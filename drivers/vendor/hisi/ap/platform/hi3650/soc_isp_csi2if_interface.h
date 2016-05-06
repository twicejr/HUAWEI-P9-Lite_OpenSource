/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_csi2if_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:29
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_CSI2IF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_CSI2IF_INTERFACE_H__
#define __SOC_ISP_CSI2IF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CSI2IF_4DL
 ****************************************************************************/
/* 寄存器说明：Version of the CSI-2 host controller
   位域定义UNION结构:  SOC_ISP_CSI2IF_VERSION_UNION */
#define SOC_ISP_CSI2IF_VERSION_ADDR(base)             ((base) + (0x0))

/* 寄存器说明：Number of active data lanes
   位域定义UNION结构:  SOC_ISP_CSI2IF_N_LANES_UNION */
#define SOC_ISP_CSI2IF_N_LANES_ADDR(base)             ((base) + (0x4))

/* 寄存器说明：D-PHY shutdown control
   位域定义UNION结构:  SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_UNION */
#define SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_ADDR(base)       ((base) + (0x8))

/* 寄存器说明：D-PHY reset control
   位域定义UNION结构:  SOC_ISP_CSI2IF_DPHY_RSTZ_UNION */
#define SOC_ISP_CSI2IF_DPHY_RSTZ_ADDR(base)           ((base) + (0xC))

/* 寄存器说明：CSI-2 controller reset
   位域定义UNION结构:  SOC_ISP_CSI2IF_CSI2_RESETN_UNION */
#define SOC_ISP_CSI2IF_CSI2_RESETN_ADDR(base)         ((base) + (0x10))

/* 寄存器说明：General settings for all blocks
   位域定义UNION结构:  SOC_ISP_CSI2IF_PHY_STATE_UNION */
#define SOC_ISP_CSI2IF_PHY_STATE_ADDR(base)           ((base) + (0x14))

/* 寄存器说明：Data IDs for which IDI reports line boundary matching errors
   位域定义UNION结构:  SOC_ISP_CSI2IF_DATA_IDS_1_UNION */
#define SOC_ISP_CSI2IF_DATA_IDS_1_ADDR(base)          ((base) + (0x18))

/* 寄存器说明：Error state register 1
   位域定义UNION结构:  SOC_ISP_CSI2IF_ERR1_UNION */
#define SOC_ISP_CSI2IF_ERR1_ADDR(base)                ((base) + (0x20))

/* 寄存器说明：Error state register 2
   位域定义UNION结构:  SOC_ISP_CSI2IF_ERR2_UNION */
#define SOC_ISP_CSI2IF_ERR2_ADDR(base)                ((base) + (0x24))

/* 寄存器说明：Masks for errors 1
   位域定义UNION结构:  SOC_ISP_CSI2IF_MASK1_UNION */
#define SOC_ISP_CSI2IF_MASK1_ADDR(base)               ((base) + (0x28))

/* 寄存器说明：Masks for errors 2
   位域定义UNION结构:  SOC_ISP_CSI2IF_MASK2_UNION */
#define SOC_ISP_CSI2IF_MASK2_ADDR(base)               ((base) + (0x2C))

/* 寄存器说明：D-PHY Test interface control 0
   位域定义UNION结构:  SOC_ISP_CSI2IF_PHY_TEST_CTRL0_UNION */
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_ADDR(base)      ((base) + (0x30))

/* 寄存器说明：D-PHY Test interface control 1
   位域定义UNION结构:  SOC_ISP_CSI2IF_PHY_TEST_CTRL1_UNION */
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_ADDR(base)      ((base) + (0x34))





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
                     (1/1) CSI2IF_4DL
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_VERSION_UNION
 结构说明  : VERSION 寄存器结构定义。地址偏移量:0x0，初值:0x3130342A，宽度:32
 寄存器说明: Version of the CSI-2 host controller
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version : 32; /* bit[0-31]: Version of the DWC_mipi_csi2_host (Value after Reset: CSI_VERSION_ID) */
    } reg;
} SOC_ISP_CSI2IF_VERSION_UNION;
#endif
#define SOC_ISP_CSI2IF_VERSION_version_START  (0)
#define SOC_ISP_CSI2IF_VERSION_version_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_N_LANES_UNION
 结构说明  : N_LANES 寄存器结构定义。地址偏移量:0x4，初值:0x00000003，宽度:32
 寄存器说明: Number of active data lanes
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  n_lanes  : 2;  /* bit[0-1] : Number of active data lanes (Value after Reset: CSI2_HOST_NUMBER_OF_LANES-1)
                                                   - 00: 1 data lane (lane 0)
                                                   - 01: 2 data lanes (lanes 0 and 1)
                                                   - 10: 3 data lanes (lanes 0, 1, and 2)
                                                   - 11: 4 data lanes (All)
                                                   Can only be updated when the D-PHY lane is in Stop state. */
        unsigned int  reserved : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_CSI2IF_N_LANES_UNION;
