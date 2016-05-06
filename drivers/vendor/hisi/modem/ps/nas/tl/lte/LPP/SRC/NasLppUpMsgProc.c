/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppUpMtaMsgProc.c
  Description     :
  History         :
     1.LIFUXIN       2015-7-30   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "LppMtaInterface.h"
#include    "NasLppPublic.h"
#include    "NasLppUpPublic.h"
#include    "NasLppUpMsgProc.h"
#include    "NasLppEmmMsgProc.h"



#define    THIS_FILE_ID            PS_FILE_ID_NASLPPUPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPUPMSGPROC_C

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
Function Name  : NAS_LPP_StopReportTimer
Description    : 停止三种方式定时器
Input          : pstReportCriteria上报准则
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_StopReportTimer
(
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstReportCriteria,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
)
{
    if(NAS_LPP_REPORT_LOCATION_TYPE_ONCE == pstReportCriteria->enType)
      {
          /*启动response定时器*/
          NAS_LPP_UpTimerStop(enPosTechType,
                              TI_NAS_LPP_UP_RESPONSE_TIMER);
      }
      else if((NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER == pstReportCriteria->enType)
              &&(0 != pstReportCriteria->u.stReportTrigger.ulReportDuration))
      {
          /*如果是trigger方式的上报，而且不是无线次数上报，则启动trigger duration定时器*/
          NAS_LPP_UpTimerStop(enPosTechType,
                              TI_NAS_LPP_UP_REPORT_DURATION);
      }
      else
      {
          /*周期性上报的定时器等到收到LRRC的测量cnf之后再启动定时器*/
          NAS_LPP_UpTimerStop(enPosTechType,
                              TI_NAS_LPP_UP_PERIODICAL_REPORT);
      }
}
/*****************************************************************************
Function Name  : NAS_LPP_UpSetBandNum
Description    : 设置UE支持的band数据
Input          :
Output         :
Return Value   : VOS_VOID

History        :
1. wangensheng 00324863 2015-12-16 新开发
*****************************************************************************/
VOS_VOID NAS_LPP_UpSetBandNum
(
    LPP_MTA_OTDOA_PROVIDE_CAP_STRU     *pstOTDOAProvideCapabilities,
    VOS_UINT32                          ulBandNum,
    VOS_UINT32                          ulExtBandNum
)
{

    pstOTDOAProvideCapabilities->stSupportedBandListEutra.ulSupportBandNum = ulBandNum;
    if ( 0 != ulBandNum )
    {
        pstOTDOAProvideCapabilities->bitOpSupportedBandListEutra = NAS_LPP_SLCT;
    }
    else
    {
        pstOTDOAProvideCapabilities->bitOpSupportedBandListEutra = NAS_LPP_NO_SLCT;
    }

    pstOTDOAProvideCapabilities->stSupportedBandListEutraV9A0.ulSupportBandNum = ulExtBandNum;
    if ( 0 != ulExtBandNum )
    {
        pstOTDOAProvideCapabilities->bitOpSupportedBandListEutraV9A0  = NAS_LPP_SLCT;
    }
    else
    {
        pstOTDOAProvideCapabilities->bitOpSupportedBandListEutraV9A0  = NAS_LPP_NO_SLCT;
    }

}

/*****************************************************************************
Function Name  : NAS_LPP_FillinUpOtodaCapCnfData
Description    : LPP用户面填充OTDOA能力cnf的数据
Input          :
Output         : pstOTDOAProvideCapabilities,传出OTDO的能力数据
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
/*lint -e701*/
VOS_UINT32   NAS_LPP_FillinUpOtodaCapCnfData
(
    LPP_MTA_OTDOA_PROVIDE_CAP_STRU      *pstOTDOAProvideCapabilities,
    LRRC_SUPPORT_CAPABILITY_STRU        *pstLrrcCap
)
{
    VOS_UINT32                              ulLoop      = 0;
    VOS_UINT32                              ulBandNum   = 0;
    VOS_UINT32                              ulExtBandNum= 0;
    VOS_UINT32                              ulTmpIndex  = 0;
    VOS_UINT32                              ulTmpShit   = 0;
    VOS_UINT32                              ulTmp       = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_FillinUpOtodaCapCnfData");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_FillinUpOtodaCapCnfData_ENUM, LNAS_LPP_Func_Enter);

    if((VOS_TRUE == pstLrrcCap->bRrcCapbilityFlag)
      &&(LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucOtdoaUeAssistFlag))/*ucOtdoaUeAssistFlag是36.331里ue能力的支持*/
    {

        pstOTDOAProvideCapabilities->stOtdoaMode.ucOTDOAMode = NAS_LPP_OTDOA_UE_ASSIST;  /*第0 bit为1，表示支持OTDOA*/
        pstOTDOAProvideCapabilities->stOtdoaMode.ucOTDOAModeLen = 1;

        /*additionalNeighbourCellInfoList
        This field, if present, indicates that the target device supports up to 3×24 OTDOA-NeighbourCellInfoElement in OTDOA NeighbourCellInfoList
        in OTDOA-ProvideAssistanceData without any restriction for the earfcn in each OTDOA-NeighbourCellInfoElement as specified in subclause 6.5.1.2. */
        /*pstProvideCapR9Ies->stOTDOAProvideCapabilities.enAdditionalNeighbourCellInfoListR10 = ;为了处理3*24层的标准小区结构，这个IE可以设置成不存在*/
        pstOTDOAProvideCapabilities->bitOpOtdoaProvideCapExt = NAS_LPP_SLCT;
        if (LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucAddOtdoaNeighbourCellInfoListFlag)
        {
            pstOTDOAProvideCapabilities->bitOpAdditionalNeighbourCellInfoListR10 = NAS_LPP_SLCT;
            pstOTDOAProvideCapabilities->enAdditionalNeighbourCellInfoListR10 = LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_SUPPORT;
        }
        else
        {
            pstOTDOAProvideCapabilities->bitOpAdditionalNeighbourCellInfoListR10 = NAS_LPP_NO_SLCT;
        }

        for ( ulLoop = 0 ; ulLoop < LPP_MAX_SUPPORTED_BAND_EUTRA_NUM; ulLoop++ )
        {
            ulTmpIndex = ulLoop/32;
            ulTmpShit  = ulLoop%32;
            ulTmp = pstLrrcCap->stRrcCapbility.aulBandInd[ulTmpIndex];
            if ( 0 != (ulTmp & (0x01 << ulTmpShit) ) )
            {
                pstOTDOAProvideCapabilities->stSupportedBandListEutra.astSupportedBandArray[ulBandNum].ulBandEutra = ulLoop+1;
                ulBandNum++;
            }
        }

        for ( ulLoop = LPP_MAX_SUPPORTED_BAND_EUTRA_NUM ; ulLoop < LRRC_LPP_MAX_BAND_IND_NUM; ulLoop++ )
        {
            ulTmpIndex = ulLoop/32;
            ulTmpShit  = ulLoop%32;
            ulTmp = pstLrrcCap->stRrcCapbility.aulBandInd[ulTmpIndex];
            if ( 0 != (ulTmp & (0x01 << ulTmpShit) ) )
            {
                if ( ulExtBandNum >= LPP_MAX_SUPPORTED_BAND_EUTRA_NUM )
                {
                    NAS_LPP_ERR_LOG1("encode capability ,ext band overflow,ulLoop", ulLoop);
                    TLPS_PRINT2LAYER_INFO1(NAS_LPP_FillinUpOtodaCapCnfData_ENUM, LNAS_LPP_ExtBandOverflowLoop, ulLoop);
                    return NAS_LPP_FAILURE;
                }
                pstOTDOAProvideCapabilities->stSupportedBandListEutraV9A0.astSupportedBandArray[ulExtBandNum].bitOpBandEutraV9A0 = NAS_LPP_SLCT;
                pstOTDOAProvideCapabilities->stSupportedBandListEutraV9A0.astSupportedBandArray[ulExtBandNum].ulBandEutraV9A0 = ulLoop+1;
                ulExtBandNum++;
            }
        }

        NAS_LPP_UpSetBandNum(pstOTDOAProvideCapabilities, ulBandNum, ulExtBandNum);

        if ( LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucInterFreqRSTDMeasFlag )
        {
            pstOTDOAProvideCapabilities->bitOpInterFreqRSTDmeasurementR10 = NAS_LPP_SLCT;
            pstOTDOAProvideCapabilities->enInterFreqRSTDmeasurementR10 = LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_SUPPORT;
        }
        else
        {
            pstOTDOAProvideCapabilities->bitOpInterFreqRSTDmeasurementR10 = NAS_LPP_NO_SLCT;
        }
    }

    return NAS_LPP_SUCCESS;
}
/*lint +e701*/

