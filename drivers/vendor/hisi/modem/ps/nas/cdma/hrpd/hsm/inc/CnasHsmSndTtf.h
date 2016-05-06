

#ifndef __CNAS_HSM_SND_TTF_H__
#define __CNAS_HSM_SND_TTF_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "cttf_hrpd_sig_public_pif.h"
#include "nas_cttf_hrpd_rsnp_pif.h"
#include "CnasHsmCtx.h"
#include "CnasHsmEncode.h"

#include "cnas_cttf_hrpd_pa_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
/* fill send cttf data request message header info */
#define CNAS_CFG_CTTF_HRPD_SNP_DATA_REQ_HEADER(pstSnpDataReqHeader, enProtoType, enAddrType, enChanType, enDeliverType, ucPri, enInsType)\
            (pstSnpDataReqHeader)->enProtocolType    = enProtoType;\
            (pstSnpDataReqHeader)->enAddressType     = enAddrType;\
            (pstSnpDataReqHeader)->enChannelType     = enChanType;\
            (pstSnpDataReqHeader)->enDeliveryType    = enDeliverType;\
            (pstSnpDataReqHeader)->ucPriority        = (ucPri);\
            (pstSnpDataReqHeader)->enInstanceType    = (enInsType)


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

typedef struct
{
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16                     enProtocolType; /**< protocol type */
    CTTF_HRPD_INSTANCE_TYPE_ENUM_UINT8                      enInstanceType;
    CTTF_HRPD_ADDRESS_TYPE_ENUM_UINT8                       enAddressType;  /**< addressing modes: broadcast, multicast, unicast */
    CTTF_HRPD_CHANNEL_TYPE_ENUM_UINT8                       enChannelType;  /**< channel type */
    CTTF_HRPD_DELLIVERY_TYPE_ENUM_UINT8                     enDeliveryType; /**< SLP delivery type */
    VOS_UINT8                                               ucPriority;     /**< a number between 0 and 255 */
    VOS_UINT8                                               aucRsv[3];
} CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU;

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

VOS_VOID CNAS_HSM_SndMacTransmitAtiNotify(
    CNAS_HSM_ATI_RECORD_STRU           *pstTransATI
);

VOS_VOID CNAS_HSM_SndMacReceiveAtiNotify(
    CNAS_HSM_ATI_LIST_INFO_STRU        *pstATIListInfo
);

VOS_VOID CNAS_HSM_SndTtfHrpdSnpDataReq(
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                *pstSnpDataReqHeader,
    VOS_UINT16                                             *pusOpId,
    VOS_UINT16                                              usMsgBitLen,
    VOS_UINT8                                              *pucMsgBuf
);

VOS_VOID CNAS_HSM_SndKeepAliveReqMsg(VOS_VOID);
VOS_VOID CNAS_HSM_SndKeepAliveRspMsg(
    VOS_UINT8                           ucKeepAliveReqTransId
);

VOS_VOID CNAS_HSM_SndHardWareIdRspMsg(
    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                 *pstHardWareIdRsp
);

VOS_VOID CNAS_HSM_SndSessionCloseMsg(
    CNAS_HSM_SESSION_CLOSE_MSG_STRU                        *pstSessionClose
);

VOS_VOID CNAS_HSM_SndUatiCmplMsg(VOS_VOID);

VOS_VOID CNAS_HSM_SndTtfHrpdPASessionCloseInd(VOS_VOID);


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

#endif /* end of CnasHsmMain.h */











