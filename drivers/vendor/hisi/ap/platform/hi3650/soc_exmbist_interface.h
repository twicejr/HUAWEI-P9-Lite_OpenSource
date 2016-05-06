/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_exmbist_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:33
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_EXMBIST.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_EXMBIST_INTERFACE_H__
#define __SOC_EXMBIST_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_exmbist
 ****************************************************************************/
/* 寄存器说明：配置CMD寄存器
   位域定义UNION结构:  SOC_EXMBIST_CMD_ADDR_UNION */
#define SOC_EXMBIST_CMD_ADDR_ADDR(base)               ((base) + (0x0000))

/* 寄存器说明：CMD携带的数据信息
   位域定义UNION结构:  SOC_EXMBIST_DAT_ADDR_UNION */
#define SOC_EXMBIST_DAT_ADDR_ADDR(base)               ((base) + (0x0004))

/* 寄存器说明：exmbist使能寄存器
   位域定义UNION结构:  SOC_EXMBIST_EN_UNION */
#define SOC_EXMBIST_EN_ADDR(base)                     ((base) + (0x0008))

/* 寄存器说明：时钟门控寄存器
   位域定义UNION结构:  SOC_EXMBIST_CLKEN0_UNION */
#define SOC_EXMBIST_CLKEN0_ADDR(base)                 ((base) + (0x000C))

/* 寄存器说明：时钟门控寄存器
   位域定义UNION结构:  SOC_EXMBIST_CLKEN1_UNION */
#define SOC_EXMBIST_CLKEN1_ADDR(base)                 ((base) + (0x0010))

/* 寄存器说明：MUX选择寄存器
   位域定义UNION结构:  SOC_EXMBIST_MUX_SEL_UNION */
#define SOC_EXMBIST_MUX_SEL_ADDR(base)                ((base) + (0x0014))

/* 寄存器说明：读写outstanding水线控制寄存器
   位域定义UNION结构:  SOC_EXMBIST_OTS_LINE_UNION */
#define SOC_EXMBIST_OTS_LINE_ADDR(base)               ((base) + (0x0018))

/* 寄存器说明：安全操作使能
   位域定义UNION结构:  SOC_EXMBIST_SECUER_EN_UNION */
#define SOC_EXMBIST_SECUER_EN_ADDR(base)              ((base) + (0x001C))

/* 寄存器说明：读写QOS配置寄存器
   位域定义UNION结构:  SOC_EXMBIST_QOS_UNION */
#define SOC_EXMBIST_QOS_ADDR(base)                    ((base) + (0x0020))

/* 寄存器说明：命令合并配置寄存器
   位域定义UNION结构:  SOC_EXMBIST_CMD_MERGE_UNION */
#define SOC_EXMBIST_CMD_MERGE_ADDR(base)              ((base) + (0x0024))

/* 寄存器说明：控制的每个RANK的DDR容量配置寄存器。
   位域定义UNION结构:  SOC_EXMBIST_RANK_VOL_UNION */
#define SOC_EXMBIST_RANK_VOL_ADDR(base, i)            ((base) + (0x0028+0x4*(i)))

/* 寄存器说明：EXMBIST当前扫描的rank配置寄存器
   位域定义UNION结构:  SOC_EXMBIST_TEST_RANK_UNION */
#define SOC_EXMBIST_TEST_RANK_ADDR(base)              ((base) + (0x0048))

/* 寄存器说明：对接DDR颗粒的位宽配置寄存器
   位域定义UNION结构:  SOC_EXMBIST_DRAM_WIDTH_UNION */
#define SOC_EXMBIST_DRAM_WIDTH_ADDR(base)             ((base) + (0x004C))

/* 寄存器说明：DDR CHAN信息配置寄存器
   位域定义UNION结构:  SOC_EXMBIST_CHAN_INFO_UNION */
#define SOC_EXMBIST_CHAN_INFO_ADDR(base)              ((base) + (0x0050))

/* 寄存器说明：地址交织模式
   位域定义UNION结构:  SOC_EXMBIST_ADDR_INTLV_UNION */
#define SOC_EXMBIST_ADDR_INTLV_ADDR(base)             ((base) + (0x0054))

/* 寄存器说明：EXMBIST模块的状态输出寄存器
   位域定义UNION结构:  SOC_EXMBIST_STATUS_UNION */
#define SOC_EXMBIST_STATUS_ADDR(base)                 ((base) + (0x0058))

/* 寄存器说明：DFX信息寄存器
   位域定义UNION结构:  SOC_EXMBIST_DFX_INFO_UNION */
#define SOC_EXMBIST_DFX_INFO_ADDR(base)               ((base) + (0x005C))

/* 寄存器说明：pclk静态时钟门控
   位域定义UNION结构:  SOC_EXMBIST_PCLK_GATE_UNION */
#define SOC_EXMBIST_PCLK_GATE_ADDR(base)              ((base) + (0x0060))