/*****************************************************************************
Function Name  : NAS_LPP_SendLppMtaUpCapCnf
Description    : LPP模块用户面收能力请求的处理
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_SendLppMtaUpCapCnf(VOS_VOID)
{
    LPP_MTA_UP_CAPABILITY_CNF_STRU      *pstLppMtaCapCnf    = NAS_LPP_NULL_PTR;
    LRRC_SUPPORT_CAPABILITY_STRU        *pstLrrcSupportCap  = NAS_LPP_NULL_PTR;
    VOS_UINT32                           ulRslt             = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_SendLppMtaUpCapCnf enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SendLppMtaUpCapCnf_ENUM, LNAS_LPP_Func_Enter);

    /* malloc the msg memory */
    pstLppMtaCapCnf = (LPP_MTA_UP_CAPABILITY_CNF_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_UP_CAPABILITY_CNF_STRU));
    if (NAS_LPP_NULL_PTR == pstLppMtaCapCnf )
    {
        return;
    }
    NAS_LPP_MEM_SET_MSG(pstLppMtaCapCnf, sizeof(LPP_MTA_UP_CAPABILITY_CNF_STRU), 0, sizeof(LPP_MTA_UP_CAPABILITY_CNF_STRU));

    /* set the msg data */
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstLppMtaCapCnf, ID_LPP_MTA_UP_CAP_CNF);

    /*填充参数*/
    pstLppMtaCapCnf->bitOpEcidCap  = NAS_LPP_SLCT;
    pstLppMtaCapCnf->bitOpOtdoaCap = NAS_LPP_SLCT;

    /*3表示当前携带的ECID测量类型的种类*/
    pstLppMtaCapCnf->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSupCnt = 3;

    /*填充ECID支持的能力*/
    if(LPP_LRRC_INFO_FLAG_VALID == NAS_LPP_GetLrrcRxTxTimeDiffMeasFlag())
    {
        /*111代表RSRP, RSRQ， RXTXTimeDiff都支持*/
        pstLppMtaCapCnf->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSup = 0x07; /*111*/
    }
    else
    {
        /*110代表RSRP, RSRQ支持， 但是RXTXTimeDiff不支持*/
        pstLppMtaCapCnf->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSup = 0x06; /*110*/
    }

    pstLrrcSupportCap = NAS_LPP_GetLrrcCap();
    ulRslt = NAS_LPP_FillinUpOtodaCapCnfData(&(pstLppMtaCapCnf->stOTDOAProvideCapabilities),
                                               pstLrrcSupportCap);
    if(NAS_LPP_SUCCESS != ulRslt)
    {
        NAS_LPP_MEM_FREE(pstLppMtaCapCnf);
        return;
    }

    /* send msg data */
    NAS_LPP_SND_MSG(pstLppMtaCapCnf);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetLppUpRefEarfcnFromOtdoaAssis
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
1. wangensheng 00324863 2015-11-24 新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_UpGetRefEarfcnFromOtdoaAssis( LPP_OTDOA_REF_CELL_INFO_STRU  *pstOtdoaRefCellInfo )
{
    VOS_UINT32 ulEarfcn;

    /*36.355  earfcnRef         ARFCN-ValueEUTRA        OPTIONAL,       -- Cond NotSameAsServ0
      This field is absent if earfcnRef-v9a0 is present. Otherwise, the field is mandatory present if the EARFCN of
      the OTDOA assistance data reference cell is not the same as the EARFCN of the target devices's current primary cell.*/
    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarFcnRef)
    {
         ulEarfcn = pstOtdoaRefCellInfo->stEarfcnRef.ulArfcnValueEUTRA;
    }
    /*earfcnRef-v9a0        ARFCN-ValueEUTRA-v9a0   OPTIONAL    -- Cond NotSameAsServ2
      The field is absent if earfcnRef is present. Otherwise, the field is mandatory present if the EARFCN of the OTDOA
      assistance data reference cell is not the same as the EARFCN of the target devices's current primary cell.*/
    else if ( (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarfcnRefV9a0)
            &&(NAS_LPP_SLCT == pstOtdoaRefCellInfo->stEarfcnRefV9a0.bitOpARFCNValueEutraV9A0) )
    {
        ulEarfcn = pstOtdoaRefCellInfo->stEarfcnRefV9a0.ulArfcnValueEUTRAv9a0;
    }
    /* 如果bitOpEarFcnRef和bitOpEarfcnRefV9a0都不在,使用serving cell的*/
    else
    {
        ulEarfcn = NAS_LPP_GetServingCell()->ulEarfcn;
    }

    return ulEarfcn;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetNeibhorFreqEarFcn
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
1. wangensheng 00324863 2015-11-24 新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_UpGetNeibhorFreqEarFcn
(
    MTA_LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU *pstOtdoaRefCellInfo,
    VOS_UINT32                                      ulRefEarfcn
)
{
    VOS_UINT32 ulEarfcn;

    /*36.355  earfcnRef         ARFCN-ValueEUTRA        OPTIONAL,       -- Cond NotSameAsServ0
      This field is absent if earfcnRef-v9a0 is present. Otherwise, the field is mandatory present if the EARFCN of
      the OTDOA assistance data reference cell is not the same as the EARFCN of the target devices's current primary cell.*/
    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarfcn)
    {
         ulEarfcn = pstOtdoaRefCellInfo->stEarfcn.ulArfcnValueEUTRA;
    }
    /*earfcnRef-v9a0        ARFCN-ValueEUTRA-v9a0   OPTIONAL    -- Cond NotSameAsServ2
      The field is absent if earfcnRef is present. Otherwise, the field is mandatory present if the EARFCN of the OTDOA
      assistance data reference cell is not the same as the EARFCN of the target devices's current primary cell.*/
    else if ( (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarfcnV9a0)
            &&(NAS_LPP_SLCT == pstOtdoaRefCellInfo->stEarfcnv9a0.bitOpARFCNValueEutraV9A0) )
    {
        ulEarfcn = pstOtdoaRefCellInfo->stEarfcnv9a0.ulArfcnValueEUTRAv9a0;
    }
    /* 如果bitOpEarFcnRef和bitOpEarfcnRefV9a0都不在,使用serving cell的*/
    else
    {
        ulEarfcn = ulRefEarfcn;
    }

    return ulEarfcn;
}
/*****************************************************************************
 Function Name   : NAS_LPP_CheckLppUpOtdoaNeighbourCell
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. wangensheng 00324863 2015-11-24 新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_UpCheckOtdoaNeighbourCell
(
    LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU   *pstOtdoaNeighbourCellInfo,
    VOS_UINT32                           ulRefArfcn
)
{
    VOS_UINT32 ulLoop,ulLoop1,ulEarfcn; /* referrencr earfcn这里不需要知道明确的大小，只是作为一个比较的基准值而已*/

    if (pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt > LPP_MAX_FREQ_LAYERS_LEN)
    {
        NAS_LPP_ERR_LOG1("NAS_LPP_CheckLppUpOtdoaNeighbourCell:otdoa neighbor cell freq cnt overflow",
                         pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaNeighbourCell_ENUM,
                               LNAS_LPP_CheckOtdoaParameterOtdoaNeighborCellFreqCntOverflow);

        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    /* 前置条件:neighbour list不支持additional neighbor list */
    /*neighbour list每个频率层里的小区的频率要一致*/
    for ( ulLoop = 0 ; ulLoop < pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt; ulLoop++ )
    {
        if (pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt > LPP_MAX_OTDOA_NEIGHBOUR_CELL_INFO_ELMENT_LEN)
        {
            NAS_LPP_ERR_LOG2("NAS_LPP_CheckLppUpOtdoaNeighbourCell:otdoa neighbor cell cell cnt overflow",
                             ulLoop,
                             pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM,
                                    LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellCntOverflowLoop, ulLoop);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM,
                                    LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellCntOverflowLoopCnt,
                                    pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt);

            return NAS_LPP_MSG_VERIFY_FAIL;
        }

        /*每个频点的第一个小区频率*/
        if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcn)
        {
            ulEarfcn = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcn.ulArfcnValueEUTRA;
        }
        else if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcnV9a0)
        {
            ulEarfcn = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.ulArfcnValueEUTRAv9a0;
        }
        else
        {
            ulEarfcn = ulRefArfcn;
        }

        for ( ulLoop1 = 1 ;
              ulLoop1 < pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;
              ulLoop1++ )
        {
            /*后续每个小区的频率要保持一致:比较第n个和第(n-1)个*/
            if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].bitOpEarfcn)
            {
                if ( ulEarfcn != pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].stEarfcn.ulArfcnValueEUTRA )
                {
                    NAS_LPP_ERR_LOG2("NAS_LPP_CheckLppUpOtdoaNeighbourCell:otdoa neighbor cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnNotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnNotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
            }
            else if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].bitOpEarfcnV9a0)
            {
                if ( ulEarfcn != pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].stEarfcnv9a0.ulArfcnValueEUTRAv9a0 )
                {
                    NAS_LPP_ERR_LOG2(":otdoa neighbor v9a0 cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnVa90NotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnVa90NotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
            }
            else
            {
                /* 每个小区的频点都不用明确说明 */
                if ( ulEarfcn != ulRefArfcn )
                {
                    NAS_LPP_ERR_LOG2("NAS_LPP_CheckLppUpOtdoaNeighbourCell:otdoa neighbor ref cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellRefCellNotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellRefCellNotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
            }

        }
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}
/*****************************************************************************
Function Name  : NAS_LPP_CheckMtaLppUpAssistData
Description    : LPP模块用户面收能力请求的处理
Input          : 辅助数据的结构数据
Output         : NAS_LPP_MSG_VERIFY_SUCC
                 NAS_LPP_MSG_VERIFY_FAIL
Return Value   : VOS_VOID

History        :
1. wangensheng 00324863 2015-11-24 新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_UpCheckMtaAssistData
(
    MTA_LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU *pstOtdoaProvideAssistData
)
{
    NAS_LPP_UP_OTDOA_INFO_STRU              *pstLppUpOtdoaInfo   = NAS_LPP_NULL_PTR;
    NAS_LPP_SERVING_CELL_STRU               *pstLppServingCell   = NAS_LPP_NULL_PTR;
    MTA_LPP_OTDOA_NEIGHBOUR_FREQ_INFO_STRU  *pstNeighborFreqInfo = NAS_LPP_NULL_PTR;
    VOS_UINT32                               ulNghbrFreqInfoNum  = 0;
    VOS_UINT32                               ulRefNghbrCellNum   = 0;
    VOS_UINT32                               ulRefEarfcn         = 0;
    VOS_UINT32                               ulLoop              = 0;
    VOS_UINT32                               ulRslt              = 0;
    VOS_UINT32                               ulLoop1             = 0;

    TLPS_PRINT2LAYER_INFO(NAS_LPP_CheckMtaLppUpAssistData_ENUM, LNAS_LPP_Func_Enter);
    pstLppServingCell   = NAS_LPP_GetServingCell();
    pstLppUpOtdoaInfo   = NAS_LPP_GetLppUpOtdoaCtx();
    ulRefEarfcn         = NAS_LPP_UpGetRefEarfcnFromOtdoaAssis(&pstOtdoaProvideAssistData->stOtdoaRefCellInfo);

    /* ASSIST DATA 合法性检查 */
    if ( (NAS_LPP_SLCT == pstOtdoaProvideAssistData->bitOpOtdoaError )
       ||(NAS_LPP_NO_SLCT == pstOtdoaProvideAssistData->bitOpOtdoaReferenceCellInfo )
       ||(NAS_LPP_NO_SLCT == pstOtdoaProvideAssistData->bitOpOtdoaNeighbourCellInfo))
    {
        pstLppUpOtdoaInfo->stOtdoaAssisCfg.ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        pstLppUpOtdoaInfo->stOtdoaAssisCfg.ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckMtaLppUpAssistData_ENUM, LNAS_LPP_ASSIST_DATA_ERROR);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    /* 参考小区存在，小区计数加一 */
    ulRefNghbrCellNum += 1;

    /* 检查临区数据 */
    ulRslt = NAS_LPP_UpCheckOtdoaNeighbourCell(&pstOtdoaProvideAssistData->stOtdoaNeighbourCellInfo,
                                              ulRefEarfcn);
    if (NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_UPCheckMtaAssistData fail");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckMtaLppUpAssistData_ENUM, LNAS_LPP_CheckOtdoaNeighbourCellFail);
        return ulRslt;
    }

    /* 统计辅助数据中共有多少个小区 */
    ulNghbrFreqInfoNum = pstOtdoaProvideAssistData->stOtdoaNeighbourCellInfo.ulOtdoaNeighbourCellInfoListCnt;
    for ( ulLoop = 0 ; ulLoop < ulNghbrFreqInfoNum; ulLoop++ )
    {
        pstNeighborFreqInfo = &(pstOtdoaProvideAssistData->stOtdoaNeighbourCellInfo.astOtdoaNeighourFreqInfoArray[ulLoop]);
        ulRefNghbrCellNum += pstNeighborFreqInfo->ulOtdoaNeighbourFreqInfoCnt;
    }
    if ( ulRefNghbrCellNum < NAS_LPP_OTDOA_CELL_MIN_NUM )
    {
        NAS_LPP_ERR_LOG("NAS_LPP_UPCheckMtaAssistData: cell num not enough! ");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckMtaLppUpAssistData_ENUM, NAS_LPP_CheckMtaLppUpAssistDataCellNotEnough);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    /* 参考小区与服务小区一致 */
    if ( (pstLppServingCell->usPhyCellId == pstOtdoaProvideAssistData->stOtdoaRefCellInfo.usPhyCellId)
       &&(pstLppServingCell->ulEarfcn == ulRefEarfcn))
    {
        NAS_LPP_ERR_LOG("NAS_LPP_UPCheckMtaAssistData: Servie Cell in Reference Cell");
        return NAS_LPP_MSG_VERIFY_SUCC;
    }

    /* 邻区与服务小区一致 */
    ulNghbrFreqInfoNum = pstOtdoaProvideAssistData->stOtdoaNeighbourCellInfo.ulOtdoaNeighbourCellInfoListCnt;
    for ( ulLoop = 0 ; ulLoop < ulNghbrFreqInfoNum; ulLoop++ )
    {
        pstNeighborFreqInfo = &(pstOtdoaProvideAssistData->stOtdoaNeighbourCellInfo.astOtdoaNeighourFreqInfoArray[ulLoop]);
        ulRefNghbrCellNum += pstNeighborFreqInfo->ulOtdoaNeighbourFreqInfoCnt;
        for ( ulLoop1 = 0 ; ulLoop1 < pstNeighborFreqInfo->ulOtdoaNeighbourFreqInfoCnt; ulLoop1++ )
        {
            if ( (pstLppServingCell->usPhyCellId == pstNeighborFreqInfo->astOtdoaNeighbourFreqInfoArray[ulLoop1].ulPhysCellId)
               &&(pstLppServingCell->ulEarfcn ==
                  NAS_LPP_UpGetNeibhorFreqEarFcn(&(pstNeighborFreqInfo->astOtdoaNeighbourFreqInfoArray[ulLoop1]),ulRefEarfcn)))
            {
                break;
            }
        }

        /* 如果这个频点中找到*/
        if (ulLoop1 < pstNeighborFreqInfo->ulOtdoaNeighbourFreqInfoCnt)
        {
            break;
        }
    }

    /* 都不一致的情况 */
    if (ulLoop >= ulNghbrFreqInfoNum)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_UPCheckMtaAssistData: Servie Cell NOT in neighbour Cell1");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckMtaLppUpAssistData_ENUM, LNAS_LPP_ServiceCellNotInNeighbourCell);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }


    return NAS_LPP_MSG_VERIFY_SUCC;
}
/*****************************************************************************
Function Name   : NAS_LPP_SaveLppUpOtdoaRefCell
Description     : 存储otdoa的ref cell
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1. wangensheng 00324863 2015-11-24 新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_UpSaveOtdoaRefCell
(
    LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU          *pstOtdoaAssist,
    NAS_LPP_OTDOA_ASSIST_CFG_STRU               *pstOtdoaAssisCfg
)
{
    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU     *pstOtdoaRefCellCfg;
    LPP_OTDOA_REF_CELL_INFO_STRU                *pstOtdoaRefCellInfo;

    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8 aucAntennaPortConfig[LPP_LRRC_OTDOA_ANT_PORT_BUTT] =
                                    {LPP_LRRC_OTDOA_ANT_PORT_1_OR_2, LPP_LRRC_OTDOA_ANT_PORT_4};

    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8 aucPrsMutType[LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO2,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO4,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO8,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO16};

    LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8 aucNumFrams[LPP_LRRC_OTDOA_NUMDL_FRAMES_BUTT] =
                                    {LPP_LRRC_OTDOA_NUMDL_FRAMES_1,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_2,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_4,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_6};

    LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8 aucBandWidth[LPP_LRRC_OTDOA_PRS_BANDWIDTH_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_BANDWIDTH_N6,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N15,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N25,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N50,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N75,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N100};

    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8 aucCpType[LPP_LRRC_OTDOA_CP_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_CP_TYPE_NORMAL,
                                     LPP_LRRC_OTDOA_CP_TYPE_EXTENDED};

    NAS_LPP_NORM_LOG("NAS_LPP_SaveOtdoaRefCell enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveOtdoaRefCell_ENUM, LNAS_LPP_Func_Enter);

    if (NAS_LPP_NO_SLCT == pstOtdoaAssist->bitOpOtdoaReferenceCellInfo)
    {
        pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        return;
    }

    pstOtdoaRefCellCfg  = &(pstOtdoaAssisCfg->stOtdoaReferenceCellInfo);
    pstOtdoaRefCellInfo = &(pstOtdoaAssist->stOtdoaRefCellInfo);

    pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

    pstOtdoaRefCellCfg->usPhyCellId = pstOtdoaRefCellInfo->usPhyCellId;
    pstOtdoaRefCellCfg->ucCpLen     = aucCpType[pstOtdoaRefCellInfo->enCpLength];

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpCellGlobalId)
    {
        pstOtdoaRefCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_VALID;
        pstOtdoaRefCellCfg->stCellGlobalIdInfo.ulCellIdentity = pstOtdoaRefCellInfo->stCellGlobalId.ulCellIdentity;

        /*两个之间的转换*/
        NAS_LPP_LppPlmn2NasPlmn( &pstOtdoaRefCellInfo->stCellGlobalId.stPlmnIdentity, pstOtdoaRefCellCfg->stCellGlobalIdInfo.aucPlmnId);
    }
    else
    {
        pstOtdoaRefCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }

    pstOtdoaRefCellCfg->ulEarfcn = NAS_LPP_UpGetRefEarfcnFromOtdoaAssis(&(pstOtdoaAssist->stOtdoaRefCellInfo));

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpAntennaPortConfig)
    {
        pstOtdoaRefCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_VALID;
        pstOtdoaRefCellCfg->ucAntennaPortConfig = aucAntennaPortConfig[pstOtdoaRefCellInfo->enAntennaPortConfig];
    }
    else
    {
        pstOtdoaRefCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpPrsInfo)
    {
        pstOtdoaRefCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

        if ( (NAS_LPP_SLCT == pstOtdoaRefCellInfo->stPrsInfo.bitOpPrsMutingInfoR9 )
           &&(NAS_LPP_SLCT == pstOtdoaRefCellInfo->stPrsInfo.bitOpPrsInfoExt) )
        {
            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoType
                = aucPrsMutType[pstOtdoaRefCellInfo->stPrsInfo.stPrsMutingInfoR9.ulChoice];

            /*prs-MutingInfo-r9       CHOICE {
                    po2-r9                  BIT STRING (SIZE(2)),
                    po4-r9                  BIT STRING (SIZE(4)),
                    po8-r9                  BIT STRING (SIZE(8)),
                    po16-r9                 BIT STRING (SIZE(16)),
                    ...
                } 最长16bit，2个字节*/

           /*usPo2R9,usPo4R9,usPo8R9,usPo16R9都是16bit*/
           pstOtdoaRefCellCfg->stPrsInfo.usPrsMutingInfo = pstOtdoaRefCellInfo->stPrsInfo.stPrsMutingInfoR9.u.usPo2R9;
        }
        else
        {
            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        }

        pstOtdoaRefCellCfg->stPrsInfo.ucPrsBandWidth = aucBandWidth[pstOtdoaRefCellInfo->stPrsInfo.enPrsBandWith];
        pstOtdoaRefCellCfg->stPrsInfo.ucNumdlFrames  = aucNumFrams[pstOtdoaRefCellInfo->stPrsInfo.enNumDlFrames];
        pstOtdoaRefCellCfg->stPrsInfo.usPrsConfigurationIndex = (VOS_UINT16)pstOtdoaRefCellInfo->stPrsInfo.ulPrsConfigIndex;
    }
    else
    {
        pstOtdoaRefCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }
}
/*****************************************************************************
Function Name   :NAS_LPP_SaveLppUpOtdoaNghbrCell
Description     : 存储otodoa的辅助数据的临区信息
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1. wangensheng 00324863 2015-11-24 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_UpSaveOtdoaNghbrCell
(
LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU      *pstOtdoaAssist,
NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg
)
{
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg;
    LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU           *pstOtdoaNeighbourCellInfo;
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement;
    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU     *pstOtdoaRefCellCfg;
    VOS_UINT32 ulLoop,i,ulFreqNum,ulCellNum;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveLppUpOtdoaNghbrCell enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveLppUpOtdoaNghbrCell_ENUM, LNAS_LPP_Func_Enter);

    if (NAS_LPP_NO_SLCT == pstOtdoaAssist->bitOpOtdoaNeighbourCellInfo)
    {
        pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        return;
    }

    pstOtdoaRefCellCfg = &(pstOtdoaAssisCfg->stOtdoaReferenceCellInfo);

    pstOtdoaNeighbourCellInfo = &(pstOtdoaAssist->stOtdoaNeighbourCellInfo);

    pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

    pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.ulFreqInfoNum = pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt;
    ulFreqNum = pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt;
    for ( ulLoop = 0 ; ulLoop < ulFreqNum; ulLoop++ )
    {
        /*取每个频点第一个作为freq layer的freq*/
        if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcn)
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn
                = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcn.ulArfcnValueEUTRA;
        }
        else if ( (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcnV9a0)
                &&(NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.bitOpARFCNValueEutraV9A0) )
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn
                = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.ulArfcnValueEUTRAv9a0;
        }
        else
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn = pstOtdoaRefCellCfg->ulEarfcn;
        }

        pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulCellNum
            = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;

        ulCellNum = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;

        for ( i = 0 ; i < ulCellNum; i++ )
        {
            pstOtdoaNghbrCellCfg = &pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].stOtdoaNeighbourCellInfoList[i];
            pstNgnbrCellElement  = &pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[i];

            NAS_LPP_SaveCellGlobalId(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            NAS_LPP_SaveCpLength(pstOtdoaNghbrCellCfg,pstNgnbrCellElement,pstOtdoaRefCellCfg);

            NAS_LPP_SavePrs(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            NAS_LPP_SaveAntennaPort(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            NAS_LPP_SaveSlotNumOffset(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            NAS_LPP_SavePrsSubFrameOffset(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            pstOtdoaNghbrCellCfg->usPhyCellId    = (VOS_UINT16)pstNgnbrCellElement->ulPhysCellId;
            pstOtdoaNghbrCellCfg->usExpectedRSTD = pstNgnbrCellElement->usExpectedRSTD;
            pstOtdoaNghbrCellCfg->usExpectedRSTDUncertainty = pstNgnbrCellElement->usExpectedRSTDUncertainty;
        }
    }

}
/*****************************************************************************
Function Name   : NAS_LPP_SaveLppUpOtdoaAssistData
Description     : 存储otdoa的辅助数据
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1. wangensheng 00324863 2015-11-24 新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_UpSaveOtdoaAssistData
(
    LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU *pstOtdoaAssist
)
{
    NAS_LPP_UP_OTDOA_INFO_STRU         *pstLppUpOtdoaInfo;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveLppUpOtdoaAssistData enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveLppUpOtdoaAssistData_ENUM, LNAS_LPP_Func_Enter);

    pstLppUpOtdoaInfo = NAS_LPP_GetLppUpOtdoaCtx();

    NAS_LPP_UpSaveOtdoaRefCell(pstOtdoaAssist, &pstLppUpOtdoaInfo->stOtdoaAssisCfg);

    NAS_LPP_UpSaveOtdoaNghbrCell(pstOtdoaAssist, &pstLppUpOtdoaInfo->stOtdoaAssisCfg);
    pstLppUpOtdoaInfo->stOtdoaAssisCfg.bOtdoaAssistDataFlag = PS_TRUE;
    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_PrePareEcidParameter
 Description    : 准备ECID编码的参数
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_UpPrePareEcidParameterElement
(
    LPP_MEAS_RESULT_ELEMENT_STRU            *pstMeasRsltEle,
    LRRC_LPP_ECID_MEAS_RESULT_STRU          *pstLrrcLppMeasRslt,
    VOS_UINT8                                ucEcidReqMeasType
)
{
    /*phyCellId*/
    pstMeasRsltEle->ulPhyCellId = pstLrrcLppMeasRslt->usPhyCellId;

    /*Arfcn*/
    /*This field specifies the ARFCN of the measured E-UTRA carrier frequency,
    as defined in [12]. In case the target device includes arfcnEUTRA-v9a0,
    the target device shall set the corresponding arfcnEUTRA (i.e. without suffix)
    to maxEARFCN.*/
    if(pstLrrcLppMeasRslt->ulArfcn <= LPP_MAX_EARFCN)
    {
        /*频率值小于等于65535*/
        pstMeasRsltEle->stArfcnEutra.ulArfcnValueEUTRA = pstLrrcLppMeasRslt->ulArfcn;
    }
    else
    {
        /*频率值大于65535小于等于262143*/
        pstMeasRsltEle->bitOpMeasResultElementExt = NAS_LPP_SLCT;
        pstMeasRsltEle->stArfcnEutra.ulArfcnValueEUTRA = LPP_MAX_EARFCN;
        pstMeasRsltEle->bitOpArfcnEutraV9a0 = NAS_LPP_SLCT;
        pstMeasRsltEle->stArfcnEutraV9a0.ulArfcnValueEUTRAv9a0 = pstLrrcLppMeasRslt->ulArfcn;
    }

    /*RxTxTimeDiff&SFN*/
    if((NAS_LPP_SLCT == pstLrrcLppMeasRslt->ucUeRxTxTimeDiffMeasFlag)
       && (0 != (ucEcidReqMeasType & 0x01)))
    {
        pstMeasRsltEle->bitOpUeRxTxTimeDiff = NAS_LPP_SLCT;
        pstMeasRsltEle->ulUeRxTxTimeDiff = pstLrrcLppMeasRslt->usUeRxTxTimeDiff;

        pstMeasRsltEle->bitOpSystemFrameNumber = NAS_LPP_SLCT;
        pstMeasRsltEle->usSystemFrameNumber = pstLrrcLppMeasRslt->usSfn;
    }

    /*cellGlobalId*/
    if(NAS_LPP_SLCT == pstLrrcLppMeasRslt->ucCellGlobalIdFlag)
    {
        NAS_LPP_PrePareGloIdPara(pstMeasRsltEle, pstLrrcLppMeasRslt);
    }

    /*RSRP*/
    if(0 != (ucEcidReqMeasType & 0x04))
    {
        pstMeasRsltEle->bitOpRsrpResult = NAS_LPP_SLCT;
        pstMeasRsltEle->ucRsrpResult = pstLrrcLppMeasRslt->ucRsrp;
    }

    /*RSRQ*/
    if(0 != (ucEcidReqMeasType & 0x02))
    {
        pstMeasRsltEle->bitOpRsrqResult = NAS_LPP_SLCT;
        pstMeasRsltEle->ucRsrqResult = pstLrrcLppMeasRslt->ucRsrq;
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_UpPrePareEcidParameter
 Description    : 准备ECID编码的参数
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_UpPrePareEcidParameter
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo
)
{
    VOS_UINT32                          ulLoop = 0;
    LPP_MEAS_RESULT_ELEMENT_STRU       *pstNeighberMeasRsltEle= NAS_LPP_NULL_PTR;
    LRRC_LPP_ECID_MEAS_RESULT_STRU     *pstLrrcLppMeasRslt  = NAS_LPP_NULL_PTR;
    LPP_MEAS_RESULT_ELEMENT_STRU       *pstPrimaryMeasRslt  = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulCellNum           = 0;
    NAS_LPP_ECID_MEAS_RESULT_STRU      *pstEcidMeasRslt     = NAS_LPP_NULL_PTR;
    VOS_UINT8                           ucEcidMeasType      = 0;

    /*得到存储的位置请求相关信息*/
    pstEcidMeasRslt = NAS_LPP_GetEcidLrrcMeasAddr();
    ucEcidMeasType  = NAS_LPP_GetEcidReqMeasType();

    ulCellNum = pstEcidMeasRslt->stLrrcLppEcidMeasResultList.ulCellNum;
    if(1 == ulCellNum)
    {
        /*当前只有主小区一个上报测量信息*/
        /*
        根据协议要求，如果当前主小区和邻区都有测量信息，则各自存储即可，如果当前只有
        主小区的测量信息，则将主小区的测量信息存在邻区中
        */
        /*This field contains measurements for the primary cell, when the target device reports
        measurements for both primary cell and neighbour cells. This field shall be omitted when
        the target device reports measurements for the primary cell only, in which case the
        measurements the primary cell is reported in the measuredResultsList.*/
        pstNeighberMeasRsltEle  = NAS_LPP_UpGetNeighberMeasRsltElement(pstEcidSignalMeasInfo, 0);
        /*得到LRRC得测量实体的指针*/
        pstLrrcLppMeasRslt  = NAS_LPP_GetLrrcEcidMeasRslt(pstEcidMeasRslt, 0);

        pstEcidSignalMeasInfo->stMeasResultList.ulMeasResultsListCnt = 1;
        NAS_LPP_UpPrePareEcidParameterElement(pstNeighberMeasRsltEle,
                                              pstLrrcLppMeasRslt,
                                              ucEcidMeasType);
    }
    else
    {
        /*LRRC上报的测量技术大于等于1， 主的服务小区存在主的信元，邻区信息存在辅小区列表*/
        pstEcidSignalMeasInfo->bitOpPrimaryCellMeasRslt = NAS_LPP_SLCT;
        pstPrimaryMeasRslt = NAS_LPP_UpGetPrimaryMeasRsltElement(pstEcidSignalMeasInfo);
        pstLrrcLppMeasRslt = NAS_LPP_GetLrrcEcidMeasRslt(pstEcidMeasRslt, 0);

        /*拷贝主小区信息*/
        NAS_LPP_UpPrePareEcidParameterElement(pstPrimaryMeasRslt,
                                              pstLrrcLppMeasRslt,
                                              ucEcidMeasType);

        /*存邻区信息*/
        pstEcidSignalMeasInfo->stMeasResultList.ulMeasResultsListCnt = ulCellNum - 1;

        for(ulLoop = 1; ulLoop < ulCellNum ; ulLoop++)
        {
            pstNeighberMeasRsltEle = NAS_LPP_UpGetNeighberMeasRsltElement(pstEcidSignalMeasInfo, ulLoop - 1);
            /*得到LRRC得测量实体的指针,从数组的第二个元素开始取*/
            pstLrrcLppMeasRslt  = NAS_LPP_GetLrrcEcidMeasRslt(pstEcidMeasRslt, ulLoop);
            /*拷贝邻区信息*/
            NAS_LPP_UpPrePareEcidParameterElement(pstNeighberMeasRsltEle,
                                                  pstLrrcLppMeasRslt,
                                                  ucEcidMeasType);
        }

    }

    return;
}


/*****************************************************************************
Function Name  : NAS_LPP_SndUpLppMtaMeasInd
Description    : 给MTA发送测量结果-带有效的测量信息的场景
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_SndUpLppMtaMeasInd
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enReqTechType

)
{
    if( NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enReqTechType)
    {
        NAS_LPP_SndUpLppMtaEcidMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_BUTT);
    }
    else if( NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == enReqTechType)
    {
        NAS_LPP_SndUpLppMtaOtdoaMeasmentInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_BUTT);
    }
    else if( NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == enReqTechType)
    {
        NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_BUTT,
                                                   LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_BUTT);
    }
    else
    {

    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_SndUpLppMtaEcidMeasAndOtdoaErrInd
Description    : 给MTA发送测量结果-测量结果中ECID有测量信息，OTDOA测量error
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_SndUpLppMtaEcidMeasAndOtodaErrInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32            enEcidErrCause
)
{
    NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd(enEcidErrCause, LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_BUTT);

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_SndUpLppMtaOtodaMeasAndEcidErrInd
Description    : 给MTA发送测量结果-测量结果中OTDOA有测量信息，ECID测量error
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_SndUpLppMtaOtodaMeasAndEcidErrInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32            enEcidErrCause
)
{
    NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd(enEcidErrCause, LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_BUTT);

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_SndUpLppMtaEcidMeasmentInd
Description    : 给MTA发送ECID测量结果
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_SndUpLppMtaEcidMeasmentInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32 enEcidErrCause
)
{
    LPP_MTA_UP_MEAS_IND_STRU        *pstLppMtaMeasInd    = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SndUpLppMtaEcidMeasmentInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUpLppMtaEcidMeasmentInd_ENUM, LNAS_LPP_Func_Enter);

    /* malloc the msg memory */
    pstLppMtaMeasInd = (LPP_MTA_UP_MEAS_IND_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_UP_MEAS_IND_STRU));
    if (NAS_LPP_NULL_PTR == pstLppMtaMeasInd )
    {
        return;
    }
    NAS_LPP_MEM_SET_MSG(pstLppMtaMeasInd, sizeof(LPP_MTA_UP_MEAS_IND_STRU), 0, sizeof(LPP_MTA_UP_MEAS_IND_STRU));

    /* set the msg data */
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstLppMtaMeasInd, ID_LPP_MTA_UP_MEAS_IND);

    /*填充参数*/
    if(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_BUTT != enEcidErrCause)
    {
        pstLppMtaMeasInd->bitOpEcidProvideLocationInfo = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stEcidPRovideLocationInfo.bitOpEcidError = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stEcidPRovideLocationInfo.stEcidError.ulChoice =
                        LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_CHOSEN;
        pstLppMtaMeasInd->stEcidPRovideLocationInfo.stEcidError.u.stTargetDeviceErrorCauses.enEcidTargetDeviceErrorCause =
                        enEcidErrCause;
    }

    if((NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == NAS_LPP_GetEcidPosReqTechType())
       && (PS_TRUE == NAS_LPP_GetEcidLrrcMeasFlag()))
    {
        /*ECID测量信息*/
        pstLppMtaMeasInd->bitOpEcidProvideLocationInfo = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stEcidPRovideLocationInfo.bitOpEcidSignalMeasInfo = NAS_LPP_SLCT;
        NAS_LPP_UpPrePareEcidParameter(&(pstLppMtaMeasInd->stEcidPRovideLocationInfo.stEcidSignalMeasInfo));
    }

    /* send msg data */
    NAS_LPP_SND_MSG(pstLppMtaMeasInd);
}

