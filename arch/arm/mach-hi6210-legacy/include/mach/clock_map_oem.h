/***********************************************************************************************************************
说明：该文件内容是Clock模块使用宏的装定义，转定义soc_baseaddr_interface.h、
      soc_sctrl_interface.h和soc_pmctrl_interface.h
************************************************************************************************************************/
#include "soc_baseaddr_interface.h" /* 寄存器基址转换生成的头文件 */
#if defined (CHIP_BB_HI6210)
#include "soc_peri_sctrl_interface.h"
#elif defined (CHIP_BB_HI6620)
#include "soc_sctrl_interface.h"    /* 系统控制寄存器转换生成的头文件 */
#endif
#include "soc_ao_sctrl_interface.h" /* AO系统控制寄存器转换生成的头文件 */
#include "soc_pmctrl_interface.h"   /* PM控制寄存器转换生成的头文件 */
#include "soc_smart_interface.h"   /* SMART STAR控制寄存器转换生成的头文件 */
#include "mach/hardware.h"

#define DISABLE_REG_OFFSET 0x04
#define ENASTAT_REG_OFFSET 0x08

#define CLKDIV_SET_INVALID -1
#define CLKSEL_SET_INVALID -1

#define CALC_REG_MASK(bit_start, bit_end) \
    (((0x1 << (bit_end - bit_start + 1)) - 1) << bit_start)


#define SCTRL_OFF_BASE_ADDR  IO_ADDRESS(SOC_SC_OFF_BASE_ADDR)
#define SCTRL_ON_BASE_ADDR   IO_ADDRESS(SOC_SC_ON_BASE_ADDR)
#define PMCTRL_BASE_ADDR     IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)

/* clkin_sys操作宏相关转定义 */
/* 转定义时钟clkin_sys的使能寄存器，状态寄存器的地址和位偏移 */
#define CLKIN_SYS_ENABLE_REG_ADDR   NULL    /* 使能寄存器地址转定义宏 */
#define CLKIN_SYS_ENABLE_BIT_OFFSET 0   /* 时钟使能位偏移 */

/* 转定义时钟clkin_sys的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLKIN_SYS_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLKIN_SYS_CLKSEL_MASK       0   //父时钟选择掩码
#define CLKIN_SYS_CLKSEL_SET_VALID  0       //父时钟选择有效标志位
#define CLKIN_SYS_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLKIN_SYS_CLKDIV_MASK       0                   //时钟分频掩码
#define CLKIN_SYS_CLKDIV_SET_VALID  0       //时钟分频设置有效标志位

/* clkin_sys操作宏相关转定义 */

/* clk_ref操作宏相关转定义 */
/* 转定义时钟clk_ref的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_REF_ENABLE_REG_ADDR     NULL    /* 使能寄存器地址转定义宏 */
#define CLK_REF_ENABLE_BIT_OFFSET   0  /* 时钟使能位偏移 */

/* 转定义时钟clk_ref的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_REF_CLKSEL_REG_ADDR    NULL                 //父时钟选择寄存器地址转定义宏
#define CLK_REF_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_REF_CLKSEL_SET_VALID   0   //父时钟选择有效标志位
#define CLK_REF_CLKDIV_REG_ADDR    NULL                 //时钟分频寄存器地址转定义宏
#define CLK_REF_CLKDIV_MASK        0    //时钟分频掩码
#define CLK_REF_CLKDIV_SET_VALID   0   //时钟分频设置有效标志位

/* clk_ref32k操作宏相关转定义 */
/* 转定义时钟clk_ref32k的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_REF32K_ENABLE_REG_ADDR  NULL    /* 使能寄存器地址转定义宏 */
#define CLK_REF32K_ENABLE_BIT_OFFSET    0   /* 时钟使能位偏移 */

/* 转定义时钟clk_ref32k的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_REF32K_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_REF32K_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_REF32K_CLKSEL_SET_VALID 0       //父时钟选择有效标志位
#define CLK_REF32K_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_REF32K_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_REF32K_CLKDIV_SET_VALID 0       //时钟分频设置有效标志位

/* clk_ref32k操作宏相关转定义 */


/* clk_pmu32kb操作宏相关转定义 */
/* 转定义时钟clk_ref的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PMU32KB_ENABLE_REG_ADDR     SOC_SMART_ONOFF8_ADDR(0)    /* 使能寄存器地址转定义宏 */
#define CLK_PMU32KB_ENABLE_BIT_OFFSET   SOC_SMART_ONOFF8_en_32kb_START  /* 时钟使能位偏移 */
/* clk_pmu32kb操作宏相关转定义 */

/* clk_pmu32kc操作宏相关转定义 */
/* 转定义时钟clk_ref的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PMU32KC_ENABLE_REG_ADDR     SOC_SMART_ONOFF8_ADDR(0)    /* 使能寄存器地址转定义宏 */
#define CLK_PMU32KC_ENABLE_BIT_OFFSET   SOC_SMART_ONOFF8_en_32kc_START  /* 时钟使能位偏移 */
/* clk_pmu32kc操作宏相关转定义 */


/* clk_apll0操作宏相关转定义 */
/* 转定义时钟clk_apll0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_APLL0_ENABLE_REG_ADDR   NULL    /* 使能寄存器地址转定义宏 */
#define CLK_APLL0_ENABLE_BIT_OFFSET 0   /* 时钟使能位偏移 */

/* 转定义时钟clk_apll0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_APLL0_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_APLL0_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_APLL0_CLKSEL_SET_VALID  0       //父时钟选择有效标志位
#define CLK_APLL0_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_APLL0_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_APLL0_CLKDIV_SET_VALID  0       //时钟分频设置有效标志位

/* clk_apll1操作宏相关转定义 */
/* 转定义时钟clk_apll1的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_APLL1_ENABLE_REG_ADDR   NULL    /* 使能寄存器地址转定义宏 */
#define CLK_APLL1_ENABLE_BIT_OFFSET 0   /* 时钟使能位偏移 */

/* 转定义时钟clk_apll1的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_APLL1_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_APLL1_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_APLL1_CLKSEL_SET_VALID  0       //父时钟选择有效标志位
#define CLK_APLL1_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_APLL1_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_APLL1_CLKDIV_SET_VALID  0       //时钟分频设置有效标志位

/* clk_dsplpl操作宏相关转定义 */
/* 转定义时钟clk_dsppll的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DSPPLL_ENABLE_REG_ADDR  NULL    /* 使能寄存器地址转定义宏 */
#define CLK_DSPPLL_ENABLE_BIT_OFFSET    0   /* 时钟使能位偏移 */

/* 转定义时钟clk_dsppll的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DSPPLL_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DSPPLL_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_DSPPLL_CLKSEL_SET_VALID 0       //父时钟选择有效标志位
#define CLK_DSPPLL_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_DSPPLL_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_DSPPLL_CLKDIV_SET_VALID 0       //时钟分频设置有效标志位

/* clk_gpll0操作宏相关转定义 */
/* 转定义时钟clk_gpll0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_GPLL0_ENABLE_REG_ADDR   SOC_PMCTRL_G3DPLL0CTRL_ADDR(PMCTRL_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_GPLL0_ENABLE_BIT_OFFSET SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_en_cfg_START /* 时钟使能位偏移 */

/* 转定义时钟clk_gpll0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_GPLL0_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_GPLL0_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_GPLL0_CLKSEL_SET_VALID  0       //父时钟选择有效标志位
#define CLK_GPLL0_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_GPLL0_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_GPLL0_CLKDIV_SET_VALID  0       //时钟分频设置有效标志位

/* clk_gpll1操作宏相关转定义 */
/* 转定义时钟clk_gpll1的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_GPLL1_ENABLE_REG_ADDR   NULL    /* 使能寄存器地址转定义宏 */
#define CLK_GPLL1_ENABLE_BIT_OFFSET 0   /* 时钟使能位偏移 */

/* 转定义时钟clk_gpll1的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_GPLL1_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_GPLL1_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_GPLL1_CLKSEL_SET_VALID  0       //父时钟选择有效标志位
#define CLK_GPLL1_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_GPLL1_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_GPLL1_CLKDIV_SET_VALID  0       //时钟分频设置有效标志位

/* clk_peripll操作宏相关转定义 */
/* 转定义时钟clk_peripll的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PERIPLL_ENABLE_REG_ADDR SOC_PMCTRL_PERIPLLCTRL_ADDR(PMCTRL_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_PERIPLL_ENABLE_BIT_OFFSET   SOC_PMCTRL_PERIPLLCTRL_peripll_en_START

#define CLK_DDRBUS_DIV_CLKDIV_REG_ADDR  SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //时钟分频寄存器地址转定义宏
#define CLK_DDRBUS_DIV_CLKDIV_MASK      CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_END)                   //时钟分频掩码
#define CLK_DDRBUS_DIV_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* 转定义时钟clk_peripll的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_PERIPLL_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_PERIPLL_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_PERIPLL_CLKSEL_SET_VALID    0       //父时钟选择有效标志位
#define CLK_PERIPLL_CLKDIV_REG_ADDR NULL    //时钟分频寄存器地址转定义宏
#define CLK_PERIPLL_CLKDIV_MASK     0                   //时钟分频掩码
#define CLK_PERIPLL_CLKDIV_SET_VALID    0       //时钟分频设置有效标志位

/* clk_hdmipll操作宏相关转定义 */
/* 转定义时钟clk_hdmipll的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_HDMIPLL_ENABLE_REG_ADDR SOC_PMCTRL_HDMIPLLCTRL_ADDR(PMCTRL_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_HDMIPLL_ENABLE_BIT_OFFSET   SOC_PMCTRL_HDMIPLLCTRL_hdmipll_en_START   /* 时钟使能位偏移 */

/* 转定义时钟clk_hdmipll的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_HDMIPLL_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_HDMIPLL_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_HDMIPLL_CLKSEL_SET_VALID    0       //父时钟选择有效标志位
#define CLK_HDMIPLL_CLKDIV_REG_ADDR NULL    //时钟分频寄存器地址转定义宏
#define CLK_HDMIPLL_CLKDIV_MASK     0                   //时钟分频掩码
#define CLK_HDMIPLL_CLKDIV_SET_VALID    0       //时钟分频设置有效标志位

/* clk_ddrpll操作宏相关转定义 */
/* 转定义时钟clk_ddrpll的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DDRPLL_ENABLE_REG_ADDR  NULL    /* 使能寄存器地址转定义宏 */
#define CLK_DDRPLL_ENABLE_BIT_OFFSET    0   /* 时钟使能位偏移 */

/* 转定义时钟clk_ddrpll的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DDRPLL_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DDRPLL_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_DDRPLL_CLKSEL_SET_VALID 0       //父时钟选择有效标志位
#define CLK_DDRPLL_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_DDRPLL_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_DDRPLL_CLKDIV_SET_VALID 0       //时钟分频设置有效标志位

/* 转定义时钟clk_300m_src的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_300M_SRC_ENABLE_REG_ADDR    NULL    /* 使能寄存器地址转定义宏 */
#define CLK_300M_SRC_ENABLE_BIT_OFFSET  0   /* 时钟使能位偏移 */

/* 转定义时钟clk_300m_src的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_300M_SRC_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_300M_SRC_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_300M_SRC_CLKSEL_SET_VALID   0       //父时钟选择有效标志位

#define CLK_300M_SRC_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_300M_SRC_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_300M_SRC_CLKDIV_SET_VALID   0       //时钟分频设置有效标志位

/* 转定义时钟clk_100m_src的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_100M_SRC_ENABLE_REG_ADDR    NULL    /* 使能寄存器地址转定义宏 */
#define CLK_100M_SRC_ENABLE_BIT_OFFSET  0   /* 时钟使能位偏移 */

