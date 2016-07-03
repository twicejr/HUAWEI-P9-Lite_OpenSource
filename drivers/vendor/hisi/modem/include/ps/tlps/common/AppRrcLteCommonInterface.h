

#ifndef __APPRRCLTECOMMONINTERFACE_H__
#define __APPRRCLTECOMMONINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#define LMAX_NEIGHBOR_CELL_NUM    (16)
#ifndef VOS_MSG_HEADER
#define VOS_MSG_HEADER  VOS_UINT32 uwSenderCpuId;  \
                        VOS_UINT32 uwSenderPid;    \
                        VOS_UINT32 uwReceiverCpuId;\
                        VOS_UINT32 uwReceiverPid;  \
                        VOS_UINT32 uwLength;
#endif
#ifndef APP_MSG_HEADER
#define APP_MSG_HEADER                  VOS_UINT16   usOriginalId;\
                                        VOS_UINT16   usTerminalId;\
                                        VOS_UINT32   ulTimeStamp; \
                                        VOS_UINT32   ulSN;
#endif

enum RRC_OM_GET_CELL_INFO_FLAG_ENUM
{
    EN_GET_SERVICE_CELL_INFO = 0,
    EN_GET_NEIGHBOR_CELL_INFO = 1
};

typedef VOS_UINT32 RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32;


/*****************************************************************************
 结构名    : APP_LRRC_GET_NCELL_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议栈和APP间的接口消息的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                       /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32             ulOpId;
    RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32   enCellFlag;   /*=0标示获取服务小区，=1标示获取邻区*/
}APP_LRRC_GET_NCELL_INFO_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 服务小区或同频、异频小区测量结果结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPhyCellId;/* 小区id */
    VOS_INT16                           sRsrp;/* RSRP值 */
    VOS_INT16                           sRsrq;/* RSRq值 */
    VOS_INT16                           sRssi;/* RSSI值 */
}LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU;


/*****************************************************************************
 结构名    : LRRC_APP_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 服务小区或同频、异频小区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;/* 服务小区频点 */
    VOS_UINT16                          enBandInd;/* 频带指示 */
    LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU     stMeasRslt;
}LRRC_APP_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_APP_CELL_MEAS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 服务小区或同频、异频小区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32   ulNCellNumber;
    LRRC_APP_CELL_INFO_STRU stCellMeasInfo[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_CELL_MEAS_INFO_STRU;

typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_SRV_CELL_MEAS_INFO_STRU;
typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_INTRA_FREQ_NCELL_MEAS_INFO_STRU;
typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_INTER_FREQ_NCELL_MEAS_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_APP_BSIC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BSC信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usNcc;
    VOS_UINT16                                              usBcc;
}LRRC_APP_BSIC_INFO_STRU;
/*****************************************************************************
 结构名    : LRRC_GERAN_NCELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : L主模下，GSM 邻区信息
*****************************************************************************/

typedef struct
{
    VOS_UINT16    usArfcn;
    VOS_INT16     sRSSI;
    LRRC_APP_BSIC_INFO_STRU     stBSIC;
}LRRC_GERAN_NCELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_UMTS_NCELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : L主模下，UMTS邻区信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16    usARFCN;
    VOS_UINT16    usPrimaryScramCode;
    VOS_INT16     sCpichRscp;
    VOS_INT16     sCpichEcN0;
}LRRC_UMTS_NCELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : L主模下，UMTS邻区信息列表
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulNCellNumber;
    LRRC_UMTS_NCELL_INFO_STRU stUMTSNcellList[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU;


/*****************************************************************************
 结构名    : LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : L主模下，GSM 邻区信息列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulNCellNumber;
    LRRC_GERAN_NCELL_INFO_STRU stGeranNcellList[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU;


/*****************************************************************************
 结构名    : LRRC_APP_NCELL_LIST_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 服务小区的同频、异频以及异系统测量结果
*****************************************************************************/
typedef struct
{
    RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32      enCellFlag;   /*=0标示获取服务小区，=1标示获取邻区*/
    LRRC_APP_SRV_CELL_MEAS_INFO_STRU          stSevCellInfo; /*服务小区信息，包括频点、band、Phycial ID,RSRP,RSRQ,RSSI*/
    LRRC_APP_INTRA_FREQ_NCELL_MEAS_INFO_STRU  stIntraFreqNcellList;/* 同频邻区信息*/
    LRRC_APP_INTER_FREQ_NCELL_MEAS_INFO_STRU  stInterFreqNcellList;/* 异频邻区信息*/
    LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU    stInterRATUMTSNcellList; /* WCDMA/TDSCDMA异系统邻区*/
    LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU  stInterRATGeranNcellList; /* GERAN异系统邻区 */
}LRRC_APP_NCELL_LIST_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_APP_GET_NCELL_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 服务小区的同频、异频以及异系统邻区信息
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                       /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32             ulOpId;
    VOS_UINT32             enResult;
    LRRC_APP_NCELL_LIST_INFO_STRU stNcellListInfo;
}LRRC_APP_GET_NCELL_INFO_CNF_STRU;




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

#endif /* end of AppRrcInterface.h */
