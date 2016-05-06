/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : tds_afc_om_def.h
 版 本 号   : 初稿
 作    者   : xuyoujiang
 生成日期   : 2012年12月29日
 最近修改   :
 功能描述   : TDS AFC om的定义文件
 函数列表   :
 修改历史   :
 1.日    期   : 2012年12月29日
   作    者   : xuyoujiang
   修改内容   : 创建文件
   
******************************************************************************/
#ifndef __TDS_AFC_OM_DEF_H__
#define __TDS_AFC_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                     包含其它模块的头文件
************************************************************/
#include "om_base_def.h"

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
{//TBD,LPHY?
    TDS_REQ_AFC_REPORT_TRACE_ENA   = OM_TCMD_ID(TPHY_AFC_MID, OM_TYPE_REQ, 0x1),
    TDS_REQ_AFC_REPORT_SG_ENA,
    TDS_REQ_AFC_REPORT_DATA_ENA,
    TDS_REQ_AFC_RF_STUB_ENA,
    TDS_REQ_AFC_INTER_LOOP_ENA,
    TDS_REQ_AFC_OUT_LOOP_ENA,
    TDS_REQ_AFC_CFG_PARA_ENA
}TDS_REQ_AFC_ENUM;

typedef enum
{
    TDS_AFC_OM_SWITCH_OFF = 0,
    TDS_AFC_OM_SWITCH_ON
}TDS_AFC_OM_SWITCH_ENUM;
typedef UINT16 TDS_AFC_OM_SWITCH_ENUM_UINT16;

/*AFC trace上报使能*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcReportTraceEn;
}TDS_REQ_AFC_REPORT_TRACE_ENA_STRU;

/*AFC sg画图上报使能*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcReportSgEn;
}TDS_REQ_AFC_REPORT_SG_ENA_STRU;

/*AFC debug上报使能*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcReportDataEn;
}TDS_REQ_AFC_REPORT_DATA_ENA_STRU;

/*AFC 内环调整使能*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcInterLoopEn;
}TDS_REQ_AFC_INTER_LOOP_ENA_STRU;

/*AFC 外环调整使能*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcOutLoopEn;
}TDS_REQ_AFC_OUT_LOOP_ENA_STRU;

/*AFC射频调整打桩上报使能*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcRFStubEn;
   UINT16 usFrqOffset;
}TDS_REQ_AFC_RF_STUB_ENA_STRU;

/*配置参量上报使能*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcCfgParaEn;
}TDS_REQ_AFC_CFG_PARA_ENA_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/



/************************************************************
                           3. TRACE数据结构定义
************************************************************/
typedef enum
{   //TBD LPHY?
    TDS_TRACE_AFC_FRQ_TR_PERIOD       = OM_TCMD_ID(TPHY_AFC_MID, OM_TYPE_TRACE, 0x1),
    TDS_TRACE_AFC_FRQ_CTH_PERIOD,
    TDS_TRACE_AFC_PRE_LOCK_IND_JUDGE,
    TDS_TRACE_AFC_LAST_LOCK_IND_JUDGE,
    TDS_TRACE_AFC_FILTER_MODULE,
    TDS_TRACE_AFC_RF_ADJUST,
    TDS_TRACE_AFC_INPUT_MEMORY,
    TDS_TRACE_TIMAFC_COMMON,
    TDS_TRACE_AFC_PRE_MID,
    TDS_TRACE_AFC_POS_MID,
    TDS_TRACE_AFC_MID_CHE,
    TDS_TRACE_AFC_DWPTS_CHE,
    TDS_TRACE_AFC_RECST,
    TDS_TRACE_AFC_CP_MODULE,
    TDS_TRACE_AFC_MD_MODULE,
    TDS_TRACE_AFC_CELLID_RECST,
    TDS_TRACE_AFC_DWPTS_FIR,
    TDS_TRACE_AFC_DWPTS_CHERESULT,
    TDS_TRACE_AFC_MID_CHE_PWR,
    TDS_TRACE_AFC_MID_DWPTS_PWR,
    TDS_TRACE_AFC_MID_FIR,
    TDS_TRACE_AFC_CP_FREQ_LIST,
    TDS_TRACE_AFC_MD_FREQ_LIST,
    TDS_TRACE_AFC_HIGH_SPEED_PARA,
    TDS_TRACE_AFC_HIGH_SPEED_DATA,
}TDS_TRACE_AFC_ENUM;


