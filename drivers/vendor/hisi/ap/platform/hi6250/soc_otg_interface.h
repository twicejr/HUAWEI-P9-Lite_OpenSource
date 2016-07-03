

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_OTG_INTERFACE_H__
#define __SOC_OTG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) OTG
 ****************************************************************************/
/* 寄存器说明：全局控制和状态寄存器。
   位域定义UNION结构:  SOC_OTG_GOTGCTL_UNION */
#define SOC_OTG_GOTGCTL_ADDR(base)                    ((base) + (0x0000))

/* 寄存器说明：全局OTG中断状态寄存器。
   位域定义UNION结构:  SOC_OTG_GOTGINT_UNION */
#define SOC_OTG_GOTGINT_ADDR(base)                    ((base) + (0x0004))

/* 寄存器说明：全局AHB配置寄存器。
   位域定义UNION结构:  SOC_OTG_GAHBCFG_UNION */
#define SOC_OTG_GAHBCFG_ADDR(base)                    ((base) + (0x0008))

/* 寄存器说明：全局USB配置寄存器。
   位域定义UNION结构:  SOC_OTG_GUSBCFG_UNION */
#define SOC_OTG_GUSBCFG_ADDR(base)                    ((base) + (0x000C))

/* 寄存器说明：全局复位控制寄存器。
   位域定义UNION结构:  SOC_OTG_GRSTCTL_UNION */
#define SOC_OTG_GRSTCTL_ADDR(base)                    ((base) + (0x0010))

/* 寄存器说明：全局中断状态寄存器。
   位域定义UNION结构:  SOC_OTG_GINTSTS_UNION */
#define SOC_OTG_GINTSTS_ADDR(base)                    ((base) + (0x0014))

/* 寄存器说明：全局中断屏蔽寄存器。
   位域定义UNION结构:  SOC_OTG_GINTMSK_UNION */
#define SOC_OTG_GINTMSK_ADDR(base)                    ((base) + (0x0018))

/* 寄存器说明：全局接收FIFO状态读出寄存器。
   位域定义UNION结构:  SOC_OTG_GRXSTSR_UNION */
#define SOC_OTG_GRXSTSR_ADDR(base)                    ((base) + (0x001C))

/* 寄存器说明：全局接收FIFO状态弹出寄存器。
   位域定义UNION结构:  SOC_OTG_GRXSTSP_UNION */
#define SOC_OTG_GRXSTSP_ADDR(base)                    ((base) + (0x0020))

/* 寄存器说明：全局接收FIFO大小寄存器。
   位域定义UNION结构:  SOC_OTG_GRXFSIZ_UNION */
#define SOC_OTG_GRXFSIZ_ADDR(base)                    ((base) + (0x0024))

/* 寄存器说明：全局非周期发送FIFO大小寄存器。 (Host Mode and Device Shared FIFO Mode)
   位域定义UNION结构:  SOC_OTG_GNPTXFSIZ_UNION */
#define SOC_OTG_GNPTXFSIZ_ADDR(base)                  ((base) + (0x0028))

/* 寄存器说明：全局非周期发送FIFO状态寄存器。
   位域定义UNION结构:  SOC_OTG_GNPTXSTS_UNION */
#define SOC_OTG_GNPTXSTS_ADDR(base)                   ((base) + (0x002C))

/* 寄存器说明：USB IP版本寄存器。
   位域定义UNION结构:  SOC_OTG_GSNPSID_UNION */
#define SOC_OTG_GSNPSID_ADDR(base)                    ((base) + (0x0040))

/* 寄存器说明：硬件配置寄存器1。
   位域定义UNION结构:  SOC_OTG_GHWCFG1_UNION */
#define SOC_OTG_GHWCFG1_ADDR(base)                    ((base) + (0x0044))

/* 寄存器说明：硬件配置寄存器2。
   位域定义UNION结构:  SOC_OTG_GHWCFG2_UNION */
#define SOC_OTG_GHWCFG2_ADDR(base)                    ((base) + (0x0048))

/* 寄存器说明：硬件配置寄存器3。
   位域定义UNION结构:  SOC_OTG_GHWCFG3_UNION */
#define SOC_OTG_GHWCFG3_ADDR(base)                    ((base) + (0x004C))

/* 寄存器说明：硬件配置寄存器4。
   位域定义UNION结构:  SOC_OTG_GHWCFG4_UNION */
#define SOC_OTG_GHWCFG4_ADDR(base)                    ((base) + (0x0050))

/* 寄存器说明：LPM配置寄存器。
   位域定义UNION结构:  SOC_OTG_GLPMCFG_UNION */
#define SOC_OTG_GLPMCFG_ADDR(base)                    ((base) + (0x0054))

/* 寄存器说明：冬眠模式掉电控制寄存器。
   位域定义UNION结构:  SOC_OTG_GPWRDN_UNION */
#define SOC_OTG_GPWRDN_ADDR(base)                     ((base) + (0x0058))

/* 寄存器说明：动态FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_GDFIFOCFG_UNION */
#define SOC_OTG_GDFIFOCFG_ADDR(base)                  ((base) + (0x005C))

/* 寄存器说明：ADP控制寄存器。
   位域定义UNION结构:  SOC_OTG_GADPCTL_UNION */
#define SOC_OTG_GADPCTL_ADDR(base)                    ((base) + (0x0060))

/* 寄存器说明：Host周期发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_HPTXFSIZ_UNION */
#define SOC_OTG_HPTXFSIZ_ADDR(base)                   ((base) + (0x0100))

/* 寄存器说明：Device IN端点1发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF1_UNION */
#define SOC_OTG_DIEPTXF1_ADDR(base)                   ((base) + (0x0104))

/* 寄存器说明：Device IN端点2发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF2_UNION */
#define SOC_OTG_DIEPTXF2_ADDR(base)                   ((base) + (0x0108))

/* 寄存器说明：Device IN端点3发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF3_UNION */
#define SOC_OTG_DIEPTXF3_ADDR(base)                   ((base) + (0x010C))

/* 寄存器说明：Device IN端点4发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF4_UNION */
#define SOC_OTG_DIEPTXF4_ADDR(base)                   ((base) + (0x0110))

/* 寄存器说明：Device IN端点5发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF5_UNION */
#define SOC_OTG_DIEPTXF5_ADDR(base)                   ((base) + (0x0114))

/* 寄存器说明：Device IN端点6发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF6_UNION */
#define SOC_OTG_DIEPTXF6_ADDR(base)                   ((base) + (0x0118))

/* 寄存器说明：Device IN端点7发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF7_UNION */
#define SOC_OTG_DIEPTXF7_ADDR(base)                   ((base) + (0x011C))

/* 寄存器说明：Device IN端点8发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF8_UNION */
#define SOC_OTG_DIEPTXF8_ADDR(base)                   ((base) + (0x0120))

/* 寄存器说明：Device IN端点9发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF9_UNION */
#define SOC_OTG_DIEPTXF9_ADDR(base)                   ((base) + (0x0124))

/* 寄存器说明：Device IN端点10发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF10_UNION */
#define SOC_OTG_DIEPTXF10_ADDR(base)                  ((base) + (0x0128))

/* 寄存器说明：Device IN端点11发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF11_UNION */
#define SOC_OTG_DIEPTXF11_ADDR(base)                  ((base) + (0x012C))

/* 寄存器说明：Device IN端点12发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF12_UNION */
#define SOC_OTG_DIEPTXF12_ADDR(base)                  ((base) + (0x0130))

/* 寄存器说明：Device IN端点13发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF13_UNION */
#define SOC_OTG_DIEPTXF13_ADDR(base)                  ((base) + (0x0134))

/* 寄存器说明：Device IN端点14发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF14_UNION */
#define SOC_OTG_DIEPTXF14_ADDR(base)                  ((base) + (0x0138))

/* 寄存器说明：Device IN端点15发送FIFO配置寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTXF15_UNION */
#define SOC_OTG_DIEPTXF15_ADDR(base)                  ((base) + (0x013C))

/* 寄存器说明：Host配置寄存器。
   位域定义UNION结构:  SOC_OTG_HCFG_UNION */
#define SOC_OTG_HCFG_ADDR(base)                       ((base) + (0x0400))

/* 寄存器说明：Host帧间隔寄存器。
   位域定义UNION结构:  SOC_OTG_HFIR_UNION */
#define SOC_OTG_HFIR_ADDR(base)                       ((base) + (0x0404))

/* 寄存器说明：Host帧序号寄存器。
   位域定义UNION结构:  SOC_OTG_HFNUM_UNION */
#define SOC_OTG_HFNUM_ADDR(base)                      ((base) + (0x0408))

/* 寄存器说明：Host周期发送FIFO和队列状态寄存器。
   位域定义UNION结构:  SOC_OTG_HPTXSTS_UNION */
#define SOC_OTG_HPTXSTS_ADDR(base)                    ((base) + (0x0410))

/* 寄存器说明：Host所有通道中断状态寄存器。
   位域定义UNION结构:  SOC_OTG_HAINT_UNION */
#define SOC_OTG_HAINT_ADDR(base)                      ((base) + (0x0414))

/* 寄存器说明：Host所用通道中断屏蔽寄存器。
   位域定义UNION结构:  SOC_OTG_HAINTMSK_UNION */
#define SOC_OTG_HAINTMSK_ADDR(base)                   ((base) + (0x0418))

/* 寄存器说明：帧列表基地址寄存器。
   位域定义UNION结构:  SOC_OTG_HFLBAddr_UNION */
#define SOC_OTG_HFLBAddr_ADDR(base)                   ((base) + (0x041C))

/* 寄存器说明：Host端口控制和状态寄存器。
   位域定义UNION结构:  SOC_OTG_HPRT_UNION */
#define SOC_OTG_HPRT_ADDR(base)                       ((base) + (0x0440))

/* 寄存器说明：通道p特性寄存器。
   位域定义UNION结构:  SOC_OTG_HCCHARp_UNION */
#define SOC_OTG_HCCHARp_ADDR(base, p)                 ((base) + (0x0500+0x20*(p)))

/* 寄存器说明：通道p Split控制寄存器。
   位域定义UNION结构:  SOC_OTG_HCSPLTp_UNION */
#define SOC_OTG_HCSPLTp_ADDR(base, p)                 ((base) + (0x0504+(p)*0x20))

/* 寄存器说明：通道p中断状态寄存器。
   位域定义UNION结构:  SOC_OTG_HCINTp_UNION */
#define SOC_OTG_HCINTp_ADDR(base, p)                  ((base) + (0x0508+(p)*0x20))

/* 寄存器说明：通道p中断屏蔽寄存器。
   位域定义UNION结构:  SOC_OTG_HCINTMSKp_UNION */
#define SOC_OTG_HCINTMSKp_ADDR(base, p)               ((base) + (0x050C+(p)*0x20))

/* 寄存器说明：通道p传输长度寄存器。（scatter / gather DMA模式）
   位域定义UNION结构:  SOC_OTG_HCTSIZp_UNION */
#define SOC_OTG_HCTSIZp_ADDR(base, p)                 ((base) + (0x0510+(p)*0x20))

/* 寄存器说明：通道p传输长度寄存器。（非scatter / gather DMA模式）
   位域定义UNION结构:  SOC_OTG_HCTSIZp_non_sg_UNION */
#define SOC_OTG_HCTSIZp_non_sg_ADDR(base, p)          ((base) + (0x0510+(p)*0x20))

/* 寄存器说明：通道p DMA地址寄存器。
   位域定义UNION结构:  SOC_OTG_HCDMAp_UNION */
#define SOC_OTG_HCDMAp_ADDR(base, p)                  ((base) + (0x0514+(p)*0x20))

/* 寄存器说明：通道p DMA buffer地址寄存器。
   位域定义UNION结构:  SOC_OTG_HCDMABp_UNION */
#define SOC_OTG_HCDMABp_ADDR(base, p)                 ((base) + (0x051C+(p)*0x20))

/* 寄存器说明：device配置寄存器。
   位域定义UNION结构:  SOC_OTG_DCFG_UNION */
#define SOC_OTG_DCFG_ADDR(base)                       ((base) + (0x0800))

/* 寄存器说明：device控制寄存器。
   位域定义UNION结构:  SOC_OTG_DCTL_UNION */
#define SOC_OTG_DCTL_ADDR(base)                       ((base) + (0x0804))

/* 寄存器说明：device状态寄存器。
   位域定义UNION结构:  SOC_OTG_DSTS_UNION */
#define SOC_OTG_DSTS_ADDR(base)                       ((base) + (0x0808))

/* 寄存器说明：IN端点普通中断屏蔽寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPMSK_UNION */
#define SOC_OTG_DIEPMSK_ADDR(base)                    ((base) + (0x0810))

/* 寄存器说明：OUT端点普通中断屏蔽寄存器。
   位域定义UNION结构:  SOC_OTG_DOEPMSK_UNION */
#define SOC_OTG_DOEPMSK_ADDR(base)                    ((base) + (0x0814))

/* 寄存器说明：所有端点中断状态寄存器。
   位域定义UNION结构:  SOC_OTG_DAINT_UNION */
#define SOC_OTG_DAINT_ADDR(base)                      ((base) + (0x0818))

/* 寄存器说明：所有端点中断屏蔽寄存器。
   位域定义UNION结构:  SOC_OTG_DAINTMSK_UNION */
#define SOC_OTG_DAINTMSK_ADDR(base)                   ((base) + (0x081C))

/* 寄存器说明：Vbus放电时间配置寄存器。
   位域定义UNION结构:  SOC_OTG_DVBUSDIS_UNION */
#define SOC_OTG_DVBUSDIS_ADDR(base)                   ((base) + (0x0828))

/* 寄存器说明：Vbus脉冲配置寄存器。
   位域定义UNION结构:  SOC_OTG_DVBUSPULSE_UNION */
#define SOC_OTG_DVBUSPULSE_ADDR(base)                 ((base) + (0x082C))

/* 寄存器说明：device水线控制寄存器。
   位域定义UNION结构:  SOC_OTG_DTHRCTL_UNION */
#define SOC_OTG_DTHRCTL_ADDR(base)                    ((base) + (0x0830))

/* 寄存器说明：IN端点FIFO空中断屏蔽寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPEMPMSK_UNION */
#define SOC_OTG_DIEPEMPMSK_ADDR(base)                 ((base) + (0x0834))

/* 寄存器说明：IN端点0控制寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPCTL0_UNION */
#define SOC_OTG_DIEPCTL0_ADDR(base)                   ((base) + (0x0900))

/* 寄存器说明：IN端点n控制寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPCTLn_UNION */
#define SOC_OTG_DIEPCTLn_ADDR(base, n)                ((base) + (0x0900+0x20*(n)))

/* 寄存器说明：IN端点m中断状态寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPINTm_UNION */
#define SOC_OTG_DIEPINTm_ADDR(base, m)                ((base) + (0x0908+0x20*(m)))

/* 寄存器说明：IN端点0传输大小寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTSIZ0_UNION */
#define SOC_OTG_DIEPTSIZ0_ADDR(base)                  ((base) + (0x0910))

/* 寄存器说明：IN端点n传输大小寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPTSIZn_UNION */
#define SOC_OTG_DIEPTSIZn_ADDR(base, n)               ((base) + (0x0910+0x20*(n)))

/* 寄存器说明：IN端点m DMA地址寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPDMAm_UNION */
#define SOC_OTG_DIEPDMAm_ADDR(base, m)                ((base) + (0x0914+0x20*(m)))

/* 寄存器说明：IN端点m发送FIFO状态寄存器。
   位域定义UNION结构:  SOC_OTG_DTXFSTSm_UNION */
#define SOC_OTG_DTXFSTSm_ADDR(base)                   ((base) + (0x0918))

/* 寄存器说明：IN端点m DMA buffer地址寄存器。
   位域定义UNION结构:  SOC_OTG_DIEPDMABn_UNION */
#define SOC_OTG_DIEPDMABn_ADDR(base, m)               ((base) + (0x091C+0x20*(m)))

/* 寄存器说明：OUT端点0控制寄存器。
   位域定义UNION结构:  SOC_OTG_DOEPCTL0_UNION */
#define SOC_OTG_DOEPCTL0_ADDR(base)                   ((base) + (0x0B00))

/* 寄存器说明：OUT端点n控制寄存器。
   位域定义UNION结构:  SOC_OTG_DOEPCTLn_UNION */
#define SOC_OTG_DOEPCTLn_ADDR(base, n)                ((base) + (0x0B00+0x20*(n)))

/* 寄存器说明：OUT端点m中断状态寄存器。
   位域定义UNION结构:  SOC_OTG_DOEPINTm_UNION */
#define SOC_OTG_DOEPINTm_ADDR(base, m)                ((base) + (0x0B08+0x20*(m)))

/* 寄存器说明：OUT端点0传输大小寄存器。
   位域定义UNION结构:  SOC_OTG_DOEPTSIZ0_UNION */
#define SOC_OTG_DOEPTSIZ0_ADDR(base)                  ((base) + (0x0B10))

/* 寄存器说明：OUT端点n传输大小寄存器。
   位域定义UNION结构:  SOC_OTG_DOEPTSIZn_UNION */
#define SOC_OTG_DOEPTSIZn_ADDR(base, n)               ((base) + (0x0B10+0x20*(n)))

/* 寄存器说明：OUT端点m DMA地址寄存器。
   位域定义UNION结构:  SOC_OTG_DOEPDMAm_UNION */
#define SOC_OTG_DOEPDMAm_ADDR(base, m)                ((base) + (0x0B14+0x20*(m)))

/* 寄存器说明：OUT端点m DMA buffer地址寄存器。
   位域定义UNION结构:  SOC_OTG_DOEPDMABm_UNION */
#define SOC_OTG_DOEPDMABm_ADDR(base, m)               ((base) + (0x0B1C+0x20*(m)))

/* 寄存器说明：功耗和时钟门控控制寄存器。
   位域定义UNION结构:  SOC_OTG_PCGCCTL_UNION */
#define SOC_OTG_PCGCCTL_ADDR(base)                    ((base) + (0x0E00))





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
                     (1/1) OTG
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_OTG_GOTGCTL_UNION
 结构说明  : GOTGCTL 寄存器结构定义。地址偏移量:0x0000，初值:0x00010000，宽度:32
 寄存器说明: 全局控制和状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SesReqScs       : 1;  /* bit[0]    : 会话请求是否成功。
                                                           0：失败；
                                                           1：成功。 */
        unsigned int  SesReq          : 1;  /* bit[1]    : 会话请求。
                                                           0：无会话请求；
                                                           1：会话请求。 */
        unsigned int  VbvalidOvEn     : 1;  /* bit[2]    : 忽略PHY给出的vbusvalid信号使能。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  VbvalidOvVal    : 1;  /* bit[3]    : 当VbvalidOvEn＝1时，该bit用于设置vbusvalid值而忽略PHY给出的vbusvalid信号。
                                                           0：vbusvalid无效；
                                                           1：vbusvalid有效。 */
        unsigned int  AvalidOvEn      : 1;  /* bit[4]    : 忽略PHY给出的avalid信号使能。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  AvalidOvVal     : 1;  /* bit[5]    : 当AvalidOvEn＝1时，该bit用于设置avalid值而忽略PHY给出的avalid信号。
                                                           0：avalid无效；
                                                           1：avalid有效。 */
        unsigned int  BvalidOvEn      : 1;  /* bit[6]    : 忽略PHY给出的bvalid信号使能。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  BvalidOvVal     : 1;  /* bit[7]    : 当BvalidOvEn＝1时，该bit用于设置bvalid值而忽略PHY给出的bvalid信号。
                                                           0：bvalid无效；
                                                           1：bvalid有效。 */
        unsigned int  HstNegScs       : 1;  /* bit[8]    : 主机协商成功，对device模式有效。
                                                           0：失败；
                                                           1：成功。 */
        unsigned int  HNPReq          : 1;  /* bit[9]    : HNP请求，对device模式有效。软件配置该bit，向host发起HNP操作。在接收到GOTGINT.HstNegSucStsChng中断之后，软件清除该bit。
                                                           0：无请求；
                                                           1：有请求。 */
        unsigned int  HstSetHNPEn     : 1;  /* bit[10]   : HOST HNP使能，对Host模式有效。Host在发出SetFeature.SetHNPEnabled命令之后，软件配置该bit为1。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  DevHNPEn        : 1;  /* bit[11]   : device HNP使能，对device模式有效。接收到SetFeature.SetHNPEnabled命令之后软件配置该bit为1。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  EHEn            : 1;  /* bit[12]   : Embedded Host enable
                                                           1：选择embedded host state machine
                                                           0：选择OTG A device state machine */
        unsigned int  reserved_0      : 2;  /* bit[13-14]: 保留。 */
        unsigned int  DbnceFltrBypass : 1;  /* bit[15]   : Debounce Filter Bypass
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  conidsts        : 1;  /* bit[16]   : 插座ID状态。
                                                           0：A设备模式；
                                                           1：B设备模式。 */
        unsigned int  dbnc_time       : 1;  /* bit[17]   : debounce时间选择。Debounce时间指协议上规定的检测到device连接状态之后到发送复位信号之间的延迟。
                                                           0：100ms+2.5us，用于物理连接；
                                                           1：2.5us，用于软连接。 */
        unsigned int  asessvld        : 1;  /* bit[18]   : Host模式收发器状态。
                                                           0：a_session无效；
                                                           1：a_session有效。 */
        unsigned int  bsesvld         : 1;  /* bit[19]   : 设备连接状态指示。
                                                           0：未连接；
                                                           1：连接。 */
        unsigned int  otg_version     : 1;  /* bit[20]   : OTG协议版本。
                                                           0：1.3。支持数据线和VBUS脉冲实现SRP协议；
                                                           1：2.0。只支持数据线脉冲实现SRP协议。 */
        unsigned int  reserved_1      : 1;  /* bit[21]   : 保留。 */
        unsigned int  multvaldidbc    : 5;  /* bit[22-26]: ACA ID管脚状态。
                                                           00001：rid_c；
                                                           00010：rid_b；
                                                           00100：rid_a；
                                                           01000：rid_gnd；
                                                           10000：rid_float；
                                                           others：reserved。 */
        unsigned int  chirpen         : 1;  /* bit[27]   : chirpon使能。
                                                           该bit配置为1，控制器在发送chirp K之前置chirp_on信号为高电平。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  reserved_2      : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_OTG_GOTGCTL_UNION;
#endif
#define SOC_OTG_GOTGCTL_SesReqScs_START        (0)
#define SOC_OTG_GOTGCTL_SesReqScs_END          (0)
#define SOC_OTG_GOTGCTL_SesReq_START           (1)
#define SOC_OTG_GOTGCTL_SesReq_END             (1)
#define SOC_OTG_GOTGCTL_VbvalidOvEn_START      (2)
#define SOC_OTG_GOTGCTL_VbvalidOvEn_END        (2)
#define SOC_OTG_GOTGCTL_VbvalidOvVal_START     (3)
#define SOC_OTG_GOTGCTL_VbvalidOvVal_END       (3)
#define SOC_OTG_GOTGCTL_AvalidOvEn_START       (4)
#define SOC_OTG_GOTGCTL_AvalidOvEn_END         (4)
#define SOC_OTG_GOTGCTL_AvalidOvVal_START      (5)
#define SOC_OTG_GOTGCTL_AvalidOvVal_END        (5)
#define SOC_OTG_GOTGCTL_BvalidOvEn_START       (6)
#define SOC_OTG_GOTGCTL_BvalidOvEn_END         (6)
#define SOC_OTG_GOTGCTL_BvalidOvVal_START      (7)
#define SOC_OTG_GOTGCTL_BvalidOvVal_END        (7)
#define SOC_OTG_GOTGCTL_HstNegScs_START        (8)
#define SOC_OTG_GOTGCTL_HstNegScs_END          (8)
#define SOC_OTG_GOTGCTL_HNPReq_START           (9)
#define SOC_OTG_GOTGCTL_HNPReq_END             (9)
#define SOC_OTG_GOTGCTL_HstSetHNPEn_START      (10)
#define SOC_OTG_GOTGCTL_HstSetHNPEn_END        (10)
#define SOC_OTG_GOTGCTL_DevHNPEn_START         (11)
#define SOC_OTG_GOTGCTL_DevHNPEn_END           (11)
#define SOC_OTG_GOTGCTL_EHEn_START             (12)
#define SOC_OTG_GOTGCTL_EHEn_END               (12)
#define SOC_OTG_GOTGCTL_DbnceFltrBypass_START  (15)
#define SOC_OTG_GOTGCTL_DbnceFltrBypass_END    (15)
#define SOC_OTG_GOTGCTL_conidsts_START         (16)
#define SOC_OTG_GOTGCTL_conidsts_END           (16)
#define SOC_OTG_GOTGCTL_dbnc_time_START        (17)
#define SOC_OTG_GOTGCTL_dbnc_time_END          (17)
#define SOC_OTG_GOTGCTL_asessvld_START         (18)
#define SOC_OTG_GOTGCTL_asessvld_END           (18)
#define SOC_OTG_GOTGCTL_bsesvld_START          (19)
#define SOC_OTG_GOTGCTL_bsesvld_END            (19)
#define SOC_OTG_GOTGCTL_otg_version_START      (20)
#define SOC_OTG_GOTGCTL_otg_version_END        (20)
#define SOC_OTG_GOTGCTL_multvaldidbc_START     (22)
#define SOC_OTG_GOTGCTL_multvaldidbc_END       (26)
#define SOC_OTG_GOTGCTL_chirpen_START          (27)
#define SOC_OTG_GOTGCTL_chirpen_END            (27)


/*****************************************************************************
 结构名    : SOC_OTG_GOTGINT_UNION
 结构说明  : GOTGINT 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 全局OTG中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0       : 2;  /* bit[0-1]  : 保留。 */
        unsigned int  SesEndDet        : 1;  /* bit[2]    : 检测到会话请求结束，即指示utmisrp_bvalid信号变为低电平。
                                                            0：无中断；
                                                            1：有中断。 */
        unsigned int  reserved_1       : 5;  /* bit[3-7]  : 保留。 */
        unsigned int  SesReqSucStsChng : 1;  /* bit[8]    : 会话请求状态变化。当会话请求成功或者失败时，该bit置1。软件必须通过查询寄存器GPTGCTL[SesReqScs]来确定会话请求是成功还是失败。
                                                            0：无中断；
                                                            1：有中断。 */
        unsigned int  HstNegSucStsChng : 1;  /* bit[9]    : 主机协商成功状态变化。
                                                            0：无中断；
                                                            1：有中断。 */
        unsigned int  reserved_2       : 7;  /* bit[10-16]: 保留。 */
        unsigned int  HstNegDet        : 1;  /* bit[17]   : 检测到主机协商请求。
                                                            0：无中断；
                                                            1：有中断。 */
        unsigned int  ADevTOUTChg      : 1;  /* bit[18]   : A设备等待B设备连接超时。
                                                            0：无中断；
                                                            1：有中断。 */
        unsigned int  DbnceDone        : 1;  
        unsigned int  MultValIDChng    : 1;  /* bit[20]   : 至少一个ACA管脚状态发生变化。
                                                            0：无中断；
                                                            1：有中断。 */
        unsigned int  reserved_3       : 11; /* bit[21-31]: 保留 */
    } reg;
} SOC_OTG_GOTGINT_UNION;
#endif
#define SOC_OTG_GOTGINT_SesEndDet_START         (2)
#define SOC_OTG_GOTGINT_SesEndDet_END           (2)
#define SOC_OTG_GOTGINT_SesReqSucStsChng_START  (8)
#define SOC_OTG_GOTGINT_SesReqSucStsChng_END    (8)
#define SOC_OTG_GOTGINT_HstNegSucStsChng_START  (9)
#define SOC_OTG_GOTGINT_HstNegSucStsChng_END    (9)
#define SOC_OTG_GOTGINT_HstNegDet_START         (17)
#define SOC_OTG_GOTGINT_HstNegDet_END           (17)
#define SOC_OTG_GOTGINT_ADevTOUTChg_START       (18)
#define SOC_OTG_GOTGINT_ADevTOUTChg_END         (18)
#define SOC_OTG_GOTGINT_DbnceDone_START         (19)
#define SOC_OTG_GOTGINT_DbnceDone_END           (19)
#define SOC_OTG_GOTGINT_MultValIDChng_START     (20)
#define SOC_OTG_GOTGINT_MultValIDChng_END       (20)


