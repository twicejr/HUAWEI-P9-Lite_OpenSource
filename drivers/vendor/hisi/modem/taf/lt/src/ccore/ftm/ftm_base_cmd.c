/******************************************************************************

                  版权所有 (C), 1998-2012, 华为技术有限公司

******************************************************************************
  文 件 名   : ftm_base_cmd.c
  版 本 号   : V1.0
  作    者   : l00169177
  生成日期   : 2012-12-24
  功能描述   : 定义终端基线AT命令的实现
               AT^TMODE    LTE&TDS
               AT^BANDSW   LTE
               AT^FCHAN    LTE&TDS
               AT^TSELRF   LTE&TDS
               AT^FWAVE    LTE&TDS
               AT^FLNA     LTE
               AT^FTXON    LTE&TDS
               AT^FRXON    LTE&TDS
               AT^FRSSI    LTE&TDS
               AT^FVCTCXO  LTE

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2012-12-24
    作    者 : l00169177
    修改内容 : 创建文件

  2.日    期 : 2013-08-13
    作    者 : l00169177
    修改内容 : 完善MT工位AT命令 DTS2013081300992
******************************************************************************/

#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
#include "ftm_errno.h"
/*lint -save -e537*/
#include <AppRrcInterface.h>
#include "TafAppMma.h"
/*lint -restore*/
#include "Tds_ps_at.h"

#include "TPsTMspInterface.h"
#include "ftm_mntn.h"
/*lint --e{830,539,525}*/

/*lint -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_BASE_CMD_C
/*lint -e767*/

#if (VOS_OS_VER == VOS_WIN32)
static VOS_BOOL g_PomDspInitIsOK = TRUE;
#else
static VOS_BOOL g_PomDspInitIsOK = FALSE;
#endif

extern VOS_VOID LPHY_SetBTBandInd(VOS_UINT8 ucBand);
extern VOS_VOID LPHY_GetBandStatus(VOS_UINT8 *pucBand, VOS_UINT8 *pucMode);

/*lint -save -e958 -e713 -e718 -e746 -e734*/
/*****************************************************************************
 函数名称: pom_GetDspInitFlg
 功能描述: 返回DSP读写标记

 参数说明:
  NONE

 返 回 值:
    成功：ERR_MSS_SUCCESS: 表示操作成功
    失败：ERR_MSS_INVALID_PARAMETER，ERR_MSS_NO_INITILIZATION， ERR_MSS_UNKNOWN
          操作失败
*****************************************************************************/
/* 记录UE_ROOT函数的返回情况，依此来确保DSP已经初始化成功，*/
/* DRA任务才开始操作DSP邮箱；*/
VOS_BOOL pom_GetDspInitFlg(VOS_VOID)
{
/* 该MSP_SUPPORT_HPA_STUB宏定义定义此处无用*/
#if(VOS_OS_VER == VOS_WIN32)
    g_PomDspInitIsOK = TRUE;
#else

    if( LRRC_COMM_LoadDspAlready() == TRUE)
    {
        g_PomDspInitIsOK = TRUE;
    }
    else
    {
        g_PomDspInitIsOK = FALSE;
    }
#endif
    return g_PomDspInitIsOK;
}
/* E*/

