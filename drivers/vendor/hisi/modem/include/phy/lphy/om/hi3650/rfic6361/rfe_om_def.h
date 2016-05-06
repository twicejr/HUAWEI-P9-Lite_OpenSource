/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : rfe_om_def.h
 版 本 号   : 初稿
 作    者   : wangxu
 生成日期   : 2011年4月25日
 最近修改   :
 功能描述   : RFE OM 的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2011年4月25日
   作    者   : wangxu
   修改内容   : 创建文件
 --------------------------------------------------------------------------------
2.日  期   : 2011年 10 月 14日
   作  者   : shijiahong
   修改内容 : DTS2011101403388 合Hi6360可维可测
--------------------------------------------------------------------------------
3.日  期     : 2011年10月31日
  作  者     : wangxu
  修改内容   : DTS2011103100442 LCS PHASE I 代码合入

******************************************************************************/


#ifndef __RFE_OM_DEF_H__
#define __RFE_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum
{
    LPHY_REQ_RFE_INFO_REPORT_ID    = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_REQ, 0x0),
}LPHY_REQ_RFE_INFO_ENUM;

typedef enum
{
    //RFE_OM_SWITCH_ON = LPHY_TRUE,
    //RFE_OM_SWITCH_OFF = LPHY_FALSE,
    RFE_OM_SWITCH_OFF = LPHY_FALSE,
    RFE_OM_SWITCH_ON = LPHY_TRUE
}RFE_OM_SWITCH_ENUM;
typedef UINT16 RFE_OM_SWITCH_ENUM_UINT16;

typedef enum
{
    RFE_OM_INFO_TYPE_L1C_ITF       = 0,
    RFE_OM_INFO_TYPE_SLAVE_TIME_RECOVER
}RFE_OM_INFO_TYPE_ENUM;
typedef UINT16 RFE_OM_INFO_TYPE_ENUM_UINT16;

/*LPHY_REQ_RFE_INFO_REPORT_ID*/
typedef struct
{
    RFE_OM_INFO_TYPE_ENUM_UINT16    enRfeInfoType;
    RFE_OM_SWITCH_ENUM_UINT16       enRfeOmSwitch;
}LPHY_REQ_RFE_INFO_ENA_STRU;

#if 0
/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum
{
    LPHY_CNF_AFC_FIX_PDM_ENA         = OM_CMD_ID(LPHY_AFC_MID, OM_TYPE_CNF, 0x1),

}LPHY_CNF_AFC_ENUM;

typedef struct
{
    UINT32                  ulMsgId;    /*1 CNF消息ID*/
}LPHY_CNF_AFC_FIX_PDM_ENA_STRU;

#endif
/************************************************************
                           3. Sg数据结构定义
************************************************************/

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_RFE_CTU_LTE_INT0_EVT         = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_RFE_CTU_LTE_INT1_EVT,
    LPHY_TRACE_RFE_CTU_LTE_INT2_EVT,
    LPHY_TRACE_RFE_CTU_LTE_INT3_EVT,
    LPHY_TRACE_RFE_CTU_LTE_INT4_EVT,
    LPHY_TRACE_RFE_CTU_LTE_INT5_EVT,
    LPHY_TRACE_RFE_CTU_LTE_INT6_EVT,
    LPHY_TRACE_RFE_CTU_WCDMA_INT5_EVT,
    //LPHY_TRACE_RFE_CTU_GSM_INT6_EVT
    LPHY_TRACE_RFE_CTU_GSM_INT5_EVT
}LPHY_TRACE_RFE_CTU_EVENT_ENUM;
typedef enum
{
    LPHY_TRACE_RFE_HI6360_BEFORE_CHANGEFRQ_EVT        = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_TRACE, 0x40),
    LPHY_TRACE_RFE_HI6360_AFTER_CHANGEFRQ_EVT

}LPHY_TRACE_RFE_HI6360_EVENT_ENUM;
/*LPHY_TRACE_RFE_CTU_LTE_INT0_EVT ~ LPHY_TRACE_RFE_CTU_GSM_INT6_EVT*/
typedef struct
{
    UINT32  ulCtuInfo[6];
}LPHY_TRACE_RFE_CTU_EVENT_STRU;
typedef struct
{
    UINT32  ulHi6360Info[6];
}LPHY_TRACE_RFE_HI6360_EVENT_STRU;

