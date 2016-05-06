/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : StImcNic.c
  版 本 号   : 初稿
  作    者   : caikai
  生成日期   : 2013年8月23日
  最近修改   :
  功能描述   : IMS虚拟网卡ST测试用例
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月23日
    作    者   : caikai
    修改内容   : 创建文件

******************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "ImsNic.h"
#include  "v_sock.h"
#include  "TTFMemInterface.h"
#include  "TTFLink.h"
#include  "IpsMntnCCore.h"

#if (VOS_OS_VER == VOS_RTOSCK)
#include  "tcpip/tcpip.h"
#include  "tcpip/public/tcpip_basetype.h"
#include  "tcpip/public/tcpip_sock.h"
#include  "tcpip/public/arith_cbb/include/utlsll.h"
#include  "tcpip/tcpip_ipv6.h"
#else
#include  "ipcom_clib.h"
#include  "ipcom_ipcom2bsd.h"
#include  "ipcom_sock.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e801*/

#define     THIS_FILE_ID    0x8888

#ifdef  ST_IMS_NIC


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define     ST_IMS_NIC_IPV4_HEADER_LEN      (20)
#define     ST_IMS_NIC_IPV6_HEADER_LEN      (40)
#define     ST_IMS_NIC_UDP_HEADER_LEN       (8)

#define     ST_IMS_NIC_HEADER_LEN           (ST_IMS_NIC_IPV4_HEADER_LEN + ST_IMS_NIC_UDP_HEADER_LEN)
#define     ST_IMS_NIC_HEADER_V6_LEN        (ST_IMS_NIC_IPV6_HEADER_LEN + ST_IMS_NIC_UDP_HEADER_LEN)

TTF_LINK_ST                     g_stImsNicQ;

VOS_UINT32      g_ulImsNicWaitTime  = 1000;
#define     ST_IMS_NIC_WAIT_TIME    g_ulImsNicWaitTime


typedef struct
{
    VOS_UINT8       aucRsv[12];
    VOS_UINT8       aucSrcIp[4];
    VOS_UINT8       aucDstIp[4];
}IMS_NIC_IPV4_HDR;

typedef struct
{
    VOS_UINT8       aucRsv[8];
    VOS_UINT8       aucSrcIp[16];
    VOS_UINT8       aucDstIp[16];
}IMS_NIC_IPV6_HDR;

typedef struct
{
    VOS_UINT16      usSrcPort;
    VOS_UINT16      usDstPort;
    VOS_UINT8       aucRsv[4];
}IMS_NIC_UDP_HDR;

extern VOS_VOID IPS_MNTN_CCORE_BridgePktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
);

extern VOS_VOID IPS_MNTN_CCORE_DhcpcRecvPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
);
/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_InitQ
 功能描述  : 初始化队列
 输入参数  :
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  ST_IMS_NIC_InitQ(VOS_VOID)
{
    TTF_LinkInit(UEPS_PID_IMSNIC, &g_stImsNicQ);

    return;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_ClrQ
 功能描述  : 清空队列
 输入参数  :
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  ST_IMS_NIC_ClrQ(VOS_VOID)
{
    TTF_MEM_ST                         *pstMem;
    VOS_UINT32                          ulQCnt;
    VOS_UINT32                          ulLoop;


    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    /* 释放队列中缓存的数据 */
    for (ulLoop = 0;ulLoop < ulQCnt ;ulLoop++ )
    {
        /* 队列中取数 */
        pstMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (VOS_NULL_PTR != pstMem)
        {
            TTF_MemFree(UEPS_PID_IMSNIC, pstMem);
        }
        else
        {
            break;
        }
    }

    /* 检查一下队列是不是确实为空了，防止内存泄漏 */
    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if (0 != ulQCnt)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_ClrQ: ulQCnt = %d\n", ulQCnt);
    }

    return;

}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_PrintData
 功能描述  : 数据打印函数
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  ST_IMS_NIC_PrintData( VOS_UINT8 *pData, VOS_UINT16 usLen )
{
    VOS_UINT16                          i;

    if ( VOS_NULL_PTR == pData )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_PrintData: pData is NULL\n");
        return IMS_NIC_FAIL;
    }

    (VOS_VOID)vos_printf("\r\n");

    for (i = 0; i < usLen; i++)
    {
        (VOS_VOID)vos_printf("0x%2x,", pData[i]);
    }

    (VOS_VOID)vos_printf("\r\n");

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_ShowEntity
 功能描述  : 打印实体信息
 输入参数  :
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  ST_IMS_NIC_ShowEntity(VOS_UINT32 ulMomemId)
{
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(ulMomemId);

    ST_IMS_NIC_PrintData((VOS_UINT8 *)pstImsNicEntity, sizeof(IMS_NIC_ENTITY_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_UlCb
 功能描述  : 上行数据发送函数
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_UlCb(VOS_UINT8 *pData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    TTF_MEM_ST                         *pstTtfMem;
    VOS_UINT32                          ulRslt;

    ST_IMS_NIC_PrintData(pData, usLen);

    pstTtfMem = TTF_MemBlkAlloc(UEPS_PID_IMSNIC, TTF_MEM_POOL_ID_DL_PDU, usLen);

    if (VOS_NULL_PTR == pstTtfMem)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlCb: TTF_MemBlkAlloc fail");

        return VOS_ERR;
    }

    VOS_MemCpy(pstTtfMem->pData, pData, usLen);
    pstTtfMem->usUsed   = usLen;

    ulRslt = TTF_LinkInsertTail(UEPS_PID_IMSNIC, &g_stImsNicQ, &(pstTtfMem->stNode));
    /*lint -e774*/
    if (ulRslt != PS_SUCC)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlCb : TTF_LinkInsertTail fail!\n");
    }
    /*lint +e774*/

    (VOS_VOID)vos_printf("ST_IMS_NIC_UlCb, ulQCnt = %d!\r\n", TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ));

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_RegUlCb
 功能描述  : 注册上行数据发送回调函数
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_RegUlCb(VOS_VOID)
{
    VOS_UINT32      ulResult;

    ulResult    =  IMS_NIC_RegUlDataSendCb(ST_IMS_NIC_UlCb, 0);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_RegUlCb: Reg UL CB fail!\n");
        return;
    }

    return;
}

#if (VOS_OS_VER == VOS_RTOSCK)
/*****************************************************************************
 函 数 名  : ST_IMS_NIC_ShowEntity
 功能描述  : 打印MTU值
 输入参数  :
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  ST_IMS_NIC_ShowMtu(VOS_UINT32 ulMomemId)
{
    VOS_UINT32                          ulIpv4Mtu;
    VOS_UINT32                          ulIpv6Mtu;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(ulMomemId);

    TCPIP_GetLinkMtu(pstImsNicEntity->ulIfIndex, &ulIpv4Mtu);
    ADDR_Get_Mtu(pstImsNicEntity->ulIfIndex, IP6_ADDR_MTU_ACTUAL_CONFIG, &ulIpv6Mtu);

    (VOS_VOID)vos_printf("TCP IPV4 MTU Value:%u\r\n", ulIpv4Mtu);
    (VOS_VOID)vos_printf("TCP IPV6 MTU Value:%u\r\n", ulIpv6Mtu);
    (VOS_VOID)vos_printf("IMS MTU Value:%u\r\n", IMS_NIC_GET_MTU);
    return;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_ND
 功能描述  : 查找ND表项
 输入参数  : 无
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月13日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_ND()
{
    VOS_UINT8                           aucSrcIpAddr[16]    = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                           aucDstIpAddr[16]    = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                           aucIpv6[16]         = {0x20, 0x00, 0x4f, 0xfe, 0x00, 0x00, 0x00, 0x0d, 0xa9, 0x8e, 0xf9, 0x14, 0xe9, 0x82, 0xe7, 0x02};
    VOS_UINT32                          ulRet;
    VRP_IN6ADDR_S                       stIpAddr6 = {0};
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VRP_IN6ADDR_S                       stNxHpAddr = {0};


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(0);

    stIpAddr6.vrp_u6_addr.u6_uladdr[0] = vrp_ntohl(*(VOS_UINT32 *)aucDstIpAddr);
    stIpAddr6.vrp_u6_addr.u6_uladdr[1] = vrp_ntohl(*(VOS_UINT32 *)(aucDstIpAddr + 4));
    stIpAddr6.vrp_u6_addr.u6_uladdr[2] = vrp_ntohl(*(VOS_UINT32 *)(aucDstIpAddr + 8));
    stIpAddr6.vrp_u6_addr.u6_uladdr[3] = vrp_ntohl(*(VOS_UINT32 *)(aucDstIpAddr + 12));

    ulRet = ND_Get_OG_Intf_HOST(&stIpAddr6, &(pstImsNicEntity->ulIfIndex), &stNxHpAddr);

    (VOS_VOID)vos_printf("\r\n\nDestIP:  IfIndex:%u ulRet:%u\r\n\n", pstImsNicEntity->ulIfIndex, ulRet);

    (VOS_VOID)vos_printf("\r\n\ndst_addr[0]:0x%2x dst_addr[1]:0x%2x dst_addr[2]:0x%2x dst_addr[3]:0x%2x\r\n\n",
        stIpAddr6.vrp_u6_addr.u6_uladdr[0], stIpAddr6.vrp_u6_addr.u6_uladdr[1],
        stIpAddr6.vrp_u6_addr.u6_uladdr[2], stIpAddr6.vrp_u6_addr.u6_uladdr[3]);

    (VOS_VOID)vos_printf("\r\n\nnxhp_addr[0]:0x%2x nxhp_addr[1]:0x%2x nxhp_addr[2]:0x%2x nxhp_addr[3]:0x%2x\r\n\n",
        stNxHpAddr.vrp_u6_addr.u6_uladdr[0], stNxHpAddr.vrp_u6_addr.u6_uladdr[1],
        stNxHpAddr.vrp_u6_addr.u6_uladdr[2], stNxHpAddr.vrp_u6_addr.u6_uladdr[3]);

    stIpAddr6.vrp_u6_addr.u6_uladdr[0] = vrp_ntohl(*(VOS_UINT32 *)aucSrcIpAddr);
    stIpAddr6.vrp_u6_addr.u6_uladdr[1] = vrp_ntohl(*(VOS_UINT32 *)(aucSrcIpAddr + 4));
    stIpAddr6.vrp_u6_addr.u6_uladdr[2] = vrp_ntohl(*(VOS_UINT32 *)(aucSrcIpAddr + 8));
    stIpAddr6.vrp_u6_addr.u6_uladdr[3] = vrp_ntohl(*(VOS_UINT32 *)(aucSrcIpAddr + 12));

    ulRet = ND_Get_OG_Intf_HOST(&stIpAddr6, &(pstImsNicEntity->ulIfIndex), &stNxHpAddr);

    (VOS_VOID)vos_printf("\r\n\nSrcIP:  IfIndex:%u ulRet:%u\r\n\n", pstImsNicEntity->ulIfIndex, ulRet);

    (VOS_VOID)vos_printf("\r\n\nsrc_addr[0]:0x%2x src_addr[1]:0x%2x src_addr[2]:0x%2x src_addr[3]:0x%2x\r\n\n",
        stIpAddr6.vrp_u6_addr.u6_uladdr[0], stIpAddr6.vrp_u6_addr.u6_uladdr[1],
        stIpAddr6.vrp_u6_addr.u6_uladdr[2], stIpAddr6.vrp_u6_addr.u6_uladdr[3]);

    (VOS_VOID)vos_printf("\r\n\nnxhp_addr[0]:0x%2x nxhp_addr[1]:0x%2x nxhp_addr[2]:0x%2x nxhp_addr[3]:0x%2x\r\n\n",
        stNxHpAddr.vrp_u6_addr.u6_uladdr[0], stNxHpAddr.vrp_u6_addr.u6_uladdr[1],
        stNxHpAddr.vrp_u6_addr.u6_uladdr[2], stNxHpAddr.vrp_u6_addr.u6_uladdr[3]);

    stIpAddr6.vrp_u6_addr.u6_uladdr[0] = vrp_ntohl(*(VOS_UINT32 *)aucIpv6);
    stIpAddr6.vrp_u6_addr.u6_uladdr[1] = vrp_ntohl(*(VOS_UINT32 *)(aucIpv6 + 4));
    stIpAddr6.vrp_u6_addr.u6_uladdr[2] = vrp_ntohl(*(VOS_UINT32 *)(aucIpv6 + 8));
    stIpAddr6.vrp_u6_addr.u6_uladdr[3] = vrp_ntohl(*(VOS_UINT32 *)(aucIpv6 + 12));

    ulRet = ND_Get_OG_Intf_HOST(&stIpAddr6, &(pstImsNicEntity->ulIfIndex), &stNxHpAddr);

    (VOS_VOID)vos_printf("\r\n\nGateWay:  IfIndex:%u ulRet:%u\r\n\n", pstImsNicEntity->ulIfIndex, ulRet);

    (VOS_VOID)vos_printf("\r\n\ngateway[0]:0x%2x gateway[1]:0x%2x gateway[2]:0x%2x gateway[3]:0x%2x\r\n\n",
        stIpAddr6.vrp_u6_addr.u6_uladdr[0], stIpAddr6.vrp_u6_addr.u6_uladdr[1],
        stIpAddr6.vrp_u6_addr.u6_uladdr[2], stIpAddr6.vrp_u6_addr.u6_uladdr[3]);

    (VOS_VOID)vos_printf("\r\n\nnxhp_addr[0]:0x%2x nxhp_addr[1]:0x%2x nxhp_addr[2]:0x%2x nxhp_addr[3]:0x%2x\r\n\n",
        stNxHpAddr.vrp_u6_addr.u6_uladdr[0], stNxHpAddr.vrp_u6_addr.u6_uladdr[1],
        stNxHpAddr.vrp_u6_addr.u6_uladdr[2], stNxHpAddr.vrp_u6_addr.u6_uladdr[3]);


    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_GetND6
 功能描述  : 查找ND表项
 输入参数  : pucAddr      -- IPV6地址
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月13日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_GetND6(VOS_UINT8* pucAddr)
{
    VOS_UINT32                          ulRet;
    VRP_IN6ADDR_S                       stIpAddr6 = {0};
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VRP_IN6ADDR_S                       stNxHpAddr = {0};


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(0);

    (VOS_VOID)inet_pton6(pucAddr, &(stIpAddr6.vrp_u6_addr.u6_uladdr));

    ulRet = ND_Get_OG_Intf_HOST(&stIpAddr6, &(pstImsNicEntity->ulIfIndex), &stNxHpAddr);

    (VOS_VOID)vos_printf("\r\n\nAddr:%s  IfIndex:%u\r\n\n", pucAddr, pstImsNicEntity->ulIfIndex);

    (VOS_VOID)vos_printf("\r\n\naddr[0]:0x%2x addr[1]:0x%2x addr[2]:0x%2x addr[3]:0x%2xr\n\n",
        stNxHpAddr.vrp_u6_addr.u6_uladdr[0], stNxHpAddr.vrp_u6_addr.u6_uladdr[1],
        stNxHpAddr.vrp_u6_addr.u6_uladdr[2], stNxHpAddr.vrp_u6_addr.u6_uladdr[3]);

    (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_GetND6: ulRet = %u !\r\n\n", ulRet);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_LookUpFIB6
 功能描述  : 查找IPV6路由表
 输入参数  : pucAddr      -- IPV6地址
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月13日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_LookUpFIB6(VOS_UINT8* pucAddr)
{
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    TCPIP_ROUTE6_S                      stRoute6 = {0};
    VOS_UINT32                          ulIndex;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(0);

    (VOS_VOID)inet_pton6(pucAddr, &(stRoute6.aulDestination));

    ulRet = TCPIP_LookupFIB6(&stRoute6, 0);

    (VOS_VOID)vos_printf("\r\n\nAddr:%s  ulRet = %u\r\n\n", pucAddr, ulRet);

    (VOS_VOID)vos_printf("\r\n\nDest_addr[0]:0x%2x Dest_addr[1]:0x%2x Dest_addr[2]:0x%2x Dest_addr[3]:0x%2x\r\n\n",
        stRoute6.aulDestination[0], stRoute6.aulDestination[1],
        stRoute6.aulDestination[2], stRoute6.aulDestination[3]);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_UlSockSend
 功能描述  : 模拟IMSA通过socket发送上行数据
 输入参数  : aucIpAddr      -- IPV4地址
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_UlSockV4Send(VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr, VOS_UINT16 usImsNicPort, VOS_INT8 *pcIpData, VOS_INT s_size)
{
    VOS_INT32                           skfd;
    VOS_INT32                           lCount;
    struct vrp_sockaddr_in              fr_addr;

    /* Get a socket */
    skfd = vrp_socket(VRP_AF_INET, VRP_SOCK_DGRAM, 0);
    if (skfd <= 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV4Send: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Send the data */
    VOS_MemSet(&fr_addr, 0, sizeof(struct vrp_sockaddr_in));
    fr_addr.sin_family  = VRP_AF_INET;
    fr_addr.sin_port    = usImsNicPort;
    fr_addr.sin_addr.s_addr = vrp_ntohl(*((VOS_UINT32 *)aucDstIpAddr));

    (VOS_VOID)vos_printf("\r\n\nport:%u,addr:%u,skfd:%d\r\n\n", usImsNicPort, fr_addr.sin_addr.s_addr, skfd);

    lCount = vrp_sendto(skfd, (CHAR *)pcIpData, s_size, 0,
                         (struct vrp_sockaddr_in *) &fr_addr,
                         sizeof(struct vrp_sockaddr_in));

    (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV4Send: sendto Count = %d !\n", lCount);

    vrp_close(skfd);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_UlSockV6Send
 功能描述  : 模拟IMSA通过socket发送上行数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_IPV6Send()
{
    VOS_INT32                           skfd;
    VOS_INT32                           lCount;
    VRP_SOCKADDR_IN6_S                  in_addr6;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IN6ADDR_S                           stNxHpAddr;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                           aucDstIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                           aucIpData[]      =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11
    };
    VOS_INT                             s_size    = sizeof(aucIpData);
    VOS_UINT16                          usImsNicPort = 101;


    /* Get a socket */
    skfd = vrp_socket(VRP_AF_INET6, VRP_SOCK_DGRAM, 0);
    if (skfd <= 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV6Send: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Send the data */
    VOS_MemSet(&in_addr6, 0, sizeof(VRP_SOCKADDR_IN6_S));
    in_addr6.ucSin6_family  = VRP_AF_INET6;
    in_addr6.usSin6_port    = usImsNicPort;

    PS_MEM_CPY(&(in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr),
        aucDstIpAddr, IMS_NIC_IPV6_ADDR_LENGTH);
    (VOS_VOID)vos_printf("\r\n\nport:%u,skfd:%d,addr[1]:%2x,addr[2]:%2x,addr[3]:%2x,addr[4]:%2x\r\n\n",
        usImsNicPort, skfd, in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr[0], in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr[1],
        in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr[2], in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr[3]);

    lCount = vrp_sendto(skfd, (CHAR *)aucIpData, s_size, 0,
                         (VRP_SOCKADDR_IN6_S *) &in_addr6,
                         sizeof(VRP_SOCKADDR_IN6_S));

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(0);

    ulRet = ND_Get_OG_Intf_HOST(&(in_addr6.stSin6_addr), &(pstImsNicEntity->ulIfIndex), &stNxHpAddr);
    (VOS_VOID)vos_printf("\r\n\nND_Get_OG_Intf_HOST:ulRet:%d\r\n\n", ulRet);
    (VOS_VOID)vos_printf("\r\n\nND_Get_OG_Intf_HOST:Addr:%2x  %2x  %2x  %2x\r\n\n",
            stNxHpAddr.u6_addr.u6_uladdr[0],stNxHpAddr.u6_addr.u6_uladdr[1],
            stNxHpAddr.u6_addr.u6_uladdr[2],stNxHpAddr.u6_addr.u6_uladdr[3]);
    (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV6Send: sendto Count = %d !\n", lCount);

    vrp_close(skfd);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_UlSockV6Send
 功能描述  : 模拟IMSA通过socket发送上行数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_UlSockV6Send(VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr, VOS_UINT16 usImsNicPort, VOS_UINT8 *pucIpData, VOS_INT s_size)
{
    VOS_INT32                           skfd;
    VOS_INT32                           lCount;
    VRP_SOCKADDR_IN6_S                  in_addr6;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IN6ADDR_S                           stNxHpAddr;
    VOS_UINT32                          ulRet;


    ST_IMS_NIC_ClrQ();


    /* Get a socket */
    skfd = vrp_socket(VRP_AF_INET6, VRP_SOCK_DGRAM, 0);
    if (skfd <= 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV6Send: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Send the data */
    VOS_MemSet(&in_addr6, 0, sizeof(VRP_SOCKADDR_IN6_S));
    in_addr6.ucSin6_family  = VRP_AF_INET6;
    in_addr6.usSin6_port    = usImsNicPort;

    PS_MEM_CPY(&(in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr),
        aucDstIpAddr, IMS_NIC_IPV6_ADDR_LENGTH);

    (VOS_VOID)vos_printf("\r\n\nport:%u,skfd:%d,addr[1]:%2x,addr[2]:%2x,addr[3]:%2x,addr[4]:%2x\r\n\n",
        usImsNicPort, skfd, in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr[0], in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr[1],
        in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr[2], in_addr6.stSin6_addr.vrp_u6_addr.u6_uladdr[3]);

    lCount = vrp_sendto(skfd, (CHAR *)pucIpData, s_size, 0,
                         (VRP_SOCKADDR_IN6_S *) &in_addr6,
                         sizeof(VRP_SOCKADDR_IN6_S));

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(0);

    ulRet = ND_Get_OG_Intf_HOST(&(in_addr6.stSin6_addr), &(pstImsNicEntity->ulIfIndex), &stNxHpAddr);
    (VOS_VOID)vos_printf("\r\n\nND_Get_OG_Intf_HOST:ulRet:%d\r\n\n", ulRet);
    (VOS_VOID)vos_printf("\r\n\nND_Get_OG_Intf_HOST:Addr:%2x  %2x  %2x  %2x\r\n\n",
            stNxHpAddr.u6_addr.u6_uladdr[0],stNxHpAddr.u6_addr.u6_uladdr[1],
            stNxHpAddr.u6_addr.u6_uladdr[2],stNxHpAddr.u6_addr.u6_uladdr[3]);
    (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV6Send: sendto Count = %d !\n", lCount);

    vrp_close(skfd);

    return IMS_NIC_SUCC;
}

VOS_UINT32 ST_IMS_NIC_001_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort    = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_INT8                        acIpData[]      =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
    };
    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(acIpData);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    VOS_UINT32              ulIndex;


    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 配置虚拟网卡 */
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_001: config pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    TCPIP_ShowFIB();
    TCPIP_ShowIPAddr();

    ulResult    = ST_IMS_NIC_UlSockV4Send(aucDstIpAddr, aucSrcIpAddr, usImsNicPort, acIpData, s_size);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_001: send data via socket fail!\n");
        return ulResult;
    }

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    for (ulIndex = 0; ulIndex < ulQCnt; ulIndex++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_001, Fail! Q is empty!\r\n");
            ST_IMS_NIC_ClrQ();
            return IMS_NIC_FAIL;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_001: data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }

        if ( 0 != (VOS_MemCmp(acIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN))) )
        {
            (VOS_VOID)vos_printf("\r\n ST_IMS_NIC_001,     Fail! data not match!\r\n");
        }
        else
        {
            (VOS_VOID)vos_printf("\r\n ST_IMS_NIC_001,     Succ!\r\n");
        }

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }
    ST_IMS_NIC_ClrQ();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        ulResult    = IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_001: del pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_001
 功能描述  : 通过socket bind IPV4地址，发送数据给同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_001(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_001_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_001
 功能描述  : 通过socket bind IPV4地址，发送数据给不同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_001A(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]         = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_001_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

VOS_UINT32 ST_IMS_NIC_002_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort    = 101;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8                       aucIpData[]      =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11
    };
    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    VOS_UINT32              ulIndex;


    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_002: config pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    ulResult    = ST_IMS_NIC_UlSockV6Send(aucDstIpAddr, aucSrcIpAddr, usImsNicPort, aucIpData, s_size);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_002: send data via socket fail!\n");
        return ulResult;
    }
    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_002: ulQCnt = %u!\r\n\n", ulQCnt);

    for (ulIndex = 0; ulIndex < ulQCnt; ulIndex++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_002, Fail! Q is empty!\r\n");
            ST_IMS_NIC_ClrQ();
            return IMS_NIC_FAIL;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_V6_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_002: data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }

        if ( 0 != (VOS_MemCmp(aucIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_V6_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_V6_LEN))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_002, Fail! data not match!\r\n");
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_002, Succ!\r\n");
            break;
        }

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }
    ST_IMS_NIC_ClrQ();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        ulResult    = IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_001: del pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    return IMS_NIC_SUCC;
}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_002
 功能描述  : 通过socket bind IPV6地址，发送数据给同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_002(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ST_IMS_NIC_002_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_002A
 功能描述  : 通过socket bind IPV6地址，发送数据给不同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_002A(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x22, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ST_IMS_NIC_002_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

VOS_UINT32 ST_IMS_NIC_003_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usImsNicPort    = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_INT8                            acIpData[]      =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22
    };
    /*lint +e813*/
    VOS_INT                             s_size    = sizeof(acIpData);
    TTF_MEM_ST                         *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32                          ulQCnt;
    struct vrp_timeval                  tv;
    long                                timeout = 5;
    VOS_UINT8                          *pucRcvBuf;
    struct vrp_sockaddr_in              stInAddr;
    VOS_INT32                           lCount;
    IMS_NIC_IPV4_HDR                   *pstIpHead;
    IMS_NIC_UDP_HDR                    *pstUdpHead;
    VOS_UINT8                           aucTmp[4];
    VOS_INT32                           skfd;
    VOS_INT32                           lRet;
    vrp_fd_set                          stFdSet;
    VOS_UINT32                          ulIndex;


    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003: config pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    /* Get a socket */
    skfd = vrp_socket(VRP_AF_INET, VRP_SOCK_DGRAM, 0);
    if (skfd <= 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Send the data */
    VOS_MemSet(&stInAddr, 0, sizeof(struct vrp_sockaddr_in));
    stInAddr.sin_family = VRP_AF_INET;
    stInAddr.sin_port   = usImsNicPort;
    stInAddr.sin_addr.s_addr    = vrp_ntohl(*((VOS_UINT32 *)aucDstIpAddr));

    lCount = vrp_sendto(skfd, (CHAR *)acIpData, s_size, 0,
                         (struct vrp_sockaddr_in *) &stInAddr,
                         sizeof(struct vrp_sockaddr_in));

    (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_003: sendto Count = %d !\r\n\n", lCount);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    for (ulIndex = 0; ulIndex < ulQCnt; ulIndex++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003, Fail! Q is empty!\r\n");
            ST_IMS_NIC_ClrQ();
            return IMS_NIC_FAIL;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003: data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }

        if ( 0 != (VOS_MemCmp(acIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003: data not match!\r\n");
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003, Succ!\r\n");
        }

        /* Set the timeout */
        tv.tv_sec = timeout;
        tv.tv_usec = 0;

        pstIpHead   = (IMS_NIC_IPV4_HDR*)pstTtfMem->pData;
        VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 4);
        VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 4);
        VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 4);
        pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV4_HEADER_LEN);
        VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
        VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
        VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);
        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

        (VOS_VOID)vos_printf("ip & udp hdr :");
        ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);

        /* Wait for the response */
        VRP_FD_ZERO(&stFdSet);
        VRP_FD_SET(skfd, &stFdSet);

        lRet = vrp_select(skfd+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
        if (lRet <= 0)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003: socketselect failed!ret:%d\n", lRet);
            vrp_close(skfd);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            ST_IMS_NIC_ClrQ();
            return IMS_NIC_FAIL;
        }

        /* Get buffer memory. */
        pucRcvBuf = (VOS_UINT8 *)IMS_NIC_MALLOC((unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));
        if (VOS_NULL_PTR == pucRcvBuf)
        {
            vrp_close(skfd);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            ST_IMS_NIC_ClrQ();
            return IMS_NIC_FAIL;
        }

        if (VRP_FD_ISSET(skfd, &stFdSet))
        {
            lCount = vrp_recvfrom(skfd, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN,
                0, VOS_NULL_PTR, VOS_NULL_PTR);
            if (lCount <= 0)
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_003: server recv failed!\n");
                vrp_close(skfd);
                IMS_NIC_FREE(pucRcvBuf);
                TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
                ST_IMS_NIC_ClrQ();
                return IMS_NIC_FAIL;
            }

            if (lCount == s_size)
            {
                ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

                if ( 0 != (VOS_MemCmp(acIpData, pucRcvBuf, (VOS_UINT32)lCount)) )
                {
                    (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_003: data not match!\r\n\n");
                    TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
                    continue;
                }
                else
                {
                    (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_003, Succ!\r\n\n");
                }
            }
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003: error!\n");
            IMS_NIC_FREE(pucRcvBuf);
            vrp_close(skfd);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            ST_IMS_NIC_ClrQ();
            return IMS_NIC_FAIL;
        }

        (VOS_VOID)vos_printf("ST_IMS_NIC_003: ipcom_recvfrom count = %d !\n", lCount);

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
        IMS_NIC_FREE(pucRcvBuf);
        vrp_close(skfd);
    }
    ST_IMS_NIC_ClrQ();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        ulResult    = IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003: del pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }
    return IMS_NIC_SUCC;
}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_003
 功能描述  : 通过socket bind IPV4地址，发送数据给同网段地址，CDS匹配数据,
             随后CDS将数据发送给协议栈，上层通过socket 接收到数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_003(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_003_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);

    return IMS_NIC_SUCC;
}

