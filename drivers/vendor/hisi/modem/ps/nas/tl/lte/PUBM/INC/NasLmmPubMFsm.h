/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File Name       : NasLmmPubMFsm.h
    Description     : NasLmmPubMFsm.c header file
    History     : hanlufeng 41410 2008-10-11 CREATE FILE
    1.zhengjunyan 00148421  2011-05-28 文件名由 NasMmPubMFsm.h修改为 NasLmmPubMFsm.h
******************************************************************************/

#ifndef __NASLMMPUBMFSM_H__
#define __NASLMMPUBMFSM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPubMIntraMsg.h"
#include    "AppMmInterface.h"
#include    "NasCommBuffer.h"
#include    "MmcLmmInterface.h"
#include    "NasMmlCtx.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_LMM_MAX_STACK_DEPTH          8
#define NAS_LMM_STACK_BASE               0
#define NAS_LMM_QUEUE_CLEAR_POSITION     0
#define NAS_LMM_TIMER_NUM                50                  /* 暂定50个 */

#define NAS_LMM_MOVEMENT_1_BITS          1
#define NAS_LMM_MOVEMENT_2_BITS          2
#define NAS_LMM_MOVEMENT_3_BITS          3
#define NAS_LMM_MOVEMENT_4_BITS          4
#define NAS_LMM_MOVEMENT_8_BITS          8
#define NAS_LMM_MOVEMENT_16_BITS         16
#define NAS_LMM_MOVEMENT_24_BITS         24



#define NAS_LMM_SEA_TABLE_ERR_LOC        0xFFFF

#define NAS_LMM_STACK_EMPTY              0
#define NAS_LMM_MSG_BUF_EMPTY            0

#define NAS_LMM_MSG_BUF_HEAD_INIT        0
#define NAS_LMM_MSG_BUF_TAIL_INIT        0

#define NAS_LMM_INTRA_MSG_HEAD_INIT      0
#define NAS_LMM_INTRA_MSG_TAIL_INIT      0

#define NAS_LMM_VOS_HEADER_LEN           20

#define NAS_LMM_REJ_CAUSE_IS_12          1
#define NAS_LMM_REJ_CAUSE_NOT_12         0

#define NAS_LMM_MMC_SER_REG_STAT_OPEN_FLAG    1
#define NAS_LMM_MMC_SER_REG_STAT_CLOSE_FLAG   0


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/* 获取MM层的上下文的地址 */
#define NAS_LMM_GetMmMainCtxAddr()                   (&g_stMmMainContext)

/* 获取MM层的状态机数组地址 */
#define NAS_LMM_GetMmFsmAddr()                       (&((NAS_LMM_GetMmMainCtxAddr())->stNasMmFsm))

/* 获取某并行状态机当前状态的地址 */
#define NAS_LMM_GetCurFsmAddr(enParalFsmId)          (&((NAS_LMM_GetMmFsmAddr())->astCurFsm[enParalFsmId]))
/*#define NAS_LMM_GetMmcCurFsmAddr()                   (&((NAS_LMM_GetMmFsmAddr())->astCurFsm[NAS_LMM_PARALLEL_FSM_MMC]))*/
#define NAS_LMM_GetEmmCurFsmAddr()                   (&((NAS_LMM_GetMmFsmAddr())->astCurFsm[NAS_LMM_PARALLEL_FSM_EMM]))
#define NAS_LMM_GetSecuFsmAddr()                     (&((NAS_LMM_GetMmFsmAddr())->astCurFsm[NAS_LMM_PARALLEL_FSM_SECU]))

/* 获取某并行状态机当前状态的主状态 */
#define NAS_LMM_GetCurFsmMS(enParalFsmId)            ((NAS_LMM_GetCurFsmAddr(enParalFsmId))->enMainState)
/*#define NAS_LMM_GetMmcCurFsmMS()                     ((NAS_LMM_GetMmcCurFsmAddr())->enMainState)*/
#define NAS_LMM_GetEmmCurFsmMS()                     ((NAS_LMM_GetEmmCurFsmAddr())->enMainState)

/* 当前安全上下文状态*/
#define NAS_LMM_GetSecuCurFsmCS()                    ((NAS_LMM_GetSecuFsmAddr())->enMainState)

/* 获取某并行状态机当前状态的子状态 */
#define NAS_LMM_GetCurFsmSS(enParalFsmId)            ((NAS_LMM_GetCurFsmAddr(enParalFsmId))->enSubState)
#define NAS_LMM_GetMmcCurFsmSS()                     ((NAS_LMM_GetMmcCurFsmAddr())->enSubState)
#define NAS_LMM_GetEmmCurFsmSS()                     ((NAS_LMM_GetEmmCurFsmAddr())->enSubState)

/* 新安全上下文状态*/
#define NAS_LMM_GetSecuCurFsmNS()                    ((NAS_LMM_GetSecuFsmAddr())->enSubState)

/* 设置安全上下文状态*/
#define NAS_LMM_SetSecuCurFsmCS(CurSta)              (((NAS_LMM_GetSecuFsmAddr())->enMainState) = (CurSta))
#define NAS_LMM_SetSecuCurFsmNS(NewSta)              (((NAS_LMM_GetSecuFsmAddr())->enSubState) = (NewSta))


/* 获取某并行状态机当前状态的定时器 */
#define NAS_LMM_GetMmcCurTimer()                     ((NAS_LMM_GetMmcCurFsmAddr())->enStaTId)
#define NAS_LMM_GetEmmCurTimer()                     ((NAS_LMM_GetEmmCurFsmAddr())->enStaTId)


/* 获取某并行状态机的状态机栈的地址 */
#define NAS_LMM_GetFsmStackAddr(enParalFsmId)        (&((NAS_LMM_GetMmFsmAddr())->astFsmStack[enParalFsmId]))
/*#define NAS_LMM_GetMmcFsmStackAddr()                 (&((NAS_LMM_GetMmFsmAddr())->astFsmStack[NAS_LMM_PARALLEL_FSM_MMC]))*/
#define NAS_LMM_GetEmmFsmStackAddr()                 (&((NAS_LMM_GetMmFsmAddr())->astFsmStack[NAS_LMM_PARALLEL_FSM_EMM]))

/* 获取某并行状态机的三个缓存队列的地址 */
#define NAS_LMM_GetFsmBufQueueAddr(enParalFsmId)     (&((NAS_LMM_GetMmFsmAddr())->astFsmMsgBuffer[enParalFsmId]))
/*#define NAS_LMM_GetMmcFsmBufQueueAddr()              (&((NAS_LMM_GetMmFsmAddr())->astFsmMsgBuffer[NAS_LMM_PARALLEL_FSM_MMC]))*/
#define NAS_LMM_GetEmmFsmBufQueueAddr()              (&((NAS_LMM_GetMmFsmAddr())->astFsmMsgBuffer[NAS_LMM_PARALLEL_FSM_EMM]))

/* 获取某并行状态机的缓存队列的高优先级队列中消息的个数的地址 */
#define NAS_LMM_GetFsmBufQueueHighCnt(enParalFsmId)  ((NAS_LMM_GetFsmBufQueueAddr(enParalFsmId))->ucHighPrioCnt)
#define NAS_LMM_GetMmcFsmBufQueueHighCnt()           ((NAS_LMM_GetMmcFsmBufQueueAddr())->ucHighPrioCnt)
#define NAS_LMM_GetEmmFsmBufQueueHighCnt()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->ucHighPrioCnt)
#define NAS_LMM_GetEmmFsmBufQueueMidCnt()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->ucMidPrioCnt)
#define NAS_LMM_GetEmmFsmBufQueueLowCnt()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->ucLowPrioCnt)

