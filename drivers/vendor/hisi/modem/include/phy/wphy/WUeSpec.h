/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : WUeSpec.h
  版 本 号   : 初稿
  作    者   : Jinying
  生成日期   : 2006年9月2日
  最近修改   :
  功能描述   : WUe的产品规格定义头文件。
  函数列表   :
  修改历史   :
  1.日    期   : 2006年9月2日
    作    者   : Jinying
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "Hi_Config.h"
#include "product_config.h"



#ifndef __WUESPEC_H__
#define __WUESPEC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PS_WUE_CIPHER_KEY_LEN                   (16)    /* 加密密钥长度 */

#define PS_WUE_MAX_FORBLA_NUM                   (32)    /* 禁止注册区的最大的个数 */

#define PS_WUE_MAX_HIGH_PLMN_NUM                (16)    /* 高质量的PLMN的最大个数 */
#define PS_WUE_MAX_LOW_PLMN_NUM                 (16)    /* 低质量的PLMN的最大个数 */

#define PS_WUE_MAX_NAS_GSM_MAP_NUM              (8)     /* 协议值 8             */
#define PS_WUE_MAX_NAS_MSG_LEN                  (4095)  /* 协议值 4095,NAS消息最大长度        */

#define PS_WUE_MAX_MULTI_PLMN_NUM               (5)     /* 协议值 5,MultiplePLMN_List_r6*/
#define PS_WUE_MAX_PLMN_NUM                     (PS_WUE_MAX_MULTI_PLMN_NUM + 1)
                                                        /* MULTI PLMN加上MIB中携带的PLMN */

