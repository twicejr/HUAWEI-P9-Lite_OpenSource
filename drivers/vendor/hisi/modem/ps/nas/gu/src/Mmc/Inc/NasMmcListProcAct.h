/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcListProcAct.h
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2010年12月7日
  最近修改   :
  功能描述   : NasMmcListProcAct.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月7日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_LISTPROCACT_H_
#define _NAS_MMC_LISTPROCACT_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


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
#define NAS_MMC_MAX_SYSINFO_LEN        255
typedef struct
{
    VOS_BOOL                            bNeedTransferSysInfo;
    VOS_UINT8                           aucSysContend[NAS_MMC_MAX_SYSINFO_LEN];
}NAS_MMC_SAVE_SYSINFO_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32  NAS_MMC_ProcPowerOffReqInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);



VOS_UINT32     NAS_MMC_ProcPlmnListAbortReqInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcSignalingStatusIndInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32    NAS_MMC_ProcMmRrConnInfoIndInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnSrchCnfInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmSysInfoIndInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmRelIndInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmSuspendIndInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmNotCampOnIndInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32     NAS_MMC_ProcPowerOffReqInUserListFirst(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnListAbortReqInUserListFirst(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnSrchCnfInUserListFirst(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmSysInfoIndInUserListFirst(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmRelIndInUserListFirst(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmSuspendIndInUserListFirst(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcWaitPlmnListTimerOutInUserListFirst(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcWaitPlmnListTimerOutInUserListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPowerOffReqInUserListSecond(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnListAbortReqInUserListSecond(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32     NAS_MMC_ProcPlmnSrchCnfInUserListSecond(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32     NAS_MMC_ProcRrmmRelIndInUserListSecond(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmSuspendIndInUserListSecond(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcWaitPlmnListTimerOutInUserListSecond(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32     NAS_MMC_ProcPowerOffReqInUserListSuspendForList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnListAbortReqInUserListSuspendForList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmRelIndInUserListSuspendForList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmSuspendCnfInUserListSuspendForList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32     NAS_MMC_ProcWaitSuspendCnfTimerOutInUserListSuspendForList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPowerOffReqInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcCmServiceIndInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcGmmDetachCnfInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcMmDetachCnfInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnSrchStopCnfInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmSysInfoIndInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcRrmmRelIndInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcWaitAsStopTimerOutInUserList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcAttachReqInUserListSuspenForSpecify(
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcDetachReqInUserListSuspenForSpecify(
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPowerOffReqInUserListSuspenForSpecify(
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnUserSelReqInUserListSuspenForSpecify(
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcSysCfgSetReqInUserListSuspenForSpecify(
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnListReqInUserListSuspenForSpecify(
    struct MsgCB                        *pstMsg
);

VOS_VOID  NAS_MMC_ProcPlmnSpecifyReqInUserListSuspenForSpecify(
    struct MsgCB                        *pstMsg
);


VOS_UINT32  NAS_MMC_CommPlmnListReq( VOS_VOID );

VOS_UINT32     NAS_MMC_ProcAttachReqInInternalListAll(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

extern VOS_UINT32  NAS_MMC_ProcDetachReqInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcPowerOffReqInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcSyscfgReqInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcPlmnListReqInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcPlmnSpecifyReqInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcSignalingStatusIndInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcGmmDetachCnfInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcMmRrConnInfoIndInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcPlmnSrchCnfInInternalListAll(
           VOS_UINT32                          sulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcMmDetachCnfInInternalListAll(
           VOS_UINT32                          sulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcRrmmSysInfoIndInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcRrmmRelIndInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcRrmmSuspendIndInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );

extern VOS_UINT32  NAS_MMC_ProcRrmmNotCampOnIndInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcWaitPlmnListTimerOutInInternalListAll(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );

extern VOS_UINT32  NAS_MMC_ProcPowerOffReqInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcPlmnSrchStopCnfInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcRrmmSysInfoIndInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcRrmmSuspendIndInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcRrmmRelIndInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcWaitAsStopTimerOutInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


VOS_UINT32  NAS_MMC_ProcInternalPlmnListBufferMsg(
    VOS_UINT8                           *pucMsgBuffer
);

VOS_UINT32  NAS_MMC_ProcInternalPlmnSpecBufferMsg(
    VOS_UINT8                           *pucMsgBuffer
);

VOS_UINT32  NAS_MMC_ProcInternalBackPlmnBeforeUserSrchBufferMsg(
    VOS_UINT8                           *pucMsgBuffer
);

VOS_VOID  NAS_MMC_SrchPlmnWithListRst( VOS_VOID );

VOS_VOID  NAS_MMC_BeginSrchPlmnInSrchPlmnList( VOS_VOID );

VOS_UINT32     NAS_MMC_ProcAttachReqInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcDetachReqInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcSysCfgReqInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnListReqInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32     NAS_MMC_ProcPlmnSpecialReqInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

extern VOS_UINT32  NAS_MMC_ProcAttachReqInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcDetachReqInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcSysCfgReqInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcPlmnListAbortReqInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcPlmnListReqInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcPlmnSpecialReqInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcSignalingStatusIndInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcGmmDetachCnfInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );

extern VOS_UINT32  NAS_MMC_ProcMmDetachCnfInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


extern VOS_UINT32  NAS_MMC_ProcMmRrConnInfoIndInInternalListStop(
           VOS_UINT32                          ulEventType,
           struct MsgCB                        *pstMsg
       );


VOS_VOID     NAS_MMC_ProcSelectPlmnAction(
    NAS_MML_PLMN_WITH_RAT_STRU          *pstDestPlmn
);

VOS_UINT32     NAS_MMC_ProcRrmmSuspendIndInUserListStop(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_VOID     NAS_MMC_MockDulaPlmnList(
    RRC_PLMN_ID_LIST_STRU              *pstSrcPlmnList,
    RRC_PLMN_ID_LIST_STRU              *pstWModePlmnList,
    RRC_PLMN_ID_LIST_STRU              *pstGModePlmnList
);

VOS_UINT32     NAS_MMC_SrchRplmnOrHplmnToSrchLisForListStop( VOS_VOID );


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasMmcListProcAct.h */
