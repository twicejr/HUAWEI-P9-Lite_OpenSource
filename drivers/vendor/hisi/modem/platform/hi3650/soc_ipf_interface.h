/******************************************************************************

                 版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_ipf_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2013-01-07 10:10:53
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年1月7日
    作    者   : z00212992
    修改内容   : 从《hiipfv200寄存器手册_IPF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_IPF_INTERFACE_H__
#define __SOC_IPF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) IPF
 ****************************************************************************/
/* 寄存器说明：IPF复位控制寄存器
   位域定义UNION结构:  SOC_IPF_SRST_UNION */
#define SOC_IPF_SRST_ADDR(base)                       ((base) + (0x0000))

/* 寄存器说明：IPF复位状态寄存器
   位域定义UNION结构:  SOC_IPF_SRST_STATE_UNION */
#define SOC_IPF_SRST_STATE_ADDR(base)                 ((base) + (0x0004))

/* 寄存器说明：IPF 通道使能配置寄存器
   位域定义UNION结构:  SOC_IPF_CH_EN_UNION */
#define SOC_IPF_CH_EN_ADDR(base)                      ((base) + (0x0008))

/* 寄存器说明：IPF 通道使能状态寄存器
   位域定义UNION结构:  SOC_IPF_EN_STATE_UNION */
#define SOC_IPF_EN_STATE_ADDR(base)                   ((base) + (0x000C))

/* 寄存器说明：IPF时钟门控配置寄存器
   位域定义UNION结构:  SOC_IPF_GATE_UNION */
#define SOC_IPF_GATE_ADDR(base)                       ((base) + (0x0010))

/* 寄存器说明：IPF全局控制配置寄存器
   位域定义UNION结构:  SOC_IPF_CTRL_UNION */
#define SOC_IPF_CTRL_ADDR(base)                       ((base) + (0x0014))

/* 寄存器说明：IPF DMA控制寄存器0
   位域定义UNION结构:  SOC_IPF_DMA_CTRL0_UNION */
#define SOC_IPF_DMA_CTRL0_ADDR(base)                  ((base) + (0x0018))

/* 寄存器说明：IPF DMA控制寄存器1
   位域定义UNION结构:  SOC_IPF_DMA_CTRL1_UNION */
#define SOC_IPF_DMA_CTRL1_ADDR(base)                  ((base) + (0x001C))

/* 寄存器说明：中断上报寄存器0
   位域定义UNION结构:  SOC_IPF_INT0_UNION */
#define SOC_IPF_INT0_ADDR(base)                       ((base) + (0x0030))

/* 寄存器说明：中断上报寄存器1
   位域定义UNION结构:  SOC_IPF_INT1_UNION */
#define SOC_IPF_INT1_ADDR(base)                       ((base) + (0x0034))

/* 寄存器说明：中断屏蔽寄存器0
   位域定义UNION结构:  SOC_IPF_INT_MASK0_UNION */
#define SOC_IPF_INT_MASK0_ADDR(base)                  ((base) + (0x0038))

/* 寄存器说明：中断屏蔽寄存器1
   位域定义UNION结构:  SOC_IPF_INT_MASK1_UNION */
#define SOC_IPF_INT_MASK1_ADDR(base)                  ((base) + (0x003C))

/* 寄存器说明：中断状态寄存器
   位域定义UNION结构:  SOC_IPF_INT_STATE_UNION */
#define SOC_IPF_INT_STATE_ADDR(base)                  ((base) + (0x0040))

/* 寄存器说明：超时配置寄存器
   位域定义UNION结构:  SOC_IPF_TIME_OUT_UNION */
#define SOC_IPF_TIME_OUT_ADDR(base)                   ((base) + (0x0044))

/* 寄存器说明：包长配置寄存器
   位域定义UNION结构:  SOC_IPF_PKT_LEN_UNION */
#define SOC_IPF_PKT_LEN_ADDR(base)                    ((base) + (0x0048))

/* 寄存器说明：IPF过滤器起始索引配置寄存器
   位域定义UNION结构:  SOC_IPF_FILTER_ZERO_INDEX_UNION */
#define SOC_IPF_FILTER_ZERO_INDEX_ADDR(base)          ((base) + (0x0070))

/* 寄存器说明：扩展过滤器基地址配置寄存器
   位域定义UNION结构:  SOC_IPF_EF_BADDR_UNION */
#define SOC_IPF_EF_BADDR_ADDR(base)                   ((base) + (0x0074))

/* 寄存器说明：基本过滤表配置索引
   位域定义UNION结构:  SOC_IPF_BFLT_INDEX_UNION */
#define SOC_IPF_BFLT_INDEX_ADDR(base)                 ((base) + (0x0078))

/* 寄存器说明：过滤器链表环告警
   位域定义UNION结构:  SOC_IPF_FLT_CHAIN_LOOP_UNION */
#define SOC_IPF_FLT_CHAIN_LOOP_ADDR(base)             ((base) + (0x007C))

/* 寄存器说明：过滤器local address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_LOCAL_ADDR0_UNION */
#define SOC_IPF_FLT_LOCAL_ADDR0_ADDR(base)            ((base) + (0x0090))

/* 寄存器说明：过滤器local address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_LOCAL_ADDR1_UNION */
#define SOC_IPF_FLT_LOCAL_ADDR1_ADDR(base)            ((base) + (0x0094))

/* 寄存器说明：过滤器local address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_LOCAL_ADDR2_UNION */
#define SOC_IPF_FLT_LOCAL_ADDR2_ADDR(base)            ((base) + (0x0098))

/* 寄存器说明：过滤器local address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_LOCAL_ADDR3_UNION */
#define SOC_IPF_FLT_LOCAL_ADDR3_ADDR(base)            ((base) + (0x009C))

/* 寄存器说明：过滤器remote address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_ADDR0_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR0_ADDR(base)           ((base) + (0x00A0))

/* 寄存器说明：过滤器remote address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_ADDR1_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR1_ADDR(base)           ((base) + (0x00A4))

/* 寄存器说明：过滤器remote address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_ADDR2_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR2_ADDR(base)           ((base) + (0x00A8))

/* 寄存器说明：过滤器remote address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_ADDR3_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR3_ADDR(base)           ((base) + (0x00AC))

/* 寄存器说明：过滤器remote address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_ADDR0_MASK_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR0_MASK_ADDR(base)      ((base) + (0x00B0))

/* 寄存器说明：过滤器remote address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_ADDR1_MASK_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR1_MASK_ADDR(base)      ((base) + (0x00B4))

/* 寄存器说明：过滤器remote address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_ADDR2_MASK_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR2_MASK_ADDR(base)      ((base) + (0x00B8))

/* 寄存器说明：过滤器remote address配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_ADDR3_MASK_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR3_MASK_ADDR(base)      ((base) + (0x00BC))

/* 寄存器说明：过滤表LOCAL PORT门限配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_LOCAL_PORT_UNION */
#define SOC_IPF_FLT_LOCAL_PORT_ADDR(base)             ((base) + (0x00C0))

/* 寄存器说明：过滤表REMOTE PORT门限配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_REMOTE_PORT_UNION */
#define SOC_IPF_FLT_REMOTE_PORT_ADDR(base)            ((base) + (0x00C4))

/* 寄存器说明：过滤表业务等级域配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_TRAFFIC_CLASS_UNION */
#define SOC_IPF_FLT_TRAFFIC_CLASS_ADDR(base)          ((base) + (0x00C8))

/* 寄存器说明：过滤器local address mask域配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_LADD_MASK_UNION */
#define SOC_IPF_FLT_LADD_MASK_ADDR(base)              ((base) + (0x00CC))

/* 寄存器说明：过滤器协议类型域配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_NEXT_HEADER_UNION */
#define SOC_IPF_FLT_NEXT_HEADER_ADDR(base)            ((base) + (0x00D0))

/* 寄存器说明：过滤器流标签域配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_FLOW_LABEL_UNION */
#define SOC_IPF_FLT_FLOW_LABEL_ADDR(base)             ((base) + (0x00D4))

/* 寄存器说明：过滤器ICMP配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_ICMP_UNION */
#define SOC_IPF_FLT_ICMP_ADDR(base)                   ((base) + (0x00D8))

/* 寄存器说明：过滤器链表域配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_CHAIN_UNION */
#define SOC_IPF_FLT_CHAIN_ADDR(base)                  ((base) + (0x00DC))

/* 寄存器说明：过滤器SPI配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_SPI_UNION */
#define SOC_IPF_FLT_SPI_ADDR(base)                    ((base) + (0x00E0))

/* 寄存器说明：过滤器规则控制配置寄存器
   位域定义UNION结构:  SOC_IPF_FLT_RULE_CTRL_UNION */
#define SOC_IPF_FLT_RULE_CTRL_ADDR(base)              ((base) + (0x00E4))

/* 寄存器说明：上行通道控制寄存器
   位域定义UNION结构:  SOC_IPF_CH0_CTRL_UNION */
#define SOC_IPF_CH0_CTRL_ADDR(base)                   ((base) + (0x0100))

/* 寄存器说明：上行通道状态寄存器
   位域定义UNION结构:  SOC_IPF_CH0_STATE_UNION */
#define SOC_IPF_CH0_STATE_ADDR(base)                  ((base) + (0x0104))

/* 寄存器说明：上行通道BDQ起始地址
   位域定义UNION结构:  SOC_IPF_CH0_BDQ_BADDR_UNION */
#define SOC_IPF_CH0_BDQ_BADDR_ADDR(base)              ((base) + (0x0108))

/* 寄存器说明：上行通道BDQ深度
   位域定义UNION结构:  SOC_IPF_CH0_BDQ_SIZE_UNION */
#define SOC_IPF_CH0_BDQ_SIZE_ADDR(base)               ((base) + (0x010C))

/* 寄存器说明：上行通道BDQ写指针
   位域定义UNION结构:  SOC_IPF_CH0_BDQ_WPTR_UNION */
#define SOC_IPF_CH0_BDQ_WPTR_ADDR(base)               ((base) + (0x0110))

/* 寄存器说明：上行通道BDQ读指针
   位域定义UNION结构:  SOC_IPF_CH0_BDQ_RPTR_UNION */
#define SOC_IPF_CH0_BDQ_RPTR_ADDR(base)               ((base) + (0x0114))

/* 寄存器说明：上行通道BDQ写地址
   位域定义UNION结构:  SOC_IPF_CH0_BDQ_WADDR_UNION */
#define SOC_IPF_CH0_BDQ_WADDR_ADDR(base)              ((base) + (0x0118))

/* 寄存器说明：上行通道BDQ读地址
   位域定义UNION结构:  SOC_IPF_CH0_BDQ_RADDR_UNION */
#define SOC_IPF_CH0_BDQ_RADDR_ADDR(base)              ((base) + (0x011C))

/* 寄存器说明：上行通道RDQ起始地址
   位域定义UNION结构:  SOC_IPF_CH0_RDQ_BADDR_UNION */
#define SOC_IPF_CH0_RDQ_BADDR_ADDR(base)              ((base) + (0x0120))

/* 寄存器说明：上行通道RDQ深度
   位域定义UNION结构:  SOC_IPF_CH0_RDQ_SIZE_UNION */
#define SOC_IPF_CH0_RDQ_SIZE_ADDR(base)               ((base) + (0x0124))

/* 寄存器说明：上行通道RDQ写指针
   位域定义UNION结构:  SOC_IPF_CH0_RDQ_WPTR_UNION */
#define SOC_IPF_CH0_RDQ_WPTR_ADDR(base)               ((base) + (0x0128))

/* 寄存器说明：上行通道RDQ读指针
   位域定义UNION结构:  SOC_IPF_CH0_RDQ_RPTR_UNION */
#define SOC_IPF_CH0_RDQ_RPTR_ADDR(base)               ((base) + (0x012C))

/* 寄存器说明：上行通道RDQ写地址
   位域定义UNION结构:  SOC_IPF_CH0_RDQ_WADDR_UNION */
#define SOC_IPF_CH0_RDQ_WADDR_ADDR(base)              ((base) + (0x0130))

/* 寄存器说明：上行通道RDQ读地址
   位域定义UNION结构:  SOC_IPF_CH0_RDQ_RADDR_UNION */
#define SOC_IPF_CH0_RDQ_RADDR_ADDR(base)              ((base) + (0x0134))

/* 寄存器说明：上行通道队列深度指示寄存器
   位域定义UNION结构:  SOC_IPF_CH0_DQ_DEPTH_UNION */
#define SOC_IPF_CH0_DQ_DEPTH_ADDR(base)               ((base) + (0x0138))

/* 寄存器说明：下行通道控制寄存器
   位域定义UNION结构:  SOC_IPF_CH1_CTRL_UNION */
#define SOC_IPF_CH1_CTRL_ADDR(base)                   ((base) + (0x0150))

/* 寄存器说明：下行通道状态寄存器
   位域定义UNION结构:  SOC_IPF_CH1_STATE_UNION */
#define SOC_IPF_CH1_STATE_ADDR(base)                  ((base) + (0x0154))

/* 寄存器说明：下行通道BDQ起始地址
   位域定义UNION结构:  SOC_IPF_CH1_BDQ_BADDR_UNION */
#define SOC_IPF_CH1_BDQ_BADDR_ADDR(base)              ((base) + (0x0158))

/* 寄存器说明：下行通道BDQ深度
   位域定义UNION结构:  SOC_IPF_CH1_BDQ_SIZE_UNION */
#define SOC_IPF_CH1_BDQ_SIZE_ADDR(base)               ((base) + (0x015C))

/* 寄存器说明：下行通道BDQ写指针
   位域定义UNION结构:  SOC_IPF_CH1_BDQ_WPTR_UNION */
#define SOC_IPF_CH1_BDQ_WPTR_ADDR(base)               ((base) + (0x0160))

/* 寄存器说明：下行通道BDQ读指针
   位域定义UNION结构:  SOC_IPF_CH1_BDQ_RPTR_UNION */
#define SOC_IPF_CH1_BDQ_RPTR_ADDR(base)               ((base) + (0x0164))

/* 寄存器说明：下行通道BDQ写地址
   位域定义UNION结构:  SOC_IPF_CH1_BDQ_WADDR_UNION */
#define SOC_IPF_CH1_BDQ_WADDR_ADDR(base)              ((base) + (0x0168))

/* 寄存器说明：下行通道BDQ读地址
   位域定义UNION结构:  SOC_IPF_CH1_BDQ_RADDR_UNION */
#define SOC_IPF_CH1_BDQ_RADDR_ADDR(base)              ((base) + (0x016C))

/* 寄存器说明：下行通道RDQ起始地址
   位域定义UNION结构:  SOC_IPF_CH1_RDQ_BADDR_UNION */
#define SOC_IPF_CH1_RDQ_BADDR_ADDR(base)              ((base) + (0x0170))

/* 寄存器说明：下行通道RDQ深度
   位域定义UNION结构:  SOC_IPF_CH1_RDQ_SIZE_UNION */
#define SOC_IPF_CH1_RDQ_SIZE_ADDR(base)               ((base) + (0x0174))

/* 寄存器说明：下行通道RDQ写指针
   位域定义UNION结构:  SOC_IPF_CH1_RDQ_WPTR_UNION */
#define SOC_IPF_CH1_RDQ_WPTR_ADDR(base)               ((base) + (0x0178))

/* 寄存器说明：下行通道RDQ读指针
   位域定义UNION结构:  SOC_IPF_CH1_RDQ_RPTR_UNION */
#define SOC_IPF_CH1_RDQ_RPTR_ADDR(base)               ((base) + (0x017C))

/* 寄存器说明：下行通道RDQ写地址
   位域定义UNION结构:  SOC_IPF_CH1_RDQ_WADDR_UNION */
#define SOC_IPF_CH1_RDQ_WADDR_ADDR(base)              ((base) + (0x0180))

/* 寄存器说明：下行通道RDQ读地址
   位域定义UNION结构:  SOC_IPF_CH1_RDQ_RADDR_UNION */
#define SOC_IPF_CH1_RDQ_RADDR_ADDR(base)              ((base) + (0x0184))

/* 寄存器说明：下行通道队列深度指示寄存器
   位域定义UNION结构:  SOC_IPF_CH1_DQ_DEPTH_UNION */
#define SOC_IPF_CH1_DQ_DEPTH_ADDR(base)               ((base) + (0x0188))

/* 寄存器说明：上行通道ADQ控制寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ_CTRL_UNION */
#define SOC_IPF_CH0_ADQ_CTRL_ADDR(base)               ((base) + (0x0204))

/* 寄存器说明：上行通道ADQ0基址寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ0_BASE_UNION */
#define SOC_IPF_CH0_ADQ0_BASE_ADDR(base)              ((base) + (0x0210))

