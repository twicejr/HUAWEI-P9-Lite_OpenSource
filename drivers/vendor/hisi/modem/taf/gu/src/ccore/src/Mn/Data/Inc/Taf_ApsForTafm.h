/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : TAf_ApsForTafm.h
  Author      : 韩鲁峰
  Version     : V200R001
  Date        : 2005-0
  Description : 该头文件定义了---
  History     :
  1. Date:2005-0 -
     Author: ---
     Modification:Create
  2. 2006-02-23 modify by 韩鲁峰 FOR A32D02144
  3. 2006-02-28 delete by 韩鲁峰 FOR A32D02268
  4. 2006-08-09 modify by J60010247 for A32D03479
************************************************************************/

#ifndef _TAF_APSFORTAFM_H_
#define _TAF_APSFORTAFM_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafApsApi.h"
#include "PppInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)     设置字节对齐方式
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************
  2 宏定义
  #define
*****************************************************************************/

#ifndef TAF_APS_SUCC
#define TAF_APS_SUCC                            0
#endif

#ifndef TAF_APS_FAIL
#define TAF_APS_FAIL                            1
#endif



#define TAF_PS_PARA_VALID                   0
#define TAF_PS_PARA_INVALID                 1

#define TAF_CID_LEN                         1
#define TAF_ACTTYPE_LEN                     1

#define TAF_CGACT_DEACT                     0
#define TAF_CGACT_ACT                       1

#define TAF_ACT_DFLT_CID                    0
#define TAF_ACT_ALL_CID                     0xFF
#define TAF_DEACT_ALL_CID                   0xFF



#define TAF_PPP_HEADER_LEN                  20
#define TAF_PPP_IPCP_MAX_LEN                100     /*2个DNS，2个NetBiosDns,1个IP*/
#define TAF_CID_PDPTYPE_LEN                 2


#define TAF_CGACT_ORDER_VALID(ucOrder) ((TAF_CGACT_DEACT        == (ucOrder))\
                                    ||  (TAF_CGACT_ACT          == (ucOrder)))

#define TAF_PS_PDP_CONTEXT_CID_VALID(ucCid) (ucCid <= TAF_MAX_CID)

#define TAF_PS_CID_VALID(ucCid)        ((1 <= ucCid) && (ucCid <= TAF_MAX_CID))

#define TAF_PS_OPID_VALID(OpId)        (OpId <= 134)

#define TAF_PDPTYPE_VALID(PdpType)     ((TAF_PDP_IPV4           == PdpType )    \
                                    ||  (TAF_PDP_IPV6           == PdpType )    \
                                    ||  (TAF_PDP_IPV4V6         == PdpType )    \
                                    ||  (TAF_PDP_PPP            == PdpType ))

#define TAF_PDP_D_COMP_VALID(PdpDcomp) ((TAF_PDP_D_COMP_OFF     == PdpDcomp)    \
                                    ||  (TAF_PDP_D_COMP_ON      == PdpDcomp)    \
                                    ||  (TAF_PDP_D_COMP_V42     == PdpDcomp))

#define TAF_PDP_H_COMP_VALID(PdpHcomp) ((TAF_PDP_H_COMP_OFF     == PdpHcomp)    \
                                    ||  (TAF_PDP_H_COMP_ON      == PdpHcomp)    \
                                    ||  (TAF_PDP_H_COMP_RFC1144 == PdpHcomp)    \
                                    ||  (TAF_PDP_H_COMP_RFC2507 == PdpHcomp))


#define TAF_PS_QOS_TRAFFICCLASS_VALID(QosTrafficClass)  ((QosTrafficClass <= 4))

#define TAF_PS_QOS_DELIVERORDER_VALID(DeliverOrder)     ((DeliverOrder <= 2))

#define TAF_PS_QOS_DELIVERERRSDU_VALID(DeliverErrSdu)   ((DeliverErrSdu <= 3))

#define TAF_PS_QOS_MAXSDUSIZE_VALID(MaxSduSize)         ((MaxSduSize <= 1520))

#define TAF_PS_QOS_MUXBITUL_VALID(MaxBitUl)             ((MaxBitUl <= 256000))

#define TAF_PS_QOS_MUXBITDL_VALID(MaxBitDl)             ((MaxBitDl <= 256000))

