/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MMGLOBAL.c
  Description :
  History     :
      1.  张志勇   2003.11.27   新版作成
      2.  s46746 2006-03-39  根据问题单A32D02486修改
      3.  x51137  2006/4/14 A32D02955
      4.  s46746 2006-04-17  根据问题单A32D02829修改
      5.  x51137 2006/5/5 A32D03487
      6.  x51137 2006/11/3 A32D06511
      7.  x51137 2006/11/3 A32D06821
      8.  d49431 2006/11/23 A32D07452
      9. 日    期   : 2006年11月23日
         作    者   : luojian   id:60022475
         修改内容   : 问题单号：A32D07583
      10.日    期   : 2007年01月04日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单号：A32D06408
      11.日    期   : 2007年1月26日
         作    者   : liurui id:40632
         修改内容   : 根据问题单号：A32D08577
      12.日    期   : 2007年03月09日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单A32D09099修改
      13.日    期   : 2007年3月20日
         作    者   : s46746
         修改内容   : 问题单号：A32D09497
      14.日    期   : 2007年05月11日
         作    者   : luojian id:60022475
         修改内容   : 问题单号:A32D10713
      15.日    期   : 2007年06月01日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单A32D10964修改
      16.日    期   : 2007年06月30日
         作    者   : s46746
         修改内容   : 问题单号:A32D12011,MM在no cell available状态下，接入层可能限制驻留，容许重选
      17.日    期   : 2007年08月03日
         作    者   : l65478
         修改内容   : 问题单号:A32D12650
      18.日    期   : 2007年08月19日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单号：A32D12706
      19.日    期   : 2007年9月29日
         作    者   : luojian id:107747
         修改内容   : 根据问题单号：A32D12966,增加部分状态对RRMM_REL_IND的处理
      20.日    期   : 2007年11月22日
         作    者   : s46746
         修改内容   : 问题单号:A32D13465,MMC接收到底层出服务区消息后，
                      如果CS和PS正在进行连接建立，不需要缓存对出服务区消息的处理
      21.日    期   : 2007年11月22日
         作    者   : l00107747
         修改内容   : 问题单号:A32D13535
      22.日    期   : 2007年12月11日
         作    者   : s46746
         修改内容   : 根据问题单号：A32D13845,出服务区后，MMC立即启动异系统相同PLMN
                      搜索
      23.日    期   : 2007年12月12日
         作    者   : l00107747
         修改内容   : 根据问题单号：A32D13859,支持对SMS的缓存处理
      24.日    期   : 2007年12月29日
         作    者   : l0010747
         修改内容   : 问题单号:A32D13958,部分状态下对RRMM_REL_IND处理修改
      25.日    期   : 2008年5月27日
         作    者   : s46746
         修改内容   : 问题单号:AT2D03209,增加列表搜索时响应寻呼处理
      26.日    期   : 2008年7月21日
         作    者   : luojian 00107747
         修改内容   : 问题单号：AT2D04201/AT2D04536,修改IMSI DETACH流程
      27.日    期   : 2008年8月22日
         作    者   : o00132663
         修改内容   : 问题单号:AT2D05087,增加函数 Mm_Cell_S4_E31
      28.日    期   : 2008年8月26日
         作    者   : o00132663
         修改内容   : 问题单号:AT2D05268,增加在重建过程中对鉴权的处理。
      29.日    期   : 2008年10月15日
         作    者   : x00115505
         修改内容   : 问题单AT2D06189
      30.日    期   : 2008年11月10日
         作    者   : l00130025
         修改内容   : 问题单号：AT2D06577, 修改aMmEvent22
      31.日    期   : 2008年11月26日
         作    者   : x00115505
         修改内容   : 问题单号:AT2D06551，MS在响应网侧Paging过程中不处理
                      USSD业务
      32.日    期   : 2008年12月22日
         作    者   : o00132663
         修改内容   : 问题单号:AT2D07757,MM丢网后重回原小区，不发起LU
      33.日    期   : 2009年01月15日
         作    者   : l00130025
         修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
      34.日    期   : 2009年04月29日
         作    者   : x00115505
         修改内容   : AT2D11365,2G下MM建立信令链接保护定时器的长度过长，从190s修改为15s。
      35.日    期   : 2009年07月13日
         作    者   : z40661
         修改内容   : AT2D12727,Gmm在Suspension状态下，软开机失败
      36.日    期   : 2009年07月24日
         作    者   : z40661
         修改内容   : 异系统重选后，紧急呼叫不能接通
      37.日    期   : 2009年9月7日
         作    者   : s46746
         修改内容   : 根据问题单号：AT2D14311，出服务区后，GMM存在连接时先进行了连接释放，会导致服务状态临时更新为Normal service
      38.日    期   : 2009年10月3日
         作    者   : l00130025
         修改内容   : 根据问题单号：AT2D14889,G网络模式I下,Combined RAU过程中，
                            设置需要CS detach的SYSCFG失败,修改ammevent10
      39.日    期   : 2010年03月19日
         作    者   : s46746
         修改内容   : 根据问题单号：AT2D17453,异系统切换状态，MM接收到底层GAS channal open消息，直接透传到CC模块

*******************************************************************************/
#include        "MM_Inc.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-2, begin */
#include "NasMmEcall.h"
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-2, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/* 定义MMC发给MM的原语实体 */
/*MMCMM_START_REQ_STRU                    g_MmcMmStartReq;*/

/* 定义CC发给MM的原语实体 */
MMCC_EST_REQ_ST                         g_MmCcEstReq;
MMCC_REL_REQ_ST                         g_MmCcRelReq;
MMCC_ABORT_REQ_ST                       g_MmCcAbortReq;
MMCC_REEST_REQ_ST                       g_MmCcReestReq;
MMCC_PROMPT_REJ_ST                      g_MmCcPromptRej;

/* 定义SS发给MM的原语实体 */
MMSS_EST_REQ_ST                         g_MmSsEstReq;
MMSS_REL_REQ_ST                         g_MmSsRelReq;
/*MMSS_DATA_REQ_STRU                      g_MmSsDataReq;*/
MMSS_ABORT_REQ_ST                       g_MmSsAbortReq;

/* 定义SMS发给MM的原语实体 */
MMSMS_EST_REQ_ST                        g_MmSmsEstReq;
MMSMS_REL_REQ_ST                        g_MmSmsRelReq;
/*MMSMS_DATA_REQ_STRU                     g_MmSmsDataReq;*/
MMSMS_ABORT_REQ_ST                      g_MmSmsAbortReq;

/* 定义RRC发给MM的原语实体 */
RRMM_SYNC_IND_ST                        g_RrMmSyncInd;

/* 定义MM收到的消息实体 */
MM_MSG_AUTHENTICATION_REQ_STRU          g_MmMsgAuthReq;
MM_MSG_CM_SVC_RJCT_STRU                 g_MmMsgCmSvcRjct;
MM_MSG_ABORT_STRU                       g_MmMsgAbort;
MM_MSG_ID_REQ_STRU                      g_MmMsgIdReq;
MM_MSG_LU_ACCPT_STRU                    g_MmMsgLuAccpt;
MM_MSG_LU_RJCT_STRU                     g_MmMsgLuRjct;
MM_MSG_MM_INFO_STRU                     g_MmMsgMmInfo;
MM_MSG_TMSI_REALLOC_CMD_STRU            g_MmMsgTmsiReallocCmd;
/*MM_MSG_MM_STATUS_STRU                   g_MmMsgMmStatus;*/

/* 定义AGENT发给MM的原语实体 */
MM_USIM_AUTHENTICATION_CNF_STRU      g_AgentUsimAuthCnf;


/* MM内部全局变量 */
MM_GLOBAL_CTRL_STRU                     g_MmGlobalInfo;
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
MM_TIMER_STRU                           gstMmTimer[MM_TIMER_MAX];
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

/* AS提供API函数指针结构体 */
NAS_MM_IMPORTED_FUNC_LIST_STRU          g_NasMmImportFunc;

MM_NSD_INFO_ST                          g_stMmNsd;

VOS_UINT32    g_MmMutexCnt;


VOS_UINT8     g_T3211Flag = 0;

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
const MM_CELL_FUN_TYPE        aMmEvent1[MM_STATE_MAX] = {
    Mm_Cell_S0_E1,                                  /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E1,                                  /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S1_E1,                                  /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S1_E1,                                  /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S1_E1,                                  /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S1_E1,                                  /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S1_E1,                                  /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S1_E1,                                  /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E1,                                  /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E1,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E1,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E1,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S13_E1,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E1,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S16_E1,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S1_E1,                                  /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S1_E1,                                  /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S1_E1,                                  /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E1,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S22_E1,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S22_E1,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S22_E1,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S22_E1,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S16_E1,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S31_E1,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE                         */
    
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */
};
const MM_CELL_FUN_TYPE        aMmEvent2[MM_STATE_MAX] = {
    Mm_Cell_S0_E2,                                  /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E2,                                  /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S1_E2,                                  /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S1_E2,                                  /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E2,                                  /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S4_E2,                                  /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S1_E2,                                  /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S1_E2,                                  /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E2,                                  /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E2,                                  /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E2,                                  /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S9_E2,                                  /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E2,                                  /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E2,                                  /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S1_E2,                                  /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S1_E2,                                  /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S19_E2,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    NAS_MM_RcvAttachReq_InterRatChange,             /* S32: MM_INTER_RAT_CHANGE                         */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)    
    NAS_MM_RcvMmcMmAttachReq_MmIdleECallInactive,  /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent3[MM_STATE_MAX] = {
    Mm_Cell_S0_E3,                                  /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E3,                                  /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S1_E3,                                  /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S1_E3,                                  /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S1_E3,                                  /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S1_E3,                                  /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S1_E3,                                  /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S1_E3,                                  /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S1_E3,                                  /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S1_E3,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE                          */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, begin */    
#if (FEATURE_ON == FEATURE_ECALL)    
    NAS_MM_RcvMmcMmPlmnSrchInit_MmIdleECallInactive, /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, end */     
};

/* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */
const MM_CELL_FUN_TYPE        aMmEvent5[MM_STATE_MAX] = {
    Mm_Nop       ,                                  /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E5,                                  /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S2_E5,                                  /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E5,                                  /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E5,                                  /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E5,                                  /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E5,                                  /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E5, /* Mm_Cell_S0_E5 , */            /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E5, /* Mm_Cell_S0_E5 , */            /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E5, /* Mm_Cell_S0_E5 , */            /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E5, /* Mm_Cell_S0_E5 , */           /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E5, /* Mm_Cell_S0_E5 , */            /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E5, /* Mm_Cell_S0_E5 , */            /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E5, /* Mm_Cell_S0_E5 , */            /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E5,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S18_E5,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S2_E5,                                  /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E5,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S23_E5,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E5, /* Mm_Nop, */                    /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)    
    NAS_MM_RcvMmcMmSysInfo_MmIdleECallInactive,    /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, end */     
};
/* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */


const MM_CELL_FUN_TYPE        aMmEvent6[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E6,                                  /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S3_E6,                                  /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E6,                                  /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S3_E6,                                  /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S3_E6,                                  /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent7[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E7,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent8[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E8,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent9[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E9,                                  /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E9,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S3_E9,                                  /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent10[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S18_E10,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S18_E10,                                /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent11[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S3_E11, /* Mm_Nop, */                   /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S3_E11, /* Mm_Nop, */                   /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E11,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E11,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E11,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */

    /* TC状态收到GMMMM_GPRS_DETACH_INITIATION也迁到IMSI_DETACH_PENDING状态 */
    Mm_Cell_S3_E11,                                 /* S31: TEST_CONTROL_ACTIVE                         */

    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent12[MM_STATE_MAX] = {
    Mm_Cell_S4_E12,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S4_E12,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S4_E12,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E12,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E12,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E12,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S4_E12,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S4_E12,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S4_E12,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S4_E12,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S4_E12,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S4_E12,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S4_E12,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S4_E12,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S4_E12,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */

    Mm_Cell_S17_E12,                                /* S17: LOCATION UPDATING PENDING                   */
    
    Mm_Cell_S18_E12,                                /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S4_E12,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S4_E12,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S4_E12,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S4_E12,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S4_E12,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S4_E12,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S4_E12,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S4_E12,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent13[MM_STATE_MAX] = {
    Mm_Cell_S0_E13,                                 /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E13,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E13,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E13,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S3_E13,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S0_E13,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E13,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E13,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E13,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E13,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S12_E13,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E13,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E13,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E13,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S3_E13,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E13,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S23_E13,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S0_E13,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S0_E13,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S0_E13,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E13,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent14[MM_STATE_MAX] = {
    Mm_Cell_S0_E14,                                 /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E14,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S3_E14,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E14,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S3_E14,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S0_E14,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E14,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E14,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E14,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E14,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S12_E14,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E14,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E14,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S3_E14,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S12_E14,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E14,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S24_E14,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S0_E14,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S0_E14,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E14,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent15[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S2_E15,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */

    Mm_Cell_S3_E15,                                 /* S3 : MM IDLE NORMAL SERVICE                      */

    Mm_Cell_S2_E15,                                 /* S4 : MM IDLE LIMITED SERVICE                     */

    Mm_Cell_S4_E15,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E15,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E15, /* Mm_Nop, */                   /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E15, /* Mm_Nop, */                   /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E15, /* Mm_Nop, */                   /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S9_E15, /* Mm_Nop, */                   /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E15, /* Mm_Nop, */                   /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E15, /* Mm_Nop, */                   /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E15, /* Mm_Nop, */                   /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E15,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E15, /* Mm_Nop, */                   /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent16[MM_STATE_MAX] = {
    Mm_Cell_S0_E16, /* Mm_Nop, */                   /* S0 : MM_NULL                                     */
    Mm_Cell_S0_E16, /* Mm_Nop, */                   /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S0_E16, /* Mm_Nop, */                   /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E16,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S3_E16,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E16,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S3_E16,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S3_E16,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S3_E16,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E16,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E16,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S12_E16,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E16,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S3_E16,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S3_E16,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S3_E16,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S0_E16,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S12_E16,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S3_E16,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S11_E16,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S25_E16,                                /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S26_E16,                                /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S3_E16,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};

const MM_CELL_FUN_TYPE        aMmEvent17[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E17,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S3_E17,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E17,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S3_E17,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E17,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S3_E17,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S3_E17,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};

const MM_CELL_FUN_TYPE        aMmEvent18[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E18,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};

const MM_CELL_FUN_TYPE        aMmEvent19[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E19,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};

const MM_CELL_FUN_TYPE        aMmEvent20[MM_STATE_MAX] = {
    Mm_Cell_S0_E20,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E20,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S1_E20,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E20,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S1_E20,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E20,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S3_E20,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S1_E20,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E20,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E20,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E20,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S9_E20,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E20,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E20,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E20,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S9_E20,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S1_E20,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S9_E20,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E20,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E20,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S9_E20,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E20,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E20,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)   
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent21[MM_STATE_MAX] = {
    Mm_Cell_S0_E21, /* Mm_Nop, */                   /* S0 : MM_NULL                                     */
    Mm_Cell_S2_E21, /* Mm_Nop, */                   /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S2_E21,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S2_E21,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S2_E21,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S2_E21,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S2_E21,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S2_E21,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E21,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S14_E21,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E21,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S14_E21,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E21,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    /*Mm_Nop,*/                                     /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Cell_S14_E21,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E21,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S2_E21,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S2_E21,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S2_E21,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S14_E21,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E21,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E21,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S14_E21,                                /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S2_E21,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S2_E21,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)    
    NAS_MM_RcvMmcMmCoverageLostInd_MmIdleECallInactive, /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent22[MM_STATE_MAX] = {
    Mm_Cell_S0_E22,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S4_E22, /* Mm_Cell_S1_E22, */           /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S4_E22, /* Mm_Cell_S1_E22, */           /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E22,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E22,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S4_E22, /* Mm_Cell_S5_E22, */           /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S4_E22, /* Mm_Cell_S5_E22, */           /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S8_E22,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E22,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E22,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E22,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E22,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S12_E22,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E22,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E22,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E22, /* Mm_Nop, */                  /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S0_E22, /* Mm_Nop, */                   /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S23_E22,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S23_E22,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S24_E22,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E22,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S9_E22, /* Mm_Nop, */                   /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_E22,                                /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent23[MM_STATE_MAX] = {
    Mm_Cell_S0_E23,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S0_E23,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S0_E23,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E23,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S0_E23,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S0_E23,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S0_E23,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S0_E23,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E23,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E23,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E23,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E23,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S12_E23,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E23,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E23,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S17_E23,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S17_E23,                                /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S0_E23,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E23,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S22_E23,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E23,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S25_E23,                                /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S25_E23,                                /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E23,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S31_E23,                                /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_E23,                                /* S32: MM_INTER_RAT_CHANGE */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)   
    NAS_MM_RcvMmcMmPowerOffReq_MmIdleECallInactive, /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent24[MM_STATE_MAX] = {
    Mm_Cell_S0_E24, /* Mm_Nop, */                   /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E24,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S9_E24,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E24,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E24,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E24,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E24,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S4_E24,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E24,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E24,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E24,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S9_E24,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E24,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E24,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E24,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S22_E24,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S9_E24,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S19_E24, /*Mm_Cell_S9_E24,*/            /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E24,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S22_E24,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S22_E24,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S25_E24,/* Mm_Cell_S9_E24, */           /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S25_E24,/* Mm_Cell_S9_E24, */           /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S22_E24,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S0_E24,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_CCEstREQ,                           /* S32: MM_INTER_RAT_CHANGE */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)    
    NAS_MM_RcvCcEstReq_MmIdleECallInactive,        /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent25[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E25,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E25,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E25,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */

    Mm_Cell_S13_E25,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E25,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S16_E25,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S9_E25,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S9_E25,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,                       /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent26[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S2_E26,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S2_E26,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S2_E26,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S2_E26,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S2_E26,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S2_E26,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S2_E26,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S2_E26,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E26,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E26,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S2_E26,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E26,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S2_E26,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S2_E26,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S16_E26,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S2_E26,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S2_E26,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S2_E26,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S2_E26,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S2_E26,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S2_E26,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S2_E26,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S2_E26,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */

    Mm_Cell_S32_E26,                       /* S32: MM_INTER_RAT_CHANGE  */


    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent27[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S11_E27,                                /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E27,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E27,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S11_E27,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S10_E27,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,          /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent28[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S13_E28,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_CCEstREQ,                /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent29[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent30[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */
};

const MM_CELL_FUN_TYPE        aMmEvent31[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S2_E31,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E31,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E31,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E31,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E31,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S2_E31,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent32[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E32,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E32,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E32,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S25_E32,                                /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_E32,                               /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent33[MM_STATE_MAX] = {
    Mm_Cell_S0_E33,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S0_E33,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S2_E33,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S0_E33,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S0_E33,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S2_E33,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S0_E33,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S0_E33,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S0_E33,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E33,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E33,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E33,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E33,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S10_E33,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E33,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S16_E33,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S2_E33,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S2_E33,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S2_E33,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E33,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S23_E33,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S24_E33,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S25_E33,                                /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S26_E33,                                /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S10_E33,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30: RR CONNECTION RELEASE NOT ALLOWED           */
    Mm_Cell_S31_E33,                                /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S2_E33,                                 /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent34[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E34, /* Mm_Nop, */                   /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S3_E34, /* Mm_Nop, */                   /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E34, /* Mm_Nop, */                   /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E34,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E34,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S10_E34,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S3_E34, /* Mm_Nop, */                   /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S3_E34, /* Mm_Nop, */                   /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E34,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E34,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S10_E34,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S10_E34,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S10_E34,                                /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S10_E34,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent35[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E35,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E35,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E35,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E35,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S9_E35,                                 /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent36[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E36,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E36,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E36,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E36,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E36,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E36,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E36,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E36,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S9_E36,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent37[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E37,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E37,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E37,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E37,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E37,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E37,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E37,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S26_E37, /* Mm_Nop, */                  /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent38[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E38,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E38,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E38,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E38,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E38,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E38,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E38,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E38,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S9_E38,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent39[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E39,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E39,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E39,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E39,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E39,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E39,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E39,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E39,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S9_E39,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent40[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E40,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E40,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E40,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E40,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent41[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E41,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E40,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E41,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E41,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent42[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E42,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E42,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E42/*Mm_Nop*/,                       /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E42/*Mm_Nop*/,                       /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E42,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent43[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E43,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E43,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E43,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E43,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E43,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E43,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E43,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E43,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent44[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E44,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E44,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E44,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E44,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E44,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E44,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E44,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E44,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent45[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S23_E45,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */
};
const MM_CELL_FUN_TYPE        aMmEvent46[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S23_E46,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent47[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E47,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E47,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E47,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E47,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E47,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S10_E40, /* Mm_Nop, */                  /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent48[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E48,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E48,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E48,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E48,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E48,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E48,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E48,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E48,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */ 

};
const MM_CELL_FUN_TYPE        aMmEvent49[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E49,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S3_E49,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E49,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E49,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E49,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E49,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E49,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S10_E49,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S3_E49,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S3_E49,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E49,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S23_E49,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S24_E49,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S25_E49,                                /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S26_E49,                                /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent50[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E50,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E50, /* Mm_Cell_S9_E50, */          /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E50,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E50,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E50,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S14_E50,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent51[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S23_E51,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent52[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S9_E52,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S9_E52,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E52,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E52,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E52,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E52,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E52,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S9_E52,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E52,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E52,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E52,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent53[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E53,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S1_E53,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E53,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S1_E53,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E53,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E53,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S1_E53,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S6_E53,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S1_E53,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S1_E53,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S1_E53,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S1_E53,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S1_E53,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S1_E53,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S1_E53,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S6_E53,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S6_E53,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S1_E53,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S1_E53,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S1_E53,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S1_E53,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S1_E53,           /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent54[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E54,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S6_E54,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E54,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S6_E54,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */     
};
const MM_CELL_FUN_TYPE        aMmEvent55[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E55,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E55,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E55,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E55,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E55,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E55,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E55,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E55,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */
    
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */
};
const MM_CELL_FUN_TYPE        aMmEvent56[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E56,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E56,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E56,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E56,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E56,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E56,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E56,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E56,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent57[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E57,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E57,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E57,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E57,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E57,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E57,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E57,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E57,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent58[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S26_E58,                                /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent59[MM_STATE_MAX] = {
    Mm_Cell_S0_E59,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S0_E59,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S0_E59,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S0_E59,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S0_E59,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S0_E59,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S0_E59,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S0_E59,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S0_E59,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E59,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S0_E59,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S0_E59,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S0_E59,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S0_E59,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E59,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Cell_S0_E59,                                 /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E59,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S0_E59,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S0_E59,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S0_E59,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Cell_S0_E59,                                 /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Cell_S0_E59,                                 /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S0_E59,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S0_E59,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S0_E59,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S0_E59,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S0_E59,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S0_E59,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Cell_S0_E59,                                 /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Cell_S0_E59,                                 /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Cell_S0_E59,                                 /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent60[MM_STATE_MAX] = {
    Mm_Cell_S0_E60,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S0_E60,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S0_E60,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S0_E60,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S0_E60,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S0_E60,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S0_E60,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S0_E60,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S0_E60,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S0_E60,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S0_E60,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E60,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S0_E60,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S0_E60,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S0_E60,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Cell_S0_E60,                                 /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S0_E60,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S0_E60,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S0_E60,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S0_E60,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Cell_S0_E60,                                 /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Cell_S0_E60,                                 /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S0_E60,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S0_E60,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S24_E60,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S0_E60,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S0_E60,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S0_E60,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Cell_S0_E60,                                 /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Cell_S0_E60,                                 /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Cell_S0_E60,                                 /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent61[MM_STATE_MAX] = {
    Mm_Cell_S0_E61,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E61,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S0_E61,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S0_E61,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S0_E61,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S0_E61,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S0_E61,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S0_E61,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S0_E61,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S0_E61,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S0_E61,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S0_E61,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E61,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S13_E61,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S0_E61,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Cell_S0_E61,                                 /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S0_E61,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S0_E61,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S0_E61,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S0_E61,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Cell_S0_E61,                                 /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Cell_S0_E61,                                 /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S0_E61,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S0_E61,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S0_E61,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S0_E61,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S0_E61,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S0_E61,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Cell_S0_E61,                                 /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Cell_S0_E61,                                 /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Cell_S0_E61,                                 /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};


const MM_CELL_FUN_TYPE        aMmEvent62[MM_STATE_MAX] = {
    Mm_Cell_S4_E62,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S4_E62,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S11_E62,                                /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E62,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E62,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E62,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E62,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S4_E62,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S11_E62,                                /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E62,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E62,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S11_E62,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S11_E62,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S11_E62,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S11_E62,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S11_E62,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S11_E62,                                /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S4_E62,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S11_E62,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S11_E62,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S11_E62,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S4_E62,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S4_E62,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S11_E62,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_SMSEstREQ,             /* S32: MM_INTER_RAT_CHANGE */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)    
    NAS_MM_RcvSmsEstReq_MmIdleECallInactive,         /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, end */    
};


const MM_CELL_FUN_TYPE        aMmEvent63[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S1_E63,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S1_E63,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S1_E63,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E63,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S1_E63,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E63,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S1_E63,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S1_E63,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S16_E63,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S1_E63,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S1_E63,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S1_E63,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S1_E63,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S1_E63,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S1_E63,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_E63,                               /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent64[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E64,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S10_E64,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent65[MM_STATE_MAX] = {
    Mm_Cell_S4_E65,                                 /* S0 : MM_NULL                                     */

    Mm_Cell_S1_E65,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */

    Mm_Cell_S11_E65,                                /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E65,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S4_E65,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E65,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E65,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S4_E65,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S11_E65,                                /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E65,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E65,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S11_E65,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S11_E65,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S11_E65,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S11_E65,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S11_E65,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S11_E65,                                /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S4_E65,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S11_E65,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S11_E65,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S11_E65,                                /* S24: LOCATION UPDATE REJECTED                    */

    Mm_Cell_S25_E65,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S25_E65,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S11_E65,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_SSEstREQ,                /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)    
    NAS_MM_RcvSsEstReq_MmIdleECallInactive,         /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent66[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S12_E66,                                /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E66,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E66,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S16_E66,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent67[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E67,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S10_E67,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,          /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent68[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S27_E68,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,                       /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent69[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E69,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E69,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E69,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E69,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent70[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E70,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E70,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S11_E70,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E70,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent71[MM_STATE_MAX] = {
    Mm_Cell_S9_E71,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S9_E71,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S9_E71,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S9_E71,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S9_E71,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S9_E71,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S9_E71,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S9_E71,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E71,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E71,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E71,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S9_E71,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E71,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E71,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E71,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S9_E71,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S9_E71,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S9_E71,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S9_E71,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E71,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E71,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S9_E71,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E71,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E71,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S31_E71,                                /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent72[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S31_E72,                                /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent73[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E73,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E73,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E73,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E73,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E73,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E73,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E73,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E73,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E73,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S9_E73,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent74[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S6_E74,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E74,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                          /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent75[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E75,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E75,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E75,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E75,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E75,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S9_E75,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S9_E75,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S9_E75,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E75,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent76[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S25_E76,                                /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S25_E76,                                /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S25_E76,                                /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S25_E76,                                /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S25_E76,                                /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S25_E76,                                /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S25_E76,                                /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S25_E76,                                /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S25_E76,                                /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S25_E76,                                /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S25_E76,                                /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S25_E76,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S25_E76,                                /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S25_E76,                                /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S25_E76,                                /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S25_E76,                                /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S25_E76,                                /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent77[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E77,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S14_E77,                                /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S22_E77,                                /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent78[MM_STATE_MAX] = {
    Mm_Cell_S0_E78,                                 /* S0 : MM_NULL                                     */
    Mm_Cell_S0_E78,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S0_E78,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S0_E78,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S0_E78,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S0_E78,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S0_E78,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S0_E78,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S0_E78,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S0_E78,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S0_E78,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S0_E78,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S0_E78,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S0_E78,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S0_E78,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Cell_S0_E78,                                 /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S0_E78,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S0_E78,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S0_E78,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S0_E78,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Cell_S0_E78,                                 /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Cell_S0_E78,                                 /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S0_E78,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S0_E78,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S0_E78,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S0_E78,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S0_E78,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S0_E78,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Cell_S0_E78,                                 /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Cell_S0_E78,                                 /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S0_E78,                                 /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent79[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E79,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    /*Mm_Nop,*/                                     /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S13_E79,                                /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S12_E79,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent80[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S5_E80,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Cell_S5_E80,                                 /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S5_E80,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S5_E80,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E80,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S5_E80,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S5_E80,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S5_E80,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E80,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E80,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S5_E80,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E80,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S5_E80,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S5_E80,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S16_E80,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S5_E80,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S5_E80,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S5_E80,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S5_E80,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S5_E80,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S5_E80,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S5_E80,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S5_E80,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S5_E80,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_E80,                                /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent81[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S5_E81,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E81,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S10_E81,                                /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S5_E81,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S12_E81,                                /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S16_E81,                                /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,                       /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent82[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S27_E82,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent83[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E83,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E83,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                        /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent84[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    /*A32D12011==>在此状态下，接入层可能限制驻留，容许重选*/
    Mm_Cell_S3_E84,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    /*<==A32D12011*/
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E84,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S3_E84,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E84,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S3_E84,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Cell_S3_E84,                                 /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S3_E84,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S3_E84,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S3_E84,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S3_E84,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S3_E84,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S3_E84,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Cell_S3_E84,                                 /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S3_E84,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Cell_S3_E84,                                 /* S17: LOCATION UPDATING PENDING                   */
    Mm_Cell_S3_E84,                                 /* S18: IMSI DETACH PENDING                         */
    Mm_Cell_S3_E84,                                 /* S19: WAIT FOR ATTACH                             */
    Mm_Cell_S3_E84,                                 /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Cell_S3_E84,                                 /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Cell_S3_E84,                                 /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Cell_S3_E84,                                 /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Cell_S3_E84,                                 /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Cell_S3_E84,                                 /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Cell_S3_E84,                                 /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S3_E84,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Cell_S3_E84,                                 /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Cell_S3_E84,                                 /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                    * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Cell_S3_E84,                                 /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Cell_S3_E84,                                 /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Cell_S3_E84,                                 /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent85[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                            * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_E85,                                /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Cell_S32_E85,                                /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
const MM_CELL_FUN_TYPE        aMmEvent86[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E86,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S6_E86,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S6_E86,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S6_E86,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S6_E86,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S6_E86,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S6_E86,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Cell_S6_E86,                                 /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S6_E86,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Cell_S6_E86,                                 /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Cell_S6_E86,                                 /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S6_E86,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Cell_S6_E86,                                 /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S6_E86,                                 /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};

const MM_CELL_FUN_TYPE        aMmEvent87[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Nop,                                         /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Nop,                                         /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S27_E87,                                /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Cell_S32_DataTransfer,          /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */
};

const MM_CELL_FUN_TYPE        aMmEvent88[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Cell_S3_E88,                                 /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
    Mm_Cell_S3_E88,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
    Mm_Cell_S3_E88,                                 /* S4 : MM IDLE LIMITED SERVICE                     */
    Mm_Cell_S3_E88,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    Mm_Cell_S6_E88,                                 /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Cell_S3_E88,                                 /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Cell_S9_E88,                                 /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Cell_S9_E88,                                 /* S10: MM CONNECTION ACTIVE                        */
    Mm_Cell_S9_E88,                                 /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Cell_S9_E88,                                 /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Cell_S9_E88,                                 /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Cell_S9_E88,                                 /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Cell_S9_E88,                                 /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Cell_S9_E88,                                 /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Cell_S9_E88,                                 /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */
    
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)   
    NAS_MM_RcvMmcMmWAcInfoChangeInd_MmIdleECallInactive, /* S33: MM_IDLE_ECALL_INACTIVE                      */
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-3-31, end */

};

const MM_CELL_FUN_TYPE        aMmEvent89[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    Mm_Nop,                                         /* S1 : MM IDLE NO CELL AVAILABLE                   */
    Mm_Nop,                                         /* S2 : MM IDLE PLMN SEARCH                         */
#if (FEATURE_ON == FEATURE_LTE)
    Mm_Cell_S3_E89,                                 /* S3 : MM IDLE NORMAL SERVICE                      */
#else
    Mm_Nop,
#endif
    Mm_Nop,                                         /* S4 : MM IDLE LIMITED SERVICE                     */
#if (FEATURE_ON == FEATURE_LTE)
    Mm_Cell_S5_E89,                                 /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
#else
    Mm_Nop,
#endif
    Mm_Nop,                                         /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */
    Mm_Nop,                                         /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    Mm_Nop,                                         /* S10: MM CONNECTION ACTIVE                        */
    Mm_Nop,                                         /* S11: WAIT FOR NETWORK COMMAND                    */
    Mm_Nop,                                         /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */
    Mm_Nop,                                         /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/
    Mm_Nop,                                         /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    Mm_Nop,                                         /* S23: LOCATION UPDATING INITIATED                 */
    Mm_Nop,                                         /* S24: LOCATION UPDATE REJECTED                    */
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */
    Mm_Nop,                                         /* S27: PROCESS CM SERVICE PROMPT                   */
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    Mm_Nop,                                         /* S32: MM_INTER_RAT_CHANGE */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACTIVE                      */
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */    
};
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */


/* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, begin */
#if (FEATURE_ON == FEATURE_ECALL)
const MM_CELL_FUN_TYPE        aMmEvent_T3242ExpiredProcTbl[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S1 : MM IDLE NO CELL AVAILABLE                   */
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S2 : MM IDLE PLMN SEARCH                         */
    NAS_MM_RcvT3242Expired_MmIdleNormalService,     /* S3 : MM IDLE NORMAL SERVICE                      */
    NAS_MM_RcvT3242Expired_MmIdleNormalService,     /* S4 : MM IDLE LIMITED SERVICE                     */
    NAS_MM_RcvT3242Expired_MmIdleNormalService,     /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    NAS_MM_RcvT3242Expired_MmIdleNormalService,     /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */    
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */    
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S10: MM CONNECTION ACTIVE                        */
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S11: WAIT FOR NETWORK COMMAND                    */
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */    
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */    
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */    
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/    
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S23: LOCATION UPDATING INITIATED                 */
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S24: LOCATION UPDATE REJECTED                    */   
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */    
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S27: PROCESS CM SERVICE PROMPT                   */    
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */                                                     
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable,   /* S32: MM_INTER_RAT_CHANGE */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACITVE */
};

const MM_CELL_FUN_TYPE        aMmEvent_T3243ExpiredProcTbl[MM_STATE_MAX] = {
    Mm_Nop,                                         /* S0 : MM_NULL                                     */
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S1 : MM IDLE NO CELL AVAILABLE                   */
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S2 : MM IDLE PLMN SEARCH                         */
    NAS_MM_RcvT3243Expired_MmIdleNormalService,     /* S3 : MM IDLE NORMAL SERVICE                      */
    NAS_MM_RcvT3243Expired_MmIdleNormalService,     /* S4 : MM IDLE LIMITED SERVICE                     */
    NAS_MM_RcvT3243Expired_MmIdleNormalService,     /* S5 : MM IDLE ATTEMPTING TO UPDATE                */
    NAS_MM_RcvT3243Expired_MmIdleNormalService,     /* S6 : MM IDLE LOCATION UPDATE NEEDED              */
    Mm_Nop,                                         /* S7 : MM IDLE PLMN SEARCH, NORMAL SERVICE         */    
    Mm_Nop,                                         /* S8 : MM IDLE NO IMSI                             */    
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S9 : WAIT FOR OUTGOING MM CONNECTION             */
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S10: MM CONNECTION ACTIVE                        */
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S11: WAIT FOR NETWORK COMMAND                    */
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S12: WAIT FOR RR CONNECTION (MM CONNECTION)      */
    Mm_Nop,                                         /* S13: WAIT FOR REESTABLISH(WAIT FOR REEST REQ)    */
    Mm_Nop,                                         /* S14: WAIT FOR REESTABLISH(WAIT FOR EST_CNF)      */    
    Mm_Nop,                                         /* S15: WAIT FOR RR ACTIVE                          */    
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S16: WAIT FOR ADDITIONAL OUTGOING MM CONNECTION  */
    Mm_Nop,                                         /* S17: LOCATION UPDATING PENDING                   */
    Mm_Nop,                                         /* S18: IMSI DETACH PENDING                         */
    Mm_Nop,                                         /* S19: WAIT FOR ATTACH                             */    
    Mm_Nop,                                         /* S20: MM IDLE RECEIVING GROUPCALL(NORMAL SERVICE) */
    Mm_Nop,                                         /* S21: MM IDLE RECEIVING GROUPCALL(LIMITED SERVICE)*/    
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S22: WAIT FOR RR CONNECTION (LOCATION UPDATING)  */
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S23: LOCATION UPDATING INITIATED                 */
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S24: LOCATION UPDATE REJECTED                    */    
    Mm_Nop,                                         /* S25: WAIT FOR RR CONNECTION (IMSI DETACH)        */
    Mm_Nop,                                         /* S26: IMSI DETACH INITIATED                       */    
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S27: PROCESS CM SERVICE PROMPT                   */    
    Mm_Nop,                                         /* S28: MM CONNECTION ACTIVE (GROUP TRANSMIT MODE)  */
    Mm_Nop,                                         /* S29: WAIT FOR RR CONNECTION (GROUP TRANSMIT WAIT *
                                                     * FOR RR CONNECTION (GROUP TRANSMIT MODE)          */                                                     
    Mm_Nop,                                         /* S30:  RR CONNECTION RELEASE NOT ALLOWED          */
    Mm_Nop,                                         /* S31: TEST_CONTROL_ACTIVE                         */
    NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable,   /* S32: MM_INTER_RAT_CHANGE */
    Mm_Nop,                                         /* S33: MM_IDLE_ECALL_INACITVE */
};
#endif
/* Added by y00245242 for V3R3C60_eCall项目, 2014-3-31, end */

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-2, begin */
const MM_CELL_FUN_TYPE*       gaMmStateTable[91] = {
    aMmEvent1,
    aMmEvent2,
    aMmEvent3,
    (MM_CELL_FUN_TYPE *)0,
    aMmEvent5,
    aMmEvent6,
    aMmEvent7,
    aMmEvent8,
    aMmEvent9,
    aMmEvent10,
    aMmEvent11,
    aMmEvent12,
    aMmEvent13,
    aMmEvent14,
    aMmEvent15,
    aMmEvent16,
    aMmEvent17,
    aMmEvent18,
    aMmEvent19,
    aMmEvent20,
    aMmEvent21,
    aMmEvent22,
    aMmEvent23,
    aMmEvent24,
    aMmEvent25,
    aMmEvent26,
    aMmEvent27,
    aMmEvent28,
    aMmEvent29,
    aMmEvent30,
    aMmEvent31,
    aMmEvent32,
    aMmEvent33,
    aMmEvent34,
    aMmEvent35,
    aMmEvent36,
    aMmEvent37,
    aMmEvent38,
    aMmEvent39,
    aMmEvent40,
    aMmEvent41,
    aMmEvent42,
    aMmEvent43,
    aMmEvent44,
    aMmEvent45,
    aMmEvent46,
    aMmEvent47,
    aMmEvent48,
    aMmEvent49,
    aMmEvent50,
    aMmEvent51,
    aMmEvent52,
    aMmEvent53,
    aMmEvent54,
    aMmEvent55,
    aMmEvent56,
    aMmEvent57,
    aMmEvent58,
    aMmEvent59,
    aMmEvent60,
    aMmEvent61,
    aMmEvent62,
    aMmEvent63,
    aMmEvent64,
    aMmEvent65,
    aMmEvent66,
    aMmEvent67,
    aMmEvent68,
    aMmEvent69,
    aMmEvent70,
    aMmEvent71,
    aMmEvent72,
    aMmEvent73,
    aMmEvent74,
    aMmEvent75,
    aMmEvent76,
    aMmEvent77,
    aMmEvent78,
    aMmEvent79,
    aMmEvent80,
    aMmEvent81,
    aMmEvent82,
    aMmEvent83,
    aMmEvent84,
    aMmEvent85,
    aMmEvent86,
    aMmEvent87,
    aMmEvent88,
#if (FEATURE_ON == FEATURE_LTE)
    aMmEvent89,
#else
    (MM_CELL_FUN_TYPE *)0,
#endif

#if (FEATURE_ON == FEATURE_ECALL)

    aMmEvent_T3242ExpiredProcTbl,

    aMmEvent_T3242ExpiredProcTbl,
#endif

};
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-2, end */



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

