

#ifndef __CNAS_HSM_DECODE_H__
#define __CNAS_HSM_DECODE_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmEncode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/



/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/


enum CNAS_HSM_DECODE_ERROR_TYPE_ENUM
{
    CNAS_HSM_DECODE_SUCCESS                                    = 0x00,
    CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_ID                  = 0x01,
    CNAS_HSM_DECODE_ERROR_TYPE_INVALID_PROT_TYPE               = 0x02,
    CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN                 = 0x03,
    CNAS_HSM_DECODE_ERROR_TYPE_MALLOC_FAILURE                  = 0x04,

    CNAS_HSM_DECODE_ERROR_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 The Declaration Of The Global Variable
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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeMsgType(
    CNAS_HSM_PROTOCOL_TYPE_ENUM_UINT16  enProtoType,
    VOS_UINT8                          *pucInMsgData,
    VOS_UINT8                          *pucOutMsgType
);

CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeHardwareIdRequest (
    VOS_UINT8                          *pucInData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_HARDWARE_ID_REQ_MSG       *pucOutHardWareIdReq
);

CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeUATIAssignment(
    VOS_UINT8                          *pucInData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstOutUatiAssign
);

CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeSessionClose(
    VOS_UINT8                          *pucInData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_SESSION_CLOSE_MSG_STRU    *pstOutSessionClose
);

CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeKeepAliveReq(
    VOS_UINT8                          *pucInMsgData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU   *pstOutBuff
);

CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeKeepAliveResp(
    VOS_UINT8                          *pucInMsgData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU  *pstOutBuff
);


#endif


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

#endif /* end of CnasHsmDecode.h */




