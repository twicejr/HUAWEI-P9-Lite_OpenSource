/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaMtcInterface.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年1月23日
  最近修改   :
  功能描述   : MTC与CMMCA之间接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月23日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/


#ifndef __CMMCA_MTC_INTERFACE_H__
#define __CMMCA_MTC_INTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "CmmcaCmdComm.h"

#include "TafMtcApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CMMCA_MAX_EUTRA_NEIGHBOR_PLMN_NUM       (8)
#define CMMCA_MAX_ARFCN_NUM                     (8)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum CMMCA_MTC_MSG_TYPE_ENUM
{
    /* CMMCA->MTC CDMA MSG: */
    ID_CMMCA_MTC_OTHER_RAT_INFO_IND                         = 0x00,             /* _H2ASN_MsgChoice CMMCA_MTC_OTHER_RAT_INFO_IND_STRU */

    ID_CMMCA_MTC_MSG_TYPE_BUTT
};
typedef VOS_UINT32  CMMCA_MTC_MSG_TYPE_ENUM_UINT32;

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
/*****************************************************************************
 结构名    : CMMCA_OTHER_RAT_INFO_STRU
 结构说明  : CDMA发来的数据结构: LTE邻区信息

 1.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEarfcn;                               /* EUTRA channel number */
    /* priority of EARFCN of the neighbir EUTRA system. 0xff means not provided */
    VOS_UINT8                           ucEarfcnPri;
    /* Min required signal threshold used for selecting an EARFCN,
        The actual threshold value in dB used to compare against the measured reference signal receive Power(RSRP).*/
    VOS_UINT8                           ucThreshX;
    /* Min ref power level to select EUTRA, which in dBm is equal to the minimum
        reference signal received power(RSRP) level of a EUTRA cell required for the UE to reselect EUTRA.*/
    VOS_UINT16                          usRxLevMinEutra;
    /* Offset to min ref power level to select EUTRA. 0xff means not provided */
    VOS_UINT8                           ucRxLevMinEutraOffset;
    /* Max TX power level UE may use when transmitting up-link of EUTRA */
    VOS_UINT8                           ucPeMax;
    /* measurement bandwidth Nrb value, Table 7.1-1 */
    VOS_UINT8                           ucMeasBandWidth;
    VOS_UINT8                           ucNumPlmn;                              /* number of PLMN on this EARFCN channel */
    /* PLMN ID of the neighbor EUTRA system. 0xffffffff means not provided */
    VOS_UINT32                          aulPlmnId[CMMCA_MAX_EUTRA_NEIGHBOR_PLMN_NUM];
} CMMCA_OTHER_RAT_INFO_STRU;


/*****************************************************************************
 结构名    : CMMCA_OTHER_RAT_INFO_IND_STRU
 结构说明  : CDMA发来的数据结构: LTE邻区信息指示消息结构体

 1.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCmdId;
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId;
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT16                          usEarfcnListSize;
    VOS_UINT8                           aucReserved2[2];
    CMMCA_OTHER_RAT_INFO_STRU           astOtherRatInfo[CMMCA_MAX_ARFCN_NUM];
}CMMCA_OTHER_RAT_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CMMCA_MTC_OTHER_RAT_INFO_IND_STRU
 结构说明  : CMMCA发往MTC消息的结构
 1.日    期  : 2014年01月23日
   作    者  : g00261581
   修改内容  : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                 /*_H2ASN_Skip*/
    CMMCA_MTC_MSG_TYPE_ENUM_UINT32      enMsgId;   /*_H2ASN_Skip*/
    CMMCA_OTHER_RAT_INFO_IND_STRU       stOtherRatInfo;
}CMMCA_MTC_OTHER_RAT_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CMMCA_MTC_CDMA_STATE_INFO
 结构说明  : 外挂CDMA状态信息结构
 1.日    期  : 2014年09月29日
   作    者  : j00174725
   修改内容  : 新增
*****************************************************************************/
typedef struct
{
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState;
    TAF_MTC_POWER_STATE_ENUM_UINT8      enPowerState;
    TAF_MTC_CDMA_USIMM_CARD_ENUM_UINT8  enUsimmCardState;
}CMMCA_MTC_CDMA_STATE_INFO;



/*****************************************************************************
 结构名    : CMMCA_MTC_MSG_DATA
 结构说明  : CMMCA_MTC_MSG_DATA数据结构，用于生成ASN文件
 1.日    期  : 2014年01月23日
   作    者  : g00261581
   修改内容  : 新增
*****************************************************************************/
typedef struct
{
    CMMCA_MTC_MSG_TYPE_ENUM_UINT32      enMsgID;                                /*_H2ASN_MsgChoice_Export CMMCA_MTC_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
/***************************************************************************
_H2ASN_MsgChoice_When_Comment          CMMCA_MTC_MSG_TYPE_ENUM_UINT32
****************************************************************************/
}CMMCA_MTC_MSG_DATA;
/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : CmmcaMtcInterface_MSG
 结构说明  : CmmcaMtcInterface_MSG数据结构,用于生成ASN文件
 1.日    期  : 2014年01月23日
   作    者  : g00261581
   修改内容  : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CMMCA_MTC_MSG_DATA                  stMsgData;
}CmmcaMtcInterface_MSG;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


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

#endif /* end of CmmcaMtcInterface.h */

