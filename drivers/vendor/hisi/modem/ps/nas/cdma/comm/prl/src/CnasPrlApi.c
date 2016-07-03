

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "CnasPrlMem.h"
#include "CnasPrlApi.h"
#include "CnasCcb.h"
#include "CnasXsdCtx.h"

#include "NasMntn.h"
#include "CnasPrlMntn.h"
#include  "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_PRL_API_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/******************************************************************************
    =============== ROAMING LIST ===============
    Roaming List Type:    IS-683C
    Preferred Only:   FALSE
    Default Roaming Indicator:  2
    Preferred List ID:    1

    =============== Acquisition Table Record ===============
    INDEX ACQ_TYPE  CH1 CH2 CH3 CH4 CH5 CH6 CH7 - - CH31
    0 1 B
    1 1 A
    2 2 B Both
    3 2 A Both
    4 10  0 283 0 691 0 384 0 777 0 779 0 738 0 486 0 568 0 40  0 1022 10 50 10 100 10 150 10 250 10 300 10 350 10 450 10 500 10 550 10 650 10 670 10 770 10 820 10 870
    5 10  1 25  1 50  1 75  1 100 1 125 1 150 1 175 1 200 1 225 1 250 1 275 1 325 1 350 1 375 1 425 1 450 1 475 1 500 1 525 1 550 1 575 1 600 1 625 1 650 1 675 1 725 1 750 1 775 1 825 1 850 1 875 1 925
    6 10  1 950 1 975 1 1000  1 1025  1 1050  1 1075  1 1100  1 1125  1 1150  1 1175
    7 10  15  25  15  50  15  75  15  100 15  125 15  150 15  175 15  225 15  250 15  275 15  300 15  325 15  350 15  375 15  425 15  450 15  475 15  525 15  550 15  575 15  625 15  650 15  675 15  725 15  750 15  775 15  800 15  825 15  850 15  875
    8 10  18  45  18  70  18  95  18  145 18  170 18  195
    9 10  19  23  19  48  19  73  19  98  19  143 19  168 19  193 19  218 19  263 19  288 19  313 19  338
    10  5 Any

    =============== System Table Record ===============
    INDEX SYS_TYPE  NEG/PREF  GEO PRI ACQ_IND ROAM_IND  ASSN INC  ASSN TAG  PN ASSN DATA ASSN SID, NID / MCC, IMSI_11_12 / SUBNETID / PLMN TYPE, PLMN, LAC
    0 0 Pref  New Same  4 0 No  0 65535
    1 0 Pref  Same  Same  5 0 No  0 65535
    2 0 Pref  Same  Same  6 0 No  0 65535
    3 0 Pref  Same  Same  7 0 No  0 65535
    4 0 Pref  Same  Same  8 0 No  0 65535
    5 0 Pref  Same  Same  9 0 No  0 65535
    6 0 Pref  Same  Same  10  2 No  0 65535
    7 0 Pref  Same  Same  2 0 No  0 65535
    8 0 Pref  Same  More  3 2 No  0 65535
    9 0 Pref  Same  Same  0 0 No  0 65535
    10  0 Pref  Same  Same  1 2 No  0 65535

******************************************************************************/
VOS_UINT8                               g_aucDefaultPrlBuffer[] =
{ 0x01, 0x4E, 0x00, 0x01, 0x03, 0x01, 0x02, 0xC0,
  0x00, 0x05, 0x80, 0x01, 0x01, 0x40, 0x01, 0x01,
  0x00, 0x02, 0x01, 0x70, 0x02, 0x01, 0x30, 0x0A,
  0x30, 0x01, 0x1B, 0x02, 0xB3, 0x01, 0x80, 0x03,
  0x09, 0x03, 0x0B, 0x02, 0xE2, 0x01, 0xE6, 0x02,
  0x38, 0x00, 0x28, 0x03, 0xFE, 0x50, 0x32, 0x50,
  0x64, 0x50, 0x96, 0x50, 0xFA, 0x51, 0x2C, 0x51,
  0x5E, 0x51, 0xC2, 0x51, 0xF4, 0x52, 0x26, 0x52,
  0x8A, 0x52, 0x9E, 0x53, 0x02, 0x53, 0x34, 0x53,
  0x66, 0x0A, 0x40, 0x08, 0x19, 0x08, 0x32, 0x08,
  0x4B, 0x08, 0x64, 0x08, 0x7D, 0x08, 0x96, 0x08,
  0xAF, 0x08, 0xC8, 0x08, 0xE1, 0x08, 0xFA, 0x09,
  0x13, 0x09, 0x45, 0x09, 0x5E, 0x09, 0x77, 0x09,
  0xA9, 0x09, 0xC2, 0x09, 0xDB, 0x09, 0xF4, 0x0A,
  0x0D, 0x0A, 0x26, 0x0A, 0x3F, 0x0A, 0x58, 0x0A,
  0x71, 0x0A, 0x8A, 0x0A, 0xA3, 0x0A, 0xD5, 0x0A,
  0xEE, 0x0B, 0x07, 0x0B, 0x39, 0x0B, 0x52, 0x0B,
  0x6B, 0x0B, 0x9D, 0x0A, 0x14, 0x0B, 0xB6, 0x0B,
  0xCF, 0x0B, 0xE8, 0x0C, 0x01, 0x0C, 0x1A, 0x0C,
  0x33, 0x0C, 0x4C, 0x0C, 0x65, 0x0C, 0x7E, 0x0C,
  0x97, 0x0A, 0x3C, 0x78, 0x19, 0x78, 0x32, 0x78,
  0x4B, 0x78, 0x64, 0x78, 0x7D, 0x78, 0x96, 0x78,
  0xAF, 0x78, 0xE1, 0x78, 0xFA, 0x79, 0x13, 0x79,
  0x2C, 0x79, 0x45, 0x79, 0x5E, 0x79, 0x77, 0x79,
  0xA9, 0x79, 0xC2, 0x79, 0xDB, 0x7A, 0x0D, 0x7A,
  0x26, 0x7A, 0x3F, 0x7A, 0x71, 0x7A, 0x8A, 0x7A,
  0xA3, 0x7A, 0xD5, 0x7A, 0xEE, 0x7B, 0x07, 0x7B,
  0x20, 0x7B, 0x39, 0x7B, 0x52, 0x7B, 0x6B, 0x0A,
  0x0C, 0x90, 0x2D, 0x90, 0x46, 0x90, 0x5F, 0x90,
  0x91, 0x90, 0xAA, 0x90, 0xC3, 0x0A, 0x18, 0x98,
  0x17, 0x98, 0x30, 0x98, 0x49, 0x98, 0x62, 0x98,
  0x8F, 0x98, 0xA8, 0x98, 0xC1, 0x98, 0xDA, 0x99,
  0x07, 0x99, 0x20, 0x99, 0x39, 0x99, 0x52, 0x05,
  0x01, 0x3C, 0x30, 0x40, 0x20, 0x00, 0x00, 0x00,
  0x30, 0x60, 0x28, 0x00, 0x00, 0x00, 0x30, 0x60,
  0x30, 0x00, 0x00, 0x00, 0x30, 0x60, 0x38, 0x00,
  0x00, 0x00, 0x30, 0x60, 0x40, 0x00, 0x00, 0x00,
  0x30, 0x60, 0x48, 0x00, 0x00, 0x00, 0x30, 0x60,
  0x50, 0x00, 0x00, 0x04, 0x30, 0x60, 0x10, 0x00,
  0x00, 0x00, 0x30, 0x70, 0x18, 0x00, 0x00, 0x04,
  0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x30, 0x60,
  0x08, 0x00, 0x00, 0x04, 0x69, 0xC7};

/****************************************************************************
 * CDMA Preferred Set of Frequency Assignments for Band Class 1 (spread rate 1)
 ****************************************************************************/
/* PCS block A prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockATab[]={
    25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275
};

/* PCS block B prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockBTab[]={
    425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675
};

/* PCS block C prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockCTab[]={
    925, 950, 975, 1000, 1025, 1050, 1075, 1100, 1125, 1150, 1175
};

/* PCS block D prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockDTab[]={
    325, 350, 375
};

/* PCS block E prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockETab[]={
    725, 750, 775
};

/* PCS block F prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockFTab[]={
    825, 850, 875
};

/****************************************************************************
 * CDMA Preferred Set of Frequency Assignments for Band Class 0 (spread rate 1)
 ****************************************************************************/
CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU const g_astCnasPrlBand0Tab[] = {
    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN, 0, 779, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN, 0, 738, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_SYS_SEL_TYPE_B, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN, 0, 486, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_SYS_SEL_TYPE_B, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN, 0, 568, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN, 0, 40, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN, 0, 1022, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_3, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN, 0, 1273, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_3, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN, 0, 40, 0}
};

/****************************************************************************
 * CDMA Preferred Set of Frequency Assignments for Band Class 10 (spread rate 1)
 ****************************************************************************/
CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU const g_astCnasPrlBand10Tab[] = {
    {CNAS_PRL_BAND_SUBCLASS_TYPE_0, CNAS_PRL_BAND10_SYS_SEL_TYPE_A, 50},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_0, CNAS_PRL_BAND10_SYS_SEL_TYPE_A, 100},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_0, CNAS_PRL_BAND10_SYS_SEL_TYPE_A, 150},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_BAND10_SYS_SEL_TYPE_B, 250},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_BAND10_SYS_SEL_TYPE_B, 300},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_BAND10_SYS_SEL_TYPE_B, 350},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_BAND10_SYS_SEL_TYPE_C, 450},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_BAND10_SYS_SEL_TYPE_C, 500},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_BAND10_SYS_SEL_TYPE_C, 550},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_3, CNAS_PRL_BAND10_SYS_SEL_TYPE_D, 650},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_3, CNAS_PRL_BAND10_SYS_SEL_TYPE_D, 670},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_4, CNAS_PRL_BAND10_SYS_SEL_TYPE_E, 770},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_4, CNAS_PRL_BAND10_SYS_SEL_TYPE_E, 820},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_4, CNAS_PRL_BAND10_SYS_SEL_TYPE_E, 870}
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958 */


VOS_VOID CNAS_PRL_InitPrlCtx(VOS_UINT32 ulTaskInitFlag)
{
    if (VOS_TRUE == ulTaskInitFlag)
    {
        /* 初始化PRL上下文 */
        CNAS_PRL_InitMemBuff();
    }
    else
    {
        CNAS_PRL_MemFreeBuff();
    }

    /* 初始化PRL存储信息 */
    CNAS_PRL_InitPrlInfo(ulTaskInitFlag);
}


CNAS_PRL_HEADER_INFO_STRU* CNAS_PRL_GetPrlHeaderInfoAddr(VOS_VOID)
{
    return &(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader);
}


VOS_UINT32 CNAS_PRL_GetPrlInfoValidFlag(VOS_VOID)
{
    return (CNAS_PRL_GetPrlInfoAddr()->ulIsPrlValid);
}


VOS_UINT8 *CNAS_PRL_GetDefaultPrl(VOS_VOID)
{
    return &(g_aucDefaultPrlBuffer[0]);
}


VOS_UINT16 CNAS_PRL_GetDefaultPrlSize(VOS_VOID)
{
    return sizeof(g_aucDefaultPrlBuffer);
}



CNAS_PRL_ACQ_RECORD_INFO_STRU* CNAS_PRL_GetPrlAcqInfoAddr(VOS_VOID)
{
    return &(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo);
}


CNAS_PRL_SYS_RECORD_INFO_STRU* CNAS_PRL_GetPrlSysInfoAddr(VOS_VOID)
{
    return &(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo);
}


VOS_UINT16 CNAS_PRL_GetPrlAcqRecordNum(VOS_VOID)
{
    return (CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo.usAcqRecordNum);
}


CNAS_PRL_SSPR_P_REV_ENUM_UINT8 CNAS_PRL_GetPrlRevInfo(VOS_VOID)
{
    return (CNAS_PRL_GetPrlHeaderInfoAddr()->enSsprPRev);
}


VOS_VOID CNAS_PRL_SetPrlRevInfo(
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev
)
{
    CNAS_PRL_GetPrlHeaderInfoAddr()->enSsprPRev = enSsprPRev;
}


CNAS_PRL_ACQ_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlAcqRecord(VOS_UINT16 usIndex)
{
    if ((usIndex < CNAS_PRL_GetPrlAcqRecordNum()) && (usIndex < CNAS_PRL_ACQ_RECORD_MAX_NUM))
    {
        return (CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo.pastPrlAcqRecord[usIndex]);

    }

    return VOS_NULL_PTR;
}


VOS_UINT16 CNAS_PRL_GetPrlSysRecordNum(VOS_VOID)
{
    return (CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo.usSysRecordNum);
}


CNAS_PRL_EXT_SYS_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlSysRecord(VOS_UINT16 usIndex)
{
    /* 索引检查 */
    if ((usIndex < CNAS_PRL_GetPrlSysRecordNum()) && (usIndex < CNAS_PRL_SYS_RECORD_MAX_NUM))
    {
        /* 跳转到指定索引的系统记录地址 */
        return (CNAS_PRL_EXT_SYS_RECORD_STRU *)(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo.pstSysRecord + usIndex);
    }

    return VOS_NULL_PTR;
}


VOS_VOID CNAS_PRL_InitPrlHeaderInfo(
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeader
)
{
    /* 初始化PRL 头信息 */
    NAS_MEM_SET_S(pstPrlHeader, sizeof(CNAS_PRL_HEADER_INFO_STRU), 0, sizeof(CNAS_PRL_HEADER_INFO_STRU));

    pstPrlHeader->enDefRoamInd = CNAS_PRL_SYS_ROAMING_STATUS_RESERVED;
}


VOS_VOID CNAS_PRL_InitPrlAcqInfo(
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstPrlAcqInfo
)
{
    VOS_UINT16                          i;

    /* 初始化PRL捕获记录信息 */
    NAS_MEM_SET_S(pstPrlAcqInfo, sizeof(CNAS_PRL_ACQ_RECORD_INFO_STRU), 0, sizeof(CNAS_PRL_ACQ_RECORD_INFO_STRU));

    for (i = 0; i < CNAS_PRL_ACQ_RECORD_MAX_NUM; i++)
    {
        pstPrlAcqInfo->pastPrlAcqRecord[i] = VOS_NULL_PTR;
    }
}


VOS_VOID CNAS_PRL_FreeMccRec(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo
)
{
    VOS_UINT32                          ulIndex;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord;

    for (ulIndex = 0; ulIndex < pstPrlSysInfo->usSysRecordNum; ulIndex++)
    {
        pstSysRecord = &(pstPrlSysInfo->pstSysRecord[ulIndex]);

        if ((CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED      == pstSysRecord->enRecordType)
         && (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID == pstSysRecord->u.stMccMncId.enMccMncSubType))
        {
            if (VOS_NULL_PTR != pstSysRecord->u.stMccMncId.u.pstSubnetId)
            {
                PS_MEM_FREE(UEPS_PID_XSD, pstSysRecord->u.stMccMncId.u.pstSubnetId);
            }
        }
    }

    return;
}


VOS_VOID CNAS_PRL_InitPrlSysInfo(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo,
    VOS_UINT32                          ulTaskInitFlag
)
{
    if ((VOS_FALSE    == ulTaskInitFlag)
     && (VOS_NULL_PTR != pstPrlSysInfo->pstSysRecord))
    {
        CNAS_PRL_FreeMccRec(pstPrlSysInfo);

        PS_MEM_FREE(UEPS_PID_XSD, pstPrlSysInfo->pstSysRecord);
    }

    /* 初始化PRL系统记录信息 */
    NAS_MEM_SET_S(pstPrlSysInfo, sizeof(CNAS_PRL_SYS_RECORD_INFO_STRU), 0, sizeof(CNAS_PRL_SYS_RECORD_INFO_STRU));

    pstPrlSysInfo->pstSysRecord = VOS_NULL_PTR;
}


