/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_type.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2000-03-27
 *        Author: HouZhipeng
 *   Description: MP模块的数据结构定义（Core）
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000-03-27      HouZhipeng      Create
 *  2005-09-15      YaoChengliang   Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *  2006-05-10      luyao           Adjust for ARM CPU
 *  2008-08-13      f54882          for BC3D00221,同步问题单BC3D00185
 *************************************************************************/

#ifndef _MP_TYPE_H_
#define _MP_TYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif


/* 终端描述信息结构 */
typedef struct tagMP_DISCR_INFO
{
    CHAR  ucUserName[MP_USERNAME_LEN + 2];  /* 用户名; "+ 2:存放结尾符和4字节对齐" */
    UCHAR ucDiscrLen;                       /* 终端描述符长度 */
    UCHAR ucDiscrClass;                     /* 终端描述符类型 */
    UCHAR ucDiscrAddr[MP_DISCRIMINATOR_MAX_LENGTH]; /* 终端描述符 */
    ULONG ulBindType;                       /* MP捆绑类型 */
} MP_DISCR_INFO_S;

/* 指定绑定VT的接口索引信息结构 */
typedef struct tagMP_IFINDEX
{
    DLL_NODE_S  stDLLNode;  /* 双链表节点 */
    ULONG       ulIfIndex;
}MP_IFINDEX_S;

/* MP子链路链表结构 */
typedef struct tagMP_SUBLINKS
{
    DLL_NODE_S  stDLLNode;  /* 双链表节点 */
    ULONG       ulIfIndex;
    CHAR        ucIfName[IF_MAX_INTERFACE_NAME_LEN + 1]; /* 原48用宏定义替换 */
}MP_SUBLINKS_S;

/* 重组缓冲区节点结构 */
typedef struct tagMP_FRAGMENT
{
    MBUF_S  *pstMbuf;       /* 本段对应MBUF指针 */
    ULONG   ulSeqNumber;    /* 报文序列号 */
    UCHAR   ucBEFlag;       /* (B)eginning、(E)nding比特标志 */
    UCHAR   ucPadding[3]; 
} MP_FRAGMENT_S;

/* MP子通道控制块索引结构 */
typedef struct tagMP_SON_INDEX
{
    struct tagMP_SON_INDEX *pstNext;    /* 下一子通道控制块指针 */
    struct tagMP_SON_INDEX *pstPrev;    /* 上一子通道控制块指针 */
    ULONG ulFatherChannelIfIndex;       /* 父通道IFNET索引 */
    ULONG ulSonChannelIfIndex;          /* 子通道IFNET索引 */
    ULONG ulChannelBandWith;            /* 子通道带宽 */
} MP_SON_INDEX_S;

/* 用于HUAWEI-MP-MIB访问的MP信息结构; "+ 4:存放结尾符和4字节对齐" */
typedef struct tagMPMULTILINKINFO
{
    /* 绑定名称; 如果是Mp-group接口，统一为"Multilink" */
    UCHAR ucHwMpBundleName[MP_USERNAME_LEN + 4];
    ULONG ulHwMpBundledSlot;        /* 父通道所在的槽号 */
    ULONG ulHwMpBundledMemberCnt;   /* 对VT:是绑定成功的子通道的个数 */
                                    /* 对Mp-group:是有绑定关系的子通道个数 */
    
    /*以下四个参数为查询子通道信息表所用*/
    ULONG ulHwMpMemberlinkSeqNumber;/* 子通道在一个MP中的序号，从1开始编号 */
    ULONG ulHwMpMemberlinkIfIndex;  /* 子通道接口索引; 如果绑定的子通道为虚链路
                                       只能在接口板取得接口名，所以需要这个参数 */
    UCHAR ucHwMpMemberlinkDescr[MAX_INTERFACE_DESCRIPTION_LEN + 4]; /*子接口描述*/
    ULONG ulHwMpMemberlinkMpStatus; /* 子通道绑定成功与否的标志; 0:没有绑定；1:成功绑定*/
    
    ULONG ulBindType;               /* 绑定方式; 如果是Mp-group接口绑定，置为0 */
    UCHAR ucHwMpMultilinkDescr[MAX_INTERFACE_DESCRIPTION_LEN + 4];  /* 父接口描述 */
    ULONG ulHwMpLostFragments;      /* 接收方向丢弃的分片 */
    ULONG ulHwMpReorderedPkts;      /* 接收方向重组报文数 */
    ULONG ulHwMpUnassignedPkts;     /* 接收方向等待重组的分片数 */
    ULONG ulHwMpInterleavedPkts;    /* 发送方向LFI的分片个数 */
    ULONG ulHwMpRcvdSequence;       /* 接收序列号 */
    ULONG ulHwMpSentSequence;       /* 发送序列号 */
    
}MP_MULTILINK_INFO_S;

/* MP父通道控制块结构 */
/* 发送/接收/重组序列号扩充成数组，段重组缓冲区起始指针扩充成数组，
 * 增加本端和对端是否接收MC报文，class等级数字段  */
