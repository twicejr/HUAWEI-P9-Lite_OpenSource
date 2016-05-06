/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallBcproc.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2006年12月1日
  最近修改   : 2006年12月1日
  功能描述   : 定义CCA能力参数处理子模块的外部接口
  函数列表   :
  修改历史   :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年4月7日
    作    者   : zhoujun /z40661
    修改内容   : 可配置当前CODEC类型

  3.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting, 去掉BUTT后的逗号，避免编译WARNING
******************************************************************************/

#ifndef _CCA_CAPABILITY_H_
#define _CCA_CAPABILITY_H_

#include "vos.h"
#include "MnCallApi.h"
#include "NasCcIe.h"
#include "product_config.h"
#include "NasOmInterface.h"
#include "NasOmTrans.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/* +FCLASS命令设置的TA模式参数 */
enum MN_CALL_TA_MODE_ENUM
{
    MN_CALL_TA_MODE_DATA                = 0,                                    /* 数据模式 */
    MN_CALL_TA_MODE_FAX_CLASS1          = 1                                     /* Fax Class1 模式 */
};
typedef VOS_UINT8 MN_CALL_TA_MODE_ENUM_UINT8;


/* +CSNS命令设置的单号码方案模式参数 */
enum MN_CALL_SNS_MODE_ENUM
{
    MN_CALL_SNS_MODE_VOICE              = 0,
    MN_CALL_SNS_MODE_ALTER_VF_V_FIRST   = 1,
    MN_CALL_SNS_MODE_FAX                = 2,
    MN_CALL_SNS_MODE_DATA               = 4,
    MN_CALL_SNS_MODE_ALTER_VF_F_FIRST   = 5
};
typedef VOS_UINT8 MN_CALL_SNS_MODE_ENUM_UINT8;


/* +CBST的速率参数，参见27.007 */
enum MN_CALL_BST_SPEED_ENUM
{
    MN_CALL_BST_SPD_AUTOBAUD            = 0,
    MN_CALL_BST_SPD_300_V21             = 1,
    MN_CALL_BST_SPD_1K2_V22             = 2,
    MN_CALL_BST_SPD_2K4_V22BIS          = 4,
    MN_CALL_BST_SPD_2K4_V26TER          = 5,
    MN_CALL_BST_SPD_4K8_V32             = 6,
    MN_CALL_BST_SPD_9K6_V32             = 7,
    MN_CALL_BST_SPD_9K6_V34             = 12,
    MN_CALL_BST_SPD_14K4_V34            = 14,
    MN_CALL_BST_SPD_19K2_V34            = 15,
    MN_CALL_BST_SPD_28K8_V34            = 16,
    MN_CALL_BST_SPD_33K6_V34            = 17,
    MN_CALL_BST_SPD_1K2_V120            = 34,
    MN_CALL_BST_SPD_2K4_V120            = 36,
    MN_CALL_BST_SPD_4K8_V120            = 38,
    MN_CALL_BST_SPD_9K6_V120            = 39,
    MN_CALL_BST_SPD_14K4_V120           = 43,
    MN_CALL_BST_SPD_19K2_V120           = 47,
    MN_CALL_BST_SPD_28K8_V120           = 48,
    MN_CALL_BST_SPD_38K4_V120           = 49,
    MN_CALL_BST_SPD_48K_V120            = 50,
    MN_CALL_BST_SPD_56K_V120            = 51,
    MN_CALL_BST_SPD_300_V110            = 65,
    MN_CALL_BST_SPD_1K2_V110            = 66,
    MN_CALL_BST_SPD_2K4_V110            = 68,
    MN_CALL_BST_SPD_4K8_V110            = 70,
    MN_CALL_BST_SPD_9K6_V110            = 71,
    MN_CALL_BST_SPD_14K4_V110           = 75,
    MN_CALL_BST_SPD_19K2_V110           = 79,
    MN_CALL_BST_SPD_28K8_V110           = 80,
    MN_CALL_BST_SPD_38K4_V110           = 81,
    MN_CALL_BST_SPD_48K_V110            = 82,
    MN_CALL_BST_SPD_56K_FTM             = 83,
    MN_CALL_BST_SPD_64K_FTM             = 84,
    MN_CALL_BST_SPD_56K_BT              = 115,
    MN_CALL_BST_SPD_64K_BT              = 116,
    MN_CALL_BST_SPD_32K_PIAFS           = 120,
    MN_CALL_BST_SPD_64K_PIAFS           = 121,
    MN_CALL_BST_SPD_64K_MULTI           = 134
};
typedef VOS_UINT8 MN_CALL_BST_SPEED_ENUM_UINT8;



/* +CBST的连接要素参数，参见27.007 */
enum MN_CALL_BST_CE_ENUM
{
    MN_CALL_BST_CE_T                    = 0,
    MN_CALL_BST_CE_NT                   = 1,
    MN_CALL_BST_CE_BOTH_T               = 2,
    MN_CALL_BST_CE_BOTH_NT              = 3
};
typedef VOS_UINT8 MN_CALL_BST_CE_ENUM_UINT8;

/* 24.008 10.5.4.22 中的定义 */
enum MN_CALL_REP_IND_ENUM
{
    MN_CALL_REP_IND_NULL              = 0x00,                                   /* regard as invalid value */
    MN_CALL_REP_IND_ALTER             = 0x01,                                   /* mode 1 alternate mode 2 */
    MN_CALL_REP_IND_FALLBACK          = 0x02,                                   /* mode 1 preferred, mode 2 selected */
    MN_CALL_REP_IND_ALTER_1_PRFER     = 0x04
};
typedef VOS_UINT8  MN_CALL_REP_IND_ENUM_U8;

