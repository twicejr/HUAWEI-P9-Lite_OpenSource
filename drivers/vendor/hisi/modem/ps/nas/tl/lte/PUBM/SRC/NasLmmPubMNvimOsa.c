/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

******************************************************************************
  File Name       : NasLmmPubMNvimOsa.c
  Description     : NVIM相关操作
  History         :
     1.leili 00132387      2009-02-17   Draft Enact
     2.leili 00132387      2010-08-04   DTS2010072301741
     3.zhengjunyan 00148421   2011-05-28 文件名由 NasMmPubMNvimOsa.c修改为
                                           NasLmmPubMNvimOsa.c
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMNvimOsa.h"
#include    "NasLmmPubMPrint.h"
#include    "LNasNvInterface.h"
#include    "NasEmmPubUMain.h"
#include    "NasLmmPubMOm.h"
#include    "NasLmmPubMEntry.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMNVIMOSA_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMNVIMOSA_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LMM_DecodeOneNvItem
 Description     : 通用的解码NV函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-4-16  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_LMM_DecodeOneNvItem(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    if(NAS_NVIM_NULL_PTR == pstNvCtrlTbl->pNvData)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeOneNvItem: WARNING->pstNvCtrlTbl is Null");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeOneNvItem_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_NVIM_FAIL;
    }

    /*Data len after decode*/
    pstNvCtrlTbl->usDataLen = pstNvCtrlTbl->usNvDataLen;

    /*Data after decode*/
    NAS_LMM_MEM_CPY_S(  pstNvCtrlTbl->pData,
                        pstNvCtrlTbl->usNvDataLen,
                        pstNvCtrlTbl->pNvData,
                        pstNvCtrlTbl->usNvDataLen);
    return NAS_LMM_NVIM_OK;
}


/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvRaCap
 Discription    : 解码RaCapability
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvRaCap(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvRaCap is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvRaCap_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}

