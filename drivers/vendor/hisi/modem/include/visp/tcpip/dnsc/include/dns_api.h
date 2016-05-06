/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_api.h
*
*  Project Code: VISPV1R7
*   Module Name: dns
*  Date Created: 2008-03-09
*        Author: wuhailan
*   Description: dns用户API接口文件,该头文件涉及到IPV6的地址数据结构VRP_IN6ADDR_S,需要先包含IPV6头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
/**
*@defgroup dnsclient DNS_CLIENT
*@ingroup app
*/

#ifndef _DNS_API_H_
#define _DNS_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 *@ingroup dnsclient
 *@brief DNS CLIENT宏定义
 *@{
*/
#ifndef DNS_DOMAIN_LIST_NAME_LENGTH
#define DNS_DOMAIN_LIST_NAME_LENGTH 20  /**< 域名列表中域名的最大长度 */
#endif

/*
根据rfc882文档的描述，如下:
To simplify implementations, the total number of octets that
represent label octets and label lengths is limited to 255.  Thus
a printed domain name can be up to 254 characters.

定义VISP支持DNS域名最大长度为254
*/
#define DNS_DOMAIN_NAME_LENGTH 254  /**< 域名最大长度 */

#define DNS_DOMAIN_LIST_NUM         10  /**< 域名列表中域名的最大个数 */

#define DNS_DOMAIN_SERVER_NUM        6  /**< 域名服务器的最大个数 */

#define DNS_MAX_INTERFACE_NAME_LEN  47  /**< 接口名长度,与MAX_INTERFACE_NAME_LEN值一样,若有改动需要同步更新*/

/*设置DNS域名服务器中使用的宏值*/
#define DNS_ADD_SERVER_IP      0  /**< 表示增加指定域名服务器地址 */
#define DNS_DEL_SERVER_IP      1  /**< 表示删除指定域名服务器地址 */
#define DNS_DEL_ALL_SERVER_IP  2  /**< 表示删除全部域名服务器地址 */
/**@}*/

/**
 *@ingroup dnsclient
 *@brief IPv6地址
*/
#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef struct tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif

/**
 *@ingroup dnsclient
 *@brief DNS域名信息中IPV6相关的结构信息。
*/
typedef struct tagTCPIP_IPV6_DNS_SERVADDRINFO
{
    VRP_IN6ADDR_S stIpAddr;
    ULONG         ulIfIndex;
    CHAR          szInterfaceName[DNS_MAX_INTERFACE_NAME_LEN + 1];
}TCPIP_IPV6_DNS_SERVADDRINFO_S;

/*dns域名信息结构,与DomainInfo_S结构一致，如有修改，要求同步修改*/
/**
 *@ingroup dnsclient
 *@brief DNS域名信息结构
*/
typedef struct  tagTCPIP_DomainInfo
{
     ULONG  ulDomainServer[DNS_DOMAIN_SERVER_NUM];
     TCPIP_IPV6_DNS_SERVADDRINFO_S stDomainServer6[DNS_DOMAIN_SERVER_NUM];
     CHAR   szDomainList[DNS_DOMAIN_LIST_NUM][DNS_DOMAIN_LIST_NAME_LENGTH + 1];
     UCHAR  ucPadding[2];
}TCPIP_DomainInfo_S;


/*dns模块错误码定义*/
/*注意:如果修改错误码，请同步修改dns_sh_info.c 文件中的CHAR *Inf_Dnsc_En[]描述信息*/
/**
 *@ingroup dnsclient
 *@brief DNS CLIENT错误码
*/
enum enum_DnsErr_INFO
{
    /* success */
    DNSC_SUCCESS       = 0,                  /**< 0 成功*/

    /* error code */
    DNS_INVALID_V4_ADDR,                     /**< 1 无效的IPV4服务器地址 */
    DNS_INVALID_V6_ADDR,                     /**< 2 无效的IPV6服务器地址 */
    DNS_UNSPECIFIED_ADDR,                    /**< 3 */
    DNS_MULTICAST_ADDR,                      /**< 4 */
    DNS_NO_DOMAIN_SERVER,                    /**< 5 */
    DNS_ILLEGAL_V6_SERVER_ADDR,              /**< 6 */
    DNS_ILLEGAL_INTF_NAME,                   /**< 7 */
    DNS_TOO_MANY_SERVERS,                    /**< 8 */
    DNS_EXISTING_SERVER,                     /**< 9 */
    DNS_SPECIFY_INTF_NAME,                   /**< 10 */
    DNS_INVALID_INTF_NAME,                   /**< 11 */
    DNS_INVALID_DOMAIN_NAME,                 /**< 12，域名无效，可能过长或长度为0或含有非法字符 */
    DNS_NO_DOMAIN_NAME,                      /**< 13 */
    DNS_TOO_MANY_DOMAINS,                    /**< 14 */
    DNS_EXISTING_DOMAIN,                     /**< 15 */

    /* info code */
    DNS_V4_SERVERS,                          /**< 16 */
    DNS_DOMAIN_SERVER,                       /**< 17 */
    DNS_IP_ADDR,                             /**< 18 */
    DNS_NO_SERVERS,                          /**< 19 */
    DNS_V6_SERVERS,                          /**< 20 */
    DNS_IPv6_ADDR,                           /**< 21 */
    DNS_INTF_NAME,                           /**< 22 */
    DNS_NO,                                  /**< 23 */
    DNS_DOMAIN_NAME,                         /**< 24 */
    DNS_TTL,                                 /**< 25 */
    DNS_ALIAS,                               /**< 26 */
    DNS_STOP_SEARCH,                         /**< 27 */
    DNS_TRY_SERVER,                          /**< 28 */
    DNS_NO_FIRST,                            /**< 29 */

    /**< error code */
    DNS_NULL_POINTER,                        /**< 30, 空指针参数. */
    DNS_ERR_WAITLIST,                        /**< 31, 对waitlist register/unregister操作失败*/
    DNS_ERR_SETWAITLIST,                     /**< 32, 对waitlist SET操作失败*/
    DNS_ERR_GETWAITLIST,                     /**< 33, 对waitlist GET操作失败*/
    DNS_LEN_DOMAIN_NAME,                     /**< 34，域名无效,域名过长*/
    DNS_LEN_INTF_NAME,                       /**< 35，IFNET名字过长*/
    DNS_ADD_IPV6_INTF_NAME,                  /**< 36，增加 ipv6 Domain Setver地址不合法*/
    DNS_DEL_IPV6_INTF_NAME,                  /**< 37，删除 ipv6 Domain Setver地址不合法*/
    DNS_V6_TOO_MANY_SERVERS,                 /**< 38，IPV6 服务器过多*/
    DNS_V4_TOO_MANY_SERVERS,                 /**< 39，IPV4 服务器过多*/
    DNS_TOO_MANY_SERVERS_FORLINT,            /**< 40，IPV4 服务器过多 for pclint*/
    DNS_DEL_V6_NO_DOMAIN_SERVER,             /**< 41,  删除V6 DOMAIN SEVER不存在*/
    DNS_V6_EXISTING_SERVER,                  /**< 42,  添加V6服务器存在.add by z62474 for A82D20453*/

    DNS_API_COM_NULL,                        /**< 43, DNS组件为空*/
    DNS_API_PARA_WRONG,                      /**< 44, 存入参数错误*/
    DNS_API_POINTER_NULL,                    /**< 45, 指针参数为空*/

    DNS_LEN_DOMAIN_LABEL,                    /**< 46, 域名Label过长 */
    DNS_API_IPV6ADDR_WRONG = 47,             /**< 47, 存入IPv6地址错误*/
    DNS_API_IPV4ADDR_WRONG,                  /**< 48, 存入IPv4地址错误*/
};
/*注意:如果修改错误码，请同步修改dns_sh_info.c 文件中的CHAR *Inf_Dnsc_En[]描述信息*/

/* 根据DNS server IP地址获取需要绑定的源IP地址, server IP地址和源IP地址均为主机序 */
/**
 *@ingroup dnsclient
 *@brief 根据DNS server IP地址获取需要绑定的源IP地址钩子函数。
 *
 *@par 描述:
 *在发送DNS请求报文时，根据DNS server IP地址获取需要绑定的源IP地址钩子函数。
 *
 *@attention
 *无
 *
 *@param ulDnsServerIP [IN] DNS服务器IP地址，主机序。32位无符号整数
 *
 *@retval VOS_OK 0    成功
 *@retval 其它    非0  失败，产品返回错误码
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_RegFuncDNSCGetSrcIPHook
*/
typedef ULONG (*DNSCGetSrcIPHOOK)(ULONG ulDnsServerIP);

/**
 *@ingroup dnsclient
 *@brief 清空DNS的主机域名缓存表接口。
 *
 *@par 描述:
 *清空DNS的主机域名缓存表接口。
 *
 *@attention
 *无
 *
 *@param ulProtocolFlag [IN] AF_INET(2) 或 AF_INET6(29)，其他输入相当于无效参数，不作非法性检查。
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_GetDnsDomainList
*/
extern ULONG TCPIP_ClrDnsDynamicHost(ULONG ulProtocolFlag);

/**
 *@ingroup dnsclient
 *@brief 获取DNS域名后缀列表信息。
 *
 *@par 描述:
 *获取DNS域名后缀列表信息。
 *
 *@attention
 *无
 *
 *@param pstDomainInfo [OUT] 存放列表的指针。非空指针
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_SetDnsDomainSuffix
*/
extern ULONG TCPIP_GetDnsDomainList(TCPIP_DomainInfo_S *pstDomainInfo);

/**
 *@ingroup dnsclient
 *@brief 域名解析接口。
 *
 *@par 描述:
 *域名解析接口。
 *
 *@attention
 *这里的域名长度（不包括最后的'.'字符）应该不大于254，这个长度包括域名后缀，即包括域名后缀的完整域名长度应该不大于254。
 *
 *@param pcDNSName [IN] 预解析的域名。要解析的域名信息长度不超过254。非空指针
 *@param pulIPAddr [OUT] 返回的解析好的IP地址指针。非空指针
 *@param ulIPV6Flag [IN] IPV6标记，0表示IPV4,非0表示IPV6。32位无符号整型
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_SetDnsServer
 *@see TCPIP_SetDnsDomainSuffix
*/
extern ULONG TCPIP_GetDnsHost(CHAR *pcDNSName, VOID *pulIPAddr, ULONG ulIPV6Flag);

/**
 *@ingroup dnsclient
 *@brief 获得域名服务器列表接口。
 *
 *@par 描述:
 *获得域名服务器列表接口。
 *
 *@attention
 *无
 *
 *@param pstDomainInfo [OUT] 存放列表的指针。非空指针
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_SetDnsServer
*/
extern ULONG TCPIP_GetDnsServer(TCPIP_DomainInfo_S * pstDomainInfo);

/**
 *@ingroup dnsclient
 *@brief 设置DNS域名前缀列表接口。
 *
 *@par 描述:
 *设置DNS域名前缀列表接口。
 *
 *@attention
 *无
 *
 *@param ulNoFlag [IN] 表示增加还是删除域名后缀；非0表示删除，0表示增加。32位无符号整型
 *@param pstDomainName [IN] 域名后缀信息。域名的最大长度为20。非空指针
 *@param ulDomainNameFlag [IN] 当ulNoFlag=1且ulDomainNameFlag=0时，删除全部域名后缀，其它情况此参数没有作用。32位无符号整型
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_GetDnsDomainList
 *@see TCPIP_ClrDnsDynamicHost
*/
extern ULONG TCPIP_SetDnsDomainSuffix(ULONG ulNoFlag,
                                      CHAR  *pstDomainName,
                                      ULONG ulDomainNameFlag);

/**
 *@ingroup dnsclient
 *@brief 设置DNS域名服务器。
 *
 *@par 描述:
 *设置DNS域名服务器。
 *
 *@attention
 *无
 *
 *@param ulOpMode [IN] 操作码。0表示增加指定域名服务器地址；1表示删除指定域名服务器地址；2表示删除全部域名服务器地址。
 *@param pstServerIP [IN] 服务器IP地址串。非空指针
 *@param ulIPV6Flag [IN] IPV6标记,0表示IPV4,非0表示IPV6。32位无符号整型
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_GetDnsServer
*/
extern ULONG TCPIP_SetDnsServer(ULONG ulOpMode, CHAR *pstServerIP, ULONG ulIPV6Flag);

/**
 *@ingroup dnsclient
 *@brief 显示本机上的DNS相关信息接口。
 *
 *@par 描述:
 *显示本机上的DNS相关信息接口：包括本机上的域名缓存信息、DNS Server信息及域名后缀信息。
 *
 *@attention
 *无
 *
 *@param 无
 *
 *@retval 无
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see 无
*/
extern VOID TCPIP_ShowDnsInfo(VOID);

/**
 *@ingroup dnsclient
 *@brief 设置DNS调试开关。
 *
 *@par 描述:
 *设置DNS调试开关。
 *
 *@attention
 *无
 *
 *@param ulswitch [IN] 调试开关设置值。0 打开，1 关闭。
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_GetDNSDebugSwitch
*/
extern ULONG TCPIP_SetDNSDebugSwitch(ULONG ulswitch);

/**
 *@ingroup dnsclient
 *@brief 获取DNS调试开关。
 *
 *@par 描述:
 *获取DNS调试开关。
 *
 *@attention
 *无
 *
 *@param pulswitch [OUT] 返回的调试开关值，0 打开，1 关闭。非空指针
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_SetDNSDebugSwitch
*/
extern ULONG TCPIP_GetDNSDebugSwitch(ULONG *pulswitch);

/**
 *@ingroup dnsclient
 *@brief 设置DNSC模块全局TOS。
 *
 *@par 描述:
 *设置DNSC模块全局TOS。
 *
 *@attention
 *只对DNSC4生效，对DNSC6无效（无意义）。
 *
 *@param ucTos [IN] 设置DNSC TOS值，值域有效。
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_GetDnsTos
*/
extern ULONG TCPIP_SetDnsTos(UCHAR ucTos);

/**
 *@ingroup dnsclient
 *@brief 获取DNSC 模块全局TOS。
 *
 *@par 描述:
 *获取DNSC 模块全局TOS。
 *
 *@attention
 *无
 *
 *@param pucTos [OUT] 保存获取DNSC TOS值。非空指针
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see TCPIP_SetDnsTos
*/
extern ULONG TCPIP_GetDnsTos(UCHAR *pucTos);

/**
 *@ingroup dnsclient
 *@brief 注册根据DNS server的IP地址获取DNS域名解析请求报文的源地址的回调函数。
 *
 *@par 描述:
 *注册根据DNS server的IP地址获取DNS域名解析请求报文的源地址的回调函数。
 *
 *@attention
 *该回调函数需要在协议栈启动前注册，注册后不能注销。
 *
 *@param pfHook [IN] 注册的函数指针。非空指针
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@see DNSCGetSrcIPHOOK
*/
extern ULONG TCPIP_RegFuncDNSCGetSrcIPHook(DNSCGetSrcIPHOOK pfHook);


/**
 *@ingroup dnsclient
 *@brief 设置DNS兼容开关。
 *
 *@par 描述:
 *设置DNS兼容开关。
 *
 *@attention
 *NA
 *
 *@param ulSwitch [IN] 兼容开关值。[0, 1]，0-去使能，1-使能
 *
 *@retval VOS_OK  0 成功
 *@retval VOS_ERR 1 失败
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@since V300R002C20
 *@see TCPIP_GetDnsCompatibleSwitch
*/
ULONG TCPIP_SetDnsCompatibleSwitch(ULONG ulSwitch);


/**
 *@ingroup dnsclient
 *@brief 获取DNS兼容开关设置值。
 *
 *@par 描述:
 *获取DNS兼容开关设置值。
 *
 *@attention
 *NA
 *
 *@param pulSwitch [OUT] 指向获取到的兼容开关值的指针。非空指针，指向值取值[0, 1]，0-去使能，1-使能
 *
 *@retval #DNSC_SUCCESS 0    成功
 *@retval 其它          非0  失败，参考enum_DnsErr_INFO
 *
 *@par 依赖:
 *@li dns_api.h:该接口声明所在文件。
 *@li tcpip_dnsc.lib:该接口所依赖库文件。　
 *
 *@since V300R002C20
 *@see TCPIP_SetDnsCompatibleSwitch
*/
ULONG TCPIP_GetDnsCompatibleSwitch(ULONG *pulSwitch);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _DNS_API_H_ */