/*****************************************************************************
 Function Name   : NAS_LPP_UPprePareOtdoaSignalMeasInfo
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.WANGENSHENG      2015-12-10  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_UPprePareOtdoaSignalMeasInfo
(
    LPP_UP_MTA_OTDOA_SIGNAL_MEAS_INFO_STRU  *pstOtdoaSignalMeasInfo,
    NAS_LPP_OTDOA_MEAS_RESLT_STRU           *pstOtdoaMeasRslt
)
{
    NAS_LPP_OTDOA_ASSIST_CFG_STRU          *pstOtdoaAssisCfg = NAS_LPP_NULL_PTR;
    LPP_NEIGHBOUR_MEAS_ELEMENT_STRU        *pstNghbrMeasElement = NAS_LPP_NULL_PTR;
    VOS_UINT32                              ulLoop = 0;
    VOS_UINT32                              ulCellCnt = 0;

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();

    pstOtdoaSignalMeasInfo->usSystemFrameNumber = pstOtdoaMeasRslt->usSfn;
    pstOtdoaSignalMeasInfo->usPhysCellIdRef     = pstOtdoaMeasRslt->usPhyCellIdRef;

    /* 36.355   OTDOA Location Information Elements
    NotSameAsRef0
    The field is absent if the corresponding earfcnRef-v9a0 is present. Otherwise, the target device shall include this field if the EARFCN of the
    RSTD reference cell is not the same as the EARFCN of the assistance data reference cell provided in the OTDOA assistance data.
     */
    if ( pstOtdoaMeasRslt->ulEarfcn <= LPP_MAX_EARFCN)
    {
        if ( pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.ulEarfcn != pstOtdoaMeasRslt->ulEarfcn)
        {
            pstOtdoaSignalMeasInfo->stEarfcnRef.ulArfcnValueEUTRA = pstOtdoaMeasRslt->ulEarfcn;
            pstOtdoaSignalMeasInfo->bitOpArfcnValueEutra = NAS_LPP_SLCT;
        }
    }
    else
    {
        if ( pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.ulEarfcn != pstOtdoaMeasRslt->ulEarfcn)
        {
            pstOtdoaSignalMeasInfo->stEarfcnRefV9a0.ulArfcnValueEUTRAv9a0 = pstOtdoaMeasRslt->ulEarfcn;
            pstOtdoaSignalMeasInfo->bitOpArfcnValueEutraV9a0 = NAS_LPP_SLCT;
            pstOtdoaSignalMeasInfo->bitOpOtdoaSignalMeasInfoExt = NAS_LPP_SLCT;
            pstOtdoaSignalMeasInfo->stEarfcnRefV9a0.bitOpARFCNValueEutraV9A0 = NAS_LPP_SLCT;
        }
    }

    if (LPP_LRRC_INFO_FLAG_VALID == pstOtdoaMeasRslt->ucCellGlobalIdFlag)
    {
       pstOtdoaSignalMeasInfo->bitOpCellGlobalIdRef = NAS_LPP_SLCT;
       pstOtdoaSignalMeasInfo->stCellGlobalIdRef.ulCellIdentity = pstOtdoaMeasRslt->stCellGlobalIdInfo.ulCellIdentity;

       NAS_LPP_NasPlmn2LppPlmn(pstOtdoaMeasRslt->stCellGlobalIdInfo.aucPlmnId,
                               &pstOtdoaSignalMeasInfo->stCellGlobalIdRef.stPlmnIdentity);
    }

    if (LPP_LRRC_INFO_FLAG_VALID == pstOtdoaMeasRslt->ucOtdoaMeasqualityFlag)
    {
        pstOtdoaSignalMeasInfo->bitOpRefQuality = NAS_LPP_SLCT;

        NAS_LPP_PrepareOtdoaQuality(&pstOtdoaMeasRslt->stReferenceMeasQuality, &pstOtdoaSignalMeasInfo->stReferenceQuality);
    }

    pstNghbrMeasElement = pstOtdoaSignalMeasInfo->stNeighbourMeasList.astNeighbourMeasListArray;
    ulCellCnt = pstOtdoaMeasRslt->ulNghbrRptNum;
    pstOtdoaSignalMeasInfo->stNeighbourMeasList.ulNeighbourMeasListCnt = ulCellCnt;

    for ( ulLoop =  0; ulLoop < ulCellCnt; ulLoop++ )
    {
     /*NotSameAsRef2
       The field is absent if the corresponding earfcnNeighbour-v9a0 is present. Otherwise, the target device shall include this field if the EARFCN of
       this neighbour cell is not the same as the earfcnRef for the RSTD reference cell.
       */
        if ( pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn <= LPP_MAX_EARFCN )
        {
            if ( pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn != pstOtdoaMeasRslt->ulEarfcn)
            {
                pstNghbrMeasElement[ulLoop].bitOpArfcnValueEutra = NAS_LPP_SLCT;

                pstNghbrMeasElement[ulLoop].stEarfcnNeighbour.ulArfcnValueEUTRA
                    = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn;
            }
        }
        else
        {
            if ( pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn != pstOtdoaMeasRslt->ulEarfcn)
            {
                pstNghbrMeasElement[ulLoop].bitOpArfcnValueEutraV9a0 = NAS_LPP_SLCT;
                pstNghbrMeasElement[ulLoop].bitOpNeighbourMeasElementExt = NAS_LPP_SLCT;
                pstNghbrMeasElement[ulLoop].stEarfcnNeighbourV9a0.bitOpARFCNValueEutraV9A0 = NAS_LPP_SLCT;
                pstNghbrMeasElement[ulLoop].stEarfcnNeighbourV9a0.ulArfcnValueEUTRAv9a0
                    = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn;
            }
        }

        pstNghbrMeasElement[ulLoop].ulPhysCellIdNeighbor
            = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].usPhyCellIdNeighbour;

        pstNghbrMeasElement[ulLoop].ulRstd = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].usRstd;

        if (LPP_LRRC_INFO_FLAG_VALID == pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ucCellGlobalIdFlag)
        {
            pstNghbrMeasElement[ulLoop].stCellGlobalIdNeighbour.ulCellIdentity
                = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].stCellGlobalIdInfo.ulCellIdentity;

            NAS_LPP_NasPlmn2LppPlmn(pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].stCellGlobalIdInfo.aucPlmnId,
                                   &pstNghbrMeasElement[ulLoop].stCellGlobalIdNeighbour.stPlmnIdentity);

            pstNghbrMeasElement[ulLoop].bitOpCellGlobalIdNeighbour = NAS_LPP_SLCT;
        }

        NAS_LPP_PrepareOtdoaQuality(&pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].stNeighboureMeasQuality,
                                    &pstNghbrMeasElement[ulLoop].stRstdQuality);

    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_SndUpLppMtaOtdoaMeasmentInd