/*****************************************************************************
 结构名    : SOC_OTG_GAHBCFG_UNION
 结构说明  : GAHBCFG 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 全局AHB配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  GlblIntrMsk       : 1;  /* bit[0]    : 全局中断屏蔽位。用于屏蔽所有中断的上报。
                                                             0：屏蔽；
                                                             1：不屏蔽。 */
        unsigned int  HBstLen           : 4;  /* bit[1-4]  : burst类型控制，配置DMA AHB总线传输burst类型。
                                                             0000：single；
                                                             0001：incr；
                                                             0011：incr4；
                                                             0101：incr8；
                                                             0111：incr16；
                                                             others：reserved。 */
        unsigned int  DMAEn             : 1;  /* bit[5]    : DMA使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  reserved_0        : 1;  /* bit[6]    : 保留。 */
        unsigned int  NPTxFEmpLvl       : 1;  /* bit[7]    : 发送FIFO空水标，配置发送FIFO空中断GINTSTS[NPTxFEmp]的触发条件。
                                                             0：发送FIFO半空；
                                                             1：发送FIFO全空。
                                                             Dedicated FIFO in device mode
                                                             0：IN Endpoint TxFIFO半空
                                                             1：IN Endpoint TxFIFO全空 */
        unsigned int  reserved_1        : 13; /* bit[8-20] : 保留。 */
        unsigned int  RemMemSupp        : 1;  /* bit[21]   : host和device移去memory支持 */
        unsigned int  NotiAllDmaWrit    : 1;  /* bit[22]   : host和device通知所有的DMA写传输
                                                             1：通知所有的DMA写传输
                                                             0：根据相应的通道或端点通知最后一次DMA写传输 */
        unsigned int  AHBsingle         : 1;  /* bit[23]   : AHB Master接口single操作配置。
                                                             0：采用INCR burst方式；
                                                             1：采用SINGLE burst方式。 */
        unsigned int  InvDescEndianness : 1;  /* bit[24]   : Host and Device Inverse descriptor Endiannness
                                                             0：descriptor Endiannness同AHB Master的Endiannness一样
                                                             1：如AHB Master的Endiannness是大端，descriptor Endiannness为小端
                                                             0：如AHB Master的Endiannness是小端，descriptor Endiannness为大端 */
        unsigned int  reserved_2        : 7;  /* bit[25-31]:  */
    } reg;
} SOC_OTG_GAHBCFG_UNION;
#endif
#define SOC_OTG_GAHBCFG_GlblIntrMsk_START        (0)
#define SOC_OTG_GAHBCFG_GlblIntrMsk_END          (0)
#define SOC_OTG_GAHBCFG_HBstLen_START            (1)
#define SOC_OTG_GAHBCFG_HBstLen_END              (4)
#define SOC_OTG_GAHBCFG_DMAEn_START              (5)
#define SOC_OTG_GAHBCFG_DMAEn_END                (5)
#define SOC_OTG_GAHBCFG_NPTxFEmpLvl_START        (7)
#define SOC_OTG_GAHBCFG_NPTxFEmpLvl_END          (7)
#define SOC_OTG_GAHBCFG_RemMemSupp_START         (21)
#define SOC_OTG_GAHBCFG_RemMemSupp_END           (21)
#define SOC_OTG_GAHBCFG_NotiAllDmaWrit_START     (22)
#define SOC_OTG_GAHBCFG_NotiAllDmaWrit_END       (22)
#define SOC_OTG_GAHBCFG_AHBsingle_START          (23)
#define SOC_OTG_GAHBCFG_AHBsingle_END            (23)
#define SOC_OTG_GAHBCFG_InvDescEndianness_START  (24)
#define SOC_OTG_GAHBCFG_InvDescEndianness_END    (24)


/*****************************************************************************
 结构名    : SOC_OTG_GUSBCFG_UNION
 结构说明  : GUSBCFG 寄存器结构定义。地址偏移量:0x000C，初值:0x00001400，宽度:32
 寄存器说明: 全局USB配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TOutCal              : 3;  /* bit[0-2]  : 高速和全速超时时间调整。单位为PHY时钟周期，用于调整标准超时时间。 */
        unsigned int  PHYIf                : 1;  /* bit[3]    : PHY数据位宽选择。
                                                                0：8bit；
                                                                1：16bit。 */
        unsigned int  ULPI_UTMI_Sel        : 1;  /* bit[4]    : ULPI 或UTMI+选择
                                                                0：选择UTMI+接口
                                                                1：选择ULPI接口 */
        unsigned int  FSIntf               : 1;  /* bit[5]    : 全速总线选择
                                                                0：6-pin无方向FS总线接口
                                                                1：3-pin有方向FS总线接口 */
        unsigned int  PHYSel               : 1;  /* bit[6]    : PHY 选择
                                                                0：选USB2.0高速UTMI+或ULPI PHY
                                                                1：选usb1.1全速收发器 */
        unsigned int  DDRSel               : 1;  /* bit[7]    : ULPI DDR选择
                                                                0：单独Data Rate ULPI接口，8位宽
                                                                1：成对Data Rate ULPI接口，4位宽 */
        unsigned int  SRPCap               : 1;  /* bit[8]    : SRP功能使能。
                                                                0：不使能；
                                                                1：使能。 */
        unsigned int  HNPCap               : 1;  /* bit[9]    : HNP功能使能。
                                                                0：不使能；
                                                                1：使能。 */
        unsigned int  USBTrdTim            : 4;  /* bit[10-13]: USB回转时间。指示从MAC发出请求到从FIFO中取出数据的时间，单位为PHY时钟周期。
                                                                必须配置成如下值：
                                                                0101：PHY数据位宽是16bit；
                                                                1001：PHY数据位宽是8bit。 */
        unsigned int  reserved             : 1;  /* bit[14]   : 保留。 */
        unsigned int  PhyPwrClkSel         : 1;  /* bit[15]   : PHY低功耗模式时钟选择。
                                                                0：480MHz内部时钟；
                                                                1：48MHz外部时钟。 */
        unsigned int  Otgl2CSel            : 1;  /* bit[16]   : 选择UTMIFS或I2C接口
                                                                0：OTG信号使用UTMI USB1.1全速接口
                                                                1：OTG信号使用I2C接口 */
        unsigned int  ULPIFsLs             : 1;  /* bit[17]   : ULPI FS/LS选择
                                                                0: ULPI interface 
                                                                1: ULPI FS/LS serial interface */
        unsigned int  ULPIAutoRes          : 1;  /* bit[18]   : ULPI自动唤醒
                                                                0：PHY不使用AutoResume特性
                                                                1：PHY使用AutoResume特性 */
        unsigned int  ULPIClkSusM          : 1;  /* bit[19]   : ULPI时钟挂起
                                                                0：suspend时，PHY对内部时钟下电
                                                                1：PHY不对内部时钟下电 */
        unsigned int  ULPIExVbusDrv        : 1;  /* bit[20]   : HOST模式下ULPI外部VBUS驱动
                                                                0：PHY使用内部charge pump驱动VBUS
                                                                1：PHY使用外部电源驱动VBUS */
        unsigned int  ULPIExtVbusIndicator : 1;  /* bit[21]   : HOST模式下ULPI外部VBUS比较
                                                                0：PHY使用内部VBUS比较
                                                                1：PHY使用外部VBUS比较 */
        unsigned int  TermSelDLPulse       : 1;  /* bit[22]   : device模式下TermSel数据线选择
                                                                0：使用utmi_txvalid进行Data line pulsing
                                                                1：使用utmi_termsel进行Data line pulsing */
        unsigned int  Complement           : 1;  /* bit[23]   : HOST模式下Indicator Complement 
                                                                0：PHY不反转ExternalVbusIndicator信号
                                                                1：PHY反转ExternalVbusIndicator信号 */
        unsigned int  Indicator            : 1;  /* bit[24]   : HOST模式下Indicator Pass Through
                                                                0：Complement Output信号符合内部VbusValid comparator
                                                                1：Complement Output信号不符合内部VbusValid comparator */
        unsigned int  ULPI                 : 1;  /* bit[25]   : HOST模式下ULPI接口保护电路使能
                                                                0：接口保护电路使能
                                                                1：接口保护电路不使能 */
        unsigned int  IC_USBCap            : 1;  /* bit[26]   : IC_USB-Capable 
                                                                0：不选择IC_USB PHY Interface
                                                                1：选择IC_USB PHY Interface */
        unsigned int  IC_USBTrafCtl        : 1;  /* bit[27]   : device模式下IC_USB TrafficPullRemove Control  */
        unsigned int  TxEndDelay           : 1;  /* bit[28]   : 发送结束延迟。配置该bit，按照UTMI 1.05版本使能发送结束timer。
                                                                0：不使能；
                                                                1：使能。 */
        unsigned int  ForceHstMode         : 1;  /* bit[29]   : 强制为Host模式。
                                                                0：正常模式；
                                                                1：host模式。 */
        unsigned int  ForceDevMode         : 1;  /* bit[30]   : 强制为device模式。
                                                                0：正常模式；
                                                                1：device模式。 */
        unsigned int  CtptTxPkt            : 1;  /* bit[31]   : 破坏包发送，用于debug，正常使用时不能配置该bit为1。
                                                                0：不发送破坏包；
                                                                1：发送破坏包。 */
    } reg;
} SOC_OTG_GUSBCFG_UNION;
#endif
#define SOC_OTG_GUSBCFG_TOutCal_START               (0)
#define SOC_OTG_GUSBCFG_TOutCal_END                 (2)
#define SOC_OTG_GUSBCFG_PHYIf_START                 (3)
#define SOC_OTG_GUSBCFG_PHYIf_END                   (3)
#define SOC_OTG_GUSBCFG_ULPI_UTMI_Sel_START         (4)
#define SOC_OTG_GUSBCFG_ULPI_UTMI_Sel_END           (4)
#define SOC_OTG_GUSBCFG_FSIntf_START                (5)
#define SOC_OTG_GUSBCFG_FSIntf_END                  (5)
#define SOC_OTG_GUSBCFG_PHYSel_START                (6)
#define SOC_OTG_GUSBCFG_PHYSel_END                  (6)
#define SOC_OTG_GUSBCFG_DDRSel_START                (7)
#define SOC_OTG_GUSBCFG_DDRSel_END                  (7)
#define SOC_OTG_GUSBCFG_SRPCap_START                (8)
#define SOC_OTG_GUSBCFG_SRPCap_END                  (8)
#define SOC_OTG_GUSBCFG_HNPCap_START                (9)
#define SOC_OTG_GUSBCFG_HNPCap_END                  (9)
#define SOC_OTG_GUSBCFG_USBTrdTim_START             (10)
#define SOC_OTG_GUSBCFG_USBTrdTim_END               (13)
#define SOC_OTG_GUSBCFG_PhyPwrClkSel_START          (15)
#define SOC_OTG_GUSBCFG_PhyPwrClkSel_END            (15)
#define SOC_OTG_GUSBCFG_Otgl2CSel_START             (16)
#define SOC_OTG_GUSBCFG_Otgl2CSel_END               (16)
#define SOC_OTG_GUSBCFG_ULPIFsLs_START              (17)
#define SOC_OTG_GUSBCFG_ULPIFsLs_END                (17)
#define SOC_OTG_GUSBCFG_ULPIAutoRes_START           (18)
#define SOC_OTG_GUSBCFG_ULPIAutoRes_END             (18)
#define SOC_OTG_GUSBCFG_ULPIClkSusM_START           (19)
#define SOC_OTG_GUSBCFG_ULPIClkSusM_END             (19)
#define SOC_OTG_GUSBCFG_ULPIExVbusDrv_START         (20)
#define SOC_OTG_GUSBCFG_ULPIExVbusDrv_END           (20)
#define SOC_OTG_GUSBCFG_ULPIExtVbusIndicator_START  (21)
#define SOC_OTG_GUSBCFG_ULPIExtVbusIndicator_END    (21)
#define SOC_OTG_GUSBCFG_TermSelDLPulse_START        (22)
#define SOC_OTG_GUSBCFG_TermSelDLPulse_END          (22)
#define SOC_OTG_GUSBCFG_Complement_START            (23)
#define SOC_OTG_GUSBCFG_Complement_END              (23)
#define SOC_OTG_GUSBCFG_Indicator_START             (24)
#define SOC_OTG_GUSBCFG_Indicator_END               (24)
#define SOC_OTG_GUSBCFG_ULPI_START                  (25)
#define SOC_OTG_GUSBCFG_ULPI_END                    (25)
#define SOC_OTG_GUSBCFG_IC_USBCap_START             (26)
#define SOC_OTG_GUSBCFG_IC_USBCap_END               (26)
#define SOC_OTG_GUSBCFG_IC_USBTrafCtl_START         (27)
#define SOC_OTG_GUSBCFG_IC_USBTrafCtl_END           (27)
#define SOC_OTG_GUSBCFG_TxEndDelay_START            (28)
#define SOC_OTG_GUSBCFG_TxEndDelay_END              (28)
#define SOC_OTG_GUSBCFG_ForceHstMode_START          (29)
#define SOC_OTG_GUSBCFG_ForceHstMode_END            (29)
#define SOC_OTG_GUSBCFG_ForceDevMode_START          (30)
#define SOC_OTG_GUSBCFG_ForceDevMode_END            (30)
#define SOC_OTG_GUSBCFG_CtptTxPkt_START             (31)
#define SOC_OTG_GUSBCFG_CtptTxPkt_END               (31)


/*****************************************************************************
 结构名    : SOC_OTG_GRSTCTL_UNION
 结构说明  : GRSTCTL 寄存器结构定义。地址偏移量:0x0010，初值:0x80000000，宽度:32
 寄存器说明: 全局复位控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CSftRst    : 1;  /* bit[0]    : 软复位请求。复位总线时钟域和phy时钟域。操作完成该bit自动清零。
                                                      0：软复位完成；
                                                      1：进行软复位。 */
        unsigned int  reserved_0 : 1;  /* bit[1]    : 保留。 */
        unsigned int  FrmCntrRst : 1;  /* bit[2]    : 微帧号计数复位。操作完成该bit自动清零。
                                                      0：不复位；
                                                      1：复位。 */
        unsigned int  reserved_1 : 1;  /* bit[3]    : 保留。 */
        unsigned int  RxFFlsh    : 1;  /* bit[4]    : 清空接收FIFO。操作完成，该bit自动清零。配置该bit之前，必须保证对接收FIFO没有读写操作。
                                                      0：清空接收FIFO完成；
                                                      1：清空接收FIFO。 */
        unsigned int  TxFFlsh    : 1;  
        unsigned int  TxFNum     : 5;  /* bit[6-10] : 清空发送FIFO序号。指示用TxFFlsh命令清除的发送FIFO，在TxFFlsh位清零之前不能改变TxFNum值。
                                                      0：Host模式下清空非周期发送FIFO，Device模式下清空发送FIFO 0；
                                                      1：Host模式下清空周期发送FIFO，Device模式下清空发送FIFO 1；
                                                      2：Device模式下，清空发送FIFO 2；
                                                      ……
                                                      F：Device模式下，清空发送FIFO 15；
                                                      10：清空所有发送FIFO；
                                                      others：reserved。 */
        unsigned int  reserved_2 : 19; /* bit[11-29]: 保留。 */
        unsigned int  DMAReq     : 1;  /* bit[30]   : DMA请求状态。指示是否正在处理DMA请求，用于debug。
                                                      0：无DMA请求；
                                                      1：DMA请求正在处理。 */
        unsigned int  AHBIdle    : 1;  /* bit[31]   : AHB总线状态。指示AHB master状态机处于空闲状态。
                                                      0：不处于空闲状态；
                                                      1：处于空闲状态。 */
    } reg;
} SOC_OTG_GRSTCTL_UNION;
#endif
#define SOC_OTG_GRSTCTL_CSftRst_START     (0)
#define SOC_OTG_GRSTCTL_CSftRst_END       (0)
#define SOC_OTG_GRSTCTL_FrmCntrRst_START  (2)
#define SOC_OTG_GRSTCTL_FrmCntrRst_END    (2)
#define SOC_OTG_GRSTCTL_RxFFlsh_START     (4)
#define SOC_OTG_GRSTCTL_RxFFlsh_END       (4)
#define SOC_OTG_GRSTCTL_TxFFlsh_START     (5)
#define SOC_OTG_GRSTCTL_TxFFlsh_END       (5)
#define SOC_OTG_GRSTCTL_TxFNum_START      (6)
#define SOC_OTG_GRSTCTL_TxFNum_END        (10)
#define SOC_OTG_GRSTCTL_DMAReq_START      (30)
#define SOC_OTG_GRSTCTL_DMAReq_END        (30)
#define SOC_OTG_GRSTCTL_AHBIdle_START     (31)
#define SOC_OTG_GRSTCTL_AHBIdle_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_GINTSTS_UNION
 结构说明  : GINTSTS 寄存器结构定义。地址偏移量:0x0014，初值:0x14000020，宽度:32
 寄存器说明: 全局中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CurMode      : 1;  /* bit[0] : 当前模式。
                                                     0：device模式；
                                                     1：host模式。 */
        unsigned int  ModeMis      : 1;  /* bit[1] : 模式不匹配中断。如果当前为host模式，软件读写device寄存器；如果当前为device模式，软件读写host寄存器会触发该中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  OTGInt       : 1;  /* bit[2] : OTG中断。软件需要查询寄存器GOTGINT确定中断类型。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  Sof          : 1;  /* bit[3] : SOF(Start Of microFrame)中断。指示接收到SOF令牌包。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  RxFLvl       : 1;  /* bit[4] : 接收FIFO非空中断。指示接收FIFO中至少1个包的数据。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  NPTxFEmp     : 1;  /* bit[5] : 非周期发送FIFO空中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  GINNakEff    : 1;  /* bit[6] : 非周期IN端点NAK有效中断。指示寄存器DCTL[SGNPInNak]设置有效，对所有的IN令牌响应NAK。该bit可以通过写DCTL[CGNPInNak]来清除。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  GOUTNakEff   : 1;  /* bit[7] : OUT端点NAK有效中断。指示寄存器DCTL[SGOUTNak]设置有效，对所有的OUT令牌包响应NAK。该bit可以通过写寄存器DCTL[CGOUTNak]来清除。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  ULPICKINT    : 1;  /* bit[8] : ULPI Carkit中断
                                                     接收到 ULPI Carkit中断后有效 */
        unsigned int  I2CINT       : 1;  /* bit[9] : I2C接口
                                                     I2C接入完成后有效 */
        unsigned int  ErlySusp     : 1;  /* bit[10]: Early suspend中断。当检测到USB处于IDLE状态超过3ms会触发该中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  USBSusp      : 1;  /* bit[11]: suspend中断。指示进入suspend状态。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  USBRst       : 1;  /* bit[12]: USB复位中断。指示检测到USB复位操作。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  EnumDone     : 1;  /* bit[13]: 枚举完成中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  ISOOutDrop   : 1;  /* bit[14]: Isochronous OUT包丢弃中断。当收到Isochronous OUT包，但是由于接收FIFO空间不够，USB会丢弃收到的包，并置位该中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  EOPF         : 1;  /* bit[15]: EOPF（End of Period Frame）中断，指示在当前帧周期传输结束。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  RstrDoneInt  : 1;  /* bit[16]: 寄存器恢复中断。指示退出冬眠模式后，寄存器恢复操作完成。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  reserved     : 1;  /* bit[17]: 保留。 */
        unsigned int  IEPInt       : 1;  /* bit[18]: IN端点中断。指示IN端点有中断产生。软件需要查询寄存器DAINT确定端点号，然后查询相应端点的中断状态寄存器确定中断类型。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  OEPInt       : 1;  /* bit[19]: OUT端点中断。指示OUT端点有中断产生。软件需要查询寄存器DAINT确定端点号，然后查询相应端点的中断状态寄存器确定中断类型。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  incompISOIN  : 1;  /* bit[20]: Isochronous IN传输未完成中断。指示至少有1个IN端点的Isochronous传输在当前的微帧未完成。该中断与EOPF中断同时产生。
                                                     0：无中断
                                                     1：有中断 */
        unsigned int  incompISOOUT : 1;  /* bit[21]: Isochronous OUT传输未完成中断。指示至少有1个OUT端点的Isochronous传输在当前的微帧未完成。该中断与EOPF中断同时产生。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  FetSusp      : 1;  /* bit[22]: 取数挂起中断。仅在DMA模式时有效。该中断指示由于发送FIFO没有空间的原因，DMA停止给IN端点从memory读取数据。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  ResetDet     : 1;  /* bit[23]: 检测到复位中断。当设备处于suspend状态，部分掉电时，检测到USB总线上有复位操作，会触发该中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  HPrtInt      : 1;  /* bit[24]: Host端口中断。软件需要通过HPRT寄存器确定具体中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  HChInt       : 1;  /* bit[25]: Host通道中断。指示任何一个通道有中断触发，软件需要通过HCINTn寄存器确定具体中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  PTxFEmp      : 1;  /* bit[26]: 周期发送FIFO空中断，对host模式有效。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  LPM_Int      : 1;  /* bit[27]: LPM接收中断。当USB接收到LPM包，且向host响应非ERROR，该中断会触发。该位仅当LPM功能使能时有效。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  ConIDStsChg  : 1;  /* bit[28]: ID状态变化中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  DisconnInt   : 1;  /* bit[29]: 断开连接中断，对host模式有效。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  SessReqInt   : 1;  /* bit[30]: 检测到会话请求中断。当utmisrp_bvalid从低电平变成高电平，会产生该中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned int  WkUpInt      : 1;  
    } reg;
} SOC_OTG_GINTSTS_UNION;
#endif
#define SOC_OTG_GINTSTS_CurMode_START       (0)
#define SOC_OTG_GINTSTS_CurMode_END         (0)
#define SOC_OTG_GINTSTS_ModeMis_START       (1)
#define SOC_OTG_GINTSTS_ModeMis_END         (1)
#define SOC_OTG_GINTSTS_OTGInt_START        (2)
#define SOC_OTG_GINTSTS_OTGInt_END          (2)
#define SOC_OTG_GINTSTS_Sof_START           (3)
#define SOC_OTG_GINTSTS_Sof_END             (3)
#define SOC_OTG_GINTSTS_RxFLvl_START        (4)
#define SOC_OTG_GINTSTS_RxFLvl_END          (4)
#define SOC_OTG_GINTSTS_NPTxFEmp_START      (5)
#define SOC_OTG_GINTSTS_NPTxFEmp_END        (5)
#define SOC_OTG_GINTSTS_GINNakEff_START     (6)
#define SOC_OTG_GINTSTS_GINNakEff_END       (6)
#define SOC_OTG_GINTSTS_GOUTNakEff_START    (7)
#define SOC_OTG_GINTSTS_GOUTNakEff_END      (7)
#define SOC_OTG_GINTSTS_ULPICKINT_START     (8)
#define SOC_OTG_GINTSTS_ULPICKINT_END       (8)
#define SOC_OTG_GINTSTS_I2CINT_START        (9)
#define SOC_OTG_GINTSTS_I2CINT_END          (9)
#define SOC_OTG_GINTSTS_ErlySusp_START      (10)
#define SOC_OTG_GINTSTS_ErlySusp_END        (10)
#define SOC_OTG_GINTSTS_USBSusp_START       (11)
#define SOC_OTG_GINTSTS_USBSusp_END         (11)
#define SOC_OTG_GINTSTS_USBRst_START        (12)
#define SOC_OTG_GINTSTS_USBRst_END          (12)
#define SOC_OTG_GINTSTS_EnumDone_START      (13)
#define SOC_OTG_GINTSTS_EnumDone_END        (13)
#define SOC_OTG_GINTSTS_ISOOutDrop_START    (14)
#define SOC_OTG_GINTSTS_ISOOutDrop_END      (14)
#define SOC_OTG_GINTSTS_EOPF_START          (15)
#define SOC_OTG_GINTSTS_EOPF_END            (15)
#define SOC_OTG_GINTSTS_RstrDoneInt_START   (16)
#define SOC_OTG_GINTSTS_RstrDoneInt_END     (16)
#define SOC_OTG_GINTSTS_IEPInt_START        (18)
#define SOC_OTG_GINTSTS_IEPInt_END          (18)
#define SOC_OTG_GINTSTS_OEPInt_START        (19)
#define SOC_OTG_GINTSTS_OEPInt_END          (19)
#define SOC_OTG_GINTSTS_incompISOIN_START   (20)
#define SOC_OTG_GINTSTS_incompISOIN_END     (20)
#define SOC_OTG_GINTSTS_incompISOOUT_START  (21)
#define SOC_OTG_GINTSTS_incompISOOUT_END    (21)
#define SOC_OTG_GINTSTS_FetSusp_START       (22)
#define SOC_OTG_GINTSTS_FetSusp_END         (22)
#define SOC_OTG_GINTSTS_ResetDet_START      (23)
#define SOC_OTG_GINTSTS_ResetDet_END        (23)
#define SOC_OTG_GINTSTS_HPrtInt_START       (24)
#define SOC_OTG_GINTSTS_HPrtInt_END         (24)
#define SOC_OTG_GINTSTS_HChInt_START        (25)
#define SOC_OTG_GINTSTS_HChInt_END          (25)
#define SOC_OTG_GINTSTS_PTxFEmp_START       (26)
#define SOC_OTG_GINTSTS_PTxFEmp_END         (26)
#define SOC_OTG_GINTSTS_LPM_Int_START       (27)
#define SOC_OTG_GINTSTS_LPM_Int_END         (27)
#define SOC_OTG_GINTSTS_ConIDStsChg_START   (28)
#define SOC_OTG_GINTSTS_ConIDStsChg_END     (28)
#define SOC_OTG_GINTSTS_DisconnInt_START    (29)
#define SOC_OTG_GINTSTS_DisconnInt_END      (29)
#define SOC_OTG_GINTSTS_SessReqInt_START    (30)
#define SOC_OTG_GINTSTS_SessReqInt_END      (30)
#define SOC_OTG_GINTSTS_WkUpInt_START       (31)
#define SOC_OTG_GINTSTS_WkUpInt_END         (31)


/*****************************************************************************
 结构名    : SOC_OTG_GINTMSK_UNION
 结构说明  : GINTMSK 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 全局中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved        : 1;  /* bit[0] : 保留。 */
        unsigned int  ModeMisMsk      : 1;  /* bit[1] : Mode Mismatch Interrupt Mask (ModeMisMsk) */
        unsigned int  OTGIntMsk       : 1;  /* bit[2] : OTG中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  SofMsk          : 1;  /* bit[3] : sof(Start Of microFrame)中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  RxFLvlMsk       : 1;  /* bit[4] : 接收FIFO非空中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  NPTxFEmpMsk     : 1;  /* bit[5] : 非周期发送FIFO空中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  GINNakEffMsk    : 1;  /* bit[6] : IN端点NAK有效中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  GOUTNakEffMsk   : 1;  /* bit[7] : OUT端点NAK有效中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  ULPICKINTMsk    : 1;  /* bit[8] : ULPI Carkit中断mask(ULPICKINTMsk) 
                                                        I2C Carkit中断mask (I2CCKINTMsk) */
        unsigned int  I2CIntMsk       : 1;  /* bit[9] : I2C中断mask */
        unsigned int  ErlySuspMsk     : 1;  /* bit[10]: Early suspend中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  USBSuspMsk      : 1;  /* bit[11]: suspend中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  USBRstMsk       : 1;  /* bit[12]: USB复位中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  EnumDoneMsk     : 1;  /* bit[13]: 枚举完成中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  ISOOutDropMsk   : 1;  /* bit[14]: Isochronous OUT包丢弃中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  EOPFMsk         : 1;  /* bit[15]: EOPF（End of Period Frame）中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  RstrDoneMsk     : 1;  /* bit[16]: 寄存器恢复中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  EPMisMsk        : 1;  /* bit[17]: Device only 
                                                        Endpoint Mismatch Interrupt Mask */
        unsigned int  IEPIntMsk       : 1;  /* bit[18]: IN端点中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  OEPIntMsk       : 1;  /* bit[19]: OUT端点中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  incompISOINMsk  : 1;  /* bit[20]: Isochronous IN传输未完成中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  incompISOOUTMsk : 1;  /* bit[21]: Isochronous OUT传输未完成中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  FetSuspMsk      : 1;  /* bit[22]: 取数挂起中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  ResetDetMsk     : 1;  /* bit[23]: 检测到复位中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  HPrtIntMsk      : 1;  /* bit[24]: Host端口中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  HChIntMsk       : 1;  /* bit[25]: Host通道中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  PTxFEmpMsk      : 1;  /* bit[26]: 周期发送FIFO空中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  LPM_IntMsk      : 1;  /* bit[27]: LPM接收中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  ConIDStsChngMsk : 1;  /* bit[28]: ID状态变化中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  DisconnIntMsk   : 1;  /* bit[29]: 断开连接中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  SessReqIntMsk   : 1;  /* bit[30]: 检测到会话请求中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  WkUpIntMsk      : 1;  /* bit[31]: Resume/Remote Wakwup中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
    } reg;
} SOC_OTG_GINTMSK_UNION;
#endif
#define SOC_OTG_GINTMSK_ModeMisMsk_START       (1)
#define SOC_OTG_GINTMSK_ModeMisMsk_END         (1)
#define SOC_OTG_GINTMSK_OTGIntMsk_START        (2)
#define SOC_OTG_GINTMSK_OTGIntMsk_END          (2)
#define SOC_OTG_GINTMSK_SofMsk_START           (3)
#define SOC_OTG_GINTMSK_SofMsk_END             (3)
#define SOC_OTG_GINTMSK_RxFLvlMsk_START        (4)
#define SOC_OTG_GINTMSK_RxFLvlMsk_END          (4)
#define SOC_OTG_GINTMSK_NPTxFEmpMsk_START      (5)
#define SOC_OTG_GINTMSK_NPTxFEmpMsk_END        (5)
#define SOC_OTG_GINTMSK_GINNakEffMsk_START     (6)
#define SOC_OTG_GINTMSK_GINNakEffMsk_END       (6)
#define SOC_OTG_GINTMSK_GOUTNakEffMsk_START    (7)
#define SOC_OTG_GINTMSK_GOUTNakEffMsk_END      (7)
#define SOC_OTG_GINTMSK_ULPICKINTMsk_START     (8)
#define SOC_OTG_GINTMSK_ULPICKINTMsk_END       (8)
#define SOC_OTG_GINTMSK_I2CIntMsk_START        (9)
#define SOC_OTG_GINTMSK_I2CIntMsk_END          (9)
#define SOC_OTG_GINTMSK_ErlySuspMsk_START      (10)
#define SOC_OTG_GINTMSK_ErlySuspMsk_END        (10)
#define SOC_OTG_GINTMSK_USBSuspMsk_START       (11)
#define SOC_OTG_GINTMSK_USBSuspMsk_END         (11)
#define SOC_OTG_GINTMSK_USBRstMsk_START        (12)
#define SOC_OTG_GINTMSK_USBRstMsk_END          (12)
#define SOC_OTG_GINTMSK_EnumDoneMsk_START      (13)
#define SOC_OTG_GINTMSK_EnumDoneMsk_END        (13)
#define SOC_OTG_GINTMSK_ISOOutDropMsk_START    (14)
#define SOC_OTG_GINTMSK_ISOOutDropMsk_END      (14)
#define SOC_OTG_GINTMSK_EOPFMsk_START          (15)
#define SOC_OTG_GINTMSK_EOPFMsk_END            (15)
#define SOC_OTG_GINTMSK_RstrDoneMsk_START      (16)
#define SOC_OTG_GINTMSK_RstrDoneMsk_END        (16)
#define SOC_OTG_GINTMSK_EPMisMsk_START         (17)
#define SOC_OTG_GINTMSK_EPMisMsk_END           (17)
#define SOC_OTG_GINTMSK_IEPIntMsk_START        (18)
#define SOC_OTG_GINTMSK_IEPIntMsk_END          (18)
#define SOC_OTG_GINTMSK_OEPIntMsk_START        (19)
#define SOC_OTG_GINTMSK_OEPIntMsk_END          (19)
#define SOC_OTG_GINTMSK_incompISOINMsk_START   (20)
#define SOC_OTG_GINTMSK_incompISOINMsk_END     (20)
#define SOC_OTG_GINTMSK_incompISOOUTMsk_START  (21)
#define SOC_OTG_GINTMSK_incompISOOUTMsk_END    (21)
#define SOC_OTG_GINTMSK_FetSuspMsk_START       (22)
#define SOC_OTG_GINTMSK_FetSuspMsk_END         (22)
#define SOC_OTG_GINTMSK_ResetDetMsk_START      (23)
#define SOC_OTG_GINTMSK_ResetDetMsk_END        (23)
#define SOC_OTG_GINTMSK_HPrtIntMsk_START       (24)
#define SOC_OTG_GINTMSK_HPrtIntMsk_END         (24)
#define SOC_OTG_GINTMSK_HChIntMsk_START        (25)
#define SOC_OTG_GINTMSK_HChIntMsk_END          (25)
#define SOC_OTG_GINTMSK_PTxFEmpMsk_START       (26)
#define SOC_OTG_GINTMSK_PTxFEmpMsk_END         (26)
#define SOC_OTG_GINTMSK_LPM_IntMsk_START       (27)
#define SOC_OTG_GINTMSK_LPM_IntMsk_END         (27)
#define SOC_OTG_GINTMSK_ConIDStsChngMsk_START  (28)
#define SOC_OTG_GINTMSK_ConIDStsChngMsk_END    (28)
#define SOC_OTG_GINTMSK_DisconnIntMsk_START    (29)
#define SOC_OTG_GINTMSK_DisconnIntMsk_END      (29)
#define SOC_OTG_GINTMSK_SessReqIntMsk_START    (30)
#define SOC_OTG_GINTMSK_SessReqIntMsk_END      (30)
#define SOC_OTG_GINTMSK_WkUpIntMsk_START       (31)
#define SOC_OTG_GINTMSK_WkUpIntMsk_END         (31)


/*****************************************************************************
 结构名    : SOC_OTG_GRXSTSR_UNION
 结构说明  : GRXSTSR 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 全局接收FIFO状态读出寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ChNum    : 4;  /* bit[0-3]  : Channel Number */
        unsigned int  BCnt     : 11; /* bit[4-14] : 数据包大小，以字节为单位。 */
        unsigned int  DPID     : 2;  /* bit[15-16]: 数据包PID。
                                                    00：DATA0；
                                                    10：DATA1；
                                                    01：DATA2；
                                                    11：MDATA。 */
        unsigned int  PktSts   : 4;  /* bit[17-20]: 包状态。指示接收到的数据包状态。
                                                    Host模式下：
                                                    0010：接收到IN数据包；
                                                    0011：IN传输完成；
                                                    0101：数据包PID翻转错误；
                                                    0111：通道停止；
                                                    others：reserved。
                                                    Device模式下：
                                                    0001：OUT NAK；
                                                    0010：接收到OUT数据包；
                                                    0011：OUT传输完成；
                                                    0100：Setup事务完成；
                                                    0110：接收到Setup包；
                                                    others：reserved。 */
        unsigned int  reserved : 11; /* bit[21-31]: 保留。 */
    } reg;
} SOC_OTG_GRXSTSR_UNION;
#endif
#define SOC_OTG_GRXSTSR_ChNum_START     (0)
#define SOC_OTG_GRXSTSR_ChNum_END       (3)
#define SOC_OTG_GRXSTSR_BCnt_START      (4)
#define SOC_OTG_GRXSTSR_BCnt_END        (14)
#define SOC_OTG_GRXSTSR_DPID_START      (15)
#define SOC_OTG_GRXSTSR_DPID_END        (16)
#define SOC_OTG_GRXSTSR_PktSts_START    (17)
#define SOC_OTG_GRXSTSR_PktSts_END      (20)


