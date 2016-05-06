/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LnasFtmInterface.h
  Description     : LnasFtmInterface.h header file
  History         :
     1.HANLUFENG 41410       2013-8-27     Draft Enact
     2.
******************************************************************************/

#ifndef __LNASFTMINTERFACE_H__
#define __LNASFTMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "omerrorlog.h"

#pragma  pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
 枚举名: NAS_LMM_ERR_LOG_CN_CAUSE_ENUM
 枚举说明:24301 9.9.3.9 LMM cause
*****************************************************************************/
enum    NAS_LMM_ERR_LOG_CN_CAUSE_ENUM
{
    NAS_OM_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS                          = 0x00000002,   /* IMSI unknown in HSS          */
    NAS_OM_LMM_CAUSE_ILLEGAL_UE                                   = 0x00000003,   /* Illegal UE                   */
    NAS_OM_LMM_CAUSE_IMSI_UNKNOWN_IN_VLR                          = 0x00000004,   /* IMSI unknown in VLR          */
    NAS_OM_LMM_CAUSE_IMEI_NOT_ACCEPTED                            = 0x00000005,   /* IMEI not accepted            */
    NAS_OM_LMM_CAUSE_ILLEGAL_ME                                   = 0x00000006,   /* Illegal ME                   */
    NAS_OM_LMM_CAUSE_EPS_SERV_NOT_ALLOW                           = 0x00000007,   /* EPS services not allowed     */
    NAS_OM_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW          = 0x00000008,   /* EPS services and non-EPSservices not allowed   */
    NAS_OM_LMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW                = 0x00000009,   /* MS identity cannot be derived by the network   */
    NAS_OM_LMM_CAUSE_EPS_IMPLICITLY_DETACHED                      = 0x0000000a,   /* Implicitly detached                            */
    NAS_OM_LMM_CAUSE_PLMN_NOT_ALLOW                               = 0x0000000b,   /* PLMN not allowed                               */
    NAS_OM_LMM_CAUSE_TA_NOT_ALLOW                                 = 0x0000000c,   /* Tracking  area not allowed                     */
    NAS_OM_LMM_CAUSE_ROAM_NOT_ALLOW                               = 0x0000000d,   /* Roaming not allowed in this tracking area      */
    NAS_OM_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN                   = 0x0000000e,   /* EPS services not allowed in this PLMN          */
    NAS_OM_LMM_CAUSE_NO_SUITABL_CELL                              = 0x0000000f,   /* No Suitable Cells In Location Area             */
    NAS_OM_LMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE                = 0x00000010,   /* MSC temporarily not reachable */
    NAS_OM_LMM_CAUSE_NETWORKFAILURE                               = 0x00000011,   /* Network failure               */
    NAS_OM_LMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE                      = 0x00000012,   /* CS domain not available       */
    NAS_OM_LMM_CAUSE_ESM_FAILURE                                  = 0x00000013,   /* ESM failure                   */
    NAS_OM_LMM_CAUSE_CONGESTION                                   = 0x00000016,   /* Congestion                    */
    NAS_OM_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG                  = 0x00000019,   /* Not authorized for this CSG   */
    NAS_OM_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN  = 0x00000023,   /* Requested service option not authorized in this PLMN */
    NAS_OM_LMM_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE                 = 0x00000027,   /* CS domain temporarily not available                  */
    NAS_OM_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED              = 0x00000028,   /* No EPS bearer context activated                      */
    NAS_OM_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG                   = 0x0000005f,   /* Semantically incorrect message                       */
    NAS_OM_LMM_CAUSE_INVALID_MANDATORY_INFORMATION                = 0x00000060,   /* Invalid mandatory information                        */
    NAS_OM_LMM_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT              = 0x00000061,   /* Message type non-existent or not implemented         */
    NAS_OM_LMM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT      = 0x00000063,   /* Information element non-existent or not implemented  */
    NAS_OM_LMM_CAUSE_MSG_NOT_COMPATIBLE_WITH_PROTOCOL_STATE       = 0x00000065,   /* Message not compatible with protocol state           */
    NAS_OM_LMM_CAUSE_BUTT
};

