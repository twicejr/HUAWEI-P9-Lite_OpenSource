

/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CbtPpm.c
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   : CBT的物理端口管理模块
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月31日
    作    者   : L00256032
    修改内容   : V8R1 OM_Optimize项目新增

***************************************************************************** */

/*****************************************************************************
  1 头文件包含
**************************************************************************** */
#include "AtAppVcomInterface.h"
#include "CbtPpm.h"
#include "CbtCpm.h"
#include "pamappom.h"
#include "SCMSoftDecode.h"
#include "omprivate.h"
#include "cbtapprl.h"
#include "PamOamSpecTaskDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_CBT_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 全局变量定义
**************************************************************************** */
VOS_SEM                            g_ulCbtUsbPseudoSyncSemId;   /* 伪造为同步接口需使用的信号量 */

CBT_ACPU_VCOM_DEBUG_INFO           g_stCbtVComAcpuDebugInfo;

/* 用于ACPU上CBT端口的UDI句柄 */
UDI_HANDLE                         g_ulCbtPortUDIHandle    = VOS_ERROR;

/*****************************************************************************
  3 外部引用声明
*****************************************************************************/
extern  CBTCPM_RCV_FUNC                 g_pCbtRcvFunc;
extern  CBTCPM_SEND_FUNC                g_pCbtSndFunc;

extern VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

/*****************************************************************************
  4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : CBTPPM_OamCbtPortDataSnd
 功能描述  : 发送CBT数据
 输入参数  : pucVirAddr:   数据虚地址
             pucPhyAddr:   数据实地址
             ulDataLen:    数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2014年5月26日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamCbtPortDataSnd(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    CBTCPM_SEND_FUNC                    pFunc;

    pFunc = CBTCPM_GetSndFunc();

    if (VOS_NULL_PTR == pFunc)
    {
        return VOS_ERR;
    }

    return pFunc(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamUsbCbtSendData
 功能描述  : 将输入的数据通过USB(APP口)发送给PC侧
 输入参数  : pucVirAddr:   数据虚地址
             pucPhyAddr:   数据实地址
             ulDataLen:    数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2011年10月8日
     作    者  : g47350
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamUsbCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    VOS_INT32                           lRet;
    ACM_WR_ASYNC_INFO                   stVcom;
    /*VOS_UINT32                          ulInSlice;
    VOS_UINT32                          ulOutSlice;
    VOS_UINT32                          ulWriteSlice;*/

    if ((VOS_NULL_PTR == pucVirAddr) || (VOS_NULL_PTR == pucPhyAddr))
    {
        /* 打印错误 */
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtSendData: Vir or Phy Addr is Null \n");
        /*lint +e534*/

        return CPM_SEND_PARA_ERR;
    }

    stVcom.pVirAddr = (VOS_CHAR*)pucVirAddr;
    stVcom.pPhyAddr = (VOS_CHAR*)pucPhyAddr;
    stVcom.u32Size  = ulDataLen;
    stVcom.pDrvPriv = VOS_NULL_PTR;

    /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteNum1++;

    ulInSlice = OM_GetSlice();*/

    lRet = mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_WRITE_ASYNC, &stVcom);

    /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteNum2++;

    ulOutSlice = OM_GetSlice();

    if(ulInSlice > ulOutSlice)
    {
        ulWriteSlice = ulInSlice - ulOutSlice;
    }
    else
    {
        ulWriteSlice = ulOutSlice - ulInSlice;
    }*/

    /*if(ulWriteSlice > g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime)
    {
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = ulWriteSlice;
    }*/


    if (MDRV_OK == lRet)     /*当前发送成功*/
    {
        if (VOS_OK != VOS_SmP(g_ulCbtUsbPseudoSyncSemId, 0))
        {
            /*lint -e534*/
            LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
            /*lint +e534*/
            return VOS_ERR;
        }

        return VOS_OK;
    }
    else if (MDRV_OK > lRet)    /*临时错误*/
    {
        /*打印信息，调用UDI接口的错误信息*/
        /*lint -e534*/
        LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/


        /*        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrNum++;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrLen    += ulDataLen;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrValue  = (VOS_UINT32)lRet;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrTime   = OM_GetSlice();*/

        return VOS_ERR; /*对于临时错误，需要返回NULL丢弃数据*/
    }
    else    /*其他错误需要复位单板*/
    {
        /*打印信息，调用UDI接口*/
        /*lint -e534*/
        LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/

        VOS_ProtectionReboot(OAM_USB_SEND_ERROR, (VOS_INT)THIS_FILE_ID, (VOS_INT)__LINE__,
                             (VOS_CHAR *)&lRet, sizeof(VOS_INT32));

        return VOS_ERR;
    }

}

