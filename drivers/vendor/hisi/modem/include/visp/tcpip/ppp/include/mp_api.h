/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mp_api.h
*
*  Project Code: VISPV100R006C02
*   Module Name:   
*  Date Created: 2008-3-8
*        Author: yebo(62004)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-8  yebo(62004)         Create the first version.
*
*******************************************************************************/
#ifndef _MP_API_H_
#define _MP_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN                 47       /* 同iifnet_inc.h */ 
#endif

#ifndef MP_SUPPORT_MAX_BIND
#define MP_SUPPORT_MAX_BIND                    128       /* 同iifnet_inc.h */ 
#endif

#ifndef MC_PREFIXE_MAX_STR
#define MC_PREFIXE_MAX_STR                     8       /* 同iifnet_inc.h */ 
#endif

/* Mp-Group接口绑定信息数据结构 */
typedef struct tagMpINFO
{
    /*父通道索引*/
    ULONG ulFatherIfIndex;
    /*父通道名字*/
    UCHAR ucFatherName[IF_MAX_INTERFACE_NAME_LEN + 1];
    /*子链路索引数组*/
    ULONG ulSubLink[MP_SUPPORT_MAX_BIND];
    /*子接口链路层状态*/
    UCHAR ucSubLinkStatus[MP_SUPPORT_MAX_BIND];
    /*配置绑定的子链路数*/
    ULONG ulSubLinkNum; 
    /*实际捆绑上的子链路数*/
    ULONG ulMpBindNum;
}MPINFO_S;

/* MP统计信息结构 */
typedef struct tagMPSTATISTIC_S
{
    ULONG ulInOctets;
    ULONG ulInGigaWords;
    ULONG ulOutOctets;
    ULONG ulOutGigaWords;
    ULONG ulInPackets;
    ULONG ulOutPackets;
    
    ULONG ulOutBadPkts;       /* 发送丢弃报文数 */
    ULONG ulOutBadOctets;     /* 发送丢弃字节数 */

    ULONG ulLostFragments;          /* 接收方向丢弃的分片 */
    ULONG ulReorderedPkts;          /* 接收方向重组报文数 */
    ULONG ulUnassignedPkts;         /* 接收方向等待重组的分片数 */
    ULONG ulInterleavedPkts;        /* 发送方向LFI的分片个数 */
    
     /* Added by z43740 for A82D20089: 增加重组方式统计,2007-09-13 */
    ULONG ulWindowMatchPkts;        /* 匹配重组窗口报文个数 */
    ULONG ulWindowInPkts;           /* 落在重组窗口中报文个数 */
    ULONG ulWindowBehindPkts;       /* 落后重组窗口报文个数 */
    ULONG ulWindowSurpassPkts;      /* 超过重组窗口报文个数 */
    /* End of addition */

}MPSTATISTIC_S;

/* 前缀省略映射结构 */
typedef struct tagMCPrefixE
{ 
    UCHAR aucPrefixE[MC_PREFIXE_MAX_STR];   /* 具体前缀省略字段，最大长度为8字节*/
    UCHAR ucIsUsedFlag;                     /* 是否配置该等级前缀省略标志 */
    UCHAR ucClass;                          /* 具体Class等级 */
    UCHAR ucPrefixELen;                     /* 前缀字段长度 */      
    UCHAR ucReserve;                        /* 保留 */
} MC_PREFIXE_S;

/*MC配置参数数据结构*/
typedef struct tagMC_CONFIG_STRUCT
{
    ULONG ulMc;           /*是否使能MC*/
    ULONG ulCode;         /*接收长短序列号标识*/
    ULONG ulClassNum;     /*最大等级数*/
    ULONG ulPrefixE;      /*是否使能前缀省略选项协商*/
}MC_CONFIG_S;
/* End of addition */

/* MP-QOS处理报文返回结果的枚举定义 */
enum enumMpQosCode
{
    MP_QOS_PROCESS_OK = 0,
    MP_QOS_PROCESS_Fail,
    MP_QOS_NOT_PROCESS      /*QOS没有处理报文*/
};

