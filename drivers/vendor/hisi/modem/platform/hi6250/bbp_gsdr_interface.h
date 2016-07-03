

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "soc_interface.h"

#ifndef __BBP_GSDR_INTERFACE_H__
#define __BBP_GSDR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/3) register_define_gsdr_glb
 ***======================================================================***/
/* 寄存器说明：
 bit[31:22]  保留
 bit[21]     G软化前端数据
 bit[20]     G软化前端控制
 bit[19]     G软化中断
 bit[18]     G软化定时
 bit[17]     G软化时钟测量
 bit[16]     系统时钟域CLK控制。在对各模块进行时钟控制时，将对应bit置1表示打开该模块的时钟；反之，将对应bit置0表示关闭该模块的时钟。
             G采数
 bit[15:6]   保留
 bit[5]      G软化前端数据
 bit[4]      G软化前端控制
 bit[3]      G软化中断
 bit[2]      G软化定时
 bit[1]      G软化时钟测量
 bit[0]      系统时钟域RST控制。在对各模块进行复位时，将对应bit置1，之后再将对应bit置0。
             G采数
   UNION结构:  GSDR_SYS_RST_CTRL_GSDR_UNION */
#define GSDR_SYS_RST_CTRL_GSDR_ADDR                   (SOC_BBP_GSDR_BASE_ADDR + 0x0)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20]     G软化前端控制
 bit[19]     G软化中断
 bit[18]     G软化定时
 bit[17]     G软化时钟测量
 bit[16]     IMI地址片选控制屏蔽使能，高电平有效。该信号有效表示对应模块未被选中时屏蔽BBP内部该模块IMI地址片选功能。
             G采数
 bit[15:5]   保留
 bit[4]      G软化前端控制
 bit[3]      G软化中断
 bit[2]      G软化定时
 bit[1]      G软化时钟测量
 bit[0]      IMI时钟域RST控制。在对各模块进行复位时，将对应bit置1，之后再将对应bit置0。
             G采数
   UNION结构:  GSDR_IMI_RST_CTRL_GSDR_UNION */
#define GSDR_IMI_RST_CTRL_GSDR_ADDR                   (SOC_BBP_GSDR_BASE_ADDR + 0x4)



/***======================================================================***
                     (2/3) register_define_g_dump
 ***======================================================================***/
/* 寄存器说明：
 bit[31]     下行通道搬数模式。0，软基带搬数；1，前端AGC采数。
 bit[30:29]  保留
 bit[28]     下行DMA搬运模式。0，一次burst请求搬运32x32bit；1，一次burst请求搬运16x32bit。
 bit[27:25]  保留
 bit[24]     下行搬运模式。0，DMA方式；1，BBPMaster方式。
             固定为1，使用BBPMaster方式，不再支持DMA方式。
 bit[23:21]  保留
 bit[20]     下行SDR IF模块搬运停止模式。0，配置停止脉冲后立即停止搬运；1，达到cpu_dlfe_sdr_data_length定义的搬运数据量后自动停止搬运。
 bit[19:17]  保留
 bit[16]     下行SDR IF模块搬运启动模式。0，配置启动脉冲后立即启动搬运；1，配置启动脉冲后到达cpu_dlfe_sdr_start_time定义的时刻启动搬运。
 bit[15:1]   保留
 bit[0]      下行SDR IF模块使能，高电平有效。
   UNION结构:  GSDR_DLFE_SDR_EN_UNION */
#define GSDR_DLFE_SDR_EN_ADDR                         (SOC_BBP_GSDR_BASE_ADDR + 0x5000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      下行搬数时钟门控bypass信号，高电平有效，表示时钟常开。
   UNION结构:  GSDR_DLFE_SDR_CKG_BYS_UNION */
#define GSDR_DLFE_SDR_CKG_BYS_ADDR                    (SOC_BBP_GSDR_BASE_ADDR + 0x5004)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12]     下行主集BBPMaster搬运复位脉冲。
 bit[11:9]   保留
 bit[8]      下行主集搬运强制停止脉冲。在检测到下行主集搬运出错后配置。
 bit[7:5]    保留
 bit[4]      下行主集搬运停止脉冲。
 bit[3:1]    保留
 bit[0]      下行主集搬运启动脉冲。
   UNION结构:  GSDR_DLFE_SDR_START_STOP_UNION */
#define GSDR_DLFE_SDR_START_STOP_ADDR                 (SOC_BBP_GSDR_BASE_ADDR + 0x5008)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   下行Buffer深度，单位32word，用于计算Buffer首地址的时间戳。
             C模和U模软化时，一个word对应一个chip；G模软化时，一个word对应一个Qb。
             C模/U模软化含义无效。
   UNION结构:  GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION */
#define GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_ADDR          (SOC_BBP_GSDR_BASE_ADDR + 0x500C)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:0]   下行搬运启动时刻。
             C模为c_base_cnt上的启动时刻，单位chip。
             bit[14:0]：范围0~32767chip；
             bit[16:15]：范围0~2；
             bit[21:17]：范围0~24。
             G模软化为gtc_timebase上的启动时刻，单位Qb。
             bit[12:0]：gtc_timebase上的帧内Qb值，范围0~4999Qb；
             bit[21:13]：无意义。
             U模软化为base_cnt上的启动时刻，单位chip。
             bit[7:0]：symbol内chip值，范围0~255chip；
             bit[11:8]：slot内symbol值，范围0~9symbol；
             bit[15:12]：帧内slot值，范围0~14slot；
             bit[21:16]：无意义。
             该参数仅在cpu_dlfe_sdr_start_mode为1时有效。
             C模/U模软化含义无效。
   UNION结构:  GSDR_DLFE_SDR_TIME_CTRL_UNION */
