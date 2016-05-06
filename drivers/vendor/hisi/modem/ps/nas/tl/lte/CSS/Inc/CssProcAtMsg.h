/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : CssProcAtMsg.h
    Description : CSS处理At消息的头文件
    History     :
      1.chengmin 00285307   2015-10-12  Draft Enact


******************************************************************************/

#ifndef __CSSPROCATMSG_H__
#define __CSSPROCATMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "CssInterface.h"
#include    "CssPublic.h"
#include    "PsCommonDef.h"

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
extern VOS_VOID CSS_UpdateStateAccordingToAtMccSetMsg
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU           *pRcvMsg,
    VOS_UINT8                                     aucMcc[2],
    VOS_UINT32                                    ulRslt
);

extern VOS_VOID CSS_SendAtMccSetCnf(const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg, VOS_UINT32 ulResult);
extern VOS_VOID CSS_SendAtQueryMccNotifyByMccList(CSS_MCC_ID_STRU astMccID[CSS_MAX_PLMN_ID_NUM], VOS_UINT32 ulMccNum, VOS_UINT16 usClientId);
extern VOS_VOID CSS_ProcAtMsgDeleteOneMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
);
extern VOS_VOID CSS_ProcAtMsgDeleteAllMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
);
extern VOS_VOID CSS_ProcAtMsgAddMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
);
extern VOS_VOID CSS_ProcAtMsgMccSetReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
);
extern VOS_VOID CSS_ProcAtMsgMccVersionReq
(
    const AT_CSS_MCC_VERSION_INFO_REQ_STRU  *pRcvMsg
);
extern VOS_VOID CSS_ProcAtMsg(const VOS_VOID *pRcvMsg);


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

#endif /* end of CssProcAtMsg.h */