/*****************************************************************************
 结构名    : SOC_OTG_GRXSTSP_UNION
 结构说明  : GRXSTSP 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 全局接收FIFO状态弹出寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EPNum    : 4;  /* bit[0-3]  : Host模式下指示通道号，device模式下指示端点号。 */
        unsigned int  BCnt     : 11; /* bit[4-14] : 数据包大小，以字节为单位。 */
        unsigned int  DPID     : 2;  /* bit[15-16]: 数据包PID。
                                                    00：DATA0；
                                                    10：DATA1；
                                                    01：DATA2；
                                                    11：MDATA。 */
        unsigned int  PktSts   : 4;  /* bit[17-20]: 包状态。指示接收到的数据包状态。
                                                    Host模式下：
                                                    0010：接收到IN数据包；
                                                    0011：IN传输完成；
                                                    0101：数据包PID翻转错误；
                                                    0111：通道停止；
                                                    others：reserved。
                                                    Device模式下：
                                                    0001：OUT NAK；
                                                    0010：接收到OUT数据包；
                                                    0011：OUT传输完成；
                                                    0100：Setup事务完成；
                                                    0110：接收到Setup包；
                                                    others：reserved。 */
        unsigned int  FN       : 4;  /* bit[21-24]: Host模式下，该域保留。
                                                    Device模式下，帧序号。指示帧序号的低4位。读该寄存器返回接收FIFO数据状态，同时弹出接收FIFO数据。 */
        unsigned int  reserved : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_OTG_GRXSTSP_UNION;
#endif
#define SOC_OTG_GRXSTSP_EPNum_START     (0)
#define SOC_OTG_GRXSTSP_EPNum_END       (3)
#define SOC_OTG_GRXSTSP_BCnt_START      (4)
#define SOC_OTG_GRXSTSP_BCnt_END        (14)
#define SOC_OTG_GRXSTSP_DPID_START      (15)
#define SOC_OTG_GRXSTSP_DPID_END        (16)
#define SOC_OTG_GRXSTSP_PktSts_START    (17)
#define SOC_OTG_GRXSTSP_PktSts_END      (20)
#define SOC_OTG_GRXSTSP_FN_START        (21)
#define SOC_OTG_GRXSTSP_FN_END          (24)


/*****************************************************************************
 结构名    : SOC_OTG_GRXFSIZ_UNION
 结构说明  : GRXFSIZ 寄存器结构定义。地址偏移量:0x0024，初值:0x00001000，宽度:32
 寄存器说明: 全局接收FIFO大小寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RxFDep   : 16; /* bit[0-15] : 接收FIFO深度。以4字节为单位。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_GRXFSIZ_UNION;
#endif
#define SOC_OTG_GRXFSIZ_RxFDep_START    (0)
#define SOC_OTG_GRXFSIZ_RxFDep_END      (15)


/*****************************************************************************
 结构名    : SOC_OTG_GNPTXFSIZ_UNION
 结构说明  : GNPTXFSIZ 寄存器结构定义。地址偏移量:0x0028，初值:0x10001000，宽度:32
 寄存器说明: 全局非周期发送FIFO大小寄存器。 (Host Mode and Device Shared FIFO Mode)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  NPTxFStAddr : 16; /* bit[0-15] : 给周期发送FIFO起始地址。以4字节为单位。 */
        unsigned int  NPTxFDep    : 16; /* bit[16-31]: 非周期发送FIFO深度。以4字节为单位。 */
    } reg;
} SOC_OTG_GNPTXFSIZ_UNION;
#endif
#define SOC_OTG_GNPTXFSIZ_NPTxFStAddr_START  (0)
#define SOC_OTG_GNPTXFSIZ_NPTxFStAddr_END    (15)
#define SOC_OTG_GNPTXFSIZ_NPTxFDep_START     (16)
#define SOC_OTG_GNPTXFSIZ_NPTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_GNPTXSTS_UNION
 结构说明  : GNPTXSTS 寄存器结构定义。地址偏移量:0x002C，初值:0x00081000，宽度:32
 寄存器说明: 全局非周期发送FIFO状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  NPTxFSpcAvail : 16; /* bit[0-15] : 非周期发送FIFO剩余空间。以4字节为单位。 */
        unsigned int  NPTxQSpcAvail : 8;  /* bit[16-23]: 非周期发送请求队列剩余空间。
                                                         非周期发送请求队列深度为8，该域指示发送请求队列还可以缓存几个发送请求。 */
        unsigned int  NPTxQTop      : 7;  /* bit[24-30]: 等待处理的非周期发送请求。
                                                         Bit[30:27]:通道号；
                                                         Bit[26:25]
                                                         00：OUT令牌；
                                                         01：零长包；
                                                         10：PING/CSPLIT令牌；
                                                         11：通道停止命令。
                                                         Bit[24]:结束标志，指示该请求为当前通道的最后一个请求。 */
        unsigned int  reserved      : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_OTG_GNPTXSTS_UNION;
#endif
#define SOC_OTG_GNPTXSTS_NPTxFSpcAvail_START  (0)
#define SOC_OTG_GNPTXSTS_NPTxFSpcAvail_END    (15)
#define SOC_OTG_GNPTXSTS_NPTxQSpcAvail_START  (16)
#define SOC_OTG_GNPTXSTS_NPTxQSpcAvail_END    (23)
#define SOC_OTG_GNPTXSTS_NPTxQTop_START       (24)
#define SOC_OTG_GNPTXSTS_NPTxQTop_END         (30)


/*****************************************************************************
 结构名    : SOC_OTG_GSNPSID_UNION
 结构说明  : GSNPSID 寄存器结构定义。地址偏移量:0x0040，初值:0x4F54310A，宽度:32
 寄存器说明: USB IP版本寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  UserID : 32; /* bit[0-31]: USB IP版本寄存器。版本为3.10a。 */
    } reg;
} SOC_OTG_GSNPSID_UNION;
#endif
#define SOC_OTG_GSNPSID_UserID_START  (0)
#define SOC_OTG_GSNPSID_UserID_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_GHWCFG1_UNION
 结构说明  : GHWCFG1 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 硬件配置寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  epdir : 32; /* bit[0-31]: 端点方向寄存器。
                                                Bit[31:30]：端点15方向；
                                                bit[29:28]：端点14方向；
                                                ……
                                                bit[1:0]：端点0方向。
                                                各个端点值：
                                                00：双向端点；
                                                01：IN端点；
                                                10：OUT端点；
                                                11：保留。 */
    } reg;
} SOC_OTG_GHWCFG1_UNION;
#endif
#define SOC_OTG_GHWCFG1_epdir_START  (0)
#define SOC_OTG_GHWCFG1_epdir_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_GHWCFG2_UNION
 结构说明  : GHWCFG2 寄存器结构定义。地址偏移量:0x0048，初值:0x22ACFC50，宽度:32
 寄存器说明: 硬件配置寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  OtgMode         : 3;  /* bit[0-2]  : OTG模式。
                                                           000：HNP和SRP使能OTG,可作host和device；
                                                           001：SRP使能OTG,可作host和device；
                                                           010：HNP和SRP不使能OTG,可作host和device；
                                                           011：SRP使能device；
                                                           100：非OTG device；
                                                           101：SRP使能host；
                                                           110：非OTG host；
                                                           111：保留。 */
        unsigned int  OtgArch         : 2;  /* bit[3-4]  : DMA模式配置。
                                                           00：非DMA模式，只有1个AHB slave接口；
                                                           01：外部DMA；
                                                           10：内部DMA
                                                           11：保留。 */
        unsigned int  SingPnt         : 1;  /* bit[5]    : Point-to-Potint模式使能。该配置仅针对host有效。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  HSPhyType       : 2;  /* bit[6-7]  : 高速PHY接口类型选择。
                                                           00：不支持高速模式；
                                                           01：UTMI+；
                                                           10：ULPI；
                                                           11：UTMI+和ULPI都支持，软件可配置。 */
        unsigned int  FSPhyType       : 2;  /* bit[8-9]  : 全速PHY接口类型。
                                                           00：不支持全速PHY接口；
                                                           01：专有全速接口；
                                                           10：全速管脚与UTMI+管脚复用；
                                                           11：全速管脚与ULPI管脚复用。 */
        unsigned int  NumDevEps       : 4;  /* bit[10-13]: 除端点0之外支持的端点数目，范围为1~15。 */
        unsigned int  NumHstChnl      : 4;  /* bit[14-17]: Host通道数目。仅支持host有效。 */
        unsigned int  PerioSupport    : 1;  /* bit[18]   : Host模式时，是否支持周期OUT通道。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  DynFifoSizing   : 1;  /* bit[19]   : 是否支持FIFO大小动态配置。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  MultiProcIntrpt : 1;  /* bit[20]   : 是否支持多中断上报。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  reserved        : 1;  /* bit[21]   : 保留。 */
        unsigned int  NPTxQDepth      : 2;  /* bit[22-23]: 非周期请求队列深度。
                                                           00：2；
                                                           01：4；
                                                           10：8；
                                                           others：reserved。 */
        unsigned int  PTxQDepth       : 2;  /* bit[24-25]: host模式时，周期请求队列深度。
                                                           00：2；
                                                           01：4；
                                                           10：8；
                                                           others：reserved。 */
        unsigned int  TknQDepth       : 5;  /* bit[26-30]: device模式时，IN令牌序列深度。 */
        unsigned int  OTG_IC_USB      : 1;  /* bit[31]   : 是否支持IC_USB模式。
                                                           0：不支持；
                                                           1：支持。 */
    } reg;
} SOC_OTG_GHWCFG2_UNION;
#endif
#define SOC_OTG_GHWCFG2_OtgMode_START          (0)
#define SOC_OTG_GHWCFG2_OtgMode_END            (2)
#define SOC_OTG_GHWCFG2_OtgArch_START          (3)
#define SOC_OTG_GHWCFG2_OtgArch_END            (4)
#define SOC_OTG_GHWCFG2_SingPnt_START          (5)
#define SOC_OTG_GHWCFG2_SingPnt_END            (5)
#define SOC_OTG_GHWCFG2_HSPhyType_START        (6)
#define SOC_OTG_GHWCFG2_HSPhyType_END          (7)
#define SOC_OTG_GHWCFG2_FSPhyType_START        (8)
#define SOC_OTG_GHWCFG2_FSPhyType_END          (9)
#define SOC_OTG_GHWCFG2_NumDevEps_START        (10)
#define SOC_OTG_GHWCFG2_NumDevEps_END          (13)
#define SOC_OTG_GHWCFG2_NumHstChnl_START       (14)
#define SOC_OTG_GHWCFG2_NumHstChnl_END         (17)
#define SOC_OTG_GHWCFG2_PerioSupport_START     (18)
#define SOC_OTG_GHWCFG2_PerioSupport_END       (18)
#define SOC_OTG_GHWCFG2_DynFifoSizing_START    (19)
#define SOC_OTG_GHWCFG2_DynFifoSizing_END      (19)
#define SOC_OTG_GHWCFG2_MultiProcIntrpt_START  (20)
#define SOC_OTG_GHWCFG2_MultiProcIntrpt_END    (20)
#define SOC_OTG_GHWCFG2_NPTxQDepth_START       (22)
#define SOC_OTG_GHWCFG2_NPTxQDepth_END         (23)
#define SOC_OTG_GHWCFG2_PTxQDepth_START        (24)
#define SOC_OTG_GHWCFG2_PTxQDepth_END          (25)
#define SOC_OTG_GHWCFG2_TknQDepth_START        (26)
#define SOC_OTG_GHWCFG2_TknQDepth_END          (30)
#define SOC_OTG_GHWCFG2_OTG_IC_USB_START       (31)
#define SOC_OTG_GHWCFG2_OTG_IC_USB_END         (31)


/*****************************************************************************
 结构名    : SOC_OTG_GHWCFG3_UNION
 结构说明  : GHWCFG3 寄存器结构定义。地址偏移量:0x004C，初值:0x0F80D4E8，宽度:32
 寄存器说明: 硬件配置寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSizeWidth   : 4;  /* bit[0-3]  : 传输大小记数器宽度。
                                                           0000：11bit；
                                                           0001：12bit；
                                                           ……
                                                           1000：19bit；
                                                           others：reserved。 */
        unsigned int  PktSizeWidth    : 3;  /* bit[4-6]  : 包大小记数器宽度。
                                                           000：4bit；
                                                           001：5bit；
                                                           010：6bit；
                                                           011：7bit；
                                                           100：8bit；
                                                           101：9bit；
                                                           110：10bit；
                                                           others：reserved。 */
        unsigned int  OtgEn           : 1;  /* bit[7]    : 是否使能OTG功能。该bit由OTG_MODE参数决定，当OTG_MODE配置为0，1或2时，OtgEn=1。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  I2CIntSel       : 1;  /* bit[8]    : 是否支持I2C接口。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  VndctlSupt      : 1;  /* bit[9]    : 是否支持Vendor Control接口。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  OptFeature      : 1;  /* bit[10]   : 是否支持取下列特性：User ID寄存器，GPIO接口，SOF翻转信号和记数器接口。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  RstType         : 1;  /* bit[11]   : 在always语句中，复位的类型。
                                                           0：异步复位；
                                                           1：同步复位。 */
        unsigned int  OTG_ADP_SUPPORT : 1;  /* bit[12]   : 是否支持ADP。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  OTG_ENABLE_HSIC : 1;  /* bit[13]   : 是否支持HSIC。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  OTG_BC_SUPPORT  : 1;  /* bit[14]   : 是否支持BC。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  OTG_ENABLE_LPM  : 1;  /* bit[15]   : 是否支持LPM。
                                                           0：不支持；
                                                           1：支持。 */
        unsigned int  DfifoDepth      : 16; /* bit[16-31]: 数据FIFO的深度，以4字节为单位。发送FIFO和接收FIFO大小之和不能大于该值。 */
    } reg;
} SOC_OTG_GHWCFG3_UNION;
#endif
#define SOC_OTG_GHWCFG3_XferSizeWidth_START    (0)
#define SOC_OTG_GHWCFG3_XferSizeWidth_END      (3)
#define SOC_OTG_GHWCFG3_PktSizeWidth_START     (4)
#define SOC_OTG_GHWCFG3_PktSizeWidth_END       (6)
#define SOC_OTG_GHWCFG3_OtgEn_START            (7)
#define SOC_OTG_GHWCFG3_OtgEn_END              (7)
#define SOC_OTG_GHWCFG3_I2CIntSel_START        (8)
#define SOC_OTG_GHWCFG3_I2CIntSel_END          (8)
#define SOC_OTG_GHWCFG3_VndctlSupt_START       (9)
#define SOC_OTG_GHWCFG3_VndctlSupt_END         (9)
#define SOC_OTG_GHWCFG3_OptFeature_START       (10)
#define SOC_OTG_GHWCFG3_OptFeature_END         (10)
#define SOC_OTG_GHWCFG3_RstType_START          (11)
#define SOC_OTG_GHWCFG3_RstType_END            (11)
#define SOC_OTG_GHWCFG3_OTG_ADP_SUPPORT_START  (12)
#define SOC_OTG_GHWCFG3_OTG_ADP_SUPPORT_END    (12)
#define SOC_OTG_GHWCFG3_OTG_ENABLE_HSIC_START  (13)
#define SOC_OTG_GHWCFG3_OTG_ENABLE_HSIC_END    (13)
#define SOC_OTG_GHWCFG3_OTG_BC_SUPPORT_START   (14)
#define SOC_OTG_GHWCFG3_OTG_BC_SUPPORT_END     (14)
#define SOC_OTG_GHWCFG3_OTG_ENABLE_LPM_START   (15)
#define SOC_OTG_GHWCFG3_OTG_ENABLE_LPM_END     (15)
#define SOC_OTG_GHWCFG3_DfifoDepth_START       (16)
#define SOC_OTG_GHWCFG3_DfifoDepth_END         (31)