VOS_VOID CNAS_PRL_InitPrlInfo(VOS_UINT32 ulTaskInitFlag)
{
    CNAS_PRL_INFO_STRU                  *pstPrlInfo = VOS_NULL_PTR;

    pstPrlInfo = CNAS_PRL_GetPrlInfoAddr();

    pstPrlInfo->ulIsPrlValid = VOS_FALSE;

    CNAS_PRL_InitPrlHeaderInfo(&(pstPrlInfo->stPrlHeader));

    CNAS_PRL_InitPrlAcqInfo(&(pstPrlInfo->stPrlAcqInfo));

    CNAS_PRL_InitPrlSysInfo(&(pstPrlInfo->stPrlSysInfo), ulTaskInitFlag);
}


VOS_UINT32 CNAS_PRL_ProcPrlInfo(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
)
{
    VOS_UINT32                          ulRslt;

    if ((CNAS_PRL_SSPR_P_REV_3 != enPrlRev)
     && (CNAS_PRL_SSPR_P_REV_1 != enPrlRev))
    {
        /* PRL数据长度与返回的文件长度不匹配 */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: enPrlRev is not supported!");

        return VOS_FALSE;
    }

    /* 申请PRL需要使用的内存 */
    CNAS_PRL_MallocMemBuff();

    if (CNAS_PRL_SSPR_P_REV_3 == enPrlRev)
    {
        ulRslt = CNAS_PRL_ParseEprlBitStream(pucSrc, usSrcLen);
    }
    else
    {
        ulRslt = CNAS_PRL_ParsePrlBitStream(pucSrc, usSrcLen);
    }

    /* 如果解析失败，释放上次分配的内存 */
    if (VOS_FALSE == ulRslt)
    {
        CNAS_PRL_InitPrlCtx(VOS_FALSE);
    }

    return ulRslt;
}



VOS_VOID CNAS_PRL_MapStandardBand0SubClassToChannel(
    CNAS_PRL_BAND_SUBCLASS_TYPE_ENUM_UINT8                  enBandSubClass,
    CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8                        enSysSelType,
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enStandChanSelType,
    VOS_UINT16                                             *pusChannel
)
{
    VOS_UINT16                                              i;
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan = VOS_NULL_PTR;

    if (CNAS_PRL_BAND_SUBCLASS_TYPE_0 == enBandSubClass)
    {
        pstCdmaStandardChan = CNAS_CCB_GetCdmaStandardChannels();

        if (CNAS_PRL_SYS_SEL_TYPE_A == enSysSelType)
        {
            if (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN == enStandChanSelType)
            {
                *pusChannel = pstCdmaStandardChan->usPrimaryA;

                return;
            }

            if (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN == enStandChanSelType)
            {
                *pusChannel = pstCdmaStandardChan->usSecondaryA;

                return;
            }
        }

        if (CNAS_PRL_SYS_SEL_TYPE_B == enSysSelType)
        {
            if (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN == enStandChanSelType)
            {
                *pusChannel = pstCdmaStandardChan->usPrimaryB;

                return;
            }

            if (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN == enStandChanSelType)
            {
                *pusChannel = pstCdmaStandardChan->usSecondaryB;

                return;
            }
        }

        return;
    }

    /* 根据g_aucCnasPrlBand0Tab表中的信息，返回对应的频点信息 */
    for (i = 0; i<(sizeof(g_astCnasPrlBand0Tab)/sizeof(CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU)); i++)
    {
        if ((enBandSubClass == g_astCnasPrlBand0Tab[i].enSubclass)
         && (enSysSelType == g_astCnasPrlBand0Tab[i].enSysType)
         && (enStandChanSelType == g_astCnasPrlBand0Tab[i].enChanType))
        {
            *pusChannel = g_astCnasPrlBand0Tab[i].usChan;
        }
    }

}


VOS_VOID CNAS_PRL_MapCellularCdmaStandardSysAToBandChannel(
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanSelType,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{

    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN == enChanSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN == enChanSelType))
    {
        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_0,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_1,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_2,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_3,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;
    }

    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN == enChanSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN == enChanSelType))
    {
        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_0,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_1,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_2,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_3,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;
    }


}



VOS_VOID CNAS_PRL_MapCellularCdmaStandardSysBToBandChannel(
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanSelType,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{

    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN == enChanSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN == enChanSelType))
    {
        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_0,
                                                   CNAS_PRL_SYS_SEL_TYPE_B,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_1,
                                                   CNAS_PRL_SYS_SEL_TYPE_B,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

    }

    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN == enChanSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN == enChanSelType))
    {
        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_0,
                                                   CNAS_PRL_SYS_SEL_TYPE_B,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_1,
                                                   CNAS_PRL_SYS_SEL_TYPE_B,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

    }


}


VOS_VOID CNAS_PRL_MapCellularCdmaStandardToBandChannel(
    CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU    *pstCellularStandardSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    /*
      For band class 0 only, the actual CDMA channels come from NV-RAM1 and,
      as may have already been deduced from the tables above, there are four
      such channels, namely, primary-A, primary-B, secondary-A, and secondary-B.
      These channels are programmed into NV by the operator (or specified by the
      operator to the manufacturer in the Product Release Information (PRI)).
      Band            Standard Channel        Channel Number
      A               Primary                 283
                      Secondary               691
      B               Primary                 384
                      Secondary               777
     */

    /* 根据传入的信息，填写频段和channel number，根据CDG130的定义，此时都是
       Band 0的场景，因此band都是填写成band 0*/
    pstFreqInfo->ulNum = 0;

    /* 如果参数异常，不是SYS A/B系统，直接返回，此时个数为0 */
    if ((CNAS_PRL_SYS_SEL_TYPE_RESERVED == pstCellularStandardSys->enSysSelType)
      ||(pstCellularStandardSys->enSysSelType > CNAS_PRL_SYS_SEL_TYPE_A_OR_B))
    {
        return;
    }

    /* 如果参数异常，不是Primary和Secondary，直接返回，此时个数为0 */
    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_RESERVED == pstCellularStandardSys->enChanSelType)
      ||(pstCellularStandardSys->enChanSelType > CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN))
    {
        return;
    }

    /* 转换SYS A的band和channel */
    if ((CNAS_PRL_SYS_SEL_TYPE_A == pstCellularStandardSys->enSysSelType)
     || (CNAS_PRL_SYS_SEL_TYPE_A_OR_B == pstCellularStandardSys->enSysSelType))
    {
        CNAS_PRL_MapCellularCdmaStandardSysAToBandChannel(pstCellularStandardSys->enChanSelType,
                                                          pstFreqInfo);
    }

    /* 转换SYS B的band和channel */
    if ((CNAS_PRL_SYS_SEL_TYPE_B == pstCellularStandardSys->enSysSelType)
     || (CNAS_PRL_SYS_SEL_TYPE_A_OR_B == pstCellularStandardSys->enSysSelType))
    {
        CNAS_PRL_MapCellularCdmaStandardSysBToBandChannel(pstCellularStandardSys->enChanSelType,
                                                          pstFreqInfo);
    }

}



VOS_VOID CNAS_PRL_MapCellularCdmaCustomToBandChannel(
    CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU      *pstCelluarCustomSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT32                          i;

    /*
    This acquisition record is used to search for CDMA service in band class 0
    (800 MHz cellular frequency band) on a list (up to 32) of specific channels.
    */

    /* 根据传入的信息，填写频段和channel number，根据CDG130的定义，此时都是
       Band 0的场景，band都是填写成band 0，channel直接填写 */

    for (i = 0; i < (VOS_UINT8)CNAS_MIN(pstCelluarCustomSys->ucNumOfChans, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++)
    {
        pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        pstFreqInfo->astFreqInfo[i].usChannel = pstCelluarCustomSys->ausChan[i];
    }
    pstFreqInfo->ulNum = pstCelluarCustomSys->ucNumOfChans;

}



VOS_VOID CNAS_PRL_MapCellularCdmaPreferToBandChannel(
    CNAS_PRL_CELLUAR_CDMA_PREFERRED_SYS_ACQ_RECORD_STRU    *pstCellularPreSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    /*
    This record is used to instruct the mobile device to search, in band
    class 0, for CDMA service first (on the standard channels in a particular
    band); and, if no CDMA service is found, to look for AMPS Cellular service
    in the same band.

    This channel editor field is known in the standards as the 'PRI_SEC 'field
    and can take one of three legal values.
    (这里按照Primary和Secondary都支持来处理)

    Band            Standard Channel        Channel Number
    A               Primary                 283
                    Secondary               691
    B               Primary                 384
                    Secondary               777
    */

    /* 根据传入的信息，填写频段和channel number，根据CDG130的定义，此时都是
       Band 0的场景，因此band都是填写成band 0*/

    pstFreqInfo->ulNum = 0;

    /* 如果参数异常，不是SYS A/B系统，直接返回，此时个数为0 */
    if ((CNAS_PRL_SYS_SEL_TYPE_RESERVED == pstCellularPreSys->enSysSelType)
      ||(pstCellularPreSys->enSysSelType > CNAS_PRL_SYS_SEL_TYPE_A_OR_B))
    {
        return;
    }


    /* 转换SYS A的band和channel */
    if ((CNAS_PRL_SYS_SEL_TYPE_A == pstCellularPreSys->enSysSelType)
     || (CNAS_PRL_SYS_SEL_TYPE_A_OR_B == pstCellularPreSys->enSysSelType))
    {
        CNAS_PRL_MapCellularCdmaStandardSysAToBandChannel(CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN,
                                                          pstFreqInfo);
    }

    /* 转换SYS B的band和channel */
    if ((CNAS_PRL_SYS_SEL_TYPE_B == pstCellularPreSys->enSysSelType)
     || (CNAS_PRL_SYS_SEL_TYPE_A_OR_B == pstCellularPreSys->enSysSelType))
    {
        CNAS_PRL_MapCellularCdmaStandardSysBToBandChannel(CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN,
                                                          pstFreqInfo);
    }

}


VOS_VOID CNAS_PRL_MapPcsBlockAToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* 当前只支持CNAS_SPREADING_RATE_1，目前芯片和物理层都还不支持CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockATab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockATab[i];
        }
        pstFreqInfo->ulNum = i;

    }

}


VOS_VOID CNAS_PRL_MapPcsBlockBToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* 当前只支持CNAS_SPREADING_RATE_1，目前芯片和物理层都还不支持CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockBTab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockBTab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}



VOS_VOID CNAS_PRL_MapPcsBlockCToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* 当前只支持CNAS_SPREADING_RATE_1，目前芯片和物理层都还不支持CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockCTab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockCTab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}


VOS_VOID CNAS_PRL_MapPcsBlockDToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* 当前只支持CNAS_SPREADING_RATE_1，目前芯片和物理层都还不支持CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockDTab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockDTab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}


VOS_VOID CNAS_PRL_MapPcsBlockEToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* 当前只支持CNAS_SPREADING_RATE_1，目前芯片和物理层都还不支持CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockETab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockETab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}


VOS_VOID CNAS_PRL_MapPcsBlockFToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* 当前只支持CNAS_SPREADING_RATE_1，目前芯片和物理层都还不支持CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockFTab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockFTab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}



VOS_VOID CNAS_PRL_MapPcsBlockAnyToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stTmpFreqInfo;

    pstFreqInfo->ulNum = 0;

    CNAS_PRL_MapPcsBlockAToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockBToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockCToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockDToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockEToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockFToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;



}


CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM_UINT32 CNAS_PRL_TransBlockTypeToBlockTypeFlag(
    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM_UINT8           enBlockType
)
{
    switch (enBlockType)
    {
        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_A:
            return CNAS_PRL_MAP_PCS_BLOCK_A_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_B:
            return CNAS_PRL_MAP_PCS_BLOCK_B_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_C:
            return CNAS_PRL_MAP_PCS_BLOCK_C_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_D:
            return CNAS_PRL_MAP_PCS_BLOCK_D_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_E:
            return CNAS_PRL_MAP_PCS_BLOCK_E_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_F:
            return CNAS_PRL_MAP_PCS_BLOCK_F_FLG;

        default:
            return CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG;
    }
}

VOS_VOID CNAS_PRL_MapPcsCdmaBlockToBandChannel(
    CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_STRU           *pstPcsBlocksSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stTmpFreqInfo;
    CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM_UINT32                  enMapPcsBlockFlg;
    CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM_UINT32                  enTmpMapPcsBlockFlg;

    /*
     This record is used to instruct the mobile device to look for CDMA service
     on the channels listed in band class 1 (1900 MHz PCS frequencies).
     */

    /* 根据传入的信息，填写频段和channel number，根据CDG130的定义，此时都是
       Band 1的场景，band都是填写成band 1，channel 根据PCS的定义转换后填写 */

    pstFreqInfo->ulNum      = 0;
    stTmpFreqInfo.ulNum     = 0;
    enMapPcsBlockFlg        = CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG;
    enTmpMapPcsBlockFlg     = CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG;


    for (i = 0; i < pstPcsBlocksSys->ucNumOfBlocks; i++)
    {
        /* 为防止Acq Record中有重复转换，因此重复出现的block，不再转换，放到频点中 */
        enTmpMapPcsBlockFlg = CNAS_PRL_TransBlockTypeToBlockTypeFlag(pstPcsBlocksSys->aenBlock[i]);
        {
            /* 如果已经处理过，则直接continue */
            if ((enTmpMapPcsBlockFlg != CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG)
             && (enTmpMapPcsBlockFlg == (enTmpMapPcsBlockFlg & enMapPcsBlockFlg)))
            {
                continue;
            }
        }

        switch (pstPcsBlocksSys->aenBlock[i])
        {
            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_A:
                CNAS_PRL_MapPcsBlockAToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_A_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_B:
                CNAS_PRL_MapPcsBlockBToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_B_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_C:
                CNAS_PRL_MapPcsBlockCToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_C_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_D:
                CNAS_PRL_MapPcsBlockDToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_D_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_E:
                CNAS_PRL_MapPcsBlockEToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_E_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_F:
                CNAS_PRL_MapPcsBlockFToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_F_FLG;
                break;

            /* 为做兼容性保护，如果此时有any 类型，而前面已经填写过其他的block，则删除掉之前的赋值，重新赋值 */
            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ANY_BLOCK:
                pstFreqInfo->ulNum = 0;
                CNAS_PRL_MapPcsBlockAnyToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_ANY_FLG;
                break;

            default:
                CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_MapPcsCdmaBlockToBandChannel():Wrong  block Type");
                break;
        }

        if (0 != stTmpFreqInfo.ulNum)
        {
            NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                          stTmpFreqInfo.astFreqInfo,
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
            pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;
        }
        stTmpFreqInfo.ulNum = 0;
    }
}