/* 获取某并行状态机的缓存队列的高优先级队列的地址 */
#define NAS_LMM_GetFsmBufQueueHighAddr(enParalFsmId) (&((NAS_LMM_GetFsmBufQueueAddr(enParalFsmId))->astHighPrioBuffer))
#define NAS_LMM_GetMmcFsmBufQueueHighAddr()          (&((NAS_LMM_GetMmcFsmBufQueueAddr())->astHighPrioBuffer))
#define NAS_LMM_GetEmmFsmBufQueueHighAddr()          ((NAS_LMM_GetEmmFsmBufQueueAddr())->astHighPrioBufQue)
#define NAS_LMM_GetEmmFsmBufQueueMidAddr()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->astMidPrioBufQue)
#define NAS_LMM_GetEmmFsmBufQueueLowAddr()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->astLowPrioBufQue)


/* 获取MM辅助状态的地址 */
#define NAS_LMM_GetMmAuxFsmAddr()                    (&((NAS_LMM_GetMmMainCtxAddr())->stNasMmAuxFsm))

/* MM辅助状态的RRC链接状态的宏定义 */
#define NAS_EMM_GetConnState()                      (NAS_LMM_GetMmAuxFsmAddr()->ucRrcConnState)
/* 根据转换后的状态进行统计Ser Other Fail计数 */
/* 判断连接状态改变则上报消息*/
#define NAS_EMM_SetConnState(ConnState)    \
            {                              \
                NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SetConnState", ConnState, NAS_EMM_GetConnState()); \
                if(ConnState != NAS_EMM_GetConnState())                                             \
                {                                                                                   \
                    NAS_LMM_SndOmConnstateInfo(ConnState);                                          \
                }                                                                                   \
                NAS_LMM_GetMmAuxFsmAddr()->ucRrcConnState = ConnState;                            \
                NAS_LMM_UpdateSerOtherFailCounter();   \
            }

#define NAS_EMM_UPDATE_STAE                         (NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat)
#define NAS_EMM_GetCurLteState()                    (NAS_LMM_GetMmAuxFsmAddr()->ulCurLteState)
#define NAS_LMM_GetNasAppRegState()                 (NAS_LMM_GetMmAuxFsmAddr()->enNasAppRegState)
#define NAS_LMM_SetNasAppRegState(RegState)         (NAS_LMM_GetMmAuxFsmAddr()->enNasAppRegState = RegState)
/* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */


/* 获取MM层内部消息队列的地址 */
#define NAS_LMM_GetMmIntrMsgQueueAddr()              (&((NAS_LMM_GetMmMainCtxAddr())->stMmIntraMsgQueue))


/* 获取MM层某个状态定时器的地址 */
#define NAS_LMM_GetMmTimerStaCtrlAddrByIdx(ucIdx)    (&((NAS_LMM_GetMmMainCtxAddr())->astMmTimerSta[ucIdx]))
#define NAS_LMM_GetMmTimerPtlCtrlAddrByIdx(ucIdx)    (&((NAS_LMM_GetMmMainCtxAddr())->astMmTimerPtl[ucIdx]))

/* 获取MM层状态定时器数组的地址 */
#define NAS_LMM_GetStateTimerListAddr()              ((NAS_LMM_GetMmMainCtxAddr())->astMmTimerSta)

/* 获取MM层某个状态定时器的地址 */
#define NAS_LMM_GET_STATE_TI_INDEX(usIndex)          ((NAS_LMM_GetStateTimerListAddr())[usIndex])

/* 根据状态定时器ID获取其对应的定时器控制块地址 */
#define NAS_LMM_GetStateTimerAddr(enStateTimerId)    ((enStateTimerId < NAS_LMM_STATE_TI_BUTT)? (&(NAS_LMM_GET_STATE_TI_INDEX(enStateTimerId))) : VOS_NULL_PTR)

/* 获取MM层协议定时器数组的地址 */
#define NAS_LMM_GetPtlTimerListAddr()                ((NAS_LMM_GetMmMainCtxAddr())->astMmTimerPtl)

/* 获取MM层某个协议定时器的地址 */
#define NAS_LMM_GET_PTL_TI_INDEX(usIndex)            ((NAS_LMM_GetPtlTimerListAddr())[usIndex])

/* 根据协议定时器ID获取其对应的定时器控制块地址 */
#define NAS_LMM_GetPtlTimerAddr(enPtlTimerId)        ((enPtlTimerId < NAS_LMM_PTL_TI_BUTT)? (&(NAS_LMM_GET_PTL_TI_INDEX(enPtlTimerId))) : VOS_NULL_PTR)

/* 根据USIM卡中的信息计算出HPLMN搜索周期
    '00':   No higher priority PLMN search attempts;
    '01':   n minutes;
    '02':   2n minutes;
    ...
    'YZ':   (16Y+Z)n minutes (maximum value)

    6:      n minutes
    1 m = 60 s
    1 s = 1000ms
*/
#define NAS_LMM_GET_MS_FROM_USIM(ucNumberOfUnit)     (ucNumberOfUnit * 6 * 60 * 1000)
#define NAS_LMM_CALC_MS_FROM_USIM(ucMinute)           (((ucMinute / 6) / 60) / 1000)

/* 获取EMM的一些信息 */
#define NAS_EMM_CUR_MAIN_STAT                       (NAS_LMM_GetEmmCurFsmMS())
#define NAS_EMM_CUR_SUB_STAT                        (NAS_LMM_GetEmmCurFsmSS())
#define NAS_EMM_CUR_STATE_PROTECT_TIMER             (NAS_LMM_GetEmmCurFsmAddr()->enStaTId)

/* 设置EMM上下文全局变量操作 */
#define NAS_EMM_MAIN_CONTEXT_SET_AUX_UPDATE_STAE(ucEmmUpStat)\
            (NAS_EMM_UPDATE_STAE = ucEmmUpStat)

#define NAS_LMM_ACT_TBL_ITEM(ucSrcPid, ulEventType, pActFun)\
        {\
            (ulEventType),\
            (pActFun)\
        }
/*EMM的普通消息*/
#define NAS_EMM_ACT_TBL_ITEM(ucSrcPid, ulMsgId, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_GET_BT_MD_ET(ulMsgId), pActFun)

/*EMM的CN消息*/
#define NAS_EMM_ACT_CN_TBL_ITEM(ucSrcPid, ulCnMsgType, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_GET_RRC_MM_DATA_IND_CN_ET(ulCnMsgType), pActFun)

/*EMM的定时器消息*/
#define NAS_EMM_ACT_TI_TBL_ITEM(ucSrcPid, ulMsgId, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_TIMER_EXP_MSG_ET(ulMsgId), pActFun)


/*MMC的普通消息*/
#define NAS_EMMC_ACT_TBL_ITEM(ucSrcPid, ulMsgId, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_GET_BT_MD_ET(ulMsgId), pActFun)

/*MMC的CN消息*/
#define NAS_EMMC_ACT_CN_TBL_ITEM(ucSrcPid, ulCnMsgType, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_GET_RRC_MM_DATA_IND_CN_ET(ulCnMsgType), pActFun)

/*MMC的定时器消息*/
#define NAS_EMMC_ACT_TI_TBL_ITEM(ucSrcPid, ulMsgId, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_TIMER_EXP_MSG_ET(ulMsgId), pActFun)



/* 计算组合状态,: 0x主_0x子 */
#define NAS_LMM_PUB_COMP_EMMSTATE(usMainStat, usSubStat)\
        ((((VOS_UINT32)(usMainStat)) << NAS_LMM_MOVEMENT_16_BITS) | (usSubStat))
#define NAS_LMM_PUB_COMP_BEARERSTATE(ucMmlStat, ucESMStat)\
            (((ucMmlStat) << NAS_LMM_MOVEMENT_8_BITS) | (ucESMStat))

#define NAS_LMM_STA_TBL_ITEM(usMainState, usSubState, astActTbl)\
        {\
            NAS_LMM_PUB_COMP_EMMSTATE(usMainState, usSubState),\
            ((sizeof(astActTbl))/sizeof(NAS_LMM_ACT_STRU)),\
            (astActTbl)\
        }
#define NAS_EMMC_STA_TBL_ITEM(usMainState, usSubState, astActTbl) \
        NAS_LMM_STA_TBL_ITEM(usMainState, usSubState, astActTbl)

#define NAS_EMM_STA_TBL_ITEM(usMainState, usSubState, astActTbl) \
            NAS_LMM_STA_TBL_ITEM(usMainState, usSubState, astActTbl)


#define NAS_LMM_TIMER_EXP_EVT_SKELETON   \
            (0x00000000UL | (VOS_PID_TIMER << NAS_LMM_MOVEMENT_16_BITS))

/* TIMER EXP MSG =>  EVENT TYPE * */
#define NAS_LMM_TIMER_EXP_MSG_ET(usNasMmTi)\
            (NAS_LMM_TIMER_EXP_EVT_SKELETON | usNasMmTi)



#define NAS_LMM_GetMsgSenderPid(pMsg)                  (((NAS_LMM_MSG_HEADER_STRU*)pMsg)->ulSenderPid)
#define NAS_LMM_GetMsgLength(pMsg)                     (((NAS_LMM_MSG_HEADER_STRU*)pMsg)->ulLength)
#define NAS_LMM_GetMsgId(pMsg)                         (((NAS_LMM_MSG_HEADER_STRU*)pMsg)->ulMsgId)
/*#define NAS_LMM_GetTimerName(pMsg)                     (((REL_TIMER_MSG *)pMsg)->ulName)*/
#define NAS_LMM_GetTimerName(pMsg)                     NAS_LMM_TIMER_EXP_MSG_ET((((REL_TIMER_MSG *)pMsg)->ulName))




#define NAS_LMM_GetNameFromMsg(ulMsgId, pMsg)\
{\
    if(VOS_PID_TIMER == NAS_LMM_GetMsgSenderPid(pMsg))\
    {\
        ulMsgId = NAS_LMM_GetTimerName(pMsg);\
    }\
    else\
    {\
        ulMsgId = NAS_LMM_GetMsgId(pMsg);\
    }\
}


#define NAS_EMM_CHK_STAT_INVALID(EMM_MS,EMM_SS)\
        (\
            NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS,EMM_SS) != \
            NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT)\
        )

