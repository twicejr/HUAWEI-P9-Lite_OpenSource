/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLcsOm.h
    Description : LCS的可谓可测
    History     :
            1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/


#ifndef __NASLCSOM_H__
#define __NASLCSOM_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "NasLcsPublic.h"
#include  "NasMmlCtx.h"
#include  "NasUtranCtrlInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_LCS_OM_MSG_ENUM
{
    ID_NAS_LCS_OM_ENTITY_STATE_INFO, /* _H2ASN_MsgChoice NAS_LCS_OM_ENTITY_STATE_INFO_STRU */
    ID_NAS_LCS_OM_CONN_STATE_INFO, /* _H2ASN_MsgChoice NAS_LCS_OM_CONN_STATE_INFO_STRU */
    ID_NAS_LCS_OM_TIMER_START,/* _H2ASN_MsgChoice NAS_LCS_OM_TIMER_START_STRU */
    ID_NAS_LCS_OM_TIMER_STOP,/* _H2ASN_MsgChoice NAS_LCS_OM_TIMER_STOP_STRU */
    ID_NAS_LCS_OM_TIMER_EXPIRE,/* _H2ASN_MsgChoice NAS_LCS_OM_TIMER_EXPIRE_STRU */
    ID_NAS_LCS_OM_NV_COMMON_CONFIG,/* _H2ASN_MsgChoice NAS_LPP_OM_NV_COMMON_CONFIG_STRU */
    ID_NAS_LCS_OM_DOMAIN_SELECT_INFO,/* _H2ASN_MsgChoice NAS_LPP_OM_NV_COMMON_CONFIG_STRU */
    ID_NAS_LCS_OM_ENITY_INFO,/* _H2ASN_MsgChoice NAS_LPP_OM_NV_COMMON_CONFIG_STRU */
    ID_NAS_LCS_OM_ENCODE_DBG_INFO,      /* _H2ASN_MsgChoice NAS_LCS_OM_ENCODE_DBG_INFO */
    ID_NAS_LCS_OM_DECODE_DBG_INFO,      /* _H2ASN_MsgChoice NAS_LCS_OM_DECODE_DBG_INFO */
    ID_NAS_LCS_OM_MSG_BUTT
};
typedef VOS_UINT32  NAS_LCS_OM_MSG_ENUM_UINT32;

