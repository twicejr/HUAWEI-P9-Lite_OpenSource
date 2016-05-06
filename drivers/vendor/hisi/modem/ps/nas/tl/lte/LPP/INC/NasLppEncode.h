


#ifndef __NASLPPENCODE_H__
#define __NASLPPENCODE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasLppAirMsg.h"
#include    "LppMtaInterface.h"
#include    "LocCommonInterface.h"
#include    "LPPLRrcInterface.h"


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
  2 Macro
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
extern VOS_UINT32 NAS_LPP_AccessTypesEncode(LPP_ACCESS_TYPES_STRU *pUserData, VOS_UINT32 ulStartIdx, VOS_UINT32 *pulEndIdx);

extern VOS_UINT16  NAS_LPP_EncodeMessage
(
    LPP_MESSAGE_STRU                   *pstLppMsg,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
);
extern VOS_UINT16  NAS_LPP_EncodeRrcLocInfo
(
    MTA_LPP_MEAS_REF_TIME_STRU                             *pstMtaLppMeasRefTime,
    LOC_COM_VELOCITY_STRU                                  *pstVelocityEstimate,
    LOC_COM_COORDINATE_STRU                                *pstLocationEstimate,
    LPP_LRRC_GNSS_DATA_INFO_IND_STRU                       *pstLppLrrcGnssDataInfo
);

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

#endif











