/* 打包APP消息头 */
#define NAS_LMM_COMP_APP_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = PS_PID_APP; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }

/*V7R2-DT ,l00195322,2014/4/30, ST时发给OM，单板运行发给MSP,begin*/
/* 打包APP消息头 */
#if(VOS_WIN32 == VOS_OS_VER)
#define NAS_LMM_COMP_APP_DT_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = PS_PID_APP; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }

#else
#define NAS_LMM_COMP_APP_DT_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = L3_MSP_PID_DT_IND; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }
#endif
/*V7R2-DT ,l00195322,2014/4/30, ST时发给OM，单板运行发给MSP ,end*/
/* 计算MMC要发给XXX的消息长度, 不包含VOS头(外部消息) */
#define NAS_LMM_MSG_LENGTH_NO_HEADER(MM_XXX_MSG_STRU) \
                    (sizeof(MM_XXX_MSG_STRU) - NAS_LMM_VOS_HEADER_LEN)

#define NAS_Emm_Get_Mmc_Srv_Reg_Flag()              g_ulMmcSerRegFlag

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 结构名    : NAS_LMM_PARALLEL_FSM_ENUM_UINT16
 结构说明  : MM层并行状态机标识
*****************************************************************************/
enum NAS_LMM_PARALLEL_FSM_ENUM
{
    NAS_LMM_PARALLEL_FSM_EMM             = 0x0000,
    /*NAS_LMM_PARALLEL_FSM_MMC                     ,*/
    NAS_LMM_PARALLEL_FSM_SECU                    ,
    NAS_LMM_PARALLEL_FSM_BUTT
};
typedef VOS_UINT16 NAS_LMM_PARALLEL_FSM_ENUM_UINT16;


/*****************************************************************************
 枚举名    : NAS_LMM_SERIES_FSM_ID_ENUM
 枚举说明  : MM层各模块并行状态机的串行状态机ID枚举定义,
             UE 1.0 只有EMM模块自己的串行状态机
             UE 1.0 中没有用到此枚举
*****************************************************************************/
enum NAS_LMM_SERIES_FSM_ID_ENUM
{
    NAS_LMM_SERIES_FSM_BEGIN             = 0x0000,

    /* EMM 状态机的各串行FSM ID */
    NAS_LMM_SERIES_FSM_EMM_IDLE                  ,
    NAS_LMM_SERIES_FSM_EMM                       ,

    /* MMC 状态机的各串行FSM ID */


    NAS_LMM_SERIES_FSM_BUTT
};
typedef VOS_UINT16 NAS_LMM_SERIES_FSM_ID_ENUM_UINT16;



/*****************************************************************************
 结构名    : NAS_LMM_MAIN_STATE_ENUM
 结构说明  : MM层所有并行状态机的主状态的枚举定义
*****************************************************************************/
enum    NAS_LMM_MAIN_STATE_ENUM
{
    /*=================== EMM的主状态 ===================*/
    EMM_MS_NULL                         = 0x0000,
    EMM_MS_DEREG                                ,
    EMM_MS_REG_INIT                             ,           /*ATTACH过程中状态*/
    EMM_MS_REG                                  ,
    EMM_MS_TAU_INIT                             ,           /*TAU过程中状态*/
    EMM_MS_SER_INIT                             ,           /*SERVICE过程中状态*/
    EMM_MS_DEREG_INIT                           ,           /*DETACH过程中状态*/

    EMM_MS_AUTH_INIT                            ,           /*AUTH过程*/

    EMM_MS_SUSPEND                              ,           /*挂起过程*/
    EMM_MS_RESUME                               ,           /*解挂过程*/

