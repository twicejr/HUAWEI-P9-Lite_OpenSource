/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MM_Message.h
  Description : MM消息数据结构头文件
  History     :
      1.  张志勇         2003.11.24      新规作成
      2.  s46746         2006-03-39      根据问题单A32D02486修改
      3.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/

#ifndef _MM_MESSAGE_H_
#define _MM_MESSAGE_H_

#include "MmcMmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)
/*******************************************************************************
 *                                    PD宏定义                                 *
 *******************************************************************************/
#define MM_IE_PD_GROUP_CALL_CONTROL                 0                           /* group call control                       */
#define MM_IE_PD_BROADCAST_CALL_CONTROL             1                           /* broadcast call control                   */
#define MM_IE_PD_CALL_CONTROL                       3                           /* call control; call related SS messages   */
#define MM_IE_PD_GTTP                               4                           /* GPRS Transparent Transport Protocol      */
#define MM_IE_PD_MM_MSG                             5                           /* mobility management messages             */
#define MM_IE_PD_RRM_MSG                            6                           /* radio resources management messages      */
#define MM_IE_PD_GPRS_MM_MSG                        8                           /* GPRS mobility management messages        */
#define MM_IE_PD_SMS_MSG                            9                           /* SMS messages                             */
#define MM_IE_PD_GPRS_SM_MSG                        10                          /* GPRS session management messages         */
#define MM_IE_PD_NON_CALL_RLT_SS_MSG                11                          /* non call related SS messages             */
#define MM_IE_PD_LOCATION_SRVC                      12                          /* Location services                        */
#define MM_IE_PD_TEST                               15                          /* reserved for tests procedures            */

#define MM_IE_PD_MASK                               15

/*******************************************************************************
 *                              消息类型宏定义                                 *
 *******************************************************************************/
#define MM_IE_MSG_TYPE_IMSI_DETACH_INDICATION       1                           /* IMSI DETACH INDICATION                   */
#define MM_IE_MSG_TYPE_LU_ACCEPT                    2                           /* LOCATION UPDATING ACCEPT                 */
#define MM_IE_MSG_TYPE_LU_REJECT                    4                           /* LOCATION UPDATING REJECT                 */
#define MM_IE_MSG_TYPE_LU_REQUEST                   8                           /* LOCATION UPDATING REQUEST                */
#define MM_IE_MSG_TYPE_AUTH_REJ                     17                          /* AUTHENTICATION REJECT                    */
#define MM_IE_MSG_TYPE_AUTH_REQ                     18                          /* AUTHENTICATION REQUEST                   */
#define MM_IE_MSG_TYPE_AUTH_RES                     20                          /* AUTHENTICATION RESPONSE                  */
#define MM_IE_MSG_TYPE_AUTH_FAIL                    28                          /* AUTHENTICATION FAILURE                   */
#define MM_IE_MSG_TYPE_ID_REQ                       24                          /* IDENTITY REQUEST                         */
#define MM_IE_MSG_TYPE_ID_RES                       25                          /* IDENTITY RESPONSE                        */
#define MM_IE_MSG_TYPE_TMSI_REALLOC_CMD             26                          /* TMSI REALLOCATION COMMAND                */
#define MM_IE_MSG_TYPE_TMSI_REALLOC_CPL             27                          /* TMSI REALLOCATION COMPLETE               */
#define MM_IE_MSG_TYPE_CM_SERV_ACP                  33                          /* CM SERVICE ACCEPT                        */
#define MM_IE_MSG_TYPE_CM_SERV_REJ                  34                          /* CM SERVICE REJECT                        */
#define MM_IE_MSG_TYPE_CM_SERV_ABO                  35                          /* CM SERVICE ABORT                         */
#define MM_IE_MSG_TYPE_CM_SERV_REQ                  36                          /* CM SERVICE REQUEST                       */
#define MM_IE_MSG_TYPE_CM_SERV_PROMPT               37                          /* CM SERVICE PROMPT                        */

#define MM_IE_MSG_TYPE_PAGING_RSP                   39                          /* PAGING RESPONSE                          */

