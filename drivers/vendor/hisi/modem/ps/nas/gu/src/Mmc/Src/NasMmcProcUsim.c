/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcProcUsim.c
  版 本 号   : 初稿
  作    者   : luokaihui /l00167671
  生成日期   : 2011年05月10日
  最近修改   :
  功能描述   : 操作(读写)SIM卡文件相关函数放在本文件中
  函数列表   :
  修改历史   :
  1.日    期   : 2011年05月10日
    作    者   : luokaihui /00167671
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmSublayerDef.h"
#include "NasMmcProcUsim.h"
#include "NasMmcFsmSwitchOn.h"
#include "GmmExt.h"
#include "NasMmcCtx.h"
#include "NasMmlCtx.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "siappstk.h"
#include "NasMmcComFunc.h"

#include "NasUsimmApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMCPROCUSIM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
/* MMC 收到USIMM_REFRESH_ALL_FILE的refresh消息时，只更新高优先网络文件
   读6F7E会在注册时用TMSI而导致注册失败  */
VOS_UINT16 g_astNasUsimAllRefreshFileID[] =
{
    USIMM_USIM_EFEHPLMN_ID,
    USIMM_USIM_EFHPLMNwACT_ID,
    USIMM_USIM_EFPLMNWACT_ID,
    USIMM_USIM_EFOPLMNWACT_ID,
    USIMM_USIM_EFFPLMN_ID
};

VOS_UINT16 g_astNasGsmAllRefreshFileID[] =
{
    USIMM_GSM_EFHPLMNACT_ID,
    USIMM_GSM_EFPLMNWACT_ID,
    USIMM_GSM_EFOPLMNWACT_ID,
    USIMM_GSM_EFPLMNSEL_ID,
    USIMM_GSM_EFFPLMN_ID
};

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */


/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : Mmc_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID
 功能描述  : 读取HPLMN文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_SIM_PLMN_WITH_RAT_STRU                         *pstHPlmnWithRatList = VOS_NULL_PTR;
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU                   *pstHplmnWithRatInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucHplmnWithRat ;

    if ( VOS_OK == pstMsg->stCmdResult.ulResult )
    {
        /* 获取全局变量的地址 */
        pstHplmnWithRatInfo = NAS_MML_GetSimHplmnWithRatList();
        pstHPlmnWithRatList = pstHplmnWithRatInfo->astHPlmnWithRatInfo;

        /* 初始化全局变量中的HPLMN信息，然后把SIM中读取的PLMN ID和RAT存储到全局变量中 */
        NAS_MML_InitSimHPlmnWithRatInfo(pstHplmnWithRatInfo);

        ucHplmnWithRat = (VOS_UINT8)(pstMsg->usEfLen / NAS_MML_PLMN_WITH_RAT_UNIT_LEN);
        if ( ucHplmnWithRat > NAS_MML_MAX_HPLMN_WITH_RAT_NUM )
        {
            ucHplmnWithRat = NAS_MML_MAX_HPLMN_WITH_RAT_NUM;
        }

        /* 将USIM中保存的PLMN信息转换为内存中的信息 */
        NAS_MMC_ConverPlmnInfoFromSim(pstMsg->aucEf, ucHplmnWithRat, pstHPlmnWithRatList);

        /* 保存PLMN的个数 */
        pstHplmnWithRatInfo->ucHPlmnWithRatNum = ucHplmnWithRat;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID
 功能描述  : 读取FORBIDDEN PLMN
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT8                           ucFplmnNum;
    VOS_UINT32                          ulTempData;
    VOS_UINT8                           ucTempNum;                              /* 存储准MMC中forbidden PlMN个数的临时变量  */
    VOS_UINT32                          i;

    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstForbPlmnIdList  = VOS_NULL_PTR;

    if ( VOS_OK == pstMsg->stCmdResult.ulResult )
    {
        /* 获取保存SIM卡中禁止的PLMN的全局变量信息 */
        pstForbidPlmnInfo   = NAS_MML_GetForbidPlmnInfo();
        pstForbPlmnIdList   = pstForbidPlmnInfo->astForbPlmnIdList;

        if (( NAS_MML_SIM_FILE_LEN_VALID == ( pstMsg->usEfLen % NAS_MML_SIM_PLMN_ID_LEN)))
        {                                                                           /* 长度合法                                 */
            ucFplmnNum = (VOS_UINT8)(pstMsg->usEfLen / NAS_MML_SIM_PLMN_ID_LEN);

            /* 存MML全局变量中SIM的forbidden PLMN个数   */
            pstForbidPlmnInfo->ucUsimForbPlmnNum = ucFplmnNum;

            if ( ucFplmnNum <= NAS_MML_MAX_FORBPLMN_NUM )
            {
                ucTempNum = ucFplmnNum;
            }
            else
            {
                ucTempNum = NAS_MML_MAX_FORBPLMN_NUM;
            }

            ucFplmnNum = 0;

            for (i = 0; i < ucTempNum; i++)
            {
                if ( (NAS_MMC_USIM_FILE_CONTENT_INVALID == pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN)])
                  && (NAS_MMC_USIM_FILE_CONTENT_INVALID == pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 1])
                  && (NAS_MMC_USIM_FILE_CONTENT_INVALID == pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 2]) )
                {                                                                   /* 内容非法                                 */
                    continue;
                }

                /* 将全局变量中的PLMN信息清为0 */
                PS_MEM_SET(&(pstForbPlmnIdList[ucFplmnNum]), NAS_MML_PLMN_ID_ZERO, sizeof(NAS_MML_PLMN_ID_STRU));

                    /*
                       PLMN BCD 编码 方式

                       MCC digit 2,  MCC digit 1, ----OCTET 1
                       MNC digit 3,  MCC digit 3, ----OCTET 2
                       MNC digit 2,  MNC digit 1, ----OCTET 3
                    */
                /* 获取SIM卡中的国家号 */
                ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pstMsg->aucEf[i * NAS_MML_SIM_PLMN_ID_LEN];
                pstForbPlmnIdList[ucFplmnNum].ulMcc = ulTempData;

                ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pstMsg->aucEf[i * NAS_MML_SIM_PLMN_ID_LEN]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
                pstForbPlmnIdList[ucFplmnNum].ulMcc |= (ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS);

                ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 1];
                pstForbPlmnIdList[ucFplmnNum].ulMcc |= (ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS);

                /* 获取SIM卡中的网络号 */
                ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 1]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
                pstForbPlmnIdList[ucFplmnNum].ulMnc |= (ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS);

                ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 2];
                pstForbPlmnIdList[ucFplmnNum].ulMnc |= ulTempData;

                ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 2]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
                pstForbPlmnIdList[ucFplmnNum].ulMnc |= (ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS);
                ucFplmnNum++;
            }

            /* 初始化MMC中forbidden PLMN的个数 */
            pstForbidPlmnInfo->ucForbPlmnNum = ucFplmnNum;
        }
        else
        {                                                                           /* 长度非法                                 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID:ERROR: The length of USIM_READ_FILE_CNF is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_UPLMN_SEL_FILE_ID
 功能描述  : 读取UPLMN文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_UPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT8                           ucUplmnNum;

    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstUplmnAddr    = VOS_NULL_PTR;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        ucUplmnNum = (VOS_UINT8)(pstMsg->usEfLen / NAS_MML_PLMN_WITH_RAT_UNIT_LEN);

        if ( ucUplmnNum > NAS_MML_MAX_USERPLMN_NUM )
        {
            ucUplmnNum  = NAS_MML_MAX_USERPLMN_NUM;
        }

        /* 获取全局变量的地址 */
        pstUserPlmnInfo = NAS_MML_GetSimUserPlmnList();
        pstUplmnAddr    = pstUserPlmnInfo->astUserPlmnInfo;

        /* 初始化全局变量中的UPLMN信息，然后把SIM中读取的PLMN ID和RAT存储到全局变量中 */
        NAS_MML_InitSimUserPlmnInfo(pstUserPlmnInfo);

        /* 将USIM中保存的PLMN信息转换为内存中的信息 */
        NAS_MMC_ConverPlmnInfoFromSim(pstMsg->aucEf, ucUplmnNum, pstUplmnAddr);

        /* 保存UPLMN的个数 */
        pstUserPlmnInfo->ucUserPlmnNum = ucUplmnNum;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : Mmc_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID
 功能描述  : 读取OPLMN文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2013年10月15日
   作    者   : x65241
   修改内容   : 有定制NV时，数据不生效
 8.日    期   : 2013年11月26日
   作    者   : s00190137
   修改内容   : 添加分组机制，最大支持设置256个OPLMN,单组允许最大设置50个OPLMN
 9.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_OPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usOplmnNum;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstOplmnAddr    = VOS_NULL_PTR;

    ulRet                               = VOS_TRUE;

    ulRet = NAS_MML_IsNvimOplmnAvail();

    /* 如果用户设置的OPLMN有效，需要将NV中的OPLMN列表保存到MML全局变量中 */
    if (ulRet == VOS_TRUE)
    {
        return;
    }
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        usOplmnNum = (VOS_UINT16)(pstMsg->usEfLen / NAS_MML_PLMN_WITH_RAT_UNIT_LEN);

        if ( usOplmnNum > NAS_MML_MAX_OPERPLMN_NUM )
        {
            usOplmnNum = NAS_MML_MAX_OPERPLMN_NUM;
        }

        /* 获取全局变量的地址 */
        pstOperPlmnInfo = NAS_MML_GetSimOperPlmnList();
        pstOplmnAddr    = pstOperPlmnInfo->astOperPlmnInfo;

        /* 初始化全局变量中的OPLMN信息，然后把SIM中读取的PLMN ID和RAT存储到全局变量中 */
        NAS_MML_InitSimOperPlmnInfo(pstOperPlmnInfo);

        /* 将USIM中保存的PLMN信息转换为内存中的信息 */
        NAS_MMC_ConverPlmnInfoFromSim(pstMsg->aucEf, usOplmnNum, pstOplmnAddr);

        /* 保存OPLMN的个数 */
        pstOperPlmnInfo->usOperPlmnNum = usOplmnNum;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_OPLMN_SEL_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID
 功能描述  : 读取LRPLMNSI文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_LAST_RPLMN_SEL_IND_ENUM_UINT8                  *penPLMNSelInd = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();
        penPLMNSelInd   = &(pstEHPlmnInfo->enPLMNSelInd);

        *penPLMNSelInd  = NAS_MML_LRPLMN_SELECTION_IND_INVALID;

        if ( (NAS_MML_LRPLMNSI_SIM_FILE_LEN == pstMsg->usEfLen)
          && (NAS_MML_LRPLMN_SELECTION_IND_VALID == pstMsg->aucEf[0]) )
        {
            *penPLMNSelInd = NAS_MML_LRPLMN_SELECTION_IND_VALID;
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID
 功能描述  : 读取EquivalentHPLMNPI文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo       = VOS_NULL_PTR;
    NAS_MML_EHPLMN_PRESENT_IND_ENUM_UINT8                  *penEHplmnPresentInd = VOS_NULL_PTR;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        /* 取得全局变量地址 */
        pstEHPlmnInfo                       = NAS_MML_GetSimEhplmnList();
        penEHplmnPresentInd                 = &(pstEHPlmnInfo->enEHplmnPresentInd);

        if ( NAS_MML_EHPLMNPI_SIM_FILE_LEN == pstMsg->usEfLen )
        {
            *penEHplmnPresentInd        = pstMsg->aucEf[0];
        }
        else
        {
            *penEHplmnPresentInd        = NAS_MML_EHPLMN_PRESENT_IND_NO_PREF;
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;


}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID
 功能描述  : 读取EHPLMN文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢

 5.日    期   : 2011年12月12日
   作    者   : w00167002
   修改内容   : DTS2011120808319:RPLMN不存在EHPLMN中无任何有效网络，导致L下
                 开机搜FFFFFF;此时实际应该使用6f07卡文件中的HOME PLMN网络。
                 协议23122-950如下:
                 EHPLMN:  Any of the PLMN entries contained in the Equivalent HPLMN list.
                 Equivalent HPLMN list: To allow provision for multiple HPLMN codes,
                 PLMN codes that are present within this list shall replace the
                 HPLMN code derived from the IMSI for PLMN selection purposes.
                 This list is stored on the USIM and is known as the EHPLMN list.
                 The EHPLMN list may also contain the HPLMN code derived from the IMSI.
                 If the HPLMN code derived from the IMSI is not present in the
                 EHPLMN list then it shall be treated as a Visited PLMN for PLMN selection purposes.

                 4.4.3:It is possible for the home network operator to identify
                 alternative Network IDs as the HPLMN. If the EHPLMN list is present,
                 and not empty, the entries in the EHPLMN list are used in the network
                 selection procedures. When attempting to select a network the
                 highest priority EHPLMN that is available shall be selected.
                 If the EHPLMN list is present and is empty or if the EHPLMN list
                 is not present, the HPLMN derived from the IMSI is used for network
                 selection procedures.
 6.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中

7.日    期   : 2012年6月11日
  作    者   : w00166186
  修改内容   : AT&T&DCM项目
 8.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 9.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmn;
    VOS_UINT32                          ulEHplmnNum;
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEHPlmnInfo = VOS_NULL_PTR;

    NAS_MML_SIM_EHPLMN_INFO_STRU        stTempSimEHPlmnInfo;

    VOS_UINT8                           ucUserCfgEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astUserCfgEhPlmnList[NAS_MML_MAX_USER_CFG_EHPLMN_NUM];

    VOS_UINT8                           ucSimEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astSimEhPlmnList[NAS_MML_MAX_EHPLMN_NUM];

    PS_MEM_SET(&stPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    PS_MEM_SET(&stTempSimEHPlmnInfo, 0, sizeof(NAS_MML_SIM_EHPLMN_INFO_STRU));

    ucSimEhplmnListNum                  = 0;
    PS_MEM_SET(astUserCfgEhPlmnList, (VOS_UINT)0X00, sizeof(astUserCfgEhPlmnList));

    ucUserCfgEhplmnListNum              = 0;
    PS_MEM_SET(astSimEhPlmnList, (VOS_UINT)0X00, sizeof(astSimEhPlmnList));

    pstSimEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    /* 如果当前为ACTING-HPLMN，则不更新 */
    if ( NAS_MML_HPLMN_TYPE_ACTING_HPLMN == NAS_MML_GetHPlmnType())
    {
        return;
    }

    /* 读卡文件失败 */
    if (VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
        return;
    }

    /* 读取的卡文件长度不合法，直接返回VOS_FALSE */
    if ((pstMsg->usEfLen < NAS_MML_SIM_PLMN_ID_LEN)
     || (NAS_MML_SIM_FILE_LEN_VALID != (pstMsg->usEfLen % NAS_MML_SIM_PLMN_ID_LEN)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF is invalid.");
        return;
    }

    ulEHplmnNum = (VOS_UINT32) (pstMsg->usEfLen / NAS_MML_SIM_PLMN_ID_LEN);

    if (ulEHplmnNum > NAS_MML_MAX_EHPLMN_NUM)
    {
        ulEHplmnNum = NAS_MML_MAX_EHPLMN_NUM;
    }


    /* 初始化EHPLMN信息，然后把SIM中读取的PLMN ID和RAT存储到全局变量中 */
    NAS_MML_InitSimEhPlmnInfo(&stTempSimEHPlmnInfo);

    /* 取得用户NV中配置的EHplmn信息，用户配置的EHplmn信息高于SIM卡中的EHPLMN */
    NAS_MML_GetValidUserCfgEhplmnInfo( NAS_MML_GetSimImsi(),
                                       &ucUserCfgEhplmnListNum,
                                       astUserCfgEhPlmnList );

    /* 将用户NV中配置的EHplmn信息加入到SIM中的EHPLMN信息里 */
    NAS_MMC_AddPlmnListIntoSimEhplmnInfo( ucUserCfgEhplmnListNum,
                                          astUserCfgEhPlmnList,
                                          NAS_MMC_PLMN_TYPE_HPLMN,
                                          &stTempSimEHPlmnInfo);


    /* 将USIM中保存的PLMN信息转换为内存中的信息 */
    for ( i = 0; i < ulEHplmnNum; i++ )
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstMsg->aucEf + (NAS_MML_SIM_PLMN_ID_LEN * i), NAS_MML_SIM_PLMN_ID_LEN);
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
        {
            astSimEhPlmnList[ucSimEhplmnListNum] = stPlmn;
            ucSimEhplmnListNum++;
        }
    }

    NAS_MMC_AddPlmnListIntoSimEhplmnInfo( ucSimEhplmnListNum,
                                          astSimEhPlmnList,
                                          NAS_MMC_PLMN_TYPE_HPLMN,
                                          &stTempSimEHPlmnInfo);


    /* NV中配置的和卡文件中的EHplmn的总个数为0个，则使用IMSI中的HOME PLMN */
    if ( 0 == stTempSimEHPlmnInfo.ucEhPlmnNum)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID:WARNING: VALID EHplmn number is zero.");

        /* 更新当前HPLMN的类型 */
        NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_HPLMN);

        NAS_MMC_UpdateHomePlmn( NAS_MML_GetSimImsi() );

        return;
    }


    /* 更新当前HPLMN的类型 */
    NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_EHPLMN);

    /* NV中配置的和卡文件中的EHplmn的总个数不为0个，则将所有有效的EHplmn信息
       更新到内存中去 */
    pstSimEHPlmnInfo->ucEhPlmnNum = stTempSimEHPlmnInfo.ucEhPlmnNum;

    PS_MEM_CPY(pstSimEHPlmnInfo->astEhPlmnInfo,
               stTempSimEHPlmnInfo.astEhPlmnInfo,
               sizeof(pstSimEHPlmnInfo->astEhPlmnInfo));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID
 功能描述  : 读取高优先级搜索时间间隔文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : luokaihui /l00167671
    修改内容   : 新生成函数
 2. 日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
 3. 日    期   : 2011年7月26日
    作    者   : z00161729
    修改内容   : V7R1 PhaseII 全局变量调整
 4. 日    期   : 2011年7月29日
    作    者   : w00166186
    修改内容   : V7R1 PhaseII 全局变量调整
 5.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 6.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 7.日    期   : 2012年6月11日
   作    者   : l60609
   修改内容   : AT&T&DCM：NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_TRUE)已在
                NAS_MMC_InitHighPrioPlmnSearchCtx中初始化
 8.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

        if (NAS_MML_HPLMN_PERI_FILE_LEN == pstMsg->usEfLen)
        {
            /*协议23.011规定，最大搜索间隔为8小时，而在协议31.102中
              ，读出的该值为16进制数，因此当该值大于等于30时，使用默
              认值60min
              31.102规定，6F31这个文件的第一个字节表示时长，单位为6分钟
            */
            if ( pstMsg->aucEf[0] > (NAS_MMC_MAX_PERI_HPLMN_ATTEMP_TIME_LEN/NAS_MMC_PERI_HPLMN_ATTEMP_STEP_SIZE) )
            {
                /* orange需求:当运营商订制时，当SIM卡中的值是无效值时，
                   从NV中获取，默认值是18分钟 */
                if (VOS_TRUE == pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ucNvimActiveFlg)
                {
                    /* Orang需求:  运营商定制值*60秒*1000毫秒 */
                    NAS_MML_SetSimHplmnTimerLen(pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ulDefaultMaxHplmnLen);
                }
                else
                {
                    /* 默认值为60分钟*60秒*1000毫秒 */
                    NAS_MML_SetSimHplmnTimerLen(NAS_MML_SIXTY_MINUTE * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND);
                }
            }
            else
            {
                /* SIM卡取值*6分钟*60秒*1000毫秒 */
                NAS_MML_SetSimHplmnTimerLen(pstMsg->aucEf[0] * NAS_MMC_PERI_HPLMN_ATTEMP_STEP_SIZE * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND);
            }
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID
 功能描述  : 读取MNC LENGTH文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : luokaihui /l00167671
    修改内容   : 新生成函数
 2. 日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  3.日    期   : 2011年12月03日
    作    者   : w00166186
    修改内容   : DTS2011112907465,读USIM失败后导致开机慢
  4.日    期   : 2012年5月16日
    作    者   : w00176964
    修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
  5.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题,区别两位和三位的MNC
  6.日    期   : 2012年12月26日
    作    者   : 张鹏 /z00214637
    修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
  7.日    期   : 2015年03月09日
    作    者   : y00245242
    修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, begin */
    VOS_UINT8                           ucExactlyComparaFlag;

    ucExactlyComparaFlag = NAS_MML_GetPlmnExactlyComparaFlg();
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, end */

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        /* 31.102,4.2.18章节，SIM卡文件长度不小于3 */
        if ( pstMsg->usEfLen < 3 )
        {
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mmc_RcvAgentUsimReadFileCnf:WARNING: The length of USIM_READ_FILE_CNF(MNC length) is invalid.");
        }
        else if ( 3 == pstMsg->usEfLen )
        {
            /* 31.102,4.2.18章节，SIM卡文件的第一个字节表示Operation mode */
            NAS_MML_SetUeOperMode(pstMsg->aucEf[0]);
        }
        else
        {
            /* 31.102,4.2.18章节，SIM卡文件的第一个字节表示Operation mode */
            NAS_MML_SetUeOperMode(pstMsg->aucEf[0]);
            if (( NAS_MMC_MNC_LENGTH_TWO_BYTES_IN_IMSI == (pstMsg->aucEf[NAS_MMC_MNC_LENGTH_INDICATOR_POSITION-1] & NAS_MML_OCTET_LOW_FOUR_BITS) )
            || ( NAS_MMC_MNC_LENGTH_THREE_BYTES_IN_IMSI == (pstMsg->aucEf[NAS_MMC_MNC_LENGTH_INDICATOR_POSITION-1] & NAS_MML_OCTET_LOW_FOUR_BITS) ))
            {
                /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
                if (VOS_TRUE == ucExactlyComparaFlag)
                {
                    NAS_MML_SetUsimMncLen(pstMsg->aucEf[NAS_MMC_MNC_LENGTH_INDICATOR_POSITION-1] & NAS_MML_OCTET_LOW_FOUR_BITS);
                }
                /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */
            }
            else
            {
                PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mmc_RcvAgentUsimReadFileCnf:WARNING: The value of USIM_READ_FILE_CNF(MNC length) is invalid.");
            }
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID
 功能描述  : 读取CS LOC文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : SIM卡内容更新到MML中
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if (NAS_MML_CS_LOCI_SIM_FILE_LEN == pstMsg->usEfLen)
        {
            NAS_MMC_UpdateSimInfoFromCsLociFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(CS location info) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID
 功能描述  : 读取CS CKIK文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : SIM卡内容更新到MML中
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if ( NAS_MML_CS_KEY_USIM_FILE_LEN == pstMsg->usEfLen)
        {
            NAS_MMC_UpdateCsSecutityInfoFromUsimFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(CS CK and IK) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_CS_KC_FILE_ID
 功能描述  : 读取CS KC文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : SIM卡内容更新到MML中
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年8月22日
   作    者   : w00167002
   修改内容   : V7R1 PhaseII 清空的标志不对,导致等待SIM卡回复超时
 5.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 6.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 7.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 8.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_KC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if ( NAS_MML_CS_KC_SIM_FILE_LEN == pstMsg->usEfLen )
        {
            NAS_MMC_UpdateCsSecutityInfoFromUsimFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "Mmc_RcvAgentUsimReadFileCnf:WARNING: The length of USIM_READ_FILE_CNF(CS KC) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "Mmc_RcvAgentUsimReadFileCnf:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID
 功能描述  : 读取PS_KEY文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : SIM卡内容更新到MML中
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
 7.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)

    {
        if ( NAS_MML_PS_KEY_USIM_FILE_LEN == pstMsg->usEfLen )
        {
            NAS_MMC_UpdatePsSecutityInfoFromUsimFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(PS key) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : Mmc_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID
 功能描述  : 读取PS KC文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : SIM卡内容更新到MML中
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年8月22日
   作    者   : w00167002
   修改内容   : V7R1 PhaseII 清空的标志不对,导致等待SIM卡回复超时
 5.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 6.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 7.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if ( NAS_MML_PS_KC_SIM_FILE_LEN == pstMsg->usEfLen )
        {
            NAS_MMC_UpdatePsSecutityInfoFromUsimFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(PS KC) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID
 功能描述  : 读取PS LOC文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : SIM卡内容保存在MML中，获取内容接口更新
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 4.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 5.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 6.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT8                           aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN];

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if ( NAS_MML_PS_LOCI_SIM_FILE_LEN == pstMsg->usEfLen )
        {
            PS_MEM_SET(aucPsLocInfo, (VOS_CHAR)0xFF, NAS_MML_PS_LOCI_SIM_FILE_LEN);

            PS_MEM_CPY(aucPsLocInfo, pstMsg->aucEf, pstMsg->usEfLen );

            /*更新MML和GMM全局变量中相关内容*/
            NAS_MMC_UpdateSimInfoFromPsLociFile(aucPsLocInfo);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(PS location info) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}



/*****************************************************************************
 函 数 名  : Mmc_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID
 功能描述  : 读取PLMN SEL文件
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 5.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 6.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 7.日    期   : 2012年12月26日
   作    者   : 张鹏 /z00214637
   修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
)
{
    VOS_UINT8                           ucPlmnSetNum;
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnSelList = VOS_NULL_PTR;

    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        ucPlmnSetNum   = (VOS_UINT8)(pstMsg->usEfLen / NAS_MML_SIM_PLMN_ID_LEN);
        if ( ucPlmnSetNum > NAS_MML_MAX_SELPLMN_NUM )
        {
            ucPlmnSetNum = NAS_MML_MAX_SELPLMN_NUM;
        }

        pstSelPlmnInfo = NAS_MML_GetSimSelPlmnList();
        pstPlmnSelList = pstSelPlmnInfo->astPlmnId;

        /* 初始化全局变量中的UPLMN信息，然后把SIM中读取的PLMN ID存储到全局变量中 */
        NAS_MML_InitSimSelPlmnInfo(pstSelPlmnInfo);

        for ( i = 0; i < ucPlmnSetNum; i++ )
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstMsg->aucEf + (NAS_MML_SIM_PLMN_ID_LEN * i), NAS_MML_SIM_PLMN_ID_LEN);

            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &pstPlmnSelList[i]);
        }

        /* 保存SELPLMN的个数 */
        pstSelPlmnInfo->ucSelPlmnNum = ucPlmnSetNum;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PLMN_SEL_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID
 功能描述  : 获取卡文件ACTING-HPLMN的内容
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目新增函数
  2.日    期   : 2012年12月26日
    作    者   : 张鹏 /z00214637
    修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK

*****************************************************************************/
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo   = VOS_NULL_PTR;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity   = VOS_NULL_PTR;

    PS_MEM_SET(&stPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if (pstMsg->usEfLen >= NAS_MML_SIM_PLMN_ID_LEN)
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstMsg->aucEf, NAS_MML_SIM_PLMN_ID_LEN);
            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
            {
                pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

                /* 初始化全局变量中的EHPLMN信息 */
                NAS_MML_InitSimEhPlmnInfo(pstEHPlmnInfo);

                pstEHPlmnInfo->ucEhPlmnNum                  = 1;
                pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId    = stPlmn;

                /* 更新当前HPLMN的类型 */
                NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_ACTING_HPLMN);

                return;
            }
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    pstMsIdentity = NAS_MML_GetSimMsIdentity();

    /* ACTING-HPLMN读取失败或无效，需要将HPLMN更新为IMSI中的HPLMN */
    NAS_MMC_UpdateHomePlmn(pstMsIdentity->aucImsi);

    /* 更新当前HPLMN的类型 */
    NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_HPLMN);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAgentUsimReadFileCnf
 功能描述  : 读取SIM卡文件的处理
 输入参数  : pstMsg:PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU消息的首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月22日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2011年12月03日
   作    者   : w00166186
   修改内容   : DTS2011112907465,读USIM失败后导致开机慢
 3.日    期   : 2012年5月12日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年5月16日
   作    者   : w00176964
   修改内容   : DTS2012051600755:清除读取文件FLG到switch on状态机中
 5.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 6.日    期   : 2015年03月09日
   作    者   : y00245242
   修改内容   : 迭代9开发
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvAgentUsimReadFileCnf(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
)
{
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &enEfId))
    {
        return;
    }

    switch ( enEfId )
    {
        case USIMM_USIM_EFHPLMNwACT_ID:
        case USIMM_GSM_EFHPLMNACT_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFFPLMN_ID:
        case USIMM_GSM_EFFPLMN_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFPLMNWACT_ID:
        case USIMM_GSM_EFPLMNWACT_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_UPLMN_SEL_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFOPLMNWACT_ID:
        case USIMM_GSM_EFOPLMNWACT_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_OPLMN_SEL_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFHPPLMN_ID:
        case USIMM_GSM_EFHPLMN_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFAD_ID:
        case USIMM_GSM_EFAD_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFLOCI_ID:
        case USIMM_GSM_EFLOCI_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFKEYS_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID(pstMsg);
            break;

        /* 增加对SIM卡中的cskc文件读取 */
        case USIMM_GSM_EFKC_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_CS_KC_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFKEYSPS_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID(pstMsg);
            break;

        /* 增加对SIM卡中的PSkc文件读取处理 */
        case USIMM_GSM_EFKCGPRS_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFPSLOCI_ID:
        case USIMM_GSM_EFLOCIGPRS_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID(pstMsg);
            break;

        /* 增加对SIM卡中的cskc文件读取 */
        case USIMM_GSM_EFPLMNSEL_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_PLMN_SEL_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFEHPLMN_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID(pstMsg);
            break;

        case USIMM_ATTGSM_EFACTINGHPLMN_ID:
        case USIMM_ATTUSIM_EFACTINGHPLMN_ID:

            NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFEHPLMNPI_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID(pstMsg);
            break;

        case USIMM_USIM_EFLRPLMNSI_ID:
            NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID(pstMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "Mmc_RcvAgentUsimReadFileCnf:WARNING: File Id Abnormal");
            break;
    }

    return ;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePtmsiFormPsLociFile
 功能描述  : 根据PSLOCI文件的内容更新PTMSI的内容
 输入参数  : pucPsLociFileContent:USIM中EFPSLOCI的内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年1月2日
   作    者   : w00167002
   修改内容   : DTS2011111100902:当从6F73文件中取得PTMSI有效性信息的时候，也
                 需要判断当前LAI是否有效。
                 LAI中的值为FFFE/FFFF，则认为LAI无效；
                 若LAI全0，则认为RAI无效；
                 若PLMN ID无效，则也不更新PTMSI信息；
                 若PTMSI无效，则显示的赋值，因为NVIM中存储的PTMSI可能跟文件中的
                 不一致。

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdatePtmsiFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucInvalidCnt;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    VOS_UINT8                           ucCurrPos;
    VOS_UINT32                          ulValidPtmsiFlag;

    PS_MEM_SET(&stSimPlmnId, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    PS_MEM_SET(&stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    /* 默认PTMSI有效 */
    ulValidPtmsiFlag    = VOS_TRUE;

    ucInvalidCnt        = 0;
    pstMsIdentity       = NAS_MML_GetSimMsIdentity();

    /* 位置区无效,则PTMSI的内容肯定是无效的,直接返回 */
    if ( (NAS_MML_LAC_LOW_BYTE_INVALID == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_BEG])
      && ( (NAS_MML_LAC_LOW_BYTE_INVALID == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_END])
        || (NAS_MML_LAC_HIGH_BYTE_INVALID == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_END])))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid LAC FFFF OR FFFE");


        /* 不能直接RETURN,而需要显示的更新当前的PTMSI为无效值，譬如NV中的保存的
          是有效的，但文件中的是无效的，则以最后读取的为准 */
        ulValidPtmsiFlag = VOS_FALSE;
    }


    /* 位置区被设置为全0，则认为RAI无效,则PTMSI的内容肯定是无效的 TS24008:10.5.1.3 */
    if ( (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_BEG])
      && (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_END]) )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid LAC,ALL ZEROS");

        ulValidPtmsiFlag = VOS_FALSE;
    }

    /* 取得SIM卡中的PLMN ID信息，用于判读PLMN是否有效 */
    ucCurrPos           = NAS_MML_RAI_POS_EFPSLOCI_FILE;

    /* 存储PLMN ID */
    PS_MEM_CPY(stSimPlmnId.aucSimPlmn,
               pucPsLociFileContent + ucCurrPos,
               NAS_MML_SIM_PLMN_ID_LEN);

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmnId, &stPlmnId);

    /* PLMN ID无效，则不更新PTMSI */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&stPlmnId) )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid PLMN ID");

        ulValidPtmsiFlag = VOS_FALSE;
    }

    /* 获取PTMSI的内容 */
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        if (NAS_MML_PTMSI_INVALID == pucPsLociFileContent[i])
        {
            ucInvalidCnt++;
        }
    }

    /* PTMSI有效时才需要更新,由于PTMSI初始化会更新为无效值 */
    if ( NAS_MML_MAX_PTMSI_LEN == ucInvalidCnt )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid PTMSI");


        /* 不能直接RETURN,而需要显示的更新当前的PTMSI为无效值，譬如NV中的保存的
          是有效的，但文件中的是无效的，则以最后读取的为准 */
        ulValidPtmsiFlag = VOS_FALSE;
    }


    /* 若PTMSI无效，则显示更新PTMSI为无效值 */
    if ( VOS_FALSE == ulValidPtmsiFlag )
    {
        for ( i = 0 ; i < NAS_MML_MAX_PTMSI_LEN ; i++ )
        {
            pstMsIdentity->aucPtmsi[i] = NAS_MML_PTMSI_INVALID;
        }

        return;
    }

    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        pstMsIdentity->aucPtmsi[i]  = pucPsLociFileContent[i];
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePtmsiSignatureFormPsLociFile
 功能描述  : 根据PSLOCI文件的内容更新PTMSI Signature的内容
 输入参数  : pucPsLociFileContent:USIM中EFPSLOCI的内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2012年1月2日
   作    者   : w00167002
   修改内容   : DTS2011111100902:需要显式更新PTMSI Signature内容为无效值，
                 因为NVIM中可能保存的是有效值，而卡文件中的是无效值，则以
                 卡文件中的为准。
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdatePtmsiSignatureFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucInvalidCnt;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    ucInvalidCnt        = 0;
    pstMsIdentity       = NAS_MML_GetSimMsIdentity();

    for (i = NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE; i < (NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE + NAS_MML_MAX_PTMSI_SIGNATURE_LEN); i++)
    {
        if (NAS_MML_PTMSI_SIGNATURE_INVALID == pucPsLociFileContent[i])
        {
            ucInvalidCnt++;
        }
    }

    /* PTMSI Signature有效时才需要更新,由于PTMSI Signature初始化会更新为无效值 */
    if (NAS_MML_MAX_PTMSI_SIGNATURE_LEN == ucInvalidCnt)
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiSignatureFormPsLociFile:invalid PTMSISignature");


        /* 更新PTMSI Signature内容为无效值 */
        for ( i = 0 ; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN ; i++ )
        {
            pstMsIdentity->aucPtmsiSignature[i] = NAS_MML_PTMSI_SIGNATURE_INVALID;
        }

        return;
    }

    for (i = 0; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN; i++)
    {
        pstMsIdentity->aucPtmsiSignature[i] = pucPsLociFileContent[i + NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE];
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRaiFormPsLociFile
 功能描述  : 根据PSLOCI文件的内容更新RAI的内容
 输入参数  : pucPsLociFileContent:USIM中EFPSLOCI的内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateRaiFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_PS_DOMAIN_INFO_STRU        *pstPsDomainInfo;
    VOS_UINT8                           ucCurrPos;

    PS_MEM_SET(&stSimPlmnId, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    ucCurrPos           = NAS_MML_RAI_POS_EFPSLOCI_FILE;
    pstPsDomainInfo     = NAS_MML_GetPsDomainInfo();

    /* 存储PLMN ID */
    PS_MEM_CPY(stSimPlmnId.aucSimPlmn,
               pucPsLociFileContent + ucCurrPos,
               NAS_MML_SIM_PLMN_ID_LEN);

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmnId,
                                    &(pstPsDomainInfo->stLastSuccRai.stLai.stPlmnId));

    /* 存储LAC  */
    ucCurrPos += NAS_MML_SIM_PLMN_ID_LEN;
    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[i] = pucPsLociFileContent[ucCurrPos + i];
    }

    if ((NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0])
     && (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1]))
    {
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    /* 如果sim卡中的内容是0xFFFF,则认为LAI为0xFEFF */
    if ((NAS_MML_LAC_LOW_BYTE_INVALID == pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0])
     && (NAS_MML_LAC_LOW_BYTE_INVALID == pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1]))
    {
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    ucCurrPos += NAS_MML_MAX_LAC_LEN;

    /* 存储RAC */
    pstPsDomainInfo->stLastSuccRai.ucRac    = pucPsLociFileContent[ucCurrPos];
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateSimInfoFromPsLociFile
 功能描述  : 根据USIM中的PSLOCI的内容更新MML中保存的SIM相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年12月1日
   作    者   : zhoujun /40661
   修改内容   : 更新保存在MML内存中的EFPSLOCI原始文件的内容
 3.日    期   : 2015年6月14日
   作    者   : z00301431
   修改内容   : DTS2015060309245,以色列updatestatus为0xff，RPLMN全0问题规避
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateSimInfoFromPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;
    VOS_UINT8                           ucUpdateStatus;

    pstSimStatus    = NAS_MML_GetSimStatus();

    /*

    Identifier: '6F73'  Structure: transparent  Mandatory
    SFI: '0C'
    File size: 14 bytes Update activity: high
    Access Conditions:
        READ    PIN
        UPDATE  PIN
        DEACTIVATE  ADM
        ACTIVATE    ADM

    Bytes   Description M/O Length
    1 to 4  P-TMSI  M   4 bytes
    5 to 7  P-TMSI signature value  M   3 bytes
    8 to13  RAI M   6 bytes
    14  Routing Area update status  M   1 byte

    */

    NAS_MML_UpdateSimPsLociFileContent(pucPsLociFileContent);


    /* 更新PTMSI的内容 */
    NAS_MMC_UpdatePtmsiFormPsLociFile(pucPsLociFileContent);

    /* 更新PTMSI SIGNATURE的内容 */
    NAS_MMC_UpdatePtmsiSignatureFormPsLociFile(pucPsLociFileContent);

    /* 更新RAI的内容 */
    NAS_MMC_UpdateRaiFormPsLociFile(pucPsLociFileContent);

    /* 更新GPRS的状态 */
    ucUpdateStatus = pucPsLociFileContent[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1];
    ucUpdateStatus = (ucUpdateStatus) & NAS_MML_UPDATE_STATUS_MASK_IN_SIM;

    if (ucUpdateStatus > NAS_MML_ROUTING_UPDATE_STATUS_BUTT )
    {
        ucUpdateStatus = NAS_MML_ROUTING_UPDATE_STATUS_BUTT;
    }
    pstSimStatus->enPsUpdateStatus  = ucUpdateStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePsSecutityInfoFromUsimFile
 功能描述  : 根据USIM的内容更新MML中保存的变量
 输入参数  : pucPsSecutityInfo:PS域安全参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月13日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

  2.日    期   : 2012年12月1日
    作    者   : w00167002
    修改内容   : DTS2012112704453:cksn的BIT:4时SPARE位，GCF测试需要匹配该项，
                 需要填写值为0.
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdatePsSecutityInfoFromUsimFile(
    VOS_UINT8                          *pucPsSecutityInfo
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;
    NAS_MML_SIM_PS_SECURITY_INFO_STRU  *pstPsSecurityInfo;

    pstSimStatus            = NAS_MML_GetSimStatus();
    pstPsSecurityInfo       = NAS_MML_GetSimPsSecurity();

    /* 存储PS security key */
    if (NAS_MML_SIM_TYPE_USIM == pstSimStatus->enSimType )
    {
        /*
        Identifier: '6F09'  Structure: transparent  Mandatory
        SFI: '08'
        File size: 33 bytes Update activity: high
        Access Conditions:
            READ    PIN
            UPDATE  PIN
            DEACTIVATE  ADM
            ACTIVATE    ADM

        Bytes   Description M/O Length
        1   Key set identifier KSIPS  M   1 byte
        2 to 17 Ciphering key CKPS    M   16 bytes
        18 to 33    Integrity key IKPS    M   16 bytes

        */

        /* 存储CKSN */
        pstPsSecurityInfo->ucCKSN   = (pucPsSecutityInfo[0] & NAS_MML_CKSN_INVALID);

        PS_MEM_CPY(pstPsSecurityInfo->aucUmtsCk,
                   &pucPsSecutityInfo[NAS_MML_CK_POS_EFKEY_FILE],
                   NAS_MML_UMTS_CK_LEN);

        PS_MEM_CPY(pstPsSecurityInfo->aucUmtsIk,
                   &pucPsSecutityInfo[NAS_MML_CK_POS_EFKEY_FILE + NAS_MML_UMTS_CK_LEN],
                   NAS_MML_UMTS_IK_LEN);

        NAS_MML_SecContext3GTO2G(pstPsSecurityInfo->aucUmtsIk,
                                 pstPsSecurityInfo->aucUmtsCk,
                                 pstPsSecurityInfo->aucGsmKc);
    }
    else
    {
        /*
        Identifier: '6F52'  Structure: transparent  Mandatory
        File size: 9 bytes  Update activity: high
        Bytes   Description M/O Length
        1 to 8  Ciphering key KcGPRS    M   8 bytes
        9   Ciphering key sequence number n M   1 byte
        */

        pstPsSecurityInfo->ucCKSN   = (pucPsSecutityInfo[NAS_MML_GSM_KC_LEN] & NAS_MML_CKSN_INVALID);

        PS_MEM_CPY(pstPsSecurityInfo->aucGsmKc,
                   pucPsSecutityInfo,
                   NAS_MML_GSM_KC_LEN);

        NAS_MML_SecContext2GTO3G(pstPsSecurityInfo->aucUmtsIk,
                                 pstPsSecurityInfo->aucUmtsCk,
                                 pstPsSecurityInfo->aucGsmKc);
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateTmsiFormCsLociFile
 功能描述  : 根据LOCI文件的内容更新TMSI的内容
 输入参数  : pucCsLociFileContent:USIM中EFLOCI的内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2012年1月2日
   作    者   : w00167002
   修改内容   : DTS2011111100902:当从6F7E文件中取得TMSI有效性信息的时候，也
                 需要判断当前LAI是否有效。
                 若LAI全0，则认为LAI无效；
                 若PLMN ID 无效，则也不更新TMSI信息。
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateTmsiFormCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucInvalidCnt;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    VOS_UINT8                          *pucLaiPos;

    VOS_UINT32                          ulValidTmsiFlag;

    PS_MEM_SET(&stSimPlmnId, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    PS_MEM_SET(&stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    /* 默认TMSI有效 */
    ulValidTmsiFlag    = VOS_TRUE;

    ucInvalidCnt        = 0;
    pstMsIdentity       = NAS_MML_GetSimMsIdentity();

    /* 位置区无效,则TMSI的内容肯定是无效的,直接返回 */
    /* 参考31.102, 4.2.17章节, 定义了相应位置的字节含义 */
    if ( ( NAS_MML_LAC_LOW_BYTE_INVALID == pucCsLociFileContent[7] )
      && ( (NAS_MML_LAC_LOW_BYTE_INVALID == pucCsLociFileContent[8])
        || (NAS_MML_LAC_HIGH_BYTE_INVALID == pucCsLociFileContent[8])))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateTmsiFormCsLociFile:invalid LAC");


        /* 不能直接RETURN,而需要显示的更新当前的PTMSI为无效值，譬如NV中的保存的
          是有效的，但文件中的是无效的，则以最后读取的为准 */
        ulValidTmsiFlag = VOS_FALSE;
    }


     /* 位置区被设置为全0，则认为RAI无效,则PTMSI的内容肯定是无效的 TS24008:10.5.1.3 */
    if ( (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pucCsLociFileContent[7])
      && (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pucCsLociFileContent[8]) )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid LAC,ALL ZEROS");


        /* 不能直接RETURN,而需要显示的更新当前的TMSI为无效值，譬如NV中的保存的
          是有效的，但文件中的是无效的，则以最后读取的为准 */
        ulValidTmsiFlag = VOS_FALSE;
    }

    /* 取得SIM卡中的PLMN ID信息，用于判读PLMN是否有效 */
    pucLaiPos             = pucCsLociFileContent +  NAS_MML_LAI_POS_EFLOCI_FILE;

    /* 存储PLMN ID */
    PS_MEM_CPY(stSimPlmnId.aucSimPlmn,
               pucLaiPos,
               NAS_MML_SIM_PLMN_ID_LEN);

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmnId, &stPlmnId);

    /* PLMN ID无效，则不更新TMSI */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&stPlmnId) )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateTmsiFormCsLociFile:invalid PLMN ID");


        /* 不能直接RETURN,而需要显示的更新当前的TMSI为无效值，譬如NV中的保存的
          是有效的，但文件中的是无效的，则以最后读取的为准 */
        ulValidTmsiFlag = VOS_FALSE;
    }

    for (i = 0; i < NAS_MML_MAX_TMSI_LEN; i++)
    {
        if (NAS_MML_TMSI_INVALID == pucCsLociFileContent[i])
        {
            ucInvalidCnt++;
        }
    }

    if ( NAS_MML_MAX_TMSI_LEN == ucInvalidCnt )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateTmsiFormCsLociFile:invalid TMSI");

        /* 不能直接RETURN,而需要显示的更新当前的TMSI为无效值，譬如NV中的保存的
          是有效的，但文件中的是无效的，则以最后读取的为准 */
        ulValidTmsiFlag = VOS_FALSE;
    }


    /* 若TMSI无效，则显式更新TMSI为无效值 */
    if ( VOS_FALSE == ulValidTmsiFlag )
    {
        for ( i = 0 ; i < NAS_MML_MAX_TMSI_LEN ; i++ )
        {
            pstMsIdentity->aucTmsi[i] = NAS_MML_TMSI_INVALID;
        }

        return;
    }

    for (i = 0; i < NAS_MML_MAX_TMSI_LEN; i++ )
    {
        pstMsIdentity->aucTmsi[i] = pucCsLociFileContent[i];
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateLaiFormCsLociFile
 功能描述  : 根据LOCI文件的内容更新LAI的内容
 输入参数  : pucCsLociFileContent:USIM中EFLOCI的内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateLaiFormCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
)
{
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_CS_DOMAIN_INFO_STRU        *pstCsDomainInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucLaiPos = VOS_NULL_PTR;
    VOS_UINT32                          i;

    PS_MEM_SET(&stSimPlmnId, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    pstCsDomainInfo       = NAS_MML_GetCsDomainInfo();
    pucLaiPos             = pucCsLociFileContent +  NAS_MML_LAI_POS_EFLOCI_FILE;

    /* 存储PLMN ID */
    PS_MEM_CPY(stSimPlmnId.aucSimPlmn,
               pucLaiPos,
               NAS_MML_SIM_PLMN_ID_LEN);

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmnId,
                                    &(pstCsDomainInfo->stLastSuccLai.stPlmnId));


    /* 存储LAI */
    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        pstCsDomainInfo->stLastSuccLai.aucLac[i] = *(pucLaiPos + NAS_MML_SIM_PLMN_ID_LEN + i);
    }

    if ((NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pstCsDomainInfo->stLastSuccLai.aucLac[0])
     && (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pstCsDomainInfo->stLastSuccLai.aucLac[1]))
    {
        pstCsDomainInfo->stLastSuccLai.aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstCsDomainInfo->stLastSuccLai.aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    /* 如果sim卡中的内容是0xFFFF,则认为LAI为0xFEFF */
    if ((NAS_MML_LAC_LOW_BYTE_INVALID == pstCsDomainInfo->stLastSuccLai.aucLac[0])
     && (NAS_MML_LAC_LOW_BYTE_INVALID == pstCsDomainInfo->stLastSuccLai.aucLac[1]))
    {
        pstCsDomainInfo->stLastSuccLai.aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstCsDomainInfo->stLastSuccLai.aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateSimInfoFromCsLociFile
 功能描述  : 根据USIM中的LOCI的内容更新MML中保存的SIM相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年12月1日
   作    者   : zhoujun /40661
   修改内容   : 更新保存在MML内存中的EFLOCI原始文件的内容
 2.日    期   : 2012年1月2日
   作    者   : w00167002
   修改内容   : DTS2011111100902:UPDATE STATUS状态无效时，则更新为U2,表示RPLMN不存在。
 3.日    期   : 2015年6月14日
   作    者   : z00301431
   修改内容   : DTS2015060309245,以色列updatestatus为0xff，RPLMN全0问题规避
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateSimInfoFromCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT8                           ucUpdateStatus;

    pstSimStatus    = NAS_MML_GetSimStatus();

    /*
    Identifier: '6F7E'  Structure: transparent  Mandatory
    SFI: '0B'
    File size: 11 bytes Update activity: high
    Access Conditions:
        READ    PIN
        UPDATE  PIN
        DEACTIVATE  ADM
        ACTIVATE    ADM

    Bytes   Description M/O Length
    1 to 4  TMSI    M   4 bytes
    5 to 9  LAI M   5 bytes
    10  RFU M   1 byte
    11  Location update status  M   1 byte
    */

    NAS_MML_UpdateSimCsLociFileContent(pucCsLociFileContent);

    /* 更新PTMSI的内容 */
    NAS_MMC_UpdateTmsiFormCsLociFile(pucCsLociFileContent);

    /* 更新LAI的内容 */
    NAS_MMC_UpdateLaiFormCsLociFile(pucCsLociFileContent);

    /* 更新CS域的状态 */
    ucUpdateStatus = pucCsLociFileContent[NAS_MML_CS_LOCI_SIM_FILE_LEN - 1];
    ucUpdateStatus = (ucUpdateStatus) & NAS_MML_UPDATE_STATUS_MASK_IN_SIM;

    if (ucUpdateStatus > NAS_MML_LOCATION_UPDATE_STATUS_BUTT)
    {
        ucUpdateStatus = NAS_MML_LOCATION_UPDATE_STATUS_BUTT;
    }

    pstSimStatus->enCsUpdateStatus  = ucUpdateStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateCsSecutityInfoFromUsimFile
 功能描述  : 根据USIM的内容更新MML中保存的变量
 输入参数  : pucCsSecutityInfo:CS域安全参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2012年12月1日
   作    者   : w00167002
   修改内容   : DTS2012112704453:cksn的BIT:4时SPARE位，GCF测试需要匹配该项，
                需要填写值为0.
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateCsSecutityInfoFromUsimFile(
    VOS_UINT8                          *pucCsSecutityInfo
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;
    NAS_MML_SIM_CS_SECURITY_INFO_STRU  *pstCsSecurityInfo;

    pstSimStatus            = NAS_MML_GetSimStatus();
    pstCsSecurityInfo       = NAS_MML_GetSimCsSecurity();

    /* 存储CS security key */
    if (NAS_MML_SIM_TYPE_USIM == pstSimStatus->enSimType )
    {
        /*
        Identifier: '6F08'  Structure: transparent  Mandatory
        SFI: '08'
        File size: 33 bytes Update activity: high
        Access Conditions:
            READ    PIN
            UPDATE  PIN
            DEACTIVATE  ADM
            ACTIVATE    ADM

        Bytes   Description M/O Length
        1   Key set identifier KSI  M   1 byte
        2 to 17 Ciphering key CK    M   16 bytes
        18 to 33    Integrity key IK    M   16 bytes
        */
        /* 存储CKSN */
        pstCsSecurityInfo->ucCKSN   = (pucCsSecutityInfo[0] & NAS_MML_CKSN_INVALID);

        PS_MEM_CPY(pstCsSecurityInfo->aucUmtsCk,
                   &pucCsSecutityInfo[NAS_MML_CK_POS_EFKEY_FILE],
                   NAS_MML_UMTS_CK_LEN);

        PS_MEM_CPY(pstCsSecurityInfo->aucUmtsIk,
                   &pucCsSecutityInfo[NAS_MML_CK_POS_EFKEY_FILE + NAS_MML_UMTS_CK_LEN],
                   NAS_MML_UMTS_IK_LEN);

        NAS_MML_SecContext3GTO2G(pstCsSecurityInfo->aucUmtsIk,
                                 pstCsSecurityInfo->aucUmtsCk,
                                 pstCsSecurityInfo->aucGsmKc);
    }
    else
    {
        /*

        Identifier: '6F20'  Structure: transparent  Mandatory
        File size: 9 bytes  Update activity: high
        Access Conditions:
            READ    CHV1
            UPDATE  CHV1
            INVALIDATE  ADM
            REHABILITATE    ADM

        Bytes   Description M/O Length
        1 to 8  Ciphering key Kc    M   8 bytes
        9   Ciphering key sequence number n M   1 byte

        */

        pstCsSecurityInfo->ucCKSN   = (pucCsSecutityInfo[NAS_MML_GSM_KC_LEN] & NAS_MML_CKSN_INVALID);

        PS_MEM_CPY(pstCsSecurityInfo->aucGsmKc,
                   pucCsSecutityInfo,
                   NAS_MML_GSM_KC_LEN);

        NAS_MML_SecContext2GTO3G(pstCsSecurityInfo->aucUmtsIk,
                                 pstCsSecurityInfo->aucUmtsCk,
                                 pstCsSecurityInfo->aucGsmKc);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmPlmn
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmPlmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFFPLMN_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFFPLMN_ID;
    }

    /* 读取PLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmEfad
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmEfad(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFAD_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFAD_ID;
    }

    /* 读取EFAD */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmUplmn
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmUplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFPLMNWACT_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFPLMNWACT_ID;
    }

    /* 读取UPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmOplmn
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmOplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFOPLMNWACT_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFOPLMNWACT_ID;
    }

    /* 读取OPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmHplmn
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmHplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFHPLMNwACT_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFHPLMNACT_ID;
    }

    /* 读取HPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmLoci
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmCSLoci(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFLOCI_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFLOCI_ID;
    }

    /* 读取CS LOCI*/
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmAtt
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmAtt(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_ATTUSIM_EFACTINGHPLMN_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_ATTGSM_EFACTINGHPLMN_ID;
    }

    /* 读取ATT */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmEhplmn
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmEhplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    /* 读取EHPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_USIM_EFEHPLMN_ID,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmEhplmnpi
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmEhplmnpi(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    /* 读取EHPLMNPI */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_USIM_EFEHPLMNPI_ID,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmLrplmnsi
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmLrplmnsi(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    /* 读取LRPLMNSI */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_USIM_EFLRPLMNSI_ID,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmHpplmn
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmHpplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFHPPLMN_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFHPLMN_ID;
    }

    /* 读取HPPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUsimmFile
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmFile(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo,
    VOS_UINT16                          usFileId
)
{
    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    /* 读取 usFileId对应文件 */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}



/*****************************************************************************
 函 数 名  : NAS_MMC_SndUsimReadFileReq
 功能描述  : 发起获取USIM文件内容请求到USIM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年7月25日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 全局变量 状态名调整
 3.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 4.日    期  : 2012年12月26日
   作    者  : 张鹏 id:00214637
   修改内容  : USIM对外接口函数变更的处理 ，
               Client ID 到 PID的转换处理 ，入参封装成结构体。
 5.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改
 6.日    期   : 2013年10月15日
   作    者   : x65241
   修改内容   : 电信定制OPLMN调整修改
 7.日    期   : 2013年07月27日
   作    者   : y00245242
   修改内容   : 为开发VOLTE，适配新的USIM接口
 8.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID   NAS_MMC_SndUsimReadFileReq( VOS_VOID )
{
    VOS_UINT32                          ulRet;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    NAS_MML_HPLMN_CFG_INFO_STRU        *pstHplmnCfgInfo = VOS_NULL_PTR;

    VOS_UINT32                          ulNvOplmnAvail = VOS_FALSE;

    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;


    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    pstSimStatus    = NAS_MML_GetSimStatus();

    NAS_MMC_ReadUsimmPlmn(&stGetFileInfo);

    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_FORBIDDEN_PLMN_LIST_FILE_ID_FLG);

    NAS_MMC_ReadUsimmEfad(&stGetFileInfo);

    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_MNC_LENGTH_FILE_ID_FLG);

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_UPLMN_SEL_WACT);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

    if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
    {
        NAS_MMC_ReadUsimmUplmn(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_UPLMN_SEL_FILE_ID_FLG);
    }

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_SEL_WACT);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

    ulNvOplmnAvail = NAS_MML_IsNvimOplmnAvail();
    if ((PS_USIM_SERVICE_AVAILIABLE == ulRet)
     && (VOS_FALSE == ulNvOplmnAvail))
    {
        NAS_MMC_ReadUsimmOplmn(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_OPLMN_SEL_FILE_ID_FLG);
    }

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_HPLMN_WACT);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

    if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
    {
        NAS_MMC_ReadUsimmHplmn(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_HPLMN_SEL_FILE_ID_FLG);
    }

    NAS_MMC_ReadUsimmCSLoci(&stGetFileInfo);

    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_LOC_FILE_ID_FLG);

    /* ACTING-HPLMN特性开关打开时需要获取ACTING-HPLMN，否则读取EHPLMN */
    if (VOS_TRUE == pstHplmnCfgInfo->ucActingHPlmnSupportFlg)
    {
        NAS_MMC_ReadUsimmAtt(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_ACTING_HPLMN_FILE_ID_FLG);
    }
    else
    {
        /* EHPLMN特性开关打开时才需要获取 */
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_EHPLMN);
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

        if ( (VOS_TRUE == pstHplmnCfgInfo->ucEhplmnSupportFlg)
          && (PS_USIM_SERVICE_AVAILIABLE == ulRet))
        {
            NAS_MMC_ReadUsimmEhplmn(&stGetFileInfo);

            NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_EHPLMN_FILE_ID_FLG);
        }
    }

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_EHPLMN_IND);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

    if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
    {
        NAS_MMC_ReadUsimmEhplmnpi(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_EHPLMNPI_FILE_ID_FLG);
    }

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_RPLMN_LACT);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

    if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
    {
        NAS_MMC_ReadUsimmLrplmnsi(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_LRPLMNSI_FILE_ID_FLG);
    }

    NAS_MMC_ReadUsimmHpplmn(&stGetFileInfo);

    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG);

    if ( NAS_MML_SIM_TYPE_SIM == pstSimStatus->enSimType)
    {
        /* 读取PS LOCI */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_GSM_EFLOCIGPRS_ID);  /* NAS_MML_READ_SIM_PS_LOC_FILE_ID */

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_LOC_FILE_ID_FLG);

        /* 读取CS KC */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_GSM_EFKC_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_KC_FILE_ID_FLG);

        /* 读取PS KC */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_GSM_EFKCGPRS_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_KC_FILE_ID_FLG);

        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_SELECTOR);
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

        if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            /* SIM卡下替代UPLMN和OPLMN */
            NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_GSM_EFPLMNSEL_ID);

            NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PLMN_SEL_FILE_ID_FLG);
        }
    }
    else
    {
        /* 读取PS LOCI */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_USIM_EFPSLOCI_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_LOC_FILE_ID_FLG);

        /* 读取CS CK IK */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_USIM_EFKEYS_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_CKIK_FILE_ID_FLG);

        /* 读取PS KEY */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_USIM_EFKEYSPS_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_KEY_FILE_ID_FLG);
    }
}




