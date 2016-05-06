/* 头文件包含 */
#include "CbtCpm.h"

/*******************************************************************
*测试项:             
*被测函数功能描述:
*预期结果：           
************************* 修改记录 *************************
#  1.日    期: 
#    作    者: 
#    修改内容: 
*******************************************************************/
/*
VOS_VOID uttest_函数名_case1(VOS_VOID)
{

}
*/

VOS_VOID uttest_CBTCPM_PortRcvReg_case1(VOS_VOID)
{
	CBTCPM_RCV_FUNC pRcvFunc;

	CBTCPM_PortRcvReg(pRcvFunc);
}

VOS_VOID uttest_CBTCPM_PortSndReg_case1(VOS_VOID)
{
	CBTCPM_SEND_FUNC pSndFunc;

	CBTCPM_PortSndReg(pSndFunc);
}

VOS_VOID uttest_CBTCPM_GetRcvFunc_case1(VOS_VOID)
{
	CBTCPM_GetRcvFunc();
}

VOS_VOID uttest_CBTCPM_GetSndFunc_case1(VOS_VOID)
{
	CBTCPM_GetSndFunc();
}

VOS_UINT32 uttest_CBTCPM_NotifyChangePort_case1(VOS_VOID)
{
	AT_PHY_PORT_ENUM_UINT32 enPhyPort = CPM_IND_PORT-1;

	return CBTCPM_NotifyChangePort(enPhyPort);
}


VOS_UINT32 uttest_CBTCPM_NotifyChangePort_case2(VOS_VOID)
{
	AT_PHY_PORT_ENUM_UINT32 enPhyPort = CPM_IND_PORT;

	return CBTCPM_NotifyChangePort(enPhyPort);
}