#define GSDR_DLFE_SDR_TIME_CTRL_ADDR                  (SOC_BBP_GSDR_BASE_ADDR + 0x5010)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   下行搬运数据量，单位32word。
             该参数仅在cpu_dlfe_sdr_stop_mode为1时有效。
   UNION结构:  GSDR_DLFE_SDR_TIME_CTRL2_UNION */
#define GSDR_DLFE_SDR_TIME_CTRL2_ADDR                 (SOC_BBP_GSDR_BASE_ADDR + 0x5014)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   下行Buffer深度，单位word。
             C模和U模软化时，一个word对应一个chip；G模软化时，一个word对应一个Qb。
             建议在G模软化时使用。
             C模/U模软化含义无效。
   UNION结构:  GSDR_DLFE_SDR_WORD_DEPTH_UNION */
#define GSDR_DLFE_SDR_WORD_DEPTH_ADDR                 (SOC_BBP_GSDR_BASE_ADDR + 0x5018)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    下行天线1当前搬运word数。
   UNION结构:  GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_ADDR            (SOC_BBP_GSDR_BASE_ADDR + 0x5040)

/* 寄存器说明：
 bit[31:12]  下行天线1当前搬运页数。根据cpu_dlfe_sdr_buffer_depth统计。
 bit[11:0]   下行天线1当前搬运块数。根据cpu_dlfe_sdr_buffer_depth统计。
   UNION结构:  GSDR_DLFE_SDR_AT1_RD_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_RD_RPT_ADDR                 (SOC_BBP_GSDR_BASE_ADDR + 0x5044)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:0]   下行天线1启动搬运后第一个数据对应时间戳。
             C模时间戳为c_base_cnt，单位chip。
             bit[14:0]：计数范围0~32767chip，时间长度80/3ms（32768chip）；
             bit[16:15]：计数范围0~2，时间长度80ms；
             bit[21:17]：计数范围0~24，时间长度2s；
             bit[27:22]：固定为0。
             G模软化时间戳为gtc_tdma_qb上的帧号和gtc_timebase上的Qb号。
             bit[12:0]：gtc_timebase上的帧内Qb计数，计数范围0~4999Qb；
             bit[23:13]：gtc_tdma_qb上的fn_low帧计数，计数范围0~1325帧。
             bit[27:24]：固定为0。
             U模软化时间戳为base_cnt和cfn。
             bit[7:0]：symbol内chip计数，计数范围0~255chip；
             bit[11:8]：slot内symbol计数，计数范围0~9symbol；
             bit[15:12]：帧内slot计数，计数范围0~14slot；
             bit[27:16]：cfn。
             C模/U模软化含义无效。
   UNION结构:  GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_ADDR          (SOC_BBP_GSDR_BASE_ADDR + 0x5050)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:0]   下行天线1启动搬运后Buffer首地址数据对应时间戳，经过时隙头锁存。
             时间戳含义同上。
             C模1x时隙头即PCG头；C模EV-DO时隙头即实际时隙头；G模软化时隙头即gtc_tdma_qb上的burst头；U模软化时隙头即实际时隙头。
             C模/U模软化含义无效。
   UNION结构:  GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_ADDR       (SOC_BBP_GSDR_BASE_ADDR + 0x5058)

/* 寄存器说明：
   详      述：下行天线1接收数据。
               C模和U模软化时采集DAGC后数据，一个word对应一个chip，格式如下。
               bit[7:0]：chip内样点0 I路；
               bit[15:8]：chip内样点0 Q路；
               bit[23:16]：chip内样点1 I路；
               bit[31:24]：chip内样点1 Q路。
               G模软化时采集AD后数据，一个word对应一个Qb，格式如下。
               bit[15:0]：Qb I路；
               bit[31:16]：Qb Q路。
               C模/U模软化含义无效。
   UNION结构 ：无 */
#define GSDR_DLFE_SDR_AT1_DATA_ADDR                   (SOC_BBP_GSDR_BASE_ADDR + 0x5060)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      下行天线1搬运出错指示。
 bit[3:1]    保留
 bit[0]      下行天线1搬运状态。
   UNION结构:  GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_ADDR            (SOC_BBP_GSDR_BASE_ADDR + 0x5070)

/* 寄存器说明：
 bit[31:16]  下行天线1当前搬运页数。根据cpu_dlfe_sdr_word_depth统计。
             建议在G模软化时使用。
 bit[15:0]   下行天线1当前搬运字数。根据cpu_dlfe_sdr_word_depth统计。
             建议在G模软化时使用。
   UNION结构:  GSDR_DLFE_SDR_AT1_RD_WORD_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_ADDR            (SOC_BBP_GSDR_BASE_ADDR + 0x5078)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24]     上行搬运模式。0，DMA方式；1，BBPMaster方式。
             建议采用BBPMaster方式。
 bit[23:17]  保留
 bit[16]     G模软化上行发送定时选择。0，基于gtc_timebase；1，基于gtc_tdma_qb。
 bit[15:13]  保留
 bit[12]     G模软化上行发送模式。0，正常模式；1，连续模式。
 bit[11:1]   保留
 bit[0]      上行SDR IF模块使能，高电平有效。
   UNION结构:  GSDR_ULFE_SDR_EN_UNION */
