



/*****************************************************************************
  1 头文件包含
**************************************************************************** */
#include "OmCommonPpm.h"
#include "cpm.h"
#include "omprivate.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "msp_diag.h"
#include "diag_common.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_COMMON_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 全局变量定义
**************************************************************************** */
/* 用于ACPU上USB设备的UDI句柄 */
UDI_HANDLE                              g_astOMPortUDIHandle[OM_PORT_HANDLE_BUTT];

/* USB承载的OM IND端口中，伪造为同步接口使用的数据结构体 */
OM_PSEUDO_SYNC_STRU                     g_stUsbIndPseudoSync;

/* USB承载的OM CNF端口中，伪造为同步接口使用的数据结构体 */
OM_PSEUDO_SYNC_STRU                     g_stUsbCfgPseudoSync;

VOS_UINT32                              g_ulUSBSendErrCnt   = 0;

/* 端口切换信息的数据结构体 */
PPM_PORT_CFG_INFO_STRU                  g_stPpmPortSwitchInfo;

/* 自旋锁，用来作AT命令端口切换的临界资源保护 */
VOS_SPINLOCK                            g_stPpmPortSwitchSpinLock;

VOS_BOOL                                g_bPpmLogCompress   = VOS_FALSE;


OM_ACPU_DEBUG_INFO                      g_stAcpuDebugInfo;

VOS_UINT32                              g_ulOmAcpuDbgFlag = VOS_FALSE;

/*****************************************************************************
  3 外部引用声明
*****************************************************************************/
extern OM_CHANNLE_PORT_CFG_STRU         g_stPortCfg;
extern VOS_SPINLOCK                     g_stScmSoftDecodeDataRcvSpinLock;
extern VOS_SPINLOCK                     g_stCbtScmDataRcvSpinLock;
/*****************************************************************************
  4 函数实现
*****************************************************************************/
#if (FEATURE_HISOCKET == FEATURE_ON)
extern VOS_UINT32 PPM_SockPortInit(VOS_VOID);
#endif

