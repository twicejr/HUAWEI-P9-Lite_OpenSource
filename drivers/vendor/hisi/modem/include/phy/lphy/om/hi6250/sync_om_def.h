/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : sync_om_def.h
  版 本 号   : 初稿
  作    者   : tuzhiguo(52067)
  生成日期   : 2010年12月29日
  最近修改   :
  功能描述   : 定义同步模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月29日
    作    者   : tuzhiguo(52067)
    修改内容   : 创建文件

  2.日    期   : 2011年05月26日
    作    者   : tuzhiguo(52067)
    修改内容   : CQI新特性修改合入

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

#ifndef __SYNC_OM_DEF_H__
#define __SYNC_OM_DEF_H__


/* #ifdef __cplusplus */
/* #if __cplusplus */
/* extern "C"{ */
/* #endif */
/* #endif /\* __cplusplus *\/ */

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_SYNC__
{
    LPHY_REQ_SYNC_RESERVED            = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_REQ, 0x0),//0x30600000
    LPHY_REQ_SYNC_ENA,
    LPHY_REQ_SYNC_RBIR_ALPHA,                //RLM计算时的RBIR滤波因子
    LPHY_REQ_SYNC_THRESH_INSYNC,             //RLM的同步门限
    LPHY_REQ_SYNC_THRESH_OUTSYNC,            //RLM的失步门限
    LPHY_REQ_SYNC_STAT
}LPHY_REQ_MSGID_SYNC_ENUM;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	UINT8						aucRsv1[2];
}LPHY_REQ_SYNC_EN_STRU;

typedef struct 
{
    LPHY_REQ_SYNC_EN_STRU stInputSw;
    LPHY_REQ_SYNC_EN_STRU stCalSw;

    LPHY_REQ_SYNC_EN_STRU stBbpResultSw;
    LPHY_REQ_SYNC_EN_STRU stPHSw;

    LPHY_REQ_SYNC_EN_STRU stRsv1;
    LPHY_REQ_SYNC_EN_STRU stRsv;
}LPHY_REQ_SYNC_REPORT_SWITCH_STRU;
    
    
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
   UINT16                      usAlpha;
}LPHY_REQ_SYNC_RBIR_ALPHA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    INT16                      sThresh;
}LPHY_REQ_SYNC_THRESH_STRU;


typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usRuuMode;            /*0, 1, 2*/
}LPHY_REQ_SYNC_RUU_MODE_STRU;


