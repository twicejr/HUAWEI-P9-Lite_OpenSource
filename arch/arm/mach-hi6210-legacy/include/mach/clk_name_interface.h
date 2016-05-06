/*************************************************************************
 *   Supply clock interfaces, clocks' name are defined by MICRO name.    *
 ************************************************************************/
 
/* source clocks */
#define CLKIN_SYS 	"clkin_sys"			/* system clock */
#define CLK_REF32K	"clk_ref32k"		/* sleep clock */
#define CLK_PMU32KB	"clk_pmu32kb"		/* pmu32kb clock */
#define CLK_PMU32KC	"clk_pmu32kc"		/* pmu32kc clock */
#define CLK_REF 	"clk_ref"			/* tcxo */

#define CLK_APLL0	"clk_apll0"			/* apll0 pll source clock */
#define CLK_APLL1	"clk_apll1"			/* apll1 pll source clock */
#define CLK_GPLL0	"clk_gpll0"			/* gpll0 pll source clock */
#define CLK_GPLL1	"clk_gpll1"			/* gpll1 pll source clock */

#define CLK_DDRPLL	"clk_ddrpll"		/* ddr pll source clock */
#define CLK_PERIPLL	"clk_peripll"		/* periph pll source clock */
#define CLK_DSPPLL	"clk_dsppll"		/* dsp pll source clock */
#define CLK_SYSPLL	"clk_syspll"
#define CLK_HDMIPLL	"clk_hdmipll"		/* hdmi pll source clock */

/* peripheral power down zone begin */
#define CLK_100M_SRC	"clk_100m_src"		/* source clock of bbe16 atb, hdmi ref */
#define CLK_300M_SRC	"clk_300m_src"		/* divisor rate clock */
#define CLK_BUS_SRC		"clk_bus_src"		
#define CLK_27M_GATED		"clk_27m_gated"	
#define CLK_27M		"clk_27m"	
#define CLK_90K		"clk_90k"	

/* uart0~6 */
#define CLK_UART0	"clk_uart0"		/* uart0 work clock */
#define CLK_UART1	"clk_uart1"		/* uart1 work clock */
#define CLK_UART2	"clk_uart2"		/* uart2 work clock */
#define CLK_UART3	"clk_uart3"		/* uart3 work clock */
#define CLK_UART4	"clk_uart4"		/* uart4 work clock */
#define CLK_UART5	"clk_uart5"		/* uart5 work clock */
#define CLK_UART6	"clk_uart6"		/* uart6 work clock */
#define PCLK_UART0	"pclk_uart0"		/* uart0 work clock */
#define PCLK_UART1	"pclk_uart1"		/* uart1 work clock */
#define PCLK_UART2	"pclk_uart2"		/* uart2 work clock */
#define PCLK_UART3	"pclk_uart3"		/* uart3 work clock */
#define PCLK_UART4	"pclk_uart4"		/* uart4 work clock */
#define PCLK_UART5	"pclk_uart5"		/* uart5 work clock */
#define PCLK_UART6	"pclk_uart6"		/* uart6 work clock */

/* SPI0~1 */
#define PCLK_SPI0	"pclk_spi0"		/* spi0 bus clock */
#define PCLK_SPI1	"pclk_spi1"		/* spi1 bus clock */

#define CLK_SPI0	"clk_spi0"		/* spi0 reference clock */
#define CLK_SPI1	"clk_spi1"		/* spi1 reference clock */

/* I2C0~5 */
#define PCLK_I2C0	"pclk_i2c0"		/* i2c0 bus clock */
#define PCLK_I2C1	"pclk_i2c1"		/* i2c1 bus clock */
#define PCLK_I2C2	"pclk_i2c2"		/* i2c2 bus clock */
#define PCLK_I2C3	"pclk_i2c3"		/* i2c3 bus clock */
#define PCLK_I2C4	"pclk_i2c4"		/* i2c4 bus clock */
#define PCLK_I2C5	"pclk_i2c5"		/* i2c5 bus clock */

