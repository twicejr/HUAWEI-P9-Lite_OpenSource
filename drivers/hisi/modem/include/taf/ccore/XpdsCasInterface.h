/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : XpdsCasInterface.h
  版 本 号   : 初稿
  作    者   : g00261581
  生成日期   : 2015年08月21日
  最近修改   :
  功能描述   : XPDS与CDMA接入层之间的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月21日
    作    者   : g00261581
    修改内容   : 创建文件

 ******************************************************************************/

#ifndef __XPDSCASINTERFACE_H__
#define __XPDSCASINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


#define  XPDS_CAS_MSG_TYPE_BASE                 (0x1000)            /* XPDS模块与CDMA接入层消息基数 */
#define  XPDS_CAS_MAX_NEIGHBOR_NUM              (50)                /* CDMA MAX NEIGHBOR SET NUM */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : XPDS_CAS_MSG_TYPE_ENUM
 结构说明  : 原语的usMsgName
 1.日    期   : 2015年08月22日
   作    者   : g00261581
   修改内容   : Cdma AGPS
*****************************************************************************/
enum XPDS_CAS_MSG_TYPE_ENUM
{

    ID_XPDS_CAS_REF_LOC_REQ                       = XPDS_CAS_MSG_TYPE_BASE + 0x1,  /* _H2ASN_MsgChoice XPDS_CAS_REF_LOC_REQ_STRU      */
    ID_CAS_XPDS_REF_LOC_CNF                       = XPDS_CAS_MSG_TYPE_BASE + 0x2,  /* _H2ASN_MsgChoice CAS_XPDS_REF_LOC_CNF_STRU      */
    ID_CAS_XPDS_REF_LOC_IND                       = XPDS_CAS_MSG_TYPE_BASE + 0x3,  /* _H2ASN_MsgChoice CAS_XPDS_REF_LOC_IND_STRU      */
    ID_XPDS_CAS_TIME_SYNC_REQ                     = XPDS_CAS_MSG_TYPE_BASE + 0x4,  /* _H2ASN_MsgChoice XPDS_CAS_TIME_SYNC_REQ_STRU      */
    ID_CAS_XPDS_TIME_SYNC_IND                     = XPDS_CAS_MSG_TYPE_BASE + 0x5,  /* _H2ASN_MsgChoice CAS_XPDS_TIME_SYNC_IND_STRU      */

    ID_XPDS_CAS_MSG_TYPE_BUTT
};
typedef VOS_UINT32 XPDS_CAS_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : XPDS_CAS_RESULT_ENUM
 结构说明  : XPDS模块与接入层间的结果码枚举

  1.日    期   : 2015年08月22日
    作    者   : g00261581
    修改内容   : Cdma AGPS
*****************************************************************************/
enum XPDS_CAS_RESULT_ENUM
{
    XPDS_CAS_RESULT_NO_ERROR                      = 0x000000,                     /* 消息处理正常 */
    XPDS_CAS_RESULT_ERROR,                                                        /* 消息处理出错 */

    XPDS_CAS_RESULT_BUTT
};
typedef VOS_UINT32 XPDS_CAS_RESULT_ENUM_UINT32;

enum XPDS_CAS_REF_LOC_RPT_TYPE_ENUM
{
    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START     = 0,                                /* start the ref loc report */
    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP      = 1,                                /* stop the ref loc report */
    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : XPDS_CAS_PILOT_MEAS_INFO_STRU
 结构说明  : XPDS start or stop the ref loc info report

  1.日    期   : 2015年6月23日
    作    者   : L00128652
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPilotPN;                           /**< 0~ 511 ,Pilot PN */
    VOS_INT16                           sPnStrength;                         /**< Strength */
    VOS_UINT32                          ulPnPhase;                           /**< PNOffset of the reference pilot,in unit of 1/16 chips */
} XPDS_CAS_PILOT_MEAS_INFO_STRU;

/*****************************************************************************
 结构名    : XPDS_CAS_REF_LOC_REQ_STRU
 结构说明  : XPDS start or stop the ref loc info report

  1.日    期   : 2015年6月23日
    作    者   : L00128652
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;                         /*_H2ASN_Skip*/
    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_UINT8    enRptType;                           /* 0: start,1:stop */
    VOS_UINT8                               aucReserved[3];
} XPDS_CAS_REF_LOC_REQ_STRU;

/*****************************************************************************
 结构名    : CAS_XPDS_REF_LOC_CNF_STRU
 结构说明  : XPDS start or stop the ref loc info report

  1.日    期   : 2015年6月23日
    作    者   : L00128652
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;                         /*_H2ASN_Skip*/
    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_UINT8    enRptType;                           /* 0: start,1:stop */
    VOS_UINT8                               aucReserved[1];
    VOS_UINT16                              usRefPn;
    XPDS_CAS_RESULT_ENUM_UINT32             enResult;
} CAS_XPDS_REF_LOC_CNF_STRU;

/*****************************************************************************
 结构名    : CAS_XPDS_REF_LOC_IND_STRU
 结构说明  :

  1.日    期   : 2015年6月23日
    作    者   : L00128652
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                         /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsRefTime;
    VOS_INT16                           sMsSysTimeOffset;
    VOS_UINT16                          usRefPN;                             /**< 0..511, PNOffset of the reference pilot */
    VOS_INT16                           sRefPnStrength;                      /**< Strength */
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usCdmaFreq;
    VOS_INT16                           sServFreqRssi;
    VOS_UINT16                          usPilotNum;
    VOS_UINT8                           aucReserved[2];
    XPDS_CAS_PILOT_MEAS_INFO_STRU       stPilotMeasInfo[XPDS_CAS_MAX_NEIGHBOR_NUM];
} CAS_XPDS_REF_LOC_IND_STRU;

/*****************************************************************************
 结构名    : XPDS_CAS_TIME_SYNC_REQ_STRU
 结构说明  :

  1.日    期   : 2015年6月23日
    作    者   : L00128652
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                         /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enForcePulse;
    VOS_UINT8                           aucReserved[3];
} XPDS_CAS_TIME_SYNC_REQ_STRU;

/*****************************************************************************
 结构名    : CAS_XPDS_TIME_SYNC_IND_STRU
 结构说明  :

  1.日    期   : 2015年6月23日
    作    者   : L00128652
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    XPDS_CAS_RESULT_ENUM_UINT32         enResult;
    VOS_UINT32                          aulPulseTime[2];
} CAS_XPDS_TIME_SYNC_IND_STRU;




/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    XPDS_CAS_MSG_TYPE_ENUM_UINT32       enMsgID;                                /*_H2ASN_MsgChoice_Export XPDS_CAS_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          XPDS_CAS_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}XPDS_CAS_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    XPDS_CAS_MSG_DATA                   stMsgData;
}XpdsCasInterface_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/

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

#endif /* end of XpdsCasInterface.h */

