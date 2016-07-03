

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaProcMma.h"
#include  "TafCbaProcUsim.h"
#include  "MnComm.h"
#include  "MnMsgTimerProc.h"
#include  "TafCbaMntn.h"

#include "TafMmaInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_MMA_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/




VOS_VOID TAF_CBA_ProcMmaMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch (pstMsgHeader->ulMsgName)
    {
        case MN_USIM_STATUS_IND:
            TAF_CBA_RcvMmaUsimStatusInd(pstMsg);
            break;

        default:
            break;
    }
}


VOS_VOID TAF_CBA_RcvMmaUsimStatusInd(
    struct MsgCB                       *pstMsg
)
{
    MNPH_USIM_STATUS_IND_STRU          *pstUsimStatus;

    pstUsimStatus = (MNPH_USIM_STATUS_IND_STRU *)pstMsg;

    if (MNPH_USIM_STATUS_AVILABLE != pstUsimStatus->enUsimStatus)
    {
        /* 初始化CBA模块的USIM相关的全局变量 */
        TAF_CBA_InitSimInfo();
        /* 追加NV中配置到CBS激活消息列表 */
        TAF_CBA_AppendNvUserAcceptMsgIdList();
        return;
    }

    /* 读取CBS相关的USIM卡文件. 文件读取顺序: CBMI 文件; CBMIR 文件 CBMID */
    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMI_ID, NAS_USIM_SVR_CBMI);

    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMIR_ID, NAS_USIM_SVR_CBMIR);

    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMID_ID, NAS_USIM_SVR_DATA_DL_SMSCB);


    /* 追加NV中配置到CBS激活消息列表 */
    TAF_CBA_AppendNvUserAcceptMsgIdList();

    /* 应用USIM文件信息到本地和通知底层配置更新 */
    TAF_CBA_ApplyUsimInfo();

    /* 勾NV相关的可维可测信息  */
    TAF_CBA_SndOmNvimInfo();

}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
