

#ifndef __MNMSGTS_H__
#define __MNMSGTS_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsLogdef.h"

#include "MnMsgApi.h"
/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "errorlog.h"
#include "msp_diag_comm.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "MnComm.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define MN_MSG_DAYS_IN_A_YEAR                               365
#define MN_MSG_DAYS_IN_A_MONTH                              30
#define MN_MSG_HOURS_IN_A_DAY                               24
#define MN_MSG_MINUTES_IN_AN_HOUR                           60
#define MN_MSG_MAX_RELAT_VP_DAYS                            441
#define MN_MSG_MONTHS_IN_A_YEAR                             12
#define MN_MSG_MAX_DAYS_IN_A_MONTH                          31
#define MN_MSG_SECONDS_IN_A_MINUTE                          60
#define MN_MSG_NEGATIVE_ALGEBRAICSIGN                       0x08

#define MN_MSG_MIN_ADDR_LEN                                 1
#define MN_MSG_MAX_ADDR_LEN                                 20
#define MN_MSG_MAX_RP_ADDR_LEN                              20

/*UDH associated mask begin */
#define MN_MSG_SMSCCTRL_TRANSACTION_CMPL_REPORT_MASK        0x01
#define MN_MSG_SMSCCTRL_PERMANENT_ERR_REPORT_MASK           0x02
#define MN_MSG_SMSCCTRL_TEMP_ERR_NOT_ATTEMPT_REPORT_MASK    0x04
#define MN_MSG_SMSCCTRL_TEMP_ERR_ATTEMPT_REPORT_MASK        0x08
#define MN_MSG_SMSCCTRL_DEACT_STATUS_REPORT_MASK            0x40
#define MN_MSG_SMSCCTRL_ORIGUDH_INCLUDE_MASK                0x80

#define MN_MSG_TP_MTI_MASK                                  3
#define MN_MSG_TP_PID_MASK                                  0x01
#define MN_MSG_TP_DCS_MASK                                  0x02
#define MN_MSG_TP_UDL_MASK                                  0x04

#define MN_MSG_UDH_LARGE_ANIM_SIZE                          128
#define MN_MSG_UDH_SMALL_ANIM_SIZE                          32

#define MN_MSG_UDH_CONCAT_8_IEL                             3
#define MN_MSG_UDH_CONCAT_16_IEL                            4
#define MN_MSG_UDH_SPECIAL_SM_IEL                           2
#define MN_MSG_UDH_APPPORT_8_IEL                            2
#define MN_MSG_UDH_APPPORT_16_IEL                           4
#define MN_MSG_UDH_TEXT_FORMATING_IEL                       4
#define MN_MSG_UDH_PRE_DEF_SOUND_IEL                        2
#define MN_MSG_UDH_PRE_DEF_ANIM_IEL                         2
/*MN_MSG_UDH_ANIM_SMALL_PIC_SIZE * MN_MSG_UDH_ANIM_LARGE_PIC_SIZE + 1*/
#define MN_MSG_UDH_LARGE_ANIM_IEL                           129
/*MN_MSG_UDH_ANIM_SMALL_PIC_SIZE * MN_MSG_UDH_ANIM_SMALL_PIC_SIZE + 1*/
#define MN_MSG_UDH_SMALL_ANIM_IEL                           33
#define MN_MSG_UDH_LARGE_PIC_IEL                            129
#define MN_MSG_UDH_SMALL_PIC_IEL                            33
#define MN_MSG_UDH_USER_PROMPT_IEL                          1
#define MN_MSG_UDH_RFC822_IEL                               1
#define MN_MSG_UDH_SMSCCTRL_IEL                             1
#define MN_MSG_UDH_SOURCE_IEL                               1
#define MN_MSG_UDH_REO_IEL                                  3
#define MN_MSG_UDH_HYPERLINK_FORMAT_IEL                     4
#define MN_MSG_UDH_OBJ_DISTR_IND_IEL                        2

#define MN_MSG_PIXELS_IN_A_OCTET                            8

#define MN_MSG_UDH_EO_HEADER_LEN                            7
#define MN_MSG_UDH_CC_HEADER_LEN                            3
#define MN_MSG_UDH_USER_DEF_SOUND_HEADER_LEN                1
#define MN_MSG_UDH_VAR_PIC_HEADER_LEN                       3
#define MN_MSG_UDH_WVG_HEADER_LEN                           1



/*****************************************************************************
  3 宏定义
*****************************************************************************/
/*23040 9.2.3.1 bits no 0 and 1 of the first octet of all PDUs*/
#define MSG_GET_TP_MTI(ucMti, ucFo)                         ((ucMti) = ((ucFo) & MN_MSG_TP_MTI_MASK))