#define GSDR_ULFE_SDR_EN_ADDR                         (SOC_BBP_GSDR_BASE_ADDR + 0x5100)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上行搬数时钟门控bypass信号，高电平有效，表示时钟常开。
   UNION结构:  GSDR_ULFE_SDR_CKG_UNION */
#define GSDR_ULFE_SDR_CKG_ADDR                        (SOC_BBP_GSDR_BASE_ADDR + 0x5104)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5]      BBPMaster搬运复位脉冲。
 bit[4:2]    保留
 bit[1]      上行取数发送停止脉冲。
             该参数仅在G模软化时有效。
 bit[0]      上行取数发送启动脉冲。
             该参数仅在G模软化时有效。
   UNION结构:  GSDR_ULFE_SDR_START_UNION */
#define GSDR_ULFE_SDR_START_ADDR                      (SOC_BBP_GSDR_BASE_ADDR + 0x5108)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  C模时，表示上行ACH时隙头相对sys_cnt时隙边界延迟量，单位chip。
             G模软化时，bit[22:16]表示启动数据发送的Qb内clk时刻；bit[26:23]无意义。
             C模含义无效。
 bit[15:13]  保留
 bit[12:0]   C模时，表示上行时隙头相对sys_cnt时隙边界提前量，单位1/4chip。
             G模软化时，表示gtc_tdma_qb上的启动数据发送时刻，单位Qb，范围0~4999。
             C模含义无效。
   UNION结构:  GSDR_ULFE_SDR_OFFSET_UNION */
#define GSDR_ULFE_SDR_OFFSET_ADDR                     (SOC_BBP_GSDR_BASE_ADDR + 0x510C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  C模时，表示上行相位补偿提前时隙头生效位置，单位1/4chip。
             G模软化时，bit[27:16]表示发送数据最后一个burst结束样点，取值范围0~2499；bit[28]无意义。
             C模含义无效。
 bit[15:13]  保留
 bit[12:0]   C模时，表示上行dbb控制字提前时隙头生效位置，单位1/4chip。
             G模软化时，bit[11:0]表示发送数据第一个burst起始样点，取值范围0~2499；bit[12]无意义。
             C模含义无效。
   UNION结构:  GSDR_ULFE_SDR_ACTIVE_TIME_UNION */
#define GSDR_ULFE_SDR_ACTIVE_TIME_ADDR                (SOC_BBP_GSDR_BASE_ADDR + 0x5110)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    G模软化时，发送数据包含的burst个数，取值范围0~5。配置值加1表示实际burst个数。
   UNION结构:  GSDR_ULFE_SDR_G_CFG_UNION */
#define GSDR_ULFE_SDR_G_CFG_ADDR                      (SOC_BBP_GSDR_BASE_ADDR + 0x5114)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      上行BBPMaster搬运完成指示。
 bit[7:5]    保留
 bit[4]      上行BBPMaster搬运出错指示。
 bit[3:1]    保留
 bit[0]      上行搬运状态。
   UNION结构:  GSDR_ULFE_SDR_DUMP_EN_RPT_UNION */
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ADDR                (SOC_BBP_GSDR_BASE_ADDR + 0x5140)

/* 寄存器说明：
   详      述：G前端AGC采数接收数据。
   UNION结构 ：无 */
#define GSDR_DUMP_DMA_RDATA_G_ADDR                    (SOC_BBP_GSDR_BASE_ADDR + 0x5240)

/* 寄存器说明：
   详      述：G前端AGC采数起始时刻上报。
   UNION结构 ：无 */
#define GSDR_DUMP_STAMP_G_PART1_CPU_ADDR              (SOC_BBP_GSDR_BASE_ADDR + 0x5250)

/* 寄存器说明：
   详      述：G前端AGC采数起始时刻上报。
   UNION结构 ：无 */
#define GSDR_DUMP_STAMP_G_PART2_CPU_ADDR              (SOC_BBP_GSDR_BASE_ADDR + 0x5254)



/***======================================================================***
                     (3/3) register_define_g_dump_mem
 ***======================================================================***/
/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  C模时，表示上行前端数据Q路，12比特有符号数，软件每1/4 PCG或slot写一遍。
             G模软化时，表示上行发送数据Q路，12比特有符号数，软件每1/5 burst写一遍。
             C模含义无效。
 bit[15:12]  保留
 bit[11:0]   C模时，表示上行前端数据I路，12比特有符号数，软件每1/4 PCG或slot写一遍。
             G模软化时，表示上行发送数据I路，12比特有符号数，软件每1/5 burst写一遍。
             C模含义无效。
   UNION结构:  GSDR_ULFE_SDR_RAM_UNION */
#define GSDR_ULFE_SDR_RAM_ADDR                        (SOC_BBP_GSDR_BASE_ADDR + 0x5800)
#define GSDR_ULFE_SDR_RAM_MEMDEPTH  (512)





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
                     (1/3) register_define_gsdr_glb
 ***======================================================================***/
