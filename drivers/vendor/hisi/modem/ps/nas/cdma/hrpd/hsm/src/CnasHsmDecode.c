

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmDecode.h"
#include "PsCommonDef.h"
#include "v_typdef.h"
#include "CnasHsmMntn.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_DECODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 Global variable
*****************************************************************************/

/*****************************************************************************
  3 Function Definitions
*****************************************************************************/


CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeMsgType(
    CNAS_HSM_PROTOCOL_TYPE_ENUM_UINT16  enProtoType,
    VOS_UINT8                          *pucInMsgData,
    VOS_UINT8                          *pucOutMsgType
)
{
    if ((CNAS_HSM_SESSION_MANAGEMENT_PROTOCOL == enProtoType)
     || (CNAS_HSM_ADDRESS_MANAGEMENT_PROTOCOL == enProtoType))
    {
        *pucOutMsgType = *pucInMsgData;

        return CNAS_HSM_DECODE_SUCCESS;
    }

    CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_DECODE_RESULT_IND, CNAS_HSM_DECODE_ERROR_TYPE_INVALID_PROT_TYPE);

    return CNAS_HSM_DECODE_ERROR_TYPE_INVALID_PROT_TYPE;
}


CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeHardwareIdRequest (
    VOS_UINT8                          *pucInData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_HARDWARE_ID_REQ_MSG       *pucOutHardWareIdReq
)
{
    /* 7.3.7.2.4 HardwareIDRequest:
    ______________________________________________________________________________________
        |Field              Length (bits)      |
        |------------       -------------------|
        |MessageID              8              |
        |TransactionID          8              |
        ______________________________________________________________________________________
    */

    CNAS_HSM_HARDWARE_ID_REQ_MSG        stHareWareIdReq;

    NAS_MEM_SET_S(&stHareWareIdReq, sizeof(stHareWareIdReq), 0x00, sizeof(CNAS_HSM_HARDWARE_ID_REQ_MSG));

    /* invalid message length */
    if (CNAS_HSM_HARDWARE_ID_REQ_MSG_BIT_LEN > usInMsgBitLen)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_DECODE_RESULT_IND, CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN);

        return CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN;
    }

    stHareWareIdReq.ucTransactionId  = *(pucInData + 1);

    NAS_MEM_CPY_S(pucOutHardWareIdReq, sizeof(CNAS_HSM_HARDWARE_ID_REQ_MSG), &stHareWareIdReq, sizeof(CNAS_HSM_HARDWARE_ID_REQ_MSG));

    CNAS_HSM_LogHardWareIdReqMsg(&stHareWareIdReq);
    return CNAS_HSM_DECODE_SUCCESS;
}


CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeUATIAssignment(
    VOS_UINT8                          *pucInData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstOutUatiAssign
)
{
    /* 7.3.7.2.2 UATIAssignment;
    ______________________________________________________________________________________
        |Field              Length (bits)            |
        |------------       -------------------------|
        |MessageID                8                  |
        |MessageSequence          8                  |
        |Reserved1                7                  |
        |SubnetIncluded           1                  |
        |UATISubnetMask        0 or 8                |
        |UATI104              0 or 104               |
        |UATIColorCode            8                  |
        |UATI024                 24                  |
        |UpperOldUATILength      4                   |
        |Reserved2               4                   |
    ______________________________________________________________________________________
    */

    CNAS_HSM_UATI_ASSIGN_MSG_STRU                           stUatiAssign;
    VOS_UINT8                                               ucSubnetIncluded;


    /* invalid message length */
    if ((CNAS_HSM_UATI_ASSIGN_WITHOUT_SUBNET_MSG_BIT_LEN != usInMsgBitLen)
     && (CNAS_HSM_UATI_ASSIGN_WITH_SUBNET_MSG_BIT_LEN    != usInMsgBitLen))
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_DECODE_RESULT_IND, CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN);

        return CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN;
    }

    NAS_MEM_SET_S(&stUatiAssign, sizeof(stUatiAssign), 0, sizeof(CNAS_HSM_UATI_ASSIGN_MSG_STRU));

    /* fill the uati assign subitem value */
    stUatiAssign.ucMsgSeq               = *(pucInData + 1);

    ucSubnetIncluded                    = *(pucInData + 2);

    stUatiAssign.ucSubnetIncluded       = ucSubnetIncluded;

    /* Check if SubnetIncluded flag is set */
    if (0x0 == (ucSubnetIncluded & 0x01))
    {
        /* Subnet and UATI104 fields not included */
        stUatiAssign.ucUATIColorCode           = *(pucInData + 3);

        NAS_MEM_CPY_S(&(stUatiAssign.aucUati024[0]), sizeof(stUatiAssign.aucUati024), pucInData + 4, CNAS_HSM_UATI024_OCTET_LENGTH);

        /* only get high 4 bits here */
        stUatiAssign.ucOldUATILen              = ((*(pucInData + 7) & 0xf0) >> 4);
    }
    else
    {
        /* Subnet and UATI104 fields included */
        stUatiAssign.ucUATISubnetMask          = *(pucInData + 3);

        NAS_MEM_CPY_S((stUatiAssign.aucUati104), sizeof(stUatiAssign.aucUati104), (pucInData + 4), CNAS_HSM_UATI104_OCTET_LENGTH); /* need to discuss abt NTOH */

        stUatiAssign.ucUATIColorCode           = *(pucInData + 17);

        NAS_MEM_CPY_S(&(stUatiAssign.aucUati024[0]), sizeof(stUatiAssign.aucUati024), pucInData + 18, CNAS_HSM_UATI024_OCTET_LENGTH);

        /* only get high 4 bits here */
        stUatiAssign.ucOldUATILen              = ((*(pucInData + 21) & 0xf0) >> 4);
    }

    NAS_MEM_CPY_S(pstOutUatiAssign, sizeof(CNAS_HSM_UATI_ASSIGN_MSG_STRU), &stUatiAssign, sizeof(CNAS_HSM_UATI_ASSIGN_MSG_STRU));

    return CNAS_HSM_DECODE_SUCCESS;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_DecodeSessionClose
