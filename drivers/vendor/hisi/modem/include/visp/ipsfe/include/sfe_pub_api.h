/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_pub_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: wuhailan
*   Description: 数据面公共模块相关对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    wuhailan         Create the first version.
*
*******************************************************************************/

#ifndef _SFE_PUB_API_H_
#define _SFE_PUB_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面PUB模块错误码定义 */
typedef enum enumSfePubErrCode
{
    SFE_PUB_OK = SFE_OK,                                /* 操作成功 */
    SFE_PUB_ERR_BEGIN = SFE_PUB_BEGIN_RET_CODE,         /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_PUB_ERR_ACLFILTERHOOK_POINTNULL,                /* 1  ACL过滤钩子注册函数指针为空 */
    SFE_PUB_ERR_FWDHOOK_POINTNULL,                      /* 2  FWD上送钩子注册函数指针为空 */
    SFE_PUB_SET_SRCIPADDR_VRF_ERR,                      /* 3  设置Src ip的VRF非法 */
    SFE_PUB_SRCIPADDR_SHARE_NULL,                       /* 4  设置Src ip全局变量为空,初始化没有成功或没有初始化完成 */
    SFE_PUB_GET_SRCIPADDR_SHARE_NULL,                   /* 5  获取Src ip全局变量为空,初始化没有成功或没有初始化完成 */
    SFE_PUB_GET_SRCIPADDR_VRF_ERR,                      /* 6  获取Src ip时，VRF非法 */
    SFE_PUB_GET_SRCIPADDR_NULL_POINT,                   /* 7  获取Src ip时，参数为空 */
    SFE_PUB_SHAREVAR_NULL_SET_ACLFAKEREASSSWITCH,       /* 8  设置ACL处理是否需要数据面进行假重组开关时,共享变量指针为NULL */
    SFE_PUB_SWITCH_INVALID_SET_ACLFAKEREASSSWITCH,      /* 9  设置ACL处理是否需要数据面进行假重组开关时,开关值非法 */
    SFE_PUB_SHAREVAR_NULL_GET_ACLFAKEREASSSWITCH,       /* 10 获取ACL处理是否需要数据面进行假重组开关时,共享变量指针为NULL */
    SFE_PUB_SWITCH_PONITERNULL_GET_ACLFAKEREASSSWITCH,  /* 11 获取ACL处理是否需要数据面进行假重组开关时,输入指针为NULL */
    SFE_PUB_SHAREVAR_NULL_SET_AUTOFAKEREASSSWITCH,      /* 12 设置自动假重组开关时,核间共享变量为NULL */

    SFE_PUB_ERR_CREATEBOX_FAIL,                         /* 13 创建黑匣子失败 */
    SFE_PUB_ERR_SETBOXPARSE_FAIL,                       /* 14 设置黑匣子解析函数失败 */
    SFE_PUB_ERR_SETBOXRECORD_MANUALSTAT_FAIL,           /* 15 设置记录手动统计信息到黑匣子失败 */
    SFE_PUB_ERR_SETBOXRECORD_AUTOSTAT_FAIL,             /* 16 设置记录自动统计信息到黑匣子失败 */
    SFE_PUB_ERR_SETBOXRECORD_MANUALSIZE_FAIL,           /* 17 黑匣子时空间不够 */
    SFE_PUB_ERR_GETVLANIDHOOK_POINTNULL,                /* 18 获取VLAN ID钩子注册函数指针为空 */
    SFE_PUB_ERR_IPPKTPROCPOLICY_POINTNULL,              /* 19 获取三层报文处理策略钩子注册函数指针为空 */
    SFE_PUB_ERR_IPPKTPSNDINFO_POINTNULL,                /* 20 获取发送IP报文的出接口和目的MAC等信息钩子注册函数指针为空 */
    SFE_PUB_ERR_PKTRCVUSERPREPROC_POINTNULL,            /* 21 数据面用户态报文接收入口产品预处理钩子注册函数指针为空 */
    SFE_PUB_ERR_PKTSNDUSERPREPROC_POINTNULL,            /* 22 数据面用户态报文发送入口产品预处理钩子注册函数指针为空 */
    SFE_PUB_ERR_GETSOCKETID_POINTNULL,                  /* 23 数据面用户态根据产品连接ID和报文上下行属性向产品获取socket id的函数钩子注册函数指针为空 */
    SFE_PUB_ERR_STATINFONOTIFY_POINTNULL,               /* 24 数据面用户态注册统计信息通知钩子注册函数指针为空 */

    SFE_PUB_ERR_INPUT_POINTNULL_NAKESENDPKT,            /* 25 根据用户指定信息直接发送MUBF时输入的MBUF指针为空 */
    SFE_PUB_ERR_INPUT_IFID_NULL_NAKESENDPKT,            /* 26 根据用户指定信息直接发送MUBF时输入的IFID指针为空 */
    SFE_PUB_ERR_SEND_FAILED_NAKESENDPKT,                /* 27 根据用户指定信息直接发送MUBF时发送消息失败 */
    SFE_PUB_ERR_CALL_NAKESENDPKT_BEFORE_INIT,           /* 28 在系统初始化之前调用对外API */

}SFE_PUB_ERR_CODE_E;

