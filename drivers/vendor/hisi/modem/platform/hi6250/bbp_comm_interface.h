

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __BBP_COMM_INTERFACE_H__
#define __BBP_COMM_INTERFACE_H__

#include "bbp_comm_fe_interface.h"
#include "bbp_guc_bbpmst_interface.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/3) register_define_irm_cs
 ***======================================================================***/
/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    用于irm_cs模式选择，影响irm_cs内部时钟切换和模式切换，默认都为0。
             3'b001，UMTS模式（包括均衡，译码R99相关RAM）；
             3'b010，LTE模式（上行HARQ部分）；
             3'b100，CDMA模式；
             3'b000，无（default）。
   UNION结构:  BBPCOMM_IRM_CS_RAM_CTRL_UNION */
#define BBPCOMM_IRM_CS_RAM_CTRL_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xA000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      irm_cs模块时钟门控旁路开关。默认为0，即开启时钟门控。配置1则开启旁路功能，时钟门控失效。
   UNION结构:  BBPCOMM_IRM_CS_CLK_BYPASS_UNION */
#define BBPCOMM_IRM_CS_CLK_BYPASS_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xA004)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL0_CS_UNION */
#define BBPCOMM_MEM_CTRL0_CS_ADDR                     (SOC_BBP_COMM_2_BASE_ADDR + 0xA00C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL1_CS_UNION */
#define BBPCOMM_MEM_CTRL1_CS_ADDR                     (SOC_BBP_COMM_2_BASE_ADDR + 0xA010)



/***======================================================================***
                     (2/3) register_define_irm_ps
 ***======================================================================***/
/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    用于irm_ps网络模式选择，影响irm_ps内部时钟切换和模式切换，默认都为0。.
             6'b000001，GBBP1模式；
             6'b000110，UMTS模式；
             6'b001000，LTE模式；
             6'b010000，TDS-CDMA模式；
             6'b100000，CDMA模式。
             注：GBBP1固定为主卡（G0/U/L/T）。
   UNION结构:  BBPCOMM_IRM_PS_RAM_CTRL_UNION */
#define BBPCOMM_IRM_PS_RAM_CTRL_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xB000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      GBBP2，默认为0，1为使能。
             注：GBBP2固定为辅卡。
             V8R1不使用。
   UNION结构:  BBPCOMM_IRM_PS_GSM2_CTRL_UNION */
#define BBPCOMM_IRM_PS_GSM2_CTRL_ADDR                 (SOC_BBP_COMM_2_BASE_ADDR + 0xB004)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      irm_ps模块时钟门控旁路开关。默认为0，即开启时钟门控。配置1则开启旁路功能，时钟门控失效。
   UNION结构:  BBPCOMM_IRM_PS_CLK_BYPASS_UNION */
#define BBPCOMM_IRM_PS_CLK_BYPASS_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xB008)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL0_TURBO_UNION */
#define BBPCOMM_MEM_CTRL0_TURBO_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xB010)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL1_TURBO_UNION */
#define BBPCOMM_MEM_CTRL1_TURBO_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xB014)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:8]   LTE两通道选择信号，0表示选择通道0,1表示选择通道1
             bit[8]，表示grp0
             bit[9]，表示grp1
             bit[10]，表示grp2
             bit[11]，表示grp3
             bit[12]，表示grp4
             bit[13]，表示grp5
 bit[7:6]    保留
 bit[5:0]    1表示选择配置的lte_irm_grp_clk_over_val，0表示选择从LTE输入的grp_clk_sel
             bit[0]，表示grp0
             bit[1]，表示grp1
             bit[2]，表示grp2
             bit[3]，表示grp3
             bit[4]，表示grp4
             bit[5]，表示grp5
   UNION结构:  BBPCOMM_LTE_IRM_GRP_SEL_UNION */
#define BBPCOMM_LTE_IRM_GRP_SEL_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xB018)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL0_PS_UNION */
#define BBPCOMM_MEM_CTRL0_PS_ADDR                     (SOC_BBP_COMM_2_BASE_ADDR + 0xB020)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL1_PS_UNION */
#define BBPCOMM_MEM_CTRL1_PS_ADDR                     (SOC_BBP_COMM_2_BASE_ADDR + 0xB024)