/* 寄存器说明：上行通道ADQ0状态寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ0_STAT_UNION */
#define SOC_IPF_CH0_ADQ0_STAT_ADDR(base)              ((base) + (0x0214))

/* 寄存器说明：上行通道ADQ0写指针寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ0_WPTR_UNION */
#define SOC_IPF_CH0_ADQ0_WPTR_ADDR(base)              ((base) + (0x0218))

/* 寄存器说明：上行通道ADQ0读指针寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ0_RPTR_UNION */
#define SOC_IPF_CH0_ADQ0_RPTR_ADDR(base)              ((base) + (0x021C))

/* 寄存器说明：上行通道ADQ1基址寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ1_BASE_UNION */
#define SOC_IPF_CH0_ADQ1_BASE_ADDR(base)              ((base) + (0x0220))

/* 寄存器说明：上行通道ADQ1状态寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ1_STAT_UNION */
#define SOC_IPF_CH0_ADQ1_STAT_ADDR(base)              ((base) + (0x0224))

/* 寄存器说明：上行通道ADQ1写指针寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ1_WPTR_UNION */
#define SOC_IPF_CH0_ADQ1_WPTR_ADDR(base)              ((base) + (0x0228))

/* 寄存器说明：上行通道ADQ1读指针寄存器
   位域定义UNION结构:  SOC_IPF_CH0_ADQ1_RPTR_UNION */
#define SOC_IPF_CH0_ADQ1_RPTR_ADDR(base)              ((base) + (0x022C))

/* 寄存器说明：下行通道ADQ控制寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ_CTRL_UNION */
#define SOC_IPF_CH1_ADQ_CTRL_ADDR(base)               ((base) + (0x0284))

/* 寄存器说明：下行通道ADQ0基址寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ0_BASE_UNION */
#define SOC_IPF_CH1_ADQ0_BASE_ADDR(base)              ((base) + (0x0290))

/* 寄存器说明：下行通道ADQ0状态寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ0_STAT_UNION */
#define SOC_IPF_CH1_ADQ0_STAT_ADDR(base)              ((base) + (0x0294))

/* 寄存器说明：下行通道ADQ0写指针寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ0_WPTR_UNION */
#define SOC_IPF_CH1_ADQ0_WPTR_ADDR(base)              ((base) + (0x0298))

/* 寄存器说明：下行通道ADQ0读指针寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ0_RPTR_UNION */
#define SOC_IPF_CH1_ADQ0_RPTR_ADDR(base)              ((base) + (0x029C))

/* 寄存器说明：下行通道ADQ1基址寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ1_BASE_UNION */
#define SOC_IPF_CH1_ADQ1_BASE_ADDR(base)              ((base) + (0x02A0))

/* 寄存器说明：下行通道ADQ1状态寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ1_STAT_UNION */
#define SOC_IPF_CH1_ADQ1_STAT_ADDR(base)              ((base) + (0x02A4))

/* 寄存器说明：下行通道ADQ1写指针寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ1_WPTR_UNION */
#define SOC_IPF_CH1_ADQ1_WPTR_ADDR(base)              ((base) + (0x02A8))

/* 寄存器说明：下行通道ADQ1读指针寄存器
   位域定义UNION结构:  SOC_IPF_CH1_ADQ1_RPTR_UNION */
#define SOC_IPF_CH1_ADQ1_RPTR_ADDR(base)              ((base) + (0x02AC))





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
                     (1/1) IPF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_IPF_SRST_UNION
 结构说明  : SRST 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: IPF复位控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipf_srst : 1;  /* bit[0]   : 全局软复位寄存器。
                                                   0：不复位；
                                                   1：复位。
                                                   高电平有效。只复位逻辑不复位配置寄存器.复位可能不能立即生效，由复位状态寄存器指示复位是否成功，复位成功后写0解除软复位。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_IPF_SRST_UNION;
#endif
#define SOC_IPF_SRST_ipf_srst_START  (0)
#define SOC_IPF_SRST_ipf_srst_END    (0)


/*****************************************************************************
 结构名    : SOC_IPF_SRST_STATE_UNION
 结构说明  : SRST_STATE 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: IPF复位状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipf_srst_state : 1;  /* bit[0]   : 复位状态指示寄存器。
                                                         0：未处于复位状态；
                                                         1：处于复位状态，表示复位成功。
                                                         当逻辑处于复位状态软件可解除复位。 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IPF_SRST_STATE_UNION;
#endif
#define SOC_IPF_SRST_STATE_ipf_srst_state_START  (0)
#define SOC_IPF_SRST_STATE_ipf_srst_state_END    (0)


/*****************************************************************************
 结构名    : SOC_IPF_CH_EN_UNION
 结构说明  : CH_EN 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: IPF 通道使能配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_en    : 1;  /* bit[0]   : UL通道使能配置寄存器.
                                                   0:通道关闭
                                                   1:通道使能
                                                   写1使能通道，立即生效.写0关闭通道,若此时通道busy，则不能立即关闭，直到通道idle后才能关闭. */
        unsigned int  dl_en    : 1;  /* bit[1]   : DL通道使能配置寄存器.
                                                   0:通道关闭
                                                   1:通道使能
                                                   写1使能通道，立即生效.写0关闭通道,若此时通道busy，则不能立即关闭，直到通道idle后才能关闭. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IPF_CH_EN_UNION;
#endif
#define SOC_IPF_CH_EN_ul_en_START     (0)
#define SOC_IPF_CH_EN_ul_en_END       (0)
#define SOC_IPF_CH_EN_dl_en_START     (1)
#define SOC_IPF_CH_EN_dl_en_END       (1)


/*****************************************************************************
 结构名    : SOC_IPF_EN_STATE_UNION
 结构说明  : EN_STATE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: IPF 通道使能状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_en_state : 1;  /* bit[0]   : UL通道使能状态寄存器.
                                                      0:通道已关闭
                                                      1:通道打开 */
        unsigned int  dl_en_state : 1;  /* bit[1]   : DL通道使能状态寄存器.
                                                      0:通道已关闭
                                                      1:通道打开 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IPF_EN_STATE_UNION;
#endif
#define SOC_IPF_EN_STATE_ul_en_state_START  (0)
#define SOC_IPF_EN_STATE_ul_en_state_END    (0)
#define SOC_IPF_EN_STATE_dl_en_state_START  (1)
#define SOC_IPF_EN_STATE_dl_en_state_END    (1)


/*****************************************************************************
 结构名    : SOC_IPF_GATE_UNION
 结构说明  : GATE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: IPF时钟门控配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipf_sysclk_sel0 : 1;  /* bit[0]    : ipf模块系统时钟门控使能。
                                                           0:时钟常开
                                                           1:自动门控  */
        unsigned int  ipf_sysclk_sel1 : 1;  /* bit[1]    : ipf模块系统时钟门控使能。
                                                           0:时钟常开
                                                           1:自动门控  */
        unsigned int  ipf_busclk_sel  : 1;  /* bit[2]    : ipf模块总线时钟门控使能。
                                                           0:时钟常开
                                                           1:自动门控  */
        unsigned int  reserved_0      : 5;  /* bit[3-7]  : 保留。 */
        unsigned int  ipf_ram0clk_sel : 1;  /* bit[8]    : ipf模块单口RAM时钟门控使能。
                                                           0:时钟常开
                                                           1:自动门控 */
        unsigned int  ipf_ram1clk_sel : 1;  /* bit[9]    : ipf模块双口RAM时钟门控使能。
                                                           0:时钟常开
                                                           1:自动门控 */
        unsigned int  reserved_1      : 22; /* bit[10-31]: 保留。 */
    } reg;
} SOC_IPF_GATE_UNION;
#endif
#define SOC_IPF_GATE_ipf_sysclk_sel0_START  (0)
#define SOC_IPF_GATE_ipf_sysclk_sel0_END    (0)
#define SOC_IPF_GATE_ipf_sysclk_sel1_START  (1)
#define SOC_IPF_GATE_ipf_sysclk_sel1_END    (1)
#define SOC_IPF_GATE_ipf_busclk_sel_START   (2)
#define SOC_IPF_GATE_ipf_busclk_sel_END     (2)
#define SOC_IPF_GATE_ipf_ram0clk_sel_START  (8)
#define SOC_IPF_GATE_ipf_ram0clk_sel_END    (8)
#define SOC_IPF_GATE_ipf_ram1clk_sel_START  (9)
#define SOC_IPF_GATE_ipf_ram1clk_sel_END    (9)


/*****************************************************************************
 结构名    : SOC_IPF_CTRL_UNION
 结构说明  : CTRL 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: IPF全局控制配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_seq       : 1;  /* bit[0]    : 过滤器配置顺序指示寄存器.
                                                            0:过滤器配置顺序排序
                                                            1:过滤器配置乱序排序 */
        unsigned int  flt_addr_reverse : 1;  /* bit[1]    : 0：表示过滤器中的地址寄存器按大端排列
                                                            1：表示过滤器中的地址寄存器按小端排列 */
        unsigned int  sp_cfg           : 1;  /* bit[2]    : 0:SP模式下DL优先级高
                                                            1;SP模式下UL优先级高 */
        unsigned int  sp_wrr_sel       : 1;  /* bit[3]    : 0:WRR模式调度
                                                            1;SP模式调度 */
        unsigned int  max_burst_len    : 2;  /* bit[4-5]  : BURST最大长度配置寄存器
                                                            2'b00:BURST16
                                                            2'b01:BURST8
                                                            2'b10,2'b11:BURST4 */
        unsigned int  ipv6_nh_sel      : 1;  /* bit[6]    : IPV6 参与匹配NextNeader选择控制信号
                                                            0:解析的上层报文对应的NextHeader或不识别的NextHeader(注意AH和ESP共存时NextHeader对应的时选择之后的NextHeader)
                                                            1:基本头中的NextNeader */
        unsigned int  ah_esp_sel       : 1;  /* bit[7]    : 如果AH和ESP同时存在且均配置为参与匹配,SPI选择控制信号
                                                            0:选择ESP对应的SPI参与匹配
                                                            1:选择AH对应的SPI参与匹配 */
        unsigned int  ah_disable       : 1;  /* bit[8]    : AH SPI是否参与匹配控制信号
                                                            0:参与匹配
                                                            1:不参与匹配 */
        unsigned int  esp_disable      : 1;  /* bit[9]    : ESP SPI是否参与匹配控制信号
                                                            0:参与匹配
                                                            1:不参与匹配 */
        unsigned int  mfc_en           : 1;  /* bit[10]   : 单通道多过滤器链使能
                                                            0：每个通道只能支持一个过滤器链，链表头索引静态配置；
                                                            1：每个通道最多支持8个过滤器链，链表头索引由BD动态配置； */
        unsigned int  mm_en            : 1;  /* bit[11]   : 单通道动态模式使能
                                                            0：每个通道模式由通道控制寄存器静态配置；
                                                            1：每个通道模式由BD中mode标志动态配置； */
        unsigned int  add_rep          : 1;  /* bit[12]   : 下行通道AD上报选择。
                                                            0：表示RD上报目的地址使用AD的第二个字；
                                                            1：表示RD上报目的地址使用AD的第一个字； */
        unsigned int  reserved         : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_IPF_CTRL_UNION;
#endif
#define SOC_IPF_CTRL_filter_seq_START        (0)
#define SOC_IPF_CTRL_filter_seq_END          (0)
#define SOC_IPF_CTRL_flt_addr_reverse_START  (1)
#define SOC_IPF_CTRL_flt_addr_reverse_END    (1)
#define SOC_IPF_CTRL_sp_cfg_START            (2)
#define SOC_IPF_CTRL_sp_cfg_END              (2)
#define SOC_IPF_CTRL_sp_wrr_sel_START        (3)
#define SOC_IPF_CTRL_sp_wrr_sel_END          (3)
#define SOC_IPF_CTRL_max_burst_len_START     (4)
#define SOC_IPF_CTRL_max_burst_len_END       (5)
#define SOC_IPF_CTRL_ipv6_nh_sel_START       (6)
#define SOC_IPF_CTRL_ipv6_nh_sel_END         (6)
#define SOC_IPF_CTRL_ah_esp_sel_START        (7)
#define SOC_IPF_CTRL_ah_esp_sel_END          (7)
#define SOC_IPF_CTRL_ah_disable_START        (8)
#define SOC_IPF_CTRL_ah_disable_END          (8)
#define SOC_IPF_CTRL_esp_disable_START       (9)
#define SOC_IPF_CTRL_esp_disable_END         (9)
#define SOC_IPF_CTRL_mfc_en_START            (10)
#define SOC_IPF_CTRL_mfc_en_END              (10)
#define SOC_IPF_CTRL_mm_en_START             (11)
#define SOC_IPF_CTRL_mm_en_END               (11)
#define SOC_IPF_CTRL_add_rep_START           (12)
#define SOC_IPF_CTRL_add_rep_END             (12)


/*****************************************************************************
 结构名    : SOC_IPF_DMA_CTRL0_UNION
 结构说明  : DMA_CTRL0 寄存器结构定义。地址偏移量:0x0018，初值:0x0FBE1010，宽度:32
 寄存器说明: IPF DMA控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipf_wr_ch0_id  : 4;  /* bit[0-3]  : AXI写通道0 ID */
        unsigned int  ipf_wr_ch1_id  : 4;  /* bit[4-7]  : AXI写通道1 ID */
        unsigned int  ipf_rd_ch0_id  : 4;  /* bit[8-11] : AXI读通道0 ID */
        unsigned int  ipf_rd_ch1_id  : 4;  /* bit[12-15]: AXI读通道1 ID */
        unsigned int  ipf_wr_ch0_pri : 3;  /* bit[16-18]: AXI写通道0优先级 */
        unsigned int  reserved_0     : 1;  /* bit[19]   : 保留 */
        unsigned int  ipf_wr_ch1_pri : 3;  /* bit[20-22]: AXI写通道1优先级 */
        unsigned int  reserved_1     : 1;  /* bit[23]   : 保留 */
        unsigned int  ipf_rd_ch0_pri : 3;  /* bit[24-26]: AXI读通道0优先级 */
        unsigned int  reserved_2     : 1;  /* bit[27]   : 保留 */
        unsigned int  ipf_rd_ch1_pri : 3;  /* bit[28-30]: AXI读通道1优先级 */
        unsigned int  reserved_3     : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_IPF_DMA_CTRL0_UNION;
#endif
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch0_id_START   (0)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch0_id_END     (3)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch1_id_START   (4)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch1_id_END     (7)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch0_id_START   (8)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch0_id_END     (11)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch1_id_START   (12)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch1_id_END     (15)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch0_pri_START  (16)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch0_pri_END    (18)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch1_pri_START  (20)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch1_pri_END    (22)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch0_pri_START  (24)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch0_pri_END    (26)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch1_pri_START  (28)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch1_pri_END    (30)


/*****************************************************************************
 结构名    : SOC_IPF_DMA_CTRL1_UNION
 结构说明  : DMA_CTRL1 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: IPF DMA控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  outstanding_w : 1;  /* bit[0]   : 写通道outstanding使能。
                                                        0：AXI master没有写outstanding操作；
                                                        1：AXI master有写outstanding操作，outstanding深度为4； */
        unsigned int  outstanding_r : 1;  /* bit[1]   : 读通道outstanding使能。
                                                        0：AXI master没有读outstanding操作；
                                                        1：AXI master有读outstanding操作，outstanding深度为4； */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_IPF_DMA_CTRL1_UNION;
#endif
#define SOC_IPF_DMA_CTRL1_outstanding_w_START  (0)
#define SOC_IPF_DMA_CTRL1_outstanding_w_END    (0)
#define SOC_IPF_DMA_CTRL1_outstanding_r_START  (1)
#define SOC_IPF_DMA_CTRL1_outstanding_r_END    (1)


