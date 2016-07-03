



/*****************************************************************************
  1 头文件包含
**************************************************************************** */
#include "OmCommonPpm.h"
#include "OmHsicPpm.h"
#include "cpm.h"
#include "TafOamInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_HSIC_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 全局变量定义
**************************************************************************** */
/* HSIC和OM关联状态，默认为不关联 */
OM_HSIC_PORT_STATUS_ENUM_UINT32         g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_OFF;

/*互斥信号量，用来保护OM HSIC关联 */
VOS_SEM                                 g_ulOmAcpuHsicSem;

/*****************************************************************************
  3 外部引用声明
*****************************************************************************/


/*****************************************************************************
  4 函数实现
*****************************************************************************/





OM_HSIC_PORT_STATUS_ENUM_UINT32 PPM_GetHsicPortStatus(VOS_VOID)
{
    /* 返回OM口和HSIC关联状态 */
    return g_ulOmHsicConnectStatus;
}


VOS_VOID PPM_HsicIndWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    /*当前只承载OM数据*/
    PPM_PortWriteAsyCB(OM_HSIC_IND_PORT_HANDLE, pucVirData, lLen);

    return;
}



VOS_INT32 PPM_HsicCfgReadDataCB(VOS_VOID)
{
    if (OM_HSIC_PORT_STATUS_OFF == PPM_GetHsicPortStatus())
    {
        return VOS_OK;
    }

    return PPM_ReadPortData(CPM_HSIC_CFG_PORT, g_astOMPortUDIHandle[OM_HSIC_CFG_PORT_HANDLE], OM_HSIC_CFG_PORT_HANDLE);
}


VOS_VOID PPM_HsicCfgWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    /*当前只承载OM数据*/
    PPM_PortWriteAsyCB(OM_HSIC_CFG_PORT_HANDLE, pucVirData, lLen);

    return;
}


VOS_VOID PPM_HsicCfgPortOpen(VOS_VOID)
{

    PPM_ReadPortDataInit(CPM_HSIC_CFG_PORT,
                           OM_HSIC_CFG_PORT_HANDLE,
                           PPM_HsicCfgReadDataCB,
                           PPM_HsicCfgWriteDataCB,
                           VOS_NULL_PTR);

    return;
}


VOS_VOID PPM_HsicIndPortOpen(VOS_VOID)
{
    /* HSIC IND 端口不会收数据，没有断开处理 */
    PPM_ReadPortDataInit(CPM_HSIC_IND_PORT,
                           OM_HSIC_IND_PORT_HANDLE,
                           VOS_NULL_PTR,
                           PPM_HsicIndWriteDataCB,
                           VOS_NULL_PTR);

    return;
}


VOS_VOID PPM_HsicIndPortClose(VOS_VOID)
{
    PPM_PortCloseProc(OM_HSIC_IND_PORT_HANDLE, CPM_HSIC_IND_PORT);

    return;
}


VOS_VOID PPM_HsicCfgPortClose(VOS_VOID)
{
    PPM_PortCloseProc(OM_HSIC_CFG_PORT_HANDLE, CPM_HSIC_CFG_PORT);

    return;
}


VOS_UINT32 PPM_HsicIndSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    return PPM_PortSend(OM_HSIC_IND_PORT_HANDLE, pucVirAddr, pucPhyAddr, ulDataLen);
}


VOS_UINT32 PPM_HsicCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    return PPM_PortSend(OM_HSIC_CFG_PORT_HANDLE, pucVirAddr, pucPhyAddr, ulDataLen);
}


VOS_VOID PPM_HsicIndStatusCB(ACM_EVT_E enPortState)
{
    PPM_PortStatus(OM_HSIC_IND_PORT_HANDLE, CPM_HSIC_IND_PORT, enPortState);

    return;
}


VOS_VOID PPM_HsicCfgStatusCB(ACM_EVT_E enPortState)
{
    PPM_PortStatus(OM_HSIC_CFG_PORT_HANDLE, CPM_HSIC_CFG_PORT, enPortState);

    return;
}


VOS_VOID PPM_HsicPortInit(VOS_VOID)
{
    /* 产品不支持HSIC特性，直接返回 */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return;
    }

    /* 如果HSIC通道已经枚举成功，则由协议栈执行初始化操作；否则将初始化函数注册至底软，
        由底软在HSIC枚举成功后调用以进行初始化*/
    if (VOS_TRUE == DRV_GET_HSIC_ENUM_STATUS())
    {
        PPM_HsicIndPortOpen();
        PPM_HsicCfgPortOpen();
    }
    else
    {
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)PPM_HsicIndPortOpen);
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)PPM_HsicCfgPortOpen);
    }

    DRV_HSIC_REGUDI_DISABLECB((HSIC_UDI_DISABLE_CB_T)PPM_HsicIndPortClose);
    DRV_HSIC_REGUDI_DISABLECB((HSIC_UDI_DISABLE_CB_T)PPM_HsicCfgPortClose);

    CPM_PhySendReg(CPM_HSIC_IND_PORT,  PPM_HsicIndSendData);
    CPM_PhySendReg(CPM_HSIC_CFG_PORT,  PPM_HsicCfgSendData);

    return;
}

/*****************************************************************************
 Prototype       : PPM_HsicConnectProc
 Description     : OM口和HSIC关联
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem锁网锁卡项目新增函数
 *****************************************************************************/
VOS_VOID PPM_HsicConnectProc(VOS_VOID)
{
    if (VOS_OK != VOS_SmP(g_ulOmAcpuHsicSem, 0))
    {
        return;
    }

    /* 产品不支持HSIC特性，直接初始化成功 */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        /*lint -e534*/
        VOS_SmV(g_ulOmAcpuHsicSem);
        /*lint +e534*/

        return;
    }

    /* 如果已经关联上不做关联 */
    if (OM_HSIC_PORT_STATUS_ON == g_ulOmHsicConnectStatus)
    {
        /*lint -e534*/
        VOS_SmV(g_ulOmAcpuHsicSem);
        /*lint +e534*/

        return;
    }

    /* 将全局变量设置为已关联上 */
    g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_ON;

    /*lint -e534*/
    VOS_SmV(g_ulOmAcpuHsicSem);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Prototype       : PPM_HsicDisconnectProc
 Description     : OM口和HSIC解除关联
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem锁网锁卡项目新增函数
 *****************************************************************************/
VOS_VOID PPM_HsicDisconnectProc(VOS_VOID)
{
    /* 产品不支持HSIC特性，直接初始化成功 */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return;
    }

    /* 如果已经是未关联状态不做解除关联操作 */
    if (OM_HSIC_PORT_STATUS_OFF == g_ulOmHsicConnectStatus)
    {
        return;
    }

    /* 将全局变量设置为已解除关联上 */
    g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_OFF;

    return;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