/* 转定义时钟clk_100m_src的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_100M_SRC_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_100M_SRC_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_100M_SRC_CLKSEL_SET_VALID   0       //父时钟选择有效标志位

#define CLK_100M_SRC_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_100M_SRC_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_100M_SRC_CLKDIV_SET_VALID   0       //时钟分频设置有效标志位

/* clk_bus_src 操作宏相关转定义 */
/* 转定义时钟clk_bus_src的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_BUS_SRC_ENABLE_REG_ADDR NULL    /* 使能寄存器地址转定义宏 */
#define CLK_BUS_SRC_ENABLE_BIT_OFFSET   0   /* 时钟使能位偏移 */

/* 转定义时钟clk_bus_src的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_BUS_SRC_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_BUS_SRC_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_BUS_SRC_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_BUS_SRC_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT1_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_BUS_SRC_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value1_START, \
                                        SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value1_END)                  //时钟分频掩码
#define CLK_BUS_SRC_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld1_START       //时钟分频设置有效标志位

/* clk_bus_src操作宏相关转定义 */

#define CLK_27M_GATED_ENABLE_REG_ADDR SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_27M_GATED_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_27m_START   /* 时钟使能位偏移 */

#define CLK_27M_GATED_CLKSEL_REG_ADDR  SOC_PMCTRL_CLKCFG4BIT1_ADDR(PMCTRL_BASE_ADDR)   //父时钟选择寄存器地址转定义宏
#define CLK_27M_GATED_CLKSEL_MASK      CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value0_START, \
                                                        SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value0_END)    //父时钟选择掩码
#define CLK_27M_GATED_CLKSEL_SET_VALID CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld0_START, \
                                                        SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld0_END)    //父时钟选择掩码
                                                        
#define CLK_27M_ENABLE_REG_ADDR SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_27M_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_27m_START   /* 时钟使能位偏移 */

#define CLK_27M_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT4_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_27M_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value1_START, \
                                                            SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value1_END)                  //时钟分频掩码
#define CLK_27M_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld1_START       //时钟分频设置有效标志位

#define CLK_90K_ENABLE_REG_ADDR SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_90K_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_90k_START   /* 时钟使能位偏移 */

/* clk_mali 操作宏相关转定义 */
/* 转定义时钟clk_mali的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MALI_ENABLE_REG_ADDR    SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   /* 使能寄存器地址转定义宏 */
#define CLK_MALI_ENABLE_BIT_OFFSET  SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_6clk_mali_START  /* 时钟使能位偏移 */

/* 转定义时钟clk_mali的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MALI_CLKSEL_REG_ADDR    SOC_PMCTRL_G3DCLKSEL_ADDR(PMCTRL_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_MALI_CLKSEL_MASK        CALC_REG_MASK(SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_cfg_START, SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_cfg_END) //父时钟选择掩码
#define CLK_MALI_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_stat_START, SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_stat_END)        //父时钟选择有效标志位

/* 转定义时钟 clk_mali 的时钟分频寄存器、选择掩码和设置有效标志位 */
#define CLK_MALI_CLKDIV_REG_ADDR    SOC_PMCTRL_G3DCLKDIV_ADDR(PMCTRL_BASE_ADDR) //时钟分频寄存器地址转定义宏
#define CLK_MALI_CLKDIV_MASK        CALC_REG_MASK(SOC_PMCTRL_G3DCLKDIV_g3d_clkdiv_cfg_START, \
                                            SOC_PMCTRL_G3DCLKDIV_g3d_clkdiv_cfg_END)                    //时钟分频掩码
#define CLK_MALI_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_mali操作宏相关转定义 */

/* clk_dsppll_edc0_core_gated操作宏相关转定义 */
/* 转定义时钟clk_dsppll_edc0_core_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DSPPLL_EDC0_CORE_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_DSPPLL_EDC0_CORE_GATED_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_edc0_core_gated_START           //时钟使能位偏移

/* 转定义时钟clk_dsppll_edc0_core_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKSEL_REG_ADDR  SOC_PMCTRL_CLKCFG4BIT1_ADDR(PMCTRL_BASE_ADDR)   //父时钟选择寄存器地址转定义宏
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKSEL_MASK      CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_START, \
                                                            SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_END)    //父时钟选择掩码
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKSEL_SET_VALID CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_START , \
                                                            SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_END)    //父时钟选择掩码
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_dsppll_edc0_core_gated操作宏相关转定义 */

/* clk_edc0_core操作宏相关转定义 */
/* 转定义时钟clk_edc0_core的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_EDC0_CORE_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_EDC0_CORE_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_core_START          //时钟使能位偏移

/* 转定义时钟clk_edc0_core的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_EDC0_CORE_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_EDC0_CORE_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_EDC0_CORE_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_EDC0_CORE_CLKDIV_REG_ADDR   SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_EDC0_CORE_CLKDIV_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value1_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value1_END)                  //时钟分频掩码
#define CLK_EDC0_CORE_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld1_START       //时钟分频设置有效标志位

/* clk_edc0_core操作宏相关转定义 */

/* clk_mux_edc0_pix_gated操作宏相关转定义 */
/* 转定义时钟clk_mux_edc0_pix_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MUX_EDC0_PIX_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_MUX_EDC0_PIX_GATED_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mux_edc0_pix_gated_START           //时钟使能位偏移

/* 转定义时钟clk_mux_edc0_pix_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MUX_EDC0_PIX_GATED_CLKSEL_REG_ADDR  SOC_PMCTRL_CLKCFG4BIT1_ADDR(PMCTRL_BASE_ADDR)   //父时钟选择寄存器地址转定义宏
#define CLK_MUX_EDC0_PIX_GATED_CLKSEL_MASK      CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_START, \
                                                        SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_END)    //父时钟选择掩码
#define CLK_MUX_EDC0_PIX_GATED_CLKSEL_SET_VALID CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_START, \
                                                        SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_END)    //父时钟选择掩码
                                                        
#define CLK_MUX_EDC0_PIX_GATED_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_MUX_EDC0_PIX_GATED_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_MUX_EDC0_PIX_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_mux_edc0_pix_gated操作宏相关转定义 */

/* clk_edc0_pix_ldi操作宏相关转定义 */
/* 转定义时钟clk_edc0_pix_ldi的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_EDC0_PIX_LDI_ENABLE_REG_ADDR    SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_EDC0_PIX_LDI_ENABLE_BIT_OFFSET  SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_pix_ldi_START           //时钟使能位偏移

/* 转定义时钟clk_edc0_pix_ldi的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_EDC0_PIX_LDI_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_EDC0_PIX_LDI_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_EDC0_PIX_LDI_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_EDC0_PIX_LDI_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_EDC0_PIX_LDI_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value0_START, \
                                                            SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value0_END)                  //时钟分频掩码
#define CLK_EDC0_PIX_LDI_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld0_START       //时钟分频设置有效标志位

/* clk_edc0_pix_ldi操作宏相关转定义 */

/* clk_edc1_core操作宏相关转定义 */
/* 转定义时钟clk_edc1_core的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_EDC1_CORE_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_EDC1_CORE_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_core_START          //时钟使能位偏移

/* 转定义时钟clk_edc1_core的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_EDC1_CORE_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_EDC1_CORE_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_EDC1_CORE_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_EDC1_CORE_CLKDIV_REG_ADDR   SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_EDC1_CORE_CLKDIV_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value3_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value3_END)                  //时钟分频掩码
#define CLK_EDC1_CORE_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld3_START       //时钟分频设置有效标志位

/* clk_edc1_core操作宏相关转定义 */

/* clk_axi_video_bus操作宏相关转定义 */
/* 转定义时钟clk_axi_video_bus的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_AXI_VIDEO_BUS_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_AXI_VIDEO_BUS_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_video_bus_START          //时钟使能位偏移

/* 转定义时钟clk_axi_video_bus的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_AXI_VIDEO_BUS_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_AXI_VIDEO_BUS_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_AXI_VIDEO_BUS_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_AXI_VIDEO_BUS_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_AXI_VIDEO_BUS_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_AXI_VIDEO_BUS_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_axi_video_bus操作宏相关转定义 */

/* clk_axi_img_bus操作宏相关转定义 */
/* 转定义时钟clk_axi_img_bus的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_AXI_IMG_BUS_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_AXI_IMG_BUS_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_img_bus_START            //时钟使能位偏移

/* 转定义时钟clk_axi_img_bus的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_AXI_IMG_BUS_CLKSEL_REG_ADDR     NULL    //父时钟选择寄存器地址转定义宏
#define CLK_AXI_IMG_BUS_CLKSEL_MASK         0   //父时钟选择掩码
#define CLK_AXI_IMG_BUS_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_AXI_IMG_BUS_CLKDIV_REG_ADDR     NULL    //时钟分频寄存器地址转定义宏
#define CLK_AXI_IMG_BUS_CLKDIV_MASK         0                   //时钟分频掩码
#define CLK_AXI_IMG_BUS_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_axi_img_bus操作宏相关转定义 */

/* clk_peripll_vpp_gated操作宏相关转定义 */
/* 转定义时钟clk_peripll_vpp_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PERIPLL_VPP_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_PERIPLL_VPP_GATED_ENABLE_BIT_OFFSET SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_vpp_gated_START            //时钟使能位偏移

/* 转定义时钟clk_peripll_vpp_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_PERIPLL_VPP_GATED_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_PERIPLL_VPP_GATED_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_PERIPLL_VPP_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_PERIPLL_VPP_GATED_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_PERIPLL_VPP_GATED_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_PERIPLL_VPP_GATED_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_peripll_vpp_gated操作宏相关转定义 */

/* clk_x2x_vpp_brg_s操作宏相关转定义 */
/* 转定义时钟clk_x2x_vpp_brg_s的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_X2X_VPP_BRG_S_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_X2X_VPP_BRG_S_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_vpp_brg_s_START          //时钟使能位偏移

/* 转定义时钟clk_x2x_vpp_brg_s的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_X2X_VPP_BRG_S_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_X2X_VPP_BRG_S_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_X2X_VPP_BRG_S_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_X2X_VPP_BRG_S_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_X2X_VPP_BRG_S_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_X2X_VPP_BRG_S_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_x2x_vpp_brg_s操作宏相关转定义 */

/* clk_p2p_vpp_brg_s操作宏相关转定义 */
/* 转定义时钟clk_p2p_vpp_brg_s的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_P2P_VPP_BRG_S_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_P2P_VPP_BRG_S_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_vpp_brg_s_START            //时钟使能位偏移

/* 转定义时钟clk_p2p_vpp_brg_s的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_P2P_VPP_BRG_S_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_P2P_VPP_BRG_S_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_P2P_VPP_BRG_S_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_P2P_VPP_BRG_S_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_P2P_VPP_BRG_S_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_P2P_VPP_BRG_S_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_p2p_vpp_brg_s操作宏相关转定义 */

/* clk_2vpp_slave_clk操作宏相关转定义 */
/* 转定义时钟clk_2vpp_slave_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_2VPP_SLAVE_CLK_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_2VPP_SLAVE_CLK_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_2vpp_slave_clk_START         //时钟使能位偏移

/* 转定义时钟clk_2vpp_slave_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_2VPP_SLAVE_CLK_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_2VPP_SLAVE_CLK_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_2VPP_SLAVE_CLK_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_2VPP_SLAVE_CLK_CLKDIV_REG_ADDR  SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_2VPP_SLAVE_CLK_CLKDIV_MASK      CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value2_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value2_END)                  //时钟分频掩码
#define CLK_2VPP_SLAVE_CLK_CLKDIV_SET_VALID SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld2_START       //时钟分频设置有效标志位

/* clk_2vpp_slave_clk操作宏相关转定义 */