/*****************************************************************************
 结构名    : GSDR_SYS_RST_CTRL_GSDR_UNION
 结构说明  : SYS_RST_CTRL_GSDR 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sys_rst_ctrl_gsdr_reg;
    struct
    {
        unsigned int  sys_rst_ctrl_gdump           : 1;  /* bit[0]    : 系统时钟域RST控制。在对各模块进行复位时，将对应bit置1，之后再将对应bit置0。
                                                                        G采数 */
        unsigned int  sys_rst_ctrl_gsdr_gdrx_gauge : 1;  /* bit[1]    : G软化时钟测量 */
        unsigned int  sys_rst_ctrl_gsdr_timing     : 1;  /* bit[2]    : G软化定时 */
        unsigned int  sys_rst_ctrl_gsdr_intr       : 1;  /* bit[3]    : G软化中断 */
        unsigned int  sys_rst_ctrl_gsdr_fe_ctrl    : 1;  /* bit[4]    : G软化前端控制 */
        unsigned int  sys_rst_ctrl_gsdr_fe_abb     : 1;  /* bit[5]    : G软化前端数据 */
        unsigned int  reserved_0                   : 10; /* bit[6-15] : 保留 */
        unsigned int  sys_clk_ctrl_gdump           : 1;  /* bit[16]   : 系统时钟域CLK控制。在对各模块进行时钟控制时，将对应bit置1表示打开该模块的时钟；反之，将对应bit置0表示关闭该模块的时钟。
                                                                        G采数 */
        unsigned int  sys_clk_ctrl_gsdr_gdrx_gauge : 1;  /* bit[17]   : G软化时钟测量 */
        unsigned int  sys_clk_ctrl_gsdr_timing     : 1;  /* bit[18]   : G软化定时 */
        unsigned int  sys_clk_ctrl_gsdr_intr       : 1;  /* bit[19]   : G软化中断 */
        unsigned int  sys_clk_ctrl_gsdr_fe_ctrl    : 1;  /* bit[20]   : G软化前端控制 */
        unsigned int  sys_clk_ctrl_gsdr_fe_abb     : 1;  /* bit[21]   : G软化前端数据 */
        unsigned int  reserved_1                   : 10; /* bit[22-31]: 保留 */
    } reg;
} GSDR_SYS_RST_CTRL_GSDR_UNION;
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gdump_START            (0)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gdump_END              (0)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_gdrx_gauge_START  (1)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_gdrx_gauge_END    (1)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_timing_START      (2)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_timing_END        (2)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_intr_START        (3)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_intr_END          (3)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_fe_ctrl_START     (4)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_fe_ctrl_END       (4)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_fe_abb_START      (5)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_fe_abb_END        (5)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gdump_START            (16)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gdump_END              (16)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_gdrx_gauge_START  (17)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_gdrx_gauge_END    (17)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_timing_START      (18)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_timing_END        (18)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_intr_START        (19)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_intr_END          (19)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_fe_ctrl_START     (20)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_fe_ctrl_END       (20)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_fe_abb_START      (21)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_fe_abb_END        (21)


/*****************************************************************************
 结构名    : GSDR_IMI_RST_CTRL_GSDR_UNION
 结构说明  : IMI_RST_CTRL_GSDR 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      imi_rst_ctrl_gsdr_reg;
    struct
    {
        unsigned int  imi_rst_ctrl_gdump            : 1;  /* bit[0]    : IMI时钟域RST控制。在对各模块进行复位时，将对应bit置1，之后再将对应bit置0。
                                                                         G采数 */
        unsigned int  imi_rst_ctrl_gsdr_gdrx_gauge  : 1;  /* bit[1]    : G软化时钟测量 */
        unsigned int  imi_rst_ctrl_gsdr_timing      : 1;  /* bit[2]    : G软化定时 */
        unsigned int  imi_rst_ctrl_gsdr_intr        : 1;  /* bit[3]    : G软化中断 */
        unsigned int  imi_rst_ctrl_gsdr_fe_ctrl     : 1;  /* bit[4]    : G软化前端控制 */
        unsigned int  reserved_0                    : 11; /* bit[5-15] : 保留 */
        unsigned int  imi_addr_ctrl_gdump           : 1;  /* bit[16]   : IMI地址片选控制屏蔽使能，高电平有效。该信号有效表示对应模块未被选中时屏蔽BBP内部该模块IMI地址片选功能。
                                                                         G采数 */
        unsigned int  imi_addr_ctrl_gsdr_gdrx_gauge : 1;  /* bit[17]   : G软化时钟测量 */
        unsigned int  imi_addr_ctrl_gsdr_timing     : 1;  /* bit[18]   : G软化定时 */
        unsigned int  imi_addr_ctrl_gsdr_intr       : 1;  /* bit[19]   : G软化中断 */
        unsigned int  imi_addr_ctrl_gsdr_fe_ctrl    : 1;  /* bit[20]   : G软化前端控制 */
        unsigned int  reserved_1                    : 11; /* bit[21-31]: 保留 */
    } reg;
} GSDR_IMI_RST_CTRL_GSDR_UNION;
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gdump_START             (0)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gdump_END               (0)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_gdrx_gauge_START   (1)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_gdrx_gauge_END     (1)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_timing_START       (2)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_timing_END         (2)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_intr_START         (3)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_intr_END           (3)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_fe_ctrl_START      (4)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_fe_ctrl_END        (4)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gdump_START            (16)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gdump_END              (16)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_gdrx_gauge_START  (17)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_gdrx_gauge_END    (17)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_timing_START      (18)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_timing_END        (18)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_intr_START        (19)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_intr_END          (19)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_fe_ctrl_START     (20)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_fe_ctrl_END       (20)


/***======================================================================***
                     (2/3) register_define_g_dump
 ***======================================================================***/