/*******************************************************************************
 结构名    :MN_CALL_SUPPORT_CODEC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前支持的codec类型,bit位置1表示该codec有效
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          CodecType_GSMFR         :1;
    VOS_UINT16                          CodecType_GSMHR         :1;
    VOS_UINT16                          CodecType_GSMEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMR      :1;
    VOS_UINT16                          CodecType_GSMHRAMR      :1;
    VOS_UINT16                          CodecType_UMTSAMR       :1;
    VOS_UINT16                          CodecType_UMTSAMR2      :1;
    VOS_UINT16                          CodecType_TDMAEFR       :1;
    VOS_UINT16                          CodecType_PDCEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMRWB    :1;
    VOS_UINT16                          CodecType_UMTSAMRWB     :1;
    VOS_UINT16                          CodecType_OHR_AMR       :1;
    VOS_UINT16                          CodecType_OFR_AMR_WB    :1;
    VOS_UINT16                          CodecType_OHR_AMR_WB    :1;
    VOS_UINT16                          BandSpare               :2;
}MN_CALL_SUPPORT_CODEC_STRU;

/*******************************************************************************
 结构名    :MN_CALL_SUPPORT_CODEC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前支持的codec类型,bit位置1表示该codec有效
*******************************************************************************/
typedef union
{
    MN_CALL_SUPPORT_CODEC_STRU          stSupportCodec;
    VOS_UINT16                          usSupportCodec;
}MN_CALL_SUPPORT_CODEC_UNION;




/*****************************************************************************
 函 数 名  : MN_CALL_CapaProcInit
 功能描述  : 初始化Capability Proc模块。主要是初始化语音编码版本列表和
             BC字段信息列表。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化的结果，VOS_OK表示初始化成功，VOS_ERROR表示初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_CapaProcInit(VOS_VOID);


/******************************************************************************
函数名  ：MN_CALL_BuildBcOfSetup
功能描述：构造SETUP消息中的BC参数
输入参数：enCallType - 本次呼叫的呼叫类型。如果呼叫模式不为single，则该参数为
                       第一个业务的类型。
           enCallMode - 本次呼叫的呼叫模式
           enTaMode   - 本次呼叫的TA模式，只对数据呼叫有效。
           pstBsType  - 本次呼叫的承载业务类型，只对数据呼叫有效。
输出参数：pstBc1 - 第一个业务的承载能力。
           pstBc2 - 第二个业务的承载能力，当呼叫模式不为single时，将输出该参数。
返回值  ：构造的BC参数的个数，可能的值为0、1、2，0表示构造失败。
*******************************************************************************/
VOS_UINT32  MN_CALL_BuildBcOfSetup(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstBsType,
    NAS_CC_IE_BC_STRU                   *pstBc1,
    NAS_CC_IE_BC_STRU                   *pstBc2
);


/******************************************************************************
函数名  ：MN_CALL_BcCompChk
功能描述：对BC参数进行兼容性检查。
输入参数：pstBc - 要检查的BC参数
输出参数：无
返回值  ：VOS_OK - 兼容性检查通过
           VOS_ERROR - 兼容性检查失败
*******************************************************************************/
VOS_UINT32  MN_CALL_BcCompChk(
    const NAS_CC_IE_BC_STRU             *pstBc
);


/******************************************************************************
函数名  ：MN_CALL_NegotBcForCallConf
功能描述：协商SETUP消息中的BC参数，得到CALL CONFIRM消息需要的BC参数。
输入参数：pstBsType - 当前设置的承载业务类型，当SETUP消息的呼叫类型为VOICE时该参数将被忽略。
           pstBc     - SETUP消息中的BC参数
输出参数：pstBc     - 协商后的BC参数
返回值  ：VOS_TRUE 表示CALL CONF消息中需要携带该BC参数；
           VOS_FALSE 表示CALL CONF消息中不需要携带该BC参数。
*******************************************************************************/
VOS_UINT32  MN_CALL_NegotBcForCallConf(
    NAS_CC_IE_BC_STRU                   *pstBc,
    NAS_CC_IE_BC_STRU                   *pstBcOfConf
);


/******************************************************************************
函数名  ：MN_CALL_BuildBcForSns
功能描述：构造单号码方案的BC参数
输入参数：enSnsMode - 当前设置的单号码方案模式
           pstBsType - 本次呼叫的承载业务类型，当单号码方案模式为VOICE时忽略该参数。
输出参数：pstBc1 - 第一个业务的BC参数
           pstBc2 - 第二个业务的BC参数
返回值  ：构造的BC参数的个数，可能的值为0、1、2，0表示构造失败。
*******************************************************************************/
VOS_UINT32  MN_CALL_BuildBcForSns(
    MN_CALL_SNS_MODE_ENUM_UINT8         enSnsMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfg,
    NAS_CC_IE_BC_STRU                   *pstBc1,
    NAS_CC_IE_BC_STRU                   *pstBc2,
    VOS_UINT8                           *pucBcRepInd
);

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */

VOS_UINT32 MN_CALL_ConfigGsmCapaProc(
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enCapaConfig
);

NAS_OM_GSM_CODEC_CONFIG_ENUM_U8  MN_CALL_ConvertSpeechVers(VOS_VOID );

NAS_OM_CURR_CODEC_TYPE_ENUM_U8  MN_CALL_ConvertMnCodecToOmCodec(
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType
);


VOS_VOID  MN_CALL_FillGsmSupCodecList(
    MN_CALL_SUPPORT_CODEC_UNION        *punCodecList
);



VOS_VOID  MN_CALL_FillUmtsSupCodecList(
    MN_CALL_SUPPORT_CODEC_UNION        *punCodecList
);


/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */

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

#endif /* _CCA_CAPABILITY_H_ */

