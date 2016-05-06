/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tds_timing_om_def.h
  版 本 号   : 初稿
  作    者   : xuyoujiang
  生成日期   : 2012年10月16日
  最近修改   :
  功能描述   : om定义文件
  函数列表   :
  修改历史   :

******************************************************************************/
#ifndef __TDS_TIMING_OM_DEF_H__
#define __TDS_TIMING_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include "om_base_def.h"

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
enum __TDS_REQ_TIMING__
{
    TDS_REQ_TIMING_REPORT_TRACE_ENA                = OM_TCMD_ID(TPHY_TIMING_MID, OM_TYPE_REQ, 0x1),
    TDS_REQ_TIMING_REPORT_SG_ENA,
    TDS_REQ_TIMING_REPORT_DATA_ENA,
    TDS_REQ_TIMING_TREND_EST_ENA

};
typedef enum
{
    TIMING_OM_SWITCH_OFF = 0,
    TIMING_OM_SWITCH_ON
}TDS_TIMING_OM_SWITCH_ENUM;
typedef UINT16 TDS_TIMING_OM_SWITCH_ENUM_UINT16;

/*定时跟踪 trace上报使能*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingReportTraceEn;
}TDS_REQ_TIMING_REPORT_TRACE_ENA_STRU;

/*定时跟踪 sg上报使能*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingReportSgEn;
}TDS_REQ_TIMING_REPORT_SG_ENA_STRU;

/*定时跟踪 DATA上报使能*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingReportDataEn;
}TDS_REQ_TIMING_REPORT_DATA_ENA_STRU;

/*定时跟踪 debug上报使能*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingTrendEstEn;
}TDS_REQ_TIMING_TREND_EST_ENA_STRU;

/*快速预同步 trace上报使能*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingIdlFstTraceEn;
}TDS_REQ_TIMING_IDL_FST_TRACE_ENA_STRU;

/*快速预同步 debug上报使能*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingIdlFstDebugEn;
}TDS_REQ_TIMING_IDL_FST_DEBUG_ENA_STRU;
/*
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16                      usChipEst;
}TDS_REQ_TIMING_CHIP_EST_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16                      usAdjustPeriod;
}TDS_REQ_TIMING_ADJUST_PERIOD_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enCfgHarqSwitchEna;
}TDS_REQ_TIMING_CFG_HARQ_SWITCH_ENA_STRU;
*/

/************************************************************
                           2. CNF数据结构定义
************************************************************/
enum __TDS_CNF_TIMING__
{
    TDS_CNF_TIMING_CFG_HARQ_SWITCH_ENA          = OM_CMD_ID(TPHY_TIMING_MID, OM_TYPE_CNF, 0x1),

};

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __TDS_TRACE_TIMING_ENUM__
{
    TDS_TRACE_TIMING_IDLE_FAST_SYNC                              = OM_TCMD_ID(TPHY_TIMING_MID, OM_TYPE_TRACE, 0x1),
    TDS_TRACE_TIMING_CAL_PAR,                               //计算PAR
    TDS_TRACE_TIMING_TREND_ESTIMATE,                        //迟早门
    TDS_TRACE_TIMING_CHIP_ESTIMATE,                         //chip级估计
    TDS_TRACE_TIMING_UNCHIP_ESTIMATE,                       //unchip级估计
    TDS_TRACE_TIMING_OFFSET_ADJUST,
    TDS_TRACE_TIMING_CS_UNCHIP_DWPTS,                       //小区搜索chip级以下定时dwpts时域数据
    TDS_TRACE_TIMING_CS_UNCHIP_PARA,                        //小区搜索chip级以下定时中间量
    TDS_TRACE_TIMING_PDP_MODULE,
    TDS_TRACE_TIMING_IDLE_FAST_SYNC1,
    TDS_TRACE_TIMING_IDLE_FAST_SYNC2,
    TDS_TRACE_TIMING_IDLE_FAST_SYNC3,
    TDS_TRACE_TIMING_IDLE_FAST_SYNC4,
    TDS_TRACE_TIMING_JD_4X_PWR,
    TDS_TRACE_TIMING_DWPTS_1X_CHE,                         
    TDS_TRACE_TIMING_MID_1X_CHE,                         
    TDS_TRACE_TIMING_DWPTS_1X_FIR,   
    TDS_TRACE_TIMING_MID_1X_FIR,
    TDS_TRACE_TIMING_JD_1X_PWR,
    TDS_TRACE_TIMING_IDLE_CELL,
}TDS_TRACE_TIMING_ENUM;
typedef UINT16 TDS_TRACE_TIMING_ENUM_UINT16;
typedef struct
{
    INT32 lChannelPulsePwr[128];                 //  128点径功率
}TDS_TRACE_TIMING_PDP_MODULE_STRU;
typedef struct
{
    UINT16 usAdjustCnt;	                         //定时调整步长计数
    UINT16 usAdjustPeriod;	                     //调整周期
    UINT16 usTdsCurState;                        //当前状态
    UINT16 usSubFrmNum;                           /*子帧号*/
    UINT16 usTdsSlotNum;                         //当前时隙号
    UINT16 usMsn;                                 /*目标信道激活窗首位置*/
    UINT16 usSF;                                  /*扩频因子*/
    INT16  sPAR;
    INT32  lElevenPathPwr[11];                    //主径前五后五共十一径功率
}TDS_TRACE_TIMING_CAL_PAR_STRU;

