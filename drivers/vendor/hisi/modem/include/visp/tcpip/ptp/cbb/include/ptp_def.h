/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_def.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP
*  Date Created: 2008-06-02
*        Author: Yaochengliang
*   Description: PTP特性宏定义头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME               DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-02    Yaochengliang        Create
*
*******************************************************************************/

#ifndef _PTP_DEF_H_
#define _PTP_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*定义PTP模块MID/SID*/
/*Mod By t00110672 For BC3D01181,2009.2.17,使用统一分配的MID*/
#define PTP_MID  MID_COMP_PTP

#define SID_PTP_UNICAST_SLAVE_S       1  /*存放单播SLAVE及其列表*/
#define SID_PTP_CLOCK_S               2  /*存放PTP时钟实体*/
#define SID_PTP_LOGIC_TIMER_S         3  /*存放PTP逻辑定时器实体*/
#define SID_PTP_DEFAULT_SOCKET_PACKET 4  /*存放Socket报文缓存*/
#define SID_PTP_MAC_VLAN              5  /*用于存放VLAN相关信息*/
#define SID_PTP_UNICAST_SLAVE_TABLE   6  /*用于存放slave table 结构体*/
#define SID_PTP_PORT_ADDR_VRF         7  /* 用于存放PTP_PORT_ADDR_VRF_S结构体 */
#define SID_PTP_VRF_SOCKET            8  /* 用于存放PTP_PORT_ADDR_VRF_S结构体 */

/*Mod end */

/* PTP版本号 */
#define PTP_VERSION                     2

/* Keep alive 报文最大超时次数 */
#define PTP_LIVE_EXPIRES_NUMBER         3

/* Keep alive 报文的发送间隔 64S */
#define PTP_LIVE_INTERVAL               6

#define PTP_LIVE_MAX_INTERVAL           10

#define PTP_LIVE_MSG_LEN                34

/* 定义文本的长度规格，用于txt TLV中 */
#define PTP_TXT_SUPPORT_LEN             256

/* 定义单播master列表配置规格,每次只能配值个数的最大值 */
#define PTP_UNICAST_MASTR_CFG_LEN       5

/*定义单播foreign Master列表长度规格*/
#define PTP_FOREIGN_MASTR_LEN           2

/*定义单播slave列表长度规格*/
#define PTP_UNICAST_SLAVE_LEN           10240


#define PTP_TRUE  1
#define PTP_FALSE 0



/*定义PTP端口地址的个数宏*/
#define PTP_PORT_ADDR_NUM               2

/*定义foreignMasterDS,BMC相关*/
#define FOREIGN_MASTER_TIME_WINDOW      4

/*任务最大优先级宏定义*/
#define PTP_MAX_TASK_PRI                255

/* 握手回应消息长度 */
#define PTP_HANDSHAKE_RESP_LEN          12

/* 握手请求消息长度 */
#define PTP_HANDSHAKE_REQ_LEN           4

/* PTP header长度 */
#define PTP_HEADER_LEN                  34

/* PTP udp/ipv4地址长度 */
#define PTP_ADDRLEN_UDP_IPV4            4

/* PTP udp/ipv4地址长度 */
#define PTP_ADDRLEN_UDP_IPV6            16
/*扩展TLV*/
#define PTP_TLV_SYNC_LEN                10


/* ptp单播协商tlv 长度 */
#define PTP_TLV_HEADER_LEN              44

/*单播长度*/
#define PTP_ONE_SIANGLING_TLV_PKTLEN    128

/*ST问题: REQ 协商消息TLV 静核的长度应该为6， 20080723, l00128792*/
/* 普通TLV长度 */
#define PTP_GENERAL_TLV_LEN             6

/* 扩展TLV长度 */
#define PTP_EXTEND_TLV_LEN              14

/*Mod By t00110672  10-1-8,支持路由器关于实现最新草案的需求 */
/* announce log interval最大最小值宏定义 */
#define PTP_MAX_ANNOUNCE_LOGINTERVAL       4