/*****************************************************************************
 函 数 名  : CBTPPM_OamUsbCbtPortClose
 功能描述  : 用于关闭USB校准端口的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史  :
   1.日    期  : 2014年5月24日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtPortClose(VOS_VOID)
{
    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        return;
    }

    /*lint -e534*/
    mdrv_udi_close(g_ulCbtPortUDIHandle);
    /*lint +e534*/

    g_ulCbtPortUDIHandle = VOS_ERROR;

    /* CBT端口从USB或VCOM切换到UART时接收函数指针为空，收到USB状态变更时不做断开处理 */
    if (VOS_NULL_PTR == CBTCPM_GetRcvFunc())
    {
        return;
    }

    /*lint -e534*/
    PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_CBT);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamUsbCbtWriteDataCB
 功能描述  : USB承载的CBT端口异步发送数据的回调
 输入参数  : pucData:   发送的数据内容
             ulDataLen: 实际发送数据长度
 输出参数  : 无
 返 回 值  : 无
 修改历史  :
   1.日    期  : 2014年5月24日
     作    者  : h59254
     修改内容  : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    if (lLen < 0)
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtWriteDataCB: lLen < 0. \n");
        /*lint +e534*/
    }

    /* 伪同步接口，释放信号量 */
    /*lint -e534*/
    VOS_SmV(g_ulCbtUsbPseudoSyncSemId);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamUsbCbtStatusCB
 功能描述  : 用于ACPU上面处理USB物理端口断开后的校准断开
 输入参数  : enPortState:   端口状态
 输出参数  : 无
 返 回 值  : 无
 修改历史  :
   1.日    期  : 2014年5月24日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtStatusCB(ACM_EVT_E enPortState)
{
    /* CBT端口从USB或VCOM切换到UART时接收函数指针为空，收到USB状态变更时不做断开处理 */
    if (VOS_NULL_PTR == CBTCPM_GetRcvFunc())
    {
        return;
    }

    /* CBT端口只处理GU的端口断开 */
    /*lint -e534*/
    PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_CBT);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamUsbCbtPortOpen
 功能描述  : 用于初始化USB承载的CBT使用的端口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史  :
   1.日    期  : 2014年5月24日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtPortOpen(VOS_VOID)
{
    CBTPPM_OamCbtPortDataInit(OM_USB_CBT_PORT_HANDLE,
                              CBTPPM_OamUsbCbtReadDataCB,
                              CBTPPM_OamUsbCbtWriteDataCB,
                              CBTPPM_OamUsbCbtStatusCB);

    return;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamUsbCbtReadDataCB
 功能描述  : 用于ACPU上面底软把USB承载的CBT口数据通过ICC发送给OM模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2014年5月24日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_INT32 CBTPPM_OamUsbCbtReadDataCB(VOS_VOID)
{
    ACM_WR_ASYNC_INFO                   stInfo;
    CBTCPM_RCV_FUNC                     pFunc;

    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB: Input HANDLE  is err. \n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&stInfo, 0, sizeof(stInfo));
    /*lint +e534*/

    /* 获取USB的IO CTRL口的读缓存 */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_GET_READ_BUFFER_CB, &stInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB:Call mdrv_udi_ioctl is Failed\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e40 -e534*/
    CBT_ACPU_DEBUG_TRACE((VOS_UINT8*)stInfo.pVirAddr, stInfo.u32Size, CBT_ACPU_USB_CB);
    /*lint +e40 +e534*/

    /* 数据接收函数 */
    pFunc = CBTCPM_GetRcvFunc();

    if (VOS_NULL_PTR != pFunc)
    {
        if (VOS_OK != pFunc((VOS_UINT8 *)stInfo.pVirAddr, stInfo.u32Size))
        {
            /* 增加可维可测计数 */
        }
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_RETUR_BUFFER_CB, &stInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB:Call mdrv_udi_ioctl UDI_ACM_IOCTL_RETUR_BUFFER_CB is Failed\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamCbtPortDataInit
 功能描述  : 用于初始化CBT使用的端口设备
 输入参数  : enHandle: 端口的句柄
             pReadCB: 该端口上面的读取回调函数
             pWriteCB: 该端口上面的异步写回调函数
             pStateCB: 该端口上面的状态回调函数
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 修改历史  :
   1.日    期  : 2014年5月24日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamCbtPortDataInit(OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                        VOS_VOID                            *pReadCB,
                                        VOS_VOID                            *pWriteCB,
                                        VOS_VOID                            *pStateCB)
{
    UDI_OPEN_PARAM_S                    stUdiPara;
    ACM_READ_BUFF_INFO                  stReadBuffInfo;


    stUdiPara.devid            = UDI_ACM_OM_ID;

    stReadBuffInfo.u32BuffSize = OM_ICC_BUFFER_SIZE;
    stReadBuffInfo.u32BuffNum  = OM_DRV_MAX_IO_COUNT;

    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice = OM_GetSlice();*/


    if (VOS_ERROR != g_ulCbtPortUDIHandle)
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit: The UDI Handle is not Null !");
        /*lint +e534*/

        return;
    }

    /* 打开CBT使用的USB通道 */
    g_ulCbtPortUDIHandle = mdrv_udi_open(&stUdiPara);

    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit: Open UDI ACM failed!");
        /*lint +e534*/

        return;
    }


    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice = OM_GetSlice();*/

    /* 配置CBT使用的USB通道缓存 */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_RELLOC_READ_BUFF Failed\r\n");
        /*lint +e534*/

        return;
    }

    /* 注册OM使用的USB读数据回调函数 */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_SET_READ_CB, pReadCB))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl UDI_ACM_IOCTL_SET_READ_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_SET_WRITE_CB, pWriteCB))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_WRITE_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_SET_EVT_CB, pStateCB))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_EVT_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_WRITE_DO_COPY, VOS_NULL_PTR))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_WRITE_DO_COPY Failed\r\n");
        /*lint +e534*/

        return;
    }


    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice = OM_GetSlice();*/

    return;
}

