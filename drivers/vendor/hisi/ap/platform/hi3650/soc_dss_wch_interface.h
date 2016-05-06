/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_wch_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:25
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_WCH.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_WCH_INTERFACE_H__
#define __SOC_DSS_WCH_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_WCH
 ****************************************************************************/
/* 寄存器说明：RDMA读入图像或WDMA写出图像左上角相对于buffer的水平偏移
   位域定义UNION结构:  SOC_DSS_WCH_DMA_OFT_X0_UNION */
#define SOC_DSS_WCH_DMA_OFT_X0_ADDR(base)             ((base) + (0x0000))

/* 寄存器说明：RDMA读入图像或WDMA写出图像左上角相对于buffer的垂直偏移
   位域定义UNION结构:  SOC_DSS_WCH_DMA_OFT_Y0_UNION */
#define SOC_DSS_WCH_DMA_OFT_Y0_ADDR(base)             ((base) + (0x0004))

/* 寄存器说明：读入图像右下角相对于buffer的水平偏移
   位域定义UNION结构:  SOC_DSS_WCH_DMA_OFT_X1_UNION */
#define SOC_DSS_WCH_DMA_OFT_X1_ADDR(base)             ((base) + (0x0008))

/* 寄存器说明：读入图像右下角相对于buffer的垂直偏移
   位域定义UNION结构:  SOC_DSS_WCH_DMA_OFT_Y1_UNION */
#define SOC_DSS_WCH_DMA_OFT_Y1_ADDR(base)             ((base) + (0x000C))

/* 寄存器说明：RDMA的Mask左上角坐标
   位域定义UNION结构:  SOC_DSS_WCH_DMA_MASK0_UNION */
#define SOC_DSS_WCH_DMA_MASK0_ADDR(base)              ((base) + (0x0010))

/* 寄存器说明：RDMA的Mask右下角坐标
   位域定义UNION结构:  SOC_DSS_WCH_DMA_MASK1_UNION */
#define SOC_DSS_WCH_DMA_MASK1_ADDR(base)              ((base) + (0x0014))

/* 寄存器说明：Y平面RDMA垂直Stretch之后的高度-1
   位域定义UNION结构:  SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_UNION */
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_ADDR(base)   ((base) + (0x0018))

/* 寄存器说明：RDMA控制
   位域定义UNION结构:  SOC_DSS_WCH_DMA_CTRL_UNION */
#define SOC_DSS_WCH_DMA_CTRL_ADDR(base)               ((base) + (0x001C))

/* 寄存器说明：tile格式地址交织使能
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TILE_SCRAM_UNION */
#define SOC_DSS_WCH_DMA_TILE_SCRAM_ADDR(base)         ((base) + (0x0020))

/* 寄存器说明：1PULSE寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_PULSE_UNION */
#define SOC_DSS_WCH_DMA_PULSE_ADDR(base)              ((base) + (0x0028))

/* 寄存器说明：保留
   位域定义UNION结构:  SOC_DSS_WCH_RWCH_CFG0_UNION */
#define SOC_DSS_WCH_RWCH_CFG0_ADDR(base)              ((base) + (0x0030))

/* 寄存器说明：WDMA控制寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_FIFO_CLR_UNION */
#define SOC_DSS_WCH_DMA_FIFO_CLR_ADDR(base)           ((base) + (0x0034))

/* 寄存器说明：WDMA输出counter_inc与counter_rst调试寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_COUNTER_DGB_UNION */
#define SOC_DSS_WCH_DMA_COUNTER_DGB_ADDR(base)        ((base) + (0x003C))

/* 寄存器说明：WDMA旋转时的BURST Length调试用寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_ROT_BURST4_UNION */
#define SOC_DSS_WCH_DMA_ROT_BURST4_ADDR(base)         ((base) + (0x0040))

/* 寄存器说明：WDMA保留1寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_RSV1_UNION */
#define SOC_DSS_WCH_DMA_RSV1_ADDR(base)               ((base) + (0x0044))

/* 寄存器说明：WDMA保留2寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_RSV2_UNION */
#define SOC_DSS_WCH_DMA_RSV2_ADDR(base)               ((base) + (0x0048))

/* 寄存器说明：WDMA软件MASK使能寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_SW_MASK_EN_UNION */
#define SOC_DSS_WCH_DMA_SW_MASK_EN_ADDR(base)         ((base) + (0x004C))

/* 寄存器说明：WDMA输出图像行首MASK0寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_START_MASK0_UNION */
#define SOC_DSS_WCH_DMA_START_MASK0_ADDR(base)        ((base) + (0x0050))

/* 寄存器说明：WDMA输出图像行尾MASK0寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_END_MASK0_UNION */
#define SOC_DSS_WCH_DMA_END_MASK0_ADDR(base)          ((base) + (0x0054))

/* 寄存器说明：WDMA输出图像行首MASK1寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_START_MASK1_UNION */
#define SOC_DSS_WCH_DMA_START_MASK1_ADDR(base)        ((base) + (0x0058))

/* 寄存器说明：WDMA输出图像行尾MASK1寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_END_MASK1_UNION */
#define SOC_DSS_WCH_DMA_END_MASK1_ADDR(base)          ((base) + (0x005C))

/* 寄存器说明：RDMA读入图像或WDMA写出图像的Y平面Data读地址寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_DATA_ADDR0_UNION */
#define SOC_DSS_WCH_DMA_DATA_ADDR0_ADDR(base)         ((base) + (0x0060))

/* 寄存器说明：RDMA读入图像或WDMA写出图像的原图Y行地址偏移
   位域定义UNION结构:  SOC_DSS_WCH_DMA_STRIDE0_UNION */
#define SOC_DSS_WCH_DMA_STRIDE0_ADDR(base)            ((base) + (0x0064))

/* 寄存器说明：Y平面跳行之后的对应的stride
   位域定义UNION结构:  SOC_DSS_WCH_DMA_STRETCH_STRIDE0_UNION */
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_ADDR(base)    ((base) + (0x0068))

/* 寄存器说明：RDMA或WDMA输出图像Y平面包含128bit数据的个数
   位域定义UNION结构:  SOC_DSS_WCH_DMA_DATA_NUM0_UNION */
#define SOC_DSS_WCH_DMA_DATA_NUM0_ADDR(base)          ((base) + (0x006C))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TEST0_UNION */
#define SOC_DSS_WCH_DMA_TEST0_ADDR(base)              ((base) + (0x0070))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TEST1_UNION */
#define SOC_DSS_WCH_DMA_TEST1_ADDR(base)              ((base) + (0x0074))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TEST3_UNION */
#define SOC_DSS_WCH_DMA_TEST3_ADDR(base)              ((base) + (0x0078))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TEST4_UNION */
#define SOC_DSS_WCH_DMA_TEST4_ADDR(base)              ((base) + (0x007C))

/* 寄存器说明：状态上报寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_STATUS_Y_UNION */
#define SOC_DSS_WCH_DMA_STATUS_Y_ADDR(base)           ((base) + (0x0080))

/* 寄存器说明：RDMA读入图像或WDMA写出图像的U平面Data读地址寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_DATA_ADDR1_UNION */
#define SOC_DSS_WCH_DMA_DATA_ADDR1_ADDR(base)         ((base) + (0x0084))

/* 寄存器说明：RDMA读入图像或WDMA写出图像的原图U平面行地址偏移寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_STRIDE1_UNION */
#define SOC_DSS_WCH_DMA_STRIDE1_ADDR(base)            ((base) + (0x0088))

/* 寄存器说明：U平面跳行之后的对应的stride
   位域定义UNION结构:  SOC_DSS_WCH_DMA_STRETCH_STRIDE1_UNION */
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_ADDR(base)    ((base) + (0x008C))

/* 寄存器说明：RDMA或WDMA输出图像U平面包含128bit数据的个数
   位域定义UNION结构:  SOC_DSS_WCH_DMA_DATA_NUM1_UNION */
#define SOC_DSS_WCH_DMA_DATA_NUM1_ADDR(base)          ((base) + (0x0090))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TEST0_U_UNION */
#define SOC_DSS_WCH_DMA_TEST0_U_ADDR(base)            ((base) + (0x0094))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TEST1_U_UNION */
#define SOC_DSS_WCH_DMA_TEST1_U_ADDR(base)            ((base) + (0x0098))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TEST3_U_UNION */
#define SOC_DSS_WCH_DMA_TEST3_U_ADDR(base)            ((base) + (0x009C))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_TEST4_U_UNION */
#define SOC_DSS_WCH_DMA_TEST4_U_ADDR(base)            ((base) + (0x00A0))

/* 寄存器说明：状态上报寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_STATUS_U_UNION */
#define SOC_DSS_WCH_DMA_STATUS_U_ADDR(base)           ((base) + (0x00A4))

/* 寄存器说明：读寄存器选择
   位域定义UNION结构:  SOC_DSS_WCH_CH_RD_SHADOW_UNION */
#define SOC_DSS_WCH_CH_RD_SHADOW_ADDR(base)           ((base) + (0x00D0))

/* 寄存器说明：通道控制寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CH_CTL_UNION */
#define SOC_DSS_WCH_CH_CTL_ADDR(base)                 ((base) + (0x00D4))

/* 寄存器说明：通道安全使能
   位域定义UNION结构:  SOC_DSS_WCH_CH_SECU_EN_UNION */
#define SOC_DSS_WCH_CH_SECU_EN_ADDR(base)             ((base) + (0x00D8))

/* 寄存器说明：软件清场寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CH_SW_END_REQ_UNION */
#define SOC_DSS_WCH_CH_SW_END_REQ_ADDR(base)          ((base) + (0x00DC))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_WCH_CH_CLK_SEL_UNION */
#define SOC_DSS_WCH_CH_CLK_SEL_ADDR(base)             ((base) + (0x00E0))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_WCH_CH_CLK_EN_UNION */
#define SOC_DSS_WCH_CH_CLK_EN_ADDR(base)              ((base) + (0x00E4))

/* 寄存器说明：图象大小
   位域定义UNION结构:  SOC_DSS_WCH_DFC_DISP_SIZE_UNION */
#define SOC_DSS_WCH_DFC_DISP_SIZE_ADDR(base)          ((base) + (0x0100))

/* 寄存器说明：输入输出像素数
   位域定义UNION结构:  SOC_DSS_WCH_DFC_PIX_IN_NUM_UNION */
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_ADDR(base)         ((base) + (0x0104))

/* 寄存器说明：透明度数据
   位域定义UNION结构:  SOC_DSS_WCH_DFC_GLB_ALPHA_UNION */
#define SOC_DSS_WCH_DFC_GLB_ALPHA_ADDR(base)          ((base) + (0x0108))

/* 寄存器说明：显示格式
   位域定义UNION结构:  SOC_DSS_WCH_DFC_DISP_FMT_UNION */
#define SOC_DSS_WCH_DFC_DISP_FMT_ADDR(base)           ((base) + (0x010C))

/* 寄存器说明：水平裁剪区域
   位域定义UNION结构:  SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_UNION */
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_ADDR(base)       ((base) + (0x0110))

/* 寄存器说明：垂直裁剪区域
   位域定义UNION结构:  SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_UNION */
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_ADDR(base)       ((base) + (0x0114))

/* 寄存器说明：图像剪裁使能
   位域定义UNION结构:  SOC_DSS_WCH_DFC_CTL_CLIP_EN_UNION */
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_ADDR(base)        ((base) + (0x0118))

/* 寄存器说明：时钟门控模式
   位域定义UNION结构:  SOC_DSS_WCH_DFC_ICG_MODULE_UNION */
#define SOC_DSS_WCH_DFC_ICG_MODULE_ADDR(base)         ((base) + (0x011C))

/* 寄存器说明：抖动处理使能
   位域定义UNION结构:  SOC_DSS_WCH_DFC_DITHER_ENABLE_UNION */
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_ADDR(base)      ((base) + (0x0120))

/* 寄存器说明：增补像素控制
   位域定义UNION结构:  SOC_DSS_WCH_DFC_PADDING_CTL_UNION */
#define SOC_DSS_WCH_DFC_PADDING_CTL_ADDR(base)        ((base) + (0x0124))

/* 寄存器说明：色彩空间转换输入直流分量寄存器，为即时寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CSC_IDC_UNION */
#define SOC_DSS_WCH_CSC_IDC_ADDR(base)                ((base) + (0x0500))

/* 寄存器说明：色彩空间转换输出直流分量寄存器，为即时寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CSC_ODC_UNION */
#define SOC_DSS_WCH_CSC_ODC_ADDR(base)                ((base) + (0x0504))

/* 寄存器说明：色彩空间转换参数0，为即时寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CSC_P0_UNION */
#define SOC_DSS_WCH_CSC_P0_ADDR(base)                 ((base) + (0x0508))

/* 寄存器说明：色彩空间转换参数0，为即时寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CSC_P1_UNION */
#define SOC_DSS_WCH_CSC_P1_ADDR(base)                 ((base) + (0x050C))

/* 寄存器说明：色彩空间转换参数0，为即时寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CSC_P2_UNION */
#define SOC_DSS_WCH_CSC_P2_ADDR(base)                 ((base) + (0x0510))

/* 寄存器说明：色彩空间转换参数0，为即时寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CSC_P3_UNION */
#define SOC_DSS_WCH_CSC_P3_ADDR(base)                 ((base) + (0x0514))

/* 寄存器说明：色彩空间转换参数0，为即时寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CSC_P4_UNION */
#define SOC_DSS_WCH_CSC_P4_ADDR(base)                 ((base) + (0x0518))