#endif
#define SOC_ISP_CSI2IF_N_LANES_n_lanes_START   (0)
#define SOC_ISP_CSI2IF_N_LANES_n_lanes_END     (1)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_UNION
 结构说明  : PHY_SHUTDOWNZ 寄存器结构定义。地址偏移量:0x8，初值:0x00000000，宽度:32
 寄存器说明: D-PHY shutdown control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_shutdownz : 1;  /* bit[0]   : Shutdown input
                                                        This line is used to place the complete macro in power down. All
                                                        analog blocks are in power down mode and digital logic is cleared.
                                                        Active Low. */
        unsigned int  reserved      : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_UNION;
#endif
#define SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_phy_shutdownz_START  (0)
#define SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_phy_shutdownz_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_DPHY_RSTZ_UNION
 结构说明  : DPHY_RSTZ 寄存器结构定义。地址偏移量:0xC，初值:0x00000000，宽度:32
 寄存器说明: D-PHY reset control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dphy_rstz : 1;  /* bit[0]   : D-PHY reset output. Active Low. */
        unsigned int  reserved  : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_CSI2IF_DPHY_RSTZ_UNION;
#endif
#define SOC_ISP_CSI2IF_DPHY_RSTZ_dphy_rstz_START  (0)
#define SOC_ISP_CSI2IF_DPHY_RSTZ_dphy_rstz_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_CSI2_RESETN_UNION
 结构说明  : CSI2_RESETN 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: CSI-2 controller reset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csi2_resetn : 1;  /* bit[0]   : CSI-2 controller reset output. Active Low. */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_CSI2IF_CSI2_RESETN_UNION;
#endif
#define SOC_ISP_CSI2IF_CSI2_RESETN_csi2_resetn_START  (0)
#define SOC_ISP_CSI2IF_CSI2_RESETN_csi2_resetn_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_PHY_STATE_UNION
 结构说明  : PHY_STATE 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: General settings for all blocks
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_rxulpsesc_0     : 1;  /* bit[0]    : Lane module 0 has entered the Ultra Low Power mode */
        unsigned int  phy_rxulpsesc_1     : 1;  /* bit[1]    : Lane module 1 has entered the Ultra Low Power mode */
        unsigned int  phy_rxulpsesc_2     : 1;  /* bit[2]    : Lane module 2 has entered the Ultra Low Power mode */
        unsigned int  phy_rxulpsesc_3     : 1;  /* bit[3]    : Lane module 3 has entered the Ultra Low Power mode */
        unsigned int  phy_stopstatedata_0 : 1;  /* bit[4]    : Data lane 0 in Stop state */
        unsigned int  phy_stopstatedata_1 : 1;  /* bit[5]    : Data lane 1 in Stop state */
        unsigned int  phy_stopstatedata_2 : 1;  /* bit[6]    : Data lane 2 in Stop state */
        unsigned int  phy_stopstatedata_3 : 1;  /* bit[7]    : Data lane 3 in Stop state */
        unsigned int  phy_rxclkactivehs   : 1;  /* bit[8]    : Indicates that the clock lane is actively receiving a DDR clock */
        unsigned int  phy_rxulpsclknot    : 1;  /* bit[9]    : This signal indicates that the clock lane module has entered the Ultra Low Power state. Active low. */
        unsigned int  phy_stopstateclk    : 1;  /* bit[10]   : Clock lane in Stop state */
        unsigned int  reserved            : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_CSI2IF_PHY_STATE_UNION;