/*****************************************************************************
 函 数 名  : NAS_MMC_SndUsimUpdateForbPlmnReq
 功能描述  : 发起更新USIM文件内容请求到USIM模块
 输入参数  : 希望更新的文件ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月26日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年12月26日
   作    者   : 张鹏 id:00214637
   修改内容   : USIM对外接口函数变更的处理 ，
                Client ID 到 PID的转换处理 ，入参封装成结构体。
 3.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改
 4.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID NAS_MMC_SndUsimUpdateForbPlmnReq(VOS_VOID)
{
    VOS_UINT8                          *pucFileContent = VOS_NULL_PTR;          /* 指向File内容的指针                       */
    VOS_UINT8                           ucForbPlmnNum;                          /* MMC forbidden PLMN的个数                 */
    VOS_UINT8                           ucUsimForbPlmnNum;                      /* MMC forbidden PLMN的个数                 */
    VOS_UINT8                           i;                                      /* 循环控制变量                             */
    VOS_UINT8                           ucDif;                                  /* MMC与SIM中forbidden PLMN个数之差         */
    VOS_UINT8                           ucSetUsimPlmnNum;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;
    VOS_UINT16                          usFileId;

    usFileId = USIMM_DEF_FILEID_BUTT;
    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    pstForbidPlmnInfo           = NAS_MML_GetForbidPlmnInfo();
    ucForbPlmnNum               = pstForbidPlmnInfo->ucForbPlmnNum;
    ucUsimForbPlmnNum           = pstForbidPlmnInfo->ucUsimForbPlmnNum;
    ucSetUsimPlmnNum            = pstForbidPlmnInfo->ucUsimForbPlmnNum;

    pucFileContent = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, ucUsimForbPlmnNum * 3);

    if (VOS_NULL_PTR == pucFileContent)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MMC_SndUsimUpdateForbPlmnReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET(pucFileContent, 0, ucUsimForbPlmnNum * 3);

    /* 将MMC内部的forbidden PLMN转化为SIM中的格式 */
    if (ucForbPlmnNum >= ucUsimForbPlmnNum)
    {
        /* MMC forbidden PLMN的个数>=SIM中的个数    */
        ucDif = ucForbPlmnNum - ucUsimForbPlmnNum;

        /* 将MMC中最新的ucUsimForbPlmnNum个forbidden PLMN转化为SIM中的格式 */
        /* 参见3GPP 31.102, 4.2.16章节，对于SIM卡文件格式的描述*/
        for (i=0; i < ucUsimForbPlmnNum; i++)
        {
            *(pucFileContent + (i*3))
              = (VOS_UINT8)(0x0000000F & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMcc);

            *(pucFileContent + (i*3))
             |= (VOS_UINT8)((0x00000F00 & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMcc) >> 4);

            *(pucFileContent + (i*3) + 1)
             = (VOS_UINT8)((0x000F0000 & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMcc) >> 16);

            *(pucFileContent + (i*3) + 1)
             |= (VOS_UINT8)((0x000F0000 & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMnc) >> 12);

            *(pucFileContent + (i*3) + 2)
             = (VOS_UINT8)(0x0000000F & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMnc);

            *(pucFileContent + (i*3) + 2)
             |= (VOS_UINT8)((0x00000F00 & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMnc) >> 4);
        }
    }
    else
    {
        /* MMC forbidden PLMN的个数小于SIM中的个数 */
        if (NAS_MML_MAX_FORBPLMN_NUM > ucUsimForbPlmnNum)
        {
            ucDif = ucUsimForbPlmnNum - ucForbPlmnNum;
        }
        else
        {
            ucDif = NAS_MML_MAX_FORBPLMN_NUM - ucForbPlmnNum;

            /* 不更新USIM内超出UE支持范围的FPLMN */
            ucSetUsimPlmnNum = NAS_MML_MAX_FORBPLMN_NUM;
        }

        /* 将MMC中forbidden PLMN转化为SIM中的格式 */
        /* 参见3GPP 31.102, 4.2.16章节，对于SIM卡文件格式的描述 */
        for (i=0; i < ucForbPlmnNum; i++)
        {
            *(pucFileContent + (i*3))
              = (VOS_UINT8)(0x0000000F & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMcc);

            *(pucFileContent + (i*3))
             |= (VOS_UINT8)((0x00000F00 & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMcc) >> NAS_MML_OCTET_MOVE_FOUR_BITS);

            *(pucFileContent + (i*3) + 1)
             = (VOS_UINT8)((0x000F0000 & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMcc) >> NAS_MML_OCTET_MOVE_SIXTEEN_BITS);
            *(pucFileContent + (i*3) + 1)
             |= (VOS_UINT8)((0x000F0000 & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMnc) >> NAS_MML_OCTET_MOVE_TWELVE_BITS);

            *(pucFileContent + (i*3) + 2)
             = (VOS_UINT8)(0x0000000F & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMnc);

            *(pucFileContent + (i*3) + 2)
             |= (VOS_UINT8)((0x00000F00 & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMnc) >> NAS_MML_OCTET_MOVE_FOUR_BITS);
        }

        /* 剩余空间用oxFF埴充  */
        PS_MEM_SET((pucFileContent + (ucForbPlmnNum*3)), (VOS_CHAR)0xFF, (ucDif*3));

    }

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFFPLMN_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFFPLMN_ID;
    }

    NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0,
                                    (VOS_UINT8)(ucSetUsimPlmnNum*NAS_MML_SIM_FORMAT_PLMN_LEN),
                                    pucFileContent);

    (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_MMC, 0, &stSetFileInfo);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_FPLMN_LIST,
                    pucFileContent, (i*3));

    /* 释放空间  */
    PS_MEM_FREE(WUEPS_PID_MMC, pucFileContent);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertSimPlmnToNasPLMN
 功能描述  : 将SIM卡中的3字节格式PLMN转换为MCC和MNC分开的格式
 输入参数  : aucEFplmn[3]
 输出参数  : 无
 返 回 值  :MMC_PLMN_ID_STRU
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年1月21日
   作    者   : likelai
   修改内容   : 新生成函数

 2.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : SIM卡内容更新到MML中