/* 寄存器说明：时钟门控模式
   位域定义UNION结构:  SOC_DSS_WCH_CSC_ICG_MODULE_UNION */
#define SOC_DSS_WCH_CSC_ICG_MODULE_ADDR(base)         ((base) + (0x051C))

/* 寄存器说明：旋转首块行数寄存器
   位域定义UNION结构:  SOC_DSS_WCH_ROT_FIRST_LNS_UNION */
#define SOC_DSS_WCH_ROT_FIRST_LNS_ADDR(base)          ((base) + (0x0530))

/* 寄存器说明：ROT状态
   位域定义UNION结构:  SOC_DSS_WCH_ROT_STATE_UNION */
#define SOC_DSS_WCH_ROT_STATE_ADDR(base)              ((base) + (0x0534))

/* 寄存器说明：ROT 低功耗控制
   位域定义UNION结构:  SOC_DSS_WCH_ROT_MEM_CTRL_UNION */
#define SOC_DSS_WCH_ROT_MEM_CTRL_ADDR(base)           ((base) + (0x0538))

/* 寄存器说明：图象大小
   位域定义UNION结构:  SOC_DSS_WCH_ROT_SIZE_UNION */
#define SOC_DSS_WCH_ROT_SIZE_ADDR(base)               ((base) + (0x053C))

/* 寄存器说明：ROT 调试选择寄存器0。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_CTL0_UNION */
#define SOC_DSS_WCH_ROT_CPU_CTL0_ADDR(base)           ((base) + (0x0540))

/* 寄存器说明：ROT 调试启动寄存器0。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_START0_UNION */
#define SOC_DSS_WCH_ROT_CPU_START0_ADDR(base)         ((base) + (0x0544))

/* 寄存器说明：ROT 地址寄存器0。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_ADDR0_UNION */
#define SOC_DSS_WCH_ROT_CPU_ADDR0_ADDR(base)          ((base) + (0x0548))

/* 寄存器说明：ROT 读数据端口寄存器0。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_RDATA0_UNION */
#define SOC_DSS_WCH_ROT_CPU_RDATA0_ADDR(base)         ((base) + (0x054C))

/* 寄存器说明：ROT 读数据端口寄存器1。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_RDATA1_UNION */
#define SOC_DSS_WCH_ROT_CPU_RDATA1_ADDR(base)         ((base) + (0x0550))

/* 寄存器说明：ROT 写数据端口寄存器0。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_WDATA0_UNION */
#define SOC_DSS_WCH_ROT_CPU_WDATA0_ADDR(base)         ((base) + (0x0554))

/* 寄存器说明：ROT 写数据端口寄存器1。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_WDATA1_UNION */
#define SOC_DSS_WCH_ROT_CPU_WDATA1_ADDR(base)         ((base) + (0x0558))

/* 寄存器说明：ROT 调试选择寄存器1。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_CTL1_UNION */
#define SOC_DSS_WCH_ROT_CPU_CTL1_ADDR(base)           ((base) + (0x055C))

/* 寄存器说明：ROT 调试启动寄存器1。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_START1_UNION */
#define SOC_DSS_WCH_ROT_CPU_START1_ADDR(base)         ((base) + (0x0560))

/* 寄存器说明：ROT 地址寄存器1。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_ADDR1_UNION */
#define SOC_DSS_WCH_ROT_CPU_ADDR1_ADDR(base)          ((base) + (0x0564))

/* 寄存器说明：ROT 读数据端口寄存器2。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_RDATA2_UNION */
#define SOC_DSS_WCH_ROT_CPU_RDATA2_ADDR(base)         ((base) + (0x0568))

/* 寄存器说明：ROT 读数据端口寄存器3。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_RDATA3_UNION */
#define SOC_DSS_WCH_ROT_CPU_RDATA3_ADDR(base)         ((base) + (0x056C))

/* 寄存器说明：ROT 写数据端口寄存器。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_WDATA2_UNION */
#define SOC_DSS_WCH_ROT_CPU_WDATA2_ADDR(base)         ((base) + (0x0570))

/* 寄存器说明：ROT 写数据端口寄存器3。
   位域定义UNION结构:  SOC_DSS_WCH_ROT_CPU_WDATA3_UNION */
#define SOC_DSS_WCH_ROT_CPU_WDATA3_ADDR(base)         ((base) + (0x0574))

/* 寄存器说明：调试选择寄存器
   位域定义UNION结构:  SOC_DSS_WCH_CH_DEBUG_SEL_UNION */
#define SOC_DSS_WCH_CH_DEBUG_SEL_ADDR(base)           ((base) + (0x600))

/* 寄存器说明：DMA_BUF控制寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CTRL_UNION */
#define SOC_DSS_WCH_DMA_BUF_CTRL_ADDR(base)           ((base) + (0x0800))

/* 寄存器说明：DMA_BUF 调试选择寄存器。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_CTL_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_ADDR(base)        ((base) + (0x0804))

/* 寄存器说明：DMA_BUF 调试启动寄存器。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_START_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_START_ADDR(base)      ((base) + (0x0808))

/* 寄存器说明：DMA_BUF 地址寄存器。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_ADDR_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_ADDR(base)       ((base) + (0x080C))

/* 寄存器说明：DMA_BUF 读数据端口寄存器0。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_ADDR(base)     ((base) + (0x0810))

/* 寄存器说明：DMA_BUF 读数据端口寄存器1。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_ADDR(base)     ((base) + (0x814))

/* 寄存器说明：DMA_BUF 读数据端口寄存器2。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_ADDR(base)     ((base) + (0x818))

/* 寄存器说明：DMA_BUF 读数据端口寄存器3。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_ADDR(base)     ((base) + (0x81C))

/* 寄存器说明：DMA_BUF 写数据端口寄存器0。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_ADDR(base)     ((base) + (0x820))

/* 寄存器说明：DMA_BUF 写数据端口寄存器1。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_ADDR(base)     ((base) + (0x824))

/* 寄存器说明：DMA_BUF 写数据端口寄存器2。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_ADDR(base)     ((base) + (0x828))

/* 寄存器说明：DMA_BUF 写数据端口寄存器3。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_ADDR(base)     ((base) + (0x82C))

/* 寄存器说明：MMU TLB 读数据端口寄存器0。
   位域定义UNION结构:  SOC_DSS_WCH_DMA_REQ_END_UNION */
#define SOC_DSS_WCH_DMA_REQ_END_ADDR(base)            ((base) + (0x830))

/* 寄存器说明：DMA_BUF 调试寄存器
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_DBGCFG_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_ADDR(base)         ((base) + (0x834))

/* 寄存器说明：DMA_BUF调试只读寄存器0
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_DBG0_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG0_ADDR(base)           ((base) + (0x838))

/* 寄存器说明：DMA_BUF调试只读寄存器1
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_DBG1_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG1_ADDR(base)           ((base) + (0x83C))

/* 寄存器说明：DMA_BUF调试只读寄存器0
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_DBG2_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG2_ADDR(base)           ((base) + (0x840))

/* 寄存器说明：DMA_BUF调试只读寄存器1
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_DBG3_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG3_ADDR(base)           ((base) + (0x844))

/* 寄存器说明：DMA_BUF调试只读寄存器0
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_DBG4_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG4_ADDR(base)           ((base) + (0x848))

/* 寄存器说明：DMA_BUF调试只读寄存器1
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_DBG5_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG5_ADDR(base)           ((base) + (0x84C))

/* 寄存器说明：图象大小
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_SIZE_UNION */
#define SOC_DSS_WCH_DMA_BUF_SIZE_ADDR(base)           ((base) + (0x850))

/* 寄存器说明：DMA_BUF SRAM控制寄存器（TP）
   位域定义UNION结构:  SOC_DSS_WCH_DMA_BUF_MEM_CTRL_UNION */
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_ADDR(base)       ((base) + (0x0854))

/* 寄存器说明：图像16x16块个数
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_UNION */
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_ADDR(base)    ((base) + (0x0900))

/* 寄存器说明：图像格式
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_HREG_FORMAT_UNION */
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_ADDR(base)      ((base) + (0x0904))

/* 寄存器说明：压缩Header起始地址低位
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_UNION */
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_ADDR(base)  ((base) + (0x0908))

/* 寄存器说明：压缩Payload起始地址低位
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_UNION */
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_ADDR(base)  ((base) + (0x090C))

/* 寄存器说明：输入图像尺寸
   位域定义UNION结构:  SOC_DSS_WCH_PICTURE_SIZE_UNION */
#define SOC_DSS_WCH_PICTURE_SIZE_ADDR(base)           ((base) + (0x0910))

/* 寄存器说明：控制
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_CTL_UNION */
#define SOC_DSS_WCH_AFBCE_CTL_ADDR(base)              ((base) + (0x0914))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_WCH_HEADER_SRTIDE_UNION */
#define SOC_DSS_WCH_HEADER_SRTIDE_ADDR(base)          ((base) + (0x0918))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_WCH_PAYLOAD_STRIDE_UNION */
#define SOC_DSS_WCH_PAYLOAD_STRIDE_ADDR(base)         ((base) + (0x091C))

/* 寄存器说明：OUSTANDING CFG
   位域定义UNION结构:  SOC_DSS_WCH_ENC_OS_CFG_UNION */
#define SOC_DSS_WCH_ENC_OS_CFG_ADDR(base)             ((base) + (0x0920))

/* 寄存器说明：AFBCE SRAM控制寄存器
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_MEM_CTRL_UNION */
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_ADDR(base)         ((base) + (0x0924))

/* 寄存器说明：OUSTANDING CFG
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_QOS_CFG_UNION */
#define SOC_DSS_WCH_AFBCE_QOS_CFG_ADDR(base)          ((base) + (0x0928))

/* 寄存器说明：数据输出的水线寄存器
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_THRESHOLD_UNION */
#define SOC_DSS_WCH_AFBCE_THRESHOLD_ADDR(base)        ((base) + (0x092C))

/* 寄存器说明：地址交织模式寄存器
   位域定义UNION结构:  SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_UNION */
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_ADDR(base)    ((base) + (0x0930))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_WCH_REG_DEFAULT_UNION */
#define SOC_DSS_WCH_REG_DEFAULT_ADDR(base)            ((base) + (0x0A00))





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
                     (1/1) reg_WCH
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_OFT_X0_UNION
 结构说明  : DMA_OFT_X0 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: RDMA读入图像或WDMA写出图像左上角相对于buffer的水平偏移
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_oft_x0 : 12; /* bit[0-11] : RDMA读入图像或WDMA写出图像在Y平面的左上角x坐标（该坐标为相对于buffer的左上角的坐标，1代表128bit，(0,0)坐标对应于buffer的左上角）；
                                                      dma_oft_x0_y = dma_oft_x0;
                                                      dma_oft_x0_u/v = planar?dma_oft_x0:dma_oft_x0/2;
                                                      (
                                                      eg.设读入图像尺寸为320*480，且读入图像左上角在buffer的左上角。则像素起点横坐标为p0 = 0，终点横坐标为p1 = 319，则
                                                       1. “像素坐标”向“读入坐标”参考换算公式：
                                                       RGB32bpp： x0 = int[p0/4] = 0 ；
                                                       x1 = int[p1/4] = 79；
                                                       YUV422pkt：x0 = int[p0/8] = 0 ；
                                                       x1 = int[p1/8] = 39；
                                                       2. “读入坐标”算得“图像像素宽度”：
                                                       RGB32bpp格式下， pix_wid=(x1-x0+1)*4；
                                                       YUV422pkt格式下，pix_wid=(x1-x0+1)*8；
                                                      )
                                                      约束条件：
                                                      1. （x1-x0）∈[0,2047]
                                                      注:buffer的左上角即为坐标原点,buffer的起始存储地址的约束为:
                                                       Linear格式128bit对齐，即最小配置单位为 1；
                                                       Tile格式 4KByte对齐，即最小配置单位是4KByte/128bit = 256)。
                                                      2. 在planar 420和planar 422格式时，y分量的dma_oft_x0坐标必须为偶数，dma_oft_x1坐标必须为奇数。这样x1-x0+1为偶数。 */
        unsigned int  reserved   : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_OFT_X0_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_X0_dma_oft_x0_START  (0)
#define SOC_DSS_WCH_DMA_OFT_X0_dma_oft_x0_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_OFT_Y0_UNION
 结构说明  : DMA_OFT_Y0 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: RDMA读入图像或WDMA写出图像左上角相对于buffer的垂直偏移
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_oft_y0 : 16; /* bit[0-15] : RDMA读入图像或WDMA写出图像在Y平面的左上角y坐标（该坐标为相对于buffer的左上角的坐标，(0,0)坐标对应于buffer的左上角）
                                                      dma_oft_y0_y = dma_oft_y0;
                                                      dma_oft_y0_u/v = 420?dma_oft_y0:dma_oft_y0/2;
                                                      (
                                                      eg.设读入图像尺寸为320*480，且读入图像左上角在buffer的左上角。则y0=0,y1=479
                                                      )
                                                      约束条件：
                                                      1. 非旋转时（y1-y0）∈[0,8191]；
                                                       在线旋转时（y1-y0）∈[0,2559]；
                                                       离线旋转时（y1-y0）∈[0,259]；
                                                      2. 在semi planar 420/planar 420格式时，y分量的dma_oft_y0坐标必须为偶数，dma_oft_y1坐标必须为奇数。这样y1-y0+1为偶数。 */
        unsigned int  reserved   : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_OFT_Y0_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_Y0_dma_oft_y0_START  (0)
