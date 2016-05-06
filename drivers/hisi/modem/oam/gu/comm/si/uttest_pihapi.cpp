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

    extern unsigned int uttest_SI_PIH_GetReceiverPid_case1(void);
    extern unsigned int uttest_SI_PIH_GetReceiverPid_case2(void);
    extern unsigned int uttest_SI_PIH_GetReceiverPid_case3(void);
    extern unsigned int uttest_SI_PIH_GetReceiverPid_case4(void);
    extern unsigned int uttest_SI_PIH_IsSvlte_case1(void);
    extern unsigned int uttest_SI_PIH_IsSvlte_case2(void);
    extern unsigned int uttest_SI_PIH_FdnBdnQuery_case1(void);
    extern unsigned int uttest_SI_PIH_FdnBdnQuery_case2(void);
    extern unsigned int uttest_SI_PIH_FdnBdnQuery_case3(void);
    extern unsigned int uttest_SI_PIH_FdnBdnQuery_case4(void);
    extern unsigned int uttest_SI_PIH_FdnBdnQuery_case5(void);
    extern unsigned int uttest_SI_PIH_GenericAccessReq_case1(void);
    extern unsigned int uttest_SI_PIH_GenericAccessReq_case2(void);
    extern unsigned int uttest_SI_PIH_GenericAccessReq_case3(void);
    extern unsigned int uttest_SI_PIH_GenericAccessReq_case4(void);
    extern unsigned int uttest_SI_PIH_GenericAccessReq_case5(void);
    extern unsigned int uttest_SI_PIH_GenericAccessReq_case6(void);
    extern unsigned int uttest_SI_PIH_GenericAccessReq_case7(void);
    extern unsigned int uttest_SI_PIH_FdnEnable_case1(void);
    extern unsigned int uttest_SI_PIH_FdnEnable_case2(void);
    extern unsigned int uttest_SI_PIH_FdnEnable_case3(void);
    extern unsigned int uttest_SI_PIH_FdnEnable_case4(void);
    extern unsigned int uttest_SI_PIH_FdnEnable_case5(void);
    extern unsigned int uttest_SI_PIH_FdnDisable_case1(void);
    extern unsigned int uttest_SI_PIH_FdnDisable_case2(void);
    extern unsigned int uttest_SI_PIH_FdnDisable_case3(void);
    extern unsigned int uttest_SI_PIH_FdnDisable_case4(void);
    extern unsigned int uttest_SI_PIH_FdnDisable_case5(void);
    extern unsigned int uttest_SI_PIH_IsdbAccessReq_case1(void);
    extern unsigned int uttest_SI_PIH_IsdbAccessReq_case2(void);
    extern unsigned int uttest_SI_PIH_IsdbAccessReq_case3(void);
    extern unsigned int uttest_SI_PIH_IsdbAccessReq_case4(void);
    extern unsigned int uttest_SI_PIH_IsdbAccessReq_case5(void);
    extern unsigned int uttest_SI_PIH_CchoSetReq_case1(void);
    extern unsigned int uttest_SI_PIH_CchoSetReq_case2(void);
    extern unsigned int uttest_SI_PIH_CchoSetReq_case3(void);
    extern unsigned int uttest_SI_PIH_CchoSetReq_case4(void);
    extern unsigned int uttest_SI_PIH_CchoSetReq_case5(void);
    extern unsigned int uttest_SI_PIH_CchcSetReq_case1(void);
    extern unsigned int uttest_SI_PIH_CchcSetReq_case2(void);
    extern unsigned int uttest_SI_PIH_CchcSetReq_case3(void);
    extern unsigned int uttest_SI_PIH_CchcSetReq_case4(void);
    extern unsigned int uttest_SI_PIH_CglaSetReq_case1(void);
    extern unsigned int uttest_SI_PIH_CglaSetReq_case2(void);
    extern unsigned int uttest_SI_PIH_CglaSetReq_case3(void);
    extern unsigned int uttest_SI_PIH_CglaSetReq_case3(void);
    extern unsigned int uttest_SI_PIH_CglaSetReq_case4(void);
    extern unsigned int uttest_SI_PIH_HvsDHSet_case1(void);
    extern unsigned int uttest_SI_PIH_HvsDHSet_case2(void);
    extern unsigned int uttest_SI_PIH_HvsDHSet_case3(void);
    extern unsigned int uttest_SI_PIH_HvsDHSet_case4(void);
    extern unsigned int uttest_SI_PIH_HvsDHSet_case5(void);
    extern unsigned int uttest_SI_PIH_HvsDHSet_case6(void);
    extern unsigned int uttest_SI_PIH_HvsDHQuery_case1(void);
    extern unsigned int uttest_SI_PIH_HvsDHQuery_case2(void);
    extern unsigned int uttest_SI_PIH_HvsDHQuery_case3(void);
    extern unsigned int uttest_SI_PIH_HvsDHQuery_case4(void);
    extern unsigned int uttest_SI_PIH_HvsContQuery_case1(void);
    extern unsigned int uttest_SI_PIH_HvsContQuery_case2(void);
    extern unsigned int uttest_SI_PIH_HvsContQuery_case3(void);
    extern unsigned int uttest_SI_PIH_HvsContQuery_case4(void);
    extern unsigned int uttest_SI_PIH_HvsContQuery_case1(void);
    extern unsigned int uttest_SI_PIH_HvsContQuery_case1(void);
    extern unsigned int uttest_SI_PIH_HvsContQuery_case2(void);
    extern unsigned int uttest_SI_PIH_HvsContQuery_case4(void);
    extern unsigned int uttest_SI_PIH_HvSstSet_case1(void);
    extern unsigned int uttest_SI_PIH_HvSstSet_case2(void);
    extern unsigned int uttest_SI_PIH_HvSstSet_case3(void);
    extern unsigned int uttest_SI_PIH_HvSstSet_case4(void);
    extern unsigned int uttest_SI_PIH_HvSstSet_case5(void);
    extern unsigned int uttest_SI_PIH_AtFileWrite_case1(void);
    extern unsigned int uttest_SI_PIH_AtFileWrite_case2(void);
    extern unsigned int uttest_SI_PIH_AtFileWrite_case3(void);
    extern unsigned int uttest_SI_PIH_AtFileWrite_case4(void);
    extern unsigned int uttest_SI_PIH_AtFileWrite_case5(void);
    extern unsigned int uttest_SI_PIH_AtFileWrite_case6(void);
    extern unsigned int uttest_SI_PIH_AtFileWrite_case7(void);
    extern unsigned int uttest_SI_PIH_UiccAuthReq_case1(void);
    extern unsigned int uttest_SI_PIH_UiccAuthReq_case2(void);
    extern unsigned int uttest_SI_PIH_UiccAuthReq_case3(void);
    extern unsigned int uttest_SI_PIH_UiccAuthReq_case4(void);
    extern unsigned int uttest_SI_PIH_UiccAuthReq_case5(void);
    extern unsigned int uttest_SI_PIH_AccessUICCFileReq_case1(void);
    extern unsigned int uttest_SI_PIH_AccessUICCFileReq_case2(void);
    extern unsigned int uttest_SI_PIH_AccessUICCFileReq_case3(void);
    extern unsigned int uttest_SI_PIH_AccessUICCFileReq_case4(void);
    extern unsigned int uttest_SI_PIH_AccessUICCFileReq_case5(void);

    extern unsigned int AT_GetModemIdFromClient(unsigned short usClientId, unsigned short *pModemId);
    extern unsigned int SI_PIH_IsSvlte(void);
    extern unsigned int NV_ReadEx(unsigned short enModemID, unsigned short usID, void *pItem, unsigned int ulLength);
    extern unsigned int uttest_NV_ReadEx_stub1(unsigned short enModemID, unsigned short usID, void *pItem, unsigned int ulLength);
    extern void * V_AllocMsg(unsigned int Pid, unsigned int ulLength, unsigned int ulFileID, signed int usLineNo);
    extern unsigned int V_SendMsg(unsigned int Pid, void **ppMsg, unsigned int ulFileID, signed int lLineNo);
    extern unsigned int SI_PIH_GetReceiverPid(unsigned short ClientId, unsigned int *pulReceiverPid);