/*****************************************************************************
 结构名    : SOC_OTG_GHWCFG4_UNION
 结构说明  : GHWCFG4 寄存器结构定义。地址偏移量:0x0050，初值:0xFFF08060，宽度:32
 寄存器说明: 硬件配置寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  NumDevEps          : 4;  /* bit[0-3]  : 支持周期IN端点个数。该域仅当DedFifoMode＝0时有效。 */
        unsigned int  EnablePwrOpt       : 1;  /* bit[4]    : 是否使能功耗优化。使能功耗优化，USB模块分成掉电域和不掉电域，并且加入时钟门控逻辑。
                                                              0：不使能；
                                                              1：使能。 */
        unsigned int  AhbFreq            : 1;  /* bit[5]    : 最小AHB频率是否小于60MHz。
                                                              0：不是；
                                                              1：是。 */
        unsigned int  Hibernation        : 1;  /* bit[6]    : 使能Hibernation。
                                                              0： Hibernation feature不使能
                                                              1： Hibernation feature使能 */
        unsigned int  ExtndedHibernation : 1;  /* bit[7]    : 外部 Hibernation 使能
                                                              0： Hibernation feature不使能
                                                              1： Hibernation feature使能 */
        unsigned int  reserved_0         : 6;  /* bit[8-13] : 保留。 */
        unsigned int  PhyDataWidth       : 2;  /* bit[14-15]: PHY数据线宽度。
                                                              00：8bit；
                                                              01：16bit；
                                                              10：软件可配置为8bit或者16bit；
                                                              others：reserved。 */
        unsigned int  NumCtlEps          : 4;  /* bit[16-19]: 除了端点0之外支持的控制端点数目。 */
        unsigned int  IddigFltr          : 1;  /* bit[20]   : 是否支持信号iddig滤毛刺。
                                                              0：不支持；
                                                              1：支持。 */
        unsigned int  VBusValidFltr      : 1;  /* bit[21]   : 是否支持信号vbus_valid滤毛刺。
                                                              0：不支持；
                                                              1：支持。 */
        unsigned int  AValidFltr         : 1;  /* bit[22]   : 是否支持信号avalid滤毛刺。
                                                              0：不支持；
                                                              1：支持。 */
        unsigned int  BValidFltr         : 1;  /* bit[23]   : 是否支持信号bvalid滤毛刺。
                                                              0：不支持；
                                                              1：支持。 */
        unsigned int  SessEndFltr        : 1;  /* bit[24]   : 是否支持信号session_end滤毛刺。
                                                              0：不支持；
                                                              1：支持。 */
        unsigned int  DedFifoMode        : 1;  /* bit[25]   : 是否支持IN端点专有发送FIFO功能。
                                                              0：不支持；
                                                              1：支持。 */
        unsigned int  INEps              : 4;  /* bit[26-29]: 包括控制端点在内，IN端点的数目。
                                                              0000：1个；
                                                              0001：2个；
                                                              ……
                                                              1111：16个。 */
        unsigned int  SGDMA              : 1;  /* bit[30]   : 是否支持Scatter/Gather DMA。
                                                              0：不支持；
                                                              1：支持。 */
        unsigned int  reserved_1         : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_OTG_GHWCFG4_UNION;
#endif
#define SOC_OTG_GHWCFG4_NumDevEps_START           (0)
#define SOC_OTG_GHWCFG4_NumDevEps_END             (3)
#define SOC_OTG_GHWCFG4_EnablePwrOpt_START        (4)
#define SOC_OTG_GHWCFG4_EnablePwrOpt_END          (4)
#define SOC_OTG_GHWCFG4_AhbFreq_START             (5)
#define SOC_OTG_GHWCFG4_AhbFreq_END               (5)
#define SOC_OTG_GHWCFG4_Hibernation_START         (6)
#define SOC_OTG_GHWCFG4_Hibernation_END           (6)
#define SOC_OTG_GHWCFG4_ExtndedHibernation_START  (7)
#define SOC_OTG_GHWCFG4_ExtndedHibernation_END    (7)
#define SOC_OTG_GHWCFG4_PhyDataWidth_START        (14)
#define SOC_OTG_GHWCFG4_PhyDataWidth_END          (15)
#define SOC_OTG_GHWCFG4_NumCtlEps_START           (16)
#define SOC_OTG_GHWCFG4_NumCtlEps_END             (19)
#define SOC_OTG_GHWCFG4_IddigFltr_START           (20)
#define SOC_OTG_GHWCFG4_IddigFltr_END             (20)
#define SOC_OTG_GHWCFG4_VBusValidFltr_START       (21)
#define SOC_OTG_GHWCFG4_VBusValidFltr_END         (21)
#define SOC_OTG_GHWCFG4_AValidFltr_START          (22)
#define SOC_OTG_GHWCFG4_AValidFltr_END            (22)
#define SOC_OTG_GHWCFG4_BValidFltr_START          (23)
#define SOC_OTG_GHWCFG4_BValidFltr_END            (23)
#define SOC_OTG_GHWCFG4_SessEndFltr_START         (24)
#define SOC_OTG_GHWCFG4_SessEndFltr_END           (24)
#define SOC_OTG_GHWCFG4_DedFifoMode_START         (25)
#define SOC_OTG_GHWCFG4_DedFifoMode_END           (25)
#define SOC_OTG_GHWCFG4_INEps_START               (26)
#define SOC_OTG_GHWCFG4_INEps_END                 (29)
#define SOC_OTG_GHWCFG4_SGDMA_START               (30)
#define SOC_OTG_GHWCFG4_SGDMA_END                 (30)


/*****************************************************************************
 结构名    : SOC_OTG_GLPMCFG_UNION
 结构说明  : GLPMCFG 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: LPM配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LPMCap           : 1;  /* bit[0]    : LPM使能。
                                                            0：不使能；
                                                            1：使能。 */
        unsigned int  APPL1Res         : 1;  /* bit[1]    : LPM响应配置，仅对device模式有效。且LPM必须使能。如果LPM不使能，则一直返回NYET。
                                                            0：NYET；
                                                            1：ACK。 */
        unsigned int  HIRD             : 4;  /* bit[2-5]  : Resume保持时间。
                                                            对于host模式，该域可读写。软件配置为LPM包传输的HIRD值。
                                                            对于device模式，该域只读。收到LPM包之后控制器更新该域。
                                                            0000：50us；
                                                            0001：125us；
                                                            0010：250us；
                                                            0011：275us；
                                                            0100：350us；
                                                            0101：425us；
                                                            0110：500us；
                                                            0111：575us；
                                                            1000：650us；
                                                            1001：725us；
                                                            1010：800us；
                                                            1011：875us；
                                                            1100：950us；
                                                            1101：1025us；
                                                            1110：1100us；
                                                            1111：1175us。 */
        unsigned int  bRemoteWake      : 1;  /* bit[6]    : 远程唤醒使能。当device收到bRemoteWake LPM包时，该域更新。
                                                            0：不使能；
                                                            1：使能。 */
        unsigned int  EnblSlpM         : 1;  /* bit[7]    : 使能utmi_sleep_n。当的处于L1状态时，软件设置该bit，使utmi_sleep_n信号置为有效。
                                                            0：不使能；
                                                            1：使能。 */
        unsigned int  HIRD_Thres       : 5;  /* bit[8-12] : HIRD水线。最高bit为使能位，低4bit为水线值。
                                                            对于device模式，当HIRD时间超过水线值时，控制器置位SuspendM信号使PHY进入低功耗模式。
                                                            0000：60us；
                                                            0001：135us；
                                                            0010：210us；
                                                            0011：285us；
                                                            0100：360us；
                                                            0101：435us；
                                                            0110：510us；
                                                            0111：585us；
                                                            1000：660us；
                                                            1001：735us；
                                                            1010：810us；
                                                            1011：885us；
                                                            1100：960us；
                                                            others：reserved。 */
        unsigned int  CoreL1Res        : 2;  /* bit[13-14]: LPM响应。
                                                            对于host模式，指示接收到的握手包；对于device模式，接收到LPM包之后按照该域发送握手包。
                                                            00：ERROR；
                                                            01：STALL；
                                                            10：NYET；
                                                            11：ACK。 */
        unsigned int  SlpSts           : 1;  /* bit[15]   : sleep状态指示。
                                                            0：没有进入sleep状态；
                                                            1：进入sleep状态。 */
        unsigned int  L1ResumeOk       : 1;  /* bit[16]   : 指示是否可以从sleep状态唤醒。进入sleep状态50us之后，该比特置位。
                                                            0：不可以从sleep状态唤醒；
                                                            1：可以从sleep状态唤醒。 */
        unsigned int  LPM_Chnl_Index   : 4;  /* bit[17-20]: 发送LPM的通道号，对host模式有效。 */
        unsigned int  LPM_Retry_Cnt    : 3;  /* bit[21-23]: LPM Retry次数配置，对host模式有效。指示收到有效的响应之前，host可以重新发送LPM的次数。 */
        unsigned int  SndLPM           : 1;  /* bit[24]   : 发送LPM事务，对host模式有效。
                                                            软件配置该bit，控制发送扩展令牌包和LPM令牌包。接收到有效的响应(STALL，NYET或者ACK)之后，硬件清除该bit。
                                                            0：不使能；
                                                            1：使能。 */
        unsigned int  LPM_RetryCnt_Sts : 3;  /* bit[25-27]: LPM retry状态，对host模式有效。指示当前LPM序列剩余的retry数。 */
        unsigned int  EnBESL           : 1;  /* bit[28]   : 最优latency使能 */
        unsigned int  RstrSlpSts       : 1;  /* bit[29]   : Device only Restore SlpSts (RstrSlpSts)
                                                            0： in Shallow Sleep mode 
                                                            1： in Deep Sleep mode */
        unsigned int  HSICCon          : 1;  /* bit[30]   : host模式：驱动HSIC总线为IDLE
                                                            device模式：等待HSIC总线为IDLE */
        unsigned int  InvSelHsic       : 1;  /* bit[31]   : HSIC-Invert Select HSIC
                                                            如if_sel_hsic输入1:
                                                            1：HSIC capability不使能
                                                            0：HSIC capability使能
                                                            如if_sel_hsic输入0:
                                                            1：HSIC capability使能
                                                            0：HSIC capability不使能 */
    } reg;
} SOC_OTG_GLPMCFG_UNION;
#endif
#define SOC_OTG_GLPMCFG_LPMCap_START            (0)
#define SOC_OTG_GLPMCFG_LPMCap_END              (0)
#define SOC_OTG_GLPMCFG_APPL1Res_START          (1)
#define SOC_OTG_GLPMCFG_APPL1Res_END            (1)
#define SOC_OTG_GLPMCFG_HIRD_START              (2)
#define SOC_OTG_GLPMCFG_HIRD_END                (5)
#define SOC_OTG_GLPMCFG_bRemoteWake_START       (6)
#define SOC_OTG_GLPMCFG_bRemoteWake_END         (6)
#define SOC_OTG_GLPMCFG_EnblSlpM_START          (7)
#define SOC_OTG_GLPMCFG_EnblSlpM_END            (7)
#define SOC_OTG_GLPMCFG_HIRD_Thres_START        (8)
#define SOC_OTG_GLPMCFG_HIRD_Thres_END          (12)
#define SOC_OTG_GLPMCFG_CoreL1Res_START         (13)
#define SOC_OTG_GLPMCFG_CoreL1Res_END           (14)
#define SOC_OTG_GLPMCFG_SlpSts_START            (15)
#define SOC_OTG_GLPMCFG_SlpSts_END              (15)
#define SOC_OTG_GLPMCFG_L1ResumeOk_START        (16)
#define SOC_OTG_GLPMCFG_L1ResumeOk_END          (16)
#define SOC_OTG_GLPMCFG_LPM_Chnl_Index_START    (17)
#define SOC_OTG_GLPMCFG_LPM_Chnl_Index_END      (20)
#define SOC_OTG_GLPMCFG_LPM_Retry_Cnt_START     (21)
#define SOC_OTG_GLPMCFG_LPM_Retry_Cnt_END       (23)
#define SOC_OTG_GLPMCFG_SndLPM_START            (24)
#define SOC_OTG_GLPMCFG_SndLPM_END              (24)
#define SOC_OTG_GLPMCFG_LPM_RetryCnt_Sts_START  (25)
#define SOC_OTG_GLPMCFG_LPM_RetryCnt_Sts_END    (27)
#define SOC_OTG_GLPMCFG_EnBESL_START            (28)
#define SOC_OTG_GLPMCFG_EnBESL_END              (28)
#define SOC_OTG_GLPMCFG_RstrSlpSts_START        (29)
#define SOC_OTG_GLPMCFG_RstrSlpSts_END          (29)
#define SOC_OTG_GLPMCFG_HSICCon_START           (30)
#define SOC_OTG_GLPMCFG_HSICCon_END             (30)
#define SOC_OTG_GLPMCFG_InvSelHsic_START        (31)
#define SOC_OTG_GLPMCFG_InvSelHsic_END          (31)


/*****************************************************************************
 结构名    : SOC_OTG_GPWRDN_UNION
 结构说明  : GPWRDN 寄存器结构定义。地址偏移量:0x0058，初值:0x00200010，宽度:32
 寄存器说明: 冬眠模式掉电控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PMUIntSel           : 1;  /* bit[0]    : PMU中断选择。该bit配置为1，将PMU产生的中断上报，控制器产生的中断屏蔽。
                                                               0：选择控制器产生的中断；
                                                               1：选择PMU产生的中断。 */
        unsigned int  PMUActv             : 1;  /* bit[1]    : 使能PMU功能。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  Restore             : 1;  /* bit[2]    : 寄存器恢复控制。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  PwrDnClmp           : 1;  /* bit[3]    : 掉电箝位控制。软件配置该bit是控制器输出的信号固定在确定的状态。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  PwrDnRst_n          : 1;  /* bit[4]    : 掉电复位控制。在退出冬眠模式或者ADP上电之前，软件必须配置该bit对控制器进行复位。
                                                               0：复位控制器；
                                                               1：不复位控制器。 */
        unsigned int  PwrDnSwtch          : 1;  /* bit[5]    : 掉电开关。指示控制器电源关断状态。
                                                               0：ON；
                                                               1：OFF。
                                                               在正常操作状态下不能配置该bit。 */
        unsigned int  VbusOff             : 1;  /* bit[6]    : 在Host模式下，在进入冬眠模式之前：
                                                               0：HPRT[PrtPwr]配置没有配置为0；
                                                               1：HPRT[Prtpwr]配置为0。
                                                               在Device模式下，在对控制器掉电之前：
                                                               0：bvalid有效；
                                                               1：bvalid无效。
                                                               该bit仅当PMUActv＝1有效。 */
        unsigned int  LnStsChng           : 1;  /* bit[7]    : 检测LineState变化中断。
                                                               0：无中断；
                                                               1：中断。 */
        unsigned int  LnStsChngMsk        : 1;  /* bit[8]    : LnStsChng中断屏蔽位。
                                                               0：屏蔽；
                                                               1：不屏蔽。 */
        unsigned int  ResetDetected       : 1;  /* bit[9]    : 检测到复位操作中断，对device模式有效。
                                                               0：无中断；
                                                               1：有中断。 */
        unsigned int  ResetDetMsk         : 1;  /* bit[10]   : ResetDetcted中断屏蔽位，对device模式有效。
                                                               0：屏蔽；
                                                               1：不屏蔽。 */
        unsigned int  DisconnectDetect    : 1;  /* bit[11]   : 断开连接中断，对host模式有效。
                                                               0：无中断；
                                                               1：有中断。 */
        unsigned int  DisconnectDetectMsk : 1;  /* bit[12]   : DisconnectDetect中断屏蔽位。对host模式有效。
                                                               0：屏蔽；
                                                               1：不屏蔽。 */
        unsigned int  ConnectDet          : 1;  /* bit[13]   : 检测到连接中断。
                                                               0：无中断；
                                                               1：有中断。 */
        unsigned int  ConnDetMsk          : 1;  /* bit[14]   : ConnectDet中断屏蔽位。
                                                               0：屏蔽；
                                                               1：不屏蔽。 */
        unsigned int  SRPDetect           : 1;  /* bit[15]   : 检测到SRP中断。对host模式有效。
                                                               0：有中断；
                                                               1：无中断。 */
        unsigned int  SRPDetectMsk        : 1;  /* bit[16]   : SRPDetect中断屏蔽位。对host模式有效。
                                                               0：不屏蔽；
                                                               1：屏蔽。 */
        unsigned int  StsChngInt          : 1;  /* bit[17]   : StsChng中断。指示IDDIG或者bvalid状态变化。
                                                               0：无中断；
                                                               1：有中断。 */
        unsigned int  StsChngMsk          : 1;  /* bit[18]   : StsChng中断屏蔽位。
                                                               0：屏蔽；
                                                               1：不屏蔽。 */
        unsigned int  LineState           : 2;  /* bit[19-20]: 当前linestate。
                                                               00：DM=0，DP=0；
                                                               01：DM=0，DP=1；
                                                               10：DM=1，DP=0；
                                                               11：reserved。 */
        unsigned int  IDDIG               : 1;  /* bit[21]   : IDDIG状态。当PMUActv＝1有效。
                                                               0：低电平；
                                                               1：高电平。 */
        unsigned int  BSessVld            : 1;  /* bit[22]   : bvalid有效状态。当PMUActv＝1有效。
                                                               0：无效；
                                                               1：有效。 */
        unsigned int  ADPInt              : 1;  /* bit[23]   : ADP中断状态。
                                                               0：无中断；
                                                               1：有中断。 */
        unsigned int  MultValIdBc         : 5;  /* bit[24-28]: ACA输入ID状态。
                                                               00001：rid_c；
                                                               00010：rid_b；
                                                               00100：rid_a；
                                                               01000：rid_gnd；
                                                               10000：rid_float；
                                                               others：reserved。 */
        unsigned int  reserved            : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_OTG_GPWRDN_UNION;
#endif
#define SOC_OTG_GPWRDN_PMUIntSel_START            (0)
#define SOC_OTG_GPWRDN_PMUIntSel_END              (0)
#define SOC_OTG_GPWRDN_PMUActv_START              (1)
#define SOC_OTG_GPWRDN_PMUActv_END                (1)
#define SOC_OTG_GPWRDN_Restore_START              (2)
#define SOC_OTG_GPWRDN_Restore_END                (2)
#define SOC_OTG_GPWRDN_PwrDnClmp_START            (3)
#define SOC_OTG_GPWRDN_PwrDnClmp_END              (3)
#define SOC_OTG_GPWRDN_PwrDnRst_n_START           (4)
#define SOC_OTG_GPWRDN_PwrDnRst_n_END             (4)
#define SOC_OTG_GPWRDN_PwrDnSwtch_START           (5)
#define SOC_OTG_GPWRDN_PwrDnSwtch_END             (5)
#define SOC_OTG_GPWRDN_VbusOff_START              (6)
#define SOC_OTG_GPWRDN_VbusOff_END                (6)
#define SOC_OTG_GPWRDN_LnStsChng_START            (7)
#define SOC_OTG_GPWRDN_LnStsChng_END              (7)
#define SOC_OTG_GPWRDN_LnStsChngMsk_START         (8)
#define SOC_OTG_GPWRDN_LnStsChngMsk_END           (8)
#define SOC_OTG_GPWRDN_ResetDetected_START        (9)
#define SOC_OTG_GPWRDN_ResetDetected_END          (9)
#define SOC_OTG_GPWRDN_ResetDetMsk_START          (10)
#define SOC_OTG_GPWRDN_ResetDetMsk_END            (10)
#define SOC_OTG_GPWRDN_DisconnectDetect_START     (11)
#define SOC_OTG_GPWRDN_DisconnectDetect_END       (11)
#define SOC_OTG_GPWRDN_DisconnectDetectMsk_START  (12)
#define SOC_OTG_GPWRDN_DisconnectDetectMsk_END    (12)
#define SOC_OTG_GPWRDN_ConnectDet_START           (13)
#define SOC_OTG_GPWRDN_ConnectDet_END             (13)
#define SOC_OTG_GPWRDN_ConnDetMsk_START           (14)
#define SOC_OTG_GPWRDN_ConnDetMsk_END             (14)
#define SOC_OTG_GPWRDN_SRPDetect_START            (15)
#define SOC_OTG_GPWRDN_SRPDetect_END              (15)
#define SOC_OTG_GPWRDN_SRPDetectMsk_START         (16)
#define SOC_OTG_GPWRDN_SRPDetectMsk_END           (16)
#define SOC_OTG_GPWRDN_StsChngInt_START           (17)
#define SOC_OTG_GPWRDN_StsChngInt_END             (17)
#define SOC_OTG_GPWRDN_StsChngMsk_START           (18)
#define SOC_OTG_GPWRDN_StsChngMsk_END             (18)
#define SOC_OTG_GPWRDN_LineState_START            (19)
#define SOC_OTG_GPWRDN_LineState_END              (20)
#define SOC_OTG_GPWRDN_IDDIG_START                (21)
#define SOC_OTG_GPWRDN_IDDIG_END                  (21)
#define SOC_OTG_GPWRDN_BSessVld_START             (22)
#define SOC_OTG_GPWRDN_BSessVld_END               (22)
#define SOC_OTG_GPWRDN_ADPInt_START               (23)
#define SOC_OTG_GPWRDN_ADPInt_END                 (23)
#define SOC_OTG_GPWRDN_MultValIdBc_START          (24)
#define SOC_OTG_GPWRDN_MultValIdBc_END            (28)


/*****************************************************************************
 结构名    : SOC_OTG_GDFIFOCFG_UNION
 结构说明  : GDFIFOCFG 寄存器结构定义。地址偏移量:0x005C，初值:0x0F801000，宽度:32
 寄存器说明: 动态FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  GDFIFOCfg      : 16; /* bit[0-15] : 内部RAM深度，以4字节为单位。 */
        unsigned int  EPInfoBaseAddr : 16; /* bit[16-31]: 保存在内部RAM里的寄存器起始地址，以4字节为单位。注意这部分地址空间不能用作FIFO空间，且逻辑也没有做保护。 */
    } reg;
} SOC_OTG_GDFIFOCFG_UNION;
#endif
#define SOC_OTG_GDFIFOCFG_GDFIFOCfg_START       (0)
#define SOC_OTG_GDFIFOCFG_GDFIFOCfg_END         (15)
#define SOC_OTG_GDFIFOCFG_EPInfoBaseAddr_START  (16)
#define SOC_OTG_GDFIFOCFG_EPInfoBaseAddr_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_GADPCTL_UNION
 结构说明  : GADPCTL 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: ADP控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PrbDschng    : 2;  /* bit[0-1]  : Probe操作放电时间。
                                                        00：4毫秒；
                                                        01：8毫秒；
                                                        10：16毫秒；
                                                        11：32毫秒。 */
        unsigned int  PrbDelta     : 2;  /* bit[2-3]  : RTIM时间刻度。
                                                        00：1个时钟周期；
                                                        01：2个时钟周期；
                                                        10：3个时钟周期；
                                                        11：4个时钟周期。 */
        unsigned int  PrbPer       : 2;  /* bit[4-5]  : Probe周期。
                                                        00：0.625秒到0.925秒（典型值0.775秒）；
                                                        01：1.25秒到1.85秒（典型值1.55秒）；
                                                        10：1.9秒到2.6秒（典型值2.275秒）；
                                                        11：reserved。 */
        unsigned int  RTIM         : 11; /* bit[6-16] : VBUS从Vadp_sink上升到Vadp_prb的时间。以PrbDelta表示的32KHz时钟周期为单位。 */
        unsigned int  EnaPrb       : 1;  /* bit[17]   : AdpPrb使能。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned int  EnaSns       : 1;  /* bit[18]   : AdpSns使能。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned int  ADPRes       : 1;  /* bit[19]   : ADP复位控制。
                                                        0：不复位；
                                                        1：复位。 */
        unsigned int  ADPEn        : 1;  /* bit[20]   : ADP使能。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned int  AdpPrbInt    : 1;  /* bit[21]   : AdpPrb中断。当VBUS电压超过Vadpprb触发该中断。
                                                        0：无中断；
                                                        1：有中断。 */
        unsigned int  AdpSnsInt    : 1;  /* bit[22]   : AdpSns中断。当VBUS电压超过Vadpsns触发该中断。
                                                        0：无中断；
                                                        1：有中断。 */
        unsigned int  AdpTmoutInt  : 1;  /* bit[23]   : ADP超时中断。
                                                        0：无中断；
                                                        1：有中断。 */
        unsigned int  AdpPrbIntMsk : 1;  /* bit[24]   : AdpPrb中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  AdpSnsIntMsk : 1;  /* bit[25]   : AdpSns中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  AdpTmoutMsk  : 1;  /* bit[26]   : ADP超时中断屏蔽位。
                                                        0：屏蔽；
                                                        1：不屏蔽。 */
        unsigned int  AR           : 2;  /* bit[27-28]: 读写请求。
                                                        00：操作有效，控制器自动更新；
                                                        01：读操作；
                                                        10：写操作；
                                                        11：保留。 */
        unsigned int  reserved     : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_OTG_GADPCTL_UNION;