/* IPFWD模块错误码 */
/* 问题单:DTS2010110502669,遗漏typedef */
typedef enum enumSfeIPFwdRetCode
{
    SFE_IPFWD_OK = SFE_OK,
    SFE_IPFWD_ERR_BEGIN = SFE_IPFWD_BEGIN_RET_CODE, /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_IPFWD_MALLOC_IPID_ERR,                      /* 1 分配IPID全局变量失败 */
    SFE_IPFWD_MALLOC_ROUTEID_ERR,                   /* 2 分配Src ip全局变量失败 */
    SFE_IPFWD_MALLOC_FAIL_AUTOFAKEREASS,            /* 3 分配自动假重组开关核间共享内存失败 */
    SFE_IPFWD_MALLOC_FAIL_ACLNEEDFAKEREASS,         /* 4 分配ACL处理是否需要数据面进行假重组开关核间共享内存失败 */
    SFE_IPFWD_GETSENDIFO_FAIL,                      /* 5 在四层转发发送报文时向产品获取报文发送信息失败 */
    SFE_IPFWD_GETIFIFO_FAIL,                        /* 6 在四层转发报文时根据向产品获取的接口ID获取接口信息失败 */
    SFE_IPFWD_NO_GETSENDINFO_HOOK,                  /* 7 产品没有注册获取报文发送信息的钩子函数 */
    SFE_IPFWD_MBUFBACKWARD_FAIL,                    /* 8 在四层转发报文时,MBUF指针归位到以太头失败*/
    SFE_IPFWD_SENDIPPKT_MTOD_FAIL,                  /* 9 发送IP报文获取以太头失败 */
    SFE_IPFWD_PKTSND_USERPREPROC_FAIL,              /* 10 发送IP报文时产品预处理失败 */
    SFE_IPFWD_SENDTO_DRIVER_FAIL,                   /* 11 发送报文到底层失败 */
    SFE_IPFWD_GETIPHDR_FAIL,                        /* 12 发送报文,获取Mbuf的IP头失败 */
    SFE_IPFWD_MBUFFRAG_FAIL,                        /* 13 发送报文,对报文进行IP分片失败 */
    SFE_IPFWD_FRAG_NOT_ALLOWED,                     /* 14 发送报文,IP报文需要分片,但是分片标志为不允许分片 */
    SFE_IPFWD_MBUFBACKWARD_IPHDR_FAIL,              /* 15 发送报文,MBUF指针指向IP头失败 */
    SFE_IPFWD_MBUFFORWARD_IPHDR_FAIL,               /* 16 发送报文,MBUF指针跳过IP头指向IP报文内容失败 */
    SFE_IPFWD_MTU_ERR,                              /* 17 发送报文,MTU太小 */
    SFE_IPFWD_FRAG_FAIL,                            /* 18 发送报文,对IP报文进行分片失败 */
    SFE_IPFWD_MBUF_BACKWARD_FAIL,                   /* 19 发送报文,对Mbuf头向后偏移失败 */
    SFE_IPFWD_FIRST_MBUF_CREATE_FAIL,               /* 20 发送报文,将Mbuf分片时创建首片的Mbuf失败 */
    SFE_IPFWD_OTHER_MBUF_CREATE_FAIL,               /* 21 发送报文,将Mbuf分片时创建首片后的Mbuf失败 */
    SFE_IPFWD_MTU_LESS_THAN_IPHEADER_LENGTH,        /* 22 MTU小于IP头长度,分片失败 */
    SFE_IPFWD_MBUFFORWARD_FIRST_FRAG_FAIL,          /* 23 发送报文,MBUF指针跳过第一片指向第二片IP报文内容失败 */
    SFE_IPFWD_MBUFFRAG_EITH_OLDMBUF_FAIL,           /* 24 发送报文,对原始报文进行IP分片失败 */

}SFE_IPFWD_ERR_CODE_E;

/* ACL处理需要数据面进行假重组处理 */
#define SFE_ACL_NEED_FAKEREASS_SWITCH_ON    1
/* ACL处理不需要数据面进行假重组处理 */
#define SFE_ACL_NEED_FAKEREASS_SWITCH_OFF   0


/* 钩子函数返回值含义说明:
   ACL安全过滤钩子只能返回以下两个值:SFE_MBUF_NOTHANDLE和SFE_MBUF_REQUIREDROP;
   FWD本地报文过滤钩子函数返回值只能是以下几种,各返回值含义描述如下; */
#define SFE_MBUF_HAVEHANDLE     0     /* 表示MBUF已被钩子处理,对于该返回值VISP将直接返回UID_STATE_TOHW状态进行报文发送 */
#define SFE_MBUF_NOTHANDLE      1     /* 表示MBUF未被钩子处理,VISP将继续沿着原来处理流程进行报文处理 */
#define SFE_MBUF_REQUIREDROP    2     /* 表示MBUF需要释放,此情况VISP将直接返回MCUP_UID_STATE_SFE_ERROR状态来释放报文 */

/* ACL过滤钩子 */
typedef UINT32 (*g_pfSfePktAclFilterHook)(SFE_MBUF_S * pstMbuf);
/*******************************************************************************
*    Func Name: SFE_RegFuncAclFilterHook
* Date Created: 2009-09-12
*       Author: wuhailan103194
*  Description: ACL安全过滤钩子
*        Input: g_pfSfePktAclFilterHook pfRegFunc:函数指针
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-12   wuhailan103194          Create
*
*******************************************************************************/
extern UINT32 SFE_RegFuncAclFilterHook(g_pfSfePktAclFilterHook pfRegFunc);


typedef UINT32 (*g_pfSfeLocalPktHook)(SFE_MBUF_S *pstMbuf);
/*******************************************************************************
*    Func Name: SFE_RegFuncLocalPkt
* Date Created: 2009-08-21
*       Author: L00105073
*  Description: 注册FWD本地报文过滤钩子
*        Input: g_pfSfeLocalPktHook pfRegFunc:待注册的钩子
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   L00105073                                     Create
*
*******************************************************************************/
extern UINT32 SFE_RegFuncLocalPkt(g_pfSfeLocalPktHook pfRegFunc);

/*******************************************************************************
*    Func Name: SFE_SetAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 设置ACL处理是否需要数据面进行假重组开关以支持精确匹配功能
*        Input: UINT32 u32Switch: 开关,
*               取值: SFE_ACL_NEED_FAKEREASS_SWITCH_ON: ACL处理需要数据面进行假重组处理
*                     SFE_ACL_NEED_FAKEREASS_SWITCH_OFF: ACL处理不需要数据面进行假重组处理
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_SetAclNeedFakeReassSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: SFE_GetAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 获取ACL处理是否需要数据面进行假重组开关以支持精确匹配功能
*        Input: 
*       Output: UINT32 *pu32Switch: 开关值,取值含义请参见TCPIP_SFE_SetAclNeedFakeReassSwitch接口说明
*       Return: 成功: 0
*               失败: 其它
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_GetAclNeedFakeReassSwitch(UINT32 *pu32Switch);

/*******************************************************************************
*    Func Name: SFE_ShowAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示ACL处理是否需要数据面进行假重组开关以支持精确匹配功能
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID SFE_ShowAclNeedFakeReassSwitch(VOID);

/*******************************************************************************
*    Func Name: SFE_BoxRecordShow
* Date Created: 2009-10-31
*       Author: wuhailan103194
*  Description: 用于显示黑匣子中的记录，显示的顺序为逆序，即先显示最后写入到黑匣子中的记录。
*        Input: UINT32 u32Begin:忽略最后的记录数。
*               UINT32 u32RecNum:需要显示的记录数，当为0时，表示显示这个黑匣子的所有记录。
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-31   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_BoxRecordShow(UINT32 u32Begin, UINT32 u32RecNum);

/*******************************************************************************
*    Func Name: SFE_BoxRecordWrite
* Date Created: 2009-10-28
*       Author: wuhailan103194
*  Description: 向黑匣子记录需要记录的信息
*        Input: 
*       Output: 
*       Return: 成功SFE_OK，其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-28   wuhailan103194          Create
*
*******************************************************************************/
extern UINT32 SFE_BoxRecordWrite(VOID);

