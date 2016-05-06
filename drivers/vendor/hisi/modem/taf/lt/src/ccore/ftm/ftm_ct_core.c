/******************************************************************************

                  ��Ȩ���� (C), 1998-2010, ��Ϊ�������޹�˾

*******************************************************************************
  �� �� ��   : ftm_ct_core.c
  �� �� ��   : V1.0
  ��    ��   : ���ķ�/00149739
  ��������   : 2010-05-12
  ��������   : TODO: ...

  �����б�   : TODO: ...
  �޸���ʷ   :
  1.��    �� : 2010-05-12
    ��    �� : ���ķ�/00149739
    �޸����� : �����ļ�

******************************************************************************/

/******************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
******************************************************************************/

/*lint --e{830,539,525}*/

#include "ftm_errno.h"
#include "osm.h"
#include "gen_msg.h"
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
#include "msp_at.h"

#include "TPsTMspInterface.h"
#include "taf_ftm.h"
#include "ftm_mntn.h"
/*lint -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_CT_CORE_C
/*lint +e767 */

VOS_UINT32 g_ulCrntClientId;

/* FTMģ�鳬ʱ���� */
FTM_CTCMD_CTRL_STRU g_ct_cmd_ctrl = {0};

static FTM_MAIN_INFO_STRU g_stFtmMainInfo = {
    NULL, /* SYMע��ӿڣ���Ҫ��Ϊ�˱�֤�ܹ���ϵ */
    /* ��ͨУ׼Ĭ��ֵ������ʱ���ݱ���*/
    {
        {EN_FCHAN_MODE_FDD_LTE,FTM_AT_FCHAN_BAND,{0},0,0,ERR_FTM_SUCCESS},
        EN_FTM_TXON_CLOSE,
        EN_FTM_RXON_CLOSE,
        EN_FWAVE_TYPE_CW,
        0,
        0,
        1200, /* -150dbm */
        0,
        FTM_NONESIG_RTT_CLOSE,
        0xFF,
        0xFF
    },

    /* ����У׼Ĭ��ֵ������ʱ���ݱ���*/
    {
        CT_F_STEPS_DONE_NULL,
        EN_FCHAN_MODE_UNKONWN,
        255,
        TXWAVE_TYPE_CW,
        START_TRIGGER_TYPE_TX,
        0,
        20 ,0 ,1,
        0 ,0 ,0 ,0 ,0 ,0 ,0 ,
        {0},{0} ,{0},{0},{0},
        {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
		{0}, {0}, 0, 0, 0, {0}, 0, 0, 0,
        {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}
     },
/*lint -e651*/
/*lint -e156*/

    /* �������۲�������� */
    {
         0 ,
		{0}, {0}, {0}, {0}, {0},
        {0}, {0}, {0}, {0}, {0},
        {0}, {0}, {0}, {0}, {0},
        {{0},}, {0}, {0}
    },
/*lint -e156*/
/*lint -e651*/
    /* ϵͳ��ǰTMODEģʽ */
    EN_SYM_TMODE_SIGNAL,

    /* ͨ��AT��������� */
    {
         ERR_FTM_SUCCESS,
         0
    },
};

/*************************************************************
   A�˷��͵�װ����Ϣ������
   ��ҪRTTȷ�ϵ��г�ʱ��������������ҪRTTȷ�ϵ�û�г�ʱ����
**************************************************************/
static FTM_EQUIP_MSG_FUNTBL_STRU g_stFtmEquipMsgTbl[] = {
    {ID_MSG_SYM_SET_TMODE_REQ,          at_ftm_tmode_set,           at_ftm_tmode_timeout        },
    {ID_MSG_SYM_RD_TMODE_REQ,           at_ftm_tmode_read,          NULL                        },
    {ID_MSG_FTM_SET_TSELRF_REQ,         at_ftm_tselrf_set,          at_ftm_tselrf_timeout       },
    {ID_MSG_FTM_SET_FCHAN_REQ,          at_ftm_fchan_set,           at_ftm_fchan_timeout        },
    {ID_MSG_FTM_RD_FCHAN_REQ,           at_ftm_fchan_read,          NULL                        },
    {ID_MSG_FTM_SET_FWAVE_REQ,          at_ftm_fwave_set,           at_ftm_fwave_timeout        },
    {ID_MSG_FTM_RD_FWAVE_REQ,           at_ftm_fwave_read,          NULL                        },
    {ID_MSG_FTM_SET_TXON_REQ,           at_ftm_ftxon_set,           at_ftm_ftxon_timeout        },
    {ID_MSG_FTM_RD_TXON_REQ,            at_ftm_ftxon_read,          NULL                        },
    {ID_MSG_FTM_SET_RXON_REQ,           at_ftm_frxon_set,           at_ftm_frxon_timeout        },
    {ID_MSG_FTM_RD_RXON_REQ,            at_ftm_frxon_read,          NULL                        },
    {ID_MSG_FTM_SET_AAGC_REQ,           at_ftm_flna_set,            at_ftm_flna_timeout         },
    {ID_MSG_FTM_RD_AAGC_REQ,            at_ftm_flna_read,           NULL                        },
    {ID_MSG_FTM_FRSSI_REQ,              at_ftm_frssi_read,          at_ftm_frssi_timeout        },

    {ID_MSG_FTM_SET_LTCOMMCMD_REQ,      at_ftm_ltcommcmd_set,       at_ftm_ltcommcmd_timeout    },
    {ID_MSG_FTM_RD_LTCOMMCMD_REQ,       at_ftm_ltcommcmd_read,      NULL                        },
    {ID_MSG_FTM_RD_FPLLSTATUS_REQ,      at_ftm_fpllstatus_read,     at_ftm_fpllstatus_timeout   },

};
/*************************************************************
   DSPȷ��ԭ����Ϣ��������������Ҫ��ʱ�жϴ���
   ע: PHY_OM_CT_RSSI_IND,PHY_OM_CT_F_MEAS_IP2_IND
       ԭ��������ʷԭ����ȻдΪINDʵ��ʹ��ΪCNF
**************************************************************/
static FTM_DSP_MSG_FUNTBL_STRU g_stFtmDspCnfMsgTbl[] = {
    {PHY_OM_CT_TEST_MODE_CNF,           at_ftm_tmode_dspcnf         },
    {PHY_OM_CT_TSELRF_SET_CNF,          at_ftm_tselrf_dspcnf        },
    {PHY_OM_CT_FREQ_SET_CNF,            at_ftm_fchan_dspcnf         },
    {PHY_OM_CT_FWAVE_SET_CNF,           at_ftm_fwave_dspcnf         },
    {PHY_OM_CT_TXON_CNF,                at_ftm_ftxon_dspcnf         },
    {PHY_OM_CT_RXON_CNF,                at_ftm_frxon_dspcnf         },
    {PHY_OM_CT_AAGC_SET_CNF,            at_ftm_flna_dspcnf          },
    {PHY_OM_CT_RSSI_IND,                at_ftm_frssi_dspind         },

    {PHY_OM_COMM_CMD_SET_CNF,           at_ftm_ltcommcmd_dspcnf     },
    {PHY_OM_FPLLSTATUS_RD_CNF,          at_ftm_fpllstatus_dspcnf     },
};

/*************************************************************
   DSPִ��ĳЩ�첽������ɺ������ϱ�ԭ����Ϣ����������������Ҫ��ʱ�ж�
   ע: PHY_OM_CT_MEAS_RSSI_CNF,PHY_OM_CT_MEAS_RSSI_CNF
       ԭ��������ʷԭ����ȻдΪCNFʵ��ʹ��ΪIND
**************************************************************/
static FTM_DSP_MSG_FUNTBL_STRU g_stFtmDspIndMsgTbl[] = {
    {PHY_OM_CT_MEAS_RSSI_CNF,      at_ftm_frssi_dspcnf     },

    {PHY_OM_COMM_CMD_IND,           at_ftm_ltcommcmd_dspind  },
};

FTM_MAIN_INFO_STRU * ftm_GetMainInfo(VOS_VOID)
{
    return &g_stFtmMainInfo;
}

SYM_TMODE_ENUM* ftm_GetTmodeMainInfo(VOS_VOID)
{
    return &(g_stFtmMainInfo.symMode);
}

/*����У׼ c00173035  start in 2010-12-29*/

FTM_CT_F_MANAGE_INFO_STRU* ftm_GetFastCTMainInfo(VOS_VOID)
{
    return &(g_stFtmMainInfo.stFtmFastCtInfo);
}

/* �������۲� */
FTM_SYN_INFO_STRU *ftm_GetSynMainInfo(VOS_VOID)
{
    return &(g_stFtmMainInfo.stFtmSynInfo);
}

VOS_VOID ftm_SetDefault(VOS_VOID)
{
	FTM_SYN_INFO_STRU *stFCtMainInfo = NULL;

	stFCtMainInfo = ftm_GetSynMainInfo();
	stFCtMainInfo->stSstartRdCnf.usType = 0;
	stFCtMainInfo->stSstartRdCnf.usStatus = 2;

	stFCtMainInfo->stSsyncRdCnf.ulStatus = 0;

	stFCtMainInfo->stSrxblerRdCnf.usbler[0] = 0;
	stFCtMainInfo->stSrxblerRdCnf.usSnr[0] = 0;
    stFCtMainInfo->stSrxblerRdCnf.usbler[1] = 0;
	stFCtMainInfo->stSrxblerRdCnf.usSnr[1] = 0;

       stFCtMainInfo->stFtmSparaInfo.usType = 0;
       stFCtMainInfo->stFtmSparaInfo.usValue = 0;
       stFCtMainInfo->stStrxBerRdCnf.ulberErr=0;
       stFCtMainInfo->stStrxBerRdCnf.ulbersum=0;
	stFCtMainInfo->ulCurCmdStepsFlag &=(~CT_S_STEPS_DONE_STRXBER_IND);
	stFCtMainInfo->ulCurCmdStepsFlag &= (~CT_S_STEPS_DONE_SRXBLER_IND);
}

/* ���÷������ģʽ */
VOS_VOID ftm_SetNoneSig(VOS_UINT8 ucNoneSigNal)
{
    (ftm_GetMainInfo()->stFtmCtInfo).ucNoSigFlg = ucNoneSigNal;
}

/* ��ȡ�������ģʽ */
VOS_UINT8 ftm_GetNoneSig(VOS_VOID)
{
    return ((ftm_GetMainInfo()->stFtmCtInfo).ucNoSigFlg);
}

/* ��ȡFTM��ǰģʽ��ͬ���ӿ�, PS���� */
VOS_UINT32 FTM_GetMode(OUT FTM_TMODE_ENUM* penFtmMode)
{
   VOS_UINT32 ret = ERR_FTM_UNKNOWN;

   if(penFtmMode == NULL)
   {
       ret = ERR_FTM_INVALID_PARAMETER;
   }
   else
   {
       SYM_TMODE_ENUM symTmode = (SYM_SYSMODE_ENUM)*ftm_GetTmodeMainInfo();

       if(symTmode == EN_SYM_TMODE_SIGNAL)
       {
           *penFtmMode = EN_FTM_TMODE_SIGNAL;
       }
       else if(symTmode == EN_SYM_TMODE_NONESIGNAL||
		     symTmode == EN_SYM_TMODE_F_NONESIGNAL||
		     symTmode == EN_SYM_TMODE_SYN_NONESIGNAL||
		     symTmode == EN_SYM_TMODE_TDS_FAST_CT||
		     symTmode == EN_SYM_TMODE_TDS_BT||
		     symTmode == EN_SYM_TMODE_COMM_CT)
       {
           *penFtmMode = EN_FTM_TMODE_NONESIGNAL;
       }
       else if(symTmode == EN_SYM_TMODE_RESET)
       {
           *penFtmMode = EN_FTM_TMODE_RESET;
       }
       else if(symTmode == EN_SYM_TMODE_SIGNAL_NOCARD)
       {
           *penFtmMode = EN_FTM_TMODE_SIGNAL_NOCARD;
       }
       else if(symTmode == EN_SYM_TMODE_OFFLINE)
       {
           *penFtmMode = EN_FTM_TMODE_OFFLINE;
       }
       else
       {
           *penFtmMode = EN_FTM_TMODE_UNKNOWN;
       }

       if(symTmode != (VOS_UINT32)EN_SYM_TMODE_UNKNOWN)
       {
           ret = ERR_FTM_SUCCESS;
       }
   }

   return ret;
}


VOS_VOID ftm_MainInfoInit(VOS_VOID)
{
     FTM_CT_F_MANAGE_INFO_STRU *stFCtMainInfo = NULL;

	 /* �������۲� */
	 FTM_SYN_INFO_STRU *stSynInfo = NULL;

    /* 1����ʼ��SYMע��ӿں���ָ�� */
    /* ((FTM_MAIN_INFO_STRU *)ftm_GetMainInfo())->pfnResetSymFunc = NULL; */

    /* 2��TODO:��ʼ����ͨУ׼Ĭ��ֵ������ʱ����(�ݲ�ʵ��) */

	/* bandsw֮�󣬱������÷�����رգ����򲻻��DSP�·�TMODE����(�ο�openChanReq����) */

	(ftm_GetMainInfo()->stFtmCtInfo).ucNoSigFlg = FTM_NONESIG_RTT_CLOSE;

    /* 3����ʼ������У׼Ĭ��ֵ������ʱ���� */
    stFCtMainInfo = ftm_GetFastCTMainInfo();
	stSynInfo = ftm_GetSynMainInfo();

    /* �������б�����ֵ�����뾲̬ȫ�ֱ����е���ȫһ�£�
       ���е�ȡֵȡ����DSP�ṩ�ĳ�ʼֵ */

    stFCtMainInfo->ulCurCmdStepsFlag   = CT_F_STEPS_DONE_NULL    ; /* ��ʼ״̬:��ǰû��ִ���κ����� */
    stFCtMainInfo->enCurMode           = EN_FCHAN_MODE_UNKONWN ;   /* ��ʼ״̬Ϊ��Чģʽ */
    stFCtMainInfo->ucCurBand           = 255;                      /* ��ʼ״̬Ϊ��ЧƵ�� */
    stFCtMainInfo->ucCurWaveType       = TXWAVE_TYPE_CW          ; /* 0->CW���ͣ�DSPĬ������ΪCW���ͣ�*/
    stFCtMainInfo->ucCurTriggerType    = START_TRIGGER_TYPE_TX   ; /* ����ͨ��У׼ */

    stFCtMainInfo->usCurSegmentLen     = 20  ; /* segment���ȣ���λms��Ĭ��ֵΪ20 */
    stFCtMainInfo->usCurMeasOffset     =  0  ; /* ������ʼλ��ƫ�ƣ���λms��ȡֵ��Χ0~19����Ĭ��ֵ */
    stFCtMainInfo->usCurMeasLen        =  1  ; /* �������ȣ���λms��ȡֵ��Χ1~20����Ĭ��ֵ */

    stFCtMainInfo->usCurUlListNum      = 0  ; /* ����У׼�����ŵ�������,Ĭ��ֵΪ0 */
    stFCtMainInfo->usCurDlListNum      = 0  ; /* ����У׼�����ŵ�������,Ĭ��ֵΪ0 */

    stFCtMainInfo->usCurTxPowerNum     = 0  ; /* ������ķ��书�ʵ�������ȡֵ��Χ0��20��Ĭ��ֵΪ0 */
    stFCtMainInfo->usCurPaLevelNum     = 0  ; /* PA�ĵȼ�������ȡֵ��Χ0��20������Ϊһ���ֽڣ���ֵӦ����^FPOWS��power_num��ֵһ�£�Ĭ��ֵΪ0��*/
    stFCtMainInfo->usCurAagcNum        = 0  ; /* LNA�ĵȼ���������ȡֵ��Χ0~20��Ĭ��ֵΪ0�� */
    stFCtMainInfo->usCmtmsNum          = 0  ;  /* �¶�ֵ������ȡֵ��ΧΪ0��16 */
    stFCtMainInfo->usRsv               = 0  ;

    (VOS_VOID)MSP_MEMSET(stFCtMainInfo->ausCurUlFreqInfo  ,0 ,sizeof(stFCtMainInfo->ausCurUlFreqInfo));
    (VOS_VOID)MSP_MEMSET(stFCtMainInfo->ausCurDlFreqInfo  ,0 ,sizeof(stFCtMainInfo->ausCurDlFreqInfo));
    (VOS_VOID)MSP_MEMSET(stFCtMainInfo->asCurTxPowerList  ,0 ,sizeof(stFCtMainInfo->asCurTxPowerList));
    (VOS_VOID)MSP_MEMSET(stFCtMainInfo->aucCurPaLevelList ,0 ,sizeof(stFCtMainInfo->aucCurPaLevelList));
    (VOS_VOID)MSP_MEMSET(stFCtMainInfo->aucCurAagcList    ,0 ,sizeof(stFCtMainInfo->aucCurAagcList));

    (VOS_VOID)MSP_MEMSET(stFCtMainInfo->ausRxANT1RSSI     ,0 ,sizeof(stFCtMainInfo->ausRxANT1RSSI));
    (VOS_VOID)MSP_MEMSET(stFCtMainInfo->ausRxANT2RSSI     ,0 ,sizeof(stFCtMainInfo->ausRxANT2RSSI));
	(VOS_VOID)MSP_MEMSET(stFCtMainInfo->ausCmtms     		,0 ,sizeof(stFCtMainInfo->ausCmtms));

    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliIp2sSetReq ,0 ,sizeof(stFCtMainInfo->stFCaliIp2sSetReq));
    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliIp2sRdCnf  ,0 ,sizeof(stFCtMainInfo->stFCaliIp2sRdCnf));
    stFCtMainInfo->stFCaliIp2sRdCnf.usStatus = FTM_STATUS_EXECUTED;

    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliDcocsSetReq,0 ,sizeof(stFCtMainInfo->stFCaliDcocsSetReq));
    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliDcocsRdCnf ,0 ,sizeof(stFCtMainInfo->stFCaliDcocsRdCnf));
    stFCtMainInfo->stFCaliDcocsRdCnf.usStatus = FTM_STATUS_EXECUTED;

    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFGainStatesSetReq,0 ,sizeof(stFCtMainInfo->stFGainStatesSetReq));

    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliIp2sMrfSetReq ,0 ,sizeof(stFCtMainInfo->stFCaliIp2sMrfSetReq));
    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliIp2sMrfRdCnf  ,0 ,sizeof(stFCtMainInfo->stFCaliIp2sMrfRdCnf));
    stFCtMainInfo->stFCaliIp2sMrfRdCnf.usStatus = FTM_STATUS_EXECUTED;

    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliDcocsMrfSetReq,0 ,sizeof(stFCtMainInfo->stFCaliDcocsMrfSetReq));
    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliDcocsMrfRdCnf ,0 ,sizeof(stFCtMainInfo->stFCaliDcocsMrfRdCnf));
    stFCtMainInfo->stFCaliDcocsMrfRdCnf.usStatus = FTM_STATUS_EXECUTED;

	(VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFDbbAttSetReq    ,0 ,sizeof(stFCtMainInfo->stFDbbAttSetReq));

	(VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFBbAttSetReq	  ,0 ,sizeof(stFCtMainInfo->stFBbAttSetReq));

	(VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliTxiqSetReq  ,0 ,sizeof(stFCtMainInfo->stFCaliTxiqSetReq));
    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCaliTxiqRdCnf   ,0 ,sizeof(stFCtMainInfo->stFCaliTxiqRdCnf));
	(VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCalPDDCSSetReq, 0, sizeof(stFCtMainInfo->stFCalPDDCSSetReq));
    (VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFCalPDDCSRdCnf, 0, sizeof(stFCtMainInfo->stFCalPDDCSRdCnf));
	(VOS_VOID)MSP_MEMSET(&stFCtMainInfo->stFpdpowsSetReq, 0, sizeof(stFCtMainInfo->stFpdpowsSetReq));
    stFCtMainInfo->stFCaliTxiqRdCnf.usStatus = FTM_STATUS_EXECUTED;
    /*****************************************/
    /* �������۲��ʼ�� */
    stSynInfo->ulCurCmdStepsFlag = CT_S_STEPS_DONE_NULL;
	stSynInfo->stSsyncRdCnf.ulStatus = 0;
	stSynInfo->stSsyncRdCnf.ulErrCode = 0;

}