#endif
#define SOC_OTG_GADPCTL_PrbDschng_START     (0)
#define SOC_OTG_GADPCTL_PrbDschng_END       (1)
#define SOC_OTG_GADPCTL_PrbDelta_START      (2)
#define SOC_OTG_GADPCTL_PrbDelta_END        (3)
#define SOC_OTG_GADPCTL_PrbPer_START        (4)
#define SOC_OTG_GADPCTL_PrbPer_END          (5)
#define SOC_OTG_GADPCTL_RTIM_START          (6)
#define SOC_OTG_GADPCTL_RTIM_END            (16)
#define SOC_OTG_GADPCTL_EnaPrb_START        (17)
#define SOC_OTG_GADPCTL_EnaPrb_END          (17)
#define SOC_OTG_GADPCTL_EnaSns_START        (18)
#define SOC_OTG_GADPCTL_EnaSns_END          (18)
#define SOC_OTG_GADPCTL_ADPRes_START        (19)
#define SOC_OTG_GADPCTL_ADPRes_END          (19)
#define SOC_OTG_GADPCTL_ADPEn_START         (20)
#define SOC_OTG_GADPCTL_ADPEn_END           (20)
#define SOC_OTG_GADPCTL_AdpPrbInt_START     (21)
#define SOC_OTG_GADPCTL_AdpPrbInt_END       (21)
#define SOC_OTG_GADPCTL_AdpSnsInt_START     (22)
#define SOC_OTG_GADPCTL_AdpSnsInt_END       (22)
#define SOC_OTG_GADPCTL_AdpTmoutInt_START   (23)
#define SOC_OTG_GADPCTL_AdpTmoutInt_END     (23)
#define SOC_OTG_GADPCTL_AdpPrbIntMsk_START  (24)
#define SOC_OTG_GADPCTL_AdpPrbIntMsk_END    (24)
#define SOC_OTG_GADPCTL_AdpSnsIntMsk_START  (25)
#define SOC_OTG_GADPCTL_AdpSnsIntMsk_END    (25)
#define SOC_OTG_GADPCTL_AdpTmoutMsk_START   (26)
#define SOC_OTG_GADPCTL_AdpTmoutMsk_END     (26)
#define SOC_OTG_GADPCTL_AR_START            (27)
#define SOC_OTG_GADPCTL_AR_END              (28)


/*****************************************************************************
 结构名    : SOC_OTG_HPTXFSIZ_UNION
 结构说明  : HPTXFSIZ 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: Host周期发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PTxFStAddr : 16; /* bit[0-15] : Host周期发送FIFO起始地址，以4字节为单位。 */
        unsigned int  PTxFSize   : 16; /* bit[16-31]: Host周期发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_HPTXFSIZ_UNION;
#endif
#define SOC_OTG_HPTXFSIZ_PTxFStAddr_START  (0)
#define SOC_OTG_HPTXFSIZ_PTxFStAddr_END    (15)
#define SOC_OTG_HPTXFSIZ_PTxFSize_START    (16)
#define SOC_OTG_HPTXFSIZ_PTxFSize_END      (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF1_UNION
 结构说明  : DIEPTXF1 寄存器结构定义。地址偏移量:0x0104，初值:0x10002000，宽度:32
 寄存器说明: Device IN端点1发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF1_UNION;
#endif
#define SOC_OTG_DIEPTXF1_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF1_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF1_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF1_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF2_UNION
 结构说明  : DIEPTXF2 寄存器结构定义。地址偏移量:0x0108，初值:0x10003000，宽度:32
 寄存器说明: Device IN端点2发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF2_UNION;
#endif
#define SOC_OTG_DIEPTXF2_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF2_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF2_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF2_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF3_UNION
 结构说明  : DIEPTXF3 寄存器结构定义。地址偏移量:0x010C，初值:0x10004000，宽度:32
 寄存器说明: Device IN端点3发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF3_UNION;
#endif
#define SOC_OTG_DIEPTXF3_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF3_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF3_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF3_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF4_UNION
 结构说明  : DIEPTXF4 寄存器结构定义。地址偏移量:0x0110，初值:0x10005000，宽度:32
 寄存器说明: Device IN端点4发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF4_UNION;
#endif
#define SOC_OTG_DIEPTXF4_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF4_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF4_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF4_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF5_UNION
 结构说明  : DIEPTXF5 寄存器结构定义。地址偏移量:0x0114，初值:0x10006000，宽度:32
 寄存器说明: Device IN端点5发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF5_UNION;
#endif
#define SOC_OTG_DIEPTXF5_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF5_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF5_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF5_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF6_UNION
 结构说明  : DIEPTXF6 寄存器结构定义。地址偏移量:0x0118，初值:0x10007000，宽度:32
 寄存器说明: Device IN端点6发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF6_UNION;
#endif
#define SOC_OTG_DIEPTXF6_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF6_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF6_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF6_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF7_UNION
 结构说明  : DIEPTXF7 寄存器结构定义。地址偏移量:0x011C，初值:0x10008000，宽度:32
 寄存器说明: Device IN端点7发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF7_UNION;
#endif
#define SOC_OTG_DIEPTXF7_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF7_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF7_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF7_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF8_UNION
 结构说明  : DIEPTXF8 寄存器结构定义。地址偏移量:0x0120，初值:0x10009000，宽度:32
 寄存器说明: Device IN端点8发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF8_UNION;
#endif
#define SOC_OTG_DIEPTXF8_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF8_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF8_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF8_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF9_UNION
 结构说明  : DIEPTXF9 寄存器结构定义。地址偏移量:0x0124，初值:0x1000A000，宽度:32
 寄存器说明: Device IN端点9发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF9_UNION;
#endif
#define SOC_OTG_DIEPTXF9_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF9_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF9_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF9_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF10_UNION
 结构说明  : DIEPTXF10 寄存器结构定义。地址偏移量:0x0128，初值:0x1000B000，宽度:32
 寄存器说明: Device IN端点10发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF10_UNION;
#endif
#define SOC_OTG_DIEPTXF10_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF10_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF10_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF10_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF11_UNION
 结构说明  : DIEPTXF11 寄存器结构定义。地址偏移量:0x012C，初值:0x1000C000，宽度:32
 寄存器说明: Device IN端点11发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF11_UNION;
#endif
#define SOC_OTG_DIEPTXF11_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF11_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF11_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF11_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF12_UNION
 结构说明  : DIEPTXF12 寄存器结构定义。地址偏移量:0x0130，初值:0x1000D000，宽度:32
 寄存器说明: Device IN端点12发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF12_UNION;
#endif
#define SOC_OTG_DIEPTXF12_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF12_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF12_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF12_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF13_UNION
 结构说明  : DIEPTXF13 寄存器结构定义。地址偏移量:0x0134，初值:0x1000E000，宽度:32
 寄存器说明: Device IN端点13发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF13_UNION;
#endif
#define SOC_OTG_DIEPTXF13_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF13_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF13_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF13_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF14_UNION
 结构说明  : DIEPTXF14 寄存器结构定义。地址偏移量:0x0138，初值:0x1000F000，宽度:32
 寄存器说明: Device IN端点14发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF14_UNION;
#endif
#define SOC_OTG_DIEPTXF14_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF14_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF14_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF14_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTXF15_UNION
 结构说明  : DIEPTXF15 寄存器结构定义。地址偏移量:0x013C，初值:0x10000000，宽度:32
 寄存器说明: Device IN端点15发送FIFO配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN端点发送FIFO起始地址，以4字节为单位。 */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN端点发送FIFO深度，以4字节为单位。 */
    } reg;
} SOC_OTG_DIEPTXF15_UNION;
#endif
#define SOC_OTG_DIEPTXF15_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF15_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF15_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF15_INEPnTxFDep_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_HCFG_UNION
 结构说明  : HCFG 寄存器结构定义。地址偏移量:0x0400，初值:0x00000200，宽度:32
 寄存器说明: Host配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  FSLSPclkSel : 2;  /* bit[0-1]  : FS/LS PHY接口时钟选择。
                                                       00：30/60MHz；
                                                       01：48MHz；
                                                       others：reserved。 */
        unsigned int  FSLSSupp    : 1;  /* bit[2]    : 仅支持FS和LS使能。
                                                       控制枚举速度。该bit使能，即使device支持HS，控制器也会枚举成FS Host。
                                                       0：不使能；
                                                       1：使能。 */
        unsigned int  reserved_0  : 4;  /* bit[3-6]  : 保留。 */
        unsigned int  Ena32KHzS   : 1;  /* bit[7]    : 使能32KHz suspend模式。改bit必须配置为0，不支持32KHz suspend模式。
                                                       0：不使能；
                                                       1：使能。 */
        unsigned int  ResValid    : 8;  /* bit[8-15] : Resume有效长度。
                                                       仅当HCFG[Ena32KHz]设置为1有效。控制器检测resume信号，超过ResValid个时钟周期认为resume有效。 */
        unsigned int  reserved_1  : 7;  /* bit[16-22]: 保留。 */
        unsigned int  DescDMA     : 1;  /* bit[23]   : 使能Scatter/Gather DMA模式。
                                                       0：不使能；
                                                       1：使能。 */
        unsigned int  FrListEn    : 2;  /* bit[24-25]: 帧列表大小。仅对Scatter/Gather DMA模式有效。
                                                       00：8；
                                                       01：16；
                                                       10：32；
                                                       11：64。 */
        unsigned int  PerSchedEna : 1;  /* bit[26]   : 使能周期传输。仅对Scatter/Gather DMA模式有效。
                                                       0：不使能；
                                                       1：使能。 */
        unsigned int  resered     : 4;  /* bit[27-30]: 保留。 */
        unsigned int  ModeChTimEn : 1;  /* bit[31]   : 模式改变计数使能。
                                                       使能Host控制器在Resume结束等待200个PHY时钟周期，然后将opmode信号改变为00。
                                                       0：等待200个PHY时钟周期或者等待linestate变成SE0；
                                                       1：等待linestate变成SE0。 */
    } reg;
} SOC_OTG_HCFG_UNION;
#endif
#define SOC_OTG_HCFG_FSLSPclkSel_START  (0)
#define SOC_OTG_HCFG_FSLSPclkSel_END    (1)
#define SOC_OTG_HCFG_FSLSSupp_START     (2)
#define SOC_OTG_HCFG_FSLSSupp_END       (2)
#define SOC_OTG_HCFG_Ena32KHzS_START    (7)
#define SOC_OTG_HCFG_Ena32KHzS_END      (7)
#define SOC_OTG_HCFG_ResValid_START     (8)
#define SOC_OTG_HCFG_ResValid_END       (15)
#define SOC_OTG_HCFG_DescDMA_START      (23)
#define SOC_OTG_HCFG_DescDMA_END        (23)
#define SOC_OTG_HCFG_FrListEn_START     (24)
#define SOC_OTG_HCFG_FrListEn_END       (25)
#define SOC_OTG_HCFG_PerSchedEna_START  (26)
#define SOC_OTG_HCFG_PerSchedEna_END    (26)
#define SOC_OTG_HCFG_resered_START      (27)
#define SOC_OTG_HCFG_resered_END        (30)
#define SOC_OTG_HCFG_ModeChTimEn_START  (31)
#define SOC_OTG_HCFG_ModeChTimEn_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_HFIR_UNION
 结构说明  : HFIR 寄存器结构定义。地址偏移量:0x0404，初值:0x0000EA60，宽度:32
 寄存器说明: Host帧间隔寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  FrInt       : 16; /* bit[0-15] : 帧间隔。以PHY接口时钟周期为单位。Host间隔FrInt个时钟周期发送1个SOF。对于HS，需要配置的间隔长度为125us，对于FS/LS需要配置的间隔长度为1ms。该机存器在初始化时配置。 */
        unsigned int  HFIRRldCtrl : 1;  /* bit[16]   : 重新加载计数器控制器。该寄存器在初始化时配置。
                                                       0：FrInt计数器不可自动加载；
                                                       1：FrInt计数器可自动加载。 */
        unsigned int  reserved    : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_OTG_HFIR_UNION;
#endif
#define SOC_OTG_HFIR_FrInt_START        (0)
#define SOC_OTG_HFIR_FrInt_END          (15)
#define SOC_OTG_HFIR_HFIRRldCtrl_START  (16)
#define SOC_OTG_HFIR_HFIRRldCtrl_END    (16)


/*****************************************************************************
 结构名    : SOC_OTG_HFNUM_UNION
 结构说明  : HFNUM 寄存器结构定义。地址偏移量:0x0408，初值:0x00003FFF，宽度:32
 寄存器说明: Host帧序号寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  FrNum : 16; /* bit[0-15] : 帧序号。 */
        unsigned int  FrRem : 16; /* bit[16-31]: 帧剩余时间记数器。从FrInt开始减计数，一直到0重新开始计数。 */
    } reg;
} SOC_OTG_HFNUM_UNION;
#endif
#define SOC_OTG_HFNUM_FrNum_START  (0)
#define SOC_OTG_HFNUM_FrNum_END    (15)
#define SOC_OTG_HFNUM_FrRem_START  (16)
#define SOC_OTG_HFNUM_FrRem_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_HPTXSTS_UNION
 结构说明  : HPTXSTS 寄存器结构定义。地址偏移量:0x0410，初值:0x00081000，宽度:32
 寄存器说明: Host周期发送FIFO和队列状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PTxSpcAvail  : 16; /* bit[0-15] : 周期发送FIFO剩余空间，以4字节为单位。 */
        unsigned int  PTxQSpcAvail : 8;  /* bit[16-23]: 周期发送请求队列剩余空间。
                                                        周期发送请求队列深度为8，该域指示发送请求队列还可以缓存几个发送请求。 */
        unsigned int  PTxQTop      : 8;  /* bit[24-31]: 周期发送请求队列当前请求。用于debug。 */
    } reg;
} SOC_OTG_HPTXSTS_UNION;
#endif
#define SOC_OTG_HPTXSTS_PTxSpcAvail_START   (0)
#define SOC_OTG_HPTXSTS_PTxSpcAvail_END     (15)
#define SOC_OTG_HPTXSTS_PTxQSpcAvail_START  (16)
#define SOC_OTG_HPTXSTS_PTxQSpcAvail_END    (23)
#define SOC_OTG_HPTXSTS_PTxQTop_START       (24)
#define SOC_OTG_HPTXSTS_PTxQTop_END         (31)


/*****************************************************************************
 结构名    : SOC_OTG_HAINT_UNION
 结构说明  : HAINT 寄存器结构定义。地址偏移量:0x0414，初值:0x00000000，宽度:32
 寄存器说明: Host所有通道中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HAINT    : 16; /* bit[0-15] : 通道中断状态。
                                                    Bit0对应通道0，bit15对应通道15。
                                                    0：无中断；
                                                    1：有中断。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_HAINT_UNION;
#endif
#define SOC_OTG_HAINT_HAINT_START     (0)
#define SOC_OTG_HAINT_HAINT_END       (15)


/*****************************************************************************
 结构名    : SOC_OTG_HAINTMSK_UNION
 结构说明  : HAINTMSK 寄存器结构定义。地址偏移量:0x0418，初值:0x00000000，宽度:32
 寄存器说明: Host所用通道中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HAINTMsk : 16; /* bit[0-15] : 通道中断屏蔽。
                                                    Bit0对应通道0，bit15对应通道15。
                                                    0：屏蔽。
                                                    1：不屏蔽。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_HAINTMSK_UNION;
#endif
#define SOC_OTG_HAINTMSK_HAINTMsk_START  (0)
#define SOC_OTG_HAINTMSK_HAINTMsk_END    (15)


/*****************************************************************************
 结构名    : SOC_OTG_HFLBAddr_UNION
 结构说明  : HFLBAddr 寄存器结构定义。地址偏移量:0x041C，初值:0x00000000，宽度:32
 寄存器说明: 帧列表基地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HFLBAddr : 32; /* bit[0-31]: 帧列表基地址，对scatter/gather DMA模式有效。 */
    } reg;
} SOC_OTG_HFLBAddr_UNION;
#endif
#define SOC_OTG_HFLBAddr_HFLBAddr_START  (0)
#define SOC_OTG_HFLBAddr_HFLBAddr_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_HPRT_UNION
 结构说明  : HPRT 寄存器结构定义。地址偏移量:0x0440，初值:0x00000000，宽度:32
 寄存器说明: Host端口控制和状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PrtConnSts     : 1;  /* bit[0]    : 端口连接状态。
                                                          0：没有devie连接到端口；
                                                          1：有device连接到端口。 */
        unsigned int  PrtConnDet     : 1;  /* bit[1]    : 检测到端口连接中断。软件必须写1清除该bit。
                                                          0：无中断；
                                                          1：有中断。 */
        unsigned int  PrtEna         : 1;  /* bit[2]    : 端口使能。
                                                          复位完成之后，端口被控制器使能。过流，断开连接或者软件可能清除该bit。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  PrtEnChng      : 1;  /* bit[3]    : 端口使能状态变化。
                                                          0：无变化；
                                                          1：有变化。 */
        unsigned int  PrtOvrCurrAct  : 1;  /* bit[4]    : 端口过流状态指示。
                                                          0：不过流；
                                                          1：过流。 */
        unsigned int  PrtOvrCurrChng : 1;  /* bit[5]    : 过流状态变化。指示PrtOvrCurrAct状态发生变化。
                                                          0：无变化；
                                                          1：有变化。 */
        unsigned int  PrtRes         : 1;  /* bit[6]    : 端口resume控制。控制在端口发出resume信号。
                                                          0：不resumne；
                                                          1：resume。 */
        unsigned int  PrtSusp        : 1;  /* bit[7]    : 端口suspend控制。控制端口进入suspend状态。
                                                          0：不处于suspend状态；
                                                          1：处于suspend状态。 */
        unsigned int  PrtRst         : 1;  /* bit[8]    : 端口复位控制。
                                                          设置该bit，控制器在端口上发出复位序列。软件必须计算复位时间的长度，并在复位完成之后清除该bit。对于HighSpeed设备，复位必须保持50ms，对于FullSpeed和LowSpeed设备，复位必须保持10ms。
                                                          0：不复位；
                                                          1：复位。 */
        unsigned int  reserved_0     : 1;  /* bit[9]    : 保留。 */
        unsigned int  PrtLnSts       : 2;  /* bit[10-11]: USB总线状态。
                                                          bit[10]：D+的逻辑电平；
                                                          bit[11]：D-的逻辑电平。 */
        unsigned int  PrtPwr         : 1;  /* bit[12]   : 端口功耗控制。出现过流的情况下，控制器自动清除该bit。
                                                          0：关断电源；
                                                          1：打开电源。 */
        unsigned int  PrtTstCtl      : 4;  /* bit[13-16]: 端口测试模式控制。
                                                          0000：测试模式不使能；
                                                          0001：Test_J模式；
                                                          0010：Test_K模式；
                                                          0011：Test_SE0_NAK模式；
                                                          0100：Test_Packet模式；
                                                          0101：Test_Force_Enable；
                                                          others：reserved。 */
        unsigned int  PrtSpd         : 2;  /* bit[17-18]: 端口速度。
                                                          指示连接在该端口上的device速度。
                                                          00：High Speed；
                                                          01：Full Speed；
                                                          10：Low Speed；
                                                          11：reserved。 */
        unsigned int  reserved_1     : 13; /* bit[19-31]: 保留。 */
    } reg;
} SOC_OTG_HPRT_UNION;
#endif
#define SOC_OTG_HPRT_PrtConnSts_START      (0)
#define SOC_OTG_HPRT_PrtConnSts_END        (0)
#define SOC_OTG_HPRT_PrtConnDet_START      (1)
#define SOC_OTG_HPRT_PrtConnDet_END        (1)
#define SOC_OTG_HPRT_PrtEna_START          (2)
#define SOC_OTG_HPRT_PrtEna_END            (2)
#define SOC_OTG_HPRT_PrtEnChng_START       (3)
#define SOC_OTG_HPRT_PrtEnChng_END         (3)
#define SOC_OTG_HPRT_PrtOvrCurrAct_START   (4)
#define SOC_OTG_HPRT_PrtOvrCurrAct_END     (4)
#define SOC_OTG_HPRT_PrtOvrCurrChng_START  (5)
#define SOC_OTG_HPRT_PrtOvrCurrChng_END    (5)
#define SOC_OTG_HPRT_PrtRes_START          (6)
#define SOC_OTG_HPRT_PrtRes_END            (6)
#define SOC_OTG_HPRT_PrtSusp_START         (7)
#define SOC_OTG_HPRT_PrtSusp_END           (7)
#define SOC_OTG_HPRT_PrtRst_START          (8)
#define SOC_OTG_HPRT_PrtRst_END            (8)
#define SOC_OTG_HPRT_PrtLnSts_START        (10)
#define SOC_OTG_HPRT_PrtLnSts_END          (11)
#define SOC_OTG_HPRT_PrtPwr_START          (12)
#define SOC_OTG_HPRT_PrtPwr_END            (12)
#define SOC_OTG_HPRT_PrtTstCtl_START       (13)
#define SOC_OTG_HPRT_PrtTstCtl_END         (16)
#define SOC_OTG_HPRT_PrtSpd_START          (17)
#define SOC_OTG_HPRT_PrtSpd_END            (18)


/*****************************************************************************
 结构名    : SOC_OTG_HCCHARp_UNION
 结构说明  : HCCHARp 寄存器结构定义。地址偏移量:0x0500+0x20*(p)，初值:0x00000000，宽度:32
 寄存器说明: 通道p特性寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 11; /* bit[0-10] : 最大包长。以字节为单位。 */
        unsigned int  EPNum    : 4;  /* bit[11-14]: 端点号。 */
        unsigned int  EPDir    : 1;  /* bit[15]   : 端点方向。
                                                    0：OUT；
                                                    1：IN。 */
        unsigned int  reserved : 1;  /* bit[16]   : 保留。 */
        unsigned int  LSpdDev  : 1;  /* bit[17]   : LowSpeed设备指示。
                                                    软件设置，指示该通道与LowSpeed设备通信。
                                                    0：不是LowSpeed设备；
                                                    1：是LowSpeed设备。 */
        unsigned int  EPType   : 2;  /* bit[18-19]: 端点类型。
                                                    00：control；
                                                    01：isochronous；
                                                    10：bulk；
                                                    11：interrupt。 */
        unsigned int  MC_EC    : 2;  /* bit[20-21]: 当split操作使能，对于周期传输，控制每个微帧的事务个数，对于非周期传输，控制内部DMA重新仲裁之前该通道传输的包个数。
                                                    00：保留；
                                                    01：1；
                                                    10：2；
                                                    11：3。
                                                    该域必须至少配置为2'b01。 */
        unsigned int  DevAddr  : 7;  /* bit[22-28]: Device地址。 */
        unsigned int  OddFrm   : 1;  /* bit[29]   : 奇偶帧控制。
                                                    软件设置该bit，指示Host在奇数帧或者偶数帧发起周期传输。
                                                    0：偶数帧；
                                                    1：奇数帧。 */
        unsigned int  ChDis    : 1;  /* bit[30]   : 通道不使能。
                                                    软件设置该bit停止发送或者接收数据。 */
        unsigned int  ChEna    : 1;  /* bit[31]   : 通道使能。
                                                    当Scatter/Gather DMA使能时：
                                                    0：指示描述符还没有准备好；
                                                    1：指示描述符和数据buffer准备好，通道可以读取描述符。
                                                    当Scatter/Gather DMA不使能时：
                                                    0：通道不使能；
                                                    1：通道使能。 */
    } reg;
} SOC_OTG_HCCHARp_UNION;
#endif
#define SOC_OTG_HCCHARp_MPS_START       (0)
#define SOC_OTG_HCCHARp_MPS_END         (10)
#define SOC_OTG_HCCHARp_EPNum_START     (11)
#define SOC_OTG_HCCHARp_EPNum_END       (14)
#define SOC_OTG_HCCHARp_EPDir_START     (15)
#define SOC_OTG_HCCHARp_EPDir_END       (15)
#define SOC_OTG_HCCHARp_LSpdDev_START   (17)
#define SOC_OTG_HCCHARp_LSpdDev_END     (17)
#define SOC_OTG_HCCHARp_EPType_START    (18)
#define SOC_OTG_HCCHARp_EPType_END      (19)
#define SOC_OTG_HCCHARp_MC_EC_START     (20)
#define SOC_OTG_HCCHARp_MC_EC_END       (21)
#define SOC_OTG_HCCHARp_DevAddr_START   (22)
#define SOC_OTG_HCCHARp_DevAddr_END     (28)
#define SOC_OTG_HCCHARp_OddFrm_START    (29)
#define SOC_OTG_HCCHARp_OddFrm_END      (29)
#define SOC_OTG_HCCHARp_ChDis_START     (30)
#define SOC_OTG_HCCHARp_ChDis_END       (30)
#define SOC_OTG_HCCHARp_ChEna_START     (31)
#define SOC_OTG_HCCHARp_ChEna_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_HCSPLTp_UNION
 结构说明  : HCSPLTp 寄存器结构定义。地址偏移量:0x0504+(p)*0x20，初值:0x00000000，宽度:32
 寄存器说明: 通道p Split控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PrtAddr  : 7;  /* bit[0-6]  : 端口地址。 */
        unsigned int  HubAddr  : 7;  /* bit[7-13] : Hub地址。 */
        unsigned int  XactPos  : 2;  /* bit[14-15]: 传输位置。
                                                    配置OUT传输是否发送all，first，middle或者last payload。
                                                    11：All。传输所有的payload（小于或等于188字节）；
                                                    10：Begin。传输First payload（大于188字节）；
                                                    01：End。传输last payload（大于188字节）；
                                                    00：Mid。传输middle payload（大于188字节）。 */
        unsigned int  CompSplt : 1;  /* bit[16]   : Split完成操作请求。
                                                    软件设置，请求控制器进行split完成传输。
                                                    0：无请求；
                                                    1：有请求。 */
        unsigned int  reserved : 14; /* bit[17-30]: 保留。 */
        unsigned int  SpltEna  : 1;  /* bit[31]   : Split使能。
                                                    使能该通道进行split传输。
                                                    0：不使能；
                                                    1：使能。 */
    } reg;
} SOC_OTG_HCSPLTp_UNION;
#endif
#define SOC_OTG_HCSPLTp_PrtAddr_START   (0)
#define SOC_OTG_HCSPLTp_PrtAddr_END     (6)
#define SOC_OTG_HCSPLTp_HubAddr_START   (7)
#define SOC_OTG_HCSPLTp_HubAddr_END     (13)
#define SOC_OTG_HCSPLTp_XactPos_START   (14)
#define SOC_OTG_HCSPLTp_XactPos_END     (15)
#define SOC_OTG_HCSPLTp_CompSplt_START  (16)
#define SOC_OTG_HCSPLTp_CompSplt_END    (16)
#define SOC_OTG_HCSPLTp_SpltEna_START   (31)
#define SOC_OTG_HCSPLTp_SpltEna_END     (31)


