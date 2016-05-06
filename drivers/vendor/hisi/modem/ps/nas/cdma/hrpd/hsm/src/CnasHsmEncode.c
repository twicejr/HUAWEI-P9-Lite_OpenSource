

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmEncode.h"
#include "PsCommonDef.h"
#include "CnasHsmMntn.h"
#include "CnasHsmComFunc.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_ENCODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/

VOS_VOID CNAS_HSM_EncodeUATIReq(
    VOS_VOID                           *pInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
)
{
    /* C.S0024-A_v3: 7.3.7.2.1 UATIRequest:
    ______________________________________________________________________________________
        |Field              Length (bits)      |
        |------------       -------------------|
        |MessageID              8              |
        |TransactionID          8              |
        ______________________________________________________________________________________
    */
    CNAS_HSM_UATI_REQ_MSG_STRU          stUatiReq;

    *(pstOutBuff)        = CNAS_HSM_AMP_MSG_TYPE_UATI_REQ;

    stUatiReq.ucTransactionId      = *((VOS_UINT8 *)pInMsgData);
    *(pstOutBuff + 1)              = stUatiReq.ucTransactionId;

    *pusOutBitLen                  = CNAS_HSM_UATI_REQ_MSG_BIT_LEN;

    CNAS_HSM_LogUatiReqMsg(&stUatiReq);
}

/*****************************************************************************
Function Name   :   CNAS_HSM_EncodeUATIComplete
Description     :   Encode UATIComplete message
Input parameters:   pInMsgData          - ptr to CNAS_HSM_UATI_COMP_MSG_STRU
Output parameters:  *pusOutBitLen       - ptr to output message bit length
                    pstOutBuff          - ptr to output UATIComplete message
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-02-04
    Author         : s00250401
    Modify content : Create
2)  Date           : 2015-06-30
    Author         : m00312079
    Modify content : 修改Upper OLD UATI的字节序
3)  Date           : 2015-09-23
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): 对和协议实现不一致的代码注释说明
*****************************************************************************/
VOS_VOID CNAS_HSM_EncodeUATIComplete(
    VOS_VOID                           *pInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
)
{
    /* 7.3.7.2.3 UATIComplete:
    ______________________________________________________________________________________
        |Field              Length (bits)            |
        |------------       -------------------------|
        |MessageID                8                  |
        |MessageSequence          8                  |
        |Reserved                 4                  |
        |UpperOldUATILength       4                  |
        |UpperOldUATI        8 × UpperOldUATILength |
        ______________________________________________________________________________________
    */
    CNAS_HSM_UATI_COMP_MSG_STRU                            *pstUatiCmp;
    VOS_UINT8                                               ucOldUATILen;


    pstUatiCmp             = (CNAS_HSM_UATI_COMP_MSG_STRU *)pInMsgData;

    ucOldUATILen           = pstUatiCmp->ucOldUATILen;

    if (ucOldUATILen > CNAS_HSM_MAX_UPPER_OLD_UATI_OCTETS)
    {
        ucOldUATILen = CNAS_HSM_MAX_UPPER_OLD_UATI_OCTETS;
    }

    NAS_MEM_SET_S(pstOutBuff, (3 + ucOldUATILen), 0x0, (3 + ucOldUATILen));

    *(pstOutBuff)         = CNAS_HSM_AMP_MSG_TYPE_UATI_COMPLETE;
    *(pstOutBuff + 1)     = pstUatiCmp->ucMsgSeq;

    /* only assign 4 bit for upper old UATI length,this include the reserved bit */
    *(pstOutBuff + 2)     = ucOldUATILen;

    /* 按照协议如果OldUATI不存在不需要编码OldUATI信息, 但是影响CCF C.S0038 5.2.2.4用例通过,
       参考标杆实现, 只要网络请求OldUATI就进行OldUATI编码 */
    /* UpperOldUATI---If UpperOldUATILength  in the UATIAssignment message whose
       receipt this message is acknowledging is not zero and OldUATI is not
       NULL, the access terminal shall set this field to OldUATI[23+UpperOldUATILength×8:24].
       Otherwise, the access terminal shall omit this field. */
    if (0 != ucOldUATILen)
    {
        NAS_MEM_CPY_S((pstOutBuff + 3),
                      ucOldUATILen,
                      ((pstUatiCmp->aucOldUATI) + CNAS_HSM_MAX_UPPER_OLD_UATI_OCTETS - ucOldUATILen),
                      ucOldUATILen);
    }

   *pusOutBitLen = CNAS_HSM_GET_UATI_COMPLETE_MSG_BIT_LEN(ucOldUATILen);

    /* 为了LOG打印清晰 */
    NAS_MEM_SET_S(pstUatiCmp->aucOldUATI,
                  sizeof(pstUatiCmp->aucOldUATI),
                  0x00,
                  CNAS_HSM_UATI_OCTET_LENGTH);

    NAS_MEM_CPY_S(pstUatiCmp->aucOldUATI, sizeof(pstUatiCmp->aucOldUATI), pstOutBuff + 3, ucOldUATILen);

    CNAS_HSM_LogUatiCompMsg(pstUatiCmp);
}


