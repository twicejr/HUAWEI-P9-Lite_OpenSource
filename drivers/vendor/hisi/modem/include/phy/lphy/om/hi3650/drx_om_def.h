/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drx_om_def.h
  版 本 号   : 初稿
  作    者   : zhangning(49144)
  生成日期   : 2011年11月1日
  最近修改   :
  功能描述   : 定义DRX OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2011年11月1日
    作    者   : zhangning(49144)
    修改内容   : 创建文件
--------------------------------------------------------------------------------
  2.日    期   : 2012年07月12日
     作    者   : zhangning
     修改内容   : DTS2012071204333 增加死机定位信息，修改符号中断打开位置
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

#ifndef __DRX_OM_DEF_H__
#define __DRX_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



typedef enum
{
     LPHY_DEBUG_DRX        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_DEBUG, 0x1),

}LPHY_DEBUG_DRX_ENUM;

typedef enum
{
     LPHY_ERR_DRX        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_ERROR, 0x1),

}LPHY_ERR_DRX_ENUM;



typedef struct
{
    UINT32 ulAllResetCnt;
    UINT32 ulInitPowUpCnt;
    UINT32 ulLpcResetCnt;
    UINT32 ulTaskLoopCnt[16];
    UINT32 ulWakeResumeFunc;
    //UINT32 ulWakeTimer;
    //UINT32 ulSlwwpTimer;
    //UINT32 ulMeasResult;

    UINT32 ulTaskInfo;
    UINT32 ulDrxCurStatus;
    UINT32 epc[4];
    UINT32 eps[4];
	UINT32 ulExcLoc;
	UINT16 usExcID;
    UINT16 usSysFrame;
    UINT16 usSubFrame;
    UINT16 usMeasCalcCnt;
    UINT16 usWakeCnt;
    UINT16 usSleepCnt;
    UINT16 usCdrxSleepCnt;
    UINT16 usCdrxWakeCnt;
    //UINT16 usWakeValid;
    UINT16 usSlaveWakeUpCnt;
    UINT16 usSlaveSleepCnt;
    UINT16 usCdrxOnlyRfSleepCnt;
    UINT16 usCdrxOnlyRfWakeCnt;
    UINT16 usRsvd[6];
}DRX_DEBUG_STRU;

typedef enum
{
    LPHY_REQ_DRX_PRINT_INFO            =  OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_REQ, 0x0),
    LPHY_DT_DRX_STATUS_INFO_REQ        =  OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_REQ, 0x100),
    LPHY_DT_DRX_STATUS_INFO_REQ_DT,

}LPHY_DT_DRX_REQ_ENUM;

typedef enum
{
     LPHY_DT_DRX_STATUS_INFO_IND        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_SG, 0x1),
    LPHY_DT_DRX_STATUS_INFO_IND_DT                = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_DT, 0x1),

    LPHY_LPC_DVFS_STATUS_INFO_IND                 = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x1),
    LPHY_LPC_DVFS_VOLTA_REQ_INFO_IND              = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x2),
    LPHY_LPC_NOTSLEEP_INFO_IND                    = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x3),
    LPHY_LPC_DSDS_RF_ON_INFO_IND                  = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x4),
    LPHY_LPC_DSDS_RF_OFF_INFO_IND                 = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x5),
    LPHY_LPC_PRESYNC_START_INFO_IND               = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x6),
    LPHY_LPC_PRESYNC_END_INFO_IND                 = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x7),
    LPHY_LPC_TASK_LOG_INFO_IND                    = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x8),
    LPHY_LPC_WAKE_INFO_IND                        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x9),
    LPHY_LPC_ULRF_PAON_INFO_IND                   = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0xa),
    LPHY_LPC_ULRF_PAOFF_INFO_IND                  = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0xb),

    LPHY_LPC_CDRX_STATUS_START_INFO_IND           = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x10),/*Begin,禁止在End前插入新的定义*/
    LPHY_LPC_CDRX_INACTIVE_START_INFO_IND         = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x10),        //当前子帧开始active
    LPHY_LPC_CDRX_ACTIVE_START_INFO_IND           = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x11),/*End,禁止在Begin后插入新的定义*/

    LPHY_LPC_DLRF_IDLE_STATUS_INFO_IND            = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x20), /*Begin,禁止在End前插入新的定义*/
    LPHY_LPC_PCELL_DLRF_IDLE_START_INFO_IND       = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x20),         //PCELL下一子帧开始RF_IDLE
    LPHY_LPC_SCELL_DLRF_IDLE_START_INFO_IND       = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x21),
    LPHY_LPC_SCELL2_DLRF_IDLE_START_INFO_IND      = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x22),
    LPHY_LPC_SCELL3_DLRF_IDLE_START_INFO_IND      = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x23),
    LPHY_LPC_DLRF_ON_STATUS_INFO_IND              = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x24),
    LPHY_LPC_PCELL_DLRF_ON_START_INFO_IND         = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x24),         //PCELL下一子帧开始RF_ON
    LPHY_LPC_SCELL_DLRF_ON_START_INFO_IND         = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x25),
    LPHY_LPC_SCELL2_DLRF_ON_START_INFO_IND        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x26),
    LPHY_LPC_SCELL3_DLRF_ON_START_INFO_IND        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x27)  /*End,禁止在Begin后插入新的定义*/


}LPHY_DT_DRX_IND_ENUM;
typedef UINT32 LPHY_DT_DRX_IND_ENUM_UINT32;

