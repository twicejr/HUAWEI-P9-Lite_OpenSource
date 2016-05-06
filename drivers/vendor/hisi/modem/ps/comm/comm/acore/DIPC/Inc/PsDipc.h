/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
#ifndef __PSDIPC_H__
#define __PSDIPC_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "AtDipcInterface.h"
#include    "ImmInterface.h"
#include    "AdsDeviceInterface.h"
#include    "mdrv.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DIPC_DEV_NUM                (DIPC_DEV_BUTT)       /* DIPC使用的设备端口数目 */

/* 可能出现的Rab个数，应该为[5,15],此处为了检索快速，直接定为[0，15] 16个，其中[0,4]为非法值  */
#define RAB_MAX_NUM                 (MAX_RAB_ID + 1)   

#define SERVICE_MAX_NUM             (6) /* 目前最多3个设备，每个设备目前最多2种SERVICE_ID */

#define DIPC_SERVICE_TYPE_MAX_NUM   (DIPC_SERVICE_TYPE_BUTT)

#define DIPC_DATA_MAX_DATA_LEN      (1536)    /* DIPC通道上单个数据包的长度上限 */

#define DIPC_IP_VER_IPV4            (4)
#define DIPC_IP_VER_IPV6            (6)

/* 检测该服务结构是否注册 */
#define DIPC_GET_SERVICE_STRU_USE(ulServiceMask, ucServiceNo)   (((ulServiceMask) & (1 << (ucServiceNo))) >> (ucServiceNo))

/* 设置对应的服务结构被使用 */
#define DIPC_SET_SERVICE_STRU_REG(ulServiceMask, ucServiceNo)   ((ulServiceMask) = ((ulServiceMask) | (1 << (ucServiceNo))))

/* 设置对应的服务结构未被使用 */
#define DIPC_CLR_SERVICE_STRU_REG(ulServiceMask, ucServiceNo)   ((ulServiceMask) = ((ulServiceMask) & (~((VOS_UINT32)(1 << (ucServiceNo))))))


/* 检测服务是否注册 */
#define DIPC_GET_SERVICE_REG(ulServerMask, enServiceType)   (((ulServerMask) & (1 << (enServiceType))) >> (enServiceType))

/* 设置服务对应的掩码被注册 */
#define DIPC_SET_SERVICE_REG(ulServerMask, enServiceType)   ((ulServerMask) = ((ulServerMask) | (1 << (enServiceType))))

/* 消除服务对应的掩码 */
#define DIPC_CLR_SERVICE_REG(ulServerMask, enServiceType)   ((ulServerMask) = ((ulServerMask) & (~((VOS_UINT32)(1 << (enServiceType))))))

/* 通过和AT之间的接口上使用的BearerType来找到服务类型 */
#define DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(enBearerType)  ((enBearerType) - 1)

#define DIPC_SET_APP(enDir, Para)   (((enDir) << 8) | (VOS_UINT8)Para)
#define DIPC_GET_DIR(App)           ((App) >> 8)
#define DIPC_GET_PARA(App)          ((App) & 0xff)

#define INVALID_RABID_VALUE             (0xFF)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*参照DrvInterface.h中UDI_DEVICE_ID对于UDI_ACM_HSIC_ACM1_ID/UDI_ACM_HSIC_ACM3_ID/UDI_ACM_HSIC_ACM5_ID
的定义，此处新增定义是为了便于检索*/
typedef enum
{
    DIPC_DEV_ID1    = 0,
    DIPC_DEV_ID2    = 1,
    DIPC_DEV_ID3    = 2,
    DIPC_DEV_BUTT
}DIPC_DEV_ID_ENUM;
typedef VOS_UINT32  DIPC_DEV_ID_ENUM_UINT32;

/* DIPC上支持的服务类型 */
typedef enum
{
    DIPC_SERVICE_TYPE_IPV4  = 0,
    DIPC_SERVICE_TYPE_IPV6  = 1,
    DIPC_SERVICE_TYPE_BUTT
}DIPC_SERVICE_TYPE_ENUM;
typedef VOS_UINT32  DIPC_SERVICE_TYPE_ENUM_UINT32;

