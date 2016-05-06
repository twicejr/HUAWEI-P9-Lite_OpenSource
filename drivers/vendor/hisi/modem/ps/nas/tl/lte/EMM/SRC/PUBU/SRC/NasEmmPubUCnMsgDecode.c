/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmPubUCnMsgDecode.c
  Description     :
  History         :
      1.  niezhouyu  00108792  Draft Enact
      2.  qilili     00145085  修改问题单
      3. zhengjunyan 00148421 2009.03.03 问题单BA8D01054
        IDEN REQ消息携带类型值为0，没有作为IMSI类型处理
      4.  yangqianhui 00135146  2009-10-19 BN8D01126 NAS圈复杂度优化
      5. shicongyong 00111599  2009-10-20 BN8D01116 NAS圈复杂度优化
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmPubUInclude.h"
#ifdef PS_ITT_PC_TEST_NAS
#include    "NasEmmLppMsgProc.h"
#endif
/*lint -e766*/
/*#include "TlPsDrv.h"*/
/*end*/
/*lint +e766*/

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBUCNMSGDECODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBUCNMSGDECODE_C
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


NAS_EMM_DECODE_MSG_IE_INFO_STRU  g_astCnTauAcpIEList[] =
{
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3412_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_GUTI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_TAI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EPSBTXT_STUS_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_LAI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_MSID_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EMMCAU_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_AUCRESERVE_IE_ITEM(3),NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3402_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3423_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_PLMNLIST_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EMERGENCYLIST_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EPSNETFEATURE_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_AUCRESERVE_IE_ITEM(3),NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_UPDTAERSLT_IE_ITEM,NAS_EMM_DECODE_IE_O)

};
NAS_EMM_DECODE_MSG_IE_INFO_STRU  g_astCnAttachAcpIEList[] =
{
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_GUTI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_LAI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_MSID_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EMMCAU_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_AUCRESERVE_IE_ITEM(3),NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3402_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3423_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_PLMNLIST_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EMERGENCYLIST_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EPSNETFEATURE_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_AUCRESERVE_IE_ITEM(3),NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_UPDTAERSLT_IE_ITEM,NAS_EMM_DECODE_IE_O)

};

NAS_EMM_DECODE_MSG_IE_INFO_STRU  g_astCnAttachRejIEList[] =
{
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_ESMMSGCON_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3402_2_IE_ITEM,NAS_EMM_DECODE_IE_O)
};

/*后续可能会使用，暂保留,先注释掉*/
/*NAS_EMM_DECODE_MSG_INFO_STRU g_astCnMsgList[] =
{
    NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_ATTACH_ACP,g_astCnAttachAcpIEList,NAS_EMM_CN_ATTACH_ACP_STR),
    NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_TAU_ACP,g_astCnTauAcpIEList,NAS_EMM_CN_TAU_ACP_STR)
};*/

NAS_EMM_DECODE_MSG_FUNS_STRU g_astEmmCnMsgFuns[] =
{
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_ATTACH_ACP,NAS_EMM_DecodeCnAttachAcpMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_ATTACH_REJ,NAS_EMM_DecodeCnAttachRejMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_DETACH_REQ_MT,NAS_EMM_DecodeCnDetachReqMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_DETACH_ACP_MO,NAS_EMM_DecodeCnDetachAcpMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_GUTI_CMD,NAS_EMM_DecodeCnGUTICmdMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_IDEN_REQ,NAS_EMM_DecodeCnIdenReqMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_SER_REJ,NAS_EMM_DecodeCnSerRejMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_TAU_ACP,NAS_EMM_DecodeCnTAUAcpMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_TAU_REJ,NAS_EMM_DecodeCnTAURejMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_AUTH_REQ,NAS_EMM_DecodeCnAuthReqMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_AUTH_REJ,NAS_EMM_DecodeCnAuthRejMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_SMC_CMD,NAS_EMM_DecodeCnSecurModeCtrlMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_EMM_INFO,NAS_EMM_DecodeCnEmmInfoMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_EMM_STATUS,NAS_EMM_DecodeCnEmmStatusMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT,NAS_EMM_DecodeCnDownlinkNasTransportMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_CS_SER_NOTIFICATION,NAS_EMM_DecodeCnCsSerNotification),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_DOWNLINK_GENERIC_NAS_TRANSPORT,NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg)
};
VOS_UINT32 g_ulSizeof_g_astEmmCnMsgFuns = sizeof(g_astEmmCnMsgFuns);