VOS_VOID CNAS_PRL_MapPcsCdmaChannelToBandChannel(
    CNAS_PRL_PCS_CDMA_SYS_ACQ_CHANNELS_STRU                *pstPcsChannelsSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /*
     This record is used to instruct the mobile device to look for CDMA service
     on the channels listed in band class 1 (1900 MHz PCS frequencies).
     */

    /* 根据传入的信息，填写频段和channel number，根据CDG130的定义，此时都是
       Band 1的场景，band都是填写成band 1，channel直接填写 */

    pstFreqInfo->ulNum = pstPcsChannelsSys->ucNumOfChans;
    for (i = 0; i < CNAS_MIN(pstPcsChannelsSys->ucNumOfChans, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++)
    {
        pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
        pstFreqInfo->astFreqInfo[i].usChannel   = pstPcsChannelsSys->ausChan[i];
    }

}


VOS_VOID CNAS_PRL_MapCdmaGenericToBandChannel(
    CNAS_PRL_GENERIC_ACQ_FOR_1X_AND_IS95_STRU              *pstGenericAcq,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* 根据传入的信息，填写频段和channel number，根据CDG130的定义，此时都是
       Band 1的场景，band都是填写成band 1，channel直接填写 */

    pstFreqInfo->ulNum = pstGenericAcq->ucNumOfChans;
    for (i = 0; i < CNAS_MIN(pstGenericAcq->ucNumOfChans, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++)
    {
        pstFreqInfo->astFreqInfo[i].enBandClass = pstGenericAcq->astFreq[i].enBandClass;
        pstFreqInfo->astFreqInfo[i].usChannel   = pstGenericAcq->astFreq[i].usChannel;
    }
}




VOS_VOID CNAS_PRL_GetPrlAcqRecFreqListInfo(
    CNAS_PRL_ACQ_RECORD_STRU                               *pstPrlAcqRec,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8            enAcqType;

    /* 如果空指针或当前的Acq record是无效的，则直接返回个数为0 */
    if ((VOS_NULL_PTR == pstPrlAcqRec)
     || (VOS_FALSE    == pstPrlAcqRec->ucAcqValid))
    {
        pstFreqInfo->ulNum = 0;
        return;
    }

    enAcqType = pstPrlAcqRec->enAcqType;
    switch (enAcqType)
    {
        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_STANDARD_CHANNELS:
            CNAS_PRL_MapCellularCdmaStandardToBandChannel(&pstPrlAcqRec->u.stCellularStandardSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS:
            CNAS_PRL_MapCellularCdmaCustomToBandChannel(&pstPrlAcqRec->u.stCelluarCustomSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_PREFERRED:
            CNAS_PRL_MapCellularCdmaPreferToBandChannel(&pstPrlAcqRec->u.stCellularPreSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_BLOCKS:
            CNAS_PRL_MapPcsCdmaBlockToBandChannel(&pstPrlAcqRec->u.stPcsBlocksSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_CHANNELS:
            CNAS_PRL_MapPcsCdmaChannelToBandChannel(&pstPrlAcqRec->u.stPcsChannelsSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_1X_AND_IS95:
            CNAS_PRL_MapCdmaGenericToBandChannel(&pstPrlAcqRec->u.st1xAndIs95Sys, pstFreqInfo);
            break;

        /* 不支持的ACQ TYPE，返回个数为0 */
        case CNAS_PRL_ACQ_TYPE_JTACS_CDMA_STANDARD_CHANNELS:
        case CNAS_PRL_ACQ_TYPE_JTACS_CDMA_CUSTOM_CHANNELS:
        case CNAS_PRL_ACQ_TYPE_2G_BAND_USING_CHANNELS:
            pstFreqInfo->ulNum = 0;
            break;
        /* 修改个数乘上sizeof */
        case CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD:
            pstFreqInfo->ulNum = pstPrlAcqRec->u.stHrpdSys.ucNumOfChans;
            NAS_MEM_CPY_S(pstFreqInfo->astFreqInfo,
                          CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM * sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                          pstPrlAcqRec->u.stHrpdSys.astFreq,
                          pstFreqInfo->ulNum * sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));
            break;

        default:
            pstFreqInfo->ulNum = 0;
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_GetPrlAcqRecFreqListInfo():Wrong  AcqType");
            break;
    }
}



VOS_UINT16 CNAS_PRL_CalcPrlAcqRecTotalFreqNum(VOS_VOID)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usAcqRecNum;
    VOS_UINT16                          usTotalNum;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stFreqInfo;

    usAcqRecNum = CNAS_PRL_GetPrlAcqRecordNum();
    usTotalNum  = 0;

    /* 当前计算的频点可能有重复，目前先允许有这样的重复，暂时认为这个重复不会是特别的多 */
    for (i = 0; i < usAcqRecNum; i++)
    {
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(i);

        /* 空指针进行保护，直接跳过 */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        /*如果是无效的Acq Rec， 直接跳过*/
        if (VOS_FALSE == pstPrlAcqRec->ucAcqValid)
        {
            continue;
        }
        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

        usTotalNum += (VOS_UINT16)stFreqInfo.ulNum;
    }

    return usTotalNum;
}




VOS_UINT16 CNAS_PRL_CalcPrlSysRecListTotalFreqNum(
    VOS_UINT16                          usSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usTotalNum;
    VOS_UINT16                          usAcqIndex;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stFreqInfo;

    usTotalNum  = 0;
    usAcqIndex  = 0;

    /* 当前计算的频点可能有重复，目前先允许有这样的重复，暂时认为这个重复不会是特别的多 */
    for (i = 0; i < usSysRecNum; i++)
    {

        if (VOS_FALSE == pstSysRecord[i].ucSysRecValid)
        {
            continue;
        }

        usAcqIndex = pstSysRecord[i].usAcqIndex;

        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(usAcqIndex);

        /* 空指针进行保护 */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

        usTotalNum += (VOS_UINT16)stFreqInfo.ulNum;
    }

    return usTotalNum;
}


VOS_UINT32 CNAS_PRL_IsSidNidMatch_1XIS95(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    VOS_UINT16                          usTmpNid;

    if ((pstSysRecord->u.st1xAndIs95Id.usSid != pstSysInfo->usSid)
     && (pstSysRecord->u.st1xAndIs95Id.usSid != CNAS_PRL_WILDCARD_SID))
    {
        return VOS_FALSE;
    }

    if (CNAS_PRL_NID_INCL == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
    {
        usTmpNid = pstSysRecord->u.st1xAndIs95Id.usNid;
    }
    else
    {
        /* 默认认为NID为通配符 */
        if (CNAS_PRL_NID_NOT_INCL_WILD_CARD == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
        {
            usTmpNid = CNAS_PRL_WILDCARD_NID;
        }
        else if (CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
        {
            usTmpNid = CNAS_PRL_PUBLIC_NETWORK_NID;
        }
        else
        {
            usTmpNid = CNAS_PRL_WILDCARD_NID;
        }
    }

    if ((usTmpNid != pstSysInfo->usNid)
     && (usTmpNid != CNAS_PRL_WILDCARD_NID))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8 CNAS_PRL_GetPrl1xIs95SysRecordWildCardType(
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8   enWildCardType;
    VOS_UINT16                          usTmpNid;

    enWildCardType = CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD;

    /* 先看SID的通配符类型 */
    if (pstSysRecord->u.st1xAndIs95Id.usSid == CNAS_PRL_WILDCARD_SID)
    {
        enWildCardType = CNAS_PRL_WILDCARD_TYPE_SID;
    }

    /* 再看NID的通配符类型 */
    else
    {
        if (CNAS_PRL_NID_INCL == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
        {
            usTmpNid = pstSysRecord->u.st1xAndIs95Id.usNid;
        }
        else
        {
            if (CNAS_PRL_NID_NOT_INCL_WILD_CARD == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
            {
                usTmpNid = CNAS_PRL_WILDCARD_NID;
            }
            else if (CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
            {
                usTmpNid = CNAS_PRL_PUBLIC_NETWORK_NID;
            }
            else
            {
                usTmpNid = CNAS_PRL_WILDCARD_NID;
            }
        }

        if( usTmpNid == CNAS_PRL_WILDCARD_NID )
        {
          enWildCardType = CNAS_PRL_WILDCARD_TYPE_NID;
        }
        else
        {
          enWildCardType = CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD;
        }
    }
    return enWildCardType;
}


CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8 CNAS_PRL_GetPrl1xMccMncSysRecordWileCardType(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8                       enWildCardType;
    CNAS_PRL_SYS_TYPE_SID_NID_STRU                         *pstSidNid = VOS_NULL_PTR;
    CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU                      *pstMccMncId = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstSidNid      = &(pstSysRecord->u.stMccMncId.u.stSidNid);
    pstMccMncId    = &(pstSysRecord->u.stMccMncId);
    enWildCardType = CNAS_PRL_WILDCARD_TYPE_BUTT;

    if (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID == pstMccMncId->enMccMncSubType)
    {
        return CNAS_PRL_WILDCARD_TYPE_SID;
    }

    for (i = 0; i < CNAS_MIN((VOS_UINT32)pstSidNid->ucSidNidNum, CNAS_PRL_MCC_MNC_SID_MAX_NUM);i++)
    {
        /* 如果SID能找到，说明SID精确匹配，NID通配 */
        if (CNAS_PRL_WILDCARD_SID == pstSidNid->asSid[i])
        {
            enWildCardType = CNAS_PRL_WILDCARD_TYPE_SID;
            break;
        }
        else if (CNAS_PRL_WILDCARD_NID == pstSidNid->asNid[i])
        {
            enWildCardType = CNAS_PRL_WILDCARD_TYPE_NID;
            break;
        }
        else
        {
            enWildCardType = CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD;
        }
    }

    return enWildCardType;
}



CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8 CNAS_PRL_GetPrlSysRecordWildCardType(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    switch( pstSysRecord->enRecordType )
    {
        case CNAS_PRL_SYS_RECORD_TYPE_1X_IS95:
            return CNAS_PRL_GetPrl1xIs95SysRecordWildCardType(pstSysRecord);

        case CNAS_PRL_SYS_RECORD_TYPE_HRPD:
            break;

        case CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED:
            return CNAS_PRL_GetPrl1xMccMncSysRecordWileCardType(pstSysInfo, pstSysRecord);

        default:
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_GetPrlSysRecordWildCardType():Wrong  Sys Rec Type");
            break;
    }

    return CNAS_PRL_WILDCARD_TYPE_UNKNOWN;
}


CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_OnlySidNidMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8   enWildCardType;

    /* 当前如果不是两种特殊类型的SID，则认为不匹配 */
    if ((CNAS_PRL_SID_OPER_0 != pstSysInfo->usSid)
     && (CNAS_PRL_SID_OPER_1 != pstSysInfo->usSid))
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    }

    enWildCardType = CNAS_PRL_GetPrlSysRecordWildCardType(pstSysInfo, pstSysRecord);

    /* 如果当前SYS RECORD中不是通配符，则说明肯定是SID/NID都匹配 */
    if (CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD == enWildCardType)
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_SID_NID;
    }

    /* 只有NID通配符的时候，返回NID通配 */
    if (CNAS_PRL_WILDCARD_TYPE_NID == enWildCardType)
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID;
    }

    return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
}



CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_OnlySidNidBandMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{

    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8                       enWildCardType;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstOhmFreq = VOS_NULL_PTR;

    enWildCardType = CNAS_PRL_GetPrlSysRecordWildCardType(pstSysInfo, pstSysRecord);

    switch (enWildCardType)
    {
        case CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD:
            enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_SID_NID;
            break;

        case CNAS_PRL_WILDCARD_TYPE_NID:
            enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID;
            break;

        case CNAS_PRL_WILDCARD_TYPE_SID:
            {
                pstOhmFreq = CNAS_CCB_GetCdmaOhmFreq();

                /* 如果当前系统频点是overheader消息的频点，则这里需要对hash频点的系统match做特殊处理 */
                if ((pstSysInfo->stFreq.enBandClass == pstOhmFreq->enBandClass)
                 && (pstSysInfo->stFreq.usChannel   == pstOhmFreq->usChannel))
                {
                    enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID;
                }
                else
                {
                    enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
                }
            }
            break;

        case CNAS_PRL_WILDCARD_TYPE_UNKNOWN:
        default:
            enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
            break;
    }

    return enMatchLvl;
}


CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_SidNidBandChannelMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8   enWildCardType;

    enWildCardType = CNAS_PRL_GetPrlSysRecordWildCardType(pstSysInfo, pstSysRecord);

    switch (enWildCardType)
    {
        case CNAS_PRL_WILDCARD_TYPE_SID:
            return CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID;

        case CNAS_PRL_WILDCARD_TYPE_NID:
            return CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID;

        case CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD:
            return CNAS_PRL_SID_NID_MATCH_LVL_SID_NID;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_GetSysRecordChannelMatchLvl():Wrong Sys wildcard Type");
            break;
    }

    return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;

}



CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_Get1xSysMatchSysRecordLvl(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord;
    VOS_UINT32                                              ulIsSidNidMatched;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;

    ulIsSidNidMatched      = VOS_FALSE;

     /* 系统记录无效，不处理 */
    if (VOS_FALSE == pstSysRecord->ucSysRecValid)
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    }

    if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord->enRecordType)
    {
        ulIsSidNidMatched = CNAS_PRL_IsSidNidMatch_1XIS95(pstSysInfo, pstSysRecord);
    }
    else if (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
    {
        ulIsSidNidMatched = CNAS_PRL_IsSidNidMatch_MccMncBased(pstSysInfo, pstSysRecord);
    }
    else
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    }

    /* 如果SID和NID都不匹配，此时当前系统肯定和系统记录不匹配 */
    if ( VOS_FALSE == ulIsSidNidMatched )
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    }

    pstAcqRecord  = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);

    /* 空指针保护 */
    if (VOS_NULL_PTR == pstAcqRecord)
    {
        return CNAS_PRL_GetMatchLvl_OnlySidNidMatch(pstSysInfo, pstSysRecord);
    }

    enBandChannelMatch = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstAcqRecord);
    /* 如果band都没有匹配，说明此时仅仅匹配了SID和NID */
    if ( CNAS_PRL_BAND_CHANNEL_NOT_MATCH == enBandChannelMatch )
    {
        return CNAS_PRL_GetMatchLvl_OnlySidNidMatch(pstSysInfo, pstSysRecord);
    }

    /* 如果CHANNEL没有匹配，说明此时仅仅匹配了SID、NID和BAND */
    if ( CNAS_PRL_BAND_MATCH == enBandChannelMatch )
    {
        return CNAS_PRL_GetMatchLvl_OnlySidNidBandMatch(pstSysInfo, pstSysRecord);
    }

    /* 到这里说明是SID、NID、BAND、CHANNEL都匹配，返回channel匹配情况下的匹配等级 */
    return CNAS_PRL_GetMatchLvl_SidNidBandChannelMatch(pstSysInfo, pstSysRecord);

}


VOS_VOID CNAS_PRL_Get1xSysGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstPrlSysInfo;
    VOS_UINT16                                              usGeoFirstSysRecIndex;
    VOS_UINT32                                              ulIsMatched;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enTmpMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstTmpSysRecord;
    VOS_UINT16                                              usMostMatchedIndex;

    pstPrlSysInfo               = CNAS_PRL_GetPrlSysInfoAddr();
    ulIsMatched                 = VOS_FALSE;
    usGeoFirstSysRecIndex       = 0;
    enMatchLvl                  = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    pstTmpSysRecord             = pstPrlSysInfo->pstSysRecord;

    /* 初始化输出参数 */
    pstGeoListInfo->ucGeoNum    = 0;
    pstGeoListInfo->usSid       = pstSysInfo->usSid;
    pstGeoListInfo->usNid       = pstSysInfo->usNid;

    usMostMatchedIndex          = 0;

    for (i = 0; i < pstPrlSysInfo->usSysRecordNum; i++,pstTmpSysRecord++)
    {

        /* 每次进新的GEO(非第一个GEO)或者到了系统列表的最后一个的时候，判断之前遍历的时候，是否存在matach的记录 */
        if (((CNAS_PRL_GEO_REGION_IND_NEW == pstTmpSysRecord->enGeoInd)
            &&(i != 0))
          ||(i == (pstPrlSysInfo->usSysRecordNum -1)))
        {
            if (VOS_TRUE == ulIsMatched)
            {
                pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].enMatchLvl             = enMatchLvl;
                pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoFirstSysRecIndex  = usGeoFirstSysRecIndex;
                pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usMostMatchedIndex     = usMostMatchedIndex;

                if ((i                            == (pstPrlSysInfo->usSysRecordNum -1))
                 && (CNAS_PRL_GEO_REGION_IND_SAME == pstTmpSysRecord->enGeoInd))
                {
                    pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoSysRecNum     = i - usGeoFirstSysRecIndex + 1;
                    pstGeoListInfo->ucGeoNum++;

                    return;
                }
                else
                {
                    pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoSysRecNum     = i - usGeoFirstSysRecIndex;
                    pstGeoListInfo->ucGeoNum++;
                }

                ulIsMatched        = VOS_FALSE;
                enMatchLvl         = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
                usMostMatchedIndex = 0;
            }
        }

        /* 判断传入的系统信息，是否和系统记录中的相匹配 */
        enTmpMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo,
                                                           pstTmpSysRecord);
        if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enTmpMatchLvl)
        {
            ulIsMatched = VOS_TRUE;

            /* 如果匹配程度有提高，则更新匹配程度 */
            if (enMatchLvl < enTmpMatchLvl)
            {
                enMatchLvl         = enTmpMatchLvl;
                usMostMatchedIndex = i;
            }
        }

        /* 记录新GEO中的第一个记录的位置 */
        if (CNAS_PRL_GEO_REGION_IND_NEW == pstTmpSysRecord->enGeoInd)
        {
            usGeoFirstSysRecIndex = i;
        }

        /* 处理一下只有一个记录并且匹配的特殊情况 */
        if ((pstPrlSysInfo->usSysRecordNum == (i+1))
         && (VOS_TRUE == ulIsMatched))
        {
            pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].enMatchLvl             = enMatchLvl;
            pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoFirstSysRecIndex  = usGeoFirstSysRecIndex;
            pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoSysRecNum         = i - usGeoFirstSysRecIndex + 1;
            pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usMostMatchedIndex     = usMostMatchedIndex;
            pstGeoListInfo->ucGeoNum++;
        }
    }
}