#define PTP_MIN_ANNOUNCE_LOGINTERVAL      (-3)

/* sync log interval最大最小值宏定义 */
#define PTP_MAX_SYNC_LOGINTERVAL       4

#define PTP_MIN_SYNC_LOGINTERVAL      (-7)

/* delay/pdelay Req interval最大最小值宏定义 */
#define PTP_MAX_MINDELAY_REQ_LOGINTERVAL       4

#define PTP_MIN_MINDELAY_REQ_LOGINTERVAL      (-7)

/*Mod End*/

#define PTP_MAX_NEW_PROFILE_CLASS 110
#define PTP_MIN_NEW_PROFILE_CLASS 80

/* announce最小接收超时倍数 */
#define PTP_MIN_RECEIPT_TIMEOUT        2

/* 当前版本的PTP端口固定号宏 */
#define PTP_PORT_NO_ZERO                0

#define VLANTYPE_DOT1Q   0x8100         /* VLAN 802.1q格式*/
#define DOT1Q_TAG_SIZE   4
#define PTP_IEEE8023_ETHTYPE 0x88f7     /*1588 OVER MAC 以太类型*/
/* Modified by jijianhua00169178, 事件id需要使用高16位, 2012/1/13   问题单号:DTS2012011304845 */
#define PTP_EVT_IEEE8023MSG_Q 0x00020000         /*MAC报文写入到PTP队列使用该消息*/
/*End of Modified by jijianhua00169178, 2012/1/13   问题单号:DTS2012011304845 */
#define PTP_IEEE8023MSGT 0x00001000     /*MAC报文写入到PTP队列MSG[0]使用该标识*/
#define PTP_ADDRLEN_IEEE8023 6          /* PTP MAC 地址长度 */

/* 定义dscp默认值宏 */
/*Added by zhangliangzhi00187023, 【检视发现问题】关于修改dscp默认值为56。, 2012/3/29   问题单号:DTS2012032903015 */
#define PTP_DEFAULT_DSCP     0x38
/* End of Added by zhangliangzhi00187023, 2012/3/29   问题单号:DTS2012032903015 */


/*PTP IPV6 MSG*/
#define PTP_IPV6MSGT 0x00002000     /*IPV6报文写入到PTP队列MSG[0]使用该标识*/

/* Modified by jijianhua00169178, 事件id需要使用高16位，且只能使用1位, 2012/1/13   问题单号:DTS2012011304845 */
#define PTP_EVT_IPV6MSG_Q 0x00040000         /*IPV6报文写入到PTP队列使用该消息*/
/*End of Modified by jijianhua00169178, 2012/1/13   问题单号:DTS2012011304845 */

/*Add By t00110672/z00146309  10-1-11,支持路由器关于实现最新草案的需求 */
#define PTP_KEEP_ALIVE_MODE_OLD  0
#define PTP_KEEP_ALIVE_MODE_NEW  1

/*Add by dutianyi 14-7-14 支持以G8275.1标准接收处理报文*/
#define PTP_G82751_MODE_DISABLE 0
#define PTP_G82751_MODE_ENABLE 1
/*End of adding*/

#define PTP_MIN_DURATION_FIELD 60
#define PTP_MAX_DURATION_FIELD 1000
#define PTP_DEFAULT_DURATION_FIELD 300

/*Ann 报文发送定时器基数*/
#define PTP_ANN_SEND_TIMER_BASE 125

/*Add By t00110672 For BC3D02818,【TD产品需求】【PTP】实现1588无线选源方案优化*/
/*优选源类型*/
#define PTP_CLOCK_CLASS_6      6
#define PTP_CLOCK_CLASS_7      7
#define PTP_CLOCK_CLASS_13    13
#define PTP_CLOCK_CLASS_14    14