#define SOC_DSS_WCH_DMA_OFT_Y0_dma_oft_y0_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_OFT_X1_UNION
 结构说明  : DMA_OFT_X1 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 读入图像右下角相对于buffer的水平偏移
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_oft_x1 : 12; /* bit[0-11] : Y平面RDMA读入图像或WDMA写出图像右下角x坐标（该坐标为相对于buffer的左上角的坐标，1代表128bit，(0,0)坐标对应于buffer的左上角）；
                                                      dma_oft_x1_y = dma_oft_x1;
                                                      dma_oft_x1_u/v = planar?dma_oft_x1:dma_oft_x1/2;
                                                      (
                                                      eg.设读入图像尺寸为320*480，且读入图像左上角在buffer的左上角。则像素起点横坐标为p0 = 0，终点横坐标为p1 = 319，则
                                                       1. “像素坐标”向“读入坐标”参考换算公式：
                                                       RGB32bpp： x0 = int[p0/4] = 0 ；
                                                       x1 = int[p1/4] = 79；
                                                       YUV422pkt：x0 = int[p0/8] = 0 ；
                                                       x1 = int[p1/8] = 39；
                                                       2. “读入坐标”算得“图像像素宽度”：
                                                       RGB32bpp格式下， pix_wid=(x1-x0+1)*4；
                                                       YUV422pkt格式下，pix_wid=(x1-x0+1)*8；
                                                      )
                                                      约束条件：
                                                      1. （x1-x0）∈[0,2047]
                                                      注:buffer的左上角即为坐标原点,buffer的起始存储地址的约束为:
                                                       Linear格式128bit对齐，即最小配置单位为 1；
                                                       Tile格式 4KByte对齐，即最小配置单位是4KByte/128bit = 256)。
                                                      2. 在planar 420和planar 422格式时，y分量的dma_oft_x0坐标必须为偶数，dma_oft_x1坐标必须为奇数。这样x1-x0+1为偶数。 */
        unsigned int  reserved   : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_OFT_X1_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_X1_dma_oft_x1_START  (0)
#define SOC_DSS_WCH_DMA_OFT_X1_dma_oft_x1_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_OFT_Y1_UNION
 结构说明  : DMA_OFT_Y1 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 读入图像右下角相对于buffer的垂直偏移
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_oft_y1 : 16; /* bit[0-15] : RDMA读入图像或WDMA写出图像在Y平面的左上角y坐标（该坐标为相对于buffer的左上角的坐标，(0,0)坐标对应于buffer的左上角）
                                                      dma_oft_y1_y = dma_oft_y1;
                                                      dma_oft_y1_u/v = 420?dma_oft_y1:dma_oft_y1/2;
                                                      (
                                                      eg.设读入图像尺寸为320*480，且读入图像左上角在buffer的左上角。则y0=0,y1=479
                                                      )
                                                      约束条件：
                                                      1. 非旋转时（y1-y0）∈[0,8191]；
                                                       在线旋转时（y1-y0）∈[0,2559]；
                                                       离线旋转时（y1-y0）∈[0,259]；
                                                      2. 在semi planar 420/planar 420格式时，y分量的dma_oft_y0坐标必须为偶数，dma_oft_y1坐标必须为奇数。这样y1-y0+1为偶数。 */
        unsigned int  reserved   : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_OFT_Y1_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_Y1_dma_oft_y1_START  (0)
#define SOC_DSS_WCH_DMA_OFT_Y1_dma_oft_y1_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_MASK0_UNION
 结构说明  : DMA_MASK0 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: RDMA的Mask左上角坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_mask_y0 : 16; /* bit[0-15] : RDMA的mask矩形区域左上角y坐标（相对于buffer的左上角，以行为单位）
                                                       RDMA读入图像的Y平面的mask矩形区域的左上角在垂直方向的像素坐标
                                                       注：
                                                       1、WDMA不关注此项
                                                       约束：在semi planar 420/planar 420格式时，y分量的dma_oft_y0坐标必须为偶数，dma_oft_y1坐标必须为奇数。这样y1-y0+1为偶数。 */
        unsigned int  dma_mask_x0 : 12; /* bit[16-27]: RDMA的mask矩形区域左上角x坐标（相对于buffer的左上角，1代表128bit，即(0,0)坐标对应于buffer的左上角）
                                                       向大按128bit取整对齐.
                                                       旋转前原始图像的Mask区域左上角。
                                                       RDMA读入图像的Y平面的mask矩形区域的左上角在水平方向的像素坐标
                                                       注：
                                                       1、WDMA不关注此项
                                                       注1：配置的Mask区域需在图像内
                                                       注2：Mask区域可以做小，但不能做大
                                                       
                                                       约束：在planar 420和planar 422格式时，y分量的dma_mask_x0坐标必须为偶数，dma_mask_x1坐标必须为奇数。这样x1-x0+1为偶数。 */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_y0_START  (0)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_y0_END    (15)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_x0_START  (16)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_x0_END    (27)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_MASK1_UNION
 结构说明  : DMA_MASK1 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: RDMA的Mask右下角坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_mask_y1 : 16; /* bit[0-15] : RDMA的mask矩形区域右下角y坐标（相对于buffer的左上角，以行为单位）
                                                       注：
                                                       1、WDMA不关注此项
                                                       约束：在semi planar 420/planar 420格式时，y分量的dma_oft_y0坐标必须为偶数，dma_oft_y1坐标必须为奇数。这样y1-y0+1为偶数。 */
        unsigned int  dma_mask_x1 : 12; /* bit[16-27]: RDMA的mask矩形区域右下角x坐标（相对于buffer的左上角，1代表128bit）
                                                       向小按128bit取整对齐.
                                                       旋转前原始图像的Mask区域右下角。
                                                       注：
                                                       1、WDMA不关注此项
                                                       注1：配置的Mask区域需在图像内
                                                       注2：Mask区域可以做小，但不能做大
                                                       
                                                       约束：在planar 420和planar 422格式时，y分量的dma_mask_x0坐标必须为偶数，dma_mask_x1坐标必须为奇数。这样x1-x0+1为偶数。 */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_y1_START  (0)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_y1_END    (15)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_x1_START  (16)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_x1_END    (27)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_UNION
 结构说明  : DMA_STRETCH_SIZE_VRT 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: Y平面RDMA垂直Stretch之后的高度-1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stretch_size_vrt : 13; /* bit[0-12] : Y平面RDMA的输出高度-1，无论是否使能stretch都需要配置该寄存器，公式如下
                                                                dma_stretch_size_vrt=
                                                                dma_stretch_en?(向上取整((dma_oft_y1-dma_oft_y0+1)/dma_line_skip_step)-1)
                                                                 :(dma_oft_y1 - dma_oft_y0）
                                                                注：
                                                                1、WDMA不关注此项 */
        unsigned int  dma_line_skip_step   : 6;  /* bit[13-18]: Y平面垂直跳行数，6位整数格式。
                                                                注：
                                                                6'd0. 0为非法值；
                                                                6'd1. 配置为1时，读的行是y，y+1，y+1*2，y+1*3…
                                                                6'd2. 配置为2时，读的行是y，y+2，y+2*2，y+2*3…
                                                                ... . 依此类推
                                                                约束：在semi planar 420/planar 420格式时，y分量的dma_line_skip_step需配置为偶数。
                                                                
                                                                dma_line_skip_step_u/v = 420?dma_line_skip_step/2:dma_line_skip_step
                                                                注：
                                                                1、WDMA不关注此项 */
        unsigned int  reserved             : 13; /* bit[19-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_START  (0)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_END    (12)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_START    (13)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_END      (18)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_CTRL_UNION
 结构说明  : DMA_CTRL 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: RDMA控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_page_8k         : 1;  /* bit[0]    : 存储空间页大小：
                                                               0: 4K Byte（单通道32bit DDR）
                                                               1: 8K byte (双通道32bit DDR） */
        unsigned int  dma_tile_en         : 1;  /* bit[1]    : RDMA输入图像或WDMA输出存储格式：
                                                               0：Linear格式
                                                               1：Tile格式 */
        unsigned int  reserved_0          : 1;  /* bit[2]    : 保留 */
        unsigned int  dma_pix_fmt         : 5;  /* bit[3-7]  : RDMA读入图像或WDMA写出图像的像素格式：
                                                               0000：RGB565
                                                               0001：ARGB4444
                                                               0010：XRGB4444
                                                               0011：ARGB1555
                                                               0100：XRGB1555
                                                               0101：ARGB8888
                                                               0110：XRGB8888
                                                               0111：reserved
                                                               1000：YUYV Packet
                                                               1001：YUV420 Semi Planar HP
                                                               1010：YUV420 Planar HP
                                                               1011：YUV422 Semi Planar HP
                                                               1100：YUV422 Planar HP
                                                               1101：AYUV444
                                                               others：illegal reserved 
                                                               注：
                                                               1、planar格式只适用于RDMA
                                                               
                                                               RDMA的输入像素格式：
                                                               0_0000： RGB16bpp
                                                               0_0001： RGB32bpp，YUV32bpp
                                                               0_0010： YUV 422 Packet
                                                               0_0011： YUV 422 Semi-Planar HP Y
                                                               0_0100： YUV 422 Semi-Planar HP UV
                                                               0_0101： YUV 422 Semi-Planar VP Y (不支持) 
                                                               0_0110： YUV 422 Semi-Planar VP UV(不支持) 
                                                               0_0111： YUV 420 Semi-Planar Y
                                                               0_1000： YUV 420 Semi-Planar UV
                                                               0_1001： YUV 422 Planar HP Y
                                                               0_1010： YUV 422 Planar HP U
                                                               0_1011： YUV 422 Planar HP V
                                                               0_1100： YUV 422 Planar VP Y(不支持) 
                                                               0_1101： YUV 422 Planar VP U(不支持) 
                                                               0_1110： YUV 422 Planar VP V(不支持) 
                                                               0_1111： YUV 420 Planar Y
                                                               1_0000： YUV 420 Planar U
                                                               1_0001： YUV 420 Planar V
                                                               注：压缩情况下，固定配置为0_0001：RGB32bpp */
        unsigned int  dma_va_en           : 1;  /* bit[8]    : RDMA或WDMA使用虚拟地址使能：
                                                               0：RDMA直接使用物理地址；
                                                               1：RDMA使用虚拟地址，需通过MMU转换成物理地址 */
        unsigned int  dma_mirror_hrz_en   : 1;  /* bit[9]    : 水平镜像使能标志：
                                                               0：禁用
                                                               1：使能 */
        unsigned int  dma_mirror_vrt_en   : 1;  /* bit[10]   : 垂直镜像使能标志：
                                                               0：禁用
                                                               1：使能 */
        unsigned int  dma_rot             : 1;  /* bit[11]   : rot模块使能标志：
                                                               0：关闭
                                                               1：打开
                                                               注：
                                                               1、对于WDMA：当垂直镜像使能与rot模块使能同时打开时，对应顺时针旋转270°；当水平镜像使能与rot模块使能同时打开时，对应顺时针旋转90°
                                                               
                                                               视觉效果与软件配置的完整对应关系如下：
                                                               视觉效果无旋转无镜像 : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b000;
                                                               视觉效果垂直镜像 : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b010;
                                                               视觉效果水平镜像 : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b001;
                                                               视觉效果顺时针旋转90° : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b101;
                                                               视觉效果顺时针旋转180° : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b011;
                                                               视觉效果顺时针旋转270° : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b110;
                                                               视觉效果顺时针旋转90°且水平镜像 : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b100;
                                                               视觉效果顺时针旋转270°且水平镜像 或
                                                               视觉效果顺时针旋转90°且垂直镜像 : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b111;
                                                               
                                                               2、RDMA不关注此项 */
        unsigned int  dma_stretch_en      : 1;  /* bit[12]   : stretch使能标志
                                                               0: 禁用
                                                               1: 使能
                                                               注：
                                                               1、WDMA不关注此项 */
        unsigned int  reserved_1          : 4;  /* bit[13-16]: 保留 */
        unsigned int  dma_mask_en         : 1;  /* bit[17]   : RDMA的mask使能标志
                                                               0: 禁用
                                                               1: 使能
                                                               注：
                                                               1、WDMA不关注此项 */
        unsigned int  dma_phy_scrambl_4   : 1;  /* bit[18]   : 特殊reserve空间Linear格式下的物理地址交织方式4：
                                                               [27:4],addr_4_3,[2:0]进行交织。其中addr_4_3 = addr[4]^addr[3]
                                                               注：
                                                               1、WDMA不关注此项 */
        unsigned int  dma_phy_scrambl_3   : 1;  /* bit[19]   : 特殊reserve空间Linear格式下的物理地址交织方式3：
                                                               28位地址按照[27:16],[11:4],[15:12],addr_4_3,[2:0]进行交织。其中addr_4_3 = addr[4]^addr[3]
                                                               注：
                                                               1、WDMA不关注此项 */
        unsigned int  dma_phy_scrambl_2   : 1;  /* bit[20]   : 特殊reserve空间Linear格式下的物理地址交织方式2：
                                                               28位地址按照[27:15],[10:4],[14:11],addr_4_3,[2:0]进行交织。其中addr_4_3 = addr[4]^addr[3]
                                                               注：
                                                               1、WDMA不关注此项 */
        unsigned int  dma_phy_scrambl_1   : 1;  /* bit[21]   : 特殊reserve空间Linear格式下的物理地址交织方式1:
                                                               28位地址按照[27:14],[9:4],[13:10],addr_4_3,[2:0]进行交织。其中addr_4_3 = addr[4]^addr[3]
                                                               注：
                                                               1、WDMA不关注此项 */
        unsigned int  reserved_2          : 1;  /* bit[22]   : 保留 */
        unsigned int  dma_cross_128       : 1;  /* bit[23]   : 可维可测 */
        unsigned int  dma_tile_128byte_en : 1;  /* bit[24]   : 可维可测 */
        unsigned int  reserved_3          : 1;  /* bit[25]   : 保留 */
        unsigned int  reserved_4          : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_CTRL_dma_page_8k_START          (0)