#define PS_WUE_MAX_AC_NUM                       (16)    /* 协议值 maxAC 16  */
#define PS_WUE_MAX_ADD_MEAS_NUM                 (4)     /* 协议值 maxAdditionalMeas 4     */
#define PS_WUE_MAX_ASC_NUM                      (8)     /* 协议值 maxASC 8     */
#define PS_WUE_MAX_ASC_MAP_NUM                  (7)     /* 协议值 maxASCmap 7     */
#define PS_WUE_MAX_ASC_PERSIST_NUM              (6)     /* 协议值 maxASCpersist 6     */
#define PS_WUE_MAX_CCTRCH_NUM                   (1)     /* 协议值 maxCCTrCH 8     */  /* 这里只是指R99的CCTRCH能力 */
#define PS_WUE_MAX_SCCPCH_CCTRCH_NUM            (2)     /* 支持cbs和pi，设定为2 */
#define PS_WUE_MAX_CELL_MEAS_NUM                (32)    /* 协议值 maxCellMeas 32    */
#define PS_WUE_MAX_CELL_MEAS1_NUM               (31)    /* 协议值 maxCellMeas_1 31    */
#define PS_WUE_MAX_CN_DOMAINS_NUM               (2)     /* 协议值 maxCNdomains 4     */  /* CS and PS */
#define PS_WUE_MAX_DPCH_DL_CHAN_NUM             (1)     /* 协议值 maxDPCH_DLchan 8     */  /* Asic spec */
#define PS_WUE_MAX_DPDCH_UL_NUM                 (1)     /* 协议值 maxDPDCH_UL 6     */
#define PS_WUE_MAX_DRAC_CLASSES_NUM             (8)     /* 协议值 maxDRACclasses 8     */
#define PS_WUE_MAC_E_DCH_MACD_FLOW_NUM          (8)     /* 协议值 maxE_DCHMACdFlow 8,E DCH流的个数 */
#define PS_WUE_MAX_E_DCH_MACD_FLOW1_NUM         (7)     /* 协议值 maxE_DCHMACdFlow_1 7     */
#define PS_WUE_MAX_E_DCH_RL_NUM                 (4)     /* 协议值 maxEDCHRL 4     */
#define PS_WUE_MAX_FACH_PCH_NUM                 (8)     /* 协议值 maxFACHPCH 8     */
#define PS_WUE_MAX_FREQ_NUM                     (8)     /* 协议值 maxFreq 8     */
#define PS_WUE_MAX_FREQ_BANDS_FDD_NUM           (2)     /* 协议值 maxFreqBandsFDD 8     */  /* 1900M and 2100M */
#define PS_WUE_MAX_FREQ_BANDS_FDD_EXT_NUM       (15)    /* 协议值 maxFreqBandsFDD_ext 15    */
#define PS_WUE_MAX_FREQ_BANDS_GSM_NUM           (3)     /* 协议值 maxFreqBandsGSM 16    */  /* 850M 900M 1800M */
#define PS_WUE_MAX_GERAN_SI_NUM                 (8)     /* 协议值 maxGERAN_SI 8     */
#define PS_WUE_MAX_GSM_TARGET_CELLS_NUM         (32)    /* 协议值 maxGSMTargetCells 32    */
#define PS_WUE_MAX_H_PROCESSES_NUM              (8)     /* 协议值 maxHProcesses 8     */
#define PS_WUE_MAX_HS_SCCHS_NUM                 (4)     /* 协议值 maxHSSCCHs 4     */
#define PS_WUE_MAX_INTER_SYS_MSGS_NUM           (2)     /* 协议值 maxInterSysMessages 4     */
#define PS_WUE_MAX_LOCH_PER_RLC_NUM             (2)     /* 协议值 maxLoCHperRLC 2,每个RLC最大可以映射的逻辑信道个数 */
#define PS_WUE_MAX_MAC_D_PDU_SIZES_NUM          (8)     /* 协议值 maxMAC_d_PDUsizes 8     */
#define PS_WUE_MAX_MEAS_EVT_NUM                 (8)     /* 协议值 maxMeasEvent 8     */
#define PS_WUE_MAX_MEAS_INTERVALS_NUM           (3)     /* 协议值 maxMeasIntervals 3     */
#if (FEATURE_ON == FEATURE_DC_UPA)
#define PS_WUE_MAX_MEAS_EVT_ON_SEC_UL_FREQ_NUM  (8)     /* 协议值 maxMeasEventOnSecULFreq 8     */
#endif
#define PS_WUE_MAX_MEAS_PAR_EV_NUM              (2)     /* 协议值 maxMeasParEvent 2 */
#define PS_WUE_MAX_NUM_GSM_FREQ_RANGES_NUM      (32)    /* 协议值 maxNumGSMFreqRanges 32    */
#define PS_WUE_MAX_NUM_FDD_FREQS_NUM            (8)     /* 协议值 maxNumFDDFreqs 8     */
#define PS_WUE_MAX_NO_OF_MEAS_NUM               (16)    /* 协议值 maxNoOfMeas 16    */
#define PS_WUE_MAX_OTHER_RAT_NUM                (1)     /* 协议值 maxOtherRAT 15    */   /* GSM */
#define PS_WUE_MAX_OTHER_RAT16_NUM              (1)     /* 协议值 maxOtherRAT_16 16    */   /* GSM */
#define PS_WUE_MAX_PAGE1_NUM                    (8)     /* 协议值 maxPage1 8     */
#define PS_WUE_MAX_PDCP_ALGO_TYPE_NUM           (2)     /* 协议值 maxPDCPAlgoType 8,PDCP头压缩算法 */
#define PS_WUE_MAX_PRACH_NUM                    (16)    /* 协议值 maxPRACH 16，用于PRACH选择，每次只选择一个PRACH，更换小区以后重新选择    */
#define PS_WUE_MAX_QUEUE_NUM                    (8)     /* 协议值 maxQueueIDs 8 ，HSDPA最大的队列数 */

#define PS_WUE_MAX_CS_RAB_NUM                   (2)     /* 1个AMR，1个CSD */
#define PS_WUE_MAX_PS_RAB_NUM                   (5)     /* 5个PS业务 GCF7.1.5.2 5个PS RB都映射到HSDPA*/
#define PS_WUE_MAX_RAB_NUM                      (PS_WUE_MAX_CS_RAB_NUM + PS_WUE_MAX_PS_RAB_NUM)
                                                        /* 协议值 maxRABsetup 16,建立的最大RAB数        */
#define PS_WUE_MAX_SRB_NUM                      (4)     /* 4个SRB */
#define PS_WUE_MAX_AMR_RB_NUM                   (3)     /* AMR最多对应3个RB */
#define PS_WUE_MAX_CS_RB_NUM                    (PS_WUE_MAX_AMR_RB_NUM + 1)     /* 3个AMR/1个CSD */
#define PS_WUE_MAX_PS_RB_NUM                    (5)     /* 5个PS */

#define PS_WUE_MAX_RB_NUM                       (PS_WUE_MAX_SRB_NUM + PS_WUE_MAX_CS_RB_NUM + PS_WUE_MAX_PS_RB_NUM)     /* 协议值 maxRB 32 */
#define PS_WUE_MAX_RB_ALL_RABS_NUM              (PS_WUE_MAX_CS_RB_NUM + PS_WUE_MAX_PS_RB_NUM)
                                                        /* 协议值 maxRBallRABs 27    */  /* 4 CS + 2 PS */
