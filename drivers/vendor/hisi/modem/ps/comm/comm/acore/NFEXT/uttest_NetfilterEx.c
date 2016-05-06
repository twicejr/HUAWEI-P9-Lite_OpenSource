/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "linux/skbuff.h"
/* below my header files */
#include "NetfilterEx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*
以下宏值拷贝from <uapi/linux/netfilter_ipv4.h>
因为这些宏在这个头文件中，是使用ifndef __KERNEL__隔离的，目的是希望兼容用户态
但是因为目前搭建的用户态为了尽量模拟内核态，故意定义了__KERNEL__
故这些宏在UT工程中是没有定义的。
所以在这里，我们自己定义一次，保证其值与内核代码完全一致。
*/
/* IP Hooks */
/* After promisc drops, checksum checks. */
#define NF_IP_PRE_ROUTING   0
/* If the packet is destined for this box. */
#define NF_IP_LOCAL_IN      1
/* If the packet is destined for another interface. */
#define NF_IP_FORWARD       2
/* Packets coming from a local process. */
#define NF_IP_LOCAL_OUT     3
/* Packets about to hit the wire. */
#define NF_IP_POST_ROUTING  4
#define NF_IP_NUMHOOKS      5

/* IPv6亦同 */
/* IP6 Hooks */
/* After promisc drops, checksum checks. */
#define NF_IP6_PRE_ROUTING  0
/* If the packet is destined for this box. */
#define NF_IP6_LOCAL_IN     1
/* If the packet is destined for another interface. */
#define NF_IP6_FORWARD      2
/* Packets coming from a local process. */
#define NF_IP6_LOCAL_OUT        3
/* Packets about to hit the wire. */
#define NF_IP6_POST_ROUTING 4
#define NF_IP6_NUMHOOKS     5


#define     MAC_HEADER_SIZE     (14)
#define     IP_HEADER_SIZE      (20)


extern NF_EXT_ENTITY_STRU                  g_stExEntity;
extern NF_EXT_FLOW_CTRL_ENTITY             g_stExFlowCtrlEntity;


unsigned char   *g_pucData = NULL;


/*****************************************************************************
  3 函数实现
*****************************************************************************/
static int okfn_stub(struct sk_buff *skb)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : init_test_NFExt_STUB_envirment
 功能描述  : .c中初始化test_NFExt_STUB测试环境, 适配WinGDB
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2014年5月17日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void init_test_NFExt_STUB_envirment(void)
{
    g_pucData        = (unsigned char *)malloc(114);
}

/*****************************************************************************
 函 数 名  : recover_test_NFExt_STUB_envirment
 功能描述  : .c中恢复test_NFExt_BrDataExport测试环境, 适配WinGDB
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2014年5月17日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void recover_test_NFExt_STUB_envirment(void)
{
    if (NULL != g_pucData)
    {
        free(g_pucData);
        g_pucData = NULL;
    }
}

/*****************************************************************************
测试项：Test_NFExt_IsOmData
功能描述：判断是否OM得数据,对于协议栈中得om数据不能抓包，否则抓包风暴
测试编号：test_NFExt_IsOmData_001
测试标题：待勾取的报文是UDP报文
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月17日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
int test_NFExt_IsOmData_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff               stSkbuff;
    NF_EXT_FLAG_OM_DATA_ENUM_U32     enRlt;
    /* 构造以太帧 */
    unsigned char pData[75]     =
    {
        0x00, 0x0D, 0x87, 0x8E, 0x4B, 0xAC, 0x58, 0x2C, 0x80, 0x13, 0x92, 0x63, 0x08, 0x00, 0x45, \
        0x00, 0x00, 0x3C, 0x00, 0xD3, 0x00, 0x00, 0x80, 0x11, 0xB6, 0x99, 0xC0, 0xA8, 0x01, 0x03, \
        0xC0, 0xA8, 0x01, 0x01, 0x08, 0x00, 0x4D, 0x22, 0x00, 0x01, 0x00, 0x39, 0x61, 0x62, 0x63, \
        0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, \
        0x73, 0x74, 0x75, 0x76, 0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69
    };
    unsigned int result;

    memset(&stSkbuff, 0x0, sizeof(struct sk_buff));
    stSkbuff.head = pData;
    stSkbuff.data = pData;
#ifdef NET_SKBUFF_DATA_USES_OFFSET
    stSkbuff.network_header     = MAC_HEADER_SIZE;
#else
    stSkbuff.network_header     = stSkbuff.head + MAC_HEADER_SIZE;