/*****************************************************************************
 函 数 名  : at_ftm_tmode_store
 功能描述  : 保存参数
 输入参数  : ucStoreType 保存类型
               FTM_F_CT_STORE_REQ_TEMP 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数
               FTM_F_CT_STORE_REQ_GLOBAL 收到LRTT确认原语，保存参数，供装备查询
             pstReq  参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOID at_ftm_tmode_store(VOS_UINT8 ucStoreType, SYM_SET_TMODE_REQ_STRU* pstReq)
{
    static SYM_SET_TMODE_REQ_STRU stReq = { 0 };
    SYM_TMODE_ENUM* pSymTmode           = ftm_GetTmodeMainInfo();

    /* 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL!=pstReq))
    {
        stReq.enTmodeMode = pstReq->enTmodeMode;
    }
    /* 收到LRTT确认原语，保存参数，供装备查询 */
    else
    {
        *pSymTmode = stReq.enTmodeMode;
    }
}
/*lint -save -e550 */
/*****************************************************************************
 函 数 名  : at_ftm_bandsw_setcnf
 功能描述  : 返回确认
 输入参数  : ulErrCode 错误码
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
static VOS_UINT32 at_ftm_tmode_setcnf(VOS_UINT32 ulErrCode)
{
    SYM_SET_TMODE_CNF_STRU stSetCnf = { 0 };

    stSetCnf.enTmodeMode   = *ftm_GetTmodeMainInfo();
    stSetCnf.enSymTmodeSta = 1; /* switch mode completely */
    stSetCnf.ulErrCode     = ulErrCode;

    return ftm_comm_send(ID_MSG_SYM_SET_TMODE_CNF,
        (VOS_UINT32)&stSetCnf, sizeof(SYM_SET_TMODE_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_bandsw_read
 功能描述  : ID_MSG_SYM_RD_TMODE_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_tmode_read(VOS_VOID* pParam)
{
    SYM_RD_TMODE_CNF_STRU stRdCnf = { 0 };
    stRdCnf.ulErrCode     = ERR_FTM_SUCCESS;
    stRdCnf.enTmodeMode   = *ftm_GetTmodeMainInfo();
    stRdCnf.enSymTmodeSta = 1; /* switch mode completely */

    return ftm_comm_send(ID_MSG_SYM_RD_TMODE_CNF,
        (VOS_UINT32)&stRdCnf, sizeof(SYM_RD_TMODE_CNF_STRU));
}
/*lint -restore*/

/*****************************************************************************
 函 数 名  : at_ftm_tmode_set
 功能描述  : 设置工作模式
 输入参数  :
 输出参数  :
 返 回 值  :
*****************************************************************************/
extern	VOS_UINT32 TDS_CBT_SetSlaveModeThenMasterMode( VOS_VOID );

extern VOS_UINT32 g_ulTdsDelayLen;
extern 	VOS_VOID TDS_CBT_SetSlaveMode( VOS_VOID );
extern 	VOS_VOID TDS_CBT_SetMasterMode( VOS_VOID );

VOS_UINT32 at_ftm_tmode_set(VOS_VOID* pParam)
{
    SYM_SET_TMODE_REQ_STRU* pstFtmReq = (SYM_SET_TMODE_REQ_STRU*)pParam;
    FTM_SYN_INFO_STRU* pFtmSynINfo    = ftm_GetSynMainInfo();
    SYM_TMODE_ENUM*    pSymTmode      = ftm_GetTmodeMainInfo();
    OM_PHY_CT_TEST_MODE_REQ_STRU stReqDspTmode = {0};
    MSP_PS_AT_MODE_REQ_STRU  stReqPsTm = {0};

    HAL_SDMLOG("\n at_ftm_tmode_set, old tmode: %d, new tmode %d\n", *pSymTmode, pstFtmReq->enTmodeMode);

    switch(pstFtmReq->enTmodeMode)
    {
        case EN_SYM_TMODE_SIGNAL:         //TMODE=0  signaling mode
        {
           *pSymTmode = pstFtmReq->enTmodeMode;
            return at_ftm_tmode_setcnf(ERR_FTM_SUCCESS);
        }

        case EN_SYM_TMODE_NONESIGNAL:     /* TMODE=1  non-signaling mode    */
            /* 设置非信令打开 */
             ftm_SetNoneSig(FTM_NONESIG_RTT_OPEN);
             ftm_SetDefault();
             *pSymTmode = pstFtmReq->enTmodeMode;
             return at_ftm_tmode_setcnf(ERR_FTM_SUCCESS);

        case EN_SYM_TMODE_F_NONESIGNAL:   /* TMODE=13 quick calibration mode */
        case EN_SYM_TMODE_SYN_NONESIGNAL: /* TMODE=14 non-signaling BT mode  */
        {
            /* 检查LRTT的初始化状态 */
            if (pom_GetDspInitFlg() == FALSE)
            {
                return at_ftm_tmode_setcnf(ERR_FTM_INVALID_OP);
            }

            if (ERR_FTM_SUCCESS != LHPA_InitDspNvForLteTdsCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_InitDspNvForLteTdsCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_INVALID_OP);
            }

            if(ERR_FTM_SUCCESS != LHPA_LoadDspForLteCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_LoadDspForLteCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_INVALID_OP);
            }

			TDS_CBT_SetSlaveMode();


            /*  切换LRTT为主模 */
            LHPA_DbgSetSlaveModeThenMasterMode();
            HAL_SDMLOG("\n call LHPA_DbgSetSlaveModeThenMasterMode! \n");
            //VOS_TaskDelay(300);

            /* 发送原语到LRTT，设为非信令模式 */
            stReqDspTmode.ulMsgId = OM_PHY_CT_TEST_MODE_REQ;
            stReqDspTmode.usTMode = pstFtmReq->enTmodeMode;
            if(ERR_FTM_SUCCESS != ftm_mailbox_ltect_write(&stReqDspTmode, sizeof(OM_PHY_CT_TEST_MODE_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ltect_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_UNKNOWN);
            }

            if(EN_SYM_TMODE_SYN_NONESIGNAL == pstFtmReq->enTmodeMode)
            {
                pFtmSynINfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_TMODE_7_REQ;
            }

            at_ftm_tmode_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
            return ERR_FTM_WAIT_ASYNC;
        }

        case EN_SYM_TMODE_COMM_CT: /* TMODE=19 comm non-signaling CT mode  */
        {
            /* 检查LRTT的初始化状态 */
            if (pom_GetDspInitFlg() == FALSE)
            {
                return at_ftm_tmode_setcnf(ERR_FTM_INVALID_OP);
            }

            if(ERR_FTM_SUCCESS != LHPA_LoadDspForLteCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_LoadDspForLteCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_INVALID_OP);
            }

			TDS_CBT_SetSlaveMode();


            /*  切换LRTT为主模 */
            LHPA_DbgSetSlaveModeThenMasterMode();
            HAL_SDMLOG("\n call LHPA_DbgSetSlaveModeThenMasterMode! \n");
            //VOS_TaskDelay(300);

            /* 发送原语到LRTT，设为非信令模式 */
            stReqDspTmode.ulMsgId = OM_PHY_CT_TEST_MODE_REQ;
            stReqDspTmode.usTMode = pstFtmReq->enTmodeMode;
            if(ERR_FTM_SUCCESS != ftm_mailbox_ltect_write(&stReqDspTmode, sizeof(OM_PHY_CT_TEST_MODE_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ltect_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_UNKNOWN);
            }

            at_ftm_tmode_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
            return ERR_FTM_WAIT_ASYNC;
        }

        case EN_SYM_TMODE_TDS_BT:
        {
            /*at^tmode=18 需要通知PS*/
            stReqPsTm.MsgId = ID_T_MSP_PS_AT_MODE_REQ;

            if(ERR_FTM_SUCCESS != atFTMSendVosMsg(TPS_PID_MAC,&stReqPsTm,sizeof(stReqPsTm)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] atFTMSendVosMsg failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_UNKNOWN);
		    }

            if (ERR_FTM_SUCCESS != LHPA_InitDspNvForLteTdsCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_InitDspNvForLteTdsCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_INVALID_OP);
            }

            LHPA_DbgSendSetWorkMode_toSlaveMode();
            (VOS_VOID)VOS_TaskDelay(g_ulTdsDelayLen);

            (VOS_VOID)TDS_CBT_SetSlaveModeThenMasterMode();

            /* 发送原语到DSP，设为非信令模式 */
            stReqDspTmode.ulMsgId = OM_PHY_CT_TEST_MODE_REQ;
            stReqDspTmode.usTMode = pstFtmReq->enTmodeMode;

            /*  MODE  先发送TDS BT ，后面需要兼容LTEBT */
            if(ERR_FTM_SUCCESS != ftm_mailbox_bt_write(EN_FCHAN_MODE_TD_SCDMA, &stReqDspTmode, sizeof(OM_PHY_CT_TEST_MODE_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_bt_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_UNKNOWN);
            }

            /* 参考TMODE=14加的，GETNOSIG 时会判断  与之或结果--待确认 */
            if(EN_SYM_TMODE_TDS_BT == pstFtmReq->enTmodeMode)
            {
                pFtmSynINfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_TMODE_7_REQ;//  ---待确认
            }

            at_ftm_tmode_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
            return ERR_FTM_WAIT_ASYNC;

	    }

        case EN_SYM_TMODE_TDS_FAST_CT:
        {
			//TDS_CBT_SetSlaveModeThenMasterMode();

            if (ERR_FTM_SUCCESS != LHPA_InitDspNvForLteTdsCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_InitDspNvForLteTdsCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_INVALID_OP);
            }

			LHPA_DbgSendSetWorkMode_toSlaveMode();

			(VOS_VOID)VOS_TaskDelay(g_ulTdsDelayLen);

			(VOS_VOID)TDS_CBT_SetSlaveModeThenMasterMode();

            /* 发送原语到LRTT，设为非信令模式 */
            stReqDspTmode.ulMsgId = OM_PHY_CT_TEST_MODE_REQ;
            stReqDspTmode.usTMode = pstFtmReq->enTmodeMode;
            if(ERR_FTM_SUCCESS != ftm_mailbox_ct_write(EN_FCHAN_MODE_TD_SCDMA, &stReqDspTmode, sizeof(OM_PHY_CT_TEST_MODE_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ct_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_FTM_UNKNOWN);
            }
            at_ftm_tmode_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
            return ERR_FTM_WAIT_ASYNC;
        }

        case EN_SYM_TMODE_SIGNAL_NOCARD:  /* TMODE=11 signaling with no card mode */
        {
            *pSymTmode = pstFtmReq->enTmodeMode;
            return at_ftm_tmode_setcnf(ERR_FTM_SUCCESS);
        }


        case EN_SYM_TMODE_SET_SLAVE:      /* TMODE=15 set LTE DSP to slave mode */
        case EN_SYM_TMODE_GU_BT:
        {
            LHPA_DbgSendSetWorkMode_toSlaveMode();
            HAL_SDMLOG("\n call LHPA_DbgSendSetWorkMode_toSlaveMode\n");

            /* delay for mode switch */
            (VOS_VOID)VOS_TaskDelay(300);

            *pSymTmode = pstFtmReq->enTmodeMode;
            return at_ftm_tmode_setcnf(ERR_FTM_SUCCESS);
        }

        case EN_SYM_TMODE_RESET:          /* TMODE=3 */
        {
            *pSymTmode = pstFtmReq->enTmodeMode;
            (VOS_VOID)VOS_TaskDelay(300);
            //BSP_OM_SoftReboot();
        }
            break;

        case EN_SYM_TMODE_LOAD:           /* TMODE=2 */
        case EN_SYM_TMODE_SHUTDOWN:       /* TMODE=4 */
        case EN_SYM_TMODE_OFFLINE:        /* TMODE=12 */
            (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] Error Mode\n", __FUNCTION__, __LINE__,VOS_GetSlice());
            return ERR_FTM_FAILURE;

        default:
            ;
    }

    return ERR_FTM_SUCCESS;
}