VOS_UINT8 CNAS_HSM_GetHardwareIdLength(
    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                 *pstHwIdRspMsg
)
{
    VOS_UINT8                           ucHardwareIdLen;

    if (CNAS_HSM_HARDWARE_ID_TYPE_MEID == pstHwIdRspMsg->enHwidType)
    {
        ucHardwareIdLen                 = CNAS_HSM_MEID_OCTET_NUM;
    }
    else if (CNAS_HSM_HARDWARE_ID_TYPE_ESN == pstHwIdRspMsg->enHwidType)
    {
        ucHardwareIdLen                 = CNAS_HSM_ESN_OCTET_NUM;
    }
    else
    {
        ucHardwareIdLen                 = 0;
    }

    return ucHardwareIdLen;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_EncodeHwIdResponse
Description     :   Encode HardwareIDResponse message
Input parameters:   pInMsgData          - ptr to CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU
Output parameters:  *pusOutBitLen       - ptr to output message bit length
                    pstOutBuff          - ptr to output HardwareIdResponse message
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-02-04
    Author         : s00250401
    Modify content : Create
2)  Date           : 2015-12-04
    Author         : y00307564
    Modify content : 根据大小端，修改hardware rsp消息中esn/meid的字节序
*****************************************************************************/
VOS_VOID CNAS_HSM_EncodeHardwareIdResponse(
    VOS_VOID                           *pInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
)
{
    /* 7.3.7.2.5 HardwareIDResponse:
    ______________________________________________________________________________________
        |Field              Length (bits)          |
        |------------       -----------------------|
        |MessageID              8                  |
        |TransactionID          8                  |
        |HardwareIDType         24                 |
        |HardwareIDLength       8                  |
        |HardwareIDValue        8×HardwareIDLength|
   ______________________________________________________________________________________
    */

    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                 *pstHardwareIdInfo;
    VOS_UINT8                                               ucHardwareIdLen;
    VOS_UINT8                                              *pucHwIdInfo;
    VOS_UINT32                                              ulHardWareIdType;
    VOS_UINT32                                              ulEsn;
    VOS_UINT8                                               aucMeId[CNAS_HSM_MEID_OCTET_NUM];
    VOS_UINT32                                              i;


    pstHardwareIdInfo  = (CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU *)pInMsgData;
    ucHardwareIdLen    = CNAS_HSM_GetHardwareIdLength(pstHardwareIdInfo);

    if (CNAS_HSM_HARDWARE_ID_TYPE_MEID == pstHardwareIdInfo->enHwidType)
    {
        /* Modified by y00307564 for DTS2015120209882 2015-12-3 begin
           此时该空口消息中HardwareIDValue携带的是meid，其中meid[0]存储的是最高位，
           meid[6]存储的是最低位，pInMsgData携带的meid[0]存储的是最低位， meid[6]
           存储的是最高位，所以需要转换meid的顺序 */
        for (i = 0; i < CNAS_HSM_MEID_OCTET_NUM; i++)
        {
            aucMeId[CNAS_HSM_MEID_OCTET_NUM - i - 1] = pstHardwareIdInfo->aucMeId[i];
        }

        pucHwIdInfo = aucMeId;
    }
    else if (CNAS_HSM_HARDWARE_ID_TYPE_ESN == pstHardwareIdInfo->enHwidType)
    {
        /* Modified by y00307564 for DTS2015120209882 2015-12-3 begin
           此时该空口消息中HardwareIDValue携带的是esn，其中esn[0]存储的是最高位，
           esn[3]存储的是最低位，若目前存储的字节序是按小端模式存储，pInMsgData携带的
           esn[0]存储的是最低位， esn[3]存储的是最高位，所以需要转换esn的顺序 */
        ulEsn       = CNAS_HTONL(pstHardwareIdInfo->ulEsn);
        pucHwIdInfo = (VOS_UINT8 *)(&(ulEsn));
    }
    else
    {
        pucHwIdInfo                     = VOS_NULL_PTR;
    }

    *(pstOutBuff)          = CNAS_HSM_AMP_MSG_TYPE_HARDWAREID_RESP;
    *(pstOutBuff + 1)      = pstHardwareIdInfo->ucTransactionId;

    /*transfor to big endian*/
    ulHardWareIdType = CNAS_HTONL(pstHardwareIdInfo->enHwidType);

    /* the Hardware ID type occupy 3 bytes */
    NAS_MEM_CPY_S((pstOutBuff + 2), CNAS_HSM_HARDWARE_ID_TYPE_OCTET_LENGTH, ((VOS_UINT8 *)&ulHardWareIdType) + 1, CNAS_HSM_HARDWARE_ID_TYPE_OCTET_LENGTH);

    *(pstOutBuff + 5)  = ucHardwareIdLen;

    if ((VOS_NULL_PTR != pucHwIdInfo)
     && (0            != ucHardwareIdLen))
    {
        NAS_MEM_CPY_S((pstOutBuff + 6), ucHardwareIdLen, pucHwIdInfo, ucHardwareIdLen);
    }

    *pusOutBitLen = CNAS_HSM_GET_HARDWARE_ID_RESPONSE_MSG_BIT_LEN(ucHardwareIdLen);

    CNAS_HSM_LogHardWareIdRespMsg(pstHardwareIdInfo);
}