/*****************************************************************************
 Function Name  : NAS_EMM_DecodeNvSupCodecs
 Discription    : 解码Supported Codecs
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvSupCodecs(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_EMM_DecodeNvSupCodecs is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvSupCodecs_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}


VOS_UINT32  NAS_LMM_DecodeNvHplmnACT(  NAS_NVIM_CTRL_TBL *pstNvCtrlTbl )
{

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}



VOS_UINT32  NAS_LMM_DecodeSimLRplmnSI(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl )
{

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);

}



/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvMNCLen
 Discription    : 解码MNC LEN
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvMNCLen(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);

}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvFplmnList
 Discription    : 解码Forbidden PLMN List
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32 NAS_LMM_DecodeNvFplmnList(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);

}


/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvUplmn
 Discription    : 解码UPLMN
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
        1 y00159566       2010-3-22          Draft Enact
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvUplmn(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{
    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);

}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvOplmn
 Discription    : 解码OPLMN
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
         1 y00159566       2010-3-22          Draft Enact
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvOplmn(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{
    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);

}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvHPLMNSelPriod
 Discription    : 解码高优先级PLMN选择周期
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvHPLMNSelPriod(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{
    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvCsLoc
 Discription    : 解码CS_LOC_FILE
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvCsLoc(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvCsLoc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvCsLoc_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}

/*****************************************************************************
 Function Name  : NAS_LMM_DecodeSimPsLoc
 Discription    : 解码PS_LOC_FILE
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeSimPsLoc( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{
    VOS_UINT8                           *pucMsg;
    NAS_LMM_UEID_STRU                    *pstUeId;
    VOS_UINT32                          usIndex = 0;
    VOS_UINT32                          ulRslt = VOS_TRUE;
    VOS_UINT32                          ulRslt2 = VOS_TRUE;
    NAS_LMM_GUTI_STRU                    stGuti;
    NAS_MM_NETWORK_ID_STRU              stLrvTai;
    VOS_UINT8                           ucUpdataSta;
    VOS_UINT8                          *pstLastPsLoc;
    NAS_MM_PLMN_ID_STRU                 stPlmnId;


    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeSimPsLoc is entered ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeSimPsLoc_ENUM
,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(&stGuti, sizeof(NAS_LMM_GUTI_STRU), 0, sizeof(NAS_LMM_GUTI_STRU));
    NAS_LMM_MEM_SET_S(&stLrvTai, sizeof(NAS_MM_NETWORK_ID_STRU), 0, sizeof(NAS_MM_NETWORK_ID_STRU));

    pstUeId  = NAS_LMM_GetEmmInfoUeidAddr();
    pstLastPsLoc  = NAS_LMM_GetEmmInfoLastWriteUsimPsLocAddr();

    pucMsg                              = (VOS_UINT8*)pstNvCtrlTbl->pNvData;

    /* 读出卡中的码流保存到上次写卡的全局变量中*/
    NAS_LMM_MEM_CPY_S( pstLastPsLoc,
                        NAS_EMM_EPS_LOC_MAX_LEN,
                        pucMsg,
                        pstNvCtrlTbl->usNvDataLen);

    /*****************GUTI*********************/
    /*检测文件GUTI头的有效性*/
    if ( NAS_LMM_NVIM_GUTI_AND_OETOI_LEN != pucMsg[usIndex])
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimPsLoc: GUTI HEAD ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimPsLoc_ENUM
,LNAS_FUNCTION_LABEL1);
        usIndex += NAS_LMM_NVIM_GUTI_AND_OETOI_LEN;
        usIndex ++;
        pstUeId->bitOpGuti                  = NAS_NVIM_BIT_NO_SLCT;

    }
    else
    {
        stGuti.stGutiHead.ucLenth  = NAS_LMM_NVIM_GUTI_AND_OETOI_LEN;

        usIndex ++;

        stGuti.stGutiHead.ucOeToi  = pucMsg[usIndex] & NAS_EMM_LOW_HALF_BYTE_F;

        if (NAS_LMM_NVIM_GUTI_OETOI != stGuti.stGutiHead.ucOeToi)
        {
            NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimPsLoc: GUTI OETOI ERR");
            TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimPsLoc_ENUM
,LNAS_FUNCTION_LABEL2);
            usIndex += NAS_LMM_NVIM_GUTI_AND_OETOI_LEN;
            pstUeId->bitOpGuti                  = NAS_NVIM_BIT_NO_SLCT;

        }
        else
        {
            usIndex ++;

            /*检测GUTI内容的合法性*/
            ulRslt = NAS_EMM_CheckSimGutiValid(pucMsg, usIndex, NAS_LMM_NVIM_GUTI_LEN);


            /*检测GUTI中PLMN ID的合法性 */
            stPlmnId.aucPlmnId[0] = pucMsg[0 + usIndex];

            stPlmnId.aucPlmnId[1] = pucMsg[1 + usIndex];

            stPlmnId.aucPlmnId[2] = pucMsg[2 + usIndex];

            ulRslt2 &= NAS_LMM_CheckPlmnIsInvalid(&stPlmnId);


            /*检测内容的有效性*/
            if ((VOS_FALSE == ulRslt) || (VOS_TRUE == ulRslt2))
            {
                NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimPsLoc: GUTI Content ERR");
                TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimPsLoc_ENUM
,LNAS_FUNCTION_LABEL3);

                usIndex = usIndex + NAS_LMM_NVIM_GUTI_LEN;

                pstUeId->bitOpGuti                  = NAS_NVIM_BIT_NO_SLCT;
            }
            else
            {
                NAS_LMM_MEM_CPY_S(  &stGuti.stPlmnId,
                                    sizeof(NAS_MM_PLMN_ID_STRU),
                                    &stPlmnId,
                                    sizeof(NAS_MM_PLMN_ID_STRU));

                usIndex += 3;

                stGuti.stMmeGroupId.ucGroupId = pucMsg[usIndex];
                usIndex ++;

                stGuti.stMmeGroupId.ucGroupIdCnt = pucMsg[usIndex];
                usIndex ++;

                stGuti.stMmeCode.ucMmeCode = pucMsg[usIndex];
                usIndex ++;

                NAS_LMM_MEM_CPY_S(                  &(stGuti.stMTmsi),
                                                    sizeof(NAS_LMM_MTMSI_STRU),
                                                    &(pucMsg[usIndex]),
                                                    sizeof(NAS_LMM_MTMSI_STRU));
                usIndex += sizeof(NAS_LMM_MTMSI_STRU);


                pstUeId->bitOpGuti                  = NAS_NVIM_BIT_SLCT;
                NAS_LMM_MEM_CPY_S(                  &(pstUeId->stGuti),
                                                    sizeof(NAS_MM_GUTI_STRU),
                                                    &stGuti,
                                                    sizeof(NAS_LMM_GUTI_STRU));

                NAS_EMM_SetLteNoSubscribeLteRegFlag(NAS_LMM_HAVE_REG_SUCC_ON_LTE);
            }
        }
    }
    /****************L.R.V TAI******************/
    /* 检测LRV TAI中 PLMN合法性 */
    /*检查PLMN中MCC和MNC是否有效*/
    NAS_LMM_MEM_CPY_S(                  &(stLrvTai.stPlmnId),
                                        NAS_LMM_NVIM_PLMN_ID_LEN,
                                        &(pucMsg[usIndex]),
                                        NAS_LMM_NVIM_PLMN_ID_LEN);
    usIndex += NAS_LMM_NVIM_PLMN_ID_LEN;

    ulRslt = NAS_LMM_CheckPlmnIsInvalid(&(stLrvTai.stPlmnId));
    /*ulRslt = NAS_LMM_CheckWhetherAllBytesAreFF(pucMsg, usIndex, NAS_LMM_NVIM_PLMN_ID_LEN);*/
    /*plmn无效，设置全局变量中PLMN为0XFFFFFF,TAC为0xfffe*/
    if (VOS_TRUE == ulRslt)
    {
        NAS_EMM_ClearLVRTai();
        usIndex = usIndex + NAS_LMM_NVIM_TAC_LEN;
    }
    else
    {
        NAS_LMM_MEM_CPY_S(                  &(stLrvTai.stTac),
                                            NAS_LMM_NVIM_TAC_LEN,
                                            &(pucMsg[usIndex]),
                                            NAS_LMM_NVIM_TAC_LEN);
        usIndex += NAS_LMM_NVIM_TAC_LEN;

        if (VOS_TRUE == NAS_LMM_TacIsUnexist(&(stLrvTai.stTac)))
        {
            NAS_LMM_UndefTac(&(stLrvTai.stTac));
        }

        NAS_EMM_SetLVRTai(&stLrvTai);
    }
    /***************UPDATE STATUS**************/
    /*检测文件UPDATE STATUS项的有效性*/
    ucUpdataSta = (pucMsg[usIndex])& NAS_LMM_NVIM_LOW_3_BIT_1;

    if ( NAS_LMM_NVIM_VALID_UPDATESTA < ucUpdataSta)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimPsLoc: UPDATE STATUS Content ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimPsLoc_ENUM
