/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : timing_om_def.h
  版 本 号   : 初稿
  作    者   : tuzhiguo(52067)
  生成日期   : 2010年12月29日
  最近修改   :
  功能描述   : 定义定时模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月29日
    作    者   : tuzhiguo(52067)
    修改内容   : 创建文件
	
  2.日    期   : 2011年05月26日
    作    者   : tuzhiguo(52067)
    修改内容   : 增加trms OM 配置项

  3.日    期   : 2011年10月17日
    作    者   : tuzhiguo
    修改内容   : DTS2011101702963 定时模块优化 修改上报结构体 减少上报使用的代码空间

  4.日    期   : 2011年11月26日
    作    者   : tuzhiguo
    修改内容   : DTS2011111200172 GCF测试修改系统定时缓慢变化
    
  5.日    期   : 2011年11月26日
    作    者   : tuzhiguo
    修改内容   : DTS2011111800531 合入Pliot版本     
  
  6.日    期   : 2011年12月19日
    作    者   : tuzhiguo
    修改内容   : DTS2011121502820 ETU信道的trms档位有小概率(20%)估计不准， 
            估成EVA信道，从而影响性能，算法对此修改一下trms的档位判断
  7.日    期   : 2012年05月15日
    作    者   : baimeng
    修改内容   : DTS2012051005805 算法修改，解决开关机上报TIME ERROR问题
******************************************************************************/

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

#ifndef __TIMING_OM_DEF_H__
#define __TIMING_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_TIMING__
{
    LPHY_REQ_TIMING_ENA_TRU = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_REQ, 0x0),                    /*使能定时跟踪模块*/
    LPHY_REQ_TIMING_PDP_ENA_TRU,
    LPHY_REQ_TIMING_EST_PERIOD,                 /*定时跟踪周期*/
    LPHY_REQ_TIMING_PDP_FILTER,                 /*滤波器使能*/
    LPHY_REQ_TIMING_LOOP_FILTER,                /*环路滤波器打桩*/
    LPHY_REQ_TIMING_CONST_ADVANCE,              /*首次启动定时跟踪相对于小区搜索的提前量*/
    LPHY_REQ_TIMING_PARA,                       /*单播定时跟踪参数*/
    LPHY_REQ_TIMING_TRMS_PARA,                  /*配置TRMS参数默认值*/
    LPHY_REQ_TIMING_TRMS_SAVE,                  /*配置时延的存储值*/
    LPHY_REQ_TIMING_RPT_SG,                     /*上报定时OM结果*/
    LPHY_REQ_TIMING_ENA_MBMS,                   /*使能MBMS定时跟踪*/
    LPHY_REQ_TIMING_MBMS_PARA,                  /*多播定时跟踪参数*/
    LPHY_REQ_TIMING_MBMS_TRMS_PARA,             /*多播定时跟踪时延扩展参数*/
    LPHY_REQ_TIMING_MBMS_LOOP_FILTER,           /*多播环路滤波器打桩*/
    LPHY_REQ_TIMING_MBMS_CONST_ADVANCE,         /*多播相对于单播的提前量*/
    LPHY_REQ_TIMING_MBMS_EST_PERIOD,            /*多播定时跟踪周期*/
    LPHY_REQ_TIMING_MBMS_LONG_PERIOD,           /*多播最大估计周期*/
    LPHY_REQ_TIMING_TRMS_STUB,                  /*单播trms打桩*/
    LPHY_REQ_TIMING_MBMS_TRMS_STUB              /*多播trms打桩*/    
}LPHY_REQ_MSGID_TIMING_ENUM;

typedef struct __LPHY_REQ_TIMING_ENA_TRU_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*0,不使能定时模块; 1,使能定时*/
    UINT16                      usRsv;          /*4字节对齐*/
}LPHY_REQ_TIMING_ENA_TRU_STRU;
typedef struct __LPHY_REQ_TIMING_MBMS_ENABLE_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM   enEna;          /*0,不使能定时模块; 1,使能定时*/
}LPHY_REQ_TIMING_MBMS_ENABLE_STUB_STRU;

typedef struct __LPHY_REQ_TIMING_EST_PERIOD_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*0,不使能定时模块; 1,使能定时*/
    UINT16                      usPeriod;       /*毫秒为单位*/
}LPHY_REQ_TIMING_EST_PERIOD_STRU;

typedef enum __LPHY_REQ_TIMING_PDP_FILTER_E__
{
    TIMING_REQ_PDP_FILTER_TIME,                 /*强迫时域滤波方式*/
    TIMING_REQ_PDP_FILTER_FREQ                  /*强迫频率滤波方式*/
}TIMING_REQ_EST_FILTER_E;
typedef UINT16 TIMING_REQ_EST_FILTER_ENUM_UINT16;