VOS_VOID CNAS_PRL_BuildGeoSysRecList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    VOS_UINT8                                               ucIgnoreNegSys,
    VOS_UINT16                                             *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usMostMatchGeoNum;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMostMatchLvl;
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstPrlSysInfo;
    VOS_UINT16                                              usGeoFirstSysRecIndex;

    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChanMostMatchLevel;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChanMatchLevel;

    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstTmpSysRecord;

    enMostMatchLvl              = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    usMostMatchGeoNum           = 0;

    pstPrlSysInfo = CNAS_PRL_GetPrlSysInfoAddr();



    /* 找到最匹配的GEO，输出对应的系统记录列表 */
    for (i = 0; i < CNAS_MIN(pstGeoListInfo->ucGeoNum, CNAS_PRL_MAX_MATCHING_GEO_NUM); i++)
    {
        /* 如果需要忽略negative系统，对于匹配的GEO中系统记录总个数为1的情况，对于匹配的系统
           是negative系统,则跳过该GEO继续查找下一个GEO */
        if ((VOS_TRUE  == ucIgnoreNegSys)
         && (1         == pstGeoListInfo->astGeoInfoList[i].usGeoSysRecNum))
        {
            pstTmpSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex);

            if (VOS_NULL_PTR == pstTmpSysRecord)
            {
                continue;
            }

            if (CNAS_PRL_PREF_NEG_SYS_NEG == pstTmpSysRecord->enPrefNegSys)
            {
                continue;
            }
        }

        if (enMostMatchLvl < pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
        {

            enMostMatchLvl      = pstGeoListInfo->astGeoInfoList[i].enMatchLvl;
            usMostMatchGeoNum   = i;
        }
        else if ((enMostMatchLvl                       == pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
              && (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != pstGeoListInfo->astGeoInfoList[i].enMatchLvl))
        {
            enBandChanMostMatchLevel = CNAS_PRL_GetBandChanMatchInfoOfGeoSys(pstSysInfo, &(pstGeoListInfo->astGeoInfoList[usMostMatchGeoNum]));
            enBandChanMatchLevel     = CNAS_PRL_GetBandChanMatchInfoOfGeoSys(pstSysInfo, &(pstGeoListInfo->astGeoInfoList[i]));

            if (enBandChanMostMatchLevel < enBandChanMatchLevel)
            {
                usMostMatchGeoNum   = i;
            }
        }
        else
        {}
    }

    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enMostMatchLvl)
    {
        *pusSysRecNum = 0;
        return;
    }

    usGeoFirstSysRecIndex = pstGeoListInfo->astGeoInfoList[usMostMatchGeoNum].usGeoFirstSysRecIndex;
    *pusSysRecNum = pstGeoListInfo->astGeoInfoList[usMostMatchGeoNum].usGeoSysRecNum;

    NAS_MEM_CPY_S(pstSysRecord,
                  sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum),
                  pstPrlSysInfo->pstSysRecord + usGeoFirstSysRecIndex,
                  sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum));

}


VOS_UINT8 CNAS_PRL_IsSysRecordVaild(
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstSysRecord
)
{
    if ((VOS_NULL_PTR                     == pstSysRecord)
     || (VOS_FALSE                        == pstSysRecord->ucSysRecValid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT8 CNAS_PRL_Is1xSysNegative_BandChanAmbiguousMatch(
    CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;

    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMostMatchNegSysLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMostMatchPrefSysLvl;

    enMostMatchNegSysLvl  = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enMostMatchPrefSysLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;

    for (i = 0; i < pstMatchedGeoInfo->usGeoSysRecNum; i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(pstMatchedGeoInfo->usGeoFirstSysRecIndex + i);

        if (VOS_FALSE == CNAS_PRL_IsSysRecordVaild(pstSysRecord))
        {
            continue;
        }

        enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstSysRecord);

        /*如果一个geo中同时存在匹配的pref系统neg系统，比较匹配等级，如果相等，不再比较band channel等级，直接作pref系统 */
        if (CNAS_PRL_PREF_NEG_SYS_PREF  == pstSysRecord->enPrefNegSys)
        {
            if (enSysMatchLvl > enMostMatchPrefSysLvl)
            {
                enMostMatchPrefSysLvl = enSysMatchLvl;
            }
        }
        else
        {
            if (enSysMatchLvl > enMostMatchNegSysLvl)
            {
                enMostMatchNegSysLvl = enSysMatchLvl;
            }
        }

    }

    if (enMostMatchNegSysLvl > enMostMatchPrefSysLvl)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}

CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_ENUM_UINT8 CNAS_PRL_CmpIncludeRelationOfTwoAcqRecord(
    CNAS_PRL_ACQ_RECORD_STRU                               *pstFirAcqRecord,
    CNAS_PRL_ACQ_RECORD_STRU                               *pstSecAcqRecord
)
{

    VOS_UINT8                                               i;
    VOS_UINT8                                               j;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stFirAcqRecFreqInfo;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stSecAcqRecFreqInfo;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstMoreChanAcqRecFreqInfo = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstLessChanAcqRecFreqInfo = VOS_NULL_PTR;

    NAS_MEM_SET_S(&stFirAcqRecFreqInfo, sizeof(stFirAcqRecFreqInfo), 0x0, sizeof(stFirAcqRecFreqInfo));
    NAS_MEM_SET_S(&stSecAcqRecFreqInfo, sizeof(stSecAcqRecFreqInfo), 0x0, sizeof(stSecAcqRecFreqInfo));

    CNAS_PRL_GetPrlAcqRecFreqListInfo(pstFirAcqRecord, &stFirAcqRecFreqInfo);
    CNAS_PRL_GetPrlAcqRecFreqListInfo(pstSecAcqRecord, &stSecAcqRecFreqInfo);

    if (stFirAcqRecFreqInfo.ulNum > stSecAcqRecFreqInfo.ulNum)
    {
        pstMoreChanAcqRecFreqInfo = &stFirAcqRecFreqInfo;
        pstLessChanAcqRecFreqInfo = &stSecAcqRecFreqInfo;
    }
    else
    {
        pstMoreChanAcqRecFreqInfo = &stSecAcqRecFreqInfo;
        pstLessChanAcqRecFreqInfo = &stFirAcqRecFreqInfo;
    }

    /*如果存在包含关系，则频点数较少的捕获记录中，每一个频点都会在频点数较多的捕获记录中存在 */
    for (i = 0; i < pstLessChanAcqRecFreqInfo->ulNum; i++)
    {
        for (j = 0; j < pstMoreChanAcqRecFreqInfo->ulNum; j++)
        {
            if ((pstLessChanAcqRecFreqInfo->astFreqInfo[i].enBandClass == pstMoreChanAcqRecFreqInfo->astFreqInfo[j].enBandClass)
             && (pstLessChanAcqRecFreqInfo->astFreqInfo[i].usChannel   == pstMoreChanAcqRecFreqInfo->astFreqInfo[j].usChannel))
            {
                break;
            }

            if (pstMoreChanAcqRecFreqInfo->ulNum - 1 == j)
            {
                return CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_NOT_INCLUDE;
            }

        }
    }

    /*如果存在包含关系，则频点数较少的为被包含，频点数相同则表示2个捕获记录所对应的频点完全一样 */
    if (stFirAcqRecFreqInfo.ulNum > stSecAcqRecFreqInfo.ulNum)
    {
        return CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_FIR_INCLUDE_SEC;
    }
    else if (stFirAcqRecFreqInfo.ulNum < stSecAcqRecFreqInfo.ulNum)
    {
        return CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SEC_INCLUDE_FIR;
    }
    else
    {
        return CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SAME;
    }

}





CNAS_PRL_BAND_CHANNEL_MATCH_CMP_ENUM_UINT8 CNAS_PRL_CmpSysBandChanMatchLvlInTwoSysRecord(
    CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstFirSysRecord,
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstSecSysRecord
)
{
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enFirSysBandChanMatchLvl;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enSecSysBandChanMatchLvl;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstFirAcqRecord   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstSecAcqRecord   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_ENUM_UINT8         enIncludeRelation;

    enFirSysBandChanMatchLvl = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
    enSecSysBandChanMatchLvl = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;

    /* 依据系统记录获取对应的捕获记录 */
    pstFirAcqRecord   = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstFirSysRecord->usAcqIndex);

    if (VOS_NULL_PTR != pstFirAcqRecord)
    {
        enFirSysBandChanMatchLvl = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstFirAcqRecord);
    }

    pstSecAcqRecord   = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSecSysRecord->usAcqIndex);

    if (VOS_NULL_PTR != pstSecAcqRecord)
    {
        enSecSysBandChanMatchLvl = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstSecAcqRecord);
    }


    /* 比较捕获记录中，系统的band channel的匹配程度 */
    if (enFirSysBandChanMatchLvl > enSecSysBandChanMatchLvl)
    {
        return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_FIR_RECORD_HIGH;
    }
    else if (enFirSysBandChanMatchLvl < enSecSysBandChanMatchLvl)
    {
        return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_SEC_RECORD_HIGH;
    }
    else
    {
        /*比较两个捕获记录所对应的频点之前是否存在包含关系，属于被包含关系的捕获记录匹配程度更高 */
        enIncludeRelation = CNAS_PRL_CmpIncludeRelationOfTwoAcqRecord(pstFirAcqRecord, pstSecAcqRecord);

        switch(enIncludeRelation)
        {
            case CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_FIR_INCLUDE_SEC:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_SEC_RECORD_HIGH;

            case CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SEC_INCLUDE_FIR:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_FIR_RECORD_HIGH;

            case CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SAME:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_TWO_RECORD_SAME;

            case CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_NOT_INCLUDE:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_UNKNOWN;

            default:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_BUTT;
        }
    }
}


VOS_UINT8 CNAS_PRL_Is1xSysNegative_BandChanAccurateMatch(
    CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enPrefSysMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enPrefSysMostMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enNegSysMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enNegSysMostMatchLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord         = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMostPrefSysRecord = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMostNegSysRecord  = VOS_NULL_PTR;

    enPrefSysMostMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enNegSysMostMatchLvl  = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enPrefSysMatchLvl     = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enNegSysMatchLvl      = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;

    for (i = 0; i < pstMatchedGeoInfo->usGeoSysRecNum; i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(pstMatchedGeoInfo->usGeoFirstSysRecIndex + i);

        if (VOS_FALSE == CNAS_PRL_IsSysRecordVaild(pstSysRecord))
        {
            continue;
        }

        /* 根据cdg143 5.8.3.1, 检查negative系统注意以下两种场景:
        Consider a system table with two entries in the same GEO of:
        0001: SID=00004; NID=05001; PREF=PREFERRED; ACQ_INDEX = 1
        0002: SID=00004; NID=65535; PREF=NEGATIVE; ACQ_INDEX=1

        Example: Consider a system table with two entries in the same GEO of:
        0001: SID=00004; NID=65535; PREF=PREFERRED; ACQ_INDEX = [PCS CHAN 25]
        0002: SID=00004; NID=65535; PREF=NEGATIVE; ACQ_INDEX  = [PCS BLOCK ANY]
        */

        if (CNAS_PRL_PREF_NEG_SYS_PREF  == pstSysRecord->enPrefNegSys)
        {
            /*记录最匹配的pref系统的等级和索引 */
            enPrefSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstSysRecord);

            if (enPrefSysMatchLvl > enPrefSysMostMatchLvl)
            {
                enPrefSysMostMatchLvl = enPrefSysMatchLvl;
                pstMostPrefSysRecord  = pstSysRecord;
            }
        }
        else
        {
            /*记录最匹配的Neg系统的等级和索引 */
            enNegSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstSysRecord);

            if (enNegSysMatchLvl > enNegSysMostMatchLvl)
            {
                enNegSysMostMatchLvl = enNegSysMatchLvl;
                pstMostNegSysRecord  = pstSysRecord;
            }
        }
    }

    /* 比较pref系统和neg系统的匹配程度 */
    if (enPrefSysMostMatchLvl > enNegSysMostMatchLvl)
    {
        return VOS_FALSE;
    }
    else if (enPrefSysMostMatchLvl < enNegSysMostMatchLvl)
    {
        return VOS_TRUE;
    }
    else
    {
        if (VOS_NULL_PTR == pstMostNegSysRecord)
        {
            return VOS_FALSE;
        }

        if (VOS_NULL_PTR == pstMostPrefSysRecord)
        {
            return VOS_TRUE;
        }

        /* 如果 pref系统和 neg系统的sid nid匹配程度相同，则比较band channel匹配等级，只要不是neg的比配程度更高，则判断为perf系统　*/
        if (CNAS_PRL_BAND_CHANNEL_MATCH_CMP_FIR_RECORD_HIGH == CNAS_PRL_CmpSysBandChanMatchLvlInTwoSysRecord(pstSysInfo,
                                                                                                             pstMostNegSysRecord,
                                                                                                             pstMostPrefSysRecord))
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }

}


