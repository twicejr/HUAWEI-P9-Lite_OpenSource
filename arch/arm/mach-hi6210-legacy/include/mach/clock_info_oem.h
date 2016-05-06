/**************************************************************************************
说明：所有Clock基本信息都在此输出，而且所有Clock都“一视同仁”，这里并不表示Clock之间的
      关系（父时钟，友时钟等）
**************************************************************************************/
#include "mach/clk_name_interface.h"

/* clkin_sys 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLKIN_SYS_DIV_MAX 		1
#define CLKIN_SYS_MIN_RATE 		150000000/CLKIN_SYS_DIV_MAX	//时钟最小频率宏定义
#define CLKIN_SYS_MAX_RATE 		150000000	//时钟最大频率宏定义
#define CLKIN_SYS_RATE 			CLKIN_SYS_MIN_RATE			//时钟频率宏定义

/* CLK_REF 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_REF_DIV_MAX          1
#define CLK_REF_MIN_RATE         19200000/CLK_REF_DIV_MAX    //时钟最小频率宏定义
#define CLK_REF_MAX_RATE         19200000    //时钟最大频率宏定义
#define CLK_REF_RATE             CLK_REF_MIN_RATE            //时钟频率宏定义

/* clk_ref32k 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_REF32K_DIV_MAX 		1
#define CLK_REF32K_MIN_RATE 	32768/CLK_REF32K_DIV_MAX	//时钟最小频率宏定义
#define CLK_REF32K_MAX_RATE 	32768	//时钟最大频率宏定义
#define CLK_REF32K_RATE 		CLK_REF32K_MIN_RATE		//时钟频率宏定义

/* clk_pmu32kb 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PMU32KB_DIV_MAX 		1
#define CLK_PMU32KB_MIN_RATE 	32768/CLK_PMU32KB_DIV_MAX	//时钟最小频率宏定义
#define CLK_PMU32KB_MAX_RATE 	32768	//时钟最大频率宏定义
#define CLK_PMU32KB_RATE 		CLK_PMU32KB_MIN_RATE		//时钟频率宏定义

/* clk_pmu32kc 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PMU32KC_DIV_MAX 		1
#define CLK_PMU32KC_MIN_RATE 	32768/CLK_PMU32KC_DIV_MAX	//时钟最小频率宏定义
#define CLK_PMU32KC_MAX_RATE 	32768	//时钟最大频率宏定义
#define CLK_PMU32KC_RATE 		CLK_PMU32KC_MIN_RATE		//时钟频率宏定义

/* clk_apll0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_APLL0_DIV_MAX 		1
#define CLK_APLL0_MIN_RATE 		60000000/CLK_APLL0_DIV_MAX	//时钟最小频率宏定义
#define CLK_APLL0_MAX_RATE 		60000000	//时钟最大频率宏定义
#define CLK_APLL0_RATE 			CLK_APLL0_MIN_RATE		//时钟频率宏定义

/* clk_apll1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_APLL1_DIV_MAX 		1
#define CLK_APLL1_MIN_RATE 		40000000/CLK_APLL1_DIV_MAX	//时钟最小频率宏定义
#define CLK_APLL1_MAX_RATE 		40000000	//时钟最大频率宏定义
#define CLK_APLL1_RATE 			CLK_APLL1_MIN_RATE		//时钟频率宏定义

/* clk_dsppll 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DSPPLL_DIV_MAX 		1
#define CLK_DSPPLL_MIN_RATE 	1200000000/CLK_DSPPLL_DIV_MAX	//时钟最小频率宏定义
#define CLK_DSPPLL_MAX_RATE 	1200000000	//时钟最大频率宏定义
#define CLK_DSPPLL_RATE 		CLK_DSPPLL_MIN_RATE		//时钟频率宏定义

/* clk_gpll0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_GPLL0_DIV_MAX 		1
#define CLK_GPLL0_MIN_RATE 		533000000/CLK_GPLL0_DIV_MAX	//时钟最小频率宏定义
#define CLK_GPLL0_MAX_RATE 		533000000	//时钟最大频率宏定义
#define CLK_GPLL0_RATE 			CLK_GPLL0_MIN_RATE		//时钟频率宏定义

/* clk_gpll1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_GPLL1_DIV_MAX 		1
#define CLK_GPLL1_MIN_RATE 		1066000000/CLK_GPLL1_DIV_MAX	//时钟最小频率宏定义
#define CLK_GPLL1_MAX_RATE 		1066000000	//时钟最大频率宏定义
#define CLK_GPLL1_RATE 			CLK_GPLL1_MIN_RATE		//时钟频率宏定义

/* clk_peripll 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PERIPLL_DIV_MAX 	1
#define CLK_PERIPLL_MIN_RATE 	1440000000/CLK_PERIPLL_DIV_MAX	//时钟最小频率宏定义
#define CLK_PERIPLL_MAX_RATE 	1440000000	//时钟最大频率宏定义
#define CLK_PERIPLL_RATE 		CLK_PERIPLL_MIN_RATE		//时钟频率宏定义

/* clk_hdmipll 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_HDMIPLL_DIV_MAX 	1
#define CLK_HDMIPLL_MIN_RATE 	1188000000/CLK_HDMIPLL_DIV_MAX	//时钟最小频率宏定义
#define CLK_HDMIPLL_MAX_RATE 	1188000000	//时钟最大频率宏定义
#define CLK_HDMIPLL_RATE 		CLK_HDMIPLL_MIN_RATE		//时钟频率宏定义

/* clk_ddrpll 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DDRPLL_DIV_MAX 		1
#define CLK_DDRPLL_MIN_RATE 	533000000/CLK_DDRPLL_DIV_MAX	//时钟最小频率宏定义
#define CLK_DDRPLL_MAX_RATE 	533000000	//时钟最大频率宏定义
#define CLK_DDRPLL_RATE 		CLK_DDRPLL_MIN_RATE		//时钟频率宏定义

/* clk_300m_src 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_300M_SRC_DIV_MAX 	1
#define CLK_300M_SRC_MIN_RATE 	300000000/CLK_300M_SRC_DIV_MAX	//时钟最小频率宏定义
#define CLK_300M_SRC_MAX_RATE 	300000000	//时钟最大频率宏定义
#define CLK_300M_SRC_RATE 		CLK_300M_SRC_MIN_RATE		//时钟频率宏定义

/* clk_100m_src 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_100M_SRC_DIV_MAX 	1
#define CLK_100M_SRC_MIN_RATE 	100000000/CLK_100M_SRC_DIV_MAX	//时钟最小频率宏定义
#define CLK_100M_SRC_MAX_RATE 	100000000	//时钟最大频率宏定义
#define CLK_100M_SRC_RATE 		CLK_100M_SRC_MIN_RATE		//时钟频率宏定义

/* clk_bus_src 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_BUS_SRC_DIV_MAX 	16
#define CLK_BUS_SRC_MIN_RATE 	CLK_300M_SRC_MIN_RATE/CLK_BUS_SRC_DIV_MAX	//时钟最小频率宏定义
#define CLK_BUS_SRC_MAX_RATE 	CLK_300M_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_BUS_SRC_RATE 		CLK_300M_SRC_MIN_RATE/2		//时钟频率宏定义

/* clk_bus_src 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_27M_GATED_DIV_MAX 	1
#define CLK_27M_GATED_MIN_RATE 	27000000/CLK_27M_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_27M_GATED_MAX_RATE 	27000000	//时钟最大频率宏定义
#define CLK_27M_GATED_RATE 		CLK_27M_GATED_MIN_RATE		//时钟频率宏定义

/* clk_bus_src 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_27M_DIV_MAX 	1
#define CLK_27M_MIN_RATE 	CLK_27M_GATED_MIN_RATE/CLK_27M_DIV_MAX	//时钟最小频率宏定义
#define CLK_27M_MAX_RATE 	CLK_27M_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_27M_RATE 		CLK_27M_MIN_RATE		//时钟频率宏定义

/* clk_bus_src 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_90K_DIV_MAX 	16
#define CLK_90K_MIN_RATE 	90000/CLK_90K_DIV_MAX	//时钟最小频率宏定义
#define CLK_90K_MAX_RATE 	90000	//时钟最大频率宏定义
#define CLK_90K_RATE 		CLK_90K_MIN_RATE		//时钟频率宏定义

/* clk_mali 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MALI_DIV_MAX 		16
#define CLK_MALI_MIN_RATE 		CLK_GPLL1_MIN_RATE/CLK_MALI_DIV_MAX	//时钟最小频率宏定义
#define CLK_MALI_MAX_RATE 		CLK_GPLL0_MAX_RATE	//时钟最大频率宏定义
#define CLK_MALI_RATE 			CLK_MALI_MIN_RATE		//时钟频率宏定义


/* clk_dsppll_edc0_core_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DSPPLL_EDC0_CORE_GATED_DIV_MAX 	1
#define CLK_DSPPLL_EDC0_CORE_GATED_MIN_RATE CLK_DSPPLL_MIN_RATE/CLK_DSPPLL_EDC0_CORE_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_DSPPLL_EDC0_CORE_GATED_MAX_RATE CLK_DSPPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_DSPPLL_EDC0_CORE_GATED_RATE 	CLK_DSPPLL_EDC0_CORE_GATED_MIN_RATE		//时钟频率宏定义


/* clk_edc0_core 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_EDC0_CORE_DIV_MAX 	64
#define CLK_EDC0_CORE_MIN_RATE 	CLK_DSPPLL_EDC0_CORE_GATED_MIN_RATE/CLK_EDC0_CORE_DIV_MAX	//时钟最小频率宏定义
#define CLK_EDC0_CORE_MAX_RATE 	CLK_DSPPLL_EDC0_CORE_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_EDC0_CORE_RATE 		CLK_EDC0_CORE_MIN_RATE		//时钟频率宏定义

/* clk_mux_edc0_pix_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MUX_EDC0_PIX_GATED_DIV_MAX 	1
#define CLK_MUX_EDC0_PIX_GATED_MIN_RATE CLK_DSPPLL_MIN_RATE/CLK_MUX_EDC0_PIX_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_MUX_EDC0_PIX_GATED_MAX_RATE CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_MUX_EDC0_PIX_GATED_RATE 	CLK_MUX_EDC0_PIX_GATED_MIN_RATE	//时钟频率宏定义


/* clk_edc0_pix_ldi 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_EDC0_PIX_LDI_DIV_MAX 	64
#define CLK_EDC0_PIX_LDI_MIN_RATE 	CLK_MUX_EDC0_PIX_GATED_MIN_RATE/CLK_EDC0_PIX_LDI_DIV_MAX	//时钟最小频率宏定义
#define CLK_EDC0_PIX_LDI_MAX_RATE 	CLK_MUX_EDC0_PIX_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_EDC0_PIX_LDI_RATE 		CLK_EDC0_PIX_LDI_MIN_RATE		//时钟频率宏定义

/* clk_edc1_core 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_EDC1_CORE_DIV_MAX 		64
#define CLK_EDC1_CORE_MIN_RATE 		CLK_HDMIPLL_MIN_RATE/CLK_EDC1_CORE_DIV_MAX	//时钟最小频率宏定义
#define CLK_EDC1_CORE_MAX_RATE 		CLK_HDMIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_EDC1_CORE_RATE 			CLK_EDC1_CORE_MIN_RATE		//时钟频率宏定义

/* clk_axi_video_bus 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_AXI_VIDEO_BUS_DIV_MAX 	64
#define CLK_AXI_VIDEO_BUS_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_AXI_VIDEO_BUS_DIV_MAX	//时钟最小频率宏定义
#define CLK_AXI_VIDEO_BUS_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_AXI_VIDEO_BUS_RATE 		CLK_AXI_VIDEO_BUS_MIN_RATE		//时钟频率宏定义

/* clk_axi_img_bus 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_AXI_IMG_BUS_DIV_MAX 	64
#define CLK_AXI_IMG_BUS_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_AXI_IMG_BUS_DIV_MAX	//时钟最小频率宏定义
#define CLK_AXI_IMG_BUS_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_AXI_IMG_BUS_RATE 		CLK_AXI_IMG_BUS_MIN_RATE		//时钟频率宏定义

/* clk_peripll_vpp_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PERIPLL_VPP_GATED_DIV_MAX 	1
#define CLK_PERIPLL_VPP_GATED_MIN_RATE 	CLK_PERIPLL_MIN_RATE/CLK_PERIPLL_VPP_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_PERIPLL_VPP_GATED_MAX_RATE 	CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_PERIPLL_VPP_GATED_RATE 		CLK_PERIPLL_VPP_GATED_MIN_RATE		//时钟频率宏定义

/* clk_2vpp_slave_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_2VPP_SLAVE_CLK_DIV_MAX 		16
#define CLK_2VPP_SLAVE_CLK_MIN_RATE 	CLK_PERIPLL_MIN_RATE/CLK_2VPP_SLAVE_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_2VPP_SLAVE_CLK_MAX_RATE 	CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_2VPP_SLAVE_CLK_RATE 		CLK_2VPP_SLAVE_CLK_MIN_RATE		//时钟频率宏定义

/* clk_x2x_vpp_brg_s 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_X2X_VPP_BRG_S_DIV_MAX 	1
#define CLK_X2X_VPP_BRG_S_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_X2X_VPP_BRG_S_DIV_MAX	//时钟最小频率宏定义
#define CLK_X2X_VPP_BRG_S_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_X2X_VPP_BRG_S_RATE 		CLK_X2X_VPP_BRG_S_MIN_RATE		//时钟频率宏定义

/* clk_p2p_vpp_brg_s 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_P2P_VPP_BRG_S_DIV_MAX 	1
#define CLK_P2P_VPP_BRG_S_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_P2P_VPP_BRG_S_DIV_MAX	//时钟最小频率宏定义
#define CLK_P2P_VPP_BRG_S_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_P2P_VPP_BRG_S_RATE 		CLK_P2P_VPP_BRG_S_MIN_RATE		//时钟频率宏定义

/* clk_peripll_venc_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PERIPLL_VENC_GATED_DIV_MAX 	1
#define CLK_PERIPLL_VENC_GATED_MIN_RATE CLK_PERIPLL_MIN_RATE/CLK_PERIPLL_VENC_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_PERIPLL_VENC_GATED_MAX_RATE CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_PERIPLL_VENC_GATED_RATE 	CLK_PERIPLL_VENC_GATED_MIN_RATE		//时钟频率宏定义

/* clk_0venc_slave_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_0VENC_SLAVE_CLK_DIV_MAX 	16
#define CLK_0VENC_SLAVE_CLK_MIN_RATE 	CLK_PERIPLL_MIN_RATE/CLK_0VENC_SLAVE_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_0VENC_SLAVE_CLK_MAX_RATE 	CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_0VENC_SLAVE_CLK_RATE 		CLK_0VENC_SLAVE_CLK_MIN_RATE		//时钟频率宏定义

/* clk_x2x_venc_brg_s 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_X2X_VENC_BRG_S_DIV_MAX 		1
#define CLK_X2X_VENC_BRG_S_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_X2X_VENC_BRG_S_DIV_MAX	//时钟最小频率宏定义
#define CLK_X2X_VENC_BRG_S_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_X2X_VENC_BRG_S_RATE 		CLK_X2X_VENC_BRG_S_MIN_RATE		//时钟频率宏定义

/* clk_p2p_venc_brg_s 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_P2P_VENC_BRG_S_DIV_MAX 		1
#define CLK_P2P_VENC_BRG_S_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_P2P_VENC_BRG_S_DIV_MAX	//时钟最小频率宏定义
#define CLK_P2P_VENC_BRG_S_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_P2P_VENC_BRG_S_RATE 		CLK_P2P_VENC_BRG_S_MIN_RATE		//时钟频率宏定义

/* clk_peripll_vdec_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PERIPLL_VDEC_GATED_DIV_MAX 	1
#define CLK_PERIPLL_VDEC_GATED_MIN_RATE CLK_PERIPLL_MIN_RATE/CLK_PERIPLL_VDEC_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_PERIPLL_VDEC_GATED_MAX_RATE CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_PERIPLL_VDEC_GATED_RATE 	CLK_PERIPLL_VDEC_GATED_MIN_RATE		//时钟频率宏定义

/* clk_1vdec_slave_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_1VDEC_SLAVE_CLK_DIV_MAX 	16
#define CLK_1VDEC_SLAVE_CLK_MIN_RATE 	CLK_PERIPLL_MIN_RATE/CLK_1VDEC_SLAVE_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_1VDEC_SLAVE_CLK_MAX_RATE 	CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_1VDEC_SLAVE_CLK_RATE 		CLK_1VDEC_SLAVE_CLK_MIN_RATE		//时钟频率宏定义

/* clk_x2x_vdec_brg_s 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_X2X_VDEC_BRG_S_DIV_MAX 		1
#define CLK_X2X_VDEC_BRG_S_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_X2X_VDEC_BRG_S_DIV_MAX	//时钟最小频率宏定义
#define CLK_X2X_VDEC_BRG_S_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_X2X_VDEC_BRG_S_RATE 		CLK_X2X_VDEC_BRG_S_MIN_RATE		//时钟频率宏定义

/* clk_p2p_vdec_brg_s 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_P2P_VDEC_BRG_S_DIV_MAX 		1
#define CLK_P2P_VDEC_BRG_S_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_P2P_VDEC_BRG_S_DIV_MAX	//时钟最小频率宏定义
#define CLK_P2P_VDEC_BRG_S_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_P2P_VDEC_BRG_S_RATE 		CLK_P2P_VDEC_BRG_S_MIN_RATE		//时钟频率宏定义

/* clk_dsppll_g2dcore_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DSPPLL_G2DCORE_GATED_DIV_MAX 	1
#define CLK_DSPPLL_G2DCORE_GATED_MIN_RATE 	CLK_DSPPLL_MIN_RATE/CLK_DSPPLL_G2DCORE_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_DSPPLL_G2DCORE_GATED_MAX_RATE 	CLK_DSPPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_DSPPLL_G2DCORE_GATED_RATE 		CLK_DSPPLL_G2DCORE_GATED_MIN_RATE		//时钟频率宏定义

/* clk_5g2d_core_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_5G2D_CORE_CLK_DIV_MAX 		16
#define CLK_5G2D_CORE_CLK_MIN_RATE 		CLK_DSPPLL_G2DCORE_GATED_MIN_RATE/CLK_5G2D_CORE_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_5G2D_CORE_CLK_MAX_RATE 		CLK_DSPPLL_G2DCORE_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_5G2D_CORE_CLK_RATE 			CLK_5G2D_CORE_CLK_MIN_RATE		//时钟频率宏定义

/* clk_4g2d_axi_clkhb 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_4G2D_AXI_CLKHB_DIV_MAX 		1
#define CLK_4G2D_AXI_CLKHB_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_4G2D_AXI_CLKHB_DIV_MAX	//时钟最小频率宏定义
#define CLK_4G2D_AXI_CLKHB_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_4G2D_AXI_CLKHB_RATE 		CLK_4G2D_AXI_CLKHB_MIN_RATE		//时钟频率宏定义

/* clk_3g2d_cfg_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_3G2D_CFG_CLK_DIV_MAX 	1
#define CLK_3G2D_CFG_CLK_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CLK_3G2D_CFG_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_3G2D_CFG_CLK_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_3G2D_CFG_CLK_RATE 		CLK_3G2D_CFG_CLK_MIN_RATE		//时钟频率宏定义

/* clk_p2p_mali_brg_s 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_P2P_MALI_BRG_S_DIV_MAX 		1
#define CLK_P2P_MALI_BRG_S_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_P2P_MALI_BRG_S_DIV_MAX	//时钟最小频率宏定义
#define CLK_P2P_MALI_BRG_S_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_P2P_MALI_BRG_S_RATE 		CLK_P2P_MALI_BRG_S_MIN_RATE		//时钟频率宏定义

/* clk_x2x_mali_brg_s 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_X2X_MALI_BRG_S_DIV_MAX 		1
#define CLK_X2X_MALI_BRG_S_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_X2X_MALI_BRG_S_DIV_MAX	//时钟最小频率宏定义
#define CLK_X2X_MALI_BRG_S_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_X2X_MALI_BRG_S_RATE 		CLK_X2X_MALI_BRG_S_MIN_RATE	//时钟频率宏定义

/* clk_x2x_mali_brg_m 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_X2X_MALI_BRG_M_DIV_MAX 		1
#define CLK_X2X_MALI_BRG_M_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_X2X_MALI_BRG_M_DIV_MAX	//时钟最小频率宏定义
#define CLK_X2X_MALI_BRG_M_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_X2X_MALI_BRG_M_RATE 		CLK_X2X_MALI_BRG_M_MIN_RATE		//时钟频率宏定义


/* clk_axi_mali_bus 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_AXI_MALI_BUS_DIV_MAX 	1
#define CLK_AXI_MALI_BUS_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_AXI_MALI_BUS_DIV_MAX	//时钟最小频率宏定义
#define CLK_AXI_MALI_BUS_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_AXI_MALI_BUS_RATE 		CLK_AXI_MALI_BUS_MIN_RATE		//时钟频率宏定义

/* clk_aclk_edc0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ACLK_EDC0_DIV_MAX 	1
#define CLK_ACLK_EDC0_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_ACLK_EDC0_DIV_MAX	//时钟最小频率宏定义
#define CLK_ACLK_EDC0_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_ACLK_EDC0_RATE 		CLK_ACLK_EDC0_MIN_RATE		//时钟频率宏定义

/* clk_edc0_cfg_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_EDC0_CFG_CLK_DIV_MAX 	1
#define CLK_EDC0_CFG_CLK_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CLK_EDC0_CFG_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_EDC0_CFG_CLK_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_EDC0_CFG_CLK_RATE 		CLK_EDC0_CFG_CLK_MIN_RATE		//时钟频率宏定义

/* clk_dsio_cfg_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DSIO_CFG_CLK_DIV_MAX 	1
#define CLK_DSIO_CFG_CLK_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CLK_DSIO_CFG_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_DSIO_CFG_CLK_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_DSIO_CFG_CLK_RATE 		CLK_DSIO_CFG_CLK_MIN_RATE		//时钟频率宏定义


/* clk_edc1_pix_ldi 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_EDC1_PIX_LDI_DIV_MAX 	64
#define CLK_EDC1_PIX_LDI_MIN_RATE 	CLK_HDMIPLL_MIN_RATE/CLK_EDC1_PIX_LDI_DIV_MAX	//时钟最小频率宏定义
#define CLK_EDC1_PIX_LDI_MAX_RATE 	CLK_HDMIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_EDC1_PIX_LDI_RATE 		CLK_EDC1_PIX_LDI_MIN_RATE		//时钟频率宏定义

/* clk_edc1_axi 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_EDC1_AXI_DIV_MAX 	1
#define CLK_EDC1_AXI_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_EDC1_AXI_DIV_MAX	//时钟最小频率宏定义
#define CLK_EDC1_AXI_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_EDC1_AXI_RATE 		CLK_EDC1_AXI_MIN_RATE		//时钟频率宏定义

/* clk_edc1_cfg_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_EDC1_CFG_CLK_DIV_MAX 	1
#define CLK_EDC1_CFG_CLK_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_EDC1_CFG_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_EDC1_CFG_CLK_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_EDC1_CFG_CLK_RATE 		CLK_EDC1_CFG_CLK_MIN_RATE		//时钟频率宏定义
/* clk_hdmipll_divfrac 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_HDMIPLL_DIVFRAC_DIV_MAX 	0xFFFFFF
#define CLK_HDMIPLL_DIVFRAC_MIN_RATE 	CLK_HDMIPLL_MIN_RATE/CLK_HDMIPLL_DIVFRAC_DIV_MAX	//时钟最小频率宏定义
#define CLK_HDMIPLL_DIVFRAC_MAX_RATE 	CLK_HDMIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_HDMIPLL_DIVFRAC_RATE 		CLK_HDMIPLL_DIVFRAC_MIN_RATE		//时钟频率宏定义

/* clk_hdmi_slave 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_HDMI_SLAVE_DIV_MAX 	1
#define CLK_HDMI_SLAVE_MIN_RATE CLK_100M_SRC_MIN_RATE/CLK_HDMI_SLAVE_DIV_MAX	//时钟最小频率宏定义
#define CLK_HDMI_SLAVE_MAX_RATE CLK_100M_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_HDMI_SLAVE_RATE 	CLK_HDMI_SLAVE_MIN_RATE		//时钟频率宏定义

/* clk_hdmi_sck 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_HDMI_SCK_DIV_MAX 	4
#define CLK_HDMI_SCK_MIN_RATE 	CLK_HDMIPLL_DIVFRAC_MIN_RATE/CLK_HDMI_SCK_DIV_MAX	//时钟最小频率宏定义
#define CLK_HDMI_SCK_MAX_RATE 	CLK_HDMIPLL_DIVFRAC_MAX_RATE	//时钟最大频率宏定义
#define CLK_HDMI_SCK_RATE 		CLK_HDMI_SCK_MIN_RATE		//时钟频率宏定义

/* clk_mclk_hdmi 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MCLK_HDMI_DIV_MAX 	1
#define CLK_MCLK_HDMI_MIN_RATE 	CLK_HDMIPLL_DIVFRAC_MIN_RATE/CLK_MCLK_HDMI_DIV_MAX	//时钟最小频率宏定义
#define CLK_MCLK_HDMI_MAX_RATE 	CLK_HDMIPLL_DIVFRAC_MAX_RATE	//时钟最大频率宏定义
#define CLK_MCLK_HDMI_RATE 		CLK_MCLK_HDMI_MIN_RATE		//时钟频率宏定义


/* clk_asp_hdmi_adws 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ASP_HDMI_ADWS_DIV_MAX 	256
#define CLK_ASP_HDMI_ADWS_MIN_RATE	CLK_HDMIPLL_DIVFRAC_MIN_RATE/CLK_ASP_HDMI_ADWS_DIV_MAX	//时钟最小频率宏定义
#define CLK_ASP_HDMI_ADWS_MAX_RATE 	CLK_HDMIPLL_DIVFRAC_MAX_RATE	//时钟最大频率宏定义
#define CLK_ASP_HDMI_ADWS_RATE 		CLK_ASP_HDMI_ADWS_MIN_RATE		//时钟频率宏定义

/* clk_asp_hdmi_bclk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ASP_HDMI_BCLK_DIV_MAX 	4
#define CLK_ASP_HDMI_BCLK_MIN_RATE 	CLK_HDMIPLL_DIVFRAC_MIN_RATE/CLK_ASP_HDMI_BCLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_ASP_HDMI_BCLK_MAX_RATE 	CLK_HDMIPLL_DIVFRAC_MAX_RATE	//时钟最大频率宏定义
#define CLK_ASP_HDMI_BCLK_RATE 		CLK_ASP_HDMI_BCLK_MIN_RATE		//时钟频率宏定义

/* clk_asp_hdmi_ref 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ASP_HDMI_REF_DIV_MAX 	1
#define CLK_ASP_HDMI_REF_MIN_RATE 	CLK_300M_SRC_MIN_RATE/CLK_ASP_HDMI_REF_DIV_MAX	//时钟最小频率宏定义
#define CLK_ASP_HDMI_REF_MAX_RATE 	CLK_300M_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_ASP_HDMI_REF_RATE 		CLK_ASP_HDMI_REF_MIN_RATE		//时钟频率宏定义

/* clk_asp_spdif_ref 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ASP_SPDIF_REF_DIV_MAX 	2
#define CLK_ASP_SPDIF_REF_MIN_RATE 	CLK_HDMIPLL_DIVFRAC_MIN_RATE/CLK_ASP_SPDIF_REF_DIV_MAX	//时钟最小频率宏定义
#define CLK_ASP_SPDIF_REF_MAX_RATE 	CLK_HDMIPLL_DIVFRAC_MAX_RATE	//时钟最大频率宏定义
#define CLK_ASP_SPDIF_REF_RATE 		CLK_ASP_SPDIF_REF_MIN_RATE		//时钟频率宏定义

#define CLK_ASP_CFG_DIV_MAX 	1
#define CLK_ASP_CFG_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CLK_ASP_SPDIF_REF_DIV_MAX	//时钟最小频率宏定义
#define CLK_ASP_CFG_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_ASP_CFG_RATE 		CLK_ASP_CFG_MIN_RATE		//时钟频率宏定义

/* clk_isp_cfg_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ISP_CFG_CLK_DIV_MAX 	1
#define CLK_ISP_CFG_CLK_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CLK_ISP_CFG_CLK_DIV_MAX	//时钟最小频率宏定义
#define CLK_ISP_CFG_CLK_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_ISP_CFG_CLK_RATE 		CLK_ISP_CFG_CLK_MIN_RATE		//时钟频率宏定义

/* clk_isp_axi 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ISP_AXI_DIV_MAX 	1
#define CLK_ISP_AXI_MIN_RATE 	CLK_DDRBUS_DIV_MIN_RATE/CLK_ISP_AXI_DIV_MAX	//时钟最小频率宏定义
#define CLK_ISP_AXI_MAX_RATE 	CLK_DDRBUS_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_ISP_AXI_RATE 		CLK_ISP_AXI_MIN_RATE		//时钟频率宏定义

/* clk_peripll_isp_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PERIPLL_ISP_GATED_DIV_MAX 	1
#define CLK_PERIPLL_ISP_GATED_MIN_RATE 	CLK_DSPPLL_MIN_RATE/CLK_PERIPLL_ISP_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_PERIPLL_ISP_GATED_MAX_RATE 	CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_PERIPLL_ISP_GATED_RATE 		CLK_PERIPLL_ISP_GATED_MIN_RATE		//时钟频率宏定义

/* clk_isp 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ISP_DIV_MAX 	16
#define CLK_ISP_MIN_RATE 	CLK_PERIPLL_ISP_GATED_MIN_RATE/CLK_ISP_DIV_MAX	//时钟最小频率宏定义
#define CLK_ISP_MAX_RATE 	CLK_PERIPLL_ISP_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_ISP_RATE 		CLK_PERIPLL_RATE/16		//时钟频率宏定义

/* clk_peripll_isp_ref_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PERIPLL_ISP_REF_GATED_DIV_MAX 	1
#define CLK_PERIPLL_ISP_REF_GATED_MIN_RATE 	CLK_PERIPLL_MIN_RATE/CLK_PERIPLL_ISP_REF_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_PERIPLL_ISP_REF_GATED_MAX_RATE 	CLK_PERIPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_PERIPLL_ISP_REF_GATED_RATE 		CLK_PERIPLL_ISP_REF_GATED_MIN_RATE		//时钟频率宏定义

/* clk_isp_ref 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_ISP_REF_DIV_MAX 	16
#define CLK_ISP_REF_MIN_RATE 	CLK_PERIPLL_ISP_REF_GATED_MIN_RATE/CLK_ISP_REF_DIV_MAX	//时钟最小频率宏定义
#define CLK_ISP_REF_MAX_RATE 	CLK_PERIPLL_ISP_REF_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_ISP_REF_RATE 		CLK_ISP_REF_MIN_RATE		//时钟频率宏定义

/* clk_dphy0_ref 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DPHY0_REF_DIV_MAX 	1
#define CLK_DPHY0_REF_MIN_RATE 	CLK_REF_MIN_RATE/CLK_DPHY0_REF_DIV_MAX	//时钟最小频率宏定义
#define CLK_DPHY0_REF_MAX_RATE 	CLK_REF_MAX_RATE	//时钟最大频率宏定义
#define CLK_DPHY0_REF_RATE 		CLK_DPHY0_REF_MIN_RATE		//时钟频率宏定义

/* clk_dphy0_cfg 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DPHY0_CFG_DIV_MAX 	1
#define CLK_DPHY0_CFG_MIN_RATE 	CLK_REF_MIN_RATE/CLK_DPHY0_CFG_DIV_MAX	//时钟最小频率宏定义
#define CLK_DPHY0_CFG_MAX_RATE 	CLK_REF_MAX_RATE	//时钟最大频率宏定义
#define CLK_DPHY0_CFG_RATE 		CLK_DPHY0_CFG_MIN_RATE		//时钟频率宏定义

/* clk_dphy1_cfg 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DPHY1_CFG_DIV_MAX 	1
#define CLK_DPHY1_CFG_MIN_RATE 	CLK_REF_MIN_RATE/CLK_DPHY1_CFG_DIV_MAX	//时钟最小频率宏定义
#define CLK_DPHY1_CFG_MAX_RATE 	CLK_REF_MAX_RATE	//时钟最大频率宏定义
#define CLK_DPHY1_CFG_RATE 		CLK_DPHY1_CFG_MIN_RATE		//时钟频率宏定义

/* clk_dphy2_cfg 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DPHY2_CFG_DIV_MAX 	1
#define CLK_DPHY2_CFG_MIN_RATE 	CLK_REF_MIN_RATE/CLK_DPHY2_CFG_DIV_MAX	//时钟最小频率宏定义
#define CLK_DPHY2_CFG_MAX_RATE 	CLK_REF_MAX_RATE	//时钟最大频率宏定义
#define CLK_DPHY2_CFG_RATE 		CLK_DPHY2_CFG_MIN_RATE		//时钟频率宏定义


/* clk_uart0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_UART0_DIV_MAX 	1
#define CLK_UART0_MIN_RATE 	CLK_REF_MIN_RATE/CLK_UART0_DIV_MAX	//时钟最小频率宏定义
#define CLK_UART0_MAX_RATE 	CLK_REF_MAX_RATE	//时钟最大频率宏定义
#define CLK_UART0_RATE 		CLK_UART0_MIN_RATE		//时钟频率宏定义
#define PCLK_UART0_DIV_MAX 	1
#define PCLK_UART0_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_UART0_DIV_MAX	//时钟最小频率宏定义
#define PCLK_UART0_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_UART0_RATE 		PCLK_UART0_MIN_RATE		//时钟频率宏定义

/* clk_uart1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_UART1_DIV_MAX 	1
#define CLK_UART1_MIN_RATE 	CLK_REF_MIN_RATE/CLK_UART1_DIV_MAX	//时钟最小频率宏定义
#define CLK_UART1_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_UART1_RATE 		CLK_UART1_MIN_RATE		//时钟频率宏定义
#define PCLK_UART1_DIV_MAX 	1
#define PCLK_UART1_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_UART1_DIV_MAX	//时钟最小频率宏定义
#define PCLK_UART1_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_UART1_RATE 		PCLK_UART1_MIN_RATE		//时钟频率宏定义

/* clk_uart2 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_UART2_DIV_MAX 	1
#define CLK_UART2_MIN_RATE 	CLK_REF_MIN_RATE/CLK_UART2_DIV_MAX	//时钟最小频率宏定义
#define CLK_UART2_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_UART2_RATE 		CLK_UART2_MIN_RATE		//时钟频率宏定义
#define PCLK_UART2_DIV_MAX 	1
#define PCLK_UART2_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_UART2_DIV_MAX	//时钟最小频率宏定义
#define PCLK_UART2_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_UART2_RATE 		PCLK_UART2_MIN_RATE		//时钟频率宏定义

/* clk_uart3 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_UART3_DIV_MAX 	1
#define CLK_UART3_MIN_RATE 	CLK_REF_MIN_RATE/CLK_UART3_DIV_MAX	//时钟最小频率宏定义
#define CLK_UART3_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_UART3_RATE 		CLK_UART3_MIN_RATE		//时钟频率宏定义
#define PCLK_UART3_DIV_MAX 	1
#define PCLK_UART3_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_UART3_DIV_MAX	//时钟最小频率宏定义
#define PCLK_UART3_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_UART3_RATE 		PCLK_UART3_MIN_RATE		//时钟频率宏定义

/* clk_uart4 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_UART4_DIV_MAX 	1
#define CLK_UART4_MIN_RATE 	CLK_REF_MIN_RATE/CLK_UART4_DIV_MAX	//时钟最小频率宏定义
#define CLK_UART4_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_UART4_RATE 		CLK_UART4_MIN_RATE		//时钟频率宏定义
#define PCLK_UART4_DIV_MAX 	1
#define PCLK_UART4_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_UART4_DIV_MAX	//时钟最小频率宏定义
#define PCLK_UART4_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_UART4_RATE 		PCLK_UART4_MIN_RATE		//时钟频率宏定义

/* clk_uart5 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_UART5_DIV_MAX 	1
#define CLK_UART5_MIN_RATE 	CLK_REF_MIN_RATE/CLK_UART5_DIV_MAX	//时钟最小频率宏定义
#define CLK_UART5_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_UART5_RATE 		CLK_UART5_MIN_RATE		//时钟频率宏定义
#define PCLK_UART5_DIV_MAX 	1
#define PCLK_UART5_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_UART5_DIV_MAX	//时钟最小频率宏定义
#define PCLK_UART5_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_UART5_RATE 		PCLK_UART5_MIN_RATE		//时钟频率宏定义

/* clk_uart6 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_UART6_DIV_MAX 	1
#define CLK_UART6_MIN_RATE 	CLK_REF_MIN_RATE/CLK_UART6_DIV_MAX	//时钟最小频率宏定义
#define CLK_UART6_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_UART6_RATE 		CLK_UART6_MIN_RATE		//时钟频率宏定义
#define PCLK_UART6_DIV_MAX 	1
#define PCLK_UART6_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_UART6_DIV_MAX	//时钟最小频率宏定义
#define PCLK_UART6_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_UART6_RATE 		PCLK_UART6_MIN_RATE		//时钟频率宏定义

/* HCLK_MMC0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define HCLK_MMC0_DIV_MAX          1
#define HCLK_MMC0_MIN_RATE         CLK_BUS_SRC_RATE/HCLK_MMC0_DIV_MAX    //时钟最小频率宏定义
#define HCLK_MMC0_MAX_RATE         CLK_BUS_SRC_RATE    //时钟最大频率宏定义
#define HCLK_MMC0_RATE             HCLK_MMC0_MIN_RATE            //时钟频率宏定义

/* HCLK_MMC1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define HCLK_MMC1_DIV_MAX          1
#define HCLK_MMC1_MIN_RATE         CLK_BUS_SRC_RATE/HCLK_MMC1_DIV_MAX    //时钟最小频率宏定义
#define HCLK_MMC1_MAX_RATE         CLK_BUS_SRC_RATE    //时钟最大频率宏定义
#define HCLK_MMC1_RATE             HCLK_MMC1_MIN_RATE            //时钟频率宏定义

/* HCLK_MMC2 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define HCLK_MMC2_DIV_MAX          1
#define HCLK_MMC2_MIN_RATE         CLK_BUS_SRC_RATE/HCLK_MMC2_DIV_MAX    //时钟最小频率宏定义
#define HCLK_MMC2_MAX_RATE         CLK_BUS_SRC_RATE    //时钟最大频率宏定义
#define HCLK_MMC2_RATE             HCLK_MMC2_MIN_RATE            //时钟频率宏定义

/* clk_dsppll_mmc0_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DSPPLL_MMC0_GATED_DIV_MAX 	1
#define CLK_DSPPLL_MMC0_GATED_MIN_RATE 	CLK_DSPPLL_MIN_RATE/CLK_DSPPLL_MMC0_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_DSPPLL_MMC0_GATED_MAX_RATE 	CLK_DSPPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_DSPPLL_MMC0_GATED_RATE 		CLK_DSPPLL_MMC0_GATED_MIN_RATE		//时钟频率宏定义

/* clk_dsppll_mmc1_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DSPPLL_MMC1_GATED_DIV_MAX 	1
#define CLK_DSPPLL_MMC1_GATED_MIN_RATE 	CLK_DSPPLL_MIN_RATE/CLK_DSPPLL_MMC1_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_DSPPLL_MMC1_GATED_MAX_RATE 	CLK_DSPPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_DSPPLL_MMC1_GATED_RATE 		CLK_DSPPLL_MMC1_GATED_MIN_RATE		//时钟频率宏定义

/* clk_dsppll_mmc2_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DSPPLL_MMC2_GATED_DIV_MAX 	1
#define CLK_DSPPLL_MMC2_GATED_MIN_RATE 	CLK_DSPPLL_MIN_RATE/CLK_DSPPLL_MMC2_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_DSPPLL_MMC2_GATED_MAX_RATE 	CLK_DSPPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_DSPPLL_MMC2_GATED_RATE 		CLK_DSPPLL_MMC2_GATED_MIN_RATE		//时钟频率宏定义

/* clk_mmc0high 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MMC0HIGH_DIV_MAX 	 8
#define CLK_MMC0HIGH_MIN_RATE 	CLK_DSPPLL_MMC0_GATED_MIN_RATE/CLK_MMC0HIGH_DIV_MAX	//时钟最小频率宏定义
#define CLK_MMC0HIGH_MAX_RATE 	CLK_DSPPLL_MMC0_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_MMC0HIGH_RATE 		CLK_MMC0HIGH_MIN_RATE	//时钟频率宏定义

/* clk_mmc1high 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MMC1HIGH_DIV_MAX 	8
#define CLK_MMC1HIGH_MIN_RATE 	CLK_DSPPLL_MMC1_GATED_MIN_RATE/CLK_MMC1HIGH_DIV_MAX	//时钟最小频率宏定义
#define CLK_MMC1HIGH_MAX_RATE 	CLK_DSPPLL_MMC1_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_MMC1HIGH_RATE 		CLK_MMC1HIGH_MIN_RATE		//时钟频率宏定义

/* clk_mmc2high 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MMC2HIGH_DIV_MAX 	8
#define CLK_MMC2HIGH_MIN_RATE 	CLK_DSPPLL_MMC2_GATED_MIN_RATE/CLK_MMC2HIGH_DIV_MAX	//时钟最小频率宏定义
#define CLK_MMC2HIGH_MAX_RATE 	CLK_DSPPLL_MMC2_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_MMC2HIGH_RATE 		CLK_MMC2HIGH_MIN_RATE		//时钟频率宏定义

/* clk_mmc0low 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MMC0LOW_DIV_MAX 	8
#define CLK_MMC0LOW_MIN_RATE 	CLK_MMC0HIGH_MIN_RATE/CLK_MMC0LOW_DIV_MAX	//时钟最小频率宏定义
#define CLK_MMC0LOW_MAX_RATE 	CLK_MMC0HIGH_MAX_RATE	//时钟最大频率宏定义
#define CLK_MMC0LOW_RATE 		CLK_MMC0HIGH_RATE/6		//时钟频率宏定义

/* clk_mmc1low 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MMC1LOW_DIV_MAX 	8
#define CLK_MMC1LOW_MIN_RATE 	CLK_MMC1HIGH_MIN_RATE/CLK_MMC1LOW_DIV_MAX	//时钟最小频率宏定义
#define CLK_MMC1LOW_MAX_RATE 	CLK_MMC1HIGH_MAX_RATE	//时钟最大频率宏定义
#define CLK_MMC1LOW_RATE 		CLK_MMC1HIGH_RATE/6		//时钟频率宏定义

/* clk_mmc2low 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_MMC2LOW_DIV_MAX 	8
#define CLK_MMC2LOW_MIN_RATE 	CLK_MMC2HIGH_MIN_RATE/CLK_MMC2LOW_DIV_MAX	//时钟最小频率宏定义
#define CLK_MMC2LOW_MAX_RATE 	CLK_MMC2HIGH_MAX_RATE	//时钟最大频率宏定义
#define CLK_MMC2LOW_RATE 		CLK_MMC2HIGH_RATE/6		//时钟频率宏定义

/* clk_ddrio_div 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DDRIO_DIV_DIV_MAX 	64
#define CLK_DDRIO_DIV_MIN_RATE 	CLK_DDRPLL_MIN_RATE/CLK_DDRIO_DIV_DIV_MAX	//时钟最小频率宏定义
#define CLK_DDRIO_DIV_MAX_RATE 	CLK_DSPPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_DDRIO_DIV_RATE 		CLK_DDRIO_DIV_MIN_RATE		//时钟频率宏定义

/* clk_ddrio 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DDRIO_DIV_MAX 	1
#define CLK_DDRIO_MIN_RATE 	CLK_DDRIO_DIV_MIN_RATE/CLK_DDRIO_DIV_MAX	//时钟最小频率宏定义
#define CLK_DDRIO_MAX_RATE 	CLK_DDRIO_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_DDRIO_RATE 		CLK_DDRIO_MIN_RATE		//时钟频率宏定义

/* clk_ddrc_div 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DDRC_DIV_DIV_MAX 	2
#define CLK_DDRC_DIV_MIN_RATE 	CLK_DDRIO_DIV_MIN_RATE/CLK_DDRC_DIV_DIV_MAX	//时钟最小频率宏定义
#define CLK_DDRC_DIV_MAX_RATE 	CLK_DDRIO_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_DDRC_DIV_RATE 		CLK_DDRC_DIV_MIN_RATE		//时钟频率宏定义

/* clk_ddrc 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DDRC_DIV_MAX 1
#define CLK_DDRC_RATE 0		//时钟频率宏定义
#define CLK_DDRC_MIN_RATE CLK_DDRC_RATE/CLK_DDRC_DIV_MAX	//时钟最小频率宏定义
#define CLK_DDRC_MAX_RATE CLK_DDRC_RATE	//时钟最大频率宏定义

/* clk_ddrbus_div 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DDRBUS_DIV_MAX 		2
#define CLK_DDRBUS_DIV_MIN_RATE CLK_DDRC_DIV_MIN_RATE/CLK_DDRBUS_DIV_MAX	//时钟最小频率宏定义
#define CLK_DDRBUS_DIV_MAX_RATE CLK_DDRC_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_DDRBUS_DIV_RATE 	CLK_DDRBUS_DIV_MIN_RATE		//时钟频率宏定义

/* clk_ddrphy 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DDRPHY_DIV_MAX 	1
#define CLK_DDRPHY_MIN_RATE CLK_DDRC_DIV_MIN_RATE/CLK_DDRPHY_DIV_MAX	//时钟最小频率宏定义
#define CLK_DDRPHY_MAX_RATE CLK_DDRC_DIV_MAX_RATE	//时钟最大频率宏定义
#define CLK_DDRPHY_RATE 	CLK_DDRPHY_MIN_RATE		//时钟频率宏定义

/* clk_i2c0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_I2C0_DIV_MAX 	1
#define CLK_I2C0_MIN_RATE 	CLKIN_SYS_MIN_RATE/CLK_I2C0_DIV_MAX	//时钟最小频率宏定义
#define CLK_I2C0_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_I2C0_RATE 		CLK_I2C0_MIN_RATE		//时钟频率宏定义
#define PCLK_I2C0_DIV_MAX 	1
#define PCLK_I2C0_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_I2C0_DIV_MAX	//时钟最小频率宏定义
#define PCLK_I2C0_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_I2C0_RATE 		PCLK_I2C0_MIN_RATE		//时钟频率宏定义

/* clk_i2c1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_I2C1_DIV_MAX 	1
#define CLK_I2C1_MIN_RATE 	CLKIN_SYS_MIN_RATE/CLK_I2C1_DIV_MAX	//时钟最小频率宏定义
#define CLK_I2C1_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_I2C1_RATE 		CLK_I2C1_MIN_RATE		//时钟频率宏定义
#define PCLK_I2C1_DIV_MAX 	1
#define PCLK_I2C1_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_I2C1_DIV_MAX	//时钟最小频率宏定义
#define PCLK_I2C1_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_I2C1_RATE 		PCLK_I2C1_MIN_RATE		//时钟频率宏定义

/* clk_i2c2 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_I2C2_DIV_MAX 	1
#define CLK_I2C2_MIN_RATE 	CLKIN_SYS_MIN_RATE/CLK_I2C2_DIV_MAX	//时钟最小频率宏定义
#define CLK_I2C2_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_I2C2_RATE 		CLK_I2C2_MIN_RATE		//时钟频率宏定义
#define PCLK_I2C2_DIV_MAX 	1
#define PCLK_I2C2_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_I2C2_DIV_MAX	//时钟最小频率宏定义
#define PCLK_I2C2_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_I2C2_RATE 		PCLK_I2C2_MIN_RATE		//时钟频率宏定义

/* clk_i2c3 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_I2C3_DIV_MAX 	1
#define CLK_I2C3_MIN_RATE 	CLKIN_SYS_MIN_RATE/CLK_I2C3_DIV_MAX	//时钟最小频率宏定义
#define CLK_I2C3_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_I2C3_RATE 		CLK_I2C3_MIN_RATE		//时钟频率宏定义
#define PCLK_I2C3_DIV_MAX 	1
#define PCLK_I2C3_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_I2C3_DIV_MAX	//时钟最小频率宏定义
#define PCLK_I2C3_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_I2C3_RATE 		PCLK_I2C3_MIN_RATE		//时钟频率宏定义

/* clk_i2c4 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_I2C4_DIV_MAX 	1
#define CLK_I2C4_MIN_RATE 	CLKIN_SYS_MIN_RATE/CLK_I2C4_DIV_MAX	//时钟最小频率宏定义
#define CLK_I2C4_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_I2C4_RATE 		CLK_I2C4_MIN_RATE		//时钟频率宏定义
#define PCLK_I2C4_DIV_MAX 	1
#define PCLK_I2C4_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_I2C4_DIV_MAX	//时钟最小频率宏定义
#define PCLK_I2C4_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_I2C4_RATE 		PCLK_I2C4_MIN_RATE		//时钟频率宏定义

/* clk_i2c5 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_I2C5_DIV_MAX 	1
#define CLK_I2C5_MIN_RATE 	CLKIN_SYS_MIN_RATE/CLK_I2C5_DIV_MAX	//时钟最小频率宏定义
#define CLK_I2C5_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_I2C5_RATE 		CLK_I2C5_MIN_RATE		//时钟频率宏定义
#define PCLK_I2C5_DIV_MAX 	1
#define PCLK_I2C5_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_I2C5_DIV_MAX	//时钟最小频率宏定义
#define PCLK_I2C5_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_I2C5_RATE 		PCLK_I2C5_MIN_RATE		//时钟频率宏定义

/* clk_pwm0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PWM0_DIV_MAX 	64
#define CLK_PWM0_MIN_RATE 	CLK_REF32K_MIN_RATE/CLK_PWM0_DIV_MAX	//时钟最小频率宏定义
#define CLK_PWM0_MAX_RATE 	CLK_REF_MAX_RATE	//时钟最大频率宏定义
#define CLK_PWM0_RATE 		CLK_PWM0_MIN_RATE		//时钟频率宏定义

/* pclk_pwm0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_PWM0_DIV_MAX 	1
#define PCLK_PWM0_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/PCLK_PWM0_DIV_MAX	//时钟最小频率宏定义
#define PCLK_PWM0_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define PCLK_PWM0_RATE 		CLK_BUS_SRC_RATE		//时钟频率宏定义

/* clk_pwm1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PWM1_DIV_MAX 	64
#define CLK_PWM1_MIN_RATE 	CLK_REF32K_MIN_RATE/CLK_PWM1_DIV_MAX	//时钟最小频率宏定义
#define CLK_PWM1_MAX_RATE 	CLK_REF_MAX_RATE	//时钟最大频率宏定义
#define CLK_PWM1_RATE 		CLK_PWM1_MIN_RATE		//时钟频率宏定义

/* pclk_pwm1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_PWM1_DIV_MAX 	1
#define PCLK_PWM1_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/PCLK_PWM0_DIV_MAX	//时钟最小频率宏定义
#define PCLK_PWM1_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define PCLK_PWM1_RATE 		CLK_BUS_SRC_RATE		//时钟频率宏定义

/* clk_spi0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_SPI0_DIV_MAX 	1
#define CLK_SPI0_MIN_RATE 	CLKIN_SYS_MIN_RATE/CLK_SPI0_DIV_MAX	//时钟最小频率宏定义
#define CLK_SPI0_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_SPI0_RATE 		CLK_SPI0_MIN_RATE		//时钟频率宏定义
#define PCLK_SPI0_DIV_MAX 	1
#define PCLK_SPI0_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_SPI0_DIV_MAX	//时钟最小频率宏定义
#define PCLK_SPI0_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_SPI0_RATE 		PCLK_SPI0_MIN_RATE		//时钟频率宏定义

/* clk_spi1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_SPI1_DIV_MAX 	1
#define CLK_SPI1_MIN_RATE 	CLKIN_SYS_MIN_RATE/CLK_SPI1_DIV_MAX	//时钟最小频率宏定义
#define CLK_SPI1_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define CLK_SPI1_RATE 		CLK_SPI1_MIN_RATE		//时钟频率宏定义
#define PCLK_SPI1_DIV_MAX 	1
#define PCLK_SPI1_MIN_RATE 	CLKIN_SYS_MIN_RATE/PCLK_SPI1_DIV_MAX	//时钟最小频率宏定义
#define PCLK_SPI1_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define PCLK_SPI1_RATE 		PCLK_SPI1_MIN_RATE		//时钟频率宏定义

/* clk_dsppll_hifi_core_gated 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_DSPPLL_HIFI_CORE_GATED_DIV_MAX 	1
#define CLK_DSPPLL_HIFI_CORE_GATED_MIN_RATE CLK_DSPPLL_MIN_RATE/CLK_DSPPLL_HIFI_CORE_GATED_DIV_MAX	//时钟最小频率宏定义
#define CLK_DSPPLL_HIFI_CORE_GATED_MAX_RATE CLK_DSPPLL_MAX_RATE	//时钟最大频率宏定义
#define CLK_DSPPLL_HIFI_CORE_GATED_RATE 	CLK_DSPPLL_HIFI_CORE_GATED_MIN_RATE		//时钟频率宏定义

/* clk_hifi_core 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_HIFI_CORE_DIV_MAX 	1
#define CLK_HIFI_CORE_MIN_RATE 	CLK_DSPPLL_HIFI_CORE_GATED_MIN_RATE/CLK_HIFI_CORE_DIV_MAX	//时钟最小频率宏定义
#define CLK_HIFI_CORE_MAX_RATE 	CLK_DSPPLL_HIFI_CORE_GATED_MAX_RATE	//时钟最大频率宏定义
#define CLK_HIFI_CORE_RATE 		CLK_HIFI_CORE_MIN_RATE		//时钟频率宏定义
#define CLK_CSI_APB_MUX_DIV_MAX 	1
#define CLK_CSI_APB_MUX_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CLK_CSI_APB_MUX_DIV_MAX	//时钟最小频率宏定义
#define CLK_CSI_APB_MUX_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_CSI_APB_MUX_RATE 		CLK_CSI_APB_MUX_MIN_RATE		//时钟频率宏定义

/* clk_csio_cfg 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_CSIO_CFG_DIV_MAX 	1
#define CLK_CSIO_CFG_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CLK_CSIO_CFG_DIV_MAX	//时钟最小频率宏定义
#define CLK_CSIO_CFG_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CLK_CSIO_CFG_RATE 		CLK_CSIO_CFG_MIN_RATE		//时钟频率宏定义

/* csi1_cfg_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CSI1_CFG_CLK_DIV_MAX 	1
#define CSI1_CFG_CLK_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CSI1_CFG_CLK_DIV_MAX	//时钟最小频率宏定义
#define CSI1_CFG_CLK_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CSI1_CFG_CLK_RATE 		CSI1_CFG_CLK_MIN_RATE		//时钟频率宏定义

/* csi2_cfg_clk 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CSI2_CFG_CLK_DIV_MAX 	1
#define CSI2_CFG_CLK_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/CSI2_CFG_CLK_DIV_MAX	//时钟最小频率宏定义
#define CSI2_CFG_CLK_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define CSI2_CFG_CLK_RATE 		CSI2_CFG_CLK_MIN_RATE		//时钟频率宏定义

/*clk_pmussi 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_PMUSSI_DIV_MAX    1
#define CLK_PMUSSI_MIN_RATE   CLK_REF_MIN_RATE/CLK_PMUSSI_DIV_MAX   //时钟最小频率宏定义
#define CLK_PMUSSI_MAX_RATE   CLK_REF_MAX_RATE    //时钟最大频率宏定义
#define CLK_PMUSSI_RATE       CLK_PMUSSI_MIN_RATE       //时钟频率宏定义

/* CLK_RTC 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_RTC_DIV_MAX          1
#define CLK_RTC_MIN_RATE         1/CLK_RTC_DIV_MAX    //时钟最小频率宏定义
#define CLK_RTC_MAX_RATE         1    //时钟最大频率宏定义
#define CLK_RTC_RATE             CLK_RTC_MIN_RATE            //时钟频率宏定义

/* HCLK_NANDC 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define HCLK_NANDC_DIV_MAX          1
#define HCLK_NANDC_MIN_RATE         CLK_BUS_SRC_RATE/HCLK_NANDC_DIV_MAX    //时钟最小频率宏定义
#define HCLK_NANDC_MAX_RATE         CLK_BUS_SRC_RATE    //时钟最大频率宏定义
#define HCLK_NANDC_RATE             HCLK_NANDC_MIN_RATE            //时钟频率宏定义

/*clk_watchdog0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_WATCHDOG0_DIV_MAX       1
#define CLK_WATCHDOG0_MIN_RATE      CLK_REF32K_MIN_RATE/CLK_WATCHDOG0_DIV_MAX   //时钟最小频率宏定义
#define CLK_WATCHDOG0_MAX_RATE      CLK_REF32K_MAX_RATE    //时钟最大频率宏定义
#define CLK_WATCHDOG0_RATE          CLK_WATCHDOG0_MIN_RATE       //时钟频率宏定义
#define PCLK_WATCHDOG0_DIV_MAX      1
#define PCLK_WATCHDOG0_MIN_RATE     CLK_REF32K_MIN_RATE/PCLK_WATCHDOG0_DIV_MAX   //时钟最小频率宏定义
#define PCLK_WATCHDOG0_MAX_RATE     CLK_REF32K_MAX_RATE    //时钟最大频率宏定义
#define PCLK_WATCHDOG0_RATE         PCLK_WATCHDOG0_MIN_RATE       //时钟频率宏定义

#define HCLK_USBOTG_ON_DIV_MAX 	    1
#define HCLK_USBOTG_ON_MIN_RATE 	CLKIN_SYS_MIN_RATE/HCLK_USBOTG_ON_DIV_MAX	//时钟最小频率宏定义
#define HCLK_USBOTG_ON_MAX_RATE 	CLKIN_SYS_MAX_RATE	//时钟最大频率宏定义
#define HCLK_USBOTG_ON_RATE 		HCLK_USBOTG_ON_MIN_RATE		//时钟频率宏定义

#define HCLK_USBOTG_OFF_DIV_MAX 	1
#define HCLK_USBOTG_OFF_MIN_RATE 	CLK_BUS_SRC_MIN_RATE/HCLK_USBOTG_OFF_DIV_MAX	//时钟最小频率宏定义
#define HCLK_USBOTG_OFF_MAX_RATE 	CLK_BUS_SRC_MAX_RATE	//时钟最大频率宏定义
#define HCLK_USBOTG_OFF_RATE 		CLK_BUS_SRC_RATE		//时钟频率宏定义

#define CLK_USBOTG_OFF_DIV_MAX 	1
#define CLK_USBOTG_OFF_MIN_RATE 	60000000/CLK_PICOPHY_DIV_MAX	//时钟最小频率宏定义
#define CLK_USBOTG_OFF_MAX_RATE 	60000000	//时钟最大频率宏定义
#define CLK_USBOTG_OFF_RATE 		CLK_USBOTG_OFF_MIN_RATE		//时钟频率宏定义

#define CLK_PICOPHY_DIV_MAX 	1
#define CLK_PICOPHY_MIN_RATE 	19200000/CLK_PICOPHY_DIV_MAX	//时钟最小频率宏定义
#define CLK_PICOPHY_MAX_RATE 	19200000	//时钟最大频率宏定义
#define CLK_PICOPHY_RATE 		CLK_PICOPHY_MIN_RATE		//时钟频率宏定义

#define CLK_PICOPHY_TEST_DIV_MAX 	1
#define CLK_PICOPHY_TEST_MIN_RATE 	37500000/CLK_PICOPHY_TEST_DIV_MAX	//时钟最小频率宏定义
#define CLK_PICOPHY_TEST_MAX_RATE 	37500000	//时钟最大频率宏定义
#define CLK_PICOPHY_TEST_RATE 		CLK_PICOPHY_TEST_MIN_RATE		//时钟频率宏定义

#define CLK_TS_DIV_MAX 	1
#define CLK_TS_MIN_RATE 	60000000/CLK_TS_DIV_MAX	//时钟最小频率宏定义
#define CLK_TS_MAX_RATE 	60000000	//时钟最大频率宏定义
#define CLK_TS_RATE 		CLK_TS_MIN_RATE		//时钟频率宏定义

#define HCLK_TS_DIV_MAX 	1
#define HCLK_TS_MIN_RATE 	CLK_BUS_SRC_RATE/HCLK_TS_DIV_MAX	//时钟最小频率宏定义
#define HCLK_TS_MAX_RATE 	CLK_BUS_SRC_RATE	//时钟最大频率宏定义
#define HCLK_TS_RATE 		HCLK_TS_MIN_RATE		//时钟频率宏定义

#define CLK_GPS_DIV_MAX 	1
#define CLK_GPS_MIN_RATE 	CLK_REF_RATE/CLK_GPS_DIV_MAX	//时钟最小频率宏定义
#define CLK_GPS_MAX_RATE 	CLK_REF_RATE	//时钟最大频率宏定义
#define CLK_GPS_RATE 		HCLK_TS_MIN_RATE		//时钟频率宏定义

#define CLK_TSENSOR0_DIV_MAX 	1
#define CLK_TSENSOR0_MIN_RATE 	1000000/HCLK_TS_DIV_MAX	//时钟最小频率宏定义
#define CLK_TSENSOR0_MAX_RATE 	1000000	//时钟最大频率宏定义
#define CLK_TSENSOR0_RATE 		CLK_TSENSOR0_MIN_RATE		//时钟频率宏定义

#define CLK_TSENSOR1_DIV_MAX 	1
#define CLK_TSENSOR1_MIN_RATE 	1000000/HCLK_TS_DIV_MAX	//时钟最小频率宏定义
#define CLK_TSENSOR1_MAX_RATE 	1000000	//时钟最大频率宏定义
#define CLK_TSENSOR1_RATE 		CLK_TSENSOR1_MIN_RATE		//时钟频率宏定义

/* CLK_AP_DMAC_AXI0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_AP_DMAC_AXI0_DIV_MAX          1
#define CLK_AP_DMAC_AXI0_MIN_RATE         CLK_BUS_SRC_RATE/CLK_AP_DMAC_AXI0_DIV_MAX    //时钟最小频率宏定义
#define CLK_AP_DMAC_AXI0_MAX_RATE         CLK_BUS_SRC_RATE    //时钟最大频率宏定义
#define CLK_AP_DMAC_AXI0_RATE             CLK_AP_DMAC_AXI0_MIN_RATE            //时钟频率宏定义

/* CLK_AP_DMAC_AXI1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_AP_DMAC_AXI1_DIV_MAX          1
#define CLK_AP_DMAC_AXI1_MIN_RATE         CLK_BUS_SRC_RATE/CLK_AP_DMAC_AXI1_DIV_MAX    //时钟最小频率宏定义
#define CLK_AP_DMAC_AXI1_MAX_RATE         CLK_BUS_SRC_RATE    //时钟最大频率宏定义
#define CLK_AP_DMAC_AXI1_RATE             CLK_AP_DMAC_AXI1_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER0_DIV_MAX          1
#define PCLK_TIMER0_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER0_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER0_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER0_RATE             PCLK_TIMER0_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER0 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER0_DIV_MAX          1
#define CLK_TIMER0_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER0_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER0_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER0_RATE             CLK_TIMER0_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER1_DIV_MAX          1
#define PCLK_TIMER1_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER1_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER1_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER1_RATE             PCLK_TIMER1_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER1 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER1_DIV_MAX          1
#define CLK_TIMER1_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER1_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER1_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER1_RATE             CLK_TIMER1_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER2 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER2_DIV_MAX          1
#define PCLK_TIMER2_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER2_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER2_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER2_RATE             PCLK_TIMER2_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER2 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER2_DIV_MAX          1
#define CLK_TIMER2_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER2_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER2_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER2_RATE             CLK_TIMER2_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER3 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER3_DIV_MAX          1
#define PCLK_TIMER3_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER3_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER3_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER3_RATE             PCLK_TIMER3_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER3 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER3_DIV_MAX          1
#define CLK_TIMER3_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER3_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER3_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER3_RATE             CLK_TIMER3_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER4 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER4_DIV_MAX          1
#define PCLK_TIMER4_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER4_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER4_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER4_RATE             PCLK_TIMER4_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER4 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER4_DIV_MAX          1
#define CLK_TIMER4_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER4_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER4_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER4_RATE             CLK_TIMER4_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER5 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER5_DIV_MAX          1
#define PCLK_TIMER5_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER5_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER5_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER5_RATE             PCLK_TIMER5_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER5 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER5_DIV_MAX          1
#define CLK_TIMER5_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER5_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER5_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER5_RATE             CLK_TIMER5_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER6 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER6_DIV_MAX          1
#define PCLK_TIMER6_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER6_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER6_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER6_RATE             PCLK_TIMER6_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER6 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER6_DIV_MAX          1
#define CLK_TIMER6_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER6_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER6_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER6_RATE             CLK_TIMER6_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER7 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER7_DIV_MAX          1
#define PCLK_TIMER7_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER7_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER7_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER7_RATE             PCLK_TIMER7_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER7 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER7_DIV_MAX          1
#define CLK_TIMER7_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER7_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER7_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER7_RATE             CLK_TIMER7_MIN_RATE            //时钟频率宏定义

/* PCLK_TIMER8 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define PCLK_TIMER8_DIV_MAX          1
#define PCLK_TIMER8_MIN_RATE         CLKIN_SYS_RATE/PCLK_TIMER8_DIV_MAX    //时钟最小频率宏定义
#define PCLK_TIMER8_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define PCLK_TIMER8_RATE             PCLK_TIMER8_MIN_RATE            //时钟频率宏定义

/* CLK_TIMER8 基本信息，包括clock宏名、频率、最小频率，最大频率 */
#define CLK_TIMER8_DIV_MAX          1
#define CLK_TIMER8_MIN_RATE         CLK_REF32K_MIN_RATE/CLK_TIMER8_DIV_MAX    //时钟最小频率宏定义
#define CLK_TIMER8_MAX_RATE         CLKIN_SYS_RATE    //时钟最大频率宏定义
#define CLK_TIMER8_RATE             CLK_TIMER8_MIN_RATE            //时钟频率宏定义