/*****************************************************************************
 �� �� ��  : ftm_get_equipmsg_handler
 ��������  : ͨ����ϢID��ȡװ����Ϣ��������ָ��
 �������  : ulMsgId װ����ϢID
 �������  : ��
 �� �� ֵ  : �ɹ�������Ϣ��������ָ��, ���򷵻�NULL
 *****************************************************************************/
static PFN_AT_FTM_EQUIP_MSG_PROC ftm_get_equipmsg_handler(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulTblSize = sizeof(g_stFtmEquipMsgTbl) / sizeof(FTM_EQUIP_MSG_FUNTBL_STRU);

    for(i=0; i<ulTblSize; i++)
    {
        if(ulMsgId == g_stFtmEquipMsgTbl[i].ulMsgId)
        {
            return g_stFtmEquipMsgTbl[i].pfnEquipMsgProc;
        }
    }

    return NULL;
}

/*****************************************************************************
 �� �� ��  : ftm_get_timeout_handler
 ��������  : ͨ��װ����ϢID��ȡ��ʱ��������ָ��
 �������  : ulMsgId װ����ϢID
 �������  : ��
 �� �� ֵ  : �ɹ�������Ϣ��������ָ��, ���򷵻�NULL
 *****************************************************************************/
static PFN_AT_FTM_TIMEOUT_PROC ftm_get_timeout_handler(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulTblSize = sizeof(g_stFtmEquipMsgTbl) / sizeof(FTM_EQUIP_MSG_FUNTBL_STRU);

    for(i=0; i<ulTblSize; i++)
    {
        if(ulMsgId == g_stFtmEquipMsgTbl[i].ulMsgId)
        {
            return g_stFtmEquipMsgTbl[i].pfnTimeoutProc;
        }
    }

    return NULL;
}
/*****************************************************************************
 �� �� ��  : ftm_get_dspcnfmsg_handler
 ��������  : ͨ��DSPȷ��ԭ����ϢID��ȡ��Ϣ��������ָ��
 �������  : ulMsgId DSPȷ��ԭ����ϢID
 �������  : ��
 �� �� ֵ  : �ɹ�������Ϣ��������ָ��, ���򷵻�NULL
 *****************************************************************************/