/* 寄存器说明：
 bit[31:16]  turbo译码子模块级门控旁路使能，高电平有效。
 bit[15:0]   turbo译码子模块级门控旁路使能，高电平有效。
   UNION结构:  BBPCOMM_TUBO_CKG_UNION */
#define BBPCOMM_TUBO_CKG_ADDR                         (SOC_BBP_COMM_2_BASE_ADDR + 0xB028)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      Turbo译码模式选择信号（L模）。
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
             3'b000，U模；
             3'b001，L模；
             3'b010，T模；
             3'b100，C模；
             其他，无意义。
   UNION结构:  BBPCOMM_U_L_TYPE_UNION */
#define BBPCOMM_U_L_TYPE_ADDR                         (SOC_BBP_COMM_2_BASE_ADDR + 0xB02C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      Turbo译码模式选择信号（T模）。
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
             3'b000，U模；
             3'b001，L模；
             3'b010，T模；
             3'b100，C模；
             其他，无意义。
   UNION结构:  BBPCOMM_U_T_TYPE_UNION */
#define BBPCOMM_U_T_TYPE_ADDR                         (SOC_BBP_COMM_2_BASE_ADDR + 0xB030)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      Turbo译码模式选择信号（C模）。
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
             3'b000，U模；
             3'b001，L模；
             3'b010，T模；
             3'b100，C模；
             其他，无意义。
   UNION结构:  BBPCOMM_U_C_TYPE_UNION */
#define BBPCOMM_U_C_TYPE_ADDR                         (SOC_BBP_COMM_2_BASE_ADDR + 0xB034)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:14]  SOC AP配置给ps ram的occupy配置信号。
 bit[13:12]  
 bit[11:10]  
 bit[9:8]    
 bit[7:6]    
 bit[5:4]    
 bit[3:2]    
 bit[1:0]    
   UNION结构:  BBPCOMM_SOC_AP_OCCUPY_GRP_UNION */
#define BBPCOMM_SOC_AP_OCCUPY_GRP_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xB038)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      W SDR模式下译码时钟选择。0，译码采用122m时钟；1，译码采用245m时钟。
 bit[0]      W SDR模式开关使能。
   UNION结构:  BBPCOMM_PS_W_SDR_EN_UNION */
#define BBPCOMM_PS_W_SDR_EN_ADDR                      (SOC_BBP_COMM_2_BASE_ADDR + 0xB03C)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      turbo译码器通过硬判比对判断收敛方法的切换开关，默认打开
             0：比较连续两次的迭代处理结果，一致则认为收敛；
             1：比较连续三次的迭代处理结果，一致则认为收敛；
 bit[3:1]    保留
 bit[0]      Turbo译码器硬判比对提前停止迭代使能，默认使用CRC校验的提前停止方法
             0：禁止
             1：使能
   UNION结构:  BBPCOMM_TURBO_HD_JUDGE_EN_UNION */
#define BBPCOMM_TURBO_HD_JUDGE_EN_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xB040)



/***======================================================================***
                     (3/3) register_define_glb_bbc
 ***======================================================================***/
/* 寄存器说明：
 bit[31:4]   保留
 bit[3:2]    bit[1]：0，表示采集GBBP1的数据；1，表示采集GBBP2的数据。现无意义，保留。
             bit[0]：0，表示采集W数据；1表示采集G数据。现无意义，保留。
 bit[1:0]    bit[1]：0，表示采集GBBP1的数据；1，表示采集GBBP2的数据。
             bit[0]：0，表示采集W数据；1表示采集G数据。现无意义，保留。
   UNION结构:  BBPCOMM_BBP_DUMP_DBG_MODE_UNION */
