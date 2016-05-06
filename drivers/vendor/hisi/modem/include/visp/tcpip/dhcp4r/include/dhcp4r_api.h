/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_api.h
*
*  Project Code: VISPV1R6
*   Module Name:   
*  Date Created: 2008-3-8
*        Author: LY(57500)
*   Description: dhcp4r模块对外提供的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-3-8  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP4R_API_H_
#define _DHCP4R_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 对外用户接口错误码;添加错误码时注意同步更新 g_aszDhcp4rErrInfo */
enum enDHCP4RErrInfo
{
    DHCP4R_OK = VOS_OK,
    DHCP4R_ERR = VOS_ERR,
    DHCP4R_ERR_PARAM,               /*  2  参数不合法                  */
    DHCP4R_ERR_NOMEM,               /*  3  内存分配失败                */
    DHCP4R_ERR_NULL_IF,             /*  4  接口不存在                  */
    DHCP4R_ERR_NULL_POINTER,        /*  5  指针参数为空                */
    DHCP4R_ERR_NOSUPPORT_IF,        /*  6  接口不支持DHCP4R            */
    DHCP4R_ERR_BORROW_IP_IF,        /*  7  借用地址接口                */
    DHCP4R_ERR_TRUNKPORT_IF,        /*  8  TRUNK成员端口不支持RELAY    */
    DHCP4R_ERR_MODE_NO_MATCH,       /*  9  配置模式不匹配              */
    DHCP4R_ERR_NO_CFG,              /*  10 没有配置控制块              */
    DHCP4R_ERR_SERVER_EXIST,        /*  11 已经配置了这个地址          */
    DHCP4R_ERR_SERVER_NOEXIST,      /*  12 没有配置了这个地址          */
    DHCP4R_ERR_SERVER_INVALID,      /*  13 配置的server地址非法        */
    DHCP4R_ERR_MAX_SERVER,          /*  14 达到最大SERVER数了          */
    DHCP4R_ERR_NO_OPERATE,          /*  15 操作码错误                  */
    DHCP4R_ERR_82_SUBCODE,          /*  16 82子选项代码错误            */
    DHCP4R_ERR_82_SUBLEN,           /*  17 82子选项长度参数错误        */
    DHCP4R_ERR_82_SUB_NOCFG,        /*  18 没有配置此82子选项          */   
    DHCP4R_ERR_HA_IS_SMOOTHING,     /*  19 HA正在手动倒换或平滑处理    */  
    DHCP4R_ERR_INVALID_VRF,         /*  20 VRF错误                     */
    DHCP4R_ERR_CFG_MODE_NOMATCH,    /*  21 模式错误                    */
    DHCP4R_ERR_NOT_REGISTER,        /*  22 DHCP4R 模块未注册           */
    DHCP4R_ERR_MALLOC_VRFCFG,       /*  23 分配Relay控制块失败         */
    DHCP4R_ERR_MODE_DIS,            /*  24 去使能模式与使能模式不一致  */
    DHCP4R_ERR_NO_CFG_VRF,          /*  25 没有该VRF下的配置控制块     */
    DHCP4R_ERR_NO_DBG_VRF,          /*  26 没有该VRF下的调试控制块     */
    DHCP4R_ERR_IF_EXC_VRF,          /*  27 接口不在该VRF实例下         */
    DHCP4R_ERR_VRF_WAITLIST,        /*  28 WAITLIST的错误              */
    
    DHCP4R_ERR_MAX,                 /*  错误码最大值,以后添加错误码请按顺序添加到此前 */
};
/* 对外用户接口错误码;添加错误码时注意同步更新 g_aszDhcp4rErrInfo */

#define DHCP4R_82_SUB_MAXLEN        24      /* 子选项最大长度   */
#define DHCP4R_SERVER_MAX_NUM       8
#define DHCP4R_82_SUB_NUM           2       /* 子选项个数       */
#define DHCP4R_AGENT_MAX_NUM        8


/* define dhcp relay 82选项模式 默认为0*/
#define DHCP4R_OPT82_MODE_HOLD          0  /*保留client的82选项参数*/
#define DHCP4R_OPT82_MODE_MODIFY        1  /*修改或者添加 client 的82选项参数*/


/* 82子选项配置控制块 */
typedef struct tagDHCP4RSubOption82
{
    ULONG       ulSubCode;          /* 子选项代码   */
    ULONG       ulSubLen;           /* 子选项长度   */
    UCHAR       aucSubVar[DHCP4R_82_SUB_MAXLEN];  /* 子选项值 */
}DHCP4R_SUBOPTION82_S;

/* 对外输出配置的控制块 */
typedef struct tagDHCP4RCfg
{
    ULONG   ulIfIndex;          /* 接口索引,全局配置模式下索引为0   */
    ULONG   ulEnableStatus;     /* 使能状态,1-使能;0-去使能         */
    ULONG   ulServerNum;        /* 配置的中继地址数目               */
    ULONG   aulServer[DHCP4R_SERVER_MAX_NUM];   /* 配置的中继地址数组,按顺序存储    */ 
    DHCP4R_SUBOPTION82_S astSubOption82[DHCP4R_82_SUB_NUM]; /* 配置的82子选项数组   */
    ULONG   ulVrfIndex;         /* 实例号,0表示公网                 */
    ULONG   ulOpt82Mode;        /* option82 模式 */
}DHCP4R_CFG_INFO_S;