/*****************************************************************************
 结构名    : SOC_IPF_INT0_UNION
 结构说明  : INT0 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 中断上报寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt_int0              : 1;  /* bit[0]    : 上行结果上报中断0 */
        unsigned int  ul_timeout_int0          : 1;  /* bit[1]    : 上行结果上报超时中断0 */
        unsigned int  ul_disable_end_int0      : 1;  /* bit[2]    : 上行通道关闭完成中断0 */
        unsigned int  ul_idle_cfg_bd_int0      : 1;  /* bit[3]    : 上行通道IDLE期间软件配置BD指示中断0 */
        unsigned int  ul_trail_cfg_bd_int0     : 1;  /* bit[4]    : 上行通道关闭但BD没有处理完期间软件继续配置BD指示中断0 */
        unsigned int  ul_noidle_clrptr_int0    : 1;  /* bit[5]    : 上行非IDLE态清指针指示中断0 */
        unsigned int  ul_rdq_downoverflow_int0 : 1;  /* bit[6]    : 上行RDQ下溢中断0 */
        unsigned int  ul_bdq_upoverflow_int0   : 1;  /* bit[7]    : 上行BDQ上溢中断0 */
        unsigned int  ul_rdq_full_int0         : 1;  /* bit[8]    : 上行RDQ满中断0 */
        unsigned int  ul_bdq_epty_int0         : 1;  /* bit[9]    : 上行BDQ空中断0 */
        unsigned int  ul_adq0_epty_int0        : 1;  /* bit[10]   : 上行ADQ0空中断0 */
        unsigned int  ul_adq1_epty_int0        : 1;  /* bit[11]   : 上行ADQ1空中断0 */
        unsigned int  reserved_0               : 4;  /* bit[12-15]: 保留 */
        unsigned int  dl_rpt_int0              : 1;  /* bit[16]   : 下行结果上报中断0 */
        unsigned int  dl_timeout_int0          : 1;  /* bit[17]   : 下行结果上报超时中断0 */
        unsigned int  dl_disable_end_int0      : 1;  /* bit[18]   : 下行通道关闭完成中断0 */
        unsigned int  dl_idle_cfg_bd_int0      : 1;  /* bit[19]   : 下行通道IDLE期间软件配置BD指示中断0 */
        unsigned int  dl_trail_cfg_bd_int0     : 1;  /* bit[20]   : 下行通道关闭但BD没有处理完期间软件继续配置BD指示中断0 */
        unsigned int  dl_noidle_clrptr_int0    : 1;  /* bit[21]   : 下行非IDLE态清指针指示中断0 */
        unsigned int  dl_rdq_downoverflow_int0 : 1;  /* bit[22]   : 下行RDQ下溢中断0 */
        unsigned int  dl_bdq_upoverflow_int0   : 1;  /* bit[23]   : 下行BDQ上溢中断0 */
        unsigned int  dl_rdq_full_int0         : 1;  /* bit[24]   : 下行RDQ满中断0 */
        unsigned int  dl_bdq_epty_int0         : 1;  /* bit[25]   : 下行BDQ空中断0 */
        unsigned int  dl_adq0_epty_int0        : 1;  /* bit[26]   : 下行ADQ0空中断0 */
        unsigned int  dl_adq1_epty_int0        : 1;  /* bit[27]   : 下行ADQ1空中断0 */
        unsigned int  reserved_1               : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_IPF_INT0_UNION;
#endif
#define SOC_IPF_INT0_ul_rpt_int0_START               (0)
#define SOC_IPF_INT0_ul_rpt_int0_END                 (0)
#define SOC_IPF_INT0_ul_timeout_int0_START           (1)
#define SOC_IPF_INT0_ul_timeout_int0_END             (1)
#define SOC_IPF_INT0_ul_disable_end_int0_START       (2)
#define SOC_IPF_INT0_ul_disable_end_int0_END         (2)
#define SOC_IPF_INT0_ul_idle_cfg_bd_int0_START       (3)
#define SOC_IPF_INT0_ul_idle_cfg_bd_int0_END         (3)
#define SOC_IPF_INT0_ul_trail_cfg_bd_int0_START      (4)
#define SOC_IPF_INT0_ul_trail_cfg_bd_int0_END        (4)
#define SOC_IPF_INT0_ul_noidle_clrptr_int0_START     (5)
#define SOC_IPF_INT0_ul_noidle_clrptr_int0_END       (5)
#define SOC_IPF_INT0_ul_rdq_downoverflow_int0_START  (6)
#define SOC_IPF_INT0_ul_rdq_downoverflow_int0_END    (6)
#define SOC_IPF_INT0_ul_bdq_upoverflow_int0_START    (7)
#define SOC_IPF_INT0_ul_bdq_upoverflow_int0_END      (7)
#define SOC_IPF_INT0_ul_rdq_full_int0_START          (8)
#define SOC_IPF_INT0_ul_rdq_full_int0_END            (8)
#define SOC_IPF_INT0_ul_bdq_epty_int0_START          (9)
#define SOC_IPF_INT0_ul_bdq_epty_int0_END            (9)
#define SOC_IPF_INT0_ul_adq0_epty_int0_START         (10)
#define SOC_IPF_INT0_ul_adq0_epty_int0_END           (10)
#define SOC_IPF_INT0_ul_adq1_epty_int0_START         (11)
#define SOC_IPF_INT0_ul_adq1_epty_int0_END           (11)
#define SOC_IPF_INT0_dl_rpt_int0_START               (16)
#define SOC_IPF_INT0_dl_rpt_int0_END                 (16)
#define SOC_IPF_INT0_dl_timeout_int0_START           (17)
#define SOC_IPF_INT0_dl_timeout_int0_END             (17)
#define SOC_IPF_INT0_dl_disable_end_int0_START       (18)
#define SOC_IPF_INT0_dl_disable_end_int0_END         (18)
#define SOC_IPF_INT0_dl_idle_cfg_bd_int0_START       (19)
#define SOC_IPF_INT0_dl_idle_cfg_bd_int0_END         (19)
#define SOC_IPF_INT0_dl_trail_cfg_bd_int0_START      (20)
#define SOC_IPF_INT0_dl_trail_cfg_bd_int0_END        (20)
#define SOC_IPF_INT0_dl_noidle_clrptr_int0_START     (21)
#define SOC_IPF_INT0_dl_noidle_clrptr_int0_END       (21)
#define SOC_IPF_INT0_dl_rdq_downoverflow_int0_START  (22)
#define SOC_IPF_INT0_dl_rdq_downoverflow_int0_END    (22)
#define SOC_IPF_INT0_dl_bdq_upoverflow_int0_START    (23)
#define SOC_IPF_INT0_dl_bdq_upoverflow_int0_END      (23)
#define SOC_IPF_INT0_dl_rdq_full_int0_START          (24)
#define SOC_IPF_INT0_dl_rdq_full_int0_END            (24)
#define SOC_IPF_INT0_dl_bdq_epty_int0_START          (25)
#define SOC_IPF_INT0_dl_bdq_epty_int0_END            (25)
#define SOC_IPF_INT0_dl_adq0_epty_int0_START         (26)
#define SOC_IPF_INT0_dl_adq0_epty_int0_END           (26)
#define SOC_IPF_INT0_dl_adq1_epty_int0_START         (27)
#define SOC_IPF_INT0_dl_adq1_epty_int0_END           (27)


/*****************************************************************************
 结构名    : SOC_IPF_INT1_UNION
 结构说明  : INT1 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 中断上报寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt_int1              : 1;  /* bit[0]    : 上行结果上报中断1 */
        unsigned int  ul_timeout_int1          : 1;  /* bit[1]    : 上行结果上报超时中断1 */
        unsigned int  ul_disable_end_int1      : 1;  /* bit[2]    : 上行通道关闭完成中断1 */
        unsigned int  ul_idle_cfg_bd_int1      : 1;  /* bit[3]    : 上行通道IDLE期间软件配置BD指示中断1 */
        unsigned int  ul_trail_cfg_bd_int1     : 1;  /* bit[4]    : 上行通道关闭但BD没有处理完期间软件继续配置BD指示中断1 */
        unsigned int  ul_noidle_clrptr_int1    : 1;  /* bit[5]    : 上行非IDLE态清指针指示中断1 */
        unsigned int  ul_rdq_downoverflow_int1 : 1;  /* bit[6]    : 上行RDQ下溢中断1 */
        unsigned int  ul_bdq_upoverflow_int1   : 1;  /* bit[7]    : 上行BDQ上溢中断1 */
        unsigned int  ul_rdq_full_int1         : 1;  /* bit[8]    : 上行RDQ满中断1 */
        unsigned int  ul_bdq_epty_int1         : 1;  /* bit[9]    : 上行BDQ空中断1 */
        unsigned int  ul_adq0_epty_int1        : 1;  /* bit[10]   : 上行ADQ0空中断1 */
        unsigned int  ul_adq1_epty_int1        : 1;  /* bit[11]   : 上行ADQ1空中断1 */
        unsigned int  reserved_0               : 4;  /* bit[12-15]: 保留 */
        unsigned int  dl_rpt_int1              : 1;  /* bit[16]   : 下行结果上报中断1 */
        unsigned int  dl_timeout_int1          : 1;  /* bit[17]   : 下行结果上报超时中断1 */
        unsigned int  dl_disable_end_int1      : 1;  /* bit[18]   : 下行通道关闭完成中断1 */
        unsigned int  dl_idle_cfg_bd_int1      : 1;  /* bit[19]   : 下行通道IDLE期间软件配置BD指示中断1 */
        unsigned int  dl_trail_cfg_bd_int1     : 1;  /* bit[20]   : 下行通道关闭但BD没有处理完期间软件继续配置BD指示中断1 */
        unsigned int  dl_noidle_clrptr_int1    : 1;  /* bit[21]   : 下行非IDLE态清指针指示中断1 */
        unsigned int  dl_rdq_downoverflow_int1 : 1;  /* bit[22]   : 下行RDQ下溢中断1 */
        unsigned int  dl_bdq_upoverflow_int1   : 1;  /* bit[23]   : 下行BDQ上溢中断1 */
        unsigned int  dl_rdq_full_int1         : 1;  /* bit[24]   : 下行RDQ满中断1 */
        unsigned int  dl_bdq_epty_int1         : 1;  /* bit[25]   : 下行BDQ空中断1 */
        unsigned int  dl_adq0_epty_int1        : 1;  /* bit[26]   : 下行ADQ0空中断1 */
        unsigned int  dl_adq1_epty_int1        : 1;  /* bit[27]   : 下行ADQ1空中断1 */
        unsigned int  reserved_1               : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_IPF_INT1_UNION;
#endif
#define SOC_IPF_INT1_ul_rpt_int1_START               (0)
#define SOC_IPF_INT1_ul_rpt_int1_END                 (0)
#define SOC_IPF_INT1_ul_timeout_int1_START           (1)
#define SOC_IPF_INT1_ul_timeout_int1_END             (1)
#define SOC_IPF_INT1_ul_disable_end_int1_START       (2)
#define SOC_IPF_INT1_ul_disable_end_int1_END         (2)
#define SOC_IPF_INT1_ul_idle_cfg_bd_int1_START       (3)
#define SOC_IPF_INT1_ul_idle_cfg_bd_int1_END         (3)
#define SOC_IPF_INT1_ul_trail_cfg_bd_int1_START      (4)
#define SOC_IPF_INT1_ul_trail_cfg_bd_int1_END        (4)
#define SOC_IPF_INT1_ul_noidle_clrptr_int1_START     (5)
#define SOC_IPF_INT1_ul_noidle_clrptr_int1_END       (5)
#define SOC_IPF_INT1_ul_rdq_downoverflow_int1_START  (6)
#define SOC_IPF_INT1_ul_rdq_downoverflow_int1_END    (6)
#define SOC_IPF_INT1_ul_bdq_upoverflow_int1_START    (7)
#define SOC_IPF_INT1_ul_bdq_upoverflow_int1_END      (7)
#define SOC_IPF_INT1_ul_rdq_full_int1_START          (8)
#define SOC_IPF_INT1_ul_rdq_full_int1_END            (8)
#define SOC_IPF_INT1_ul_bdq_epty_int1_START          (9)
#define SOC_IPF_INT1_ul_bdq_epty_int1_END            (9)
#define SOC_IPF_INT1_ul_adq0_epty_int1_START         (10)
#define SOC_IPF_INT1_ul_adq0_epty_int1_END           (10)
#define SOC_IPF_INT1_ul_adq1_epty_int1_START         (11)
#define SOC_IPF_INT1_ul_adq1_epty_int1_END           (11)
#define SOC_IPF_INT1_dl_rpt_int1_START               (16)
#define SOC_IPF_INT1_dl_rpt_int1_END                 (16)
#define SOC_IPF_INT1_dl_timeout_int1_START           (17)
#define SOC_IPF_INT1_dl_timeout_int1_END             (17)
#define SOC_IPF_INT1_dl_disable_end_int1_START       (18)
#define SOC_IPF_INT1_dl_disable_end_int1_END         (18)
#define SOC_IPF_INT1_dl_idle_cfg_bd_int1_START       (19)
#define SOC_IPF_INT1_dl_idle_cfg_bd_int1_END         (19)
#define SOC_IPF_INT1_dl_trail_cfg_bd_int1_START      (20)
#define SOC_IPF_INT1_dl_trail_cfg_bd_int1_END        (20)
#define SOC_IPF_INT1_dl_noidle_clrptr_int1_START     (21)
#define SOC_IPF_INT1_dl_noidle_clrptr_int1_END       (21)
#define SOC_IPF_INT1_dl_rdq_downoverflow_int1_START  (22)
#define SOC_IPF_INT1_dl_rdq_downoverflow_int1_END    (22)
#define SOC_IPF_INT1_dl_bdq_upoverflow_int1_START    (23)
#define SOC_IPF_INT1_dl_bdq_upoverflow_int1_END      (23)
#define SOC_IPF_INT1_dl_rdq_full_int1_START          (24)
#define SOC_IPF_INT1_dl_rdq_full_int1_END            (24)
#define SOC_IPF_INT1_dl_bdq_epty_int1_START          (25)
#define SOC_IPF_INT1_dl_bdq_epty_int1_END            (25)
#define SOC_IPF_INT1_dl_adq0_epty_int1_START         (26)
#define SOC_IPF_INT1_dl_adq0_epty_int1_END           (26)
#define SOC_IPF_INT1_dl_adq1_epty_int1_START         (27)
#define SOC_IPF_INT1_dl_adq1_epty_int1_END           (27)


/*****************************************************************************
 结构名    : SOC_IPF_INT_MASK0_UNION
 结构说明  : INT_MASK0 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt_mask0              : 1;  /* bit[0]    : 上行结果上报中断屏蔽寄存器0 */
        unsigned int  ul_timeout_mask0          : 1;  /* bit[1]    : 上行结果上报超时中断屏蔽寄存器0 */
        unsigned int  ul_disable_end_mask0      : 1;  /* bit[2]    : 上行通道关闭完成中断屏蔽寄存器0 */
        unsigned int  ul_idle_cfg_bd_mask0      : 1;  /* bit[3]    : 上行通道IDLE期间软件配置BD指示中断屏蔽寄存器0 */
        unsigned int  ul_trail_cfg_bd_mask0     : 1;  /* bit[4]    : 上行通道关闭但BD没有处理完期间软件继续配置BD指示中断屏蔽寄存器0 */
        unsigned int  ul_noidle_clrptr_mask0    : 1;  /* bit[5]    : 上行非IDLE态清指针指示中断屏蔽寄存器0 */
        unsigned int  ul_rdq_downoverflow_mask0 : 1;  /* bit[6]    : 上行RDQ下溢中断屏蔽寄存器0 */
        unsigned int  ul_bdq_upoverflow_mask0   : 1;  /* bit[7]    : 上行BDQ上溢中断屏蔽寄存器0 */
        unsigned int  ul_rdq_full_mask0         : 1;  /* bit[8]    : 上行RDQ满中断屏蔽寄存器0 */
        unsigned int  ul_bdq_epty_mask0         : 1;  /* bit[9]    : 上行BDQ空中断屏蔽寄存器0 */
        unsigned int  ul_adq0_epty_mask0        : 1;  /* bit[10]   : 上行ADQ0空中断屏蔽寄存器0 */
        unsigned int  ul_adq1_epty_mask0        : 1;  /* bit[11]   : 上行ADQ1空中断屏蔽寄存器0 */
        unsigned int  reserved_0                : 4;  /* bit[12-15]: 保留 */
        unsigned int  dl_rpt_mask0              : 1;  /* bit[16]   : 下行结果上报中断屏蔽寄存器0 */
        unsigned int  dl_timeout_mask0          : 1;  /* bit[17]   : 下行结果上报超时中断屏蔽寄存器0 */
        unsigned int  dl_disable_end_mask0      : 1;  /* bit[18]   : 下行通道关闭完成中断屏蔽寄存器0 */
        unsigned int  dl_idle_cfg_bd_mask0      : 1;  /* bit[19]   : 下行通道IDLE期间软件配置BD指示中断屏蔽寄存器0 */
        unsigned int  dl_trail_cfg_bd_mask0     : 1;  /* bit[20]   : 下行通道关闭但BD没有处理完期间软件继续配置BD指示中断屏蔽寄存器0 */
        unsigned int  dl_noidle_clrptr_mask0    : 1;  /* bit[21]   : 下行非IDLE态清指针指示中断屏蔽寄存器0 */
        unsigned int  dl_rdq_downoverflow_mask0 : 1;  /* bit[22]   : 下行RDQ下溢中断屏蔽寄存器0 */
        unsigned int  dl_bdq_upoverflow_mask0   : 1;  /* bit[23]   : 下行BDQ上溢中断屏蔽寄存器0 */
        unsigned int  dl_rdq_full_mask0         : 1;  /* bit[24]   : 下行RDQ满中断屏蔽寄存器0 */
        unsigned int  dl_bdq_epty_mask0         : 1;  /* bit[25]   : 下行BDQ空中断屏蔽寄存器0 */
        unsigned int  dl_adq0_epty_mask0        : 1;  /* bit[26]   : 下行ADQ0空中断屏蔽寄存器0 */
        unsigned int  dl_adq1_epty_mask0        : 1;  /* bit[27]   : 下行ADQ1空中断屏蔽寄存器0。
                                                                     0 */
        unsigned int  reserved_1                : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_IPF_INT_MASK0_UNION;