typedef struct __LPHY_REQ_TIMING_PDP_FILTER_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16           enEna;          /*0,不使能定时模块; 1,使能定时*/
    TIMING_REQ_EST_FILTER_ENUM_UINT16   enFilt;         /*1 对定时跟踪使用的滤波器进行打桩:0, 不打桩，1, 频域，2时域*/
}LPHY_REQ_TIMING_PDP_FILTER_STRU;

typedef struct __LPHY_REQ_TIMING_LOOP_FILTER_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*环路滤波系数使能*/
    UINT16                      usRsv;          /*4字节对齐*/
    UINT32                      ulKi;           /*环路滤波系数*/
}LPHY_REQ_TIMING_LOOP_FILTER_STRU;
#if 0
typedef struct __LPHY_REQ_TIMING_ENA_MPS_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*0,不使能多径搜索模块，1，使能多径搜索结果 */
    UINT16                      usRsv;          /*4字节对齐*/
}LPHY_REQ_TIMING_ENA_MPS_STRU;
#endif
typedef struct __LPHY_REQ_TIMING_CONST_ADVANCE_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16    enEna;           /*强制提前值,默认为16*4=64(0.25Ts) */
    INT16                        sAdvance;        /*将初始化搜索的结果强制提前多少个(0.25Ts)*/
}LPHY_REQ_TIMING_CONST_ADVANCE_STRU;

typedef struct __LPHY_REQ_TIMING_TRMS_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16    enEna;           /*1 打开系统定时调整上报使能，0关闭使能 */
    UINT16                       usSrchWinLen[6]; /*搜索窗长*/
    UINT16                       usTrmsParThrd[6];/*搜索峰均比域值*/
    UINT8                        ucAverCoef1[6];  /*{3, 6, 6, 4, 4, 4}平均值门限因子1*/
    UINT8                        ucStartPath[6];  /*用于时延扩展判决的第一条径的径标号索引*/
    UINT8                        ucPowerFactor;   /*功率门限因子*/
    UINT8                        ucAverCoef2;     /*平均值门限因子2*/
    UINT8                        ucAverCoef3;     /*平均值门限因子3*/
    UINT8                        uc1D4MThreshold1;/*TrmsFlag判决门限1*/
    UINT8                        uc1D4MThreshold2;/*TrmsFlag判决门限2*/
    UINT8                        ucDefaultValue;  /*初始化配置值，满足算法可配*/
    UINT8                        ucDefaultValue1; /*第二种情况默认置(未过PAR门限),满足算法可配*/
    UINT8                        ucRsv[3];
}LPHY_REQ_TIMING_TRMS_PARA_STRU;

typedef struct __LPHY_REQ_TIMING_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    INT8         cSysTimieLimit[2][6];
    UINT16                 usWin1a[6];
    UINT16             usWin1bWin2[6];
    UINT16                 usTa[2][6];
    UINT16      usTrefParThreshold[6];
    UINT8    ucDrxPresyncEstPeriod[2];
    UINT8       ucRrcIdleEstPeriod[2];
    UINT8            ucOtherEstPeriod;
    UINT8                       ucRsv;            /*4字节对齐*/
    UINT8                 ucCaTref[6];
}LPHY_REQ_TIMING_PARA_STRU;

typedef struct __LPHY_REQ_TIMING_ENA_MBMS_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16    enEna;           /*1,使能MBMS定时跟踪; 0,不使能定时跟踪*/
    UINT16                      usRsv;            /*4字节对齐*/
}LPHY_REQ_TIMING_ENA_MBMS_STRU;

typedef struct __LPHY_REQ_TIMING_MBMS_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16     enEna;
    UINT16                  usW1aLen[6];
    UINT16                  usW1bLen[6];
    UINT16                  usW2aLen[6];
    UINT16                  usW2bLen[6];
    UINT16                  usFPWLen[6];
    UINT16                      usTa[6];
    UINT16                      usTb[6];
    UINT16                   usT_par[6];
    UINT16       usParThreshold_Tref[6];
    UINT8                    ucTref1[6];
    UINT8                    ucTref2[6];
    UINT8                        ucM[6];
    UINT8               ucSampleR[4][6]; 
    INT16           sResetLowThreshHold;
    INT16          sResetHighThreshHold;
    INT16                          sRsv;
}LPHY_REQ_TIMING_MBMS_PARA_STRU;

