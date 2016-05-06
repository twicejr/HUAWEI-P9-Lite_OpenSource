
#include "siappstk.h"

/*******************************************************************
*测试项:发送消息失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_STK_MenuSelection_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	SI_STK_ENVELOPE_STRU stEvent;

    stEvent.EnvelopeType = SI_STK_ENVELOPE_MENUSEL;

    if (VOS_ERR != SI_STK_MenuSelection(0,0,&stEvent))
    {
        return VOS_ERR;

    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:输入参数错误
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_STK_MenuSelection_case2(void)
{
#if ( FEATURE_MULTI_MODEM != FEATURE_ON )
	if (VOS_ERR != SI_STK_MenuSelection(0,0,0))
    {
        return VOS_ERR;

    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:输入参数错误2
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_STK_MenuSelection_case3(void)
{
#if ( FEATURE_MULTI_MODEM != FEATURE_ON )
	SI_STK_ENVELOPE_STRU stEvent;

    stEvent.EnvelopeType = SI_STK_ENVELOPE_PPDOWN;

    if (VOS_ERR != SI_STK_MenuSelection(0,0,&stEvent))
    {
        return VOS_ERR;

    }
#endif

    return VOS_OK;
}

/*******************************************************************
*测试项:发送消息成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
unsigned int uttest_SI_STK_MenuSelection_case4(void)
{
#if ( FEATURE_MULTI_MODEM != FEATURE_ON )
	SI_STK_ENVELOPE_STRU stEvent;

    stEvent.EnvelopeType = SI_STK_ENVELOPE_MENUSEL;

    if (VOS_OK != SI_STK_MenuSelection(0,0,&stEvent))
    {
        return VOS_ERR;

    }
#endif

    return VOS_OK;
}


/*******************************************************************
测试用例编号      : Test_SI_STK_SetUpCallConfirm_001
测试用例标题      : 用户输入的操作类型不正确
预期结果          : 函数返回VOS_ERR
修改历史          :
1.日   期  : 2012-09-24
  作   者  : h59254
  修改内容 : STK项目开发
*******************************************************************/
unsigned int uttest_SI_STK_SetUpCallConfirm_case1(void)
{
	// 变量声明
	VOS_UINT32                          ulAction;
	MN_CLIENT_ID_T						ClientId;
	VOS_UINT32                          ulRet;

	ulAction							=	SI_STK_SETUPCALL_BUTT;
	ClientId							=	0;

	// 调用被测函数
	ulRet = SI_STK_SetUpCallConfirm(ClientId, ulAction);

	// 执行检查
    if (VOS_ERR != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*******************************************************************
测试用例编号      : Test_SI_STK_SetUpCallConfirm_002
测试用例标题      : 消息发送成功
预期结果          : 函数返回VOS_OK
修改历史          :
1.日   期  : 2012-09-24
  作   者  : h59254
  修改内容 : STK项目开发
*******************************************************************/
unsigned int uttest_SI_STK_SetUpCallConfirm_case2(void)
{
	// 变量声明
	VOS_UINT32                          ulAction;
	MN_CLIENT_ID_T						ClientId;
	VOS_UINT32                          ulRet;

	ulAction							=	SI_STK_SETUPCALL_ALLOW;
	ClientId							=	0;

	// 调用被测函数
	ulRet = SI_STK_SetUpCallConfirm(ClientId, ulAction);

	// 执行检查
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


/*******************************************************************
测试用例编号      :
测试用例标题      :
预期结果          : 函数返回
修改历史          :
1.日   期  : 2012-09-24
  作   者  :
  修改内容 :
*******************************************************************/
unsigned int uttest_SI_STK_SendReqMsg_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];

	if (VOS_ERR != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case2(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];

	if (VOS_ERR != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case3(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];

	if (VOS_ERR != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case4(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];
	VOS_UINT8 aucMsg;
	MODEM_ID_ENUM_UINT16    enModemID = MODEM_ID_1;

	if (VOS_OK != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case5(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	VOS_UINT8 aucData[100];
	VOS_UINT8 aucMsg;

	if (VOS_OK != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_QuerySTKCommand_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	if (TAF_FAILURE != SI_STK_QuerySTKCommand(0,0))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_TerminalResponse_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	SI_STK_TERMINAL_RSP_STRU  stTRStru = {0};

	if (TAF_FAILURE != SI_STK_TerminalResponse(0,0, &stTRStru))
	{
        return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STKDualIMSIChangeReq_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	if (TAF_FAILURE != SI_STKDualIMSIChangeReq(0,0))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STKIsDualImsiSupport_case1(void)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
	if (TAF_FAILURE != SI_STKIsDualImsiSupport())
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}

unsigned int uttest_SI_STK_SendReqMsg_case6(void)
{
#if ( FEATURE_MULTI_MODEM != FEATURE_ON )
	VOS_UINT8 aucData[100];
	VOS_UINT8 aucMsg;

	if (VOS_OK != SI_STK_SendReqMsg(0,0,0,0,sizeof(aucData), aucData))
	{
	    return VOS_ERR;
	}
#endif

    return VOS_OK;
}