#define BBPCOMM_BBP_DUMP_DBG_MODE_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xD800)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      WSDR模式下译码时钟选择。0，译码采用122m时钟；1，译码采用245m时钟。现无意义，保留。
 bit[1]      WSDR模式开关使能。现无意义，保留。
 bit[0]      GSDR模式开关使能。现无意义，保留。
   UNION结构:  BBPCOMM_GU_SDR_EN_UNION */
#define BBPCOMM_GU_SDR_EN_ADDR                        (SOC_BBP_COMM_2_BASE_ADDR + 0xD804)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      UC2_SHARE CPU接口时钟自动门控BYPASS信号。
 bit[8]      CBBP_TOP_2 CPU接口时钟自动门控BYPASS信号。
 bit[7]      WBBP_R99 CPU接口时钟自动门控BYPASS信号。
 bit[6]      WTC_SHARE CPU接口时钟自动门控BYPASS信号。
 bit[5]      CBBP_TOP CPU接口时钟自动门控BYPASS信号。
 bit[4]      WBBP_TOP2 CPU接口时钟自动门控BYPASS信号。
 bit[3]      WBBP_TOP1 CPU接口时钟自动门控BYPASS信号。
 bit[2]      GBBP_TOP2 CPU接口时钟自动门控BYPASS信号。
 bit[1]      GBBP_TOP1 CPU接口时钟自动门控BYPASS信号。
 bit[0]      BBC_COMM CPU接口时钟自动门控BYPASS信号。
   UNION结构:  BBPCOMM_CPU_CLK_GATE_BYPASS_UNION */
#define BBPCOMM_CPU_CLK_GATE_BYPASS_ADDR              (SOC_BBP_COMM_2_BASE_ADDR + 0xD808)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      CDMA GPS同步信号选择。0，选择CBBP_TOP输出的GPS同步信号；1，选择CBBP_TOP_2输出的GPS同步信号。
   UNION结构:  BBPCOMM_CDMA_GPS_SYNC_SEL_UNION */
#define BBPCOMM_CDMA_GPS_SYNC_SEL_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xD80C)





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

/***======================================================================***
                     (1/3) register_define_irm_cs
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_IRM_CS_RAM_CTRL_UNION
 结构说明  : IRM_CS_RAM_CTRL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_cs_ram_ctrl_reg;
    struct
    {
        unsigned int  irm_cs_ram_ctrl : 3;  /* bit[0-2] : 用于irm_cs模式选择，影响irm_cs内部时钟切换和模式切换，默认都为0。
                                                          3'b001，UMTS模式（包括均衡，译码R99相关RAM）；
                                                          3'b010，LTE模式（上行HARQ部分）；
                                                          3'b100，CDMA模式；
                                                          3'b000，无（default）。 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_IRM_CS_RAM_CTRL_UNION;
#define BBPCOMM_IRM_CS_RAM_CTRL_irm_cs_ram_ctrl_START  (0)
#define BBPCOMM_IRM_CS_RAM_CTRL_irm_cs_ram_ctrl_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_IRM_CS_CLK_BYPASS_UNION
 结构说明  : IRM_CS_CLK_BYPASS 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_cs_clk_bypass_reg;
    struct
    {
        unsigned int  irm_cs_clk_bypass : 1;  /* bit[0]   : irm_cs模块时钟门控旁路开关。默认为0，即开启时钟门控。配置1则开启旁路功能，时钟门控失效。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_IRM_CS_CLK_BYPASS_UNION;
#define BBPCOMM_IRM_CS_CLK_BYPASS_irm_cs_clk_bypass_START  (0)
#define BBPCOMM_IRM_CS_CLK_BYPASS_irm_cs_clk_bypass_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL0_CS_UNION
 结构说明  : MEM_CTRL0_CS 寄存器结构定义。地址偏移量:0x00C，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_cs_reg;
    struct
    {
        unsigned int  mem_ctrl_s_cs      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned int  mem_ctrl_d_1w2r_cs : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
    } reg;
} BBPCOMM_MEM_CTRL0_CS_UNION;
#define BBPCOMM_MEM_CTRL0_CS_mem_ctrl_s_cs_START       (0)
#define BBPCOMM_MEM_CTRL0_CS_mem_ctrl_s_cs_END         (15)
#define BBPCOMM_MEM_CTRL0_CS_mem_ctrl_d_1w2r_cs_START  (16)
#define BBPCOMM_MEM_CTRL0_CS_mem_ctrl_d_1w2r_cs_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL1_CS_UNION
 结构说明  : MEM_CTRL1_CS 寄存器结构定义。地址偏移量:0x010，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_cs_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_cs : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned int  rom_ctrl_cs          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned int  reserved             : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_MEM_CTRL1_CS_UNION;
#define BBPCOMM_MEM_CTRL1_CS_mem_ctrl_d_1rw2rw_cs_START  (0)
#define BBPCOMM_MEM_CTRL1_CS_mem_ctrl_d_1rw2rw_cs_END    (15)
#define BBPCOMM_MEM_CTRL1_CS_rom_ctrl_cs_START           (16)
#define BBPCOMM_MEM_CTRL1_CS_rom_ctrl_cs_END             (23)


/***======================================================================***
                     (2/3) register_define_irm_ps
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_IRM_PS_RAM_CTRL_UNION
 结构说明  : IRM_PS_RAM_CTRL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_ps_ram_ctrl_reg;
    struct
    {
        unsigned int  irm_ps_ram_ctrl : 6;  /* bit[0-5] : 用于irm_ps网络模式选择，影响irm_ps内部时钟切换和模式切换，默认都为0。.
                                                          6'b000001，GBBP1模式；
                                                          6'b000110，UMTS模式；
                                                          6'b001000，LTE模式；
                                                          6'b010000，TDS-CDMA模式；
                                                          6'b100000，CDMA模式。
                                                          注：GBBP1固定为主卡（G0/U/L/T）。 */
        unsigned int  reserved        : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_IRM_PS_RAM_CTRL_UNION;
