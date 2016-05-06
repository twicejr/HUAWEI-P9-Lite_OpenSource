/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : IpNdClient.h
  版 本 号   : 初稿
  作    者   : WangGang 00145177
  生成日期   : 2011年3月31日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2011年3月31日
    作    者   : WangGang 00145177
    修改内容   : 创建文件

******************************************************************************/

#ifndef __IPNDCLIENT_H__
#define __IPNDCLIENT_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "IpComm.h"
#include  "IpIpmGlobal.h"


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
  2 宏定义
*****************************************************************************/
#define NDCLIENT_TASK_PID     UEPS_PID_NDCLIENT      /*PID*/
#define NDCLIENT_TASK_FID     UEPS_FID_NDCLIENT      /*FID*/

/*对NDCLIENT使用的内存池进行适配，分别用于V9R1和V3R3*/
#if (FEATURE_OFF == FEATURE_SKB_EXP)
#define IP_NDCLIENT_MEM_POOL_ID             (TTF_MEM_POOL_ID_UL_IP_DATA)
#else
#define IP_NDCLIENT_MEM_POOL_ID             (TTF_MEM_POOL_ID_DL_SHARE)
#endif

#define IP_MAX_NDCLIENT_ENTITY_NUM      (11)

#define IP_NDCLIENT_GET_ADDR_INFO_INDEX(exEpsbId)       (IP_NdClient_GetEntityIndex(exEpsbId))

#define IP_NDCLIENT_Entity_IncRevPackageNum(ulEpsbId) \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevPackageNum++; \
                g_stNdClientStatInfo.ulRevPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevRaPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevRaPackageNum++; \
                g_stNdClientStatInfo.ulRevRaPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevEchoReqPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevEchoReqPackageNum++; \
                g_stNdClientStatInfo.ulRevEchoReqPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevTooBigPackageNum(ulEpsbId)   \
                        {\
                            g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevTooBigPackageNum++; \
                            g_stNdClientStatInfo.ulRevTooBigPackageNum++; \
                        }

#define IP_NDCLIENT_Entity_IncSendPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulSendPackageNum++; \
                g_stNdClientStatInfo.ulSendPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncSendRsPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulSendRsPackageNum++; \
                g_stNdClientStatInfo.ulSendRsPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncSendEchoReplyPackageNum(ulEpsbId)   \
                        {\
                            g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulSendEchoReplyPackageNum++; \
                            g_stNdClientStatInfo.ulSendEchoReplyPackageNum++; \
                        }

#define IP_NDCLIENT_Entity_IncSendICMPV6TooBigPackageNum(ulEpsbId)   \
                        {\
                            g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulSendICMPV6TooBigPackageNum++; \
                            g_stNdClientStatInfo.ulSendICMPV6TooBigPackageNum++; \
                        }

#define IP_NDCLIENT_Entity_IncDiscPackageNum(ulEpsbId)    \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulDiscPackageNum++; \
                g_stNdClientStatInfo.ulDiscPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevNotForMePackageNum(ulEpsbId)  \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevNotForMePackageNum++; \
                g_stNdClientStatInfo.ulRevNotForMePackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevInvalidPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevInvalidPackageNum++; \
                g_stNdClientStatInfo.ulRevInvalidPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncTimerNum(ulEpsbId)      \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulTimerNum++; \
                g_stNdClientStatInfo.ulTimerNum++; \
            }

#define IP_NDCLIENT_Entity_IncTimeoutNum(ulEpsbId)      \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulTimeoutNum++; \
                g_stNdClientStatInfo.ulTimeoutNum++; \
            }

#define IP_NDCLIENT_Entity_IncMemAllocNum(ulEpsbId)    \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulMemAllocNum++; \
                g_stNdClientStatInfo.ulMemAllocNum++; \
            }

#define IP_NDCLIENT_Entity_IncMemFreeNum(ulEpsbId)     \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulMemFreeNum++; \
                g_stNdClientStatInfo.ulMemFreeNum++; \
            }