#endif
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_0_START      (0)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_0_END        (0)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_1_START      (1)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_1_END        (1)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_2_START      (2)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_2_END        (2)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_3_START      (3)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_3_END        (3)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_0_START  (4)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_0_END    (4)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_1_START  (5)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_1_END    (5)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_2_START  (6)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_2_END    (6)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_3_START  (7)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_3_END    (7)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxclkactivehs_START    (8)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxclkactivehs_END      (8)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsclknot_START     (9)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsclknot_END       (9)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstateclk_START     (10)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstateclk_END       (10)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_DATA_IDS_1_UNION
 结构说明  : DATA_IDS_1 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: Data IDs for which IDI reports line boundary matching errors
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  di0_dt : 6;  /* bit[0-5]  : Data ID 0 data Type */
        unsigned int  di0_vc : 2;  /* bit[6-7]  : Data ID 0 virtual channel */
        unsigned int  di1_dt : 6;  /* bit[8-13] : Data ID 1 data Type */
        unsigned int  di1_vc : 2;  /* bit[14-15]: Data ID 1 virtual channel */
        unsigned int  di2_dt : 6;  /* bit[16-21]: Data ID 2 data Type */
        unsigned int  di2_vc : 2;  /* bit[22-23]: Data ID 2 virtual channel */
        unsigned int  di3_dt : 6;  /* bit[24-29]: Data ID 3 data Type */
        unsigned int  di3_vc : 2;  /* bit[30-31]: Data ID 3 virtual channel */
    } reg;
} SOC_ISP_CSI2IF_DATA_IDS_1_UNION;
#endif
#define SOC_ISP_CSI2IF_DATA_IDS_1_di0_dt_START  (0)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di0_dt_END    (5)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di0_vc_START  (6)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di0_vc_END    (7)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di1_dt_START  (8)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di1_dt_END    (13)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di1_vc_START  (14)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di1_vc_END    (15)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di2_dt_START  (16)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di2_dt_END    (21)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di2_vc_START  (22)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di2_vc_END    (23)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di3_dt_START  (24)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di3_dt_END    (29)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di3_vc_START  (30)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di3_vc_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_ERR1_UNION
 结构说明  : ERR1 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: Error state register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_errsotsynchs_0    : 1;  /* bit[0]    : Start of transmission error on data lane 0 (no synchronization achieved) */
        unsigned int  phy_errsotsynchs_1    : 1;  /* bit[1]    : Start of transmission error on data lane 1 (no synchronization achieved) */
        unsigned int  phy_errsotsynchs_2    : 1;  /* bit[2]    : Start of transmission error on data lane 2 (no synchronization achieved) */
        unsigned int  phy_errsotsynchs_3    : 1;  /* bit[3]    : Start of transmission error on data lane 3 (no synchronization achieved) */
        unsigned int  err_f_bndry_match_vc0 : 1;  /* bit[4]    : Error matching frame start with frame end for virtual channel 0 */
        unsigned int  err_f_bndry_match_vc1 : 1;  /* bit[5]    : Error matching frame start with frame end for virtual channel 1 */
        unsigned int  err_f_bndry_match_vc2 : 1;  /* bit[6]    : Error matching frame start with frame end for virtual channel 2 */
        unsigned int  err_f_bndry_match_vc3 : 1;  /* bit[7]    : Error matching frame start with frame end for virtual channel 3 */
        unsigned int  err_f_seq_vc0         : 1;  /* bit[8]    : Incorrect frame sequence detected in virtual channel 0 */
        unsigned int  err_f_seq_vc1         : 1;  /* bit[9]    : Incorrect frame sequence detected in virtual channel 1 */
        unsigned int  err_f_seq_vc2         : 1;  /* bit[10]   : Incorrect frame sequence detected in virtual channel 2 */
        unsigned int  err_f_seq_vc3         : 1;  /* bit[11]   : Incorrect frame sequence detected in virtual channel 3 */
        unsigned int  err_frame_data_vc0    : 1;  /* bit[12]   : Last received frame, in virtual channel 0, had at least one CRC error */
        unsigned int  err_frame_data_vc1    : 1;  /* bit[13]   : Last received frame, in virtual channel 1, had at least one CRC error */
        unsigned int  err_frame_data_vc2    : 1;  /* bit[14]   : Last received frame, in virtual channel 2, had at least one CRC error */
        unsigned int  err_frame_data_vc3    : 1;  /* bit[15]   : Last received frame, in virtual channel 3, had at least one CRC error */
        unsigned int  err_l_bndry_match_di0 : 1;  /* bit[16]   : Error matching line start with line end for vc0 and dt0 */
        unsigned int  err_l_bndry_match_di1 : 1;  /* bit[17]   : Error matching line start with line end for vc1 and dt1 */
        unsigned int  err_l_bndry_match_di2 : 1;  /* bit[18]   : Error matching line start with line end for vc2 and dt2 */
        unsigned int  err_l_bndry_match_di3 : 1;  /* bit[19]   : Error matching line start with line end for vc3 and dt3 */
        unsigned int  err_l_seq_di0         : 1;  /* bit[20]   : Error in the sequence of lines for vc0 and dt0 */
        unsigned int  err_l_seq_di1         : 1;  /* bit[21]   : Error in the sequence of lines for vc1 and dt1 */
        unsigned int  err_l_seq_di2         : 1;  /* bit[22]   : Error in the sequence of lines for vc2 and dt2 */
        unsigned int  err_l_seq_di3         : 1;  /* bit[23]   : Error in the sequence of lines for vc3 and dt3 */
        unsigned int  vc0_err_crc           : 1;  /* bit[24]   : Checksum error detected on virtual channel 0 */
        unsigned int  vc1_err_crc           : 1;  /* bit[25]   : Checksum error detected on virtual channel 1 */
        unsigned int  vc2_err_crc           : 1;  /* bit[26]   : Checksum error detected on virtual channel 2 */
        unsigned int  vc3_err_crc           : 1;  /* bit[27]   : Checksum error detected on virtual channel 3 */
        unsigned int  err_ecc_double        : 1;  /* bit[28]   : Header ECC contains 2 errors, unrecoverable */
        unsigned int  reserved              : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CSI2IF_ERR1_UNION;
