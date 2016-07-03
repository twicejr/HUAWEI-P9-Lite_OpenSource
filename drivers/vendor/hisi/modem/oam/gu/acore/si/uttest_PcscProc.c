
#include "PcscProc.h"

extern VOS_UINT32 PCSC_AcpuCmdReq(VOS_UINT32 ulCmdType, VOS_UINT8 *pucAPDU, VOS_UINT32 ulAPDULen);
extern USIMM_CARD_SERVIC_ENUM_UINT32 g_enAcpuCardStatus;


VOS_UINT32 uttest_PCSC_AcpuCmdReq_case1(VOS_VOID)
{
    if (VOS_ERR == PCSC_AcpuCmdReq(0,0,0))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}


VOS_UINT32 uttest_PCSC_AcpuCmdReq_case2(VOS_VOID)
{
	VOS_UINT8                           aucTemp[20];

	aucTemp[4] = 5;

	if (VOS_ERR == PCSC_AcpuCmdReq(0,aucTemp,5))
	{
	    return VOS_OK;
	}

	return VOS_ERR;
}

VOS_UINT32 uttest_PCSC_AcpuCmdReq_case3(VOS_VOID)
{
	VOS_UINT8                           aucTemp[20];

	aucTemp[4] = 10;

    if (VOS_ERR == PCSC_AcpuCmdReq(0,aucTemp,20))
	{
	    return VOS_OK;
	}

	return VOS_ERR;
}


VOS_UINT32 uttest_PCSC_AcpuCmdReq_case4(VOS_VOID)
{
	VOS_UINT8                           aucTemp[20];

	aucTemp[4] = 15;

    if (VOS_OK == PCSC_AcpuCmdReq(0,aucTemp,20))
	{
	    return VOS_OK;
	}

	return VOS_ERR;
}


VOS_UINT32 uttest_PCSC_AcpuGetCardStatus_case1(VOS_VOID)
{
	g_enAcpuCardStatus = USIMM_CARD_SERVIC_ABSENT;

    if (VOS_ERROR == PCSC_AcpuGetCardStatus())
	{
	    return VOS_OK;
	}

	return VOS_ERR;
}


VOS_UINT32 uttest_PCSC_AcpuGetCardStatus_case2(VOS_VOID)
{
	g_enAcpuCardStatus = USIMM_CARD_SERVIC_AVAILABLE;

    if (VOS_OK == PCSC_AcpuGetCardStatus())
	{
	    return VOS_OK;
	}

	return VOS_ERR;
}



VOS_VOID uttest_PCSC_AcpuMsgProc_case1(VOS_VOID)
{
	SI_PIH_PCSC_CNF_STRU stMsg;

	stMsg.ulMsgName = SI_PIH_PCSC_DATA_CNF;

	PCSC_AcpuMsgProc((MsgBlock*)&stMsg);
}



VOS_VOID uttest_PCSC_AcpuMsgProc_case3(VOS_VOID)
{
	SI_PIH_PCSC_CNF_STRU stMsg;

	stMsg.ulMsgName = SI_PIH_NULL_REQ;

	PCSC_AcpuMsgProc((MsgBlock*)&stMsg);
}