/* clk_peripll_venc_gated操作宏相关转定义 */
/* 转定义时钟clk_peripll_venc_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PERIPLL_VENC_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_PERIPLL_VENC_GATED_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_venc_gated_START           //时钟使能位偏移

/* 转定义时钟clk_peripll_venc_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_PERIPLL_VENC_GATED_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_PERIPLL_VENC_GATED_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_PERIPLL_VENC_GATED_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_PERIPLL_VENC_GATED_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_PERIPLL_VENC_GATED_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_PERIPLL_VENC_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_peripll_venc_gated操作宏相关转定义 */

/* clk_x2x_venc_brg_s操作宏相关转定义 */
/* 转定义时钟clk_x2x_venc_brg_s的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_X2X_VENC_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_X2X_VENC_BRG_S_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_venc_brg_s_START         //时钟使能位偏移

/* 转定义时钟clk_x2x_venc_brg_s的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_X2X_VENC_BRG_S_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_X2X_VENC_BRG_S_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_X2X_VENC_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_X2X_VENC_BRG_S_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_X2X_VENC_BRG_S_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_X2X_VENC_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_x2x_venc_brg_s操作宏相关转定义 */

/* clk_p2p_venc_brg_s操作宏相关转定义 */
/* 转定义时钟clk_p2p_venc_brg_s的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_P2P_VENC_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_P2P_VENC_BRG_S_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_venc_brg_s_START           //时钟使能位偏移

/* 转定义时钟clk_p2p_venc_brg_s的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_P2P_VENC_BRG_S_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_P2P_VENC_BRG_S_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_P2P_VENC_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_P2P_VENC_BRG_S_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_P2P_VENC_BRG_S_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_P2P_VENC_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_p2p_venc_brg_s操作宏相关转定义 */

/* clk_0venc_slave_clk操作宏相关转定义 */
/* 转定义时钟clk_0venc_slave_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_0VENC_SLAVE_CLK_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_0VENC_SLAVE_CLK_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_0venc_clk_START          //时钟使能位偏移

/* 转定义时钟clk_0venc_slave_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_0VENC_SLAVE_CLK_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_0VENC_SLAVE_CLK_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_0VENC_SLAVE_CLK_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_0VENC_SLAVE_CLK_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_0VENC_SLAVE_CLK_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value3_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value3_END)                  //时钟分频掩码
#define CLK_0VENC_SLAVE_CLK_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld3_START       //时钟分频设置有效标志位

/* clk_0venc_slave_clk操作宏相关转定义 */

/* clk_peripll_vdec_gated操作宏相关转定义 */
/* 转定义时钟clk_peripll_vdec_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PERIPLL_VDEC_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_PERIPLL_VDEC_GATED_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_vdec_gated_START            //时钟使能位偏移

/* 转定义时钟clk_peripll_vdec_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_PERIPLL_VDEC_GATED_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_PERIPLL_VDEC_GATED_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_PERIPLL_VDEC_GATED_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_PERIPLL_VDEC_GATED_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_PERIPLL_VDEC_GATED_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_PERIPLL_VDEC_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_peripll_vdec_gated操作宏相关转定义 */

/* clk_x2x_vdec_brg_s操作宏相关转定义 */
/* 转定义时钟clk_x2x_vdec_brg_s的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_X2X_VDEC_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_X2X_VDEC_BRG_S_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_vdec_brg_s_START         //时钟使能位偏移

/* 转定义时钟clk_vdec_vpp_brg_s的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_X2X_VDEC_BRG_S_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_X2X_VDEC_BRG_S_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_X2X_VDEC_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_X2X_VDEC_BRG_S_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_X2X_VDEC_BRG_S_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_X2X_VDEC_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_x2x_vdec_brg_s操作宏相关转定义 */

/* clk_p2p_vdec_brg_s操作宏相关转定义 */
/* 转定义时钟clk_p2p_vdec_brg_s的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_P2P_VDEC_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_P2P_VDEC_BRG_S_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_vdec_brg_s_START           //时钟使能位偏移

/* 转定义时钟clk_p2p_vdec_brg_s的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_P2P_VDEC_BRG_S_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_P2P_VDEC_BRG_S_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_P2P_VDEC_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_P2P_VDEC_BRG_S_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_P2P_VDEC_BRG_S_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_P2P_VDEC_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_p2p_vdec_brg_s操作宏相关转定义 */

/* clk_1vdec_slave_clk操作宏相关转定义 */
/* 转定义时钟clk_1vdec_slave_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_1VDEC_SLAVE_CLK_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_1VDEC_SLAVE_CLK_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_1vdec_clk_START         //时钟使能位偏移

/* 转定义时钟clk_1vdec_slave_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_1VDEC_SLAVE_CLK_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_1VDEC_SLAVE_CLK_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_1VDEC_SLAVE_CLK_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_1VDEC_SLAVE_CLK_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_1VDEC_SLAVE_CLK_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value1_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value1_END)                  //时钟分频掩码
#define CLK_1VDEC_SLAVE_CLK_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld1_START       //时钟分频设置有效标志位

/* clk_1vdec_slave_clk操作宏相关转定义 */

/* clk_dsppll_g2dcore_gated操作宏相关转定义 */
/* 转定义时钟clk_dsppll_g2dcore_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DSPPLL_G2DCORE_GATED_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR) //使能寄存器地址转定义宏
#define CLK_DSPPLL_G2DCORE_GATED_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_g2dcore_gated_START         //时钟使能位偏移

/* 转定义时钟clk_dsppll_g2dcore_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DSPPLL_G2DCORE_GATED_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DSPPLL_G2DCORE_GATED_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_DSPPLL_G2DCORE_GATED_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DSPPLL_G2DCORE_GATED_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_DSPPLL_G2DCORE_GATED_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_DSPPLL_G2DCORE_GATED_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_dsppll_g2dcore_gated操作宏相关转定义 */

/* clk_5g2d_core_clk操作宏相关转定义 */
/* 转定义时钟clk_5g2d_core_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_5G2D_CORE_CLK_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_5G2D_CORE_CLK_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_5g2d_core_clk_START          //时钟使能位偏移

/* 转定义时钟clk_5g2d_core_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_5G2D_CORE_CLK_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_5G2D_CORE_CLK_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_5G2D_CORE_CLK_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_5G2D_CORE_CLK_CLKDIV_REG_ADDR   SOC_SCTRL_SC_CLKCFG8BIT6_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_5G2D_CORE_CLK_CLKDIV_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value0_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value0_END)                  //时钟分频掩码
#define CLK_5G2D_CORE_CLK_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld0_START       //时钟分频设置有效标志位

/* clk_5g2d_core_clk操作宏相关转定义 */

/* clk_4g2d_axi_clkhb操作宏相关转定义 */
/* 转定义时钟clk_4g2d_axi_clkhb的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_4G2D_AXI_CLKHB_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_4G2D_AXI_CLKHB_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_4g2d_axi_clkhb_START         //时钟使能位偏移

/* 转定义时钟clk_4g2d_axi_clkhb的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_4G2D_AXI_CLKHB_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_4G2D_AXI_CLKHB_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_4G2D_AXI_CLKHB_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_4G2D_AXI_CLKHB_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_4G2D_AXI_CLKHB_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_4G2D_AXI_CLKHB_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_4g2d_axi_clkhb操作宏相关转定义 */

/* clk_3g2d_cfg_clk操作宏相关转定义 */
/* 转定义时钟clk_3g2d_cfg_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_3G2D_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_3G2D_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_3g2d_cfg_clk_START           //时钟使能位偏移

/* 转定义时钟clk_3g2d_cfg_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_3G2D_CFG_CLK_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_3G2D_CFG_CLK_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_3G2D_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_3G2D_CFG_CLK_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_3G2D_CFG_CLK_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_3G2D_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_3g2d_cfg_clk操作宏相关转定义 */

/* clk_p2p_mali_brg_s 操作宏相关转定义 */
/* 转定义时钟 clk_p2p_mali_brg_s 的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_P2P_MALI_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_P2P_MALI_BRG_S_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_7pclk_p2p_mali_START           //时钟使能位偏移

/* 转定义时钟 clk_p2p_mali_brg_s 的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_P2P_MALI_BRG_S_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_P2P_MALI_BRG_S_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_P2P_MALI_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_P2P_MALI_BRG_S_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_P2P_MALI_BRG_S_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_P2P_MALI_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_p2p_mali_brg_s 操作宏相关转定义 */

/* clk_x2x_mali_brg_s操作宏相关转定义 */
/* 转定义时钟clk_x2x_mali_brg_s的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_X2X_MALI_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_X2X_MALI_BRG_S_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mali_brg_s_START         //时钟使能位偏移

/* 转定义时钟clk_x2x_mali_brg_s的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_X2X_MALI_BRG_S_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_X2X_MALI_BRG_S_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_X2X_MALI_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_X2X_MALI_BRG_S_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_X2X_MALI_BRG_S_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_X2X_MALI_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_x2x_mali_brg_s操作宏相关转定义 */

/* clk_x2x_mali_brg_m操作宏相关转定义 */
/* 转定义时钟clk_x2x_mali_brg_m的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_X2X_MALI_BRG_M_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_X2X_MALI_BRG_M_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mali_brg_m_START         //时钟使能位偏移

/* 转定义时钟clk_x2x_mali_brg_m的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_X2X_MALI_BRG_M_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_X2X_MALI_BRG_M_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_X2X_MALI_BRG_M_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_X2X_MALI_BRG_M_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_X2X_MALI_BRG_M_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_X2X_MALI_BRG_M_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_x2x_mali_brg_m操作宏相关转定义 */

/* clk_axi_mali_bus操作宏相关转定义 */
/* 转定义时钟clk_axi_mali_bus的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_AXI_MALI_BUS_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_AXI_MALI_BUS_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_mali_bus_START           //时钟使能位偏移

/* 转定义时钟clk_axi_mali_bus的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_AXI_MALI_BUS_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_AXI_MALI_BUS_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_AXI_MALI_BUS_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_AXI_MALI_BUS_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_AXI_MALI_BUS_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_AXI_MALI_BUS_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_axi_mali_bus操作宏相关转定义 */

/* clk_aclk_edc0操作宏相关转定义 */
/* 转定义时钟clk_aclk_edc0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ACLK_EDC0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_ACLK_EDC0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_aclk_edc0_START          //时钟使能位偏移

/* 转定义时钟clk_aclk_edc0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ACLK_EDC0_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ACLK_EDC0_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_ACLK_EDC0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ACLK_EDC0_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_ACLK_EDC0_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_ACLK_EDC0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_aclk_edc0操作宏相关转定义 */

/* clk_edc0_cfg_clk操作宏相关转定义 */
/* 转定义时钟clk_edc0_cfg_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_EDC0_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_EDC0_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_cfg_clk_START           //时钟使能位偏移

/* 转定义时钟clk_edc0_cfg_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_EDC0_CFG_CLK_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_EDC0_CFG_CLK_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_EDC0_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_EDC0_CFG_CLK_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_EDC0_CFG_CLK_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_EDC0_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_edc0_cfg_clk操作宏相关转定义 */

/* clk_dsio_cfg_clk操作宏相关转定义 */
/* 转定义时钟clk_dsio_cfg_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DSIO_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_DSIO_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dsio_cfg_clk_START           //时钟使能位偏移

/* 转定义时钟clk_dsio_cfg_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DSIO_CFG_CLK_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DSIO_CFG_CLK_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_DSIO_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DSIO_CFG_CLK_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_DSIO_CFG_CLK_CLKDIV_MASK        0               //时钟分频掩码
#define CLK_DSIO_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_dsio_cfg_clk操作宏相关转定义 */

