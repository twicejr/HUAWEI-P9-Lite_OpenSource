/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_ddrc_qosb_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:19:52
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DDRC_QOSB.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DDRC_QOSB_INTERFACE_H__
#define __SOC_DDRC_QOSB_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_DDRC_QOSB
 ****************************************************************************/
/* 寄存器说明：QOS_PUSH_CTRL是配置QosBuf Push功能的寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_PUSH_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_ADDR(base)       ((base) + (0x000))

/* 寄存器说明：QOS_ADPT_CTRL是配置QosBuf的adpt功能。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_ADPT_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_ADDR(base)       ((base) + (0x004))

/* 寄存器说明：QOS_FLUX_ID是QosBuf的流量匹配ID。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_FLUX_ID_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_ADDR(base, fids)   ((base) + (0x008+0x4*(fids)))

/* 寄存器说明：QOS_FLUX_ID_MASK是QosBuf的流量统计的ID的Mask寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_ADDR(base, fids)  ((base) + (0x024+0x4*(fids)))

/* 寄存器说明：QOS_FLUX_PRD是QosBuf的流量统计周期寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_FLUX_BDW_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_ADDR(base, fgps)  ((base) + (0x040+0x4*(fgps)))

/* 寄存器说明：QOS_FLUX_LVL是QosBuf的流量统计水线。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_FLUX_LVL_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_ADDR(base)        ((base) + (0x060))

/* 寄存器说明：QOS_FLUX_EN是QosBuf的流量统计功能使能寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_FLUX_EN_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_ADDR(base)         ((base) + (0x064))

/* 寄存器说明：QOS_BANK_CTRL是QosBuf的bank rotating控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_BANK_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ADDR(base, chans)  ((base) + (0x068+0x4*(chans)))

/* 寄存器说明：QOS_GREEN_CTRL是QosBuf的绿色通道控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_GREEN_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_ADDR(base, chans)  ((base) + (0x078+0x4*(chans)))

/* 寄存器说明：QOS_BUF_BYP是QosBuf的bypass功能控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION */
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_ADDR(base)         ((base) + (0x088))

/* 寄存器说明：QOS_WBUF_CTRL是QosBuf的写命令优先级调整控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WBUF_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_ADDR(base, chans)  ((base) + (0x08C+0x4*(chans)))

/* 寄存器说明：QOSB_WRTOUT是QosBuf的写命令timeout配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRTOUT0_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_ADDR(base)         ((base) + (0x09C))

/* 寄存器说明：QOSB_WRTOUT是QosBuf的写命令timeout配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRTOUT1_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_ADDR(base)         ((base) + (0x0A0))

/* 寄存器说明：QOSB_WRTOUT是QosBuf的写命令timeout配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRTOUT2_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_ADDR(base)         ((base) + (0x0A4))

/* 寄存器说明：QOSB_WRTOUT是QosBuf的写命令timeout配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRTOUT3_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_ADDR(base)         ((base) + (0x0A8))

/* 寄存器说明：QOSB_RDTOUT是QosBuf的读命令timeout配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDTOUT0_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_ADDR(base)         ((base) + (0x0AC))

/* 寄存器说明：QOSB_RDTOUT是QosBuf的读命令timeout配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDTOUT1_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_ADDR(base)         ((base) + (0x0B0))

/* 寄存器说明：QOSB_RDTOUT是QosBuf的读命令timeout配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDTOUT2_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_ADDR(base)         ((base) + (0x0B4))

/* 寄存器说明：QOSB_RDTOUT是QosBuf的读命令timeout配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDTOUT3_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_ADDR(base)         ((base) + (0x0B8))

/* 寄存器说明：QOSB_WRTOUT是QosBuf的写命令timeout映射控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_ADDR(base)      ((base) + (0x0BC))

/* 寄存器说明：QOSB_RDTOUT是QosBuf的读命令timeout映射控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_ADDR(base)      ((base) + (0x0D0))

/* 寄存器说明：QOSB_WRTAGE是QosBuf的写命令aging配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRAGE0_UNION */
#define SOC_DDRC_QOSB_QOSB_WRAGE0_ADDR(base)          ((base) + (0x0D4))

/* 寄存器说明：QOSB_WRTAGE是QosBuf的写命令aging配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRAGE1_UNION */
#define SOC_DDRC_QOSB_QOSB_WRAGE1_ADDR(base)          ((base) + (0x0D8))

/* 寄存器说明：QOSB_WRTAGE是QosBuf的读命令aging配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDAGE0_UNION */
#define SOC_DDRC_QOSB_QOSB_RDAGE0_ADDR(base)          ((base) + (0x0DC))

/* 寄存器说明：QOSB_WRTAGE是QosBuf的读命令aging配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDAGE1_UNION */
#define SOC_DDRC_QOSB_QOSB_RDAGE1_ADDR(base)          ((base) + (0x0E0))

/* 寄存器说明：QOSB_WRAGE_MAP是QosBuf的写命令aging映射控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRAGE_MAP_UNION */
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_ADDR(base)       ((base) + (0x0E4))

/* 寄存器说明：QOSB_RDAGE_MAP是QosBuf的读命令aging映射控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDAGE_MAP_UNION */
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_ADDR(base)       ((base) + (0x0E8))

/* 寄存器说明：QOSB_ROWHIT_PRILVL是QosBuf的row hit优先级水线寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_UNION */
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ADDR(base)   ((base) + (0x0EC))

/* 寄存器说明：QOSB_ROWHIT_PRI是QosBuf的row hit优先级控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_UNION */
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ADDR(base)      ((base) + (0x0F0))

/* 寄存器说明：QOS_ROWHIT_CTRL是QosBuf的row hit的使能控制。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ADDR(base)     ((base) + (0x0F4))

/* 寄存器说明：QOS_WRAM_CTRL是QosBuf的write buf的ram控制。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WRAM_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ADDR(base)       ((base) + (0x0F8))

/* 寄存器说明：QOS_CRAM_CTRL是QosBuf CID的RAM控制。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_CRAM_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_ADDR(base)       ((base) + (0x0FC))

/* 寄存器说明：QOS_RDRRAM_CTRL是QosBuf的write buf的ram控制。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ADDR(base)     ((base) + (0x100))

/* 寄存器说明：QOS_RAM_TMOD是QosBuf/RDR的RAM的端口配置信号寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RAM_TMOD_UNION */
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ADDR(base)        ((base) + (0x104))

/* 寄存器说明：QOS_CKG_CFG是QosBuf的时钟控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_CKG_CFG_UNION */
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_ADDR(base)         ((base) + (0x108))

/* 寄存器说明：QOSB_DMC_LVL是QosBuf的进入DMC的命令的线控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_DMC_LVL_UNION */
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_ADDR(base, chans)  ((base) + (0x10C+0x4*(chans)))

/* 寄存器说明：QOSB_CFG_PERF是QosBuf性能统计的模式配置寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_CFG_PERF_UNION */
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR(base)        ((base) + (0x120))

/* 寄存器说明：QOSB_CMD_SUM是QosBuf命令计数的累积寄存器
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_CMD_SUM_UNION */
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_ADDR(base)         ((base) + (0x124))

/* 寄存器说明：QOSB_SLOT_STAT0是QosBuf的queue的状态寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_SLOT_STAT0_UNION */
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_ADDR(base)      ((base) + (0x128))

/* 寄存器说明：QOSB_SLOT_STAT0是QosBuf的queue的状态寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_SLOT_STAT1_UNION */
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_ADDR(base)      ((base) + (0x12C))

/* 寄存器说明：QOSB_SLOT_STAT0是QosBuf的queue的状态寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_SLOT_STAT2_UNION */
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_ADDR(base)      ((base) + (0x130))

/* 寄存器说明：QOSB_SLOT_STAT0是QosBuf的queue的状态寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_SLOT_STAT3_UNION */
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_ADDR(base)      ((base) + (0x134))

/* 寄存器说明：QOSB_WBUF_STAT0是QosBuf的写buf状态寄存器
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WBUF_STAT0_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_ADDR(base, chans)  ((base) + (0x140+0x4*(chans)))

/* 寄存器说明：QOSB_WBUF_STAT1是QosBuf的写buf状态寄存器
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WBUF_STAT1_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_ADDR(base, chans)  ((base) + (0x150+0x4*(chans)))

/* 寄存器说明：QOSB_RDRBUF_STAT是Reorder模块的buf状态寄存器
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_UNION */
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_ADDR(base, chans)  ((base) + (0x160+0x4*(chans)))

/* 寄存器说明：QOSB_INTMSK是QosBuf中断屏蔽寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_INTMSK_UNION */
#define SOC_DDRC_QOSB_QOSB_INTMSK_ADDR(base)          ((base) + (0x170))

/* 寄存器说明：QOSB_RINT是QosBuf原始中断寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RINT_UNION */
#define SOC_DDRC_QOSB_QOSB_RINT_ADDR(base)            ((base) + (0x174))

/* 寄存器说明：QOSB_INTSTS是QOSBUF中断状态寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_INTSTS_UNION */
#define SOC_DDRC_QOSB_QOSB_INTSTS_ADDR(base)          ((base) + (0x178))

/* 寄存器说明：QOSB_CMD_CNT是QOSBUF中当前有多少命令的统计寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_CMD_CNT_UNION */
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_ADDR(base)         ((base) + (0x180))

/* 寄存器说明：QOSB_RNK_CNT是QOSBUF中当前每个rank中有多少命令的统计寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RNK_CNT_UNION */
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_ADDR(base, chans)  ((base) + (0x190+0x4*(chans)))

