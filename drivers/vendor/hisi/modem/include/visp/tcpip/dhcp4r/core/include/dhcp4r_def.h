/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_def.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-11
*        Author: LY(57500)
*   Description: DHCP4R模块的宏和枚举定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-11  LY(57500)     Create the first version.
*
*******************************************************************************/

#ifndef _DHCP4R_DEF_H_
#define _DHCP4R_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 使能配置模式: 0 - 接口模式，1 - 全局模式 */
#define DHCP4R_ENABLE_INTERFACE     0
#define DHCP4R_ENABLE_GLOBAL        1
#define DHCP4R_ENABLE_AUTO           2

/* 使能去使能   */
#define DHCP4R_DISABLE              0
#define DHCP4R_ENABLE               1

/* 82选项相关宏定义 */
#define DHCP4R_OPTION_82            82
#define DHCP4R_82_SUB_MINLEN        1       /* 子选项最小长度   */
#define DHCP4R_82_CIRCUIT_ID        0x1     /* 子选项1 CODE     */
#define DHCP4R_82_REMOTE_ID         0x2     /* 子选项2 CODE     */

/* 可能生成的82选项的最大长度; 每个子选项有1字节code和1字节Len,82选项另外需要1字节code和1字节Len */
#define DHCP4R_82_TOTAL_LEN  (DHCP4R_82_SUB_NUM * (DHCP4R_82_SUB_MAXLEN + 2) + 2)

/* 最大中继跳数限制 */
#define DHCP4R_HOPS_MAX             16
/* 中继模式 */
#define DHCP4R_FORWORD_CYCLE        0x0     /* 分担方式 */
#define DHCP4R_FORWORD_BROADCAST    0x1     /* 广播方式 */

/* 公共配置信息(最大hops,中继方式,TOS)的默认值 */
#define DHCP4R_HOPS_DEFAULT         16
#define DHCP4R_FORWORD_DEFAULT      DHCP4R_FORWORD_CYCLE
#define DHCP4R_TOS_DEFAULT          0

/* relay配置标志    */
#define DHCP4R_FLAG_ENABLE          0x01    /* 已使能           */
#define DHCP4R_FLAG_SERVER          0x02    /* 已配置中继地址   */
#define DHCP4R_FLAG_OPTION82        0x04    /* 已配置82选项     */
#define DHCP4R_FLAG_OPT82MODE       0x08    /* 已配置82选项处理模式 */
/* 设置清除配置标记 */
#define DHCP4R_SET_FLAG(SetFlag, FlagMask)      ((SetFlag) |= (FlagMask))
#define DHCP4R_CLEAR_FLAG(SetFlag, FlagMask)    ((SetFlag) &= ~(FlagMask))

/* relay接收发送报文缓冲区长度 */
#define DHCP4R_UDPBUF_MAXLEN        2048

/* debug开关 */
#define DHCP4R_DEBUG_PAKCET         0x1     /* packet调试开关   */
#define DHCP4R_DEBUG_ERROR          0x2     /* error调试开关    */
#define DHCP4R_DEBUG_ALL            0x3     /* 前两者都打开     */

/* DHCP4R模块事件位 */
/* 配置消息使用同一个配置消息队列和相同事件，但通过不同的消息类型来区分  */
#define DHCP4R_EV_CNTRL             0x1     /* 其他模块通知DHCP4R事件   */

#define DHCP4R_MSG_IFDEL            0x1     /* 以太模块删除接口消息     */
#define DHCP4R_MSG_CRTSKT           0x2     /* 创建relay socket消息     */
#define DHCP4R_MSG_VRFDEL           0x3     /* VRF删除消息              */
#define DHCP4R_MSG_CLSSKT           0x4     /* 删除relay socket消息     */



/* 用户配置接口中传入的接口索引值在当前配置模式下是否有效
 * 接口配置模式(0),接口索引必须 非0
 * 全局配置模式(1),接口索引必须 为0
 * 宏值为1表示传入索引与配置模式冲突
 */
#define DHCP4R_MODE_NO_MATCH(mode, ifIndex)  (((!(mode))&&(!(ifIndex))) || ((mode)&&(ifIndex)))

