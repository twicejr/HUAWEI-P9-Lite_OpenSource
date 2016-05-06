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

/*******************************************************************
*测试项:处理SI_PB_READ_REQ消息成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_PidMsgProc1, UT)
{
    MOCKER(SI_PB_ReadProc)
        .expects(once())
        .will(returnValue((unsigned int)VOS_OK));

    uttest_SI_PB_PidMsgProc_case1();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:处理SI_PB_SET_REQ消息成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_PidMsgProc2, UT)
{
    MOCKER(SI_PB_ReadProc)
        .expects(never());

    uttest_SI_PB_PidMsgProc_case2();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:处理消息成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PBUpdateAGlobal1, UT)
{
    MOCKER(mdrv_phy_to_virt)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    EXPECT_EQ(VOS_OK, uttest_SI_PBUpdateAGlobal_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:处理消息成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PBUpdateACurPB1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PBUpdateACurPB_case1());
}

/*******************************************************************
*测试项:读取范围查过
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SReadEMLProc1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case1());
}

/*******************************************************************
*测试项:读取Type1范围OK
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SReadEMLProc2, UT)
{
	MOCKER(SI_PB_TransEMLFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:读取Type2IAP为空
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SReadEMLProc3, UT)
{
	MOCKER(SI_PB_TransEMLFromate)
		.expects(once());

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadEMLProc_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:读取Type2Index为空
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
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


/*******************************************************************
*测试项:读取Type2Index不为空
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项:读取Type2_OK
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项:ANR为空
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SReadANRProc1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadANRProc_case1());
}

/*******************************************************************
*测试项:TYPE2IAP为空
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SReadANRProc2, UT)
{
	EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadANRProc_case2());
}

/*******************************************************************
*测试项:TYPE2Index为空
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SReadANRProc3, UT)
{
	MOCKER(SI_PB_GetFileCntFromIndex)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PB_SReadANRProc_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:TYPE2Index不为空
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
*测试项:TYPE1Index不为空
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_WuepsPBPidInit_001
测试用例标题      : VOS_IP_LOAD_CONFIG阶段初始化全局变量
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-06-13
  作   者  : h59254
  修改内容 : SVLTE开发
*******************************************************************/
TEST(WuepsPBPidInit1, UT)
{
    // 执行检查
    EXPECT_EQ(VOS_OK, uttest_Test_WuepsPBPidInit_case1());
}

/*******************************************************************
测试用例编号      : Test_WuepsPBPidInit_002
测试用例标题      : VOS_IP_BUTT阶段给PB注册USIM事件
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-06-13
  作   者  : h59254
  修改内容 : SVLTE开发
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_WuepsPBPidInit_003
测试用例标题      : Default分支
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-06-13
  作   者  : h59254
  修改内容 : SVLTE开发
*******************************************************************/
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

