/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_rch_g_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:19
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_RCH_G.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_RCH_G_INTERFACE_H__
#define __SOC_DSS_RCH_G_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_RCH_G
 ****************************************************************************/
/* 寄存器说明：RDMA读入图像或WDMA写出图像左上角相对于buffer的水平偏移
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_OFT_X0_UNION */
#define SOC_DSS_RCH_G_DMA_OFT_X0_ADDR(base)           ((base) + (0x0000))

/* 寄存器说明：RDMA读入图像或WDMA写出图像左上角相对于buffer的垂直偏移
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_OFT_Y0_UNION */
#define SOC_DSS_RCH_G_DMA_OFT_Y0_ADDR(base)           ((base) + (0x0004))

/* 寄存器说明：读入图像右下角相对于buffer的水平偏移
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_OFT_X1_UNION */
#define SOC_DSS_RCH_G_DMA_OFT_X1_ADDR(base)           ((base) + (0x0008))

/* 寄存器说明：读入图像右下角相对于buffer的垂直偏移
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_OFT_Y1_UNION */
#define SOC_DSS_RCH_G_DMA_OFT_Y1_ADDR(base)           ((base) + (0x000C))

/* 寄存器说明：RDMA的Mask左上角坐标
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_MASK0_UNION */
#define SOC_DSS_RCH_G_DMA_MASK0_ADDR(base)            ((base) + (0x0010))

/* 寄存器说明：RDMA的Mask右下角坐标
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_MASK1_UNION */
#define SOC_DSS_RCH_G_DMA_MASK1_ADDR(base)            ((base) + (0x0014))

/* 寄存器说明：Y平面RDMA垂直Stretch之后的高度-1
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_UNION */
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：RDMA控制
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_CTRL_UNION */
#define SOC_DSS_RCH_G_DMA_CTRL_ADDR(base)             ((base) + (0x001C))

/* 寄存器说明：tile格式地址交织使能
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_TILE_SCRAM_UNION */
#define SOC_DSS_RCH_G_DMA_TILE_SCRAM_ADDR(base)       ((base) + (0x0020))

/* 寄存器说明：1PULSE寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_PULSE_UNION */
#define SOC_DSS_RCH_G_DMA_PULSE_ADDR(base)            ((base) + (0x0028))

/* 寄存器说明：保留
   位域定义UNION结构:  SOC_DSS_RCH_G_RWCH_CFG0_UNION */
#define SOC_DSS_RCH_G_RWCH_CFG0_ADDR(base)            ((base) + (0x0030))

/* 寄存器说明：RDMA读入图像或WDMA写出图像的Y平面Data读地址寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_DATA_ADDR0_UNION */
#define SOC_DSS_RCH_G_DMA_DATA_ADDR0_ADDR(base)       ((base) + (0x0060))

/* 寄存器说明：RDMA读入图像或WDMA写出图像的原图Y行地址偏移
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_STRIDE0_UNION */
#define SOC_DSS_RCH_G_DMA_STRIDE0_ADDR(base)          ((base) + (0x0064))

/* 寄存器说明：Y平面跳行之后的对应的stride
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_UNION */
#define SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_ADDR(base)  ((base) + (0x0068))

/* 寄存器说明：RDMA或WDMA输出图像Y平面包含128bit数据的个数
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_DATA_NUM0_UNION */
#define SOC_DSS_RCH_G_DMA_DATA_NUM0_ADDR(base)        ((base) + (0x006C))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_TEST0_UNION */
#define SOC_DSS_RCH_G_DMA_TEST0_ADDR(base)            ((base) + (0x0070))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_TEST1_UNION */
#define SOC_DSS_RCH_G_DMA_TEST1_ADDR(base)            ((base) + (0x0074))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_TEST3_UNION */
#define SOC_DSS_RCH_G_DMA_TEST3_ADDR(base)            ((base) + (0x0078))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_TEST4_UNION */
#define SOC_DSS_RCH_G_DMA_TEST4_ADDR(base)            ((base) + (0x007C))

/* 寄存器说明：状态上报寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_STATUS_Y_UNION */
#define SOC_DSS_RCH_G_DMA_STATUS_Y_ADDR(base)         ((base) + (0x0080))

/* 寄存器说明：读寄存器选择
   位域定义UNION结构:  SOC_DSS_RCH_G_CH_RD_SHADOW_UNION */
#define SOC_DSS_RCH_G_CH_RD_SHADOW_ADDR(base)         ((base) + (0x00D0))

/* 寄存器说明：通道控制寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_CH_CTL_UNION */
#define SOC_DSS_RCH_G_CH_CTL_ADDR(base)               ((base) + (0x00D4))

/* 寄存器说明：通道安全使能
   位域定义UNION结构:  SOC_DSS_RCH_G_CH_SECU_EN_UNION */
#define SOC_DSS_RCH_G_CH_SECU_EN_ADDR(base)           ((base) + (0x00D8))

/* 寄存器说明：软件清场寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_CH_SW_END_REQ_UNION */
#define SOC_DSS_RCH_G_CH_SW_END_REQ_ADDR(base)        ((base) + (0x00DC))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_RCH_G_CH_CLK_SEL_UNION */
#define SOC_DSS_RCH_G_CH_CLK_SEL_ADDR(base)           ((base) + (0x00E0))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_RCH_G_CH_CLK_EN_UNION */
#define SOC_DSS_RCH_G_CH_CLK_EN_ADDR(base)            ((base) + (0x00E4))

/* 寄存器说明：图象大小
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_DISP_SIZE_UNION */
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_ADDR(base)        ((base) + (0x0100))

/* 寄存器说明：输入输出像素数
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_PIX_IN_NUM_UNION */
#define SOC_DSS_RCH_G_DFC_PIX_IN_NUM_ADDR(base)       ((base) + (0x0104))

/* 寄存器说明：透明度数据
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_GLB_ALPHA_UNION */
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_ADDR(base)        ((base) + (0x0108))

/* 寄存器说明：显示格式
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_DISP_FMT_UNION */
#define SOC_DSS_RCH_G_DFC_DISP_FMT_ADDR(base)         ((base) + (0x010C))

/* 寄存器说明：水平裁剪区域
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_UNION */
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_ADDR(base)     ((base) + (0x0110))

/* 寄存器说明：垂直裁剪区域
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_UNION */
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_ADDR(base)     ((base) + (0x0114))

/* 寄存器说明：图像剪裁使能
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_UNION */
#define SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_ADDR(base)      ((base) + (0x0118))

/* 寄存器说明：时钟门控模式
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_ICG_MODULE_UNION */
#define SOC_DSS_RCH_G_DFC_ICG_MODULE_ADDR(base)       ((base) + (0x011C))

/* 寄存器说明：抖动处理使能
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_DITHER_ENABLE_UNION */
#define SOC_DSS_RCH_G_DFC_DITHER_ENABLE_ADDR(base)    ((base) + (0x0120))

/* 寄存器说明：增补像素控制
   位域定义UNION结构:  SOC_DSS_RCH_G_DFC_PADDING_CTL_UNION */
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_ADDR(base)      ((base) + (0x0124))

/* 寄存器说明：水平丢点缩放使能
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_EN_HSCL_STR_UNION */
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_ADDR(base)      ((base) + (0x0200))

/* 寄存器说明：垂直丢点缩放使能
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_EN_VSCL_STR_UNION */
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_ADDR(base)      ((base) + (0x0204))

/* 寄存器说明：水平和垂直滤波以及video处理模式配置
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_H_V_ORDER_UNION */
#define SOC_DSS_RCH_G_SCF_H_V_ORDER_ADDR(base)        ((base) + (0x0208))

/* 寄存器说明：通道时钟门控
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_CH_CORE_GT_UNION */
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_ADDR(base)       ((base) + (0x020C))

/* 寄存器说明：输入宽高
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_UNION */
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0210))

/* 寄存器说明：输出宽高
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_UNION */
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0214))

/* 寄存器说明：缩放MEM低功耗控制
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_UNION */
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_ADDR(base)    ((base) + (0x0218))

/* 寄存器说明：水平缩放使能信号
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_EN_HSCL_UNION */
#define SOC_DSS_RCH_G_SCF_EN_HSCL_ADDR(base)          ((base) + (0x021C))

/* 寄存器说明：垂直缩放使能信号
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_EN_VSCL_UNION */
#define SOC_DSS_RCH_G_SCF_EN_VSCL_ADDR(base)          ((base) + (0x0220))

