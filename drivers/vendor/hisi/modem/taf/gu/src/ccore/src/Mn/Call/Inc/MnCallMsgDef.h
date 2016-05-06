/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallMsgDef.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2006年12月1日
  最近修改   : 2006年12月1日
  功能描述   : 定义Call模块内部使用的空口消息结构和字段值
  函数列表   :
  修改历史   :
  1.日    期   : 2006年12月1日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2009年12月6日
    作    者   : h44270
    修改内容   : 问题单号:AT2D15311,增加手机支持的能力,半速率和AMR

  3.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/
#ifndef _CCA_MSG_DEF_H_
#define _CCA_MSG_DEF_H_

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#pragma pack(4)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*           IE 字段值定义 (24.008)                      */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* BC field values definition */
/* ext */
#define MN_CALL_BC_VAL_EXT_EXTEND       0
#define MN_CALL_BC_VAL_EXT_NO_EXT       1
/* Information transfer capability*/
#define MN_CALL_BC_VAL_ITC_SPEECH       0
#define MN_CALL_BC_VAL_ITC_UDI          1
#define MN_CALL_BC_VAL_ITC_3D1K         2
#define MN_CALL_BC_VAL_ITC_FAX          3
#define MN_CALL_BC_VAL_ITC_OTHER        5
#define MN_CALL_BC_VAL_ITC_AUX_SPEECH   6
/* Transfer mode */
#define MN_CALL_BC_VAL_TM_CIRCUIT       0
#define MN_CALL_BC_VAL_TM_PACKET        1
/* Coding standard */
#define MN_CALL_BC_VAL_CODSTD_GSM       0
/* Radio channel requirement */
#define MN_CALL_BC_VAL_RCR_FR_ONLY      1
#define MN_CALL_BC_VAL_RCR_DUAL_HR      2
#define MN_CALL_BC_VAL_RCR_DUAL_FR      3
/* Speech version indication */
#define MN_CALL_BC_VAL_SPH_VER_FR_1     0
#define MN_CALL_BC_VAL_SPH_VER_FR_2     2
#define MN_CALL_BC_VAL_SPH_VER_FR_3     4
#define MN_CALL_BC_VAL_SPH_VER_HR_1     1
/* #define MN_CALL_BC_VAL_SPH_VER_HR_3     3 */

/*modify by t55263 for nas*/
#define MN_CALL_BC_VAL_SPH_VER_HR_3     5
/*modify by t55263 for nas*/

#define MN_CALL_BC_VAL_SPH_VER_FR_5     8


#define MN_CALL_UMTS_CODEC_TYPE_AMR     (5)
#define MN_CALL_UMTS_CODEC_TYPE_AMR2    (6)
#define MN_CALL_UMTS_CODEC_TYPE_AMRWB   (10)