static PFN_AT_FTM_DSP_MSP_PROC ftm_get_dspcnfmsg_handler(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulTblSzie = sizeof(g_stFtmDspCnfMsgTbl) / sizeof(FTM_DSP_MSG_FUNTBL_STRU);

    for(i=0; i<ulTblSzie; i++)
    {
        if(ulMsgId == g_stFtmDspCnfMsgTbl[i].ulMsgId)
        {
            return g_stFtmDspCnfMsgTbl[i].pfnDspMsgProc;
        }
    }

    return NULL;
}

/*****************************************************************************
 �� �� ��  : ftm_get_dspindmsg_handler
 ��������  : ͨ��DSP�����ϱ�ԭ����ϢID��ȡ��Ϣ��������ָ��
 �������  : ulMsgId DSPԭ��ԭ����ϢID
 �������  : ��
 �� �� ֵ  : �ɹ�������Ϣ��������ָ��, ���򷵻�NULL
 *****************************************************************************/
static PFN_AT_FTM_DSP_MSP_PROC ftm_get_dspindmsg_handler(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulTblSize = sizeof(g_stFtmDspIndMsgTbl) / sizeof(FTM_DSP_MSG_FUNTBL_STRU);

    for(i=0; i<ulTblSize; i++)
    {
        if(ulMsgId == g_stFtmDspIndMsgTbl[i].ulMsgId)
        {
            return g_stFtmDspIndMsgTbl[i].pfnDspMsgProc;
        }
    }

    return NULL;
}

