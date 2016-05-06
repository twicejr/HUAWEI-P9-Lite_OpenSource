/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ImsNic.h
  版 本 号   : 初稿
  作    者   : caikai
  生成日期   : 2013年7月16日
  最近修改   :
  功能描述   : IMS虚拟网卡内部头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月30日
    作    者   : caikai
    修改内容   : 创建文件

******************************************************************************/


#ifndef __IMSNIC_H__
#define __IMSNIC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "ImsNicInterface.h"

#if( FEATURE_ON == FEATURE_IMS )
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"

#if (VOS_OS_VER == VOS_WIN32)
#include  "VxWorksStub.h"
#endif  /* VOS_OS_VER == VOS_WIN32 */


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define UEPS_PID_IMSNIC                    UEPS_PID_IPS_CCORE


#define IMS_NIC_RAB_ID_MAX_NUM             (11)                         /* RAB的最大个数值 */

#define IMS_NIC_RAB_ID_OFFSET              (5)

#define IMS_NIC_RAB_ID_MIN                 (5)                          /* Rab Id的最小值 */
#define IMS_NIC_RAB_ID_MAX                 (15)                         /* Rab Id的最大值 */

#define IMS_NIC_RAB_ID_INVALID             (0xFF)

#define IMS_NIC_ETH_HDR_SIZE               (14)
#define IMS_NIC_ETHER_ADDR_LEN             (6)

#define IMS_NIC_IPV4_VERSION               (4)                          /* IP头部中IP V4版本号 */
#define IMS_NIC_IPV6_VERSION               (6)                          /* IP头部中IP V6版本号 */
#define IMS_NIC_IP_VERSION_POS             (4)                          /* IP数据包的协议版本字段偏移 */
#define IMS_NIC_IP_VERSION_MASK            (0x0F)                       /* IP数据包的协议版本字段掩码 */

#define IMS_NIC_MIN_IPPKT_LEN              (20)                         /* 最小IP包长度 */
#define IMS_NIC_MAX_IPPKT_LEN              (1500)                       /* IMS虚拟网卡限定最大IP包长度 */

#define IMS_NIC_IPPKT_OFFSET               (4)                          /* IP包在上层传下的数据中的偏移 */

#define IMS_NIC_ETHERTYPE_IPV4             (0x0800)                     /* 主机序形式，表示IPv4包类型  */
#define IMS_NIC_ETHERTYPE_IPV6             (0x86DD)                     /* 主机序形式，表示IPv6包类型  */
#define IMS_NIC_ETHERTYPE_ARP              (0x0806)                     /* 主机序形式，表示ARP包类型  */

#define IMS_NIC_CMD_LEN                    (200)

#define IMS_NIC_IP_ADDR_MAX_LENGTH         (16)                         /* IP地址的最大长度，取IPV6的长度 */

#define IMS_NIC_UL_SEND_BUFF_SIZE          (1520)                       /* IMS虚拟网卡上行发送缓存大小 */

#define IMS_NIC_SPEED_100M                 (100000000)                  /* 100Mbs */

#define IMS_NIC_IPV6_ADDR_BIT_LEN          (128)
#define IMS_NIC_IPV6_ADDR_STR_LEN          (39)
#define IMS_NIC_IPV6_STR_RFC2373_TOKENS    (8)
#define IMS_NIC_IPV6_STR_DELIMITER         ':'                          /* RFC2373使用的IPV6文本表达方式使用的分隔符 */

#define IMS_NIC_MODEM_ID_LEN               (2)                          /* ModemId占用2个字节*/
#define IMS_NIC_MODEM_ID_OFFSET            (4)                          /* 填写可维可测时使用，保持字节对齐 */

#define IMS_NIC_LOG_RECORD_MAX_NUM         (10)
#define IMS_NIC_LOG_PARAM_MAX_NUM          (4)

#define IMS_NIC_TYPE_HEX                   (16)
#define IMS_NIC_TYPE_DEC                   (10)

#define IMS_NIC_MTU_DEFAULT_VALUE          (1280)                       /* MTU默认值 */

#define IMS_NIC_ROUND_UP(x, n)             (((x)+(n)-1U) & ~((n)-1U))  /* 取n的倍数 */

#define IMS_NIC_DEFAULT_ROUTE_GATEWAY      (0x01010101)                 /* 设置IPV4静态路由时配置的下一跳 */
#define IMS_NIC_DEFAULT_IPV6_MASK_LEN      (128)                        /* IPV6默认的掩码长度是128 */
#define IMS_NIC_MAC_STR_LEN                (15)                         /* MAC地址长度xxxx-xxxx-xxxx */
#define IMS_NIC_ENABLE_HOST_MODE           (1)                          /* 使能主机模式 */
#define IMS_NIC_ENABLE_IPV6_FORWARDING     (1)                          /* 使能IPV6转发 */
#define IMS_NIC_DISABLE_IPV6_FORWARDING    (0)                          /* 去使能IPV6转发 */