/* z36377调整字段位置以满足ARM字节对齐要求,A82D21957,2007/12/17 */
typedef struct tagMP_FATHER
{
    ULONG ulOutSeqNumber[MC_MAX_LSCLASS];   /* 当前发送序列号 */
    ULONG ulInSeqNumber[MC_MAX_LSCLASS];    /* 当前接收序列号 */
    ULONG ulVTIfIndex;          /* 虚模板IFNET索引 */
    ULONG ulFatherIndexAddr;    /* 父通道索引地址 */
    ULONG ulFragmentBufLen;     /* 段重组缓冲区长度 */
    ULONG ulLostFragments;      /* 丢弃的段数 */
    ULONG ulReordered;          /* 重组的报文数 */
    ULONG ulUnassigned;         /* 等待重组的段数 */

    ULONG ulInterleaved;        /* 链路层分段插入的报文数 */

    ULONG ulFibIndex;           /* 增加VLINK时的邻接表索引 */
    MP_FRAGMENT_S *pstMpFrags[MC_MAX_LSCLASS];  /* 段重组缓冲区起始指针 */

    ULONG ulSeqReordered[MC_MAX_LSCLASS];       /* 已重组报文序号 */

    MP_SON_INDEX_S *pstCurrentSonChannel;   /* 当前可以发送报文的子通道 */
    MP_SON_INDEX_S *pstFirstSonChannel;     /* 用于MP的show命令标记头一个子通道 */
    USHORT usMaxMpBindNum;      /* 最大绑定链路数 */
    USHORT usMpBindNum;         /* 已绑定的链路数 */

    USHORT usMinFragLen;        /* MP开始分段的最小包长 */
    UCHAR  bPppReorderWindow;   /* MP重组是否使用重组功能，0:不使用，1:使用 */
    UCHAR  bPppInterleave;      /* LFI使能与否标记 */
    USHORT usMaxFragLFI;        /* LFI最大分片长度值 */
    UCHAR bSheRcvShortHdr ;     /* 对端接收短地址 */
    UCHAR bWeRcvShortHdr ;      /* 本端接收短地址 */

    UCHAR bSheMultiClass;       /* 对端接收MC报文*/
    UCHAR ucSheClassNum;        /* 对端支持接收的mc等级数*/
    UCHAR bWeMultiClass;        /* 本端接收MC报文*/
    UCHAR ucWeClassNum;         /* 本端支持接收的mc等级数*/

    USHORT usUpSublinkLowLimit; /* mp接口成员端口UP数达到该值进行网络层协商 */ 
    UCHAR ucPadding[2];

    /* Added by z43740 for A82D20089: 增加重组方式统计,2007-09-13 */
    ULONG ulWindowMatch;        /* 匹配重组窗口的报文个数 */
    ULONG ulWindowIn;           /* 落在重组窗口内报文个数 */
    ULONG ulWindowBehind;       /* 落后重组窗口的报文个数 */
    ULONG ulWindowSurpass;      /* 超过重组窗口的报文个数 */
    /* End of addition */
} MP_FATHER_S;

/* MP父通道索引链表结构 */
typedef struct tagMP_FATHER_INDEX
{
    DLL_NODE_S stDLLNode;           /* 双链表节点 */
    DLL_S *pstFatherIndexList;      /* 双链表头节点指针 */
    ULONG ulFatherChannelIfIndex;   /* 父通道IFNET索引 */
    ULONG ulWaitBindTimerId;        /* 等待绑定响应定时器 */
    MP_DISCR_INFO_S stDiscrInfo;    /* 终端描述信息 */
    ULONG ulBindType;               /* 绑定方式 */
} MP_FATHER_INDEX_S;



/* MP模块信息结构，由SHELL注册时填入 */
 typedef struct tagMP_ModInfo
{
    ULONG ulMID_MP;
    ULONG ulQUE_PPP_ASY;
    ULONG ulQUE_PPP_NEGO;
    ULONG ulQUE_PPP_MP;
    ULONG ulQUE_PPP_STAC;
    ULONG ulQUE_IP_INPUT;
    ULONG ulQUE_MPLS_INPUT;
    ULONG ulQUE_ISIS_INPUT;
    ULONG ulQUE_IPX_INPUT;
    ULONG ulQUE_PPPMUX_INPUT;
    ULONG ulQUE_IPV6_INPUT;
    ULONG ulWaitList;
}MP_MOD_INFO_S;