#define PS_WUE_MAX_E_DCH_LOCH_NUM               (12)    /* 4个信令RB,5个PS域RB,3个CS,不考虑1个AM RB对应2个LOCH的情况,GCF14_7_7用例4个SRB+3个PS RB都映射到EDCH*/
#define PS_WUE_MAX_RB_MUX_OP_NUM                (4)     /* 协议值 maxRBMuxOptions 8     */
#define PS_WUE_MAX_RB_PER_RAB_NUM               (3)     /* 协议值 maxRBperRAB 8,每个RAB包含的最大RB数  */  /* AMR */
#define PS_WUE_MAX_RB_PER_TRCH_NUM              (4)     /* 协议值 maxRBperTrCh 16     */  /* SRB */
#define PS_WUE_MAX_RPT_GSM_CELLS_NUM            (8)     /* 协议值 maxReportedGSMCells 8     */
#define PS_WUE_MAX_RL_NUM                       (6)     /* 协议值 maxRL 8     */  /* ASIC spec */
#define PS_WUE_MAX_RL_MINUS1_NUM                (5)     /* 协议值 maxRL_1 7   */
#define PS_WUE_MAX_RLC_PDU_SIZE_NUM_PER_LOCH    (32)    /* 协议值 maxRLCPDUsizePerLogChan 32,每个逻辑信道可用的RLC SIZE德个数 */
#define PS_WUE_MAX_SAT_NUM                      (16)     /* 协议值 maxSat 16    */
#define PS_WUE_MAX_SVGLOBALHEALTH_NUM           (46)    /* 协议值 maxSvGlobalHealth 46    */
#define PS_WUE_MAX_SCCPCH_NUM                   (1)     /* 协议值 maxSCCPCH 16    */
#define PS_WUE_MAX_SIB_NUM                      (32)    /* 协议值 maxSIB 32    */
#define PS_WUE_MAX_SIB_FACH_NUM                 (8)     /* 协议值 maxSIB_FACH 8     */
#define PS_WUE_MAX_SIB_PER_MSG_NUM              (16)    /* 协议值 maxSIBperMsg 16    */
#define PS_WUE_MAX_SRB_SETUP_NUM                (5)     /* 协议值 maxSRBsetup 8     */
#define PS_WUE_MAX_SYS_CAPAB_NUM                (2)     /* 协议值 maxSystemCapability 16    */
#define PS_WUE_MAX_TF_NUM                       (32)    /* 协议值 maxTF 32,最大传输格式 */

#define PS_WUE_MAX_DL_TFC_NUM                   (128)   /* 协议值 maxTFC 1024  */
#define PS_WUE_MAX_UL_TFC_NUM                   (128)   /* 协议值 maxTFC 1024  */
#define PS_WUE_MAX_TFC_NUM                      (128)   /* 协议值 maxTFC 1024  */

#define PS_WUE_MAX_REF_E_TFCI_NUM               (8)     /* 协议值 8 E_DPDCH_Reference_E_TFCIList */
#define PS_WUE_MAX_TFC_SUB_NUM                  (128)   /* 协议值 maxTFCsub 1024  */

#define PS_WUE_MAX_TGPS_NUM                     (6)     /* 协议值 maxTGPS 6     */
#define PS_WUE_MAX_TGPL                         (144)   /* 协议值：144 */
#define PS_WUE_MAX_TGPRC                        (511)   /* 协议值：511 */

#define PS_WUE_MAX_DCH_NUM                      (8)     /* 3CS AMR + 3PS + 1SIG */

#define PS_WUE_MAX_TRCH_NUM                     (PS_WUE_MAX_DCH_NUM + 1 + 1)
                                                        /* 协议值 maxTrCH 32，加1HSDSCH,1E DCH,BBP规格 */

#define PS_WUE_MAX_MEAS_TRCH_NUM                (PS_WUE_MAX_DCH_NUM)
                                                        /* 协议值 maxTrCH 32，最大情况为6个DCH或者1个RACH */

#define PS_WUE_MAX_URA_NUM                      (8)     /* 协议值 maxURA 8     */
#define PS_WUE_MAX_URNTI_GROUP_NUM              (8)     /* 协议值 maxURNTI_Group 8     */

