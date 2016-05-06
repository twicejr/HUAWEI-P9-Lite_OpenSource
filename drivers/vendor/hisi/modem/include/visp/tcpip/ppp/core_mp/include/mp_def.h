/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                                mp_def.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2000-03-27
 *        Author: HouZhipeng
 *   Description: MP模块的宏定义声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000-03-27      HouZhipeng      Create
 *  2005-09-15      YaoChengliang   Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *  2006-05-12      languanghua     支持ARM CPU 四字节对齐
 *************************************************************************/

#ifndef _MP_DEF_H_
#define _MP_DEF_H_

#ifdef  __cplusplus
extern "C"{
#endif


/* 系统支持的MP默认绑定数16, 最小绑定数1，最大绑定数128 */
#define MP_DEFAULT_MAX_BIND         16
#define MP_SUPPORT_MIN_BIND         1
#define MP_SUPPORT_MAX_BIND         128


/* MBUF透传绑定消息类型 */
#define MP_INPUT_PACKET             0
#define MP_TR_MP_PACKET             1
#define MP_TR_IP_PACKET             2


/* 消息类型定义---最小分片长度设置消息; 发送即时生效消息给父通道 */
#define MP_MSG_FRAGMENT_LEN         1

/* 最大分段数 */
#define MP_MAX_FRAGMENT_NUM         16
/* MP最小分片长度的缺省值500，最小值128，最大值1500 */
#define MP_MIN_FRAGMENT_LEN         500 
#define MP_MIN_FRAGMENT_LEN_MIN     128
#define MP_MIN_FRAGMENT_LEN_MAX     1500

/* 每个子通道对应的段重组缓冲区长度 */
#define MP_FRAGMENTNUM_PER_CHANNEL  16
/* 最大段重组缓冲区长度 */
#define MP_MAX_FRAGMENT_BUF_LEN     512


/* LFI使能/去使能宏定义 */
#define MP_LFI_ENABLE                   1
#define MP_LFI_DISABLE                  0

/* LFI分片时延:缺省值10毫秒，最小值1毫秒，最大值1000毫秒 */
#define MP_LFI_DEFAULT_FRAGMENT_DELAY   10
#define MP_LFI_MIN_FRAGMENT_DELAY       1
#define MP_LFI_MAX_FRAGMENT_DELAY       1000

/* LFI功能生效要求的线路带宽小于阈值: 12000Kbps = 12Mbps */
#define MP_LFI_BANDWIDTH_THRESHOLD      12000

/* LFI最大分片长度的最小值80，最大值1500 */
#define MP_LFI_MIN_FRAGMENT_LENGTH      80
#define MP_LFI_MAX_FRAGMENT_LENGTH      1500


/* MP重组窗口使能/去使能宏定义 */
#define MP_REORDER_WINDOW_ENABLE        1
#define MP_REORDER_WINDOW_DISABLE       0

/* 终端描述符使能/去使能宏定义 */
#define MP_DISCRIMINATOR_ENABLE         1
#define MP_DISCRIMINATOR_DISABLE        0
/* 终端描述符最大长度值 */
#define MP_DISCRIMINATOR_MAX_LENGTH     20


/* MP报文头部字段值宏定义 */
#define MP_UCHAR_M      0x00
#define MP_UCHAR_E      0x40
#define MP_UCHAR_B      0x80
#define MP_UCHAR_BE     0xC0

/* MP用来辨别IP报文分片与否以及分片偏移量的宏定义 */
#define MP_IP_DF        0x4000  /* dont fragment flag */
#define MP_IP_MF        0x2000  /* more fragments flag */
#define MP_IP_OFFMASK   0x1fff  /* mask for fragmenting bits */

/* MP报文头部长度宏定义 */

/* Modified by z43740: 加入PFC/ACFC后，最小长度为1, 2006/05/12 */
#define MP_MIN_LEN      1       /* 最小MP报文长度 */
#define MP_SHDRLEN      2       /* 短序列号MP头长度 */
#define MP_LHDRLEN      4       /* 长序列号MP头长度 */
#define MP_PPP_HDRLEN   4       /* PPP报文头长度 */

/* Added by z43740 for A82D20089: MP重组窗口扩大系数，2007-09-13 */
#define MP_REORDERWIN_TIMES_MIN   1
#define MP_REORDERWIN_TIMES_DEF   2
#define MP_REORDERWIN_TIMES_MAX   4
/* End of addition */

/* Modified by likaikun213099, 迭代4检视意见修改, 2014/12/22   问题单号:DTS2014121903356 */
#define MP_MASK_BIT0    0x0001
#define MP_MASK_BIT16   0x0100
/*End of Modified by likaikun213099, 2014/12/22   问题单号:DTS2014121903356 */

/* MP调试输出信息数组下标的枚举定义 */
enum
{
    /*报文方向*/
    MP_IN = 0,              /* 0 IN */
    MP_OUT,                 /* 1 OUT */
    /*MP事件*/
    MP_DEL_FATHER_CHANNEL,  /* 2 Deleted a mp bundle */
    MP_ADD_FATHER_CHANNEL,  /* 3 Created a mp bundle */
    MP_DEL_SON_CHANNEL,     /* 4 Removed a mp link */
    MP_ADD_SON_CHANNEL      /* 5 Appended a mp link */
};


#define MP_GET_CHAR(c, cp) { \
    (c) = *( (UCHAR *)(cp) ); \
    (cp) += 1 ; \
}

