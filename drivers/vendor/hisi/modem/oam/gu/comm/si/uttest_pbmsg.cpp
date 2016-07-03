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
    extern void uttest_SI_PB_PidMsgProc_case1(void);
    extern void uttest_SI_PB_PidMsgProc_case2(void);
    extern unsigned int uttest_SI_PBUpdateAGlobal_case1(void);
    extern unsigned int uttest_SI_PBUpdateACurPB_case1(void);
    extern unsigned int uttest_SI_PB_SReadEMLProc_case1(void);
    extern unsigned int uttest_SI_PB_SReadEMLProc_case2(void);
    extern unsigned int uttest_SI_PB_SReadEMLProc_case3(void);
    extern unsigned int uttest_SI_PB_SReadEMLProc_case4(void);
    extern unsigned int uttest_SI_PB_SReadEMLProc_case5(void);
    extern unsigned int uttest_SI_PB_SReadEMLProc_case6(void);
    extern unsigned int uttest_SI_PB_SReadANRProc_case1(void);
    extern unsigned int uttest_SI_PB_SReadANRProc_case2(void);
    extern unsigned int uttest_SI_PB_SReadANRProc_case3(void);
    extern unsigned int uttest_SI_PB_SReadANRProc_case4(void);
    extern unsigned int uttest_SI_PB_SReadANRProc_case5(void);
    extern unsigned int uttest_Test_WuepsPBPidInit_case1(void);
    extern unsigned int uttest_Test_WuepsPBPidInit_case2(void);
    extern unsigned int uttest_Test_WuepsPBPidInit_case3(void);

    extern void SI_PB_TransEMLFromate(unsigned char ucEmailMaxLen, unsigned char *pEMLContent, void *pstRecord);
    extern unsigned int SI_PB_GetFileCntFromIndex(unsigned short ucIndex, unsigned char *pucFileCnt);
    extern void SI_PB_TransANRFromate(unsigned char ucANROffset, unsigned char *pANRContent, void *pstRecord);
    extern unsigned int PIH_RegUsimCardStatusIndMsg(unsigned int ulRegPID);
    extern unsigned int PIH_RegCardRefreshIndMsg(unsigned int ulRegPID);
    extern unsigned int SI_PB_ReadProc(void *pMsg);
    extern void *mdrv_phy_to_virt(void *pPhyAddr);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif

#ifndef VOS_NULL_PTR
#define VOS_NULL_PTR                    0
#endif


TEST(SI_PB_PidMsgProc1, UT)
{
    MOCKER(SI_PB_ReadProc)
        .expects(once())
        .will(returnValue((unsigned int)VOS_OK));

    uttest_SI_PB_PidMsgProc_case1();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::reset();
}


TEST(SI_PB_PidMsgProc2, UT)
{
    MOCKER(SI_PB_ReadProc)
        .expects(never());

    uttest_SI_PB_PidMsgProc_case2();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::reset();
}


TEST(SI_PBUpdateAGlobal1, UT)
{
    MOCKER(mdrv_phy_to_virt)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    EXPECT_EQ(VOS_OK, uttest_SI_PBUpdateAGlobal_case1());

    GlobalMockObject::reset();
}


TEST(SI_PBUpdateACurPB1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PBUpdateACurPB_case1());
}


TEST(SI_PB_SReadEMLProc1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case1());
}


TEST(SI_PB_SReadEMLProc2, UT)
{
	MOCKER(SI_PB_TransEMLFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case2());

    GlobalMockObject::reset();
}


TEST(SI_PB_SReadEMLProc3, UT)
{
	MOCKER(SI_PB_TransEMLFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case3());

    GlobalMockObject::reset();
}


TEST(SI_PB_SReadEMLProc4, UT)
{
	MOCKER(SI_PB_GetFileCntFromIndex)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	MOCKER(SI_PB_TransEMLFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case4());

    GlobalMockObject::reset();
}



TEST(SI_PB_SReadEMLProc5, UT)
{
	unsigned char			aucEmaIndex = 1;
	unsigned char          *pucIndex;

	MOCKER(SI_PB_GetFileCntFromIndex)
	    .stubs()
		.with(any(), outBoundP(pucIndex))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(SI_PB_TransEMLFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case5());

    GlobalMockObject::reset();
}


TEST(SI_PB_SReadEMLProc6, UT)
{
	unsigned char			aucEmaIndex = 1;
	unsigned char          *pucIndex;

	pucIndex = &aucEmaIndex;

	MOCKER(SI_PB_GetFileCntFromIndex)
	    .stubs()
		.with(any(), outBoundP(pucIndex))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(SI_PB_TransEMLFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case6());

    GlobalMockObject::reset();
}


TEST(SI_PB_SReadANRProc1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadANRProc_case1());
}


TEST(SI_PB_SReadANRProc2, UT)
{
	EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadANRProc_case2());
}


TEST(SI_PB_SReadANRProc3, UT)
{
	MOCKER(SI_PB_GetFileCntFromIndex)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadANRProc_case3());

    GlobalMockObject::reset();
}


TEST(SI_PB_SReadANRProc4, UT)
{
	unsigned char			aucEmaIndex = 1;
	unsigned char			*pucIndex;

	pucIndex = &aucEmaIndex;

	MOCKER(SI_PB_GetFileCntFromIndex)
	    .stubs()
		.with(any(), outBoundP(pucIndex))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(SI_PB_TransANRFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadANRProc_case4());

    GlobalMockObject::reset();
}


TEST(SI_PB_SReadANRProc5, UT)
{
	unsigned char			aucEmaIndex = 1;
	unsigned char			*pucIndex;

	pucIndex = &aucEmaIndex;

	MOCKER(SI_PB_GetFileCntFromIndex)
	    .stubs()
		.with(any(), outBoundP(pucIndex))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(SI_PB_TransANRFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadANRProc_case5());

    GlobalMockObject::reset();
}


TEST(WuepsPBPidInit1, UT)
{
    // 执行检查
    EXPECT_EQ(VOS_OK, uttest_Test_WuepsPBPidInit_case1());
}


TEST(WuepsPBPidInit2, UT)
{
	// MOCKER操作;
	MOCKER(PIH_RegUsimCardStatusIndMsg)
		.expects(once())
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(PIH_RegCardRefreshIndMsg)
		.expects(once())
		.will(returnValue((unsigned int)VOS_OK));

    // 执行检查
    EXPECT_EQ(VOS_OK, uttest_Test_WuepsPBPidInit_case2());

    GlobalMockObject::reset();
}


TEST(WuepsPBPidInit3, UT)
{
	// MOCKER操作;
	MOCKER(PIH_RegUsimCardStatusIndMsg)
		.expects(once())
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(PIH_RegCardRefreshIndMsg)
		.expects(once())
		.will(returnValue((unsigned int)VOS_OK));

    // 执行检查
    EXPECT_EQ(VOS_OK, uttest_Test_WuepsPBPidInit_case3());

    GlobalMockObject::reset();
}