/*****************************************************************************
 结构名    : SOC_OTG_HCINTp_UNION
 结构说明  : HCINTp 寄存器结构定义。地址偏移量:0x0508+(p)*0x20，初值:0x00000000，宽度:32
 寄存器说明: 通道p中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferCompl         : 1;  /* bit[0]    : 传输结束中断。
                                                             对于scatter/gather DMA模式，指示处理完IOC标志有效的描述符。
                                                             对于非scatter/gather DMA模式，指示传输正常结束。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  ChHlted           : 1;  /* bit[1]    : 通道停止中断。
                                                             对于非scatter/gather DMA模式，指示传输异常结束。
                                                             对于scatter/gather DMA模式，指示通道由于以下原因结束：描述符的EOL标志有效，AHB总线错误，验证的事务错误，软件配置通道不使能，babble，stall响应。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  AHBErr            : 1;  /* bit[2]    : AHB总线错误中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  STALL             : 1;  /* bit[3]    : 接收到STALL响应中断。
                                                             对于scatter/gather DMA模式，控制器屏蔽该中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  NAK               : 1;  /* bit[4]    : 接收到NAK响应中断。
                                                             对于scatter/gather DMA模式，控制器屏蔽该中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  ACK               : 1;  /* bit[5]    : 接收或者发送ACK响应中断。
                                                             对于scatter/gather DMA模式，控制器屏蔽该中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  NYET              : 1;  /* bit[6]    : 接收到NYET响应中断。
                                                             对于scatter/gather DMA模式，控制器屏蔽该中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  XactErr           : 1;  /* bit[7]    : 事务错误中断。
                                                             指示发生以下几种错误情况之一：
                                                             CRC校验错误，超时，位填充错误，虚假的EOP。
                                                             对于scatter/gather DMA模式，控制器屏蔽该中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  BblErr            : 1;  /* bit[8]    : Babble错误中断。
                                                             对于scatter/gather DMA模式，控制器屏蔽该中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  FrmOvrun          : 1;  /* bit[9]    : 帧计数翻转中断。
                                                             对于scatter/gather DMA模式，控制器屏蔽该中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  DataTglErr        : 1;  /* bit[10]   : 数据PID翻转错误中断。
                                                             对于scatter/gather DMA模式，控制器屏蔽该中断。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  BNAIntr           : 1;  /* bit[11]   : buffer无效中断。
                                                             对scatter/gather DMA模式有效。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  XCS_XACT_ERR      : 1;  /* bit[12]   : 严重的事务错误中断。
                                                             对scatter/gather DMA模式有效。指示连续3个事务发生错误。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  DESC_LST_ROLLIntr : 1;  /* bit[13]   : 描述符翻转中断。
                                                             对scatter/gather DMA模式有效。
                                                             0：无中断；
                                                             1：有中断。 */
        unsigned int  reserved          : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_OTG_HCINTp_UNION;
#endif
#define SOC_OTG_HCINTp_XferCompl_START          (0)
#define SOC_OTG_HCINTp_XferCompl_END            (0)
#define SOC_OTG_HCINTp_ChHlted_START            (1)
#define SOC_OTG_HCINTp_ChHlted_END              (1)
#define SOC_OTG_HCINTp_AHBErr_START             (2)
#define SOC_OTG_HCINTp_AHBErr_END               (2)
#define SOC_OTG_HCINTp_STALL_START              (3)
#define SOC_OTG_HCINTp_STALL_END                (3)
#define SOC_OTG_HCINTp_NAK_START                (4)
#define SOC_OTG_HCINTp_NAK_END                  (4)
#define SOC_OTG_HCINTp_ACK_START                (5)
#define SOC_OTG_HCINTp_ACK_END                  (5)
#define SOC_OTG_HCINTp_NYET_START               (6)
#define SOC_OTG_HCINTp_NYET_END                 (6)
#define SOC_OTG_HCINTp_XactErr_START            (7)
#define SOC_OTG_HCINTp_XactErr_END              (7)
#define SOC_OTG_HCINTp_BblErr_START             (8)
#define SOC_OTG_HCINTp_BblErr_END               (8)
#define SOC_OTG_HCINTp_FrmOvrun_START           (9)
#define SOC_OTG_HCINTp_FrmOvrun_END             (9)
#define SOC_OTG_HCINTp_DataTglErr_START         (10)
#define SOC_OTG_HCINTp_DataTglErr_END           (10)
#define SOC_OTG_HCINTp_BNAIntr_START            (11)
#define SOC_OTG_HCINTp_BNAIntr_END              (11)
#define SOC_OTG_HCINTp_XCS_XACT_ERR_START       (12)
#define SOC_OTG_HCINTp_XCS_XACT_ERR_END         (12)
#define SOC_OTG_HCINTp_DESC_LST_ROLLIntr_START  (13)
#define SOC_OTG_HCINTp_DESC_LST_ROLLIntr_END    (13)


/*****************************************************************************
 结构名    : SOC_OTG_HCINTMSKp_UNION
 结构说明  : HCINTMSKp 寄存器结构定义。地址偏移量:0x050C+(p)*0x20，初值:0x00000000，宽度:32
 寄存器说明: 通道p中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferCompl            : 1;  /* bit[0]    : 传输结束中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  ChHlted              : 1;  /* bit[1]    : 通道停止中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  AHBErr               : 1;  /* bit[2]    : AHB总线错误中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  STALL                : 1;  /* bit[3]    : 接收到STALL响应中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  NAK                  : 1;  /* bit[4]    : 接收到NAK响应中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  ACK                  : 1;  /* bit[5]    : 接收或者发送ACK响应中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  NYET                 : 1;  /* bit[6]    : 接收到NYET响应中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  XactErr              : 1;  /* bit[7]    : 事务错误中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  BblErr               : 1;  /* bit[8]    : Babble错误中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  FrmOvrunMsk          : 1;  /* bit[9]    : 帧计数翻转中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  DataTglErrMsk        : 1;  /* bit[10]   : 数据PID翻转错误中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  BNAIntrMsk           : 1;  /* bit[11]   : buffer无效中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  reserved_0           : 1;  /* bit[12]   : 保留。 */
        unsigned int  DESC_LST_ROLLIntrMsk : 1;  /* bit[13]   : 描述符翻转中断屏蔽位。
                                                                0：屏蔽；
                                                                1：不屏蔽。 */
        unsigned int  reserved_1           : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_OTG_HCINTMSKp_UNION;
#endif
#define SOC_OTG_HCINTMSKp_XferCompl_START             (0)
#define SOC_OTG_HCINTMSKp_XferCompl_END               (0)
#define SOC_OTG_HCINTMSKp_ChHlted_START               (1)
#define SOC_OTG_HCINTMSKp_ChHlted_END                 (1)
#define SOC_OTG_HCINTMSKp_AHBErr_START                (2)
#define SOC_OTG_HCINTMSKp_AHBErr_END                  (2)
#define SOC_OTG_HCINTMSKp_STALL_START                 (3)
#define SOC_OTG_HCINTMSKp_STALL_END                   (3)
#define SOC_OTG_HCINTMSKp_NAK_START                   (4)
#define SOC_OTG_HCINTMSKp_NAK_END                     (4)
#define SOC_OTG_HCINTMSKp_ACK_START                   (5)
#define SOC_OTG_HCINTMSKp_ACK_END                     (5)
#define SOC_OTG_HCINTMSKp_NYET_START                  (6)
#define SOC_OTG_HCINTMSKp_NYET_END                    (6)
#define SOC_OTG_HCINTMSKp_XactErr_START               (7)
#define SOC_OTG_HCINTMSKp_XactErr_END                 (7)
#define SOC_OTG_HCINTMSKp_BblErr_START                (8)
#define SOC_OTG_HCINTMSKp_BblErr_END                  (8)
#define SOC_OTG_HCINTMSKp_FrmOvrunMsk_START           (9)
#define SOC_OTG_HCINTMSKp_FrmOvrunMsk_END             (9)
#define SOC_OTG_HCINTMSKp_DataTglErrMsk_START         (10)
#define SOC_OTG_HCINTMSKp_DataTglErrMsk_END           (10)
#define SOC_OTG_HCINTMSKp_BNAIntrMsk_START            (11)
#define SOC_OTG_HCINTMSKp_BNAIntrMsk_END              (11)
#define SOC_OTG_HCINTMSKp_DESC_LST_ROLLIntrMsk_START  (13)
#define SOC_OTG_HCINTMSKp_DESC_LST_ROLLIntrMsk_END    (13)


/*****************************************************************************
 结构名    : SOC_OTG_HCTSIZp_UNION
 结构说明  : HCTSIZp 寄存器结构定义。地址偏移量:0x0510+(p)*0x20，初值:0x00000000，宽度:32
 寄存器说明: 通道p传输长度寄存器。（scatter / gather DMA模式）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SCHED_INFO : 8;  /* bit[0-7]  : 调度信息。
                                                      仅对周期传输有效。每bit指示相应的微帧调度控制。Bit[0]对应第1个微帧，bit[7]对应第8个微帧。
                                                      8'b11111111指示在该帧内，该通道每个微帧调度一次，发起相应的令牌包。8'b10101010指示隔一个微帧调度一次。 */
        unsigned int  NTD        : 8;  /* bit[8-15] : 对于scatter/gather DMA模式，指示描述符个数。 */
        unsigned int  reserved   : 13; /* bit[16-28]: 保留。 */
        unsigned int  PID        : 2;  /* bit[29-30]: PID设置。
                                                      设置起始传输的PID。控制器维护传输中其它PID。
                                                      00：DATA0；
                                                      01：DATA2；
                                                      10：DATA1；
                                                      11：MDATA。 */
        unsigned int  DoPng      : 1;  /* bit[31]   : PING操作设置。
                                                      该Bit仅对OUT传输有效。设置该bit，host按照协议进行PING操作。
                                                      对IN传输设置该bit，会导致通道不使能。 */
    } reg;
} SOC_OTG_HCTSIZp_UNION;
#endif
#define SOC_OTG_HCTSIZp_SCHED_INFO_START  (0)
#define SOC_OTG_HCTSIZp_SCHED_INFO_END    (7)
#define SOC_OTG_HCTSIZp_NTD_START         (8)
#define SOC_OTG_HCTSIZp_NTD_END           (15)
#define SOC_OTG_HCTSIZp_PID_START         (29)
#define SOC_OTG_HCTSIZp_PID_END           (30)
#define SOC_OTG_HCTSIZp_DoPng_START       (31)
#define SOC_OTG_HCTSIZp_DoPng_END         (31)


/*****************************************************************************
 结构名    : SOC_OTG_HCTSIZp_non_sg_UNION
 结构说明  : HCTSIZp_non_sg 寄存器结构定义。地址偏移量:0x0510+(p)*0x20，初值:0x00000000，宽度:32
 寄存器说明: 通道p传输长度寄存器。（非scatter / gather DMA模式）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 19; /* bit[0-18] : 传输大小，以字节为单位。
                                                    对于OUT传输，表示Host在这次传输中要传输的字节数。
                                                    对于IN传输，表示这个传输中剩余的字节数。软件需要将该域配置为最大保护包长的整数倍。 */
        unsigned int  PktCnt   : 10; /* bit[19-28]: 包个数配置。 */
        unsigned int  PID      : 2;  /* bit[29-30]: PID设置。
                                                    设置起始传输的PID。控制器维护传输中其它PID。
                                                    00：DATA0；
                                                    01：DATA2；
                                                    10：DATA1；
                                                    11：MDATA（非控制端点）/setup（控制端点）。 */
        unsigned int  DoPng    : 1;  /* bit[31]   : PING操作设置。
                                                    该Bit仅对OUT传输有效。设置该bit，host按照协议进行PING操作。
                                                    对IN传输设置该bit，会导致通道不使能。 */
    } reg;
} SOC_OTG_HCTSIZp_non_sg_UNION;
#endif
#define SOC_OTG_HCTSIZp_non_sg_XferSize_START  (0)
#define SOC_OTG_HCTSIZp_non_sg_XferSize_END    (18)
#define SOC_OTG_HCTSIZp_non_sg_PktCnt_START    (19)
#define SOC_OTG_HCTSIZp_non_sg_PktCnt_END      (28)
#define SOC_OTG_HCTSIZp_non_sg_PID_START       (29)
#define SOC_OTG_HCTSIZp_non_sg_PID_END         (30)
#define SOC_OTG_HCTSIZp_non_sg_DoPng_START     (31)
#define SOC_OTG_HCTSIZp_non_sg_DoPng_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_HCDMAp_UNION
 结构说明  : HCDMAp 寄存器结构定义。地址偏移量:0x0514+(p)*0x20，初值:0x00000000，宽度:32
 寄存器说明: 通道p DMA地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMAAddr : 32; /* bit[0-31]: DMA起始地址。 */
    } reg;
} SOC_OTG_HCDMAp_UNION;
#endif
#define SOC_OTG_HCDMAp_DMAAddr_START  (0)
#define SOC_OTG_HCDMAp_DMAAddr_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_HCDMABp_UNION
 结构说明  : HCDMABp 寄存器结构定义。地址偏移量:0x051C+(p)*0x20，初值:0x00000000，宽度:32
 寄存器说明: 通道p DMA buffer地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HCDMA : 32; /* bit[0-31]: 当前buffer地址。对scatter/gather DMA模式有效。 */
    } reg;
} SOC_OTG_HCDMABp_UNION;
#endif
#define SOC_OTG_HCDMABp_HCDMA_START  (0)
#define SOC_OTG_HCDMABp_HCDMA_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_DCFG_UNION
 结构说明  : DCFG 寄存器结构定义。地址偏移量:0x0800，初值:0x08200000，宽度:32
 寄存器说明: device配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DevSpd       : 2;  /* bit[0-1]  : Device速度模式配置。
                                                        00：High-speed；
                                                        01：Full-speed；
                                                        others：reserved。 */
        unsigned int  NZStsOUTHShk : 1;  /* bit[2]    : 非0长度的OUT握手策略选择。在控制传输的状态阶段，当收到非0长度的数据包时，需要返回1个握手包。配置该bit选择送出什么握手包。
                                                        0：将收到的数据包送给软件，并按照相应端点控制寄存器的NAK和STALL位送出握手包；
                                                        1：送出STALL握手包，并丢弃收到的数据包。 */
        unsigned int  reserved_0   : 1;  /* bit[3]    : 保留。 */
        unsigned int  DevAddr      : 7;  /* bit[4-10] : device地址。每次收到SetAddr命令后，软件必须将device地址写入该域。 */
        unsigned int  PerFrInt     : 2;  /* bit[11-12]: 周期帧间隔。在1个微帧内，当周期帧间隔达到该域的值，上报周期帧结束中断。
                                                        00：微帧长度的80％；
                                                        01：微帧长度的85％；
                                                        10：微帧长度的90％；
                                                        11：微帧长度的95％。 */
        unsigned int  EnDevOutNak  : 1;  /* bit[13]   : Device OUT NAK使能
                                                        0：Bulk OUT完成后不发送NAK
                                                        1：Bulk OUT完成后发送NAK */
        unsigned int  reserved_1   : 4;  /* bit[14-17]: 保留。 */
        unsigned int  EpMisCnt     : 5;  /* bit[18-22]: IN端点Mismatch计数 */
        unsigned int  DescDMA      : 1;  /* bit[23]   : Scatter/Gather DMA使能。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned int  PerSchIntvl  : 2;  /* bit[24-25]: 周期调度间隔。配置DMA分配给搬移周期IN端点数据的时间。如果有周期端点被激活，DMA必须分配该域配置的时间用于搬移非周期IN端点数据；否则，DMA为非周期端点服务。该域配置的时间之后，DMA开始搬移非周期端点数据。
                                                        00：微帧长度的25%；
                                                        01：微帧长度的50%；
                                                        10：微帧长度的75%；
                                                        11：保留。 */
        unsigned int  reserved_2   : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_OTG_DCFG_UNION;
#endif
#define SOC_OTG_DCFG_DevSpd_START        (0)
#define SOC_OTG_DCFG_DevSpd_END          (1)
#define SOC_OTG_DCFG_NZStsOUTHShk_START  (2)
#define SOC_OTG_DCFG_NZStsOUTHShk_END    (2)
#define SOC_OTG_DCFG_DevAddr_START       (4)
#define SOC_OTG_DCFG_DevAddr_END         (10)
#define SOC_OTG_DCFG_PerFrInt_START      (11)
#define SOC_OTG_DCFG_PerFrInt_END        (12)
#define SOC_OTG_DCFG_EnDevOutNak_START   (13)
#define SOC_OTG_DCFG_EnDevOutNak_END     (13)
#define SOC_OTG_DCFG_EpMisCnt_START      (18)
#define SOC_OTG_DCFG_EpMisCnt_END        (22)
#define SOC_OTG_DCFG_DescDMA_START       (23)
#define SOC_OTG_DCFG_DescDMA_END         (23)
#define SOC_OTG_DCFG_PerSchIntvl_START   (24)
#define SOC_OTG_DCFG_PerSchIntvl_END     (25)


/*****************************************************************************
 结构名    : SOC_OTG_DCTL_UNION
 结构说明  : DCTL 寄存器结构定义。地址偏移量:0x0804，初值:0x00000002，宽度:32
 寄存器说明: device控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RmtWkUpSig          : 1;  /* bit[0]    : 远程唤醒控制。
                                                               配置该bit，控制器远程唤醒host。软件通过配置该bit，使device退出suspend状态。根据协议，软件必须在配置该bit之后，1～15ms内清除该bit。
                                                               当LPM使能且device处于L1(sleep)状态，软件通过设置该bit唤醒host，并使device退出L1状态。硬件在50us之后自动清除该bit。
                                                               0：不进行远程唤醒操作；
                                                               1：进行远程唤醒操作。 */
        unsigned int  SftDiscon           : 1;  /* bit[1]    : 软件断开连接控制。
                                                               0：正常操作；
                                                               1：控制器驱动UTMI+接口的opmode信号为2'b01，在USB host端产生device断开连接事件。 */
        unsigned int  GNPINNakSts         : 1;  /* bit[2]    : 全局非周期IN传输NAK状态。
                                                               0：根据发送FIFO中数据发送握手包；
                                                               1：发送NAK。 */
        unsigned int  GOUTNakSts          : 1;  /* bit[3]    : 全局非周期OUT传输NAK状态。
                                                               0：握手包已经发送；
                                                               1：发送NAK，并忽略接收到的数据。 */
        unsigned int  TstCtl              : 3;  /* bit[4-6]  : 测试模式控制。
                                                               000：测试模式不使能；
                                                               001：测试J模式；
                                                               010：测试K模式；
                                                               011：测试SE0_NAK模式；
                                                               100：测试包模式；
                                                               101：测试Force_Enable模式；
                                                               others：保留。 */
        unsigned int  SGNPInNak           : 1;  /* bit[7]    : 全局非周期IN传输NAK设置。软件对该bit写“1”后，device对所有的非周期IN传输响应NAK。软件必须在GINTSTS[GINNakEff]清除后才能配置该bit。
                                                               0：不设置NAK；
                                                               1：设置NAK。 */
        unsigned int  CGNPInNak           : 1;  /* bit[8]    : 清除全局非周期IN传输NAK设置。对该bit的写“1”清除全局IN NAK。
                                                               0：不清除；
                                                               1：清除。 */
        unsigned int  SGOUTNak            : 1;  /* bit[9]    : 全局非周期OUT传输NAK设置。软件对该bit写“1”后，device对所有的非周期OUT传输响应NAK。软件必须在GINTSTS[GOUTNakEff]清除后才能配置该bit。
                                                               0：不设置NAK；
                                                               1：设置NAK。 */
        unsigned int  CGOUTNak            : 1;  /* bit[10]   : 清除全局非周期IN传输NAK设置。对该bit的写“1”清除全局OUT NAK。
                                                               0：不清除；
                                                               1：清除。 */
        unsigned int  PWROnPrgDone        : 1;  /* bit[11]   : 上电编程完毕。软件配置该bit，指示退出Power Down模式后，软件配置寄存器完毕。
                                                               0：未完成；
                                                               1：完成。 */
        unsigned int  reserved_0          : 1;  /* bit[12]   : 保留。 */
        unsigned int  GMC                 : 2;  /* bit[13-14]: 在Scatter/Gather DMA模式下，配置DMA服务下1个端点之前，服务本端点的包数量，仅针对非周期端点。
                                                               00：reserved；
                                                               01：1个包；
                                                               10：2个包；
                                                               11：3个包。 */
        unsigned int  IgnrFrmNum          : 1;  /* bit[15]   : 在Scatter/Gather DMA模式下，忽略同步端点的帧序号。该bit使能，描述符中的帧序号比当前帧序号小，也不清除发送FIFO中的数据。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  NakOnBble           : 1;  /* bit[16]   : 设置收到babble之后自动回复NAK。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  EnContOnBNA         : 1;  /* bit[17]   : Enable Continue on BNA
                                                               0：starts processing from the DOEPDMA descriptor
                                                               1：starts processing from the descriptor that received the BNA interrupt */
        unsigned int  DeepSleepBESLReject : 1;  /* bit[18]   : Deep Sleep BESL Reject */
        unsigned int  reserved_1          : 13; /* bit[19-31]: 保留。 */
    } reg;
} SOC_OTG_DCTL_UNION;
#endif
#define SOC_OTG_DCTL_RmtWkUpSig_START           (0)
#define SOC_OTG_DCTL_RmtWkUpSig_END             (0)
#define SOC_OTG_DCTL_SftDiscon_START            (1)
#define SOC_OTG_DCTL_SftDiscon_END              (1)
#define SOC_OTG_DCTL_GNPINNakSts_START          (2)
#define SOC_OTG_DCTL_GNPINNakSts_END            (2)
#define SOC_OTG_DCTL_GOUTNakSts_START           (3)
#define SOC_OTG_DCTL_GOUTNakSts_END             (3)
#define SOC_OTG_DCTL_TstCtl_START               (4)
#define SOC_OTG_DCTL_TstCtl_END                 (6)
#define SOC_OTG_DCTL_SGNPInNak_START            (7)
#define SOC_OTG_DCTL_SGNPInNak_END              (7)
#define SOC_OTG_DCTL_CGNPInNak_START            (8)
#define SOC_OTG_DCTL_CGNPInNak_END              (8)
#define SOC_OTG_DCTL_SGOUTNak_START             (9)
#define SOC_OTG_DCTL_SGOUTNak_END               (9)
#define SOC_OTG_DCTL_CGOUTNak_START             (10)
#define SOC_OTG_DCTL_CGOUTNak_END               (10)
#define SOC_OTG_DCTL_PWROnPrgDone_START         (11)
#define SOC_OTG_DCTL_PWROnPrgDone_END           (11)
#define SOC_OTG_DCTL_GMC_START                  (13)
#define SOC_OTG_DCTL_GMC_END                    (14)
#define SOC_OTG_DCTL_IgnrFrmNum_START           (15)
#define SOC_OTG_DCTL_IgnrFrmNum_END             (15)
#define SOC_OTG_DCTL_NakOnBble_START            (16)
#define SOC_OTG_DCTL_NakOnBble_END              (16)
#define SOC_OTG_DCTL_EnContOnBNA_START          (17)
#define SOC_OTG_DCTL_EnContOnBNA_END            (17)
#define SOC_OTG_DCTL_DeepSleepBESLReject_START  (18)
#define SOC_OTG_DCTL_DeepSleepBESLReject_END    (18)


/*****************************************************************************
 结构名    : SOC_OTG_DSTS_UNION
 结构说明  : DSTS 寄存器结构定义。地址偏移量:0x0808，初值:0x0007FF02，宽度:32
 寄存器说明: device状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SuspSts   : 1;  /* bit[0]    : suspend状态指示。
                                                     0：不处于suspend状态；
                                                     1：处于suspend状态。 */
        unsigned int  EnumSpd   : 2;  /* bit[1-2]  : 枚举速度。
                                                     00：高速（PHY时钟为30或60MHz）；
                                                     01：全速（PHY时钟为30或60MHz）；
                                                     others：保留。 */
        unsigned int  ErrticErr : 1;  /* bit[3]    : 用于指示任何UTMI+上接收到的不确定的错误。产生这种错误时，控制器进入suspend状态，并上报中断GINTSTS[ErlySusp]。
                                                     0：没有UTMI+接口错误；
                                                     1：有UTMI+接口错误。 */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : 保留。 */
        unsigned int  SOFFN     : 14; /* bit[8-21] : 当前帧或者微帧的帧序号。 */
        unsigned int  DevLnSts  : 2;  /* bit[22-23]: Device Line Status (DevLnSts)  */
        unsigned int  reserved_1: 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_OTG_DSTS_UNION;