VOS_UINT8 CNAS_PRL_Is1xSysNegativeInCurGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
)
{
    /* 通过NV项中的值判断采用哪一种判断方式*/
    if (CNAS_XSD_NEG_PREF_SYS_CMP_BAND_CHAN_AMBIGUOUS_MATCH == CNAS_XSD_GetNegPrefSysCmpType())
    {
        return CNAS_PRL_Is1xSysNegative_BandChanAmbiguousMatch(pstSysInfo, pstMatchedGeoInfo);

    }
    else
    {
        return CNAS_PRL_Is1xSysNegative_BandChanAccurateMatch(pstSysInfo, pstMatchedGeoInfo);
    }
}



VOS_UINT32 CNAS_PRL_Is1xSysNegativeInPrl(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;
    VOS_UINT16                                              ucMostMatchIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;

    /* 做下保护，以免异常 */
    if (0 == pstGeoListInfo->ucGeoNum)
    {
        return VOS_FALSE;
    }

    /* cdg143 7.1.2.6:
       The placement of negative systems in the system table can vary. In some cases, a
       policy can dictate that all negative systems are placed in their own GEO or a combined
       GEO. In other cases, policy may dictate that negative systems are located in the same
       GEO as the preferred systems of the same market. Maintainability is increased if
       negative systems appear at the bottom of their appropriate GEO and it ensures that the
       frequencies of preferred systems of the GEO are immediately scanned.

       negative系统在PRL中放置规则如下:
       1. 一种场景，negative系统通常以独立的GEO出现；
       2. 另外，negative系统也可以与preferred系统共处同一个GEO，从维护性来说，negative系统通常
          会放置在GEO中底部。
    */

    /* 从GEO list中找出最匹配的GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstSysInfo, pstGeoListInfo);

    /* 从最匹配的GEO中获取PRL表中最匹配的系统记录索引 */
    enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstSysInfo, pstMostMatchGeoInfo, &ucMostMatchIndex);

    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enSysMatchLvl)
    {
        return CNAS_PRL_Is1xSysNegativeInCurGeo(pstSysInfo, pstMostMatchGeoInfo);

    }

    return VOS_FALSE;

}


VOS_UINT8 CNAS_PRL_GetPrefOnlyFlg(VOS_VOID)
{
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeaderInfo = VOS_NULL_PTR;

    pstPrlHeaderInfo = CNAS_PRL_GetPrlHeaderInfoAddr();

    return pstPrlHeaderInfo->ucPreferOnly;
}


VOS_UINT32 CNAS_PRL_IsMostPref1xSysInGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsMostPref;
    VOS_UINT16                                              ucMostMatchIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord        = VOS_NULL_PTR;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIs1xSysRecordExist;

    VOS_UINT8                                               ucIsExistWildcardSid;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enCurSysMatchLvl;

    ucIsExistWildcardSid  = VOS_FALSE;

    ulIs1xSysRecordExist  = VOS_FALSE;

    ulIsMostPref          = VOS_FALSE;
    /* 如果当前不在GEO里，说明肯定不会是最优系统 */
    if (0 == pstGeoListInfo->ucGeoNum)
    {
        return ulIsMostPref;
    }

    /* 从GEO list中找出最匹配的GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstCurSysInfo ,pstGeoListInfo);

    /* 从最匹配的GEO中获取PRL表中最匹配的系统记录索引 */
    enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstCurSysInfo, pstMostMatchGeoInfo, &ucMostMatchIndex);

    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enSysMatchLvl)
    {
        for (i = 0; i < pstMostMatchGeoInfo->usGeoSysRecNum; i++)
        {
            pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(pstMostMatchGeoInfo->usGeoFirstSysRecIndex + i);

            if (VOS_FALSE == CNAS_PRL_IsSysRecordVaild(pstSysRecord))
            {
                continue;
            }

            if (VOS_TRUE == CNAS_PRL_Is1xSysRecord(pstSysRecord))
            {
                ulIs1xSysRecordExist = VOS_TRUE;
            }

            enCurSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstCurSysInfo, pstSysRecord);

            /* 获取GEO中匹配等级最高的系统记录 */
            if (enSysMatchLvl == enCurSysMatchLvl)
            {
                pstAcqRecord  = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);

                /* 如果在GEO中匹配等级最高的系统中，当前系统的band与channel匹配, 返回TRUE */
                if (CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID == enSysMatchLvl)
                {
                    if (CNAS_PRL_BAND_CHANNEL_MATCH == CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstCurSysInfo->stFreq), pstAcqRecord))
                    {
                        ulIsMostPref = VOS_TRUE;
                        break;
                    }
                }
                else
                {
                    ulIsMostPref = VOS_TRUE;
                    break;
                }
            }


            /* 记录geo中是否存在sid通配匹配且为pref的系统*/
            if ((CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID == enCurSysMatchLvl)
             && (CNAS_PRL_PREF_NEG_SYS_PREF              == pstSysRecord->enPrefNegSys))
            {
                ucIsExistWildcardSid = VOS_TRUE;
            }


            if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
            {
                /* 存在优先级为more的记录，且之前存在SID通配匹配，且该系统在geo中pref系统，则为最优系统 */
                if (VOS_TRUE  == ucIsExistWildcardSid)
                {
                    ulIsMostPref = VOS_TRUE;
                }

                /* 该变量用于过滤如下场景: 比当前系统更优的系统是全是HRPD系统 */
                if (VOS_TRUE == ulIs1xSysRecordExist)
                {
                    break;
                }
            }
        }
    }

    return ulIsMostPref;
}



VOS_UINT32 CNAS_PRL_Is1xSysIdMatched(
    VOS_UINT16                          usSrcSid,
    VOS_UINT16                          usSrcNid,
    VOS_UINT16                          usDstSid,
    VOS_UINT16                          usDstNid
)
{
    if ((usDstSid != usSrcSid)
     && (usDstSid != CNAS_PRL_WILDCARD_SID))
    {
        return VOS_FALSE;
    }

    if ((usDstNid != usSrcNid)
     && (usDstNid != CNAS_PRL_WILDCARD_NID))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_PRL_Is1xSysIdInSysIdList(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstSrcSysId,
    VOS_UINT16                          usDtsSysIdNum,
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstDstSysIdInfo
)
{
    VOS_UINT16                          i;

    for (i = 0; i < usDtsSysIdNum; i++)
    {
        if (VOS_TRUE == CNAS_PRL_Is1xSysIdMatched(pstSrcSysId->usSid, pstSrcSysId->usNid,
                                                  pstDstSysIdInfo[i].usSid,pstDstSysIdInfo[i].usNid))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}




VOS_UINT32 CNAS_PRL_Is1xSysMatched(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSrcSys,
    CNAS_PRL_1X_SYSTEM_STRU            *pstDstSys
)
{
    if ((pstDstSys->usSid != pstSrcSys->usSid)
     && (pstDstSys->usSid != CNAS_PRL_WILDCARD_SID))
    {
        return VOS_FALSE;
    }

    if ((pstDstSys->usNid != pstSrcSys->usNid)
     && (pstDstSys->usNid != CNAS_PRL_WILDCARD_NID))
    {
        return VOS_FALSE;
    }

    if (pstDstSys->stFreq.enBandClass != pstSrcSys->stFreq.enBandClass)
    {
        return VOS_FALSE;
    }

    if (pstDstSys->stFreq.usChannel != pstSrcSys->stFreq.usChannel)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeoInfo,
    VOS_UINT16                         *pusIndex
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstSysRecordAddr = VOS_NULL_PTR;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enTempMatchLvl;
    VOS_UINT16                                              usGeoEndIndex;
    VOS_UINT16                                              i;

    enMatchLvl     = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enTempMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    *pusIndex      = 0;

    pstSysRecordAddr = CNAS_PRL_GetPrlSysInfoAddr();

    usGeoEndIndex    = pstMatchedGeoInfo->usGeoFirstSysRecIndex + pstMatchedGeoInfo->usGeoSysRecNum;

    for (i = pstMatchedGeoInfo->usGeoFirstSysRecIndex; i < usGeoEndIndex; i++)
    {
        /* get matched index of current system in GEO */
        enTempMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo,
                                                           (pstSysRecordAddr->pstSysRecord + i));

        /* update matche level */
        if (enMatchLvl < enTempMatchLvl)
        {
            enMatchLvl = enTempMatchLvl;
            *pusIndex  = i;
        }
    }

    return enMatchLvl;
}


CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32  CNAS_PRL_CmpSysPriorityofTwoSystemsInSameGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMatchedGeoInfo
)
{
    VOS_UINT16                                              usOrigSysIndex;
    VOS_UINT16                                              usCurSysIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enOrigSysMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enCurSysMatchLvl;
    CNAS_PRL_PREF_NEG_SYS_ENUM_UINT8                        enOrigSysPri;
    CNAS_PRL_PREF_NEG_SYS_ENUM_UINT8                        enCurSysPri;
    VOS_UINT16                                              i;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enCurSysRoamingInd;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enOrigSysRoamingInd;
    VOS_UINT8                                               ucIsCurSysHome;
    VOS_UINT8                                               ucIsOrigSysHome;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstOrigSysRecord = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstCurSysRecord  = VOS_NULL_PTR;

    /* get current system matched index in GEO */
    enCurSysMatchLvl  = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstCurSysInfo,
                                                                  pstMatchedGeoInfo,
                                                                  &usCurSysIndex);

    /* get orignal system matched index in GEO */
    enOrigSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstOrigSysInfo,
                                                                  pstMatchedGeoInfo,
                                                                  &usOrigSysIndex);

    if ((CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enCurSysMatchLvl)
     || (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enOrigSysMatchLvl))
    {
        /* In theory, it should not happen. */
        CNAS_ERROR_LOG(UEPS_PID_XSD,
                       "CNAS_PRL_CmpSysPriorityofTwoSystemsInSameGeo: somewhere is error!");

        return CNAS_PRL_SYS_PRI_UNKNOWN;
    }

    if (usCurSysIndex == usOrigSysIndex)
    {
        return CNAS_PRL_SYS_PRI_SAME;
    }

    pstOrigSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(usOrigSysIndex);
    if (VOS_NULL_PTR == pstOrigSysRecord)
    {
        return CNAS_PRL_SYS_PRI_UNKNOWN;
    }
    enOrigSysPri = pstOrigSysRecord->enPrefNegSys;

    pstCurSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(usCurSysIndex);
    if (VOS_NULL_PTR == pstCurSysRecord)
    {
        return CNAS_PRL_SYS_PRI_UNKNOWN;
    }
    enCurSysPri  = pstCurSysRecord->enPrefNegSys;

    ucIsOrigSysHome = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstOrigSysInfo);
    ucIsCurSysHome  = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo);

    enOrigSysPri    = (VOS_TRUE == ucIsOrigSysHome) ? CNAS_PRL_PREF_NEG_SYS_PREF : enOrigSysPri;
    enCurSysPri     = (VOS_TRUE == ucIsCurSysHome) ? CNAS_PRL_PREF_NEG_SYS_PREF : enCurSysPri;


    if ((CNAS_PRL_PREF_NEG_SYS_NEG == enCurSysPri)
     && (CNAS_PRL_PREF_NEG_SYS_NEG == enOrigSysPri))
    {
        return CNAS_PRL_SYS_PRI_SAME;
    }

    if ((CNAS_PRL_PREF_NEG_SYS_NEG != enCurSysPri)
     && (CNAS_PRL_PREF_NEG_SYS_NEG == enOrigSysPri))
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    if ((CNAS_PRL_PREF_NEG_SYS_NEG == enCurSysPri)
     && (CNAS_PRL_PREF_NEG_SYS_NEG != enOrigSysPri))
    {
        return CNAS_PRL_SYS_PRI_LOW;
    }

    for (i = CNAS_MIN(usCurSysIndex, usOrigSysIndex); i < (CNAS_MAX(usCurSysIndex, usOrigSysIndex) + 1); i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(i);
        if (VOS_NULL_PTR == pstSysRecord)
        {
            continue;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
        {
            break;
        }
    }

    /* last system record is MORE or no MORE is met, two system priority is same */
    if (i >= CNAS_MAX(usCurSysIndex, usOrigSysIndex))
    {
        /* reference from chapter 2.11 in CDG 143:
           3. If the roaming indicator of one system is more favorable than the other (as defined in
           Req. 2.6.2), select the more favorable one.
        */
        enOrigSysRoamingInd = (VOS_TRUE == ucIsOrigSysHome) ? CNAS_PRL_SYS_ROAMING_STATUS_OFF : pstOrigSysRecord->enRoamingInd;
        enCurSysRoamingInd  = (VOS_TRUE == ucIsCurSysHome) ? CNAS_PRL_SYS_ROAMING_STATUS_OFF : pstCurSysRecord->enRoamingInd;

        /*****************************************************************
        *
        * 1、enOrigRoamingInd非漫游，enCurRoamingInd漫游，返回CNAS_PRL_SYS_PRI_LOW
        * 2、enOrigRoamingInd漫游，enCurRoamingInd非漫游，返回CNAS_PRL_SYS_PRI_HIGH
        * 3、其余场景返回CNAS_PRL_SYS_PRI_SAME
        *
        ******************************************************************/
        return (CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32)((enOrigSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_OFF) ? ( (enCurSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_OFF)
                                                                                                                ? CNAS_PRL_SYS_PRI_SAME : CNAS_PRL_SYS_PRI_LOW)
                                                                                                            : ( (enCurSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_OFF)
                                                                                                                ? CNAS_PRL_SYS_PRI_HIGH : CNAS_PRL_SYS_PRI_SAME));
    }

    if (usCurSysIndex < usOrigSysIndex)
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    return CNAS_PRL_SYS_PRI_LOW;
}


CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 CNAS_PRL_GetRoamingIndInMatchedGeolist(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    VOS_UINT8                                               i;
    VOS_UINT16                                              ucMostMatchIndex;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stMostMatchGeoListInfo;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enRoamingInd;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enTempRoamingInd;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;

    NAS_MEM_SET_S(&stMostMatchGeoListInfo, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* 从GEO list获取等级最高的GEO列表 */
    CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList(pstSysInfo, pstGeoListInfo, &stMostMatchGeoListInfo);

    enRoamingInd = CNAS_PRL_SYS_ROAMING_STATUS_RESERVED;

    for (i = 0; i < stMostMatchGeoListInfo.ucGeoNum; i++)
    {
        enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstSysInfo,
                                                                  &stMostMatchGeoListInfo.astGeoInfoList[i],
                                                                  &ucMostMatchIndex);


        if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enSysMatchLvl)
        {
            pstSysRecord  = CNAS_PRL_GetSpecifiedPrlSysRecord(ucMostMatchIndex);

            if (VOS_NULL_PTR != pstSysRecord)
            {
                enTempRoamingInd = pstSysRecord->enRoamingInd;

                if (CNAS_PRL_SYS_ROAMING_STATUS_OFF == enTempRoamingInd)
                {
                    return CNAS_PRL_SYS_ROAMING_STATUS_OFF;
                }

                /* 根据cdg130 5.3.9.3.2章节协议:
                  typically ‘roaming indicator off’ would be preferred over ‘roaming
                  indicator on’ or ‘roaming indicator flashing’; and, ‘roaming indicator on’ would be
                  preferred over ‘roaming indicator flashing’.

                  这里返回漫游值最小系统记录的roaming指示值，即对非协议中提到其他漫游指示值，这里按漫游值
                  最小，优先级最高处理，roaming indicator off除外；
                 */
                if (enTempRoamingInd < enRoamingInd)
                {
                    enRoamingInd = enTempRoamingInd;
                }
            }
        }
    }

    return enRoamingInd;

}



#if 0