/*zhuyqEncode*/
/*
NAS_EMM_CN_MSGCON_STRU                  g_stAirMsgEncode;
*/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : ulEt
                   pOsaMsg
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/
/*lint -e72*/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_DecodeCnMsg( MsgBlock        *pOsaMsg,
                                    NAS_EMM_CN_MSG_STRU      *pstCnMsgStru)/*lint  -e818*/
{
    VOS_UINT8                           *pRcvMsg            = NAS_EMM_NULL_PTR;
    VOS_UINT32                           ulIndex            = NAS_EMM_NULL;
    VOS_UINT32                           ulRslt             = NAS_EMM_NULL;
    LRRC_LMM_DATA_IND_STRU                *pstTmpRcvMsg       = NAS_EMM_NULL_PTR;
    LRRC_LNAS_MSG_STRU                    *pstNasRcvMsg       = NAS_EMM_NULL_PTR;
    VOS_UINT8                            ucPD               = NAS_EMM_NULL;
    VOS_UINT8                            ucSecHeadTp        = NAS_EMM_NULL;
    VOS_UINT8                            ucMsgType          = NAS_EMM_NULL;
    NAS_EMM_DECODE_CN_MSG_HEADER_STRU    *pstCnMsgHeaer     = \
                                        (NAS_EMM_DECODE_CN_MSG_HEADER_STRU *)pstCnMsgStru;
    VOS_UINT32                           i                  = 0;
    VOS_UINT32                           ulMsgNum           = g_ulSizeof_g_astEmmCnMsgFuns/
                                                            sizeof(NAS_EMM_DECODE_MSG_FUNS_STRU);

    /* 判断入口参数是否合法*/
    if( NAS_EMM_NULL_PTR == pOsaMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsg:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsg_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*结构化消息，取出消息体*/
    pstTmpRcvMsg = (LRRC_LMM_DATA_IND_STRU*)pOsaMsg;
    pstNasRcvMsg = &(pstTmpRcvMsg->stNasMsg);
    pRcvMsg      = pstTmpRcvMsg->stNasMsg.aucNasMsg;

    /*取出PD*/
    ucPD = pRcvMsg[ulIndex]& EMM_CN_MSG_PDMASK;

    /*判断PD是否符合协议要求，GMM消息为0x07*/
    if(EMM_CN_MSG_PD_EMM != ucPD)
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_PD_IE, EMM_CN_MSG_PD_INVALID, ucPD);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsg:WARNING:NAS->EMM MSG PD is wrong");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }
    /*取出Security header type*/
    ucSecHeadTp = (VOS_UINT8)((pRcvMsg[ulIndex]& NAS_EMM_HIGH_HALF_BYTE_F)
                >>NAS_EMM_MOVEMENT_4_BITS);

    /*判断Security header type是否符合协议*/
    if((ucSecHeadTp > NAS_EMM_MSG_SEC_TYPE_NAS)
        &&(ucSecHeadTp < NAS_EMM_MSG_SEC_TYPE_SERREQ))
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_SEC_HEAD_TYPE_IE, EMM_CN_MSG_SEC_HEAD_TYPE_INVALID, ucSecHeadTp);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsg:WARNING:NAS->EMM MSG Security header type is wrong");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsg_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
    if(ucSecHeadTp > NAS_EMM_MSG_SEC_TYPE_SERREQ)
    {
        ucSecHeadTp = NAS_EMM_MSG_SEC_TYPE_SERREQ;
    }

    /*跳过PD和Security header type*/
    ulIndex++;

    /*第2个字节为消息类型，取出*/
    ucMsgType = pRcvMsg[ulIndex];

    pstCnMsgHeaer->ucPd = ucPD;
    pstCnMsgHeaer->ucSecurityHeadType = ucSecHeadTp;
    pstCnMsgHeaer->ucMt = ucMsgType;

    for(i = 0;i < ulMsgNum;i++)
    {
        if(g_astEmmCnMsgFuns[i].enMsgTp == ucMsgType)
        {
            break;
        }
    }

    if(i >= ulMsgNum)
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_MSG_TYPE_IE, EMM_CN_MSG_MSG_TYPE_INVALID, ucMsgType);
        /*打印错误信息*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsg:WARNING:NAS->EMM MSG Type not assigned ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsg_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_FAIL;
    }
    if(NAS_EMM_NULL_PTR != g_astEmmCnMsgFuns[i].pDecodeMsgFun)
    {
        ulRslt = g_astEmmCnMsgFuns[i].pDecodeMsgFun(pstNasRcvMsg, ulIndex, pstCnMsgStru);
    }
    else
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsg:g_astEmmCnMsgFuns[i].pDecodeMsgFun is null ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    return ulRslt;
}
VOS_VOID  NAS_EMM_DecodeCnMsgIEOptListCalcLen
(
    VOS_UINT8                                   *pTmpRcvMsg,
    NAS_EMM_DECODE_IE_INFO_STRU                 stIEInfo,
    VOS_UINT32                                  *pulIndexNoIEI,
    VOS_UINT32                                  *pulIELen,
    VOS_UINT32                                  *pulIndex
)
{
    VOS_UINT32      ulIndexNoIEI      = *pulIndexNoIEI;          /*信元(除去IEI)的位置      */
    VOS_UINT32      ulIELen           = NAS_EMM_NULL;          /*信元长度                 */

    /*类型中包含L的时候，长度需要重新计算出来*/
    if(NAS_EMM_DECODE_IE_FORMAT_L== \
                (NAS_EMM_DECODE_IE_FORMAT_L&stIEInfo.ucIEFormat))
    {
        if (NAS_RELEASE_R11)
        {
            /* 如果可选信元的格式是TLV_E或者LV_E，L是占了两个字节 */
            if ((NAS_EMM_DECODE_IE_FORMAT_TLV_E == stIEInfo.ucIEFormat) ||
                (NAS_EMM_DECODE_IE_FORMAT_LV_E == stIEInfo.ucIEFormat))
            {
                ulIELen = (pTmpRcvMsg[(*pulIndex)+ \
                              ((NAS_EMM_DECODE_IE_FORMAT_T&stIEInfo.ucIEFormat)/ \
                              NAS_EMM_DECODE_IE_FORMAT_T)]<< NAS_EMM_MOVEMENT_8_BITS)
                            | pTmpRcvMsg[(*pulIndex)+ \
                                          ((NAS_EMM_DECODE_IE_FORMAT_T&stIEInfo.ucIEFormat)/ \
                                          NAS_EMM_DECODE_IE_FORMAT_T) + 1];

                /* 加上L本身的字节 */
                ulIELen = ulIELen + 2;
                /*加上IEI的字节, (ulIndexNoIEI - ulIndex) 为IEI的字节*/
                ulIELen = ulIELen + (ulIndexNoIEI - (*pulIndex));
            }
            else
            {
                /*根据L的位置取得长度,这里默认L总是再整字节上,根据类型来获取*/
                ulIELen = pTmpRcvMsg[(*pulIndex)+ \
                          ((NAS_EMM_DECODE_IE_FORMAT_T&stIEInfo.ucIEFormat)/ \
                          NAS_EMM_DECODE_IE_FORMAT_T)];

                /*加上L本身字节*/
                ulIELen++;
                /*加上IEI的字节, (ulIndexNoIEI - ulIndex) 为IEI的字节*/
                ulIELen = ulIELen + (ulIndexNoIEI - (*pulIndex));
            }
        }
        else
        {
            /*根据L的位置取得长度,这里默认L总是再整字节上,根据类型来获取*/
            ulIELen = pTmpRcvMsg[(*pulIndex)+ \
                      ((NAS_EMM_DECODE_IE_FORMAT_T&stIEInfo.ucIEFormat)/ \
                      NAS_EMM_DECODE_IE_FORMAT_T)];

            /*加上L本身字节*/
            ulIELen++;
            /*加上IEI的字节, (ulIndexNoIEI - ulIndex) 为IEI的字节*/
            ulIELen = ulIELen + (ulIndexNoIEI - (*pulIndex));
        }
        *pulIELen += ulIELen;
    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnMsgIEOptList
 Description     : 循环解析可选信元
 Input           : NAS_EMM_DECODE_IELIST_PARA_STRU
 Output          :
 Return          : 解码是否成功
 History         :
    1.s00111599      2009-9-28  Draft Enact
    2.z00148421      2011-3-01  DTS201102220339:对于识别到的IE，如果没提供Decode
                                函数，则跳过该IE，继续解码
    3.n00181501      2012-7-23 modify 增加网络兼容性,对可选信元解析时忽略顺序
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnMsgIEOptList(
                                            NAS_EMM_DECODE_IELIST_PARA_STRU *pstIEOptParaList,
                                            VOS_UINT32  *pulSum
                                          )
{
    /*输入参数重命名的定义             */
    VOS_UINT8                           *pTmpRcvMsg;
    VOS_UINT32                          *pTmpCnMsgOpt;
    VOS_UINT32                          ulTmpOptPos;
    VOS_VOID                            *pstCnMsgStruIE;
    NAS_EMM_DECODE_MSG_IE_INFO_STRU     *pstMsgIETable;

    /*下面为辅助变量的定义及初始化     */
    VOS_UINT32      ulIESum           = NAS_EMM_NULL;          /*单个信元解析长度         */
    VOS_UINT32      ulOptBit          = NAS_EMM_BIT_SLCT;      /*可选项bit位对应的数值    */
    VOS_UINT32      ulIndex           = NAS_EMM_NULL;          /*记录当前信元的开始位置   */
    VOS_UINT32      ulIndexNoIEI      = NAS_EMM_NULL;          /*信元(除去IEI)的位置      */
    VOS_UINT32      ulIELen           = NAS_EMM_NULL;          /*信元长度                 */
    VOS_UINT32      ulIEI             = NAS_EMM_NULL;          /*信元类型编码             */
    VOS_UINT32      ulRslt            = NAS_EMM_FAIL;
    VOS_UINT32      i                 = NAS_EMM_NULL;
    VOS_UINT32      ulDecodedIE       = NAS_EMM_NULL;
    VOS_UINT32      ulDecodingIE      = NAS_EMM_BIT_SLCT;

    /* 判断输入参数是否合法*/
    ulRslt = NAS_EMM_DecodeCnMsgIEOptListParaChk(pstIEOptParaList);
    if( NAS_EMM_FAIL == ulRslt)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEList:ERROR: some input pointer is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptList_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    /*重命名的参数初始化*/
    pTmpRcvMsg          = pstIEOptParaList->pRcvMsg;
    pTmpCnMsgOpt        = pstIEOptParaList->pCnMsgOpt;
    *pulSum             = NAS_EMM_NULL;

    /*循环解析信元*/
    while(ulIndex < pstIEOptParaList->ulLength)
    {
        ulIESum         = NAS_EMM_NULL;
        pstMsgIETable   = pstIEOptParaList->pstCnMsgInfo->pastMsgIETable;
        pstCnMsgStruIE  = pstIEOptParaList->pstCnMsgStru;
        ulIndexNoIEI    = ulIndex;
        ulTmpOptPos     = pstIEOptParaList->ulOptPos;
        ulDecodingIE    = pstIEOptParaList->ulOptPos;/*记录正在解的信元 */

        /*循环在信元信息表中查找匹配项*/
        for (i = 0; i < pstIEOptParaList->pstCnMsgInfo->ucMsgIETableSize; i++)
        {
             /*检查信元存在性*/
            ulIEI = pTmpRcvMsg[ulIndex] & pstMsgIETable->stIEInfo.ucIEBits;
            ulIEI = ulIEI >> pstMsgIETable->stIEInfo.ucIEBitsMove;

            if(pstMsgIETable->stIEInfo.ucIEI != ulIEI)
            {
                /*结构体指针、信元列表、可选项位置平移*/
                pstCnMsgStruIE = (VOS_UINT8 *)pstCnMsgStruIE
                                         + pstMsgIETable->stIEInfo.usIEStructSize;
                pstMsgIETable++;
                ulTmpOptPos++;
                ulDecodingIE = ulDecodingIE << 1;
                continue;
            }

            break;
        }
        /*无法识别收到的NAS消息中的信元,也无法知道跳过码流的长度,可选信元不影响
          正常功能,按照宽进严出原则,所以暂时按照解码成功处理 */
        if (i >= pstIEOptParaList->pstCnMsgInfo->ucMsgIETableSize)
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsgIEList:(WARN): some Option IEI in Msg is not exist!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsgIEOptList_ENUM,LNAS_FUNCTION_LABEL1);
            return NAS_EMM_SUCC;
        }

        /*计算除去IEI后的位置,计算信元长度*/
        /*lint -e961*/
        ulIndexNoIEI = ulIndexNoIEI + pstMsgIETable->stIEInfo.ucIEBits/NAS_EMM_DECODE_OCTET_USE_8_BITS;
        /*lint +961*/
        ulIELen      = pstMsgIETable->stIEInfo.ucIELen;

        /*类型中包含L的时候，长度需要重新计算出来*/
        NAS_EMM_DecodeCnMsgIEOptListCalcLen(pTmpRcvMsg,pstMsgIETable->stIEInfo,&ulIndexNoIEI,&ulIELen,&ulIndex);


        /*如果超过长度,返回成功，与原函数一致*/
        if(pstIEOptParaList->ulLength < (ulIndex + ulIELen))
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsgIEList:WARN: exceed length!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsgIEOptList_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_SUCC;
        }

        /*(1)检查函数指针是否存在,存在则解码,否则跳过*/
        /*(2)以及如果该信元之前没解到过,则执行解码，否则跳过 */
        if ((NAS_EMM_NULL != pstMsgIETable->stIEInfo.pfIEDecodeFun)
            && ((ulDecodingIE | ulDecodedIE) != ulDecodedIE))
        {

            ulRslt = pstMsgIETable->stIEInfo.pfIEDecodeFun(pTmpRcvMsg+ulIndexNoIEI,
                                                            &ulIESum,
                                                            pstCnMsgStruIE,
                                                            pstIEOptParaList->pstCnMsgInfo->ucMsgType
                                                           );
            if(NAS_EMM_FAIL == ulRslt)
            {
                /* 可选信元解码失败，当是测试卡时，返回解码失败，否则按照宽进严出原则跳过该可选信元，继续解析剩余信元 */
                if(PS_SUCC == LPS_OM_IsTestMode())
                {
                    NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEList:(ERROR): IE content error");
                    TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptList_ENUM,LNAS_ERROR);
                    return NAS_EMM_FAIL;
                }
                else
                {
                    /*跳过信元 */
                    ulIESum = ulIELen;
                    /*码流平移*/
                    ulIndex += ulIESum;
                    /*解析的总长度 */
                    *pulSum = ulIndex;
                    continue;
                }
            }

            /*填写标志位，未填写的默认为NAS_EMM_BIT_NO_SLCT*/
            ulOptBit = NAS_EMM_BIT_SLCT;

            /*记录已解信元 */
            ulDecodedIE |= (ulOptBit << (ulTmpOptPos - 1));

            NAS_EMM_DecodeCnMsgIEEdianChk(&ulTmpOptPos,NAS_EMM_MSG_IE_OPT_BITS);
            ulOptBit = NAS_EMM_BIT_SLCT;
            ulOptBit = ulOptBit << ulTmpOptPos;
            *pTmpCnMsgOpt = *pTmpCnMsgOpt | ulOptBit;

            /*码流平移*/
            ulIndex = ulIndexNoIEI + ulIESum;

        }
        else
        {
            /*跳过信元 */
            ulIESum = ulIELen;

            /*码流平移*/
            ulIndex += ulIESum;

        }
        /*解析的总长度 */
        *pulSum = ulIndex;
    }

    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnMsgIEMstListParaChk
 Description     : 指针非空的检查
 Input           : NAS_EMM_DECODE_IELIST_PARA_STRU
 Output          :
 Return          : NAS_EMM_SUCC 指针非空
 History         :
    1.s00111599      2009-10-20  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_DecodeCnMsgIEOptListParaChk(
                           NAS_EMM_DECODE_IELIST_PARA_STRU *pstIEOptParaList
                                                                   )
{
    VOS_UINT32 ulRslt;
    ulRslt = NAS_EMM_FAIL;
    if(NAS_EMM_NULL_PTR == pstIEOptParaList)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_NULL_PTR);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pRcvMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pRcvMsg is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL1);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pCnMsgOpt)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pCnMsgOpt is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL2);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pstCnMsgStru)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pstCnMsgStru is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL3);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pstCnMsgInfo)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pstCnMsgInfo is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL4);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pstCnMsgInfo->pastMsgIETable)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pstCnMsgInfo->pastMsgIETable is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL5);
        return ulRslt;
    }
    ulRslt = NAS_EMM_SUCC;
    return ulRslt;

}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnMsgIEEdianChk
 Description     : 检查字节序，并对消息可选项存储的bit位的纠正
 Input           : pulOptpos 传入存储位置
 Output          : pulOptpos 纠正存储位置
 Return          : 无
 History         :
    1. s00111599  2009-10-20    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_DecodeCnMsgIEEdianChk(

                                            VOS_UINT32  *pulOptpos,
                                            VOS_UINT8   ucOptbits
                                          )
{
    if(PS_TRUE == NAS_EMM_DecodeIsLittleEdian())
    {
        *pulOptpos = ((*pulOptpos - NAS_EMM_AD_MOVEMENT_1_BIT) % ucOptbits);
    }
    else
    {
        *pulOptpos = (ucOptbits - (*pulOptpos% ucOptbits)) ;
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_DECODE_IsLittleEdian
 Description     : 判断是否为小头
 Input           : 无
 Output          :
 Return          :返回PS_TRUE为小头； 否则为大头
 History         :
    1. s00111599  2009-10-20     Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_DecodeIsLittleEdian(VOS_VOID)
{
    NAS_EMM_DECODE_EDIAN_UION unNasEdian;
    unNasEdian.ulMember = 1;
    if(1 == unNasEdian.aucMember[0])
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnEmmCause
 Description     :    主要用于CN消息中EMM原因值的解码，
                      参考协议24301   9.9.3.9节的Table 9.9.3.9.1中所述，
                      非表中所列原因值均作为#111处理。
 Input           : VOS_UINT8
 Output          : NULL
 Return          :  NAS_EMM_CN_CAUSE_ENUM_UINT8
 History         :
    1.sunjitan 00193151      2012-06-05  Draft Enact
*****************************************************************************/
NAS_EMM_CN_CAUSE_ENUM_UINT8  NAS_EMM_DecodeCnEmmCause(VOS_UINT8  ucEMMCau)
{
    if (   ((NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS <= ucEMMCau) && (ucEMMCau <= NAS_LMM_CAUSE_ILLEGAL_UE))
        || ((NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED <= ucEMMCau) && (ucEMMCau <= NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED))
        || ((NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG <= ucEMMCau) && (ucEMMCau <= NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE))
        || (NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE == ucEMMCau))
    {
        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_GetFtmInfoCnRej() = ucEMMCau;
        #endif

        return ucEMMCau;
    }
    else
    {
        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_GetFtmInfoCnRej() = NAS_LMM_CAUSE_PROTOCOL_ERROR;
        #endif

        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_DecodeCnEmmCause: The CnEmmCause is undefine in protocol 24301 !  ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmCause_ENUM,LNAS_NO_CAUSE);
        return NAS_LMM_CAUSE_PROTOCOL_ERROR;
    }

}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnAttachAcpMsgNasMsg
 Description     :
 Input           : pRcvMsg       : 指向 LRRC_LNAS_MSG_STRU.aucNasMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-3  Draft Enact
*****************************************************************************/

VOS_UINT32  NAS_EMM_DecodeCnAttachAcpMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucEPSAttRslt        = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;
    NAS_EMM_DECODE_IELIST_PARA_STRU     stIEOptParaList={NAS_EMM_NULL};
    NAS_EMM_DECODE_MSG_INFO_STRU        stCnAttachAcp = \
                                        NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_ATTACH_ACP,\
                                                                g_astCnAttachAcpIEList,\
                                                                NAS_EMM_CN_ATTACH_ACP_STR);

    NAS_LMM_MEM_SET_S(  &stIEOptParaList,
                        sizeof(NAS_EMM_DECODE_IELIST_PARA_STRU),
                        0,
                        sizeof(NAS_EMM_DECODE_IELIST_PARA_STRU));

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    /*取出EPS attach result*/
    ucEPSAttRslt = (pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_HALF_BYTE_F);

    /*判断EPS attach result是否符合协议要求*/
    if((VOS_NULL != ucEPSAttRslt)&&(ucEPSAttRslt <= NAS_EMM_CN_ATT_RST_VAL_MAX))
    {
        pstCnMsgStruIE->uCnMsgStru.stAttAcp.ucAttachRst = ucEPSAttRslt;
    }
    else
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_ATTRSLT_IE, EMM_CN_MSG_IE_ATTRSLT_INVALID, ucEPSAttRslt);
        /*打印错误信息*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnAttachAcpMsg:WARNING:NAS->EMM MSG AttachRst not assigned ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnAttachAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*跳过EPS attach result*/
    ulIndex++;

    (VOS_VOID)NAS_EMM_DecodeTimer((pTmpRcvMsg+ulIndex),
                                 &ulSum,
                                 &(pstCnMsgStruIE->uCnMsgStru.stAttAcp.stT3412Value),
                                 NAS_EMM_CN_MT_BUTT);

    ulIndex = ulIndex + ulSum;

    /*记数器清0*/
    ulSum = NAS_EMM_NULL;

    if(NAS_EMM_FAIL == NAS_EMM_DecodeTai((pTmpRcvMsg+ulIndex),
                                         &ulSum,
                                         &(pstCnMsgStruIE->uCnMsgStru.stAttAcp.stTaiList),
                                         NAS_EMM_CN_MT_BUTT))
    {
        /*打印错误信息*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnAttachAcpMsg:WARNING:NAS->EMM MSG TAI decode error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnAttachAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL2);

        return NAS_EMM_FAIL;
    }
    /*跳过Tai*/
    ulIndex = ulIndex + ulSum;

    /*记数器清0*/
    ulSum = NAS_EMM_NULL;

    if(NAS_EMM_FAIL == NAS_EMM_DecodeMsgCon((pTmpRcvMsg+ulIndex),
                                                &ulSum,
                                                &(pstCnMsgStruIE->uCnMsgStru.stAttAcp.stMsgCon)))
    {
        /*打印错误信息*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnAttachAcpMsg:WARNING:NAS->EMM MSG MsId decode error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnAttachAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_FAIL;
    }
    /*跳过ESM message container*/
    ulIndex = ulIndex + ulSum;
    /*循环解析参数填充*/
    stIEOptParaList.pRcvMsg = pTmpRcvMsg+ulIndex;
    stIEOptParaList.ulLength = ulMsgSize-(ulIndex + ulLength);
    stIEOptParaList.pCnMsgOpt = NAS_EMM_DECODE_BUFFER_MSG_OPT(pstCnMsgStruIE);
    stIEOptParaList.ulOptPos = 1;
    stIEOptParaList.pstCnMsgStru = &(pstCnMsgStruIE->uCnMsgStru.stAttAcp.stGuti);
    stIEOptParaList.pstCnMsgInfo = &stCnAttachAcp;
    if(NAS_EMM_FAIL == NAS_EMM_DecodeCnMsgIEOptList(&stIEOptParaList,&ulSum))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnAttachAcpMsg:OPT IE Decode ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnAttachAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnAttachAcpMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnAttachAcpMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnAttachAcpMsgNasMsg( pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}


VOS_UINT32  NAS_EMM_DecodeCnAttachRejMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulRcvNwMsgLen       = NAS_EMM_NULL;
    VOS_UINT8                           ulEsmCause          = NAS_EMM_NULL;
    VOS_UINT32                          ulRet;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    NAS_EMM_DECODE_IELIST_PARA_STRU     stIEOptParaList={NAS_EMM_NULL};
    NAS_EMM_DECODE_MSG_INFO_STRU        stCnAttachRej = \
                                        NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_ATTACH_REJ,\
                                                                g_astCnAttachRejIEList,\
                                                                NAS_EMM_CN_ATTACH_REJ_STR);

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    /* 协议24301   9.9.3.9节的Table 9.9.3.9.1中所述，非表中所列原因值均作为#111处理 */
    /*存放EMM cause*/
    pstCnMsgStruIE->uCnMsgStru.stAttRej.ucCause = NAS_EMM_DecodeCnEmmCause(pTmpRcvMsg[ulIndex]);

    /*跳过EMM cause*/
    ulIndex++;

    if (NAS_RELEASE_R11)
    {
        /*已解码的消息长度和发过来的消息长度作比较，判断解码是否结束*/
        if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
        {
            return NAS_EMM_SUCC;
        }
        /*循环解析参数填充*/
        stIEOptParaList.pRcvMsg = pTmpRcvMsg+ulIndex;
        stIEOptParaList.ulLength = ulMsgSize-(ulIndex + ulLength);
        stIEOptParaList.pCnMsgOpt = NAS_EMM_DECODE_BUFFER_MSG_OPT(pstCnMsgStruIE);
        stIEOptParaList.ulOptPos = 1;
        stIEOptParaList.pstCnMsgStru = &(pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon);
        stIEOptParaList.pstCnMsgInfo = &stCnAttachRej;
        if(NAS_EMM_FAIL == NAS_EMM_DecodeCnMsgIEOptList(&stIEOptParaList,&ulSum))
        {
            NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnAttachRejMsg:OPT IE Decode ERR!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnAttachRejMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
            return NAS_EMM_FAIL;
        }

        if(NAS_EMM_BIT_SLCT == pstCnMsgStruIE->uCnMsgStru.stAttRej.ucBitOpMsgCon)
        {
            /*解码ESM Cause*/
            ulRcvNwMsgLen = pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon.ulMsgLen;
            ulRet = NAS_ESM_DecodeNwEsmMsgGetEsmCause((VOS_UINT8  *)(pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon.aucMsg), ulRcvNwMsgLen, &ulEsmCause);
            if(NAS_EMM_SUCC == ulRet)
            {
                pstCnMsgStru->uCnMsgStru.stAttRej.ucEsmCause = ulEsmCause;
            }
        }
    }
    else
    {
        /*如果消息的总长度大于已经接的加上消息头长度加上1，表明至少有TL或者TV，则继续解码可选信元*/
         while(ulMsgSize >= (ulIndex + ulLength + 1))
         {
             if(NAS_EMM_MSG_CON_IEI == pTmpRcvMsg[ulIndex])
             {
                  /*判断是否超长*/
                 if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
                 {
                     return NAS_EMM_SUCC;
                 }

                /*跳过ESM message container字节*/
                ulIndex++;

                 if(NAS_EMM_FAIL == NAS_EMM_DecodeMsgCon((pTmpRcvMsg+ulIndex),
                                                         &ulSum,
                                                         &(pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon)))
                 {

                     NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnAttachAcpMsg:WARNING:NAS->EMM MSG MsId decode error!");
                     TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnAttachRejMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL2);
                     return NAS_EMM_FAIL;
                 }

                 pstCnMsgStruIE->uCnMsgStru.stAttRej.ucBitOpMsgCon = NAS_EMM_BIT_SLCT;
                 ulRcvNwMsgLen = pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon.ulMsgLen;
                 ulRet = NAS_ESM_DecodeNwEsmMsgGetEsmCause((VOS_UINT8  *)(pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon.aucMsg), ulRcvNwMsgLen, &ulEsmCause);
                 if(NAS_EMM_SUCC == ulRet)
                 {
                     pstCnMsgStru->uCnMsgStru.stAttRej.ucEsmCause = ulEsmCause;
                 }
                 /*跳过ESM message container*/

                 ulIndex += ulSum;
             }
             else if(NAS_EMM_MSG_T3346_IEI == pTmpRcvMsg[ulIndex])
             {
                 /*判断是否超长*/
                 if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
                 {
                     return NAS_EMM_SUCC;
                 }

                 /*这里暂时跳过，不解码*/
                 ulIndex += 3;
             }
             else if(NAS_EMM_MSG_EXT_3402_IEI == pTmpRcvMsg[ulIndex])
             {
                 /*判断是否超长*/
                 if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
                 {
                     return NAS_EMM_SUCC;
                 }

                 /*这里暂时跳过，不解码*/
                 ulIndex += 3;
             }
             else if(NAS_EMM_MSG_EXTENDED_EMM_CAUSE == ((pTmpRcvMsg[ulIndex])& NAS_EMM_CN_HIGH_4_BIT))
             {
                 pstCnMsgStruIE->uCnMsgStru.stAttRej.ucBitOpExtCause = NAS_EMM_BIT_SLCT;
                 pstCnMsgStruIE->uCnMsgStru.stAttRej.ucExtendedEmmCause = (pTmpRcvMsg[ulIndex]) & 0x01;
                 ulIndex++;
             }
             else
             {
                 return NAS_EMM_SUCC;
             }
         }

    }

    return NAS_EMM_SUCC;
}



