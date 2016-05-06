#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include <stdio.h>
#include <stdlib.h>

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
extern "C"
{
#endif
    extern unsigned int uttest_SI_STK_MenuSelection_case1(void);
    extern unsigned int uttest_SI_STK_MenuSelection_case2(void);
    extern unsigned int uttest_SI_STK_MenuSelection_case3(void);
    extern unsigned int uttest_SI_STK_MenuSelection_case4(void);
    extern unsigned int uttest_SI_STK_SetUpCallConfirm_case1(void);
    extern unsigned int uttest_SI_STK_SetUpCallConfirm_case2(void);
    extern unsigned int uttest_SI_STK_SendReqMsg_case1(void);
    extern unsigned int uttest_SI_STK_SendReqMsg_case2(void);
    extern unsigned int uttest_SI_STK_SendReqMsg_case3(void);
    extern unsigned int uttest_SI_STK_SendReqMsg_case4(void);
    extern unsigned int uttest_SI_STK_SendReqMsg_case5(void);
    extern unsigned int uttest_SI_STK_QuerySTKCommand_case1(void);
    extern unsigned int uttest_SI_STK_TerminalResponse_case1(void);
    extern unsigned int uttest_SI_STKDualIMSIChangeReq_case1(void);
    extern unsigned int uttest_SI_STKIsDualImsiSupport_case1(void);
    extern unsigned int uttest_SI_STK_SendReqMsg_case6(void);

    extern unsigned int SI_STK_SendReqMsg(unsigned short ClientId, unsigned char OpId, unsigned int MsgName,
                                    unsigned int CmdType, unsigned int DataLen, unsigned char *pData);
    extern unsigned int AT_GetModemIdFromClient(unsigned short usClientId, unsigned short *pModemId);
    extern void * V_AllocMsg(unsigned int Pid, unsigned int ulLength, unsigned int ulFileID, signed int usLineNo);
    extern unsigned int V_SendMsg(unsigned int Pid, void **ppMsg, unsigned int ulFileID, signed int lLineNo);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif

/*******************************************************************
*测试项:发送消息失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_STK_MenuSelection1, UT)
{
    MOCKER(SI_STK_SendReqMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_STK_MenuSelection_case1());

    GlobalMockObject::reset();
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
TEST(SI_STK_MenuSelection2, UT)
{
	EXPECT_EQ(VOS_OK, uttest_SI_STK_MenuSelection_case2());
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
TEST(SI_STK_MenuSelection3, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_STK_MenuSelection_case3());
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
TEST(SI_STK_MenuSelection4, UT)
{
    MOCKER(SI_STK_SendReqMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_STK_MenuSelection_case4());

    GlobalMockObject::reset();
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
TEST(Test_SI_STK_SetUpCallConfirm1, UT)
{
	// 执行检查
    EXPECT_EQ(VOS_OK, uttest_SI_STK_SetUpCallConfirm_case1());
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
TEST(Test_SI_STK_SetUpCallConfirm2, UT)
{
    char buf[1024];

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&buf[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

	// 执行检查
    EXPECT_EQ(VOS_OK, uttest_SI_STK_SetUpCallConfirm_case2());

    GlobalMockObject::reset();
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
TEST(SI_STK_SendReqMsg1, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_STK_SendReqMsg_case1());

	GlobalMockObject::reset();
}

TEST(SI_STK_SendReqMsg2, AllocError)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)0));

	EXPECT_EQ(VOS_OK, uttest_SI_STK_SendReqMsg_case2());

	GlobalMockObject::reset();
}

TEST(SI_STK_SendReqMsg3, SendError)
{
	unsigned char aucMsg[200];

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)aucMsg));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_STK_SendReqMsg_case3());

	GlobalMockObject::reset();
}


TEST(SI_STK_SendReqMsg4, MODEM1)
{
    unsigned char  aucMsg[200];
	unsigned short enModemID = 1;

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.with(any(), outBoundP(&enModemID))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)aucMsg));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_SI_STK_SendReqMsg_case4());

	GlobalMockObject::reset();
}

TEST(SI_STK_SendReqMsg5, MODEM0)
{
    unsigned char  aucMsg[200];
	unsigned short enModemID = 0;

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.with(any(), outBoundP(&enModemID))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)aucMsg));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_SI_STK_SendReqMsg_case5());

	GlobalMockObject::reset();
}

TEST(SI_STK_QuerySTKCommand, Fail)
{
	EXPECT_EQ(VOS_OK, uttest_SI_STK_QuerySTKCommand_case1());
}

TEST(SI_STK_TerminalResponse, Fail)
{
	EXPECT_EQ(VOS_OK, uttest_SI_STK_TerminalResponse_case1());
}

TEST(SI_STKDualIMSIChangeReq, Fail)
{
	EXPECT_EQ(VOS_OK, uttest_SI_STKDualIMSIChangeReq_case1());
}

TEST(SI_STKIsDualImsiSupport, Fail)
{
	EXPECT_EQ(VOS_OK, uttest_SI_STKIsDualImsiSupport_case1());
}

TEST(SI_STK_SendReqMsg6, OK)
{
	MOCKER(AT_GetModemIdFromClient)
		.expects(once());

	EXPECT_EQ(VOS_OK, uttest_SI_STK_SendReqMsg_case6());

	GlobalMockObject::reset();
}