VOS_UINT16 CNAS_PRL_GetAcqRecIndexAccordingToSysRecIndex(
    VOS_UINT16                          usSysRecIndex
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstSysRecordAddr = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstCurSysRecord  = VOS_NULL_PTR;

    pstSysRecordAddr = CNAS_PRL_GetPrlSysInfoAddr();

    pstCurSysRecord = (pstSysRecordAddr->pstSysRecord + usSysRecIndex);

    return pstCurSysRecord->usAcqIndex;
}
#endif


VOS_UINT32 CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                    *penRoamingInd
)
{
    if (0 != pstGeoListInfo->ucGeoNum)
    {
        if (VOS_TRUE == CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstSysInfo))
        {
            return VOS_TRUE;
        }

        *penRoamingInd = CNAS_PRL_GetRoamingIndInMatchedGeolist(pstSysInfo,pstGeoListInfo);

        /* is home roaming indicator? */
        if (CNAS_PRL_SYS_ROAMING_STATUS_OFF == *penRoamingInd)
        {
            return VOS_TRUE;
        }
    }

    /* TO DO: implement home group and roam mask (reference from chapter 2.6.2 in cdg143 and
        chapter 5.3.9.1 in cdg130)
    ) */

    return VOS_FALSE;
}


CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareRoamingIndicatorPreferenceOfTwoSystems(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstCurSysGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstOrigSysGeoListInfo
)
{
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enOrigSysRoamingInd;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enCurSysRoamingInd;
    VOS_UINT32                                              ulIsOrigSysHomeRoaming;
    VOS_UINT32                                              ulIsCurSysHomeRoaming;

    enOrigSysRoamingInd = 0xFF;
    enCurSysRoamingInd  = 0xFF;

    /* reference from chapter 5.3.9.3.2 in cdg130
      Where both systems are listed in different GEOs and the roaming indicators are
      different then typically ‘roaming indicator off’ would be preferred over ‘roaming
      indicator on’ or ‘roaming indicator flashing’; and, ‘roaming indicator on’ would be
      preferred over ‘roaming indicator flashing’
     */
    ulIsOrigSysHomeRoaming = CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(pstOrigSysInfo,
                                                                          pstOrigSysGeoListInfo,
                                                                          &enOrigSysRoamingInd);

    ulIsCurSysHomeRoaming = CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(pstCurSysInfo,
                                                                         pstCurSysGeoListInfo,
                                                                         &enCurSysRoamingInd);

    if ((VOS_TRUE == ulIsOrigSysHomeRoaming)
     && (VOS_TRUE == ulIsCurSysHomeRoaming))
    {
        return CNAS_PRL_SYS_PRI_SAME;
    }

    if (VOS_TRUE == ulIsOrigSysHomeRoaming)
    {
        return CNAS_PRL_SYS_PRI_LOW;
    }

    if (VOS_TRUE == ulIsCurSysHomeRoaming)
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    if (enCurSysRoamingInd == enOrigSysRoamingInd)
    {
        return CNAS_PRL_SYS_PRI_SAME;
    }

    if ((enCurSysRoamingInd < enOrigSysRoamingInd)
     && ((enCurSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_ON)
      || (enCurSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_FLASHING)))
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    if ((enOrigSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_ON)
     || (enOrigSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_FLASHING))
    {
        return CNAS_PRL_SYS_PRI_LOW;
    }

    return CNAS_PRL_SYS_PRI_UNKNOWN;
}


CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareChannelIndexOfTwoSystems(
    VOS_UINT16                          usCurSysAcqIndex,
    VOS_UINT8                           ucCurSysFreqIndex,
    VOS_UINT16                          usOrigSysAcqIndex,
    VOS_UINT8                           usOrigSysFreqIndex
)
{
    if (usCurSysAcqIndex == usOrigSysAcqIndex)
    {
        if (ucCurSysFreqIndex == usOrigSysFreqIndex)
        {
            return CNAS_PRL_SYS_PRI_SAME;
        }

        if (ucCurSysFreqIndex < usOrigSysFreqIndex)
        {
            return CNAS_PRL_SYS_PRI_HIGH;
        }

        return CNAS_PRL_SYS_PRI_LOW;
    }

    if (usCurSysAcqIndex < usOrigSysAcqIndex)
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    return CNAS_PRL_SYS_PRI_LOW;
}


CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareChannelPreferenceOfTwoSystems(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU            *pstOrigSysInfo
)
{
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqInfoAddr = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec   = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT8                           j;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;
    VOS_UINT16                          usCurSysAcqIndex;
    VOS_UINT16                          usOrigSysAcqIndex;
    VOS_UINT8                           ucCurSysFreqIndex;
    VOS_UINT8                           usOrigSysFreqIndex;
    VOS_UINT8                           ucOrigSysSearchEnd;
    VOS_UINT8                           ucCurSysSearchEnd;
    CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32   enSysPri;

    ucOrigSysSearchEnd = VOS_FALSE;
    ucCurSysSearchEnd  = VOS_FALSE;
    usCurSysAcqIndex   = 0;
    usOrigSysAcqIndex  = 0;
    ucCurSysFreqIndex  = 0;
    usOrigSysFreqIndex = 0;

    pstAcqInfoAddr = CNAS_PRL_GetPrlAcqInfoAddr();

    for (i = 0; i < pstAcqInfoAddr->usAcqRecordNum; i++)
    {
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(i);

        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

        for (j = 0; j < (VOS_UINT8)CNAS_MIN(stAcqRecFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); j++)
        {
            if ((ucCurSysSearchEnd                           == VOS_FALSE)
             && (stAcqRecFreqInfo.astFreqInfo[j].enBandClass == pstCurSysInfo->stFreq.enBandClass)
             && (stAcqRecFreqInfo.astFreqInfo[j].usChannel   == pstCurSysInfo->stFreq.usChannel))
            {
                usCurSysAcqIndex  = i;
                ucCurSysFreqIndex = j;
                ucCurSysSearchEnd = VOS_TRUE;
            }

            if ((ucOrigSysSearchEnd                          == VOS_FALSE)
             && (stAcqRecFreqInfo.astFreqInfo[j].enBandClass == pstOrigSysInfo->stFreq.enBandClass)
             && (stAcqRecFreqInfo.astFreqInfo[j].usChannel   == pstOrigSysInfo->stFreq.usChannel))
            {
                usOrigSysAcqIndex  = i;
                usOrigSysFreqIndex = j;
                ucOrigSysSearchEnd = VOS_TRUE;
            }
        }

        if ((VOS_TRUE == ucCurSysSearchEnd)
         && (VOS_TRUE == ucOrigSysSearchEnd))
        {
            break;
        }
    }

    if ((VOS_FALSE == ucCurSysSearchEnd)
     && (VOS_FALSE == ucOrigSysSearchEnd))
    {
        return CNAS_PRL_SYS_PRI_UNKNOWN;
    }

    if (VOS_TRUE == ucCurSysSearchEnd)
    {
        if (VOS_FALSE == ucOrigSysSearchEnd)
        {
            return CNAS_PRL_SYS_PRI_HIGH;
        }

        enSysPri = CNAS_PRL_CompareChannelIndexOfTwoSystems(usCurSysAcqIndex,
                                                            ucCurSysFreqIndex,
                                                            usOrigSysAcqIndex,
                                                            usOrigSysFreqIndex);
        return enSysPri;
    }

    return CNAS_PRL_SYS_PRI_LOW;
}


CNAS_PRL_MATCHED_GEO_INFO_STRU *CNAS_PRL_GetTheSameGeoInfoOfTwoGeoList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstCurSysGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstOrigSysGeoListInfo
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;

    for (i = 0; i < pstCurSysGeoListInfo->ucGeoNum; i++)
    {
        for (j = 0; j < pstOrigSysGeoListInfo->ucGeoNum; j++)
        {
            if (pstCurSysGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex ==
                pstOrigSysGeoListInfo->astGeoInfoList[j].usGeoFirstSysRecIndex)
            {
                return &(pstCurSysGeoListInfo->astGeoInfoList[i]);
            }
        }
    }

    return VOS_NULL_PTR;
}


CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareSystemPreference(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU            *pstOrigSysInfo
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stOrigSysGeoListInfo;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stCurSysGeoListInfo;
    CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32                       enSysPref;
    VOS_UINT32                                              ulCurMostPrefer;
    VOS_UINT32                                              ulOrigMostPrefer;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMatchedGeoInfo = VOS_NULL_PTR;

    enSysPref = CNAS_PRL_SYS_PRI_UNKNOWN;

    /* Get the GEO list informaion of the orignal system */
    NAS_MEM_SET_S(&stOrigSysGeoListInfo, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstOrigSysInfo, &stOrigSysGeoListInfo);

    /* Get the GEO list informaion of the synchronized system */
    NAS_MEM_SET_S(&stCurSysGeoListInfo, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stCurSysGeoListInfo);

    if ((0 != stOrigSysGeoListInfo.ucGeoNum)
     && (0 != stCurSysGeoListInfo.ucGeoNum))
    {
        pstMatchedGeoInfo = CNAS_PRL_GetTheSameGeoInfoOfTwoGeoList(&stCurSysGeoListInfo,
                                                                   &stOrigSysGeoListInfo);
        if (VOS_NULL_PTR != pstMatchedGeoInfo)
        {
            /* reference from chapter 2.11 in CDG 143:
            1. If there is a GEO in the PRL that lists both systems, select the one that is listed as
               the more preferred in this GEO.
             - If both systems are listed in more than one GEO, only look in the first GEO (from top
               to bottom of the PRL system table) that lists both systems to determine the priority.
             - If both systems are listed at the same preference, select/stay on the original system
               (to avoid ping-pong effect).
            */

            enSysPref = CNAS_PRL_CmpSysPriorityofTwoSystemsInSameGeo(pstCurSysInfo,
                                                                     pstOrigSysInfo,
                                                                     pstMatchedGeoInfo);

            return enSysPref;
        }

        /* reference from chapter 2.11 in CDG 143:
           3. If the roaming indicator of one system is more favorable than the other (as defined in
           Req. 2.6.2), select the more favorable one.
        */
        enSysPref = CNAS_PRL_CompareRoamingIndicatorPreferenceOfTwoSystems(pstCurSysInfo,
                                                                           pstOrigSysInfo,
                                                                           &stCurSysGeoListInfo,
                                                                           &stOrigSysGeoListInfo);
        if ((CNAS_PRL_SYS_PRI_HIGH == enSysPref)
         || (CNAS_PRL_SYS_PRI_LOW  == enSysPref))
        {
            return enSysPref;
        }

        /* reference from chapter 2.11 in CDG 143:
           4. If one system is listed as most preferred system in its GEO, select that system.
        */
        ulCurMostPrefer  = CNAS_PRL_IsMostPref1xSysInGeo(pstCurSysInfo, &stCurSysGeoListInfo);
        ulOrigMostPrefer = CNAS_PRL_IsMostPref1xSysInGeo(pstOrigSysInfo, &stOrigSysGeoListInfo);

        if ((VOS_TRUE  == ulCurMostPrefer)
         && (VOS_FALSE == ulOrigMostPrefer))
        {
            return CNAS_PRL_SYS_PRI_HIGH;
        }

        if ((VOS_FALSE  == ulCurMostPrefer)
         && (VOS_TRUE   == ulOrigMostPrefer))
        {
            return CNAS_PRL_SYS_PRI_LOW;
        }

        /* reference from chapter 2.11 in CDG 143:
            5. If the position of channels in the PRL acquisition table is different, select the system
               for which its channel is listed first. The position of the channel is determined by the
               first appearance of that channel in the acquisition table when traversed from top to bottom.
        */
        enSysPref = CNAS_PRL_CompareChannelPreferenceOfTwoSystems(pstCurSysInfo, pstOrigSysInfo);

        return enSysPref;
    }

    /* reference from chapter 2.11 in CDG 143:
       2. If only one system is listed in the PRL system table (as a preferred system), select
          the one that is listed in the PRL.
    */
    if (0 != stCurSysGeoListInfo.ucGeoNum)
    {
        /* current system is in PRL */
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    if (0 != stOrigSysGeoListInfo.ucGeoNum)
    {
        /* orignal system is in PRL */
        return CNAS_PRL_SYS_PRI_LOW;
    }

    /* could not determine the preference while both systems are not in PRL */
    return CNAS_PRL_SYS_PRI_UNKNOWN;
}



VOS_UINT16 CNAS_PRL_CalcMatchedGeoListTotalFreqNum(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord  = VOS_NULL_PTR;
    VOS_UINT16                          usSysRecordNum;
    VOS_UINT16                          i;
    VOS_UINT16                          usMaxGeoChanNum;
    VOS_UINT16                          usGeoSysRecordNum;

    usMaxGeoChanNum     = 0;
    usSysRecordNum      = 0;
    usGeoSysRecordNum   = 0;

    /* calculate the system record numbers */
    for (i = 0; i < (VOS_UINT8)CNAS_MIN(pstGeoListInfo->ucGeoNum, CNAS_PRL_MAX_MATCHING_GEO_NUM); i++)
    {
        usGeoSysRecordNum += pstGeoListInfo->astGeoInfoList[i].usGeoSysRecNum;
    }

    pstSysRecord = PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU) * usGeoSysRecordNum);

    /* alloc memory fail,return */
    if (VOS_NULL_PTR == pstSysRecord)
    {
        return usMaxGeoChanNum;
    }

    CNAS_PRL_BuildGeoSysRecList(pstSysInfo, pstGeoListInfo, VOS_TRUE, &usSysRecordNum, pstSysRecord);

    /* calculate max size of the channuel number */
    usMaxGeoChanNum                 = CNAS_PRL_CalcPrlSysRecListTotalFreqNum(usSysRecordNum, pstSysRecord);

    /* free the memory of pstSysRecord */
    PS_MEM_FREE(UEPS_PID_XSD, pstSysRecord);

    return usMaxGeoChanNum;
}



CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_GetBandChanMatchInfoOfGeoSys(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstGeoInfo
)
{
    VOS_UINT16                                              usFirstSysRecIndex;
    VOS_UINT16                                              usGeoSysRecNum;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMostMatch;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord          = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMostMatchSysRecord = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord          = VOS_NULL_PTR;
    VOS_UINT16                                              usIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enPrlSidNidMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enPrlSidNidMostMatchLvl;

    usFirstSysRecIndex      = pstGeoInfo->usGeoFirstSysRecIndex;
    usGeoSysRecNum          = pstGeoInfo->usGeoSysRecNum;
    enPrlSidNidMostMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enBandChannelMostMatch  = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;

    for (usIndex = usFirstSysRecIndex; usIndex < (usFirstSysRecIndex + usGeoSysRecNum); usIndex++)
    {
        /* 依次获取系统记录索引所对应的系统记录信息 */
        pstSysRecord  = CNAS_PRL_GetSpecifiedPrlSysRecord(usIndex);

        if (VOS_NULL_PTR !=  pstSysRecord)
        {
            /*  获取SID NID匹配等级　*/
            enPrlSidNidMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstSysRecord);

            /* 获取系统记录中获取记录索引所对应的获取记录信息*/
            pstAcqRecord = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);

            if (VOS_NULL_PTR != pstAcqRecord)
            {
                /*  获取band channel匹配等级　*/
                enBandChannelMatch  = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstAcqRecord);

                if (enPrlSidNidMatchLvl > enPrlSidNidMostMatchLvl)
                {
                    enPrlSidNidMostMatchLvl  = enPrlSidNidMatchLvl;
                    pstMostMatchSysRecord    = pstSysRecord;
                    enBandChannelMostMatch   = enBandChannelMatch;
                }
                else if (enPrlSidNidMatchLvl == enPrlSidNidMostMatchLvl)
                {
                    /*SID NID匹配优先级相同，继续比较band channel匹配优先级等级 */
                    if (enBandChannelMatch > enBandChannelMostMatch)
                    {
                        enBandChannelMostMatch = enBandChannelMatch;
                        pstMostMatchSysRecord  = pstSysRecord;
                    }
                }
                else
                {}
            }
        }
    }

    if (VOS_NULL_PTR != pstMostMatchSysRecord)
    {
         /* 获取系统记录中获取记录索引所对应的获取记录信息*/
        pstAcqRecord = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstMostMatchSysRecord->usAcqIndex);

        if (VOS_NULL_PTR != pstAcqRecord)
        {
            /* 获取BandChannel 匹配等级*/
            enBandChannelMostMatch = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstAcqRecord);

            return enBandChannelMostMatch;
        }

    }

    return CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
}