#define BBPCOMM_IRM_PS_RAM_CTRL_irm_ps_ram_ctrl_START  (0)
#define BBPCOMM_IRM_PS_RAM_CTRL_irm_ps_ram_ctrl_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_IRM_PS_GSM2_CTRL_UNION
 结构说明  : IRM_PS_GSM2_CTRL 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_ps_gsm2_ctrl_reg;
    struct
    {
        unsigned int  irm_ps_gsm2_ctrl : 1;  /* bit[0]   : GBBP2，默认为0，1为使能。
                                                           注：GBBP2固定为辅卡。
                                                           V8R1不使用。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_IRM_PS_GSM2_CTRL_UNION;
#define BBPCOMM_IRM_PS_GSM2_CTRL_irm_ps_gsm2_ctrl_START  (0)
#define BBPCOMM_IRM_PS_GSM2_CTRL_irm_ps_gsm2_ctrl_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_IRM_PS_CLK_BYPASS_UNION
 结构说明  : IRM_PS_CLK_BYPASS 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_ps_clk_bypass_reg;
    struct
    {
        unsigned int  irm_ps_clk_bypass : 1;  /* bit[0]   : irm_ps模块时钟门控旁路开关。默认为0，即开启时钟门控。配置1则开启旁路功能，时钟门控失效。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_IRM_PS_CLK_BYPASS_UNION;
#define BBPCOMM_IRM_PS_CLK_BYPASS_irm_ps_clk_bypass_START  (0)
#define BBPCOMM_IRM_PS_CLK_BYPASS_irm_ps_clk_bypass_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL0_TURBO_UNION
 结构说明  : MEM_CTRL0_TURBO 寄存器结构定义。地址偏移量:0x010，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_turbo_reg;
    struct
    {
        unsigned int  mem_ctrl_s_turbo      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned int  mem_ctrl_d_1w2r_turbo : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
    } reg;
} BBPCOMM_MEM_CTRL0_TURBO_UNION;
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_s_turbo_START       (0)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_s_turbo_END         (15)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_d_1w2r_turbo_START  (16)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_d_1w2r_turbo_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL1_TURBO_UNION
 结构说明  : MEM_CTRL1_TURBO 寄存器结构定义。地址偏移量:0x014，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_turbo_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_turbo : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned int  rom_ctrl_turbo          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_MEM_CTRL1_TURBO_UNION;
#define BBPCOMM_MEM_CTRL1_TURBO_mem_ctrl_d_1rw2rw_turbo_START  (0)
#define BBPCOMM_MEM_CTRL1_TURBO_mem_ctrl_d_1rw2rw_turbo_END    (15)
#define BBPCOMM_MEM_CTRL1_TURBO_rom_ctrl_turbo_START           (16)
#define BBPCOMM_MEM_CTRL1_TURBO_rom_ctrl_turbo_END             (23)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_IRM_GRP_SEL_UNION
 结构说明  : LTE_IRM_GRP_SEL 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      lte_irm_grp_sel_reg;
    struct
    {
        unsigned int  lte_irm_grp_clk_sel_overwhelm : 6;  /* bit[0-5]  : 1表示选择配置的lte_irm_grp_clk_over_val，0表示选择从LTE输入的grp_clk_sel
                                                                         bit[0]，表示grp0
                                                                         bit[1]，表示grp1
                                                                         bit[2]，表示grp2
                                                                         bit[3]，表示grp3
                                                                         bit[4]，表示grp4
                                                                         bit[5]，表示grp5 */
        unsigned int  reserved_0                    : 2;  /* bit[6-7]  : 保留 */
        unsigned int  lte_irm_grp_clk_over_val      : 6;  /* bit[8-13] : LTE两通道选择信号，0表示选择通道0,1表示选择通道1
                                                                         bit[8]，表示grp0
                                                                         bit[9]，表示grp1
                                                                         bit[10]，表示grp2
                                                                         bit[11]，表示grp3
                                                                         bit[12]，表示grp4
                                                                         bit[13]，表示grp5 */
        unsigned int  reserved_1                    : 18; /* bit[14-31]: 保留 */
    } reg;
} BBPCOMM_LTE_IRM_GRP_SEL_UNION;
#define BBPCOMM_LTE_IRM_GRP_SEL_lte_irm_grp_clk_sel_overwhelm_START  (0)
#define BBPCOMM_LTE_IRM_GRP_SEL_lte_irm_grp_clk_sel_overwhelm_END    (5)
#define BBPCOMM_LTE_IRM_GRP_SEL_lte_irm_grp_clk_over_val_START       (8)
#define BBPCOMM_LTE_IRM_GRP_SEL_lte_irm_grp_clk_over_val_END         (13)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL0_PS_UNION
 结构说明  : MEM_CTRL0_PS 寄存器结构定义。地址偏移量:0x020，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_ps_reg;
    struct
    {
        unsigned int  mem_ctrl_s_ps      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned int  mem_ctrl_d_1w2r_ps : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
    } reg;
} BBPCOMM_MEM_CTRL0_PS_UNION;
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_s_ps_START       (0)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_s_ps_END         (15)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_d_1w2r_ps_START  (16)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_d_1w2r_ps_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL1_PS_UNION
 结构说明  : MEM_CTRL1_PS 寄存器结构定义。地址偏移量:0x024，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_ps_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_ps : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned int  rom_ctrl_ps          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned int  reserved             : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_MEM_CTRL1_PS_UNION;