/* 寄存器说明：mem_ctrl寄存器
   位域定义UNION结构:  SOC_EXMBIST_MEM_CTRL_UNION */
#define SOC_EXMBIST_MEM_CTRL_ADDR(base)               ((base) + (0x0064))

/* 寄存器说明：通用控制寄存器0
   位域定义UNION结构:  SOC_EXMBIST_COMMON_CTRL0_UNION */
#define SOC_EXMBIST_COMMON_CTRL0_ADDR(base)           ((base) + (0x0068))

/* 寄存器说明：通用控制寄存器1
   位域定义UNION结构:  SOC_EXMBIST_COMMON_CTRL1_UNION */
#define SOC_EXMBIST_COMMON_CTRL1_ADDR(base)           ((base) + (0x006C))

/* 寄存器说明：通用控制寄存器2
   位域定义UNION结构:  SOC_EXMBIST_COMMON_CTRL2_UNION */
#define SOC_EXMBIST_COMMON_CTRL2_ADDR(base)           ((base) + (0x0070))

/* 寄存器说明：通用控制寄存器3
   位域定义UNION结构:  SOC_EXMBIST_COMMON_CTRL3_UNION */
#define SOC_EXMBIST_COMMON_CTRL3_ADDR(base)           ((base) + (0x0074))

/* 寄存器说明：读写mid配置寄存器
   位域定义UNION结构:  SOC_EXMBIST_RW_MID_UNION */
#define SOC_EXMBIST_RW_MID_ADDR(base)                 ((base) + (0x0078))





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
                     (1/1) register_exmbist
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_EXMBIST_CMD_ADDR_UNION
 结构说明  : CMD_ADDR 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 配置CMD寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_info      : 8;  /* bit[0-7] : 读或写含义区分：
                                                        写寄存器：指示需要配置的cmd指令。具体指令号请参考EXMBIST FS文档。
                                                        读寄存器：相应读指令的输出数据； */
        unsigned int  data_info_cmd : 24; /* bit[8-31]: 读或写含义区分：
                                                        写寄存器：当cmd携带的数据信息小于等于24bit时，此域段为cmd指令所携带的数据信息；当cmd携带的数据信息大于24bit，cmd携带的数据信息由0x0004寄存器输入，此域段无效；
                                                        读寄存器：相应读指令的输出数据； */
    } reg;
} SOC_EXMBIST_CMD_ADDR_UNION;
#endif
#define SOC_EXMBIST_CMD_ADDR_cmd_info_START       (0)
#define SOC_EXMBIST_CMD_ADDR_cmd_info_END         (7)
#define SOC_EXMBIST_CMD_ADDR_data_info_cmd_START  (8)
#define SOC_EXMBIST_CMD_ADDR_data_info_cmd_END    (31)


/*****************************************************************************
 结构名    : SOC_EXMBIST_DAT_ADDR_UNION
 结构说明  : DAT_ADDR 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: CMD携带的数据信息
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_info : 32; /* bit[0-31]: 当cmd携带的数据信息大于24bit，此寄存器用于辅助输入数据信息，对应于EXMBIST中的DIN输入端口。 */
    } reg;
} SOC_EXMBIST_DAT_ADDR_UNION;
#endif
#define SOC_EXMBIST_DAT_ADDR_data_info_START  (0)
#define SOC_EXMBIST_DAT_ADDR_data_info_END    (31)


/*****************************************************************************
 结构名    : SOC_EXMBIST_EN_UNION
 结构说明  : EN 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: exmbist使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_exmbist_en : 1;  /* bit[0]   : exmbist使能寄存器。
                                                         0：关闭exmbist；
                                                         1：使能exmbist； */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_EXMBIST_EN_UNION;
#endif
#define SOC_EXMBIST_EN_cfg_exmbist_en_START  (0)
#define SOC_EXMBIST_EN_cfg_exmbist_en_END    (0)