#define IMS_NIC_IFNAMSIZ                   (16)                         /*虚拟网卡名称长度*/

/* DNS数量，取4的整数倍防止结构体大小不是4的整数倍 */
#define IMS_NIC_DNS_NUM_ADAPTER            IMS_NIC_ROUND_UP(IMS_NIC_MAX_DNS_SERVER_NUM,4)

#define IMS_NIC_IS_RAB_VALID(rabId) \
        ((rabId >= IMS_NIC_RAB_ID_MIN) && (rabId <= IMS_NIC_RAB_ID_MAX))

/* 统计操作 */
#define IMS_NIC_STATS_INC(type, n, modem)  \
        (g_astImsNicEntity[modem].stImsNicStatsInfo.aulStats[type] += n)

#define IMS_INC_STATS_SHOW(type, modem) \
        vos_printf("%s      %d \n", #type, g_astImsNicEntity[modem].stImsNicStatsInfo.aulStats[type])

/* 获取IMS虚拟网卡实体 */
#define IMS_NIC_GET_ENTITY_STRU(modem)              (&g_astImsNicEntity[modem])

/* 获取虚拟网卡名 */
#define IMS_NIC_GET_NIC_NAME                        (g_stImsNicManageTbl.ucImsNicName)

/* 获取目的MAC地址 */
#define IMS_NIC_GET_DST_MAC_ADDR(modem) \
        (g_stImsNicManageTbl.astImsNicElementTbl[modem].stIpv4Ethhead.aucEtherDhost)

#define IMS_NIC_IPV4_DNS_CONFIG(ipAddr, pstDnsInfo, pstPdnInfo) \
        IMS_NIC_DnsConfig(ipAddr, IMS_NIC_IPV4_ADDR_LENGTH, pstDnsInfo, pstPdnInfo)

#define IMS_NIC_IPV6_DNS_CONFIG(ipAddr, pstDnsInfo, pstPdnInfo) \
        IMS_NIC_DnsConfig(ipAddr, IMS_NIC_IPV6_ADDR_LENGTH, pstDnsInfo, pstPdnInfo)

#define IMS_NIC_IPCOM_DNSS_CONFIG(indx, ipAddrStr) \
        IMS_NIC_MNTN_TRACE2(ID_IMS_NIC_MNTN_TRACE_DNS_CFG, ipAddrStr, sizeof(ipAddrStr), indx, (VOS_UINT32)ipcom_sysvar_set(g_pcDnsSSysVarName[indx], (VOS_CHAR *)ipAddrStr, IPCOM_SYSVAR_FLAG_OVERWRITE))

#define IMS_NIC_IPCOM_DNSS_DEL(indx) \
        IMS_NIC_MNTN_TRACE2(ID_IMS_NIC_MNTN_TRACE_DNS_DEL, "", sizeof(""), indx, (VOS_UINT32)ipcom_sysvar_set(g_pcDnsSSysVarName[indx], (VOS_CHAR *)"", IPCOM_SYSVAR_FLAG_OVERWRITE))

/* 获取IMS虚拟网卡基本信息表 */
#define IMS_NIC_GET_ELEMENT_TABLE(modem)            (&(g_stImsNicManageTbl.astImsNicElementTbl[modem]))

/* 获取IMS虚拟网卡设备结构 */
#define IMS_NIC_GET_DEV_STRU_PTR(modem)             (&g_astImsNicDev[modem])

#define IMS_NIC_GET_MTU                             (g_stImsNicCtx.ulMtu)               /* 获取IMS虚拟网卡MTU值 */
#define IMS_NIC_SET_MTU(n)                          (g_stImsNicCtx.ulMtu = (n))         /* 设置IMS虚拟网卡MTU值 */

#define IMS_NIC_GET_SAVED_UL_DATA_FUNC(modem)       (g_stImsNicCtx.pTmpSendFunc[modem])
#define IMS_NIC_SAVE_UL_DATA_FUNC(modem, pFunc)     (g_stImsNicCtx.pTmpSendFunc[modem]  = (pFunc))

#define IMS_NIC_IP4_TO_STR(str, ipArray)  \
        VOS_sprintf((VOS_CHAR *)str, "%d.%d.%d.%d", ipArray[0], ipArray[1], ipArray[2], ipArray[3])

#define IMS_NIC_SET_CMD_END(cmd, indx) \
        PS_MEM_SET(&cmd[indx], 0, sizeof(cmd) - indx); \
        (cmd[indx] = '\0')

#define IMS_NIC_MNTN_TRACE_DATA_OFFSET_LEN           /*lint -e(545) -e(413)*/TTF_OFFSET_OF(IMS_NIC_MNTN_TRACE_MSG_STRU, aucData)

#define IMS_NIC_INFO_LOG(ModuleId, str)
#define IMS_NIC_INFO_LOG1(ModuleId, str, para1)
#define IMS_NIC_INFO_LOG2(ModuleId, str, para1, para2)
#define IMS_NIC_INFO_LOG3(ModuleId, str, para1, para2, para3)
#define IMS_NIC_INFO_LOG4(ModuleId, str, para1, para2, para3, para4)

#ifdef __UT_CENTER__
#define IMS_NIC_WARNING_LOG(ModuleId, str) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, 0, 0, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_WARNING_LOG1(ModuleId, str, para1) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, 0, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_WARNING_LOG2(ModuleId, str, para1, para2) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_WARNING_LOG3(ModuleId, str, para1, para2, para3) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, (VOS_INT32)para3, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_WARNING_LOG4(ModuleId, str, para1, para2, para3, para4) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, (VOS_INT32)para3, (VOS_INT32)para4); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG(ModuleId, str) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, 0, 0, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG1(ModuleId, str, para1) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, 0, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG2(ModuleId, str, para1, para2) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG3(ModuleId, str, para1, para2, para3) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, (VOS_INT32)para3, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG4(ModuleId, str, para1, para2, para3, para4) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, (VOS_INT32)para3, (VOS_INT32)para4); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)
#else
#define IMS_NIC_WARNING_LOG(ModuleId, str)  \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s \r\n", str)
#define IMS_NIC_WARNING_LOG1(ModuleId, str, para1)  \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s, %d \r\n", str, para1)
#define IMS_NIC_WARNING_LOG2(ModuleId, str, para1, para2)   \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s, %d, %d \r\n", str, para1, para2)
#define IMS_NIC_WARNING_LOG3(ModuleId, str, para1, para2, para3)    \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", str, para1, para2, para3)
#define IMS_NIC_WARNING_LOG4(ModuleId, str, para1, para2, para3, para4) \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", str, para1, para2, para3, para4)

#define IMS_NIC_ERROR_LOG(ModuleId, str)    \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s \r\n", str)
#define IMS_NIC_ERROR_LOG1(ModuleId, str, para1)    \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s, %d \r\n", str, para1)
#define IMS_NIC_ERROR_LOG2(ModuleId, str, para1, para2) \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s, %d, %d \r\n", str, para1, para2)
#define IMS_NIC_ERROR_LOG3(ModuleId, str, para1, para2, para3)  \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", str, para1, para2, para3)
#define IMS_NIC_ERROR_LOG4(ModuleId, str, para1, para2, para3, para4)   \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", str, para1, para2, para3, para4)
#endif

/* IMS虚拟网卡初始化期间的错误打印，直接打印到串口 */
#define IMS_NIC_INIT_LOG_PRINT(ModuleId, String)                              vos_printf(" %s, %d, %s \r\n ", __FILE__, __LINE__,String)
#define IMS_NIC_INIT_LOG_PRINT1(ModuleId, String,Para1)                       vos_printf(" %s, %d, %s, %d \r\n ",  __FILE__, __LINE__, String, Para1)
#define IMS_NIC_INIT_LOG_PRINT2(ModuleId, String,Para1,Para2)                 vos_printf(" %s, %d, %s, %d, %d \r\n ",  __FILE__, __LINE__, String, Para1, Para2)
#define IMS_NIC_INIT_LOG_PRINT3(ModuleId, String,Para1,Para2,Para3)           vos_printf(" %s, %d, %s, %d, %d, %d \r\n ",  __FILE__, __LINE__, String, Para1, Para2, Para3)
#define IMS_NIC_INIT_LOG_PRINT4(ModuleId, String,Para1,Para2,Para3,Para4)     vos_printf(" %s, %d, %s, %d, %d, %d, %d \r\n ",  __FILE__, __LINE__, String, Para1, Para2, Para3, Para4)


#define IMS_NIC_MNTN_TRACE(msgId, pData, ulLen)   \
        IMS_NIC_MntnTrace(msgId, (VOS_UINT8 *)pData, ulLen, 0, 0)

#define IMS_NIC_MNTN_TRACE1(msgId, pData, ulLen, ulPara1)   \
        IMS_NIC_MntnTrace(msgId, (VOS_UINT8 *)pData, ulLen, ulPara1, 0)

#define IMS_NIC_MNTN_TRACE2(msgId, pData, ulLen, ulPara1, ulPara2)   \
        IMS_NIC_MntnTrace(msgId, (VOS_UINT8 *)pData, ulLen, ulPara1, ulPara2)

#define IMS_NIC_MNTN_TRACE_NO_DATA(msgId, ulPara1, ulPara2)   \
        IMS_NIC_MntnTrace(msgId, VOS_NULL_PTR, 0, ulPara1, ulPara2)

/* ----------------VxWorks 系统函数封装--------------------------- */
#if (VOS_OS_VER == VOS_WIN32)
#define IMS_NIC_MALLOC(size)                    VOS_MemAlloc(UEPS_PID_IMSNIC, STATIC_MEM_PT, size)
#define IMS_NIC_FREE(pAddr)                     VOS_MemFree(UEPS_PID_IMSNIC, pAddr)
#elif (VOS_OS_VER == VOS_RTOSCK)
/* TODO: */
#define IMS_NIC_MALLOC(size)                    malloc(size)
#define IMS_NIC_FREE(pAddr)                     free(pAddr)

#else
#define IMS_NIC_MALLOC(size)                    malloc(size)
#define IMS_NIC_FREE(pAddr)                     free(pAddr)

#endif

#define IMS_NIC_TCPIP_ADD_DNS_OP                (0)                          /* 添加指定DNS服务器操作 */
#define IMS_NIC_TCPIP_DEL_DNS_OP                (1)                          /* 删除指定DNS服务器操作 */
#define IMS_NIC_TCPIP_DEL_ALL_DNS_OP            (2)                          /* 删除所有DNS服务器操作 */
#define IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG      (0)                          /* IPV4地址类型DNS标记 */
#define IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG      (1)                          /* IPV6地址类型DNS标记 */
#define IMS_NIC_TCPIP_DEFAULT_SUBNET_MASK       (0xffffffff)                 /* 默认的掩码地址是255.255.255.255 */
#define IMS_NIC_TCPIP_DEFAULT_ROUTE_PRIORITY    (1)                          /* 路由添加时的优先级，合法范围是1~255 */
#define IMS_NIC_TCPIP_GLOBAL_ADDR_FLAG          (0)                          /* 全局地址标志 */
#define IMS_NIC_TCPIP_MAX_IMS_NIC_DATA_LEN      (2048)                       /* 最大存储数据长度 */

#define IMS_NIC_TCPIP_HEADER_RESERVE_LEN        (64)                         /* 下行报文送入VISP协议栈申请MBUF时预留的报文头长度 */
#define IMS_NIC_TCPIP_INPUT_LEN                 (200)

#define IMS_NIC_IPV6_ADDR_ELEM_0                (0)                          /* IPV6地址UINT32格式第0个元素 */
#define IMS_NIC_IPV6_ADDR_ELEM_1                (1)                          /* IPV6地址UINT32格式第1个元素 */
#define IMS_NIC_IPV6_ADDR_ELEM_2                (2)                          /* IPV6地址UINT32格式第2个元素 */
#define IMS_NIC_IPV6_ADDR_ELEM_3                (3)                          /* IPV6地址UINT32格式第3个元素 */

#define IMS_NIC_TCPIP_INPUT_LOG(str, fn, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s Return:%u \n", #fn, ulRet)

#define IMS_NIC_TCPIP_INPUT_LOG1(str, fn, ulPara1, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u Return:%u \n", #fn, ulPara1, ulRet)

#define IMS_NIC_TCPIP_INPUT_LOG2(str, fn, ulPara1, ulPara2, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%u Return:%u \n", #fn, ulPara1, ulPara2, ulRet)

#define IMS_NIC_TCPIP_INPUT_STR_LOG2(str, fn, ulPara1, szStringPara2, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%s Return:%u \n", #fn, ulPara1, szStringPara2, ulRet)

#define IMS_NIC_TCPIP_INPUT_STR2_LOG2(str, fn, szStringPara1, szStringPara2, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%s para2:%s Return:%u \n", #fn, szStringPara1, szStringPara2, ulRet)

#define IMS_NIC_TCPIP_INPUT_LOG3(str, fn, ulPara1, ulPara2, ulPara3, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%u para3:%u Return:%u \n", #fn, ulPara1, ulPara2, ulPara3, ulRet)

#define IMS_NIC_TCPIP_INPUT_STR_LOG3(str, fn, ulPara1, ulPara2, szStringPara3, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%u para3:%s Return:%u \n", #fn, ulPara1, ulPara2, szStringPara3, ulRet)

#define IMS_NIC_TCPIP_INPUT_LOG4(str, fn, ulPara1, ulPara2, ulPara3, ulPara4, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%u para3:%u para4:%u Return:%u \n", #fn, ulPara1, ulPara2, ulPara3, ulPara4, ulRet)

#define IMS_NIC_TCPIP_INPUT_STR_LOG4(str, fn, szStringPara1, szStringPara2, ulPara3, ulPara4, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%s para2:%s para3:%u para4:%u Return:%u \n", #fn, szStringPara1, szStringPara2, ulPara3, ulPara4, ulRet)

/* 转定义LogMsg函数，在阻塞性操作中使用 */
#define IMS_NIC_ERROR_LOG_MSG(ModuleId, fmt)                                  LogPrint(fmt)
#define IMS_NIC_ERROR_LOG_MSG1(ModuleId, fmt,Para1)                           LogPrint1((fmt), (Para1))
#define IMS_NIC_ERROR_LOG_MSG2(ModuleId, fmt,Para1,Para2)                     LogPrint2((fmt), (Para1), (Para2))
#define IMS_NIC_ERROR_LOG_MSG3(ModuleId, fmt,Para1,Para2,Para3)               LogPrint3((fmt), (Para1), (Para2), (Para3))
#define IMS_NIC_ERROR_LOG_MSG4(ModuleId, fmt,Para1,Para2,Para3,Para4)         LogPrint4((fmt), (Para1), (Para2), (Para3), (Para4))

#define IMS_NIC_IP6_ADDR_XOR_ADDRESSES(m_pstIP6Addr1, m_pstIP6Addr2, m_stIP6AddrRes)\
{\
    m_stIP6AddrRes.s6_addr32[0] = m_pstIP6Addr1->s6_addr32[0]\
                                                ^ m_pstIP6Addr2->s6_addr32[0];\
    m_stIP6AddrRes.s6_addr32[1] = m_pstIP6Addr1->s6_addr32[1]\
                                                ^ m_pstIP6Addr2->s6_addr32[1];\
    m_stIP6AddrRes.s6_addr32[2] = m_pstIP6Addr1->s6_addr32[2]\
                                                ^ m_pstIP6Addr2->s6_addr32[2];\
    m_stIP6AddrRes.s6_addr32[3] = m_pstIP6Addr1->s6_addr32[3]\
                                               ^ m_pstIP6Addr2->s6_addr32[3];\
}

#define IMS_NIC_IN6_IS_MULTICAST(a)   ((a)->s6_addr[0] == 0xff)

#define IMS_NIC_IN6_IS_LINKLOCAL(a)   \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))

#define IMS_NIC_IN6_IS_UNSPECIFIED(a)   \
        (((a)->s6_addr32[0] == 0) && ((a)->s6_addr32[1] == 0) && \
          ((a)->s6_addr32[2] == 0) && ((a)->s6_addr32[3] == 0))

#define IMS_NIC_MAP_MAC_INTERFACEID(enaddr , interfaceid) \
{ \
   (interfaceid)[0] = (enaddr)[0] | (VOS_UINT8)0x02; \
   (interfaceid)[1] = (enaddr)[1];  \
   (interfaceid)[2] = (enaddr)[2];  \
   (interfaceid)[3] = (VOS_UINT8)  0xff; \
   (interfaceid)[4] = (VOS_UINT8)  0xfe; \
   (interfaceid)[5] = (enaddr)[3]; \
   (interfaceid)[6] = (enaddr)[4]; \
   (interfaceid)[7] = (enaddr)[5]; \
}

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum IMS_NIC_MODEM_ID_ENUM
{
    IMS_NIC_MODEM_ID_0 = 0,

    IMS_NIC_MODEM_ID_BUTT       /* 考虑到目前副卡不需要IMS网卡，故暂时设置BUTT值为1*/
};

typedef VOS_UINT16 IMS_NIC_MODEM_ID_ENUM_UINT16;

/* IMS虚拟网卡统计枚举 */
enum IMS_NIC_STATS_INFO_ENUM
{
    IMS_NIC_STATS_DL_RCV_IPV4_PKT = 0,                                  /* IMS虚拟网卡收到下行IPV4数据的个数 */
    IMS_NIC_STATS_DL_RCV_IPV6_PKT,                                      /* IMS虚拟网卡收到下行IPV6数据的个数 */
    IMS_NIC_STATS_DL_SEND_PKT,                                          /* IMS虚拟网卡发送下行数据的个数 */
    IMS_NIC_STATS_DL_RCV_BYTES,                                         /* 下行收到数据包byte数 */
    IMS_NIC_STATS_DL_RCV_ERR_PKT,                                       /* 收到错误数据包的个数(非ipv4、ipv6包) */
    IMS_NIC_STATS_DL_INPUT_NULL_PTR,                                    /* 输入数据为空的次数 */
    IMS_NIC_STATS_DL_RCV_DATA_LEN_ERR,                                  /* IMS虚拟网卡收到下行数据长度错误的个数 */

    IMS_NIC_STATS_UL_RCV_IPV4_PKT,                                      /* IMS虚拟网卡收到上行IPV4数据的个数 */
    IMS_NIC_STATS_UL_RCV_IPV6_PKT,                                      /* IMS虚拟网卡收到上行IPV6数据的个数 */
    IMS_NIC_STATS_UL_SEND_PKT,                                          /* IMS虚拟网卡上行发送给CDS数据的个数 */
    IMS_NIC_STATS_UL_SEND_BYTES,                                        /* 上行发送的数据包byte数 */
    IMS_NIC_STATS_UL_RCV_ERR_PKT,                                       /* 收到错误数据包的个数(非ipv4、ipv6包) */
    IMS_NIC_STATS_UL_RCV_ARP_PKT,                                       /* 收到ARP包的个数 */
    IMS_NIC_STATS_UL_INPUT_NULL_PTR,                                    /* 输入数据为空的次数 */
    IMS_NIC_STATS_UL_RCV_DATA_LEN_ERR,                                  /* IMS虚拟网卡收到上行数据长度错误的个数 */
    IMS_NIC_STATS_UL_CB_FUN_NOT_REG,                                    /* IMS虚拟网卡上行数据发送函数没有注册次数 */
    IMS_NIC_STATS_UL_CALL_CB_FUN_FAIL,                                  /* 调用CDS注册的回调函数失败次数 */
    IMS_NIC_STATS_UL_PKT_MEM_SEG,                                       /* 数据包内存分段 */

    IMS_NIC_STATS_CFG_DNS_SERVER_FULL,
    IMS_NIC_STATS_CFG_INPUT_NULL_PTR,                                   /* 配置指针为空 */
    IMS_NIC_STATS_CFG_ADD_MODEM_ID_ERR,                                 /* 配置时传入的modem id匈牙利 */
    IMS_NIC_STATS_CFG_DEL_MODEM_ID_ERR,                                 /* 删除配置传入的ModemId错误 */
    IMS_NIC_STATS_CFG_ADD_RAB_ID_ERR,                                   /* 增加配置输入的RABID错误 */
    IMS_NIC_STATS_CFG_DEL_RAB_ID_ERR,                                   /* 删除输入的RABID错误 */
    IMS_NIC_STATS_GET_CLUSTER_FAIL,                                     /* 获取Cluster失败次数 */
    IMS_NIC_STATS_GET_CLBLK_FAIL,                                       /* 获取clBlk失败 */
    IMS_NIC_STATS_GET_MBLK_FAIL,
    IMS_NIC_STATS_MBLK_COPY_ERR,                                        /* 拷贝Mblk内存失败 */
    IMS_NIC_STATS_NOT_INITED_ERR,                                       /* 虚拟网卡没有初始化 */
    IMS_NIC_STATS_SYS_CALL_FAIL,                                        /* 系统调用失败 */
    IMS_NIC_STATS_FIND_DEV_FAIL,                                        /* 查找设备失败 */
    IMS_NIC_STATS_NO_CFGED_PDN,
    IMS_NIC_STATS_CFG_ADD_NO_PDN,
    IMS_NIC_STATS_CFG_DEL_NO_PDN,
    IMS_NIC_STATS_MODEM_ID_ERR_OTHER,
    IMS_NIC_STATS_MODEM_ID_ERR_IN_REG_CB,
    IMS_NIC_STATS_MODE_ID_ERR_IN_DL_PROC,
    IMS_NIC_STATS_MODE_ID_ERR_IN_UL_PROC,
    IMS_NIC_STATS_MTU_INVALID,
    IMS_NIC_STATS_INVALID_IPV6_PREFIX_LEN,
    IMS_NIC_STATS_MTU_CONFIG_FAIL,                                      /* 配置MTU失败 */
    IMS_NIC_STATS_PORT_CONFIG_INVALID,                                  /* 配置端口参数非法 */
    IMS_NIC_STATS_NETIF_RESET_FAIL,                                     /* 网卡释放失败 */
    IMS_NIC_STATS_DEL_IPV4_ADDR_FAIL,                                   /* 删除IPV4地址失败 */
    IMS_NIC_STATS_DEL_IPV6_ADDR_FAIL,                                   /* 删除IPV6地址失败 */
    IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL,                            /* 通过接口索引获取接口名失败 */
    IMS_NIC_STATS_ADD_IPV4_ADDR_FAIL,                                   /* 新增IPV4地址失败 */
    IMS_NIC_STATS_ADD_IPV6_ADDR_FAIL,                                   /* 新增IPV6地址失败 */
    IMS_NIC_STATS_CONFIG_IPV4_ROUTE_FAIL,                               /* 配置IPV4路由失败 */
    IMS_NIC_STATS_CONFIG_IPV6_ROUTE_FAIL,                               /* 配置IPV6路由失败 */
    IMS_NIC_STATS_COPY_DATA_FROM_MBUF_FAIL,                             /* 从MBUF拷贝数据失败 */
    IMS_NIC_STATS_RESUME_IF_FAIL,                                       /* 接口恢复失败 */
    IMS_NIC_STATS_SET_STATIC_ARP_FAIL,                                  /* 设置静态ARP失败 */
    IMS_NIC_STATS_SET_STATIC_ND_FAIL,                                   /* 设置静态ND表项失败 */
    IMS_NIC_STATS_ENABLE_HOST_FAIL,                                     /* 使能主机模式失败 */
    IMS_NIC_STATS_ISLUP_SUCC,                                           /* 网卡up成功 */
    IMS_NIC_STATS_ISLUP_FAIL,                                           /* 网卡up失败 */
    IMS_NIC_STATS_MATCH_IPV6_ADDR_SUCC,                                 /* 获取IPV6地址成功 */
    IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL,                                 /* 获取IPV6地址失败 */
    IMS_NIC_STATS_LOCAL_IPV6_ADDR_SUCC,                                 /* 获取Local地址成功 */
    IMS_NIC_STATS_LOCAL_IPV6_ADDR_FAIL,                                 /* 获取Local地址失败 */
    IMS_NIC_STATS_HAVE_IPV6_ADDR_SUCC,                                  /* 是否有地址成功 */
    IMS_NIC_STATS_HAVE_IPV6_ADDR_FAIL,                                  /* 是否有地址失败 */

    IMS_NIC_STATS_BUTT,
};
typedef VOS_UINT32 IMS_NIC_STATS_INFO_ENUM_UINT32;

enum IMS_NIC_DNS_STATE_ENUM
{
    IMS_NIC_DNS_CFGED                           = 0,
    IMS_NIC_DNS_NOT_CFGED,
    IMS_NIC_DNS_STATE_BUTT
};
typedef VOS_UINT32 IMS_NIC_DNS_STATE_ENUM_UINT32;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : IMS_NIC_SINGLE_PDN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 某个承载上IMS虚拟网卡PDN信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo            : 1;                        /* 如果为1则代表aucIpV4Addr有效 */
    VOS_UINT32                          bitOpIpv6PdnInfo            : 1;                        /* 如果为1则代表aucIpV6Addr有效 */
    VOS_UINT32                          bitOpIpv4DnsPrimCfged       : 1;                     /* IMS NIC内部填写，记录aucDnsPrimAddr是否配置成功 */
    VOS_UINT32                          bitOpIpv4DnsSecCfged        : 1;                     /* IMS NIC内部填写，记录aucDnsSecAddr是否配置成功 */
    VOS_UINT32                          bitOpIpv6DnsPrimCfged       : 1;                     /* IMS NIC内部填写，记录aucDnsPrimAddr是否配置成功 */
    VOS_UINT32                          bitOpIpv6DnsSecCfged        : 1;                     /* IMS NIC内部填写，记录aucDnsSecAddr是否配置成功 */

    VOS_UINT32                          bitOpSpare                  : 26;

    VOS_UINT8                           aucDnsFlag[IMS_NIC_DNS_NUM_ADAPTER];         /* 如果为1则代表配置了DNS服务器,分别对应主、第二、第三和第四DNS服务器 */

    IMS_NIC_IPV4_PDN_INFO_STRU          stIpv4PdnInfo;
    IMS_NIC_IPV6_PDN_INFO_STRU          stIpv6PdnInfo;
}IMS_NIC_SINGLE_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_SINGLE_DNS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单个DNS配置信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cDnsRef;                                   /* DNS服务器的引用计数 */
    VOS_UINT8                           ucIpAddrLen;                                /* 存储的DNS服务器IP地址长度 */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucDnsAddr[IMS_NIC_IP_ADDR_MAX_LENGTH];     /* DNS服务器地址 */
}IMS_NIC_SINGLE_DNS_INFO_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_DNS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DNS配置信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDnsServerCnt;                                     /* 当前配置DNS服务器的个数 */
    VOS_UINT8                           aucReserved[3];
    IMS_NIC_SINGLE_DNS_INFO_STRU        astImsNicDnsInfo[IMS_NIC_MAX_DNS_SERVER_NUM];       /* DNS配置信息，分别对应主、第一、第二、第三DNS服务器 */
}IMS_NIC_DNS_INFO_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_PDN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 所有承载上IMS虚拟网卡PDN信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_INT                             iPdnCfgCnt;
    IMS_NIC_DNS_INFO_STRU               stImsNicDnsInfo;                                /* 当前DNS服务器配置信息 */
    IMS_NIC_SINGLE_PDN_INFO_STRU        astImsNicPdnInfo[IMS_NIC_RAB_ID_MAX_NUM];       /* 各Rab上PDN激活信息 */
}IMS_NIC_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_DEV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于控制设备的主数据结构
*****************************************************************************/
typedef struct
{
    VOS_INT                   unit;                                             /* 设备的unit号 */                                      /* 用于获取网络缓存 */
    VOS_UINT8                 aucSendBuf[IMS_NIC_UL_SEND_BUFF_SIZE];            /* 上行发送缓存,1520字节*/
} IMS_NIC_DEV_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_ETH_HEADER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 以太网头结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 aucEtherDhost[IMS_NIC_ETHER_ADDR_LEN];            /* 目的以太网地址 */
    VOS_UINT8                 aucEtherShost[IMS_NIC_ETHER_ADDR_LEN];            /* 源以太网地址 */
    VOS_UINT16                usEtherType;                                      /* 包类型 */
}IMS_NIC_ETH_HEADER_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_ELEMENT_TAB_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS虚拟网卡信息
*****************************************************************************/
typedef struct
{
    IMS_NIC_ETH_HEADER_STRU             stIpv4Ethhead;                          /* IPV4以太网头 */
    IMS_NIC_ETH_HEADER_STRU             stIpv6Ethhead;                          /* IPV6以太网头 */
}IMS_NIC_ELEMENT_TAB_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_STATS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS虚拟网卡统计信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32              aulStats[IMS_NIC_STATS_BUTT];
}IMS_NIC_STATS_INFO_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_ENTITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS虚拟网卡实体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulImsNicInitFlag;                       /* IMS虚拟网卡初始化标记 */
    VOS_UINT32                          ulIfIndex;                              /* 接口索引 */
    IMS_NIC_SEND_UL_DATA_FUNC           pUlDataSendFunc;                        /* IMS虚拟网卡上行数据发送函数 */
    IMS_NIC_PDN_INFO_STRU               stImsNicPdnInfo;                        /* IMS虚拟网卡PDN配置信息 */
    IMS_NIC_STATS_INFO_STRU             stImsNicStatsInfo;                      /* IMS虚拟网卡统计信息 */
    VOS_UINT8                           aucIpV6LinkLocalAddr[IMS_NIC_IPV6_ADDR_LENGTH]; /* IPv6链路本地地址 */
}IMS_NIC_ENTITY_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_MANAGE_TBL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS虚拟网卡管理结构
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            ucImsNicName[IMS_NIC_IFNAMSIZ];                 /* 网卡名称 */
    IMS_NIC_ELEMENT_TAB_STRU            astImsNicElementTbl[IMS_NIC_MODEM_ID_BUTT];     /* IMS虚拟网卡基本信息表 */
}IMS_NIC_MANAGE_TBL_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16 usMsgId;
    VOS_UINT8  aucRsv[2];
    VOS_UINT32 ulPara1;
    VOS_UINT32 ulPara2;
    VOS_UINT8  aucData[4];
}IMS_NIC_MNTN_TRACE_MSG_STRU;