/* Relay统计信息结构 */
typedef struct tagDHCP4RStatInfo
{
    ULONG ulRxServerPkt;            /* Relay收到的Server发来的报文数        */
    ULONG ulTxServerPkt;            /* Relay发送到Server的报文数            */

    ULONG ulRxClientPkt;            /* Relay收到的Client发过来的报文总数    */
    ULONG ulTxClientUnicast;        /* Relay向Client发送的DHCP单播报文数    */
    ULONG ulTxClientBroadcast;      /* Relay向Client发送的DHCP广播报文数    */
    ULONG ulTxClientPkt;            /* Relay发送到Client的报文数            */

    ULONG ulRxClientDiscoverPkt;    /* Relay收到的DISCOVER报文数            */
    ULONG ulRxClientRequestPkt;     /* Relay收到的REQUEST报文数             */
    ULONG ulRxClientDeclinePkt;     /* Relay收到的DECLINE报文数             */
    ULONG ulRxClientReleasePkt;     /* Relay收到的RELEASE报文数             */
    ULONG ulRxClientInformPkt;      /* Relay收到的INFORM报文数              */
    ULONG ulRxServerOfferPkt;       /* Relay收到的OFFER报文数               */
    ULONG ulRxServerAckPkt;         /* Relay收到的ACK报文数                 */
    ULONG ulRxServerNakPkt;         /* Relay收到的NAK报文数                 */

    /* 异常报文计数 */
    ULONG ulRxBadPkt;               /* Relay收到的异常报文数                    */
    ULONG ulBorrowDropPkt;          /* Relay从借用接口接收上来的报文应丢弃      */
    ULONG ulAdd82TooLongPkt;        /* Relay加82选项后报文长度超过限制应丢弃    */

    ULONG ulTxRelayPkt;            /* Relay发送到Relay(二级Relay)的报文数            */

}DHCP4R_STATINFO_S;

/*根据接口索引和Relay 地址获取Relay请求报文源地址回调函数 
  传入参数: ulIfIndex:接口索引，用于支持多个接口使能DHCP Relay的情况
            ulRelayIP: 网关地址(主机序)，如果没有其它地址时，可以使用该地址做为报文的源地址
  返回值:   源地址(主机序)，如果返回的源地址为0或者指定的地址非本机IP，使用网关地址做为源地址
*/
typedef ULONG (*DHCP4R_GET_SRCADDR_HOOK)(ULONG ulIfIndex, ULONG ulOutIfIndex, ULONG ulRelayIP);

typedef struct tagDHCP4R_GET_SRCADDR
{
    UCHAR  *pPacket;        /* DHCP报文，剥掉IP和UDP首部，仅剩下DHCP首部（原始报文）*/
    ULONG  ulInputIfIndex;  /* 入接口索引           */
    ULONG  ulVrfIndex;      /* VRF索引              */
    ULONG  ulServerIp;      /* 主机序, dhcp服务器IP */
}DHCP4R_GET_SRCADDR_S;

/*根据接口索引和server 地址获取Relay请求报文源地址回调函数 
  传入参数: DHCP4R_GET_SRCADDR_S *pstInfo 通过dhcp报文，入接口，vrf和server ip信息获取源地址
  返回值:   源地址(主机序)，如果返回的源地址为0或者指定的地址非本机IP，使用网关地址做为源地址
*/
typedef ULONG (*DHCP4R_GET_SRCADDR_BY_SVRIP_HOOK)(DHCP4R_GET_SRCADDR_S *pstInfo);

/*******************************************************************************
*    Func Name: DHCP4R_PROC_REQUEST_HOOK
* Date Created: 2011-07-06
*       Author: y00176567/z00171897
*      Purpose: 
*  Description: 注册DHCP Relay模块报文预处理钩子,由产品完成所收到的DHCP Request报文的预处理过程,
*               根据报文内容，填写或者修改Giaddr字段;
*        Input: ULONG ulIfIndex: 收到的DHCP报文入接口
*               UCHAR* pPacket:  收到的DHCP报文，剥掉IP和UDP首部，仅剩下DHCP首部（原始报文）。
*               ULONG ulDhcpServerIp: Server IP 主机序
*       Output: UCHAR* pPacket:  修改Giaddr后的DHCP报文，剥掉IP和UDP首部，仅剩下DHCP首部（原始报文）。
*       Return: VOS_OK          成功
*               其它             失败
*      Caution: 1.在协议栈启动之前注册,不支持解注册
*               2.钩子函数对Giaddr字段的处理规则如下：
*                 如果ulIfIndex是VI接口，且Giaddr为0，则替换报文Giaddr为OMIP；
*                 如果ulIfIndex是VI接口，且Giaddr非0，则记录原始Giaddr，并替换报文Giaddr为OMIP；
*                 如果ulIfIndex不是VI接口，且Giaddr为0，则返回成功，由VISP处理；
*                 如果ulIfIndex不是VI接口，且Giaddr非0，则记录原始Giaddr，并替换报文Giaddr为OMIP；
*               3.Giaddr要求为网络序
*               4.DHCP-Relay自动选源需求,产品会根据Server IP查找路由,返回对应的Giaddr
*        Since: V2R3C05 UTRP自启动需求
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-06   y00176567      Create the first version.
*
*******************************************************************************/
typedef ULONG (*DHCP4R_PROC_REQUEST_HOOK)(ULONG ulIfIndex, UCHAR* pPacket, ULONG ulDhcpServerIp);

