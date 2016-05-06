
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "RnicEntity.h"
#include "RnicDebug.h"
#include "RnicCtx.h"
#include "RnicDev.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_RNIC_DEV_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
*****************************************************************************/
/* 将网卡的操作进行静态映射 */
#if (VOS_OS_VER == VOS_WIN32)
    static struct net_device_ops rnic_ops;
#else
    static const struct net_device_ops rnic_ops = {
           .ndo_stop                = RNIC_StopNetCard,
           .ndo_open                = RNIC_OpenNetCard,
           .ndo_start_xmit          = RNIC_StartXmit,
           .ndo_set_mac_address     = RNIC_SetMacAddress,
           .ndo_change_mtu          = RNIC_ChangeMtu,
           .ndo_tx_timeout          = RNIC_ProcTxTimeout,
           .ndo_do_ioctl            = RNIC_Ioctrl,
           .ndo_get_stats           = RNIC_GetNetCardStats,
    };
#endif

#if (FEATURE_ON == FEATURE_RMNET_CUSTOM)
#define RNIC_DEV_NAME_PREFIX            "eth_x"
#else
#define RNIC_DEV_NAME_PREFIX            "rmnet"
#endif
const RNIC_NETCARD_ELEMENT_TAB_STRU           g_astRnicManageTbl[RNIC_NET_ID_MAX_NUM] =
{
    {
#if (FEATURE_ON == FEATURE_RMNET_CUSTOM)
      "",
#else
      "0",
#endif
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x06}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x01}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x06}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x01}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_0, {0, 0, 0, 0, 0}},

    { "1",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x07}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x02}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x07}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x02}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_1, {0, 0, 0, 0, 0}},

    { "2",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x08}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x03}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x08}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x03}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_2, {0, 0, 0, 0, 0}},

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    { "3",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x09}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x04}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x09}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x04}, 0xDD86, {0, 0}},
      MODEM_ID_1, RNIC_RMNET_ID_3, {0, 0, 0, 0, 0}},

    { "4",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0a}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x05}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0a}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x05}, 0xDD86, {0, 0}},
      MODEM_ID_1, RNIC_RMNET_ID_4, {0, 0, 0, 0, 0}},

#if  (MULTI_MODEM_NUMBER == 3)
    { "5",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0b}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x06}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0b}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x06}, 0xDD86, {0, 0}},
      MODEM_ID_2, RNIC_RMNET_ID_5, {0, 0, 0, 0, 0}},

    { "6",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0c}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x07}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0c}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x07}, 0xDD86, {0, 0}},
      MODEM_ID_2, RNIC_RMNET_ID_6, {0, 0, 0, 0, 0}},
#endif /* #if (MULTI_MODEM_NUMBER == 3) */

#endif

    {
      "_ims",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0d}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x08}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0d}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x08}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_VT, {0, 0, 0, 0, 0}},

};


/******************************************************************************
   5 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : RNIC_StopNetCard
 功能描述  : RNIC被关闭时的处理
 输出参数  : pstNetDev:网卡设备指针
 输出参数  : 无
 返 回 值  : VOS_INT:RNIC_OK, RNIC_ERROR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
VOS_INT RNIC_StopNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /* 获取网卡私有数据 */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    /* 使用netif_stop_queue()停止网卡的数据收发 */
    netif_stop_queue(pstNetDev);

    /* 将私有数据中的网卡状态标志置为关闭 */
    pstPriv->enStatus = RNIC_NETCARD_STATUS_CLOSED;

    return 0;
}

/*****************************************************************************
 函 数 名  : RNIC_OpenNetCard
 功能描述  : RNIC被打开时的处理
 输入参数  : pstNetDev:网卡设备指针
 输出参数  : 无
 返 回 值  : VOS_INT:RNIC_OK, RNIC_ERR, RNIC_BUSY
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
VOS_INT RNIC_OpenNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /* 获取网卡私有数据 */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    /* 启动网卡接收数据 */
    netif_start_queue(pstNetDev);

    /* 将私有数据中的网卡状态标志置为打开 */
    pstPriv->enStatus = RNIC_NETCARD_STATUS_OPENED;

    return 0;
}

