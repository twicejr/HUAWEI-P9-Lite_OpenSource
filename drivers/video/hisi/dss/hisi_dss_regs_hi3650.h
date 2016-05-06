/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/
#ifndef HISI_DSS_REGS_H
#define HISI_DSS_REGS_H

#include "hisi_fb.h"

/* MACROS */
#define DSS_WIDTH(width)	((width) - 1)
#define DSS_HEIGHT(height)	((height) - 1)

// resolution
#define RES_540P	(960 * 540)
#define RES_720P	(1280 * 720)
#define RES_1080P	(1920 * 1080)
#define RES_1200P	(1920 * 1200)
#define RES_1440P	(2560 * 1440)
#define RES_1600P	(2560 * 1600)

#define DFC_MAX_CLIP_NUM	(31)

#define DBUF1_DEPTH	(512)

#define GET_THD_RQOS_IN(max_depth)	((max_depth) * 10 / 100)
#define GET_THD_RQOS_OUT(max_depth)	((max_depth) * 30 / 100)
#define GET_THD_WQOS_IN(max_depth)	((max_depth) * 95 / 100)
#define GET_THD_WQOS_OUT(max_depth)	((max_depth) * 70 / 100)
#define GET_THD_CG_IN(max_depth)	((max_depth) -1)
#define GET_THD_CG_OUT(max_depth)	((max_depth) * 70 / 100)
#define GET_THD_OTHER_DFS_CG_HOLD(max_depth)	(0x20)
#define GET_THD_OTHER_WR_WAIT(max_depth)	((max_depth) * 90 / 100)

#define GET_THD_FLUX_REQ_IN(max_depth)  ((max_depth) * 50 / 100)
#define GET_THD_FLUX_REQ_OUT(max_depth) ((max_depth) * 90 / 100)

#define GET_RDMA_ROT_HQOS_ASSERT_LEV(max_depth)	((max_depth) * 30 /100)
#define GET_RDMA_ROT_HQOS_REMOVE_LEV(max_depth)	((max_depth)* 60 / 100)


enum lcd_orientation {
	LCD_LANDSCAPE = 0,
	LCD_PORTRAIT,
};

enum lcd_format {
	LCD_RGB565 = 0,
	LCD_RGB666,
	LCD_RGB888,
};

enum lcd_rgb_order {
	LCD_RGB = 0,
	LCD_BGR,
};

enum dss_addr {
	DSS_ADDR_PLANE0 = 0,
	DSS_ADDR_PLANE1,
	DSS_ADDR_PLANE2,
};

enum dss_transform {
	DSS_TRANSFORM_NOP = 0x0,
	DSS_TRANSFORM_FLIP_H = 0x01,
	DSS_TRANSFORM_FLIP_V = 0x02,
	DSS_TRANSFORM_ROT = 0x04,
};

enum dss_dfc_format {
	DFC_PIXEL_FORMAT_RGB_565 = 0,
	DFC_PIXEL_FORMAT_XRGB_4444,
	DFC_PIXEL_FORMAT_ARGB_4444,
	DFC_PIXEL_FORMAT_XRGB_5551,
	DFC_PIXEL_FORMAT_ARGB_5551,
	DFC_PIXEL_FORMAT_XRGB_8888,
	DFC_PIXEL_FORMAT_ARGB_8888,
	DFC_PIXEL_FORMAT_BGR_565,
	DFC_PIXEL_FORMAT_XBGR_4444,
	DFC_PIXEL_FORMAT_ABGR_4444,
	DFC_PIXEL_FORMAT_XBGR_5551,
	DFC_PIXEL_FORMAT_ABGR_5551,
	DFC_PIXEL_FORMAT_XBGR_8888,
	DFC_PIXEL_FORMAT_ABGR_8888,

	DFC_PIXEL_FORMAT_YUV444,
	DFC_PIXEL_FORMAT_YVU444,
	DFC_PIXEL_FORMAT_YUYV422,
	DFC_PIXEL_FORMAT_YVYU422,
	DFC_PIXEL_FORMAT_VYUY422,
	DFC_PIXEL_FORMAT_UYVY422,
};

enum dss_dma_format {
	DMA_PIXEL_FORMAT_RGB_565 = 0,
	DMA_PIXEL_FORMAT_ARGB_4444,
	DMA_PIXEL_FORMAT_XRGB_4444,
	DMA_PIXEL_FORMAT_ARGB_5551,
	DMA_PIXEL_FORMAT_XRGB_5551,
	DMA_PIXEL_FORMAT_ARGB_8888,
	DMA_PIXEL_FORMAT_XRGB_8888,

	DMA_PIXEL_FORMAT_RESERVED0,

	DMA_PIXEL_FORMAT_YUYV_422_Pkg,
	DMA_PIXEL_FORMAT_YUV_420_SP_HP,
	DMA_PIXEL_FORMAT_YUV_420_P_HP,
	DMA_PIXEL_FORMAT_YUV_422_SP_HP,
	DMA_PIXEL_FORMAT_YUV_422_P_HP,
	DMA_PIXEL_FORMAT_AYUV_4444,
};

enum dss_buf_format {
	DSS_BUF_LINEAR = 0,
	DSS_BUF_TILE,
};

enum dss_blend_mode {
	DSS_BLEND_CLEAR = 0,
	DSS_BLEND_SRC, // 1
	DSS_BLEND_DST, // 2
	DSS_BLEND_SRC_OVER_DST, // 3
	DSS_BLEND_DST_OVER_SRC, // 4
	DSS_BLEND_SRC_IN_DST, // 5
	DSS_BLEND_DST_IN_SRC, // 6
	DSS_BLEND_SRC_OUT_DST, // 7
	DSS_BLEND_DST_OUT_SRC, // 8
	DSS_BLEND_SRC_ATOP_DST, // 9
	DSS_BLEND_DST_ATOP_SRC, // 10
	DSS_BLEND_SRC_XOR_DST, // 11
	DSS_BLEND_SRC_ADD_DST, // 12
	DSS_BLEND_FIX_OVER, // 13
	DSS_BLEND_FIX_PER0, // 14
	DSS_BLEND_FIX_PER1, // 15
	DSS_BLEND_FIX_PER2, // 16
	DSS_BLEND_FIX_PER3, // 17
	DSS_BLEND_FIX_PER4, // 18
	DSS_BLEND_FIX_PER5, // 19
	DSS_BLEND_FIX_PER6, // 20
	DSS_BLEND_FIX_PER7, // 21
	DSS_BLEND_FIX_PER8, // 22
	DSS_BLEND_FIX_PER9, // 23
	DSS_BLEND_FIX_PER10, // 24
	DSS_BLEND_FIX_PER11, // 25
	DSS_BLEND_FIX_PER12, // 26
	DSS_BLEND_FIX_PER13, // 27
	DSS_BLEND_FIX_PER14, // 28
	DSS_BLEND_FIX_PER15, // 29
	DSS_BLEND_FIX_PER16, // 30
	DSS_BLEND_FIX_PER17, // 31

	DSS_BLEND_MAX,
};

enum dss_chn_module {
	MODULE_MIF_CHN,
	MODULE_AIF0_CHN,
	MODULE_AIF1_CHN,
	MODULE_MCTL_CHN_MUTEX,
	MODULE_MCTL_CHN_FLUSH_EN,
	MODULE_MCTL_CHN_OV_OEN,
	MODULE_MCTL_CHN_STARTY,
	MODULE_MCTL_CHN_MOD_DBG,
	MODULE_DMA,
	MODULE_DFC,
	MODULE_SCL,
	MODULE_SCL_LUT,
	MODULE_SHARPNESS,
	MODULE_POST_CLIP,
	MODULE_CSC,
	MODULE_CE,
	MODULE_CE_HIST_RPT0,
	MODULE_CE_HIST_RPT1,
	MODULE_CE_LUT0,
	MODULE_CE_LUT1,
	MODULE_CHN_MAX,
};

enum dss_chn_cap {
	MODULE_CAP_ROT,
	MODULE_CAP_SCL,
	MODULE_CAP_CSC,
	MODULE_CAP_SHARPNESS_1D,
	MODULE_CAP_SHARPNESS_2D,
	MODULE_CAP_CE,
	MODULE_CAP_AFBCD,
	MODULE_CAP_AFBCE,
	MODULE_CAP_YUV_PLANAR,
	MODULE_CAP_YUV_SEMI_PLANAR,
	MODULE_CAP_YUV_PACKAGE,
	MODULE_CAP_MAX,
};

enum dss_ovl_module {
	MODULE_OVL_BASE,
	MODULE_MCTL_BASE,
	MODULE_OVL_MAX,
};

enum dss_axi_idx {
	AXI_CHN0 = 0,
	AXI_CHN1,
	AXI_CHN_MAX,
};

#define AXI0_MAX_DSS_CHN_THRESHOLD	(3)
#define AXI1_MAX_DSS_CHN_THRESHOLD	(3)

#define DEFAULT_AXI_CLK_RATE0	(120 * 1000000)
#define DEFAULT_AXI_CLK_RATE1	(240 * 1000000)
#define DEFAULT_AXI_CLK_RATE2	(360 * 1000000)
#define DEFAULT_AXI_CLK_RATE3	(480 * 1000000)
#define DEFAULT_AXI_CLK_RATE4	(667 * 1000000)
#define DEFAULT_AXI_CLK_RATE5	(800 * 1000000)

enum dss_rdma_idx {
	DSS_RDMA0 = 0,
	DSS_RDMA1,
	DSS_RDMA2,
	DSS_RDMA3,
	DSS_RDMA4,
	DSS_RDMA_MAX,
};

/*******************************************************************************
**
*/
// CRGPERI
#define PEREN0	(0x000)
#define PEREN2	(0x020)
#define PERDIS2	(0x024)
#define PERCLKEN2	(0x028)
#define PERSTAT2	(0x02C)
#define PEREN3	(0x030)
#define PERDIS3	(0x034)
#define PERCLKEN3	(0x038)
#define PERSTAT3	(0x03C)
#define PEREN5	(0x050)
#define PERDIS5	(0x054)
#define PERCLKEN5	(0x058)
#define PERSTAT5	(0x05C)
#define PERRSTDIS0	(0x064)
#define PERRSTEN2	(0x078)
#define PERRSTDIS2	(0x07C)
#define PERRSTEN3	(0x084)
#define PERRSTDIS3	(0x088)
#define PERRSTSTAT3 (0x08c)
#define CLKDIV3	(0x0B4)
#define CLKDIV5	(0x0BC)
#define CLKDIV10	(0x0D0)
#define CLKDIV18	(0x0F0)
#define CLKDIV20	(0x0F8)
#define ISODIS	(0x148)
#define ISOSTAT	(0x14c)
#define PERPWREN	(0x150)
#define PERPWRSTAT 	(0x158)
#define PERI_AUTODIV8	(0x380)
#define PERI_AUTODIV9	(0x384)
#define PERI_AUTODIV10	(0x388)

// PMC
#define NOC_POWER_IDLEREQ	(0x380)
#define NOC_POWER_IDLEACK	(0x384)
#define NOC_POWER_IDLE	(0x388)

//PCTRL
#define PERI_CTRL23	(0x060)
#define PERI_CTRL29	(0x078)
#define PERI_CTRL30	(0x07C)
#define PERI_CTRL32	(0x084)
#define PERI_STAT0	(0x094)
#define PERI_STAT1	(0x098)
#define PERI_STAT16	(0x0D4)

//PERI_CTRL23	(0x060)
#define PCTRL_DPHYTX_ULPSEXIT1	BIT(4)
#define PCTRL_DPHYTX_ULPSEXIT0	BIT(3)

//PERI_CTRL29	(0x078)
//pctrl_dphytx_stopcnt0

//PERI_CTRL32	(0x084)
//pctrl_dphytx_stopcnt1

//PERI_CTRL30	(0x07C)
#define PCTRL_DPHYTX_CTRL1	BIT(1)
#define PCTRL_DPHYTX_CTRL0	BIT(0)


/*******************************************************************************
**
*/
// CPU_PDP_INTS		0x224
// CPU_PDP_INT_MSK	0x228
#define BIT_DSS_GLB_INTS	BIT(30)
#define BIT_MMU_IRPT_S	BIT(29)
#define BIT_MMU_IRPT_NS	BIT(28)
#define BIT_DBG_MCTL_INTS	BIT(27)
#define BIT_DBG_WCH1_INTS	BIT(26)
#define BIT_DBG_WCH0_INTS	BIT(25)
#define BIT_DBG_RCH7_INTS	BIT(24)
#define BIT_DBG_RCH6_INTS	BIT(23)
#define BIT_DBG_RCH5_INTS	BIT(22)
#define BIT_DBG_RCH4_INTS	BIT(21)
#define BIT_DBG_RCH3_INTS	BIT(20)
#define BIT_DBG_RCH2_INTS	BIT(19)
#define BIT_DBG_RCH1_INTS	BIT(18)
#define BIT_DBG_RCH0_INTS	BIT(17)
#define BIT_ITF0_INTS	BIT(16)
#define BIT_DPP_INTS	BIT(15)
#define BIT_CMDLIST13	BIT(14)
#define BIT_CMDLIST12	BIT(13)
#define BIT_CMDLIST11	BIT(12)
#define BIT_CMDLIST10	BIT(11)
#define BIT_CMDLIST9	BIT(10)
#define BIT_CMDLIST8	BIT(9)
#define BIT_CMDLIST7	BIT(8)
#define BIT_CMDLIST6	BIT(7)
#define BIT_CMDLIST5	BIT(6)
#define BIT_CMDLIST4	BIT(5)
#define BIT_CMDLIST3	BIT(4)
#define BIT_CMDLIST2	BIT(3)
#define BIT_CMDLIST1	BIT(2)
#define BIT_CMDLIST0	BIT(1)
#define BIT_RCH_CE_INTS	BIT(0)


// CPU_SDP_INTS		0x22C
// CPU_SDP_INT_MSK	0x230
#define BIT_SDP_DSS_GLB_INTS	BIT(29)
#define BIT_SDP_MMU_IRPT_S	BIT(28)
#define BIT_SDP_MMU_IRPT_NS	BIT(27)
#define BIT_SDP_DBG_MCTL_INTS	BIT(26)
#define BIT_SDP_DBG_WCH1_INTS	BIT(25)
#define BIT_SDP_DBG_WCH0_INTS	BIT(24)
#define BIT_SDP_DBG_RCH7_INTS	BIT(23)
#define BIT_SDP_DBG_RCH6_INTS	BIT(22)
#define BIT_SDP_DBG_RCH5_INTS	BIT(21)
#define BIT_SDP_DBG_RCH4_INTS	BIT(20)
#define BIT_SDP_DBG_RCH3_INTS	BIT(19)
#define BIT_SDP_DBG_RCH2_INTS	BIT(18)
#define BIT_SDP_DBG_RCH1_INTS	BIT(17)
#define BIT_SDP_DBG_RCH0_INTS	BIT(16)
#define BIT_SDP_ITF1_INTS	BIT(15)
#define BIT_SDP_CMDLIST13	BIT(14)
#define BIT_SDP_CMDLIST12	BIT(13)
#define BIT_SDP_CMDLIST11	BIT(12)
#define BIT_SDP_CMDLIST10	BIT(11)
#define BIT_SDP_CMDLIST9	BIT(10)
#define BIT_SDP_CMDLIST8	BIT(9)
#define BIT_SDP_CMDLIST7	BIT(8)
#define BIT_SDP_CMDLIST6	BIT(7)
#define BIT_SDP_CMDLIST5	BIT(6)
#define BIT_SDP_CMDLIST4	BIT(5)
#define BIT_SDP_CMDLIST3	BIT(4)
#define BIT_SDP_SDP_CMDLIST2	BIT(3)
#define BIT_SDP_CMDLIST1	BIT(2)
#define BIT_SDP_CMDLIST0	BIT(1)
#define BIT_SDP_RCH_CE_INTS	BIT(0)


