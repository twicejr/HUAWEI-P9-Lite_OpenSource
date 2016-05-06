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

   extern unsigned int CBTCPM_NotifyChangePort(unsigned int enPhyPort);
   extern void CBTCPM_PortSndReg(void * pSndFunc);
   extern void CBTCPM_PortRcvReg(void * pRcvFunc);
   extern void uttest_CBTCPM_PortRcvReg_case1(void);
   extern void uttest_CBTCPM_PortSndReg_case1(void);
   extern void uttest_CBTCPM_GetRcvFunc_case1(void);
   extern void uttest_CBTCPM_GetSndFunc_case1(void);
   extern unsigned int uttest_CBTCPM_NotifyChangePort_case1(void);
   extern unsigned int uttest_CBTCPM_NotifyChangePort_case2(void);
   extern void * AT_QuerySndFunc(unsigned int ulPhyPort);
   extern void AT_RcvFuncReg(unsigned int ulPhyPort, void * pRcvFunc);

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
*测试项:给CBT通道注册接收函数
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(CBTCPM_PortRcvReg1, UT)
{
	uttest_CBTCPM_PortRcvReg_case1();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:给CBT通道注册发送函数
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(CBTCPM_PortSndReg1, UT)
{
	uttest_CBTCPM_PortSndReg_case1();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:获取CBT通道接收函数地址
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(CBTCPM_GetRcvFunc1, UT)
{
	uttest_CBTCPM_GetRcvFunc_case1();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:获取CBT通道发送函数地址
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(CBTCPM_GetSndFunc1, UT)
{
	uttest_CBTCPM_GetSndFunc_case1();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:NAS走UART口做校准
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(CBTCPM_NotifyChangePort1, UT)
{
	MOCKER(CBTCPM_PortSndReg)
		.expects(once());

	MOCKER(CBTCPM_PortSndReg)
		.expects(once())
		.will(returnValue((void *)0));

	MOCKER(CBTCPM_PortRcvReg)
		.expects(once());

	MOCKER(AT_RcvFuncReg)
		.expects(once());

    MOCKER(AT_QuerySndFunc)
        .expects(once())
        .will(returnValue((void *)0));

	EXPECT_EQ(VOS_OK,uttest_CBTCPM_NotifyChangePort_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:NAS走其他口做校准
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(CBTCPM_NotifyChangePort2, UT)
{
	MOCKER(CBTCPM_PortSndReg)
		.expects(once());

	MOCKER(CBTCPM_PortRcvReg)
		.expects(once());

	MOCKER(AT_RcvFuncReg)
		.expects(once());

	EXPECT_EQ(VOS_ERR,uttest_CBTCPM_NotifyChangePort_case2());

	GlobalMockObject::reset();
}
