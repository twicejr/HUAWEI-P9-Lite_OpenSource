

#ifndef __CNAS_XREG_SNDINTERNALMSG_H__
#define __CNAS_XREG_SNDINTERNALMSG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "cas_1x_access_ctrl_proc_nas_pif.h"
#include  "CnasXregRegingProcTbl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum CNAS_XREG_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_XREG_XREG_REG_REQ                = 0x0000, /* _H2ASN_MsgChoice CNAS_XREG_XREG_REG_REQ_STRU*/
    ID_CNAS_XREG_XREG_REG_CNF                = 0x0001,
    ID_CNAS_XREG_ABORT_FSM_REQ               = 0x0002,
    ID_CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF     = 0x0003
};
typedef VOS_UINT16 CNAS_XREG_INTERNAL_MSG_TYPE_ENUM_UINT16;


enum CNAS_XREG_REG_RESULT_ENUM
{
    CNAS_XREG_REG_RESULT_SUCCESS                = 0x0000,
    CNAS_XREG_REG_RESULT_FAILURE                = 0x0001,
    CNAS_XREG_REG_RESULT_NORF                   = 0x0002,
    CNAS_XREG_REG_RESULT_PWROFF                 = 0x0003
};
typedef VOS_UINT32 CNAS_XREG_REG_RESULT_ENUM_UINT32;


enum CNAS_XREG_SWITCH_ON_RESULT_ENUM
{
    CNAS_XREG_SWITCH_ON_RESULT_SUCCESS          = 0x00000000,
    CNAS_XREG_SWITCH_ON_RESULT_FAILURE          = 0x00000001,
    CNAS_XREG_SWITCH_ON_RESULT_BUTT             = 0x00000002
};
typedef VOS_UINT32 CNAS_XREG_SWITCH_ON_RESULT_ENUM_UINT32;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XREG_INTERNAL_MSG_TYPE_ENUM_UINT16                 enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8                enRegType;
    VOS_UINT8                                               aucRsv[3];
}CNAS_XREG_XREG_REG_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XREG_INTERNAL_MSG_TYPE_ENUM_UINT16                 enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XREG_REG_RESULT_ENUM_UINT32                        enRegResult;
    CNAS_XREG_REGING_STA_ENUM_UINT32                        enRegingSta;
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8                enRegType;
    VOS_UINT8                                               aucRsv[3];
}CNAS_XREG_XREG_REG_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XREG_INTERNAL_MSG_TYPE_ENUM_UINT16                 enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
}CNAS_XREG_XREG_ABORT_FSM_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XREG_INTERNAL_MSG_TYPE_ENUM_UINT16                 enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XREG_SWITCH_ON_RESULT_ENUM_UINT32                  enRslt;
}CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_XREG_SndRegReqMsg(CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 enRegType);
VOS_VOID CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_ENUM_UINT32 enRegResult,
                                            CNAS_XREG_REGING_STA_ENUM_UINT32 enRegingSta,
                                            CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 enRegType);
VOS_VOID CNAS_XREG_SndAbortFsmMsg(VOS_VOID);

VOS_VOID CNAS_XREG_SndSwitchOnRlst(
    VOS_UINT32                          ulResult
);

#endif





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

#endif /* end of CnasXregSndInternalMsg.h */