Description     :   Decode SessionClose message sent by AN
Input parameters:   *pucInData          - ptr to SessionClose message sent by CTTF
Output parameters:  *pstOutSessionClose - ptr to SessionClose structure with decoded fields of CTTF message
Return Value    :   CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32

Modify History  :
1)  Date           : 2015-02-04
    Author         : s00250401
    Modify content : Create
2)  Date           : 2015-05-29
    Author         : s00250401
    Modify content : Iteration 12 - Added decode for all CloseEeason(0x03 and 0x04)
3.  日    期   : 2015年08月26日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/
 CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeSessionClose(
    VOS_UINT8                          *pucInData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_SESSION_CLOSE_MSG_STRU    *pstOutSessionClose
)
{
     /* C.S0024-A_v3: 7.2.6.2.1 SessionClose
     ______________________________________________________________________________________
         |Field              Length (bits)          |
         |------------       -----------------------|
         |MessageID              8                  |
         |CloseReason            8                  |
         |MoreInfoLen            8                  |
         |MoreInfo           8 × MoreInfoLen       |
    ______________________________________________________________________________________
     */


    CNAS_HSM_SESSION_CLOSE_MSG_STRU                          stSessionClose;
    VOS_UINT16                                               usType;
    VOS_UINT16                                               usSubType;

    usSubType = 0;

    NAS_MEM_SET_S(&stSessionClose, sizeof(stSessionClose), 0x0, sizeof(CNAS_HSM_SESSION_CLOSE_MSG_STRU));

    /* invalid message bit length */
    if (CNAS_HSM_SESSION_CLOSE_MSG_WITHOUT_MOREINFO_BIT_LEN > usInMsgBitLen)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_DECODE_RESULT_IND, CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN);

        return CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN;
    }

    stSessionClose.enCloseReason       = *(pucInData + 1);
    stSessionClose.ucMoreInfoLen       = *(pucInData + 2);

    if ((CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL == stSessionClose.enCloseReason)
     || (CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_NEG_ERR == stSessionClose.enCloseReason))
    {
        /* C.S0024-A_v3: 7.2.6.2.1.1 MoreInfo record :
          ______________________________________________________________________________________
              |Field              Length (bits)          |
              |------------       -----------------------|
              |TypeLen                1                  |
              |Type                 7 or 15              |
              |SubType                16                 |
          ______________________________________________________________________________________
          */
        if (0 == ((*(pucInData + 3)) & 0x80) >> 7)
        {
            /* If TypeLen = 0, read Type as 7 bits*/
            stSessionClose.usType = (*(pucInData + 3)) & 0x7F;

            /* if TypeLen = 0, 消息最小长度为6字节, 否则解码失败 */
            if (stSessionClose.ucMoreInfoLen >= CNAS_HSM_SESSION_CLOSE_MSG_MOREINFOLEN_WITH_7BIT_TYPE)
            {
                NAS_MEM_CPY_S(&usSubType, sizeof(VOS_UINT16), (pucInData + 4), sizeof(VOS_UINT16));

                /* convert to little endian */
                stSessionClose.usSubType = CNAS_NTOHS(usSubType);
            }
            else
            {
                CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_DecodeSessionClose: TypeLen=0, Msg Len is not enough to Decode!");
            }
        }
        else
        {
            /* if TypeLen = 1, 消息最小长度为7字节, 否则解码失败 */
            if (stSessionClose.ucMoreInfoLen >= CNAS_HSM_SESSION_CLOSE_MSG_MOREINFOLEN_WITH_15BIT_TYPE)
            {
                /* If Typelen = 1, read Type as 15 bits */
                usType = *(pucInData + 3);
                usType = (VOS_UINT16)((usType << 8) | (*(pucInData + 4)));
                usType = 0x7FFF & usType; /* Remove TypeLen field */

                NAS_MEM_CPY_S(&usSubType, sizeof(VOS_UINT16), (pucInData + 5), sizeof(VOS_UINT16));

                stSessionClose.usType = usType;

                /* convert to little endian */
                stSessionClose.usSubType = CNAS_NTOHS(usSubType);
            }
            else
            {
                CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_DecodeSessionClose: TypeLen=1, Msg Len is not enough to Decode!");
            }
        }
    }
    /* Decode and store offending attributes fields for CloseReason = 0x04 is not implemented as we do not use
        offending attribute records info */


    NAS_MEM_CPY_S(pstOutSessionClose, sizeof(CNAS_HSM_SESSION_CLOSE_MSG_STRU), &stSessionClose, sizeof(CNAS_HSM_SESSION_CLOSE_MSG_STRU));

    CNAS_HSM_LogSessionCloseMsg(&stSessionClose);
    return CNAS_HSM_DECODE_SUCCESS;
}



CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeKeepAliveReq(
    VOS_UINT8                          *pucInData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU   *pstOutBuff
)
{
    /* C.S0024-A_v3.0_060912: 7.2.6.2.2 KeepAliveRequest
         _______________________________________
        |Field           |   Length (bits)      |
        |----------------|----------------------|
        |MessageID       |       8              |
        |TransactionID   |       8              |
        |________________|______________________|
    */

    CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU                        stKeepAliveReq;

    /* Check for invalid message bit length */
    if (usInMsgBitLen < CNAS_HSM_KEEP_ALIVE_REQ_MSG_BIT_LEN)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_DECODE_RESULT_IND,
                                   CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN);

        return CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN;
    }

    pstOutBuff->ucTransId = *(pucInData + 1);

    stKeepAliveReq.ucTransId   = pstOutBuff->ucTransId;
    stKeepAliveReq.aucRsrvd[0] = 0;
    stKeepAliveReq.aucRsrvd[1] = 0;
    stKeepAliveReq.aucRsrvd[2] = 0;

    CNAS_HSM_LogKeepAliveReq(&stKeepAliveReq);

    return CNAS_HSM_DECODE_SUCCESS;
}


CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32 CNAS_HSM_DecodeKeepAliveResp(
    VOS_UINT8                          *pucInData,
    VOS_UINT16                          usInMsgBitLen,
    CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU  *pstOutBuff
)
{
    /*
       C.S0024-A_v3.0_060912.pdf : 7.2.6.2.3 KeepAliveResponse
         _______________________________________
        |Field           |   Length (bits)      |
        |----------------|----------------------|
        |MessageID       |       8              |
        |TransactionID   |       8              |
        |________________|______________________|
    */

    CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU                       stKeepAliveResp;

    /* Check for invalid message bit length */
    if (usInMsgBitLen < CNAS_HSM_KEEP_ALIVE_RESP_MSG_BIT_LEN)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_DECODE_RESULT_IND,
                                   CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN);

        return CNAS_HSM_DECODE_ERROR_TYPE_INVALID_MSG_LEN;
    }

    pstOutBuff->ucTransId = *(pucInData + 1);

    stKeepAliveResp.ucTransId   = pstOutBuff->ucTransId;
    stKeepAliveResp.aucRsrvd[0] = 0;
    stKeepAliveResp.aucRsrvd[1] = 0;
    stKeepAliveResp.aucRsrvd[2] = 0;

    CNAS_HSM_LogKeepAliveResp(&stKeepAliveResp);

    return CNAS_HSM_DECODE_SUCCESS;
}




#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





