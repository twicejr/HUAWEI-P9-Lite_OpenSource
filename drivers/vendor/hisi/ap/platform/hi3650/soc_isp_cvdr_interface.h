/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_cvdr_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:46:39
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_CVDR.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_CVDR_INTERFACE_H__
#define __SOC_ISP_CVDR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CVDR
 ****************************************************************************/
/* 寄存器说明：CVDR config register.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_CFG_UNION */
#define SOC_ISP_CVDR_CVDR_CFG_ADDR(base)              ((base) + (0x0))

/* 寄存器说明：CVDR debug register enable.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_EN_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_ADDR(base)         ((base) + (0x4))

/* 寄存器说明：CVDR debug register.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_ADDR(base)            ((base) + (0x8))

/* 寄存器说明：AXI QOS configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_QOS_CFG_UNION */
#define SOC_ISP_CVDR_CVDR_QOS_CFG_ADDR(base)          ((base) + (0xC))

/* 寄存器说明：Initiator write Configuration (0x10+0x4*Range).
   位域定义UNION结构:  SOC_ISP_CVDR_NR_WR_CFG_UNION */
#define SOC_ISP_CVDR_NR_WR_CFG_ADDR(base)             ((base) + (0x10))

/* 寄存器说明：Initiator read Configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_NR_RD_CFG_UNION */
#define SOC_ISP_CVDR_NR_RD_CFG_ADDR(base, NR_RD_NBR_range, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR_range)))

/* 寄存器说明：Video port write Configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_WR_CFG_UNION */
#define SOC_ISP_CVDR_VP_WR_CFG_ADDR(base, VP_WR_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR_range)))

/* 寄存器说明：AXI address Frame start.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_WR_AXI_FS_UNION */
#define SOC_ISP_CVDR_VP_WR_AXI_FS_ADDR(base, VP_WR_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x4+0x10*(VP_WR_NBR_range)))

/* 寄存器说明：AXI line wrap and line stride.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_WR_AXI_LINE_UNION */
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_ADDR(base, VP_WR_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x8+0x10*(VP_WR_NBR_range)))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_WR_PREFETCH_UNION */
#define SOC_ISP_CVDR_VP_WR_PREFETCH_ADDR(base, VP_WR_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0xC+0x10*(VP_WR_NBR_range)))

/* 寄存器说明：Video port read Configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_RD_CFG_UNION */
#define SOC_ISP_CVDR_VP_RD_CFG_ADDR(base, VP_WR_NBR, VP_RD_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x20*(VP_RD_NBR_range)))

/* 寄存器说明：Line width generation.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_RD_LWG_UNION */
#define SOC_ISP_CVDR_VP_RD_LWG_ADDR(base, VP_WR_NBR, VP_RD_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x4+0x20*(VP_RD_NBR_range)))

/* 寄存器说明：Frame height generation.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_RD_FHG_UNION */
#define SOC_ISP_CVDR_VP_RD_FHG_ADDR(base, VP_WR_NBR, VP_RD_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x8+0x20*(VP_RD_NBR_range)))

/* 寄存器说明：AXI frame start.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_RD_AXI_FS_UNION */
#define SOC_ISP_CVDR_VP_RD_AXI_FS_ADDR(base, VP_WR_NBR, VP_RD_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0xC+0x20*(VP_RD_NBR_range)))

/* 寄存器说明：Line Wrap definition.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_RD_AXI_LINE_UNION */
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_ADDR(base, VP_WR_NBR, VP_RD_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x10+0x20*(VP_RD_NBR_range)))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_VP_RD_PREFETCH_UNION */
#define SOC_ISP_CVDR_VP_RD_PREFETCH_ADDR(base, VP_WR_NBR, VP_RD_NBR_range, NR_RD_NBR, NR_WR_NBR)  ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x14+0x20*(VP_RD_NBR_range)))

/* 寄存器说明：DEBUG information.
   位域定义UNION结构:  SOC_ISP_CVDR_DEBUG_UNION */
#define SOC_ISP_CVDR_DEBUG_ADDR(base, Range4)         ((base) + (0x310+0x4*(Range4)))

/* 寄存器说明：NR write Master ID.
   位域定义UNION结构:  SOC_ISP_CVDR_AXI_CFG_NR_WR_UNION */
#define SOC_ISP_CVDR_AXI_CFG_NR_WR_ADDR(base)         ((base) + (0x320))

/* 寄存器说明：NR read Master ID.
   位域定义UNION结构:  SOC_ISP_CVDR_AXI_CFG_NR_RD_UNION */