#endif
#define SOC_IPF_INT_MASK0_ul_rpt_mask0_START               (0)
#define SOC_IPF_INT_MASK0_ul_rpt_mask0_END                 (0)
#define SOC_IPF_INT_MASK0_ul_timeout_mask0_START           (1)
#define SOC_IPF_INT_MASK0_ul_timeout_mask0_END             (1)
#define SOC_IPF_INT_MASK0_ul_disable_end_mask0_START       (2)
#define SOC_IPF_INT_MASK0_ul_disable_end_mask0_END         (2)
#define SOC_IPF_INT_MASK0_ul_idle_cfg_bd_mask0_START       (3)
#define SOC_IPF_INT_MASK0_ul_idle_cfg_bd_mask0_END         (3)
#define SOC_IPF_INT_MASK0_ul_trail_cfg_bd_mask0_START      (4)
#define SOC_IPF_INT_MASK0_ul_trail_cfg_bd_mask0_END        (4)
#define SOC_IPF_INT_MASK0_ul_noidle_clrptr_mask0_START     (5)
#define SOC_IPF_INT_MASK0_ul_noidle_clrptr_mask0_END       (5)
#define SOC_IPF_INT_MASK0_ul_rdq_downoverflow_mask0_START  (6)
#define SOC_IPF_INT_MASK0_ul_rdq_downoverflow_mask0_END    (6)
#define SOC_IPF_INT_MASK0_ul_bdq_upoverflow_mask0_START    (7)
#define SOC_IPF_INT_MASK0_ul_bdq_upoverflow_mask0_END      (7)
#define SOC_IPF_INT_MASK0_ul_rdq_full_mask0_START          (8)
#define SOC_IPF_INT_MASK0_ul_rdq_full_mask0_END            (8)
#define SOC_IPF_INT_MASK0_ul_bdq_epty_mask0_START          (9)
#define SOC_IPF_INT_MASK0_ul_bdq_epty_mask0_END            (9)
#define SOC_IPF_INT_MASK0_ul_adq0_epty_mask0_START         (10)
#define SOC_IPF_INT_MASK0_ul_adq0_epty_mask0_END           (10)
#define SOC_IPF_INT_MASK0_ul_adq1_epty_mask0_START         (11)
#define SOC_IPF_INT_MASK0_ul_adq1_epty_mask0_END           (11)
#define SOC_IPF_INT_MASK0_dl_rpt_mask0_START               (16)
#define SOC_IPF_INT_MASK0_dl_rpt_mask0_END                 (16)
#define SOC_IPF_INT_MASK0_dl_timeout_mask0_START           (17)
#define SOC_IPF_INT_MASK0_dl_timeout_mask0_END             (17)
#define SOC_IPF_INT_MASK0_dl_disable_end_mask0_START       (18)
#define SOC_IPF_INT_MASK0_dl_disable_end_mask0_END         (18)
#define SOC_IPF_INT_MASK0_dl_idle_cfg_bd_mask0_START       (19)
#define SOC_IPF_INT_MASK0_dl_idle_cfg_bd_mask0_END         (19)
#define SOC_IPF_INT_MASK0_dl_trail_cfg_bd_mask0_START      (20)
#define SOC_IPF_INT_MASK0_dl_trail_cfg_bd_mask0_END        (20)
#define SOC_IPF_INT_MASK0_dl_noidle_clrptr_mask0_START     (21)
#define SOC_IPF_INT_MASK0_dl_noidle_clrptr_mask0_END       (21)
#define SOC_IPF_INT_MASK0_dl_rdq_downoverflow_mask0_START  (22)
#define SOC_IPF_INT_MASK0_dl_rdq_downoverflow_mask0_END    (22)
#define SOC_IPF_INT_MASK0_dl_bdq_upoverflow_mask0_START    (23)
#define SOC_IPF_INT_MASK0_dl_bdq_upoverflow_mask0_END      (23)
#define SOC_IPF_INT_MASK0_dl_rdq_full_mask0_START          (24)
#define SOC_IPF_INT_MASK0_dl_rdq_full_mask0_END            (24)
#define SOC_IPF_INT_MASK0_dl_bdq_epty_mask0_START          (25)
#define SOC_IPF_INT_MASK0_dl_bdq_epty_mask0_END            (25)
#define SOC_IPF_INT_MASK0_dl_adq0_epty_mask0_START         (26)
#define SOC_IPF_INT_MASK0_dl_adq0_epty_mask0_END           (26)
#define SOC_IPF_INT_MASK0_dl_adq1_epty_mask0_START         (27)
#define SOC_IPF_INT_MASK0_dl_adq1_epty_mask0_END           (27)


/*****************************************************************************
 结构名    : SOC_IPF_INT_MASK1_UNION
 结构说明  : INT_MASK1 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt_mask1              : 1;  /* bit[0]    : 上行结果上报中断屏蔽寄存器1 */
        unsigned int  ul_timeout_mask1          : 1;  /* bit[1]    : 上行结果上报超时中断屏蔽寄存器1 */
        unsigned int  ul_disable_end_mask1      : 1;  /* bit[2]    : 上行通道关闭完成中断屏蔽寄存器1 */
        unsigned int  ul_idle_cfg_bd_mask1      : 1;  /* bit[3]    : 上行通道IDLE期间软件配置BD指示中断屏蔽寄存器1 */
        unsigned int  ul_trail_cfg_bd_mask1     : 1;  /* bit[4]    : 上行通道关闭但BD没有处理完期间软件继续配置BD指示中断屏蔽寄存器1 */
        unsigned int  ul_noidle_clrptr_mask1    : 1;  /* bit[5]    : 上行非IDLE态清指针指示中断屏蔽寄存器1 */
        unsigned int  ul_rdq_downoverflow_mask1 : 1;  /* bit[6]    : 上行RDQ下溢中断屏蔽寄存器1 */
        unsigned int  ul_bdq_upoverflow_mask1   : 1;  /* bit[7]    : 上行BDQ上溢中断屏蔽寄存器1 */
        unsigned int  ul_rdq_full_mask1         : 1;  /* bit[8]    : 上行RDQ满中断屏蔽寄存器1 */
        unsigned int  ul_bdq_epty_mask1         : 1;  /* bit[9]    : 上行BDQ空中断屏蔽寄存器1 */
        unsigned int  ul_adq0_epty_mask1        : 1;  /* bit[10]   : 上行ADQ0空中断屏蔽寄存器1 */
        unsigned int  ul_adq1_epty_mask1        : 1;  /* bit[11]   : 上行ADQ1空中断屏蔽寄存器1 */
        unsigned int  reserved_0                : 4;  /* bit[12-15]: 保留 */
        unsigned int  dl_rpt_mask1              : 1;  /* bit[16]   : 下行结果上报中断屏蔽寄存器1 */
        unsigned int  dl_timeout_mask1          : 1;  /* bit[17]   : 下行结果上报超时中断屏蔽寄存器1 */
        unsigned int  dl_disable_end_mask1      : 1;  /* bit[18]   : 下行通道关闭完成中断屏蔽寄存器1 */
        unsigned int  dl_idle_cfg_bd_mask1      : 1;  /* bit[19]   : 下行通道IDLE期间软件配置BD指示中断屏蔽寄存器1 */
        unsigned int  dl_trail_cfg_bd_mask1     : 1;  /* bit[20]   : 下行通道关闭但BD没有处理完期间软件继续配置BD指示中断屏蔽寄存器1 */
        unsigned int  dl_noidle_clrptr_mask1    : 1;  /* bit[21]   : 下行非IDLE态清指针指示中断屏蔽寄存器1 */
        unsigned int  dl_rdq_downoverflow_mask1 : 1;  /* bit[22]   : 下行RDQ下溢中断屏蔽寄存器1 */
        unsigned int  dl_bdq_upoverflow_mask1   : 1;  /* bit[23]   : 下行BDQ上溢中断屏蔽寄存器1 */
        unsigned int  dl_rdq_full_mask1         : 1;  /* bit[24]   : 下行RDQ满中断屏蔽寄存器1 */
        unsigned int  dl_bdq_epty_mask1         : 1;  /* bit[25]   : 下行BDQ空中断屏蔽寄存器1 */
        unsigned int  dl_adq0_epty_mask1        : 1;  /* bit[26]   : 下行ADQ0空中断屏蔽寄存器1 */
        unsigned int  dl_adq1_epty_mask1        : 1;  /* bit[27]   : 下行ADQ1空中断屏蔽寄存器1 */
        unsigned int  reserved_1                : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_IPF_INT_MASK1_UNION;
#endif
#define SOC_IPF_INT_MASK1_ul_rpt_mask1_START               (0)
#define SOC_IPF_INT_MASK1_ul_rpt_mask1_END                 (0)
#define SOC_IPF_INT_MASK1_ul_timeout_mask1_START           (1)
#define SOC_IPF_INT_MASK1_ul_timeout_mask1_END             (1)
#define SOC_IPF_INT_MASK1_ul_disable_end_mask1_START       (2)
#define SOC_IPF_INT_MASK1_ul_disable_end_mask1_END         (2)
#define SOC_IPF_INT_MASK1_ul_idle_cfg_bd_mask1_START       (3)
#define SOC_IPF_INT_MASK1_ul_idle_cfg_bd_mask1_END         (3)
#define SOC_IPF_INT_MASK1_ul_trail_cfg_bd_mask1_START      (4)
#define SOC_IPF_INT_MASK1_ul_trail_cfg_bd_mask1_END        (4)
#define SOC_IPF_INT_MASK1_ul_noidle_clrptr_mask1_START     (5)
#define SOC_IPF_INT_MASK1_ul_noidle_clrptr_mask1_END       (5)
#define SOC_IPF_INT_MASK1_ul_rdq_downoverflow_mask1_START  (6)
#define SOC_IPF_INT_MASK1_ul_rdq_downoverflow_mask1_END    (6)
#define SOC_IPF_INT_MASK1_ul_bdq_upoverflow_mask1_START    (7)
#define SOC_IPF_INT_MASK1_ul_bdq_upoverflow_mask1_END      (7)
#define SOC_IPF_INT_MASK1_ul_rdq_full_mask1_START          (8)
#define SOC_IPF_INT_MASK1_ul_rdq_full_mask1_END            (8)
#define SOC_IPF_INT_MASK1_ul_bdq_epty_mask1_START          (9)
#define SOC_IPF_INT_MASK1_ul_bdq_epty_mask1_END            (9)
#define SOC_IPF_INT_MASK1_ul_adq0_epty_mask1_START         (10)
#define SOC_IPF_INT_MASK1_ul_adq0_epty_mask1_END           (10)
#define SOC_IPF_INT_MASK1_ul_adq1_epty_mask1_START         (11)
#define SOC_IPF_INT_MASK1_ul_adq1_epty_mask1_END           (11)
#define SOC_IPF_INT_MASK1_dl_rpt_mask1_START               (16)
#define SOC_IPF_INT_MASK1_dl_rpt_mask1_END                 (16)
#define SOC_IPF_INT_MASK1_dl_timeout_mask1_START           (17)
#define SOC_IPF_INT_MASK1_dl_timeout_mask1_END             (17)
#define SOC_IPF_INT_MASK1_dl_disable_end_mask1_START       (18)
#define SOC_IPF_INT_MASK1_dl_disable_end_mask1_END         (18)
#define SOC_IPF_INT_MASK1_dl_idle_cfg_bd_mask1_START       (19)
#define SOC_IPF_INT_MASK1_dl_idle_cfg_bd_mask1_END         (19)
#define SOC_IPF_INT_MASK1_dl_trail_cfg_bd_mask1_START      (20)
#define SOC_IPF_INT_MASK1_dl_trail_cfg_bd_mask1_END        (20)
#define SOC_IPF_INT_MASK1_dl_noidle_clrptr_mask1_START     (21)
#define SOC_IPF_INT_MASK1_dl_noidle_clrptr_mask1_END       (21)
#define SOC_IPF_INT_MASK1_dl_rdq_downoverflow_mask1_START  (22)
#define SOC_IPF_INT_MASK1_dl_rdq_downoverflow_mask1_END    (22)
#define SOC_IPF_INT_MASK1_dl_bdq_upoverflow_mask1_START    (23)
#define SOC_IPF_INT_MASK1_dl_bdq_upoverflow_mask1_END      (23)
#define SOC_IPF_INT_MASK1_dl_rdq_full_mask1_START          (24)
#define SOC_IPF_INT_MASK1_dl_rdq_full_mask1_END            (24)
#define SOC_IPF_INT_MASK1_dl_bdq_epty_mask1_START          (25)
#define SOC_IPF_INT_MASK1_dl_bdq_epty_mask1_END            (25)
#define SOC_IPF_INT_MASK1_dl_adq0_epty_mask1_START         (26)
#define SOC_IPF_INT_MASK1_dl_adq0_epty_mask1_END           (26)
#define SOC_IPF_INT_MASK1_dl_adq1_epty_mask1_START         (27)
#define SOC_IPF_INT_MASK1_dl_adq1_epty_mask1_END           (27)


/*****************************************************************************
 结构名    : SOC_IPF_INT_STATE_UNION
 结构说明  : INT_STATE 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt              : 1;  /* bit[0]    : 上行结果上报指示 */
        unsigned int  ul_timeout          : 1;  /* bit[1]    : 上行结果上报超时指示 */
        unsigned int  ul_disable_end      : 1;  /* bit[2]    : 上行通道关闭完成指示 */
        unsigned int  ul_idle_cfg_bd      : 1;  /* bit[3]    : 上行通道IDLE期间软件配置BD指示 */
        unsigned int  ul_trail_cfg_bd     : 1;  /* bit[4]    : 上行通道关闭但BD没有处理完期间软件继续配置BD指示 */
        unsigned int  ul_noidle_clrptr    : 1;  /* bit[5]    : 上行非IDLE态清指针指示 */
        unsigned int  ul_rdq_downoverflow : 1;  /* bit[6]    : 上行RDQ下溢指示 */
        unsigned int  ul_bdq_upoverflow   : 1;  /* bit[7]    : 上行BDQ上溢指示 */
        unsigned int  ul_rdq_full         : 1;  /* bit[8]    : 上行RDQ满指示 */
        unsigned int  ul_bdq_epty         : 1;  /* bit[9]    : 上行通道BDQ空指示 */
        unsigned int  ul_adq0_epty        : 1;  /* bit[10]   : 上行通道ADQ0空指示 */
        unsigned int  ul_adq1_epty        : 1;  /* bit[11]   : 上行通道ADQ1空指示 */
        unsigned int  reserved_0          : 4;  /* bit[12-15]: 保留 */
        unsigned int  dl_rpt              : 1;  /* bit[16]   : 下行结果上报指示 */
        unsigned int  dl_timeout          : 1;  /* bit[17]   : 下行结果上报超时指示 */
        unsigned int  dl_disable_end      : 1;  /* bit[18]   : 下行通道关闭完成指示 */
        unsigned int  dl_idle_cfg_bd      : 1;  /* bit[19]   : 下行通道IDLE期间软件配置BD指示 */
        unsigned int  dl_trail_cfg_bd     : 1;  /* bit[20]   : 下行通道关闭但BD没有处理完期间软件继续配置BD指示 */
        unsigned int  dl_noidle_clrptr    : 1;  /* bit[21]   : 下行非IDLE态清指针指示 */
        unsigned int  dl_rdq_downoverflow : 1;  /* bit[22]   : 下行RDQ下溢指示 */
        unsigned int  dl_bdq_upoverflow   : 1;  /* bit[23]   : 下行BDQ上溢指示 */
        unsigned int  dl_rdq_full         : 1;  /* bit[24]   : 下行RDQ满指示 */
        unsigned int  dl_bdq_epty         : 1;  /* bit[25]   : 下行通道BDQ空指示 */
        unsigned int  dl_adq0_epty        : 1;  /* bit[26]   : 下行通道ADQ0空指示 */
        unsigned int  dl_adq1_epty        : 1;  /* bit[27]   : 下行通道ADQ1空指示 */
        unsigned int  reserved_1          : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_IPF_INT_STATE_UNION;