#define CLK_I2C0	"clk_i2c0"		/* i2c0 referencee clock */
#define CLK_I2C1	"clk_i2c1"		/* i2c1 referencee clock */
#define CLK_I2C2	"clk_i2c2"		/* i2c2 referencee clock */
#define CLK_I2C3	"clk_i2c3"		/* i2c3 referencee clock */
#define CLK_I2C4	"clk_i2c4"		/* i2c4 referencee clock */
#define CLK_I2C5	"clk_i2c5"		/* i2c5 referencee clock */

/* PWM */
#define CLK_PWM0	"clk_pwm0"		/* pwm0 work clock */
#define CLK_PWM1	"clk_pwm1"		/* pwm1 work clock */
#define PCLK_PWM0	"pclk_pwm0"		/* pwm0 bus clock */
#define PCLK_PWM1	"pclk_pwm1"		/* pwm1 bus clock */

/* gpio */
#define CLK_GPIO0      "clk_gpio0"
#define CLK_GPIO1   "clk_gpio1"
#define CLK_GPIO2   "clk_gpio2"
#define CLK_GPIO3   "clk_gpio3"
#define CLK_GPIO4   "clk_gpio4"
#define CLK_GPIO5   "clk_gpio5"
#define CLK_GPIO6   "clk_gpio6"
#define CLK_GPIO7   "clk_gpio7"
#define CLK_GPIO8   "clk_gpio8"
#define CLK_GPIO9   "clk_gpio9"
#define CLK_GPIO10   "clk_gpio10"
#define CLK_GPIO11   "clk_gpio11"
#define CLK_GPIO12   "clk_gpio12"
#define CLK_GPIO13   "clk_gpio13"
#define CLK_GPIO14   "clk_gpio14"
#define CLK_GPIO15   "clk_gpio15"
#define CLK_GPIO16   "clk_gpio16"
#define CLK_GPIO17   "clk_gpio17"
#define CLK_GPIO18   "clk_gpio18"
#define CLK_GPIO19   "clk_gpio19"

/* MMC */
#define CLK_DSPPLL_MMC0_GATED	"clk_dsppll_mmc0_gated"		/* mmc0 high src clock */
#define CLK_DSPPLL_MMC1_GATED	"clk_dsppll_mmc1_gated"		/* mmc1 high src clock */
#define CLK_DSPPLL_MMC2_GATED	"clk_dsppll_mmc2_gated"		/* mmc2 high src clock */
	
#define HCLK_MMC0		"hclk_mmc0"		/* mmc0 low clock */
#define HCLK_MMC1		"hclk_mmc1"		/* mmc1 low clock */
#define HCLK_MMC2		"hclk_mmc2"		/* mmc2 low clock */
#define CLK_MMC0HIGH	"clk_mmc0high"		/* mmc0 high clock */
#define CLK_MMC1HIGH	"clk_mmc1high"		/* mmc1 high clock */
#define CLK_MMC2HIGH	"clk_mmc2high"		/* mmc2 high clock */
#define CLK_MMC0LOW		"clk_mmc0low"		/* mmc0 low clock */
#define CLK_MMC1LOW		"clk_mmc1low"		/* mmc1 low clock */
#define CLK_MMC2LOW		"clk_mmc2low"		/* mmc2 low clock */

/* SIO */
#define CLK_SIO0_BUS	"hclk_sio0"		/* sio0 bus clock */
#define CLK_SIO1_BUS	"hclk_sio1"		/* sio1 bus clock */
#define CLK_SIO2_BUS	"hclk_sio2"		/* sio2 bus clock */
#define CLK_SIO3_BUS	"hclk_sio3"		/* sio3 bus clock */

#define CLK_SIO0_SRC	"clk_sio0_src"		/* sio0 selectable parent clock */
#define CLK_SIO1_SRC	"clk_sio1_src"		/* sio0 selectable parent clock */
#define CLK_SIO2_SRC	"clk_sio2_src"		/* sio0 selectable parent clock */
#define CLK_SIO3_SRC	"clk_sio3_src"		/* sio0 selectable parent clock */