typedef enum
{
    DRX_TIMER_INACTIVE = 0,
    DRX_TIMER_ACTIVE
}DRX_TIMER_STATUS_ENUM;

typedef UINT16 DRX_TIMER_STATUS_ENUM_UINT16;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    OM_REQ_ENABLE_ENUM_UINT16   enLpcReport;
} LPHY_DT_DRX_STATUS_INFO_REQ_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enHighPrintEn;
    OM_REQ_ENABLE_ENUM_UINT16   enLowPrintEn;
    OM_REQ_ENABLE_ENUM_UINT16   enMidPrintEn;
    UINT16                      usRsv;
} LPHY_REQ_DRX_PRINT_INFO_REQ_STRU;


typedef struct
{
    DRX_TIMER_STATUS_ENUM_UINT16  aenDlRttTimer[15];
    DRX_TIMER_STATUS_ENUM_UINT16  aenDlRetranTimer[15];
} DRX_DL_HARQ_TIMER_INFO_STRU;

typedef struct __LPHY_DT_DRX_STATUS_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
    UINT16  usDrxCycleType;
    UINT16  usActiveState;
    DRX_TIMER_STATUS_ENUM_UINT16  enOndurationTimerState;
    DRX_TIMER_STATUS_ENUM_UINT16  enInactivityTimer;
    DRX_TIMER_STATUS_ENUM_UINT16  enShortTimer;
    UINT16                        usRsv;
    DRX_DL_HARQ_TIMER_INFO_STRU   astDlHarqTimer[4];

} LPHY_DT_DRX_STATUS_INFO_IND_STRU;

typedef struct __LPHY_DT_DRX_STATUS_INFO_IND_STRU_DT__
{
    UINT16  usSFN;
    UINT16  usSubFn;

    UINT16  usDrxCycleType;
    DRX_TIMER_STATUS_ENUM_UINT16  enOndurationTimerState;

    DRX_TIMER_STATUS_ENUM_UINT16  enInactivityTimer;
    UINT16                        usRsv;


} LPHY_DT_DRX_STATUS_INFO_IND_STRU_DT;

typedef struct __LPHY_LPC_DVFS_VOLTA_REQ_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //申请时的系统帧号
    UINT16 usSubFn;                   //申请时的系统帧号
    UINT16 usReqCnt;                  //累计申请次数
    UINT8  ucBbpVoltaReq;             //申请BBP电压状态，0为低压，1为高压
    UINT8  ucDspVoltaReq;             //申请BBE16电压状态，0为低压，1为高压
}LPHY_LPC_DVFS_VOLTA_REQ_INFO_IND_STRU;