Description    : 给MTA发送OTDOA测量结果
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_SndUpLppMtaOtdoaMeasmentInd
(
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause
)
{
    LPP_MTA_UP_MEAS_IND_STRU        *pstLppMtaMeasInd    = NAS_LPP_NULL_PTR;
    NAS_LPP_OTDOA_MEAS_RESLT_STRU   *pstOtdoaMeasRslt    = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SndUpLppMtaOtdoaMeasmentInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUpLppMtaOtdoaMeasmentInd_ENUM, LNAS_LPP_Func_Enter);

    /* malloc the msg memory */
    pstLppMtaMeasInd = (LPP_MTA_UP_MEAS_IND_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_UP_MEAS_IND_STRU));
    if (NAS_LPP_NULL_PTR == pstLppMtaMeasInd )
    {
        return;
    }
    NAS_LPP_MEM_SET_MSG(pstLppMtaMeasInd, sizeof(LPP_MTA_UP_MEAS_IND_STRU), 0, sizeof(LPP_MTA_UP_MEAS_IND_STRU));

    /* set the msg data */
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstLppMtaMeasInd, ID_LPP_MTA_UP_MEAS_IND);

    /*填充参数*/
    if(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_BUTT != enOtdoaErrCause)
    {
        pstLppMtaMeasInd->bitOpOtodaProvideLocationInfo = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.bitOpOtdoaError = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.stOtdoaError.ulChoice =
                        LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_CHOSEN;
        pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.stOtdoaError.u.stTargetDeviceErrorCauses.enOtoaTargetDeviceErrorCause =
                        enOtdoaErrCause;
    }

    if((NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == NAS_LPP_GetOtdoaPosReqTechType())
       && (PS_TRUE == NAS_LPP_GetOtodaLrrcMeasFlag()))
    {
        /*OTDOA测量信息*/
        pstLppMtaMeasInd->bitOpOtodaProvideLocationInfo = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.bitOpOtdoaSignalMeasInfo = NAS_LPP_SLCT;
        pstOtdoaMeasRslt = NAS_LPP_GetOtodaLrrcMeasAddr();
        NAS_LPP_UPprePareOtdoaSignalMeasInfo(&(pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.stOtdoaSignalMeasInfo),
                                            pstOtdoaMeasRslt);
    }

    /* send msg data */
    NAS_LPP_SND_MSG(pstLppMtaMeasInd);
}