/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_EN_UNION
 结构说明  : DLFE_SDR_EN 寄存器结构定义。地址偏移量:0x000，初值:0x01000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_en_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_en         : 1;  /* bit[0]    : 下行SDR IF模块使能，高电平有效。 */
        unsigned int  reserved_0              : 15; /* bit[1-15] : 保留 */
        unsigned int  cpu_dlfe_sdr_start_mode : 1;  /* bit[16]   : 下行SDR IF模块搬运启动模式。0，配置启动脉冲后立即启动搬运；1，配置启动脉冲后到达cpu_dlfe_sdr_start_time定义的时刻启动搬运。 */
        unsigned int  reserved_1              : 3;  /* bit[17-19]: 保留 */
        unsigned int  cpu_dlfe_sdr_stop_mode  : 1;  /* bit[20]   : 下行SDR IF模块搬运停止模式。0，配置停止脉冲后立即停止搬运；1，达到cpu_dlfe_sdr_data_length定义的搬运数据量后自动停止搬运。 */
        unsigned int  reserved_2              : 3;  /* bit[21-23]: 保留 */
        unsigned int  cpu_dlfe_sdr_trans_mode : 1;  /* bit[24]   : 下行搬运模式。0，DMA方式；1，BBPMaster方式。
                                                                   固定为1，使用BBPMaster方式，不再支持DMA方式。 */
        unsigned int  reserved_3              : 3;  /* bit[25-27]: 保留 */
        unsigned int  cpu_dlfe_sdr_dma_mode   : 1;  /* bit[28]   : 下行DMA搬运模式。0，一次burst请求搬运32x32bit；1，一次burst请求搬运16x32bit。 */
        unsigned int  reserved_4              : 2;  /* bit[29-30]: 保留 */
        unsigned int  cpu_dlfe_g_dump_mode    : 1;  /* bit[31]   : 下行通道搬数模式。0，软基带搬数；1，前端AGC采数。 */
    } reg;
} GSDR_DLFE_SDR_EN_UNION;
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_en_START          (0)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_en_END            (0)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_start_mode_START  (16)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_start_mode_END    (16)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_stop_mode_START   (20)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_stop_mode_END     (20)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_trans_mode_START  (24)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_trans_mode_END    (24)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_dma_mode_START    (28)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_dma_mode_END      (28)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_g_dump_mode_START     (31)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_g_dump_mode_END       (31)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_CKG_BYS_UNION
 结构说明  : DLFE_SDR_CKG_BYS 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_ckg_bys_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_ckg_bypass : 1;  /* bit[0]   : 下行搬数时钟门控bypass信号，高电平有效，表示时钟常开。 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_CKG_BYS_UNION;
#define GSDR_DLFE_SDR_CKG_BYS_cpu_dlfe_sdr_ckg_bypass_START  (0)
#define GSDR_DLFE_SDR_CKG_BYS_cpu_dlfe_sdr_ckg_bypass_END    (0)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_START_STOP_UNION
 结构说明  : DLFE_SDR_START_STOP 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_start_stop_reg;
    struct
    {
        unsigned int  cpu_dlfe_at1_sdr_start      : 1;  /* bit[0]    : 下行主集搬运启动脉冲。 */
        unsigned int  reserved_0                  : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_dlfe_at1_sdr_stop       : 1;  /* bit[4]    : 下行主集搬运停止脉冲。 */
        unsigned int  reserved_1                  : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_dlfe_at1_sdr_force_stop : 1;  /* bit[8]    : 下行主集搬运强制停止脉冲。在检测到下行主集搬运出错后配置。 */
        unsigned int  reserved_2                  : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_dlfe_at1_sdr_trans_clr  : 1;  /* bit[12]   : 下行主集BBPMaster搬运复位脉冲。 */
        unsigned int  reserved_3                  : 19; /* bit[13-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_START_STOP_UNION;
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_start_START       (0)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_start_END         (0)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_stop_START        (4)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_stop_END          (4)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_force_stop_START  (8)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_force_stop_END    (8)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_trans_clr_START   (12)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_trans_clr_END     (12)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION
 结构说明  : DLFE_SDR_OFFSET_BUFF_DEPTH 寄存器结构定义。地址偏移量:0x00C，初值:0x0000007F，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_offset_buff_depth_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_buffer_depth : 12; /* bit[0-11] : 下行Buffer深度，单位32word，用于计算Buffer首地址的时间戳。
                                                                     C模和U模软化时，一个word对应一个chip；G模软化时，一个word对应一个Qb。
                                                                     C模/U模软化含义无效。 */
        unsigned int  reserved                  : 20; /* bit[12-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION;
#define GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_sdr_buffer_depth_START  (0)
#define GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_sdr_buffer_depth_END    (11)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_TIME_CTRL_UNION
 结构说明  : DLFE_SDR_TIME_CTRL 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_time_ctrl_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_start_time : 22; /* bit[0-21] : 下行搬运启动时刻。
                                                                   C模为c_base_cnt上的启动时刻，单位chip。
                                                                   bit[14:0]：范围0~32767chip；
                                                                   bit[16:15]：范围0~2；
                                                                   bit[21:17]：范围0~24。
                                                                   G模软化为gtc_timebase上的启动时刻，单位Qb。
                                                                   bit[12:0]：gtc_timebase上的帧内Qb值，范围0~4999Qb；
                                                                   bit[21:13]：无意义。
                                                                   U模软化为base_cnt上的启动时刻，单位chip。
                                                                   bit[7:0]：symbol内chip值，范围0~255chip；
                                                                   bit[11:8]：slot内symbol值，范围0~9symbol；
                                                                   bit[15:12]：帧内slot值，范围0~14slot；
                                                                   bit[21:16]：无意义。
                                                                   该参数仅在cpu_dlfe_sdr_start_mode为1时有效。
                                                                   C模/U模软化含义无效。 */
        unsigned int  reserved                : 10; /* bit[22-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_TIME_CTRL_UNION;
#define GSDR_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_start_time_START  (0)
#define GSDR_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_start_time_END    (21)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_TIME_CTRL2_UNION
 结构说明  : DLFE_SDR_TIME_CTRL2 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_time_ctrl2_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_data_length : 12; /* bit[0-11] : 下行搬运数据量，单位32word。
                                                                    该参数仅在cpu_dlfe_sdr_stop_mode为1时有效。 */
        unsigned int  reserved                 : 20; /* bit[12-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_TIME_CTRL2_UNION;
#define GSDR_DLFE_SDR_TIME_CTRL2_cpu_dlfe_sdr_data_length_START  (0)
#define GSDR_DLFE_SDR_TIME_CTRL2_cpu_dlfe_sdr_data_length_END    (11)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_WORD_DEPTH_UNION
 结构说明  : DLFE_SDR_WORD_DEPTH 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_word_depth_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_word_depth : 16; /* bit[0-15] : 下行Buffer深度，单位word。
                                                                   C模和U模软化时，一个word对应一个chip；G模软化时，一个word对应一个Qb。
                                                                   建议在G模软化时使用。
                                                                   C模/U模软化含义无效。 */
        unsigned int  reserved                : 16; /* bit[16-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_WORD_DEPTH_UNION;
#define GSDR_DLFE_SDR_WORD_DEPTH_cpu_dlfe_sdr_word_depth_START  (0)
#define GSDR_DLFE_SDR_WORD_DEPTH_cpu_dlfe_sdr_word_depth_END    (15)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_UNION
 结构说明  : DLFE_SDR_AT1_RD_CHIP_RPT 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_rd_chip_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_rd_chip_cnt_cpu : 6;  /* bit[0-5] : 下行天线1当前搬运word数。 */
        unsigned int  reserved                     : 26; /* bit[6-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_dlfe_sdr_at1_rd_chip_cnt_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_dlfe_sdr_at1_rd_chip_cnt_cpu_END    (5)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_AT1_RD_RPT_UNION
 结构说明  : DLFE_SDR_AT1_RD_RPT 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_rd_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_rd_block_cnt_cpu : 12; /* bit[0-11] : 下行天线1当前搬运块数。根据cpu_dlfe_sdr_buffer_depth统计。 */
        unsigned int  dlfe_sdr_at1_rd_page_cnt_cpu  : 20; /* bit[12-31]: 下行天线1当前搬运页数。根据cpu_dlfe_sdr_buffer_depth统计。 */
    } reg;
} GSDR_DLFE_SDR_AT1_RD_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_block_cnt_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_block_cnt_cpu_END    (11)
#define GSDR_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_page_cnt_cpu_START   (12)
#define GSDR_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_page_cnt_cpu_END     (31)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION
 结构说明  : DLFE_SDR_AT1_1ST_STAMP_RPT 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_1st_stamp_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_1st_stamp_cpu : 28; /* bit[0-27] : 下行天线1启动搬运后第一个数据对应时间戳。
                                                                      C模时间戳为c_base_cnt，单位chip。
                                                                      bit[14:0]：计数范围0~32767chip，时间长度80/3ms（32768chip）；
                                                                      bit[16:15]：计数范围0~2，时间长度80ms；
                                                                      bit[21:17]：计数范围0~24，时间长度2s；
                                                                      bit[27:22]：固定为0。
                                                                      G模软化时间戳为gtc_tdma_qb上的帧号和gtc_timebase上的Qb号。
                                                                      bit[12:0]：gtc_timebase上的帧内Qb计数，计数范围0~4999Qb；
                                                                      bit[23:13]：gtc_tdma_qb上的fn_low帧计数，计数范围0~1325帧。
                                                                      bit[27:24]：固定为0。
                                                                      U模软化时间戳为base_cnt和cfn。
                                                                      bit[7:0]：symbol内chip计数，计数范围0~255chip；
                                                                      bit[11:8]：slot内symbol计数，计数范围0~9symbol；
                                                                      bit[15:12]：帧内slot计数，计数范围0~14slot；
                                                                      bit[27:16]：cfn。
                                                                      C模/U模软化含义无效。 */
        unsigned int  reserved                   : 4;  /* bit[28-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_dlfe_sdr_at1_1st_stamp_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_dlfe_sdr_at1_1st_stamp_cpu_END    (27)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION
 结构说明  : DLFE_SDR_AT1_BUFFER_STAMP_RPT 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_buffer_stamp_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_bufferhead_stamp_cpu : 28; /* bit[0-27] : 下行天线1启动搬运后Buffer首地址数据对应时间戳，经过时隙头锁存。
                                                                             时间戳含义同上。
                                                                             C模1x时隙头即PCG头；C模EV-DO时隙头即实际时隙头；G模软化时隙头即gtc_tdma_qb上的burst头；U模软化时隙头即实际时隙头。
                                                                             C模/U模软化含义无效。 */
        unsigned int  reserved                          : 4;  /* bit[28-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_dlfe_sdr_at1_bufferhead_stamp_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_dlfe_sdr_at1_bufferhead_stamp_cpu_END    (27)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_UNION
 结构说明  : DLFE_SDR_AT1_DUMP_EN_RPT 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_dump_en_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_dump_en : 1;  /* bit[0]   : 下行天线1搬运状态。 */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : 保留 */
        unsigned int  dlfe_sdr_at1_err_sta : 1;  /* bit[4]   : 下行天线1搬运出错指示。 */
        unsigned int  reserved_1           : 27; /* bit[5-31]: 保留 */
    } reg;
} GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_dump_en_START  (0)
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_dump_en_END    (0)
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_err_sta_START  (4)
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_err_sta_END    (4)