/*****************************************************************************
 结构名    : SOC_EXMBIST_CLKEN0_UNION
 结构说明  : CLKEN0 寄存器结构定义。地址偏移量:0x000C，初值:0x0000FFFF，宽度:32
 寄存器说明: 时钟门控寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_clk_en_0        : 1;  /* bit[0]    : DMC0时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  dmc_clk_en_1        : 1;  /* bit[1]    : DMC1时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  rdr_clk_en_0        : 1;  /* bit[2]    : RBUFFER0时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  apb_clken_0         : 1;  /* bit[3]    : DDRC0 APB时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  dmc_clk_en_2        : 1;  /* bit[4]    : DMC2时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  dmc_clk_en_3        : 1;  /* bit[5]    : DMC3时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  rdr_clk_en_1        : 1;  /* bit[6]    : RBUFFER1时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  apb_clken_1         : 1;  /* bit[7]    : DDRC1 APB时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  reserved_0          : 1;  /* bit[8]    : 保留 */
        unsigned int  brg_ivp_clk_en      : 1;  /* bit[9]    : ivp接口异步桥时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  exmbist_wrap_clk_en : 1;  /* bit[10]   : exmbist_wrap时钟门控使能：
                                                               0：关闭该模块的时钟；
                                                               1：使能该模块的时钟； */
        unsigned int  reserved_1          : 5;  /* bit[11-15]: 保留 */
        unsigned int  clk_wr_en           : 16; /* bit[16-31]: clk_en每个bit的使能位。
                                                               只有当clk_wr_en对应的bit为1'b1，clk_en相应的bit才能配置。
                                                               clk_wr_en[31:16]与clk_en[15:0]每一bit为一一对应关系 */
    } reg;
} SOC_EXMBIST_CLKEN0_UNION;
#endif
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_0_START         (0)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_0_END           (0)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_1_START         (1)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_1_END           (1)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_0_START         (2)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_0_END           (2)
#define SOC_EXMBIST_CLKEN0_apb_clken_0_START          (3)
#define SOC_EXMBIST_CLKEN0_apb_clken_0_END            (3)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_2_START         (4)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_2_END           (4)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_3_START         (5)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_3_END           (5)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_1_START         (6)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_1_END           (6)
#define SOC_EXMBIST_CLKEN0_apb_clken_1_START          (7)
#define SOC_EXMBIST_CLKEN0_apb_clken_1_END            (7)
#define SOC_EXMBIST_CLKEN0_brg_ivp_clk_en_START       (9)
#define SOC_EXMBIST_CLKEN0_brg_ivp_clk_en_END         (9)
#define SOC_EXMBIST_CLKEN0_exmbist_wrap_clk_en_START  (10)
#define SOC_EXMBIST_CLKEN0_exmbist_wrap_clk_en_END    (10)
#define SOC_EXMBIST_CLKEN0_clk_wr_en_START            (16)
#define SOC_EXMBIST_CLKEN0_clk_wr_en_END              (31)


/*****************************************************************************
 结构名    : SOC_EXMBIST_CLKEN1_UNION
 结构说明  : CLKEN1 寄存器结构定义。地址偏移量:0x0010，初值:0x0000FFFF，宽度:32
 寄存器说明: 时钟门控寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pack_clk_en_0     : 1;  /* bit[0]    : PACK0时钟门控使能：
                                                             0：关闭该模块的时钟；
                                                             1：使能该模块的时钟； */
        unsigned int  pack_apb_clk_en_0 : 1;  /* bit[1]    : PACK0 APB时钟门控使能：
                                                             0：关闭该模块的时钟；
                                                             1：使能该模块的时钟； */
        unsigned int  pack_clk_en_1     : 1;  /* bit[2]    : PACK1时钟门控使能：
                                                             0：关闭该模块的时钟；
                                                             1：使能该模块的时钟； */
        unsigned int  pack_apb_clk_en_1 : 1;  /* bit[3]    : PACK1 APB时钟门控使能：
                                                             0：关闭该模块的时钟；
                                                             1：使能该模块的时钟； */
        unsigned int  pack_clk_en_2     : 1;  /* bit[4]    : PACK2时钟门控使能：
                                                             0：关闭该模块的时钟；
                                                             1：使能该模块的时钟； */
        unsigned int  pack_apb_clk_en_2 : 1;  /* bit[5]    : PACK2 APB时钟门控使能：
                                                             0：关闭该模块的时钟；
                                                             1：使能该模块的时钟； */
        unsigned int  pack_clk_en_3     : 1;  /* bit[6]    : PACK3时钟门控使能：
                                                             0：关闭该模块的时钟；
                                                             1：使能该模块的时钟； */
        unsigned int  pack_apb_clk_en_3 : 1;  /* bit[7]    : PACK3 APB时钟门控使能：
                                                             0：关闭该模块的时钟；
                                                             1：使能该模块的时钟； */
        unsigned int  reserved          : 8;  /* bit[8-15] : 保留 */
        unsigned int  clk_wr_en         : 16; /* bit[16-31]: clk_en每个bit的使能位。
                                                             只有当clk_wr_en对应的bit为1'b1，clk_en相应的bit才能配置。
                                                             clk_wr_en[31:16]与clk_en[15:0]每一bit为一一对应关系 */
    } reg;
} SOC_EXMBIST_CLKEN1_UNION;
#endif
#define SOC_EXMBIST_CLKEN1_pack_clk_en_0_START      (0)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_0_END        (0)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_0_START  (1)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_0_END    (1)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_1_START      (2)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_1_END        (2)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_1_START  (3)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_1_END    (3)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_2_START      (4)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_2_END        (4)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_2_START  (5)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_2_END    (5)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_3_START      (6)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_3_END        (6)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_3_START  (7)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_3_END    (7)
#define SOC_EXMBIST_CLKEN1_clk_wr_en_START          (16)
#define SOC_EXMBIST_CLKEN1_clk_wr_en_END            (31)