#define SOC_DSS_WCH_DMA_CTRL_dma_page_8k_END            (0)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_en_START          (1)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_en_END            (1)
#define SOC_DSS_WCH_DMA_CTRL_dma_pix_fmt_START          (3)
#define SOC_DSS_WCH_DMA_CTRL_dma_pix_fmt_END            (7)
#define SOC_DSS_WCH_DMA_CTRL_dma_va_en_START            (8)
#define SOC_DSS_WCH_DMA_CTRL_dma_va_en_END              (8)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_hrz_en_START    (9)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_hrz_en_END      (9)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_vrt_en_START    (10)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_vrt_en_END      (10)
#define SOC_DSS_WCH_DMA_CTRL_dma_rot_START              (11)
#define SOC_DSS_WCH_DMA_CTRL_dma_rot_END                (11)
#define SOC_DSS_WCH_DMA_CTRL_dma_stretch_en_START       (12)
#define SOC_DSS_WCH_DMA_CTRL_dma_stretch_en_END         (12)
#define SOC_DSS_WCH_DMA_CTRL_dma_mask_en_START          (17)
#define SOC_DSS_WCH_DMA_CTRL_dma_mask_en_END            (17)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_4_START    (18)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_4_END      (18)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_3_START    (19)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_3_END      (19)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_2_START    (20)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_2_END      (20)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_1_START    (21)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_1_END      (21)
#define SOC_DSS_WCH_DMA_CTRL_dma_cross_128_START        (23)
#define SOC_DSS_WCH_DMA_CTRL_dma_cross_128_END          (23)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_128byte_en_START  (24)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_128byte_en_END    (24)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TILE_SCRAM_UNION
 结构说明  : DMA_TILE_SCRAM 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: tile格式地址交织使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_tile_scrambling_en : 1;  /* bit[0]   : tile模式下地址交织(按照28bit地址来看，就是4,3交织)使能：
                                                                 1：使用
                                                                 0：禁用 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_TILE_SCRAM_UNION;
#endif
#define SOC_DSS_WCH_DMA_TILE_SCRAM_dma_tile_scrambling_en_START  (0)
#define SOC_DSS_WCH_DMA_TILE_SCRAM_dma_tile_scrambling_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_PULSE_UNION
 结构说明  : DMA_PULSE 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 1PULSE寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_pulse : 1;  /* bit[0]   : 可维可测寄存器更新脉冲：
                                                    1'b1：更新可维可测寄存器
                                                    1'b0：保持可维可测寄存器 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_PULSE_UNION;
#endif
#define SOC_DSS_WCH_DMA_PULSE_dma_pulse_START  (0)
#define SOC_DSS_WCH_DMA_PULSE_dma_pulse_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_RWCH_CFG0_UNION
 结构说明  : RWCH_CFG0 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 保留
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwch_cfg0 : 32; /* bit[0-31]: 调试用
                                                    31: 配置为1时，实取模块时钟门控bypass
                                                    30: 配置为1时，预取模块时钟门控bypass
                                                    29: 配置为1时，数据模块时钟门控bypass
                                                    1: 配置为1时，dma_inte_err中断可刷新
                                                    0: 配置为1时，monitor 时钟门控强制生效 */
    } reg;
} SOC_DSS_WCH_RWCH_CFG0_UNION;
#endif
#define SOC_DSS_WCH_RWCH_CFG0_rwch_cfg0_START  (0)
#define SOC_DSS_WCH_RWCH_CFG0_rwch_cfg0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_FIFO_CLR_UNION
 结构说明  : DMA_FIFO_CLR 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: WDMA控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_fifo_clr : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_FIFO_CLR_UNION;