/* MP SHELL向CORE注册的回调函数集合 */
typedef struct tagMP_SHELL_CALLBACK
{
    VOID(*pfDebugOutString)(CHAR *szString, ULONG ulBufLenth);
    
    ULONG(*pfMPQOS_MpGroupQueInit)(ULONG ulIfIndex, BOOL_T bLfiConfigFlag, 
                                   UCHAR ucMC, UCHAR ucClassNum);
    ULONG(*pfMPQOS_CloneTemplateQue)(ULONG ulFatherIndex, ULONG ulTemplateIfIndex, 
                                     UCHAR ucMC,UCHAR ucClassNum);
    VOID(*pfMPQOS_DelFatherFromQos)(ULONG ulFatherIndex);
    VOID(*pfMPQOS_QosChange)( ULONG ulFatherIndex, ULONG *pulLfiConfigFlag);
    ULONG(*pfMPQOS_QM_TransmitDone)(ULONG ulIfIndex, UINTPTR ulPointerToDcb, MBUF_S *pstMBuf);
    ULONG(*pfQOS_QM_TransmitDone)(ULONG ulIfIndex, UINTPTR ulPointerToDcb, MBUF_S *pstMBuf);
    BOOL_T(*pfQOS_IfCanSendPkt)(ULONG ulIfIndex);
    ULONG(*pfMPQOS_QM_Transmit)(ULONG ulIfIndex, MBUF_S *pstMBuf, USHORT usProtocol);

    ULONG(*pfDDR_GetFatherIfIndex)(IFNET_S*pstSonIf);
    ULONG(*pfDDR_IoCtl)(IFNET_S*pstIfnet,ULONG ulCommand, CHAR *pszPara);
    VOID(*pfDDR_ResetIdleTimeout)(IFNET_S *pstIf);
    
    ULONG(*pfPPP_BAK_RealTime_Send)(VOID *pstInfo, ULONG ulParaType, ULONG ulOpType);
    
    ULONG(*pfMP_EnDropQue)(MBUF_S *pMBuf);
    ULONG(*pfMP_EnQueue)(MBUF_S *pMBuf);
}MP_SHELL_CALLBACK_S;

/* disp mp(show)处理的数据结构定义 */
/* 发送/接收序列号扩充成数组*/
typedef struct tagMpDispInfo
{
    ULONG ulFatherIfIndex;      /* 父通道索引 */
    
    /* 父通道名字，该项主要是为了解决主控板上不能根据VA索引获取VA名字的问题 */
    UCHAR ucFatherName[IF_MAX_INTERFACE_NAME_LEN + 1];
    ULONG ulSubLink[MP_SUPPORT_MAX_BIND];       /* 子链路索引数组 */
    UCHAR ucSubLinkStatus[MP_SUPPORT_MAX_BIND]; /* 子接口链路层状态，在MP-group模式下有效 */

    /* 在MP-group模式下，ulSubLinkNum是配置的子链路数，等于ulSubLink数组的项数; 
       在VT模式下，ulSubLinkNum等于下面定义的ulMpBindNum */
    ULONG ulSubLinkNum;         /* 子链路数 */    
    ULONG ulFatherSlot;         /* 父通道所在槽号 */
    ULONG ulMpBindNum;          /* 捆绑链路数, 即已生效的子链路数 */

    /* 以下4项信息，VT模式下有效，MP-group下请不要使用； */
    UCHAR ucUserName[MP_USERNAME_LEN + 2];      /* 用户名; "+ 2:存放结尾符和4字节对齐" */
    UCHAR ucDiscrLen;                           /* 终端描述符长度 */
    UCHAR ucDiscrClass;                         /* 终端描述符类型 */
    UCHAR ucDiscrAddr[MP_DISCRIMINATOR_MAX_LENGTH]; /* 终端描述符 */

    ULONG ulBindType;           /* 绑定类型 */

    ULONG ulLostFragments;      /* 接收方向丢弃的分片数 */
    ULONG ulReorderedPkts;      /* 接收方向重组的报文数 */
    ULONG ulUnassignedPkts;     /* 接收方向等待重组的分片数 */
    ULONG ulInterleavedPkts;    /* 发送方向LFI的分片个数 */
    ULONG ulInSeqNum[MC_MAX_LSCLASS];           /* 入报文序列号 */
    ULONG ulOutSeqNum[MC_MAX_LSCLASS];          /* 出报文序列号 */

    /* Added by z43740 for A82D20089: 增加重组方式统计,2007-09-13 */
    ULONG ulWindowMatchPkts;        /* 匹配重组窗口报文个数 */
    ULONG ulWindowInPkts;           /* 落在重组窗口中报文个数 */
    ULONG ulWindowBehindPkts;       /* 落后重组窗口报文个数 */
    ULONG ulWindowSurpassPkts;      /* 超过重组窗口报文个数 */
    /* End of addition */
}MP_DISP_INFO_S;

typedef struct tagMpSubIndexInfo
{
    ULONG ulSubLink[MP_SUPPORT_MAX_BIND]; /* 子接口链路的接口索引*/
    ULONG ulSubLinkNum;                   /* 子链路索引数组 */
}MP_SUB_INDEX_S;

/* MP GROUP子通道接口指针的链表结构 */
typedef struct tag_Mtl_link
{
    UINTPTR ulIfPointer;
    struct tag_Mtl_link * pNext;
}MTL_LINK_S;

/* MP GROUP底层使用的控制块结构 */
typedef struct tag_Mtl_Message
{
    COMMON_MSG;
    MTL_LINK_S st_mul_link;
}MLT_MESSAGE_S;


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MP_TYPE_H_ */