/*****************************************************************************
 �� �� ��  : ftm_RttMsgProc
 ��������  : DSPԭ����Ϣ����
             1��ȷ��ԭ������ȷ��ԭ�����ô�������������֮���رճ�ʱ������ʱ��
             2�������ϱ�ԭ�����������ϱ�ԭ�����ô�������
 �������  : pMsg DSPԭ����Ϣ
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_FTM_SUCCESS ���򷵻�����
 *****************************************************************************/
VOS_UINT32 ftm_RttMsgProc(OS_MSG_STRU* pMsg)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;
    PFN_AT_FTM_DSP_MSP_PROC pfnDspMsgProc = NULL;
    L1A_CT_IND_STRU* pstDspCt             = NULL;

    pstDspCt = (L1A_CT_IND_STRU*)(pMsg->ulParam1);

    if(NULL == pstDspCt)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ERR_FTM_INVALID_PARAMETER\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_INVALID_PARAMETER;
    }

    /* DSP CNF��Ϣ�������� */
    pfnDspMsgProc = ftm_get_dspcnfmsg_handler(pstDspCt->ulDspId);

    if(NULL != pfnDspMsgProc)
    {
        if(g_ct_cmd_ctrl.ucSta == FTM_CT_WAIT)
        {
            (VOS_VOID)ftm_comm_stoptimer(&g_ct_cmd_ctrl.ulReqTimer);
            g_ct_cmd_ctrl.ucSta = FTM_CT_NORMAL;
            ulRet = (pfnDspMsgProc)(pstDspCt);
        }
        else
        {
            (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]Warning: Released DSP Msg 0x%x\n", __FUNCTION__, __LINE__,VOS_GetSlice(), pMsg->ulMsgId);
        }
        return ulRet;
    }

    /* DSP IND��Ϣ�������� */
    pfnDspMsgProc = ftm_get_dspindmsg_handler(pstDspCt->ulDspId);
    if(NULL != pfnDspMsgProc)
    {
        ulRet = (pfnDspMsgProc)(pstDspCt);
        return ulRet;
    }

    (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]Invalid DSP Msg 0x%x\n", __FUNCTION__, __LINE__,VOS_GetSlice(), pstDspCt->ulDspId);
    return ERR_FTM_NOT_EXIST;
}