/* clk_edc1_pix_ldi操作宏相关转定义 */
/* 转定义时钟clk_edc1_pix_ldi的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_EDC1_PIX_LDI_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_EDC1_PIX_LDI_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_pix_ldi_START           //时钟使能位偏移

/* 转定义时钟clk_edc1_pix_ldi的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_EDC1_PIX_LDI_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_EDC1_PIX_LDI_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_EDC1_PIX_LDI_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_EDC1_PIX_LDI_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_EDC1_PIX_LDI_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value2_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value2_END)                  //时钟分频掩码
#define CLK_EDC1_PIX_LDI_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld2_START       //时钟分频设置有效标志位

/* clk_edc1_pix_ldi操作宏相关转定义 */

/* clk_edc1_axi操作宏相关转定义 */
/* 转定义时钟clk_edc1_axi的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_EDC1_AXI_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_EDC1_AXI_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_axi_START           //时钟使能位偏移

/* 转定义时钟clk_edc1_axi的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_EDC1_AXI_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_EDC1_AXI_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_EDC1_AXI_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_EDC1_AXI_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_EDC1_AXI_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_EDC1_AXI_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_edc1_axi操作宏相关转定义 */

/* clk_edc1_cfg_clk操作宏相关转定义 */
/* 转定义时钟clk_edc1_cfg_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_EDC1_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_EDC1_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_cfg_clk_START         //时钟使能位偏移

/* 转定义时钟clk_edc1_cfg_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_EDC1_CFG_CLK_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_EDC1_CFG_CLK_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_EDC1_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_EDC1_CFG_CLK_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_EDC1_CFG_CLK_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_EDC1_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_edc1_cfg_clk操作宏相关转定义 */

/* clk_isp_cfg_clk操作宏相关转定义 */
/* 转定义时钟clk_isp_cfg_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ISP_CFG_CLK_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_ISP_CFG_CLK_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_isp_cfg_clk_START            //时钟使能位偏移

/* 转定义时钟clk_isp_cfg_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ISP_CFG_CLK_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ISP_CFG_CLK_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_ISP_CFG_CLK_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ISP_CFG_CLK_CLKDIV_REG_ADDR NULL    //时钟分频寄存器地址转定义宏
#define CLK_ISP_CFG_CLK_CLKDIV_MASK     0                   //时钟分频掩码
#define CLK_ISP_CFG_CLK_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_isp_cfg_clk操作宏相关转定义 */

/* clk_isp_axi操作宏相关转定义 */
/* 转定义时钟clk_isp_axi的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ISP_AXI_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_ISP_AXI_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_isp_axi_START         //时钟使能位偏移

/* 转定义时钟clk_isp_axi的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ISP_AXI_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ISP_AXI_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_ISP_AXI_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ISP_AXI_CLKDIV_REG_ADDR NULL    //时钟分频寄存器地址转定义宏
#define CLK_ISP_AXI_CLKDIV_MASK     0                   //时钟分频掩码
#define CLK_ISP_AXI_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_isp_axi操作宏相关转定义 */

/* clk_peripll_isp_gated操作宏相关转定义 */
/* 转定义时钟clk_peripll_isp_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PERIPLL_ISP_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_PERIPLL_ISP_GATED_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mux_isp_gated_START         //时钟使能位偏移

/* 转定义时钟clk_peripll_isp_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_PERIPLL_ISP_GATED_CLKSEL_REG_ADDR   SOC_PMCTRL_CLKCFG4BIT1_ADDR(PMCTRL_BASE_ADDR)     //父时钟选择寄存器地址转定义宏
#define CLK_PERIPLL_ISP_GATED_CLKSEL_MASK       CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value2_START, \
                                                SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value2_END)              //时钟分频掩码
#define CLK_PERIPLL_ISP_GATED_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld2_START , \
                                                SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld2_END)              //时钟分频掩码
#define CLK_PERIPLL_ISP_GATED_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_PERIPLL_ISP_GATED_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_PERIPLL_ISP_GATED_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_peripll_isp_gated操作宏相关转定义 */

/* clk_isp操作宏相关转定义 */
/* 转定义时钟clk_isp的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ISP_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_ISP_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_isp_START            //时钟使能位偏移

/* 转定义时钟clk_isp的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ISP_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ISP_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_ISP_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ISP_CLKDIV_REG_ADDR     SOC_SCTRL_SC_CLKCFG8BIT6_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_ISP_CLKDIV_MASK         CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value1_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value1_END)              //时钟分频掩码
#define CLK_ISP_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld1_START       //时钟分频设置有效标志位

/* clk_isp操作宏相关转定义 */


/* clk_peripll_isp_ref_gated操作宏相关转定义 */
/* 转定义时钟clk_peripll_isp_ref_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PERIPLL_ISP_REF_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_PERIPLL_ISP_REF_GATED_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_isp_ref_gated_START            //时钟使能位偏移

/* 转定义时钟clk_peripll_isp_ref_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_PERIPLL_ISP_REF_GATED_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_PERIPLL_ISP_REF_GATED_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_PERIPLL_ISP_REF_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_PERIPLL_ISP_REF_GATED_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_PERIPLL_ISP_REF_GATED_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_PERIPLL_ISP_REF_GATED_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_peripll_isp_ref_gated操作宏相关转定义 */

/* clk_isp_ref操作宏相关转定义 */
/* 转定义时钟clk_isp_ref的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ISP_REF_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_ISP_REF_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_isp_ref_START            //时钟使能位偏移

/* 转定义时钟clk_isp_ref的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ISP_REF_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ISP_REF_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_ISP_REF_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ISP_REF_CLKDIV_REG_ADDR     SOC_SCTRL_SC_CLKCFG8BIT6_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_ISP_REF_CLKDIV_MASK         CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value3_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value3_END)              //时钟分频掩码
#define CLK_ISP_REF_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld3_START       //时钟分频设置有效标志位

/* clk_isp_ref操作宏相关转定义 */

/* clk_hdmi_slave操作宏相关转定义 */
/* 转定义时钟clk_hdmi_slave的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_HDMI_SLAVE_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_HDMI_SLAVE_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_hdmi_slave_START         //时钟使能位偏移

/* 转定义时钟clk_hdmi_slave的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_HDMI_SLAVE_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_HDMI_SLAVE_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_HDMI_SLAVE_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_HDMI_SLAVE_CLKDIV_REG_ADDR      NULL    //时钟分频寄存器地址转定义宏
#define CLK_HDMI_SLAVE_CLKDIV_MASK          0               //时钟分频掩码
#define CLK_HDMI_SLAVE_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_hdmi_slave操作宏相关转定义 */

/* clk_hdmi_sck操作宏相关转定义 */
/* 转定义时钟clk_hdmi_sck的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_HDMI_SCK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_HDMI_SCK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_hdmi_sck_START           //时钟使能位偏移

/* 转定义时钟clk_hdmi_sck的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_HDMI_SCK_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_HDMI_SCK_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_HDMI_SCK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_HDMI_SCK_CLKDIV_REG_ADDR        NULL    //时钟分频寄存器地址转定义宏
#define CLK_HDMI_SCK_CLKDIV_MASK            0               //时钟分频掩码
#define CLK_HDMI_SCK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_hdmi_sck操作宏相关转定义 */

/* clk_hdmipll_divfrac操作宏相关转定义 */
/* 转定义时钟clk_hdmipll_divfrac的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_HDMIPLL_DIVFRAC_ENABLE_REG_ADDR     NULL    //使能寄存器地址转定义宏
#define CLK_HDMIPLL_DIVFRAC_ENABLE_BIT_OFFSET       0           //时钟使能位偏移

/* 转定义时钟clk_hdmipll_divfrac的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_HDMIPLL_DIVFRAC_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_HDMIPLL_DIVFRAC_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_HDMIPLL_DIVFRAC_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_HDMIPLL_DIVFRAC_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFGALL4_ADDR(SCTRL_OFF_BASE_ADDR)   //时钟分频寄存器地址转定义宏
#define CLK_HDMIPLL_DIVFRAC_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFGALL4_divfrac_49m_START, \
                                                SOC_SCTRL_SC_CLKCFGALL4_divfrac_49m_END)                //时钟分频掩码
#define CLK_HDMIPLL_DIVFRAC_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_hdmipll_divfrac操作宏相关转定义 */

/* clk_mclk_hdmi操作宏相关转定义 */
/* 转定义时钟clk_mclk_hdmi的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MCLK_HDMI_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_MCLK_HDMI_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_mclk_hdmi_START          //时钟使能位偏移

/* 转定义时钟clk_mclk_hdmi的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MCLK_HDMI_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_MCLK_HDMI_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_MCLK_HDMI_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_MCLK_HDMI_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_MCLK_HDMI_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_MCLK_HDMI_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_mclk_hdmi操作宏相关转定义 */

/* clk_asp_hdmi_adws操作宏相关转定义 */
/* 转定义时钟clk_asp_hdmi_adws的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ASP_HDMI_ADWS_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_ASP_HDMI_ADWS_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_adws_START            //时钟使能位偏移

/* 转定义时钟clk_asp_hdmi_adws的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ASP_HDMI_ADWS_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ASP_HDMI_ADWS_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_ASP_HDMI_ADWS_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ASP_HDMI_ADWS_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_ASP_HDMI_ADWS_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_ASP_HDMI_ADWS_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_asp_hdmi_adws操作宏相关转定义 */

/* clk_asp_hdmi_bclk操作宏相关转定义 */
/* 转定义时钟clk_asp_hdmi_bclk的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ASP_HDMI_BCLK_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_ASP_HDMI_BCLK_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_bclk_START            //时钟使能位偏移

/* 转定义时钟clk_asp_hdmi_bclk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ASP_HDMI_BCLK_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ASP_HDMI_BCLK_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_ASP_HDMI_BCLK_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ASP_HDMI_BCLK_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_ASP_HDMI_BCLK_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_ASP_HDMI_BCLK_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_asp_hdmi_bclk操作宏相关转定义 */

/* clk_asp_hdmi_ref操作宏相关转定义 */
/* 转定义时钟clk_asp_hdmi_ref的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ASP_HDMI_REF_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_ASP_HDMI_REF_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_ref_START         //时钟使能位偏移

/* 转定义时钟clk_asp_hdmi_ref的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ASP_HDMI_REF_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ASP_HDMI_REF_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_ASP_HDMI_REF_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ASP_HDMI_REF_CLKDIV_REG_ADDR        NULL    //时钟分频寄存器地址转定义宏
#define CLK_ASP_HDMI_REF_CLKDIV_MASK            0               //时钟分频掩码
#define CLK_ASP_HDMI_REF_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_asp_hdmi_ref操作宏相关转定义 */

/* clk_asp_spdif_ref操作宏相关转定义 */
/* 转定义时钟clk_asp_spdif_ref的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_ASP_SPDIF_REF_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_ASP_SPDIF_REF_ENABLE_BIT_OFFSET SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_spdif_ref_START            //时钟使能位偏移

/* 转定义时钟clk_asp_spdif_ref的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_ASP_SPDIF_REF_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_ASP_SPDIF_REF_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_ASP_SPDIF_REF_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_ASP_SPDIF_REF_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_ASP_SPDIF_REF_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_ASP_SPDIF_REF_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define CLK_ASP_CFG_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_ASP_CFG_ENABLE_BIT_OFFSET SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_asp_cfg_clk_START            //时钟使能位偏移

/* clk_asp_spdif_ref操作宏相关转定义 */

/* clk_dphy0_ref操作宏相关转定义 */
/* 转定义时钟clk_dphy0_ref的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DPHY0_REF_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_DPHY0_REF_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy0_START          //时钟使能位偏移

/* 转定义时钟clk_dphy0_ref的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DPHY0_REF_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DPHY0_REF_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_DPHY0_REF_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DPHY0_REF_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_DPHY0_REF_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_DPHY0_REF_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_dphy0_ref操作宏相关转定义 */

