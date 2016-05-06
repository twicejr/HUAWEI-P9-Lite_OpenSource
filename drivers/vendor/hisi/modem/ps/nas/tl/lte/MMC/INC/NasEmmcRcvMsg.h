

#ifndef __NASEMMCRCVMMCMSG_H__
#define __NASEMMCRCVMMCMSG_H__



/*****************************************************************************
1 Include Headfile
*****************************************************************************/
#include  "vos.h"

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
#define NAS_EMMC_LA_INFO_MASK_LOW_BIT          0x00000001
#define NAS_EMMC_LA_INFO_MASK_SEC_BIT          0x00000002
#define NAS_EMMC_LA_INFO_MASK_THD_BIT          0x00000004


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
extern VOS_UINT32  NAS_EMMC_RcvMmcPlmnSrchReq(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMMC_RcvEmmStartReq(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMMC_RcvEmmStopReq(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMMC_RcvRrcPlmnSrchCnf (MsgBlock *pMsg  );
extern VOS_UINT32  NAS_EMMC_RcvRrcSysInfoInd(MsgBlock *pMsg );
/*extern VOS_UINT32  NAS_EMMC_RcvEmmActionRsltReq(MsgBlock *pMsg );*/
extern VOS_UINT32  NAS_EMMC_RcvMmcEplmnNotifyReq(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvMmcStopSrchReq(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcPlmnSrchStopCnf(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcAreaLostInd(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMMC_RcvMmcUserPlmnEndNotify(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMMC_RcvMmcGsmSysInfoInd(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMMC_RcvMmcUmtsSysInfoInd(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMMC_RcvMmcBgPlmnSearchReq(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvMmcStopBgPlmnSearchReq(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcBgPlmnSearchCnf(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcBgPlmnSearchStopCnf(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcNotCampOnInd(MsgBlock *pMsg);



extern VOS_UINT32  NAS_EMMC_RcvMmcCellSelectionReq(  MsgBlock *pMsg );
extern VOS_UINT32 NAS_LMM_PreProcMmcLteSysInfoInd(MsgBlock *pMsg );

extern VOS_UINT32  NAS_EMMC_RcvRrcSearchPlmnInfoInd(MsgBlock *pMsg);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32  NAS_EMMC_RcvRrcBgSearchHrpdCnf(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcBgSearchHrpdStopCnf(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvMmcBgSearchHrpdReq(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvMmcStopBgSearchHrpdReq(MsgBlock *pMsg);
#endif
#if (FEATURE_ON == FEATURE_CSG)
extern VOS_UINT32  NAS_EMMC_RcvMmcCsgWhiteListNotify(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvMmcCsgListSearchReq(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvMmcCsgBgPlmnSearchReq(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcCsgBgPlmnSearchCnf(MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcCsgListSrchCnf (MsgBlock *pMsg);
extern VOS_UINT32  NAS_EMMC_RcvRrcCsgIdHomeNodeBNameInd (MsgBlock *pMsg);
#endif

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

#endif  /* end of NasEmmcRcvMmcMsg.h */