#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif

#ifndef VOS_TRUE
#define VOS_TRUE                        1
#endif

#ifndef VOS_FALSE
#define VOS_FALSE                       0
#endif

#ifndef VOS_NULL_PTR
#define VOS_NULL_PTR                    0
#endif

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GetReceiverPid1, ERROR)
{
	MOCKER(AT_GetModemIdFromClient)
		.stubs()
        .will(returnValue(VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GetReceiverPid_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GetReceiverPid2, MODEMID0)
{
	unsigned short usModemID = 0;

	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.with(any(), outBoundP(&usModemID))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(SI_PIH_IsSvlte)
        .stubs()
		.will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GetReceiverPid_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GetReceiverPid3, MODEMID1)
{
	unsigned short usModemID = 1;

	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.with(any(), outBoundP(&usModemID))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(SI_PIH_IsSvlte)
        .stubs()
		.will(returnValue((unsigned int)VOS_FALSE));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_GetReceiverPid_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GetReceiverPid4, SVLTE)
{
	unsigned short usModemID = 1;

	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.with(any(), outBoundP(&usModemID))
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(SI_PIH_IsSvlte)
        .stubs()
		.will(returnValue((unsigned int)VOS_TRUE));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_GetReceiverPid_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:NV项读取失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_IsSvlte1, UT)
{
	MOCKER(NV_ReadEx)
        .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsSvlte_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:NV项读取成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_IsSvlte2, UT)
{
	MOCKER(NV_ReadEx)
		.stubs()
        .will(invoke(uttest_NV_ReadEx_stub1));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsSvlte_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnBdnQuery1, Error)
{
	unsigned char	                    aucData[100];

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnBdnQuery_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:查询当前的FDN状态
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnBdnQuery2, UT)
{
	unsigned char	                    aucData[100];

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
            .stubs()
            .will(returnValue((unsigned int)VOS_FALSE));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnBdnQuery_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: 查询当前的BDN状态
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnBdnQuery3, UT)
{
    unsigned char	                    aucData[100];

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
            .stubs()
            .will(returnValue((unsigned int)VOS_FALSE));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnBdnQuery_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:查询当前的FDN状态Failed
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnBdnQuery4, UT)
{
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
            .stubs()
            .will(returnValue((unsigned int)VOS_FALSE));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)0));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnBdnQuery_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:查询当前的FDN状态Failed
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnBdnQuery5, UT)
{
    unsigned char	                    aucData[100];

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
            .stubs()
            .will(returnValue((unsigned int)VOS_FALSE));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnBdnQuery_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GenericAccessReq1, Error)
{
	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GenericAccessReq_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: 输入参数错误
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GenericAccessReq2, UT)
{
	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GenericAccessReq_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: 长度大于5
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GenericAccessReq3, UT)
{
	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GenericAccessReq_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: 申请内存失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GenericAccessReq4, UT)
{
	MOCKER(V_AllocMsg)
        .stubs()
		.will(returnValue((void*)0));

	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GenericAccessReq_case4());

    GlobalMockObject::reset();
}
/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GenericAccessReq5, UT)
{
	unsigned char				 aucData[100];

	MOCKER(V_AllocMsg)
        .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_SendMsg)
        .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GenericAccessReq_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: 数据错误
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GenericAccessReq6, UT)
{
	unsigned char				 aucData[100];

	MOCKER(V_AllocMsg)
        .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GenericAccessReq_case6());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: 发送消息OK
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_GenericAccessReq7, UT)
{
    unsigned char                          aucData[100];

	MOCKER(V_AllocMsg)
        .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_GenericAccessReq_case7());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:Error
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnEnable1, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnEnable_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:未完成初始化
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnEnable2, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnEnable_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:申请消息内存失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnEnable3,UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)0));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnEnable_case3());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:消息发送失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnEnable4,UT)
{
    unsigned char                       aucData[100];

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
    	.stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnEnable_case4());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:消息发送成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnEnable5,UT)
{
    unsigned char                       aucData[100];

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnEnable_case5());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:Error
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnDisable1, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnDisable_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:未完成初始化
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnDisable2, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnDisable_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:申请消息内存失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnDisable3, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)VOS_NULL_PTR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnDisable_case3());

	GlobalMockObject::reset();

}