#define BBPCOMM_MEM_CTRL1_PS_mem_ctrl_d_1rw2rw_ps_START  (0)
#define BBPCOMM_MEM_CTRL1_PS_mem_ctrl_d_1rw2rw_ps_END    (15)
#define BBPCOMM_MEM_CTRL1_PS_rom_ctrl_ps_START           (16)
#define BBPCOMM_MEM_CTRL1_PS_rom_ctrl_ps_END             (23)


/*****************************************************************************
 结构名    : BBPCOMM_TUBO_CKG_UNION
 结构说明  : TUBO_CKG 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      tubo_ckg_reg;
    struct
    {
        unsigned int  tubo_ram_ckg_en : 16; /* bit[0-15] : turbo译码子模块级门控旁路使能，高电平有效。 */
        unsigned int  tubo_mod_ckg_en : 16; /* bit[16-31]: turbo译码子模块级门控旁路使能，高电平有效。 */
    } reg;
} BBPCOMM_TUBO_CKG_UNION;
#define BBPCOMM_TUBO_CKG_tubo_ram_ckg_en_START  (0)
#define BBPCOMM_TUBO_CKG_tubo_ram_ckg_en_END    (15)
#define BBPCOMM_TUBO_CKG_tubo_mod_ckg_en_START  (16)
#define BBPCOMM_TUBO_CKG_tubo_mod_ckg_en_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_U_L_TYPE_UNION
 结构说明  : U_L_TYPE 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      u_l_type_reg;
    struct
    {
        unsigned int  u_l_type : 1;  /* bit[0]   : Turbo译码模式选择信号（L模）。
                                                   {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
                                                   3'b000，U模；
                                                   3'b001，L模；
                                                   3'b010，T模；
                                                   3'b100，C模；
                                                   其他，无意义。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_U_L_TYPE_UNION;
#define BBPCOMM_U_L_TYPE_u_l_type_START  (0)
#define BBPCOMM_U_L_TYPE_u_l_type_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_U_T_TYPE_UNION
 结构说明  : U_T_TYPE 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      u_t_type_reg;
    struct
    {
        unsigned int  u_t_type : 1;  /* bit[0]   : Turbo译码模式选择信号（T模）。
                                                   {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
                                                   3'b000，U模；
                                                   3'b001，L模；
                                                   3'b010，T模；
                                                   3'b100，C模；
                                                   其他，无意义。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_U_T_TYPE_UNION;
#define BBPCOMM_U_T_TYPE_u_t_type_START  (0)
#define BBPCOMM_U_T_TYPE_u_t_type_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_U_C_TYPE_UNION
 结构说明  : U_C_TYPE 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      u_c_type_reg;
    struct
    {
        unsigned int  u_c_type : 1;  /* bit[0]   : Turbo译码模式选择信号（C模）。
                                                   {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
                                                   3'b000，U模；
                                                   3'b001，L模；
                                                   3'b010，T模；
                                                   3'b100，C模；
                                                   其他，无意义。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_U_C_TYPE_UNION;
#define BBPCOMM_U_C_TYPE_u_c_type_START  (0)
#define BBPCOMM_U_C_TYPE_u_c_type_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_SOC_AP_OCCUPY_GRP_UNION
 结构说明  : SOC_AP_OCCUPY_GRP 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      soc_ap_occupy_grp_reg;
    struct
    {
        unsigned int  soc_ap_occupy_grp1 : 2;  /* bit[0-1]  :  */
        unsigned int  soc_ap_occupy_grp2 : 2;  /* bit[2-3]  :  */
        unsigned int  soc_ap_occupy_grp3 : 2;  /* bit[4-5]  :  */
        unsigned int  soc_ap_occupy_grp4 : 2;  /* bit[6-7]  :  */
        unsigned int  soc_ap_occupy_grp5 : 2;  /* bit[8-9]  :  */
        unsigned int  soc_ap_occupy_grp6 : 2;  /* bit[10-11]:  */
        unsigned int  soc_ap_occupy_grp7 : 2;  /* bit[12-13]:  */
        unsigned int  soc_ap_occupy_grp8 : 2;  /* bit[14-15]: SOC AP配置给ps ram的occupy配置信号。 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_SOC_AP_OCCUPY_GRP_UNION;
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp1_START  (0)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp1_END    (1)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp2_START  (2)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp2_END    (3)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp3_START  (4)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp3_END    (5)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp4_START  (6)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp4_END    (7)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp5_START  (8)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp5_END    (9)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp6_START  (10)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp6_END    (11)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp7_START  (12)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp7_END    (13)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp8_START  (14)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp8_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_PS_W_SDR_EN_UNION
 结构说明  : PS_W_SDR_EN 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ps_w_sdr_en_reg;
    struct
    {
        unsigned int  ps_w_sdr_en          : 1;  /* bit[0]   : W SDR模式开关使能。 */
        unsigned int  ps_w_sdr_dec_clk_sel : 1;  /* bit[1]   : W SDR模式下译码时钟选择。0，译码采用122m时钟；1，译码采用245m时钟。 */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_PS_W_SDR_EN_UNION;
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_en_START           (0)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_en_END             (0)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_dec_clk_sel_START  (1)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_dec_clk_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TURBO_HD_JUDGE_EN_UNION
 结构说明  : TURBO_HD_JUDGE_EN 寄存器结构定义。地址偏移量:0x040，初值:0x00000010，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      turbo_hd_judge_en_reg;
    struct
    {
        unsigned int  c_tc_iter_over_en       : 1;  /* bit[0]   : Turbo译码器硬判比对提前停止迭代使能，默认使用CRC校验的提前停止方法
                                                                  0：禁止
                                                                  1：使能 */
        unsigned int  reserved_0              : 3;  /* bit[1-3] : 保留 */
        unsigned int  c_conv_judge_enhance_en : 1;  /* bit[4]   : turbo译码器通过硬判比对判断收敛方法的切换开关，默认打开
                                                                  0：比较连续两次的迭代处理结果，一致则认为收敛；
                                                                  1：比较连续三次的迭代处理结果，一致则认为收敛； */
        unsigned int  reserved_1              : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_TURBO_HD_JUDGE_EN_UNION;
#define BBPCOMM_TURBO_HD_JUDGE_EN_c_tc_iter_over_en_START        (0)
#define BBPCOMM_TURBO_HD_JUDGE_EN_c_tc_iter_over_en_END          (0)
#define BBPCOMM_TURBO_HD_JUDGE_EN_c_conv_judge_enhance_en_START  (4)
#define BBPCOMM_TURBO_HD_JUDGE_EN_c_conv_judge_enhance_en_END    (4)


/***======================================================================***
                     (3/3) register_define_glb_bbc
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_BBP_DUMP_DBG_MODE_UNION
 结构说明  : BBP_DUMP_DBG_MODE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbp_dump_dbg_mode_reg;
    struct
    {
        unsigned int  dump_data_mode  : 2;  /* bit[0-1] : bit[1]：0，表示采集GBBP1的数据；1，表示采集GBBP2的数据。
                                                          bit[0]：0，表示采集W数据；1表示采集G数据。现无意义，保留。 */
        unsigned int  debug_data_mode : 2;  /* bit[2-3] : bit[1]：0，表示采集GBBP1的数据；1，表示采集GBBP2的数据。现无意义，保留。
                                                          bit[0]：0，表示采集W数据；1表示采集G数据。现无意义，保留。 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBP_DUMP_DBG_MODE_UNION;
#define BBPCOMM_BBP_DUMP_DBG_MODE_dump_data_mode_START   (0)
#define BBPCOMM_BBP_DUMP_DBG_MODE_dump_data_mode_END     (1)
#define BBPCOMM_BBP_DUMP_DBG_MODE_debug_data_mode_START  (2)
#define BBPCOMM_BBP_DUMP_DBG_MODE_debug_data_mode_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_GU_SDR_EN_UNION
 结构说明  : GU_SDR_EN 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gu_sdr_en_reg;
    struct
    {
        unsigned int  g_sdr_en          : 1;  /* bit[0]   : GSDR模式开关使能。现无意义，保留。 */
        unsigned int  w_sdr_en          : 1;  /* bit[1]   : WSDR模式开关使能。现无意义，保留。 */
        unsigned int  w_sdr_dec_clk_sel : 1;  /* bit[2]   : WSDR模式下译码时钟选择。0，译码采用122m时钟；1，译码采用245m时钟。现无意义，保留。 */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_GU_SDR_EN_UNION;
#define BBPCOMM_GU_SDR_EN_g_sdr_en_START           (0)
#define BBPCOMM_GU_SDR_EN_g_sdr_en_END             (0)
#define BBPCOMM_GU_SDR_EN_w_sdr_en_START           (1)
#define BBPCOMM_GU_SDR_EN_w_sdr_en_END             (1)
#define BBPCOMM_GU_SDR_EN_w_sdr_dec_clk_sel_START  (2)
#define BBPCOMM_GU_SDR_EN_w_sdr_dec_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_CLK_GATE_BYPASS_UNION
 结构说明  : CPU_CLK_GATE_BYPASS 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_clk_gate_bypass_reg;
    struct
    {
        unsigned int  bbc_cpu_clk_gate_bypass       : 1;  /* bit[0]    : BBC_COMM CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  g1_cpu_clk_gate_bypass        : 1;  /* bit[1]    : GBBP_TOP1 CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  g2_cpu_clk_gate_bypass        : 1;  /* bit[2]    : GBBP_TOP2 CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  w1_cpu_clk_gate_bypass        : 1;  /* bit[3]    : WBBP_TOP1 CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  w2_cpu_clk_gate_bypass        : 1;  /* bit[4]    : WBBP_TOP2 CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  c_cpu_clk_gate_bypass         : 1;  /* bit[5]    : CBBP_TOP CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  wtc_share_cpu_clk_gate_bypass : 1;  /* bit[6]    : WTC_SHARE CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  r99w2_cpu_clk_gate_bypass     : 1;  /* bit[7]    : WBBP_R99 CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  c2_cpu_clk_gate_bypass        : 1;  /* bit[8]    : CBBP_TOP_2 CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  wc2_share_cpu_clk_gate_bypass : 1;  /* bit[9]    : UC2_SHARE CPU接口时钟自动门控BYPASS信号。 */
        unsigned int  reserved                      : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_CPU_CLK_GATE_BYPASS_UNION;
#define BBPCOMM_CPU_CLK_GATE_BYPASS_bbc_cpu_clk_gate_bypass_START        (0)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_bbc_cpu_clk_gate_bypass_END          (0)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_g1_cpu_clk_gate_bypass_START         (1)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_g1_cpu_clk_gate_bypass_END           (1)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_g2_cpu_clk_gate_bypass_START         (2)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_g2_cpu_clk_gate_bypass_END           (2)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_w1_cpu_clk_gate_bypass_START         (3)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_w1_cpu_clk_gate_bypass_END           (3)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_w2_cpu_clk_gate_bypass_START         (4)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_w2_cpu_clk_gate_bypass_END           (4)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_c_cpu_clk_gate_bypass_START          (5)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_c_cpu_clk_gate_bypass_END            (5)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_wtc_share_cpu_clk_gate_bypass_START  (6)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_wtc_share_cpu_clk_gate_bypass_END    (6)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_r99w2_cpu_clk_gate_bypass_START      (7)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_r99w2_cpu_clk_gate_bypass_END        (7)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_c2_cpu_clk_gate_bypass_START         (8)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_c2_cpu_clk_gate_bypass_END           (8)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_wc2_share_cpu_clk_gate_bypass_START  (9)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_wc2_share_cpu_clk_gate_bypass_END    (9)


/*****************************************************************************
 结构名    : BBPCOMM_CDMA_GPS_SYNC_SEL_UNION
 结构说明  : CDMA_GPS_SYNC_SEL 寄存器结构定义。地址偏移量:0x000C，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cdma_gps_sync_sel_reg;
    struct
    {
        unsigned int  cdma_gps_sync_sel : 1;  /* bit[0]   : CDMA GPS同步信号选择。0，选择CBBP_TOP输出的GPS同步信号；1，选择CBBP_TOP_2输出的GPS同步信号。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CDMA_GPS_SYNC_SEL_UNION;
#define BBPCOMM_CDMA_GPS_SYNC_SEL_cdma_gps_sync_sel_START  (0)
#define BBPCOMM_CDMA_GPS_SYNC_SEL_cdma_gps_sync_sel_END    (0)




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

#endif /* end of bbp_comm_interface.h */
