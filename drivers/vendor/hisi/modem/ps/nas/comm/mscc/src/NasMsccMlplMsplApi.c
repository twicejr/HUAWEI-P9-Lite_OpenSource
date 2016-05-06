


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccMlplMsplApi.h"
#include "NasMsccComFunc.h"
#include "NasMsccCtx.h"
#include "NasMsccMntn.h"
#include "PsCommonDef.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_MLPL_MSPL_API_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetMatchedMsplTableBy3gppInfo
 功能描述  : 拆分原来NAS_MSCC_GetHigherPriMsplSysListThan3gpp，根据输入的系统信息，获取匹配的mspl表
 输入参数  : *pstIn3gppInfo
 输出参数  : 无
 返 回 值  : NAS_MSCC_MSPL_ID_STRU* -- MSPL_INDEX对应的mspl表指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_MSPL_ID_STRU*  NAS_MSCC_GetMatchedMsplTableBy3gppInfo(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo
)
{
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                        stMsplSysList;

    PS_MEM_SET(&stMsplSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_NULL_PTR;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_3GPP;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn3gppInfo;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前3gpp系统匹配的最高优先级MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy3gppSys(pstIn3gppInfo, pstMlpl,
                                                    &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_NULL_PTR;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* 在MSPL列表中找到MSPL_INDEX对应的MSPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_NULL_PTR;
    }

    NAS_MSCC_GetSysListFromMsplTable(pstMatchedMsplTable, &stMsplSysList);

    stLogMatchRsltInput.pstMsplSysList     = &stMsplSysList;
    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return pstMatchedMsplTable;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetHigherPriSysListWithMsplTable
 功能描述  : 根据匹配到的mspl表，获取更高优先级的系统
             拆分原来NAS_MSCC_GetHigherPriMsplSysListThan3gpp
 输入参数  : *pstIn3gppInfo
             *pstMatchedMsplTable -- MSPL_INDEX对应的mspl表指针
             enInMlplMatchLvl     -- MLPL表匹配等级
             ucInIsUseDfltMlplRec -- 是否使用默认mlpl
             ucInMatchedMsplIndex -- 匹配的MSPL_INDEX
 输出参数  : *pstOutSysList -- 输出所有比当前系统更高优先级的系统
 返 回 值  : VOS_TRUE  -- 在mspl中找到匹配当前系统的mspl下标
             VOS_FALSE -- 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数
  2.日    期   : 2016年1月14日
    作    者   : w00176964
    修改内容   : DTS2016011505496:L到C的BSR场景,LTE在MSPL表中无对应系统类型,开机搜优先级高的
                 HRPD系统,hrpd掉网后,搜到LTE后,未启动BSR定时器搜HRPD
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetHigherPriSysListWithMsplTable(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_3GPP;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn3gppInfo;
    stLogMatchRsltInput.pstMsplSysList = pstOutSysList;

    /* 如果当前MSPL表中无对应的lte系统记录,MATCH必然失败,此时需要进一步
       判定如果有hrpd系统在前面, 也需要认为hrp优先级比lte高 */
    if (VOS_FALSE == NAS_MSCC_IsLteSysTypeExistedInMsplTable(pstMatchedMsplTable))
    {
        /* 无lte系统记录的表,此时lte系统优先级比较低,需要输出当前MSPL表中
           所有记录对应的系统list */

        NAS_MSCC_GetSysListFromMsplTable(pstMatchedMsplTable, pstOutSysList);

        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_BUTT;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplIndex = 0;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;
        stLogMatchRsltInput.ucCurSysTypeNotExistInMspl = VOS_TRUE;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* 在MSPL记录表中找到匹配当前系统的MSPL记录的下标 */
    if (VOS_FALSE == NAS_MSCC_Get3gppMatchedMsplRecIndex(pstIn3gppInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_BUTT;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplIndex = 0;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 如果匹配到MSPL表中的第一条记录，说明是最高优先级，返回 */
    if (0 == ucMatchedMsplRecId)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_BUTT;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplIndex = 0;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* 获取MSPL表中比当前系统优先级高的优选系统列表 */
    NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(pstMatchedMsplTable, ucMatchedMsplRecId,
                                                 pstOutSysList);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_BUTT;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplIndex = 0;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetSysListFromMsplTable
 功能描述  : 将匹配到的mspl表转成系统List
 输入参数  : *pstMatchedMsplTable
 输出参数  : *pstMsplSysList
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : CL_MUTIMODE_OPTIMIZE新增
*****************************************************************************/
VOS_VOID NAS_MSCC_GetSysListFromMsplTable(
    NAS_MSCC_MSPL_ID_STRU              *pstMatchedMsplTable,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU   *pstMsplSysList
)
{
    VOS_UINT8                           ucLoop;

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        return;
    }

    for (ucLoop = 0; ucLoop < pstMatchedMsplTable->ucNumMsplRec; ucLoop++)
    {
        if (VOS_FALSE == pstMatchedMsplTable->astMsplRec[ucLoop].ucIsValid)
        {
            continue;
        }

        pstMsplSysList->astSysList[pstMsplSysList->ucSysCount].enSysType  =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].enSysType;

        pstMsplSysList->astSysList[pstMsplSysList->ucSysCount].enPriClass =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].enPriClass;


        pstMsplSysList->astSysList[pstMsplSysList->ucSysCount].enSysPri   =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].enSysPri;
        pstMsplSysList->astSysList[pstMsplSysList->ucSysCount].ucIsValid  =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].ucIsValid;

        pstMsplSysList->ucSysCount++;
    }

    return;
}


VOS_UINT8 NAS_MSCC_GetHigherPriMsplSysListThan1x(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList = pstOutSysList;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前1x系统匹配的MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* 在MSPL列表中找到MSPL_INDEX对应的MSPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 在MSPL记录表中找到匹配当前系统的MSPL记录的下标 */
    if (VOS_FALSE == NAS_MSCC_Get1xMatchedMsplRecIndex(pstIn1xInfo, pstMatchedMsplTable,
                                                       &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    if (0 == ucMatchedMsplRecId)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* 获取MSPL表中比当前系统优先级高的优选系统列表 */
    NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(pstMatchedMsplTable, ucMatchedMsplRecId,
                                                 pstOutSysList);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_GetHigherPriMsplSysListThanHrpd
Description     :   Get higher prioity systems of HRPD system
Input parameters:   pstInHrpdInfo - HRPD system info
Outout parameters:  pstOutSysList - List of higher priority system,
                                    the previous record has higher priority than the next
Return Value     :  VOS_TRUE  - match success
                    VOS_FALSE - match fail
Modify History:
    1)  Date    :   2015-04-08
        Author  :   y00174758
        Modify content :    Create
    2)  Date    :   2016-01-07
        Author  :   w00176964
        Modify content :DTS2016010602409:CCF用例CL互操作用例11002失败(MSPL表LTE优先,无HRPD系统
                        ,驻留HRPD后,不启动BSR定时器回LTE)
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetHigherPriMsplSysListThanHrpd(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstInHrpdInfo;
    stLogMatchRsltInput.pstMsplSysList = pstOutSysList;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前hrpd系统匹配的MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexByHrpdSys(pstInHrpdInfo, pstMlpl,
                                                    &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* 在MSPL列表中找到MSPL_INDEX对应的MSPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 如果当前MSPL表中无对应的HRPD系统记录,MATCH必然失败,此时需要进一步
       判定如果有LTE系统在前面, 也需要认为LTE优先级比HRPD高 */
    if (VOS_FALSE == NAS_MSCC_IsHrpdSysTypeExistedInMsplTable(pstMatchedMsplTable))
    {
        /* 无HRPD系统记录的表,此时HRPD系统优先级比较低,需要输出当前MSPL表中
           所有记录对应的系统list */

        NAS_MSCC_GetSysListFromMsplTable(pstMatchedMsplTable, pstOutSysList);

        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;
        stLogMatchRsltInput.ucCurSysTypeNotExistInMspl = VOS_TRUE;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }


    /* 在MSPL记录表中找到匹配当前系统的MSPL记录的下标 */
    if (VOS_FALSE == NAS_MSCC_GetHrpdMatchedMsplRecIndex(pstInHrpdInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;

        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;

        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    if (0 == ucMatchedMsplRecId)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* 获取MSPL表中比当前系统优先级高的优选系统列表 */
    NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(pstMatchedMsplTable,
                                                 ucMatchedMsplRecId, pstOutSysList);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetHigherPriMsplSysListThanHrpdBy1xLoc
Description     :   When Mcc in overhead msg is invalid,use 1x sysinfo to get mspl prefer syslist
                    Then use HRPD info to get sys list prefered than hrpd
Input parameters:   NAS_MSCC_1X_SYS_INFO_STRU                              *pstIn1xInfo
                    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo

Output parameters:  NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-5-7
        Author  :   t00323010
        Modify content :    Create
    2)  Date    :   2016-01-07
        Author  :   w00176964
        Modify content :DTS2016010602409:CCF用例CL互操作用例11002失败(MSPL表LTE优先,无HRPD系统
                        ,驻留HRPD后,不启动BSR定时器回LTE)
*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetHigherPriMsplSysListThanHrpdBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose     = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_MSPL_INDEX_OF_1X;
    stLogMatchRsltInput.enSysRat           = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo          = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList     = VOS_NULL_PTR;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前1x系统匹配的MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* 在MSPL列表中找到MSPL_INDEX对应的MSPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR != pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMsplMatchRslt = VOS_TRUE;
    }

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose     = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS_THAN_HRPD_BY_1X_LOC;
    stLogMatchRsltInput.enSysRat           = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD;
    stLogMatchRsltInput.pvSysInfo          = (VOS_VOID *)pstInHrpdInfo;
    stLogMatchRsltInput.pstMsplSysList     = pstOutSysList;
    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
    stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_BUTT;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 如果当前MSPL表中无对应的HRPD系统记录,MATCH必然失败,此时需要进一步
       判定如果有LTE系统在前面, 也需要认为LTE优先级比HRPD高 */
    if (VOS_FALSE == NAS_MSCC_IsHrpdSysTypeExistedInMsplTable(pstMatchedMsplTable))
    {
        /* 无HRPD系统记录的表,此时HRPD系统优先级比较低,需要输出当前MSPL表中
           所有记录对应的系统list */
        NAS_MSCC_GetSysListFromMsplTable(pstMatchedMsplTable, pstOutSysList);

        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;
        stLogMatchRsltInput.ucCurSysTypeNotExistInMspl = VOS_TRUE;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* 在MSPL记录表中找到匹配当前系统的MSPL记录的下标 */
    if (VOS_FALSE == NAS_MSCC_GetHrpdMatchedMsplRecIndex(pstInHrpdInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    if (0 == ucMatchedMsplRecId)
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* 获取MSPL表中比当前系统优先级高的优选系统列表 */
    NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(pstMatchedMsplTable,
                                                 ucMatchedMsplRecId, pstOutSysList);

    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetMatchedMsplTableBy1xLocInfo
Description     :   用1x的位置信息取得对应的mspl table
Input parameters:   pstIn1xInfo 1x输入位置信息
Outout parameters:  penMlplMatchLvl      mlpl匹配级别
                    pucIsUseDfltMlplRec  是否使用缺省的mlpl记录
                    pucMatchedMsplIndex  匹配的msplIndex

Return Value     :  pstMatchedMsplTable mspl表

Modify History:
    1)  Date    :   2015-09-21
        Author  :   y00346957
        Modify content :    Create for DTS2015070910885
*****************************************************************************/
NAS_MSCC_MSPL_ID_STRU* NAS_MSCC_GetMatchedMsplTableBy1xLocInfo(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penMlplMatchLvl,
    VOS_UINT8                                              *pucIsUseDfltMlplRec,
    VOS_UINT8                                              *pucMatchedMsplIndex
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return pstMatchedMsplTable;
    }

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ALL_SYS_OF_1X;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn1xInfo;

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前1x系统匹配的最高优先级MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return pstMatchedMsplTable;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* 在MSPL列表中找到MSPL_INDEX对应的MSPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR != penMlplMatchLvl)
    {
        *penMlplMatchLvl = enMlplMatchLvl;
    }

    if (VOS_NULL_PTR != pucMatchedMsplIndex)
    {
        *pucMatchedMsplIndex = ucMatchedMsplIndex;
    }

    if (VOS_NULL_PTR != pucIsUseDfltMlplRec)
    {
        *pucIsUseDfltMlplRec = ucIsUseDfltMlplRec;
    }
    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return pstMatchedMsplTable;
    }

    return pstMatchedMsplTable;
}

VOS_UINT8 NAS_MSCC_GetMsplSysListBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;
    VOS_UINT8                                               ucMatchedMsplIndex;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    pstMatchedMsplTable= NAS_MSCC_GetMatchedMsplTableBy1xLocInfo(pstIn1xInfo, &enMlplMatchLvl, &ucIsUseDfltMlplRec, &ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        return VOS_FALSE;
    }

    /* 输出当前MSPL表中所有的优选系统 */
    for (ucLoop = 0; ucLoop < pstMatchedMsplTable->ucNumMsplRec; ucLoop++)
    {
        if (VOS_FALSE == pstMatchedMsplTable->astMsplRec[ucLoop].ucIsValid)
        {
            continue;
        }

        pstOutSysList->astSysList[pstOutSysList->ucSysCount].enSysType  =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].enSysType;

        pstOutSysList->astSysList[pstOutSysList->ucSysCount].enPriClass =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].enPriClass;

        pstOutSysList->astSysList[pstOutSysList->ucSysCount].enSysPri   =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].enSysPri;
         pstOutSysList->astSysList[pstOutSysList->ucSysCount].ucIsValid =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].ucIsValid;

        pstOutSysList->ucSysCount++;
    }
    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ALL_SYS_OF_1X;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList = pstOutSysList;

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_GetCurr3gppSysBsrTimerLen
Description     :   Get BSR timer length of 3gpp system
Input parameters:   pstInHrpdInfo - 3gpp system info
Outout parameters:  penOutBsrTimerLen - BSR timer length in unit millisecond
Return Value     :  VOS_TRUE  - match success
                    VOS_FALSE - match fail
Modify History:
    1)  Date    :   2015-04-08
        Author  :   y00174758
        Modify content :    Create
   2.日    期   : 2016年1月14日
     作    者   : w00176964
     修改内容   : DTS2016011505496:L到C的BSR场景,LTE在MSPL表中无对应系统类型,开机搜优先级高的
                  HRPD系统,hrpd掉网后,搜到LTE后,未启动BSR定时器搜HRPD
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetCurr3gppSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    VOS_UINT32                                             *pulOutBsrTimerLenMilliSec
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    VOS_UINT8                                               ucGetBsrTimerLenRslt;

    *pulOutBsrTimerLenMilliSec = 0;

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_3GPP;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn3gppInfo;
    stLogMatchRsltInput.pstMsplSysList = VOS_NULL_PTR;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前3gpp系统匹配的最高优先级MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy3gppSys(pstIn3gppInfo, pstMlpl,
                                                    &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* 在MSPL列表中找到MSPL_INDEX对应的MLPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 如果当前MSPL表中无对应的lte系统记录,MATCH必然失败,此时需要进一步
       判定如果有hrpd系统在前面, 也需要认为hrp优先级比lte高 */
    if (VOS_FALSE == NAS_MSCC_IsLteSysTypeExistedInMsplTable(pstMatchedMsplTable))
    {
        /* 无lte系统记录的表,此时BSR定时器时长无法从MSPL表中取,故取NV中设置的值 */
        *pulOutBsrTimerLenMilliSec = NAS_MSCC_GetSysAcqTimerCfgAddr()->ulBsrTimerLenWithNoMatchedMsplRec;

        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;
        stLogMatchRsltInput.ucCurSysTypeNotExistInMspl = VOS_TRUE;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }


    /* 在MSPL记录表中找到匹配当前系统的MSPL记录的下标 */
    if (VOS_FALSE == NAS_MSCC_Get3gppMatchedMsplRecIndex(pstIn3gppInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 将匹配到的MSPL记录中的BSR定时器枚举转换成毫秒 */
    ucGetBsrTimerLenRslt = NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
                            pstMatchedMsplTable->astMsplRec[ucMatchedMsplRecId].enHigherPriSrchTime,
                            pulOutBsrTimerLenMilliSec);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;
    stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return ucGetBsrTimerLenRslt;
}



VOS_UINT8 NAS_MSCC_GetCurr1xSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    VOS_UINT32                                             *pulOutBsrTimerLenMilliSec
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    VOS_UINT8                                               ucGetBsrTimerLenRslt;

    *pulOutBsrTimerLenMilliSec = 0;

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList = VOS_NULL_PTR;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前1x系统匹配的最高优先级MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* 在MSPL列表中找到MSPL_INDEX对应的MLPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 在MSPL记录表中找到匹配当前系统的MSPL记录的下标 */
    if (VOS_FALSE == NAS_MSCC_Get1xMatchedMsplRecIndex(pstIn1xInfo, pstMatchedMsplTable,
                                                       &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 将匹配到的MSPL记录中的BSR定时器枚举转换成毫秒 */
    ucGetBsrTimerLenRslt = NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
                            pstMatchedMsplTable->astMsplRec[ucMatchedMsplRecId].enHigherPriSrchTime,
                            pulOutBsrTimerLenMilliSec);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;
    stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return ucGetBsrTimerLenRslt;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_GetCurrHrpdSysBsrTimerLen
Description     :   Get BSR timer length of HRPD system
Input parameters:   pstInHrpdInfo - HRPD system info
Outout parameters:  penOutBsrTimerLen - BSR timer length in unit millisecond
Return Value     :  VOS_TRUE  - match success
                    VOS_FALSE - match fail
Modify History:
    1)  Date    :   2015-04-08
        Author  :   y00174758
        Modify content :    Create
    2)  Date    :   2016-01-07
        Author  :   w00176964
        Modify content :DTS2016010602409:CCF用例CL互操作用例11002失败(MSPL表LTE优先,无HRPD系统
                        ,驻留HRPD后,不启动BSR定时器回LTE)
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetCurrHrpdSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    VOS_UINT32                                             *pulOutBsrTimerLenMilliSec
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    VOS_UINT8                                               ucGetBsrTimerLenRslt;

    *pulOutBsrTimerLenMilliSec = 0;

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstInHrpdInfo;
    stLogMatchRsltInput.pstMsplSysList = VOS_NULL_PTR;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前hrpd系统匹配的最高优先级MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexByHrpdSys(pstInHrpdInfo, pstMlpl,
                                                    &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* 在MSPL列表中找到MSPL_INDEX对应的MLPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 如果当前MSPL表中无对应的HRPD系统记录,MATCH必然失败,此时需要进一步
       判定如果有LTE系统在前面, 也需要认为LTE优先级比HRPD高 */
    if (VOS_FALSE == NAS_MSCC_IsHrpdSysTypeExistedInMsplTable(pstMatchedMsplTable))
    {
        /* 无HRPD系统记录的表,此时BSR定时器时长无法从MSPL表中取,故取NV中设置的值 */

        *pulOutBsrTimerLenMilliSec = NAS_MSCC_GetSysAcqTimerCfgAddr()->ulBsrTimerLenWithNoMatchedMsplRec;

        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;
        stLogMatchRsltInput.ucCurSysTypeNotExistInMspl = VOS_TRUE;

        stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* 在MSPL记录表中找到匹配当前系统的MSPL记录的下标 */
    if (VOS_FALSE == NAS_MSCC_GetHrpdMatchedMsplRecIndex(pstInHrpdInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
         stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 将匹配到的MSPL记录中的BSR定时器枚举转换成毫秒 */
    ucGetBsrTimerLenRslt = NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
                            pstMatchedMsplTable->astMsplRec[ucMatchedMsplRecId].enHigherPriSrchTime,
                            pulOutBsrTimerLenMilliSec);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;
    stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return ucGetBsrTimerLenRslt;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetCurrHrpdSysBsrTimerLenBy1xLoc
Description     :   When Mcc in overhead msg is invalid,use 1x sysinfo to get MSPL List
                    Then use Hrpd info to get curr hrpd sys BSR timer len
Input parameters:   NAS_MSCC_1X_SYS_INFO_STRU                              *pstIn1xInfo
                    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo

Output parameters:  VOS_UINT32                                             *pusOutBsrTimerLenMilliSec
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-5-7
        Author  :   t00323010
        Modify content :    Create
    2)  Date    :   2016-01-07
        Author  :   w00176964
        Modify content :DTS2016010602409:CCF用例CL互操作用例11002失败(MSPL表LTE优先,无HRPD系统
                        ,驻留HRPD后,不启动BSR定时器回LTE)
*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetCurrHrpdSysBsrTimerLenBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    VOS_UINT32                                             *pulOutBsrTimerLenMilliSec
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    VOS_UINT8                                               ucGetBsrTimerLenRslt;

    *pulOutBsrTimerLenMilliSec = 0;

    /* 如果MLPL MSPL不可用，直接返回VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose     = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_MSPL_INDEX_OF_1X;
    stLogMatchRsltInput.enSysRat           = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo          = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList     = VOS_NULL_PTR;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* 在MLPL表中找到当前1x系统匹配的最高优先级MLPL记录，返回对应的MLPL记录的MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* 如果在MLPL列表中找不到匹配的MLPL记录，并且Default MLPL可用，获取Default MLPL的MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;

    /* 在MSPL列表中找到MSPL_INDEX对应的MLPL表指针 */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR != pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMsplMatchRslt = VOS_TRUE;
    }

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose     = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN_OF_HRPD_BY_1X_LOC;
    stLogMatchRsltInput.enSysRat           = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD;
    stLogMatchRsltInput.pvSysInfo          = (VOS_VOID *)pstInHrpdInfo;
    stLogMatchRsltInput.pstMsplSysList     = VOS_NULL_PTR;
    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;;
    stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_BUTT;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 如果当前MSPL表中无对应的HRPD系统记录,MATCH必然失败,此时需要进一步
       判定如果有LTE系统在前面, 也需要认为LTE优先级比HRPD高 */
    if (VOS_FALSE == NAS_MSCC_IsHrpdSysTypeExistedInMsplTable(pstMatchedMsplTable))
    {
        /* 无HRPD系统记录的表,此时BSR定时器时长无法从MSPL表中取,故取NV中设置的值 */
        *pulOutBsrTimerLenMilliSec = NAS_MSCC_GetSysAcqTimerCfgAddr()->ulBsrTimerLenWithNoMatchedMsplRec;

        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;
        stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;
        stLogMatchRsltInput.ucCurSysTypeNotExistInMspl = VOS_TRUE;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* 在MSPL记录表中找到匹配当前HRPD系统的MSPL记录的下标 */
    if (VOS_FALSE == NAS_MSCC_GetHrpdMatchedMsplRecIndex(pstInHrpdInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* 将匹配到的MSPL记录中的BSR定时器枚举转换成毫秒 */
    ucGetBsrTimerLenRslt = NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
                            pstMatchedMsplTable->astMsplRec[ucMatchedMsplRecId].enHigherPriSrchTime,
                            pulOutBsrTimerLenMilliSec);

    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;
    stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return ucGetBsrTimerLenRslt;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetMsplIndexBy3gppSys
Description     :   Get MLPL index in MLPL of 3gpp system
Input parameters:   pstInHrpdInfo - HRPD system info
                    pstInMlplInfo - MLPL info
Outout parameters:  pucOutMsplIndex - matched MSPL index
                    penOutMatchLvl  - matched level
Return Value     :  VOS_TRUE  - match success
                    VOS_FALSE - match fail
Modify History:
1)  Date    :   2015-04-08
    Author  :   y00174758
    Modify content : Create
2)  Date    :   2015-04-08
    Author  :   y00174758
    Modify content : 修改PLMN匹配规则，最高优先级改为MCC_MNC
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetMsplIndexBy3gppSys(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    VOS_UINT8                                               ucLoop;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enBestLvl;
    VOS_UINT8                                               ucBestLvlRecId;

    enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucBestLvlRecId = 0;

    for (ucLoop = 0; ucLoop < pstInMlplInfo->stMlplHdr.ucNumMlplRec; ucLoop++)
    {
        enMlplMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        /* 当前系统和单条MLPL记录比较，获取匹配级别 */
        NAS_MSCC_Compare3gppSysWithMlplRec(pstIn3gppInfo, pstInMlplInfo->apstMlplRec[ucLoop],
                                           &enMlplMatchLvl);

        /* 如果匹配到优先级最高的MLPL记录，退出循环 */
        if (NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC == enMlplMatchLvl)
        {
            enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC;
            ucBestLvlRecId = ucLoop;

            break;
        }

        if (enMlplMatchLvl > enBestLvl)
        {
            enBestLvl      = enMlplMatchLvl;
            ucBestLvlRecId = ucLoop;
        }
    }

    if (NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH != enBestLvl)
    {
        *pucOutMsplIndex = pstInMlplInfo->apstMlplRec[ucBestLvlRecId]->ucMsplIndex;
        *penOutMatchLvl  = enBestLvl;

        return VOS_TRUE;
    }

    *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_GetMsplIndexBy1xSys(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    VOS_UINT8                                               ucLoop;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enBestLvl;
    VOS_UINT8                                               ucBestLvlRecId;

    enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucBestLvlRecId = 0;

    for (ucLoop = 0; ucLoop < pstInMlplInfo->stMlplHdr.ucNumMlplRec; ucLoop++)
    {
        enMlplMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        /* 当前系统和单条MLPL记录比较，获取匹配级别 */
        NAS_MSCC_Compare1xSysWithMlplRec(pstIn1xInfo, pstInMlplInfo->apstMlplRec[ucLoop],
                                         &enMlplMatchLvl);

        /* 匹配到优先级最高的MLPL记录，退出循环 */
        if (NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC_LOC == enMlplMatchLvl)
        {
            enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC_LOC;
            ucBestLvlRecId = ucLoop;

            break;
        }

        if (enMlplMatchLvl > enBestLvl)
        {
            enBestLvl      = enMlplMatchLvl;
            ucBestLvlRecId = ucLoop;
        }
    }

    if (NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH != enBestLvl)
    {
        *pucOutMsplIndex = pstInMlplInfo->apstMlplRec[ucBestLvlRecId]->ucMsplIndex;
        *penOutMatchLvl  = enBestLvl;

        return VOS_TRUE;
    }

    *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_GetMsplIndexByHrpdSys(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    VOS_UINT8                                               ucLoop;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enBestLvl;
    VOS_UINT8                                               ucBestLvlRecId;

    enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucBestLvlRecId = 0;

    for (ucLoop = 0; ucLoop < pstInMlplInfo->stMlplHdr.ucNumMlplRec; ucLoop++)
    {
        enMlplMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        /* 当前系统和单条MLPL记录比较，获取匹配级别 */
        NAS_MSCC_CompareHrpdSysWithMlplRec(pstInHrpdInfo, pstInMlplInfo->apstMlplRec[ucLoop],
                                           &enMlplMatchLvl);

        /* 匹配到优先级最高的MLPL记录，退出循环 */
        if (NAS_MSCC_MLPL_MATCH_LVL_MCC_LOC == enMlplMatchLvl)
        {
            enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_MCC_LOC;
            ucBestLvlRecId = ucLoop;

            break;
        }

        if (enMlplMatchLvl > enBestLvl)
        {
            enBestLvl      = enMlplMatchLvl;
            ucBestLvlRecId = ucLoop;
        }
    }

    if (NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH != enBestLvl)
    {
        *pucOutMsplIndex = pstInMlplInfo->apstMlplRec[ucBestLvlRecId]->ucMsplIndex;
        *penOutMatchLvl  = enBestLvl;

        return VOS_TRUE;
    }

    *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    return VOS_FALSE;
}



NAS_MSCC_MSPL_ID_STRU* NAS_MSCC_GetMsplTableByMsplIndex(
    NAS_MSCC_MSPL_STRU                                     *pstInMsplInfo,
    VOS_UINT8                                               ucInMsplIndex
)
{
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;

    for (ucLoop = 0; ucLoop < pstInMsplInfo->stMsplHdr.ucNumMsplId; ucLoop++)
    {
        if ((VOS_TRUE      == pstInMsplInfo->apstMsplId[ucLoop]->ucIsMsplIdValid)
         && (ucInMsplIndex == pstInMsplInfo->apstMsplId[ucLoop]->ucMsplId))
        {
            pstMatchedMsplTable = (pstInMsplInfo->apstMsplId[ucLoop]);

            break;
        }
    }

    return pstMatchedMsplTable;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_Compare3gppSysWithMlplRec
Description     :   Get the result of 3gpp system matching a MLPL record
Input parameters:   pstIn3gppInfo - 3gpp system info
                    pstInMlplRec  - MLPL record info
Outout parameters:  penOutMatchLvl - match level
Return Value     :  VOS_VOID
Modify History:
1)  Date    :   2015-04-08
    Author  :   y00174758
    Modify content : Create
2)  Date    :   2015-06-03
    Author  :   y00174758
    Modify content : Iteration 12: 修改3GPP PLMN匹配规则
*****************************************************************************/
VOS_VOID NAS_MSCC_Compare3gppSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMatchLvl;
    VOS_UINT32                                              ulNasStyleMcc;
    VOS_UINT32                                              ulNasStyleMnc;


    /*
        3GPP匹配规则：

        1）如果TAG_MCC是FALSE，继续匹配TAG_LOC：从TAG_LOC构造PLMN列表，如果匹配成功，则匹配级别为MCC_MNC，否则为不匹配。

        2）PLMN列表构造：先判断TAG_LOC记录中的制式是否和驻留制式匹配，如果不匹配，则跳过该记录
         PLMN_START直接加入PLMN列表，不判断是否在PLMN Selector List中。
           PLMN_RANGE的使用：先在PLMN Selector List中匹配到PLMN_START的下标，
           然后从PLMN_START下标开始，将PLMN Selector List中PLMN_RANGE下标范围内的PLMN加入到PLMN列表。

        3）如果TAG_MCC是TRUE，MCC不同，TAG_MCC、TAG_MNC为不匹配，继续匹配TAG_LOC，
           如果TAG_LOC匹配 则匹配级别为MCC_MNC，否则为该MLPL记录不匹配。

        4）如果TAG_MCC是TRUE，MCC相同，TAG_MNC是TRUE，MNC是通配符或相同，则匹配级别为MCC_MNC；
           如果MNC不是通配符并且不同，TAG_MCC、TAG_MNC为不匹配，继续匹配TAG_LOC。

        5）如果TAG_MCC是TRUE，MCC相同，TAG_MNC是FALSE，匹配级别为MCC，继续匹配TAG_LOC，
           看TAG_LOC是否能匹配到优先级为MCC_MNC的记录。

        6）匹配优先级大小：MCC_MNC > MCC

        代码实现了上面的逻辑
     */

    if (VOS_FALSE == pstInMlplRec->ucIsRecValid)
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC & pstInMlplRec->ucLocParamType))
    {
        ulNasStyleMcc = NAS_MSCC_ConvertMlplMccToNasStyleMcc(pstInMlplRec->stLocParamVal.usMcc);

        if (pstIn3gppInfo->stPlmnId.ulMcc == ulNasStyleMcc)
        {
            enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MCC;

            if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC ==
                    (NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC & pstInMlplRec->ucLocParamType))
            {
                if (NAS_MSCC_MLPL_WILDCARD_MNC == pstInMlplRec->stLocParamVal.usMnc)
                {
                    enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MNC;
                }
                else
                {
                    ulNasStyleMnc = NAS_MSCC_ConvertMlplMncToNasStyleMnc(
                                                                pstInMlplRec->stLocParamVal.usMnc);

                    if (pstIn3gppInfo->stPlmnId.ulMnc == ulNasStyleMnc)
                    {

                        enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MNC;
                    }
                    else
                    {
                        enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
                    }
                }
            }
        }
    }

    /* TAG_MCC和TAG_MNC匹配到最高优先级，返回 */
    if (NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC == enMatchLvl)
    {
        *penOutMatchLvl = enMatchLvl;

        return;
    }

    /* 继续匹配TAG_LOC */
    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG & pstInMlplRec->ucLocParamType))
    {
        if (VOS_TRUE == NAS_MSCC_Is3gppSysWithLocTagMatched(pstIn3gppInfo, pstInMlplRec))
        {
             enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC;
        }
    }

    *penOutMatchLvl = enMatchLvl;

    return;
}



VOS_VOID NAS_MSCC_Compare1xSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMatchLvl;
    VOS_UINT32                                              ulNasStyleMcc;

    /*
     * 1x系统MLPL匹配规则:

     * 如果网络不发MCC，调用代码保证不使用1X信息查找更优系统，匹配结果为不匹配

     * 如果网络下发MCC和MNC，匹配规则和3gpp一致，参考NAS_MSCC_Compare3gppSysWithMlplRec()
       区别在于匹配LOC时，1x比较SID NID range

     * 如果网络只下发MCC，只比较MCC和SID NID，匹配级别里不包含MNC，匹配规则和TAG_MNC不存在时一致

     * 代码实现了上面的逻辑

     */

    if (VOS_FALSE == pstInMlplRec->ucIsRecValid)
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    if ((VOS_FALSE == pstIn1xInfo->ucIsMccValid) || (NAS_MSCC_INVALID_MCC == pstIn1xInfo->ulMcc))
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC & pstInMlplRec->ucLocParamType))
    {
        ulNasStyleMcc = NAS_MSCC_ConvertMlplMccToNasStyleMcc(pstInMlplRec->stLocParamVal.usMcc);

        if (pstIn1xInfo->ulMcc == ulNasStyleMcc)
        {
            enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MCC;
        }
        else
        {
            *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

            return;
        }

        if (VOS_TRUE == pstIn1xInfo->ucIsMncValid)
        {
            if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC ==
                    (NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC & pstInMlplRec->ucLocParamType))
            {
                if (VOS_TRUE == NAS_MSCC_Is1xMncWithMlplMncMatched(pstIn1xInfo->ulMnc,
                                                              pstInMlplRec->stLocParamVal.usMnc))
                {
                    enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MNC;
                }
                else
                {
                    *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

                    return;
                }
            }
        }
    }

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG & pstInMlplRec->ucLocParamType))
    {
      if (VOS_TRUE == NAS_MSCC_Is1xSysWithLocTagMatched(pstIn1xInfo, pstInMlplRec))
      {
        enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_LOC;
      }
    }

    *penOutMatchLvl = enMatchLvl;

    return;
}



VOS_VOID NAS_MSCC_CompareHrpdSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMatchLvl;
    VOS_UINT32                                              ulNasStyleMcc;

    /*
     * HRPD系统MLPL匹配规则:

     * 如果网络不发MCC，调用代码保证不使用HRPD信息查找更优系统，匹配结果为不匹配

     * 如果网络下发MCC和MNC，匹配规则和3gpp一致，参考NAS_MSCC_Compare3gppSysWithMlplRec()
       区别在于匹配LOC时，1x比较SID NID range

     * 如果网络只下发MCC，只比较MCC和SID NID，匹配级别里不包含MNC，匹配规则和TAG_MNC不存在时一致

     * 代码实现了上面的逻辑

     */

    if (VOS_FALSE == pstInMlplRec->ucIsRecValid)
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    if ((VOS_FALSE == pstInHrpdInfo->ucIsMccValid)
     || (NAS_MSCC_INVALID_MCC == pstInHrpdInfo->ulMcc))
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC & pstInMlplRec->ucLocParamType))
    {
        ulNasStyleMcc = NAS_MSCC_ConvertMlplMccToNasStyleMcc(pstInMlplRec->stLocParamVal.usMcc);

        if (pstInHrpdInfo->ulMcc == ulNasStyleMcc)
        {
            enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MCC;
        }
        else
        {
            *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

            return;
        }
    }

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG & pstInMlplRec->ucLocParamType))
    {
      if (VOS_TRUE == NAS_MSCC_IsHrpdSysWithLocTagMatched(pstInHrpdInfo, pstInMlplRec))
      {
        enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_LOC;
      }
    }

    *penOutMatchLvl = enMatchLvl;

    return;
}



VOS_UINT8 NAS_MSCC_Is3gppSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pst3gppInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
)
{
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU                         *pstLocTag     = VOS_NULL_PTR;
    NAS_MSCC_MLPL_SYS_LOC_TAG_3GPP_STRU                    *pstLocTag3gpp = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;

    /* 循环匹配每个LOC_TAG，如果系统类型是3GPP_AI或LTE，判断PLMN是否在PLMN_RANGE范围 */
    for (ucLoop = 0; ucLoop < pstMlplRec->stLocParamVal.ucNumSysLocTag; ucLoop++)
    {
        pstLocTag = &(pstMlplRec->stLocParamVal.astSysLocTag[ucLoop]);

        if (VOS_FALSE == pstLocTag->ucIsLocTagValid)
        {
            continue;
        }

        /* 目前只支持LTE系统 */
        if (VOS_TRUE == NAS_MSCC_IsMlplMsplSysTypeSupportLte(pstLocTag->enSysType))
        {
            pstLocTag3gpp = &(pstLocTag->unSysLocTag.stSysLocTag3GPP);

            /* 判断当前系统的PLMN是否在LOC TAG的PLMN范围内 */
            if (VOS_TRUE == NAS_MSCC_IsSysPlmnInLocTagPlmnRange(&(pst3gppInfo->stPlmnId),
                                                                pstLocTag3gpp->aucPlmnStart,
                                                                pstLocTag3gpp->ucPlmnRange))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}



VOS_UINT8  NAS_MSCC_Is1xSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pst1xInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
)
{
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU                         *pstLocTag         = VOS_NULL_PTR;
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_STRU                *pstLocTagCdma2000 = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;

    /* 循环匹配每个LOC_TAG，如果系统类型是CDMA2000_AI或CDMA2000_1X，判断SID NID是否在SID NID范围 */
    for (ucLoop = 0; ucLoop < pstMlplRec->stLocParamVal.ucNumSysLocTag; ucLoop++)
    {
        pstLocTag = &(pstMlplRec->stLocParamVal.astSysLocTag[ucLoop]);

        if (VOS_FALSE == pstLocTag->ucIsLocTagValid)
        {
            continue;
        }

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == pstLocTag->enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_1X == pstLocTag->enSysType))
        {
            pstLocTagCdma2000 = &(pstLocTag->unSysLocTag.stSysLocTagCdma2000);

            /* 如果SID相同，并且NID Start是通配符或者NID在range范围内，返回TRUE */
            if (pst1xInfo->usSid == pstLocTagCdma2000->usSid)
            {
                if (NAS_MSCC_MLPL_WILDCARD_NID_START == pstLocTagCdma2000->usNidStart)
                {
                    return VOS_TRUE;
                }

                if ((pst1xInfo->usNid >= pstLocTagCdma2000->usNidStart)
                 && (pst1xInfo->usNid <= pstLocTagCdma2000->usNidStart + pstLocTagCdma2000->ucNidRange))
                {
                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}



VOS_UINT8  NAS_MSCC_IsHrpdSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
)
{
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU                         *pstLocTag     = VOS_NULL_PTR;
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_HRPD_STRU           *pstLocTagHrpd = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;

    /* 循环匹配每个LOC_TAG，如果系统类型是CDMA2000_HRPD，判断SubnetID是否相同 */
    for (ucLoop = 0; ucLoop < pstMlplRec->stLocParamVal.ucNumSysLocTag; ucLoop++)
    {
        pstLocTag = &(pstMlplRec->stLocParamVal.astSysLocTag[ucLoop]);

        if (VOS_FALSE == pstLocTag->ucIsLocTagValid)
        {
            continue;
        }

        if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstLocTag->enSysType)
        {
            pstLocTagHrpd = &(pstLocTag->unSysLocTag.stSysLocTagCdma2000Hrpd);

            if (VOS_TRUE == NAS_MSCC_IsSysSubnetIdWithLocTagMatched(pstInHrpdInfo, pstLocTagHrpd))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_Get3gppMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
)
{
    VOS_UINT8                                               ucLoop;

    /* Get matched mspl record in MSPL table*/
    for (ucLoop = 0; ucLoop < pstInMsplTable->ucNumMsplRec; ucLoop++)
    {
        if (VOS_TRUE == NAS_MSCC_Is3gppSysWithMsplRecMatched(pstIn3gppInfo,
                                                    &(pstInMsplTable->astMsplRec[ucLoop])))
        {
            *pucOutMsplRecId = ucLoop;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_Get1xMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
)
{
    VOS_UINT8                                               ucLoop;

    NAS_MSCC_MSPL_SYS_INFO_STRU                            stMsplSysInfo;

    PS_MEM_SET(&stMsplSysInfo, 0x00, sizeof(NAS_MSCC_MSPL_SYS_INFO_STRU));
    /* Get matched mspl record in MSPL table*/
    for (ucLoop = 0; ucLoop < pstInMsplTable->ucNumMsplRec; ucLoop++)
    {
        stMsplSysInfo.ucIsValid  = pstInMsplTable->astMsplRec[ucLoop].ucIsValid;
        stMsplSysInfo.enSysType  = pstInMsplTable->astMsplRec[ucLoop].enSysType;
        stMsplSysInfo.enPriClass = pstInMsplTable->astMsplRec[ucLoop].enPriClass;
        stMsplSysInfo.enSysPri   = pstInMsplTable->astMsplRec[ucLoop].enSysPri;
        if (VOS_TRUE == NAS_MSCC_Is1xSysWithMsplRecMatched(pstIn1xInfo, &stMsplSysInfo))
        {
            *pucOutMsplRecId = ucLoop;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_GetHrpdMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
)
{
    VOS_UINT8                                              ucLoop;

    /* Get matched mspl record in MSPL table*/
    for (ucLoop = 0; ucLoop < pstInMsplTable->ucNumMsplRec; ucLoop++)
    {
        if (VOS_TRUE == NAS_MSCC_IsHrpdSysWithMsplRecMatched(pstInHrpdInfo,
                                                 &(pstInMsplTable->astMsplRec[ucLoop])))
        {
            *pucOutMsplRecId = ucLoop;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_Is3gppSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pst3gppInfo,
    NAS_MSCC_MSPL_REC_STRU                                 *pstMsplRec
)
{
    if (VOS_FALSE == pstMsplRec->ucIsValid)
    {
        return VOS_FALSE;
    }

    /* 目前仅支持LTE制式 */
    if (VOS_RATMODE_LTE != pst3gppInfo->enSysRat)
    {
        return VOS_FALSE;
    }

    if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI != pstMsplRec->enSysType)
     && (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     != pstMsplRec->enSysType))
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY == pstMsplRec->enPriClass)
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF == pstMsplRec->enPriClass)
      && ((NAS_MSCC_PIF_PRI_CLASS_HOME == pst3gppInfo->enPriClass)
       || (NAS_MSCC_PIF_PRI_CLASS_PREF == pst3gppInfo->enPriClass)))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME == pstMsplRec->enPriClass)
     && (NAS_MSCC_PIF_PRI_CLASS_HOME      == pst3gppInfo->enPriClass))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_Is1xSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_SYS_INFO_STRU                            *pstMsplSysInfo
)
{
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8                       en1xPriClass;

    if (VOS_FALSE == pstMsplSysInfo->ucIsValid)
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == pstMsplSysInfo->enSysType)
    {
        en1xPriClass = pstIn1xInfo->enPriClassCdma2000Ai;
    }
    else if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_1X == pstMsplSysInfo->enSysType)
    {
        en1xPriClass = pstIn1xInfo->enPriClassCdma20001x;
    }
    else
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY == pstMsplSysInfo->enPriClass)
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF == pstMsplSysInfo->enPriClass)
      && ((NAS_MSCC_PIF_PRI_CLASS_HOME == en1xPriClass)
       || (NAS_MSCC_PIF_PRI_CLASS_PREF == en1xPriClass)))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME == pstMsplSysInfo->enPriClass)
     && (NAS_MSCC_PIF_PRI_CLASS_HOME      == en1xPriClass))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_IsHrpdSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstHrpdInfo,
    NAS_MSCC_MSPL_REC_STRU                                 *pstMsplRec
)
{
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8                       enHrpdPriClass;

    if (VOS_FALSE == pstMsplRec->ucIsValid)
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == pstMsplRec->enSysType)
    {
        enHrpdPriClass = pstHrpdInfo->enPriClassCdma2000Ai;
    }
    else if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstMsplRec->enSysType)
    {
        enHrpdPriClass = pstHrpdInfo->enPriClassCdma2000Hrpd;
    }
    else
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY == pstMsplRec->enPriClass)
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF == pstMsplRec->enPriClass)
     && ((NAS_MSCC_PIF_PRI_CLASS_HOME == enHrpdPriClass)
      || (NAS_MSCC_PIF_PRI_CLASS_PREF == enHrpdPriClass)))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME == pstMsplRec->enPriClass)
     && (NAS_MSCC_PIF_PRI_CLASS_HOME      == enHrpdPriClass) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_GetHigherSysListThanSpecRecIndexSys
Description     :   Get higher sys by MSPL record ID
                    获取比当前Recoard ID的MSPL记录更优先的MSPL系统列表
Input parameters:   enInPriSrchTime - enum of higher srch time
Outout parameters:  pusOutMillSec   - timer length in millisecond
Return Value     :  VOS_TURE  - SUCCESS
                    VOS_FALSE - FAIL
Modify History:
    1)  Date    :   2015-04-08
        Author  :   y00174758
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                               ucInCurrMsplRecId,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MSPL_SYS_INFO_STRU                            *pstMsplSys = VOS_NULL_PTR;
    VOS_UINT8                                               ucFoundPriMore;
    VOS_INT16                                               sPriMoreRecPos;
    VOS_INT16                                               sLoop;

    ucFoundPriMore = VOS_FALSE;
    sPriMoreRecPos = NAS_MSCC_INVALID_MSPL_REC_ID;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    if ((ucInCurrMsplRecId < 1) || (ucInCurrMsplRecId >= NAS_MSCC_MAX_NUM_MSPL_REC))
    {
        return;
    }

    /* Find the first MORE priority above the matched record */
    /* 从当前记录的上一条记录开始找到第一个优先级为MORE的下标 */
    for (sLoop = (VOS_INT16)(ucInCurrMsplRecId - 1); sLoop >= 0; sLoop--)
    {
        if (VOS_FALSE == pstInMsplTable->astMsplRec[sLoop].ucIsValid)
        {
            continue;
        }

        if (NAS_MSCC_MSPL_SYS_PRI_MORE == pstInMsplTable->astMsplRec[sLoop].enSysPri)
        {
            ucFoundPriMore = VOS_TRUE;
            sPriMoreRecPos = sLoop;
            break;
        }
    }

    /* 如果没有找到优先级为MORE的记录，说明没有更优系统，返回 */
    if (VOS_FALSE == ucFoundPriMore)
    {
        return;
    }

    /* 从下标0开始到MORE下标结束的所有记录比当前记录高， 依次填入列表 */
    /* PCLINT告警屏蔽,wangfei 00351686 已同DE:sunxibo 00246516,工程组:yangguang 00187525确认*/
    /*lint -save -e661 -specific(-e661)*/
    /*lint -save -e662 -specific(-e662)*/
    for (sLoop = 0; sLoop <= sPriMoreRecPos; sLoop++)
    {
        if (VOS_FALSE == pstInMsplTable->astMsplRec[sLoop].ucIsValid)
        {
            continue;
        }

        pstMsplSys              = &(pstOutSysList->astSysList[pstOutSysList->ucSysCount]);
        pstMsplSys->enSysType   = pstInMsplTable->astMsplRec[sLoop].enSysType;
        pstMsplSys->enPriClass  = pstInMsplTable->astMsplRec[sLoop].enPriClass;

        pstMsplSys->enSysPri    = pstInMsplTable->astMsplRec[sLoop].enSysPri;
        pstMsplSys->ucIsValid   = pstInMsplTable->astMsplRec[sLoop].ucIsValid;
        pstOutSysList->ucSysCount++;
    }
    /*lint -restore*/
}


/*****************************************************************************
Function Name   :   NAS_MSCC_IsSysPlmnInLocTagPlmnRange
Description     :   Check if sys PLMN is in PLMN range of MLPL record
Input parameters:   pstSysPlmn   - PLMN of 3gpp sys
                    aucPlmnStart - PLMN start of loc tag
Outout parameters:  None
Return Value     :  VOS_TRUE  - In PLMN range
                    VOS_FALSE - Not in PLMN range
Modify History:
    1)  Date    :   2015-04-08
        Author  :   y00174758
        Modify content :    Create
    2)  Date    :   2015-06-03
        Author  :   y00174758
        Modify content : Iteration 12: 修改3GPP PLMN匹配规则
*****************************************************************************/
VOS_UINT8 NAS_MSCC_IsSysPlmnInLocTagPlmnRange(
    NAS_MSCC_PIF_PLMN_ID_STRU                              *pstSysPlmn,
    VOS_UINT8                                              *aucPlmnStart,
    VOS_UINT8                                               ucPlmnRange
)
{
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU                    *pstPrefPlmnList = VOS_NULL_PTR;
    NAS_MSCC_SIM_FORMAT_PLMN_ID_STRU                        stPlmnStartSimFmt;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnStart;
    VOS_UINT16                                              usPrefPlmnCnt;
    VOS_UINT16                                              usPrefPlmnIndex;
    VOS_UINT16                                              usPlmnRangeIndex;
    VOS_UINT16                                              usPlmnRangeIndexStart;
    VOS_UINT16                                              usPlmnRangeIndexEnd;

    PS_MEM_SET(&stPlmnStartSimFmt, 0, sizeof(NAS_MSCC_SIM_FORMAT_PLMN_ID_STRU));
    PS_MEM_CPY(stPlmnStartSimFmt.aucSimPlmn, aucPlmnStart, NAS_MSCC_SIM_FORMAT_PLMN_LEN);

    NAS_MSCC_ConvertSimPlmnToNasPlmn(&stPlmnStartSimFmt, &stPlmnStart);

    /* 如果PLMN_START中的MCC是通配符，该PLMN_START无效，直接返回VOS_FALSE */
    if (NAS_MSCC_MLPL_WILDCARD_MCC == stPlmnStart.ulMcc)
    {
        return VOS_FALSE;
    }

    /* 先判断PLMN_START是否匹配，如果匹配，直接返回匹配成功 */
    if (VOS_TRUE == NAS_MSCC_ComparePlmn(pstSysPlmn, &stPlmnStart))
    {
        return VOS_TRUE;
    }

    pstPrefPlmnList = (NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                         NAS_MSCC_MAX_PREF_PLMN_NUM * sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));

    if (VOS_NULL_PTR == pstPrefPlmnList)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pstPrefPlmnList, 0,
                    NAS_MSCC_MAX_PREF_PLMN_NUM * sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));

    usPrefPlmnCnt = 0;

    NAS_MSCC_GeneratePrefPlmnList(pstPrefPlmnList, &usPrefPlmnCnt);

    if (0 == usPrefPlmnCnt)
    {
        PS_MEM_FREE(UEPS_PID_MSCC, pstPrefPlmnList);

        return VOS_FALSE;
    }

    /* 先找到PLMN_START对应的列表下标，当前系统的PLMN匹配的记录 */
    for (usPrefPlmnIndex = 0; usPrefPlmnIndex < usPrefPlmnCnt; usPrefPlmnIndex++)
    {
        if (VOS_TRUE == NAS_MSCC_ComparePlmn(&(pstPrefPlmnList[usPrefPlmnIndex].stPlmnId),
                                             &stPlmnStart))
        {
            break;
        }
    }

    /* 如果没有找到PLMN_START对应的列表下标，驻留的PLMN不在PLMN Range范围，返回VOS_FALSE */
    if (usPrefPlmnIndex >= usPrefPlmnCnt)
    {
        PS_MEM_FREE(UEPS_PID_MSCC, pstPrefPlmnList);

        return VOS_FALSE;
    }

    usPlmnRangeIndexStart = usPrefPlmnIndex;
    usPlmnRangeIndexEnd   = usPrefPlmnIndex + ucPlmnRange;

    if (usPlmnRangeIndexEnd >= usPrefPlmnCnt)
    {
        usPlmnRangeIndexEnd = usPrefPlmnCnt -1;
    }

    /* 判断当前系统的PLMN是否在PLMN_START和PLMN_RANGE范围内 */
    for (usPlmnRangeIndex  = usPlmnRangeIndexStart;
         usPlmnRangeIndex <= usPlmnRangeIndexEnd;
         usPlmnRangeIndex++)
    {
        if (VOS_TRUE == NAS_MSCC_ComparePlmn(&(pstPrefPlmnList[usPlmnRangeIndex].stPlmnId),
                                              pstSysPlmn))
        {
            PS_MEM_FREE(UEPS_PID_MSCC, pstPrefPlmnList);

            return VOS_TRUE;
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstPrefPlmnList);

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_IsSysSubnetIdWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstHrpdInfo,
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_HRPD_STRU           *pstLocTagHrpd
)
{
    VOS_UINT8                                               ucByteCnt;
    VOS_UINT8                                               ucRemainBitCnt;
    VOS_UINT8                                               ucSysSubnetIdRemainValue;

    /* TAG_LOC中SubnetID长度为0，返回FALSE */
    if (0 == pstLocTagHrpd->ucSubnetLen)
    {
        return VOS_FALSE;
    }

    /* 系统SubnetID长度小于Tag SubnetID长度，返回FALSE */
    if (pstHrpdInfo->ucSubNetMask < pstLocTagHrpd->ucSubnetLen)
    {
        return VOS_FALSE;
    }

    /* 先比较整字节，按TAG_LOC中的长度比较 */
    ucByteCnt = pstLocTagHrpd->ucSubnetLen / NAS_MSCC_BIT_LEN_ONE_BYTE;

    if (0 != VOS_MemCmp(pstHrpdInfo->aucSectorId, pstLocTagHrpd->aucSubnetId, ucByteCnt))
    {
        return VOS_FALSE;
    }

    ucRemainBitCnt = pstLocTagHrpd->ucSubnetLen % NAS_MSCC_BIT_LEN_ONE_BYTE;

    if (0 == ucRemainBitCnt)
    {
        return VOS_TRUE;
    }

    /* 再比较剩余bit */
    ucSysSubnetIdRemainValue = pstHrpdInfo->aucSectorId[ucByteCnt]
                               >> (NAS_MSCC_BIT_LEN_ONE_BYTE - ucRemainBitCnt);

    if (ucSysSubnetIdRemainValue == pstLocTagHrpd->aucSubnetId[ucByteCnt])
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_Is1xMncWithMlplMncMatched(
    VOS_UINT32                                              ul1xMnc,
    VOS_UINT16                                              usMlplMnc
)
{
    VOS_UINT32                                              ulNasStyleMnc;

    if (NAS_MSCC_MLPL_WILDCARD_MNC == usMlplMnc)
    {
        return VOS_TRUE;
    }

    ulNasStyleMnc = NAS_MSCC_ConvertMlplMncToNasStyleMnc(usMlplMnc);

    if (ul1xMnc == ulNasStyleMnc)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_IsMlplMsplSysTypeSupportLte(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
)
{
    switch (enSysType)
    {
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI:
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}



VOS_VOID NAS_MSCC_GeneratePrefPlmnList(
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU                    *pstOutPlmnList,
    VOS_UINT16                                             *pusOutPlmnCnt
)
{
    NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU                      *pstSimEhPlmnInfo     = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                    *pstUserPlmnInfo      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                    *pstOperPlmnInfo      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU                    *pstPlmnListStartPos  = VOS_NULL_PTR;

    /* 消除 PCLINT429 告警 */
    pstOutPlmnList   = pstOutPlmnList;

    pstSimEhPlmnInfo = NAS_MSCC_GetEhPlmnInfoAddr();
    pstUserPlmnInfo  = NAS_MSCC_GetUserPlmnInfoAddr();
    pstOperPlmnInfo  = NAS_MSCC_GetOperPlmnInfoAddr();

    *pusOutPlmnCnt = pstSimEhPlmnInfo->ucEhPlmnNum + pstUserPlmnInfo->ucUserPlmnNum
                     + pstOperPlmnInfo->usOperPlmnNum;

    if (pstSimEhPlmnInfo->ucEhPlmnNum > 0)
    {
        PS_MEM_CPY(pstOutPlmnList, pstSimEhPlmnInfo->astEhPlmnInfo,
                   pstSimEhPlmnInfo->ucEhPlmnNum * sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));
    }

    if (pstUserPlmnInfo->ucUserPlmnNum > 0)
    {
        pstPlmnListStartPos = pstOutPlmnList + pstSimEhPlmnInfo->ucEhPlmnNum;

        PS_MEM_CPY(pstPlmnListStartPos, pstUserPlmnInfo->astUserPlmnInfo,
                   pstUserPlmnInfo->ucUserPlmnNum* sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));
    }

    if (pstOperPlmnInfo->usOperPlmnNum > 0)
    {
        pstPlmnListStartPos = pstOutPlmnList + pstSimEhPlmnInfo->ucEhPlmnNum
                              + pstUserPlmnInfo->ucUserPlmnNum;

        PS_MEM_CPY(pstPlmnListStartPos, pstOperPlmnInfo->astOperPlmnInfo,
                   pstOperPlmnInfo->usOperPlmnNum * sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));
    }

}