/* g_pfSfePktRcvUserPreProcHook钩子函数返回值含义说明:
   钩子函数返回值只能是以下几种,各返回值含义描述如下; */
/* 报文由VISP处理,VISP将继续沿着原来处理流程进行报文处理 */
#define SFE_PKT_STACK_HANDLE     0
/* 报文由产品处理,产品需要负责释放报文 */
#define SFE_PKT_USER_HANDLE      1

/*******************************************************************************
*    Func Name: g_pfSfePktRcvUserPreProcHook
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 数据面用户态报文接收入口产品预处理钩子
*  Description: 数据面用户态报文接收入口产品预处理钩子
*        Input: SFE_MBUF_S *pstMbuf: MBUF报文<非空>
*       Output: UINT32 *pu32RcvPolicy: 该报文由VISP处理还是由产品直接处理,
*               产品只能输出以下取值: 0:由VISP处理；1:由产品直接处理(产品需要负责释放该MBUF).
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.VISP在用户态接收报文入口将报文交给产品进行定制特性预处理,
*                 如果产品不注册该钩子则报文默认由VISP协议栈处理。
*               2.该钩子函数返回失败时,VISP会释放该报文,所以如果该报文由产
*                 品处理则必须返回成功0,并且需要负责释放报文.
*               3.当前在SCG产品的应用下,该钩子需要实现以下功能:
*                 (1)解析产品FCB信息并将相关信息设置到MBUF中,当前有报文分发KEY值,
*                    连接ID,报文上下行属性,产品自有信息FCB.产品需要在该钩子函数中将报文尾部的产品自有数据砍掉.
*                    产品需要保证FCB信息设置正确.
*                 (2)还原报文信息.LC与SPU之间的报文分发机制会将IP头中的TOS修改为报文分发KEY值
*                    以保证同一个用户的数据流分发到同一个核上处理.
*                    所以产品必须将其还原为原始报文并重新计算IP校验和.
*                 (3)该钩子也作为LC与SPU之间产品控制报文的接收通道.
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_RegFuncPktRcvUserPreProcHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
typedef UINT32 (*g_pfSfePktRcvUserPreProcHook)(SFE_MBUF_S * pstMbuf, UINT32 *pu32RcvPolicy);

/*******************************************************************************
*    Func Name: SFE_RegFuncPktRcvUserPreProcHook
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 注册数据面用户态报文接收入口产品预处理钩子
*  Description: 注册数据面用户态报文接收入口产品预处理钩子
*        Input: g_pfSfePktRcvUserPreProcHook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution:
*        Since: DOPRA VISP V2R3C02
*    Reference: g_pfSfePktRcvUserPreProcHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
extern UINT32 SFE_RegFuncPktRcvUserPreProcHook(g_pfSfePktRcvUserPreProcHook pfRegFunc);

/*******************************************************************************
*    Func Name: g_pfSfePktSndUserPreProcHook
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 数据面用户态报文报文发送产品预处理钩子
*  Description: 数据面用户态报文报文发送产品预处理钩子
*        Input: SFE_MBUF_S *pstMbuf: MBUF报文<非空>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.该钩子函数返回失败时,VISP会释放该报文.
*               2.当前在SCG产品的应用下,该钩子需要实现以下功能:
*                 (1)产品需要在该函数中从MBUF中获取FCB信息并将FCB信息添加到报文尾部,以将这些信息带到LC线卡
*                 (2)产品分发KEY值在显示代理场景下由VISP设置到MBUF中.在其它场景下使用接收时产品告知的分发KEY值.
*                 (3)对于TCP显示代理场景下的连接ID,VISP MBUF中填写的连接ID是产品设置到VISP的连接ID.正确性由产品保证.
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_RegFuncPktSndUserPreProcHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
typedef UINT32 (*g_pfSfePktSndUserPreProcHook)(SFE_MBUF_S * pstMbuf);

/*******************************************************************************
*    Func Name: SFE_RegFuncPktSndUserPreProcHook
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 注册数据面用户态报文发送出口产品预处理钩子
*  Description: 注册数据面用户态报文发送出口产品预处理钩子
*        Input: g_pfSfePktSndUserPreProcHook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution:
*        Since: DOPRA VISP V2R3C02
*    Reference: g_pfSfePktSndUserPreProcHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
extern UINT32 SFE_RegFuncPktSndUserPreProcHook(g_pfSfePktSndUserPreProcHook pfRegFunc);

/* IP报文接收处理策略,产品只能返回以下几种策略取值 */
typedef enum enumSfeIpPktRcvPolicy
{
    SFE_IPPKTRCV_POLICY_NORMAL = 0,                  /* VISP按照正常流程处理(查路由和ARP进行正常转发和本地接收处理) */
    SFE_IPPKTRCV_POLICY_PROXY,                       /* VISP进行透明代理处理 */
    SFE_IPPKTRCV_POLICY_REORDER,                     /* VISP进行重排处理 */
    SFE_IPPKTRCV_POLICY_LOCALRCV,                    /* VISP直接进行本地接收处理(如:显示代理),不查找路由和判断是否是本机接收报文 */
    SFE_IPPKTRCV_POLICY_DROP,                        /* VISP丢弃报文处理 */
    SFE_IPPKTRCV_POLICY_MAX,                         /* 边界值,非法无效值 */
}SFE_IPPKTRCV_POLICY_E;

