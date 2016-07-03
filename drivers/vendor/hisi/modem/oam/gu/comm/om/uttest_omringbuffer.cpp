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
    extern unsigned int uttest_OM_RingBufferCreate_case1(void);
    extern unsigned int uttest_OM_RingBufferCreate_case2(void);
    extern unsigned int uttest_OM_RingBufferCreate_case3(void);
    extern unsigned int uttest_OM_RingBufferCreateEx_case1(void);
    extern unsigned int uttest_OM_RingBufferCreateEx_case2(void);
    extern unsigned int uttest_OM_RingBufferCreateEx_case3(void);
    extern unsigned int uttest_OM_RingBufferCreateEx_case4(void);
    extern unsigned int uttest_OM_RingBufferNBytes_case1(void);
    extern unsigned int uttest_OM_RingBufferFreeBytes_case1(void);
    extern unsigned int uttest_OM_RingBufferIsFull_case1(void);
    extern unsigned int uttest_OM_RingBufferIsFull_case2(void);
    extern unsigned int uttest_OM_RingBufferIsEmpty_case1(void);
    extern unsigned int uttest_OM_RingBufferGetReserve_case1(void);
    extern unsigned int uttest_OM_RingBufferGetReserve_case2(void);
    extern unsigned int uttest_OM_RingBufferRemove_case1(void);
    extern unsigned int uttest_OM_RingBufferRemove_case2(void);
    extern unsigned int uttest_OM_RingBufferRemove_case3(void);
    extern unsigned int uttest_OM_RingBufferPut_case1(void);
    extern unsigned int uttest_OM_RingBufferPut_case2(void);
    extern unsigned int uttest_OM_RingBufferPut_case3(void);
    extern unsigned int uttest_OM_RingBufferPut_case4(void);
    extern unsigned int uttest_OM_RingBufferPut_case5(void);

    extern void *__kmalloc(unsigned int ulSize, unsigned int ulFlag);
    extern void OM_RealMemCopy( const char *source, char *destination, int nbytes );
    extern void BSP_MNTN_SystemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif



TEST(OM_RingBufferCreate1, UT)
{
	// 调用被测函数
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(once());

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreate_case1());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferCreate2, UT)
{
	// 调用被测函数
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreate_case2());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferCreate3, UT)
{
	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreate_case3());
}


TEST(OM_RingBufferCreateEx1, UT)
{
	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case1());
}


TEST(OM_RingBufferCreateEx2, UT)
{
	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case2());
}


TEST(OM_RingBufferCreateEx3, UT)
{
    // 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case3());
}


TEST(OM_RingBufferCreateEx4, UT)
{
    // 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case4());
}


TEST(OM_RingBufferNBytes1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferNBytes_case1());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferFreeBytes1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferFreeBytes_case1());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferIsFull1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsFull_case1());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferIsFull2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsFull_case2());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferIsEmpty1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsEmpty_case1());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferGetReserve1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

    MOCKER(OM_RealMemCopy)
        .expects(exactly(2));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferGetReserve_case1());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferGetReserve2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
		.expects(exactly(2));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferGetReserve_case2());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferRemove1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case1());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferRemove2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case2());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferRemove3, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case3());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferPut1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
	    .expects(once());

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case1());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferPut2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
	    .expects(exactly(2));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case2());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferPut3, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
		.expects(exactly(1));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case3());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferGet4, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
		.expects(exactly(1));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case4());

	GlobalMockObject::reset();
}


TEST(OM_RingBufferGet5, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
		.expects(exactly(1));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case5());

	GlobalMockObject::reset();
}