,LNAS_FUNCTION_LABEL4);
    }
    else
    {
        NAS_EMM_MAIN_CONTEXT_SET_AUX_UPDATE_STAE(pucMsg[usIndex]);
    }

    usIndex ++;

    pstNvCtrlTbl->usNvDataLen           = (VOS_UINT16)(usIndex);

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeSimPsLoc:GUTI IS: ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeSimPsLoc_ENUM
,LNAS_FUNCTION_LABEL5);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),(VOS_UINT8 *)&pstUeId->stGuti,20);
    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeSimPsLoc:L.R.V TAI IS: ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeSimPsLoc_ENUM
,LNAS_FUNCTION_LABEL6);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),(VOS_UINT8*)NAS_LMM_GetEmmInfoLastRegPlmnAddr(),4);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),(VOS_UINT8*)NAS_LMM_GetEmmInfoLastRegTacAddr(),4);
    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_DecodeSimPsLoc:UPDATE STATUS IS: ",NAS_EMM_UPDATE_STAE);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_DecodeSimPsLoc_ENUM
,LNAS_FUNCTION_LABEL7,NAS_EMM_UPDATE_STAE);

    return  NAS_LMM_NVIM_OK;
}

/*****************************************************************************
 Function Name  : NAS_LMM_DecodeMncLen
 Discription    : 解码Mnc长度
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
    1. sunjitan 00193151   2015-01-04   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeSimMncLen(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{
    VOS_UINT32                          *pstImsiMncLen;
    VOS_UINT8                           *pUsimData;
    VOS_UINT32                           ulMncLen = 0;
    pstImsiMncLen = NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_MNC_LEN);
    pUsimData     = (VOS_UINT8*)pstNvCtrlTbl->pNvData;

    /* 31.102,4.2.18章节，SIM卡文件长度不小于3，携带MNC需要不小于4 */
    if (NAS_LMM_NVIM_MNCLEN_FILE_MIN_LEN > pstNvCtrlTbl->usNvDataLen)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeMncLen: Sim Mnc file Length ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimMncLen_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_NVIM_FAIL;
    }

    /* 取出相应位置的低4bit */
    ulMncLen = pUsimData[NAS_LMM_NVIM_MNC_LENGTH_POSITION-1] & NAS_LMM_NVIM_LOW_4_BIT_1;

    /* 协议规定MNC的有效长度只能是2或3 */
    if (( NAS_LMM_NVIM_MNCLEN_VALUE_2 == ulMncLen ) || ( NAS_LMM_NVIM_MNCLEN_VALUE_3 == ulMncLen))
    {
        *pstImsiMncLen = ulMncLen;
    }
    else
    {
        /* 赵学理说GU NAS默认值为3，需要跟GU NAS保持一致 */
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeMncLen: Mnc Length ERR, set len=3");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimMncLen_ENUM
,LNAS_FUNCTION_LABEL2);
        *pstImsiMncLen = NAS_LMM_NVIM_MNCLEN_VALUE_3;
    }

    return  NAS_LMM_NVIM_OK;
}

/*****************************************************************************
 Function Name  : NAS_LMM_DecodeSimImsi
 Discription    : 解码IMSI
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeSimImsi(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{
    VOS_UINT8                           *pucImsi;
    NAS_EMM_UEID_STRU                   *pstUeId;

    pstUeId = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_UEID);

    pucImsi = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_IMSI);

    if((NAS_NVIM_NULL_PTR == pstUeId) || (NAS_NVIM_NULL_PTR == pucImsi))
    {
        /* 打印查询的 类型 */
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimImsi: Point is Null");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimImsi_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_NVIM_FAIL;
    }
    /* Mod by y00307272 IMSI长度保护，当IMSI长度大于0x08或0时走无卡开机, 下面pNvData指针被强转了下 */
    if ((NAS_LMM_NVIM_IMSI_FILE_LEN != pstNvCtrlTbl->usNvDataLen)
        ||(((VOS_UINT8*)pstNvCtrlTbl->pNvData)[0] > NAS_LMM_NVIM_IMSI_FILE_LEN - 1)
        ||(((VOS_UINT8*)pstNvCtrlTbl->pNvData)[0] == 0))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimImsi: USIM IMSI LENGTH ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimImsi_ENUM
,LNAS_FUNCTION_LABEL1);

        return NAS_LMM_NVIM_FAIL;
    }

    pstUeId->bitOpImsi                  = NAS_NVIM_BIT_SLCT;

    NAS_LMM_MEM_CPY_S(                  pucImsi,
                                        NAS_LMM_NVIM_IMSI_FILE_LEN,
                                        pstNvCtrlTbl->pNvData,
                                        NAS_LMM_NVIM_IMSI_FILE_LEN);