#define TAF_PS_QOS_RESIDUALBER_VALID(ResidualBer)       ((ResidualBer <= 9))

#define TAF_PS_QOS_SDUERRRATIO_VALID(SduErrRatio)       ((SduErrRatio <= 7))

#define TAF_PS_QOS_TRANSDELAY_VALID(TransDelay)         ((TransDelay <= 4100))

#define TAF_PS_QOS_TRAFFHANDLEPRIOR_VALID(TraffHandlePrior) ((TraffHandlePrior <= 3))

#define TAF_PS_QOS_GUARANTBITUL_VALID(GuarantBitUl)     ((GuarantBitUl <= 256000))

#define TAF_PS_QOS_GUARANTBITDL_VALID(GuarantBitDl)     ((GuarantBitDl <= 256000))




#define TAF_PS_INFO_LOG(String)         TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_INFO, String)
#define TAF_PS_NORM_LOG(String)         TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_NORMAL, String)
#define TAF_PS_WARN_LOG(String)         TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_WARNING, String)
#define TAF_PS_ERR_LOG(String)          TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_ERROR, String)

#define TAF_PDP_AUTH_VALID(AUTH)       ((TAF_PDP_ACTIVATE_NO_AUTH == AUTH) || (TAF_PDP_ACTIVATE_AUTH == AUTH))

/*PCO中最大可能包含的IPCP报文个数,ref to Q*/
#define APS_PCO_MAX_IPCP_PKT_NUM        (4)

/*PCO头的长度*/
#define APS_PCO_CONFIG_HDR_LEN          (4)

/*IP地址长度*/
#define APS_PPP_IP_ADDR_LEN             (6)

/*主NBNS地址长度*/
#define APS_PPP_PRI_NBNS_LEN            (6)

/*主DNS地址长度*/
#define APS_PPP_PRI_DNS_LEN             (6)

/*副NBNS地址长度*/
#define APS_PPP_SEC_NBNS_LEN            (6)

/*副NBNS地址长度*/
#define APS_PPP_SEC_DNS_LEN             (6)




/*******************************************************************************
  3 枚举定义
  typedef enum
{
    模块名_意义描述_ENUM
    MAPS_TEMPLATE_ENUM1 = 0,
    MAPS_TEMPLATE_ENUM2
    MAPS_TEMPLATE_BUTT,    用这个统一的BUTT，作为最后一个枚举值。
}MAPS_TEMPLATE_ENUM;   模块名_枚举类型描述_ENUM
*******************************************************************************/


/*****************************************************************************
  4 全局变量声明
extern VOS_UINT8* pgucMapsTemplateBuffer;   指针＋全局标识＋类型＋模块名＋意义描述
*****************************************************************************/

/*****************************************************************************
  5 UNION定义
  typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_UNION;
*****************************************************************************/

/*****************************************************************************
  6 STRUCT定义
  typedef struct
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_ST;

          事件上报时使用回调函数,由APP访问APS存放事件的内存.
          当ACT_CNF时，如果有PCO，需要在标准的事件结构的最后坠上一块内
          存，存放PCO信息，这块PCO信息的数据结构如下:
          -------------------------------
          |  PS_EVENT_STRU              |
          -------------------------------
 BEGIN :  |  AUTH_LEN (2 OCT)           |
          -------------------------------
          |  AUTH包 (AUTH_LEN OCT)      |
          -------------------------------
          |  IPCP_LEN (2 oct)           |
          -------------------------------
 END   :  |  IPCP包 (IPCP_LEN OCT)      |
          -------------------------------

          IPCP包的内容格式如下:
          -------------------------------
          |  当前子包的个数 (1 OCT)     |
          -------------------------------
          |  P1_LEN (2 OCT)             |
          -------------------------------
          |  P1包 (P1_LEN OCT)          |
          -------------------------------
          |  P2_LEN (2 oct)             |
          -------------------------------
          |  P2包 (P2_LEN OCT)          |
          -------------------------------
          |  P3_LEN (2 oct)             |
          -------------------------------
          |  P3包 (P3_LEN OCT)          |
          -------------------------------
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usLen;              /*PPP帧中code和后面的码流的长度*/
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                          *pProtIdCont;        /*即PPP帧中code和后面的码流*/
} APS_PCO_PPP_ST;


