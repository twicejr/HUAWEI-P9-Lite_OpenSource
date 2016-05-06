/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcMsgEncDec.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月25日
  最近修改   :
  功能描述   : 实现CC空口消息编解码
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasCcInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASCC_MSGENCDEC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/******************************************************************************/
/* IE Lookup Table Definition                                           */
/******************************************************************************/

CONST NAS_IE_TBL_STRU c_aNasCcIeTbl[]=                                          /* ┌────────────────┐ */
{                                                                               /* │  MUST in order as  NAS_CC_IEI  │ */
/*                                            */                                /* ┌────────────────┐ */
   {0x00,   0x00,   0,      0,      0x0000  },                                  /* [00] 10.5.4.1 Extensions of codesets */
   {0x90,   0xF8,   0,      0,      0x0000  },                                  /* [01] 10.5.4.2 Locking shift          */
   {0x91,   0xF8,   0,      0,      0x0000  },                                  /* [02] 10.5.4.3 Non-locking shift      */
   {0x24,   0xFF,   1,      1,      0x0000  },                                  /* [03] 10.5.4.4 Auxiliary states       */
   {0x41,   0xFF,   1,      13,     0x07F4  },                                  /* [04] 10.5.4.4a Backup BC             */
   {0x04,   0xFF,   1,      15,     0x3FB3F },                                  /* [05] 10.5.4.5 Bearer capability      */
   {0x15,   0xFF,   2,      2,      0x0000  },                                  /* [06] 10.5.4.5a Call Control Cap.     */
   {0x00,   0xFF,   1,      1,      0x0000  },                                  /* [07] 10.5.4.6 Call state             */
   {0x5E,   0xFF,   1,      41,     0x0000  },                                  /* [08] 10.5.4.7 Called party number    */
   {0x6D,   0xFF,   0,      21,     0x0000  },                                  /* [09] 10.5.4.8 Called party subaddr   */
   {0x5C,   0xFF,   1,      12,     0x0001  },                                  /* [10] 10.5.4.9 Calling party number   */
   {0x5D,   0xFF,   0,      21,     0x0000  },                                  /* [11] 10.5.4.10 Calling party subaddr */
   {0x08,   0xFF,   2,      30,     0x0001  },                                  /* [12] 10.5.4.11 Cause                 */
   {0xA1,   0xFF,   0,      0,      0x0000  },                                  /* [13] 10.5.4.11a CLIR suppression     */
   {0xA2,   0xFF,   0,      0,      0x0000  },                                  /* [14] 10.5.4.11b CLIR invocation      */
   {0x00,   0xF0,   0,      0,      0x0000  },                                  /* [15] 10.5.4.12 Congestion level      */
   {0x4C,   0xFF,   1,      12,     0x0001  },                                  /* [16] 10.5.4.13 Connected number      */
   {0x4D,   0xFF,   0,      21,     0x0000  },                                  /* [17] 10.5.4.14 Connected subaddress  */
   {0x1C,   0xFF,   0,      255,    0x0000  },                                  /* [18] 10.5.4.15 Facility              */ /* CRSS */
   {0x7D,   0xFF,   0,      3,      0x0002  },                                  /* [19] 10.5.4.16 HLC                   */
   {0x2C,   0xFF,   1,      1,      0x0000  },                                  /* [20] 10.5.4.17 Keypad facility       */
   {0x7C,   0xFF,   0,      16,     0x0000  },                                  /* [21] 10.5.4.18 LLC                   */
   {0xA0,   0xFF,   0,      0,      0x0000  },                                  /* [22] 10.5.4.19 More data             */
   {0x00,   0xFF,   1,      1,      0x0000  },                                  /* [23] 10.5.4.20 Notification indicator*/
   {0x1E,   0xFF,   2,      2,      0x0000  },                                  /* [24] 10.5.4.21 Progress indicator    */
   {0x00,   0xFF,   1,      1,      0x0000  },                                  /* [25] 10.5.4.21a Recall type $(CCBS)$ */
   {0x74,   0xFF,   1,      17,     0x0001  },                                  /* [26] 10.5.4.21b Redirecting number   */
   {0x75,   0xFF,   0,      21,     0x0000  },                                  /* [27] 10.5.4.21c Redirecting subaddr  */
   {0xD0,   0xF0,   0,      0,      0x0000  },                                  /* [28] 10.5.4.22 Repeat indicator      */
   {0xA3,   0xFF,   0,      0,      0x0000  },                                  /* [29] 10.5.4.22a Reverse dir.         */
   {0x00,   0xFF,   0,      255,    0x0000  },                                  /* [30] 10.5.4.22b SETUP Container      */
   {0x34,   0xFF,   1,      1,      0x0000  },                                  /* [31] 10.5.4.23 Signal                */
   {0x7F,   0xFF,   0,      1,      0x0000  },                                  /* [32] 10.5.4.24 SS Version Indicator  */ /* CRSS */
   {0x7E,   0xFF,   1,      129,    0x0000  },                                  /* [33] 10.5.4.25 User-user             */
   {0x19,   0xFF,   1,      1,      0x0000  },                                  /* [34] 10.5.4.26 Alerting Patt.$(NIA)$ */
   {0x7B,   0xFF,   1,      1,      0x0000  },                                  /* [35] 10.5.4.27 Allowed act. $(CCBS)$ */
   {0x2D,   0xFF,   1,      1,      0x0000  },                                  /* [36] 10.5.4.28 Stream Identifier     */
   {0x2F,   0xFF,   1,      1,      0x0000  },                                  /* [37] 10.5.4.29 Network CC Cap.       */
   {0x3A,   0xFF,   1,      1,      0x0000  },                                  /* [38] 10.5.4.30 Cause of No CLI       */
   {0x00,   0x00,   0,      0,      0x0000  },                                  /* [39] 10.5.4.31 Void                  */
   {0x40,   0xFF,   3,      255,    0x0000  },                                  /* [40] 10.5.4.32 Supported codec list  */
   {0x2E,   0xFF,   1,      1,      0x0000  },                                  /* [41] 10.5.4.33 Service category      */
   {0xA3,   0xFF,   0,      0,      0x0000  },                                  /* [42] 10.5.4.34 Redial                */
   {0xA4,   0xFF,   0,      0,      0x0000  },                                  /* [43] 10.5.4.35 NISU indicator        */

   {0x80,   0xF0,   0,      0,      0x0000 },                                   /* [44] 10.5.1.11 Priority Level        */
   {0x1D,   0xFF,   0,      255,    0x0000 },                                   /* [45] 10.5.4.15 Facility $CCBS$       */ /* CRSS */
   {0x1B,   0xFF,   0,      255,    0x0000 },                                   /* [46] 10.5.4.15 Facility $CCBS$       */ /* CRSS */
};

