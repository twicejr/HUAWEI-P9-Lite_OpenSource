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


/*******************************************************************
测试用例编号      : OM_RingBufferCreate_001
测试用例标题      : 内存申请失败了
预期结果          : 函数返回NULL
修改历史          :
1.日   期  : 2012-08-27
  作   者  : x51137
  修改内容 : v9r1MSP拆分和可维可测开发项目修改函数
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferCreate_002
测试用例标题      : 创建成功
预期结果          : 函数返回控制结构体
修改历史          :
1.日   期  : 2012-08-27
  作   者  : x51137
  修改内容 : v9r1MSP拆分和可维可测开发项目修改函数
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferCreate_003
测试用例标题      : Buffer控制信息已经满了
预期结果          : 函数返回NULL
修改历史          :
1.日   期  : 2012-08-27
  作   者  : x51137
  修改内容 : v9r1MSP拆分和可维可测开发项目修改函数
*******************************************************************/
TEST(OM_RingBufferCreate3, UT)
{
	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreate_case3());
}

/*******************************************************************
测试用例编号      : OM_RingBufferCreateEx_001
测试用例标题      : 传入指针为NULL
预期结果          : 函数返回NULL
修改历史          :
1.日   期  : 2013-09-03
  作   者  : d00212987
  修改内容 : Error Log上报和工程模式项目新增函数
*******************************************************************/
TEST(OM_RingBufferCreateEx1, UT)
{
	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case1());
}

/*******************************************************************
测试用例编号      : OM_RingBufferCreateEx_002
测试用例标题      : 管理空间大于8k
预期结果          : 函数返回NULL
修改历史          :
1.日   期  : 2013-09-03
  作   者  : d00212987
  修改内容 : Error Log上报和工程模式项目新增函数
*******************************************************************/
TEST(OM_RingBufferCreateEx2, UT)
{
	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case2());
}

/*******************************************************************
测试用例编号      : OM_RingBufferCreateEx_003
测试用例标题      : Buffer控制信息已经满了
预期结果          : 函数返回NULL
修改历史          :
1.日   期  : 2013-09-03
  作   者  : d00212987
  修改内容 : Error Log上报和工程模式项目新增函数
*******************************************************************/
TEST(OM_RingBufferCreateEx3, UT)
{
    // 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case3());
}

/*******************************************************************
测试用例编号      : OM_RingBufferCreateEx_004
测试用例标题      : 创建环形buffer成功
预期结果          : 函数返回NULL
修改历史          :
1.日   期  : 2013-09-03
  作   者  : d00212987
  修改内容 : Error Log上报和工程模式项目新增函数
*******************************************************************/
TEST(OM_RingBufferCreateEx4, UT)
{
    // 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case4());
}

/*******************************************************************
测试用例编号      : OM_RingBufferNBytes_001
测试用例标题      : 环形buffer中字节数
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
TEST(OM_RingBufferNBytes1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferNBytes_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : OM_RingBufferNBytes_001
测试用例标题      : 环形buffer中空闲字节数
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferIsFull_001
测试用例标题      : 环形buffer中已满
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
TEST(OM_RingBufferIsFull1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsFull_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : OM_RingBufferIsFull_001
测试用例标题      : 环形buffer中未满
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
TEST(OM_RingBufferIsFull2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsFull_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : OM_RingBufferIsEmpty_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
TEST(OM_RingBufferIsEmpty1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsEmpty_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : OM_RingBufferIsEmpty_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferIsEmpty_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferRemove_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
TEST(OM_RingBufferRemove1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : OM_RingBufferRemove_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
TEST(OM_RingBufferRemove2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : OM_RingBufferRemove_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
TEST(OM_RingBufferRemove3, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// 执行检查
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case3());

	GlobalMockObject::reset();
}

/*******************************************************************
测试用例编号      : OM_RingBufferPut_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferPut_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferPut_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferGet_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
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

/*******************************************************************
测试用例编号      : OM_RingBufferPut_001
测试用例标题      : 环形buffer中未空
预期结果          : 函数返回字节数
修改历史          :
1.日   期  : 2013-11-26
	作   者  : J00168360
	修改内容 :
*******************************************************************/
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