typedef APS_PCO_PPP_ST                  APS_PCO_AUTH_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_IPCP_PPP_ST;

typedef APS_PCO_PPP_ST                  APS_PCO_AUTH_ACK_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_AUTH_NAK_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_AUTH_REJ_PPP_ST;

typedef APS_PCO_PPP_ST                  APS_PCO_IPCP_ACK_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_IPCP_NAK_PPP_ST;
typedef APS_PCO_PPP_ST                  APS_PCO_IPCP_REJ_PPP_ST;

typedef struct
{
    VOS_UINT8               ucIpcpPktNum;
    VOS_UINT8               aucRsv[3];
    APS_PCO_IPCP_PPP_ST     stIpcpPkt[APS_PCO_MAX_IPCP_PKT_NUM];
}APS_PCO_IPCP_ST;


typedef struct
{
    VOS_UINT16                          usLen;              /*PPP帧中ID和后面的码流的长度*/
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                          *pProtIdCont;        /*即PPP帧中ID和后面的码流*/
} APS_PPP_ID_ST;



#define MN_APS_MAX_PROTOCOL_ID_NUM      (4)
#define MN_APS_MAX_PROTOCOL_CONTENT_LEN (127)

#define MN_APS_IPCP_PROTOCOL_ID         (0x8021)            /* Internet Protocol Control Protocol */
#define TAF_APS_IPV4_PCSCF_PROTOCOL_ID  (0x000C)            /* IPv4 P-CSCF Container Identifier */

#if (FEATURE_ON == FEATURE_IPV6)
#define MN_APS_IPV6_DNS_PROTOCOL_ID     (0x0003)            /* IPv6 DNS Container Identifier */
#define TAF_APS_IPV6_PCSCF_PROTOCOL_ID  (0x0001)            /* IPv6 P-CSCF Container Identifier */
#endif

/*****************************************************************************
 结构名称   : MN_APS_CONFIG_PROTOCOL_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : Protocol identifier内容结构
*****************************************************************************/
typedef struct
{
  VOS_UINT8                             aucProtocolId[2];   /* Protocol identifier */
  VOS_UINT16                            usProtocolLen;      /* Protocol id内容长度 */
  VOS_UINT8                             aucProtocolContents[MN_APS_MAX_PROTOCOL_CONTENT_LEN];
  VOS_UINT8                             aucReserved[1];
} MN_APS_CONFIG_PROTOCOL_STRU;


/*****************************************************************************
 结构名称   : MN_APS_PROTOCOL_CFG_OPTIONS_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 详见TS 24.008 section 10.5.6.3 Protocol configuration options
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucConfigProtocol;   /* Configuration protocol  */
    VOS_UINT8                           ucProtocolIdsNum;   /* Protocol identifier num */
    VOS_UINT8                           aucReserved[2];     /* 四字节对齐 */
    MN_APS_CONFIG_PROTOCOL_STRU         stProtocolInfo[MN_APS_MAX_PROTOCOL_ID_NUM];

} MN_APS_PROTOCOL_CFG_OPTIONS_STRU;


/*****************************************************************************
  7 消息头定义
  模块名＋意义＋HEADER
#define MAPS_TEMPLATE_HEADER            VOS_UINT16    usTotalsMsgLen;\
                                        VOS_UINT32    ulSendModuleId;\
                                        VOS_UINT32    ulRecvModuleId;
*****************************************************************************/


/*****************************************************************************
  8 消息定义
  typedef struct
{
    MAPS_TEMPLATE_HEADER
    VOS_UINT8    aucData[2];     消息体
} MAPS_TEMPLATE_MSG;
*****************************************************************************/


/*****************************************************************************
  9 FUNCTIONS定义
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*<>     在近端文件中定义，但要在远端使用的函数        <>*/
/*=======================================================*/

VOS_VOID    Aps_Str2LenStr(     VOS_UINT32                  ulStrMaxLen,
                                VOS_UINT8                  *pStr,
                                VOS_UINT8                  *pLenStr );
VOS_UINT32  Aps_Option12Cids(   VOS_UINT8                  *paucCid );
VOS_UINT32  Aps_Option0Cid(     VOS_UINT8                  *paucCid );

/*****************************************************************************
  10 OTHERS定义
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

#endif /* end of MapsTemplate.h*/