#define PS_WUE_MAX_LOCH_NUM                     (15)    /* 2个非AM SRB + 3个AMR + (2个PS RB + 3个AM SRB) * 2(LOCH PER RB) */
#define PS_WUE_MIN_LOCH_ID                      (1)
#define PS_WUE_MAX_LOCH_ID                      (15)    /* 协议值 15,LogicalChannelList中explicitList的最大映射rb数 */
#define PS_WUE_CCCH_LOCH_ID_OVER_EDCH           (15)    /* CCCH逻辑信道ID固定填写15 */
#define PS_WUE_MIN_TRCH_ID                      (1)
#define PS_WUE_MAX_TRCH_ID                      (32)    /* 协议值 Integer(1..32)*/
#define PS_PROTOCOL_MAX_OTHER_RAT_NUM           (15)    /* 协议值 maxOtherRAT 15  UE能力对应:PS_WUE_MAX_OTHER_RAT_NUM:1  */

/*V3 R7_7C1 Start */
#define PS_WUE_INVALID_TRCH_ID                  (0xFFFF)
#define PS_WUE_MIN_HS_FLOW_ID                   (0)
#define PS_WUE_MAX_HS_FLOW_ID                   (7)
#define PS_WUE_MIN_HS_QUEUE_ID                  (0)
#define PS_WUE_MAX_HS_QUEUE_ID                  (7)
/* V3 R7_7C1 End */

#define PS_WUE_MAX_EDCHS                        (32)    /* 协议值 32,maxEDCHs*/

#if (FEATURE_ON == FEATURE_DC_MIMO)
#define PS_WUE_MAX_HS_CATEGORY_NUM              (28)    /* UE 最大的HSDPA Category Num数 包括扩展的cate */
#else
#define PS_WUE_MAX_HS_CATEGORY_NUM              (24)    /* UE 最大的HSDPA Category Num数 包括扩展的cate */
#endif /* FEATURE_DC_MIMO */
#define PS_WUE_MAX_CRC_LEN                      (3)     /* 单位:字节，CRC bit长度取值为:0、8、12、16、24 */
#define PS_WUE_MAX_TB_CNT                       (32)    /* 协议值最大512,TB数目,HI4131 规格最大32*/
#define PS_WUE_MAX_COMM_HRNTI_NUM               (4)     /* maxCommonHRNTI,协议值 4 */
#define PS_WUE_MAX_COMM_QUEUE_ID_NUM            (2)     /* maxCommonQueueID ,协议值 2 */

#define PS_WUE_RSSI_THRESHOLD                   (-960)  /* 下发给物理层做RSSI搜索的上报门限 */