/* 寄存器说明：QOSB_BNK_CNT0是QOSBUF中当前每个Bank有多少命令的统计寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_BNK_CNT0_UNION */
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_ADDR(base, chans)  ((base) + (0x1A0+0x4*(chans)))

/* 寄存器说明：QOSB_BNK_CNT1是QOSBUF中当前每个Bank有多少命令的统计寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_BNK_CNT1_UNION */
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_ADDR(base, chans)  ((base) + (0x1B0+0x4*(chans)))

/* 寄存器说明：QOSB_BNK_CNT2是QOSBUF中当前每个Bank有多少命令的统计寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_BNK_CNT2_UNION */
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_ADDR(base, chans)  ((base) + (0x1C0+0x4*(chans)))

/* 寄存器说明：QOSB_BNK_CNT3是QOSBUF中当前每个Bank有多少命令的统计寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_BNK_CNT3_UNION */
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_ADDR(base, chans)  ((base) + (0x1D0+0x4*(chans)))

/* 寄存器说明：QOSB_OSTD_CNT是QOSBUF中当前每个通道有多少Oustanding命令的统计寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_OSTD_CNT_UNION */
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ADDR(base)        ((base) + (0x1E0))

/* 寄存器说明：QOSB_CMD_SUM是QosBuf写命令计数的累积寄存器
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_UNION */
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_ADDR(base)      ((base) + (0x1E4))

/* 寄存器说明：QOSB_CMD_SUM是QosBuf读命令计数的累积寄存器
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_UNION */
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_ADDR(base)      ((base) + (0x1E8))

/* 寄存器说明：QOSB_GRT_FIFO_STATUS是写数据汇聚MUX对应的grant fifo的状态寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_UNION */
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_ADDR(base) ((base) + (0x1EC))

/* 寄存器说明：QOSB_TIMEOUT_MODE是QOSBUF中timeout模式选择寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_UNION */
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_ADDR(base)    ((base) + (0x1F0))