typedef VOS_UINT8 NAS_LMM_ERR_LOG_CN_CAUSE_ENUM_UINT8;
typedef VOS_UINT8 LMM_FTM_CN_CAUSE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : OM_EMM_MAIN_STATE_ENUM
 枚举说明  : EMM主状态
*****************************************************************************/
enum   EMM_FTM_MAIN_STATE_ENUM
{
    /*=================== EMM的主状态 ===================*/
    EMM_FTM_NULL                                = 0x0000,   /* 空状态           */
    EMM_FTM_DEREGISTERED                        = 0x0001,   /* DETACH状态       */
    EMM_FTM_REGISTERED_INITIATED                = 0x0002,   /* ATTACH过程中状态 */
    EMM_FTM_REGISTERED                          = 0x0003,   /* ATTACH状态       */
    EMM_FTM_DEREGISTERED_INITIATED              = 0x0004,   /* DETACH过程中状态 */
    EMM_FTM_TRACKING_AREA_UPDATING_INITIATED    = 0x0005,   /* TAU过程中状态    */
    EMM_FTM_SERVICE_REQUEST_INITIATED           = 0x0006,   /* SERVICE过程中状态*/
    EMM_FTM_STATE_BUTT
};
typedef VOS_UINT16 EMM_FTM_MAIN_STATE_ENUM_UINT16;



/*****************************************************************************
 枚举名    : OM_EMM_FTM_SUB_STATE_ENUM
 枚举说明  : EMM子状态
*****************************************************************************/
enum    EMM_FTM_SUB_STATE_ENUM
{

    /*=================== EMM的子状态 ===================*/
    EMM_FTM_SS_NULL                             = 0x0000,  /* 空子状态 */
    /*========== OM_EMM_MS_DEREG下的子状态 ==============*/
    EMM_FTM_DEREGISTERED_NORMAL_SERVICE         = 0x0001,  /* 未注册正常服务状态 */
    EMM_FTM_DEREGISTERED_LIMITED_SERVICE        = 0x0002,  /* 未注册限制服务状态 */
    EMM_FTM_DEREGISTERED_ATTEMPTING_TO_ATTACH   = 0x0003,  /* 未注册等待尝试ATTCH状态*/
    EMM_FTM_DEREGISTERED_PLMN_SEARCH            = 0x0004,  /* 未注册搜网状态 */
    EMM_FTM_DEREGISTERED_NO_IMSI                = 0x0005,  /* 未注册卡无效状态 */
    EMM_FTM_DEREGISTERED_ATTACH_NEEDED          = 0x0006,  /* 未注册需要尽快ATTACH状态 */
    EMM_FTM_DEREGISTERED_NO_CELL_AVAILABLE      = 0x0007,  /* 未注册没有可用小区状态 */

    /*========== OM_EMM_MS_REG下的子状态 ================*/
    EMM_FTM_REGISTERED_NORMAL_SERVICE           = 0x0011,  /* 注册正常服务状态 */
    EMM_FTM_REGISTERED_ATTEMPTING_TO_UPDATE     = 0x0012,  /* 注册等待尝试TA更新状态 */
    EMM_FTM_REGISTERED_LIMITED_SERVICE          = 0x0013,  /* 注册限制服务状态 */
    EMM_FTM_REGISTERED_PLMN_SEARCH              = 0x0014,  /* 注册搜网状态 */
    EMM_FTM_REGISTERED_UPDATE_NEEDED            = 0x0015,  /* 注册需要TA更新状态 */
    EMM_FTM_REGISTERED_NO_CELL_AVAILABLE        = 0x0016,  /* 注册没有可用小区状态 */
    EMM_FTM_REGISTERED_ATTEMPTING_TO_UPDATE_MM  = 0x0017,  /* 联合注册只注册成功EPS服务的状态 */
    EMM_FTM_REGISTERED_IMSI_DETACH_INITIATED    = 0x0018,  /* IMSI DETACH等待网络回复状态 */
    EMM_FTM_SS_BUTT
};
typedef VOS_UINT16  EMM_FTM_SUB_STATE_ENUM_UINT16;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*==============================================================================
结构名称    : NAS_LMM_FTM_GUTI_HEAD_STRU
结构说明    : 24.301 9.9.3.10  EPS mobile identity
              两个成员的结构如下:
              ----------------------------------------------------------
              (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
              ----------------------------------------------------------
                  Length of EPS mobile identity contents, UNIT is byte
              ----------------------------------------------------------
                  1     1      1      1  | OorE |  Type of identity
              ----------------------------------------------------------
==============================================================================*/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeToi;
    VOS_UINT8                           aucRsv[2];
}NAS_LMM_FTM_GUTI_HEAD_STRU;