/*****************************************************************************
 函 数 名  : at_ftm_tmode_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_tmode_timeout(VOS_VOID)
{
#ifdef BSP_CONFIG_HI3650
    /* 韩磊要求添加此功能方便定位DSP问题，此命令失败一次系统就重启 */
    mdrv_om_system_error(FTM_REBOOT_FTM_ERR, THIS_FILE_ID, __LINE__, 0, 0);
#endif

    return at_ftm_tmode_setcnf(ERR_FTM_OPEN_CHAN_ERROR);
}

/*****************************************************************************
 函 数 名  : at_ftm_tmode_dspcnf
 功能描述  : DSP原语PHY_OM_CT_TEST_MODE_CNF处理函数
 输入参数  : pParam PHY_OM_CT_TEST_MODE_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_tmode_dspcnf(VOS_VOID* pParam)
{
    at_ftm_tmode_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    /* 设置非信令打开 */
    ftm_SetNoneSig(FTM_NONESIG_RTT_OPEN);
    ftm_SetDefault();

    return at_ftm_tmode_setcnf(ERR_FTM_SUCCESS);

}

/*lint -save -e550 -e830*/
/*****************************************************************************
 函 数 名  : at_ftm_fchan_setcnf
 功能描述  : 返回确认
 输入参数  : ulErrCode 错误码
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FCHAN_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode   = ulErrCode;
    stCnf.enFchanMode = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    return ftm_comm_send(ID_MSG_FTM_SET_FCHAN_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FCHAN_CNF_STRU));
}
/*lint -restore +e550 +e830*/

/*****************************************************************************
 函 数 名  : at_ftm_fchan_store
 功能描述  : 保存参数
 输入参数  : ucStoreType 保存类型
               FTM_F_CT_STORE_REQ_TEMP 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数
               FTM_F_CT_STORE_REQ_GLOBAL 收到LRTT确认原语，保存参数，供装备查询
             pstReq  参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
static VOID at_ftm_fchan_store(VOS_UINT8 ucStoreType, FTM_SET_FCHAN_REQ_STRU* pstReq)
{
    static FTM_SET_FCHAN_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    VOS_UINT16 usUlChannel = 65535; /* 上行频点默认为无效值 */
    VOS_UINT16 usDlChannel = 65535; /* 下行频点默认为无效值 */

    /* 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FCHAN_REQ_STRU));
    }
    /* 收到LRTT确认原语，保存参数，供装备查询 */
    else
    {
        pstFCtManageInfo->stCurFchan.enFchanMode = stReq.enFchanMode;
        pstFCtManageInfo->stCurFchan.ucBand      = stReq.ucBand;
        pstFCtManageInfo->stCurFchan.usUlChannel = usUlChannel;
        pstFCtManageInfo->stCurFchan.usDlChannel = usDlChannel;

        ftm_GetMainInfo()->stFtmFastCtInfo.enCurMode = stReq.enFchanMode;

        if(stReq.enFchanMode == EN_FCHAN_MODE_TD_SCDMA)
        {
            /* TDSCDMA上下行频点相等 */
            pstFCtManageInfo->stCurFchan.usUlChannel = stReq.usChannel;/* [false alarm]:fortify */
            pstFCtManageInfo->stCurFchan.usDlChannel = stReq.usChannel;
        }
        else
        {
            /* 上行频点与设置频点相等则保存上行频点，否则上行频点为无效值 */
            usUlChannel = at_ftm_get_ulchan(EN_FCHAN_MODE_FDD_LTE, stReq.usChannel);
            /* coverity[original] */
            if(stReq.usChannel == usUlChannel)
            {
                pstFCtManageInfo->stCurFchan.usUlChannel = usUlChannel;
            }

            /*下行频点与设置频点相等则保存下行频点，否则下行频点为无效值 */
            usDlChannel = at_ftm_get_dlchan(EN_FCHAN_MODE_FDD_LTE, stReq.usChannel);
            /* coverity[copy_paste_error] */
            if(stReq.usChannel == usUlChannel)
            {
                pstFCtManageInfo->stCurFchan.usDlChannel = usDlChannel;
            }
        }
    }

    return ;
}

