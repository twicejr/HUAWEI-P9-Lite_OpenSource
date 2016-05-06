/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : SNInterface.h
  Version     : V200R001
  Date        : 2005-06-16
  Description : 该头文件定义了SNDCP模块对外接口
  History     :
  1. Date:2005-06-16
     Author: w29695
     Modification:Create
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
*******************************************************************************/
#ifndef __SN_INTERFACE_H__
#define __SN_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#include "vos.h"
#include "TTFCause.h"
#include "TTFMem.h"

/*******************************************************************************
宏定义
*******************************************************************************/
#define ID_SN_XID_REQ                   0x0101
#define ID_SN_XID_RSP                   0x0102
#define ID_SN_XID_IND                   0x0103
#define ID_SN_XID_CNF                   0x0104

#define ID_SN_DATA_REQ                  0x0110
#define ID_SN_DATA_IND                  0x0111  /*目前NAS架构优化后，暂不使用该消息类型*/
#define ID_SN_UNITDATA_REQ              0x0112
#define ID_SN_UNITDATA_IND              0x0113  /*目前NAS架构优化后，暂不使用该消息类型*/

#define ID_SM_ACT_IND                   0x0121
#define ID_SM_ACT_RSP                   0x0122
#define ID_SM_DEACT_IND                 0x0123
#define ID_SM_DEACT_RSP                 0x0124
#define ID_SM_MODIFY_IND                0x0125
#define ID_SM_MODIFY_RSP                0x0126
#define ID_SN_RABM_SEQUENCE_IND         0x0127
#define ID_SN_RABM_SEQUENCE_RSP         0x0128

#define ID_SM_STATUS_REQ                0x0130

#define ID_RABM_SNDCP_SAVE_DATA_IND     0x0140
#define ID_RABM_SNDCP_SAVE_DATA_RSP     0x0141
#define ID_RABM_SNDCP_RESUME_DATA_IND   0x0142
#define ID_RABM_SNDCP_RESUME_DATA_RSP   0x0143

#define ID_SN_RESUME_ABM_IND            0x0144 /* GTTF模块内部使用的消息*/

/*******************************************************************************
结构定义
*******************************************************************************/
#pragma pack(4)

/* SN_DATA_REQ_ST为NAS用户面架构优化前的函数中使用的结构，在架构优化后的PS域
不再使用，但由于该函数被GCF测试时所需的一个AT命令(AT^TRIG)所使用，故仍旧保留*/
typedef struct
{
    /*0         Escape mechanism for future extensions.
    1           Point-to-Multipoint Multicast (PTM-M) information for Multimedia Broadcast/Multicast Service (MBMS).
    2-4         Reserved for future use.
    5-15        Dynamically allocated NSAPI value (see subclause 6.1).*/
    VOS_UINT8       ucNsapi;
#define SN_DATA_REQ_MASK_PDU            0x80
    VOS_UINT8       ucMask;                     /*b0000000  b为0:无pdu number, 1:有*/
    VOS_UINT16      usRsv;                      /*四字节补齐*/
    VOS_UINT16      usPduNum;                   /*N PDU number - acknowledged mode:    0-255    N PDU number - unacknowledged mode:    0-4095*/
    VOS_UINT16      usDataLen;                  /*NDPU的数据长度*/
    void           *pPdu;
}SN_DATA_REQ_ST;

typedef struct
{
    VOS_UINT8       ucNsapi;
    VOS_UINT8       ucRsv;                      /*四字节补齐*/
    VOS_UINT16      usDataLen;
    void           *pPdu;
}SN_UNITDATA_REQ_ST;


typedef struct
{
#define SN_XID_PARA_P_CMPR              0x80
#define SN_XID_PARA_D_CMPR              0x40

#define SN_1144_ALGRTH                  0
#define SN_2507_ALGRTH                  1
#define SN_ROHC_ALGRTH                  2

#define SN_V42_ALGRTH                   0
#define SN_V44_ALGRTH                   1

    VOS_UINT8       ucMask;                     /*0表示没有，1表示有    bit7表示协议压缩参数    bit6表示数据压缩参数*/
    VOS_UINT8       ucPCmprAlgrth;              /*RFC 1144  0    RFC 2507    1    ROHC        2*/
    VOS_UINT8       ucDCmprAlgrth;              /*V.42 bis  0      V.44      1*/
    VOS_UINT8       ucRsv;                      /*四字节补齐*/
}SN_XID_REQ_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;
    VOS_UINT16      usPId;                      /*即ucNsapi;范围与意义见SN_DATA_REQ_ST中的说明    该字段在消息中以子进程表示*/
    SN_XID_REQ_ST   stXid;
}SN_XID_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;
    VOS_UINT16      usPId;                      /*即ucNsapi;范围与意义见SN_DATA_REQ_ST中的说明    该字段在消息中以子进程表示*/
    SN_XID_REQ_ST   stXid;
}SN_XID_RSP_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;
    VOS_UINT16      usPId;                      /*即ucNsapi;范围与意义见SN_DATA_REQ_ST中的说明    该字段在消息中以子进程表示*/
    SN_XID_REQ_ST   stXid;
}SN_XID_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;
    VOS_UINT16      usPId;                      /*即ucNsapi;范围与意义见SN_DATA_REQ_ST中的说明    该字段在消息中以子进程表示*/
    SN_XID_REQ_ST   stXid;
}SN_XID_CNF_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usMsgType;                          /*消息类型*/
    VOS_UINT16  usPId;                              /*NSAPI 子进程标识,用于定位子进程*/
    VOS_UINT16  usPduLen;
    VOS_UINT16  usRsv;
    TTF_MEM_ST *pMemPt;                             /*分配的内存指针*/
}SN_UNITDATA_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usMsgType;
    VOS_UINT16  usPId;                              /*NSAPI 子进程标识,用于定位子进程*/
    VOS_UINT8   ucMask;
    VOS_UINT8   ucRsv;
    VOS_UINT16  usPduNum;
    VOS_UINT16  usPduLen;
    VOS_UINT16  usRsv;
    TTF_MEM_ST *pMemPt;                             /*分配的内存指针*/
}SN_DATA_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;      /*消息类型*/
    VOS_UINT16      usTransId;      
} SN_RESUME_ABM_IND_MSG;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*******************************************************************************
向外提供的函数声明
*******************************************************************************/
VOS_UINT32 SN_DataReq       (SN_DATA_REQ_ST     *pData);    /*确认数据传输请求接口如果返回值不为VOS_OK，则表示没有发送成功*/
VOS_UINT32 SN_UnitDataReq   (SN_UNITDATA_REQ_ST *pData);    /*非确认数据传输请求接口如果返回值不为VOS_OK，则表示没有发送成功*/
VOS_VOID SN_RabmClear2G3Share(VOS_VOID);                            /*2G向3G切换发生异常时，RABM清除SNDCP与PDCP之间的NPDU共享全局变量*/
VOS_VOID SN_RabmClear3G2Share(VOS_VOID);                            /*3G向2G切换发生异常时，RABM清除SNDCP与PDCP之间的NPDU共享全局变量*/




/******************************************************************************/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