/* clk_dphy0_cfg操作宏相关转定义 */
/* 转定义时钟clk_dphy0_cfg的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DPHY0_CFG_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_DPHY0_CFG_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy0_clk_START          //时钟使能位偏移

/* 转定义时钟clk_dphy0_cfg的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DPHY0_CFG_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DPHY0_CFG_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_DPHY0_CFG_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DPHY0_CFG_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_DPHY0_CFG_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_DPHY0_CFG_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_dphy0_cfg操作宏相关转定义 */

/* clk_dphy1_cfg操作宏相关转定义 */
/* 转定义时钟clk_dphy1_cfg的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DPHY1_CFG_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_DPHY1_CFG_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy1_cfg_START          //时钟使能位偏移

/* 转定义时钟clk_dphy1_cfg的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DPHY1_CFG_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DPHY1_CFG_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_DPHY1_CFG_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DPHY1_CFG_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_DPHY1_CFG_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_DPHY1_CFG_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_dphy1_cfg操作宏相关转定义 */

/* clk_dphy2_cfg操作宏相关转定义 */
/* 转定义时钟clk_dphy2_cfg的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DPHY2_CFG_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_DPHY2_CFG_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy2_cfg_clk_START          //时钟使能位偏移

/* 转定义时钟clk_dphy2_cfg的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DPHY2_CFG_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DPHY2_CFG_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_DPHY2_CFG_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DPHY2_CFG_CLKDIV_REG_ADDR       NULL    //时钟分频寄存器地址转定义宏
#define CLK_DPHY2_CFG_CLKDIV_MASK           0               //时钟分频掩码
#define CLK_DPHY2_CFG_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_dphy2_cfg操作宏相关转定义 */

/* clk_uart0操作宏相关转定义 */
/* 转定义时钟clk_uart0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_UART0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_UART0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart0_START            //时钟使能位偏移

/* 转定义时钟clk_uart0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_UART0_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_UART0_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_UART0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_UART0_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_UART0_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_UART0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_UART0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_UART0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart0_pclk_START            //时钟使能位偏移

/* 转定义时钟clk_uart0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_UART0_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_UART0_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_UART0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_UART0_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_UART0_CLKDIV_MASK       0                   //时钟分频掩码
#define PCLK_UART0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_uart0操作宏相关转定义 */

/* clk_uart1操作宏相关转定义 */
/* 转定义时钟clk_uart1的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_UART1_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_UART1_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart1_START            //时钟使能位偏移

/* 转定义时钟clk_uart1的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_UART1_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_UART1_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_END)    //父时钟选择掩码
#define CLK_UART1_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_msk_START , \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_msk_END)    //父时钟选择掩码
                                        
#define CLK_UART1_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_UART1_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_UART1_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_UART1_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_UART1_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart1_pclk_START            //时钟使能位偏移

/* 转定义时钟clk_uart0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_UART1_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_UART1_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_UART1_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_UART1_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_UART1_CLKDIV_MASK       0                   //时钟分频掩码
#define PCLK_UART1_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_uart1操作宏相关转定义 */

/* clk_uart2操作宏相关转定义 */
/* 转定义时钟clk_uart2的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_UART2_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_UART2_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart2_START            //时钟使能位偏移

/* 转定义时钟clk_uart2的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_UART2_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_UART2_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_END)    //父时钟选择掩码
#define CLK_UART2_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_msk_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_msk_END)    //父时钟选择掩码
#define CLK_UART2_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_UART2_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_UART2_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_UART2_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_UART2_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart2_pclk_START            //时钟使能位偏移

/* 转定义时钟clk_uart0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_UART2_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_UART2_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_UART2_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_UART2_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_UART2_CLKDIV_MASK       0                   //时钟分频掩码
#define PCLK_UART2_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_uart2操作宏相关转定义 */

/* clk_uart3操作宏相关转定义 */
/* 转定义时钟clk_uart3的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_UART3_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_UART3_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart3_START            //时钟使能位偏移

/* 转定义时钟clk_uart3的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_UART3_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_UART3_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_END)    //父时钟选择掩码
#define CLK_UART3_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_msk_START , \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_msk_END)    //父时钟选择掩码
#define CLK_UART3_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_UART3_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_UART3_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_UART3_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_UART3_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart3_pclk_START            //时钟使能位偏移

/* 转定义时钟clk_uart0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_UART3_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_UART3_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_UART3_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_UART3_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_UART3_CLKDIV_MASK       0                   //时钟分频掩码
#define PCLK_UART3_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_uart3操作宏相关转定义 */

/* clk_uart4操作宏相关转定义 */
/* 转定义时钟clk_uart4的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_UART4_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_UART4_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart4_START            //时钟使能位偏移

/* 转定义时钟clk_uart4的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_UART4_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_UART4_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_END)    //父时钟选择掩码
#define CLK_UART4_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_msk_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_msk_END)    //父时钟选择掩码
#define CLK_UART4_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_UART4_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_UART4_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_UART4_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_UART4_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart4_pclk_START            //时钟使能位偏移

/* 转定义时钟clk_uart0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_UART4_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_UART4_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_UART4_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_UART4_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_UART4_CLKDIV_MASK       0                   //时钟分频掩码
#define PCLK_UART4_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_uart4操作宏相关转定义 */

/* clk_uart5操作宏相关转定义 */
/* 转定义时钟clk_uart5的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_UART5_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_UART5_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart5_START            //时钟使能位偏移

/* 转定义时钟clk_uart5的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_UART5_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_UART5_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_END)    //父时钟选择掩码
#define CLK_UART5_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_msk_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_msk_END)    //父时钟选择掩码
#define CLK_UART5_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_UART5_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_UART5_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_UART5_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_UART5_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart5_pclk_START            //时钟使能位偏移

/* 转定义时钟clk_uart0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_UART5_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_UART5_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_UART5_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_UART5_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_UART5_CLKDIV_MASK       0                   //时钟分频掩码
#define PCLK_UART5_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_uart5操作宏相关转定义 */

/* clk_uart6操作宏相关转定义 */
/* 转定义时钟clk_uart6的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_UART6_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_UART6_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart6_START            //时钟使能位偏移

/* 转定义时钟clk_uart6的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_UART6_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_UART6_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_END)    //父时钟选择掩码
#define CLK_UART6_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_msk_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_msk_END)    //父时钟选择掩码
#define CLK_UART6_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_UART6_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_UART6_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_UART6_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_UART6_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart6_pclk_START            //时钟使能位偏移

/* 转定义时钟clk_uart0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_UART6_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_UART6_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_UART6_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_UART6_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_UART6_CLKDIV_MASK       0                   //时钟分频掩码
#define PCLK_UART6_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_uart6操作宏相关转定义 */

/* hclk_nandc操作宏相关转定义 */
/* 转定义时钟hclk_nandc的使能寄存器，状态寄存器的地址和位偏移 */
#define HCLK_NANDC_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define HCLK_NANDC_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_hclk_nandc_START  /* 时钟使能位偏移 */

/* hclk_mmc0操作宏相关转定义 */
/* 转定义时钟hclk_mmc0的使能寄存器，状态寄存器的地址和位偏移 */
#define HCLK_MMC0_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define HCLK_MMC0_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0_bus_START /* 时钟使能位偏移 */

/* hclk_mmc1操作宏相关转定义 */
/* 转定义时钟hclk_mmc1的使能寄存器，状态寄存器的地址和位偏移 */
#define HCLK_MMC1_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define HCLK_MMC1_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1_bus_START  /* 时钟使能位偏移 */

/* hclk_mmc2操作宏相关转定义 */
/* 转定义时钟hclk_mmc2的使能寄存器，状态寄存器的地址和位偏移 */
#define HCLK_MMC2_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define HCLK_MMC2_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2_bus_START  /* 时钟使能位偏移 */

/* clk_dsppll_mmc0_gated操作宏相关转定义 */
/* 转定义时钟clk_dsppll_mmc0_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DSPPLL_MMC0_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_DSPPLL_MMC0_GATED_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc0_gated_START           //时钟使能位偏移

/* 转定义时钟clk_dsppll_mmc0_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DSPPLL_MMC0_GATED_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DSPPLL_MMC0_GATED_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_DSPPLL_MMC0_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DSPPLL_MMC0_GATED_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)     //时钟分频寄存器地址转定义宏
#define CLK_DSPPLL_MMC0_GATED_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_END)                  //时钟分频掩码
#define CLK_DSPPLL_MMC0_GATED_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld0_START      //时钟分频设置有效标志位

/* clk_dsppll_mmc0_gated操作宏相关转定义 */

/* clk_dsppll_mmc1_gated操作宏相关转定义 */
/* 转定义时钟clk_dsppll_mmc1_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DSPPLL_MMC1_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_DSPPLL_MMC1_GATED_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc1_gated_START          //时钟使能位偏移

/* 转定义时钟clk_dsppll_mmc1_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DSPPLL_MMC1_GATED_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DSPPLL_MMC1_GATED_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_DSPPLL_MMC1_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DSPPLL_MMC1_GATED_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)    //时钟分频寄存器地址转定义宏
#define CLK_DSPPLL_MMC1_GATED_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_END)                  //时钟分频掩码
#define CLK_DSPPLL_MMC1_GATED_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld1_START       //时钟分频设置有效标志位

/* clk_dsppll_mmc1_gated操作宏相关转定义 */

/* clk_dsppll_mmc2_gated操作宏相关转定义 */
/* 转定义时钟clk_dsppll_mmc2_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DSPPLL_MMC2_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)     //使能寄存器地址转定义宏
#define CLK_DSPPLL_MMC2_GATED_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc2_gated_START           //时钟使能位偏移

/* 转定义时钟clk_dsppll_mmc2_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DSPPLL_MMC2_GATED_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DSPPLL_MMC2_GATED_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_DSPPLL_MMC2_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DSPPLL_MMC2_GATED_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)    //时钟分频寄存器地址转定义宏
#define CLK_DSPPLL_MMC2_GATED_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_END)                  //时钟分频掩码
#define CLK_DSPPLL_MMC2_GATED_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld2_START      //时钟分频设置有效标志位

/* clk_dsppll_mmc2_gated操作宏相关转定义 */

/* clk_mmc0high操作宏相关转定义 */
/* 转定义时钟clk_mmc0high的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MMC0HIGH_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_MMC0HIGH_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0high_START         //时钟使能位偏移

/* 转定义时钟clk_mmc0low的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MMC0HIGH_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_MMC0HIGH_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_MMC0HIGH_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_MMC0HIGH_CLKDIV_REG_ADDR       SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_MMC0HIGH_CLKDIV_MASK          CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_END)                  //时钟分频掩码
#define CLK_MMC0HIGH_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld0_START       //时钟分频设置有效标志位


/* clk_mmc0high操作宏相关转定义 */

/* clk_mmc1high操作宏相关转定义 */
/* 转定义时钟clk_mmc1high的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MMC1HIGH_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_MMC1HIGH_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1high_START         //时钟使能位偏移

/* 转定义时钟clk_mmc1low的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MMC1HIGH_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_MMC1HIGH_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_MMC1HIGH_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_MMC1HIGH_CLKDIV_REG_ADDR       SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)  //时钟分频寄存器地址转定义宏
#define CLK_MMC1HIGH_CLKDIV_MASK           CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_END)                  //时钟分频掩码
#define CLK_MMC1HIGH_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld1_START       //时钟分频设置有效标志位

/* clk_mmc1high操作宏相关转定义 */

