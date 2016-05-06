/******************************************************************************
        @(#)Copyright(C)2008,Hisilicon Co. LTD.
 ******************************************************************************
    File name   : NasEmmGuti.c
    Description : 本文件定义了GUTI模块的处理流程
    History     :
      1.  zangyalan 57968  2008-09-09  Draft Enact
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmGuti.h"
#include "NasEmmAttDetInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMGUTI_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMGUTI_C
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
 Function Name  : NAS_EMM_GutiInit
 Discription    : GUTI模块初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
      2.  hanlufeng 41410 2009-05-12  初始化不再附缺省值。
*****************************************************************************/
VOS_VOID NAS_EMM_GutiInit(VOS_VOID)
{
    /*GUTI目前没有需要初始化的信息,暂时为空*/
    return;
}


VOS_VOID  NAS_EMM_FreeGutiDyn( VOS_VOID )
{
    /*GUTI暂时为空*/
    return;
}



/*****************************************************************************
 Function Name  : Nas_Emm_TaiListSet
 Discription    : 更新TAI列表
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_TaiListSet(const NAS_EMM_TA_LIST_STRU *pstTaiList)
{

    /*检查TaiList合法性      */
    if ( NAS_EMM_NULL_PTR == pstTaiList)
    {
        NAS_EMM_GUTI_ERROR_LOG("NAS_EMM_TaiListSet:Input TaiList is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TaiListSet_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_FAIL;
    }

    /*把旧TaiList清0*/
    NAS_LMM_MEM_SET_S(  &NAS_EMM_TAI_LIST,
                        sizeof(NAS_EMM_TA_LIST_STRU),
                        0,
                        sizeof(NAS_EMM_TA_LIST_STRU));

    /* 更新TaiList的全局变量 */
    NAS_LMM_MEM_CPY_S(  &NAS_EMM_TAI_LIST,
                        sizeof(NAS_MM_TA_LIST_STRU),
                        pstTaiList,
                        sizeof(NAS_EMM_TA_LIST_STRU));

    g_stEmmInfo.stNetInfo.bitOpTaiList = NAS_EMM_BIT_SLCT;

    /* 把更新的全局变量TAI List写入NVIM */
    /*NAS_LMM_WriteNvTaList();*/

    return NAS_LMM_SUCC;
}

/*****************************************************************************
 Function Name  : Nas_Emm_CompCnGutiCmp
 Discription    : 构造GUTI REALLOCATION COMPLETE的CN消息
 Input          : 消息
 Output         : pNasMsg
 Return         : None
 History:
      1.  zangyalan  2008-09-18  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_CompCnGutiCmp(LRRC_LNAS_MSG_STRU  *pNasMsg)
{

    /* 填充CN消息长度字段,即 NasMsg部分*/
    pNasMsg->ulNasMsgSize = NAS_GUTI_COMP_NAS_MSG_LEN;

    /* 清空将填充CN消息的空间 */
    NAS_LMM_MEM_SET_S(  pNasMsg->aucNasMsg,
                        pNasMsg->ulNasMsgSize,
                        0,
                        pNasMsg->ulNasMsgSize);

    /* 填充 Protocol Discriminator */
    pNasMsg->aucNasMsg[0]  = EMM_CN_MSG_PD_EMM;

    /*填充 Security header type*/
    pNasMsg->aucNasMsg[0] |= NAS_EMM_CN_MSG_SE_EMM;

    /* 填充 Guti reallocation complete message identity   */
    pNasMsg->aucNasMsg[1]  = NAS_EMM_CN_MT_GUTI_CMP;

    return;
}


/*****************************************************************************
 Function Name  : Nas_Emm_MrrcDataReq
 Discription    : 构造MRRC_DATA_REQ，把上行消息发给mrrc模块转发
 Input          : GUTI
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_GutiMrrcDataReq(VOS_VOID)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pstMrrcDataReqMsg = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLen;


    /*分配空间,内部消息不应该分配空间,而应获取地址方式*/
    /*获取内部消息地址*/
    pstMrrcDataReqMsg =(NAS_EMM_MRRC_DATA_REQ_STRU *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    if(NAS_EMM_NULL_PTR == pstMrrcDataReqMsg)
    {
        return NAS_EMM_ERR;
    }

     /* 填充CN消息    */
    NAS_EMM_CompCnGutiCmp( &(pstMrrcDataReqMsg->stNasMsg));

    ulLen  = NAS_EMM_CountMrrcDataReqLen(pstMrrcDataReqMsg->stNasMsg.ulNasMsgSize);

    /*打包VOS消息头,NAS_EMM_MRRC_DATA_REQ_STRU */
    NAS_EMM_INTRA_MSG_HEADER(pstMrrcDataReqMsg, ulLen);

    /*填充消息ID    */
    pstMrrcDataReqMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    pstMrrcDataReqMsg->enDataCnf        = LRRC_LMM_DATA_CNF_NEED;

    /*填充消息内容*/
    pstMrrcDataReqMsg->enEstCaue        = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
     pstMrrcDataReqMsg->enCallType      = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pstMrrcDataReqMsg->enEmmMsgType     = NAS_EMM_MSG_GUTI_CMP;

    /*空口消息上报GUTI REALLOCATION COMPLETE*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_GUTI_CMP,  (NAS_MSG_STRU*)&(pstMrrcDataReqMsg->stNasMsg));

    /*关键事件上报GUTI REALLOCATION COMPLETE*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_GUTI_CMP);

    /*发出内部消息MRRC_DATA_REQ*/
    NAS_EMM_SndUplinkNasMsg(            pstMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pstMrrcDataReqMsg);

    return NAS_EMM_OK;
}