/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_SYNC__
{
    LPHY_CNF_SYNC_RESERVED            = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_SYNC_ENUM;

/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_MSGID_SYNC__
{
    LPHY_IND_SYNC_RESERVED            = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_SYNC_ENUM;


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_SYNC_
{
    LPHY_TRACE_SYNC_RESERVED         = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_SYNC_TRACE_BINARY,  
    LPHY_TRACE_SYNC_TRACE,  
}LPHY_TRACE_SYNC_ENUM;

typedef enum __LPHY_TRACE_SYNC_STAT__
{
    LPHY_TRACE_SYNC_STAT_NEW_CFG_PARA = 1,   /*收到CONFIG消息*/
    LPHY_TRACE_SYNC_STAT_INVALID_CFG_PARA,   /*收到CONFIG消息不合法*/
    LPHY_TRACE_SYNC_STAT_GET_CNF_BUF_FAIL,       /*收到CONFIG消息回复确认消息无缓冲区*/
}LPHY_TRACE_SYNC_STAT_ENUM;
typedef UINT16 LPHY_TRACE_SYNC_STAT_ENUM_UINT16;

typedef struct __LPHY_TRACE_SYNC_STRU__
{
    LPHY_TRACE_SYNC_STAT_ENUM_UINT16  enTraceStat;    
}LPHY_TRACE_SYNC_STRU;


/************************************************************
                           5. SG数据结构定义
************************************************************/
typedef enum __LPHY_SG_SYNC_
{
    LPHY_SG_SYNC_RESERVED         = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_SG, 0x0),//0x30630000
    LPHY_SG_PCELL_SYNC_STAT,
    LPHY_PCELL_INPUT_STAT,
    LPHY_PCELL_CAL_STAT,
    LPHY_PCELL_BBP_RESULT_STAT,
    LPHY_TEXT_RESULT_STAT,
}LPHY_SG_SYNC_ENUM;

typedef struct __LPHY_SG_SYNC_SNR_STRU__
{
    INT16       sOSSINR;
    INT16       sISSINR;
}LPHY_SG_SYNC_SNR_STRU;

typedef struct __LPHY_SG_SYNC_RESULT_STRU__
{
	UINT8      ucRsv[2];
    UINT8      ucOSFlag;   
    UINT8      ucISFlag;   
}LPHY_SG_SYNC_RESULT_STRU;

typedef struct __LPHY_SG_SYNC_OM_STAT_STRU__
{
    UINT8       ucOSFlag;
    UINT8       ucISFlag;
    UINT8       ucTrmsInd;
    UINT8       ucUnevenFlagFinal;
    
    INT16       sISSINR;
    INT16       sOSSINR;

    INT16       sIThrd;  
    INT16       sOThrd;  

    UINT16      usAlphaRlm;  
    UINT8       ucCdrx;  
    UINT8       ucRsv;
    
    INT16       sAvSinDb;  
    INT16       sISMinSINR;  

	INT32       sOSSINRSum;
	INT32       sISSINRSum;

	INT32       sCnt;
}LPHY_SG_SYNC_OM_STAT_STRU;
    

typedef struct
{
    UINT16 usSysFrmNum;
    UINT16 usSubFrmNum;
    
    UINT16 usNoiseMulFactor;
    UINT8  ucTrmsInd;
    UINT8  ucDftCheFlag;
    
    UINT16 usFrameType;
    UINT8  ucHetnet;
    UINT8  ucRsv;
    
    INT16 asSinrDB[4];

    UINT32 aulNoiseCmu[4];
    
    UINT32 ulRsv[4];
    
}LPHY_SYNC_INPUT_REPORT_STRU;
    
typedef struct 
{
    UINT32 ulWhiteSel;
    
    UINT16 usBeta;
    UINT16 usGamma;
    
    UINT32 ulRsv;
    UINT32 ulRsv1;
    UINT32 ulRsv2;
    UINT32 ulRsv3;
}LPHY_SYNC_CAL_REPORT_STRU;
typedef struct 
{

    UINT32 ulBaseRbir;
    UINT32 ulDrxRbir;
    UINT32 ulAccRbir;
    UINT32 ulAccCnt;
    

    UINT8 ucCdrx;
    UINT8 ucRsv;
    UINT8 ucRsv1;
    UINT8 ucRsv2;
    
    INT16 sRsv;
    UINT16 usAlpha;
    

    UINT32 ulRsv;
}LPHY_SYNC_BBPRESULT_REPORT_STRU;

typedef struct 
{
    UINT32 ulSysNum;
    UINT32 ulSubNum;
    UINT32 aulContent[128];

}LPHY_SYNC_TEXT_REPORT_STRU;

    

/*
    同失步结构体定义，方便调试根据开关全部上报
*/
typedef enum __SYNC_TYPE_E__
{
    SYNC_TYPE_NONE,
    SYNC_TYPE_FILTER,
    SYNC_TYPE_REPORT    
}SYNC_TYPE_E;
typedef UINT16 SYNC_TYPE_ENUM_UINT16;

typedef struct __SYNC_MODULE_STRU__
{
    /*原语下发同失步使能*/
    UINT8           ucInSyncReportEn;       /*同步上报使能*/
    UINT8           ucOutofSyncReportEn;    /*失步上报使能*/

    /*同失步控制*/
    UINT8           ucInitFliterAlhpaFlag;  /*初始化滤波器alpha系数标记*/
    UINT8           ucJudge2InitAlphaFlag;  /*判决方式alpha初始化标记*/
    UINT16          usCounter;              /*经历的时间计数，单位毫秒*/
    SYNC_TYPE_ENUM_UINT16     enType;       /*启动同失步计算后，设置该标记，同失步判决后清除该标记*/
    UINT16          usInSyncAlpha;
    UINT16          usOutSyncAlpha;
    
    /*同失步判决*/
    UINT16          usOSRptFlag;            /*失步结果上报标记 1，表示失步; 0, 表示未失步*/
    UINT16          usISRptFlag;            /*同步结果上报标记 1，表示同步; 0, 表示未同步*/
    INT32           lSINR;                  /*判决方式2滤波值*/
    UINT16          usJudge2OSFlag;         /*判决方式2失步标记*/

    /*记录同失步的异常分支*/
    UINT8           ucStartDgbBranch1;      /*记录当前子帧的异常分支，方便调试*/
    UINT8           ucCompleteDbgBranch2;   /*记录当前子帧的结束分支, 方便调试*/  

    /*记录OM上报每个子帧的信噪比*/
    LPHY_SG_SYNC_SNR_STRU   stSNR;          /*信噪比，每启动计算一次读一次*/
    
    /*OM上报部分*/
    UINT32          ulAccTimeCounter;       /*累加经历的时间计数，单位毫秒*/
    INT32           lAccNum;                /*累加次数*/
    INT32           lOSSNRSum;              /*失步信噪比累加值*/
    INT16           sMaxOSSINR;             /*最大失步值*/
    INT16           sMinOSSINR;             /*最小失步值*/
    INT32           lISSNRSum;              /*同步信噪比累加值*/
    INT16           sMaxISSINR;             /*最大同步值*/
    INT16           sMinISSINR;             /*最小同步值*/

    /*新增OM*/
    INT16           sOrgCmuSINR;            /*从CMU获取的SINR*/
    INT16           sOrgCqiSINR;            /*CMU给CQI后，CQI再给RLM的SINR, RLM用该值做滤波*/
    INT16           usValidSINR;            /*看是否有效的表示SINR*/
    INT16           usRsv;
    
}SYNC_MODULE_STRU;


/* #ifdef __cplusplus */
/* #if __cplusplus */
/* } */
/* #endif */
/* #endif /\* __cplusplus *\/ */


#endif /* __SYNC_OM_DEF_H__ */