    /*=================== MMC的主状态 ===================*/
    MMC_MS_NULL                                 ,           /* 复位后的空状态                   */
    MMC_MS_TRYING_PLMN                          ,           /* 复位后或者list无效情况下，搜PLMN和等待注册结果*/
    MMC_MS_TRYING_PLMN_LIST                     ,           /* List有效情况下，搜网和等待注册结果状态        */
    MMC_MS_ON_PLMN                              ,           /* 指定PLMN下注册成功状态           */
    MMC_MS_NOT_ON_PLMN                          ,           /* 等待用户指定PLMN，只用于手动模式 */
    MMC_MS_WAIT_FOR_PLMN                        ,           /* 等待PLMN                         */
    MMC_MS_NO_IMSI                              ,           /* NO SIM状态                       */


    /*=================== SECU 的CUR 状态 ===================*/
    EMM_CUR_SECU_NOT_EXIST,   /*17*/
    EMM_CUR_SECU_EXIST_NOT_ACTIVE, /*18*/
    EMM_CUR_SECU_EXIST_ACTIVE, /*19*/



    NAS_LMM_MAIN_STATE_BUTT
};
typedef VOS_UINT16 NAS_LMM_MAIN_STATE_ENUM_UINT16;
typedef NAS_LMM_MAIN_STATE_ENUM_UINT16   NAS_EMM_MAIN_STATE_ENUM_UINT16;
typedef NAS_LMM_MAIN_STATE_ENUM_UINT16   NAS_EMMC_MAIN_STATE_ENUM_UINT16;


/*****************************************************************************
 结构名    : NAS_LMM_SUB_STATE_ENUM
 结构说明  : MM层所有并行状态机的子状态的枚举定义
*****************************************************************************/
enum    NAS_LMM_SUB_STATE_ENUM
{

    /*=================== EMM的子状态 ===================*/

    /*========== NULL下的子状态 ===============*/
    EMM_SS_NULL_WAIT_APP_START_REQ      = 0x0000,           /*此状态下只处理APP_START_REQ消息*/
    /*EMM_SS_WAIT_NULL_READING_SRV_TABLE          ,*/       /* y00159566 10.5.28 流程清理后删除此状态*/
    EMM_SS_NULL_WAIT_READING_USIM               ,
    /*EMM_SS_NULL_WAITING_USIM_READY              ,*/
    EMM_SS_NULL_WAIT_MMC_START_CNF              ,
    EMM_SS_NULL_WAIT_RRC_START_CNF              ,
    EMM_SS_NULL_WAIT_SWITCH_OFF                 ,
    EMM_SS_NULL_WAIT_MMC_STOP_CNF               ,
    EMM_SS_NULL_WAIT_RRC_STOP_CNF               ,


    /*========== DEREG下的子状态 ==============*/
    EMM_SS_DEREG_NORMAL_SERVICE                 ,   /*0x0009*/
    EMM_SS_DEREG_LIMITED_SERVICE                ,
    EMM_SS_DEREG_ATTEMPTING_TO_ATTACH           ,
    EMM_SS_DEREG_PLMN_SEARCH                    ,
    EMM_SS_DEREG_NO_IMSI                        ,
    EMM_SS_DEREG_ATTACH_NEEDED                  ,
    EMM_SS_DEREG_NO_CELL_AVAILABLE              ,

    /*========== ATTACH_INIT的子状态 ==========*/
    EMM_SS_ATTACH_WAIT_ESM_PDN_RSP              ,  /*0x0011*/
    EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF            ,
    EMM_SS_ATTACH_WAIT_MRRC_REL_CNF             ,
    EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF           ,
    EMM_SS_ATTACH_WAIT_RRC_DATA_CNF             ,


    /*========== REG下的子状态 ================*/
    EMM_SS_REG_NORMAL_SERVICE                   ,   /*0x0017*/
    EMM_SS_REG_ATTEMPTING_TO_UPDATE             ,
    EMM_SS_REG_LIMITED_SERVICE                  ,
    EMM_SS_REG_PLMN_SEARCH                      ,
    EMM_SS_REG_WAIT_ACCESS_GRANT_IND            ,
    EMM_SS_REG_NO_CELL_AVAILABLE                ,
    EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM          ,
    EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF   ,


    /*========== TAU_INIT的子状态  ============*/
    EMM_SS_TAU_WAIT_CN_TAU_CNF                  ,   /*0x0021*/

    /*========== SER_INIT的子状态 =============*/
    EMM_SS_SER_WAIT_CN_SER_CNF                  ,   /*0x0024*/

    /*========== DETACH_INIT的子状态 ==========*/
    EMM_SS_DETACH_WAIT_CN_DETACH_CNF            ,
    EMM_SS_DETACH_WAIT_MRRC_REL_CNF             ,


    /*========== EMM_MS_RRC_CONN_INIT的子状态 =*/
    EMM_SS_RRC_CONN_WAIT_EST_CNF                ,
    EMM_SS_RRC_CONN_WAIT_REL_CNF                ,


    /*========== AUTH过程中的子状态 ===========*/
    EMM_SS_AUTH_WAIT_CN_AUTH,

    /*========== SUSPEND过程中的子状态 ========*/
    EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND,
    EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND,
    EMM_SS_SUSPEND_WAIT_END,
    EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
    EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,

    /*========== RESUME过程中的子状态 ========*/
    EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME,
    EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND,
    EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,

    /*========== GUTI     过程暂无子状态  =====*/
    /*========== IDEN     过程暂无子状态  =====*/
    /*========== SECURITY 过程暂无子状态  =====*/

    /*=================== SECU的NEW状态 ===================*/
    EMM_NEW_SECU_NOT_EXIST,/*56*/
    EMM_NEW_SECU_EXIST,


    MM_SS_BUTT
};
typedef VOS_UINT16  NAS_LMM_SUB_STATE_ENUM_UINT16;
typedef NAS_LMM_SUB_STATE_ENUM_UINT16    NAS_EMM_SUB_STATE_ENUM_UINT16;
typedef NAS_LMM_SUB_STATE_ENUM_UINT16    NAS_EMMC_SUB_STATE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : NAS_LMM_STATE_TI_ENUM
 枚举说明  : MM层所有并行状态机的状态保护定时器定义
             BOUNDARY_START，标识该模块定时器在定时器表中的起始下标;
             BOUNDARY_END，标识该模块定时器在定时器表中的结束下标;
             各个模块的定时器定义需要定义在各自响应的区间中.
*****************************************************************************/
enum NAS_LMM_STATE_TI_ENUM
{
    /*=================== EMM的定时器 ===================*/

    /*========== 保留定时器 ===================*/
    TI_NAS_EMM_STATE_NO_TIMER           = 0x0000,           /* 稳定状态下无定时器 */
    TI_NAS_EMM_STATE_T3440                      ,
    TI_NAS_EMM_STATE_DEL_FORB_TA_PROID          ,            /* 删除禁止的TA */
    /*========== PUB模块定时器 ===================*/
    TI_NAS_LMM_TIMER_WAIT_USIM_CNF               ,
    TI_NAS_LMM_TIMER_WAIT_USIM_READY_START       ,

    /*========== MRRC 模块定时器 ==============*/
    TI_NAS_EMM_STATE_MRRC_BOUNDARY_START        ,           /* MRRC 定时器开始边界 */
    TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF           ,
    TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF            ,