/*lint -e413 修改人：胡文 44270；检视人：梁金广 65478；原因简述：空指针指示*/
/******************************************************************************/
/* Messages Lookup Table Definition                                           */
/******************************************************************************/
CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblAlertingMT[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_ALERTING_MT_STRU,stFacility),          &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_ALERTING_MT_STRU,stProgInd),           &c_aNasCcIeTbl[NAS_CC_IEI_PROG_IND]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_ALERTING_MT_STRU,stUserUser),          &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblAlertingMO[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_ALERTING_MO_STRU,stFacility),          &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_ALERTING_MO_STRU,stUserUser),          &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_ALERTING_MO_STRU,stSSversion),         &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblCallCnf[]=
{
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_C,  2,  IE_OFFSET(NAS_CC_MSG_CALL_CNF_STRU,stRepeatInd),            &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_CALL_CNF_STRU,stBC1),                  &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_CALL_CNF_STRU,stBC2),                  &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_CALL_CNF_STRU,stCause),                &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_CALL_CNF_STRU,stCCCap),                &c_aNasCcIeTbl[NAS_CC_IEI_CC_CAP]            },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  5,  IE_OFFSET(NAS_CC_MSG_CALL_CNF_STRU,stStreamID),             &c_aNasCcIeTbl[NAS_CC_IEI_STREAM_ID]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  6,  IE_OFFSET(NAS_CC_MSG_CALL_CNF_STRU,stCodecList),            &c_aNasCcIeTbl[NAS_CC_IEI_CODEC_LIST]        }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblCallProc[]=
{
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_C,  2,  IE_OFFSET(NAS_CC_MSG_CALL_PROC_STRU,stRepeatInd),           &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_CALL_PROC_STRU,stBC1),                 &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_CALL_PROC_STRU,stBC2),                 &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_CALL_PROC_STRU,stFacility),            &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_CALL_PROC_STRU,stProgInd),             &c_aNasCcIeTbl[NAS_CC_IEI_PROG_IND]          },
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_O,  5,  IE_OFFSET(NAS_CC_MSG_CALL_PROC_STRU,stPrioGranted),         &c_aNasCcIeTbl[NAS_CC_IEI_PRIO_LEVEL]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  6,  IE_OFFSET(NAS_CC_MSG_CALL_PROC_STRU,stNwCCCap),             &c_aNasCcIeTbl[NAS_CC_IEI_NW_CC_CAP]         }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblCongCtrl[]=
{
   {NAS_IE_FORMAT_V,   NAS_IE_PRESENCE_M,   0,  IE_OFFSET(NAS_CC_MSG_CONG_CTRL_STRU,stCongLevel),           &c_aNasCcIeTbl[NAS_CC_IEI_CONG_LEVEL]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_CONG_CTRL_STRU,stCause),               &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblConnectMT[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_CONNECT_MT_STRU,stFacility),           &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_CONNECT_MT_STRU,stProgInd),            &c_aNasCcIeTbl[NAS_CC_IEI_PROG_IND]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_CONNECT_MT_STRU,stConnectedNum),       &c_aNasCcIeTbl[NAS_CC_IEI_CONN_NUM]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_CONNECT_MT_STRU,stConnectedSubaddr),   &c_aNasCcIeTbl[NAS_CC_IEI_CONN_SUBADDR]      },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_CONNECT_MT_STRU,stUserUser),           &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblConnectMO[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_CONNECT_MO_STRU,stFacility),           &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_CONNECT_MO_STRU,stConnectedSubaddr),   &c_aNasCcIeTbl[NAS_CC_IEI_CONN_SUBADDR]      },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_CONNECT_MO_STRU,stUserUser),           &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_CONNECT_MO_STRU,stSSVersion),          &c_aNasCcIeTbl[NAS_CC_IEI_SS_VER]            },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_CONNECT_MO_STRU,stStreamID),           &c_aNasCcIeTbl[NAS_CC_IEI_STREAM_ID]         }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblConnectAck[]=
{
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_O,  0,  0, NULL}
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblDisconnectMT[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MT_STRU,stCause),           &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]            },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MT_STRU,stFacility),        &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MT_STRU,stProgInd),         &c_aNasCcIeTbl[NAS_CC_IEI_PROG_IND]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MT_STRU,stUserUser),        &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MT_STRU,stAllowedAct),      &c_aNasCcIeTbl[NAS_CC_IEI_ALLOWED_ACTIONS]  }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblDisconnectMO[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MO_STRU,stCause),           &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MO_STRU,stFacility),        &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MO_STRU,stUserUser),        &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_DISCONNECT_MO_STRU,stSSVersion),       &c_aNasCcIeTbl[NAS_CC_IEI_SS_VER]            }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblEmergencySetup[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_EMERGENCY_STEUP_STRU,stBC),            &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_EMERGENCY_STEUP_STRU,stStreamID),      &c_aNasCcIeTbl[NAS_CC_IEI_STREAM_ID]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_EMERGENCY_STEUP_STRU,stCodecList),     &c_aNasCcIeTbl[NAS_CC_IEI_CODEC_LIST]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_EMERGENCY_STEUP_STRU,stEmergencyCAT),  &c_aNasCcIeTbl[NAS_CC_IEI_SERVICE_CAT]       }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblFacilityMT[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_FACILITY_MT_STRU,stFacility),          &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblFacilityMO[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_FACILITY_MO_STRU,stFacility),          &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_FACILITY_MO_STRU,stSSVersion),         &c_aNasCcIeTbl[NAS_CC_IEI_SS_VER]            }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblHold[]=
{
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_O,  0,  0, NULL}
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblHoldAck[]=
{
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_O,  0,  0, NULL}
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblHoldRej[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_HOLD_REJ_STRU,stCause),                &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblModify[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_MODIFY_STRU,stBC),                     &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_MODIFY_STRU,stLLC),                    &c_aNasCcIeTbl[NAS_CC_IEI_LLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_MODIFY_STRU,stHLC),                    &c_aNasCcIeTbl[NAS_CC_IEI_HLC]               },
   {NAS_IE_FORMAT_T,    NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_MODIFY_STRU,stReverseDir),             &c_aNasCcIeTbl[NAS_CC_IEI_RESVERSE_DIR]      },
   {NAS_IE_FORMAT_T,    NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_MODIFY_STRU,stNwInitServUpgrade),      &c_aNasCcIeTbl[NAS_CC_IEI_NISU_IND]          }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblModifyComplete[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_MODIFY_COMPLETE_STRU,stBC),            &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_MODIFY_COMPLETE_STRU,stLLC),           &c_aNasCcIeTbl[NAS_CC_IEI_LLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_MODIFY_COMPLETE_STRU,stHLC),           &c_aNasCcIeTbl[NAS_CC_IEI_HLC]               },
   {NAS_IE_FORMAT_T,    NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_MODIFY_COMPLETE_STRU,stReverseDir),    &c_aNasCcIeTbl[NAS_CC_IEI_RESVERSE_DIR]      }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblModifyRej[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_MODIFY_REJ_STRU,stBC),                 &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  1,  IE_OFFSET(NAS_CC_MSG_MODIFY_REJ_STRU,stCause),              &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_MODIFY_REJ_STRU,stLLC),                &c_aNasCcIeTbl[NAS_CC_IEI_LLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_MODIFY_REJ_STRU,stHLC),                &c_aNasCcIeTbl[NAS_CC_IEI_HLC]               }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblNotify[]=
{
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_NOTIFY_STRU,stNotifyInd),              &c_aNasCcIeTbl[NAS_CC_IEI_NOTIFY_IND]        }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblProgress[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_PROGRESS_STRU,stProgInd),              &c_aNasCcIeTbl[NAS_CC_IEI_PROG_IND]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_PROGRESS_STRU,stUserUser),             &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblCCEst[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_CC_EST_STRU,stSetupContainer),         &c_aNasCcIeTbl[NAS_CC_IEI_SETUP_CONTAINER]   }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblCCEstCnf[]=
{
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_C,  0,  IE_OFFSET(NAS_CC_MSG_CC_EST_CNF_STRU,stRepeatInd),          &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_M,  1,  IE_OFFSET(NAS_CC_MSG_CC_EST_CNF_STRU,stBC1),                &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_CC_EST_CNF_STRU,stBC2),                &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_CC_EST_CNF_STRU,stCause),              &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_CC_EST_CNF_STRU,stCodecList),          &c_aNasCcIeTbl[NAS_CC_IEI_CODEC_LIST]        }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblReleaseMT[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_RELEASE_MT_STRU,stCause),              &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_RELEASE_MT_STRU,stCause2),             &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_RELEASE_MT_STRU,stFacility),           &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_RELEASE_MT_STRU,stUserUser),           &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblReleaseMO[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_RELEASE_MO_STRU,stCause),              &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_RELEASE_MO_STRU,stCause2),             &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_RELEASE_MO_STRU,stFacility),           &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_RELEASE_MO_STRU,stUserUser),           &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_RELEASE_MO_STRU,stSSVersion),          &c_aNasCcIeTbl[NAS_CC_IEI_SS_VER]            }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblRecall[]=
{
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_RECALL_STRU,stRecallType),             &c_aNasCcIeTbl[NAS_CC_IEI_RECALL_TYPE]       },
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  1,  IE_OFFSET(NAS_CC_MSG_RECALL_STRU,stFacility),               &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblReleaseCompleteMT[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU,stCause),     &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU,stFacility),  &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU,stUserUser),  &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblReleaseCompleteMO[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU,stCause),     &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU,stFacility),  &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU,stUserUser),  &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU,stSSVersion), &c_aNasCcIeTbl[NAS_CC_IEI_SS_VER]            }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblRetrieve[]=
{
    {NAS_IE_FORMAT_V,   NAS_IE_PRESENCE_O,  0,  0, NULL}
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblRetrieveAck[]=
{
    {NAS_IE_FORMAT_V,   NAS_IE_PRESENCE_O,  0,  0, NULL}
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblRetrieveRej[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_RETRIEVE_REJ_STRU,stCause),            &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblSetupMT[]=
{
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_C,  0,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stBCRepeatInd),          &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  1,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stBC1),                  &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stBC2),                  &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stFacility),             &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stProgInd),              &c_aNasCcIeTbl[NAS_CC_IEI_PROG_IND]          },
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_O,  5,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stSignal),               &c_aNasCcIeTbl[NAS_CC_IEI_SIGNAL]            },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  6,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stCallingNum),           &c_aNasCcIeTbl[NAS_CC_IEI_CALLING_NUM]       },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  7,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stCallingSubaddr),       &c_aNasCcIeTbl[NAS_CC_IEI_CALLING_SUBADDR]   },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  8,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stCalledNum),            &c_aNasCcIeTbl[NAS_CC_IEI_CALLED_NUM]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  9,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stCalledSubaddr),        &c_aNasCcIeTbl[NAS_CC_IEI_CALLED_SUBADDR]    },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 10,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stRedirectingNum),       &c_aNasCcIeTbl[NAS_CC_IEI_REDIRECT_NUM]      },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 11,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stRedirectingSubaddr),   &c_aNasCcIeTbl[NAS_CC_IEI_REDIRECT_SUBADDR]  },
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_O, 12,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stLLCRepeatInd),         &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 13,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stLLC1),                 &c_aNasCcIeTbl[NAS_CC_IEI_LLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_C, 12,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stLLC2),                 &c_aNasCcIeTbl[NAS_CC_IEI_LLC]               },
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_O, 15,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stHLCRepeatInd),         &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 16,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stHLC1),                 &c_aNasCcIeTbl[NAS_CC_IEI_HLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_C, 15,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stHLC2),                 &c_aNasCcIeTbl[NAS_CC_IEI_HLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 18,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stUserUser),             &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         },
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_O, 19,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stPriority),             &c_aNasCcIeTbl[NAS_CC_IEI_PRIO_LEVEL]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 20,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stAlert),                &c_aNasCcIeTbl[NAS_CC_IEI_ALERTING_PATTERN]  },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 21,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stNwCCCap),              &c_aNasCcIeTbl[NAS_CC_IEI_NW_CC_CAP]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 22,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stNoCLICause),           &c_aNasCcIeTbl[NAS_CC_IEI_NO_CLI_CAUSE]      },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 23,  IE_OFFSET(NAS_CC_MSG_SETUP_MT_STRU,stBackupBC),             &c_aNasCcIeTbl[NAS_CC_IEI_BAK_BC]            }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblSetupMO[]=
{
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_C,  2,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stBCRepeatInd),          &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_M,  1,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stBC1),                  &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stBC2),                  &c_aNasCcIeTbl[NAS_CC_IEI_BC]                },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  3,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stFacility),             &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY]          },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  4,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stCallingSubaddr),       &c_aNasCcIeTbl[NAS_CC_IEI_CALLING_SUBADDR]   },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_M,  5,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stCalledNum),            &c_aNasCcIeTbl[NAS_CC_IEI_CALLED_NUM]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  6,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stCalledSubaddr),        &c_aNasCcIeTbl[NAS_CC_IEI_CALLED_SUBADDR]    },
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_O,  7,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stLLCRepeatInd),         &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  8,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stLLC1),                 &c_aNasCcIeTbl[NAS_CC_IEI_LLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  9,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stLLC2),                 &c_aNasCcIeTbl[NAS_CC_IEI_LLC]               },
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_O, 10,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stHLCRepeatInd),         &c_aNasCcIeTbl[NAS_CC_IEI_REPEAT_IND]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 11,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stHLC1),                 &c_aNasCcIeTbl[NAS_CC_IEI_HLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 12,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stHLC2),                 &c_aNasCcIeTbl[NAS_CC_IEI_HLC]               },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 13,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stUserUser),             &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 14,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stSSVersion),            &c_aNasCcIeTbl[NAS_CC_IEI_SS_VER]            },
   {NAS_IE_FORMAT_T,    NAS_IE_PRESENCE_C, 16,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stCLIR_S),               &c_aNasCcIeTbl[NAS_CC_IEI_CLIR_S]            },
   {NAS_IE_FORMAT_T,    NAS_IE_PRESENCE_C, 15,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stCLIR_I),               &c_aNasCcIeTbl[NAS_CC_IEI_CLIR_I]            },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 17,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stCCCap),                &c_aNasCcIeTbl[NAS_CC_IEI_CC_CAP]            },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 18,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stFacility1D),           &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY_1D]       },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 19,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stFacility1B),           &c_aNasCcIeTbl[NAS_CC_IEI_FACILITY_1B]       },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 20,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stStreamID),             &c_aNasCcIeTbl[NAS_CC_IEI_STREAM_ID]         },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O, 21,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stCodecList),            &c_aNasCcIeTbl[NAS_CC_IEI_CODEC_LIST]        },
   {NAS_IE_FORMAT_T,    NAS_IE_PRESENCE_O, 22,  IE_OFFSET(NAS_CC_MSG_SETUP_MO_STRU,stRedial),               &c_aNasCcIeTbl[NAS_CC_IEI_REDIAL]            }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblStartCC[]=
{
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_START_CC_STRU,stCCCap),                &c_aNasCcIeTbl[NAS_CC_IEI_CC_CAP] }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblStartDTMF[]=
{
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_START_DTMF_STRU,stKeypadFacility),     &c_aNasCcIeTbl[NAS_CC_IEI_KEYPAD_FACILITY]   }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblStartDTMFAck[]=
{
   {NAS_IE_FORMAT_TV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_START_DTMF_ACK_STRU,stKeypadFacility), &c_aNasCcIeTbl[NAS_CC_IEI_KEYPAD_FACILITY]   }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblStartDTMFRej[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_START_DTMF_REJ_STRU,stCause),          &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblStatus[]=
{
   {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_STATUS_STRU,stCause),                  &c_aNasCcIeTbl[NAS_CC_IEI_CAUSE]             },
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_M,  1,  IE_OFFSET(NAS_CC_MSG_STATUS_STRU,stCallState),              &c_aNasCcIeTbl[NAS_CC_IEI_CALL_STATE]        },
   {NAS_IE_FORMAT_TLV,  NAS_IE_PRESENCE_O,  2,  IE_OFFSET(NAS_CC_MSG_STATUS_STRU,stAuxState),               &c_aNasCcIeTbl[NAS_CC_IEI_AUX_STATES]        }
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblStatusEnquiry[]=
{
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_O,  0,  0, NULL}
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblStopDTMF[]=
{
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_O,  0,  0, NULL}
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblStopDTMFAck[]=
{
   {NAS_IE_FORMAT_V,    NAS_IE_PRESENCE_O,  0,  0, NULL}
};

CONST NAS_MSG_TBL_STRU c_stNasCcMsgTblUserInfo[]=
{
    {NAS_IE_FORMAT_LV,   NAS_IE_PRESENCE_M,  0,  IE_OFFSET(NAS_CC_MSG_USER_INFO_STRU,stUserUser),            &c_aNasCcIeTbl[NAS_CC_IEI_USER_USER]         },
    {NAS_IE_FORMAT_T,    NAS_IE_PRESENCE_O,  0,  IE_OFFSET(NAS_CC_MSG_USER_INFO_STRU,stMoredata),            &c_aNasCcIeTbl[NAS_CC_IEI_MORE_DATA]         }
};
/*lint +e413 修改人：胡文 44270；检视人：liangjinguang*/

/******************************************************************************/
/* Entry of CC Messages                                                       */
/******************************************************************************/

CONST NAS_MSG_ENTRY_STRU c_aNasCcMsgEntry[] =
{
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 3, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblAlertingMO,          3,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblAlertingMT           },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       7,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblCallProc             },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       2,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblProgress             },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       1,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblCCEst                },
   {23, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblSetupMO,             24, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblSetupMT              },
   { 5, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblCCEstCnf,            0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 5, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblConnectMO,           5,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblConnectMT            },
   { 7, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblCallCnf,             0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 1, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStartCC,             0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       2,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblRecall               },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 4, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblEmergencySetup,      0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblConnectAck,          0,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblConnectAck           },
   { 1, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblUserInfo,            1,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblUserInfo             },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 4, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblModifyRej,           4,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblModifyRej            },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       5,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblModify               },
   { 0, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblHold,                0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblHoldAck              },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblHoldRej              },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblRetrieve,            0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblRetrieveAck          },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblRetrieveRej          },
   { 4, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblModifyComplete,      4,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblModifyComplete       },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 4, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblDisconnectMO,        5,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblDisconnectMT         },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 4, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblReleaseCompleteMO,   3,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblReleaseCompleteMT    },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 5, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblReleaseMO,           4,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblReleaseMT            },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStopDTMF,            0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStopDTMFAck          },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStatusEnquiry,       0,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStatusEnquiry        },
   { 1, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStartDTMF,           0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       1,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStartDTMFAck         },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       1,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStartDTMFRej         },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       2,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblCongCtrl             },
   { 2, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblFacilityMO,          1,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblFacilityMT           },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 3, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStatus,              3,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblStatus               },
   { 1, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblNotify,              1,  (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblNotify               },

   /* 预留8个空位用于协议升级后可能有的新消息类型 */
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        },

   /* 自定义的消息类型从此处开始 */
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       23, (NAS_MSG_TBL_STRU *)c_stNasCcMsgTblSetupMO              },
   { 0, (NAS_MSG_TBL_STRU *)VOS_NULL_PTR,                       0,  (NAS_MSG_TBL_STRU *)VOS_NULL_PTR                        }
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_CC_EncodeMsg
 功能描述  : Encode Nas Msg
 输入参数  : pucMsg          - 消息编码前源地址
 输出参数  : pucRawData      - 消息编码后目的地址
             pucLength       - 消息长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_EncodeMsg(
    const NAS_CC_AIR_MSG_UNION          *punMsg,
    VOS_UINT8                           *pucRawData,
    VOS_UINT8                           *pucLength
)
{
    if (NAS_PROT_ERR_NO_ERROR != NasEncodeMsg(c_aNasCcMsgEntry,
                                              (VOS_UINT8 *)punMsg,
                                              pucRawData,
                                              pucLength))
    {
        NAS_CC_ERR_LOG("NAS_CC_EncodeMsg: NasEncodeMsg failure.");
    }
    return;
}


/*****************************************************************************
 函 数 名  : NAS_CC_DecodeMsg
 功能描述  : Decode Nas Msg
 输入参数  : pucRawData         - 消息解码前源地址
             ucLength           - 消息长度
 输出参数  : pucMsg             - 消息解码后目的地址
 返 回 值  : 协议错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年02月25日
    作    者   : z00214637
    修改内容   : 问题单号:DTS2013022107190,CC在解析消息时，表格访问越界保护；
*****************************************************************************/
NAS_PROTOCOL_ERR_ENUM_U8 NAS_CC_DecodeMsg(
    const VOS_UINT8                     *pucRawData,
    VOS_UINT8                           ucLength,
    NAS_CC_AIR_MSG_UNION                *punMsg
)
{
    return NasDecodeMsg(c_aNasCcMsgEntry,
                        sizeof(c_aNasCcMsgEntry)/sizeof(c_aNasCcMsgEntry[0]),
                        pucRawData,
                        ucLength,
                        (VOS_UINT8 *)punMsg);
}


/*****************************************************************************
 函 数 名  : NAS_CC_GetFacilityInfoWithRsltTag
 功能描述  : 解析带result tag的facility IE
 输入参数  : paucFacility    - Facility IE 内容地址
 输出参数  : pstFacilityInfo - Facility Info
             pucLength       - Component偏移地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月2日
    作    者   : z00161729
    修改内容   : 降NAS_CC_GetFacilityInfo圈复杂度新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_GetFacilityInfoWithRsltTag(
    const VOS_UINT8                     *paucFacility,
    NAS_CC_FACILITY_INFO_STRU           *pstFacilityInfo,
    VOS_UINT8                           *pucLength
)
{
    if ((*pucLength > 3) && (NAS_SS_OPERATION_CODE_TAG == paucFacility[5]))
    {
        pstFacilityInfo->bOpCodePresent = VOS_TRUE;
        pstFacilityInfo->enOpCode       = paucFacility[7];

        /*  3Byte ( Invoke ID tag + Invoke ID length +Invoke ID )
           +3Byte ( Operation Code tag + Operation Code length + Operation Code ) */
        if (*pucLength > 6)
        {
            pstFacilityInfo->ucParamOffset = 8;
        }
    }
    else if ((*pucLength > 5) && (NAS_SS_OPERATION_CODE_TAG == paucFacility[7]))
    {
        pstFacilityInfo->bOpCodePresent = VOS_TRUE;
        pstFacilityInfo->enOpCode       = paucFacility[9];

        /*  3Byte ( Invoke ID tag + Invoke ID length +Invoke ID )
           +2Byte ( Sequence tag + Sequence length )
           +3Byte ( Operation Code tag + Operation Code length + Operation Code ) */
        if (*pucLength > 8)
        {
            pstFacilityInfo->ucParamOffset = 10;
        }
    }
    else
    {
        /*  3Byte ( Invoke ID tag + Invoke ID length +Invoke ID ) */
        if (*pucLength > 3)
        {
             pstFacilityInfo->ucParamOffset = 4;
        }
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_CC_GetFacilityInfoWithInvokeTag
 功能描述  : 解析带invoke tag的facility IE
 输入参数  : paucFacility    - Facility IE 内容地址
 输出参数  : pstFacilityInfo - Facility Info
             pucLength       - Component偏移地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月2日
    作    者   : z00161729
    修改内容   : 降NAS_CC_GetFacilityInfo圈复杂度新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_GetFacilityInfoWithInvokeTag(
    const VOS_UINT8                    *paucFacility,
    NAS_CC_FACILITY_INFO_STRU          *pstFacilityInfo,
    VOS_UINT8                          *pucLength
)
{
    pstFacilityInfo->bOpCodePresent = VOS_TRUE;

    if (NAS_SS_COMPONENT_ID_TAG_LINKED == paucFacility[5])
    {
        pstFacilityInfo->enOpCode = paucFacility[10];

         /* 3Byte ( Invoke ID tag + Invoke ID length +Invoke ID )
            +3Byte ( Linked ID tag + Linked ID length + Linked ID )
            +3Byte ( Operation Code tag + Operation Code length + Operation Code ) */
        if (*pucLength > 9)
        {
            pstFacilityInfo->ucParamOffset = 11;
        }
    }
    else
    {
        pstFacilityInfo->enOpCode = paucFacility[7];

        /*  3Byte ( Invoke ID tag + Invoke ID length +Invoke ID )
           +3Byte ( Operation Code tag + Operation Code length + Operation Code ) */
        if (*pucLength > 6)
        {
            pstFacilityInfo->ucParamOffset = 8;
        }
    }

    return;

}
/*****************************************************************************
 函 数 名  : NAS_CC_GetFacilityInfo
 功能描述  : 解谐facility IE
 输入参数  : paucFacility      - Facility IE 内容地址
 输出参数  : pstFacilityInfo   - Facility Info
 返 回 值  : Component偏移地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2009年6月25日
    作    者   : z00161729
    修改内容   : CC降圈复杂度
  3.日    期   : 2013年6月05日
    作    者   : Y00213812
    修改内容   : DTS2013060507591,COVERITY和FORITY修改

*****************************************************************************/
VOS_UINT8 NAS_CC_GetFacilityInfo(
    const VOS_UINT8                    *paucFacility,
    NAS_CC_FACILITY_INFO_STRU          *pstFacilityInfo
)
{
    VOS_UINT8                           ucLength;

    /*上层传下来的是V结构*/
    ucLength                        = paucFacility[1];    /* Component Length */
    pstFacilityInfo->ucCompType     = *paucFacility;
    pstFacilityInfo->ucInvokeID     = *(paucFacility+4);
    pstFacilityInfo->ucParamOffset  = 0;
    pstFacilityInfo->bOpCodePresent = VOS_FALSE;

    switch ( pstFacilityInfo->ucCompType )
    {
        case NAS_SS_COMPONENT_TYPE_TAG_INVOKE:
            NAS_CC_GetFacilityInfoWithInvokeTag(paucFacility, pstFacilityInfo, &ucLength);
            break;

        case NAS_SS_COMPONENT_TYPE_TAG_RTN_RSLT:
            NAS_CC_GetFacilityInfoWithRsltTag(paucFacility, pstFacilityInfo, &ucLength);
            break;

        case NAS_SS_COMPONENT_TYPE_TAG_RTN_ERR:
        case NAS_SS_COMPONENT_TYPE_TAG_REJECT:
            break;

        default:
            NAS_CC_ERR_LOG("NAS_CC_GetFacilityInfo: Facility Component Type Tag Error.");
            break;

    }
    ucLength += 2;
    return ucLength;
}


/*****************************************************************************
 函 数 名  : NAS_CC_FillAirMsgHeader
 功能描述  : 填写CC的空口消息头
 输入参数  : ucTi      - Transcation ID
             ucMsgType - 消息类型
 输出参数  : pstHeader - 填写完成的消息头
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_CC_FillAirMsgHeader(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucMsgType,
    NAS_AIR_MSG_HDR_STRU                *pstHeader
)
{
    pstHeader->bit4PD = NAS_PD_CC;
    pstHeader->bit4TI = ucTi;
    pstHeader->ucMsgType = ucMsgType;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