typedef struct tagDHCP4R_GET_GIADDR
{
    UCHAR  *pPacket; 
    ULONG  ulInputIfIndex; /* 入接口索引 */
    ULONG  ulVrfIndex;     /* 基站目前只能为0，产品可以不关注 */
    ULONG  ulServerIp;     /* 服务器地址，主机序 */
    USHORT usVlanInfo;     /*VLAN Tag信息，主机序，后12bit为VLAN ID。当前尚不能获取优先级，TRAN没上传优先级信息 */
    USHORT usRes;  
    ULONG  ulGiaddr[DHCP4R_AGENT_MAX_NUM]; /*Giaddr列表，主机序，为0表示无效，不需要保证有效地都放在前面*/
}DHCP4R_GET_GIADDR_S;

/*******************************************************************************
*    Func Name: DHCP4R_GET_GIADDR_HOOK
* Date Created: 2013-09-27
*       Author: l00213099
*      Purpose: 
*  Description: 注册DHCP Relay模块获取Giaddr处理钩子,由产品完成由报文信息获取Giaddr列表处理过程,
*               根据DHCP请求报文信息获取需要Relay的Giaddr列表。
*        Input: DHCP4R_GET_GIAADR_S *pInfo  DHCP报文和服务器信息
*       Output: pInfo->ulGiaddr  Giaddr列表
*       Return: VOS_OK          成功
*               其它            失败
*      Caution: a)	如果Giaddr为0，即为一级Relay：
*                   a)	入接口为VI接口，则为背板级联场景，需要返回OMIP作为Giaddr；
*                   b)	非VI接口，且VLAN ID为0或不带VLAN（函数入参的VID均为0），则由产品查找
*                       符合要求的地址，并返回对应的Giaddr列表，如果找不到地址，则产品使用
*                       TCPIP_GetMainIpAddr获取接口第一个地址作为Giaddr输出，函数返回成功；
*                   c)	非VI接口， VLAN ID非0，且DHCP服务器是OMIP，则根据Request报文的VLAN ID和
*                       入接口索引选择一个对应的源地址作为Giaddr输出，函数返回成功；如果找不到地址，则函数返回错误码；
*                   d)	非VI接口， VLAN ID非0，且DHCP服务器非OMIP，则根据Request报文的VLAN ID和入接口
*                       索引选择一组对应的源地址作为Giaddr输出，并且需要剔除OMIP（考虑到共IP场景），
*                       最大支持8个地址作为Giaddr，函数返回成功；
*               b)	如果Giaddr非0，即为二级Relay：（此处不能判断接口类型，因为可能是Loopback也可能是
*                   面板接口）
*                   a)	记录原始Giaddr，将Giaddr替换成OMIP进行Relay处理；
*
*        Since: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-27   l00213099      Create the first version.
*
*******************************************************************************/
typedef ULONG (*DHCP4R_GET_GIADDR_HOOK)(DHCP4R_GET_GIADDR_S *pInfo);

/*******************************************************************************
*    Func Name: DHCP4R_PROC_REPLY_HOOK
* Date Created: 2011-07-06
*       Author: y00176567/z00171897
*      Purpose: 
*  Description: 注册DHCP Relay模块报文预处理钩子,由产品完成所收到的DHCP Reply报文的预处理过程。,
*               根据XID，修改Giaddr字段;
*        Input: ULONG ulIfIndex: 收到的DHCP报文入接口
*               UCHAR * pPacket: 收到的DHCP报文，剥掉IP和UDP首部，仅剩下DHCP首部（原始报文）。
*       Output: UCHAR * pPacket: 修改Giaddr后的DHCP报文，剥掉IP和UDP首部，仅剩下DHCP首部（原始报文）。
*               ULONG * pulRecLen: 添加选项后的报文长度
*       Return: VOS_OK          成功
*               其它             失败
*      Caution: 1.在协议栈启动之前注册,不支持解注册;
*               2.钩子函数对Giaddr字段的处理规则如下：
*                 解析DHCP报文，根据XID，获取之前记录的原始Giaddr，并替换报文中的Giaddr字段;
*               3.Giaddr要求为网络序;
*               4.产品保证返回的pulRecLen为添加选项后的报文长度(从DHCP首部算起的报文长度),且长度不能越界
*        Since: V2R3C05 UTRP自启动需求
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-06   y00176567      Create the first version.
*
*******************************************************************************/
typedef ULONG (*DHCP4R_PROC_REPLY_HOOK)(ULONG ulIfIndex, UCHAR *pPacket, ULONG *pulRecLen);

typedef struct tagDHCP4R_GET_CLIENTIF
{
    UCHAR *pPacket;         /* 入参,DHCP报文,不含IP和UDP首部,此时的Giaddr字段为网络序 */ 
    ULONG  ulOutIfIndex;    /* 出参,转发的接口索引 */
    ULONG  ulSrcIp;         /* 出参,转发报文的源地址(主机序) */
}DHCP4R_GET_CLIENTIF_S;

typedef struct tagDHCP4R_GET_CLIENTIF_BYVRF
{
    UCHAR *pPacket;         /* 入参,DHCP报文,不含IP和UDP首部,此时的Giaddr字段为网络序 */ 
    ULONG  ulOutIfIndex;    /* 出参,转发的接口索引 */
    ULONG  ulSrcIp;         /* 出参,转发报文的源地址(主机序) */
    ULONG ulVrfIndex;
}DHCP4R_GET_CLIENTIF_BYVRF_S;