#endif
#define SOC_IPF_INT_STATE_ul_rpt_START               (0)
#define SOC_IPF_INT_STATE_ul_rpt_END                 (0)
#define SOC_IPF_INT_STATE_ul_timeout_START           (1)
#define SOC_IPF_INT_STATE_ul_timeout_END             (1)
#define SOC_IPF_INT_STATE_ul_disable_end_START       (2)
#define SOC_IPF_INT_STATE_ul_disable_end_END         (2)
#define SOC_IPF_INT_STATE_ul_idle_cfg_bd_START       (3)
#define SOC_IPF_INT_STATE_ul_idle_cfg_bd_END         (3)
#define SOC_IPF_INT_STATE_ul_trail_cfg_bd_START      (4)
#define SOC_IPF_INT_STATE_ul_trail_cfg_bd_END        (4)
#define SOC_IPF_INT_STATE_ul_noidle_clrptr_START     (5)
#define SOC_IPF_INT_STATE_ul_noidle_clrptr_END       (5)
#define SOC_IPF_INT_STATE_ul_rdq_downoverflow_START  (6)
#define SOC_IPF_INT_STATE_ul_rdq_downoverflow_END    (6)
#define SOC_IPF_INT_STATE_ul_bdq_upoverflow_START    (7)
#define SOC_IPF_INT_STATE_ul_bdq_upoverflow_END      (7)
#define SOC_IPF_INT_STATE_ul_rdq_full_START          (8)
#define SOC_IPF_INT_STATE_ul_rdq_full_END            (8)
#define SOC_IPF_INT_STATE_ul_bdq_epty_START          (9)
#define SOC_IPF_INT_STATE_ul_bdq_epty_END            (9)
#define SOC_IPF_INT_STATE_ul_adq0_epty_START         (10)
#define SOC_IPF_INT_STATE_ul_adq0_epty_END           (10)
#define SOC_IPF_INT_STATE_ul_adq1_epty_START         (11)
#define SOC_IPF_INT_STATE_ul_adq1_epty_END           (11)
#define SOC_IPF_INT_STATE_dl_rpt_START               (16)
#define SOC_IPF_INT_STATE_dl_rpt_END                 (16)
#define SOC_IPF_INT_STATE_dl_timeout_START           (17)
#define SOC_IPF_INT_STATE_dl_timeout_END             (17)
#define SOC_IPF_INT_STATE_dl_disable_end_START       (18)
#define SOC_IPF_INT_STATE_dl_disable_end_END         (18)
#define SOC_IPF_INT_STATE_dl_idle_cfg_bd_START       (19)
#define SOC_IPF_INT_STATE_dl_idle_cfg_bd_END         (19)
#define SOC_IPF_INT_STATE_dl_trail_cfg_bd_START      (20)
#define SOC_IPF_INT_STATE_dl_trail_cfg_bd_END        (20)
#define SOC_IPF_INT_STATE_dl_noidle_clrptr_START     (21)
#define SOC_IPF_INT_STATE_dl_noidle_clrptr_END       (21)
#define SOC_IPF_INT_STATE_dl_rdq_downoverflow_START  (22)
#define SOC_IPF_INT_STATE_dl_rdq_downoverflow_END    (22)
#define SOC_IPF_INT_STATE_dl_bdq_upoverflow_START    (23)
#define SOC_IPF_INT_STATE_dl_bdq_upoverflow_END      (23)
#define SOC_IPF_INT_STATE_dl_rdq_full_START          (24)
#define SOC_IPF_INT_STATE_dl_rdq_full_END            (24)
#define SOC_IPF_INT_STATE_dl_bdq_epty_START          (25)
#define SOC_IPF_INT_STATE_dl_bdq_epty_END            (25)
#define SOC_IPF_INT_STATE_dl_adq0_epty_START         (26)
#define SOC_IPF_INT_STATE_dl_adq0_epty_END           (26)
#define SOC_IPF_INT_STATE_dl_adq1_epty_START         (27)
#define SOC_IPF_INT_STATE_dl_adq1_epty_END           (27)


/*****************************************************************************
 结构名    : SOC_IPF_TIME_OUT_UNION
 结构说明  : TIME_OUT 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 超时配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  time_out_cfg   : 16; /* bit[0-15] : 超时配置，如果两个RD间隔超时则上报中断，步长为256个时钟周期。对两个通道同时生效。 */
        unsigned int  time_out_valid : 1;  /* bit[16]   : 超时中断使能 */
        unsigned int  reserved       : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_IPF_TIME_OUT_UNION;
#endif
#define SOC_IPF_TIME_OUT_time_out_cfg_START    (0)
#define SOC_IPF_TIME_OUT_time_out_cfg_END      (15)
#define SOC_IPF_TIME_OUT_time_out_valid_START  (16)
#define SOC_IPF_TIME_OUT_time_out_valid_END    (16)


/*****************************************************************************
 结构名    : SOC_IPF_PKT_LEN_UNION
 结构说明  : PKT_LEN 寄存器结构定义。地址偏移量:0x0048，初值:0x05DC0028，宽度:32
 寄存器说明: 包长配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  min_pkt_len : 14; /* bit[0-13] : 最小包长配置寄存器，默认值为40字节（0x28） */
        unsigned int  reserved_0  : 2;  /* bit[14-15]: 保留。 */
        unsigned int  max_pkt_len : 14; /* bit[16-29]: 最大包长配置寄存器，默认值为1500字节（0x5DC） */
        unsigned int  reserved_1  : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_IPF_PKT_LEN_UNION;
#endif
#define SOC_IPF_PKT_LEN_min_pkt_len_START  (0)
#define SOC_IPF_PKT_LEN_min_pkt_len_END    (13)
#define SOC_IPF_PKT_LEN_max_pkt_len_START  (16)
#define SOC_IPF_PKT_LEN_max_pkt_len_END    (29)


/*****************************************************************************
 结构名    : SOC_IPF_FILTER_ZERO_INDEX_UNION
 结构说明  : FILTER_ZERO_INDEX 寄存器结构定义。地址偏移量:0x0070，初值:0x01FF01FF，宽度:32
 寄存器说明: IPF过滤器起始索引配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_filter_zero_index : 9;  /* bit[0-8]  : ul基本过滤器起始索引，ul基本过滤器起始地址配置范围为0～63，扩展过滤器地址范围从64~510，如果配置为511表示上行通道无过滤器，默认值为511（0x1FF）。
                                                                当mfc_en控制位有效时，这个域无效； */
        unsigned int  reserved_0           : 7;  /* bit[9-15] : 保留。 */
        unsigned int  dl_filter_zero_index : 9;  /* bit[16-24]: dl基本过滤器起始索引，dl基本过滤器起始地址配置范围为0～63,扩展过滤器地址范围从64~510，如果配置为511表示下行通道无过滤器，默认值为511（0x1FF）。
                                                                当mfc_en控制位有效时，这个域无效； */
        unsigned int  reserved_1           : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_IPF_FILTER_ZERO_INDEX_UNION;
#endif
#define SOC_IPF_FILTER_ZERO_INDEX_ul_filter_zero_index_START  (0)
#define SOC_IPF_FILTER_ZERO_INDEX_ul_filter_zero_index_END    (8)
#define SOC_IPF_FILTER_ZERO_INDEX_dl_filter_zero_index_START  (16)
#define SOC_IPF_FILTER_ZERO_INDEX_dl_filter_zero_index_END    (24)


/*****************************************************************************
 结构名    : SOC_IPF_EF_BADDR_UNION
 结构说明  : EF_BADDR 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 扩展过滤器基地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ef_baddr : 32; /* bit[0-31]: 扩展扩滤器起始地址，8字节对齐 */
    } reg;
} SOC_IPF_EF_BADDR_UNION;
#endif
#define SOC_IPF_EF_BADDR_ef_baddr_START  (0)
#define SOC_IPF_EF_BADDR_ef_baddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_BFLT_INDEX_UNION
 结构说明  : BFLT_INDEX 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 基本过滤表配置索引
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bf_index : 8;  /* bit[0-7] : 基本过滤表读写地址（范围为0～63） */
        unsigned int  reserved : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_BFLT_INDEX_UNION;
#endif
#define SOC_IPF_BFLT_INDEX_bf_index_START  (0)
#define SOC_IPF_BFLT_INDEX_bf_index_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_CHAIN_LOOP_UNION
 结构说明  : FLT_CHAIN_LOOP 寄存器结构定义。地址偏移量:0x007C，初值:0x0000，宽度:32
 寄存器说明: 过滤器链表环告警
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_chain_loop : 1;  /* bit[0]   : 表示过滤器链表形成环异常告警 */
        unsigned int                 : 31; /* bit[1-31]:  */
    } reg;
} SOC_IPF_FLT_CHAIN_LOOP_UNION;
#endif
#define SOC_IPF_FLT_CHAIN_LOOP_flt_chain_loop_START  (0)
#define SOC_IPF_FLT_CHAIN_LOOP_flt_chain_loop_END    (0)
#define SOC_IPF_FLT_CHAIN_LOOP__START                (1)
#define SOC_IPF_FLT_CHAIN_LOOP__END                  (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_LOCAL_ADDR0_UNION
 结构说明  : FLT_LOCAL_ADDR0 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 过滤器local address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_laddr0 : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示LOCAL ADDRESS {[103:96],[111:104],[119:112],[127:120]}，IPV4表示LOCAL ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                     flt_addr_reverse等于1时按照字节小端排列，IPV6表示LOCAL ADDRESS [127:96]，
                                                     IPV4表示LOCAL ADDRESS [31:0] */
    } reg;
} SOC_IPF_FLT_LOCAL_ADDR0_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_ADDR0_flt_laddr0_START  (0)
#define SOC_IPF_FLT_LOCAL_ADDR0_flt_laddr0_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_LOCAL_ADDR1_UNION
 结构说明  : FLT_LOCAL_ADDR1 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 过滤器local address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_laddr1 : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示LOCAL ADDRESS {[71:64],[79:72],[87:80],[95:88]}
                                                     flt_addr_reverse等于1时按照字节小端排列，IPV6表示LOCAL ADDRESS[95:64]
                                                     IPV4保留 */
    } reg;
} SOC_IPF_FLT_LOCAL_ADDR1_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_ADDR1_flt_laddr1_START  (0)
#define SOC_IPF_FLT_LOCAL_ADDR1_flt_laddr1_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_LOCAL_ADDR2_UNION
 结构说明  : FLT_LOCAL_ADDR2 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 过滤器local address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_laddr2 : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示LOCAL ADDRESS {[39:32],[47:40],[55:48],[63:56]}
                                                     flt_addr_reverse等于1时按照字节小端排列，IPV6表示LOCAL ADDRESS[63:32]
                                                     IPV4保留 */
    } reg;
} SOC_IPF_FLT_LOCAL_ADDR2_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_ADDR2_flt_laddr2_START  (0)
#define SOC_IPF_FLT_LOCAL_ADDR2_flt_laddr2_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_LOCAL_ADDR3_UNION
 结构说明  : FLT_LOCAL_ADDR3 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: 过滤器local address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_laddr3 : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示LOCAL ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                     flt_addr_reverse等于1时按照字节小端排列，IPV6表示LOCAL ADDRESS[31:0]
                                                     IPV4保留 */
    } reg;
} SOC_IPF_FLT_LOCAL_ADDR3_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_ADDR3_flt_laddr3_START  (0)
#define SOC_IPF_FLT_LOCAL_ADDR3_flt_laddr3_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_ADDR0_UNION
 结构说明  : FLT_REMOTE_ADDR0 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: 过滤器remote address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr0 : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示REMOTE ADDRESS {[103:96],[111:104],[119:112],[127:120]}，
                                                     IPV4表示REMOTE ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                     flt_addr_reverse等于1时按照字节小端排列，IPV6表示REMOTE ADDRESS[127:96]，
                                                     IPV4表示REMOTE ADDRESS[31:0] */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR0_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR0_flt_raddr0_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR0_flt_raddr0_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_ADDR1_UNION
 结构说明  : FLT_REMOTE_ADDR1 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000000，宽度:32
 寄存器说明: 过滤器remote address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr1 : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示REMOTE ADDRESS {[71:64],[79:72],[87:80],[95:88]}
                                                     flt_addr_reverse等于1时按照字节小端排列，IPV6表示REMOTE ADDRESS[95:64]
                                                     IPV4保留 */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR1_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR1_flt_raddr1_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR1_flt_raddr1_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_ADDR2_UNION
 结构说明  : FLT_REMOTE_ADDR2 寄存器结构定义。地址偏移量:0x00A8，初值:0x00000000，宽度:32
 寄存器说明: 过滤器remote address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr2 : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示REMOTE ADDRESS {[39:32],[47:40],[55:48],[63:56]}
                                                     flt_addr_reverse等于1时按照字节小端排列，IPV6表示REMOTE ADDRESS[63:32]
                                                     IPV4保留 */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR2_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR2_flt_raddr2_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR2_flt_raddr2_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_ADDR3_UNION
 结构说明  : FLT_REMOTE_ADDR3 寄存器结构定义。地址偏移量:0x00AC，初值:0x00000000，宽度:32
 寄存器说明: 过滤器remote address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr3 : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示REMOTE ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                     flt_addr_reverse等于1时按照字节小端排列，IPV6表示REMOTE ADDRESS[31:0]
                                                     IPV4保留 */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR3_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR3_flt_raddr3_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR3_flt_raddr3_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_ADDR0_MASK_UNION
 结构说明  : FLT_REMOTE_ADDR0_MASK 寄存器结构定义。地址偏移量:0x00B0，初值:0x00000000，宽度:32
 寄存器说明: 过滤器remote address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr0_mask : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示REMOTE ADDRESS_MASK {[103:96],[111:104],[119:112],[127:120]}
                                                          IPV4表示REMOTE ADDRESS_MASK {[7:0],[15:8],[23:16],[31:24]}
                                                          flt_addr_reverse等于1时按照字节小端排列，IPV6表示REMOTE ADDRESS_MASK[127:96]
                                                          IPV4表示REMOTE ADDRESS_MASK[31:0] */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR0_MASK_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR0_MASK_flt_raddr0_mask_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR0_MASK_flt_raddr0_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_ADDR1_MASK_UNION
 结构说明  : FLT_REMOTE_ADDR1_MASK 寄存器结构定义。地址偏移量:0x00B4，初值:0x00000000，宽度:32
 寄存器说明: 过滤器remote address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr1_mask : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示REMOTE ADDRESS_MASK {[71:64],[79:72],[87:80],[95:88]}
                                                          flt_addr_reverse等于1时按照字节小端排列，IPV6表示REMOTE ADDRESS_MASK[95:64]
                                                          IPV4保留 */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR1_MASK_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR1_MASK_flt_raddr1_mask_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR1_MASK_flt_raddr1_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_ADDR2_MASK_UNION
 结构说明  : FLT_REMOTE_ADDR2_MASK 寄存器结构定义。地址偏移量:0x00B8，初值:0x00000000，宽度:32
 寄存器说明: 过滤器remote address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr2_mask : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示REMOTE ADDRESS_MASK {[39:32],[47:40],[55:48],[63:56]}
                                                          flt_addr_reverse等于1时按照字节小端排列，IPV6表示REMOTE ADDRESS_MASK[63:32]
                                                          IPV4保留 */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR2_MASK_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR2_MASK_flt_raddr2_mask_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR2_MASK_flt_raddr2_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_ADDR3_MASK_UNION
 结构说明  : FLT_REMOTE_ADDR3_MASK 寄存器结构定义。地址偏移量:0x00BC，初值:0x00000000，宽度:32
 寄存器说明: 过滤器remote address配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr3_mask : 32; /* bit[0-31]: flt_addr_reverse等于0时按照字节大端排列，IPV6表示REMOTE ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                          flt_addr_reverse等于1时按照字节小端排列，IPV6表示REMOTE ADDRESS[31:0]
                                                          IPV4保留 */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR3_MASK_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR3_MASK_flt_raddr3_mask_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR3_MASK_flt_raddr3_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_LOCAL_PORT_UNION
 结构说明  : FLT_LOCAL_PORT 寄存器结构定义。地址偏移量:0x00C0，初值:0x00000000，宽度:32
 寄存器说明: 过滤表LOCAL PORT门限配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_local_port_low  : 16; /* bit[0-15] : 过滤表LOCAL PORT低门限，字节小端排列 */
        unsigned int  flt_local_port_high : 16; /* bit[16-31]: 过滤表LOCAL PORT高门限，字节小端排列 */
    } reg;
} SOC_IPF_FLT_LOCAL_PORT_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_PORT_flt_local_port_low_START   (0)
#define SOC_IPF_FLT_LOCAL_PORT_flt_local_port_low_END     (15)
#define SOC_IPF_FLT_LOCAL_PORT_flt_local_port_high_START  (16)
#define SOC_IPF_FLT_LOCAL_PORT_flt_local_port_high_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_REMOTE_PORT_UNION
 结构说明  : FLT_REMOTE_PORT 寄存器结构定义。地址偏移量:0x00C4，初值:0x00000000，宽度:32
 寄存器说明: 过滤表REMOTE PORT门限配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_remote_port_low  : 16; /* bit[0-15] : 过滤表REMOTE PORT低门限，字节小端排列 */
        unsigned int  flt_remote_port_high : 16; /* bit[16-31]: 过滤表REMOTE PORT高门限，字节小端排列 */
    } reg;
} SOC_IPF_FLT_REMOTE_PORT_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_PORT_flt_remote_port_low_START   (0)
#define SOC_IPF_FLT_REMOTE_PORT_flt_remote_port_low_END     (15)
#define SOC_IPF_FLT_REMOTE_PORT_flt_remote_port_high_START  (16)
#define SOC_IPF_FLT_REMOTE_PORT_flt_remote_port_high_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_TRAFFIC_CLASS_UNION
 结构说明  : FLT_TRAFFIC_CLASS 寄存器结构定义。地址偏移量:0x00C8，初值:0x00000000，宽度:32
 寄存器说明: 过滤表业务等级域配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_traffic_class      : 8;  /* bit[0-7]  : 过滤器业务等级域配置值
                                                                  IPV4为type of service域
                                                                  IPV6为traffic class域 */
        unsigned int  flt_traffic_class_mask : 8;  /* bit[8-15] : 过滤器业务等级域掩码配置值 */
        unsigned int  reserved               : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_IPF_FLT_TRAFFIC_CLASS_UNION;