/*******************************************************************
*测试项:消息发送失败
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnDisable4, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnDisable_case4());

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:消息发送成功
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: w00184875
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_FdnDisable5, UT)
{
	unsigned char	                    aucData[100];

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_FdnDisable_case5());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_001
测试用例标题      : 输入的APDU长度为0
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
TEST(Test_SI_PIH_IsdbAccessReq1, UT)
{
	// 变量声明
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsdbAccessReq_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_001
测试用例标题      : 输入的APDU长度为0
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
TEST(Test_SI_PIH_IsdbAccessReq2, UT)
{
    unsigned short          usModemId = 0;

	// 变量声明
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
	    .with(any(), outBoundP(&usModemId))
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsdbAccessReq_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_003
测试用例标题      : 申请消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
TEST(Test_SI_PIH_IsdbAccessReq3, UT)
{
    unsigned short          usModemId = 0;

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
	    .with(any(), outBoundP(&usModemId))
		.will(returnValue((unsigned int)VOS_OK));


    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	//mocker
	MOCKER(V_AllocMsg)
	    .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsdbAccessReq_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
TEST(Test_SI_PIH_IsdbAccessReq4, UT)
{
    unsigned short          usModemId = 0;
    unsigned char	        aucData[100];

	//mocker
	MOCKER(V_AllocMsg)
	    .stubs()
        .will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
	    .with(any(), outBoundP(&usModemId))
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsdbAccessReq_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_IsdbAccessReq_005
测试用例标题      : 发送消息成功
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2012-09-04
  作   者  : h59254
  修改内容 : 安全存储项目新增
*******************************************************************/
TEST(Test_SI_PIH_IsdbAccessReq5, UT)
{
	// 变量声明
	unsigned short          usModemId = 0;
	unsigned char	        aucData[100];

	//mocker
	MOCKER(V_AllocMsg)
	    .stubs()
        .will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
        .will(returnValue((unsigned int)VOS_OK));

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
	    .with(any(), outBoundP(&usModemId))
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsdbAccessReq_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_001
测试用例标题      : 参数检测失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchoSetReq1, UT)
{
    // 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchoSetReq_case1());
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_002
测试用例标题      : 获取接收者PID失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchoSetReq2, UT)
{
    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchoSetReq_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_003
测试用例标题      : 分配消息内存失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchoSetReq3, UT)
{
    // 变量声明

    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchoSetReq_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchoSetReq4, UT)
{
    // 变量声明
    unsigned char	                    aucData[100];
    unsigned short                      usModemId = 0;

    //mocker
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .with(any(), outBoundP(&usModemId))
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));


    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchoSetReq_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchoSetReq_005