/*******************************************************************************
*    Func Name: DHCP4R_GET_CLIENTIF_HOOK
* Date Created: 2011-07-06
*       Author: y00176567/z00171897
*      Purpose: 
*  Description: 注册DHCP Relay模块报文钩子,根据收到的Server报文获取转发的广播接口索引以及源地址。
*        Input: DHCP4R_GET_CLIENTIF_S *pstInfo: 收到的DHCP报文信息结构体
*       Output: 
*       Return: VOS_OK          成功
*               其它            失败
*      Caution: 1.在协议栈启动之前注册,不支持解注册
*               2.钩子函数对Giaddr字段的处理规则如下：
*                 判断Giaddr如果是OMIP，则需要返回pulOutIfIndex为背板接口索引及源IP(OMIP)；
*                 如果Giaddr不是OMIP，则返回pulOutIfIndex为0，由VISP通过Giaddr进行查找，查找则进行转发
*        Since: V2R3C05 UTRP自启动需求
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-06   y00176567      Create the first version.
*
*******************************************************************************/
typedef ULONG (*DHCP4R_GET_CLIENTIF_HOOK)(DHCP4R_GET_CLIENTIF_S *pstInfo);

/*******************************************************************************
*    Func Name: DHCP4R_GET_CLIENTIF_HOOK
* Date Created: 2013-05-23
*       Author: w00217009
*      Purpose: 
*  Description: 注册DHCP Relay模块报文钩子,根据收到的Server报文中giaddr(request报文时就改为VRRP IP了)以及
*               VrfIndex获取转发的广播接口索引以及源地址。
*        Input: DHCP4R_GET_CLIENTIF_BYVRF_S *pstInfo: 收到的DHCP报文信息结构体
*       Output: 
*       Return: VOS_OK          成功
*               其它            失败
*      Caution: 1.在协议栈启动之前注册,不支持解注册
*               2.钩子函数对Giaddr字段的处理规则如下：
*                 PTN产品根据Giaddr字段和VrfIndex查找出接口，并返回出接口索引和源地址。
*                 一级Relay,Giaddr为VRRP IP,VISP不能找到出接口,如果产品返回的出接口索引为0将丢弃报文
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-05-23   w00217009      Create the first version.
*
*******************************************************************************/
typedef ULONG (*DHCP4R_GET_CLIENTIF_BYVRF_HOOK)(DHCP4R_GET_CLIENTIF_BYVRF_S *pstInfo);

/* 注册DHCP Relay模块报文预处理钩子，由产品根据报文内容，给出Option82的选项 */
typedef struct tagDHCP4R_FORM_OPTION82
{
    ULONG ulIfIndex;   /*入参，收到的DHCP报文入接口*/
    ULONG ulGiaddr;    /*入参，报文中填充的Giaddr（主机序）*/
    DHCP4R_SUBOPTION82_S astSubOption82[2]; /*出参，Option82内容（Option82有2个子选项，不需要配置的子选项的ulSubLen字段必须设置为0）*/
}DHCP4R_FORM_OPTION82_S;

/*******************************************************************************
*    Func Name: DHCP4R_OPTION82_HOOK
* Date Created: 2011-07-06
*       Author: y00176567/z00171897
*      Purpose: 
*  Description: 注册DHCP Relay模块报文预处理钩子，由产品根据报文内容，给出Option82的选项
*        Input: DHCP4R_FORM_OPTION82_S *pstInfo: Option82结构体
*       Output: 
*       Return: VOS_OK          成功
*               其它            失败
*      Caution: 1.在协议栈启动之前注册,不支持解注册
*        Since: V2R3C05 UTRP自启动需求
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-06   y00176567      Create the first version.
*
*******************************************************************************/
typedef ULONG (*DHCP4R_OPTION82_HOOK)(DHCP4R_FORM_OPTION82_S *pstInfo);