#define MM_IE_MSG_TYPE_REEST_REQ                    40                          /* CM RE-ESTABLISHMENT REQUEST              */
#define MM_IE_MSG_TYPE_ABORT                        41                          /* ABORT                                    */
#define MM_IE_MSG_TYPE_MM_NULL                      48                          /* MM NULL                                  */
#define MM_IE_MSG_TYPE_MM_STA                       49                          /* MM STATUS                                */
#define MM_IE_MSG_TYPE_MM_INFO                      50                          /* MM INFORMATION                           */

/*******************************************************************************
 *                              消息参数IE宏定义                                 *
 *******************************************************************************/
#define MM_IE_FULL_NAME_FOR_NETWORK                 0x43
#define MM_IE_SHORT_NAME_FOR_NETWORK                0x45
#define MM_IE_LOCAL_TIME_ZONE                       0x46
#define MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE    0x47
#define MM_IE_LSA_IDENTITY                          0x48
#define MM_IE_NETWORK_DAYLIGHT_SAVING_TIME          0x49
#define MM_IE_MM_TIMER                              (0x36)

/* 消息TAG和Length占2个字节*/
#define MM_IE_TL_LENGTH                             (2)
#define MM_IE_TAG_LENGTH                            (1)

#define MM_MSG_HEADER_LEN                               (2)
#define MM_IE_LOCAL_TIME_ZONE_LEN                       (2)
#define MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE_LEN    (8)
#define MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_LEN          (3)
#define MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_VALUE_LEN    (1)
#define MM_IE_LSA_IDENTITY_VALUE_MAX_LEN                (3)
#define MM_CM_SRV_REJ_MIN_LEN                           (3)
#define MM_CM_SRV_REJ_MAX_LEN                           (6)



/* IE结构体定义 */
/*******************************************************************************
 *                          COMMON IE STRUCTURE                                *
 *******************************************************************************/

/* 10.5.1.2 Ciphering Key  Sequence Number  */
typedef struct{
    #define                     MM_IE_CKSN_NO_KEY_AVAILABLE             0x07    /* No key is available (MS to network)      */
    #define                     MM_IE_CKSN_RESERVED                     0x07    /* Reserved (network to MS)                 */
    #define                     MM_IE_CKSN_KEY_SEQUENCE_MASK            0x07    /* CKSN后三位有效                           */
    VOS_UINT8                       ucCksn;                                         /* CKSN                                     */
}MM_IE_CKSN_STRU;

/* 10.5.1.3 Location Area Identification  */
typedef struct{
    #define                     MM_IE_LU_ID_MCC_DIGIT_2_MASK    0xf0            /* MCC digit 2的5-8位有效                   */
    #define                     MM_IE_LU_ID_MCC_DIGIT_1_MASK    0x0f            /* MCC digit 1的1-4位有效                   */
    #define                     MM_IE_LU_ID_MCC_DIGIT_3_MASK    0x0f            /* MCC digit 3的1-4位有效                   */
    #define                     MM_IE_LU_ID_MNC_DIGIT_3_MASK    0xf0            /* MNC digit 3的5-8位有效                   */
    #define                     MM_IE_LU_ID_MNC_DIGIT_2_MASK    0xf0            /* MNC digit 2的5-8位有效                   */
    #define                     MM_IE_LU_ID_MNC_DIGIT_1_MASK    0x0f            /* MNC digit 1的1-4位有效                   */
    MM_LAI_STRU                 IeLai;                                          /* Location Area Identity                   */
}MM_IE_LAI_STRU;

/* 10.5.1.4 Mobile Identity  */
#define MM_IEI_LAI                                              0x13
#define MM_IEI_MOBILE_ID                                        0x17
#define MM_IEI_MS_CLASSMARK_3                                   0x20

#define MM_IEI_ADDITIONAL_UPDATE_PARAMETERS                     (0xC0)
#define MM_IE_CSFB_CSMT_FLAG_EXIST                              (0x01)          /* 存在CSMT标志                            */

#define MM_IEI_MS_NETWORK_FEATURE_SUPPORT                       (0xE0)
#define MM_IE_MS_SUPPORT_EXTEND_PERIODIC_TIMER_IN_THIS_DOMAIN   (0x01)

#define MM_IE_CSFB_CSMO_FLAG_EXIST                              (0x02)          /* 存在CSMO标志                            */

#define MM_IE_MI_ID_TYPE_IMSI                                   0x01            /* 参见 10.5.1.4 Mobile Identity            */
#define MM_IE_MI_ID_TYPE_IMEI                                   0x02
#define MM_IE_MI_ID_TYPE_IMEISV                                 0x03
#define MM_IE_MI_ID_TYPE_TMSI                                   0x04
#define MM_IE_MI_ID_TYPE_NO_ID                                  0x00


#define MM_IE_MI_ID_DIGIT_1_MASK                                0xf0            /* Identity digit 1的5-8位有效              */
#define MM_IE_MI_OEI_MASK                                       0x08            /* odd/even indic的第4位有效                */
#define MM_IE_MI_ID_TYPE_MASK                                   0x07            /* Type of identity的后3位有效              */
#define MM_IE_MI_ID_DIGIT_P_ADD_1_MASK                          0xf0            /* Identity digit p+1的5-8位有效            */
#define MM_IE_MI_ID_DIGIT_P_MASK                                0x0f            /* Identity digit p的1-4位有效              */
typedef struct
{
    MM_MOBILE_ID_STRU                   MobileID;


}MM_IE_MOBILE_ID_STRU;

/* 10.5.1.5 Mobile Station Classmark 1  */
typedef struct{
/*  MM_IE_COMMON_PARA_STRU      IeCommonPara;                    */             /* IE公共变量结构体                         */
    #define                     MM_IE_MS_CLASSMARK1_REVISION_LEVEL_MASK 0x60    /* Revision level的6，7位有效               */
    VOS_UINT8                       ucRevisionLev;                                  /* Revision level                           */
    #define                     MM_IE_MS_CLASSMARK1_ES_IND_MASK         0x10    /* ES IND的第5位有效                        */
    VOS_UINT8                       ucEsInd;                                        /* ES IND                                   */
    #define                     MM_IE_MS_CLASSMARK1_A5_1_MASK           0x08    /* A5_1的第4位有效                          */
    VOS_UINT8                       ucA5_1;                                         /* A5_1                                     */
    #define                     MM_IE_MS_CLASSMARK1_RF_POW_CAP_MASK     0x07    /* RF powercapability的后3位有效            */
    VOS_UINT8                       ucRFPowCap;                                     /* RF powercapability                       */
}MM_IE_MS_CLASSMARK1_STRU;

/* 10.5.1.6 Mobile station classmark 2  */
typedef struct{

    VOS_UINT8               aucClassmark2 [4];                                      /* classmark 2 information                  */

}MM_IE_MS_CLASSMARK2_STRU;

/* 10.5.1.11 Priority Level  */
typedef struct{
/*  MM_IE_COMMON_PARA_STRU      IeCommonPara;                    */             /* IE公共变量结构体                         */
    #define MM_IE_PRIO_LEVE_NULL        0                                       /* no priority applied                      */
    #define MM_IE_PRIO_LEVE_4           1                                       /* call priority level 4                    */
    #define MM_IE_PRIO_LEVE_3           2                                       /* call priority level 3                    */
    #define MM_IE_PRIO_LEVE_2           3                                       /* call priority level 2                    */
    #define MM_IE_PRIO_LEVE_1           4                                       /* call priority level 1                    */
    #define MM_IE_PRIO_LEVE_0           5                                       /* call priority level 0                    */
    #define MM_IE_PRIO_LEVE_B           6                                       /* call priority level B                    */
    #define MM_IE_PRIO_LEVE_A           7                                       /* call priority level A                    */
    #define MM_IE_PRIO_LEVE_MASK        0x07                                    /* 后3 位有效                               */
    VOS_UINT8   ucPrioLeve;                                                         /* CM service type                          */
}MM_IE_PRIO_LEVE_STRU;

/* 10.5.1.13 PLMN list */
typedef struct{

    VOS_UINT8                       ucPlmnNum;                                      /* 列表中PLMN数目                           */
    #define                     MM_PLMN_LIST_MAX                    0x2D        /* IE中PLMN ID最大数目                      */
    MM_PLMN_ID_STRU                aPlmnId[MM_PLMN_LIST_MAX];
}MM_IE_PLMN_LIST_STRU;

/********************************************************************************
 *                  MM Message IE Structure                                     *
 ********************************************************************************/
/* 10.5.3.1 Authentication parameter RAND */
typedef struct{
    #define                     MM_RAND_VALUE_LENGTH            0x10
    VOS_UINT8                       aucRandValue[MM_RAND_VALUE_LENGTH];             /* RAND value                               */
}MM_IE_RAND_STRU;

/* 10.5.3.1.1 Authentication Parameter AUTN(UMTS authentication challenge only)*/
typedef struct{
    #define                     MM_AUTN_MAX_LENGTH              0x10
    VOS_UINT8                       ucAutnLen;                                      /* 参数AUTN的长度                           */
    VOS_UINT8                       aucAutn[MM_AUTN_MAX_LENGTH];                    /* AUTN                                     */
}MM_IE_AUTN_STRU;

/* 10.5.3.2 Auth. Response parameter */
typedef struct{

    VOS_UINT8                       aucSgnfcntRES[4];                               /* SRES value or most significant4 octets   *
                                                                                 * of RES                                   */

}MM_IE_AUTH_RSP_PARA_STRU;

/* 10.5.3.2.1 Auth. Response parameter (extension) */
typedef struct{
    VOS_UINT8                       ucLength;                                       /* RES的长度                                */
    VOS_UINT8                       aucRES[12];                                     /* RES的数据                                */
}MM_IE_AUTH_RSP_PARA_EXT_STRU;

/*  10.5.3.2.2 Authentication Failure parameter  */
typedef struct{
    VOS_UINT8                       ucLength;                                       /* 鉴权失败参数的长度                       */

    VOS_UINT8                       aucAuthFailPara[14];                            /* 鉴权失败参数                             */

}MM_IE_AUTH_FAIL_PARA_STRU;


#define MM_IE_CM_SVC_TYPE_MO_CALL_EST           1                           /* Mobile originating call establishment or *
                                                                             * packet mode connection establishment     */
#define MM_IE_CM_SVC_TYPE_EMG_CALL_EST          2                           /* Emergency call establishment             */
#define MM_IE_CM_SVC_TYPE_SMS                   4                           /* Short message service                    */
#define MM_IE_CM_SVC_TYPE_SS_ACT                8                           /* Supplementary service activation         */
#define MM_IE_CM_SVC_TYPE_VG_CALL_EST           9                           /* Voice group call establishment           */
#define MM_IE_CM_SVC_TYPE_VB_CALL_EST           10                          /* Voice broadcast call establishment       */
#define MM_IE_CM_SVC_TYPE_LS                    11                          /* Location Services                        */


/* 10.5.3.3 CM service type  */
typedef struct{
    VOS_UINT8   ucCMSvcType;                                                        /* CM service type                          */
}MM_IE_CM_SVC_TYPE_STRU;

/* 10.5.3.4 Identity type  */
typedef struct{
    #define                     MM_IE_ID_TYPE_IDTYPE_MASK    0x07               /* IDType的第1-3位有效                      */
    VOS_UINT8                       ucIDType;                                       /* IDType                                   */
}MM_IE_ID_TYPE_STRU;

/* 10.5.3.5 Location updating type  */
typedef struct{
    #define                     MM_IE_LU_TYPE_FOR_MASK    0x08                  /* FOR的第4位有效                           */
    VOS_UINT8                       ucFOR;                                          /* FOR                                      */
    #define                     MM_IE_LU_TYPE_LUT_MASK    0x07                  /* LUT的第1-3位有效                         */
    VOS_UINT8                       ucLUT;                                          /* LUT                                      */
}MM_IE_LU_TYPE_STRU;

/* 10.5.3.5a Network Name */
typedef struct{
    VOS_UINT8                       ucLength;                                       /* Length of Network Name contents          */
    #define                     MM_NUM_OF_SPRBIT_IN_LST_OCT_MASK    0x07        /* 参数在消息中的有效位置                   */
    #define                     MM_NO_INFO                          0x00        /* this field carries no information about
                                                                                 * the number of spare bits in octet n      */
    #define                     MM_BIT8_SPARE_SET_TO_ZERO           0x01        /* bit 8 is spare and set to "0" in octet n */
    #define                     MM_BIT7_TO_8_SPARE_SET_TO_ZERO      0x02        /* bits 7 and 8 are spare and set to "0" in
                                                                                 *  octet n                                 */
    #define                     MM_BIT6_TO_8_SPARE_SET_TO_ZERO      0x03        /* bits 6 to 8(inclusive) are spare and set *
                                                                                 *  to "0" in octet n                       */
    #define                     MM_BIT5_TO_8_SPARE_SET_TO_ZERO      0x04        /* bits 5 to 8(inclusive) are spare and set *
                                                                                 *  to "0" in octet n                       */
    #define                     MM_BIT4_TO_8_SPARE_SET_TO_ZERO      0x05        /* bits 4 to 8(inclusive) are spare and set *
                                                                                 *  to "0" in octet n                       */
    #define                     MM_BIT3_TO_8_SPARE_SET_TO_ZERO      0x06        /* bits 3 to 8(inclusive) are spare and set *
                                                                                 *  to "0" in octet n                       */
    #define                     MM_BIT2_TO_8_SPARE_SET_TO_ZERO      0x07        /* bits 2 to 8(inclusive) are spare and set *
                                                                                 *  to "0" in octet n                       */
    VOS_UINT8                       ucNumOfSprbitInLstOct;                          /* Number of sparebits in last octet        */
    #define                     MM_ADDCI_MASK                       0x80        /* 参数在消息中的有效位置                   */
    #define                     MM_NOT_ADD_LETTER                   0x00        /* The MS should not add the letters for the*
                                                                                 *  Country's Initials to the text string   */
    #define                     MM_ADD_LETTER                       0x01        /* The MS should add the letters for the    *
                                                                                 * Country's Initials and a separator       */
    VOS_UINT8                       ucAddCI;                                        /* AddCI                                    */
    #define                     MM_CODE_SCHEME_MASK                 0x70        /* 参数在消息中的有效位置                   */
    #define                     MM_CELL_BRDCST_DAT_SCHEME           0x00        /* Cell Broadcast data coding scheme        */
    #define                     MM_UCS2_SCHEME                      0x01        /* UCS2 (16 bit) [72]                       */
    VOS_UINT8                       ucCodeScheme;                                   /* coding scheme                            */

    VOS_UINT32                       ulTextLen;                                      /* Text struing的长度，以bit为单位          */
    VOS_UINT8                       *pucTextStr;                                    /* Text String                              */
}MM_IE_NW_NAME_STRU;


/*  10.5.3.6 Reject Cause */
typedef struct{
    #define MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_LOW           0x30   /* retry upon entry into a new cell的下限   */
    #define MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_UP            0x3f   /* retry upon entry into a new cell的上限   */
    VOS_UINT8   ucRejCause;                                                         /* 拒绝原因                                 */
}MM_IE_REJECT_CAUSE_STRU;


/* 10.5.3.7 Follow-on Proceed */
typedef struct{

    VOS_UINT32                         ulReserved;
}MM_IE_FOLLOW_ON_STRU;

/* 10.5.3.8 Time Zone */
typedef struct{
    VOS_INT8                        cTimeZone;              /* 以15分钟为单位, 与标准时间的差距 */
}MM_IE_TIME_ZONE_STRU;

/* 年，月，日，时，分，秒，示例: ucHour: 0x0a ,表示10点 */
typedef struct{
    VOS_UINT8                       ucYear;
    VOS_UINT8                       ucMonth;
    VOS_UINT8                       ucDay;
    VOS_UINT8                       ucHour;
    VOS_UINT8                       ucMinute;
    VOS_UINT8                       ucSecond;
    VOS_INT8                        cTimeZone;
    VOS_UINT8                       Reserved;
}MM_IE_TIME_ZONE_TIME_STRU;

/* 10.5.3.10 CTS permission */
typedef struct{

    VOS_UINT32                       ulReserved;
}MM_IE_CTS_PERMISSION_STRU;

/* 10.5.3.11 LSA Identifier */
typedef struct{
    VOS_UINT8                       ucLsaLen;                                       /* Length of LSA Identifier contents        */
    #define             MM_LSAID_TYPE_MASK      0x01                            /* Length不为零,用于ucLSAID[2]              */
    VOS_UINT8                       ucLSAID[3];                                     /* LSA ID                                   */
}MM_IE_LSA_ID_STRU;

/* 10.5.3.12 Daylight Saving Time */
typedef struct{
    VOS_UINT8                       ucLength;                                       /* Length of Daylight Saving Time contents  */
    #define         MM_DAYLIGHT_SAVEING_TIME_VALUE_MASK         0x03            /* VALUE的有效位                            */
    #define         MM_NO_ADJSTMNT_FOR_DYLGHT_SAV_TM            0x00            /* No adjustment for Daylight Saving Time   */
    #define         MM_ADD_ONE_HOUR_FOR_DYLGHT_SAV_TM           0x01            /* +1 hour adjustment                       */
    #define         MM_ADD_TWO_HOURS_FOR_DYLGHT_SAV_TM          0x02            /* +2 hour adjustment                       */
    #define         MM_RESERVED_FOR_DYLGHT_SAV_TM               0x03            /* Reserved                                 */
    VOS_UINT8                       ucValue;                                        /* Daylight Saving Time value               */

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-27, begin */
    VOS_UINT8                       aucReserved2[2];
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-27, end */
}MM_IE_DAYLIGHT_SAV_TIME_STRU;




/* MM 消息结构体定义 */

/* 9.2.2 Authentication request */
typedef struct{
    MM_IE_CKSN_STRU             MmIeCKSN;                                       /* Ciphering Key Sequence Number            */
    MM_IE_RAND_STRU             MmIeRAND;                                       /* Authentication parameter RAND            */
#define MM_IE_AUTN_ABSENT   0
#define MM_IE_AUTN_PRESENT  1
    VOS_UINT8                       ucAutnFlg;                                      /* AUTN 存在标识                            */
    MM_IE_AUTN_STRU             MmIeAUTN;                                       /* Authentication Parameter AUTN            */
}MM_MSG_AUTHENTICATION_REQ_STRU;

/* 9.2.3 Authentication response */
typedef struct{
    MM_IE_AUTH_RSP_PARA_STRU        MmIeAuthRspPara;                            /* Auth. Response parameter                 */


#define MM_IE_AUTN_EXT_ABSENT  0
#define MM_IE_AUTN_EXT_PRESENT 1

    VOS_UINT8                           ucAutnRspParaExtFlg;                        /* MmIeAuthRspParaExt 存在标识              */
    MM_IE_AUTH_RSP_PARA_EXT_STRU    MmIeAuthRspParaExt;                         /* Auth. Response parameter (extension)     */
}MM_MSG_AUTHENTICATION_RSP_STRU;

/* 9.2.3a Authentication Failure */
typedef struct{
    MM_IE_REJECT_CAUSE_STRU     MmIeRejCause;                                   /* Reject Cause                             */
    VOS_UINT8                       ucAuthFailParaFlg;                              /* MmIeAuthFailPara 存在标识                */
    MM_IE_AUTH_FAIL_PARA_STRU   MmIeAuthFailPara;                               /* Authentication Failure parameter         */
}MM_MSG_AUTHENTICATION_FAIL_STRU;

/* 9.2.4 CM Re-establishment request */
typedef struct{
    MM_IE_CKSN_STRU             MmIeCKSN;                                       /* Ciphering Key Sequence Number            */
    MM_IE_MOBILE_ID_STRU        MmIeMobileId;                                   /* Mobile Identity                          */

    MM_IE_LAI_STRU              MmIeLai;                                        /* Location Area Identification             */
}MM_MSG_RE_EST_REQ_STRU;


/* 9.2.5a CM service prompt $(CCBS)$ */
/* TBD. */

/* 9.2.6 CM service reject */
typedef struct{
    MM_IE_REJECT_CAUSE_STRU             MmIeRejCause;                           /* Reject Cause                             */
    VOS_UINT8                           ucIsCmSrvRejCongestionWithT3246;        /* VOS_TRUE:CM SERVICE REJ消息中携带T3246; VOS_FALSE:CM SERVICE REJ消息中未携带T3246 */
}MM_MSG_CM_SVC_RJCT_STRU;


/* 9.2.8 Abort */
typedef struct{
    MM_IE_REJECT_CAUSE_STRU     MmIeRejCause;                                   /* Reject Cause                             */
}MM_MSG_ABORT_STRU;

/* 9.2.9 CM service request */
typedef struct{
    MM_IE_CM_SVC_TYPE_STRU      MmIeCmSvcType;                                  /* CM service type                          */
    MM_IE_CKSN_STRU             MmIeCKSN;                                       /* Ciphering Key Sequence Number            */
    MM_IE_MOBILE_ID_STRU        MmIeMobileId;                                   /* Mobile Identity                          */
    VOS_UINT8                       ucPrioLeveFlg;                                  /* MmIePrioLeve 存在标识                    */
    MM_IE_PRIO_LEVE_STRU        MmIePrio;                                       /* Priority Level                           */
}MM_MSG_CM_SVC_REQ_STRU;

/* 9.2.10 Identity request */
typedef struct{
    MM_IE_ID_TYPE_STRU          MmIeIdType;                                     /* Identity type                            */
}MM_MSG_ID_REQ_STRU;

/* 9.2.11 Identity response */
typedef struct{
    MM_IE_MOBILE_ID_STRU        MmIeMobileId;                                   /* Mobile Identity                          */
}MM_MSG_ID_RSP_STRU;

/* 9.2.12 IMSI detach indication */
typedef struct{
    MM_IE_MS_CLASSMARK1_STRU    MmIeMsClassmark;                                /* Mobile Station Classmark 1               */
    MM_IE_MOBILE_ID_STRU        MmIeMobileId;                                   /* Mobile Identity                          */
}MM_MSG_IMSI_DETACH_IND_STRU;

/* 9.2.13 Location updating accept */
typedef struct{
    MM_IE_LAI_STRU              MmIeLAI;                                        /* Location Area Identification             */
    /*MM_IE_FOLLOW_ON_STRU        MmIeFollowOn;*/                                   /* Follow-on Proceed                        */
    /*MM_IE_CTS_PERMISSION_STRU   MmIeCtsPermis;*/                                  /* CTS permission                           */
    MM_IE_PLMN_LIST_STRU        MmIePlmnList;                                   /* PLMN list                                */

    VOS_UINT8                       ucMobileIDFlg;                                  /* MmIeMobileId 存在标识                    */
    MM_IE_MOBILE_ID_STRU        MmIeMobileId;                                   /* Mobile Identity                          */
    VOS_UINT8                       ucFollowOFlg;                                   /* MmIeFollowOn 存在标识                    */
    VOS_UINT8                       ucCtsPermisFlg;                                 /* MmIeCtsPermis 存在标识                   */
    VOS_UINT8                       ucPlmnListFlg;                                  /* MmIePlmnList 存在标识                    */
    VOS_UINT8                       ucEmcFlg;                                   /* Emergency Number LIst 存在标识             */
}MM_MSG_LU_ACCPT_STRU;


/* 9.2.14 Location updating reject */
typedef struct{
    MM_IE_REJECT_CAUSE_STRU     MmIeRejCause;                                   /* Reject Cause                             */
}MM_MSG_LU_RJCT_STRU;

/* 9.2.15 Location updating request */
typedef struct{
    MM_IE_LU_TYPE_STRU          MmIeLuType;                                     /* Location updating type                   */
    MM_IE_CKSN_STRU             MmIeCksn;                                       /* Ciphering key sequence number            */
    MM_IE_LAI_STRU              MmIeLAI;                                        /* Location area identification             */
    MM_IE_MS_CLASSMARK1_STRU    MmIeMsClsMsk;                                   /* Mobile station classmark                 */
    MM_IE_MOBILE_ID_STRU        MmIeMobileId;                                   /* Mobile identity                          */
    VOS_UINT8                       ucMsClsMskFrUMTSFlg;                            /* MmIeMsClsMskFrUMTS 存在标识              */
    MM_IE_MS_CLASSMARK2_STRU    MmIeMsClsMskFrUMTS;                             /* Mobile station classmark for UMTS        */
}MM_MSG_LU_REQ_STRU;

/* 9.2.15a MM information */
typedef struct{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-26, begin */
    /* 网络名字段目前未使用,只标识长短名IE是否存在，如果存在需要通知mmc，mmc再通知mma，mma更新全局变量供查询使用  */
    VOS_UINT8                       ucFulNamFrNWFlg;                            /* MmIeFulNamFrNW 存在标识                  */
    /*MM_IE_NW_NAME_STRU              MmIeFulNamFrNW;*/                         /* Full name for network 10.5.3.5a          */
    VOS_UINT8                       ucShortNamFrNWFlg;                          /* MmIeShortNamFrNW 存在标识                */
    /*MM_IE_NW_NAME_STRU              MmIeShortNamFrNW;*/                       /* Short name for network 10.5.3.5a         */

    VOS_UINT8                       ucLocalTmZoneFlg;                           /* MmIeLocalTmZone 存在标识                 */
    MM_IE_TIME_ZONE_STRU            MmIeLocalTmZone;                            /* Local time zone 10.5.3.8                 */
    VOS_UINT8                       ucUnvrslTmAndLocalTmZoneFlg;                /* MmIeUnvrslTmAndLocalTmZone 存在标识      */
    VOS_UINT8                       ucLsaIDFlg;                                 /* MmIeLsaID 存在标识                       */
    VOS_UINT8                       ucNWDyLitSavTmFlg;                          /* MmIeNWDyLitSavTm 存在标识                */
    VOS_UINT8                       ucReserved1;
    MM_IE_TIME_ZONE_TIME_STRU       MmIeUnvrslTmAndLocalTmZone;                 /* Universal time and local time zone       */
    MM_IE_LSA_ID_STRU               MmIeLsaID;                                  /* LSA Identity 10.5.3.11,目前未使用                   */
    MM_IE_DAYLIGHT_SAV_TIME_STRU    MmIeNWDyLitSavTm;                           /* Network Daylight Saving Time             */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-26, end */
}MM_MSG_MM_INFO_STRU;

/* 9.2.16 MM Status */
typedef struct{
    MM_IE_REJECT_CAUSE_STRU     MmIeRjctCause;                                  /* Reject cause 10.5.3.6                    */
}MM_MSG_MM_STATUS_STRU;

/* 9.2.17 TMSI reallocation command */
typedef struct{
    MM_IE_LAI_STRU              MmIeLAI;                                        /* Location area identification 10.5.1.3    */
    MM_IE_MOBILE_ID_STRU        MmIeMobileId;                                   /* Mobile Identity 10.5.1.4                 */
}MM_MSG_TMSI_REALLOC_CMD_STRU;


/* 9.1.25 IN 04.18 Paging response */
typedef struct{
/*  MM_MSG_HEADER_STRU          MmMsgHeader;                   */               /* MM Message Header                        */
    MM_IE_CKSN_STRU             MmIeCksn;                                       /* Ciphering Key Sequence Number 10.5.1.2   */
    MM_IE_MOBILE_ID_STRU        MmIeMobileId;                                   /* Mobile Identity 10.5.1.4                 */
}MM_MSG_PAGING_RSP_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