VOS_UINT32 ST_IMS_NIC_003A(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]            = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_003_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);

    return IMS_NIC_SUCC;
}

VOS_UINT32 ST_IMS_NIC_004_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usImsNicPort    = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_INT8                            acIpData[]      =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33
    };
    /*lint +e813*/
    VOS_INT                             s_size    = sizeof(acIpData);
    TTF_MEM_ST                         *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32                          ulQCnt;
    vrp_fd_set                          stFdSet;
    struct vrp_timeval                  tv;
    long                                timeout = 5;
    VOS_UINT8                          *pucRcvBuf;
    VRP_SOCKADDR_IN6_S                  in_addr6;
    VOS_INT32                           skfd;
    VOS_INT32                           lCount;
    VOS_INT32                           lRet;
    IMS_NIC_IPV6_HDR                   *pstIpHead;
    IMS_NIC_UDP_HDR                    *pstUdpHead;
    VOS_UINT8                           aucTmp[16];
    VOS_UINT32                          ulIndex;


    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004: config pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    /* Get a socket */
    skfd = vrp_socket(VRP_AF_INET6, VRP_SOCK_DGRAM, 0);
    if (skfd < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Send the data */
    VOS_MemSet(&in_addr6, 0, sizeof(VRP_SOCKADDR_IN6_S));
    in_addr6.ucSin6_family      = VRP_AF_INET6;
    in_addr6.ucSin6_len         = sizeof(VRP_SOCKADDR_IN6_S);
    in_addr6.ulSin6_scope_id    = 0;
    in_addr6.usSin6_port        = VOS_HTONS(usImsNicPort);
    VOS_MemCpy(in_addr6.stSin6_addr.vrp_u6_addr.u6_ucaddr, aucDstIpAddr,
        sizeof(in_addr6.stSin6_addr.vrp_u6_addr.u6_ucaddr));

    lCount = vrp_sendto(skfd, (CHAR *)acIpData, s_size, 0,
                         (VRP_SOCKADDR_IN6_S *) &in_addr6,
                         sizeof(VRP_SOCKADDR_IN6_S));

    (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_004: ipcom_sendto count = %d !\r\n\n", lCount);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    for (ulIndex = 0; ulIndex < ulQCnt; ulIndex++)
    {
        (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_004: ulQCnt = %d ulIndex = %u!\r\n\n", ulQCnt, ulIndex);
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004, Fail! Q is empty!\r\n");
            ST_IMS_NIC_ClrQ();
            return IMS_NIC_FAIL;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_V6_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004: data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }

        if ( 0 != (VOS_MemCmp(acIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_V6_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_V6_LEN))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004: data not match!\r\n");
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004, Succ!\r\n");
        }

        /* Set the timeout */
        tv.tv_sec   = timeout;
        tv.tv_usec  = 0;

        pstIpHead   = (IMS_NIC_IPV6_HDR*)pstTtfMem->pData;
        VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 16);
        VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 16);
        VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 16);
        pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV6_HEADER_LEN);
        VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
        VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
        VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);

        /* 发送下行数据 */
        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

        (VOS_VOID)vos_printf("ip & udp hdr :");
        ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_V6_LEN);
    }

    /* Wait for the response */
    VRP_FD_ZERO(&stFdSet);
    VRP_FD_SET(skfd, &stFdSet);
    lRet = vrp_select(skfd+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
    if (lRet < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: socketselect failed!\n");
        vrp_close(skfd);
        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)IMS_NIC_MALLOC((unsigned int)(s_size + ST_IMS_NIC_HEADER_V6_LEN));
    if (pucRcvBuf == VOS_NULL_PTR)
    {
        vrp_close(skfd);
        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if (lRet == 0)
    {
        /* Timeout */
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: Timeout!\n");
        IMS_NIC_FREE(pucRcvBuf);
        vrp_close(skfd);
        return IMS_NIC_FAIL;
    }
    /*lint -e573*/
    else if (lRet > 0 && VRP_FD_ISSET(skfd, &stFdSet))
    /*lint +e573*/
    {
        /* Data available */
        lCount = vrp_recvfrom(skfd, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_V6_LEN,
            0, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    if (lCount == s_size)
    {
        ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

        if ( 0 != (VOS_MemCmp(acIpData, pucRcvBuf, (VOS_UINT32)lCount)) )
        {
            (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_004, Fail! data not match!\r\n\n");
        }
        else
        {
            (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_004, Succ!\r\n\n");
        }

        (VOS_VOID)vos_printf("ST_IMS_NIC_004: ipcom_recvfrom count = %d !\n", lCount);

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
        IMS_NIC_FREE(pucRcvBuf);
        vrp_close(skfd);
    }
    ST_IMS_NIC_ClrQ();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        ulResult    = IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004: del pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }
    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_002
 功能描述  : 通过socket bind IPV6地址，发送数据给同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_004(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ST_IMS_NIC_004_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_004A
 功能描述  : 通过socket bind IPV6地址，发送数据给不同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_004A(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x22, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ST_IMS_NIC_004_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_005
 功能描述  : 通过socket bind IPV4地址，发送5块数据给不同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_005_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usImsNicPort            = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_INT8                            acIpData[]              =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44
    };
    /*lint +e813*/
    VOS_INT                             s_size      = sizeof(acIpData);
    TTF_MEM_ST                         *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32                          ulQCnt;
    vrp_fd_set                          stFdSet;
    struct vrp_timeval                  tv;
    long                                timeout     = 5;
    VOS_UINT8                          *pucRcvBuf   = VOS_NULL_PTR;
    struct vrp_sockaddr_in              stInAddr;
    VOS_INT32                           sock;
    VOS_INT32                           lCount;
    VOS_INT32                           lRet;
    IMS_NIC_IPV4_HDR                   *pstIpHead;
    IMS_NIC_UDP_HDR                    *pstUdpHead;
    VOS_UINT8                           aucTmp[4];
    int                                 i;
    int                                 rcvNum  = 0;

    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: config pdn fail! ulResult = %d\n", ulResult);
            return;
        }
    }

    /* Get a socket */
    sock = vrp_socket(VRP_AF_INET, VRP_SOCK_DGRAM, 0);
    if (sock <= 0)
    {
        if (pstConfigInfo != VOS_NULL_PTR)
        {
            /* 删除虚拟网卡配置 */
            IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        }
        (VOS_VOID)vos_printf("ST_IMS_NIC_005: Get socket failed!\n");
        return;
    }

    /* Send the data */
    VOS_MemSet(&stInAddr, 0, sizeof(struct vrp_sockaddr_in));
    stInAddr.sin_family = VRP_AF_INET;
    stInAddr.sin_port   = usImsNicPort;
    stInAddr.sin_addr.s_addr    = vrp_ntohl(*((VOS_UINT32 *)aucDstIpAddr));

    /* 发送5遍 */
    for (i = 0; i < 5; i++)
    {
        lCount = vrp_sendto(sock, (CHAR *)acIpData, s_size, 0,
                             (struct vrp_sockaddr_in *) &stInAddr,
                             sizeof(struct vrp_sockaddr_in));

        (VOS_VOID)vos_printf("ST_IMS_NIC_005: ipcom_sendto [%d] count = %d !\n", i, lCount);
    }

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    /* 等待两秒 */
    VOS_TaskDelay(ST_IMS_NIC_WAIT_TIME);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    for (i = 0; i < (VOS_INT)ulQCnt; i++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005, Fail! Q is empty!\r\n");
            goto out;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }

        if ( 0 != (VOS_MemCmp(acIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: data not match!\r\n");
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005, Succ!\r\n");
        }

        pstIpHead   = (IMS_NIC_IPV4_HDR*)pstTtfMem->pData;
        VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 4);
        VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 4);
        VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 4);
        pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV4_HEADER_LEN);
        VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
        VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
        VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);

        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

        (VOS_VOID)vos_printf("ip & udp hdr :");
        ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }

    /* Wait for the response */
    VRP_FD_ZERO(&stFdSet);
    VRP_FD_SET(sock, &stFdSet);

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)IMS_NIC_MALLOC((unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));
    if (pucRcvBuf == VOS_NULL_PTR)
    {
        goto out;
    }

    for (;;)
    {
        lRet = vrp_select(sock+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
        if (lRet < 0)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: socketselect failed!\n");
            goto out;
        }

        /* Get buffer memory. */
        VOS_MemSet(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (lRet == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (lRet > 0 && VRP_FD_ISSET(sock, &stFdSet))
        /*lint +e573*/
        {
            /* Data available */
            lCount = vrp_recvfrom(sock, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN,
                0, VOS_NULL_PTR, VOS_NULL_PTR);
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: error!\n");
            goto out;
        }

        if (lCount == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

            if ( 0 != (VOS_MemCmp(acIpData, pucRcvBuf, (VOS_UINT32)lCount)) )
            {
                (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_005, Fail! data not match!\r\n\n");
            }
            else
            {
                (VOS_VOID)vos_printf("\r\n\nrecvfrom data match!\r\n\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("\r\n\nST_IMS_NIC_005: ipcom_recvfrom count = %d !\r\n\n", lCount);
    }

    if (rcvNum != 5)
    {
        (VOS_VOID)vos_printf("\r\n\nrecvfrom data num= %d not equal 5!\r\n\n", rcvNum);
        goto out;
    }
    (VOS_VOID)vos_printf("\r\n\n=====ST_IMS_NIC_005: Pass!=====\r\n\n");

out:
    /*lint -e961*/
    if (pucRcvBuf != VOS_NULL_PTR)
    {
        IMS_NIC_FREE(pucRcvBuf);
    }

    vrp_close(sock);
    ST_IMS_NIC_ClrQ();
    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
    }
    /*lint +e961*/
    return;
}

VOS_VOID ST_IMS_NIC_005(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]            = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_005_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);

    return;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_006
 功能描述  : 网卡配置两个IP,分别通过socket bind IPV4地址，发送5块数据给不同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_006(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo;
    VOS_UINT8                           aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                           aucDstIpAddr1[4]            = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                           aucDnsPrimAddr1[4]          = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                           aucDnsSecAddr1[4]           = {0xC0, 0xA8, 0x05, 0x02};
    VOS_UINT8                           aucSrcIpAddr2[4]            = {0xC0, 0xA8, 0x03, 0x05};
    VOS_UINT8                           aucDstIpAddr2[4]            = {0xB0, 0xA8, 0x02, 0x07};
    VOS_UINT8                           aucDnsPrimAddr2[4]          = {0xC0, 0xA8, 0x05, 0x03};
    VOS_UINT8                           aucDnsSecAddr2[4]           = {0xC0, 0xA8, 0x05, 0x04};

    VOS_UINT32                          ulResult;
    VOS_UINT16                          usImsNicPort                = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_INT8                            acIpData1[]                 =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x55
    };

    VOS_INT8                            acIpData2[]                 =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x66
    };

    /*lint +e813*/
    VOS_INT                             s_size      = sizeof(acIpData1);
    TTF_MEM_ST                         *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32                          ulQCnt;
    vrp_fd_set                          stFdSet;
    struct vrp_timeval                  tv;
    long                                timeout     = 5;
    VOS_UINT8                          *pucRcvBuf   = VOS_NULL_PTR;
    struct vrp_sockaddr_in              stInAddr;
    VOS_INT32                           sock1;
    VOS_INT32                           sock2;
    VOS_INT32                           lRet;
    VOS_INT32                           lCount;
    IMS_NIC_IPV4_HDR                   *pstIpHead;
    IMS_NIC_UDP_HDR                    *pstUdpHead;
    VOS_UINT8                           aucTmp[4];
    int                                 i;
    int                                 rcvNum      = 0;

    ST_IMS_NIC_RegUlCb();

    /* 配置第一个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    /* 配置第二个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 6;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr2, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr2, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr2, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: config pdn fail! ulResult = %d\n", ulResult);
        IMS_NIC_PdnInfoDel(5, 0);
        return;
    }

    /* Get a socket */
    sock1 = vrp_socket(VRP_AF_INET, VRP_SOCK_DGRAM, 0);
    if (sock1 < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: Get socket failed!\n");
        IMS_NIC_PdnInfoDel(5, 0);
        IMS_NIC_PdnInfoDel(6, 0);
        return;
    }

    /* Send the data */
    VOS_MemSet(&stInAddr, 0, sizeof(struct vrp_sockaddr_in));
    stInAddr.sin_family = VRP_AF_INET;
    stInAddr.sin_port   = usImsNicPort;
    stInAddr.sin_addr.s_addr    = vrp_ntohl(*((VOS_UINT32 *)aucDstIpAddr1));

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        lCount = vrp_sendto(sock1, (CHAR *)acIpData1, s_size, 0,
                             (struct vrp_sockaddr *) &stInAddr,
                             sizeof(struct vrp_sockaddr));

        (VOS_VOID)vos_printf("sock1: ipcom_sendto [%d] count = %d !\n", i, lCount);
    }

    /* Get another socket */
    sock2 = vrp_socket(VRP_AF_INET, VRP_SOCK_DGRAM, 0);
    if (sock2 < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: Get socket failed!\n");
        vrp_close(sock1);
        IMS_NIC_PdnInfoDel(5, 0);
        IMS_NIC_PdnInfoDel(6, 0);
        return;
    }

    /* Send the data */
    VOS_MemSet(&stInAddr, 0, sizeof(struct vrp_sockaddr_in));
    stInAddr.sin_family = VRP_AF_INET;
    stInAddr.sin_port   = usImsNicPort;
    stInAddr.sin_addr.s_addr = vrp_ntohl(*((VOS_UINT32 *)aucDstIpAddr2));

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        lCount = vrp_sendto(sock2, (CHAR *)acIpData2, s_size, 0,
                             (struct vrp_sockaddr *) &stInAddr,
                             sizeof(struct vrp_sockaddr_in));

        (VOS_VOID)vos_printf("sock2: ipcom_sendto [%d] count = %d !\n", i, lCount);
    }

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    /* 等待两秒 */
    VOS_TaskDelay(ST_IMS_NIC_WAIT_TIME);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    for (i = 0; i < (VOS_INT)ulQCnt; i++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_006, Fail! Q is empty!\r\n");
            goto out;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_006: data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }

        if ( 0 != (VOS_MemCmp(acIpData1, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN -1))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_006: data not match!\r\n");
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_006: data match!rcv :ip & udp hdr :");
            ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);
        }

        pstIpHead   = (IMS_NIC_IPV4_HDR*)pstTtfMem->pData;
        VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 4);
        VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 4);
        VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 4);
        pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV4_HEADER_LEN);
        VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
        VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
        VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);

        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

        (VOS_VOID)vos_printf("send: ip & udp hdr :");
        ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }

    /* Wait for the response */
    VRP_FD_ZERO(&stFdSet)
    VRP_FD_SET(sock1, &stFdSet);

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)IMS_NIC_MALLOC((unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));
    if (pucRcvBuf == VOS_NULL_PTR)
    {
        goto out;
    }

    for (;;)
    {
        lRet = vrp_select(sock1+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
        if (lRet < 0)
        {
            (VOS_VOID)vos_printf("sock1: socketselect failed!ret:%d\n", lRet);
            goto out;
        }

        /* Get buffer memory. */
        VOS_MemSet(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (lRet == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock1: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (lRet > 0 && VRP_FD_ISSET(sock1, &stFdSet))
        /*lint +e573*/
        {
            /* Data available */
            lCount = vrp_recvfrom(sock1, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN,
                0, VOS_NULL_PTR, VOS_NULL_PTR);
        }
        else
        {
            (VOS_VOID)vos_printf("sock1: error!\n");
            goto out;
        }

        if (lCount == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

            if ( 0 != (VOS_MemCmp(acIpData1, pucRcvBuf, (VOS_UINT32)lCount)) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_006: sock1, Fail! data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock1, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("ST_IMS_NIC_006: ipcom_recvfrom from sock1 count = %d !\n", lCount);
    }

    (VOS_VOID)vos_printf("rcv data from sock1, rcvNum= %d!\r\n", rcvNum);
    if (rcvNum != 2)
    {
        goto out;
    }
    rcvNum  = 0;

    /* Wait for the second response */
    VRP_FD_ZERO(&stFdSet);
    VRP_FD_SET(sock2, &stFdSet);

    for (;;)
    {
        lRet = vrp_select(sock2+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
        if (lRet < 0)
        {
            (VOS_VOID)vos_printf("sock2: socketselect failed!ret:%d\n", lRet);
            goto out;
        }

        /* Get buffer memory. */
        VOS_MemSet(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (lRet == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock2: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (lRet > 0 && VRP_FD_ISSET(sock2, &stFdSet))
        /*lint +e573*/
        {
            /* Data available */
            lCount = vrp_recvfrom(sock2, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN,
                0, VOS_NULL_PTR, VOS_NULL_PTR);
        }
        else
        {
            (VOS_VOID)vos_printf("sock2: error!\n");
            goto out;
        }

        if (lCount == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

            if ( 0 != (VOS_MemCmp(acIpData2, pucRcvBuf, (VOS_UINT32)lCount)) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_006:sock2, Fail! data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock2, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock2: ipcom_recvfrom from sock2 count = %d !\n", lCount);
    }

    if (rcvNum != 2)
    {
        (VOS_VOID)vos_printf("recvfrom data num= %d not equal 2!\r\n", rcvNum);
        goto out;
    }
    (VOS_VOID)vos_printf("ST_IMS_NIC_006: Pass!\r\n");

out:
    /*lint -e961*/
    if (pucRcvBuf != VOS_NULL_PTR)
    {
        IMS_NIC_FREE(pucRcvBuf);
    }
    vrp_close(sock1);
    vrp_close(sock2);
    ST_IMS_NIC_ClrQ();
    /* 删除虚拟网卡配置 */
    IMS_NIC_PdnInfoDel(5, 0);
    IMS_NIC_PdnInfoDel(6, 0);
    /*lint +e961*/
    return;
}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_007
 功能描述  : 网卡配置两个IP,分别通过socket bind IPV6地址，发送2块数据给不同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_007(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo;
    VOS_UINT8                           aucSrcIpAddr1[16]           = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                           aucDstIpAddr1[16]           = {0x22, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                           aucDnsPrimAddr1[16]         = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                           aucDnsSecAddr1[16]          = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                           aucSrcIpAddr2[16]           = {0x23, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                           aucDstIpAddr2[16]           = {0x24, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                           aucDnsPrimAddr2[16]         = {0x4, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                           aucDnsSecAddr2[16]          = {0x5, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_UINT32                          ulResult;
    VOS_UINT16                          usImsNicPort                = 1007;            /* 16-bit port number */
    /*lint -e813*/
    VOS_INT8                            acIpData1[]                 =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x77
    };

    VOS_INT8                            acIpData2[]                 =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x88
    };

    /*lint +e813*/
    VOS_INT                             s_size      = sizeof(acIpData1);
    TTF_MEM_ST                         *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32                          ulQCnt;
    vrp_fd_set                          stFdSet;
    struct vrp_timeval                  tv;
    long                                timeout     = 5;
    VOS_UINT8                          *pucRcvBuf   = VOS_NULL_PTR;
    VRP_SOCKADDR_IN6_S                  in_addr6;
    VOS_INT32                           sock1;
    VOS_INT32                           sock2;
    VOS_INT32                           lCount;
    VOS_INT32                           lRet;
    IMS_NIC_IPV6_HDR                   *pstIpHead;
    IMS_NIC_UDP_HDR                    *pstUdpHead;
    VOS_UINT8                           aucTmp[16];
    int                                 i;
    VOS_UINT8                           ucRabId1    = 7;
    VOS_UINT8                           ucRabId2    = 8;
    VOS_UINT16                          usMaxPort1  = 65534;
    VOS_UINT16                          usMinPort1  = 1;
    VOS_UINT16                          usMaxPort2  = 19000;
    VOS_UINT16                          usMinPort2  = 2;
    VOS_UINT16                          usExpectMinPort = 0;
    VOS_UINT16                          usExpectMaxPort = 0;
    int                                 rcvNum      = 0;
    VOS_UINT16                          usSize      = 2;
    VOS_CHAR                           *pcValue;
    SOCK_GLOBLE_S                       stSockGlobal;


    ST_IMS_NIC_RegUlCb();

    /* 配置第一个IPV6地址 */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.bitOpSockPortInfo  = PS_TRUE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr1, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 16);

    stConfigInfo.stSockPortInfo.usSockMaxPort       = usMaxPort1;
    stConfigInfo.stSockPortInfo.usSockMinPort       = usMinPort1;

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    (VOS_VOID)TCPIP_GetSockGlobleConfig(&stSockGlobal);


    (VOS_VOID)vos_printf("ST_IMS_NIC_007:first config MinPort = %d, MaxPort = %d\n",
        stSockGlobal.usAutoPortStart, stSockGlobal.usAutoPortEnd);

    if ((usMinPort1 != stSockGlobal.usAutoPortStart) || (usMaxPort1 != stSockGlobal.usAutoPortEnd))
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: config socket port fail!\n");
        return;
    }

    /* 配置第二个IPV6地址 */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.bitOpSockPortInfo  = PS_TRUE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId2;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr2, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr2, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr2, 16);

    stConfigInfo.stSockPortInfo.usSockMaxPort       = usMaxPort2;
    stConfigInfo.stSockPortInfo.usSockMinPort       = usMinPort2;

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: config pdn fail! ulResult = %d\n", ulResult);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        return;
    }

    (VOS_VOID)TCPIP_GetSockGlobleConfig(&stSockGlobal);

    (VOS_VOID)vos_printf("ST_IMS_NIC_007:sec config MinPort = %d, MaxPort = %d\n",
        stSockGlobal.usAutoPortStart, stSockGlobal.usAutoPortEnd);
    if ((usMinPort1 != stSockGlobal.usAutoPortStart) || (usMaxPort1 != stSockGlobal.usAutoPortEnd))
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007:socket port can not config twice!\n");
        return;
    }

    /* Get a socket */
    sock1 = vrp_socket(VRP_AF_INET6, VRP_SOCK_DGRAM, 0);
    if (sock1 <= 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: Get socket1 failed!\n");
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Send the data */
    VOS_MemSet(&in_addr6, 0, sizeof(VRP_SOCKADDR_IN6_S));
    in_addr6.ucSin6_family      = VRP_AF_INET6;
    in_addr6.ulSin6_scope_id    = 0;
    in_addr6.usSin6_port        = usImsNicPort;
    VOS_MemCpy(in_addr6.stSin6_addr.vrp_u6_addr.u6_ucaddr, aucDstIpAddr1,
        sizeof(in_addr6.stSin6_addr.vrp_u6_addr.u6_ucaddr));

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        lCount = vrp_sendto(sock1, (CHAR *)acIpData1, s_size, 0,
                             (VRP_SOCKADDR_IN6_S *) &in_addr6,
                             sizeof(VRP_SOCKADDR_IN6_S));

        (VOS_VOID)vos_printf("sock1: ipcom_sendto[%d] count = %d !\n",i, lCount);
    }

    /* Get another socket */
    sock2 = vrp_socket(VRP_AF_INET6, VRP_SOCK_DGRAM, 0);
    if (sock2 <= 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: Get socket2 failed!\n");
        vrp_close(sock1);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Send the data */
    VOS_MemSet(&in_addr6, 0, sizeof(VRP_SOCKADDR_IN6_S));
    in_addr6.ucSin6_family      = VRP_AF_INET6;
    in_addr6.ulSin6_scope_id    = 0;
    in_addr6.usSin6_port        = usImsNicPort;
    VOS_MemCpy(in_addr6.stSin6_addr.vrp_u6_addr.u6_ucaddr, aucDstIpAddr2,
        sizeof(in_addr6.stSin6_addr.vrp_u6_addr.u6_ucaddr));

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        lCount = vrp_sendto(sock2, (void*)acIpData2, s_size, 0,
                             (VRP_SOCKADDR_IN6_S *) &in_addr6,
                             sizeof(VRP_SOCKADDR_IN6_S));

        (VOS_VOID)vos_printf("sock2: ipcom_sendto[%d] count = %d !\n",i, lCount);
    }

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    /* 等待两秒 */
    VOS_TaskDelay(ST_IMS_NIC_WAIT_TIME);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    for (i = 0; i < (VOS_INT)ulQCnt; i++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_007, Fail! Q is empty!\r\n");
            goto out;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_V6_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_007: data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }

        if ( 0 != (VOS_MemCmp(acIpData1, pstTtfMem->pData + ST_IMS_NIC_HEADER_V6_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_V6_LEN -1))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_007: UL data not match!\r\n");
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            continue;
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_007: UL data match!rcv :ip & udp hdr :");
            ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_V6_LEN);
        }

        pstIpHead   = (IMS_NIC_IPV6_HDR*)pstTtfMem->pData;
        VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 16);
        VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 16);
        VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 16);
        pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV6_HEADER_LEN);
        VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
        VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
        VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);

        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

        (VOS_VOID)vos_printf("send: ip & udp hdr :");
        ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_V6_LEN);

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }

    /* Wait for the response */
    VRP_FD_ZERO(&stFdSet);
    VRP_FD_SET(sock1, &stFdSet);

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)IMS_NIC_MALLOC((unsigned int)(s_size + ST_IMS_NIC_HEADER_V6_LEN));
    if (pucRcvBuf == VOS_NULL_PTR)
    {
        goto out;
    }

    for (;;)
    {
        lRet = vrp_select(sock1+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
        if (lRet < 0)
        {
            (VOS_VOID)vos_printf("sock1: socketselect failed!ret:%d\n", lRet);
            goto out;
        }

        /* Get buffer memory. */
        VOS_MemSet(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_V6_LEN));

        if (lRet == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock1: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (lRet > 0 && VRP_FD_ISSET(sock1, &stFdSet))
        /*lint +e573*/
        {
            /* Data available */
            lCount = vrp_recvfrom(sock1, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_V6_LEN,
                0, VOS_NULL_PTR, VOS_NULL_PTR);
        }
        else
        {
            (VOS_VOID)vos_printf("sock1: error!\n");
            goto out;
        }

        if (lCount == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

            if ( 0 != (VOS_MemCmp(acIpData1, pucRcvBuf, (VOS_UINT32)lCount)) )
            {
                (VOS_VOID)vos_printf("sock1, Fail! DL data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock1, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock1: ipcom_recvfrom from sock1 count = %d !\n", lCount);
    }

    (VOS_VOID)vos_printf("rcv data from sock1, rcvNum= %d!\r\n", rcvNum);
    if (rcvNum != 2)
    {
        goto out;
    }
    rcvNum  = 0;

    /* Wait for the second response */
    VRP_FD_ZERO(&stFdSet);
    VRP_FD_SET(sock2, &stFdSet);
    for (;;)
    {
        lRet = vrp_select(sock2+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
        if (lRet < 0)
        {
            (VOS_VOID)vos_printf("sock2: socketselect failed!ret:%d\n", lRet);
            goto out;
        }

        /* Get buffer memory. */
        VOS_MemSet(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_V6_LEN));

        if (lRet == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock2: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (lRet > 0 && VRP_FD_ISSET(sock2, &stFdSet))
        /*lint +e573*/
        {
            /* Data available */
            lCount = vrp_recvfrom(sock2, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_V6_LEN, 0, VOS_NULL_PTR, VOS_NULL_PTR);
        }
        else
        {
            (VOS_VOID)vos_printf("sock2: error!\n");
            goto out;
        }

        if (lCount == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

            if ( 0 != (VOS_MemCmp(acIpData2, pucRcvBuf, (VOS_UINT32)lCount)) )
            {
                (VOS_VOID)vos_printf("sock2, Fail! DL data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock2, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock2: ipcom_recvfrom from sock2 count = %d !\n", lCount);
    }

    if (rcvNum != 2)
    {
        (VOS_VOID)vos_printf("recvfrom data num= %d not equal 2!\r\n", rcvNum);
        goto out;
    }
    (VOS_VOID)vos_printf("ST_IMS_NIC_007: Pass!\r\n");

out:
    /*lint -e961*/
    if (pucRcvBuf != VOS_NULL_PTR)
    {
        IMS_NIC_FREE(pucRcvBuf);
    }
    vrp_close(sock1);
    vrp_close(sock2);
    ST_IMS_NIC_ClrQ();
    /* 删除虚拟网卡配置 */
    IMS_NIC_PdnInfoDel(ucRabId1, 0);
    IMS_NIC_PdnInfoDel(ucRabId2, 0);
    /*lint +e961*/
    return;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_008
 功能描述  : 网卡配置两个IP，一个IPV4，一个IPV6,分别通过socket bind 该两个地址，
             发送2块数据给不同网段地址，CDS匹配数据，匹配后CDS将数据发送回协议栈，
             上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_008(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo;
    VOS_UINT8                           aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                           aucDstIpAddr1[4]            = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                           aucDnsPrimAddr1[4]          = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                           aucDnsSecAddr1[4]           = {0xC0, 0xA8, 0x05, 0x02};
    VOS_UINT8                           aucSrcIpAddr2[16]           = {0x23, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                           aucDstIpAddr2[16]           = {0x24, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                           aucDnsPrimAddr2[16]         = {0x4, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                           aucDnsSecAddr2[16]          = {0x5, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_UINT32                          ulResult;
    VOS_UINT16                          usImsNicPort                = 1002;            /* 16-bit port number */
    /*lint -e813*/
    VOS_INT8                            acIpData1[]                 =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x55,0x66
    };

    VOS_INT8                            acIpData2[]                 =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x55,0x77
    };

    /*lint +e813*/
    VOS_INT                             s_size      = sizeof(acIpData1);
    TTF_MEM_ST                         *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32                          ulQCnt;
    vrp_fd_set                          stFdSet;
    struct vrp_timeval                  tv;
    long                                timeout     = 5;
    VOS_UINT8                          *pucRcvBuf   = VOS_NULL_PTR;
    struct vrp_sockaddr_in              stInAddr;
    VRP_SOCKADDR_IN6_S                  in_addr6;
    VOS_INT32                           sock1;
    VOS_INT32                           sock2;
    VOS_INT32                           lCount;
    VOS_INT32                           lRet;
    IMS_NIC_IPV4_HDR                   *pstIpV4Head;
    IMS_NIC_IPV6_HDR                   *pstIpV6Head;
    IMS_NIC_UDP_HDR                    *pstUdpHead;
    VOS_UINT8                           aucTmp[16];
    int                                 i;
    VOS_UINT8                           ucRabId1    = 9;
    VOS_UINT8                           ucRabId2    = 10;
    int                                 rcvNum      = 0;
    VOS_UINT8                           ucIpType;
    VOS_UINT8                          *pucData;

    ST_IMS_NIC_RegUlCb();

    /* 配置第一个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    /* 配置第二个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId2;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr2, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr2, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr2, 16);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("config pdn fail! ulResult = %d\n", ulResult);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        return;
    }

    /* Get a socket */
    sock1 = vrp_socket(VRP_AF_INET, VRP_SOCK_DGRAM, 0);
    if (sock1 <= 0)
    {
        (VOS_VOID)vos_printf("Get socket failed!\n");
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Send the data */
    VOS_MemSet(&stInAddr, 0, sizeof(struct vrp_sockaddr_in));
    stInAddr.sin_family = VRP_AF_INET;
    stInAddr.sin_port   = usImsNicPort;
    stInAddr.sin_addr.s_addr = vrp_ntohl(*((VOS_UINT32 *)aucDstIpAddr1));

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        lCount = vrp_sendto(sock1, (CHAR *)acIpData1, s_size, 0,
                             (struct vrp_sockaddr *) &stInAddr,
                             sizeof(struct vrp_sockaddr_in));

        (VOS_VOID)vos_printf("sock1: ipcom_sendto [%d] count = %d !\n", i, lCount);
    }

    /* Get another socket */
    sock2 = vrp_socket(VRP_AF_INET6, VRP_SOCK_DGRAM, 0);
    if (sock2 < 0)
    {
        (VOS_VOID)vos_printf("Get socket2 failed!\n");
        vrp_close(sock1);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Send the data */
    VOS_MemSet(&in_addr6, 0, sizeof(VRP_SOCKADDR_IN6_S));
    in_addr6.ucSin6_family      = VRP_AF_INET6;
    in_addr6.ulSin6_scope_id    = 0;
    in_addr6.usSin6_port        = usImsNicPort;
    VOS_MemCpy(in_addr6.stSin6_addr.vrp_u6_addr.u6_ucaddr, aucDstIpAddr2,
        sizeof(in_addr6.stSin6_addr.vrp_u6_addr.u6_ucaddr));
    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        lCount = vrp_sendto(sock2, (CHAR *)acIpData2, s_size, 0,
                             (VRP_SOCKADDR_IN6_S *) &in_addr6,
                             sizeof(VRP_SOCKADDR_IN6_S));

        (VOS_VOID)vos_printf("sock2: ipcom_sendto[%d] count = %d !\n",i, lCount);
    }

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    /* 等待两秒 */
    VOS_TaskDelay(ST_IMS_NIC_WAIT_TIME);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);

    for (i = 0; i < (VOS_INT)ulQCnt; i++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_008, Fail! Q is empty!\r\n");
            goto out;
        }

        pucData = pstTtfMem->pData;
        /* 解析IP包的版本号 */
        ucIpType    = ((pucData[0] >> IMS_NIC_IP_VERSION_POS) & IMS_NIC_IP_VERSION_MASK);
        if (IMS_NIC_IPV4_VERSION == ucIpType)
        {
            if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
                TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
                continue;
            }

            if ( 0 != (VOS_MemCmp(acIpData1, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN -1))) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008:UL IPV4 data not match!\r\n");
                TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
                continue;
            }
            else
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008:UL IPV4 data match!rcv :ip & udp hdr :");
                ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);
            }

            pstIpV4Head   = (IMS_NIC_IPV4_HDR*)pstTtfMem->pData;
            VOS_MemCpy(aucTmp, pstIpV4Head->aucDstIp, 4);
            VOS_MemCpy(pstIpV4Head->aucDstIp, pstIpV4Head->aucSrcIp, 4);
            VOS_MemCpy(pstIpV4Head->aucSrcIp, aucTmp, 4);
            pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV4_HEADER_LEN);
            VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
            VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
            VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);
        }
        else if (IMS_NIC_IPV6_VERSION == ucIpType)
        {
            if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_V6_LEN)
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008: data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
                TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
                continue;
            }

            if ( 0 != (VOS_MemCmp(acIpData1, pstTtfMem->pData + ST_IMS_NIC_HEADER_V6_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_V6_LEN -1))) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008: UL IPV6 data not match!\r\n");
                TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
                continue;
            }
            else
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008: UL IPV6 data match!rcv :ip & udp hdr :");
                ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_V6_LEN);
            }

            pstIpV6Head   = (IMS_NIC_IPV6_HDR*)pstTtfMem->pData;
            VOS_MemCpy(aucTmp, pstIpV6Head->aucDstIp, 16);
            VOS_MemCpy(pstIpV6Head->aucDstIp, pstIpV6Head->aucSrcIp, 16);
            VOS_MemCpy(pstIpV6Head->aucSrcIp, aucTmp, 16);
            pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV6_HEADER_LEN);
            VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
            VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
            VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);
        }
        else
        {
            (VOS_VOID)vos_printf("rcv error ip pkt\n");
        }

        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);
        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }

    /* Wait for the response */
    VRP_FD_ZERO(&stFdSet);
    VRP_FD_SET(sock1, &stFdSet);

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)IMS_NIC_MALLOC((unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));
    if (pucRcvBuf == VOS_NULL_PTR)
    {
        goto out;
    }

    for (;;)
    {
        lRet = vrp_select(sock1+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
        if (lRet < 0)
        {
            (VOS_VOID)vos_printf("sock1: socketselect failed!ret:%d\n", lRet);
            goto out;
        }

        /* Get buffer memory. */
        VOS_MemSet(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (lRet == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock1: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (lRet > 0 && VRP_FD_ISSET(sock1, &stFdSet))
        /*lint +e573*/
        {
            /* Data available */
            lCount = vrp_recvfrom(sock1, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN, 0, VOS_NULL_PTR, VOS_NULL_PTR);
        }
        else
        {
            (VOS_VOID)vos_printf("sock1: error!\n");
            goto out;
        }

        if (lCount == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

            if ( 0 != (VOS_MemCmp(acIpData1, pucRcvBuf, (VOS_UINT32)lCount)) )
            {
                (VOS_VOID)vos_printf("sock1, Fail! DL data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock1, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock1: ipcom_recvfrom from sock1 count = %d !\n", lCount);
    }

    (VOS_VOID)vos_printf("rcv data from sock1, rcvNum= %d!\r\n", rcvNum);
    if (rcvNum != 2)
    {
        goto out;
    }
    rcvNum  = 0;

    /* Wait for the second response */
    VRP_FD_ZERO(&stFdSet);
    VRP_FD_SET(sock2, &stFdSet);

    for (;;)
    {
        lRet = vrp_select(sock2+1, &stFdSet, VOS_NULL_PTR, VOS_NULL_PTR, &tv);
        if (lRet < 0)
        {
            (VOS_VOID)vos_printf("sock2: socketselect failed!ret:%d\n", lRet);
            goto out;
        }

        /* Get buffer memory. */
        VOS_MemSet(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (lRet == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock2: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (lRet > 0 && VRP_FD_ISSET(sock2, &stFdSet))
        /*lint +e573*/
        {
            /* Data available */
            lCount = vrp_recvfrom(sock2, (CHAR *)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN, 0, VOS_NULL_PTR, VOS_NULL_PTR);
        }
        else
        {
            (VOS_VOID)vos_printf("sock2: error!\n");
            goto out;
        }

        if (lCount == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)lCount);

            if ( 0 != (VOS_MemCmp(acIpData2, pucRcvBuf, (VOS_UINT32)lCount)) )
            {
                (VOS_VOID)vos_printf("sock2, Fail! UL data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock2, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock2: ipcom_recvfrom from sock2 count = %d !\n", lCount);
    }

    if (rcvNum != 2)
    {
        (VOS_VOID)vos_printf("recvfrom data num= %d not equal 2!\r\n", rcvNum);
        goto out;
    }
    (VOS_VOID)vos_printf("ST_IMS_NIC_008: Pass!\r\n");

out:
    /*lint -e961*/
    if (pucRcvBuf != VOS_NULL_PTR)
    {
        IMS_NIC_FREE(pucRcvBuf);
    }

    vrp_close(sock1);
    vrp_close(sock2);
    ST_IMS_NIC_ClrQ();
    /* 删除虚拟网卡配置 */
    IMS_NIC_PdnInfoDel(ucRabId1, 0);
    IMS_NIC_PdnInfoDel(ucRabId2, 0);
    /*lint +e961*/
    return;
}

VOS_VOID ST_IMS_NIC_009(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDnsPrimAddr1[4]          = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr1[4]           = {0xC0, 0xA8, 0x05, 0x02};
    VOS_UINT8                       aucSrcIpAddr2[4]            = {0xC0, 0xA8, 0x03, 0x05};
    VOS_UINT8                       aucDnsPrimAddr2[4]          = {0xC0, 0xA8, 0x05, 0x03};
    VOS_UINT8                       aucDnsSecAddr2[4]           = {0xC0, 0xA8, 0x05, 0x04};

    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 5;
    VOS_UINT8   ucRabId2    = 6;

    ST_IMS_NIC_RegUlCb();

    /* 配置第一个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_009: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    /* 配置第二个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId2;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr2, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr2, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr2, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_009: config pdn fail! ulResult = %d\n", ulResult);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_ADD_DNS_001
 功能描述  : 查询DNS
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_ADD_DNS_001
(
    CHAR                               *pstServerIP,
    ULONG                               ulIPV6Flag,
    CHAR                               *pstDomainName,
    CHAR                               *pcDNSName
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulDnsNum = 200;
    VOS_VOID*                           pulIPAddr;


    pulIPAddr = (VOID *)IMS_NIC_MALLOC(ulDnsNum * sizeof(VOS_UINT32));
    VOS_MemSet(pulIPAddr, 0, sizeof(ulDnsNum * sizeof(VOS_UINT32)));

    /* 设置DNS Server IP:"192.168.30.121" */
    ulRet = TCPIP_SetDnsServer(0, pstServerIP, ulIPV6Flag);
    if (VOS_OK != ulRet)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_ADD_DNS_001:Set Dns Fail!ulRet=%u\r\n", ulRet);
    }

    /* 设置DNS后缀:"huawei.com" */
    ulRet = TCPIP_SetDnsDomainSuffix(0, pstDomainName, 0);
    if (VOS_OK != ulRet)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_ADD_DNS_001:Set Dns Domain Fail!ulRet=%u\r\n", ulRet);
    }

    /* 查询DNS:"server34_v4" */
    ulRet = TCPIP_GetDnsHost(pcDNSName, pulIPAddr, ulIPV6Flag);
    if (VOS_OK != ulRet)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_ADD_DNS_001:Get Dns Names Fail!ulRet=%u\r\n", ulRet);
        return ulRet;
    }

    /* 也可以查询TCPIP_ShowDnsInfo */

    (VOS_VOID)vos_printf("\r\n=====DNS Info====\r\n");
    for (ulIndex = 0; ulIndex < ulDnsNum; ulIndex++)
    {
        if (0 == (ulIndex % 8))
        {
            (VOS_VOID)vos_printf("\r\n");
        }
        (VOS_VOID)vos_printf("%u ",*((VOS_UINT32 *)pulIPAddr + ulIndex));
    }
    (VOS_VOID)vos_printf("\r\n=================\r\n");

    return;
}

VOS_VOID ST_DNS_001(VOS_UINT8 ucIpAddr, VOS_UINT8 ucDnsPrim, VOS_UINT8 ucDnsSec)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x33, 0};
    VOS_UINT8                       aucDnsPrimAddr1[4]          = {0xC0, 0xA8, 0x1E, 0x01};
    VOS_UINT8                       aucDnsSecAddr1[4]           = {0xC0, 0xA8, 0x1E, 0x02};

    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 5;

    aucSrcIpAddr1[3]        = ucIpAddr;
    aucDnsPrimAddr1[3]      = ucDnsPrim;
    aucDnsSecAddr1[3]       = ucDnsSec;

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_FALSE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_DNS_001: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    return;
}

VOS_VOID ST_DNS_002(VOS_UINT8 ucIpAddr)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]            = {0x21, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x20, 0x0, 0x0, 0x02, 0x0, 0x02, 0x0, 0x01, 0x0, 0x01, 0x0, 0x01, 0x0, 0x1f, 0x0, 0x01};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x20, 0x0, 0x0, 0x02, 0x0, 0x02, 0x0, 0x01, 0x0, 0x01, 0x0, 0x01, 0x0, 0x1f, 0x0, 0x01};
    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 6;

    aucSrcIpAddr[7]  = ucIpAddr;

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_FALSE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_DNS_002: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    return;
}