/* API declare */
/*******************************************************************************
*    Func Name: TCPIP_DhcpRelay
*  Description: 使能DHCP Relay
*        Input: ULONG ulIfIndex: 接口索引(支持DHCP Relay的合法接口索引)或0(预配置全局配置模块)
*               ULONG ulSetYes:  使能/去使能 0- 去使能 1- 使能
*       Output: 
*       Return: DHCP4R_OK 0                 成功
*               DHCP4R_ERR_NOMEM            内存分配失败
*               DHCP4R_ERR_NO_OPERATE       操作码错误
*               DHCP4R_ERR_MODE_NO_MATCH    配置模式不匹配
*               DHCP4R_ERR_NULL_IF          接口为空
*               DHCP4R_ERR_NOSUPPORT_IF     索引对应接口不支持DHCP Relay
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK成员端口不支持DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     借用地址接口不能使能/配置DHCP Relay
*               DHCP4R_ERR_HA_IS_SMOOTHING  在平滑或手动倒换
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DhcpRelay( ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_CfgDhcprServer
*  Description: 配置RELAY中继地址
*        Input: ULONG ulOperate: 增加/删除中继地址
*               ULONG ulIndex:   接口索引(支持DHCP Relay的合法接口索引)或0(预配置全局配置模块)
*               ULONG ulServerIP: 中继地址
*       Output: 
*       Return: DHCP4R_OK 0                 成功
*               DHCP4R_ERR_NOMEM            内存分配失败
*               DHCP4R_ERR_NO_OPERATE       操作码错误
*               DHCP4R_ERR_MODE_NO_MATCH    配置模式不匹配
*               DHCP4R_ERR_NULL_IF          接口为空
*               DHCP4R_ERR_SERVER_INVALID   非法中继地址
*               DHCP4R_ERR_NOSUPPORT_IF     索引对应接口不支持DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     借用地址接口不能使能/配置DHCP Relay
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK成员端口不支持DHCP Relay
*               DHCP4R_ERR_MAX_SERVER       达到最大SERVER数了
*               DHCP4R_ERR_NO_CFG           没有进行过配置
*               DHCP4R_ERR_SERVER_EXIST     已经配置了这个IP
*               DHCP4R_ERR_SERVER_NOEXIST   没有配置此IP
*               DHCP4R_ERR_HA_IS_SMOOTHING  在平滑或手动倒换
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_CfgDhcprServer(ULONG ulOperate, ULONG ulIndex, ULONG ulServerIP);
/*******************************************************************************
*    Func Name: TCPIP_CfgOption82
*  Description: 配置82选项
*        Input: ULONG ulOperate: 增加/删除82选项
*               ULONG ulIndex:   接口索引(支持DHCP Relay的合法接口索引)或0(预配置全局配置模块)
*               ULONG ulSubCode: 子选项ID(1/2合法;删除82选项时0也合法,表示删除所有子选项)
*               ULONG ulSubLen:  子选项长度
*               UCHAR *szSubVar: 子选项值
*       Output: 
*       Return: DHCP4R_OK  0                成功
*               DHCP4R_ERR_PARAM            参数非法
*               DHCP4R_ERR_NO_OPERATE       操作码错误
*               DHCP4R_ERR_MODE_NO_MATCH    配置模式不匹配
*               DHCP4R_ERR_NULL_IF          接口为空
*               DHCP4R_ERR_NULL_POINTER     指针参数为空
*               DHCP4R_ERR_NO_CFG           没有进行过配置
*               DHCP4R_ERR_NOSUPPORT_IF     索引对应接口不支持DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     借用地址接口不能使能/配置DHCP Relay
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK成员端口不支持DHCP Relay
*               DHCP4R_ERR_82_SUBCODE       82子选项代码错误
*               DHCP4R_ERR_82_SUBLEN        82子选项长度参数错误
*               DHCP4R_ERR_82_SUB_NOCFG     没有配置此82子选项 
*               DHCP4R_ERR_HA_IS_SMOOTHING  在平滑或手动倒换
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_CfgOption82(ULONG ulOperate, ULONG ulIndex, ULONG ulSubCode, ULONG ulSubLen, UCHAR *szSubVar);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprCfg
*  Description: 获取DHCP RELAY配置情况，包括使能状态、中继地址、中继数目和OPTION82配置
*        Input: ULONG ulIndex: 接口索引。0或其他有效索引   
*               DHCP4R_CFG_INFO_S *pstDhcprCfg   
*       Output: DHCP4R_CFG_INFO_S *pstDHCP4RCfg: 输出配置信息
*       Return: DHCP4R_OK 0                 成功
*               DHCP4R_ERR_MODE_NO_MATCH    配置模式不匹配
*               DHCP4R_ERR_NULL_IF          接口为空
*               DHCP4R_ERR_NOSUPPORT_IF     索引对应接口不支持DHCP4R
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK成员端口不支持DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     借用地址接口不能使能/配置DHCP Relay
*               DHCP4R_ERR_NULL_POINTER     指针参数为空
*               DHCP4R_ERR_NO_CFG           没有在这个接口上配置
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprCfg(ULONG ulIndex, DHCP4R_CFG_INFO_S *pstDhcprCfg);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcprFwdMode
*  Description: 设置中继方式
*        Input: ULONG ulFwdMode: 中继方式 0-分担方式,1-广播方式
*       Output: 
*       Return: DHCP4R_OK 0                 成功
*               DHCP4R_ERR_PARAM            参数非法
*               DHCP4R_ERR_HA_IS_SMOOTHING  在平滑或手动倒换
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprFwdMode(ULONG ulFwdMode);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprFwdMode
*  Description: 获取DHCP Relay中继方式
*        Input: ULONG *pulFwdMode: 保存中继方式
*       Output: 
*       Return: DHCP4R_OK                   成功
*               DHCP4R_ERR_NULL_POINTER     指针参数为空
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprFwdMode(ULONG *pulFwdMode);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprStat
*  Description: 获取relay统计信息
*        Input: DHCP4R_STATINFO_S *pstDhcprStat: 保存输出的统计信息
*       Output: 
*       Return: DHCP4R_OK                   成功
*               DHCP4R_ERR_NULL_POINTER     指针参数为空
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprStat(DHCP4R_STATINFO_S *pstDhcprStat);
/*******************************************************************************
*    Func Name: TCPIP_ClrDhcprStat
*  Description: 清零Relay的统计信息
*        Input: VOID
*       Output: 
*       Return: DHCP4R_OK                   成功
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_ClrDhcprStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcprMaxHops
*  Description: 设置relay最大中继跳数
*        Input: ULONG ulhops: 跳数,1~16
*       Output: 
*       Return: DHCP4R_OK 0                 成功
*               DHCP4R_ERR_PARAM            参数非法
*               DHCP4R_ERR_HA_IS_SMOOTHING  在平滑或手动倒换
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprMaxHops(ULONG ulhops);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprMaxHops
*  Description: 获取最大中继跳数
*        Input: ULONG *pulhops: 保存输出的中继跳数
*       Output: 
*       Return: DHCP4R_OK                   成功
*               DHCP4R_ERR_NULL_POINTER     指针参数为空
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprMaxHops(ULONG *pulhops);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcprTos
*  Description: 设置relay socket TOS
*        Input: UCHAR ucTos: tos值，值域有效
*       Output: 
*       Return: DHCP4R_OK 0                 成功
*               DHCP4R_ERR_HA_IS_SMOOTHING  在平滑或手动倒换
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprTos(UCHAR ucTos);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprTos
*  Description: 获取tos
*        Input: UCHAR *pucTos: 保存输出的tos
*       Output: 
*       Return: DHCP4R_OK                   成功
*               DHCP4R_ERR_NULL_POINTER     指针参数为空
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprTos(UCHAR *pucTos);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcpDebug
*  Description: 设置RELAY调试开关
*        Input: ULONG ulOperate:  0或1，0表示清除调试开关，1表示设置调试开关
*               ULONG ulIndex: 0或有效接口索引,0表示设置全局调试开关;其他表示设置对应接口的调试开关
*               ULONG ulDebugLevel: 调试级别1－packet调试开关,2－err调试开关,3－all(packet和err调试开关)
*       Output: 
*       Return: DHCP4R_OK 0                 成功
*               DHCP4R_ERR_PARAM            参数非法
*               DHCP4R_ERR_NOMEM            没有内存
*               DHCP4R_ERR_NO_OPERATE       操作码错误
*               DHCP4R_ERR_NULL_IF          接口为空
*               DHCP4R_ERR_NOSUPPORT_IF     索引对应接口不支持DHCP4R
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK成员端口不支持DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     借用地址接口
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpDebug(ULONG ulOperate, ULONG ulIndex, ULONG ulDebugLevel);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpDebug
*  Description: 获取调试开关状态
*        Input: ULONG ulIndex: 接口索引。0或其他有效索引
*       Output: ULONG *pulDebug: 保存调试参数的变量指针
*       Return: DHCP4R_OK 0                 成功
*               DHCP4R_ERR_NULL_IF          接口为空
*               DHCP4R_ERR_NOSUPPORT_IF     索引对应接口不支持DHCP4R
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK成员端口不支持DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     借用地址接口不能使能/配置DHCP Relay
*               DHCP4R_ERR_NULL_POINTER     指针参数为空
*               DHCP4R_ERR_NO_CFG           没有配置
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpDebug(ULONG ulIndex, ULONG *pulDebug);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcprHADbg
*  Description: 设置DHCP4R ha调试开关
*        Input: ULONG ulDbg: 开关状态 1-open;0-close
*       Output: 
*       Return: VOS_OK                      设置成功
*               VOS_ERR                     设置失败
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprHADbg
*  Description: 获取dhcp4r ha调试开关状态
*        Input: ULONG* pulDbg: 保存输出的ha调试开关状态
*       Output: 
*       Return: VOS_OK                      获取成功
*               VOS_ERR                     获取失败(指针参数为空)
*               DHCP4R_ERR_NOT_REGISTER     DHCP4R模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprHADbg(ULONG* pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcp4rStatistic
*  Description: 显示DHCP4R模块统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowDhcp4rStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowDhcp4rStatisticByVrf
* Date Created: 2008-3-8
*       Author: LY(57500)
*  Description: 显示DHCP4R模块统计信息
*        Input: ULONG ulVrfIndex:vrf索引
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
VOID TCPIP_ShowDhcp4rStatisticByVrf(ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4RGetSrcAddrHook
* Date Created: 2008-12-14
*       Author: z43740
*  Description: 注册获取Relay请求报文源地址回调函数
*        Input: DHCP4R_GET_SRCADDR_HOOK pfHook: 回调函数指针
*       Output: 
*       Return: VOS_OK                  注册成功
*               DHCP4R_ERR_NULL_POINTER 函数指针为空
*      Caution: 注册后不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-14   z43740                  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4RGetSrcAddrHook(DHCP4R_GET_SRCADDR_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RelayEnableByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 使能VRF或VRF实例下的接口Relay功能
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulIfIndex:接口索引(0:基于VRF的全局实例)
*               ULONG ulEnable:1:使能，0:去使能
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RelayEnableByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG ulEnable);

/*******************************************************************************
*    Func Name: TCPIP_CfgServerByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 配置RELAY中继地址
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulOperate:增加/删除中继地址
*               ULONG ulIfIndex:接口索引(支持DHCP Relay的合法接口索引)或0(预配置全局配置模块)
*               ULONG ulServerIP:中继地址
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgDhcprServerByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, ULONG ulServerIP);

/*******************************************************************************
*    Func Name: TCPIP_CfgOption82ByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 配置82选项
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulOperate:增加/删除82选项
*               ULONG ulIfIndex:接口索引(支持DHCP Relay的合法接口索引)或0(预配置全局配置模块)
*               ULONG ulSubCode:子选项ID(1/2合法;删除82选项时0也合法,表示删除所有子选项)
*               ULONG ulSubLen:子选项长度
*               UCHAR *szSubVar:子选项值
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgDhcprOption82ByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, 
                                  ULONG ulSubCode, ULONG ulSubLen, UCHAR *szSubVar);

/*******************************************************************************
*    Func Name: TCPIP_GetCfgByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 获取DHCP RELAY配置情况，包括VRF索引值、使能状态、中继地址、
*               中继数目和OPTION82配置
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulIfIndex:接口索引。0或其他有效索引
*               
*       Output: DHCP4R_CFG_INFO_S *pstDHCP4RCfg:输出配置信息
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprCfgByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, DHCP4R_CFG_INFO_S *pstDHCP4RCfg);

/*******************************************************************************
*    Func Name: TCPIP_SetFwdModeByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF索引值设置中继方式
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulFwdMode:中继方式 0-分担方式,1-广播方式
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprFwdModeByVrf(ULONG ulVrfIndex, ULONG ulFwdMode);

/*******************************************************************************
*    Func Name: TCPIP_GetFwdModeByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF获取中继方式
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG *pulMode:中继方式 0-分担方式,1-广播方式
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprFwdModeByVrf(ULONG ulVrfIndex, ULONG *pulFwdMode);

/*******************************************************************************
*    Func Name: TCPIP_GetStatisticsByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF索引值获取统计信息
*        Input: ULONG ulVrfIndex:VRF索引值
*               DHCP4R_STATINFO_S *pstDHCP4RStat:获取统计信息
*       Output: DHCP4R_STATINFO_S *pstDHCP4RStat:获取统计信息
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprStatisticsByVrf(ULONG ulVrfIndex, DHCP4R_STATINFO_S *pstDHCP4RStat);

/*******************************************************************************
*    Func Name: TCPIP_ClearStatisticsByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF清空Relay统计信息
*        Input: ULONG ulVrfIndex:VRF索引值
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID TCPIP_ClearDhcprStatisticsByVrf(ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetMaxHopsByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF索引值设置relay最大中继跳数
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulhops:跳数,1~16
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprMaxHopsByVrf(ULONG ulVrfIndex, ULONG ulMaxHops);

/*******************************************************************************
*    Func Name: TCPIP_GetMaxHopsByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF索引值获取Relay最大中继跳数
*        Input: ULONG ulVrfIndex:VRF索引值
*       Output: ULONG *pulhops:最大跳数
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprMaxHopsByVrf(ULONG ulVrfIndex, ULONG *pulMaxHops);

/*******************************************************************************
*    Func Name: TCPIP_SetTosByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF索引值设置TOS值
*        Input: ULONG ulVrfIndex:VRF索引值
*               UCHAR ucTos:设置的TOS值
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprTosByVrf(ULONG ulVrfIndex, UCHAR ucTos);

/*******************************************************************************
*    Func Name: TCPIP_GetTosByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF索引值获取对应的TOS值
*        Input: ULONG ulVrfIndex:VRF索引值
*               
*       Output: UCHAR *pucTos:获取的TOS值
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprTosByVrf(ULONG ulVrfIndex, UCHAR *pucTos);

/*******************************************************************************
*    Func Name: TCPIP_SetDebugByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF索引值设置调试开关
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulOperate:0或1，0表示清除调试开关，1表示设置调试开关
*               ULONG ulIfIndex:0或有效接口索引,0表示设置全局调试开关;其他表示设置对应接口的调试开关
*               ULONG ulDebugLevel: 调试级别1－packet调试开关,2－err调试开关,3－all(packet和err调试开关)
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprDebugByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, ULONG ulDebugLevel);

/*******************************************************************************
*    Func Name: TCPIP_GetDebugByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: 根据VRF索引值获取调试开关状态
*        Input: ULONG ulVrfIndex: VRF索引值
*               ULONG ulIfIndex: 接口索引。0或其他有效索引
*       Output: ULONG *pulDebug: 保存调试参数的变量指针
*       Output: 
*       Return: 成功或失败(错误码)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprDebugByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG *pulDbgLevel);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4RProcRequestHook
* Date Created: 2011-06-28
*       Author: y00176567/z00171897
*      Purpose: 
*  Description: 注册DHCP Relay模块报文预处理钩子,由产品完成所收到的DHCP Request报文的预处理过程
*        Input: DHCP4R_PROC_REQUEST_HOOK pfHook:回调函数指针
*       Output: 
*       Return: VOS_OK          注册成功
*               其它            失败
*      Caution: 在协议栈启动之前注册,不支持解注册
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-28   y00176567      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4RProcRequestHook(DHCP4R_PROC_REQUEST_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4RGetGiaddrListHook
* Date Created: 2013-09-27
*       Author: l00213099
*      Purpose: 
*  Description: 注册DHCP Relay模块获取Giaddr处理钩子,由产品完成由报文信息获取Giaddr列表处理过程
*        Input: DHCP4R_GET_GIADDR_HOOK pfHook:回调函数指针
*       Output: 
*       Return: DHCP4R_OK       注册成功
*               其它            失败
*      Caution: 在协议栈启动之前注册,不支持解注册
*        Since: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-27   l00213099      Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncDHCP4RGetGiaddrListHook(DHCP4R_GET_GIADDR_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4RProcReplyHook
* Date Created: 2011-06-28
*       Author: y00176567/z00171897
*      Purpose: 
*  Description: 注册DHCP Relay模块报文预处理钩子,由产品完成所收到的DHCP Reply报文的预处理过程
*        Input: DHCP4R_PROC_REPLY_HOOK pfHook:回调函数指针
*       Output: 
*       Return: VOS_OK          注册成功
*               其它            失败
*      Caution: 在协议栈启动之前注册,不支持解注册
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-28   y00176567/z00171897     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4RProcReplyHook(DHCP4R_PROC_REPLY_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4RGetClientIfHook
* Date Created: 2011-06-28
*       Author: y00176567/z00171897
*      Purpose: 
*  Description: 注册DHCP Relay模块报文处理钩子,
                根据收到的Server报文的Giaddr获取转发的广播接口索引以及源地址
*        Input: DHCP4R_GET_CLIENTIF_HOOK  pfHook: 回调函数指针
*       Output: 
*       Return: VOS_OK          注册成功
*               其它            失败
*      Caution: 在协议栈启动之前注册,不支持解注册
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-28   y00176567/z00171897      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4RGetClientIfHook(DHCP4R_GET_CLIENTIF_HOOK  pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4ROption82Hook
* Date Created: 2011-06-28
*       Author: y00176567y00176567
*      Purpose: 
*  Description: 注册DHCP Relay模块报文预处理钩子,由产品根据报文内容,给出Option82的选项
*        Input: DHCP4R_OPTION82_HOOK  pfHook: 回调函数指针
*       Output: 
*       Return: VOS_OK          注册成功
*               其它            失败
*      Caution: 在协议栈启动之前注册,不支持解注册
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-28   y00176567y00176567      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4ROption82Hook(DHCP4R_OPTION82_HOOK pfHook);
/*******************************************************************************
*    Func Name: TCPIP_SetDHCP4RMultiRelaySwitch
* Date Created: 2011-07-03
*       Author: zhaoyue00171897/yangheng00176567
*  Description: 设置多级Relay开关,以进入产品定制的二级Relay处理流程
*        Input: ULONG ulSwitch:开关状态 0 关闭  其他 打开
*       Output: 
*       Return: DHCP4R_OK   成功
*               其他        失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-03   z171897/y176567         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDHCP4RMultiRelaySwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetDHCP4RMultiRelaySwitch
* Date Created: 2011-07-03
*       Author: zhaoyue00171897/yangheng00176567
*  Description: 获取在DHCP Relay上多级Relay开关的状态
*        Input: 
*       Output: ULONG *pulSwitch:开关状态
*       Return: DHCP4R_OK   成功
*               其他        失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-03   z171897/y176567         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDHCP4RMultiRelaySwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcp4rOpt82ModeByVrf
* Date Created: 2011-04-17
*       Author: luogaowei61496
*  Description: 针对使能DHCP Relay的接口设置82选项的处理模式
*               不修改DHCP Client 的82选项 或者替换为 Relay 的选项
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulIfIndex: 使能DHCP Relay的接口索引值
*               ULONG ulMode:  82选项的处理模式
*                     (0:不修改Client 82选项，1:替换 client 82选项)
*       Output: 
*       Return: 
*               DHCP4R_OK  0                成功
*               其他错误码
*      Caution: 默认为保留client的82选项
*              #define DHCP4R_OPT82_MODE_HOLD    0  保留client的82选项参数
*              #define DHCP4R_OPT82_MODE_MODIFY  1  修改或者添加 client 的82选项参数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-04-17   luogaowei61496          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcp4rOpt82ModeByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, 
                                                ULONG ulMode);


/*******************************************************************************
*    Func Name: TCPIP_GetDhcp4rOpt82ModeByVrf
* Date Created: 2011-04-17
*       Author: luogaowei61496
*  Description: 获取指定接口设置82选项的处理模式
*        Input: ULONG ulVrfIndex:VRF索引值
*               ULONG ulIfIndex: 使能DHCP Relay的接口索引值
*                     (0:不修改Client 82选项，1:替换 client 82选项)
*       Output: ULONG *pulMode:  82选项的处理模式
*       Return: 
*               DHCP4R_OK  0                成功
*               其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-04-17   luogaowei61496          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcp4rOpt82ModeByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, 
                                                ULONG   *pulMode);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4RGetClientIfByVrfHook
* Date Created: 2013-05-23
*       Author: w00217009
*      Purpose: 
*  Description: 注册DHCP Relay模块报文处理钩子,
*               根据收到的Server报文的Giaddr和VrfIndex获取转发的广播接口索引以及源地址
*               针对报文中Giaddr已经是VRRP IP，即不是本接口的地址的场景
*        Input: DHCP4R_GET_CLIENTIF_BYVRF_HOOK  pfHook: 回调函数指针
*       Output: 
*       Return: DHCP4R_OK       注册成功
*               其它            失败
*      Caution: 在协议栈启动之前注册,不支持解注册
*        Since: V3R1C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-05-23   w00217009      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4RGetClientIfByVrfHook(DHCP4R_GET_CLIENTIF_BYVRF_HOOK  pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4RGetSrcAddrBySvrIpHook
* Date Created: 2014-04-16
*       Author: likaikun213099
*  Description: 注册获取Relay请求报文源地址回调函数
*        Input: DHCP4R_GET_SRCADDR_BY_SVRIP_HOOK pfHook: 回调函数指针
*       Output: 
*       Return: VOS_OK                  注册成功
*               DHCP4R_ERR_NULL_POINTER 函数指针为空
*      Caution: 注册后不能注销，与TCPIP_RegFuncDHCP4RGetSrcAddrHook相比，
*               需要sever IP信息
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-16   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4RGetSrcAddrBySvrIpHook(DHCP4R_GET_SRCADDR_BY_SVRIP_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_SetDHCP4RTaskScheduleTime
* Date Created: 2014-05-21
*       Author: likaikun213099
*  Description: 设置DHCP4R的调度开关及流量时间参数
*        Input: ULONG ulSwitch:
*               ULONG ulPacketProCount:
*               ULONG ulDR4DelayTime:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-21   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDHCP4RTaskScheduleTime(ULONG ulSwitch, ULONG ulPacketProCount,ULONG ulDR4DelayTime);

/*******************************************************************************
*    Func Name: TCPIP_GetDHCP4RTaskScheduleTime
* Date Created: 2014-06-7
*       Author: fengjing209023
*  Description: 获取DHCP4R的调度开关及流量时间参数
*       Output: ULONG *pulSwitch: 开关
*               ULONG *pulPacketProCount:每次处理报文个数
*               ULONG *pulDR4DelayTime:主动延迟时间
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-06-7   fengjing209023          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDHCP4RTaskScheduleTime(ULONG *pulSwitch, ULONG *pulPacketProCount,ULONG *pulDR4DelayTime);

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _DHCP4R_API_H_    */

