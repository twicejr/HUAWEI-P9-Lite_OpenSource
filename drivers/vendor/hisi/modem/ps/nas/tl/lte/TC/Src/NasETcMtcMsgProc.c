/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasETcMtcMsgProc.c
    Description : 处理TC发给MTC的消息
    History     :
     1.xiongxianghui00253310       2015-05-12  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasETcMtcMsgProc.h"
#include    "NasETcPublic.h"
#include    "NasETcMain.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCMTCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCMTCMSGPROC_C
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
 Function Name   : NAS_ETC_SndTcMtcStatusInfoMsg
 Description     : 向MTC发送ID_NAS_MTC_TC_STATUS_INFO_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310      2015-05-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcMtcStatusInfoMsg(MTC_NAS_TC_STATUS_ENUM_UINT16 enStatus)
{
    NAS_MTC_TC_STATUS_INFO_IND_STRU     *pstTcStatusInfoInd = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstTcStatusInfoInd = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(NAS_MTC_TC_STATUS_INFO_IND_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcStatusInfoInd)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcMtcStatusInfoMsg:ERROR:TC->MTC,Memory Alloc FAIL!");
        return ;
    }

    /* 清空 */
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_TC_MTC_MSG_ENTITY(pstTcStatusInfoInd),
                       NAS_ETC_GET_MSG_LENGTH(pstTcStatusInfoInd), 
                       0,
                       NAS_ETC_GET_MSG_LENGTH(pstTcStatusInfoInd));

    /* 填写消息头 */
    NAS_ETC_WRITE_MTC_MSG_HEAD(pstTcStatusInfoInd,ID_NAS_MTC_TC_STATUS_INFO_IND);

    pstTcStatusInfoInd->enTcStatus = enStatus;
    pstTcStatusInfoInd->enRatMode = MTC_NAS_RAT_MODE_LTE;

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcStatusInfoInd);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcMtcStatusInfoMsg:Send ID_NAS_MTC_TC_STATUS_INFO_IND!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcMtcStatusInfoMsg_ENUM, LNAS_FUNCTION_LABEL1);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasETcMtcMsgProc.c */
