/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : rfd_om_def.h
 版 本 号   : 初稿
 作    者   : wangxu
 生成日期   : 2011年4月25日
 最近修改   :
 功能描述   : RFD OM 的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2012年1月9日
   作    者   : shijiahong
   修改内容   : 创建文件
 --------------------------------------------------------------------------------
 ******************************************************************************/

#ifndef __RFD_OM_DEF_H__
#define __RFD_OM_DEF_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#define MAX_SSI_NUM         (32)


typedef enum
{
    LPHY_RFD_FREQ_SWITCH_OM_REQ  = OM_CMD_ID(LPHY_RFD_MID, OM_TYPE_REQ, 0x0),/*切频上报请求*/
    LPHY_RFD_AGC_DC_OM_REQ                                                     /*AGC/DC配置上报请求*/
}LPHY_RFD_OM_REQ_ENUM;

typedef enum
{
    RFD_FREQ_SWITCH_OM_OFF = 0x0,
    RFD_FREQ_SWITCH_OM_ON,
    RFD_FREQ_SWITCH_OM_RD
}RFD_FREQ_SWITCH_OM_SWITCH_ENUM;
typedef UINT16 RFD_FREQ_SWITCH_OM_SWITCH_ENUM_UINT16;
typedef struct
{
	RFD_FREQ_SWITCH_OM_SWITCH_ENUM      enRfdOmSwitch;
}LPHY_REQ_RFD_REPORT_ENA_STRU;
typedef enum
{
    RFD_AGC_DC_CFG_OM_OFF = 0x0,
    RFD_AGC_DC_CFG_OM_ON
}RFD_AGC_DC_CFG_OM_SWITCH_ENUM;


typedef struct
{
    UINT16 usBand;
    UINT16 usBw;
    UINT32 ulFreq;
}RFD_BAND_INFO_STRU;

typedef struct
{
    RFD_FREQ_SWITCH_OM_SWITCH_ENUM  enRptSwitch;
    UINT32                          ulRfSsiCmd[10];  /*切频完成后产生的ssi指令*/
    RFD_BAND_INFO_STRU              stDestBandInfo;  /*目标band信息*/
    RFD_BAND_INFO_STRU              stCurrBandInfo;  /*当前band信息*/
}RFD_FREQ_SWITCH_OM_STRU;

typedef struct
{
    RFD_AGC_DC_CFG_OM_SWITCH_ENUM   enAgcDcCfgRpt;
    UINT16                          usAnt0RfGainCode; /*天线0的aagc code*/
    UINT16                          usAnt0RfDCCode;   /*天线0的dc code*/
    UINT16                          usAnt1RfGainCode; /*天线1的aagc code*/
    UINT16                          usAnt1RfDCCode;   /*天线1的dc code*/
}RFD_AGC_DC_CFG_OM_STRU;

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_RFD_SSI_RPT         = OM_CMD_ID(LPHY_RFD_MID, OM_TYPE_TRACE, 0x0),
}LPHY_TRACE_RFD_ENUM;
/*射频切换类型定义*/
enum RF_RFIC_SWITCH_TYPE
{
    RF_IDLE_INTERMEAS_DL = 0,   /*IDLE 异频测量，切频操作*/
    RF_IDLE_INTERMEAS_FINISH,   /*IDLE 异频测量结束回切操作*/
    RF_GAP_DL,                  /*GAP模式，切频操作*/
    RF_GAP_FORCE_CLOSE,         /*GAP模式DSP强制结束，回切*/
    RF_RL_SETUP_DL,             /*下行信道建立,配置下行射频通道*/
    RF_RL_SETUP_UL,             /*上行信道建立,配置上行射频通道*/
    RF_ENTER_GU_OCCASION,       /*进入GU Occasion*/
    RF_OCCASION_FINISH,         /*退出occasion*/
    RF_ENTER_LTE_OCCASION,       /*进入LTE occasion*/
	RF_RFIC_SWITCH_BUTT
    
};

typedef UINT16 RFE_RFIC_SWITCH_TYPE_ENUM_UINT16;

/*add by ljh*/
typedef struct
{
    RFE_RFIC_SWITCH_TYPE_ENUM_UINT16      	enRfDrvCmdType;     	/*射频前端请求类型*/
	UINT16                                   ulSsiCmdNum;
	UINT32 									aulCmdBuffer[MAX_SSI_NUM];
}RF_FREQ_SWITCH_STRU;

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __RFD_OM_DEF_H__ */

