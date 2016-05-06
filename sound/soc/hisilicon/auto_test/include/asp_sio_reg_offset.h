//******************************************************************************
// Copyright (C), 2008-2014, Hisilicon Technologies Co., Ltd.
// Project name   : hiaspv300
// File name      : reg_offset.h
// Author         : xxx
// Abstract       : The offset address definition for the module SIO
// Others         : Generated automatically by nManager 
//------------------------------------------------------------------------------
// Modification History: 
// 
//******************************************************************************

/* SIO 模块寄存器基地址 */
#define HI3650_ASP_BASE                              (0xE804E800)

/******************************************************************************/
/*                      hiaspv300 SIO 寄存器定义                              */
/******************************************************************************/
#define HI3650_ASP_SIO_VERSION_REG                   (0x3C)           /* 版本寄存器 */
#define HI3650_ASP_SIO_MODE_REG                      (0x40)           /* 模式寄存器 */
#define HI3650_ASP_SIO_INTSTATUS_REG                 (0x44)           /* 中断状态寄存器 */
#define HI3650_ASP_SIO_INTCLR_REG                    (0x48)           /* 中断清除寄存器. */
#define HI3650_ASP_SIO_I2S_LEFT_XD_REG               (0x4C)           /* I2S模式下左声道数据发送寄存器 */
#define HI3650_ASP_SIO_I2S_RIGHT_XD_REG              (0x50)           /* I2S模式下右声道数据发送寄存器/PCM模式下的数据发送寄存器SIO_PCM_XD */
#define HI3650_ASP_SIO_I2S_LEFT_RD_REG               (0x54)           /* I2S模式下左声道数据接收寄存器 */
#define HI3650_ASP_SIO_I2S_RIGHT_RD_REG              (0x58)           /* I2S模式下右声道数据接收寄存器/PCM模式下接收数据寄存器 */
#define HI3650_ASP_SIO_CT_SET_REG                    (0x5C)           /* 控制寄存器使能寄存器 */
#define HI3650_ASP_SIO_CT_CLR_REG                    (0x60)           /* 控制寄存器清除寄存器 */
#define HI3650_ASP_SIO_RX_STA_REG                    (0x68)           /* SIO接收状态寄存器 */
#define HI3650_ASP_SIO_TX_STA_REG                    (0x6C)           /* SIO发送状态寄存器 */
#define HI3650_ASP_SIO_DATA_WIDTH_SET_REG            (0x78)           /* 数据宽度寄存器 */
#define HI3650_ASP_SIO_I2S_START_POS_REG             (0x7C)           /* I2S左右声道起始位置配置控制寄存器 */
#define HI3650_ASP_SIO_I2S_POS_FLAG_REG              (0x80)           /* I2S左右声道操作当前位置状态寄存器 */
#define HI3650_ASP_SIO_SIGNED_EXT_REG                (0x84)           /* 高位数据符号扩展使能寄存器 */
#define HI3650_ASP_SIO_I2S_POS_MERGE_EN_REG          (0x88)           /* I2S左右声道数据合并使能寄存器 */
#define HI3650_ASP_SIO_INTMASK_REG                   (0x8C)           /* 中断屏蔽寄存器 */
#define HI3650_ASP_SIO_I2S_DUAL_RX_CHN_REG           (0xA0)           /* 接收合并数据寄存器 */
#define HI3650_ASP_SIO_I2S_DUAL_TX_CHN_REG           (0xC0)           /* 发送合并数据寄存器 */

struct sio_congfig{
	 unsigned int tx_en;
	 unsigned int rx_en;
	 unsigned int frame_mode;
	 unsigned int mst_slv;
	 unsigned int lrclk_mode;
	 unsigned int chnnl_mode;
	 unsigned int io_wordlength;

	 unsigned int direct_loop;
	 unsigned int tx_clk_sel;
	 unsigned int rx_clk_sel;
	 unsigned int data_format;
	 unsigned int func_mode;
};