/*****************************************************************************
 �� �� ��  : ftm_TimeoutMsgProc
 ��������  : ��ʱ��Ϣ����
             ����װ����Ϣ��������ó�ʱ��������������֮
 �������  : pMsg��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_FTM_SUCCESS, ���򷵻�����
 *****************************************************************************/
VOS_UINT32 ftm_TimeoutMsgProc(OS_MSG_STRU* pMsg)
{
    VOS_UINT32 ulTimeoutMsgId = 0;
    VOS_UINT32 ulRet          = ERR_FTM_SUCCESS;
    OSM_MSG_TIMER_STRU*     pTimerMsg       = NULL;
    PFN_AT_FTM_TIMEOUT_PROC pfnTimeoutProc  = NULL;

    pTimerMsg = (OSM_MSG_TIMER_STRU *)(pMsg->ulParam1);

    if(NULL == pTimerMsg)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]Invalid Msg\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_INVALID_PARAMETER;
    }

    ulTimeoutMsgId = (VOS_UINT32)(pTimerMsg->ulPara);
    pfnTimeoutProc = ftm_get_timeout_handler(ulTimeoutMsgId);
    /* HAL_SDMLOG("\n ftm_TimeoutMsgProc: Timeout Msg ID 0x%x \n", ulTimeoutMsgId); */
    if(NULL == pfnTimeoutProc)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]Invalid Timeout Msg ID: 0x%x \n", __FUNCTION__, __LINE__,VOS_GetSlice(),ulTimeoutMsgId);
        return ERR_FTM_NOT_EXIST;
    }

     /* ��ʱ������ʱ����Ϣ */
    else
    {
        if(g_ct_cmd_ctrl.ucSta == FTM_CT_WAIT)
        {
            (VOS_VOID)ftm_comm_stoptimer(&g_ct_cmd_ctrl.ulReqTimer);
            g_ct_cmd_ctrl.ucSta = FTM_CT_NORMAL;
			/*lint -save -e746*/
            ulRet = (pfnTimeoutProc)();
			/*lint -restore*/
        }
        else
        {
            (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]Waring: Released Timeout Msg 0x%xn", __FUNCTION__, __LINE__,VOS_GetSlice(),pMsg->ulMsgId);
        }
        return ulRet;
    }
}

