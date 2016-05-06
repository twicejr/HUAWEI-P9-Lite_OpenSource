/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.
******************************************************************************/

#ifndef __NASLPPUPMTAMSGPROC_H__
#define __NASLPPUPMTAMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


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
#define NAS_LPP_OTDOA_UE_ASSIST     0x01
#define NAS_LPP_MIN_NEIGHBOUR_CELL_NUM 2

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
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32   NAS_LPP_FillinUpOtodaCapCnfData
(
    LPP_MTA_OTDOA_PROVIDE_CAP_STRU      *pstOTDOAProvideCapabilities,
    LRRC_SUPPORT_CAPABILITY_STRU        *pstLrrcCap
);
extern VOS_VOID  NAS_LPP_SaveCellGlobalId
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
);
extern VOS_VOID  NAS_LPP_SaveCpLength
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement,
    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU     *pstOtdoaRefCellCfg
);
extern VOS_VOID  NAS_LPP_SavePrs
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
);
extern VOS_VOID  NAS_LPP_SaveAntennaPort
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
);
extern VOS_VOID  NAS_LPP_SaveAntennaPort
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
);
extern VOS_VOID  NAS_LPP_SavePrsSubFrameOffset
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
);
extern VOS_VOID NAS_LPP_UpProcessEcidMeasCnf
(
    LRRC_LPP_ECID_MEAS_CNF_STRU        *pstEcidMeasCnf
);
extern VOS_VOID NAS_LPP_UpProcessOtdoaMeasCnf
(
    LRRC_LPP_OTDOA_MEAS_CNF_STRU        *pstOtdoaMeasCnf
);
extern VOS_VOID NAS_LPP_UPSndOtdoaMeasReq
(
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
);
extern VOS_VOID  NAS_LPP_SaveSlotNumOffset
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
);
extern VOS_VOID   NAS_LPP_SaveOtdoaNghbrCell
(
LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU      *pstOtdoaAssist,
NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg
);
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetEcidPosReqTechType(VOS_VOID);
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetOtdoaPosReqTechType(VOS_VOID);
extern VOS_VOID NAS_LPP_UpProcessOtdoaMeasInd
(
    LRRC_LPP_OTDOA_MEAS_IND_STRU        *pstOtdoaMeasInd
);
extern VOS_VOID NAS_LPP_UpProcessEcidMeasInd
(
    LRRC_LPP_ECID_MEAS_IND_STRU         *pstEcidMeasInd
);
extern VOS_VOID  NAS_LPP_PrepareOtdoaQuality
(
    LRRC_LPP_OTDOA_MEAS_QUALITY_STRU        *pstMeasRsltQuality,
    LPP_OTDOA_MEAS_QUALITY_STRU             *pstLppQuality
);
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

#endif /* end of NasLppSendMsg.h */
