

#ifndef __CNAS_HSM_ENCODE_H__
#define __CNAS_HSM_ENCODE_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
/* UATI request message:according to protocol,it only contains two value and each value occupy 8 bits */
#define CNAS_HSM_UATI_REQ_MSG_OCTET_LEN                     ( 2 )
#define CNAS_HSM_UATI_REQ_MSG_BIT_LEN                       ( CNAS_HSM_UATI_REQ_MSG_OCTET_LEN * CNAS_HSM_BIT_LEN_PER_BYTE )

#define CNAS_HSM_KEEP_ALIVE_REQ_MSG_OCTET_LEN               ( 2 )
#define CNAS_HSM_KEEP_ALIVE_RESP_MSG_OCTET_LEN              ( 2 )


/* UATI complete message:this is dynamic due to the upper old UATI length */
#define CNAS_HSM_GET_UATI_COMPLETE_MSG_OCTET_LEN(ucOldUATILen)            ( 3 + (ucOldUATILen) )
#define CNAS_HSM_GET_UATI_COMPLETE_MSG_BIT_LEN(ucOldUATILen)              ( (3 + (ucOldUATILen)) * CNAS_HSM_BIT_LEN_PER_BYTE )

/* hardware id request message:according to protocol,it only contains two value and each value occupy 8 bits */
#define CNAS_HSM_HARDWARE_ID_REQ_MSG_OCTET_LEN                ( 2 )
#define CNAS_HSM_HARDWARE_ID_REQ_MSG_BIT_LEN                  ( CNAS_HSM_HARDWARE_ID_REQ_MSG_OCTET_LEN * CNAS_HSM_BIT_LEN_PER_BYTE )

/* hardware ID TYPE length */
#define CNAS_HSM_HARDWARE_ID_TYPE_OCTET_LENGTH               ( 3 )

/* HARDWARE ID response complete message:this is dynamic due to hardware id length */
#define CNAS_HSM_GET_HARDWARE_ID_RESPONSE_MSG_OCTET_LEN(ucHardwareIdLen)            ( 6 + (ucHardwareIdLen) )
#define CNAS_HSM_GET_HARDWARE_ID_RESPONSE_MSG_BIT_LEN(ucHardwareIdLen)              ( (6 + (ucHardwareIdLen)) * CNAS_HSM_BIT_LEN_PER_BYTE )

/* session close message:this is dynamic due to moreinfo length */
#define CNAS_HSM_SESSION_CLOSE_MSG_WITHOUT_MOREINFO_BIT_LEN                     ( 3 * CNAS_HSM_BIT_LEN_PER_BYTE )
#define CNAS_HSM_GET_SESSION_CLOSE_MSG_OCTET_LEN(ucMoreInfoLen)                 ( 3 + (ucMoreInfoLen) )
#define CNAS_HSM_GET_SESSION_CLOSE_MSG_BIT_LEN(ucMoreInfoLen)                   ( (3 + (ucMoreInfoLen)) * CNAS_HSM_BIT_LEN_PER_BYTE )

#define CNAS_HSM_SESSION_CLOSE_MSG_MOREINFOLEN_WITH_7BIT_TYPE                   ( 1 + 2 ) /* 7BitType + SubType */
#define CNAS_HSM_SESSION_CLOSE_MSG_MOREINFOLEN_WITH_15BIT_TYPE                  ( 2 + 2 ) /* 15BitType + SubType */

/* Maximum value which can be stored in 7 bit variable i.e. 01111111 */
#define CNAS_HSM_SESSION_CLOSE_MSG_MAX_VALUE_STORED_IN_7BIT_VAR                 ( 127 )


#define CNAS_HSM_UATI_ASSIGN_WITHOUT_SUBNET_MSG_BIT_LEN     ( 8 * CNAS_HSM_BIT_LEN_PER_BYTE )
#define CNAS_HSM_UATI_ASSIGN_WITH_SUBNET_MSG_BIT_LEN        ( 22 * CNAS_HSM_BIT_LEN_PER_BYTE )

#define CNAS_HSM_KEEP_ALIVE_REQ_MSG_BIT_LEN                 ( CNAS_HSM_KEEP_ALIVE_REQ_MSG_OCTET_LEN * CNAS_HSM_BIT_LEN_PER_BYTE )
#define CNAS_HSM_KEEP_ALIVE_RESP_MSG_BIT_LEN                ( CNAS_HSM_KEEP_ALIVE_RESP_MSG_OCTET_LEN * CNAS_HSM_BIT_LEN_PER_BYTE )


#define CNAS_HSM_UATI104_OCTET_LENGTH                        (13)

#define CNAS_HSM_UATI024_OCTET_LENGTH                        (3)

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

