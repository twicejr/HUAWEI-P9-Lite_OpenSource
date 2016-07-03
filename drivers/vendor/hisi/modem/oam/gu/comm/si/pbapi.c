


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif


#include "TafTypeDef.h"
#include "si_pb.h"
#include "product_config.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define      THIS_FILE_ID     PS_FILE_ID_PBAPI_C
/*lint +e767*/

#if ((OSA_CPU_ACPU == VOS_OSA_CPU) || (defined(DMT)))


VOS_UINT32 SI_PB_GetReceiverPid(MN_CLIENT_ID_T  ClientId, VOS_UINT32 *pulReceiverPid)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    MODEM_ID_ENUM_UINT16    enModemID;

    /* 调用接口获取Modem ID */
    if(VOS_OK != AT_GetModemIdFromClient(ClientId,&enModemID))
    {
        return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        *pulReceiverPid = I1_MAPS_PB_PID;
    }
#if (MULTI_MODEM_NUMBER == 3)
    else if (MODEM_ID_2 == enModemID)
    {
        *pulReceiverPid = I2_MAPS_PB_PID;
    }
#endif /* MULTI_MODEM_NUMBER == 3 */
    else
    {
        *pulReceiverPid = I0_MAPS_PB_PID;
    }
#else
    *pulReceiverPid = MAPS_PB_PID;
#endif

    return VOS_OK;
}


SI_UINT32 SI_PB_Read(  MN_CLIENT_ID_T           ClientId,
                            MN_OPERATION_ID_T        OpId,
                            SI_PB_STORATE_TYPE       Storage,
                            SI_UINT16                Index1,
                            SI_UINT16                Index2)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    SI_PB_READ_REQ_STRU     *pMsg;

    pMsg = (SI_PB_READ_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_READ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Read:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

#if (VOS_WIN32 == VOS_OS_VER)
    pMsg->ulReceiverPid = MAPS_PB_PID;
#else
    pMsg->ulReceiverPid = ACPU_PID_PB;
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/

    pMsg->ulMsgName     = SI_PB_READ_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->usIndex1      = Index1;
    pMsg->usIndex2      = Index2;

    if(SI_PB_STORAGE_UNSPECIFIED == Storage)
    {
        pMsg->ulStorage = gstPBCtrlInfo.enPBCurType;
    }
    else
    {
        pMsg->ulStorage = Storage;
    }

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Read:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
#endif
}


SI_UINT32 SI_PB_SRead(  MN_CLIENT_ID_T           ClientId,
                            MN_OPERATION_ID_T        OpId,
                            SI_PB_STORATE_TYPE       Storage,
                            SI_UINT16                Index1,
                            SI_UINT16                Index2)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    SI_PB_READ_REQ_STRU     *pMsg;

    pMsg = (SI_PB_READ_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_READ_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Read:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

#if (VOS_WIN32 == VOS_OS_VER)
    pMsg->ulReceiverPid = MAPS_PB_PID;
#else
    pMsg->ulReceiverPid = ACPU_PID_PB;
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/

    pMsg->ulMsgName     = SI_PB_SREAD_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->usIndex1      = Index1;
    pMsg->usIndex2      = Index2;

    if(SI_PB_STORAGE_UNSPECIFIED == Storage)
    {
        pMsg->ulStorage = gstPBCtrlInfo.enPBCurType;
    }
    else
    {
        pMsg->ulStorage = Storage;
    }

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Read:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
#endif
}


SI_UINT32 SI_PB_Query(     MN_CLIENT_ID_T           ClientId,
                                MN_OPERATION_ID_T        OpId)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    SI_PB_QUERY_REQ_STRU    *pMsg;

    pMsg = (SI_PB_QUERY_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_QUERY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Query:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = MAPS_PB_PID;
    pMsg->ulMsgName     = SI_PB_QUERY_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->ulStorage     = gstPBCtrlInfo.enPBCurType;

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Query:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
#endif
}