/*****************************************************************************
 结构名    : SOC_EXMBIST_MUX_SEL_UNION
 结构说明  : MUX_SEL 寄存器结构定义。地址偏移量:0x0014，初值:0x00000001，宽度:32
 寄存器说明: MUX选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mux_sel  : 1;  /* bit[0]   : mux选择寄存器。
                                                   0：选择EXMBIST WRAP的AXI_MST口从MUX输出；
                                                   1：选择IVP的AXI_MST口从MUX输出； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_EXMBIST_MUX_SEL_UNION;
#endif
#define SOC_EXMBIST_MUX_SEL_mux_sel_START   (0)
#define SOC_EXMBIST_MUX_SEL_mux_sel_END     (0)


/*****************************************************************************
 结构名    : SOC_EXMBIST_OTS_LINE_UNION
 结构说明  : OTS_LINE 寄存器结构定义。地址偏移量:0x0018，初值:0x003F003F，宽度:32
 寄存器说明: 读写outstanding水线控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_wr_ots_line : 6;  /* bit[0-5]  : 写操作outstanding水线，outstanding最大值为64，当配置值大于64时，以64为准。
                                                           当配置值为0时，写操作将被限制，无法下发写操作。 */
        unsigned int  reserved_0      : 10; /* bit[6-15] : 保留 */
        unsigned int  cfg_rd_ots_line : 6;  /* bit[16-21]: 读操作outstanding水线，outstanding最大值为64，当配置值大于64时，以64为准。
                                                           当配置值为0时，读操作将被限制，无法下发读操作。 */
        unsigned int  reserved_1      : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_EXMBIST_OTS_LINE_UNION;
#endif
#define SOC_EXMBIST_OTS_LINE_cfg_wr_ots_line_START  (0)
#define SOC_EXMBIST_OTS_LINE_cfg_wr_ots_line_END    (5)
#define SOC_EXMBIST_OTS_LINE_cfg_rd_ots_line_START  (16)
#define SOC_EXMBIST_OTS_LINE_cfg_rd_ots_line_END    (21)


/*****************************************************************************
 结构名    : SOC_EXMBIST_SECUER_EN_UNION
 结构说明  : SECUER_EN 寄存器结构定义。地址偏移量:0x001C，初值:0x00000001，宽度:32
 寄存器说明: 安全操作使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_secure_en : 1;  /* bit[0]   : 安全操作使能位：
                                                        0：从axi发出的操作均为安全操作；
                                                        1:从axi发出的操作均为非安全操作；
                                                        注意：改写该寄存器需要安全属性访问，读该寄存器没有属性要求； */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_EXMBIST_SECUER_EN_UNION;
#endif
#define SOC_EXMBIST_SECUER_EN_cfg_secure_en_START  (0)
#define SOC_EXMBIST_SECUER_EN_cfg_secure_en_END    (0)


/*****************************************************************************
 结构名    : SOC_EXMBIST_QOS_UNION
 结构说明  : QOS 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 读写QOS配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_rd_qos : 4;  /* bit[0-3]  : 读操作的QoS值。 
                                                      0x0～0xF：QoS对应为0~15，0为最低，15为最高。 */
        unsigned int  reserved_0 : 12; /* bit[4-15] : 保留 */
        unsigned int  cfg_wr_qos : 4;  /* bit[16-19]: 写操作的QoS值。 
                                                      0x0～0xF：QoS对应为0~15，0为最低，15为最高。 */
        unsigned int  reserved_1 : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_EXMBIST_QOS_UNION;
#endif
#define SOC_EXMBIST_QOS_cfg_rd_qos_START  (0)
#define SOC_EXMBIST_QOS_cfg_rd_qos_END    (3)
#define SOC_EXMBIST_QOS_cfg_wr_qos_START  (16)
#define SOC_EXMBIST_QOS_cfg_wr_qos_END    (19)


/*****************************************************************************
 结构名    : SOC_EXMBIST_CMD_MERGE_UNION
 结构说明  : CMD_MERGE 寄存器结构定义。地址偏移量:0x0024，初值:0x0000000E，宽度:32
 寄存器说明: 命令合并配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_cmd_merge_bypass : 1;  /* bit[0]   : merge功能bypass开关：
                                                               0：关闭merge bypass功能
                                                               1：使能merge bypass功能 */
        unsigned int  cfg_cmd_wait_timeout : 3;  /* bit[1-3] : 对命令进行合并的超时配置。
                                                               当打拍逻辑rs中存在一拍数据，但此时cmd fifo已经为空，那么将等待一段时间，如果没有超出等待时间，从cmd fifo中过来的命令仍然可以拼接；如果超过等待时间，将不再与后面的命令进行拼接。其中，cfg_cmd_wait_timeout即为等待的cycle数。 */
        unsigned int  reserved             : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_EXMBIST_CMD_MERGE_UNION;