/*******************************************************************************
*    Func Name: g_pfSfeIpPktRcvProcPolicyHook
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 从产品获取三层报文接收处理策略钩子函数原型
*  Description: 从产品获取三层报文接收处理策略钩子函数原型
*        Input: SFE_MBUF_S *pstMbuf: MBUF报文<非空>
*       Output: 
*       Return: IP报文接收处理策略,取值参见SFE_IPPKTRCV_POLICY_E枚举定义
*      Caution:
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_RegFuncIpPktRcvProcPolicyHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
typedef UINT32 (*g_pfSfeIpPktRcvProcPolicyHook)(SFE_MBUF_S * pstMbuf);

/*******************************************************************************
*    Func Name: SFE_RegFuncIpPktRcvProcPolicyHook
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 注册从产品获取三层报文接收处理策略的钩子函数
*  Description: 注册从产品获取三层报文接收处理策略的钩子函数
*        Input: g_pfSfeIpPktRcvProcPolicyHook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution:
*        Since: DOPRA VISP V2R3C02
*    Reference: g_pfSfeIpPktRcvProcPolicyHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
extern UINT32 SFE_RegFuncIpPktRcvProcPolicyHook(g_pfSfeIpPktRcvProcPolicyHook pfRegFunc);

/*******************************************************************************
*    Func Name: g_pfSfeGetIpPktSndInfoHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 向产品获取发送IP报文的出接口及目的MAC等信息的钩子函数原型,后续发
*               送报文时不查找路由和ARP表项直接根据获取的信息发送.
*  Description: 向产品获取发送IP报文的出接口及目的MAC等信息的钩子函数原型,后续发
*               送报文时不查找路由和ARP表项直接根据获取的信息发送.
*        Input: SFE_MBUF_S *pstMbuf: 报文MBUF指针
*       Output: SFE_MBUF_IFID_S *pstIfId: 出接口ID信息 <非NULL>
*               UINT8 *pu8DstMac: 目的physical地址(调用者提供的内存空间大小为6字节) <非NULL>
*               UINT32 *pu32VlanId: VLAN ID, 封装VLAN头使用. <非NULL>
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
typedef UINT32 (*g_pfSfeGetIpPktSndInfoHook)(SFE_MBUF_S *pstMbuf, SFE_MBUF_IFID_S *pstIfId,
                                                   UINT8 *pu8DstMac, UINT32 *pu32VlanId);

/*******************************************************************************
*    Func Name: SFE_RegFuncGetIpPktSndInfoHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 注册发送IP报文时获取发送出接口和目的MAC等信息的钩子函数
*  Description: 注册发送IP报文时获取发送出接口和目的MAC等信息的钩子函数
*        Input: g_pfSfeGetIpPktSndInfoHook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786             Create
*
*******************************************************************************/
extern UINT32 SFE_RegFuncGetIpPktSndInfoHook(g_pfSfeGetIpPktSndInfoHook pfRegFunc);

/* 统计信息类型 */
typedef enum enumSfeUserStatisticType
{
    SFE_USTAT_TYPE_UNCLASSIFY = 0,                    /* 不需要关注类型的统计 */
    SFE_USTAT_TYPE_DROP,                              /* 协议栈丢弃报文进行的统计 */
    SFE_USTAT_TYPE_SEND,                              /* 协议栈主动发送进行的统计 */
    SFE_USTAT_TYPE_FORWARD,                           /* 协议栈的TCP重排正常转发的统计 */
    SFE_USTAT_TYPE_RXMT,                              /* 协议栈主动发送时重传的统计 */
    SFE_USTAT_TYPE_MAX,                               /* 统计类型边界无效值 */
}SFE_USER_STATISTIC_TYPE_E;