/*****************************************************************************
 �� �� ��  : ftm_CmdMsgProc
 ��������  : A�˷��͵�װ����Ϣ����
             ����װ����Ϣ��������ô�������������֮���رճ�ʱ������ʱ��
 �������  : pMsgװ����Ϣ
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_FTM_SUCCESS, ���򷵻�����
 *****************************************************************************/
VOS_UINT32 ftm_CmdMsgProc(OS_MSG_STRU* pMsg)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;
    PFN_AT_FTM_EQUIP_MSG_PROC pfnEquipMsgProc = NULL;

    pfnEquipMsgProc = ftm_get_equipmsg_handler(pMsg->ulMsgId);
    if(NULL != pfnEquipMsgProc)
    {
        if(g_ct_cmd_ctrl.ucSta == FTM_CT_NORMAL)
	    {
	        ulRet = (pfnEquipMsgProc)((VOS_VOID *)pMsg->ulParam1);

            if(ulRet == ERR_FTM_WAIT_ASYNC)
            {
                (VOS_VOID)ftm_comm_starttimer(&g_ct_cmd_ctrl.ulReqTimer, pMsg->ulMsgId);
                g_ct_cmd_ctrl.ucSta = FTM_CT_WAIT;
                return ERR_FTM_SUCCESS;
            }
            else if(ulRet == ERR_FTM_SUCCESS)
            {
                return ERR_FTM_SUCCESS;
            }
            else
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]Warning: Msg 0x%x processed abnormal\n", __FUNCTION__, __LINE__,VOS_GetSlice(), pMsg->ulMsgId);
                return ulRet;
            }
        }
        else
        {
            (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]Warning: Discarded Msg 0x%x\n", __FUNCTION__, __LINE__,VOS_GetSlice(), pMsg->ulMsgId);
        }
    }

   return ERR_FTM_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : ftm_TaskMsg
 ��������  : FTM������Ϣ�����������Է��͵�����Ϣ���зַ�����
 �������  : pMsg ��Ϣ����
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_FTM_SUCCESS, ���򷵻�����
 *****************************************************************************/