/*****************************************************************************
Function Name  : NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd
Description    : 给MTA发送测量结果
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32 enEcidErrCause,
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause
)
{
    LPP_MTA_UP_MEAS_IND_STRU        *pstLppMtaMeasInd    = NAS_LPP_NULL_PTR;
    NAS_LPP_OTDOA_MEAS_RESLT_STRU   *pstOtdoaMeasRslt    = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd_ENUM, LNAS_LPP_Func_Enter);

    /* malloc the msg memory */
    pstLppMtaMeasInd = (LPP_MTA_UP_MEAS_IND_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_UP_MEAS_IND_STRU));
    if (NAS_LPP_NULL_PTR == pstLppMtaMeasInd )
    {
        return;
    }
    NAS_LPP_MEM_SET_MSG(pstLppMtaMeasInd, sizeof(LPP_MTA_UP_MEAS_IND_STRU), 0, sizeof(LPP_MTA_UP_MEAS_IND_STRU));

    /* set the msg data */
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstLppMtaMeasInd, ID_LPP_MTA_UP_MEAS_IND);

    /*填充参数*/
    if(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_BUTT != enEcidErrCause)
    {
        pstLppMtaMeasInd->bitOpEcidProvideLocationInfo = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stEcidPRovideLocationInfo.bitOpEcidError = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stEcidPRovideLocationInfo.stEcidError.ulChoice =
                        LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_CHOSEN;
        pstLppMtaMeasInd->stEcidPRovideLocationInfo.stEcidError.u.stTargetDeviceErrorCauses.enEcidTargetDeviceErrorCause =
                        enEcidErrCause;
    }

    if(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_BUTT != enOtdoaErrCause)
    {
        pstLppMtaMeasInd->bitOpOtodaProvideLocationInfo = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.bitOpOtdoaError = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.stOtdoaError.ulChoice =
                        LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_CHOSEN;
        pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.stOtdoaError.u.stTargetDeviceErrorCauses.enOtoaTargetDeviceErrorCause =
                        enOtdoaErrCause;
    }

    if((NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == NAS_LPP_GetEcidPosReqTechType())
       && (PS_TRUE == NAS_LPP_GetEcidLrrcMeasFlag()))
    {
        /*ECID测量信息*/
        pstLppMtaMeasInd->bitOpEcidProvideLocationInfo = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stEcidPRovideLocationInfo.bitOpEcidSignalMeasInfo = NAS_LPP_SLCT;
        NAS_LPP_UpPrePareEcidParameter(&(pstLppMtaMeasInd->stEcidPRovideLocationInfo.stEcidSignalMeasInfo));
    }

    if((NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == NAS_LPP_GetOtdoaPosReqTechType())
       && (PS_TRUE == NAS_LPP_GetOtodaLrrcMeasFlag()))
    {
        /*OTDOA测量信息*/
        pstLppMtaMeasInd->bitOpOtodaProvideLocationInfo = NAS_LPP_SLCT;
        pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.bitOpOtdoaSignalMeasInfo = NAS_LPP_SLCT;
        pstOtdoaMeasRslt = NAS_LPP_GetOtodaLrrcMeasAddr();
        NAS_LPP_UPprePareOtdoaSignalMeasInfo(&(pstLppMtaMeasInd->stOtdoaPRovideLocationInfo.stOtdoaSignalMeasInfo),
                                            pstOtdoaMeasRslt);
    }

    /* send msg data */
    NAS_LPP_SND_MSG(pstLppMtaMeasInd);
}