#define SOC_ISP_CVDR_AXI_CFG_NR_RD_ADDR(base, NR_RD_NBR_range)  ((base) + (0x330+0x4*(NR_RD_NBR_range)))

/* 寄存器说明：VP write master ID.
   位域定义UNION结构:  SOC_ISP_CVDR_AXI_CFG_VP_WR_UNION */
#define SOC_ISP_CVDR_AXI_CFG_VP_WR_ADDR(base, VP_WR_NBR_range)  ((base) + (0x350+0x4*(VP_WR_NBR_range)))

/* 寄存器说明：VP read master ID.
   位域定义UNION结构:  SOC_ISP_CVDR_AXI_CFG_VP_RD_UNION */
#define SOC_ISP_CVDR_AXI_CFG_VP_RD_ADDR(base, VP_RD_NBR_range)  ((base) + (0x400+0x4*(VP_RD_NBR_range)))

/* 寄存器说明：Spare.
   位域定义UNION结构:  SOC_ISP_CVDR_SPARE_UNION */
#define SOC_ISP_CVDR_SPARE_ADDR(base, Range4)         ((base) + (0x430+0x4*(Range4)))

/* 寄存器说明：Spare Other RO.
   位域定义UNION结构:  SOC_ISP_CVDR_OTHER_RO_UNION */
#define SOC_ISP_CVDR_OTHER_RO_ADDR(base)              ((base) + (0x440))

/* 寄存器说明：Spare Other RW.
   位域定义UNION结构:  SOC_ISP_CVDR_OTHER_RW_UNION */
#define SOC_ISP_CVDR_OTHER_RW_ADDR(base)              ((base) + (0x444))





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
                     (1/1) CVDR
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_CFG_UNION
 结构说明  : CVDR_CFG 寄存器结构定义。地址偏移量:0x0，初值:0x01002000，宽度:32
 寄存器说明: CVDR config register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  du_write_threshold     : 6;  /* bit[0-5]  : DataUnit write threshold (from 0 to 64) - AXI burst mode
                                                                  This registers enables to define when the AXI write commands must be sent.
                                                                  If the number of valid DUs is higher than the du_write_threshold, then all valid DUs are sent to AXI write interface until no valid DUs are available. */
        unsigned int  reserved_0             : 2;  /* bit[6-7]  :  */
        unsigned int  stall_srt_du_threshold : 8;  /* bit[8-15] : configuration register used to limit the impact of the srt (soft real time) initiators when the system is preforming refresh or any other stall on the DRAM. Once number_busy_write_DUs > stall_srt_du_threshold, then, the srt read and write initiators are stalled (this is replacing the back pressure signal)
                                                                  This register can be used to optimize the CVDR DU usage and "reserve" some DUs to RT path. For configuration, please have a look into the systemC document available under: http://szxsvn09-rd:6801/svn/HIS_RES_SVN/2.CODE/ISP/HiStarISPV100/arch_model/doc/HiStarISPv1_SystemC_modeling.docx. 
                                                                  Default value: 32 */
        unsigned int  max_axiread_id         : 5;  /* bit[16-20]: Maximum value allowed on the ARID to access the memory.
                                                                  0: only value 0x0 is allowed,
                                                                  1: value 0 and 1 are allowed
                                                                  …
                                                                  31: value 0,1, … 31 are allowed (32 transactions)
                                                                  [note]this setting should be not more than h0F (16 transactions maximum at a time). The outstanding num supported by NOC is 16. We also need take the outstanding request of MMU into account.[end] */
        unsigned int  reserved_1             : 3;  /* bit[21-23]:  */
        unsigned int  max_axiwrite_tx        : 5;  /* bit[24-28]: max number of AXI write transactions
                                                                  0: 1 transaction at a time maximum
                                                                  1: 2 transaction at a time maximum
                                                                  …
                                                                  31: 32 transactions maximum at a time (ordered)
                                                                  [note]this setting should be not more than h0B (12 transactions maximum at a time)[end] */
        unsigned int  reserved_2             : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_CFG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_CFG_du_write_threshold_START      (0)