/* clk_mmc2high操作宏相关转定义 */
/* 转定义时钟clk_mmc2high的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MMC2HIGH_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_MMC2HIGH_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2high_START         //时钟使能位偏移

/* 转定义时钟clk_mmc2low的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MMC2HIGH_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_MMC2HIGH_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_MMC2HIGH_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_MMC2HIGH_CLKDIV_REG_ADDR       SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)   //时钟分频寄存器地址转定义宏
#define CLK_MMC2HIGH_CLKDIV_MASK           CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_END)                  //时钟分频掩码
#define CLK_MMC2HIGH_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld2_START       //时钟分频设置有效标志位


/* clk_mmc0low操作宏相关转定义 */
/* 转定义时钟clk_mmc0low的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MMC0LOW_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_MMC0LOW_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0low_START          //时钟使能位偏移

/* 转定义时钟clk_mmc0low的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MMC0LOW_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_MMC0LOW_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_MMC0LOW_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_MMC0LOW_CLKDIV_REG_ADDR  SOC_SCTRL_SC_CLKCFG8BIT2_ADDR(SCTRL_OFF_BASE_ADDR)     //时钟分频寄存器地址转定义宏
#define CLK_MMC0LOW_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value0_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value0_END)                  //时钟分频掩码
#define CLK_MMC0LOW_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld0_START      //时钟分频设置有效标志位

/* clk_mmc0low操作宏相关转定义 */

/* clk_mmc1low操作宏相关转定义 */
/* 转定义时钟clk_mmc1low的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MMC1LOW_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_MMC1LOW_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1low_START          //时钟使能位偏移

/* 转定义时钟clk_mmc1low的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MMC1LOW_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_MMC1LOW_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_MMC1LOW_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_MMC1LOW_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT2_ADDR(SCTRL_OFF_BASE_ADDR)    //时钟分频寄存器地址转定义宏
#define CLK_MMC1LOW_CLKDIV_MASK    CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value1_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value1_END)                  //时钟分频掩码
#define CLK_MMC1LOW_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld1_START      //时钟分频设置有效标志位

/* clk_mmc1low操作宏相关转定义 */

/* clk_mmc2low操作宏相关转定义 */
/* 转定义时钟clk_mmc2low的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_MMC2LOW_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_MMC2LOW_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2low_START          //时钟使能位偏移

/* 转定义时钟clk_mmc2low的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_MMC2LOW_CLKSEL_REG_ADDR NULL    //父时钟选择寄存器地址转定义宏
#define CLK_MMC2LOW_CLKSEL_MASK     0   //父时钟选择掩码
#define CLK_MMC2LOW_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_MMC2LOW_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT2_ADDR(SCTRL_OFF_BASE_ADDR)    //时钟分频寄存器地址转定义宏
#define CLK_MMC2LOW_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value2_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value2_END)                  //时钟分频掩码
#define CLK_MMC2LOW_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld2_START      //时钟分频设置有效标志位

/* clk_mmc2low操作宏相关转定义 */

/* clk_ddrio_div操作宏相关转定义 */
/* 转定义时钟clk_ddrio_div的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DDRIO_DIV_ENABLE_REG_ADDR       NULL    //使能寄存器地址转定义宏
#define CLK_DDRIO_DIV_ENABLE_BIT_OFFSET     0           //时钟使能位偏移

/* 转定义时钟clk_ddrio_div的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DDRIO_DIV_CLKSEL_REG_ADDR   SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_DDRIO_DIV_CLKSEL_MASK       CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddr_pllsw_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddr_pllsw_prof_END)    //父时钟选择掩码
#define CLK_DDRIO_DIV_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DDRIO_DIV_CLKDIV_REG_ADDR   SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //时钟分频寄存器地址转定义宏
#define CLK_DDRIO_DIV_CLKDIV_MASK       CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddrio_clk_div_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddrio_clk_div_prof_END)                    //时钟分频掩码
#define CLK_DDRIO_DIV_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_ddrio_div操作宏相关转定义 */

/* clk_ddrio操作宏相关转定义 */
/* 转定义时钟clk_ddrio的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DDRIO_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN0_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_DDRIO_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrio_START            //时钟使能位偏移

/* 转定义时钟clk_ddrio的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DDRIO_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DDRIO_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_DDRIO_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DDRIO_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_DDRIO_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_DDRIO_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_ddrio操作宏相关转定义 */

/* clk_ddrc_div操作宏相关转定义 */
/* 转定义时钟clk_ddrc_div的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DDRC_DIV_ENABLE_REG_ADDR        NULL    //使能寄存器地址转定义宏
#define CLK_DDRC_DIV_ENABLE_BIT_OFFSET      0           //时钟使能位偏移

/* 转定义时钟clk_ddrc_div的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DDRC_DIV_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DDRC_DIV_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_DDRC_DIV_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DDRC_DIV_CLKDIV_REG_ADDR    SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //时钟分频寄存器地址转定义宏
#define CLK_DDRC_DIV_CLKDIV_MASK        CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddrc_clk_div_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddrc_clk_div_prof_END)                 //时钟分频掩码
#define CLK_DDRC_DIV_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_ddrc_div操作宏相关转定义 */

/* clk_ddrc操作宏相关转定义 */
/* 转定义时钟clk_ddrc的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DDRC_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN0_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_DDRC_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrc_START         //时钟使能位偏移

/* 转定义时钟clk_ddrc的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DDRC_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DDRC_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_DDRC_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DDRC_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_DDRC_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_DDRC_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_ddrc操作宏相关转定义 */

/* clk_ddrbus_div操作宏相关转定义 */
/* 转定义时钟clk_ddrbus_div的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DDRBUS_DIV_ENABLE_REG_ADDR      NULL    //使能寄存器地址转定义宏
#define CLK_DDRBUS_DIV_ENABLE_BIT_OFFSET    0           //时钟使能位偏移

/* 转定义时钟clk_ddrbus_div的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DDRBUS_DIV_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DDRBUS_DIV_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_DDRBUS_DIV_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DDRBUS_DIV_CLKDIV_REG_ADDR  SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //时钟分频寄存器地址转定义宏
#define CLK_DDRBUS_DIV_CLKDIV_MASK      CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_END)                   //时钟分频掩码
#define CLK_DDRBUS_DIV_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_ddrcbus_div操作宏相关转定义 */

/* clk_ddrphy操作宏相关转定义 */
/* 转定义时钟clk_ddrphy的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DDRPHY_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN0_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_DDRPHY_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrphy_START           //时钟使能位偏移

/* 转定义时钟clk_ddrphy的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DDRPHY_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DDRPHY_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_DDRPHY_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DDRPHY_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_DDRPHY_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_DDRPHY_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_ddrphy操作宏相关转定义 */

/* clk_i2c0操作宏相关转定义 */
/* 转定义时钟clk_i2c0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_I2C0_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_I2C0_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c0_START         //时钟使能位偏移

/* 转定义时钟clk_i2c0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_I2C0_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_I2C0_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_I2C0_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_I2C0_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_I2C0_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_I2C0_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_I2C0_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_I2C0_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c0_pclk_START         //时钟使能位偏移

/* 转定义时钟clk_i2c0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_I2C0_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_I2C0_CLKSEL_MASK        0   //父时钟选择掩码
#define PCLK_I2C0_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_I2C0_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define PCLK_I2C0_CLKDIV_MASK        0                   //时钟分频掩码
#define PCLK_I2C0_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_i2c0操作宏相关转定义 */

/* clk_i2c1操作宏相关转定义 */
/* 转定义时钟clk_i2c1的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_I2C1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_I2C1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c1_START         //时钟使能位偏移

/* 转定义时钟clk_i2c1的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_I2C1_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_I2C1_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_I2C1_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_I2C1_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_I2C1_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_I2C1_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* 转定义时钟clk_i2c1的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_I2C1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_I2C1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c1_pclk_START         //时钟使能位偏移

/* 转定义时钟clk_i2c1的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_I2C1_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_I2C1_CLKSEL_MASK        0   //父时钟选择掩码
#define PCLK_I2C1_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_I2C1_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define PCLK_I2C1_CLKDIV_MASK        0                   //时钟分频掩码
#define PCLK_I2C1_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_i2c1操作宏相关转定义 */

/* clk_i2c2操作宏相关转定义 */
/* 转定义时钟clk_i2c2的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_I2C2_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_I2C2_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c2_START         //时钟使能位偏移

/* 转定义时钟clk_i2c2的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_I2C2_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_I2C2_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_I2C2_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_I2C2_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_I2C2_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_I2C2_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* 转定义时钟clk_i2c2的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_I2C2_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_I2C2_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c2_pclk_START         //时钟使能位偏移

/* 转定义时钟clk_i2c2的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_I2C2_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_I2C2_CLKSEL_MASK        0   //父时钟选择掩码
#define PCLK_I2C2_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_I2C2_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define PCLK_I2C2_CLKDIV_MASK        0                   //时钟分频掩码
#define PCLK_I2C2_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_i2c2操作宏相关转定义 */

/* clk_i2c3操作宏相关转定义 */
/* 转定义时钟clk_i2c3的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_I2C3_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_I2C3_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c3_START         //时钟使能位偏移

/* 转定义时钟clk_i2c3的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_I2C3_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_I2C3_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_I2C3_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_I2C3_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_I2C3_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_I2C3_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* 转定义时钟clk_i2c3的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_I2C3_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_I2C3_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c3_pclk_START         //时钟使能位偏移

/* 转定义时钟clk_i2c3的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_I2C3_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_I2C3_CLKSEL_MASK        0   //父时钟选择掩码
#define PCLK_I2C3_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_I2C3_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define PCLK_I2C3_CLKDIV_MASK        0                   //时钟分频掩码
#define PCLK_I2C3_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_i2c3操作宏相关转定义 */

/* clk_i2c4操作宏相关转定义 */
/* 转定义时钟clk_i2c4的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_I2C4_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_I2C4_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c4_START         //时钟使能位偏移

/* 转定义时钟clk_i2c4的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_I2C4_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_I2C4_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_I2C4_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_I2C4_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_I2C4_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_I2C4_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* 转定义时钟clk_i2c4的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_I2C4_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_I2C4_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c4_pclk_START         //时钟使能位偏移

/* 转定义时钟clk_i2c4的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_I2C4_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_I2C4_CLKSEL_MASK        0   //父时钟选择掩码
#define PCLK_I2C4_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_I2C4_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define PCLK_I2C4_CLKDIV_MASK        0                   //时钟分频掩码
#define PCLK_I2C4_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_i2c4操作宏相关转定义 */

/* clk_i2c5操作宏相关转定义 */
/* 转定义时钟clk_i2c5的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_I2C5_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_I2C5_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c5_START         //时钟使能位偏移

/* 转定义时钟clk_i2c5的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_I2C5_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_I2C5_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_I2C5_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_I2C5_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_I2C5_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_I2C5_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* 转定义时钟clk_i2c5的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_I2C5_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_I2C5_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c5_pclk_START         //时钟使能位偏移

/* 转定义时钟clk_i2c5的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_I2C5_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_I2C5_CLKSEL_MASK        0   //父时钟选择掩码
#define PCLK_I2C5_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_I2C5_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define PCLK_I2C5_CLKDIV_MASK        0                   //时钟分频掩码
#define PCLK_I2C5_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_i2c5操作宏相关转定义 */

/* clk_pwm0操作宏相关转定义 */
/* 转定义时钟clk_pwm0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PWM0_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_PWM0_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm0_START         //时钟使能位偏移

/* 转定义时钟clk_pwm0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_PWM0_CLKSEL_REG_ADDR    SOC_SCTRL_SC_CLK_SEL1_ADDR(SCTRL_OFF_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_PWM0_CLKSEL_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_START, \
                                                SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_END) //父时钟选择掩码
#define CLK_PWM0_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_msk_START, \
                                                SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_msk_END) //父时钟选择掩码
#define CLK_PWM0_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT10_ADDR(SCTRL_OFF_BASE_ADDR) //时钟分频寄存器地址转定义宏
#define CLK_PWM0_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value0_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value0_END)                    //时钟分频掩码
#define CLK_PWM0_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld0_START     //时钟分频设置有效标志位

/* clk_pwm0操作宏相关转定义 */