/* 可维可测使用消息 */
typedef enum
{
    ID_DIPC_ADD_NEW_MAPPING_INFO_FAIL       = 0x0001,   /* 添加新的映射关系失败信息 */ 
    ID_DIPC_DEL_MAPPING_INFO_FAIL           = 0x0002,   /* 删除新的映射关系失败信息 */
    ID_DIPC_REG_ADS_DL_DATA_CALLBACK_FAIL   = 0x0003,   /* PDP激活时注册ADS下行回调函数失败 */
    ID_DIPC_DEREG_ADS_DL_DATA_CALLBACK_FAIL = 0x0004,   /* PDP去激活时去注册ADS下行回调函数失败 */
    ID_DIPC_PDP_ACT_SUCC                    = 0x0005,   /* PDP激活成功 */
    ID_DIPC_PDP_DEACT_SUCC                  = 0x0006,   /* PDP去激活成功 */
    ID_DIPC_SHOW_MAPPING_INFO               = 0x0007,   /* 手动要求显示映射关系信息 */
    ID_DIPC_TRACE_UL_DATA                   = 0x1001,   /* 上行数据勾包 */
    ID_DIPC_TRACE_DL_DATA                   = 0x1002,   /* 下行数据勾包 */
    ID_DIPC_TRACE_TYPE_BUTT
}DIPC_TRACE_MSG_TYPE_ENUM;
typedef VOS_UINT32 DIPC_TRACE_MSG_TYPE_ENUM_UINT32;

typedef VOS_UINT32 (*DIPC_SERV_ULDATA_CALLFUNC)(IMM_ZC_STRU *pData, VOS_UINT8 ucRabId);
typedef VOS_UINT32 (*DIPC_SERV_DLDATA_CALLFUNC)(DIPC_DEV_ID_ENUM_UINT32 enUdiDevId, IMM_ZC_STRU *pstBuf);
typedef VOS_UINT32 (*DIPC_SERV_ULDATA_MATCHFUNC)(IMM_ZC_STRU *pstBuf);
typedef VOS_UINT32 (*DIPC_SERV_DLDATA_MATCHFUNC)(IMM_ZC_STRU *pstBuf);

typedef enum
{
    ID_DIPC_UL_DATA,
    ID_DIPC_DL_DATA,
    ID_DIPC_DATA_BUTT
}DIPC_DATA_TYPE_ENUM;
typedef VOS_UINT16  DIPC_DATA_TYPE_ENUM_UINT16;

enum ID_DIPC_MSG_TYPE_ENUM
{
    ID_DIPC_DATA_NOTIFY_REQ
};
typedef VOS_UINT32  ID_DIPC_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                              /* 消息头 */     
    ID_DIPC_MSG_TYPE_ENUM_UINT32    enMsgType;  /* 消息类型 */   
}DIPC_DATA_PROC_NOTIFY_MSG;

/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*TTF 类型类型为32位的消息解析用共用消息头*/
typedef struct
{
    VOS_MSG_HEADER                      /* 消息头 */
    VOS_UINT32 ulMsgType;               /* 消息类型 */
}TTF_U32MSG_COMM_HEAD_STRU;

/*勾包消息*/
typedef struct
{
    VOS_MSG_HEADER
    DIPC_TRACE_MSG_TYPE_ENUM_UINT32     enMsgType;
    DIPC_DEV_ID_ENUM_UINT32             enDevId;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[DIPC_DATA_MAX_DATA_LEN];
} TRACE_UL_DIPC_DATA_MSG;

typedef struct
{
    VOS_MSG_HEADER
    DIPC_TRACE_MSG_TYPE_ENUM_UINT32     enMsgType;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[DIPC_DATA_MAX_DATA_LEN];
} TRACE_DL_DIPC_DATA_MSG;

typedef struct
{
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceType;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv[3];   
}DIPC_DEV_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    DIPC_TRACE_MSG_TYPE_ENUM_UINT32     enMsgType;
    DIPC_DEV_INFO_STRU                  astDipcDevData[DIPC_DEV_NUM];     
}DIPC_DEV_SUITE_INFO_MSG;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* 记录设备的信息 */
typedef struct
{
    UDI_DEVICE_ID_E             enUdiDevId;     /* 底软实际和DIPC一起使用的设备ID */
    UDI_HANDLE                  slUdiHsicHdl;   /* 设备对应的句柄 */

    VOS_UINT32  (*pTxFunc)(UDI_HANDLE ulhandle, IMM_ZC_STRU *pstBuf); /* 数据发送函数指针 */
    
    union
    {
        VOS_UINT32  (*pAcmRxFunc)(VOS_VOID);                                /* ACM下该句柄上报数据时调用的回调函数指针 */
        VOS_UINT32  (*pNcmRxFunc)(UDI_HANDLE ulhandle, VOS_VOID *pPktNode); /* NCM下该句柄上报数据时调用的回调函数指针 */
    }pRxFunc;
}DEV_INFO_STRU;