#define IP_NDCLIENT_IncRevPackageNum()          g_stNdClientStatInfo.ulRevPackageNum++;
#define IP_NDCLIENT_IncRevRaPackageNum()        g_stNdClientStatInfo.ulRevRaPackageNum++;
#define IP_NDCLIENT_IncRevEchoReqPackageNum()   g_stNdClientStatInfo.ulRevEchoReqPackageNum++;
#define IP_NDCLIENT_IncRevTooBigPackageNum()    g_stNdClientStatInfo.ulRevTooBigPackageNum
#define IP_NDCLIENT_IncSendPackageNum()         g_stNdClientStatInfo.ulSendPackageNum++;
#define IP_NDCLIENT_IncSendRsPackageNum()       g_stNdClientStatInfo.ulSendRsPackageNum++;
#define IP_NDCLIENT_IncSendEchoReplyPackageNum() g_stNdClientStatInfo.ulSendEchoReplyPackageNum++;
#define IP_NDCLIENT_IncSendICMPV6TooBigPackageNum() g_stNdClientStatInfo.ulSendICMPV6TooBigPackageNum++;
#define IP_NDCLIENT_IncDiscPackageNum()         g_stNdClientStatInfo.ulDiscPackageNum++;
#define IP_NDCLIENT_IncRevNotForMePackageNum()  g_stNdClientStatInfo.ulRevNotForMePackageNum++;
#define IP_NDCLIENT_IncRevInvalidPackageNum()   g_stNdClientStatInfo.ulRevInvalidPackageNum++;
#define IP_NDCLIENT_IncTimerNum()               g_stNdClientStatInfo.ulTimerNum++;
#define IP_NDCLIENT_IncTimeoutNum()             g_stNdClientStatInfo.ulTimeoutNum++;
#define IP_NDCLIENT_IncMemAllocNum()            g_stNdClientStatInfo.ulMemAllocNum++;
#define IP_NDCLIENT_IncMemFreeNum()             g_stNdClientStatInfo.ulMemFreeNum++;

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NDCLIENT_TIMER_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NDCLIENT定时器枚举
*****************************************************************************/
enum NDCLIENT_TIMER_ENUM
{
    /* ND CLIENT定时器 */
    IP_NDCLIENT_TIMER_RS               = 0,

    IP_NDCLIENT_TIMER_BUTT
};
typedef VOS_UINT32 NDCLIENT_TIMER_ENUM_UINT32;

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


/* 统计数据 */
typedef struct
{
    VOS_UINT32                          ulRevPackageNum;            /* 收到数据包总数 */
    VOS_UINT32                          ulRevRaPackageNum;          /* 收到RA总数 */
    VOS_UINT32                          ulRevEchoReqPackageNum;     /* 收到ECHO REQUEST总数*/
    VOS_UINT32                          ulRevTooBigPackageNum;      /* 收到超长包总数*/
    VOS_UINT32                          ulSendPackageNum;           /* 发送数据包总数 */
    VOS_UINT32                          ulSendRsPackageNum;         /* 发送RS总数 */
    VOS_UINT32                          ulSendEchoReplyPackageNum;  /* 发送ECHO REPLY总数 */
    VOS_UINT32                          ulSendICMPV6TooBigPackageNum; /* 发送超长包响应总数 */
    VOS_UINT32                          ulDiscPackageNum;           /* 丢弃数据包总数 */
    VOS_UINT32                          ulRevNotForMePackageNum;    /* 收到不能处理的数据包总数 */
    VOS_UINT32                          ulRevInvalidPackageNum;     /* 收到Checksum Error数据包总数 */

    VOS_UINT32                          ulTimerNum;                 /* Timer启动统计 */
    VOS_UINT32                          ulTimeoutNum;               /* Timer超时统计 */

    VOS_UINT32                          ulMemAllocNum;              /* 内存分配统计 */
    VOS_UINT32                          ulMemFreeNum;               /* 内存释放统计 */

}IP_NDCLIENT_STATISTIC_INFO_STRU;

/* NDCLIENT实体 */
typedef struct
{
    VOS_UINT8                           ucEpsbId;       /*DSDA修改后，高2bit代表ModemId，低6bit代表EPSID*/
    VOS_UINT8                           ucflag;
    VOS_UINT8                           aucReserve1[2];
    IP_ICMPV6_TYPE_ENUM_UINT32          enMsgType;

    VOS_UINT8                           aucInterfaceId[ND_IPV6_IF_LEN];
    VOS_UINT8                           aucRouterIpAddr[IP_IPV6_ADDR_LEN];
    IP_TIMER_STRU                       stTimerInfo;
    IP_SND_MSG_STRU                     stIpSndNwMsg;
    VOS_UINT16                          usRouterLifeTime;
    VOS_UINT8                           aucReserve2[2];
    VOS_UINT32                          ulReachableTimer;
    VOS_UINT32                          ulReTransTime;
    VOS_UINT32                          ulMtu;
    IP_NDCLIENT_STATISTIC_INFO_STRU     stStats;
}IP_NDCLIENT_ENTITY_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID IP_NdClient_Init(VOS_VOID);
extern VOS_UINT32  IP_NdClient_GetEntityIndex(VOS_UINT8 ucExEpsId);







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

#endif /* end of IpNdClient.h */