/*****************************************************************************
 函 数 名  : GU_OamUsbCbtPortInit
 功能描述  : 用于USB 上CBT端口通道的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 修改历史  :
   1.日    期  : 2014年5月25日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamUsbCbtPortInit(VOS_VOID)
{
    /* CBT端口与PCVOICE复用，动态注册数据接收函数 */
    CBTCPM_PortRcvReg(CBTSCM_SoftDecodeDataRcv);

    /* 动态注册数据发送函数 */
    CBTCPM_PortSndReg(CBTPPM_OamUsbCbtSendData);

    /* USB承载的CBT端口，调用底软的异步接口发送数据，现在需要伪造成同步接口，申请信号量 */
    if(VOS_OK != VOS_SmCCreate("UCBT", 0, VOS_SEMA4_FIFO, &g_ulCbtUsbPseudoSyncSemId))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtPortInit: create g_ulCbtUsbPseudoSyncSemId failedd\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /* USB承载的CBT端口初始化UDI设备句柄 */
    g_ulCbtPortUDIHandle = VOS_ERROR;

    /* CBT端口通过CBT的CPM管理，不注册物理发送函数 */
    /*lint -e534*/
    mdrv_usb_reg_enablecb((USB_UDI_ENABLE_CB_T)CBTPPM_OamUsbCbtPortOpen);

    mdrv_usb_reg_disablecb((USB_UDI_DISABLE_CB_T)CBTPPM_OamUsbCbtPortClose);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamVComCbtReadData
 功能描述  : 从VCOM端口读取CBT的数据
 输入参数  :  ucDevIndex: 物理端口
              pData    : 收到数据
              ullength : 数据长度

 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2014年5月26日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_INT CBTPPM_OamVComCbtReadData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 ullength)
{
    CBTCPM_RCV_FUNC                     pFunc;

    if (ucDevIndex != APP_VCOM_DEV_INDEX_LOG)
    {
        /*lint -e534*/
        vos_printf("\r\n CBTPPM_OamVComCbtReadData:PhyPort port is error: %d\n", ucDevIndex);
        /*lint +e534*/

        return VOS_ERR;
    }

    g_stCbtVComAcpuDebugInfo.ulVCOMRcvNum++;
    g_stCbtVComAcpuDebugInfo.ulVCOMRcvLen += ullength;

    if ((VOS_NULL_PTR == pData) || (0 == ullength))
    {
        /*lint -e534*/
        vos_printf("\r\n CBTPPM_OamVComCbtReadData:Send data is NULL\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e40 -e534*/
    CBT_ACPU_DEBUG_TRACE((VOS_UINT8*)pData, ullength, CBT_ACPU_VCOM_CB);
    /*lint +e40 +e534*/

    pFunc = CBTCPM_GetRcvFunc();

    /* 数据接收函数 */
    if (VOS_NULL_PTR == pFunc)
    {
        return VOS_ERR;
    }

    if (VOS_OK != pFunc((VOS_UINT8*)pData, ullength))
    {
        g_stCbtVComAcpuDebugInfo.ulVCOMRcvErrNum++;
        g_stCbtVComAcpuDebugInfo.ulVCOMRcvErrLen += ullength;

        /*lint -e534*/
        vos_printf("\r\n Info: CBTPPM_OamVComCbtReadData:Call CBT Data Rcv Func fail\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamVComCbtSendData
 功能描述  : 从VCOM端口发送CBT数据
 输入参数  : pucVirAddr:   数据虚地址
             pucPhyAddr:   数据实地址
             ulDataLen:    数据长度
 输出参数  : 无
 返 回 值  : CPM_SEND_ERR/CPM_SEND_OK
 修改历史  :
   1.日    期  : 2014年5月26日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamVComCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    g_stCbtVComAcpuDebugInfo.ulVCOMSendNum++;
    g_stCbtVComAcpuDebugInfo.ulVCOMSendLen += ulDataLen;

    if (VOS_OK != APP_VCOM_Send(APP_VCOM_DEV_INDEX_LOG, pucVirAddr, ulDataLen))
    {
        g_stCbtVComAcpuDebugInfo.ulVCOMSendErrNum++;
        g_stCbtVComAcpuDebugInfo.ulVCOMSendErrLen += ulDataLen;

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamVComCbtPortInit
 功能描述  : 用于 Vcom CBT端口的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史  :
   1.日    期  : 2014年5月24日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamVComCbtPortInit(VOS_VOID)
{
    /* CBT端口与PCVOICE复用，动态注册数据接收函数 */
    CBTCPM_PortRcvReg(CBTSCM_SoftDecodeDataRcv);

    /* 校准走VCOM28，会有数据下发，数据的回复不走CPM，直接发送 */
    /*lint -e534*/
    APP_VCOM_RegDataCallback(APP_VCOM_DEV_INDEX_LOG, CBTPPM_OamVComCbtReadData);
    /*lint +e534*/

    CBTCPM_PortSndReg(CBTPPM_OamVComCbtSendData);

    return;
}

/*****************************************************************************
 函 数 名  : CBTPPM_OamCbtPortInit
 功能描述  : CBT端口初始化
 输入参数  : enCbtPort:CBT物理端口类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 修改历史  :
  1.日    期   : 2014年5月25日
    作    者   : h59254
    修改内容   : V8R1 OM_Optimize项目新增
*****************************************************************************/
VOS_VOID CBTPPM_OamCbtPortInit(VOS_VOID)
{
    OM_CHANNLE_PORT_CFG_STRU            stPortCfg;

    /* 初始化变量 */
    /*lint -e534*/
    VOS_MemSet(&g_stCbtVComAcpuDebugInfo, 0, sizeof(g_stCbtVComAcpuDebugInfo));
    /*lint +e534*/

    /* 读取OM的物理输出通道 */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        stPortCfg.enCbtPortNum = CPM_CBT_PORT_VCOM;
    }

    if (CPM_CBT_PORT_USB == stPortCfg.enCbtPortNum)
    {
        /* USB 承载的CBT端口的初始化 */
        /*lint -e534*/
        CBTPPM_OamUsbCbtPortInit();
        /*lint +e534*/
    }
    else if (CPM_CBT_PORT_SOCKET == stPortCfg.enCbtPortNum)
    {
        CBTPPM_SocketPortInit();
    }
    /* 默认都走VCOM做CBT */
    else
    {
        /* Vcom 口CBT通道的初始化 */
        CBTPPM_OamVComCbtPortInit();
    }

    return;
}

#if (FEATURE_HISOCKET == FEATURE_ON)

/* ****************************************************************************
  全局变量定义
**************************************************************************** */

CBTPPM_SOCKET_CTRL_INFO_STRU    g_stCbtPpmSocketCtrlInfo;

CBTPPM_SOCKET_DEBUG_INFO_STRU   g_stCbtPpmSocketDebugInfo;

/*****************************************************************************
 函 数 名  : CBTPPM_SockBindListen
 功能描述  :  socket服务器绑定监听
 输入参数  : 无
 输出参数  : 无
 返 回 值  :   无
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_SockBindListen(VOS_VOID)
{
    struct sockaddr_in  sAddr;
    VOS_INT             lAddLen;

    if((CBTPPM_SOCK_NULL != g_stCbtPpmSocketCtrlInfo.listener)||
       (CBTPPM_SOCK_NULL != g_stCbtPpmSocketCtrlInfo.socket))
    {
        return;
    }

    g_stCbtPpmSocketCtrlInfo.listener = CBT_socket(AF_INET, SOCK_STREAM, 0);

    if (VOS_OK > g_stCbtPpmSocketCtrlInfo.listener)
    {
        vos_printf("[%s][%d]:socket err !\n",__FUNCTION__,__LINE__);
        g_stCbtPpmSocketCtrlInfo.listener = CBTPPM_SOCK_NULL;
        VOS_TaskDelay(100);/*delay 100 ms*/
        return ;
    }

    /*lint -e534*/
    VOS_MemSet(&sAddr, 0, sizeof(sAddr));
    /*lint +e534*/
    sAddr.sin_family = AF_INET;

    sAddr.sin_addr.s_addr = 0;

    /* 监听的端口号 */
    sAddr.sin_port = htons(CBTPPM_SOCK_PORT_NUM);

    lAddLen = sizeof(struct sockaddr_in);

    /* 将监听Socket绑定到对应的端口上 */
    if (CBTPPM_SOCKET_ERROR == CBT_bind(g_stCbtPpmSocketCtrlInfo.listener, (struct sockaddr *)&sAddr, lAddLen))
    {
        CBT_closesocket(g_stCbtPpmSocketCtrlInfo.listener);
        g_stCbtPpmSocketCtrlInfo.listener = CBTPPM_SOCK_NULL;
        vos_printf("[%s][%d]:bind err !\n",__FUNCTION__,__LINE__);
        return ;
    }

    /* 设置服务器端监听的最大客户端数 */
    if (CBTPPM_SOCKET_ERROR == CBT_listen(g_stCbtPpmSocketCtrlInfo.listener, CBTPPM_SOCKET_NUM_MAX))
    {
        CBT_closesocket(g_stCbtPpmSocketCtrlInfo.listener);
        g_stCbtPpmSocketCtrlInfo.listener = CBTPPM_SOCK_NULL;
        vos_printf("[%s][%d]:listen err !\n",__FUNCTION__,__LINE__);
        return ;
    }
}

/*****************************************************************************
 函 数 名     : CBTPPM_SockAcceptRecv
 功能描述  :  用于处理客户端的请求，接收数据提交给上层处理。
 输入参数  : 无
 输出参数  : 无
 返 回 值  :   无
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_SockAcceptRecv(VOS_VOID)
{
    CBT_Ip_fd_set                           listen1;
    VOS_INT32                               ret;
    VOS_INT32                               len;
    struct sockaddr_in                      from;
    CBTPPM_SOCKET                           socket;
    CBTPPM_SOCKET                           maxSocket;
    CBTCPM_RCV_FUNC                         pFunc;

    if((CBTPPM_SOCK_NULL == g_stCbtPpmSocketCtrlInfo.listener)&&(CBTPPM_SOCK_NULL == g_stCbtPpmSocketCtrlInfo.socket))
    {
        vos_printf("[%s][%d]:listener && socket err !\n",__FUNCTION__,__LINE__);
        return;
    }
    
    HI_FD_ZERO(&listen1);

    HI_FD_SET(g_stCbtPpmSocketCtrlInfo.listener, &listen1);

    if(CBTPPM_SOCK_NULL != g_stCbtPpmSocketCtrlInfo.socket)
    {
        HI_FD_SET(g_stCbtPpmSocketCtrlInfo.socket, &listen1);
    }

    maxSocket = g_stCbtPpmSocketCtrlInfo.socket > g_stCbtPpmSocketCtrlInfo.listener ? g_stCbtPpmSocketCtrlInfo.socket : g_stCbtPpmSocketCtrlInfo.listener;

    ret = CBT_select((int)maxSocket + 1,&listen1, NULL, NULL, NULL);
    if(ret < 0)
    {
        vos_printf("[%s][%d]:select err !\n",__FUNCTION__,__LINE__);
        return;
    }

    if((g_stCbtPpmSocketCtrlInfo.listener != CBTPPM_SOCK_NULL) && (HI_FD_ISSET(g_stCbtPpmSocketCtrlInfo.listener, &listen1)))
    {
        len = sizeof(struct sockaddr_in);
        socket = CBT_accept(g_stCbtPpmSocketCtrlInfo.listener, (struct sockaddr *)&from, (int *)&len);
        if(socket < 0)
        {
            CBT_closesocket(g_stCbtPpmSocketCtrlInfo.listener);
            g_stCbtPpmSocketCtrlInfo.listener = CBTPPM_SOCK_NULL;
            vos_printf("[%s][%d]:accept err !\n",__FUNCTION__,__LINE__);

            return;
        }

        g_stCbtPpmSocketDebugInfo.ulListernNum1++;

        /* a new socket reconnct*/
        if(CBTPPM_SOCK_NULL != g_stCbtPpmSocketCtrlInfo.socket)
        {
            (VOS_VOID)VOS_SmP(g_stCbtPpmSocketCtrlInfo.SmClose, 0);
            CBT_closesocket(g_stCbtPpmSocketCtrlInfo.socket);
            /*lint -e534*/
            VOS_SmV(g_stCbtPpmSocketCtrlInfo.SmClose);
            /*lint +e534*/
        }

        g_stCbtPpmSocketDebugInfo.ulListernNum2++;

        (VOS_VOID)VOS_SmP(g_stCbtPpmSocketCtrlInfo.SmClose, 0);
        g_stCbtPpmSocketCtrlInfo.socket = socket;
        /*lint -e534*/
        VOS_SmV(g_stCbtPpmSocketCtrlInfo.SmClose);
        /*lint +e534*/  
    }

    if((g_stCbtPpmSocketCtrlInfo.socket != CBTPPM_SOCK_NULL) && (HI_FD_ISSET(g_stCbtPpmSocketCtrlInfo.socket, &listen1)))
    {
        ret = CBT_recv((int)g_stCbtPpmSocketCtrlInfo.socket, g_stCbtPpmSocketCtrlInfo.aucBuf, CBTPPM_SOCK_MSG_LEN, 0);
        if(ret <= 0)    /*客户端断开之后服务端会持续受到长度为0的数据包*/
        {
            (VOS_VOID)VOS_SmP(g_stCbtPpmSocketCtrlInfo.SmClose, 0);
            CBT_closesocket(g_stCbtPpmSocketCtrlInfo.socket);
            g_stCbtPpmSocketCtrlInfo.socket   = CBTPPM_SOCK_NULL;
            /*lint -e534*/
            VOS_SmV(g_stCbtPpmSocketCtrlInfo.SmClose);
            /*lint +e534*/
            
            vos_printf("[%s][%d]:rcv err !\n",__FUNCTION__,__LINE__);
            return;
        }

        g_stCbtPpmSocketDebugInfo.ulRcvData += ret;
        
        /*将接收到的数据提交给上层处理*/
        pFunc = CBTCPM_GetRcvFunc();

        if (VOS_NULL_PTR != pFunc)
        {
            if (VOS_OK != pFunc((VOS_UINT8 *)g_stCbtPpmSocketCtrlInfo.aucBuf, ret))
            {
                /* 增加可维可测计数 */
                g_stCbtPpmSocketDebugInfo.ulFailToProcess++;
            }
        }
    }
    
}

/*****************************************************************************
 函 数 名  : CBTPPM_SocketServerTask
 功能描述  :  socket服务器线程，用来处理服务器端和客户端的所有请求。
  输入参数  : 无
  输出参数  : 无
 返 回 值  :   无
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/

VOS_VOID CBTPPM_SocketServerTask(VOS_VOID)
{
    for( ; ; )
    {
        CBTPPM_SockBindListen();
        CBTPPM_SockAcceptRecv();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CBTPPM_SockIsEnable
 功能描述  :  socket功能是否支持
  输入参数  : 无
  输出参数  : 无
 返 回 值  :  VOS_TRUE/VOS_FALSE
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/

VOS_BOOL CBTPPM_SockIsEnable(VOS_VOID)
{
    OM_CHANNLE_PORT_CFG_STRU            stPortCfg;
    
    /* 读取OM的物理输出通道 */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        stPortCfg.enCbtPortNum = CPM_CBT_PORT_VCOM;
    }

    if (CPM_CBT_PORT_SOCKET != stPortCfg.enCbtPortNum)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CBTPPM_SocketTaskInit
 功能描述  :  初始化socket服务器端
 输入参数  : 无
 输出参数  : 无
 返 回 值  :   VOS_OK/VOS_ERR
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_SocketTaskInit(VOS_VOID)
{
    VOS_UINT32 ulRelVal;
    
    if((BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
        && (VOS_TRUE == CBTPPM_SockIsEnable()))
    {
        g_stCbtPpmSocketCtrlInfo.listener = CBTPPM_SOCK_NULL;
    
        g_stCbtPpmSocketCtrlInfo.socket = CBTPPM_SOCK_NULL;

        /*lint -e534*/
        VOS_MemSet(&g_stCbtPpmSocketDebugInfo, 0, sizeof(g_stCbtPpmSocketDebugInfo));
        /*lint +e534*/
        
        if(VOS_OK != VOS_SmMCreate("CBTSOCK", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &(g_stCbtPpmSocketCtrlInfo.SmClose)))
        {
            return VOS_ERR;
        }
    
        /* 接收SOCKET数据的自处理任务 */
        ulRelVal = VOS_RegisterSelfTaskPrio(ACPU_FID_CBT,
                         (VOS_TASK_ENTRY_TYPE)CBTPPM_SocketServerTask,
                         COMM_SOCK_SELFTASK_PRIO, CBT_SOCKET_TASK_STACK_SIZE);
        if ( VOS_NULL_BYTE == ulRelVal )
        {
            return VOS_ERR;
        }

    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBTPPM_SocketSendData
 功能描述  : 从socket发送CBT数据
 输入参数  : pucVirAddr 数据虚地址
                           pucPhyAddr 数据实地址
                           ulDataLen 数据长度
 输出参数  : 
 返 回 值  :   VOS_OK/VOS_ERR
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/

VOS_UINT32 CBTPPM_SocketSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    CBTPPM_SOCKET socket;
    VOS_INT       nSndNum;

    (VOS_VOID)VOS_SmP(g_stCbtPpmSocketCtrlInfo.SmClose, 0);

    socket = g_stCbtPpmSocketCtrlInfo.socket;

    if (CBTPPM_SOCK_NULL == socket)
    {
        /*lint -e534*/
        VOS_SmV(g_stCbtPpmSocketCtrlInfo.SmClose);
        /*lint +e534*/
        vos_printf("[%s][%d]:socket err !\n",__FUNCTION__,__LINE__);
        return VOS_ERR;
    }

    /* 调用send将数据通过socket发送出去，走TCP */
    nSndNum = CBT_send(socket, pucVirAddr, ulDataLen, 0);

    /*lint -e534*/
    VOS_SmV(g_stCbtPpmSocketCtrlInfo.SmClose);
    /*lint +e534*/

    if (nSndNum != ulDataLen)
    {
        g_stCbtPpmSocketDebugInfo.ulFailToSend++;
        
        return VOS_ERR;
    }

    g_stCbtPpmSocketDebugInfo.ulSndData += ulDataLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBTPPM_SocketPortInit
 功能描述  :  用于socket上CBT端口通道的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :  无
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/

VOS_VOID CBTPPM_SocketPortInit(VOS_VOID)
{
    /* CBT端口与PCVOICE复用，动态注册数据接收函数 */
    CBTCPM_PortRcvReg(CBTSCM_SoftDecodeDataRcv);

    CBTCPM_PortSndReg(CBTPPM_SocketSendData);

    return;
}

/*****************************************************************************
 函 数 名  : CBTPPM_SocketCtrlInfoShow
 功能描述  :  打印控制信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :  无
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_SocketCtrlInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("CBTPPM listen: %d.\r\n", g_stCbtPpmSocketCtrlInfo.listener);

    vos_printf("CBTPPM socket: %d.\r\n", g_stCbtPpmSocketCtrlInfo.socket);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : CBTPPM_SocketDebugInfoShow
 功能描述  :  打印调试信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :  无
 修改历史  :
   1.日    期  : 2015年12月21日
     作    者  : x51137
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_SocketDebugInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("CBTPPM ulListernNum1: %d.\r\n", g_stCbtPpmSocketDebugInfo.ulListernNum1);

    vos_printf("CBTPPM ulListernNum2: %d.\r\n", g_stCbtPpmSocketDebugInfo.ulListernNum2);

    vos_printf("CBTPPM ulRcvData: %d.\r\n", g_stCbtPpmSocketDebugInfo.ulRcvData);

    vos_printf("CBTPPM ulFailToProcess: %d.\r\n", g_stCbtPpmSocketDebugInfo.ulFailToProcess);

    vos_printf("CBTPPM ulSndData: %d.\r\n", g_stCbtPpmSocketDebugInfo.ulSndData);

    vos_printf("CBTPPM ulFailToSend: %d.\r\n", g_stCbtPpmSocketDebugInfo.ulFailToSend);
    /*lint +e534*/

    return;
}


#else

/*****************************************************************************
 函 数 名  : CBTPPM_SocketTaskInit
 功能描述  : CBT端口初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 修改历史  :
  1.日    期   : 2015年12月21日
    作    者   : x51137
    修改内容   :  Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_SocketTaskInit(VOS_VOID)
{
    return VOS_OK;
}

VOS_VOID CBTPPM_SocketPortInit(VOS_VOID)
{
    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