/*****************************************************************************
 函 数 名  : RNIC_StartXmit
 功能描述  : RNIC发送数据时的处理过程
 输入参数  : pstSkb   :SKBUF数据首地址
             pstNetDev:网卡设备指针
 输出参数  : 无
 返 回 值  : netdev_tx_t:NETDEV_TX_OK
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
 2.日    期   : 2012年5月31日
   作    者   : A00165503
   修改内容   : DTS2012053004651: PS业务中丢网, 导致A核数传内存耗尽, 导致
                192.168.1.1 ping不通
 3.日    期   : 2012年6月20日
   作    者   : A00165503
   修改内容   : DTS2012061904440: 增加用户面时延统计
 4.日    期   : 2012年8月30日
   作    者   : l60609
   修改内容   : AP适配项目：先判断输入参数是否为空，再判断网卡是否有效
 5.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
netdev_tx_t RNIC_StartXmit(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev
)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;

    pstPriv     = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    pstNetCntxt = RNIC_GetNetCntxtByRmNetId(pstPriv->enRmNetId);
    if (VOS_NULL_PTR == pstNetCntxt)
    {
        IMM_ZcFree(pstSkb);
        RNIC_DBG_NET_TX_RMNETID_ERR_NUM(1);
        return NETDEV_TX_OK;
    }

    /* 按MODEM类型分发处理数据 */
    RNIC_ProcessTxDataByModemType(pstNetCntxt, pstSkb);

    return NETDEV_TX_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_SetMacAddress
 功能描述  : RNIC的重新设置MAC地址的处理
 输入参数  : pstNetDev:网卡设备指针
             pMacAddr :MAC地址
 输出参数  : 无
 返 回 值  : VOS_INT:RNIC_OK, RNIC_ADDR_INVALID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
VOS_INT RNIC_SetMacAddress(
    struct net_device                  *pstNetDev,
    VOS_VOID                           *pMacAddr
)
{
    struct sockaddr                    *pstAddr;
    VOS_INT                             lValid;

    /* 类型转换 */
    pstAddr = (struct sockaddr *)pMacAddr;

    /* MAC地址为无效值 */
    lValid = is_valid_ether_addr((VOS_UINT8 *)pstAddr->sa_data);
    if (VOS_FALSE == lValid)
    {
        RNIC_DEV_ERR_PRINTK("RNIC_SetMacAddress: Ether addr is invalid!");
        return -EINVAL;
    }

    /* 将MAC地址赋值到网卡 */
    memcpy(pstNetDev->dev_addr, pstAddr->sa_data, pstNetDev->addr_len);

    return 0;
}

/*****************************************************************************
 函 数 名  : RNIC_ChangeMtu
 功能描述  : RNIC重新设置MTU大小
 输入参数  : pstNetDev:网卡设备指针
             lNewMtu  :MTU值
 输出参数  : 无
 返 回 值  : VOS_INT:RNIC_OK, RNIC_ERROR, RNIC_OUT_RANGE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
VOS_INT RNIC_ChangeMtu(
    struct net_device                  *pstNetDev,
    VOS_INT                             lNewMtu
)
{
    /* new_mtu长度不在有效范围内 */
    if (lNewMtu > RNIC_MAX_PACKET)
    {
        RNIC_DEV_ERR_PRINTK("RNIC_ChangeMtu: Mtu out of range!");
        return -EINVAL;
    }

    /* 网卡mtu完成赋值 */
    pstNetDev->mtu = (VOS_UINT)lNewMtu;

    return 0;
}

/*****************************************************************************
 函 数 名  : RNIC_Tx_Timeout
 功能描述  : RNIC发送超时处理函数,目前认为不会出现发送超时情况,暂不作任何处理
             留到以后拓展使用
 输入参数  : pstNetDev:网卡设备指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID RNIC_ProcTxTimeout(
    struct net_device                  *pstNetDev
)
{
    return;
}

/*****************************************************************************
 函 数 名  : RNIC_Ioctrl
 功能描述  : RNIC的ioctrl处理,目前没有特殊的ioctrl,留作以后扩展
 输入参数  : pstNetDev:网卡设备指针
             pstIfr   :用户请求
             lCmd     :操作命令
 输出参数  : 无
 返 回 值  : 操作不支持  RNIC_NOTSUPP
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
VOS_INT RNIC_Ioctrl(
    struct net_device                  *pstNetDev,
    struct ifreq                       *pstIfr,
    VOS_INT                             lCmd
)
{
    return -EOPNOTSUPP;
}

/*****************************************************************************
 函 数 名  : RNIC_GetNetCardStats
 功能描述  : 获取RNIC网卡统计信息
 输入参数  : pstNetDev:网卡设备指针
 输出参数  : 无
 返 回 值  : net_device_stats
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
struct net_device_stats *RNIC_GetNetCardStats(
    struct net_device                  *pstNetDev
)

{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /* 获取私有数据 */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    /* 将设备的统计信息返回 */
    return &pstPriv->stStats;
}