// CPU_OFF_INTS	0x234
// CPU_OFF_INT_MASK	0x238
#define BIT_OFF_DSS_GLB_INTS	BIT(31)
#define BIT_OFF_MMU_IRPT_S	BIT(30)
#define BIT_OFF_MMU_IRPT_NS	BIT(29)
#define BIT_OFF_DBG_MCTL_INTS	BIT(28)
#define BIT_OFF_DBG_WCH1_INTS	BIT(27)
#define BIT_OFF_DBG_WCH0_INTS	BIT(26)
#define BIT_OFF_DBG_RCH7_INTS	BIT(25)
#define BIT_OFF_DBG_RCH6_INTS	BIT(24)
#define BIT_OFF_DBG_RCH5_INTS	BIT(23)
#define BIT_OFF_DBG_RCH4_INTS	BIT(22)
#define BIT_OFF_DBG_RCH3_INTS	BIT(21)
#define BIT_OFF_DBG_RCH2_INTS	BIT(20)
#define BIT_OFF_DBG_RCH1_INTS	BIT(19)
#define BIT_OFF_DBG_RCH0_INTS	BIT(18)
#define BIT_OFF_WCH1_INTS	BIT(17)
#define BIT_OFF_WCH0_INTS	BIT(16)
#define BIT_OFF_WCH0_WCH1_FRM_END_INT	BIT(15)
#define BIT_OFF_CMDLIST13	BIT(14)
#define BIT_OFF_CMDLIST12	BIT(13)
#define BIT_OFF_CMDLIST11	BIT(12)
#define BIT_OFF_CMDLIST10	BIT(11)
#define BIT_OFF_CMDLIST9	BIT(10)
#define BIT_OFF_CMDLIST8	BIT(9)
#define BIT_OFF_CMDLIST7	BIT(8)
#define BIT_OFF_CMDLIST6	BIT(7)
#define BIT_OFF_CMDLIST5	BIT(6)
#define BIT_OFF_CMDLIST4	BIT(5)
#define BIT_OFF_CMDLIST3	BIT(4)
#define BIT_OFF_CMDLIST2	BIT(3)
#define BIT_OFF_CMDLIST1	BIT(2)
#define BIT_OFF_CMDLIST0	BIT(1)
#define BIT_OFF_RCH_CE_INTS	BIT(0)


// CPU_ITF0_INTS		0x0180
// CPU_ITF0_INT_MSK	0x0184
// CPU_ITF1_INTS		0x0188
// CPU_ITF1_INT_MSK	0x018C
#define BIT_DSI_TE_TRI	BIT(13)
#define BIT_LCD_TE0_PIN	BIT(12)
#define BIT_LCD_TE1_PIN	BIT(11)
#define BIT_VACTIVE1_END	BIT(10)
#define BIT_VACTIVE1_START	BIT(9)
#define BIT_VACTIVE0_END	BIT(8)
#define BIT_VACTIVE0_START	BIT(7)
#define BIT_VFRONTPORCH	BIT(6)
#define BIT_VBACKPORCH	BIT(5)
#define BIT_VSYNC	BIT(4)
#define BIT_VFRONTPORCH_END	BIT(3)
#define BIT_LDI_UNFLOW	BIT(2)
#define BIT_FRM_END	BIT(1)
#define BIT_FRM_START	BIT(0)


// CTL_FLUSH 0x0158
#define BIT_CTL_FLUSH_EN	BIT(21)
#define BIT_SCF_FLUSH_EN	BIT(19)
#define BIT_DPP0_FLUSH_EN	BIT(18)
#define BIT_DBUF1_FLUSH_EN	BIT(17)
#define BIT_DBUF0_FLUSH_EN	BIT(16)
#define BIT_OV3_FLUSH_EN	BIT(15)
#define BIT_OV2_FLUSH_EN	BIT(14)
#define BIT_OV1_FLUSH_EN	BIT(13)
#define BIT_OV0_FLUSH_EN	BIT(12)
#define BIT_WB1_FLUSH_EN	BIT(11)
#define BIT_WB0_FLUSH_EN	BIT(10)
#define BIT_DMA3_FLUSH_EN	BIT(9)
#define BIT_DMA2_FLUSH_EN	BIT(8)
#define BIT_DMA1_FLUSH_EN	BIT(7)
#define BIT_DMA0_FLUSH_EN	BIT(6)
#define BIT_RGB1_FLUSH_EN	BIT(4)
#define BIT_RGB0_FLUSH_EN	BIT(3)
#define BIT_VIG1_FLUSH_EN	BIT(1)
#define BIT_VIG0_FLUSH_EN	BIT(0)

//RCH_CE
#define BIT_CE_END_RCH4_IND	BIT(3)
#define BIT_CE_CANCEL_RCH4_IND	BIT(2)
#define BIT_CE_END_RCH2_IND	BIT(1)
#define BIT_CE_CANCEL_RCH2_IND	BIT(0)


// GLB_INTS	(0x294)
// GLB_INT_MSK	(0x298)
#define BIT_BUS_DBG_INT	BIT(5)
#define BIT_CRC_SUM_INT	BIT(4)
#define BIT_CRC_ITF1_INT	BIT(3)
#define BIT_CRC_ITF0_INT	BIT(2)
#define BIT_CRC_OV1_INT	BIT(1)
#define BIT_CRC_OV0_INT	BIT(0)


//DPP_INTS	(0x190)
#define BIT_STRENGTH_INTP	BIT(7)
#define BIT_BACKLIGHT_INTP	BIT(6)
#define BIT_CE_END_IND	BIT(5)
#define BIT_CE_CANCEL_IND	BIT(4)
#define BIT_CE_LUT1_RW_COLLIDE_IND	BIT(3)
#define BIT_CE_LUT0_RW_COLLIDE_IND	BIT(2)
#define BIT_CE_HIST1_RW_COLLIDE_IND	BIT(1)
#define BIT_CE_HIST0_RW_COLLIDE_IND	BIT(0)


/*******************************************************************************
** MODULE BASE ADDRESS
*/
// GLB0
#define DSS_GLB0_OFFSET	(0x0000)

// CMDLIST
#define DSS_CMDLIST_OFFSET	(0x2000)

//SMMU
#define DSS_SMMU_OFFSET	(0x8000)

//AIF
#define DSS_VBIF0_AIF	(0x7000)
#define DSS_VBIF1_AIF	(0x9000)

// MIF
#define DSS_MIF_OFFSET	(0xA000)

// MCTL SYS
#define DSS_MCTRL_SYS_OFFSET	(0x10000)

// MCTL MUTEX
#define DSS_MCTRL_CTL0_OFFSET	(0x10800)
#define DSS_MCTRL_CTL1_OFFSET	(0x10900)
#define DSS_MCTRL_CTL2_OFFSET	(0x10A00)
#define DSS_MCTRL_CTL3_OFFSET	(0x10B00)
#define DSS_MCTRL_CTL4_OFFSET	(0x10C00)
#define DSS_MCTRL_CTL5_OFFSET	(0x10D00)

// DBG
#define DSS_DBG_OFFSET	(0x11000)

// OVL
#define DSS_OVL0_OFFSET	(0x60000)
#define DSS_OVL1_OFFSET	(0x60400)
#define DSS_OVL2_OFFSET	(0x60800)
#define DSS_OVL3_OFFSET	(0x60C00)

// POST SCF
#define DSS_POST_SCF_OFFSET	(0x64000)
#define DSS_POST_SCF_LUT_OFFSET	(0x65000)

//DBUF
#define DSS_DBUF0_OFFSET	(0x6D000)
#define DSS_DBUF1_OFFSET	(0x6E000)

// DPP
#define DSS_DPP_OFFSET	(0x70000)
#define DSS_TOP_OFFSET	(0x70000)
#define DSS_DPP_RD_SHADOW_OFFSET	(0x70000)
#define DSS_DPP_LCP_OFFSET	(0x70100)
#define DSS_DPP_ACM_OFFSET	(0x70200)
#define DSS_DPP_ACM_CE_OFFSET	(0x70200)
#define DSS_DPP_GAMMA_OFFSET	(0x70300)
#define DSS_GAMA_LUT_OFFSET	(0x70400)
#define DSS_ACM_LUT_OFFSET	(0x71000)
#define DSS_LCP_LUT_OFFSET	(0x73000)
#define DSS_DPP_SBL_OFFSET	(0x7C000)
#define DSS_LDI0_OFFSET	(0x7D000)
#define DSS_IFBC_OFFSET	(0x7D800)
#define DSS_DSC_OFFSET	(0x7DC00)
#define DSS_LDI1_OFFSET	(0x7E000)

// RCH_V
#define DSS_RCH_VG0_DMA_OFFSET	(0x20000)
#define DSS_RCH_VG0_DFC_OFFSET (0x20100)
#define DSS_RCH_VG0_SCL_OFFSET	(0x20200)
#define DSS_RCH_VG0_SHARPNESS_OFFSET	(0x20300)
#define DSS_RCH_VG0_POST_CLIP_OFFSET	(0x203A0)
#define DSS_RCH_VG0_CE_OFFSET	(0x20400)
#define DSS_RCH_VG0_CSC_OFFSET	(0x20500)
#define DSS_RCH_VG0_SCL_LUT_OFFSET	(0x21000)
#define DSS_RCH_VG0_CE0_LUT_OFFSET	(0x25000)
#define DSS_RCH_VG0_CE1_LUT_OFFSET	(0x25400)
#define DSS_RCH_VG0_CE2_LUT_OFFSET	(0x25800)
#define DSS_RCH_VG0_CE3_LUT_OFFSET	(0x25C00)

#define DSS_RCH_VG1_DMA_OFFSET	(0x28000)
#define DSS_RCH_VG1_DFC_OFFSET	(0x28100)
#define DSS_RCH_VG1_SCL_OFFSET	(0x28200)
#define DSS_RCH_VG1_SHARPNESS_OFFSET	(0x28300)
#define DSS_RCH_VG1_POST_CLIP_OFFSET	(0x283A0)
#define DSS_RCH_VG1_CE_OFFSET	(0x28400)
#define DSS_RCH_VG1_CSC_OFFSET	(0x28500)
#define DSS_RCH_VG1_SCL_LUT_OFFSET	(0x29000)
#define DSS_RCH_VG1_CE0_LUT_OFFSET	(0x2D000)
#define DSS_RCH_VG1_CE1_LUT_OFFSET	(0x2D400)
#define DSS_RCH_VG1_CE2_LUT_OFFSET	(0x2D800)
#define DSS_RCH_VG1_CE3_LUT_OFFSET	(0x2DC00)

// RCH_G
#define DSS_RCH_G0_DMA_OFFSET	(0x38000)
#define DSS_RCH_G0_DFC_OFFSET	(0x38100)
#define DSS_RCH_G0_SCL_OFFSET	(0x38200)
#define DSS_RCH_G0_POST_CLIP_OFFSET (0x383A0)

#define DSS_RCH_G1_DMA_OFFSET	(0x40000)
#define DSS_RCH_G1_DFC_OFFSET	(0x40100)
#define DSS_RCH_G1_SCL_OFFSET	(0x40200)
#define DSS_RCH_G1_POST_CLIP_OFFSET (0x403A0)

// RCH_D
#define DSS_RCH_D0_DMA_OFFSET	(0x50000)
#define DSS_RCH_D0_DFC_OFFSET	(0x50100)
#define DSS_RCH_D0_CSC_OFFSET	(0x50500)

#define DSS_RCH_D1_DMA_OFFSET	(0x51000)
#define DSS_RCH_D1_DFC_OFFSET	(0x51100)
#define DSS_RCH_D1_CSC_OFFSET	(0x51500)

#define DSS_RCH_D2_DMA_OFFSET	(0x52000)
#define DSS_RCH_D2_DFC_OFFSET	(0x52100)
#define DSS_RCH_D2_CSC_OFFSET	(0x52500)

#define DSS_RCH_D3_DMA_OFFSET	(0x53000)
#define DSS_RCH_D3_DFC_OFFSET	(0x53100)
#define DSS_RCH_D3_CSC_OFFSET	(0x53500)

// WCH
#define DSS_WCH0_DMA_OFFSET	(0x5A000)
#define DSS_WCH0_DFC_OFFSET	(0x5A100)
#define DSS_WCH0_CSC_OFFSET	(0x5A500)

#define DSS_WCH1_DMA_OFFSET	(0x5C000)
#define DSS_WCH1_DFC_OFFSET	(0x5C100)
#define DSS_WCH1_CSC_OFFSET	(0x5C500)


/*******************************************************************************
** GLB
*/
#define GLB_APB_CTL	(0x0004)

#define GLB_PXL0_DIV2_GT_EN	(0x0100)
#define GLB_PXL0_DIV4_GT_EN	(0x0104)
#define GLB_PXL0_GT_EN	(0x0108)
#define GLB_PXL0_DSI_GT_EN	(0x010C)
#define GLB_PXL0_DIVXCFG	(0x0110)

#define GLB_DSI1_CLK_SEL	(0x0114)

#define GLB_DSS_AXI_RST_EN	(0x0118)
#define GLB_DSS_APB_RST_EN	(0x011C)
#define GLB_DSS_CORE_RST_EN	(0x0120)
#define GLB_PXL0_DIV2_RST_EN	(0x0124)
#define GLB_PXL0_DIV4_RST_EN	(0x0128)
#define GLB_PXL0_RST_EN	(0x012C)
#define GLB_PXL0_DSI_RST_EN	(0x0130)
#define GLB_DSS_PXL1_RST_EN	(0x0134)
#define GLB_DSI1_RST_SEL	(0x0138)

