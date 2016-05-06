/* 头文件包含 */
/*
#include ""
*/
#include "SOCPInterface.h"
#include "SCMProc.h"
#include "SCMSoftDecode.h"
#include "ombufmngr.h"
#include "OmHdlcInterface.h"
#include "OmAppRl.h"

extern VOS_UINT32 CBTSCM_SoftDecodeDataRcvProc(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);
extern VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

VOS_UINT32 uttest_CBTSCM_SoftDecodeDataRcvProc_case1(VOS_VOID)
{
	VOS_UINT8 aucBuffer[1000] = {0}; 
	VOS_UINT32 ulLen = 1000;

	return CBTSCM_SoftDecodeDataRcvProc(aucBuffer, ulLen);
}

VOS_UINT32 uttest_CBTSCM_SoftDecodeDataRcvProc_case2(VOS_VOID)
{
	VOS_UINT8 aucBuffer[1000] = {0}; 
	VOS_UINT32 ulLen = 1024;

	return CBTSCM_SoftDecodeDataRcvProc(aucBuffer, ulLen);
}

VOS_UINT32 uttest_CBTSCM_SoftDecodeDataRcvProc_case3(VOS_VOID)
{
	VOS_UINT8 aucBuffer[1000] = {0}; 
	VOS_UINT32 ulLen = 1000;

	return CBTSCM_SoftDecodeDataRcvProc(aucBuffer, ulLen);
}

VOS_UINT32 uttest_CBTSCM_SoftDecodeDataRcv_case1(VOS_VOID)
{
	VOS_UINT8 aucBuffer[1000] = {0}; 
	VOS_UINT32 ulLen = 1000;

	return CBTSCM_SoftDecodeDataRcv(aucBuffer, ulLen);
}

VOS_UINT32 uttest_CBTSCM_SoftDecodeAcpuRcvData_case1(VOS_VOID)
{
	OM_HDLC_STRU                        stHdlcCtrl;
	VOS_UINT8                           aucData[10];
	VOS_UINT32                          ulLen = 3;
	VOS_UINT8                           aucTmp[10];


	stHdlcCtrl.pucDecapBuff = aucTmp;
	stHdlcCtrl.pucDecapBuff[0] = SCM_DATA_TYPE_TL;

	return CBTSCM_SoftDecodeAcpuRcvData(&stHdlcCtrl, aucData, ulLen);
}

VOS_UINT32 Stub_RcvData(SOCP_DECODER_DST_ENUM_U32 enChanlID,VOS_UINT8 *pucData, VOS_UINT32 ulSize, VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize)
{
	return VOS_OK;
}

VOS_UINT32 uttest_CBTSCM_SoftDecodeAcpuRcvData_case2(VOS_VOID)
{
	OM_HDLC_STRU                        stHdlcCtrl;
	VOS_UINT8                           aucData[10];
	VOS_UINT32                          ulLen = 3;
	VOS_UINT8                           aucTmp[10];


	stHdlcCtrl.pucDecapBuff = aucTmp;
	stHdlcCtrl.pucDecapBuff[0] = SCM_DATA_TYPE_GU;

	g_astSCMDecoderCbFunc[SOCP_DECODER_DST_CB_GU_CBT] = Stub_RcvData;

	return CBTSCM_SoftDecodeAcpuRcvData(&stHdlcCtrl, aucData, ulLen);
}

VOS_UINT32 uttest_CBTSCM_SoftDecodeHdlcInit_case1(VOS_VOID)
{
	OM_HDLC_STRU                        stHdlcCtrl;

	return CBTSCM_SoftDecodeHdlcInit(&stHdlcCtrl);
}

VOS_UINT32 uttest_CBTSCM_SoftDecodeReqRcvTaskInit_case1(VOS_VOID)
{
	return CBTSCM_SoftDecodeReqRcvTaskInit();
}
