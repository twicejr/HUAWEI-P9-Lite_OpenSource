


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmPdcpMsgProc.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasERabmEsmMsgProc.h"
#include  "NasERabmCdsMsgProc.h"
#include  "NasEsmPublic.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMPDCPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMPDCPMSGPROC_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/
VOS_VOID APP_DATA_IND_FUNC( VOS_UINT32  ulRabId, VOS_UINT32  ulDataLen, const VOS_UINT8 *srcMem)
{
    (VOS_VOID)ulRabId;
    (VOS_VOID)ulDataLen;
    (VOS_VOID)srcMem;
}

VOS_VOID APP_ERABM_DATA_TRANS_FUNC( const VOS_UINT8 *pucData)
{
    (VOS_VOID)pucData;
}


/*****************************************************************************
 Function Name   : LPDCP_ERABM_GetDefaultEpsbId
 Description     : 获取DRB对应的缺省承载号
 Input           : ucDrbId---------------------DRB ID
 Output          : pucDeftEpsbId---------------缺省承载号指针
 Return          : VOS_UINT32
 History         :
      1.wangchen 00209181   2014-10-24  Draft Enact

*****************************************************************************/
VOS_UINT32 LPDCP_ERABM_GetDefaultEpsbId
(
    VOS_UINT8                           ucDrbId,
    VOS_UINT8                          *pucDeftEpsbId
)
{
    VOS_UINT32                           ulEpsbId = NAS_ERABM_NULL;

    if (VOS_NULL_PTR == pucDeftEpsbId)
    {
        NAS_ERABM_ERR_LOG("LPDCP_ERABM_GetDefaultEpsbId:pucEpsbId is NULL!");
        TLPS_PRINT2LAYER_ERROR(LPDCP_ERABM_GetDefaultEpsbId_ENUM, LNAS_ERABM_EpsbIdIsNULL);
        return PS_FAIL;
    }

    /* 获取DRB关联承载号 */
    if (NAS_ERABM_SUCCESS != NAS_ERABM_GetEpsbIdByDrbId(  ucDrbId,
                                                         &ulEpsbId))
    {
        NAS_ERABM_WARN_LOG("LPDCP_ERABM_GetDefaultEpsbId:NAS_ERABM_GetEpsbIdByDrbId failed!");
        TLPS_PRINT2LAYER_WARNING(LPDCP_ERABM_GetDefaultEpsbId_ENUM, LNAS_ERABM_GetEpsbIdByDrbId_Failed);

        return PS_FAIL;
    }

    /* 判断承载类型是否为缺省 */
    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ERABM_GetEpsbBearerType(ulEpsbId)))
    {
        *pucDeftEpsbId = (VOS_UINT8)ulEpsbId;
    }
    else
    {
        *pucDeftEpsbId = (VOS_UINT8)NAS_ERABM_GetEpsbLinkedEpsbId(ulEpsbId);
    }

    return PS_SUCC ;
}







#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

