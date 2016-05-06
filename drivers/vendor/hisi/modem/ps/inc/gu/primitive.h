/******************************************************************************
  File name:           Primitive.h
  Description:         WCDMA UE SD6510 软件原语ID定义

  History:
  1. Created by LiYajuan 2005-01-26
 -------------------------------------------------------------------------------------------

  2.日    期   : 2005年4月12日
    作    者   : zuowen
    修改内容   : 修改问题单 A32D00067
*******************************************************************************/

/******************************************************************************
* Don't allow this file to be included more than once.
*******************************************************************************/

#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_


/******************************************************************************
                Destination Module Define

                #define    PBC       0x10
                #define    AMR       0x11
                #define    CIPHER    0x12
                #define    BBP       0x13
                #define    USIM      0x14

                #define    HPA       0x20
                #define    AGENT     0x21
                #define    SLEEP     0x22
                #define    WD        0x23

                #define    MAC       0x30
                #define    RLC       0x31
                #define    RRCF      0x32
                #define    RCSF      0x33
                #define    RSRF      0x34
                #define    RMF       0x35

                #define    MM        0x40
                #define    GMM       0x41
                #define    SM        0x42

                #define    NOT_CLEAR 0x00

The MSG ID define as following:
                 --------------
                |  D   |  N    |
                 --------------
                 D:Destination Module
                 N:the MSG number
For exsample:
#define    CPHY_RL_SETUP_REQ        0x1001
the Destination Module is PBC, the number is 01,so the MSGID is 0x1001.
*******************************************************************************/

/****************************************************************
The following msg's Destination is PBC
*****************************************************************/
/* RRCF->PBC */
#define    CPHY_RL_SETUP_REQ                     0x1001
#define    CPHY_RL_MODIFY_REQ                    0x1002
#define    CPHY_RL_RELEASE_REQ                   0x1003
#define    CPHY_POWER_CONTROL_REQ                0x1004
#define    CPHY_TRCH_CONFIG_REQ                  0x1005
#define    CPHY_TRCH_RELEASE_REQ                 0x1006
#define    CPHY_DL_SYNC_REQ                      0x1007
#define    CPHY_UPLINK_MAXTXPWR_REQ              0x1008
#define    CPHY_RELALL_PHYCH_REQ                 0x1009
#define    CPHY_CAMPED_MAINCELL_REQ              0x100A
#define    CPHY_RESET_REQ                        0x100B
#define    RRC_INTEGRITY_REQ                     0x100C

/* RSRF->PBC */
#define    CPHY_PCCPCH_SETUP_REQ                 0x100D
#define    CPHY_PCCPCH_RELEASE_REQ               0x100E

/* RCSF->PBC */
#define    CPHY_CELL_SEARCHING_REQ               0x100F
#define    CPHY_MEASUREMENT_IN_IDLE_REQ          0x1010
#define    CPHY_QUALITY_MEASUREMENT_REQ          0x1011

/* RCSF/RMF->PBC */
#define    CPHY_MEASUREMENT_IN_CONNECTED_REQ     0x1012

#define    CPHY_BSIC_VERIFIED_REQ                0x1020

/* RMF->PBC */
#define    CPHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ  0x1013

/* MAC->PBC */
#define    PHY_ACCESS_REQ                        0x1014

/* HPA->PBC */
#define    PHY_INFO_CONFIG_REQ                   0x1015
/* SLEEP->PBC */
#define    PBC_SLEEP_REQ                         0x1019

/****************************************************************
The following msg's Destination is AMR
*****************************************************************/
/* MAC->AMR */
#define    PHY_AMR_DATA_IND                      0x1101

/* HPA->AMR */
#define    HPA_AMR_LOOP_TEST_REQ                 0x1102

/* SPEECH->AMR */
#define    PHY_AMR_CONNECTING_SETUP_REQ          0x1103
#define    PHY_AMR_CONNECTING_RELEASE_REQ        0x1104
#define    PHY_AMR_ENCODE_MODE_REQ               0x1105
#define    PHY_SIGNAL_TONE_SETUP_REQ             0x1106
#define    PHY_SIGNAL_TONE_RELEASE_REQ           0x1107