VOS_UINT32 ftm_TaskMsg(OS_MSG_STRU * pMsg)
{
    VOS_UINT32 ulRet = ERR_FTM_FAILURE;

    if (NULL == pMsg)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]Invalid Msg\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_INVALID_PARAMETER;
    }

    switch(pMsg->ulMsgId)
    {
        case ID_MSG_L1A_CT_IND:
            ulRet = ftm_RttMsgProc(pMsg);
            break;

        case ID_MSG_FTM_TIME_OUT:
            ulRet = ftm_TimeoutMsgProc(pMsg);
            break;

        default :
            ulRet = ftm_CmdMsgProc(pMsg);
    }

    /* PS��������ulParam1�Ƕ�̬�ڴ治��Ҫ�ͷţ��������ͷ� */
    if( ID_T_PS_MSP_SFN_SYNC_CNF != pMsg->ulMsgId)
    {
        if (NULL != pMsg->ulParam1)
        {
        	/*lint -save -e740*/
			(VOS_VOID)VOS_MemFree(MSP_SYS_FTM_PID, pMsg->ulParam1);
			/*lint -restore*/
        }
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : FTM_MsgConvert
 ��������  : ��Ϣ��ʽת���ӿ�(����AT�Ƶ�A�ˣ���Ϣ���ܴ���ָ�룬����ԭ�нӿ�)
 �������  : MsgBlock* pMsg
             OS_MSG_STRU* pstFtmMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��28��
    ��    ��   : ������/wx26324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FTM_MsgConvert(MsgBlock* pMsg, OS_MSG_STRU* pstFtmMsg)
{
	/*lint -save -e740*/
	AT_FW_DATA_MSG_STRU* pDataMsg = (AT_FW_DATA_MSG_STRU*)pMsg;
	/*lint -restore*/

    g_ulCrntClientId = pDataMsg->ulClientId;
    pstFtmMsg->ulMsgId = pDataMsg->ulMsgId;

    pstFtmMsg->ulParam1 = VOS_MemAlloc(MSP_SYS_FTM_PID, (DYNAMIC_MEM_PT), pDataMsg->ulLen);
    if(pstFtmMsg->ulParam1 == NULL)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]VOS_MemAlloc failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_FAILURE;
    }

    (VOS_VOID)MSP_MEMCPY(pstFtmMsg->ulParam1, pDataMsg->pContext, pDataMsg->ulLen);
    pstFtmMsg->ulParam2 = pDataMsg->ulLen;

    return ERR_FTM_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : ftm_SendDataMsg
 ��������  : FTM��AT������Ϣ�ӿ�(����AT�Ƶ�A�ˣ���Ϣ���ܴ���ָ�룬����ԭ�нӿ�)
 �������  : VOS_UINT32 ulSenderId
             VOS_UINT32 ulRecverId
             VOS_UINT32 ulMsgId
             VOS_UINT32 ulParam1
             VOS_UINT32 ulParam2
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��28��
    ��    ��   : ������/wx26324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 ftm_SendDataMsg(VOS_UINT32 ulSenderId, VOS_UINT32 ulRecverId, VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2)
{
    VOS_UINT32 ret = ERR_FTM_UNKNOWN;

    AT_FW_DATA_MSG_STRU* pDataMsg = NULL;
	/*lint -save -e740*/
    pDataMsg = (AT_FW_DATA_MSG_STRU*)VOS_AllocMsg(ulSenderId,(sizeof(AT_FW_DATA_MSG_STRU)+ ulParam2 - VOS_MSG_HEAD_LENGTH));
	/*lint -restore*/

    (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]MsgId 0x%x, address: 0x%x, length: 0x%x \n",__FUNCTION__, __LINE__,VOS_GetSlice(),ulMsgId,ulParam1, ulParam2);

    if (pDataMsg)
    {
        pDataMsg->ulReceiverPid = ulRecverId;
        pDataMsg->ulSenderPid   = ulSenderId;
        pDataMsg->ulLength      = sizeof(AT_FW_DATA_MSG_STRU)+ ulParam2 - VOS_MSG_HEAD_LENGTH;

        pDataMsg->ulClientId = g_ulCrntClientId;
        pDataMsg->ulMsgId    = ulMsgId;
        pDataMsg->ulLen      = ulParam2;
        (VOS_VOID)MSP_MEMCPY(pDataMsg->pContext,(VOS_UINT8*)ulParam1,ulParam2);

        ret = VOS_SendMsg(ulSenderId, pDataMsg);
        if (ret != VOS_OK)
        {
            (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] VOS_SendMsg failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        }
        else
        {
            ret = ERR_FTM_SUCCESS;
        }

    }
    return ret;
}