#define MP_PUT_CHAR(c, cp) { \
    *( (UCHAR *)(cp) ) = (c) ; \
    (cp) += 1 ; \
}

#define MP_GET_SHORT(s, cp) { \
    VOS_CopyVar((s), *((USHORT *)(cp))); \
    (cp) += 2 ; \
}

#define MP_PUT_SHORT(s, cp) { \
    VOS_CopyVar(*((USHORT*)(cp)),(s)) ; \
    (cp) += 2 ; \
}

#define MP_GET_LONG(l, cp) { \
    VOS_CopyVar((l) , *((ULONG *)(cp))); \
    (cp) += 4 ; \
}

#define MP_PUT_LONG(l, cp) { \
    VOS_CopyVar(*((ULONG*)(cp)),(l)) ; \
    (cp) += 4 ; \
}

#define MP_PPP_MAKEHEADER(p, t) \
{ \
    USHORT usPro = t; \
    MP_PUT_CHAR(0xff, p); \
    MP_PUT_CHAR(0x03, p); \
    usPro = VOS_HTONS(usPro); \
    MP_PUT_SHORT(usPro, p); \
}

/* Modified by z43740 for MC:增加参数ucClass, 2006/05/11 */
#define MP_MAKEHEADER( pstMpInfo, pucData, ucFlag, ucClass )\
{ \
    if( 1 == pstMpInfo->bSheRcvShortHdr )\
    {\
        USHORT usHeader;\
        ucFlag = (ucFlag | (ucClass << 4));\
        usHeader = (USHORT)(((USHORT)ucFlag << 8) | pstMpInfo->ulOutSeqNumber[ucClass]);\
\
        usHeader = (USHORT)VOS_HTONS(usHeader);\
        MP_PUT_SHORT(usHeader ,pucData);\
        pstMpInfo->ulOutSeqNumber[ucClass]++;\
        pstMpInfo->ulOutSeqNumber[ucClass] &= 0xfff;\
    } \
    else\
    {\
        ULONG ulHeader;\
        ucFlag = (ucFlag | (ucClass << 2));\
        ulHeader =  ((ULONG)ucFlag << 24) | pstMpInfo->ulOutSeqNumber[ucClass];\
        ulHeader = VOS_HTONL(ulHeader);\
        MP_PUT_LONG(ulHeader, pucData);\
        pstMpInfo->ulOutSeqNumber[ucClass]++;\
        pstMpInfo->ulOutSeqNumber[ucClass] &= 0xffffff;\
    } \
}


/* 计算报文包含的段数 */
#define MP_COUNTFRAGNUM( ulFragNum, ulBeginPos, ulEndPos, ulFragmentBufLen ) \
{\
    if( ulEndPos >= ulBeginPos )\
    {\
        ulFragNum = ulEndPos - ulBeginPos + 1;\
    }\
    else\
    {\
        ulFragNum = ulFragmentBufLen - (ulBeginPos - ulEndPos -1);\
    }\
}

/* add by L00105073 for BC3D01550,比较非首次加入MP接口的子通道参数是否与mp一致 */
#define MP_SON_CHECKOPTION(pstFatherLcpOption, pstSonLcpOption, ulCheckFailCode, ulWarningId)\
do\
{\
    /* 比较PFC */\
    if ((pstFatherLcpOption)->neg_pcompression != (pstSonLcpOption)->neg_pcompression)\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* 比较ACFC */\
    if ((pstFatherLcpOption)->neg_accompression != (pstSonLcpOption)->neg_accompression)\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* 比较MHF */\
    if (((pstFatherLcpOption)->ucMhfCode != (pstSonLcpOption)->ucMhfCode)\
        || ((pstFatherLcpOption)->ucMhfClass != (pstSonLcpOption)->ucMhfClass))\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* 比较SSNHF */\
    if ((pstFatherLcpOption)->neg_ssnhf != (pstSonLcpOption)->neg_ssnhf)\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* 比较mrru/mru */\
    if (((pstFatherLcpOption)->mrru != (pstSonLcpOption)->mrru)\
        || ((pstFatherLcpOption)->mru != (pstSonLcpOption)->mru))\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* 前缀省略表比较:1,协商能力不一致不允许加入 */\
    if ((pstFatherLcpOption)->neg_prefixE ^ (pstSonLcpOption)->neg_prefixE)\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* 前缀省略表比较:2,父子通道都有前缀省略表但是不一致则不允许加入 */\
    if ((pstFatherLcpOption)->neg_prefixE  && (pstSonLcpOption)->neg_prefixE)\
    {\
        LONG lCmpRet = 0;\
        if ((NULL == (pstFatherLcpOption)->pstPrefixE) || (NULL == (pstSonLcpOption)->pstPrefixE)) \
        {\
            ulCheckFailCode = PPP_MP_CFG_DIFF;\
            ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
            break;\
        }\
        (VOID)VOS_Mem_Cmp((VOID*)((pstFatherLcpOption)->pstPrefixE), (VOID*)((pstSonLcpOption)->pstPrefixE),\
                           sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM, &lCmpRet);\
        if (lCmpRet)\
        { \
            ulCheckFailCode = PPP_MP_CFG_DIFF;\
            ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
            break;\
        }\
    }\
    ulCheckFailCode = 0; /* check ok */ \
}while(0)