CNAS_PRL_MATCHED_GEO_INFO_STRU *CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    VOS_UINT8                                               i;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;

    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChanMostMatchLevel;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChanMatchLevel;

    /* 初始化首个GEO为最match GEO */
    pstMostMatchGeoInfo = &(pstGeoListInfo->astGeoInfoList[0]);

    for (i = 1; i < pstGeoListInfo->ucGeoNum; i++)
    {
        if (pstMostMatchGeoInfo->enMatchLvl < pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
        {
            pstMostMatchGeoInfo = &(pstGeoListInfo->astGeoInfoList[i]);
        }
        else if (pstMostMatchGeoInfo->enMatchLvl == pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
        {
            enBandChanMostMatchLevel = CNAS_PRL_GetBandChanMatchInfoOfGeoSys(pstSysInfo, pstMostMatchGeoInfo);
            enBandChanMatchLevel     = CNAS_PRL_GetBandChanMatchInfoOfGeoSys(pstSysInfo, &(pstGeoListInfo->astGeoInfoList[i]));

            if (enBandChanMostMatchLevel < enBandChanMatchLevel)
            {
                pstMostMatchGeoInfo = &(pstGeoListInfo->astGeoInfoList[i]);
            }

        }
        else
        {}
    }

    return pstMostMatchGeoInfo;
}


VOS_VOID CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMostMatchGeoListInfo
)
{
    VOS_UINT8                                               i;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;

    /* 从GEO list中找出最匹配的GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstSysInfo, pstGeoListInfo);

    /* 查找所有GEO中与最匹配的GEO等级相同的GEO, 并保存的最match GEO list中 */
    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        if (pstMostMatchGeoInfo->enMatchLvl == pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
        {
            NAS_MEM_CPY_S(&(pstMostMatchGeoListInfo->astGeoInfoList[pstMostMatchGeoListInfo->ucGeoNum]),
                          sizeof(CNAS_PRL_MATCHED_GEO_INFO_STRU),
                          &(pstGeoListInfo->astGeoInfoList[i]),
                          sizeof(CNAS_PRL_MATCHED_GEO_INFO_STRU));

            pstMostMatchGeoListInfo->ucGeoNum++;
        }
    }
}


CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord
)
{
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stFreqInfo;
    VOS_UINT8                                               i;

    CNAS_PRL_GetPrlAcqRecFreqListInfo(pstAcqRecord, &stFreqInfo);

    enBandChannelMatch = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;

    for (i = 0; i < CNAS_MIN(stFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++ )
    {
        if (pstFreq->enBandClass == stFreqInfo.astFreqInfo[i].enBandClass)
        {
            enBandChannelMatch = CNAS_PRL_BAND_MATCH;

            if (pstFreq->usChannel == stFreqInfo.astFreqInfo[i].usChannel)
            {
                enBandChannelMatch = CNAS_PRL_BAND_CHANNEL_MATCH;
                break;
            }
        }
    }

    return enBandChannelMatch;
}



VOS_UINT8 CNAS_PRL_IsCurrentSystemInHomeSidNidList(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
)
{
    VOS_UINT8                           i;
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList = VOS_NULL_PTR;

    pstHomeSidNidList = CNAS_CCB_GetHomeSidNidList();

    for (i = 0; i < CNAS_MIN(pstHomeSidNidList->ucSysNum, CNAS_CCB_MAX_HOME_SID_NID_LIST); i++)
    {
        /* 3gpp2 CS0005 2.6.5.3章节:
           The mobile station may use the special NID value 65535 to indicate that
           the mobile station considers all NIDs within a SID to be non-roaming */

        /* 由于协议仅说明NID可以是通配符，对于SID为通配符，我们这里跳过 */
        if ((CNAS_PRL_WILDCARD_SID != pstHomeSidNidList->astHomeSidNid[i].usSid)
         && (pstCurSysInfo->usSid  == pstHomeSidNidList->astHomeSidNid[i].usSid))
        {
            /* NID相等或是通配符 */
            if ((pstCurSysInfo->usNid  == pstHomeSidNidList->astHomeSidNid[i].usNid)
             || (CNAS_PRL_WILDCARD_NID == pstHomeSidNidList->astHomeSidNid[i].usNid))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}



CNAS_PRL_ACQ_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlValidAcqRecord(VOS_UINT16 usIndex)
{
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRecord;

    if ((usIndex < CNAS_PRL_GetPrlAcqRecordNum()) && (usIndex < CNAS_PRL_ACQ_RECORD_MAX_NUM))
    {
        pstPrlAcqRecord = (CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo.pastPrlAcqRecord[usIndex]);

        if (VOS_FALSE == pstPrlAcqRecord->ucAcqValid)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_PRL_GetSpecifiedPrlValidAcqRecord: AcqRecValid is False,index is", usIndex);
            return VOS_NULL_PTR;
        }

        return pstPrlAcqRecord;
    }

    return VOS_NULL_PTR;
}

CNAS_PRL_EXT_SYS_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlValidSysRecord(VOS_UINT16 usIndex)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord;

    /* 索引检查 */
    if ((usIndex < CNAS_PRL_GetPrlSysRecordNum()) && (usIndex < CNAS_PRL_SYS_RECORD_MAX_NUM))
    {
        /* 跳转到指定索引的系统记录地址 */
        pstSysRecord = (CNAS_PRL_EXT_SYS_RECORD_STRU *)(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo.pstSysRecord + usIndex);

        /* 判断记录属性 */
        if (VOS_FALSE == pstSysRecord->ucSysRecValid)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetNonHybridHrpdSysRecNum: SysRecValid is False,index is", usIndex);
            return VOS_NULL_PTR;
        }

        return pstSysRecord;
    }

    return VOS_NULL_PTR;
}


VOS_UINT32 CNAS_PRL_CmpFreqValue(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSrcFreq,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstFreq
)
{
    if ((VOS_NULL_PTR == pstSrcFreq) || (VOS_NULL_PTR == pstDstFreq))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_CmpFreqValue: para is NULL!");

        return VOS_FALSE;
    }

    if ((pstSrcFreq->enBandClass == pstDstFreq->enBandClass)
         && (pstSrcFreq->usChannel   == pstDstFreq->usChannel))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 CNAS_PRL_CmpSubnetValue(
    VOS_UINT8                          *pucSrcSubnet,
    VOS_UINT8                          *pucDstSubnet,
    VOS_UINT32                          ulCmpLen
)
{
    if ((VOS_NULL_PTR == pucSrcSubnet) || (VOS_NULL_PTR == pucDstSubnet))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_CmpSubnetValue: para is NULL!");

        return VOS_FALSE;
    }

    if (VOS_OK == PS_MEM_CMP(pucSrcSubnet, pucDstSubnet, ulCmpLen))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_IsHrpdSubnetMatched(
    VOS_UINT8                          *pucOTASubnetid,
    VOS_UINT8                           ucOTASubnetidBitSize,
    VOS_UINT8                          *pucSysRecSubnetid,
    VOS_UINT8                           ucSysRecSubnetidBitSize
)
{
    VOS_UINT8                           ucSrcSubnetid;
    VOS_UINT8                           ucDstSubnetid;
    VOS_UINT8                           ucSubnetTempLen;
    VOS_UINT8                           ucSubnetBitTempLen;   /* 存放Subne剩余bit长度 */

    if ((VOS_NULL_PTR == pucOTASubnetid) || (VOS_NULL_PTR == pucSysRecSubnetid))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_IsHrpdSubnetMatched: para is NULL!");
        return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    /* OTA码流小于PRL Subnet码流 */
    if (ucOTASubnetidBitSize < ucSysRecSubnetidBitSize)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_IsHrpdSubnetMatched: OTA TOO Small!");

        return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    /* 是否是通配 */
    if (0 == ucSysRecSubnetidBitSize)
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD;
    }

    ucSubnetTempLen = (ucSysRecSubnetidBitSize / CNAS_PRL_BIT_LEN_8_BIT);

    /* SYS RECORD subnet按照bit存贮，先比较整字节 */
    if (VOS_TRUE != CNAS_PRL_CmpSubnetValue(pucOTASubnetid, pucSysRecSubnetid, ucSubnetTempLen))
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    /* 再比较剩余bit */
    ucSubnetBitTempLen = (ucSysRecSubnetidBitSize % CNAS_PRL_BIT_LEN_8_BIT);
    if (0 < ucSubnetBitTempLen)
    {
        ucSrcSubnetid = CNAS_PRL_ExtractBitStringToOctet(&pucOTASubnetid[ucSubnetTempLen], 0, ucSubnetBitTempLen);
        ucDstSubnetid = CNAS_PRL_ExtractBitStringToOctet(&pucSysRecSubnetid[ucSubnetTempLen], 0, ucSubnetBitTempLen);
        if (ucSrcSubnetid != ucDstSubnetid)
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
        }
    }

    return CNAS_PRL_SUBNET_MATCH_LVL_SUBNET;
}


CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_IsHrpdFreqMatched(
    VOS_UINT16                          usAcqIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    CNAS_PRL_ACQ_RECORD_STRU                               *pstPrlAcqRecord;
    CNAS_PRL_GENERIC_ACQ_FOR_HRPD_STRU                     *pstHrpdSys;
    VOS_UINT32                                              i;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;

    pstPrlAcqRecord = CNAS_PRL_GetSpecifiedPrlValidAcqRecord(usAcqIndex);

    /* 参数检查 */
    if (VOS_NULL_PTR == pstPrlAcqRecord)
    {
        CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_PRL_IsHrpdFreqMatched: usAcqIndex out of range", usAcqIndex);
        return CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
    }

    /* 是否为HRPD ACQ */
    if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD != pstPrlAcqRecord->enAcqType)
    {
        return CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
    }

    enBandChannelMatch  = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
    pstHrpdSys          = &(pstPrlAcqRecord->u.stHrpdSys);

    for (i = 0; i < pstHrpdSys->ucNumOfChans; i++ )
    {
        if (pstFreq->enBandClass == pstHrpdSys->astFreq[i].enBandClass)
        {
            enBandChannelMatch = CNAS_PRL_BAND_MATCH;

            if (pstFreq->usChannel == pstHrpdSys->astFreq[i].usChannel)
            {
                enBandChannelMatch = CNAS_PRL_BAND_CHANNEL_MATCH;
                break;
            }
        }
    }

    return enBandChannelMatch;
}


CNAS_PRL_EXT_SYS_RECORD_STRU* CNAS_PRL_GetHrpdSysRecByIndex(VOS_UINT16 usIndex)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord;

    pstSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(usIndex);

    /* 参数检查 */
    if (VOS_NULL_PTR == pstSysRecord)
    {
        CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_PRL_GetHrpdSysRecByIndex: usIndex out of range", usIndex);
        return VOS_NULL_PTR;
    }

    /* 非HRPD */
    if (VOS_FALSE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_GetHrpdSysRecByIndex: is not Hrpd");
        return VOS_NULL_PTR;
    }

    return pstSysRecord;
}


CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16     enMatchLevel;

    /* 非HRPD */
    if (VOS_FALSE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    /* 判断Subnet匹配等级 */
    if ((CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
      && (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID == pstSysRecord->u.stMccMncId.enMccMncSubType))
    {
        enMatchLevel = CNAS_PRL_GetHrpdSysRecMatchLvl_MccMncBased(pstHrpdSystem, pstSysRecord);
    }
    else if (CNAS_PRL_SYS_RECORD_TYPE_HRPD == pstSysRecord->enRecordType)
    {
        enMatchLevel = CNAS_PRL_GetHrpdSysRecMatchLvl_IS856(pstHrpdSystem, pstSysRecord);
    }
    else
    {
        enMatchLevel = CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    return enMatchLevel;
}


VOS_VOID CNAS_PRL_RecordMostMatchLvlGeoIndex(
    CNAS_PRL_MATCHED_1X_GEO_INFO_EX_STRU                   *pst1xGeoInfoEx,
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                 *penMatchLvl,
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enGet1xSysMatchLvl,
    VOS_UINT16                                              usSysRecIndex
)
{
    if ((*penMatchLvl                             == enGet1xSysMatchLvl) &&
        (CNAS_HSD_MAX_MATCH_LVL_SYS_REC_INDEX_NUM > pst1xGeoInfoEx->us1xSysIndexNum))
    {
        /* 存放index */
        pst1xGeoInfoEx->aus1xSysIndex[pst1xGeoInfoEx->us1xSysIndexNum] = usSysRecIndex;
        pst1xGeoInfoEx->us1xSysIndexNum++;
    }

    /* 如果匹配程度有提高，则更新匹配程度 */
    if (*penMatchLvl < enGet1xSysMatchLvl)
    {
        *penMatchLvl  = enGet1xSysMatchLvl;

        /* 清空之前存放的index */
        pst1xGeoInfoEx->us1xSysIndexNum = 0;

        /* 存放当前index */
        pst1xGeoInfoEx->aus1xSysIndex[pst1xGeoInfoEx->us1xSysIndexNum] = usSysRecIndex;
        pst1xGeoInfoEx->us1xSysIndexNum++;
    }

    return;
}


VOS_VOID CNAS_PRL_Get1xSysGeoListEx(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_1X_GEO_LIST_INFO_EX_STRU              *pst1xGeoListEx
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstTmpSysRecord;
    CNAS_PRL_MATCHED_1X_GEO_INFO_EX_STRU                   *pstTmp1xGeoInfoEx;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enTmpMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    VOS_UINT16                                              usGeoFirstSysRecIndex;
    VOS_UINT32                                              ulIsMatched;
    VOS_UINT16                                              i;

    enMatchLvl                   = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    ulIsMatched                  = VOS_FALSE;
    usGeoFirstSysRecIndex        = 0;
    pstTmp1xGeoInfoEx            = VOS_NULL_PTR;

    /* 初始化输出参数 */
    pst1xGeoListEx->ucGeoNum    = 0;
    pst1xGeoListEx->usSid       = pstSysInfo->usSid;
    pst1xGeoListEx->usNid       = pstSysInfo->usNid;

    for (i = 0; i < CNAS_PRL_GetPrlSysRecordNum(); i++)
    {
        pstTmpSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(i);

        if (VOS_NULL_PTR == pstTmpSysRecord)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_PRL_Get1xSysGeoListEx: Get SysRecord is Null,i is", i);
            continue;
        }

        /* 每次进新的GEO，判断之前遍历的时候，是否存在matach的记录 */
        if (CNAS_PRL_GEO_REGION_IND_NEW == pstTmpSysRecord->enGeoInd)
        {
            if (VOS_TRUE == ulIsMatched)
            {
                pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].enMatchLvl            = enMatchLvl;
                pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].usGeoFirstSysRecIndex = usGeoFirstSysRecIndex;
                pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].usGeoSysRecNum        = i - usGeoFirstSysRecIndex;
                pst1xGeoListEx->ucGeoNum++;

                /* 判断GEO NUM是否合法 */
                if (CNAS_PRL_MAX_MATCHING_GEO_NUM <= pst1xGeoListEx->ucGeoNum)
                {
                    CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_PRL_Get1xSysGeoListEx: GeoNum is", pst1xGeoListEx->ucGeoNum);
                    return;
                }

                ulIsMatched = VOS_FALSE;
                enMatchLvl  = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
            }

            usGeoFirstSysRecIndex = i;
        }

        /* 是否属于1X */
        if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 != pstTmpSysRecord->enRecordType)
        {
            continue;
        }

        /* 是否是NEG */
        if (CNAS_PRL_PREF_NEG_SYS_NEG == pstTmpSysRecord->enPrefNegSys)
        {
            continue;
        }

        /* 判断传入的系统信息，是否和系统记录中的相匹配 */
        enTmpMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstTmpSysRecord);

        if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enTmpMatchLvl)
        {
            ulIsMatched = VOS_TRUE;

            pstTmp1xGeoInfoEx = &(pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum]);

            /* 记录最高MATCH LEVEL Index，最多存放四个 */
            CNAS_PRL_RecordMostMatchLvlGeoIndex(pstTmp1xGeoInfoEx, &enMatchLvl, enTmpMatchLvl, i);
        }
    }

    if (VOS_TRUE == ulIsMatched)
    {
        pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].enMatchLvl            = enMatchLvl;
        pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].usGeoFirstSysRecIndex = usGeoFirstSysRecIndex;
        pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].usGeoSysRecNum        = i - usGeoFirstSysRecIndex;

        pst1xGeoListEx->ucGeoNum++;
    }

    return;
}