#endif
#define SOC_OTG_DSTS_SuspSts_START    (0)
#define SOC_OTG_DSTS_SuspSts_END      (0)
#define SOC_OTG_DSTS_EnumSpd_START    (1)
#define SOC_OTG_DSTS_EnumSpd_END      (2)
#define SOC_OTG_DSTS_ErrticErr_START  (3)
#define SOC_OTG_DSTS_ErrticErr_END    (3)
#define SOC_OTG_DSTS_SOFFN_START      (8)
#define SOC_OTG_DSTS_SOFFN_END        (21)
#define SOC_OTG_DSTS_DevLnSts_START   (22)
#define SOC_OTG_DSTS_DevLnSts_END     (23)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPMSK_UNION
 结构说明  : DIEPMSK 寄存器结构定义。地址偏移量:0x0810，初值:0x00000000，宽度:32
 寄存器说明: IN端点普通中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferComplMsk   : 1;  /* bit[0]    : 传输完成中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  EPDisbldMsk    : 1;  /* bit[1]    : 端点不使能中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  AHBErrMsk      : 1;  /* bit[2]    : AHB总线错误中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  TimeOUTMsk     : 1;  /* bit[3]    : 超时中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  INTknTXFEmpMsk : 1;  /* bit[4]    : 接收到IN令牌，但是发送FIFO空中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  reserved_0     : 1;  /* bit[5]    : 保留。 */
        unsigned int  INEPNakEffMsk  : 1;  /* bit[6]    : IN端点NAK有效屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  reserved_1     : 1;  /* bit[7]    : 保留。 */
        unsigned int  TxfifoUndrnMsk : 1;  /* bit[8]    : 发送FIFO下溢中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  BNAInIntrMsk   : 1;  /* bit[9]    : IN端点BNA中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  reserved_2     : 3;  /* bit[10-12]: 保留。 */
        unsigned int  NAKMsk         : 1;  /* bit[13]   : IN端点NAK中断屏蔽位。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  reserved_3     : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_OTG_DIEPMSK_UNION;
#endif
#define SOC_OTG_DIEPMSK_XferComplMsk_START    (0)
#define SOC_OTG_DIEPMSK_XferComplMsk_END      (0)
#define SOC_OTG_DIEPMSK_EPDisbldMsk_START     (1)
#define SOC_OTG_DIEPMSK_EPDisbldMsk_END       (1)
#define SOC_OTG_DIEPMSK_AHBErrMsk_START       (2)
#define SOC_OTG_DIEPMSK_AHBErrMsk_END         (2)
#define SOC_OTG_DIEPMSK_TimeOUTMsk_START      (3)
#define SOC_OTG_DIEPMSK_TimeOUTMsk_END        (3)
#define SOC_OTG_DIEPMSK_INTknTXFEmpMsk_START  (4)
#define SOC_OTG_DIEPMSK_INTknTXFEmpMsk_END    (4)
#define SOC_OTG_DIEPMSK_INEPNakEffMsk_START   (6)
#define SOC_OTG_DIEPMSK_INEPNakEffMsk_END     (6)
#define SOC_OTG_DIEPMSK_TxfifoUndrnMsk_START  (8)
#define SOC_OTG_DIEPMSK_TxfifoUndrnMsk_END    (8)
#define SOC_OTG_DIEPMSK_BNAInIntrMsk_START    (9)
#define SOC_OTG_DIEPMSK_BNAInIntrMsk_END      (9)
#define SOC_OTG_DIEPMSK_NAKMsk_START          (13)
#define SOC_OTG_DIEPMSK_NAKMsk_END            (13)


/*****************************************************************************
 结构名    : SOC_OTG_DOEPMSK_UNION
 结构说明  : DOEPMSK 寄存器结构定义。地址偏移量:0x0814，初值:0x00000000，宽度:32
 寄存器说明: OUT端点普通中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferComplMsk   : 1;  /* bit[0]    : 传输完成中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  EPDisbldMsk    : 1;  /* bit[1]    : 端点不使能中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  AHBErrMsk      : 1;  /* bit[2]    : AHB总线错误中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  SetUPMsk       : 1;  /* bit[3]    : setup阶段完成中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  OUTTknEPdisMsk : 1;  /* bit[4]    : 接收到OUT令牌，但端点没有使能中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  reserved_0     : 1;  /* bit[5]    : 保留。 */
        unsigned int  Back2BackSetup : 1;  /* bit[6]    : 背靠背SETUP包接收中断。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  reserved_1     : 1;  /* bit[7]    : 保留。 */
        unsigned int  OutPktErrMsk   : 1;  /* bit[8]    : OUT包错误中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  BNAOutIntrMsk  : 1;  /* bit[9]    : OUT端点BNA中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  reserved_2     : 2;  /* bit[10-11]: 保留。 */
        unsigned int  BbleErrMsk     : 1;  /* bit[12]   : babble错误中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  NAKMsk         : 1;  /* bit[13]   : NAK中断屏蔽位。
                                                          0：屏蔽
                                                          1：不屏蔽 */
        unsigned int  NYETMsk        : 1;  /* bit[14]   : NYET中断屏蔽。
                                                          0：屏蔽；
                                                          1：不屏蔽。 */
        unsigned int  reserved_3     : 17; /* bit[15-31]: 保留。 */
    } reg;
} SOC_OTG_DOEPMSK_UNION;
#endif
#define SOC_OTG_DOEPMSK_XferComplMsk_START    (0)
#define SOC_OTG_DOEPMSK_XferComplMsk_END      (0)
#define SOC_OTG_DOEPMSK_EPDisbldMsk_START     (1)
#define SOC_OTG_DOEPMSK_EPDisbldMsk_END       (1)
#define SOC_OTG_DOEPMSK_AHBErrMsk_START       (2)
#define SOC_OTG_DOEPMSK_AHBErrMsk_END         (2)
#define SOC_OTG_DOEPMSK_SetUPMsk_START        (3)
#define SOC_OTG_DOEPMSK_SetUPMsk_END          (3)
#define SOC_OTG_DOEPMSK_OUTTknEPdisMsk_START  (4)
#define SOC_OTG_DOEPMSK_OUTTknEPdisMsk_END    (4)
#define SOC_OTG_DOEPMSK_Back2BackSetup_START  (6)
#define SOC_OTG_DOEPMSK_Back2BackSetup_END    (6)
#define SOC_OTG_DOEPMSK_OutPktErrMsk_START    (8)
#define SOC_OTG_DOEPMSK_OutPktErrMsk_END      (8)
#define SOC_OTG_DOEPMSK_BNAOutIntrMsk_START   (9)
#define SOC_OTG_DOEPMSK_BNAOutIntrMsk_END     (9)
#define SOC_OTG_DOEPMSK_BbleErrMsk_START      (12)
#define SOC_OTG_DOEPMSK_BbleErrMsk_END        (12)
#define SOC_OTG_DOEPMSK_NAKMsk_START          (13)
#define SOC_OTG_DOEPMSK_NAKMsk_END            (13)
#define SOC_OTG_DOEPMSK_NYETMsk_START         (14)
#define SOC_OTG_DOEPMSK_NYETMsk_END           (14)


/*****************************************************************************
 结构名    : SOC_OTG_DAINT_UNION
 结构说明  : DAINT 寄存器结构定义。地址偏移量:0x0818，初值:0x00000000，宽度:32
 寄存器说明: 所有端点中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InEpInt  : 16; /* bit[0-15] : IN端点中断。每bit对应1个端点，bit[0]对应端点0，bit[15]对应端点15。 */
        unsigned int  OutEpInt : 16; /* bit[16-31]: OUT端点中断。每bit对应1个端点，bit[16对应端点0，bit[31]对应端点15。 */
    } reg;
} SOC_OTG_DAINT_UNION;
#endif
#define SOC_OTG_DAINT_InEpInt_START   (0)
#define SOC_OTG_DAINT_InEpInt_END     (15)
#define SOC_OTG_DAINT_OutEpInt_START  (16)
#define SOC_OTG_DAINT_OutEpInt_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_DAINTMSK_UNION
 结构说明  : DAINTMSK 寄存器结构定义。地址偏移量:0x081C，初值:0x00000000，宽度:32
 寄存器说明: 所有端点中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InEpMsk  : 16; /* bit[0-15] : IN端点的中断屏蔽。每bit对应一个端点，bit[0]对应端点0，bit[15]对应端点15。
                                                    0：屏蔽；
                                                    1：不屏蔽。 */
        unsigned int  OutEpMsk : 16; /* bit[16-31]: OUT端点的中断屏蔽。每bit对应一个端点，bit[16]对应端点0，bit[31]对应端点15。
                                                    0：屏蔽；
                                                    1：不屏蔽。 */
    } reg;
} SOC_OTG_DAINTMSK_UNION;
#endif
#define SOC_OTG_DAINTMSK_InEpMsk_START   (0)
#define SOC_OTG_DAINTMSK_InEpMsk_END     (15)
#define SOC_OTG_DAINTMSK_OutEpMsk_START  (16)
#define SOC_OTG_DAINTMSK_OutEpMsk_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_DVBUSDIS_UNION
 结构说明  : DVBUSDIS 寄存器结构定义。地址偏移量:0x0828，初值:0x000017D7，宽度:32
 寄存器说明: Vbus放电时间配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DVBUSDis : 16; /* bit[0-15] : Vbus放电时间。配置在SRP过程中Vbus的放电时间。该域的值等于Vbus放电时间的PHY时钟周期数/1024。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_DVBUSDIS_UNION;
#endif
#define SOC_OTG_DVBUSDIS_DVBUSDis_START  (0)
#define SOC_OTG_DVBUSDIS_DVBUSDis_END    (15)


/*****************************************************************************
 结构名    : SOC_OTG_DVBUSPULSE_UNION
 结构说明  : DVBUSPULSE 寄存器结构定义。地址偏移量:0x082C，初值:0x000005B8，宽度:32
 寄存器说明: Vbus脉冲配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DVBUSPulse : 12; /* bit[0-11] : Vbus脉冲时间。配置在SRP过程中Vbus脉冲时间。该域的值等于Vbus脉冲时间的PHY时钟周期数/1024。 */
        unsigned int  reserved   : 20; /* bit[12-31]: 保留。 */
    } reg;
} SOC_OTG_DVBUSPULSE_UNION;
#endif
#define SOC_OTG_DVBUSPULSE_DVBUSPulse_START  (0)
#define SOC_OTG_DVBUSPULSE_DVBUSPulse_END    (11)


/*****************************************************************************
 结构名    : SOC_OTG_DTHRCTL_UNION
 结构说明  : DTHRCTL 寄存器结构定义。地址偏移量:0x0830，初值:0x0C100020，宽度:32
 寄存器说明: device水线控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  NonISOThrEn : 1;  /* bit[0]    : 非Isochronous IN端点水线使能。
                                                       0：不使能；
                                                       1：使能。 */
        unsigned int  ISOThrEn    : 1;  /* bit[1]    : Isochronous IN端点水线使能。
                                                       0：不使能；
                                                       1：使能。 */
        unsigned int  TxThrLen    : 9;  /* bit[2-10] : 发送FIFO水线，该域同时也是MAC水线。单位为32bit。当发送FIFO中数据大于水线，向USB发送数据。
                                                       当AHBThrRatio=2'b00时，水线至少配置为8；当AHBThrRation不为0时，该域配置的值必须保证AHB水线不小于8。
                                                       该域对isochronous和非isochronous传输都有效。
                                                       建议配置值与配置的AHB burst长度相等。 */
        unsigned int  AHBThrRatio : 2;  /* bit[11-12]: 发送数据时，AHB水线与MAC水线的比例。
                                                       00：AHB水线＝MAC水线；
                                                       01：AHB水线＝MAC水线/2;
                                                       10：AHB水线＝MAC水线/4；
                                                       11：AHB水线＝MAC水线/8 */
        unsigned int  reserved_0  : 3;  /* bit[13-15]: 保留。 */
        unsigned int  RxThrEn     : 1;  /* bit[16]   : 接收水线使能。
                                                       0：不使能；
                                                       1：使能。 */
        unsigned int  RxThrLen    : 9;  /* bit[17-25]: 接收FIFO水线。单位为32bit。当从USB总线上接收到的数据大于该域配置值时，启动AHB传输。该域配置值不能小于8。建议该域配置值等于AHB burst长度。 */
        unsigned int  reserved_1  : 1;  /* bit[26]   : 保留。 */
        unsigned int  ArbPkEn     : 1;  /* bit[27]   : DMA仲裁配置。该bit配置IN端点的DMA仲裁。当该bit使能，如果某IN端点接收到IN令牌，该IN端点会一直得到DMA的仲裁。该bit可以防止发送FIFO下溢。
                                                       0：不使能；
                                                       1：使能。 */
        unsigned int  reserved_2  : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_OTG_DTHRCTL_UNION;
#endif
#define SOC_OTG_DTHRCTL_NonISOThrEn_START  (0)
#define SOC_OTG_DTHRCTL_NonISOThrEn_END    (0)
#define SOC_OTG_DTHRCTL_ISOThrEn_START     (1)
#define SOC_OTG_DTHRCTL_ISOThrEn_END       (1)
#define SOC_OTG_DTHRCTL_TxThrLen_START     (2)
#define SOC_OTG_DTHRCTL_TxThrLen_END       (10)
#define SOC_OTG_DTHRCTL_AHBThrRatio_START  (11)
#define SOC_OTG_DTHRCTL_AHBThrRatio_END    (12)
#define SOC_OTG_DTHRCTL_RxThrEn_START      (16)
#define SOC_OTG_DTHRCTL_RxThrEn_END        (16)
#define SOC_OTG_DTHRCTL_RxThrLen_START     (17)
#define SOC_OTG_DTHRCTL_RxThrLen_END       (25)
#define SOC_OTG_DTHRCTL_ArbPkEn_START      (27)
#define SOC_OTG_DTHRCTL_ArbPkEn_END        (27)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPEMPMSK_UNION
 结构说明  : DIEPEMPMSK 寄存器结构定义。地址偏移量:0x0834，初值:0x00000000，宽度:32
 寄存器说明: IN端点FIFO空中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InEpTxfEmpMsk : 16; /* bit[0-15] : IN端点发送FIFO空中断屏蔽寄存器。每bit对应一个端点，bit[0]对应端点0，bit[15]对应端点15。
                                                         每bit含义：
                                                         0：屏蔽；
                                                         1：不屏蔽。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_DIEPEMPMSK_UNION;
#endif
#define SOC_OTG_DIEPEMPMSK_InEpTxfEmpMsk_START  (0)
#define SOC_OTG_DIEPEMPMSK_InEpTxfEmpMsk_END    (15)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPCTL0_UNION
 结构说明  : DIEPCTL0 寄存器结构定义。地址偏移量:0x0900，初值:0x00008000，宽度:32
 寄存器说明: IN端点0控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 2;  /* bit[0-1]  : 最大包大小。对IN端点和OUT端点都有效。
                                                    00：64字节；
                                                    01：32字节；
                                                    10：16字节；
                                                    11：8字节。 */
        unsigned int  reserved_0: 9;  /* bit[2-10] : 保留。 */
        unsigned int  NextEp   : 4;  /* bit[11-14]: Next Endpoint (NextEp)  */
        unsigned int  USBActEP : 1;  /* bit[15]   : 端点是否激活。该bit一直为1，表示端点0一直处于激活状态。 */
        unsigned int  reserved_1: 1;  /* bit[16]   : 保留。 */
        unsigned int  NAKSts   : 1;  /* bit[17]   : NAK状态。
                                                    0：根据FIFO状态发送握手包；
                                                    1：对该端点的传输请求一直发送NAK握手包。 */
        unsigned int  EPType   : 2;  /* bit[18-19]: 端点类型。一直为0，表示端点0是控制端点。 */
        unsigned int  reserved_2: 1;  /* bit[20]   : 保留。 */
        unsigned int  Stall    : 1;  /* bit[21]   : STALL握手设置。软件配置该bit使能，硬件收到setup包会清除该bit。该bit使能，对该端点的请求一直响应STALL握手。该bit的优先级高于NAK设置。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  TxFNum   : 4;  /* bit[22-25]: 端点0的发送FIFO序号。 */
        unsigned int  CNAK     : 1;  /* bit[26]   : 清除NAK设置。向该bit写1清除NAK设置。
                                                    0：不清除；
                                                    1：清除。 */
        unsigned int  SNAK     : 1;  /* bit[27]   : NAK设置。设置该bit后，即使发送FIFO有数据，硬件也不向外发送。并对接收到的setup包返回NAK握手。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  reserved_3: 2;  /* bit[28-29]: 保留。 */
        unsigned int  EPDis    : 1;  /* bit[30]   : 端点使能清除。
                                                    0：不清除；
                                                    1：清除。 */
        unsigned int  EPEna    : 1;  /* bit[31]   : 端点使能。
                                                    0：不使能；
                                                    1：使能。 */
    } reg;
} SOC_OTG_DIEPCTL0_UNION;
#endif
#define SOC_OTG_DIEPCTL0_MPS_START       (0)
#define SOC_OTG_DIEPCTL0_MPS_END         (1)
#define SOC_OTG_DIEPCTL0_NextEp_START    (11)
#define SOC_OTG_DIEPCTL0_NextEp_END      (14)
#define SOC_OTG_DIEPCTL0_USBActEP_START  (15)
#define SOC_OTG_DIEPCTL0_USBActEP_END    (15)
#define SOC_OTG_DIEPCTL0_NAKSts_START    (17)
#define SOC_OTG_DIEPCTL0_NAKSts_END      (17)
#define SOC_OTG_DIEPCTL0_EPType_START    (18)
#define SOC_OTG_DIEPCTL0_EPType_END      (19)
#define SOC_OTG_DIEPCTL0_Stall_START     (21)
#define SOC_OTG_DIEPCTL0_Stall_END       (21)
#define SOC_OTG_DIEPCTL0_TxFNum_START    (22)
#define SOC_OTG_DIEPCTL0_TxFNum_END      (25)
#define SOC_OTG_DIEPCTL0_CNAK_START      (26)
#define SOC_OTG_DIEPCTL0_CNAK_END        (26)
#define SOC_OTG_DIEPCTL0_SNAK_START      (27)
#define SOC_OTG_DIEPCTL0_SNAK_END        (27)
#define SOC_OTG_DIEPCTL0_EPDis_START     (30)
#define SOC_OTG_DIEPCTL0_EPDis_END       (30)
#define SOC_OTG_DIEPCTL0_EPEna_START     (31)
#define SOC_OTG_DIEPCTL0_EPEna_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPCTLn_UNION
 结构说明  : DIEPCTLn 寄存器结构定义。地址偏移量:0x0900+0x20*(n)，初值:0x00000000，宽度:32
 寄存器说明: IN端点n控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 11; /* bit[0-10] : 最大包长。单位为字节。 */
        unsigned int  reserved_0: 4;  /* bit[11-14]: 保留。 */
        unsigned int  USBActEp : 1;  /* bit[15]   : 端点激活。
                                                    0：没有激活；
                                                    1：激活。 */
        unsigned int  DPID     : 1;  /* bit[16]   : 数据包PID状态。仅对interrupt和bulk传输有效。
                                                    0：DATA0；
                                                    1：DATA1。 */
        unsigned int  NAKSts   : 1;  /* bit[17]   : NAK状态。
                                                    0：根据FIFO状态发送握手包；
                                                    1：对该端点的传输请求一直发送NAK握手包。 */
        unsigned int  EPType   : 2;  /* bit[18-19]: 端点类型。
                                                    00：control；
                                                    01：isochronous；
                                                    10：bulk；
                                                    11：interrupt。 */
        unsigned int  reserved_1: 1;  /* bit[20]   : 保留。 */
        unsigned int  Stall    : 1;  /* bit[21]   : Stall握手设置。
                                                    对于非control和非isochronous端点，使能该bit后，对所有的传输请求返回stall握手包。优先级比NAK设置高。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  TxFNum   : 4;  /* bit[22-25]: 对应该端点的发送FIFO序号。 */
        unsigned int  CNAK     : 1;  /* bit[26]   : 清除NAK设置。向该bit写1清除NAK设置。
                                                    0：不清除；
                                                    1：清除。 */
        unsigned int  SNAK     : 1;  /* bit[27]   : NAK设置。设置该bit后，即使发送FIFO有数据，硬件也不向外发送。并对接收到的setup包返回NAK握手。
                                                    0：根据FIFO状态发送握手包；
                                                    1：对该端点的传输请求一直发送NAK握手包。 */
        unsigned int  SetD0PID : 1;  /* bit[28]   : 设置数据包PID为data0。
                                                    0：不设置；
                                                    1：设置。 */
        unsigned int  SetD1PID : 1;  /* bit[29]   : 设置数据包PID为data1。
                                                    0：不设置；
                                                    1：设置。 */
        unsigned int  EPDis    : 1;  /* bit[30]   : 设置端点不使能。
                                                    0：不设置；
                                                    1：设置。 */
        unsigned int  EPEna    : 1;  /* bit[31]   : 设置端点使能。
                                                    0：不设置；
                                                    1：设置。 */
    } reg;
} SOC_OTG_DIEPCTLn_UNION;
#endif
#define SOC_OTG_DIEPCTLn_MPS_START       (0)
#define SOC_OTG_DIEPCTLn_MPS_END         (10)
#define SOC_OTG_DIEPCTLn_USBActEp_START  (15)
#define SOC_OTG_DIEPCTLn_USBActEp_END    (15)
#define SOC_OTG_DIEPCTLn_DPID_START      (16)
#define SOC_OTG_DIEPCTLn_DPID_END        (16)
#define SOC_OTG_DIEPCTLn_NAKSts_START    (17)
#define SOC_OTG_DIEPCTLn_NAKSts_END      (17)
#define SOC_OTG_DIEPCTLn_EPType_START    (18)
#define SOC_OTG_DIEPCTLn_EPType_END      (19)
#define SOC_OTG_DIEPCTLn_Stall_START     (21)
#define SOC_OTG_DIEPCTLn_Stall_END       (21)
#define SOC_OTG_DIEPCTLn_TxFNum_START    (22)
#define SOC_OTG_DIEPCTLn_TxFNum_END      (25)
#define SOC_OTG_DIEPCTLn_CNAK_START      (26)
#define SOC_OTG_DIEPCTLn_CNAK_END        (26)
#define SOC_OTG_DIEPCTLn_SNAK_START      (27)
#define SOC_OTG_DIEPCTLn_SNAK_END        (27)
#define SOC_OTG_DIEPCTLn_SetD0PID_START  (28)
#define SOC_OTG_DIEPCTLn_SetD0PID_END    (28)
#define SOC_OTG_DIEPCTLn_SetD1PID_START  (29)
#define SOC_OTG_DIEPCTLn_SetD1PID_END    (29)
#define SOC_OTG_DIEPCTLn_EPDis_START     (30)
#define SOC_OTG_DIEPCTLn_EPDis_END       (30)
#define SOC_OTG_DIEPCTLn_EPEna_START     (31)
#define SOC_OTG_DIEPCTLn_EPEna_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPINTm_UNION
 结构说明  : DIEPINTm 寄存器结构定义。地址偏移量:0x0908+0x20*(m)，初值:0x00000080，宽度:32
 寄存器说明: IN端点m中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferCompl   : 1;  /* bit[0]    : 传输完成中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  EPDisbld    : 1;  /* bit[1]    : 端点没有使能中断。指示对于软件的请求，该端点没有被使能。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  AHBErr      : 1;  /* bit[2]    : AHB错误中断。指示AHB总线错误。软件可以通过相应端点的DMA地址寄存器。得到出错的地址。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_0  : 1;  /* bit[3]    : 保留。 */
        unsigned int  INTknTXFEmp : 1;  /* bit[4]    : 接收到IN令牌时，发送FIFO空中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_1  : 1;  /* bit[5]    : 保留。 */
        unsigned int  INEPNakEff  : 1;  /* bit[6]    : NAK设置有效指示。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  TxFEmp      : 1;  /* bit[7]    : 发送FIFO空中断。指示发送FIFO半空或者全空。是指示半空还是全空状态，由GAHB[NPTxFEmpLvl]的配置值决定。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  TxfifoUndrn : 1;  /* bit[8]    : 发送FIFO下溢中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  BNAIntr     : 1;  /* bit[9]    : BNA(Buffer Not Available)中断。仅当Scatter/Gather DMA使能时有效。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_2  : 1;  /* bit[10]   : 保留。 */
        unsigned int  PktDrpSts   : 1;  /* bit[11]   : Packet Dropped Status (PktDrpSts) */
        unsigned int  BbleErr     : 1;  /* bit[12]   : Bable错误中断。 */
        unsigned int  NAKIntrpt   : 1;  /* bit[13]   : NAK中断。指示端点接收到NAK握手包。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  NYETIntrpt  : 1;  /* bit[14]   : NYET interrupt (NYETIntrpt) */
        unsigned int  StupPktRcvd : 1;  /* bit[15]   : Setup Packet Received 
                                                       0：No Setup packet received；
                                                       1：Setup packet received。 */
        unsigned int  reserved_3  : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_DIEPINTm_UNION;
#endif
#define SOC_OTG_DIEPINTm_XferCompl_START    (0)
#define SOC_OTG_DIEPINTm_XferCompl_END      (0)
#define SOC_OTG_DIEPINTm_EPDisbld_START     (1)
#define SOC_OTG_DIEPINTm_EPDisbld_END       (1)
#define SOC_OTG_DIEPINTm_AHBErr_START       (2)
#define SOC_OTG_DIEPINTm_AHBErr_END         (2)
#define SOC_OTG_DIEPINTm_INTknTXFEmp_START  (4)
#define SOC_OTG_DIEPINTm_INTknTXFEmp_END    (4)
#define SOC_OTG_DIEPINTm_INEPNakEff_START   (6)
#define SOC_OTG_DIEPINTm_INEPNakEff_END     (6)
#define SOC_OTG_DIEPINTm_TxFEmp_START       (7)
#define SOC_OTG_DIEPINTm_TxFEmp_END         (7)
#define SOC_OTG_DIEPINTm_TxfifoUndrn_START  (8)
#define SOC_OTG_DIEPINTm_TxfifoUndrn_END    (8)
#define SOC_OTG_DIEPINTm_BNAIntr_START      (9)
#define SOC_OTG_DIEPINTm_BNAIntr_END        (9)
#define SOC_OTG_DIEPINTm_PktDrpSts_START    (11)
#define SOC_OTG_DIEPINTm_PktDrpSts_END      (11)
#define SOC_OTG_DIEPINTm_BbleErr_START      (12)
#define SOC_OTG_DIEPINTm_BbleErr_END        (12)
#define SOC_OTG_DIEPINTm_NAKIntrpt_START    (13)
#define SOC_OTG_DIEPINTm_NAKIntrpt_END      (13)
#define SOC_OTG_DIEPINTm_NYETIntrpt_START   (14)
#define SOC_OTG_DIEPINTm_NYETIntrpt_END     (14)
#define SOC_OTG_DIEPINTm_StupPktRcvd_START  (15)
#define SOC_OTG_DIEPINTm_StupPktRcvd_END    (15)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTSIZ0_UNION
 结构说明  : DIEPTSIZ0 寄存器结构定义。地址偏移量:0x0910，初值:0x00000000，宽度:32
 寄存器说明: IN端点0传输大小寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 7;  /* bit[0-6]  : 传输大小。单位为byte。该域计数到0会触发传输完成中断。每有1个包的数据写入发送FIFO时，该域会减去包长并更新。 */
        unsigned int  reserved_0: 12; /* bit[7-18] : 保留。 */
        unsigned int  PktCnt   : 2;  /* bit[19-20]: 包数量。每有1个包从发送FIFO读出时，该域进行递减。 */
        unsigned int  reserved_1: 11; /* bit[21-31]: 保留。 */
    } reg;
} SOC_OTG_DIEPTSIZ0_UNION;
#endif
#define SOC_OTG_DIEPTSIZ0_XferSize_START  (0)
#define SOC_OTG_DIEPTSIZ0_XferSize_END    (6)
#define SOC_OTG_DIEPTSIZ0_PktCnt_START    (19)
#define SOC_OTG_DIEPTSIZ0_PktCnt_END      (20)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPTSIZn_UNION
 结构说明  : DIEPTSIZn 寄存器结构定义。地址偏移量:0x0910+0x20*(n)，初值:0x00000000，宽度:32
 寄存器说明: IN端点n传输大小寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 19; /* bit[0-18] : 传输大小。单位为byte。该域计数到0会触发传输完成中断。每有1个包的数据写入发送FIFO时，该域会减去包长并更新。 */
        unsigned int  PktCnt   : 10; /* bit[19-28]: 包数量。指示该传输的数据包个数，每有1个包从发送FIFO读出时，该域进行递减。 */
        unsigned int  MC       : 2;  /* bit[29-30]: 对于周期端点，该域指示每个微帧内必须传输的包数量。硬件根据该域的值产生IN数据包的PID。
                                                    对于非周期传输，该域指示切换到下1个端点前，当前端点必须传输的包数量。 */
        unsigned int  reserved : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_OTG_DIEPTSIZn_UNION;