/*----------------------------------------------*
 * Error code definition
 *----------------------------------------------*/
/*注意:
如果修改错误码，请同步修改mp_sh_err.c文件中的
CHAR *Inf_MP_Err_En[]描述信息*/
enum enumMpErrorCode
{
    MP_OK = 0,
    MP_ERR,        
    MP_ERR_RESOURCE_UNAVAILABLE,      /* 2  资源申请失败 */
    MP_ERR_NULL_IFNET,                /* 3  IFNET指针为NULL */
    MP_ERR_EXCEED_USER_NUM,           /* 4  超过最大可配置用户名数 */
    MP_ERR_ZERO_USER_NUM,             /* 5  配置用户名数已降为0 */
    MP_ERR_NONE_USER_NAME,            /* 6  无此用户名 */
    MP_ERR_NONE_PPP_INFO,             /* 7  没有PPP控制块指针 */
    MP_ERR_NOT_FATHER,                /* 8  对应通道非父通道 */
    MP_ERR_MP_HEADER,                 /* 9  MP帧头错误 */
    MP_ERR_PACKET_LEN,                /* 10 报文长度错误 */
    MP_ERR_ASSEMBLE_FAIL,             /* 11 报文组装失败 */
    MP_ERR_EXCEED_MULTILINK,          /* 12 MP-group子链路数超出可配置范围 */
    MP_ERR_COM_NOT_AVAILABLE,         /* 13 组件不可用 */

    MP_ERR_VA_NOT_EXIST,              /* 14 VA不存在 */
    MP_ERR_VT_NUM,                    /* 15 VT号超出范围 */
    MP_ERR_NOT_PPP_LINE,              /* 16 非PPP链路 */
    MP_ERR_NOT_MPGROUP_INTF,          /* 17 非MP-group接口 */
    MP_ERR_NOT_VT_INTF,               /* 18 非VT接口 */
    MP_ERR_NOT_VT_NOT_MPGROUP_INTF,   /* 19 非VT接口也非MP-group接口 */
    MP_ERR_MPGROUP_CANNT_BIND,        /* 20 Mp-group接口不能绑定到VT或Mp-group */
    MP_ERR_VA_CANNT_BIND_TO_MPGROUP,  /* 21 VA接口不能绑定到Mp-group */
    MP_ERR_BIND_MODE,                 /* 22 绑定模式值超出范围 */
    MP_ERR_MAX_BIND_NUM,              /* 23 最大绑定数超出可配置范围 */
    MP_ERR_MIN_FRAG_LEN,              /* 24 最小分片长度值超出可配置范围 */
    MP_ERR_FRAGMENT_DELAY,            /* 25 分片延时值超出可配置范围 */
    MP_ERR_MPGROUP_NAME,              /* 26 Mp-group名格式错误 */
    MP_ERR_USER_NAME_NULL,            /* 27 用户名为空 */
    MP_GET_DATA_END,                  /* 28 获取数据已到末尾 */

    MP_ERR_INPUT_PARAMETER,           /* 29 输入参数非法 */
    MP_ERR_GETCONFIGINFO,             /* 30 获取PPP控制块失败 */
    MP_ERR_EXCEED_MHF_CLASS,          /* 31 MHF选项的class等级超出可配置范围 */
    MP_ERR_MHF_CODE,                  /* 32 MHF选项的code值非法 */
    MP_ERR_PREFIX_ELISION_LENGTH,     /* 33 前缀字段长度超出可配置范围 */
    MP_ERR_LENGTH_PREFIX_ELISION,     /* 34 配置的长度与计算的字段长度不相等 */
    MP_ERR_PREFIX_ELISION_FIELD,      /* 35 前缀字段非法 */
    MP_ERR_PREFIX_ELISION_NUM,        /* 36 配置的前缀省略映射对数目为0 */
    MP_ERR_CMD_SWITCH_ERROR,          /* 37 输入的配置开关值非法 */
    /* End of addition */

