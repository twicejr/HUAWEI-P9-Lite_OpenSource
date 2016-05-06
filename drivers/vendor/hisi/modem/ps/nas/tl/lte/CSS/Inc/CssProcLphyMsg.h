/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : CssProcLphyMsg.h
    Description : CSS处理LPHY消息的头文件
    History     :
      1.wangchen 00209181   2015-05-14  Draft Enact


******************************************************************************/

#ifndef __CSSPROCLPHYMSG_H__
#define __CSSPROCLPHYMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "NasMmlCtx.h"
#include    "CssPublic.h"

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


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/




/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc(VOS_VOID);
extern VOS_VOID CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfSucc(VOS_VOID);
extern VOS_VOID CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc(VOS_VOID);

extern VOS_VOID CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfFail();
extern VOS_VOID CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail();
extern VOS_VOID CSS_ProcLphyMsgScanIndForCommScan
(
    const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
);
extern VOS_VOID CSS_ProcLphyMsgScanIndForAsScan
(
 const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
 );

extern VOS_VOID CSS_SndLphyMsgStopBandScanReq
(
    VOS_VOID
);

extern VOS_VOID CSS_SndLphyMsgSetWorkModeReq
(
    CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16       enWorkModeType
);

extern VOS_VOID CSS_SndLphyMsgCommBandScanReq
(
    CSS_COMM_SCAN_BAND_NODE_STRU               *pstBandNode,
    CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16         enScanType,
    VOS_UINT8                                   ucCurFreqRangeIdx
);
extern VOS_UINT32 CSS_IsAsScanNeedSndLphyNextBandScanReq(VOS_VOID);
extern VOS_VOID CSS_SndLphyMsgStartBgSearchReq(VOS_VOID);
extern VOS_VOID CSS_SndLphyMsgStopBgSearchReq(VOS_VOID);
extern VOS_VOID CSS_ProcLphyMsgScanInd
(
    const CSS_LPHY_BAND_SCAN_IND_STRU   *pRcvMsg
);

extern VOS_VOID CSS_ProcLphyMsgStopScanCnf
(
    const CSS_LPHY_STOP_BAND_SCAN_CNF_STRU  *pRcvMsg
);

extern VOS_VOID CSS_ProcLphyMsgSetModeCnf
(
    const CSS_LPHY_SET_WORK_MODE_CNF_STRU   *pstSetModeCnf
);
extern VOS_VOID CSS_ProcLphyMsgStartBgSearchCnf
(
    const CSS_LPHY_START_BG_SEARCH_CNF_STRU  *pRcvMsg
);
extern VOS_VOID CSS_ProcLphyMsgStopBgSearchCnf
(
    const CSS_LPHY_STOP_BG_SEARCH_CNF_STRU  *pRcvMsg
);
extern VOS_VOID CSS_ProcLphyMsg(const VOS_VOID *pRcvMsg );
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

#endif /* end of CssProcLmmMsg.h */