/*lint -save -e550 -e830*/
/*****************************************************************************
 函 数 名  : at_ftm_fchan_read
 功能描述  : ID_MSG_FTM_RD_FCHAN_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_read(VOS_VOID* pParam)
{
    FTM_RD_FCHAN_CNF_STRU stRdCnf = { 0 };
    FTM_RD_FCHAN_CNF_STRU* pstSavedRdCnf = &ftm_GetMainInfo()->stFtmCtInfo.stCurFchan;

    stRdCnf.ulErrCode   = ERR_FTM_SUCCESS;
    stRdCnf.enFchanMode = pstSavedRdCnf->enFchanMode;
    stRdCnf.ucBand      = pstSavedRdCnf->ucBand;
    stRdCnf.usUlChannel = pstSavedRdCnf->usUlChannel;
    stRdCnf.usDlChannel = pstSavedRdCnf->usDlChannel;

     return ftm_comm_send(ID_MSG_FTM_RD_FCHAN_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_FCHAN_CNF_STRU));
}
/*lint -restore +e550 +e830*/

/*****************************************************************************
 函 数 名  : at_ftm_fchan_set
 功能描述  : ID_MSG_FTM_SET_FCHAN_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_set(VOS_VOID* pParam)
{
    FTM_SET_FCHAN_REQ_STRU* pstFtmReq       = (FTM_SET_FCHAN_REQ_STRU*)pParam;
    OM_PHY_CT_FREQ_SET_REQ_STRU stReqToDsp  = { 0 };
    VOS_UINT8  ucBand;
    VOS_UINT16 usUlChan = 0;
    VOS_UINT16 usDlChan = 0;

    /* 判断是否处于非信令模式下 */
    if (ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fchan_setcnf(ERR_FTM_UE_MODE_ERR);
    }

    if(pstFtmReq->enFchanMode == EN_FCHAN_MODE_TD_SCDMA)
    {
        /* 设LRTT从模 */
        LHPA_DbgSendSetWorkMode_toSlaveMode();
        (VOS_VOID)VOS_TaskDelay(100);

        /* 设TRTT从模 */
        TDS_CBT_SetSlaveMode();

        /* 设TRTT为主模 */
        TDS_CBT_SetMasterMode();
    }
    else
    {
        /* 设LRTT从模 */
         LHPA_DbgSendSetWorkMode_toSlaveMode();
         (VOS_VOID)VOS_TaskDelay(100);

        /* 设TRTT从模 */
        TDS_CBT_SetSlaveMode();

        /*  切换LRTT为主模 */
		LHPA_DbgSendSetWorkMode_toMaterMode();
		(VOS_VOID)VOS_TaskDelay(100);
    }

    usUlChan = at_ftm_get_ulchan(pstFtmReq->enFchanMode, pstFtmReq->usChannel);
    usDlChan = at_ftm_get_dlchan(pstFtmReq->enFchanMode, pstFtmReq->usChannel);
    if(ERR_FTM_SUCCESS != at_ftm_getBandID(pstFtmReq->enFchanMode, pstFtmReq->ucBand, &ucBand))
    {
         (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] at_ftm_getBandID failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
         return at_ftm_fchan_setcnf(ERR_FTM_INVALID_PARAMETER);
    }

    /* 发送原语到DSP */
    stReqToDsp.ulMsgId   = OM_PHY_CT_FREQ_SET_REQ;
    stReqToDsp.usMode    = pstFtmReq->enFchanMode;
    stReqToDsp.usBandNum = ucBand;
    stReqToDsp.usUlFreq  = at_ftm_get_freq(pstFtmReq->enFchanMode, usUlChan);
    stReqToDsp.usDlFreq  = at_ftm_get_freq(pstFtmReq->enFchanMode, usDlChan);

    if(ERR_FTM_SUCCESS != ftm_mailbox_ct_write(pstFtmReq->enFchanMode, &stReqToDsp, sizeof(OM_PHY_CT_FREQ_SET_REQ_STRU)))
    {

        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ct_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fchan_setcnf(ERR_FTM_UNKNOWN);
    }

    at_ftm_fchan_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_FTM_WAIT_ASYNC;
}

/*****************************************************************************
 函 数 名  : at_ftm_fchan_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_timeout(VOS_VOID)
{
    return at_ftm_fchan_setcnf(ERR_FTM_TIME_OUT);
}

/*****************************************************************************
 函 数 名  : at_ftm_fchan_dspcnf
 功能描述  : DSP原语PHY_OM_CT_FREQ_SET_CNF处理函数
             向DSP发送原语进行频段切换
 输入参数  : pParam PHY_OM_CT_FREQ_SET_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_dspcnf(VOS_VOID* pParam)
{
    at_ftm_fchan_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);
    return at_ftm_fchan_setcnf(ERR_FTM_SUCCESS);
}

/*****************************************************************************
 函 数 名  : at_ftm_tselrf_store
 功能描述  : 保存参数
 输入参数  : ucStoreType 保存类型
               FTM_F_CT_STORE_REQ_TEMP 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数
               FTM_F_CT_STORE_REQ_GLOBAL 收到LRTT确认原语，保存参数，供装备查询
             pstReq  参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
static VOID at_ftm_tselrf_store(VOS_UINT8 ucStoreType, FTM_SET_TSELRF_REQ_STRU* pstReq)
{
    static FTM_SET_TSELRF_REQ_STRU stReq = {0};

    /* 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数*/
    if ((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_TSELRF_REQ_STRU));
    }
    /* 收到LRTT确认原语，保存参数，供装备查询 */
    else
    {
        (ftm_GetMainInfo()->stFtmCtInfo).ucTselrfPath = stReq.ucPath;
        (ftm_GetMainInfo()->stFtmCtInfo).ucTselrfGroup = stReq.ucGroup;
    }

    return ;
}

