/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_def.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG模块宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_DEF_H
#define _1AG_DEF_H

#ifdef  __cplusplus
    extern "C"{
#endif

/* 1AG协议类型*/
#define OAM_1AG_ETHERTYPE 0x8902

/*VLAN 类型 0x8100*/
#define OAM_1AG_VLANTYPE 0x8100
#define DOT1Q_TAG_SIZE   4

/* 接收报文解析时用于标识报文中没有带VLAN头 */
#define OAM_1AG_NOVLAN_FLAG  0xFFFF

/* 带VLAN的以太头长度 */
#define OAM_1AG_ETHHEAD_LEN sizeof(OAM1AG_ETHERHDR_S)

/* 不带VLAN的以太头长度 */
#define OAM_1AG_NOVLAN_ETHHEAD_LEN sizeof(OAM1AG_NOVLAN_ETHERHDR_S)

/* 不带VLAN头的SNAP报文转换为以太报文时SNAP头的偏移量 */
#define OAM_1AG_CUTSNAP_NOVLAN_OFFSET 12
/* 带VLAN头的SNAP报文转换为以太报文时SNAP头的偏移量 */
#define OAM_1AG_CUTSNAP_OFFSET 16
/* SNAP报文转换为以太报文时应去掉的SNAP头长度 */
#define OAM_1AG_CUTSNAP_LENGTH 8

/* 收到一个不带VLAN的LB和LT报文时,入接口存在多个不带VLAN的MEP信息时,回调通知信息的最大个数 */
#define OAM_1AG_MAX_NOVLANINFONUM  8


/*MD + MA最大名字长度*/
#define OAM_1AG_MAX_MDMANAME_LEN 44
/*CCM报文MD和MA信息长度*/
#define OAM_1AG_MAX_MDMAINFO_LEN 48

/* 最大MD级别 */
#define OAM_1AG_MAX_MDLEVEL 7

/*最大MD数*/
#define OAM_1AG_MAX_MDNUM 8
/*最大MA数*/
/* Modified by z00208058/w00207740, 1AG规格扩展, 2012/5/4 */
#define OAM_1AG_MAX_MANUM 3000
/*最大MEP数*/
#define OAM_1AG_MAX_MEPNUM 3000
/*最大RMEP数*/
#define OAM_1AG_MAX_RMEPNUM 3000
/*MEPID最小值*/
#define OAM_1AG_MIN_MEPID 1
/*mepid最大值*/
#define OAM_1AG_MAX_MEPID 8191

/* 最小的VLAN ID */
#define OAM_1AG_MIN_VLANID 1
/* 最大的VLAN ID */
#define OAM_1AG_MAX_VLANID 4094

/* 报文最小优先级 */
#define OAM_1AG_MIN_PRIORITY 0
/* 报文最大优先级 */
#define OAM_1AG_MAX_PRIORITY 7
/* 基于MA的VLAN优先级初始值, 1AG Ping使用协议栈默认规则填写VLAN优先级的标志 */
#define OAM_1AG_INIT_PRIORITY  0xFF


/*LBR队列最大缓存节点数*/
#define OAM_1AG_MAX_LBRNODE 128
/*清除LBR缓存队列时间间隔*/
#define OAM_1AG_CLRQUE_INTERVAL 60000
/*LBR节点超时时间*/
#define OAM_1AG_LBR_MAXTIMEOUT 60000
/*最大普通PING用户数*/
#define OAM_1AG_MAX_LBUSER 16
/*默认LB报文发送次数*/
#define OAM_1AG_LBM_DEFAULT_COUNT 5
/*默认LB报文长度*/
#define OAM_1AG_LB_DEFAULT_LEN 128
/*最大LB报文长度*/
#define OAM_1AG_LBM_MAX_LEN 1500
/*最小报文长度*/
#define OAM_1AG_LBM_MIN_LEN 95

/*定义MEP发送CCM超时时间*/
#define OAM_1AG_MEPTIME  20
/*定义RMEP检测超时时间*/
#define OAM_1AG_RMEPTIME 50
/*定义LTR检测超时时间*/
#define OAM_1AG_LTRTIMER  1000

/*定义AIS检测超时时间*/
#define OAM_1AG_AISTIMER  500

/*默认超时时间*/
#define OAM_1AG_LB_DEFAULT_TIMEOUT 2
/*最小超时时间*/
#define OAM_1AG_LB_MIN_TIMEOUT 1
/*最大超时时间*/
#define OAM_1AG_LB_MAX_TIMEOUT 65535
/*LB测试发送报文最大间隔时间*/
#define OAM_1AG_LB_MAX_INTERVAL 60
/*用户自定义测试最小用户缓冲区长度*/
#define OAM_1AG_LB_MIN_USERBUFFLEN 40
/*用户自定义测试最大用户缓冲区长度*/
#define OAM_1AG_LB_MAX_USERBUFFLEN 1460
/* 数通偏移 */
#define   OAM_1AG_VRPLB_FIRSTTLVOFFSET  10
/* 标准偏移 */
#define   OAM_1AG_STDLB_FIRSTTLVOFFSET      4
/* 数通lb报文tlv类型和草案7报文tlv类型相同 */
#define OAM_1AG_LB_DATATYPE    4
#define OAM_1AG_LB_STDDATALEN    8
#define OAM_1AG_LB_VRPDATALEN   sizeof(OAM_1AG_VRPDATATLV_VALUE_S)

/* 最小LB报文长度 ,以太头+LB必须的8个字段+end tlv*/
#define  OAM_1AG_LB_MIN_LEN    (OAM_1AG_ETHHEAD_LEN+8+1)
/* LBM报文中DATA TLV长度字段及之前的1AG报文长度(不包括以太头) */
#define  OAM_1AG_FIXED_LBM_LEN  11

/*可以同时发起的LT任务数*/
#define OAM_1AG_MAX_LTMSEND 16
/* LT的最小超时秒数 */
#define OAM_1AG_MIN_LT_TIMEOUT 1
/* LT的最大超时秒数 */
#define OAM_1AG_MAX_LT_TIMEOUT 60

/* 组装LTM和LTR时填在first tlv offset字段的值，目的是与数通的实现一致,同时不违反标准协议,
    如此构造的LTM报文可以同时兼容两种模式,给后续的编码带来便利 */
#define OAM_1AG_LT_FIRST_TLV_OFFSET 28
/* 标准LTM报文的first tlv offset 值 */
#define OAM_1AG_LTM_DRAFT7_FIRST_TLV_OFFSET 25
/* 1AG-CFM-2007标准LTM报文的first tlv offset 值 */
#define OAM_1AG_LTM_STD_FIRST_TLV_OFFSET 17
/* 标准LTR报文的first tlv offset 值 */
#define OAM_1AG_LTR_DRAFT7_FIRST_TLV_OFFSET 22
/* 1AG-CFM-2007标准LTR报文的first tlv offset 值 */
#define OAM_1AG_LTR_STD_FIRST_TLV_OFFSET 6

/* 长度为1AG报文头到FirstTlvOffset字段的长度,不包括1字节的FirstTlvOffset字段 */
#define OAM_1AG_LTR_STD_COMMON_OFFSET 3
#define OAM_1AG_LTM_STD_COMMON_OFFSET 3


/* TLV长度,包括type.length.value长度 */
#define OAM_1AG_LTM_EGRESS_TLV_LEN  sizeof(OAM_1AG_LTM_EGRESS_TLV_S)
/* END TLV长度 */
#define OAM_1AG_END_TLV_LEN       1


/* LTR 中的 TLV 要用到的宏 */
#define REPLY_INGRESS_TLV_LENGTH 13
#define REPLY_EGRESS_TLV_LENGTH 13
#define INGRESS_PORT_ID_LENGTH 4    /* 应该为4，协议规定必须为lenth-9=portid_len  DTS2011083001954 */
#define INGRESS_PORT_ID_SUBTYPE 5
#define EGRESS_PORT_ID_LENGTH 4     /* 应该为4，协议规定必须为lenth-9=portid_len  DTS2011083001954 */
#define EGRESS_PORT_ID_SUBTYPE 5
#define REPLY_Y1731INGRESS_TLV_LENGTH 7
#define REPLY_Y1731EGRESS_TLV_LENGTH 7



/* 设备的出端口信息长度 */
#define OAM_1AG_EGRESSID_SIZE 8

/* 设备的入/出端口ID长度 */
#define OAM_1AG_PORTID_SIZE 4

/*表示RMEP是否下发过NP*/
#define OAM_1AG_NODOWNLOADNP 0   /* 表示此RMEP未下发过NP */
#define OAM_1AG_DOWNLOADNP   1   /* 表示此RMEP下发过NP */


/* 表示收到的CCM报文是否带有VLAN tag */
#define OAM_1AG_NOTVLAN_CCM   0   /* 非VLAN CCM报文 */
#define OAM_1AG_VLAN_CCM      1   /* VLAN CCM报文  */

/* 当删除MD时,会删除MD下的所有MA,MEP和RMEP,每次删除都发送备份消息是不必要的,因而此时不发备份消息;而单独的删除
MA,MEP,RMEP是则必须发送备份消息 */
/* 删除MA,MEP,RMEP时是否发送备份消息 */
#define OAM_1AG_BACKUP 1        /* 发送备份消息 */
#define OAM_1AG_NOBACKUP 0      /* 不发送备份消息 */

/*CCM报文字段偏移量*/
#define OAM_1AG_MDTYPE_OFFSET   0
#define OAM_1AG_MDLENGTH_OFFSET 1
#define OAM_1AG_MDNAME_OFFSET   2
#define OAM_1AG_MALENGTH_OFFSET 3
#define OAM_1AG_MANAME_OFFSET   4

/* Add for V2R3C06, by b0177000/z00187940, at 2011-09-29. 修改原因: V2R3C06 Y1731协议CCM报文MEGID格式 */
#define OAM_Y1731_MEGID_TYPE_ICC      32
#define OAM_Y1731_MEGID_LEN_ICC       13

#define OAM_Y1731_MEGTYPE_OFFSET 1
#define OAM_Y1731_MEGLENGTH_OFFSET   2
#define OAM_Y1731_MEGID_OFFSET 3


/*标准CCM报文偏移量*/
#define OAM_1AG_CCM_STDOFFSET    70
/*标准CCM报文填充长度*/
#define OAM_1AG_CCM_STDPAD_LEN   16
/*兼容数通CCM报文偏移量*/
#define OAM_1AG_CCM_VRPOFFSET    54

/* 定时器下标索引 */
#define OAM_1AG_100MSLISTINDEX 0
#define OAM_1AG_1SLISTINDEX    1
#define OAM_1AG_10SLISTINDEX   2

/* AIS 定时器下标索引 */
#define OAM_Y1731_AIS_1SLISTINDEX 0
#define OAM_Y1731_AIS_1MINLISTINDEX    1

/* Interface Status相关 */
#define OAM_1AG_INTERFACE_UP    1
#define OAM_1AG_INTERFACE_DOWN  2

/* 发送不带Interface Tlv的CCM */
#define OAM_1AG_NOTLVFLAG 0
/* 发送带Interface Tlv的CCM */
#define OAM_1AG_TLVFLAG   1
/* 发送不带任何Tlv的CCM */
#define OAM_1AG_NOTLVFLAG_Y1731 2

/*SID定义*/
#define SID_OAM_1AG_MD   1
#define SID_OAM_1AG_MA   2
#define SID_OAM_1AG_MEP  3
#define SID_OAM_1AG_RMEP 4
#define SID_OAM_1AG_DISP_MEP 5

/*1AG性能测试开始*/
#define OAM_1AG_CAPTEST_BEGIN 1
/*1AG性能测试结束*/
#define OAM_1AG_CAPTEST_END   2
/*VLAN ID的Hash值*/
#define OAM_1AG_VLANHASHVALUE 128


#define OAM_1AG_SET_VERSION_USER_INPUT 0
#define OAM_1AG_SET_VERSION_TRUNK_PORT 1

#define OAM_1AG_NOT_HANDLE      0xFFF /* 1ag 报文尚未处理，需要其它模块继续处理 */

typedef enum enOAM_1AG_PKT_DEBUG
{
    OAM_1AG_PKTIN = 1, /*接收到的报文*/
    OAM_1AG_PKTOUT,    /*发送的报文*/
    OAM_1AG_FORWARD,   /*转发的报文*/
    OAM_1AG_MAX_END
}OAM_1AG_PKT_DEBUG_E;

/*兼容标准模式*/
#define OAM_1AG_COMPATIBLE_STD    0
/*兼容数通模式*/
#define OAM_1AG_COMPATIBLE_VRP    1

/*OAM 1ag调试开关,对应位0-关闭,1-开启*/
#define OAM_1AG_DEBUGCCON   1
#define OAM_1AG_DEBUGLBON   2
#define OAM_1AG_DEBUGLTON   4
#define OAM_1AG_DEBUGAISON   8
/*判断CC是否开启*/
#define OAM_1AG_DEBUGCCISON(ulDebugSwitch) ((ulDebugSwitch) & OAM_1AG_DEBUGCCON)

/*判断LB是否开启*/
#define OAM_1AG_DEBUGLBISON(ulDebugSwitch) ((ulDebugSwitch) & OAM_1AG_DEBUGLBON)

/*判断LT是否开启*/
#define OAM_1AG_DEBUGLTISON(ulDebugSwitch) ((ulDebugSwitch) & OAM_1AG_DEBUGLTON)

/*判断AIS是否开启*/
#define OAM_1AG_DEBUGAISISON(ulDebugSwitch) ((ulDebugSwitch) & OAM_1AG_DEBUGAISON)

/* 如果组装CCM报文，ulValue填级别，如果组装LTM报文，ulValue填级别+8 */
#define OAM_1AG_DEST_ADDRESS(pdestmac, ucValue) \
{\
    (pdestmac[0]) = 0x01;\
    (pdestmac[1]) = 0x80;\
    (pdestmac[2]) = 0xC2;\
    (pdestmac[3]) = 0x00;\
    (pdestmac[4]) = 0x00;\
    (pdestmac[5]) = 0x30 | (ucValue);\
}

/* 根据版本号计算掩码 */
#define OAM_1AG_DESTMASK_ADDRESS(pdestmac_mask, ucversion) \
{\
    (pdestmac_mask[0]) = 0xff;\
    (pdestmac_mask[1]) = 0xff;\
    (pdestmac_mask[2]) = 0xff;\
    if (ucversion) /* draft8 */\
    {\
        (pdestmac_mask[3]) = 0xff;\
        (pdestmac_mask[4]) = 0xff;\
        (pdestmac_mask[5]) = 0xf0;\
    }\
    else /* draft7 */\
    {\
        (pdestmac_mask[3]) = 0x00;\
        (pdestmac_mask[4]) = 0x00;\
        (pdestmac_mask[5]) = 0x00;\
    }\
}

/* 根据是否有VLAN头标志获取以太头的长度 */
#define OAM_1AG_GET_ETHHEADER_LEN(ucVlanFlag, ulEthHeaderLen)\
{\
    if (OAM_1AG_SEND_WITH_VLAN == ucVlanFlag)\
    {\
        ulEthHeaderLen = OAM_1AG_ETHHEAD_LEN;\
    }\
    else\
    {\
        ulEthHeaderLen = OAM_1AG_NOVLAN_ETHHEAD_LEN;\
    }\
}

/* 根据是否有VLAN头标志获取以太头的长度 */
#define OAM_1AG_GET_ETHHEADER_LEN_WITH_VLANID(ucVlanId, ulEthHeaderLen)\
{\
    if (OAM_1AG_NOVLAN_FLAG == ucVlanId)\
    {\
        ulEthHeaderLen = OAM_1AG_NOVLAN_ETHHEAD_LEN;\
    }\
    else\
    {\
        ulEthHeaderLen = OAM_1AG_ETHHEAD_LEN;\
    }\
}


/* 如果该地址既不是全0地址,也不是全F地址,也不是多播地址(第一字节的最低位为1表示是多播地址),则该地址就是单播地址 */
/* physical地址第一字节的最低位为0并且该physical地址不是全0地址，则该physical地址就是单播地址 */
#define ISUNICASTMAC(aucMac)\
            ( (0 == (aucMac[0] & 1))\
              && ((0 != aucMac[0]) || (0 != aucMac[1]) || (0 != aucMac[2])\
                 || (0 != aucMac[3]) || (0 != aucMac[4])|| (0 !=  aucMac[5]) )\
            )

/* 用于计算hash值 */
#define OAM_1AG_HASH_CODE 16777619

#define GET_MDINFO_PTR(ulMdIndex)       ((OAM_1AG_MD_S*)g_pstMdChainTable[ulMdIndex].pstMdInfo)
#define GET_MAINFO_PTR(ulMaIndex)       ((OAM_1AG_MA_S*)g_pstMaChainTable[ulMaIndex].pstMaInfo)
#define GET_MEPINFO_PTR(ulMepIndex)     ((OAM_1AG_MEP_S*)g_pstMepChainTable[ulMepIndex].pstMepInfo)
#define GET_RMEPINFO_PTR(ulRmepIndex)   ((OAM_1AG_RMEP_S*)g_pstRmepChainTable[ulRmepIndex].pstRmepInfo)

/* 计算逝去的时间，考虑了时间反转问题 */
#define OAM_1AG_INVALID_ULONG 0xFFFFFFFF
#define ELAPSETIME(begintime, endtime, elapsetime)\
{\
    if (begintime > endtime) \
    {\
        elapsetime = endtime + (OAM_1AG_INVALID_ULONG - begintime) + 1;\
    }\
    else\
    {\
        elapsetime = endtime - begintime;\
    }\
}

/*增加NP处理的宏*/
#define OAM1AG_PPI_Update(ulIfIndex,ulOprType,pEoam1agMsg)\
{\
    if ((OAM_1AG_FULLNP == g_stOam1agModInfo.ulNpModel) || (OAM_1AG_HALFNP == g_stOam1agModInfo.ulNpModel))\
    {\
        if (g_pfTCPIP_PPI_1AG_Update)\
        {\
            ULONG ulResult = OAM1AG_OK;\
            /*记录时间点*/\
            MAKE_NP_STARTDOT(PPI_TYPE_OAM1AG, ulOprType);\
            ulResult = g_pfTCPIP_PPI_1AG_Update(ulIfIndex,ulOprType,pEoam1agMsg);\
            /*记录时间点*/\
            MAKE_NP_ENDDOT(PPI_TYPE_OAM1AG);\
            TCPIP_PPI_1AG_LogMsg(ulResult,ulIfIndex,ulOprType,(VOID*)pEoam1agMsg);\
        }\
    }\
}

/*增加获取MEP信息NP处理的宏*/
#define OAM1AG_PPI_GetMep(ulIfIndex,ulOprType,pEoam1agMsg,ulResult)\
{\
    if (g_pfTCPIP_PPI_1AG_Update)\
    {\
        /*记录时间点*/\
        MAKE_NP_STARTDOT(PPI_TYPE_OAM1AG, ulOprType);\
        ulResult = g_pfTCPIP_PPI_1AG_Update(ulIfIndex,ulOprType,pEoam1agMsg);\
        /*记录时间点*/\
        MAKE_NP_ENDDOT(PPI_TYPE_OAM1AG);\
        TCPIP_PPI_1AG_LogMsg(ulResult,ulIfIndex,ulOprType,(VOID*)pEoam1agMsg);\
    }\
}

/*组装1AG全局NP下发消息*/
#define PPI_1AG_COPYGLBINFO(pstPpi1agGlbInfo)\
{\
    (pstPpi1agGlbInfo)->usPktType = g_usOam1agPktType;\
    (pstPpi1agGlbInfo)->ucPktPriority = g_ucOam1agPktPri;\
    (pstPpi1agGlbInfo)->ulCompatibleSwitch = g_ulCompatibleSwitch;\
}

/*组装1AG MA下发消息*/
#define PPI_1AG_COPYMAINFO(pstPpi1agMaInfo,pstMaInfo)\
{\
    OAM_1AG_MD_S *pstMdInfoTemp = NULL;\
    \
    pstMdInfoTemp = (OAM_1AG_MD_S *)((g_pstMdChainTable[(pstMaInfo)->ulMdIndex]).pstMdInfo);\
    /*在调用宏前已经保证了pstMdInfoTemp非空*/\
    (VOID)TCPIP_Mem_Copy((VOID*)(pstPpi1agMaInfo)->szMdName,OAM_1AG_MAX_MDNAME_LEN+1,(VOID*)pstMdInfoTemp->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1);\
    (VOID)TCPIP_Mem_Copy((VOID*)(pstPpi1agMaInfo)->szMaName,OAM_1AG_MAX_MANAME_LEN+1,(VOID*)(pstMaInfo)->szMaName, OAM_1AG_MAX_MANAME_LEN + 1);\
    (pstPpi1agMaInfo)->ucCcmInterval = (pstMaInfo)->ucCcmInterval;\
    (pstPpi1agMaInfo)->ucCompatibleType = (pstMaInfo)->ucCompatibleFlag;\
    (pstPpi1agMaInfo)->usVlanId = (pstMaInfo)->usVlanId;\
    (pstPpi1agMaInfo)->ucMaPri  = (OAM_1AG_INIT_PRIORITY == (pstMaInfo)->ucMaVlanPri)?g_ucOam1agPktPri:(pstMaInfo)->ucMaVlanPri;\
    (pstPpi1agMaInfo)->ucRdiFlag = (pstMaInfo)->ucRdiFlag;\
    (pstPpi1agMaInfo)->ucMaNameType = (pstMaInfo)->ucMaNameType;\
}

/*组装1AG CCM下发信息*/
#define PPI_1AG_COPYCCMINFO(pstPpiCcmInfo,pstMepInfo)\
{\
    OAM_1AG_MA_S *pstTempMaInfo = NULL;\
    OAM_1AG_MD_S *pstMdInfo = NULL;\
    /*在调用宏前已经保证了pstMdInfo、pstMaInfo非空*/\
    pstTempMaInfo = (OAM_1AG_MA_S *)((g_pstMaChainTable[(pstMepInfo)->ulMaIndex]).pstMaInfo);\
    pstMdInfo = (OAM_1AG_MD_S *)((g_pstMdChainTable[pstTempMaInfo->ulMdIndex]).pstMdInfo);\
    (VOID)TCPIP_Mem_Copy((pstPpiCcmInfo)->szMdName,OAM_1AG_MAX_MDNAME_LEN+1,pstMdInfo->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1);\
    (VOID)TCPIP_Mem_Copy((pstPpiCcmInfo)->szMaName,OAM_1AG_MAX_MANAME_LEN+1,pstTempMaInfo->szMaName, OAM_1AG_MAX_MANAME_LEN + 1);\
    (pstPpiCcmInfo)->usMepId = (pstMepInfo)->usMepId;\
    (pstPpiCcmInfo)->usVId = pstTempMaInfo->usVlanId;\
    (pstPpiCcmInfo)->ucMdLevel = pstMdInfo->ucMdLevel;\
    (pstPpiCcmInfo)->ucCcmInterval = pstTempMaInfo->ucCcmInterval;\
    (pstPpiCcmInfo)->ucRdiFlag = pstTempMaInfo->ucRdiFlag;\
    (pstPpiCcmInfo)->ucMaPri = (OAM_1AG_INIT_PRIORITY == (pstTempMaInfo)->ucMaVlanPri)?g_ucOam1agPktPri:(pstTempMaInfo)->ucMaVlanPri;\
    (pstPpiCcmInfo)->ucCompatibleType = pstTempMaInfo->ucCompatibleFlag;\
    (pstPpiCcmInfo)->uc1agVersion = (pstMepInfo)->uc1agVersion;\
    (pstPpiCcmInfo)->ucVlanFlag = (pstMepInfo)->ucVlanFlag;\
    (pstPpiCcmInfo)->ucCcSendEnable = (pstMepInfo)->ucCcSendEnable;\
    (pstPpiCcmInfo)->ulIfIndex = (pstMepInfo)->ulIfIndex;\
    (pstPpiCcmInfo)->usLossDetectTimer = (pstMepInfo)->usLossDetectTimer;\
}

/* Add for V2R3C06, by z00171897/p00193127, at 2011-10-17. 修改原因: 支持Y1731使能/去使性能检测 */
/*组装Y1731 PM下发信息*/
#define PPI_Y1731_COPYPMINFO(pstPpiPMInfo,pstMepInfo)\
{\
    OAM_1AG_MA_S *pstTempMaInfo = NULL;\
    OAM_1AG_MD_S *pstMdInfo = NULL;\
    /*在调用宏前已经保证了pstMdInfo、pstMaInfo非空*/\
    pstTempMaInfo = (OAM_1AG_MA_S *)((g_pstMaChainTable[(pstMepInfo)->ulMaIndex]).pstMaInfo);\
    pstMdInfo = (OAM_1AG_MD_S *)((g_pstMdChainTable[pstTempMaInfo->ulMdIndex]).pstMdInfo);\
    (VOID)TCPIP_Mem_Copy((pstPpiPMInfo)->szMdName,OAM_1AG_MAX_MDNAME_LEN+1,pstMdInfo->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1);\
    (VOID)TCPIP_Mem_Copy((pstPpiPMInfo)->szMaName,OAM_1AG_MAX_MANAME_LEN+1,pstTempMaInfo->szMaName, OAM_1AG_MAX_MANAME_LEN + 1);\
    (pstPpiPMInfo)->usMepId = (pstMepInfo)->usMepId;\
}

/* 组装RMEP下发信息 */
#define PPI_1AG_COPYRMEPINFO(pstPpiRmepInfo, pstRmepInfo)\
{\
    OAM_1AG_MD_S *pstMd = NULL;\
    OAM_1AG_MA_S *pstMa = NULL;\
    /*在调用宏前已经保证了pstMdInfo、pstMaInfo非空*/\
    pstMa = (OAM_1AG_MA_S *)((g_pstMaChainTable[(pstRmepInfo)->ulMaIndex]).pstMaInfo);\
    pstMd = (OAM_1AG_MD_S *)((g_pstMdChainTable[pstMa->ulMdIndex]).pstMdInfo);\
    (pstPpiRmepInfo)->ulIfIndex = (pstRmepInfo)->ulIfIndex;\
    (pstPpiRmepInfo)->usVlanId = GET_MAINFO_PTR((pstRmepInfo)->ulMaIndex)->usVlanId;\
    (pstPpiRmepInfo)->usRmepId = (pstRmepInfo)->usRmepId;\
    (pstPpiRmepInfo)->ucInterval = (pstRmepInfo)->ucCcmInterval;\
    (pstPpiRmepInfo)->ucMdLevelFlag = (pstRmepInfo)->ucMdLevelFlag;\
    (VOID)TCPIP_Mem_Copy((pstPpiRmepInfo)->aucMacAddr,MACADDRLEN,(pstRmepInfo)->aucMacAddress,OAM_1AG_MACADDR_LEN);\
    (VOID)TCPIP_Mem_Copy((pstPpiRmepInfo)->aucMdName,OAM_1AG_MAX_MDNAME_LEN+1,pstMd->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1);\
    (VOID)TCPIP_Mem_Copy((pstPpiRmepInfo)->aucMaName,OAM_1AG_MAX_MANAME_LEN + 1,pstMa->szMaName, OAM_1AG_MAX_MANAME_LEN + 1);\
    (pstPpiRmepInfo)->ucRdiFlag = (pstRmepInfo)->ucRdiFlag;\
    (pstPpiRmepInfo)->ucRemoteIfFlag = (pstRmepInfo)->ucRemoteIfFlag;\
    (pstPpiRmepInfo)->ucVlanFlag = (pstRmepInfo)->ucVlanFlag;\
    (pstPpiRmepInfo)->ucRMepStatic = (pstRmepInfo)->ucRMepStatic;\
    (pstPpiRmepInfo)->ucMdLevel = (pstRmepInfo)->ucMdLevel;\
}

#define INFO_MAX_LEN  800

#define LB_OUTPUT(szBuf,ulID)                \
if (g_pfOAM1AGOutputInfo)               \
{                                       \
    (VOID)g_pfOAM1AGOutputInfo((UCHAR *)szBuf,ulID);   \
}

#define LT_OUTPUT(szBuf,ulID)                \
if (g_pfOAM1AGOutputInfo)               \
{                                       \
    (VOID)g_pfOAM1AGOutputInfo((UCHAR *)szBuf,ulID);   \
}


#define OAM_1AG_INFOOUTPUTCOUNT_EACHTIME    (8)

/* 用于计算动态CCM的老化时间 */
#define OAM_1AG_1TIMERSOLD(x)    ((x) * 1200)
#define OAM_1AG_10TIMERSOLD(x)   ((x) * 120)
#define OAM_1AG_100TIMERSOLD(x)  ((x) * 12)

/*Added by luogaowei 2013-2-2  DTS2013020403949
由于Y1731和1AG 功能是独立的，需要共享RMEP信息； 所以表项的下发和 CC探测 两个功能需要分离。
考虑到其他产品不使用Y1731，需要兼容老功能。
即 g_ulRmepCCDetectMode 打开情况下 底层对应表项下发不再启动CC探测功能(hert3.3)
其他产品 在接收RMEP下发后继续启动CC探测功能
*/

#define OAM_1AG_RMEP_NOTIFY     1  /*1AG 表项下发标记*/
#define OAM_1AG_RMEP_CC_DETECT  2  /*1AG  RMEP CC探测标记*/

#ifdef  __cplusplus
}
#endif

#endif

