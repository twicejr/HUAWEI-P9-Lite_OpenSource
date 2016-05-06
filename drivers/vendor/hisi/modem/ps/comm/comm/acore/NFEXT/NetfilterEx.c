

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_NFEXT)

#include "NetfilterEx.h"

#if (VOS_OS_VER == VOS_WIN32)
#include <linuxstub.h>
#else
#include "linux/inet.h"
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_ACPU_NFEX_C


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define             PACKAGE_HEAD_LEN        (80)        /*设定的截取包头的长度*/
#define             OM_SOCK_PORT_NUM        (3000)      /*与OM的宏SOCK_PORT_NUM保持一致*/
/*****************************************************************************
  3 外部函数变量声明
*****************************************************************************/

extern NF_EXT_ENTITY_STRU           g_stExEntity;
extern NF_EXT_FLOW_CTRL_ENTITY      g_stExFlowCtrlEntity;

/******************************************************************************
  4 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : NFExt_IsOmData
 功能描述  : 判断是否OM得数据,对于协议栈中得om数据不能抓包，否则抓包风暴
 输入参数  : struct sk_buff *skb    待勾取报文的sk_buff结构
 输出参数  : 无
 返 回 值  : NF_EXT_FLAG_OM_DATA/NF_EXT_FLAG_NOT_OM_DATA
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
NF_EXT_FLAG_OM_DATA_ENUM_U32 NFExt_IsOmData(struct sk_buff *skb)
{
    struct iphdr        *ipHeader;
    __be32               srcIp;
    __be32               destIp;
    struct tcphdr       *tcpHeader;
    __be16               srcPort;
    __be16               destPort;
    __be32               ulOmSocketIp;

    ipHeader        = (struct iphdr *)(skb_network_header(skb));

    /*如果不是TCP报文则直接返回*/
    if ( NF_EXT_RPO_TCP != ipHeader->protocol )
    {
        return NF_EXT_FLAG_NOT_OM_DATA;
    }

    /* 传输层的数据在ip层之后 */
    tcpHeader       = (struct tcphdr *)(skb_network_header(skb) + sizeof(struct iphdr));

    srcIp           = ipHeader->saddr;
    destIp          = ipHeader->daddr;
    srcPort         = ntohs(tcpHeader->source);
    destPort        = ntohs(tcpHeader->dest);
    ulOmSocketIp    = g_stExEntity.ulOmIp;

    if ( ((ulOmSocketIp == srcIp) && (OM_SOCK_PORT_NUM == srcPort))
      || ((ulOmSocketIp == destIp) && (OM_SOCK_PORT_NUM == destPort)) )
    {
        return NF_EXT_FLAG_OM_DATA;
    }

    return NF_EXT_FLAG_NOT_OM_DATA;
}

/*****************************************************************************
 函 数 名  : NFExt_BrDataExport
 功能描述  : 将勾取网桥中转报文导出到SDT
 输入参数  : struct sk_buff *skb,       待勾取报文的sk_buff结构
             const struct net_device *device_in, 数据发送设备信息
             const struct net_device *device_out, 数据接收设备信息
             TTF_MNTN_MSG_TYPE_ENUM_UINT16 usType  可维可测消息类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
VOS_VOID NFExt_BrDataExport( struct sk_buff *skb,
                                const struct net_device *device_in,
                                const struct net_device *device_out,
                                TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType)
{
    VOS_UINT8                       *pucData;
    VOS_UINT32                       ulHookDataLen;

    /* skb->data指向数据包的IP头部，上移14个字节令 pucData指向数据包的mac头部 */
    pucData             = skb->data - MAC_HEADER_LENGTH;
    ulHookDataLen       = ((skb->len > NF_EXT_MAX_IP_SIZE) ? NF_EXT_MAX_IP_SIZE : skb->len) + MAC_HEADER_LENGTH;

    IPS_MNTN_BridgePktInfoCB((const VOS_UINT8 *)device_in->name, (const VOS_UINT8 *)device_out->name, pucData, (VOS_UINT16)ulHookDataLen, enType);
}

/*****************************************************************************
 函 数 名  : NFExt_ArpDataExport
 功能描述  : 将勾取ARP报文导出到SDT
 输入参数  : struct sk_buff *skb,       待勾取报文的sk_buff结构
             const struct net_device *device_in, 数据发送设备信息
             const struct net_device *device_out, 数据接收设备信息
             TTF_MNTN_MSG_TYPE_ENUM_UINT16 usType  可维可测消息类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
VOS_VOID NFExt_ArpDataExport( struct sk_buff *skb,
                                    const struct net_device *device,
                                    TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType)
{
    VOS_UINT8                       *pucData;
    VOS_UINT32                       ulHookDataLen;

    pucData             = skb->data;
    ulHookDataLen       = skb->len;

    IPS_MNTN_CtrlPktInfoCB((const VOS_UINT8 *)device->name, (const VOS_UINT8 *)pucData, (VOS_UINT16)ulHookDataLen, enType);
}

/*****************************************************************************
 函 数 名  : NFExt_IpDataExport
 功能描述  : 将勾取IP报文导出到SDT
 输入参数  : struct sk_buff *skb,       待勾取报文的sk_buff结构
             const struct net_device *device_in, 数据发送设备信息
             const struct net_device *device_out, 数据接收设备信息
             TTF_MNTN_MSG_TYPE_ENUM_UINT16 usType  可维可测消息类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
VOS_VOID NFExt_IpDataExport( struct sk_buff *skb,
                         const struct net_device *device,
                         TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType)
{
    VOS_UINT8                       *pucData;
    VOS_UINT32                       ulHookDataLen;

    if ( NF_EXT_FLAG_OM_DATA == NFExt_IsOmData(skb) )
    {
        return;
    }

    /* skb->data指向数据包的IP头部，上移14个字节令 pucData指向数据包的mac头部 */
    pucData           = skb->data - MAC_HEADER_LENGTH;
    ulHookDataLen     = ((skb->len > NF_EXT_MAX_IP_SIZE) ? NF_EXT_MAX_IP_SIZE : skb->len) + MAC_HEADER_LENGTH;

    IPS_MNTN_PktInfoCB((const VOS_UINT8 *)device->name, (const VOS_UINT8 *)pucData, (VOS_UINT16)ulHookDataLen, enType);
}