#endif
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_0_START     (0)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_0_END       (0)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_1_START     (1)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_1_END       (1)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_2_START     (2)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_2_END       (2)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_3_START     (3)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_3_END       (3)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc0_START  (4)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc0_END    (4)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc1_START  (5)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc1_END    (5)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc2_START  (6)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc2_END    (6)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc3_START  (7)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc3_END    (7)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc0_START          (8)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc0_END            (8)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc1_START          (9)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc1_END            (9)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc2_START          (10)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc2_END            (10)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc3_START          (11)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc3_END            (11)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc0_START     (12)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc0_END       (12)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc1_START     (13)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc1_END       (13)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc2_START     (14)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc2_END       (14)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc3_START     (15)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc3_END       (15)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di0_START  (16)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di0_END    (16)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di1_START  (17)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di1_END    (17)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di2_START  (18)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di2_END    (18)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di3_START  (19)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di3_END    (19)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di0_START          (20)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di0_END            (20)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di1_START          (21)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di1_END            (21)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di2_START          (22)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di2_END            (22)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di3_START          (23)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di3_END            (23)
#define SOC_ISP_CSI2IF_ERR1_vc0_err_crc_START            (24)
#define SOC_ISP_CSI2IF_ERR1_vc0_err_crc_END              (24)
#define SOC_ISP_CSI2IF_ERR1_vc1_err_crc_START            (25)
#define SOC_ISP_CSI2IF_ERR1_vc1_err_crc_END              (25)
#define SOC_ISP_CSI2IF_ERR1_vc2_err_crc_START            (26)
#define SOC_ISP_CSI2IF_ERR1_vc2_err_crc_END              (26)
#define SOC_ISP_CSI2IF_ERR1_vc3_err_crc_START            (27)
#define SOC_ISP_CSI2IF_ERR1_vc3_err_crc_END              (27)
#define SOC_ISP_CSI2IF_ERR1_err_ecc_double_START         (28)
#define SOC_ISP_CSI2IF_ERR1_err_ecc_double_END           (28)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_ERR2_UNION
 结构说明  : ERR2 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: Error state register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_erresc_0          : 1;  /* bit[0]    : Escape entry error (ULPM) on data lane 0 */
        unsigned int  phy_erresc_1          : 1;  /* bit[1]    : Escape entry error (ULPM) on data lane 1 */
        unsigned int  phy_erresc_2          : 1;  /* bit[2]    : Escape entry error (ULPM) on data lane 2 */
        unsigned int  phy_erresc_3          : 1;  /* bit[3]    : Escape entry error (ULPM) on data lane 3 */
        unsigned int  phy_errsoths_0        : 1;  /* bit[4]    : Start of transmission error on data lane 0 (synchronization can still be achieved) */
        unsigned int  phy_errsoths_1        : 1;  /* bit[5]    : Start of transmission error on data lane 1 (synchronization can still be achieved) */
        unsigned int  phy_errsoths_2        : 1;  /* bit[6]    : Start of transmission error on data lane 2 (synchronization can still be achieved) */
        unsigned int  phy_errsoths_3        : 1;  /* bit[7]    : Start of transmission error on data lane 3 (synchronization can still be achieved) */
        unsigned int  vc0_err_ecc_corrected : 1;  /* bit[8]    : Header error detected and corrected on virtual channel 0 */
        unsigned int  vc1_err_ecc_corrected : 1;  /* bit[9]    : Header error detected and corrected on virtual channel 1 */
        unsigned int  vc2_err_ecc_corrected : 1;  /* bit[10]   : Header error detected and corrected on virtual channel 2 */
        unsigned int  vc3_err_ecc_corrected : 1;  /* bit[11]   : Header error detected and corrected on virtual channel 3 */
        unsigned int  err_id_vc0            : 1;  /* bit[12]   : Unrecognized or unimplemented data type detected in virtual channel 0 */
        unsigned int  err_id_vc1            : 1;  /* bit[13]   : Unrecognized or unimplemented data type detected in virtual channel 1 */
        unsigned int  err_id_vc2            : 1;  /* bit[14]   : Unrecognized or unimplemented data type detected in virtual channel 2 */
        unsigned int  err_id_vc3            : 1;  /* bit[15]   : Unrecognized or unimplemented data type detected in virtual channel 3 */
        unsigned int  reserved              : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_CSI2IF_ERR2_UNION;