/* 以下为目前不支持的规格，包括TDD和MBMS */
#if 0
#define PS_WUE_HI_PDSCH_ID                      (1)     /* 协议值 64    */
#define PS_WUE_HI_PUSCH_ID                      (1)     /* 协议值 64    */
#define PS_WUE_MAX_CPCH_SETS                    (1)     /* 协议值 16    */
#define PS_WUE_MAX_FREQ_BANDS_TDD               (1)     /* 协议值 4     */
#define PS_WUE_MAX_HSDSCHTB_INDEX_TDD384        (1)     /* 协议值 512   */   /* tdd not support */
#define PS_WUE_MAX_HSDSCHTB_INDEX               (1)     /* 协议值 maxHSDSCHTBIndex 64    */  /* not use */
#define PS_WUE_MAX_MBMS_COMM_CCTRCH             (1)     /* 协议值 32    */
#define PS_WUE_MAX_MBMS_COMM_PHY_CH             (1)     /* 协议值 32    */
#define PS_WUE_MAX_MBMS_COMM_RB                 (1)     /* 协议值 32    */
#define PS_WUE_MAX_MBMS_COMM_TRCH               (1)     /* 协议值 32    */
#define PS_WUE_MAX_MBMS_FREQ                    (1)     /* 协议值 4     */
#define PS_WUE_MAX_MBMS_L1_CP                   (1)     /* 协议值 4     */
#define PS_WUE_MAX_MBM_SSERV_CNT                (1)     /* 协议值 8     */
#define PS_WUE_MAX_MBM_SSERV_MODIF              (1)     /* 协议值 32    */
#define PS_WUE_MAX_MBM_SSERV_SCHED              (1)     /* 协议值 16    */
#define PS_WUE_MAX_MBM_SSERV_UNMODIF            (1)     /* 协议值 64    */
#define PS_WUE_MAX_MBMS_TRANSMIS                (1)     /* 协议值 4     */
#define PS_WUE_MAX_NUM_CDMA2000_FREQS           (1)     /* 协议值 8     */
#define PS_WUE_MAX_NUM_TDD_FREQS                (1)     /* 协议值 8     */
#define PS_WUE_MAX_PCPCH_AP_SIG                 (1)     /* 协议值 16    */
#define PS_WUE_MAX_PCPCH_AP_SUB_CH              (1)     /* 协议值 12    */
#define PS_WUE_MAX_PCPCH_CD_SIG                 (1)     /* 协议值 16    */
#define PS_WUE_MAX_PCPCH_CD_SUB_CH              (1)     /* 协议值 12    */
#define PS_WUE_MAX_PCPCH_SF                     (1)     /* 协议值 7     */
#define PS_WUE_MAX_PCPCHS                       (1)     /* 协议值 64    */
#define PS_WUE_MAX_PDSCH                        (1)     /* 协议值 8     */
#define PS_WUE_MAX_PDSCH_TFCI_GROUPS            (1)     /* 协议值 256   */
#define PS_WUE_MAX_PRACH_FPACH                  (1)     /* 协议值 8     */  /* TDD */
#define PS_WUE_MAX_PREDEF_CFG                   (1)     /* 协议值 16    */
#define PS_WUE_MAX_PUSCH                        (1)     /* 协议值 8     */
#define PS_WUE_MAX_RAT_NUM                      (2)     /* 协议值 maxRAT 16    */
#define PS_WUE_MAX_RB_PER_TRCH                  (1)     /* 协议值 16     */ /* MBMS */
#define PS_WUE_MAX_RFC3095_CID                  (1)     /* 协议值 16384 */
#define PS_WUE_MAX_ROHC_PACKET_SIZES_R4         (1)     /* 协议值 16    */
#define PS_WUE_MAX_ROHC_PROFILE_R4              (1)     /* 协议值 8     */
#define PS_WUE_MAX_TF_CPCH                      (1)     /* 协议值 16    */
#define PS_WUE_MAX_TFCI2_COMBS                  (1)     /* 协议值 512   */  /* dsch */
#define PS_WUE_MAX_TRCH_PRECONF                 (1)     /* 协议值 32    */
#define PS_WUE_MAX_TS                           (1)     /* 协议值 14    */
#define PS_WUE_MAX_TS1                          (1)     /* 协议值 13    */
#define PS_WUE_MAX_TS2                          (1)     /* 协议值 12    */
#define PS_WUE_MAX_TS_LCR                       (1)     /* 协议值 6     */
#define PS_WUE_MAX_TS_LCR1                      (1)     /* 协议值 5     */
#endif

/* RB_Identity ::=                        INTEGER (1..32) */
#define PS_WUE_MIN_RB_ID                        (1)     /* INTEGER (1..32) */
#define PS_WUE_MIN_T_RB_ID                      (5)     /* 最小TRAFFIC RB ID */
#define PS_WUE_MAX_RB_ID                        (32)    /* INTEGER (1..32) */

#define PS_WUE_MIN_RAB_ID                       (1)
#define PS_WUE_MAX_RAB_ID                       (16)

/* 选择的DRX长度，用于CBS，协议规格256 */
#define PS_WUE_MAX_DRXSEL_LEN                   (255)

/* UE能力规格 */

/* 物理层能力存储在NV项中 */
#if 1
/* UE允许的最大发送功率 */
#define PS_WUE_MAX_TX_PWR                       (24)                            /* 25.101 6.2.1: Power Class 3              */

/*****************************************************************************
 结构名    : PS_WUE_MULTI_RAT_GSM_SUPPT
             PS_WUE_MULTI_CARRIER_SUPPT
 ASN.1描述 : supportOfGSM                        BOOLEAN,
             supportOfMulticarrier               BOOLEAN
 结构说明  : 是否支持异系统和多载波
*****************************************************************************/
#define PS_WUE_MULTI_RAT_GSM_SUPPT              PS_CAP_SUPPORT                  /* PS_CAP_SUPPORT: support GSM ,         PS_CAP_UNSUPPORT: not support GSM                       */
#define PS_WUE_MULTI_CARRIER_SUPPT              PS_CAP_UNSUPPORT                /* PS_CAP_SUPPORT: support multi carrier,PS_CAP_UNSUPPORT: not support multi carrier             */