#endif
#define SOC_DSS_WCH_DMA_FIFO_CLR_dma_fifo_clr_START  (0)
#define SOC_DSS_WCH_DMA_FIFO_CLR_dma_fifo_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_COUNTER_DGB_UNION
 结构说明  : DMA_COUNTER_DGB 寄存器结构定义。地址偏移量:0x003C，初值:0x00000001，宽度:32
 寄存器说明: WDMA输出counter_inc与counter_rst调试寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_counter_en       : 1;  /* bit[0]    : WDMA输出counter_inc（表示一行已完全写入dram）与counter_rst（表示一帧已完全写入dram）的使能标志：
                                                                0：关闭
                                                                1：使能
                                                                注：
                                                                1、RDMA不关注此项 */
        unsigned int  dma_counter_inc_cnum : 4;  /* bit[1-4]  : WDMA输出counter_inc（表示一行已完全写入dram）拉高的cycle数，为实际值-1
                                                                注：
                                                                1、RDMA不关注此项 */
        unsigned int  dma_counter_rst_cnum : 4;  /* bit[5-8]  : WDMA输出counter_rst（表示一帧已完全写入dram）拉高的cycle数，为实际值-1
                                                                注：
                                                                1、RDMA不关注此项 */
        unsigned int  wch_enc_slice_h      : 8;  /* bit[9-16] : WDMA输出slice高度，为实际值-1。每输出完该寄存器指定的行数后，输出dma_counter_inc脉冲给enc，表示一个slice输出完毕。
                                                                注：
                                                                1、RDMA不关注此项 */
        unsigned int  wch_enc_space        : 4;  /* bit[17-20]: WDMA输出counter_inc信号之间的最小间距，以cycle为单位，为实际值-1
                                                                注：
                                                                1、RDMA不关注此项 */
        unsigned int  reserved             : 11; /* bit[21-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_COUNTER_DGB_UNION;
#endif
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_en_START        (0)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_en_END          (0)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_inc_cnum_START  (1)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_inc_cnum_END    (4)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_rst_cnum_START  (5)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_rst_cnum_END    (8)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_slice_h_START       (9)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_slice_h_END         (16)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_space_START         (17)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_space_END           (20)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_ROT_BURST4_UNION
 结构说明  : DMA_ROT_BURST4 寄存器结构定义。地址偏移量:0x0040，初值:0x00000001，宽度:32
 寄存器说明: WDMA旋转时的BURST Length调试用寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_rot_burst4 : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved       : 31; /* bit[1-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_ROT_BURST4_UNION;
#endif
#define SOC_DSS_WCH_DMA_ROT_BURST4_dma_rot_burst4_START  (0)
#define SOC_DSS_WCH_DMA_ROT_BURST4_dma_rot_burst4_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_RSV1_UNION
 结构说明  : DMA_RSV1 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: WDMA保留1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_reload_rsv1_reg : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_RSV1_UNION;
#endif
#define SOC_DSS_WCH_DMA_RSV1_dma_reload_rsv1_reg_START  (0)
#define SOC_DSS_WCH_DMA_RSV1_dma_reload_rsv1_reg_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_RSV2_UNION
 结构说明  : DMA_RSV2 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: WDMA保留2寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_rsv2_reg : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_RSV2_UNION;
#endif
#define SOC_DSS_WCH_DMA_RSV2_dma_rsv2_reg_START  (0)
#define SOC_DSS_WCH_DMA_RSV2_dma_rsv2_reg_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_SW_MASK_EN_UNION
 结构说明  : DMA_SW_MASK_EN 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: WDMA软件MASK使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_sw_mask_en : 1;  /* bit[0]   : WDMA写出图像行首或行尾使能软件MASK功能
                                                         0：关闭
                                                         1：打开
                                                         注：
                                                         1、RDMA不关注此项 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_SW_MASK_EN_UNION;
#endif
#define SOC_DSS_WCH_DMA_SW_MASK_EN_dma_sw_mask_en_START  (0)
#define SOC_DSS_WCH_DMA_SW_MASK_EN_dma_sw_mask_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_START_MASK0_UNION
 结构说明  : DMA_START_MASK0 寄存器结构定义。地址偏移量:0x0050，初值:0xFFFFFFFF，宽度:32
 寄存器说明: WDMA输出图像行首MASK0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_start_mask0 : 32; /* bit[0-31]: WDMA输出图像行首起始MASK0
                                                          [15:0]行首第一个128bit数据的mask
                                                          [31:16]行首第二个128bit数据的mask（仅在旋转时有效，非旋转时必须配FFFF）
                                                          注：
                                                          1、1个bit对应1个byte
                                                          2、每个bit：1'b0表示mask有效，1'b1表示mask无效 */
    } reg;
} SOC_DSS_WCH_DMA_START_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_START_MASK0_dma_start_mask0_START  (0)
#define SOC_DSS_WCH_DMA_START_MASK0_dma_start_mask0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_END_MASK0_UNION
 结构说明  : DMA_END_MASK0 寄存器结构定义。地址偏移量:0x0054，初值:0xFFFFFFFF，宽度:32
 寄存器说明: WDMA输出图像行尾MASK0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_end_mask0 : 32; /* bit[0-31]: WDMA输出图像行尾结尾MASK0
                                                        [31:16]行尾倒数第一个128bit数据的mask
                                                        [15:0]行尾倒数第二个128bit数据的mask（仅在旋转时有效，非旋转时必须配FFFF）
                                                        注：
                                                        1、1个bit对应1个byte
                                                        2、每个bit：1'b0表示mask有效，1'b1表示mask无效 */
    } reg;
} SOC_DSS_WCH_DMA_END_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_END_MASK0_dma_end_mask0_START  (0)
#define SOC_DSS_WCH_DMA_END_MASK0_dma_end_mask0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_START_MASK1_UNION
 结构说明  : DMA_START_MASK1 寄存器结构定义。地址偏移量:0x0058，初值:0xFFFFFFFF，宽度:32
 寄存器说明: WDMA输出图像行首MASK1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_start_mask1 : 32; /* bit[0-31]: WDMA输出图像行首MASK1
                                                          [15:0]行首第三个128bit数据的mask（仅在旋转时有效，非旋转时必须配FFFF）
                                                          [31:16]行首第四个128bit数据的mask（仅在旋转时有效，非旋转时必须配FFFF）
                                                          注：
                                                          1、1个bit对应1个byte
                                                          2、每个bit：1'b0表示mask有效，1'b1表示mask无效 */
    } reg;
} SOC_DSS_WCH_DMA_START_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_START_MASK1_dma_start_mask1_START  (0)
#define SOC_DSS_WCH_DMA_START_MASK1_dma_start_mask1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_END_MASK1_UNION
 结构说明  : DMA_END_MASK1 寄存器结构定义。地址偏移量:0x005C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: WDMA输出图像行尾MASK1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_end_mask1 : 32; /* bit[0-31]: WDMA输出图像行尾MASK1
                                                        [31:16]行尾倒数第三个128bit数据的mask（仅在旋转时有效，非旋转时必须配FFFF）
                                                        [15:0]行尾倒数第四个128bit数据的mask（仅在旋转时有效，非旋转时必须配FFFF）
                                                        注：
                                                        1、1个bit对应1个byte
                                                        2、每个bit：1'b0表示mask有效，1'b1表示mask无效 */
    } reg;
} SOC_DSS_WCH_DMA_END_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_END_MASK1_dma_end_mask1_START  (0)
#define SOC_DSS_WCH_DMA_END_MASK1_dma_end_mask1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_DATA_ADDR0_UNION
 结构说明  : DMA_DATA_ADDR0 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: RDMA读入图像或WDMA写出图像的Y平面Data读地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_addr0 : 32; /* bit[0-31]: RDMA读入图像或WDMA写出图像的Y平面在内存中的存储起始点Byte地址:
                                                    1. 无镜像：左上角Byte地址
                                                    2. 水平镜像：右上角Byte地址
                                                    3. 垂直：左下角Byte地址
                                                    4. 水平垂直：右下角Byte地址
                                                    
                                                    注、RDMA向16Byte对齐，低4bit始终配0，WDMA无约束 */
    } reg;
} SOC_DSS_WCH_DMA_DATA_ADDR0_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_ADDR0_dma_addr0_START  (0)
#define SOC_DSS_WCH_DMA_DATA_ADDR0_dma_addr0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_STRIDE0_UNION
 结构说明  : DMA_STRIDE0 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: RDMA读入图像或WDMA写出图像的原图Y行地址偏移
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stride0           : 13; /* bit[0-12] : RDMA读入图像或WDMA写出图像的Y平面行地址偏移量。行地址偏移量为图像在内存中相邻两行首像素存储地址之差。（1代表128bit）
                                                                 Linear格式Stride按128bit对齐，即最小配置值为1，表示Stride为128bit；
                                                                 Tile格式Stride按2的幂次方Byte对齐，最小256Byte，即最小配置值是256Byte/128bit = 16 = 10000。 */
        unsigned int  reserved_0            : 3;  /* bit[13-15]: 保留 */
        unsigned int  dma_l2t_interleave_n0 : 4;  /* bit[16-19]: Video Tile: Linear VA转Tile VA时交织的位号；
                                                                 CPU Tile：Linear PA转Tile PA 交织的位号；
                                                                 计算方法是：l2t_interleave_n=7 + log2(Stride/256)。合法范围是：7~15。
                                                                 （需要注意的是，当Stride=256Byte时，其图像宽度就是一个tile的宽度，此时n=7，Linear地址和Tile地址实际是一致的，并不需要转换） */
        unsigned int  reserved_1            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_STRIDE0_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRIDE0_dma_stride0_START            (0)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_stride0_END              (12)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_l2t_interleave_n0_START  (16)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_l2t_interleave_n0_END    (19)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_STRETCH_STRIDE0_UNION
 结构说明  : DMA_STRETCH_STRIDE0 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: Y平面跳行之后的对应的stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stretch_stride0 : 19; /* bit[0-18] : Y平面跳行之后的stride，等于dma_stretch_line_num0 * dma_stride0 */
        unsigned int  reserved            : 13; /* bit[19-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_STRETCH_STRIDE0_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_dma_stretch_stride0_START  (0)
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_dma_stretch_stride0_END    (18)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_DATA_NUM0_UNION
 结构说明  : DMA_DATA_NUM0 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: RDMA或WDMA输出图像Y平面包含128bit数据的个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_data_num0 : 30; /* bit[0-29] : RDMA读入图像或WDMA写出图像Y平面包含128bit数据的个数，计算公式如下：
                                                         1.在非yuv_semi/planar_420时：
                                                         data_num = strech?( (stretch_size_vrt+1)*(oftx1-oftx0+1) ) :((oftx1-oftx0+1)*(ofty1-ofty0+1))
                                                         2.在yuv_semi/planar_420 u/v时，对上述公式再乘以2，即：
                                                         data_num = strech?( (stretch_size_vrt+1)*(oftx1-oftx0+1)*2) :((oftx1-oftx0+1)*(ofty1-ofty0+1)*2)
                                                         注、
                                                         1. RDMA调试用 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_DATA_NUM0_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_NUM0_dma_data_num0_START  (0)
#define SOC_DSS_WCH_DMA_DATA_NUM0_dma_data_num0_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TEST0_UNION
 结构说明  : DMA_TEST0 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test0_y : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_TEST0_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST0_dma_test0_y_START  (0)
#define SOC_DSS_WCH_DMA_TEST0_dma_test0_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TEST1_UNION
 结构说明  : DMA_TEST1 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test1_y : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_TEST1_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST1_dma_test1_y_START  (0)
#define SOC_DSS_WCH_DMA_TEST1_dma_test1_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TEST3_UNION
 结构说明  : DMA_TEST3 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test3_y : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_TEST3_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST3_dma_test3_y_START  (0)
#define SOC_DSS_WCH_DMA_TEST3_dma_test3_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TEST4_UNION
 结构说明  : DMA_TEST4 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test4_y : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_TEST4_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST4_dma_test4_y_START  (0)
#define SOC_DSS_WCH_DMA_TEST4_dma_test4_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_STATUS_Y_UNION
 结构说明  : DMA_STATUS_Y 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 状态上报寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_status_y : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_STATUS_Y_UNION;
#endif
#define SOC_DSS_WCH_DMA_STATUS_Y_dma_status_y_START  (0)
#define SOC_DSS_WCH_DMA_STATUS_Y_dma_status_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_DATA_ADDR1_UNION
 结构说明  : DMA_DATA_ADDR1 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: RDMA读入图像或WDMA写出图像的U平面Data读地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_addr1 : 32; /* bit[0-31]: RDMA读入图像或WDMA写出图像的U平面在内存中的存储起始点Byte地址:
                                                    1. 无镜像：左上角Byte地址
                                                    2. 水平镜像：右上角Byte地址
                                                    3. 垂直：左下角Byte地址
                                                    4. 水平垂直：右下角Byte地址
                                                    
                                                    注、RDMA向16Byte对齐，低4bit始终配0，WDMA无约束 */
    } reg;
} SOC_DSS_WCH_DMA_DATA_ADDR1_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_ADDR1_dma_addr1_START  (0)
#define SOC_DSS_WCH_DMA_DATA_ADDR1_dma_addr1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_STRIDE1_UNION
 结构说明  : DMA_STRIDE1 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: RDMA读入图像或WDMA写出图像的原图U平面行地址偏移寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stride1           : 13; /* bit[0-12] : RDMA读入图像或WDMA写出图像的U平面行地址偏移量。行地址偏移量为图像在内存中相邻两行首像素存储地址之差。（1代表128bit）
                                                                 Linear格式Stride按128bit对齐，即最小配置值为1，表示Stride为128bit；
                                                                 Tile格式Stride按2的幂次方Byte对齐，最小256Byte，即最小配置值是256Byte/128bit = 16 = 10000。
                                                                 注：
                                                                 1、单平面格式不关注此项 */
        unsigned int  reserved_0            : 3;  /* bit[13-15]: 保留 */
        unsigned int  dma_l2t_interleave_n1 : 4;  /* bit[16-19]: Video Tile: Linear VA转Tile VA时交织的位号；
                                                                 CPU Tile：Linear PA转Tile PA 交织的位号；
                                                                 计算方法是：l2t_interleave_n=7 + log2(Stride/256)。合法范围是：7~15。
                                                                 （需要注意的是，当Stride=256Byte时，其图像宽度就是一个tile的宽度，此时n=7，Linear地址和Tile地址实际是一致的，并不需要转换） */
        unsigned int  reserved_1            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_STRIDE1_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRIDE1_dma_stride1_START            (0)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_stride1_END              (12)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_l2t_interleave_n1_START  (16)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_l2t_interleave_n1_END    (19)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_STRETCH_STRIDE1_UNION
 结构说明  : DMA_STRETCH_STRIDE1 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: U平面跳行之后的对应的stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stretch_stride1 : 19; /* bit[0-18] : U平面跳行之后对应的stride */
        unsigned int  reserved            : 13; /* bit[19-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_STRETCH_STRIDE1_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_dma_stretch_stride1_START  (0)
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_dma_stretch_stride1_END    (18)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_DATA_NUM1_UNION
 结构说明  : DMA_DATA_NUM1 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: RDMA或WDMA输出图像U平面包含128bit数据的个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_data_num1 : 30; /* bit[0-29] : RDMA读入图像或WDMA写出图像U平面包含128bit数据的个数，计算公式如下：
                                                         1.在非yuv_semi/planar_420时：
                                                         data_num = strech?( (stretch_size_vrt+1)*(oftx1-oftx0+1) ) :((oftx1-oftx0+1)*(ofty1-ofty0+1))
                                                         2.在yuv_semi/planar_420 u/v时，对上述公式再乘以2，即：
                                                         data_num = strech?( (stretch_size_vrt+1)*(oftx1-oftx0+1)*2) :((oftx1-oftx0+1)*(ofty1-ofty0+1)*2)
                                                         注、
                                                         1. RDMA调试用 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_DATA_NUM1_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_NUM1_dma_data_num1_START  (0)
#define SOC_DSS_WCH_DMA_DATA_NUM1_dma_data_num1_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TEST0_U_UNION
 结构说明  : DMA_TEST0_U 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test0_u : 32; /* bit[0-31]: 可维可测寄存器（在dma_pulse有效时更新）：
                                                      [31:4]: real.dma_addr;
                                                       [3:0]: real.dma_arlen; */
    } reg;
} SOC_DSS_WCH_DMA_TEST0_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST0_U_dma_test0_u_START  (0)
#define SOC_DSS_WCH_DMA_TEST0_U_dma_test0_u_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TEST1_U_UNION
 结构说明  : DMA_TEST1_U 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test1_u : 32; /* bit[0-31]: 可维可测寄存器（在dma_pulse有效时更新）：
                                                      31 : real.rbrg_dma_cneed;
                                                      30 : real.dma_rbrg_crdy;
                                                      29 : real.pref_va_drdy;
                                                      28 : real.pa_drdy;
                                                      [27:16]: real.pix_axis_cnt;
                                                      [15:0] : real.line_axis_cnt; */
    } reg;
} SOC_DSS_WCH_DMA_TEST1_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST1_U_dma_test1_u_START  (0)
#define SOC_DSS_WCH_DMA_TEST1_U_dma_test1_u_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TEST3_U_UNION
 结构说明  : DMA_TEST3_U 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test3_u : 32; /* bit[0-31]: 可维可测寄存器（在dma_pulse有效时更新）：
                                                      [31:16]: monitor.rbrg_dma_cneed_cnt;
                                                      [15:0]: monitor.dma_dbg_cnt[23:8]; */
    } reg;
} SOC_DSS_WCH_DMA_TEST3_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST3_U_dma_test3_u_START  (0)
#define SOC_DSS_WCH_DMA_TEST3_U_dma_test3_u_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_TEST4_U_UNION
 结构说明  : DMA_TEST4_U 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test4_u : 32; /* bit[0-31]: 可维可测寄存器（在dma_pulse有效时更新）：
                                                      [31:16]: monitor.rbrg_dma_drdy_cnt;
                                                      [15:0]: monitor.dma_dbg_cnt[23:8]; */
    } reg;
} SOC_DSS_WCH_DMA_TEST4_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST4_U_dma_test4_u_START  (0)
#define SOC_DSS_WCH_DMA_TEST4_U_dma_test4_u_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_STATUS_U_UNION
 结构说明  : DMA_STATUS_U 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000000，宽度:32
 寄存器说明: 状态上报寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_status_u : 32; /* bit[0-31]: 状态上报寄存器（内部出现某些异常时更新）：
                                                       24~31: 保留
                                                       23：pre.block_dma_req_idle
                                                       22：pre.pipeline_en
                                                       21：pre.block_end
                                                       20：pre.line_end
                                                       19：pre.inte_err_3
                                                       18：pre.inte_err_2
                                                       17：pre.inte_err_1
                                                       16：pre.inte_err_0
                                                       8~15: 保留
                                                       7：real.block_dma_req_idle
                                                       6：real.pipeline_en
                                                       5：real.block_end
                                                       4：real.line_end
                                                       3：real.inte_err_3
                                                       2：real.inte_err_2
                                                       1：real.inte_err_1
                                                       0：real.inte_err_0 */
    } reg;
} SOC_DSS_WCH_DMA_STATUS_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_STATUS_U_dma_status_u_START  (0)
#define SOC_DSS_WCH_DMA_STATUS_U_dma_status_u_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CH_RD_SHADOW_UNION
 结构说明  : CH_RD_SHADOW 寄存器结构定义。地址偏移量:0x00D0，初值:0x00000000，宽度:32
 寄存器说明: 读寄存器选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwch_rd_shadow : 1;  /* bit[0]   : 读寄存器选择：
                                                         0：工作寄存器
                                                         1：影子寄存器 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CH_RD_SHADOW_UNION;
#endif
#define SOC_DSS_WCH_CH_RD_SHADOW_rwch_rd_shadow_START  (0)
#define SOC_DSS_WCH_CH_RD_SHADOW_rwch_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CH_CTL_UNION
 结构说明  : CH_CTL 寄存器结构定义。地址偏移量:0x00D4，初值:0x00000000，宽度:32
 寄存器说明: 通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_en          : 1;  /* bit[0]   : RCH或WCH使能 */
        unsigned int  ch_version_sel : 1;  /* bit[1]   : 0：K3V3原功能版本；
                                                         1：保留 */
        unsigned int  ch_afbce_en    : 1;  /* bit[2]   : 0：关闭压缩功能
                                                         1：开启压缩功能 */
        unsigned int  ch_block_en    : 1;  /* bit[3]   : 0：关闭block功能
                                                         1：开启block功能 */
        unsigned int  ch_last_block  : 1;  /* bit[4]   : 0：表示当前帧非最后一块
                                                         1：表示当前帧最后一块 */
        unsigned int  reserved       : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CH_CTL_UNION;