#define CLK_SIO0_DIV	"clk_sio0_div"		/* divisor rate parent clock of sio0 selectable */
#define CLK_SIO1_DIV	"clk_sio1_div"		/* divisor rate parent clock of sio1 selectable */
#define CLK_SIO2_DIV	"clk_sio2_div"		/* divisor rate parent clock of sio2 selectable */
#define CLK_SIO3_DIV	"clk_sio3_div"		/* divisor rate parent clock of sio3 selectable */

#define CLK_SIO0_WORK	"clk_sio0_work"		/* sio0 work clock */
#define CLK_SIO1_WORK	"clk_sio1_work"		/* sio1 work clock */
#define CLK_SIO2_WORK	"clk_sio2_work"		/* sio2 work clock */
#define CLK_SIO3_WORK	"clk_sio3_work"		/* sio3 work clock */

/* peripheral power down zone end */

/* DDR WRAP zone begin */
#define CLK_DDRIO			"clk_ddrio"			/* ddrio clock */
#define CLK_DDRIO_DIV		"clk_ddrio_div"			/* ddrio clock */
#define CLK_DDRC			"clk_ddrc"			/* ddrc clock */
#define CLK_DDRC_DIV		"clk_ddrc_div"			/* ddrc clock */
#define CLK_DDRBUS_DIV		"clk_ddrbus_div"	/* ddr bus divisor clock */
#define CLK_AXI_IMG_BUS		"clk_axi_img_bus"		/* img axi bus clock */
#define CLK_AXI_VIDEO_BUS	"clk_axi_video_bus"	/* video axi bus clock */

/* DDR WRAP zone end */

/* DDRPHY zone begin */
#define CLK_DDRPHY	"clk_ddrphy"			/* ddrphy clock */

/* DDRPHY zone end */

/* VPP zone begin */
#define CLK_PERIPLL_VPP_GATED		"clk_peripll_vpp_gated"	/* vpp gate clock of before divisor rate */
#define CLK_2VPP_SLAVE_CLK			"clk_2vpp_slave_clk"		/* vpp work clock */
#define CLK_X2X_VPP_BRG_S			"clk_x2x_vpp_brg_s"		/* vpp x2x brige clock */
#define CLK_P2P_VPP_BRG_S			"clk_p2p_vpp_brg_s"		/* vpp p2p brige clock */
#define CLK_VPP_VIDEO_BUS			CLK_AXI_VIDEO_BUS		/* video axi bus clock */

/* VPP zone end */

/* VENC zone begin */
#define CLK_PERIPLL_VENC_GATED	"clk_peripll_venc_gated"	/* venc gate clock of before divisor rate */
#define CLK_0VENC_SLAVE_CLK		"clk_0venc_slave_clk"				/* venc work clock */
#define CLK_X2X_VENC_BRG_S	"clk_x2x_venc_brg_s"		/* venc x2x brige clock */
#define CLK_P2P_VENC_BRG_S	"clk_p2p_venc_brg_s"		/* venc p2p brige clock */
#define CLK_VENC_VIDEO_BUS	CLK_AXI_VIDEO_BUS		/* video axi bus clock */

/* VENC zone end */

/* VDEC zone begin */
#define CLK_PERIPLL_VDEC_GATED	"clk_peripll_vdec_gated"		/* vdec gate clock of before divisor rate */
#define CLK_1VDEC_SLAVE_CLK		"clk_1vdec_slave_clk"				/* vdec work clock */
#define CLK_X2X_VDEC_BRG_S		"clk_x2x_vdec_brg_s"		/* vdec x2x brige clock */
#define CLK_P2P_VDEC_BRG_S		"clk_p2p_vdec_brg_s"		/* vdec p2p brige clock */
#define CLK_VDEC_VIDEO_BUS		CLK_AXI_VIDEO_BUS			/* video axi bus clock */