typedef struct
{   
    VOS_UINT8                   ucServiceIndex;     /* 服务在服务数组结构中的下标 */
    VOS_UINT8                   ucRabId;            /* Rab ID，调用pUlCallFunc时使用 */
    VOS_UINT8                   aucRsv[2];
    DIPC_DEV_ID_ENUM_UINT32     enDipcDevId;        /* DIPC内部使用dev ID，调用pDlCallFunc时使用 */
    DIPC_SERV_ULDATA_MATCHFUNC  pUlMatchFunc;
    DIPC_SERV_DLDATA_MATCHFUNC  pDlMatchFunc;
    DIPC_SERV_ULDATA_CALLFUNC   pUlCallFunc;
    DIPC_SERV_DLDATA_CALLFUNC   pDlCallFunc;
}SERVICE_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulServiceNum;
    VOS_UINT32                  ulServiceMask;
    SERVICE_INFO_STRU           astServiceInfo[SERVICE_MAX_NUM];
}TOTAL_SERVICE_INFO_STRU;

typedef struct
{   
    VOS_UINT32                  ulServiceCnt;
    VOS_UINT32                  ulServiceMask;
    SERVICE_INFO_STRU          *apstServiceInfo[DIPC_SERVICE_TYPE_MAX_NUM];
}DEV_SERVICE_INFO_STRU;

typedef struct
{   
    VOS_UINT32                  ulServiceCnt;
    VOS_UINT32                  ulServiceMask;
    SERVICE_INFO_STRU          *apstServiceInfo[DIPC_SERVICE_TYPE_MAX_NUM];
}RAB_SERVICE_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulGetDataFailNums;          /* 底软回调后获取不到数据的次数 */
    VOS_UINT32                  ulSuccGetUlPacketNums;      /* 上行Hsic通道成功获取的数据包个数 */
    VOS_UINT32                  ulFailMatchUlPacketNums;    /* 上行Hsic通道找不到匹配服务的数据包个数 */
    VOS_UINT32                  ulFailSendUlPacketNums;     /* 上行调用ADS通道发送失败的数据包个数 */
    VOS_UINT32                  ulDiscardUlPacketNums;      /* 上行收到数据时正在进行PDP去激活操作，为了避免单板复位，将该数据丢弃 */
    VOS_UINT32                  ulSuccSendUlPacketNums;     /* 上行调用ADS通道成功发送的数据包个数*/
    VOS_UINT32                  ulFailSendDlPacketNums;     /* 下行调用底软通道发送失败的数据包个数 */
    VOS_UINT32                  ulSuccSendDlPacketNums;     /* 下行调用底软通道发送成功的数据包个数 */
} DIPC_DEV_STATIC_INFO_STRU;

typedef struct
{
    DIPC_DEV_STATIC_INFO_STRU   astDipcDevStaticInfo[DIPC_DEV_NUM];
    VOS_UINT32                  ulNullDlPacketNums;         /* 下行ADS调用了回调函数但是没有数据的次数 */
    VOS_UINT32                  ulSuccGetDlPacketNums;      /* 下行Hsic通道成功获取的数据包个数 */
    VOS_UINT32                  ulFailMatchDlPacketNums;    /* 下行Hsic通道找不到匹配服务的数据包个数 */
    VOS_UINT32                  ulDiscardDlPacketNums;      /* 下行收到数据时正在进行PDP去激活操作，为了避免单板复位，将该数据丢弃 */
} DIPC_STATIC_INFO_STRU;

typedef struct
{
    VOS_UINT8                   ucIpHdrLen  :4;     /* IP头部长度 */
    VOS_UINT8                   ucIpVer     :4;     /* IP版本号*/
    VOS_UINT8                   ucServiceType;      /* IP TOS字段*/
    VOS_UINT16                  usTotalLen;         /* IP数据包总长度*/
    VOS_UINT16                  usIdentification;   /* IP数据包ID*/
    VOS_UINT16                  usOffset;           /* IP分片偏移量*/
    VOS_UINT8                   ucTTL;              /* IPTTL*/
    VOS_UINT8                   ucProtocol;         /* IP数据载荷部分协议*/
    VOS_UINT16                  usCheckSum;         /* IP头部校验和*/
    VOS_UINT32                  ulSrcAddr;          /* 源IP地址*/
    VOS_UINT32                  ulDstAddr;          /* 目的IP地址*/
} DIPC_IPHDR_STRU;

typedef struct
{
    IMM_ZC_HEAD_STRU            stDipcDataQ;        /* DIPC数据队列，上下行数据都在其中 */
    /* DIPC消息队列中待处理的消息个数，为了解决DIPC长时间得不到处理导致消息队列满的情况 */
    VOS_UINT32                  ulNotifyMsgCnt;     
}DIPC_DATA_Q_CTRL_ST;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/* OAM ACPU勾包函数 */
extern VOS_VOID DIPC_PrintLog(VOS_UINT32 ulModuleId, VOS_UINT32 ulSubMod,
    VOS_UINT32 ulLevel, VOS_CHAR *pcString);