    MP_ERR_PREFIX_ELISION_NOT_EXIST,  /* 38 前缀省略规则不存在 */
    /* End of addition */
    MP_ERR_INVALID_OPERATION,         /* 39 非法操作:不能在父通道上做配置，查询等操作 */
    MP_ERR_HA_IS_SMOOTHING,           /* 40 HA正在平滑处理或手动倒换处理 */

    MP_ERR_MPGROUP_NAME_TOOSHORT,     /* 41 输入名字过短 */
    MP_ERR_MPGROUP_NAME_NOTMATCH,     /* 42 名字与"Mp_Group"不匹配*/
    MP_ERR_MPGROUP_NAME_NOIF,         /* 43 找不到名字对应的接口 */
    MP_ERR_ENABLE,                    /* 44 MP使能错误 */
    MP_ERR_ADDTOGROUP,                /* 45 加入MP_GROUP错误 */
    MP_ERR_PREFIX_ELISION_NOT_INUSE,  /* 46 Prefix没有使用 */
    MP_ERR_EXCEED_MHF_CLASS_LONG,     /* 47 CODE 为2时超出范围 */
    MP_ERR_VT_BIND_TO_ETH,            /* 48 VT接口已经绑定到以太接口了(使能pppoe server功能) */
    MP_ERR_VT_EXCEED_MULTILINK,       /* 49 MP-group子链路数超出可配置范围(VT接口) */
    MP_ERR_VT_NONE_PPP_INFO,          /* 50 没有PPP控制块指针(VT接口) */
    MP_ERR_LOWLIMIT_OVER_MAXBIND,     /* 51 设置的下限阈值大于mp的最大绑定数 */
    MP_ERR_COM_NULL,                  /* 52 组件为空 */

    MP_ERR_NOT_BOUND,                 /* 53 PPP接口尚未绑定到MP组 */
    MP_ERR_ANALYSE,                   /* 54 解析接口名失败 */
    MP_ERR_INPUT_NULL_POINTER,        /* 55 输入空指针 */
    MP_ERR_CFGINFO_NOEXIST,           /* 56 接口上对应的配置信息不存在 */
    MP_ERR_PORT_IS_VIRTUAL = 57,      /* 57 指定接口为虚接口 */

    MP_ERR_LOWLIMIT_OVER_DEFAULTBIND, /* 58 设置的下限阈值大于默认最大绑定数 */
    MP_ERR_CODE_MAX                   /* 59 MP错误码最大值 */
};
/*注意:
如果修改错误码，请同步修改mp_sh_err.c文件中的
CHAR *Inf_MP_Err_En[]描述信息*/


/*定义钩子函数*/
typedef ULONG(*MPQOSQueInit_HOOK_FUNC)(ULONG ulIfIndex, BOOL_T bLfiConfigFlag, 
                               UCHAR ucMC, UCHAR ucClassNum);
typedef ULONG(*MPQOSCloneTemplateQue_HOOK_FUNC)(ULONG ulFatherIndex, ULONG ulTemplateIfIndex, 
                                 UCHAR ucMC,UCHAR ucClassNum);
typedef VOID(*MPQOSDelFatherFromQos_HOOK_FUNC)(ULONG ulFatherIndex);
typedef VOID(*MPQOSChange_HOOK_FUNC)( ULONG ulFatherIndex, ULONG *pulLfiConfigFlag);
typedef ULONG(*MPQOSTransmitDone_HOOK_FUNC)(ULONG ulIfIndex, UINTPTR ulPointerToDcb, MBUF_S *pstMBuf);
typedef ULONG(*QOSTransmitDone_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulPointerToDcb, MBUF_S *pstMBuf);
typedef  BOOL_T(*MPQOSIfCanSendPkt_HOOK_FUNC)(ULONG ulIfIndex);
typedef ULONG(*QOSTransmit_HOOK_FUNC)(ULONG ulIfIndex, MBUF_S *pstMBuf, USHORT usProtocol);