/*AFC频率跟踪周期内输出结果*/
typedef struct
{
    UINT16 usFrqTrAdjPeriod;        //频率跟踪调整周期
    UINT16 usFreqTrAdjustCnt;       //频率跟踪周期计数器
    UINT16 usMidID;                  //midamble码id;
    INT16  sFrqTrEstOffset;         //频率跟踪频偏估计结果
    INT32  lConjMultyISum;          //频率跟踪复乘结果I信号累和
    INT32  lConjMultyQSum;          //频率跟踪复乘结果Q信号累和
    UINT16 usTdsCurState;           //当前状态
    UINT16 usTdsSlotNum;
}TDS_TRACE_AFC_FRQ_TR_PERIOD_STRU;

/*AFC精频偏捕获周期内输出结果*/
typedef struct
{
    UINT16 usSINRAvg;               //软值信噪比线性值
    UINT16 usFrqCthAdjPeriod;       //精频偏捕获调整周期
    UINT16 usFreqCthAdjustCnt;      //精频偏捕获周期计数器
    INT16  sFrqCthEstOffset;        //精频偏捕获频偏估计结果
    INT32  lFreqCthIsum;            //精频偏捕获复乘结果I信号累和
    INT32  lFreqCthQsum;            //精频偏捕获复乘结果Q信号累和
    INT16  asUserList[8];           //激活用户集合
}TDS_TRACE_AFC_FRQ_CTH_PERIOD_STRU;
typedef struct
{
    UINT16 usSINRAvg;               //软值信噪比线性值
    UINT16 usFrqCthAdjPeriod;       //精频偏捕获调整周期
    UINT16 usFreqCthAdjustCnt;      //精频偏捕获周期计数器
    INT16  sFrqCthEstOffset;        //精频偏捕获频偏估计结果
    INT16  sFrqServEstOffset;
    INT16  sFrqNeighEstOffset;
    INT32  lServScaleSum;
    INT32  lFreqCthIsum;            //精频偏捕获复乘结果I信号累和
    INT32  lFreqCthQsum;            //精频偏捕获复乘结果Q信号累和
    UINT16 ausCellIdList[12];
}TDS_TRACE_AFC_CP_MODULE_STRU;
typedef struct
{
    INT32 alCorrRlst[49];
    INT8  acPCoefList[23];
    INT8  cRes;
    INT32 lSFctrISum;
    INT32 lSFctrQSum;
    INT32 lOutAngle;
    INT32 lMidNoise;
    INT32 lDwptsNoise;
    INT16 sFrqCthEstOffset;
    INT16 sFrqServEstOffset;
    INT32 lSFctrISum2;
    INT32 lSFctrQSum2;
    INT32 lOutAngle2;
}TDS_TRACE_AFC_MD_MODULE_STRU;

/*AFC未判决前锁定失锁指示模块OM上报*/
typedef struct
{
    UINT16 usInterLoopStatusFlag;   //内环状态标识
    UINT16 usOLLockInd;             //外环锁定指示
    UINT16 usOLUnLockInd;           //外环失锁指示
    UINT16 usILLockInd;             //内环锁定指示
    UINT16 usFrqResultValid;        //频偏结果无效标识
    INT16  sUnLockCnt;              //失锁计数
//    UINT16 usReserved;
}TDS_TRACE_AFC_PRE_LOCK_IND_JUDGE_STRU;

/*AFC判决后锁定失锁指示模块OM上报*/
typedef struct
{
    UINT16 usInterLoopStatusFlag;   //内环状态标识
    INT16  sFreqOffsetResult;       //输出内环或者外环结果
    UINT16 usFilterResetFlag;       //滤波器重置指示
    INT16  sUnLockCnt;              //失锁计数
    UINT16 usOLLockInd;             //外环锁定指示
    UINT16 usOLUnLockInd;           //外环失锁指示
    UINT16 usILLockInd;             //内环锁定指示
    UINT16 usReserved;
}TDS_TRACE_AFC_LAST_LOCK_IND_JUDGE_STRU;