/* 用于在解读DHCP报文时检查指针操作是否越界，每次读取操作前都要调用 */
#define  DHCP4R_MSG_BOUNDCHECK(pucOptRead, pucStart, length) \
    (((UINTPTR)(pucOptRead) > (UINTPTR)(pucStart) + (length)) ? (VOS_ERR) : (VOS_OK))

/* 定义dhcp报文流方向 */
enum enDHCPTxRx
{
    DHCP_FROM_CLIENT = 1,   /* 1 从client接收 */
    DHCP_TO_CLIENT,         /* 2 向client发送 */
    DHCP_FROM_SERVER,       /* 3 从server接收 */
    DHCP_TO_SERVER,         /* 4 向server发送 */
    /* Add by y00176567/z00171897, at 2011-06-28. 修改原因: 支持UTRP自启动 */
    DHCP_TO_RELAY,         /* 5 二级Relay */
};

/* 判断是否非法dhcp消息类型 */
#define DHCP_IS_BADTYPE(msgType) (((msgType) < DHCP4C_DHCPDISCOVER) || ((msgType) > DHCP4C_DHCPINFORM))

/* 定义非法dhcp消息类型宏 */
#define DHCP_BAD_MSG    0

/* 定义报文统计类型,为区别DHCPC报文类型这里定义从16开始 */
enum enDHCPERRPKTTYPE
{
    /* 定义ulRxServerPkt报文统计类型0x10 */
    DHCP4R_RXS_MSG = 0x10,
    /* 定义ulTxServerPkt报文统计类型0x11 */
    DHCP4R_TXS_MSG,
    /* 定义ulRxClientPkt报文统计类型0x12 */
    DHCP4R_RXC_MSG,
    /* 定义ulTxClientUnicast报文统计类型0x13 */
    DHCP4R_TXCU_MSG,
    /* 定义ulTxClientBroadcast报文统计类型0x14 */
    DHCP4R_TXCB_MSG,
    /* 定义ulTxClientPkt报文统计类型0x15 */
    DHCP4R_TXC_MSG,
    /* 定义ulBorrowDropPkt报文统计类型0x16 */
    DHCP4R_BD_MSG,
    /* 定义ulAdd82TooLongPkt报文统计类型0x17 */
    DHCP4R_ATL_MSG,
    /* Add by y00176567/z00171897, at 2011-06-28. 修改原因: 支持UTRP自启动 */
    /* 定义二级Relay报文统计类型0x18 */
    DHCP4R_TXR_MSG,
};

/* 主机字节序, DHCP OPTION开始的四个字节为魔术字, 用于校验 */
#define DHCP4R_MAGICCOOKIE  0x63825363  

/* DHCP4R模块使用的SID统一在此定义 */

#define SID_COMP_DHCP4R_DLL_S      1  /* DLL_S */
#define SID_COMP_DHCP4R_CFG_S      2  /* DHCP4R_CFG_NODE_S */
#define SID_COMP_DHCP4R_DBG_S      3  /* DHCP4R_DEBUG_NODE_S */
    
/* end of SID */

/* 定义公网VRF索引宏为IP_L3VPN_VRF_INDEX_PUBLIC*/
#define DHCP4R_VRF_INDEX_PUBLIC IP_L3VPN_VRF_INDEX_PUBLIC
/* 定义特殊VRF索引宏为IP_L3VPN_VRF_RESERVE_DCN*/
#define DHCP4R_VRF_INDEX_RESERVE_DCN IP_L3VPN_VRF_RESERVE_DCN

/* 定义最大VRF索引宏为IP_L3VPN_VRF_INDEX_MAX_DEFAULT*/
#define DHCP4R_VRF_INDEX_MIN           1
#define DHCP4R_VRF_INDEX_MAX_DEFAULT   1
#define DHCP4R_VRF_INDEX_MAX g_ulDhcp4rMaxVrfIndex
#define DHCP4R_VRF_POOL_SIZE (g_ulDhcp4rMaxVrfIndex + 1)


#define DHCP4R_VRF_INVALIDVRF(ulVrfIndex) ((ulVrfIndex) > DHCP4R_VRF_INDEX_MAX)

#define DHCP4R_PACKET_PRO_COUNT 40
#define DHCP4R_PACKET_MAX_PRO_COUNT 100
#define DHCP4R_DELAY_TIME 40
#define DHCP4R_MAX_DELAY_TIME 100

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _DHCP4R_DEF_H_    */

