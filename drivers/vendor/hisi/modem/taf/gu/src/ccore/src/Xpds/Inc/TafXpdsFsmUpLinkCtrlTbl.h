

#ifndef __TAF_XPDS_FSM_LINK_CTRL_TBL_H__
#define __TAF_XPDS_FSM_LINK_CTRL_TBL_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "TafFsm.h"
#include "TafXpdsSndInternalMsg.h"
#include "AtXpdsInterface.h"
#include "xcc_xpds_pif.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/

/*****************************************************************************
  3 Ã¶¾Ù¶¨Òå
*****************************************************************************/

enum TAF_XPDS_LINK_CTRL_SUBSTA_ENUM
{
    TAF_XPDS_UP_LINK_CTRL_SUBSTA_INIT                            = 0x00,
    TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF      = 0x01,
    TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_MPC_SOCKET_CNF        = 0x02,
    TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_MPC_SOCKET_CNF       = 0x03,
    TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_PDE_SOCKET_CNF        = 0x04,
    TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_PDE_SOCKET_CNF       = 0x05,

    TAF_XPDS_UP_LINK_CTRL_SUBSTA_BUTT
};
typedef VOS_UINT32 TAF_XPDS_LINK_CTRL_SUBSTA_ENUM_UINT32;


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/


/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/


/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetUpLinkCtrlStaTblSize( VOS_VOID );
TAF_STA_STRU* TAF_XPDS_GetUpLinkCtrlStaTblAddr( VOS_VOID );
TAF_FSM_DESC_STRU * TAF_XPDS_GetFsmUpLinkFsmDescAddr( VOS_VOID );

#endif /* FEATURE_UE_MODE_CDMA */

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

#endif /* end of TafXpdsFsmLinkCtrlTbl.h */