#define GLB_MCU_ITF0_INTS	(0x0170)
#define GLB_MCU_ITF0_INT_MSK	(0x0174)
#define GLB_MCU_ITF1_INTS	(0x0178)
#define GLB_MCU_ITF1_INT_MSK	(0x017C)
#define GLB_GLB_CPU_ITF0_INTS	(0x0180)
#define GLB_GLB_CPU_ITF0_INT_MSK	(0x0184)
#define GLB_GLB_CPU_ITF1_INTS	(0x0188)
#define GLB_GLB_CPU_ITF1_INT_MSK	(0x018C)
#define GLB_GLB_DPP_INTS	(0x0190)
#define GLB_GLB_DPP_INT_MSK	(0x0194)
#define GLB_RCH_CE_INTS	(0x0198)
#define GLB_RCH_CE_INT_MSK	(0x019c)

#define GLB_MCU_PDP_INTS	(0x20C)
#define GLB_MCU_PDP_INT_MSK	(0x210)
#define GLB_MCU_SDP_INTS	(0x214)
#define GLB_MCU_SDP_INT_MSK	(0x218)
#define GLB_MCU_OFF_INTS	(0x21C)
#define GLB_MCU_OFF_INT_MSK	(0x220)
#define GLB_CPU_PDP_INTS	(0x224)
#define GLB_CPU_PDP_INT_MSK	(0x228)
#define GLB_CPU_SDP_INTS	(0x22C)
#define GLB_CPU_SDP_INT_MSK	(0x230)
#define GLB_CPU_OFF_INTS	(0x234)
#define GLB_CPU_OFF_INT_MSK	(0x238)

#define GLB_DBG_MCTL_INTS	(0x23C)
#define GLB_DBG_MCTL_INT_MSK	(0x240)
#define GLB_DBG_WCH0_INTS	(0x244)
#define GLB_DBG_WCH0_INT_MSK	(0x248)
#define GLB_DBG_WCH1_INTS	(0x24C)
#define GLB_DBG_WCH1_INT_MSK	(0x250)
#define GLB_DBG_RCH0_INTS	(0x254)
#define GLB_DBG_RCH0_INT_MSK	(0x258)
#define GLB_DBG_RCH1_INTS	(0x25C)
#define GLB_DBG_RCH1_INT_MSK	(0x260)
#define GLB_DBG_RCH2_INTS	(0x264)
#define GLB_DBG_RCH2_INT_MSK	(0x268)
#define GLB_DBG_RCH3_INTS	(0x26C)
#define GLB_DBG_RCH3_INT_MSK	(0x270)
#define GLB_DBG_RCH4_INTS	(0x274)
#define GLB_DBG_RCH4_INT_MSK	(0x278)
#define GLB_DBG_RCH5_INTS	(0x27C)
#define GLB_DBG_RCH5_INT_MSK	(0x280)
#define GLB_DBG_RCH6_INTS	(0x284)
#define GLB_DBG_RCH6_INT_MSK	(0x288)
#define GLB_DBG_RCH7_INTS	(0x28C)
#define GLB_DBG_RCH7_INT_MSK	(0x290)

#define GLB_INTS	(0x294)
#define GLB_INT_MSK	(0x298)

#define GLB_MODULE_CLK_SEL	(0x0300)
#define GLB_MODULE_CLK_EN	(0x0304)
#define GLB_MODULE1_CLK_SEL	(0x308)
#define GLB_MODULE1_CLK_EN	(0x30C)
#define GLB_GLB0_DBG_SEL	(0x310)
#define GLB_GLB1_DBG_SEL	(0x314)
#define GLB_DSS_TAG	(0x318)
#define GLB_DBG_IRQ_CPU	(0x320)
#define GLB_DBG_IRQ_MCU	(0x324)

#define GLB_TP_SEL	(0x0400)
#define GLB_CRC_DBG_LDI0	(0x0404)
#define GLB_CRC_DBG_LDI1	(0x0408)
#define GLB_CRC_LDI0_EN	(0x040C)
#define GLB_CRC_LDI0_FRM	(0x0410)
#define GLB_CRC_LDI1_EN	(0x0414)
#define GLB_CRC_LDI1_FRM	(0x0418)
#define GLB_DSS_MEM_CTRL	(0x0600)
#define GLB_DSS_PM_CTRL	(0x0604)


/*******************************************************************************
** DBG
*/
#define DBG_CRC_DBG_OV0	(0x0000)
#define DBG_CRC_DBG_OV1	(0x0004)
#define DBG_CRC_DBG_SUM	(0x0008)
#define DBG_CRC_OV0_EN	(0x000C)
#define DBG_DSS_GLB_DBG_O	(0x0010)
#define DBG_DSS_GLB_DBG_I	(0x0014)
#define DBG_CRC_OV0_FRM	(0x0018)
#define DBG_CRC_OV1_EN	(0x001C)
#define DBG_CRC_OV1_FRM	(0x0020)
#define DBG_CRC_SUM_EN	(0x0024)
#define DBG_CRC_SUM_FRM	(0x0028)


/*******************************************************************************
** CMDLIST
*/
#define BIT_CMDLIST_CH_TASKDONE_INTS	    BIT(7)
#define BIT_CMDLIST_CH_TIMEOUT_INTS	    BIT(6)
#define BIT_CMDLIST_CH_BADCMD_INTS	    BIT(5)
#define BIT_CMDLIST_CH_START_INTS	           BIT(4)
#define BIT_CMDLIST_CH_PENDING_INTS	    BIT(3)
#define BIT_CMDLIST_CH_AXIERR_INTS	    BIT(2)
#define BIT_CMDLIST_CH_ALLDONE_INTS	    BIT(1)
#define BIT_CMDLIST_CH_ONEDONE_INTS	    BIT(0)

#define BIT_CMDLIST_CH13_INTS	BIT(13)
#define BIT_CMDLIST_CH12_INTS	BIT(12)
#define BIT_CMDLIST_CH11_INTS	BIT(11)
#define BIT_CMDLIST_CH10_INTS	BIT(10)
#define BIT_CMDLIST_CH9_INTS	BIT(9)
#define BIT_CMDLIST_CH8_INTS	BIT(8)
#define BIT_CMDLIST_CH7_INTS	BIT(7)
#define BIT_CMDLIST_CH6_INTS	BIT(6)
#define BIT_CMDLIST_CH5_INTS	BIT(5)
#define BIT_CMDLIST_CH4_INTS	BIT(4)
#define BIT_CMDLIST_CH3_INTS	BIT(3)
#define BIT_CMDLIST_CH2_INTS	BIT(2)
#define BIT_CMDLIST_CH1_INTS	BIT(1)
#define BIT_CMDLIST_CH0_INTS	BIT(0)

#define CMDLIST_CH0_PENDING_CLR	(0x0000)
#define CMDLIST_CH0_CTRL	(0x0004)
#define CMDLIST_CH0_STATUS	(0x0008)
#define CMDLIST_CH0_STAAD	(0x000C)
#define CMDLIST_CH0_CURAD	(0x0010)
#define CMDLIST_CH0_INTE	(0x0014)
#define CMDLIST_CH0_INTC	(0x0018)
#define CMDLIST_CH0_INTS	(0x001C)
#define CMDLIST_CH0_DBG	(0x0028)

#define CMDLIST_ADDR_MASK_DIS	(0x03EC)
#define CMDLIST_TIMEOUT_TH	(0x03FC)
#define CMDLIST_START	(0x0400)
#define CMDLIST_ADDR_MASK_EN	(0x0404)
#define CMDLIST_TASK_CONTINUE	(0x0408)
#define CMDLIST_TASK_STATUS	(0x040C)
#define CMDLIST_CTRL	(0x0410)
#define CMDLIST_SECU	(0x0414)
#define CMDLIST_INTS	(0x0418)
#define CMDLIST_SWRST	(0x041C)
#define CMD_MEM_CTRL	(0x0420)
#define CMD_PM_CTRL	(0x0424)
#define CMD_CLK_SEL		(0x0428)
#define CMD_CLK_EN	(0x042C)

#define HISI_DSS_MIN_ROT_AFBCE_BLOCK_SIZE (256)
#define HISI_DSS_MAX_ROT_AFBCE_BLOCK_SIZE (480)

/*******************************************************************************
** AIF
*/
#define AIF0_CH0_OFFSET	(DSS_VBIF0_AIF + 0x00)
#define AIF0_CH1_OFFSET	(DSS_VBIF0_AIF + 0x20)
#define AIF0_CH2_OFFSET	(DSS_VBIF0_AIF + 0x40)
#define AIF0_CH3_OFFSET	(DSS_VBIF0_AIF + 0x60)
#define AIF0_CH4_OFFSET	(DSS_VBIF0_AIF + 0x80)
#define AIF0_CH5_OFFSET	(DSS_VBIF0_AIF + 0xA0)
#define AIF0_CH6_OFFSET	(DSS_VBIF0_AIF + 0xC0)
#define AIF0_CH7_OFFSET	(DSS_VBIF0_AIF + 0xE0)
#define AIF0_CH8_OFFSET	(DSS_VBIF0_AIF + 0x100)
#define AIF0_CH9_OFFSET	(DSS_VBIF0_AIF + 0x120)

#define AIF1_CH0_OFFSET	(DSS_VBIF1_AIF + 0x00)
#define AIF1_CH1_OFFSET	(DSS_VBIF1_AIF + 0x20)
#define AIF1_CH2_OFFSET	(DSS_VBIF1_AIF + 0x40)
#define AIF1_CH3_OFFSET	(DSS_VBIF1_AIF + 0x60)
#define AIF1_CH4_OFFSET	(DSS_VBIF1_AIF + 0x80)
#define AIF1_CH5_OFFSET	(DSS_VBIF1_AIF + 0xA0)
#define AIF1_CH6_OFFSET	(DSS_VBIF1_AIF + 0xC0)
#define AIF1_CH7_OFFSET	(DSS_VBIF1_AIF + 0xE0)
#define AIF1_CH8_OFFSET	(DSS_VBIF1_AIF + 0x100)
#define AIF1_CH9_OFFSET	(DSS_VBIF1_AIF + 0x120)

//(0x0000+0x20*n)
#define AIF_CH_CTL	(0x0000)
//(0x0018+0x20*n)
#define AIF_CH_STS	(0x0018)

#define AXI0_RID_MSK0	(0x0800)
#define AXI0_RID_MSK1	(0x0804)
#define AXI0_WID_MSK	(0x0808)
#define AXI0_R_QOS_MAP	(0x080c)
#define AXI1_RID_MSK0	(0x0810)
#define AXI1_RID_MSK1	(0x0814)
#define AXI1_WID_MSK	(0x0818)
#define AXI1_R_QOS_MAP	(0x081c)
#define AIF_CLK_SEL0	(0x0820)
#define AIF_CLK_SEL1	(0x0824)
#define AIF_CLK_EN0	(0x0828)
#define AIF_CLK_EN1	(0x082c)
#define MONITOR_CTRL	(0x0830)
#define MONITOR_TIMER_INI	(0x0834)
#define DEBUG_BUF_BASE	(0x0838)
#define DEBUG_CTRL	(0x083C)
#define AIF_SHADOW_READ	(0x0840)
#define AIF_MEM_CTRL	(0x0844)

typedef struct dss_aif {
	uint32_t aif_ch_ctl;
} dss_aif_t;

typedef struct dss_aif_bw {
	uint32_t bw;
	uint8_t chn_idx;
	int8_t axi_sel;
	uint8_t is_used;
} dss_aif_bw_t;


/*******************************************************************************
** MIF
*/
#define MIF_CH0_OFFSET	(DSS_MIF_OFFSET + 0x20)
#define MIF_CH1_OFFSET	(DSS_MIF_OFFSET + 0x40)
#define MIF_CH2_OFFSET	(DSS_MIF_OFFSET + 0x60)
#define MIF_CH3_OFFSET	(DSS_MIF_OFFSET + 0x80)
#define MIF_CH4_OFFSET	(DSS_MIF_OFFSET + 0xA0)
#define MIF_CH5_OFFSET	(DSS_MIF_OFFSET + 0xC0)
#define MIF_CH6_OFFSET	(DSS_MIF_OFFSET + 0xE0)
#define MIF_CH7_OFFSET	(DSS_MIF_OFFSET + 0x100)
#define MIF_CH8_OFFSET	(DSS_MIF_OFFSET + 0x120)
#define MIF_CH9_OFFSET	(DSS_MIF_OFFSET + 0x140)

#define MIF_CTRL0	(0x000)
#define MIF_CTRL1	(0x004)
#define MIF_CTRL2	(0x008)
#define MIF_CTRL3	(0x00C)
#define MIF_CTRL4	(0x010)
#define MIF_CTRL5	(0x014)

//0x0160+16*k
#define MIF_STAT0	(0x0160)
//0x0164+16*k
#define MIF_STAT1	(0x0164)
//0x0168+16*k
#define MIF_STAT2	(0x0168)

#define MIF_ENABLE	(0x0000)
#define MIF_MEM_CTRL	(0x0004)
#define REG_DEFAULT (0x0500)
#define MIF_SHADOW_READ	(0x0504)
#define MIF_CLK_CTL	(0x0508)

#define MIF_CTRL_OFFSET	(0x20)
#define MIF_CTRL_NUM	(10)

#define LITTLE_LAYER_BUF_SIZE	(256 * 1024)
#define MIF_STRIDE_UNIT (4 * 1024)

typedef struct dss_mif {
	uint32_t mif_ctrl1;
	uint32_t mif_ctrl2;
	uint32_t mif_ctrl3;
	uint32_t mif_ctrl4;
	uint32_t mif_ctrl5;
} dss_mif_t;


/*
** stretch blt, linear/tile, rotation, pixel format
** 0 0 000
*/
enum dss_mmu_tlb_tag_org {
	MMU_TLB_TAG_ORG_0x0 = 0x0,
	MMU_TLB_TAG_ORG_0x1 = 0x1,
	MMU_TLB_TAG_ORG_0x2 = 0x2,
	MMU_TLB_TAG_ORG_0x3 = 0x3,
	MMU_TLB_TAG_ORG_0x4 = 0x4,
	MMU_TLB_TAG_ORG_0x7 = 0x7,

	MMU_TLB_TAG_ORG_0x8 = 0x8,
	MMU_TLB_TAG_ORG_0x9 = 0x9,
	MMU_TLB_TAG_ORG_0xA = 0xA,
	MMU_TLB_TAG_ORG_0xB = 0xB,
	MMU_TLB_TAG_ORG_0xC = 0xC,
	MMU_TLB_TAG_ORG_0xF = 0xF,

	MMU_TLB_TAG_ORG_0x10 = 0x10,
	MMU_TLB_TAG_ORG_0x11 = 0x11,
	MMU_TLB_TAG_ORG_0x12 = 0x12,
	MMU_TLB_TAG_ORG_0x13 = 0x13,
	MMU_TLB_TAG_ORG_0x14 = 0x14,
	MMU_TLB_TAG_ORG_0x17 = 0x17,

	MMU_TLB_TAG_ORG_0x18 = 0x18,
	MMU_TLB_TAG_ORG_0x19 = 0x19,
	MMU_TLB_TAG_ORG_0x1A = 0x1A,
	MMU_TLB_TAG_ORG_0x1B = 0x1B,
	MMU_TLB_TAG_ORG_0x1C = 0x1C,
	MMU_TLB_TAG_ORG_0x1F = 0x1F,
};