/*lint -save -e550 -e830*/
/*****************************************************************************
 函 数 名  : at_ftm_tselrf_setcnf
 功能描述  : 返回确认
 输入参数  : ulErrCode 错误码
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
static VOS_UINT32 at_ftm_tselrf_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_TSELRF_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_TSELRF_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_TSELRF_CNF_STRU));
}
/*lint -restore +e550 +e830*/

/*****************************************************************************
 函 数 名  : at_ftm_tselrf_set
 功能描述  : ID_MSG_FTM_SET_TSELRF_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_tselrf_set(VOS_VOID* pParam)
{
    FTM_SET_TSELRF_REQ_STRU* pstFtmReq       = (FTM_SET_TSELRF_REQ_STRU*)pParam;
    OM_PHY_CT_TSELRF_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM emFchanMode              = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* 判断参数有效性 */
    if((pstFtmReq->ucPath     != FTM_TSELRF_TD)
        && (pstFtmReq->ucPath != FTM_TSELRF_FDD_LTE_MAIN)
        && (pstFtmReq->ucPath != FTM_TSELRF_TDD_LTE_MAIN)
        && (pstFtmReq->ucPath != FTM_TSELRF_FDD_LTE_SUB)
        && (pstFtmReq->ucPath != FTM_TSELRF_TDD_LTE_SUB))
    {
        return at_ftm_tselrf_setcnf(ERR_FTM_INVALID_OP);
    }

    /* 判读是否处于非信令模式 */
    if (ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {

        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_tselrf_setcnf(ERR_FTM_UE_MODE_ERR);
    }

    stReqToDsp.ulMsgId = OM_PHY_CT_TSELRF_SET_REQ;

    if((pstFtmReq->ucPath    == FTM_TSELRF_FDD_LTE_MAIN)
        ||(pstFtmReq->ucPath == FTM_TSELRF_TDD_LTE_MAIN))
    {
        stReqToDsp.ucPath = FTM_RXANT_OPEN_CHAN1;
        stReqToDsp.ucGroup= FTM_RXANT_TYPE_RX;
    }
    else if((pstFtmReq->ucPath == FTM_TSELRF_FDD_LTE_SUB)
        || (pstFtmReq->ucPath == FTM_TSELRF_TDD_LTE_SUB))
    {
        stReqToDsp.ucPath = FTM_RXANT_OPEN_CHAN2;
        stReqToDsp.ucGroup= FTM_RXANT_TYPE_RX;
    }
    else /* FTM_TSELRF_TD */
    {
        stReqToDsp.ucGroup = 0xFF;
        stReqToDsp.ucPath  = pstFtmReq->ucPath;
    }

    if(ERR_FTM_SUCCESS != ftm_mailbox_ct_write(emFchanMode, &stReqToDsp, sizeof(OM_PHY_CT_TSELRF_SET_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_tselrf_setcnf(ERR_FTM_UNKNOWN);
    }

    at_ftm_tselrf_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_FTM_WAIT_ASYNC;
}

/*****************************************************************************
 函 数 名  : at_ftm_tselrf_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_tselrf_timeout(VOS_VOID)
{
    return at_ftm_tselrf_setcnf(ERR_FTM_TIME_OUT);
}

/*****************************************************************************
 函 数 名  : at_ftm_tselrf_dspcnf
 功能描述  : DSP原语PHY_OM_CT_TSELRF_SET_CNF处理函数
 输入参数  : pParam PHY_OM_CT_TSELRF_SET_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_tselrf_dspcnf(VOS_VOID* pParam)
{
    at_ftm_tselrf_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);
    return at_ftm_tselrf_setcnf(ERR_FTM_SUCCESS);

}

/*****************************************************************************
 函 数 名  : at_ftm_ftxon_store
 功能描述  : 保存参数
 输入参数  : ucStoreType 保存类型
               FTM_F_CT_STORE_REQ_TEMP 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数
               FTM_F_CT_STORE_REQ_GLOBAL 收到LRTT确认原语，保存参数，供装备查询
             pstReq  参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOID at_ftm_ftxon_store(VOS_UINT8 ucStoreType, FTM_SET_TXON_REQ_STRU* pstReq)
{
    static FTM_SET_TXON_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_TXON_REQ_STRU));
    }
    /* 收到LRTT确认原语，保存参数，供装备查询 */
    else
    {
        pstFCtManageInfo->enCurTxon = stReq.enSwtich;
    }

    return ;
}
/*lint -save -e550 */
/*****************************************************************************
 函 数 名  : at_ftm_ftxon_setcnf
 功能描述  : 保存参数
 输入参数  : ulErrCode 错误码
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_TXON_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_TXON_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_TXON_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_ftxon_read
 功能描述  : ID_MSG_FTM_RD_TXON_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_read(VOS_VOID* pParam)
{
    FTM_RD_TXON_CNF_STRU stRdCnf = { 0 };
    FTM_TXON_SWT_ENUM enCurTxon  = ftm_GetMainInfo()->stFtmCtInfo.enCurTxon;

    stRdCnf.ulErrCode = ERR_FTM_SUCCESS;
    stRdCnf.enSwtich  = enCurTxon;

     return ftm_comm_send(ID_MSG_FTM_RD_TXON_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_TXON_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_ftxon_set
 功能描述  : ID_MSG_FTM_SET_TXON_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_set(VOS_VOID* pParam)
{
    FTM_SET_TXON_REQ_STRU* pstFtmReq   = (FTM_SET_TXON_REQ_STRU*)pParam;
    OM_PHY_CT_TXON_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode          = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* 判断是否处于非信令模式下 */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_ftxon_setcnf(ERR_FTM_UE_MODE_ERR);
    }

    /* 判断参数是否为有效参数 */
    if((pstFtmReq->enSwtich != EN_FTM_TXON_CLOSE)
        && (pstFtmReq->enSwtich !=  EN_FTM_TXON_UL_RFBBP_OPEN)
        && (pstFtmReq->enSwtich !=  EN_FTM_TXON_RF_PA_OPEN))
    {

        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ERR_FTM_INVALID_PARAMETER\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_ftxon_setcnf(ERR_FTM_INVALID_PARAMETER);
    }

    /* 发送原语到DSP */
    stReqToDsp.ulMsgId  = OM_PHY_CT_TXON_REQ;
    stReqToDsp.usTxType = (VOS_UINT16)pstFtmReq->enSwtich;

    if(ERR_FTM_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_TXON_REQ_STRU)))
    {
      (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_ftxon_setcnf(ERR_FTM_UNKNOWN);
    }

    at_ftm_ftxon_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_FTM_WAIT_ASYNC;
}