测试用例标题      : 执行成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchoSetReq5, UT)
{
    // 变量声明
    unsigned short                      usModemId = 0;
    unsigned char	                    aucData[100];

    //mocker
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .with(any(), outBoundP(&usModemId))
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));


    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchoSetReq_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchcSetReq_001
测试用例标题      : 获取接收者PID失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchcSetReq1, UT)
{
    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchcSetReq_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchcSetReq_002
测试用例标题      : 分配消息内存失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchcSetReq2, UT)
{
    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchcSetReq_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchcSetReq_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchcSetReq3, UT)
{
    // 变量声明
    unsigned char	                    aucData[100];

    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchcSetReq_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CchcSetReq_004
测试用例标题      : 执行成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CchcSetReq4, UT)
{
    // 变量声明
    unsigned char	                    aucData[100];

    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchcSetReq_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CglaSetReq_001
测试用例标题      : 获取接收者PID失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CglaSetReq1, UT)
{
    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CglaSetReq_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CglaSetReq_002
测试用例标题      : 分配消息内存失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CglaSetReq2, UT)
{
    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CglaSetReq_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CglaSetReq_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CglaSetReq3, UT)
{
    // 变量声明
    unsigned char	                    aucData[100];

    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CglaSetReq_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_CglaSetReq_004
测试用例标题      : 执行成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-05-21
  作   者  : g47350
  修改内容 : NFC-BIP项目新增
*******************************************************************/
TEST(SI_PIH_CglaSetReq4, UT)
{
    // 变量声明
    unsigned char	                    aucData[100];

    //mocker
    MOCKER(SI_PIH_GetReceiverPid)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_CglaSetReq_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_001
测试用例标题      : 参数检测空指针
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHSet1, UT)
{
    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case1());
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_002
测试用例标题      : 参数检测长度过大
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHSet2, UT)
{
    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case2());
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_003
测试用例标题      : client转换为ulReceiverPid失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHSet3, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	// 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case3());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_004
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHSet4, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

	// 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_005
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHSet5, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

	// 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHSet_006