/*******************************************************************************
**
*/
#define SMMU_SCR	(0x0000)
#define SMMU_MEMCTRL	(0x0004)
#define SMMU_LP_CTRL	(0x0008)
#define SMMU_INTMAS_S	(0x0010)
#define SMMU_INTRAW_S	(0x0014)
#define SMMU_INTSTAT_S	(0x0018)
#define SMMU_INTCLR_S	(0x001C)
#define SMMU_INTMASK_NS	(0x0020)
#define SMMU_INTRAW_NS	(0x0024)
#define SMMU_INTSTAT_NS	(0x0028)
#define SMMU_INTCLR_NS	(0x002C)
//(0x0030+n*0x4)
#define SMMU_SMRx	(0x0030)
#define SMMU_RLD_EN0	(0x01F0)
#define SMMU_RLD_EN1	(0x01F4)
#define SMMU_SCB_SCTRL	(0x0200)
#define SMMU_CB_SCTRL	(0x0204)
#define SMMU_SCB_TTBR	(0x0208)
#define SMMU_CB_TTBR0	(0x020C)
#define SMMU_CB_TTBR1	(0x0210)
#define SMMU_SCB_TTBCR	(0x0214)
#define SMMU_CB_TTBCR	(0x0218)
#define SMMU_OFFSET_ADDR_S	(0x0220)
#define SMMU_OFFSET_ADDR_NS	(0x0224)
#define SMMU_ADDR_MSB	(0x0300)
#define SMMU_ERR_RDADDR	(0x0304)
#define SMMU_ERR_WRADDR	(0x0308)
#define SMMU_FAULT_ADDR	(0x0310)
#define SMMU_FAULT_ID	(0x0314)
#define SMMU_FAULT_INFO	(0x0318)
#define SMMU_DBGRPTR_TLB	(0x0400)
#define SMMU_DBGRDATA_TLB	(0x0404)
#define SMMU_DBGRPTR_CACHE	(0x0408)
#define SMMU_DBGRDATA0_CACHE	(0x040C)
#define SMMU_DBGRDATA1_CACHE	(0x0410)
#define SMMU_SCACHEI_ALL	(0x0414)
#define SMMU_SCACHEI_L1	(0x0418)
#define SMMU_SCACHEI_L2L3	(0x041C)
#define SMMU_OVA_ADDR	(0x0500)
#define SMMU_OPA_ADDR	(0x0504)
#define SMMU_OVA_CTRL	(0x0508)
#define SMMU_OPREF_ADDR	(0x0510)
#define SMMU_OPREF_CTRL	(0x0514)
#define SMMU_OPREF_CNT	(0x0518)


#define SMMU_SID_NUM	(64)

typedef struct dss_smmu {
	uint32_t smmu_scr;
	uint32_t smmu_memctrl;
	uint32_t smmu_lp_ctrl;
	uint32_t smmu_intmas_s;
	uint32_t smmu_intraw_s;
	uint32_t smmu_intstat_s;
	uint32_t smmu_intclr_s;
	uint32_t smmu_intmask_ns;
	uint32_t smmu_intraw_ns;
	uint32_t smmu_intstat_ns;
	uint32_t smmu_intclr_ns;
	uint32_t smmu_smrx[SMMU_SID_NUM];
	uint32_t smmu_rld_en0;
	uint32_t smmu_rld_en1;
	uint32_t smmu_scb_sctrl;
	uint32_t smmu_cb_sctrl;
	uint32_t smmu_scb_ttbr;
	uint32_t smmu_cb_ttbr0;
	uint32_t smmu_cb_ttbr1;
	uint32_t smmu_scb_ttbcr;
	uint32_t smmu_cb_ttbcr;
	uint32_t smmu_offset_addr_s;
	uint32_t smmu_offset_addr_ns;
	uint32_t smmu_addr_msb;
	uint32_t smmu_err_rdaddr;
	uint32_t smmu_err_wraddr;
	uint32_t smmu_fault_addr;
	uint32_t smmu_fault_id;
	uint32_t smmu_fault_info;
	uint32_t smmu_dbgrptr_tlb;
	uint32_t smmu_dbgrdata_tlb;
	uint32_t smmu_dbgrptr_cache;
	uint32_t smmu_dbgrdata0_cache;
	uint32_t smmu_dbgrdata1_cache;
	uint32_t smmu_scachei_all;
	uint32_t smmu_scachei_l1;
	uint32_t smmu_scachei_l2l3;
	uint32_t smmu_ova_addr;
	uint32_t smmu_opa_addr;
	uint32_t smmu_ova_ctrl;
	uint32_t smmu_opref_addr;
	uint32_t smmu_opref_ctrl;
	uint32_t smmu_opref_cnt;

	uint8_t smmu_smrx_used[DSS_CHN_MAX_DEFINE];
} dss_smmu_t;


/*******************************************************************************
** RDMA
*/

//DMA_CMN
#define DMA_OFT_X0	(0x0000)
#define DMA_OFT_Y0	(0x0004)
#define DMA_OFT_X1	(0x0008)
#define DMA_OFT_Y1	(0x000C)
#define DMA_MASK0	(0x0010)
#define DMA_MASK1	(0x0014)
#define DMA_STRETCH_SIZE_VRT	(0x0018)
#define DMA_CTRL	(0x001C)
#define DMA_TILE_SCRAM	(0x0020)

#define DMA_PULSE	(0x0028)
#define DMA_CORE_GT	(0x002C)
#define RWCH_CFG0	(0x0030)

//WDMA_CMN
#define WDMA_DMA_SW_MASK_EN	(0x004C)
#define WDMA_DMA_START_MASK0	(0x0050)
#define WDMA_DMA_END_MASK0	(0x0054)
#define WDMA_DMA_START_MASK1	(0x0058)
#define WDMA_DMA_END_MASK1	(0x005C)

//Y
#define DMA_DATA_ADDR0	(0x0060)
#define DMA_STRIDE0	(0x0064)
#define DMA_STRETCH_STRIDE0	(0x0068)
#define DMA_DATA_NUM0	(0x006C)

#define DMA_TEST0	(0x0070)
#define DMA_TEST1	(0x0074)
#define DMA_TEST3	(0x0078)
#define DMA_TEST4	(0x007C)
#define DMA_STATUS_Y	(0x0080)

//U
#define DMA_DATA_ADDR1	(0x0084)
#define DMA_STRIDE1	(0x0088)
#define DMA_STRETCH_STRIDE1	(0x008C)
#define DMA_DATA_NUM1	(0x0090)

#define DMA_TEST0_U	(0x0094)
#define DMA_TEST1_U	(0x0098)
#define DMA_TEST3_U	(0x009C)
#define DMA_TEST4_U	(0x00A0)
#define DMA_STATUS_U	(0x00A4)

//V
#define DMA_DATA_ADDR2	(0x00A8)
#define DMA_STRIDE2	(0x00AC)
#define DMA_STRETCH_STRIDE2	(0x00B0)
#define DMA_DATA_NUM2	(0x00B4)

#define DMA_TEST0_V	(0x00B8)
#define DMA_TEST1_V	(0x00BC)
#define DMA_TEST3_V	(0x00C0)
#define DMA_TEST4_V	(0x00C4)
#define DMA_STATUS_V	(0x00C8)

//CH
#define CH_RD_SHADOW	(0x00D0)
#define CH_CTL	(0x00D4)
#define CH_SECU_EN	(0x00D8)
#define CH_SW_END_REQ	(0x00DC)
#define CH_CLK_SEL	(0x00E0)
#define CH_CLK_EN	(0x00E4)

//VPP
#define VPP_CTRL	(0x0700)
#define VPP_MEM_CTRL	(0x0704)

//DMA BUF
#define DMA_BUF_CTRL	(0x0800)
#define DMA_BUF_SIZE  (0x0850)
#define DMA_BUF_MEM_CTRL	(0x0854)
#define DMA_BUF_DBG0 (0x0838)
#define DMA_BUF_DBG1 (0x083c)


//AFBCD
#define AFBCD_HREG_HDR_PTR_LO	(0x0900)
#define AFBCD_HREG_PIC_WIDTH	(0x0904)
#define AFBCD_HREG_PIC_HEIGHT	(0x090C)
#define AFBCD_HREG_FORMAT	(0x0910)
#define AFBCD_CTL		(0x0914)
#define AFBCD_STR	(0x0918)
#define AFBCD_LINE_CROP	(0x091C)
#define AFBCD_INPUT_HEADER_STRIDE	(0x0920)
#define AFBCD_PAYLOAD_STRIDE	(0x0924)
#define AFBCD_MM_BASE_0	(0x0928)
#define AFBCD_MM_BASE_1	(0x092C)
#define AFBCD_AFBCD_PAYLOAD_POINTER	(0x0930)
#define AFBCD_HEIGHT_BF_STR	(0x0934)
#define AFBCD_OS_CFG	(0x0938)
#define AFBCD_MEM_CTRL	(0x093C)
#define AFBCD_SCRAMBLE_MODE	(0x0940)
#define AFBCD_HEADER_POINTER_OFFSET	(0x0944)


//AFBCE
#define AFBCE_HREG_PIC_BLKS	(0x0900)
#define AFBCE_HREG_FORMAT	(0x0904)
#define AFBCE_HREG_HDR_PTR_LO	(0x0908)
#define AFBCE_HREG_PLD_PTR_LO	(0x090C)
#define AFBCE_PICTURE_SIZE	(0x0910)
#define AFBCE_CTL	(0x0914)
#define AFBCE_HEADER_SRTIDE	(0x0918)
#define AFBCE_PAYLOAD_STRIDE	(0x091C)
#define AFBCE_ENC_OS_CFG	(0x0920)
#define AFBCE_MEM_CTRL	(0x0924)
#define AFBCE_QOS_CFG	(0x0928)
#define AFBCE_THRESHOLD	(0x092C)
#define AFBCE_SCRAMBLE_MODE	(0x0930)
#define AFBCE_HEADER_POINTER_OFFSET	(0x0934)


//ROT
#define ROT_FIRST_LNS	(0x0530)
#define ROT_STATE	(0x0534)
#define ROT_MEM_CTRL		(0x0538)
#define ROT_SIZE	(0x053C)
#define ROT_CPU_CTL0	(0x0540)
#define ROT_CPU_START0	(0x0544)
#define ROT_CPU_ADDR0	(0x0548)
#define ROT_CPU_RDATA0	(0x054C)
#define ROT_CPU_RDATA1	(0x0550)
#define ROT_CPU_WDATA0	(0x0554)
#define ROT_CPU_WDATA1	(0x0558)
#define ROT_CPU_CTL1	(0x055C)
#define ROT_CPU_START1	(0x0560)
#define ROT_CPU_ADDR1	(0x0564)
#define ROT_CPU_RDATA2	(0x0568)
#define ROT_CPU_RDATA3	(0x056C)
#define ROT_CPU_WDATA2	(0x0570)
#define ROT_CPU_WDATA3	(0x0574)


//REG_DEFAULT
#define CH_REG_DEFAULT (0x0A00)


/* MACROS */
#define MIN_INTERLEAVE	(7)
#define MAX_TILE_SURPORT_NUM	(6)

/* DMA aligned limited:  128bits aligned */
#define DMA_ALIGN_BYTES	(128 / BITS_PER_BYTE)
#define DMA_ADDR_ALIGN	(128 / BITS_PER_BYTE)
#define DMA_STRIDE_ALIGN	(128 / BITS_PER_BYTE)

#define TILE_DMA_ADDR_ALIGN	(256 * 1024)

#define DMA_IN_WIDTH_MAX	(2048)
#define DMA_IN_HEIGHT_MAX	(8192)


#define AFBC_PIC_WIDTH_MIN	(16)
#define AFBC_PIC_WIDTH_MAX	(8192)
#define AFBC_PIC_HEIGHT_MIN	(16)
#define AFBC_PIC_HEIGHT_MAX	(8192)

#define AFBCD_TOP_CROP_MAX	(15)
#define AFBCD_BOTTOM_CROP_MAX	(15)

//16Bytes
#define AFBC_HEADER_STRIDE_BLOCK	(16)
//32BPP:1024, 16BPP 512
#define AFBC_PAYLOAD_STRIDE_BLOCK	(1024)

#define AFBC_HEADER_ADDR_ALIGN	(64)
#define AFBC_HEADER_STRIDE_ALIGN	(64)

#define AFBC_PAYLOAD_ADDR_ALIGN_32	(1024)
#define AFBC_PAYLOAD_STRIDE_ALIGN_32	(1024)
#define AFBC_PAYLOAD_ADDR_ALIGN_16	(512)
#define AFBC_PAYLOAD_STRIDE_ALIGN_16	(512)

//16Pixels
#define AFBC_BLOCK_ALIGN	(16)

#define AFBCE_IN_WIDTH_MAX	(512)
#define WROT_IN_WIDTH_MAX	(512)

#define MMBUF_BASE	(0x40) //(0xea800000)
#define MMBUF_LINE_NUM	(8)
#define MMBUF_ADDR_ALIGN	(64)

enum DSS_AFBC_HALF_BLOCK_MODE {
	AFBC_HALF_BLOCK_UPPER_LOWER_ALL = 0,
	AFBC_HALF_BLOCK_LOWER_UPPER_ALL,
	AFBC_HALF_BLOCK_UPPER_ONLY,
	AFBC_HALF_BLOCK_LOWER_ONLY,
};

typedef struct dss_rdma {
	uint32_t oft_x0;
	uint32_t oft_y0;
	uint32_t oft_x1;
	uint32_t oft_y1;
	uint32_t mask0;
	uint32_t mask1;
	uint32_t stretch_size_vrt;
	uint32_t ctrl;
	uint32_t tile_scram;

	uint32_t data_addr0;
	uint32_t stride0;
	uint32_t stretch_stride0;
	uint32_t data_num0;

	uint32_t data_addr1;
	uint32_t stride1;
	uint32_t stretch_stride1;
	uint32_t data_num1;

	uint32_t data_addr2;
	uint32_t stride2;
	uint32_t stretch_stride2;
	uint32_t data_num2;

	uint32_t ch_rd_shadow;
	uint32_t ch_ctl;

	uint32_t dma_buf_ctrl;

	uint32_t vpp_ctrl;
	uint32_t vpp_mem_ctrl;

	uint32_t afbcd_hreg_hdr_ptr_lo;
	uint32_t afbcd_hreg_pic_width;
	uint32_t afbcd_hreg_pic_height;
	uint32_t afbcd_hreg_format;
	uint32_t afbcd_ctl;
	uint32_t afbcd_str;
	uint32_t afbcd_line_crop;
	uint32_t afbcd_input_header_stride;
	uint32_t afbcd_payload_stride;
	uint32_t afbcd_mm_base_0;
	uint32_t afbcd_mm_base_1;
	uint32_t afbcd_afbcd_payload_pointer;
	uint32_t afbcd_height_bf_str;
	uint32_t afbcd_os_cfg;
	uint32_t afbcd_mem_ctrl;
	uint32_t afbcd_scramble_mode;
	uint32_t afbcd_header_pointer_offset;

	uint8_t vpp_used;
	uint8_t afbc_used;
} dss_rdma_t;