/* CTM */
#define MN_CALL_BC_VAL_CTM_N_SUPPORT    0
#define MN_CALL_BC_VAL_CTM_SUPPORT      1
/* Coding */
#define MN_CALL_BC_VAL_CODING_EXT_ITC   0
#define MN_CALL_BC_VAL_CODING_EXT_OTH   1
/* Establishment */
#define MN_CALL_BC_VAL_ESTABLI_DEMAND   0
/* NIRR */
#define MN_CALL_BC_VAL_NIRR_NO_MEAN     0
#define MN_CALL_BC_VAL_NIRR_6K          1
/* Configuration */
#define MN_CALL_BC_VAL_CONFIGUR_PTP     0
/* Duplex mode */
#define MN_CALL_BC_VAL_DUPLMOD_HALF     0
#define MN_CALL_BC_VAL_DUPLMOD_FULL     1
/* Structure */
#define MN_CALL_BC_VAL_STRUCT_SDU       0
#define MN_CALL_BC_VAL_STRUCT_UNSTRU    3
/* Compression */
#define MN_CALL_BC_VAL_COMP_NOT_ALLOW   0
#define MN_CALL_BC_VAL_COMP_ALLOW       1
/* Signalling accesss protocol */
#define MN_CALL_BC_VAL_SIGNAL_I440      1
#define MN_CALL_BC_VAL_SIGNAL_X32       6
/* Rate adaption */
#define MN_CALL_BC_VAL_RA_NO            0
#define MN_CALL_BC_VAL_RA_V110          1
#define MN_CALL_BC_VAL_RA_X31           2
#define MN_CALL_BC_VAL_RA_OTHER         3
/* Access identity */
#define MN_CALL_BC_VAL_ACCESS_ID_OCT    0
/* Other rate adaption */
#define MN_CALL_BC_VAL_ORA_V120         0
#define MN_CALL_BC_VAL_ORA_H223_245     1
#define MN_CALL_BC_VAL_ORA_PIAFS        2
/* Other ITC */
#define MN_CALL_BC_VAL_OTHITC_RDI       0
/* In band/Out band negotiation */
#define MN_CALL_BC_VAL_INBNEG_INB       0
#define MN_CALL_BC_VAL_INBNEG_OUTB      1
/* Assignor/Assignee */
#define MN_CALL_BC_VAL_DEF_ASSIGNEE     0
#define MN_CALL_BC_VAL_ASSIGNOR_ONLY    1
/* Logical link identifier negotiation */
#define MN_CALL_BC_VAL_LLI_DEFAULT      0
#define MN_CALL_BC_VAL_FULL_PROTO_NEG   1
/* Mode of operation */
#define MN_CALL_BC_VAL_BIT_TRANS_MODE   0
#define MN_CALL_BC_VAL_PROT_SENSI_MODE  1
/* Multiple frame establishment support */
#define MN_CALL_BC_VAL_MF_NSUPPT        0
#define MN_CALL_BC_VAL_MF_SUPPT         1
/* Rate adaption header/no header */
#define MN_CALL_BC_VAL_RA_HDR_N_INCLUD  0
#define MN_CALL_BC_VAL_RA_HDR_INCLUD    1
/* Synchronous/asynchronous */
#define MN_CALL_BC_VAL_SYNC             0
#define MN_CALL_BC_VAL_ASYNC            1
/* User information layer 1 protocol */
#define MN_CALL_BC_VAL_UIL1P_DEFAULT    0
/* Layer 1 indenetity */
#define MN_CALL_BC_VAL_L1_ID_OCT        1
/* User rate */
#define MN_CALL_BC_VAL_UR_300           1
#define MN_CALL_BC_VAL_UR_1K2           2
#define MN_CALL_BC_VAL_UR_2K4           3
#define MN_CALL_BC_VAL_UR_4K8           4
#define MN_CALL_BC_VAL_UR_9K6           5
#define MN_CALL_BC_VAL_UR_12K           6
/* Number of data bits */
#define MN_CALL_BC_VAL_NDB_7BIT         0
#define MN_CALL_BC_VAL_NDB_8BIT         1
/* Negotiation */
#define MN_CALL_BC_VAL_NEG_NO_IBN       0
/* Number of stop bits */
#define MN_CALL_BC_VAL_NSB_1BIT         0
#define MN_CALL_BC_VAL_NSB_2BIT         1
/* Parity information */
#define MN_CALL_BC_VAL_PARITY_ODD       0
#define MN_CALL_BC_VAL_PARITY_EVEN      2
#define MN_CALL_BC_VAL_PARITY_NONE      3
#define MN_CALL_BC_VAL_PARITY_FORCE_0   4
#define MN_CALL_BC_VAL_PARITY_FORCE_1   5
/* Network independent clock on Rx */
#define MN_CALL_BC_VAL_NICRX_N_SUPPT    0
#define MN_CALL_BC_VAL_NICRX_SUPPT      1
/* Network independent clock on Tx */
#define MN_CALL_BC_VAL_NICTX_N_SUPPT    0
#define MN_CALL_BC_VAL_NICTX_SUPPT      1
/* Intermediate rate */
#define MN_CALL_BC_VAL_IR_8K            2
#define MN_CALL_BC_VAL_IR_16K           3
/* Modem type */
#define MN_CALL_BC_VAL_MT_NONE          0
#define MN_CALL_BC_VAL_MT_V21           1
#define MN_CALL_BC_VAL_MT_V22           2
#define MN_CALL_BC_VAL_MT_V22BIS        3
#define MN_CALL_BC_VAL_MT_V26           5
#define MN_CALL_BC_VAL_MT_V32           6
#define MN_CALL_BC_VAL_MT_UNDEF         7
#define MN_CALL_BC_VAL_MT_AUTOBAUD      8
/* Connection element */
#define MN_CALL_BC_VAL_CE_T             0
#define MN_CALL_BC_VAL_CE_NT            1
#define MN_CALL_BC_VAL_CE_BOTH_T        2
#define MN_CALL_BC_VAL_CE_BOTH_NT       3
/* Fixed network user rate */
#define MN_CALL_BC_VAL_FNUR_NA          0
#define MN_CALL_BC_VAL_FNUR_9K6         1
#define MN_CALL_BC_VAL_FNUR_14K4        2
#define MN_CALL_BC_VAL_FNUR_19K2        3
#define MN_CALL_BC_VAL_FNUR_28K8        4
#define MN_CALL_BC_VAL_FNUR_38K4        5
#define MN_CALL_BC_VAL_FNUR_48K         6
#define MN_CALL_BC_VAL_FNUR_56K         7
#define MN_CALL_BC_VAL_FNUR_64K         8
#define MN_CALL_BC_VAL_FNUR_33K6        9
#define MN_CALL_BC_VAL_FNUR_32K         10
#define MN_CALL_BC_VAL_FNUR_31K2        11
/* Other modem type */
#define MN_CALL_BC_VAL_OMT_NONE         0
#define MN_CALL_BC_VAL_OMT_V34          2
/* Maximum number of traffic channels */
#define MN_CALL_BC_VAL_MTCH_1           0
#define MN_CALL_BC_VAL_MTCH_2           1
#define MN_CALL_BC_VAL_MTCH_3           2
#define MN_CALL_BC_VAL_MTCH_4           3
#define MN_CALL_BC_VAL_MTCH_5           4
#define MN_CALL_BC_VAL_MTCH_6           5
#define MN_CALL_BC_VAL_MTCH_7           6
#define MN_CALL_BC_VAL_MTCH_8           7
/* Acceptable channel codings */
#define MN_CALL_BC_VAL_ACC_14K4         8
#define MN_CALL_BC_VAL_ACC_9K6          2
#define MN_CALL_BC_VAL_ACC_4K8          1
/* Wanted air interface user rate */
#define MN_CALL_BC_VAL_WAIUR_NA         0
#define MN_CALL_BC_VAL_WAIUR_9K6        1
#define MN_CALL_BC_VAL_WAIUR_14K4       2
#define MN_CALL_BC_VAL_WAIUR_19K2       3
#define MN_CALL_BC_VAL_WAIUR_28K8       5
#define MN_CALL_BC_VAL_WAIUR_38K4       6
#define MN_CALL_BC_VAL_WAIUR_43K2       7
#define MN_CALL_BC_VAL_WAIUR_57K6       8
/* User initiated modification indication */
#define MN_CALL_BC_VAL_UIMI_NA          0
#define MN_CALL_BC_VAL_UIMI_1_TCH       1
#define MN_CALL_BC_VAL_UIMI_2_TCH       2
#define MN_CALL_BC_VAL_UIMI_3_TCH       3
#define MN_CALL_BC_VAL_UIMI_4_TCH       4
/* Channel coding asymmetry indication */
#define MN_CALL_BC_VAL_ASYM_CH_CODING   0
#define MN_CALL_BC_VAL_ASYM_DL_BIASED   2
#define MN_CALL_BC_VAL_ASYM_UL_BIASED   1
#define MN_CALL_BC_VAL_ASYM_UNUSED      3
/* Acceptable channel coding extended */
#define MN_CALL_BC_VAL_ACCEXT_28K8      4
#define MN_CALL_BC_VAL_ACCEXT_32K       2
#define MN_CALL_BC_VAL_ACCEXT_43K2      1
/* User information layer 2 protocol */
/*#define MN_CALL_BC_VAL_UIL2P_X25        6 */
#define MN_CALL_BC_VAL_UIL2P_DC1_DC3    8
/*#define MN_CALL_BC_VAL_UIL2P_VIDEOTEX   10*/
#define MN_CALL_BC_VAL_UIL2P_COPNOFLCT  12
/*define MN_CALL_BC_VAL_UIL2P_CAPI       13*/
/* Layer 2 identity */
#define MN_CALL_BC_VAL_L2_ID_OCT        2

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

#endif /* _CCA_MSG_DEF_H_ */