#endif
#define SOC_IPF_FLT_TRAFFIC_CLASS_flt_traffic_class_START       (0)
#define SOC_IPF_FLT_TRAFFIC_CLASS_flt_traffic_class_END         (7)
#define SOC_IPF_FLT_TRAFFIC_CLASS_flt_traffic_class_mask_START  (8)
#define SOC_IPF_FLT_TRAFFIC_CLASS_flt_traffic_class_mask_END    (15)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_LADD_MASK_UNION
 结构说明  : FLT_LADD_MASK 寄存器结构定义。地址偏移量:0x00CC，初值:0x00000000，宽度:32
 寄存器说明: 过滤器local address mask域配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_local_addr_mask : 7;  /* bit[0-6] : 过滤器local address域掩码配置值，IPV4过滤器表示32位地址掩码从低位到高位0的个数。
                                                              例如
                                                              flt_local_addr_mask=7'b0表示掩码等于0xffffffff；
                                                              flt_local_addr_mask=7'h4表示掩码等于0xfffffff0；
                                                              flt_local_addr_mask=7'h8表示掩码等于0xffffff00；
                                                              IPV6过滤器表示128位地址掩码从低位到高位0的个数。 */
        unsigned int  reserved            : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_IPF_FLT_LADD_MASK_UNION;
#endif
#define SOC_IPF_FLT_LADD_MASK_flt_local_addr_mask_START  (0)
#define SOC_IPF_FLT_LADD_MASK_flt_local_addr_mask_END    (6)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_NEXT_HEADER_UNION
 结构说明  : FLT_NEXT_HEADER 寄存器结构定义。地址偏移量:0x00D0，初值:0x00000000，宽度:32
 寄存器说明: 过滤器协议类型域配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_next_header : 8;  /* bit[0-7] : 过滤器协议类型域配置值
                                                          IPV4为protocol域
                                                          IPV6为next header域 */
        unsigned int  reserved        : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_FLT_NEXT_HEADER_UNION;
#endif
#define SOC_IPF_FLT_NEXT_HEADER_flt_next_header_START  (0)
#define SOC_IPF_FLT_NEXT_HEADER_flt_next_header_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_FLOW_LABEL_UNION
 结构说明  : FLT_FLOW_LABEL 寄存器结构定义。地址偏移量:0x00D4，初值:0x00000000，宽度:32
 寄存器说明: 过滤器流标签域配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_fow_lable : 20; /* bit[0-19] : 过滤表流标签配置寄存器，字节小端排列 */
        unsigned int  reserved      : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_IPF_FLT_FLOW_LABEL_UNION;
#endif
#define SOC_IPF_FLT_FLOW_LABEL_flt_fow_lable_START  (0)
#define SOC_IPF_FLT_FLOW_LABEL_flt_fow_lable_END    (19)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_ICMP_UNION
 结构说明  : FLT_ICMP 寄存器结构定义。地址偏移量:0x00D8，初值:0x00000000，宽度:32
 寄存器说明: 过滤器ICMP配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_type : 8;  /* bit[0-7]  : 过滤器type域配置值 */
        unsigned int  reserved_0: 8;  /* bit[8-15] : 保留。 */
        unsigned int  flt_code : 8;  /* bit[16-23]: 过滤器code域配置值 */
        unsigned int  reserved_1: 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_IPF_FLT_ICMP_UNION;
#endif
#define SOC_IPF_FLT_ICMP_flt_type_START  (0)
#define SOC_IPF_FLT_ICMP_flt_type_END    (7)
#define SOC_IPF_FLT_ICMP_flt_code_START  (16)
#define SOC_IPF_FLT_ICMP_flt_code_END    (23)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_CHAIN_UNION
 结构说明  : FLT_CHAIN 寄存器结构定义。地址偏移量:0x00DC，初值:0x00000000，宽度:32
 寄存器说明: 过滤器链表域配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_next_index : 9;  /* bit[0-8]  : 下一个过滤器对应的index */
        unsigned int  reserved_0     : 7;  /* bit[9-15] : 保留。 */
        unsigned int  flt_pri        : 9;  /* bit[16-24]: 过滤器优先级，flt_pri数值越小优先级越高 */
        unsigned int  reserved_1     : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_IPF_FLT_CHAIN_UNION;
#endif
#define SOC_IPF_FLT_CHAIN_flt_next_index_START  (0)
#define SOC_IPF_FLT_CHAIN_flt_next_index_END    (8)
#define SOC_IPF_FLT_CHAIN_flt_pri_START         (16)
#define SOC_IPF_FLT_CHAIN_flt_pri_END           (24)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_SPI_UNION
 结构说明  : FLT_SPI 寄存器结构定义。地址偏移量:0x00E0，初值:0x00000000，宽度:32
 寄存器说明: 过滤器SPI配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_spi : 32; /* bit[0-31]: 过滤器SPI域配置值，字节小端排列 */
    } reg;
} SOC_IPF_FLT_SPI_UNION;
#endif
#define SOC_IPF_FLT_SPI_flt_spi_START  (0)
#define SOC_IPF_FLT_SPI_flt_spi_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_FLT_RULE_CTRL_UNION
 结构说明  : FLT_RULE_CTRL 寄存器结构定义。地址偏移量:0x00E4，初值:0x00000000，宽度:32
 寄存器说明: 过滤器规则控制配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_en       : 1;  /* bit[0]    : 过滤器使能 */
        unsigned int  flt_type     : 1;  /* bit[1]    : 过滤器类型
                                                        0：IPV4
                                                        1：IPV6 */
        unsigned int  reserved_0   : 2;  /* bit[2-3]  : 保留。 */
        unsigned int  flt_spi_en   : 1;  /* bit[4]    : 过滤器SPI域使能 */
        unsigned int  flt_code_en  : 1;  /* bit[5]    : 过滤器ICMP CODE域使能 */
        unsigned int  flt_type_en  : 1;  /* bit[6]    : 过滤器ICMP TYPE域使能 */
        unsigned int  flt_fl_en    : 1;  /* bit[7]    : 过滤器IPV6 FLOW LABLE域使能。IPV4过滤器此位保留 */
        unsigned int  flt_nh_en    : 1;  /* bit[8]    : 过滤器NEXT HEADER域使能
                                                        IPV4为protocol域使能
                                                        IPV6为next header域使能 */
        unsigned int  flt_tos_en   : 1;  /* bit[9]    : 过滤器TRAFFIC CLASS域使能
                                                        IPV4为type of service域使能
                                                        IPV6为traffic class域使能 */
        unsigned int  flt_rport_en : 1;  /* bit[10]   : 过滤器remote port域使能 */
        unsigned int  flt_lport_en : 1;  /* bit[11]   : 过滤器local port域使能 */
        unsigned int  flt_raddr_en : 1;  /* bit[12]   : 过滤器remote address域使能 */
        unsigned int  flt_laddr_en : 1;  /* bit[13]   : 过滤器local address域使能 */
        unsigned int  reserved_1   : 2;  /* bit[14-15]: 保留。 */
        unsigned int  flt_bear_id  : 6;  /* bit[16-21]: 过滤器对应的承载号 */
        unsigned int  reserved_2   : 10; /* bit[22-31]: 保留。 */
    } reg;
} SOC_IPF_FLT_RULE_CTRL_UNION;
#endif
#define SOC_IPF_FLT_RULE_CTRL_flt_en_START        (0)
#define SOC_IPF_FLT_RULE_CTRL_flt_en_END          (0)
#define SOC_IPF_FLT_RULE_CTRL_flt_type_START      (1)
#define SOC_IPF_FLT_RULE_CTRL_flt_type_END        (1)
#define SOC_IPF_FLT_RULE_CTRL_flt_spi_en_START    (4)
#define SOC_IPF_FLT_RULE_CTRL_flt_spi_en_END      (4)
#define SOC_IPF_FLT_RULE_CTRL_flt_code_en_START   (5)
#define SOC_IPF_FLT_RULE_CTRL_flt_code_en_END     (5)
#define SOC_IPF_FLT_RULE_CTRL_flt_type_en_START   (6)
#define SOC_IPF_FLT_RULE_CTRL_flt_type_en_END     (6)
#define SOC_IPF_FLT_RULE_CTRL_flt_fl_en_START     (7)
#define SOC_IPF_FLT_RULE_CTRL_flt_fl_en_END       (7)
#define SOC_IPF_FLT_RULE_CTRL_flt_nh_en_START     (8)
#define SOC_IPF_FLT_RULE_CTRL_flt_nh_en_END       (8)
#define SOC_IPF_FLT_RULE_CTRL_flt_tos_en_START    (9)
#define SOC_IPF_FLT_RULE_CTRL_flt_tos_en_END      (9)
#define SOC_IPF_FLT_RULE_CTRL_flt_rport_en_START  (10)
#define SOC_IPF_FLT_RULE_CTRL_flt_rport_en_END    (10)
#define SOC_IPF_FLT_RULE_CTRL_flt_lport_en_START  (11)
#define SOC_IPF_FLT_RULE_CTRL_flt_lport_en_END    (11)
#define SOC_IPF_FLT_RULE_CTRL_flt_raddr_en_START  (12)
#define SOC_IPF_FLT_RULE_CTRL_flt_raddr_en_END    (12)
#define SOC_IPF_FLT_RULE_CTRL_flt_laddr_en_START  (13)
#define SOC_IPF_FLT_RULE_CTRL_flt_laddr_en_END    (13)
#define SOC_IPF_FLT_RULE_CTRL_flt_bear_id_START   (16)
#define SOC_IPF_FLT_RULE_CTRL_flt_bear_id_END     (21)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_CTRL_UNION
 结构说明  : CH0_CTRL 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 上行通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_mod        : 2;  /* bit[0-1]  : 模式控制寄存器
                                                         00：搬数过滤
                                                         01：只过滤
                                                         10 or 11：只搬数
                                                         当mm_en控制位有效时，这个域无效； */
        unsigned int  ul_endian     : 1;  /* bit[2]    : 输入数据大小端指示
                                                         0：big endian
                                                         1：little endian */
        unsigned int  ul_data_chain : 1;  /* bit[3]    : 数据是否为链表 */
        unsigned int  ul_bdq_clr    : 1;  /* bit[4]    : 上行队列清除控制信号,
                                                         软件配置为1则BD,读写指针清零.此寄存器逻辑自清 */
        unsigned int  ul_rdq_clr    : 1;  /* bit[5]    : 上行队列清除控制信号,
                                                         软件配置为1则RD读写指针清零.此寄存器逻辑自清 */
        unsigned int  reserved      : 10; /* bit[6-15] : 保留 */
        unsigned int  ul_wrr_value  : 16; /* bit[16-31]: WRR值，单位字节。
                                                         上下行如果配置为WRR调度模式，此配置寄存器含义为上行分配的权重。即连续服务上行ul_wrr_value节后才相应下行。除非上行没有任务下行有任务才切到下行。 */
    } reg;
} SOC_IPF_CH0_CTRL_UNION;
#endif
#define SOC_IPF_CH0_CTRL_ul_mod_START         (0)
#define SOC_IPF_CH0_CTRL_ul_mod_END           (1)
#define SOC_IPF_CH0_CTRL_ul_endian_START      (2)
#define SOC_IPF_CH0_CTRL_ul_endian_END        (2)
#define SOC_IPF_CH0_CTRL_ul_data_chain_START  (3)
#define SOC_IPF_CH0_CTRL_ul_data_chain_END    (3)
#define SOC_IPF_CH0_CTRL_ul_bdq_clr_START     (4)
#define SOC_IPF_CH0_CTRL_ul_bdq_clr_END       (4)
#define SOC_IPF_CH0_CTRL_ul_rdq_clr_START     (5)
#define SOC_IPF_CH0_CTRL_ul_rdq_clr_END       (5)
#define SOC_IPF_CH0_CTRL_ul_wrr_value_START   (16)
#define SOC_IPF_CH0_CTRL_ul_wrr_value_END     (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_STATE_UNION
 结构说明  : CH0_STATE 寄存器结构定义。地址偏移量:0x0104，初值:0x00000014，宽度:32
 寄存器说明: 上行通道状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_busy             : 1;  /* bit[0]    : 上行busy状态指示寄存器 */
        unsigned int  ul_rdq_full         : 1;  /* bit[1]    : 上行RDQ满状态指示寄存器 */
        unsigned int  ul_rdq_empty        : 1;  /* bit[2]    : 上行RDQ空状态指示寄存器 */
        unsigned int  ul_bdq_full         : 1;  /* bit[3]    : 上行BDQ满状态指示寄存器 */
        unsigned int  ul_bdq_empty        : 1;  /* bit[4]    : 上行BDQ空状态指示寄存器 */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : 保留 */
        unsigned int  ul_rdq_rptr_invalid : 1;  /* bit[8]    : 上行RDQ读指针无效，表示软件配置的RDQ读指针大于RDQ SIZE */
        unsigned int  ul_bdq_wptr_invalid : 1;  /* bit[9]    : 上行BDQ写指针无效，表示软件配置的BDQ写指针大于BDQ SIZE */
        unsigned int  reserved_1          : 22; /* bit[10-31]: 保留。 */
    } reg;
} SOC_IPF_CH0_STATE_UNION;
#endif
#define SOC_IPF_CH0_STATE_ul_busy_START              (0)
#define SOC_IPF_CH0_STATE_ul_busy_END                (0)
#define SOC_IPF_CH0_STATE_ul_rdq_full_START          (1)
#define SOC_IPF_CH0_STATE_ul_rdq_full_END            (1)
#define SOC_IPF_CH0_STATE_ul_rdq_empty_START         (2)
#define SOC_IPF_CH0_STATE_ul_rdq_empty_END           (2)
#define SOC_IPF_CH0_STATE_ul_bdq_full_START          (3)
#define SOC_IPF_CH0_STATE_ul_bdq_full_END            (3)
#define SOC_IPF_CH0_STATE_ul_bdq_empty_START         (4)
#define SOC_IPF_CH0_STATE_ul_bdq_empty_END           (4)
#define SOC_IPF_CH0_STATE_ul_rdq_rptr_invalid_START  (8)
#define SOC_IPF_CH0_STATE_ul_rdq_rptr_invalid_END    (8)
#define SOC_IPF_CH0_STATE_ul_bdq_wptr_invalid_START  (9)
#define SOC_IPF_CH0_STATE_ul_bdq_wptr_invalid_END    (9)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_BDQ_BADDR_UNION
 结构说明  : CH0_BDQ_BADDR 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 上行通道BDQ起始地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_baddr : 32; /* bit[0-31]: 上行通道BDQ起始地址,8字节对其 */
    } reg;
} SOC_IPF_CH0_BDQ_BADDR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_BADDR_ul_bdq_baddr_START  (0)
#define SOC_IPF_CH0_BDQ_BADDR_ul_bdq_baddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_BDQ_SIZE_UNION
 结构说明  : CH0_BDQ_SIZE 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 上行通道BDQ深度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_size : 8;  /* bit[0-7] : 上行通道BDQ深度 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH0_BDQ_SIZE_UNION;
#endif
#define SOC_IPF_CH0_BDQ_SIZE_ul_bdq_size_START  (0)
#define SOC_IPF_CH0_BDQ_SIZE_ul_bdq_size_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_BDQ_WPTR_UNION
 结构说明  : CH0_BDQ_WPTR 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 上行通道BDQ写指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_wptr : 8;  /* bit[0-7] : 上行通道BDQ写指针，不能大于上行BDQ深度 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH0_BDQ_WPTR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_WPTR_ul_bdq_wptr_START  (0)
#define SOC_IPF_CH0_BDQ_WPTR_ul_bdq_wptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_BDQ_RPTR_UNION
 结构说明  : CH0_BDQ_RPTR 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 上行通道BDQ读指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_rptr : 8;  /* bit[0-7] : 上行通道BDQ读指针 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH0_BDQ_RPTR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_RPTR_ul_bdq_rptr_START  (0)
#define SOC_IPF_CH0_BDQ_RPTR_ul_bdq_rptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_BDQ_WADDR_UNION
 结构说明  : CH0_BDQ_WADDR 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 上行通道BDQ写地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_waddr : 32; /* bit[0-31]: 上行通道BDQ写地址 */
    } reg;
} SOC_IPF_CH0_BDQ_WADDR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_WADDR_ul_bdq_waddr_START  (0)
#define SOC_IPF_CH0_BDQ_WADDR_ul_bdq_waddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_BDQ_RADDR_UNION
 结构说明  : CH0_BDQ_RADDR 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: 上行通道BDQ读地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_raddr : 32; /* bit[0-31]: 上行通道BDQ读地址 */
    } reg;
} SOC_IPF_CH0_BDQ_RADDR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_RADDR_ul_bdq_raddr_START  (0)
#define SOC_IPF_CH0_BDQ_RADDR_ul_bdq_raddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_RDQ_BADDR_UNION
 结构说明  : CH0_RDQ_BADDR 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: 上行通道RDQ起始地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_baddr : 32; /* bit[0-31]: 上行通道RDQ起始地址,8字节对其 */
    } reg;
} SOC_IPF_CH0_RDQ_BADDR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_BADDR_ul_rdq_baddr_START  (0)
#define SOC_IPF_CH0_RDQ_BADDR_ul_rdq_baddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_RDQ_SIZE_UNION
 结构说明  : CH0_RDQ_SIZE 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 上行通道RDQ深度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_size : 8;  /* bit[0-7] : 上行通道RDQ深度 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH0_RDQ_SIZE_UNION;
#endif
#define SOC_IPF_CH0_RDQ_SIZE_ul_rdq_size_START  (0)
#define SOC_IPF_CH0_RDQ_SIZE_ul_rdq_size_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_RDQ_WPTR_UNION
 结构说明  : CH0_RDQ_WPTR 寄存器结构定义。地址偏移量:0x0128，初值:0x00000000，宽度:32
 寄存器说明: 上行通道RDQ写指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_wptr : 8;  /* bit[0-7] : 上行通道RDQ写指针 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH0_RDQ_WPTR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_WPTR_ul_rdq_wptr_START  (0)
#define SOC_IPF_CH0_RDQ_WPTR_ul_rdq_wptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_RDQ_RPTR_UNION
 结构说明  : CH0_RDQ_RPTR 寄存器结构定义。地址偏移量:0x012C，初值:0x00000000，宽度:32
 寄存器说明: 上行通道RDQ读指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_rptr : 8;  /* bit[0-7] : 上行通道RDQ读指针，不能大于上行RDQ深度 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH0_RDQ_RPTR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_RPTR_ul_rdq_rptr_START  (0)
#define SOC_IPF_CH0_RDQ_RPTR_ul_rdq_rptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_RDQ_WADDR_UNION
 结构说明  : CH0_RDQ_WADDR 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 上行通道RDQ写地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_waddr : 32; /* bit[0-31]: 上行通道RDQ写地址 */
    } reg;
} SOC_IPF_CH0_RDQ_WADDR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_WADDR_ul_rdq_waddr_START  (0)
#define SOC_IPF_CH0_RDQ_WADDR_ul_rdq_waddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_RDQ_RADDR_UNION
 结构说明  : CH0_RDQ_RADDR 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: 上行通道RDQ读地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_raddr : 32; /* bit[0-31]: 上行通道RDQ读地址 */
    } reg;
} SOC_IPF_CH0_RDQ_RADDR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_RADDR_ul_rdq_raddr_START  (0)
#define SOC_IPF_CH0_RDQ_RADDR_ul_rdq_raddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_DQ_DEPTH_UNION
 结构说明  : CH0_DQ_DEPTH 寄存器结构定义。地址偏移量:0x0138，初值:0x00000000，宽度:32
 寄存器说明: 上行通道队列深度指示寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_depth : 9;  /* bit[0-8]  : 上行BDQ当前深度寄存器,表示BDQ中BD的个数.等于0表示空,等于(ul_bdq_size+1)表示满 */
        unsigned int  reserved_0   : 7;  /* bit[9-15] : 保留. */
        unsigned int  ul_rdq_depth : 9;  /* bit[16-24]: 上行RDQ当前深度寄存器,表示RDQ中RD的个数.等于0表示空,等于(ul_rdq_size+1)表示满 */
        unsigned int  reserved_1   : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_IPF_CH0_DQ_DEPTH_UNION;
