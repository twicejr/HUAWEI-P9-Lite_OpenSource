



/*****************************************************************************
  1 头文件包含
**************************************************************************** */
#include "OmCommonPpm.h"
#include "OmSocketPpm.h"
#include "cpm.h"
#include "NVIM_Interface.h"

#if (VOS_WIN32 == VOS_OS_VER)
#include "OmAppRl.h"
#include <winsock2.h>
#include <windows.h>
#endif

#if (VOS_LINUX == VOS_OS_VER)
#include "hisocket.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767*/
#define  THIS_FILE_ID        PS_FILE_ID_OM_SOCKET_PPM_C
/*lint +e767*/


/* ****************************************************************************
  2 全局变量定义
**************************************************************************** */
COMM_SOCKET_CTRL_INFO_STRU g_astSockInfo[SOCKET_BUTT] =
            {{SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_OM_IND_PORT, SOCK_OM_IND_SRC_PORT_NUM,       {0,}},
             {SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_OM_CFG_PORT, SOCK_OM_CFG_SRC_PORT_NUM,       {0,}},
             {SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_AT_PORT,     SOCK_AT_SRC_PORT_NUM,           {0,}}
            };

/*****************************************************************************
  3 外部引用声明
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (FEATURE_HISOCKET == FEATURE_ON))
/*****************************************************************************
  4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : XXXXXXXX
    修改内容   : V8R1 OM_Optimize项目新增

*****************************************************************************/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*保存当前SOCKET的状态*/
VOS_UINT32          g_ulSockState = SOCK_OK;

/* 自旋锁，用来作自处理任务的临界资源保护 */
VOS_SPINLOCK        g_stSockTaskSpinLock;

/*保存当前SOCKETOM的初始化状态*/
VOS_UINT32          g_ulSockOMInitState  = VOS_FALSE;

/*保存当前SOCKETAT的初始化状态*/
VOS_UINT32          g_ulSockATInitState = VOS_FALSE;

VOS_UINT32          g_ulOmIsReConn      = VOS_FALSE;
VOS_UINT32          g_ulAtIsReConn      = VOS_FALSE;


SOCKET_UDP_INFO_STRU g_stUdpInfo = {VOS_FALSE, };

/*****************************************************************************
 Prototype      : Sock_IsEnable
 Description    : SOCK功能是否支持
 Input          : void
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2012-05-24
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_BOOL PPM_SockIsEnable(VOS_VOID)
{
#if (VOS_LINUX == VOS_OS_VER)
    OM_CHANNLE_PORT_CFG_STRU    stPortCfg;

    /* 读取OM的物理输出通道 */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        return VOS_FALSE;
    }

    //stPortCfg.enPortNum += CPM_APP_PORT;

    /* 检测参数*/
    if (CPM_OM_PORT_TYPE_WIFI != stPortCfg.enPortNum)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}
#if 0
/*****************************************************************************
 Prototype      : Sock_ShutdownAll
 Description    : 关闭所有的SOCKET连接
 Input          : VOS_VOID

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
 *****************************************************************************/
VOS_VOID PPM_SockShutdownAll(VOS_VOID)
{
    VOS_UINT32 ulIndex;

    for (ulIndex = 0; ulIndex < SOCKET_BUTT; ulIndex++)
    {
        if (SOCK_NULL != g_astSockInfo[ulIndex].socket)
        {
            (VOS_VOID)VOS_SmP(g_astSockInfo[ulIndex].SmClose, 0);

            closesocket(g_astSockInfo[ulIndex].socket);

            g_astSockInfo[ulIndex].socket = SOCK_NULL;

            /*lint -e534*/
            VOS_SmV(g_astSockInfo[ulIndex].SmClose);
            /*lint +e534*/
        }
    }

    return;
}
#endif

/*****************************************************************************
 Prototype      : PPM_SockUdpInit
 Description    : 初始化IND通道的socket服务器端
 Input          : pstSockInfo  -- socket控制结构体
 Output         : void
 Return Value   : VOS_OK :初始化成功
                  VOS_ERR:初始化失败

 History        : ---
    Date        : 2014-05-29
    Author      : h59254
    Modification: Created function
 *****************************************************************************/