/*****************************************************************************
Function Name  : NAS_LPP_UpRcvMtaOtdoaAssistData
Description    : LPP模块用户面收能力请求的处理
Input          : pstMtaLppUpCapREq表示能力请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. wangensheng 00324863 2015-11-24 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_UpRcvMtaOtdoaAssistData
(
    MTA_LPP_UP_OTDOA_ASSIST_DATA_NTY_STRU                  *pstMtaLppUpOtdoaAssistData
)
{
    NAS_LPP_UP_OTDOA_INFO_STRU         *pstLppUpOtdoaInfo   = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulReturnRslt        = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_UPRcvMtaOtdoaAssistData enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UPRcvMtaOtdoaAssistData_ENUM, LNAS_LPP_Func_Enter);

    pstLppUpOtdoaInfo   = NAS_LPP_GetLppUpOtdoaCtx();

    /* 检查下行辅助数据 */
    ulReturnRslt = NAS_LPP_UpCheckMtaAssistData(&pstMtaLppUpOtdoaAssistData->stOTDOAProvideAssistanceData);
    if (NAS_LPP_MSG_VERIFY_SUCC != ulReturnRslt)
    {
        /*如果校验辅助数据失败，区分场景，如果是UE触发的辅助数据流程，则需要给MTA
          回复测量error，另外还有初始辅助数据场景，以及测量过程中更新了OTDOA的辅助数据，
          无需要清空实体，直接放过去。
        */
        if(LPP_UP_STATE_ASSISTDATA_WAIT_CN_CNF == pstLppUpOtdoaInfo->enLppUpState)
        {
            NAS_LPP_SndUpLppMtaOtdoaMeasmentInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_ASSIST_DATA_MISSING);
            NAS_LPP_UPClrOtdoaCtx();
        }
        return;
    }

    /* 保存辅助数据，设置辅助数据存在标志位 */
    NAS_LPP_UpSaveOtdoaAssistData(&pstMtaLppUpOtdoaAssistData->stOTDOAProvideAssistanceData);

    /* 如果已经收到位置信息请求或者启测量，则发送测量请求并转状态等MEAS_CNF */
    if (LPP_UP_STATE_ASSISTDATA_WAIT_CN_CNF == pstLppUpOtdoaInfo->enLppUpState)
    {
        NAS_LPP_UPSndOtdoaMeasReq(LPP_LRRC_LCS_MEAS_CMD_SETUP);
        NAS_LPP_UpChangeTransFsmState( LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF,
                                       NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);

    }
    else if((LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF == pstLppUpOtdoaInfo->enLppUpState)
          ||(LPP_UP_STATE_WAIT_LRRC_MEAS_IND == pstLppUpOtdoaInfo->enLppUpState))
    {

        /* 重新起测量 */
        NAS_LPP_UPSndOtdoaMeasReq(LPP_LRRC_LCS_MEAS_CMD_SETUP);

        /* 转状态 */
        NAS_LPP_UpChangeTransFsmState( LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF,
                                       NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);

    }
    else
    {
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppUpCapReq
Description    : LPP模块用户面收能力请求的处理
Input          : pstMtaLppUpCapREq表示能力请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_RcvMtaLppUpCapReq
(
    MTA_LPP_UP_CAPABILITY_REQ_STRU          *pstMtaLppUpCapREq
)
{
    NAS_LPP_NORM_LOG("NAS_LPP_RcvMtaLppUpCapReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaLppUpCapReq_ENUM, LNAS_LPP_Func_Enter);

    NAS_LPP_SendLppMtaUpCapCnf();

    return;
}
/*****************************************************************************
 Function Name  : NAS_LPP_UPProcessEcidMeasCnf
 Description    : LPP模块收到ECID的测量回复的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
   1. wangensheng 00324863 2015-11-25  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_UpProcessEcidMeasCnf
(
    LRRC_LPP_ECID_MEAS_CNF_STRU        *pstEcidMeasCnf
)
{
    LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8 enLcsMeasRslt       = 0;
    NAS_LPP_USER_PLANE_ENTITY_STRU     *pstUserPlaneEntity  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_OTDOA_INFO_STRU         *pstLppUpOtdoaInfo   = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_UpProcessEcidMeasCnf: Func enter !");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UpProcessEcidMeasCnf_ENUM,LNAS_LPP_Func_Enter);

    pstUserPlaneEntity  = NAS_LPP_GetLppUpEntityCtx();
    pstLppUpOtdoaInfo   = NAS_LPP_GetLppUpOtdoaCtx();
    enLcsMeasRslt       = pstEcidMeasCnf->ucResult;

    switch(enLcsMeasRslt)
    {
        case LRRC_LPP_LCS_MEAS_RESULT_SUCC:

            /*转状到等测量回复*/
            NAS_LPP_UpChangeTransFsmState( LPP_UP_STATE_WAIT_LRRC_MEAS_IND,
                                           NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);
            break;

        case LRRC_LPP_LCS_MEAS_IDLE_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_CONN_REL_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_PHY_FAIL_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_RESULT_OTHER_CAUSE:
            /* 清除了LPP的实体信息，要判断一下是否有OTDOA的在跑 */
            NAS_LPP_UpChangeTransFsmState( LPP_UP_STATE_IDLE,
                                           NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);
            NAS_LPP_UPClrEcidCtx();
            NAS_LPP_SndUpLppMtaEcidMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL);

            /* 如果同时跑两种技术时OTDOA实体已经被清除了，需要停止相应的定时器 */
            if ((PS_TRUE == pstUserPlaneEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag)
              &&(NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL == pstLppUpOtdoaInfo->enReqPosTechType))
            {
                NAS_LPP_StopReportTimer(&(pstUserPlaneEntity->stMultiPosTechEntity.stReportCriteria),
                                          NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA);

                NAS_LPP_MEM_SET_S(  &(pstUserPlaneEntity->stMultiPosTechEntity.stReportCriteria),
                                    sizeof(NAS_LPP_UP_REPORT_CRITERIA_STRU),
                                    0,
                                    sizeof(NAS_LPP_UP_REPORT_CRITERIA_STRU));

                pstUserPlaneEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag = PS_FALSE;
            }

            break;

        default:
            break;
    }

    return;
}
/*****************************************************************************
 Function Name  : NAS_LPP_UPProcessOtdoaMeasCnf
 Description    : LPP模块收到OTDOA的测量回复的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
   1. wangensheng 00324863 2015-11-25  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_UpProcessOtdoaMeasCnf
(
    LRRC_LPP_OTDOA_MEAS_CNF_STRU        *pstOtdoaMeasCnf
)
{
    LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8 enLcsMeasRslt       = 0;
    NAS_LPP_USER_PLANE_ENTITY_STRU     *pstUserPlaneEntity  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU          *pstLppUpEcidInfo    = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_UpProcessOtdoaMeasCnf: Func enter !");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UpProcessOtdoaMeasCnf_ENUM,LNAS_LPP_Func_Enter);

    pstUserPlaneEntity  = NAS_LPP_GetLppUpEntityCtx();
    pstLppUpEcidInfo    = NAS_LPP_GetLppUpEcidCtx();
    enLcsMeasRslt = pstOtdoaMeasCnf->ucResult;

    switch(enLcsMeasRslt)
    {
        case LRRC_LPP_LCS_MEAS_RESULT_SUCC:

            /*转状到等测量回复*/
            NAS_LPP_UpChangeTransFsmState( LPP_UP_STATE_WAIT_LRRC_MEAS_IND, NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);
            break;

        case LRRC_LPP_LCS_MEAS_IDLE_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_CONN_REL_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_PHY_FAIL_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_RESULT_OTHER_CAUSE:

            /* 清除了LPP UP的OTDOA实体信息 */
            NAS_LPP_INFO_LOG("NAS_LPP_UpProcessOtdoaMeasCnf: Otdoa Meas Fail !");
            NAS_LPP_UpChangeTransFsmState( LPP_UP_STATE_IDLE,
                                           NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);
            NAS_LPP_UPClrOtdoaCtx();
            NAS_LPP_SndUpLppMtaOtdoaMeasmentInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_REF_CELL);

            /* 如果同时跑两种技术时ECID实体已经被清除了，需要停止相应的定时器 */
            if ((PS_TRUE == pstUserPlaneEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag)
              &&(NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL == pstLppUpEcidInfo->enReqPosTechType))
            {
                NAS_LPP_StopReportTimer(&(pstUserPlaneEntity->stMultiPosTechEntity.stReportCriteria),
                                          NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA);
                NAS_LPP_MEM_SET_S(  &(pstUserPlaneEntity->stMultiPosTechEntity.stReportCriteria),
                                    sizeof(NAS_LPP_UP_REPORT_CRITERIA_STRU),
                                    0,
                                    sizeof(NAS_LPP_UP_REPORT_CRITERIA_STRU));

                pstUserPlaneEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag = PS_FALSE;
            }

            break;

        default:
            break;
    }

    return;
}
/*****************************************************************************
 Function Name  : NAS_LPP_SaveUPLppEcidMeasReslt
 Description    : LPP模块收到ECID的测量回复的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
   1. wangensheng 00324863 2015-11-25  新开发
*****************************************************************************/
VOS_VOID    NAS_LPP_UpSaveEcidMeasReslt
(
    LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU                    *pstLrrcLppEcidMeasResultList
)
{
    NAS_LPP_UP_ECID_INFO_STRU          *pstEcidUpEntity     = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulLoop              = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_SaveUPLppEcidMeasReslt: Func enter !");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveUPLppEcidMeasReslt_ENUM,LNAS_LPP_Func_Enter);

    pstEcidUpEntity = NAS_LPP_GetLppUpEcidCtx();

    if(0 == pstLrrcLppEcidMeasResultList->ulCellNum)
    {
        /*如果ECID的小区个数为0，直接返回*/
        pstEcidUpEntity->stEcidMeasRslt.bHaveEcidMeasFlag   = PS_FALSE;
        return;
    }

    for (ulLoop = 0; ulLoop <pstLrrcLppEcidMeasResultList->ulCellNum; ulLoop++ )
    {
        pstEcidUpEntity->stEcidMeasRslt.stLrrcLppEcidMeasResultList.astLrrcLppEcidMeasResult[ulLoop]
                            = pstLrrcLppEcidMeasResultList->astLrrcLppEcidMeasResult[ulLoop];
    }
    pstEcidUpEntity->stEcidMeasRslt.stLrrcLppEcidMeasResultList.ulCellNum = pstLrrcLppEcidMeasResultList->ulCellNum;

    /* 设置ECID测量结果标志位 */
    pstEcidUpEntity->stEcidMeasRslt.bHaveEcidMeasFlag   = PS_TRUE;
}
/*****************************************************************************
 Function Name  : NAS_LPP_SaveUPLppOtdoaMeasReslt
 Description    : LPP模块收到OTDOA的测量回复的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
   1. wangensheng 00324863 2015-11-25  新开发
*****************************************************************************/
VOS_VOID    NAS_LPP_UpSaveOtdoaMeasReslt
(
    LRRC_LPP_OTDOA_MEAS_IND_STRU       *pstOtdoaMeasInd
)
{
    NAS_LPP_UP_OTDOA_INFO_STRU         *pstOtdoaInfo        = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_SaveUPLppOtdoaMeasReslt: Func enter !");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveUPLppOtdoaMeasReslt_ENUM,LNAS_LPP_Func_Enter);

    pstOtdoaInfo = NAS_LPP_GetLppUpOtdoaCtx();
    if(pstOtdoaMeasInd->stNeighbourMeasurementList.ulCellNum < NAS_LPP_MIN_NEIGHBOUR_CELL_NUM)
    {
        /*如果LRRC上报的邻区个数小于2，则认为是异常*/
        pstOtdoaInfo->stOtdoaMeasRslt.bMeasRsltFlag = PS_FALSE;
        return;
    }

    pstOtdoaInfo->stOtdoaMeasRslt.ucCellGlobalIdFlag = pstOtdoaMeasInd->ucCellGlobalIdFlag;
    pstOtdoaInfo->stOtdoaMeasRslt.ucOtdoaMeasqualityFlag = pstOtdoaMeasInd->ucOtdoaMeasqualityFlag;
    pstOtdoaInfo->stOtdoaMeasRslt.usSfn = pstOtdoaMeasInd->usSfn;
    pstOtdoaInfo->stOtdoaMeasRslt.usPhyCellIdRef = pstOtdoaMeasInd->usPhyCellIdRef;
    pstOtdoaInfo->stOtdoaMeasRslt.ulEarfcn = pstOtdoaMeasInd->ulEarfcn;

    NAS_LPP_MEM_CPY_S(  &pstOtdoaInfo->stOtdoaMeasRslt.stCellGlobalIdInfo,
                        sizeof(LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU),
                        &pstOtdoaMeasInd->stCellGlobalIdInfo,
                        sizeof(LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU));
    NAS_LPP_MEM_CPY_S(  &pstOtdoaInfo->stOtdoaMeasRslt.stReferenceMeasQuality,
                        sizeof(LRRC_LPP_OTDOA_MEAS_QUALITY_STRU),
                        &pstOtdoaMeasInd->stReferenceMeasQuality,
                        sizeof(LRRC_LPP_OTDOA_MEAS_QUALITY_STRU));
    NAS_LPP_MEM_CPY_S(  &pstOtdoaInfo->stOtdoaMeasRslt.stNeighbourMeasurementList,
                        sizeof(LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU),
                        &pstOtdoaMeasInd->stNeighbourMeasurementList,
                        sizeof(LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU));
    pstOtdoaInfo->stOtdoaMeasRslt.ulNghbrRptNum = pstOtdoaMeasInd->stNeighbourMeasurementList.ulCellNum;
    /* 设置ECID测量结果标志位 */
    pstOtdoaInfo->stOtdoaMeasRslt.bMeasRsltFlag = PS_TRUE;
}
/*****************************************************************************
 Function Name  : NAS_LPP_ConfirmServeCellChange
 Description    : LPP模块收到OTDOA的测量回复的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
   1. wangensheng 00324863 2015-11-25  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_UpConfirmServeCellChange
(
    LRRC_LPP_ECID_MEAS_IND_STRU        *pstEcidMeasInd
)
{
    NAS_LPP_UP_ECID_INFO_STRU          *pstUPLppEcidInfo    = NAS_LPP_NULL_PTR;
    VOS_INT32                           ulCmpReslt          = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_ConfirmServeCellChange: Func enter !");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ConfirmServeCellChange_ENUM,LNAS_LPP_Func_Enter);
    pstUPLppEcidInfo = NAS_LPP_GetLppUpEcidCtx();

    /* 判断CELL GLOBAL ID INFO */
    ulCmpReslt = NAS_LPP_MEM_CMP(&pstUPLppEcidInfo->stEcidMeasRslt.stLastGlobalIdInfo,
                                 &pstEcidMeasInd->stLrrcLppEcidMeasResultList.astLrrcLppEcidMeasResult[0].stGlobalIdInfo,
                                  sizeof(LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU));
    if (0 != ulCmpReslt)
    {
        return PS_TRUE;
    }

    if (pstUPLppEcidInfo->stEcidMeasRslt.usLastPhyCellId
     != pstEcidMeasInd->stLrrcLppEcidMeasResultList.astLrrcLppEcidMeasResult[0].usPhyCellId)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}