extern VOS_VOID DIPC_PrintLog1(VOS_UINT32 ulModuleId, VOS_UINT32 ulSubMod,
    VOS_UINT32 ulLevel, VOS_CHAR  *pcString, VOS_INT32 lPara1);
extern VOS_VOID DIPC_PrintLog2(VOS_UINT32 ulModuleId, VOS_UINT32 ulSubMod,
    VOS_UINT32 ulLevel, VOS_CHAR *pcString, VOS_INT32 lPara1, VOS_INT32 lPara2);
    
extern VOS_VOID DIPC_DEV_HsicAcmFreeDlDataCB(IMM_ZC_STRU *pstBuf);    
extern VOS_UINT32 DIPC_DEV_AcmOpenDevice(DEV_INFO_STRU *pstDevInfo);
extern VOS_UINT32 DIPC_DEV_NcmOpenDevice(DEV_INFO_STRU *pstDevInfo);
extern VOS_UINT32 DIPC_DEV_AcmGetUlDataBuf(UDI_HANDLE slUdiHsicAcmHdl, IMM_ZC_STRU **ppstBuf);
extern VOS_UINT32 DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID_ENUM_UINT32 ulDeviceId);
extern VOS_UINT32 DIPC_DEV_UsbAcm1ReadUlData( VOS_VOID);
extern VOS_UINT32 DIPC_DEV_UsbAcm3ReadUlData( VOS_VOID);
extern VOS_UINT32 DIPC_DEV_UsbAcm5ReadUlData( VOS_VOID);
extern VOS_UINT32 DIPC_DEV_UsbNcmReadUlData(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstImmZcData);
extern VOS_UINT32 DIPC_DEV_UsbNcm0ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode);
extern VOS_UINT32 DIPC_DEV_UsbNcm1ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode);
extern VOS_UINT32 DIPC_DEV_UsbNcm2ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode);
extern VOS_UINT32 DIPC_DEV_UsbAcmWriteData(UDI_HANDLE slUdiHandle, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 DIPC_DEV_UsbNcmWriteData(UDI_HANDLE slUdiHandle, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 DIPC_DEV_UsbWriteData(DIPC_DEV_ID_ENUM_UINT32 enDipcDevId, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 DIPC_DEV_PortInit( VOS_VOID );
extern VOS_VOID DIPC_DEV_AddNewIpTypeService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType, SERVICE_INFO_STRU *pstServiceInfo);
extern UDI_HANDLE DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID_ENUM_UINT32 enDevId);
extern VOS_VOID DIPC_MGR_AddNewIpTypeService(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType, SERVICE_INFO_STRU *pstServiceInfo);
extern VOS_UINT32 DIPC_MGR_DelIpVService(VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType);
extern VOS_UINT32 DIPC_MGR_AddNewService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType);
extern VOS_UINT32 DIPC_DEV_UlDataProc(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstBuf);    
extern VOS_UINT32 DIPC_MGR_UlDataProc(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 DIPC_MGR_DlAdsDataRcv(VOS_UINT8 ucRabId, IMM_ZC_STRU *pData);
extern DIPC_DEV_ID_ENUM_UINT32 DIPC_GetDevIdByRabId(VOS_UINT8 ucRabId);
extern VOS_UINT32 DIPC_DlAdsDataRcv(VOS_UINT8 ucRabId, IMM_ZC_STRU *pData,
    ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);
extern SERVICE_INFO_STRU* DIPC_MGR_GetServiceByRabId(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType);
extern VOS_VOID DIPC_MGR_DelIpTypeService(VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType);
extern VOS_VOID DIPC_RcvAtPdpActIndProc(AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg);
extern VOS_VOID DIPC_RcvAtPdpRelIndProc(AT_DIPC_PDP_DEACT_STRU *pstAtDipcPdpDeactMsg);
extern VOS_VOID  DIPC_ProcDataNotify(VOS_VOID);
extern VOS_UINT32 DIPC_AtMsgProc(const MsgBlock *pMsgBlock);
extern VOS_UINT32  DIPC_EnqueueData(IMM_ZC_STRU *pstImmZc);
extern VOS_UINT32 DIPC_Init(VOS_VOID);
extern VOS_UINT32 DIPC_Pid_InitFunc(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID DIPC_TraceUlData(DIPC_DEV_ID_ENUM_UINT32 ulDeviceId, IMM_ZC_STRU *pstData);
extern VOS_VOID DIPC_TraceDlData(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstData);
extern VOS_VOID DIPC_MappingInfoTrace(DIPC_TRACE_MSG_TYPE_ENUM_UINT32 enDipcTraceMsgType);
extern VOS_VOID DIPC_StaticInfoInit( VOS_VOID );

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

#endif /* end of PsHsic.h */