/************************************************************
                           5. ERROR数据结构定义
************************************************************/
/************************************************************
                           7. Ind数据结构定义
************************************************************/
typedef enum
{
    LPHY_IND_RFE_L1C_DEM_CMD_ID    = OM_CMD_ID(LPHY_RFE_MID, OM_TYPE_IND, 0x0),
    LPHY_IND_RFE_L1C_EMCS_CMD_ID,
    LPHY_IND_RFE_TIME_RCVR_IND_ID
}LPHY_IND_RFE_L1C_CMD_ENUM;

enum RFE_OM_DEM_REQ_TYPE_ENUM
{
    RFE_OM_DEM_REQ_CAMP_MAINCELL           =0,
    RFE_OM_DEM_REQ_NCELL_BCCH_START,
    RFE_OM_DEM_REQ_NCELL_BCCH_FINISH,
    RFE_OM_DEM_REQ_SERV_BCCH_START,
    RFE_OM_DEM_REQ_SERV_BCCH_FINISH,
    RFE_OM_DEM_REQ_DL_SYSPARA_CHANGE,
    RFE_OM_DEM_REQ_HANDOVER_BLIND,
    RFE_OM_DEM_REQ_HANDOVER_NON_BLIND
};
typedef UINT16 RFE_OM_DEM_REQ_TYPE_ENUM_UINT16;


typedef struct
{
    UINT16                              usFreqInfo;
    UINT16                              usCellID;
    LTE_FRAME_TYPE_ENUM_UINT16          enMultiplexMode;
    LTE_CP_TYPE_ENUM_UINT16             enCPType;
    LTE_TDD_SPEC_SUBFRM_CFG_ENUM_UINT16 enSpecSFCfg;
    LTE_TDD_UD_CFG_ENUM_UINT16          enULDLCfg;
    UINT32                              ulFramePosition;
    LTE_BAND_WIDTH_ENUM_UINT16          enSysBandWidth;
    UINT8                               ucTxAntennaNum;
}RFE_OM_DL_CFG_PARA_STRU;

/*LPHY_IND_RFE_L1C_DEM_CMD_ID*/
typedef struct
{
    RFE_OM_DEM_REQ_TYPE_ENUM_UINT16         enFreqSwitchType;
    UINT8                                   ucIratHoFlag;      /*IRAT -> LTE切换标识，1有效*/
    UINT8                                   ucRsvd;
    RFE_OM_DL_CFG_PARA_STRU                 stDLCfgPara;
}RFE_OM_DEM_REQ_STRU;



enum RFE_OM_EMCS_REQ_TYPE_ENUM
{
    RFE_OM_EMCS_REQ_BAND_SCAN               = 0,
    RFE_OM_EMCS_REQ_FREE_CELL_SEARCH ,
    RFE_OM_EMCS_REQ_INTER_MEAS,
    RFE_OM_EMCS_REQ_INTER_MEAS_FINISH,
    RFE_OM_EMCS_REQ_INTER_SRCH_FINISH,
    RFE_OM_EMCS_REQ_INTER_MEAS_RELEASE,
    RFE_OM_EMCS_REQ_GAP_INTER_MODE,
    RFE_OM_EMCS_REQ_W_OCCASION,
    RFE_OM_EMCS_REQ_G_RSSI_OCCASION,
    RFE_OM_EMCS_REQ_G_BSIC_VERIFY_OCCASION,
    RFE_OM_EMCS_REQ_G_BSIC_CONFIRM_OCCASION,
    RFE_OM_EMCS_REQ_OCCASION_RELEASE,
    RFE_OM_EMCS_REQ_SLAVE_OCCASION_REQ,
//#ifdef BALONGV7_FEATURE_LCS
    RFE_OM_EMCS_REQ_LCS_OCCASION_REQ
//#endif
};
typedef UINT16 RFE_OM_EMCS_REQ_TYPE_ENUM_UINT16;