/* VDEC zone end */

/* G2D zone begin */
#define CLK_DSPPLL_G2DCORE_GATED	"clk_dsppll_g2dcore_gated"	/* g2d gate clock of before divisor rate */
#define CLK_5G2D_CORE_CLK				"clk_5g2d_core_clk"			/* g2d work clock */
#define CLK_4G2D_AXI_CLKHB			"clk_4g2d_axi_clkhb"		/* g2d axi bus interface clock */
#define CLK_3G2D_CFG_CLK				"clk_3g2d_cfg_clk"			/* g2d config interface clock */

/* G2D zone end */

/* G3D zone begin */
#define CLK_MALI			"clk_mali"				/* g3d work clock */
#define CLK_AXI_MALI_BUS	"clk_axi_mali_bus"		/* g3d axi bus interface clock */
#define CLK_X2X_MALI_BRG_S	"clk_x2x_mali_brg_s"	/* g3d x2x brige slave clock */
#define CLK_X2X_MALI_BRG_M	"clk_x2x_mali_brg_m"	/* g3d x2x brige master clock */
#define CLK_P2P_MALI_BRG_S	"clk_p2p_mali_brg_s"	/* g3d p2p brige slave clock */

/* G3D zone end */

/* EDC0 zone begin */
#define CLK_DSPPLL_EDC0_CORE_GATED	"clk_dsppll_edc0_core_gated"	/* edc0 gate clock of before divisor rate */
#define CLK_EDC0_CORE			"clk_edc0_core"					/* edc0 work clock */
#define CLK_MUX_EDC0_PIX_GATED	"clk_mux_edc0_pix_gated"		/* gate clock of before edc0 pix divisor rate */
#define CLK_EDC0_PIX_LDI	"clk_edc0_pix_ldi"		/* edc0 pix clock */
#define CLK_ACLK_EDC0			"clk_aclk_edc0"				/* edc0 axi bus interface clock */
#define CLK_EDC0_CFG_CLK	"clk_edc0_cfg_clk"			/* edc0 config interface clock */
#define CLK_DSIO_CFG_CLK	"clk_dsio_cfg_clk"			/* dsio config interface clock */

/* EDC0 zone end */

/* EDC1 zone begin */
#define CLK_EDC1_CORE		"clk_edc1_core"			/* edc1 work clock */
#define CLK_EDC1_PIX_LDI	"clk_edc1_pix_ldi"		/* edc1 pix clock */
#define CLK_EDC1_AXI		"clk_edc1_axi"			/* edc1 axi bus interface clock */
#define CLK_EDC1_CFG_CLK	"clk_edc1_cfg_clk"			/* edc1 config clock */

/* ASP HDMI */
#define CLK_HDMIPLL_DIVFRAC	"clk_hdmipll_divfrac"	/* divfrac hdmipll to mclk hdmi */
#define CLK_MCLK_HDMI		"clk_mclk_hdmi"			/* hdmi master sound clock */
#define CLK_ASP_SPDIF_REF	"clk_asp_spdif_ref"	/* ASP reference clock */
#define CLK_HDMI_SLAVE	"clk_hdmi_slave"		/* hdmi p2p slave brige clock */
#define CLK_HDMI_SCK	"clk_hdmi_sck"			/* hdmi i2s sound clock */
#define CLK_ASP_HDMI_ADWS	"clk_asp_hdmi_adws"		/* hdmi i2s clock */
#define CLK_ASP_HDMI_BCLK	"clk_asp_hdmi_bclk"		
#define CLK_ASP_HDMI_REF	"clk_asp_hdmi_ref"		/* ASP reference clock */
#define CLK_ASP_CFG	        "clk_asp_cfg"		/* ASP reference clock */

/* EDC1 zone end */