#else
/*****************************************************************************
 函 数 名  : ST_IMS_NIC_UlSockSend
 功能描述  : 模拟IMSA通过socket发送上行数据
 输入参数  : aucIpAddr      -- IPV4地址
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_UlSockV4Send(VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr, VOS_UINT16 usImsNicPort, VOS_UINT8 *aucIpData, VOS_INT s_size)
{
    Ip_s32                  sock, count;
    struct Ip_sockaddr_in   stInAddr;

    /* Get a socket */
    sock = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
    if (sock < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV4Send: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Bind the socket */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    //stInAddr.sin_addr.s_addr = IP_INADDR_ANY;
    ipcom_memcpy(&stInAddr.sin_addr, aucSrcIpAddr, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = 0;
    if (ipcom_bind(sock, (struct Ip_sockaddr*) &stInAddr, sizeof(struct Ip_sockaddr)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV4Send: bind socket failed!\n");
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    /* Send the data */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    ipcom_memcpy(&stInAddr.sin_addr, aucDstIpAddr, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = usImsNicPort;

    count = ipcom_sendto(sock, (void*)aucIpData, s_size, 0,
                         (struct Ip_sockaddr *) &stInAddr,
                         sizeof(struct Ip_sockaddr_in));

    (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV4Send: ipcom_sendto count = %d !\n", count);
    ipcom_socketclose(sock);
    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_UlSockV6Send
 功能描述  : 模拟IMSA通过socket发送上行数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_UlSockV6Send(VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr, VOS_UINT16 usImsNicPort, VOS_UINT8 *aucIpData, VOS_INT s_size)
{
    Ip_s32                      sock, count;
    struct Ip_sockaddr_in6      in_addr6;

    /* Get a socket */
    sock = ipcom_socket(IP_AF_INET6, IP_SOCK_DGRAM, 0);
    if (sock < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV4Send: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Bind the socket */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    //in_addr6.sin6_addr = in6addr_any;
    ipcom_memcpy(&in_addr6.sin6_addr, aucSrcIpAddr, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_port = 0;
    if (ipcom_bind(sock, (struct Ip_sockaddr*)&in_addr6, sizeof(struct Ip_sockaddr_in6)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV6Send: bind socket failed!\n");
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;

    }

    /* Send the data */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    ipcom_memcpy(&in_addr6.sin6_addr, aucDstIpAddr, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_scope_id = 0;
    in_addr6.sin6_port = usImsNicPort;

    count = ipcom_sendto(sock, (void*)aucIpData, s_size, 0,
                         (struct Ip_sockaddr *) &in_addr6,
                         sizeof(struct Ip_sockaddr_in6));

    (VOS_VOID)vos_printf("ST_IMS_NIC_UlSockV6Send: ipcom_sendto count = %d !\n", count);
    ipcom_socketclose(sock);
    return IMS_NIC_SUCC;
}

VOS_UINT32 ST_IMS_NIC_001_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort            = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
    };
    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    char *cmd_str           = "ifconfig -a";

    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 配置虚拟网卡 */
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_001: config pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    ipcom_run_cmd(cmd_str);

    ulResult    = ST_IMS_NIC_UlSockV4Send(aucDstIpAddr, aucSrcIpAddr, usImsNicPort, aucIpData, s_size);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_001: send data via socket fail!\n");
        return ulResult;
    }

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if ( ulQCnt != 1 )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_001, Fail! ulQCnt = %d!\r\n", ulQCnt);
        return IMS_NIC_FAIL;
    }

    /* 队列中取数 */
    pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if (pstTtfMem == VOS_NULL_PTR)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_001, Fail! Q is empty!\r\n");
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_001, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if ( 0 != (VOS_MemCmp(aucIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN))) )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_001, Fail! data not match!\r\n");
    }
    else
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_001, Succ!\r\n");
    }

    TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    ST_IMS_NIC_ClrQ();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        ulResult    = IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_001: del pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_001
 功能描述  : 通过socket bind IPV4地址，发送数据给同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_001(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_001_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_001
 功能描述  : 通过socket bind IPV4地址，发送数据给不同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_001A(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]         = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_001_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_001M(同001，但需手动配置网卡)
 功能描述  : 通过socket bind IPV4地址，发送数据给同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_001M(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU   *pstConfigInfo   = VOS_NULL_PTR;
    VOS_UINT8                       aucSrcIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x07};

    ST_IMS_NIC_001_base(pstConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_001M(同001A，但需手动配置网卡)
 功能描述  : 通过socket bind IPV4地址，发送数据给同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_001AM(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU   *pstConfigInfo   = VOS_NULL_PTR;
    VOS_UINT8                       aucSrcIpAddr[4]         = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]         = {0xA0, 0xA8, 0x02, 0x07};

    ST_IMS_NIC_001_base(pstConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

VOS_UINT32 ST_IMS_NIC_002_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort            = 101;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11
    };
    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    char                    addr_str[40];           /* 查看IP地址字符串 */
    char *cmd_str           = "ifconfig -a";

    (VOS_VOID)vos_printf("ST_IMS_NIC_002: Src IP: %s, Dst IP: %s\n", ipcom_inet_ntop(IP_AF_INET6, aucSrcIpAddr, addr_str, sizeof(addr_str)), ipcom_inet_ntop(IP_AF_INET6, aucDstIpAddr, addr_str, sizeof(addr_str)));

    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_002: config pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    ipcom_run_cmd(cmd_str);

    ulResult    = ST_IMS_NIC_UlSockV6Send(aucDstIpAddr, aucSrcIpAddr, usImsNicPort, aucIpData, s_size);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_002: send data via socket fail!\n");
        return ulResult;
    }

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if ( ulQCnt != 1 )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_002, Fail! ulQCnt = %d!\r\n", ulQCnt);
        return IMS_NIC_FAIL;
    }

    /* 队列中取数 */
    pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if (pstTtfMem == VOS_NULL_PTR)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_002, Fail! Q is empty!\r\n");
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_V6_LEN)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_002, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if ( 0 != (VOS_MemCmp(aucIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_V6_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_V6_LEN))) )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_002, Fail! data not match!\r\n");
    }
    else
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_002, Succ!\r\n");
    }

    TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    ST_IMS_NIC_ClrQ();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        ulResult    = IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_001: del pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    return IMS_NIC_SUCC;
}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_002
 功能描述  : 通过socket bind IPV6地址，发送数据给同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_002(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ST_IMS_NIC_002_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_002A
 功能描述  : 通过socket bind IPV6地址，发送数据给不同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_002A(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x22, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ST_IMS_NIC_002_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_002M(同002，但需手动配置网卡)
 功能描述  : 通过socket bind IPV6地址，发送数据给同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_002M(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU   *pstConfigInfo   = VOS_NULL_PTR;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */

    ST_IMS_NIC_002_base(pstConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_002MA(同002A，但需手动配置网卡)
 功能描述  : 通过socket bind IPV6地址，发送数据给同网段地址，CDS匹配数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_002AM(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU   *pstConfigInfo   = VOS_NULL_PTR;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x22, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */

    ST_IMS_NIC_002_base(pstConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

VOS_UINT32 ST_IMS_NIC_003_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort            = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22
    };
    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    Ip_fd_set *read_set = IP_NULL;
    struct Ip_timeval tv;
    long    timeout = 5;
    VOS_UINT8       *pucRcvBuf;
    struct Ip_sockaddr_in   stInAddr;
    Ip_s32 sock, count, num;
    IMS_NIC_IPV4_HDR    *pstIpHead;
    IMS_NIC_UDP_HDR     *pstUdpHead;
    VOS_UINT8            aucTmp[4];
    char *cmd_str           = "ifconfig -a";

    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003: config pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    ipcom_run_cmd(cmd_str);

    /* Get a socket */
    sock = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
    if (sock < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Bind the socket */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    //stInAddr.sin_addr.s_addr = IP_INADDR_ANY;
    ipcom_memcpy(&stInAddr.sin_addr, aucSrcIpAddr, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = 0;
    if (ipcom_bind(sock, (struct Ip_sockaddr*) &stInAddr, sizeof(struct Ip_sockaddr)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003: bind socket failed!\n");
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    /* Send the data */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    ipcom_memcpy(&stInAddr.sin_addr, aucDstIpAddr, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = usImsNicPort;

    count = ipcom_sendto(sock, (void*)aucIpData, s_size, 0,
                         (struct Ip_sockaddr *) &stInAddr,
                         sizeof(struct Ip_sockaddr_in));

    (VOS_VOID)vos_printf("ST_IMS_NIC_003: ipcom_sendto count = %d !\n", count);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if ( ulQCnt != 1 )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004, Fail! ulQCnt = %d!\r\n", ulQCnt);
        return IMS_NIC_FAIL;
    }

    /* 队列中取数 */
    pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if (pstTtfMem == VOS_NULL_PTR)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003, Fail! Q is empty!\r\n");
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if ( 0 != (VOS_MemCmp(aucIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN))) )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003, Fail! data not match!\r\n");
    }
    else
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003, Succ!\r\n");
    }

    /* Prepare the read set */
    read_set = ipcom_malloc(sizeof(Ip_fd_set));
    if (read_set == IP_NULL)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003: Prepare read set failed!\n");
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }
    ipcom_memset(read_set, 0, sizeof(Ip_fd_set));

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    pstIpHead   = (IMS_NIC_IPV4_HDR*)pstTtfMem->pData;
    VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 4);
    VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 4);
    VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 4);
    pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV4_HEADER_LEN);
    VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
    VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
    VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);
    IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

    (VOS_VOID)vos_printf("ip & udp hdr :");
    ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);

    /* Wait for the response */
    /*lint -e573*/
    IP_FD_SET(sock, read_set);
    /*lint +e573*/
    num = ipcom_socketselect(sock+1, read_set, IP_NULL, IP_NULL, &tv);
    if (num == IP_SOCKERR)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003: socketselect failed!\n");
        ipcom_free(read_set);
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)ipcom_malloc((unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));
    if (pucRcvBuf == IP_NULL)
    {
        ipcom_free(read_set);
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    if (num == 0)
    {
        /* Timeout */
        (VOS_VOID)vos_printf("ST_IMS_NIC_003: Timeout!\n");
        ipcom_free(read_set);
        ipcom_free(pucRcvBuf);
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }
    /*lint -e573*/
    else if (num > 0 && IP_FD_ISSET(sock, read_set))
    /*lint +e573*/
    {
        /* Data available */
        count = ipcom_recvfrom(sock, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN, 0, IP_NULL, IP_NULL);
    }
    else
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_003: error!\n");
        ipcom_free(read_set);
        ipcom_free(pucRcvBuf);
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    if (count == s_size)
    {
        ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

        if ( 0 != (VOS_MemCmp(aucIpData, pucRcvBuf, (VOS_UINT32)count)) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003, Fail! data not match!\r\n");
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003, Succ!\r\n");
        }
    }

    (VOS_VOID)vos_printf("ST_IMS_NIC_003: ipcom_recvfrom count = %d !\n", count);

    TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    ipcom_free(read_set);
    ipcom_free(pucRcvBuf);
    ipcom_socketclose(sock);
    ST_IMS_NIC_ClrQ();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        ulResult    = IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_003: del pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }
    return IMS_NIC_SUCC;
}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_003
 功能描述  : 通过socket bind IPV4地址，发送数据给同网段地址，CDS匹配数据,
             随后CDS将数据发送给协议栈，上层通过socket 接收到数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_003(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_003_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_003M(同003，但需手动配置网卡)
 功能描述  : 通过socket bind IPV4地址，发送数据给同网段地址，CDS匹配数据,
             随后CDS将数据发送给协议栈，上层通过socket 接收到数据
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ST_IMS_NIC_003M(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU   *pstConfigInfo   = VOS_NULL_PTR;
    VOS_UINT8                       aucSrcIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x07};

    ST_IMS_NIC_003_base(pstConfigInfo, aucDstIpAddr, aucSrcIpAddr);

    return IMS_NIC_SUCC;
}