/* MP子链路状态的宏定义 */
#define MP_IF_STATUS_PROT_DOWN  0x1       /*子连路物理层DOWN*/
#define MP_IF_STATUS_LOW_DOWN   0x2       /*子连路物理层UP，协议层DOWN*/
#define MP_IF_STATUS_PROT_UP    0x3       /*子连路协议层UP，但还绑定到父通道未生效*/
#define MP_IF_STATUS_BIND_UP    0x4       /*子连路协议层UP且绑定到父通道已生效*/
#define MP_IF_STATUS_INVALID    0xFF

/* MP父通道存在子通道与否的宏定义 */
#define MP_EXISTSON             0x1
#define MP_NOT_EXISTSON         0x0

/* MP MIB信息获取的宏定义 */
#define MP_MIB_MULTILINKTABLE_INFO  1   /*获取父通道信息表*/
#define MP_MIB_MEMBERLINKTABLE_INFO 2   /*获取子通道信息表*/

/* MP NCP协商UP以后，通过IFNET通知PPPoE Client或者DDR对应接口UP的宏定义 */
#define MP_PPP_NEG_UP               1
#define MP_PPP_NEG_DOWN             0

/* NE5000产品注册标记宏定义 */
#define MP_PRODUCT_NE5000_REG       0x01

/* MP WAITLIST对应表项的宏定义 */
#define MP_WAITLIST_GET_USERINFO    0x01

/* MP SID宏定义 */
#define MP_SID_MP                   0x01
#define MP_SID_CACHE                0x02

/* 无效的MP通道号 */
#define MP_INVALID_CHAN_NUM         0xFFFFFFFF

/* MP SHELL注册的模块信息宏定义 */
#define MP_MID_MP               g_stMPModInfo.ulMID_MP
#define MP_QUE_IP_INPUT         g_stMPModInfo.ulQUE_IP_INPUT
#define MP_QUE_IP6_INPUT        g_stMPModInfo.ulQUE_IPV6_INPUT 

#define MP_QUE_IPX_INPUT        g_stMPModInfo.ulQUE_IPX_INPUT
#define MP_QUE_ISIS_INPUT       g_stMPModInfo.ulQUE_ISIS_INPUT
#define MP_QUE_MPLS_INPUT       g_stMPModInfo.ulQUE_MPLS_INPUT
#define MP_QUE_PPP_ASY          g_stMPModInfo.ulQUE_PPP_ASY
#define MP_QUE_PPP_MP           g_stMPModInfo.ulQUE_PPP_MP
#define MP_QUE_PPP_NEGO         g_stMPModInfo.ulQUE_PPP_NEGO
#define MP_QUE_PPP_STAC         g_stMPModInfo.ulQUE_PPP_STAC
#define MP_QUE_PPPMUX_INPUT     g_stMPModInfo.ulQUE_PPPMUX_INPUT
/* End of addition */
#define MP_WAITLIST_MAIN_TYPE   g_stMPModInfo.ulWaitList 

/* MP SHELL注册的API接口函数宏定义 */
#define MP_GetDialerFatherIfIndex   g_stMPShellApi.pfDDR_GetFatherIfIndex
#define MP_DialerIoCtl              g_stMPShellApi.pfDDR_IoCtl
#define MP_ResetDialerIdleTimeout   g_stMPShellApi.pfDDR_ResetIdleTimeout
#define MP_DebugOutString           g_stMPShellApi.pfDebugOutString
#define MP_CloneTemplateQue         g_stMPShellApi.pfMPQOS_CloneTemplateQue
#define MP_DelFatherFromQos         g_stMPShellApi.pfMPQOS_DelFatherFromQos
#define MP_MpGroupQueInit           g_stMPShellApi.pfMPQOS_MpGroupQueInit
#define MP_QosChange                g_stMPShellApi.pfMPQOS_QosChange
#define MP_EnDropQue                g_stMPShellApi.pfMP_EnDropQue
#define MP_EnQueue                  g_stMPShellApi.pfMP_EnQueue
#define MP_PPP_BAK_RealTime_Send    g_stMPShellApi.pfPPP_BAK_RealTime_Send
#define MP_QOS_IfCanSendPkt         g_stMPShellApi.pfQOS_IfCanSendPkt
#define MP_MPQOS_Transmit           g_stMPShellApi.pfMPQOS_QM_Transmit

#define MP_MPQOSTransmitDone        g_stMPShellApi.pfMPQOS_QM_TransmitDone
#define MP_QOSTransmitDone          g_stMPShellApi.pfQOS_QM_TransmitDone


extern DLL_S * MP_GetMpgroupList();


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MP_DEF_H_ */