#endif
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_merge_bypass_START  (0)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_merge_bypass_END    (0)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_wait_timeout_START  (1)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_wait_timeout_END    (3)


/*****************************************************************************
 结构名    : SOC_EXMBIST_RANK_VOL_UNION
 结构说明  : RANK_VOL 寄存器结构定义。地址偏移量:0x0028+0x4*(i)，初值:0x00000012，宽度:32
 寄存器说明: 控制的每个RANK的DDR容量配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_col_bit  : 3;  /* bit[0-2] : 单片SDRAM列地址位宽配置。
                                                       000：8 bit；
                                                       001：9 bit；
                                                       010：10 bit；
                                                       011：11 bit；
                                                       100：12 bit；
                                                       其它保留。 */
        unsigned int  cfg_row_bit  : 3;  /* bit[3-5] : 单片SDRAM行地址位宽配置。
                                                       000：11 bit；
                                                       001：12 bit；
                                                       010：13 bit；
                                                       011：14 bit；
                                                       100：15 bit；
                                                       101：16 bit；
                                                       110: 17 bit；
                                                       111: 18 bit； */
        unsigned int  cfg_bank_bit : 2;  /* bit[6-7] : 单片SDRAM Bank数。
                                                       00：2bit；
                                                       01：3bit；
                                                       10：4bit；
                                                       11：保留。
                                                       注意：对于DDR4，这里是配置成所有bank group中的bank之和。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_EXMBIST_RANK_VOL_UNION;
#endif
#define SOC_EXMBIST_RANK_VOL_cfg_col_bit_START   (0)
#define SOC_EXMBIST_RANK_VOL_cfg_col_bit_END     (2)
#define SOC_EXMBIST_RANK_VOL_cfg_row_bit_START   (3)
#define SOC_EXMBIST_RANK_VOL_cfg_row_bit_END     (5)
#define SOC_EXMBIST_RANK_VOL_cfg_bank_bit_START  (6)
#define SOC_EXMBIST_RANK_VOL_cfg_bank_bit_END    (7)


/*****************************************************************************
 结构名    : SOC_EXMBIST_TEST_RANK_UNION
 结构说明  : TEST_RANK 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: EXMBIST当前扫描的rank配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_test_rank : 3;  /* bit[0-2] : 当前扫描的rank。
                                                        000：选择扫描rank0；
                                                        001：选择扫描rank1；
                                                        010：选择扫描rank2；
                                                        011：选择扫描rank3；
                                                        100：选择扫描rank4；
                                                        101：选择扫描rank5；
                                                        110：选择扫描rank6；
                                                        111：选择扫描rank7； */
        unsigned int  reserved      : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_EXMBIST_TEST_RANK_UNION;
#endif
#define SOC_EXMBIST_TEST_RANK_cfg_test_rank_START  (0)
#define SOC_EXMBIST_TEST_RANK_cfg_test_rank_END    (2)


/*****************************************************************************
 结构名    : SOC_EXMBIST_DRAM_WIDTH_UNION
 结构说明  : DRAM_WIDTH 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 对接DDR颗粒的位宽配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_dram_width : 1;  /* bit[0]   : 对接的DDR颗粒类型。
                                                         0:对接DDR颗粒位宽为16；
                                                         1：对接DDR颗粒的位宽为32； */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_EXMBIST_DRAM_WIDTH_UNION;
#endif
#define SOC_EXMBIST_DRAM_WIDTH_cfg_dram_width_START  (0)
#define SOC_EXMBIST_DRAM_WIDTH_cfg_dram_width_END    (0)


/*****************************************************************************
 结构名    : SOC_EXMBIST_CHAN_INFO_UNION
 结构说明  : CHAN_INFO 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: DDR CHAN信息配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_chan_type : 1;  /* bit[0]   : 对接DDR为双通道或者四通道。
                                                        0：对接DDR为双通道；
                                                        1：对接DDR为四通道； */
        unsigned int  cfg_test_chan : 2;  /* bit[1-2] : 当前选择扫描的channel。
                                                        00：选择channel 0；
                                                        01：选择channel 1；
                                                        10：选择channel 2；
                                                        11：选择channel 3； */
        unsigned int  reserved      : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_EXMBIST_CHAN_INFO_UNION;
#endif
#define SOC_EXMBIST_CHAN_INFO_cfg_chan_type_START  (0)
#define SOC_EXMBIST_CHAN_INFO_cfg_chan_type_END    (0)
#define SOC_EXMBIST_CHAN_INFO_cfg_test_chan_START  (1)
#define SOC_EXMBIST_CHAN_INFO_cfg_test_chan_END    (2)