/* 寄存器说明：QOSB_WBUF_PRI_CTRL是QOSBUF中写wbuf优先级调整控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_ADDR(base)   ((base) + (0x1F4))

/* 寄存器说明：QOSB_RHIT_CTRL是QOSBUF中rowhit优先级调整控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_RHIT_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_ADDR(base)       ((base) + (0x1F8))

/* 寄存器说明：QOSB_WBUF_MERG_CTRL是QOSBUF双通道写buf合并控制寄存器。
   位域定义UNION结构:  SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ADDR(base)  ((base) + (0x1FC))





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
                     (1/1) register_DDRC_QOSB
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_PUSH_CTRL_UNION
 结构说明  : QOSB_PUSH_CTRL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: QOS_PUSH_CTRL是配置QosBuf Push功能的寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_push_en   : 1;  /* bit[0]   : 同ID的push使能。
                                                       0：push功能关闭；
                                                       1：push功能使能。 */
        unsigned int  addr_push_en : 1;  /* bit[1]   : 同地址的push使能。
                                                       0：push功能关闭；
                                                       1：push功能使能。 */
        unsigned int  mid_push_en  : 1;  /* bit[2]   : 同mid的push使能。
                                                       0：push功能关闭；
                                                       1：push功能使能。 */
        unsigned int  reserved     : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_PUSH_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_id_push_en_START    (0)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_id_push_en_END      (0)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_addr_push_en_START  (1)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_addr_push_en_END    (1)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_mid_push_en_START   (2)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_mid_push_en_END     (2)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_ADPT_CTRL_UNION
 结构说明  : QOSB_ADPT_CTRL 寄存器结构定义。地址偏移量:0x004，初值:0x00000FF0，宽度:32
 寄存器说明: QOS_ADPT_CTRL是配置QosBuf的adpt功能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adpt_en        : 1;  /* bit[0]    : Adapt功能使能控制。
                                                          0：adapt功能关闭；
                                                          1：adapt功能打开。 */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : 保留。 */
        unsigned int  adpt_share_cnt : 16; /* bit[4-19] : Adapt功能的低位共享计数器。当该计数器递减为0时，每个cmd对应的高位计数器减1。 */
        unsigned int  reserved_1     : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_ADPT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_en_START         (0)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_en_END           (0)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_share_cnt_START  (4)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_share_cnt_END    (19)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_FLUX_ID_UNION
 结构说明  : QOSB_FLUX_ID 寄存器结构定义。地址偏移量:0x008+0x4*(fids)，初值:0x00000000，宽度:32
 寄存器说明: QOS_FLUX_ID是QosBuf的流量匹配ID。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_id : 32; /* bit[0-31]: 用于流量统计的匹配ID，一共有0~6个ID，每个ID对应一个统计组；如果与这7个ID都不相同，则将流量归入默认的一组。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_ID_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_flux_id_START  (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_flux_id_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_UNION
 结构说明  : QOSB_FLUX_ID_MASK 寄存器结构定义。地址偏移量:0x024+0x4*(fids)，初值:0x00000000，宽度:32
 寄存器说明: QOS_FLUX_ID_MASK是QosBuf的流量统计的ID的Mask寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_id_mask : 32; /* bit[0-31]: 与QOS_FLUX_ID寄存器对应，用于ID的MASK。
                                                       0：表示对应的ID的bit被忽略；
                                                       1：表示对应的ID的bit参与比较。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_flux_id_mask_START  (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_flux_id_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_FLUX_BDW_UNION
 结构说明  : QOSB_FLUX_BDW 寄存器结构定义。地址偏移量:0x040+0x4*(fgps)，初值:0x00000000，宽度:32
 寄存器说明: QOS_FLUX_PRD是QosBuf的流量统计周期寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_bandwidth : 9;  /* bit[0-8] : 允许平均带宽：
                                                         配置值=允许平均带宽(Beats/Hz)*256=允许带宽(MB/DMC_WIDTH/s)/工作频率（MHz）*256
                                                         例如：工作频率为400MHz，当前端口的允许带宽为1400MB/s，DMC_WIDTH=16byte，则带宽配置值为1400/16/400*256=56=0x38
                                                         说明：
                                                         1.乘256的目的是保留允许平均带宽的高8位小数；
                                                         2.控制后的瞬时带宽可能会超过允许带宽，超过的范围取决于带宽容限的配置；
                                                         3.控制后的长时间平均带宽小于等于允许平均带宽。 */
        unsigned int  reserved       : 23; /* bit[9-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_BDW_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_flux_bandwidth_START  (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_flux_bandwidth_END    (8)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_FLUX_LVL_UNION
 结构说明  : QOSB_FLUX_LVL 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: QOS_FLUX_LVL是QosBuf的流量统计水线。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_lvl : 20; /* bit[0-19] : 带宽容限：
                                                    配置值=带宽容限(Beats)；
                                                    说明：
                                                    可以将本带宽控制方式等效成基于滑动窗口的流量控制，带宽容限决定了滑窗宽度以及滑窗内的允许流量：带宽容限(Beats)/允许平均带宽(Beats/Hz)=滑窗宽度（cycle）。即在配置的允许平均带宽固定的情况下，带宽容限越大，滑窗越宽，对控制前的瞬时带宽变化越不敏感，长时间控制后的平均带宽也越接近配置的允许平均带宽，但控制后的瞬时带宽的变化也可能会越剧烈。
                                                    当带宽统计计数器大于带宽容限时，则将相应的命令的优先级改为最低；当小于带宽空限时，则优先级维持不变。 */
        unsigned int  reserved : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_LVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_flux_lvl_START  (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_flux_lvl_END    (19)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_FLUX_EN_UNION
 结构说明  : QOSB_FLUX_EN 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: QOS_FLUX_EN是QosBuf的流量统计功能使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_en  : 1;  /* bit[0]   : 流量统计功能使能。
                                                   0：表示流量统计功能关闭；
                                                   1：表示流量统计功能使能。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_EN_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_flux_en_START   (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_flux_en_END     (0)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_BANK_CTRL_UNION
 结构说明  : QOSB_BANK_CTRL 寄存器结构定义。地址偏移量:0x068+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOS_BANK_CTRL是QosBuf的bank rotating控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ba_intleav_en : 1;  /* bit[0]   : QosBuf的bank rotating使能控制。
                                                        0：Bank rotating功能关闭
                                                        1：Bank rotating功能使能 */
        unsigned int  reserved_0    : 3;  /* bit[1-3] :  */
        unsigned int  ba_cnt_lvl    : 4;  /* bit[4-7] : Bank冲突水线配置，当每个bank的命令高于该水线时，认为有bank冲突。否则认为没有bank冲突。 */
        unsigned int  reserved_1    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_BANK_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_intleav_en_START  (0)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_intleav_en_END    (0)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_cnt_lvl_START     (4)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_cnt_lvl_END       (7)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_GREEN_CTRL_UNION
 结构说明  : QOSB_GREEN_CTRL 寄存器结构定义。地址偏移量:0x078+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOS_GREEN_CTRL是QosBuf的绿色通道控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  green_en  : 1;  /* bit[0]   : 绿色通道功能使能。（注意，这里没有将通道分开控制，后续需要优化）
                                                    0：表示该功能关闭；
                                                    1：表示该功能使能。 */
        unsigned int  reserved_0: 3;  /* bit[1-3] : 保留。 */
        unsigned int  green_lvl : 4;  /* bit[4-7] : 绿色通道水线。即在该水线以上的空位给绿色通道预留。如dmc的queue为12，水线设为9，则10，11为绿色通道预留。
                                                    注意：由于流水的问题，当配置为N时，实际通过的命令个数为N+1。另外，该寄存器不能在访问过程中进行动态配置。 */
        unsigned int  reserved_1: 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_GREEN_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_en_START   (0)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_en_END     (0)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_lvl_START  (4)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_lvl_END    (7)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION
 结构说明  : QOSB_BUF_BYP 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: QOS_BUF_BYP是QosBuf的bypass功能控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_buf_byp : 2;  /* bit[0-1] : Qos buf的bypass控制。
                                                      X0：表示强制非bypass，即配成00或10时，所有命令都要进入qosbuf；
                                                      01：表示根据dmc中queue的状态，自动控制是否bypass；
                                                      11：表示强制byapss，所有命令都不进入qosbuf
                                                      （注意：这些模式在访问开始之前就需要配置，而不能在访问过程中进行动态配置） */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_qos_buf_byp_START  (0)
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_qos_buf_byp_END    (1)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WBUF_CTRL_UNION
 结构说明  : QOSB_WBUF_CTRL 寄存器结构定义。地址偏移量:0x08C+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOS_WBUF_CTRL是QosBuf的写命令优先级调整控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wbuf_lvl0    : 8;  /* bit[0-7]  : wbuf的水线0。当命令的个数由上往下穿过该水线时，所有写命令的优先级都会被降为最低。（注意，这个水线不能动态配置，否则可能导致写buf自适应功能失效） */
        unsigned int  wbuf_lvl1    : 8;  /* bit[8-15] : wbuf的水线1。当命令的个数由下往上穿过该水线，或由上往下穿过该水线，则所有写命令的优先级如果低于wbuf_pri1，则将其配置为wbuf_pri1；如果高于wbuf_pri1，则将优先级恢复。（注意，这个水线不能动态配置，否则可能导致写buf自适应功能失效） */
        unsigned int  wbuf_pri1    : 3;  /* bit[16-18]: wbuf的水线1对应的优先级。 */
        unsigned int  reserved     : 1;  /* bit[19]   : 保留。 */
        unsigned int  wbuf_lvl2    : 8;  /* bit[20-27]: wbuf的水线2。当命令的个数由下往上穿过该水线，则所有写命令的优先级如果低于wbuf_pri2，则将其配置为wbuf_pri2；如果高于wbuf_pri2，则将优先级恢复。（注意，这个水线不能动态配置，否则可能导致写buf自适应功能失效） */
        unsigned int  wbuf_pri2    : 3;  /* bit[28-30]: wbuf的水线2对应的优先级。 */
        unsigned int  wbuf_ptun_en : 1;  /* bit[31]   : 写优调级调整使能。
                                                        0：表示该功能关闭；
                                                        1：表示该功能使能。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl0_START     (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl0_END       (7)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl1_START     (8)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl1_END       (15)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri1_START     (16)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri1_END       (18)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl2_START     (20)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl2_END       (27)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri2_START     (28)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri2_END       (30)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_ptun_en_START  (31)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_ptun_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRTOUT0_UNION
 结构说明  : QOSB_WRTOUT0 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTOUT是QosBuf的写命令timeout配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_tout0 : 8;  /* bit[0-7]  : 写命令timeout配置（档位0）。
                                                    0x0：禁止timeout功能；
                                                    0x1～0xFF：n*4个时钟周期；
                                                    注意：
                                                    timeout配置为8bits，但实际计数为10bits，即低两位固定为零。 */
        unsigned int  wr_tout1 : 8;  /* bit[8-15] : 写命令timeout配置（档位1）。
                                                    配置方式同wr_tout0。 */
        unsigned int  wr_tout2 : 8;  /* bit[16-23]: 写命令timeout配置（档位2）。
                                                    配置方式同wr_tout0。 */
        unsigned int  wr_tout3 : 8;  /* bit[24-31]: 写命令timeout配置（档位3）。
                                                    配置方式同wr_tout0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout0_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout0_END    (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout1_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout1_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout2_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout2_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout3_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRTOUT1_UNION
 结构说明  : QOSB_WRTOUT1 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTOUT是QosBuf的写命令timeout配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_tout4 : 8;  /* bit[0-7]  : 写命令timeout配置（档位4）。
                                                    配置方式同wr_tout0。 */
        unsigned int  wr_tout5 : 8;  /* bit[8-15] : 写命令timeout配置（档位5）。
                                                    配置方式同wr_tout0。 */
        unsigned int  wr_tout6 : 8;  /* bit[16-23]: 写命令timeout配置（档位6）。
                                                    配置方式同wr_tout0。 */
        unsigned int  wr_tout7 : 8;  /* bit[24-31]: 写命令timeout配置（档位7）。
                                                    配置方式同wr_tout0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout4_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout4_END    (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout5_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout5_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout6_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout6_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout7_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRTOUT2_UNION
 结构说明  : QOSB_WRTOUT2 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTOUT是QosBuf的写命令timeout配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_tout8  : 8;  /* bit[0-7]  : 写命令timeout配置（档位8）。
                                                     配置方式同wr_tout0。 */
        unsigned int  wr_tout9  : 8;  /* bit[8-15] : 写命令timeout配置（档位9）。
                                                     配置方式同wr_tout0。 */
        unsigned int  wr_tout10 : 8;  /* bit[16-23]: 写命令timeout配置（档位10）。
                                                     配置方式同wr_tout0。 */
        unsigned int  wr_tout11 : 8;  /* bit[24-31]: 写命令timeout配置（档位11）。
                                                     配置方式同wr_tout0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout8_START   (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout8_END     (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout9_START   (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout9_END     (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout10_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout10_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout11_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout11_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRTOUT3_UNION
 结构说明  : QOSB_WRTOUT3 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTOUT是QosBuf的写命令timeout配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_tout12 : 8;  /* bit[0-7]  : 写命令timeout配置（档位12）。
                                                     配置方式同wr_tout0。 */
        unsigned int  wr_tout13 : 8;  /* bit[8-15] : 写命令timeout配置（档位13）。
                                                     配置方式同wr_tout0。 */
        unsigned int  wr_tout14 : 8;  /* bit[16-23]: 写命令timeout配置（档位14）。
                                                     配置方式同wr_tout0。 */
        unsigned int  wr_tout15 : 8;  /* bit[24-31]: 写命令timeout配置（档位15）。
                                                     配置方式同wr_tout0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout12_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout12_END    (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout13_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout13_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout14_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout14_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout15_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout15_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDTOUT0_UNION
 结构说明  : QOSB_RDTOUT0 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RDTOUT是QosBuf的读命令timeout配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_tout0 : 8;  /* bit[0-7]  : 读命令timeout配置（档位0）。
                                                    0x0：禁止timeout功能；
                                                    0x1～0xFF：n*4个时钟周期；
                                                    注意：
                                                    timeout配置为8bits，但实际计数为10bits，即低两位固定为零。 */
        unsigned int  rd_tout1 : 8;  /* bit[8-15] : 读命令timeout配置（档位1）。
                                                    配置方式同rd_tout0。 */
        unsigned int  rd_tout2 : 8;  /* bit[16-23]: 读命令timeout配置（档位2）。
                                                    配置方式同rd_tout0。 */
        unsigned int  rd_tout3 : 8;  /* bit[24-31]: 读命令timeout配置（档位3）。
                                                    配置方式同rd_tout0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout0_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout0_END    (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout1_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout1_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout2_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout2_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout3_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDTOUT1_UNION
 结构说明  : QOSB_RDTOUT1 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RDTOUT是QosBuf的读命令timeout配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_tout4 : 8;  /* bit[0-7]  : 读命令timeout配置（档位4）。
                                                    配置方式同rd_tout0。 */
        unsigned int  rd_tout5 : 8;  /* bit[8-15] : 读命令timeout配置（档位5）。
                                                    配置方式同rd_tout0。 */
        unsigned int  rd_tout6 : 8;  /* bit[16-23]: 读命令timeout配置（档位6）。
                                                    配置方式同rd_tout0。 */
        unsigned int  rd_tout7 : 8;  /* bit[24-31]: 读命令timeout配置（档位7）。
                                                    配置方式同rd_tout0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout4_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout4_END    (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout5_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout5_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout6_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout6_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout7_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDTOUT2_UNION
 结构说明  : QOSB_RDTOUT2 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RDTOUT是QosBuf的读命令timeout配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_tout8  : 8;  /* bit[0-7]  : 读命令timeout配置（档位8）。
                                                     配置方式同rd_tout0。 */
        unsigned int  rd_tout9  : 8;  /* bit[8-15] : 读命令timeout配置（档位9）。
                                                     配置方式同rd_tout0。 */
        unsigned int  rd_tout10 : 8;  /* bit[16-23]: 读命令timeout配置（档位10）。
                                                     配置方式同rd_tout0。 */
        unsigned int  rd_tout11 : 8;  /* bit[24-31]: 读命令timeout配置（档位11）。
                                                     配置方式同rd_tout0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout8_START   (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout8_END     (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout9_START   (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout9_END     (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout10_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout10_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout11_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout11_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDTOUT3_UNION
 结构说明  : QOSB_RDTOUT3 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RDTOUT是QosBuf的读命令timeout配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_tout12 : 8;  /* bit[0-7]  : 读命令timeout配置（档位12）。
                                                     配置方式同rd_tout0。 */
        unsigned int  rd_tout13 : 8;  /* bit[8-15] : 读命令timeout配置（档位13）。
                                                     配置方式同rd_tout0。 */
        unsigned int  rd_tout14 : 8;  /* bit[16-23]: 读命令timeout配置（档位14）。
                                                     配置方式同rd_tout0。 */
        unsigned int  rd_tout15 : 8;  /* bit[24-31]: 读命令timeout配置（档位15）。
                                                     配置方式同rd_tout0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout12_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout12_END    (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout13_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout13_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout14_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout14_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout15_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout15_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_UNION
 结构说明  : QOSB_WRTOUT_MAP 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTOUT是QosBuf的写命令timeout映射控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wrtout_map0 : 5;  /* bit[0-4]  : timeout一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。wrtout_map0表示要选择的bit0的在整个ID中的位置。 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  wrtout_map1 : 5;  /* bit[8-12] : timeout一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。wrtout_map1表示要选择的bit1的在整个ID中的位置。 */
        unsigned int  reserved_1  : 3;  /* bit[13-15]: 保留。 */
        unsigned int  wrtout_map2 : 5;  /* bit[16-20]: timeout一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。wrtout_map2表示要选择的bit2的在整个ID中的位置。 */
        unsigned int  reserved_2  : 3;  /* bit[21-23]: 保留。 */
        unsigned int  wrtout_map3 : 5;  /* bit[24-28]: timeout一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。wrtout_map3表示要选择的bit3的在整个ID中的位置。 */
        unsigned int  reserved_3  : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map0_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map0_END    (4)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map1_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map1_END    (12)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map2_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map2_END    (20)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map3_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map3_END    (28)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_UNION
 结构说明  : QOSB_RDTOUT_MAP 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RDTOUT是QosBuf的读命令timeout映射控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdtout_map0 : 5;  /* bit[0-4]  : timeout一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。rdtout_map0表示要选择的bit0的在整个ID中的位置。 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  rdtout_map1 : 5;  /* bit[8-12] : timeout一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。rdtout_map1表示要选择的bit1的在整个ID中的位置。 */
        unsigned int  reserved_1  : 3;  /* bit[13-15]: 保留。 */
        unsigned int  rdtout_map2 : 5;  /* bit[16-20]: timeout一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。rdtout_map2表示要选择的bit2的在整个ID中的位置。 */
        unsigned int  reserved_2  : 3;  /* bit[21-23]: 保留。 */
        unsigned int  rdtout_map3 : 5;  /* bit[24-28]: timeout一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。rdtout_map3表示要选择的bit3的在整个ID中的位置。 */
        unsigned int  reserved_3  : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map0_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map0_END    (4)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map1_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map1_END    (12)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map2_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map2_END    (20)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map3_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map3_END    (28)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRAGE0_UNION
 结构说明  : QOSB_WRAGE0 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTAGE是QosBuf的写命令aging配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_age_prd0 : 4;  /* bit[0-3]  : 写命令老化时间配置（档位0）。
                                                       0x0：禁止Aging功能；
                                                       0x1～0xF：N×16个时钟周期。 */
        unsigned int  wr_age_prd1 : 4;  /* bit[4-7]  : 写命令老化时间配置（档位1）。
                                                       具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd2 : 4;  /* bit[8-11] : 写命令老化时间配置（档位2）。
                                                       具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd3 : 4;  /* bit[12-15]: 写命令老化时间配置（档位3）。
                                                       具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd4 : 4;  /* bit[16-19]: 写命令老化时间配置（档位4）。
                                                       具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd5 : 4;  /* bit[20-23]: 写命令老化时间配置（档位5）。
                                                       具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd6 : 4;  /* bit[24-27]: 写命令老化时间配置（档位6）。
                                                       具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd7 : 4;  /* bit[28-31]: 写命令老化时间配置（档位7）。
                                                       具体说明见wr_age_prd0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd0_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd0_END    (3)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd1_START  (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd1_END    (7)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd2_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd2_END    (11)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd3_START  (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd3_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd4_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd4_END    (19)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd5_START  (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd5_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd6_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd6_END    (27)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd7_START  (28)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRAGE1_UNION
 结构说明  : QOSB_WRAGE1 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTAGE是QosBuf的写命令aging配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_age_prd8  : 4;  /* bit[0-3]  : 写命令老化时间配置（档位8）。
                                                        具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd9  : 4;  /* bit[4-7]  : 写命令老化时间配置（档位9）。
                                                        具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd10 : 4;  /* bit[8-11] : 写命令老化时间配置（档位10）。
                                                        具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd11 : 4;  /* bit[12-15]: 写命令老化时间配置（档位11）。
                                                        具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd12 : 4;  /* bit[16-19]: 写命令老化时间配置（档位12）。
                                                        具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd13 : 4;  /* bit[20-23]: 写命令老化时间配置（档位13）。
                                                        具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd14 : 4;  /* bit[24-27]: 写命令老化时间配置（档位14）。
                                                        具体说明见wr_age_prd0。 */
        unsigned int  wr_age_prd15 : 4;  /* bit[28-31]: 写命令老化时间配置（档位15）。
                                                        具体说明见wr_age_prd0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd8_START   (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd8_END     (3)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd9_START   (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd9_END     (7)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd10_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd10_END    (11)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd11_START  (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd11_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd12_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd12_END    (19)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd13_START  (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd13_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd14_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd14_END    (27)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd15_START  (28)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd15_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDAGE0_UNION
 结构说明  : QOSB_RDAGE0 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTAGE是QosBuf的读命令aging配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_age_prd0 : 4;  /* bit[0-3]  : 读命令老化时间配置（档位0）。
                                                       0x0：禁止Aging功能；
                                                       0x1～0xF：N×16个时钟周期。 */
        unsigned int  rd_age_prd1 : 4;  /* bit[4-7]  : 读命令老化时间配置（档位1）。
                                                       具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd2 : 4;  /* bit[8-11] : 读命令老化时间配置（档位2）。
                                                       具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd3 : 4;  /* bit[12-15]: 读命令老化时间配置（档位3）。
                                                       具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd4 : 4;  /* bit[16-19]: 读命令老化时间配置（档位4）。
                                                       具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd5 : 4;  /* bit[20-23]: 读命令老化时间配置（档位5）。
                                                       具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd6 : 4;  /* bit[24-27]: 读命令老化时间配置（档位6）。
                                                       具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd7 : 4;  /* bit[28-31]: 读命令老化时间配置（档位7）。
                                                       具体说明见rd_age_prd0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd0_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd0_END    (3)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd1_START  (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd1_END    (7)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd2_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd2_END    (11)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd3_START  (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd3_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd4_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd4_END    (19)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd5_START  (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd5_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd6_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd6_END    (27)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd7_START  (28)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd7_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDAGE1_UNION
 结构说明  : QOSB_RDAGE1 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRTAGE是QosBuf的读命令aging配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_age_prd8  : 4;  /* bit[0-3]  : 读命令老化时间配置（档位8）。
                                                        具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd9  : 4;  /* bit[4-7]  : 读命令老化时间配置（档位9）。
                                                        具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd10 : 4;  /* bit[8-11] : 读命令老化时间配置（档位10）。
                                                        具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd11 : 4;  /* bit[12-15]: 读命令老化时间配置（档位11）。
                                                        具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd12 : 4;  /* bit[16-19]: 读命令老化时间配置（档位12）。
                                                        具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd13 : 4;  /* bit[20-23]: 读命令老化时间配置（档位13）。
                                                        具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd14 : 4;  /* bit[24-27]: 读命令老化时间配置（档位14）。
                                                        具体说明见rd_age_prd0。 */
        unsigned int  rd_age_prd15 : 4;  /* bit[28-31]: 读命令老化时间配置（档位15）。
                                                        具体说明见rd_age_prd0。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd8_START   (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd8_END     (3)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd9_START   (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd9_END     (7)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd10_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd10_END    (11)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd11_START  (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd11_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd12_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd12_END    (19)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd13_START  (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd13_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd14_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd14_END    (27)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd15_START  (28)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd15_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRAGE_MAP_UNION
 结构说明  : QOSB_WRAGE_MAP 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WRAGE_MAP是QosBuf的写命令aging映射控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wrage_map0 : 5;  /* bit[0-4]  : aging一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。wrage_map0表示要选择的bit0的在整个ID中的位置。 */
        unsigned int  reserved_0 : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  wrage_map1 : 5;  /* bit[8-12] : aging一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。wrage_map1表示要选择的bit1的在整个ID中的位置。 */
        unsigned int  reserved_1 : 3;  /* bit[13-15]: 保留。 */
        unsigned int  wrage_map2 : 5;  /* bit[16-20]: aging一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。wrage_map2表示要选择的bit2的在整个ID中的位置。 */
        unsigned int  reserved_2 : 3;  /* bit[21-23]: 保留。 */
        unsigned int  wrage_map3 : 5;  /* bit[24-28]: aging一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。wrage_map3表示要选择的bit3的在整个ID中的位置。 */
        unsigned int  reserved_3 : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map0_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map0_END    (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map1_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map1_END    (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map2_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map2_END    (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map3_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map3_END    (28)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDAGE_MAP_UNION
 结构说明  : QOSB_RDAGE_MAP 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RDAGE_MAP是QosBuf的读命令aging映射控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdage_map0 : 5;  /* bit[0-4]  : aging一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。rdage_map0表示要选择的bit0的在整个ID中的位置。 */
        unsigned int  reserved_0 : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  rdage_map1 : 5;  /* bit[8-12] : aging一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。rdage_map1表示要选择的bit1的在整个ID中的位置。 */
        unsigned int  reserved_1 : 3;  /* bit[13-15]: 保留。 */
        unsigned int  rdage_map2 : 5;  /* bit[16-20]: aging一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。rdage_map2表示要选择的bit2的在整个ID中的位置。 */
        unsigned int  reserved_2 : 3;  /* bit[21-23]: 保留。 */
        unsigned int  rdage_map3 : 5;  /* bit[24-28]: aging一共分为16个档位，其映射方法是ID(包含了MID+ID+PORT_ID,从高到低依次是MID,ID,PORT_ID)中选出4bit，并根据这4bit的值选择对应的档位。rdage_map3表示要选择的bit3的在整个ID中的位置。 */
        unsigned int  reserved_3 : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map0_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map0_END    (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map1_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map1_END    (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map2_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map2_END    (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map3_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map3_END    (28)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_UNION
 结构说明  : QOSB_ROWHIT_PRILVL 寄存器结构定义。地址偏移量:0x0EC，初值:0x00000000，宽度:32
 寄存器说明: QOSB_ROWHIT_PRILVL是QosBuf的row hit优先级水线寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_rowhit_pri_lvl : 3;  /* bit[0-2]  : 通道0优先级水线：
                                                              当前优先级低于ch0_rohit_pri_lvl时，将优先级提到ch0_rowhit_pri1；
                                                              当前优先级高于ch0_rohit_pri_lvl时，将优先级提到ch0_rowhit_pri0； */
        unsigned int  reserved_0         : 1;  /* bit[3]    : 保留。 */
        unsigned int  ch1_rowhit_pri_lvl : 3;  /* bit[4-6]  : 通道1优先级水线：
                                                              当前优先级低于ch1_rohit_pri_lvl时，将优先级提到ch1_rowhit_pri1；
                                                              当前优先级高于ch1_rohit_pri_lvl时，将优先级提到ch1_rowhit_pri0； */
        unsigned int  reserved_1         : 1;  /* bit[7]    : 保留。 */
        unsigned int  ch2_rowhit_pri_lvl : 3;  /* bit[8-10] : 通道2优先级水线：
                                                              当前优先级低于ch2_rohit_pri_lvl时，将优先级提到ch2_rowhit_pri1；
                                                              当前优先级高于ch2_rohit_pri_lvl时，将优先级提到ch2_rowhit_pri0； */
        unsigned int  reserved_2         : 1;  /* bit[11]   : 保留。 */
        unsigned int  ch3_rowhit_pri_lvl : 3;  /* bit[12-14]: 通道3优先级水线：
                                                              当前优先级低于ch3_rohit_pri_lvl时，将优先级提到ch3_rowhit_pri1；
                                                              当前优先级高于ch3_rohit_pri_lvl时，将优先级提到ch3_rowhit_pri0； */
        unsigned int  reserved_3         : 17; /* bit[15-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch0_rowhit_pri_lvl_START  (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch0_rowhit_pri_lvl_END    (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch1_rowhit_pri_lvl_START  (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch1_rowhit_pri_lvl_END    (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch2_rowhit_pri_lvl_START  (8)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch2_rowhit_pri_lvl_END    (10)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch3_rowhit_pri_lvl_START  (12)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch3_rowhit_pri_lvl_END    (14)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_UNION
 结构说明  : QOSB_ROWHIT_PRI 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: QOSB_ROWHIT_PRI是QosBuf的row hit优先级控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_rowhit_pri0 : 3;  /* bit[0-2]  : 请见ch0_rowhit_pri_lvl的说明。 */
        unsigned int  reserved_0      : 1;  /* bit[3]    : 保留。 */
        unsigned int  ch0_rowhit_pri1 : 3;  /* bit[4-6]  : 请见ch0_rowhit_pri_lvl的说明。 */
        unsigned int  reserved_1      : 1;  /* bit[7]    : 保留。 */
        unsigned int  ch1_rowhit_pri0 : 3;  /* bit[8-10] : 请见ch1_rowhit_pri_lvl的说明。 */
        unsigned int  reserved_2      : 1;  /* bit[11]   : 保留。 */
        unsigned int  ch1_rowhit_pri1 : 3;  /* bit[12-14]: 请见ch1_rowhit_pri_lvl的说明。 */
        unsigned int  reserved_3      : 1;  /* bit[15]   : 保留。 */
        unsigned int  ch2_rowhit_pri0 : 3;  /* bit[16-18]: 请见ch2_rowhit_pri_lvl的说明。 */
        unsigned int  reserved_4      : 1;  /* bit[19]   : 保留。 */
        unsigned int  ch2_rowhit_pri1 : 3;  /* bit[20-22]: 请见ch2_rowhit_pri_lvl的说明。 */
        unsigned int  reserved_5      : 1;  /* bit[23]   : 保留。 */
        unsigned int  ch3_rowhit_pri0 : 3;  /* bit[24-26]: 请见ch3_rowhit_pri_lvl的说明。 */
        unsigned int  reserved_6      : 1;  /* bit[27]   : 保留。 */
        unsigned int  ch3_rowhit_pri1 : 3;  /* bit[28-30]: 请见ch3_rowhit_pri_lvl的说明。 */
        unsigned int  reserved_7      : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri0_START  (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri0_END    (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri1_START  (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri1_END    (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri0_START  (8)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri0_END    (10)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri1_START  (12)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri1_END    (14)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri0_START  (16)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri0_END    (18)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri1_START  (20)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri1_END    (22)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri0_START  (24)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri0_END    (26)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri1_START  (28)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri1_END    (30)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_UNION
 结构说明  : QOSB_ROWHIT_CTRL 寄存器结构定义。地址偏移量:0x0F4，初值:0x00000000，宽度:32
 寄存器说明: QOS_ROWHIT_CTRL是QosBuf的row hit的使能控制。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_row_hit_en   : 1;  /* bit[0]   : channel0 row hit使能控制：
                                                           0：rowhit功能关闭；
                                                           1：rowhit功能打开； */
        unsigned int  ch1_row_hit_en   : 1;  /* bit[1]   : channel1 row hit使能控制：
                                                           0：rowhit功能关闭；
                                                           1：rowhit功能打开； */
        unsigned int  ch2_row_hit_en   : 1;  /* bit[2]   : channel2 row hit使能控制：
                                                           0：rowhit功能关闭；
                                                           1：rowhit功能打开； */
        unsigned int  ch3_row_hit_en   : 1;  /* bit[3]   : channel3 row hit使能控制：
                                                           0：rowhit功能关闭；
                                                           1：rowhit功能打开； */
        unsigned int  ch0_dual_flow_en : 1;  /* bit[4]   : channel0的row hit的双流使能控制：
                                                           0：双流功能关闭；
                                                           1：双流功能打开。 */
        unsigned int  ch1_dual_flow_en : 1;  /* bit[5]   : channel1的row hit的双流使能控制：
                                                           0：双流功能关闭；
                                                           1：双流功能打开。 */
        unsigned int  ch2_dual_flow_en : 1;  /* bit[6]   : channel2的row hit的双流使能控制：
                                                           0：双流功能关闭；
                                                           1：双流功能打开。 */
        unsigned int  ch3_dual_flow_en : 1;  /* bit[7]   : channel3的row hit的双流使能控制：
                                                           0：双流功能关闭；
                                                           1：双流功能打开。 */
        unsigned int  reserved         : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_row_hit_en_START    (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_row_hit_en_END      (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_row_hit_en_START    (1)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_row_hit_en_END      (1)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_row_hit_en_START    (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_row_hit_en_END      (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_row_hit_en_START    (3)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_row_hit_en_END      (3)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_dual_flow_en_START  (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_dual_flow_en_END    (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_dual_flow_en_START  (5)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_dual_flow_en_END    (5)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_dual_flow_en_START  (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_dual_flow_en_END    (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_dual_flow_en_START  (7)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_dual_flow_en_END    (7)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WRAM_CTRL_UNION
 结构说明  : QOSB_WRAM_CTRL 寄存器结构定义。地址偏移量:0x0F8，初值:0x00000000，宽度:32
 寄存器说明: QOS_WRAM_CTRL是QosBuf的write buf的ram控制。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0wramerrinj        : 2;  /* bit[0-1]  : channel0的write buf的ram的错误注入。 */
        unsigned int  ch1wramerrinj        : 2;  /* bit[2-3]  : channel1的write buf的ram的错误注入。 */
        unsigned int  ch2wramerrinj        : 2;  /* bit[4-5]  : channel2的write buf的ram的错误注入。 */
        unsigned int  ch3wramerrinj        : 2;  /* bit[6-7]  : channel3的write buf的ram的错误注入。 */
        unsigned int  reserved_0           : 8;  /* bit[8-15] : 保留。 */
        unsigned int  ch0_wbuf_one_bit_err : 1;  /* bit[16]   : channel0的write buf的ram的1bit ECC错误标志。 */
        unsigned int  ch0_wbuf_two_bit_err : 1;  /* bit[17]   : channel0的write buf的ram的2bit ECC错误标志。 */
        unsigned int  ch1_wbuf_one_bit_err : 1;  /* bit[18]   : channel1的write buf的ram的1bit ECC错误标志。 */
        unsigned int  ch1_wbuf_two_bit_err : 1;  /* bit[19]   : channel1的write buf的ram的2bit ECC错误标志。 */
        unsigned int  ch2_wbuf_one_bit_err : 1;  /* bit[20]   : channel2的write buf的ram的1bit ECC错误标志。 */
        unsigned int  ch2_wbuf_two_bit_err : 1;  /* bit[21]   : channel2的write buf的ram的2bit ECC错误标志。 */
        unsigned int  ch3_wbuf_one_bit_err : 1;  /* bit[22]   : channel3的write buf的ram的1bit ECC错误标志。 */
        unsigned int  ch3_wbuf_two_bit_err : 1;  /* bit[23]   : channel3的write buf的ram的2bit ECC错误标志。 */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0wramerrinj_START         (0)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0wramerrinj_END           (1)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1wramerrinj_START         (2)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1wramerrinj_END           (3)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2wramerrinj_START         (4)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2wramerrinj_END           (5)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3wramerrinj_START         (6)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3wramerrinj_END           (7)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_one_bit_err_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_one_bit_err_END    (16)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_two_bit_err_START  (17)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_two_bit_err_END    (17)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_one_bit_err_START  (18)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_one_bit_err_END    (18)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_two_bit_err_START  (19)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_two_bit_err_END    (19)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_one_bit_err_START  (20)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_one_bit_err_END    (20)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_two_bit_err_START  (21)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_two_bit_err_END    (21)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_one_bit_err_START  (22)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_one_bit_err_END    (22)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_two_bit_err_START  (23)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_two_bit_err_END    (23)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_CRAM_CTRL_UNION
 结构说明  : QOSB_CRAM_CTRL 寄存器结构定义。地址偏移量:0x0FC，初值:0x00000000，宽度:32
 寄存器说明: QOS_CRAM_CTRL是QosBuf CID的RAM控制。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cramerrinj       : 2;  /* bit[0-1] : cid ram的错误注入。 */
        unsigned int  reserved_0       : 2;  /* bit[2-3] : 保留。 */
        unsigned int  cram_one_bit_err : 1;  /* bit[4]   : cid ram的ram的1bit ECC错误标志。 */
        unsigned int  cram_two_bit_err : 1;  /* bit[5]   : cid ram的ram的2bit ECC错误标志。 */
        unsigned int  reserved_1       : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_CRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cramerrinj_START        (0)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cramerrinj_END          (1)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_one_bit_err_START  (4)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_one_bit_err_END    (4)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_two_bit_err_START  (5)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_two_bit_err_END    (5)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_UNION
 结构说明  : QOSB_RDRRAM_CTRL 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: QOS_RDRRAM_CTRL是QosBuf的write buf的ram控制。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_rdr_err_inj     : 2;  /* bit[0-1]  : channel0的rdr buf的ram的错误注入。 */
        unsigned int  ch1_rdr_err_inj     : 2;  /* bit[2-3]  : channel1的rdr buf的ram的错误注入。 */
        unsigned int  ch2_rdr_err_inj     : 2;  /* bit[4-5]  : channel2的rdr buf的ram的错误注入。 */
        unsigned int  ch3_rdr_err_inj     : 2;  /* bit[6-7]  : channel3的rdr buf的ram的错误注入。 */
        unsigned int  reserved_0          : 8;  /* bit[8-15] : 保留。 */
        unsigned int  ch0_rdr_one_bit_err : 1;  /* bit[16]   : channel0的rdr buf的ram的1bit ECC错误标志。 */
        unsigned int  ch0_rdr_two_bit_err : 1;  /* bit[17]   : channel0的rdr buf的ram的2bit ECC错误标志。 */
        unsigned int  ch1_rdr_one_bit_err : 1;  /* bit[18]   : channel1的rdr buf的ram的1bit ECC错误标志。 */
        unsigned int  ch1_rdr_two_bit_err : 1;  /* bit[19]   : channel1的rdr buf的ram的2bit ECC错误标志。 */
        unsigned int  ch2_rdr_one_bit_err : 1;  /* bit[20]   : channel2的rdr buf的ram的1bit ECC错误标志。 */
        unsigned int  ch2_rdr_two_bit_err : 1;  /* bit[21]   : channel2的rdr buf的ram的2bit ECC错误标志。 */
        unsigned int  ch3_rdr_one_bit_err : 1;  /* bit[22]   : channel3的rdr buf的ram的1bit ECC错误标志。 */
        unsigned int  ch3_rdr_two_bit_err : 1;  /* bit[23]   : channel3的rdr buf的ram的2bit ECC错误标志。 */
        unsigned int  reserved_1          : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_err_inj_START      (0)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_err_inj_END        (1)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_err_inj_START      (2)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_err_inj_END        (3)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_err_inj_START      (4)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_err_inj_END        (5)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_err_inj_START      (6)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_err_inj_END        (7)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_one_bit_err_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_one_bit_err_END    (16)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_two_bit_err_START  (17)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_two_bit_err_END    (17)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_one_bit_err_START  (18)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_one_bit_err_END    (18)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_two_bit_err_START  (19)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_two_bit_err_END    (19)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_one_bit_err_START  (20)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_one_bit_err_END    (20)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_two_bit_err_START  (21)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_two_bit_err_END    (21)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_one_bit_err_START  (22)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_one_bit_err_END    (22)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_two_bit_err_START  (23)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_two_bit_err_END    (23)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RAM_TMOD_UNION
 结构说明  : QOSB_RAM_TMOD 寄存器结构定义。地址偏移量:0x104，初值:0x000001A8，宽度:32
 寄存器说明: QOS_RAM_TMOD是QosBuf/RDR的RAM的端口配置信号寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram_tmod : 32; /* bit[0-31]: 根据不同的工艺配置，由宏定义决定其值。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RAM_TMOD_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ram_tmod_START  (0)
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ram_tmod_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_CKG_CFG_UNION
 结构说明  : QOSB_CKG_CFG 寄存器结构定义。地址偏移量:0x108，初值:0x00000001，宽度:32
 寄存器说明: QOS_CKG_CFG是QosBuf的时钟控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dyn_ck_gate : 1;  /* bit[0]   : Qosbuf模块的动态时钟门控。
                                                      0：时钟常开；
                                                      1：模块空闲时，时钟自动门控。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_CKG_CFG_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_dyn_ck_gate_START  (0)
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_dyn_ck_gate_END    (0)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_DMC_LVL_UNION
 结构说明  : QOSB_DMC_LVL 寄存器结构定义。地址偏移量:0x10C+0x4*(chans)，初值:0x0000000F，宽度:32
 寄存器说明: QOSB_DMC_LVL是QosBuf的进入DMC的命令的线控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_cmd_full_lvl : 5;  /* bit[0-4] : qos buf进入dmc的命令的个数，当达到这个水线，表示dmc的queue已经满。
                                                           注意：由于流水的问题，当配置为N时，实际通过的命令个数为N+1。另外，该寄存器不能在访问过程中进行动态配置。 */
        unsigned int  reserved         : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_DMC_LVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_dmc_cmd_full_lvl_START  (0)
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_dmc_cmd_full_lvl_END    (4)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_CFG_PERF_UNION
 结构说明  : QOSB_CFG_PERF 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: QOSB_CFG_PERF是QosBuf性能统计的模式配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perf_prd  : 28; /* bit[0-27] : 性能统计周期。
                                                     0x0：无效配置。
                                                     0x1～0xFFFFFFF：统计周期。
                                                     实际统计周期为perf_prd*16*tclk（Tclk为DDRC总线时钟周期）。
                                                     注意：此配置只在perf_mode=1时有效。当perf_mode=0的连续统计模式下，性能统计相关计数器会一直计数。 */
        unsigned int  perf_mode : 1;  /* bit[28]   : 性能统计模式。
                                                     0：连续触发模式。性能统计相关计数器连续计数。可保证在连续统计模式下，1s内统计不溢出（1GHZMHz）。
                                                     1：单次触发模式。性能统计时间计满perf_prd后，统计结果保持，并停止统计。
                                                     注意：当统计值溢出后保持。 */
        unsigned int  perf_en   : 1;  /* bit[29]   : 性能统计使能寄存器。
                                                     1：使能；
                                                     0：禁止。
                                                      注意：在perf_mode=0时，此位使能表示性能统计寄存器将开始循环技术。在perf_mode=1时，完成一次统计之后，该位自动清零 */
        unsigned int  reserved  : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_CFG_PERF_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_prd_START   (0)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_prd_END     (27)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_mode_START  (28)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_mode_END    (28)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_en_START    (29)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_en_END      (29)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_CMD_SUM_UNION
 结构说明  : QOSB_CMD_SUM 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: QOSB_CMD_SUM是QosBuf命令计数的累积寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_cmd_sum : 32; /* bit[0-31]: 当前QosBuf暂存命令的值按周期累积，溢出卷绕 */
    } reg;
} SOC_DDRC_QOSB_QOSB_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_qos_cmd_sum_START  (0)
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_qos_cmd_sum_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_SLOT_STAT0_UNION
 结构说明  : QOSB_SLOT_STAT0 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: QOSB_SLOT_STAT0是QosBuf的queue的状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grp_cmd_valid_l : 32; /* bit[0-31]: QosBuf中cmd queue从0~31的状态，对应的位为1表示该slot中存有命令，否则为空。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_grp_cmd_valid_l_START  (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_grp_cmd_valid_l_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_SLOT_STAT1_UNION
 结构说明  : QOSB_SLOT_STAT1 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: QOSB_SLOT_STAT0是QosBuf的queue的状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grp_cmd_valid_m0 : 32; /* bit[0-31]: QosBuf中cmd queue从32~63的状态，对应的位为1表示该slot中存有命令，否则为空。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_grp_cmd_valid_m0_START  (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_grp_cmd_valid_m0_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_SLOT_STAT2_UNION
 结构说明  : QOSB_SLOT_STAT2 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: QOSB_SLOT_STAT0是QosBuf的queue的状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grp_cmd_valid_m1 : 32; /* bit[0-31]: QosBuf中cmd queue从64~95的状态，对应的位为1表示该slot中存有命令，否则为空。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_grp_cmd_valid_m1_START  (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_grp_cmd_valid_m1_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_SLOT_STAT3_UNION
 结构说明  : QOSB_SLOT_STAT3 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: QOSB_SLOT_STAT0是QosBuf的queue的状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grp_cmd_valid_h : 32; /* bit[0-31]: QosBuf中cmd queue从96~127的状态，对应的位为1表示该slot中存有命令，否则为空。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_grp_cmd_valid_h_START  (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_grp_cmd_valid_h_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WBUF_STAT0_UNION
 结构说明  : QOSB_WBUF_STAT0 寄存器结构定义。地址偏移量:0x140+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WBUF_STAT0是QosBuf的写buf状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_ldata_valid_l : 32; /* bit[0-31]: QosBuf中写buf从0~31的状态，相应的位为1表示该buf中存有一个burst的数据，否则数据不到一个burst或为空。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_STAT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_buf_ldata_valid_l_START  (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_buf_ldata_valid_l_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WBUF_STAT1_UNION
 结构说明  : QOSB_WBUF_STAT1 寄存器结构定义。地址偏移量:0x150+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WBUF_STAT1是QosBuf的写buf状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_ldata_valid_h : 32; /* bit[0-31]: QosBuf中写buf从31~63的状态，相应的位为1表示该buf中存有一个burst的数据，否则数据不到一个burst或为空。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_STAT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_buf_ldata_valid_h_START  (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_buf_ldata_valid_h_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_UNION
 结构说明  : QOSB_RDRBUF_STAT 寄存器结构定义。地址偏移量:0x160+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RDRBUF_STAT是Reorder模块的buf状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  e_vld : 32; /* bit[0-31]: Reorder中reorder buf从0~31的状态，相应的位为1表示该buf中存有一个burst的数据，否则数据不到一个burst或为空。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_e_vld_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_e_vld_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_INTMSK_UNION
 结构说明  : QOSB_INTMSK 寄存器结构定义。地址偏移量:0x170，初值:0x00000000，宽度:32
 寄存器说明: QOSB_INTMSK是QosBuf中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_stat_int_mask    : 1;  /* bit[0]   : QOS Buf命令统计中断屏蔽使能。
                                                               1：屏蔽中断；
                                                               0：使能中断。 */
        unsigned int  rdrbuf_serr_int_mask : 1;  /* bit[1]   : RDR BUF(RAM)的ECC单bit错误中断屏蔽使能
                                                               1：屏蔽中断；
                                                               0：使能中断； */
        unsigned int  rdrbuf_derr_int_mask : 1;  /* bit[2]   : RDR BUF(RAM)的ECC双bit错误中断屏蔽使能
                                                               1：屏蔽中断；
                                                               0：使能中断； */
        unsigned int  qosbuf_serr_int_mask : 1;  /* bit[3]   : QosBuf 写buf单bit错误中断屏蔽使能。
                                                               1：屏蔽中断；
                                                               0：使能中断。 */
        unsigned int  qosbuf_derr_int_mask : 1;  /* bit[4]   : QosBuf 写buf双bit错误中断屏蔽使能。
                                                               1：屏蔽中断；
                                                               0：使能中断。 */
        unsigned int  qoscid_serr_int_mask : 1;  /* bit[5]   : QosBuf cid ram单bit错误中断屏蔽使能。
                                                               1：屏蔽中断；
                                                               0：使能中断。 */
        unsigned int  qoscid_derr_int_mask : 1;  /* bit[6]   : QosBuf cid ram双bit错误中断屏蔽使能。
                                                               1：屏蔽中断；
                                                               0：使能中断。 */
        unsigned int  reserved             : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_INTMSK_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_INTMSK_qos_stat_int_mask_START     (0)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qos_stat_int_mask_END       (0)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_serr_int_mask_START  (1)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_serr_int_mask_END    (1)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_derr_int_mask_START  (2)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_derr_int_mask_END    (2)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_serr_int_mask_START  (3)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_serr_int_mask_END    (3)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_derr_int_mask_START  (4)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_derr_int_mask_END    (4)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_serr_int_mask_START  (5)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_serr_int_mask_END    (5)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_derr_int_mask_START  (6)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_derr_int_mask_END    (6)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RINT_UNION
 结构说明  : QOSB_RINT 寄存器结构定义。地址偏移量:0x174，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RINT是QosBuf原始中断寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_stat_rint    : 1;  /* bit[0]   : QOS Buf命令统计中断。写1中断清除 */
        unsigned int  rdrbuf_serr_rint : 1;  /* bit[1]   : RDR BUF(RAM)的ECC单bit错误中断。写1中断清除。 */
        unsigned int  rdrbuf_derr_rint : 1;  /* bit[2]   : RDR BUF(RAM)的ECC双bit错误中断。写1中断清除。 */
        unsigned int  qosbuf_serr_rint : 1;  /* bit[3]   : QosBuf 写buf单bit错误中断。写1中断清除 */
        unsigned int  qosbuf_derr_rint : 1;  /* bit[4]   : QosBuf 写buf双bit错误中断。写1中断清除。 */
        unsigned int  qoscid_serr_rint : 1;  /* bit[5]   : QosBuf cid ram单bit错误中断。写1中断清除。 */
        unsigned int  qoscid_derr_rint : 1;  /* bit[6]   : QosBuf cid ram双bit错误中断。写1中断清除。 */
        unsigned int  reserved         : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RINT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RINT_qos_stat_rint_START     (0)
#define SOC_DDRC_QOSB_QOSB_RINT_qos_stat_rint_END       (0)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_serr_rint_START  (1)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_serr_rint_END    (1)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_derr_rint_START  (2)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_derr_rint_END    (2)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_serr_rint_START  (3)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_serr_rint_END    (3)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_derr_rint_START  (4)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_derr_rint_END    (4)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_serr_rint_START  (5)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_serr_rint_END    (5)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_derr_rint_START  (6)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_derr_rint_END    (6)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_INTSTS_UNION
 结构说明  : QOSB_INTSTS 寄存器结构定义。地址偏移量:0x178，初值:0x00000000，宽度:32
 寄存器说明: QOSB_INTSTS是QOSBUF中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_stat_intsts    : 1;  /* bit[0]   : QOS Buf命令统计中断。 */
        unsigned int  rdrbuf_serr_intsts : 1;  /* bit[1]   : RDR BUF(RAM)的ECC单bit错误中断。 */
        unsigned int  rdrbuf_derr_intsts : 1;  /* bit[2]   : RDR BUF(RAM)的ECC双bit错误中断。。 */
        unsigned int  qosbuf_serr_intsts : 1;  /* bit[3]   : QosBuf 写buf单bit错误中断。 */
        unsigned int  qosbuf_derr_intsts : 1;  /* bit[4]   : QosBuf 写buf双bit错误中断。 */
        unsigned int  qoscid_serr_intsts : 1;  /* bit[5]   : QosBuf cid ram单bit错误中断。 */
        unsigned int  qoscid_derr_intsts : 1;  /* bit[6]   : QosBuf cid ram双bit错误中断。 */
        unsigned int  reserved           : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_INTSTS_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_INTSTS_qos_stat_intsts_START     (0)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qos_stat_intsts_END       (0)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_serr_intsts_START  (1)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_serr_intsts_END    (1)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_derr_intsts_START  (2)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_derr_intsts_END    (2)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_serr_intsts_START  (3)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_serr_intsts_END    (3)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_derr_intsts_START  (4)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_derr_intsts_END    (4)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_serr_intsts_START  (5)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_serr_intsts_END    (5)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_derr_intsts_START  (6)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_derr_intsts_END    (6)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_CMD_CNT_UNION
 结构说明  : QOSB_CMD_CNT 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: QOSB_CMD_CNT是QOSBUF中当前有多少命令的统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_cmd_cnt : 8;  /* bit[0-7] : QosBuf当前命令的个数，包括流水线上的命令。 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_CMD_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_qos_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_qos_cmd_cnt_END    (7)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RNK_CNT_UNION
 结构说明  : QOSB_RNK_CNT 寄存器结构定义。地址偏移量:0x190+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOSB_RNK_CNT是QOSBUF中当前每个rank中有多少命令的统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnk0_cmd_cnt : 8;  /* bit[0-7]  : QosBuf中当前通道属于rank0的命令个数 */
        unsigned int  rnk1_cmd_cnt : 8;  /* bit[8-15] : QosBuf中当前通道属于rank1的命令个数 */
        unsigned int  rnk2_cmd_cnt : 8;  /* bit[16-23]: QosBuf中当前通道属于rank2的命令个数 */
        unsigned int  rnk3_cmd_cnt : 8;  /* bit[24-31]: QosBuf中当前通道属于rank3的命令个数 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RNK_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk0_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk0_cmd_cnt_END    (7)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk1_cmd_cnt_START  (8)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk1_cmd_cnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk2_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk2_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk3_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk3_cmd_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_BNK_CNT0_UNION
 结构说明  : QOSB_BNK_CNT0 寄存器结构定义。地址偏移量:0x1A0+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOSB_BNK_CNT0是QOSBUF中当前每个Bank有多少命令的统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk0_cmd_cnt : 8;  /* bit[0-7]  : 统计DMC中当前通道属于bank0的命令个数 */
        unsigned int  bnk1_cmd_cnt : 8;  /* bit[8-15] : 统计DMC中当前通道属于bank1的命令个数 */
        unsigned int  bnk2_cmd_cnt : 8;  /* bit[16-23]: 统计DMC中当前通道属于bank2的命令个数 */
        unsigned int  bnk3_cmd_cnt : 8;  /* bit[24-31]: 统计DMC中当前通道属于bank3的命令个数 */
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk0_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk0_cmd_cnt_END    (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk1_cmd_cnt_START  (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk1_cmd_cnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk2_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk2_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk3_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk3_cmd_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_BNK_CNT1_UNION
 结构说明  : QOSB_BNK_CNT1 寄存器结构定义。地址偏移量:0x1B0+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOSB_BNK_CNT1是QOSBUF中当前每个Bank有多少命令的统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk4_cmd_cnt : 8;  /* bit[0-7]  : 统计DMC中当前通道属于bank4的命令个数 */
        unsigned int  bnk5_cmd_cnt : 8;  /* bit[8-15] : 统计DMC中当前通道属于bank5的命令个数 */
        unsigned int  bnk6_cmd_cnt : 8;  /* bit[16-23]: 统计DMC中当前通道属于bank6的命令个数 */
        unsigned int  bnk7_cmd_cnt : 8;  /* bit[24-31]: 统计DMC中当前通道属于bank7的命令个数 */
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk4_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk4_cmd_cnt_END    (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk5_cmd_cnt_START  (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk5_cmd_cnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk6_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk6_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk7_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk7_cmd_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_BNK_CNT2_UNION
 结构说明  : QOSB_BNK_CNT2 寄存器结构定义。地址偏移量:0x1C0+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOSB_BNK_CNT2是QOSBUF中当前每个Bank有多少命令的统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk8_cmd_cnt  : 8;  /* bit[0-7]  : 统计DMC中当前通道属于bank8的命令个数 */
        unsigned int  bnk9_cmd_cnt  : 8;  /* bit[8-15] : 统计DMC中当前通道属于bank9的命令个数 */
        unsigned int  bnk10_cmd_cnt : 8;  /* bit[16-23]: 统计DMC中当前通道属于bank10的命令个数 */
        unsigned int  bnk11_cmd_cnt : 8;  /* bit[24-31]: 统计DMC中当前通道属于bank11的命令个数 */
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk8_cmd_cnt_START   (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk8_cmd_cnt_END     (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk9_cmd_cnt_START   (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk9_cmd_cnt_END     (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk10_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk10_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk11_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk11_cmd_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_BNK_CNT3_UNION
 结构说明  : QOSB_BNK_CNT3 寄存器结构定义。地址偏移量:0x1D0+0x4*(chans)，初值:0x00000000，宽度:32
 寄存器说明: QOSB_BNK_CNT3是QOSBUF中当前每个Bank有多少命令的统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk12_cmd_cnt : 8;  /* bit[0-7]  : 统计DMC中当前通道属于bank12的命令个数 */
        unsigned int  bnk13_cmd_cnt : 8;  /* bit[8-15] : 统计DMC中当前通道属于bank13的命令个数 */
        unsigned int  bnk14_cmd_cnt : 8;  /* bit[16-23]: 统计DMC中当前通道属于bank14的命令个数 */
        unsigned int  bnk15_cmd_cnt : 8;  /* bit[24-31]: 统计DMC中当前通道属于bank15的命令个数 */
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk12_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk12_cmd_cnt_END    (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk13_cmd_cnt_START  (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk13_cmd_cnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk14_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk14_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk15_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk15_cmd_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_OSTD_CNT_UNION
 结构说明  : QOSB_OSTD_CNT 寄存器结构定义。地址偏移量:0x1E0，初值:0x00000000，宽度:32
 寄存器说明: QOSB_OSTD_CNT是QOSBUF中当前每个通道有多少Oustanding命令的统计寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_cmd_ostd : 8;  /* bit[0-7]  : QosBuf中当前通道属于channel0的Outanding命令个数 */
        unsigned int  ch1_cmd_ostd : 8;  /* bit[8-15] : QosBuf中当前通道属于channel1的Outanding命令个数 */
        unsigned int  ch2_cmd_ostd : 8;  /* bit[16-23]: QosBuf中当前通道属于channel2的Outanding命令个数 */
        unsigned int  ch3_cmd_ostd : 8;  /* bit[24-31]: QosBuf中当前通道属于channel3的Outanding命令个数 */
    } reg;
} SOC_DDRC_QOSB_QOSB_OSTD_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch0_cmd_ostd_START  (0)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch0_cmd_ostd_END    (7)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch1_cmd_ostd_START  (8)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch1_cmd_ostd_END    (15)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch2_cmd_ostd_START  (16)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch2_cmd_ostd_END    (23)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch3_cmd_ostd_START  (24)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch3_cmd_ostd_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_UNION
 结构说明  : QOSB_WR_CMD_SUM 寄存器结构定义。地址偏移量:0x1E4，初值:0x00000000，宽度:32
 寄存器说明: QOSB_CMD_SUM是QosBuf写命令计数的累积寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_wr_cmd_sum : 32; /* bit[0-31]: 当前QosBuf暂存写命令的值按周期累积，溢出卷绕 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_qos_wr_cmd_sum_START  (0)
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_qos_wr_cmd_sum_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_UNION
 结构说明  : QOSB_RD_CMD_SUM 寄存器结构定义。地址偏移量:0x1E8，初值:0x00000000，宽度:32
 寄存器说明: QOSB_CMD_SUM是QosBuf读命令计数的累积寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_rd_cmd_sum : 32; /* bit[0-31]: 当前QosBuf暂存读命令的值按周期累积，溢出卷绕 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_qos_rd_cmd_sum_START  (0)
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_qos_rd_cmd_sum_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_UNION
 结构说明  : QOSB_GRT_FIFO_STATUS 寄存器结构定义。地址偏移量:0x1EC，初值:0x00000000，宽度:32
 寄存器说明: QOSB_GRT_FIFO_STATUS是写数据汇聚MUX对应的grant fifo的状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grt_fifo_vld_0 : 1;  /* bit[0]    : 通道0对应的grant fifo的状态。
                                                          0：表示空；
                                                          1：表示非空。 */
        unsigned int  grt_fifo_pid_0 : 7;  /* bit[1-7]  : 通道0对应的grant fifo中的port id。 */
        unsigned int  grt_fifo_vld_1 : 1;  /* bit[8]    : 通道1对应的grant fifo的状态。
                                                          0：表示空；
                                                          1：表示非空。 */
        unsigned int  grt_fifo_pid_1 : 7;  /* bit[9-15] : 通道1对应的grant fifo中的port id。 */
        unsigned int  grt_fifo_vld_2 : 1;  /* bit[16]   : 通道2对应的grant fifo的状态。
                                                          0：表示空；
                                                          1：表示非空。 */
        unsigned int  grt_fifo_pid_2 : 7;  /* bit[17-23]: 通道2对应的grant fifo中的port id。 */
        unsigned int  grt_fifo_vld_3 : 1;  /* bit[24]   : 通道3对应的grant fifo的状态。
                                                          0：表示空；
                                                          1：表示非空。 */
        unsigned int  grt_fifo_pid_3 : 7;  /* bit[25-31]: 通道3对应的grant fifo中的port id。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_0_START  (0)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_0_END    (0)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_0_START  (1)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_0_END    (7)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_1_START  (8)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_1_END    (8)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_1_START  (9)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_1_END    (15)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_2_START  (16)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_2_END    (16)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_2_START  (17)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_2_END    (23)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_3_START  (24)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_3_END    (24)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_3_START  (25)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_3_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_UNION
 结构说明  : QOSB_TIMEOUT_MODE 寄存器结构定义。地址偏移量:0x1F0，初值:0x00000000，宽度:32
 寄存器说明: QOSB_TIMEOUT_MODE是QOSBUF中timeout模式选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeout_mode : 1;  /* bit[0]   : Timeout模式选择寄存器
                                                       0：表示通过ID来映射，共16级
                                                       1：表示通过优先级来映射，共8级。其中映射表与ID的映射表的低8个相同。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_timeout_mode_START  (0)
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_timeout_mode_END    (0)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_UNION
 结构说明  : QOSB_WBUF_PRI_CTRL 寄存器结构定义。地址偏移量:0x1F4，初值:0x00200000，宽度:32
 寄存器说明: QOSB_WBUF_PRI_CTRL是QOSBUF中写wbuf优先级调整控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wbuf_lcnt : 16; /* bit[0-15] : 当写wbuf达到lvl2水线时才会起作用。该计数器表示在该时间区域内写buf会将优写命令的优先级调到pri1.如果该计数器为0，表示会一直使用pri2的优先级。
                                                     （注意：这里的pri1指wbuf在lvl1以上对应的优先级） */
        unsigned int  wbuf_hcnt : 16; /* bit[16-31]: 当写wbuf达到lvl2水线时才会起作用。该计数器表示在该时间区域内写buf会将优写命令的优先级调到pri2.
                                                     （注意：这里的pri2指wbuf在lvl2以上对应的优先级） */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_lcnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_lcnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_hcnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_hcnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_RHIT_CTRL_UNION
 结构说明  : QOSB_RHIT_CTRL 寄存器结构定义。地址偏移量:0x1F8，初值:0x00FF000F，宽度:32
 寄存器说明: QOSB_RHIT_CTRL是QOSBUF中rowhit优先级调整控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rhit_lcnt : 16; /* bit[0-15] : 当rowhit的流达到该寄存器配置的值后，就会强行将其断开。然后计数rhit_lcnt的时间，才允许重新进行rowhit。 */
        unsigned int  rhit_hcnt : 16; /* bit[16-31]: 当rowhit的流达到该寄存器配置的值后，就会强行将其断开。然后计数rhit_lcnt的时间，才允许重新进行rowhit。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_RHIT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_lcnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_lcnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_hcnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_hcnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_UNION
 结构说明  : QOSB_WBUF_MERG_CTRL 寄存器结构定义。地址偏移量:0x1FC，初值:0x00000000，宽度:32
 寄存器说明: QOSB_WBUF_MERG_CTRL是QOSBUF双通道写buf合并控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_merge : 1;  /* bit[0]   : 在双通道模式下是否将通道1的wbuf合到通道0。
                                                   0：表示两个通道的wbuf不合并；
                                                   1：表示将通道1的wbuf与通道0的wbuf合并。
                                                   
                                                   注意：在合并模式下只能支持通道0工作，通道1不能工作。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ch_merge_START  (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ch_merge_END    (0)






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

#endif /* end of soc_ddrc_qosb_interface.h */
