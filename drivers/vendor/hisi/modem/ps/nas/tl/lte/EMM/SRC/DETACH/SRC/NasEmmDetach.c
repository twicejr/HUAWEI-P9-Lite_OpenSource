



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasEmmGIMComm.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMDETACH_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMDETACH_C
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
NAS_EMM_DETACH_CTRL_STRU                g_stEmmDetCtrl;


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_EMM_DetachInit
 Description     :

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-12-24  Mod:为了支持开机不自动ATTACH功能,DETACH
                                         模块全局变量g_stEmmDetCtrl.ucAutoAttSta
                                         移到PUBU模块g_ulAutoAttFlag。
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_DetachInit()
{
    NAS_EMM_DETACH_LOG_NORM("NAS_EMM_DetachInit                START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DetachInit_ENUM,LNAS_BEGIN);

    /* 初始化 detach全局变量 */
    NAS_LMM_MEM_SET_S(&g_stEmmDetCtrl, sizeof(g_stEmmDetCtrl), 0, sizeof(g_stEmmDetCtrl));

    NAS_EMM_GLO_AD_GetDetTypeMo()       = MMC_LMM_MO_DET_PS_ONLY;

    /*初始化 UE 发起 detach 的默认类型*/
    NAS_EMM_GLO_AD_GetDetMode()         = NAS_EMM_DETACH_MODE_NOT_SWITCH_OFF;

    return;
}


VOS_VOID  NAS_EMM_FreeDetDyn( VOS_VOID )
{
    /*暂时无相关操作*/
    return;
}

/*****************************************************************************
 Function Name   :  NAS_EMM_Detach_ClearResourse
 Description     :
 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-12-24  Mod:为了支持开机不自动ATTACH功能,DETACH
                                         模块全局变量g_stEmmDetCtrl.ucAutoAttSta
                                         移到PUBU模块g_ulAutoAttFlag。
*****************************************************************************/
VOS_VOID NAS_EMM_Detach_ClearResourse(VOS_VOID)
{

    /*动态内存释放*/
    /*lint -e522*/
    NAS_EMM_FreeDetDyn();
    /*lint +e522*/

    /* 停止DETACH定时器 */
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

    /*赋初值*/
    NAS_LMM_MEM_SET_S(  NAS_EMM_GLO_AD_GetDetCtrlAddr(),
                        sizeof(NAS_EMM_DETACH_CTRL_STRU),
                        0,
                        sizeof(NAS_EMM_DETACH_CTRL_STRU));

    NAS_EMM_GLO_AD_GetDetTypeMo()       = MMC_LMM_MO_DET_PS_ONLY;

    /*初始化 UE 发起 detach 的默认类型*/
    NAS_EMM_GLO_AD_GetDetMode()         = NAS_EMM_DETACH_MODE_NOT_SWITCH_OFF;

    return;
}


VOS_UINT32  NAS_EMM_IntraDetReqChk(const NAS_LMM_INTRA_DETACH_REQ_STRU *pMsgMsg)
{
    /*消息内容检查*/
    if (ID_NAS_LMM_INTRA_DETACH_REQ == pMsgMsg->ulMsgId)
    {
        return  NAS_EMM_PARA_VALID;
    }
    else
    {
        return  NAS_EMM_PARA_INVALID;
    }
}


VOS_VOID  NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_ENUM_UINT32 ulAppRslt  )
{
    if (VOS_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_DETACH_REQ))
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_SendDetRslt: Send LMM_MMC_DETACH_CNF");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SendDetRslt_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_AppSendDetCnf(ulAppRslt);
    }
    else
    {
        NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
        #endif
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetDetachType
 Description     : 编码DETACH REQ消息时，获取DETACH TYPE

         用户DetachType                   UE MODE
                                PS                      CS+PS
         EPS detach             EPS DETACH              EPS DETACH
         IMSI detach            在预处理里已处理        IMSI DETACH
         EPS/IMSI detach        EPS DETACH              EPS DETACH(当注册域为PS);
                                                        EPS/IMSI DETACH(当注册域为其他)

 Input           : 无
 Output          : 无
 Return          : MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32

 History         :
    1.lihong00150010      2011-09-29  Draft Enact

*****************************************************************************/
MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 NAS_EMM_GetDetachType( VOS_VOID )
{
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  enDetachType = MMC_LMM_MO_DETACH_TYPE_BUTT;

    /* 获取用户请求的DETACH类型 */
    enDetachType = NAS_EMM_GLO_AD_GetDetTypeMo();

    /* 如果UE模式为PS，则返回类型为EPS ONLY */
    if (NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        return MMC_LMM_MO_DET_PS_ONLY;
    }

    /* 如果用户请求的DETACH类型不为EPS/IMSI，则返回用户请求的DETACH类型 */
    if (MMC_LMM_MO_DET_CS_PS != enDetachType)
    {
        return enDetachType;
    }

    /*如果用户请求的是EPS/IMSI DETACH，且当前注册域为PS，则返回EPS ONLY;如果当前
      注册域为CS+PS，则返回EPS/IMSI;如果当前注册域为NULL，则暂时暂时先返回EPS/IMSI，
      不再考虑UE是否被原因值#2拒绝过，也不考虑在收到DETACH消息之前用户是否允许在CS域注册 */
    if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        return MMC_LMM_MO_DET_PS_ONLY;
    }
    else
    {
        return MMC_LMM_MO_DET_CS_PS;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetSwitchOffDetachType
 Description     : 当为关机类型的DETACH时，获取DETACH TYPE

 Input           : 无
 Output          : 无
 Return          : MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32

 History         :
    1.lihong00150010      2012-02-02  Draft Enact

*****************************************************************************/
MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 NAS_EMM_GetSwitchOffDetachType( VOS_VOID )
{
    VOS_UINT32                          ulCurEmmStat;

    /*如果用户请求的是EPS/IMSI DETACH，且当前注册域为PS，则返回EPS ONLY;如果当前
      注册域为CS+PS，则返回EPS/IMSI;如果当前注册域为NULL时，目前只有注册过程中的
      三种状态会发送关机DETACH消息，因此根据ATTACH类型来填写DETACH类型*/
    if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        return MMC_LMM_MO_DET_PS_ONLY;
    }

    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        return MMC_LMM_MO_DET_CS_PS;
    }

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    if ((ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(    EMM_MS_REG_INIT,
                                                        EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
        && (ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_REG_INIT,
                                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF))
        && (ulCurEmmStat != NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_REG_INIT,
                                                        EMM_SS_ATTACH_WAIT_RRC_DATA_CNF)))
    {
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_GetSwitchOffDetachType:Illegal state!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_GetSwitchOffDetachType_ENUM,LNAS_ERROR);

        return MMC_LMM_MO_DET_PS_ONLY;
    }

    /* 如果是ATTACH过程中的关机，则根据ATTACH类型填写DETACH类型 */
    if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType())
    {
        return MMC_LMM_MO_DET_CS_PS;
    }
    else
    {
        return MMC_LMM_MO_DET_PS_ONLY;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_CompCnDetachReqMoNasMsg
 Description     : 为规避PC-LINT检查数组越界的问题，独立出来一个打包CN消息的函数
 Input           : pulIndex
 Output          : pucCnMsg
                   pulIndex
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-2  Draft Enact
    1.z00148421   2009-12-09  09Q1-CR40:DETACH REQ消息
    3.l00150010   2012-12-13  Modify:Emergency
*****************************************************************************/
VOS_VOID    NAS_EMM_CompCnDetachReqMoNasMsg(    VOS_UINT8      *pucCnMsg,
                                                VOS_UINT32     *pulIndex)
{
    VOS_UINT32                          ulIndex      = 0;
    VOS_UINT8                           ucKsi;
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  enDetachType = MMC_LMM_MO_DETACH_TYPE_BUTT;
    VOS_UINT32                          ulLen        = 0;

    ulIndex                             = *pulIndex;

    /* 填充 Protocol Discriminator + Security header type*/
    pucCnMsg[ulIndex++]                 = EMM_CN_MSG_PD_EMM;

    /* 填充 Detach request message identity */
    pucCnMsg[ulIndex++]                 = NAS_EMM_CN_MT_DETACH_REQ_MT;

    /*填充Detach type*/
    if (NAS_EMM_DETACH_MODE_SWITCH_OFF == NAS_EMM_GLO_AD_GetDetMode())
    {
        enDetachType = NAS_EMM_GetSwitchOffDetachType();
    }
    else
    {
        enDetachType = NAS_EMM_GetDetachType();
    }
    pucCnMsg[ulIndex]                   = (VOS_UINT8)(NAS_EMM_GLO_AD_GetDetMode() |
                                                      enDetachType);
    /*填充KSIasme*/
    ucKsi = NAS_EMM_SecuGetKSIValue();
    pucCnMsg[ulIndex++] |= (ucKsi & 0x0F)<<4;

    /*填充GUTI或IMSI*/
    if (NAS_EMM_AD_BIT_SLCT             == NAS_EMM_GLO_AD_OP_GUTI())
    {
        /*填充GUTI*/
        /*============ GUTI ============ begin */
        pucCnMsg[ulIndex++]             = NAS_EMM_GLO_AD_GetLen();
        pucCnMsg[ulIndex++]             =(NAS_EMM_GLO_AD_GetOeToi()|NAS_EMM_HIGH_HALF_BYTE_F);/* [false alarm]:代码保证了不会越界 */

        NAS_LMM_MEM_CPY_S(  &(pucCnMsg[ulIndex]),
                            NAS_EMM_AD_LEN_PLMN_ID,
                            NAS_EMM_GLO_AD_GetGutiPlmn(),
                            NAS_EMM_AD_LEN_PLMN_ID);

        ulIndex                         += NAS_EMM_AD_LEN_PLMN_ID;
        pucCnMsg[ulIndex++]             = NAS_EMM_GLO_AD_GetMmeGroupId();/* [false alarm]:代码保证了不会越界 */
        pucCnMsg[ulIndex++]             = NAS_EMM_GLO_AD_GetMMeGroupIdCnt();/* [false alarm]:代码保证了不会越界 */
        pucCnMsg[ulIndex++]             = NAS_EMM_GLO_AD_GetMMeCode();/* [false alarm]:代码保证了不会越界 */

        NAS_LMM_MEM_CPY_S(  &(pucCnMsg[ulIndex]),
                            sizeof(NAS_MM_MTMSI_STRU),
                            NAS_EMM_GLO_AD_GetMTmsiAddr(),
                            sizeof(NAS_EMM_MTMSI_STRU));
        ulIndex                         += sizeof(NAS_EMM_MTMSI_STRU);


        /*============ GUTI ============ end */
    }
    else if (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_IMSI())
    {
        /*填充IMSI*/
        /*============ IMSI ============ begin */

        NAS_LMM_MEM_CPY_S(  &(pucCnMsg[ulIndex]),
                            NAS_EMM_AD_LEN_CN_MSG_IMSI,
                            NAS_EMM_GLO_AD_GetImsi(),
                            NAS_EMM_AD_LEN_CN_MSG_IMSI);

        ulIndex                         += NAS_EMM_AD_LEN_CN_MSG_IMSI;
        /*============ IMSI ============ end */

    }
    else
    {
        NAS_EMM_CompImei(&(pucCnMsg[ulIndex]),&ulLen);
        ulIndex                         += ulLen;
    }
    *pulIndex = ulIndex;

    return;

}



/*****************************************************************************
 Function Name  : Nas_Emm_CompCnDetachReqMo
 Discription    : 构造CN消息(Compose the msg of): DETACH_REQUEST
 Input          :
 Output         : None
 Return         : None
 History:
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化

*****************************************************************************/
VOS_VOID    NAS_EMM_CompCnDetachReqMo(  NAS_EMM_MRRC_DATA_REQ_STRU *pDetReqMoMsg)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulDataReqLenNoHeader;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pTempDetReqMsg = pDetReqMoMsg;

    if (NAS_EMM_NULL_PTR == pDetReqMoMsg)
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_CompCnDetachReqMo: Mem Alloc Err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompCnDetachReqMo_ENUM,LNAS_NULL_PTR);
        return;
    }

    ulIndex = 0;
    /*计算DETACH REQ空口消息*/
    NAS_EMM_CompCnDetachReqMoNasMsg(pTempDetReqMsg->stNasMsg.aucNasMsg, &ulIndex);

    /*内部消息长度计算*/
    ulDataReqLenNoHeader             = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqLenNoHeader )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_CompCnDetachReqMo, Size error");
        return ;
    }

    /*填充消息长度*/
    pTempDetReqMsg->stNasMsg.ulNasMsgSize    = ulIndex;

    /*填充消息头*/
    NAS_EMM_COMP_AD_INTRA_MSG_HEADER(pTempDetReqMsg, ulDataReqLenNoHeader);

    /*填充消息ID*/
    pTempDetReqMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    pTempDetReqMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NEED;

    /*填充消息内容*/
    pTempDetReqMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pTempDetReqMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pTempDetReqMsg->enEmmMsgType             = NAS_EMM_MSG_DETACH_REQ;

    return;
}