/*****************************************************************************
 结构名    : GSDR_DLFE_SDR_AT1_RD_WORD_RPT_UNION
 结构说明  : DLFE_SDR_AT1_RD_WORD_RPT 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_rd_word_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_rd_word_cnt_cpu : 16; /* bit[0-15] : 下行天线1当前搬运字数。根据cpu_dlfe_sdr_word_depth统计。
                                                                        建议在G模软化时使用。 */
        unsigned int  dlfe_sdr_at1_rd_seg_cnt_cpu  : 16; /* bit[16-31]: 下行天线1当前搬运页数。根据cpu_dlfe_sdr_word_depth统计。
                                                                        建议在G模软化时使用。 */
    } reg;
} GSDR_DLFE_SDR_AT1_RD_WORD_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_word_cnt_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_word_cnt_cpu_END    (15)
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_seg_cnt_cpu_START   (16)
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_seg_cnt_cpu_END     (31)


/*****************************************************************************
 结构名    : GSDR_ULFE_SDR_EN_UNION
 结构说明  : ULFE_SDR_EN 寄存器结构定义。地址偏移量:0x100，初值:0x01000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_en_reg;
    struct
    {
        unsigned int  cpu_ulfe_sdr_en            : 1;  /* bit[0]    : 上行SDR IF模块使能，高电平有效。 */
        unsigned int  reserved_0                 : 11; /* bit[1-11] : 保留 */
        unsigned int  cpu_ulfe_sdr_g_mode        : 1;  /* bit[12]   : G模软化上行发送模式。0，正常模式；1，连续模式。 */
        unsigned int  reserved_1                 : 3;  /* bit[13-15]: 保留 */
        unsigned int  cpu_ulfe_sdr_g_timing_mode : 1;  /* bit[16]   : G模软化上行发送定时选择。0，基于gtc_timebase；1，基于gtc_tdma_qb。 */
        unsigned int  reserved_2                 : 7;  /* bit[17-23]: 保留 */
        unsigned int  cpu_ulfe_sdr_trans_mode    : 1;  /* bit[24]   : 上行搬运模式。0，DMA方式；1，BBPMaster方式。
                                                                      建议采用BBPMaster方式。 */
        unsigned int  reserved_3                 : 7;  /* bit[25-31]: 保留 */
    } reg;
} GSDR_ULFE_SDR_EN_UNION;
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_en_START             (0)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_en_END               (0)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_g_mode_START         (12)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_g_mode_END           (12)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_g_timing_mode_START  (16)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_g_timing_mode_END    (16)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_trans_mode_START     (24)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_trans_mode_END       (24)