#define SOC_ISP_CVDR_CVDR_CFG_du_write_threshold_END        (5)
#define SOC_ISP_CVDR_CVDR_CFG_stall_srt_du_threshold_START  (8)
#define SOC_ISP_CVDR_CVDR_CFG_stall_srt_du_threshold_END    (15)
#define SOC_ISP_CVDR_CVDR_CFG_max_axiread_id_START          (16)
#define SOC_ISP_CVDR_CVDR_CFG_max_axiread_id_END            (20)
#define SOC_ISP_CVDR_CVDR_CFG_max_axiwrite_tx_START         (24)
#define SOC_ISP_CVDR_CVDR_CFG_max_axiwrite_tx_END           (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_EN_UNION
 结构说明  : CVDR_DEBUG_EN 寄存器结构定义。地址偏移量:0x4，初值:0x00000000，宽度:32
 寄存器说明: CVDR debug register enable.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_peak_en : 1;  /* bit[0]   : Enable the FIFO peak functionality over the write port */
        unsigned int  reserved_0 : 7;  /* bit[1-7] : reserved */
        unsigned int  rd_peak_en : 1;  /* bit[8]   : Enable the FIFO peak functionality over the read port */
        unsigned int  reserved_1 : 23; /* bit[9-31]: reserved */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_EN_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_wr_peak_en_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_wr_peak_en_END    (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_rd_peak_en_START  (8)
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_rd_peak_en_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_UNION
 结构说明  : CVDR_DEBUG 寄存器结构定义。地址偏移量:0x8，初值:0x00000000，宽度:32
 寄存器说明: CVDR debug register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_peak  : 8;  /* bit[0-7]  : Peak number of Data Units used for the write functionality */
        unsigned int  rd_peak  : 8;  /* bit[8-15] : Peak number of Data Units used for the read functionality */
        unsigned int  reserved : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_wr_peak_START   (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_wr_peak_END     (7)
#define SOC_ISP_CVDR_CVDR_DEBUG_rd_peak_START   (8)
#define SOC_ISP_CVDR_CVDR_DEBUG_rd_peak_END     (15)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_QOS_CFG_UNION
 结构说明  : CVDR_QOS_CFG 寄存器结构定义。地址偏移量:0xC，初值:0x79ABFE89，宽度:32
 寄存器说明: AXI QOS configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_qos_rt_default     : 2;  /* bit[0-1]  : QoS Minimum value to send for RT initiators */
        unsigned int  rd_qos_threshold_11   : 3;  /* bit[2-4]  : QOS=11 generated if number of DUs in use is less than the programmed value * 8.
                                                                 When 0: the threshold check is disabled
                                                                 When 7: maximum number of DUs 56 */
        unsigned int  rd_qos_threshold_10   : 3;  /* bit[5-7]  : QOS=10 generated if number of DUs in use is less than the programmed value * 8 */
        unsigned int  rd_qos_threshold_01   : 3;  /* bit[8-10] : QOS=01 generated if number of DUs in use is less than the programmed value * 8 */
        unsigned int  rd_qos_sr             : 2;  /* bit[11-12]: 2 bits register to configure the qos value to generate when pressure from SR is asserted. Note that the qos generated will be the highest value possible between the rd_qos_sr, the qos generated based on bumber of DUs in use and the qos RT default */
        unsigned int  rd_pressure_value     : 2;  /* bit[13-14]: rd_pressure[1:0] value to use when pressure from Stream Router (otherwise value is 2'b00) */
        unsigned int  wr_qos_threshold_11   : 4;  /* bit[15-18]: Threshold level used for Qos generation (based on number of DUs in use). Real value = wr_threshold_qos * 8
                                                                 When 0: The condition is always true
                                                                 1 : 8 DUs
                                                                 ....
                                                                 Values from 11 to 15: are disabling the condition since current implementation has 80 DUs possible */
        unsigned int  wr_qos_threshold_10   : 4;  /* bit[19-22]: Threshold level used for Qos generation (based on number of DUs in use). Real value = wr_threshold_qos * 8 */
        unsigned int  wr_qos_threshold_01   : 4;  /* bit[23-26]: Threshold level used for Qos generation (based on number of DUs in use). Real value = wr_threshold_qos * 8 */
        unsigned int  wr_qos_sr             : 2;  /* bit[27-28]: 2 bits register to configure the qos value to generate when pressure from SR is asserted. Note that the qos generated will be the highest value possible between the wr_qos_sr and the qos generated based on bumber of DUs in use  */
        unsigned int  wr_pressure_value     : 2;  /* bit[29-30]: wr_pressure[1:0] value to use when pressure from Stream Router or when number of DUs in use = max allowed DU nbr (effect can be masked using wr_pressure_cvdr_mask) (otherwise value is 2'b00) */
        unsigned int  wr_pressure_cvdr_mask : 1;  /* bit[31]   : mask used to generated or not the write pressure when the number of Write DUs = max allowed DU nbr */
    } reg;
} SOC_ISP_CVDR_CVDR_QOS_CFG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_rt_default_START      (0)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_rt_default_END        (1)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_11_START    (2)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_11_END      (4)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_10_START    (5)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_10_END      (7)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_01_START    (8)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_01_END      (10)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_sr_START              (11)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_sr_END                (12)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_pressure_value_START      (13)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_pressure_value_END        (14)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_11_START    (15)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_11_END      (18)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_10_START    (19)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_10_END      (22)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_01_START    (23)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_01_END      (26)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_sr_START              (27)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_sr_END                (28)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_pressure_value_START      (29)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_pressure_value_END        (30)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_pressure_cvdr_mask_START  (31)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_pressure_cvdr_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_NR_WR_CFG_UNION
 结构说明  : NR_WR_CFG 寄存器结构定义。地址偏移量:0x10，初值:0x00001E00，宽度:32
 寄存器说明: Initiator write Configuration (0x10+0x4*Range).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 9;  /* bit[0-8]  : reserved */
        unsigned int  nrwr_access_limiter : 4;  /* bit[9-12] : CVDR RAM access limiter: maximum number of write 128 bit accesses allowed on a 32 clock cycle window
                                                               0: no access limiter (all requests are accepted - unexpected in regular SW)
                                                               1: 1 access maximum allowed
                                                               …
                                                               15: 15 accesses maximum allowed */
        unsigned int  reserved_1          : 18; /* bit[13-30]: reserved */
        unsigned int  nrwr_enable         : 1;  /* bit[31]   : Enable or stop the initiator acquisition (at any time) */
    } reg;
} SOC_ISP_CVDR_NR_WR_CFG_UNION;
#endif
#define SOC_ISP_CVDR_NR_WR_CFG_nrwr_access_limiter_START  (9)
#define SOC_ISP_CVDR_NR_WR_CFG_nrwr_access_limiter_END    (12)
#define SOC_ISP_CVDR_NR_WR_CFG_nrwr_enable_START          (31)
#define SOC_ISP_CVDR_NR_WR_CFG_nrwr_enable_END            (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_NR_RD_CFG_UNION
 结构说明  : NR_RD_CFG 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR_range)，初值:0x00003C00，宽度:32
 寄存器说明: Initiator read Configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 5;  /* bit[0-4]  : reserved */
        unsigned int  nrrd_allocated_du   : 5;  /* bit[5-9]  : Number of allocated DUs
                                                               A maximum of 32 DUs can be allocated per non-raster port
                                                               [note]it is only the maximum num. The real num used by this port also is based on the arbitration[end] */
        unsigned int  nrrd_access_limiter : 4;  /* bit[10-13]: CVDR RAM access limiter: maximum number of read 128 bit accesses allowed on a 32 clock cycle window
                                                               0: no access limiter (all requests are accepted - unexpected in regular SW)
                                                               1: 1 access maximum allowed
                                                               …
                                                               15: 15 accesses maximum allowed */
        unsigned int  reserved_1          : 17; /* bit[14-30]: reserved */
        unsigned int  nrrd_enable         : 1;  /* bit[31]   : Enable or stop the initiator acquisition (at any time) */
    } reg;
} SOC_ISP_CVDR_NR_RD_CFG_UNION;
#endif
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_allocated_du_START    (5)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_allocated_du_END      (9)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_access_limiter_START  (10)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_access_limiter_END    (13)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_enable_START          (31)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_enable_END            (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_WR_CFG_UNION
 结构说明  : VP_WR_CFG 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR_range)，初值:0x00001E00，宽度:32
 寄存器说明: Video port write Configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format    : 4;  /* bit[0-3]  : Pixel formats supported (see ref. [1])
                                                                "0:3->1PF8:1PF14 ; 4:7->2PF8:2PF14 ; 9:11->3PF8:3PF14 ; 12:D32 ; 13:D48 ; 14 D64";
                                                                [note]the supported format for every port, please refer to the document "HiStarISPv1_Toplevel_FS_Specification_tables.xlsx"[end] */
        unsigned int  vpwr_pixel_expansion : 1;  /* bit[4]    : Pixel expansion can be used (see ref. [1]) */
        unsigned int  reserved_0           : 4;  /* bit[5-8]  : reserved */
        unsigned int  vpwr_access_limiter  : 4;  /* bit[9-12] : CVDR RAM access limiter: maximum number of 128 bit write accesses allowed on a 32 clock cycle window
                                                                0: 0 access allowed (unexpected in regular SW)
                                                                1: 1 access maximum allowed
                                                                …
                                                                15: 15 accesses maximum allowed */
        unsigned int  reserved_1           : 2;  /* bit[13-14]:  */
        unsigned int  vpwr_last_page       : 17; /* bit[15-31]: last 32KB page reserved to write the data. This page is not necessarely prefetched but is the last page reserved by the Software.
                                                                The CVDR must prefetch the page used by the frame start (back to initial - in case of continuous mode) once the last page is equal to vpwr_last_page. 
                                                                This info must be aligned with the frame size (SW info) and the vpwr_line_wrap info (SW and HW) to be aligned with buffer size reserved by the SW.
                                                                Specific case: long lines in 1 frame are possible (Jpeg case, 3A/DIS, debug): vpwr_line_wrap=0 and vpwr_last_page will be different from the page used by vpwr_address_frame_start. In this case, the module must be able to prefetch continuously until the vpwr_last_page and get back to initial page to prepare continuous write operation. 
                                                                [note]In case of YUV420, UV data is bigger than needed, 1 additional line is received, and this register must be configured accordingly.
                                                                We can calculate the memory address of last pixel and use the 32KB address including it as the setting of last page. When calculate the memory address of last pixel, please note the line stride. If line stride is 0, the start address of the next line will start at next 128B boundry.
                                                                [end] */
    } reg;
} SOC_ISP_CVDR_VP_WR_CFG_UNION;
#endif
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_pixel_format_START     (0)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_pixel_format_END       (3)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_pixel_expansion_START  (4)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_pixel_expansion_END    (4)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_access_limiter_START   (9)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_access_limiter_END     (12)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_last_page_START        (15)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_last_page_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_WR_AXI_FS_UNION
 结构说明  : VP_WR_AXI_FS 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x4+0x10*(VP_WR_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                 : 4;  /* bit[0-3] : reserved */
        unsigned int  vpwr_address_frame_start : 28; /* bit[4-31]: Start address of the frame (in 16 bytes boundary).
                                                                   Since we are 128-bits, the 4 lowest bits on the AXI address are always 0. */
    } reg;
} SOC_ISP_CVDR_VP_WR_AXI_FS_UNION;
#endif
#define SOC_ISP_CVDR_VP_WR_AXI_FS_vpwr_address_frame_start_START  (4)
#define SOC_ISP_CVDR_VP_WR_AXI_FS_vpwr_address_frame_start_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_WR_AXI_LINE_UNION
 结构说明  : VP_WR_AXI_LINE 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x8+0x10*(VP_WR_NBR_range)，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride : 10; /* bit[0-9]  : Stride to use on line starts (aligned to a 16 byte boundary: Max stride of 16 KBytes)
                                                            0: line stride disabled (continuous) (continuous mode : next line will start on a 128 bytes boundary)
                                                            1: 2*16 bytes
                                                            …
                                                            1023 : 1024*16 bytes */
        unsigned int  reserved_0       : 5;  /* bit[10-14]: reserved */
        unsigned int  vpwr_line_wrap   : 14; /* bit[15-28]: Line wrap: wrap to frame start location (14 bits)
                                                            0: wrap every line
                                                            1: wrap every 2 lines
                                                            …
                                                            0x3FFF: wrap every 16384 lines
                                                            In case of YUV420, UV data is bigger than needed, 1 additional line is received, and this register must be configured accordingly.
                                                            [note]if the wrap function is enalbe (frame size is less then line_wrap setting), prefetch bypass must be enable[end] */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_CVDR_VP_WR_AXI_LINE_UNION;