    /*========== ATTACH 模块定时器 ============*/
    TI_NAS_EMM_STATE_REG_BOUNDARY_START         ,           /* REG 定时器开始边界 */
    TI_NAS_EMM_T3410                            ,
   /*TI_NAS_EMM_T3402                          ,*/
    TI_NAS_EMM_WAIT_ESM_PDN_RSP                 ,           /*等待ESM的PDN响应*/
    TI_NAS_EMM_WAIT_ESM_BEARER_CNF              ,           /*等待ESM的承载响应*/
    TI_NAS_EMM_WAIT_RRC_DATA_CNF                ,           /*等待RRC直传消息传输确认*/

    /*========== DETACH 模块定时器 ============*/
    TI_NAS_EMM_STATE_DEREG_BOUNDARY_START       ,           /* DEREG 定时器开始边界 */
    TI_NAS_EMM_T3421                            ,

    /*========== TAU 模块定时器 ===============*/
    TI_NAS_EMM_STATE_TAU_BOUNDARY_START         ,           /* TAU 定时器开始边界 */
    TI_NAS_EMM_STATE_TAU_T3430                  ,

    /*========== SERVICE 模块定时器 ===========*/
    TI_NAS_EMM_STATE_SERVICE_BOUNDARY_START     ,           /* SERVICE 定时器开始边界 */
    TI_NAS_EMM_STATE_SERVICE_T3417              ,
    TI_NAS_EMM_STATE_SERVICE_T3417_EXT          ,
    TI_NAS_EMM_STATE_SERVICE_T3442              ,

    /*========== PLMN 模块定时器 ==============*/
    TI_NAS_EMM_STATE_PLMN_BOUNDARY_START        ,           /* PLMN 定时器开始边界 */
    TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER         ,
    TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER         ,
    TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER          ,
    TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER          ,

    /*========== AUTH 模块定时器 ==============*/
    TI_NAS_EMM_STATE_AUTH_BOUNDARY_START        ,           /* AUTH 定时器开始边界 */
    TI_NAS_EMM_T3418                            ,
    TI_NAS_EMM_T3420                            ,

    /*========== SUSPEND定时器 ================*/
    TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,
    TI_NAS_EMM_WAIT_SUSPEND_END_TIMER           ,
    TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,
    TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,


    /*========== RESEUME定时器 ================*/
    TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER     ,
    TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER         ,
    TI_NAS_EMM_SYSCFGRSM_WAIT_OTHER_RESUME_RSP_TIMER,

    /*========== SYSCFG的定时器 ============================*/
    TI_NAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER,

    TI_NAS_EMM_STATE_TI_BUTT                    ,

    /*========== MMC的定时器 ============================*/
    /*========== PLMN_SRCH的定时器 ============================*/
    TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER,

    TI_NAS_EMMC_STATE_TI_BUTT                    ,

    /*========== END ====================================*/
    NAS_LMM_STATE_TI_BUTT
};
typedef VOS_UINT16 NAS_LMM_STATE_TI_ENUM_UINT16;
typedef NAS_LMM_STATE_TI_ENUM_UINT16     NAS_EMM_STATE_TI_ENUM_UINT16;
typedef NAS_LMM_STATE_TI_ENUM_UINT16     NAS_EMMC_STATE_TI_ENUM_UINT16;


/*****************************************************************************
 枚举名    : NAS_LMM_PTL_TI_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 协议定时器和功能定时器 定义
             BOUNDARY_START，标识该模块定时器在定时器表中的起始下标;
             BOUNDARY_END，标识该模块定时器在定时器表中的结束下标;
             各个模块的定时器定义需要定义在各自响应的区间中.
*****************************************************************************/
enum NAS_LMM_PTL_TI_ENUM
{
    /*=================== EMM的定时器 ===================*/

    /*========== 公共定时器 ===================*/
    TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START = NAS_LMM_STATE_TI_BUTT,


    /*========== ATTACH 模块定时器 ============*/
    /*========== DETACH 模块定时器 ============*/
    /*========== TAU 模块定时器 ===============*/
    TI_NAS_EMM_PTL_T3411                        ,
    TI_NAS_EMM_PTL_T3412                        ,
    TI_NAS_EMM_PTL_T3402                        ,
    TI_NAS_EMM_PTL_T3423                        ,

    /*========== AUTH 模块定时器 ===============*/
    TI_NAS_EMM_PTL_T3416                        ,

    /*========== 关机定时器 ===================*/
    TI_NAS_EMM_PTL_SWITCH_OFF_TIMER             ,

    /*========== attach延时定时器 =============*/
    TI_NAS_EMM_PTL_REATTACH_DELAY               ,

    /*========== CSFB延时定时器 ===============*/
    TI_NAS_EMM_PTL_CSFB_DELAY               ,

    TI_NAS_EMM_PTL_T3346                        ,
    TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER            ,       /* 渐进被禁惩罚定时器 */
    TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER      ,       /* 渐进被禁老化定时器 */
    TI_NAS_EMM_PTL_SER_BACKOFF_TIMER            ,       /*SERVICE失败补偿定时器*/
    TI_NAS_EMM_PTL_TI_BUTT                      ,

    /*========== MMC的定时器 ==================*/
    NAS_LMM_PTL_TI_BUTT
};
typedef VOS_UINT16 NAS_LMM_PTL_TI_ENUM_UINT16;

/*****************************************************************************
 枚举名    : NAS_LMM_TIMER_RUN_STATE_ENUM
 枚举说明  : MM层的状态保护定时器的运行标识
             Timer启动标记(有哪些Timer在运行)
*****************************************************************************/
enum NAS_LMM_TIMER_RUN_STATE_ENUM
{
    NAS_LMM_TIMER_RS_NOT_RUNNING         = 0,                /*NO RUNNING*/
    NAS_LMM_TIMER_RS_RUNNING                ,                /*RUNNING*/

    NAS_LMM_TIMER_RS_BUTT
};
typedef VOS_UINT8 NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_LMM_TIMER_RUN_STATE_ENUM
 枚举说明  : MM层的状态保护定时器的运行标识
             Timer挂起标记(有哪些Timer被挂起)
*****************************************************************************/
enum NAS_LMM_TIMER_SUS_STATE_ENUM
{
    NAS_LMM_TIMER_SS_NOT_SUSPENDING      = 0,                /*NO SUSPEND*/
    NAS_LMM_TIMER_SS_SUSPENDING             ,                /*SUSPEND*/

    NAS_LMM_TIMER_SS_BUTT
};
typedef VOS_UINT8 NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_LMM_TIMER_RUN_STATE_ENUM
 枚举说明  : MM层的状态保护定时器的运行标识
             Timer时长更新标记(有哪些Timer时长被更新)
             当空口消息中更新定时器时长时, NAS_EMM_TIMER_VALUE_STATE_ENUM 被置1,
             定时器启动时判断;
             如被置位，则调用OS API更新时长，并将NAS_EMM_TIMER_VALUE_STATE_ENUM
             清零，然后再启动;
*****************************************************************************/
enum NAS_LMM_TIMER_VALUE_STATE_ENUM
{
    NAS_LMM_TIMER_VS_NOT_NEED_TO_UPDATE  = 0,                /* NO NEED TO UPDATE */
    NAS_LMM_TIMER_VS_NEED_TO_UPDATE         ,                /* NEED TO UPDATE */

    NAS_LMM_TIMER_VS_BUTT
};
typedef VOS_UINT8 NAS_LMM_TIMER_VALUE_STATE_ENUM_UINT8;