typedef struct
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          enLevel;
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_INT32                           alPara[IMS_NIC_LOG_PARAM_MAX_NUM];
}IMS_NIC_LOG_RECORD_STRU;

typedef struct
{
    VOS_UINT32                          ulCnt;                  /* 实际缓存的打印记录数目 */
    IMS_NIC_LOG_RECORD_STRU             astData[IMS_NIC_LOG_RECORD_MAX_NUM];
}IMS_NIC_LOG_ENT_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    VOS_UINT16                          usMsgType;      /* _H2ASN_Skip */
    VOS_UINT16                          usTransId;
    IMS_NIC_LOG_ENT_STRU                stLogMsgCont;   /* LOG_MSG内容 */
}IMS_NIC_TRACE_LOG_MSG_STRU;


/*****************************************************************************
 结构名    : IMS_NIC_CTX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS虚拟网卡上下文
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMtu;                                  /* MTU值,默认1280，外部模块可以通过接口修改 */
    VOS_SEM                             ulInitLogMutexSem;
    VOS_SEM                             ulSaveLogMutexSem;
    IMS_NIC_SEND_UL_DATA_FUNC           pTmpSendFunc[IMS_NIC_MODEM_ID_BUTT];    /* 记录CDS注册上行回调函数 */
    IMS_NIC_LOG_ENT_STRU                stLogEnt;
}IMS_NIC_CTX_STRU;