/*****************************************************************************
 结构名称: NAS_LCS_CN_MSG_IE_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 编解码可维可测IE类型
*****************************************************************************/
enum NAS_LCS_CN_MSG_IE_TYPE_ENUM
{
    NAS_LCS_CN_MSG_IE_MSG_LEN               = 0,
    NAS_LCS_CN_MSG_IE_MSG_TYPE              = 1,
    NAS_LCS_CN_MSG_IE_FACILITY              = 2,
    NAS_LCS_CN_MSG_IE_CAUSE                 = 3,
    NAS_LCS_CN_MSG_IE_COMPONENT             = 4,
    NAS_LCS_CN_MSG_IE_RTN_RSLT              = 5,
    NAS_LCS_CN_MSG_IE_INVOKE                = 6,
    NAS_LCS_CN_MSG_IE_OPERA                 = 7,
    NAS_LCS_CN_MSG_IE_PARA                  = 8,
    NAS_LCS_CN_MSG_IE_LOC_POINT             = 9,
    NAS_LCS_CN_MSG_IE_LOC_ELLIPSE           = 10,
    NAS_LCS_CN_MSG_IE_LOC_ALIT_ELLI         = 11,
    NAS_LCS_CN_MSG_IE_LOC_ARC               = 12,
    NAS_LCS_CN_MSG_IE_LOC_ALT               = 13,
    NAS_LCS_CN_MSG_IE_LOC_POLYGON           = 14,
    NAS_LCS_CN_MSG_IE_LOC_ESTIMATE          = 15,
    NAS_LCS_CN_MSG_IE_ADD_LOC_EST           = 16,
    NAS_LCS_CN_MSG_IE_HOR_VEL               = 17,
    NAS_LCS_CN_MSG_IE_HOR_VER_VEL           = 18,
    NAS_LCS_CN_MSG_IE_HOR_VER_UNCERT        = 19,
    NAS_LCS_CN_MSG_IE_HOR_VER_VEL_UNCERT    = 20,
    NAS_LCS_CN_MSG_IE_VEL_ESTIMATE          = 21,
    NAS_LCS_CN_MSG_IE_HGMLC_ADDR            = 22,
    NAS_LCS_CN_MSG_IE_REP_PLMN_LIST         = 23,
    NAS_LCS_CN_MSG_IE_PLMN_LIST             = 24,
    NAS_LCS_CN_MSG_IE_PLMN                  = 25,
    NAS_LCS_CN_MSG_IE_ERROR_CODE            = 26,
    NAS_LCS_CN_MSG_IE_PROBLEM_CODE          = 27,
    NAS_LCS_CN_MSG_IE_OPERA_CODE            = 28,
    NAS_LCS_CN_MSG_LOC_NTF                  = 29,
    NAS_LCS_CN_MSG_LOC_TYPE                 = 30,
    NAS_LCS_CN_MSG_LOC_NTF_TYPE             = 31,
    NAS_LCS_CN_MSG_LOC_EST_TYPE             = 32,
    NAS_LCS_CN_MSG_LOC_REQUESTOR_ID         = 32,
    NAS_LCS_CN_MSG_LOC_DATA_CODE_SHM        = 33,
    NAS_LCS_CN_MSG_LOC_REQ_ID_STRING        = 34,
    NAS_LCS_CN_MSG_FORMAT_IND               = 35,
    NAS_LCS_CN_MSG_CODE_WORD                = 36,
    NAS_LCS_CN_MSG_CODE_WORD_STRING         = 37,
    NAS_LCS_CN_MSG_IE_SER_TYPE_ID           = 38,
    NAS_LCS_CN_MSG_IE_EXT_CLIENT_ID         = 39,
    NAS_LCS_CN_MSG_IE_EXT_ADDR              = 40,
    NAS_LCS_CN_MSG_IE_CLIENT_NAME           = 41,
    NAS_LCS_CN_MSG_IE_CLIENT_STRING         = 42,
    NAS_LCS_CN_MSG_IE_TAG                   = 43,
    NAS_LCS_CN_MSG_IE_LENGTH                = 44,
    NAS_LCS_CN_MSG_IE_LOC_CIRCLE            = 45,


    NAS_LCS_CN_MSG_IE_BUTT
};
typedef VOS_UINT8 NAS_LCS_CN_MSG_IE_TYPE_ENUM_UINT32;
/*****************************************************************************
 结构名称: NAS_LCS_DECODE_FAIL_CAUSE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 译码失败原因
*****************************************************************************/
enum NAS_LCS_DECODE_FAIL_CAUSE_ENUM
{
    NAS_LCS_MSG_TYPE_INVALID                = 0,
    NAS_LCS_LEN_INVAILID                    = 1,
    NAS_LCS_MISS_MANDATORY_IE               = 2,
    NAS_LCS_UNDECODE_LEN_INVAlID            = 3,
    NAS_LCS_CMPONENT_INVALID                = 4,
    NAS_LCS_UNKNOWN_OPER                    = 5,
    NAS_LCS_UNKNOWN_OP_IE                   = 6,
    NAS_LCS_POINT_NUM_INVALID               = 7,
    NAS_LCS_UNKNOWN_SHAPE_TYPE              = 8,
    NAS_LCS_UNKNOWN_VEL_TYPE                = 9,
    NAS_LCS_MISS_PLMN_ID                    = 10,
    NAS_LCS_MISS_INVOKE_ID                  = 11,
    NAS_LCS_TAG_ERROR                       = 12,
    NAS_LCS_LEN_DECODE_FAIL                 = 13,
    NAS_LCS_OPERA_INVALID                   = 14,
    NAS_LCS_VALUE_IVALID                    = 15,
    NAS_LCS_MISS_DATA_CODE_SCH              = 16,
    NAS_LCS_TAG_DECODE_FAIL                 = 17,
    NAS_LCS_VALUE_MEM_CPY_FAIL              = 18,