/* pclk_pwm0操作宏相关转定义 */
/* 转定义时钟pclk_pwm0的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_PWM0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_PWM0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm0_pclk_START            //时钟使能位偏移

/* 转定义时钟pclk_pwm0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_PWM0_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_PWM0_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_PWM0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_PWM0_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_PWM0_CLKDIV_MASK       0       //时钟分频掩码
#define PCLK_PWM0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* pclk_pwm0操作宏相关转定义 */

/* clk_pwm1操作宏相关转定义 */
/* 转定义时钟clk_pwm1的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PWM1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_PWM1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm1_START         //时钟使能位偏移

/* 转定义时钟clk_pwm1的时钟选择寄存器、选择掩s码和设置有效标志位 */
#define CLK_PWM1_CLKSEL_REG_ADDR    SOC_SCTRL_SC_CLK_SEL1_ADDR(SCTRL_OFF_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_PWM1_CLKSEL_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_START, \
                                                SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_END) //父时钟选择掩码
#define CLK_PWM1_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_msk_START, \
                                                SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_msk_END) //父时钟选择掩码
#define CLK_PWM1_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT10_ADDR(SCTRL_OFF_BASE_ADDR) //时钟分频寄存器地址转定义宏
#define CLK_PWM1_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value1_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value1_END)                    //时钟分频掩码
#define CLK_PWM1_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld1_START     //时钟分频设置有效标志位

/* clk_pwm1操作宏相关转定义 */

/* pclk_pwm1操作宏相关转定义 */
/* 转定义时钟pclk_pwm1的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_PWM1_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_PWM1_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm1_pclk_START            //时钟使能位偏移

/* 转定义时钟pclk_pwm1的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_PWM1_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_PWM1_CLKSEL_MASK       0   //父时钟选择掩码
#define PCLK_PWM1_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_PWM1_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define PCLK_PWM1_CLKDIV_MASK       0       //时钟分频掩码
#define PCLK_PWM1_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* pclk_pwm1操作宏相关转定义 */

/* clk_spi0操作宏相关转定义 */
/* 转定义时钟clk_spi0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_SPI0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)  //使能寄存器地址转定义宏
#define CLK_SPI0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi0_START //时钟使能位偏移

/* 转定义时钟clk_spi0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_SPI0_CLKSEL_REG_ADDR    NULL   //父时钟选择寄存器地址转定义宏
#define CLK_SPI0_CLKSEL_MASK        0 //父时钟选择掩码
#define CLK_SPI0_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_SPI0_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_SPI0_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_SPI0_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

#define PCLK_SPI0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)  //使能寄存器地址转定义宏
#define PCLK_SPI0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi0_pclk_START //时钟使能位偏移

/* 转定义时钟clk_spi0的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_SPI0_CLKSEL_REG_ADDR    NULL   //父时钟选择寄存器地址转定义宏
#define PCLK_SPI0_CLKSEL_MASK        0 //父时钟选择掩码
#define PCLK_SPI0_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_SPI0_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define PCLK_SPI0_CLKDIV_MASK        0                   //时钟分频掩码
#define PCLK_SPI0_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_spi0操作宏相关转定义 */

/* clk_spi1操作宏相关转定义 */
/* 转定义时钟clk_spi1的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_SPI1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define CLK_SPI1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi1_START         //时钟使能位偏移

/* 转定义时钟clk_spi1的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_SPI1_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define CLK_SPI1_CLKSEL_MASK        0   //父时钟选择掩码
#define CLK_SPI1_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_SPI1_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define CLK_SPI1_CLKDIV_MASK        0                   //时钟分频掩码
#define CLK_SPI1_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* 转定义时钟clk_spi1的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_SPI1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //使能寄存器地址转定义宏
#define PCLK_SPI1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi1_pclk_START         //时钟使能位偏移

/* 转定义时钟clk_spi1的时钟选择寄存器、选择掩码和设置有效标志位 */
#define PCLK_SPI1_CLKSEL_REG_ADDR    NULL    //父时钟选择寄存器地址转定义宏
#define PCLK_SPI1_CLKSEL_MASK        0   //父时钟选择掩码
#define PCLK_SPI1_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define PCLK_SPI1_CLKDIV_REG_ADDR    NULL    //时钟分频寄存器地址转定义宏
#define PCLK_SPI1_CLKDIV_MASK        0                   //时钟分频掩码
#define PCLK_SPI1_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_spi1操作宏相关转定义 */

/* clk_dsppll_hifi_core_gated操作宏相关转定义 */
/* 转定义时钟clk_dsppll_hifi_core_gated的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_DSPPLL_HIFI_CORE_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_DSPPLL_HIFI_CORE_GATED_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_hifi_core_gated_START           //时钟使能位偏移

/* 转定义时钟clk_dsppll_hifi_core_gated的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKSEL_REG_ADDR  NULL    //父时钟选择寄存器地址转定义宏
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKSEL_MASK      0   //父时钟选择掩码
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_DSPPLL_HIFI_CORE_GATED_CLKDIV_REG_ADDR  NULL    //时钟分频寄存器地址转定义宏
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKDIV_MASK      0                   //时钟分频掩码
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_dsppll_hifi_core_gated操作宏相关转定义 */

/* clk_hifi_core操作宏相关转定义 */
/* 转定义时钟clk_hifi_core的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_HIFI_CORE_ENABLE_REG_ADDR       NULL    //使能寄存器地址转定义宏
#define CLK_HIFI_CORE_ENABLE_BIT_OFFSET     0           //时钟使能位偏移

/* 转定义时钟clk_hifi_core的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_HIFI_CORE_CLKSEL_REG_ADDR   NULL    //父时钟选择寄存器地址转定义宏
#define CLK_HIFI_CORE_CLKSEL_MASK       0   //父时钟选择掩码
#define CLK_HIFI_CORE_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_HIFI_CORE_CLKDIV_REG_ADDR   NULL    //时钟分频寄存器地址转定义宏
#define CLK_HIFI_CORE_CLKDIV_MASK       0                   //时钟分频掩码
#define CLK_HIFI_CORE_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_hifi_core操作宏相关转定义 */
#define CLK_CSI_APB_MUX_ENABLE_REG_ADDR         SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_CSI_APB_MUX_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi_apb_mux_START            //时钟使能位偏移

/* 转定义时钟clk_csi_apb_mux的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_CSI_APB_MUX_CLKSEL_REG_ADDR     NULL    //父时钟选择寄存器地址转定义宏
#define CLK_CSI_APB_MUX_CLKSEL_MASK         0   //父时钟选择掩码
#define CLK_CSI_APB_MUX_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_CSI_APB_MUX_CLKDIV_REG_ADDR     NULL    //时钟分频寄存器地址转定义宏
#define CLK_CSI_APB_MUX_CLKDIV_MASK         0                   //时钟分频掩码
#define CLK_CSI_APB_MUX_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_csi_apb_mux操作宏相关转定义 */

/* clk_csio_cfg操作宏相关转定义 */
/* 转定义时钟clk_csio_cfg的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_CSIO_CFG_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_CSIO_CFG_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_csio_cfg_START           //时钟使能位偏移

/* 转定义时钟clk_csio_cfg的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_CSIO_CFG_CLKSEL_REG_ADDR        NULL    //父时钟选择寄存器地址转定义宏
#define CLK_CSIO_CFG_CLKSEL_MASK            0   //父时钟选择掩码
#define CLK_CSIO_CFG_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_CSIO_CFG_CLKDIV_REG_ADDR        NULL    //时钟分频寄存器地址转定义宏
#define CLK_CSIO_CFG_CLKDIV_MASK            0                   //时钟分频掩码
#define CLK_CSIO_CFG_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_csio_cfg操作宏相关转定义 */

/* csi1_cfg_clk操作宏相关转定义 */
/* 转定义时钟csi1_cfg_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CSI1_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CSI1_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi1_cfg_clk_START           //时钟使能位偏移

/* 转定义时钟csi1_cfg_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CSI1_CFG_CLK_CLKSEL_REG_ADDR        NULL    //父时钟选择寄存器地址转定义宏
#define CSI1_CFG_CLK_CLKSEL_MASK            0   //父时钟选择掩码
#define CSI1_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CSI1_CFG_CLK_CLKDIV_REG_ADDR        NULL    //时钟分频寄存器地址转定义宏
#define CSI1_CFG_CLK_CLKDIV_MASK            0                   //时钟分频掩码
#define CSI1_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* csi1_cfg_clk操作宏相关转定义 */

/* csi2_cfg_clk操作宏相关转定义 */
/* 转定义时钟csi2_cfg_clk的使能寄存器，状态寄存器的地址和位偏移 */
#define CSI2_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //使能寄存器地址转定义宏
#define CSI2_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi2_cfg_clk_START           //时钟使能位偏移

/* 转定义时钟csi2_cfg_clk的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CSI2_CFG_CLK_CLKSEL_REG_ADDR        NULL    //父时钟选择寄存器地址转定义宏
#define CSI2_CFG_CLK_CLKSEL_MASK            0   //父时钟选择掩码
#define CSI2_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CSI2_CFG_CLK_CLKDIV_REG_ADDR        NULL    //时钟分频寄存器地址转定义宏
#define CSI2_CFG_CLK_CLKDIV_MASK            0                   //时钟分频掩码
#define CSI2_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* csi2_cfg_clk操作宏相关转定义 */

/* clk_pmussi操作宏相关转定义 */
/* 转定义时钟clk_pmussi的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_PMUSSI_ENABLE_REG_ADDR        SOC_AO_SCTRL_SC_PERIPH_CLKEN5_ADDR(SCTRL_ON_BASE_ADDR)   //使能寄存器地址转定义宏
#define CLK_PMUSSI_ENABLE_BIT_OFFSET      SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_pmussi_START           //时钟使能位偏移

/* 转定义时钟clk_pmussi的时钟选择寄存器、选择掩码和设置有效标志位 */
#define CLK_PMUSSI_CLKSEL_REG_ADDR        NULL    //父时钟选择寄存器地址转定义宏
#define CLK_PMUSSI_CLKSEL_MASK            0   //父时钟选择掩码
#define CLK_PMUSSI_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //父时钟选择有效标志位

#define CLK_PMUSSI_CLKDIV_REG_ADDR        NULL    //时钟分频寄存器地址转定义宏
#define CLK_PMUSSI_CLKDIV_MASK            0                   //时钟分频掩码
#define CLK_PMUSSI_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //时钟分频设置有效标志位

/* clk_pmussi操作宏相关转定义 */
/* clk_rtc操作宏相关转定义 */
/* 转定义时钟clk_rtc的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_RTC_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_RTC_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_rtc_START  /* 时钟使能位偏移 */

/* clk_watchdog0操作宏相关转定义 */
/* 转定义时钟clk_watchdog0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_WATCHDOG0_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_WATCHDOG0_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_START  /* 时钟使能位偏移 */

/* pclk_watchdog0操作宏相关转定义 */
/* 转定义时钟clk_watchdog0_pclk的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_WATCHDOG0_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_WATCHDOG0_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_pclk_START  /* 时钟使能位偏移 */

#define HCLK_USBOTG_ON_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN6_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define HCLK_USBOTG_ON_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_hclk_usbotg_START  /* 时钟使能位偏移 */

#define HCLK_USBOTG_OFF_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define HCLK_USBOTG_OFF_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_usbotg_bus_clk_START  /* 时钟使能位偏移 */

#define CLK_USBOTG_OFF_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_USBOTG_OFF_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_usbotg_work_clk_START  /* 时钟使能位偏移 */