/* 寄存器说明：水平初始相位
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_ACC_HSCL_UNION */
#define SOC_DSS_RCH_G_SCF_ACC_HSCL_ADDR(base)         ((base) + (0x0224))

/* 寄存器说明：通道1水平相位的相对偏移量
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_ACC_HSCL1_UNION */
#define SOC_DSS_RCH_G_SCF_ACC_HSCL1_ADDR(base)        ((base) + (0x0228))

/* 寄存器说明：水平缩放比例
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_INC_HSCL_UNION */
#define SOC_DSS_RCH_G_SCF_INC_HSCL_ADDR(base)         ((base) + (0x0234))

/* 寄存器说明：垂直初始相位
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_ACC_VSCL_UNION */
#define SOC_DSS_RCH_G_SCF_ACC_VSCL_ADDR(base)         ((base) + (0x0238))

/* 寄存器说明：通道1垂直相位的相对偏移量
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_ACC_VSCL1_UNION */
#define SOC_DSS_RCH_G_SCF_ACC_VSCL1_ADDR(base)        ((base) + (0x023C))

/* 寄存器说明：垂直缩放比例
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_INC_VSCL_UNION */
#define SOC_DSS_RCH_G_SCF_INC_VSCL_ADDR(base)         ((base) + (0x0248))

/* 寄存器说明：软复位寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_EN_NONLINEAR_UNION */
#define SOC_DSS_RCH_G_SCF_EN_NONLINEAR_ADDR(base)     ((base) + (0x024C))

/* 寄存器说明：过冲处理使能信号
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_EN_MMP_UNION */
#define SOC_DSS_RCH_G_SCF_EN_MMP_ADDR(base)           ((base) + (0x027C))

/* 寄存器说明：水平滤波器的内部状态寄存器0
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_DB_H0_UNION */
#define SOC_DSS_RCH_G_SCF_DB_H0_ADDR(base)            ((base) + (0x0280))

/* 寄存器说明：水平滤波器的内部状态寄存器1
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_DB_H1_UNION */
#define SOC_DSS_RCH_G_SCF_DB_H1_ADDR(base)            ((base) + (0x0284))

/* 寄存器说明：垂直滤波器的内部状态寄存器0
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_DB_V0_UNION */
#define SOC_DSS_RCH_G_SCF_DB_V0_ADDR(base)            ((base) + (0x0288))

/* 寄存器说明：垂直滤波器的内部状态寄存器1
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_DB_V1_UNION */
#define SOC_DSS_RCH_G_SCF_DB_V1_ADDR(base)            ((base) + (0x028C))

/* 寄存器说明：LINE BUFFER POWER MANAGER
   位域定义UNION结构:  SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_UNION */
#define SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_ADDR(base)      ((base) + (0x0290))

/* 寄存器说明：图象大小
   位域定义UNION结构:  SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_UNION */
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_ADDR(base)  ((base) + (0x03A0))

/* 寄存器说明：水平裁剪区域
   位域定义UNION结构:  SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_UNION */
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_ADDR(base)    ((base) + (0x03B0))

/* 寄存器说明：垂直裁剪区域
   位域定义UNION结构:  SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_UNION */
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_ADDR(base)    ((base) + (0x03B4))

/* 寄存器说明：图像剪裁使能
   位域定义UNION结构:  SOC_DSS_RCH_G_POST_CLIP_EN_UNION */
#define SOC_DSS_RCH_G_POST_CLIP_EN_ADDR(base)         ((base) + (0x03B8))

/* 寄存器说明：调试选择寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_CH_DEBUG_SEL_UNION */
#define SOC_DSS_RCH_G_CH_DEBUG_SEL_ADDR(base)         ((base) + (0x600))

/* 寄存器说明：DMA_BUF控制寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CTRL_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_ADDR(base)         ((base) + (0x0800))

/* 寄存器说明：DMA_BUF 调试选择寄存器。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_ADDR(base)      ((base) + (0x0804))

/* 寄存器说明：DMA_BUF 调试启动寄存器。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_START_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_START_ADDR(base)    ((base) + (0x0808))

/* 寄存器说明：DMA_BUF 地址寄存器。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_ADDR(base)     ((base) + (0x080C))

/* 寄存器说明：DMA_BUF 读数据端口寄存器0。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_ADDR(base)   ((base) + (0x0810))

/* 寄存器说明：DMA_BUF 读数据端口寄存器1。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_ADDR(base)   ((base) + (0x814))

/* 寄存器说明：DMA_BUF 读数据端口寄存器2。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_ADDR(base)   ((base) + (0x818))

/* 寄存器说明：DMA_BUF 读数据端口寄存器3。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_ADDR(base)   ((base) + (0x81C))

/* 寄存器说明：DMA_BUF 写数据端口寄存器0。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_ADDR(base)   ((base) + (0x820))

/* 寄存器说明：DMA_BUF 写数据端口寄存器1。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_ADDR(base)   ((base) + (0x824))

/* 寄存器说明：DMA_BUF 写数据端口寄存器2。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_ADDR(base)   ((base) + (0x828))

/* 寄存器说明：DMA_BUF 写数据端口寄存器3。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_ADDR(base)   ((base) + (0x82C))

/* 寄存器说明：MMU TLB 读数据端口寄存器0。
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_REQ_END_UNION */
#define SOC_DSS_RCH_G_DMA_REQ_END_ADDR(base)          ((base) + (0x830))

/* 寄存器说明：DMA_BUF 调试寄存器
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_DBGCFG_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_DBGCFG_ADDR(base)       ((base) + (0x834))

/* 寄存器说明：DMA_BUF调试只读寄存器0
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_DBG0_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_DBG0_ADDR(base)         ((base) + (0x838))

/* 寄存器说明：DMA_BUF调试只读寄存器1
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_DBG1_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_DBG1_ADDR(base)         ((base) + (0x83C))

/* 寄存器说明：DMA_BUF调试只读寄存器0
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_DBG2_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_DBG2_ADDR(base)         ((base) + (0x840))

/* 寄存器说明：DMA_BUF调试只读寄存器1
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_DBG3_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_DBG3_ADDR(base)         ((base) + (0x844))

/* 寄存器说明：DMA_BUF调试只读寄存器0
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_DBG4_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_DBG4_ADDR(base)         ((base) + (0x848))

/* 寄存器说明：DMA_BUF调试只读寄存器1
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_DBG5_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_DBG5_ADDR(base)         ((base) + (0x84C))

/* 寄存器说明：图象大小
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_SIZE_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_ADDR(base)         ((base) + (0x850))

/* 寄存器说明：DMA_BUF SRAM控制寄存器（TP）
   位域定义UNION结构:  SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_UNION */
#define SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_ADDR(base)     ((base) + (0x0854))

/* 寄存器说明：压缩Header起始地址低位
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_UNION */
#define SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_ADDR(base) ((base) + (0x0900))

/* 寄存器说明：压缩图像宽度
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_UNION */
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_ADDR(base) ((base) + (0x0904))

/* 寄存器说明：压缩图像高度
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_UNION */
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_ADDR(base) ((base) + (0x090C))

/* 寄存器说明：压缩图像格式
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_UNION */
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_ADDR(base)    ((base) + (0x0910))

/* 寄存器说明：AFBCD控制
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_CTL_UNION */
#define SOC_DSS_RCH_G_AFBCD_CTL_ADDR(base)            ((base) + (0x0914))

/* 寄存器说明：STRETCH PARAMETER
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_STR_UNION */
#define SOC_DSS_RCH_G_AFBCD_STR_ADDR(base)            ((base) + (0x0918))

/* 寄存器说明：TOP AND BOTTOM LINT NUMBER BE CROPPED
   位域定义UNION结构:  SOC_DSS_RCH_G_LINE_CROP_UNION */
#define SOC_DSS_RCH_G_LINE_CROP_ADDR(base)            ((base) + (0x091C))

/* 寄存器说明：INPUT HEADER STRIDE
   位域定义UNION结构:  SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_UNION */
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_ADDR(base)  ((base) + (0x0920))

/* 寄存器说明：output payload stride
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_UNION */
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_ADDR(base) ((base) + (0x0924))

/* 寄存器说明：mm buffer base 0
   位域定义UNION结构:  SOC_DSS_RCH_G_MM_BASE_0_UNION */
#define SOC_DSS_RCH_G_MM_BASE_0_ADDR(base)            ((base) + (0x0928))