#define CLK_GPIO0_DIV_MAX      1
#define CLK_GPIO0_MIN_RATE     CLK_BUS_SRC_MIN_RATE/CLK_GPIO0_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO0_MAX_RATE     CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO0_RATE                 CLK_GPIO0_MIN_RATE              //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>

#define CLK_GPIO1_DIV_MAX   1
#define CLK_GPIO1_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO1_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO1_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO1_RATE      CLK_GPIO1_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO2_DIV_MAX   1
#define CLK_GPIO2_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO2_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO2_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO2_RATE      CLK_GPIO2_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO3_DIV_MAX   1
#define CLK_GPIO3_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO3_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO3_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO3_RATE      CLK_GPIO3_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO4_DIV_MAX   1
#define CLK_GPIO4_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO4_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO4_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO4_RATE      CLK_GPIO4_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO5_DIV_MAX   1
#define CLK_GPIO5_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO5_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO5_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO5_RATE      CLK_GPIO5_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO6_DIV_MAX   1
#define CLK_GPIO6_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO6_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO6_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO6_RATE      CLK_GPIO6_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO7_DIV_MAX   1
#define CLK_GPIO7_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO7_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO7_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO7_RATE      CLK_GPIO7_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO8_DIV_MAX   1
#define CLK_GPIO8_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO8_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO8_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO8_RATE      CLK_GPIO8_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO9_DIV_MAX   1
#define CLK_GPIO9_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO9_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO9_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO9_RATE      CLK_GPIO9_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO10_DIV_MAX   1
#define CLK_GPIO10_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO10_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO10_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO10_RATE      CLK_GPIO10_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO11_DIV_MAX   1
#define CLK_GPIO11_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO11_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO11_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO11_RATE      CLK_GPIO11_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO12_DIV_MAX   1
#define CLK_GPIO12_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO12_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO12_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO12_RATE      CLK_GPIO12_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO13_DIV_MAX   1
#define CLK_GPIO13_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO13_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO13_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO13_RATE      CLK_GPIO13_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO14_DIV_MAX   1
#define CLK_GPIO14_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO14_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO14_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO14_RATE      CLK_GPIO14_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO15_DIV_MAX   1
#define CLK_GPIO15_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO15_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO15_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO15_RATE      CLK_GPIO15_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO16_DIV_MAX   1
#define CLK_GPIO16_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO16_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO16_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO16_RATE      CLK_GPIO16_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO17_DIV_MAX   1
#define CLK_GPIO17_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO17_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO17_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO17_RATE      CLK_GPIO17_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO18_DIV_MAX   1
#define CLK_GPIO18_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO18_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO18_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO18_RATE      CLK_GPIO18_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO19_DIV_MAX   1
#define CLK_GPIO19_MIN_RATE  CLK_BUS_SRC_MIN_RATE/CLK_GPIO18_DIV_MAX  //ê±<D6><D3><D7><EE>D??μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO19_MAX_RATE  CLK_BUS_SRC_MAX_RATE    //ê±<D6><D3><D7><EE><B4><F3>?μ<C2>êoê?¨<D2><E5>
#define CLK_GPIO19_RATE      CLK_GPIO18_MIN_RATE      //ê±<D6><D3>?μ<C2>êoê?¨<D2><E5>