/*****************************************************************************
 结构名    : GSDR_ULFE_SDR_CKG_UNION
 结构说明  : ULFE_SDR_CKG 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_ckg_reg;
    struct
    {
        unsigned int  cpu_ulfe_sdr_ckg_bypass : 1;  /* bit[0]   : 上行搬数时钟门控bypass信号，高电平有效，表示时钟常开。 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} GSDR_ULFE_SDR_CKG_UNION;
#define GSDR_ULFE_SDR_CKG_cpu_ulfe_sdr_ckg_bypass_START  (0)
#define GSDR_ULFE_SDR_CKG_cpu_ulfe_sdr_ckg_bypass_END    (0)


/*****************************************************************************
 结构名    : GSDR_ULFE_SDR_START_UNION
 结构说明  : ULFE_SDR_START 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_start_reg;
    struct
    {
        unsigned int  cpu_ulfe_sdr_g_start   : 1;  /* bit[0]   : 上行取数发送启动脉冲。
                                                                 该参数仅在G模软化时有效。 */
        unsigned int  cpu_ulfe_sdr_g_stop    : 1;  /* bit[1]   : 上行取数发送停止脉冲。
                                                                 该参数仅在G模软化时有效。 */
        unsigned int  reserved_0             : 3;  /* bit[2-4] : 保留 */
        unsigned int  cpu_ulfe_sdr_trans_clr : 1;  /* bit[5]   : BBPMaster搬运复位脉冲。 */
        unsigned int  reserved_1             : 26; /* bit[6-31]: 保留 */
    } reg;
} GSDR_ULFE_SDR_START_UNION;
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_g_start_START    (0)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_g_start_END      (0)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_g_stop_START     (1)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_g_stop_END       (1)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_trans_clr_START  (5)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_trans_clr_END    (5)