typedef struct __LPHY_LPC_DVFS_STATUS_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //状态变化时的系统帧号
    UINT16 usSubFn;                   //状态变化时的系统帧号
    UINT8  ucBbpVolta;                //BBP电压状态，0为低压，1为高压
    UINT8  ucDspVolta;                //BBE16电压状态，0为低压，1为高压
    UINT8  ucDspClkStatus;            //BBE16的时钟频率状态,0,低；1,高
    UINT8  ucPdtClkStatus;            //BBP PDT的时钟频率状态,0,低；1,高
    UINT8  ucPdfClkStatus;            //BBP PDF的时钟频率状态,0,低；1,高
    UINT8  ucTdlClkStatus;            //BBP TDL的时钟频率状态,0,低；1,高
    UINT16 usRsv;
    UINT32 ulDspClkSelStatus;         //BBE16的各模块高频申请状态
    UINT32 aulLPdtClkSelStatus;       //PDT的各模块高频申请状态
    UINT32 aulLPdfClkSelStatus;       //PDF的各模块高频申请状态
    UINT32 aulLTdlClkSelStatus;       //PDL的各模块高频申请状态
}LPHY_LPC_DVFS_STATUS_INFO_IND_STRU;

typedef struct __LPHY_LPC_DVFS_INFO_STRU__
{
    LPHY_LPC_DVFS_VOLTA_REQ_INFO_IND_STRU stVoltaReqInfo;   //调压请求状态
    LPHY_LPC_DVFS_STATUS_INFO_IND_STRU    stDvfsStatusInfo; //调频调压变化状态
}LPHY_LPC_DVFS_INFO_STRU;

typedef struct __LPHY_LPC_NOTSLEEP_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //上报时的系统帧号
    UINT16 usSubFn;                   //上报时的系统帧号
    UINT16 usCdrxValid;               //当前状态为CDRX
    UINT16 usIdrxValid;               //当前状态为IDLE
    UINT32 ulNotSleepReason;          //不能进入睡眠的原因
    UINT32 ulCurrentTaskStatus;       //当前任务状态
}LPHY_LPC_NOTSLEEP_INFO_IND_STRU;

typedef struct __LPHY_LPC_PRESYNC_START_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //上报时的系统帧号
    UINT16 usSubFn;                   //上报时的系统帧号
    UINT16 usPresyncDlCnt;            //预同步下行子帧个数
    UINT16 usRsv;                     //保持四字节对齐
}LPHY_LPC_PRESYNC_START_INFO_IND_STRU;

typedef struct __LPHY_LPC_TASK_LOG_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //上报时的系统帧号
    UINT16 usSubFn;                   //上报时的系统帧号
    UINT16 usCdrxValid;               //当前状态为CDRX
    UINT16 usIdrxValid;               //当前状态为IDLE
    UINT16 usTaskId;                  //当前状态为IDLE
    UINT16 usLogStatus;               //0:log out, 1: log in
}LPHY_LPC_TASK_LOG_INFO_IND_STRU;

/*x00312156, DSP Wake信息上报结构体，必须和lpc.h的结构体LPC_DEBUG_CNT_STRU保持一致*/
typedef struct __LPHY_LPC_WAKE_INFO_IND_STRU__
{
    UINT32 ulAllResetCnt;
    UINT32 ulInitPowUpCnt;
    UINT32 ulLpcResetCnt;
    UINT32 ulTaskLoopCnt;
    UINT32 ulLpcSnoozeCnt;
    UINT16 enDspSleepMode;
    UINT16 enLpcIratMode;
    UINT16 enLpcMainState;
    UINT16 enLpcSubState;
    UINT16 usMasterFlag;
    UINT16 usFuncIdxCnt;
    UINT32 ulLastWakeupStartSlice;
    UINT32 ulLastWakeupEndSlice;
    UINT32 ulLastWakeStep;
    UINT32 ulLastWakeStepSlice;
    UINT32 ulLastResumeIpcSlice;
    UINT32 ulLastSleepIpcSlice;
    UINT32 ulSleepIpcCnt;
    UINT32 ulWakeIpcCnt;
    UINT16 enLpcWakeType;
    UINT16 usRsv;
}LPHY_LPC_WAKE_INFO_IND_STRU;  //LPC_DEBUG_CNT_STRU


typedef struct __LPHY_LPC_DRX_OM_TIME_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //上报时的系统帧号
    UINT16 usSubFn;                   //上报时的系统帧号
}LPHY_LPC_DRX_OM_TIME_INFO_IND_STRU;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DRX_OM_DEF_H__ */

