

#ifndef __NASRABMAPPMSGPROC_H__
#define __NASRABMAPPMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasERabmPublic.h"
#include  "LRabmPdcpInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*TFT的最大优先级*/
#define NAS_ERABM_MAX_TFT_PRECEDENCE         (255)

/*标识EPS承载对应的RB是否建立*/
#define NAS_ERABM_RB_SETUP                   (0)
#define NAS_ERABM_RB_NOTSETUP                (1)


/*标识最后一个包是否为分片包*/
#define NAS_ERABM_RESEGMENT                  (1)
#define NAS_ERABM_NOT_RESEGMENT              (0)


/*标识TFT匹配结果*/
#define NAS_ERABM_TFT_MATCH_SUCC             (0)
#define NAS_ERABM_TFT_MATCH_FAIL             (1)

/*定义IP的版本*/
#define NAS_ERABM_IPFILTER_VERSION_4               (0)
#define NAS_ERABM_IPFILTER_VERSION_6               (1)

#define NAS_ERABM_SRC_IPV4_ADDR_OFFSET       (12)
#define NAS_ERABM_SRC_IPV6_ADDR_OFFSET       (8)
#define NAS_ERABM_IP_ADDRESS_4BYTE_TO_ULONG(pucIpAddr)    ((*(pucIpAddr)<<NAS_ERABM_MOVEMENT_24_BITS)\
         | (*((pucIpAddr)+1)<<NAS_ERABM_MOVEMENT_16_BITS)| (*((pucIpAddr)+2)<<NAS_ERABM_MOVEMENT_8_BITS) | (*((pucIpAddr)+3)))



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_ERABM_APP_DATA_STATUS_ENUM
{
    NAS_ERABM_APP_DATA_STATUS_STOP             =      0,       /*停止数据传输*/
    NAS_ERABM_APP_DATA_STATUS_START,                           /*启动数据传输*/
    NAS_ERABM_APP_DATA_STATUS_FORBID,                          /*禁止数据传输*/

    NAS_ERABM_APP_DATA_STATUS_BUTT
};
typedef VOS_UINT8 NAS_ERABM_APP_DATA_STATUS_ENUM_UINT8;

enum NAS_ERABM_APP_DATA_START_CAUSE_ENUM
{
    NAS_ERABM_APP_DATA_START_RBSETUP_FAIL      =      0,       /*重建RB失败开始发送数据*/
    NAS_ERABM_APP_DATA_START_RBSETUP_SUCC,                     /*重建RB成功开始发送数据*/
    NAS_ERABM_APP_DATA_START_RRC_IND,                          /*RRC指示开始发送数据*/

    NAS_ERABM_APP_DATA_START_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_ERABM_APP_DATA_START_CAUSE_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
typedef struct
{
    VOS_UINT32     ulIdentifier;
    VOS_UINT8      aucSrcIpV4Addr[NAS_ERABM_IPV4_ADDR_LEN];
    VOS_UINT8     aucDesIpV4Addr[NAS_ERABM_IPV4_ADDR_LEN];
}NAS_ERABM_IPV4_HEADER_STRU;

typedef struct
{
    VOS_UINT32     ulIdentifier;
    VOS_UINT8      aucSrcIpV6Addr[NAS_ERABM_IPV6_ADDR_LEN];
    VOS_UINT8      aucDesIpV6Addr[NAS_ERABM_IPV6_ADDR_LEN];
}NAS_ERABM_IPV6_HEADER_STRU;

typedef struct
{
    APP_ERABM_MSG_TYPE_ENUM_UINT32               ulMsgId;
    VOS_UINT16                                  usOriginalId;
    VOS_UINT16                                  usTerminalId;
    VOS_UINT32                                  ulSn;
    APP_ERABM_DATA_TRANS_SET_RESULT_ENUM_UINT32  enSetRslt;

}NAS_ERABM_APP_DATA_TRANS_SET_RESLT_STRU;

typedef VOS_VOID (*APP_DATA_IND_CALLBACK_FUNC)
(
    VOS_UINT32  ulRabId,
    VOS_UINT32  ulDataLen,
    VOS_UINT8  *pucData
 );

 typedef VOS_VOID (*APP_DATA_STATUS_CALLBACK_FUNC)
(
    VOS_UINT32  ulRabId,
    VOS_UINT8   ucStatus,
    VOS_UINT8   ucCause
);

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID Nas_DataReqTest(VOS_UINT32 ulIpVersion, VOS_UINT32 ulResegmentFlag,
                                        VOS_UINT32 ulDataNum);
extern VOS_VOID  NAS_ERABM_AppMsgDistr( VOS_VOID *pRcvMsg );

extern VOS_VOID NAS_ERABM_RcvRabmAppDataReq( const APP_ERABM_DATA_TRANS_REQ_STRU *pRcvMsg );
extern  VOS_VOID  NAS_ERABM_SndRabmAppDataCnf( const NAS_ERABM_APP_DATA_TRANS_SET_RESLT_STRU
                                                             *pstRabmAppDataTrans );
extern VOS_VOID NAS_ERABM_DecodeIpV4Data
(
    VOS_UINT8 *pucSrcData,
    NAS_ERABM_IPV4_HEADER_STRU *pstDestData
);

extern VOS_VOID  NAS_ERABM_DecodeIpV6Data
(
    VOS_UINT8 *pucSrcData,
    NAS_ERABM_IPV6_HEADER_STRU *pstDestData
);
extern VOS_VOID NAS_ERABM_SaveIpv4SegDataInfo
(
    const NAS_ERABM_IPV4_HEADER_STRU   *pstIpv4HeaderInfo,
    VOS_UINT8                           ucBearerId
);
extern PS_BOOL_ENUM_UINT8  NAS_ERABM_IsExistUplinkPfinTft( VOS_UINT32 ulEpsbId);

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

#endif /* end of NasERabmAppMsgProc.h */