#define MSG_GET_TP_RD(bFlag, ucFo)                          ((bFlag) = ((ucFo) & 0x04) ? VOS_TRUE : VOS_FALSE)
    /*23040 9.2.3.2 bit no 2 of the first octet of SMS DELIVER and SMS STATUS REPORT*/
#define MSG_GET_TP_MMS(bFlag, ucFo)                         ((bFlag) = ((ucFo) & 0x04) ? VOS_FALSE : VOS_TRUE)

    /*23040 9.2.3.26 bit no. 5 of the first octet of SMS STATUS REPORT*/
#define MSG_GET_TP_SRQ(bFlag, ucFo)                         ((bFlag) = ((ucFo) & 0x20) ? VOS_TRUE : VOS_FALSE)

    /*23040 9.2.3.4 bit no. 5 of the first octet of SMS DELIVER*/
#define MSG_GET_TP_SRI( bFlag, ucFo)                        ((bFlag) = ((ucFo) & 0x20) ? VOS_TRUE : VOS_FALSE)

    /*23040 9.2.3.5 bit no. 5 of the first octet of SMS SUBMIT and SMS COMMAND*/
#define MSG_GET_TP_SRR( bFlag, ucFo)                        ((bFlag) = ((ucFo) & 0x20) ? VOS_TRUE : VOS_FALSE)

#define MSG_GET_TP_UDHI( bFlag, ucFo)                       ((bFlag) = ((ucFo) & 0x40) ? VOS_TRUE : VOS_FALSE)

#define MSG_GET_TP_RP( bFlag, ucFo)                         ((bFlag) = ((ucFo) & 0x80) ? VOS_TRUE : VOS_FALSE)

    /*23040 9.2.3.3 bit no 3 and 4 of the first octet of SMS SUBMIT*/
#define MSG_GET_TP_VPF( ucVpf, ucFo)                        (ucVpf = (ucFo & 0x18) >> 3)

    /*23038 4 SMS Data Coding Scheme*/
#define MSG_GET_COMPRESSED(bFlag, ucDcs)                    ((bFlag) = ((ucDcs) & 0x20) ? VOS_TRUE : VOS_FALSE)

#define MSG_GET_MSGCLASS(ucClass, ucDcs )                   (ucClass = ((ucDcs) & 0x03))

#define MSG_GET_CHARSET(ucCharSet, ucDcs)                   (ucCharSet = ((ucDcs) >> 2) & 0x03)

#define MSG_GET_INDSENSE(bFlag, ucDcs)                      ((bFlag) = ((ucDcs) & 0x08 ) ? VOS_TRUE : VOS_FALSE)

#define MSG_GET_INDTYPE(ucIndType, ucDcs)                   ((ucIndType) = ((ucDcs) & 0x03))

#define MSG_GET_MSGCODING(ucMsgCoding, ucDcs)               ((ucMsgCoding) = (((ucDcs) >> 2) & 0x01))

#define MSG_GetObjFowardedFlag(bFlag, ucCtrldata)           ((bFlag) = (((ucCtrldata) & 0x01) ? VOS_TRUE : VOS_FALSE))

#define MSG_GetUserPromptInd(bFlag, ucCtrldata)             ((bFlag) = (((ucCtrldata) & 0x02) ? VOS_TRUE : VOS_FALSE))


#define MN_MSG_REVERSE_BCD(ucReversedBcd, ucBcd)   \
    (ucReversedBcd = (VOS_UINT8)((((ucBcd) << 4) & 0xf0) + (((ucBcd) >> 4) & 0x0f)))

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define MN_MSG_TS_PID                   WUEPS_PID_AT
#else
#define MN_MSG_TS_PID                   WUEPS_PID_TAF
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "AtMntn.h"
#define MN_INFO_LOG(str)                    TAF_LOG(WUEPS_PID_AT, 0, PS_LOG_LEVEL_INFO, str)
#define MN_NORM_LOG(str)                    TAF_LOG(WUEPS_PID_AT, 0, PS_LOG_LEVEL_NORMAL, str)
#define MN_WARN_LOG(str)                    TAF_LOG(WUEPS_PID_AT, 0, PS_LOG_LEVEL_WARNING, str)
#define MN_ERR_LOG(str)                     TAF_LOG(WUEPS_PID_AT, 0, PS_LOG_LEVEL_ERROR, str)

#define MN_INFO_LOG1(str, x1)               TAF_LOG1(WUEPS_PID_AT, 0, PS_LOG_LEVEL_INFO, str, x1)
#define MN_INFO_LOG2(str, x1, x2)           TAF_LOG2(WUEPS_PID_AT, 0, PS_LOG_LEVEL_INFO, str, x1, x2)
#define MN_INFO_LOG3(str, x1, x2, x3)       TAF_LOG3(WUEPS_PID_AT, 0, PS_LOG_LEVEL_INFO, str, x1, x2, x3)
#define MN_INFO_LOG4(str, x1, x2, x3, x4)   TAF_LOG4(WUEPS_PID_AT, 0, PS_LOG_LEVEL_INFO, str, x1, x2, x3, x4)