#endif
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_vpwr_line_stride_START  (0)
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_vpwr_line_stride_END    (9)
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_vpwr_line_wrap_START    (15)
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_vpwr_line_wrap_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_WR_PREFETCH_UNION
 结构说明  : VP_WR_PREFETCH 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0xC+0x10*(VP_WR_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0       : 7;  /* bit[0-6]  : configurable index ID 0 */
        unsigned int  reserved_0           : 1;  /* bit[7]    :  */
        unsigned int  vpwr_index_id1       : 7;  /* bit[8-14] : configurable index ID 1 */
        unsigned int  reserved_1           : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass : 1;  /* bit[31]   : Enables to bypass the prefetch mechanism.
                                                                0: prefetch functionality is enabled
                                                                1: prefetch functionality is bypassed (Stream ID is always stream_id0) */
    } reg;
} SOC_ISP_CVDR_VP_WR_PREFETCH_UNION;
#endif
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_index_id0_START        (0)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_index_id0_END          (6)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_index_id1_START        (8)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_index_id1_END          (14)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_prefetch_bypass_START  (31)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_prefetch_bypass_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_RD_CFG_UNION
 结构说明  : VP_RD_CFG 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x20*(VP_RD_NBR_range)，初值:0x00003C00，宽度:32
 寄存器说明: Video port read Configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format    : 4;  /* bit[0-3]  : Pixel formats supported (see ref. [1])
                                                                "0:3->1PF8:1PF14 ; 4:7->2PF8:2PF14 ; 9:11->3PF8:3PF14 ; 12:D32 ; 13:D48 ; 14 D64";
                                                                [note]the supported format for every port, please refer to the document "HiStarISPv1_Toplevel_FS_Specification_tables.xlsx"[end] */
        unsigned int  vprd_pixel_expansion : 1;  /* bit[4]    : Pixel expansion can be used (see ref. [1]) */
        unsigned int  vprd_allocated_du    : 5;  /* bit[5-9]  : Number of allocated DUs
                                                                A maximum of 32 DUs can be allocated per video port
                                                                [note]it is only the maximum num. The real num used by this port also is based on the arbitration[end] */
        unsigned int  vprd_access_limiter  : 4;  /* bit[10-13]: CVDR RAM access limiter: maximum number of read 128 bit accesses allowed on a 32 clock cycle window
                                                                0: 0 access allowed (unexpected in regular SW)
                                                                1: 1 access maximum allowed
                                                                …
                                                                15: 15 accesses maximum allowed */
        unsigned int  reserved             : 1;  /* bit[14]   : - */
        unsigned int  vprd_last_page       : 17; /* bit[15-31]: last 32KB page reserved to read the data. This page is not necessarely prefetched but is the last page reserved by the Software.
                                                                The CVDR must prefetch the page used by the frame start (back to initial - in case of continuous mode) once the last page is equal to vprd_last_page. 
                                                                This info must be aligned with the frame size (SW info) and the vprd_line_wrap info (SW and HW) to be aligned with buffer size reserved by the SW.
                                                                [note]We can calculate the memory address of last pixel and use the 32KB address including it as the setting of last page. When calculate the memory address of last pixel, please note the line stride. If line stride is 0, the start address of the next line will start at next 128B boundry.[end] */
    } reg;
} SOC_ISP_CVDR_VP_RD_CFG_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_pixel_format_START     (0)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_pixel_format_END       (3)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_pixel_expansion_START  (4)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_pixel_expansion_END    (4)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_allocated_du_START     (5)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_allocated_du_END       (9)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_access_limiter_START   (10)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_access_limiter_END     (13)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_last_page_START        (15)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_last_page_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_RD_LWG_UNION
 结构说明  : VP_RD_LWG 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x4+0x20*(VP_RD_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: Line width generation.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size           : 13; /* bit[0-12] : number of pixels per line (up to 8192 pixels) */
        unsigned int  reserved_0               : 3;  /* bit[13-15]: reserved */
        unsigned int  vprd_horizontal_blanking : 8;  /* bit[16-23]: Horizontal blanking (number of clock cycles between 2 lines)
                                                                    up to 256 clock cycles */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_ISP_CVDR_VP_RD_LWG_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_LWG_vprd_line_size_START            (0)
#define SOC_ISP_CVDR_VP_RD_LWG_vprd_line_size_END              (12)
#define SOC_ISP_CVDR_VP_RD_LWG_vprd_horizontal_blanking_START  (16)
#define SOC_ISP_CVDR_VP_RD_LWG_vprd_horizontal_blanking_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_RD_FHG_UNION
 结构说明  : VP_RD_FHG 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x8+0x20*(VP_RD_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size        : 13; /* bit[0-12] : number of lines per frame (up to 8192 lines) */
        unsigned int  reserved_0             : 3;  /* bit[13-15]: reserved */
        unsigned int  vprd_vertical_blanking : 8;  /* bit[16-23]: Vertical blanking (number of dummy lines between 2 frames)
                                                                  up to 256 lines */
        unsigned int  reserved_1             : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_ISP_CVDR_VP_RD_FHG_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_FHG_vprd_frame_size_START         (0)
#define SOC_ISP_CVDR_VP_RD_FHG_vprd_frame_size_END           (12)
#define SOC_ISP_CVDR_VP_RD_FHG_vprd_vertical_blanking_START  (16)
#define SOC_ISP_CVDR_VP_RD_FHG_vprd_vertical_blanking_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_RD_AXI_FS_UNION
 结构说明  : VP_RD_AXI_FS 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0xC+0x20*(VP_RD_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved             : 4;  /* bit[0-3] : reserved */
        unsigned int  vprd_axi_frame_start : 28; /* bit[4-31]: Start address of the frame (in 16 bytes boundary).
                                                               Since we are 128-bits, the 4 lowest bits on the AXI address are always 0. */
    } reg;
} SOC_ISP_CVDR_VP_RD_AXI_FS_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_AXI_FS_vprd_axi_frame_start_START  (4)
#define SOC_ISP_CVDR_VP_RD_AXI_FS_vprd_axi_frame_start_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_RD_AXI_LINE_UNION
 结构说明  : VP_RD_AXI_LINE 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x10+0x20*(VP_RD_NBR_range)，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride : 10; /* bit[0-9]  : Stride to use on line starts (aligned to a 16 byte boundary: Max stride of 16 KBytes)
                                                            0: line stride disabled (continuous) (continuous mode : next line will start on a 128 bytes boundary)
                                                            1: 2*16 bytes
                                                            …
                                                            1023 : 1024*16 bytes */
        unsigned int  reserved_0       : 6;  /* bit[10-15]: reserved */
        unsigned int  vprd_line_wrap   : 13; /* bit[16-28]: Line wrap: wrap to frame start location (13 bits)
                                                            0: wrap every line
                                                            1: wrap every 2 lines
                                                            …
                                                            8191: wrap every 8192 lines
                                                            [note]if the wrap function is enalbe (frame size is less then line_wrap setting), prefetch bypass must be enable[end] */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_CVDR_VP_RD_AXI_LINE_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_vprd_line_stride_START  (0)
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_vprd_line_stride_END    (9)
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_vprd_line_wrap_START    (16)
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_vprd_line_wrap_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_VP_RD_PREFETCH_UNION
 结构说明  : VP_RD_PREFETCH 寄存器结构定义。地址偏移量:0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x14+0x20*(VP_RD_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0       : 7;  /* bit[0-6]  : configurable index ID 0 */
        unsigned int  reserved_0           : 1;  /* bit[7]    :  */
        unsigned int  vprd_index_id1       : 7;  /* bit[8-14] : configurable index ID 1 */
        unsigned int  reserved_1           : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass : 1;  /* bit[31]   : Enables to bypass the prefetch mechanism.
                                                                0: prefetch functionality is enabled
                                                                1: prefetch functionality is bypassed (Stream ID is always stream_id0) */
    } reg;
} SOC_ISP_CVDR_VP_RD_PREFETCH_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_index_id0_START        (0)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_index_id0_END          (6)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_index_id1_START        (8)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_index_id1_END          (14)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_prefetch_bypass_START  (31)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_prefetch_bypass_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_DEBUG_UNION
 结构说明  : DEBUG 寄存器结构定义。地址偏移量:0x310+0x4*(Range4)，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_info : 32; /* bit[0-31]: debug0 register:
                                                      vpwr debug info (VP 0)
                                                      1: pixel_buf_valid_for_app
                                                      0: pixel_buf_valid
                                                      AXI Read Interface module
                                                      11:6: rd_axiq_rs_cnt
                                                      5:0: rd_axiq_cnt
                                                      AXI Write Interface module.
                                                      17:12: wr_axi_dvld_cnt
                                                      11:6: wr_axiq_rs_cnt
                                                      5:0: wr_axiq_cnt
                                                     debug1:
                                                      vpwr debug info (VP 1 to VP 16)
                                                      1: pixel_buf_valid_for_app
                                                      0: pixel_buf_valid
                                                     debug2: 
                                                      vprd debug info (VP 0 to VP 6)
                                                      1: vprd_du_req
                                                      0: du_apply_flag
                                                      vpwr debug info (VP 17 to VP 25)
                                                      1: pixel_buf_valid_for_app
                                                      0: pixel_buf_valid
                                                     debug3:
                                                      Accept signal on VP write ports
                                                      vprd debug info (VP 7 to VP 9)
                                                      1: vprd_du_req
                                                      0: du_apply_flag */
    } reg;
} SOC_ISP_CVDR_DEBUG_UNION;
#endif
#define SOC_ISP_CVDR_DEBUG_debug_info_START  (0)
#define SOC_ISP_CVDR_DEBUG_debug_info_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_AXI_CFG_NR_WR_UNION
 结构说明  : AXI_CFG_NR_WR 寄存器结构定义。地址偏移量:0x320，初值:0x0000000A，宽度:32
 寄存器说明: NR write Master ID.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nr_wr_mid : 5;  /* bit[0-4] : Master ID configuration register. A MID information is attached to AXI transactions (Commands) for SOC debug purpose
                                                    [note]about the available setting, please refer to "austin mid allocation table"[end] */
        unsigned int  reserved  : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_CVDR_AXI_CFG_NR_WR_UNION;