    NAS_LCS_DECODE_FAIL_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_LCS_DECODE_FAIL_CAUSE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_LCS_AIR_MSG_DIR_ENUM
 枚举说明  : 空口消息方向美剧
*****************************************************************************/
enum    NAS_LCS_AIR_MSG_DIR_ENUM
{
    NAS_LCS_AIR_MSG_DIR_ENUM_UP         = 0x00,
    NAS_LCS_AIR_MSG_DIR_ENUM_DOWN             ,

    NAS_LCS_AIR_MSG_DIR_BUTT
};
typedef VOS_UINT8   NAS_LCS_AIR_MSG_DIR_ENUM_UINT8 ;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*******************************************************************************
 结构名    : NAS_LCS_OM_ENTITY_STATE_INFO_STRU
 结构说明  : 实体状态的OM信息
 1.日    期   : 2015年10月14日
   作    者   : lihong00150010
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT32                          ulEntityIndex;

    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enOldEntityState;
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enNewEntityState;

    VOS_UINT8                           aucRsv[2];
}NAS_LCS_OM_ENTITY_STATE_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_LCS_OM_CONN_STATE_INFO_STRU
 结构说明  : 连接状态的OM信息
 1.日    期   : 2015年10月14日
   作    者   : lihong00150010
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT32                          ulEntityIndex;

    NAS_LCS_CONN_STATE_ENUM_UINT8       enOldConnState;
    NAS_LCS_CONN_STATE_ENUM_UINT8       enNewConnState;

    VOS_UINT8                           aucRsv[2];
}NAS_LCS_OM_CONN_STATE_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_LCS_OM_TIMER_START_STRU
 结构说明  : 定时器启动的om信息
 1.日    期   : 2015年10月14日
   作    者   : lihong00150010
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT32                          ulEntityIndex;
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usPara;
    VOS_UINT32                          ulTimerLen;
}NAS_LCS_OM_TIMER_START_STRU;

/*******************************************************************************
 结构名    : NAS_LCS_OM_TIMER_STOP_STRU
 结构说明  : 定时器停止的om信息
 1.日    期   : 2015年10月14日
   作    者   : lihong00150010
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT32                          ulEntityIndex;
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulRemainTime;
}NAS_LCS_OM_TIMER_STOP_STRU;

/*******************************************************************************
 结构名    : NAS_LCS_OM_TIMER_EXPIRE_STRU
 结构说明  : 定时器超时的om信息
 1.日    期   : 2015年10月14日
   作    者   : lihong00150010
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

   VOS_UINT32                           ulEntityIndex;
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usPara;
}NAS_LCS_OM_TIMER_EXPIRE_STRU;

/*******************************************************************************
 结构名    : NAS_LCS_OM_NV_COMMON_CONFIG_STRU
 结构说明  : LCS NV基本配置的OM信息
 1.日    期   : 2015年10月14日
   作    者   : lihong00150010
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    NAS_LCS_COMM_NV_PARA_STRU           stLcsNvCommConfig;
}NAS_LCS_OM_NV_COMMON_CONFIG_STRU;

/*******************************************************************************
 结构名    : NAS_LCS_OM_DOMAIN_SELECT_INFO_STRU
 结构说明  : 域选择的OM信息
 1.日    期   : 2015年10月15日
   作    者   : lihong00150010
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enSelectedDomain;
    VOS_UINT8                           ucHasExistEntity;/* 0表示没有，1表示存在 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    NAS_LCS_NW_CAP_INFO_STRU            stNwLcsCap;
    NAS_MML_UE_NETWORK_CAPABILITY_STRU  stUeNwCap;
    VOS_UINT8                           aucMsClassMark2[NAS_MML_CLASSMARK2_LEN];
}NAS_LCS_OM_DOMAIN_SELECT_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_LCS_OM_DECODE_DBG_INFO
 结构说明  : LCS译码失败可维可测
 1.日    期   : 2015年10月14日
   作    者   : leixiantiao 00258641
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;

    NAS_LCS_CN_MSG_IE_TYPE_ENUM_UINT32      enMsgIe;    /* 译码失败的IE */
    NAS_LCS_DECODE_FAIL_CAUSE_ENUM_UINT32   enCause;    /* 译码失败原因 */
    VOS_UINT32                              ulValue;    /* 判断失败的值 */
    VOS_UINT32                              ulPara;     /* 预留参数,如LEN不合标准时,该参数填LEN标准 */
}NAS_LCS_OM_DECODE_DBG_INFO;

