/* 头文件包含 */
#include "om.h"
#include "omprivate.h"
#include "OmCommonPpm.h"

extern VOS_UINT32                      g_ulPcvStatus;
extern VOS_UINT8                       g_ucPcvComPort;
extern OM_ACPU_DEBUG_INFO              g_stAcpuDebugInfo;



extern VOS_UINT32 OM_PcvOpen(VOS_UINT32 ulPort);
extern VOS_VOID OM_PcvReleaseAll(VOS_VOID);
extern VOS_UINT32 OM_PcvSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr,VOS_UINT32 ulDataLen);




VOS_UINT32 uttest_OM_PcvOpen_case1(VOS_VOID)
{
    g_ulPcvStatus = OM_PCV_CHANNEL_BUTT;

    return OM_PcvOpen(0);
}


VOS_UINT32 uttest_OM_PcvOpen_case2(VOS_VOID)
{
    g_ulPcvStatus = OM_PCV_CHANNEL_CLOSE;

    return OM_PcvOpen(0);
}


VOS_VOID uttest_OM_PcvReleaseAll_case1(VOS_VOID)
{
    g_ucPcvComPort = 0;

    OM_PcvReleaseAll();
}


VOS_VOID uttest_OM_PcvReleaseAll_case2(VOS_VOID)
{
    g_ucPcvComPort = VOS_NULL_BYTE;

    OM_PcvReleaseAll();
}


VOS_UINT32 uttest_OM_PcvSendData_case1(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = VOS_NULL_PTR;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 0; 
        
    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}


VOS_UINT32 uttest_OM_PcvSendData_case2(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = VOS_NULL_PTR;
    ulDataLen  = 0; 
        
    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}


VOS_UINT32 uttest_OM_PcvSendData_case3(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 1; 
        
    g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = 1;

    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}


VOS_UINT32 uttest_OM_PcvSendData_case4(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 1; 
        
    g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = 15;

    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}


VOS_UINT32 uttest_OM_PcvSendData_case5(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 1; 
        
    g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = 15;

    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}


VOS_UINT32 uttest_OM_PcvSendData_case6(VOS_VOID)
{
    VOS_UINT8       *pucVirAddr;
    VOS_UINT8       *pucPhyAddr;
    VOS_UINT32      ulDataLen;

    pucVirAddr = (VOS_UINT8 *)1;
    pucPhyAddr = (VOS_UINT8 *)1;
    ulDataLen  = 1; 
        
    g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = 15;

    return OM_PcvSendData(pucVirAddr, pucPhyAddr, ulDataLen);
}


VOS_VOID uttest_OM_PcvTransmitTaskEntry_case1(VOS_VOID)
{
    OM_PcvTransmitTaskEntry();
}


VOS_VOID uttest_OM_PcvTransmitTaskEntry_case2(VOS_VOID)
{
    OM_PcvTransmitTaskEntry();
}


VOS_UINT32 uttest_OM_PcvPidInit_case1(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_FARMALLOC);
}


VOS_UINT32 uttest_OM_PcvPidInit_case2(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}


VOS_UINT32 uttest_OM_PcvPidInit_case3(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}


VOS_UINT32 uttest_OM_PcvPidInit_case4(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}