#endif
#define SOC_ISP_CVDR_AXI_CFG_NR_WR_nr_wr_mid_START  (0)
#define SOC_ISP_CVDR_AXI_CFG_NR_WR_nr_wr_mid_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_AXI_CFG_NR_RD_UNION
 结构说明  : AXI_CFG_NR_RD 寄存器结构定义。地址偏移量:0x330+0x4*(NR_RD_NBR_range)，初值:0x0000000B，宽度:32
 寄存器说明: NR read Master ID.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nr_rd_mid : 5;  /* bit[0-4] : Master ID configuration register. A MID information is attached to AXI transactions (Commands) for SOC debug purpose
                                                    [note]about the available setting, please refer to "austin mid allocation table"[end] */
        unsigned int  reserved  : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_CVDR_AXI_CFG_NR_RD_UNION;
#endif
#define SOC_ISP_CVDR_AXI_CFG_NR_RD_nr_rd_mid_START  (0)
#define SOC_ISP_CVDR_AXI_CFG_NR_RD_nr_rd_mid_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_AXI_CFG_VP_WR_UNION
 结构说明  : AXI_CFG_VP_WR 寄存器结构定义。地址偏移量:0x350+0x4*(VP_WR_NBR_range)，初值:0x0000000C，宽度:32
 寄存器说明: VP write master ID.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid : 5;  /* bit[0-4] : Master ID configuration register. A MID information is attached to AXI transactions (Commands) for SOC debug purpose
                                                    [note]about the available setting, please refer to "austin mid allocation table"[end] */
        unsigned int  reserved  : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_CVDR_AXI_CFG_VP_WR_UNION;
