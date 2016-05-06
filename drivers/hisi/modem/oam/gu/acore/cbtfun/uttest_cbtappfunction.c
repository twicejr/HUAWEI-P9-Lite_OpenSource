/* 头文件包含 */

#include "omnvinterface.h"
#include "CbtPpm.h"
#include "AtAppVcomInterface.h"


OM_CHANNLE_PORT_CFG_STRU            stPortCfg;

extern UDI_HANDLE                   g_astOMPortUDIHandle[OM_PORT_HANDLE_BUTT];

extern UDI_HANDLE                   g_ulCbtPortUDIHandle;
#if 0
/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_CBTPPM_OamCbtPortInit_case1(VOS_VOID)
{
	CBTPPM_OamCbtPortInit();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_CBTPPM_OamCbtPortInit_case2(VOS_VOID)
{
	stPortCfg.enCbtPortNum = CPM_CBT_PORT_USB;

	CBTPPM_OamCbtPortInit();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_CBTPPM_OamVComCbtPortInit_case1(VOS_VOID)
{
	CBTPPM_OamVComCbtPortInit();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_CBTPPM_OamVComCbtPortInit_case2(VOS_VOID)
{
	CBTPPM_OamVComCbtPortInit();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamVComCbtSendData_case1(VOS_VOID)
{
	VOS_UINT8 ucVirAddr; 
	VOS_UINT8 ucPhyAddr;
	VOS_UINT32 ulDataLen = 10;

	return CBTPPM_OamVComCbtSendData(&ucVirAddr, &ucPhyAddr, ulDataLen);
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamVComCbtReadData_case1(VOS_VOID)
{
	VOS_UINT8 ucDevIndex = APP_VCOM_DEV_INDEX_LOG+1;
	VOS_UINT8 aucData[100] = {0};
	VOS_UINT32 ullength = 10;

	return CBTPPM_OamVComCbtReadData(ucDevIndex, aucData, ullength);
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamVComCbtReadData_case2(VOS_VOID)
{
	VOS_UINT8 ucDevIndex = APP_VCOM_DEV_INDEX_LOG;
	VOS_UINT8 *pucData = VOS_NULL_PTR;
	VOS_UINT32 ullength = 10;

	return CBTPPM_OamVComCbtReadData(ucDevIndex, pucData, ullength);
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamVComCbtReadData_case3(VOS_VOID)
{
	VOS_UINT8 ucDevIndex = APP_VCOM_DEV_INDEX_LOG;
	VOS_UINT8 aucData[100] = {0};
	VOS_UINT32 ullength = 0;

	return CBTPPM_OamVComCbtReadData(ucDevIndex, aucData, ullength);
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamVComCbtReadData_case4(VOS_VOID)
{
	VOS_UINT8 ucDevIndex = APP_VCOM_DEV_INDEX_LOG;
	VOS_UINT8 aucData[100] = {0};
	VOS_UINT32 ullength = 10;

	return CBTPPM_OamVComCbtReadData(ucDevIndex, aucData, ullength);
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamVComCbtReadData_case5(VOS_VOID)
{
	VOS_UINT8 ucDevIndex = APP_VCOM_DEV_INDEX_LOG;
	VOS_UINT8 aucData[100] = {0};
	VOS_UINT32 ullength = 10;

	return CBTPPM_OamVComCbtReadData(ucDevIndex, aucData, ullength);
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamVComCbtReadData_case6(VOS_VOID)
{
	VOS_UINT8 ucDevIndex = APP_VCOM_DEV_INDEX_LOG;
	VOS_UINT8 aucData[100] = {0};
	VOS_UINT32 ullength = 10;

	return CBTPPM_OamVComCbtReadData(ucDevIndex, aucData, ullength);
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamUsbCbtPortInit_case1(VOS_VOID)
{
	return CBTPPM_OamUsbCbtPortInit();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_CBTPPM_OamUsbCbtPortInit_case2(VOS_VOID)
{
	return CBTPPM_OamUsbCbtPortInit();
}

VOS_VOID uttest_CBTPPM_OamCbtPortDataInit_case1(VOS_VOID)
{
	OM_PROT_HANDLE_ENUM_UINT32          enHandle = OM_USB_CBT_PORT_HANDLE;
	VOS_UINT32                            ReadCB;
	VOS_UINT32                            WriteCB;
	VOS_UINT32                            StateCB;

	g_ulCbtPortUDIHandle = VOS_OK;

	CBTPPM_OamCbtPortDataInit(enHandle, (VOS_VOID *)&ReadCB, (VOS_VOID *)&WriteCB, (VOS_VOID *)&StateCB);
}

VOS_VOID uttest_CBTPPM_OamCbtPortDataInit_case2(VOS_VOID)
{
	OM_PROT_HANDLE_ENUM_UINT32          enHandle = OM_USB_CBT_PORT_HANDLE;
	VOS_UINT32                            ReadCB;
	VOS_UINT32                            WriteCB;
	VOS_UINT32                            StateCB;

	g_ulCbtPortUDIHandle = VOS_ERROR;

	CBTPPM_OamCbtPortDataInit(enHandle, (VOS_VOID *)&ReadCB, (VOS_VOID *)&WriteCB, (VOS_VOID *)&StateCB);
}

VOS_UINT32 uttest_CBTPPM_OamUsbCbtReadDataCB_case1(VOS_VOID)
{
	g_ulCbtPortUDIHandle = VOS_ERROR;

	return CBTPPM_OamUsbCbtReadDataCB();
}

VOS_UINT32 uttest_CBTPPM_OamUsbCbtReadDataCB_case2(VOS_VOID)
{
	g_ulCbtPortUDIHandle = VOS_OK;

	return CBTPPM_OamUsbCbtReadDataCB();
}

VOS_VOID uttest_CBTPPM_OamUsbCbtPortOpen_case1(VOS_VOID)
{
	CBTPPM_OamUsbCbtPortOpen();
}

VOS_VOID uttest_CBTPPM_OamUsbCbtStatusCB_case1(VOS_VOID)
{
	ACM_EVT_E enPortState = 10;

	CBTPPM_OamUsbCbtStatusCB(enPortState);
}

VOS_VOID uttest_CBTPPM_OamUsbCbtWriteDataCB_case1(VOS_VOID)
{
	VOS_UINT8 aucVirData[100];
	VOS_UINT8 aucPhyData[100];
	VOS_INT lLen = -1;

    CBTPPM_OamUsbCbtWriteDataCB(&aucVirData, &aucPhyData, lLen);
}

VOS_VOID uttest_CBTPPM_OamUsbCbtPortClose_case0(VOS_VOID)
{
    g_ulCbtPortUDIHandle = VOS_ERROR;

    CBTPPM_OamUsbCbtPortClose();

    return;
}


VOS_VOID uttest_CBTPPM_OamUsbCbtPortClose_case1(VOS_VOID)
{
    g_ulCbtPortUDIHandle = 1;

    CBTPPM_OamUsbCbtPortClose();

    return;
}

VOS_UINT32 uttest_CBTPPM_OamCbtPortDataSnd_case1(VOS_VOID)
{
	VOS_UINT8 aucVirData[100];
	VOS_UINT8 aucPhyData[100];
    VOS_UINT32 ulDataLen = 10;

	return CBTPPM_OamCbtPortDataSnd(aucVirData, aucPhyData, ulDataLen);
}


VOS_UINT32 uttest_CBTPPM_OamUsbCbtSendData_case1(VOS_VOID)
{
	VOS_UINT8 *pucVirAddr=VOS_NULL_PTR;
	VOS_UINT8 aucPhyData[100];
	VOS_UINT32 ulDataLen = 10;

	return CBTPPM_OamUsbCbtSendData(pucVirAddr, aucPhyData, ulDataLen);
}

VOS_UINT32 uttest_CBTPPM_OamUsbCbtSendData_case2(VOS_VOID)
{
	VOS_UINT8 aucVirData[100];
	VOS_UINT8 *pucPhyData = VOS_NULL_PTR;
	VOS_UINT32 ulDataLen = 10;

	return CBTPPM_OamUsbCbtSendData(aucVirData, pucPhyData, ulDataLen);
}

VOS_UINT32 uttest_CBTPPM_OamUsbCbtSendData_case3(VOS_VOID)
{
	VOS_UINT8 aucVirData[100];
	VOS_UINT8 aucPhyData[100];
	VOS_UINT32 ulDataLen = 10;

	return CBTPPM_OamUsbCbtSendData(aucVirData, aucPhyData, ulDataLen);
}
VOS_VOID *uttest_GetPortTypePtr(VOS_VOID)
{
	return &stPortCfg;
}

VOS_UINT32 func1(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
	return VOS_ERR;
}

VOS_UINT32 func2(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
	return VOS_OK;
}

VOS_VOID *uttest_CBTCPM_GetRcvFuncPtr1(VOS_VOID)
{
	return (VOS_VOID *)&func1;
}

VOS_VOID *uttest_CBTCPM_GetRcvFuncPtr2(VOS_VOID)
{
	return (VOS_VOID *)&func2;
}
#endif