/*PC REPLAY MODIFY BY LEILI DELETE*/

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeSimImsi: IMSI IS ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeSimImsi_ENUM
,LNAS_FUNCTION_LABEL2);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),pucImsi,NAS_LMM_NVIM_IMSI_FILE_LEN);

    return  NAS_LMM_NVIM_OK;
}


/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvCsCKIK
 Discription    : 解码CS_CKIK
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvCsCKIK(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvCsCKIK is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvCsCKIK_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvPsKey
 Discription    : 解码PS_KEY
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvPsKey(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvPsKey is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvPsKey_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvKC
 Discription    : 解码KC
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvKC(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvKC is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvKC_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvSecAlgrithm
 Discription    : 解码Security Algorithms
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvSecAlgrithm(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvSecAlgrithm is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvSecAlgrithm_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvMacAddr
 Discription    : 解码MAC ADDR
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvMacAddr(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvMacAddr is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvMacAddr_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}
/*****************************************************************************
 Function Name  : NAS_LMM_DecodeNvIPAddr
 Discription    : 解码IP ADDR
 Input          : pstNvCtrlTbl:公共处理结构
 Output         : 解码后的数据
 Return         :
 History:
*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeNvIPAddr(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvIPAddr is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvIPAddr_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_DecodeOneNvItem(pstNvCtrlTbl);
}

VOS_UINT32  NAS_LMM_DecodeNvACC(  NAS_NVIM_CTRL_TBL *pstNvCtrlTbl  )
{
    VOS_UINT8   ucTmp;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeNvACC is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeNvACC_ENUM
,LNAS_ENTRY);

    if (NAS_LMM_NVIM_ACC_FILE_LEN != pstNvCtrlTbl->usNvDataLen)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeNvACC : ACC File Len Err!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeNvACC_ENUM
,LNAS_FUNCTION_LABEL1);

        return NAS_LMM_NVIM_FAIL;
    }

    ucTmp      = *(VOS_UINT8 *)(pstNvCtrlTbl->pNvData);
    gstRrcNasAc.usAccClassMask = ucTmp << 8;
    ucTmp      = *((VOS_UINT8 *)pstNvCtrlTbl->pNvData + 1);
    gstRrcNasAc.usAccClassMask |= ucTmp;

    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_DecodeNvACC: access class is :",gstRrcNasAc.usAccClassMask);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_DecodeNvACC_ENUM
,LNAS_FUNCTION_LABEL2,gstRrcNasAc.usAccClassMask);
    return NAS_LMM_NVIM_OK;
}


/*****************************************************************************
 Function Name   : NAS_LMM_DecodeNvSmc
 Description     : 从卡中读取安全上下文
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yangfan  00159566      2009-10-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_DecodeSimSecContext( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl )
{
    NAS_LMM_SECU_CONTEXT_STRU            stCurSecuContext;
    VOS_UINT16                          usIndex = 0;
    VOS_UINT8                          *pucMsg;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_DecodeSimSecContext is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_ENTRY);

    /*初始化stCurSecuContext*/
    NAS_LMM_MEM_SET_S(  &(stCurSecuContext),
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));

    /*保存安全上下文的长度*/
    NAS_EMM_GET_USIM_SECU_FILE_LEN() = pstNvCtrlTbl->usNvDataLen;

    pucMsg     = (VOS_UINT8*)pstNvCtrlTbl->pNvData;


    NAS_LMM_MEM_SET_S(  NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                        NAS_NVIM_SECU_CONTEXT_MAX_LEN,
                        0,
                        NAS_NVIM_SECU_CONTEXT_MAX_LEN);


    /* 检测文件Tag是否合法 */
    if ( NAS_LMM_NVIM_SECU_CONTEXT_TAG != pucMsg[usIndex++])
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: File Tag Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_NVIM_FAIL;
    }

    /* 检测文件Length是否合法 */
    if ( NAS_LMM_NVIM_SEC_MSG_LEN != pucMsg[usIndex++] )/*待确认*/
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: File LEN Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL2);
        return  NAS_LMM_NVIM_FAIL;
    }

    /********************************* KSIASME *****************************************/
    if ( NAS_LMM_NVIM_SEC_KSI_TAG != pucMsg[usIndex++] )
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: KSI TAG Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL3);

        return  NAS_LMM_NVIM_FAIL;
    }

    if (NAS_LMM_NVIM_SEC_KSI_LEN != pucMsg[usIndex++])
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: KSI LEN Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL4);

        return  NAS_LMM_NVIM_FAIL;
    }

    /* 检测KSI的合法性 */
    if ( NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE < pucMsg[usIndex] )
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: KSI Content Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL5);

        return  NAS_LMM_NVIM_FAIL;
    }

    stCurSecuContext.ucKSIasme = pucMsg[usIndex];

    usIndex                           += NAS_LMM_NVIM_SEC_KSI_LEN ;

    /*********************************** KASME ******************************************/
    if ( NAS_LMM_NVIM_SEC_KASME_TAG != pucMsg[usIndex++] )
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: KASME TAG Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL6);

        return  NAS_LMM_NVIM_FAIL;
    }

    if (NAS_LMM_NVIM_SEC_KASME_LEN != pucMsg[usIndex++])
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: KASME LEN Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL7);

        return  NAS_LMM_NVIM_FAIL;
    }

    NAS_LMM_MEM_CPY_S(                (stCurSecuContext.aucKasme),
                                      NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                      &(pucMsg[usIndex]),
                                      NAS_LMM_NVIM_SEC_KASME_LEN);

    usIndex                           += NAS_LMM_NVIM_SEC_KASME_LEN ;

    /**************************** Uplink NAS count ************************************/
    if ( NAS_LMM_NVIM_SEC_UPNASCOUNT_TAG != pucMsg[usIndex++] )
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: UPNASCOUNT TAG Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL8);

        return  NAS_LMM_NVIM_FAIL;
    }

    if (NAS_LMM_NVIM_SEC_NAS_COUNT_LEN != pucMsg[usIndex++])
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: UPNASCOUNT LEN Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL9);

        return  NAS_LMM_NVIM_FAIL;
    }

    stCurSecuContext.ulUlNasCount = stCurSecuContext.ulUlNasCount | ((VOS_UINT32)pucMsg[usIndex++] << NAS_LMM_NVIM_MOVE_24_BIT);
    stCurSecuContext.ulUlNasCount = stCurSecuContext.ulUlNasCount | ((VOS_UINT32)pucMsg[usIndex++] << NAS_LMM_NVIM_MOVE_16_BIT);
    stCurSecuContext.ulUlNasCount = stCurSecuContext.ulUlNasCount | ((VOS_UINT32)pucMsg[usIndex++] << NAS_LMM_NVIM_MOVE_8_BIT);
    stCurSecuContext.ulUlNasCount = stCurSecuContext.ulUlNasCount | (VOS_UINT32)pucMsg[usIndex++];

    /* 检测NAS count的合法性 */
    if (NAS_LMM_NVIM_MAX_NASCOUNT < stCurSecuContext.ulUlNasCount)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: UPNASCOUNT Content Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL10);

        return  NAS_LMM_NVIM_FAIL;
    }


    /*************************** Downlink NAS count ***********************************/
    if ( NAS_LMM_NVIM_SEC_DNNASCOUNT_TAG != pucMsg[usIndex++] )
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: DNNASCOUNT Tag Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL11);

        return  NAS_LMM_NVIM_FAIL;
    }

    if (NAS_LMM_NVIM_SEC_NAS_COUNT_LEN != pucMsg[usIndex++])
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: DNNASCOUNT Len Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL12);

        return  NAS_LMM_NVIM_FAIL;
    }

    stCurSecuContext.ulDlNasCount = stCurSecuContext.ulDlNasCount | ((VOS_UINT32)pucMsg[usIndex++] << NAS_LMM_NVIM_MOVE_24_BIT);
    stCurSecuContext.ulDlNasCount = stCurSecuContext.ulDlNasCount | ((VOS_UINT32)pucMsg[usIndex++]<< NAS_LMM_NVIM_MOVE_16_BIT);
    stCurSecuContext.ulDlNasCount = stCurSecuContext.ulDlNasCount | ((VOS_UINT32)pucMsg[usIndex++]<< NAS_LMM_NVIM_MOVE_8_BIT);
    stCurSecuContext.ulDlNasCount = stCurSecuContext.ulDlNasCount | (VOS_UINT32)pucMsg[usIndex++];

    /* 检测NAS count的合法性 */
    if (NAS_LMM_NVIM_MAX_NASCOUNT < stCurSecuContext.ulDlNasCount)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: DNNASCOUNT Content Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL13);

        return  NAS_LMM_NVIM_FAIL;
    }

    /******** Identifiers of selected NAS integrity and encryption algorithms *********/
    if ( NAS_LMM_NVIM_SEC_ALG_TAG != pucMsg[usIndex++] )
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: Alg Tag Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL14);

        return  NAS_LMM_NVIM_FAIL;
    }

    if (NAS_LMM_NVIM_SEC_ENCINT_LEN != pucMsg[usIndex++])
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: Alg LEN Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL15);

        return  NAS_LMM_NVIM_FAIL;
    }

    stCurSecuContext.ucSecuAlg = pucMsg[usIndex];

    usIndex                           += NAS_LMM_NVIM_SEC_ENCINT_LEN;

    /*检测合法性*/
    if ( VOS_TRUE != NAS_LMM_CheckSecuAlgValid(stCurSecuContext.ucSecuAlg))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_DecodeSimSecContext: Alg Content Err ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DecodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL16);

        return  NAS_LMM_NVIM_FAIL;
    }


    /* 如果长度超过缓存区，则认为异常不保存读出的码流，如果短于缓存区，多出长度位置已初始化为0 */
    if(NAS_NVIM_SECU_CONTEXT_MAX_LEN >= pstNvCtrlTbl->usNvDataLen)
    {
        /* 保存从USIM卡中读取出的安全上下文码流*/
        NAS_LMM_MEM_CPY_S(  NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                            NAS_NVIM_SECU_CONTEXT_MAX_LEN,
                            pucMsg,
                            pstNvCtrlTbl->usNvDataLen);
    }


    pstNvCtrlTbl->usDataLen           = usIndex;

    /*调用安全上下文更新函数,并计算NasCK ,NasIk*/
    NAS_EMM_SecuSetCurCntxt(&stCurSecuContext);

    return NAS_LMM_NVIM_OK;
}