VOS_UINT32 ST_IMS_NIC_003A(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]            = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_003_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);

    return IMS_NIC_SUCC;
}

VOS_UINT32 ST_IMS_NIC_003AM(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU   *pstConfigInfo   = VOS_NULL_PTR;
    VOS_UINT8                       aucSrcIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]            = {0xA0, 0xA8, 0x02, 0x07};

    ST_IMS_NIC_003_base(pstConfigInfo, aucDstIpAddr, aucSrcIpAddr);

    return IMS_NIC_SUCC;
}

VOS_UINT32 ST_IMS_NIC_004_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort            = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33
    };
    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    Ip_fd_set *read_set = IP_NULL;
    struct Ip_timeval tv;
    long    timeout = 5;
    VOS_UINT8       *pucRcvBuf;
    struct Ip_sockaddr_in6      in_addr6;
    Ip_s32 sock, count, num;
    IMS_NIC_IPV6_HDR    *pstIpHead;
    IMS_NIC_UDP_HDR     *pstUdpHead;
    VOS_UINT8            aucTmp[16];
    char *cmd_str           = "ifconfig -a";

    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004: config pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }

    ipcom_run_cmd(cmd_str);

    /* Get a socket */
    sock = ipcom_socket(IP_AF_INET6, IP_SOCK_DGRAM, 0);
    if (sock < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: Get socket failed!\n");
        return IMS_NIC_FAIL;
    }

    /* Bind the socket */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    //in_addr6.sin6_addr = in6addr_any;
    ipcom_memcpy(&in_addr6.sin6_addr, aucSrcIpAddr, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_port = 0;
    if (ipcom_bind(sock, (struct Ip_sockaddr*)&in_addr6, sizeof(struct Ip_sockaddr_in6)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: bind socket failed!\n");
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    /* Send the data */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    ipcom_memcpy(&in_addr6.sin6_addr, aucDstIpAddr, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_scope_id = 0;
    in_addr6.sin6_port = usImsNicPort;

    count = ipcom_sendto(sock, (void*)aucIpData, s_size, 0,
                         (struct Ip_sockaddr *) &in_addr6,
                         sizeof(struct Ip_sockaddr_in6));

    (VOS_VOID)vos_printf("ST_IMS_NIC_004: ipcom_sendto count = %d !\n", count);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if ( ulQCnt != 1 )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004, Fail! ulQCnt = %d!\r\n", ulQCnt);
        return IMS_NIC_FAIL;
    }

    /* 队列中取数 */
    pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if (pstTtfMem == VOS_NULL_PTR)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004, Fail! Q is empty!\r\n");
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_V6_LEN)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
        ST_IMS_NIC_ClrQ();
        return IMS_NIC_FAIL;
    }

    if ( 0 != (VOS_MemCmp(aucIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_V6_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_V6_LEN))) )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004, Fail! data not match!\r\n");
    }
    else
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004, Succ!\r\n");
    }

    /* Prepare the read set */
    read_set = ipcom_malloc(sizeof(Ip_fd_set));
    if (read_set == IP_NULL)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: Prepare read set failed!\n");
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }
    ipcom_memset(read_set, 0, sizeof(Ip_fd_set));

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    pstIpHead   = (IMS_NIC_IPV6_HDR*)pstTtfMem->pData;
    VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 16);
    VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 16);
    VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 16);
    pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV6_HEADER_LEN);
    VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
    VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
    VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);

    /* 发送下行数据 */
    IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

    (VOS_VOID)vos_printf("ip & udp hdr :");
    ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_V6_LEN);

    /* Wait for the response */
    /*lint -e573*/
    IP_FD_SET(sock, read_set);
    /*lint +e573*/
    num = ipcom_socketselect(sock+1, read_set, IP_NULL, IP_NULL, &tv);
    if (num == IP_SOCKERR)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: socketselect failed!\n");
        ipcom_free(read_set);
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)ipcom_malloc((unsigned int)(s_size + ST_IMS_NIC_HEADER_V6_LEN));
    if (pucRcvBuf == IP_NULL)
    {
        ipcom_free(read_set);
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    if (num == 0)
    {
        /* Timeout */
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: Timeout!\n");
        ipcom_free(read_set);
        ipcom_free(pucRcvBuf);
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }
    /*lint -e573*/
    else if (num > 0 && IP_FD_ISSET(sock, read_set))
    /*lint +e573*/
    {
        /* Data available */
        count = ipcom_recvfrom(sock, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_V6_LEN, 0, IP_NULL, IP_NULL);
    }
    else
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_004: error!\n");
        ipcom_free(read_set);
        ipcom_free(pucRcvBuf);
        ipcom_socketclose(sock);
        return IMS_NIC_FAIL;
    }

    if (count == s_size)
    {
        ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

        if ( 0 != (VOS_MemCmp(aucIpData, pucRcvBuf, (VOS_UINT32)count)) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004, Fail! data not match!\r\n");
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004, Succ!\r\n");
        }
    }

    (VOS_VOID)vos_printf("ST_IMS_NIC_004: ipcom_recvfrom count = %d !\n", count);

    TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    ipcom_free(read_set);
    ipcom_free(pucRcvBuf);
    ipcom_socketclose(sock);
    ST_IMS_NIC_ClrQ();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        ulResult    = IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_004: del pdn fail! ulResult = %d\n", ulResult);
            return ulResult;
        }
    }
    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_002
 功能描述  : 通过socket bind IPV6地址，发送数据给同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_004(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ST_IMS_NIC_004_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_004A
 功能描述  : 通过socket bind IPV6地址，发送数据给不同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_004A(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x22, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ST_IMS_NIC_004_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

VOS_VOID ST_IMS_NIC_004M(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU   *pstConfigInfo   = VOS_NULL_PTR;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */

    ST_IMS_NIC_004_base(pstConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

VOS_VOID ST_IMS_NIC_004AM(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU   *pstConfigInfo   = VOS_NULL_PTR;
    VOS_UINT8                       aucSrcIpAddr[16]               = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr[16]               = {0x22, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */

    ST_IMS_NIC_004_base(pstConfigInfo, aucDstIpAddr, aucSrcIpAddr);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_005
 功能描述  : 通过socket bind IPV4地址，发送5块数据给不同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_005_base(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo, VOS_UINT8 *aucDstIpAddr, VOS_UINT8 *aucSrcIpAddr)
{
    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort            = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44
    };
    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    Ip_fd_set *read_set = IP_NULL;
    struct Ip_timeval tv;
    long    timeout = 5;
    VOS_UINT8       *pucRcvBuf  = VOS_NULL_PTR;
    struct Ip_sockaddr_in   stInAddr;
    Ip_s32 sock, count, num;
    IMS_NIC_IPV4_HDR    *pstIpHead;
    IMS_NIC_UDP_HDR     *pstUdpHead;
    VOS_UINT8            aucTmp[4];
    char *cmd_str           = "ifconfig -a";
    int i;
    int rcvNum  = 0;

    ST_IMS_NIC_RegUlCb();

    if (pstConfigInfo != VOS_NULL_PTR)
    {
        ulResult    = IMS_NIC_PdnInfoConfig (pstConfigInfo);
        if (IMS_NIC_SUCC != ulResult)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: config pdn fail! ulResult = %d\n", ulResult);
            return;
        }
    }

    ipcom_run_cmd(cmd_str);

    /* Get a socket */
    sock = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
    if (sock < 0)
    {
        if (pstConfigInfo != VOS_NULL_PTR)
        {
            /* 删除虚拟网卡配置 */
            IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
        }
        (VOS_VOID)vos_printf("ST_IMS_NIC_005: Get socket failed!\n");
        return;
    }

    /* Bind the socket */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    //stInAddr.sin_addr.s_addr = IP_INADDR_ANY;
    ipcom_memcpy(&stInAddr.sin_addr, aucSrcIpAddr, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = 0;
    if (ipcom_bind(sock, (struct Ip_sockaddr*) &stInAddr, sizeof(struct Ip_sockaddr)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_005: bind socket failed!\n");
        goto out;
    }

    /* Send the data */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    ipcom_memcpy(&stInAddr.sin_addr, aucDstIpAddr, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = usImsNicPort;

    /* 发送5遍 */
    for (i = 0; i < 5; i++)
    {
        count = ipcom_sendto(sock, (void*)aucIpData, s_size, 0,
                             (struct Ip_sockaddr *) &stInAddr,
                             sizeof(struct Ip_sockaddr_in));

        (VOS_VOID)vos_printf("ST_IMS_NIC_005: ipcom_sendto [%d] count = %d !\n", i, count);
    }

    /* Prepare the read set */
    read_set = ipcom_malloc(sizeof(Ip_fd_set));
    if (read_set == IP_NULL)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_005: Prepare read set failed!\n");
        goto out;
    }
    ipcom_memset(read_set, 0, sizeof(Ip_fd_set));

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    /* 等待两秒 */
    VOS_TaskDelay(ST_IMS_NIC_WAIT_TIME);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if ( ulQCnt != 5 )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_005, Fail! ulQCnt = %d!\r\n", ulQCnt);
        goto out;
    }

    for (i = 0; i < (VOS_INT)ulQCnt; i++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005, Fail! Q is empty!\r\n");
            goto out;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            goto out;
        }

        if ( 0 != (VOS_MemCmp(aucIpData, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005, Fail! data not match!\r\n");
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005, Succ!\r\n");
        }

        pstIpHead   = (IMS_NIC_IPV4_HDR*)pstTtfMem->pData;
        VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 4);
        VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 4);
        VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 4);
        pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV4_HEADER_LEN);
        VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
        VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
        VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);

        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

        (VOS_VOID)vos_printf("ip & udp hdr :");
        ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }

    /* Wait for the response */
    /*lint -e573*/
    IP_FD_SET(sock, read_set);
    /*lint +e573*/

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)ipcom_malloc((unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));
    if (pucRcvBuf == IP_NULL)
    {
        goto out;
    }

    for (;;)
    {
        num = ipcom_socketselect(sock+1, read_set, IP_NULL, IP_NULL, &tv);
        if (num == IP_SOCKERR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: socketselect failed!\n");
            goto out;
        }

        /* Get buffer memory. */
        ipcom_memset(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (num == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (num > 0 && IP_FD_ISSET(sock, read_set))
        /*lint +e573*/
        {
            /* Data available */
            count = ipcom_recvfrom(sock, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN, 0, IP_NULL, IP_NULL);
        }
        else
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_005: error!\n");
            goto out;
        }

        if (count == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

            if ( 0 != (VOS_MemCmp(aucIpData, pucRcvBuf, (VOS_UINT32)count)) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_005, Fail! data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("recvfrom data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("ST_IMS_NIC_005: ipcom_recvfrom count = %d !\n", count);
    }

    if (rcvNum != 5)
    {
        (VOS_VOID)vos_printf("recvfrom data num= %d not equal 5!\r\n", rcvNum);
        goto out;
    }
    (VOS_VOID)vos_printf("ST_IMS_NIC_005: Pass!\r\n");

out:
    /*lint -e961*/
    if (pucRcvBuf != VOS_NULL_PTR)
    {
        ipcom_free(pucRcvBuf);
    }
    if (read_set != IP_NULL)
    {
        ipcom_free(read_set);
    }
    ipcom_socketclose(sock);
    ST_IMS_NIC_ClrQ();
    if (pstConfigInfo != VOS_NULL_PTR)
    {
        /* 删除虚拟网卡配置 */
        IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, 0);
    }
    /*lint +e961*/
    return;
}

VOS_VOID ST_IMS_NIC_005(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr[4]            = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr[4]       = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr[4]        = {0xC0, 0xA8, 0x05, 0x02};

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 4);

    ST_IMS_NIC_005_base(&stConfigInfo, aucDstIpAddr, aucSrcIpAddr);

    return;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_006
 功能描述  : 网卡配置两个IP,分别通过socket bind IPV4地址，发送5块数据给不同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_006(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr1[4]            = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr1[4]          = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr1[4]           = {0xC0, 0xA8, 0x05, 0x02};
    VOS_UINT8                       aucSrcIpAddr2[4]            = {0xC0, 0xA8, 0x03, 0x05};
    VOS_UINT8                       aucDstIpAddr2[4]            = {0xB0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr2[4]          = {0xC0, 0xA8, 0x05, 0x03};
    VOS_UINT8                       aucDnsSecAddr2[4]           = {0xC0, 0xA8, 0x05, 0x04};

    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort            = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData1[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x55
    };

    VOS_UINT8               aucIpData2[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x66
    };

    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData1);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    Ip_fd_set *read_set = IP_NULL;
    struct Ip_timeval tv;
    long    timeout = 5;
    VOS_UINT8       *pucRcvBuf  = VOS_NULL_PTR;
    struct Ip_sockaddr_in   stInAddr;
    Ip_s32 sock1, sock2, count, num;
    IMS_NIC_IPV4_HDR    *pstIpHead;
    IMS_NIC_UDP_HDR     *pstUdpHead;
    VOS_UINT8            aucTmp[4];
    char *cmd_str           = "ifconfig -a";
    int i;
    int rcvNum  = 0;

    ST_IMS_NIC_RegUlCb();

    /* 配置第一个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 5;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    /* 配置第二个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = 6;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr2, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr2, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr2, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: config pdn fail! ulResult = %d\n", ulResult);
        IMS_NIC_PdnInfoDel(5, 0);
        return;
    }

    ipcom_run_cmd(cmd_str);

    /* Get a socket */
    sock1 = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
    if (sock1 < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: Get socket failed!\n");
        IMS_NIC_PdnInfoDel(5, 0);
        IMS_NIC_PdnInfoDel(6, 0);
        return;
    }

    /* Bind the socket */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    //stInAddr.sin_addr.s_addr = IP_INADDR_ANY;
    ipcom_memcpy(&stInAddr.sin_addr, aucSrcIpAddr1, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = 0;
    if (ipcom_bind(sock1, (struct Ip_sockaddr*) &stInAddr, sizeof(struct Ip_sockaddr)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: bind socket failed!\n");
        ipcom_socketclose(sock1);
        IMS_NIC_PdnInfoDel(5, 0);
        IMS_NIC_PdnInfoDel(6, 0);
        return;
    }

    /* Send the data */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    ipcom_memcpy(&stInAddr.sin_addr, aucDstIpAddr1, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = usImsNicPort;

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        count = ipcom_sendto(sock1, (void*)aucIpData1, s_size, 0,
                             (struct Ip_sockaddr *) &stInAddr,
                             sizeof(struct Ip_sockaddr_in));

        (VOS_VOID)vos_printf("sock1: ipcom_sendto [%d] count = %d !\n", i, count);
    }

    /* Get another socket */
    sock2 = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
    if (sock2 < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: Get socket failed!\n");
        ipcom_socketclose(sock1);
        IMS_NIC_PdnInfoDel(5, 0);
        IMS_NIC_PdnInfoDel(6, 0);
        return;
    }

    /* Bind the socket */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    //stInAddr.sin_addr.s_addr = IP_INADDR_ANY;
    ipcom_memcpy(&stInAddr.sin_addr, aucSrcIpAddr2, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = 0;
    if (ipcom_bind(sock2, (struct Ip_sockaddr*) &stInAddr, sizeof(struct Ip_sockaddr)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: bind socket failed!\n");
        goto out;
    }

    /* Send the data */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    ipcom_memcpy(&stInAddr.sin_addr, aucDstIpAddr2, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = usImsNicPort;

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        count = ipcom_sendto(sock2, (void*)aucIpData2, s_size, 0,
                             (struct Ip_sockaddr *) &stInAddr,
                             sizeof(struct Ip_sockaddr_in));

        (VOS_VOID)vos_printf("sock2: ipcom_sendto [%d] count = %d !\n", i, count);
    }

    /* Prepare the read set */
    read_set = ipcom_malloc(sizeof(Ip_fd_set));
    if (read_set == IP_NULL)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006: Prepare read set failed!\n");
        goto out;
    }
    ipcom_memset(read_set, 0, sizeof(Ip_fd_set));

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    /* 等待两秒 */
    VOS_TaskDelay(ST_IMS_NIC_WAIT_TIME);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if ( ulQCnt != 4 )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_006, Fail! ulQCnt = %d!\r\n", ulQCnt);
        goto out;
    }

    for (i = 0; i < (VOS_INT)ulQCnt; i++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_006, Fail! Q is empty!\r\n");
            goto out;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_006, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            goto out;
        }

        if ( 0 != (VOS_MemCmp(aucIpData1, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN -1))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_006, Fail! data not match!\r\n");
        }
        else
        {
            (VOS_VOID)vos_printf("rcv :ip & udp hdr :");
            ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);
        }

        pstIpHead   = (IMS_NIC_IPV4_HDR*)pstTtfMem->pData;
        VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 4);
        VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 4);
        VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 4);
        pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV4_HEADER_LEN);
        VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
        VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
        VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);

        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

        (VOS_VOID)vos_printf("send: ip & udp hdr :");
        ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }

    /* Wait for the response */
    /*lint -e573*/
    IP_FD_SET(sock1, read_set);
    /*lint +e573*/

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)ipcom_malloc((unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));
    if (pucRcvBuf == IP_NULL)
    {
        goto out;
    }

    for (;;)
    {
        num = ipcom_socketselect(sock1+1, read_set, IP_NULL, IP_NULL, &tv);
        if (num == IP_SOCKERR)
        {
            (VOS_VOID)vos_printf("sock1: socketselect failed!\n");
            goto out;
        }

        /* Get buffer memory. */
        ipcom_memset(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (num == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock1: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (num > 0 && IP_FD_ISSET(sock1, read_set))
        /*lint +e573*/
        {
            /* Data available */
            count = ipcom_recvfrom(sock1, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN, 0, IP_NULL, IP_NULL);
        }
        else
        {
            (VOS_VOID)vos_printf("sock1: error!\n");
            goto out;
        }

        if (count == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

            if ( 0 != (VOS_MemCmp(aucIpData1, pucRcvBuf, (VOS_UINT32)count)) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_006: sock1, Fail! data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock1, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("ST_IMS_NIC_006: ipcom_recvfrom from sock1 count = %d !\n", count);
    }

    (VOS_VOID)vos_printf("rcv data from sock1, rcvNum= %d!\r\n", rcvNum);
    if (rcvNum != 2)
    {
        goto out;
    }
    rcvNum  = 0;

    ipcom_memset(read_set, 0, sizeof(Ip_fd_set));

    /* Wait for the second response */
    /*lint -e573*/
    IP_FD_SET(sock2, read_set);
    /*lint +e573*/

    for (;;)
    {
        num = ipcom_socketselect(sock2+1, read_set, IP_NULL, IP_NULL, &tv);
        if (num == IP_SOCKERR)
        {
            (VOS_VOID)vos_printf("sock2: socketselect failed!\n");
            goto out;
        }

        /* Get buffer memory. */
        ipcom_memset(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (num == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock2: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (num > 0 && IP_FD_ISSET(sock2, read_set))
        /*lint +e573*/
        {
            /* Data available */
            count = ipcom_recvfrom(sock2, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN, 0, IP_NULL, IP_NULL);
        }
        else
        {
            (VOS_VOID)vos_printf("sock2: error!\n");
            goto out;
        }

        if (count == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

            if ( 0 != (VOS_MemCmp(aucIpData2, pucRcvBuf, (VOS_UINT32)count)) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_006:sock2, Fail! data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock2, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock2: ipcom_recvfrom from sock2 count = %d !\n", count);
    }

    if (rcvNum != 2)
    {
        (VOS_VOID)vos_printf("recvfrom data num= %d not equal 2!\r\n", rcvNum);
        goto out;
    }
    (VOS_VOID)vos_printf("ST_IMS_NIC_006: Pass!\r\n");

out:
    /*lint -e961*/
    if (pucRcvBuf != VOS_NULL_PTR)
    {
        ipcom_free(pucRcvBuf);
    }
    if (read_set != IP_NULL)
    {
        ipcom_free(read_set);
    }
    ipcom_socketclose(sock1);
    ipcom_socketclose(sock2);
    ST_IMS_NIC_ClrQ();
    /* 删除虚拟网卡配置 */
    IMS_NIC_PdnInfoDel(5, 0);
    IMS_NIC_PdnInfoDel(6, 0);
    /*lint +e961*/
    return;
}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_007
 功能描述  : 网卡配置两个IP,分别通过socket bind IPV6地址，发送2块数据给不同网段地址，CDS匹配数据，
             匹配后CDS将数据发送回协议栈，上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_007(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[16]            = {0x21, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr1[16]            = {0x22, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr1[16]          = {0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr1[16]           = {0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucSrcIpAddr2[16]            = {0x23, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr2[16]            = {0x24, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr2[16]          = {0x4, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr2[16]           = {0x5, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort            = 1007;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData1[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x77
    };

    VOS_UINT8               aucIpData2[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x88
    };

    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData1);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    Ip_fd_set *read_set = IP_NULL;
    struct Ip_timeval tv;
    long    timeout = 5;
    VOS_UINT8       *pucRcvBuf  = VOS_NULL_PTR;
    struct Ip_sockaddr_in6      in_addr6;
    Ip_s32 sock1, sock2, count, num;
    IMS_NIC_IPV6_HDR    *pstIpHead;
    IMS_NIC_UDP_HDR     *pstUdpHead;
    VOS_UINT8            aucTmp[16];
    char *cmd_str           = "ifconfig -a";
    int i;
    VOS_UINT8       ucRabId1    = 7;
    VOS_UINT8       ucRabId2    = 8;
    VOS_UINT16      usMaxPort1  = 65534;
    VOS_UINT16      usMinPort1  = 1;
    VOS_UINT16      usMaxPort2  = 19000;
    VOS_UINT16      usMinPort2  = 2;
    VOS_UINT16      usExpectMinPort = 0;
    VOS_UINT16      usExpectMaxPort = 0;
    int rcvNum  = 0;
    const VOS_CHAR  *pcMinPortCmd = "ipnet.sock.AnonPortMin";
    const VOS_CHAR  *pcMaxPortCmd = "ipnet.sock.AnonPortMax";
    VOS_UINT16       usSize = 2;
    VOS_CHAR        *pcValue;


    ST_IMS_NIC_RegUlCb();

    /* 配置第一个IPV6地址 */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.bitOpSockPortInfo  = PS_TRUE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr1, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 16);

    stConfigInfo.stSockPortInfo.usSockMaxPort       = usMaxPort1;
    stConfigInfo.stSockPortInfo.usSockMinPort       = usMinPort1;

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    pcValue = ipcom_sysvar_get(pcMinPortCmd, 0, 0);
    usExpectMinPort = (VOS_UINT16)atoi(pcValue);
    ipcom_free(pcValue);

    pcValue = ipcom_sysvar_get(pcMaxPortCmd, 0, 0);
    usExpectMaxPort = (VOS_UINT16)atoi(pcValue);
    ipcom_free(pcValue);

    (VOS_VOID)vos_printf("ST_IMS_NIC_007:first config MinPort = %d, MaxPort = %d\n", usExpectMinPort, usExpectMaxPort);

    if ((usMinPort1 != usExpectMinPort) || (usMaxPort1 != usExpectMaxPort))
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: config socket port fail!\n");
        return;
    }

    /* 配置第二个IPV6地址 */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.bitOpSockPortInfo  = PS_TRUE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId2;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr2, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr2, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr2, 16);

    stConfigInfo.stSockPortInfo.usSockMaxPort       = usMaxPort2;
    stConfigInfo.stSockPortInfo.usSockMinPort       = usMinPort2;

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: config pdn fail! ulResult = %d\n", ulResult);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        return;
    }

    pcValue = ipcom_sysvar_get(pcMinPortCmd, 0, 0);
    usExpectMinPort = (VOS_UINT16)atoi(pcValue);
    ipcom_free(pcValue);

    pcValue = ipcom_sysvar_get(pcMaxPortCmd, 0, 0);
    usExpectMaxPort = (VOS_UINT16)atoi(pcValue);
    ipcom_free(pcValue);

    (VOS_VOID)vos_printf("ST_IMS_NIC_007:sec config MinPort = %d, MaxPort = %d\n", usExpectMinPort, usExpectMaxPort);

    if ((usMinPort1 != usExpectMinPort) || (usMaxPort1 != usExpectMaxPort))
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007:socket port can not config twice!\n");
        return;
    }

    ipcom_run_cmd(cmd_str);

    /* Get a socket */
    sock1 = ipcom_socket(IP_AF_INET6, IP_SOCK_DGRAM, 0);
    if (sock1 < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: Get socket1 failed!\n");
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Bind the socket */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    //in_addr6.sin6_addr = in6addr_any;
    ipcom_memcpy(&in_addr6.sin6_addr, aucSrcIpAddr1, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_port = 0;
    if (ipcom_bind(sock1, (struct Ip_sockaddr*)&in_addr6, sizeof(struct Ip_sockaddr_in6)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: bind socket1 failed!\n");
        ipcom_socketclose(sock1);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Send the data */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    ipcom_memcpy(&in_addr6.sin6_addr, aucDstIpAddr1, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_scope_id = 0;
    in_addr6.sin6_port = usImsNicPort;

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        count = ipcom_sendto(sock1, (void*)aucIpData1, s_size, 0,
                             (struct Ip_sockaddr *) &in_addr6,
                             sizeof(struct Ip_sockaddr_in6));

        (VOS_VOID)vos_printf("sock1: ipcom_sendto[%d] count = %d !\n",i, count);
    }

    /* Get another socket */
    sock2 = ipcom_socket(IP_AF_INET6, IP_SOCK_DGRAM, 0);
    if (sock2 < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: Get socket2 failed!\n");
        ipcom_socketclose(sock1);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Bind the socket */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    //in_addr6.sin6_addr = in6addr_any;
    ipcom_memcpy(&in_addr6.sin6_addr, aucSrcIpAddr2, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_port = 0;
    if (ipcom_bind(sock2, (struct Ip_sockaddr*)&in_addr6, sizeof(struct Ip_sockaddr_in6)) < 0)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: bind socket2 failed!\n");
        goto out;
    }

    /* Send the data */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    ipcom_memcpy(&in_addr6.sin6_addr, aucDstIpAddr2, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_scope_id = 0;
    in_addr6.sin6_port = usImsNicPort;

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        count = ipcom_sendto(sock2, (void*)aucIpData2, s_size, 0,
                             (struct Ip_sockaddr *) &in_addr6,
                             sizeof(struct Ip_sockaddr_in6));

        (VOS_VOID)vos_printf("sock2: ipcom_sendto[%d] count = %d !\n",i, count);
    }

    /* Prepare the read set */
    read_set = ipcom_malloc(sizeof(Ip_fd_set));
    if (read_set == IP_NULL)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007: Prepare read set failed!\n");
        goto out;
    }
    ipcom_memset(read_set, 0, sizeof(Ip_fd_set));

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    /* 等待两秒 */
    VOS_TaskDelay(ST_IMS_NIC_WAIT_TIME);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if ( ulQCnt != 4 )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_007, Fail! ulQCnt = %d!\r\n", ulQCnt);
        goto out;
    }

    for (i = 0; i < (VOS_INT)ulQCnt; i++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_007, Fail! Q is empty!\r\n");
            goto out;
        }

        if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_V6_LEN)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_007, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
            TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
            goto out;
        }

        if ( 0 != (VOS_MemCmp(aucIpData1, pstTtfMem->pData + ST_IMS_NIC_HEADER_V6_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_V6_LEN -1))) )
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_007, Fail! UL data not match!\r\n");
        }
        else
        {
            (VOS_VOID)vos_printf("rcv :ip & udp hdr :");
            ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_V6_LEN);
        }

        pstIpHead   = (IMS_NIC_IPV6_HDR*)pstTtfMem->pData;
        VOS_MemCpy(aucTmp, pstIpHead->aucDstIp, 16);
        VOS_MemCpy(pstIpHead->aucDstIp, pstIpHead->aucSrcIp, 16);
        VOS_MemCpy(pstIpHead->aucSrcIp, aucTmp, 16);
        pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV6_HEADER_LEN);
        VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
        VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
        VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);

        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);

        (VOS_VOID)vos_printf("send: ip & udp hdr :");
        ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_V6_LEN);

        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }

    /* Wait for the response */
    /*lint -e573*/
    IP_FD_SET(sock1, read_set);
    /*lint +e573*/

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)ipcom_malloc((unsigned int)(s_size + ST_IMS_NIC_HEADER_V6_LEN));
    if (pucRcvBuf == IP_NULL)
    {
        goto out;
    }

    for (;;)
    {
        num = ipcom_socketselect(sock1+1, read_set, IP_NULL, IP_NULL, &tv);
        if (num == IP_SOCKERR)
        {
            (VOS_VOID)vos_printf("sock1: socketselect failed!\n");
            goto out;
        }

        /* Get buffer memory. */
        ipcom_memset(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_V6_LEN));

        if (num == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock1: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (num > 0 && IP_FD_ISSET(sock1, read_set))
        /*lint +e573*/
        {
            /* Data available */
            count = ipcom_recvfrom(sock1, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_V6_LEN, 0, IP_NULL, IP_NULL);
        }
        else
        {
            (VOS_VOID)vos_printf("sock1: error!\n");
            goto out;
        }

        if (count == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

            if ( 0 != (VOS_MemCmp(aucIpData1, pucRcvBuf, (VOS_UINT32)count)) )
            {
                (VOS_VOID)vos_printf("sock1, Fail! DL data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock1, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock1: ipcom_recvfrom from sock1 count = %d !\n", count);
    }

    (VOS_VOID)vos_printf("rcv data from sock1, rcvNum= %d!\r\n", rcvNum);
    if (rcvNum != 2)
    {
        goto out;
    }
    rcvNum  = 0;

    /* Wait for the second response */
    /*lint -e573*/
    IP_FD_SET(sock2, read_set);
    /*lint +e573*/
    for (;;)
    {
        num = ipcom_socketselect(sock2+1, read_set, IP_NULL, IP_NULL, &tv);
        if (num == IP_SOCKERR)
        {
            (VOS_VOID)vos_printf("sock2: socketselect failed!\n");
            goto out;
        }

        /* Get buffer memory. */
        ipcom_memset(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_V6_LEN));

        if (num == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock2: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (num > 0 && IP_FD_ISSET(sock2, read_set))
        /*lint +e573*/
        {
            /* Data available */
            count = ipcom_recvfrom(sock2, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_V6_LEN, 0, IP_NULL, IP_NULL);
        }
        else
        {
            (VOS_VOID)vos_printf("sock2: error!\n");
            goto out;
        }

        if (count == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

            if ( 0 != (VOS_MemCmp(aucIpData2, pucRcvBuf, (VOS_UINT32)count)) )
            {
                (VOS_VOID)vos_printf("sock2, Fail! DL data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock2, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock2: ipcom_recvfrom from sock2 count = %d !\n", count);
    }

    if (rcvNum != 2)
    {
        (VOS_VOID)vos_printf("recvfrom data num= %d not equal 2!\r\n", rcvNum);
        goto out;
    }
    (VOS_VOID)vos_printf("ST_IMS_NIC_007: Pass!\r\n");

out:
    /*lint -e961*/
    if (pucRcvBuf != VOS_NULL_PTR)
    {
        ipcom_free(pucRcvBuf);
    }
    if (read_set != IP_NULL)
    {
        ipcom_free(read_set);
    }
    ipcom_socketclose(sock1);
    ipcom_socketclose(sock2);
    ST_IMS_NIC_ClrQ();
    /* 删除虚拟网卡配置 */
    IMS_NIC_PdnInfoDel(ucRabId1, 0);
    IMS_NIC_PdnInfoDel(ucRabId2, 0);
    /*lint +e961*/
    return;
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_008
 功能描述  : 网卡配置两个IP，一个IPV4，一个IPV6,分别通过socket bind 该两个地址，
             发送2块数据给不同网段地址，CDS匹配数据，匹配后CDS将数据发送回协议栈，
             上层通过socket接收
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_008(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDstIpAddr1[4]            = {0xA0, 0xA8, 0x02, 0x07};
    VOS_UINT8                       aucDnsPrimAddr1[4]          = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr1[4]           = {0xC0, 0xA8, 0x05, 0x02};
    VOS_UINT8                       aucSrcIpAddr2[16]            = {0x23, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};         /* 128-bit IP address */
    VOS_UINT8                       aucDstIpAddr2[16]            = {0x24, 0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr2[16]          = {0x4, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    VOS_UINT8                       aucDnsSecAddr2[16]           = {0x5, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    VOS_UINT32                      ulResult;
    VOS_UINT16                      usImsNicPort            = 1002;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData1[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x55,0x66
    };

    VOS_UINT8               aucIpData2[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
        0x11,0x22,0x33,0x44,0x55,0x77
    };

    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData1);
    TTF_MEM_ST             *pstTtfMem   = VOS_NULL_PTR;
    VOS_UINT32              ulQCnt;
    Ip_fd_set *read_set = IP_NULL;
    struct Ip_timeval tv;
    long    timeout = 5;
    VOS_UINT8       *pucRcvBuf  = VOS_NULL_PTR;
    struct Ip_sockaddr_in   stInAddr;
    struct Ip_sockaddr_in6      in_addr6;
    Ip_s32 sock1, sock2, count, num;
    IMS_NIC_IPV4_HDR    *pstIpV4Head;
    IMS_NIC_IPV6_HDR    *pstIpV6Head;
    IMS_NIC_UDP_HDR     *pstUdpHead;
    VOS_UINT8            aucTmp[16];
    char *cmd_str           = "ifconfig -a";
    int i;
    VOS_UINT8       ucRabId1    = 9;
    VOS_UINT8       ucRabId2    = 10;
    int rcvNum  = 0;
    VOS_UINT8       ucIpType;
    VOS_UINT8       *pucData;

    ST_IMS_NIC_RegUlCb();

    /* 配置第一个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    /* 配置第二个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId2;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr2, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr2, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr2, 16);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("config pdn fail! ulResult = %d\n", ulResult);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        return;
    }

    ipcom_run_cmd(cmd_str);

    /* Get a socket */
    sock1 = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
    if (sock1 < 0)
    {
        (VOS_VOID)vos_printf("Get socket failed!\n");
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Bind the socket */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    //stInAddr.sin_addr.s_addr = IP_INADDR_ANY;
    ipcom_memcpy(&stInAddr.sin_addr, aucSrcIpAddr1, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = 0;
    if (ipcom_bind(sock1, (struct Ip_sockaddr*) &stInAddr, sizeof(struct Ip_sockaddr)) < 0)
    {
        (VOS_VOID)vos_printf("bind socket failed!\n");
        ipcom_socketclose(sock1);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Send the data */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    ipcom_memcpy(&stInAddr.sin_addr, aucDstIpAddr1, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = usImsNicPort;

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        count = ipcom_sendto(sock1, (void*)aucIpData1, s_size, 0,
                             (struct Ip_sockaddr *) &stInAddr,
                             sizeof(struct Ip_sockaddr_in));

        (VOS_VOID)vos_printf("sock1: ipcom_sendto [%d] count = %d !\n", i, count);
    }

    /* Get another socket */
    sock2 = ipcom_socket(IP_AF_INET6, IP_SOCK_DGRAM, 0);
    if (sock2 < 0)
    {
        (VOS_VOID)vos_printf("Get socket2 failed!\n");
        ipcom_socketclose(sock1);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        IMS_NIC_PdnInfoDel(ucRabId2, 0);
        return;
    }

    /* Bind the socket */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    //in_addr6.sin6_addr = in6addr_any;
    ipcom_memcpy(&in_addr6.sin6_addr, aucSrcIpAddr2, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_port = 0;
    if (ipcom_bind(sock2, (struct Ip_sockaddr*)&in_addr6, sizeof(struct Ip_sockaddr_in6)) < 0)
    {
        (VOS_VOID)vos_printf("bind socket2 failed!\n");
        goto out;
    }

    /* Send the data */
    ipcom_memset(&in_addr6, 0, sizeof(struct Ip_sockaddr_in6));
    IPCOM_SA_LEN_SET(&in_addr6, sizeof(struct Ip_sockaddr_in6));
    in_addr6.sin6_family = IP_AF_INET6;
    ipcom_memcpy(&in_addr6.sin6_addr, aucDstIpAddr2, sizeof(in_addr6.sin6_addr));
    in_addr6.sin6_scope_id = 0;
    in_addr6.sin6_port = usImsNicPort;

    /* 发送2遍 */
    for (i = 0; i < 2; i++)
    {
        count = ipcom_sendto(sock2, (void*)aucIpData2, s_size, 0,
                             (struct Ip_sockaddr *) &in_addr6,
                             sizeof(struct Ip_sockaddr_in6));

        (VOS_VOID)vos_printf("sock2: ipcom_sendto[%d] count = %d !\n",i, count);
    }

    /* Prepare the read set */
    read_set = ipcom_malloc(sizeof(Ip_fd_set));
    if (read_set == IP_NULL)
    {
        (VOS_VOID)vos_printf("Prepare read set failed!\n");
        goto out;
    }
    ipcom_memset(read_set, 0, sizeof(Ip_fd_set));

    /* Set the timeout */
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    /* 等待两秒 */
    VOS_TaskDelay(ST_IMS_NIC_WAIT_TIME);

    ulQCnt  = TTF_LinkCnt(UEPS_PID_IMSNIC, &g_stImsNicQ);
    if ( ulQCnt != 4 )
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_008, Fail! ulQCnt = %d!\r\n", ulQCnt);
        goto out;
    }

    for (i = 0; i < (VOS_INT)ulQCnt; i++)
    {
        /* 队列中取数 */
        pstTtfMem = (TTF_MEM_ST *)TTF_LinkRemoveHead(UEPS_PID_IMSNIC, &g_stImsNicQ);
        if (pstTtfMem == VOS_NULL_PTR)
        {
            (VOS_VOID)vos_printf("ST_IMS_NIC_008, Fail! Q is empty!\r\n");
            goto out;
        }

        pucData = pstTtfMem->pData;
        /* 解析IP包的版本号 */
        ucIpType    = ((pucData[0] >> IMS_NIC_IP_VERSION_POS) & IMS_NIC_IP_VERSION_MASK);
        if (IMS_NIC_IPV4_VERSION == ucIpType)
        {
            if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_LEN)
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
                TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
                goto out;
            }

            if ( 0 != (VOS_MemCmp(aucIpData1, pstTtfMem->pData + ST_IMS_NIC_HEADER_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_LEN -1))) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008, Fail! UL IPV4 data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("rcv :ip & udp hdr :");
                ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_LEN);
            }

            pstIpV4Head   = (IMS_NIC_IPV4_HDR*)pstTtfMem->pData;
            VOS_MemCpy(aucTmp, pstIpV4Head->aucDstIp, 4);
            VOS_MemCpy(pstIpV4Head->aucDstIp, pstIpV4Head->aucSrcIp, 4);
            VOS_MemCpy(pstIpV4Head->aucSrcIp, aucTmp, 4);
            pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV4_HEADER_LEN);
            VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
            VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
            VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);
        }
        else if (IMS_NIC_IPV6_VERSION == ucIpType)
        {
            if ( pstTtfMem->usUsed  != s_size + ST_IMS_NIC_HEADER_V6_LEN)
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008, Fail! data len not match!pstTtfMem->usUsed = %d\r\n", pstTtfMem->usUsed);
                TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
                goto out;
            }

            if ( 0 != (VOS_MemCmp(aucIpData1, pstTtfMem->pData + ST_IMS_NIC_HEADER_V6_LEN, (VOS_UINT32)(pstTtfMem->usUsed - ST_IMS_NIC_HEADER_V6_LEN -1))) )
            {
                (VOS_VOID)vos_printf("ST_IMS_NIC_008, Fail! UL IPV6 data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("rcv :ip & udp hdr :");
                ST_IMS_NIC_PrintData(pstTtfMem->pData, ST_IMS_NIC_HEADER_V6_LEN);
            }

            pstIpV6Head   = (IMS_NIC_IPV6_HDR*)pstTtfMem->pData;
            VOS_MemCpy(aucTmp, pstIpV6Head->aucDstIp, 16);
            VOS_MemCpy(pstIpV6Head->aucDstIp, pstIpV6Head->aucSrcIp, 16);
            VOS_MemCpy(pstIpV6Head->aucSrcIp, aucTmp, 16);
            pstUdpHead  = (IMS_NIC_UDP_HDR*)(pstTtfMem->pData + ST_IMS_NIC_IPV6_HEADER_LEN);
            VOS_MemCpy(aucTmp, &pstUdpHead->usDstPort, 2);
            VOS_MemCpy(&pstUdpHead->usDstPort, &pstUdpHead->usSrcPort, 2);
            VOS_MemCpy(&pstUdpHead->usSrcPort, aucTmp, 2);
        }
        else
        {
            (VOS_VOID)vos_printf("rcv error ip pkt\n");
        }

        IMS_NIC_DlDataRcv(pstTtfMem->pData, pstTtfMem->usUsed, 0);
        TTF_MemFree(UEPS_PID_IMSNIC, pstTtfMem);
    }

    /* Wait for the response */
    /*lint -e573*/
    IP_FD_SET(sock1, read_set);
    /*lint +e573*/

    /* Get buffer memory. */
    pucRcvBuf = (VOS_UINT8 *)ipcom_malloc((unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));
    if (pucRcvBuf == IP_NULL)
    {
        goto out;
    }

    for (;;)
    {
        num = ipcom_socketselect(sock1+1, read_set, IP_NULL, IP_NULL, &tv);
        if (num == IP_SOCKERR)
        {
            (VOS_VOID)vos_printf("sock1: socketselect failed!\n");
            goto out;
        }

        /* Get buffer memory. */
        ipcom_memset(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (num == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock1: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (num > 0 && IP_FD_ISSET(sock1, read_set))
        /*lint +e573*/
        {
            /* Data available */
            count = ipcom_recvfrom(sock1, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN, 0, IP_NULL, IP_NULL);
        }
        else
        {
            (VOS_VOID)vos_printf("sock1: error!\n");
            goto out;
        }

        if (count == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

            if ( 0 != (VOS_MemCmp(aucIpData1, pucRcvBuf, (VOS_UINT32)count)) )
            {
                (VOS_VOID)vos_printf("sock1, Fail! DL data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock1, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock1: ipcom_recvfrom from sock1 count = %d !\n", count);
    }

    (VOS_VOID)vos_printf("rcv data from sock1, rcvNum= %d!\r\n", rcvNum);
    if (rcvNum != 2)
    {
        goto out;
    }
    rcvNum  = 0;

    /* Wait for the second response */
    /*lint -e573*/
    IP_FD_SET(sock2, read_set);
    /*lint +e573*/
    for (;;)
    {
        num = ipcom_socketselect(sock2+1, read_set, IP_NULL, IP_NULL, &tv);
        if (num == IP_SOCKERR)
        {
            (VOS_VOID)vos_printf("sock2: socketselect failed!\n");
            goto out;
        }

        /* Get buffer memory. */
        ipcom_memset(pucRcvBuf, 0, (unsigned int)(s_size + ST_IMS_NIC_HEADER_LEN));

        if (num == 0)
        {
            /* Timeout */
            (VOS_VOID)vos_printf("sock2: Timeout!\n");
            break;
        }
        /*lint -e573*/
        else if (num > 0 && IP_FD_ISSET(sock2, read_set))
        /*lint +e573*/
        {
            /* Data available */
            count = ipcom_recvfrom(sock2, (void*)pucRcvBuf, s_size + ST_IMS_NIC_HEADER_LEN, 0, IP_NULL, IP_NULL);
        }
        else
        {
            (VOS_VOID)vos_printf("sock2: error!\n");
            goto out;
        }

        if (count == s_size)
        {
            ST_IMS_NIC_PrintData(pucRcvBuf, (VOS_UINT16)count);

            if ( 0 != (VOS_MemCmp(aucIpData2, pucRcvBuf, (VOS_UINT32)count)) )
            {
                (VOS_VOID)vos_printf("sock2, Fail! UL data not match!\r\n");
            }
            else
            {
                (VOS_VOID)vos_printf("sock2, data match!\r\n");
                rcvNum++;
            }
        }

        (VOS_VOID)vos_printf("sock2: ipcom_recvfrom from sock2 count = %d !\n", count);
    }

    if (rcvNum != 2)
    {
        (VOS_VOID)vos_printf("recvfrom data num= %d not equal 2!\r\n", rcvNum);
        goto out;
    }
    (VOS_VOID)vos_printf("ST_IMS_NIC_008: Pass!\r\n");

out:
    /*lint -e961*/
    if (pucRcvBuf != VOS_NULL_PTR)
    {
        ipcom_free(pucRcvBuf);
    }
    if (read_set != IP_NULL)
    {
        ipcom_free(read_set);
    }
    ipcom_socketclose(sock1);
    ipcom_socketclose(sock2);
    ST_IMS_NIC_ClrQ();
    /* 删除虚拟网卡配置 */
    IMS_NIC_PdnInfoDel(ucRabId1, 0);
    IMS_NIC_PdnInfoDel(ucRabId2, 0);
    /*lint +e961*/
    return;
}

VOS_VOID ST_IMS_NIC_009(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x02, 0x05};
    VOS_UINT8                       aucDnsPrimAddr1[4]          = {0xC0, 0xA8, 0x05, 0x01};
    VOS_UINT8                       aucDnsSecAddr1[4]           = {0xC0, 0xA8, 0x05, 0x02};
    VOS_UINT8                       aucSrcIpAddr2[4]            = {0xC0, 0xA8, 0x03, 0x05};
    VOS_UINT8                       aucDnsPrimAddr2[4]          = {0xC0, 0xA8, 0x05, 0x03};
    VOS_UINT8                       aucDnsSecAddr2[4]           = {0xC0, 0xA8, 0x05, 0x04};

    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 5;
    VOS_UINT8   ucRabId2    = 6;
    char *cmd_str           = "ifconfig -a";

    ST_IMS_NIC_RegUlCb();

    /* 配置第一个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_009: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    /* 配置第二个IP */
    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId2;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr2, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_TRUE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr2, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr2, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_IMS_NIC_009: config pdn fail! ulResult = %d\n", ulResult);
        IMS_NIC_PdnInfoDel(ucRabId1, 0);
        return;
    }

    ipcom_run_cmd(cmd_str);

    return;
}

VOS_VOID ST_UL_SEND_001(VOS_UINT8 ucIpAddr, VOS_UINT8 ulSendCnt, VOS_UINT32 ulTime)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x33, 0};
    VOS_UINT8                       aucDstIpAddr1[4]            = {0xC0, 0xA8, 0x1E, 0x65};

    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 5;
    char *cmd_str           = "ifconfig -a";
    VOS_UINT16                      usImsNicPort            = 100;            /* 16-bit port number */
    /*lint -e813*/
    VOS_UINT8               aucIpData[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
    };
    /*lint +e813*/
    VOS_INT                 s_size    = sizeof(aucIpData);
    Ip_s32                  sock, count;
    struct Ip_sockaddr_in   stInAddr;
    VOS_UINT32 i;

    aucSrcIpAddr1[3]        = ucIpAddr;

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_FALSE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_FALSE;

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_UL_SEND_001: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    ipcom_run_cmd(cmd_str);

    /* Get a socket */
    sock = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
    if (sock < 0)
    {
        /* 删除虚拟网卡配置 */
        IMS_NIC_PdnInfoDel(stConfigInfo.ucRabId, 0);
        (VOS_VOID)vos_printf("ST_UL_SEND_001: Get socket failed!\n");
        return;
    }

    /* Bind the socket */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    //stInAddr.sin_addr.s_addr = IP_INADDR_ANY;
    ipcom_memcpy(&stInAddr.sin_addr, aucSrcIpAddr1, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = 0;
    if (ipcom_bind(sock, (struct Ip_sockaddr*) &stInAddr, sizeof(struct Ip_sockaddr)) < 0)
    {
        (VOS_VOID)vos_printf("ST_UL_SEND_001: bind socket failed!\n");
        goto out;
    }

    /* Send the data */
    ipcom_memset(&stInAddr, 0, sizeof(struct Ip_sockaddr_in));
    IPCOM_SA_LEN_SET(&stInAddr, sizeof(struct Ip_sockaddr_in));
    stInAddr.sin_family = IP_AF_INET;
    ipcom_memcpy(&stInAddr.sin_addr, aucDstIpAddr1, sizeof(stInAddr.sin_addr));
    stInAddr.sin_port = usImsNicPort;

    /* 发送5遍 */
    for (i = 0; i < ulSendCnt; i++)
    {
        count = ipcom_sendto(sock, (void*)aucIpData, s_size, 0,
                             (struct Ip_sockaddr *) &stInAddr,
                             sizeof(struct Ip_sockaddr_in));

        if ( count !=  s_size)
        {
            (VOS_VOID)vos_printf("ST_UL_SEND_001: ipcom_sendto [%d] count = %d !\n", i, count);
        }

        VOS_TaskDelay(ulTime);
    }

out:
    /*lint -e961*/
    ipcom_socketclose(sock);
    IMS_NIC_PdnInfoDel(stConfigInfo.ucRabId, 0);
    /*lint +e961*/

    return;
}

VOS_VOID ST_DL_RCV_001(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[4]            = {0xac, 0x14, 0x80, 0x06};
    VOS_UINT8                       aucDstIpAddr1[4]            = {0x2, 0x1, 0x15, 0x27};

    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 5;
    char *cmd_str           = "ifconfig -a";

    /*lint -e813*/
    VOS_UINT8               aucIpData1[] =
    {
        0x45, 0x00,
        0x01, 0x39, 0x11, 0xe2, 0x00, 0x00, 0xfe, 0x11, 0x66, 0x8f, 0xac, 0x14, 0x80, 0x06, 0x02, 0x01,
        0x15, 0x27, 0x13, 0xc4, 0xf8, 0x09, 0x01, 0x25, 0x00, 0x00, 0x53, 0x49, 0x50, 0x2f, 0x32, 0x2e,
        0x30, 0x20, 0x31, 0x30, 0x30, 0x20, 0x54, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x0d, 0x0a, 0x56, 0x69,
        0x61, 0x3a, 0x20, 0x53, 0x49, 0x50, 0x2f, 0x32, 0x2e, 0x30, 0x2f, 0x55, 0x44, 0x50, 0x20, 0x32,
        0x2e, 0x31, 0x2e, 0x32, 0x31, 0x2e, 0x33, 0x39, 0x3a, 0x36, 0x33, 0x34, 0x39, 0x37, 0x3b, 0x62,
        0x72, 0x61, 0x6e, 0x63, 0x68, 0x3d, 0x7a, 0x39, 0x68, 0x47, 0x34, 0x62, 0x4b, 0x63, 0x6f, 0x65,
        0x63, 0x62, 0x56, 0x39, 0x3b, 0x72, 0x70, 0x6f, 0x72, 0x74, 0x3d, 0x36, 0x33, 0x34, 0x39, 0x37,
        0x0d, 0x0a, 0x43, 0x61, 0x6c, 0x6c, 0x2d, 0x49, 0x44, 0x3a, 0x20, 0x61, 0x6d, 0x65, 0x63, 0x62,
        0x56, 0x39, 0x63, 0x4a, 0x40, 0x32, 0x2e, 0x31, 0x2e, 0x32, 0x31, 0x2e, 0x33, 0x39, 0x0d, 0x0a,
        0x46, 0x72, 0x6f, 0x6d, 0x3a, 0x20, 0x3c, 0x73, 0x69, 0x70, 0x3a, 0x2b, 0x38, 0x36, 0x31, 0x33,
        0x31, 0x30, 0x30, 0x30, 0x30, 0x31, 0x30, 0x33, 0x39, 0x40, 0x68, 0x69, 0x73, 0x69, 0x2e, 0x63,
        0x6f, 0x6d, 0x3e, 0x3b, 0x74, 0x61, 0x67, 0x3d, 0x62, 0x6e, 0x65, 0x63, 0x62, 0x56, 0x39, 0x0d,
        0x0a, 0x54, 0x6f, 0x3a, 0x20, 0x22, 0x31, 0x33, 0x31, 0x30, 0x30, 0x30, 0x30, 0x32, 0x31, 0x30,
        0x31, 0x22, 0x3c, 0x73, 0x69, 0x70, 0x3a, 0x31, 0x33, 0x31, 0x30, 0x30, 0x30, 0x30, 0x32, 0x31,
        0x30, 0x31, 0x40, 0x69, 0x6d, 0x73, 0x2e, 0x6d, 0x6e, 0x63, 0x30, 0x31, 0x32, 0x2e, 0x6d, 0x63,
        0x63, 0x34, 0x36, 0x30, 0x2e, 0x33, 0x67, 0x70, 0x70, 0x6e, 0x65, 0x74, 0x77, 0x6f, 0x72, 0x6b,
        0x2e, 0x6f, 0x72, 0x67, 0x3b, 0x75, 0x73, 0x65, 0x72, 0x3d, 0x70, 0x68, 0x6f, 0x6e, 0x65, 0x3e,
        0x0d, 0x0a, 0x43, 0x53, 0x65, 0x71, 0x3a, 0x20, 0x31, 0x20, 0x49, 0x4e, 0x56, 0x49, 0x54, 0x45,
        0x0d, 0x0a, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x4c, 0x65, 0x6e, 0x67, 0x74, 0x68,
        0x3a, 0x20, 0x30, 0x0d, 0x0a, 0x0d, 0x0a
    };
    VOS_UINT8               aucIpData2[] =
    {
        0x45, 0x00,
        0x00, 0x4a, 0x80, 0x52, 0x00, 0x00, 0xfb, 0x11, 0xfc, 0x0b, 0xac, 0x14, 0x80, 0x08, 0x02, 0x01,
        0x15, 0x27, 0x45, 0xa4, 0x90, 0x92, 0x00, 0x36, 0xf8, 0x69, 0x80, 0x6c, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x40, 0x3a, 0x7f, 0xcc, 0x43, 0x20, 0x14, 0x37, 0x08, 0x81, 0x43, 0xf6, 0x83, 0x24, 0x50,
        0x81, 0xd3, 0x28, 0xa9, 0x16, 0x60, 0x76, 0x40, 0x11, 0xb1, 0x5a, 0xf8, 0x58, 0x10, 0xec, 0x42,
        0x69, 0x4c, 0xfc, 0x4b, 0xda, 0xce, 0x49, 0x78
    };
    /*lint +e813*/
    VOS_INT                 s_size1    = sizeof(aucIpData1);
    VOS_INT                 s_size2    = sizeof(aucIpData2);

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucDstIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_FALSE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_FALSE;

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_DL_RCV_001: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    ipcom_run_cmd(cmd_str);

    IMS_NIC_DlDataRcv(aucIpData1, s_size1, 0);
    IMS_NIC_DlDataRcv(aucIpData2, s_size2, 0);
}

VOS_VOID ST_DNS_001(VOS_UINT8 ucIpAddr, VOS_UINT8 ucDnsPrim, VOS_UINT8 ucDnsSec)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr1[4]            = {0xC0, 0xA8, 0x33, 0};
    VOS_UINT8                       aucDnsPrimAddr1[4]          = {0xC0, 0xA8, 0x1E, 0x01};
    VOS_UINT8                       aucDnsSecAddr1[4]           = {0xC0, 0xA8, 0x1E, 0x02};

    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 5;
    char *cmd_str           = "ifconfig -a";

    aucSrcIpAddr1[3]        = ucIpAddr;
    aucDnsPrimAddr1[3]      = ucDnsPrim;
    aucDnsSecAddr1[3]       = ucDnsSec;

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucSrcIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_FALSE;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr1, 4);
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecAddr1, 4);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_DNS_001: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    ipcom_run_cmd(cmd_str);

    return;
}

VOS_VOID ST_DNS_002(VOS_UINT8 ucIpAddr)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucSrcIpAddr[16]            = {0x21, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};         /* 128-bit IP address */
    VOS_UINT8                       aucDnsPrimAddr[16]          = {0x20, 0x0, 0x0, 0x02, 0x0, 0x02, 0x0, 0x01, 0x0, 0x01, 0x0, 0x01, 0x0, 0x1f, 0x0, 0x01};
    VOS_UINT8                       aucDnsSecAddr[16]           = {0x20, 0x0, 0x0, 0x02, 0x0, 0x02, 0x0, 0x01, 0x0, 0x01, 0x0, 0x01, 0x0, 0x1f, 0x0, 0x01};
    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 6;
    char *cmd_str           = "ifconfig -a";

    aucSrcIpAddr[7]  = ucIpAddr;

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv6PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv4PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, aucSrcIpAddr, 16);

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim         = PS_TRUE;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec          = PS_FALSE;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen       = 64;
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, aucDnsPrimAddr, 16);
    VOS_MemCpy(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, aucDnsSecAddr, 16);

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_DNS_002: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    ipcom_run_cmd(cmd_str);

    return;
}