/*****************************************************************************
 结构名    :PS_WUE_MEAS_DL_COMPRS_TDD_SUPPT
            PS_WUE_MEAS_DL_COMPRS_FDD_SUPPT
            PS_WUE_MEAS_DL_COMPRS_GSM900_SUPPT
            PS_WUE_MEAS_DL_COMPRS_DCS1800_SUPPT
            PS_WUE_MEAS_DL_COMPRS_GSM1900_SUPPT
            PS_WUE_MEAS_DL_COMPRS_MULTI_CARRIER_SUPPT

            PS_WUE_MEAS_UL_COMPRS_TDD_SUPPT
            PS_WUE_MEAS_UL_COMPRS_FDD_SUPPT
            PS_WUE_MEAS_UL_COMPRS_GSM900_SUPPT
            PS_WUE_MEAS_UL_COMPRS_DCS1800_SUPPT
            PS_WUE_MEAS_UL_COMPRS_GSM1900_SUPPT
            PS_WUE_MEAS_UL_COMPRS_MULTI_CARRIER_SUPPT

 ASN.1描述 :fdd_Measurements                    BOOLEAN,
            -- TABULAR: The IEs tdd_Measurements, gsm_Measurements and multiCarrierMeasurements
            -- are made optional since they are conditional based on another information element.
            -- Their absence corresponds to the case where the condition is not true.
            tdd_Measurements                    BOOLEAN                                OPTIONAL,
            gsm_Measurements                    GSM_Measurements                    OPTIONAL,
                GSM_Measurements ::=                SEQUENCE {
                    gsm900                                BOOLEAN,
                    dcs1800                                BOOLEAN,
                    gsm1900                                BOOLEAN
                }
            multiCarrierMeasurements            BOOLEAN                                OPTIONAL

 结构说明  : 支持的压模测量能力
*****************************************************************************/
#define PS_WUE_MEAS_DL_COMPRS_TDD_SUPPT                     PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_DL_COMPRS_FDD_SUPPT                     PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_DL_COMPRS_GSM900_SUPPT                  PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_DL_COMPRS_DCS1800_SUPPT                 PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_DL_COMPRS_GSM1900_SUPPT                 PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_DL_COMPRS_MULTI_CARRIER_SUPPT           PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */

#define PS_WUE_MEAS_UL_COMPRS_TDD_SUPPT                     PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_UL_COMPRS_FDD_SUPPT                     PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_UL_COMPRS_GSM900_SUPPT                  PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_UL_COMPRS_DCS1800_SUPPT                 PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_UL_COMPRS_GSM1900_SUPPT                 PS_CAP_SUPPORT      /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#define PS_WUE_MEAS_UL_COMPRS_MULTI_CARRIER_SUPPT           PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT:支持    PS_CAP_UNSUPPORT:不支持                       */
#endif

/*==============================================================================
                        存储在本地的UE能力宏定义=
==============================================================================*/
/* PDCP capability */
#define PS_WUE_CAP_LOSSLESS_SRNS_RELOC_SUPPT                PS_CAP_SUPPORT      /* PS_CAP_SUPPORT : SUPPORT                          */

#define PS_WUE_CAP_LOSSLESS_DL_RLC_PDU_SIZE_CHG_SUPPT       PS_CAP_SUPPORT      /* PS_CAP_SUPPORT : SUPPORT                          */
#define ASN1_LOSSLESS_DL_RLC_PDU_SIZE_CHG                   EN_ENC_PDCP_CAPAB_R5_EXT2_LOSSLESS_DLRLC_PDU_SIZE_CHG_TRUE

#define PS_WUE_CAP_RFC2507_SUPPT                            PS_CAP_UNSUPPORT    /* PS_CAP_SUPPORT : SUPPORT                          */

#define PS_WUE_CAP_RFC3095_SUPPT                            PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT 此处作预留，现不支持  */

#define PS_WUE_CAP_MAX_ROHC_CTX_SESSION                     PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT 此处作预留，现不支持  */
#define ASN1_MAX_ROHC_CTX_SESSION                           EN_ENC_MAX_ROHC_CONTEXT_SESSIONS_R4_BUTT/* PS_CAP_UNSUPPORT:NOT SUPPORT 此处作预留，现不支持  */

#define PS_WUE_CAP_REVERSE_DECOMPRS_DEP                     PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT 此处作预留，现不支持  */

#define PS_WUE_CAP_RFC3095_CTX_RELOC                        PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT 此处作预留，现不支持  */

#define PS_WUE_CAP_REVERSE_DECOMPRS_SUPPT                   PS_CAP_UNSUPPORT    /* PS_CAP_UNSUPPORT:NOT SUPPORT 此处作预留，现不支持  */

