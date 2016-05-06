/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasLppEtcMsgProc.c
  版 本 号   : 初稿
  作    者   : LIFUXIN
  生成日期   : 2015年7月30日
  最近修改   :
  功能描述   : LPP 模块的内部消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月1日
    作    者   : LIFUXIN
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
//#include  "vos.h"
#include  "NasLppPublic.h"
#include  "NasLppSendMsg.h"
#include  "EtcLppInterface.h"
#include  "NasLppSendMsg.h"
#include  "NasLppEtcMsgProc.h"

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPETCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPETCMSGPROC_C


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LPP_SndMtaResetGnssPositionInfo
 Description     : reset GNSS的辅助数据
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-10-21  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_SndMtaResetGnssPositionInfo(VOS_VOID)
{
    LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU    *pstResetGnssAssistData  = NAS_LPP_NULL_PTR;
    NAS_LPP_NORM_LOG("NAS_LPP_SndMtaResetGnssPositionInfo!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndMtaResetGnssPositionInfo_ENUM, LNAS_LPP_Func_Enter);

    pstResetGnssAssistData = (LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU));
    if (NAS_LPP_NULL_PTR == pstResetGnssAssistData)
    {
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstResetGnssAssistData, sizeof(LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU), 0, sizeof(LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU));

    /*消息头*/
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstResetGnssAssistData, ID_LPP_MTA_GNSS_RESET_ASSIST_DATA);

    NAS_LPP_SND_MSG(pstResetGnssAssistData);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvLppEtcResetPostitionInfoInd
 Description     : ETC模块给LPP发送的reset positioning info的处理
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-9-1  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RcvLppEtcResetPostitionInfoInd( ETC_LPP_RESET_POSTION_INFO_STRU *pRcvMsg )
{
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLocTechmap = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEtcResetPostitionInfoInd_ENUM, LNAS_LPP_Func_Enter);

    switch(pRcvMsg->enRestType)
    {
        case ETC_LPP_RESET_TYPE_GNSS:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd: Reset GNSS Information!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEtcResetPostitionInfoInd_ENUM, LNAS_LPP_ResetGnssInfo);
            NAS_LPP_SndMtaResetGnssPositionInfo();
            break;

        case ETC_LPP_RESET_TYPE_OTDOA:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd: Reset OTDOA Information!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEtcResetPostitionInfoInd_ENUM, LNAS_LPP_ResetOtdoaInfo);

            /*复位OTDOA的辅助信息*/
            /*清空本地存贮的辅助信息*/
            NAS_LPP_MEM_SET_S(&(NAS_LPP_GetLppEntityCtx()->stMeasResult.stOtdoaMeasRslt),
                            sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU),
                            0,
                            sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU));

            NAS_LPP_MEM_SET_S(&(NAS_LPP_GetLppEntityCtx()->stLppConfig.stOtdoaAssisCfg),
                            sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU),
                            0,
                            sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));

            /*查找running表，得到transactionIndex，sessionTransactionIndx*/
            pstLocTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
            if (NAS_LPP_NULL_PTR != pstLocTechmap)
            {
                /*给LRRC发送测量停止*/
                NAS_LPP_SndOtdoaMeasReq(pstLocTechmap->ucSessionIndx,
                                              pstLocTechmap->ucSessionTranIndx,
                                              LPP_LRRC_LCS_MEAS_CMD_REL);
            }
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EtcMsgDistr
 Description     : ETC模块给LPP模块自己发的消息的处理入口函数
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-9-1  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EtcMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_EtcMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EtcMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pEmmMsg->ulMsgName)
    {
        /*收到的是ID_ETC_LPP_RESET_POSTION_INFO_IND消息*/
        case ID_ETC_LPP_RESET_POSTION_INFO_IND:
            NAS_LPP_RcvLppEtcResetPostitionInfoInd((ETC_LPP_RESET_POSTION_INFO_STRU *)pRcvMsg);
            break;

        default:
            NAS_LPP_WARN_LOG("NAS_LPP_EtcMsgDistr:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_EtcMsgDistr_ENUM, LNAS_LPP_ErrorSenderPid);
            break;
    }

    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

