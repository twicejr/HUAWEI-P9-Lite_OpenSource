
#ifndef __NAS_MTA_INTERFACE_H__
#define __NAS_MTA_INTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "AppNasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define MTA_LNAS_MSG_TYPE_BASE          (0x0100)                               /*MTA模块与LNAS模块的消息基数*/
#define LNAS_MTA_MSG_TYPE_BASE          (0x0200)                               /*LNAS模块与MTA模块的消息基数*/

#define MTA_MMC_MSG_TYPE_BASE          (0x0300)                               /* MTA模块与MMC模块的消息基数 */
#define MMC_MTA_MSG_TYPE_BASE          (0x0400)                               /* MMC模块与MTA模块的消息基数 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
 结构名称: NAS_MTA_MSG_TYPE_ENUM_UINT32
 结构说明: MTA和NAS之间的原语
*****************************************************************************/
enum NAS_MTA_MSG_TYPE_ENUM
{
    ID_NAS_MTA_AREA_LOST_IND           = 0x0001,          /* _H2ASN_MsgChoice NAS_MTA_AREA_LOST_IND_STRU */

    ID_MTA_LNAS_SET_UE_CENTER_REQ      = MTA_LNAS_MSG_TYPE_BASE + 0x01,        /* _H2ASN_MsgChoice MTA_LNAS_SET_UE_CENTER_REQ_STRU */

    ID_LNAS_MTA_SET_UE_CENTER_CNF      = LNAS_MTA_MSG_TYPE_BASE + 0x01,        /* _H2ASN_MsgChoice LNAS_MTA_SET_UE_CENTER_CNF_STRU */

    ID_MTA_LNAS_QRY_UE_CENTER_REQ      = MTA_LNAS_MSG_TYPE_BASE + 0x02,        /* _H2ASN_MsgChoice MTA_LNAS_QRY_UE_CENTER_REQ_STRU */

    ID_LNAS_MTA_QRY_UE_CENTER_CNF      = LNAS_MTA_MSG_TYPE_BASE + 0x02,        /* _H2ASN_MsgChoice LNAS_MTA_QRY_UE_CENTER_CNF_STRU */
    ID_MTA_MMC_GET_NAS_CHR_INFO_REQ    = MTA_MMC_MSG_TYPE_BASE + 0x01,        /* _H2ASN_MsgChoice MTA_MMC_GET_NAS_INFO_REQ_STRU */

    ID_MMC_MTA_GET_NAS_CHR_INFO_CNF    = MMC_MTA_MSG_TYPE_BASE + 0x01,        /* _H2ASN_MsgChoice MMC_MTA_GET_NAS_INFO_CNF_STRU */

    ID_NAS_MTA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MTA_MSG_TYPE_ENUM_UINT32;


enum MTA_LMM_RESULT_ENUM
{
    MTA_LMM_RESULT_NO_ERROR                     = 0x000000,                     /* 消息处理正常 */
    MTA_LMM_RESULT_ERROR,                                                       /* 消息处理出错 */

    MTA_LMM_RESULT_BUTT
};
typedef VOS_UINT32 MTA_LMM_RESULT_ENUM_UINT32;

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
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/

    VOS_UINT8                                   aucRsv[4];                      /* 保留位 */
}NAS_MTA_AREA_LOST_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT32                                  ulOpId;
    LNAS_LMM_UE_CENTER_ENUM_UINT32              enUeCenter;
}MTA_LNAS_SET_UE_CENTER_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulRslt;                         /*0成功，1失败*/
}LNAS_MTA_SET_UE_CENTER_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           aucReserved[4];                         /* 保留位 */
} MTA_LNAS_QRY_UE_CENTER_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          enResult;                               /*查询操作结果*/
    VOS_UINT32                          enUeCenter;                             /*UE模式*/
} LNAS_MTA_QRY_UE_CENTER_CNF_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    NAS_MTA_MSG_TYPE_ENUM_UINT32        enMsgID;                                /*_H2ASN_MsgChoice_Export NAS_MTA_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_MTA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}NAS_MTA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_MTA_MSG_DATA                     stMsgData;
} NasMtaInterface_MSG;


typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           aucReserved[4];                 /* 保留位 */
} MTA_NAS_CHR_INFO_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT8                           ucIsExsitRrcConn;
    VOS_UINT8                           aucRsv[3];
} MMC_MTA_NAS_CHR_INFO_CNF_STRU;

/*****************************************************************************
  10 函数声明
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

#endif