#endif
#define SOC_IPF_CH0_DQ_DEPTH_ul_bdq_depth_START  (0)
#define SOC_IPF_CH0_DQ_DEPTH_ul_bdq_depth_END    (8)
#define SOC_IPF_CH0_DQ_DEPTH_ul_rdq_depth_START  (16)
#define SOC_IPF_CH0_DQ_DEPTH_ul_rdq_depth_END    (24)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_CTRL_UNION
 结构说明  : CH1_CTRL 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 下行通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_mod        : 2;  /* bit[0-1]  : 模式控制寄存器
                                                         00：搬数过滤
                                                         01：只过滤
                                                         10 or 11：只搬数；
                                                         当mm_en控制位有效时，这个域无效； */
        unsigned int  dl_endian     : 1;  /* bit[2]    : 输入数据大小端指示
                                                         0：big endian
                                                         1：little endian */
        unsigned int  dl_data_chain : 1;  /* bit[3]    : 数据是否为链表 */
        unsigned int  dl_bdq_clr    : 1;  /* bit[4]    : 下行队列清除控制信号,
                                                         软件配置为1则BD读写指针清零.此寄存器逻辑自清 */
        unsigned int  dl_rdq_clr    : 1;  /* bit[5]    : 下行队列清除控制信号,
                                                         软件配置为1则RD读写指针清零.此寄存器逻辑自清 */
        unsigned int  reserved      : 10; /* bit[6-15] : 保留 */
        unsigned int  dl_wrr_value  : 16; /* bit[16-31]: WRR值，单位字节。
                                                         上下行如果配置为WRR调度模式，此配置寄存器含义为下行分配的权重。即连续服务下行dl_wrr_value节后才相应上行。除非下行没有任务上行有任务才切到上行。 */
    } reg;
} SOC_IPF_CH1_CTRL_UNION;
#endif
#define SOC_IPF_CH1_CTRL_dl_mod_START         (0)
#define SOC_IPF_CH1_CTRL_dl_mod_END           (1)
#define SOC_IPF_CH1_CTRL_dl_endian_START      (2)
#define SOC_IPF_CH1_CTRL_dl_endian_END        (2)
#define SOC_IPF_CH1_CTRL_dl_data_chain_START  (3)
#define SOC_IPF_CH1_CTRL_dl_data_chain_END    (3)
#define SOC_IPF_CH1_CTRL_dl_bdq_clr_START     (4)
#define SOC_IPF_CH1_CTRL_dl_bdq_clr_END       (4)
#define SOC_IPF_CH1_CTRL_dl_rdq_clr_START     (5)
#define SOC_IPF_CH1_CTRL_dl_rdq_clr_END       (5)
#define SOC_IPF_CH1_CTRL_dl_wrr_value_START   (16)
#define SOC_IPF_CH1_CTRL_dl_wrr_value_END     (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_STATE_UNION
 结构说明  : CH1_STATE 寄存器结构定义。地址偏移量:0x0154，初值:0x00000014，宽度:32
 寄存器说明: 下行通道状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_busy             : 1;  /* bit[0]    : 下行busy状态指示寄存器 */
        unsigned int  dl_rdq_full         : 1;  /* bit[1]    : 下行RDQ满状态指示寄存器 */
        unsigned int  dl_rdq_empty        : 1;  /* bit[2]    : 下行RDQ空状态指示寄存器 */
        unsigned int  dl_bdq_full         : 1;  /* bit[3]    : 下行BDQ满状态指示寄存器 */
        unsigned int  dl_bdq_empty        : 1;  /* bit[4]    : 下行BDQ空状态指示寄存器 */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : 保留 */
        unsigned int  dl_rdq_rptr_invalid : 1;  /* bit[8]    : 下行RDQ读指针无效，表示软件配置的RDQ读指针大于RDQ SIZE */
        unsigned int  dl_bdq_wptr_invalid : 1;  /* bit[9]    : 下行BDQ写指针无效，表示软件配置的BDQ写指针大于BDQ SIZE */
        unsigned int  reserved_1          : 22; /* bit[10-31]: 保留。 */
    } reg;
} SOC_IPF_CH1_STATE_UNION;
#endif
#define SOC_IPF_CH1_STATE_dl_busy_START              (0)
#define SOC_IPF_CH1_STATE_dl_busy_END                (0)
#define SOC_IPF_CH1_STATE_dl_rdq_full_START          (1)
#define SOC_IPF_CH1_STATE_dl_rdq_full_END            (1)
#define SOC_IPF_CH1_STATE_dl_rdq_empty_START         (2)
#define SOC_IPF_CH1_STATE_dl_rdq_empty_END           (2)
#define SOC_IPF_CH1_STATE_dl_bdq_full_START          (3)
#define SOC_IPF_CH1_STATE_dl_bdq_full_END            (3)
#define SOC_IPF_CH1_STATE_dl_bdq_empty_START         (4)
#define SOC_IPF_CH1_STATE_dl_bdq_empty_END           (4)
#define SOC_IPF_CH1_STATE_dl_rdq_rptr_invalid_START  (8)
#define SOC_IPF_CH1_STATE_dl_rdq_rptr_invalid_END    (8)
#define SOC_IPF_CH1_STATE_dl_bdq_wptr_invalid_START  (9)
#define SOC_IPF_CH1_STATE_dl_bdq_wptr_invalid_END    (9)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_BDQ_BADDR_UNION
 结构说明  : CH1_BDQ_BADDR 寄存器结构定义。地址偏移量:0x0158，初值:0x00000000，宽度:32
 寄存器说明: 下行通道BDQ起始地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_baddr : 32; /* bit[0-31]: 下行通道BDQ起始地址,8字节对其 */
    } reg;
} SOC_IPF_CH1_BDQ_BADDR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_BADDR_dl_bdq_baddr_START  (0)
#define SOC_IPF_CH1_BDQ_BADDR_dl_bdq_baddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_BDQ_SIZE_UNION
 结构说明  : CH1_BDQ_SIZE 寄存器结构定义。地址偏移量:0x015C，初值:0x00000000，宽度:32
 寄存器说明: 下行通道BDQ深度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_size : 8;  /* bit[0-7] : 下行通道BDQ深度 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH1_BDQ_SIZE_UNION;
#endif
#define SOC_IPF_CH1_BDQ_SIZE_dl_bdq_size_START  (0)
#define SOC_IPF_CH1_BDQ_SIZE_dl_bdq_size_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_BDQ_WPTR_UNION
 结构说明  : CH1_BDQ_WPTR 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: 下行通道BDQ写指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_wptr : 8;  /* bit[0-7] : 下行通道BDQ写指针，不能大于下行BDQ深度 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH1_BDQ_WPTR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_WPTR_dl_bdq_wptr_START  (0)
#define SOC_IPF_CH1_BDQ_WPTR_dl_bdq_wptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_BDQ_RPTR_UNION
 结构说明  : CH1_BDQ_RPTR 寄存器结构定义。地址偏移量:0x0164，初值:0x00000000，宽度:32
 寄存器说明: 下行通道BDQ读指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_rptr : 8;  /* bit[0-7] : 下行通道BDQ读指针 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH1_BDQ_RPTR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_RPTR_dl_bdq_rptr_START  (0)
#define SOC_IPF_CH1_BDQ_RPTR_dl_bdq_rptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_BDQ_WADDR_UNION
 结构说明  : CH1_BDQ_WADDR 寄存器结构定义。地址偏移量:0x0168，初值:0x00000000，宽度:32
 寄存器说明: 下行通道BDQ写地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_waddr : 32; /* bit[0-31]: 下行通道BDQ写地址 */
    } reg;
} SOC_IPF_CH1_BDQ_WADDR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_WADDR_dl_bdq_waddr_START  (0)
#define SOC_IPF_CH1_BDQ_WADDR_dl_bdq_waddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_BDQ_RADDR_UNION
 结构说明  : CH1_BDQ_RADDR 寄存器结构定义。地址偏移量:0x016C，初值:0x00000000，宽度:32
 寄存器说明: 下行通道BDQ读地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_raddr : 32; /* bit[0-31]: 下行通道BDQ读地址 */
    } reg;
} SOC_IPF_CH1_BDQ_RADDR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_RADDR_dl_bdq_raddr_START  (0)
#define SOC_IPF_CH1_BDQ_RADDR_dl_bdq_raddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_RDQ_BADDR_UNION
 结构说明  : CH1_RDQ_BADDR 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: 下行通道RDQ起始地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_baddr : 32; /* bit[0-31]: 下行通道RDQ起始地址,8字节对齐 */
    } reg;
} SOC_IPF_CH1_RDQ_BADDR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_BADDR_dl_rdq_baddr_START  (0)
#define SOC_IPF_CH1_RDQ_BADDR_dl_rdq_baddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_RDQ_SIZE_UNION
 结构说明  : CH1_RDQ_SIZE 寄存器结构定义。地址偏移量:0x0174，初值:0x00000000，宽度:32
 寄存器说明: 下行通道RDQ深度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_size : 8;  /* bit[0-7] : 下行通道RDQ深度 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH1_RDQ_SIZE_UNION;
#endif
#define SOC_IPF_CH1_RDQ_SIZE_dl_rdq_size_START  (0)
#define SOC_IPF_CH1_RDQ_SIZE_dl_rdq_size_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_RDQ_WPTR_UNION
 结构说明  : CH1_RDQ_WPTR 寄存器结构定义。地址偏移量:0x0178，初值:0x00000000，宽度:32
 寄存器说明: 下行通道RDQ写指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_wptr : 8;  /* bit[0-7] : 下行通道RDQ写指针 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH1_RDQ_WPTR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_WPTR_dl_rdq_wptr_START  (0)
#define SOC_IPF_CH1_RDQ_WPTR_dl_rdq_wptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_RDQ_RPTR_UNION
 结构说明  : CH1_RDQ_RPTR 寄存器结构定义。地址偏移量:0x017C，初值:0x00000000，宽度:32
 寄存器说明: 下行通道RDQ读指针
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_rptr : 8;  /* bit[0-7] : 下行通道RDQ读指针，不能大于下行RDQ深度 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IPF_CH1_RDQ_RPTR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_RPTR_dl_rdq_rptr_START  (0)
#define SOC_IPF_CH1_RDQ_RPTR_dl_rdq_rptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_RDQ_WADDR_UNION
 结构说明  : CH1_RDQ_WADDR 寄存器结构定义。地址偏移量:0x0180，初值:0x00000000，宽度:32
 寄存器说明: 下行通道RDQ写地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_waddr : 32; /* bit[0-31]: 下行通道RDQ写地址 */
    } reg;
} SOC_IPF_CH1_RDQ_WADDR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_WADDR_dl_rdq_waddr_START  (0)
#define SOC_IPF_CH1_RDQ_WADDR_dl_rdq_waddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_RDQ_RADDR_UNION
 结构说明  : CH1_RDQ_RADDR 寄存器结构定义。地址偏移量:0x0184，初值:0x00000000，宽度:32
 寄存器说明: 下行通道RDQ读地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_raddr : 32; /* bit[0-31]: 下行通道RDQ读地址 */
    } reg;
} SOC_IPF_CH1_RDQ_RADDR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_RADDR_dl_rdq_raddr_START  (0)
#define SOC_IPF_CH1_RDQ_RADDR_dl_rdq_raddr_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_DQ_DEPTH_UNION
 结构说明  : CH1_DQ_DEPTH 寄存器结构定义。地址偏移量:0x0188，初值:0x00000000，宽度:32
 寄存器说明: 下行通道队列深度指示寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_depth : 9;  /* bit[0-8]  : 下行BDQ当前深度寄存器,表示BDQ中BD的个数.等于0表示空,等于(dl_bdq_size+1)表示满 */
        unsigned int  reserved_0   : 7;  /* bit[9-15] : 保留. */
        unsigned int  dl_rdq_depth : 9;  /* bit[16-24]: 下行RDQ当前深度寄存器,表示RDQ中RD的个数.等于0表示空,等于(dl_rdq_size+1)表示满 */
        unsigned int  reserved_1   : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_IPF_CH1_DQ_DEPTH_UNION;