VOS_UINT16 CNAS_HSM_GetSessionCloseMsgEncodedBufLen(
    CNAS_HSM_SESSION_CLOSE_MSG_STRU     *pstSessionCloseInput
)
{
    VOS_UINT8                            ucMoreInfoLen;

    if((CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL == pstSessionCloseInput->enCloseReason)
     || (CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_NEG_ERR == pstSessionCloseInput->enCloseReason))
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

        if(CNAS_HSM_SESSION_CLOSE_MSG_MAX_VALUE_STORED_IN_7BIT_VAR >= pstSessionCloseInput->usType)
        {
            /* 7 bit Type */
            ucMoreInfoLen = CNAS_HSM_SESSION_CLOSE_MSG_MOREINFOLEN_WITH_7BIT_TYPE;
        }
        else
        {
            /* 15 bit Type */
            ucMoreInfoLen = CNAS_HSM_SESSION_CLOSE_MSG_MOREINFOLEN_WITH_15BIT_TYPE;
        }
    }
    else
    {
        ucMoreInfoLen = 0;
    }

    return (VOS_UINT16)CNAS_HSM_GET_SESSION_CLOSE_MSG_OCTET_LEN(ucMoreInfoLen);
}


VOS_VOID CNAS_HSM_EncodeSessionClose(
    VOS_VOID                           *pInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
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

    CNAS_HSM_SESSION_CLOSE_MSG_STRU                        *pstSessionCloseInput;
    VOS_UINT16                                              usSubType;

    pstSessionCloseInput    = (CNAS_HSM_SESSION_CLOSE_MSG_STRU *)pInMsgData;

    *(pstOutBuff)          = CNAS_HSM_SMP_MESSAGE_TYPE_SESSION_CLOSE;

    if ((CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL == pstSessionCloseInput->enCloseReason)
     || (CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_NEG_ERR == pstSessionCloseInput->enCloseReason))
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

        /* In current implementation we send both message as CNAS_HSM_CLOSE_REASON_TYPE_PROT_CONF_FAIL */
        *(pstOutBuff + 1)      = CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL;

        if (CNAS_HSM_SESSION_CLOSE_MSG_MAX_VALUE_STORED_IN_7BIT_VAR >= pstSessionCloseInput->usType)
        {
            /* Set 7 bit Type */
            *(pstOutBuff + 2)  = CNAS_HSM_SESSION_CLOSE_MSG_MOREINFOLEN_WITH_7BIT_TYPE;
            *(pstOutBuff + 3)  = (0x00FF & (pstSessionCloseInput->usType)); /* Set TypeLen to 0 */

            /* convert to big endian */
            usSubType = CNAS_HTONS(pstSessionCloseInput->usSubType);
            NAS_MEM_CPY_S((pstOutBuff + 4), sizeof(VOS_UINT16), &usSubType, sizeof(VOS_UINT16));
        }
        else
        {
            /* Set 15 bit Type */
            *(pstOutBuff + 2)  = CNAS_HSM_SESSION_CLOSE_MSG_MOREINFOLEN_WITH_15BIT_TYPE;
            *(pstOutBuff + 3)  = (VOS_UINT8)(((0xFF00 & (pstSessionCloseInput->usType)) >> 8)| 0x80); /* Set TypeLen to 1 */
            *(pstOutBuff + 4)  = (0x00FF & (pstSessionCloseInput->usType));

            /* convert to big endian */
            usSubType = CNAS_HTONS(pstSessionCloseInput->usSubType);
            NAS_MEM_CPY_S((pstOutBuff + 5), sizeof(VOS_UINT16), &usSubType, sizeof(VOS_UINT16));
        }
    }
    else
    {
        *(pstOutBuff + 1)      = pstSessionCloseInput->enCloseReason;
        *(pstOutBuff + 2)      = 0;
    }

    *pusOutBitLen          = CNAS_HSM_GET_SESSION_CLOSE_MSG_BIT_LEN(*(pstOutBuff + 2));

    CNAS_HSM_LogSessionCloseMsg(pstSessionCloseInput);

}