VOS_UINT32 PPM_SockUdpInit(VOS_VOID)
{
    COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo = g_astSockInfo + SOCKET_OM_IND;
#if 0
    VOS_INT sndbuf = 0; /* Send buffer size */
    VOS_INT ret = 0;
    VOS_INT optlen = 0;
#endif
    pstSockInfo->socket = socket(AF_INET, SOCK_DGRAM, 0);

    if (VOS_OK > pstSockInfo->socket)
    {
        return VOS_ERR;
    }
#if 0
    sndbuf = 128*1024; /* Send buffer size */

    ret = setsockopt(pstSockInfo->socket, SOL_SOCKET, SO_SNDBUF, &sndbuf, sizeof(VOS_INT));
    if(ret)
    {
        vos_printf("setsockopt failed %d.\n", ret);
    }
    else
    {
        vos_printf("setsockopt success.\n");
    }

    optlen = sizeof(VOS_INT);
    ret = getsockopt(pstSockInfo->socket, SOL_SOCKET, SO_SNDBUF, &sndbuf, &optlen);

    vos_printf("getsockopt ret %d, sndbuf %d, optlen %d.\n", ret, sndbuf, optlen);
#endif
    /* 创建SOCKET保护信号量 */
    if (CPM_WIFI_OM_IND_PORT == pstSockInfo->enPhyPort)
    {
        if(VOS_OK != VOS_SmMCreate("INDSOCK", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &pstSockInfo->SmClose))
        {
            closesocket(pstSockInfo->socket);
            return VOS_ERR;
        }
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 Prototype      : Sock_TcpInit
 Description    : 初始化Socket服务器端
 Input          : VOS_VOID
 Output         : void
 Return Value   : VOS_TRUE :初始化成功
                  VOS_FALSE:初始化失败

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
 *****************************************************************************/
VOS_BOOL PPM_SockTcpInit(COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo)
{
    /* 创建SOCKET保护信号量 */
    if (CPM_WIFI_OM_CFG_PORT == pstSockInfo->enPhyPort)
    {
        if(VOS_OK != VOS_SmMCreate("CFGSOCK", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &pstSockInfo->SmClose))
        {
            return VOS_FALSE;
        }
    }
    else if (CPM_WIFI_AT_PORT == pstSockInfo->enPhyPort)
    {
        if(VOS_OK != VOS_SmMCreate("ATSOCK", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &pstSockInfo->SmClose))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_FALSE;
    }
    return VOS_TRUE;
}

/*****************************************************************************
 Prototype      : PPM_SockBindListen
 Description    :
 Input          : lpParameter - Unused.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_VOID PPM_SockBindListen(COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo)
{
    struct sockaddr_in  sAddr;
    VOS_INT             lAddLen;

    if((SOCK_NULL != pstSockInfo->listener)||
       (SOCK_NULL != pstSockInfo->socket))
    {
        return;
    }

    pstSockInfo->listener = socket(AF_INET, SOCK_STREAM, 0);

    if (VOS_OK > pstSockInfo->listener)
    {
        vos_printf("[%s][%d]:socket err !\n",__FUNCTION__,__LINE__);
        pstSockInfo->listener = SOCK_NULL;
        VOS_TaskDelay(100);/*delay 100 ms*/
        return ;
    }

    /*lint -e534*/
    VOS_MemSet(&sAddr, 0, sizeof(sAddr));
    /*lint +e534*/
    sAddr.sin_family = AF_INET;

    sAddr.sin_addr.s_addr = 0;

    /* 监听的端口号 */
    sAddr.sin_port = htons(pstSockInfo->usPort);

    lAddLen = sizeof(struct sockaddr_in);

    /* 将监听Socket绑定到对应的端口上 */
    if (SOCKET_ERROR == bind(pstSockInfo->listener, (struct sockaddr *)&sAddr, lAddLen))
    {
        closesocket(pstSockInfo->listener);
        pstSockInfo->listener = SOCK_NULL;
        vos_printf("[%s][%d]:bind err !\n",__FUNCTION__,__LINE__);
        return ;
    }

    /* 设置服务器端监听的最大客户端数 */
    if (SOCKET_ERROR == listen(pstSockInfo->listener, SOCKET_NUM_MAX))
    {
        closesocket(pstSockInfo->listener);
        pstSockInfo->listener = SOCK_NULL;
        vos_printf("[%s][%d]:listen err !\n",__FUNCTION__,__LINE__);
        return ;
    }
}