/*****************************************************************************
 函 数 名  : at_ftm_ftxon_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_timeout(VOS_VOID)
{
    return at_ftm_ftxon_setcnf(ERR_FTM_TIME_OUT);
}

/*****************************************************************************
 函 数 名  : at_ftm_ftxon_dspcnf
 功能描述  : DSP原语PHY_OM_CT_TXON_CNF处理函数
 输入参数  : pParam PHY_OM_CT_TXON_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_dspcnf(VOS_VOID* pParam)
{
    at_ftm_ftxon_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_ftxon_setcnf(ERR_FTM_SUCCESS);
}

/*****************************************************************************
 函 数 名  : at_ftm_frxon_store
 功能描述  : 保存参数
 输入参数  : ucStoreType 保存类型
               FTM_F_CT_STORE_REQ_TEMP 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数
               FTM_F_CT_STORE_REQ_GLOBAL 收到LRTT确认原语，保存参数，供装备查询
             pstReq  参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOID at_ftm_frxon_store(VOS_UINT8 ucStoreType, FTM_SET_RXON_REQ_STRU* pstReq)
{
    static FTM_SET_RXON_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_RXON_REQ_STRU));
    }
    /* 收到LRTT确认原语，保存参数，供装备查询 */
    else
    {
        pstFCtManageInfo->enCurRxon = stReq.ulRxSwt;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : at_ftm_frxon_setcnf
 功能描述  : 保存参数
 输入参数  : ulErrCode 错误码
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_RXON_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_RXON_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_RXON_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_frxon_read
 功能描述  : ID_MSG_FTM_RD_TXON_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_read(VOS_VOID* pParam)
{
    FTM_RD_RXON_CNF_STRU stRdCnf = { 0 };
    FTM_RXON_SWT_ENUM enCurRxon = ftm_GetMainInfo()->stFtmCtInfo.enCurRxon;

    stRdCnf.ulErrCode = ERR_FTM_SUCCESS;
    stRdCnf.ulRxSwt= enCurRxon;

     return ftm_comm_send(ID_MSG_FTM_RD_RXON_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_RXON_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_frxon_set
 功能描述  : ID_MSG_FTM_SET_RXON_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_set(VOS_VOID* pParam)
{
    FTM_SET_RXON_REQ_STRU* pstFtmReq   = (FTM_SET_RXON_REQ_STRU*)pParam;
    OM_PHY_CT_RXON_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode          = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* 判断是否处于非信令模式下 */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_frxon_setcnf(ERR_FTM_UE_MODE_ERR);
    }

    /* 判断参数是否为有效参数 */
    if((pstFtmReq->ulRxSwt!= EN_FTM_RXON_CLOSE)
        && (pstFtmReq->ulRxSwt != EN_FTM_RXON_OPEN))
    {

        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ERR_FTM_INVALID_PARAMETER\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_frxon_setcnf(ERR_FTM_INVALID_PARAMETER);
    }

    /* 注意: 实际使用中并为向DSP发送开关标志， DSP接收机一直是开着的  */

    /* 发送原语到DSP */
    stReqToDsp.ulMsgId  = OM_PHY_CT_RXON_REQ;
    stReqToDsp.usRxType = (VOS_UINT16)pstFtmReq->ulRxSwt;
    if(ERR_FTM_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_RXON_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_frxon_setcnf(ERR_FTM_UNKNOWN);
    }

    at_ftm_frxon_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_FTM_WAIT_ASYNC;
}

/*****************************************************************************
 函 数 名  : at_ftm_frxon_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_timeout(VOS_VOID)
{
    return at_ftm_frxon_setcnf(ERR_FTM_TIME_OUT);
}

/*****************************************************************************
 函 数 名  : at_ftm_frxon_dspcnf
 功能描述  : DSP原语PHY_OM_CT_RXON_CNF处理函数
 输入参数  : pParam PHY_OM_CT_RXON_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_dspcnf(VOS_VOID* pParam)
{

    at_ftm_frxon_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_frxon_setcnf(ERR_FTM_SUCCESS);
}

#if (FEATURE_LTE_4RX == FEATURE_ON)
VOID at_ftm_frssi_store_lte_4rx(VOS_INT16 usRssiVal1, VOS_INT16 usRssiVal2,VOS_INT16 usRssiVal3,VOS_INT16 usRssiVal4);
#endif

#if (FEATURE_LTE_4RX == FEATURE_ON)
VOID at_ftm_frssi_store_lte_4rx(VOS_INT16 usRssiVal1, VOS_INT16 usRssiVal2,VOS_INT16 usRssiVal3,VOS_INT16 usRssiVal4)
{
    ftm_GetMainInfo()->stFtmCtInfo.usRssiVal1 = (VOS_UINT16)usRssiVal1;
    ftm_GetMainInfo()->stFtmCtInfo.usRssiVal2 = (VOS_UINT16)usRssiVal2;
    ftm_GetMainInfo()->stFtmCtInfo.usRssiVal3 = (VOS_UINT16)usRssiVal3;
    ftm_GetMainInfo()->stFtmCtInfo.usRssiVal4 = (VOS_UINT16)usRssiVal4;
    return ;
}
#else
/*****************************************************************************
 函 数 名  : at_ftm_frssi_store
 功能描述  : 保存参数
 输入参数  : sRssiVal  接收信号强度(例如: 850代表-85dbm)
             pstReq  参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOID at_ftm_frssi_store(VOS_INT16 sRssiVal)
{
    ftm_GetMainInfo()->stFtmCtInfo.sCurRssiVal = sRssiVal;
    return ;
}
#endif

/*****************************************************************************
 函 数 名  : at_ftm_frssi_readcnf
 功能描述  : 保存参数
 输入参数  : ulErrCode 错误码
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_readcnf(VOS_UINT32 ulErrCode)
{
    FTM_FRSSI_CNF_STRU stCnf = { 0 };
    stCnf.ulErrCode = ulErrCode;
#if (FEATURE_LTE_4RX == FEATURE_ON)
    stCnf.lValue1 = ftm_GetMainInfo()->stFtmCtInfo.usRssiVal1;
    stCnf.lValue2 = ftm_GetMainInfo()->stFtmCtInfo.usRssiVal2;
    stCnf.lValue3 = ftm_GetMainInfo()->stFtmCtInfo.usRssiVal3;
    stCnf.lValue4 = ftm_GetMainInfo()->stFtmCtInfo.usRssiVal4;
#else
    stCnf.lValue1 = ftm_GetMainInfo()->stFtmCtInfo.sCurRssiVal;
#endif
    return ftm_comm_send(ID_MSG_FTM_FRSSI_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_FRSSI_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_frssi_read
 功能描述  : ID_MSG_FTM_FRSSI_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_read(VOS_VOID* pParam)
{
    OM_PHY_CT_MEAS_RSSI_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode               = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* 判断是否处于非信令模式下 */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_frssi_readcnf(ERR_FTM_UE_MODE_ERR);
    }

    /* 发送原语到DSP */
    stReqToDsp.ulMsgId = OM_PHY_CT_MEAS_RSSI_REQ;
    if(ERR_FTM_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_MEAS_RSSI_REQ_STRU)))
    {
        return at_ftm_frssi_readcnf(ERR_FTM_UNKNOWN);
    }

    return ERR_FTM_WAIT_ASYNC;
}