/*AFC滤波模块OM上报*/
typedef struct
{
    INT32  lFilterResult;           //滤波结果
    INT16  sFilterInitIndex;        //滤波初始索引
    INT16  sFilterCnt;              //滤波计数    
    UINT16 usFilterCoefKLow;        //最低滤波系数
    UINT16 usReserved;
}TDS_TRACE_AFC_FILTER_MODULE_STRU;

/*AFC射频调整模块OM上报*/
typedef struct
{
    UINT32 ulConvCoefppm;           //折算因子
    UINT16 usSysFreq;               //载频频点
    UINT16 usPDMInitial;            //PDM调整基准值
    UINT16 usRFFrqOffset;           //射频频率调整量
    UINT16 usReserved;
}TDS_TRACE_AFC_RF_ADJUST_STRU;
typedef struct
{
    INT16 asChEstMidamble[256];        /*获取信道估计结果，与定时共用*/
    INT16 asJDRxData[88];             //JD软值结果，由联合检测传入
//    INT16 asExtendMidamble[308];       //左右开窗5chip midamble码
}TDS_TRACE_AFC_INPUT_MEMORY_STRU;
typedef struct
{
    UINT16 usSubFrmNum;                           /*子帧号*/
    UINT16 usPreSubFrmNum;                        /*上一个子帧号*/
    UINT16 usAFCSubFrmNum;                        /*AFC子帧号*/
    UINT16 usAFCPreSubFrmNum;                     /*AFC上一个子帧号*/
    UINT16 usK;                                   /*用户数*/
    UINT16 usMsn;                                 /*目标信道激活窗首位置*/
    UINT16 usSF;                                  /*扩频因子*/
    UINT16 usTdsSlotNum;                          /*当前时隙号*/
    INT32 *plFirAddr;                             /*Fir时域数据*/
    INT32 lMidNoise;
    INT32 lDwptsNoise;
    INT16 sServScale;
    INT16 sRes;                            /*Fir时域数据*/
}TDS_TRACE_TIMAFC_COMMON_STRU;

typedef struct
{
    INT32  alServNeighPow;   /*主临区功率*/
    INT16* psReCst[4];
    UINT16 usCellId;
    INT16  sServNeighSs;
    INT16  sCnt;
    INT16  sRes;
}TDS_AFC_CELLID_RECST_STRU;

typedef struct
{
    INT16 sIndex[3];
    INT16 sRes;
    TDS_AFC_CELLID_RECST_STRU astCellIdReCst[3];
}TDS_TRACE_AFC_CELLID_RECST_STRU;

typedef struct
{
    INT16 asPreMidFir[128];        
}TDS_TRACE_AFC_PRE_MID_STRU;

typedef struct
{
    INT16 asPosMidFir[128];        
}TDS_TRACE_AFC_POS_MID_STRU;

typedef struct
{
    INT16 asMidChEst[12];        
}TDS_TRACE_AFC_MID_CHE_STRU;

typedef struct
{
    INT16 asDwptsChEst[12];        
}TDS_TRACE_AFC_DWPTS_CHE_STRU;

typedef struct
{
    INT32 galReConstructData[192];      
}TDS_TRACE_AFC_RECST_STRU;

typedef struct
{
    INT16 asDwptsFir[256];      
}TDS_TRACE_AFC_DWPTS_FIR_STRU;

typedef struct
{
    INT16 asDwptsChe[256];      
}TDS_TRACE_AFC_DWPTS_CHERESULT_STRU;

typedef struct
{
    INT32 asMidChePwr[6];        
}TDS_TRACE_AFC_MID_CHE_PWR_STRU;

typedef struct
{
    INT32 asDwptsChePwr[6];        
}TDS_TRACE_AFC_MID_DWPTS_PWR_STRU;

typedef struct
{
    INT16 asMidFir[308];      
}TDS_TRACE_AFC_MID_FIR_STRU;

typedef struct
{
    INT16 asCpFreqList[50];      
}TDS_TRACE_AFC_CP_FREQ_LIST_STRU;

typedef struct
{
    INT16 asMdFreqList[50];      
}TDS_TRACE_AFC_MD_FREQ_LIST_STRU;

/************************************************************
                           4. Debug数据结构定义
************************************************************/
typedef enum
{
    TDS_DEBUG_AFC_FRQ_TR_PERIOD        = OM_TCMD_ID(TPHY_AFC_MID, OM_TYPE_DEBUG, 0x1),
    TDS_DEBUG_AFC_FRQ_CTH_PERIOD,
    TDS_DEBUG_AFC_PRE_LOCK_IND_JUDGE,
    TDS_DEBUG_AFC_LAST_LOCK_IND_JUDGE
}TDS_DEBUG_AFC_ENUM;