VOS_UINT32  NAS_LMM_DecodeSoftUsimCnf( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl )
{
    (VOS_VOID)pstNvCtrlTbl;

    return NAS_LMM_NVIM_OK;
}



VOS_UINT32  NAS_LMM_EncodeOneNvItem(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl)
{
    if(NAS_NVIM_NULL_PTR == pstNvCtrlTbl->pData)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_EncodeOneNvItem: WARNING->pData is Null");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_EncodeOneNvItem_ENUM
,LNAS_NULL_PTR);
          return NAS_LMM_NVIM_FAIL;
    }

    NAS_LMM_MEM_CPY_S(  pstNvCtrlTbl->pNvData,
                        pstNvCtrlTbl->usDataLen,
                        pstNvCtrlTbl->pData,
                        pstNvCtrlTbl->usDataLen);

    /*Data len after encode*/
    pstNvCtrlTbl->usNvDataLen           = pstNvCtrlTbl->usDataLen;
    return NAS_LMM_NVIM_OK;
}



VOS_UINT32  NAS_LMM_EncodeNvUplmn( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl )
{
    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_EncodeNvUplmn is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_EncodeNvUplmn_ENUM,LNAS_ENTRY);

    return  NAS_LMM_EncodeOneNvItem(pstNvCtrlTbl);
}