enum    NAS_EMM_UPDATE_STATE_ENUM
{
    EMM_US_UPDATED_EU1                  = 0x00,             /* UPDATED */
    EMM_US_NOT_UPDATED_EU2              = 0x01,             /* NOT UPDATED */
    EMM_US_ROAMING_NOT_ALLOWED_EU3      = 0x02,             /* ROAMING NOT ALLOWED */

    EMM_US_BUTT
};
typedef VOS_UINT8  NAS_EMM_UPDATE_STATE_ENUM_UINT8;


enum    NAS_EMM_RRC_CONN_STATE_ENUM
{
    NAS_EMM_CONN_IDLE                   = 0x00,
    NAS_EMM_CONN_ESTING                 = 0x01,
    NAS_EMM_CONN_SIG                    = 0x02,
    NAS_EMM_CONN_DATA                   = 0x03,
    NAS_EMM_CONN_RELEASING              = 0X04,  /* 释放过程中，LMM内部使用的RRC连接状态，对于MMC来说等同IDLE */
    NAS_EMM_CONN_WAIT_SYS_INFO          = 0X05,  /* 表示收到了RRC_IND或者RRC_CNF之后，等待RRC系统消息的过程*/

    NAS_EMM_CONN_BUTT
};
typedef VOS_UINT8  NAS_EMM_RRC_CONN_STATE_ENUM_UINT8;


enum    NAS_EMM_USIM_STATE_ENUM
{
    EMM_USIM_STATE_VALID                = 0x00,
    EMM_USIM_STATE_INVALID              = 0x01,

    EMM_USIM_STATE_BUTT
};
typedef VOS_UINT8  NAS_EMM_USIM_STATE_ENUM_UINT8;


enum NAS_APP_REG_STAT_ENUM
{
    NAS_APP_RS_NOT_REG_AND_NOT_SRCH_OPERATOR    = APP_REG_STAT_NOT_REG_AND_NOT_SRCH_OPERATOR,
    NAS_APP_RS_REG_HPLMN                        = APP_REG_STAT_REG_HPLMN ,
    NAS_APP_RS_NOT_REG_AND_SRCH_OPERATOR        = APP_REG_STAT_NOT_REG_AND_SRCH_OPERATOR,
    NAS_APP_RS_REG_DENIED                       = APP_REG_STAT_REG_DENIED,
    NAS_APP_RS_UNKNOWN                          = APP_REG_STAT_UNKNOWN,
    NAS_APP_RS_REG_ROAMING                      = APP_REG_STAT_REG_ROAMING,
    NAS_APP_RS_BUTT
};
typedef VOS_UINT32  NAS_APP_REG_STAT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_EMM_REG_CHANGE_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LMM上报的register status
*****************************************************************************/
enum NAS_EMM_REG_CHANGE_TYPE_ENUM
{
    NAS_EMM_REG_CHANGE_TYPE_REG_STATE    = 0,
    NAS_EMM_REG_CHANGE_TYPE_LOCATION_INFO,
    NAS_EMM_REG_CHANGE_TYPE_BUTT
};
typedef VOS_UINT32 NAS_EMM_REG_CHANGE_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名称:  NAS_LMM_CUR_LTE_STATE_ENUM_UINT32
 协议表格:  NO CELL状态下，是LTE挂起状态，还是LTE激活时正常的 NO CELL态
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum    NAS_LMM_CUR_LTE_STATE_ENUM
{
    NAS_LMM_CUR_LTE_SUSPEND          = 0x00,
    NAS_LMM_CUR_LTE_ACTIVE           = 0x01,

    NAS_LMM_CUR_LTE_BUTT
};
typedef VOS_UINT32  NAS_LMM_CUR_LTE_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_LMM_TIMER_RUN_STATE_ENUM
 枚举说明  : MM层Timer类型标识
*****************************************************************************/

enum NAS_LMM_TIMER_TYPE_ENUM
{
    NAS_LMM_STATE_TIMER                  ,             /* 状态定时器 */
    NAS_LMM_PTL_TIMER                    ,                   /* 协议定时器 */

    NAS_LMM_TIMER_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LMM_TIMER_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : NAS_LMM_RAT_TYPE_ENUM_UINT8
 结构说明  :
*****************************************************************************/
enum NAS_LMM_RAT_TYPE_ENUM
{
    NAS_LMM_RAT_TYPE_GSM = 0,                           /* GSM接入技术 */
    NAS_LMM_RAT_TYPE_WCDMA,                             /* WCDMA接入技术 */
    NAS_LMM_RAT_TYPE_LTE,                               /* LTE接入技术 */
    NAS_LMM_RAT_TYPE_CDMA1X,                            /* 1x接入技术*/
    NAS_LMM_RAT_TYPE_HRPD,                              /* HRPD接入技术*/
    NAS_LMM_RAT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LMM_RAT_TYPE_ENUM_UINT8;


/*****************************************************************************
 结构名    : NAS_LMM_RAT_PRIO_ENUM_UINT8
 结构说明  :
*****************************************************************************/
enum NAS_LMM_RAT_PRIO_ENUM
{
    NAS_LMM_RAT_PRIO_NULL                = 0,               /* 该接入技术不存在    */
    NAS_LMM_RAT_PRIO_LOW                 = 1,               /* 优先级较低   */
    NAS_LMM_RAT_PRIO_MIDDLE              = 2,               /* 优先级中间   */
    NAS_LMM_RAT_PRIO_HIGH                = 3,               /* 优先级较高   */
    NAS_LMM_RAT_PRIO_BUTT
};
typedef VOS_UINT8  NAS_LMM_RAT_PRIO_ENUM_UINT8;
enum NAS_EMM_BEARER_STATE_ENUM
{
    NAS_EMM_BEARER_STATE_INACTIVE = 0,                                       /* 上下文去激活状态 */
    NAS_EMM_BEARER_STATE_ACTIVE,                                             /* 上下文激活状态 */
    NAS_EMM_BEARER_STATE_BUTT
};
typedef VOS_UINT8 NAS_EMM_BEARER_STATE_ENUM_UINT8;
/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_LMM_BUFF_MSG_STRU
 结构说明  : NAS MM缓存消息队列结构，缓存队列满，则不再装入新消息，
             ulEvtType   : 缓存消息的类型
             pBuffMsg    : 缓存消息的地址
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulEvtType;                             /* 缓存消息对应的事件 PID + MSGTYPE */
    VOS_VOID                            *pBuffMsg;                              /* 缓存消息指针 */
}NAS_LMM_BUFF_MSG_STRU;

/*****************************************************************************
 结构名    : NAS_LMM_FSM_MSG_BUF_STRU
 结构说明  : 管理缓存消息结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHighPrioCnt;      /* 高优先级消息个数 */
    VOS_UINT8                           ucMidPrioCnt;       /* 中优先级消息个数 */
    VOS_UINT8                           ucLowPrioCnt;       /* 低优先级消息个数 */
    VOS_UINT8                           ucRsrv;             /* 字节对齐，保留 */

    NAS_LMM_BUFF_MSG_STRU                astHighPrioBufQue[NAS_EMM_BUF_MSG_MAX_NUM];
    NAS_LMM_BUFF_MSG_STRU                astMidPrioBufQue[NAS_EMM_BUF_MSG_MAX_NUM];
    NAS_LMM_BUFF_MSG_STRU                astLowPrioBufQue[NAS_EMM_BUF_MSG_MAX_NUM];
}NAS_LMM_FSM_MSG_BUF_STRU;