/*****************************************************************************
 Function Name   :  NAS_EMM_MrrcSendDetReqMo
 Description     :  向MRRC发送NAS_EMM_MRRC_DATA_REQ(DETACH REQUEST)消息

 Input           :
 Output          :
 Return          : None

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化

*****************************************************************************/
VOS_VOID    NAS_EMM_MrrcSendDetReqMo()
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pIntraMsg;
    NAS_MSG_STRU                        *pstNasMsg;
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  enDetachType = MMC_LMM_MO_DETACH_TYPE_BUTT;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MrrcSendDetReqMo is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MrrcSendDetReqMo_ENUM,LNAS_ENTRY);

    /*以最小消息长度，申请消息内存,主要是看是否队列有空间*/
    pIntraMsg = (VOS_VOID *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /*构造发向网侧的DETACH REQUEST 消息*/
    NAS_EMM_CompCnDetachReqMo(pIntraMsg);

    /* 如果是联合TAU，则通知MM进入MM IMSI DETACH PENDING状态 */
    enDetachType = NAS_EMM_GetDetachType();
    if ((NAS_EMM_DETACH_MODE_NOT_SWITCH_OFF == NAS_EMM_GLO_AD_GetDetMode())
        && ((MMC_LMM_MO_DET_CS_PS == enDetachType)
            || (MMC_LMM_MO_DET_CS_ONLY == enDetachType)))
    {
        NAS_EMM_SendMmCombinedStartNotifyReq(MM_LMM_COMBINED_DETACH);
    }

    /*向OM发送空口消息DETACH REQUEST*/
    pstNasMsg = (NAS_MSG_STRU *)(&(pIntraMsg->stNasMsg));
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_DETACH_REQ_MO, pstNasMsg);
    NAS_LMM_SendOmtKeyEvent(             EMM_OMT_KE_DETACH_REQ_MO);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送begin notify消息给RRC，通知RRC申请资源*/
    NAS_LMM_SendRrcDsdsBeginNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*向MRRC发送DETACH REQUEST 消息*/
    NAS_EMM_SndUplinkNasMsg(            pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);
    return;

}
/*****************************************************************************
 Function Name   : NAS_EMM_SendImsiDetachReqMo
 Description     : 发起IMSI DETACH流程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010       2011-09-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SendImsiDetachReqMo( VOS_VOID )
{
    NAS_LMM_FSM_STATE_STRU               stEmmState;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SendImsiDetachReqMo is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendImsiDetachReqMo_ENUM,LNAS_ENTRY);

    /*启动定时器T3421*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3421);

    /*修改状态：进入主状态EMM_MS_REG子状态EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF*/
    stEmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    stEmmState.enMainState                = EMM_MS_REG;
    stEmmState.enSubState                 = EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF;
    stEmmState.enStaTId                   = TI_NAS_EMM_T3421;
    NAS_LMM_StaTransProc(stEmmState);

    /*向MRRC发送DETACH REQUEST消息*/
    NAS_EMM_MrrcSendDetReqMo();

    return;
}

