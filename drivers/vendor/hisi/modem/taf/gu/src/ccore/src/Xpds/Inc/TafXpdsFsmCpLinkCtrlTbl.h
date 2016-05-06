

#ifndef __TAF_XPDS_FSM_CP_LINK_CTRL_TBL_H__
#define __TAF_XPDS_FSM_CP_LINK_CTRL_TBL_H__

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
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_XPDS_CP_LINK_Ctrl_SUBSTA_ENUM_UINT32
 枚举说明  : XPDS LINK Ctrl子状态枚举定义
 1.日    期   : 2015年8月21日
   作    者   : g00261581
   修改内容   : 新建

*****************************************************************************/
enum TAF_XPDS_CP_LINK_Ctrl_SUBSTA_ENUM
{
    TAF_XPDS_CP_LINK_CTRL_SUBSTA_INIT                               = 0x00,
    TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF         = 0x01,
    TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_DATA_CAll_STATUS_IND_MO   = 0x02, /* in mobile originated */
    TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_ANSWER_CAll_CNF           = 0X03,
    TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_DATA_CAll_STATUS_IND_MT   = 0x04, /* in mobile terminated */
    TAF_XPDS_CP_LINK_CTRL_SUBSTA_WAIT_XCC_CALL_CONN_IND             = 0X05,

    TAF_XPDS_CP_LINK_CTRL_SUBSTA_BUTT
};
typedef VOS_UINT32 TAF_XPDS_CP_LINK_Ctrl_SUBSTA_ENUM_UINT32;


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
VOS_UINT32 TAF_XPDS_GetCpLinkCtrlStaTblSize( VOS_VOID );
TAF_STA_STRU* TAF_XPDS_GetCpLinkCtrlStaTblAddr( VOS_VOID );
TAF_FSM_DESC_STRU * TAF_XPDS_GetFsmCpLinkFsmDescAddr( VOS_VOID );

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