/*****************************************************************************
 函 数 名  : PPM_DisconnectGUPort
 功能描述  : GU断开OM端口
 输入参数  : ucCpuId:CpuId
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2014年05月26日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel)
{
#if 0 /* 断链码流，仅供参考 */
    VOS_UINT8                           aucMsg[]={0x0a,         /* FuncType */
                                                  0x01,         /* CpuId */
                                                  0x08, 0x00,   /* Len */
                                                  0xB3, 0x80,   /* PrimId */
                                                  0x00, 0x00,   /* ToolId */
                                                  0x01, 0x00, 0x00, 0x00};

    MsgBlock                           *pstMsg;
    APP_OM_MSG_EX_STRU                 *pstAppOmMsg;

    pstMsg = (MsgBlock *)VOS_AllocMsg(UEPS_PID_OMRL, sizeof(MsgBlock) + sizeof(APP_OM_MSG_EX_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstAppOmMsg = (APP_OM_MSG_EX_STRU*)pstMsg->aucValue;

    if (OM_LOGIC_CHANNEL_CBT == enChannel)
    {
        pstMsg->ulSenderPid = ACPU_PID_OM;
        pstMsg->ulReceiverPid = ACPU_PID_CBT;
    }
    else
    {
        pstMsg->ulReceiverPid = ACPU_PID_OM;
    }

    pstAppOmMsg->ucFuncType    = OM_QUERY_FUNC;
    pstAppOmMsg->ucCpuId       = (VOS_UINT8)enChannel;
    pstAppOmMsg->usLength      = sizeof(pstAppOmMsg->aucPara)
                                + sizeof(pstAppOmMsg->usToolId)
                                + sizeof(pstAppOmMsg->usPrimId);
    pstAppOmMsg->usToolId      = VOS_NULL;
    pstAppOmMsg->usPrimId      = APP_OM_RELEASE_REQ;

    (VOS_VOID)VOS_SendMsg(UEPS_PID_OMRL, pstMsg);
#endif

    return VOS_OK;
}
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : PPM_DisconnectTLPort
 功能描述  : TL断开OM端口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2014年05月26日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_DisconnectTLPort(VOS_VOID)
{
    DIAG_DATA_MSG_STRU                 *pstMsg;

    pstMsg = (DIAG_DATA_MSG_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, sizeof(DIAG_DATA_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstMsg->ulReceiverPid = MSP_PID_DIAG_APP_AGENT;
    pstMsg->ulMsgId       = ID_MSG_DIAG_HSO_DISCONN_IND;

    (VOS_VOID)VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstMsg);

    return VOS_OK;
}
#endif
/*****************************************************************************
 函 数 名  : PPM_DisconnectAllPort
 功能描述  : GUTL断开OM端口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2014年05月26日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel)
{
#if (FEATURE_ON == FEATURE_LTE)
    PPM_DisconnectTLPort();
#endif
    PPM_DisconnectGUPort(enChannel);

    return;
}

/*****************************************************************************
 函 数 名  : PPM_GetSendDataLen
 功能描述  : PPM对数据发送长度进行处理
 输入参数  : ulDataLen: SOCP通道的数据长度
             enChanID:  SOCP channel ID
 输出参数  : pulSendDataLen:实际发送出去的数据长度
             penPhyport:指向物理端口号
 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2014年5月25日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_VOID PPM_GetSendDataLen(SOCP_CODER_DST_ENUM_U32 enChanID, VOS_UINT32 ulDataLen, VOS_UINT32 *pulSendDataLen, CPM_PHY_PORT_ENUM_UINT32 *penPhyport)
{
    CPM_PHY_PORT_ENUM_UINT32    enPhyport;

    if (SOCP_CODER_DST_OM_CNF == enChanID)
    {
        enPhyport = CPM_QueryPhyPort(CPM_OM_CFG_COMM);
    }
    else
    {
        enPhyport = CPM_QueryPhyPort(CPM_OM_IND_COMM);
    }


    /*当发送是通过USB并且发送长度大于60k的时候，需要限制发送长度*/
    if (((CPM_IND_PORT == enPhyport) || (CPM_CFG_PORT == enPhyport))
        &&(ulDataLen > USB_MAX_DATA_LEN))
    {
        /*lint -e534*/
        LogPrint1("PPM_GetSendDataLen: Change the send Data Len %d", (VOS_INT)ulDataLen);
        /*lint +e534*/

        *pulSendDataLen = USB_MAX_DATA_LEN;
    }
    else
    {
        *pulSendDataLen = ulDataLen;  /*其他情况下不需要调整当前的大小，包括sd、wifi*/
    }

    *penPhyport = enPhyport;
    return;
}

/*****************************************************************************
 函 数 名  : PPM_PortStatus
 功能描述  : 用于ACPU上面处理物理端口断开后的OM链接断开
 输入参数  : enHandle:   UDI设备句柄
             enPhyPort:  物理端口
             enPortState:端口状态
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2014年5月25日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_VOID PPM_PortStatus(OM_PROT_HANDLE_ENUM_UINT32 enHandle, CPM_PHY_PORT_ENUM_UINT32 enPhyPort,ACM_EVT_E enPortState)
{
    VOS_ULONG                           ulLockLevel;
    OM_LOGIC_CHANNEL_ENUM_UINT32        enChannel;
    VOS_BOOL                            ulSndMsg;

    if (ACM_EVT_DEV_SUSPEND == enPortState)
    {
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutTime = mdrv_timer_get_normal_timestamp();

        VOS_SpinLockIntLock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

        ulSndMsg  = VOS_FALSE;
        enChannel = OM_LOGIC_CHANNEL_BUTT;

        /* CFG端口处理GU和TL的端口断开，发消息到GU和TL去处理，但不断开CPM的关联 */
        if (OM_USB_CFG_PORT_HANDLE == enHandle)
        {
            if (enPhyPort == CPM_QueryPhyPort(CPM_OM_CFG_COMM))
            {
                ulSndMsg  = VOS_TRUE;
                enChannel = OM_LOGIC_CHANNEL_CNF;
            }
        }
        /* IND端口断开时发消息到GU和TL去处理 */
        else if (OM_USB_IND_PORT_HANDLE == enHandle)
        {
            if (enPhyPort == CPM_QueryPhyPort(CPM_OM_IND_COMM))
            {
                ulSndMsg  = VOS_TRUE;
                enChannel = OM_LOGIC_CHANNEL_IND;
            }
        }
        else
        {

        }

        VOS_SpinUnlockIntUnlock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

        if (VOS_TRUE == ulSndMsg)
        {
            PPM_DisconnectAllPort(enChannel);
        }
    }
    else if(ACM_EVT_DEV_READY == enPortState)
    {
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINTime = mdrv_timer_get_normal_timestamp();
    }
    else
    {
        /*lint -e534*/
        LogPrint2("PPM_PortStatus: The USB Port %d State %d is Unknow", (VOS_INT)enPhyPort, (VOS_INT)enPortState);
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrTime = mdrv_timer_get_normal_timestamp();
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPM_PortCloseProc
 功能描述  : OM端口已经消失，需要关闭USB端口
 输入参数  : enHandle: 端口句柄枚举定义，关闭后端口设置为VOS_ERROR
             enPhyPort:物理端口
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2014年5月25日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_VOID PPM_PortCloseProc(OM_PROT_HANDLE_ENUM_UINT32  enHandle, CPM_PHY_PORT_ENUM_UINT32 enPhyPort)
{
    VOS_ULONG                           ulLockLevel;
    OM_LOGIC_CHANNEL_ENUM_UINT32        enChannel;
    VOS_BOOL                            ulSndMsg;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseSlice = mdrv_timer_get_normal_timestamp();

    if (VOS_ERROR == g_astOMPortUDIHandle[enHandle])
    {
        return;
    }

    mdrv_udi_close(g_astOMPortUDIHandle[enHandle]);

    g_astOMPortUDIHandle[enHandle] = VOS_ERROR;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkSlice = mdrv_timer_get_normal_timestamp();

    VOS_SpinLockIntLock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    ulSndMsg  = VOS_FALSE;
    enChannel = OM_LOGIC_CHANNEL_BUTT;

    /* CFG端口处理GU和TL的端口断开，发消息到GU和TL去处理，但不断开CPM的关联 */
    if (OM_USB_CFG_PORT_HANDLE == enHandle)
    {
        if (enPhyPort == CPM_QueryPhyPort(CPM_OM_CFG_COMM))
        {
            ulSndMsg  = VOS_TRUE;
            enChannel = OM_LOGIC_CHANNEL_CNF;
        }
    }
    /* IND端口断开时发消息到GU和TL去处理，但不断开CPM的关联 */
    else if (OM_USB_IND_PORT_HANDLE == enHandle)
    {
        if (enPhyPort == CPM_QueryPhyPort(CPM_OM_IND_COMM))
        {
            ulSndMsg  = VOS_TRUE;
            enChannel = OM_LOGIC_CHANNEL_IND;
        }
    }
    else
    {

    }

    VOS_SpinUnlockIntUnlock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    if (VOS_TRUE == ulSndMsg)
    {
        PPM_DisconnectAllPort(enChannel);
    }

    return;
}

/*****************************************************************************
 函 数 名  : GU_OamUSBReadData
 功能描述  : 用于ACPU上面底软把数据通过ICC发送给OM模块
 输入参数  : enPhyPort: 物理端口
             UdiHandle:设备句柄
             enHandle: UDI设备句柄数组偏移
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK

 修改历史      :
  1.日    期   : 2014年5月25日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_INT32 PPM_ReadPortData(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, UDI_HANDLE UdiHandle, OM_PROT_HANDLE_ENUM_UINT32 enHandle)
{
    ACM_WR_ASYNC_INFO                   stInfo;

    diag_PTR(EN_DIAG_PTR_PPM_READDATA);

    if (VOS_ERROR == UdiHandle)
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_PortCloseProc: Input HANDLE  is err. \n");
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleErr++;

        diag_PTR(EN_DIAG_PTR_PPM_ERR1);

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&stInfo, 0, sizeof(stInfo));
    /*lint +e534*/

    /* 获取USB的IO CTRL口的读缓存 */
    if (VOS_OK != mdrv_udi_ioctl(UdiHandle, UDI_ACM_IOCTL_GET_READ_BUFFER_CB, &stInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortData:Call mdrv_udi_ioctl is Failed\n");
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadGetBufferErr++;
        diag_PTR(EN_DIAG_PTR_PPM_ERR2);

        return VOS_ERR;
    }

    /*lint -e40*/
    OM_ACPU_DEBUG_CHANNEL_TRACE(enPhyPort, (VOS_UINT8*)stInfo.pVirAddr, stInfo.u32Size, OM_ACPU_USB_CB);
    /*lint +e40*/

    if(VOS_OK != CPM_ComRcv(enPhyPort, (VOS_UINT8*)stInfo.pVirAddr, stInfo.u32Size))
    {
        /*lint -e534*/
        LogPrint1("\r\n Info: PPM_ReadPortData:Call CPM_ComRcv is NULL, PhyPort is %d\n", (VOS_INT)enPhyPort);
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiCommRcvNullPtrErr++;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktByte += stInfo.u32Size;

    if(VOS_OK != mdrv_udi_ioctl(UdiHandle, UDI_ACM_IOCTL_RETUR_BUFFER_CB, &stInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortData:Call mdrv_udi_ioctl UDI_ACM_IOCTL_RETUR_BUFFER_CB is Failed\n");
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadBufferFreeErr++;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPM_PortPseudoSyncGetSmp
 功能描述  : 伪同步接口，需要在调用底软异步写函数后，获取信号量
 输入参数  : enHandle:UDI设备句柄
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月25日
    作    者   : L00256032
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_VOID PPM_PortPseudoSyncGetSmp(OM_PROT_HANDLE_ENUM_UINT32 enHandle)
{

    return;
}

/*****************************************************************************
 函 数 名  : PPM_QueryLogPort
 功能描述  : 提供给NAS进行Log端口查询
 输入参数  : 无
 输出参数  : pulLogPort当前Log输出端口

 返 回 值  : VOS_ERR/VOS_OK

 修改历史  :
   1.日    期  : 2014年06月3日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_QueryLogPort(VOS_UINT32  *pulLogPort)
{
    if (VOS_NULL_PTR == pulLogPort)
    {
        /*lint -e534*/
        vos_printf("\r\n PPM_QueryLogPort: para is NULL !!\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    *pulLogPort = g_stPortCfg.enPortNum;

    if ((CPM_OM_PORT_TYPE_USB != *pulLogPort) && (CPM_OM_PORT_TYPE_VCOM != *pulLogPort))
    {
        /*lint -e534*/
        vos_printf("\r\n PPM_QueryLogPort: log prot is not support. port:%d!!\n", *pulLogPort);
        /*lint +e534*/
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPM_LogPortSwitch
 功能描述  : 提供给NAS进行端口切换
 输入参数  : enPhyPort: 带切换物理端口枚举值
             ulEffect:是否立即生效
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK

 修改历史  :
   1.日    期  : 2014年6月3日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_LogPortSwitch(VOS_UINT32  ulPhyPort, VOS_BOOL ulEffect)
{
    CPM_PHY_PORT_ENUM_UINT32            enPhyCfgPort;
    CPM_PHY_PORT_ENUM_UINT32            enPhyIndPort;
    VOS_ULONG                           ulLockLevel;
    VOS_BOOL                            ulSndMsg;

    if ((CPM_OM_PORT_TYPE_USB != ulPhyPort) && (CPM_OM_PORT_TYPE_VCOM != ulPhyPort))
    {
        /*lint -e534*/
        vos_printf("\r\n PPM_LogPortSwitch: enPhyPort is error.port %d\n", ulPhyPort);
        /*lint +e534*/

        g_stPpmPortSwitchInfo.ulPortTypeErr++;

        return VOS_ERR;
    }

    /* 切换的端口与当前端口一致不切换 */
    if (ulPhyPort == g_stPortCfg.enPortNum)
    {
        /* 切换到VCOM输出时在LOG延迟写入开启情况下需要重新设置SOCP的超时中断 */
        if (CPM_OM_PORT_TYPE_VCOM == g_stPortCfg.enPortNum)
        {
            mdrv_socp_set_log_int_timeout();
        }

        /* 为了规避USB输出时开启了延时写入无法连接工具,切换到USB输出时需要重新设置SOCP的超时中断到默认值 */
        if (CPM_OM_PORT_TYPE_USB == g_stPortCfg.enPortNum)
        {
            mdrv_socp_set_log_int_default_timeout();
        }
        return VOS_OK;
    }

    g_stPpmPortSwitchInfo.ulStartSlice = mdrv_timer_get_normal_timestamp();

    enPhyCfgPort = CPM_QueryPhyPort(CPM_OM_CFG_COMM);
    enPhyIndPort = CPM_QueryPhyPort(CPM_OM_IND_COMM);

    ulSndMsg = VOS_FALSE;

    VOS_SpinLockIntLock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    /* 切换到VCOM输出 */
    if (CPM_OM_PORT_TYPE_VCOM == ulPhyPort)
    {
        /* 当前是USB输出 */
        if ((CPM_CFG_PORT == enPhyCfgPort) && (CPM_IND_PORT == enPhyIndPort))
        {
            /* 需要断开连接 */
            ulSndMsg = VOS_TRUE;

            CPM_DisconnectPorts(CPM_CFG_PORT, CPM_OM_CFG_COMM);
            CPM_DisconnectPorts(CPM_IND_PORT, CPM_OM_IND_COMM);
        }

        /* 当前OM走VCOM上报 */
        CPM_ConnectPorts(CPM_VCOM_CFG_PORT, CPM_OM_CFG_COMM);
        CPM_ConnectPorts(CPM_VCOM_IND_PORT, CPM_OM_IND_COMM);

        g_stPortCfg.enPortNum = CPM_OM_PORT_TYPE_VCOM;
    }
    /* 切换到USB输出 */
    else
    {
        /* 当前是VCOM输出 */
        if ((CPM_VCOM_CFG_PORT == enPhyCfgPort) && (CPM_VCOM_IND_PORT == enPhyIndPort))
        {
            /* 断开连接 */
            ulSndMsg = VOS_TRUE;

            CPM_DisconnectPorts(CPM_VCOM_CFG_PORT, CPM_OM_CFG_COMM);
            CPM_DisconnectPorts(CPM_VCOM_IND_PORT, CPM_OM_IND_COMM);
        }

        /* OM走USB上报 */
        CPM_ConnectPorts(CPM_CFG_PORT, CPM_OM_CFG_COMM);
        CPM_ConnectPorts(CPM_IND_PORT, CPM_OM_IND_COMM);

        g_stPortCfg.enPortNum = CPM_OM_PORT_TYPE_USB;
    }

    VOS_SpinUnlockIntUnlock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    if (VOS_TRUE == ulSndMsg)
    {
        PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_CNF);
    }
    /* 切换到VCOM输出时在LOG延迟写入开启情况下需要重新设置SOCP的超时中断 */
    if (CPM_OM_PORT_TYPE_VCOM == g_stPortCfg.enPortNum)
    {
        mdrv_socp_set_log_int_timeout();
    }

    /* 为了规避USB输出时开启了延时写入无法连接工具,切换到USB输出时需要重新设置SOCP的超时中断到默认值 */
    if (CPM_OM_PORT_TYPE_USB == g_stPortCfg.enPortNum)
    {
        mdrv_socp_set_log_int_default_timeout();
    }
    g_stPpmPortSwitchInfo.ulSwitchSucc++;
    g_stPpmPortSwitchInfo.ulEndSlice = mdrv_timer_get_normal_timestamp();

    if (VOS_TRUE == ulEffect)
    {
        if (VOS_OK != NV_Write(en_NV_Item_Om_Port_Type, &g_stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
        {
            /*lint -e534*/
            vos_printf("\r\n PPM_LogPortSwitch: NV_Write fail\n");
            /*lint +e534*/
        }
    }

    return VOS_OK;
}

VOS_UINT32 PPM_LogCompressCfg(VOS_BOOL enable)
{
    if(g_bPpmLogCompress != enable)
    {
        g_bPpmLogCompress = enable;
        if (CPM_OM_PORT_TYPE_VCOM == g_stPortCfg.enPortNum)
        {
            SCM_CoderDstCompressCfg(enable);
        }
        /*为了芯片验证，临时打桩，让USB端口也走压缩方式*/
        if (CPM_OM_PORT_TYPE_USB == g_stPortCfg.enPortNum)
        {
            SCM_CoderDstCompressCfg(enable);
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPM_UdiRegCallBackFun
 功能描述  : 用于注册UDI设备的回调函数
 输入参数  : enHandle: 端口的句柄
             ulCmdType: 命令类型
             pFunc: 注册的回调函数指针
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_UINT32 PPM_UdiRegCallBackFun(UDI_HANDLE enHandle, VOS_UINT32 ulCmdType, VOS_VOID* pFunc)
{
    if (VOS_NULL_PTR == pFunc)
    {
        return VOS_OK;
    }

    if (VOS_OK != mdrv_udi_ioctl(enHandle, ulCmdType, pFunc))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_UdiRegCallBackFun, mdrv_udi_ioctl Failed\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    return VOS_OK;
}



#define OM_SOCP_CNF_BUFFER_SIZE          (8*1024)
#define OM_SOCP_CNF_BUFFER_NUM           (8)

#define OM_SOCP_IND_BUFFER_SIZE          (2*1024)
#define OM_SOCP_IND_BUFFER_NUM           (2)


/*****************************************************************************
 函 数 名  : PPM_ReadPortDataInit
 功能描述  : 用于初始化OM使用的设备
 输入参数  : enPhyPort: 物理端口号
             enHandle: 端口的句柄
             pReadCB: 该端口上面的读取回调函数
             pWriteCB: 该端口上面的异步写回调函数
             pStateCB: 该端口上面的状态回调函数
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_VOID PPM_ReadPortDataInit(CPM_PHY_PORT_ENUM_UINT32        enPhyPort,
                                    OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                    VOS_VOID                            *pReadCB,
                                    VOS_VOID                            *pWriteCB,
                                    VOS_VOID                            *pStateCB)
{
    UDI_OPEN_PARAM_S                    stUdiPara;
    ACM_READ_BUFF_INFO                  stReadBuffInfo;
    VOS_BOOL                            isCnf = VOS_TRUE;

    /*初始化当前使用的USB通道*/
    if (CPM_IND_PORT == enPhyPort)
    {
        isCnf                      = VOS_FALSE;
        stUdiPara.devid            = UDI_ACM_LTE_DIAG_ID;
    }
    else if (CPM_CFG_PORT == enPhyPort)
    {
        isCnf                      = VOS_TRUE;
        stUdiPara.devid            = UDI_ACM_GPS_ID;
    }
    else if (CPM_HSIC_IND_PORT == enPhyPort)
    {
        isCnf                      = VOS_FALSE;
        stUdiPara.devid            = UDI_ACM_HSIC_ACM7_ID;
    }
    else if (CPM_HSIC_CFG_PORT == enPhyPort)
    {
        isCnf                      = VOS_TRUE;
        stUdiPara.devid            = UDI_ACM_HSIC_ACM8_ID;
    }
    else
    {
        /*lint -e534*/
        LogPrint1("\r\n PPM_ReadPortDataInit: Open Wrong Port %d!", (VOS_INT)enPhyPort);
        /*lint +e534*/

        return;
    }

    if(isCnf == VOS_TRUE)
    {
        stReadBuffInfo.u32BuffSize = OM_SOCP_CNF_BUFFER_SIZE;
        stReadBuffInfo.u32BuffNum  = OM_SOCP_CNF_BUFFER_NUM;
    }
    else
    {
        stReadBuffInfo.u32BuffSize = OM_SOCP_IND_BUFFER_SIZE;
        stReadBuffInfo.u32BuffNum  = OM_SOCP_IND_BUFFER_NUM;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice = mdrv_timer_get_normal_timestamp();

    if (VOS_ERROR != g_astOMPortUDIHandle[enHandle])
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit: The UDI Handle is not Null !");
        /*lint +e534*/

        return;
    }

    /* 打开OM使用的USB通道 */
    g_astOMPortUDIHandle[enHandle] = mdrv_udi_open(&stUdiPara);

    if (VOS_ERROR == g_astOMPortUDIHandle[enHandle])
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit: Open UDI ACM failed!");
        /*lint +e534*/

        return;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice = mdrv_timer_get_normal_timestamp();

    /* 配置OM使用的USB通道缓存 */
    if (VOS_OK != mdrv_udi_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl ACM_IOCTL_RELLOC_READ_BUFF Failed\r\n");
        /*lint +e534*/

        return;
    }

    /* 注册OM使用的USB读数据回调函数 */
    if (VOS_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], UDI_ACM_IOCTL_SET_READ_CB, pReadCB))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl UDI_ACM_IOCTL_SET_READ_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if(VOS_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_WRITE_CB, pWriteCB))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_WRITE_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if(VOS_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_EVT_CB, pStateCB))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_WRITE_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if (VOS_OK != mdrv_udi_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_WRITE_DO_COPY, VOS_NULL_PTR))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl ACM_IOCTL_WRITE_DO_COPY Failed\r\n");
        /*lint +e534*/

        return;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice = mdrv_timer_get_normal_timestamp();

    return;
}

/*****************************************************************************
 函 数 名  : PPM_PortSend
 功能描述  : 将输入的数据通过异步发送给PC侧
 输入参数  :  enHandle: 发送端口句柄的枚举定义
              pucVirAddr:   数据虚地址
              pucPhyAddr:   数据实地址
              ulDataLen: 数据长度
 输出参数  : 无
 返 回 值  : VOS_ERROR/VOS_OK
 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_UINT32 PPM_PortSend(OM_PROT_HANDLE_ENUM_UINT32 enHandle, VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    VOS_INT32           lRet;
    ACM_WR_ASYNC_INFO   stVcom;
    VOS_UINT32          ulInSlice;
    VOS_UINT32          ulOutSlice;
    VOS_UINT32          ulWriteSlice;
//    VOS_CHAR            aucUsbLog[100];

    if((OM_USB_CFG_PORT_HANDLE == enHandle)
        || (OM_HSIC_CFG_PORT_HANDLE == enHandle))
    {
        diag_PTR(EN_DIAG_PTR_PPM_PORTSEND);
    }

    if ((VOS_NULL_PTR == pucVirAddr) || (VOS_NULL_PTR == pucPhyAddr))
    {
        /* 打印错误 */
        /*lint -e534*/
        LogPrint("\r\nPPM_PortSend: Vir or Phy Addr is Null \n");
        /*lint +e534*/

        return CPM_SEND_PARA_ERR;
    }

    stVcom.pVirAddr = (VOS_CHAR*)pucVirAddr;
    stVcom.pPhyAddr = (VOS_CHAR*)pucPhyAddr;
    stVcom.u32Size  = ulDataLen;
    stVcom.pDrvPriv = VOS_NULL_PTR;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum1++;

    if (VOS_ERROR == g_astOMPortUDIHandle[enHandle])
    {
        /*lint -e534*/
        LogPrint("\r\nPPM_PortSend: USB HANDLE  is err. \n");
        /*lint +e534*/

        return CPM_SEND_ERR;
    }

    ulInSlice = mdrv_timer_get_normal_timestamp();

    /* 返回写入数据长度代表写操作成功 */
    lRet = mdrv_udi_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_WRITE_ASYNC, &stVcom);

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum2++;

    ulOutSlice = mdrv_timer_get_normal_timestamp();

    if(ulInSlice > ulOutSlice)
    {
        ulWriteSlice = ulInSlice - ulOutSlice;
    }
    else
    {
        ulWriteSlice = ulOutSlice - ulInSlice;
    }

    if(ulWriteSlice > g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime)
    {
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime = ulWriteSlice;
    }

    if (MDRV_OK == lRet)     /*当前发送成功*/
    {
        /* 伪同步接口，获取信号量 */
        PPM_PortPseudoSyncGetSmp(enHandle);

        return CPM_SEND_AYNC;

    }
    else if(MDRV_OK > lRet)    /*临时错误*/
    {
        /*打印信息，调用UDI接口的错误信息*/
        /*lint -e534*/
        LogPrint1("\r\nPPM_PortSend: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrNum++;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrLen    += ulDataLen;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrValue  = (VOS_UINT32)lRet;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrTime   = mdrv_timer_get_normal_timestamp();

#if 0   /* TODO:cjq */
        if (VOS_OK != OM_AcpuGetLogPath(aucUsbLog, OM_USB_LOG_FILE, OM_USB_UNITARY_LOG_FILE))
        {
            return CPM_SEND_FUNC_NULL;
        }

        if( 0 == (g_ulUSBSendErrCnt%USB_SEND_DATA_ERROR_MAX)) /*累计丢包超过限制需要记录到log文件中*/
        {
            OM_Acpu_WriteLogFile(aucUsbLog, (VOS_CHAR *)&g_stAcpuDebugInfo, sizeof(OM_ACPU_DEBUG_INFO));
        }
#endif

        g_ulUSBSendErrCnt++;

        return CPM_SEND_FUNC_NULL; /*对于临时错误，需要返回NULL丢弃数据*/
    }
    else    /*其他错误需要复位单板*/
    {
        /*打印信息，调用UDI接口*/
        /*lint -e534*/
        LogPrint1("\r\nPPM_PortSend: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/

        VOS_ProtectionReboot(OAM_USB_SEND_ERROR, lRet, (VOS_INT)enHandle,
                             (VOS_CHAR *)&g_stAcpuDebugInfo, (VOS_INT)sizeof(OM_ACPU_DEBUG_INFO));

        return CPM_SEND_ERR;
    }
}

/*****************************************************************************
 函 数 名  :GU_OamPortWriteAsyCB
 功能描述  :OM异步发送回调函数
 输入参数  :enHandle:UDI句柄
            pucData:需要发送的数据内容
            lLen:数据长度
 输出参数  :无
 返 回 值  :无
 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_VOID PPM_PortWriteAsyCB(OM_PROT_HANDLE_ENUM_UINT32 enHandle, VOS_UINT8* pucData, VOS_INT lLen)
{
    VOS_UINT32      ulRlsLen;

    if(lLen < 0)
    {
        ulRlsLen = 0;
    }
    else
    {
        ulRlsLen = (VOS_UINT32)lLen;
    }

    /* 统计数据通道的吞吐率 */
    if(OM_USB_IND_PORT_HANDLE == enHandle)
    {
        diag_ThroughputSave(EN_DIAG_THRPUT_DATA_CHN_CB, lLen);
    }

    /* 伪同步接口，释放信号量 */
    if (OM_USB_IND_PORT_HANDLE == enHandle)
    {
        g_stUsbIndPseudoSync.ulLen          = ulRlsLen;
        g_stUsbIndPseudoSync.pucAsyncCBData = pucData;


        SCM_RlsDestBuf(SOCP_CODER_DST_OM_IND, ulRlsLen);

    }
    else if (OM_USB_CFG_PORT_HANDLE == enHandle)
    {
        g_stUsbCfgPseudoSync.ulLen          = ulRlsLen;
        g_stUsbCfgPseudoSync.pucAsyncCBData = pucData;


        SCM_RlsDestBuf(SOCP_CODER_DST_OM_CNF, ulRlsLen);

    }
    else
    {
        ;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteCBNum++;

    return;
}


OM_PSEUDO_SYNC_STRU * PPM_ComPpmGetSyncInfo(VOS_VOID)
{
    return &g_stUsbIndPseudoSync;
}

OM_ACPU_DEBUG_INFO * PPM_ComPpmGetDebugInfo(VOS_VOID)
{
    return &g_stAcpuDebugInfo;
}


/*****************************************************************************
 函 数 名  : PPM_InitPhyPort
 功能描述  : 初始化物理通道
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败
 修改历史:
     1. 日期:2012-01-21
         修改人:s00207770
         修改原因:添加SOCKET端口初始化
     2. 日期:2013-12-29
         修改人:s00207770
         修改原因:修改LOG保存初始化接口
*****************************************************************************/
VOS_UINT32 PPM_InitPhyPort(VOS_VOID)
{
    if (VOS_OK != PPM_PortInit())
    {
        vos_printf("PPM_InitPhyPort: PPM_PortInit failed.\n");
        return VOS_ERR;
    }

#if ((VOS_OS_VER == VOS_WIN32) || (FEATURE_HISOCKET == FEATURE_ON))
    if (VOS_OK != PPM_SockPortInit())
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPM_PortInit
 功能描述  : 端口通道的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK   - 初始化成功
             VOS_ERR  - 初始化失败

 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_UINT32 PPM_PortInit(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stAcpuDebugInfo, 0, sizeof(g_stAcpuDebugInfo));

    VOS_MemSet(g_astOMPortUDIHandle, VOS_ERROR, sizeof(g_astOMPortUDIHandle));

    VOS_MemSet(&g_stPpmPortSwitchInfo, 0, sizeof(g_stPpmPortSwitchInfo));
    /*lint +e534*/

    VOS_SpinLockInit(&g_stPpmPortSwitchSpinLock);

    /* USB承载的虚拟端口通道的初始化 */
    PPM_UsbPortInit();

    /* Hsic承载的虚拟端口通道的初始化 */
    PPM_HsicPortInit();

    /* Vcom承载的虚拟端口通道的初始化 */
    PPM_VComPortInit();

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : OmOpenLog
 功能描述  : 打印当前OM通道的状态
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2009年5月18日
     作    者  : g47350
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OmOpenLog(VOS_UINT32 ulFlag)
{
    g_ulOmAcpuDbgFlag = ulFlag;

    return;
}


/*****************************************************************************
 函 数 名  : PPM_OmPortInfoShow
 功能描述  : 用于打印当前通道的统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2011年3月10日
     作    者  : l46160
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PPM_OmPortInfoShow(OM_PROT_HANDLE_ENUM_UINT32  enHandle)
{
    /*lint -e534*/
    vos_printf("\r\nThe Port Write num 1 is          %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum1);
    vos_printf("\r\nThe Port Write num 2 is          %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum2);
    vos_printf("\r\nThe Port Write Max Time is       0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime);

    vos_printf("\r\nThe Port Write CB Num is         %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteCBNum);

    vos_printf("\r\nThe Port Write Err Time is       %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrTime);
    vos_printf("\r\nThe Port Write Err Num  is       %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrNum);
    vos_printf("\r\nThe Port Write Err Value is      0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrValue);
    vos_printf("\r\nThe Port Write Err Len is        0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrLen);

    vos_printf("\r\nThe Port In CB Num is            %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINNum);
    vos_printf("\r\nThe Port In CB Time is           0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINTime);
    vos_printf("\r\nThe Port Out CB Num is           %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutNum);
    vos_printf("\r\nThe Port Out CB Time is          0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutTime);
    vos_printf("\r\nThe Port State CB Err Num is     %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrNum);
    vos_printf("\r\nThe Port State CB Err Time is    0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrTime);

    vos_printf("\r\nThe Port Open num is            %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum);
    vos_printf("\r\nThe Port Open slice is          0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice);

    vos_printf("\r\nThe Port Open OK num is         %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum);
    vos_printf("\r\nThe Port Open OK slice is       0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice);

    vos_printf("\r\nThe Port Open OK2 num is        %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num);
    vos_printf("\r\nThe Port Open OK2 slice is      0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice);

    vos_printf("\r\nThe Port Close num is           %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseNum);
    vos_printf("\r\nThe Port Close slice is         0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseSlice);

    vos_printf("\r\nThe Port Close OK num is        %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkNum);
    vos_printf("\r\nThe Port Close OK slice is      0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkSlice);

    vos_printf("\r\nUSB IND Pseudo sync fail num is   %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBIndPseudoSyncFailNum);
    vos_printf("\r\nUSB IND Pseudo sync fail slice is 0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBIndPseudoSyncFailSlice);
    vos_printf("\r\nUSB CFG Pseudo sync fail num is   %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCnfPseudoSyncFailNum);
    vos_printf("\r\nUSB CFG Pseudo sync fail slice is 0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCnfPseudoSyncFailSlice);

    vos_printf("\r\nThe Port UDI Handle Err num is %d",                 g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleErr);
    vos_printf("\r\nThe Port UDI Handle Get Buffer Err num is %d",      g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadGetBufferErr);
    vos_printf("\r\nThe Port UDI Handle Comm Rcv Null Ptr num is %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiCommRcvNullPtrErr);
    vos_printf("\r\nThe Port UDI Handle Read Buffer Free Err num is %d",g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadBufferFreeErr);

    vos_printf("\r\nThe Port UDI Handle Total Rcv Pkt num is %d",       g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktNum);
    vos_printf("\r\nThe Port UDI Handle Total Rcv Byte is %d",          g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktByte);
    /*lint +e534*/

    return;
}


/*****************************************************************************
 函 数 名  : PPM_OmPortDebugInfoShow
 功能描述  : 用于打印CNF\IND通道的统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2015年11月2日
     作    者  : c00326366
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PPM_OmPortDebugInfoShow(VOS_VOID)
{
    vos_printf("IND ulOmDiscardNum %d, len %d; ulUSBSendErrNum %d, Len %d; ulUSBSendNum %d, len %d.\r\n",
    g_stAcpuDebugInfo.stIndDebugInfo.ulOmDiscardNum, g_stAcpuDebugInfo.stIndDebugInfo.ulOmDiscardLen,
    g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendErrNum, g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendErrLen,
    g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendNum, g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendLen);

    vos_printf("CNF ulOmDiscardNum %d, len %d; ulUSBSendErrNum %d, Len %d; ulUSBSendNum %d, len %d.\r\n",
    g_stAcpuDebugInfo.stCnfDebugInfo.ulOmDiscardNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulOmDiscardLen,
    g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendErrNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendErrLen,
    g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendLen);
}

/*****************************************************************************
 函 数 名  : PPM_PortSwitchInfoShow
 功能描述  : 用于打印端口切换的统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年6月10日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PPM_PortSwitchInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\n Port Type Err num is %d", g_stPpmPortSwitchInfo.ulPortTypeErr);

    vos_printf("\r\n Port Switch Fail time is %d", g_stPpmPortSwitchInfo.ulSwitchFail);

    vos_printf("\r\n Port Switch Success time is %d", g_stPpmPortSwitchInfo.ulSwitchSucc);

    vos_printf("\r\n Port Switch Start slice is 0x%x", g_stPpmPortSwitchInfo.ulStartSlice);

    vos_printf("\r\n Port Switch End slice is 0x%x", g_stPpmPortSwitchInfo.ulEndSlice);
    /*lint +e534*/

    return;
}



#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




