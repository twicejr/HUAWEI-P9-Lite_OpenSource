/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_api.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCPv6
*  Date Created: 2011-7-19
*        Author: PBQ(RT24429)
*   Description: dhcp6r模块对外提供的头文件
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME              DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-19     PBQ(RT24429)      Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6R_API_H_
#define _DHCP6R_API_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* 使能去使能 */
#define DHCP6R_DISABLED             0
#define DHCP6R_ENABLED              1

/* 中继模式 */
#define DHCP6R_FORWORD_CYCLE        0x0     /* 分担方式 */
#define DHCP6R_FORWORD_BROADCAST    0x1     /* 广播方式 */

/* 调试信息类型 */
#define DHCP6R_DEBUG_OFF            0x0     /* 关闭调试开关 */
#define DHCP6R_DEBUG_PAKCET         0x1     /* Packet简略信息调试开关 */
#define DHCP6R_DEBUG_ERROR          0x2     /* Error调试开关 */
#define DHCP6R_DEBUG_ALL            0x3     /* 前两者都打开 */
#define DHCP6R_DEBUG_ALL_DETAIL     0x7     /* 前两者都打开且打印报文详细信息 */

/* 对外用户接口错误码 */
enum enDHCP6RErrInfo
{
    DHCP6R_OK           = VOS_OK,
    DHCP6R_ERR          = VOS_ERR,
    DHCP6R_ERR_PARAM,                       /*  2  参数不合法                 */
    DHCP6R_ERR_NOMEM,                       /*  3  内存分配失败               */
    DHCP6R_ERR_NULL_IF,                     /*  4  接口不存在                 */
    DHCP6R_ERR_NULL_POINTER,                /*  5  指针参数为空               */
    DHCP6R_ERR_NOSUPPORT_IF,                /*  6  接口不支持DHCP6R           */
    DHCP6R_ERR_BORROW_IP_IF,                /*  7  借用地址接口               */
    DHCP6R_ERR_TRUNKPORT_IF,                /*  8  TRUNK成员端口不支持RELAY   */
    DHCP6R_ERR_MODE_NO_MATCH,               /*  9  传入接口索引与配置模式冲突 */
    DHCP6R_ERR_SERVERADDR_NO_MATCH,         /*  10 传入接口索引与Server地址类型不匹配 */
    DHCP6R_ERR_NO_CFG,                      /*  11 没有配置控制块             */
    DHCP6R_ERR_SERVER_EXIST,                /*  12 已经配置了这个地址         */
    DHCP6R_ERR_SERVER_NOEXIST,              /*  13 没有配置这个地址           */
    DHCP6R_ERR_SERVER_INVALID,              /*  14 配置的server地址非法       */
    DHCP6R_ERR_MAX_SERVER,                  /*  15 达到最大SERVER数了         */
    DHCP6R_ERR_NOT_REGISTER,                /*  16 DHCP6R 模块未注册          */
    DHCP6R_ERR_MODE_DIS,                    /*  17 去使能模式与使能模式不一致 */
    DHCP6R_ERR_JOIN_MULTI_GROUP,            /*  18 加入多播组失败             */
    DHCP6R_ERR_LEAVE_MULTI_GROUP,           /*  19 退出多播组失败             */
    DHCP6R_ERR_NO_ENABLE_RELAY,             /*  20 未始能relay功能(全局和接口模式均未使能) */
    DHCP6R_ERR_INADDR6_TO_CHAR,             /*  21 将地址结构转换成字符串失败 */
    DHCP6R_ERR_GET_IFNAMEBYINDEX,           /*  22 由接口索引获取接口名失败   */
    DHCP6R_ERR_MEMCPY,                      /*  23 内存拷贝失败               */
    DHCP6R_ERR_IPV6_DOWN,                   /*  24 接口未使能IPv6协议         */
    DHCP6R_ERR_IPV6_IF_SCAN,                /*  25 遍历使能IPv6接口失败       */
    DHCP6R_ERR_LINKLOCAL_EXIST,             /*  26 同一链路本地地址添加多次   */
    DHCP6R_ERR_LOCALHOST_ADDR,              /*  27 添加的地址是本机的地址   */
    DHCP6R_ERR_NO_CFG_DEBUG,                /*  28 没有配置此接口调试开关     */
    DHCP6R_ERR_NO_CFG_DST_IPADDR,           /*  29 发送报文没有配置目的地址   */
    DHCP6R_ERR_ADDR6_TO_STRING,             /*  30 将IPV6地址转换为字符串失败 */
    DHCP6R_ERR_ALL_JOIN_MULTI_GROUP,        /*  31 全局使能时，所有接口加入多播组失败。
                                                所有接口退出多播组失败对去使能和重新
                                                使能无影响，所以无需错误码    */
    DHCP6R_ERR_NO_IN_MULTI_GROUP,           /*  32 没有加入多播组             */
    DHCP6R_ERR_MAX,                         /*  错误码最大值,以后添加错误码请按顺序添加到此前 */
};