#endif
#define SOC_ISP_CVDR_AXI_CFG_VP_WR_vp_wr_mid_START  (0)
#define SOC_ISP_CVDR_AXI_CFG_VP_WR_vp_wr_mid_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_AXI_CFG_VP_RD_UNION
 结构说明  : AXI_CFG_VP_RD 寄存器结构定义。地址偏移量:0x400+0x4*(VP_RD_NBR_range)，初值:0x0000000D，宽度:32
 寄存器说明: VP read master ID.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid : 5;  /* bit[0-4] : Master ID configuration register. A MID information is attached to AXI transactions (Commands) for SOC debug purpose
                                                    [note]about the available setting, please refer to "austin mid allocation table"[end] */
        unsigned int  reserved  : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_CVDR_AXI_CFG_VP_RD_UNION;
#endif
#define SOC_ISP_CVDR_AXI_CFG_VP_RD_vp_rd_mid_START  (0)
#define SOC_ISP_CVDR_AXI_CFG_VP_RD_vp_rd_mid_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_SPARE_UNION
 结构说明  : SPARE 寄存器结构定义。地址偏移量:0x430+0x4*(Range4)，初值:0x00000000，宽度:32
 寄存器说明: Spare.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spare : 32; /* bit[0-31]: spare register for ECOs */
    } reg;
} SOC_ISP_CVDR_SPARE_UNION;
#endif
#define SOC_ISP_CVDR_SPARE_spare_START  (0)
#define SOC_ISP_CVDR_SPARE_spare_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_OTHER_RO_UNION
 结构说明  : OTHER_RO 寄存器结构定义。地址偏移量:0x440，初值:0x00000000，宽度:32
 寄存器说明: Spare Other RO.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  other_ro : 32; /* bit[0-31]: [0]: after set other_rw[0] to be 1'b1, when read other_ro[0]'s value is 1'b1, it indicates that CVDR has no outstanding AXI request;
                                                   [31:1]: reserved, not used; */
    } reg;
} SOC_ISP_CVDR_OTHER_RO_UNION;
#endif
#define SOC_ISP_CVDR_OTHER_RO_other_ro_START  (0)
#define SOC_ISP_CVDR_OTHER_RO_other_ro_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_OTHER_RW_UNION
 结构说明  : OTHER_RW 寄存器结构定义。地址偏移量:0x444，初值:0x00000000，宽度:32
 寄存器说明: Spare Other RW.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  other_rw : 32; /* bit[0-31]: [0]: if need reset CVDR, need set this bit to be 1'b1, then wait other_ro[0] to be 1'b1;
                                                   [31:1]: reserved, not used;
                                                   [note]when set [0] bit to start reset flow, please do not change its value again. It will be clear auto by reset operation[end] */
    } reg;
} SOC_ISP_CVDR_OTHER_RW_UNION;
#endif
#define SOC_ISP_CVDR_OTHER_RW_other_rw_START  (0)
#define SOC_ISP_CVDR_OTHER_RW_other_rw_END    (31)






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

#endif /* end of soc_isp_cvdr_interface.h */