enum CNAS_HSM_AMP_MESSAGE_TYPE_ENUM
{
    CNAS_HSM_AMP_MSG_TYPE_UATI_REQ                          = 0x00,
    CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN                       = 0x01,
    CNAS_HSM_AMP_MSG_TYPE_UATI_COMPLETE                     = 0x02,
    CNAS_HSM_AMP_MSG_TYPE_HARDWAREID_REQ                    = 0x03,
    CNAS_HSM_AMP_MSG_TYPE_HARDWAREID_RESP                   = 0x04,
    CNAS_HSM_AMP_MESSAGE_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_HSM_AMP_MESSAGE_TYPE_ENUM_UINT8;


enum CNAS_HSM_SMP_MESSAGE_TYPE_ENUM
{
    CNAS_HSM_SMP_MESSAGE_TYPE_SESSION_CLOSE                 = 0x01,
    CNAS_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_REQ                = 0x02,
    CNAS_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_RESP               = 0x03,
    CNAS_HSM_SMP_MESSAGE_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_HSM_SMP_MESSAGE_TYPE_ENUM_UINT8;

/* Move CNAS_HSM_CLOSE_REASON_TYPE_ENUM_UINT8 to CnasHsmCtx.h: CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM_UINT8 */


enum CNAS_HSM_ENCODE_ERROR_TYPE_ENUM
{
    CNAS_HSM_ENCODE_SUCCESS                                    = 0x00,
    CNAS_HSM_ENCODE_FAILURE                                    = 0x01,

    CNAS_HSM_ENCODE_ERROR_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_HSM_ENCODE_ERROR_TYPE_ENUM_UINT32;


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


typedef struct
{
    CNAS_HSM_HARDWARE_ID_TYPE_ENUM_UINT32                   enHwidType;
    VOS_UINT32                                              ulEsn;                              /* 32-bit */
    VOS_UINT8                                               aucMeId[CNAS_HSM_MEID_OCTET_NUM];    /* 56-bit */
    VOS_UINT8                                               ucTransactionId;
}CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU;


typedef struct
{
    VOS_UINT8                           ucMsgSeq;
    VOS_UINT8                           ucOldUATILen;                       /* 4 bits */
    VOS_UINT8                           aucOldUATI[CNAS_HSM_UATI_OCTET_LENGTH];
    VOS_UINT8                           aucRsv[2];
}CNAS_HSM_UATI_COMP_MSG_STRU;


typedef struct
{
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM_UINT8       enCloseReason;
    VOS_UINT8                                               ucMoreInfoLen;
    VOS_UINT8                                               aucRsv[2];
    VOS_UINT16                                              usType;
    VOS_UINT16                                              usSubType;
}CNAS_HSM_SESSION_CLOSE_MSG_STRU;


typedef struct
{
    VOS_UINT8                           ucMsgSeq;
    VOS_UINT8                           ucSubnetIncluded;
    VOS_UINT8                           ucUATISubnetMask;                  /* 0 or 8 bits */
    VOS_UINT8                           ucOldUATILen;                      /* 4 bits */
    /* UATI[23:0] ,aucUati024[0] is UATI[23:16] */
    VOS_UINT8                           aucUati024[CNAS_HSM_UATI024_OCTET_LENGTH];
    VOS_UINT8                           ucUATIColorCode;
    VOS_UINT8                           aucUati104[CNAS_HSM_UATI104_OCTET_LENGTH];
    VOS_UINT8                           aucRsv[3];
}CNAS_HSM_UATI_ASSIGN_MSG_STRU;


typedef struct
{
    VOS_UINT8                                               ucTransactionId;
    VOS_UINT8                                               aucRsv[3];
}CNAS_HSM_UATI_REQ_MSG_STRU;


typedef struct
{
    VOS_UINT8                                               ucTransactionId;
    VOS_UINT8                                               aucRsv[3];
}CNAS_HSM_HARDWARE_ID_REQ_MSG;


typedef struct
{
    VOS_UINT8                           ucTransId;
    VOS_UINT8                           aucRsrvd[3];
}CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU;


typedef struct
{
    VOS_UINT8                           ucTransId;
    VOS_UINT8                           aucRsrvd[3];
}CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU;

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
VOS_UINT8 CNAS_HSM_GetHardwareIdLength(
    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                 *pstHwIdRspMsg
);

VOS_VOID CNAS_HSM_EncodeUATIReq(
    VOS_VOID                           *pInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
);

VOS_VOID CNAS_HSM_EncodeUATIComplete(
    VOS_VOID                           *pInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
);

VOS_VOID CNAS_HSM_EncodeHardwareIdResponse(
    VOS_VOID                           *pInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
);

VOS_VOID CNAS_HSM_EncodeSessionClose(
    VOS_VOID                           *pInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
);

VOS_VOID CNAS_HSM_EncodeKeepAliveReq(
    VOS_VOID                           *pucInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
);

VOS_VOID CNAS_HSM_EncodeKeepAliveResp(
    VOS_VOID                           *pucInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
);


VOS_UINT16 CNAS_HSM_GetSessionCloseMsgEncodedBufLen(
    CNAS_HSM_SESSION_CLOSE_MSG_STRU     *pstSessionCloseInput
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

#endif /* end of CnasHsmEncode.h */