/*****************************************************************************
 结构名    : NAS_EMM_FSM_STATE_STRU
 结构说明  : 状态机状态描述结构
*****************************************************************************/
typedef struct
{
    NAS_LMM_PARALLEL_FSM_ENUM_UINT16     enFsmId;            /* 状态机标识 */
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;        /* 主状态 */
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;         /* 子状态 */
    NAS_LMM_STATE_TI_ENUM_UINT16         enStaTId;           /* 状态定时器ID,保护当前状态的定时器 */

}NAS_LMM_FSM_STATE_STRU;
typedef NAS_LMM_FSM_STATE_STRU           NAS_EMM_FSM_STATE_STRU;
typedef NAS_LMM_FSM_STATE_STRU           NAS_EMMC_FSM_STATE_STRU;

/*****************************************************************************
 结构名    : NAS_EMM_FSM_STATE_STACK_STRU
 结构说明  : 状态机栈描述结构
             其中压入栈的第K个状态，放在 astFsmStack[K-1]的位置；
             ucStackDepth 为当前压栈的状态机数，
             栈顶为空,，即astFsmStack[ucStackDepth]为空，即下一次入栈放入的位置，
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           ucStackDepth;                           /* 当前压栈的状态机数 */
    NAS_EMM_FSM_STATE_STRU              astFsmStack[NAS_LMM_MAX_STACK_DEPTH];    /* 状态机栈的深度 */
}NAS_LMM_FSM_STATE_STACK_STRU;
typedef NAS_LMM_FSM_STATE_STACK_STRU     NAS_EMM_FSM_STATE_STACK_STRU;
typedef NAS_LMM_FSM_STATE_STACK_STRU     NAS_EMMC_FSM_STATE_STACK_STRU;




/*****************************************************************************
 结构名    : NAS_LMM_COMM_ACTION_FUN
 结构说明  : MM动作处理函数的类型定义，目前用于初始化处理
*****************************************************************************/
typedef VOS_UINT32  ( * NAS_LMM_COMM_ACTION_FUN )( MsgBlock  *  /* 消息指针 */);

typedef VOS_UINT32  ( * NAS_EMMC_COMM_ACTION_FUN )( MsgBlock  *  /* 消息指针 */);

/*****************************************************************************
 结构名    : NAS_LMM_COMM_ACT_STRU
 结构说明  : MM动作表结构，目前用于初始化处理
*****************************************************************************/
typedef VOS_UINT32  MM_MSG_TYPE_ENUM_UINT32;

typedef struct
{
    MM_MSG_TYPE_ENUM_UINT32             ulMsgId;     /* 消息ID */
    VOS_UINT32                          ulSenderPid;
    NAS_LMM_COMM_ACTION_FUN              pfFun;     /* 消息处理函数 */
}NAS_LMM_COMM_ACT_STRU;

typedef struct
{
    MM_MSG_TYPE_ENUM_UINT32              ulMsgId;     /* 消息ID */
    VOS_UINT32                           ulSenderPid;
    NAS_LMM_COMM_ACTION_FUN              pfFun;       /* 消息处理函数 */
}NAS_EMMC_COMM_ACT_STRU;



/*****************************************************************************
 结构名    : NAS_LMM_FSM_STRU
 结构说明  : 存放各个状态机
*****************************************************************************/
typedef struct
{
    NAS_LMM_FSM_STATE_STRU               astCurFsm[NAS_LMM_PARALLEL_FSM_BUTT];   /* 状态机*/
    NAS_LMM_FSM_STATE_STACK_STRU         astFsmStack[NAS_LMM_PARALLEL_FSM_BUTT]; /* 状态机的状态机栈的数组   */
    NAS_LMM_FSM_MSG_BUF_STRU             astFsmMsgBuffer[NAS_LMM_PARALLEL_FSM_BUTT];/* 该状态机缓存的消息的数组 */
} NAS_LMM_FSM_STRU;



/* 定义异常函数原型 */
typedef VOS_UINT32 ( * NAS_LMM_EXCEP_FUN )
(
    VOS_UINT32, /* EVENT ID,包括PID和MSG ID */
    VOS_VOID *  /* 消息指针 */
);

/* 动作处理函数的类型定义 */
typedef VOS_UINT32 ( * NAS_LMM_ACTION_FUN )
(
    VOS_UINT32, /* 消息ID   */
    VOS_VOID *  /* 消息指针 */
);


/* 动作表结构 */
typedef struct
{
    VOS_UINT32                          ulEventType;        /* 事件类型 */
    NAS_LMM_ACTION_FUN                   pfActionFun;        /* 动作函数 */
}NAS_LMM_ACT_STRU;
typedef NAS_LMM_ACT_STRU                 NAS_EMM_ACT_STRU;
typedef NAS_LMM_ACT_STRU                 NAS_EMMC_ACT_STRU;


/* 状态转移表结构 */
typedef struct
{
    VOS_UINT32                          ulState;            /* 状态                                */
    VOS_UINT32                          ulSize;             /* 动作表的大小字节数除以ACT结构的大小 */
    NAS_LMM_ACT_STRU                    *pActTable;          /* 动作表的基地址                      */
}NAS_LMM_STA_STRU;
typedef NAS_LMM_STA_STRU                 NAS_EMM_STA_STRU;
typedef NAS_LMM_STA_STRU                 NAS_EMMC_STA_STRU;


/* 有限状态机描述符结构 */
typedef struct
{
    NAS_LMM_STA_STRU*                    pStaTable;          /* 状态转移表的基地址     */
    VOS_UINT32                          ulSize;             /* 状态转移表的大小       */
    VOS_UINT32                          aulMmParaFsmId;     /* 并行有限状态机的ID       */
    NAS_LMM_EXCEP_FUN                    pfExceptHandle;     /* 用于处理异常的回调函数 */
}NAS_LMM_FSM_DESC_STRU;

/* 消息头定义 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
}NAS_LMM_MSG_HEADER_STRU;


/*****************************************************************************
 结构名    : NAS_LMM_AUXILIARY_FSM_STRU
 结构说明  : EMM的辅助状态机
*****************************************************************************/
typedef struct
{
    NAS_EMM_UPDATE_STATE_ENUM_UINT8     ucEmmUpStat;    /* EMM UPDATE STATE */
    NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucRrcConnState; /* 当前RRC连接是否存在 */
    VOS_UINT8                           aucRsv[2];
    NAS_APP_REG_STAT_ENUM_UINT32        enNasAppRegState;
/* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    NAS_LMM_CUR_LTE_STATE_ENUM_UINT32   ulCurLteState;
/* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */

}NAS_LMM_AUXILIARY_FSM_STRU;