VOS_VOID PPM_SockAcceptRecv(COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo)
{
    Ip_fd_set                               listen1,listen2;
    VOS_INT32                               ret;
    VOS_INT32                               len;
    struct sockaddr_in                      from;
    VOS_ULONG                               ulLockLevel;
    SOCKET                                  socket;
    SOCKET                                  maxSocket;

    if((SOCK_NULL == pstSockInfo->listener)&&(SOCK_NULL == pstSockInfo->socket))
    {
        vos_printf("[%s][%d]:listener && socket err ! %d\n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        return;
    }
    HI_FD_ZERO(&listen1);
    HI_FD_ZERO(&listen2);

    HI_FD_SET(pstSockInfo->listener, &listen1);

    if(SOCK_NULL != pstSockInfo->socket)
    {
        HI_FD_SET(pstSockInfo->socket, &listen1);
    }

    VOS_MemCpy(&listen2,&listen1,sizeof(Ip_fd_set));

    maxSocket = pstSockInfo->socket > pstSockInfo->listener ? pstSockInfo->socket : pstSockInfo->listener;

    ret = select((int)maxSocket + 1,&listen1, NULL, &listen2, NULL);
    if(ret < 0)
    {
        vos_printf("[%s][%d]:select err ! %d \n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        return;
    }

    if((pstSockInfo->listener != SOCK_NULL) && (HI_FD_ISSET(pstSockInfo->listener, &listen1)))
    {
        len = sizeof(struct sockaddr_in);
        socket = accept(pstSockInfo->listener, (struct sockaddr *)&from, (int *)&len);
        if(socket < 0)
        {
            closesocket(pstSockInfo->listener);
            pstSockInfo->listener = SOCK_NULL;
            vos_printf("[%s][%d]:accept err !%d \n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        }
        else
        {
            if(SOCK_NULL != pstSockInfo->socket)
            {
                if(pstSockInfo->enPhyPort == CPM_WIFI_OM_CFG_PORT)
                {
                    g_ulOmIsReConn = VOS_TRUE;
                }
                if(pstSockInfo->enPhyPort == CPM_WIFI_AT_PORT)
                {
                    g_ulAtIsReConn = VOS_TRUE;
                }
                (VOS_VOID)VOS_SmP(pstSockInfo->SmClose, 0);
                closesocket(pstSockInfo->socket);
                /*lint -e534*/
                VOS_SmV(pstSockInfo->SmClose);
                /*lint +e534*/
            }

            (VOS_VOID)VOS_SmP(pstSockInfo->SmClose, 0);
            pstSockInfo->socket = socket;
            /*lint -e534*/
            VOS_SmV(pstSockInfo->SmClose);
            /*lint +e534*/

            if(CPM_WIFI_OM_CFG_PORT == pstSockInfo->enPhyPort)
            {
                if(0 > getpeername(pstSockInfo->socket, &g_stUdpInfo.stAddr, (int *)&len))
                {
                    vos_printf("getpeername failed.\n");
                }
                else
                {
                    /* 获取对端地址后，修改端口号，用于UDP传输 */
                    g_stUdpInfo.stAddr.sin_port = htons(g_astSockInfo[SOCKET_OM_IND].usPort);

                    g_stUdpInfo.bStatus = VOS_TRUE;
                }
            }
        }
    }

    if(SOCK_NULL == pstSockInfo->socket)
    {
        vos_printf("[%s][%d]:SOCK_NULL == pstSockInfo->socket ,%d!\n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        return;
    }

    ret = recv((int)pstSockInfo->socket, pstSockInfo->aucBuf, SOCK_OM_MSG_LEN, 0);
    if(ret <= 0)    /*客户端断开之后服务端会持续受到长度为0的数据包*/
    {
        (VOS_VOID)VOS_SmP(pstSockInfo->SmClose, 0);
        shutdown(pstSockInfo->socket,SHUT_RDWR);
        pstSockInfo->socket   = SOCK_NULL;
        /*lint -e534*/
        VOS_SmV(pstSockInfo->SmClose);
        /*lint +e534*/
        if(pstSockInfo->enPhyPort == CPM_WIFI_OM_CFG_PORT)
        {
            PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_CNF);

            g_stUdpInfo.bStatus = VOS_FALSE;
        }
        vos_printf("[%s][%d]:rcv err %d!\n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        return;
    }
    
    if(pstSockInfo->enPhyPort == CPM_WIFI_OM_CFG_PORT)
    {
        /*lint -e40*/
        OM_ACPU_DEBUG_CHANNEL_TRACE(pstSockInfo->enPhyPort, (VOS_UINT8*)pstSockInfo->aucBuf, ret, OM_ACPU_RECV_SOCKET);
        /*lint +e40*/
    }

    VOS_SpinLockIntLock(&g_stSockTaskSpinLock, ulLockLevel);
    /*将接收到的数据提交给上层处理*/
    CPM_ComRcv(pstSockInfo->enPhyPort, pstSockInfo->aucBuf, ret);

    VOS_SpinUnlockIntUnlock(&g_stSockTaskSpinLock, ulLockLevel);
}

/*****************************************************************************
 Prototype      : Sock_ServerProc
 Description    : 服务器线程，用来处理服务器端和客户端的所有请求。
 Input          : lpParameter - Unused.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_VOID PPM_SockServerProc(COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo)
{
    /* coverity[no_escape] */
    for(;;)
    {
        PPM_SockBindListen(pstSockInfo);
        PPM_SockAcceptRecv(pstSockInfo);
    }

}

/*****************************************************************************
 Prototype      : PPM_SockOmServerTask
 Description    : 服务器线程，用来处理OM配置请求
 Input          : lpParameter - Unused.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2014-05-29
    Author      : h59254
    Modification: Created function
*****************************************************************************/
VOS_VOID PPM_SockOmServerTask(VOS_VOID)
{
    /* 初始化CFG口的SOCKET，采用TCP协议 */
    if (VOS_FALSE == PPM_SockTcpInit(g_astSockInfo + SOCKET_OM_CFG))
    {
        return;
    }

    g_ulSockState = SOCK_START;

	g_ulSockOMInitState = VOS_TRUE;
    /* CFG口自处理循环处理入口 */
    PPM_SockServerProc(g_astSockInfo + SOCKET_OM_CFG);

    return;
}


/*****************************************************************************
 Prototype      : Sock_AtServerTask
 Description    : 服务器线程，用来处理AT命令请求
 Input          : lpParameter - Unused.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2014-05-29
    Author      : h59254
    Modification: Created function
*****************************************************************************/
VOS_VOID PPM_SockAtServerTask(VOS_VOID)
{
    /* 初始化SOCKET */
    if (VOS_FALSE == PPM_SockTcpInit(g_astSockInfo + SOCKET_AT))
    {
        return;
    }

    g_ulSockATInitState = VOS_TRUE;

    PPM_SockServerProc(g_astSockInfo + SOCKET_AT);

    return;
}

/* UDP单包包长最大65535字节，减去UDP包头后最大65507个字节 */
#define UDP_MAX_LEN	    65507

/* 获取UDP端口发送的信息 */
VOS_UINT32 PPM_SocketGetUdpInfo(VOS_VOID)
{
    return g_stUdpInfo.ulTotalLen;
}


/*****************************************************************************
 Prototype      : PPM_SockOMIndComSend
 Description    : 提供给上层OM 主动上报数据发送的接口.
 Input          : pucVirAddr:   数据虚地址
                  pucPhyAddr:   数据实地址
                  ulLength:     数据长度
 Output         : void
 Return Value   : VOS_ERR  - 发送失败
                  VOS_OK   - 发送成功

 History        : ---
    Date        : 2014-05-29
    Author      : h59254
    Modification: Created function
 *****************************************************************************/
VOS_INT32 PPM_SockOMIndComSend(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT16 uslength)
{
    SOCKET                              socket;
    VOS_INT                             nSndNum;
    VOS_UINT16  ustimes = 0, uslen = 0, i;

    (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_OM_IND].SmClose, 0);

    socket = g_astSockInfo[SOCKET_OM_IND].socket;

    if ((SOCK_NULL == socket) || (VOS_FALSE == g_stUdpInfo.bStatus))
    {
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_OM_IND].SmClose);
        /*lint +e534*/

        return VOS_ERR;
    }

    if(uslength > UDP_MAX_LEN)
    {
        ustimes = uslength / UDP_MAX_LEN;
        uslen   = uslength % UDP_MAX_LEN;
    }
    else
    {
        ustimes = 0;
        uslen   = uslength;
    }

    /* 调用sendto将数据通过socket发送出去，走UDP */
    /* coverity[overrun-buffer-val] */
    for(i = 0; i < ustimes; i++)
    {
        /* coverity[overrun-buffer-val] */
        nSndNum = sendto(socket, (pucVirAddr + (i*UDP_MAX_LEN)), UDP_MAX_LEN, 0, &g_stUdpInfo.stAddr, sizeof(g_stUdpInfo.stAddr));

        if (nSndNum != UDP_MAX_LEN)
        {
            vos_printf("uslength %d, nSndNum %d.\n", UDP_MAX_LEN, nSndNum);

            /*lint -e534*/
            VOS_SmV(g_astSockInfo[SOCKET_OM_IND].SmClose);
            /*lint +e534*/

            return VOS_ERR;
        }
        else
        {
            g_stUdpInfo.ulTotalLen += nSndNum;
        }
    }

    if(0 != uslen)
    {
        nSndNum = sendto(socket, (pucVirAddr + (ustimes*UDP_MAX_LEN)), uslen, 0, &g_stUdpInfo.stAddr, sizeof(g_stUdpInfo.stAddr));

        if (nSndNum != uslen)
        {
            vos_printf("uslength %d, nSndNum %d.\n", uslen, nSndNum);

            /*lint -e534*/
            VOS_SmV(g_astSockInfo[SOCKET_OM_IND].SmClose);
            /*lint +e534*/

            return VOS_ERR;
        }
        else
        {
            g_stUdpInfo.ulTotalLen += nSndNum;
        }
    }

    /*lint -e534*/
    VOS_SmV(g_astSockInfo[SOCKET_OM_IND].SmClose);
    /*lint +e534*/

    return VOS_OK;
}


/*****************************************************************************
 Prototype      : PPM_SockOMCfgComSend
 Description    : 提供给上层OM CFG响应数据发送的接口.
 Input          : pucVirAddr:   数据虚地址
                  pucPhyAddr:   数据实地址
                  ulLength:     数据长度
 Output         : void
 Return Value   : VOS_ERR  - 发送失败
                  VOS_OK   - 发送成功

 History        : ---
    Date        : 2014-05-29
    Author      : h59254
    Modification: Created function
 *****************************************************************************/
VOS_INT32 PPM_SockOMCfgComSend(VOS_UINT8* pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT16 uslength)
{
    SOCKET socket;
    VOS_INT nSndNum;

    if (VOS_FALSE == g_ulSockOMInitState)
    {
        return VOS_ERR;
    }

    (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_OM_CFG].SmClose, 0);

    socket = g_astSockInfo[SOCKET_OM_CFG].socket;

    if (SOCK_NULL == socket)
    {
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_OM_CFG].SmClose);
        /*lint +e534*/
        vos_printf("[%s][%d]:socket err !\n",__FUNCTION__,__LINE__);
        return VOS_ERR;
    }
    
    /*lint -e40*/
    OM_ACPU_DEBUG_CHANNEL_TRACE(CPM_WIFI_OM_CFG_PORT, (VOS_UINT8*)pucVirAddr, uslength, OM_ACPU_SEND_SOCKET);
    /*lint +e40*/

    /* 调用send将数据通过socket发送出去，走TCP */
    nSndNum = send(socket, pucVirAddr, uslength, 0);

    /*lint -e534*/
    VOS_SmV(g_astSockInfo[SOCKET_OM_CFG].SmClose);
    /*lint +e534*/

    if (nSndNum != uslength)
    {
        vos_printf("[%s][%d]:send err %d,%d!\n",__FUNCTION__,__LINE__,nSndNum,uslength);
        if(g_ulOmIsReConn == VOS_TRUE)
        {
            vos_printf("[%s][%d]:Re Conn %d,%d!\n",__FUNCTION__,__LINE__,nSndNum,uslength);
			return VOS_ERR;
        }
        PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_CNF);

        g_stUdpInfo.bStatus = VOS_FALSE;

        (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_OM_CFG].SmClose, 0);

		closesocket(g_astSockInfo[SOCKET_OM_CFG].socket);

		g_astSockInfo[SOCKET_OM_CFG].socket = SOCK_NULL;

        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_OM_CFG].SmClose);
        /*lint +e534*/

        return VOS_ERR;
    }

    g_ulOmIsReConn = VOS_FALSE;

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : PPM_SockATComSend
 Description    : 提供给上层AT发送数据的接口.
 Input          : pucVirAddr:   数据虚地址
                  pucPhyAddr:   数据实地址
                  ulLength:     数据长度
 Output         : void
 Return Value   : VOS_ERR  - 发送失败
                  VOS_OK   - 发送成功

 History        : ---
    Date        : 2014-05-29
    Author      : h59254
    Modification: Created function
 *****************************************************************************/
