/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_api_01.h
*
*  Project Code: Dopra V3R2
*   Module Name:   
*  Date Created: 2014-05-12
*        Author: guojianjun178934
*   Description: 该文件用于OSPFV3通过I3通知产品相关的对外结构体定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-05-12   guojianjun178934        Create
*
*******************************************************************************/
#ifndef _OSPF6_API_01_H_
#define _OSPF6_API_01_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define OSPF6_MAX_INET_ADDR_LEN                 16         /*IPV6地址最大长度*/

/*STRUCT<IPV6地址结构>*/
typedef struct tagINET6_ADDRESS
{
    UCHAR ucAddress[OSPF6_MAX_INET_ADDR_LEN];/*IPV6地址，长度为16字节*/
    UCHAR ucPrefixLen;                       /*掩码长度,取值范围:0-128*/
    UCHAR ucPad[3];                          /*填充*/
}INET6_ADDRESS_S;

/*Added by guojianjun178934, OSPFV3 邻居事件、接口事件、邻居状态告警, 2014/5/12   问题单号:S-IP-005-OSPFv3-005  */
/*接口事件告警*/
typedef struct tagOSPF6_IF_EVENT_NOTIFY
{
  ULONG ulProcID; /*OSPF进程ID*/
  ULONG ulLocalRouterID;  /*自身router id*/
  ULONG ulAreaID; /*接口区域号*/
  ULONG ulInstanceId; /*接口实例ID*/
  ULONG ulIfIndex;  /*本地接口索引*/
  UCHAR ucIfddr[OSPF6_MAX_INET_ADDR_LEN]; /*自身接口IP*/
  ULONG ulReason; /*触发事件*/
  ULONG ulPrevState;  /*接口状态机转变前的状态*/
  ULONG ulNewState; /*接口状态机转变后的状态*/
}OSPF6_IF_EVENT_NOTIFY_S;

/*邻居事件告警*/
typedef struct tagOSPF6_NBR_EVNET_NOTIFY
{
    ULONG ulVrfIndex;          /*VRF索引*/
    ULONG ulProcID;            /*进程ID*/ 
    ULONG ulLocalRouterID;    /*本端route id*/
    ULONG ulAreaID;            /*区域ID*/
    ULONG ulInstanceId;        /*接口实例ID*/
    ULONG ulLocalIfIndex;      /*和邻居对应的本地接口索引*/
    UCHAR ucIfddr[OSPF6_MAX_INET_ADDR_LEN]; /*邻居对应接口的地址*/
    ULONG ulNbrRouterID;       /*邻居地址route id*/
    UCHAR ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN]; /*邻居对应接口的地址*/
    ULONG ulReason;            /*状态变化的原因值 具体参见原因值说明*/
    ULONG ulPrevState;         /*前一状态 具体参见状态值说明*/
    ULONG ulNewState;          /*新状态 具体参见状态值说明*/
}OSPF6_NBR_EVENT_NOTIFY_S;  /*邻居状态通知结构体*/

/*邻居状态告警*/
typedef struct tagOSPF6_NBR_STATE_NOTIFY
{
    ULONG ulVrfIndex;          /*VRF索引*/
    ULONG ulProcID;            /*进程ID*/
    ULONG ulLocalRouterID;    /*Router ID*/
    ULONG ulAreaID;            /*区域ID*/ 
    ULONG ulInstanceId;        /*接口实例ID*/
    ULONG ulLocalIfIndex;      /*和邻居对应的本地接口索引*/
    ULONG ulNbrRouterID;       /*邻居Router ID*/
    UCHAR ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN]; /*邻居地址*/
    ULONG ulNbrReachable;      /*邻居是否可达标识(0:邻居不可达 1:邻居不可达)*/
    ULONG ulReason;            /*状态变化的原因值,暂时保留不用 */
}OSPF6_NBR_STATE_NOTIFY_S;  /*邻居状态通知结构体*/
/* End of Added by guojianjun178934, 2014/5/12   问题单号:S-IP-005-OSPFv3-005  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

