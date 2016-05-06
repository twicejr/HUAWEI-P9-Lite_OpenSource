

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmProcUsim.h"
#include "CnasMntn.h"
#include "CnasCcb.h"
#include "NasUsimmApi.h"
#include "NasComm.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_PROC_USIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/


VOS_VOID CNAS_HSM_SndReadUsimmFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enCardApp,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileId
)
{
    NAS_USIMM_GETFILE_INFO_STRU                             stGetFileInfo;

    NAS_MEM_SET_S(&stGetFileInfo, sizeof(stGetFileInfo), 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    NAS_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      enCardApp,
                                      (VOS_UINT16)(enFileId),
                                      0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(UEPS_PID_HSM, 0, &stGetFileInfo);

    return;
}



VOS_VOID  CNAS_HSM_RcvUsimmReadIccidFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
)
{
    VOS_UINT8                                              *pucCardIccId = VOS_NULL_PTR;
    VOS_UINT8                                               i;

    pucCardIccId = CNAS_CCB_GetCardIccIdAddr();

    /* Read file fail */
    if (VOS_OK != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadIccidFileCnf: Read ICCID FAIL");

        for (i = 0; i < CNAS_CCB_ICCID_OCTET_LEN; i++)
        {
            pucCardIccId[i] = 0xFF;
        }

        return;
    }

    /* ICCID卡文件结构参考ETSI TS 102 201, 13.2节，其长度为10bytes */
    if (CNAS_CCB_ICCID_OCTET_LEN != pstUsimmReadCnfMsg->usEfLen)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadIccidFileCnf: Read ICCID length FAIL");

        for (i = 0; i < CNAS_CCB_ICCID_OCTET_LEN; i++)
        {
            pucCardIccId[i] = 0xFF;
        }

        return;
    }

    NAS_MEM_CPY_S(pucCardIccId,
                  sizeof(VOS_UINT8) * CNAS_CCB_ICCID_OCTET_LEN,
                  pstUsimmReadCnfMsg->aucEf,
                  pstUsimmReadCnfMsg->usEfLen);

    return;
}


VOS_VOID  CNAS_HSM_RcvUsimmReadUimidFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
)
{
    CNAS_CCB_UIMID_STRU                                    *pstUIMID = VOS_NULL_PTR;
    VOS_UINT8                                               i;

    pstUIMID = CNAS_CCB_GetUIMID();

    /* Read file fail */
    if (VOS_OK != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadUimidFileCnf: Read UIMID FAIL");

        for (i = 0; i < CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT; i++)
        {
            pstUIMID->aucEFRUIMID[i] = 0xff;
        }

        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read fail,
            set the UIMID length to 0, namely invalid UIMID */
        pstUIMID->aucEFRUIMID[0] = 0;

        return;
    }

    /* the EFRUIMID may have 5 or 8 bytes */
    if ((CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT != pstUsimmReadCnfMsg->usEfLen)
     && (CNAS_CCB_EFRUIMID_OCTET_LEN_FIVE  != pstUsimmReadCnfMsg->usEfLen))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadUimidFileCnf: Read UIMID length FAIL");

        for (i = 0; i < CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT; i++)
        {
            pstUIMID->aucEFRUIMID[i] = 0xff;
        }

        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read length fail,
            set the UIMID length to 0, namely invalid UIMID */
        pstUIMID->aucEFRUIMID[0] = 0;

        return;
    }

    NAS_MEM_CPY_S(pstUIMID->aucEFRUIMID,
                  sizeof(pstUIMID->aucEFRUIMID),
                  pstUsimmReadCnfMsg->aucEf,
                  pstUsimmReadCnfMsg->usEfLen);

    return;
}


VOS_VOID  CNAS_HSM_RcvUsimmReadEsnMeidMeFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
)
{
    CNAS_CCB_ESNMEIDME_INFO_STRU                           *pstEsnMeidMe = VOS_NULL_PTR;

    pstEsnMeidMe = CNAS_CCB_GetEsnMeidMeInfoAddr();

    /* Read file fail */
    if (VOS_OK != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadEsnMeidMeFileCnf: Read ESNMEIDME FAIL");

        pstEsnMeidMe->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_BUTT;

        return;
    }

    if (CNAS_CCB_ESN_MEID_OCTET_LEN != pstUsimmReadCnfMsg->usEfLen)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadEsnMeidMeFileCnf: ESNMEIDME length is error");

        pstEsnMeidMe->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_BUTT;

        return;
    }

    /* This EF stores the 32-bit ESN_ME or 56-bit MEID_ME  to  which  the  R-UIM  is  attached.
      Bytes           Description                        M/O      Length
         1  Number of bytes for ESN_ME or MEID_ME         M       1 byte
         2  Least significant byte                        M       1 byte
         3      :                                         M       1 byte
         4      :                                         M       1 byte
         5      :                                         M       1 byte
         6      :                                         M       1 byte
         7      :                                         M       1 byte
         8  Most significant byte                         M       1 byte */
    if (CNAS_CCB_ESN_OCTET_LEN == pstUsimmReadCnfMsg->aucEf[0])
    {
        pstEsnMeidMe->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_ESN;

        NAS_MEM_CPY_S(pstEsnMeidMe->u.aucEsn, sizeof(pstEsnMeidMe->u.aucEsn), pstUsimmReadCnfMsg->aucEf + 1, pstUsimmReadCnfMsg->aucEf[0]);
    }
    else if (CNAS_CCB_MEID_OCTET_LEN == pstUsimmReadCnfMsg->aucEf[0])
    {
        pstEsnMeidMe->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_MEID;

        NAS_MEM_CPY_S(pstEsnMeidMe->u.aucMeid, sizeof(pstEsnMeidMe->u.aucMeid), pstUsimmReadCnfMsg->aucEf + 1, pstUsimmReadCnfMsg->aucEf[0]);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadEsnMeidMeFileCnf: ESNMEIDME length is error");

        pstEsnMeidMe->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_BUTT;
    }

    return;
}