VOS_VOID  NAS_EMM_SendDetachReqMo(VOS_VOID)
{

    NAS_LMM_FSM_STATE_STRU               stEmmState;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SendDetachReqMo is enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendDetachReqMo_ENUM,LNAS_ENTRY);


    /*启动定时器T3421*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3421);

    /*修改状态：进入主状态DEREG_INIT子状态DETACH_WAIT_CN_DETACH_CNF*/
    stEmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    stEmmState.enMainState                = EMM_MS_DEREG_INIT;
    stEmmState.enSubState                 = EMM_SS_DETACH_WAIT_CN_DETACH_CNF;
    stEmmState.enStaTId                   = TI_NAS_EMM_T3421;
    NAS_LMM_StaTransProc(stEmmState);

    /*向MRRC发送DETACH REQUEST消息*/
    NAS_EMM_MrrcSendDetReqMo();
    return;
}
/*****************************************************************************
 Function Name   :  NAS_EMM_RrcRelCauseCnDetachSrcClrAttemptToAtt
 Description     : Cn的detach请求，连接释放，没有原因值和原因为Others的处理

 Input           :
 Output          :
 Return          : None

 History         :
    1.zhengjunyan 00148421 2009.05.08 New Draft
    2.zhengjunyan 00148421 2009.10.20 Mod:stDestState.enStaTId不能赋值PTL定时器，
                                      会导致打印状态转换错误。
*****************************************************************************/
VOS_VOID NAS_EMM_RrcRelCauseCnDetachSrcClrAttemptToAtt(VOS_VOID)
{
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_RrcRelCauseCnDetachSrcClrAttemptToAtt is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcRelCauseCnDetachSrcClrAttemptToAtt_ENUM,LNAS_ENTRY);

    /*delete list of equivalent PLMNs, */
    /*NAS_EMM_INFO_DELETE_EPLMN_LIST();*/

    /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
    /*shall set the update status to EU2 NOT UPDATED */
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

    /*删除GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*and shall start timer T3402. */
    NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendDetachForPowerOffReq
 Description     : DETACH模块提供给其他模块的关机DETACH接口
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-2-20  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_SendDetachForPowerOffReq(VOS_VOID)
{
    /* 设置DETACH类型为关机DETACH */
    NAS_EMM_GLO_AD_GetDetMode()         = NAS_EMM_DETACH_MODE_SWITCH_OFF;

    /* 向MRRC发送DETACH REQUEST消息 */
    NAS_EMM_MrrcSendDetReqMo();
}

