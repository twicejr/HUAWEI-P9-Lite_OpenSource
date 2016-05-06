/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NASUTRANCTRLProcNvim.c
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : NASUTRANCTRLProcNvim.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasComm.h"
#include "NVIM_Interface.h"
#include "SysNvId.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasUtranCtrlInterface.h"
#include "NasMmlLib.h"
#include "NasUtranCtrlMntn.h"
#include "NasUtranCtrlCommFunc.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_PROC_NVIM_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/




/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义

*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim
 功能描述  : 从NV中获取en_NV_Item_Utran_Mode_Auto_Switch NV项内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月8日
    作    者   : w00167002
    修改内容   : 新建
  2.日    期   : 2012年8月14日
    作    者   : w00176964
    修改内容   : 增加当前UTRAN的切换模式控制变量
  3.日    期   : 2012年10月20日
    作    者   : w00167002
    修改内容   : DTS2012102001400:多模CDRX何如V7R1C50BUGFIX,NAS删除关于低功耗桩
                 处理。
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim( VOS_VOID )
{
    NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU         *pstNvimUtranModeAutoSwitch;
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU              *pstUtranModeAutoSwitch;
    VOS_UINT32                                              i;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;

    pstUtranModeAutoSwitch = NAS_UTRANCTRL_GetUtranModeAutoSwtich();

    pstNvimUtranModeAutoSwitch = (NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU *)
                                 PS_MEM_ALLOC(WUEPS_PID_MMC,
                                              sizeof(NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU));

    /* 内存申请失败直接退出 */
    if ( VOS_NULL_PTR == pstNvimUtranModeAutoSwitch )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim():ERROR: Mem alloc fail ! ");
        return;
    }

    if ( NV_OK != NV_Read( en_NV_Item_Utran_Mode_Auto_Switch,
                           pstNvimUtranModeAutoSwitch,
                           sizeof(NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU)) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim():ERROR: en_NV_Item_Utran_Mode_Auto_Switch read Error");

        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimUtranModeAutoSwitch);

        return;
    }

    /* 将NV中的UTRAN SWITCH MODE内容拷贝到内存中保存 */
    pstUtranModeAutoSwitch->ucUtranSwitchMode = pstNvimUtranModeAutoSwitch->ucUtranSwitchMode;


    /* 如果当前的TD的MCC的个数超过了最大值，则取最大值，此处进行国家码个数有效性保护 */
    if ( pstNvimUtranModeAutoSwitch->ucTdMccListNum > NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM )
    {
        pstNvimUtranModeAutoSwitch->ucTdMccListNum  = NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM;
    }

    for (i = 0 ; i < pstNvimUtranModeAutoSwitch->ucTdMccListNum; i++)
    {
        /* 如果当前的MCC有效，则将NV中的MCC LIST内容拷贝到内存中保存 */
        if ( VOS_TRUE == NAS_MML_IsMccValid(pstNvimUtranModeAutoSwitch->aulTdMccList[i]) )
        {
            pstUtranModeAutoSwitch->aulTdMccList[pstUtranModeAutoSwitch->ucTdMccListNum] = pstNvimUtranModeAutoSwitch->aulTdMccList[i];

            pstUtranModeAutoSwitch->ucTdMccListNum++;
        }
    }

    /* IMSI PLMN个数为任意IMSI则直接返回 */
    if (NAS_UTRANCTRL_SUPPORT_ALL_SIM_AUTO_SWITCH_UTRAN_NUM == pstNvimUtranModeAutoSwitch->ucImsiPlmnListNum)
    {
        pstUtranModeAutoSwitch->ucImsiPlmnListNum = NAS_UTRANCTRL_SUPPORT_ALL_SIM_AUTO_SWITCH_UTRAN_NUM;

        /* 可维可测UTRAN模式自动切换信息打印 */
        NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo();

        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimUtranModeAutoSwitch);

        return;
    }

    /* 如果当前的TD的Plmn的个数超过了最大值，则取最大值，保护当前的PLMN ID网络个数 */
    if ( pstNvimUtranModeAutoSwitch->ucImsiPlmnListNum > NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM )
    {
        pstNvimUtranModeAutoSwitch->ucImsiPlmnListNum = NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM;
    }

    for (i = 0 ; i < pstNvimUtranModeAutoSwitch->ucImsiPlmnListNum; i++)
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstNvimUtranModeAutoSwitch->astImsiPlmnList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
        NAS_UTRANCTRL_ConvertSimPlmnToNasPlmn(&stSimPlmn, &stPlmn);

        /* 判断当前的PLMN ID是否有效，若有效则拷贝到内存中 */
        if ( VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn) )
        {
            pstUtranModeAutoSwitch->astImsiPlmnList[pstUtranModeAutoSwitch->ucImsiPlmnListNum] = stPlmn;

            pstUtranModeAutoSwitch->ucImsiPlmnListNum++;
        }
    }

    /* 可维可测UTRAN模式自动切换信息打印 */
    NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo();

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimUtranModeAutoSwitch);

    return;
}