#define PS_WUE_CAP_MAX_HC_CONTEXT_SPACE                     8192                /* 协议值 : 512/1024/2048/4096/8192           */
#define ASN1_MAX_HC_CONTEXT_SPACE                           EN_ENC_MAX_HC_CONTEXT_SPACE_BY8192

/* RLC capability */
/*****************************************************************************
 结构名    : PS_WUE_MAX_RLC_AM_ENTITY_CNT
 ASN.1描述 : MaximumAM_EntityNumberRLC_Cap
             am4, am5, am6, am8, am16, am30
 结构说明  : 3个AM业务RB,外加RB2-RB4 三个信令RB,共计6个AM RB
              25.306 R9协议Table 5.1b升级到8个AM RB
*****************************************************************************/
#define PS_WUE_MAX_RLC_AM_ENTITY_CNT            (8)
#define ASN1_MAX_RLC_AM_ENTITY_CNT              EN_ENC_MAX_AM_ENTITY_NUM_RLC_CAP_AM8

/*****************************************************************************
 结构名    : PS_WUE_MAX_RLC_AM_WIN_SIZE
 ASN.1描述 : MaximumRLC_WindowSize ::=            ENUMERATED { mws2047, mws4095 }
 结构说明  :
*****************************************************************************/
#define PS_WUE_MAX_RLC_AM_WIN_SIZE              (2047)
#define ASN1_MAX_RLC_AM_WIN_SIZE                EN_ENC_MAX_RLC_WIN_SIZE_MWS2047

/*****************************************************************************
 结构名    : PS_WUE_MAX_TOTAL_AM_RLC_BUFFER_SIZE
 ASN.1描述 : TotalRLC_AM_BufferSize
             kb10, kb50, kb100, kb150, kb500, kb1000
 结构说明  : R3,R4的能力，Total receiving and transmitting RLC AM buffer
*****************************************************************************/
#define PS_WUE_MAX_TOTAL_AM_RLC_BUFFER_SIZE     (150)
#define ASN1_TOTAL_RLC_AM_BUF_SIZE              EN_ENC_TOTAL_RLC_AM_BUF_SIZE_KB150

/*****************************************************************************
 结构名    : PS_WUE_MAX_TOTAL_AM_RLC_AND_MAC_HS_BUFFER_SIZE
 ASN.1描述 : TotalRLC_AM_BufferSize_r5_ext
             kb200, kb300, kb400, kb750
 结构说明  : R5的能力，包括了MAC HS的缓存t
             Total receiving and transmitting RLC AM buffer and
             MAC-hs reordering buffer capability in kBytes.
             Note 1.
             The IE "Total RLC AM buffer size" values 200, 300, 400
             and 750 are not used in the INTER RAT HANDOVER INFO message.
*****************************************************************************/
#define PS_WUE_MAX_TOTAL_AM_RLC_AND_MAC_HS_BUFFER_SIZE      (750)
#define ASN1_TOTAL_RLC_AM_AND_MAC_HS_BUF_SIZE        EN_ENC_TOTAL_RLC_AM_BUF_SIZE_R5_EXT_KB750

/*****************************************************************************
 结构名    : PS_WUE_TWO_LOGIC_CHL_SUPPT
 ASN.1描述 : supportOfTwoLogicCh                        BOOLEAN,
 结构说明  : 是否支持两个逻辑信道
*****************************************************************************/
#define PS_WUE_TWO_LOGIC_CH_SUPPT               PS_CAP_UNSUPPORT                  /* PS_CAP_SUPPORT: support ,   PS_CAP_UNSUPPORT: not support   */

/* Transport channel capability */
#define PS_WUE_CAP_MAX_NO_BITS_RECV             (6400)                          /* Max no of bits received                    */
#define ASN1_MAX_NO_BITS_RECV                   EN_ENC_MAX_NO_BITS_B6400

#define PS_WUE_CAP_MAX_CONV_CODE_BITS_RECV      (640)                           /* Max convolutionally coded bits received    */
#define ASN1_MAX_CONV_CODE_BITS_RECV            EN_ENC_MAX_NO_BITS_B640

#define PS_WUE_CAP_TURBO_DEC_SUPPT              PS_CAP_SUPPORT                  /* PS_CAP_SUPPORT : Support turbo decoding    */

#define PS_WUE_CAP_MAX_TURB_CODE_BITS_RECV      (6400)                          /* Max turbo coded bits received              */
#define ASN1_MAX_TURB_CODE_BITS_RECV            EN_ENC_MAX_NO_BITS_B6400