VOS_UINT32  NAS_LMM_EncodeSimSecContext( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl )
{
    VOS_UINT8                          *pucNvData = VOS_NULL_PTR;
    LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU   *pstNvSecContext = VOS_NULL_PTR;
    VOS_UINT16                          usIndex = 0;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_EncodeSimSecContext is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_EncodeSimSecContext_ENUM
,LNAS_ENTRY);

    if(NAS_NVIM_NULL_PTR == pstNvCtrlTbl->pData)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_EncodeSimSecContext: WARNING->pData is Null");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_EncodeSimSecContext_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_NVIM_FAIL;
    }

    pstNvSecContext                     = (LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU *)pstNvCtrlTbl->pData;
    pucNvData                           = (VOS_UINT8 *)pstNvCtrlTbl->pNvData;

    /*初始化安全上下文为全FF*/
    NAS_LMM_SetArrayAllBytesFF(pucNvData,NAS_EMM_GET_USIM_SECU_FILE_LEN());

    /*EPS NAS Security Context Tag    SMC 长度*/
    pucNvData[usIndex ++]               = NAS_LMM_NVIM_SECU_CONTEXT_TAG;

    pucNvData[usIndex ++]               = NAS_LMM_NVIM_SEC_MSG_LEN;

    /*********** KSIASME ************/
    pucNvData[usIndex ++]               = NAS_LMM_NVIM_SEC_KSI_TAG;
    pucNvData[usIndex ++]               = sizeof(VOS_UINT8);
    pucNvData[usIndex ++]               = pstNvSecContext->ucKSIasme;

    /*********** KASME **************/
    pucNvData[usIndex ++]               = NAS_LMM_NVIM_SEC_KASME_TAG;
    pucNvData[usIndex ++]               = NAS_LMM_NVIM_SEC_KASME_LEN;
    NAS_LMM_MEM_CPY_S(                  &(pucNvData[usIndex]),
                                        NAS_LMM_NVIM_SEC_KASME_LEN,
                                        pstNvSecContext->aucKasme,
                                        NAS_LMM_NVIM_SEC_KASME_LEN);

    usIndex                             += NAS_LMM_NVIM_SEC_KASME_LEN;

    /*********** Uplink NAS count **************/
    pucNvData[usIndex ++]               = NAS_LMM_NVIM_SEC_UPNASCOUNT_TAG;
    pucNvData[usIndex ++]               = sizeof(VOS_UINT32);

    pucNvData[usIndex ++]               = (VOS_UINT8)((pstNvSecContext->ulUlNasCount >> NAS_LMM_NVIM_MOVE_24_BIT)
                                                      & NAS_LMM_NVIM_BYTE_FF);
    pucNvData[usIndex ++]               = (VOS_UINT8)((pstNvSecContext->ulUlNasCount >> NAS_LMM_NVIM_MOVE_16_BIT)
                                                      & NAS_LMM_NVIM_BYTE_FF);
    pucNvData[usIndex ++]               = (VOS_UINT8)((pstNvSecContext->ulUlNasCount >> NAS_LMM_NVIM_MOVE_8_BIT)
                                                      & NAS_LMM_NVIM_BYTE_FF);
    pucNvData[usIndex ++]               = (VOS_UINT8)((pstNvSecContext->ulUlNasCount)
                                                      & NAS_LMM_NVIM_BYTE_FF);

    /*********** Downlink NAS count **************/
    pucNvData[usIndex ++]               = NAS_LMM_NVIM_SEC_DNNASCOUNT_TAG;
    pucNvData[usIndex ++]               = sizeof(VOS_UINT32);

    pucNvData[usIndex ++]               = (VOS_UINT8)((pstNvSecContext->ulDlNasCount >> NAS_LMM_NVIM_MOVE_24_BIT)
                                                      & NAS_LMM_NVIM_BYTE_FF);
    pucNvData[usIndex ++]               = (VOS_UINT8)((pstNvSecContext->ulDlNasCount >> NAS_LMM_NVIM_MOVE_16_BIT)
                                                      & NAS_LMM_NVIM_BYTE_FF);
    pucNvData[usIndex ++]               = (VOS_UINT8)((pstNvSecContext->ulDlNasCount >> NAS_LMM_NVIM_MOVE_8_BIT)
                                                      & NAS_LMM_NVIM_BYTE_FF);
    pucNvData[usIndex ++]               = (VOS_UINT8)((pstNvSecContext->ulDlNasCount)
                                                      & NAS_LMM_NVIM_BYTE_FF);


    /*********** Identifiers of selected NAS integrity and encryption algorithms **************/
    pucNvData[usIndex ++]               = NAS_LMM_NVIM_SEC_ALG_TAG;
    pucNvData[usIndex ++]               = sizeof(VOS_UINT8);
    pucNvData[usIndex ++]               = pstNvSecContext->ucSecuAlg;

    pstNvCtrlTbl->usNvDataLen           = (VOS_UINT16)NAS_EMM_GET_USIM_SECU_FILE_LEN();

    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_EncodeSimSecContext: ESP SEC CONTEXT",pstNvCtrlTbl->usNvDataLen);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_EncodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL1,pstNvCtrlTbl->usNvDataLen);

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_EncodeSimSecContext: ESP SEC CONTEXT");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_EncodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL2);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),pucNvData,pstNvCtrlTbl->usNvDataLen);

    /* 如果上次写卡的码流与本次要写入的完全相同，则无需写入 */
    if((0 == NAS_LMM_MEM_CMP( (const VOS_VOID *)NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                              (const VOS_VOID *)pucNvData,
                              pstNvCtrlTbl->usNvDataLen)))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_EncodeSimPsLoc:  Equal  value!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_EncodeSimSecContext_ENUM
