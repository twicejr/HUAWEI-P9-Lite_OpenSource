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


TEST(SI_PIH_GetReceiverPid1, ERROR)
{
	MOCKER(AT_GetModemIdFromClient)
		.stubs()
        .will(returnValue(VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GetReceiverPid_case1());

    GlobalMockObject::reset();
}


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


TEST(SI_PIH_IsSvlte1, UT)
{
	MOCKER(NV_ReadEx)
        .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsSvlte_case1());

    GlobalMockObject::reset();
}


TEST(SI_PIH_IsSvlte2, UT)
{
	MOCKER(NV_ReadEx)
		.stubs()
        .will(invoke(uttest_NV_ReadEx_stub1));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_IsSvlte_case2());

    GlobalMockObject::reset();
}


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


TEST(SI_PIH_GenericAccessReq1, Error)
{
	MOCKER(AT_GetModemIdFromClient)
        .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_GenericAccessReq_case1());

    GlobalMockObject::reset();
}


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


TEST(SI_PIH_CchoSetReq1, UT)
{
    // 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_CchoSetReq_case1());
}


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


TEST(SI_PIH_HvsDHSet1, UT)
{
    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case1());
}


TEST(SI_PIH_HvsDHSet2, UT)
{
    // 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case2());
}


TEST(SI_PIH_HvsDHSet3, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	// 调用被测函数
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsDHSet_case3());

	GlobalMockObject::reset();
}


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


TEST(SI_PIH_HvsContQuery1, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

   EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case1());

   GlobalMockObject::reset();
}



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


TEST(SI_PIH_HvSstQuery1, UT)
{
    unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvsContQuery_case1());

    GlobalMockObject::reset();
}



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


TEST(SI_PIH_HvSstSet1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvSstSet_case1());
}


TEST(SI_PIH_HvSstSet2, UT)
{
	unsigned char	                    aucData[100];

	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_OK, uttest_SI_PIH_HvSstSet_case2());

	GlobalMockObject::reset();
}


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


TEST(At_SetHvsDHPara1, UT)
{
}


TEST(At_SetHvsDHPara2, UT)
{
}


TEST(At_SetHvsDHPara3, UT)
{
}


TEST(At_SetHvsDHPara4, UT)
{
}


TEST(At_SetHvsDHPara5, UT)
{
}


TEST(At_SetHvsDHPara6, UT)
{
}


TEST(At_SetHvsDHPara7, UT)
{
}


TEST(At_QryHvsDHPara1, UT)
{
}


TEST(At_QryHvsDHPara2, UT)
{
}


TEST(At_TestHvsDHPara1, UT)
{
}


TEST(At_QryHvsContPara1, UT)
{
}


TEST(At_QryHvsContPara2, UT)
{
}



TEST(SI_PIH_AtFileWrite1, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case1());

    GlobalMockObject::reset();
}


TEST(SI_PIH_AtFileWrite2, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case2());

    GlobalMockObject::reset();
}


TEST(SI_PIH_AtFileWrite3, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case3());

    GlobalMockObject::reset();
}


TEST(SI_PIH_AtFileWrite4, UT)
{
	MOCKER(SI_PIH_GetReceiverPid)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PIH_AtFileWrite_case4());

    GlobalMockObject::reset();
}


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


TEST(Test_SI_PIH_AccessUICCFileReq1, UT)
{
	MOCKER(AT_GetModemIdFromClient)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	// 调用被测函数
	EXPECT_EQ(VOS_OK, uttest_SI_PIH_AccessUICCFileReq_case1());

    GlobalMockObject::reset();
}


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