#endif
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_0_START           (0)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_0_END             (0)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_1_START           (1)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_1_END             (1)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_2_START           (2)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_2_END             (2)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_3_START           (3)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_3_END             (3)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_0_START         (4)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_0_END           (4)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_1_START         (5)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_1_END           (5)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_2_START         (6)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_2_END           (6)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_3_START         (7)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_3_END           (7)
#define SOC_ISP_CSI2IF_ERR2_vc0_err_ecc_corrected_START  (8)
#define SOC_ISP_CSI2IF_ERR2_vc0_err_ecc_corrected_END    (8)
#define SOC_ISP_CSI2IF_ERR2_vc1_err_ecc_corrected_START  (9)
#define SOC_ISP_CSI2IF_ERR2_vc1_err_ecc_corrected_END    (9)
#define SOC_ISP_CSI2IF_ERR2_vc2_err_ecc_corrected_START  (10)
#define SOC_ISP_CSI2IF_ERR2_vc2_err_ecc_corrected_END    (10)
#define SOC_ISP_CSI2IF_ERR2_vc3_err_ecc_corrected_START  (11)
#define SOC_ISP_CSI2IF_ERR2_vc3_err_ecc_corrected_END    (11)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc0_START             (12)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc0_END               (12)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc1_START             (13)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc1_END               (13)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc2_START             (14)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc2_END               (14)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc3_START             (15)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc3_END               (15)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_MASK1_UNION
 结构说明  : MASK1 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: Masks for errors 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mask_phy_errsotsynchs_0    : 1;  /* bit[0]    :  */
        unsigned int  mask_phy_errsotsynchs_1    : 1;  /* bit[1]    :  */
        unsigned int  mask_phy_errsotsynchs_2    : 1;  /* bit[2]    :  */
        unsigned int  mask_phy_errsotsynchs_3    : 1;  /* bit[3]    :  */
        unsigned int  mask_err_f_bndry_match_vc0 : 1;  /* bit[4]    :  */
        unsigned int  mask_err_f_bndry_match_vc1 : 1;  /* bit[5]    :  */
        unsigned int  mask_err_f_bndry_match_vc2 : 1;  /* bit[6]    :  */
        unsigned int  mask_err_f_bndry_match_vc3 : 1;  /* bit[7]    :  */
        unsigned int  mask_err_f_seq_vc0         : 1;  /* bit[8]    :  */
        unsigned int  mask_err_f_seq_vc1         : 1;  /* bit[9]    :  */
        unsigned int  mask_err_f_seq_vc2         : 1;  /* bit[10]   :  */
        unsigned int  mask_err_f_seq_vc3         : 1;  /* bit[11]   :  */
        unsigned int  mask_err_frame_data_vc0    : 1;  /* bit[12]   :  */
        unsigned int  mask_err_frame_data_vc1    : 1;  /* bit[13]   :  */
        unsigned int  mask_err_frame_data_vc2    : 1;  /* bit[14]   :  */
        unsigned int  mask_err_frame_data_vc3    : 1;  /* bit[15]   :  */
        unsigned int  mask_err_l_bndry_match_di0 : 1;  /* bit[16]   :  */
        unsigned int  mask_err_l_bndry_match_di1 : 1;  /* bit[17]   :  */
        unsigned int  mask_err_l_bndry_match_di2 : 1;  /* bit[18]   :  */
        unsigned int  mask_err_l_bndry_match_di3 : 1;  /* bit[19]   :  */
        unsigned int  mask_err_l_seq_di0         : 1;  /* bit[20]   :  */
        unsigned int  mask_err_l_seq_di1         : 1;  /* bit[21]   :  */
        unsigned int  mask_err_l_seq_di2         : 1;  /* bit[22]   :  */
        unsigned int  mask_err_l_seq_di3         : 1;  /* bit[23]   :  */
        unsigned int  mask_vc0_err_crc           : 1;  /* bit[24]   :  */
        unsigned int  mask_vc1_err_crc           : 1;  /* bit[25]   :  */
        unsigned int  mask_vc2_err_crc           : 1;  /* bit[26]   :  */
        unsigned int  mask_vc3_err_crc           : 1;  /* bit[27]   :  */
        unsigned int  mask_err_ecc_double        : 1;  /* bit[28]   :  */
        unsigned int  reserved                   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CSI2IF_MASK1_UNION;