typedef struct dss_wdma {
	uint32_t oft_x0;
	uint32_t oft_y0;
	uint32_t oft_x1;
	uint32_t oft_y1;

	uint32_t mask0;
	uint32_t mask1;
	uint32_t stretch_size_vrt;
	uint32_t ctrl;
	uint32_t tile_scram;

	uint32_t sw_mask_en;
	uint32_t start_mask0;
	uint32_t end_mask0;
	uint32_t start_mask1;
	uint32_t end_mask1;

	uint32_t data_addr;
	uint32_t stride0;
	uint32_t data1_addr;
	uint32_t stride1;

	uint32_t stretch_stride;
	uint32_t data_num;

	uint32_t ch_rd_shadow;
	uint32_t ch_ctl;
	uint32_t ch_secu_en;
	uint32_t ch_sw_end_req;

	uint32_t dma_buf_ctrl;
	uint32_t dma_buf_size;

	uint32_t rot_size;

	uint32_t afbce_hreg_pic_blks;
	uint32_t afbce_hreg_format;
	uint32_t afbce_hreg_hdr_ptr_lo;
	uint32_t afbce_hreg_pld_ptr_lo;
	uint32_t afbce_picture_size;
	uint32_t afbce_ctl;
	uint32_t afbce_header_srtide;
	uint32_t afbce_payload_stride;
	uint32_t afbce_enc_os_cfg;
	uint32_t afbce_mem_ctrl;
	uint32_t afbce_qos_cfg;
	uint32_t afbce_threshold;
	uint32_t afbce_scramble_mode;
	uint32_t afbce_header_pointer_offset;

	uint8_t afbc_used;
	uint8_t rot_used;
} dss_wdma_t;


/*******************************************************************************
** DFC
*/
#define DFC_DISP_SIZE	(0x0000)
#define DFC_PIX_IN_NUM	(0x0004)
#define DFC_GLB_ALPHA	(0x0008)
#define DFC_DISP_FMT	(0x000C)
#define DFC_CLIP_CTL_HRZ	(0x0010)
#define DFC_CLIP_CTL_VRZ	(0x0014)
#define DFC_CTL_CLIP_EN	(0x0018)
#define DFC_ICG_MODULE	(0x001C)
#define DFC_DITHER_ENABLE	(0x0020)
#define DFC_PADDING_CTL	(0x0024)

typedef struct dss_dfc {
	uint32_t disp_size;
	uint32_t pix_in_num;
	uint32_t disp_fmt;
	uint32_t clip_ctl_hrz;
	uint32_t clip_ctl_vrz;
	uint32_t ctl_clip_en;
	uint32_t icg_module;
	uint32_t dither_enable;
	uint32_t padding_ctl;
} dss_dfc_t;


/*******************************************************************************
** CSC
*/
#define CSC_IDC	(0x0000)
#define CSC_ODC	(0x0004)
#define CSC_P0	(0x0008)
#define CSC_P1	(0x000C)
#define CSC_P2	(0x0010)
#define CSC_P3	(0x0014)
#define CSC_P4	(0x0018)
#define CSC_ICG_MODULE	(0x001C)

typedef struct dss_csc {
	uint32_t idc;
	uint32_t odc;
	uint32_t p0;
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;
	uint32_t p4;
	uint32_t icg_module;
} dss_csc_t;


/*******************************************************************************
** SCF
*/
#define DSS_SCF_H0_Y_COEF_OFFSET	(0x0000)
#define DSS_SCF_Y_COEF_OFFSET	(0x2000)
#define DSS_SCF_UV_COEF_OFFSET	(0x2800)

#define SCF_EN_HSCL_STR	(0x0000)
#define SCF_EN_VSCL_STR	(0x0004)
#define SCF_H_V_ORDER	(0x0008)
#define SCF_SCF_CORE_GT	(0x000C)
#define SCF_INPUT_WIDTH_HEIGHT	(0x0010)
#define SCF_OUTPUT_WIDTH_HEIGHT	(0x0014)
#define SCF_COEF_MEM_CTRL  (0x0018)
#define SCF_EN_HSCL	(0x001C)
#define SCF_EN_VSCL	(0x0020)
#define SCF_ACC_HSCL	(0x0024)
#define SCF_ACC_HSCL1	(0x0028)
#define SCF_INC_HSCL	(0x0034)
#define SCF_ACC_VSCL	(0x0038)
#define SCF_ACC_VSCL1	(0x003C)
#define SCF_INC_VSCL	(0x0048)
#define SCF_EN_NONLINEAR	(0x004C)
#define SCF_EN_MMP	(0x007C)
#define SCF_DB_H0	(0x0080)
#define SCF_DB_H1	(0x0084)
#define SCF_DB_V0	(0x0088)
#define SCF_DB_V1	(0x008C)
#define SCF_LB_MEM_CTRL	(0x0090)
#define SCF_RD_SHADOW	(0x00F0)
#define SCF_CLK_SEL	(0x00F8)
#define SCF_CLK_EN	(0x00FC)

/* MACROS */
#define SCF_MIN_INPUT	(16) //SCF min input pix 16x16
#define SCF_MIN_OUTPUT	(16) //SCF min output pix 16x16

/* Threshold for SCF Stretch and SCF filter */
#define RDMA_STRETCH_THRESHOLD	(2)
#define SCF_INC_FACTOR	(1 << 18) //(262144)
#define SCF_UPSCALE_MAX	(60)
#define SCF_DOWNSCALE_MAX	  (60)
#define SCF_EDGE_FACTOR (3)

typedef struct dss_scl {
	uint32_t en_hscl_str;
	uint32_t en_vscl_str;
	uint32_t h_v_order;
	uint32_t input_width_height;
	uint32_t output_width_height;
	uint32_t en_hscl;
	uint32_t en_vscl;
	uint32_t acc_hscl;
	uint32_t inc_hscl;
	uint32_t inc_vscl;
	uint32_t en_mmp;
	uint32_t fmt;
} dss_scl_t;

enum scl_coef_lut_idx {
	SCL_COEF_NONE_IDX = -1,
	SCL_COEF_YUV_IDX = 0,
	SCL_COEF_RGB_IDX = 1,
	SCL_COEF_IDX_MAX = 2,
};

/*******************************************************************************
** SHARPNESS
*/
#define SHARPNESS_FILT_C		(0x00)
#define SHARPNESS_MODE	(0x04)
#define SHARPNESS_GAIN	(0x08)
#define SHARPNESS_WEIGHT	(0x0C)
#define SHARPNESS_FILT_C1	(0x10)
#define SHARPNESS_FILT_C2	(0x14)
#define SHARPNESS_LINEDET	(0x18)
#define SHARPNESS_SHARPCFG	(0x1C)
#define SHARPNESS_EDGECFG	(0x20)

#define SHARPNESS_DBG0	(0x30)
#define SHARPNESS_DBG1	(0x34)
#define SHARPNESS_MEM_CTRL	(0x3C)
#define SHARPNESS_CPU_CTL	(0x40)
#define SHARPNESS_CPU_START	(0x44)
#define SHARPNESS_CPU_ADDR	(0x48)
#define SHARPNESS_CPU_RDATA0	(0x4C)
#define SHARPNESS_CPU_RDATA1	(0x50)
#define SHARPNESS_CPU_WDATA0	(0x54)
#define SHARPNESS_CPU_WDATA1	(0x58)

typedef struct dss_sharpness {
	uint32_t filt_c;
	uint32_t mode;
	uint32_t gain;
	uint32_t weight;
	uint32_t filt_c1;
	uint32_t filt_c2;
	uint32_t linedet;
	uint32_t sharpcfg;
	uint32_t edgecfg;
} dss_sharpness_t;

/*******************************************************************************
** POST_CLIP
*/
#define POST_CLIP_DISP_SIZE	(0x0000)
#define POST_CLIP_CTL_HRZ	(0x0010)
#define POST_CLIP_CTL_VRZ	(0x0014)
#define POST_CLIP_EN	(0x0018)

typedef struct dss_post_clip{
	uint32_t disp_size;
	uint32_t clip_ctl_hrz;
	uint32_t clip_ctl_vrz;
	uint32_t ctl_clip_en;
} dss_post_clip_t;


/*******************************************************************************
** CE
*/
#define CE_HIST_RESET	(0x00)
#define CE_HIST_CTL	(0x04)
#define CE_HIST_FRAME_CNT	(0x08)
#define CE_SIZE	(0x0C)
#define CE_NO_STAT_LINES	(0x10)
#define CE_BLACK_REGION_THRE	(0x14)
#define CE_WHITE_REGION_THRE	(0x18)
#define CE_LUT_SEL	(0x1C)
#define CE_LUT_ENABLE	(0x20)
#define CE_LUT_USING_IND	(0x54)
#define CE_STATE_IND	(0x58)
#define CE_MEM_CTRL	(0x5C)
//
#define CE_TOTALGRAY	(0x30)
#define CE_TOTALPIXL	(0x34)
#define CE_MEAN	(0x38)
#define CE_PEC0_3	(0x3C)
#define CE_PEC4_7	(0x40)
#define CE_PEC8	(0x44)
#define CE_BLACK_NUM	(0x48)
#define CE_WHITE_NUM	(0x4C)
#define CE_HIST_RPT_IND	(0x50)

typedef struct dss_ce {
	uint32_t hist_reset;
	uint32_t hist_ctl;
	uint32_t hist_frame_cnt;
	uint32_t size;
	uint32_t no_stat_lines;
	uint32_t black_region_thre;
	uint32_t white_region_thre;
	uint32_t lut_sel;
	uint32_t lut_enable;
	uint32_t mem_ctrl;

	uint32_t totalgray;
	uint32_t totalpixl;
	uint32_t mean;
	uint32_t pec0_3;
	uint32_t pec4_7;
	uint32_t pec8;
	uint32_t black_num;
	uint32_t white_num;
	uint32_t hist_rpt_ind;
	char __iomem *lut_base;
	uint8_t *lut_table;
} dss_ce_t;


/*******************************************************************************
** MCTL
*/
#define MCTL_CTL_EN	(0x0000)
#define MCTL_CTL_MUTEX	(0x0004)
#define MCTL_CTL_MUTEX_STATUS	(0x0008)
#define MCTL_CTL_MUTEX_ITF	(0x000C)
#define MCTL_CTL_MUTEX_DBUF	(0x0010)
#define MCTL_CTL_MUTEX_SCF	(0x0014)
#define MCTL_CTL_MUTEX_OV	(0x0018)
#define MCTL_CTL_MUTEX_WCH0	(0x0020)
#define MCTL_CTL_MUTEX_WCH1	(0x0024)
#define MCTL_CTL_MUTEX_RCH0	(0x0030)
#define MCTL_CTL_MUTEX_RCH1	(0x0034)
#define MCTL_CTL_MUTEX_RCH2	(0x0038)
#define MCTL_CTL_MUTEX_RCH3	(0x003C)
#define MCTL_CTL_MUTEX_RCH4	(0x0040)
#define MCTL_CTL_MUTEX_RCH5	(0x0044)
#define MCTL_CTL_MUTEX_RCH6	(0x0048)
#define MCTL_CTL_MUTEX_RCH7	(0x004C)
#define MCTL_CTL_TOP	(0x0050)
#define MCTL_CTL_FLUSH_STATUS	(0x0054)
#define MCTL_CTL_CLEAR	(0x0058)
#define MCTL_CTL_CACK_TOUT	(0x0060)
#define MCTL_CTL_MUTEX_TOUT	(0x0064)
#define MCTL_CTL_STATUS	(0x0068)
#define MCTL_CTL_INTEN	(0x006C)
#define MCTL_CTL_CLK_SEL	(0x0080)
#define MCTL_CTL_CLK_EN	(0x0084)
#define MCTL_CTL_DBG	(0x00E0)

#define MCTL_CTL_SECU_CFG	(0x0000)
#define MCTL_PAY_SECU_FLUSH_EN  (0x0018)
#define MCTL_CTL_SECU_GATE0	(0x0080)
#define MCTL_CTL_SECU_GATE1	(0x0084)
#define MCTL_CTL_SECU_GATE2	(0x0088)
#define MCTL_DSI0_SECU_CFG_EN	(0x00A0)
#define MCTL_DSI1_SECU_CFG_EN	(0x00A4)
#define MCTL_RCH0_FLUSH_EN	(0x0100)
#define MCTL_RCH1_FLUSH_EN	(0x0104)
#define MCTL_RCH2_FLUSH_EN	(0x0108)
#define MCTL_RCH3_FLUSH_EN	(0x010C)
#define MCTL_RCH4_FLUSH_EN	(0x0110)
#define MCTL_RCH5_FLUSH_EN	(0x0114)
#define MCTL_RCH6_FLUSH_EN	(0x0118)
#define MCTL_RCH7_FLUSH_EN	(0x011C)
#define MCTL_WCH0_FLUSH_EN	(0x0120)
#define MCTL_WCH1_FLUSH_EN	(0x0124)
#define MCTL_OV0_FLUSH_EN	(0x0128)
#define MCTL_OV1_FLUSH_EN	(0x012C)
#define MCTL_OV2_FLUSH_EN	(0x0130)
#define MCTL_OV3_FLUSH_EN	(0x0134)
#define MCTL_RCH0_OV_OEN	(0x0160)
#define MCTL_RCH1_OV_OEN	(0x0164)
#define MCTL_RCH2_OV_OEN	(0x0168)
#define MCTL_RCH3_OV_OEN	(0x016C)
#define MCTL_RCH4_OV_OEN	(0x0170)
#define MCTL_RCH5_OV_OEN	(0x0174)
#define MCTL_RCH6_OV_OEN	(0x0178)
#define MCTL_RCH7_OV_OEN	(0x017C)
#define MCTL_RCH_OV0_SEL	(0x0180)
#define MCTL_RCH_OV1_SEL	(0x0184)
#define MCTL_RCH_OV2_SEL	(0x0188)
#define MCTL_RCH_OV3_SEL	(0x018C)
#define MCTL_WCH0_OV_IEN   (0x01A0)
#define MCTL_WCH1_OV_IEN   (0x01A4)
#define MCTL_WCH_OV2_SEL   (0x01A8)
#define MCTL_WCH_OV3_SEL   (0x01AC)
#define MCTL_WB_ENC_SEL	(0x01B0)
#define MCTL_DSI_MUX_SEL	(0x01B4)
#define MCTL_RCH0_STARTY	(0x01C0)
#define MCTL_RCH1_STARTY	(0x01C4)
#define MCTL_RCH2_STARTY	(0x01C8)
#define MCTL_RCH3_STARTY	(0x01CC)
#define MCTL_RCH4_STARTY	(0x01D0)
#define MCTL_RCH5_STARTY	(0x01D4)
#define MCTL_RCH6_STARTY	(0x01D8)
#define MCTL_RCH7_STARTY	(0x01DC)
#define MCTL_MCTL_CLK_SEL	(0x01F0)
#define MCTL_MCTL_CLK_EN	(0x01F4)
#define MCTL_MOD_CLK_SEL	(0x01F8)
#define MCTL_MOD_CLK_EN	(0x01FC)

