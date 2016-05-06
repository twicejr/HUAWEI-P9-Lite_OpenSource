

#ifndef __LCSLPPINTERFACE_H__
#define __LCSLPPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "LocCommonInterface.h"



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif



/*****************************************************************************
  2 Macro
*****************************************************************************/
#define PS_MSG_ID_LCS_TO_LPP_BASE 0
#define PS_MSG_ID_LPP_TO_LCS_BASE 100

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : LCS_LPP_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LCS与LPP之间的消息枚举
*****************************************************************************/
enum    LCS_LPP_MSG_ID_ENUM
{
    /* LCS发给LPP的消息原语 */
    ID_LCS_LPP_GNSS_ASSISTDATA_CNF      = 0x01+PS_MSG_ID_LCS_TO_LPP_BASE,       /* _H2ASN_MsgChoice LCS_LPP_GNSS_ASSISTDATA_CNF_STRU */
    ID_LCS_LPP_LOCATION_INFO_NTF        = 0x02+PS_MSG_ID_LCS_TO_LPP_BASE,       /* _H2ASN_MsgChoice LCS_LPP_LOCATION_INFO_NTF_STRU */

    /* LPP发送给LCS的消息原语*/
    ID_LPP_LCS_GNSS_ASSISTDATA_REQ      = 0x01+PS_MSG_ID_LPP_TO_LCS_BASE,       /* _H2ASN_MsgChoice LPP_LCS_GNSS_ASSISTDATA_REQ_STRU */

    ID_LCS_LPP_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 LCS_LPP_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : LCS_LPP_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LCS与LPP之间的结果美剧
*****************************************************************************/
enum    LCS_LPP_RSLT_ENUM
{
    LCS_LPP_RSLT_SUCC                   = 0,
    LCS_LPP_RSLT_FAIL                   = 1,

    LCS_LPP_RSLT_BUTT
};
typedef VOS_UINT32 LCS_LPP_RSLT_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名称: LPP_LCS_GNSS_ASSISTDATA_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LPP请求LCS获取GNSS辅助数据
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulLppMsgSize;
    VOS_UINT8                           aucLppMsg[4];       /* 消息的前四个字节内容 */
}LPP_LCS_GNSS_ASSISTDATA_REQ_STRU;

/*****************************************************************************
 结构名称: LCS_LPP_GNSS_ASSISTDATA_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    LCS_LPP_RSLT_ENUM_UINT32            enRslt;
}LCS_LPP_GNSS_ASSISTDATA_CNF_STRU;

/*****************************************************************************
 结构名称: LCS_LPP_LOCATION_INFO_NTF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpLocationEstimate   :1;
    VOS_UINT32                          bitOpVelocityEstimate   :1;
    VOS_UINT32                          bitOpSpare              :30;
    LOC_COM_COORDINATE_STRU             stLocationEstimate;             /* 位置信息 */
    LOC_COM_VELOCITY_STRU               stVelocityEstimate;             /* 速度信息 */
}LCS_LPP_LOCATION_INFO_NTF_STRU;



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

#endif /* end of LcsLppInterface.h */