VOS_VOID  CNAS_HSM_RcvUsimmReadHrpdAccessAuthUserNameFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
)
{
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstHrpdAccessAuthInfo = VOS_NULL_PTR;

    pstHrpdAccessAuthInfo = CNAS_CCB_GetHrpdAccesAuthInfoAddr();

    /* Read file fail */
    if (VOS_OK != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadHrpdAccessAuthUserNameFileCnf: Read HRPDUPPID FAIL");

        pstHrpdAccessAuthInfo->ucAccessAuthAvailFlag = VOS_FALSE;

        return;
    }

    /* refer to 3GPP2 C.S0023-D Section3.4.53 and C.S0016-D v2.0 Section 3.5.8.13 */
    /* 1、GPP2 C.S0023-D Section3.4.53
            Bytes  | Description                                           | M/O | Length
              1      Length of HRPD Access Authentication                    M     1 byte
                     User Profile ParametersBlock
             2~X+1  See C.S0016-D v2.0 Section 3.5.8.13, HRPD Access         M     X byte
                    Authentication User Profile Parameters Block

       2、C.S0016-D v2.0 Section 3.5.8.13, HRPD Access
           Field           |        Length (bits)
           NAI_LENGTH      |          8
           NAI             |          8 * NAI_LENGTH
           AUTH_ALGORITHM  |          4
           RESERVED        |          4                                          */

    /* aucEf[0]-> ength of HRPD Access Authentication User Profile ParametersBlock
       aucEf[1]-> NAI_LENGTH
       aucEf[2]-> NAI */

    /* 由卡文件的结构可知，aucEf[0]的长度为C.S0016-D v2.0 Section 3.5.8.13所定义的长度的总长，
     * 包括NAI_LENGTH、AUTH_ALGORITHM、RESERVED占用的2byte。而aucEf[1]为NAI的长度，所以
     * usEfLen与aucEf[1]应该满足usEfLen不小于aucEf[1]+3
     * 其中3byte为: NAI_LENGTH、AUTH_ALGORITHM、RESERVED占用的2byte以及aucEf[0] 1byte */
    if ((pstUsimmReadCnfMsg->usEfLen < (pstUsimmReadCnfMsg->aucEf[1] + 3))
     || (CNAS_CCB_MAX_AUTHDATA_USERNAME_LEN < pstUsimmReadCnfMsg->aucEf[1]))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadHrpdAccessAuthUserNameFileCnf: Authdata username legth is too lager");

        pstHrpdAccessAuthInfo->ucAccessAuthAvailFlag = VOS_FALSE;
    }
    else
    {
        pstHrpdAccessAuthInfo->ucAccessAuthAvailFlag   = VOS_TRUE;
        pstHrpdAccessAuthInfo->ucAccessAuthUserNameLen = pstUsimmReadCnfMsg->aucEf[1];

        NAS_MEM_CPY_S(pstHrpdAccessAuthInfo->aucAccessAuthUserName,
                      sizeof(pstHrpdAccessAuthInfo->aucAccessAuthUserName),
                      pstUsimmReadCnfMsg->aucEf + 2,
                      pstUsimmReadCnfMsg->aucEf[1]);

        return;
    }

    return;
}



VOS_VOID  CNAS_HSM_RcvUsimmReadFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg,
    USIMM_DEF_FILEID_ENUM_UINT32                            enEfId
)
{
    switch (enEfId)
    {
        case USIMM_ICCID_ID:
            CNAS_HSM_RcvUsimmReadIccidFileCnf(pstUsimmReadCnfMsg);
            break;

        case USIMM_CSIM_EFRUIMID_ID:
        case USIMM_CDMA_EFRUIMID_ID:
            CNAS_HSM_RcvUsimmReadUimidFileCnf(pstUsimmReadCnfMsg);
            break;

        case USIMM_CSIM_EFESNMEID_ID:
        case USIMM_CDMA_EFESNMEIDME_ID:
            CNAS_HSM_RcvUsimmReadEsnMeidMeFileCnf(pstUsimmReadCnfMsg);
            break;

        case USIMM_CSIM_EFHRPDUPP_ID:
        case USIMM_CDMA_EFHRPDUPP_ID:
            CNAS_HSM_RcvUsimmReadHrpdAccessAuthUserNameFileCnf(pstUsimmReadCnfMsg);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUsimmReadFileCnf:WARNING: File Id Abnormal");
            break;
    }
}


VOS_VOID CNAS_HSM_SndReadUsimmStoreEsnMeidRsltReq(VOS_VOID)
{
    USIMM_QUERYESNMEIDRSLT_REQ_STRU    *pstMsg          = VOS_NULL_PTR;

    pstMsg = (USIMM_QUERYESNMEIDRSLT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSM,
                   sizeof(USIMM_QUERYESNMEIDRSLT_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndReadUsimmStoreEsnMeidRsltReq: Alloc msg wrong");

        return;
    }

    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSM;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName       = USIMM_QUERYESNMEIDRSLT_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_CDMA_APP;

    /* 预留参数 */
    pstMsg->stMsgHeader.ulSendPara      = 0;

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstMsg);

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

