/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasERabmIpMsgProc.c
  Description     : RABM模块处理IP模块的消息
  History         :
    1.lihong 00150010       2010-11-29   Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmIpMsgProc.h"
#include  "NasIpInterface.h"
#include  "NasERabmPublic.h"
#include  "NasERabmMain.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMIPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMIPMSGPROC_C
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
/*****************************************************************************
 Function Name   : NAS_ERABM_SndIpRabmDataInd
 Description     : 向IP模块发送ID_IP_RABM_DATA_IND消息
 Input           : ucEpsbId---------------------承载号
                   pucIpMsg---------------------IP数据包首地址
                   ulIpMsgLen-------------------IP数据包长度
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-11-29  Draft Enact

*****************************************************************************/
/*lint -e960*/
VOS_VOID  NAS_ERABM_SndIpRabmDataInd
(
    VOS_UINT8                           ucEpsbId,
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen
)
{
    IP_RABM_DATA_IND_STRU              *pstDataInd  = VOS_NULL_PTR;
    VOS_UINT32                          ulTmpLength = NAS_ERABM_NULL;

    /*根据空口消息的长度分配空间*/
    if( NAS_ERABM_NULL == ulIpMsgLen)
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_SndIpRabmDataInd: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_SndIpRabmDataInd_ENUM, LNAS_EMM_MSG_LENGTH_ERROR);
        return ;
    }
    else if(ulIpMsgLen > NAS_ERABM_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulIpMsgLen - NAS_ERABM_MIN_SND_MSG_LEN ;
        pstDataInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(IP_RABM_DATA_IND_STRU) + ulTmpLength);
    }
    else/*如果长度小于NAS_ERABM_MIN_SND_MSG_LEN，分配的空间等于NAS_ERABM_MIN_SND_MSG_LEN*/
    {
        pstDataInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(IP_RABM_DATA_IND_STRU));
    }

    if (VOS_NULL_PTR == pstDataInd)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndIpRabmDataInd:ERROR:Alloc msg fail!" );
        return;
    }

    /*清空*/
    NAS_ERABM_MEM_SET_S(   NAS_ERABM_GET_MSG_ENTITY(pstDataInd),
                        NAS_ERABM_GET_MSG_LENGTH(pstDataInd),
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstDataInd));

    /*填写消息头*/
    NAS_ERABM_WRITE_IP_MSG_HEAD(pstDataInd, ID_IP_RABM_DATA_IND);

    /* 填写消息内容 */
    pstDataInd->ucEpsbId = ucEpsbId;
    pstDataInd->stIpMsg.ulIpMsgSize = ulIpMsgLen;

    /*lint -e669*/
    NAS_ERABM_MEM_CPY_S(   pstDataInd->stIpMsg.aucIpMsg,
                        ulIpMsgLen,
                        pucIpMsg,
                        ulIpMsgLen);
    /*lint +e669*/

    /* 调用消息发送函数*/
    NAS_ERABM_SND_MSG(pstDataInd);
}
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