测试用例标题      : 服务器密钥设置请求发到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHSet6, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

	// 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case6());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHQuery_001
测试用例标题      : client转换为ulReceiverPid失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHQuery1, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHQuery_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHQuery_002
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHQuery2, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHQuery_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHQuery_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHQuery3, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHQuery_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsDHQuery_004
测试用例标题      : 密钥查询发送到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsDHQuery4, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHQuery_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsContQuery_001
测试用例标题      : client转换为ulReceiverPid失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsContQuery1, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

   EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case1());

   GlobalMockObject::reset();
}


/*******************************************************************
测试用例编号      : SI_PIH_HvsContQuery_002
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsContQuery2, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsContQuery_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsContQuery3, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvsContQuery_004
测试用例标题      : 文件内容查询发送到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvsContQuery4, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstQuery_001
测试用例标题      : client转换为ulReceiverPid失败)
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstQuery1, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case1());

    GlobalMockObject::reset();
}


/*******************************************************************
测试用例编号      : SI_PIH_HvSstQuery_002
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstQuery2, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstQuery_003
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstQuery3, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstQuery_004
测试用例标题      : 卡状态查询发送到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstQuery4, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_001
测试用例标题      : 参数检测失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstSet1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvSstSet_case1());
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_002
测试用例标题      : client转换为ulReceiverPid失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstSet2, UT)
{
	unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvSstSet_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_003
测试用例标题      : 分配消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstSet3, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)VOS_NULL_PTR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvSstSet_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstSet4, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvSstSet_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : SI_PIH_HvSstSet_005
测试用例标题      : 卡状态设置发送到CCPU
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(SI_PIH_HvSstSet5, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvSstSet_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : At_SetHvsDHPara_001
测试用例标题      : 参数过多
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_SetHvsDHPara1, UT)
{
}

/*******************************************************************
测试用例编号      : At_SetHvsDHPara_002
测试用例标题      : 输入字符串为空
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_SetHvsDHPara2, UT)
{
}

/*******************************************************************
测试用例编号      : At_SetHvsDHPara_002
测试用例标题      : 分配内存失败
预期结果          : 函数返回AT_ERROR
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_SetHvsDHPara3, UT)
{
}

/*******************************************************************
测试用例编号      : At_SetHvsDHPara_003
测试用例标题      : BASE64解码失败
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_SetHvsDHPara4, UT)
{
}

/*******************************************************************
测试用例编号      : At_SetHvsDHPara_004
测试用例标题      : BASE64解码后数据过长
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_SetHvsDHPara5, UT)
{
}

/*******************************************************************
测试用例编号      : At_SetHvsDHPara_005
测试用例标题      : PIH接口返回失败
预期结果          : 函数返回AT_ERROR
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_SetHvsDHPara6, UT)
{
}

/*******************************************************************
测试用例编号      : At_SetHvsDHPara_005
测试用例标题      : 服务器密钥设置AT命令处理成功
预期结果          : 函数返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_SetHvsDHPara7, UT)
{
}

/*******************************************************************
测试用例编号      : At_QryHvsDHPara_001
测试用例标题      : PIH接口返回失败
预期结果          : 函数返回AT_ERROR
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_QryHvsDHPara1, UT)
{
}

/*******************************************************************
测试用例编号      : At_QryHvsDHPara_002
测试用例标题      : 密钥查询AT命令处理成功
预期结果          : 函数返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_QryHvsDHPara2, UT)
{
}

/*******************************************************************
测试用例编号      : At_TestHvsDHPara_001
测试用例标题      : 返回成功
预期结果          : 函数返回AT_OK
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_TestHvsDHPara1, UT)
{
}

/*******************************************************************
测试用例编号      : At_QryHvsContPara_001
测试用例标题      : PIH接口返回失败
预期结果          : 函数返回AT_ERROR
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_QryHvsContPara1, UT)
{
}

/*******************************************************************
测试用例编号      : At_QryHvsContPara_002
测试用例标题      : 查询文件内容AT命令处理成功
预期结果          : 函数返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2013-04-02
  作   者  : g47350
  修改内容 : BalongV300R002 vSIM开发项目
*******************************************************************/
TEST(At_QryHvsContPara2, UT)
{
}