/****************************************************************
The following msg's Destination is AUDIO
*****************************************************************/
#define  CPHY_VOMATE_SOUND_REQ  0X1759				


/****************************************************************
The following msg's Destination is CIPHER
*****************************************************************/
/* RLC->CIPHER */
#define    RLC_AM_CIPHER_REQ                     0x1201
#define    RLC_UM_CIPHER_REQ                     0x1202

/* MAC->CIPHER */
#define    MAC_CIPHER_REQ                        0x1203

/* HPA->CIPHER */
#define    CIPHER_AMDATA_REQ                     0x1204
#define    CIPHER_UMDATA_REQ                     0x1205
#define    CIPHER_TMDATA_REQ                     0x1206

/****************************************************************
The following msg's Destination is BBP
*****************************************************************/
/* MAC->BBP */
#define    PHY_DATA_REQ                          0x1301

/****************************************************************
The following msg's Destination is USIM
*****************************************************************/
/* AGENT->USIM */
#define    AGENT_USIM_SET_MOBILEID               0x1401
#define    AGENT_USIM_SET_DEFAULT_DATA           0x1402


/****************************************************************
The following msg's Destination is HPA
*****************************************************************/
/* PBC->HPA */
#define    HPA_PBC_LOOP_TEST_IND                 0x2002

/* AMR->HPA */
#define    HPA_AMR_LOOP_TEST_IND                 0x2003

/* CIPHER->HPA */
#define    CIPHER_AMDATA_CNF                     0x2004
#define    CIPHER_UMDATA_CNF                     0x2005
#define    CIPHER_TMDATA_CNF                     0x2006

/* OM->HPA */
#define    PHY_BG_DSP_DATA_READ_REQ              0x2007
#define    PHY_BG_DSP_DATA_WRITE_REQ             0x2008

/*OM->RCSF*/
#define  OM_RCSF_CELLINFO_REP_CFG_REQ            0x3301
#define  RCSF_OM_SERVINGCELL_REP_IND		     0x21b1
#define  RCSF_OM_ACTIVECELL_REP_IND		         0x21b2
/* PBC->HPA */
#define    AMR_LOADING_IND                       0x2009
#define    PHY_INFO_CONFIG_CNF                   0x2010
/****************************************************************
The following msg's Destination is AGNET
*****************************************************************/
/* RRCF->AGENT */
#define    CBG_REPORT_IND                        0x2101
#define    CBG_RRC_ACT_IND                       0x2102
#define    CBG_RRC_CELLRESEL_IND                 0x2103

/* RLC->AGENT */
#define    RLC_BG_LINK_RATE_IND                  0x2104

/* MAC->AGENT */
#define    MAC_BG_DATA_RATE_DISPLAY_IND          0x2105
#define    CMD_MAC_START_FTP_CNF                 0x2106

/* MM->AGENT */
#define    MM_AGENT_INFO                         0x2107
#define    MM_AGENT_PROCEDURE_IND                0x2108

/* GMM->AGENT */
#define    PMM_AGENT_INFO                        0x2109
#define    PMM_AGENT_PROCEDURE_IND               0x210A

/* SM->AGENT */
#define    SM_AGENT_INFO                         0x210B
#define    SM_AGENT_STATUS_IND                   0x210C
#define    SM_AGENT_PDPNUM_IND                   0X210D

/* HPA->AGENT */
#define    PHY_BG_DSP_DATA_READ_IND              0x210E

#define    CPHY_REPORT_OM_IND                    0x21c1

/****************************************************************
The following msg's Destination is SLEEP
*****************************************************************/
/* PBC->SLEEP */
#define    PBC_SLEEP_IND                         0x2201
#define    PBC_SLEEP_CNF                         0x2202

/****************************************************************
The following msg's Destination is WD
*****************************************************************/


/****************************************************************
The following msg's Destination is MAC
*****************************************************************/
/* BBP->MAC */
#define    PHY_DATA_IND                          0x3001

/* PBC->MAC */
#define    PHY_ACCESS_CNF                        0x3002
#define    PHY_STATUS_IND                        0x3003

/* AGENT->MAC */
#define    MAC_SET_DATA_RATE_DISPLAY             0x3004
#define    CMD_MAC_START_FTP_REQ                 0x3005
#define    CMD_MAC_STOP_FTP_REQ                  0x3006
#define    CMD_MAC_REG_RPT_REQ                   0x3010

/* HPA->MAC */
#define    MAC_TIMER_MSG                         0x3007

/* PBC->MAC */
#define    PHY_TFC_STATUS_IND                    0x3008


/****************************************************************
The following msg's Destination is RLC
*****************************************************************/
/* AMR->RLC */
#define    PHY_AMR_DATA_REQ                      0x3101

/* AGENT->RLC */
#define    BG_RLC_SET_DATA_RATE_DISPLAY          0x3102
#define    MAC_BG_AMR_REQ                        0x3103

/****************************************************************
The following msg's Destination is RRCF
*****************************************************************/
/* PBC->RRCF */
#define    CPHY_RL_SETUP_CNF                     0x3201
#define    CPHY_RL_MODIFY_CNF                    0x3202
#define    CPHY_RL_RELEASE_CNF                   0x3203
#define    CPHY_ACTIVATE_IND                     0x3204
#define    CPHY_POWER_CONTROL_CNF                0x3205
#define    CPHY_TRCH_CONFIG_CNF                  0x3206
#define    CPHY_TRCH_RELEASE_CNF                 0x3207
#define    CPHY_ERROR_IND                        0x3208
#define    CPHY_SYNC_IND                         0x3209
#define    CPHY_OUT_OF_SYNC_IND                  0x320A
#define    CPHY_DL_SYNC_CNF                      0x320B
#define    CPHY_RELALL_PHYCH_CNF                 0x320C
#define    CPHY_DPCH_COMPRESSED_MODE_STATUS_IND  0x320D
#define    CPHY_CAMPED_MAINCELL_CNF              0x320E

/* AGENT->RRCF */
#define    CBG_REPORT_CONFIG_REQ                 0x320F

/****************************************************************
The following msg's Destination is RCSF
*****************************************************************/
/* PBC->RCSF */
#define    CPHY_CELL_SEARCH_IND                  0x3301
#define    CPHY_MEASUREMENT_IN_IDLE_CNF          0x3302
#define    CPHY_MEASUREMENT_IN_IDLE_IND          0x3303


/****************************************************************
The following msg's Destination is RSRF
*****************************************************************/
/* PBC->RSRF */
#define    CPHY_PCCPCH_SETUP_CNF                 0x3401
#define    CPHY_PCCPCH_RELEASE_CNF               0x3402
#define    CPHY_BCCHDATA_IND                     0x3403

/****************************************************************
The following msg's Destination is RMF
*****************************************************************/
/* PBC->RMF */
#define    CPHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF  0x3501
#define    CPHY_QUALITY_MEASUREMENT_CNF                 0x3502
#define    CPHY_QUALITY_MEASUREMENT_IND                 0x3503

/****************************************************************
The following msg's Destination is MM
*****************************************************************/
/* AGENT->MM */
#define    AGENT_MM_INQUIRE                      0x4001
#define    MM_TRANS_STATUS_INFO_REQ              0x5400
#define    MM_TRANS_STATUS_INFO_RSP              0x5401

/****************************************************************
The following msg's Destination is GMM
*****************************************************************/
/* AGENT->GMM */
#define    AGENT_PMM_INQUIRE                     0x4101

/****************************************************************
The following msg's Destination is SM
*****************************************************************/
/* AGENT->SM */
#define    AGENT_SM_INQUIRE                      0x4201
#define    AGENT_SM_PDPNUM_INQUIRE               0x4202

/****************************************************************
The following msg's Destination is CC
*****************************************************************/

/****************************************************************
The following msg's Destination is SS
*****************************************************************/

/****************************************************************
The following msg's Destination is SMS
*****************************************************************/

/****************************************************************
The Destination is not clear
*****************************************************************/
/* PBC->RCSF/RMF */
#define    CPHY_MEASUREMENT_IN_CONNECTED_CNF     0x0001
#define    CPHY_MEASUREMENT_IN_CONNECTED_IND     0x0002

#define    CPHY_BSIC_VERIFIED_CNF                0x0003
#define    CPHY_BSIC_VERIFIED_IND                0x0004
#endif