/*****************************************************************************
 Function Name   : NAS_EMM_DetProcEnterForbTA
 Description     : DeregInit.WtDetCnf状态下收到SYS_INFO，且携带禁止信息，终止DETACH
                   流程，释放连接
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421     2010-10-25  Draft Enact
    2.lihong 00150010          2012-12-17  Modify:Emergency

*****************************************************************************/
VOS_VOID    NAS_EMM_DetProcEnterForbTA(VOS_VOID)
{
    /* 终止DETACH流程*/
    NAS_LMM_StopStateTimer(           TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        /*状态转换，通知MMC卡无效*/
        NAS_EMM_ProcLocalNoUsim();
    }
    else
    {
        /* 状态迁移:Dereg.Limite_Service*/
        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
        /* 本地DETACH*/
        NAS_LMM_DeregReleaseResource();
    }

    /*向MMC发送LMM_MMC_DETACH_CNF消息*/
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    NAS_EMM_RelReq(                  NAS_LMM_NOT_BARRED);

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ImsiDetProcEnterForbTA
 Description     : REG.IMSI_DETACH_INIT状态下收到SYS_INFO，且携带禁止信息，终止DETACH
                   流程，释放链路
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010     2011-10-18  Draft Enact
    2.lihong00150010     2012-12-19  Modify:Emergency

*****************************************************************************/
VOS_VOID    NAS_EMM_ImsiDetProcEnterForbTA( VOS_VOID )
{
    /* 终止DETACH流程*/
    NAS_LMM_StopStateTimer(           TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* 设置注册域为PS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                EMM_SS_REG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*向MMC发送LMM_MMC_DETACH_CNF消息*/
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* IMSI DETACH后释放资源 */
    NAS_LMM_ImsiDetachReleaseResource();

    NAS_EMM_RelReq(                  NAS_LMM_NOT_BARRED);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705    2009-9-30  Draft Enact
    2.Z00148421    2010-11-16 MOD:修改DATA_ABSENT的处理，直接本地DETACH
    3.Z00148421    2010-12-23 DTS2010111701490:LOAD_BALANCE_REQ原因值
                              不立即触发TAU，收到SYS_INFO_IND再触发。
    4.Z00148421    2011-02-22 DTS2011022203339:不区分释放原因值，完成本地DETACH
    5.l00150010    2012-12-17 Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd( VOS_UINT32 ulCause)
{
    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)(                             ulCause);

    /*停止定时器T3421*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
     NAS_EMM_EsmSendStatResult(       EMM_ESM_ATTACH_STATUS_DETACHED);
    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        NAS_EMM_DETACH_LOG_NORM("NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd: No USIM");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_ProcLocalNoUsim();

        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
        NAS_EMM_CommProcConn2Ilde();

        return;
    }

    /* 有卡，不区分释放原因值，完成本地DETACH*/

    /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgInitSsWtCnDetCnfMsgRrcRelInd
 Description     : 主状态DEREG_INIT+子状态DETACH_WAIT_CN_DETACH_CNF下收到RRC_REL_IND

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.X00148705              2009-09-30  重构

*****************************************************************************/

VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgRrcRelInd(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru)
{

    LRRC_LMM_REL_IND_STRU                 *pMsgRrcRelInd  = (LRRC_LMM_REL_IND_STRU *)pMsgStru;
    VOS_UINT32                          ulCause;

    (VOS_VOID)(ulMsgId);
    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgRrcRelInd_ENUM,LNAS_ENTRY);

    /*获得原因值*/
    ulCause                                             =   pMsgRrcRelInd->enRelCause;

    NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd(          ulCause);

    return   NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd
 Description     : 主状态EMM_MS_REG+子状态EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF下收到MRRC的
                   INTRA-CONNECT-FAIL-IND消息
 Input           : ulMsgId--------------------消息ID
                   pMsgStru-------------------消息指针
 Return          : VOS_UINT32

 History         :
    1.lihong  00150010  2011.09.27  New Draft
*****************************************************************************/
VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU         *pMrrcConnectFailInd = NAS_EMM_NULL_PTR;

    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd is entered",
                                                ulMsgId,
                                                pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd_ENUM,LNAS_ENTRY,
                                                ulMsgId,
                                                pMsgStru);
    pMrrcConnectFailInd = (NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *)pMsgStru;

    /*check the input ptr*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd: NULL PTR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*check current state*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF))
    {
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*停止定时器T3421*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* 设置注册域为PS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    /*修改状态：进入主状态REG子状态EMM_SS_REG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    if ((LRRC_EST_ACCESS_BARRED_MO_SIGNAL == pMrrcConnectFailInd->enEstResult) ||
        (LRRC_EST_ACCESS_BARRED_ALL == pMrrcConnectFailInd->enEstResult))
    {
        /*向MMC发送LMM_MMC_DETACH_CNF消息*/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_ACCESS_BARED);
    }
    else
    {
        /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
    }

    /* IMSI DETACH后释放资源 */
    NAS_LMM_ImsiDetachReleaseResource();

    /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
    NAS_EMM_CommProcConn2Ilde();

    return   NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd
 Description     : 主状态DEREG_INIT+子状态DETACH_WAIT_CN_DETACH_CNF下收到MRRC的
                   INTRA-CONNECT-FAIL-IND消息
 Input           :
 Return          :
 History         :
    1.zhengjunyan  00148421 2009.03.17 New Draft
    2.zhengjunyan  00148421 2010-11-16 添加:通知ESM DETACHED
    3.lihong       00150010 2012-12-17 Modify:Emergency
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru)
{

    NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU         *pMrrcConnectFailInd = NAS_EMM_NULL_PTR;

    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd is entered",
                                                ulMsgId,
                                                pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd_ENUM,LNAS_ENTRY,
                                                ulMsgId,
                                                pMsgStru);
    pMrrcConnectFailInd = (NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *)pMsgStru;
    /*check the input ptr*/
    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd: NULL PTR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*check current state*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF))
    {
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*停止定时器T3421*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);
    if (VOS_TRUE != NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /*NAS_EMM_ProcLocalNoUsim();*/
        /*修改状态：进入主状态DEREG子状态DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(             EMM_MS_DEREG,
                                            EMM_SS_DEREG_NO_IMSI,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /* 给MMC回复LMM_MMC_USIM_STATUS_CNF */
        NAS_EMM_SendMmcUsimStatusCnf();
        /* 清除拔卡标识 */
        NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_FALSE;
    }

    if ((LRRC_EST_ACCESS_BARRED_MO_SIGNAL == pMrrcConnectFailInd->enEstResult) ||
        (LRRC_EST_ACCESS_BARRED_ALL == pMrrcConnectFailInd->enEstResult))
    {
        /*向MMC发送LMM_MMC_DETACH_CNF消息*/
        /*NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_ACCESS_BARED);*/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_ACCESS_BARED);
    }
    else
    {
        /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
        /*NAS_EMM_MmcSendDetIndLocal();*/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
    }

   /* 本地DETACH释放资源:动态内存、赋初值 */
   NAS_LMM_DeregReleaseResource();

   /*send INTRA_CONN2IDLE_REQ，更新连接状态*/
   NAS_EMM_CommProcConn2Ilde();
   return   NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp
 Description     : 主状态DEREG_INIT+子状态DETACH_WAIT_CN_DETACH_CNF下收到定时器
                   T3421超时

 Input           : ulMsgId--------------------消息ID
                   pMsgStru-------------------消息指针
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2011-09-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp",
                                                    ulMsgId,
                                                    pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp_ENUM,LNAS_ENTRY,
                                                    ulMsgId,
                                                    pMsgStru);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*Detach attempt counter加1*/
    NAS_EMM_GLO_AD_GetDetAtmpCnt()++;

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*判断Detach attempt counter，分为小于5和大于等于5处理*/
    if (NAS_EMM_GLO_AD_GetDetAtmpCnt() < 5)
    {
        /*发送DETACH REQUEST消息*/
        NAS_EMM_SendImsiDetachReqMo();

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp 5 times");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp_ENUM,LNAS_FUNCTION_LABEL1);

    NAS_EMM_GLO_AD_GetDetAtmpCnt()  = 0;

    /* 设置注册域为PS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    /* 如果当前是数据连接态，则直接转到REG+NORMAL_SERVIC态，否则待释放RRC链路
       后再转到REG+NORMAL_SERVIC态 */
    if (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
    {
        NAS_EMM_AdStateConvert(             EMM_MS_REG,
                                            EMM_SS_REG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /* IMSI DETACH后释放资源 */
        NAS_LMM_ImsiDetachReleaseResource();

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_AdStateConvert( EMM_MS_REG,
                            EMM_SS_REG_NORMAL_SERVICE,
                            TI_NAS_EMM_STATE_NO_TIMER);

    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp
 Description     : 主状态DEREG_INIT+子状态DETACH_WAIT_CN_DETACH_CNF下收到定时器
                   T3421超时

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.lihong00150010         2012-12-17  Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp( VOS_UINT32  ulMsgId,
                                                      VOS_VOID   *pMsgStru )
{
    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp",
                                                    ulMsgId,
                                                    pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp_ENUM,LNAS_ENTRY,
                                                    ulMsgId,
                                                    pMsgStru);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*Detach attempt counter加1*/
    NAS_EMM_GLO_AD_GetDetAtmpCnt()++;

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*判断Detach attempt counter，分为小于5和大于等于5处理*/
    if (NAS_EMM_GLO_AD_GetDetAtmpCnt() < 5)
    {
        /*发送DETACH REQUEST消息*/
        NAS_EMM_SendDetachReqMo();
    }
    else
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp 5 times");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp_ENUM,LNAS_FUNCTION_LABEL1);

        /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
        NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);
        if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
        {
            /*状态转换，通知MMC卡无效*/
            NAS_EMM_ProcLocalNoUsim();
        }
        else
        {
            NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                    EMM_SS_DEREG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        }
        NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

        /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
        NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    }
    return  NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DetachToTAU
 Description     : 提供给TAU调用的函数

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_DetachToTAU()
{
    /*停止定时器T3421*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*修改状态：进入主状态REG子状态REG_NORMAL_SERVICE*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

   return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsRegNmlSrvMsgTauIntraMsgDetReq
 Description     : 收到TAU发送的内部消息DETACH REQUEST

 Input           :

 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    NAS_LMM_INTRA_DETACH_REQ_STRU              *pRcvEmmMsg;
    pRcvEmmMsg                          = (NAS_LMM_INTRA_DETACH_REQ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_DETACH_LOG1_INFO("NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq is entered", ulMsgId);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq_ENUM,LNAS_ENTRY,ulMsgId);


     /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查,若有错，打印并退出*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_IntraDetReqChk(pRcvEmmMsg))
    {
        NAS_EMM_DETACH_LOG_ERR("NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq: MMC_MM_SYS_INFO_IND_STRU para err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 如果是IMSI DETACH类型，则发起IMSI DETACH流程 */
    if (MMC_LMM_MO_DET_CS_ONLY == NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq:Proceed Imsi Detach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq_ENUM,LNAS_FUNCTION_LABEL1);

        /* IMSI detach被TAU打断，如果TAU ACCEPT是Ta Updated Only，原因值为#2或者#18
           也会进入NORMAL_SERVICE，发送内部DETACH请求，这时不应该再发起IMSI DETACH流程*/
        if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
            /*向APP发送DETACH成功*/
            NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

            /* IMSI DETACH后释放资源 */
            NAS_LMM_ImsiDetachReleaseResource();

            return  NAS_LMM_MSG_HANDLED;
        }

        /* 发起IMSI DETACH流程 */
        NAS_EMM_SendImsiDetachReqMo();
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_DETACH_LOG_INFO("NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq:Proceed EPS Detach or EPS/IMSI Detach");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq_ENUM,LNAS_FUNCTION_LABEL2);

    /* 如果3411在运行，需要给MMC报TAU结果，以让MMC退出搜网状态机；3402定时器在
       运行无需通知，MMC收到TAU结果尝试次数为5时，已退出搜网状态机 */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        NAS_EMM_SetTauTypeNoProcedure();

        ulTauRslt = MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE;
        NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

    }

    /*停止定时器*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3411);
    NAS_LMM_Stop3402Timer();

    /*发送DETACH REQUEST消息*/
    NAS_EMM_SendDetachReqMo();

    return   NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DetGuAttachRst
 Description     : 挂起状态下，处理GU发来的DETACH结果
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Hanlufeng 41410      2011-5-12  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_DetGuAttachRst( VOS_VOID * pMsg )
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pMmcActResult;


    pMmcActResult = (MMC_LMM_ACTION_RESULT_REQ_STRU *)pMsg;


    NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_DetGuAttachRst: ulActRst =.",
                            pMmcActResult->ulActRst);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_DetGuAttachRst_ENUM,LNAS_ACT_RESULT,pMmcActResult->ulActRst);

    /* 若非PS相关的，暂时丢弃，待联合操作时再考虑 */
    if(MMC_LMM_IMSI_ONLY == pMmcActResult->ulRstDomain)
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_DetGuAttachRst: ulRstDomain =.",
                            pMmcActResult->ulRstDomain);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_DetGuAttachRst_ENUM,LNAS_EMM_REG_DOMAIN,pMmcActResult->ulRstDomain);
        return;
    }

    /* DETACH 无论成功失败，都认为去注册完成 */
    NAS_EMM_AdStateConvert(         EMM_MS_DEREG,
                                    EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                    TI_NAS_EMM_STATE_NO_TIMER);


    /* 通知ESM状态改变 */
    NAS_EMM_PUB_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgEsmDataReq
 Description     : 主状态REG+子状态IMSI_DETACH_INIT下收到ESM
                   EMM_ESM_DATA_REQ消息

 Input           : ulMsgId--------------------消息ID
                   pMsgStru-------------------消息指针
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2011-09-27  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgEsmDataReq",
                                                            ulMsgId,
                                                            pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgEsmDataReq_ENUM,LNAS_ENTRY,
                                                            ulMsgId,
                                                            pMsgStru);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgEsmDataReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgEsmDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    if (VOS_TRUE == pstEsmDataReq->ulIsEmcType)
    {
        NAS_LMM_SetEmmInfoIsEmerPndEsting(VOS_TRUE);
    }

    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmDataReq->stEsmMsg, pstEsmDataReq->ulOpId);
    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgTcDataReq
 Description     : 主状态REG+子状态IMSI_DETACH_INIT下收到ETC
                   EMM_ETC_DATA_REQ消息

 Input           : ulMsgId--------------------消息ID
                   pMsgStru-------------------消息指针
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2011-09-27  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgTcDataReq",
                                                            ulMsgId,
                                                            pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgTcDataReq_ENUM,LNAS_ENTRY,
                                                            ulMsgId,
                                                            pMsgStru);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgTcDataReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgTcDataReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    NAS_EMM_SER_SendMrrcDataReq_Tcdata((EMM_ETC_DATA_REQ_STRU *)pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRabmRelReq
 Description     : 主状态REG+子状态IMSI_DETACH_INIT下收到RABM
                   EMM_RABM_REL_REQ消息

 Input           : ulMsgId--------------------消息ID
                   pMsgStru-------------------消息指针
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010         2011-09-27  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_DETACH_LOG2_INFO("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRabmRelReq",
                                                            ulMsgId,
                                                            pMsgStru);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRabmRelReq_ENUM,LNAS_ENTRY,
                                                            ulMsgId,
                                                            pMsgStru);
    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_DETACH_LOG_WARN("NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRabmRelReq: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRabmRelReq_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*停止定时器T3421*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /* 设置注册域为PS */
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
    /*向MMC发送LMM_MMC_DETACH_CNF消息*/
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* IMSI DETACH后释放资源 */
    NAS_LMM_ImsiDetachReleaseResource();

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return  NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndDetachReqFailProc
 Description     : DETACH REQ发送失败时的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndDetachReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;

    *pulIsDelBuff = VOS_TRUE;

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    if ((EMM_MS_DEREG_INIT != NAS_LMM_GetEmmCurFsmMS())
        && ((EMM_MS_REG != NAS_LMM_GetEmmCurFsmMS())
             && (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF != NAS_LMM_GetEmmCurFsmSS()))
        && ((EMM_MS_NULL != NAS_LMM_GetEmmCurFsmMS())
             && (EMM_SS_NULL_WAIT_SWITCH_OFF!= NAS_LMM_GetEmmCurFsmSS())))
    {
        /*打印出错信息*/
        NAS_EMM_SER_LOG_INFO("NAS_EMM_SndExtendedServiceReqFailProc: STATE ERR!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndDetachReqFailProc_ENUM,LNAS_ERROR);
        return  NAS_EMM_SUCC;
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            if (EMM_MS_DEREG_INIT == NAS_LMM_GetEmmCurFsmMS())
            {
                NAS_LMM_StopStateTimer(         TI_NAS_EMM_T3421);

                /*发送DETACH REQUEST消息*/
                NAS_EMM_SendDetachReqMo();
            }

            else if (EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
            {
                NAS_LMM_StopStateTimer(         TI_NAS_EMM_T3421);

                /* 发起IMSI DETACH流程 */
                NAS_EMM_SendImsiDetachReqMo();
            }
            else if (EMM_MS_NULL == NAS_LMM_GetEmmCurFsmMS())
            {
                /* 发送detach for power off req消息 */
                NAS_EMM_SendDetachForPowerOffReq();
            }
            else
            {
            }

            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case LRRC_LMM_SEND_RSLT_NO_RF:
             /* 如果是NO_RF的情况，则直接进行本地DETACH */
             if (EMM_MS_DEREG_INIT == NAS_LMM_GetEmmCurFsmMS())
             {
                /*停止定时器T3421*/
                NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3421);

                NAS_EMM_GLO_AD_GetDetAtmpCnt()  = 0;

                /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
                NAS_EMM_EsmSendStatResult(          EMM_ESM_ATTACH_STATUS_DETACHED);

                /* 通知ESM清除所有EHRPD承载记录 */
                NAS_EMM_SndEsmClearAllClBearerNotify();

                if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
                {
                    NAS_EMM_ProcLocalNoUsim();
                }
                else
                {
                    NAS_EMM_AdStateConvert( EMM_MS_DEREG,
                                            EMM_SS_DEREG_NORMAL_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);
                }

                NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
                NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

                /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
                NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

             }
             else if (EMM_MS_NULL == NAS_LMM_GetEmmCurFsmMS())
             {
                 /*sunbing 00265702/yanglei 关机定时器没有停 begin for DTS2015092904078*/
                 /* 停止关机定时器 */
                 NAS_LMM_StopPtlTimer( TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);
                 /*sunbing 00265702/yanglei 关机定时器没有停 end for DTS2015092904078*/

                 /* 本地关机 */
                 NAS_EMM_ProcLocalStop();
             }
             else
             {
             }
        #endif
        default:
            break;
        }

    return NAS_EMM_SUCC;
}

/* sunbing 00265702 begin for DTS2015100600547 关机不等网络释放*/
/*****************************************************************************
 Function Name   : NAS_EMM_SndDetachReqSuccProc
 Description     : DETACH REQ发送成功时的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : sunbing 00265702   2015-10-07  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndDetachReqSuccProc(VOS_VOID* pMsg)
{
    /*关机状态下，只要网络受到detach请求，则直接走关机流程，不用等网络的释放*/
    if ((EMM_MS_NULL == NAS_LMM_GetEmmCurFsmMS())
      &&(EMM_SS_NULL_WAIT_SWITCH_OFF == NAS_LMM_GetEmmCurFsmSS()))
    {
        /* 停止TI_NAS_EMM_PTL_SWITCH_OFF_TIMER */
        NAS_LMM_StopPtlTimer(               TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*发送end notify消息给RRC，通知RRC释放资源*/
        NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
        #endif

        NAS_EMM_ProcLocalStop();
    }

    return NAS_EMM_SUCC;
}
/* sunbing 00265702 end for DTS2015100600547 关机不等网络释放*/


/*****************************************************************************
 Function Name   : NAS_EMM_SndMtDetachAccFailProc
 Description     : MT DETACH ACP发送失败时的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndMtDetachAccFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    *pulIsDelBuff = VOS_TRUE;

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    ulRrcMmDataReqMsgLen = sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                           pEmmMrrcMgmtData->ulNasMsgLength -
                           NAS_EMM_4BYTES_LEN;
    /* 申请消息内存*/
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)((VOS_VOID*)NAS_LMM_MEM_ALLOC(ulRrcMmDataReqMsgLen));

    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SndMtDetachAccFailProc: Mem Alloc Fail");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndMtDetachAccFailProc_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            if (NAS_EMM_MAX_MT_DETACH_ACC_TX_NUM > NAS_EMM_GLO_AD_GetMtDetachAccTxCnt())
            {
                NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() ++;

                pMrrcDataMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

                pMrrcDataMsg->enEmmMsgType = NAS_EMM_MSG_DETACH_ACP;
                pMrrcDataMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
                pMrrcDataMsg->ulEsmMmOpId = pEmmMrrcMgmtData->ulEsmMmOpId;

                pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;

                NAS_LMM_MEM_CPY_S(  pMrrcDataMsg->stNasMsg.aucNasMsg,
                                    pEmmMrrcMgmtData->ulNasMsgLength,
                                    pEmmMrrcMgmtData->aucNasMsgContent,
                                    pEmmMrrcMgmtData->ulNasMsgLength);

                NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);
            }
            else
            {
                NAS_EMM_GLO_AD_GetMtDetachAccTxCnt() = 0;
            }

            break;

        default:
            break;
        }

    /*释放所申请内存 */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name  : NAS_EMM_SndRrcDetachInd
 Discription    : 给RRC模块发送DETACH IND
 Input          :
 Output         : None
 Return         : None
 History:
      1.  wangchen 00209181 2014-11-14  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_SndRrcDetachInd(VOS_VOID)
{
    LRRC_LMM_DETACH_IND_STRU                *pDetachIndMsg;

    /* 分配内存*/
    pDetachIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_DETACH_IND_STRU));
    if(NAS_EMM_NULL_PTR == pDetachIndMsg)
    {
        /* 打印内存分配失败log */
        NAS_EMM_GIM_ERROR_LOG("LRRC_LMM_DETACH_IND_STRU:Alloc Msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndRrcDetachInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充VOS消息头*/
    NAS_EMM_GIM_RRC_MSG_HEADER(pDetachIndMsg, (sizeof(LRRC_LMM_DETACH_IND_STRU) - NAS_EMM_VOS_HEADER_LEN));

    /*填充消息ID*/
    pDetachIndMsg->enMsgId    = ID_LRRC_LMM_DETACH_IND;

    /*发送ID_LRRC_LMM_DETACH_IND*/
    NAS_LMM_SEND_MSG(pDetachIndMsg);

    return;
}

/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