/*******************************************************************************
 结构名    : NAS_LCS_OM_ENITY_INFO_STRU
 结构说明  : 实体的OM信息
 1.日    期   : 2015年10月16日
   作    者   : lihong00150010
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    NAS_LCS_NW_CAP_INFO_STRU            stNwLcsCap;                             /* 网侧LCS能力 */
    NAS_LCS_COMM_NV_PARA_STRU           stCommNvPara;                           /* LCS NV相关配置都保存到该成员中 */

    /* LCS实体记录,最多记录5条,第一个实体存储LPP触发的MO-LR,第二个实体存储TAF触发的MO-LR,
        第三个到第五个实体存储MT-LR */
    NAS_LCS_ENTITY_INFO_STRU            astLcsEntity[NAS_LCS_MAX_ENTITY_NUM];
    NAS_LCS_TAF_MSG_RECORD_STRU         stTafMsgRecord;                         /* 记录TAF给LCS的消息 */

    VOS_UINT8                           ucCurHandleId;
    VOS_UINT8                           ucCurInvokeId;
    VOS_UINT8                           ucMoTiUsedBit;
    VOS_UINT8                           ucRsv;
}NAS_LCS_OM_ENITY_INFO_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_CHAR                         g_acLcsPrintBuf[NAS_COMM_PRINT_BUFF_LEN];
#define NAS_COMM_GET_LCS_PRINT_BUF()    (g_acEsmPrintBuf)


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_LCS_SndOmEntityConnStateInfo
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_CONN_STATE_ENUM_UINT8       enOldConnState,
    NAS_LCS_CONN_STATE_ENUM_UINT8       enNewConnState
);
extern VOS_VOID  NAS_LCS_SndOmEntityStateInfo
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enOldEntityState,
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enNewEntityState
);
extern VOS_VOID  NAS_LCS_SndOmTimerStart
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType,
    VOS_UINT32                          ulTimerLen
);
extern VOS_VOID  NAS_LCS_SndOmTimerStop
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType,
    VOS_UINT32                          ulRemainTime
);
extern VOS_VOID  NAS_LCS_SndOmTimerExpire
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
);
extern VOS_VOID  NAS_LCS_SndOmNvCommonConfig( VOS_VOID );
extern VOS_VOID NAS_LCS_SndOmDecodeDbgInfo
(
    NAS_LCS_CN_MSG_IE_TYPE_ENUM_UINT32       enMsgIe,
    NAS_LCS_DECODE_FAIL_CAUSE_ENUM_UINT32    enCause,
    VOS_UINT32                               ulValue,
    VOS_UINT32                               ulPara
);
extern VOS_VOID  NAS_LCS_SndOmEntityInfo( VOS_VOID );
extern VOS_VOID NAS_LCS_SndAirMsgReportInd
(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLength,
    NAS_LCS_AIR_MSG_DIR_ENUM_UINT8      enMsgDir,
    OM_PS_AIR_MSG_ENUM_UINT8            enMsgId
);
extern VOS_VOID  NAS_LCS_SndOmDomainSelectInfo
(
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enSelectedDomain
);
extern VOS_VOID  NAS_LCS_SndOmEntityInfo( VOS_VOID );
extern VOS_VOID NAS_LCS_PrintLcsSendMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);
extern VOS_VOID NAS_LCS_PrintLcsRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