/*******************************************************************************
*    Func Name: TCPIP_AddMcPrefix
*  Description: 添加MC前缀
*        Input: ULONG ulIfIndex: 接口索引
*               UCHAR ucClass: 具体MC等级    
*               UCHAR ucLen: 需要省略的前缀的长度
*               UCHAR *pszPreInfo: 需要省略的前缀字段
*       Output: 
*       Return: VOS_OK      设置成功                                         
*               其它        设置失败   
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_AddMcPrefix (ULONG ulIfIndex, UCHAR ucClass, UCHAR ucLen, UCHAR *pszPreInfo );
/*******************************************************************************
*    Func Name: TCPIP_AddToMpGroup
*  Description: 将接口直接绑定到MP-group
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulMpNo: MP-Group号
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_AddToMpGroup(ULONG ulIfIndex, ULONG ulMpNo);
/*******************************************************************************
*    Func Name: TCPIP_ClrMpStatics
*  Description: 清空统计信息
*        Input: ULONG ulIfIndex: 接口索引
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_ClrMpStatics(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_DelFromMpGroup
*  Description: 去使能MP的接口。
*        Input: ULONG ulIfIndex: 接口索引
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelFromMpGroup(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_DelMcPrefix
*  Description: 删除一条指定的MC等级与对应前缀省略的映射  
*        Input: ULONG ulIfIndex: 接口索引
*               UCHAR ucClass: 需要处理的等级
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelMcPrefix ( ULONG ulIfIndex, UCHAR ucClass );
/*******************************************************************************
*    Func Name: TCPIP_EncapPPP
*  Description: 封装PPP报文
*        Input: ULONG ulIfIndex: 接口索引
*               MBUF_S *pstMbuf: 待封装报文
*               USHORT usProtocol: 封装协议号
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_EncapPPP (ULONG ulIfIndex, MBUF_S *pstMbuf, USHORT usProtocol);
/*******************************************************************************
*    Func Name: TCPIP_FragmentMP
*  Description: mp报文分片处理
*        Input: ULONG ulIfIndex:接口索引 
*               MBUF_S *pstMBuf: 报文信息
*               USHORT usProtocol: 协议号
*               UCHAR ucClass: MP等级
*       Output: 0--成功 
*             : 其它失败
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_FragmentMP(ULONG ulIfIndex,  MBUF_S *pstMBuf, USHORT usProtocol, UCHAR ucClass);
/*******************************************************************************
*    Func Name: TCPIP_GetMcConfig
*  Description: 获取MC配置信息
*        Input: ULONG ulIfIndex: 接口索引
*       Output: MC_CONFIG_S* pstMcCfg: MC配置信息
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMcConfig(ULONG ulIfIndex,MC_CONFIG_S* pstMcCfg);
/*******************************************************************************
*    Func Name: TCPIP_GetMpInfo
*  Description: 获取MP信息
*        Input: ULONG ulIfIndex:接口索引 
*       Output: MPINFO_S * pstMpInfo: MP信息控制块
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpInfo(ULONG ulIfIndex, MPINFO_S * pstMpInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetMpReorderWindowTimes
*  Description: 获取MP重组窗口调整系数。
*        Input: 
*       Output: ULONG *pulValue: 输出值
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpReorderWindowTimes(ULONG *pulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetMpStatics
*  Description: 获取MP统计信息
*        Input: ULONG ulIfIndex: 接口索引
*               MPSTATISTIC_S * pstStat: 统计信息
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpStatics(ULONG ulIfIndex, MPSTATISTIC_S * pstStat);
/*******************************************************************************
*    Func Name: TCPIP_GetMpUpSublinkLowLimit
*  Description: 获取MP的下限阈值。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG *pulValue: 要获取的下限阈值指针
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpUpSublinkLowLimit (ULONG ulIfIndex, ULONG *pulValue );
/*******************************************************************************
*    Func Name: TCPIP_GetPrefixEInfo
*  Description: 获取前缀配置信息
*        Input: ULONG ulIfIndex: 接口索引
*       Output: MC_PREFIXE_S *pstClsPrefix: 前缀配置信息
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetPrefixEInfo(ULONG ulIfIndex, MC_PREFIXE_S *pstClsPrefix);
/*******************************************************************************
*    Func Name: TCPIP_MPQOS_SonTransmit
*  Description: MPQOS选择子链路或者根据指定的子链路发送报文接口
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulPointerToDcb: 底层控制块指针，如果该指针为空，接口指针指向父通道接口，
*                                     否则，接口指针指向指定的子通道接口
*               MBUF_S * pstMBuf: MBUF指针
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_MPQOS_SonTransmit(ULONG ulIfIndex, ULONG ulPointerToDcb, MBUF_S * pstMBuf);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSChangeHook
*  Description: MP子链路增删时通知MPQOS注册接口。
*        Input: MPQOSChange_HOOK_FUNC pfHookFunc: 注册函数指针。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSChangeHook(MPQOSChange_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSCloneTemplateQueHook
*  Description: VT的QOS信息向VA上的复制注册接口。
*        Input: MPQOSCloneTemplateQue_HOOK_FUNC pfHookFunc: 注册函数指针。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSCloneTemplateQueHook(MPQOSCloneTemplateQue_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSDelFatherFromQosHook
*  Description: 删除父通道时的通知QOS注册接口。
*        Input: MPQOSDelFatherFromQos_HOOK_FUNC pfHookFunc: 注册函数指针。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSDelFatherFromQosHook(MPQOSDelFatherFromQos_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSIfCanSendPktHook
*  Description: 如果使能了MPQOS，判断子通道是否空闲能发送报文。
*        Input: MPQOSIfCanSendPkt_HOOK_FUNC pfHookFunc: 注册函数指针。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSIfCanSendPktHook(MPQOSIfCanSendPkt_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSQueInitHook
*  Description: MPQOS队列初始化函数注册接口。
*        Input: MPQOSQueInit_HOOK_FUNC pfHookFunc: 注册函数指针。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSQueInitHook(MPQOSQueInit_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSTransmitDoneHook
*  Description: 底层上报MPQOS模块的上行通知发送报文注册接口。
*        Input: MPQOSTransmitDone_HOOK_FUNC pfHookFunc: 注册函数指针。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSTransmitDoneHook(MPQOSTransmitDone_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncQOSTransmitDoneHook
*  Description: 底层上报IFNET模块的上行通知发送报文注册接口。
*        Input: QOSTransmitDone_HOOK_FUNC pfHookFunc: 注册函数指针。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncQOSTransmitDoneHook(QOSTransmitDone_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncQOSTransmitHook
*  Description: 注册给IFNET模块的下行报文发送函数注册接口。
*        Input: QOSTransmit_HOOK_FUNC pfHookFunc: 注册函数指针。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncQOSTransmitHook(QOSTransmit_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_SetMc
*  Description: 对指定接口设置使能/去使能MC功能。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulSetYes: 使能/去使能标记(0 去使能，1 使能)，其他输入非法。
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMc (ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetMcMhf
*  Description: 设置MHF(Multilink Header Format 多链路头格式)选项的参数：code（长/短序列号），class（MC报文等级数）。
*        Input: ULONG ulIfIndex: 接口索引。
*               UCHAR ucCode: 长短序列号标记（2 长序列头格式，6 短序列头格式）。
*               UCHAR ucClass: MC等级数。
*               UCHAR ucReset: 重置默认值标识   0:不重置, 1: 重置, 其他: 非法。
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMcMhf ( ULONG ulIfIndex, UCHAR ucCode, UCHAR ucClass, UCHAR ucReset );
/*******************************************************************************
*    Func Name: TCPIP_SetMcPrefixENeg
*  Description: 使能/去使能Prefix-Elision选项协商。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulSetYes:  使能/去使能标记(0 去使能，1 使能)
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMcPrefixENeg(ULONG ulIfIndex , ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetMcSsnhfNeg
*  Description: 使能/去使能协商SSNHF选项。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulSetYes: 使能标志，1 使能，0 去使能，其他输入非法
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMcSsnhfNeg ( ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetMpDiscriminatorNeg
*  Description: 使能MP终端描述符协商选项接口。
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSetYes: 使能标志，1 使能，0 去使能，其他输入错误
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpDiscriminatorNeg(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetMpEndpointDiscriminator
*  Description: 设置MP终端描述符的生成方式。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulDiscriminator: 设置的终端描述符,如果用户设置的ulDiscriminator为0,则等同于使用默认值,
*                                       由VISP默认生成(MP组通道号)
*               ULONG ulReset: 1,设置    0恢复默认设置(MP组通道号)
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpEndpointDiscriminator(ULONG ulIfIndex, ULONG ulDiscriminator, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetMpFragment
*  Description: 设置MP最小分片长度，该功能对VT/MP-Group接口都有效。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulMinFragLen: 最小分片长度值，128～1500字节。
*               ULONG ulReset: 设置标志，0 设置，1 恢复，其他输入非法
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpFragment( ULONG ulIfIndex, ULONG ulMinFragLen, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetMpFragmentDelay
*  Description: 设置MP最大分片时延。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulDelay: 时延值，1～1000毫秒。
*               ULONG ulReset: 设置标志，0 设置，1 恢复，其他输入错误。
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpFragmentDelay(ULONG ulIfIndex,ULONG ulDelay, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetMpInterleave
*  Description: 使能MP LFI功能。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulSetYes: 使能标志，1 使能，0 去使能，其他输入非法。
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpInterleave(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetMpMaxBind
*  Description: 设置MP捆绑的最大绑定数，对MP-Group接口有效。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulMaxBindNum: 最大绑定数值，1～128。
*               ULONG ulReset: 设置标志，0 设置，1 恢复，其他输入错误。
*       Output: 
*       Return: 0--成功 
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpMaxBind(ULONG ulIfIndex, ULONG ulMaxBindNum, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetMpReorderWindow
*  Description: 使能/去使能MP重组窗口功能。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulSetYes: 使能标志，1 使能，0 去使能，其他输入非法
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpReorderWindow(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetMpReorderWindowTimes
*  Description: 设置MP重组窗口调整系数。
*        Input: ULONG ulTimes: 窗口系数
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpReorderWindowTimes(ULONG ulTimes);
/*******************************************************************************
*    Func Name: TCPIP_SetMpUpSublinkLowLimit
*  Description: 设置MP的下限阈值。
*        Input: ULONG ulIfIndex: 接口索引。
*               ULONG ulValue: 设置的下限阈值
*       Output: 
*       Return: 0--成功 
*             : 其它失败 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpUpSublinkLowLimit (ULONG ulIfIndex, ULONG ulValue );
/*******************************************************************************
*    Func Name: TCPIP_ShowMcConfig
*  Description: 显示MC配置信息
*        Input: CHAR *pszIfName: 输入接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowMcConfig(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowMpConfig
*  Description: 显示MP接口配置信息
*        Input: CHAR *pszIfName: 接口名
*               ULONG ulUsed: 0-配置控制块,1-使用控制块
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowMpConfig (CHAR *pszIfName,ULONG ulUsed);
/*******************************************************************************
*    Func Name: TCPIP_ShowMpInfo
*  Description: 显示MP信息,每显示5次接口,自动释放CPU 10ms
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowMpInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowMpStatistic
*  Description: 显示MP统计信息
*        Input: CHAR *pName: 接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowMpStatistic(CHAR *pName);
/*******************************************************************************
*    Func Name: TCPIP_ShowPrefixEInfo
*  Description: 显示MP前缀信息
*        Input: CHAR *pszIfName:接口名称 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*  2008-5-27   y62007           Modify for A82D26203 添加组件虚表非空判断
*******************************************************************************/
extern VOID  TCPIP_ShowPrefixEInfo(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_MpIsEnableLFI
*  Description: 判断MP接口是否使能了LFI
*        Input: ULONG ulIfIndex:MP接口索引
*       Output: ULONG *pulIsEnable:保存是否使能了LFI的标志:1-使能;0-未使能
*       Return: 成功: MP_OK;其他: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-06-18   XiongChangSheng36317    Create
*
*******************************************************************************/
extern ULONG TCPIP_MpIsEnableLFI(ULONG ulIfIndex, ULONG *pulIsEnable);
/*******************************************************************************
*    Func Name: TCPIP_GetMpFatherIfIndex
*  Description: 通过子通道接口索引获取MP父通道接口索引
*        Input: ULONG ulSonIfIndex: 子通过接口索引
*       Output: ULONG *pulFatherIfIndex:保存返回的父通道接口索引
*       Return: 成功: MP_OK; 其他: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-06-18   XiongChangSheng36317    Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMpFatherIfIndex(ULONG ulSonIfIndex, ULONG *pulFatherIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetMpChanNumFromPpp
* Date Created: 2008-11-4
*       Author: wujie(61195)
*  Description: 根据输入的PPP子通道号查找对应的MP父通道号
*        Input: ULONG ulPppChanNum: PPP子通道号
*       Output: ULONG *pulMpChanNum: 对应的MP父通道号
*       Return: MP_ERR_COM_NOT_AVAILABLE
*               MP_ERR_RESOURCE_UNAVAILABLE
*               MP_ERR_INPUT_PARAMETER
*               MP_ERR_INPUT_NULL_POINTER
*               MP_ERR_NULL_IFNET
*               MP_ERR_NOT_BOUND
*               MP_ERR_ANALYSE
*               MP_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-11-4   wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpChanNumFromPpp(ULONG ulPppChanNum, ULONG *pulMpChanNum);

/*******************************************************************************
*    Func Name: TCPIP_SetMpDiscReq
* Date Created: 2009-04-09
*       Author: z43740
*  Description: 设置MP组处理Discard Request报文开关
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSetYes:  开关(0 关闭,1 打开)
*       Output: 
*       Return: VOS_OK                  成功
*               其它                    失败
*      Caution: 该参数设置后实时生效
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-09   z43740                  Create
*
*******************************************************************************/
ULONG TCPIP_SetMpDiscReq(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_GetMpDiscReq
* Date Created: 2009-04-09
*       Author: z43740
*  Description: 获取MP组处理Discard Request报文开关
*        Input: ULONG ulIfIndex: 接口索引
*       Output: ULONG *pulSetYes:开关(0 关闭,1 打开)
*       Return: VOS_OK                  成功
*               其它                    失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-09   z43740                  Create
*
*******************************************************************************/
ULONG TCPIP_GetMpDiscReq(ULONG ulIfIndex, ULONG *pulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_GetMpFatherIfIndex
* Date Created: 2009-04-30
*       Author: L57500
*  Description: 通过子通道接口索引获取MP父通道接口索引[加入即可获取，不需要子通道协商通过]
*        Input: ULONG ulSonIfIndex: 子通道接口索引
*       Output: ULONG *pulFatherIfIndex:保存返回的父通道接口索引
*       Return: 成功: MP_OK; 其他: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-30   L57500                  Create
*
*******************************************************************************/
ULONG TCPIP_GetMpFatherIfIndexFromCfg(ULONG ulSonIfIndex, ULONG *pulFatherIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowMpInfoByIf
* Date Created: 2009-11-20
*       Author: zhangchi(00142640)
*  Description: 根据接口名显示MP信息
*        Input: CHAR* pszIfName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-20   zhangchi(00142640)      Create
*
*******************************************************************************/
VOID TCPIP_ShowMpInfoByIf(CHAR* pszIfName);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _MP_API_H_ */