/*****************************************************************************
 函 数 名  : RNIC_DeInitNetCard
 功能描述  : RNIC的去注册处理
 输入参数  : pNetDev:网卡设备指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
 2.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_VOID RNIC_DeinitNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;

    /* 获取网卡私有数据 */
    pstPriv     = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);
    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(pstPriv->enRmNetId);

    /* 关闭载波 */
    netif_carrier_off(pstNetDev);

    /* 停止网卡接收数据 */
    netif_stop_queue(pstNetDev);

    /* 去注册网卡设备 */
    unregister_netdev(pstNetDev);

    /* 释放网卡设备 */
    free_netdev(pstNetDev);

    /* 清除网卡设备信息 */
    pstNetCntxt->pstPriv = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_InitNetCard
 功能描述  : RNIC网卡被初始化时调用的函数，完成RNIC初始化相关处理
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : VOS_INT:RNIC_NOMEM, RNIC_STATE, RNIC_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : 范晶
   修改内容   : 新生成函数
 2.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_INT __init RNIC_InitNetCard(VOS_VOID)
{
    struct net_device                  *pstDev      = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    VOS_INT                             lRegRst;
    VOS_UINT8                           ucIndex;

    printk("RNIC_InitNetCard: entry, %u", VOS_GetSlice());

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /* 初始化网卡私有信息 */
        pstNetCntxt = RNIC_GET_SPEC_NET_CTX(ucIndex);
        pstNetCntxt->pstPriv = VOS_NULL_PTR;

        /* 创建网卡设备netdev和私有数据 */
        /* alloc_etherdev这个接口分配了net_device和 RNIC_NETCARD_DEV_INFO_STRU两个接口的内存
           RNIC_NETCARD_DEV_INFO_STRU结构挂接在net_device的后面 */
        pstDev = alloc_etherdev(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        if (VOS_NULL_PTR == pstDev)
        {
            RNIC_DEV_ERR_PRINTK("RNIC_InitNetCard: net ptr is Null!");
            continue;
        }

        /* 给设备配置MAC地址,以后需要填固定值 */
        memcpy(pstDev->dev_addr, RNIC_GET_DST_MAC_ADDR(ucIndex), RNIC_MAC_ADDR_LEN);

        /* 设置默认的MTU值 */
        pstDev->mtu = RNIC_DEFAULT_MTU;

#if (VOS_OS_VER == VOS_WIN32)
        sprintf(pstDev->name, "%s%s",
            RNIC_DEV_NAME_PREFIX, g_astRnicManageTbl[ucIndex].pucRnicNetCardName);
#else
        snprintf(pstDev->name, sizeof(pstDev->name),
            "%s%s",
            RNIC_DEV_NAME_PREFIX, g_astRnicManageTbl[ucIndex].pucRnicNetCardName);
#endif

        /* 对申请到的net_device结构的设备指针的函数域进行赋值 */
#if (VOS_OS_VER == VOS_WIN32)

#else
        pstDev->netdev_ops = &rnic_ops;
#endif

        /* 网卡私有数据初始化 */
        pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstDev);
        pstPriv->pstDev    = pstDev;
        pstPriv->enRmNetId = ucIndex;

        /* 关闭载波 */
        netif_carrier_off(pstDev);

        /* 停止网卡接收数据 */
        netif_stop_queue(pstDev);

        /* 调用register_netdev函数对Netcard进行注册 */
        lRegRst = register_netdev(pstDev);
        if (VOS_OK != lRegRst)
        {
            /* 注册失败释放创建的RNIC设备 */
            RNIC_DEV_ERR_PRINTK("RNIC_InitNetCard:Register netdev failed!");
            free_netdev(pstDev);
            continue;
        }

        /* 保存网卡私有数据 */
        pstNetCntxt->pstPriv = pstPriv;

        /* 打开载波 */
        netif_carrier_on(pstDev);

        /* 启动网卡接收数据 */
        netif_start_queue(pstDev);
    }

    printk("RNIC_InitNetCard: eixt, %u", VOS_GetSlice());

    return 0;
}

#if (VOS_LINUX == VOS_OS_VER)
#if (FEATURE_ON == FEATURE_DELAY_MODEM_INIT)
module_init(RNIC_InitNetCard);
#endif
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