,LNAS_FUNCTION_LABEL3);
        return NAS_LMM_NVIM_WRITTEN_UNNEEDED;
    }

    /* 不相同，更新为本次写卡码流 */
    NAS_LMM_MEM_SET_S(  NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                        NAS_NVIM_SECU_CONTEXT_MAX_LEN,
                        0,
                        NAS_NVIM_SECU_CONTEXT_MAX_LEN);

    /* 如果长度大于缓存区，则认为异常不保存上次写卡码流 */
    if(NAS_NVIM_SECU_CONTEXT_MAX_LEN >= pstNvCtrlTbl->usNvDataLen)
    {
        NAS_LMM_MEM_CPY_S(  NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                            NAS_NVIM_SECU_CONTEXT_MAX_LEN,
                            pucNvData,
                            pstNvCtrlTbl->usNvDataLen);
    }

    return NAS_LMM_NVIM_OK;

}


VOS_UINT32  NAS_LMM_EncodeSimPsLoc( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl )
{
    NAS_LMM_GUTI_STRU                    stGuti   = {{0}};
    NAS_MM_TA_STRU                      stTai;
    VOS_UINT8                           *pucNvData;
    VOS_UINT8                           *pucData;
    VOS_UINT16                           usIndex = 0;
    VOS_UINT32                           ulLen = 0;
    VOS_UINT8                          *pstLastPsLoc;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_EncodeSimPsLoc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_EncodeSimPsLoc_ENUM
,LNAS_ENTRY);

    pstLastPsLoc                        = NAS_LMM_GetEmmInfoLastWriteUsimPsLocAddr();

    if(NAS_NVIM_NULL_PTR == pstNvCtrlTbl->pData)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_EncodeSimPsLoc: WARNING->pData is Null");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_EncodeSimPsLoc_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_NVIM_FAIL;
    }

    pucData                             = (VOS_UINT8 *)pstNvCtrlTbl->pData;
    pucNvData                           = (VOS_UINT8 *)pstNvCtrlTbl->pNvData;

    /*****************GUTI*******************/
    ulLen                               = sizeof(VOS_UINT32);
    NAS_LMM_MEM_CPY_S(                  &stGuti,
                                        sizeof(NAS_LMM_GUTI_STRU),
                                        &(pucData[ulLen]),
                                        sizeof(NAS_LMM_GUTI_STRU));

    pucNvData[usIndex ++]               = NAS_LMM_NVIM_GUTI_AND_OETOI_LEN;
    pucNvData[usIndex ++]               = (stGuti.stGutiHead.ucOeToi |
                                           NAS_EMM_HIGH_HALF_BYTE_F);
    pucNvData[usIndex ++]               = stGuti.stPlmnId.aucPlmnId[0];
    pucNvData[usIndex ++]               = stGuti.stPlmnId.aucPlmnId[1];
    pucNvData[usIndex ++]               = stGuti.stPlmnId.aucPlmnId[2];
    pucNvData[usIndex ++]               = stGuti.stMmeGroupId.ucGroupId;
    pucNvData[usIndex ++]               = stGuti.stMmeGroupId.ucGroupIdCnt;
    pucNvData[usIndex ++]               = stGuti.stMmeCode.ucMmeCode;
    /*pucNvData[usIndex ++]               = stGuti.stMTmsi.ucMTmsi;*/
    NAS_LMM_MEM_CPY_S(                  &(pucNvData[usIndex]),
                                        sizeof(NAS_LMM_MTMSI_STRU),
                                        &(stGuti.stMTmsi),
                                        sizeof(NAS_LMM_MTMSI_STRU));
    usIndex                             += sizeof(NAS_EMM_MTMSI_STRU);

    /*L.V.R TAI*/
    ulLen                               += sizeof(NAS_LMM_GUTI_STRU);
    NAS_LMM_MEM_CPY_S(                  &stTai,
                                        sizeof(NAS_MM_TA_STRU),
                                        &(pucData[ulLen]),
                                        sizeof(NAS_MM_TA_STRU));

    pucNvData[usIndex ++]               = stTai.stPlmnId.aucPlmnId[0];
    pucNvData[usIndex ++]               = stTai.stPlmnId.aucPlmnId[1];
    pucNvData[usIndex ++]               = stTai.stPlmnId.aucPlmnId[2];
    pucNvData[usIndex ++]               = stTai.stTac.ucTac;
    pucNvData[usIndex ++]               = stTai.stTac.ucTacCnt;

    /*UPDATE STATUS*/
    ulLen                               += sizeof(NAS_MM_TA_STRU);
    pucNvData[usIndex++]                = pucData[ulLen];

    pstNvCtrlTbl->usNvDataLen           = usIndex;

    /* 如果上次写卡的码流与本次要写入的完全相同，则无需写入 */
    if((0 == NAS_LMM_MEM_CMP( (const VOS_VOID *)pstLastPsLoc,
                              (const VOS_VOID *)pucNvData,
                              pstNvCtrlTbl->usNvDataLen)))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_EncodeSimPsLoc:  Equal  value!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_EncodeSimPsLoc_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_NVIM_WRITTEN_UNNEEDED;
    }

    /* 不相同，更新为本次写卡码流 */
    NAS_LMM_MEM_SET_S(  pstLastPsLoc,
                        NAS_EMM_EPS_LOC_MAX_LEN,
                        0,
                        sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

    NAS_LMM_MEM_CPY_S(  pstLastPsLoc,
                        NAS_EMM_EPS_LOC_MAX_LEN,
                        pucNvData,
                        pstNvCtrlTbl->usNvDataLen);

    return NAS_LMM_NVIM_OK;
}
/*lint +e961*/
/*lint +e960*/