/*****************************************************************************
 结构名    : NAS_LMM_TIMER_CTRL_STRU
 结构说明  : NAS_LMM 定时器结构

             其中的参数与收到的TIMER的超时消息中的参数的对应:
             参见:  REL_TIMER_MSG

定时器停止时: NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8被清0,
              NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8被清0;

定时器启动时: NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8被置1,
              NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8被清0;

定时器暂停时: NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8被置1,
              NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8被置1,

当空口消息中更新定时器时长时, usTimerValMask被置位, 定时器启动时判断;
如被置位，则调用OS API更新时长，并将usTimerSusMask清零，然后再启动;
*****************************************************************************/
typedef struct
{

    HTIMER                              psthTimer;          /* Timer句柄 */
    VOS_UINT32                          ulName;             /* 即 NAS_LMM_STATE_TI_ENUM_UINT16*/
    VOS_UINT32                          ulParam;            /* 各模块自己决定填写，也可以不填 */
    VOS_UINT32                          ulTimerLen;         /* Timer时长(UNIT: ms) */
    VOS_UINT32                          ulTimerRemainLen;   /* Timer暂停状态下的剩余时长(UNIT: ms),只有当
                                                               ucTimerSs == NAS_LMM_TIMER_SS_SUSPENDING 时有效*/
    VOS_UINT8                           ucMaxNum;           /* 定时器超时最大次数(N) */
    VOS_UINT8                           ucExpedNum;         /* 已超时次数 */
    VOS_UINT8                           ucMode;             /* timer work mode
                                                               VOS_RELTIMER_LOOP   -- start periodically
                                                               VOS_RELTIMER_NOLOOP -- start once time */
    NAS_LMM_TIMER_TYPE_ENUM_UINT8        ucTimerType;        /* NAS_LMM_STATE_TIMER或者NAS_LMM_PTL_TIMER */
    NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8   ucTimerRs;
    NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8   ucTimerSs;
    NAS_LMM_TIMER_VALUE_STATE_ENUM_UINT8 ucTimerVs;          /* UE 1.0 暂不使用 */

    VOS_UINT8                           ucRsv;

}NAS_LMM_TIMER_CTRL_STRU;


/*****************************************************************************
 结构名    : NAS_LMM_MAIN_CONTEXT_STRU
 结构说明  : MM 模块运行上下文
*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        NAS_LMM 状态机状态及其状态栈
    **************************************************************************/
    NAS_LMM_FSM_STRU                     stNasMmFsm;

    /**************************************************************************
                        NAS_LMM 辅助状态
    **************************************************************************/
    NAS_LMM_AUXILIARY_FSM_STRU           stNasMmAuxFsm;

    /**************************************************************************
                        NAS_LMM 状态定时器控制表
    **************************************************************************/
    NAS_LMM_TIMER_CTRL_STRU              astMmTimerSta[NAS_LMM_STATE_TI_BUTT];

    /**************************************************************************
                        NAS_LMM 协议定时器控制表
    **************************************************************************/
    NAS_LMM_TIMER_CTRL_STRU              astMmTimerPtl[NAS_LMM_PTL_TI_BUTT];



    /**************************************************************************
                        内部消息队列存储区
    **************************************************************************/
    NAS_LMM_INTRA_MSG_QUEUE_STRU         stMmIntraMsgQueue;

}NAS_LMM_MAIN_CONTEXT_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_LMM_MAIN_CONTEXT_STRU        g_stMmMainContext;
extern  NAS_LMM_FSM_DESC_STRU            g_astNasMmFsmDesc[NAS_LMM_PARALLEL_FSM_BUTT];
extern  VOS_UINT32                       g_ulMmcSerRegFlag;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32   NAS_LMM_FsmRegisterFsm(     NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParaFsmId,
                                               VOS_UINT32                      ulSize,
                                               NAS_LMM_STA_STRU                *pStaTable,
                                               NAS_LMM_EXCEP_FUN                pfExceptHandle );

extern VOS_UINT32   NAS_LMM_FsmProcessEvent(    NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                                               VOS_UINT32                      ulEventType,
                                               VOS_UINT32                      ulMsgID,
                                               VOS_UINT8                      *pRcvMsg );
extern NAS_LMM_ACTION_FUN   NAS_LMM_FsmFindAct(  const NAS_LMM_FSM_DESC_STRU   *pFsmDesc,
                                               VOS_UINT32              ulState,
                                               VOS_UINT32              ulEventType);

extern VOS_VOID    NAS_LMM_FsmGetEvtTab(        const NAS_LMM_FSM_DESC_STRU   *pFsmDesc,
                                               VOS_UINT32             *pulStaTblLoc);


extern VOS_VOID    NAS_LMM_FsmGetEvtStatFun(    const NAS_LMM_FSM_DESC_STRU   *pFsmDesc,
                                               VOS_UINT32              ulFsmStaTblLoc,
                                               VOS_UINT32              ulEventType,
                                               VOS_UINT32             *pulEmmActTblLoc);

extern VOS_VOID     NAS_LMM_FsmTranState(       NAS_LMM_FSM_STATE_STRU  stDestState);
extern VOS_UINT32   NAS_LMM_MsgProcessInFsm(    NAS_LMM_PARALLEL_FSM_ENUM_UINT16  enParalFsmId,
                                               MsgBlock                        *pMsg,
                                               VOS_UINT32                       ulMsgId,
                                               VOS_UINT32                       ulEventType );
extern  VOS_UINT32  NAS_LMM_ClearOnePtlTimer(   NAS_LMM_PTL_TI_ENUM_UINT16    usTi);
extern  VOS_UINT32  NAS_LMM_ClearOneStaTimer(   NAS_LMM_STATE_TI_ENUM_UINT16  usTi);
extern  NAS_LMM_COMM_ACTION_FUN  NAS_LMM_CommFindFun(
                                                const NAS_LMM_COMM_ACT_STRU   *pastMap,
                                                VOS_UINT32              ulMapNum,
                                                VOS_UINT32              ulMsgId,
                                                VOS_UINT32              ulSenderPid);

extern  NAS_EMMC_COMM_ACTION_FUN  NAS_EMMC_CommFindFun(
                                        const NAS_EMMC_COMM_ACT_STRU   *pastMap,
                                        VOS_UINT32              ulMapNum,
                                        VOS_UINT32              ulMsgId,
                                        VOS_UINT32              ulSenderPid);
extern  VOS_VOID  NAS_LMM_AppStateChange( NAS_EMM_FSM_STATE_STRU  stEmmDestState);
extern  VOS_VOID  NAS_LMM_StateMap(const NAS_EMM_FSM_STATE_STRU *pstEmmDestState,
                            NAS_APP_REG_STAT_ENUM_UINT32   *pulNasAppDstState);
extern VOS_VOID  NAS_LMM_RegStatOsa(const NAS_APP_REG_STAT_ENUM_UINT32   *pulNasAppDstState,
                               APP_REG_STAT_ENUM_UINT32       *pulAppRegStat);
extern VOS_VOID  NAS_LMM_StaTransProc( NAS_LMM_FSM_STATE_STRU  stDestState );
extern VOS_VOID  NAS_LMM_EnterDeregStateModify
(
    NAS_LMM_FSM_STATE_STRU              *pstDestState
);
extern VOS_VOID  NAS_LMM_ActionBeforeTransToDestSta( NAS_LMM_FSM_STATE_STRU  stDestState );
extern VOS_UINT32  NAS_LMM_GetServiceDomain(NAS_LMM_MAIN_STATE_ENUM_UINT16  enMainState);
/* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
extern VOS_VOID NAS_LMM_SndOmLogStateChange(NAS_LMM_FSM_STATE_STRU *pstCurState, NAS_LMM_FSM_STATE_STRU *pstDestState);
/* 根据转换后的状态进行统计Ser Other Fail计数 */
extern VOS_VOID NAS_LMM_UpdateSerOtherFailCounter(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMFsm.h*/