/* 寄存器说明：mm buffer base 1
   位域定义UNION结构:  SOC_DSS_RCH_G_MM_BASE_1_UNION */
#define SOC_DSS_RCH_G_MM_BASE_1_ADDR(base)            ((base) + (0x092C))

/* 寄存器说明：input payload point
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_UNION */
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_ADDR(base) ((base) + (0x0930))

/* 寄存器说明：input height
   位域定义UNION结构:  SOC_DSS_RCH_G_HEIGHT_BF_STR_UNION */
#define SOC_DSS_RCH_G_HEIGHT_BF_STR_ADDR(base)        ((base) + (0x0934))

/* 寄存器说明：OUSTANDING CFG
   位域定义UNION结构:  SOC_DSS_RCH_G_OS_CFG_UNION */
#define SOC_DSS_RCH_G_OS_CFG_ADDR(base)               ((base) + (0x0938))

/* 寄存器说明：AFBCE SRAM控制寄存器（SP）
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_MEM_CTRL_UNION */
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_ADDR(base)       ((base) + (0x093C))

/* 寄存器说明：SCRAMBLE模式选择
   位域定义UNION结构:  SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_UNION */
#define SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_ADDR(base)  ((base) + (0x0940))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_RCH_G_REG_DEFAULT_UNION */
#define SOC_DSS_RCH_G_REG_DEFAULT_ADDR(base)          ((base) + (0x0A00))





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
                     (1/1) reg_RCH_G
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_OFT_X0_UNION
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
} SOC_DSS_RCH_G_DMA_OFT_X0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_OFT_X0_dma_oft_x0_START  (0)
#define SOC_DSS_RCH_G_DMA_OFT_X0_dma_oft_x0_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_OFT_Y0_UNION
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
} SOC_DSS_RCH_G_DMA_OFT_Y0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_OFT_Y0_dma_oft_y0_START  (0)
#define SOC_DSS_RCH_G_DMA_OFT_Y0_dma_oft_y0_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_OFT_X1_UNION
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
} SOC_DSS_RCH_G_DMA_OFT_X1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_OFT_X1_dma_oft_x1_START  (0)
#define SOC_DSS_RCH_G_DMA_OFT_X1_dma_oft_x1_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_OFT_Y1_UNION
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
} SOC_DSS_RCH_G_DMA_OFT_Y1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_OFT_Y1_dma_oft_y1_START  (0)
#define SOC_DSS_RCH_G_DMA_OFT_Y1_dma_oft_y1_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_MASK0_UNION
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
                                                       
                                                       约束1：配置的Mask区域需在图像内，即dma_mask_y0>dma_oft_y0, dma_mask_y1<dma_oft_y1
                                                       约束2：Mask区域可以做小，但不能做大
                                                       约束3：在semi planar 420/planar 420格式时，y分量的dma_oft_y0坐标必须为偶数，dma_oft_y1坐标必须为奇数。这样y1-y0+1为偶数。 */
        unsigned int  dma_mask_x0 : 12; /* bit[16-27]: RDMA的mask矩形区域左上角x坐标（相对于buffer的左上角，1代表128bit，即(0,0)坐标对应于buffer的左上角）
                                                       向大按128bit取整对齐.
                                                       旋转前原始图像的Mask区域左上角。
                                                       RDMA读入图像的Y平面的mask矩形区域的左上角在水平方向的像素坐标
                                                       注：
                                                       1、WDMA不关注此项
                                                       
                                                       约束1：配置的Mask区域需在图像内，即dma_mask_x0>dma_oft_x0, dma_mask_x1<dma_oft_x1
                                                       约束2：Mask区域可以做小，但不能做大
                                                       约束3：在planar 420和planar 422格式时，y分量的dma_mask_x0坐标必须为偶数，dma_mask_x1坐标必须为奇数。这样x1-x0+1为偶数。 */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_DMA_MASK0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_MASK0_dma_mask_y0_START  (0)
#define SOC_DSS_RCH_G_DMA_MASK0_dma_mask_y0_END    (15)
#define SOC_DSS_RCH_G_DMA_MASK0_dma_mask_x0_START  (16)
#define SOC_DSS_RCH_G_DMA_MASK0_dma_mask_x0_END    (27)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_MASK1_UNION
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
                                                       
                                                       约束1：配置的Mask区域需在图像内，即dma_mask_y0>dma_oft_y0, dma_mask_y1<dma_oft_y1
                                                       约束2：Mask区域可以做小，但不能做大
                                                       约束3：在semi planar 420/planar 420格式时，y分量的dma_oft_y0坐标必须为偶数，dma_oft_y1坐标必须为奇数。这样y1-y0+1为偶数。 */
        unsigned int  dma_mask_x1 : 12; /* bit[16-27]: RDMA的mask矩形区域右下角x坐标（相对于buffer的左上角，1代表128bit）
                                                       向小按128bit取整对齐.
                                                       旋转前原始图像的Mask区域右下角。
                                                       注：
                                                       1、WDMA不关注此项
                                                       
                                                       约束1：配置的Mask区域需在图像内，即dma_mask_x0>dma_oft_x0, dma_mask_x1<dma_oft_x1
                                                       约束2：Mask区域可以做小，但不能做大
                                                       约束3：在planar 420和planar 422格式时，y分量的dma_mask_x0坐标必须为偶数，dma_mask_x1坐标必须为奇数。这样x1-x0+1为偶数。 */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_DMA_MASK1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_MASK1_dma_mask_y1_START  (0)
#define SOC_DSS_RCH_G_DMA_MASK1_dma_mask_y1_END    (15)
#define SOC_DSS_RCH_G_DMA_MASK1_dma_mask_x1_START  (16)
#define SOC_DSS_RCH_G_DMA_MASK1_dma_mask_x1_END    (27)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_UNION
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
} SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_START  (0)
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_END    (12)
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_START    (13)
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_END      (18)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_CTRL_UNION
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
} SOC_DSS_RCH_G_DMA_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_CTRL_dma_page_8k_START          (0)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_page_8k_END            (0)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_tile_en_START          (1)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_tile_en_END            (1)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_pix_fmt_START          (3)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_pix_fmt_END            (7)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_va_en_START            (8)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_va_en_END              (8)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mirror_hrz_en_START    (9)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mirror_hrz_en_END      (9)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mirror_vrt_en_START    (10)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mirror_vrt_en_END      (10)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_rot_START              (11)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_rot_END                (11)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_stretch_en_START       (12)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_stretch_en_END         (12)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mask_en_START          (17)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mask_en_END            (17)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_4_START    (18)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_4_END      (18)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_3_START    (19)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_3_END      (19)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_2_START    (20)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_2_END      (20)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_1_START    (21)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_1_END      (21)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_cross_128_START        (23)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_cross_128_END          (23)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_tile_128byte_en_START  (24)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_tile_128byte_en_END    (24)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_TILE_SCRAM_UNION
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
} SOC_DSS_RCH_G_DMA_TILE_SCRAM_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TILE_SCRAM_dma_tile_scrambling_en_START  (0)
#define SOC_DSS_RCH_G_DMA_TILE_SCRAM_dma_tile_scrambling_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_PULSE_UNION
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
} SOC_DSS_RCH_G_DMA_PULSE_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_PULSE_dma_pulse_START  (0)
#define SOC_DSS_RCH_G_DMA_PULSE_dma_pulse_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_RWCH_CFG0_UNION
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
} SOC_DSS_RCH_G_RWCH_CFG0_UNION;
#endif
#define SOC_DSS_RCH_G_RWCH_CFG0_rwch_cfg0_START  (0)
#define SOC_DSS_RCH_G_RWCH_CFG0_rwch_cfg0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_DATA_ADDR0_UNION
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
} SOC_DSS_RCH_G_DMA_DATA_ADDR0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_DATA_ADDR0_dma_addr0_START  (0)
#define SOC_DSS_RCH_G_DMA_DATA_ADDR0_dma_addr0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_STRIDE0_UNION
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
} SOC_DSS_RCH_G_DMA_STRIDE0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_STRIDE0_dma_stride0_START            (0)
#define SOC_DSS_RCH_G_DMA_STRIDE0_dma_stride0_END              (12)
#define SOC_DSS_RCH_G_DMA_STRIDE0_dma_l2t_interleave_n0_START  (16)
#define SOC_DSS_RCH_G_DMA_STRIDE0_dma_l2t_interleave_n0_END    (19)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_UNION
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
} SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_dma_stretch_stride0_START  (0)
#define SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_dma_stretch_stride0_END    (18)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_DATA_NUM0_UNION
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
} SOC_DSS_RCH_G_DMA_DATA_NUM0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_DATA_NUM0_dma_data_num0_START  (0)
#define SOC_DSS_RCH_G_DMA_DATA_NUM0_dma_data_num0_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_TEST0_UNION
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
} SOC_DSS_RCH_G_DMA_TEST0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TEST0_dma_test0_y_START  (0)
#define SOC_DSS_RCH_G_DMA_TEST0_dma_test0_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_TEST1_UNION
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
} SOC_DSS_RCH_G_DMA_TEST1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TEST1_dma_test1_y_START  (0)
#define SOC_DSS_RCH_G_DMA_TEST1_dma_test1_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_TEST3_UNION
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
} SOC_DSS_RCH_G_DMA_TEST3_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TEST3_dma_test3_y_START  (0)
#define SOC_DSS_RCH_G_DMA_TEST3_dma_test3_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_TEST4_UNION
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
} SOC_DSS_RCH_G_DMA_TEST4_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TEST4_dma_test4_y_START  (0)
#define SOC_DSS_RCH_G_DMA_TEST4_dma_test4_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_STATUS_Y_UNION
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
} SOC_DSS_RCH_G_DMA_STATUS_Y_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_STATUS_Y_dma_status_y_START  (0)
#define SOC_DSS_RCH_G_DMA_STATUS_Y_dma_status_y_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_CH_RD_SHADOW_UNION
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
} SOC_DSS_RCH_G_CH_RD_SHADOW_UNION;
#endif
#define SOC_DSS_RCH_G_CH_RD_SHADOW_rwch_rd_shadow_START  (0)
#define SOC_DSS_RCH_G_CH_RD_SHADOW_rwch_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_CH_CTL_UNION
 结构说明  : CH_CTL 寄存器结构定义。地址偏移量:0x00D4，初值:0x0000F000，宽度:32
 寄存器说明: 通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_en          : 1;  /* bit[0]    : RCH或WCH使能 */
        unsigned int  ch_version_sel : 1;  /* bit[1]    : 0：K3V3原功能版本；
                                                          1：保留 */
        unsigned int  ch_afbcd_en    : 1;  /* bit[2]    : 0：关闭压缩功能
                                                          1：开启压缩功能 */
        unsigned int  ch_block_en    : 1;  /* bit[3]    : 0：frame模式；
                                                          1：block模式； */
        unsigned int  reserved_0     : 8;  /* bit[4-11] : 保留 */
        unsigned int  ch_frm_end_dly : 4;  /* bit[12-15]: 数据传完之后延迟若干拍出frame_end，该寄存器表示延迟的拍数 */
        unsigned int  ch_block_h     : 13; /* bit[16-28]: block模式下有效，表示当前block的高度 */
        unsigned int  reserved_1     : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_CH_CTL_UNION;