/*****************************************************************************
 函 数 名  : at_ftm_frssi_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_timeout(VOS_VOID)
{
    return at_ftm_frssi_readcnf(ERR_FTM_TIME_OUT);
}

/*****************************************************************************
 函 数 名  : at_ftm_frssi_dspcnf
 功能描述  : DSP原语PHY_OM_CT_MEAS_RSSI_CNF处理函数
 输入参数  : pParam PHY_OM_CT_MEAS_RSSI_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_dspcnf(VOS_VOID* pParam)
{

    /* 此函数啥也不干, 处理有些特殊 */
    /* 关闭超时判断定时器放在at_ftm_frssi_dspind函数里*/

    return ERR_FTM_SUCCESS;
}

/*****************************************************************************
 函 数 名  : at_ftm_frssi_dspind
 功能描述  : DSP原语PHY_OM_CT_RSSI_IND处理函数
 输入参数  : pParam PHY_OM_CT_RSSI_IND_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_dspind(VOS_VOID* pParam)
{
    VOS_UINT32 ulErrCode = ERR_FTM_SUCCESS;
    PHY_OM_CT_RSSI_IND_STRU* pDspInd = (PHY_OM_CT_RSSI_IND_STRU*)pParam;

    HAL_SDMLOG("\n usRxANT1ValidFlag:0x%x, sRxANT1RSSI:0x%x, usRxANT2ValidFlag:0x%x, sRxANT2RSSI:0x%x \n",
        pDspInd->usRxANT1ValidFlag, pDspInd->sRxANT1RSSI, pDspInd->usRxANT2ValidFlag, pDspInd->sRxANT2RSSI);
#if (FEATURE_LTE_4RX == FEATURE_ON)
    at_ftm_frssi_store_lte_4rx(pDspInd->sRxANT1RSSI,pDspInd->sRxANT2RSSI,pDspInd->sRxANT3RSSI,pDspInd->sRxANT4RSSI);
    ulErrCode = ERR_FTM_SUCCESS;
#else
    if(pDspInd->usRxANT1ValidFlag == 1)
    {

        at_ftm_frssi_store(pDspInd->sRxANT1RSSI);
        ulErrCode = ERR_FTM_SUCCESS;
    }
    else if(pDspInd->usRxANT2ValidFlag == 1)
    {
        HAL_SDMLOG("\n pDspInd->usRxANT1ValidFlag == 1 \n");
        at_ftm_frssi_store(pDspInd->sRxANT2RSSI);
        ulErrCode = ERR_FTM_SUCCESS;
    }
    else
    {
        at_ftm_frssi_store(-1);
        ulErrCode = ERR_FTM_OPERTION_ERROR;
    }
#endif

    return at_ftm_frssi_readcnf(ulErrCode);
}

/*****************************************************************************
 函 数 名  : at_ftm_fwave_store
 功能描述  : 保存参数
 输入参数  : ucStoreType 保存类型
               FTM_F_CT_STORE_REQ_TEMP 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数
               FTM_F_CT_STORE_REQ_GLOBAL 收到LRTT确认原语，保存参数，供装备查询
             pstReq  参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOID at_ftm_fwave_store(VOS_UINT8 ucStoreType, FTM_SET_FWAVE_REQ_STRU* pstReq)
{
    static FTM_SET_FWAVE_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FWAVE_REQ_STRU));
    }
    /* 收到LRTT确认原语，保存参数，供装备查询 */
    else
    {
        pstFCtManageInfo->enCurFwaveType  = (FWAVE_TYPE_ENUM)stReq.usType;
        pstFCtManageInfo->usCurFwavePower = stReq.usPower;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : at_ftm_fwave_setcnf
 功能描述  : 保存参数
 输入参数  : ulErrCode 错误码
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FWAVE_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FWAVE_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FWAVE_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_fwave_read
 功能描述  : ID_MSG_FTM_RD_FWAVE_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_read(VOS_VOID* pParam)
{
    FTM_RD_FWAVE_CNF_STRU stRdCnf = { 0 };

    stRdCnf.usType    = (VOS_UINT16)ftm_GetMainInfo()->stFtmCtInfo.enCurFwaveType;
    stRdCnf.usPower   = ftm_GetMainInfo()->stFtmCtInfo.usCurFwavePower;

    return ftm_comm_send(ID_MSG_FTM_RD_FWAVE_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_FWAVE_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_fwave_set
 功能描述  : ID_MSG_FTM_SET_FWAVE_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_set(VOS_VOID* pParam)
{
    FTM_SET_FWAVE_REQ_STRU* pstFtmReq       = (FTM_SET_FWAVE_REQ_STRU*)pParam;
    OM_PHY_CT_FWAVE_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode               = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* 判断是否处于非信令模式下 */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fwave_setcnf(ERR_FTM_UE_MODE_ERR);
    }

    /* 发送原语到DSP */
    stReqToDsp.ulMsgId = OM_PHY_CT_FWAVE_SET_REQ;
    stReqToDsp.usType  = pstFtmReq->usType;
    stReqToDsp.usPower = (VOS_INT16)pstFtmReq->usPower;
    if(ERR_FTM_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_FWAVE_SET_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fwave_setcnf(ERR_FTM_UNKNOWN);
    }
    at_ftm_fwave_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_FTM_WAIT_ASYNC;
}

/*****************************************************************************
 函 数 名  : at_ftm_fwave_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_timeout(VOS_VOID)
{
    return at_ftm_fwave_setcnf(ERR_FTM_TIME_OUT);
}

/*****************************************************************************
 函 数 名  : at_ftm_fwave_dspcnf
 功能描述  : DSP原语PHY_OM_CT_FWAVE_CNF处理函数
             关闭超时定时器
 输入参数  : pParam PHY_OM_CT_FWAVE_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fwave_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fwave_setcnf(ERR_FTM_SUCCESS);
}

/*****************************************************************************
 函 数 名  : at_ftm_flna_store
 功能描述  : 保存参数
 输入参数  : ucStoreType 保存类型
               FTM_F_CT_STORE_REQ_TEMP 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数
               FTM_F_CT_STORE_REQ_GLOBAL 收到LRTT确认原语，保存参数，供装备查询
             pstReq  参数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOID at_ftm_flna_store(VOS_UINT8 ucStoreType, FTM_SET_AAGC_REQ_STRU* pstReq)
{
    static FTM_SET_AAGC_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* 收到装备参数设置指令，未收到LRTT确认原语，只缓存参数*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_AAGC_REQ_STRU));
    }
    /* 收到LRTT确认原语，保存参数，供装备查询 */
    else
    {
        pstFCtManageInfo->ucCurLnaLvl = stReq.ucAggcLvl;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : at_ftm_flna_setcnf
 功能描述  : 保存参数
 输入参数  : ulErrCode 错误码
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_flna_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_AAGC_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_AAGC_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_AAGC_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_flna_read
 功能描述  : ID_MSG_FTM_RD_AAGC_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_flna_read(VOS_VOID* pParam)
{
    FTM_RD_AAGC_CNF_STRU stRdCnf = { 0 };

    stRdCnf.ulErrCode = ERR_FTM_SUCCESS;
    stRdCnf.ucAggcLvl = ftm_GetMainInfo()->stFtmCtInfo.ucCurLnaLvl;

     return ftm_comm_send(ID_MSG_FTM_RD_AAGC_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_AAGC_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_flna_set
 功能描述  : ID_MSG_FTM_SET_AAGC_REQ 处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_flna_set(VOS_VOID* pParam)
{
    FTM_SET_AAGC_REQ_STRU* pstFtmReq       = (FTM_SET_AAGC_REQ_STRU*)pParam;
    OM_PHY_CT_AAGC_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode              = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* 判断是否处于非信令模式下 */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_flna_setcnf(ERR_FTM_UE_MODE_ERR);
    }

    /* 发送原语到DSP */
    stReqToDsp.ulMsgId     = OM_PHY_CT_AAGC_SET_REQ;
    stReqToDsp.usAAGCValue = pstFtmReq->ucAggcLvl;
    if(ERR_FTM_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_AAGC_SET_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_flna_setcnf(ERR_FTM_UNKNOWN);
    }

    at_ftm_flna_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_FTM_WAIT_ASYNC;
}

/*****************************************************************************
 函 数 名  : at_ftm_flna_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_flna_timeout(VOS_VOID)
{
    return at_ftm_flna_setcnf(ERR_FTM_TIME_OUT);
}

/*****************************************************************************
 函 数 名  : at_ftm_flna_dspcnf
 功能描述  : DSP原语PHY_OM_CT_AAGC_CNF处理函数
             关闭超时定时器
             输入参数  : pParam PHY_OM_CT_AAGC_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_flna_dspcnf(VOS_VOID* pParam)
{

    at_ftm_flna_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);
    return at_ftm_flna_setcnf(ERR_FTM_SUCCESS);
}

/*****************************************************************************
 函 数 名  : at_ftm_fpllstatus_read
 功能描述  : ID_MSG_FTM_RD_FPLLSTATUS_REQ处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/

VOS_UINT32 at_ftm_fpllstatus_read(VOS_VOID* pParam)
{
    OM_PHY_FPLLSTATUS_RD_REQ_STRU stReqToDsp = {0};
    if (NULL == pParam)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ERR_FTM_INVALID_OP\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_INVALID_OP;
    }

    /* 发送原语到DSP */
    stReqToDsp.ulMsgId   = OM_PHY_FPLLSTATUS_RD_REQ;

    if (ERR_FTM_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_FPLLSTATUS_RD_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ltect_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fpllstatus_readcnf(0,0,ERR_FTM_UNKNOWN);
    }
    return ERR_FTM_WAIT_ASYNC;
}

VOS_UINT32 at_ftm_fpllstatus_readcnf(VOS_UINT16 txStatus, VOS_UINT16 rxStatus, VOS_UINT32 ulErrCode)
{
    FTM_RD_FPLLSTATUS_CNF_STRU stCnf = { 0 };
    stCnf.tx_status = txStatus;
    stCnf.rx_status = rxStatus;
    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_RD_FPLLSTATUS_CNF,
             (VOS_UINT32)&stCnf, sizeof(FTM_RD_FPLLSTATUS_CNF_STRU));
}

/*****************************************************************************
 函 数 名  : at_ftm_fpllstatus_dspcnf
 输入参数  : pParam PHY_OM_CT_FPLLSTATUS_RD_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_fpllstatus_dspcnf(VOS_VOID* pParam)
{
    if (NULL == pParam)
    {
        (VOS_VOID)vos_printf("invalid data\n");
        return ERR_FTM_INVALID_OP;
    }

    PHY_OM_FPLLSTATUS_RD_CNF_STRU *pDspCnf = (PHY_OM_FPLLSTATUS_RD_CNF_STRU *)pParam;
    FTM_RD_FPLLSTATUS_CNF_STRU stCnf = {0};
    stCnf.tx_status = pDspCnf->tx_status;
    stCnf.rx_status = pDspCnf->rx_status;
    stCnf.ulErrCode = ERR_FTM_SUCCESS;

    return ftm_comm_send(ID_MSG_FTM_RD_FPLLSTATUS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_RD_FPLLSTATUS_CNF_STRU));
}
/*lint -restore*/

VOS_UINT32 at_ftm_fpllstatus_timeout(VOS_VOID)
{
    return at_ftm_fpllstatus_readcnf(0,0,ERR_FTM_TIME_OUT);
}