#endif
#define SOC_DSS_WCH_CH_CTL_ch_en_START           (0)
#define SOC_DSS_WCH_CH_CTL_ch_en_END             (0)
#define SOC_DSS_WCH_CH_CTL_ch_version_sel_START  (1)
#define SOC_DSS_WCH_CH_CTL_ch_version_sel_END    (1)
#define SOC_DSS_WCH_CH_CTL_ch_afbce_en_START     (2)
#define SOC_DSS_WCH_CH_CTL_ch_afbce_en_END       (2)
#define SOC_DSS_WCH_CH_CTL_ch_block_en_START     (3)
#define SOC_DSS_WCH_CH_CTL_ch_block_en_END       (3)
#define SOC_DSS_WCH_CH_CTL_ch_last_block_START   (4)
#define SOC_DSS_WCH_CH_CTL_ch_last_block_END     (4)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CH_SECU_EN_UNION
 结构说明  : CH_SECU_EN 寄存器结构定义。地址偏移量:0x00D8，初值:0x00000000，宽度:32
 寄存器说明: 通道安全使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_secu_en : 1;  /* bit[0]   : 0：非安全
                                                     1：安全 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CH_SECU_EN_UNION;
#endif
#define SOC_DSS_WCH_CH_SECU_EN_ch_secu_en_START  (0)
#define SOC_DSS_WCH_CH_SECU_EN_ch_secu_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CH_SW_END_REQ_UNION
 结构说明  : CH_SW_END_REQ 寄存器结构定义。地址偏移量:0x00DC，初值:0x00000000，宽度:32
 寄存器说明: 软件清场寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_sw_end_req : 1;  /* bit[0]   : 软件写1进行清场操作，完成后该位自动清零。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CH_SW_END_REQ_UNION;
#endif
#define SOC_DSS_WCH_CH_SW_END_REQ_ch_sw_end_req_START  (0)
#define SOC_DSS_WCH_CH_SW_END_REQ_ch_sw_end_req_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CH_CLK_SEL_UNION
 结构说明  : CH_CLK_SEL 寄存器结构定义。地址偏移量:0x00E0，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                     1：表示强制打开时钟。
                                                     0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                     bit0：用于apb；
                                                     bit1：用于ch_ctl；
                                                     bit2：用于reg；
                                                     bit3：用于dma；
                                                     bit4：用于dfc；
                                                     bit5：用于vscf_v；
                                                     bit6：用于vscf_h；
                                                     bit7：用于sharp；
                                                     bit8：用于ce；
                                                     bit9：用于csc；
                                                     bit10：用于rot；
                                                     bit11：用于vpp；
                                                     bit12：用于gscf； */
    } reg;
} SOC_DSS_WCH_CH_CLK_SEL_UNION;
#endif
#define SOC_DSS_WCH_CH_CLK_SEL_ch_clk_sel_START  (0)
#define SOC_DSS_WCH_CH_CLK_SEL_ch_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CH_CLK_EN_UNION
 结构说明  : CH_CLK_EN 寄存器结构定义。地址偏移量:0x00E4，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                    1：表示软件时钟使能有效，允许硬件开钟
                                                    0：表示软件时钟使能无效，禁止硬件开钟
                                                    bit0：用于apb；
                                                    bit1：用于ch_ctl；
                                                    bit2：用于reg；
                                                    bit3：用于dma；
                                                    bit4：用于dfc；
                                                    bit5：用于scf；
                                                    bit6：保留；
                                                    bit7：用于sharp；
                                                    bit8：用于ce；
                                                    bit9：用于csc；
                                                    bit10：用于rot；
                                                    bit11：用于vpp；
                                                    bit12：用于gscf； */
    } reg;
} SOC_DSS_WCH_CH_CLK_EN_UNION;
#endif
#define SOC_DSS_WCH_CH_CLK_EN_ch_clk_en_START  (0)
#define SOC_DSS_WCH_CH_CLK_EN_ch_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_DISP_SIZE_UNION
 结构说明  : DFC_DISP_SIZE 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 图象大小
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_size_vrt : 13; /* bit[0-12] : 输入DFC的图像的垂直高度-1 */
        unsigned int  reserved_0   : 3;  /* bit[13-15]: 保留 */
        unsigned int  dfc_size_hrz : 13; /* bit[16-28]: 输入DFC的图像每行传输的像素数-1（由于是2pixel或者是4pxiel传输，所以SIZE_HRZ+1必须为2或者4的倍数） */
        unsigned int  reserved_1   : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_DISP_SIZE_UNION;
#endif
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_vrt_START  (0)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_vrt_END    (12)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_hrz_START  (16)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_hrz_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_PIX_IN_NUM_UNION
 结构说明  : DFC_PIX_IN_NUM 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: 输入输出像素数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_pix_in_num : 1;  /* bit[0]   : DFC读通道输入或者写通道输出的像素数目
                                                         0:2pixel (RDMA输出数据每像素为32bit或者24bit类型 即RGB888,YUV444)
                                                         1:4pixel (RDMA输出数据每像素为16bit类型 即RGB565,XRGB1555,XRGB4444，YUV422)
                                                         注： */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_PIX_IN_NUM_UNION;
#endif
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_dfc_pix_in_num_START  (0)
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_dfc_pix_in_num_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_GLB_ALPHA_UNION
 结构说明  : DFC_GLB_ALPHA 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 透明度数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_glb_alpha1 : 8;  /* bit[0-7]  : 当ARGB1555 A为1时选择的透明度数据 */
        unsigned int  dfc_glb_alpha0 : 8;  /* bit[8-15] : 当ARGB1555 A为0时选择的透明度数据 */
        unsigned int  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_GLB_ALPHA_UNION;
#endif
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha1_START  (0)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha1_END    (7)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha0_START  (8)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha0_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_DISP_FMT_UNION
 结构说明  : DFC_DISP_FMT 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 显示格式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_ax_swap : 1;  /* bit[0]   : AX 高低位切换(RGBA->ARGB YUVA->AYUV)
                                                      0：不交换
                                                      1：交换 */
        unsigned int  dfc_img_fmt : 5;  /* bit[1-5] : 读入时输入格式/写回输出格式
                                                      00000:RGB565
                                                      00001:XRGB4444(WDFC不支持)
                                                      00010:ARGB4444(WDFC不支持)
                                                      00011:XRGB1555(WDFC不支持)
                                                      00100:ARGB1555(WDFC不支持)
                                                      00101:XRGB8888
                                                      00110:ARGB8888
                                                      00111:BGR565
                                                      01000:XBGR4444
                                                      01001:ABGR4444
                                                      01010:XBGR1555
                                                      01011:ABGR1555
                                                      01100:XBGR8888
                                                      01101:ABGR8888
                                                      01110:YUV444
                                                      01111:YVU444
                                                      10000:YUYV422
                                                      10001:YVYU422
                                                      10010:VYUY422
                                                      10011:UYVY422 */
        unsigned int  dfc_uv_swap : 1;  /* bit[6]   : U和V交换标志：
                                                      0：不交换
                                                      1：交换 */
        unsigned int  dfc_rb_swap : 1;  /* bit[7]   : R和B交换标志：
                                                      0：不交换
                                                      1：交换 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_DISP_FMT_UNION;
#endif
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_ax_swap_START  (0)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_ax_swap_END    (0)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_img_fmt_START  (1)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_img_fmt_END    (5)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_uv_swap_START  (6)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_uv_swap_END    (6)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_rb_swap_START  (7)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_rb_swap_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_UNION
 结构说明  : DFC_CLIP_CTL_HRZ 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 水平裁剪区域
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_right_clip : 6;  /* bit[0-5]  : 图像右边界需CLIP掉的像素数（当dma_pix_fmt是32bpp类，支持0~3；16bpp类，支持0~7；8bpp，支持0~15） */
        unsigned int  reserved_0     : 10; /* bit[6-15] : 保留 */
        unsigned int  dfc_left_clip  : 6;  /* bit[16-21]: 图像左边界需CLIP掉的像素数（ROT不使能时，CLIP范围为0~15） */
        unsigned int  reserved_1     : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_UNION;
#endif
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_right_clip_START  (0)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_right_clip_END    (5)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_left_clip_START   (16)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_left_clip_END     (21)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_UNION
 结构说明  : DFC_CLIP_CTL_VRZ 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 垂直裁剪区域
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_bot_clip : 6;  /* bit[0-5]  : 图像底边界需CLIP掉的像素数（ROT使能时，CLIP范围为0~15） */
        unsigned int  reserved_0   : 10; /* bit[6-15] : 保留 */
        unsigned int  dfc_top_clip : 6;  /* bit[16-21]: 图像顶边界需CLIP掉的像素数（ROT使能时，CLIP范围为0~15） */
        unsigned int  reserved_1   : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_UNION;
#endif
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_bot_clip_START  (0)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_bot_clip_END    (5)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_top_clip_START  (16)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_top_clip_END    (21)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_CTL_CLIP_EN_UNION
 结构说明  : DFC_CTL_CLIP_EN 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 图像剪裁使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_ctl_clip_enable : 1;  /* bit[0]   : 图像剪裁使能 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_CTL_CLIP_EN_UNION;
#endif
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_START  (0)
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_ICG_MODULE_UNION
 结构说明  : DFC_ICG_MODULE 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: 时钟门控模式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_module_en : 1;  /* bit[0]   : 1'b1:子模块enable
                                                        1'b0:子模块disable */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_ICG_MODULE_UNION;
#endif
#define SOC_DSS_WCH_DFC_ICG_MODULE_dfc_module_en_START  (0)
#define SOC_DSS_WCH_DFC_ICG_MODULE_dfc_module_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_DITHER_ENABLE_UNION
 结构说明  : DFC_DITHER_ENABLE 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: 抖动处理使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_dither_en : 1;  /* bit[0]   : 
                                                        抖动处理使能 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DFC_DITHER_ENABLE_UNION;
#endif
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_dfc_dither_en_START  (0)
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_dfc_dither_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DFC_PADDING_CTL_UNION
 结构说明  : DFC_PADDING_CTL 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 增补像素控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_left_pad       : 5;  /* bit[0-4]  : 左边界增补像素数 */
        unsigned int  reserved_0         : 3;  /* bit[5-7]  : 保留 */
        unsigned int  dfc_right_pad      : 5;  /* bit[8-12] : 右边界增补像素数 */
        unsigned int  reserved_1         : 3;  /* bit[13-15]: 保留 */
        unsigned int  dfc_top_pad        : 5;  /* bit[16-20]: 上边界增补像素数 */
        unsigned int  reserved_2         : 3;  /* bit[21-23]: 保留 */
        unsigned int  dfc_bot_pad        : 5;  /* bit[24-28]: 下边界增补像素数 */
        unsigned int  reserved_3         : 2;  /* bit[29-30]: 保留 */
        unsigned int  dfc_ctl_pad_enable : 1;  /* bit[31]   : 增补像素使能 */
    } reg;
} SOC_DSS_WCH_DFC_PADDING_CTL_UNION;
#endif
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_left_pad_START        (0)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_left_pad_END          (4)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_right_pad_START       (8)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_right_pad_END         (12)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_top_pad_START         (16)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_top_pad_END           (20)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_bot_pad_START         (24)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_bot_pad_END           (28)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_ctl_pad_enable_START  (31)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_ctl_pad_enable_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CSC_IDC_UNION
 结构说明  : CSC_IDC 寄存器结构定义。地址偏移量:0x0500，初值:0x00000000，宽度:32
 寄存器说明: 色彩空间转换输入直流分量寄存器，为即时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_idc0 : 9;  /* bit[0-8]  : 输入分量0直流参数，MSB为符号位，补码表示。 */
        unsigned int  csc_idc1 : 9;  /* bit[9-17] : 输入分量1直流参数，MSB为符号位，补码表示。 */
        unsigned int  csc_idc2 : 9;  /* bit[18-26]: 输入分量2直流参数，MSB为符号位，补码表示。 */
        unsigned int  reserved : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CSC_IDC_UNION;
#endif
#define SOC_DSS_WCH_CSC_IDC_csc_idc0_START  (0)
#define SOC_DSS_WCH_CSC_IDC_csc_idc0_END    (8)
#define SOC_DSS_WCH_CSC_IDC_csc_idc1_START  (9)
#define SOC_DSS_WCH_CSC_IDC_csc_idc1_END    (17)
#define SOC_DSS_WCH_CSC_IDC_csc_idc2_START  (18)
#define SOC_DSS_WCH_CSC_IDC_csc_idc2_END    (26)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CSC_ODC_UNION
 结构说明  : CSC_ODC 寄存器结构定义。地址偏移量:0x0504，初值:0x00000000，宽度:32
 寄存器说明: 色彩空间转换输出直流分量寄存器，为即时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_odc0 : 9;  /* bit[0-8]  : 输出分量0直流参数，MSB为符号位，补码表示。 */
        unsigned int  csc_odc1 : 9;  /* bit[9-17] : 输出分量1直流参数，MSB为符号位，补码表示。 */
        unsigned int  csc_odc2 : 9;  /* bit[18-26]: 输出分量2直流参数，MSB为符号位，补码表示。 */
        unsigned int  reserved : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CSC_ODC_UNION;
#endif
#define SOC_DSS_WCH_CSC_ODC_csc_odc0_START  (0)
#define SOC_DSS_WCH_CSC_ODC_csc_odc0_END    (8)
#define SOC_DSS_WCH_CSC_ODC_csc_odc1_START  (9)
#define SOC_DSS_WCH_CSC_ODC_csc_odc1_END    (17)
#define SOC_DSS_WCH_CSC_ODC_csc_odc2_START  (18)
#define SOC_DSS_WCH_CSC_ODC_csc_odc2_END    (26)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CSC_P0_UNION
 结构说明  : CSC_P0 寄存器结构定义。地址偏移量:0x0508，初值:0x00000000，宽度:32
 寄存器说明: 色彩空间转换参数0，为即时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p00  : 11; /* bit[0-10] : 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved_0: 5;  /* bit[11-15]: 保留 */
        unsigned int  csc_p01  : 11; /* bit[16-26]: 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved_1: 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CSC_P0_UNION;
#endif
#define SOC_DSS_WCH_CSC_P0_csc_p00_START   (0)
#define SOC_DSS_WCH_CSC_P0_csc_p00_END     (10)
#define SOC_DSS_WCH_CSC_P0_csc_p01_START   (16)
#define SOC_DSS_WCH_CSC_P0_csc_p01_END     (26)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CSC_P1_UNION
 结构说明  : CSC_P1 寄存器结构定义。地址偏移量:0x050C，初值:0x00000000，宽度:32
 寄存器说明: 色彩空间转换参数0，为即时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p02  : 11; /* bit[0-10] : 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved_0: 5;  /* bit[11-15]: 保留 */
        unsigned int  csc_p10  : 11; /* bit[16-26]: 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved_1: 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CSC_P1_UNION;
#endif
#define SOC_DSS_WCH_CSC_P1_csc_p02_START   (0)
#define SOC_DSS_WCH_CSC_P1_csc_p02_END     (10)
#define SOC_DSS_WCH_CSC_P1_csc_p10_START   (16)
#define SOC_DSS_WCH_CSC_P1_csc_p10_END     (26)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CSC_P2_UNION
 结构说明  : CSC_P2 寄存器结构定义。地址偏移量:0x0510，初值:0x00000000，宽度:32
 寄存器说明: 色彩空间转换参数0，为即时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p11  : 11; /* bit[0-10] : 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved_0: 5;  /* bit[11-15]: 保留 */
        unsigned int  csc_p12  : 11; /* bit[16-26]: 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved_1: 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CSC_P2_UNION;
#endif
#define SOC_DSS_WCH_CSC_P2_csc_p11_START   (0)
#define SOC_DSS_WCH_CSC_P2_csc_p11_END     (10)
#define SOC_DSS_WCH_CSC_P2_csc_p12_START   (16)
#define SOC_DSS_WCH_CSC_P2_csc_p12_END     (26)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CSC_P3_UNION
 结构说明  : CSC_P3 寄存器结构定义。地址偏移量:0x0514，初值:0x00000000，宽度:32
 寄存器说明: 色彩空间转换参数0，为即时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p20  : 11; /* bit[0-10] : 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved_0: 5;  /* bit[11-15]: 保留 */
        unsigned int  csc_p21  : 11; /* bit[16-26]: 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved_1: 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CSC_P3_UNION;
#endif
#define SOC_DSS_WCH_CSC_P3_csc_p20_START   (0)
#define SOC_DSS_WCH_CSC_P3_csc_p20_END     (10)
#define SOC_DSS_WCH_CSC_P3_csc_p21_START   (16)
#define SOC_DSS_WCH_CSC_P3_csc_p21_END     (26)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CSC_P4_UNION
 结构说明  : CSC_P4 寄存器结构定义。地址偏移量:0x0518，初值:0x00000000，宽度:32
 寄存器说明: 色彩空间转换参数0，为即时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p22  : 11; /* bit[0-10] : 3.8数据格式：1bit符号位、2bit整数位、8bit小数位。补码表示 */
        unsigned int  reserved : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CSC_P4_UNION;