/* 统计原因 */
typedef enum enumSfeUserStatisticReason
{
    SFE_USTAT_REASON_UNCLASSIFY = 0,                     /* 00不需要关注原因的统计 */
    SFE_USTAT_REASON_DROP_PRODUCT_POLICY,                /* 01丢弃报文统计,原因:产品应用丢包,统一使用该值,内部不能使用 */

    SFE_USTAT_REASON_DROP_TCP_HDRDATALEN_ERROR,          /* 02丢弃报文统计,原因:TCP头中记录的数据长度错误,L7长度为L3长度 */
    SFE_USTAT_REASON_DROP_TCP_CHKSUM_ERROR,              /* 03丢弃报文统计,原因:TCP校验和错误 */
    SFE_USTAT_REASON_DROP_TCP_FLAGS_ERROR,               /* 04丢弃报文统计,原因:TCP flags错误 */
    SFE_USTAT_REASON_DROP_TCP_DATALEN_ERROR,             /* 05丢弃报文统计,原因:IP包长度小于mbuf总长度,删除mbuf尾部多余失败 */
    SFE_USTAT_REASON_DROP_TCP_REORDERESTABLISH_ERROR,    /* 06丢弃报文统计,原因:TCP重排建连失败 */
    SFE_USTAT_REASON_DROP_TCP_REORDERRST_ERROR,          /* 07丢弃报文统计,原因:TCP重排收到RST错误 */
    SFE_USTAT_REASON_DROP_TCP_REORDERFIN_ERROR,          /* 08丢弃报文统计,原因:TCP重排收到FIN错误 */
    SFE_USTAT_REASON_DROP_TCP_REORDERMBUFFORWARD_ERROR,  /* 09丢弃报文统计,原因:TCP重排前移MBUF失败 */
    SFE_USTAT_REASON_DROP_TCP_REORDERRCVSEQNUM_ERROR,    /* 10丢弃报文统计,原因:TCP重排收到报文序号错误 */
    SFE_USTAT_REASON_DROP_TCP_REORDEROVERWND_ERROR,      /* 11丢弃报文统计,原因:TCP重排收到的报文超出窗口 */
    SFE_USTAT_REASON_DROP_TCP_REORDERMBUFBACKWARD_ERROR, /* 12丢弃报文统计,原因:TCP重排发送报文后移MBUF失败 */
    SFE_USTAT_REASON_DROP_TCP_REORDERREASSMBUFFWD_ERROR, /* 13丢弃报文统计,原因:TCP重排重组发送报文前移MBUF失败 */
    SFE_USTAT_REASON_DROP_TCP_SYNDATA,                   /* 14丢弃报文统计,原因:TCP重排SYN带数据建连 */
    SFE_USTAT_REASON_DROP_TCP_REORDER_REASS_CACHE_FULL,  /* 15丢弃报文统计,原因:TCP重排乱序重组重复缓存中报文个数超出界限 */
    SFE_USTAT_REASON_DROP_TCP_MBUF_CONTINUOUS_ERROR,     /* 16丢弃报文统计,原因:在TCP处理时将含有多个DB的MBUF连续化失败,L7长度为mbuf长度 */
    SFE_USTAT_REASON_DROP_TCP_REORDER_INVALID_FIN,       /* 17丢弃报文统计,原因:TCP重排有效接收FIN状态收到的FIN序号小于期望序号 */
    SFE_USTAT_REASON_DROP_TCP_REPTDATA,                  /* 18丢弃报文统计,原因:TCP重排中部分重复数据删除(L3L7长度为丢弃部分数据长度) */

    SFE_USTAT_REASON_DROP_UDP_HDRDATALEN_ERROR,          /* 19丢弃报文统计,原因:UDP头中记录的数据长度错误 */
    SFE_USTAT_REASON_DROP_UDP_DATALEN_ERROR,             /* 20丢弃报文统计,原因:IP报文长度小于mbuf总长度cut数据失败 */
    SFE_USTAT_REASON_DROP_UDP_CHKSUM_ERROR,              /* 21丢弃报文统计,原因:UDP校验和错误 */
    SFE_USTAT_REASON_DROP_UDP_NEWSOCKNODE_ERROR,         /* 22丢弃报文统计,原因:UDP重排收到时申请sock节点资源失败 */
    SFE_USTAT_REASON_DROP_UDP_SOCKCREATENOTIFY_ERROR,    /* 23丢弃报文统计,原因:UDP重排创建sock节点通知失败 */
    SFE_USTAT_REASON_DROP_UDP_SOCKNOFIND_ERROR,          /* 24丢弃报文统计,原因:UDP标准时查找sock节点失败 */
    SFE_USTAT_REASON_DROP_UDP_MBUFBACKWARD_ERROR,        /* 25丢弃报文统计,原因:UDP重排发送报文后移MBUF失败 */
    SFE_USTAT_REASON_DROP_UDP_FORWARD_ERROR,             /* 26丢弃报文统计,原因:UDP偏移掉头部失败 */
    SFE_USTAT_REASON_DROP_UDP_MBUF_CONTINUOUS_ERROR,     /* 27丢弃报文统计,原因:在UDP处理时将含有多个DB的MBUF连续化失败,L7长度为mbuf长度 */

    SFE_USTAT_REASON_DROP_IP_REASSOFFSET_ERROR,          /* 28丢弃报文统计,原因:IP重组偏移量错误,L7长度为L3-IP首部长 */
    SFE_USTAT_REASON_DROP_IP_REASSPKTLEN_ERROR,          /* 29丢弃报文统计,原因:IP重组报文长度错误,L7长度为L3-IP首部长 */
    SFE_USTAT_REASON_DROP_IP_REASSLOCK_ERROR,            /* 30丢弃报文统计,原因:IP重组锁失败,L7长度为L3-IP首部长 */
    SFE_USTAT_REASON_DROP_IP_REASSNODE_ERROR,            /* 31丢弃报文统计,原因:IP重组获取HASH节点失败,L7长度为L3-IP首部长 */
    SFE_USTAT_REASON_DROP_IP_REASSMAXPKTNUM_ERROR,       /* 32丢弃报文统计,原因:IP重组达到最大分片数失败,L7长度为L3-IP首部长 */
    SFE_USTAT_REASON_DROP_IP_REASSPRENODECOVER_ERROR,    /* 33丢弃报文统计,原因:IP重组重复前面报文失败,L7长度为L3-IP首部长 */
    SFE_USTAT_REASON_DROP_IP_REASSFOLLOWNODECOVER_ERROR, /* 34丢弃报文统计,原因:IP重组重复后面报文失败,L7长度为L3-IP首部长 */
    SFE_USTAT_REASON_DROP_IP_REASSHASH_TIMEOUT,          /* 35丢弃报文统计,原因:IP重组超时释放队列,L7长度为L3-IP首部长 */
    SFE_USTAT_REASON_DROP_IP_GETSENDIFO_ERROR,           /* 36丢弃报文统计,原因:IP转发报文向产品获取报文发送的相关信息失败 */
    SFE_USTAT_REASON_DROP_IP_GETIFIFO_ERROR,             /* 37丢弃报文统计,原因:IP转发获取发送报文接口控制块地址失败 */
    SFE_USTAT_REASON_DROP_IP_GETIPHDR_ERROR,             /* 38丢弃报文统计,原因:IP转发获取发送报文IP报文头失败 */
    SFE_USTAT_REASON_DROP_IP_TTL_ERROR,                  /* 39丢弃报文统计,原因:IP转发报文TTL值耗尽 */
    SFE_USTAT_REASON_DROP_IP_PKT_CHECK_ERROR,            /* 40丢弃报文统计,原因:IP接收报文检查失败,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_IP_BROADCAST_PKT,              /* 41丢弃报文统计,原因:IP接收广播报文当前丢弃处理,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_IP_MULTICAST_PKT,              /* 42丢弃报文统计,原因:IP接收多播报文当前丢弃处理,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_IP_NON_TCPUDP_PKT,             /* 43丢弃报文统计,原因:IP接收不支持非TCP/UDP报文重排代理处理,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_IP_POLICY_DROP_PKT,            /* 44丢弃报文统计,原因:IP接收产品策略钩子返回丢弃报文,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_IP_PKT_REASS_PREOVERLAP,       /* 45丢弃报文统计,原因:IP重组时前部数据重复,L3L7长度为丢弃部分数据长度 */
    SFE_USTAT_REASON_DROP_IP_PKT_REASS_NXTOVERLAP,       /* 46丢弃报文统计,原因:IP重组时后部数据重复,L3L7长度为丢弃部分数据长度 */
    SFE_USTAT_REASON_DROP_IP_MBUFBACKWARD_ERROR,         /* 47丢弃报文统计,原因:IP重组后报文后移MBUF失败 */

    SFE_USTAT_REASON_DROP_SOCK_BUFFULL_ERROR,            /* 48丢弃报文统计,原因:socket的buf满 */
    SFE_USTAT_REASON_DROP_SOCK_CACHEPKT_ERROR,           /* 49丢弃报文统计,原因:socket删除时缓冲区的报文 */
    SFE_USTAT_REASON_DROP_SOCK_REASSPKT_ERROR,           /* 50丢弃报文统计,原因:socket删除时重组队列中的报文 */
    SFE_USTAT_REASON_DROP_SOCK_REASSCACHEPKT_ERROR,      /* 51丢弃报文统计,原因:socket删除时重组缓存队列中的报文 */
    SFE_USTAT_REASON_DROP_SOCK_RCVCACHEPKT_ERROR,        /* 52丢弃报文统计,原因:socket删除时接收缓存区中的报文 */
    SFE_USTAT_REASON_DROP_SOCK_SNDCACHEPKT_ERROR,        /* 53丢弃报文统计,原因:socket删除时发送缓存区中的报文 */

    SFE_USTAT_REASON_DROP_FASTPASS_NET_PKTCHK_ERR,       /* 54丢弃报文统计,原因:快通道校验IP包失败,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_FASTPASS_NOT_PROC_BROADCAST,   /* 55丢弃报文统计,原因:快通道不处理广播包,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_FASTPASS_NOT_PROC_MULTICAST,   /* 56丢弃报文统计,原因:快通道不处理多播包,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_FASTPASS_NON_TCPUDP_PKT,       /* 57丢弃报文统计,原因:快通道不处理非TCP和UDP报文,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_FASTPASS_POLICY_DROP_PKT,      /* 58丢弃报文统计,原因:快通道获取策略为代理或丢弃时,丢弃报文,L3L7长度为mbuf总长 */
    SFE_USTAT_REASON_DROP_FASTPASS_NON_PROC_POLICY,      /* 59丢弃报文统计,原因:快通道获取报文处理策略失败,L3L7长度为mbuf总长 */

    SFE_USTAT_REASON_STACK_PROC_END,                     /* 60协议栈直接转发的报文 */

    SFE_USTAT_REASON_DROP_TCP_REORDER_REDIRECTION_RCV,               /* 61丢弃报文统计,原因:该条流做了重定向,后续所有报文终结 */
    SFE_USTAT_REASON_SEND_TCP_REORDER_REDIRECTION_AOXRXMT,           /* 62发送报文统计,原因:该条流做了重定向,后续有重传AOX报文 */
    SFE_USTAT_REASON_SEND_TCP_REORDER_REDIRECTION_RST,               /* 63发送报文统计,原因:该条流做了重定向,后续有主动发送的RST报文 */
    SFE_USTAT_REASON_DROP_IP_PKT_REASS_OTHERIPHD ,                   /* 64丢弃报文统计,原因:IP重组时分片报文的IP首部只保留一个,L3L7长度为丢弃的IP首部长度 */
    SFE_USTAT_REASON_DROP_R2P_REASSPKT_ERROR,                        /* 65丢弃报文统计,原因:重排转透明代理中丢弃所有缓存报文 */
    SFE_USTAT_REASON_DROP_TCP_RDR_DUPPKT_BFR_POLICY_SURE,            /* 66丢弃报文统计,原因:重排模式下未明确是否要转透明代理,收到重传报文 */
    SFE_USTAT_REASON_DROP_UDP_SOCKMODE_NOTMATCH,                     /* 67丢弃报文统计,原因:UDP重排或代理模式下收到的报文策略和socket不匹配 */
    SFE_USTAT_REASON_DROP_TCP_RDR_SOCKMODE_NOTMATCH,                 /* 68丢弃报文统计,原因:TCP重排模式下收到的报文策略和socket不匹配 */  
    SFE_USTAT_REASON_DROP_TCP_PROXY_NOTCPCB,                         /* 69丢弃报文统计,原因:代理下,TCP控制块为空*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_POLICY_NOT_MATCH,                /* 70丢弃报文统计,原因:代理下,收到策略不匹配的报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_TCP_CLOSED,                      /* 71丢弃报文统计,原因:代理下,用户已关闭，仍收到报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCV_NODATA_FIN,                  /* 72丢弃报文统计,原因:代理下,收到不带数据的FIN报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_OTHER_CONTROLPKT,                /* 73丢弃报文统计,原因:代理下,在接收数据时终结非数据非FIN的控制报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCV_PURE_ACK,                    /* 74丢弃报文统计,原因:代理下,收到合法的纯ACK报文 */    
    SFE_USTAT_REASON_DROP_TCP_PROXY_RECV_RETRAN_PKT,                 /* 75丢弃报文统计,原因:代理下,收到重传数据,L3L7长度为重传数据长度*/        
    SFE_USTAT_REASON_DROP_TCP_PROXY_RECV_OVERWINDOW_PKT,             /* 76丢弃报文统计,原因:代理下,收到超窗数据,L3L7长度为超窗数据长度 */  
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_RCV_HDR_COMPLETELY_DUP,    /* 77丢弃报文统计,原因:重组时,收到报文前段与重组队列有完全重复的报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_RCV_HDR_DUPPKT,            /* 78丢弃报文统计,原因:重组时,收到报文前段与重组队列有重复,L3L7长度为重复数据长度*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_RCV_TAIL_DUPPKT,           /* 79丢弃报文统计,原因:重组时,收到报文后段与重组队列有重复,L3L7长度为重复数据长度 */
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_RCV_TAIL_COMPLETELY_DUP,   /* 80丢弃报文统计,原因:重组时,收到报文后段与重组队列有完全重复的报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_CANTRCVMORE,               /* 81丢弃报文统计,原因:重组时,上层socket无法再接收数据*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCV_DUPSYN_BUT_EXPECTSEQ,        /* 82丢弃报文统计,原因:代理下,收到重复的SYN,但序号为期望的序号 */
    SFE_USTAT_REASON_SEND_HAVE_COMPLETELY_DUP_PKT,                   /* 83发送报文统计,原因:发送报文时,存在完全重复数据,L3L7长度为重传报文长度 */
    SFE_USTAT_REASON_SEND_HAVE_PART_DUP_PKT,                         /* 84发送报文统计,原因:发送报文时,存在部分重复数据,,L3L7长度为重传长度 */
    SFE_USTAT_REASON_DROP_TCP_PROXY_RECV_OVERWINDOW_PKT_AT_RCVSYN,   /* 85丢弃报文统计,原因:在处理带数据的SYN报文时,数据存在超窗,L3L7为超窗数据长度 */
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVDUPSYN,           /* 86丢弃报文统计,原因:在连接建立完成后收到SYN报文直接回ACK后丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_DUPLICATE_RCVRST,                /* 87丢弃报文统计,原因:直接丢弃重复的RST报文,即RST报文中的序号
                                                                               比当前期望接收的序号小并且报文完全重复则直接丢弃报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_NOTEXPECT_PARTDUPLICATE_RCVRST,  /* 88丢弃报文统计,原因:带部分重复数据的RST报文,只要RST报文不是期望的接收序号直接回ACK后丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ALREADY_CLOSE_RCVPKT,            /* 89丢弃报文统计,原因:用户已经主动调用了close函数关闭socket.
                                                                               本端的就不能再接收新数据,如果此时再收到对端发送来的新数据则直接回复RST后断连*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_EXCEED_WINDOW_RCVPKT,            /* 90丢弃报文统计,原因:对于完全超出接收窗口的报文回应ACK后直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_EXCEED_WINDOW_RCVPKT_ESTABLISHED,/* 91丢弃报文统计,原因:连接建立完成后的完全超出接收窗口的报文直接回应ACK后丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LISTEN_RCVRST,                   /* 92丢弃报文统计,原因:在LISTEN时，收到RST报文，直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LISTEN_RCVACK,                   /* 93丢弃报文统计,原因:在LISTEN时，收到ACK报文，终止该报文，回RST*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LISTEN_RCVNOTSYN,                /* 94丢弃报文统计,原因:在LISTEN时，收到非SYN报文，直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LISTEN_RCVDSTMULTICAST,          /* 95丢弃报文统计,原因:在LISTEN时，收到TCP连接报文的目的地址不能是多播地址和广播地址*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_SYNSEND_RCVERRACK,               /* 96丢弃报文统计,原因:在SYNSEND时，主动建连端期望收到对端的SYN/ACK时,
                                                                               收到报文中的ACK序号不合法则回RST后丢弃报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_SYNSEND_RCVRST,                  /* 97丢弃报文统计,原因:在SYNSEND时，收到RST报文，直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_SYNSEND_RCVNOTSYN,               /* 98丢弃报文统计,原因:在SYNSEND时，收到非SYN报文，直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_NOTLISTEN_RCVNOTACK,             /* 99丢弃报文统计,原因:只有LISTEN和SYN_SENT状态的报文可以不携带ACK,并且已经处理过,
                                                                                如果还收到ACK报文，直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_SYNRECEIVED_RCVERRACK,           /* 100丢弃报文统计,原因:连接建立过程中ACK序号不合法应该做断连处理*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVDUPACK,           /* 101丢弃报文统计,原因:收到重复的ACK报文，直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVDUPACK_GTREXMTTHRESH,/* 102丢弃报文统计,原因:启动快速重传算法后，收到重复的ACK报文，直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVOLDACK,           /* 103丢弃报文统计,原因:丢弃非当前期望接收序号的很老的ACK报文.
                                                                                如果该ACK的序号远远小于当前期望接收的ACK序号并且报文的序号不是当前期望接收的序号,
                                                                                我们可以认为这是一个在网络上被延迟很久的重复报文. 直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LASTACK_FINISACKED,              /* 104丢弃报文统计,原因:被动断连完成,通知产品断连完成并释放资源，并丢弃报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_TIMEWAIT_RCVPKT,                 /* 105丢弃报文统计,原因:在TIMEWAIT下，收到报文，回复ACK后丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCVERRRST,                       /* 106丢弃报文统计,原因:收到非法的RST报文，回复ACK后丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCVRST,                          /* 107丢弃报文统计,原因:收到合法的RST报文，处理后，丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_CREATECHILDSOCKET_FAILED,        /* 108丢弃报文统计,原因:创建子socket失败，直接丢弃报文*/    
    SFE_USTAT_REASON_DROP_TCP_PROXY_NOSOCKET_RCVPKT,                 /* 109丢弃报文统计,原因:没有socket接收该报文，直接发送RST后丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVSYN,              /* 110丢弃报文统计,原因:连接建立完成后收到带SYN标志的报文不是期望的则会直接丢弃报文*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCVDUPPKT,                       /* 111丢弃报文统计,原因:收到重复的报文，回复ACK后，丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_OTHERSTATE_RCVSYN,               /* 112丢弃报文统计,原因:建连完成后其余状态(如断连状态)下收到SYN报文直接丢弃*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCV_ACK_TOOMUCH,                 /* 113丢弃报文统计,原因:收到对未发送数据的ACK，回复ACK后丢弃报文*/
    SFE_USTAT_REASON_SIACK_PROC_END,                                 /* 114协议栈直接发送的报文 */
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_FIN_PKT,                   /* 115 丢弃报文统计,原因:收到乱序的FIN报文*/
    SFE_USTAT_REASON_SEND_TCP_REORDER_REASSRXMT,                     /* 116主动发送报文统计,原因:重传乱序包 DTS2012110907656 l00177467*/

    SFE_USTAT_REASON_NO_MAX,                                         /* 统计原因边界无效值 */
}SFE_USER_STATISTIC_REASON_E;

