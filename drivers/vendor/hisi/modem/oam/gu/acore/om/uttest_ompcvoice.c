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



/*******************************************************************
*测试项: OM_PcvOpen            
*被测函数功能描述:g_ulPcvStatus状态不为关闭
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvOpen_case1(VOS_VOID)
{
    g_ulPcvStatus = OM_PCV_CHANNEL_BUTT;

    return OM_PcvOpen(0);
}

/*******************************************************************
*测试项: OM_PcvOpen            
*被测函数功能描述:g_ulPcvStatus状态为关闭
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvOpen_case2(VOS_VOID)
{
    g_ulPcvStatus = OM_PCV_CHANNEL_CLOSE;

    return OM_PcvOpen(0);
}

/*******************************************************************
*测试项: OM_PcvReleaseAll            
*被测函数功能描述:g_ucPcvComPort不为VOS_NULL_BYTE
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_OM_PcvReleaseAll_case1(VOS_VOID)
{
    g_ucPcvComPort = 0;

    OM_PcvReleaseAll();
}

/*******************************************************************
*测试项: OM_PcvReleaseAll            
*被测函数功能描述:g_ucPcvComPort为VOS_NULL_BYTE
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_OM_PcvReleaseAll_case2(VOS_VOID)
{
    g_ucPcvComPort = VOS_NULL_BYTE;

    OM_PcvReleaseAll();
}

/*******************************************************************
*测试项: OM_PcvSendData            
*被测函数功能描述:pucVirAddr为空指针
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项: OM_PcvSendData            
*被测函数功能描述:pucPhyAddr为空指针
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项: OM_PcvSendData            
*被测函数功能描述:发送成功，但获取信号量失败
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项: OM_PcvSendData            
*被测函数功能描述:发送成功，获取信号量成功
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项: OM_PcvSendData            
*被测函数功能描述:发送失败，错误码为BSP_ERROR
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项: OM_PcvSendData            
*被测函数功能描述:发送失败，错误码为其他错误
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项: OM_PcvTransmitTaskEntry            
*被测函数功能描述:发送失败，错误码为其他错误
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_OM_PcvTransmitTaskEntry_case1(VOS_VOID)
{
    OM_PcvTransmitTaskEntry();
}

/*******************************************************************
*测试项: OM_PcvTransmitTaskEntry            
*被测函数功能描述:申请uncache内存失败
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_OM_PcvTransmitTaskEntry_case2(VOS_VOID)
{
    OM_PcvTransmitTaskEntry();
}

/*******************************************************************
*测试项: OM_PcvPidInit            
*被测函数功能描述:phase不为VOS_IP_LOAD_CONFIG
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvPidInit_case1(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_FARMALLOC);
}

/*******************************************************************
*测试项: OM_PcvPidInit            
*被测函数功能描述:申请g_stPcvOmToDspAddr uncache内存失败
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvPidInit_case2(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}

/*******************************************************************
*测试项: OM_PcvPidInit            
*被测函数功能描述:申请g_stPcvDspToOmAddr uncache内存失败
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvPidInit_case3(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}

/*******************************************************************
*测试项: OM_PcvPidInit            
*被测函数功能描述:PID初始化成功
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_OM_PcvPidInit_case4(VOS_VOID)
{
    return OM_PcvPidInit(VOS_IP_LOAD_CONFIG);
}