/*LPHY_IND_RFE_L1C_EMCS_CMD_ID*/
typedef struct
{
    UINT16                              usInterFreq;
    UINT16                              usRsvd;
    RFE_OM_EMCS_REQ_TYPE_ENUM_UINT16    enFreqSwitchType;
    LTE_BAND_WIDTH_ENUM_UINT16          enSysBandWidth;
    LTE_FRAME_TYPE_ENUM_UINT16          enMultiplexMode;
    UINT16                              usOccasionInms;
    UINT8                               ucWFrequencySwitchFlag;
}RFE_OM_EMCS_REQ_STRU;


typedef struct{
    union {
        struct{
            UINT32      gFnLow      :   11;//[0,10]  0-1325
            UINT32      gFnHigh     :   11;//[11,21] 0-2047
        } u;
        UINT32 bits;
    } gfn;

    UINT16 usGsmQb;         /*0-4999*/
	UINT8  aucRsv[2];    
}RFE_OM_GSM_TIMING_STRU;

typedef union{
    struct{
        UINT32      clockInChip             :   4;//[0,3] 0-15
        UINT32      chip                    :   12;//[4,15] 0-2559
        UINT32      slot                    :   4;//[16,19] 0-14
        UINT32      sfn                     :   12;//[20,31] 0-4095
    } u;
    UINT32 bits;
}RFE_OM_WCDMA_TIMING_UINION;

typedef union{
    struct{
        UINT32      chip                    :   12;//[0,11] 0-2559
        UINT32      slot                    :   4;//[12,15] 0-14
    } u;
    UINT32 bits;
}RFE_OM_WCDMA_SYSABS_UINION;


typedef union{
    struct{
        UINT32      ts                      :   15;//[0,14]  0-30719
        UINT32      sbfn                    :   4;//[15,18]  0-9
        UINT32      sfn                     :   10;//[19,28] 0-1023
    } u;
    UINT32 bits;
}RFE_OM_LTE_TIMING_UINION;

typedef union{
    struct{
        UINT32      cycle					:   3; //[0,2]
        UINT32      rsv1					:   1; //[3]
        UINT32      ts                      :   15;//[4,18]  0-30719
        UINT32      rsv2                    :   1; //[19]  
        UINT32      sbfn                    :   4; //[20,23] 0-9
    } u;
    UINT32 bits;
}RFE_OM_LTE_ABS_TIMING_UINION;

typedef struct
{
    UINT32 ulSfn;     //子帧号
    UINT32 ulChip;    //1/32chip 为单位
}RFE_OM_TDS_TIMING_STRU;


typedef struct{
    RFE_OM_LTE_ABS_TIMING_UINION   uLteTiming;
    RFE_OM_WCDMA_TIMING_UINION     uWcdmaTiming;
    RFE_OM_WCDMA_SYSABS_UINION     uWcdmaSysAbsOffs;
    RFE_OM_GSM_TIMING_STRU         stGsmTiming;
    RFE_OM_TDS_TIMING_STRU         stTdsTiming;
    UINT32					       ulCtuDsp;
    UINT8                   	   ucValidFlg;
	UINT8						   aucRsv[3];
}RFE_OM_IRAT_TIMING_STRU;

/*LPHY_IND_RFE_TIME_RCVR_IND_ID*/
typedef struct{
    RFE_OM_IRAT_TIMING_STRU         stOldTime;
    RFE_OM_IRAT_TIMING_STRU         stNewTime;
    RFE_OM_LTE_ABS_TIMING_UINION    stRecoveredLteTime;
    UINT32                          ulDeltaT;
}RFE_OM_SLAVE_TIME_RECOVER_IND_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RFE_OM_DEF_H__ */