/* D-PHY zone begin */
#define CLK_DPHY0_REF	"clk_dphy0_ref"		/* dsiphy reference clock */
#define CLK_DPHY0_CFG	"clk_dphy0_cfg"		/* dsiphy0 config interface clock */
#define CLK_DPHY1_CFG	"clk_dphy1_cfg"		/* dsiphy1 config interface clock */
#define CLK_DPHY2_CFG	"clk_dphy2_cfg"		/* dsiphy2 config interface clock */

/* D-PHY zone end */

/* ISP zone begin */
#define CLK_ISP_CFG_CLK	"clk_isp_cfg_clk"				/* isp config interface clock */
#define CLK_ISP_AXI		"clk_isp_axi"					/* isp bus interface clock */
#define CLK_PERIPLL_ISP_GATED		"clk_peripll_isp_gated"		/* isp gate clock of before divisor rate */
#define CLK_ISP			"clk_isp"					/* isp work clock */
#define CLK_PERIPLL_ISP_REF_GATED	"clk_peripLL_isp_ref_gated"	/* isp reference gate clock of before divisor rate */
#define CLK_ISP_REF		"clk_isp_ref"				/* isp reference clock */

#define CLK_CSI_APB_MUX	"clk_csi_apb_mux"	/* csi apb mux clock */
#define CLK_CSIO_CFG	"clk_csio_cfg"		/* csio config interface clock */
#define CSI1_CFG_CLK	"csi1_cfg_clk"		/* csi1 config interface clock */
#define CSI2_CFG_CLK	"csi2_cfg_clk"		/* csi2 config interface clock */

/* ISP zone end */

/* HIFI zone begin */				
#define CLK_DSPPLL_HIFI_CORE_GATED "clk_dsppll_hifi_core_gated"		/* hifi gate clock of before divisor rate */
#define CLK_HIFI_CORE "clk_hifi_core"					/* hifi kernel clock */

/* HIFI zone end */


/*PMUSSI begin*/
#define CLK_PMUSSI "clk_pmussi"        /*pmussi work clock*/

/*PMUSSI end*/

#define CLK_WATCHDOG0               "clk_watchdog0"
#define PCLK_WATCHDOG0      "clk_watchdog0_pclk"
#define CLK_RTC      "clk_rtc"
#define HCLK_NANDC      "hclk_nandc"
#define CLK_AP_DMAC_AXI0 "clk_ap_dmac_axi0"
#define CLK_AP_DMAC_AXI1 "clk_ap_dmac_axi1"
#define HCLK_USBOTG_ON          "hclk_usbotg_on"
#define HCLK_USBOTG_OFF         "hclk_usbotg_off"
#define CLK_USBOTG_OFF          "clk_usbotg_off"
#define CLK_PICOPHY                 "clk_picophy"
#define CLK_PICOPHY_TEST        "clk_picophy_test"

#define CLK_TS                          "clk_ts"
#define HCLK_TS                         "hclk_ts"
#define CLK_GPS                         "clk_gps"
#define CLK_TSENSOR0                "clk_tsensor0"
#define CLK_TSENSOR1                "clk_tsensor1"

#define PCLK_TIMER0 "pclk_timer0"
#define CLK_TIMER0 "clk_timer0"
#define PCLK_TIMER1 "pclk_timer1"
#define CLK_TIMER1 "clk_timer1"
#define PCLK_TIMER2 "pclk_timer2"
#define CLK_TIMER2 "clk_timer2"
#define PCLK_TIMER3 "pclk_timer3"
#define CLK_TIMER3 "clk_timer3"
#define PCLK_TIMER4 "pclk_timer4"
#define CLK_TIMER4 "clk_timer4"
#define PCLK_TIMER5 "pclk_timer5"
#define CLK_TIMER5 "clk_timer5"
#define PCLK_TIMER6 "pclk_timer6"
#define CLK_TIMER6 "clk_timer6"
#define PCLK_TIMER7 "pclk_timer7"
#define CLK_TIMER7 "clk_timer7"
#define PCLK_TIMER8 "pclk_timer8"
#define CLK_TIMER8 "clk_timer8"
