#endif

VOS_VOID ST_IMS_NIC_DEL(VOS_UINT8 ucRabId, VOS_UINT8 ucModemId)
{
    VOS_UINT32 ulRslt;

    ulRslt = IMS_NIC_PdnInfoDel(ucRabId, ucModemId);

    (VOS_VOID)vos_printf("ST_IMS_NIC_DEL Result %d \n", ulRslt);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_CFG_001
 功能描述  : 配置IPV4/IPV6 共4个DNS服务器，输出0表示成功
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_CFG_001(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo;

    VOS_UINT8                           aucDnsPrimV4[]  = {192, 168, 22, 1};
    VOS_UINT8                           aucDnsSecV4[]   = {192, 168, 22, 2};
    VOS_UINT16                          ausDnsPrimV6[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 1};
    VOS_UINT16                          ausDnsSecV6[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 2};

    VOS_UINT8                           aucIpV4[]       = {192, 168, 30, 1};
    VOS_UINT16                          ausIpV6[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 1};
    VOS_UINT32                          ulRslt;


    PS_MEM_SET(&stConfigInfo, 0, sizeof(stConfigInfo));
    stConfigInfo.bitOpIpv4PdnInfo = 1;
    stConfigInfo.bitOpIpv6PdnInfo = 1;
    stConfigInfo.enModemId        = 0;
    stConfigInfo.ucRabId          = 5;

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim     = 1;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec      = 1;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen   = 64;
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucIpV4, sizeof(aucIpV4));
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4, sizeof(aucDnsPrimV4));
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4, sizeof(aucDnsSecV4));

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, ausIpV6, sizeof(ausIpV6));
    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6, sizeof(ausDnsPrimV6));
    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6, sizeof(ausDnsSecV6));

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_001 Result %d \n", ulRslt);
}