#endif
#define SOC_DSS_WCH_CSC_P4_csc_p22_START   (0)
#define SOC_DSS_WCH_CSC_P4_csc_p22_END     (10)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CSC_ICG_MODULE_UNION
 结构说明  : CSC_ICG_MODULE 寄存器结构定义。地址偏移量:0x051C，初值:0x00000000，宽度:32
 寄存器说明: 时钟门控模式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_module_en : 1;  /* bit[0]   : ICG模式使能
                                                        1'b1:子模块enable
                                                        1'b1:子模块disable */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CSC_ICG_MODULE_UNION;
#endif
#define SOC_DSS_WCH_CSC_ICG_MODULE_csc_module_en_START  (0)
#define SOC_DSS_WCH_CSC_ICG_MODULE_csc_module_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_FIRST_LNS_UNION
 结构说明  : ROT_FIRST_LNS 寄存器结构定义。地址偏移量:0x0530，初值:0x00000000，宽度:32
 寄存器说明: 旋转首块行数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_first_lns_en : 1;  /* bit[0]   : 当只旋转时，原始图像上部padding使能信号 */
        unsigned int  rot_first_lns    : 5;  /* bit[1-5] : 当只旋转时，原始图像上部padding的行数。
                                                           当16bpp时，最小padding1行，最多padding31行；
                                                           当32bpp时，最小padding1行，最多padding15行。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_WCH_ROT_FIRST_LNS_UNION;
#endif
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_en_START  (0)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_en_END    (0)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_START     (1)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_END       (5)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_STATE_UNION
 结构说明  : ROT_STATE 寄存器结构定义。地址偏移量:0x0534，初值:0x00000000，宽度:32
 寄存器说明: ROT状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_state : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_STATE_UNION;
#endif
#define SOC_DSS_WCH_ROT_STATE_rot_state_START  (0)
#define SOC_DSS_WCH_ROT_STATE_rot_state_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_MEM_CTRL_UNION
 结构说明  : ROT_MEM_CTRL 寄存器结构定义。地址偏移量:0x0538，初值:0x00000000，宽度:32
 寄存器说明: ROT 低功耗控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器，ROT memory低功耗软件配置
                                                       [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                       [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                       [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                       [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved     : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_DSS_WCH_ROT_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_ROT_MEM_CTRL_rot_mem_ctrl_START  (0)
#define SOC_DSS_WCH_ROT_MEM_CTRL_rot_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_SIZE_UNION
 结构说明  : ROT_SIZE 寄存器结构定义。地址偏移量:0x053C，初值:0x00000000，宽度:32
 寄存器说明: 图象大小
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_img_width  : 13; /* bit[0-12] : 输入ROT的有效图像宽度，按像素为单位，减一配置。
                                                          旋转不压缩时，YUV422格式，最小为2个像素，最大512个pixcel；
                                                           16RGB格式，最小1个像素，最大512个pixcel；
                                                           32RGB/YUV444格式，最小1个像素，最大512个pixcel；
                                                          旋转压缩时， YUV422格式，最小为2个像素，最大1024个pixcel；
                                                           16RGB格式，最小1个像素，最大1024个pixcel；
                                                           32RGB/YUV444格式，最小1个像素，最大512个pixcel； */
        unsigned int  reserved_0     : 3;  /* bit[13-15]: 保留 */
        unsigned int  rot_img_height : 13; /* bit[16-28]: 输入ROT的有效图像高度，按行为单位，减一配置。
                                                          Yuv422格式，最小为2行，最大4096行；
                                                          其他格式，最小为1行，最大4096行。 */
        unsigned int  reserved_1     : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_WCH_ROT_SIZE_UNION;
#endif
#define SOC_DSS_WCH_ROT_SIZE_rot_img_width_START   (0)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_width_END     (12)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_height_START  (16)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_height_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_CTL0_UNION
 结构说明  : ROT_CPU_CTL0 寄存器结构定义。地址偏移量:0x0540，初值:0x00000000，宽度:32
 寄存器说明: ROT 调试选择寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_ctl0 : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_CTL0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_CTL0_rot_cpu_ctl0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_CTL0_rot_cpu_ctl0_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_START0_UNION
 结构说明  : ROT_CPU_START0 寄存器结构定义。地址偏移量:0x0544，初值:0x00000000，宽度:32
 寄存器说明: ROT 调试启动寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_start0 : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_START0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_START0_rot_cpu_start0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_START0_rot_cpu_start0_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_ADDR0_UNION
 结构说明  : ROT_CPU_ADDR0 寄存器结构定义。地址偏移量:0x0548，初值:0x00000000，宽度:32
 寄存器说明: ROT 地址寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_addr0 : 12; /* bit[0-11] : 调试用 */
        unsigned int  reserved      : 19; /* bit[12-30]: 保留 */
        unsigned int  rot_cpu_rw0   : 1;  /* bit[31]   : 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_ADDR0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_addr0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_addr0_END    (11)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_rw0_START    (31)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_rw0_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_RDATA0_UNION
 结构说明  : ROT_CPU_RDATA0 寄存器结构定义。地址偏移量:0x054C，初值:0x00000000，宽度:32
 寄存器说明: ROT 读数据端口寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_rdata0 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA0_rot_cpu_rdata0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA0_rot_cpu_rdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_RDATA1_UNION
 结构说明  : ROT_CPU_RDATA1 寄存器结构定义。地址偏移量:0x0550，初值:0x00000000，宽度:32
 寄存器说明: ROT 读数据端口寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_rdata1 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA1_rot_cpu_rdata1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA1_rot_cpu_rdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_WDATA0_UNION
 结构说明  : ROT_CPU_WDATA0 寄存器结构定义。地址偏移量:0x0554，初值:0x00000000，宽度:32
 寄存器说明: ROT 写数据端口寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_wdata0 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA0_rot_cpu_wdata0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA0_rot_cpu_wdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_WDATA1_UNION
 结构说明  : ROT_CPU_WDATA1 寄存器结构定义。地址偏移量:0x0558，初值:0x00000000，宽度:32
 寄存器说明: ROT 写数据端口寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_wdata1 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA1_rot_cpu_wdata1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA1_rot_cpu_wdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_CTL1_UNION
 结构说明  : ROT_CPU_CTL1 寄存器结构定义。地址偏移量:0x055C，初值:0x00000000，宽度:32
 寄存器说明: ROT 调试选择寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_ctl1 : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_CTL1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_CTL1_rot_cpu_ctl1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_CTL1_rot_cpu_ctl1_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_START1_UNION
 结构说明  : ROT_CPU_START1 寄存器结构定义。地址偏移量:0x0560，初值:0x00000000，宽度:32
 寄存器说明: ROT 调试启动寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_start1 : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_START1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_START1_rot_cpu_start1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_START1_rot_cpu_start1_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_ADDR1_UNION
 结构说明  : ROT_CPU_ADDR1 寄存器结构定义。地址偏移量:0x0564，初值:0x00000000，宽度:32
 寄存器说明: ROT 地址寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_addr1 : 12; /* bit[0-11] : 调试用 */
        unsigned int  reserved      : 19; /* bit[12-30]: 保留 */
        unsigned int  rot_cpu_rw1   : 1;  /* bit[31]   : 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_ADDR1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_addr1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_addr1_END    (11)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_rw1_START    (31)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_rw1_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_RDATA2_UNION
 结构说明  : ROT_CPU_RDATA2 寄存器结构定义。地址偏移量:0x0568，初值:0x00000000，宽度:32
 寄存器说明: ROT 读数据端口寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_rdata2 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA2_rot_cpu_rdata2_START  (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA2_rot_cpu_rdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_RDATA3_UNION
 结构说明  : ROT_CPU_RDATA3 寄存器结构定义。地址偏移量:0x056C，初值:0x00000000，宽度:32
 寄存器说明: ROT 读数据端口寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_rdata3 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA3_rot_cpu_rdata3_START  (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA3_rot_cpu_rdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_WDATA2_UNION
 结构说明  : ROT_CPU_WDATA2 寄存器结构定义。地址偏移量:0x0570，初值:0x00000000，宽度:32
 寄存器说明: ROT 写数据端口寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_wdata2 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA2_rot_cpu_wdata2_START  (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA2_rot_cpu_wdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ROT_CPU_WDATA3_UNION
 结构说明  : ROT_CPU_WDATA3 寄存器结构定义。地址偏移量:0x0574，初值:0x00000000，宽度:32
 寄存器说明: ROT 写数据端口寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_wdata3 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA3_rot_cpu_wdata3_START  (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA3_rot_cpu_wdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_CH_DEBUG_SEL_UNION
 结构说明  : CH_DEBUG_SEL 寄存器结构定义。地址偏移量:0x600，初值:0x00000000，宽度:32
 寄存器说明: 调试选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_debug_sel : 4;  /* bit[0-3] : 功能模块的module_debug到ch_debug的输出选择信号, 编码值为：
                                                       'b0000:dma_y_debug
                                                       'b0001:dma_u_debug
                                                       'b0010:dma_v_debug
                                                       'b0011:rot_debug
                                                       'b0100:dfc_debug
                                                       'b0101:scf_debug
                                                       'b0110:sharp_debug
                                                       'b0111:ce_debug
                                                       'b1000:csc_debug */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_WCH_CH_DEBUG_SEL_UNION;