/*****************************************************************************
 函 数 名  : NFExt_BrPreRoutingHook
 功能描述  : BRIGE钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_BrPreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    /* 判断是否OM的数据 */
    if ( NF_EXT_FLAG_OM_DATA == NFExt_IsOmData(skb) )
    {
        return NF_ACCEPT;
    }

    NFExt_BrDataExport(skb, in, out, ID_IPS_TRACE_BRIDGE_PRE_ROUTING_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_BrPostRoutingHook
 功能描述  : Bridge钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_BrPostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    if ( NF_EXT_FLAG_OM_DATA == NFExt_IsOmData(skb) )
    {
        return NF_ACCEPT;
    }

    NFExt_BrDataExport(skb, in, out, ID_IPS_TRACE_BRIDGE_POST_ROUTING_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_BrLocalInHook
 功能描述  : Bridge钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_BrLocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    if ( NF_EXT_FLAG_OM_DATA == NFExt_IsOmData(skb) )
    {
        return NF_ACCEPT;
    }

    NFExt_BrDataExport(skb, in, out, ID_IPS_TRACE_BRIDGE_LOCAL_IN_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_BrLocalOutHook
 功能描述  : Bridge钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_BrLocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    if ( NF_EXT_FLAG_OM_DATA == NFExt_IsOmData(skb) )
    {
        return NF_ACCEPT;
    }

    NFExt_BrDataExport(skb, in, out, ID_IPS_TRACE_BRIDGE_LOCAL_OUT_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_BrForwardHook
 功能描述  : Bridge钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_BrForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_BrDataExport(skb, in, out, ID_IPS_TRACE_BRIDGE_DATA_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_ArpInHook
 功能描述  : ARP钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_ArpInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_ArpDataExport(skb, in, ID_IPS_TRACE_RECV_ARP_PKT);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_ArpOutHook
 功能描述  : ARP钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/

unsigned int NFExt_ArpOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{

    NFExt_ArpDataExport(skb, out, ID_IPS_TRACE_SEND_ARP_PKT);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip4PreRoutingHook
 功能描述  : IPV4钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip4PreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, in, ID_IPS_TRACE_INPUT_DATA_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip4PostRoutingHook
 功能描述  : IPV4钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/

unsigned int NFExt_Ip4PostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, out, ID_IPS_TRACE_OUTPUT_DATA_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip4LocalInHook
 功能描述  : IPV4钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip4LocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{

    NFExt_IpDataExport(skb, in, ID_IPS_TRACE_IP4_LOCAL_IN_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip4LocalOutHook
 功能描述  : IPV4钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip4LocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, out, ID_IPS_TRACE_IP4_LOCAL_OUT_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip4ForwardHook
 功能描述  : IPV4钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip4ForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, in, ID_IPS_TRACE_IP4_FORWARD_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip6PreRoutingHook
 功能描述  : IPV6钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip6PreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, in, ID_IPS_TRACE_INPUT_DATA_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip6PostRoutingHook
 功能描述  : IPV6钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip6PostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, out, ID_IPS_TRACE_OUTPUT_DATA_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip6LocalInHook
 功能描述  : IPV6钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip6LocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, in, ID_IPS_TRACE_IP6_LOCAL_IN_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip6LocalOutHook
 功能描述  : IPV6钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip6LocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, out, ID_IPS_TRACE_IP6_LOCAL_OUT_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
 函 数 名  : NFExt_Ip6ForwardHook
 功能描述  : IPV6钩子函数
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月22日
    作    者   : caikai
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_Ip6ForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NFExt_IpDataExport(skb, in, ID_IPS_TRACE_IP6_FORWARD_INFO);

    return NF_ACCEPT;
}

/*****************************************************************************
                        流控功能
*****************************************************************************/


/*****************************************************************************
 函 数 名  : NFExt_BrForwardFlowCtrlHook
 功能描述  : 网桥forward流控点
 输入参数  : unsigned int hooknum,          钩子函数的hooknum
             struct sk_buff *skb,           待勾取报文的sk_buff结构
             const struct net_device *in,   输入设备信息
             const struct net_device *out,  输出设备信息
             int (*okfn)(struct sk_buff *)  默认处理函数
 输出参数  : 无
 返 回 值  : NF_ACCEPT 非流控状态
             NF_DROP   流控状态，直接丢包
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月11日
    作    者   : t00148005
    修改内容   : Created
*****************************************************************************/
unsigned int NFExt_BrForwardFlowCtrlHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *))
{
    NF_EXT_STATS_INC(1, NF_EXT_STATS_BR_FC_ENTER);

    /* 网桥转发统计 */
    NF_EXT_TX_BYTES_INC(skb->len, NF_EXT_TX_BYTES_CNT_BR);


    /* 当前在网桥forward流控状态，直接丢包 */
    if (NF_EXT_BR_FORWARD_FLOW_CTRL_MASK == (g_stExFlowCtrlEntity.ulFlowCtrlMsk & NF_EXT_BR_FORWARD_FLOW_CTRL_MASK))
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_BR_FC_DROP);
        return NF_DROP;
    }

    return NF_ACCEPT;
}

#endif      /* #if (FEATURE_ON == FEATURE_NFEXT) */