#endif
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_0_START     (0)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_0_END       (0)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_1_START     (1)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_1_END       (1)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_2_START     (2)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_2_END       (2)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_3_START     (3)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_3_END       (3)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc0_START  (4)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc0_END    (4)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc1_START  (5)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc1_END    (5)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc2_START  (6)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc2_END    (6)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc3_START  (7)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc3_END    (7)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc0_START          (8)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc0_END            (8)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc1_START          (9)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc1_END            (9)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc2_START          (10)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc2_END            (10)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc3_START          (11)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc3_END            (11)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc0_START     (12)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc0_END       (12)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc1_START     (13)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc1_END       (13)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc2_START     (14)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc2_END       (14)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc3_START     (15)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc3_END       (15)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di0_START  (16)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di0_END    (16)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di1_START  (17)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di1_END    (17)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di2_START  (18)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di2_END    (18)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di3_START  (19)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di3_END    (19)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di0_START          (20)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di0_END            (20)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di1_START          (21)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di1_END            (21)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di2_START          (22)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di2_END            (22)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di3_START          (23)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di3_END            (23)
#define SOC_ISP_CSI2IF_MASK1_mask_vc0_err_crc_START            (24)
#define SOC_ISP_CSI2IF_MASK1_mask_vc0_err_crc_END              (24)
#define SOC_ISP_CSI2IF_MASK1_mask_vc1_err_crc_START            (25)
#define SOC_ISP_CSI2IF_MASK1_mask_vc1_err_crc_END              (25)
#define SOC_ISP_CSI2IF_MASK1_mask_vc2_err_crc_START            (26)
#define SOC_ISP_CSI2IF_MASK1_mask_vc2_err_crc_END              (26)
#define SOC_ISP_CSI2IF_MASK1_mask_vc3_err_crc_START            (27)
#define SOC_ISP_CSI2IF_MASK1_mask_vc3_err_crc_END              (27)
#define SOC_ISP_CSI2IF_MASK1_mask_err_ecc_double_START         (28)
#define SOC_ISP_CSI2IF_MASK1_mask_err_ecc_double_END           (28)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_MASK2_UNION
 结构说明  : MASK2 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: Masks for errors 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mask_phy_erresc_0          : 1;  /* bit[0]    :  */
        unsigned int  mask_phy_erresc_1          : 1;  /* bit[1]    :  */
        unsigned int  mask_phy_erresc_2          : 1;  /* bit[2]    :  */
        unsigned int  mask_phy_erresc_3          : 1;  /* bit[3]    :  */
        unsigned int  mask_phy_errsoths_0        : 1;  /* bit[4]    :  */
        unsigned int  mask_phy_errsoths_1        : 1;  /* bit[5]    :  */
        unsigned int  mask_phy_errsoths_2        : 1;  /* bit[6]    :  */
        unsigned int  mask_phy_errsoths_3        : 1;  /* bit[7]    :  */
        unsigned int  mask_vc0_err_ecc_corrected : 1;  /* bit[8]    :  */
        unsigned int  mask_vc1_err_ecc_corrected : 1;  /* bit[9]    :  */
        unsigned int  mask_vc2_err_ecc_corrected : 1;  /* bit[10]   :  */
        unsigned int  mask_vc3_err_ecc_corrected : 1;  /* bit[11]   :  */
        unsigned int  mask_err_id_vc0            : 1;  /* bit[12]   :  */
        unsigned int  mask_err_id_vc1            : 1;  /* bit[13]   :  */
        unsigned int  mask_err_id_vc2            : 1;  /* bit[14]   :  */
        unsigned int  mask_err_id_vc3            : 1;  /* bit[15]   :  */
        unsigned int  reserved                   : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_CSI2IF_MASK2_UNION;