typedef struct __LPHY_REQ_TIMING_MBMS_TRMS_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16     enEna;
    UINT16                 usWinLen1[6];
    UINT16                 usWinLen2[6];
    UINT16                 usWinLen3[6];
    UINT16          usM_PAR_Threhold[6];
    UINT16         usM_PAR_Threhold1[6];
    UINT16         usM_PAR_Threhold2[6];
    UINT16         usM_PAR_Threhold3[6];
    UINT16        usM_PAR_Threhold_L[6];
    UINT16           usM_PowerFactor[6];
    UINT16          usM_PowerFactor1[6];
    UINT16          usM_PowerFactor2[6];
    UINT16          usM_PowerFactor3[6];
    UINT16                 usConsti[12];
    UINT16          usStartIndexi[3][6];
    UINT8          ucM_AVG_Threhold1[6];
    UINT8          ucM_AVG_Threhold2[6];
    UINT8          ucM_AVG_Threhold3[6];
    UINT8         ucM_AVG_Threhold_L[6];
    UINT8             ucM_Avg_Factor[6];
    UINT8            ucM_Avg_Factor1[6];
    UINT8            ucM_Avg_Factor2[6];
    UINT8            ucM_Avg_Factor3[6];
    UINT8                        ucM[6];
    UINT8                        ucQ[6];
    UINT8          ucPathPowerThrehold0;
    UINT8          ucPathPowerThrehold1;
    UINT8                       ucCycle;
    UINT8                 ucWin3EffFlag;
    UINT8         ucWinProtectTrmsValue;
    UINT8        ucWin1ProtectTrmsValue;
    UINT8        ucWin2ProtectTrmsValue;
    UINT8        ucWin3ProtectTrmsValue;
    UINT8            ucTrmsReserveValue;
    UINT8               ucTrmsInitValue;
    UINT8             ucTrmsNoPathValue;
    UINT8           ucTrmsNoTimingValue;
    UINT8                      ucRsv[2];
}LPHY_REQ_TIMING_MBMS_TRMS_PARA_STRU;


typedef struct __LPHY_REQ_TIMING_RPT_SG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;          /*1 打开系统定时调整上报使能，0关闭使能 */
    UINT16                      usRsv;          /*4字节对齐*/
}LPHY_REQ_TIMING_RPT_SG_STRU;

typedef struct __LPHY_REQ_TIMING_TRMS_SAVE_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT8       ucNum;
    UINT8       ucNum2Value;
}LPHY_REQ_TIMING_TRMS_SAVE_STRU;

typedef struct __LPHY_REQ_TIMING_TRMS_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT8       ucTrms;
    UINT8       ucRsv;
}LPHY_REQ_TIMING_TRMS_STUB_STRU;