/* 用户统计不关心接收发送 */
#define SFE_USER_STAT_NO_DIRECTION    0
/* 接收报文,在报文接收入口统一设置为该值 */
#define SFE_USER_STAT_RCV    1
/* 发送报文,在用户主动调用发送接口或产品主动构造报文时统一设置为值 */
#define SFE_USER_STAT_SND    2

/* 统计通知信息 */
typedef struct tagSFE_STATISTIC_NOTIFY_INFO
{
    UINT32 u32InOut;            /* 统计方向:接收报文统计;发送报文统计,当前该字段产品可不用 */
    UINT32 u32ConnectionId;     /* 连接ID */
    UINT32 u32Direction;        /* 连接方向:上行,下行 */
    UINT32 u32SrcIP;            /* 报文中的源地址(网络字节序),无法获取地址的时候填为0 */
    UINT32 u32DstIP;            /* 报文中的目的地址(网络字节序),无法获取地址的时候填为0 */
    UINT32 u32StatType;         /* 统计类型 */
    UINT32 u32StatReason;       /* 统计原因 */
    UINT32 u32StatIpPktLen;     /* L3层统计,需统计的IP报文长度(头部加数据长度,并不一定是完整报文长度)
                                   ,在无法获取IP报文长度时填写为整个报文MBUF长度. */
    UINT32 u32StatPktDataLen;   /* L7层统计,需统计的报文中的纯数据长度(不含IP和传输层头的长度,并不一定是完整数据长度)
                                   ,在无法获取数据长度时填写为整个报文MBUF长度.*/
    UINT16 u16VrfIndex;         /* VPN ID */
    UINT8  u8Reserved[2];       /* 填充2字节保证在64位上8字节对齐 */
}SFE_STATISTIC_NOTIFY_INFO_S;