/*****************************************************************************
 �� �� ��  : atFTMSendVosMsg
 ��������  : FTM������ģ�鷢��VOSMSG
 �������  : TaskId  ����ģ��ID
                            pData  ��Ϣָ��
                            uLen   ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_UINT32 atFTMSendVosMsg(VOS_UINT32 TaskId, IN VOS_VOID* pData, VOS_UINT32 uLen)
{
    VOS_UINT32 ulRet = ERR_FTM_UNKNOWN;
    MsgBlock *pMsgBlock = NULL;

    pMsgBlock = VOS_AllocMsg(MSP_SYS_FTM_PID, uLen);
    if(NULL == pMsgBlock)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] VOS_AllocMsg failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_MALLOC_FAILUE;
    }

    pMsgBlock->ulReceiverPid = TaskId;
    pMsgBlock->ulSenderPid   = MSP_SYS_FTM_PID;

	/*lint -e419*/
	(VOS_VOID)VOS_MemCpy(pMsgBlock->aucValue, pData, uLen);
	/*lint -e419*/
    ulRet = VOS_SendMsg(MSP_SYS_FTM_PID, pMsgBlock);
    if (VOS_OK != ulRet)
    {
/*        VOS_FreeMsg(sda_GetMspDsMuxPid(), (PVOID_T)pMsgBlock);*/
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] VOS_SendMsg failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
    }
    else
    {
        ulRet = ERR_FTM_SUCCESS;
    }

    return ulRet;
}