/*****************************************************************************
 Function Name  : NAS_EMM_AnyStateMsgGtReCmd
 Discription    : Reg.Normal_Service,SerInit.WtSerCnf,DeregInit.WtCnDetCnf,
                  MrrcConnInit.WtRrcRelCnf状态下，收到GUTI_REALLOC_CMD
 Input          : 消息ID,消息
 Output         : None
 Return         : None
 History:
      1.  zhengjunyan 00148421 2009-10-27  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_AnyStateMsgGtReCmd(VOS_UINT32  ulMsgId,
                                      VOS_VOID  *pMsgStru)
{
    NAS_EMM_GUTI_REALLOCATION_CMD_STRU *pstGutiCmdMsg = NAS_EMM_NULL_PTR;
    NAS_EMM_GUTI_STRU                  *pstGuti;
    VOS_UINT32                          ulRst;

    (VOS_VOID)ulMsgId;

    /*解析消息，获取网侧发来的GUTI*/
    pstGutiCmdMsg = (NAS_EMM_GUTI_REALLOCATION_CMD_STRU *)pMsgStru;
    pstGuti       = (NAS_EMM_GUTI_STRU *) &pstGutiCmdMsg->stGuti;

    /*更新全局变量GUTI*/
    NAS_LMM_MEM_CPY_S(  NAS_LMM_GetEmmInfoUeidGutiAddr(),
                        sizeof(NAS_LMM_GUTI_STRU),
                        pstGuti,
                        sizeof(NAS_LMM_GUTI_STRU));

    NAS_LMM_GetEmmInfoUeidAddr()->bitOpGuti = NAS_EMM_BIT_SLCT;
    /*如果更新了Tai List,存储最新Tai List */
    if(VOS_TRUE == pstGutiCmdMsg->ucBitOpTaiList)
    {
        if(NAS_LMM_SUCC == NAS_EMM_TaiListSet(&pstGutiCmdMsg->stTaiList))
        {
            NAS_EMM_GUTI_NORMAL_LOG("NAS_EMM_AnyStateMsgGtReCmd: TaiList update is success!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_AnyStateMsgGtReCmd_ENUM,LNAS_SUCC);

            /*保存新的TAI List的同时更新ForbTA for Roaming和ForbTA for RPOS*/
            NAS_EMMC_UpdateForbTaList();
        }
        else
        {
            NAS_EMM_GUTI_ERROR_LOG("NAS_EMM_AnyStateMsgGtReCmd: TaiList update is fail!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_AnyStateMsgGtReCmd_ENUM,LNAS_FAIL);
        }
    }

    /* 判断没有放到函数NAS_LMM_WritePsLoc中来做，是由于紧急注册被拒或者尝试
       次数达到5次时还是要删除参数 ，协议只规定是紧急注册成功后才不写卡或者
       NV项 */
    if ((NAS_LMM_REG_STATUS_EMC_REGING != NAS_LMM_GetEmmInfoRegStatus())
        && (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus()))
    {
        /*保存PS LOC信息*/ /*存储最新guti，last Ta,update state */
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }

    /*发出内部消息MRRC_DATA_REQ,携带GUTI REALLOCAITON CMPL*/
    ulRst = NAS_EMM_GutiMrrcDataReq();
    if(NAS_EMM_OK != ulRst)
    {
        NAS_EMM_GUTI_ERROR_LOG("NAS_EMM_AnyStateMsgGtReCmd: NAS_EMM_GutiMrrcDataReq err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AnyStateMsgGtReCmd_ENUM,LNAS_ERROR);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/


VOS_UINT32  NAS_EMM_CheckSimGutiValid( const VOS_UINT8 *pucSimRecord,
                                                  const VOS_UINT32 ulIndex,
                                                  const VOS_UINT32 ulLen )
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_LMM_CheckWhetherAllBytesAreFF( pucSimRecord, ulIndex, ulLen );

    if ( VOS_FALSE == ulRslt)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}


/****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of NasEmmGuti.c */