#define DHCP6R_SERVERLIST_MAX_NUM   8       /* 全局模式下最大Server数目，接口模式下每个接口最大Server数目 */

#ifndef _IN6ADDR_S
#define _IN6ADDR_S
 /* IPv6地址结构 */
 typedef struct tagIN6Addr
 {
     union
     {
         UCHAR     u6_ucaddr[16];
         USHORT    u6_usaddr[8];
         ULONG     u6_uladdr[4];
     } u6_addr;    /* 128-bit IP6 address */
 }IN6ADDR_S;
#endif
/* 为了引用方便，进行如下宏定义*/
#define s6_addr      u6_addr.u6_ucaddr
#define s6_addr8     u6_addr.u6_ucaddr
#define s6_addr16    u6_addr.u6_usaddr
#define s6_addr32    u6_addr.u6_uladdr

/* 对外server地址结构 */
typedef struct tagDHCP6RServerNode
{
    IN6ADDR_S      stServerAddr;     /*Server 的IPV6地址*/
    ULONG          ulIfIndex;        /*Server 对应的出接口*/
}DHCP6R_SERVERNODE_S;

/* Relay统计信息结构 */
typedef struct tagDHCP6RStatInfo
{
    ULONG ulRxServerPkt;                /* Relay收到的Server方发来的报文数      */
    ULONG ulTxServerGlobal;             /* Relay向Server方发送的目的地址为全局地
                                           址报文数                             */
    ULONG ulTxServerLinklocal;          /* Relay向Server方发送的目的地址为链路本
                                           地地址报文数                         */
    ULONG ulTxServerMulticast;          /* Relay向Server方发送的目的地址为多播地
                                           址报文数                             */
    ULONG ulTxServerPkt;                /* Relay向Server方发送的报文总数        */
                                        
    ULONG ulRxClientPkt;                /* Relay收到的Client方发过来的报文数    */ 
    ULONG ulTxClientRelayReplyPkt;      /* Relay发送到Client方的RELAYREPLY报文数 */
    ULONG ulTxClientAdvertisePkt;       /* Relay发送到Client方的ADVERTISE报文数 */
    ULONG ulTxClientReconfigurePkt;     /* Relay发送到Client方的RECONFIGURE报文数 */
    ULONG ulTxClientReplyPkt;           /* Relay发送到Client方的REPLY报文数     */
    ULONG ulTxClientPkt;                /* Relay发送到Client方的报文总数        */
                                        
    ULONG ulRxClientSolicitPkt;         /* Relay收到的SOLICIT报文数             */
    ULONG ulRxClientRequestPkt;         /* Relay收到的REQUEST报文数             */
    ULONG ulRxClientConfirmPkt;         /* Relay收到的CONFIRM报文数             */
    ULONG ulRxClientRenewPkt;           /* Relay收到的RENEW报文数               */
    ULONG ulRxClientRebindPkt;          /* Relay收到的REBIND报文数              */
    ULONG ulRxClientReleasePkt;         /* Relay收到的RELEASE报文数             */
    ULONG ulRxClientDeclinePkt;         /* Relay收到的DECLINE报文数             */
    ULONG ulRxClientInforequestPkt;     /* Relay收到的INFORMATION_REQUEST报文数 */
    ULONG ulRxClientRelayforwPkt;       /* Relay收到的RELAY_FORW报文数          */    

    ULONG ulRxServerRelayreplyPkt;      /* Relay收到的RELAY_REPL报文数          */

    /***********************************************\
     * 报文接收、发送总数                          *
     * 分担模式下，接收总数-丢弃数 == 发送报文总数 *
     * 广播模式下，接收总数-丢弃数 <= 发送报文总数 *
    \***********************************************/
    ULONG ulRxAllPkt;                   /* Relay接收报文总数，包括正常报文和丢弃
                                           报文                                 */
    ULONG ulTxAllPkt;                   /* Relay发送报文总数，包括发送成功和失败
                                           报文                                 */

    /* 丢弃报文计数 */                  
    ULONG ulRxDropPkt;                  /* Relay丢弃的报文数，包括异常报文和未配
                                           置Server地址时的正常报文             */
    ULONG ulTxFailedPkt;                /* Relay发送失败的报文数，包括完全失败和
                                           字节数不对的失败                     */                                            
}DHCP6R_STATINFO_S;

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_Enable
*  Description: 使能/去使能Relay功能。
*        Input: ULONG ulInIfIndex:  指定入接口的接口索引或0，为0表示以全局模式
*                                   使能/去使能Relay功能，非0表示以接口模式
*                                   使能/去使能指定接口的Relay功能。
*               ULONG ulEnableFlag: 使能开关：DHCP6R_DISABLED   去使能
*                                             DHCP6R_ENABLED    使能
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_Enable(ULONG ulIfIndex, ULONG ulEnableFlag);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_AddServerList
*  Description: 增加一个ServerList表项
*        Input: ULONG ulInIfIndex: 指定入接口的接口索引或0，为0表示增加全局
*                                  ServerList表项，非0表示增加指定接口的
*                                  ServerList表项。
*               DHCP6R_SERVERNODE_S *pstServerNode: Server地址结构指针，结构包括
*                                                   两个字段stServerAddr和
*                                                   ulIfIndex，说明如下:
*               stServerAddr: IPV6地址，可以是以下三种地址类型：
*                             1. IPv6全球单播地址：可以是下一个Relay的地址，
*                                也可以是Server的地址。此时ulIfIndex必须为0；
*                             2. IPv6链路本地地址：可以是下一个relay的地址，对最
*                                后一个relay来说是server的地址，此时ulIfIndex必
*                                须指定为非0;
*                             3. IPv6多播地址FF02::1:2或FF05::1:3，对于多播地址
*                                FF05::1:3，仅限与Server在同一子网的Relay才能配
*                                置。此时ulIfIndex必须指定为非0;
*               ulIfIndex: 指定地址对应的出接口索引，当指定的地址为全局单播地址
*                          时，ulIfIndex必须为0；当指定的地址为链路本地地址和多
*                          播地址时，ulIfIndex必须指定为非0;
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_AddServerList(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstServerNode);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_DelServerList
*  Description: 删除一个ServerList表项
*        Input: ULONG ulInIfIndex: 指定入接口的接口索引或0，为0表示删除全局
*                                  ServerList表项，非0表示删除指定接口的
*                                  ServerList表项。
*               DHCP6R_SERVERNODE_S *pstServerNode: Server地址结构指针，结构包括
*                                                   两个字段stServerAddr和
*                                                   ulIfIndex，说明如下:
*               stServerAddr: IPV6地址，可以是以下三种地址类型：
*                             1. IPv6全球单播地址：可以是下一个Relay的地址，
*                                也可以是Server的地址。此时ulIfIndex必须为0；
*                             2. IPv6链路本地地址：可以是下一个relay的地址，对最
*                                后一个relay来说是server的地址，此时ulIfIndex必
*                                须指定为非0;
*                             3. IPv6多播地址FF02::1:2或FF05::1:3，对于多播地址
*                                FF05::1:3，仅限与Server在同一子网的Relay才能配
*                                置。此时ulIfIndex必须指定为非0;
*               ulIfIndex: 指定地址对应的出接口索引，当指定的地址为全局单播地址
*                          时，ulIfIndex必须为0；当指定的地址为链路本地地址和多
*                          播地址时，ulIfIndex必须指定为非0;
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_DelServerList(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstServerNode);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_DelAllServerList
*  Description: 删除所有ServerList表项
*        Input: ULONG ulInIfIndex: 指定入接口的接口索引或0
*                                  为0:在接口使能模式下:表示删除所有接口的所有
*                                                       ServerList表项
*                                      在全局使能模式下:表示删除全局serverlist
*                                                       表项
*                                  非0:表示删除指定接口的所有ServerList表项。
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-28   chenyao/mashouqiang     Create
*
*******************************************************************************/
ULONG TCPIP_DHCP6R_DelAllServerList(ULONG ulInIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetServerList
*  Description: 获取ServerList列表
*        Input: ULONG ulInIfIndex: 指定入接口的接口索引或0，为0表示获取全局 
*                                  ServerList列表，非0表示获取指定入接口的
*                                  ServerList列表。
*       Output: DHCP6R_SERVERNODE_S *pstDhcp6rServerList: 保存获取到的ServerList。
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetServerList(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstDhcp6rServerList);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowServerList
*  Description: 显示ServerList列表
*        Input: ULONG ulInIfIndex: 指定入接口的接口索引或0，为0表示显示全局 
*                                  ServerList列表，非0表示显示指定入接口的
*                                  ServerList列表。
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowServerList(ULONG ulInIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_SetMaxHops
*  Description: 设置最大中继跳数。
*        Input: ULONG ulHops: 最大中继跳数，取值范围：0~255，默认为32
*       Output: 
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_SetMaxHops(ULONG ulHops);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetMaxHops
*  Description: 获取最大中继跳数。
*        Input: 
*       Output: ULONG *ulHops:保存获取的最大跳数
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetMaxHops(ULONG *pulHops);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowMaxHops
*  Description: 显示最大中继跳数。
*        Input: 无
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowMaxHops(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_SetDebugSwitch
*  Description: 设置 Relay 调试开关
*        Input: ULONG ulIfIndex: 指定接口的接口索引或0，为0表示设置全局调试开关 
*                                非0表示设置指定接口的调试开关
*               ULONG ulDebugSwitch: 调试信息等级如下: 
*                                   DHCP6R_DEBUG_OFF        调试开关关闭
*                                   DHCP6R_DEBUG_PAKCET     打开Packet简略信息调
*                                                           试开关
*                                   DHCP6R_DEBUG_ERROR      打开Error调试开关
*                                   DHCP6R_DEBUG_ALL        打开Packet简略信息和
*                                                           Error调试开关
*                                   DHCP6R_DEBUG_ALL_DETAIL 打开Packet详细信息和
*                                                           Error调试开关
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_SetDebugSwitch(ULONG ulIfIndex, ULONG ulDebugSwitch);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetDebugSwitch
*  Description: 获取 Relay 调试开关
*        Input: ULONG ulIfIndex: 指定接口的接口索引或0，为0表示获取全局 
*                                Relay 调试开关，非0表示获取指定接口的
*                                Relay 调试开关。
*       Output: ULONG *pulDebugSwitch 保存获取到的调试开关
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetDebugSwitch(ULONG ulIfIndex, ULONG *pulDebugSwitch);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_SetDbgPktLen
*  Description: 设置调试报文输出长度
*        Input: USHORT usPacketLen: 默认长度为DHCP6R_PRINT_LEN_DEFAULT(128),
*                                   最小值为DHCP6R_PRINT_LEN_MIN(34),
*                                   最大值为DHCP6R_PRINT_LEN_MAX(16384),
*                                   长度为0或者大于报文实际长度则打印报文全部内容
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-29   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_SetDbgPktLen(USHORT usPacketLen);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowDebugSwitch
*  Description: 显示 Relay 调试开关
*        Input: ULONG ulIfIndex: 指定接口的接口索引或0，为0表示显示全局 
*                                Relay 调试开关，非0表示显示指定入接口的
*                                Relay 调试开关。
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-29   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowDebugSwitch(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowCfgInfo
*  Description: 显示Relay配置信息
*        Input: ULONG ulIfIndex: 指定接口的接口索引或0，为0表示显示全局 
*                                Relay 配置信息，非0表示显示指定入接口的
*                                Relay 配置信息。
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-29   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowCfgInfo(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetStatInfo
*  Description: 获取Relay统计信息
*        Input: 无
*       Output: DHCP6R_STATINFO_S *pstDhcp6rStat: 保存获取到的Relay统计信息结构
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetStatInfo(DHCP6R_STATINFO_S *pstDhcp6rStat);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ClrStatInfo
*  Description: 清空Relay统计信息
*        Input: 无
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ClrStatInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowStatInfo
*  Description: 显示Relay统计信息
*        Input: 无
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowStatInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_SetFwdMode
*  Description: 设置中继server模式
*        Input: ULONG ulMode: DHCP6R_FORWORD_CYCLE      分担方式
*                             DHCP6R_FORWORD_BROADCAST  广播方式
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_SetFwdMode(ULONG ulMode);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetFwdMode
*  Description: 获取中继server模式
*        Input: 无
*       Output: ULONG *pulMode: 获取到的中继server模式
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetFwdMode(ULONG *pulMode);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowFwdMode
*  Description: 显示中继server模式
*        Input: 无
*       Output: 无
*       Return: 成功返回DHCP6R_OK,返回其他表示失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowFwdMode(VOID);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif      /* end of _DHCP6R_API_H_ */


