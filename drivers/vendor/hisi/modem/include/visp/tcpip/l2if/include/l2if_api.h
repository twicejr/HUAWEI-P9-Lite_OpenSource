/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              l2if_api.h
*
*  Project Code: VISPV1R7
*   Module Name: L2IF  
*  Date Created: 2008-10-18
*        Author: LY(57500)
*   Description: l2if模块对外提供api文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-10-18  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _L2IF_API_H_
#define _L2IF_API_H_
    
#ifdef __cplusplus
extern "C"{
#endif

/* L2IF模块错误码定义 */
typedef enum enumL2IfErrCode
{
    L2IF_OK = VOS_OK,                 /* 0 OK                                       */
    L2IF_ERR,                         /* 1 未知错误                                 */
    L2IF_ERR_NO_REGISTER = MID_COMP_L2IF + 1, /* 2 L2组件未注册                     */
    L2IF_ERR_MEM_ALLOCFAIL,           /* 3 申请内存失败                             */
    L2IF_ERR_NULL_POINTER,            /* 4 null pointer                             */
    L2IF_ERR_STR_TOOLONG,             /* 5 输入的字符串长度过长                     */
    L2IF_ERR_PORTFLAG_INVALID,        /* 6 创建port接口flag参数错误                 */
    L2IF_ERR_PHYFUNC_NOREG,           /* 7 没有注册PORT底层指针                     */
    L2IF_ERR_PHYTRANS_FAILED,         /* 8 PORT底层报文发送失败                     */
    L2IF_ERR_PHYIOCTL_FAILED,         /* 9 PORT底层控制下发失败                     */
    
    L2IF_ERR_NULL_OUTPOINTER,         /* 10 输出指针参数为空                        */
    L2IF_ERR_GETPHYLINKERR,           /* 11 获取Phylink失败                         */
    L2IF_ERR_PORT_NOTL2IFPORT,        /* 12 端口非二层接口                          */
    L2IF_ERR_PORT_NOTEXIST,           /* 13 port无对应端口信息                      */
    L2IF_ERR_VLAN_SUPER,              /* 14 VLAN为S***R VLAN                        */
    L2IF_ERR_VLAN_INVALID,            /* 15 VLAN ID无效                             */
    L2IF_ERR_VLAN_PPICMD,             /* 16 Vlan 下发NP命令字错误                   */
    L2IF_ERR_VLAN_PPINOREGISTER,      /* 17 VLAN 下发NP PPI接口未注册               */
    L2IF_ERR_PORT_PPINOREGISTER,      /* 18 PORT 下发NP PPI接口未注册               */
    L2IF_ERR_MAC_PPINOREGISTER,       /* 19 MAC 下发NP PPI接口未注册                */
    
    L2IF_ERR_QINQ_PPINOREGISTER,      /* 20 QINQ 下发NP PPI接口未注册               */    
    L2IF_ERR_PARA_WRONG,              /* 21 参数错误                                */
    L2IF_ERR_VLAN_NOEXIST,            /* 22 VLAN不存在                              */
    L2IF_ERR_VLAN_TYPE,               /* 23 VLAN类型错误                            */
    L2IF_ERR_VLAN_MAXSUPER,           /* 24 S***r Vlan个数已达到1024                */
    L2IF_ERR_VLAN_MAXSUB,             /* 25 加入S***r VLAN的Sub VLAN个数已达到1024  */
    L2IF_ERR_SUBVLAN_INOTHERSUPER,    /* 26 Sub Vlan已加入其他S***r Vlan            */
    L2IF_ERR_VLAN_SUB,                /* 27 VLAN类型为Sub VLAN                      */
    L2IF_ERR_SUBVLAN_NOTINSUPER,      /* 28 Sub VLAN没有加入S***r VLAN              */
    L2IF_ERR_VLAN_SUPERNOUP,          /* 29 UP sub vlan时候,sup** vlan还没有up      */
    
    L2IF_ERR_VP_NULLPOINT,            /* 30 VP输入参数指针为空                      */    
    L2IF_ERR_PORT_NULLPOINT,          /* 31 PORT输入参数指针为空                    */
    L2IF_ERR_PORT_GETIFFAIL,          /* 32 获取ifnet指针失败                       */
    L2IF_ERR_VLAN_NOT_SUPER,          /* 33 VLAN 不是su**r vlan                     */
    L2IF_ERR_VLAN_HAVEL3IF,           /* 34 存在跟VLAN对应的三层VLAN IF             */
    L2IF_ERR_VP_VLANHASPORT,          /* 35 有端口加入了VLAN                        */
    L2IF_ERR_PORT_PPICMD,             /* 36 PORT下发命令字错误                      */
    L2IF_ERR_PORT_MAXNUM,             /* 37 超出最大端口数                          */
    L2IF_ERR_PORT_NOUSED,             /* 38 端口不可用                              */
    L2IF_ERR_PORT_LIMITTYPE,          /* 39 端口抑制类型错误                        */
    
    L2IF_ERR_PORT_INVALIDLINKTYPE,    /* 40 端口的链路类型错误                      */
    L2IF_ERR_VLAN_PVIDNOTEXIST,       /* 41 端口未设置PVID                          */
    L2IF_ERR_VP_ISPVID,               /* 42 VLAN ID是PVID，操作失败                 */
    L2IF_ERR_VP_ISSUPER,              /* 43 sup** vlan不允许端口移除操作            */
    L2IF_ERR_VP_ISNOTINMAP,           /* 44 端口未以普通方式加入指定VLAN            */
    L2IF_ERR_VP_ADD_WITH_TAGGED,      /* 45 端口已经以tagged方式加入过VLAN，但不限定是哪个VLAN */
    L2IF_ERR_VP_ADD_WITH_UNTAGGED,    /* 46 端口已经以untagged方式加入过VLAN，但不限定是哪个VLAN */
    L2IF_ERR_VP_TRUNK_UNTAGGED,       /* 47 Trunk端口不能以untagged方式加入VLAN     */
    L2IF_ERR_VP_VLAN_TAGGED,          /* 48 端口已经以tagged方式加入过该VLAN，不能再设置端口跟VLAN的其他关联关系 */
    L2IF_ERR_VP_VLAN_UNTAGGED,        /* 49 端口已经以untagged方式加入过该VLAN，不能再设置端口跟VLAN的其他关联关系 */
    
    L2IF_ERR_VLANTRANS_HAS_CFG,       /* 50 端口已经对VLAN配置了VLAN Trans功能      */
    L2IF_ERR_TRANS_PORTISADDCEVLAN,   /* 51 已有端口加入到CEVLAN                    */
    L2IF_ERR_TRANS_PORTTYPENOTTRUNK,  /* 52 配置TRANS功能的端口不是TRUNK            */
    L2IF_ERR_TRANSNODE_NOTEXSIT,      /* 53 没有TRANS配置结点                       */
    L2IF_ERR_VLAN_HAVMAP,             /* 54 已有CeVlan配置了Mapping功能             */
    L2IF_ERR_VLAN_HAVSTACK,           /* 55 已有CeVlan配置了Stacking功能            */
    L2IF_ERR_TRANS_HAVOTHERPE,        /* 56 输入的CeVlan范围已配置在其它PeVlan中    */
    L2IF_ERR_FDB_PORTNOINVLAN,        /* 57 端口未以任何方式加入指定VLAN            */
    L2IF_ERR_FDB_MACMULTICAST,        /* 58 广播或多播地址                          */
    L2IF_ERR_FDB_NULLPOINT,           /* 59 FDB输入参数指针为空                     */
    
    L2IF_ERR_FDB_MACLOCAL,            /* 60 桥physical地址                               */
    L2IF_ERR_FDB_ANOTHER_PORT,        /* 61 端口与已存在表项不一致                  */
    L2IF_ERR_MAC_PPICMD,              /* 62 MAC下发命令字错误                       */
    L2IF_ERR_FDB_MACNULL,             /* 63 physical地址为空                             */
    L2IF_ERR_FDB_ANOTHER_TYPE,        /* 64 添加表项类型与原表项类型不一致          */
    L2IF_ERR_FDB_NOFREEITEM,          /* 65 申请FDB表项资源失败                     */
    L2IF_ERR_FDB_NOEXIST,              /* 66 FDB表项不存在                           */
    L2IF_ERR_FDB_ANOTHER_CEVLAN,      /* 67 添加表项CEVlan与原表项不一致            */
    L2IF_ERR_VLAN_ADDSELF,            /* 68 Vlan不能为自己的子Vlan                  */  
    L2IF_ERR_FDB_AGINGTIME_INVALID,   /* 69 动态FDB老化时间范围无效                 */
    
    L2IF_ERR_TRANS_NO_EXIST,          /* 70 待删除的trans不存在                     */
    L2IF_ERR_FDB_INVALID_TYPE,        /* 71 表项类型非法                            */
    L2IF_ERR_FDB_OPEN_WAIT_LIST,      /* 72 FDB模块打开waitlist失败                 */
    L2IF_ERR_FDB_CLOSE_WAIT_LIST,     /* 73 FDB模块关闭waitlist失败                 */
    L2IF_ERR_FDB_WRONGNUM,            /* 74 要获取的表项数目错误                    */
    L2IF_ERR_FDB_GET_WAIT_LIST,       /* 75 FDB模块获取waitlist失败                 */
    L2IF_ERR_FDB_WAIT_LIST_NOMORE,    /* 76 wait list已经没有元素了                 */
    L2IF_ERR_FDB_TRANS_ISNOTEXIST,    /* 77 端口未以Mapping的方式加入VLAN           */
    L2IF_ERR_TRANS_VLANADDPORT,       /* 78 VLAN加入TRANS之前已加入到PORT           */
    L2IF_ERR_TRANS_NODEFAULTVLAN,     /* 79 端口未设置Stacking的默认VLAN            */
    
    L2IF_ERR_PORTHASCEDEFVLAN,        /* 80 端口已经配置了Ce default vlan           */
    L2IF_ERR_PORTHASPVID,             /* 81 端口已经配置了default vlan              */
    L2IF_ERR_IF_GETIFFAIL,            /* 82 取得VLANIF失败                          */
    L2IF_ERR_IF_NOTL3VLANIF,          /* 83 接口不是上层VLANIF                      */
    L2IF_ERR_MBUFNULL,                /* 84 MBUF为空                                */
    L2IF_ERR_PREPENDMBUFFAIL,         /* 85 MBUF Prepend处理失败                    */
    L2IF_ERR_CONTINUEMBUFFAIL,        /* 86 MBUF Continue处理失败                   */
    L2IF_ERR_RAWCOPYMBUFFAIL,         /* 87 MBUF Raw copy处理失败                   */
    L2IF_ERR_VLAN_PHYSTATUS_DOWN,     /* 88 VLAN的物理状态DOWN                      */
    L2IF_ERR_TRANS_REGWAITLIST,       /* 89 注册WaitList句柄失败                    */
    
    L2IF_ERR_TRANS_SETWAITLIST,       /* 90 设置WaitList头节点失败                  */
    L2IF_ERR_TRANS_GETWAITLIST,       /* 91 获取WaitList头节点失败                  */
    L2IF_ERR_TRANS_UNREGWAITLIST,     /* 92 解注册WaitList句柄失败                  */
    L2IF_ERR_GETLOCALMAC_NOREGISTER,  /* 93 获取桥MAC函数为注册                     */

    L2IF_ERR_GETIFINDEX_BYIFNAME,     /* 94 通过接口名字获取接口索引失败            */
    L2IF_ERR_IFNET_IS_NULL,           /* 95 IFNET接口指针为NULL                     */
    L2IF_ERR_DELETE_IF_FAIL,          /* 96 删除接口失败                            */
    L2IF_ERR_CRT_PORT_FAIL,           /* 97 创建L2 trunk成员端口返回失败            */
    L2IF_ERR_IFTYPE_IS_WRONG,         /* 98 接口类型错误                            */
    L2IF_ERR_VP_ACCESS_TAGGED,        /* 99 ACCESS端口不能以tagged方式加入VLAN     */    
    L2IF_ERR_DYNAMIC_FDB_GET,         /* 100 获取的动态FDB表项中的VLANID和MAC与查询的不一致 */
    
    L2IF_ERR_MAXCODE                  /* 最大错误码 */
}L2IF_ERRCODE_E;

/*******************************************************************************
 * 宏定义:                                                                     *
 *******************************************************************************/
/* 一个S***R VLAN中最大子VLAN数目 */
#define L2IF_MAX_SUB_VLAN       1024

/* 表示设置为抑制比例或绝对值 */
#define L2IF_LIMIT_RATIO        0  /* 表示以相对比例设置流量抑制比   */
#define L2IF_LIMIT_VALUE        1  /* 表示以流量绝对值设置流量抑制比 */

/* 系统中支持的最大VLAN数目 */
#define L2IF_MAX_VLAN_NUM       4096

/* 以位图方式表示VLAN ID时的位图长度(ULONG为单位) */
#define VLAN_BITMAP_LEN         (L2IF_MAX_VLAN_NUM/(sizeof(ULONG) * 8))

/* Modified by luogaowei, for DTS2013080906587 ,L2IF接口扩充为256, 2013/8/12 */
/* 系统支持的最大端口个数 */
#define L2IF_MAX_PORT_NUM       256

#ifndef MACADDRLEN
#define MACADDRLEN 6   /* physical地址长度 */
#endif

/*******************************************************************************
 * 枚举定义:                                                                   *
 *******************************************************************************/
/* L2IF模块标记设置定义 */
typedef enum tagL2IfSetFlag
{
    L2IF_FLAG_SET_NO = 0,           /* 0 不设置标记 */
    L2IF_FLAG_SET_YES               /* 1 设置标记 */
}L2IFSETFLAG_E;

/* 端口以tagged/untagged方式加入VLAN */
typedef enum tagL2If_VlanTag
{
    VLAN_UNTAGGED = 0,  /* VLAN以untagged方式加入VLAN */
    VLAN_TAGGED   = 1,  /* VLAN以tagged方式加入VLAN */
}L2IF_VLANTAG_E;

/* 端口类型 */
enum enPortType
{
    PORT_TYPE_INVALID = 0,  
    PORT_TYPE_ACCESS  = 1,          /* 接入端口 */
    PORT_TYPE_TRUNK   = 2,          /* 干道端口 */
    PORT_TYPE_HYBRID  = 3,          /* Hybrid 端口 */
    PORT_TYPE_QINQ    = 4,          /* QinQ 端口 */
};

/* 报文处理方式 */
typedef enum tagL2IF_Unknow_Frame_Mode
{
    L2IF_UNKNOW_FRAME_DROP = 0,                /* 丢弃模式 */
    L2IF_UNKNOW_FRAME_2CPU,                    /* 交CPU模式 */
    L2IF_UNKNOW_FRAME_BC                       /* 广播模式 */
}L2IF_UNKNOW_FRAME_MODE_E;

/* physical地址学习使能/禁止 */
typedef enum tagL2If_MacLearn
{
    L2IF_MAC_LEARNING_DISABLE = 0,   /* physical地址学习禁止 */
    L2IF_MAC_LEARNING_ENABLE  = 1    /* physical地址学习使能 */
}L2IF_MACLEARN_E;

/* 流量抑制功能使能/禁止 */
typedef enum tagL2If_FlowLimit
{
    L2IF_FLOW_LIMIT_DISABLE = 0,   /* 流量抑制功能禁止 */
    L2IF_FLOW_LIMIT_ENABLE  = 1    /* 流量抑制功能使能 */
}L2IF_MACLIMIT_E;

/* 广播包的类型 */
typedef enum tagL2IF_PORT_BROADCAST
{
    L2IF_INBROADCAST_LIMIT,         /* 上行广播速率抑制 */
    L2IF_INMULCAST_LIMIT,           /* 上行多播速率抑制 */
    L2IF_INUNMULCAST_LIMIT,         /* 上行未知单播速率抑制 */
    L2IF_OUTBROADCAST_LIMIT,        /* 下行广播速率抑制 */
    L2IF_OUTMULCAST_LIMIT,          /* 下行多播速率抑制 */
    L2IF_OUTUNMULCAST_LIMIT,        /* 下行未知单播速率抑制 */
    L2IF_BROADCAST_MAX,
}L2IF_PORT_BROADCAST_E;

/* TRANS模式 */
typedef enum tagL2TRANS_MODE
{
    L2TRANS_CEDEFAULT    = 0,       /* Ce Default Vlan stacking*/
    L2TRANS_STACKING     = 1,       /* Stacking*/
    L2TRANS_MAPPING      = 2,       /* Mapping*/
    L2TRANS_STACKINGMAPPING = 3,    /* stack方式对内存vlan再次mapping,目前此类型暂不支持*/
    L2TRANS_INVALIDMODE
}L2TRANS_MODE_E;

/*******************************************************************************
 * 数据结构定义:                                                               *
 *******************************************************************************/
 /* VLAN信息数据结构 */
typedef struct tagTCPIP_L2IF_VLAN_INFO
{
    UCHAR  ucVlanType;             /* VLAN类型,缺省值VLAN_TYPE_INVALID */
    UCHAR  ucShutdown;             /* VLAN的管理状态，SHUT OR NOSHUT */
    UCHAR  ucStatus;               /* VLAN的物理状态，UP/DOWN，缺省值VLAN_STATUS_DOWN */
    UCHAR  ucMacLearning;          /* physical地址学习,缺省值MAC_LEARNING_ENABLE */
    UCHAR  ucBroadcast;            /* VLAN内广播报文的处理方式 */
    UCHAR  ucUnkownMulti;          /* VLAN内未知多播报文的处理方式，不可配置 */
    UCHAR  ucUnkownUniFrame;       /* VLAN内未知单播报文的处理方式 */
    UCHAR  ucReserved[1];
    USHORT usSuperVlan;            /* 对应的s***r-VLAN的VLAN ID,初始值VLANID_INVALID*/
    USHORT usSubCount;             /* 对于S***r VLAN而言，包含的Sub VLAN的个数 */    
    USHORT usSubVlanID[L2IF_MAX_SUB_VLAN]; /* S***r Vlan 下所有Sub Vlan ID列表 */
    ULONG  ulIfnetIndex;           /* VLAN接口对应的ifindex,缺省值INVALID_IFINDEX(Len: 108) */
}TCPIP_L2IF_VLAN_INFO_S;

/* PORT信息数据结构 */
typedef struct tagTCPIP_L2IF_PORT_INFO
{
    UCHAR  ucIfType;                 /* 端口链路类型 */
    UCHAR  ucMacLearning;            /* 端口的physical地址学习使能标志 */
    UCHAR  ucPriority;               /* 端口优先级 0-7 */
    UCHAR  ucReserved[1];
    USHORT usPVID;                   /* 端口缺省VID */
    USHORT usCEDefaultVlan;          /* 基于端口的QinQ */
    ULONG  ulIfIndex;                /* 端口IFNET索引 */
    
    UCHAR  ucInBroadSuppressRatio;     /* 端口广播抑制的比例,缺省值100,即不抑制 */
    UCHAR  ucInMultiSuppressRatio;     /* 端口未知多播抑制的比例,缺省值100,即不抑制 */
    UCHAR  ucInUnicastSuppressRatio;   /* 端口未知单播抑制的比例,缺省值100,即不抑制 */
    UCHAR  ucOutBroadSuppressRatio;  /* 端口下行广播抑制的比例,缺省值100,即不抑制 */
    UCHAR  ucOutMultiSuppressRatio;  /* 端口下行未知多播抑制的比例,缺省值100,即不抑制 */
    UCHAR  ucOutUnicastSuppressRatio;/* 端口下行未知单播抑制的比例,缺省值100,即不抑制 */
    UCHAR  ucResv[2];
    ULONG  ulInBroadSuppress;        /* 端口上行 广播抑制的值,缺省值端口带宽,即不抑制 */
    ULONG  ulInMultiSuppress;        /* 端口上行未知多播抑制的值,缺省值端口带宽,即不抑制 */
    ULONG  ulInUnicastSuppress;      /* 端口上行未知单播抑制的值,缺省值端口带宽,即不抑制 */
    ULONG  ulOutBroadSuppress;       /* 端口下行广播抑制的值,缺省值端口带宽,即不抑制 */
    ULONG  ulOutMultiSuppress;       /* 端口下行未知多播抑制的值,缺省值端口带宽,即不抑制 */
    ULONG  ulOutUnicastSuppress;     /* 端口下行未知单播抑制的值,缺省值端口带宽,即不抑制 */
}TCPIP_L2IF_PORT_INFO_S;

/* FDB表项信息数据结构 */
typedef struct tagTCPIP_FDB_ENTRY_S
{
    UCHAR  aucMacAddr[MACADDRLEN];       /* physical地址 */        
    USHORT usVlanId;                     /* physical地址所属VLAN ID */
    ULONG  ulIfIndex;                    /* 接口索引 */
    UCHAR  ucType;                       /* physical地址表项类型 */
    UCHAR  ucFdbFlag;                    /* VLAN/QINQ 标志,仅在静态和黑洞表项下有效,动态FDB表项时无效 */
    USHORT usOutCeVlanId;                /* 用户侧VLAN ID,仅在静态和黑洞表项下有效,动态FDB表项时无效 */
    /* Add by zhaoyue00171897, at 2011-08-17. 修改原因: 支持获取动态FDB表项,表项增加老化时间 */
    ULONG  ulAgingTime;                  /* 老化时间,仅在动态FDB表项时有效,静态和黑洞表项下不必关注 */
}TCPIP_FDB_ENTRY_S;

/* TRANS配置信息数据结构 */
typedef struct tagTCPIP_L2TRANS_CONFIGINFO
{
    ULONG  ulPortIndex;             /*二层端口的接口索引*/
    ULONG  ulTransMode;             /*表示是Stacking还是Mapping模式，参见L2TRANS_MODE_E*/
    USHORT usPeVlan;                /*PeVlan ID*/
    USHORT usOutVlanBegin;          /*CeVlan 起始ID*/
    USHORT usOutVlanEnd;            /*CeVlan 终止ID*/
    UCHAR  ucReserve[2];
}TCPIP_L2TRANS_CONFIGINFO_S;

/*******************************************************************************
 * 注册适配函数原型:                                                           *
 *******************************************************************************/

/* 获取桥mac的注册函数原型 */
typedef ULONG  (*GETLOCALMAC_HOOK_FUNC)(UCHAR* pucMacAddr);

/* 端口报文发送函数原型 */
typedef ULONG  (*PORT_PHYTRANSMIT_HOOK_FUNC)(ULONG ulPhyCtlBlk, MBUF_S *pstMbuf);

/* 端口物理层下发控制函数原型 */
typedef ULONG  (*PORT_PHYIOCTL_HOOK_FUNC)(ULONG ulPhyCtlBlk, ULONG ulCmd, CHAR *pData);

/* 通过PORT接口名获取底层信息函数原型 */
typedef ULONG  (*PORT_GETPHYLINK_HOOK_FUNC)(CHAR *szName, ULONG *pulPhyLink);

/* 在VISP进行软转发VLAN报文时，通过此注册钩子获取其优先级字段 */
typedef ULONG  (*L2IF_TOS_TO_VLAN_PRIORITY)(MBUF_S *pMbuf, ULONG *pPriority);

/*******************************************************************************
 * API原型:                                                                    *
 *******************************************************************************/

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetLocalMacHook
* Date Created: 2008-10-18
*       Author: LY(57500)
*  Description: 产品注册获取桥mac的适配函数
*        Input: GETLOCALMAC_HOOK_FUNC pfFunc: 获取桥mac适配函数原型
*       Output: 
*       Return: VOS_OK:     注册成功
*               VOS_ERR:    注册失败
*      Caution: 协议栈启动前注册,不可解注册
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-18    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetLocalMacHook(GETLOCALMAC_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPortPhyTransmitHook
* Date Created: 2008-10-18
*       Author: LY(57500)
*  Description: 产品注册交换机端口的底层报文发送适配函数 
*        Input: PORT_PHYTRANSMIT_HOOK_FUNC pfFunc: 待注册函数
*       Output: 
*       Return: VOS_OK:     注册成功
*               VOS_ERR:    注册失败
*      Caution: 协议栈启动前注册,不可解注册
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-18    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPortPhyTransmitHook(PORT_PHYTRANSMIT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPortPhyIoCtlHook
* Date Created: 2008-10-18
*       Author: LY(57500)
*  Description: 产品注册交换机端口的物理层控制适配函数
*        Input: PORT_PHYIOCTL_HOOK_FUNC pfFunc: 待注册函数
*       Output: 
*       Return: VOS_OK:     注册成功
*               VOS_ERR:    注册失败
*      Caution: 协议栈启动前注册,不可解注册
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-18    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPortPhyIoCtlHook(PORT_PHYIOCTL_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPortPhyLinkHook
* Date Created: 2008-10-25
*       Author: LY(57500)
*  Description: 根据接口名获取底层信息注册函数
*        Input: PORT_GETPHYLINK_HOOK_FUNC pfFunc: 待注册指针
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-25    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetPortPhyLinkHook(PORT_GETPHYLINK_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_AddSubVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 添加Sub VLAN到S***r VLAN
*        Input: USHORT usSuperVlanId: S***r VLAN的VLAN ID
*               USHORT usSubVlanId: Sub VLAN的VLAN ID
*       Output: 
*       Return: 
*      Caution: 直接将COMMON VLAN添加到S***r VLAN中，COMMON VLAN直接自动转换为Sub VLAN
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_AddSubVlan(USHORT usSuperVlanId, USHORT usSubVlanId);

/*******************************************************************************
*    Func Name: TCPIP_CreateVlan
* Date Created: 2008-10-20
*       Author: z00104207
*  Description: 创建VLAN
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-20   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_CreateVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_RemoveSubVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 将Sub VLAN从S***r VLAN中移出
*        Input: USHORT usSuperVlanId: S***r VLAN的VLAN ID
*               USHORT usSubVlanId: Sub VLAN的VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RemoveSubVlan(USHORT usSuperVlanId, USHORT usSubVlanId);

/*******************************************************************************
*    Func Name: TCPIP_DeleteVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 删除VLAN
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_DeleteVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_DeleteBatchVlan
* Date Created: 2008-11-11
*       Author: Zheng Sen Huo (00104483)
*  Description: 删除指定范围的VLAN。
*        Input: USHORT usBeginVlan:起始VLANID
*               USHORT usEndVlan:结束VLANID
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-11   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DeleteBatchVlan(USHORT usBeginVlan, USHORT usEndVlan);

/*******************************************************************************
*    Func Name: TCPIP_GetPortInfoByIfIndex
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 根据物理口接口索引获取二层端口配置信息
*        Input: ULONG ulIfIndex: 端口对应的接口索引
*               TCPIP_L2IF_PORT_INFO_S *pulPortInfo: 端口配置信息输出缓冲区
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPortInfoByIfIndex(ULONG ulIfIndex, TCPIP_L2IF_PORT_INFO_S *pstPortInfo);

/*******************************************************************************
*    Func Name: TCPIP_GetUsedPort
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 获取当前在用的端口数目和对应的接口索引列表
*        Input: ULONG *pulPortNum: 当前在用的端口数目
*               ULONG  ulIfIndexList[L2IF_MAX_PORT_NUM]: 在用的二层端口对应的接口索引列表
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetUsedPort(ULONG *pulPortNum, ULONG ulIfIndexList[L2IF_MAX_PORT_NUM]);

/*******************************************************************************
*    Func Name: TCPIP_GetUsedVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 获取当前在用的VLAN数目和VLAN ID列表
*        Input: 
*       Output: ULONG *pulVlanNum: 当前在用的VLAN数
*               ULONG ulVlanIDBitMap[VLAN_BITMAP_LEN]: vlan id 位图
*       Return: 成功返回L2IF_OK，其它错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetUsedVlan(ULONG *pulVlanNum, ULONG ulVlanIDBitMap[VLAN_BITMAP_LEN]);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanInfo
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: 根据VLAN ID获取VLAN的信息
*        Input: USHORT usVlanId: VLAN ID
*       Output: TCPIP_L2IF_VLAN_INFO_S *pstVlanInfo: VLAN信息输出缓冲区
*       Return: 成功返回L2IF_OK，其它错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVlanInfo(USHORT usVlanId, TCPIP_L2IF_VLAN_INFO_S *pstVlanInfo);

/*******************************************************************************
*    Func Name: TCPIP_SetPortMacLearn
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: 使能/去使能二层端口physical地址学习功能
*        Input: ULONG ulIfIndex: 端口对应的接口索引
*               ULONG ulFlag: 使能/去使能标记, L2IF_FLAG_SET_NO / L2IF_FLAG_SET_YES
*       Output: 
*       Return: 成功返回L2IF_OK，其它错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortMacLearn(ULONG ulIfIndex, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetPortPriority
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: 设置二层端口优先级
*        Input: ULONG ulIfIndex: 端口对应的接口索引
*               UCHAR ucPriority: 优先级范围是0~7
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortPriority(ULONG ulIfIndex, UCHAR ucPriority);

/*******************************************************************************
*    Func Name: TCPIP_SetPortSuppressRatio
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: 设置二层端口流量抑制比例,ucSuppressRatio 值为100表示不设置抑制功能
*        Input: ULONG ulIfIndex: 端口对应的接口索引
*               ULONG ulLimitType: 需要抑制的报文类型，包括上行/下行单播报文、
*               上行/下行多播报文、上行/下行广播报文
*               UCHAR ucSuppressRatio: 限制速率的百分数
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortSuppressRatio(ULONG ulIfIndex, ULONG ulLimitType, UCHAR ucSuppressRatio);


/*******************************************************************************
*    Func Name: TCPIP_SetPortSuppressValue
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 设置限制二层端口速率的绝对值,值为0或全f表示不限制速率
*        Input: ULONG ulIfIndex: 端口对应的接口索引
*               ULONG ulLimitType: 需要抑制的报文类型，包括上行/下行单播报文、
*               上行/下行多播报文、上行/下行广播报文
*               ULONG ulSuppressValue: 限制速率的绝对值
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortSuppressValue(ULONG ulIfIndex, ULONG ulLimitType, ULONG ulSuppressValue);

/*******************************************************************************
*    Func Name: TCPIP_SetPortType
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: 设置二层端口的链路类型
*        Input: ULONG ulIfIndex: 端口对应的接口索引
*               UCHAR ucPortType: 要设置成的端口类型，共有PORT_TYPE_ACCESS,
*               PORT_TYPE_TRUNK, PORT_TYPE_HYBRID和PORT_TYPE_QINQ四种类型
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortType(ULONG ulIfIndex, UCHAR ucPortType);

/*******************************************************************************
*    Func Name: TCPIP_SetStackingDefaultVlan
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: 设置端口的默认Stacking VLAN
*        Input: ULONG ulIfIndex: 端口对应的接口索引
*               USHORT usVlanID: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetStackingDefaultVlan(ULONG ulIfIndex, USHORT usVlanID);

/*******************************************************************************
*    Func Name: TCPIP_UndoStackingDefaultVlan
* Date Created: 2008-11-20
*       Author: Zheng Sen Huo (00104483)
*  Description: 取消二层端口的StackingDefaultVlan
*        Input: ULONG ulIfIndex:二层端口索引
*       Output: 
*       Return: 成功返回L2IF_OK,失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-20   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_UndoStackingDefaultVlan(ULONG ulIfIndex);


/*******************************************************************************
*    Func Name: TCPIP_SetSuperVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 设置VLAN为Su*** VLAN或将Su*** VLAN恢复为Commond VLAN
*        Input: USHORT usVlanId: VLAN ID
*               UCHAR ucFlag: L2IF_FLAG_SET_NO / L2IF_FLAG_SET_YES
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSuperVlan(USHORT usVlanId, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanBroadCast
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 设置VLAN内广播报文的处理方式
*        Input: USHORT usVlanID: VLAN ID
*               UCHAR ucFlag: L2IF_UNKNOW_FRAME_DROP / L2IF_UNKNOW_FRAME_2CPU
*                             / L2IF_UNKNOW_FRAME_BC
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetVlanBroadCast(USHORT usVlanID, UCHAR ucFlag);


/*******************************************************************************
*    Func Name: TCPIP_SetVlanUnknowMulti
* Date Created: 2008-11-10
*       Author: wuhailan
*  Description: 设置VLAN内未知多播报文的处理方式
*        Input: USHORT usVlanID: VLAN ID
*               UCHAR ucFlag: L2IF_UNKNOW_FRAME_DROP / L2IF_UNKNOW_FRAME_2CPU
*                             / L2IF_UNKNOW_FRAME_BC
*       Output: 
*       Return: L2IF_OK: 成功
*               错误码:  失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   wuhailan                Create
*
*******************************************************************************/
ULONG TCPIP_SetVlanUnknowMulti(USHORT usVlanID, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanMacLearn
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 设置指定VLAN的physical地址学习是否使能
*        Input: USHORT usVlanId: VLAN ID
*               UCHAR ucFlag: MAC_LEARNING_DISABLE / MAC_LEARNING_ENABLE
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetVlanMacLearn(USHORT usVlanId, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanUnknowUnicast
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 设置VLAN内未知单播报文的处理方式，默认的处理方式是广播方式。未知
*               单播报文是指，根据报文的上的MAC和VLAN TAG无法找到匹配的二层转发
*               表项的单播报文
*        Input: USHORT usVlanId: VLAN ID
*               UCHAR ucFlag: 未知单播报文的处理方式。包括: L2IF_UNKNOW_FRAME_DROP
*               / L2IF_UNKNOW_FRAME_2CPU / L2IF_UNKNOW_FRAME_BC
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetVlanUnknowUnicast(USHORT usVlanId, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_ShowAllVlanInfo
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: 显示所有VLAN的信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowAllVlanInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowPortInfoByIfName
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 根据物理口接口显示二层端口配置信息
*        Input: ULONG ulIfIndex: 端口对应的接口索引
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPortInfoByIfName(UCHAR *pucIfName);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlan
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: 根据VLAN ID显示VLAN的详细配置信息
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_ShutdownVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: Shut down指定的VLAN
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_ShutdownVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_UpVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: 将shout down的VLAN置UP
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_UpVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_AddPortToVlan
* Date Created: 2008-10-31
*       Author: z00104207
*  Description: 把Hybrid类型或Trunk类型的二层端口添加到VLAN
*        Input: ULONG ulIfIndex: 二层端口对应的接口索引
*               USHORT usVlanId: 目标VLAN ID
*               ULONG ulTagFlag: 端口加入VLAN的方式: VLAN_UNTAGGED/VLAN_TAGGED
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-31   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_AddPortToVlan(ULONG ulIfIndex, USHORT usVlanId, ULONG ulTagFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetDefaultVlan
* Date Created: 2008-11-04
*       Author: z00104207
*  Description: 设置二层端口的默认VLAN
*        Input: ULONG ulIfIndex: 二层端口对应的接口索引
*               USHORT usVlanId: 目标VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDefaultVlan(ULONG ulIfIndex, USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_UndoDefaultVlan
* Date Created: 2008-11-06
*       Author: z00104207
*  Description: 取消端口的PVID
*        Input: ULONG ulIfIndex: 接口索引
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-06   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_UndoDefaultVlan(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_CreatePortIf
* Date Created: 2008-10-25
*       Author: LY(57500)
*  Description: 动态创建PORT接口
*        Input: CHAR *szPortIfName: 接口名，名字形式为：ethernetXYZ，
*                                    XYZ中X的含义是板号，YZ的含义是该板的端口号。
*                                    具体值由用户负责分配和解释。外部负责
*               ULONG ulL2Flag: 标识是创建普通port接口(L2IF_PORT)还是L2-TRUNK成员端口(L2IF_TRUNKPORT)
*       Output: ULONG *pulIfIndex: 输出PORT接口指针
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-25    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_CreatePortIf(CHAR *szPortIfName, ULONG ulL2Flag, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_L2PortSwitch
* Date Created: 2010-01-04
*       Author: z62531
*  Description: 实现L2普通端口与L2Trunk成员端口的互相转换
*        Input: CHAR *szPortIfName: 接口名，名字形式为：ethernetXYZ，
*                                    XYZ中X的含义是板号，YZ的含义是该板的端口号。
*                                    具体值由用户负责分配和解释。外部负责
*       Output: ULONG *pulIfIndex: 输出PORT接口指针
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-01-04   z62531     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_L2PortSwitch(CHAR *szPortIfName, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DelPortFromVlan
* Date Created: 2008-11-04
*       Author: wuhailan
*  Description: 将二层端口从指定vlan中删除
*        Input: ULONG ulIfIndex:二层接口索引
*               USHORT usVlanId:vlan id
*       Output: 无
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_DelPortFromVlan(ULONG ulIfIndex, USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_DelPortFromAllVlan
* Date Created: 2008-11-04
*       Author: wuhailan 
*  Description: 退出所有VLAN，含默认VLAN。
*        Input: ULONG ulIfIndex:端口索引
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_DelPortFromAllVlan(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetPortListInVlan
* Date Created: 2008-11-04
*       Author: h00121208
*  Description: 获取加入VLAN的端口数目和端口IFIndex列表
*        Input: USHORT usVlanId:       VLAN id
*               ULONG *pulPortNum:     端口数目
*               ULONG ulIfList[L2IF_MAX_PORT_NUM]:  端口数组 
*       Output: ULONG *pulPortNum:     加入VLAN的端口数目
*               ULONG ulIfList[L2IF_MAX_PORT_NUM]:  加入VLAN的端口IFIndex列表 
*       Return: 成功返回L2IF_OK，其它错误码
*      Caution: 传入的Ifnet List数组大小和清零由用户保证
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   h00121208               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPortListInVlan(USHORT usVlanId, ULONG *pulPortNum, ULONG ulIfList[L2IF_MAX_PORT_NUM]);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanListInPort
* Date Created: 2008-11-04
*       Author: h00121208
*  Description: 获取端口加入的VLAN数目和VLAN列表
*        Input: ULONG ulIfIndex:         接口索引
*       Output: ULONG *pulVlanNum:       端口加入的VLAN数目
*               ULONG ulVlanList[VLAN_BITMAP_LEN]:   端口加入的VLAN位图数组
*               ULONG ulTagList[VLAN_BITMAP_LEN]:    端口加入的VLAN的Tag标记位图数组
*       Return: 成功返回L2IF_OK，其它错误码
*      Caution: 传入的VLAN List数组大小和清零由用户保证
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   h00121208               Create
*  2011-08-04   s00176784               Modify
*******************************************************************************/
ULONG TCPIP_GetVlanListInPort(ULONG ulIfIndex, ULONG *pulVlanNum, 
                              ULONG ulVlanList[VLAN_BITMAP_LEN], ULONG ulTagList[VLAN_BITMAP_LEN]);


/*******************************************************************************
*    Func Name: TCPIP_ShowPortListInVlan
* Date Created: 2008-11-04
*       Author: h00121208
*  Description: 显示加入VLAN的接口名称
*        Input: USHORT usVlanID: VLAN id
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   h00121208               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPortListInVlan(USHORT usVlanID);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlanListInPort
* Date Created: 2008-11-05
*       Author: wuhailan
*  Description: 显示接口所在的vlan list信息
*        Input: CHAR *pIfName:接口名称
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-05   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVlanListInPort(CHAR *pIfName);

/*******************************************************************************
*    Func Name: TCPIP_AddVlanMapping
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据端口索引增加Vlan Mapping功能
*        Input: ULONG ulIfIndex:      端口索引
*               USHORT usOutVlanBegin:Mapping前的起始VLANID 1~4094
*               USHORT usOutVlanEnd:  Mapping前的终止VLANID 1~4094
*               USHORT usMappingVlan: Mapping后的VLANID 1~4094
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_AddVlanMapping(ULONG ulIfIndex, USHORT usOutVlanBegin, USHORT usOutVlanEnd,USHORT usMappingVlan);

/*******************************************************************************
*    Func Name: TCPIP_DelVlanMapping
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据端口索引删除Vlan Mapping功能
*        Input: ULONG ulIfIndex:      端口索引
*               USHORT usOutVlanBegin:Mapping前的起始VLANID 1~4094
*               USHORT usOutVlanEnd:  Mapping前的终止VLANID 1~4094
*               USHORT usMappingVlan: Mapping后的VLANID 1~4094
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DelVlanMapping(ULONG ulIfIndex, USHORT usOutVlanBegin, USHORT usOutVlanEnd,USHORT usMappingVlan);

/*******************************************************************************
*    Func Name: TCPIP_AddVlanStacking
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据端口索引增加Stacking功能
*        Input: ULONG ulIfIndex:      端口索引
*               USHORT usOutVlanBegin:Stacking内层Vlan的起始VLANID 1~4094
*               USHORT usOutVlanEnd:  Stacking内层Vlan的终止VLANID 1~4094
*               USHORT usStackingVlan:Stacking的外层VLANID 1~4094
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_AddVlanStacking(ULONG ulIfIndex, USHORT usOutVlanBegin, USHORT usOutVlanEnd,USHORT usStackingVlan);

/*******************************************************************************
*    Func Name: TCPIP_DelVlanStacking
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据端口索引删除Stacking功能
*        Input: ULONG ulIfIndex:      端口索引
*               USHORT usOutVlanBegin:Stacking内层Vlan的起始VLANID 1~4094
*               USHORT usOutVlanEnd:  Stacking内层Vlan的终止VLANID 1~4094
*               USHORT usStackingVlan:Stacking的外层VLANID 1~4094
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DelVlanStacking(ULONG ulIfIndex, USHORT usOutVlanBegin, USHORT usOutVlanEnd,USHORT usStackingVlan);

/*******************************************************************************
*    Func Name: TCPIP_SetPortQinqProtocol
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据端口索引设置QinQ的外层协议号
*        Input: ULONG ulIfIndex:      端口索引
*               USHORT usQinqProtocol:QinQ的外层协议号
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortQinqProtocol(ULONG ulIfIndex, USHORT usQinqProtocol);

/*******************************************************************************
*    Func Name: TCPIP_GetQinqProtocolByPort
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据端口索引获取QinQ的外层协议号
*        Input: ULONG ulIfIndex:        端口索引
*               USHORT *pusQinqProtocol:QinQ的外层协议号
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetQinqProtocolByPort(ULONG ulIfIndex, USHORT *pusQinqProtocol);

/*******************************************************************************
*    Func Name: TCPIP_OpenVlanQinQTable
* Date Created: 2008-11-24
*       Author: Zheng Sen Huo (00104483)
*  Description: 获取WaitList句柄
*        Input: ULONG *pulWaitlist:WaitList句柄
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-24   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenVlanQinQTable(UINTPTR *pulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanQinQTable
* Date Created: 2008-11-24
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据WaitList句柄获取QinQ配置信息
*        Input: ULONG ulWaitlist:WaitList句柄
*               ULONG ulTransNum:需要获取的配置信息个数
*       Output: TCPIP_L2TRANS_CONFIGINFO_S *pstTransEntry:Trans配置信息
*               ULONG *pulTransNumReturn:实际获取的配置信息个数
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-24   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVlanQinQTable(UINTPTR ulWaitlist,ULONG ulTransNum, 
                                    TCPIP_L2TRANS_CONFIGINFO_S *pstTransEntry,ULONG *pulTransNumReturn);

/*******************************************************************************
*    Func Name: TCPIP_CloseVlanQinQTable
* Date Created: 2008-11-24
*       Author: Zheng Sen Huo (00104483)
*  Description: 关闭WaitList
*        Input: ULONG ulWaitlist:WaitList句柄
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-24   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseVlanQinQTable(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_DelAllMappingByPort
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据二层端口索引删除端口上所有Mapping配置信息
*        Input: ULONG ulIfIndex:二层端口索引
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DelAllMappingByPort(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DelAllStackingByPort
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据二层端口索引删除端口上所有Stacking配置信息
*        Input: ULONG ulIfIndex:二层端口索引
*       Output: 
*       Return: 成功:L2IF_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DelAllStackingByPort(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlanQinQByPort
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据二层端口名显示所有Trans信息
*        Input: CHAR *pIfName:二层端口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowVlanQinQByPort(CHAR *pIfName);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlanQinQByPEVlan
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 根据PeVlan显示与此Vlan相关的Trans信息
*        Input: USHORT usPeVlan:Mapping后的VlanID或Stacking的外层VlanID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowVlanQinQByPEVlan(USHORT usPeVlan);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlanQinQAll
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: 显示所有端口下的Trans信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowVlanQinQAll(VOID);

/*******************************************************************************
*    Func Name: TCPIP_FDB_AddStatic
* Date Created: 2008-11-13
*       Author: zhangchi(00142640)
*  Description: 添加静态physical地址表项
*        Input: UCHAR *aucMacAddr:  MAC表项
*               USHORT usVlanId:    VLAN ID
*               ULONG ulIfIndex:    接口索引
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-13   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_AddStatic(UCHAR *aucMacAddr, USHORT usVlanId, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_FDB_AddBlackhole
* Date Created: 2008-11-15
*       Author: zhangchi(00142640)
*  Description: 添加黑洞MAC表项
*        Input: UCHAR *aucMacAddr:  MAC表项
*               USHORT usVlanId:    VLAN ID
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-15   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_AddBlackhole(UCHAR *aucMacAddr, USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_FDB_AddMappingStatic
* Date Created: 2008-11-17
*       Author: zhangchi(00142640)
*  Description: 添加基于Mapping的静态Mac表项
*        Input: UCHAR *aucMacAddr: physical地址
*               USHORT usVlanId:   VLAN id
*               USHORT usCeVlanId: CEVLAN id
*               ULONG ulIfIndex:   接口索引
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_AddMappingStatic(UCHAR *aucMacAddr, USHORT usVlanId, USHORT usCeVlanId, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_FDB_AddMappingBlackhole
* Date Created: 2008-11-17
*       Author: zhangchi(00142640)
*  Description: 添加基于Mapping的黑洞Mac表项
*        Input: UCHAR *aucMacAddr: physical地址
*               USHORT usVlanId:   VLAN id
*               USHORT usCeVlanId: CEVLAN id
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码

*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_AddMappingBlackhole(UCHAR *aucMacAddr, USHORT usVlanId, USHORT usCeVlanId);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByType
* Date Created: 2008-11-18
*       Author: zhangchi(00142640)
*  Description: 根据表项类型删除FDB表项
*        Input: UCHAR ucType: 表项类型
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-18   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByType(UCHAR ucType);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByVlanType
* Date Created: 2008-11-19
*       Author: zhangchi(00142640)
*  Description: 根据表项类型和VLAN ID删除FDB表项
*        Input: USHORT usVlanID: VLAN ID
*               UCHAR ucType:    表项类型
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-19   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByVlanType(USHORT usVlanID, UCHAR ucType);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByPortType
* Date Created: 2008-11-20
*       Author: zhangchi(00142640)
*  Description: 根据端口和表项类型删除MAC表项
*        Input: ULONG ulIfIndex: 接口索引
*               UCHAR ucType:    表项类型
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-20   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByPortType(ULONG ulIfIndex, UCHAR ucType);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByPortVlanType
* Date Created: 2008-11-20
*       Author: zhangchi(00142640)
*  Description: 根据端口，VLAN和表项类型删除MAC表项
*        Input: ULONG ulIfIndex:接口索引
*               USHORT usVlanId:VLAN ID
*               UCHAR ucType:   表项类型
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-20   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByPortVlanType(ULONG ulIfIndex, USHORT usVlanId, UCHAR ucType);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByMacVlan
* Date Created: 2008-11-20
*       Author: zhangchi(00142640)
*  Description: 根据physical地址和VLAN ID删除MAC表项
*        Input: UCHAR *aucMacAddr: physical地址
*               USHORT usVlanId:   VLAN ID
*       Output: 
*       Return: 成功返回L2IF_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-20   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByMacVlan(UCHAR *aucMacAddr, USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_FDB_SetAgingTime
* Date Created: 2008-11-14
*       Author: lianglong111779
*  Description: 设置动态physical地址表项的老化时间
*        Input: ULONG ulAgingTime:  老化时间
*       Output: 
*       Return: 成功返回L2IF_OK，其它错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-14   lianglong111779         Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_SetAgingTime(ULONG ulAgingTime);

/*******************************************************************************
*    Func Name: TCPIP_FDB_GetAgingTime
* Date Created: 2008-11-14
*       Author: lianglong111779
*  Description: 获取动态physical地址表项的老化时间
*        Input: ULONG ulAgingTime:  老化时间
*       Output: 
*       Return: 成功返回L2IF_OK，其它错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-14   lianglong111779         Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_GetAgingTime(ULONG* pulAgingTime);

/*******************************************************************************
*    Func Name: TCPIP_FDB_GetEntryByMacPlusVlan
* Date Created: 2008-11-17
*       Author: luowentong105073
*  Description: 根据physical地址和VLAN ID来获取表项
*        Input: UCHAR* aucMacAddr:physical地址
*               USHORT usVlanid:VLAN ID
*       Output: TCPIP_FDB_ENTRY_S* pstFdbEntry:返回的表项
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_GetEntryByMacPlusVlan(UCHAR* aucMacAddr, USHORT usVlanid, TCPIP_FDB_ENTRY_S* pstFdbEntry);

/*******************************************************************************
*    Func Name: TCPIP_FDB_OpenWtLstObject
* Date Created: 2008-11-17
*       Author: luowentong105073
*  Description: 打开waitlist
*        Input: 
*       Output: ULONG *pulWaitListHandle:wait list handle
*       Return: 成功或失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_OpenWtLstObject(UINTPTR *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_FDB_CloseWtLstObject
* Date Created: 2008-11-17
*       Author: luowentong105073
*  Description: 关闭waitlist
*        Input: ULONG ulWaitListHandle:wait list handle
*       Output: 
*       Return: 成功或失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_CloseWtLstObject(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_FDB_GetWLStaticByIfIndexPlusVlan
* Date Created: 2008-11-17
*       Author: luowentong105073
*  Description: 根据接口索引和VLAN ID获取表项
*        Input: ULONG ulWaitlist:wait list handle
*               ULONG ulIfIndex:接口索引
*               USHORT usVlanId:VLAN ID
*               ULONG *pulFdbNum:表项数目
*       Output: TCPIP_FDB_ENTRY_S** ppstFdbEntry:表项数组
*               ULONG *pulFdbNum:表项数目
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_GetWLStaticByIfIndexPlusVlan(UINTPTR ulWaitlist, ULONG ulIfIndex, USHORT usVlanId, 
    TCPIP_FDB_ENTRY_S* pstFdbEntry, ULONG *pulFdbNum);
    

/*******************************************************************************
*    Func Name: TCPIP_FDB_GetWLBlackholeByVlan
* Date Created: 2008-11-22
*       Author: luowentong105073
*  Description: 根据VLAN ID获取黑洞表项
*        Input: ULONG ulWaitListHandle:wait list
*               USHORT usVlanId:VLAN ID
*               ULONG *pulFdbNum:表项数目
*       Output: TCPIP_FDB_ENTRY_S* pstFdbEntry:表项数组
*               ULONG *pulFdbNum:表项数目
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-22   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_GetWLBlackholeByVlan(UINTPTR ulWaitlist, USHORT usVlanId, 
    TCPIP_FDB_ENTRY_S* pstFdbEntry, ULONG *pulFdbNum);
    
/*******************************************************************************
*    Func Name: TCPIP_FDB_ShowStatic
* Date Created: 2008-11-22
*       Author: zhangchi(00142640)
*  Description: 显示所有静态MAC表项
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-22   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID TCPIP_FDB_ShowStatic(VOID);    

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTos2VlanPriorityHook
* Date Created: 2008-11-18
*       Author: wuhailan 
*  Description: 在VISP进行软转发VLAN报文时，通过此注册钩子获取其优先级字段
*        Input: L2IF_TOS_TO_VLAN_PRIORITY pfHookFunc:函数钩子
*       Output: 
*       Return: 成功返回L2IF_OK，其它错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-18   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncTos2VlanPriorityHook(L2IF_TOS_TO_VLAN_PRIORITY pfHookFunc);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _L2IF_API_H_      */