/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ReadUtranModeNvim
 功能描述  : 从NV中获取en_NV_Item_Current_Utran_Mode NV项内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 新建
  2.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:删除FEATURE_UE_MODE_TDS宏判断
  3.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年5月30日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ReadUtranModeNvim( VOS_VOID )
{
    NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU  stUtranMode;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stUtranMode, 0x00, sizeof(NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Utran_Mode, &ulLength);
    if (ulLength > sizeof(stUtranMode))
    {
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Utran_Mode, &stUtranMode, ulLength) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ReadUtranModeNvim():WARNING: en_NV_Item_Utran_Mode Error");

        return;
    }

    /* 将NVIM中读取的UTRAN模式保存到NASUTRANCTRL中的全局变量中 */
    NAS_UTRANCTRL_SetCurrUtranMode(stUtranMode.ucUtranMode);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ReadSmcCtrlFlgNvim
 功能描述  : 从NV中获取en_NV_Item_SMC_Ctrl_Flg NV项内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月19日
    作    者   : w00167002
    修改内容   : 新建

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ReadSmcCtrlFlgNvim( VOS_VOID )
{
    NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU                   stSmcCtrlFlg;

    PS_MEM_SET(&stSmcCtrlFlg, 0x00, sizeof(NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU));

    if ( NV_OK != NV_Read(en_NV_Item_SMC_Ctrl_Flg, &stSmcCtrlFlg, sizeof(NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU)) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ReadSmcCtrlFlgNvim():WARNING: en_NV_Item_SMC_Ctrl_Flg Error");

        return;
    }

    /* NV中的异常原因值转换 */
    if ( (VOS_FALSE != stSmcCtrlFlg.ucIsUtranTddCsSmcNeeded)
      && (VOS_TRUE  != stSmcCtrlFlg.ucIsUtranTddCsSmcNeeded))
    {
        stSmcCtrlFlg.ucIsUtranTddCsSmcNeeded = VOS_TRUE;
    }

    if ( (VOS_FALSE != stSmcCtrlFlg.ucIsUtranTddPsSmcNeeded)
      && (VOS_TRUE  != stSmcCtrlFlg.ucIsUtranTddPsSmcNeeded))
    {
        stSmcCtrlFlg.ucIsUtranTddPsSmcNeeded = VOS_TRUE;
    }

    /* 保存NVIM中的UTRAN TDD模式下是否需要检测SMC流程值 */
    NAS_UTRANCTRL_SetUtranTddCsSmcNeededFlg(stSmcCtrlFlg.ucIsUtranTddCsSmcNeeded);
    NAS_UTRANCTRL_SetUtranTddPsSmcNeededFlg(stSmcCtrlFlg.ucIsUtranTddPsSmcNeeded);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_WriteUtranModeNvim
 功能描述  : 将UTRAN模式写入NV:en_NV_Item_Current_Utran_Mode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 新建

  2.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:删除FEATURE_UE_MODE_TDS宏判断
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_WriteUtranModeNvim(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enCurrentUtranMode
)
{
    NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU  stUtranMode;
    VOS_UINT32                          ulNvLength;

    stUtranMode.ucReserve   = 0;
    stUtranMode.ucUtranMode = enCurrentUtranMode;
    ulNvLength              = 0;

    /* 从NV中获取en_NV_Item_Utran_Mode NV项内容 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Utran_Mode, &ulNvLength);
    if ( NV_OK != NV_Write(en_NV_Item_Utran_Mode, &stUtranMode, ulNvLength) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_WriteUtranModeNvim:ERROR: NV_Write Error");

        return;
    }

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