#define MCTL_MOD0_DBG	(0x0200)
#define MCTL_MOD1_DBG	(0x0204)
#define MCTL_MOD2_DBG	(0x0208)
#define MCTL_MOD3_DBG	(0x020C)
#define MCTL_MOD4_DBG	(0x0210)
#define MCTL_MOD5_DBG	(0x0214)
#define MCTL_MOD6_DBG	(0x0218)
#define MCTL_MOD7_DBG	(0x021C)
#define MCTL_MOD8_DBG	(0x0220)
#define MCTL_MOD9_DBG	(0x0224)
#define MCTL_MOD10_DBG	(0x0228)
#define MCTL_MOD11_DBG	(0x022C)
#define MCTL_MOD12_DBG	(0x0230)
#define MCTL_MOD13_DBG	(0x0234)
#define MCTL_MOD14_DBG	(0x0238)
#define MCTL_MOD15_DBG	(0x023C)
#define MCTL_MOD16_DBG	(0x0240)
#define MCTL_MOD17_DBG	(0x0244)
#define MCTL_MOD18_DBG	(0x0248)
#define MCTL_MOD0_STATUS	(0x0250)
#define MCTL_MOD1_STATUS	(0x0254)
#define MCTL_MOD2_STATUS	(0x0258)
#define MCTL_MOD3_STATUS	(0x025C)
#define MCTL_MOD4_STATUS	(0x0260)
#define MCTL_MOD5_STATUS	(0x0264)
#define MCTL_MOD6_STATUS	(0x0268)
#define MCTL_MOD7_STATUS	(0x026C)
#define MCTL_MOD8_STATUS	(0x0270)
#define MCTL_MOD9_STATUS	(0x0274)
#define MCTL_MOD10_STATUS	(0x0278)
#define MCTL_MOD11_STATUS	(0x027C)
#define MCTL_MOD12_STATUS	(0x0280)
#define MCTL_MOD13_STATUS	(0x0284)
#define MCTL_MOD14_STATUS	(0x0288)
#define MCTL_MOD15_STATUS	(0x028C)
#define MCTL_MOD16_STATUS	(0x0290)
#define MCTL_MOD17_STATUS	(0x0294)
#define MCTL_MOD18_STATUS	(0x0298)
#define MCTL_SW_DBG	(0x02B0)
#define MCTL_SW0_STATUS0	(0x02B4)
#define MCTL_SW0_STATUS1	(0x02B8)
#define MCTL_SW0_STATUS2	(0x02BC)
#define MCTL_SW0_STATUS3	(0x02C0)
#define MCTL_SW0_STATUS4	(0x02C4)
#define MCTL_SW0_STATUS5	(0x02C8)
#define MCTL_SW0_STATUS6	(0x02D0)
#define MCTL_SW0_STATUS7	(0x02D4)
#define MCTL_SW1_STATUS	(0x02D8)


//RCH
#define MCTL_MOD_DBG_RCH_NUM (10)
#define MCTL_MOD_DBG_OV_NUM (4)
#define MCTL_MOD_DBG_DBUF_NUM (2)
#define MCTL_MOD_DBG_SCF_NUM (1)
#define MCTL_MOD_DBG_ITF_NUM (2)


typedef struct dss_mctl {
	uint32_t ctl_mutex_itf;
	uint32_t ctl_mutex_dbuf;
	uint32_t ctl_mutex_scf;
	uint32_t ctl_mutex_ov;
} dss_mctl_t;

typedef struct dss_mctl_ch_base {
	char __iomem *chn_mutex_base;
	char __iomem *chn_flush_en_base;
	char __iomem *chn_ov_en_base;
	char __iomem *chn_starty_base;
	char __iomem *chn_mod_dbg_base;
} dss_mctl_ch_base_t;

typedef struct dss_mctl_ch {
	uint32_t chn_mutex;
	uint32_t chn_flush_en;
	uint32_t chn_ov_oen;
	uint32_t chn_starty;
	uint32_t chn_mod_dbg;
} dss_mctl_ch_t;

typedef struct dss_mctl_sys {
	uint32_t ov_flush_en[DSS_OVL_IDX_MAX];
	uint32_t chn_ov_sel[DSS_OVL_IDX_MAX];
	uint32_t wchn_ov_sel[DSS_WCH_MAX];
	uint8_t ov_flush_en_used[DSS_OVL_IDX_MAX];
	uint8_t chn_ov_sel_used[DSS_OVL_IDX_MAX];
	uint8_t wch_ov_sel_used[DSS_WCH_MAX];
} dss_mctl_sys_t;


/*******************************************************************************
** OVL
*/
#define OVL_SIZE	(0x0000)
#define OVL_BG_COLOR	(0x4)
#define OVL_DST_STARTPOS	(0x8)
#define OVL_DST_ENDPOS	(0xC)
#define OVL_GCFG	(0x10)
#define OVL_LAYER0_POS	(0x14)
#define OVL_LAYER0_SIZE	(0x18)
#define OVL_LAYER0_SRCLOKEY	(0x1C)
#define OVL_LAYER0_SRCHIKEY	(0x20)
#define OVL_LAYER0_DSTLOKEY	(0x24)
#define OVL_LAYER0_DSTHIKEY	(0x28)
#define OVL_LAYER0_PATTERN	(0x2C)
#define OVL_LAYER0_ALPHA	(0x30)
#define OVL_LAYER0_CFG	(0x34)
#define OVL_LAYER0_INFO_ALPHA	(0x40)
#define OVL_LAYER0_INFO_SRCCOLOR	(0x44)
#define OVL_LAYER1_POS	(0x50)
#define OVL_LAYER1_SIZE	(0x54)
#define OVL_LAYER1_SRCLOKEY	(0x58)
#define OVL_LAYER1_SRCHIKEY	(0x5C)
#define OVL_LAYER1_DSTLOKEY	(0x60)
#define OVL_LAYER1_DSTHIKEY	(0x64)
#define OVL_LAYER1_PATTERN	(0x68)
#define OVL_LAYER1_ALPHA	(0x6C)
#define OVL_LAYER1_CFG	(0x70)
#define OVL_LAYER1_INFO_ALPHA	(0x7C)
#define OVL_LAYER1_INFO_SRCCOLOR	(0x80)
#define OVL_LAYER2_POS	(0x8C)
#define OVL_LAYER2_SIZE	(0x90)
#define OVL_LAYER2_SRCLOKEY	(0x94)
#define OVL_LAYER2_SRCHIKEY	(0x98)
#define OVL_LAYER2_DSTLOKEY	(0x9C)
#define OVL_LAYER2_DSTHIKEY	(0xA0)
#define OVL_LAYER2_PATTERN	(0xA4)
#define OVL_LAYER2_ALPHA	(0xA8)
#define OVL_LAYER2_CFG	(0xAC)
#define OVL_LAYER2_INFO_ALPHA	(0xB8)
#define OVL_LAYER2_INFO_SRCCOLOR	(0xBC)
#define OVL_LAYER3_POS	(0xC8)
#define OVL_LAYER3_SIZE	(0xCC)
#define OVL_LAYER3_SRCLOKEY	(0xD0)
#define OVL_LAYER3_SRCHIKEY	(0xD4)
#define OVL_LAYER3_DSTLOKEY	(0xD8)
#define OVL_LAYER3_DSTHIKEY	(0xDC)
#define OVL_LAYER3_PATTERN	(0xE0)
#define OVL_LAYER3_ALPHA	(0xE4)
#define OVL_LAYER3_CFG	(0xE8)
#define OVL_LAYER3_INFO_ALPHA	(0xF4)
#define OVL_LAYER3_INFO_SRCCOLOR	(0xF8)
#define OVL_LAYER4_POS	(0x104)
#define OVL_LAYER4_SIZE	(0x108)
#define OVL_LAYER4_SRCLOKEY	(0x10C)
#define OVL_LAYER4_SRCHIKEY	(0x110)
#define OVL_LAYER4_DSTLOKEY	(0x114)
#define OVL_LAYER4_DSTHIKEY	(0x118)
#define OVL_LAYER4_PATTERN	(0x11C)
#define OVL_LAYER4_ALPHA	(0x120)
#define OVL_LAYER4_CFG	(0x124)
#define OVL_LAYER4_INFO_ALPHA	(0x130)
#define OVL_LAYER4_INFO_SRCCOLOR	(0x134)
#define OVL_LAYER5_POS	(0x140)
#define OVL_LAYER5_SIZE	(0x144)
#define OVL_LAYER5_SRCLOKEY	(0x148)
#define OVL_LAYER5_SRCHIKEY	(0x14C)
#define OVL_LAYER5_DSTLOKEY	(0x150)
#define OVL_LAYER5_DSTHIKEY	(0x154)
#define OVL_LAYER5_PATTERN	(0x158)
#define OVL_LAYER5_ALPHA	(0x15C)
#define OVL_LAYER5_CFG	(0x160)
#define OVL_LAYER5_INFO_ALPHA	(0x16C)
#define OVL_LAYER5_INFO_SRCCOLOR	(0x170)
#define OVL_LAYER6_POS	(0x14)
#define OVL_LAYER6_SIZE	(0x18)
#define OVL_LAYER6_SRCLOKEY	(0x1C)
#define OVL_LAYER6_SRCHIKEY	(0x20)
#define OVL_LAYER6_DSTLOKEY	(0x24)
#define OVL_LAYER6_DSTHIKEY	(0x28)
#define OVL_LAYER6_PATTERN	(0x2C)
#define OVL_LAYER6_ALPHA	(0x30)
#define OVL_LAYER6_CFG	(0x34)
#define OVL_LAYER6_INFO_ALPHA	(0x40)
#define OVL_LAYER6_INFO_SRCCOLOR	(0x44)
#define OVL_LAYER7_POS	(0x50)
#define OVL_LAYER7_SIZE	(0x54)
#define OVL_LAYER7_SRCLOKEY	(0x58)
#define OVL_LAYER7_SRCHIKEY	(0x5C)
#define OVL_LAYER7_DSTLOKEY	(0x60)
#define OVL_LAYER7_DSTHIKEY	(0x64)
#define OVL_LAYER7_PATTERN	(0x68)
#define OVL_LAYER7_ALPHA	(0x6C)
#define OVL_LAYER7_CFG	(0x70)
#define OVL_LAYER7_INFO_ALPHA	(0x7C)
#define OVL_LAYER7_INFO_SRCCOLOR	(0x80)
#define OVL_LAYER0_ST_INFO	(0x48)
#define OVL_LAYER1_ST_INFO	(0x84)
#define OVL_LAYER2_ST_INFO	(0xC0)
#define OVL_LAYER3_ST_INFO	(0xFC)
#define OVL_LAYER4_ST_INFO	(0x138)
#define OVL_LAYER5_ST_INFO	(0x174)
#define OVL_LAYER6_ST_INFO	(0x48)
#define OVL_LAYER7_ST_INFO	(0x84)
#define OVL_LAYER0_IST_INFO	(0x4C)
#define OVL_LAYER1_IST_INFO	(0x88)
#define OVL_LAYER2_IST_INFO	(0xC4)
#define OVL_LAYER3_IST_INFO	(0x100)
#define OVL_LAYER4_IST_INFO	(0x13C)
#define OVL_LAYER5_IST_INFO	(0x178)
#define OVL_LAYER6_IST_INFO	(0x4C)
#define OVL_LAYER7_IST_INFO	(0x88)
#define OVL_LAYER0_PSPOS	(0x38)
#define OVL_LAYER0_PEPOS	(0x3C)
#define OVL_LAYER1_PSPOS	(0x74)
#define OVL_LAYER1_PEPOS	(0x78)
#define OVL_LAYER2_PSPOS	(0xB0)
#define OVL_LAYER2_PEPOS	(0xB4)
#define OVL_LAYER3_PSPOS	(0xEC)
#define OVL_LAYER3_PEPOS	(0xF0)
#define OVL_LAYER4_PSPOS	(0x128)
#define OVL_LAYER4_PEPOS	(0x12C)
#define OVL_LAYER5_PSPOS	(0x164)
#define OVL_LAYER5_PEPOS	(0x168)
#define OVL_LAYER6_PSPOS	(0x38)
#define OVL_LAYER6_PEPOS	(0x3C)
#define OVL_LAYER7_PSPOS	(0x74)
#define OVL_LAYER7_PEPOS	(0x78)

#define OVL6_BASE_ST_INFO	(0x17C)
#define OVL6_BASE_IST_INFO	(0x180)
#define OVL6_GATE_CTRL	(0x184)
#define OVL6_RD_SHADOW_SEL	(0x188)
#define OVL6_OV_CLK_SEL	(0x18C)
#define OVL6_OV_CLK_EN	(0x190)
#define OVL6_BLOCK_SIZE	(0x1A0)
#define OVL6_BLOCK_DBG	(0x1A4)
#define OVL6_REG_DEFAULT	(0x1A8)

#define OVL2_BASE_ST_INFO	(0x8C)
#define OVL2_BASE_IST_INFO	(0x90)
#define OVL2_GATE_CTRL	(0x94)
#define OVL2_OV_RD_SHADOW_SEL	(0x98)
#define OVL2_OV_CLK_SEL	(0x9C)
#define OVL2_OV_CLK_EN	(0xA0)
#define OVL2_BLOCK_SIZE	(0xB0)
#define OVL2_BLOCK_DBG	(0xB4)
#define OVL2_REG_DEFAULT	(0xB8)


/* LAYER0_CFG */
#define BIT_OVL_LAYER_SRC_CFG	BIT(8)
#define BIT_OVL_LAYER_ENABLE	BIT(0)

/* LAYER0_INFO_ALPHA */
#define BIT_OVL_LAYER_SRCALPHA_FLAG	BIT(3)
#define BIT_OVL_LAYER_DSTALPHA_FLAG	BIT(2)

/* LAYER0_INFO_SRCCOLOR */
#define BIT_OVL_LAYER_SRCCOLOR_FLAG	BIT(0)


#define OVL_6LAYER_NUM		(6)
#define OVL_2LAYER_NUM		(2)


typedef struct dss_ovl_layer {
	uint32_t layer_pos;
	uint32_t layer_size	;
	uint32_t layer_pattern;
	uint32_t layer_alpha;
	uint32_t layer_cfg;

} dss_ovl_layer_t;

typedef struct dss_ovl_layer_pos {
	uint32_t layer_pspos;
	uint32_t layer_pepos;

} dss_ovl_layer_pos_t;