VOS_INT32 PPM_SockATComSend(VOS_UINT8* pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT16 uslength)
{
    SOCKET socket;
    VOS_INT nSndNum;

    if (VOS_FALSE == g_ulSockATInitState)
    {
        return VOS_ERR;
    }

    (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_AT].SmClose, 0);

    socket = g_astSockInfo[SOCKET_AT].socket;

    if (SOCK_NULL == socket)
    {
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_AT].SmClose);
        /*lint +e534*/
        vos_printf("[%s][%d]:socket err !\n",__FUNCTION__,__LINE__);
        return VOS_ERR;
    }

    /* 调用send将数据通过socket发送出去，走TCP */
    nSndNum = send(socket, pucVirAddr, uslength, MSG_DONTWAIT);

    /*lint -e534*/
    VOS_SmV(g_astSockInfo[SOCKET_AT].SmClose);
    /*lint +e534*/
    if (nSndNum != uslength)
    {
        vos_printf("[%s][%d]:send err %d,%d!\n",__FUNCTION__,__LINE__,nSndNum,uslength);
        if(g_ulAtIsReConn == VOS_TRUE)
        {
            vos_printf("[%s][%d]:Re Conn %d,%d!\n",__FUNCTION__,__LINE__,nSndNum,uslength);
			return VOS_ERR;
        }
        (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_AT].SmClose, 0);
		closesocket(g_astSockInfo[SOCKET_AT].socket);
		g_astSockInfo[SOCKET_AT].socket =SOCK_NULL;
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_AT].SmClose);
        /*lint +e534*/
        return VOS_ERR;
    }

    g_ulAtIsReConn = VOS_FALSE;

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : Sock_PortInit
 功能描述  : 用于WIFI通道的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年1月21日
     作    者  : s00207770
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_SockPortInit(VOS_VOID)
{
#if (VOS_OS_VER != VOS_WIN32)
    if ((BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
        && (VOS_TRUE == PPM_SockIsEnable()))
    {
        /*CPM_PhySendReg(CPM_WIFI_OM_IND_PORT,    (CPM_SEND_FUNC)PPM_SockOMIndComSend);*/
        CPM_PhySendReg(CPM_WIFI_OM_IND_PORT,    (CPM_SEND_FUNC)PPM_SockOMIndComSend);
        CPM_PhySendReg(CPM_WIFI_OM_CFG_PORT,    (CPM_SEND_FUNC)PPM_SockOMCfgComSend);
        CPM_PhySendReg(CPM_WIFI_AT_PORT,        (CPM_SEND_FUNC)PPM_SockATComSend);
    }
#endif

    VOS_SpinLockInit(&g_stSockTaskSpinLock);

    return VOS_OK;
}

#endif


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