*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertSimPlmnToNasPLMN(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
)
{

    VOS_UINT32                          ulTempData;
    NAS_MML_PLMN_ID_STRU                stPlmn;

    /*
       PLMN BCD 编码 方式

       MCC digit 2,  MCC digit 1, ----OCTET 1
       MNC digit 3,  MCC digit 3, ----OCTET 2
       MNC digit 2,  MNC digit 1, ----OCTET 3
    */
    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[0]);
    stPlmn.ulMcc = ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[0])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[1]);
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[1])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;

    stPlmn.ulMnc = ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[2]);
    stPlmn.ulMnc |= ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[2])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMnc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    *pstNasPlmn = stPlmn;


    return ;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertNasPlmnToSimFormat
 功能描述  : 将MCC和MNC分开的格式转换为Sim的3字节格式PLMN(LAI格式的PLMN)
            (10.5.1.3 Location Area Identification)
             8 7 6 5     4 3 2 1
            Location Area Identification IEI       octet 1
            MCC digit 2     MCC digit 1            octet 2
            MNC digit 3     MCC digit 3            octet 3
            MNC digit 2     MNC digit 1            octet 4

            例如:230,02f (mcc:0x000302,mnc:0x0f0200)  --> 32f020

 输入参数  : pGUNasPlmn,GUNAS格式的PLMN ID
 输出参数  : pstSimPlmn:Sim格式的PLMN ID
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月6日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertNasPlmnToSimFormat(
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn,
    NAS_MML_SIM_FORMAT_PLMN_ID         *pstSimPlmn
)
{
    pstSimPlmn->aucSimPlmn[0]
      = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMcc);
    pstSimPlmn->aucSimPlmn[0]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMcc) >> 4);

    pstSimPlmn->aucSimPlmn[1]
     = (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMcc) >> 16);

    pstSimPlmn->aucSimPlmn[1]
     |= (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMnc) >> 12);

    pstSimPlmn->aucSimPlmn[2]
     = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMnc);
    pstSimPlmn->aucSimPlmn[2]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMnc) >> 4);

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ConverPlmnInfoFromSim
 功能描述  : 将SIM卡中保存的信息转换为内存中保存的Plmn Info的信息
 输入参数  : pucData,       卡文件中的信息
              ulPlmnNum，    卡文件中的PLMN个数
 输出参数  : pstPlmnWithRat, plmn id的信息和接入技术
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_ConverPlmnInfoFromSim(
    VOS_UINT8                          *pucUsimFileData,
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnWithRat
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU                stTempPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;
    VOS_UINT16                          usTempData;

    PS_MEM_SET(&stTempPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    
    for ( i = 0; i < ulPlmnNum; i++ )
    {
        /*
            31102
            1 to 3 PLMN (highest priority) M 3 bytes st
            4 to 5 PLMN Access Technology Identifier M 2 bytes
        */

        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pucUsimFileData + (i * NAS_MML_PLMN_WITH_RAT_UNIT_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* 转换PLMN ID为MMC内部的格式并存储 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stTempPlmn);
        pstPlmnWithRat[i].stPlmnId = stTempPlmn;

        /* 存储PLMN对应的RAT */
        usTempData = (VOS_UINT16)(pucUsimFileData[(i * NAS_MML_PLMN_WITH_RAT_UNIT_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                                | pucUsimFileData[(i * NAS_MML_PLMN_WITH_RAT_UNIT_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];
        pstPlmnWithRat[i].usSimRat = usTempData;

    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSndStkSearchModeChgEvt
 功能描述  : 判断是否需要给stk发送search mode改变事件，SVLTE形态下，如果没有CS域能力，无需上报该事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报；VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSndStkSearchModeChgEvt(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
    {
       if (VOS_TRUE == NAS_MML_IsCsServDomainAvail(NAS_MML_GetMsMode()))
       {
           return VOS_TRUE;
       }
       return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }

}


/* Added by l00208543 for STK升级 2013-07-23, begin */
/*****************************************************************************
 Prototype    : NAS_MMC_ConvertSrchModeToStkSrchMode
 Description  : 将MMC的搜网类型转为上报给STK的搜网类型
 Input        : ucReselMode -- AUTO:0，MANUAL:1；
 Output       : None
 Return Value : 上报给STK的搜网类型
 Calls        :
 Called By    : NAS_MMC_SndStkSearchModeChgEvt

  History        :
 1.日    期   : 2013年7月23日
   作    者   : l00208543
   修改内容   : Created

*****************************************************************************/

TAF_PH_PLMN_SEL_MODE NAS_MMC_ConvertSrchModeToStkSrchMode(
                                         VOS_UINT8 ucReselMode
                                         )
{
    switch (ucReselMode)
    {
        case NAS_MMC_PLMN_SELECTION_MODE_AUTO:
             return TAF_PH_PLMN_SEL_MODE_AUTO;

        case NAS_MMC_PLMN_SELECTION_MODE_MANUAL:
             return TAF_PH_PLMN_SEL_MODE_MANUAL;

        default:
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_ConvertSrchModeToStkSrchMode: The input is invalid");
            return TAF_PH_PLMN_SEL_MODE_BUTT;
    }
}

/* Added by l00208543 for STK升级 2013-07-23, end */

/*****************************************************************************
 Prototype    : NAS_MMC_SndStkSearchModeChgEvt
 Description  : 搜网模式变化上报USIM
 Input        : ucReselMode -- AUTO:0，MANUAL:1；
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
 1.日    期   : 2009年12月17日
   作    者   : x00115505
   修改内容   : Created
 2.日    期   : 2011年7月20日
   作    者   : L00171473
   修改内容   : V7R1 phase II 修改
 3.日    期   : 2013年6月4日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改
 4.日    期   : 2013年7月13日
   作    者   : l00208543
   修改内容   : STK升级项目

*****************************************************************************/
VOS_VOID NAS_MMC_SndStkSearchModeChgEvt(
    VOS_UINT8                           ucReselMode
)
{
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-13, begin */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLength;
    NAS_STK_SRCHMODE_CHG_EVENT_STRU    *pstSearchModeChgEvent = VOS_NULL_PTR;

    ulMsgLength    = sizeof(NAS_STK_SRCHMODE_CHG_EVENT_STRU);

    pstSearchModeChgEvent = (NAS_STK_SRCHMODE_CHG_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                           (ulMsgLength - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstSearchModeChgEvent)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_SndStkSearchModeChgEvt: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(&(pstSearchModeChgEvent->stSrchModeChgEvent), 0, sizeof(NAS_STK_SRCHMODE_CHG_EVENT_INFO_STRU));

    pstSearchModeChgEvent->ulReceiverPid = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstSearchModeChgEvent->ulMsgId       = ID_NAS_STK_NET_SRCH_MODE_CHG_EVENT;

    pstSearchModeChgEvent->stSrchModeChgEvent.ucSrchMode = NAS_MMC_ConvertSrchModeToStkSrchMode(ucReselMode);

    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstSearchModeChgEvent);
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_SndStkSearchModeChgEvt: Send Msg Fail!");
        return;
    }

    NAS_EventReport(WUEPS_PID_MMC,
                    NAS_OM_EVENT_STK_NETWORK_SEARCH_MODE_CHANGE_EVENT,
                    (VOS_VOID *)&ucReselMode,
                    NAS_OM_EVENT_STK_NETWORK_SEARCH_MODE_CHANGE_LEN);


    return;
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-13, end */
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateOPlmnInfoFromNvim
 功能描述  : 读取NV中的OPLMN文件，并保存到MML全局变量中,该函数会覆盖MML中保存卡
             文件中OPLMN信息的全局变量，即NV中用户设置的OPLMN列表与卡文件中的互斥
 输入参数  :     VOS_UINT8                          *pucOPlmnData,
                 VOS_UINT16                          usOPlmnNum
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月15日
   作    者   : s00190137
   修改内容   : 新生成函数
 2.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateOPlmnInfoFromNvim(
    VOS_UINT8                         *pucOPlmnData,
    VOS_UINT16                         usOPlmnNum
)
{
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstOplmnAddr    = VOS_NULL_PTR;

    /* 获取全局变量的地址 */
    pstOperPlmnInfo = NAS_MML_GetSimOperPlmnList();
    pstOplmnAddr    = pstOperPlmnInfo->astOperPlmnInfo;

    /* 初始化全局变量中的OPLMN信息，然后把SIM中读取的PLMN ID和RAT存储到全局变量中 */
    NAS_MML_InitSimOperPlmnInfo(pstOperPlmnInfo);

    /* 将NV中保存的用户设置的OPLMN信息转换为内存中的信息 */
    NAS_MMC_ConverPlmnInfoFromSim(pucOPlmnData, usOPlmnNum, pstOplmnAddr);

    /* 保存OPLMN的个数 */
    pstOperPlmnInfo->usOperPlmnNum = usOPlmnNum;

    return;
}



/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, Begin */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetUsimAllRefreshFileNumber
 功能描述  : 获取g_astNasUsimAllRefreshFileID数组元素数目，最大不超过USIMM_MAX_REFRESH_FILE_NUM
 输入参数  : 无
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月05日
   作    者   : c00318887
   修改内容   : 新生成函数
2.日    期   : 2015年07月30日
  作    者   : c00318887
  修改内容   : 卡接口变化，增加类型区分USIM，sim卡
*****************************************************************************/
VOS_UINT8  NAS_MMC_GetUsimAllRefreshFileNumber(VOS_VOID)
{
    VOS_UINT8                   ucNumber;
    NAS_MML_SIM_TYPE_ENUM_UINT8 ucSimType = NAS_MML_GetSimType();

    /* Modified by  for c00318887 for file refresh需要触发背景搜, 2015-7-30, begin */
    if (NAS_MML_SIM_TYPE_USIM == ucSimType)
    {
        ucNumber = sizeof(g_astNasUsimAllRefreshFileID)/sizeof(g_astNasUsimAllRefreshFileID[0]);
    }
    else if (NAS_MML_SIM_TYPE_SIM == ucSimType)
    {
        ucNumber = sizeof(g_astNasGsmAllRefreshFileID)/sizeof(g_astNasGsmAllRefreshFileID[0]);
    }
    else
    {
        ucNumber = 0;
    }
    /* Modified by  for c00318887 for file refresh需要触发背景搜, 2015-7-30, end */

    return ucNumber;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetUsimRefreshFileNumber
 功能描述  : 获取g_astNasUsimAllRefreshFileID数组元素中的file id
 输入参数  : ucIndex---数组下标
 输出参数  : file id
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月05日
   作    者   : c00318887
   修改内容   : 新生成函数
2.日    期   : 2015年07月30日
  作    者   : c00318887
  修改内容   : 卡接口变化，增加类型区分USIM，sim卡
*****************************************************************************/
VOS_UINT16  NAS_MMC_GetUsimAllRefreshFileId(VOS_UINT8 ucIndex)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8 ucSimType = NAS_MML_GetSimType();

    /* Modified by  for c00318887 for file refresh需要触发背景搜, 2015-7-30, begin */
    if (NAS_MML_SIM_TYPE_USIM == ucSimType)
    {
        if (NAS_MMC_GetUsimAllRefreshFileNumber() <= ucIndex)
        {
            return USIMM_DEF_FILEID_BUTT;
        }

        return g_astNasUsimAllRefreshFileID[ucIndex];
    }
    else if (NAS_MML_SIM_TYPE_SIM == ucSimType)
    {
        if (NAS_MMC_GetUsimAllRefreshFileNumber() <= ucIndex)
        {
            return USIMM_DEF_FILEID_BUTT;
        }

        return g_astNasGsmAllRefreshFileID[ucIndex];
    }
    else
    {
        return USIMM_DEF_FILEID_BUTT;
    }
    /* Modified by  for c00318887 for file refresh需要触发背景搜, 2015-7-30, end */
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildRefreshFileList
 功能描述  : 高优先级网络文件更新时构建更新文件结构
 输入参数  : pstUsimRefreshInd  --- USIM 卡文件更新消息
 输出参数  : pstRefreshFile     --- 统计实际更新的文件列表和个数
 返 回 值  : 无
             
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月28日
   作    者   : c00318887
   修改内容   : 新生成函数
 2.日    期   : 2015年07月30日
   作    者   : c00318887
   修改内容   : 卡接口变化，增加类型区分USIM，sim卡

*****************************************************************************/
VOS_VOID NAS_MMC_BuildRefreshFileList(
    USIMM_STKREFRESH_IND_STRU                  *pstUsimRefreshInd,
    NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU    *pstRefreshFile
)
{
    VOS_UINT32      ulLoop;
    VOS_UINT16      usFileId;
    VOS_UINT16      usNumber;
    VOS_UINT16      usIndex;
    
    /* file list 类型时，copy 消息体的EF ID */
    if (USIMM_REFRESH_FILE_LIST == pstUsimRefreshInd->enRefreshType)
    {
        pstRefreshFile->usEfNum = pstUsimRefreshInd->usEfNum;
        
        if (USIMM_MAX_REFRESH_FILE_NUM < pstRefreshFile->usEfNum)
        {
            pstRefreshFile->usEfNum = USIMM_MAX_REFRESH_FILE_NUM;
        }

        
        for (ulLoop = 0; ulLoop < pstRefreshFile->usEfNum; ulLoop++)
        {
            PS_MEM_CPY(&pstRefreshFile->astRefreshFile[ulLoop], &pstUsimRefreshInd->astEfId[ulLoop], sizeof(USIM_REFRESH_FILE_STRU)); 
        }

        return;
        
    }

    /* Modified by  for c00318887 for file refresh需要触发背景搜, 2015-7-30, begin */
    /* ALL FILE 类型时，认为FILE ID 是能触发高优先级搜网的文件，并且根据卡类型分开读 */  
    usNumber = NAS_MMC_GetUsimAllRefreshFileNumber();
    usIndex  = 0;
    
    for (ulLoop = 0; ulLoop < usNumber; ulLoop++)
    {
        usFileId = NAS_MMC_GetUsimAllRefreshFileId((VOS_UINT8)ulLoop);

        if (USIMM_DEF_FILEID_BUTT == usFileId)
        {
            continue;
        }

        pstRefreshFile->astRefreshFile[usIndex].usFileId     = usFileId;
        pstRefreshFile->astRefreshFile[usIndex].enAppType    = USIMM_GUTL_APP; 
        
        pstRefreshFile->astRefreshFile[usIndex].usPathLen    = 0;
        PS_MEM_SET(pstRefreshFile->astRefreshFile[usIndex].aucPath, 0x0, sizeof(pstRefreshFile->astRefreshFile[usIndex].aucPath));
    
        usIndex++;
    }
    
    pstRefreshFile->usEfNum = usIndex;
    /* Modified by  for c00318887 for file refresh需要触发背景搜, 2015-7-30, end */
}
/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


