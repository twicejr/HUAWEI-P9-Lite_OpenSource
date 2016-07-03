
/*该头文件专为TLdsp和Hifi提供，其他模块应引用drv_edma.h*/
#ifndef __DRV_EDMA_ENUM_H__
#define __DRV_EDMA_ENUM_H__

#define EDMA_CHANNEL_START  0
#define EDMA_CH16_NUM       16
#ifdef HI_EDMA_CH4_REGBASE_ADDR_VIRT
#define EDMA_CH4_NUM        12
#define EDMA_CHANNEL_END    (EDMA_CHANNEL_START+EDMA_CH16_NUM+EDMA_CH4_NUM)
#else
#define EDMA_CHANNEL_END    (EDMA_CHANNEL_START+EDMA_CH16_NUM)
#endif


#define	EDMA_CH16_0	    0
#define	EDMA_CH16_1	    1
#define	EDMA_CH16_2	    2
#define	EDMA_CH16_3	    3
#define	EDMA_CH16_4	    4
#define	EDMA_CH16_5	    5
#define	EDMA_CH16_6	    6
#define	EDMA_CH16_7	    7
#define	EDMA_CH16_8	    8
#define	EDMA_CH16_9	    9
#define	EDMA_CH16_10	10
#define	EDMA_CH16_11	11
#define	EDMA_CH16_12	12
#define	EDMA_CH16_13	13
#define	EDMA_CH16_14	14
#define	EDMA_CH16_15	15

#define	EDMA_CH12_0	    16
#define	EDMA_CH12_1	    17
#define	EDMA_CH12_2	    18
#define	EDMA_CH12_3	    19
#define EDMA_CH12_4     20
#define EDMA_CH12_5     21
#define EDMA_CH12_6     22
#define EDMA_CH12_7     23
#define EDMA_CH12_8     24
#define EDMA_CH12_9     25
#define EDMA_CH12_10    26
#define EDMA_CH12_11    27
#define	EDMA_CH_END	    28


#define	EDMA_CH_LDSP_API_USED_0 EDMA_CH16_0
#define	EDMA_CH_LDSP_API_USED_1 EDMA_CH16_1
#define	EDMA_CH_LDSP_LCS_SDR    EDMA_CH16_2
#define	EDMA_CH_LDSP_CSU_SDR    EDMA_CH16_3
#define	EDMA_CH_LDSP_EMU_SDR    EDMA_CH16_4
#define	EDMA_CH_LDSP_NV_LOADING EDMA_CH16_5
/****arm与ldsp复用****低功耗备份恢复  m2m */
#define	EDMA_CH_LOAD_LDSP_TCM  EDMA_CH_LDSP_API_USED_0
#define	EDMA_CH_LOAD_TDSP_TCM  EDMA_CH_LDSP_API_USED_1
/****gudsp与ldsp复用****GU CQI搬移 与 LDSP LCS */
#define	EDMA_CH_GUDSP_MEMORY_3  EDMA_CH_LDSP_LCS_SDR

/*EDMA_CH_GUDSP_MEMORY_9  ==  BBP_GRIF_PHY，
GUDSP实现BBP搬数，用于校准 复用GU BBP DEBUG采数功能
其他通道均为 M2M */
#define	EDMA_CH_GUDSP_MEMORY_9  EDMA_CH16_6
#define	EDMA_CH_GUDSP_MEMORY_7  EDMA_CH16_7
/****gudsp与gudsp复用****GU DSP加载与 GU AHB加载 */
#define	EDMA_CH_GUDSP_MEMORY_8  EDMA_CH_GUDSP_MEMORY_7


#define	EDMA_CH_GUDSP_MEMORY_1  EDMA_CH16_8
#define	EDMA_CH_GUDSP_MEMORY_2  EDMA_CH16_9
#define	EDMA_CH_GUDSP_MEMORY_4  EDMA_CH16_10
#define	EDMA_CH_GUDSP_MEMORY_6  EDMA_CH16_11

#define	EDMA_CH_GUDSP_MEMORY_10  EDMA_CH16_15

/* SIM卡0 接收和发送 / SIM卡1 接收和发送 */
#define	EDMA_CH_DRV_SIM_0       EDMA_CH16_12
#define	EDMA_CH_DRV_SIM_1       EDMA_CH16_13
/* 接收来自axi_monitor的采集数据 */
#define	EDMA_CH_DRV_AXIMON      EDMA_CH16_14



/* hi6250 有两个 EDMA 基地址: 0xE0204000 0xE0210000
   第一个 EDMA的通道号记为 0~15，第二个 EDMA的通道号记为 16~27
*/

#define EDMA_CH_G1_GTC EDMA_CH12_0
#define EDMA_CH_G2_GTC EDMA_CH12_1

/* C ps 专用通道 */
#define EDMA_CH_CPS_M2M_0 EDMA_CH12_4      /* PS L2上行搬数  */
#define EDMA_CH_CPS_M2M_1 EDMA_CH12_5      /* PS L2下行搬数  */


/* CPHY的专用通道号 5 个, 1个与底软加载/备份 C dsp_tcm 复用*/
/* 基地址 0xE0210000 */

#define EDMA_CH_LOAD_CDSP_TCM   EDMA_CH12_6     /* 底软镜像加载与备份恢复 + cdsp低功耗备份恢复 */
#define EDMA_CH_CPHY_M2M_2      EDMA_CH12_7     /* DDR到DDR         */
#define EDMA_CH_CPHY_1X_1       EDMA_CH12_8     /* 编码上报 */
#define EDMA_CH_CPHY_1X_2       EDMA_CH12_9     /* 搜索上报 */
#define EDMA_CH_CPHY_1X_3       EDMA_CH12_10    /* 译码上报 */
#define EDMA_CH_CPHY_1X_4       EDMA_CH12_11    /* 编码下发 */


/* CPHY 5 个复用 EDMA 通道 (不能与 L 复用，所以与 GU 复用) 
    (基地址 0xE0204000) */
/* 搜索上报 * 编码上报 * 搜索上报 * 译码上报 * 编码下发 */
#define EDMA_CH_CPHY_EVDO_1 EDMA_CH_GUDSP_MEMORY_1
#define EDMA_CH_CPHY_EVDO_2 EDMA_CH_GUDSP_MEMORY_2
#define EDMA_CH_CPHY_EVDO_3 EDMA_CH_GUDSP_MEMORY_4
#define EDMA_CH_CPHY_EVDO_4 EDMA_CH_GUDSP_MEMORY_6
#define EDMA_CH_CPHY_EVDO_5 EDMA_CH_GUDSP_MEMORY_9


#endif