SI_UINT32 SI_PB_Set(    MN_CLIENT_ID_T           ClientId,
                            MN_OPERATION_ID_T        OpId,
                            SI_PB_STORATE_TYPE      Storage)
{
    SI_PB_SET_REQ_STRU  *pMsg;
    VOS_UINT32          ulReceiverPid;

#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    if(SI_PB_STORAGE_FD != Storage)
    {
        PB_ERROR_LOG("SI_PB_Set:Double Modem only support the FDN");

        return TAF_FAILURE;
    }
#endif

    if (VOS_OK != SI_PB_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PB_ERROR_LOG("SI_PB_Set:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    pMsg = (SI_PB_SET_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Set:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->ulMsgName     = SI_PB_SET_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->ulStorage     = Storage;

    if(VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Set:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


SI_UINT32 SI_PB_Add(    MN_CLIENT_ID_T          ClientId,
                            MN_OPERATION_ID_T        OpId,
                             SI_PB_STORATE_TYPE      Storage,
                             SI_PB_RECORD_STRU       *pRecord)
{
    SI_PB_ADD_REP_STRU  *pMsg;
    VOS_UINT32          ulReceiverPid;

    if (VOS_OK != SI_PB_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PB_ERROR_LOG("SI_PB_Add:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    if(VOS_NULL_PTR == pRecord)
    {
        PB_ERROR_LOG("SI_PB_Add:pRecord is a NULL pointer");

        return TAF_FAILURE;
    }

    pMsg = (SI_PB_ADD_REP_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_ADD_REP_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Add:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->ulMsgName     = SI_PB_ADD_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;

#if( FEATURE_MULTI_MODEM == FEATURE_ON )
    pMsg->ulStorage = SI_PB_STORAGE_FD;     /*只能够操作FDN号码*/
#else
    if(SI_PB_STORAGE_UNSPECIFIED == Storage)
    {
        pMsg->ulStorage = gstPBCtrlInfo.enPBCurType;
    }
    else
    {
        pMsg->ulStorage = Storage;
    }
#endif

    pRecord->Index = 1;

    /*lint -e534*/
    VOS_MemCpy(&pMsg->stRecord, pRecord, sizeof(SI_PB_RECORD_STRU));
    /*lint +e534*/

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Add:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

SI_UINT32 SI_PB_SAdd(    MN_CLIENT_ID_T          ClientId,
                            MN_OPERATION_ID_T        OpId,
                             SI_PB_STORATE_TYPE      Storage,
                             SI_PB_RECORD_STRU       *pRecord)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    SI_PB_ADD_REP_STRU  *pMsg;

    if(VOS_NULL_PTR == pRecord)
    {
        PB_ERROR_LOG("SI_PB_Add:pRecord is a NULL pointer");

        return TAF_FAILURE;
    }

    pMsg = (SI_PB_ADD_REP_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_ADD_REP_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Add:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = MAPS_PB_PID;
    pMsg->ulMsgName     = SI_PB_SADD_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;

    if(SI_PB_STORAGE_UNSPECIFIED == Storage)
    {
        pMsg->ulStorage = gstPBCtrlInfo.enPBCurType;
    }
    else
    {
        pMsg->ulStorage = Storage;
    }

    pRecord->Index = 1;

    /*lint -e534*/
    VOS_MemCpy(&pMsg->stRecord, pRecord, sizeof(SI_PB_RECORD_STRU));
    /*lint +e534*/

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Add:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
#endif
}


SI_UINT32 SI_PB_Modify(    MN_CLIENT_ID_T          ClientId,
                                MN_OPERATION_ID_T       OpId,
                                SI_PB_STORATE_TYPE      Storage,
                                SI_PB_RECORD_STRU       *pRecord )
{
    SI_PB_MODIFY_REP_STRU  *pMsg;
    VOS_UINT32              ulReceiverPid;

    if (VOS_OK != SI_PB_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PB_ERROR_LOG("SI_PB_Modify:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    if(VOS_NULL_PTR == pRecord)
    {
        PB_ERROR_LOG("SI_PB_Modify:pRecord is a NULL pointer");

        return TAF_FAILURE;
    }

    pMsg = (SI_PB_MODIFY_REP_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_MODIFY_REP_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Modify:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->ulMsgName     = SI_PB_MODIFY_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;

#if( FEATURE_MULTI_MODEM == FEATURE_ON )
    pMsg->ulStorage = SI_PB_STORAGE_FD;     /*只能够操作FDN号码*/
#else
    if(SI_PB_STORAGE_UNSPECIFIED == Storage)
    {
        pMsg->ulStorage = gstPBCtrlInfo.enPBCurType;
    }
    else
    {
        pMsg->ulStorage = Storage;
    }
#endif

    /*lint -e534*/
    VOS_MemCpy(&pMsg->Record, pRecord, sizeof(SI_PB_RECORD_STRU));
    /*lint +e534*/

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Modify:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


SI_UINT32 SI_PB_SModify(    MN_CLIENT_ID_T          ClientId,
                                MN_OPERATION_ID_T       OpId,
                                SI_PB_STORATE_TYPE      Storage,
                                SI_PB_RECORD_STRU       *pRecord )
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    SI_PB_MODIFY_REP_STRU  *pMsg;

    if(VOS_NULL_PTR == pRecord)
    {
        PB_ERROR_LOG("SI_PB_Modify:pRecord is a NULL pointer");

        return TAF_FAILURE;
    }

    pMsg = (SI_PB_MODIFY_REP_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_MODIFY_REP_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Modify:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = MAPS_PB_PID;
    pMsg->ulMsgName     = SI_PB_SMODIFY_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;

    if(SI_PB_STORAGE_UNSPECIFIED == Storage)
    {
        pMsg->ulStorage = gstPBCtrlInfo.enPBCurType;
    }
    else
    {
        pMsg->ulStorage = Storage;
    }

    /*lint -e534*/
    VOS_MemCpy(&pMsg->Record, pRecord, sizeof(SI_PB_RECORD_STRU));
    /*lint +e534*/

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Modify:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
#endif
}


SI_UINT32 SI_PB_Delete(     MN_CLIENT_ID_T             ClientId,
                                MN_OPERATION_ID_T           OpId,
                                SI_PB_STORATE_TYPE          Storage,
                                SI_UINT16                   Index)
{
    SI_PB_DELETE_REQ_STRU  *pMsg;
    VOS_UINT32              ulReceiverPid;

    if (VOS_OK != SI_PB_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PB_ERROR_LOG("SI_PB_Modify:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    pMsg = (SI_PB_DELETE_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_DELETE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Delete:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->ulMsgName     = SI_PB_DELETE_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->usIndex       = Index;

#if( FEATURE_MULTI_MODEM == FEATURE_ON )
    pMsg->ulStorage = SI_PB_STORAGE_FD;     /*只能够操作FDN号码*/
#else
    if(SI_PB_STORAGE_UNSPECIFIED == Storage)
    {
        pMsg->ulStorage = gstPBCtrlInfo.enPBCurType;
    }
    else
    {
        pMsg->ulStorage = Storage;
    }
#endif

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Delete:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


SI_UINT32 SI_PB_Search(    MN_CLIENT_ID_T             ClientId,
                                MN_OPERATION_ID_T           OpId,
                                SI_PB_STORATE_TYPE          Storage,
                                SI_UINT8                    ucLength,
                                SI_UINT8                    *pucContent)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    SI_PB_SEARCH_REQ_STRU  *pMsg;

    pMsg = (SI_PB_SEARCH_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Search:VOS_AllocMsg Failed");
        return TAF_FAILURE;
    }

#if (VOS_WIN32 == VOS_OS_VER)
    pMsg->ulReceiverPid = MAPS_PB_PID;
#else
    pMsg->ulReceiverPid = ACPU_PID_PB;
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/

    pMsg->ulMsgName     = SI_PB_SEARCH_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->ucLength      = ucLength;

    pMsg->ulStorage = ((Storage == SI_PB_STORAGE_UNSPECIFIED)?(gstPBCtrlInfo.enPBCurType):(Storage));

    /*lint -e534*/
    VOS_MemCpy(pMsg->aucContent, pucContent, ucLength);
    /*lint +e534*/

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Search:VOS_SendMsg Failed");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
#endif
}


VOS_UINT32 SI_PB_GetStorateType(VOS_VOID)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return SI_PB_STORAGE_UNSPECIFIED;   /*返回当前未指定*/
#else
    return (VOS_UINT32)gstPBCtrlInfo.enPBCurType;
#endif
}


VOS_UINT32 SI_PB_GetSPBFlag(VOS_VOID)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return VOS_FALSE;   /*返回状态关闭*/
#else
    return (VOS_UINT32)gstPBConfigInfo.ucSPBFlag;
#endif
}


#endif

#if ((OSA_CPU_CCPU == VOS_OSA_CPU)||(defined(DMT)))


VOS_UINT32 SI_PB_GetEccNumber(SI_PB_ECC_DATA_STRU *pstEccData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPBOffset=0;
    VOS_UINT8                          *ptemp;
    VOS_UINT32                          ulNum;
    VOS_UINT8                           i,j;

    ulResult = SI_PB_LocateRecord(PB_ECC, 1, 1, &ucPBOffset);

    if(VOS_OK != ulResult)     /*当前电话本不存在或者初始化未完成*/
    {
        PB_ERROR_LOG("SI_PB_GetEccNumber Error: SI_PB_LocateRecord Return Failed");

        pstEccData->bEccExists = SI_PB_CONTENT_INVALID;
        pstEccData->ulReocrdNum= VOS_NULL;

        return VOS_ERR;
    }

    pstEccData->bEccExists = SI_PB_CONTENT_VALID;

    ulNum = ((gastPBContent[ucPBOffset].usTotalNum>USIM_MAX_ECC_RECORDS)?USIM_MAX_ECC_RECORDS:gastPBContent[ucPBOffset].usTotalNum);

    ptemp = gastPBContent[ucPBOffset].pContent;

    for(i=0,j=0; i<ulNum; i++)   /*根据数据结构最大长度循环*/
    {
        ulResult = SI_PB_CheckEccValidity(ptemp);

        if(VOS_ERR == ulResult)     /*当前记录内容无效*/
        {
            PB_INFO_LOG("SI_PB_GetEccNumber Info: The Ecc Number is Empty");
        }
        else                                /*转换当前记录内容*/
        {
            PB_INFO_LOG("SI_PB_GetEccNumber Info: The Ecc Number is Not Empty");

            /*lint -e534*/
            VOS_MemCpy(pstEccData->astEccRecord[j].aucEccCode,
                                    ptemp, gastPBContent[ucPBOffset].ucNumberLen);
            /*lint +e534*/

            if (USIMM_CARD_USIM == gstPBInitState.enCardType)
            {
                pstEccData->astEccRecord[j].bESC = SI_PB_CONTENT_VALID;

                /*lint -e534*/
                VOS_MemCpy(pstEccData->astEccRecord[j].AlphaIdentifier,
                           &ptemp[gastPBContent[ucPBOffset].ucNumberLen],
                           gastPBContent[ucPBOffset].ucNameLen);
                /*lint +e534*/

                pstEccData->astEccRecord[j].ucESC = ptemp[gastPBContent[ucPBOffset].ucRecordLen - 1];
            }

            j++;
        }

        ptemp += gastPBContent[ucPBOffset].ucRecordLen;
    }

    pstEccData->ulReocrdNum = j;

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 SI_PB_GetXeccNumber(SI_PB_ECC_DATA_STRU *pstEccData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulNum;
    VOS_UINT8                          *pucTemp;
    VOS_UINT8                           ucPBOffset=0;
    VOS_UINT8                           i;
    VOS_UINT8                           j;

    /* 输入参数检测 */
    if (VOS_NULL_PTR == pstEccData)
    {
        PB_ERROR_LOG("SI_PB_GetXeccNumber Error: Para is incorrect.");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(pstEccData, 0, sizeof(SI_PB_ECC_DATA_STRU));
    /*lint +e534*/

    ulResult = SI_PB_LocateRecord(PB_XECC, 1, 1, &ucPBOffset);

    /* 当前电话本不存在或者初始化未完成 */
    if (VOS_OK != ulResult)
    {
        PB_ERROR_LOG("SI_PB_GetXeccNumber Error: SI_PB_LocateRecord Return Failed");

        pstEccData->bEccExists = SI_PB_CONTENT_INVALID;
        pstEccData->ulReocrdNum= VOS_NULL;

        return VOS_ERR;
    }

    pstEccData->bEccExists = SI_PB_CONTENT_VALID;

    ulNum   = gastPBContent[ucPBOffset].usTotalNum;

    pucTemp = gastPBContent[ucPBOffset].pContent;

    for (i = 0, j = 0; i < ulNum; i++)   /* 根据数据结构最大长度循环 */
    {
        ulResult = SI_PB_CheckEccValidity(pucTemp);

        if (VOS_ERR == ulResult)     /* 当前记录内容无效 */
        {
            PB_INFO_LOG("SI_PB_GetXeccNumber Info: The Ecc Number is Empty");
        }
        else                                /* 转换当前记录内容 */
        {
            PB_INFO_LOG("SI_PB_GetXeccNumber Info: The Ecc Number is Not Empty");

            /*lint -e534*/
            VOS_MemCpy(pstEccData->astEccRecord[j].aucEccCode, pucTemp, gastPBContent[ucPBOffset].ucNumberLen);
            /*lint +e534*/

            j++;
        }

        pucTemp += gastPBContent[ucPBOffset].ucRecordLen;
    }

    pstEccData->ulReocrdNum = j;

    return VOS_OK;
}
#endif

#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif



