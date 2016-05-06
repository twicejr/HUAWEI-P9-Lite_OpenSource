/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : CssCloudStrategyPublic.h
    Description : CSS云端频点频段特性公共头文件
    History     :
      1.chengmin 00285307   2015-10-12  Draft Enact


******************************************************************************/

#ifndef __CSSCLOUDSTRATEGYPUBLIC_H__
#define __CSSCLOUDSTRATEGYPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include            "CssPublic.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/




/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : CSS_COUNTY_MCC_DESC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 多MCC国家的MCC描述
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulMccNum;        /* 该国家MCC个数 */
    VOS_UINT32                                 *pulMccListAddr;  /* 该国家MCC列表的首地址 */
}CSS_COUNTY_MCC_DESC_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32 CSS_IsMccBelongToCountry
(
    VOS_UINT32                          ulMcc,
    CSS_COUNTY_MCC_DESC_STRU           *pstMccDesc
);
extern VOS_UINT32 CSS_IsMccBelongToMultiCountry(VOS_UINT32 ulMcc);
extern VOS_UINT32 CSS_IsTwoMccBelongToOneCountry
(
    VOS_UINT32                          ulMcc1,
    VOS_UINT32                          ulMcc2
);

VOS_UINT32 CSS_IsMccUpdatedAccordToUpdateStateTable(VOS_UINT8 aucMccId[2]);
extern VOS_VOID CSS_GetAllMccBelongToOneCountry
(
    VOS_UINT32                                    ulInNum,
    CSS_PLMN_ID_STRU                              astInPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutNum,
    CSS_PLMN_ID_STRU                              astOutPlmn[CSS_MAX_PREF_PLMN_NUM]
);
extern VOS_VOID CSS_AddAllMccBelongToCountry
(
    VOS_UINT32                         *pulOutNum,
    CSS_PLMN_ID_STRU                    astOutPlmn[CSS_MAX_PREF_PLMN_NUM],
    CSS_COUNTY_MCC_DESC_STRU           *pstMccDesc
);
extern VOS_UINT32 CSS_IsMccUpdatingInUpdateStateTable
(
    VOS_UINT8                           aucMccID[2]
);

extern VOS_VOID CSS_ConvertSimPlmnToGuPlmn
(
    VOS_UINT8                           aucPlmn[CSS_PLMN_ID_LEN],
    VOS_UINT32                         *pulMcc,
    VOS_UINT32                         *pulMnc

);
extern VOS_VOID CSS_ConvertSimMccToGuMcc
(
    VOS_UINT8                           aucMcc[2],
    VOS_UINT32                         *pulMcc
);


extern VOS_VOID CSS_ConvertSimMncToGuMnc
(
    VOS_UINT8                           aucMnc[2],
    VOS_UINT32                         *pulMnc
);


extern VOS_VOID CSS_ConvertGuMccToSimMcc
(
    VOS_UINT32                          ulMcc,
    VOS_UINT8                           aucMcc[2]
);


extern VOS_VOID CSS_ConvertGuMncToSimMnc
(
    VOS_UINT32                          ulMnc,
    VOS_UINT8                           aucMnc[2]
);


extern VOS_VOID CSS_ConvertMccDigitToSimMcc
(
    VOS_UINT8                           ucMccDigit1,
    VOS_UINT8                           ucMccDigit2,
    VOS_UINT8                           ucMccDigit3,
    VOS_UINT8                           aucMcc[2]
);
extern VOS_VOID CSS_ConvertMncDigitToSimMnc
(
    VOS_UINT8                           ucMncDigit1,
    VOS_UINT8                           ucMncDigit2,
    VOS_UINT8                           ucMncDigit3,
    VOS_UINT8                           aucMnc[2]
);
extern VOS_UINT32 CSS_HasGetMccVersionFromAp(VOS_VOID);
extern VOS_VOID CSS_InitMccVersion(VOS_VOID);
extern VOS_UINT32 CSS_ReadBandRatSuppotFromAtMsg
(
    VOS_UINT8                           *pucBandRatFlag,
    VOS_UINT8                           *pAddr,
    VOS_UINT32                          *pulSum,
    VOS_UINT32                          ulRemainLen
);
extern VOS_UINT32 CSS_isMncMatch(VOS_UINT8 aucMnc1[2], VOS_UINT8 aucMnc2[2]);
extern VOS_UINT32 CSS_isMccMatch(VOS_UINT8 aucMcc1[2], VOS_UINT8 aucMcc2[2]);
extern VOS_UINT32 CSS_IsRatSupportInFlag(CSS_RAT_TYPE_ENUM_UINT8 ucRat, VOS_UINT8 ucSupportFlag);
extern VOS_VOID CSS_DeleteAllFreq(CSS_PUB_PREF_BAND_STRU *pBand);
extern VOS_VOID CSS_DeleteAllBand(CSS_PUB_PREF_MNC_STRU *pMnc);
extern VOS_VOID CSS_DeleteAllMnc(CSS_PUB_PREF_MCC_STRU *pMcc);
extern VOS_VOID CSS_DeleteAllMcc(VOS_VOID);
extern VOS_VOID CSS_DeleteOneMcc(VOS_UINT8 aucMccId[2]);
extern VOS_UINT32 CSS_IsMccExistInLocal(VOS_UINT8 aucMccId[2]);
extern VOS_VOID CSS_StartApMccUpdateProcedure
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum,
    VOS_UINT16                          usClientId
);
extern VOS_VOID CSS_StartMmcOrAsMccUpdateProcedure
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum,
    CSS_MCC_ID_STRU                     astMccToSend[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNumToSend,
    VOS_UINT32                          ulPId
);
extern VOS_VOID CSS_EndApUpdateProcedure(VOS_VOID);
extern VOS_VOID CSS_EndMmcOrAsUpdateProcedure(CSS_MCC_UPDATE_STRU *pstUpdate);
extern VOS_VOID CSS_CloudContrlTimerInit(VOS_VOID);
extern VOS_UINT32  CSS_ReadNvCloudStrategy(VOS_VOID);
extern VOS_VOID  CSS_ReadNvCloudPrefArfcn(VOS_VOID);
extern VOS_VOID CSS_AddNvRatSupport(VOS_UINT8 *pucRatSupport, CSS_RAT_TYPE_ENUM_UINT8 ucRat);
extern VOS_VOID CSS_AddNvOneFreq(CSS_PUB_PREF_BAND_STRU *pstBand, CSS_NV_PREF_ARFCN_STRU *pNvFreq, CSS_RAT_TYPE_ENUM_UINT8 ucRat);
extern VOS_VOID CSS_AddNvOneBand(CSS_PUB_PREF_MNC_STRU *pstMnc, CSS_NV_PREF_MNC_STRU *pNvMnc);
extern VOS_VOID CSS_AddNvOneMnc(CSS_PUB_PREF_MCC_STRU *pstMcc, CSS_NV_PREF_MNC_STRU *pstNvMnc);
extern VOS_VOID CSS_AddNvOneMcc(CSS_NV_PREF_MCC_STRU *pPrefMcc, VOS_UINT32 ulIndex);
extern VOS_UINT32 CSS_UpdateOneMcc(CSS_MCC_UPDATE_STRU *pMccUpdate, VOS_UINT8 aucMcc[2]);
extern VOS_UINT32 CSS_IsAllMccUpdated(CSS_MCC_UPDATE_STRU *pMccUpdate);
extern VOS_UINT32 CSS_IsMmcOrAsUpdating(VOS_VOID);
extern VOS_VOID CSS_GetMccListFromLocal
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_MEMORY_PERF_MCC_NUM],
    VOS_UINT32                         *pulMccNum
);
extern VOS_UINT32 CSS_IsMccFreqExist
(
    VOS_UINT32                                    ulPlmnNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PLMN_ID_NUM]
);
extern VOS_VOID CSS_GetPrefFreqFromBandNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_BAND_STRU             *pBandNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
);
extern VOS_VOID CSS_GetPrefFreqFromMncNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
);
extern VOS_VOID CSS_GetPrefFreqFromMccNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PLMN_ID_STRU                   *pstPlmn,
    CSS_PUB_PREF_MCC_STRU              *pMccNode,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
);
extern CSS_RESULT_ENUM_UINT32 CSS_GetPreferFreqInfo
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnIdNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutPlmnNum,
    CSS_PREF_FREQ_INFO_STRU                       astPrefFreq[CSS_MAX_PREF_PLMN_NUM]
);
extern VOS_UINT32 CSS_IsBandNodeSupportRat
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_BAND_STRU             *pBandNode
);
extern VOS_VOID CSS_GetPrefBandFromMncNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_BAND_INFO_STRU            *pstOut
);
extern VOS_UINT32 CSS_IsMccBelongToMultiCountry
(
    VOS_UINT32 ulMcc
);
extern VOS_UINT32 CSS_IsRatHasNoPrefBand
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode
);

VOS_UINT32 CSS_JudgeMultiMccCountryHasPrefBand
(
    VOS_UINT32                         *pulNum,
    CSS_PREF_BAND_INFO_STRU             astPrefBand[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                          aulResult[CSS_MAX_PREF_PLMN_NUM]
);

extern VOS_UINT32 CSS_GetPrefBandFromMccNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PLMN_ID_STRU                   *pstPlmn,
    CSS_PUB_PREF_MCC_STRU              *pMccNode,
    CSS_PREF_BAND_INFO_STRU            *pstOut
);
extern CSS_RESULT_ENUM_UINT32 CSS_GetPreferBandInfo
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnIdNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutPlmnNum,
    CSS_PREF_BAND_INFO_STRU                       astPrefBand[CSS_MAX_PREF_PLMN_NUM]
);
extern VOS_VOID CSS_GetMccFromPlmnArr
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum,
    const CSS_PLMN_ID_STRU              astPlmnId[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulPlmnNum
);
extern VOS_UINT32 CSS_IsMccUpdatedFromAp(VOS_UINT8 aucMcc[2]);
extern VOS_VOID CSS_DeleteSameMccAccordToLocal
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum
);
extern VOS_VOID CSS_DeleteMccAlreadySndToAp
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum
);
extern VOS_VOID CSS_DeleteLocalMccFromMccArray
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum
);
extern VOS_UINT32 CSS_ReadNoPrefBandFlgFromAtMsg
(
     CSS_PUB_PREF_MNC_STRU *pstMnc, 
     VOS_UINT8 *pAddr, 
     VOS_UINT32 *pulSum, 
     VOS_UINT32 ulRemainLen
 );
extern VOS_UINT32 CSS_ReadFreqFromAtMsg
(
     CSS_PUB_PREF_BAND_STRU *pstBand,
     VOS_UINT8 *pAddr,
     VOS_UINT32 *pulSum, 
     VOS_UINT32 ulRemainLen
 );
extern VOS_UINT32 CSS_ReadBandFromAtMsg
(
     CSS_PUB_PREF_MNC_STRU *pstMnc, 
     VOS_UINT8 *pAddr, 
     VOS_UINT32 *pulSum,
     VOS_UINT32 ulRemainLen
 );
extern VOS_UINT32 CSS_ReadMncFromAtMsg
(
     CSS_PUB_PREF_MCC_STRU *pstMcc, 
     VOS_UINT8 *pAddr,
     VOS_UINT32 *pulSum, 
     VOS_UINT32 ulRemainLen
 );
extern VOS_UINT32 CSS_ReadMccFromAtMsg
(
     VOS_UINT8 *pAddr, 
     VOS_UINT32 ulRemainLen
 );
extern VOS_VOID CSS_AddFreqNodeToLocal
(
     CSS_PUB_PREF_BAND_STRU *pstBandNode, 
     CSS_PUB_PREF_FREQ_STRU *pstFreqIn
 );
extern VOS_VOID CSS_AddBandNodeToLocal
(
 CSS_PUB_PREF_MNC_STRU *pstMncNode,
 CSS_PUB_PREF_BAND_STRU *pstBandIn
 );
extern VOS_VOID CSS_AddMncNodeToLocal
(
     CSS_PUB_PREF_MCC_STRU *pstMccNode,
     CSS_PUB_PREF_MNC_STRU *pstMncIn
 );
extern VOS_VOID CSS_AddMccNodeToLocal
(
    CSS_PUB_PREF_MCC_STRU *pstMccIn
 );
extern VOS_VOID CSS_UpdateRatFreqToNv
(
    VOS_UINT8 aucMncId[2],
    VOS_UINT8 ucBand,
    CSS_RAT_TYPE_ENUM_UINT8 ucRat,
    CSS_PUB_PREF_FREQ_STRU *pstFreqNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
);
extern VOS_VOID CSS_UpdateRatBandToNv
(
    VOS_UINT8 aucMncId[2],
    CSS_RAT_TYPE_ENUM_UINT8 ucRat,
    CSS_PUB_PREF_BAND_STRU *pstBandNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
);
extern VOS_VOID CSS_UpdateFreqToNv
(
    VOS_UINT8 aucMncId[2],
    CSS_PUB_PREF_BAND_STRU *pstBandNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
);
extern VOS_VOID CSS_UpdateBandToNv(CSS_PUB_PREF_MNC_STRU *pstMncNode, CSS_NV_PREF_MCC_STRU *pstNvMcc);
extern VOS_VOID CSS_UpdateMncToNv(CSS_PUB_PREF_MCC_STRU *pstMccNode, CSS_NV_PREF_MCC_STRU *pstNvMcc);
extern VOS_UINT32 CSS_UpdateMccToNv(VOS_UINT8 aucMccId[2], CSS_NV_PREF_MCC_STRU *pstNvMcc);
extern VOS_VOID CSS_WriteNvMccPrefFreq(VOS_VOID);
extern VOS_UINT32 CSS_ConvertAscToHex(VOS_UINT8 *pucDest, VOS_UINT8 ucSrc);
extern VOS_UINT32 CSS_ConvertStrToHex(VOS_UINT8 *pucHex, const VOS_UINT8 *pucStr, VOS_UINT32 ulStrLen);
extern VOS_UINT32 CSS_IsMccNeedToDelete(VOS_UINT8 aucMccId[2]);
extern VOS_VOID CSS_DeleteLocalMccNotUpdating(VOS_VOID);
extern VOS_VOID * CSS_AllocCloudPreferNodeAndClearFullMemory(VOS_UINT32 ulLen);
#if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
extern VOS_VOID * CSS_AllocCloudPreferNode(VOS_VOID);
#endif
extern VOS_VOID CSS_FreeCloudPreferNode(VOS_VOID *pAddr);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of CssCloudStrategyPublic.h */