VOS_VOID CNAS_HSM_EncodeKeepAliveReq(
    VOS_VOID                           *pucInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
)
{
    /* C.S0024-A_v3.0_060912.pdf : 7.2.6.2.2 KeepAliveRequest
         _______________________________________
        |Field           |   Length (bits)      |
        |----------------|----------------------|
        |MessageID       |       8              |
        |TransactionID   |       8              |
        |________________|______________________|

    */

    CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU    stKeepAliveReq;

    *(pstOutBuff + 0) = CNAS_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_REQ;
    *(pstOutBuff + 1) = *((VOS_UINT8 *)pucInMsgData);

    *pusOutBitLen = CNAS_HSM_KEEP_ALIVE_REQ_MSG_BIT_LEN;

    stKeepAliveReq.ucTransId   = *((VOS_UINT8 *)pucInMsgData);
    stKeepAliveReq.aucRsrvd[0] = 0;
    stKeepAliveReq.aucRsrvd[1] = 0;
    stKeepAliveReq.aucRsrvd[2] = 0;

    CNAS_HSM_LogKeepAliveReq(&stKeepAliveReq);

    return;
}




VOS_VOID CNAS_HSM_EncodeKeepAliveResp(
    VOS_VOID                           *pucInMsgData,
    VOS_UINT16                         *pusOutBitLen,
    VOS_UINT8                          *pstOutBuff
)
{
    /* C.S0024-A_v3.0_060912.pdf : 7.2.6.2.3 KeepAliveResponse
         _______________________________________
        |Field           |   Length (bits)      |
        |----------------|----------------------|
        |MessageID       |       8              |
        |TransactionID   |       8              |
        |________________|______________________|

    */

    CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU   stKeepAliveResp;

    *(pstOutBuff + 0) = CNAS_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_RESP;
    *(pstOutBuff + 1) = *((VOS_UINT8 *)pucInMsgData);

    *pusOutBitLen = CNAS_HSM_KEEP_ALIVE_RESP_MSG_BIT_LEN;

    stKeepAliveResp.ucTransId   = *((VOS_UINT8 *)pucInMsgData);
    stKeepAliveResp.aucRsrvd[0] = 0;
    stKeepAliveResp.aucRsrvd[1] = 0;
    stKeepAliveResp.aucRsrvd[2] = 0;

    CNAS_HSM_LogKeepAliveResp(&stKeepAliveResp);

    return;
}




#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */






