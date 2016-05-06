/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SsDef.h
  Description : 宏定义
  History     :
      1.  张志勇 2004.03.09   新版作成
*******************************************************************************/
#ifndef _SS_DEF_H_
#define _SS_DEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


/*******************************************************************************/
/**************************** 函数宏定义 ***************************************/
/*******************************************************************************/
#define  GET_MSG_TI(ti)             (((ti)>7)?  ((ti)-8):((ti)+8))

#define  Ss_MemSet(pBuf,Data,Len)   PS_NAS_MEM_SET(pBuf,Data,Len)                  /* 内存设置函数                             */
#define  Ss_MemCpy(pDst,pSrc,Len)   PS_NAS_MEM_CPY(pDst,pSrc,Len)                  /* 内存拷贝函数                             */

#define SS_ASN_ENCODER(msg_id,p_msg_data,msg_data_size,p_enc_data_adr,p_data_size,p_pad_bits)   \
    per_encoder_ss(                                                                             \
                    msg_id,          /* 入口消息ID（其宏值在per_interface.h中定义） */          \
                    p_msg_data,      /* 输入数据地址（待编码数据的头地址）          */          \
                    msg_data_size,   /* 输入数据长度（待编码数据的长度）            */          \
                    p_enc_data_adr,  /* 输出数据地址（编码后数据的头地址）          */          \
                    p_data_size,     /* 输出数据长度（编码后数据的byte数）          */          \
                    p_pad_bits )     /* padding的位数（bit数）                      */
#define SS_ASN_ENC_SIZE_CALC(msg_id,p_msg_data,msg_data_size,p_enc_data_adr,p_data_size)        \
    per_enc_size_calculation_ss(                                                                \
                    msg_id,          /* 入口消息ID（其宏值在per_interface.h中定义） */          \
                    p_msg_data,      /* 输入数据地址（待编码数据的头地址）          */          \
                    msg_data_size,   /* 输入数据长度（待编码数据的长度）            */          \
                    p_enc_data_adr,  /* 输出数据地址（编码后数据的头地址）          */          \
                    p_data_size )    /* 输出数据长度（编码后数据的byte数）          */
#define SS_ASN_DECODER(msg_id,p_msg_data,p_msg_data_size,p_dec_data_adr,data_size)              \
    per_decoder_ss(                                                                             \
                    msg_id,          /* 入口消息ID（其宏值在per_interface.h中定义） */          \
                    p_msg_data,      /* 输出数据地址（解码后数据的头地址）          */          \
                    p_msg_data_size, /* 输出数据长度（解码后数据的byte数）          */          \
                    p_dec_data_adr,  /* 输入数据地址（解码前数据的头地址）          */          \
                    data_size )      /* 输入数据长度（解码前数据byte数）            */
#define SS_ASN_DEC_SIZE_CALC(msg_id,p_msg_data,p_msg_data_size,p_dec_data_adr,data_size)        \
    per_dec_size_calculation_ss(                                                                \
                    msg_id,          /* 入口消息ID（其宏值在per_interface.h中定义） */          \
                    p_msg_data,      /* 输出数据地址（解码后数据的头地址）          */          \
                    p_msg_data_size, /* 输出数据长度（解码后数据的byte数）          */          \
                    p_dec_data_adr,  /* 输入数据地址（解码前数据的头地址）          */          \
                    data_size )      /* 输入数据长度（解码前数据byte数）            */
/*******************************************************************************/
/**************************** 常量宏定义 ***************************************/
/*******************************************************************************/

/*-----------------------------------------------------------------------------*/
/*----------------------------实体管理宏定义-----------------------------------*/
/*-----------------------------------------------------------------------------*/

#define SS_MAX_ENTITY_NUM               15                                      /* SS实体最大个数                           */
#define SS_M0_ENTITY_NUM                7                                       /* MO实体最大个数                           */
#define SS_MT_ENTITY_NUM                7                                       /* MT实体最大个数                           */
#define SS_NONE_TI                      16                                      /* 没找到TI                                 */
#define SS_NONE_TAFID                   0                                       /* 没找到TAF ID                             */
#define SS_NONE_CR                      0xff                                    /* 没找到CR                                 */
#define SS_MO_CR_NUM                    0x7f                                    /* MO过程中使用的CR数                       */
/*-----------------------------------------------------------------------------*/
/*----------------------------空口消息类型(24.080)-----------------------------*/
/*-----------------------------------------------------------------------------*/

/* 空口消息类型 */
#define  SS_MSG_REGISTER                0x3b                                    /* REGISTER                                 */
#define  SS_MSG_FACILITY                0x3a                                    /* FACILITY                                 */
#define  SS_MSG_RELCMPL                 0x2a                                    /* RELEASE COMPLETE                         */

/*-----------------------------------------------------------------------------*/
/*----------------------------空口消息中使用的IEI(24.080)----------------------*/
/*-----------------------------------------------------------------------------*/
#define  SS_IEINONE                     0x00                                    /* 无IEI                                    */
#define  SS_IEICAUSE                    0x08                                    /* Cause 域的IEI                            */
#define  SS_IEIFACILITY                 0x1C                                    /* Facility 域的IEI                         */
#define  SS_IEISSPVERSION               0x7F                                    /* SS version 域的IEI                       */
/*-----------------------------------------------------------------------------*/
/*----------------------------TAF-SS接口原语类型-------------------------------*/
/*-----------------------------------------------------------------------------*/
#define  MNSS_BEGIN_REQ                 D_SMC_BEGIN_REQ                         /* MNSS_BEGIN_REQ                           */
#define  MNSS_FACILITY_REQ              D_SMC_FACILITY_REQ                      /* MNSS_FACILITY_REQ                        */
#define  MNSS_END_REQ                   D_SMC_END_REQ                           /* MNSS_END_REQ                             */
#define  MNSS_BEGIN_IND                 D_SMC_BEGIN_IND                         /* MNSS_BEGIN_IND                           */
#define  MNSS_FACILITY_IND              D_SMC_FACILITY_IND                      /* MNSS_FACILITY_IND                        */
#define  MNSS_END_IND                   D_SMC_END_IND                           /* MNSS_END_IND                             */
#define  MNSS_SS_STATUS_NTY             SSA_SS_STATUS_NTY                       /* MNSS_SS_STATUS_NTY                       */

/*-----------------------------------------------------------------------------*/
/*----------------------------异常处理类型-------------------------------------*/
/*-----------------------------------------------------------------------------*/
#define  SS_ERROR_MSG                   0x00                                    /* 空口消息错                               */
#define  SS_ERROR_STATE                 0x01                                    /* 状态错                                   */
#define  SS_ERROR_TAFID                 0x02                                    /* TAF ID错                                 */
#define  SS_ERROR_ENCODE                0x03                                    /* 编码错                                   */
#define  SS_ERROR_DECODE                0x04                                    /* 解码错                                   */

/*-----------------------------------------------------------------------------*/
/*----------------------------TIMER类型----------------------------------------*/
/*-----------------------------------------------------------------------------*/
#define  SS_T551                        0xF0                                    /* T551                                     */
#define  SS_T551_LEN                    180                                     /* T551时长(秒)                             */
#define  SS_MAX_MSG_LEN                 256                                     /* SS消息最大长度                           */

/*-----------------------------------------------------------------------------*/
/*----------------------------Cause Value--------------------------------------*/
/*-----------------------------------------------------------------------------*/
#define  SS_CAUSE_NORMAL_CALL_CLEARING              0x10                        /* Normal Call Clearing */
#define  SS_CAUSE_NORMAL_UNSPECIFIED                0x9f
#define  SS_CAUSE_INVALID_TI_VALUE                  0xd1                          /* invalid transaction identifier value             */
#define  SS_CAUSE_MSG_TYPE_ERR_OR_NOT_IMPLEMENT     0xe1                          /* message type non-existent or not implemented     */
#define  SS_CAUSE_MSG_NOT_COMPATIBLE_STATUS         0xe2                          /* message type not compatible with protocol state  */
#define  SS_CAUSE_RECOVERY_TIMER_EXPIRY             0xe6                         /* Recovery on timer expiry                         */
#define  SS_CAUSE_INVALID_MANDATORY_IE              0xe0

#define  LCS_MM_IE_PD_LOCATION_SRVC                 (12)                        /* Location services                        */
#define  LCS_IEICAUSE                               (0x10)                      /* Cause 域的IEI                            */
#define  LCS_MSG_REGISTER                           (0x32)                      /* REGISTER                                 */
#define  LCS_MSG_RELCMPL                            (0x21)                      /* RELEASE COMPLETE                         */
#define  LCS_CAUSE_CODING_STANDARD_GSM              (0xE0)
#define  LCS_CAUSE_FACILITY_NOT_IMPLEMENTED         (0xC5)                      /* Requested facility not implemented       */

#define NAS_SS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI (0x08)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