/*****************************************************************************
 结构名    : SOC_EXMBIST_ADDR_INTLV_UNION
 结构说明  : ADDR_INTLV 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 地址交织模式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_intlv_gran : 3;  /* bit[0-2] : 地址交织粒度：
                                                         0x0：128Byte；
                                                         0x1：256Byte；
                                                         0x2：512Byte；
                                                         0x3：1KByte；
                                                         0x4：2KByte；
                                                         0x5：4KByte；
                                                         注意：地址交织粒度必须与DMSS模块配置相同，该模式决定了channel地址的地址映射。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_EXMBIST_ADDR_INTLV_UNION;
#endif
#define SOC_EXMBIST_ADDR_INTLV_cfg_intlv_gran_START  (0)
#define SOC_EXMBIST_ADDR_INTLV_cfg_intlv_gran_END    (2)


/*****************************************************************************
 结构名    : SOC_EXMBIST_STATUS_UNION
 结构说明  : STATUS 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: EXMBIST模块的状态输出寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bist_done      : 1;  /* bit[0]    : 表示EXMBIST的工作状态。
                                                          1 : current execution finished, 
                                                          0 : current execution in progress */
        unsigned int  bist_pass      : 1;  /* bit[1]    : Bist操作结果是否正确。
                                                          1 : test passes, no errors found, 
                                                          0 : found errors */
        unsigned int  reserved_0     : 2;  /* bit[2-3]  : 保留 */
        unsigned int  parity_error   : 1;  /* bit[4]    : 保留 */
        unsigned int  watchdog_error : 1;  /* bit[5]    : watchdog状态指示。
                                                          1 : watchdog error fired, 
                                                          0 : not fired */
        unsigned int  diag_fifo_last : 1;  /* bit[6]    : Diag_fifo的状态指示。
                                                          1 ： have reached the last element in the DIAG FIFO
                                                          0 ： not yet */
        unsigned int  reserved_1     : 1;  /* bit[7]    : 保留 */
        unsigned int  diag_ip        : 3;  /* bit[8-10] : Instruction # that catches the current fault (saved in the Diag FIFO) */
        unsigned int  reserved_2     : 1;  /* bit[11]   : 保留 */
        unsigned int  fingerprint    : 4;  /* bit[12-15]: tie to 4’b0101, used for sanity check */
        unsigned int  iter_cnt       : 16; /* bit[16-31]: # of iterations that have been executed, meaningful when cfg_loop_en=1 */
    } reg;
} SOC_EXMBIST_STATUS_UNION;
#endif
#define SOC_EXMBIST_STATUS_bist_done_START       (0)
#define SOC_EXMBIST_STATUS_bist_done_END         (0)
#define SOC_EXMBIST_STATUS_bist_pass_START       (1)
#define SOC_EXMBIST_STATUS_bist_pass_END         (1)
#define SOC_EXMBIST_STATUS_parity_error_START    (4)
#define SOC_EXMBIST_STATUS_parity_error_END      (4)
#define SOC_EXMBIST_STATUS_watchdog_error_START  (5)
#define SOC_EXMBIST_STATUS_watchdog_error_END    (5)
#define SOC_EXMBIST_STATUS_diag_fifo_last_START  (6)
#define SOC_EXMBIST_STATUS_diag_fifo_last_END    (6)
#define SOC_EXMBIST_STATUS_diag_ip_START         (8)
#define SOC_EXMBIST_STATUS_diag_ip_END           (10)
#define SOC_EXMBIST_STATUS_fingerprint_START     (12)
#define SOC_EXMBIST_STATUS_fingerprint_END       (15)
#define SOC_EXMBIST_STATUS_iter_cnt_START        (16)
#define SOC_EXMBIST_STATUS_iter_cnt_END          (31)


/*****************************************************************************
 结构名    : SOC_EXMBIST_DFX_INFO_UNION
 结构说明  : DFX_INFO 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: DFX信息寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_fifo_empty   : 1;  /* bit[0]    : cmd fifo空状态。
                                                            0：cmd fifo为非空；
                                                            1：cmd fifo为空； */
        unsigned int  wdata_fifo_empty : 1;  /* bit[1]    : wdata fifo空状态。
                                                            0：wdata fifo为非空；
                                                            1：wdata fifo为空； */
        unsigned int  cnt_fifo_empty   : 1;  /* bit[2]    : cnt fifo空状态。
                                                            0：cnt fifo为非空；
                                                            1：cnt fifo为空； */
        unsigned int  cmd_fifo_full    : 1;  /* bit[3]    : cmd fifo满状态。
                                                            0：cmd fifo为非满；
                                                            1：cmd fifo为满； */
        unsigned int  wdata_fifo_full  : 1;  /* bit[4]    : wdata fifo满状态。
                                                            0：wdata fifo为非满；
                                                            1：wdata fifo为满； */
        unsigned int  cnt_fifo_full    : 1;  /* bit[5]    : cnt fifo满状态。
                                                            0：cnt fifo为非满；
                                                            1：cnt fifo为满； */
        unsigned int  wr_ots_cnt       : 6;  /* bit[6-11] : 当前还未返回bresp的写操作。 */
        unsigned int  rd_ots_cnt       : 6;  /* bit[12-17]: 当前还未返回rresp的读操作。 */
        unsigned int  reserved         : 14; /* bit[18-31]: 保留 */
    } reg;
} SOC_EXMBIST_DFX_INFO_UNION;
#endif
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_empty_START    (0)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_empty_END      (0)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_empty_START  (1)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_empty_END    (1)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_empty_START    (2)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_empty_END      (2)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_full_START     (3)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_full_END       (3)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_full_START   (4)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_full_END     (4)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_full_START     (5)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_full_END       (5)
#define SOC_EXMBIST_DFX_INFO_wr_ots_cnt_START        (6)
#define SOC_EXMBIST_DFX_INFO_wr_ots_cnt_END          (11)
#define SOC_EXMBIST_DFX_INFO_rd_ots_cnt_START        (12)
#define SOC_EXMBIST_DFX_INFO_rd_ots_cnt_END          (17)