#endif
    result = (unsigned int)NFExt_IsOmData(&stSkbuff);

    if (NF_EXT_FLAG_NOT_OM_DATA != result)
    {
        return -1;  /* FAIL */
    }
    else
    {
        return 0;   /* SUCC */
    }
#else
    return 0;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_IsOmData
功能描述：判断是否OM得数据,对于协议栈中得om数据不能抓包，否则抓包风暴
测试编号：Test_NFExt_IsOmData02
测试标题：待勾取的报文是TCP报文且目的端口和ip和OM匹配
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月17日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_IsOmData_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff               stSkbuff;
    /* 构造以太帧 */
    unsigned char pData[55]     =
    {
        0x00, 0x0D, 0x87, 0x8E, 0x4B, 0xAC, 0x58, 0x2C, 0x80, 0x13, 0x92, 0x63, \
        0x08, 0x00, 0x45, 0x00, 0x00, 0x28, 0x12, 0x92, 0x40, 0x00, 0x80, 0x06, \
        0x5A, 0xE2, 0xC0, 0xA8, 0x02, 0x05, 0xC0, 0xA8, 0x02, 0x05, 0x0B, 0xB8, \
        0xB8, 0x0B, 0xEC, 0x07, 0xCE, 0x85, 0xEF, 0xEF, 0xE0, 0x7F, 0x50, 0x10, \
        0x80, 0x00, 0x49, 0x4B, 0x00, 0x00
    };

    memset(&stSkbuff, 0x0, sizeof(stSkbuff));

    stSkbuff.head = pData;
    stSkbuff.data = pData;

#ifdef NET_SKBUFF_DATA_USES_OFFSET
    stSkbuff.network_header     = MAC_HEADER_SIZE;
    stSkbuff.transport_header   = stSkbuff.network_header + IP_HEADER_SIZE;
#else
    stSkbuff.network_header     = stSkbuff.head + MAC_HEADER_SIZE;
    stSkbuff.transport_header   = stSkbuff.network_header + IP_HEADER_SIZE;
#endif

    g_stExEntity.ulOmIp         = inet_addr("192.168.2.5");

    return (unsigned int)NFExt_IsOmData(&stSkbuff);
#else
    return 0;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_IsOmData
功能描述：判断是否OM得数据,对于协议栈中得om数据不能抓包，否则抓包风暴
测试编号：Test_NFExt_IsOmData03
测试标题：待勾取的报文是TCP报文且目的和源端口和ip和OM均不匹配
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月17日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_IsOmData_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff               stSkbuff;
    /* 构造以太帧 */
    unsigned char pData[55]     =
    {
        0x00, 0x0D, 0x87, 0x8E, 0x4B, 0xAC, 0x58, 0x2C, 0x80, 0x13, 0x92, 0x63, \
        0x08, 0x00, 0x45, 0x00, 0x00, 0x28, 0x12, 0x92, 0x40, 0x00, 0x80, 0x06, \
        0x5A, 0xE2, 0xC0, 0xA8, 0x01, 0x03, 0xC0, 0xA8, 0x0B, 0x08, 0xB8, 0x01, \
        0x0B, 0x20, 0xEC, 0x07, 0xCE, 0x85, 0xEF, 0xEF, 0xE0, 0x7F, 0x50, 0x10, \
        0x80, 0x00, 0x49, 0x4B, 0x00, 0x00
    };

    memset(&stSkbuff, 0x0, sizeof(stSkbuff));
    stSkbuff.head = pData;
    stSkbuff.data = pData;

#ifdef NET_SKBUFF_DATA_USES_OFFSET
    stSkbuff.network_header     = MAC_HEADER_SIZE;
    stSkbuff.transport_header   = stSkbuff.network_header + IP_HEADER_SIZE;
#else
    stSkbuff.network_header     = stSkbuff.head + MAC_HEADER_SIZE;
    stSkbuff.transport_header   = stSkbuff.network_header + IP_HEADER_SIZE;
#endif

    g_stExEntity.ulOmIp         = inet_addr("192.168.2.5");

    return NFExt_IsOmData(&stSkbuff);
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrDataExport
功能描述：将勾取网桥中转报文导出到SDT
测试编号：Test_NFExt_BrDataExport01
测试标题：正常导入
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月17日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void test_NFExt_BrDataExport_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff                      stSkb;
    struct net_device               stDevIn;
    struct net_device               stDevOut;
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16 usType;


    memset(g_pucData, 1, 114);
    stSkb.len   = 100;
    usType      = ID_IPS_TRACE_BRIDGE_DATA_INFO;
    stSkb.data  = g_pucData+MAC_HEADER_SIZE;

    NFExt_BrDataExport(&stSkb, &stDevIn, &stDevOut, usType);
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrDataExport
功能描述：将勾取网桥中转报文导出到SDT
测试编号：Test_NFExt_BrDataExport02
测试标题：数据大于1500
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void test_NFExt_BrDataExport_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff                      stSkb;
    struct net_device               stDevIn;
    struct net_device               stDevOut;
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16 usType;

    memset(g_pucData, 1, 114);
    stSkb.len   = 3000;
    usType      = ID_IPS_TRACE_BRIDGE_DATA_INFO;
    stSkb.data  = g_pucData+MAC_HEADER_SIZE;

    NFExt_BrDataExport(&stSkb, &stDevIn, &stDevOut, usType);