/*****************************************************************************
 Function Name  : NAS_LPP_UpProcessEcidMeasInd
 Description    : LPP模块收到ECID的测量回复的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
   1. wangensheng 00324863 2015-11-25  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_UpProcessEcidMeasInd
(
    LRRC_LPP_ECID_MEAS_IND_STRU         *pstEcidMeasInd
)
{
    NAS_LPP_USER_PLANE_ENTITY_STRU      *pstLppUserPlaneEntity  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_REPORT_CRITERIA_STRU     *pstLppUpReportCriteria = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_OTDOA_INFO_STRU          *pstLppUpOtdoaInfo   = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU          *pstEcidUpEntity     = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_UpProcessEcidMeasInd: Func enter !");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UPprocessEcidMeasInd_ENUM,LNAS_LPP_Func_Enter);
    pstLppUserPlaneEntity   = NAS_LPP_GetLppUpEntityCtx();
    pstLppUpOtdoaInfo       = NAS_LPP_GetLppUpOtdoaCtx();
    pstEcidUpEntity = NAS_LPP_GetLppUpEcidCtx();
    pstLppUpReportCriteria  = &pstLppUserPlaneEntity->stEcidUpEntity.stReportCriteria;

    NAS_LPP_UpSaveEcidMeasReslt(&pstEcidMeasInd->stLrrcLppEcidMeasResultList);

    if ( PS_TRUE == pstLppUserPlaneEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag )
    {
        /* 同时请求多种定位技术，只有上报一次和周期上报两种上报方式 */
        if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE == pstLppUserPlaneEntity->stMultiPosTechEntity.stReportCriteria.enType)
        {
            if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == pstLppUpOtdoaInfo->enReqPosTechType)
            {
                /* OTDOA存在时，检查是否有位置信息数据，如果有则上报 */
                if (PS_TRUE == NAS_LPP_GetOtodaLrrcMeasFlag())
                {
                    NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA);

                    /* 上报一次之后，停止定时器，清空对应技术实体 */
                    NAS_LPP_UPClrEntity();
                }
            }
            else
            {
                /* OTDOA不存在，仅上报ECID的位置信息数据 */
                NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);

                /* 上报一次之后，停止定时器，清空对应技术实体 */
                NAS_LPP_UPClrEntity();

            }
        }
        else if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD == pstLppUserPlaneEntity->stMultiPosTechEntity.stReportCriteria.enType)
        {
            /* 周期性上报只要存储位置信息数据即可 */
        }
        else
        {
        }
    }
    else
    {
        if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE == pstLppUpReportCriteria->enType)
        {
            NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);

            /* 上报一次之后，停止定时器清除ECID实体 */
            NAS_LPP_UPClrEcidCtx();
        }
        else if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD == pstLppUpReportCriteria->enType)
        {
            /* 周期性上报只要存储位置信息数据即可 */
        }
        else if (NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER == pstLppUpReportCriteria->enType)
        {
            /* 判断小区位置信息是否变化，如果没有发生变化，只存储不上报 */
            if (PS_TRUE == NAS_LPP_UpConfirmServeCellChange(pstEcidMeasInd))
            {
                NAS_LPP_INFO_LOG("NAS_LPP_ConfirmServeCellChange: Location change !");
                NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);


                /* 保存Global信息，物理小区信息，trigger上报会用到 */
                NAS_LPP_MEM_CPY_S(  &pstEcidUpEntity->stEcidMeasRslt.stLastGlobalIdInfo,
                                    sizeof( LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU ),
                                    &pstEcidMeasInd->stLrrcLppEcidMeasResultList.astLrrcLppEcidMeasResult[0].stGlobalIdInfo,
                                    sizeof( LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU ));
                pstEcidUpEntity->stEcidMeasRslt.usLastPhyCellId =
                    pstEcidMeasInd->stLrrcLppEcidMeasResultList.astLrrcLppEcidMeasResult[0].usPhyCellId;
            }
            else
            {
                NAS_LPP_INFO_LOG("NAS_LPP_ConfirmServeCellChange: Location don't change !");
            }
        }
        else
        {
        }
    }

}
/*****************************************************************************
 Function Name  : NAS_LPP_UPProcessOtdoaMeasInd
 Description    : LPP模块收到OTDOA的测量回复的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
   1. wangensheng 00324863 2015-11-25  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_UpProcessOtdoaMeasInd
(
    LRRC_LPP_OTDOA_MEAS_IND_STRU        *pstOtdoaMeasInd
)
{
    NAS_LPP_USER_PLANE_ENTITY_STRU      *pstLppUserPlaneEntity  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_REPORT_CRITERIA_STRU     *pstLppUpReportCriteria = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU           *pstLppUpEcidInfo       = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_UpProcessOtdoaMeasInd: Func enter !");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UpProcessOtdoaMeasInd_ENUM,LNAS_LPP_Func_Enter);
    pstLppUserPlaneEntity   = NAS_LPP_GetLppUpEntityCtx();
    pstLppUpEcidInfo        = NAS_LPP_GetLppUpEcidCtx();
    pstLppUpReportCriteria  = &pstLppUserPlaneEntity->stOtdoaUpEntity.stReportCriteria;

    NAS_LPP_UpSaveOtdoaMeasReslt(pstOtdoaMeasInd);
    if ( PS_TRUE == pstLppUserPlaneEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag )
    {
        /* 同时请求多种定位技术，只有上报一次和周期上报两种上报方式 */
        if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE == pstLppUserPlaneEntity->stMultiPosTechEntity.stReportCriteria.enType)
        {
            if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == pstLppUpEcidInfo->enReqPosTechType)
            {
                /* ECID存在时，检查是否有位置信息数据，如果有则上报 */
                if (PS_TRUE == NAS_LPP_GetEcidLrrcMeasFlag())
                {
                    NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA);

                    /* 上报一次之后，停止定时器，清空对应技术实体 */
                    NAS_LPP_UPClrEntity();
                }
            }
            else
            {
                /* ECID不存在，仅上报OTDOA的位置信息数据 */
                NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);

                /* 上报一次之后，停止定时器，清空对应技术实体 */
                NAS_LPP_UPClrEntity();
            }
        }
        else if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD == pstLppUserPlaneEntity->stMultiPosTechEntity.stReportCriteria.enType)
        {
            /* 周期性上报只要存储位置信息数据即可 */
        }
        else
        {
        }
    }
    else
    {
        if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE == pstLppUpReportCriteria->enType)
        {
            NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);

            /* 上报一次之后，停止定时器清除实体 */
            NAS_LPP_UPClrOtdoaCtx();
        }
        else if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD == pstLppUpReportCriteria->enType)
        {
            /* 周期性上报只要存储位置信息数据即可 */
        }
        else
        {
        }
    }

}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppUpMeasNotify
Description    : LPP用户面收到MTA测量通知消息的处理
Input          : pstUpMeasNty表示测量请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_UINT32   NAS_LPP_UpCheckEcidOrOtodaParameter
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
)
{
    NAS_LPP_INFO_LOG("NAS_LPP_UpCheckEcidOrOtodaParameter is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UpCheckEcidOrOtodaParameter_ENUM, LNAS_LPP_Func_Enter);

    if(NAS_LPP_SLCT != pstUpMeasNty->bitOpCommonReqLocInfo)
    {
        /*测量请求没有公共信息，不能完成测量*/
        NAS_LPP_ERR_LOG("NAS_LPP_UpCheckEcidOrOtodaParameter: No Common Infomation!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpCheckEcidOrOtodaParameter_ENUM, LNAS_LPP_UpCheckParaNoCommonInfo);
        return NAS_LPP_FAILURE;
    }

    /*有公共信息，检查三种上报方式*/
    /*如果要求是周期性的上报，则要求清除上报一次以及触发上报的信息*/
    if(NAS_LPP_SLCT == pstUpMeasNty->stCommonIESReqLocInfo.bitOpPeriodicalReportCriteria)
    {
        pstUpMeasNty->stCommonIESReqLocInfo.bitOpTriggeredReportCriteria =
                                                                            NAS_LPP_NO_SLCT;
        NAS_LPP_MEM_SET_S(  &(pstUpMeasNty->stCommonIESReqLocInfo.stTriggerReportCriteria),
                            sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU),
                            0,
                            sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU));

        /*清除上报一次场景的信息*/
        pstUpMeasNty->stCommonIESReqLocInfo.stQos.bitOpResponseTime = NAS_LPP_NO_SLCT;
        NAS_LPP_MEM_SET_S(  &(pstUpMeasNty->stCommonIESReqLocInfo.stQos.stResponseTime),
                            sizeof(LPP_MTA_COMMON_RESPONSE_TIME_STRU),
                            0,
                            sizeof(LPP_MTA_COMMON_RESPONSE_TIME_STRU));
    }

    /*如果是上报一次的场景，则要求清除触发上报的场景*/
    if((NAS_LPP_SLCT == pstUpMeasNty->stCommonIESReqLocInfo.bitOpQos)
            && (NAS_LPP_SLCT == pstUpMeasNty->stCommonIESReqLocInfo.stQos.bitOpResponseTime))
    {
        pstUpMeasNty->stCommonIESReqLocInfo.bitOpTriggeredReportCriteria = NAS_LPP_NO_SLCT;
        NAS_LPP_MEM_SET_S(  &(pstUpMeasNty->stCommonIESReqLocInfo.stTriggerReportCriteria),
                            sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU),
                            0,
                            sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU));
    }

    /*既不是周期性上报，又不是上报一次的场景，则一定是触发上报的场景*/

    /*trigger触发上报方式检查*/
    /*ECID The field is optionally present, need ON, if ECID is requested. Otherwise it is not present.*/
     /*如果是条件触发上报，那么一定是ECID的定位技术，如果出现其他的定位技术，则认为是错误*/
    if((NAS_LPP_SLCT == pstUpMeasNty->stCommonIESReqLocInfo.bitOpTriggeredReportCriteria)
    && (NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo))
    {
        NAS_LPP_ERR_LOG("NAS_LPP_UpCheckEcidOrOtodaParameter,Tigger report NOT for OTDOA!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpCheckEcidOrOtodaParameter_ENUM, LNAS_LPP_UpCheckParaTriggerReportNotForOtdoa);

        return NAS_LPP_FAILURE;
    }

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
Function Name  : NAS_LPP_UpSaveSingleReportCriteriaInfo
Description    : 保存用户面上报方式的逻辑
Input          : pstUpMeasNty表示测量请求的消息结构
                 pstReportCriteria 传出上报准则
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_UpSaveSingleReportCriteriaInfo
(
    MTA_LPP_UP_MEAS_NTY_STRU           *pstUpMeasNty,
    NAS_LPP_UP_REPORT_CRITERIA_STRU    *pstReportCriteria
)
{
    VOS_UINT8 aucRptAmnt[LPP_REPORT_AMOUNT_BUTT] = {1,2,4,8,16,32,64,0};
    VOS_UINT32 aulRptIntvl[LPP_REPORT_INTERVAL_BUTT] = {0,1000,2000,4000,8000,10000,16000,20000,32000,64000};
    LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16  aenRptIntvl[LPP_REPORT_INTERVAL_BUTT] =
    {   LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_1, /* 此对应LPP空口消息对应LPP_REPORT_INTERVAL_NO_PERIOD_REPORT的情形，仅做保护*/
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_1, LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_2,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_4, LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_8,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_10,LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_16,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_20,LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_32,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_64
    };

    if (NAS_LPP_SLCT == pstUpMeasNty->stCommonIESReqLocInfo.bitOpPeriodicalReportCriteria)
    {
        pstReportCriteria->enType = NAS_LPP_REPORT_LOCATION_TYPE_PERIOD;
        pstReportCriteria->u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_PERIODICAL_REPORT;

        pstReportCriteria->u.stReportPeriod.ucReportAmount
            = aucRptAmnt[pstUpMeasNty->stCommonIESReqLocInfo.stPeriodReport.enReportAmount];

        pstReportCriteria->u.stReportPeriod.ulReportIntraval
            = aulRptIntvl[pstUpMeasNty->stCommonIESReqLocInfo.stPeriodReport.enReportInterval];

        pstReportCriteria->u.stReportPeriod.enOtdoaRprtInterval
            = aenRptIntvl[pstUpMeasNty->stCommonIESReqLocInfo.stPeriodReport.enReportInterval];
    }
    else if ((NAS_LPP_SLCT == pstUpMeasNty->stCommonIESReqLocInfo.bitOpQos)
            &&(NAS_LPP_SLCT == pstUpMeasNty->stCommonIESReqLocInfo.stQos.bitOpResponseTime))
    {
        pstReportCriteria->enType = NAS_LPP_REPORT_LOCATION_TYPE_ONCE;
        pstReportCriteria->u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_RESPONSE_TIMER;

        pstReportCriteria->u.stReportOnce.ulResponseTime
            = (VOS_UINT32)(pstUpMeasNty->stCommonIESReqLocInfo.stQos.stResponseTime.ucTime) *1000;/*s转成ms*/
    }
    else if (NAS_LPP_SLCT == pstUpMeasNty->stCommonIESReqLocInfo.bitOpTriggeredReportCriteria)
    {
        pstReportCriteria->enType = NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER;
        pstReportCriteria->u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_REPORT_DURATION;

        pstReportCriteria->u.stReportTrigger.ulReportDuration
            = (VOS_UINT32)(pstUpMeasNty->stCommonIESReqLocInfo.stTriggerReportCriteria.ulReportDuration) *1000;/*s转成ms*/
    }
    else
    {
        NAS_LPP_ERR_LOG("no report criteria");
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_UpSaveReportCriteriaInfo
Description    : 保存用户面上报方式的逻辑
Input          : pstUpMeasNty表示测量请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_UpSaveReportCriteriaInfo
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
)
{
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstEcidReportType  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstOtdoaReportType = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstEcidAndOtdoaReportType = NAS_LPP_NULL_PTR;

    pstEcidReportType = NAS_LPP_EcidReportTypeAddr();
    pstOtdoaReportType = NAS_LPP_OtdoaReportTypeAddr();
    pstEcidAndOtdoaReportType = NAS_LPP_MultiPosTechReportTypeAddr();

    if((NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
     &&(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo))
    {
        /*如果同时请求了ECID和OTDOA的定位技术，则将上报准则存储一份到对应实体中去*/
        NAS_LPP_UpSaveSingleReportCriteriaInfo(pstUpMeasNty, pstEcidAndOtdoaReportType);
    }
    else if(NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
    {
        /*单独请求ECID定位技术*/
        NAS_LPP_UpSaveSingleReportCriteriaInfo(pstUpMeasNty, pstEcidReportType);
    }
    else if(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo)
    {
        /*单独请求OTDOA定位技术*/
        NAS_LPP_UpSaveSingleReportCriteriaInfo(pstUpMeasNty, pstOtdoaReportType);
    }
    else
    {

    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_UpSaveMeasNotifyParameter
Description    : 保存用户面ECID或者OTDOA测量的相关参数
Input          : pstUpMeasNty表示测量请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_UpSaveMeasNotifyParameter
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
)
{
    NAS_LPP_INFO_LOG("NAS_LPP_UpSaveMeasNotifyParameter is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UpSaveMeasNotifyParameter_ENUM, LNAS_LPP_Func_Enter);

    /*保存请求OTDOA或者ECID测量是走用户面还是信令面,以及保存是否请求了ECID或者OTDOA，
      还是ECID&OTDOA同时请求*/
    if((NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
      &&(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo))
    {
        /*将ECID和OTDOA的定位场景都设置为用户面*/
        NAS_LPP_SetEcidPosType(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);
        NAS_LPP_SetOtdoaPosType(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);
        NAS_LPP_SetEcidAndOtdoaMeasFlag(PS_TRUE);

        /*保存ECID请求的类型标识*/
        NAS_LPP_GetLppUpEcidCtx()->stRequestedMeasurements.ucRequestedMeas =
            pstUpMeasNty->stEcidReqLocationInfo.stRequestedMeasurements.ucRequestedMeas;

    }
    else if(NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
    {
        /*当前单请求ECID的定位技术*/
        NAS_LPP_SetEcidPosType(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);
        NAS_LPP_SetEcidAndOtdoaMeasFlag(PS_FALSE);

        /*保存ECID请求的类型标识*/
        NAS_LPP_GetLppUpEcidCtx()->stRequestedMeasurements.ucRequestedMeas =
            pstUpMeasNty->stEcidReqLocationInfo.stRequestedMeasurements.ucRequestedMeas;
    }
    else if(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo)
    {
        /*将OTDOA的定位技术设置上*/
        NAS_LPP_SetOtdoaPosType(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);
        NAS_LPP_SetEcidAndOtdoaMeasFlag(PS_FALSE);
    }
    else
    {}

    /*保存上报方式等关键信息*/
    NAS_LPP_UpSaveReportCriteriaInfo(pstUpMeasNty);

    return;
}

/*****************************************************************************
Function Name   : NAS_LPP_SndUpLppMtaOtdoaAssistDataReq
Description     : 用户面请求Mta otdoa的辅助数据
Input           : None
Output          : None
Return          : VOS_VOID

History         :
1.lifuxin 00253982      2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_SndUpLppMtaOtdoaAssistDataReq
(
    VOS_UINT16                      usPhyCellId
)
{
    LPP_MTA_UP_NO_OTDOA_ASSIST_DATA_IND_STRU    *pstUpOtodaNoAssitDataInd  = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SndUpLppMtaOtdoaAssistDataReq!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUpLppMtaOtdoaAssistDataReq_ENUM, LNAS_LPP_Func_Enter);

    pstUpOtodaNoAssitDataInd =
    (LPP_MTA_UP_NO_OTDOA_ASSIST_DATA_IND_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_UP_NO_OTDOA_ASSIST_DATA_IND_STRU));
    if (NAS_LPP_NULL_PTR == pstUpOtodaNoAssitDataInd)
    {
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstUpOtodaNoAssitDataInd, sizeof(LPP_MTA_UP_NO_OTDOA_ASSIST_DATA_IND_STRU), 0, sizeof(LPP_MTA_UP_NO_OTDOA_ASSIST_DATA_IND_STRU));

    /*消息头*/
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstUpOtodaNoAssitDataInd, ID_LPP_MTA_UP_NO_OTDOA_ASSIST_DATA_IND);
    pstUpOtodaNoAssitDataInd->stOtodaAssistDataReq.usPhyCellId = usPhyCellId;

    NAS_LPP_SND_MSG(pstUpOtodaNoAssitDataInd);

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_UpStartReportTimer
Description    : 启动三种方式定时器
Input          : pstReportCriteria上报准则
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_UpStartReportTimer
(
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstReportCriteria,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
)
{
    if(NAS_LPP_REPORT_LOCATION_TYPE_ONCE == pstReportCriteria->enType)
    {
        /*启动response定时器*/
        NAS_LPP_UpTimerStart(enPosTechType,
                           TI_NAS_LPP_UP_RESPONSE_TIMER);
    }
    else if((NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER == pstReportCriteria->enType)
          &&(0 != pstReportCriteria->u.stReportTrigger.ulReportDuration))
    {
        /*如果是trigger方式的上报，而且不是无线次数上报，则启动trigger duration定时器*/
        NAS_LPP_UpTimerStart(enPosTechType,
                           TI_NAS_LPP_UP_REPORT_DURATION);
    }
    else if(NAS_LPP_REPORT_LOCATION_TYPE_PERIOD == pstReportCriteria->enType)
    {
        /*周期性上报的定时器等到收到LRRC的测量cnf之后再启动定时器*/
        NAS_LPP_UpTimerStart(enPosTechType,
                           TI_NAS_LPP_UP_PERIODICAL_REPORT);
    }
}

/*****************************************************************************
Function Name  : NAS_LPP_UpStartReportTypeTimer
Description    : 启动上报方式定时器
Input          : pstUpMeasNty表示测量请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_UpStartReportTypeTimer
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
)
{
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstEcidReportType  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstOtdoaReportType = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstEcidAndOtdoaReportType = NAS_LPP_NULL_PTR;

    pstEcidReportType = NAS_LPP_EcidReportTypeAddr();
    pstOtdoaReportType = NAS_LPP_OtdoaReportTypeAddr();
    pstEcidAndOtdoaReportType = NAS_LPP_MultiPosTechReportTypeAddr();

    if ((NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
      &&(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo))
    {
        /*ECID和OTDOA同时请求的场景*/
        NAS_LPP_UpStartReportTimer(pstEcidAndOtdoaReportType, NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA);
    }
    else
    {
        if(NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
        {
            /*单独请求ECID场景*/
            NAS_LPP_UpStartReportTimer(pstEcidReportType, NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);
        }

        if(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo)
        {
            /*单独请求OTDOA场景*/
            NAS_LPP_UpStartReportTimer(pstOtdoaReportType, NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);
        }
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_CheckMutilSamePosTech
Description    : LPP用户面check多个相同的定位技术请求判断
Input          :
Output         : VOS_VOID
Return Value   : VOS_BOOL

History        :
1. lifuxin 00253982 2015-11-26 新开发
*****************************************************************************/
VOS_BOOL   NAS_LPP_CheckMutilSamePosTech
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
)
{
    if((NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
       && (NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == NAS_LPP_GetEcidPosReqTechType()))
    {
            return PS_TRUE;
    }

    if((NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo)
       && (NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == NAS_LPP_GetOtdoaPosReqTechType()))
    {
            return PS_TRUE;
    }

    return PS_FALSE;
}


/*****************************************************************************
Function Name  : NAS_LPP_SinglePlaneHaveEcidPostionTech
Description    : 有信令面的ECID running
Input          : pstUpMeasNty表示测量请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_BOOL

History        :
1. lifuxin 00253982 2015-11-26 新开发
*****************************************************************************/
VOS_BOOL   NAS_LPP_SinglePlaneHaveEcidPostionTech( VOS_VOID )
{
    NAS_LPP_LOC_TECH_MAP_STRU       *pstTechMap = NAS_LPP_NULL_PTR;

    pstTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_ECID);
    if(NAS_LPP_NULL_PTR == pstTechMap)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
Function Name  : NAS_LPP_SinglePlaneHaveOtdoaPostionTech
Description    : 有信令面的OTDOA running
Input          : pstUpMeasNty表示测量请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_BOOL

History        :
1. lifuxin 00253982 2015-11-26 新开发
*****************************************************************************/
VOS_BOOL   NAS_LPP_SinglePlaneHaveOtdoaPostionTech( VOS_VOID )
{
    NAS_LPP_LOC_TECH_MAP_STRU       *pstTechMap = NAS_LPP_NULL_PTR;

    pstTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
    if(NAS_LPP_NULL_PTR == pstTechMap)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
Function Name  : NAS_LPP_ControlPlaneHaveTheSamePosTech
Description    : 收到用户面的测量请求的时候判断是否存在相同的信另面定位技术正在running
Input          : pstUpMeasNty表示测量请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-11-26 新开发
*****************************************************************************/
VOS_BOOL   NAS_LPP_ControlPlaneHaveTheSamePosTech
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
)
{
    if((NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
       && (PS_TRUE == NAS_LPP_SinglePlaneHaveEcidPostionTech()))
    {
            return PS_TRUE;
    }

    if((NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo)
       && (PS_TRUE == NAS_LPP_SinglePlaneHaveOtdoaPostionTech()))
    {
            return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppUpMeasNotify
Description    : LPP用户面收到MTA测量通知消息的处理
Input          : pstUpMeasNty表示测量请求的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_RcvMtaLppUpMeasNotify
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
)
{
    VOS_UINT32                  ulRslt          = 0 ;
    NAS_LPP_SERVING_CELL_STRU  *pstServingCell  = NAS_LPP_NULL_PTR;
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32            enEcidErrCause =
            LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_BUTT;
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause =
            LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_BUTT;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvMtaLppUpMeasNotify enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaLppUpMeasNotify_ENUM, LNAS_LPP_Func_Enter);

    /*获取服务小区信息*/
    pstServingCell = NAS_LPP_GetServingCell();

    /*检查当前是否已经有对应的用户面定位技术正在running，如果有，则直接回复测量error
      检查当前是否有信另面的对应的流程正在running，如果有，则直接回复测量error*/
    if((PS_TRUE == NAS_LPP_CheckMutilSamePosTech(pstUpMeasNty))
       || (PS_TRUE == NAS_LPP_ControlPlaneHaveTheSamePosTech(pstUpMeasNty)))
    {
        /*如果ECID和OTDOA有一种定位正在running，则回复MTA，测量error*/
        if(NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
        {
            enEcidErrCause = LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL;
        }

        if(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo)
        {
            enOtdoaErrCause = LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNDEFINED;
        }
        NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd(enEcidErrCause, enOtdoaErrCause);

        return;
    }

    /*参数校验*/
    ulRslt = NAS_LPP_UpCheckEcidOrOtodaParameter(pstUpMeasNty);
    if(NAS_LPP_SUCCESS != ulRslt)
    {
        /*如果ECID和OTDOA有一种定位正在running，则回复MTA，测量error*/
        if(NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
        {
            enEcidErrCause = LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL;
        }

        if(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo)
        {
            enOtdoaErrCause = LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNDEFINED;
        }
        NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd(enEcidErrCause, enOtdoaErrCause);

        return;
    }

    /*校验通过，保存相关参数*/
    NAS_LPP_UpSaveMeasNotifyParameter(pstUpMeasNty);

    /*给LRRC发送测量请求*/
    if(NAS_LPP_SLCT == pstUpMeasNty->bitOpEcidReqLocInfo)
    {
        NAS_LPP_UPSndEcidMeasReq(LPP_LRRC_LCS_MEAS_CMD_SETUP);

        /*转状态到等待LRRC测量回复，同时启动定时器*/
        NAS_LPP_UpChangeTransFsmState(LPP_UP_STATE_WAIT_LRRC_ECID_MEAS_CNF,
                                      NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);
    }

    if(NAS_LPP_SLCT == pstUpMeasNty->bitOpOtdoaReqLocInfo)
    {
        if(PS_TRUE == NAS_LPP_GetOtdoaAssistDataFlag())
        {
            /*有OTDOA的辅助数据*/
            NAS_LPP_UPSndOtdoaMeasReq(LPP_LRRC_LCS_MEAS_CMD_SETUP);

            NAS_LPP_UpChangeTransFsmState(LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF,
                                          NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);
        }
        else
        {
            /*没有OTDOA的辅助数据，则请求MTA OTDOA的辅助数据*/
            NAS_LPP_SndUpLppMtaOtdoaAssistDataReq(pstServingCell->usPhyCellId);
            NAS_LPP_UpChangeTransFsmState(LPP_UP_STATE_ASSISTDATA_WAIT_CN_CNF,
                                          NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);
        }
    }

    /*启动上报方式定时器*/
    NAS_LPP_UpStartReportTypeTimer(pstUpMeasNty);

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppUpAbortMeas
Description    : LPP用户面收到MTA测量停止消息
Input          : pstUpMeasNty表示测量停止的消息结构
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. wangensheng 00324863 2015-12-01 新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvMtaLppUpAbortMeas
(
    MTA_LPP_UP_MEAS_ABORT_NTY_STRU     *pstLppUpMeasAbort
)
{


    /* 如果是同时请求两种技术的，还需要将同时请求的上报方式停止 */
    if ((PS_TRUE == pstLppUpMeasAbort->bAbortOtdoaMeas)
        && (PS_TRUE == pstLppUpMeasAbort->bAbortEcidMeas))
    {
        NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppUpAbortMeas: abort ECID&OTDOA");
        NAS_LPP_UPClrEntity();
    }

    /* 清除ECID实体 */
    else if (PS_TRUE == pstLppUpMeasAbort->bAbortEcidMeas)
    {
        NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppUpAbortMeas: abort ECID");
        NAS_LPP_UPClrEcidCtx();
    }

    /* 清除OTDOA实体 */
    else if (PS_TRUE == pstLppUpMeasAbort->bAbortOtdoaMeas)
    {
        NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppUpAbortMeas: abort OTDOA");
        NAS_LPP_UPClrOtdoaCtx();
    }
    else
    {
    }


    return;
}

#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