/*******************************************************************************
*    Func Name: g_pfSfeStatisticInfoNotifyHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 统计信息通知钩子
*  Description: 统计信息通知钩子
*        Input: SFE_MBUF_S *pstMbuf: 报文MBUF指针
*               SFE_STATISTIC_NOTIFY_INFO_S *pstStatNotifyInfo: 统计信息
*       Output: 
*       Return: 成功 :0
*               失败 :其它
*      Caution: 1.对于部分重复的数据通知出去的7层长度和三层长度是相同的,
*                 只包括数据长度,不包括IP头和传输层头长度,IP头和传输层头长度算在正常数据中.
*               2.当VISP通知流量统计时,如果产品连接表不存在,产品也可以统计流量.
*               3.异常流量只统计IP层及传输层丢包,链路层异常丢包可不统计.
*               4.只要产品调用发送接口发送的报文,及产品自行构造的报文发送时都不做统计.
*               5.当前产品不能使用pstMbuf参数,当前该参数为NULL用于后续扩展.
*               6.当前只支持TCP重排的统计.
*               7.正常接收的报文统计不通过该钩子通知.所有正常报文的统计信息,
*                 在产品调用接收接口获取数据时随数据一并返回给产品.
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_RegFuncStatisticInfoNotifyHook
*               g_pfSfeStatisticInfoNotifyHook
*               SFE_USER_STATISTIC_TYPE_E
*               SFE_USER_STATISTIC_REASON_E
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
typedef UINT32 (*g_pfSfeStatisticInfoNotifyHook)(SFE_MBUF_S *pstMbuf,
                                                 SFE_STATISTIC_NOTIFY_INFO_S *pstStatNotifyInfo);

/*******************************************************************************
*    Func Name: SFE_RegFuncStatisticInfoNotifyHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 注册统计信息通知钩子函数
*  Description: 注册统计信息通知钩子函数
*        Input: g_pfSfeStatisticInfoNotifyHook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功 :0
*               失败 :其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_RegFuncStatisticInfoNotifyHook
*               g_pfSfeStatisticInfoNotifyHook
*               SFE_USER_STATISTIC_TYPE_E
*               SFE_USER_STATISTIC_REASON_E
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
extern UINT32 SFE_RegFuncStatisticInfoNotifyHook(g_pfSfeStatisticInfoNotifyHook pfRegFunc);

/*******************************************************************************
*    Func Name: g_pfSfeGetVlanIdHook
* Date Created: 2010-06-10
*       Author: w00161372
*      Purpose: 获取VLAN ID钩子函数原型
*  Description: 获取VLAN ID钩子函数原型
*        Input: SFE_MBUF_S *pstMbuf:Mbuf报文指针<非空>
*       Output: UINT32 *pu32VlanId:VLAN ID<非空>
*       Return: 成功 :0
*               失败 :其它
*      Caution: 1.在该钩子中如果需要获取连接ID和报文分发KEY值则应从MBUF中获取不能从FCB中获取,
*                 因为在显示代理情况下此时的连接ID和报文分发KEY值还没有设置到MBUF的自有数据区中的FCB中.
*        Since: DOPRA VISP V2R3C02
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-10   w00161372               Create
*
*******************************************************************************/
typedef UINT32 (*g_pfSfeGetVlanIdHook)(SFE_MBUF_S *pstMbuf, UINT32 *pu32VlanId);