typedef struct
{
    UINT16 usTdsCurSumFrm;                  //IDLE态当前子帧号
    UINT16 usTdsPreSumFrm;                  //IDLE态下一子帧号
    UINT16 usPichSlotNum;                   //IDLE态PICH时隙号
    UINT16 usPchSlotNum;                    //IDLE态PCH时隙号
    UINT16 usPichChnFlag;                   //IDLE态PICH信道标识
    UINT16 usPchChnFlag;                    //IDLE态PCH信道标识
    UINT16 usForceAwakeFlag;                //强制唤醒标识
    UINT16 usTdsTaskRfokFlag;               //RF配置完成标识
    INT16  sCellID;                         //小区ID
    INT16  sDwptsFirstPath;
    UINT16 usSyncActiveFlag;                //同步激活标识
    INT16  sJdFirstPath;                  //联合1x首径
    INT32  lJd1xPosMaxPwr;
    INT32  lJd1xNoisePwrSum;                //噪声功率累和
    INT16  sJd4xPosMax;
    INT16  sPosMax;
    INT16  sKLength;
    INT16  sPreFrameOffSet;                 //1/4chip精度
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU;
typedef struct
{
    INT32  al4xRfData[1024];
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU1;
typedef struct
{
    INT32  al4xRfData[1024];
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU2;
typedef struct
{
    INT32  al4xRfData[1024];
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU3;
typedef struct
{
    INT32  al4xRfData[1024];
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU4;
typedef struct
{
    INT32  alJd4xPwr[512];
}TDS_TRACE_TIMING_JD_4X_PWR_STRU;
typedef struct
{
    INT16  alDwpts1xChe[256];
}TDS_TRACE_TIMING_DWPTS_1X_CHE_STRU;
typedef struct
{
    INT16  alMid1xChe[256];
}TDS_TRACE_TIMING_MID_1X_CHE_STRU;
typedef struct
{
    INT16  alDwpts1xFir[256];
}TDS_TRACE_TIMING_DWPTS_1X_FIR_STRU;
typedef struct
{
    INT16  alMid1xFir[256];
}TDS_TRACE_TIMING_MID_1X_FIR_STRU;
typedef struct
{
    INT32  alJd1xPwr[16];
}TDS_TRACE_TIMING_JD_1X_PWR_STRU;
typedef struct
{
    INT16 sCellNum;
    INT16 sCellPos;
    INT16 asCellId[6];
}TDS_TRACE_TIMING_IDLE_CELL_STRU;


typedef struct
{
    INT16  asDwptsRf[256];
}TDS_TRACE_TIMING_CS_UNCHIP_DWPTS_STRU;
typedef struct
{
    INT16  sDwptsId;
    INT16  sRshift;
    INT16  sDwptsAdjustCnt;
    INT16  sDwptsPeriod;
    UINT16 usPar;
    INT16  sDwptsSs;
}TDS_TRACE_TIMING_CS_UNCHIP_PARA_STRU;

typedef struct
{
    INT16 sDemoTimeOffset;                       //解调定时偏差量
    INT16 sADInterOffset;                        //AD采样定时整数部分
    INT16 sADFracOffset;                         //AD采样定时小数部分
    UINT16 usTrendEstAdjustCnt;                 //迟早门调整步长
    UINT16 usTrendEstAdjustPeriod;              //迟早门调整周期
    INT16  sSamplingTimeOffset;
}TDS_TRACE_TIMING_TREND_ESTIMATE_STRU;

typedef struct
{
    INT32 lMeanPAR;                           //累和峰均比均值
    INT32 lAlphaPAR;
    INT32 lNoisePowerLimit;                   //噪声功率门限
    INT32 lLeakingTh;
    INT16 sFirstPath;                           //首径
    INT16 sChipEstSs;                           //chip级偏差结果
    INT16 sCurrentAGC;
    INT16  sRes;
    INT32 alChipEstPDPSum[16];
}TDS_TRACE_TIMING_CHIP_ESTIMATE_STRU;

typedef struct
{
    UINT16 usCompensateFlag;                     //unchip级补偿标志
    INT16 sPreUnChipEstSs;                         //unchip级偏差估计结果
    INT16 sFiltUnChipEstSs;                         //unchip级偏差估计结果,滤波后s
    UINT16 usFilterSumCnt;                       //滤波计数
}TDS_TRACE_TIMING_UNCHIP_ESTIMATE_STRU;

/*定时跟踪调整标识结构体*/
typedef struct
{
    INT32  lTimingAdjOffset;
    INT16  sUnChipEstSs;
    INT16  sDemoTimeOffset;
    INT16  sADFracOffset;
    UINT16 usTimingAdjFlag;
    UINT16 usTimingAdjCompleteFlag;
    UINT16 usTimingStateFlag;
    UINT16 usTimingSampleFilterAdjFlag;
    INT16  sTrendEstInvalidFlag;
}TIMING_OFFSET_ADJUST_FLAG;

/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum __TDS_ERROR_TIMING_ENUM__
{
    TDS_ERROR_TIMING_INPUT_CHANNEL_ESTIMATE           = OM_TCMD_ID(TPHY_TIMING_MID, OM_TYPE_ERROR, 0x1),
    TDS_ERROR_TIMING_CHIP_ESTIMATE_RESULT,
    TDS_ERROR_TIMING_UNCHIP_ESTIMATE_RESULT,
    TDS_ERROR_TIMING_SAMPLING_TREND_ESTIMATE_RESULT,
    TDS_ERROR_TIMING_PARA_RANGE                                         //参数范围
}TDS_ERROR_TIMING_ENUM;
typedef UINT16 TDS_ERROR_TIMING_ENUM_UINT16;

typedef struct __TDS_TIMING_CB_NUM_ZERO_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCplus;
    UINT16 usCminus;
}TDS_ERROR_TIMING_CB_NUM_ZERO_STRU;

/************************************************************
                           6. DEBUG数据结构定义
************************************************************/
#define     OM_TIMING_MAX_CFG_REG_IMG_LEN       ((0xA0 - 0x20) / 4 + 1)       /*Turbo配置的数据长度, DW, 注意需要软硬件接口同步*/

typedef enum __TDS_DEBUG_TIMING_ENUM__
{
    TDS_DEBUG_TIMING_IDLE_FAST_SYNC                   = OM_TCMD_ID(TPHY_TIMING_MID, OM_TYPE_DEBUG, 0x1),
    TDS_DEBUG_TIMING_TREND_ESTIMATE,                        //迟早门
    TDS_DEBUG_TIMING_PDP_MODULE,                            //PDP模块
    TDS_DEBUG_TIMING_CAL_PAR,                               //计算PAR
    TDS_DEBUG_TIMING_INTER_MODULE,                          //插值加密模块
    TDS_DEBUG_TIMING_INTER_COMP_MODULE,                     //插值加密比较模块
    TDS_DEBUG_TIMING_CHIP_ESTIMATE,                         //CHIP级估计
    TDS_DEBUG_TIMING_UNCHIP_ESTIMATE,                       //unchip级估计

}TDS_DEBUG_TIMING_ENUM;
typedef UINT16 TDS_DEBUG_TIMING_ENUM_UINT16;


typedef struct __TDS_DEBUG_TIMING_CFG_PARA__
{
    INT32 alDwPTSChannelPulsePwr[128];
    INT32 alIdleDwPTSChEst[128];
    INT32 alIdleMidambleChEst[128];
}TDS_DEBUG_TIMING_IDLE_FAST_SYNC_STRU;

typedef struct
{
    INT16 asChInter[256];                       //信道估计插值数组
    INT32 alInterPwr[128];                      //迟早门插值功率累和数组
    INT32 alChEstSum[256];
    INT32 alChInterSum[256];
    INT32 alChEstPwrSum[128];
    INT32 alInterPwrSum[128];
    INT32 lMpyRealImagAdd;
    INT32 lAddRealImag;
    INT32 lMaxChannelPulsePwr;                  //最大值功率
    INT16 sTEDIntegraph;                        //迟早门积分器
    INT16  sReserved;
}TDS_DEBUG_TIMING_TREND_ESTIMATE_STRU;

typedef struct
{
    INT32 lChannelPulsePwr[128];                 //  128点径功率
    INT32 lMaxChannelPulsePwr;
    INT32 lPAR;                                  //峰均比
    INT16 *pInChannelEst;                        //输入信道估计结果
    INT16 sRShift;                               //右移量
}TDS_DEBUG_TIMING_PDP_MODULE_STRU;

typedef struct
{
    INT16 sPosMax;
    INT16 sReserved;
    INT32 lNoisePwr;                             //累和噪声功率
    INT32 lMaxNoisePwr;                          //最大噪声功率
    INT32 lPAR;
    INT32 lElevenPathPwr[11];                    //主径前五后五共十一径功率
    INT32 alChEstMidamble[128];
}TDS_DEBUG_TIMING_CAL_PAR_STRU;

typedef struct
{
//    INT32 lThreePathOutInter[96];               //前三径插值数组，需要初始化
//    INT32 lTwoPathOutInter[96];                 //前二径插值数组
    INT32 lThreePathOutInterPwrSum[96];         //前三径插值功率累和数组
    INT32 lTwoPathOutInterPwrSum[96];           //前二径插值功率累和数组
}TDS_DEBUG_TIMING_INTER_MODULE_STRU;

typedef struct
{
    INT32 sChipEstPDPSum[19];                   //chip级估计累和PDP
    INT32 sOutInterPower[96];                   //32倍速插值功率数组
    UINT16 usCompensateFlag;                     //定时补偿生效标识
    INT16  sReserved;
}TDS_DEBUG_TIMING_INTER_COMP_MODULE_STRU;

typedef struct
{
    INT16 sPosMax;
    INT16 sFirstPath;                           //首径
    INT16 sFirstPathSuccFlag;                    //首径搜索成功标识
    UINT16  usFPNoiseFactor;                    //首径搜索噪声判决因子
    INT32 lNoisePowerLimit;                     //噪声功率门限
    INT32 lPosMaxPwr;

}TDS_DEBUG_TIMING_CHIP_ESTIMATE_STRU;

typedef struct
{
    INT32 lPosMaxPwr;
    INT16 sPosMax;
    INT16 sUnChipEstSs;                         //unchip级偏差估计结果
    UINT16 usFilterSumCnt;								 //unchip级估计滤波累和计数
    UINT16 usRes;
}TDS_DEBUG_TIMING_UNCHIP_ESTIMATE_STRU;

/* 全局变量定义*/

extern TDS_REQ_TIMING_REPORT_TRACE_ENA_STRU          gstReqTimingReportTraceEna;
extern TDS_REQ_TIMING_REPORT_DATA_ENA_STRU           gstReqTimingReportDataEna;
extern TDS_REQ_TIMING_REPORT_SG_ENA_STRU             gstReqTimingReportSgEna;
extern TDS_REQ_TIMING_TREND_EST_ENA_STRU             gstReqTimingTrendEstEna;
extern TDS_REQ_TIMING_IDL_FST_TRACE_ENA_STRU         gstReqTimingIdlFstTraceEna;
extern TDS_REQ_TIMING_IDL_FST_DEBUG_ENA_STRU         gstReqTimingIdlFstDebugEna;

/*trace结构体*/
extern TDS_TRACE_TIMING_TREND_ESTIMATE_STRU          gstTdsTraceTimingTrendEstimate;
extern TDS_TRACE_TIMING_CHIP_ESTIMATE_STRU           gstTdsTraceTimingChipEstimate;
extern TDS_TRACE_TIMING_UNCHIP_ESTIMATE_STRU         gstTdsTraceTimingUnchipEstimate;
//extern TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU          gstTdsTraceTimingIdleFastSync;
extern TDS_TRACE_TIMING_CS_UNCHIP_PARA_STRU          gstTdsTraceTimingCsUnchip;
extern TDS_TRACE_TIMING_CAL_PAR_STRU                 gstTdsTraceTimingCalPar;

extern void TDS_TIMING_OmReq(UINT32 ulMsgId, UINT32 ulSessionId, void* pstMsg, UINT32 ulMsgSize);
#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* __cplusplus */


#endif /* __TIMING_OM_H__ */
