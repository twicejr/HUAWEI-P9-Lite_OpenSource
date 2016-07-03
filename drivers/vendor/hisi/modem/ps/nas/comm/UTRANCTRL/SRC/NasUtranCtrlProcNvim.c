

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

#include "NasNvInterface.h"
#include "TafNvInterface.h"

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

