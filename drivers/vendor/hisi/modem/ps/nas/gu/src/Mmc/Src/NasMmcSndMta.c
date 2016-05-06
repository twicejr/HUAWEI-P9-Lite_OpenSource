/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndMta.c
  版 本 号   : 初稿
  作    者   : gaoliangliang 00322017
  生成日期   : 2015年12月01日
  最近修改   :
  功能描述   : MMC发给MTA的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年12月01日
    作    者   : gaoliangliang 00322017
    修改内容   : 创建文件

******************************************************************************/
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
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMtaGetNasChrInfoCnf
 功能描述  : 向MTA发送CHR NAS信息
 输入参数  : 无,

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月01日
    作    者   : g00322017
    修改内容   : 新生成函数
*****************************************************************************/
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