#endif
}

/*****************************************************************************
测试项：Test_NFExt_ArpDataExport
功能描述：将勾取ARP报文导出到SDT
测试编号：Test_NFExt_ArpDataExport01
测试标题：正常导入
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void test_NFExt_ArpDataExport_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff                      stSkb;
    struct net_device                   stDev;
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16 usType;

    memset(g_pucData, 1, 100);
    stSkb.len   = 100;
    usType      = ID_IPS_TRACE_BRIDGE_DATA_INFO;
    stSkb.data  = g_pucData;

    NFExt_ArpDataExport(&stSkb, &stDev, usType);
#endif
}

/*****************************************************************************
测试项：Test_NFExt_IpDataExport
功能描述：将勾取IP报文导出到SDT
测试编号：Test_NFExt_IpDataExport01
测试标题：待勾取的报文是OM的数据
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void test_NFExt_IpDataExport_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff                      stSkb;
    struct net_device               stDev;
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16 usType;

    usType      = ID_IPS_TRACE_INPUT_DATA_INFO;
    stSkb.len   = 100;

    NFExt_IpDataExport(&stSkb, &stDev, usType);
#endif
}

/*****************************************************************************
测试项：Test_NFExt_IpDataExport
功能描述：将勾取IP报文导出到SDT
测试编号：test_NFExt_IpDataExport_002
测试标题：数据包大于1500
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void test_NFExt_IpDataExport_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff                      stSkb;
    struct net_device               stDev;
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16 usType;

    usType      = ID_IPS_TRACE_INPUT_DATA_INFO;
    stSkb.len   = 3000;

    NFExt_IpDataExport(&stSkb, &stDev, usType);
#endif
}

/*****************************************************************************
测试项：Test_NFExt_IpDataExport
功能描述：将勾取IP报文导出到SDT
测试编号：test_NFExt_IpDataExport_003
测试标题：正常导入
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void test_NFExt_IpDataExport_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    struct sk_buff                      stSkb;
    struct net_device               stDev;
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16 usType;

    memset(g_pucData, 1, 114);
    stSkb.len   = 100;
    usType      = ID_IPS_TRACE_INPUT_DATA_INFO;
    stSkb.data  = g_pucData+MAC_HEADER_SIZE;

    NFExt_IpDataExport(&stSkb, &stDev, usType);
#endif
}

/*****************************************************************************
测试项：test_NFExt_BrPreRoutingHook_001
功能描述：BRIGE钩子函数
测试编号：test_NFExt_BrPreRoutingHook_001
测试标题：待勾取的报文是OM的消息
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_BrPreRoutingHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int hooknum    = NF_BR_PRE_ROUTING;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    return NFExt_BrPreRoutingHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrPreRoutingHook
功能描述：BRIGE钩子函数
测试编号：Test_NFExt_BrPreRoutingHook02
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_BrPreRoutingHook_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int hooknum    = NF_BR_PRE_ROUTING;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    return NFExt_BrPreRoutingHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrPostRoutingHook
功能描述：BRIGE钩子函数
测试编号：Test_NFExt_BrPostRoutingHook01
测试标题：待勾取的报文是OM的消息
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void test_NFExt_BrPostRoutingHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int hooknum    = NF_BR_POST_ROUTING;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    NFExt_BrPostRoutingHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrPostRoutingHook
功能描述：BRIGE钩子函数
测试编号：Test_NFExt_BrPostRoutingHook02
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
void test_NFExt_BrPostRoutingHook_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int hooknum    = NF_BR_POST_ROUTING;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    NFExt_BrPostRoutingHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrLocalInHook
功能描述：BRIGE钩子函数
测试编号：Test_NFExt_BrLocalInHook01
测试标题：待勾取的报文是OM的消息
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_BrLocalInHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_BR_LOCAL_IN;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_BrLocalInHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrLocalInHook
功能描述：BRIGE钩子函数
测试编号：Test_NFExt_BrLocalInHook02
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_BrLocalInHook_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_BR_LOCAL_IN;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_BrLocalInHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrLocalOutHook
功能描述：BRIGE钩子函数
测试编号：Test_NFExt_BrLocalOutHook01
测试标题：待勾取的报文是OM的消息
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_BrLocalOutHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_BR_LOCAL_OUT;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_BrLocalOutHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrLocalOutHook
功能描述：BRIGE钩子函数
测试编号：Test_NFExt_BrLocalOutHook02
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_BrLocalOutHook_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_BR_LOCAL_OUT;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_BrLocalOutHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrForwardHook
功能描述：BRIGE钩子函数
测试编号：Test_NFExt_BrForwardHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_BrForwardHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_BR_FORWARD;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_BrForwardHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_ArpInHook
功能描述：ARP钩子函数
测试编号：Test_NFExt_ArpInHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_ArpInHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_ARP_IN;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_ArpInHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_ArpOutHook
功能描述：ARP钩子函数
测试编号：Test_NFExt_ArpOutHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_ArpOutHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_ARP_OUT;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_ArpOutHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip4PreRoutingHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip4PreRoutingHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月19日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip4PreRoutingHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP_PRE_ROUTING;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip4PreRoutingHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip4PostRoutingHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip4PostRoutingHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip4PostRoutingHook_001(void)
{
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP_POST_ROUTING;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip4PostRoutingHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
}

/*****************************************************************************
测试项：Test_NFExt_Ip4LocalInHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip4LocalInHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip4LocalInHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP_LOCAL_IN;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip4LocalInHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip4LocalOutHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip4LocalOutHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip4LocalOutHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP_LOCAL_OUT;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip4LocalOutHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip4ForwardHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip4ForwardHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip4ForwardHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP_FORWARD;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip4ForwardHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip6PreRoutingHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip6PreRoutingHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip6PreRoutingHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP6_PRE_ROUTING;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip6PreRoutingHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip6PostRoutingHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip6PostRoutingHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip6PostRoutingHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP6_POST_ROUTING;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip6PostRoutingHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip6LocalInHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip6LocalInHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip6LocalInHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP6_LOCAL_IN;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip6LocalInHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip6LocalOutHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip6LocalOutHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip6LocalOutHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP6_LOCAL_OUT;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip6LocalOutHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_Ip6ForwardHook
功能描述：IP钩子函数
测试编号：Test_NFExt_Ip6ForwardHook01
测试标题：正常勾包
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
unsigned int test_NFExt_Ip6ForwardHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    unsigned int result     = 0;
    unsigned int hooknum    = NF_IP6_FORWARD;
    struct sk_buff  stSkb;
    struct net_device stDevIn;
    struct net_device stDevOut;

    result  = NFExt_Ip6ForwardHook(hooknum, &stSkb, &stDevIn, &stDevOut, okfn_stub);

    return result;
#else
    return 1;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrForwardFlowCtrlHook
功能描述：br forward流控函数测试
测试编号：Test_NFExt_BrForwardFlowCtrlHook01
测试标题：流控状态丢包(起流控状态应该返回丢包)
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
int test_NFExt_BrForwardFlowCtrlHook_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_INT32       iRet;
    struct sk_buff  skb;

    /* 先初始化流控 */
    NFExt_FlowCtrlInit();

    g_stExFlowCtrlEntity.ulFlowCtrlMsk |= NF_EXT_BR_FORWARD_FLOW_CTRL_MASK;

    iRet = NFExt_BrForwardFlowCtrlHook(0, &skb, NULL, NULL, NULL);

    return iRet;
#else
    return 0;
#endif
}

/*****************************************************************************
测试项：Test_NFExt_BrForwardFlowCtrlHook
功能描述：br forward流控函数测试
测试编号：Test_NFExt_BrForwardFlowCtrlHook02
测试标题：解流控状态不丢包(非起流控状态应该返回正常接受数据包)
测试步骤：1、
预期结果：1、

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : c00191211
    修改内容   : Created
  2.日    期   : 2014年5月20日
    作    者   : liukai
    修改内容   : 改造到WinGDB
*****************************************************************************/
int test_NFExt_BrForwardFlowCtrlHook_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_INT32 iRet;
    struct sk_buff  skb;

    /* 先初始化流控 */
    NFExt_FlowCtrlInit();

    g_stExFlowCtrlEntity.ulFlowCtrlMsk &= ~NF_EXT_BR_FORWARD_FLOW_CTRL_MASK;

    iRet = NFExt_BrForwardFlowCtrlHook(0, &skb, NULL, NULL, NULL);

    return iRet;
#else
    return 1;
#endif
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