VOS_UINT32 CNAS_PRL_IsSidNidMatch_MccMncBased(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SYS_TYPE_SID_NID_STRU                         *pstSidNid = VOS_NULL_PTR;
    CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU                      *pstMccMncId = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstSidNid   = &(pstSysRecord->u.stMccMncId.u.stSidNid);
    pstMccMncId = &(pstSysRecord->u.stMccMncId);

    if ( (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID != pstMccMncId->enMccMncSubType)
      && (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID != pstMccMncId->enMccMncSubType) )
    {
        return VOS_FALSE;
    }

    for (i = 0; i < CNAS_MIN((VOS_UINT32)pstSidNid->ucSidNidNum, CNAS_PRL_MCC_MNC_SID_MAX_NUM);i++)
    {
        /* 如果SID能找到，说明SID精确匹配，NID通配 */
        if ( ( (pstSysInfo->usSid == pstSidNid->asSid[i])
            || (CNAS_PRL_WILDCARD_SID == pstSidNid->asSid[i]) )
          && ( (pstSysInfo->usNid == pstSidNid->asNid[i])
            || (CNAS_PRL_WILDCARD_NID == pstSidNid->asNid[i]) ) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU const *CNAS_PRL_GetBand0PrefChanTab(VOS_VOID)
{
    return g_astCnasPrlBand0Tab;
}


VOS_UINT32 CNAS_PRL_GetBand0PrefChanTabSize(VOS_VOID)
{
    return (sizeof(g_astCnasPrlBand0Tab)/sizeof(CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU));
}


VOS_UINT32 CNAS_PRL_GetBand10PrefChanTabSize(VOS_VOID)
{
    return (sizeof(g_astCnasPrlBand10Tab)/sizeof(CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU));
}


CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU const *CNAS_PRL_GetBand10PrefChanTab(VOS_VOID)
{
    return g_astCnasPrlBand10Tab;
}


VOS_UINT8 CNAS_PRL_Is1xSysRecord(
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstSysRecord
)
{
    if ((VOS_NULL_PTR                     == pstSysRecord)
     || (VOS_FALSE                        == pstSysRecord->ucSysRecValid))
    {
        return VOS_FALSE;
    }

    if ( (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord->enRecordType)
      || ( (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
        && ( (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID == pstSysRecord->u.stMccMncId.enMccMncSubType)
          || (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID == pstSysRecord->u.stMccMncId.enMccMncSubType) ) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 CNAS_PRL_IsHrpdSysRec(
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    if ((CNAS_PRL_SYS_RECORD_TYPE_HRPD == pstSysRecord->enRecordType)
     || ((CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
      && (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID == pstSysRecord->u.stMccMncId.enMccMncSubType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl_IS856(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16                   enMatchLevel;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;

    enMatchLevel = CNAS_PRL_IsHrpdSubnetMatched(pstHrpdSystem->aucSubnet,
                                                pstHrpdSystem->ucSubnetMask,
                                                pstSysRecord->u.stIs856Id.aucSubnet,
                                                pstSysRecord->u.stIs856Id.ucSubnetBitLen);

    if (CNAS_PRL_SUBNET_MATCH_LVL_SUBNET == enMatchLevel)
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_SUBNET;
    }

    if (CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD == enMatchLevel)
    {
        /* 判断Freq 是否匹配 */
        enBandChannelMatch = CNAS_PRL_IsHrpdFreqMatched(pstSysRecord->usAcqIndex,
                                                        &(pstHrpdSystem->stFreq));
        if (CNAS_PRL_BAND_CHANNEL_MATCH == enBandChannelMatch)
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND_CHANNEL;
        }
        else if (CNAS_PRL_BAND_MATCH == enBandChannelMatch)
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND;
        }
        else
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD;
        }
    }

    return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
}


CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl_MccMncBased(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU                       *pstSubnetId;
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16                   enSubnetMatchLevel;
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16                   enMatchLevel;
    VOS_UINT16                                              i;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enMostFreqMatch;

    enMatchLevel            = CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    enMostFreqMatch         = CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;

    pstSubnetId             = pstSysRecord->u.stMccMncId.u.pstSubnetId;

    for (i = 0; i < CNAS_MIN((VOS_UINT32)pstSubnetId->ucSubnetNum, CNAS_PRL_MCC_MNC_SID_MAX_NUM); i++)
    {
        enSubnetMatchLevel = CNAS_PRL_IsHrpdSubnetMatched(pstHrpdSystem->aucSubnet,
                                                          pstHrpdSystem->ucSubnetMask,
                                                          pstSubnetId->aucSubnetID[i],
                                                          pstSubnetId->aucSubnetLen[i]);

        if (CNAS_PRL_SUBNET_MATCH_LVL_SUBNET == enSubnetMatchLevel)
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_SUBNET;
        }

        if (CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD == enSubnetMatchLevel)
        {
            enMatchLevel       =   CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD;

            enBandChannelMatch = CNAS_PRL_IsHrpdFreqMatched(pstSysRecord->usAcqIndex,
                                                        &(pstHrpdSystem->stFreq));

            if (enBandChannelMatch > enMostFreqMatch)
            {
                enMostFreqMatch = enBandChannelMatch;
            }
        }
    }

    if (CNAS_PRL_BAND_CHANNEL_MATCH == enMostFreqMatch)
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND_CHANNEL;
    }
    else if (CNAS_PRL_BAND_MATCH == enMostFreqMatch)
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND;
    }
    else
    {
        return enMatchLevel;
    }

}


CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16 CNAS_PRL_ConvertStandardMatchLvlToCustom(
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enStandardMatchLvl
)
{
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enCustomMatchLvl;

    enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_BUTT;

    switch ( enStandardMatchLvl )
    {
        case CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH :
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
            break;
        case CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID :
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_SID;
            break;
        case CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID :
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_NID;
            break;
        case CNAS_PRL_SID_NID_MATCH_LVL_SID_NID :
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_SID_NID;
            break;
        default:
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_BUTT;
            break;
    }

    return enCustomMatchLvl;
}


CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetCustomMatchLvl_OnlySidNidBandMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{

    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8                       enWildCardType;
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enMatchLvl;

    enWildCardType = CNAS_PRL_GetPrlSysRecordWildCardType(pstSysInfo, pstSysRecord);

    switch (enWildCardType)
    {
        case CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD:
            enMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_SID_NID;
            break;

        case CNAS_PRL_WILDCARD_TYPE_NID:
            enMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_NID;
            break;

        case CNAS_PRL_WILDCARD_TYPE_SID:
            enMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_SID_EXCEPT_CHANNEL;
            break;

        case CNAS_PRL_WILDCARD_TYPE_UNKNOWN:
        default:
            enMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
            break;
    }

    return enMatchLvl;
}



CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16 CNAS_PRL_Get1xSysMatchSysRecordCustomLvl(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord;
    VOS_UINT32                                              ulIsSidNidMatched;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enStandardMatchLvl;

    ulIsSidNidMatched      = VOS_FALSE;

     /* 系统记录无效，不处理 */
    if (VOS_FALSE == pstSysRecord->ucSysRecValid)
    {
        return CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
    }

    if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord->enRecordType)
    {
        ulIsSidNidMatched = CNAS_PRL_IsSidNidMatch_1XIS95(pstSysInfo, pstSysRecord);
    }
    else if (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
    {
        ulIsSidNidMatched = CNAS_PRL_IsSidNidMatch_MccMncBased(pstSysInfo, pstSysRecord);
    }
    else
    {
        return CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
    }

    /* 如果SID和NID都不匹配，此时当前系统肯定和系统记录不匹配 */
    if ( VOS_FALSE == ulIsSidNidMatched )
    {
        return CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
    }

    pstAcqRecord  = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);

    /* 空指针保护 */
    if (VOS_NULL_PTR == pstAcqRecord)
    {
        enStandardMatchLvl = CNAS_PRL_GetMatchLvl_OnlySidNidMatch(pstSysInfo, pstSysRecord);

        return CNAS_PRL_ConvertStandardMatchLvlToCustom(enStandardMatchLvl);
    }

    enBandChannelMatch = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstAcqRecord);

    /* 如果band都没有匹配，说明此时仅仅匹配了SID和NID */
    if ( CNAS_PRL_BAND_CHANNEL_NOT_MATCH == enBandChannelMatch )
    {
        enStandardMatchLvl = CNAS_PRL_GetMatchLvl_OnlySidNidMatch(pstSysInfo, pstSysRecord);

        return CNAS_PRL_ConvertStandardMatchLvlToCustom(enStandardMatchLvl);
    }

    /* 如果CHANNEL没有匹配，说明此时仅仅匹配了SID、NID和BAND */
    if ( CNAS_PRL_BAND_MATCH == enBandChannelMatch )
    {
        return CNAS_PRL_GetCustomMatchLvl_OnlySidNidBandMatch(pstSysInfo, pstSysRecord);
    }

    /* 到这里说明是SID、NID、BAND、CHANNEL都匹配，返回channel匹配情况下的匹配等级 */
    enStandardMatchLvl = CNAS_PRL_GetMatchLvl_SidNidBandChannelMatch(pstSysInfo, pstSysRecord);

    return CNAS_PRL_ConvertStandardMatchLvlToCustom(enStandardMatchLvl);
}


VOS_VOID CNAS_PRL_GetMostMultiMatched1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstMostMatchGeoListInfo
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstSysRecordAddr  = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord   = VOS_NULL_PTR;
    VOS_UINT16                                              i;
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU                    stGeoInfo;
    VOS_UINT8                                               ucGeoNum;
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enMatchLvl;
    VOS_UINT16                                              usGeoFirstSysRecIndex;
    VOS_UINT16                                              usMatchedIndexNum;


    NAS_MEM_SET_S(&stGeoInfo, sizeof(stGeoInfo), 0x00, sizeof(stGeoInfo));

    pstSysRecordAddr = CNAS_PRL_GetPrlSysInfoAddr();

    ucGeoNum = 0;

    /* 系统记录表第一条记录做特殊处理 */
    pstSysRecord      = pstSysRecordAddr->pstSysRecord;

    enMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordCustomLvl(pstCurSysInfo, pstSysRecord);

    NAS_MEM_SET_S(&stGeoInfo, sizeof(stGeoInfo), 0x00, sizeof(stGeoInfo));
    stGeoInfo.usGeoFirstSysRecIndex = 0;
    stGeoInfo.enGeoMostMatchLvl     = enMatchLvl;
    usGeoFirstSysRecIndex           = 0;

    if (CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH != enMatchLvl)
    {
        stGeoInfo.astIndexList[enMatchLvl].ausMostMatchedIndex[0] = 0;
        stGeoInfo.astIndexList[enMatchLvl].usMatchedIndexNum++;
    }

    for (i = 1; i < pstSysRecordAddr->usSysRecordNum; i++)
    {
        /* 得到第i条记录 */
        pstSysRecord      = pstSysRecordAddr->pstSysRecord + i;

        if (CNAS_PRL_GEO_REGION_IND_NEW == pstSysRecord->enGeoInd)
        {
            /* 填写GEO的系统记录个数 */
            stGeoInfo.usGeoSysRecNum        = i - usGeoFirstSysRecIndex;

            /* 将现有GEO加入到GEO列表 */
            if (CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH != stGeoInfo.enGeoMostMatchLvl)
            {
                CNAS_PRL_LogMultiMatchedGeoInfo(&stGeoInfo);

                ucGeoNum = pstMostMatchGeoListInfo->ucGeoNum;
                NAS_MEM_CPY_S(&(pstMostMatchGeoListInfo->astGeoInfoList[ucGeoNum]), sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU), &stGeoInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU));
                pstMostMatchGeoListInfo->ucGeoNum++;
            }

            /* 清空GEO */
            NAS_MEM_SET_S(&stGeoInfo, sizeof(stGeoInfo), 0x00, sizeof(stGeoInfo));
            usGeoFirstSysRecIndex           = i;
            stGeoInfo.usGeoFirstSysRecIndex = usGeoFirstSysRecIndex;
        }

        enMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordCustomLvl(pstCurSysInfo, pstSysRecord);

        if (stGeoInfo.enGeoMostMatchLvl < enMatchLvl)
        {
            stGeoInfo.enGeoMostMatchLvl = enMatchLvl;
        }

        if (CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH != enMatchLvl)
        {
            usMatchedIndexNum = stGeoInfo.astIndexList[enMatchLvl].usMatchedIndexNum;

            if (usMatchedIndexNum < CNAS_PRL_MAX_MATCHED_SYSTEM_NUM)
            {
                stGeoInfo.astIndexList[enMatchLvl].ausMostMatchedIndex[usMatchedIndexNum] = i;
                stGeoInfo.astIndexList[enMatchLvl].usMatchedIndexNum++;
            }
            else
            {
                NAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_GetMostMultiMatched1xGeoList MatchedIndexNum > CNAS_PRL_MAX_MATCHED_SYSTEM_NUM!");
            }
        }
    }

    /* 最后一个GEO的特殊处理 */
    stGeoInfo.usGeoSysRecNum = pstSysRecordAddr->usSysRecordNum - usGeoFirstSysRecIndex;

    if (CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH != stGeoInfo.enGeoMostMatchLvl)
    {
        CNAS_PRL_LogMultiMatchedGeoInfo(&stGeoInfo);

        ucGeoNum = pstMostMatchGeoListInfo->ucGeoNum;
        NAS_MEM_CPY_S(&(pstMostMatchGeoListInfo->astGeoInfoList[ucGeoNum]), sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU), &stGeoInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU));
        pstMostMatchGeoListInfo->ucGeoNum++;
    }

    pstMostMatchGeoListInfo->usSid = pstCurSysInfo->usSid;
    pstMostMatchGeoListInfo->usNid = pstCurSysInfo->usNid;

    CNAS_PRL_LogMultiMatchedGeoListInfo(pstMostMatchGeoListInfo);

    return;
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



