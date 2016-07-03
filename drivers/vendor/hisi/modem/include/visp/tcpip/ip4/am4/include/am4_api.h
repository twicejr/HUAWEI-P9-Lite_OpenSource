
#ifndef __AM4_API_H__
#define __AM4_API_H__

#ifdef __cplusplus
extern "C"{
#endif

/*挪自am4_core.h*/
#define MAXADDR_ON_ONEIF    48
#define IPADDR_ADD 1
#define IPADDR_DEL 0
#define CFG_SECONDARY_IPADDR 0
#define CFG_PRIMARY_IPADDR 1
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define MAXADDR_DESCRIPTION_LEN 47
#define IP4_MAX_VRFNAME_LENGTH 31
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define RTM_NEWADDRESS      0x20    /* IP层汇报本地接口的地址*/
#define RTM_DELADDRESS      0x40    /* IP层删除本地接口的地址*/
#define RM_IM_MSG_ADDIP     RTM_NEWADDRESS  /* New address configured */
#define RM_IM_MSG_DELIP     RTM_DELADDRESS  /* address deleted */

#define RM_IM_STATE_PRIMARY     0x0008  /* It's the address configured on an physical interface without 
                                           "secondary" keyword. */
#define RM_IM_STATE_BORROW      0x0010  /* Contrary to the above */

#define INVALID_VRF             0xffffffff
typedef struct tagINADDR
{
    ULONG s_ulAddr;
}INADDR_S;

typedef struct tagTCPIP_IPIFADDR
{    
    struct tagINADDR ia_stAddr;
    /* net info */
    struct tagINADDR ia_stNet;
    struct tagINADDR ia_stNetMask;
    struct tagINADDR ia_stNetBroadcast;
    /* subnet info */
    struct tagINADDR ia_stSubnet;
    struct tagINADDR ia_stSubnetMask;
    struct tagINADDR ia_stSubnetBroadcast;
    /* dst info */
    struct tagINADDR ia_stDstAddr;
    /*Modify for BC3D00792,DR.137支持全局地址链遍历*/
    ULONG  ulIpIfIndex;
    ULONG  ulIsMainIp;
    /* add  for api TCPIP_GetAddrTable*/
    ULONG  ulIfIndex;
} TCPIP_IPIFADDR_S;

typedef struct tagIpAm4IfAddr
{
    ULONG ulAddrNum;
    ULONG ipif_address[MAXADDR_ON_ONEIF];
    ULONG ipif_mask[MAXADDR_ON_ONEIF];
}IP_AM4_IF_ADDR_S;

/* AM4配置返回错误号，同时作为模块中英文信息宏下标 
请注意同步修改 am4_sh_info.c文件中CHAR * ErrInf_AM4_En[]描述信息*/
enum enum_IP_AM4_ERR
{
    ERR_AM4_OK = 0,                          /* 0 success */
    ERR_AM4_NOPRIADDR,                       /* 1 主地址不存在 */
    ERR_AM4_DELSECBFPRI,                     /* 2 删除主地址之前必须先删除从地址 */
    ERR_AM4_INVALIDADDR,                     /* 3 无效地址 */
    ERR_AM4_NOSECADDR,                       /* 4 该从地址不存在 */
    ERR_AM4_SECPRIISSAME,                    /* 5 从地址不能与主地址相同 */
    ERR_AM4_ADDREXIST,                       /* 6 该地址已经存在 */
    ERR_AM4_SECFAIL,                         /* 7 只有配置了主地址,才能配置从地址 */
    ERR_AM4_MAX,                             /* 8 超过最大地址数 */
    ERR_AM4_INVALIDLENDIN,                   /* 9 无效的借出接口 */
    ERR_AM4_ADDRCONFLICT,                    /* 10 地址冲突 */
    ERR_AM4_INVALIDIN,                       /* 11 输入参数不合法 */
    ERR_AM4_CANTNONEGO,                      /* 12 未配置协商地址，不能取消 */
    ERR_AM4_INVALIDBRIN,                     /* 13 无效的借入接口 */
    ERR_AM4_CANTUSEUNIN,                     /* 14 借用到的地址不能转借 */
    ERR_AM4_CANTNOUNNUMBER,                  /* 15 未设置地址借用，不能取消 */
    ERR_AM4_INVALIDMAC,                      /* 16 无效的physical地址 */
    ERR_AM4_NOARPENTRY,                      /* 17 没有这个ARP项 */
    ERR_AM4_ARPMAX,                          /* 18 ARP项目数已经达到最大值 */
    ERR_AM4_MALLOCFAIL,                      /* 19 内存分配失败 */
    ERR_AM4_WRONGCOMMAND,                    /* 20 命令字不合法 */
    ERR_AM4_NOT_IN_ONEVPN,                   /* 21 借用接口VRF和被借用接口VRF不是同一个*/
    ERR_AM4_NOVRF,                           /* 22 指定的VPN实例不存在或VPN实例没有配置Route-Distinguisher */
                                             
    ERR_AM4_VRRP,                            /* 23 某些不合法的虚拟地址已被删除 */
    ERR_AM4_VRRP_EQUAL_VRITUAL_IP,           /* 24 某些虚拟路由器的优先级变为了255 */
    ERR_AM4_DISPARP_INVALIDMASK,             /* 25 无效掩码 */
    ERR_AM4_DISPARP_RPCFAIL,                 /* 26 RPC失败 */
    ERR_AM4_DISPARP_WAITLIST_REGISTER_FAIL,  /* 27 Waitlist注册失败 */
    ERR_AM4_DISPARP_WAITLIST_GET_FAIL,       /* 28 Waitlist取数据失败 */
    ERR_AM4_DISPARP_SPECIFY_SUBIF_AND_VLAN,  /* 29 请指定子接口和VID */
           
    ERR_AM4_IPCRPCERR,                       /* 30 IPC/RPC 错误 */
    ERR_AM4_CANTNODHCP,                      /* 31 没有配置DHCP分配地址，不能取消 */
    ERR_AM4_GENERR,                          /* 32 处理地址出错 */
    ERR_AM4_ISBINDING,                       /* 33 接口正在执行ip binding或undo ip binding时不允许配置地址 */
    ERR_AM4_NOFREE_ITEM,                     /* 34 RIB没有可用空间 */

    ERR_AM4_HA_IS_SMOOTHING,                 /* 35 HA正在平滑处理或手动倒换处理*/

    ERR_AM4_INTERFACE,                       /* 36 指定的接口不允许配置 */
    ERR_AM4_IPCTL,                           /* 37 无效的IP控制块 */
    ERR_AM4_GENERR_DELPRIADDR,               /* 38 删除主地址出错(不通知链路层) */
    ERR_AM4_GENERR_DELSECONDARY,             /* 39 删除从地址出错(不通知链路层)*/
    ERR_AM4_GENERR_DELALL,                   /* 40 删除所有地址时(不通知链路层) */
    ERR_AM4_GENERR_ADDSECONDARY,             /* 41 增加从地址时出错(不通知链路层) */
    ERR_AM4_GENERR_ADDPRI,                   /* 42 增加主地址时出错(不通知链路层) */
    ERR_AM4_DELPRI,                          /* 43 删除主地址出错 */
    ERR_AM4_ADDRESS,                         /* 44 地址无效 */
    ERR_AM4_DELSECONDARY,                    /* 45 删除从地址出错 */
    ERR_AM4_ADDSECONDARY,                    /* 46 增加从地址出错 */
    ERR_AM4_ADDPRI,                          /* 47 增加主地址出错 */
    ERR_AM4_INVALIDIN_2,                     /* 48 输入参数不合法 */
    ERR_AM4_INVALIDIN_3,                     /* 49 输入参数不合法 */
    ERR_AM4_INVALIDIN_4,                     /* 50 输入参数不合法 */
    ERR_AM4_NOFREE_ITEM_2,                   /* 51 RIB没有可用空间 */
    ERR_AM4_NOFREE_ITEM_3,                   /* 52 RIB没有可用空间 */
    ERR_AM4_NOFREE_ITEM_4,                   /* 53 RIB没有可用空间 */
    ERR_AM4_LOOPBACKORNULL,                  /* 54 借用接口为loopback或null接口 */
    ERR_AM4_INVALIDBRIN_2,                   /* 55 无效的借入接口 */
    ERR_AM4_INVALIDBRIN_3,                   /* 56 无效的借入接口 */
    ERR_AM4_INVALIDBRIN_4,                   /* 57 无效的借入接口 */
    ERR_AM4_INVALIDBRIN_5,                   /* 58 无效的借入接口 */
    
    ERR_AM4_INVALIDLENDIN_2,                 /* 59 无效的借出接口 */
    ERR_AM4_INVALIDLENDIN_3,                 /* 60 无效的借出接口 */
    ERR_AM4_CFG_DHCP4R,                      /* 61 接口配置了DHCP4 RELAY */
    ERR_AM4_IFISVT,                          /* 62 接口是VT类型，不能配置借用地址 */

    ERR_AM4_PARAM,                           /* 63 参数错误 */
    ERR_AM4_NO_NEGO,                         /* 64 取消协商时出错 */
    ERR_AM4_ADDRINEXISTENCE,                 /* 65 配置的地址已经存在 */
    ERR_AM4_LENDINLOOKBACK,                  /* 66 INLOOKBACK接口地址不能被借用 */

    ERR_AM4_IF_NULL,                         /* 67 接口IFNET指针为空 */
    ERR_AM4_NOADDR,                          /* 68 接口无地址 */
    ERR_AM4_PPP_COMP_NULL,                   /* 69 PPP组件虚表为空 */    
    ERR_AM4_NOT_SAME_BOARD,                  /* 70 借入借出接口不在同一块单板上 */
    ERR_AM4_VIRTUAL_IFNET,                   /* 71 虚接口*/
    ERR_AM4_IF_NOT_EXIST,                    /* 72 接口不存在*/
    
    ERR_AM4_END,                             /* 73 接口没有地址，全局地址链为空*/

    ERR_AM4_IFTYPE,                          /* 74 接口类型错误 */
    ERR_AM4_IPIFNET_NULL,                    /* 75 接口IP控制块指针为空 */

    ERR_AM4_IS_L2PORT,                       /* 76 输入的目标接口是二层端口 */
    
    ERR_AM4_GETWAITLIST_FAIL,                /* 77 获取waitlist失败 */
    ERR_AM4_SETWAITLIST_FAIL,                /* 78 设置waitlist失败*/ 
    ERR_AM4_CLOSEWAITLIST_FAIL,              /* 79 关闭waitlist失败 */
    ERR_AM4_OPENWAITLIST_FAIL,               /* 80 打开waitlist失败 */

    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ERR_AM4_GET_VRFINDEX,                    /* 81 获取VRF 索引失败 */
    ERR_AM4_INVALID_VRFINDEX,                /* 82 VRF 索引不匹配 */
    ERR_AM4_NULL_POINT,                      /* 83 输入指针参数为空 */
    ERR_AM4_VRF_NOT_INIT,                    /* 84 VRF组件未注册 */
    ERR_AM4_NOT_FINDIF,                      /* 85 根据IP查找接口失败 */
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    ERR_AM4_GENERR_DELADDR,                  /* 86 Delete alias address failed */
    ERR_AM4_GENERR_ADDADDR,                  /* 87 Add alias address failed */
    ERR_AM4_OSPF_INIT,                       /* 88 Ospf module is initialized */
    ERR_AM4_INVALIDLENDIN_TUNNEL,            /* 89 无效的借出接口(tunnel接口) */
    
    ERR_AM4_MAX_INVALID_END                 /* 255 最大值 */
}; 
/* AM4配置返回错误号，同时作为模块中英文信息宏下标 
请注意同步修改 am4_sh_info.c文件中CHAR * ErrInf_AM4_En[]描述信息*/

typedef struct tagIpAddrNotifyMsg
{
    ULONG  ulIfnetIndex;     /* IFNET index of bound physical interface */
    ULONG  ulIpFlag;         /* address flag, such as primary or borrow */
    ULONG  ulLogAddr;        /* address */
    ULONG  ulSubMask;        /* Address mask */
    UCHAR  ucMsgType;        /* address added or deleted */
    UCHAR  ucPadding[3]; 
}IP_ADDR_NOTIFY_MSG_S;  

typedef struct tagIfAddrmsg
{
    ULONG   ulIntfIndex;        /* 接口索引 */
    USHORT  usMsgType;          /* 消息类型 */
    UCHAR   ucPadding[2]; 
    ULONG   ulIpFlag;           /* 借用IP等标志 */
    SOCKADDR_S  sLocalAddr;     
    SOCKADDR_S  sNetMask;       /* 网络掩码 */
    SOCKADDR_S  sPrimaryAddr;   /* 新的主地址 */
}IFADDRMSG_S;

typedef struct tagIpAddrOper
{
    ULONG ulOper;
    ULONG ulIpAddr;
    ULONG ulMask;
    ULONG ulPrimary;
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szIfName[IF_MAX_INTERFACE_NAME_LEN + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}IPADDR_OPER_S;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagIpAddrFilter
{
    ULONG ulIfIndex;
    CHAR szVrfName[IP4_MAX_VRFNAME_LENGTH + 1];
    ULONG ulIsAll;
}IPADDR_FILTER_S;
typedef struct tagIpAddrDecOper
{
    ULONG ulIpAddr;
    CHAR szDesc[MAXADDR_DESCRIPTION_LEN + 1];
    CHAR szVrfName[IP4_MAX_VRFNAME_LENGTH + 1];
}IPADDR_DEC_OPER_S;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef ULONG(*AM4_SHELL_RM_CALLBACK_FUNC_PTR)(USHORT usInstanceID, struct tagIpAddrNotifyMsg *pstIpMsg, struct tagIfAddrmsg * pstIPMsg);/*add by x36530*/


extern ULONG TCPIP_AddIpAddr (ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_AddPrimaryAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_AddSecondAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_CloseAddrTable(UINTPTR ulWaitlist);

extern ULONG TCPIP_ConflictIpAddressSpecial(ULONG ulIfIndex, ULONG ulAddr, ULONG ulMask);

extern ULONG TCPIP_DelIpAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_DelPrimaryAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_DelSecondAddr(ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

extern ULONG TCPIP_GetAddrNumOnIf(ULONG ulIfIndex);

extern ULONG TCPIP_GetAddrTable(UINTPTR ulWaitlist,TCPIP_IPIFADDR_S *pIfa,ULONG ulIfIndex);

extern ULONG TCPIP_GetIpHADbg(ULONG *pulDbg);

extern ULONG TCPIP_GetLocalIpAddr(ULONG ulIfIndex, IP_AM4_IF_ADDR_S *pstIPIfAddr);

extern ULONG TCPIP_GetMainIpAddr(ULONG ulIfIndex,ULONG *pulMainAddr, ULONG *pulMainMask);

extern ULONG TCPIP_GetPeerIpAddr(ULONG ulIfIndex, ULONG *pulIpAddr);

extern ULONG TCPIP_OpenAddrTable(UINTPTR *pulWaitlist,ULONG ulIfIndex);

extern ULONG TCPIP_ProIpNegoSet(ULONG ulIfIndex, ULONG ulSetYes);

extern ULONG TCPIP_RegFuncUpdateIntfAddrHook(AM4_SHELL_RM_CALLBACK_FUNC_PTR pfHookFunc);

extern ULONG TCPIP_SetIpHADbg(ULONG ulDbg);

extern ULONG TCPIP_UnnumberIpAddr(ULONG ulIfIndex, ULONG ulIfIndexLendIn, ULONG ulSetYes);

extern ULONG TCPIP_IsLocalIfAddr(ULONG ulIpAddr);
extern ULONG TCPIP_Proc_IPAddr( IPADDR_OPER_S* pIpAddrOper );
extern ULONG TCPIP_SetIPAddrDescription( ULONG ulIpAddr, CHAR* pucDesc );
/*******************************************************************************
*    Func Name: TCPIP_GetIfIndexByIP
*  Description: 通过IP获取对应的接口索引
*        Input: ULONG ulIPAddr:地址(网络序)
*       Output: ULONG *pulIfIndex:返回的接口索引值
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 借用的地址无法返回对应的接口索引
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-07-31   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfIndexByIP(ULONG ulIPAddr, ULONG *pulIfIndex);


extern ULONG TCPIP_SetHostRouteReserved(ULONG ulIfIndex, ULONG ulFlag);
/*******************************************************************************
*    Func Name: TCPIP_GetHostRouteReserved
*  Description: 获取接口DWON时是否保留主机路由的标记
*        Input: ULONG ulIfIndex:接口索引（只能是ETH或Trunk的对应的接口）
*       Output: ULONG *pulFlag:标识
*       Return: 成功: VOS_OK
*               失败: FIB_HA_IS_SMOOTHING
*                     FIB_ERR_NULL_POINTER
*                     FIB_ERR_INVALID_INTERFACE
*                     FIB_ERR_INVALID_IFTYPE
*                     FIB_ERR_INVALID_IPCTL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-09-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetHostRouteReserved(ULONG ulIfIndex, ULONG *pulFlag);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*******************************************************************************
*    Func Name: TCPIP_OpenAddrTableByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: 注册waitlist
*        Input: IPADDR_FILTER_S szFilter:    过滤条件
*       Output: ULONG *pulWaitlist: waitlist句柄
*       Return: 成功:VOS_OK
*               失败:
*               ERR_AM4_INVALIDIN:              输入参数不合法
*               ERR_AM4_GENERR:                 处理地址出错
*               ERR_AM4_END:                    未知错误
*               ERR_WAITLIST_INVALID_HANDLE:    waitlist句柄无效
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenAddrTableByVrf(UINTPTR *pulWaitlist,IPADDR_FILTER_S szFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetAddrTableByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: 获取地址链的下一个节点
*        Input: ULONG   ulWaitlist:waitlist句柄
*               IPADDR_FILTER_S szFilter:    过滤条件
*       Output: TCPIP_IPIFADDR_S *pIfa:地址节点的输出缓冲区，由用户指定
*       Return: 成功:VOS_OK
*               失败:VOS_ERR, ERR_AM4_INVALIDIN,
*                    ERR_AM4_END,ERR_WAITLIST_INVALID_HANDLE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetAddrTableByVrf(UINTPTR ulWaitlist, TCPIP_IPIFADDR_S *pIfa, IPADDR_FILTER_S szFilter);
/*******************************************************************************
*    Func Name: TCPIP_SetIPAddrDescriptionByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: 设置地址描述信息
*        Input: pIpDesInfo
*        Output: 无
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIPAddrDescriptionByVrf(IPADDR_DEC_OPER_S *pIpDesInfo);
/*******************************************************************************
*    Func Name: TCPIP_IsLocalIfAddrByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: 根据指定的地址查找全局地址链,判断该地址是否是本地某个接口的地址
*        Input: ULONG ulIpAddr:地址(主机序)
*       Output: 
*       Return: 成功:0, 失败:1
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_IsLocalIfAddrByVrf(ULONG ulIpAddr,CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: TCPIP_GetIfIndexByIpByVrf
* Date Created: 2009-02-02
*       Author: q62011
*  Description: 通过IP获取对应的接口索引
*        Input: ULONG ulIPAddr:地址(网络序)
*       Output: ULONG *pulIfIndex:返回的接口索引值
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 借用的地址无法返回对应的接口索引
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfIndexByIpByVrf(ULONG ulIPAddr, CHAR *pszVrfName, ULONG *pulIfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */


extern ULONG TCPIP_CheckIpIsOnIf( ULONG ulIfIndex, ULONG ulIpAddr,ULONG *pulFlag );


extern ULONG TCPIP_GetIPAddrFlag(ULONG ulIfIndex, ULONG *pulAddrFlag);


extern ULONG TCPIP_AddIpAddrEx (ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);


extern ULONG TCPIP_DelIpAddrEx (ULONG ulIpAddr,ULONG ulSubnetMask,ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_IsLocalIfAddrByVrfIndex
* Date Created: 2014-11-20
*       Author: caiqizheng
*  Description: 根据指定的地址查找全局地址链,判断该地址是否是本地某个接口的地址
*        Input: ULONG ulIpAddr:地址(主机序)
*               ULONG ulVrfIndex: VRF地址树索引
*       Output:
*       Return: 成功:0, 失败:1
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-20   caiqizheng              Create
*******************************************************************************/
extern ULONG TCPIP_IsLocalIfAddrByVrfIndex(ULONG ulIpAddr, ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetIfIndexByIpByVrfIndex
* Date Created: 2014-11-20
*       Author: caiqizheng
*  Description: 通过IP获取对应的接口索引
*        Input: ULONG ulIPAddr:地址(网络序)
*               ULONG ulVrfIndex: vrf索引
*       Output: ULONG *pulIfIndex:返回的接口索引值
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 借用的地址无法返回对应的接口索引
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-20   caiqizheng              Create
*******************************************************************************/
extern ULONG TCPIP_GetIfIndexByIpByVrfIndex(ULONG ulIPAddr, ULONG ulVrfIndex, ULONG *pulIfIndex);

#ifdef __cplusplus
}
#endif

#endif /* __AM4_API_H__ */