/*AFC频率跟踪周期内输出结果*/
typedef struct
{
    INT16  asOmJDRxData[88];        //联合检测JD软值符号数组
    UINT16 usSINRThresh0;           //低信噪比保护门限0；
    INT16  sFrqTrRShift;            //频率跟踪复乘结果右移量，默认为2;
    UINT16 usFrqTrConvFactor;       //频率跟踪频偏折算因子；
}TDS_DEBUG_AFC_FRQ_TR_PERIOD_STRU;

/*AFC精频偏捕获周期内输出结果*/
typedef struct
{
    INT32  alExtendMidamble[154];   //信道估计时域信号
    INT32  alChEstMidamble[128];    //信道估计输出结果
    INT16  asPluralMidSeqIQ[288];
    INT16  asUserList[8];           //激活用户集合
    INT16  sMultiPathNum;           //多径数量
    UINT16 usMainPathDelay;         //主径偏移；
    UINT16 usFrqCthConvFactor;      //精频偏捕获频偏折算因子；
    UINT16 usMultPathCompensate;    //多径补偿量；
    UINT16 usFOLimit;               //频偏估计限幅值；
}TDS_DEBUG_AFC_FRQ_CTH_PERIOD_STRU;

/*AFC未判决前锁定失锁指示模块OM上报*/
typedef struct
{
    INT16  asFreqTrResList[127];    //频率跟踪鉴频结果表
    INT16  asFreqCthResList[127];   //精频偏捕获鉴频结果表
    INT16  sFrqTrSlipWinCnt;        //频率跟踪滑窗计数
    INT16  sFrqCthSlipWinCnt;      //精频偏捕获滑窗计数
//    UINT16 usReserved;
}TDS_DEBUG_AFC_PRE_LOCK_IND_JUDGE_STRU;

/*AFC判决后锁定失锁指示模块OM上报*/
typedef struct
{
    INT16  asFreqTrResList[127];    //频率跟踪鉴频结果表
    INT16  asFreqCthResList[127];   //精频偏捕获鉴频结果表
    INT16  sFrqTrSlipWinCnt;        //频率跟踪滑窗计数
    INT16  sFrqCthSlipWinCnt;      //精频偏捕获滑窗计数
//    UINT16 usReserved;
}TDS_DEBUG_AFC_LAST_LOCK_IND_JUDGE_STRU;

//高铁场景添加
typedef struct
{
    UINT16 usSfn;
    UINT16 usTempStudyFlag;
    UINT16 usHighSpeedFlag;
    UINT16 usResv;
    TDS_HIGH_SPEED_NV_PARA stNvPara;
} TDS_AFC_OM_HIGH_SPEED_PARA_STRU;



/*AFC om上报结构体*/
extern TDS_TRACE_AFC_FRQ_TR_PERIOD_STRU       gstTraceAFCFrqTr;
extern TDS_TRACE_AFC_FRQ_CTH_PERIOD_STRU      gstTraceAFCFrqCth;
extern TDS_TRACE_AFC_PRE_LOCK_IND_JUDGE_STRU  gstTraceAFCPreLockInd;
extern TDS_TRACE_AFC_LAST_LOCK_IND_JUDGE_STRU gstTraceAFCLastLockInd;
extern TDS_TRACE_AFC_FILTER_MODULE_STRU       gstTraceAFCFilterModule;
extern TDS_TRACE_AFC_RF_ADJUST_STRU           gstTraceAFCRfAdjust;
extern TDS_TRACE_AFC_CP_MODULE_STRU           gstTraceAFCCpModule;
extern TDS_TRACE_AFC_MD_MODULE_STRU           gstTraceAFCMdModule;
extern TDS_REQ_AFC_INTER_LOOP_ENA_STRU        gstReqAfcInterLoopEna;
extern TDS_REQ_AFC_OUT_LOOP_ENA_STRU          gstReqAfcOutLoopEna;

extern void TDS_AFC_OmReq(UINT32 ulMsgId, UINT32 ulSessionId, void* pstMsg, UINT32 ulMsgSize);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __AFC_OM_DEF_H__ */











//