typedef struct __LPHY_REQ_TIMING_MBMS_TRMS_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT8       ucTrms;
    UINT8       ucRsv;
}LPHY_REQ_TIMING_MBMS_TRMS_STUB_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_TIMING__
{
    LPHY_CNF_TIMING_RESERVED            = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_TIMING_ENUM;


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_MSGID_TIMING__
{
    LPHY_IND_TIMING_RESERVED            = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_TIMING_ENUM;

/************************************************************
                           4. SG 数据结构定义, 算法需要绘图的
************************************************************/
typedef enum __LPHY_SG_MSGID_TIMING__
{
    LPHY_SG_TIMING_RPT            = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_SG, 0x0),/*上报定时所有的SG信息*/
    LPHY_SG_PDP_RPT_PCC,
    LPHY_SG_PDP_RPT_SCC,
    LPHY_SG_PDP_RPT_MBMS,
}LPHY_SG_MSGID_TIMING_ENUM;
typedef struct __TIMING_PDP_STRU__
{
    UINT32    aulPdp[512];
}TIMING_PDP_STRU;
typedef struct __TIMING_COUNTER_INFO_STRU__
{
    UINT32 ulAfn;           /*绝对帧号*/
    UINT32 ulAbs;           /*绝对时标*/
    UINT32 ulSfn;           /*系统帧号*/
    UINT32 ulSysTime;       /*系统定时当前计数值*/    
}TIMING_COUNTER_INFO_STRU;

/* 定时切换类型 */
typedef enum TIMING_SWITCH_TYPE
{
    TIMING_SWITCH_NONE                = 0,
    TIMING_SWITCH_REQ,
    TIMING_SWITCHBACK_REQ
} TIMING_SWITCH_TYPE_ENUM;
typedef UINT16 TIMING_SWITCH_TYPE_ENUM_UINT16;

/*记录定时启动命令状态*/
typedef enum __TIMING_CMD_STATE_ENUM__
{
    TIMING_CMD_STATE_STOP = 0,
    TIMING_CMD_STATE_START,
    TIMING_CMD_STATE_BUTT
}TIMING_CMD_STATE_ENUM;
typedef UINT16 TIMING_CMD_STATE_ENUM_UINT16;

/*记录定时运行状态*/
typedef enum __TIMING_SDR_STATE_ENUM__
{
    TIMING_SDR_STATE_STOPPED = 0,
    TIMING_SDR_STATE_RUNNING,
    TIMING_SDR_STATE_BUTT
}TIMING_SDR_STATE_ENUM;
typedef UINT16 TIMING_SDR_STATE_ENUM_UINT16;

typedef enum __TIMING_STATE_ENUM__
{
    TIMING_RUN_STATE = 0,
    TIMING_STOP_STATE,
    TIMING_STATE_BUTT
}TIMING_STATE_ENUM;
typedef UINT16 TIMING_STATE_ENUM_UINT16;

/*解调定时跟踪类型*/
typedef enum __TIMING_EVT_E__
{
    TIMING_EVT_NONE         = 0x0,          /*空事件*/                
    TIMING_EVT_STOP         = (1<<0),       /*前端主动停止定时跟踪，此后处于hold状态*/
    TIMING_EVT_START        = (1<<1),       /*前端启动定时跟踪，恢复定时跟踪*/
    TIMING_EVT_START_RESET  = (1<<2),       /*前端复位后设置初时解调定时位置， 并恢复定时跟踪*/
    TIMING_EVT_SWITCH_RESET = (1<<3),       /*前端切换定时跟踪*/
    TIMING_EVT_SWITCH_BACK  = (1<<4),       /*前端回切定时跟踪*/
    TIMING_EVT_TCS          = (1<<5),       /*周期小区搜索到结果后, 通知定时跟踪进行解调定时跟踪*/
    TIMING_EVT_EST          = (1<<6),       /*周期定时偏差估计引起的解调定时跟踪*/
    TIMING_EVT_MPS          = (1<<7),       /*多径搜索引起的解调定时跟踪*/
    TIMING_EVT_PRESYNC      = (1<<8),       /*预同步引起的系统定时跟踪*/
    TIMING_EVT_MBMS_LONGPERIOD = (1<<9),    /*多播长周期*/
    TIMING_EVT_SWITCH_NORESET   = (1<<10),
    TIMING_EVT_SWITCH_CA_RESET   = (1<<11),
    TIMING_EVT_SWITCH_TRACKING   = (1<<12),
    TIMING_EVT_EST_MBMS    = (1<<13),
    TIMING_EVT_BUTT
}TIMING_EVT_E;
typedef UINT32 TIMING_EVT_ENUM_UINT32;

typedef enum __TIMING_SWITCH_CONFIG_E__
{
	TIMING_TRACKING_MODE = 0,
	TIMING_SWITCH_RESET_MODE,	
	TIMING_SWITCH_NO_RESET_MODE,
}TIMING_SWITCH_CONFIG_ENUM;

typedef  UINT16   TIMING_SWITCH_CONFIG_ENUM_UINT16;
#define TIMING_SWITCH_NO_RESET_MODE_BBP_CONFIG  3

/*1. 定时偏差估计模，包括算法PDP计算(3.3.2节)和定时偏差估计(3.3.3)两部分*/
typedef struct __TIMING_EST_STRU__ /*estimate*/
{
    UINT32                          ulTruNoise;
    UINT32 			                ulTruRsrp;
    UINT16                          usAfcUnLockedFlag;  /*AFC锁定标记*/
    UINT16                          usFirstPathCmpFlag; /*首径搜索比较开关,default 1*/
    
    UINT16                          usFilterInitFlag;   /*滤波器是否初始化*/
    UINT16                          usDurMaxSubFrmNum;  /*一个估计周期总子帧数*/
    
    UINT16                          usDurSubFrmCounter; /*一个估计周期总子帧计数，包含各种帧*/
    UINT16                          usVldMaxSubFrmNum;  /*一个周期内有效估计子帧总数*/
    
    UINT16                          usVldSubFrmCounter; /*一个周期内已经完成的有效估计子帧计数*/
    //UINT16                          usAlphaStateFlag;   //Alpha滤波初始化标志
    //UINT16                          usReserved;
    UINT16                          usSavedFilterPAR;   /*滤波后的峰均比值*/
    
    UINT16                          usSavedOncePAR;     /*单次峰均比值*/
    UINT16                          usLowPARThreshold;  /*低信噪比峰均比值域值*/
    
    UINT16                          usLowPARFlagSuccNum;/*连续低信噪比个数*/
    UINT16                          usLowPARHoldFlag;   /*低信噪比HoldFlag指示*/

    UINT16                          usIsCaclDone;       /*硬件未正常结束*/
    UINT16                          usSubFrmNumOfCaclDone;    /*硬件未正常结束*/
    
    INT16                           sDelta;             /*最近一次的定时偏差估计值,单位:0.5Ts*/
    INT16                           usTrefParThreshold; /*进行提前量折算的PAR域值*/    
    
    TIMING_SDR_STATE_ENUM_UINT16    enState;            /*定时偏差估计状态机*/
    UINT16                          usExcTerminateFlag; /*本次估计结果不可信，目前是因为提前遇到gap*/
    
    INT16                           sTref[2];           /*提前量*/
    
    UINT8                           ucTimeCoef;
    UINT8                           ucFreqCoef;
    UINT8                           ucLeftCoef;
    UINT8                           ucRightCoef;
}TIMING_EST_STRU;

#if 0
/*2. 多经搜索部分，包括算法多经搜索(3.3.4节)及其对应的功能部分*/
typedef struct __TIMING_MPS_STRU__ 
{

    UINT16                          usFilterInitFlag;   /*滤波器是否初始化*/
    INT16                           sSinglePAR;         /*单次峰均比,for om*/
    INT16                           sFilterPAR;         /*滤波后的峰均比, for om*/
    INT16                           usHoldFlag;         /*多径搜索结果, for om*/

    INT16                           sDelta1;            /*最近一次或者前0~5毫秒的定时偏差估计值*/
    INT16                           sDelta0;            /*前6~10毫秒的定时偏差估计值*/

    UINT16                          usCollisionFlag;    /*小区碰撞标记*/
    UINT16                          usLastCalcTiming;   /*前一次计算碰撞的系统帧号*/

    TIMING_SDR_STATE_ENUM_UINT16    enState;            /*多径搜索偏差估计状态机*/

    UINT16                          usThresholdCounter;              /*4字节对齐*/
}TIMING_MPS_STRU;
#endif

/*3. 解调定时跟踪部分，包括算法环路滤波(3.3.5)及其对应的功能部分*/
typedef struct __TIMING_DTT_STRU__
{
    /*外部模块触发的三种事件*/
    TIMING_EVT_ENUM_UINT32          enEvents;           /*输入定时跟踪事件*/
    TIMING_EVT_ENUM_UINT32          enBakEvents;        /*备份输入定时跟踪事件,供调试*/
    UINT32                          ulTcsValue;         /*小区搜索给出的当前小区同步位置: 0.25Ts*/
    INT16                           sEstDelta;          /*保留的定时跟踪偏差, 0.5Ts单位*/
    UINT16                           usReserved;//sMpsDelta;          /*0.5Ts单位*/

    UINT16                          usCurKiIndex;       /*定时偏差当前滤波系数*/
    UINT16                          usNcsCounter;       /*计数器*/
    UINT32                          ulCompItoFlag;
    INT32                           lLastAdjustRemain;  /*上次调整残余量*/
    UINT32                          ulBakDemodTime;     /*备份的解调定时位置*/
    INT32                           lBakTimeAdjust;     /*备份的定时调整量*/
    UINT16                          usBakKiIndex;       /*备份滤波器系数*/
        
    /*输出当前定时跟踪类型，解调定时，调整量*/
    UINT16                          usResetFlag;        /*重置标记*/
    INT32                           lTimeAdjust;        /*定时调整值，0.25TS单位*/
    UINT32                          ulDemodTime;        /*下一子帧解调定时位置*/
    UINT32                          ulPenulDemodTime;     /*倒数第二个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulLastDemodTime;      /*倒数第一个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulCurDemodTime;       /*当前子帧的解调定时, 单位: 0.25TS*/

}TIMING_DTT_STRU;

/*4. 系统定时跟踪部分，包括算法系统定时计算部分(3.3.6节)*/
typedef struct __TIMING_STT_STRU__
{
    /*外部模块触发的事件*/
    TIMING_EVT_ENUM_UINT32          enEvents;           /*输入定时跟踪事件*/
    INT16                           sResetCompDelta;    /*解调定时突变导致系统定时调整量0.25Ts*/
    UINT16                          usDemCounter;       /*解调定时跟踪输出计数*/
    INT32                           lSingleIOAcc;       /*单入单出累加器*/
    INT32                           lSysTimeAccValue;   /*系统定时调整累积和值*/
    INT32                           lLastAvgAcc;        /*系统定时累和平均值*/
    INT32                           lLastCompsent;      /*累和平均置减去单入单出累和值剩下的补偿值*/
    INT32                           lLastRemainder;     /*上一次剩下的调整量*/

    INT32                           lAdjustValue;       /*系统定时调整量,0.5TS单位*/
    UINT32                          ulSysTime;          /*系统定时位置*/
}TIMING_STT_STRU;

/*5. 解调定时调整部分，根据解调定时跟踪的结果配置硬件进行定时调整*/
typedef struct __TIMING_DTA_STRU__
{
    /*外部模块触发的事件*/
    TIMING_EVT_ENUM_UINT32          enEvents;                    /*输入定时跟踪事件*/
    TIMING_EVT_ENUM_UINT32          enHwEvents;                  /*备份最近的调整事件*/

    /*原始单播解调定时*/
    UINT32                          ulOrgNormalPenulDemodTime;   /*倒数第二个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulOrgNormalLastDemodTime;    /*倒数第一个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulOrgNormalCurDemodTime;     /*当前子帧的解调定时, 单位: 0.25TS*/
    UINT32                          ulOrgNormalNextDemodTime;    /*下一个子帧的解调定时, 单位: 0.25TS*/

    /*折算后的单播解调定时*/
    UINT32                          ulNormalPenulDemodTime;     /*倒数第二个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulNormalLastDemodTime;      /*倒数第一个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulNormalCurDemodTime;       /*当前子帧的解调定时, 单位: 0.25TS*/
    UINT32                          ulNormalNextDemodTime;      /*下一个子帧的解调定时, 单位: 0.25TS*/

    /*通过原始值算出来的给AFC的调整量*/
    INT32                           lNormalTimeAdjust;        /*单播调整量*/

    /*调整标记*/
    UINT8                           ucErrResetFlag;           /*因解调定时偏差太大导致的重置标记,上报协议栈处理*/
    UINT8                           ucInitResetFlag;          /*初始化重置标记*/
    UINT8                           ucTcsResetFlag;           /*因小区搜索结果和当前解调定时位置偏差太大导致的重置标记*/
    UINT8                           ucReserved;

    UINT8                           ucNormalEstAdjFlag;       /*单播估计调整标记*/
    UINT8                           ucSubRef;                 /*本周期所用定时提前量*/
    UINT16                          usReserved;
    UINT32							pFpu;
    
}TIMING_DTA_STRU;
typedef struct __TIMING_MBMS_DTA_STRU__
{
    TIMING_EVT_ENUM_UINT32          enMbmsEvents;                /*输入定时跟踪事件*/
    TIMING_EVT_ENUM_UINT32          enMbmsHwEvents;              /*备份最近的调整事件*/
    /*原始多播解调定时*/
    UINT32                          ulOrgMbmsPenulDemodTime;     /*倒数第二个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulOrgMbmsLastDemodTime;      /*倒数第一个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulOrgMbmsCurDemodTime;       /*当前子帧的解调定时, 单位: 0.25TS*/
    UINT32                          ulOrgMbmsNextDemodTime;      /*下一个子帧的解调定时, 单位: 0.25TS*/
    /*折算后的多播解调定时*/
    UINT32                          ulMbmsPenulDemodTime;       /*倒数第二个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulMbmsLastDemodTime;        /*倒数第一个子帧的解调定时, 单位: 0.25Ts*/
    UINT32                          ulMbmsCurDemodTime;         /*当前子帧的解调定时, 单位: 0.25TS*/
    UINT32                          ulMbmsNextDemodTime;        /*下一个子帧的解调定时, 单位: 0.25TS*/

    /*通过原始值算出来的给AFC的调整量*/
    INT32                           lMbmsTimeAdjust;          /*多播调整量*/
    INT32                           lAdjustValue;             /*给AFC的调整量*/

    /*调整标记*/
    UINT8                           ucMbmsResetFlag;          /*多播重置标记*/
    UINT8                           ucMbmsEstAdjFlag;         /*多播调整标记*/
    UINT8                           ucMbmsFlag;               /*多播主ID或者非主ID区域*/
    UINT8                           ucSubRef;                 /*本周期所用定时提前量*/
    
}TIMING_MBMS_DTA_STRU;

/*6. 系统定时调整部分，根据系统定时跟踪的结果配置硬件进行定时调整*/
typedef struct __TIMING_STA_STRU__
{
    /*外部模块触发的事件*/
    TIMING_EVT_ENUM_UINT32          enEvents;           /*输入定时跟踪事件*/
    TIMING_EVT_ENUM_UINT32          enHwEvents;         /*备份硬件调整事件*/

    UINT32                          ulLastSysTime;      /*前一子帧的系统定时, 单位: 0.25TS*/
    UINT32                          ulCurSysTime;       /*当前子帧的系统定时, 单位: 0.25TS*/
    UINT32                          ulNextSysTime;      /*下一个子帧的系统定时, 单位: 0.25TS*/

    UINT32                          ulBakSysTime;       /*备份的系统定时, 单位: 0.25TS*/
    /*备份最近一次切系统定时对应的计数寄存器，回切的时候通过这些值来推算回复SFN*/
    TIMING_COUNTER_INFO_STRU        stSysTimCntRegs;    /*记录系统定时相关的计数寄存器*/
    
}TIMING_STA_STRU;


/*7. 定时控制部分，主要记录和控制当前软件的执行状态*/
typedef struct __timing_controller_stru__
{
    TIMING_CMD_STATE_ENUM_UINT16    enCmd;              /*记录控制器接受的命令状态*/
    TIMING_SWITCH_TYPE_ENUM_UINT16  enSwitchType;       /*记录定时切换类型*/
    UINT32                          ulCurSyncPos;       /*当前小区的同步位置: 16Ts*/
    UINT32                          ulBakSyncPos;       /*备份小区的同步位置: 16Ts*/
    UINT16                         usSccTimingStartFlag;
    UINT16                         usMbmsTimingStartFlag;
    //UINT32                          ulBgsAnrSyncPos;    /*背景搜或ANR小区的同步位置: 16Ts*/
    LTE_CELL_INFO_STRU              stCurCellInfo[LPHY_FEATURE_MAX_CARRIER_NUM];      /*当前小区的参数信息*/ 
    LTE_CELL_INFO_STRU              stBakCellInfo;      /*备份小区的参数信息*/
    UINT16                          usPreSyncFlag;
    UINT16                          usReserved;
    //LTE_CELL_INFO_STRU              stBgsAnrCellInfo;   /*背景搜或ANR小区的参数信息*/
}TIMING_CONTROLLER_STRU;


/*8. 时延扩展计算部分，对应算法时延扩展计算(3.3.7节)*/
typedef struct __timing_trms_stru__
{
    UINT16                          usTrms;             /*trms结果*/
    UINT16                          usNoiseFlag1;       /*异常情况*/
    UINT16                          usRawTrmsFlag;      /*字节对齐*/
    UINT8                           ucCurSaveTrmsPos;   /*当前trms位置*/    
    UINT8                           ucVldSaveTrmsNum;   /*保存的有效个数*/    
    UINT8                           ucTrmsSave[32];     /*保存32个历史值*/
    UINT32                          ulSqrPowMulPosAcc;  /*二阶矩*/
    UINT32                          ulValidPowMulPosAcc;/*一阶矩*/
    UINT32                          ulMolecule;         /*分子*/
    UINT32                          ulDenominator0;     /*门限*/
    UINT32                          ulDenominator1;
    UINT32                          ulShiftM;
    UINT32                          ulValidPowMulPosAccInt;
    UINT32                          ulValidPowerAcc;
    UINT32                          ulPowerAve;
    UINT32                          ulPdpMaxPower;
    UINT32                          ulPdpSubMaxPower;
    UINT32                          ulValidPosMax;
    UINT32                          ulPowerTh;
    UINT32                          ulValidPowerAccRest;
    UINT32                          ulValidPowMulPosAccRest;
    UINT32                          ullSqrPowMulPosAccRest;
}TIMING_TRMS_STRU;
#if 0
typedef struct __timing_mbms_trms_stru__
{
    UINT32                          ulStateRegValue;    /*状态寄存器*/ 
    UINT32                          ulResultRegValue;   /*时延扩展寄存器*/
    UINT16                          usSavedFilterPAR[3];/*滤波后的峰均比值*/
    UINT16                          usSavedOncePAR[3];   /*滤波后的峰均比值*/
    UINT32                          ulSaveTrmsAvg[4];   /*三个窗平均功率普内的均值，定时跟踪和时延扩展共用*/

    UINT8                           ucWin1ProtectFlag;  /*窗1保护标记*/
    UINT8                           ucWin2ProtectFlag;  /*窗2保护标记*/
    UINT8                           ucWin3ProtectFlag;  /*窗3保护标记*/
    UINT8                           ucWin3ProtectFlag1; /*窗3保护标记1*/
    UINT8                           ucWin3ProtectFlag2; /*窗3保护标记2*/
    UINT8                           ucWinProtectFlag;   /*总窗保护标记*/
    UINT8                           ucWinTrmsValueL;    /*总窗trms值*/
    UINT8                           ucWin1TrmsValueL;   /*窗1trms值*/
    
    UINT16                          usTrms;             /*trms结果*/
    UINT16                          usRsv;
}TIMING_MBMS_TRMS_STRU;
#endif
typedef struct __TIMING_MBMS_CTRL_STRU__
{
    TIMING_CMD_STATE_ENUM_UINT16    enCmd;              /*MBMS模块的触发命令*/
    TIMING_SDR_STATE_ENUM_UINT16    enState;            /*MBMS定时偏差估计状态机*/
    UINT16                          usAllocType;        /*MBMS中每个周期中的分配广播帧数,1或者4*/
    UINT16                          usAllocPeriod;      /*MBMS的分配周期*/
    UINT16                          usAllocSubFrmNum;   /*MBMS中每个周期中分配的子帧数*/ 
    UINT16                          usRsv;              /*4字节对齐*/
    LTE_CELL_INFO_STRU              stCurCellInfo;      /*MBMS对应的小区参数*/
}TIMING_MBMS_CTRL_STRU;

typedef struct __TIMING_NORMAL_STRU__
{
    TIMING_EST_STRU                 stEst;              /*定时偏差估计*/
    TIMING_DTT_STRU                 stDtt;              /*解调定时跟踪*/
    TIMING_TRMS_STRU                stTrms;             /*时延扩展计算*/
    TIMING_DTA_STRU                 stDta;              /*解调定时调整*/
}TIMING_NORMAL_STRU;

typedef struct __TIMING_MBMS_STRU__
{
    TIMING_EST_STRU                 stEst;              /*多播定时跟踪估计*/
    TIMING_DTT_STRU                 stDtt;              /*多播定时跟踪解调定时计算*/
    TIMING_MBMS_DTA_STRU           stDta;
    //TIMING_MBMS_TRMS_STRU           stTrms;             /*多播时延扩展*/
    TIMING_MBMS_CTRL_STRU           stCtrl;             /*多播定时跟踪控制*/
}TIMING_MBMS_STRU;

typedef struct __TIMING_INFO_STRU__
{
    UINT16                          usFreqId;           /*小区频点*/
    UINT16                          usCellId;           /*小区ID*/
    UINT32                          ulPosOfSubFrmZero;  /*子帧0同步头对应的绝对时标,初始化的同步位置 0.25Ts*/
    UINT16                          usAfnOfSysFrmZero; /*系统帧0,子帧0同步头对应的mfn,单位为帧*/
    UINT16                          usSysFrmNum;        /*维护对应的系统帧号*/
    UINT8                           ucSubFrmNum;        /*维护对应的子帧号*/
    UINT8                           ucSysFrmNumVld;     /*维护的系统帧号是否有效:LPHY_TRUE 表示有效, LPHY_FALSE表示无效*/
    UINT8                           ucSubFrmNumVld;     /*维护的子帧号是否有效:LPHY_TRUE 表示有效, LPHY_FALSE表示无效*/
    UINT8                           ucValid;            /*是否开始启动维护*/
}TIMING_INFO_STRU;


/*9. 定时模块结构定义*/
typedef struct __TIMING_MODULE_STRU__
{
    UINT16                          usSysFrmNum;        /*上报时候的系统帧号*/
    UINT16                          usSubFrmNum;        /*上报时刻的子帧号*/
	TIMING_STATE_ENUM_UINT16        aenTimingState[LPHY_FEATURE_MAX_CARRIER_NUM];
	TIMING_STATE_ENUM_UINT16        enTimingMbmsState;
    LTE_DRX_TIMING_STATE_ENUM_UINT16    enPreSyncFlag;
	#if (defined (LPHY_FEATURE_ONE_XO))
	UINT16                          usReserved;
	#endif
    TIMING_NORMAL_STRU              stNormal[LPHY_FEATURE_MAX_CARRIER_NUM];           /*单播定时跟踪控制*/
    TIMING_CONTROLLER_STRU          stCtrl;             /*定时控制*/
    TIMING_MBMS_STRU                stMbms;             /*MBMS的定时跟踪控制*/
    TIMING_STT_STRU                 stStt;              /*系统定时跟踪*/
    //TIMING_DTA_STRU                 stDta;              /*解调定时调整*/
    TIMING_STA_STRU                 stSta;              /*系统定时调整*/
    TIMING_INFO_STRU                stMaintainedInfo[3];/*位ANR增加的维护定时小区*/
}TIMING_MODULE_STRU;


/************************************************************
                           5. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_TIMING_ENUM__
{
    LPHY_TRACE_TIMING_RESERVED              = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_TIMING_TRACE_BINARY          = OM_CMD_ID(LPHY_TIMING_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_TIMING_TRACE
}LPHY_TRACE_TIMING_ENUM;

typedef enum __LPHY_TRACE_TIMING_TRACE_STAT_ENUM__
{
    LPHY_TRACE_TIMING_TRACE_START_TRACK,
    LPHY_TRACE_TIMING_TRACE_STOP_TRACK,
    LPHY_TRACE_TIMING_TRACE_SWITCH
}LPHY_TRACE_TIMING_TRACE_ENUM_UINT16;

typedef struct __LPHY_TRACE_TIMING_TRACE_STRU__
{
    LPHY_TRACE_TIMING_TRACE_ENUM_UINT16  enStat;
}LPHY_TRACE_TIMING_TRACE_STRU;


typedef struct __TIMING_MBMS_PDP_STRU__
{
    UINT32    aulPdpMbms[1024];
}TIMING_MBMS_PDP_STRU;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TIMING_OM_DEF_H__ */
