
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasMmcSndMta.h"
#include "NasMtaInterface.h"
#include "PsCommonDef.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmcComFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_MTA_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID NAS_MMC_SndMtaGetNasChrInfoCnf(VOS_VOID)
{
    MMC_MTA_NAS_CHR_INFO_CNF_STRU      *pstNasInfoMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulIsRrcConnExist;

    pstNasInfoMsg = (MMC_MTA_NAS_CHR_INFO_CNF_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(MMC_MTA_NAS_CHR_INFO_CNF_STRU));
    if (VOS_NULL_PTR == pstNasInfoMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMtaGetNasChrInfoCnf: memery alloc failed.");

        return;
    }

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstNasInfoMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstNasInfoMsg,
                        UEPS_PID_MTA,
                        ID_MMC_MTA_GET_NAS_CHR_INFO_CNF,
                        sizeof(MMC_MTA_NAS_CHR_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    ulIsRrcConnExist                 = NAS_MML_IsRrcConnExist();
    pstNasInfoMsg->ucIsExsitRrcConn  = (VOS_UINT8)ulIsRrcConnExist;

    NAS_MMC_SEND_MSG(pstNasInfoMsg);

    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