#endif
#define SOC_DSS_RCH_G_CH_CTL_ch_en_START           (0)
#define SOC_DSS_RCH_G_CH_CTL_ch_en_END             (0)
#define SOC_DSS_RCH_G_CH_CTL_ch_version_sel_START  (1)
#define SOC_DSS_RCH_G_CH_CTL_ch_version_sel_END    (1)
#define SOC_DSS_RCH_G_CH_CTL_ch_afbcd_en_START     (2)
#define SOC_DSS_RCH_G_CH_CTL_ch_afbcd_en_END       (2)
#define SOC_DSS_RCH_G_CH_CTL_ch_block_en_START     (3)
#define SOC_DSS_RCH_G_CH_CTL_ch_block_en_END       (3)
#define SOC_DSS_RCH_G_CH_CTL_ch_frm_end_dly_START  (12)
#define SOC_DSS_RCH_G_CH_CTL_ch_frm_end_dly_END    (15)
#define SOC_DSS_RCH_G_CH_CTL_ch_block_h_START      (16)
#define SOC_DSS_RCH_G_CH_CTL_ch_block_h_END        (28)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_CH_SECU_EN_UNION
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
} SOC_DSS_RCH_G_CH_SECU_EN_UNION;
#endif
#define SOC_DSS_RCH_G_CH_SECU_EN_ch_secu_en_START  (0)
#define SOC_DSS_RCH_G_CH_SECU_EN_ch_secu_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_CH_SW_END_REQ_UNION
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
} SOC_DSS_RCH_G_CH_SW_END_REQ_UNION;
#endif
#define SOC_DSS_RCH_G_CH_SW_END_REQ_ch_sw_end_req_START  (0)
#define SOC_DSS_RCH_G_CH_SW_END_REQ_ch_sw_end_req_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_CH_CLK_SEL_UNION
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
} SOC_DSS_RCH_G_CH_CLK_SEL_UNION;
#endif
#define SOC_DSS_RCH_G_CH_CLK_SEL_ch_clk_sel_START  (0)
#define SOC_DSS_RCH_G_CH_CLK_SEL_ch_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_CH_CLK_EN_UNION
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
} SOC_DSS_RCH_G_CH_CLK_EN_UNION;
#endif
#define SOC_DSS_RCH_G_CH_CLK_EN_ch_clk_en_START  (0)
#define SOC_DSS_RCH_G_CH_CLK_EN_ch_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_DISP_SIZE_UNION
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
} SOC_DSS_RCH_G_DFC_DISP_SIZE_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_dfc_size_vrt_START  (0)
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_dfc_size_vrt_END    (12)
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_dfc_size_hrz_START  (16)
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_dfc_size_hrz_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_PIX_IN_NUM_UNION
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
                                                         1:4pixel (RDMA输出数据每像素为16bit类型 即RGB565,XRGB1555,XRGB4444，YUV422) */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_DFC_PIX_IN_NUM_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_PIX_IN_NUM_dfc_pix_in_num_START  (0)