#endif
#define SOC_OTG_DIEPTSIZn_XferSize_START  (0)
#define SOC_OTG_DIEPTSIZn_XferSize_END    (18)
#define SOC_OTG_DIEPTSIZn_PktCnt_START    (19)
#define SOC_OTG_DIEPTSIZn_PktCnt_END      (28)
#define SOC_OTG_DIEPTSIZn_MC_START        (29)
#define SOC_OTG_DIEPTSIZn_MC_END          (30)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPDMAm_UNION
 结构说明  : DIEPDMAm 寄存器结构定义。地址偏移量:0x0914+0x20*(m)，初值:0x00000000，宽度:32
 寄存器说明: IN端点m DMA地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMAADDR : 32; /* bit[0-31]: DMA地址。当Scatter/Gather使能时，该域描述符起始地址。必须32bit对齐。 */
    } reg;
} SOC_OTG_DIEPDMAm_UNION;
#endif
#define SOC_OTG_DIEPDMAm_DMAADDR_START  (0)
#define SOC_OTG_DIEPDMAm_DMAADDR_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_DTXFSTSm_UNION
 结构说明  : DTXFSTSm 寄存器结构定义。地址偏移量:0x0918，初值:0x00001000，宽度:32
 寄存器说明: IN端点m发送FIFO状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPTxFSpcAvail : 16; /* bit[0-15] : 发送FIFO可用空间，单位为32bit。 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_DTXFSTSm_UNION;
#endif
#define SOC_OTG_DTXFSTSm_INEPTxFSpcAvail_START  (0)
#define SOC_OTG_DTXFSTSm_INEPTxFSpcAvail_END    (15)


/*****************************************************************************
 结构名    : SOC_OTG_DIEPDMABn_UNION
 结构说明  : DIEPDMABn 寄存器结构定义。地址偏移量:0x091C+0x20*(m)，初值:0x00000000，宽度:32
 寄存器说明: IN端点m DMA buffer地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMABufferAddr : 32; /* bit[0-31]: DMA buffer地址。仅当Scatter/Gather使能时有效。指示当前buffer的地址。 */
    } reg;
} SOC_OTG_DIEPDMABn_UNION;
#endif
#define SOC_OTG_DIEPDMABn_DMABufferAddr_START  (0)
#define SOC_OTG_DIEPDMABn_DMABufferAddr_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_DOEPCTL0_UNION
 结构说明  : DOEPCTL0 寄存器结构定义。地址偏移量:0x0B00，初值:0x00008000，宽度:32
 寄存器说明: OUT端点0控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 2;  /* bit[0-1]  : 最大包大小。与IN端点0最大包长一样。 */
        unsigned int  reserved_0: 13; /* bit[2-14] : 保留。 */
        unsigned int  USBActEP : 1;  /* bit[15]   : 端点是否激活。该bit一直为1，表示端点0一直处于激活状态。 */
        unsigned int  reserved_1: 1;  /* bit[16]   : 保留。 */
        unsigned int  NAKSts   : 1;  /* bit[17]   : NAK状态。
                                                    0：根据FIFO状态发送握手包；
                                                    1：对该端点的传输请求一直发送NAK握手包。 */
        unsigned int  EPType   : 2;  /* bit[18-19]: 端点类型。一直为0，表示端点0是控制端点。 */
        unsigned int  Snp      : 1;  /* bit[20]   : 探听模式设置。使能该模式，硬件不检查OUT包，直接将接收到的数据写到memory中。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  Stall    : 1;  /* bit[21]   : STALL握手设置。软件配置该bit使能，硬件收到setup包会清除该bit。该bit使能，对该端点的请求一直响应STALL握手。该bit的优先级高于NAK设置。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  reserved_2: 4;  /* bit[22-25]: 保留。 */
        unsigned int  CNAK     : 1;  /* bit[26]   : 清除NAK设置。向该bit写1清除NAK设置。
                                                    0：不清除；
                                                    1：清除。 */
        unsigned int  SNAK     : 1;  /* bit[27]   : NAK设置。设置该bit后，硬件会丢弃所有接收到的数据，即使接收FIFO有空间。
                                                    0：根据FIFO状态发送握手包；
                                                    1：对该端点的传输请求一直发送NAK握手包。 */
        unsigned int  reserved_3: 2;  /* bit[28-29]: 保留。 */
        unsigned int  EPDis    : 1;  /* bit[30]   : 端点使能清除。
                                                    0：不清除；
                                                    1：清除。 */
        unsigned int  EPEna    : 1;  /* bit[31]   : 端点使能。软件在如下条件下会清除该位：控制传输setup阶段结束；端点使能清除；传输结束。
                                                    0：不使能；
                                                    1：使能。 */
    } reg;
} SOC_OTG_DOEPCTL0_UNION;
#endif
#define SOC_OTG_DOEPCTL0_MPS_START       (0)
#define SOC_OTG_DOEPCTL0_MPS_END         (1)
#define SOC_OTG_DOEPCTL0_USBActEP_START  (15)
#define SOC_OTG_DOEPCTL0_USBActEP_END    (15)
#define SOC_OTG_DOEPCTL0_NAKSts_START    (17)
#define SOC_OTG_DOEPCTL0_NAKSts_END      (17)
#define SOC_OTG_DOEPCTL0_EPType_START    (18)
#define SOC_OTG_DOEPCTL0_EPType_END      (19)
#define SOC_OTG_DOEPCTL0_Snp_START       (20)
#define SOC_OTG_DOEPCTL0_Snp_END         (20)
#define SOC_OTG_DOEPCTL0_Stall_START     (21)
#define SOC_OTG_DOEPCTL0_Stall_END       (21)
#define SOC_OTG_DOEPCTL0_CNAK_START      (26)
#define SOC_OTG_DOEPCTL0_CNAK_END        (26)
#define SOC_OTG_DOEPCTL0_SNAK_START      (27)
#define SOC_OTG_DOEPCTL0_SNAK_END        (27)
#define SOC_OTG_DOEPCTL0_EPDis_START     (30)
#define SOC_OTG_DOEPCTL0_EPDis_END       (30)
#define SOC_OTG_DOEPCTL0_EPEna_START     (31)
#define SOC_OTG_DOEPCTL0_EPEna_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DOEPCTLn_UNION
 结构说明  : DOEPCTLn 寄存器结构定义。地址偏移量:0x0B00+0x20*(n)，初值:0x00000000，宽度:32
 寄存器说明: OUT端点n控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 11; /* bit[0-10] : 最大包长。单位为字节。 */
        unsigned int  reserved : 4;  /* bit[11-14]: 保留。 */
        unsigned int  USBActEp : 1;  /* bit[15]   : 端点激活。
                                                    1：激活；
                                                    0：没有激活。 */
        unsigned int  DPID     : 1;  /* bit[16]   : 数据包PID状态。仅对intterupt和bulk传输有效。
                                                    0：DATA0；
                                                    1：DATA1。 */
        unsigned int  NAKSts   : 1;  /* bit[17]   : NAK状态。
                                                    0：根据FIFO状态发送握手包；
                                                    1：对该端点的传输请求一直发送NAK握手包。 */
        unsigned int  EPType   : 2;  /* bit[18-19]: 端点类型。
                                                    00：control；
                                                    01：isochronous；
                                                    10：bulk；
                                                    11：interrupt。 */
        unsigned int  Snp      : 1;  /* bit[20]   : 探听模式设置。使能该模式，硬件不检查OUT包，直接将接收到的数据写到memory中。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  Stall    : 1;  /* bit[21]   : Stall握手设置。
                                                    对于非control和非isochronous端点，使能该bit后，对所有的传输请求返回stall握手包。优先级比NAK设置高。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  TxFNum   : 4;  /* bit[22-25]: 对应该端点的发送FIFO序号。 */
        unsigned int  CNAK     : 1;  /* bit[26]   : 清除NAK设置。向该bit写1清除NAK设置。
                                                    0：不清除；
                                                    1：清除。 */
        unsigned int  SNAK     : 1;  /* bit[27]   : NAK设置。设置该bit后，硬件会丢弃所有接收到的数据，即使接收FIFO有空间。
                                                    0：根据FIFO状态发送握手包；
                                                    1：对该端点的传输请求一直发送NAK握手包。 */
        unsigned int  SetD0PID : 1;  /* bit[28]   : 设置数据包PID为data0。
                                                    0：不设置；
                                                    1：设置。 */
        unsigned int  SetD1PID : 1;  /* bit[29]   : 设置数据包PID为data1。
                                                    0：不设置；
                                                    1：设置。 */
        unsigned int  EPDis    : 1;  /* bit[30]   : 设置端点不使能。
                                                    0：不设置；
                                                    1：设置。 */
        unsigned int  EPEna    : 1;  /* bit[31]   : 设置端点使能。
                                                    0：不设置；
                                                    1：设置。 */
    } reg;
} SOC_OTG_DOEPCTLn_UNION;
#endif
#define SOC_OTG_DOEPCTLn_MPS_START       (0)
#define SOC_OTG_DOEPCTLn_MPS_END         (10)
#define SOC_OTG_DOEPCTLn_USBActEp_START  (15)
#define SOC_OTG_DOEPCTLn_USBActEp_END    (15)
#define SOC_OTG_DOEPCTLn_DPID_START      (16)
#define SOC_OTG_DOEPCTLn_DPID_END        (16)
#define SOC_OTG_DOEPCTLn_NAKSts_START    (17)
#define SOC_OTG_DOEPCTLn_NAKSts_END      (17)
#define SOC_OTG_DOEPCTLn_EPType_START    (18)
#define SOC_OTG_DOEPCTLn_EPType_END      (19)
#define SOC_OTG_DOEPCTLn_Snp_START       (20)
#define SOC_OTG_DOEPCTLn_Snp_END         (20)
#define SOC_OTG_DOEPCTLn_Stall_START     (21)
#define SOC_OTG_DOEPCTLn_Stall_END       (21)
#define SOC_OTG_DOEPCTLn_TxFNum_START    (22)
#define SOC_OTG_DOEPCTLn_TxFNum_END      (25)
#define SOC_OTG_DOEPCTLn_CNAK_START      (26)
#define SOC_OTG_DOEPCTLn_CNAK_END        (26)
#define SOC_OTG_DOEPCTLn_SNAK_START      (27)
#define SOC_OTG_DOEPCTLn_SNAK_END        (27)
#define SOC_OTG_DOEPCTLn_SetD0PID_START  (28)
#define SOC_OTG_DOEPCTLn_SetD0PID_END    (28)
#define SOC_OTG_DOEPCTLn_SetD1PID_START  (29)
#define SOC_OTG_DOEPCTLn_SetD1PID_END    (29)
#define SOC_OTG_DOEPCTLn_EPDis_START     (30)
#define SOC_OTG_DOEPCTLn_EPDis_END       (30)
#define SOC_OTG_DOEPCTLn_EPEna_START     (31)
#define SOC_OTG_DOEPCTLn_EPEna_END       (31)


/*****************************************************************************
 结构名    : SOC_OTG_DOEPINTm_UNION
 结构说明  : DOEPINTm 寄存器结构定义。地址偏移量:0x0B08+0x20*(m)，初值:0x00000000，宽度:32
 寄存器说明: OUT端点m中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferCompl   : 1;  /* bit[0]    : 传输完成中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  EPDisbld    : 1;  /* bit[1]    : 端点没有使能中断。指示对于软件的请求，该端点没有被使能。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  AHBErr      : 1;  /* bit[2]    : AHB错误中断。指示AHB总线错误。软件可以通过相应端点的DMA地址寄存器得到出错的地址。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_0  : 1;  /* bit[3]    : 保留。 */
        unsigned int  INTknTXFEmp : 1;  /* bit[4]    : 接收到IN令牌时，发送FIFO空中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_1  : 1;  /* bit[5]    : 保留。 */
        unsigned int  INEPNakEff  : 1;  /* bit[6]    : NAK设置有效指示。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_2  : 1;  /* bit[7]    : 保留。 */
        unsigned int  OutPktErr   : 1;  /* bit[8]    : OUT包错误。指示接收FIFO溢出或者OUT包有CRC错误。该bit仅水线使能时有效。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  BNAIntr     : 1;  /* bit[9]    : BNA(Buffer Not Available)中断。仅当Scatter/Gather DMA使能时有效。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  reserved_3  : 1;  /* bit[10]   : 保留。 */
        unsigned int  PktDrpSts   : 1;  /* bit[11]   : 包丢弃状态。指示有1个isochronous包被丢弃。该bit没有屏蔽位，且不会产生中断上报。仅当Scatter/Gather DMA模式不使能时有效。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  BbleErr     : 1;  /* bit[12]   : Bable错误中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  NAKIntrpt   : 1;  /* bit[13]   : NAK中断。指示端点接收到NAK握手包。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  NYET        : 1;  /* bit[14]   : NYET中断。该端点作为非isochronous端点时，NYET握手包发送会触发该中断。
                                                       0：无中断；
                                                       1：有中断。 */
        unsigned int  StupPktRcvd : 1;  /* bit[15]   : Setup Packet Received 
                                                       0：No Setup packet received；
                                                       1：Setup packet received。 */
        unsigned int  reserved_4  : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_DOEPINTm_UNION;
#endif
#define SOC_OTG_DOEPINTm_XferCompl_START    (0)
#define SOC_OTG_DOEPINTm_XferCompl_END      (0)
#define SOC_OTG_DOEPINTm_EPDisbld_START     (1)
#define SOC_OTG_DOEPINTm_EPDisbld_END       (1)
#define SOC_OTG_DOEPINTm_AHBErr_START       (2)
#define SOC_OTG_DOEPINTm_AHBErr_END         (2)
#define SOC_OTG_DOEPINTm_INTknTXFEmp_START  (4)
#define SOC_OTG_DOEPINTm_INTknTXFEmp_END    (4)
#define SOC_OTG_DOEPINTm_INEPNakEff_START   (6)
#define SOC_OTG_DOEPINTm_INEPNakEff_END     (6)
#define SOC_OTG_DOEPINTm_OutPktErr_START    (8)
#define SOC_OTG_DOEPINTm_OutPktErr_END      (8)
#define SOC_OTG_DOEPINTm_BNAIntr_START      (9)
#define SOC_OTG_DOEPINTm_BNAIntr_END        (9)
#define SOC_OTG_DOEPINTm_PktDrpSts_START    (11)
#define SOC_OTG_DOEPINTm_PktDrpSts_END      (11)
#define SOC_OTG_DOEPINTm_BbleErr_START      (12)
#define SOC_OTG_DOEPINTm_BbleErr_END        (12)
#define SOC_OTG_DOEPINTm_NAKIntrpt_START    (13)
#define SOC_OTG_DOEPINTm_NAKIntrpt_END      (13)
#define SOC_OTG_DOEPINTm_NYET_START         (14)
#define SOC_OTG_DOEPINTm_NYET_END           (14)
#define SOC_OTG_DOEPINTm_StupPktRcvd_START  (15)
#define SOC_OTG_DOEPINTm_StupPktRcvd_END    (15)


/*****************************************************************************
 结构名    : SOC_OTG_DOEPTSIZ0_UNION
 结构说明  : DOEPTSIZ0 寄存器结构定义。地址偏移量:0x0B10，初值:0x00000000，宽度:32
 寄存器说明: OUT端点0传输大小寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 7;  /* bit[0-6]  : 传输大小。单位为byte。该域计数到0会触发传输完成中断。每有1个包的数据从接收FIFO读出写入外部memory中时，该域会减去包长并更新。 */
        unsigned int  reserved_0: 12; /* bit[7-18] : 保留。 */
        unsigned int  PktCnt   : 1;  /* bit[19]   : 包数量。每有1个包写入接收FIFO中时，该域进行递减。 */
        unsigned int  reserved_1: 9;  /* bit[20-28]: 保留。 */
        unsigned int  SUPCnt   : 2;  /* bit[29-30]: setup包数量。该域指示能连续接收的setup包的数量。 */
        unsigned int  reserved_2: 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_OTG_DOEPTSIZ0_UNION;
#endif
#define SOC_OTG_DOEPTSIZ0_XferSize_START  (0)
#define SOC_OTG_DOEPTSIZ0_XferSize_END    (6)
#define SOC_OTG_DOEPTSIZ0_PktCnt_START    (19)
#define SOC_OTG_DOEPTSIZ0_PktCnt_END      (19)
#define SOC_OTG_DOEPTSIZ0_SUPCnt_START    (29)
#define SOC_OTG_DOEPTSIZ0_SUPCnt_END      (30)


/*****************************************************************************
 结构名    : SOC_OTG_DOEPTSIZn_UNION
 结构说明  : DOEPTSIZn 寄存器结构定义。地址偏移量:0x0B10+0x20*(n)，初值:0x00000000，宽度:32
 寄存器说明: OUT端点n传输大小寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 19; /* bit[0-18] : 传输大小。单位为byte。该域计数到0会触发传输完成中断。每有1个包的数据从接收FIFO读出写入外部memory中时，该域会减去包长并更新。 */
        unsigned int  PktCnt   : 10; /* bit[19-28]: 包数量。每有1个包写入接收FIFO中时，该域进行递减。 */
        unsigned int  RxDPID   : 2;  /* bit[29-30]: 对于isochronous端点，指示接收到的数据包PID。
                                                    00：DATA0；
                                                    01：DATA1；
                                                    10：DATA2；
                                                    11：MDATA。
                                                    对于控制端点，指示可以接收的背靠背setup包个数。
                                                    00：reserved；
                                                    01：1个；
                                                    10：2个；
                                                    11：3个。 */
        unsigned int  reserved : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_OTG_DOEPTSIZn_UNION;
#endif
#define SOC_OTG_DOEPTSIZn_XferSize_START  (0)
#define SOC_OTG_DOEPTSIZn_XferSize_END    (18)
#define SOC_OTG_DOEPTSIZn_PktCnt_START    (19)
#define SOC_OTG_DOEPTSIZn_PktCnt_END      (28)
#define SOC_OTG_DOEPTSIZn_RxDPID_START    (29)
#define SOC_OTG_DOEPTSIZn_RxDPID_END      (30)


/*****************************************************************************
 结构名    : SOC_OTG_DOEPDMAm_UNION
 结构说明  : DOEPDMAm 寄存器结构定义。地址偏移量:0x0B14+0x20*(m)，初值:0x00000000，宽度:32
 寄存器说明: OUT端点m DMA地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMAAddr : 32; /* bit[0-31]: DMA地址。当Scatter/Gather使能时，该域为描述符起始地址。 */
    } reg;
} SOC_OTG_DOEPDMAm_UNION;
#endif
#define SOC_OTG_DOEPDMAm_DMAAddr_START  (0)
#define SOC_OTG_DOEPDMAm_DMAAddr_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_DOEPDMABm_UNION
 结构说明  : DOEPDMABm 寄存器结构定义。地址偏移量:0x0B1C+0x20*(m)，初值:0x00000000，宽度:32
 寄存器说明: OUT端点m DMA buffer地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMABufferAddr : 32; /* bit[0-31]: DMA buffer地址。仅当Scatter/Gather使能时有效。指示当前buffer的地址。 */
    } reg;
} SOC_OTG_DOEPDMABm_UNION;
#endif
#define SOC_OTG_DOEPDMABm_DMABufferAddr_START  (0)
#define SOC_OTG_DOEPDMABm_DMABufferAddr_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_PCGCCTL_UNION
 结构说明  : PCGCCTL 寄存器结构定义。地址偏移量:0x0E00，初值:0xA80A8000，宽度:32
 寄存器说明: 功耗和时钟门控控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  StopPclk                 : 1;  /* bit[0]    : 关断PHY时钟。当USB处于suspend状态或者会话无效时，软件可以通过设置该bit关断PHY时钟。USB进入resume状态或者新的会话开始时，软件需要清除该bit。
                                                                    0：不关断PHY时钟；
                                                                    1：关断PHY时钟。 */
        unsigned int  GateHclk                 : 1;  /* bit[1]    : 关断总线时钟。当USB处于suspend状态或者会话无效时，软件可以通过设置该bit关断总线时钟。USB进入resume状态或者新的会话开始时，软件需要清除该bit。
                                                                    0：不关断总线时钟；
                                                                    1：关断总线时钟。 */
        unsigned int  PwrClmp                  : 1;  /* bit[2]    : 信号箝制控制。在掉电域掉电之前，软件需要配置该bit，使穿越电源域的信号箝制在固定状态；软件需要在重现上电之前清除该bit。
                                                                    0：信号不箝制；
                                                                    1：信号箝制。 */
        unsigned int  RstPdenModule            : 1;  /* bit[3]    : 掉电域复位控制。软件在掉电之前配置该bit，在重新上电之后，且PHY时钟稳定之后清除该bit。
                                                                    0：清除掉电域复位；
                                                                    1：对掉电域复位。 */
        unsigned int  reserved                 : 1;  /* bit[4]    : 保留。 */
        unsigned int  Enbl_L1Gating            : 1;  /* bit[5]    : L1状态时钟门控使能。该bit使能后，进入L1状态，内部关断PHY时钟。
                                                                    0：不使能；
                                                                    1：使能。 */
        unsigned int  PhySleep                 : 1;  /* bit[6]    : sleep状态指示。指示PHY处于sleep状态。
                                                                    0：不处于sleep状态；
                                                                    1：处于sleep状态。 */
        unsigned int  L1_suspended             : 1;  /* bit[7]    : 指示当进入L1状态时，PHY进入deep sleep状态。
                                                                    0：不处于deep sleep状态；
                                                                    1：处于deep sleep状态。 */
        unsigned int  ResetAfterSusp           : 1;  /* bit[8]    : 进入suspend状态之后复位控制。
                                                                    0：不复位；
                                                                    1：复位。 */
        unsigned int  RestoreMode              : 1;  /* bit[9]    : 恢复模式。
                                                                    对于host模式：
                                                                    0：Host发起resume操作和复位操作；
                                                                    1：device发起远程唤醒操作。
                                                                    对于device模式：
                                                                    0：device发起远程唤醒操作；
                                                                    1：host发起resume操作和复位操作。 */
        unsigned int  EnExtndedHibernation     : 1;  /* bit[10]   : Enable Extended Hibernation
                                                                    0：Extended Hibernation feature不使能
                                                                    1：Extended Hibernation feature使能 */
        unsigned int  ExtndedHibernationClamp  : 1;  /* bit[11]   : Extended Hibernation Clamp 
                                                                    0：Extended hibernation Clamp不使能
                                                                    1：Extended hibernation Clamp使能 */
        unsigned int  ExtndedHibernationSwitch : 1;  /* bit[12]   : Extended Hibernation Switch
                                                                    0：Extended hibernation power开关不使能
                                                                    1：Extended hibernation power开关使能 */
        unsigned int  EssRegRestored           : 1;  /* bit[13]   : 重要寄存器恢复。
                                                                    写1表示重要寄存器值已经恢复。 */
        unsigned int  RestoreValue             : 18; /* bit[14-31]: 恢复值。
                                                                    Bit[31]：device模式。
                                                                    0：host模式；
                                                                    1：device模式。
                                                                    Bit[30:29]；端口速度。
                                                                    00：高速；
                                                                    01：全速；
                                                                    others：reserved。
                                                                    Bit[26:20]：device地址。
                                                                    Bit[19]：mac_termselect。 
                                                                    0：HS_TERM；
                                                                    1：FS_TERM。
                                                                    Bit[18:17]：mac_xcvrselect。
                                                                    00：HS_XCVR；
                                                                    01：FS_XCVR；
                                                                    10：LS_XCVR；
                                                                    11：LFS_XCVR。
                                                                    Bit[16]：端口电源控制。
                                                                    0：端口电源不使能；
                                                                    1：端口电源使能。
                                                                    bit[15:14]：prt_clk_sel。 */
    } reg;
} SOC_OTG_PCGCCTL_UNION;
#endif
#define SOC_OTG_PCGCCTL_StopPclk_START                  (0)
#define SOC_OTG_PCGCCTL_StopPclk_END                    (0)
#define SOC_OTG_PCGCCTL_GateHclk_START                  (1)
#define SOC_OTG_PCGCCTL_GateHclk_END                    (1)
#define SOC_OTG_PCGCCTL_PwrClmp_START                   (2)
#define SOC_OTG_PCGCCTL_PwrClmp_END                     (2)
#define SOC_OTG_PCGCCTL_RstPdenModule_START             (3)
#define SOC_OTG_PCGCCTL_RstPdenModule_END               (3)
#define SOC_OTG_PCGCCTL_Enbl_L1Gating_START             (5)
#define SOC_OTG_PCGCCTL_Enbl_L1Gating_END               (5)
#define SOC_OTG_PCGCCTL_PhySleep_START                  (6)
#define SOC_OTG_PCGCCTL_PhySleep_END                    (6)
#define SOC_OTG_PCGCCTL_L1_suspended_START              (7)
#define SOC_OTG_PCGCCTL_L1_suspended_END                (7)
#define SOC_OTG_PCGCCTL_ResetAfterSusp_START            (8)
#define SOC_OTG_PCGCCTL_ResetAfterSusp_END              (8)
#define SOC_OTG_PCGCCTL_RestoreMode_START               (9)
#define SOC_OTG_PCGCCTL_RestoreMode_END                 (9)
#define SOC_OTG_PCGCCTL_EnExtndedHibernation_START      (10)
#define SOC_OTG_PCGCCTL_EnExtndedHibernation_END        (10)
#define SOC_OTG_PCGCCTL_ExtndedHibernationClamp_START   (11)
#define SOC_OTG_PCGCCTL_ExtndedHibernationClamp_END     (11)
#define SOC_OTG_PCGCCTL_ExtndedHibernationSwitch_START  (12)
#define SOC_OTG_PCGCCTL_ExtndedHibernationSwitch_END    (12)
#define SOC_OTG_PCGCCTL_EssRegRestored_START            (13)
#define SOC_OTG_PCGCCTL_EssRegRestored_END              (13)
#define SOC_OTG_PCGCCTL_RestoreValue_START              (14)
#define SOC_OTG_PCGCCTL_RestoreValue_END                (31)






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

#endif /* end of soc_otg_interface.h */