/*是否为优选源*/
#define PTP_IS_PRI_CLOCK_SOURCE(clkclass)\
    ((g_pstPtpClock->ucClass0 == clkclass)\
    || (g_pstPtpClock->ucClass1 == clkclass)\
    || (g_pstPtpClock->ucClass2 == clkclass)\
    || (g_pstPtpClock->ucClass3 == clkclass))\

/*Add By t00110672 For BC3D03289,在单播IP模式下，仍可以添加单播master physical地址列表，应该增加此限制*/
#define IP_ADDR_VALID( stAddr )\
    (((PTP_PROTOCAL_UDP_IPV4 == (stAddr).usNetworkProtocol)&&(PTP_ADDRLEN_UDP_IPV4 == (stAddr).usAddressLength))\
   ||((PTP_PROTOCAL_UDP_IPV6 == (stAddr).usNetworkProtocol)&&( PTP_ADDRLEN_UDP_IPV6 == (stAddr).usAddressLength)))

#define PTP_IS_MASTER()                                                \
    (PTP_CLOCK_FSM_MODE_MASTER_ONLY == g_pstPtpClock->ucClockFsmMode) 

#define PTP_IS_SLAVE()                                                 \
    (PTP_CLOCK_FSM_MODE_SLAVE_ONLY == g_pstPtpClock->ucClockFsmMode) 

#define PTP_IS_UNICAST()                                    \
    (PTP_CLOCK_UNICAST_MODE == g_pstPtpClock->ucCastMode) 

#define PTP_IS_MULTICAST()                                    \
    (PTP_CLOCK_MULTICAST_MODE == g_pstPtpClock->ucCastMode) 

#define PTP_IS_OVERMAC()                                    \
    (PTP_CLOCK_IEEE8023_MODE == g_pstPtpClock->ucCastMode) 

#define PTP_IS_NEW_MODE()                                   \
    (PTP_KEEP_ALIVE_MODE_NEW == g_ucKeepAliveMode)

#define PTP_IS_OLD_MODE()                                   \
    (PTP_KEEP_ALIVE_MODE_OLD == g_ucKeepAliveMode)


#define ADDR_VALID( stAddr )\
    (((PTP_PROTOCAL_UDP_IPV4 == (stAddr).usNetworkProtocol)&&(PTP_ADDRLEN_UDP_IPV4 == (stAddr).usAddressLength))\
      || ((PTP_PROTOCAL_IEEE_802 == (stAddr).usNetworkProtocol)&&(PTP_ADDRLEN_IEEE8023 == (stAddr).usAddressLength))\
      || (( PTP_PROTOCAL_UDP_IPV6 == (stAddr).usNetworkProtocol)&&( PTP_ADDRLEN_UDP_IPV6 == (stAddr).usAddressLength)))

#define PTP_IS_IPV4_ADDR(pstAddr)                              \
    ((PTP_PROTOCAL_UDP_IPV4 == (pstAddr)->usNetworkProtocol)   \
    && (PTP_ADDRLEN_UDP_IPV4 == (pstAddr)->usAddressLength))   

#define PTP_IS_IPV6_ADDR(pstAddr)                              \
    ((PTP_PROTOCAL_UDP_IPV6 == (pstAddr)->usNetworkProtocol)   \
    && (PTP_ADDRLEN_UDP_IPV6 == (pstAddr)->usAddressLength))   

#define PTP_IS_MAC_ADDR(pstAddr)                               \
    ((PTP_PROTOCAL_IEEE_802 == (pstAddr)->usNetworkProtocol)   \
    && (PTP_ADDRLEN_IEEE8023 == (pstAddr)->usAddressLength))   


/*slave状态下仅允许配置允许配置一种类型地址*/
#define PTP6_ADDR_VALID(stPortAddr)\
    (!((PTP_CLOCK_FSM_MODE_SLAVE_ONLY == g_pstPtpClock->ucClockFsmMode)\
    && ((PTP6_CheckIfIPV6Enable() && (PTP_PROTOCAL_UDP_IPV6 != (stPortAddr).usNetworkProtocol))\
        || (!PTP6_CheckIfIPV6Enable() && (PTP_PROTOCAL_UDP_IPV4 != (stPortAddr).usNetworkProtocol)))))

