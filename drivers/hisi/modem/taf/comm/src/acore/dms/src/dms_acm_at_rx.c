

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "msp_errno.h"
#include <dms.h>
#include "dms_core.h"
#include "vos.h"
#include "mdrv.h"


#ifdef __cplusplus
    #if __cplusplus
    extern "C" {
    #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

/*lint -e767 -e960*/
#define THIS_FILE_ID                    PS_FILE_ID_DMS_ACM_AT_RX_C
/*lint +e767 +e960*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

pComRecv                                pfnAcmReadData = VOS_NULL_PTR;


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : Dms_AtReadData
 功能描述  : AT读数据总入口
 输入参数  : enPhyBear: 端口号
              pDataBuf: 数据指针
              ulLen:数据长度
 输出参数  :
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_INVALID_PARAMETER
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2012年8月27日
    作    者   : heliping
    修改内容   : Creat Function

  2.日    期   : 2015年5月22日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 Dms_AtReadData(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 *pDataBuf, VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = 0;

    if ((VOS_NULL == pfnAcmReadData) || (VOS_NULL == pDataBuf))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if ( (DMS_PHY_BEAR_USB_PCUI != enPhyBear)
      && (DMS_PHY_BEAR_USB_CTRL != enPhyBear)
      && (DMS_PHY_BEAR_USB_PCUI2 != enPhyBear))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    DMS_LOG_INFO("Dms_AtReadData: PortNo = %d, len = %d, buf = %s\n", enPhyBear, ulLen, pDataBuf);

    ulRet = (VOS_UINT32)pfnAcmReadData((VOS_UINT8)enPhyBear, pDataBuf, (VOS_UINT16)ulLen);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : DMS_ACMRecvFuncReg
 功能描述  : AT数据接收函数注册接口
 输入参数  : pCallback: 回调函数指针

 输出参数  :
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_INVALID_PARAMETER
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
VOS_INT32 DMS_ACMRecvFuncReg(pComRecv pCallback)
{
    DMS_MAIN_INFO * pstMainInfo = DMS_GetMainInfo();

    if (VOS_NULL == pCallback)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    pstMainInfo->pfnRdDataCallback = Dms_AtReadData;
    pfnAcmReadData = pCallback;

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 函 数 名  : DMS_UsbPortOpen
 功能描述  : 打开USB端口
 输入参数  : enPhyBear  --- 物理端口号
             enDeviceId --- 设备号
             pReadCB    --- 读取回调
             pWriteCB   --- 写入回调
             pStateCB   --- 事件回调
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_UsbPortOpen(
    DMS_PHY_BEAR_ENUM                   enPhyBear,
    UDI_DEVICE_ID_E                     enDeviceId,
    VOS_VOID                           *pReadCB,
    VOS_VOID                           *pWriteCB,
    VOS_VOID                           *pStateCB
)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;
    UDI_OPEN_PARAM_S                    stOpenParam;
    ACM_READ_BUFF_INFO                  stReadBuffInfo;
    UDI_HANDLE                          lHandle = UDI_INVALID_HANDLE;

    DMS_LOG_INFO("DMS_UsbPortOpen[%d]: Open Enter.\n", enPhyBear);

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    if (UDI_INVALID_HANDLE != pstPhyBearProp->lPortHandle)
    {
        DMS_LOG_WARNING("DMS_UsbPortOpen[%d]: Already open.\n", enPhyBear);
        return ERR_MSP_SUCCESS;
    }

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_BEGIN + (VOS_UINT32)enPhyBear),\
                      0, 0, 0);

    stOpenParam.devid = enDeviceId;

    stReadBuffInfo.u32BuffSize = DMS_UL_DATA_BUFF_SIZE;
    stReadBuffInfo.u32BuffNum  = DMS_UL_DATA_BUFF_NUM;

    lHandle = mdrv_udi_open(&stOpenParam);
    if (UDI_INVALID_HANDLE != lHandle)
    {
        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_RELLOC_READ_BUFF fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                              (VOS_UINT32)lHandle, 0, 0);
        }

        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_SET_READ_CB, pReadCB))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_SET_READ_CB fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                            (VOS_UINT32)lHandle, 0, 2);
        }

        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_SET_WRITE_CB, pWriteCB))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_SET_WRITE_CB fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                            (VOS_UINT32)lHandle, 0, 3);
        }

        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_WRITE_DO_COPY, (void *)0))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_WRITE_DO_COPY fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                            (VOS_UINT32)lHandle, 0, 4);
        }

        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_SET_EVT_CB, pStateCB))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_SET_EVT_CB fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                            (VOS_UINT32)lHandle, 0, 5);
        }

        DMS_LOG_INFO("DMS_UsbPortOpen[%d]: Open success.\n", enPhyBear);
        pstPhyBearProp->lPortHandle = lHandle;
        return ERR_MSP_SUCCESS;
    }

    DMS_LOG_INFO("DMS_UsbPortOpen[%d]: Open fail.\n", enPhyBear);
    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                    (VOS_UINT32)lHandle, 0, 6);
    return ERR_MSP_FAILURE;
}

/*****************************************************************************
 函 数 名  : DMS_UsbPortClose
 功能描述  : 关闭USB端口
 输入参数  : enPhyBear --- 物理端口号
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_UsbPortClose(DMS_PHY_BEAR_ENUM enPhyBear)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;
    VOS_INT32                           lRet = ERR_MSP_SUCCESS;

    DMS_LOG_INFO("DMS_UsbPortClose[%d]: Enter.\n", enPhyBear);

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    if (UDI_INVALID_HANDLE == pstPhyBearProp->lPortHandle)
    {
        DMS_LOG_WARNING("DMS_UsbPortClose[%d]: Already close.\n", enPhyBear);
        return ERR_MSP_SUCCESS;
    }

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_CLOSE_BEGIN + (VOS_UINT32)enPhyBear),\
                    0, 0, 0);

    lRet = mdrv_udi_close(pstPhyBearProp->lPortHandle);
    if (lRet == ERR_MSP_SUCCESS)
    {
        DMS_LOG_INFO("DMS_UsbPortClose[%d]: Close success.\n", enPhyBear);
        pstPhyBearProp->lPortHandle = UDI_INVALID_HANDLE;
        pstPhyBearProp->ucChanStat   = ACM_EVT_DEV_SUSPEND;
        return (VOS_UINT32)lRet;
    }

    DMS_LOG_INFO("DMS_UsbPortClose[%d]: Close fail.\n", enPhyBear);
    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_CLOSE_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                    (VOS_UINT32)lRet, 0, 0);
    return ERR_MSP_FAILURE;
}

/*****************************************************************************
 函 数 名  : DMS_UsbPortReadCB
 功能描述  : USB端口数据读回调
 输入参数  : enPhyBear --- 物理端口号
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2014年5月30日
    作    者   : j00174725
    修改内容   : TQE
*****************************************************************************/
VOS_VOID DMS_UsbPortReadCB(DMS_PHY_BEAR_ENUM enPhyBear)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;
    DMS_READ_DATA_PFN                   pRdDataFun = NULL;
    ACM_WR_ASYNC_INFO                   stAcmInfo;
    UDI_HANDLE                          lHandle = UDI_INVALID_HANDLE;

    DMS_LOG_INFO("DMS_UsbPortReadCB[%d]: Read begin.\n", enPhyBear);


    VOS_MemSet(&stAcmInfo, 0x0, sizeof(stAcmInfo));

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    lHandle = pstPhyBearProp->lPortHandle;
    if (UDI_INVALID_HANDLE == lHandle)
    {
        DMS_LOG_ERROR("DMS_UsbPortReadCB[%d]: UDI_INVALID_HANDLE.\n", enPhyBear);
        return;
    }

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_RD_CB_BEGIN + (VOS_UINT32)enPhyBear),\
                    0, 0, 0);

    if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_GET_RD_BUFF, &stAcmInfo))
    {
        DMS_LOG_ERROR("DMS_UsbPortReadCB[%d]: ACM_IOCTL_GET_RD_BUFF fail.\n", enPhyBear);
        DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_RD_CB_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                        (VOS_UINT32)lHandle, 0, 0);
        return;
    }

    pstPhyBearProp->ucChanStat = ACM_EVT_DEV_READY;

    pRdDataFun = DMS_GetDataReadFun();
    if (NULL != pRdDataFun)
    {
        (VOS_VOID)pRdDataFun(enPhyBear, (VOS_UINT8 *)stAcmInfo.pVirAddr, stAcmInfo.u32Size);
    }

    if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_RETURN_BUFF, &stAcmInfo))
    {
        DMS_LOG_INFO("DMS_UsbPortReadCB[%d]: ACM_IOCTL_RETURN_BUFF fail.\n", enPhyBear);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_UsbPortWrtCB
 功能描述  : USB端口数据写完成回调
 输入参数  : enPhyBear --- 物理端口号
             pcVirAddr --- 写指针(虚拟地址)
             pcPhyAddr --- 写指针(物理地址)
             lDoneSize --- 写入长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_UsbPortWrtCB(
    DMS_PHY_BEAR_ENUM                   enPhyBear,
    VOS_CHAR                           *pcVirAddr,
    VOS_CHAR                           *pcPhyAddr,
    VOS_INT                             lDoneSize
)
{
    VOS_UINT_PTR                        ptrDebugVirAddr;
    VOS_UINT_PTR                        ptrDebugPhyAddr;

    ptrDebugVirAddr = (VOS_UINT_PTR)pcVirAddr;
    ptrDebugPhyAddr = (VOS_UINT_PTR)pcPhyAddr;

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_WRT_CB_BEGIN + (VOS_UINT32)enPhyBear),\
                    (VOS_UINT32)(ptrDebugVirAddr & (~0U)), (VOS_UINT32)(ptrDebugPhyAddr & (~0U)), (VOS_UINT32)lDoneSize);

    if (lDoneSize < 0)
    {
        DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_WRT_CB_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                        (VOS_UINT32)(ptrDebugVirAddr & (~0U)), (VOS_UINT32)(ptrDebugPhyAddr & (~0U)), (VOS_UINT32)lDoneSize);
    }

    if (VOS_TRUE == Dms_IsStaticBuf((VOS_UINT8 *)pcVirAddr))
    {
        Dms_FreeStaticBuf((VOS_UINT8 *)pcVirAddr);
    }
    else
    {
        if (NULL != pcVirAddr)
        {
#if (VOS_LINUX== VOS_OS_VER)
            kfree(pcVirAddr);
#endif
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_UsbPortEvtCB
 功能描述  : USB端口事件处理回调函数
 输入参数  : enPhyBear --- 物理端口号
             enEvt     --- ACM设备事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_UsbPortEvtCB(DMS_PHY_BEAR_ENUM enPhyBear, ACM_EVT_E enEvt)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_EVT_BEGIN + (VOS_UINT32)enPhyBear),\
                    enEvt, 0, 0);

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    if (ACM_EVT_DEV_READY == enEvt)
    {
        pstPhyBearProp->ucChanStat  = ACM_EVT_DEV_READY;
    }
    else
    {
        pstPhyBearProp->ucChanStat  = ACM_EVT_DEV_SUSPEND;
        pstPhyBearProp->enLogicChan = DMS_CHANNEL_AT;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcuiOpen
 功能描述  : 打开PCUI端口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_VcomPcuiOpen(VOS_VOID)
{
    return DMS_UsbPortOpen(DMS_PHY_BEAR_USB_PCUI,
                           UDI_ACM_AT_ID,
                           DMS_VcomPcuiReadCB,
                           DMS_VcomPcuiWrtCB,
                           DMS_VcomPcuiEvtCB);
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcuiClose
 功能描述  : 关闭PCUI端口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_VcomPcuiClose(VOS_VOID)
{
    return DMS_UsbPortClose(DMS_PHY_BEAR_USB_PCUI);
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcuiReadCB
 功能描述  : PCUI端口读取回调
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_VcomPcuiReadCB(VOS_VOID)
{
    DMS_UsbPortReadCB(DMS_PHY_BEAR_USB_PCUI);
    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcuiWrtCB
 功能描述  : PCUI口写完成回调
 输入参数  : pcVirAddr --- 写指针(虚拟地址)
             pcPhyAddr --- 写指针(物理地址)
             lDoneSize --- 写入长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_VcomPcuiWrtCB(
    VOS_CHAR                           *pcVirAddr,
    VOS_CHAR                           *pcPhyAddr,
    VOS_INT                             lDoneSize
)
{
    DMS_UsbPortWrtCB(DMS_PHY_BEAR_USB_PCUI, pcVirAddr, pcPhyAddr, lDoneSize);
    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcuiEvtCB
 功能描述  : PCUI端口事件处理回调
 输入参数  : enEvt --- ACM设备事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_VcomPcuiEvtCB(ACM_EVT_E enEvt)
{
    DMS_UsbPortEvtCB(DMS_PHY_BEAR_USB_PCUI, enEvt);
    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomCtrlOpen
 功能描述  : 打开CTRL端口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_VcomCtrlOpen(VOS_VOID)
{
    return DMS_UsbPortOpen(DMS_PHY_BEAR_USB_CTRL,
                           UDI_ACM_CTRL_ID,
                           DMS_VcomCtrlReadCB,
                           DMS_VcomCtrlWrtCB,
                           DMS_VcomCtrlEvtCB);
}

/*****************************************************************************
 函 数 名  : DMS_VcomCtrlClose
 功能描述  : 关闭CTRL端口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_VcomCtrlClose(VOS_VOID)
{
    return DMS_UsbPortClose(DMS_PHY_BEAR_USB_CTRL);
}

/*****************************************************************************
 函 数 名  : DMS_VcomCtrlReadCB
 功能描述  : CTRL端口读取回调
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_VcomCtrlReadCB(VOS_VOID)
{
    DMS_UsbPortReadCB(DMS_PHY_BEAR_USB_CTRL);
    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomCtrlWrtCB
 功能描述  : CTRL口写完成回调
 输入参数  : pcVirAddr --- 写指针(虚拟地址)
             pcPhyAddr --- 写指针(物理地址)
             lDoneSize --- 写入长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_VcomCtrlWrtCB(
    VOS_CHAR                           *pcVirAddr,
    VOS_CHAR                           *pcPhyAddr,
    VOS_INT                             lDoneSize
)
{
    DMS_UsbPortWrtCB(DMS_PHY_BEAR_USB_CTRL, pcVirAddr, pcPhyAddr, lDoneSize);
    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomCtrlEvtCB
 功能描述  : CTRL端口事件处理回调
 输入参数  : enEvt --- ACM设备事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_VcomCtrlEvtCB(ACM_EVT_E enEvt)
{
    DMS_UsbPortEvtCB(DMS_PHY_BEAR_USB_CTRL, enEvt);
    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcui2Open
 功能描述  : 打开PCUI2端口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 DMS_VcomPcui2Open(VOS_VOID)
{
    return DMS_UsbPortOpen(DMS_PHY_BEAR_USB_PCUI2,
                           UDI_ACM_SKYTONE_ID,
                           DMS_VcomPcui2ReadCB,
                           DMS_VcomPcui2WrtCB,
                           DMS_VcomPcui2EvtCB);
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcui2Close
 功能描述  : 关闭PCUI2端口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 DMS_VcomPcui2Close(VOS_VOID)
{
    return DMS_UsbPortClose(DMS_PHY_BEAR_USB_PCUI2);
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcui2ReadCB
 功能描述  : PCUI2端口读取回调
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID DMS_VcomPcui2ReadCB(VOS_VOID)
{
    DMS_UsbPortReadCB(DMS_PHY_BEAR_USB_PCUI2);
    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcui2WrtCB
 功能描述  : PCUI2口写完成回调
 输入参数  : pcVirAddr --- 写指针(虚拟地址)
             pcPhyAddr --- 写指针(物理地址)
             lDoneSize --- 写入长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID DMS_VcomPcui2WrtCB(
    VOS_CHAR                           *pcVirAddr,
    VOS_CHAR                           *pcPhyAddr,
    VOS_INT                             lDoneSize
)
{
    DMS_UsbPortWrtCB(DMS_PHY_BEAR_USB_PCUI2, pcVirAddr, pcPhyAddr, lDoneSize);
    return;
}

/*****************************************************************************
 函 数 名  : DMS_VcomPcui2EvtCB
 功能描述  : PCUI2端口事件处理回调
 输入参数  : enEvt --- ACM设备事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID DMS_VcomPcui2EvtCB(ACM_EVT_E enEvt)
{
    DMS_UsbPortEvtCB(DMS_PHY_BEAR_USB_PCUI2, enEvt);
    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