#define MN_NORM_LOG1(str, x)                TAF_LOG1(WUEPS_PID_AT, 0, PS_LOG_LEVEL_NORMAL, str, x)
#define MN_WARN_LOG1(str, x)                TAF_LOG1(WUEPS_PID_AT, 0, PS_LOG_LEVEL_WARNING, str, x)
#define MN_WARN_LOG2(str, x1,x2)            TAF_LOG2(WUEPS_PID_AT, 0, PS_LOG_LEVEL_WARNING, str,x1,x2)
#define MN_ERR_LOG1(str, x)                 TAF_LOG1(WUEPS_PID_AT, 0, PS_LOG_LEVEL_ERROR, str, x)
#endif


/*23040 9.2.3.1 bits no 0 and 1 of the first octet of all PDUs*/
#define MSG_SET_TP_MTI(ucFo, ucMti)                         ((ucFo) |= ((ucMti) & 0x03))
/*23040 9.2.3.25  1 bit field located within bit 2 of the first octet of SMS SUBMIT*/
#define MSG_SET_TP_RD(ucFo, bFlag)                          ((ucFo) |= (VOS_TRUE == (bFlag)) ? 0x04 : 0)
/*23040 9.2.3.2 bit no 2 of the first octet of SMS DELIVER and SMS STATUS REPORT*/
#define MSG_SET_TP_MMS(ucFo, bFlag)                         ((ucFo) |= (VOS_TRUE == (bFlag)) ? 0 : 0x04)
/*23040 9.2.3.3 bit no 3 and 4 of the first octet of SMS SUBMIT*/
#define MSG_SET_TP_VPF(ucFo, ucVpf)                         ((ucFo) |= (((ucVpf) << 3) & 0x18))
/*23040 9.2.3.26 bit no. 5 of the first octet of SMS STATUS REPORT*/
#define MSG_SET_TP_SRQ(ucFo, bFlag)                         ((ucFo) |= (VOS_TRUE == (bFlag)) ? 0x20 : 0)
/*23040 9.2.3.4 bit no. 5 of the first octet of SMS DELIVER*/
#define MSG_SET_TP_SRI(ucFo, bFlag)                         ((ucFo) |= (VOS_TRUE == (bFlag)) ? 0x20 : 0)
/*23040 9.2.3.5 bit no. 5 of the first octet of SMS SUBMIT and SMS COMMAND*/
#define MSG_SET_TP_SRR(ucFo, bFlag)                         ((ucFo) |= (VOS_TRUE == (bFlag)) ? 0x20 : 0)
/*23040 9.2.3.23 1 bit field within bit 6 of the first octet of SMS SUBMIT SMS-SUBMIT-REPORT SMS DELIVER,SMS-DELIVER-REPORT SMS-STATUS-REPORT SMS-COMMAND.*/
#define MSG_SET_TP_UDHI(ucFo, bFlag)                        ((ucFo) |= (VOS_TRUE == (bFlag))? 0x40 : 0)
/*23040 9.2.3.17 1 bit field, located within bit no 7 of the first octet of both SMS DELIVER and SMS SUBMIT,*/
#define MSG_SET_TP_RP(ucFo, bFlag)                          ((ucFo) |= (VOS_TRUE == (bFlag))? 0x80 : 0)
/*23038 4 Coding Group Bits 00xx
        SMS Data Coding Scheme indicates whether the text is uncompressed */
#define MSG_SET_COMPRESSED(ucDcs, bFlag)                    ((ucDcs) |= (VOS_TRUE == (bFlag)) ? 0x20 : 0)
/*23038 4 Coding Group Bits 00xx
        SMS Data Coding Scheme indicates whether the Message have a message class meaning*/
#define MSG_SET_CLASSFLAG(ucDcs, bFlag)                     ((ucDcs) |= (MN_MSG_MSG_CLASS_NONE == (bFlag)) ? 0 : 0x10)
/*23038 4 Coding Group Bits 00xx 1111
        SMS Data Coding Scheme Bit 1 Bit 0 indicates Message Class*/
#define MSG_SET_MSGCLASS(ucDcs, ucClass)                    ((ucDcs) |= ((ucClass) & 0x03))
/*23038 4 Coding Group Bits 00xx
        SMS Data Coding Scheme Bits 3 and 2 indicate the character set being used*/
#define MSG_SET_CHARSET(ucDcs, ucCharSet)                   ((ucDcs) |= ((ucCharSet) << 2) & 0x0C)
/*23038 4 Coding Group Bits 1101
        SMS Data Coding Scheme Bits 3 indicates Indication Sense*/
