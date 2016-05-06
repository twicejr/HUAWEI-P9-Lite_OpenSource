

#ifndef __APPRABMINTERFACE_H__
#define __APPRABMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "AppNasComm.h"
#include  "LUPZeroCopy.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*IP地址长度宏定义*/
#define APP_MAX_IPV4_ADDR_LEN                               4
#define APP_MAX_IPV6_ADDR_LEN                               16


/*APP->RABM Command消息前3个字节宏定义 APP->RABM*/
#define APP_ERABM_MSG_ID_HEADER                               0x03C01300

/*RABM->APP Command消息前3个字节宏定义 RABM->APP*/
#define ERABM_APP_MSG_ID_HEADER                               0x0313C000
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : APP_ERABM_MSG_TYPE_ENUM
 枚举说明  : APP与RABM消息取值
*****************************************************************************/
enum APP_ERABM_MSG_TYPE_ENUM
{
    /*数据传输原语*/
    ID_APP_ERABM_DATA_TRANS_REQ     = 0x01|APP_ERABM_MSG_ID_HEADER,  /*APP发给RABM的消息*/
    ID_APP_ERABM_DATA_TRANS_CNF     = 0x02|ERABM_APP_MSG_ID_HEADER,  /*RABM发给APP的消息*/

    ID_APP_ERABM_SERVICE_REQ        = 0x03|APP_ERABM_MSG_ID_HEADER,  /*APP发给RABM的消息*/

    ID_APP_ERABM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 APP_ERABM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_ERABM_DATA_TRANS_OPERATE_ENUM
 枚举说明  : 数据传输操作标识
*****************************************************************************/
enum APP_ERABM_DATA_TRANS_OPERATE_ENUM
{
    /*数据传输操作原语*/
    APP_ERABM_START_DATA_TRANS     = 0x01,                       /*启动数据传输*/
    APP_ERABM_STOP_DATA_TRANS      = 0x02,                       /*停止数据传输*/

    APP_ERABM_DATA_TRANS_OPERATE_BUTT
};
typedef VOS_UINT32 APP_ERABM_DATA_TRANS_OPERATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APP_ERABM_DATA_TRANS_SET_RESULT_ENUM
 枚举说明  : 数据传输操作设置结果取值
*****************************************************************************/
enum APP_ERABM_DATA_TRANS_SET_RESULT_ENUM
{
    APP_ERABM_DATA_TRANS_SET_SUCCESS            = 0x00,     /*RABM模块设置数据传输操作成功*/
    APP_ERABM_DATA_TRANS_SET_FAIL,                          /*RABM模块设置数据传输操作失败*/
    APP_ERABM_DATA_TRANS_SET_BUTT
};
typedef VOS_UINT32 APP_ERABM_DATA_TRANS_SET_RESULT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : APP_ERABM_TRANSFER_RESULT_ENUM
 枚举说明  : APP数传结果取值
*****************************************************************************/
enum APP_ERABM_TRANSFER_RESULT_ENUM
{
    APP_ERABM_TRANSFER_RESULT_SUCC       = 0x00,
    APP_ERABM_TRANSFER_RESULT_FAIL       = 0x01,
    APP_ERABM_TRANSFER_RESULT_BUTT
};
typedef VOS_UINT32 APP_ERABM_TRANSFER_RESULT_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : APP_ERABM_DATA_TRANS_INFO_STRU
 结构说明  : 数据传输操作请求结构
*****************************************************************************/

typedef struct
 {
     VOS_UINT32                                           bitOpIpv4 : 1;
     VOS_UINT32                                           bitOpIpv6 : 1;
     VOS_UINT32                                           bitOpSpare: 30;

     VOS_UINT16                                           usIpv4SingleRmtPort;
     VOS_UINT16                                           usIpv6SingleRmtPort;
     APP_ERABM_DATA_TRANS_OPERATE_ENUM_UINT32              enSetOpType;  /*设置数据传输操作类型:0:启动,1:停止*/


     VOS_UINT8                                            aucRmtIpv4Address[APP_MAX_IPV4_ADDR_LEN];
                                                                       /*ucSourceIpAddress[0]为IP地址高字节位
                                                                       ucSourceIpAddress[3]为低字节位*/
     VOS_UINT8                                            aucRmtIpv6Address[APP_MAX_IPV6_ADDR_LEN];
                                                                       /*ucRmtIpv6Address[0]为IPv6接口标识高字节位
                                                                       ucRmtIpv6Address[7]为IPv6接口标识低字节位*/
 }APP_ERABM_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    : APP_ERABM_DATA_TRANS_REQ_STRU
 结构说明  : 数据传输操作请求结构
*****************************************************************************/
 typedef struct
 {
     VOS_MSG_HEADER
     VOS_UINT32                                           ulMsgId;
     APP_MSG_HEADER

     APP_ERABM_DATA_TRANS_INFO_STRU                        stDataTransInfo;

 }APP_ERABM_DATA_TRANS_REQ_STRU;

/*****************************************************************************
 结构名    : APP_ERABM_DATA_TRANS_CNF_STRU
 结构说明  : 数据传输操作响应结构
*****************************************************************************/
 typedef struct
 {
     VOS_MSG_HEADER
     VOS_UINT32                                           ulMsgId;
     APP_MSG_HEADER

     APP_ERABM_DATA_TRANS_SET_RESULT_ENUM_UINT32            enSetOpRslt;  /*设置数据传输操作类型:0:成功,1:失败*/
 }APP_ERABM_DATA_TRANS_CNF_STRU;

/*****************************************************************************
 结构名    : APP_ERABM_SERVICE_REQ_STRU
 结构说明  : SERVICE请求结构
*****************************************************************************/
 typedef struct
 {
     VOS_MSG_HEADER
     VOS_UINT32                                           ulMsgId;
     APP_MSG_HEADER
 }APP_ERABM_SERVICE_REQ_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32                   g_ulERabmBufTimerLength;


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

#endif /* end of AppRabmInterface.h */