VOS_UINT32  NAS_LMM_EncodeNvHPLMNSelPriod( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl )
{
    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_EncodeNvHPLMNSelPriod is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_EncodeNvHPLMNSelPriod_ENUM
,LNAS_ENTRY);

    return  NAS_LMM_EncodeOneNvItem(pstNvCtrlTbl);
}

/*****************************************************************************
 Function Name   : NAS_LMM_CheckNvDrxParamAndTransVal
 Description     : 检查NVIM中读取的DRX参数是否有效，如果无效则按照协议进行转换,
                   数据最后给pstTransDrxParam赋值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_CheckNvDrxParamAndTransVal(
                                         CONST  NAS_MM_DRX_STRU *pstNvimDrxParam,
                                                NAS_MM_DRX_STRU *pstTransDrxParam)
{
    /*检查入参指针*/
    if ((VOS_NULL_PTR == pstNvimDrxParam)
      ||(VOS_NULL_PTR == pstTransDrxParam))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckNvDrxParamAndTransVal: Input NULL PTR.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_CheckNvDrxParamAndTransVal_ENUM
,LNAS_NULL_PTR);
        return;
    }

    /*SPLIT on CCCH有效性验证,无效赋值 0*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxSplitOnCcchValid(pstNvimDrxParam->ucSplitOnCcch))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckNvDrxParamAndTransVal: SplitOnCcch InValid.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_CheckNvDrxParamAndTransVal_ENUM
,LNAS_FUNCTION_LABEL1);
        pstTransDrxParam->ucSplitOnCcch = NAS_LMM_SPLIT_ON_CCCH_NOT_SUPPORT;
    }
    else
    {
        pstTransDrxParam->ucSplitOnCcch = pstNvimDrxParam->ucSplitOnCcch;
    }

    /*non_DRX Timer有效性验证，无效则赋值 0*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxNonDrxTimerValid(pstNvimDrxParam->ucNonDrxTimer))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckNvDrxParamAndTransVal: NonDrxTimer InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckNvDrxParamAndTransVal_ENUM
,LNAS_FUNCTION_LABEL2);
        pstTransDrxParam->ucNonDrxTimer = NAS_LMM_NO_NONE_DRX_MODE;
    }
    else
    {
        pstTransDrxParam->ucNonDrxTimer = pstNvimDrxParam->ucNonDrxTimer;
    }

    /*SPLIT PG CYCLE CODE有效则直接赋值，无效则按照协议转换*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxPgCycleCodeValid(pstNvimDrxParam->ucSplitPgCode))
    {
        pstTransDrxParam->ucSplitPgCode = NAS_LMM_SPLIT_PG_CYCLE_CODE_ONE;
    }
    else
    {
        pstTransDrxParam->ucSplitPgCode = pstNvimDrxParam->ucSplitPgCode;
    }

     /*DRX Valude for S1 Mode有效则直接赋值，无效则按照协议转换*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsUeDrxCycleValid(pstNvimDrxParam->ucPsDrxLen))
    {
        pstTransDrxParam->ucPsDrxLen = NAS_LMM_UE_NOT_SPEC_DRX_VALUE;
    }
    else
    {
        pstTransDrxParam->ucPsDrxLen    = pstNvimDrxParam->ucPsDrxLen;
    }

    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