#endif
#define SOC_IPF_CH1_DQ_DEPTH_dl_bdq_depth_START  (0)
#define SOC_IPF_CH1_DQ_DEPTH_dl_bdq_depth_END    (8)
#define SOC_IPF_CH1_DQ_DEPTH_dl_rdq_depth_START  (16)
#define SOC_IPF_CH1_DQ_DEPTH_dl_rdq_depth_END    (24)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ_CTRL_UNION
 结构说明  : CH0_ADQ_CTRL 寄存器结构定义。地址偏移量:0x0204，初值:0x0000，宽度:32
 寄存器说明: 上行通道ADQ控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq_en        : 2;  /* bit[0-1]  : 上行通道ADQ0使能。
                                                            00：表示上行通道不使用ADQ；
                                                            01：表示上行通道使用ADQ0；
                                                            1x：表示上行通道使用ADQ0和ADQ1； */
        unsigned int  ul_adq0_size_sel : 2;  /* bit[2-3]  : 上行ADQ0大小(ul_adq0_size)选择寄存器。
                                                            00：表示ADQ0的大小为32；
                                                            01：表示ADQ0的大小为64；
                                                            10：表示ADQ0的大小为128；
                                                            11：表示ADQ0的大小为256； */
        unsigned int  ul_adq1_size_sel : 2;  /* bit[4-5]  : 上行ADQ1大小(ul_adq1_size)选择寄存器。
                                                            00：表示ADQ1的大小为32；
                                                            01：表示ADQ1的大小为64；
                                                            10：表示ADQ1的大小为128；
                                                            11：表示ADQ1的大小为256； */
        unsigned int  reserved         : 10; /* bit[6-15] : 保留 */
        unsigned int  ul_adq_plen_th   : 16; /* bit[16-31]: 上行通道数据包长阈值。当上行通道两个adq都开启时，如果当前数据包长小于阈值，使用adq0的AD；否则使用adq1的AD */
    } reg;
} SOC_IPF_CH0_ADQ_CTRL_UNION;
#endif
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq_en_START         (0)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq_en_END           (1)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq0_size_sel_START  (2)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq0_size_sel_END    (3)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq1_size_sel_START  (4)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq1_size_sel_END    (5)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq_plen_th_START    (16)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq_plen_th_END      (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ0_BASE_UNION
 结构说明  : CH0_ADQ0_BASE 寄存器结构定义。地址偏移量:0x0210，初值:0x0000，宽度:32
 寄存器说明: 上行通道ADQ0基址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq0_base : 32; /* bit[0-31]: 上行通道目的地址描述符队列基址 */
    } reg;
} SOC_IPF_CH0_ADQ0_BASE_UNION;
#endif
#define SOC_IPF_CH0_ADQ0_BASE_ul_adq0_base_START  (0)
#define SOC_IPF_CH0_ADQ0_BASE_ul_adq0_base_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ0_STAT_UNION
 结构说明  : CH0_ADQ0_STAT 寄存器结构定义。地址偏移量:0x0214，初值:0x0200，宽度:32
 寄存器说明: 上行通道ADQ0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq0_empty        : 1;  /* bit[0]   : 上行ADQ0空状态指示寄存器 */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : 保留. */
        unsigned int  ul_adq0_rptr_invalid : 1;  /* bit[4]   : 上行ADQ0读指针无效，表示软件配置的ADQ0读指针大于ADQ0 SIZE */
        unsigned int  ul_adq0_wptr_invalid : 1;  /* bit[5]   : 上行ADQ0写指针无效，表示软件配置的ADQ0写指针大于ADQ0 SIZE */
        unsigned int  reserved_1           : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_IPF_CH0_ADQ0_STAT_UNION;
#endif
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_empty_START         (0)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_empty_END           (0)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_rptr_invalid_START  (4)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_rptr_invalid_END    (4)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_wptr_invalid_START  (5)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_wptr_invalid_END    (5)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ0_WPTR_UNION
 结构说明  : CH0_ADQ0_WPTR 寄存器结构定义。地址偏移量:0x0218，初值:0x0000，宽度:32
 寄存器说明: 上行通道ADQ0写指针寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq0_wptr : 8;  /* bit[0-7] : 上行通道ADQ0写指针，正常工作时写指针需要软件维护。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IPF_CH0_ADQ0_WPTR_UNION;
#endif
#define SOC_IPF_CH0_ADQ0_WPTR_ul_adq0_wptr_START  (0)
#define SOC_IPF_CH0_ADQ0_WPTR_ul_adq0_wptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ0_RPTR_UNION
 结构说明  : CH0_ADQ0_RPTR 寄存器结构定义。地址偏移量:0x021C，初值:0x0000，宽度:32
 寄存器说明: 上行通道ADQ0读指针寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq0_rptr : 8;  /* bit[0-7] : 上行通道ADQ0读指针，正常工作时读指针由硬件维护。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IPF_CH0_ADQ0_RPTR_UNION;
#endif
#define SOC_IPF_CH0_ADQ0_RPTR_ul_adq0_rptr_START  (0)
#define SOC_IPF_CH0_ADQ0_RPTR_ul_adq0_rptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ1_BASE_UNION
 结构说明  : CH0_ADQ1_BASE 寄存器结构定义。地址偏移量:0x0220，初值:0x0000，宽度:32
 寄存器说明: 上行通道ADQ1基址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq1_base : 32; /* bit[0-31]: 上行通道目的地址描述符队列基址 */
    } reg;
} SOC_IPF_CH0_ADQ1_BASE_UNION;
#endif
#define SOC_IPF_CH0_ADQ1_BASE_ul_adq1_base_START  (0)
#define SOC_IPF_CH0_ADQ1_BASE_ul_adq1_base_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ1_STAT_UNION
 结构说明  : CH0_ADQ1_STAT 寄存器结构定义。地址偏移量:0x0224，初值:0x0200，宽度:32
 寄存器说明: 上行通道ADQ1状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq1_empty        : 1;  /* bit[0]   : 上行ADQ1空状态指示寄存器 */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : 保留. */
        unsigned int  ul_adq1_rptr_invalid : 1;  /* bit[4]   : 上行ADQ1读指针无效，表示软件配置的ADQ1读指针大于ADQ1 SIZE */
        unsigned int  ul_adq1_wptr_invalid : 1;  /* bit[5]   : 上行ADQ1写指针无效，表示软件配置的ADQ1写指针大于ADQ1 SIZE */
        unsigned int  reserved_1           : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_IPF_CH0_ADQ1_STAT_UNION;
#endif
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_empty_START         (0)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_empty_END           (0)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_rptr_invalid_START  (4)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_rptr_invalid_END    (4)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_wptr_invalid_START  (5)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_wptr_invalid_END    (5)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ1_WPTR_UNION
 结构说明  : CH0_ADQ1_WPTR 寄存器结构定义。地址偏移量:0x0228，初值:0x0000，宽度:32
 寄存器说明: 上行通道ADQ1写指针寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq1_wptr : 8;  /* bit[0-7] : 上行通道ADQ1写指针，正常工作时写指针需要软件维护。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IPF_CH0_ADQ1_WPTR_UNION;
#endif
#define SOC_IPF_CH0_ADQ1_WPTR_ul_adq1_wptr_START  (0)
#define SOC_IPF_CH0_ADQ1_WPTR_ul_adq1_wptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH0_ADQ1_RPTR_UNION
 结构说明  : CH0_ADQ1_RPTR 寄存器结构定义。地址偏移量:0x022C，初值:0x0000，宽度:32
 寄存器说明: 上行通道ADQ1读指针寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq1_rptr : 8;  /* bit[0-7] : 上行通道ADQ1读指针，正常工作时读指针由硬件维护。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IPF_CH0_ADQ1_RPTR_UNION;
#endif
#define SOC_IPF_CH0_ADQ1_RPTR_ul_adq1_rptr_START  (0)
#define SOC_IPF_CH0_ADQ1_RPTR_ul_adq1_rptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ_CTRL_UNION
 结构说明  : CH1_ADQ_CTRL 寄存器结构定义。地址偏移量:0x0284，初值:0x0000，宽度:32
 寄存器说明: 下行通道ADQ控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq_en        : 2;  /* bit[0-1]  : 下行通道ADQ0使能。
                                                            00：表示下行通道不使用ADQ；
                                                            01：表示下行通道使用ADQ0；
                                                            1x：表示下行通道使用ADQ0和ADQ1； */
        unsigned int  dl_adq0_size_sel : 2;  /* bit[2-3]  : 下行ADQ0大小(dl_adq0_size)选择寄存器。
                                                            00：表示ADQ0的大小为32；
                                                            01：表示ADQ0的大小为64；
                                                            10：表示ADQ0的大小为128；
                                                            11：表示ADQ0的大小为256； */
        unsigned int  dl_adq1_size_sel : 2;  /* bit[4-5]  : 下行ADQ1大小(dl_adq1_size)选择寄存器。
                                                            00：表示ADQ1的大小为32；
                                                            01：表示ADQ1的大小为64；
                                                            10：表示ADQ1的大小为128；
                                                            11：表示ADQ1的大小为256； */
        unsigned int  reserved         : 10; /* bit[6-15] : 保留 */
        unsigned int  dl_adq_plen_th   : 16; /* bit[16-31]: 下行通道数据包长阈值。当下行通道两个adq都开启时，如果当前数据包长小于阈值，使用adq0的AD；否则使用adq1的AD */
    } reg;
} SOC_IPF_CH1_ADQ_CTRL_UNION;
#endif
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq_en_START         (0)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq_en_END           (1)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq0_size_sel_START  (2)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq0_size_sel_END    (3)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq1_size_sel_START  (4)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq1_size_sel_END    (5)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq_plen_th_START    (16)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq_plen_th_END      (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ0_BASE_UNION
 结构说明  : CH1_ADQ0_BASE 寄存器结构定义。地址偏移量:0x0290，初值:0x0000，宽度:32
 寄存器说明: 下行通道ADQ0基址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq0_base : 32; /* bit[0-31]: 下行通道目的地址描述符队列基址 */
    } reg;
} SOC_IPF_CH1_ADQ0_BASE_UNION;
#endif
#define SOC_IPF_CH1_ADQ0_BASE_dl_adq0_base_START  (0)
#define SOC_IPF_CH1_ADQ0_BASE_dl_adq0_base_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ0_STAT_UNION
 结构说明  : CH1_ADQ0_STAT 寄存器结构定义。地址偏移量:0x0294，初值:0x0200，宽度:32
 寄存器说明: 下行通道ADQ0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq0_empty        : 1;  /* bit[0]   : 下行ADQ0空状态指示寄存器 */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : 保留. */
        unsigned int  dl_adq0_rptr_invalid : 1;  /* bit[4]   : 下行ADQ0读指针无效，表示软件配置的ADQ0读指针大于dl_adq0_size */
        unsigned int  dl_adq0_wptr_invalid : 1;  /* bit[5]   : 下行ADQ0写指针无效，表示软件配置的ADQ0写指针大于dl_adq0_size */
        unsigned int  reserved_1           : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_IPF_CH1_ADQ0_STAT_UNION;
#endif
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_empty_START         (0)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_empty_END           (0)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_rptr_invalid_START  (4)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_rptr_invalid_END    (4)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_wptr_invalid_START  (5)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_wptr_invalid_END    (5)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ0_WPTR_UNION
 结构说明  : CH1_ADQ0_WPTR 寄存器结构定义。地址偏移量:0x0298，初值:0x0000，宽度:32
 寄存器说明: 下行通道ADQ0写指针寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq0_wptr : 8;  /* bit[0-7] : 下行通道ADQ0写指针，正常工作时写指针需要软件维护。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IPF_CH1_ADQ0_WPTR_UNION;
#endif
#define SOC_IPF_CH1_ADQ0_WPTR_dl_adq0_wptr_START  (0)
#define SOC_IPF_CH1_ADQ0_WPTR_dl_adq0_wptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ0_RPTR_UNION
 结构说明  : CH1_ADQ0_RPTR 寄存器结构定义。地址偏移量:0x029C，初值:0x0000，宽度:32
 寄存器说明: 下行通道ADQ0读指针寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq0_rptr : 8;  /* bit[0-7] : 下行通道ADQ0读指针，正常工作时读指针由硬件维护。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IPF_CH1_ADQ0_RPTR_UNION;
#endif
#define SOC_IPF_CH1_ADQ0_RPTR_dl_adq0_rptr_START  (0)
#define SOC_IPF_CH1_ADQ0_RPTR_dl_adq0_rptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ1_BASE_UNION
 结构说明  : CH1_ADQ1_BASE 寄存器结构定义。地址偏移量:0x02A0，初值:0x0000，宽度:32
 寄存器说明: 下行通道ADQ1基址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq1_base : 32; /* bit[0-31]: 下行通道目的地址描述符队列基址 */
    } reg;
} SOC_IPF_CH1_ADQ1_BASE_UNION;
#endif
#define SOC_IPF_CH1_ADQ1_BASE_dl_adq1_base_START  (0)
#define SOC_IPF_CH1_ADQ1_BASE_dl_adq1_base_END    (31)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ1_STAT_UNION
 结构说明  : CH1_ADQ1_STAT 寄存器结构定义。地址偏移量:0x02A4，初值:0x0200，宽度:32
 寄存器说明: 下行通道ADQ1状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq1_empty        : 1;  /* bit[0]   : 下行ADQ1空状态指示寄存器 */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : 保留. */
        unsigned int  dl_adq1_rptr_invalid : 1;  /* bit[4]   : 下行ADQ1读指针无效，表示软件配置的ADQ1读指针大于dl_adq1_size */
        unsigned int  dl_adq1_wptr_invalid : 1;  /* bit[5]   : 下行ADQ1写指针无效，表示软件配置的ADQ1写指针大于dl_adq1_size */
        unsigned int  reserved_1           : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_IPF_CH1_ADQ1_STAT_UNION;
#endif
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_empty_START         (0)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_empty_END           (0)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_rptr_invalid_START  (4)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_rptr_invalid_END    (4)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_wptr_invalid_START  (5)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_wptr_invalid_END    (5)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ1_WPTR_UNION
 结构说明  : CH1_ADQ1_WPTR 寄存器结构定义。地址偏移量:0x02A8，初值:0x0000，宽度:32
 寄存器说明: 下行通道ADQ1写指针寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq1_wptr : 8;  /* bit[0-7] : 下行通道ADQ1写指针，正常工作时写指针需要软件维护。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IPF_CH1_ADQ1_WPTR_UNION;
#endif
#define SOC_IPF_CH1_ADQ1_WPTR_dl_adq1_wptr_START  (0)
#define SOC_IPF_CH1_ADQ1_WPTR_dl_adq1_wptr_END    (7)


/*****************************************************************************
 结构名    : SOC_IPF_CH1_ADQ1_RPTR_UNION
 结构说明  : CH1_ADQ1_RPTR 寄存器结构定义。地址偏移量:0x02AC，初值:0x0000，宽度:32
 寄存器说明: 下行通道ADQ1读指针寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq1_rptr : 8;  /* bit[0-7] : 下行通道ADQ1读指针，正常工作时读指针由硬件维护。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_IPF_CH1_ADQ1_RPTR_UNION;
#endif
#define SOC_IPF_CH1_ADQ1_RPTR_dl_adq1_rptr_START  (0)
#define SOC_IPF_CH1_ADQ1_RPTR_dl_adq1_rptr_END    (7)






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

#endif /* end of soc_ipf_interface.h */