#define CLK_PICOPHY_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN6_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_PICOPHY_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_clk_picophy_START  /* 时钟使能位偏移 */

#define CLK_PICOPHY_TEST_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN6_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_PICOPHY_TEST_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_clk_picophy_test_START  /* 时钟使能位偏移 */

#define CLK_TS_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TS_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ts_clk_START  /* 时钟使能位偏移 */

#define HCLK_TS_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define HCLK_TS_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ts_hclk_START  /* 时钟使能位偏移 */

#define CLK_GPS_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_GPS_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_clk_tcxo_gps_START  /* 时钟使能位偏移 */

#define CLK_TSENSOR0_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TSENSOR0_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_tsensor0_clk_START  /* 时钟使能位偏移 */

#define CLK_TSENSOR1_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TSENSOR1_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_tsensor1_clk_START  /* 时钟使能位偏移 */

/* clk_ap_dmac_axi0操作宏相关转定义 */
/* 转定义时钟clk_ap_dmac_axi0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_AP_DMAC_AXI0_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_AP_DMAC_AXI0_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ap_dmac_axi0_START  /* 时钟使能位偏移 */

/* clk_ap_dmac_axi1操作宏相关转定义 */
/* 转定义时钟clk_ap_dmac_axi1的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_AP_DMAC_AXI1_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_AP_DMAC_AXI1_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ap_dmac_axi1_START  /* 时钟使能位偏移 */

/* pclk_timer0操作宏相关转定义 */
/* 转定义时钟pclk_timer0的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER0_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER0_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_pclk_START  /* 时钟使能位偏移 */

/* clk_timer0操作宏相关转定义 */
/* 转定义时钟clk_timer0的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER0_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER0_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_START  /* 时钟使能位偏移 */
#define CLK_TIMER0_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER0_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_1acpu_dualtimer0_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_1acpu_dualtimer0_en0_END) //父时钟选择掩码
#define CLK_TIMER0_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_1acpu_dualtimer0_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_1acpu_dualtimer0_en0_END) //父时钟选择掩码        //父时钟选择有效标志位

/* pclk_timer1操作宏相关转定义 */
/* 转定义时钟pclk_timer1的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER1_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER1_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_pclk_START  /* 时钟使能位偏移 */

/* clk_timer1操作宏相关转定义 */
/* 转定义时钟clk_timer1的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER1_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER1_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_START  /* 时钟使能位偏移 */
#define CLK_TIMER1_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER1_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_3acpu_dualtimer0_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_3acpu_dualtimer0_en1_END) //父时钟选择掩码
#define CLK_TIMER1_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_3acpu_dualtimer0_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_3acpu_dualtimer0_en1_END) //父时钟选择掩码    

/* pclk_timer2操作宏相关转定义 */
/* 转定义时钟pclk_timer2的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER2_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER2_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_pclk_START  /* 时钟使能位偏移 */

/* clk_timer2操作宏相关转定义 */
/* 转定义时钟clk_timer2的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER2_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER2_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_START  /* 时钟使能位偏移 */
#define CLK_TIMER2_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER2_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_5acpu_dualtimer1_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_5acpu_dualtimer1_en0_END) //父时钟选择掩码
#define CLK_TIMER2_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_5acpu_dualtimer1_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_5acpu_dualtimer1_en0_END) //父时钟选择掩码 


/* pclk_timer3操作宏相关转定义 */
/* 转定义时钟pclk_timer3的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER3_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER3_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_pclk_START  /* 时钟使能位偏移 */

/* clk_timer3操作宏相关转定义 */
/* 转定义时钟clk_timer3的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER3_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER3_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_START  /* 时钟使能位偏移 */
#define CLK_TIMER3_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER3_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_7acpu_dualtimer1_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_7acpu_dualtimer1_en1_END) //父时钟选择掩码
#define CLK_TIMER3_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_7acpu_dualtimer1_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_7acpu_dualtimer1_en1_END) //父时钟选择掩码 

/* pclk_timer4操作宏相关转定义 */
/* 转定义时钟pclk_timer4的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER4_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER4_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_pclk_START  /* 时钟使能位偏移 */

/* clk_timer4操作宏相关转定义 */
/* 转定义时钟clk_timer4的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER4_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER4_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_START  /* 时钟使能位偏移 */
#define CLK_TIMER4_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER4_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_9acpu_dualtimer2_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_9acpu_dualtimer2_en0_END) //父时钟选择掩码
#define CLK_TIMER4_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_9acpu_dualtimer2_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_9acpu_dualtimer2_en0_END) //父时钟选择掩码

/* pclk_timer5操作宏相关转定义 */
/* 转定义时钟pclk_timer5的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER5_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER5_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_pclk_START  /* 时钟使能位偏移 */

/* clk_timer5操作宏相关转定义 */
/* 转定义时钟clk_timer5的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER5_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER5_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_START  /* 时钟使能位偏移 */
#define CLK_TIMER5_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER5_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_11acpu_dualtimer2_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_11acpu_dualtimer2_en1_END) //父时钟选择掩码
#define CLK_TIMER5_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_11acpu_dualtimer2_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_11acpu_dualtimer2_en1_END) //父时钟选择掩码 

/* pclk_timer6操作宏相关转定义 */
/* 转定义时钟pclk_timer6的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER6_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER6_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_pclk_START  /* 时钟使能位偏移 */

/* clk_timer6操作宏相关转定义 */
/* 转定义时钟clk_timer6的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER6_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER6_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_START  /* 时钟使能位偏移 */
#define CLK_TIMER6_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER6_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_13acpu_dualtimer3_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_13acpu_dualtimer3_en0_END) //父时钟选择掩码
#define CLK_TIMER6_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_13acpu_dualtimer3_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_13acpu_dualtimer3_en0_END) //父时钟选择掩码 


/* pclk_timer7操作宏相关转定义 */
/* 转定义时钟pclk_timer7的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER7_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER7_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_pclk_START  /* 时钟使能位偏移 */

/* clk_timer7操作宏相关转定义 */
/* 转定义时钟clk_timer7的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER7_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER7_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_START  /* 时钟使能位偏移 */
#define CLK_TIMER7_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER7_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_15acpu_dualtimer3_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_15acpu_dualtimer3_en1_END) //父时钟选择掩码
#define CLK_TIMER7_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_15acpu_dualtimer3_en1_START , \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_15acpu_dualtimer3_en1_END) //父时钟选择掩码

/* pclk_timer8操作宏相关转定义 */
/* 转定义时钟pclk_timer8的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER8_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER8_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4pclk_START  /* 时钟使能位偏移 */

/* clk_timer8操作宏相关转定义 */
/* 转定义时钟clk_timer8的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER8_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER8_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4_START  /* 时钟使能位偏移 */
#define CLK_TIMER8_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN1_ADDR(SCTRL_ON_BASE_ADDR) //父时钟选择寄存器地址转定义宏
#define CLK_TIMER8_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_1acpu_dualtimer4_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_1acpu_dualtimer4_en0_END) //父时钟选择掩码
#define CLK_TIMER8_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_1acpu_dualtimer4_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_1acpu_dualtimer4_en0_END) //父时钟选择掩码 

/* pclk_timer8操作宏相关转定义 */
/* 转定义时钟pclk_timer8的使能寄存器，状态寄存器的地址和位偏移 */
#define PCLK_TIMER9_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define PCLK_TIMER9_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4pclk_START  /* 时钟使能位偏移 */

/* clk_timer8操作宏相关转定义 */
/* 转定义时钟clk_timer8的使能寄存器，状态寄存器的地址和位偏移 */
#define CLK_TIMER9_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* 使能寄存器地址转定义宏 */
#define CLK_TIMER9_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4_START  /* 时钟使能位偏移 */

#define CLK_GPIO0_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO0_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio0<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO0_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO0_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO0_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO0_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio0<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio1<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio1<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO1_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO1_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio1<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO1_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO1_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO1_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO1_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO1_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO1_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio1<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio2<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio2<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO2_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO2_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio2<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO2_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO2_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO2_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO2_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO2_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO2_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio2<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio3<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio3<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO3_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO3_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>
#define CLK_GPIO3_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO3_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO3_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO3_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO3_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO3_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio3<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio4<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio4<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO4_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO4_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio4<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO4_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO4_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO4_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO4_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO4_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO4_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio4<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio5<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio5<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO5_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO5_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio5<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO5_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO5_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO5_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO5_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO5_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO5_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio5<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
#define CLK_GPIO6_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO6_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* clk_gpio6<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio6<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO6_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO6_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio6<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO6_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO6_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO6_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????
/* clk_gpio6<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
#define CLK_GPIO6_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO6_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO6_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio7<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio7<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO7_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO7_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio7<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO7_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO7_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO7_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO7_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO7_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO7_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio7<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio8<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio8<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO8_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO8_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio8<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO8_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO8_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO8_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO8_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO8_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO8_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio8<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio9<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio9<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO9_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO9_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio9<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO9_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO9_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO9_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO9_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO9_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO9_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio9<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
#define CLK_GPIO10_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO10_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio10<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO10_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO10_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO10_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????
#define CLK_GPIO10_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO10_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO10_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio10<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio11<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio11<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO11_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO11_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio11<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO11_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO11_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO11_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO11_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO11_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO11_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio11<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio12<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio12<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO12_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO12_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio12<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO12_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO12_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO12_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO12_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO12_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO12_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio12<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
#define CLK_GPIO13_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO13_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* clk_gpio13<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio13<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO13_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO13_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO13_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO13_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO13_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO13_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio13<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio14<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio14<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO14_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO14_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio14<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO14_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO14_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO14_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO14_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO14_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO14_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio14<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio15<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio15<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO15_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO15_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio15<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO15_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO15_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO15_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO15_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO15_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO15_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio15<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio16<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio16<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO16_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO16_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio16<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO16_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO16_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO16_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO16_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO16_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO16_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio16<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio17<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio17<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO17_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO17_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio17<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO17_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO17_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO17_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA>????

#define CLK_GPIO17_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO17_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO17_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

/* clk_gpio17<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */

/* clk_gpio18<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>×a<B6><A8><D2><E5> */
/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio18<B5><C4>ê1<C4>ü??′<E6><C6><F7><A3><AC>×′ì?<BC>?′<E6><C6><F7><B5>?μ<D8>?·<BA><CD>????<D2><C6> */
#define CLK_GPIO18_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO18_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio18<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO18_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO18_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO18_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA> */
#define CLK_GPIO18_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO18_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO18_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????
#define CLK_GPIO19_ENABLE_REG_ADDR       NULL    //ê1<C4>ü??′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO19_ENABLE_BIT_OFFSET     0           //ê±<D6><D3>ê1<C4><DC>????<D2><C6>

/* ×a<B6><A8><D2><E5>ê±<D6><D3>clk_gpio18<B5><C4>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D§<B1><EA>???? */
#define CLK_GPIO19_CLKSEL_REG_ADDR   NULL    //<B8><B8>ê±<D6><D3>??<D4><F1><BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO19_CLKSEL_MASK       0   //<B8><B8>ê±<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO19_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>ê±<D6><D3>??<D4><F1><D3><D0>D§<B1><EA> */
#define CLK_GPIO19_CLKDIV_REG_ADDR   NULL    //ê±<D6>ó·<D6>?μ<BC>?′<E6><C6><F7><B5><D8>?·×a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO19_CLKDIV_MASK       0                   //ê±<D6>ó·<D6>?μ<D1><DA><C2><EB>
#define CLK_GPIO19_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ê±<D6>ó·<D6>?μ<C9><E8><D6><C3><D3><D0>D§<B1><EA>????