#endif
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_0_START           (0)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_0_END             (0)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_1_START           (1)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_1_END             (1)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_2_START           (2)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_2_END             (2)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_3_START           (3)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_3_END             (3)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_0_START         (4)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_0_END           (4)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_1_START         (5)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_1_END           (5)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_2_START         (6)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_2_END           (6)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_3_START         (7)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_3_END           (7)
#define SOC_ISP_CSI2IF_MASK2_mask_vc0_err_ecc_corrected_START  (8)
#define SOC_ISP_CSI2IF_MASK2_mask_vc0_err_ecc_corrected_END    (8)
#define SOC_ISP_CSI2IF_MASK2_mask_vc1_err_ecc_corrected_START  (9)
#define SOC_ISP_CSI2IF_MASK2_mask_vc1_err_ecc_corrected_END    (9)
#define SOC_ISP_CSI2IF_MASK2_mask_vc2_err_ecc_corrected_START  (10)
#define SOC_ISP_CSI2IF_MASK2_mask_vc2_err_ecc_corrected_END    (10)
#define SOC_ISP_CSI2IF_MASK2_mask_vc3_err_ecc_corrected_START  (11)
#define SOC_ISP_CSI2IF_MASK2_mask_vc3_err_ecc_corrected_END    (11)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc0_START             (12)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc0_END               (12)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc1_START             (13)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc1_END               (13)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc2_START             (14)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc2_END               (14)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc3_START             (15)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc3_END               (15)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_PHY_TEST_CTRL0_UNION
 结构说明  : PHY_TEST_CTRL0 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: D-PHY Test interface control 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_testclr : 1;  /* bit[0]   : D-PHY test interface clear
                                                      It is used when active performs vendor specific interface initialization
                                                      (Active High). */
        unsigned int  phy_testclk : 1;  /* bit[1]   : D-PHY test interface strobe signal
                                                      It is used to clock TESTDIN bus into the D-PHY. In conjunction with
                                                      TESTEN signal controls the operation selection. */
        unsigned int  reserved    : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_CSI2IF_PHY_TEST_CTRL0_UNION;
#endif
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_phy_testclr_START  (0)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_phy_testclr_END    (0)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_phy_testclk_START  (1)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_phy_testclk_END    (1)


/*****************************************************************************
 结构名    : SOC_ISP_CSI2IF_PHY_TEST_CTRL1_UNION
 结构说明  : PHY_TEST_CTRL1 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: D-PHY Test interface control 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_testdin  : 8;  /* bit[0-7]  : D-PHY test interface input 8-bit data bus for internal register
                                                        programming and test functionalities access. */
        unsigned int  phy_testdout : 8;  /* bit[8-15] : D-PHY output 8-bit data bus for read-back and internal probing
                                                        functionalities. */
        unsigned int  phy_testen   : 1;  /* bit[16]   : D-PHY test interface operation selector:
                                                        - 1: Configures address write operation on the falling edge of
                                                        TESTCLK
                                                        - 0: Configures a data write operation on the rising edge of TESTCLK */
        unsigned int  reserved     : 15; /* bit[17-31]:  */
    } reg;
} SOC_ISP_CSI2IF_PHY_TEST_CTRL1_UNION;
#endif
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testdin_START   (0)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testdin_END     (7)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testdout_START  (8)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testdout_END    (15)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testen_START    (16)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testen_END      (16)






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

#endif /* end of soc_isp_csi2if_interface.h */