/*****************************************************************************
 结构名    : SOC_EXMBIST_PCLK_GATE_UNION
 结构说明  : PCLK_GATE 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: pclk静态时钟门控
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_gt_en : 1;  /* bit[0]   : pclk时钟静态时钟门控：
                                                    0：关闭pclk时钟；
                                                    1：开启pclk时钟； */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_EXMBIST_PCLK_GATE_UNION;
#endif
#define SOC_EXMBIST_PCLK_GATE_apb_gt_en_START  (0)
#define SOC_EXMBIST_PCLK_GATE_apb_gt_en_END    (0)


/*****************************************************************************
 结构名    : SOC_EXMBIST_MEM_CTRL_UNION
 结构说明  : MEM_CTRL 寄存器结构定义。地址偏移量:0x0064，初值:0x000001A8，宽度:32
 寄存器说明: mem_ctrl寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slp      : 1;  /* bit[0]    :  */
        unsigned int  dslp     : 1;  /* bit[1]    :  */
        unsigned int  sd       : 1;  /* bit[2]    :  */
        unsigned int  rct      : 2;  /* bit[3-4]  :  */
        unsigned int  wct      : 2;  /* bit[5-6]  :  */
        unsigned int  kp       : 3;  /* bit[7-9]  :  */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  reserved_1: 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_EXMBIST_MEM_CTRL_UNION;
#endif
#define SOC_EXMBIST_MEM_CTRL_slp_START       (0)
#define SOC_EXMBIST_MEM_CTRL_slp_END         (0)
#define SOC_EXMBIST_MEM_CTRL_dslp_START      (1)
#define SOC_EXMBIST_MEM_CTRL_dslp_END        (1)
#define SOC_EXMBIST_MEM_CTRL_sd_START        (2)
#define SOC_EXMBIST_MEM_CTRL_sd_END          (2)
#define SOC_EXMBIST_MEM_CTRL_rct_START       (3)
#define SOC_EXMBIST_MEM_CTRL_rct_END         (4)
#define SOC_EXMBIST_MEM_CTRL_wct_START       (5)
#define SOC_EXMBIST_MEM_CTRL_wct_END         (6)
#define SOC_EXMBIST_MEM_CTRL_kp_START        (7)
#define SOC_EXMBIST_MEM_CTRL_kp_END          (9)