/*定义CLOCK ID的相等判断宏，ulResult为0则相等，其他值为不等*/
#define PTP_IS_CLOCK_ID_EQUAL(szDescClockId,szSrcClockId,ulResult) \
{\
    (VOID)VOS_Mem_Cmp((VOID*)szDescClockId, (VOID*)szSrcClockId, PTP_CLOCK_ID_LEN, (LONG*)&ulResult); \
}

/*定义PORT_ADDR的相等判断宏，ulResult为0则相等，其他值为不等*/
#define PTP_IS_PORT_ADDR_EQUAL(pstDescPortAddr, pstSrcPortAddr, lResult) \
{\
    (VOID)PTP_Addr_Cmp(pstDescPortAddr, pstSrcPortAddr, (LONG*)&lResult);\
}

/* 计算转换log值到毫级别的整数的宏 */
#define PTP_CAL_LOG_TO_MILL(cLogValue,ulMillValue)\
{\
    ULONG ulLogValueAbs = 0;\
    (ulMillValue) = 1;     \
    ulLogValueAbs = (cLogValue) >= 0 ? (cLogValue) : -(cLogValue);\
    (ulMillValue) = (ulMillValue) << ulLogValueAbs;\
    (ulMillValue) = (cLogValue) >= 0 ? (1000 * (ulMillValue)):(1000 / (ulMillValue));\
}

#define PTP_GRANT_ACQUIRED(ulMasterIp, bGrantR, ulMsgType)  \
{\
    if (NULL != g_pfPtpGrantAcquired)\
    {\
        (VOID)g_pfPtpGrantAcquired(ulMasterIp, &bGrantR, ulMsgType);\
    }\
    else\
    {\
        bGrantR = BOOL_TRUE;\
    }\
}

/*Begin Add by heyijun KF37287 for DTS2011062105058 支持clock id授权方案*/
/* Modified by weishanfengwKF61331, 产品授权是否拒绝请求, 2011/11/26   问题单号:S.PTP.ANNCHOOK.01  */
#define PTP_GRANT_ACQUIRED_BY_ID(pstPortId, bGrantR, ulPtpMsgType, ulAnnInterval, cSlaveFlag)\
{\
    if (NULL != g_pfPtpGrantAcquiredById)\
    {\
        PTP_GRANT_PARA_S stMsgPara;\
        (VOID)TCPIP_Mem_Set((CHAR *)&stMsgPara, 0, sizeof(PTP_GRANT_PARA_S));\
        (VOID)TCPIP_Mem_Copy(&(stMsgPara.stPortId),sizeof(PTP_PORT_ID_S),(pstPortId),sizeof(PTP_PORT_ID_S));\
        stMsgPara.ulMsgType= (ULONG)(ulPtpMsgType);\
        stMsgPara.cAnnInterval = (ulAnnInterval);\
        stMsgPara.cSlaveFlag = (cSlaveFlag);\
        (VOID)g_pfPtpGrantAcquiredById(&stMsgPara, &(bGrantR));\
    }\
/*End of Modified by weishanfengwKF61331, 2011/11/26   问题单号:S.PTP.ANNCHOOK.01 */\
    else\
    {\
        (bGrantR) = BOOL_TRUE;\
    }\
}
/*End Add by heyijun KF37287 for DTS2011062105058 支持clock id授权方案*/

/*打印输出宏*/
#define PTP_DEBUGINFO_OUTPUT(ulDebugType,szBuffer)\
{\
    if (ulDebugType & g_ulPtpGlobalDbgSwitch)\
    {\
        PTP_DBG_OUTPUT(szBuffer);\
    }\
}