typedef  struct  tagImsNicIp6InterfaceId
{
    union
    {
        VOS_UINT8       u6_InterfaceId8[8];
        VOS_UINT16      u6_InterfaceId16[4];
        VOS_UINT32      u6_InterfaceId32[2];
    } u6_InterfaceId;
}IMS_NIC_INTERFACEID_S;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern IMS_NIC_ENTITY_STRU                      g_astImsNicEntity[IMS_NIC_MODEM_ID_BUTT];        /* IMS虚拟网卡实体信息 */
extern const IMS_NIC_MANAGE_TBL_STRU            g_stImsNicManageTbl;
extern IMS_NIC_CTX_STRU                         g_stImsNicCtx;
extern IMS_NIC_DEV_STRU                         g_astImsNicDev[IMS_NIC_MODEM_ID_BUTT];

/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if ((VOS_OS_VER == VOS_RTOSCK) || ((VOS_OS_VER == VOS_WIN32) && (VOS_PC_TEST == VOS_RTOSCK)))

#else
extern IP_PUBLIC int    ipcom_run_cmd(char *cmd_str);

#endif

VOS_UINT32 IMS_NIC_SetSocketPort
(
    VOS_UINT16                          usMinPort,
    VOS_UINT16                          usMaxPort,
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID    IMS_NIC_SetDefaultRoute(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID IMS_NIC_ResetAll(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID IMS_NIC_DnsConfigtoIpStack
(
    VOS_UINT8                           ucIpAddrLen,
    VOS_UINT8                           ucDnsIndx,
    VOS_UINT8                          *pucIpAddr
);

VOS_VOID IMS_NIC_DnsDeltoIpStack
(
    VOS_UINT32                          ulIndx,
    VOS_UINT8                           ucRabId,
    IMS_NIC_DNS_INFO_STRU              *pstDnsInfo
);

VOS_VOID   IMS_NIC_PdnInfoDelIpv4(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID   IMS_NIC_PdnInfoDelIpv6(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID   IMS_NIC_ConfigIpv4Addr
(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                          *pucIpAddr
);

VOS_VOID   IMS_NIC_ConfigIpv6Addr
(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT32                          ulBitPrefixLen
);

VOS_UINT32 IMS_NIC_Delete (MODEM_ID_ENUM_UINT16 enModemId);

VOS_UINT32 IMS_NIC_Init (MODEM_ID_ENUM_UINT16 enModemId);

#endif  /*FEATURE_ON == FEATURE_IMS*/

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of ImsNicInterface.h */