#define PS_WUE_CAP_MAX_SIMU_TRANS_CH_DL         (8)                             /* Max Simultaneous TrChs DL                  */
#define ASN1_MAX_SIMU_TRANS_CH_DL               EN_ENC_MAX_SIMUL_TRANS_CHS_DL_E8

#define PS_WUE_CAP_MAX_SIMU_CCTRCH_CNT_DL       PS_WUE_MAX_CCTRCH_NUM           /* Max Simultaneous CCTRCH DL                 */

#define PS_WUE_CAP_MAX_TB_DL                    (PS_WUE_MAX_TB_CNT)             /* MaxTransportBlocksDL                       */
#define ASN1_MAX_TB_DL                          EN_ENC_MAX_TRANSP_BLOCK_DL_TB32

#define PS_WUE_CAP_MAX_TFC_DL                   (PS_WUE_MAX_DL_TFC_NUM)         /* MaxNumberOfTFC-InTFCS-DL                   */
#define ASN1_MAX_TFC_DL                         EN_ENC_MAX_NUM_OF_TFC_DL_TFC128

#define PS_WUE_CAP_MAX_TF_DL                    (64)                            /* MaxNumberOfTF                              */
#define ASN1_MAX_TF_DL                          EN_ENC_MAX_NUM_OF_TF_TF64

#define PS_WUE_CAP_MAX_NO_BITS_TRANS            (6400)
#define ASN1_MAX_NO_BITS_TRANS                  EN_ENC_MAX_NO_BITS_B6400

#define PS_WUE_CAP_MAX_CONV_CODE_BITS_TRANS     (640)                           /* Max conv coded bits transmitted            */
#define ASN1_MAX_CONV_CODE_BITS_TRANS           EN_ENC_MAX_NO_BITS_B640

#define PS_WUE_CAP_TURBO_ENC_SUPPT              PS_CAP_SUPPORT                  /* PS_CAP_SUPPORT : Support turbo encoding    */

#define PS_WUE_CAP_MAX_TURB_CODE_BITS_TRANS     (6400)                          /* Max turbo coded bits transmitted,          */
#define ASN1_MAX_TURB_CODE_BITS_TRANS           EN_ENC_MAX_NO_BITS_B6400

#define PS_WUE_CAP_MAX_SIMU_TRANS_CH_UL         (8)                             /* Max Simultaneous TrChs UL                  */
#define ASN1_MAX_SIMU_TRANS_CH_UL               EN_ENC_MAX_SIMUL_TRANS_CHS_UL_E8

#define PS_WUE_CAP_MAX_TB_UL                    (PS_WUE_MAX_TB_CNT)
#define ASN1_MAX_TB_UL                          EN_ENC_MAX_TRANSP_BLOCK_UL_TB32

#define PS_WUE_CAP_MAX_TFC_UL                   (PS_WUE_MAX_UL_TFC_NUM)
#define ASN1_MAX_TFC_UL                         EN_ENC_MAX_NUM_OF_TFC_UL_TFC128


#define PS_WUE_CAP_MAX_TF_UL                    (32)
#define ASN1_MAX_TF_UL                          EN_ENC_MAX_NUM_OF_TF_TF32

/* Security capability */
#define PS_WUE_CAP_SECURITY_NOT_SUPPORT_CIPH_ALG_CAP        (0x0001)            /* Ciphering algorithm capability, 0x0001:UEA0=1 */
#define PS_WUE_CAP_SECURITY_SUPPORT_CIPH_ALG_CAP            (0x0003)            /* Ciphering algorithm capability, 0x0003:UEA0=1&UEA1=1 */
#define PS_WUE_CAP_SECURITY_INTEG_PROT_ALG_CAP  (0x0002)                        /* Integrity protection algorithm capability 0x0001:UIA1=1 */

#define PS_WUE_CLASSMARK2_SIZE                  (5)                             /*协议值5,HI4131 规格4*/
#define PS_WUE_CLASSMARK3_MAX_SIZE              (34)                            /*协议值最大22,HI4131 规格最大14*/
#define PS_WUE_GERAN_IU_RADIO_ACS_CAP_MAX_SIZE  (22)                            /*协议值最大22,HI4131 规格最大22*/

#define PS_WUE_MAX_E_DCH_CCCH_BUF_BYTE_SIZE     (64)                            /* CCCH RB0缓存空间，非协议值，根据目前CELL UPDATE/RRC CONN REQ最长消息预留空间 */
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/








#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of WUeSpec.h */