/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnAttachRejMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnAttachRejMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnAttachRejMsgNasMsg( pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnDetachAcpMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnDetachAcpMsg(
                                        LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    /*保存消息类型*/
    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnDetachReqMsgNasMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnDetachReqMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucDetachType        = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    ucDetachType = pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_HALF_BYTE_F;
    if((NAS_EMM_DETACH_TYPE_MT_REATTACH != ucDetachType)
        &&(NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH != ucDetachType)
        &&(NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH != ucDetachType)
        &&(NAS_EMM_DETACH_TYPE_MT_RESERVED1 != ucDetachType)
        &&(NAS_EMM_DETACH_TYPE_MT_RESERVED2 != ucDetachType))
    {
        ucDetachType = NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH;
    }
    pstCnMsgStruIE->uCnMsgStru.stDetachReq.ucDetType = ucDetachType;

    /*跳过ucDetachType*/
    ulIndex++;

    /*已解码的消息长度和发过来的消息长度作比较，判断解码是否结束*/
    if(ulMsgSize < (ulIndex + ulLength + 2))
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_EMM_MSG_EMMCAU_IEI == pTmpRcvMsg[ulIndex])
    {
        pstCnMsgStruIE->uCnMsgStru.stDetachReq.ucBitOpCause = NAS_EMM_BIT_SLCT;

        /*跳过IEI*/
        ulIndex++;

        pstCnMsgStruIE->uCnMsgStru.stDetachReq.ucEmmCause = NAS_EMM_DecodeCnEmmCause(pTmpRcvMsg[ulIndex]);
    }

    return NAS_EMM_SUCC;
}