#endif
#define SOC_DSS_WCH_CH_DEBUG_SEL_ch_debug_sel_START  (0)
#define SOC_DSS_WCH_CH_DEBUG_SEL_ch_debug_sel_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CTRL_UNION
 结构说明  : DMA_BUF_CTRL 寄存器结构定义。地址偏移量:0x0800，初值:0x00000008，宽度:32
 寄存器说明: DMA_BUF控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_os_cfg    : 6;  /* bit[0-5]  : dma_buf流量控制寄存器。
                                                             1. 对于rdma_buf，表示使用的buf占总buf的比例，可以配置为1~8，设A为配置值：
                                                             单平面格式时使用的buf占总buf的比例为A/8；
                                                             双平面格式时使用的buf占总buf的比例为int[(A+1)/2]*2/8；
                                                             三平面格式时使用的buf占总buf的比例为int[(A+3)/4]*4/8；
                                                             2. 对于wdma_buf，代表流控的y通道最大数据量水线值，可以配置为0~15，设A为配置值，
                                                             数据量水线值为(A+1)* 8 * 16B，package格式；
                                                             数据量水线值为(A+1)* 4 * 16B，非package格式； */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : 保留 */
        unsigned int  dma_buf_qos_mask  : 1;  /* bit[8]    : 外部qos信息屏蔽寄存器
                                                             0：外部qos信息有效传输
                                                             1：外部qos信息屏蔽传输
                                                             注：
                                                             1、wdma_buf不关注此项 */
        unsigned int  dma_buf_cont_mask : 1;  /* bit[9]    : 行尾cont拉低功能屏蔽寄存器
                                                             0：行尾cont拉低使能
                                                             1：行尾cont拉低屏蔽
                                                             注：
                                                             1、wdma_buf不关注此项 */
        unsigned int  dma_buf_l_e_mask  : 1;  /* bit[10]   : 行尾buf跳转功能屏蔽寄存器
                                                             0：行尾buf跳转使能
                                                             1：行尾buf跳转屏蔽
                                                             注：
                                                             1、wdma_buf不关注此项 */
        unsigned int  reserved_1        : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_os_cfg_START     (0)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_os_cfg_END       (5)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_qos_mask_START   (8)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_qos_mask_END     (8)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_cont_mask_START  (9)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_cont_mask_END    (9)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_l_e_mask_START   (10)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_l_e_mask_END     (10)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_CTL_UNION
 结构说明  : DMA_BUF_CPU_CTL 寄存器结构定义。地址偏移量:0x0804，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 调试选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_ctl : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_CTL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_START_UNION
 结构说明  : DMA_BUF_CPU_START 寄存器结构定义。地址偏移量:0x0808，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 调试启动寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_start : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_START_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_START_dma_buf_cpu_start_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_START_dma_buf_cpu_start_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_ADDR_UNION
 结构说明  : DMA_BUF_CPU_ADDR 寄存器结构定义。地址偏移量:0x080C，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_addr : 9;  /* bit[0-8] : 调试用 */
        unsigned int  reserved         : 22; /* bit[9-30]: 保留 */
        unsigned int  dma_buf_cpu_rw   : 1;  /* bit[31]  : 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_ADDR_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_END    (8)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_START    (31)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_UNION
 结构说明  : DMA_BUF_CPU_RDATA0 寄存器结构定义。地址偏移量:0x0810，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 读数据端口寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_rdata0 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_UNION
 结构说明  : DMA_BUF_CPU_RDATA1 寄存器结构定义。地址偏移量:0x814，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 读数据端口寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_rdata1 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_UNION
 结构说明  : DMA_BUF_CPU_RDATA2 寄存器结构定义。地址偏移量:0x818，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 读数据端口寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_rdata2 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_UNION
 结构说明  : DMA_BUF_CPU_RDATA3 寄存器结构定义。地址偏移量:0x81C，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 读数据端口寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_rdata3 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_UNION
 结构说明  : DMA_BUF_CPU_WDATA0 寄存器结构定义。地址偏移量:0x820，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 写数据端口寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_wdata0 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_UNION
 结构说明  : DMA_BUF_CPU_WDATA1 寄存器结构定义。地址偏移量:0x824，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 写数据端口寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_wdata1 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_UNION
 结构说明  : DMA_BUF_CPU_WDATA2 寄存器结构定义。地址偏移量:0x828，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 写数据端口寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_wdata2 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_UNION
 结构说明  : DMA_BUF_CPU_WDATA3 寄存器结构定义。地址偏移量:0x82C，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 写数据端口寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_wdata3 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_REQ_END_UNION
 结构说明  : DMA_REQ_END 寄存器结构定义。地址偏移量:0x830，初值:0x00000000，宽度:32
 寄存器说明: MMU TLB 读数据端口寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_req_end : 1;  /* bit[0]   : 调试用 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_REQ_END_UNION;
#endif
#define SOC_DSS_WCH_DMA_REQ_END_dma_req_end_START  (0)
#define SOC_DSS_WCH_DMA_REQ_END_dma_req_end_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_DBGCFG_UNION
 结构说明  : DMA_BUF_DBGCFG 寄存器结构定义。地址偏移量:0x834，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF 调试寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbgcfg : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBGCFG_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_dma_buf_dbgcfg_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_dma_buf_dbgcfg_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_DBG0_UNION
 结构说明  : DMA_BUF_DBG0 寄存器结构定义。地址偏移量:0x838，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF调试只读寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg0 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG0_dma_buf_dbg0_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG0_dma_buf_dbg0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_DBG1_UNION
 结构说明  : DMA_BUF_DBG1 寄存器结构定义。地址偏移量:0x83C，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF调试只读寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg1 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG1_dma_buf_dbg1_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG1_dma_buf_dbg1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_DBG2_UNION
 结构说明  : DMA_BUF_DBG2 寄存器结构定义。地址偏移量:0x840，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF调试只读寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg2 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG2_dma_buf_dbg2_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG2_dma_buf_dbg2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_DBG3_UNION
 结构说明  : DMA_BUF_DBG3 寄存器结构定义。地址偏移量:0x844，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF调试只读寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg3 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG3_dma_buf_dbg3_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG3_dma_buf_dbg3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_DBG4_UNION
 结构说明  : DMA_BUF_DBG4 寄存器结构定义。地址偏移量:0x848，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF调试只读寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg4 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG4_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG4_dma_buf_dbg4_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG4_dma_buf_dbg4_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_DBG5_UNION
 结构说明  : DMA_BUF_DBG5 寄存器结构定义。地址偏移量:0x84C，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF调试只读寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg5 : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG5_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG5_dma_buf_dbg5_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG5_dma_buf_dbg5_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_SIZE_UNION
 结构说明  : DMA_BUF_SIZE 寄存器结构定义。地址偏移量:0x850，初值:0x00000000，宽度:32
 寄存器说明: 图象大小
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_img_width  : 13; /* bit[0-12] : WDMA_BUF输出的有效图像宽度，按像素为单位，减一配置。 */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: 保留 */
        unsigned int  dma_buf_img_height : 13; /* bit[16-28]: WDMA_BUF输出的有效图像高度，按行为单位，减一配置。 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_SIZE_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_width_START   (0)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_width_END     (12)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_height_START  (16)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_height_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_DMA_BUF_MEM_CTRL_UNION
 结构说明  : DMA_BUF_MEM_CTRL 寄存器结构定义。地址偏移量:0x0854，初值:0x00000000，宽度:32
 寄存器说明: DMA_BUF SRAM控制寄存器（TP）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器
                                                           [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                           [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                           [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                           [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved         : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_WCH_DMA_BUF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_START  (0)
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_UNION
 结构说明  : AFBCE_HREG_PIC_BLKS 寄存器结构定义。地址偏移量:0x0900，初值:0x00000000，宽度:32
 寄存器说明: 图像16x16块个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_pic_blks : 24; /* bit[0-23] : 图像16x16块数-1，如0表示1个16x16块 */
        unsigned int  reserved       : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_afbce_pic_blks_START  (0)
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_afbce_pic_blks_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_HREG_FORMAT_UNION
 结构说明  : AFBCE_HREG_FORMAT 寄存器结构定义。地址偏移量:0x0904，初值:0x00050000，宽度:32
 寄存器说明: 图像格式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 16; /* bit[0-15] : 保留 */
        unsigned int  reserved_1            : 5;  /* bit[16-20]: bit[20] color transform, 1-enable, 0-disable，
                                                                 bit[19:16] pixel format
                                                                 0x0: R5G6B5
                                                                 0x1: R5G5B5A1
                                                                 0x2: R10G10B10A2
                                                                 0x3: reserved
                                                                 0x4: R8G8B8
                                                                 0x5: R8G8B8A8
                                                                 0x6: R4G4B4A4
                                                                 0x7: R8, 不支持color transform
                                                                 0x8: R8G8, 不支持color transform
                                                                 0x9: YUV420,不支持color transform
                                                                 0xA: reserved
                                                                 0xB: YUV422,不支持color transform
                                                                 0xC~0xF: reserved
                                                                 注：如果是YUV422格式，需要配置成0x8，即按照R8G8格式解压
                                                                 格式编码值请参考0x1C, dma_pix_fmt寄存器 */
        unsigned int  afbce_color_transform : 1;  /* bit[21]   : color transform, 1-enable, 0-disable， */
        unsigned int  reserved_2            : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_FORMAT_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_afbce_color_transform_START  (21)
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_afbce_color_transform_END    (21)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_UNION
 结构说明  : AFBCE_HREG_HDR_PTR_LO 寄存器结构定义。地址偏移量:0x0908，初值:0x00000000，宽度:32
 寄存器说明: 压缩Header起始地址低位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_hdr_ptr_lo : 32; /* bit[0-31]: 压缩Header起始地址[31:0]，地址64Byte对齐 */
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_afbce_hdr_ptr_lo_START  (0)
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_afbce_hdr_ptr_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_UNION
 结构说明  : AFBCE_HREG_PLD_PTR_LO 寄存器结构定义。地址偏移量:0x090C，初值:0x00000000，宽度:32
 寄存器说明: 压缩Payload起始地址低位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_payload_ptr_lo : 32; /* bit[0-31]: 压缩Payload起始地址[31:0]，32比特格式的时候，为1024Byte的整数倍；16比特格式的时候，512Byte的整数倍 */
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_afbce_payload_ptr_lo_START  (0)
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_afbce_payload_ptr_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_PICTURE_SIZE_UNION
 结构说明  : PICTURE_SIZE 寄存器结构定义。地址偏移量:0x0910，初值:0x00000000，宽度:32
 寄存器说明: 输入图像尺寸
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_block_height : 16; /* bit[0-15] : 待压缩图像高度，实际像素数减1 */
        unsigned int  afbce_block_width  : 10; /* bit[16-25]: 待压缩图像宽度，实际像素数减1 */
        unsigned int  reserved           : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_WCH_PICTURE_SIZE_UNION;
#endif
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_height_START  (0)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_height_END    (15)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_width_START   (16)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_width_END     (25)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_CTL_UNION
 结构说明  : AFBCE_CTL 寄存器结构定义。地址偏移量:0x0914，初值:0x00000000，宽度:32
 寄存器说明: 控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0-0] : 合并于ch_afbce_en */
        unsigned int  reserved_1: 1;  /* bit[1-1] : 合并于ch_afbce_en */
        unsigned int  reserved_2: 1;  /* bit[2-2] : 合并于dma_rot */
        unsigned int  reserved_3: 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_WCH_AFBCE_CTL_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_DSS_WCH_HEADER_SRTIDE_UNION
 结构说明  : HEADER_SRTIDE 寄存器结构定义。地址偏移量:0x0918，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_header_stride    : 14; /* bit[0-13] : can be used for decoding a sub picture of a full picture
                                                                  必须是64byte的倍数 */
        unsigned int  afbce_header_start_pos : 2;  /* bit[14-15]: valid header in first burst
                                                                  2’b00：第1个开始有效
                                                                  2’b01：第2个开始有效
                                                                  2’b10：第3个开始有效
                                                                  2’b11：第4个开始有效 */
        unsigned int  reserved               : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_WCH_HEADER_SRTIDE_UNION;
#endif
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_stride_START     (0)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_stride_END       (13)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_start_pos_START  (14)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_start_pos_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_PAYLOAD_STRIDE_UNION
 结构说明  : PAYLOAD_STRIDE 寄存器结构定义。地址偏移量:0x091C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_payload_stride : 20; /* bit[0-19] : payload的换行的宽度 */
        unsigned int  reserved             : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_DSS_WCH_PAYLOAD_STRIDE_UNION;
#endif
#define SOC_DSS_WCH_PAYLOAD_STRIDE_afbce_payload_stride_START  (0)
#define SOC_DSS_WCH_PAYLOAD_STRIDE_afbce_payload_stride_END    (19)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_ENC_OS_CFG_UNION
 结构说明  : ENC_OS_CFG 寄存器结构定义。地址偏移量:0x0920，初值:0x00000007，宽度:32
 寄存器说明: OUSTANDING CFG
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_ddrw_os : 3;  /* bit[0-2] : VBIF MM读接口的outstanding设置，其值+1为实际outstanding值，最大值0x7 */
        unsigned int  reserved      : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_WCH_ENC_OS_CFG_UNION;
#endif
#define SOC_DSS_WCH_ENC_OS_CFG_afbce_ddrw_os_START  (0)
#define SOC_DSS_WCH_ENC_OS_CFG_afbce_ddrw_os_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_MEM_CTRL_UNION
 结构说明  : AFBCE_MEM_CTRL 寄存器结构定义。地址偏移量:0x0924，初值:0x00000000，宽度:32
 寄存器说明: AFBCE SRAM控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_mem_ctrl_0 : 4;  /* bit[0-3]  : 调试用寄存器,afbce input sp memory低功耗软件配置
                                                            [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                            [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                            [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                            [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  afbce_mem_ctrl_1 : 4;  /* bit[4-7]  : 调试用寄存器,afbce payload sp memory低功耗软件配置
                                                            [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                            [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                            [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                            [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  afbce_mem_ctrl_2 : 4;  /* bit[8-11] : 调试用寄存器,afbce header tp memory低功耗软件配置
                                                            [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                            [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                            [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                            [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_WCH_AFBCE_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_0_START  (0)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_0_END    (3)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_1_START  (4)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_1_END    (7)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_2_START  (8)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_2_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_QOS_CFG_UNION
 结构说明  : AFBCE_QOS_CFG 寄存器结构定义。地址偏移量:0x0928，初值:0x00000000，宽度:32
 寄存器说明: OUSTANDING CFG
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_qos_cfg : 3;  /* bit[0-2] : afbce的qos配置寄存器 */
        unsigned int  reserved      : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_WCH_AFBCE_QOS_CFG_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_QOS_CFG_afbce_qos_cfg_START  (0)
#define SOC_DSS_WCH_AFBCE_QOS_CFG_afbce_qos_cfg_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_THRESHOLD_UNION
 结构说明  : AFBCE_THRESHOLD 寄存器结构定义。地址偏移量:0x092C，初值:0x00000002，宽度:32
 寄存器说明: 数据输出的水线寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_threshold : 3;  /* bit[0-2] : afbce数据输出的水线寄存器 */
        unsigned int  reserved        : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_WCH_AFBCE_THRESHOLD_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_THRESHOLD_afbce_threshold_START  (0)
#define SOC_DSS_WCH_AFBCE_THRESHOLD_afbce_threshold_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_UNION
 结构说明  : AFBCE_SCRAMBLE_MODE 寄存器结构定义。地址偏移量:0x0930，初值:0x00000000，宽度:32
 寄存器说明: 地址交织模式寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_scramble_mode : 2;  /* bit[0-1] : afbce地址交织寄存器
                                                              2'b00 无scramble 兼容之前的功能
                                                              2'b01 scramble mode 1
                                                              2'b10 scramble mode 2
                                                              2'b11 reserved */
        unsigned int  reserved            : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_afbce_scramble_mode_START  (0)
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_afbce_scramble_mode_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_WCH_REG_DEFAULT_UNION
 结构说明  : REG_DEFAULT 寄存器结构定义。地址偏移量:0x0A00，初值:0x00000000，宽度:32
 寄存器说明: 模块影子寄存器恢复到默认值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   :  */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_WCH_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_WCH_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_WCH_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_wch_interface.h */