/*****************************************************************************
 结构名    : SOC_EXMBIST_COMMON_CTRL0_UNION
 结构说明  : COMMON_CTRL0 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 通用控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_clk_ddrphy_rs                : 4;  /* bit[0-3]  : 各级RS的时钟正反沿配置。
                                                                            0：正常时钟；
                                                                            1：反相时钟； */
        unsigned int  sel_clk_ddrphy_rsperi            : 1;  /* bit[4]    : LPDDR3专用RS的时钟正反沿配置。
                                                                            0：正常时钟；
                                                                            1：反相时钟； */
        unsigned int  sel_clk_ddrphy_in                : 1;  /* bit[5]    : DDRPHY的时钟正反沿配置。
                                                                            0：正常时钟；
                                                                            1：反相时钟； */
        unsigned int  reserved                         : 2;  /* bit[6-7]  : 保留 */
        unsigned int  ddrphy_rs_passthrough            : 4;  /* bit[8-11] : 各级RS的bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  ddrphy_rs_rst_passthrough        : 4;  /* bit[12-15]: 各级RS的rst bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  ddrphy_rs_rstcont_passthrough    : 4;  /* bit[16-19]: 各级RS的rstcont bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  rs_passthrough                   : 1;  /* bit[20]   : LPDDR3专用RS的bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  rs_rst_passthrough               : 1;  /* bit[21]   : LPDDR3专用RS的rst bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  rs_rstcont_passthrough           : 1;  /* bit[22]   : LPDDR3专用RS的rstcont bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  ddrphy_rs_rx_passthrough         : 4;  /* bit[23-26]: 各级RS的RX通路bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效；； */
        unsigned int  rs_rx_passthrough                : 1;  /* bit[27]   : LPDDR3专用RS的RX通路bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  ddrphy_rs_passthroug_add         : 1;  /* bit[28]   : 新增一级（第4级）RS的bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  ddrphy_rs_rst_passthroug_add     : 1;  /* bit[29]   : 新增一级（第4级）RS的rst bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效；； */
        unsigned int  ddrphy_rs_rstcont_passthroug_add : 1;  /* bit[30]   : 新增一级（第4级）RS的rstcont bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
        unsigned int  ddrphy_rs_rx_passthroug_add      : 1;  /* bit[31]   : 新增一级（第4级）RS的RX通路bypass配置。
                                                                            1：RS pass through；
                                                                            0：RS有效； */
    } reg;
} SOC_EXMBIST_COMMON_CTRL0_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rs_START                 (0)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rs_END                   (3)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rsperi_START             (4)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rsperi_END               (4)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_in_START                 (5)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_in_END                   (5)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_passthrough_START             (8)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_passthrough_END               (11)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rst_passthrough_START         (12)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rst_passthrough_END           (15)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rstcont_passthrough_START     (16)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rstcont_passthrough_END       (19)
#define SOC_EXMBIST_COMMON_CTRL0_rs_passthrough_START                    (20)
#define SOC_EXMBIST_COMMON_CTRL0_rs_passthrough_END                      (20)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rst_passthrough_START                (21)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rst_passthrough_END                  (21)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rstcont_passthrough_START            (22)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rstcont_passthrough_END              (22)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rx_passthrough_START          (23)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rx_passthrough_END            (26)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rx_passthrough_START                 (27)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rx_passthrough_END                   (27)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_passthroug_add_START          (28)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_passthroug_add_END            (28)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rst_passthroug_add_START      (29)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rst_passthroug_add_END        (29)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rstcont_passthroug_add_START  (30)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rstcont_passthroug_add_END    (30)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rx_passthroug_add_START       (31)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rx_passthroug_add_END         (31)


/*****************************************************************************
 结构名    : SOC_EXMBIST_COMMON_CTRL1_UNION
 结构说明  : COMMON_CTRL1 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 通用控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pack_apb_deadlock_avoid : 1;  /* bit[0]   : PACK时钟门控后的防挂死功能bypass。
                                                                  0：打开防挂死功能；
                                                                  1：禁用防挂死功能； */
        unsigned int  reserved_0              : 7;  /* bit[1-7] : 保留 */
        unsigned int  sel_clk_ddrphy_rs_add   : 1;  /* bit[8]   : 新增一级（第4级）RS的时钟正反沿配置。
                                                                  0：正常时钟；
                                                                  1：反相时钟； */
        unsigned int  reserved_1              : 23; /* bit[9-31]: 保留 */
    } reg;
} SOC_EXMBIST_COMMON_CTRL1_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL1_pack_apb_deadlock_avoid_START  (0)
#define SOC_EXMBIST_COMMON_CTRL1_pack_apb_deadlock_avoid_END    (0)
#define SOC_EXMBIST_COMMON_CTRL1_sel_clk_ddrphy_rs_add_START    (8)
#define SOC_EXMBIST_COMMON_CTRL1_sel_clk_ddrphy_rs_add_END      (8)


/*****************************************************************************
 结构名    : SOC_EXMBIST_COMMON_CTRL2_UNION
 结构说明  : COMMON_CTRL2 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 通用控制寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  common_ctrl2 : 32; /* bit[0-31]:  */
    } reg;
} SOC_EXMBIST_COMMON_CTRL2_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL2_common_ctrl2_START  (0)
#define SOC_EXMBIST_COMMON_CTRL2_common_ctrl2_END    (31)


/*****************************************************************************
 结构名    : SOC_EXMBIST_COMMON_CTRL3_UNION
 结构说明  : COMMON_CTRL3 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 通用控制寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  common_ctrl3 : 32; /* bit[0-31]:  */
    } reg;
} SOC_EXMBIST_COMMON_CTRL3_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL3_common_ctrl3_START  (0)
#define SOC_EXMBIST_COMMON_CTRL3_common_ctrl3_END    (31)


/*****************************************************************************
 结构名    : SOC_EXMBIST_RW_MID_UNION
 结构说明  : RW_MID 寄存器结构定义。地址偏移量:0x0078，初值:0x0000001A，宽度:32
 寄存器说明: 读写mid配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rw_mid   : 6;  /* bit[0-5] : 读写mid配置。 */
        unsigned int  reserved : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_EXMBIST_RW_MID_UNION;
#endif
#define SOC_EXMBIST_RW_MID_rw_mid_START    (0)
#define SOC_EXMBIST_RW_MID_rw_mid_END      (5)






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

#endif /* end of soc_exmbist_interface.h */
