/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmDef.h
  Description : SM宏定义
  History     :
      1.  张志勇      2003.12.04   新版作成
      2.  张志勇   2005.01.10   移植修改
      3.  韩鲁峰   2005-11-20 ADD for A32D00790
      3.  韩鲁峰   2006-02-10 ADD for A32D01902
      4.  日    期 : 2006-12-30
          作    者 : 孙少华
          修改内容 : A32D08079
                     修改#define TAF_SM_REJ_CAUSE_PROTOCOL_ERR的值
      5.  L47619   2007-01-16 MOD for A32D08447
*******************************************************************************/

#ifndef _SM_DEF_H_
#define _SM_DEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#define  SM_MAX_NSAPI_NUM    11                                                 /* NSAPI的最大个数                          */

#define  SM_NSAPI_MIN_VALUE  5
#define  SM_NSAPI_MAX_VALUE  15

#define  SM_NW2UE_STATUS_CAUSE_TI_INVALID   81

#define  SM_NSAPI_OFFSET     5                                                  /* NSAPI的offset                            */
#define  SM_RETURN_NG        0
#define  SM_RETURN_OK        1

#define  SM_MAX_TI_NUM       256
#define  SM_MAX_CR_NUM       256

#define  SM_TRUE             1
#define  SM_FALSE            0
#define  SM_MAX_SND_MSG_LEN  400                                                /* 发送申请的最大的内存*/
#define  SM_SAPI_NOT_ASSIGN  0                                                  /* Requested LLC SAPI*/

/*Requested LLC SAPI:*/
#define  SM_SAPI_3           0x3
#define  SM_SAPI_5           0x5
#define  SM_SAPI_9           0x9
#define  SM_SAPI_11          0xB



/* 原语TAFSM_PDP_ACTIVATE_REJ的结构体 */
/* ucSmCause 的宏定义 */
#define TAF_SM_REJ_CAUSE_TIMER_TIMEOUT              201                         /* Timer timeout                            */
#define TAF_SM_REJ_CAUSE_GPRS_ATTACH_FAIL           202                         /* GPRS attach failure                      */
#define TAF_SM_REJ_CAUSE_OTHER_PDP_CONT_EXIST       203                         /* other PDP context exist                  */
#define TAF_SM_REJ_CAUSE_NSAPI_IN_USE               204                         /* NSAPI已经激活                            */
#define TAF_SM_REJ_CAUSE_COLLISION_WITH_NW          205                         /* 和网侧发起的更改过程冲突                 */
#define TAF_SM_REJ_CAUSE_GMM_INIT                   206                         /* GMM初始化                                */
#define TAF_SM_REJ_CAUSE_SGSN_VER_PRE_R99           207                         /* SGSN版本切换到R99之前的版本              */

#define TAF_SM_REJ_CAUSE_INSUFF_RESOURCE            26                          /* insufficient resources                   */
#define TAF_SM_REJ_CAUSE_MISS_OR_UNKNOWN_APN        27                          /* missing or unknown APN                   */
#define TAF_SM_REJ_CAUSE_UNKNOWN_PDP_ADDR_OR_TYPE   28                          /* unknown PDP address or PDP type          */
#define TAF_SM_REJ_CAUSE_USER_AUTHEN_FAIL           29                          /* user authentication failed               */
#define TAF_SM_REJ_CAUSE_ACT_REJ_BY_GGSN_SGW_OR_PGW 30                          /* activation rejected by GGSN, Serving GW or PDN GW */
#define TAF_SM_REJ_CAUSE_ACT_REJ_UNSPEC             31                          /* activation rejected， unspecified        */
#define TAF_SM_REJ_CAUSE_SERV_OPT_NOT_SUPP          32                          /* service option not supported             */
#define TAF_SM_REJ_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIB  33                          /* requested service option not subscribed  */
#define TAF_SM_REJ_CAUSE_SERV_OPT_TEMP_OUT_ORDER    34                          /* service option temporarily out of order  */
#define TAF_SM_REJ_CAUSE_NSAPI_USED                 35                          /* NSAPI already used                       */
#define TAF_SM_REJ_CAUSE_SEMANTIC_ERR_IN_TFT        41                          /* semantic error in the TFT operation      */
#define TAF_SM_REJ_CAUSE_SYNTACTIC_ERR_IN_TFT       42                          /* syntactical error in the TFT operation   */
#define TAF_SM_REJ_CAUSE_UNKNOWN_PDP_CONTEXT        43                          /* unknown PDP context                      */
#define TAF_SM_REJ_CAUSE_SEMANTIC_ERR_IN_PF         44                          /* semantic errors in packet filter(s)      */
#define TAF_SM_REJ_CAUSE_SYNTACTIC_ERR_IN_PF        45                          /* syntactical errors in packet filter(s)   */
#define TAF_SM_REJ_CAUSE_PDP_CONT_WITHOUT_TFT_ACT   46                          /* PDPcontext without TFT already activated */
#define TAF_SM_REJ_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED 50                          /* PDP type IPv4 only allowed               */
#define TAF_SM_REJ_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED 51                          /* PDP type IPv6 only allowed               */
#define TAF_SM_REJ_CAUSE_SINGLE_ADDR_ONLY_ALLOWED   52                          /* Single address bearers only allowed      */

#define TAF_SM_REJ_CAUSE_INVALID_TI                 0x51                        /* Invalid transaction identifier value     */
#define TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE       0x60                        /* Invalid mandatory information            */
#define TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT           0x61                        /* Message type non-existent or not
                                                                                *  implemented                              */
#define TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE       0x62            /* Message type not compatible with protocol state */
#define TAF_SM_REJ_CAUSE_STATE_ERR                  0x65                        /* Message not compatible with the protocol
                                                                                *  state                                    */

#define TAF_SM_REJ_CAUSE_PROTOCOL_ERR               0x6F                       /* protocol errors                          */


/**************************************************/
/* MS和network间的消息类型宏定义 */
#define SM_ACT_PDP_CONTEXT_REQ          0x41
#define SM_ACT_PDP_CONTEXT_ACC          0x42
#define SM_ACT_PDP_CONTEXT_REJ          0x43

#define SM_REQ_PDP_CONTEXT_ACT          0x44
#define SM_REQ_PDP_CONTEXT_REJ          0x45
#define SM_DEACT_PDP_CONTEXT_REQ        0x46
#define SM_DEACT_PDP_CONTEXT_ACC        0x47
#define SM_MOD_PDP_CONTEXT_REQ_N2M      0x48
#define SM_MOD_PDP_CONTEXT_ACC_M2N      0x49                                    /* Modify PDP context accept (MS to network
                                                                                *  direction)                               */
#define SM_MOD_PDP_CONTEXT_REQ_M2N      0x4A                                    /* Modify PDP context request(MS to network
                                                                                *  direction)                               */
#define SM_MOD_PDP_CONTEXT_ACC_N2M      0x4B                                    /* Modify PDP context accept (Network to MS
                                                                                *  direction)                               */
#define SM_MOD_PDP_CONTEXT_REJ          0x4C                                    /* Modify PDP context reject                            */

#define SM_ACT_SEC_PDP_CONTEXT_REQ      0x4D                                    /* Activate secondary PDP context request   */
#define SM_ACT_SEC_PDP_CONTEXT_ACC      0x4E                                    /* Activate secondary PDP context accept    */
#define SM_ACT_SEC_PDP_CONTEXT_REJ      0x4F                                    /* SM_Activate secondary PDP context reject */
#define SM_STATUS                       0x55                                    /* SM_stasus                                */

/* INVALID NSAPI */
#define SM_INVALID_NSAPI                   0xff

/* Domain */
#define SM_MM_COM_SRVDOMAIN_CS             1   /*与MM_COM_SRVDOMAIN_CS对应，请注意同步更新*/
#define SM_MM_COM_SRVDOMAIN_PS             2   /*与MM_COM_SRVDOMAIN_PS对应，请注意同步更新*/

/*定义下边这些宏来取出QOS数组码流中的各功能值：*/
#define NAS_SM_QOS_DELAY_CLASS_MASK                         (0x38)    /* 0011 1000*/
#define NAS_SM_QOS_RELIABILITY_CLASS_MASK                   (0x07)    /* 0000 0111*/
#define NAS_SM_QOS_PEAK_THROUGHPUT_MASK                     (0xF0)    /* 1111 0000*/
#define NAS_SM_QOS_PRECEDENCE_CLASS_MASK                    (0x07)    /* 0000 0111*/
#define NAS_SM_QOS_MEAN_THROUGHPUT_MASK                     (0x1F)    /* 0001 1111*/
#define NAS_SM_QOS_TRAFFIC_CLASS_MASK                       (0xE0)    /* 1110 0000*/
#define NAS_SM_QOS_DELIVERY_ORDER_MASK                      (0x18)    /* 0001 1000*/
#define NAS_SM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK             (0x07)    /* 0000 0111*/
#define NAS_SM_QOS_RESIDUAL_BER_MASK                        (0xF0)    /* 1111 0000*/
#define NAS_SM_QOS_SDU_ERROR_RATIO_MASK                     (0x0F)    /* 0000 1111*/
#define NAS_SM_QOS_TRANSFER_DELAY_MASK                      (0xFC)    /* 1111 1100*/
#define NAS_SM_QOS_TRAFFIC_HANDLING_PRIORITY_MASK           (0x03)    /* 0000 0011*/
#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
#define NAS_SM_QOS_SSD_MASK                                 (0x0F)    /* 0000 1111*/
#define NAS_SM_QOS_SIGNALLING_INDICATION_MASK               (0x10)    /* 0001 0000*/
#endif

/* 定义下面这些宏来说明QOS数组码流中的速率类型，上行或下行 */
#define NAS_SM_QOS_BIT_RATE_TYPE_UL                (1)
#define NAS_SM_QOS_BIT_RATE_TYPE_DL                (2)

#define NAS_SM_IEI_ACCESS_POINT_NAME               (0x28)
#define NAS_SM_IEI_PROTOCOL_CFG_OPTIONS            (0x27)
#define NAS_SM_IEI_PDP_ADDRESS                     (0x2B)
#define NAS_SM_IEI_PACKET_FLOW_ID                  (0x34)
#define NAS_SM_IEI_TRAFFIC_FLOW_TEMPLATE           (0x36)
#define NAS_SM_IEI_REQUEST_LLC_SAPI                (0x32)
#define NAS_SM_IEI_NEW_QOS                         (0x30)
#define NAS_SM_IEI_NEW_TFT                         (0x31)
#define NAS_SM_IEI_NEW_RADIO_PRIORITY              (0x08)
#define NAS_SM_IEI_TEARDOWN_INDICATOR              (0x90)
#if (FEATURE_ON == FEATURE_IPV6)
#define NAS_SM_IEI_CAUSE_TWO                                (0x39)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
