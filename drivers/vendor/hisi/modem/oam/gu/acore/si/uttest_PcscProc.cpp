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

    extern unsigned int uttest_PCSC_AcpuCmdReq_case1(void);
    extern unsigned int uttest_PCSC_AcpuCmdReq_case2(void);
    extern unsigned int uttest_PCSC_AcpuCmdReq_case3(void);
    extern unsigned int uttest_PCSC_AcpuCmdReq_case4(void);
    extern unsigned int uttest_PCSC_AcpuGetCardStatus_case1(void);
    extern unsigned int uttest_PCSC_AcpuGetCardStatus_case2(void);
    extern void uttest_PCSC_UpdateCardStatus_case1(void);
    extern void uttest_PCSC_AcpuMsgProc_case1(void);
    extern void uttest_PCSC_AcpuMsgProc_case2(void);
    extern void uttest_PCSC_AcpuMsgProc_case3(void);

    extern void *V_AllocMsg(unsigned int Pid, unsigned int ulLength, unsigned int ulFileID, signed int usLineNo);
    extern unsigned int V_SendMsg(unsigned int Pid, void **ppMsg, unsigned int ulFileID, signed int lLineNo);
    extern void PCSC_UpdateCardStatus(void *pstMsg);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif


TEST(PCSC_AcpuCmdReq1, UT)
{
	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)0));

	EXPECT_EQ(VOS_OK, uttest_PCSC_AcpuCmdReq_case1());

	GlobalMockObject::reset();
}


TEST(PCSC_AcpuCmdReq2, UT)
{
	unsigned char                       aucData[100];

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_PCSC_AcpuCmdReq_case2());

	GlobalMockObject::reset();
}

TEST(PCSC_AcpuCmdReq3, UT)
{
	unsigned char                       aucData[100];

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_PCSC_AcpuCmdReq_case3());

	GlobalMockObject::reset();
}


TEST(PCSC_AcpuCmdReq4, UT)
{
	unsigned char                       aucData[100];

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_PCSC_AcpuCmdReq_case4());

	GlobalMockObject::reset();
}


TEST(PCSC_AcpuGetCardStatus1, UT)
{
	EXPECT_EQ(VOS_OK, uttest_PCSC_AcpuGetCardStatus_case1());
}


TEST(PCSC_AcpuGetCardStatus2, UT)
{
	EXPECT_EQ(VOS_OK, uttest_PCSC_AcpuGetCardStatus_case2());
}


TEST(PCSC_UpdateCardStatus1, UT)
{
	uttest_PCSC_UpdateCardStatus_case1();
}


TEST(PCSC_AcpuMsgProc1, UT)
{
	uttest_PCSC_AcpuMsgProc_case1();
}


TEST(PCSC_AcpuMsgProc2, UT)
{
	MOCKER(PCSC_UpdateCardStatus)
	    .expects(once());

	uttest_PCSC_AcpuMsgProc_case2();

	GlobalMockObject::reset();
}


TEST(PCSC_AcpuMsgProc3, UT)
{
	uttest_PCSC_AcpuMsgProc_case3();

	GlobalMockObject::reset();
}