/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnDetachReqMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnDetachReqMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;
    NAS_EMM_DETACH_TYPE_MT_ENUM_UINT8   ucCnDetType;

    ulRet = NAS_EMM_DecodeCnDetachReqMsgNasMsg( pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);
    /*如果是网侧DETACH的类型是RESERVED1,RESERVED2，目前作为
      REATTACH-NOT-REQUIRED类型处理，为了保证容易扩展，暂时不进入状态机处理*/
    ucCnDetType = pstCnMsgStru->uCnMsgStru.stDetachReq.ucDetType;
    if((NAS_EMM_DETACH_TYPE_MT_RESERVED1 == ucCnDetType)
      ||(NAS_EMM_DETACH_TYPE_MT_RESERVED2 == ucCnDetType))
    {
        pstCnMsgStru->uCnMsgStru.stDetachReq.ucDetType = NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH;
    }

    return ulRet;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnGUTICmdMsgNasMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnGUTICmdMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    /*GUTI是必选参数*/
    if(NAS_EMM_FAIL == NAS_EMM_DecodeGuti((pTmpRcvMsg+ulIndex),
                                         &ulSum,
                                         &(pstCnMsgStruIE->uCnMsgStru.stGutiReaCmd.stGuti),
                                         NAS_EMM_CN_MT_BUTT))
    {
        /*打印错误信息*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnGUTICmdMsg:WARNING:NAS->EMM MSG GUTI decode error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnGUTICmdMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*跳过GUTI*/
    ulIndex = ulIndex + ulSum;

    /*已解码的消息长度和发过来的消息长度作比较，判断解码是否结束*/
    if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
    {
        return NAS_EMM_SUCC;
    }

    /*判断TAI是否存在*/
    if(NAS_EMM_MSG_TAI_IEI == pTmpRcvMsg[ulIndex])
    {
        /*跳过TAI IEI字节*/
        ulIndex++;

        /*记数器清0*/
        ulSum = NAS_EMM_NULL;

        if(NAS_EMM_FAIL == NAS_EMM_DecodeTai((pTmpRcvMsg+ulIndex),
                                            &ulSum,
                                            &(pstCnMsgStruIE->uCnMsgStru.stGutiReaCmd.stTaiList),
                                            NAS_EMM_CN_MT_BUTT))
        {
            /* 可选信元解码失败，当是测试卡时，返回解码失败，否则按照宽进严出原则返回解码成功 */
            if(PS_SUCC == LPS_OM_IsTestMode())
            {
                /*打印错误信息*/
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnGUTICmdMsg:WARNING:NAS->EMM MSG TAI decode error!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnGUTICmdMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL2);
                return NAS_EMM_FAIL;
            }
            else
            {
                return NAS_EMM_SUCC;
            }
        }

        pstCnMsgStruIE->uCnMsgStru.stGutiReaCmd.ucBitOpTaiList = NAS_EMM_BIT_SLCT;

        /*跳过TAI*/
    }

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnGUTICmdMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.n00108792      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnGUTICmdMsg(LRRC_LNAS_MSG_STRU            *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnGUTICmdMsgNasMsg(   pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnIdenReqMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.n00108792      2008-9-28  Draft Enact
    2.zhengjunyan 00148421 2009.03.03 问题单BA8D01054
    描述:type of identity的判断条件
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnIdenReqMsg(
                                    LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                    VOS_UINT32                  ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ulTypeId            = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    /*保存消息类型*/
    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    /*取出type of identity*/
    ulTypeId = pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_3_BITS_F;

    /*保存type of identity:24008-930 10.5.5.9 取值范围[0,7],非1,2,3,4的值作为IMSI处理*/
    pstCnMsgStruIE->uCnMsgStru.stIdenReq.ucIdenType = ulTypeId;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnSerRejMsgNasMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnSerRejMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;

    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    pstCnMsgStruIE->uCnMsgStru.stSerRej.ucEMMCause = NAS_EMM_DecodeCnEmmCause(pTmpRcvMsg[ulIndex]);

    ulIndex++;

    /*已解码的消息长度和发过来的消息长度作比较，判断解码是否结束*/
    if(ulMsgSize < (ulIndex + ulLength + 2))
    {
        return NAS_EMM_SUCC;
    }

    /*判断T3442是否存在*/
    if(NAS_EMM_MSG_T3442_IEI == pTmpRcvMsg[ulIndex])
    {
        pstCnMsgStruIE->uCnMsgStru.stSerRej.ucBitOpT3442 = NAS_EMM_BIT_SLCT;

        /*跳过T3442 IEI字节*/
        ulIndex++;

        (VOS_VOID)NAS_EMM_DecodeTimer((pTmpRcvMsg+ulIndex),
                                         &ulSum,
                                         &(pstCnMsgStruIE->uCnMsgStru.stSerRej.stT3442),
                                         NAS_EMM_CN_MT_BUTT);

    }

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnSerRejMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.n00108792      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnSerRejMsg(LRRC_LNAS_MSG_STRU             *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnSerRejMsgNasMsg(    pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}
/*****************************************************************************
 Function Name   : NAS_EMM_VerifyEpsUpdateRslt
 Description     : 验证EPS Update Result信元是否合法

                   0   0   0       TA updated
                   0   0   1       combined TA/LA updated
                   1   0   0       TA updated and ISR activated (NOTE)
                   1   0   1       combined TA/LA updated and ISR activated (NOTE)
                   All other values are reserved

 Input           : ucEPSUpdateRslt----------EPS Update Result
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-08-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_VerifyEpsUpdateRslt
(
    VOS_UINT8                           ucEPSUpdateRslt
)
{
    if (NAS_EMM_EPS_UPDATE_RST_TA_UPDATED == ucEPSUpdateRslt)
    {
        return NAS_EMM_SUCC;
    }

    if (NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED == ucEPSUpdateRslt)
    {
        return NAS_EMM_SUCC;
    }

    if (NAS_EMM_EPS_UPDATE_RST_TA_UPDATED_AND_ISR == ucEPSUpdateRslt)
    {
        return NAS_EMM_SUCC;
    }

    if (NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED_AND_ISR == ucEPSUpdateRslt)
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnTAUAcpMsgNasMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-3  Draft Enact
    2.lining 00141619        2009-7-10     2009Q1协议刷新
      CR39--Security and inter RAT mobility to E-UTRAN
      新增解析可选信元NAS key set identifierASME
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnTAUAcpMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucEPSUpdateRslt     = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;
    NAS_EMM_DECODE_MSG_INFO_STRU        stCnTauAcp = \
                                        NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_TAU_ACP,\
                                                                g_astCnTauAcpIEList,\
                                                                NAS_EMM_CN_TAU_ACP_STR);
    NAS_EMM_DECODE_IELIST_PARA_STRU     stIEOptParaList = {NAS_EMM_NULL};

    NAS_LMM_MEM_SET_S(  &stIEOptParaList,
                        sizeof(NAS_EMM_DECODE_IELIST_PARA_STRU),
                        0,
                        sizeof(NAS_EMM_DECODE_IELIST_PARA_STRU));


    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    /*取出EPS attach result*/
    ucEPSUpdateRslt = pTmpRcvMsg[ulIndex]&NAS_EMM_LOW_3_BITS_F;

    /*判断EPS update result是否符合协议要求*/
    if(NAS_EMM_SUCC == NAS_EMM_VerifyEpsUpdateRslt(ucEPSUpdateRslt))
    {
        pstCnMsgStruIE->uCnMsgStru.stTauAcp.ucEPSupdataRst = ucEPSUpdateRslt;
    }
    else
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_TAURSLT_IE, EMM_CN_MSG_IE_TAURSLT_INVALID, ucEPSUpdateRslt);
        /*打印错误信息*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnTAUAcpMsg:WARNING:NAS->EMM MSG update Rslt not assigned ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnTAUAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*跳过EPS update result*/
    ulIndex++;

    /*循环解析参数填充*/
    stIEOptParaList.pRcvMsg = pTmpRcvMsg+ulIndex;
    stIEOptParaList.ulLength = ulMsgSize-( ulIndex + ulLength );
    stIEOptParaList.pCnMsgOpt = NAS_EMM_DECODE_BUFFER_MSG_OPT(pstCnMsgStruIE);
    stIEOptParaList.ulOptPos = 1;
    stIEOptParaList.pstCnMsgStru = &(pstCnMsgStruIE->uCnMsgStru.stTauAcp.stT3412);
    stIEOptParaList.pstCnMsgInfo = &stCnTauAcp;
    if(NAS_EMM_FAIL == NAS_EMM_DecodeCnMsgIEOptList(&stIEOptParaList,&ulSum))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnTAUAcpMsg:OPT IE Decode ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnTAUAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnTAUAcpMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.n00108792      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnTAUAcpMsg(LRRC_LNAS_MSG_STRU             *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnTAUAcpMsgNasMsg(    pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnTAURejMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.n00108792      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnTAURejMsg(
                                    LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                    VOS_UINT32                  ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;

    NAS_EMM_CN_MSG_STRU   *pstCnMsgStruIE  = pstCnMsgStru;

    /*保存消息类型*/
    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg =  pRcvMsg->aucNasMsg + ulLength;
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    pstCnMsgStruIE->uCnMsgStru.stTauRej.ucEMMCause = NAS_EMM_DecodeCnEmmCause(pTmpRcvMsg[ulIndex]);

    /*跳过EMM cause*/
    ulIndex++;

    /*如果消息的总长度大于已经接的加上消息头长度加上1，表明至少有TL或者TV，则继续解码可选信元*/
    while(ulMsgSize >= (ulIndex + ulLength + 1))
    {
        if(NAS_EMM_MSG_T3346_IEI == pTmpRcvMsg[ulIndex])
        {
            /*判断是否超长*/
            if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
            {
                return NAS_EMM_SUCC;
            }

            /*跳过T3346字节*/
            ulIndex++;

            if(NAS_EMM_FAIL == NAS_EMM_DecodeTimer2((pTmpRcvMsg+ulIndex),
                                                        &ulSum,
                                                        &(pstCnMsgStruIE->uCnMsgStru.stTauRej.stT3346),
                                                        NAS_EMM_CN_MT_TAU_REJ))
            {
                /*打印错误信息*/
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnTAURejMsg:WARNING:NAS->EMM MSG MsId decode error!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnTAURejMsg_ENUM,LNAS_FUNCTION_LABEL1);
                return NAS_EMM_SUCC;
            }
            /* 如果网侧携带T3346,但是时长为0，则不认为网侧携带了T3346 */
            /* 24304 5.5.1.2.5 If the T3346 value IE is present in the ATTACH REJECT message and the
            value indicates that this timer is neither zero nor deactivated,*/
            if ((0 != pstCnMsgStruIE->uCnMsgStru.stTauRej.stT3346.ucTimerVal) &&
                (NAS_EMM_TIMER_DEACTIVATE != pstCnMsgStruIE->uCnMsgStru.stTauRej.stT3346.ucUnit))
            {
                pstCnMsgStruIE->uCnMsgStru.stTauRej.ucBitOpT3346 = NAS_EMM_BIT_SLCT;
            }

            /*跳过当前3346的解码字节*/
            ulIndex += ulSum;
        }
        else if(NAS_EMM_MSG_EXTENDED_EMM_CAUSE == ((pTmpRcvMsg[ulIndex])& NAS_EMM_CN_HIGH_4_BIT))
        {
            pstCnMsgStruIE->uCnMsgStru.stTauRej.ucBitOpExtCause = NAS_EMM_BIT_SLCT;
            pstCnMsgStruIE->uCnMsgStru.stTauRej.ucEmmExtCause = (pTmpRcvMsg[ulIndex]) & 0x01;
            ulIndex++;
        }
        else
        {
            return NAS_EMM_SUCC;
        }
    }
    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnAuthReqMsgNasMsg
 Description     :
 Input           : LRRC_LNAS_MSG_STRU                    *pRcvMsg
                   VOS_UINT8                           *pucRcvCnNasMsg
                   VOS_UINT32                          ulLength
                   NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian      2009-4-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnAuthReqMsgNasMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT8                           *pucRcvCnNasMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    (VOS_VOID)pRcvMsg;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_DecodeCnAuthReqMsgNasMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnAuthReqMsgNasMsg_ENUM,LNAS_ENTRY);

    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

     /*跳过消息类型*/
    ulIndex++;

    /* 取KSI位 */
    pstCnMsgStruIE->uCnMsgStru.stAuthReq.ucKsi = pTmpRcvMsg[ulIndex++];

    /* 取Rand */
    NAS_LMM_MEM_CPY_S(  pstCnMsgStruIE->uCnMsgStru.stAuthReq.aucRand,
                        NAS_EMM_RAND_LEN,
                        &pTmpRcvMsg[ulIndex],
                        NAS_EMM_SECU_AUTH_RAND_LEN);

    ulIndex                             += NAS_EMM_SECU_AUTH_RAND_LEN;

    /*取auth的长度*/
    pstCnMsgStruIE->uCnMsgStru.stAuthReq.ulAutnLen = pTmpRcvMsg[ulIndex];

    /* 跳过autn长度 */
    ulIndex++;

    /* 取Auth */
    NAS_LMM_MEM_CPY_S(  pstCnMsgStruIE->uCnMsgStru.stAuthReq.aucAutn,
                        NAS_EMM_AUTN_LEN,
                        &pTmpRcvMsg[ulIndex],
                        pstCnMsgStruIE->uCnMsgStru.stAuthReq.ulAutnLen);

    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnAuthReqMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.liuwenyu 00143951      2008-9-28  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnAuthReqMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnAuthReqMsgNasMsg( pRcvMsg,
                                              pRcvMsg->aucNasMsg,
                                              ulLength,
                                              pstCnMsgStru);

    return ulRet;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnAuthRejMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.liuwenyu 00143951      2008-9-28  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnAuthRejMsg(
                                    LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                    VOS_UINT32                  ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    /* 不需要解析了,只有头部 */

    (VOS_VOID)ulLength;
    (VOS_VOID)pRcvMsg;
    (VOS_VOID)pstCnMsgStru;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.liuwenyu 00143951      2008-9-28  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT8                           *pucRcvCnNasMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucImeisvIei         = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_PUBU_LOG_INFO( "NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg_ENUM,LNAS_ENTRY);
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    /* 取 security algorithms */
    pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.ucSelAlgrthm
                                        = pTmpRcvMsg[ulIndex++];

    /* 取EPS的KSI */
    pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.ucKSIasme
                                        = pTmpRcvMsg[ulIndex++] & NAS_EMM_LOW_3_BITS_F;

    /* 取UE的安全能力 */
    pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.stReSecurityCapa.ucLen
                                        = pTmpRcvMsg[ulIndex++];
    pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.stReSecurityCapa.pucValue
                                        = &pTmpRcvMsg[ulIndex];

    ulIndex += pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.stReSecurityCapa.ucLen;

    if(ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    ucImeisvIei = (pTmpRcvMsg[ulIndex] & NAS_EMM_HIGH_HALF_BYTE_F) >> NAS_EMM_MOVEMENT_4_BITS;

    if(NAS_EMM_MSG_KSI_IMEISV_IEI == ucImeisvIei)
    {
        /* 取是否需要Imeisv */
        pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.ucImeisvRsq = pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_3_BITS_F;
    }
    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnSecurModeCtrlMsg
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pstCnMsgStru
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.liuwenyu 00143951      2008-9-28  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnSecurModeCtrlMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg( pRcvMsg,
                                              pRcvMsg->aucNasMsg,
                                              ulLength,
                                              pstCnMsgStru);

    return ulRet;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeType1Tai
 Description     : 译码类型为010的TA List
 Input           : VOS_UINT32 *pulTaiLength
                   VOS_UINT32  ulTaiNumSum
                   VOS_UINT8  *pucTmpMsg
                   NAS_EMM_TA_LIST_STRU   *pstTaiStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00135146      2009-10-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_DecodeType1Tai(VOS_UINT32 *pulTaiLength,
                                        VOS_UINT32  ulTaiNumSum,
                                        VOS_UINT8  *pucTaiInfo,
                                        NAS_EMM_TA_LIST_STRU   *pstTaiStru
)
{
    VOS_UINT8                          *pucTmpMsg           = pucTaiInfo;
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiNum            = NAS_EMM_NULL;
    VOS_UINT32                          ulTotalTaiNum       = ulTaiNumSum;
    VOS_UINT32                          ulRst;
    NAS_MM_TA_STRU                      stTmpTa;
    NAS_EMM_TA_LIST_STRU               *pstTmpTaiStru       = pstTaiStru;

    /*取出Tai个数,00000对应1，所以应该+1*/
    ulTaiNum  = ((VOS_UINT32)(pucTmpMsg[ulSum]&NAS_EMM_CN_LOW_5_BIT))+1;

    /*跳过TAI个数*/
    ulSum++;

    stTmpTa.stPlmnId.aucPlmnId[0] = pucTmpMsg[ulSum++];
    stTmpTa.stPlmnId.aucPlmnId[1] = pucTmpMsg[ulSum++];
    stTmpTa.stPlmnId.aucPlmnId[2] = pucTmpMsg[ulSum++];
    stTmpTa.stTac.ucTac = pucTmpMsg[ulSum++];
    stTmpTa.stTac.ucTacCnt = pucTmpMsg[ulSum++];

    for(i = 0; i < ulTaiNum;i++)
    {
        NAS_LMM_PlmnCpy( &(pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId),
                        &(stTmpTa.stPlmnId));
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTac
            = stTmpTa.stTac.ucTac;
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTacCnt
            = stTmpTa.stTac.ucTacCnt;

        ulRst = NAS_LMM_TaIncrease(&stTmpTa.stTac);
        if(NAS_LMM_SUCC != ulRst)
        {
            NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeType1Tai: NAS_LMM_TaIncrease error!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeType1Tai_ENUM,LNAS_FUNCTION_LABEL1);
        }

        ulTotalTaiNum++;

        if (ulTotalTaiNum >= NAS_EMM_TA_MAX_TAC_MUN)
        {
            break;
        }
    }

    *pulTaiLength = ulSum;

    return (ulTotalTaiNum - ulTaiNumSum);
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeType0Tai
 Description     : 译码类型为000的TA List
 Input           : VOS_UINT32 *pulTaiLength
                   VOS_UINT32  ulTaiNumSum
                   VOS_UINT8  *pucTmpMsg
                   NAS_EMM_TA_LIST_STRU   *pstTaiStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00135146      2009-10-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_DecodeType0Tai(VOS_UINT32 *pulTaiLength,
                                        VOS_UINT32  ulTaiNumSum,
                                        VOS_UINT8  *pucTaiInfo,
                                        NAS_EMM_TA_LIST_STRU   *pstTaiStru
)
{
    VOS_UINT8                          *pucTmpMsg           = pucTaiInfo;
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiNum            = NAS_EMM_NULL;
    VOS_UINT32                          ulTotalTaiNum       = ulTaiNumSum;
    NAS_MM_TA_STRU                      stTmpTa;
    NAS_EMM_TA_LIST_STRU               *pstTmpTaiStru       = pstTaiStru;

    /*取出Tai个数,00000对应1，所以应该+1*/
    ulTaiNum  = ((VOS_UINT32)(pucTmpMsg[ulSum]&NAS_EMM_CN_LOW_5_BIT))+1;

    /*跳过TAI个数*/
    ulSum++;

    stTmpTa.stPlmnId.aucPlmnId[0] = pucTmpMsg[ulSum++];
    stTmpTa.stPlmnId.aucPlmnId[1] = pucTmpMsg[ulSum++];
    stTmpTa.stPlmnId.aucPlmnId[2] = pucTmpMsg[ulSum++];

    for(i = 0; i < ulTaiNum;i++)
    {
        NAS_LMM_PlmnCpy( &(pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId),
                        &(stTmpTa.stPlmnId));

        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTac
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTacCnt
            = pucTmpMsg[ulSum++];

        ulTotalTaiNum++;

        if (ulTotalTaiNum >= NAS_EMM_TA_MAX_TAC_MUN)
        {
            break;
        }
    }

    *pulTaiLength = ulSum;

    return (ulTotalTaiNum - ulTaiNumSum);
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeType2Tai
 Description     : 译码类型为010的TA List
 Input           : VOS_UINT32 *pulTaiLength
                   VOS_UINT32  ulTaiNumSum
                   VOS_UINT8  *pucTmpMsg
                   NAS_EMM_TA_LIST_STRU   *pstTaiStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00135146      2009-10-12  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_DecodeType2Tai(VOS_UINT32 *pulTaiLength,
                                        VOS_UINT32  ulTaiNumSum,
                                        VOS_UINT8  *pucTaiInfo,
                                        NAS_EMM_TA_LIST_STRU   *pstTaiStru
)
{
    VOS_UINT8                          *pucTmpMsg           = pucTaiInfo;
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiNum            = NAS_EMM_NULL;
    VOS_UINT32                          ulTotalTaiNum       = ulTaiNumSum;
    NAS_EMM_TA_LIST_STRU               *pstTmpTaiStru       = pstTaiStru;

    /*取出Tai个数,00000对应1，所以应该+1*/
    ulTaiNum  = ((VOS_UINT32)(pucTmpMsg[ulSum]&NAS_EMM_CN_LOW_5_BIT))+1;

    /*跳过TAI个数*/
    ulSum++;

    for(i = 0; i < ulTaiNum;i++)
    {
        pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId.aucPlmnId[0]
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId.aucPlmnId[1]
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId.aucPlmnId[2]
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTac
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTacCnt
            = pucTmpMsg[ulSum++];

        ulTotalTaiNum++;

        if (ulTotalTaiNum >= NAS_EMM_TA_MAX_TAC_MUN)
        {
            break;
        }
    }

    *pulTaiLength = ulSum;

    return (ulTotalTaiNum - ulTaiNumSum);
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeTai
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pulIndex
                   pstTaiStru
                   enMsgTp
 Output          : pstTaiStru pulIndex
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact
    2.y00135146   2009-10-10 Modify  BN8D01126 修改内容:NAS圈复杂度优化

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeTai(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstTaiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiLength         = NAS_EMM_NULL;
    VOS_UINT32                          ulIeLen             = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiNum            = NAS_EMM_NULL;
    VOS_UINT32                          ulTotalTaiNum       = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    VOS_UINT8                           ucListType          = NAS_EMM_NULL;
    NAS_EMM_TA_LIST_STRU               *pstTmpTaiStru       = (NAS_EMM_TA_LIST_STRU *)pstTaiStru;

    (VOS_VOID)enMsgTp;


    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeTai:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeTai_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*传入第一个参数为TAI长度，检查长度*/
    ulIeLen = pucTmpMsg[ulSum];

    if((NAS_EMM_CN_MAX_TAI_LIST_LEN < ulIeLen )||(NAS_EMM_CN_MIN_TAI_LIST_LEN > ulIeLen))
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_TAI_IE, EMM_CN_MSG_IE_LEN_INVALID, ulIeLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeTai:ERROR:TAI list length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeTai_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*跳过TAI长度*/
    ulSum++;

    pstTmpTaiStru->ulTaNum = 0;

    /*指向TA List的首地址*/
    pucTmpMsg = pucTmpMsg + ulSum;

    while(ulSum < ulIeLen)
    {
        pucTmpMsg = pucTmpMsg + ulTaiLength;

        /*取出Type of list*/
        ucListType = (VOS_UINT8)((pucTmpMsg[0]&NAS_EMM_CN_HIGH_3_BIT)
                    >>NAS_EMM_MOVEMENT_5_BITS);

        if (ulTotalTaiNum >= NAS_EMM_TA_MAX_TAC_MUN)
        {
            break;
        }

        /*根据Type of list存储TAC*/
        if((NAS_EMM_TA_LIST_1 == ucListType))
        {
            ulTaiNum = NAS_EMM_DecodeType1Tai(&ulTaiLength,ulTotalTaiNum,pucTmpMsg,pstTaiStru);
        }
        else if(NAS_EMM_TA_LIST_0 == ucListType)
        {
            ulTaiNum = NAS_EMM_DecodeType0Tai(&ulTaiLength,ulTotalTaiNum,pucTmpMsg,pstTaiStru);
        }
        else if(NAS_EMM_TA_LIST_2 == ucListType)
        {
            ulTaiNum = NAS_EMM_DecodeType2Tai(&ulTaiLength,ulTotalTaiNum,pucTmpMsg,pstTaiStru);
        }
        else
        {
            /* 抛出可维可测 */
            NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_TAI_IE, EMM_CN_MSG_IE_TAILIST_TYPE_INVALID, ucListType);
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeTai:ERROR:TAI list decode error!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeTai_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_FAIL;
        }

        ulSum = ulSum + ulTaiLength;
        ulTotalTaiNum = ulTotalTaiNum + ulTaiNum;
    }

    pstTmpTaiStru->ulTaNum = ulTotalTaiNum;

    /*记录长度*/
    *pulIndex = ulIeLen + 1;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeGuti
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pulIndex
                   pstGutiStru
                   enMsgTp
 Output          : pstGutiStru pulIndex
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/

VOS_UINT32  NAS_EMM_DecodeGuti(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstGutiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulGutiLen           = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    VOS_UINT8                           ucEPSIdType         = NAS_EMM_NULL;
    NAS_EMM_GUTI_STRU                  *pstTmpGutiStru      = (NAS_EMM_GUTI_STRU *)pstGutiStru;

    (VOS_VOID)enMsgTp;


    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeTai:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeGuti_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*传入第一个参数为Guti长度，检查长度*/
    if((NAS_EMM_NULL == pucTmpMsg[ulSum])
        ||(pucTmpMsg[ulSum] > NAS_EMM_CN_GUTI_MAX_LEN))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeGuti:ERROR:Guti length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeGuti_ENUM,LNAS_FUNCTION_LABEL1);
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_GUTI_IE, EMM_CN_MSG_IE_LEN_INVALID, pucTmpMsg[ulSum]);
        return NAS_EMM_FAIL;
    }
    else
    {
        /*保存GUTI内容长度*/
        ulGutiLen = pucTmpMsg[ulSum];
        pstTmpGutiStru->stGutiHead.ucLenth = (VOS_UINT8)ulGutiLen;
    }

    /*跳过长度*/
    ulSum++;

    /*第3字节低3为EPSIdType*/
    ucEPSIdType = pucTmpMsg[ulSum] & NAS_EMM_LOW_3_BITS_F;

    if(NAS_EMM_CN_EPS_TYPE_GUTI == ucEPSIdType)
    {
        /*保存ucOeToi*/
        pstTmpGutiStru->stGutiHead.ucOeToi = pucTmpMsg[ulSum++];

        /*保存PLMN*/
        pstTmpGutiStru->stPlmnId.aucPlmnId[0] = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stPlmnId.aucPlmnId[1] = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stPlmnId.aucPlmnId[2] = pucTmpMsg[ulSum++];

        /*保存Group ID*/
        pstTmpGutiStru->stMmeGroupId.ucGroupId = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stMmeGroupId.ucGroupIdCnt = pucTmpMsg[ulSum++];

        /*保存MME Code*/
        pstTmpGutiStru->stMmeCode.ucMmeCode = pucTmpMsg[ulSum++];

        /*保存M-TMSI*/
        pstTmpGutiStru->stMTmsi.ucMTmsi = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stMTmsi.ucMTmsiCnt1 = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stMTmsi.ucMTmsiCnt2 = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stMTmsi.ucMTmsiCnt3 = pucTmpMsg[ulSum++];
    }
    else
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_GUTI_IE, EMM_CN_MSG_IE_TYPE_INVALID, ucEPSIdType);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeGuti:ERROR:GUTI error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeGuti_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }

    /*记录长度*/
    *pulIndex = ulSum;
    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeLai
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   pulIndex
                   pstLaiStru
                   enMsgTp
 Output          : pstLaiStru pulIndex
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeLai(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstLaiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    NAS_EMM_LA_STRU                    *pstTmpLaiStru       = (NAS_EMM_LA_STRU *)pstLaiStru;


    (VOS_VOID)enMsgTp;

    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeLai:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeLai_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    pstTmpLaiStru->stPlmnId.aucPlmnId[0] = pucTmpMsg[ulSum++];
    pstTmpLaiStru->stPlmnId.aucPlmnId[1] = pucTmpMsg[ulSum++];
    pstTmpLaiStru->stPlmnId.aucPlmnId[2] = pucTmpMsg[ulSum++];
    pstTmpLaiStru->stLac.ucLac    = pucTmpMsg[ulSum++];
    pstTmpLaiStru->stLac.ucLacCnt = pucTmpMsg[ulSum++];

    /*记录长度*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeMsId
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   ulIndex
                   pstMsIdStru
                   enMsgTp
 Output          : pstMsIdStru ulIndex
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact
    2.z00148421   2011-3-01  DTS201102220339:V1R1版本不关心 MS Identity 信元，只
                             验证信元长度合法性，不解析内容
*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeMsId(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstMsIdStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulMsIdLen           = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;

    NAS_EMM_MSID_STRU                  *pstTmpMsIdStru      = (NAS_EMM_MSID_STRU  *)pstMsIdStru;

    (VOS_VOID)enMsgTp;


    /*取出长度*/
    ulMsIdLen = pucTmpMsg[0];

    /*判断长度是否符合协议*/
    if((ulMsIdLen < NAS_EMM_CN_MSID_MIN_LEN)
        ||(ulMsIdLen > NAS_EMM_CN_MSID_MAX_LEN))
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_MSID_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsIdLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeMsId:WARNING:Length Err. ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeMsId_ENUM,LNAS_ERROR);
        return NAS_EMM_FAIL;
    }

    NAS_LMM_MEM_CPY_S(pstTmpMsIdStru->aucMsId,NAS_MM_MAX_MSID_SIZE,pucTmpMsg,(ulMsIdLen+1));


    /*记录长度*/
    *pulIndex = ulMsIdLen + 1;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodePlmnList
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   ulIndex
                   pstPlmnListStru
                   enMsgTp
 Output          : pstPlmnListStru pulIndex
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/

VOS_UINT32  NAS_EMM_DecodePlmnList(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstPlmnListStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulPlmnLen           = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    NAS_EMM_PLMN_LIST_STRU             *pstTmpPlmnListStru  = (NAS_EMM_PLMN_LIST_STRU *)pstPlmnListStru;

    (VOS_VOID)enMsgTp;

    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodePlmnList:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodePlmnList_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*取出长度*/
    ulPlmnLen = pucTmpMsg[ulSum];

    /*判断长度是否符合协议*/
    if((ulPlmnLen < NAS_EMM_CN_PLMNLIST_MIN_LEN)||(ulPlmnLen > NAS_EMM_CN_PLMNLIST_MAX_LEN))
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_PLMNLIST_IE, EMM_CN_MSG_IE_LEN_INVALID, ulPlmnLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodePlmnList:ERROR:Eplmn List length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodePlmnList_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*由于PLMN固定长度为3，可得到PLMN个数*/
    if(NAS_EMM_NULL != (ulPlmnLen%NAS_EMM_CN_PLMNLIST_MIN_LEN))
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_PLMNLIST_IE, EMM_CN_MSG_IE_LEN_INVALID, ulPlmnLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodePlmnList:ERROR:Eplmn List length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodePlmnList_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
    else
    {
        pstTmpPlmnListStru->ulPlmnNum = ulPlmnLen/NAS_EMM_CN_PLMNLIST_MIN_LEN;
    }

    /*跳过长度*/
    ulSum++;

    for(i = 0; i < pstTmpPlmnListStru->ulPlmnNum; i++)
    {
        pstTmpPlmnListStru->astPlmnId[i].aucPlmnId[0] = pucTmpMsg[ulSum++];
        pstTmpPlmnListStru->astPlmnId[i].aucPlmnId[1] = pucTmpMsg[ulSum++];
        pstTmpPlmnListStru->astPlmnId[i].aucPlmnId[2] = pucTmpMsg[ulSum++];
    }

    /*记录长度*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_VerifyEmergencyNumListLen
 Description     : 检测紧急呼号码列表长度的合法性
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010     2012-2-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_VerifyEmergencyNumListLen
(
    VOS_UINT8                          *pRcvMsg
)
{
    VOS_UINT8                           ucTotalLen          = NAS_EMM_NULL;
    VOS_UINT8                           ucTmpLen            = NAS_EMM_NULL;
    VOS_UINT8                           ucEmerNumLen        = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;

    /*取出长度*/
    ucTotalLen = pucTmpMsg[ulSum];

    /*判断长度是否符合协议*/
    if((ucTotalLen < NAS_EMM_CN_EMERGENCYLIST_MIN_LEN)||(ucTotalLen > NAS_EMM_CN_EMERGENCYLIST_MAX_LEN))
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_EMERGENCYLIST_IE, EMM_CN_MSG_IE_LEN_INVALID, ucTotalLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_VerifyEmergencyNumListLen:ERROR:<MIN LEN or >MAX LEN!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_VerifyEmergencyNumListLen_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*跳过长度*/
    ulSum++;

    while (ucTotalLen > ucTmpLen)
    {
        /* Length of Emergency Number information */
        ucEmerNumLen = pucTmpMsg[ulSum++];

        /* 累积所有紧急呼号码的长度 */
        ucTmpLen = ucTmpLen + ucEmerNumLen + 1;

        ulSum += ucEmerNumLen;
    }

    if (ucTotalLen != ucTmpLen)
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_EMERGENCYLIST_IE, EMM_CN_MSG_IE_LEN_INVALID, ucTmpLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_VerifyEmergencyNumListLen:ERROR:Emergency List length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_VerifyEmergencyNumListLen_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeEmergencyNumList
 Description     : 把空口消息携带的Emergency number list IE内容解码到内存结构中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-2  Draft Enact
    2.lihong 00150010     2012-2-21 Modify

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeEmergencyNumList
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pstEmergencyListStru,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
)
{
    VOS_UINT8                           ucTotalLen          = NAS_EMM_NULL;
    VOS_UINT8                           ucTmpLen            = NAS_EMM_NULL;
    VOS_UINT8                           ucEmerNumLen        = NAS_EMM_NULL;
    VOS_UINT8                           ucEmerNumAmout      = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulLoop              = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    NAS_LMM_EMERGENCY_NUM_LIST_STRU    *pstTmpEmergencyListStru  = (NAS_LMM_EMERGENCY_NUM_LIST_STRU *)pstEmergencyListStru;
    LMM_MM_EMERGENCY_NUM_STRU          *pstEmergencyNum     = VOS_NULL_PTR;

    (VOS_VOID)enMsgTp;

    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEmergencyNumList:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEmergencyNumList_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*取出长度*/
    ucTotalLen = pucTmpMsg[ulSum];

    /*判断长度是否符合协议*/
    if (NAS_EMM_FAIL == NAS_EMM_VerifyEmergencyNumListLen(pucTmpMsg))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEmergencyNumList:NAS_EMM_VerifyEmergencyNumListLen FAIL!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEmergencyNumList_ENUM,LNAS_FAIL);
        /*跳过长度*/
        ulSum++;
        ulSum += ucTotalLen;
        /*记录长度*/
        *pulIndex = ulSum;
        return NAS_EMM_SUCC;
    }

    /*跳过长度*/
    ulSum++;

    while (ucTotalLen > ucTmpLen)
    {
        /* Length of Emergency Number information */
        ucEmerNumLen = pucTmpMsg[ulSum++];

        pstEmergencyNum = &pstTmpEmergencyListStru->astEmergencyNumList[ucEmerNumAmout];

        /* 减去CATAGORY的长度 */
        pstEmergencyNum->ucEmcNumLen = ucEmerNumLen - 1;
        pstEmergencyNum->ucCategory = pucTmpMsg[ulSum++] & 0x1f;
        for (ulLoop = NAS_EMM_NULL; ulLoop < pstEmergencyNum->ucEmcNumLen; ulLoop++)
        {
            pstEmergencyNum->aucEmcNum[ulLoop] = pucTmpMsg[ulSum++];
        }

        /* 紧急呼号码数加1 */
        ucEmerNumAmout++;

        /* 累积所有紧急呼号码的长度 */
        ucTmpLen = ucTmpLen + ucEmerNumLen + 1;
    }

    pstTmpEmergencyListStru->ucEmergencyNumAmount = ucEmerNumAmout;

    /*记录长度*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeEpsNetFeatureSupport
 Description     : 把空口消息携带的EPS network feature support IE内容解码到内存结构中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-4  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeEpsNetFeatureSupport
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pucNetFeature,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
)
{
    VOS_UINT32                          ulNetFeatureLen     = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    VOS_UINT8                          *pucTmpNetFeature    = (VOS_UINT8 *)pucNetFeature;

    (VOS_VOID)enMsgTp;

    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEpsNetFeatureSupport:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEpsNetFeatureSupport_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*取出长度*/
    ulNetFeatureLen = pucTmpMsg[ulSum];

    /*判断长度是否符合协议*/
    if(ulNetFeatureLen != NAS_EMM_CN_EPS_NET_FEATURE_LEN)
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_EPSNETFEATURE_IE, EMM_CN_MSG_IE_LEN_INVALID, ulNetFeatureLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEpsNetFeatureSupport:ERROR:EPS NET Feature length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEpsNetFeatureSupport_ENUM,LNAS_ERROR);
        return NAS_EMM_FAIL;
    }

    /*跳过长度*/
    ulSum++;

    *pucTmpNetFeature                   = pucTmpMsg[ulSum];

    ulSum ++;

    /*记录长度*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeAdditionalUpdateRslt
 Description     : 把空口消息携带的Additional update result IE内容解码到内存结构中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-4  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeAdditionalUpdateRslt
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pulUpRslt,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
)
{
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  *pulTmpAddUpRslt =
                    (NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32 *)pulUpRslt;

    (VOS_VOID)enMsgTp;

    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeAdditionalUpdateRslt:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeAdditionalUpdateRslt_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    pucTmpMsg[ulSum] = (pucTmpMsg[ulSum]& NAS_EMM_LOW_2_BITS_F);

    if (NAS_EMM_NULL == pucTmpMsg[ulSum])
    {
        *pulTmpAddUpRslt = NAS_LMM_ADDITIONAL_UPDATE_NO_INFO;
    }
    else if (0x01 == pucTmpMsg[ulSum])
    {
        *pulTmpAddUpRslt = NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED;
    }
    else if (0x02 == pucTmpMsg[ulSum])
    {
        *pulTmpAddUpRslt = NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY;
    }
    else
    {
        *pulTmpAddUpRslt = NAS_LMM_ADDITIONAL_UPDATE_BUTT;
    }

    ulSum ++;

    /*记录长度*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeMsgCon
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   ulIndex
                   pstPlmnListStru
 Output          : pstPlmnListStru
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeMsgCon(VOS_UINT8  *pRcvMsg,
                                        VOS_UINT32  *ulIndex,
                                    NAS_EMM_CN_MSGCON_STRU   *pstMsgConStru)
{
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgConLen         = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulSum1               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;

    NAS_EMM_CN_MSGCON_STRU             *pstTmpMsgConStru    = pstMsgConStru;

    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeMsgCon:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeMsgCon_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    ulSum1 = ulSum+1;

    /*取出长度*/
    ulMsgConLen = (pucTmpMsg[ulSum]<< NAS_EMM_MOVEMENT_8_BITS)
            | pucTmpMsg[ulSum1];

    ulSum++;

    if(NAS_EMM_NULL == ulMsgConLen)
    {
        /* 抛出可维可测 */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_ESMMSG_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsgConLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeMsgCon:ERROR: No ESM Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeMsgCon_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }
    pstTmpMsgConStru->ulMsgLen = ulMsgConLen;

    /*跳过跳过长度第3个字节*/
    ulSum++;

    for(i = 0; i < ulMsgConLen; i++)
    {
        pstTmpMsgConStru->aucMsg[i] = pucTmpMsg[ulSum++];
    }

    *ulIndex = ulSum;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeESMMsgCon
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   ulIndex
                   pstPlmnListStru
 Output          : pstPlmnListStru
 Return          : 解码是否成功
 History         :
    1.w00209181     2014-09-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeEsmMsgCon
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pulUpRslt,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
)
{
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgConLen         = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulSum1              = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;

    NAS_EMM_CN_MSGCON_STRU             *pstTmpMsgConStru    = (NAS_EMM_CN_MSGCON_STRU *)pulUpRslt;

    (VOS_VOID)enMsgTp;

    /*入口参数检查*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEsmMsgCon:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEsmMsgCon_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    ulSum1 = ulSum+1;

    /*取出长度*/
    ulMsgConLen = (pucTmpMsg[ulSum]<< NAS_EMM_MOVEMENT_8_BITS)
            | pucTmpMsg[ulSum1];

    ulSum++;

    if(NAS_EMM_NULL == ulMsgConLen)
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_ESMMSG_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsgConLen);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEsmMsgCon_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }
    pstTmpMsgConStru->ulMsgLen = ulMsgConLen;

    /*跳过跳过长度第3个字节*/
    ulSum++;

    for(i = 0; i < ulMsgConLen; i++)
    {
        pstTmpMsgConStru->aucMsg[i] = pucTmpMsg[ulSum++];
    }

    /*记录长度*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeTimer2
 Description     : 把T3402(GPRS TIMER2)消息解码到具体的结构中
 Input           : pRcvMsg
                   ulIndex
                   pstTimer
                   enMsgTp
 Output          : pstTimer pulIndex
 Return          : 解码是否成功
 History         :
    1.c00134407      2014-10-13  Draft Enact

*****************************************************************************/