/*******************************************************************************
*    Func Name: SFE_RegFuncGetVlanIdHook
* Date Created: 2010-06-10
*       Author: w00161372
*      Purpose: 注册从产品获取VLAN ID的钩子函数
*  Description: 注册从产品获取VLAN ID的钩子函数
*        Input: g_pfSfeGetVlanIdHook pfHook:g_pfSfeGetVlanIdHook钩子 <非空>
*       Output: 
*       Return: 成功 :0
*               失败 :其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-10   w00161372               Create
*
*******************************************************************************/
extern UINT32 SFE_RegFuncGetVlanIdHook(g_pfSfeGetVlanIdHook pfHook);

/*******************************************************************************
*    Func Name: SFE_NakeSendPkt
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 数据面用户态直接发送产品封装好的报文
*  Description: 数据面用户态直接发送产品封装好的报文
*        Input: SFE_MBUF_S *pstMBuf: 产品封装好的二层报文<非空指针>
*               SFE_MBUF_IFID_S *pstIfId:产品指定的发送报文的接口<非空指针>
*       Output: 
*       Return: 成功 :0
*               失败 :其它
*      Caution: 1.在SCG产品的应用场景下,SPU与LC线卡之间的控制报文通道处理如下:
*                 (1)接收方向(从LC到SPU的控制报文):在VISP用户态接收入口提供钩子由产品区分该报文是由VISP
*                 处理还是产品处理.该钩子与接收时解析FCB信息的钩子合并为一个钩子,
*                 D*I可在该钩子里再提供一个钩子供产品使用。
*                 (2)发送方向(从SPU发送到LC的控制报文):由VISP提供一个发送接口,产品需要指定发送物理接口
*                 (以VISP数据面接口形式表示),完成完整报文的封装,VISP直接按产品指定的接口发送报文.
*               2.该接口无论处理成功还是失败,报文都有协议栈释放.
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
extern UINT32 SFE_NakeSendPkt(SFE_MBUF_S *pstMBuf, SFE_MBUF_IFID_S *pstIfId);

#ifdef  __cplusplus
}
#endif

#endif


