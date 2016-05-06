/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "TafAppXsmsInterface.h"
#include "TafXsmsStkInterface.h"
#include "TafXpdsXsmsInterface.h"
#include "xcc_sms_pif.h"
#include "cas_1x_control_main_nas_pif.h"
#include "TafXsmsInterMsg.h"
#include "AtXpdsInterface.h"
#include "xcc_xpds_pif.h"
#include "TafXpdsSndInternalMsg.h"
#include "CnasXregSndInternalMsg.h"
#include "CnasXregListProc.h"
#include "CnasXregProcess.h"
#include "CnasHsdSndInternalMsg.h"
#include "CnasHsdMntn.h"
#include "CnasMntn.h"
#include "SysNvId.h"
#include "xsd_xreg_pif.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"
#endif

#include "UsimmApi.h"
#include "UsimPsInterface.h"
#include "siapppih.h"
#include "siappstk.h"
#include "si_pih.h"
#include "si_stk.h"
#include "si_pb.h"
#include "AtOamInterface.h"
#include "AtCsimagent.h"
#include "csimagent.h"
#include "CbpaPsInterface.h"


int pam_main()
{
    /* enum define */
    /* uism */
    enum USIMM_AUTH_TYPE_ENUM                           enUSIMM_AUTH_TYPE_ENUM;
    enum USIMM_POLL_FCP_ENUM                            enUSIMM_POLL_FCP_ENUM;
    enum USIMM_FBDN_HANDLE_ENUM                         enUSIMM_FBDN_HANDLE_ENUM;
    enum USIMM_PB_INIT_STATUS_ENUM                      enUSIMM_PB_INIT_STATUS_ENUM;
    enum USIMM_RESTRIC_CMD_ENUM                         enUSIMM_RESTRIC_CMD_ENUM;
    enum USIMM_CMDTYPE_REQ_ENUM                         enUSIMM_CMDTYPE_REQ_ENUM;
    enum USIMM_CARDAPP_ENUM                             enUSIMM_CARDAPP_ENUM;
    enum USIMM_PIN_CMD_TYPE_ENUM                        enUSIMM_PIN_CMD_TYPE_ENUM;
    enum USIMM_PIN_TYPE_ENUM                            enUSIMM_PIN_TYPE_ENUM;

#if (FEATURE_OFF == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    enum CBP_MODEM_RESET_STATUS_ENUM                    enCBP_MODEM_RESET_STATUS_ENUM;
    enum CBPCA_MSG_TYPE_ENUM                            enCBPCA_MSG_TYPE_ENUM;
#endif

    enum CSIMA_CBP_UICC_MSGID_ENUM                      enCSIMA_CBP_UICC_MSGID_ENUM;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* xsms */
    enum TAF_XSMS_SEND_OPTION_ENUM                      enTAF_XSMS_SEND_OPTION_ENUM;
    enum TAF_XSMS_AP_MEM_FULL_ENUM                      enTAF_XSMS_AP_MEM_FULL_ENUM;
    enum TAF_XSMS_STATUS_ENUM                           enTAF_XSMS_STATUS_ENUM;
    enum TAF_XSMS_STK_MSG_TYPE_ENUM                     enTAF_XSMS_STK_MSG_TYPE_ENUM;
    enum TAF_XPDS_XSMS_MSG_TYPE_ENUM                    enTAF_XPDS_XSMS_MSG_TYPE_ENUM;
    enum XCC_SMS_PIF_MSG_TYPE_ENUM                      enXCC_SMS_PIF_MSG_TYPE_ENUM;
    enum TAF_XSMS_TL_ERROR_CLASS_ENUM                   enTAF_XSMS_TL_ERROR_CLASS_ENUM;
    enum TAF_XSMS_TL_CAUSE_CODE_ENUM                    enTAF_XSMS_TL_CAUSE_CODE_ENUM;

    /* XCC XSMS */
    enum TAF_CDMA_SO_TYPE_ENUM                          enTAF_CDMA_SO_TYPE_ENUM;
    enum TAF_XCC_CAUSE_ENUM                             enTAF_XCC_CAUSE_ENUM;
    enum TAF_XCC_FAIL_LAYER_ENUM                        enTAF_XCC_FAIL_LAYER_ENUM;
    enum TAF_XCC_END_REASON_ENUM                        enTAF_XCC_END_REASON_ENUM;
    enum XCC_CSMS_RESULT_ENUM                           enXCC_CSMS_RESULT_ENUM;

    /* CAS XSMS(XPDS) */
    enum CAS_1X_CONTROL_MAIN_NAS_PIF_MSG_TYPE_ENUM      enCAS_1X_CONTROL_MAIN_NAS_PIF_MSG_TYPE_ENUM;
    enum CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM               enCAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM;
    enum PS_BOOL_ENUM                                   enPS_BOOL_ENUM;
    enum CAS_CNAS_1X_DATA_CNF_RSLT_ENUM                 enCAS_CNAS_1X_DATA_CNF_RSLT_ENUM;
    enum CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM               enCAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM;
    enum CAS_CNAS_1X_TX_COMMON_MSG_TYPE_ENUM            enCAS_CNAS_1X_TX_COMMON_MSG_TYPE_ENUM;
    enum CAS_CNAS_1X_DATA_BURST_TYPE_ENUM               enCAS_CNAS_1X_DATA_BURST_TYPE_ENUM;
    enum CAS_CNAS_1X_MSG_DATA_TYPE_ENUM                 enCAS_CNAS_1X_MSG_DATA_TYPE_ENUM;
    enum CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM            enCAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM;
    enum TAF_XSMS_MT_FSM_ID_ENUM                        enTAF_XSMS_MT_FSM_ID_ENUM;
    enum TAF_XSMS_MO_FSM_ID_ENUM                        enTAF_XSMS_MO_FSM_ID_ENUM;

    /*XPDS AT*/
    enum TAF_XPDS_INITIAL_TYPE_ENUM                     enTAF_XPDS_INITIAL_TYPE_ENUM;
    enum XPDS_AT_RESULT_ENUM                            enXPDS_AT_RESULT_ENUM;
    enum TAF_XPDS_CALL_TYPE_ENUM                        enTAF_XPDS_CALL_TYPE_ENUM;
    enum TAF_XPDS_FIX_MODE_ENUM                         enTAF_XPDS_FIX_MODE_ENUM;
    enum AT_XPDS_REPLY_SYNC_TIME_ENUM                   enAT_XPDS_REPLY_SYNC_TIME_ENUM;
    enum XPDS_AT_SYNC_TIME_ENUM                         enXPDS_AT_SYNC_TIME_ENUM;
    enum TAF_MSG_CDMA_GPS_FIX_QUALITY_ENUM              enTAF_MSG_CDMA_GPS_FIX_QUALITY_ENUM;
    enum TAF_MSG_CDMA_GPS_FIX_TYPE_ENUM                 enTAF_MSG_CDMA_GPS_FIX_TYPE_ENUM;
    enum TAF_MSG_CDMA_GPS_SELECTION_TYPE_ENUM           enTAF_MSG_CDMA_GPS_SELECTION_TYPE_ENUM;
    enum AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ENUM           enAT_XPDS_GPS_NI_REQ_REPLY_RESULT_ENUM;
    enum AT_XPDS_GPS_NI_REQ_REJECT_TYPE_ENUM            enAT_XPDS_GPS_NI_REQ_REJECT_TYPE_ENUM;
    enum TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_ENUM      enTAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_ENUM;
    enum TAF_XPDS_POS_TECH_INDICATOR_ENUM               enTAF_XPDS_POS_TECH_INDICATOR_ENUM;
    enum TAF_XPDS_IS801_MODE_ENUM                       enTAF_XPDS_IS801_MODE_ENUM;
    enum XPDS_AT_ABORT_POS_REASON_ENUM                  enXPDS_AT_ABORT_POS_REASON_ENUM;

    /* XPDS XCC */
    enum AT_XPDS_AGPS_DATA_CALL_CTRL_ENUM               enAT_XPDS_AGPS_DATA_CALL_CTRL_ENUM;
    enum AT_XPDS_DATA_CALL_STATUS_ENUM                  enAT_XPDS_DATA_CALL_STATUS_ENUM;
    enum AT_XPDS_SERVER_MODE_ENUM                       enAT_XPDS_SERVER_MODE_ENUM;
    enum AT_XPDS_SERVER_BIND_STATUS_ENUM                enAT_XPDS_SERVER_BIND_STATUS_ENUM;
    enum XCC_AGPS_PIF_MSG_TYPE_ENUM                     enXCC_AGPS_PIF_MSG_TYPE_ENUM;
    enum XCC_XPDS_RESULT_ENUM                           enXCC_XPDS_RESULT_ENUM;

    /* XPDS CAS */
    enum XPDS_CAS_REF_LOC_RPT_TYPE_ENUM                 enXPDS_CAS_REF_LOC_RPT_TYPE_ENUM;
    enum XPDS_CAS_RESULT_ENUM                           enXPDS_CAS_RESULT_ENUM;

    /* XPDS XPDS */
    enum TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM             enTAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM;
    enum TAF_XPDS_SERVER_BIND_OPER_ENUM                 enTAF_XPDS_SERVER_BIND_OPER_ENUM;
    enum TAF_XPDS_POS_PROC_RSLT_ENUM                    enTAF_XPDS_POS_PROC_RSLT_ENUM;
    enum TAF_XPDS_MPC_OPER_TYPE_ENUM                    enTAF_XPDS_MPC_OPER_TYPE_ENUM;

    /* xreg */
    enum CNAS_XREG_INTERNAL_MSG_TYPE_ENUM               enCNAS_XREG_INTERNAL_MSG_TYPE_ENUM;
    enum CAS_CNAS_1X_REGISTRATION_TYPE_ENUM             enCAS_CNAS_1X_REGISTRATION_TYPE_ENUM;
    enum CNAS_XREG_REG_RESULT_ENUM                      enCNAS_XREG_REG_RESULT_ENUM;
    enum CNAS_XREG_REGING_STA_ENUM                      enCNAS_XREG_REGING_STA_ENUM;
    enum CNAS_XREG_SWITCH_ON_RESULT_ENUM                enCNAS_XREG_SWITCH_ON_RESULT_ENUM;
    enum CNAS_XREG_MNTN_MSGID_ENUM                      enCNAS_XREG_MNTN_MSGID_ENUM;
    enum CNAS_XREG_L1_STA_ENUM                          enCNAS_XREG_L1_STA_ENUM;
    enum XSD_XREG_PIF_MSG_TYPE_ENUM                     enXSD_XREG_PIF_MSG_TYPE_ENUM;

    enum CNAS_XREG_VAR_VALUE_ENUM                       enCNAS_XREG_VAR_VALUE_ENUM;
    enum CNAS_XREG_TIMER_STATE_ENUM                     enCNAS_XREG_TIMER_STATE_ENUM;
    enum CAS_CNAS_1X_CAS_STATE_ENUM                     enCAS_CNAS_1X_CAS_STATE_ENUM;
    enum CNAS_XREG_BLKSYS_ENUM                          enCNAS_XREG_BLKSYS_ENUM;
    enum NAS_OM_CDMA_REG_TYPE_ENUM                      enNAS_OM_CDMA_REG_TYPE_ENUM;

    /*hsd*/
    enum CNAS_HSD_FSM_ID_ENUM                           enCNAS_HSD_FSM_ID_ENUM;
    enum CNAS_HSD_SYS_ACQ_SCENE_ENUM                    enCNAS_HSD_SYS_ACQ_SCENE_ENUM;
    enum CNAS_HSD_AVOID_ITEM_USED_FALG_ENUM             enCNAS_HSD_AVOID_ITEM_USED_FALG_ENUM;
    enum CNAS_HSD_INTERNAL_MSG_TYPE_ENUM                enCNAS_HSD_INTERNAL_MSG_TYPE_ENUM;
    enum CNAS_HSD_ABORT_TYPE_ENUM                       enCNAS_HSD_ABORT_TYPE_ENUM;
    enum CNAS_HSD_SWITCH_ON_RESULT_ENUM                 enCNAS_HSD_SWITCH_ON_RESULT_ENUM;
    enum CNAS_HSD_BSR_RESULT_ENUM                       enCNAS_HSD_BSR_RESULT_ENUM;
    enum CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM         enCAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM;
    enum CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM                 enCNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM;
    enum VOS_RATMODE_ENUM                               enVOS_RATMODE_ENUM_UINT32;
    enum CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM                enCNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM;
    enum CAS_HRPD_AIRLINKMGMT_NAS_PIF_MSG_TYPE_ENUM     enCAS_HRPD_AIRLINKMGMT_NAS_PIF_MSG_TYPE_ENUM;
    enum CNAS_HSD_PRL_SOURCE_TYPE_ENUM                  enCNAS_HSD_PRL_SOURCE_TYPE_ENUM;
    enum SYS_NV_ID_ENUM                                 enSYS_NV_ID_ENUM;
    enum CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM           enCNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM;
#endif

    /* USIMM */

    USIMM_ACTIVECARD_REQ_STRU usimm_activecard_req_stru;
    USIMM_INITCONTINUE_REQ_STRU usimm_initcontinue_req_stru;
    USIMM_PROTECTRESET_REQ_STRU usimm_protectreset_req_stru;
    USIMM_DEACTIVECARD_REQ_STRU usimm_deactivecard_req_stru;
    USIMM_READFILE_REQ_STRU usimm_readfile_req_stru;
    USIMM_QUERYFILE_REQ_STRU usimm_queryfile_req_stru;
    USIMM_STATUSCMD_REQ_STRU usimm_statuscmd_req_stru;
    USIMM_SEARCHFILE_REQ_STRU usimm_searchfile_req_stru;
    USIMM_FDNPROCESS_REQ_STRU usimm_fdnprocess_req_stru;
    USIMM_OPENCHANNEL_REQ_STRU usimm_openchannel_req_stru;
    USIMM_CLOSECHANNEL_REQ_STRU usimm_closechannel_req_stru;
    USIMM_SENDTPDUDATA_REQ_STRU usimm_sendtpdudata_req_stru;
    USIMM_TERMINALRESPONSE_REQ_STRU usimm_termianlresponse_stru;
    USIMM_STKENVELOPE_REQ_STRU usimm_envelope_req_stru;
    USIMM_STKREFRESH_REQ_STRU usimm_stkrefresh_req_stru;
    USIMM_PBINIT_STATUS_IND_STRU usimm_pbinit_status_ind_stru;
    USIMM_RACCESS_REQ_STRU usimm_raccess_req_stru;
    USIMM_SETMUTILFILE_REQ_STRU usimm_setmutilfile_req_stru;
    USIMM_HOTINOUT_IND_STRU usimm_hotinout_ind_stru;
    USIMM_CARD_STATUS_IND_STRU usimm_card_status_ind_stru;
    USIMM_CMDHEADER_REQ_STRU usimm_cmdheader_req_stru;
    USIMM_AUTHENTICATION_REQ_STRU usimm_authentication_req_stru;
    USIMM_PINHANDLE_REQ_STRU usimm_pinhandle_req_stru;
    USIMM_UPDATEFILE_REQ_STRU usimm_updatefile_req_stru;
#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    USIMM_CARDTIMEOUT_IND_STRU usimm_cardtimeoutind_stru;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    USIMM_BSCHALLENGE_REQ_STRU usimm_basechallenge_req_stru;
    USIMM_GENERATE_KEYVPM_REQ_STRU usimm_generate_keyvpm_req_stru;
    USIMM_MANAGESSD_REQ_STRU usimm_managessd_req_stru;
    USIMM_CDMASPECAUTH_REQ_STRU usimm_cdmaspecauth_req_stru;
    USIMM_QUERYESNMEIDRSLT_REQ_STRU usimm_queryesnmeidrslt_req_stru;
#endif

    USIMM_PINHANDLE_CNF_STRU usimm_pinhandle_cnf_stru;
    USIMM_UPDATEFILE_CNF_STRU usimm_updatefile_cnf_stru;
    USIMM_READFILE_CNF_STRU usimm_readfile_cnf_stru;
    USIMM_STKREFRESH_CNF_STRU usimm_stkrefresh_cnf_stru;
    USIMM_AUTHENTICATION_CNF_STRU usimm_authentication_cnf_stru;
    USIMM_RACCESS_CNF_STRU usimm_raccess_cnf_stru;
    USIMM_STKTERMINALRSP_CNF_STRU usimm_stkterminalrsp_cnf_stru;
    USIMM_STKENVELOPE_CNF_STRU usimm_stkenvelope_cnf_stru;
    USIMM_SINGLECMD_CNF_STRU usimm_singlecmd_cnf_stru;
    USIMM_FDNPROCESS_CNF_STRU usimm_fdnprocess_cnf_stru;
    USIMM_SETMUTILFILE_CNF_STRU usimm_setmutilfile_cnf_stru;
    USIMM_SEARCHFILE_CNF_STRU usimm_searchfile_cnf_stru;
    USIMM_OPENCHANNEL_CNF_STRU usimm_openchannel_cnf_stru;
    USIMM_CLOSECHANNEL_CNF_STRU usimm_closechannel_cnf_stru;
    USIMM_SENDTPDUDATA_CNF_STRU usimm_sendtpdudata_cnf_stru;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    USIMM_BSCHALLENGE_CNF_STRU usimm_bschallenge_cnf_stru;
    USIMM_GENERATE_KEYVPM_CNF_STRU usimm_generate_keyvpm_cnf_stru;
    USIMM_QUERYESNMEIDRSLT_CNF_STRU usimm_queryesnmeidrslt_cnf_stru;
    USIMM_CDMASPECAUTH_CNF_STRU usimm_cdmaspecauth_cnf_stru;
#endif

    USIMM_CARDSTATUS_IND_STRU usimm_cardstatusind_stru;
    USIMM_STKDATA_IND_STRU usimm_stkdata_ind_stru;
    USIMM_VSIM_RDH_IND_STRU usimm_vsim_rdh_ind_stru;
    USIMM_ECCNUMBER_IND_STRU usimm_eccnumber_ind_stru;
    USIMM_XECCNUMBER_IND_STRU usimm_xeccnumber_ind_stru;

    SI_PIH_FDN_ENABLE_REQ_STRU si_pih_fdn_enable_req_stru;
    SI_PIH_FDN_DISABLE_REQ_STRU si_pih_fdn_disable_req_stru;
    SI_PIH_MSG_HEADER_STRU si_pih_msg_header_stru;
    SI_PIH_GACCESS_REQ_STRU si_pih_gaccess_req_stru;
    SI_PIH_ISDB_ACCESS_REQ_STRU si_pih_isdb_access_req_stru;
    SI_PIH_CCHO_SET_REQ_STRU si_pih_ccho_set_req_stru;
    SI_PIH_CCHC_SET_REQ_STRU si_pih_cchc_set_req_stru;
    SI_PIH_CGLA_REQ_STRU si_pih_cgla_req_stru;
    SI_PIH_HVSST_REQ_STRU si_pih_hvsst_req_stru;
    SI_PIH_SCICFG_SET_REQ_STRU si_pih_scicfg_req_stru;
    SI_PIH_HVCHECKCARD_REQ_STRU si_pih_hvcheckcard_req_stru;
    SI_PIH_UICCAUTH_REQ_STRU si_pih_uiccauth_req_stru;
    SI_PIH_ACCESSFILE_REQ_STRU si_pih_accessfile_req_stru;
    SI_PIH_CRSM_SET_REQ_STRU si_pih_crsm_set_req_stru;
    SI_PIH_CRLA_SET_REQ_STRU si_pih_crla_set_req_stru;
    MN_APP_PIH_AT_CNF_STRU mn_app_pih_at_cnf_stru;
    SI_PIH_PCSC_REQ_STRU si_pih_pcsc_req_stru;
    SI_PIH_HVSDH_SET_REQ_STRU si_pih_hvsdh_set_req_stru;
    SI_PIH_HVS_QRY_REQ_STRU si_pih_hvs_qry_req_stru;
    SI_PIH_FILE_WRITE_REQ_STRU si_pih_file_write_req_stru;
    SI_PIH_HVTEE_SET_REQ_STRU si_pih_hvtee_set_req_stru;

    SI_STK_REQ_STRU si_stk_req_stru;
    STK_AS_TA_INFO_REQ_STRU stk_as_ta_info_req_stru;
    STK_AS_NMR_INFO_REQ_STRU stk_as_nmr_info_req_stru;
    SI_STK_TAF_SENDMSG_STRU si_stk_taf_sendmsg_stru;
    SI_STK_ENVELOPEDOWN_REQ_STRU si_stk_envelopedown_req_stru;
    MN_APP_STK_AT_CNF_STRU mn_app_stk_at_cnf_stru;
    STK_NAS_STEERING_OF_ROAMING_STRU stk_nas_steering_of_roaming_stru;
    SI_PIH_DSP_LIMIT_STRU si_pih_dsp_limit_stru;

    SI_PB_READ_REQ_STRU si_pb_read_req_stru;
    SI_PB_QUERY_REQ_STRU si_pb_query_req_stru;
    SI_PB_SET_REQ_STRU si_pb_set_req_stru;
    SI_PB_ADD_REP_STRU si_pb_add_req_stru;
    SI_PB_MODIFY_REP_STRU si_pb_modify_req_stru;
    SI_PB_DELETE_REQ_STRU si_pb_delete_req_stru;
    SI_PB_SEARCH_REQ_STRU si_pb_search_req_stru;
    SI_PB_ECALLQRY_REQ_STRU si_pb_ecall_req_stru;
    SI_PB_ECALLINIT_IND_STRU si_pb_ecallinit_ind_stru;
    SI_PB_FDN_CHECK_REQ_STRU si_pb_fdn_check_req_stru;
    SI_PB_UPDATEGLOBAL_IND_STRU si_pb_updateglobal_ind_stru;
    SI_PB_SETPB_IND_STRU si_pb_setpb_ind_stru;
    MN_APP_PB_AT_CNF_STRU mn_app_pb_at_cnf_stru;
    MN_APP_CALL_CALLORIG_REQ_STRU mn_app_call_callorig_req_stru;
    SI_PIH_CHANGEPOLLTIMER_REQ_STRU si_pih_changeepolltimer_req_stru;
    SI_PB_ECALLQRY_CNF_STRU si_pb_ecallqry_cnf_stru;

#if (FEATURE_OFF == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    AT_CSIMA_RESET_STATUS_IND_MSG_STRU at_csima_reset_status_ind_msg_stru;
    CBPCA_DATA_IND_MSG_STRU cbpca_data_ind_msg_stru;
#endif

    CSIMA_STK_PROACTIVE_CMD_MSG_STRU csima_stk_proactive_cmd_msg_stru;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* at xsms stru */
    TAF_XSMS_SEND_MSG_REQ_STRU taf_xsms_send_msg_req_stru;
    TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU taf_xsms_app_msg_set_ap_mem_full_req_stru;
    TAF_XSMS_WRITE_MSG_REQ_STRU taf_xsms_write_msg_req_stru;
    TAF_XSMS_DELETE_MSG_REQ_STRU taf_xsms_delete_msg_req_stru;
    TAF_XSMS_INIT_IND_STRU taf_xsms_init_ind_stru;
    TAF_XSMS_WRITE_CNF_STRU taf_xsms_write_cnf_stru;
    TAF_XSMS_SEND_SUCC_IND_STRU taf_xsms_send_succ_ind_stru;
    TAF_XSMS_RCV_IND_STRU taf_xsms_rcv_ind_stru;
    TAF_XSMS_MESSAGE_STRU taf_xsms_message_stru;
    TAF_XSMS_APP_AT_CNF_STRU taf_xsms_app_at_cnf_stru;

    /* stk xsms*/
    XSMS_STK_SEND_SMS_CNF_STRU xsms_stk_send_sms_cnf_stru;
    XSMS_STK_SEND_SMS_RSLT_IND_STRU xsms_stk_send_sms_rslt_ind_stru;
    XSMS_STK_RCV_SMS_IND_STRU xsms_stk_rcv_sms_ind_stru;
    STK_XSMS_SEND_SMS_REQ_STRU stk_xsms_send_sms_req_stru;

    /* xpds xsms*/
    TAF_XSMS_XPDS_REV_IND_STRU taf_xsms_xpds_rev_ind_stru;
    TAF_XPDS_XSMS_SEND_REQ_STRU taf_xpds_xsms_send_req_stru;

    /* XCC XSMS */
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU csms_xcc_orig_sms_call_req_stru;
    XCC_CSMS_ORIG_SMS_CALL_CNF_STRU xcc_csms_orig_sms_call_cnf_stru;
    CSMS_XCC_END_SMS_CALL_REQ_STRU csms_xcc_end_sms_call_req_stru;
    XCC_CSMS_END_SMS_CALL_CNF_STRU xcc_csms_end_sms_call_cnf_stru;
    XCC_CSMS_INCOMING_CALL_IND_STRU xcc_csms_incoming_call_ind_stru;
    CSMS_XCC_INCOMING_CALL_RSP_STRU csms_xcc_incoming_call_rsp_stru;
    XCC_CSMS_CALL_CONN_IND_STRU xcc_csms_call_conn_ind_stru;
    CSMS_XCC_ANSWER_CALL_REQ_STRU csms_xcc_answer_call_req_stru;
    XCC_CSMS_ANSWER_CALL_CNF_STRU xcc_csms_answer_call_cnf_stru;
    XCC_CSMS_MESSAGE_WAITING_IND_STRU xcc_csms_message_waiting_ind_stru;
    XCC_CSMS_SERVICE_CONNECT_IND_STRU xcc_csms_service_connect_ind_stru;
    XCC_CSMS_MSG_WATING_IND_STRU xcc_csms_msg_wating_ind_stru;
    /* CAS XSMS(XPDS) */
    CNAS_CAS_1X_DSCH_DATA_REQ_STRU cnas_cas_1x_dsch_data_req_stru;
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU cas_cnas_1x_dsch_data_cnf_stru;
    CAS_CNAS_1X_DSCH_DATA_IND_STRU cas_cnas_1x_dsch_data_ind_stru;
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU cnas_cas_1x_csch_data_req_stru;
    CAS_CNAS_1X_CSCH_DATA_CNF_STRU cas_cnas_1x_csch_data_cnf_stru;
    CAS_CNAS_1X_CSCH_DATA_IND_STRU cas_cnas_1x_csch_data_ind_stru;
    CAS_CNAS_1X_SMS_ABORT_IND_STRU cas_cnas_1x_sms_abort_ind_stru;

    /* XSMS XSMS */
    TAF_XSMS_INT_3RD_PARTY_ERR_STRU taf_xsms_int_3rd_party_err_stru;
    TAF_XSMS_INT_CUR_MO_FSM_STRU taf_xsms_int_cur_mo_fsm_stru;
    TAF_XSMS_INT_CUR_MT_FSM_STRU taf_xsms_int_cur_mt_fsm_stru;
    TAF_XSMS_INT_SMS_CONTENT_STRU taf_xsms_int_sms_content_stru;
    TAF_XSMS_INT_TL_ACK_STRU taf_xsms_int_tl_ack_stru;

    /*XPDS AT*/
    AT_XPDS_GPS_START_REQ_STRU at_xpds_gps_start_req_stru;
    XPDS_AT_RESULT_CNF_STRU xpds_at_result_cnf_stru;
    AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU at_xpds_gps_cfg_mpc_addr_req_stru;
    AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU at_xpds_gps_cfg_pde_addr_req_stru;
    AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU at_xpds_gps_cfg_position_mode_req_stru;
    AT_XPDS_RESERVE_STRU at_xpds_reserve_stru;
    XPDS_AT_GPS_REFLOC_INFO_CNF_STRU xpds_at_gps_refloc_info_cnf_stru;
    AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU at_xpds_gps_qry_time_info_req_stru;
    XPDS_AT_GPS_SYNC_TIME_IND_STRU xpds_at_gps_sync_time_ind_stru;
    AT_XPDS_GPS_PRM_INFO_RSP_STRU at_xpds_gps_prm_info_rsp_stru;
    AT_XPDS_GPS_POS_INFO_RSP_STRU at_xpds_gps_pos_info_rsp_stru;
    AT_XPDS_GPS_REPLY_NI_RSP_STRU at_xpds_gps_reply_ni_rsp_stru;
    XPDS_AT_GPS_ION_INFO_IND_STRU xpds_at_gps_ion_info_ind_stru;
    XPDS_AT_GPS_EPH_INFO_IND_STRU xpds_at_gps_eph_info_ind_stru;
    XPDS_AT_GPS_ALM_INFO_IND_STRU xpds_at_gps_alm_info_ind_stru;
    XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU xpds_at_gps_pde_posi_info_ind_stru;
    XPDS_AT_GPS_NI_SESSION_IND_STRU xpds_at_gps_ni_session_ind_stru;
    XPDS_AT_GPS_CANCEL_IND_STRU xpds_at_gps_cancel_ind_stru;
    XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU xpds_at_gps_acq_assidata_ind_stru;
    XPDS_AT_GPS_DEL_ASSIST_DATA_IND_STRU xpds_at_gps_del_assidata_ind_stru;
    XPDS_AT_GPS_ABORT_IND_STRU xpds_at_gps_abort_ind_stru;
    XPDS_AT_GPS_NI_CP_START_STRU xpds_at_gps_ni_cp_start_stru;
    XPDS_AT_GPS_NI_CP_STOP_STRU xpds_at_gps_ni_cp_stop_stru;
    XPDS_AT_AP_DATA_CALL_REQ_STRU xpds_at_ap_data_call_req_stru;
    AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU at_xpds_ap_data_call_status_ind_stru;
    XPDS_AT_AP_SERVER_BIND_REQ_STRU xpds_at_ap_server_bind_req_stru;
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU at_xpds_ap_server_bind_status_ind_stru;
    XPDS_AT_AP_REVERSE_DATA_IND_STRU xpds_at_ap_reverse_data_ind_stru;
    AT_XPDS_AP_FORWARD_DATA_IND_STRU at_xpds_ap_forward_data_ind_stru;

    /* XPDS XCC */
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU xpds_xcc_orig_agps_call_req_stru;
    XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU xcc_xpds_orig_agps_call_cnf_stru;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU xpds_xcc_end_agps_call_req_stru;
    XCC_XPDS_END_AGPS_CALL_CNF_STRU xcc_xpds_end_agps_call_cnf_stru;
    XCC_XPDS_INCOMING_CALL_IND_STRU xcc_xpds_incoming_call_ind_stru;
    XPDS_XCC_INCOMING_CALL_RSP_STRU xpds_xcc_incoming_call_rsp_stru;
    XCC_XPDS_CALL_CONN_IND_STRU xcc_xpds_call_conn_ind_stru;
    XPDS_XCC_ANSWER_CALL_REQ_STRU xpds_xcc_answer_call_req_stru;
    XCC_XPDS_ANSWER_CALL_CNF_STRU xcc_xpds_answer_call_cnf_stru;
    XCC_XPDS_SERVICE_CONNECT_IND_STRU xcc_xpds_service_connect_ind_stru;

    /* XPDS CAS */
    XPDS_CAS_REF_LOC_REQ_STRU  xpds_cas_ref_loc_req_stru;
    CAS_XPDS_REF_LOC_CNF_STRU cas_xpds_ref_loc_cnf_stru;
    CAS_XPDS_REF_LOC_IND_STRU  cas_xpds_ref_loc_ind_stru;
    XPDS_CAS_TIME_SYNC_REQ_STRU xpds_cas_time_sync_req_stru;
    CAS_XPDS_TIME_SYNC_IND_STRU cas_xpds_time_sync_ind_stru;

    /* XPDS XPDS */
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU taf_xpds_xpds_up_link_ctrl_req_stru;
    TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU taf_xpds_xpds_up_link_ctrl_cnf_stru;
    TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU taf_xpds_xpds_int_mpc_proc_start_req_stru;
    TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU taf_xpds_xpds_int_mpc_proc_rslt_ind_stru;
    TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU taf_xpds_xpds_int_rcv_mpc_start_pos_resp_stru;
    TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU taf_xpds_xpds_cp_link_proc_start_req_stru;
    TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU taf_xpds_xpds_cp_link_proc_rslt_ind_stru;
    TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU taf_xpds_xpds_cp_pde_proc_start_req_stru;
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU taf_xpds_xpds_forward_pde_data_ind_stru;
    TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU taf_xpds_xpds_pde_proc_start_req_stru;
    TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU taf_xpds_xpds_int_rcv_mpc_pos_report_resp_stru;
    TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU taf_xpds_xpds_int_xsms_cancel_ni_track_session_stru;
    TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU taf_xpds_xpds_ppm_complete_msg_stru;
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU taf_xpds_xpds_int_abnormal_abort_agps_session_ind_stru;
    TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU taf_xpds_xpds_pde_proc_rslt_ind_stru;

    /* XREG XREG */
    CNAS_XREG_XREG_REG_REQ_STRU  cnas_xreg_xreg_reg_req_stru;
    CNAS_XREG_XREG_REG_CNF_STRU  cnas_xreg_xreg_reg_cnf_stru;
    CNAS_XREG_XREG_ABORT_FSM_STRU  cnas_xreg_xreg_abort_fsm_stru;
    CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF_STRU  cnas_xreg_xreg_switch_on_rslt_cnf_stru;
    CNAS_XREG_ZONE_LIST_MNTN_STRU  cnas_xreg_zone_list_mntn_stru;
    CNAS_XREG_SIDNID_LIST_MNTN_STRU  cnas_xreg_sidnid_list_mntn_stru;
    CNAS_XREG_MNTN_MSG_STRU  cnas_xreg_mntn_msg_stru;
    CNAS_MNTN_LOG_FSM_INFO_STRU cnas_mntn_log_fsm_info_stru;

    /* XREG XSD */
    XREG_XSD_REG_SUCCESS_IND_STRU   xreg_xsd_reg_success_ind_stru;
    XREG_XSD_START_CNF_STRU         xreg_xsd_start_cnf_stru;
    XREG_XSD_POWER_OFF_CNF_STRU     xreg_xsd_power_off_cnf_stru;

    /* HSD HSD */
    CNAS_HSD_HSD_ABORT_REQ_STRU  cnas_hsd_hsd_abort_req_stru;
    CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU  cnas_hsd_hsd_switch_on_rslt_cnf_stru;
    CNAS_HSD_HSD_BSR_RSLT_CNF_STRU  cnas_hsd_hsd_bsr_rslt_cnf_stru;
    CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU  cnas_hsd_hsd_power_off_rslt_cnf_stru;
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU  cnas_hsd_hsd_system_acquired_req_stru;
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU  cnas_hsd_hsd_system_acquired_rslt_cnf_stru;
    CNAS_XSD_HSD_SYS_ACQ_RSLT_IND_STRU  cnas_xsd_hsd_sys_acq_rslt_ind_stru;
    CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU  cnas_hsd_hsd_power_save_rslt_cnf_stru;
    CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU  cnas_hsd_hsd_inter_sys_rslt_cnf_stru;
    CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU  cnas_hsd_log_scan_freq_list_msg_stru;
    CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU  cnas_hsd_log_hrpd_sys_list_msg_stru;
    CNAS_HSD_LOG_MRU_LIST_MSG_STRU  cnas_hsd_log_mru_list_msg_stru;
    CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU  cnas_hsd_log_ooc_timer_schedule_info_msg_stru;
    CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU  cnas_hsd_log_ooc_ctx_info_msg_stru;
    CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU  cnas_hsd_log_avoid_freq_list_msg_stru;
    CNAS_HSD_LOG_REDIRCT_MSG_STRU  cnas_hsd_log_redirct_msg_stru;
    CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU  cnas_hsd_log_oper_lock_sys_white_list_stru;
    CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU  cnas_hsd_log_ctcc_customize_freq_list_stru;
    CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU  cnas_hsd_log_prl_source_type_msg_stru;
#endif

    REL_TIMER_MSG   rel_timer_msg;

    return 0;
}