#define MSG_SET_INDSENSE(ucDcs, bFlag)                      ((ucDcs) |= (VOS_TRUE == (bFlag)) ? 0x08 : 0)
/*23038 4 Coding Group Bits 1101
        SMS Data Coding Scheme Bit 1 Bit 0 indicates Indication Type*/
#define MSG_SET_INDTYPE(ucDcs, ucIndType)                   ((ucDcs) |= ((ucIndType) & 0x03))
/*23038 4 Coding Group Bits 1111
        SMS Data Coding Scheme Bit 2 indicates Message coding*/
#define MSG_SET_MSGCODING(ucDcs, ucMsgCoding)               ((ucDcs) |= ((ucMsgCoding) << 2) & 0x04)

#define MSG_SetObjForwardedFlag(ucCtrlData, bFlag)          (ucCtrlData |= ((VOS_TRUE == bFlag)? 0x01 : 0x00))

#define MSG_SetUserPromptInd(ucCtrlData, bFlag)             (ucCtrlData |= ((VOS_TRUE == bFlag)? 0x02 : 0x00))


/*****************************************************************************
  4 接口函数声明
*****************************************************************************/

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted MN_UnPack7Bit */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/*****************************************************************************
 函 数 名  : MN_ChkNumType
 功能描述  : 同步函数,号码类型检查,参考协议23040 9.1.2.5
 输入参数  : enNumType      - 号码类型
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR号码类型检查通过 其他,号码类型检查失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年1月21日
    作    者   : fuyingjun
    修改内容   : 新生成函数
  2.日    期   : 2010年2月21日
    作    者   : f62575
    修改内容   : 问题单号：AT2D16979，UE侧不再检查地址的TON和NPI类型
*****************************************************************************/
TAF_UINT32 MN_ChkNumType(
    MN_MSG_TON_ENUM_U8                  enNumType
);

/*****************************************************************************
 函 数 名  : MN_ChkNumPlan
 功能描述  : 同步函数,拨号计划类型检查,参考协议23040 9.1.2.5
 输入参数  : enNumPlan - 拨号计划类型
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR拨号计划类型检查通过 其他,拨号计划类型检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月13日
    作    者   : fuyingjun
    修改内容   : 新生成函数
  2.日    期   : 2010年2月21日
    作    者   : f62575
    修改内容   : 问题单号：AT2D16717，UE侧不再检查地址的TON和NPI类型
*****************************************************************************/
TAF_UINT32 MN_ChkNumPlan(
    MN_MSG_NPI_ENUM_U8                  enNumPlan
);

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */





/*****************************************************************************
 函 数 名  : MN_MSG_Decode_UsimMsg
 功能描述  : 同步函数,将(U)SIM卡下发的短信TPDU码流转换成空口发送需要的TPDU码流
 输入参数  : pucData         - (U)SIM卡下发的短信TPDU码流
             ulLen           - (U)SIM卡下发的短信TPDU码流长度
 输出参数  : pstLongSubmit   - 根据(U)SIM卡下发的短信TPDU码流解码得到长短信数据结构
 返 回 值  : VOS_UINT32:函数返回的结果,成功以及失败的原因值
 调用函数  :
 被调函数  :

 修改历史      :
 12.日    期   : 2009年10月28日
    作    者   : f62575
    修改内容   : 新生成函数，AT2D15272, STK短信发送需要支持长短信的分段发送功能
*****************************************************************************/
VOS_UINT32 MN_MSG_Decode_UsimMsg(
    VOS_UINT8                           *pucData,
    VOS_UINT32                          ulLen,
    MN_MSG_SUBMIT_LONG_STRU             *pstLongSubmit
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetAddressFromSubmit
 功能描述  : 获取发送失败短信的目的号码和短信中心号码
 输入参数  : VOS_UINT8                          *pucRpduContent
             VOS_UINT32                          ulRpDataLen
             NAS_MNTN_BCD_ADDR_STRU             *pstScAddr,
             NAS_MNTN_BCD_ADDR_STRU             *pstDestAddr
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月19日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_GetAddressFromSubmit(
    VOS_UINT8                          *pucRpduContent,
    VOS_UINT32                          ulRpDataLen,
    NAS_MNTN_ASCII_ADDR_STRU           *pstScAddr,
    NAS_MNTN_ASCII_ADDR_STRU           *pstDestAddr
);


/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeTpRd
 功能描述  : 编码TP-RD参数到TP-FO
 输入参数  : VOS_BOOL                            bRejectDuplicates  TP-RD标志
 输出参数  : VOS_UINT8                          *pucTpFo            TP-FO
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : f62575
    修改内容   : DTS2012110604069 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_EncodeTpRd(
    VOS_BOOL                            bRejectDuplicates,
    VOS_UINT8                          *pucTpFo
);

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted MN_Pack7Bit */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MnMsgTs.h */

