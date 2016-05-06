
#include "om.h"
#include "ombbplog.h"

/*******************************************************************
*测试项:             A核消息处理
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2012年11月29日
#    作    者: j00174752
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_Om_AcpuBbpConfigMsgProc_case1(VOS_VOID)
{
	OM_REQ_PACKET_STRU stRspPacket;

	*(VOS_UINT16*)stRspPacket.aucCommand = (VOS_UINT16)APP_OM_BBP_DUMP_DUMP_REQ;

	Om_AcpuBbpConfigMsgProc(&stRspPacket,0);
}

VOS_VOID uttest_Om_AcpuBbpConfigMsgProc_case2(VOS_VOID)
{
	OM_REQ_PACKET_STRU stRspPacket;

	*(VOS_UINT16*)stRspPacket.aucCommand = 40;

	Om_AcpuBbpConfigMsgProc(&stRspPacket,0);
}

VOS_VOID uttest_Om_AcpuBbpConfigMsgProc_case3(VOS_VOID)
{
	OM_REQ_PACKET_STRU stRspPacket;

	*(VOS_UINT16*)stRspPacket.aucCommand = (VOS_UINT16)APP_OM_BBP_DUMP_DUMP_REQ;

	Om_AcpuBbpConfigMsgProc(&stRspPacket,0);
}

/*******************************************************************
*测试项:             导出数据选择
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2012年11月29日
#    作    者: j00174752
#    修改内容: 新建CASE
*******************************************************************/
VOS_UINT32 uttest_Om_AcpuDumpReboot_case1(VOS_VOID)
{
	APP_OM_MSG_EX_STRU stAppToOmMsg;

	BBP_DUMP_CHOOSE_STRU               *pstPcMsg;

	pstPcMsg        = (BBP_DUMP_CHOOSE_STRU*)stAppToOmMsg.aucPara;

	pstPcMsg->ulChooseRelt = BBP_DUMP_CHOOSE_YES;


	return Om_AcpuDumpReboot(&stAppToOmMsg,OM_APP_BBP_DUMP_DUMP_CNF);
}

