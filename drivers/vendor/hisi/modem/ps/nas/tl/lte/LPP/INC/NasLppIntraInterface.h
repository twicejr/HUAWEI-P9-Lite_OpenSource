

#ifndef __NASLPPINTRAINTERFACE_H__
#define __NASLPPINTRAINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPSCommon.h"
#include    "NasLppPublic.h"
#include    "LppMtaInterface.h"
#include    "v_typdef.h"
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/


#define LPP_INTRA_MSG_HDR  0

/*封装写LPP DL消息头的宏*/
#define NAS_ETC_WRITE_LPP_MSG_HEAD(pstMsg, ulLppMsgID)\
                    (pstMsg)->enMsgName         = (ulLppMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_TC;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_LPP;


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : ETC_LPP_MSG_TYPE_ENUM
 枚举说明  : ETC与LPP消息类型
 作者      : lifuxin 00253982 2015-09-01 新开发
*****************************************************************************/
enum NAS_LPP_INTRA_MSG_ID_ENUM
{
    ID_NAS_LPP_INTRA_DATA_CNF           = 0,    /* _H2ASN_MsgChoice NAS_LPP_INTRA_DATA_CNF_STRU */

    ID_NAS_LPP_INTRA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LPP_INTRA_MSG_ID_ENUM_UINT32;

/*******************************************************************************
  结构名    :NAS_LPP_INTRA_DATA_CNF_STRU
  结构说明  :
  1.日    期   : 2015年07月06日
    作    者   : Xiaojun
    修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    NAS_LPP_INTRA_MSG_ID_ENUM_UINT32    ulMsgId;                /*_H2ASN_Skip*//* 消息 ID */

    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity;
    /*enRslt=NAS_LPP_CONN_MANAGE_FAIL时，不携带stLppMsgIdentiy，把所有在进行的transaction的流程都结束*/
    NAS_LPP_ERROR_CODE_ENUM_UINT32      enRslt;
    VOS_UINT32                          ulOpId;
}NAS_LPP_INTRA_DATA_CNF_STRU;


/*****************************************************************************
 5. STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : ETC_LPP_RESET_POSTION_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ETC跟LPP之间的复位辅助信息的逻辑
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    NAS_LPP_INTRA_MSG_ID_ENUM_UINT32    ulMsgId;                /*_H2ASN_Skip*//* 消息 ID */

    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity;
    VOS_UINT8                           aucMsgData[4];          /* 整条消息存储 */
}NAS_LPP_INTRA_MSG_STRU;

typedef struct
{
    NAS_LPP_INTRA_MSG_ID_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export NAS_LPP_INTRA_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_LPP_INTRA_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}LPP_INTRA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LPP_INTRA_MSG_DATA                     stMsgData;
}LppIntraInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

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

#endif /* end of EmmLppInterface.h */