/*******************************************************************
*测试项:SI_PIH_AtFileWrite_001
*被测函数功能描述:client转换为ulReceiverPid失败
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_AtFileWrite1, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_002
*被测函数功能描述:pstData为空
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_AtFileWrite2, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_003
*被测函数功能描述:1 pstData不为空
                  2 pstData中文件内容为空
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_AtFileWrite3, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_004
*被测函数功能描述:1 pstData不为空
                  2 pstData中文件长度为空
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_AtFileWrite4, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_005
*被测函数功能描述:1 pstData不为空
                  2 pstData中所有属性不为空
                  3 分配内存失败
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_AtFileWrite5, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)VOS_NULL_PTR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_006
*被测函数功能描述:1 pstData不为空
                  2 pstData中所有属性不为空
                  3 分配内存成功
                  4 发送消息失败
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_AtFileWrite6, UT)
{
	unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case6());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:SI_PIH_AtFileWrite_007
*被测函数功能描述:1 pstData不为空
                  2 pstData中所有属性不为空
                  3 分配内存成功
                  4 发送消息成功
*预期结果：返回error
************************* 修改记录 *********************************
#  1.日    期: 2013-04-10
#    作    者: z00208519
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PIH_AtFileWrite7, UT)
{
	unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case7());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_001
测试用例标题      : Client Id转换失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_UiccAuthReq1, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_UiccAuthReq_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_002
测试用例标题      : 鉴权参数为空指针
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_UiccAuthReq2, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_UiccAuthReq_case2());


    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_003
测试用例标题      : 申请消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_UiccAuthReq3, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
                .stubs()
                .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)VOS_NULL_PTR));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_UiccAuthReq_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_UiccAuthReq4, UT)
{
	unsigned char	                    aucData[1000];

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
        .stubs()
        .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_UiccAuthReq_case4());


    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_UiccAuthReq_005
测试用例标题      : 发送消息成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_UiccAuthReq5, UT)
{
	// 变量声明
	unsigned char	                    aucData[1000];

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
        .stubs()
        .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_UiccAuthReq_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_001
测试用例标题      : Client Id转换失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_AccessUICCFileReq1, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_AccessUICCFileReq_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_002
测试用例标题      : 鉴权参数为空指针
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_AccessUICCFileReq2, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
        .stubs()
        .will(returnValue((unsigned int)VOS_FALSE));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_AccessUICCFileReq_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_003
测试用例标题      : 申请消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_AccessUICCFileReq3, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
        .stubs()
        .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)VOS_NULL_PTR));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_AccessUICCFileReq_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_005
测试用例标题      : 发送消息成功
预期结果          : 函数返回TAF_SUCCESS
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_AccessUICCFileReq4, UT)
{

	// 变量声明
	unsigned char	                    aucData[1000];

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
        .stubs()
        .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_AccessUICCFileReq_case4());


    GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : Test_SI_PIH_AccessUICCFileReq_004
测试用例标题      : 发送消息失败
预期结果          : 函数返回TAF_FAILURE
修改历史          :
1.日   期  : 2014-03-24
  作   者  : h59254
  修改内容 : GBA项目开发
*******************************************************************/
TEST(Test_SI_PIH_AccessUICCFileReq5, UT)
{

	// 变量声明
	unsigned char	                    aucData[1000];

	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    MOCKER(SI_PIH_IsSvlte)
        .stubs()
        .will(returnValue((unsigned int)VOS_FALSE));

	MOCKER(V_AllocMsg)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

	MOCKER(V_SendMsg)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_AccessUICCFileReq_case5());


    GlobalMockObject::reset();
}