/*****************************************************************************
结构名称    :NAS_LMM_FTM_PLMN_ID_STRU中
使用说明    :
    MCC, Mobile country code (aucPlmnId[0], aucPlmnId[1] bits 1 to 4)
    MNC, Mobile network code (aucPlmnId[2], aucPlmnId[1] bits 5 to 8).

    The coding of this field is the responsibility of each administration but BCD
    coding shall be used. The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA,
    Federal regulation mandates that a 3-digit MNC shall be used. However a network
    operator may decide to use only two digits in the MNC over the radio interface.
    In this case, bits 5 to 8 of octet 4 shall be coded as "1111". Mobile equipment
    shall accept MNC coded in such a way.

    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2            |           MCC digit 1
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3            |           MCC digit 3
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2            |           MNC digit 1
    ---------------------------------------------------------------------------

    AT命令：
    at+cops=1,2,"mcc digit 1, mcc digit 2, mcc digit 3, mnc digit 1, mnc digit 2, mnc

digit 3",2 :

    e.g.
    at+cops=1,2,"789456",2 :
    --------------------------------------------------------------------------------
    (mcc digit 1)|(mcc digit 2)|(mcc digit 3)|(mnc digit 1)|(mnc digit 2)|(mnc digit 3)
    --------------------------------------------------------------------------------
       7         |     8       |      9      |     4       |      5      |     6
    --------------------------------------------------------------------------------

    在aucPlmnId[3]中的存放格式:
    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2 = 8        |           MCC digit 1 = 7
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3 = 6        |           MCC digit 3 = 9
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2 = 5        |           MNC digit 1 = 4
    ---------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucRsv;
}NAS_LMM_FTM_PLMN_ID_STRU;



/*****************************************************************************
结构名称    :NAS_LMM_FTM_MME_GROUPID_STRU
使用说明    :NAS_LMM_FTM_MME_GROUPID_STRU的相关参数
协议描述的 各DIGIT与字节/位的关系如下:
    ----------------------------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ----------------------------------------------------------------------------------
                               GroupId
    ----------------------------------------------------------------------------------
                              GroupIdCnt
    ----------------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupId;
    VOS_UINT8                           ucGroupIdCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_LMM_FTM_MME_GROUPID_STRU;

/*****************************************************************************
结构名称    :NAS_LMM_FTM_MME_CODE_STRU
使用说明    :NAS_LMM_FTM_MME_CODE_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmeCode;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_FTM_MME_CODE_STRU;


/*****************************************************************************
结构名称    :NAS_LMM_FTM_MTMSI_STRU
使用说明    :NAS_LMM_FTM_MTMSI_STRU的相关参数
协议描述的 各DIGIT与字节/位的关系如下:
    ----------------------------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ----------------------------------------------------------------------------------
                               MTmsi
    ----------------------------------------------------------------------------------
    ......
    ----------------------------------------------------------------------------------
                             MTmsiCnt3
    ----------------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMTmsi;
    VOS_UINT8                           ucMTmsiCnt1;
    VOS_UINT8                           ucMTmsiCnt2;
    VOS_UINT8                           ucMTmsiCnt3;
}NAS_LMM_FTM_MTMSI_STRU;

/*****************************************************************************
 结构名称   : NAS_LMM_FTM_GUTI_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : GUTI相关参数数据结构
*****************************************************************************/
typedef struct
{
    NAS_LMM_FTM_PLMN_ID_STRU                 stPlmnId;
    NAS_LMM_FTM_MME_GROUPID_STRU             stMmeGroupId;
    NAS_LMM_FTM_MME_CODE_STRU                stMmeCode;
    NAS_LMM_FTM_MTMSI_STRU                   stMTmsi;
}NAS_LMM_FTM_GUTI_STRU;