#define SOC_DSS_RCH_G_DFC_PIX_IN_NUM_dfc_pix_in_num_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_GLB_ALPHA_UNION
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
} SOC_DSS_RCH_G_DFC_GLB_ALPHA_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_dfc_glb_alpha1_START  (0)
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_dfc_glb_alpha1_END    (7)
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_dfc_glb_alpha0_START  (8)
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_dfc_glb_alpha0_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_DISP_FMT_UNION
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
                                                      00001:XRGB4444
                                                      00010:ARGB4444
                                                      00011:XRGB1555
                                                      00100:ARGB1555
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
} SOC_DSS_RCH_G_DFC_DISP_FMT_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_ax_swap_START  (0)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_ax_swap_END    (0)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_img_fmt_START  (1)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_img_fmt_END    (5)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_uv_swap_START  (6)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_uv_swap_END    (6)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_rb_swap_START  (7)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_rb_swap_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_UNION
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
} SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_dfc_right_clip_START  (0)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_dfc_right_clip_END    (5)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_dfc_left_clip_START   (16)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_dfc_left_clip_END     (21)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_UNION
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
} SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_dfc_bot_clip_START  (0)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_dfc_bot_clip_END    (5)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_dfc_top_clip_START  (16)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_dfc_top_clip_END    (21)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_UNION
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
} SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_START  (0)
#define SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_ICG_MODULE_UNION
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
} SOC_DSS_RCH_G_DFC_ICG_MODULE_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_ICG_MODULE_dfc_module_en_START  (0)
#define SOC_DSS_RCH_G_DFC_ICG_MODULE_dfc_module_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_DITHER_ENABLE_UNION
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
} SOC_DSS_RCH_G_DFC_DITHER_ENABLE_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_DITHER_ENABLE_dfc_dither_en_START  (0)
#define SOC_DSS_RCH_G_DFC_DITHER_ENABLE_dfc_dither_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DFC_PADDING_CTL_UNION
 结构说明  : DFC_PADDING_CTL 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 增补像素控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_left_pad       : 4;  /* bit[0-3]  : 左边界增补像素数 */
        unsigned int  reserved_0         : 4;  /* bit[4-7]  : 保留 */
        unsigned int  dfc_right_pad      : 4;  /* bit[8-11] : 右边界增补像素数 */
        unsigned int  reserved_1         : 4;  /* bit[12-15]: 保留 */
        unsigned int  dfc_top_pad        : 4;  /* bit[16-19]: 上边界增补像素数 */
        unsigned int  reserved_2         : 4;  /* bit[20-23]: 保留 */
        unsigned int  dfc_bot_pad        : 4;  /* bit[24-27]: 下边界增补像素数 */
        unsigned int  reserved_3         : 3;  /* bit[28-30]: 保留 */
        unsigned int  dfc_ctl_pad_enable : 1;  /* bit[31]   : 增补像素使能 */
    } reg;
} SOC_DSS_RCH_G_DFC_PADDING_CTL_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_left_pad_START        (0)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_left_pad_END          (3)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_right_pad_START       (8)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_right_pad_END         (11)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_top_pad_START         (16)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_top_pad_END           (19)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_bot_pad_START         (24)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_bot_pad_END           (27)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_ctl_pad_enable_START  (31)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_ctl_pad_enable_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_EN_HSCL_STR_UNION
 结构说明  : SCF_EN_HSCL_STR 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: 水平丢点缩放使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_hscl_str   : 1;  /* bit[0]   : 水平丢点缩放使能，仅当EN_HSCL有效时有效
                                                            0：水平滤波缩放
                                                            1：水平丢点缩放 */
        unsigned int  scf_en_hscl_str_a : 1;  /* bit[1]   : alpha水平丢点缩放使能，仅当EN_HSCL有效时有效
                                                            0：水平滤波缩放
                                                            1：水平丢点缩放 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_EN_HSCL_STR_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_scf_en_hscl_str_START    (0)
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_scf_en_hscl_str_END      (0)
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_scf_en_hscl_str_a_START  (1)
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_scf_en_hscl_str_a_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_EN_VSCL_STR_UNION
 结构说明  : SCF_EN_VSCL_STR 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: 垂直丢点缩放使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_vscl_str   : 1;  /* bit[0]   : 垂直丢点缩放使能，仅当EN_VSCL有效时有效
                                                            0：垂直滤波缩放
                                                            1：垂直丢点缩放
                                                            如果考虑节省带宽，可在RDMA模块作垂直方向的整数倍丢点缩小 */
        unsigned int  scf_en_vscl_str_a : 1;  /* bit[1]   : alpha垂直丢点缩放使能，仅当EN_VSCL有效时有效
                                                            0：垂直滤波缩放
                                                            1：垂直丢点缩放
                                                            如果考虑节省带宽，可在RDMA模块作垂直方向的整数倍丢点缩小 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_EN_VSCL_STR_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_scf_en_vscl_str_START    (0)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_scf_en_vscl_str_END      (0)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_scf_en_vscl_str_a_START  (1)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_scf_en_vscl_str_a_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_H_V_ORDER_UNION
 结构说明  : SCF_H_V_ORDER 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: 水平和垂直滤波以及video处理模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_h_v_order : 1;  /* bit[0]   : 水平和垂直滤波的顺序
                                                        0：水平先做
                                                        1：水平后做 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_H_V_ORDER_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_H_V_ORDER_scf_h_v_order_START  (0)
#define SOC_DSS_RCH_G_SCF_H_V_ORDER_scf_h_v_order_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_CH_CORE_GT_UNION
 结构说明  : SCF_CH_CORE_GT 寄存器结构定义。地址偏移量:0x020C，初值:0x00000000，宽度:32
 寄存器说明: 通道时钟门控
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_a_core_gt : 1;  /* bit[0]   : 通道alpha单独门控使能：
                                                        0：表示在通道alpha不存在或不工作时，可以关闭通道alpha相关逻辑时钟；
                                                        1：通道alpha使能，时钟不可以关闭 */
        unsigned int  scf_r_core_gt : 1;  /* bit[1]   : 通道R或Y单独门控使能：
                                                        0：表示在通道R或Y不存在或不工作时，可以关闭通道R或Y相关逻辑时钟；
                                                        1：通道R或Y使能，时钟不可以关闭 */
        unsigned int  scf_g_core_gt : 1;  /* bit[2]   : 通道G或U单独门控使能：
                                                        0：表示在通道G或U不存在或不工作时，可以关闭通道G或U相关逻辑时钟；
                                                        1：通道G或U使能，时钟不可以关闭 */
        unsigned int  scf_b_core_gt : 1;  /* bit[3]   : 通道B或V单独门控使能：
                                                        0：表示在通道B或V不存在或不工作时，可以关闭通道B或V相关逻辑时钟；
                                                        1：通道B或V使能，时钟不可以关闭 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_CH_CORE_GT_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_a_core_gt_START  (0)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_a_core_gt_END    (0)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_r_core_gt_START  (1)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_r_core_gt_END    (1)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_g_core_gt_START  (2)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_g_core_gt_END    (2)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_b_core_gt_START  (3)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_b_core_gt_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_UNION
 结构说明  : SCF_INPUT_WIDTH_HEIGHT 寄存器结构定义。地址偏移量:0x0210，初值:0x00000000，宽度:32
 寄存器说明: 输入宽高
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_input_height : 13; /* bit[0-12] : 实际输入高度 - 1 */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: 保留 */
        unsigned int  scf_input_width  : 13; /* bit[16-28]: 实际输入宽度 - 1 */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_START  (0)
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_END    (12)
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_START   (16)
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_END     (28)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_UNION
 结构说明  : SCF_OUTPUT_WIDTH_HEIGHT 寄存器结构定义。地址偏移量:0x0214，初值:0x00000000，宽度:32
 寄存器说明: 输出宽高
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_output_height : 13; /* bit[0-12] : 实际输出高度 - 1 */
        unsigned int  reserved_0        : 3;  /* bit[13-15]: 保留 */
        unsigned int  scf_output_width  : 13; /* bit[16-28]: 实际输出宽度 - 1; */
        unsigned int  reserved_1        : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_START  (0)
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_END    (12)
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_START   (16)
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_END     (28)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_UNION
 结构说明  : SCF_COEF_MEM_CTRL 寄存器结构定义。地址偏移量:0x0218，初值:0x00000000，宽度:32
 寄存器说明: 缩放MEM低功耗控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_hcoef_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器，水平滤波系数LUT软件配置：
                                                             [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                             [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                             [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                             [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  scf_vcoef_mem_ctrl : 4;  /* bit[4-7] : 调试用寄存器，垂直滤波系数LUT软件配置：
                                                             [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                             [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                             [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                             [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved           : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_START  (0)
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_END    (3)
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_START  (4)
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_EN_HSCL_UNION
 结构说明  : SCF_EN_HSCL 寄存器结构定义。地址偏移量:0x021C，初值:0x00000000，宽度:32
 寄存器说明: 水平缩放使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_hscl_en : 1;  /* bit[0]   : 水平缩放使能信号 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_EN_HSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_HSCL_scf_en_hscl_en_START  (0)
#define SOC_DSS_RCH_G_SCF_EN_HSCL_scf_en_hscl_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_EN_VSCL_UNION
 结构说明  : SCF_EN_VSCL 寄存器结构定义。地址偏移量:0x0220，初值:0x00000000，宽度:32
 寄存器说明: 垂直缩放使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_vscl_en    : 1;  /* bit[0]   : 垂直缩放使能信号 */
        unsigned int  scf_out_buffer_en : 1;  /* bit[1]   : 当垂直方向的输出图像高度小于等于输入图像高度时，使用scf的行buffer作输出缓存使能配置寄存器：
                                                            1.使用行buffer作输出缓存；
                                                            0.不使用行buffer作输出缓存 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_EN_VSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_VSCL_scf_en_vscl_en_START     (0)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_scf_en_vscl_en_END       (0)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_scf_out_buffer_en_START  (1)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_scf_out_buffer_en_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_ACC_HSCL_UNION
 结构说明  : SCF_ACC_HSCL 寄存器结构定义。地址偏移量:0x0224，初值:0x00000000，宽度:32
 寄存器说明: 水平初始相位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_hscl : 30; /* bit[0-29] : 水平初始相位，决定水平SC从什么位置开始做缩放。
                                                        VSCF：其中[17:0]位为小数部分，[29:18]位为整数部分。
                                                        GSCF：其中[17:2]位为小数部分，[29:18]位为整数部分,[1:0]位保留。 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_ACC_HSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_ACC_HSCL_scf_acc_hscl_START  (0)
#define SOC_DSS_RCH_G_SCF_ACC_HSCL_scf_acc_hscl_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_ACC_HSCL1_UNION
 结构说明  : SCF_ACC_HSCL1 寄存器结构定义。地址偏移量:0x0228，初值:0x00000000，宽度:32
 寄存器说明: 通道1水平相位的相对偏移量
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_hscl1 : 19; /* bit[0-18] : 通道1水平相位的相对偏移量，相对于ACC_HSCL； */
        unsigned int  reserved      : 13; /* bit[19-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_ACC_HSCL1_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_ACC_HSCL1_scf_acc_hscl1_START  (0)
#define SOC_DSS_RCH_G_SCF_ACC_HSCL1_scf_acc_hscl1_END    (18)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_INC_HSCL_UNION
 结构说明  : SCF_INC_HSCL 寄存器结构定义。地址偏移量:0x0234，初值:0x00005000，宽度:32
 寄存器说明: 水平缩放比例
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_inc_hscl : 24; /* bit[0-23] : 水平缩放比例，计算公式为
                                                        hinc = (input_width*262144-acc_hscl)/(output_width)
                                                        其中input_width 和output_width分别为输入图像的宽度和输出图像宽度的寄存器配置值，注意，因为寄存器的配置值比实际的图像小1， 例如如果输入图像宽度是1920，那么input_width的寄存器配置为1919，acc_hscl是SCF配置的寄存器值“水平初始相位”
                                                        
                                                        hinc的低18比特为ratio的小数部分，高6比特为整数部分。整数部分6比特，支持64倍以下（不含64倍）的缩小。放大的倍数，原理上只受18比特的小数部分的限制，可达2的18次方；实际上受到宽度寄存器的限制，最多放大到8X1024. */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_INC_HSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_INC_HSCL_scf_inc_hscl_START  (0)
#define SOC_DSS_RCH_G_SCF_INC_HSCL_scf_inc_hscl_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_ACC_VSCL_UNION
 结构说明  : SCF_ACC_VSCL 寄存器结构定义。地址偏移量:0x0238，初值:0x00000000，宽度:32
 寄存器说明: 垂直初始相位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_vscl : 30; /* bit[0-29] : 垂直初始相位，决定垂直SC从什么位置开始做缩放，其中低18位为小数部分，高12位为整数部分。 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_ACC_VSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_ACC_VSCL_scf_acc_vscl_START  (0)
#define SOC_DSS_RCH_G_SCF_ACC_VSCL_scf_acc_vscl_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_ACC_VSCL1_UNION
 结构说明  : SCF_ACC_VSCL1 寄存器结构定义。地址偏移量:0x023C，初值:0x00000000，宽度:32
 寄存器说明: 通道1垂直相位的相对偏移量
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_vscl1 : 19; /* bit[0-18] : 通道1垂直相位的相对偏移量，相对于ACC_VSCL； */
        unsigned int  reserved      : 13; /* bit[19-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_ACC_VSCL1_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_ACC_VSCL1_scf_acc_vscl1_START  (0)
#define SOC_DSS_RCH_G_SCF_ACC_VSCL1_scf_acc_vscl1_END    (18)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_INC_VSCL_UNION
 结构说明  : SCF_INC_VSCL 寄存器结构定义。地址偏移量:0x0248，初值:0x00005000，宽度:32
 寄存器说明: 垂直缩放比例
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_inc_vscl : 24; /* bit[0-23] : 垂直缩放比例，计算公式为
                                                        INPUT_HEIGHT*262144/OUTPUT_HEIGHT
                                                        软件计算，配置该寄存器 这部分作废
                                                        
                                                        约束更新： 
                                                        inc_vscl的计算公式更新为
                                                         inc_vscl=floor( (262144*(intput_height_reg)+131072-acc_vscl)/(output_height_reg))
                                                        寄存器配置值output_height为实际输出高度-1
                                                        寄存器配置值input_height为实际输入高度-1
                                                        floor()为向下取整
                                                        acc_vscl是SCF配置的寄存器值“垂直初始相位” */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_INC_VSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_INC_VSCL_scf_inc_vscl_START  (0)
#define SOC_DSS_RCH_G_SCF_INC_VSCL_scf_inc_vscl_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_EN_NONLINEAR_UNION
 结构说明  : SCF_EN_NONLINEAR 寄存器结构定义。地址偏移量:0x024C，初值:0x00000000，宽度:32
 寄存器说明: 软复位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_sw_rst : 1;  /* bit[0]   : scf模块软复位配置寄存器，1有效 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_EN_NONLINEAR_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_NONLINEAR_scf_sw_rst_START  (0)
#define SOC_DSS_RCH_G_SCF_EN_NONLINEAR_scf_sw_rst_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_EN_MMP_UNION
 结构说明  : SCF_EN_MMP 寄存器结构定义。地址偏移量:0x027C，初值:0x00000001，宽度:32
 寄存器说明: 过冲处理使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_mmp : 1;  /* bit[0]   : 过冲处理使能信号，1表示使能，0表示不使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_EN_MMP_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_MMP_scf_en_mmp_START  (0)
#define SOC_DSS_RCH_G_SCF_EN_MMP_scf_en_mmp_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_DB_H0_UNION
 结构说明  : SCF_DB_H0 寄存器结构定义。地址偏移量:0x0280，初值:0x00000000，宽度:32
 寄存器说明: 水平滤波器的内部状态寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_h0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_RCH_G_SCF_DB_H0_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_DB_H0_scf_debug_h0_START  (0)
#define SOC_DSS_RCH_G_SCF_DB_H0_scf_debug_h0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_DB_H1_UNION
 结构说明  : SCF_DB_H1 寄存器结构定义。地址偏移量:0x0284，初值:0x00000000，宽度:32
 寄存器说明: 水平滤波器的内部状态寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_h1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_RCH_G_SCF_DB_H1_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_DB_H1_scf_debug_h1_START  (0)
#define SOC_DSS_RCH_G_SCF_DB_H1_scf_debug_h1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_DB_V0_UNION
 结构说明  : SCF_DB_V0 寄存器结构定义。地址偏移量:0x0288，初值:0x00000000，宽度:32
 寄存器说明: 垂直滤波器的内部状态寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_v0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_RCH_G_SCF_DB_V0_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_DB_V0_scf_debug_v0_START  (0)
#define SOC_DSS_RCH_G_SCF_DB_V0_scf_debug_v0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_DB_V1_UNION
 结构说明  : SCF_DB_V1 寄存器结构定义。地址偏移量:0x028C，初值:0x00000000，宽度:32
 寄存器说明: 垂直滤波器的内部状态寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_v1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_RCH_G_SCF_DB_V1_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_DB_V1_scf_debug_v1_START  (0)
#define SOC_DSS_RCH_G_SCF_DB_V1_scf_debug_v1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_UNION
 结构说明  : SCF_LB_MEM_CTRL 寄存器结构定义。地址偏移量:0x0290，初值:0x00000000，宽度:32
 寄存器说明: LINE BUFFER POWER MANAGER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_lb_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器，line buffer memory低功耗配置：
                                                          [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                          [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                          [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                          [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_START  (0)
#define SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_UNION
 结构说明  : POST_CLIP_DISP_SIZE 寄存器结构定义。地址偏移量:0x03A0，初值:0x00000000，宽度:32
 寄存器说明: 图象大小
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  post_clip_size_vrt : 13; /* bit[0-12] : 输入DFC的图像的垂直高度-1 */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: 保留 */
        unsigned int  post_clip_size_hrz : 13; /* bit[16-28]: 输入DFC的图像每行传输的像素数-1（由于是2pixel或者是4pxiel传输，所以SIZE_HRZ+1必须为2或者4的倍数） */
        unsigned int  reserved_1         : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_UNION;
#endif
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_post_clip_size_vrt_START  (0)
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_post_clip_size_vrt_END    (12)
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_post_clip_size_hrz_START  (16)
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_post_clip_size_hrz_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_UNION
 结构说明  : POST_CLIP_CTL_HRZ 寄存器结构定义。地址偏移量:0x03B0，初值:0x00000000，宽度:32
 寄存器说明: 水平裁剪区域
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  post_clip_right : 6;  /* bit[0-5]  : 图像右边界需CLIP掉的像素数（当dma_pix_fmt是32bpp类，支持0~3；16bpp类，支持0~7；8bpp，支持0~15） */
        unsigned int  reserved_0      : 10; /* bit[6-15] : 保留 */
        unsigned int  post_clip_left  : 6;  /* bit[16-21]: 图像左边界需CLIP掉的像素数（ROT不使能时，CLIP范围为0~15） */
        unsigned int  reserved_1      : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_UNION;
#endif
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_post_clip_right_START  (0)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_post_clip_right_END    (5)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_post_clip_left_START   (16)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_post_clip_left_END     (21)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_UNION
 结构说明  : POST_CLIP_CTL_VRZ 寄存器结构定义。地址偏移量:0x03B4，初值:0x00000000，宽度:32
 寄存器说明: 垂直裁剪区域
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  post_clip_bot : 6;  /* bit[0-5]  : 图像底边界需CLIP掉的像素数（ROT使能时，CLIP范围为0~15） */
        unsigned int  reserved_0    : 10; /* bit[6-15] : 保留 */
        unsigned int  post_clip_top : 6;  /* bit[16-21]: 图像顶边界需CLIP掉的像素数（ROT使能时，CLIP范围为0~15） */
        unsigned int  reserved_1    : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_UNION;
#endif
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_post_clip_bot_START  (0)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_post_clip_bot_END    (5)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_post_clip_top_START  (16)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_post_clip_top_END    (21)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_POST_CLIP_EN_UNION
 结构说明  : POST_CLIP_EN 寄存器结构定义。地址偏移量:0x03B8，初值:0x00000000，宽度:32
 寄存器说明: 图像剪裁使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  post_clip_enable : 1;  /* bit[0]   : 图像剪裁使能 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_POST_CLIP_EN_UNION;
#endif
#define SOC_DSS_RCH_G_POST_CLIP_EN_post_clip_enable_START  (0)
#define SOC_DSS_RCH_G_POST_CLIP_EN_post_clip_enable_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_CH_DEBUG_SEL_UNION
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
} SOC_DSS_RCH_G_CH_DEBUG_SEL_UNION;
#endif
#define SOC_DSS_RCH_G_CH_DEBUG_SEL_ch_debug_sel_START  (0)
#define SOC_DSS_RCH_G_CH_DEBUG_SEL_ch_debug_sel_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CTRL_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_os_cfg_START     (0)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_os_cfg_END       (5)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_qos_mask_START   (8)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_qos_mask_END     (8)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_cont_mask_START  (9)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_cont_mask_END    (9)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_l_e_mask_START   (10)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_l_e_mask_END     (10)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_START_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_START_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_START_dma_buf_cpu_start_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_START_dma_buf_cpu_start_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_END    (8)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_START    (31)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_REQ_END_UNION
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
} SOC_DSS_RCH_G_DMA_REQ_END_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_REQ_END_dma_req_end_START  (0)
#define SOC_DSS_RCH_G_DMA_REQ_END_dma_req_end_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_DBGCFG_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_DBGCFG_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBGCFG_dma_buf_dbgcfg_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBGCFG_dma_buf_dbgcfg_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_DBG0_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_DBG0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG0_dma_buf_dbg0_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG0_dma_buf_dbg0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_DBG1_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_DBG1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG1_dma_buf_dbg1_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG1_dma_buf_dbg1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_DBG2_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_DBG2_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG2_dma_buf_dbg2_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG2_dma_buf_dbg2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_DBG3_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_DBG3_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG3_dma_buf_dbg3_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG3_dma_buf_dbg3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_DBG4_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_DBG4_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG4_dma_buf_dbg4_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG4_dma_buf_dbg4_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_DBG5_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_DBG5_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG5_dma_buf_dbg5_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG5_dma_buf_dbg5_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_SIZE_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_SIZE_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_dma_buf_img_width_START   (0)
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_dma_buf_img_width_END     (12)
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_dma_buf_img_height_START  (16)
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_dma_buf_img_height_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_UNION
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
} SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_START  (0)
#define SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_UNION
 结构说明  : AFBCD_HREG_HDR_PTR_LO 寄存器结构定义。地址偏移量:0x0900，初值:0x00000000，宽度:32
 寄存器说明: 压缩Header起始地址低位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_hdr_ptr_lo : 32; /* bit[0-31]: 输入Header起始地址[31:0]，地址64Byte对齐 */
    } reg;
} SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_afbcd_hdr_ptr_lo_START  (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_afbcd_hdr_ptr_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_UNION
 结构说明  : AFBCD_HREG_PIC_WIDTH 寄存器结构定义。地址偏移量:0x0904，初值:0x0000000F，宽度:32
 寄存器说明: 压缩图像宽度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_pic_width : 16; /* bit[0-15] : 压缩图像宽度像素个数-1，压缩图像像素数必须是16整数倍 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_afbcd_pic_width_START  (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_afbcd_pic_width_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_UNION
 结构说明  : AFBCD_HREG_PIC_HEIGHT 寄存器结构定义。地址偏移量:0x090C，初值:0x0000000F，宽度:32
 寄存器说明: 压缩图像高度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_pic_height : 16; /* bit[0-15] : 压缩图像高度像素个数-1，压缩图像像素数必须是8整数倍(是stretch之后、crop之前的高度） */
        unsigned int  reserved         : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_afbcd_pic_height_START  (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_afbcd_pic_height_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_UNION
 结构说明  : AFBCD_HREG_FORMAT 寄存器结构定义。地址偏移量:0x0910，初值:0x00050001，宽度:32
 寄存器说明: 压缩图像格式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_block_split     : 1;  /* bit[0]    : block split mode
                                                                 1=enable, 0=disable */
        unsigned int  reserved_0            : 15; /* bit[1-15] : 保留 */
        unsigned int  reserved_1            : 5;  /* bit[16-20]: bit[20] reserved；
                                                                 bit[19:16] pixel format
                                                                 0x0: RGB565
                                                                 0x1: ARGB4444
                                                                 0x2: XRGB4444
                                                                 0x3: ARGB1555
                                                                 0x4: XRGB1555
                                                                 0x5: ARGB8888
                                                                 0x6: XRGB8888
                                                                 0x7: reserved
                                                                 0x8: YUYV packet, 只支持color transform=0，不支持color transform=1
                                                                 0x9: YUV420 Semi Planar HP，不支持
                                                                 0xA: YUV420 Planar HP，不支持
                                                                 0xB: YUV422 Semi Planar HP，不支持
                                                                 0xC: YUV422 Planar HP，不支持
                                                                 0xD: AYUV444，不支持
                                                                 0xE: UYVY Packet, 不支持
                                                                 others: reserved */
        unsigned int  afbcd_color_transform : 1;  /* bit[21]   : color transform, 1-enable, 0-disable，(单独提取出来) */
        unsigned int  reserved_2            : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_afbcd_block_split_START      (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_afbcd_block_split_END        (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_afbcd_color_transform_START  (21)
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_afbcd_color_transform_END    (21)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_CTL_UNION
 结构说明  : AFBCD_CTL 寄存器结构定义。地址偏移量:0x0914，初值:0x00000000，宽度:32
 寄存器说明: AFBCD控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 1;  /* bit[0-0] : 合并于ch_afbcd_en */
        unsigned int  reserved_1            : 1;  /* bit[1-1] : 合并于ch_afbcd_en */
        unsigned int  reserved_2            : 1;  /* bit[2-2] : 合并于dma_mirror_hrz_en */
        unsigned int  reserved_3            : 1;  /* bit[3-3] : 合并于dma_mirror_vrt_en */
        unsigned int  reserved_4            : 1;  /* bit[4-4] : 合并于dma_stretch_en */
        unsigned int  reserved_5            : 1;  /* bit[5-5] : 合并于ch_secu */
        unsigned int  afbcd_half_block_mode : 2;  /* bit[6-7] : decoeder order
                                                                2'b0:upper 8 line, then lower 8 line
                                                                2'b1:lower I line ,then upper 8 line
                                                                2'b2:upper 8 line only
                                                                2'b3:lower 8 line only */
        unsigned int  reserved_6            : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_RCH_G_AFBCD_CTL_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_CTL_afbcd_half_block_mode_START  (6)
#define SOC_DSS_RCH_G_AFBCD_CTL_afbcd_half_block_mode_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_STR_UNION
 结构说明  : AFBCD_STR 寄存器结构定义。地址偏移量:0x0918，初值:0x00000001，宽度:32
 寄存器说明: STRETCH PARAMETER
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_stretch_inc : 8;  /* bit[0-7]  : step (16行为单位）for stretch */
        unsigned int  afbcd_stretch_acc : 4;  /* bit[8-11] : init block line for strecth */
        unsigned int  reserved          : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_RCH_G_AFBCD_STR_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_STR_afbcd_stretch_inc_START  (0)
#define SOC_DSS_RCH_G_AFBCD_STR_afbcd_stretch_inc_END    (7)
#define SOC_DSS_RCH_G_AFBCD_STR_afbcd_stretch_acc_START  (8)
#define SOC_DSS_RCH_G_AFBCD_STR_afbcd_stretch_acc_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_LINE_CROP_UNION
 结构说明  : LINE_CROP 寄存器结构定义。地址偏移量:0x091C，初值:0x00000000，宽度:32
 寄存器说明: TOP AND BOTTOM LINT NUMBER BE CROPPED
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_bottom_crop_num : 4;  /* bit[0-3] : line number be cropped in the bottom after stretch and vertical mirror
                                                                0: 0 line
                                                                n: n line */
        unsigned int  afbcd_top_crop_num    : 4;  /* bit[4-7] : line number to be cropped in the top after stretch and vertical mirror
                                                                0: 0 line
                                                                n: n line */
        unsigned int  reserved              : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_RCH_G_LINE_CROP_UNION;
#endif
#define SOC_DSS_RCH_G_LINE_CROP_afbcd_bottom_crop_num_START  (0)
#define SOC_DSS_RCH_G_LINE_CROP_afbcd_bottom_crop_num_END    (3)
#define SOC_DSS_RCH_G_LINE_CROP_afbcd_top_crop_num_START     (4)
#define SOC_DSS_RCH_G_LINE_CROP_afbcd_top_crop_num_END       (7)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_UNION
 结构说明  : INPUT_HEADER_STRIDE 寄存器结构定义。地址偏移量:0x0920，初值:0x00000040，宽度:32
 寄存器说明: INPUT HEADER STRIDE
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_header_stride    : 14; /* bit[0-13] : can be used for decoding a sub picture of a full picture
                                                                  必须是64byte的倍数 */
        unsigned int  afbcd_header_start_pos : 2;  /* bit[14-15]: valid header in first burst
                                                                  2’b00：第1个开始有效
                                                                  2’b01：第2个开始有效
                                                                  2’b10：第3个开始有效
                                                                  2’b11：第4个开始有效 */
        unsigned int  reserved               : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_UNION;
#endif
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_afbcd_header_stride_START     (0)
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_afbcd_header_stride_END       (13)
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_afbcd_header_start_pos_START  (14)
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_afbcd_header_start_pos_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_UNION
 结构说明  : AFBCD_PAYLOAD_STRIDE 寄存器结构定义。地址偏移量:0x0924，初值:0x00000400，宽度:32
 寄存器说明: output payload stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_payload_stride : 20; /* bit[0-19] : payload的换行宽度，以byte为单位，
                                                                32比特格式的时候，1024Byte的整数倍；16比特格式的时候，512Byte的整数倍 */
        unsigned int  reserved             : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_afbcd_payload_stride_START  (0)
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_afbcd_payload_stride_END    (19)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_MM_BASE_0_UNION
 结构说明  : MM_BASE_0 寄存器结构定义。地址偏移量:0x0928，初值:0x00000000，宽度:32
 寄存器说明: mm buffer base 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_mm_base_0 : 32; /* bit[0-31]: base 0 address in MM buffer
                                                          必须是64byte的整数倍，必须小于（0x64000-8行图像数据量），且两个MM_BASE地址之间的存储空间要大于图像8行对应的数据大小。 */
    } reg;
} SOC_DSS_RCH_G_MM_BASE_0_UNION;
#endif
#define SOC_DSS_RCH_G_MM_BASE_0_afbcd_mm_base_0_START  (0)
#define SOC_DSS_RCH_G_MM_BASE_0_afbcd_mm_base_0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_MM_BASE_1_UNION
 结构说明  : MM_BASE_1 寄存器结构定义。地址偏移量:0x092C，初值:0x00000200，宽度:32
 寄存器说明: mm buffer base 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_mm_base_1 : 32; /* bit[0-31]: base 1 address in MM buffer
                                                          必须是64byte的整数倍，必须小于（0x64000-8行图像数据量），且两个MM_BASE地址之间的存储空间要大于图像8行对应的数据大小。 */
    } reg;
} SOC_DSS_RCH_G_MM_BASE_1_UNION;
#endif
#define SOC_DSS_RCH_G_MM_BASE_1_afbcd_mm_base_1_START  (0)
#define SOC_DSS_RCH_G_MM_BASE_1_afbcd_mm_base_1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_UNION
 结构说明  : AFBCD_PAYLOAD_POINTER 寄存器结构定义。地址偏移量:0x0930，初值:0x00000400，宽度:32
 寄存器说明: input payload point
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_payload_ptr : 32; /* bit[0-31]: 输入payload起始地址[31:0]，地址1K Byte对齐 */
    } reg;
} SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_afbcd_payload_ptr_START  (0)
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_afbcd_payload_ptr_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_HEIGHT_BF_STR_UNION
 结构说明  : HEIGHT_BF_STR 寄存器结构定义。地址偏移量:0x0934，初值:0x0000000F，宽度:32
 寄存器说明: input height
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_pic_height_bf_stretch : 16; /* bit[0-15] : 压缩图像高度像素个数-1，压缩图像像素数必须是16整数倍(是丢弃block行之前的高度）---新增加的 */
        unsigned int  reserved                    : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_HEIGHT_BF_STR_UNION;