typedef struct dss_ovl {
	uint32_t ovl_size;
	uint32_t ovl_bg_color;
	uint32_t ovl_dst_startpos;
	uint32_t ovl_dst_endpos;
	uint32_t ovl_gcfg;
	uint32_t ovl_block_size;
	dss_ovl_layer_t ovl_layer[OVL_6LAYER_NUM];
	dss_ovl_layer_pos_t ovl_layer_pos[OVL_6LAYER_NUM];
	uint8_t ovl_layer_used[OVL_6LAYER_NUM];
} dss_ovl_t;

typedef struct dss_ovl_alpha {
	uint32_t src_amode;
	uint32_t src_gmode;
	uint32_t alpha_offsrc;
	uint32_t src_lmode;
	uint32_t src_pmode;

	uint32_t alpha_smode;

	uint32_t dst_amode;
	uint32_t dst_gmode;
	uint32_t alpha_offdst;
	uint32_t dst_pmode;

	uint32_t fix_mode;
} dss_ovl_alpha_t;


/*******************************************************************************
** DBUF
*/
#define DBUF_FRM_SIZE	(0x0000)
#define DBUF_FRM_HSIZE	(0x0004)
#define DBUF_SRAM_VALID_NUM	(0x0008)
#define DBUF_WBE_EN	(0x000C)
#define DBUF_THD_FILL_LEV0	(0x0010)
#define DBUF_DFS_FILL_LEV1	(0x0014)
#define DBUF_THD_RQOS	(0x0018)
#define DBUF_THD_WQOS	(0x001C)
#define DBUF_THD_CG	(0x0020)
#define DBUF_THD_OTHER	(0x0024)
#define DBUF_FILL_LEV0_CNT	(0x0028)
#define DBUF_FILL_LEV1_CNT	(0x002C)
#define DBUF_FILL_LEV2_CNT	(0x0030)
#define DBUF_FILL_LEV3_CNT	(0x0034)
#define DBUF_FILL_LEV4_CNT	(0x0038)
#define DBUF_ONLINE_FILL_LEVEL	(0x003C)
#define DBUF_WB_FILL_LEVEL	(0x0040)
#define DBUF_DFS_STATUS	(0x0044)
#define DBUF_THD_FLUX_REQ (0x0048)
#define DBUF_DFS_LP_CTRL	(0x004C)
#define DBUF_RD_SHADOW_SEL	(0x0050)
#define DBUF_MEM_CTRL	(0x0054)
#define DBUF_PM_CTRL	(0x0058)
#define DBUF_CLK_SEL	(0x005C)
#define DBUF_CLK_EN  	(0x0060)
#define DBUF_REG_DEFAULT  (0x00A4)


/*******************************************************************************
** SBL
*/
#define SBL_DATA_FORMAT	(0x0000)
#define SBL_CONTROL_REG1	(0x0004)
#define SBL_HS_POS_L	(0x0008)
#define SBL_HS_POS_H	(0x000C)
#define SBL_FRAME_WIDTH_L	(0x0010)
#define SBL_FRAME_WIDTH_H	(0x0014)
#define SBL_FRAME_HEIGHT_L	(0x0018)
#define SBL_FRAME_HEIGHT_H	(0x001C)
#define SBL_VS_POS_L	(0x0020)
#define SBL_VS_POS_H	(0x0024)
#define SBL_ENABLE	(0x0400)
#define SBL_STRENGTH	(0x0408)
#define SBL_VARIANCE_INTENSITY_SPACE	(0x040C)
#define SBL_SLOPE_MAX	(0x0410)
#define SBL_SLOPE_MIN	(0x0414)
#define SBL_BLACK_LEVEL_L	(0x0418)
#define SBL_BLACK_LEVEL_H	(0x041C)
#define SBL_WHITE_LEVEL_L	(0x0420)
#define SBL_WHITE_LEVEL_H	(0x0424)
#define SBL_BRIGHT_DARK_AMP_LIMIT	(0x0428)
#define SBL_DITHER_MODE	(0x042C)
#define SBL_CONFIG_BUFFER_MODE	(0x0430)
#define SBL_CONFIG_BUFFER_GLOBAL	(0x0434)
#define SBL_ASYMMETRY_LUT_ADDR	(0x0480)
#define SBL_ASYMMETRY_LUT_WRITE_DATA_L	(0x0484)
#define SBL_ASYMMETRY_LUT_WRITE_DATA_H		(0x0488)
#define SBL_COLOR_CORRECTION_LUT_ADDR	(0x04C0)
#define SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L	(0x04C4)
#define SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H	(0x04C8)
#define SBL_LOGO_LEFT	(0x0800)
#define SBL_LOGO_TOP	(0x0804)
#define SBL_APICAL_DITHER	(0x0840)
#define SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL	(0x0C00)
#define SBL_STRENGTH_MANUAL	(0x0C04)
#define SBL_DRC_IN_L	(0x0C08)
#define SBL_DRC_IN_H	(0x0C0C)
#define SBL_BACKLIGHT_L	(0x0C10)
#define SBL_BACKLIGHT_H	(0x0C14)
#define SBL_AMBIENT_LIGHT_L	(0x0C18)
#define SBL_AMBIENT_LIGHT_H	(0x0C1C)
#define SBL_START_CALC	(0x0C20)
#define SBL_STRENGTH_LIMIT	(0x0C24)
#define SBL_CALIBRATION_A_L	(0x0C28)
#define SBL_CALIBRATION_A_H	(0x0C2C)
#define SBL_CALIBRATION_B_L	(0x0C30)
#define SBL_CALIBRATION_B_H	(0x0C34)
#define SBL_CALIBRATION_C_L	(0x0C38)
#define SBL_CALIBRATION_C_H	(0x0C3C)
#define SBL_CALIBRATION_D_L	(0x0C40)
#define SBL_CALIBRATION_D_H	(0x0C44)
#define SBL_T_FILTER_CONTROL	(0x0C48)
#define SBL_BACKLIGHT_MIN_L	(0x0C4C)
#define SBL_BACKLIGHT_MIN_H	(0x0C50)
#define SBL_BACKLIGHT_MAX_L	(0x0C54)
#define SBL_BACKLIGHT_MAX_H	(0x0C58)
#define SBL_BACKLIGHT_SCALE_L	(0x0C5C)
#define SBL_BACKLIGHT_SCALE_H	(0x0C60)
#define SBL_AMBIENT_LIGHT_MIN_L	(0x0C64)
#define SBL_AMBIENT_LIGHT_MIN_H	(0x0C68)
#define SBL_FILTER_A_L	(0x0C6C)
#define SBL_FILTER_A_H	(0x0C70)
#define SBL_FILTER_B	(0x0C74)
#define SBL_STRENGTH_OUT	(0x0C80)
#define SBL_DRC_OUT_L	(0x0C84)
#define SBL_DRC_OUT_H	(0x0C88)
#define SBL_BACKLIGHT_OUT_L	(0x0C8C)
#define SBL_BACKLIGHT_OUT_H	(0x0C90)
#define SBL_CALC_DONE	(0x0C94)
#define SBL_AL_CALIB_LUT_LUT_ADDR	(0x0F00)
#define SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L	(0x0F10)
#define SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H	(0x0F14)
#define SBL_MEM_CTRL	(0x0F18)
#define SBL_CLK_SEL	(0x0F1C)
#define SBL_CLK_EN	(0x0F20)


typedef struct dss_sbl {
	int sbl_backlight_l;
	int sbl_backlight_h;
	int sbl_ambient_light_l;
	int sbl_ambient_light_h;
	int sbl_calibration_a_l;
	int sbl_calibration_a_h;
	int sbl_calibration_b_l;
	int sbl_calibration_b_h;
	int sbl_calibration_c_l;
	int sbl_calibration_c_h;
	int sbl_calibration_d_l;
	int sbl_calibration_d_h;
	int sbl_enable;
} dss_sbl_t;


/*******************************************************************************
** DPP
*/
#define DPP_RD_SHADOW_SEL	(0x0000)

#define DPP_ID	(0x0004)
#define DPP_IMG_HRZ	(0x0008)
#define DPP_IMG_VRT	(0x000C)
#define DPP_CLRBAR_CTRL	(0x0010)
#define DPP_DITHER	(0x0014)
#define DPP_SBL	(0x0018)
#define DPP_CLK_SEL	(0x01C)
#define DPP_CLK_EN	(0x020)
#define DPP_DBG_CNT	(0x024)
#define DPP_DBG	(0x314)

//ACM
#define ACM_R0_H	(0x000)
#define ACM_R1_H	(0x004)
#define ACM_R2_H	(0x008)
#define ACM_R3_H	(0x00C)
#define ACM_R4_H	(0x010)
#define ACM_R5_H	(0x014)
#define ACM_R6_H	(0x018)
#define ACM_EN	(0x01C)
#define ACM_MEM_CTRL	(0x020)
//ACM LUT
#define ACM_LUT_HUE	(0x1000)
//#define ACM_LUT_VALUE
#define ACM_LUT_SATA	(0x1A00)
#define ACM_LUT_SATR	(0x1C00)

//ACM_CE
#define ACM_CE_HIST_RESET	(0x030)
#define ACM_CE_HIST_CTL	(0x034)
#define ACM_CE_HIST_FRAME_CNT	(0x038)
#define ACM_CE_SIZE	(0x03c)
#define ACM_CE_NO_STAT_LINES	(0x040)
#define ACM_CE_BLACK_REGION_THRE	(0x044)
#define ACM_CE_WHITE_REGION_THRE	(0x048)
#define ACM_CE_LUT_SEL	(0x04c)
#define ACM_CE_LUT_ENABLE	(0x050)
#define ACM_CE_LUT_USING_IND	(0x054)
#define ACM_CE_STATE_IND	(0x058)
#define ACM_CE_MEM_CTRL0	(0x05C)
#define ACM_CE_MEM_CTRL1	(0x060)

#define ACM_CE_TOTALGRAY	(0x064)
#define ACM_CE_TOTALPIXL	(0x068)
#define ACM_CE_MEAN	(0x06c)
#define ACM_CE_PEC0_3	(0x070)
#define ACM_CE_PEC4_7	(0x074)
#define ACM_CE_PEC8	(0x078)
#define ACM_CE_BLACK_NUM	(0x07c)
#define ACM_CE_WHITE_NUM	(0x080)
#define ACM_CE_HIST_RPT_IND	(0x084)

#define ACM_CE_HIST_RPT0_OFFSET	(0x2000)
#define ACM_CE_HIST_RPT1_OFFSET	(0x2400)
#define ACM_CE_LUT0_OFFSET	(0x2800)
#define ACM_CE_LUT1_OFFSET	(0x2c00)

//IGM
#define IGM_MEM_CTRL	(0x0138)

#define LUT_IGM_R_COEF_OFFSET     (0xB000)
#define LUT_IGM_G_COEF_OFFSET     (0xB400)
#define LUT_IGM_B_COEF_OFFSET     (0xB800)

//GMP
#define LCP_GMP_BYPASS_EN	(0x0130)
#define GMP_MEM_CTRL	(0x013C)

#define LUT_GMP_COEF_OFFSET	(0x3000)

//XCC
#define LCP_XCC_COEF_00	(0x000)
#define LCP_XCC_COEF_01	(0x004)
#define LCP_XCC_COEF_02	(0x008)
#define LCP_XCC_COEF_03	(0x00C)
#define LCP_XCC_COEF_10	(0x010)
#define LCP_XCC_COEF_11	(0x014)
#define LCP_XCC_COEF_12	(0x018)
#define LCP_XCC_COEF_13	(0x01C)
#define LCP_XCC_COEF_20	(0x020)
#define LCP_XCC_COEF_21	(0x024)
#define LCP_XCC_COEF_22	(0x028)
#define LCP_XCC_COEF_23	(0x02C)
#define LCP_XCC_BYPASS_EN	(0x034)

//GAMA
#define GAMA_SHORTBIT_EN	(0x000)
#define GAMA_BYPASS_EN	(0x004)
#define GAMA_MEM_CTRL	(0x008)
#define GAMA_REG_DEFAULT	(0x00c)
//GAMA LUT
#define LUT_GAMA_R_COEF_OFFSET	(0x0400)
#define LUT_GAMA_G_COEF_OFFSET	(0x0800)
#define LUT_GAMA_B_COEF_OFFSET	(0x0C00)


/*******************************************************************************
** IFBC
*/
#define IFBC_SIZE	(0x0000)
#define IFBC_CTRL	(0x0004)
#define IFBC_HIMAX_CTRL0	(0x0008)
#define IFBC_HIMAX_CTRL1	(0x000C)
#define IFBC_HIMAX_CTRL2	(0x0010)
#define IFBC_HIMAX_CTRL3	(0x0014)
#define IFBC_EN	(0x0018)
#define IFBC_MEM_CTRL	(0x001C)
#define IFBC_INSERT	(0x0020)
#define IFBC_HIMAX_TEST_MODE	(0x0024)
#define IFBC_CORE_GT	(0x0028)
#define IFBC_PM_CTRL	(0x002C)
#define IFBC_RD_SHADOW	(0x0030)
#define IFBC_ORISE_CTL	(0x0034)
#define IFBC_ORSISE_DEBUG0	(0x0038)
#define IFBC_ORSISE_DEBUG1	(0x003C)
#define IFBC_RSP_COMP_TEST	(0x0040)
#define IFBC_CLK_SEL	(0x044)
#define IFBC_CLK_EN	(0x048)
#define IFBC_PAD	(0x004C)
#define IFBC_REG_DEFAULT	(0x0050)


/*******************************************************************************
** DSC
*/
#define DSC_VERSION	(0x0000)
#define DSC_PPS_IDENTIFIER	(0x0004)
#define DSC_EN	(0x0008)
#define DSC_CTRL	(0x000C)
#define DSC_PIC_SIZE	(0x0010)
#define DSC_SLICE_SIZE	(0x0014)
#define DSC_CHUNK_SIZE	(0x0018)
#define DSC_INITIAL_DELAY	(0x001C)
#define DSC_RC_PARAM0	(0x0020)
#define DSC_RC_PARAM1	(0x0024)
#define DSC_RC_PARAM2	(0x0028)
#define DSC_RC_PARAM3	(0x002C)
#define DSC_FLATNESS_QP_TH	(0x0030)
#define DSC_RC_PARAM4	(0x0034)
#define DSC_RC_PARAM5	(0x0038)
#define DSC_RC_BUF_THRESH0	(0x003C)
#define DSC_RC_BUF_THRESH1	(0x0040)
#define DSC_RC_BUF_THRESH2	(0x0044)
#define DSC_RC_BUF_THRESH3	(0x0048)
#define DSC_RC_RANGE_PARAM0	(0x004C)
#define DSC_RC_RANGE_PARAM1	(0x0050)
#define DSC_RC_RANGE_PARAM2	(0x0054)
#define DSC_RC_RANGE_PARAM3	(0x0058)
#define DSC_RC_RANGE_PARAM4	(0x005C)
#define DSC_RC_RANGE_PARAM5	(0x0060)
#define DSC_RC_RANGE_PARAM6	(0x0064)
#define DSC_RC_RANGE_PARAM7	(0x0068)
#define DSC_ADJUSTMENT_BITS	(0x006C)
#define DSC_BITS_PER_GRP	(0x0070)
#define DSC_MULTI_SLICE_CTL	(0x0074)
#define DSC_OUT_CTRL	(0x0078)
#define DSC_CLK_SEL	(0x007C)
#define DSC_CLK_EN	(0x0080)
#define DSC_MEM_CTRL	(0x0084)
#define DSC_ST_DATAIN	(0x0088)
#define DSC_ST_DATAOUT	(0x008C)
#define DSC0_ST_SLC_POS	(0x0090)
#define DSC1_ST_SLC_POS	(0x0094)
#define DSC0_ST_PIC_POS	(0x0098)
#define DSC1_ST_PIC_POS	(0x009C)
#define DSC0_ST_FIFO	(0x00A0)
#define DSC1_ST_FIFO	(0x00A4)
#define DSC0_ST_LINEBUF	(0x00A8)
#define DSC1_ST_LINEBUF	(0x00AC)
#define DSC_ST_ITFC	(0x00B0)
#define DSC_RD_SHADOW_SEL	(0x00B4)
#define DSC_REG_DEFAULT	(0x00B8)