/*****************************************************************************
 函 数 名  : ST_IMS_NIC_CFG_002
 功能描述  : 重复配置IPV4/IPV6相同IP共4个DNS服务器，输出0表示成功；
             删除IPV4两个DNS服务器，输出0表示成功
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_CFG_002(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo;
    VOS_UINT8                           aucDnsPrimV4[]  = {192, 168, 22, 1};
    VOS_UINT8                           aucDnsSecV4[]   = {192, 168, 22, 2};
    VOS_UINT16                          ausDnsPrimV6[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 1};
    VOS_UINT16                          ausDnsSecV6[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 2};

    VOS_UINT8                           aucIpV4[]       = {192, 168, 30, 1};
    VOS_UINT16                          ausIpV6[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 1};
    VOS_UINT32                          ulRslt;


    PS_MEM_SET(&stConfigInfo, 0, sizeof(stConfigInfo));
    stConfigInfo.bitOpIpv4PdnInfo = 1;
    stConfigInfo.bitOpIpv6PdnInfo = 1;
    stConfigInfo.enModemId        = 0;
    stConfigInfo.ucRabId          = 5;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucIpV4, sizeof(aucIpV4));
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4, sizeof(aucDnsPrimV4));
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4, sizeof(aucDnsSecV4));

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, ausIpV6, sizeof(ausIpV6));
    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6, sizeof(ausDnsPrimV6));
    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6, sizeof(ausDnsSecV6));

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_002 Result1 %d \n", ulRslt);

    stConfigInfo.bitOpIpv4PdnInfo = 0;

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_002 Result1 %d \n", ulRslt);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_CFG_003
 功能描述  : 配置IPV4/IPV6 共4个DNS服务器，输出0表示成功；
             删除IPV4两个DNS服务器，输出0表示成功
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_CFG_003(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo;
    VOS_UINT8                           aucDnsPrimV4[]  = {192, 168, 22, 1};
    VOS_UINT8                           aucDnsSecV4[]   = {192, 168, 22, 2};
    VOS_UINT16                          ausDnsPrimV6[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 1};
    VOS_UINT16                          ausDnsSecV6[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 2};

    VOS_UINT8                           aucIpV4[]       = {192, 168, 30, 1};
    VOS_UINT16                          ausIpV6[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 1};
    VOS_UINT32                          ulRslt;


    PS_MEM_SET(&stConfigInfo, 0, sizeof(stConfigInfo));
    stConfigInfo.bitOpIpv4PdnInfo = 1;
    stConfigInfo.bitOpIpv6PdnInfo = 1;
    stConfigInfo.enModemId        = 0;
    stConfigInfo.ucRabId          = 5;

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec  = 1;
    stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen   = 64;
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucIpV4, sizeof(aucIpV4));
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4, sizeof(aucDnsPrimV4));
    PS_MEM_CPY(stConfigInfo.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4, sizeof(aucDnsSecV4));

    stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucIpV6Addr, ausIpV6, sizeof(ausIpV6));
    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6, sizeof(ausDnsPrimV6));
    PS_MEM_CPY(stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6, sizeof(ausDnsSecV6));

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_003 Result1 %d \n", ulRslt);

    stConfigInfo.bitOpIpv6PdnInfo = 0;

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_003 Result1 %d \n", ulRslt);
}

/*****************************************************************************
 函 数 名  : ST_IMS_NIC_CFG_004
 功能描述  : 配置DNS服务器超出上限。Result5,Result6输出0,Result7输出5表示成功
 输入参数  :
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ST_IMS_NIC_CFG_004(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab5 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab6 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab7 = {0};

    VOS_UINT8                           aucDnsPrimV4_rab5[]  = {192, 168, 22, 1};
    VOS_UINT8                           aucDnsSecV4_rab5[]   = {192, 168, 22, 2};
    VOS_UINT16                          ausDnsPrimV6_rab5[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 1};
    VOS_UINT16                          ausDnsSecV6_rab5[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 2};

    VOS_UINT8                           aucIpV4_rab5[]       = {192, 168, 30, 5};
    VOS_UINT16                          ausIpV6_rab5[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 5};

    VOS_UINT8                           aucDnsPrimV4_rab6[]  = {192, 168, 22, 1};
    VOS_UINT8                           aucDnsSecV4_rab6[]   = {192, 168, 22, 2};
    VOS_UINT16                          ausDnsPrimV6_rab6[]  = {0x2003, 0, 0, 0, 0, 0, 0x22, 1};
    VOS_UINT16                          ausDnsSecV6_rab6[]   = {0x2003, 0, 0, 0, 0, 0, 0x22, 2};

    VOS_UINT8                           aucIpV4_rab6[]       = {192, 168, 30, 6};
    VOS_UINT16                          ausIpV6_rab6[]       = {0x2003, 0, 0, 0, 0, 0, 0x30,6};

    VOS_UINT8                           aucDnsPrimV4_rab7[]  = {192, 168, 22, 7};
    VOS_UINT8                           aucDnsSecV4_rab7[]   = {192, 168, 22, 8};
    VOS_UINT16                          ausDnsPrimV6_rab7[]  = {0x2004, 0, 1, 0, 0, 0, 0x22, 7};
    VOS_UINT16                          ausDnsSecV6_rab7[]   = {0x2004, 0, 0, 1, 0, 0, 0x22, 8};

    VOS_UINT8                           aucIpV4_rab7[]       = {192, 168, 30, 7};
    VOS_UINT16                          ausIpV6_rab7[]       = {0x2004, 0, 0, 0, 1, 0, 0x30, 7};



    VOS_UINT32                          ulRslt;


    PS_MEM_SET(&stConfigInfo_rab5, 0, sizeof(stConfigInfo_rab5));
    PS_MEM_SET(&stConfigInfo_rab6, 0, sizeof(stConfigInfo_rab6));
    PS_MEM_SET(&stConfigInfo_rab7, 0, sizeof(stConfigInfo_rab7));
    stConfigInfo_rab5.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab5.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab5.enModemId        = 0;
    stConfigInfo_rab5.ucRabId          = 5;
    stConfigInfo_rab5.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab6.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab6.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab6.enModemId        = 0;
    stConfigInfo_rab6.ucRabId          = 6;
    stConfigInfo_rab6.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab7.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab7.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab7.enModemId        = 0;
    stConfigInfo_rab7.ucRabId          = 7;
    stConfigInfo_rab7.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab5.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab5.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab5, sizeof(aucIpV4_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab5, sizeof(aucDnsPrimV4_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab5, sizeof(aucDnsSecV4_rab5));

    stConfigInfo_rab5.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab5.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab5, sizeof(ausIpV6_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab5, sizeof(ausDnsPrimV6_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab5, sizeof(ausDnsSecV6_rab5));


    stConfigInfo_rab6.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab6.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab6, sizeof(aucIpV4_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab6, sizeof(aucDnsPrimV4_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab6, sizeof(aucDnsSecV4_rab6));

    stConfigInfo_rab6.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab6.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab6, sizeof(ausIpV6_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab6, sizeof(ausDnsPrimV6_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab6, sizeof(ausDnsSecV6_rab6));

    stConfigInfo_rab7.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab7.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab7, sizeof(aucIpV4_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab7, sizeof(aucDnsPrimV4_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab7, sizeof(aucDnsSecV4_rab7));

    stConfigInfo_rab7.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab7.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab7, sizeof(ausIpV6_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab7, sizeof(ausDnsPrimV6_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab7, sizeof(ausDnsSecV6_rab7));



    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab5);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result5 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab6);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result6 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab7);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result7 %d \n", ulRslt);

    ST_IMS_NIC_DEL(5, 0);
    ST_IMS_NIC_DEL(6, 0);
    ST_IMS_NIC_DEL(7, 0);
}



VOS_VOID ST_IMS_NIC_CFG_005(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab5 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab6 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab7 = {0};

    VOS_UINT8                           aucDnsPrimV4_rab5[]  = {192, 168, 22, 0x15};
    VOS_UINT8                           aucDnsSecV4_rab5[]   = {192, 168, 22, 0x25};
    VOS_UINT16                          ausDnsPrimV6_rab5[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x15};
    VOS_UINT16                          ausDnsSecV6_rab5[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x25};

    VOS_UINT8                           aucIpV4_rab5[]       = {192, 168, 30, 5};
    VOS_UINT16                          ausIpV6_rab5[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 5};

    VOS_UINT8                           aucDnsPrimV4_rab6[]  = {192, 168, 22, 16};
    VOS_UINT8                           aucDnsSecV4_rab6[]   = {192, 168, 22, 26};
    VOS_UINT16                          ausDnsPrimV6_rab6[]  = {0x2003, 0, 0, 0, 0, 0, 0x22, 0x16};
    VOS_UINT16                          ausDnsSecV6_rab6[]   = {0x2003, 0, 0, 0, 0, 0, 0x22, 0x26};

    VOS_UINT8                           aucIpV4_rab6[]       = {192, 168, 30, 6};
    VOS_UINT16                          ausIpV6_rab6[]       = {0x2003, 0, 0, 0, 0, 0, 0x30, 6};

    VOS_UINT8                           aucDnsPrimV4_rab7[]  = {192, 168, 22, 17};
    VOS_UINT8                           aucDnsSecV4_rab7[]   = {192, 168, 22, 27};
    VOS_UINT16                          ausDnsPrimV6_rab7[]  = {0x2004, 0, 1, 0, 0, 0, 0x22, 0x17};
    VOS_UINT16                          ausDnsSecV6_rab7[]   = {0x2004, 0, 0, 1, 0, 0, 0x22, 0x27};

    VOS_UINT8                           aucIpV4_rab7[]       = {192, 168, 30, 7};
    VOS_UINT16                          ausIpV6_rab7[]       = {0x2004, 0, 0, 0, 1, 0, 0x30, 7};



    VOS_UINT32                          ulRslt;


    PS_MEM_SET(&stConfigInfo_rab5, 0, sizeof(stConfigInfo_rab5));
    PS_MEM_SET(&stConfigInfo_rab6, 0, sizeof(stConfigInfo_rab6));
    PS_MEM_SET(&stConfigInfo_rab7, 0, sizeof(stConfigInfo_rab7));

    stConfigInfo_rab5.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab5.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab5.enModemId        = 0;
    stConfigInfo_rab5.ucRabId          = 5;
    stConfigInfo_rab5.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab6.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab6.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab6.enModemId        = 0;
    stConfigInfo_rab6.ucRabId          = 6;
    stConfigInfo_rab6.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab7.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab7.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab7.enModemId        = 0;
    stConfigInfo_rab7.ucRabId          = 7;
    stConfigInfo_rab7.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab5.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab5.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab5, sizeof(aucIpV4_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab5, sizeof(aucDnsPrimV4_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab5, sizeof(aucDnsSecV4_rab5));

    stConfigInfo_rab5.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab5.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab5, sizeof(ausIpV6_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab5, sizeof(ausDnsPrimV6_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab5, sizeof(ausDnsSecV6_rab5));


    stConfigInfo_rab6.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab6.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab6, sizeof(aucIpV4_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab6, sizeof(aucDnsPrimV4_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab6, sizeof(aucDnsSecV4_rab6));

    stConfigInfo_rab6.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab6.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab6, sizeof(ausIpV6_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab6, sizeof(ausDnsPrimV6_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab6, sizeof(ausDnsSecV6_rab6));

    stConfigInfo_rab7.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab7.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab7, sizeof(aucIpV4_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab7, sizeof(aucDnsPrimV4_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab7, sizeof(aucDnsSecV4_rab7));

    stConfigInfo_rab7.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab7.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab7, sizeof(ausIpV6_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab7, sizeof(ausDnsPrimV6_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab7, sizeof(ausDnsSecV6_rab7));


    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab5);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result5 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab6);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result6 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab7);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result7 %d \n", ulRslt);

}

VOS_VOID ST_IMS_NIC_CFG_006(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab5 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab6 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab7 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab8 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab9 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab10 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab11 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab12 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab13 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab14 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab15 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab16 = {0};

    VOS_UINT8                           aucDnsPrimV4_rab5[]  = {192, 168, 22, 0x15};
    VOS_UINT8                           aucDnsSecV4_rab5[]   = {192, 168, 22, 0x25};
    VOS_UINT16                          ausDnsPrimV6_rab5[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x15};
    VOS_UINT16                          ausDnsSecV6_rab5[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x25};
    VOS_UINT8                           aucIpV4_rab5[]       = {192, 168, 30, 5};
    VOS_UINT16                          ausIpV6_rab5[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 5};

    VOS_UINT8                           aucDnsPrimV4_rab6[]  = {192, 168, 22, 16};
    VOS_UINT8                           aucDnsSecV4_rab6[]   = {192, 168, 22, 26};
    VOS_UINT16                          ausDnsPrimV6_rab6[]  = {0x2003, 0, 0, 0, 0, 0, 0x22, 0x16};
    VOS_UINT16                          ausDnsSecV6_rab6[]   = {0x2003, 0, 0, 0, 0, 0, 0x22, 0x26};
    VOS_UINT8                           aucIpV4_rab6[]       = {192, 168, 30, 6};
    VOS_UINT16                          ausIpV6_rab6[]       = {0x2003, 0, 0, 0, 0, 0, 0x30, 6};

    VOS_UINT8                           aucDnsPrimV4_rab7[]  = {192, 168, 22, 17};
    VOS_UINT8                           aucDnsSecV4_rab7[]   = {192, 168, 22, 27};
    VOS_UINT16                          ausDnsPrimV6_rab7[]  = {0x2004, 0, 1, 0, 0, 0, 0x22, 0x17};
    VOS_UINT16                          ausDnsSecV6_rab7[]   = {0x2004, 0, 0, 1, 0, 0, 0x22, 0x27};
    VOS_UINT8                           aucIpV4_rab7[]       = {192, 168, 30, 7};
    VOS_UINT16                          ausIpV6_rab7[]       = {0x2004, 0, 0, 0, 1, 0, 0x30, 7};

    VOS_UINT8                           aucDnsPrimV4_rab8[]  = {192, 168, 22, 0x15};
    VOS_UINT8                           aucDnsSecV4_rab8[]   = {192, 168, 22, 0x25};
    VOS_UINT16                          ausDnsPrimV6_rab8[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x15};
    VOS_UINT16                          ausDnsSecV6_rab8[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x25};
    VOS_UINT8                           aucIpV4_rab8[]       = {192, 168, 30, 5};
    VOS_UINT16                          ausIpV6_rab8[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 5};

    VOS_UINT8                           aucDnsPrimV4_rab9[]  = {192, 168, 22, 16};
    VOS_UINT8                           aucDnsSecV4_rab9[]   = {192, 168, 22, 26};
    VOS_UINT16                          ausDnsPrimV6_rab9[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x16};
    VOS_UINT16                          ausDnsSecV6_rab9[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x26};
    VOS_UINT8                           aucIpV4_rab9[]       = {192, 168, 30, 6};
    VOS_UINT16                          ausIpV6_rab9[]       = {0x2003, 0, 0, 0, 0, 0, 0x30, 6};

    VOS_UINT8                           aucDnsPrimV4_rab10[]  = {192, 168, 22, 17};
    VOS_UINT8                           aucDnsSecV4_rab10[]   = {192, 168, 22, 27};
    VOS_UINT16                          ausDnsPrimV6_rab10[]  = {0x2002, 0, 1, 0, 0, 0, 0x22, 0x17};
    VOS_UINT16                          ausDnsSecV6_rab10[]   = {0x2002, 0, 0, 1, 0, 0, 0x22, 0x27};
    VOS_UINT8                           aucIpV4_rab10[]       = {192, 168, 30, 7};
    VOS_UINT16                          ausIpV6_rab10[]       = {0x2004, 0, 0, 0, 1, 0, 0x30, 7};

    VOS_UINT8                           aucDnsPrimV4_rab11[]  = {192, 168, 22, 0x15};
    VOS_UINT8                           aucDnsSecV4_rab11[]   = {192, 168, 22, 0x25};
    VOS_UINT16                          ausDnsPrimV6_rab11[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x15};
    VOS_UINT16                          ausDnsSecV6_rab11[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x25};
    VOS_UINT8                           aucIpV4_rab11[]       = {192, 168, 30, 5};
    VOS_UINT16                          ausIpV6_rab11[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 5};

    VOS_UINT8                           aucDnsPrimV4_rab12[]  = {192, 168, 22, 16};
    VOS_UINT8                           aucDnsSecV4_rab12[]   = {192, 168, 22, 26};
    VOS_UINT16                          ausDnsPrimV6_rab12[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x16};
    VOS_UINT16                          ausDnsSecV6_rab12[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x26};
    VOS_UINT8                           aucIpV4_rab12[]       = {192, 168, 30, 6};
    VOS_UINT16                          ausIpV6_rab12[]       = {0x2003, 0, 0, 0, 0, 0, 0x30, 6};

    VOS_UINT8                           aucDnsPrimV4_rab13[]  = {192, 168, 22, 17};
    VOS_UINT8                           aucDnsSecV4_rab13[]   = {192, 168, 22, 27};
    VOS_UINT16                          ausDnsPrimV6_rab13[]  = {0x2002, 0, 1, 0, 0, 0, 0x22, 0x17};
    VOS_UINT16                          ausDnsSecV6_rab13[]   = {0x2002, 0, 0, 1, 0, 0, 0x22, 0x27};
    VOS_UINT8                           aucIpV4_rab13[]       = {192, 168, 30, 7};
    VOS_UINT16                          ausIpV6_rab13[]       = {0x2004, 0, 0, 0, 1, 0, 0x30, 7};

    VOS_UINT8                           aucDnsPrimV4_rab14[]  = {192, 168, 22, 0x15};
    VOS_UINT8                           aucDnsSecV4_rab14[]   = {192, 168, 22, 0x25};
    VOS_UINT16                          ausDnsPrimV6_rab14[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x15};
    VOS_UINT16                          ausDnsSecV6_rab14[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x25};
    VOS_UINT8                           aucIpV4_rab14[]       = {192, 168, 30, 5};
    VOS_UINT16                          ausIpV6_rab14[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 5};

    VOS_UINT8                           aucDnsPrimV4_rab15[]  = {192, 168, 22, 16};
    VOS_UINT8                           aucDnsSecV4_rab15[]   = {192, 168, 22, 26};
    VOS_UINT16                          ausDnsPrimV6_rab15[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x16};
    VOS_UINT16                          ausDnsSecV6_rab15[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x26};
    VOS_UINT8                           aucIpV4_rab15[]       = {192, 168, 30, 6};
    VOS_UINT16                          ausIpV6_rab15[]       = {0x2003, 0, 0, 0, 0, 0, 0x30, 6};

    VOS_UINT8                           aucDnsPrimV4_rab16[]  = {192, 168, 22, 17};
    VOS_UINT8                           aucDnsSecV4_rab16[]   = {192, 168, 22, 27};
    VOS_UINT16                          ausDnsPrimV6_rab16[]  = {0x2002, 0, 1, 0, 0, 0, 0x22, 0x17};
    VOS_UINT16                          ausDnsSecV6_rab16[]   = {0x2002, 0, 0, 1, 0, 0, 0x22, 0x27};
    VOS_UINT8                           aucIpV4_rab16[]       = {192, 168, 30, 7};
    VOS_UINT16                          ausIpV6_rab16[]       = {0x2004, 0, 0, 0, 1, 0, 0x30, 7};


    VOS_UINT32                          ulRslt;


    PS_MEM_SET(&stConfigInfo_rab5, 0, sizeof(stConfigInfo_rab5));
    PS_MEM_SET(&stConfigInfo_rab6, 0, sizeof(stConfigInfo_rab6));
    PS_MEM_SET(&stConfigInfo_rab7, 0, sizeof(stConfigInfo_rab7));
    PS_MEM_SET(&stConfigInfo_rab8, 0, sizeof(stConfigInfo_rab8));
    PS_MEM_SET(&stConfigInfo_rab9, 0, sizeof(stConfigInfo_rab9));
    PS_MEM_SET(&stConfigInfo_rab10, 0, sizeof(stConfigInfo_rab10));
    PS_MEM_SET(&stConfigInfo_rab11, 0, sizeof(stConfigInfo_rab11));
    PS_MEM_SET(&stConfigInfo_rab12, 0, sizeof(stConfigInfo_rab12));
    PS_MEM_SET(&stConfigInfo_rab13, 0, sizeof(stConfigInfo_rab13));
    PS_MEM_SET(&stConfigInfo_rab14, 0, sizeof(stConfigInfo_rab14));
    PS_MEM_SET(&stConfigInfo_rab15, 0, sizeof(stConfigInfo_rab15));
    PS_MEM_SET(&stConfigInfo_rab16, 0, sizeof(stConfigInfo_rab16));

    stConfigInfo_rab5.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab5.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab5.enModemId        = 0;
    stConfigInfo_rab5.ucRabId          = 5;
    stConfigInfo_rab5.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab6.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab6.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab6.enModemId        = 0;
    stConfigInfo_rab6.ucRabId          = 6;
    stConfigInfo_rab6.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab7.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab7.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab7.enModemId        = 0;
    stConfigInfo_rab7.ucRabId          = 7;
    stConfigInfo_rab7.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab8.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab8.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab8.enModemId        = 0;
    stConfigInfo_rab8.ucRabId          = 8;
    stConfigInfo_rab8.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab9.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab9.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab9.enModemId        = 0;
    stConfigInfo_rab9.ucRabId          = 9;
    stConfigInfo_rab9.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab10.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab10.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab10.enModemId        = 0;
    stConfigInfo_rab10.ucRabId          = 10;
    stConfigInfo_rab10.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab11.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab11.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab11.enModemId        = 0;
    stConfigInfo_rab11.ucRabId          = 11;
    stConfigInfo_rab11.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab12.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab12.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab12.enModemId        = 0;
    stConfigInfo_rab12.ucRabId          = 12;
    stConfigInfo_rab12.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab13.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab13.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab13.enModemId        = 0;
    stConfigInfo_rab13.ucRabId          = 13;
    stConfigInfo_rab13.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab14.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab14.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab14.enModemId        = 0;
    stConfigInfo_rab14.ucRabId          = 14;
    stConfigInfo_rab14.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab15.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab15.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab15.enModemId        = 0;
    stConfigInfo_rab15.ucRabId          = 15;
    stConfigInfo_rab15.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab16.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab16.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab16.enModemId        = 0;
    stConfigInfo_rab16.ucRabId          = 16;
    stConfigInfo_rab16.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab5.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab5.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab5, sizeof(aucIpV4_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab5, sizeof(aucDnsPrimV4_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab5, sizeof(aucDnsSecV4_rab5));

    stConfigInfo_rab5.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab5.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab5, sizeof(ausIpV6_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab5, sizeof(ausDnsPrimV6_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab5, sizeof(ausDnsSecV6_rab5));


    stConfigInfo_rab6.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab6.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab6, sizeof(aucIpV4_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab6, sizeof(aucDnsPrimV4_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab6, sizeof(aucDnsSecV4_rab6));

    stConfigInfo_rab6.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab6.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab6, sizeof(ausIpV6_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab6, sizeof(ausDnsPrimV6_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab6, sizeof(ausDnsSecV6_rab6));

    stConfigInfo_rab7.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab7.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab7, sizeof(aucIpV4_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab7, sizeof(aucDnsPrimV4_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab7, sizeof(aucDnsSecV4_rab7));

    stConfigInfo_rab7.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab7.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab7, sizeof(ausIpV6_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab7, sizeof(ausDnsPrimV6_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab7, sizeof(ausDnsSecV6_rab7));


    stConfigInfo_rab8.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab8.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab8.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab8, sizeof(aucIpV4_rab8));
    PS_MEM_CPY(stConfigInfo_rab8.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab8, sizeof(aucDnsPrimV4_rab8));
    PS_MEM_CPY(stConfigInfo_rab8.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab8, sizeof(aucDnsSecV4_rab8));

    stConfigInfo_rab8.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab8.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab8.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab8, sizeof(ausIpV6_rab8));
    PS_MEM_CPY(stConfigInfo_rab8.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab8, sizeof(ausDnsPrimV6_rab8));
    PS_MEM_CPY(stConfigInfo_rab8.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab8, sizeof(ausDnsSecV6_rab8));

    stConfigInfo_rab9.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab9.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab9.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab9, sizeof(aucIpV4_rab9));
    PS_MEM_CPY(stConfigInfo_rab9.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab9, sizeof(aucDnsPrimV4_rab9));
    PS_MEM_CPY(stConfigInfo_rab9.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab9, sizeof(aucDnsSecV4_rab9));

    stConfigInfo_rab9.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab9.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab9.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab9, sizeof(ausIpV6_rab9));
    PS_MEM_CPY(stConfigInfo_rab9.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab9, sizeof(ausDnsPrimV6_rab9));
    PS_MEM_CPY(stConfigInfo_rab9.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab9, sizeof(ausDnsSecV6_rab9));

    stConfigInfo_rab10.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab10.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab10.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab10, sizeof(aucIpV4_rab10));
    PS_MEM_CPY(stConfigInfo_rab10.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab10, sizeof(aucDnsPrimV4_rab10));
    PS_MEM_CPY(stConfigInfo_rab10.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab10, sizeof(aucDnsSecV4_rab10));

    stConfigInfo_rab10.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab10.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab10.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab10, sizeof(ausIpV6_rab10));
    PS_MEM_CPY(stConfigInfo_rab10.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab10, sizeof(ausDnsPrimV6_rab10));
    PS_MEM_CPY(stConfigInfo_rab10.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab10, sizeof(ausDnsSecV6_rab10));

    stConfigInfo_rab11.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab11.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab11.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab11, sizeof(aucIpV4_rab11));
    PS_MEM_CPY(stConfigInfo_rab11.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab11, sizeof(aucDnsPrimV4_rab11));
    PS_MEM_CPY(stConfigInfo_rab11.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab11, sizeof(aucDnsSecV4_rab11));

    stConfigInfo_rab11.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab11.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab11.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab11, sizeof(ausIpV6_rab11));
    PS_MEM_CPY(stConfigInfo_rab11.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab11, sizeof(ausDnsPrimV6_rab11));
    PS_MEM_CPY(stConfigInfo_rab11.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab11, sizeof(ausDnsSecV6_rab11));

    stConfigInfo_rab12.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab12.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab12.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab12, sizeof(aucIpV4_rab12));
    PS_MEM_CPY(stConfigInfo_rab12.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab12, sizeof(aucDnsPrimV4_rab12));
    PS_MEM_CPY(stConfigInfo_rab12.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab12, sizeof(aucDnsSecV4_rab12));

    stConfigInfo_rab12.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab12.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab12.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab12, sizeof(ausIpV6_rab12));
    PS_MEM_CPY(stConfigInfo_rab12.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab12, sizeof(ausDnsPrimV6_rab12));
    PS_MEM_CPY(stConfigInfo_rab12.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab12, sizeof(ausDnsSecV6_rab12));

    stConfigInfo_rab13.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab13.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab13.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab13, sizeof(aucIpV4_rab13));
    PS_MEM_CPY(stConfigInfo_rab13.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab13, sizeof(aucDnsPrimV4_rab13));
    PS_MEM_CPY(stConfigInfo_rab13.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab13, sizeof(aucDnsSecV4_rab13));

    stConfigInfo_rab13.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab13.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab13.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab13, sizeof(ausIpV6_rab13));
    PS_MEM_CPY(stConfigInfo_rab13.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab13, sizeof(ausDnsPrimV6_rab13));
    PS_MEM_CPY(stConfigInfo_rab13.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab13, sizeof(ausDnsSecV6_rab13));

    stConfigInfo_rab14.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab14.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab14.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab14, sizeof(aucIpV4_rab14));
    PS_MEM_CPY(stConfigInfo_rab14.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab14, sizeof(aucDnsPrimV4_rab14));
    PS_MEM_CPY(stConfigInfo_rab14.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab14, sizeof(aucDnsSecV4_rab14));

    stConfigInfo_rab14.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab14.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab14.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab14, sizeof(ausIpV6_rab14));
    PS_MEM_CPY(stConfigInfo_rab14.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab14, sizeof(ausDnsPrimV6_rab14));
    PS_MEM_CPY(stConfigInfo_rab14.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab14, sizeof(ausDnsSecV6_rab14));

    stConfigInfo_rab15.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab15.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab15.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab15, sizeof(aucIpV4_rab15));
    PS_MEM_CPY(stConfigInfo_rab15.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab15, sizeof(aucDnsPrimV4_rab15));
    PS_MEM_CPY(stConfigInfo_rab15.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab15, sizeof(aucDnsSecV4_rab15));

    stConfigInfo_rab15.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab15.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab15.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab15, sizeof(ausIpV6_rab15));
    PS_MEM_CPY(stConfigInfo_rab15.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab15, sizeof(ausDnsPrimV6_rab15));
    PS_MEM_CPY(stConfigInfo_rab15.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab15, sizeof(ausDnsSecV6_rab15));

    stConfigInfo_rab16.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab16.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab16.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab16, sizeof(aucIpV4_rab16));
    PS_MEM_CPY(stConfigInfo_rab16.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab16, sizeof(aucDnsPrimV4_rab16));
    PS_MEM_CPY(stConfigInfo_rab16.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab16, sizeof(aucDnsSecV4_rab16));

    stConfigInfo_rab16.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab16.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab16.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab16, sizeof(ausIpV6_rab16));
    PS_MEM_CPY(stConfigInfo_rab16.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab16, sizeof(ausDnsPrimV6_rab16));
    PS_MEM_CPY(stConfigInfo_rab16.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab16, sizeof(ausDnsSecV6_rab16));


    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab5);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result5 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab6);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result6 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab7);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result7 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab8);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result8 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab9);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result9 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab10);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result10 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab11);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result11 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab12);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result12 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab13);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result13 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab14);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result14 %d \n", ulRslt);


    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab15);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result15 %d \n", ulRslt);


    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab16);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result16 %d \n", ulRslt);

}


VOS_VOID ST_IMS_NIC_CFG_007(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab5 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab6 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab7 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab8 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab9 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab10 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab11 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab12 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab13 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab14 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab15 = {0};
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo_rab16 = {0};

    VOS_UINT8                           aucDnsPrimV4_rab5[]  = {192, 168, 22, 0x15};
    VOS_UINT8                           aucDnsSecV4_rab5[]   = {192, 168, 22, 0x25};
    VOS_UINT16                          ausDnsPrimV6_rab5[]  = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x15};
    VOS_UINT16                          ausDnsSecV6_rab5[]   = {0x2002, 0, 0, 0, 0, 0, 0x22, 0x25};
    VOS_UINT8                           aucIpV4_rab5[]       = {192, 168, 30, 5};
    VOS_UINT16                          ausIpV6_rab5[]       = {0x2002, 0, 0, 0, 0, 0, 0x30, 5};

    VOS_UINT8                           aucDnsPrimV4_rab6[]  = {192, 168, 22, 16};
    VOS_UINT8                           aucDnsSecV4_rab6[]   = {192, 168, 22, 26};
    VOS_UINT16                          ausDnsPrimV6_rab6[]  = {0x2003, 0, 0, 0, 0, 0, 0x22, 0x16};
    VOS_UINT16                          ausDnsSecV6_rab6[]   = {0x2003, 0, 0, 0, 0, 0, 0x22, 0x26};
    VOS_UINT8                           aucIpV4_rab6[]       = {192, 168, 30, 6};
    VOS_UINT16                          ausIpV6_rab6[]       = {0x2003, 0, 0, 0, 0, 0, 0x30, 6};

    VOS_UINT8                           aucDnsPrimV4_rab7[]  = {192, 168, 22, 17};
    VOS_UINT8                           aucDnsSecV4_rab7[]   = {192, 168, 22, 27};
    VOS_UINT16                          ausDnsPrimV6_rab7[]  = {0x2004, 0, 1, 0, 0, 0, 0x22, 0x17};
    VOS_UINT16                          ausDnsSecV6_rab7[]   = {0x2004, 0, 0, 1, 0, 0, 0x22, 0x27};
    VOS_UINT8                           aucIpV4_rab7[]       = {192, 168, 30, 7};
    VOS_UINT16                          ausIpV6_rab7[]       = {0x2004, 0, 0, 0, 1, 0, 0x30, 7};

    VOS_UINT8                           aucDnsPrimV4_rab8[]  = {192, 168, 22, 0x18};
    VOS_UINT8                           aucDnsSecV4_rab8[]   = {192, 168, 22, 0x28};
    VOS_UINT16                          ausDnsPrimV6_rab8[]  = {0x2005, 0, 0, 0, 0, 0, 0x22, 0x18};
    VOS_UINT16                          ausDnsSecV6_rab8[]   = {0x2005, 0, 0, 0, 0, 0, 0x22, 0x28};
    VOS_UINT8                           aucIpV4_rab8[]       = {192, 168, 30, 8};
    VOS_UINT16                          ausIpV6_rab8[]       = {0x2005, 0, 0, 0, 0, 0, 0x30, 8};

    VOS_UINT8                           aucDnsPrimV4_rab9[]  = {192, 168, 22, 19};
    VOS_UINT8                           aucDnsSecV4_rab9[]   = {192, 168, 22, 29};
    VOS_UINT16                          ausDnsPrimV6_rab9[]  = {0x2006, 0, 0, 0, 0, 0, 0x22, 0x19};
    VOS_UINT16                          ausDnsSecV6_rab9[]   = {0x2006, 0, 0, 0, 0, 0, 0x22, 0x29};
    VOS_UINT8                           aucIpV4_rab9[]       = {192, 168, 30, 9};
    VOS_UINT16                          ausIpV6_rab9[]       = {0x2006, 0, 0, 0, 0, 0, 0x30, 9};

    VOS_UINT8                           aucDnsPrimV4_rab10[]  = {192, 168, 22, 20};
    VOS_UINT8                           aucDnsSecV4_rab10[]   = {192, 168, 22, 30};
    VOS_UINT16                          ausDnsPrimV6_rab10[]  = {0x2007, 0, 1, 0, 0, 0, 0x22, 0x20};
    VOS_UINT16                          ausDnsSecV6_rab10[]   = {0x2007, 0, 0, 1, 0, 0, 0x22, 0x30};
    VOS_UINT8                           aucIpV4_rab10[]       = {192, 168, 30, 10};
    VOS_UINT16                          ausIpV6_rab10[]       = {0x2007, 0, 0, 0, 1, 0, 0x30, 10};

    VOS_UINT8                           aucDnsPrimV4_rab11[]  = {192, 168, 22, 0x21};
    VOS_UINT8                           aucDnsSecV4_rab11[]   = {192, 168, 22, 0x22};
    VOS_UINT16                          ausDnsPrimV6_rab11[]  = {0x2008, 0, 0, 0, 0, 0, 0x22, 0x21};
    VOS_UINT16                          ausDnsSecV6_rab11[]   = {0x2008, 0, 0, 0, 0, 0, 0x22, 0x22};
    VOS_UINT8                           aucIpV4_rab11[]       = {192, 168, 30, 11};
    VOS_UINT16                          ausIpV6_rab11[]       = {0x2008, 0, 0, 0, 0, 0, 0x30, 11};

    VOS_UINT8                           aucDnsPrimV4_rab12[]  = {192, 168, 22, 22};
    VOS_UINT8                           aucDnsSecV4_rab12[]   = {192, 168, 22, 32};
    VOS_UINT16                          ausDnsPrimV6_rab12[]  = {0x2009, 0, 0, 0, 0, 0, 0x22, 0x22};
    VOS_UINT16                          ausDnsSecV6_rab12[]   = {0x2009, 0, 0, 0, 0, 0, 0x22, 0x32};
    VOS_UINT8                           aucIpV4_rab12[]       = {192, 168, 30, 12};
    VOS_UINT16                          ausIpV6_rab12[]       = {0x2009, 0, 0, 0, 0, 0, 0x30, 12};

    VOS_UINT8                           aucDnsPrimV4_rab13[]  = {192, 168, 22, 23};
    VOS_UINT8                           aucDnsSecV4_rab13[]   = {192, 168, 22, 33};
    VOS_UINT16                          ausDnsPrimV6_rab13[]  = {0x200a, 0, 1, 0, 0, 0, 0x22, 0x23};
    VOS_UINT16                          ausDnsSecV6_rab13[]   = {0x200a, 0, 0, 1, 0, 0, 0x22, 0x33};
    VOS_UINT8                           aucIpV4_rab13[]       = {192, 168, 30, 13};
    VOS_UINT16                          ausIpV6_rab13[]       = {0x200a, 0, 0, 0, 1, 0, 0x30, 13};

    VOS_UINT8                           aucDnsPrimV4_rab14[]  = {192, 168, 22, 0x24};
    VOS_UINT8                           aucDnsSecV4_rab14[]   = {192, 168, 22, 0x34};
    VOS_UINT16                          ausDnsPrimV6_rab14[]  = {0x200b, 0, 0, 0, 0, 0, 0x22, 0x24};
    VOS_UINT16                          ausDnsSecV6_rab14[]   = {0x200b, 0, 0, 0, 0, 0, 0x22, 0x34};
    VOS_UINT8                           aucIpV4_rab14[]       = {192, 168, 30, 14};
    VOS_UINT16                          ausIpV6_rab14[]       = {0x200b, 0, 0, 0, 0, 0, 0x30, 14};

    VOS_UINT8                           aucDnsPrimV4_rab15[]  = {192, 168, 22, 55};
    VOS_UINT8                           aucDnsSecV4_rab15[]   = {192, 168, 22, 65};
    VOS_UINT16                          ausDnsPrimV6_rab15[]  = {0x200c, 0, 0, 0, 0, 0, 0x22, 0x55};
    VOS_UINT16                          ausDnsSecV6_rab15[]   = {0x200c, 0, 0, 0, 0, 0, 0x22, 0x65};
    VOS_UINT8                           aucIpV4_rab15[]       = {192, 168, 30, 15};
    VOS_UINT16                          ausIpV6_rab15[]       = {0x200c, 0, 0, 0, 0, 0, 0x30, 15};

    VOS_UINT8                           aucDnsPrimV4_rab16[]  = {192, 168, 22, 56};
    VOS_UINT8                           aucDnsSecV4_rab16[]   = {192, 168, 22, 66};
    VOS_UINT16                          ausDnsPrimV6_rab16[]  = {0x200d, 0, 1, 0, 0, 0, 0x22, 0x56};
    VOS_UINT16                          ausDnsSecV6_rab16[]   = {0x200d, 0, 0, 1, 0, 0, 0x22, 0x66};
    VOS_UINT8                           aucIpV4_rab16[]       = {192, 168, 30, 16};
    VOS_UINT16                          ausIpV6_rab16[]       = {0x200d, 0, 0, 0, 1, 0, 0x30, 16};


    VOS_UINT32                          ulRslt;


    PS_MEM_SET(&stConfigInfo_rab5, 0, sizeof(stConfigInfo_rab5));
    PS_MEM_SET(&stConfigInfo_rab6, 0, sizeof(stConfigInfo_rab6));
    PS_MEM_SET(&stConfigInfo_rab7, 0, sizeof(stConfigInfo_rab7));
    PS_MEM_SET(&stConfigInfo_rab8, 0, sizeof(stConfigInfo_rab8));
    PS_MEM_SET(&stConfigInfo_rab9, 0, sizeof(stConfigInfo_rab9));
    PS_MEM_SET(&stConfigInfo_rab10, 0, sizeof(stConfigInfo_rab10));
    PS_MEM_SET(&stConfigInfo_rab11, 0, sizeof(stConfigInfo_rab11));
    PS_MEM_SET(&stConfigInfo_rab12, 0, sizeof(stConfigInfo_rab12));
    PS_MEM_SET(&stConfigInfo_rab13, 0, sizeof(stConfigInfo_rab13));
    PS_MEM_SET(&stConfigInfo_rab14, 0, sizeof(stConfigInfo_rab14));
    PS_MEM_SET(&stConfigInfo_rab15, 0, sizeof(stConfigInfo_rab15));
    PS_MEM_SET(&stConfigInfo_rab16, 0, sizeof(stConfigInfo_rab16));


    stConfigInfo_rab5.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab5.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab5.enModemId        = 0;
    stConfigInfo_rab5.ucRabId          = 5;
    stConfigInfo_rab5.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab6.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab6.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab6.enModemId        = 0;
    stConfigInfo_rab6.ucRabId          = 6;
    stConfigInfo_rab6.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab7.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab7.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab7.enModemId        = 0;
    stConfigInfo_rab7.ucRabId          = 7;
    stConfigInfo_rab7.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab8.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab8.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab8.enModemId        = 0;
    stConfigInfo_rab8.ucRabId          = 8;
    stConfigInfo_rab8.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab9.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab9.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab9.enModemId        = 0;
    stConfigInfo_rab9.ucRabId          = 9;
    stConfigInfo_rab9.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab10.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab10.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab10.enModemId        = 0;
    stConfigInfo_rab10.ucRabId          = 10;
    stConfigInfo_rab10.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab11.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab11.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab11.enModemId        = 0;
    stConfigInfo_rab11.ucRabId          = 11;
    stConfigInfo_rab11.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab12.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab12.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab12.enModemId        = 0;
    stConfigInfo_rab12.ucRabId          = 12;
    stConfigInfo_rab12.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab13.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab13.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab13.enModemId        = 0;
    stConfigInfo_rab13.ucRabId          = 13;
    stConfigInfo_rab13.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab14.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab14.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab14.enModemId        = 0;
    stConfigInfo_rab14.ucRabId          = 14;
    stConfigInfo_rab14.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab15.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab15.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab15.enModemId        = 0;
    stConfigInfo_rab15.ucRabId          = 15;
    stConfigInfo_rab15.stIpv6PdnInfo.ulBitPrefixLen   = 64;

    stConfigInfo_rab16.bitOpIpv4PdnInfo = 1;
    stConfigInfo_rab16.bitOpIpv6PdnInfo = 1;
    stConfigInfo_rab16.enModemId        = 0;
    stConfigInfo_rab16.ucRabId          = 16;
    stConfigInfo_rab16.stIpv6PdnInfo.ulBitPrefixLen   = 64;


    stConfigInfo_rab5.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab5.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab5, sizeof(aucIpV4_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab5, sizeof(aucDnsPrimV4_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab5, sizeof(aucDnsSecV4_rab5));

    stConfigInfo_rab5.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab5.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab5, sizeof(ausIpV6_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab5, sizeof(ausDnsPrimV6_rab5));
    PS_MEM_CPY(stConfigInfo_rab5.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab5, sizeof(ausDnsSecV6_rab5));


    stConfigInfo_rab6.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab6.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab6, sizeof(aucIpV4_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab6, sizeof(aucDnsPrimV4_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab6, sizeof(aucDnsSecV4_rab6));

    stConfigInfo_rab6.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab6.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab6, sizeof(ausIpV6_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab6, sizeof(ausDnsPrimV6_rab6));
    PS_MEM_CPY(stConfigInfo_rab6.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab6, sizeof(ausDnsSecV6_rab6));

    stConfigInfo_rab7.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab7.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab7, sizeof(aucIpV4_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab7, sizeof(aucDnsPrimV4_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab7, sizeof(aucDnsSecV4_rab7));

    stConfigInfo_rab7.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab7.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab7, sizeof(ausIpV6_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab7, sizeof(ausDnsPrimV6_rab7));
    PS_MEM_CPY(stConfigInfo_rab7.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab7, sizeof(ausDnsSecV6_rab7));


    stConfigInfo_rab8.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab8.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab8.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab8, sizeof(aucIpV4_rab8));
    PS_MEM_CPY(stConfigInfo_rab8.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab8, sizeof(aucDnsPrimV4_rab8));
    PS_MEM_CPY(stConfigInfo_rab8.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab8, sizeof(aucDnsSecV4_rab8));

    stConfigInfo_rab8.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab8.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab8.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab8, sizeof(ausIpV6_rab8));
    PS_MEM_CPY(stConfigInfo_rab8.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab8, sizeof(ausDnsPrimV6_rab8));
    PS_MEM_CPY(stConfigInfo_rab8.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab8, sizeof(ausDnsSecV6_rab8));

    stConfigInfo_rab9.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab9.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab9.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab9, sizeof(aucIpV4_rab9));
    PS_MEM_CPY(stConfigInfo_rab9.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab9, sizeof(aucDnsPrimV4_rab9));
    PS_MEM_CPY(stConfigInfo_rab9.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab9, sizeof(aucDnsSecV4_rab9));

    stConfigInfo_rab9.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab9.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab9.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab9, sizeof(ausIpV6_rab9));
    PS_MEM_CPY(stConfigInfo_rab9.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab9, sizeof(ausDnsPrimV6_rab9));
    PS_MEM_CPY(stConfigInfo_rab9.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab9, sizeof(ausDnsSecV6_rab9));

    stConfigInfo_rab10.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab10.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab10.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab10, sizeof(aucIpV4_rab10));
    PS_MEM_CPY(stConfigInfo_rab10.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab10, sizeof(aucDnsPrimV4_rab10));
    PS_MEM_CPY(stConfigInfo_rab10.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab10, sizeof(aucDnsSecV4_rab10));

    stConfigInfo_rab10.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab10.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab10.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab10, sizeof(ausIpV6_rab10));
    PS_MEM_CPY(stConfigInfo_rab10.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab10, sizeof(ausDnsPrimV6_rab10));
    PS_MEM_CPY(stConfigInfo_rab10.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab10, sizeof(ausDnsSecV6_rab10));

    stConfigInfo_rab11.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab11.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab11.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab11, sizeof(aucIpV4_rab11));
    PS_MEM_CPY(stConfigInfo_rab11.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab11, sizeof(aucDnsPrimV4_rab11));
    PS_MEM_CPY(stConfigInfo_rab11.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab11, sizeof(aucDnsSecV4_rab11));

    stConfigInfo_rab11.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab11.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab11.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab11, sizeof(ausIpV6_rab11));
    PS_MEM_CPY(stConfigInfo_rab11.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab11, sizeof(ausDnsPrimV6_rab11));
    PS_MEM_CPY(stConfigInfo_rab11.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab11, sizeof(ausDnsSecV6_rab11));

    stConfigInfo_rab12.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab12.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab12.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab12, sizeof(aucIpV4_rab12));
    PS_MEM_CPY(stConfigInfo_rab12.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab12, sizeof(aucDnsPrimV4_rab12));
    PS_MEM_CPY(stConfigInfo_rab12.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab12, sizeof(aucDnsSecV4_rab12));

    stConfigInfo_rab12.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab12.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab12.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab12, sizeof(ausIpV6_rab12));
    PS_MEM_CPY(stConfigInfo_rab12.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab12, sizeof(ausDnsPrimV6_rab12));
    PS_MEM_CPY(stConfigInfo_rab12.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab12, sizeof(ausDnsSecV6_rab12));

    stConfigInfo_rab13.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab13.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab13.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab13, sizeof(aucIpV4_rab13));
    PS_MEM_CPY(stConfigInfo_rab13.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab13, sizeof(aucDnsPrimV4_rab13));
    PS_MEM_CPY(stConfigInfo_rab13.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab13, sizeof(aucDnsSecV4_rab13));

    stConfigInfo_rab13.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab13.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab13.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab13, sizeof(ausIpV6_rab13));
    PS_MEM_CPY(stConfigInfo_rab13.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab13, sizeof(ausDnsPrimV6_rab13));
    PS_MEM_CPY(stConfigInfo_rab13.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab13, sizeof(ausDnsSecV6_rab13));

    stConfigInfo_rab14.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab14.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab14.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab14, sizeof(aucIpV4_rab14));
    PS_MEM_CPY(stConfigInfo_rab14.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab14, sizeof(aucDnsPrimV4_rab14));
    PS_MEM_CPY(stConfigInfo_rab14.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab14, sizeof(aucDnsSecV4_rab14));

    stConfigInfo_rab14.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab14.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab14.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab14, sizeof(ausIpV6_rab14));
    PS_MEM_CPY(stConfigInfo_rab14.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab14, sizeof(ausDnsPrimV6_rab14));
    PS_MEM_CPY(stConfigInfo_rab14.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab14, sizeof(ausDnsSecV6_rab14));

    stConfigInfo_rab15.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab15.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab15.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab15, sizeof(aucIpV4_rab15));
    PS_MEM_CPY(stConfigInfo_rab15.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab15, sizeof(aucDnsPrimV4_rab15));
    PS_MEM_CPY(stConfigInfo_rab15.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab15, sizeof(aucDnsSecV4_rab15));

    stConfigInfo_rab15.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab15.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab15.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab15, sizeof(ausIpV6_rab15));
    PS_MEM_CPY(stConfigInfo_rab15.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab15, sizeof(ausDnsPrimV6_rab15));
    PS_MEM_CPY(stConfigInfo_rab15.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab15, sizeof(ausDnsSecV6_rab15));

    stConfigInfo_rab16.stIpv4PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab16.stIpv4PdnInfo.bitOpDnsSec  = 1;
    PS_MEM_CPY(stConfigInfo_rab16.stIpv4PdnInfo.aucIpV4Addr, aucIpV4_rab16, sizeof(aucIpV4_rab16));
    PS_MEM_CPY(stConfigInfo_rab16.stIpv4PdnInfo.aucDnsPrimAddr, aucDnsPrimV4_rab16, sizeof(aucDnsPrimV4_rab16));
    PS_MEM_CPY(stConfigInfo_rab16.stIpv4PdnInfo.aucDnsSecAddr, aucDnsSecV4_rab16, sizeof(aucDnsSecV4_rab16));

    stConfigInfo_rab16.stIpv6PdnInfo.bitOpDnsPrim = 1;
    stConfigInfo_rab16.stIpv6PdnInfo.bitOpDnsSec  = 1;

    PS_MEM_CPY(stConfigInfo_rab16.stIpv6PdnInfo.aucIpV6Addr, ausIpV6_rab16, sizeof(ausIpV6_rab16));
    PS_MEM_CPY(stConfigInfo_rab16.stIpv6PdnInfo.aucDnsPrimAddr, ausDnsPrimV6_rab16, sizeof(ausDnsPrimV6_rab16));
    PS_MEM_CPY(stConfigInfo_rab16.stIpv6PdnInfo.aucDnsSecAddr, ausDnsSecV6_rab16, sizeof(ausDnsSecV6_rab16));


    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab5);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result5 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab6);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result6 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab7);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result7 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab8);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result8 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab9);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result9 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab10);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result10 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab11);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result11 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab12);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result12 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab13);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result13 %d \n", ulRslt);

    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab14);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result14 %d \n", ulRslt);


    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab15);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result15 %d \n", ulRslt);


    ulRslt = IMS_NIC_PdnInfoConfig(&stConfigInfo_rab16);

    (VOS_VOID)vos_printf("ST_IMS_NIC_CFG_004 Result16 %d \n", ulRslt);

}


VOS_VOID ST_IPS_CCORE_Bridge(VOS_VOID)
{
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU        stIpsMntnCapturePara;
    VOS_UINT8           aucNetIfName[16]    = {0x69, 0x6D, 0x73, 0x5F, 0x6E, 0x69, 0x63, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    /*lint -e813*/
    VOS_UINT8               aucIpData[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
    };
    /*lint +e813*/
    char    *DstPort   = "DstPort";
    char    *SrcPort   = "SrcPort";

    stIpsMntnCapturePara.paucNetIfName  = aucNetIfName;
    stIpsMntnCapturePara.paucDestPort   = (unsigned char*)DstPort;
    stIpsMntnCapturePara.paucSrcPort    = (unsigned char*)SrcPort;
    stIpsMntnCapturePara.usLen          = 256;
    stIpsMntnCapturePara.pucData        = aucIpData;

    IPS_MNTN_CCORE_BridgePktInfoCB(&stIpsMntnCapturePara);

}

VOS_VOID ST_IPS_CCORE_DHCP(VOS_VOID)
{
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU        stIpsMntnCapturePara;
    VOS_UINT8           aucNetIfName[16]    = {0x69, 0x6D, 0x73, 0x5F, 0x6E, 0x69, 0x63, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    /*lint -e813*/
    VOS_UINT8               aucIpData[] =
    {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
        0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
        0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
    };
    /*lint +e813*/

    stIpsMntnCapturePara.paucNetIfName  = aucNetIfName;
    stIpsMntnCapturePara.usLen          = 256;
    stIpsMntnCapturePara.pucData        = aucIpData;

    IPS_MNTN_CCORE_DhcpcRecvPktInfoCB(&stIpsMntnCapturePara);

}


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