VOS_UINT32 NAS_MSCC_ConvertMlplMccToNasStyleMcc(
    VOS_UINT16                          usMlplMcc
)
{
    VOS_UINT32                          ulNasMcc;

    /* 如果MLPL mcc的最高4位不是0，返回FALSE */
    if (0 != (usMlplMcc & 0xF000))
    {
        return NAS_MSCC_INVALID_MCC;
    }

    ulNasMcc = ((VOS_UINT32)(usMlplMcc & 0x0F00)) >> 8;

    ulNasMcc += ((VOS_UINT32)(usMlplMcc & 0x00F0)) << 4;

    ulNasMcc += ((VOS_UINT32)(usMlplMcc & 0x000F)) << 16;

    return ulNasMcc;
}



VOS_UINT32 NAS_MSCC_ConvertMlplMncToNasStyleMnc(
    VOS_UINT16                          usMlplMnc
)
{
    VOS_UINT32                          ulNasMnc;

    /* 如果MLPL mnc的最高4位不是0，返回FALSE */
    if (0 != (usMlplMnc & 0xF000))
    {
        return NAS_MSCC_INVALID_MNC;
    }

    ulNasMnc = ((VOS_UINT32)(usMlplMnc & 0x0F00)) >> 8;

    ulNasMnc += ((VOS_UINT32)(usMlplMnc & 0x00F0)) << 4;

    ulNasMnc += ((VOS_UINT32)(usMlplMnc & 0x000F)) << 16;

    return ulNasMnc;
}



NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplFile(
    VOS_UINT8                          *pucMlplBuff,
    VOS_UINT16                          usBuffSize
)
{
    NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32                     enParseRslt;

    if ((VOS_NULL_PTR == pucMlplBuff)
     || (NAS_MSCC_CONVERT_BYTES_TO_BITS(usBuffSize) < NAS_MSCC_MLPL_MIN_BIT_LEN))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMlplInfo:Invalid buffer Len passed.");
        return NAS_MSCC_PARSE_MLPL_RSLT_FAIL;
    }

    enParseRslt = NAS_MSCC_ParseMlplBitStream(pucMlplBuff, usBuffSize);
    if (enParseRslt != NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMlplInfo:MLPL parse failed, reason:",
                       enParseRslt);
        return enParseRslt;
    }

    NAS_MSCC_MNTN_LogMlplInfo(NAS_MSCC_GetMlplInfoAddr());

    return NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS;
}



NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplFile(
    VOS_UINT8                          *pucMsplBuff,
    VOS_UINT16                          usBuffSize
)
{
    NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32                     enParseRslt;

    if ((VOS_NULL_PTR == pucMsplBuff)
     || (NAS_MSCC_CONVERT_BYTES_TO_BITS(usBuffSize) < NAS_MSCC_MSPL_MIN_BIT_LEN))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMsplInfo:Invalid buffer Len passed.");
        return NAS_MSCC_PARSE_MSPL_RSLT_FAIL;
    }

    enParseRslt = NAS_MSCC_ParseMsplBitStream(pucMsplBuff, usBuffSize);
    if (enParseRslt != NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMsplInfo:MSPL parse failed, reason:",
                       enParseRslt);
        return enParseRslt;
    }

    NAS_MSCC_MNTN_LogMsplInfo(NAS_MSCC_GetMsplInfoAddr());

    return NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_IsHrpdSysTypeExistedInMsplTable
Description     :   判定当前MSPL表是否存在HRPD系统类型的记录
Input parameters:   pstInMsplTable----当前MSPL表
Outout parameters:  VOS_VOID
Return Value     :  VOS_TRUE  - 存在HRPD系统记录
                    VOS_FALSE - 不存在HRPD系统记录

    1)  Date    :   2016-01-07
        Author  :   w00176964
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsHrpdSysTypeExistedInMsplTable(
    NAS_MSCC_MSPL_ID_STRU              *pstInMsplTable
)
{
    VOS_UINT8                           ucLoop;
    NAS_MSCC_MSPL_REC_STRU             *pstMsplRec;

    for (ucLoop = 0; ucLoop < pstInMsplTable->ucNumMsplRec; ucLoop++)
    {
        pstMsplRec = &(pstInMsplTable->astMsplRec[ucLoop]);

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstMsplRec->enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI   == pstMsplRec->enSysType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_IsLteSysTypeExistedInMsplTable
Description     :   判定当前MSPL表是否存在LTE系统类型的记录
Input parameters:   pstInMsplTable----当前MSPL表
Outout parameters:  VOS_VOID
Return Value     :  VOS_TRUE  - 存在LTE系统记录
                    VOS_FALSE - 不存在LTE系统记录

    1)  Date    :   2016-01-14
        Author  :   w00176964
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsLteSysTypeExistedInMsplTable(
    NAS_MSCC_MSPL_ID_STRU              *pstInMsplTable
)
{
    VOS_UINT8                           ucLoop;
    NAS_MSCC_MSPL_REC_STRU             *pstMsplRec;

    for (ucLoop = 0; ucLoop < pstInMsplTable->ucNumMsplRec; ucLoop++)
    {
        pstMsplRec = &(pstInMsplTable->astMsplRec[ucLoop]);

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstMsplRec->enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstMsplRec->enSysType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