/* 删除运行表 */
#define PTP_DEL_RUNMASTERTAB(pstUniMaster)\
{\
    PTP_ClearUnicastMasterRunInfo(pstUniMaster);\
}

/* 删除总表 */
#define PTP_DEL_TOTALMASTERTAB(pstUniMaster)\
{\
    PTP_ClearUnicastMasterCfgInfo(pstUniMaster);\
}

/* 设置Delay_Resp/Pdelay_Resp时间间隔值 */
#define PTP_SET_PPI_DELAYRESP_INTERVAL(ucDelayMechanism,cLogMinDelayReqInterval,cLogMinPdelayReqInterval,cLogInterMessagePeriod)\
{\
    if (PTP_DELAY_MACHENISM_E2E == ucDelayMechanism)\
    {\
        cLogMinDelayReqInterval = cLogInterMessagePeriod;\
        cLogMinPdelayReqInterval = 0;\
    }\
    else\
    {\
        cLogMinDelayReqInterval = 0;\
        cLogMinPdelayReqInterval= cLogInterMessagePeriod;\
    }\
}

/* if x not equs NULL return ERR_CODE, make sure x is null */
#define  PTP_CHECK_NUL(X, ERR_CODE)       \
{                                          \
    if (NULL != (X))                       \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

/* if x equs NULL return ERR_CODE, make sure x is not null */
#define  PTP_CHECK_NNU(X, ERR_CODE)       \
{                                          \
    if (NULL == (X))                       \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define  PTP_CHECK_NEQ(X, Y, ERR_CODE)     \
{                                          \
    if ((X) == (Y))                        \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define  PTP_CHECK_EQU(X, Y, ERR_CODE)     \
{                                          \
    if ((X) != (Y))                        \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_TRUE(VALUE, ERR_CODE)    \
{                                          \
    if (!(VALUE))                          \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_FALSE(VALUE, ERR_CODE)   \
{                                          \
    if (VALUE)                             \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_GT(X, Y, ERR_CODE)       \
{                                          \
    if ((X) <= (Y))                        \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_LT(X, Y, ERR_CODE)       \
{                                          \
    if ((X) >= (Y))                        \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_GE(X, Y, ERR_CODE)       \
{                                          \
    if ((X) < (Y))                         \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_LE(X, Y, ERR_CODE)       \
{                                          \
    if ((X) > (Y))                         \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}



/*调试输出宏*/
#define PTP_DBG_OUTPUT(pszMsg)  do\
                                {\
                                    if (NULL != g_pfDbgOutput)\
                                    {\
                                        g_pfDbgOutput(pszMsg);\
                                    }\
                                }while (FALSE)

#define PTP_WARN_OUTPUT(ulWarnId, pWarnParam)    do\
                                {\
                                    PTP_WarningOut(ulWarnId,pWarnParam);\
                                }while (FALSE)


/* 主机序转为网络序 */
#define PTP6_ADDRESS_HTON(x) \
{\
    (x)[0] = VOS_HTONL((x)[0]);\
    (x)[1] = VOS_HTONL((x)[1]);\
    (x)[2] = VOS_HTONL((x)[2]);\
    (x)[3] = VOS_HTONL((x)[3]);\
}

/* 网络序 转为主机序*/
#define PTP6_ADDRESS_NTOH(x) \
{\
    (x)[0] = VOS_NTOHL((x)[0]);\
    (x)[1] = VOS_NTOHL((x)[1]);\
    (x)[2] = VOS_NTOHL((x)[2]);\
    (x)[3] = VOS_NTOHL((x)[3]);\
}

/*IPv6地址赋值*/
#define IPV6_ADDR_COPY(dst, src)\
{\
    dst[0] = src[0];\
    dst[1] = src[1];\
    dst[2] = src[2];\
    dst[3] = src[3];\
}

#define PTP_REQUEST_UNICAST_TRANSMISSION_TLV_LEN            6
#define PTP_GRANT_UNICAST_TRANSMISSION_TLV_LEN              8
#define PTP_ACK_CANCEL_UNICAST_TRANSMISSION_TLV_LEN         2
#define PTP_CANCEL_UNICAST_TRANSMISSION_TLV_LEN             2
#define PTP_ORGANIZATION_EXTENSION_TLV_LEN                  14

#define PTP_TLVLEN_CHECK(type, len)\
    (((PTP_REQUEST_UNICAST_TRANSMISSION == type) && (PTP_REQUEST_UNICAST_TRANSMISSION_TLV_LEN == len))\
    || ((PTP_GRANT_UNICAST_TRANSMISSION == type) && (PTP_GRANT_UNICAST_TRANSMISSION_TLV_LEN == len))\
    || ((PTP_CANCEL_UNICAST_TRANSMISSION == type) && (PTP_CANCEL_UNICAST_TRANSMISSION_TLV_LEN == len))\
    || ((PTP_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION == type) && (PTP_ACK_CANCEL_UNICAST_TRANSMISSION_TLV_LEN == len))\
    || ((PTP_ORGANIZATION_EXTENSION == type) && (PTP_ORGANIZATION_EXTENSION_TLV_LEN == len)))

#define PTP_IS_MULTI_TLV_WITH_DELAY(ptp_port_num)\
    ((PTP_KEEP_ALIVE_MODE_NEW == g_ucKeepAliveMode)\
    && (PTP_DELAY_MACHENISM_E2E == g_pstPtpClock->stPtpPort[ptp_port_num].ucDelayMechanism))


#define PTP_NEWPROFILE_DEFAULT_CLASS      255
#define PTP_NEWPROFILE_DEFAULT_DOMAIN     4
#define PTP_NEWPROFILE_DEFAULT_QUERYMAX   3

#define PTP_YES    1
#define PTP_NO     0
/*如果定时器超时时间ulOutTime + ulTimeLow时间小于0xFFFFFFFF,
 *就保持ulEndTimeHigh不变，直接在ulEndTimeLow上加上ulOutTime即可*/

/*如果定时器超时周期 + ulTimeLow时间大于0xFFFFFFFF,
 *ulEndTimeHigh需要加1，在ulEndTimeLow上加上周期 */
#define PTP_SET_OUTTIME(interval ,timenowhigh ,timenowlow ,dsthigh ,dstlow)\
{\
    ULONG ultime = 0;\
    ultime = 0xFFFFFFFF - timenowlow;\
    if (ultime >= interval)\
    {\
        dstlow  = timenowlow + interval;\
        dsthigh = timenowhigh;\
    }\
    else \
    {\
        dsthigh = timenowhigh + 1;\
        dstlow  = interval + ultime;\
    }\
}

#define PTP_CANCEL_QUERY_DEFAULT    3

#define PTP_TIMER_COUNT_MAX         10240
#define PTP_TIMER_COUNT_MIN         500

/* 地址比较失败或者不相等的时候输出值 */

/*Added by guo00178934, 清除PTP模块"宏定义宏值定义为负数，但未加括号"导致的PC Lint告警, 2011/8/30   问题单号:DTS2011083000609 */
#define PTP_ADDRCMP_ERR         (-1)
/* End of Added by guo00178934, 2011/8/30   问题单号:DTS2011083000609 */



#define PTP_DEL_TIMER(ulTimerId)\
{\
    if (ulTimerId)\
    {\
        (VOID)PTP_DeleteLogicTimer(ulTimerId);\
        ulTimerId = 0;\
    }\
}

#define  PTP_NP_PPI_ADD_FLAG  0x01
#define  PTP_NP_PPI_SET_FLAG  0x02

#define PTP_IPV6_END_EXTEND_SIZE   2 /*ptp ipv6报文末尾扩展2字节*/

#define  PTP_MASTER_CANCEL_OR_ACK_OR_REFUSE(flag)   \
    ((PTP_STATE_UNICAST_NEGO_CANCEL == flag)         \
    || (PTP_STATE_UNICAST_NEGO_ACK == flag)         \
    || (PTP_STATE_UNICAST_NEGO_REFUSE == flag))

#define  PTP_MASTER_ACK_OR_REFUSE(flag)   \
    ((PTP_STATE_UNICAST_NEGO_ACK == flag)         \
    || (PTP_STATE_UNICAST_NEGO_REFUSE == flag))

/*Added by guo00178934, two-way模式，是否允许sync和delay序号相同, 2012/1/5   问题单号:20120105_2 */
#define PTP_TWOWAY_SEQID_CHECK_DIFF 1 /*two way 应答 sync 、delay序列不能相同 默认值此情况，即默认和TP5000 对接不成功*/ 
#define PTP_TWOWAY_SEQID_CHECK_SAME 2 /*two way 应答 sync 、delay序列必须相同*/ 
#define PTP_TWOWAY_SEQID_CHECK_ALL  (PTP_TWOWAY_SEQID_CHECK_DIFF|PTP_TWOWAY_SEQID_CHECK_SAME) /*兼容上述两种情况 */
/* End of Added by guo00178934, 2012/1/5   问题单号:20120105_2 */

/*Added by guo00178934, Duration重协商时间用户可配, 2012/1/7   问题单号:20120107_1 */
#define PTP_DURATION_TIMEOUT_PERCENT_MIN  50
#define PTP_DURATION_TIMEOUT_PERCENT_MAX  99

/*计算Duration重协商的时间*/
#define PTP_DURATION_TIMEOUT_PERIOD(ulDuration, ulPrecent) \
  ((ulDuration) * 1000 * (ulPrecent) / 100)
/* End of Added by guo00178934, 2012/1/7   问题单号:20120107_1 */

/*Added by guo00178934, 拷贝单播Master告警信息, 2012/1/13   问题单号:20120112_1 */
#define PTP_CPY_WARNING_INFO(pstWarnParam, pstUniMaster, pstPtpPort)  \
{\
    if(((pstUniMaster) != NULL) && \
      ((pstPtpPort) != NULL)) \
    {\
        if (PTP_FALSE == PTP6_CheckIfIPV6Enable())\
        {\
            VOS_CopyVar((pstWarnParam)->stLocalPortAddr, (pstPtpPort)->stLocalPortAddr[0]); \
        }\
        else\
        {\
            VOS_CopyVar((pstWarnParam)->stLocalPortAddr, (pstPtpPort)->stLocalPortAddr6[0]);  \
        }\
        VOS_CopyVar((pstWarnParam)->stDstPortAddr, (pstUniMaster)->stPortAddr); \
        (pstWarnParam)->ulVrfIndex = (pstUniMaster)->ulVrfIndex;  \
        (pstWarnParam)->usPtpPortNum = (pstPtpPort)->stPortId.usPortNumber; \
    }\
}
/* End of Added by guo00178934, 2012/1/13   问题单号:20120112_1 */

/*Added by limin00188004, 1588 PTP支持多TLV处理和协商链路单独删除, 2012/9/21   问题单号:S.PTP.02.01 */
#define PTP_MASTER_DURATION_SWITCH() (PTP_YES == g_ulPtpMasterDurationSwitch)
/* End of Added by limin00188004, 2012/9/21   问题单号:S.PTP.02.01 */

#define PTP_UNI_SLAVE_TBL_HASH_SIZE 64
#define PTP_UNI_SLAVE_TBL_HASH(pstPortAddr) \
    ((UINT8)((pstPortAddr->unAddr.ulIpv4 >> 24) \
                      ^ (pstPortAddr->unAddr.ulIpv4 >> 16) \
                      ^ (pstPortAddr->unAddr.ulIpv4 >> 8) \
                      ^ (pstPortAddr->unAddr.ulIpv4)) % PTP_UNI_SLAVE_TBL_HASH_SIZE)

#ifdef __cplusplus
}
#endif


#endif