/*******************************************************************************
** LDI
*/
#define LDI_DPI0_HRZ_CTRL0	(0x0000)
#define LDI_DPI0_HRZ_CTRL1	(0x0004)
#define LDI_DPI0_HRZ_CTRL2	(0x0008)
#define LDI_VRT_CTRL0	(0x000C)
#define LDI_VRT_CTRL1	(0x0010)
#define LDI_VRT_CTRL2	(0x0014)
#define LDI_PLR_CTRL	(0x0018)
#define LDI_SH_MASK_INT	(0x001C)
#define LDI_3D_CTRL	(0x0020)
#define LDI_CTRL	(0x0024)
#define LDI_WORK_MODE	(0x0028)
#define LDI_DE_SPACE_LOW	(0x002C)
#define LDI_DSI_CMD_MOD_CTRL	(0x0030)
#define LDI_DSI_TE_CTRL	(0x0034)
#define LDI_DSI_TE_HS_NUM	(0x0038)
#define LDI_DSI_TE_HS_WD	(0x003C)
#define LDI_DSI_TE_VS_WD	(0x0040)
#define LDI_FRM_MSK	(0x0044)
#define LDI_FRM_MSK_UP	(0x0048)
#define LDI_VINACT_MSK_LEN	(0x0050)
#define LDI_CMD_EVENT_SEL	(0x0060)
#define LDI_SRAM_LP_CTRL	(0x0064)
#define LDI_ITF_RD_SHADOW	(0x006C)
#define LDI_DPI1_HRZ_CTRL0	(0x00F0)
#define LDI_DPI1_HRZ_CTRL1	(0x00F4)
#define LDI_DPI1_HRZ_CTRL2	(0x00F8)
#define LDI_OVERLAP_SIZE	(0x00FC)
#define LDI_MEM_CTRL	(0x0100)
#define LDI_PM_CTRL	(0x0104)
#define LDI_CLK_SEL	(0x0108)
#define LDI_CLK_EN	(0x010C)
#define LDI_IF_BYPASS	(0x0110)
#define LDI_FRM_VALID_DBG (0x0118)


/*******************************************************************************
** MIPI DSI
*/
#define DSS_MIPI_DSI0_OFFSET	(0x00001000)
#define DSS_MIPI_DSI1_OFFSET	(0x00001400)

#define MIPIDSI_VERSION_OFFSET	(0x0000)
#define MIPIDSI_PWR_UP_OFFSET	(0x0004)
#define MIPIDSI_CLKMGR_CFG_OFFSET	(0x0008)
#define MIPIDSI_DPI_VCID_OFFSET	(0x000c)
#define MIPIDSI_DPI_COLOR_CODING_OFFSET	(0x0010)
#define MIPIDSI_DPI_CFG_POL_OFFSET	(0x0014)
#define MIPIDSI_DPI_LP_CMD_TIM_OFFSET	(0x0018)
#define MIPIDSI_PCKHDL_CFG_OFFSET	(0x002c)
#define MIPIDSI_GEN_VCID_OFFSET	(0x0030)
#define MIPIDSI_MODE_CFG_OFFSET	(0x0034)
#define MIPIDSI_VID_MODE_CFG_OFFSET	(0x0038)
#define MIPIDSI_VID_PKT_SIZE_OFFSET	(0x003c)
#define MIPIDSI_VID_NUM_CHUNKS_OFFSET	(0x0040)
#define MIPIDSI_VID_NULL_SIZE_OFFSET	(0x0044)
#define MIPIDSI_VID_HSA_TIME_OFFSET	(0x0048)
#define MIPIDSI_VID_HBP_TIME_OFFSET	(0x004c)
#define MIPIDSI_VID_HLINE_TIME_OFFSET	(0x0050)
#define MIPIDSI_VID_VSA_LINES_OFFSET	(0x0054)
#define MIPIDSI_VID_VBP_LINES_OFFSET	(0x0058)
#define MIPIDSI_VID_VFP_LINES_OFFSET	(0x005c)
#define MIPIDSI_VID_VACTIVE_LINES_OFFSET	(0x0060)
#define MIPIDSI_EDPI_CMD_SIZE_OFFSET	(0x0064)
#define MIPIDSI_CMD_MODE_CFG_OFFSET	(0x0068)
#define MIPIDSI_GEN_HDR_OFFSET	(0x006c)
#define MIPIDSI_GEN_PLD_DATA_OFFSET	(0x0070)
#define MIPIDSI_CMD_PKT_STATUS_OFFSET	(0x0074)
#define MIPIDSI_TO_CNT_CFG_OFFSET	(0x0078)
#define MIPIDSI_HS_RD_TO_CNT_OFFSET	(0x007C)
#define MIPIDSI_LP_RD_TO_CNT_OFFSET	(0x0080)
#define MIPIDSI_HS_WR_TO_CNT_OFFSET	(0x0084)
#define MIPIDSI_LP_WR_TO_CNT_OFFSET	(0x0088)
#define MIPIDSI_BTA_TO_CNT_OFFSET	(0x008C)
#define MIPIDSI_SDF_3D_OFFSET	(0x0090)
#define MIPIDSI_LPCLK_CTRL_OFFSET	(0x0094)
#define MIPIDSI_PHY_TMR_LPCLK_CFG_OFFSET	(0x0098)
#define MIPIDSI_PHY_TMR_CFG_OFFSET	(0x009c)
#define MIPIDSI_PHY_RSTZ_OFFSET	(0x00a0)
#define MIPIDSI_PHY_IF_CFG_OFFSET	(0x00a4)
#define MIPIDSI_PHY_ULPS_CTRL_OFFSET	(0x00a8)
#define MIPIDSI_PHY_TX_TRIGGERS_OFFSET	(0x00ac)
#define MIPIDSI_PHY_STATUS_OFFSET	(0x00b0)
#define MIPIDSI_PHY_TST_CTRL0_OFFSET	(0x00b4)
#define MIPIDSI_PHY_TST_CTRL1_OFFSET	(0x00b8)
#define MIPIDSI_INT_ST0_OFFSET	(0x00bc)
#define MIPIDSI_INT_ST1_OFFSET	(0x00c0)
#define MIPIDSI_INT_MSK0_OFFSET	(0x00c4)
#define MIPIDSI_INT_MSK1_OFFSET	(0x00c8)
#define INT_FORCE0	(0x00D8)
#define INT_FORCE1	(0x00DC)
#define VID_SHADOW_CTRL	(0x0100)
#define DPI_VCID_ACT	(0x010C)
#define DPI_COLOR_CODING_ACT	(0x0110)
#define DPI_LP_CMD_TIM_ACT	(0x0118)
#define VID_MODE_CFG_ACT	(0x0138)
#define VID_PKT_SIZE_ACT	(0x013C)
#define VID_NUM_CHUNKS_ACT	(0x0140)
#define VID_NULL_SIZE_ACT	(0x0144)
#define VID_HSA_TIME_ACT	(0x0148)
#define VID_HBP_TIME_ACT	(0x014C)
#define VID_HLINE_TIME_ACT	(0x0150)
#define VID_VSA_LINES_ACT	(0x0154)
#define VID_VBP_LINES_ACT	(0x0158)
#define VID_VFP_LINES_ACT	(0x015C)
#define VID_VACTIVE_LINES_ACT	(0x0160)
#define SDF_3D_ACT	(0x0190)


/*******************************************************************************
** MMBUF
*/
#define SMC_LOCK	(0x0000)
#define SMC_MEM_LP	(0x0004)
#define SMC_GCLK_CS	(0x000C)
#define SMC_QOS_BACKDOOR	(0x0010)
#define SMC_DFX_WCMD_CNT_1ST	(0x0014)
#define SMC_DFX_WCMD_CNT_2ND	(0x0018)
#define SMC_DFX_WCMD_CNT_3RD	(0x001C)
#define SMC_DFX_WCMD_CNT_4TH	(0x0020)
#define SMC_DFX_RCMD_CNT_1ST	(0x0024)
#define SMC_DFX_RCMD_CNT_2ND	(0x0028)
#define SMC_DFX_RCMD_CNT_3RD	(0x002C)
#define SMC_DFX_RCMD_CNT_4TH	(0x0030)
#define SMC_CS_IDLE	(0x0034)
#define SMC_DFX_BFIFO_CNT0	(0x0038)
#define SMC_DFX_RDFIFO_CNT1	(0x003C)
#define SMC_SP_SRAM_STATE0	(0x0040)
#define SMC_SP_SRAM_STATE1	(0x0044)


/*******************************************************************************
** dirty_region_updt
*/
typedef struct dirty_region_updt {
	uint32_t dbuf_frm_size;
	uint32_t dbuf_frm_hsize;
	uint32_t dpp_img_hrz;
	uint32_t dpp_img_vrt;
	uint32_t ldi_dpi0_hrz_ctrl0;
	uint32_t ldi_dpi0_hrz_ctrl1;
	uint32_t ldi_dpi0_hrz_ctrl2;
	uint32_t ldi_dpi1_hrz_ctrl0;
	uint32_t ldi_dpi1_hrz_ctrl1;
	uint32_t ldi_dpi1_hrz_ctrl2;
	uint32_t ldi_vrt_ctrl0;
	uint32_t ldi_vrt_ctrl1;
	uint32_t ldi_vrt_ctrl2;
	uint32_t ldi_ctrl;
	uint32_t ifbc_size;
	uint32_t edpi_cmd_size;
}dirty_region_updt_t;


/*******************************************************************************
** dss module reg
*/
typedef struct dss_module_reg {
	char __iomem *aif_ch_base[DSS_CHN_MAX_DEFINE];
	char __iomem *aif1_ch_base[DSS_CHN_MAX_DEFINE];
	char __iomem *mif_ch_base[DSS_CHN_MAX_DEFINE];
	char __iomem *dma_base[DSS_CHN_MAX_DEFINE];
	char __iomem *dfc_base[DSS_CHN_MAX_DEFINE];
	char __iomem *scl_base[DSS_CHN_MAX_DEFINE];
	char __iomem *sharp_base[DSS_CHN_MAX_DEFINE];
	char __iomem *post_clip_base[DSS_CHN_MAX_DEFINE];
	char __iomem *ce_base[DSS_CHN_MAX_DEFINE];
	char __iomem *csc_base[DSS_CHN_MAX_DEFINE];
	char __iomem *ov_base[DSS_OVL_IDX_MAX];
	char __iomem *mctl_base[DSS_OVL_IDX_MAX];
	dss_mctl_ch_base_t mctl_ch_base[DSS_CHN_MAX_DEFINE];
	char __iomem *mctl_sys_base;
	char __iomem *smmu_base;
	char __iomem *post_scf_base;

	dss_aif_t aif[DSS_CHN_MAX_DEFINE];
	dss_aif_t aif1[DSS_CHN_MAX_DEFINE];
	dss_aif_bw_t aif_bw[DSS_CHN_MAX_DEFINE];
	dss_aif_bw_t aif1_bw[DSS_CHN_MAX_DEFINE];
	dss_mif_t mif[DSS_CHN_MAX_DEFINE];
	dss_rdma_t rdma[DSS_CHN_MAX_DEFINE];
	dss_wdma_t wdma[DSS_CHN_MAX_DEFINE];
	dss_dfc_t dfc[DSS_CHN_MAX_DEFINE];
	dss_scl_t scl[DSS_CHN_MAX_DEFINE];
	dss_sharpness_t sharp[DSS_CHN_MAX_DEFINE];
	dss_post_clip_t post_clip[DSS_CHN_MAX_DEFINE];
	dss_ce_t ce[DSS_CHN_MAX_DEFINE];
	dss_csc_t csc[DSS_CHN_MAX_DEFINE];
	dss_ovl_t ov[DSS_OVL_IDX_MAX];
	dss_mctl_t mctl[DSS_OVL_IDX_MAX];
	dss_mctl_ch_t mctl_ch[DSS_CHN_MAX_DEFINE];
	dss_mctl_sys_t mctl_sys;
	dss_smmu_t smmu;
	dirty_region_updt_t dirty_region_updt;
	dss_scl_t post_scf;

	uint8_t aif_ch_used[DSS_CHN_MAX_DEFINE];
	uint8_t aif1_ch_used[DSS_CHN_MAX_DEFINE];
	uint8_t mif_used[DSS_CHN_MAX_DEFINE];
	uint8_t dma_used[DSS_CHN_MAX_DEFINE];
	uint8_t dfc_used[DSS_CHN_MAX_DEFINE];
	uint8_t scl_used[DSS_CHN_MAX_DEFINE];
	uint8_t sharp_used[DSS_CHN_MAX_DEFINE];
	uint8_t post_cilp_used[DSS_CHN_MAX_DEFINE];
	uint8_t ce_used[DSS_CHN_MAX_DEFINE];
	uint8_t csc_used[DSS_CHN_MAX_DEFINE];
	uint8_t ov_used[DSS_OVL_IDX_MAX];
	uint8_t ch_reg_default_used[DSS_CHN_MAX_DEFINE];
	uint8_t mctl_used[DSS_OVL_IDX_MAX];
	uint8_t mctl_ch_used[DSS_CHN_MAX_DEFINE];
	uint8_t mctl_sys_used;
	uint8_t smmu_used;
	uint8_t dirty_region_updt_used;
	uint8_t post_scf_used;
} dss_module_reg_t;

typedef struct dss_mmbuf_info {
	uint32_t mm_base[DSS_CHN_MAX_DEFINE];
	uint32_t mm_size[DSS_CHN_MAX_DEFINE];

	uint8_t mm_used[DSS_CHN_MAX_DEFINE];
} dss_mmbuf_info_t;



#endif  /* HISI_DSS_REGS_H */