VOS_UINT32  NAS_EMM_DecodeTimer2(
                                        VOS_UINT8   *pucRcvMsg,
                                        VOS_UINT32  *pulIndex,
                                        VOS_VOID    *pulUpRslt,
                                        NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg;
    VOS_UINT8                           ucTimeGap;
    NAS_EMM_TIMER_STRU                 *pstTmpTimer;
    VOS_UINT32                          ulMsgConLen;

    (VOS_VOID)enMsgTp;

    if((VOS_NULL == pucRcvMsg) ||
        (VOS_NULL == pulIndex) ||
        (VOS_NULL == pulUpRslt))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeTimer2: input pointer is NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeTimer2_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    pucTmpMsg                           = pucRcvMsg;
    pstTmpTimer                         = (NAS_EMM_TIMER_STRU *)pulUpRslt;
    ulSum                               = NAS_EMM_NULL;

    /*取出消息长度*/
    ulMsgConLen = pucTmpMsg[ulSum];

    /*跳过消息长度*/
    ulSum++;

    if(NAS_EMM_NULL == ulMsgConLen)
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_TIMER2_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsgConLen);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeTimer2_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*暂时先不保存长度信息，后续需要再添加*/

    /*取出Timer unit值*/
    ucTimeGap = (VOS_UINT8)((pucTmpMsg[ulSum] & NAS_EMM_CN_HIGH_3_BIT)
                            >>NAS_EMM_MOVEMENT_5_BITS);

    if((ucTimeGap > NAS_EMM_TIMER_UNIT_6MINUTES) &&
       (ucTimeGap < NAS_EMM_TIMER_DEACTIVATE))
    {
        ucTimeGap = NAS_EMM_TIMER_UNIT_1MINUTE;
    }

    /*保存参数*/
    pstTmpTimer->ucUnit     = ucTimeGap;
    pstTmpTimer->ucTimerVal = pucTmpMsg[ulSum++] & NAS_EMM_CN_LOW_5_BIT;

    *pulIndex = ulSum;
    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeTimer
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   ulIndex
                   pstTimer
                   enMsgTp
 Output          : pstTimer pulIndex
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeTimer(
                                    VOS_UINT8   *pucRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstTimer,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg;
    VOS_UINT8                           ucTimeGap;
    NAS_EMM_TIMER_STRU                 *pstTmpTimer;

    (VOS_VOID)enMsgTp;

    if((VOS_NULL == pucRcvMsg) ||
        (VOS_NULL == pulIndex) ||
        (VOS_NULL == pstTimer))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeTimer: input pointer is NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeTimer_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    pucTmpMsg                           = pucRcvMsg;
    pstTmpTimer                         = (NAS_EMM_TIMER_STRU *)pstTimer;

    ulSum                               = NAS_EMM_NULL;
    /*l00258641 消除fortify告警 begin*/
    /*ucTimeGap                           = NAS_EMM_NULL;*/
    /*l00258641 消除fortify告警 end*/


    /*取出Timer unit值*/
    ucTimeGap = (VOS_UINT8)((pucTmpMsg[ulSum] & NAS_EMM_CN_HIGH_3_BIT)
                            >>NAS_EMM_MOVEMENT_5_BITS);

    if((ucTimeGap > NAS_EMM_TIMER_UNIT_6MINUTES) &&
       (ucTimeGap < NAS_EMM_TIMER_DEACTIVATE))
    {
        ucTimeGap = NAS_EMM_TIMER_UNIT_1MINUTE;
    }

    /*保存参数*/
    pstTmpTimer->ucUnit     = ucTimeGap;
    pstTmpTimer->ucTimerVal = pucTmpMsg[ulSum++] & NAS_EMM_CN_LOW_5_BIT;

    *pulIndex = ulSum;
    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeBearerTxtStus
 Description     : 把MM CN 消息解码到具体的结构中
 Input           : pRcvMsg
                   ulIndex
                   pstCnMsgStru
                   enMsgTp
 Output          : pstCnMsgStru pulIndex
 Return          : 解码是否成功
 History         :
    1.h41410      2008-9-28  Draft Enact

*****************************************************************************/

VOS_UINT32  NAS_EMM_DecodeBearerTxtStus(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstBTxtStus,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT8                          *pTmpRcvMsg          = pRcvMsg;
    VOS_UINT32                          ulEpsbIdNum         = NAS_EMM_NULL;
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT16                          usEPSstatus         = NAS_EMM_NULL;
    NAS_EMM_EPS_BEARER_STATUS_STRU      *pstTmpBTxtStus     = (NAS_EMM_EPS_BEARER_STATUS_STRU *)pstBTxtStus;

    (VOS_VOID)enMsgTp;

    /*跳过EPS bearer context 长度字节*/
    ulSum++;

    /*取得承载的16位码.并跳过EPS bearer context*/
    usEPSstatus = pTmpRcvMsg[ulSum++] & NAS_EMM_CN_HIGH_3_BIT;
    usEPSstatus = (VOS_UINT16)(usEPSstatus |
                               ((pTmpRcvMsg[ulSum++] << NAS_EMM_MOVEMENT_8_BITS)));

    /*24.301  9.9.2.1.1
       EBI(0) - EBI(4):
       Bits 0 to 4 of octet 3 are spare and shall be coded as zero.
       -------------------------------------------------------------------------------
        (BIT8)|   (BIT7)|   (BIT6)|   (BIT5)|   (BIT4)|   (BIT3)|   (BIT2)|   (BIT1)
       -------------------------------------------------------------------------------
        EBI 8)|   EBI 7)|   EBI 6)|   EBI 5)|   EBI 4)|   EBI 3)|  EBI  2)|   EBI 1
       -------------------------------------------------------------------------------
        EBI 15|   EBI 14|   EBI 13|   EBI 12|   EBI 11|   EBI 10|  EBI  9)|   EBI 8
       -------------------------------------------------------------------------------*/
    for(i = 5; i < (EMM_ESM_MAX_EPS_BEARER_NUM + 5); i++)
    {
        if(1 == ((usEPSstatus >> i) & 1))
        {
            pstTmpBTxtStus->aulEsmEpsId[ulEpsbIdNum] = i;
            NAS_EMM_PUBU_LOG2_INFO("i = , ID=", i,pstTmpBTxtStus->aulEsmEpsId[ulEpsbIdNum]);
            TLPS_PRINT2LAYER_INFO2(NAS_EMM_DecodeBearerTxtStus_ENUM,LNAS_FUNCTION_LABEL1,
                                        i,pstTmpBTxtStus->aulEsmEpsId[ulEpsbIdNum]);
            ulEpsbIdNum++;
        }

    }

    pstTmpBTxtStus->ulEpsIdNum  = ulEpsbIdNum;

    NAS_EMM_PUBU_LOG1_INFO("NUM = ", pstTmpBTxtStus->ulEpsIdNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_DecodeBearerTxtStus_ENUM,LNAS_FUNCTION_LABEL2,pstTmpBTxtStus->ulEpsIdNum);

    *pulIndex = ulSum;
    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeEmmCau
 Description     : EmmCau信元解析函数
 Input           : pRcvMsg
                   ulIndex
                   pstCnMsgStru
                   enMsgTp
 Output          : pstCnMsgStru pulIndex
 Return          : 解码是否成功
 History         :
    1.shiconyong      2009-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeEmmCau(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstCnMsgStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    NAS_EMM_CN_CAUSE_ENUM_UINT8 *pucEmmCau = (NAS_EMM_CN_CAUSE_ENUM_UINT8*)pstCnMsgStru;

    (VOS_VOID)enMsgTp;

    *pulIndex = 1;
    *pucEmmCau = NAS_EMM_DecodeCnEmmCause(pRcvMsg[0]);
    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeKSIasme
 Description     : KSIasme信元解析函数
 Input           : pRcvMsg
                   ulIndex
                   pstCnMsgStru
                   enMsgTp
 Output          : pstCnMsgStru pulIndex
 Return          : 解码是否成功
 History         :
    1.shiconyong      2009-10-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeKSIasme(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstCnMsgStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    NAS_EMM_CN_KSIASME_UINT8 *pucKSIasme = (NAS_EMM_CN_KSIASME_UINT8*)pstCnMsgStru;

    (VOS_VOID)enMsgTp;

    *pulIndex = 1;
    *pucKSIasme = pRcvMsg[0] & NAS_EMM_DECODE_OCTET_USE_LOW_4_BITS;
    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeNwName
 Description     : Network Name信元解析函数
 Input           :
 Output          : VOS_UINT32  *pulIndex
 Return          : 解码是否成功
 History         :
    1.y00159566      2011-3-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeNwName(
                                        NAS_EMM_CN_NETWORK_NAME_STRU   *pstNwName,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex)
{
    VOS_UINT32                          ulIndex = (*pulIndex);

    /*本地存储的长度只包括二进制编码的内容，不包括CodeScheme等信元，需要减去1*/
    pstNwName->ucMsgLen                = pTmpRcvMsg[ulIndex]-NAS_EMM_MOVEMENT_1_BYTE;

    /*跳过长度*/
    ulIndex++;

    pstNwName->ucNumOfSpareInLastByte  = ((pTmpRcvMsg[ulIndex]) & NAS_EMM_LOW_3_BITS_F);
    pstNwName->ucAddCI                 = (((pTmpRcvMsg[ulIndex]) & NAS_EMM_FOURTH_BITS_F) >> NAS_EMM_MOVEMENT_3_BITS);
    pstNwName->ucCodingScheme          = (((pTmpRcvMsg[ulIndex]) & NAS_EMM_HIGH_3_BITS_F) >> NAS_EMM_MOVEMENT_4_BITS);

    if (NAS_EMM_CODESCHM_RESERVED <= pstNwName->ucCodingScheme)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeNwName: Coding Scheme is out of range!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeNwName_ENUM,LNAS_FUNCTION_LABEL1);
    }

    /*跳过Code Scheme等信元*/
    ulIndex++;

    /* 跳过文本区域 */
    NAS_LMM_MEM_CPY_S(                    pstNwName->aucMsg,
                                          NAS_EMM_CN_NAME_MAX_LEN,
                                          &(pTmpRcvMsg[ulIndex]),
                                          (pstNwName->ucMsgLen));

    *pulIndex = ulIndex + pstNwName->ucMsgLen;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeTimeZone
 Description     : TimeZone信元解析函数
 Input           :
 Output          : VOS_UINT32  *pulIndex
 Return          : 解码是否成功
 History         :
    1.y00159566      2011-3-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeTimeZone(
                                        NAS_EMM_CN_TIMEZONE_STRU       *pstTimeZone,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex)
{
    VOS_UINT32                          ulIndex = (*pulIndex);

    pstTimeZone->ucTimeZone    = ((pTmpRcvMsg[ulIndex]& NAS_EMM_LOW_3_BITS_F) * 10)
                               +((pTmpRcvMsg[ulIndex]& NAS_EMM_HIGH_HALF_BYTE_F)>>NAS_EMM_MOVEMENT_4_BITS);

    /* 对时区进行解码 */
    if (pTmpRcvMsg[ulIndex] & NAS_EMM_FOURTH_BITS_F)
    {
        pstTimeZone->enPosNegTimeZone = NAS_LMM_TIMEZONE_NAGETIVE;
    }
    else
    {
        pstTimeZone->enPosNegTimeZone = NAS_LMM_TIMEZONE_POSITIVE;
    }

    *pulIndex = ++ulIndex;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeLocalTimeZone
 Description     : LocalTimeZone信元解析函数
 Input           :
 Output          : VOS_UINT32  *pulIndex
 Return          : 解码是否成功
 History         :
    1.y00159566      2011-3-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeLocalTimeZone(
                                        NAS_EMM_CN_TIMEZONE_UNITIME_STRU *pstLocalTZ,
                                        VOS_UINT8                        *pTmpRcvMsg,
                                        VOS_UINT32                       *pulIndex)
{
    VOS_UINT32                          ulIndex = (*pulIndex);

    pstLocalTZ->ucYear    = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucMonth   = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucDay     = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucHour    = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucMinute  = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucSecond  = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    (VOS_VOID)NAS_EMM_DecodeTimeZone(&(pstLocalTZ->stTimeZone),
                                     pTmpRcvMsg,
                                     &ulIndex);

    *pulIndex = ulIndex;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeDaylight
 Description     : TimeZone信元解析函数
 Input           :
 Output          : VOS_UINT32  *pulIndex
 Return          : 解码是否成功
 History         :
    1.y00159566      2011-3-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeDaylight(
                                        NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8       *pstDaylight,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex)
{
    VOS_UINT32                          ulIndex = (*pulIndex);

    /* 对时区进行解码 */
    if ((pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_2_BITS_F) < NAS_LMM_DAYLIGHT_BUTT)
    {
        *pstDaylight = pTmpRcvMsg[ulIndex];
    }
    else
    {
        /*若网侧数据有误则不覆盖原有值*/
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_DAYLIGHT_IE, EMM_CN_MSG_IE_TYPE_INVALID, (pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_2_BITS_F));
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeDaylight_ENUM,LNAS_FUNCTION_LABEL1);
    }

    *pulIndex = ++ulIndex;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnEmmInfoMsg
 Description     : 解码EmmInformation消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yangfan     00159566      2009-11-4  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnEmmInfoMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                                      VOS_UINT32                 ulLength,
                                                      NAS_EMM_CN_MSG_STRU       *pstCnMsgStru)
{
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;
    VOS_UINT32                          ulCnFullNameLen     = NAS_EMM_NULL;
    VOS_UINT32                          ulCnShortNameLen     = NAS_EMM_NULL;



    NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnEmmInfoMsg is enter! ");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_ENTRY);

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    /*保存消息类型*/
    ucMsgType  = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    /*判断是否已经译完*/
    if (ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    /* 译码完整网络名 */
    if (NAS_EMM_CN_FULL_NAME == pTmpRcvMsg[ulIndex])
    {
        /*跳过Network IEI字节*/
        ulIndex++;

        /*判断长度是否合法,NAS_EMM_IE_L_LENGTH标识长度信元的 1 BYTE*/
        if (ulMsgSize < (pTmpRcvMsg[ulIndex] + ulIndex + ulLength + NAS_EMM_IE_L_LENGTH))
        {
            return NAS_EMM_SUCC;
        }

        /* 设置 Full Name 标识 */
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpFullName = NAS_EMM_BIT_SLCT;

        /* 上海要求只提供网侧下发的码流，因此不作协议译码，仅做拷贝，包括长度最长40字节 */
        if((MMC_LMM_MAX_OPER_LONG_NAME_LEN-1) <= pTmpRcvMsg[ulIndex])
        {

            /* 若信元长度大于等于39，则总共只拷贝40字节(包含了长度) */
            ulCnFullNameLen = MMC_LMM_MAX_OPER_LONG_NAME_LEN;
        }
        else
        {
            /* 拷贝的总长度要为信元长度加1 */
            ulCnFullNameLen = pTmpRcvMsg[ulIndex]+1;
        }

        NAS_LMM_MEM_CPY_S(  pstCnMsgStruIE->uCnMsgStru.stEmmInfo.aucOperatorNameLong,
                            MMC_LMM_MAX_OPER_LONG_NAME_LEN,
                            &pTmpRcvMsg[ulIndex],
                            ulCnFullNameLen);

        /* 跳过Full name信元 */
        ulIndex += pTmpRcvMsg[ulIndex]+1;


        NAS_EMM_PUBU_LOG_INFO("Full NetName: ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                            pstCnMsgStru->uCnMsgStru.stEmmInfo.aucOperatorNameLong,
                            ulCnFullNameLen);




    }

    /*判断是否已经译完*/
    if (ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    /* 译码网络简称 */
    if(NAS_EMM_CN_SHORT_NAME == pTmpRcvMsg[ulIndex])
    {
        /*跳过Network IEI字节*/
        ulIndex++;

        /*判断长度是否合法,NAS_EMM_IE_L_LENGTH标识长度信元的 1 BYTE*/
        /*lint -e961*/
        if (ulMsgSize < (pTmpRcvMsg[ulIndex] + ulIndex + ulLength + NAS_EMM_IE_L_LENGTH))
        {
        /*lint +e961*/
            return NAS_EMM_SUCC;
        }

        /* 设置ShortName标识 */
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpShortName = NAS_EMM_BIT_SLCT;

        /* 上海要求只提供网侧下发的码流，因此不作协议译码，仅做拷贝，包括长度最长36字节 */
        if((MMC_LMM_MAX_OPER_SHORT_NAME_LEN-1) <= pTmpRcvMsg[ulIndex])
        {
            /* 若信元长度大于等于35，则总共只拷贝36字节(包含了长度) */
            ulCnShortNameLen = MMC_LMM_MAX_OPER_SHORT_NAME_LEN;
        }
        else
        {
            /* 拷贝的总长度要为信元长度加1 */
            ulCnShortNameLen = pTmpRcvMsg[ulIndex]+1;
        }

        NAS_LMM_MEM_CPY_S(  pstCnMsgStruIE->uCnMsgStru.stEmmInfo.aucOperatorNameShort,
                            MMC_LMM_MAX_OPER_SHORT_NAME_LEN,
                            &pTmpRcvMsg[ulIndex],
                            ulCnShortNameLen);

        /* 跳过Short name信元 */
        ulIndex += pTmpRcvMsg[ulIndex]+1;


        NAS_EMM_PUBU_LOG_INFO("Full NetName: ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                            pstCnMsgStru->uCnMsgStru.stEmmInfo.aucOperatorNameShort,
                            ulCnShortNameLen);




    }

    /*判断是否已经译完*/
    if (ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    /* 译码本地时区 */
    if (NAS_EMM_LOCAL_TIME_ZONE == pTmpRcvMsg[ulIndex])
    {
        /*判断长度是否合法*/
        if (ulMsgSize < (ulIndex + ulLength + NAS_EMM_TIMEZONE_LEN))
        {
            return NAS_EMM_SUCC;
        }

        /* 设置标识位 */
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpLocTimeZone            = NAS_EMM_BIT_SLCT;

        /*跳过 IEI字节*/
        ulIndex++;

        /*解码*//*协议表述为精度为15分钟，GCF码流为1小时,可能有问题*/
        (VOS_VOID)NAS_EMM_DecodeTimeZone(&(pstCnMsgStruIE->uCnMsgStru.stEmmInfo.stLocTimeZone),
                                         pTmpRcvMsg,
                                         &ulIndex);
    }

    if (ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    NAS_EMM_PUBU_LOG_INFO("TIMEZONE: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL3);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                       (VOS_UINT8 *)&(pstCnMsgStru->uCnMsgStru.stEmmInfo.stLocTimeZone),
                       sizeof(NAS_EMM_CN_TIMEZONE_STRU));

    /* 解码本地时间 */
    if(NAS_EMM_UNIVTIME_LOCALTIMEZONE == pTmpRcvMsg[ulIndex])
    {
        /*判断长度是否合法*/
        if (ulMsgSize < (ulIndex + ulLength + NAS_EMM_TIME_TIMEZONE_LEN))
        {
            return NAS_EMM_SUCC;
        }

        /*跳过 IEI字节*/
        ulIndex++;

        /*设置支持LocTimeZone*/
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpUniTimeLocTimeZone     = NAS_EMM_BIT_SLCT;

        /*给每个属性赋值*/
        (VOS_VOID)NAS_EMM_DecodeLocalTimeZone(&(pstCnMsgStruIE->uCnMsgStru.stEmmInfo.stTimeZoneAndTime),
                                              pTmpRcvMsg,
                                              &ulIndex);

    }

    NAS_EMM_PUBU_LOG_INFO("TIMEZONE_UNITIME: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL4);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                       (VOS_UINT8 *)&(pstCnMsgStru->uCnMsgStru.stEmmInfo.stTimeZoneAndTime),
                       sizeof(NAS_EMM_CN_TIMEZONE_UNITIME_STRU));

    if (ulMsgSize < (ulIndex + ulLength + NAS_EMM_DAYLIGHTTIME))
    {
        return NAS_EMM_SUCC;
    }

    /* 解码Daylight时间 */
    if(NAS_EMM_CN_DAYLIGHT_SAVE_TIME == pTmpRcvMsg[ulIndex])
    {
        /*跳过 IEI字节*/
        ulIndex++;

        /*跳过 Length 字节*/
        ulIndex++;

        /*设置标识*/
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpDaylightTime = NAS_EMM_BIT_SLCT;

        (VOS_VOID)NAS_EMM_DecodeDaylight(&(pstCnMsgStruIE->uCnMsgStru.stEmmInfo.enDaylightSavingTime),
                                         pTmpRcvMsg,
                                         &ulIndex);
    }

    NAS_EMM_PUBU_LOG_INFO("DAYLIGHT: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL5);
    /*lint -e961*/
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                       (VOS_UINT8 *)&(pstCnMsgStru->uCnMsgStru.stEmmInfo.enDaylightSavingTime),
                       sizeof(NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8));
    /*lint +e961*/

    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_DecodeCnEmmStatusMsg(LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                                         VOS_UINT32                  ulLength,
                                                         NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;

    /*保存消息类型*/
    ucMsgType  = pTmpRcvMsg[ulIndex];
    pstCnMsgStru->ulCnMsgType = ucMsgType;

    /*跳过消息类型*/
    ulIndex++;

    pstCnMsgStru->uCnMsgStru.stEmmStatus.ucEmmCause = pTmpRcvMsg[ulIndex];

    return NAS_EMM_SUCC;

}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnDownlinkNasTransportMsg
 Description     : 解码downlink nas transport消息，里面暂时只支持sms解码
 Input           : pRcvMsg
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.FTY       2011-11-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnDownlinkNasTransportMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;

    /*保存消息类型*/
    pstCnMsgStru->ulCnMsgType  = pTmpRcvMsg[ulIndex];

    /*跳过消息类型*/
    ulIndex++;

    /*读取SMS信息长度*/
    pstCnMsgStru->uCnMsgStru.stDownlinkNasTransport.ucDownlinkNasTransportLen = pTmpRcvMsg[ulIndex];

    /*跳过SMS信息长度*/
    ulIndex++;

    /*读取SMS信息*/
    NAS_LMM_MEM_CPY_S(  pstCnMsgStru->uCnMsgStru.stDownlinkNasTransport.aucDownlinkNasTransportMsg,
                        NAS_EMM_DOWNLINK_NAS_TRANSPORT_MAX_LEN,
                        &(pTmpRcvMsg[ulIndex]),
                        pstCnMsgStru->uCnMsgStru.stDownlinkNasTransport.ucDownlinkNasTransportLen);

    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCli
 Description     : 解码CLI信元
 Input           : pRcvMsg
                   ulLength
 Output          : pstCsSerNotifications
                   pulIndex
 Return          : 解码是否成功
 History         :
    1.lihong00150010       2012-02-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCli
(
    LRRC_LNAS_MSG_STRU                  *pRcvMsg,
    VOS_UINT32                           ulLength,
    VOS_UINT32                          *pulIndex,
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification
)
{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulDecodedLenBefore  = ulLength + (*pulIndex);

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulDecodedLenBefore;
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    /*跳过Network IEI字节*/
    ulIndex++;

    /* 判断CLI的长度位于【1-12】 */
    if ((pTmpRcvMsg[ulIndex] < NAS_EMM_CLI_MIN_LEN)
        || (pTmpRcvMsg[ulIndex] > NAS_EMM_CLI_MAX_LEN))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCli:CLI LEN Illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCli_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*判断长度是否合法*/
    if (ulMsgSize < (pTmpRcvMsg[ulIndex] + ulIndex + ulDecodedLenBefore + NAS_EMM_IE_L_LENGTH))
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_CLI_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsgSize);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCli_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }

    pstCsSerNotification->bitOpCli = NAS_EMM_BIT_SLCT;
    pstCsSerNotification->ucCliLength = pTmpRcvMsg[ulIndex++];
    NAS_LMM_MEM_CPY_S(  pstCsSerNotification->aucCliValue,
                        NAS_EMM_CLI_MAX_LEN,
                        &pTmpRcvMsg[ulIndex],
                        pstCsSerNotification->ucCliLength);
    ulIndex += pstCsSerNotification->ucCliLength;
    *pulIndex = *pulIndex + ulIndex;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeLcsClientId
 Description     : 解码LCS CLIENT IDENTIFIER信元
 Input           : pRcvMsg
                   ulLength
 Output          : pstCsSerNotifications
                   pulIndex
 Return          : 解码是否成功
 History         :
    1.lihong00150010       2012-02-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeLcsClientId
(
    LRRC_LNAS_MSG_STRU                  *pRcvMsg,
    VOS_UINT32                           ulLength,
    VOS_UINT32                          *pulIndex,
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification
)
{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulDecodedLenBefore  = ulLength + (*pulIndex);

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulDecodedLenBefore;
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    /*跳过Network IEI字节*/
    ulIndex++;

    /* 判断CLI的长度位于【1-255】 */
    if (pTmpRcvMsg[ulIndex] < NAS_EMM_LCS_CLIENT_ID_MIN_LEN)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeLcsClientId:LCS CLIENT ID Illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeLcsClientId_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }

    /*判断长度是否合法*/
    if (ulMsgSize < (pTmpRcvMsg[ulIndex] + ulIndex + ulDecodedLenBefore + NAS_EMM_IE_L_LENGTH))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeLcsClientId:LCS CLIENT ID is too long!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeLcsClientId_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SUCC;
    }

    pstCsSerNotification->bitOpLcsClientId = NAS_EMM_BIT_SLCT;
    pstCsSerNotification->ucLcsClientIdLen = pTmpRcvMsg[ulIndex++];
    NAS_LMM_MEM_CPY_S(  pstCsSerNotification->aucLcsClientId,
                        NAS_EMM_LCS_CLIENT_ID_MAX_LEN,
                        &pTmpRcvMsg[ulIndex],
                        pstCsSerNotification->ucLcsClientIdLen);
    ulIndex += pstCsSerNotification->ucLcsClientIdLen;
    *pulIndex = *pulIndex + ulIndex;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnCsSerNotification
 Description     : 解码CS SERVICE NOTIFICATION消息
 Input           : pRcvMsg
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.lihong00150010       2012-02-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnCsSerNotification
(
    LRRC_LNAS_MSG_STRU                 *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStru
)
{
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification = VOS_NULL_PTR;

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    /* 保存消息类型 */
    pstCnMsgStru->ulCnMsgType  = pTmpRcvMsg[ulIndex];

    /* 跳过消息类型 */
    ulIndex++;

    pstCsSerNotification = &pstCnMsgStru->uCnMsgStru.stCsSerNotification;

    pstCsSerNotification->ucPagingIdenity = pTmpRcvMsg[ulIndex++] & NAS_EMM_BIT_1;

    /* 判断是否已经译完,CLI最小为3 */
    if (ulMsgSize <= (ulIndex + ulLength + 2))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:CLI IE LEN <=2!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }

    /* 判断是否携带CLI */
    if (NAS_EMM_MSG_CLI_IEI == pTmpRcvMsg[ulIndex])
    {
        if (NAS_EMM_FAIL == NAS_EMM_DecodeCli(  pRcvMsg, ulLength,
                                                &ulIndex, pstCsSerNotification))
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:NAS_EMM_DecodeCli failed!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_SUCC;
        }
    }

    /* 判断是否已经译完,SS CODE最小为2 */
    if (ulMsgSize <= (ulIndex + ulLength + 1))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:SS code IE LEN <=1!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_SUCC;
    }

    /* 判断是否携带SS COE */
    if (NAS_EMM_MSG_SS_CODE_IEI == pTmpRcvMsg[ulIndex])
    {
        /*跳过Network IEI字节*/
        ulIndex++;

        pstCsSerNotification->bitOpSsCode = NAS_EMM_BIT_SLCT;
        pstCsSerNotification->ucSsCodeValue = pTmpRcvMsg[ulIndex++];
    }

    /* 判断是否已经译完,LCS INDICATOR最小为2 */
    if (ulMsgSize <= (ulIndex + ulLength + 1))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:LCS INDICATOR IE LEN <=1!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_SUCC;
    }

    /* 判断是否携带LCS INDICATOR */
    if (NAS_EMM_MSG_LCS_INDICATOR_IEI == pTmpRcvMsg[ulIndex])
    {
        /*跳过Network IEI字节*/
        ulIndex++;

        pstCsSerNotification->bitOpLcsIndicator = NAS_EMM_BIT_SLCT;
        pstCsSerNotification->ucLcsIndicatorValue = pTmpRcvMsg[ulIndex++];
    }

    /* 判断是否已经译完,LCS CLIENT ID最小为3 */
    if (ulMsgSize <= (ulIndex + ulLength + 2))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:LCS CLIENT ID IE LEN <=2!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL5);
        return NAS_EMM_SUCC;
    }

    /* 判断是否携带LCS CLIENT ID */
    if (NAS_EMM_MSG_LCS_CLIENT_ID_IEI == pTmpRcvMsg[ulIndex])
    {
        if (NAS_EMM_FAIL == NAS_EMM_DecodeLcsClientId(  pRcvMsg, ulLength,
                                                        &ulIndex, pstCsSerNotification))
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:NAS_EMM_DecodeLcsClientId failed!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL6);
            return NAS_EMM_SUCC;
        }
    }

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeGenericMessageContainer
 Description     : 解码 Generic Message Container 部分
 Input           : pMsgBuf      : 待解码码流
 Output          : pLength      : 解码完成后内存偏移量
                   pDstMsgStrct : 解码后存放数据结构
 Return          : 解码是否成功
 History         :
    1.liuhua    00212067       2012-07-04  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_DecodeGenericMessageContainer(VOS_UINT8 *pucMsgBuf,
                                                 VOS_UINT32 *pulLength,
                                                 NAS_EMM_GENERIC_MESSAGE_CONTAINER_STRU *pstDstMsgStrct)
{
    VOS_UINT32 ulIndex = 0;

    if ((VOS_NULL_PTR == pucMsgBuf) || (VOS_NULL_PTR == pstDstMsgStrct))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeGenericMessageContainer: invalid parameter");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeGenericMessageContainer_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    *pulLength = 0;

    /* save generic message container contents length */
    pstDstMsgStrct->usMsgLen = (pucMsgBuf[ulIndex] << NAS_EMM_MOVEMENT_8_BITS) + pucMsgBuf[ulIndex + 1];
    ulIndex += 2;

    if (pstDstMsgStrct->usMsgLen > NAS_EMM_CN_MSGCON_MAX_LEN)
    {
        pstDstMsgStrct->usMsgLen = NAS_EMM_CN_MSGCON_MAX_LEN;
    }

    /* save generic message container content */
    NAS_LMM_MEM_CPY_S(  pstDstMsgStrct->aucMsg,
                        NAS_EMM_CN_MSGCON_MAX_LEN,
                        pucMsgBuf + ulIndex,
                        pstDstMsgStrct->usMsgLen);
    ulIndex += pstDstMsgStrct->usMsgLen;

    *pulLength = ulIndex;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeAdditionalInfo
 Description     : 解码 Additional Information 部分
 Input           : pMsgBuf      : 待解码码流
 Output          : pLength      : 解码完成后内存偏移量
                   pDstMsgStrct : 解码后存放数据结构
 Return          : 解码是否成功
 History         :
    1.liuhua    00212067       2012-07-04  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_DecodeAdditionalInfo(VOS_UINT8 *pucMsgBuf,
                                        VOS_UINT32 *pulLength,
                                        NAS_EMM_ADDITIONAL_INFOR_STRU *pstDstMsgStrct)
{
    VOS_UINT32 ulIndex = 0;

    if ((VOS_NULL_PTR == pucMsgBuf) || (VOS_NULL_PTR == pstDstMsgStrct))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeAdditionalInfo: invalid parameter");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeAdditionalInfo_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    *pulLength = 0;

    /* save Additional Information length */
    pstDstMsgStrct->ucMsgLen = pucMsgBuf[ulIndex];
    ulIndex++;

    NAS_LMM_MEM_CPY_S(  pstDstMsgStrct->aucMsg,
                        sizeof(pstDstMsgStrct->aucMsg),
                        pucMsgBuf + ulIndex,
                        pstDstMsgStrct->ucMsgLen);
    ulIndex += pstDstMsgStrct->ucMsgLen;

    *pulLength = ulIndex;

    return NAS_EMM_SUCC;
}
/*lint +e961*/
/*lint +e960*/
/*lint +e72*/
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg
 Description     : 解码DOWNLINK GENERIC NAS Transport消息
 Input           : pRcvMsg
 Output          : pstCnMsgStru
 Return          : 解码是否成功
 History         :
    1.liuhua    00212067       2012-07-03  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg
(
    LRRC_LNAS_MSG_STRU                 *pstRcvMsg,
    VOS_UINT32                          ulIndex,
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStru
)
{
    NAS_EMM_CN_DOWNLINK_GENERIC_NAS_TRANSPORT_STRU *pstDstMsgStruct = VOS_NULL_PTR;
    VOS_UINT32 ulEleLen = 0;
    VOS_UINT32 ulRet = NAS_EMM_SUCC;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg: entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_ENTRY);

    if ((VOS_NULL_PTR == pstRcvMsg) || (VOS_NULL_PTR == pstCnMsgStru))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg: invalid parameter");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    pstDstMsgStruct = &pstCnMsgStru->uCnMsgStru.stDownlinkGenericNasTransport;

    /* save and skip message type */
    pstCnMsgStru->ulCnMsgType  = pstRcvMsg->aucNasMsg[ulIndex];
    ulIndex++;

    /* Generic message container type */
    pstDstMsgStruct->ucContainerType = pstRcvMsg->aucNasMsg[ulIndex];
    ulIndex++;

    /* check length */
    if ((ulIndex + 3) > pstRcvMsg->ulNasMsgSize)
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_GENERIC_MSG_CONT_IE, EMM_CN_MSG_IE_LEN_INVALID, pstRcvMsg->ulNasMsgSize);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /* decode Generic message container */
    ulRet = NAS_EMM_DecodeGenericMessageContainer(pstRcvMsg->aucNasMsg + ulIndex,
                                                 &ulEleLen,
                                                 &pstDstMsgStruct->stContainer);
    if (NAS_EMM_FAIL == ulRet)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg: decode GMC fail");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
    ulIndex += ulEleLen;

    if (ulIndex > pstRcvMsg->ulNasMsgSize)
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_GENERIC_MSG_CONT_IE, EMM_CN_MSG_IE_LEN_INVALID, ulIndex);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_FUNCTION_LABEL3);
        ulRet = NAS_EMM_FAIL;
    }
    else if (((pstRcvMsg->ulNasMsgSize - ulIndex) >= 3) &&
             (NAS_EMM_ADDITIONAL_INFO_IEI == pstRcvMsg->aucNasMsg[ulIndex]))
    {
        /* skip Additional information IEI */
        ulIndex++;

        /* decode Additional information */
        ulRet = NAS_EMM_DecodeAdditionalInfo(pstRcvMsg->aucNasMsg + ulIndex,
                                             &ulEleLen,
                                             &pstDstMsgStruct->stAdditionalInfo);
        if ((NAS_EMM_SUCC == ulRet) && ((ulIndex + ulEleLen) <= pstRcvMsg->ulNasMsgSize))
        {
            pstDstMsgStruct->bitOpAdditionalInfo = 1;
        }
        else
        {
            /* 抛出可维可测 */
            NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_ADDITIONAL_IE, EMM_CN_MSG_IE_ADDITONAL_INFO_TOO_SHORT, (ulIndex + ulEleLen));
            ulRet = NAS_EMM_FAIL;
        }
    }
    else
    {
        /* loosely-input principle, we consider it as success case */
        ulRet = NAS_EMM_SUCC;
    }

    /* The following code is used for ST */
#ifdef PS_ITT_PC_TEST_NAS
    if (NAS_EMM_SUCC == ulRet)
    {
        NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU stUplinkMsg = {0};

        stUplinkMsg.ucContainerType     = pstDstMsgStruct->ucContainerType;
        stUplinkMsg.stContainer         = pstDstMsgStruct->stContainer;
        stUplinkMsg.bitOpAdditionalInfo = pstDstMsgStruct->bitOpAdditionalInfo;
        stUplinkMsg.stAdditionalInfo    = pstDstMsgStruct->stAdditionalInfo;

 //       NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport(&stUplinkMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogCnMsgIEDecodeFail
 Description     : EMM空口信元解析失败，可维可测上报
 Input           : enIeType 信元类型
                   enCause  失败原因
                   ulValue  失败值
 Output          : None
 Return          : None

 History         :
    1.leixiantiao 00258641      2015-3-13  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SndOmLogCnMsgDecodeFail
(
    NAS_EMM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_EMM_CN_MSG_DECODE_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
)
{
    NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndOmLogStateChange: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmLogCnMsgDecodeFail_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL;
    pstMsg->enIeType = enIeType;
    pstMsg->enCause = enCause;
    pstMsg->ulValue = ulValue;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}


/*lint +e818*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