/*****************************************************************************
 结构名    : GSDR_ULFE_SDR_OFFSET_UNION
 结构说明  : ULFE_SDR_OFFSET 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_offset_reg;
    struct
    {
        unsigned int  cpu_ulfe_slot_offset : 13; /* bit[0-12] : C模时，表示上行时隙头相对sys_cnt时隙边界提前量，单位1/4chip。
                                                                G模软化时，表示gtc_tdma_qb上的启动数据发送时刻，单位Qb，范围0~4999。
                                                                C模含义无效。 */
        unsigned int  reserved_0           : 3;  /* bit[13-15]: 保留 */
        unsigned int  cpu_ulfe_ach_offset  : 11; /* bit[16-26]: C模时，表示上行ACH时隙头相对sys_cnt时隙边界延迟量，单位chip。
                                                                G模软化时，bit[22:16]表示启动数据发送的Qb内clk时刻；bit[26:23]无意义。
                                                                C模含义无效。 */
        unsigned int  reserved_1           : 5;  /* bit[27-31]: 保留 */
    } reg;
} GSDR_ULFE_SDR_OFFSET_UNION;
#define GSDR_ULFE_SDR_OFFSET_cpu_ulfe_slot_offset_START  (0)
#define GSDR_ULFE_SDR_OFFSET_cpu_ulfe_slot_offset_END    (12)
#define GSDR_ULFE_SDR_OFFSET_cpu_ulfe_ach_offset_START   (16)
#define GSDR_ULFE_SDR_OFFSET_cpu_ulfe_ach_offset_END     (26)


/*****************************************************************************
 结构名    : GSDR_ULFE_SDR_ACTIVE_TIME_UNION
 结构说明  : ULFE_SDR_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_active_time_reg;
    struct
    {
        unsigned int  cpu_ulfe_dbb_active_time        : 13; /* bit[0-12] : C模时，表示上行dbb控制字提前时隙头生效位置，单位1/4chip。
                                                                           G模软化时，bit[11:0]表示发送数据第一个burst起始样点，取值范围0~2499；bit[12]无意义。
                                                                           C模含义无效。 */
        unsigned int  reserved_0                      : 3;  /* bit[13-15]: 保留 */
        unsigned int  cpu_ulfe_phase_comp_active_time : 13; /* bit[16-28]: C模时，表示上行相位补偿提前时隙头生效位置，单位1/4chip。
                                                                           G模软化时，bit[27:16]表示发送数据最后一个burst结束样点，取值范围0~2499；bit[28]无意义。
                                                                           C模含义无效。 */
        unsigned int  reserved_1                      : 3;  /* bit[29-31]: 保留 */
    } reg;
} GSDR_ULFE_SDR_ACTIVE_TIME_UNION;
#define GSDR_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_dbb_active_time_START         (0)
#define GSDR_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_dbb_active_time_END           (12)
#define GSDR_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_phase_comp_active_time_START  (16)
#define GSDR_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_phase_comp_active_time_END    (28)


/*****************************************************************************
 结构名    : GSDR_ULFE_SDR_G_CFG_UNION
 结构说明  : ULFE_SDR_G_CFG 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_g_cfg_reg;
    struct
    {
        unsigned int  cpu_ulfe_sdr_g_burst_num : 3;  /* bit[0-2] : G模软化时，发送数据包含的burst个数，取值范围0~5。配置值加1表示实际burst个数。 */
        unsigned int  reserved                 : 29; /* bit[3-31]: 保留 */
    } reg;
} GSDR_ULFE_SDR_G_CFG_UNION;
#define GSDR_ULFE_SDR_G_CFG_cpu_ulfe_sdr_g_burst_num_START  (0)
#define GSDR_ULFE_SDR_G_CFG_cpu_ulfe_sdr_g_burst_num_END    (2)


/*****************************************************************************
 结构名    : GSDR_ULFE_SDR_DUMP_EN_RPT_UNION
 结构说明  : ULFE_SDR_DUMP_EN_RPT 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_dump_en_rpt_reg;
    struct
    {
        unsigned int  ulfe_sdr_dump_en   : 1;  /* bit[0]   : 上行搬运状态。 */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ulfe_sdr_err_sta   : 1;  /* bit[4]   : 上行BBPMaster搬运出错指示。 */
        unsigned int  reserved_1         : 3;  /* bit[5-7] : 保留 */
        unsigned int  ulfe_sdr_trans_sta : 1;  /* bit[8]   : 上行BBPMaster搬运完成指示。 */
        unsigned int  reserved_2         : 23; /* bit[9-31]: 保留 */
    } reg;
} GSDR_ULFE_SDR_DUMP_EN_RPT_UNION;
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_dump_en_START    (0)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_dump_en_END      (0)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_err_sta_START    (4)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_err_sta_END      (4)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_trans_sta_START  (8)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_trans_sta_END    (8)


/***======================================================================***
                     (3/3) register_define_g_dump_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : GSDR_ULFE_SDR_RAM_UNION
 结构说明  : ULFE_SDR_RAM 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_ram_reg;
    struct
    {
        unsigned int  ulfe_sdr_data_i : 12; /* bit[0-11] : C模时，表示上行前端数据I路，12比特有符号数，软件每1/4 PCG或slot写一遍。
                                                           G模软化时，表示上行发送数据I路，12比特有符号数，软件每1/5 burst写一遍。
                                                           C模含义无效。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  ulfe_sdr_data_q : 12; /* bit[16-27]: C模时，表示上行前端数据Q路，12比特有符号数，软件每1/4 PCG或slot写一遍。
                                                           G模软化时，表示上行发送数据Q路，12比特有符号数，软件每1/5 burst写一遍。
                                                           C模含义无效。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} GSDR_ULFE_SDR_RAM_UNION;
#define GSDR_ULFE_SDR_RAM_ulfe_sdr_data_i_START  (0)
#define GSDR_ULFE_SDR_RAM_ulfe_sdr_data_i_END    (11)
#define GSDR_ULFE_SDR_RAM_ulfe_sdr_data_q_START  (16)
#define GSDR_ULFE_SDR_RAM_ulfe_sdr_data_q_END    (27)




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

#endif /* end of bbp_gsdr_interface.h */