/*****************************************************************************
 结构名称   : LMM_FTM_TAC_STRU
 协议表格   : 参照24.301  9.9.3.26
 ASN.1 描述 :
 结构说明   : TAC信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}LMM_FTM_TAC_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*================================LNAS ======================================*/
typedef struct
{
    /* AR: 注册成功的PLMN */
    NAS_LMM_FTM_PLMN_ID_STRU                stPlmnId;
    NAS_LMM_FTM_GUTI_STRU                   stGuti;
    /* 单位ms，参考函数 NAS_LMM_ModifyPtlTimer()的处理 */
    VOS_UINT32                              ulTimerLen3412;

}LMM_FTM_CN_INFO_STRU;

/*****************************************************************************
 结构名称   : LMM_FTM_STATE_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : EMM状态信息数据结构
*****************************************************************************/
typedef struct
{
    EMM_FTM_MAIN_STATE_ENUM_UINT16      ulLmmMainState;    /* EMM主状态 */
    EMM_FTM_SUB_STATE_ENUM_UINT16       ulLmmSubState;     /* EMM子状态 */

}LMM_FTM_STATE_STRU;

/*****************************************************************************
 结构名称   : LNAS_OM_FTM_REPROT_CONTENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : EMM工程信息数据结构
*****************************************************************************/
typedef struct
{
    NAS_LMM_FTM_PLMN_ID_STRU            stPlmnId;           /* PLMNID信息 */
    NAS_LMM_FTM_GUTI_STRU               stGuti;             /* GUTI信息 */
	/* 单位ms，参考函数 NAS_LMM_ModifyPtlTimer()的处理 */
    VOS_UINT32                          ulTimerLen3412;     /* T3412时长 */
    LMM_FTM_TAC_STRU                    stTac;              /* TAC信息 */
    LMM_FTM_STATE_STRU                  stEmmState;         /* EMM状态信息 */
    LMM_FTM_CN_CAUSE_ENUM_UINT8         ucEmmCnRejCause;    /* EMM拒绝原因 */
    VOS_UINT8                           aucRsv[3];          /* 保留 */

}LNAS_LMM_FTM_INFO_STRU;

/*****************************************************************************
 结构名称   : LNAS_OM_FTM_REPROT_CONTENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ESM工程信息数据结构
*****************************************************************************/
typedef struct
{
    /* 取值和含义见 24301 9.9.4.4 */
    VOS_UINT8                           ucEsmCause;    /* ESM拒绝原因 */
    VOS_UINT8                           aucRsv[3];     /* 保留 */

}LNAS_ESM_FTM_INFO_STRU;


/*****************************************************************************
 结构名称   : LNAS_OM_FTM_REPROT_CONTENT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 工程模式上报内容数据结构
*****************************************************************************/
typedef struct
{
    /* 子模块ID */
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    ulMsgModuleID;

    /* 00：主卡, 01：副卡 ,10/11:保留  */
    VOS_UINT16                          usModemId;

    VOS_UINT16                          usProjectID;
    VOS_UINT32                          ulLength;

    union
    {
        LNAS_LMM_FTM_INFO_STRU          stLmmFtmInfo;    /* EMM工程信息 */
        LNAS_ESM_FTM_INFO_STRU          stEsmFtmInfo;    /* ESM工程信息 */
    }u;

}LNAS_OM_FTM_REPROT_CONTENT_STRU;

typedef LNAS_OM_FTM_REPROT_CONTENT_STRU  LMM_OM_FTM_REPROT_CONTENT_STRU;
typedef LNAS_OM_FTM_REPROT_CONTENT_STRU  ESM_OM_FTM_REPROT_CONTENT_STRU;



/*****************************************************************************
 结构名称   : LNAS_OM_FTM_REPROT_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 工程模式上报数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* 工程模式上报的内容长度,如果ulRptlen为0,aucContent内容长度也为0 */
    LNAS_OM_FTM_REPROT_CONTENT_STRU     stLnasFtmContent;
}LNAS_OM_FTM_REPROT_IND_STRU;

typedef LNAS_OM_FTM_REPROT_IND_STRU  LMM_OM_FTM_REPROT_IND_STRU;
typedef LNAS_OM_FTM_REPROT_IND_STRU  ESM_OM_FTM_REPROT_IND_STRU;


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LnasMntnInterface.h */