#endif
#define SOC_DSS_RCH_G_HEIGHT_BF_STR_afbcd_pic_height_bf_stretch_START  (0)
#define SOC_DSS_RCH_G_HEIGHT_BF_STR_afbcd_pic_height_bf_stretch_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_OS_CFG_UNION
 结构说明  : OS_CFG 寄存器结构定义。地址偏移量:0x0938，初值:0x00000F57，宽度:32
 寄存器说明: OUSTANDING CFG
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_mmrd_os : 4;  /* bit[0-3]  : VBIF MM读接口的outstanding设置，其值+1为实际outstanding值，最大值0x7 */
        unsigned int  afbcd_mmwr_os : 4;  /* bit[4-7]  : VBIF MM写接口的outstanding设置，其值+1为实际outstanding值，最大值0x5 */
        unsigned int  afbcd_ddrr_os : 6;  /* bit[8-13] : VBIF DDR读接口的outstanding设置，其值+1为实际outstanding值，最大值0x1F */
        unsigned int  reserved      : 18; /* bit[14-31]:  */
    } reg;
} SOC_DSS_RCH_G_OS_CFG_UNION;
#endif
#define SOC_DSS_RCH_G_OS_CFG_afbcd_mmrd_os_START  (0)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_mmrd_os_END    (3)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_mmwr_os_START  (4)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_mmwr_os_END    (7)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_ddrr_os_START  (8)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_ddrr_os_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_MEM_CTRL_UNION
 结构说明  : AFBCD_MEM_CTRL 寄存器结构定义。地址偏移量:0x093C，初值:0x00000000，宽度:32
 寄存器说明: AFBCE SRAM控制寄存器（SP）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_mem_ctrl_0 : 4;  /* bit[0-3]  : 调试用寄存器,afbcd_br memory低功耗软件配置
                                                            [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                            [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                            [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                            [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  afbcd_mem_ctrl_1 : 4;  /* bit[4-7]  : 调试用寄存器,vbif_rdata_ram memory低功耗软件配置
                                                            [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                            [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                            [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                            [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  afbcd_mem_ctrl_2 : 4;  /* bit[8-11] : 调试用寄存器,afbcd_write memory低功耗配置：
                                                            [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                            [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                            [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                            [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_AFBCD_MEM_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_0_START  (0)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_0_END    (3)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_1_START  (4)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_1_END    (7)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_2_START  (8)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_2_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_UNION
 结构说明  : AFBCD_SCRAMBLE_MODE 寄存器结构定义。地址偏移量:0x0940，初值:0x00000000，宽度:32
 寄存器说明: SCRAMBLE模式选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd_scramble_mode : 2;  /* bit[0-1] : 要和GPU（或AFBCD）保持一致
                                                               2'b00 无scramble 兼容当前的功能。
                                                               2'b01 scramble mode 1
                                                               2'b10 scramble mode 2
                                                               2'b11 reserved */
        unsigned int  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_afbcd_scramble_mode_START  (0)
#define SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_afbcd_scramble_mode_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_RCH_G_REG_DEFAULT_UNION
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
} SOC_DSS_RCH_G_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_RCH_G_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_RCH_G_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_rch_g_interface.h */
