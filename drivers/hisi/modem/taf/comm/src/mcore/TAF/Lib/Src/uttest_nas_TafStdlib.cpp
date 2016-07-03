#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "v_typdef.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "TafStdlib.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

//说明：经过改造后的gtest+，测试套和测试用例名字不允许为空
//      请避免用和gtest相同的关键字，避免不必要的麻烦
//      gtest提供 EXPECT 和 ASSERT 两套,具体含义可以看胶片，两套宏都是一一对应的，下面以EXPECT为例

//1、比对布尔类型 EXPECT_TRUE　EXPECT_FALSE/ASSERT_TRUE
//2、比较整形 EXPECT_EQ EXPECT_NE
//3、比较字符串 EXPECT_STREQ
//4、设置失败输出信息 ADD_FAILUREd
//5、设置成功和失败 SUCCEED FAIL
//6、自定义格式 EXPECT_PRED_FORMAT3
//7、期望带入参数返回TRUE EXPECT_PRED1
//8、浮点型比较 EXPECT_FLOAT_EQ EXPECT_PRED_FORMAT2 ASSERT_PRED_FORMAT2
//9、类型检查 StaticAssertTypeEq
//10、设置3种测试级别事件
//11、获取测试用例名字 test_case_name()
//12、比较异常 EXPECT_THROW
//13、结构体类型比较ASSERT_SAME_DATA ASSERT_SAME_MEMORY

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_STD_LIB_C

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


class TEST_TAF_STD_AsciiNum2HexString: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();

    }

    void TearDown()
    {
    }
};

TEST_F(TEST_TAF_STD_AsciiNum2HexString, TEST_TAF_STD_AsciiNum2HexString_001)
{
    VOS_UINT8               aucDigit[] = "12gf";
    VOS_UINT16              usLength;
    VOS_UINT32              ulRet;

    ulRet = TAF_STD_AsciiNum2HexString(aucDigit, &usLength);

    
    EXPECT_EQ(VOS_FALSE, ulRet);

    // 执行检查
    GlobalMockObject::verify();

}


TEST_F(TEST_TAF_STD_AsciiNum2HexString, TEST_TAF_STD_AsciiNum2HexString_002)
{
    VOS_UINT8               aucDigit[] = "12fg";
    VOS_UINT16              usLength;
    VOS_UINT32              ulRet;

    ulRet = TAF_STD_AsciiNum2HexString(aucDigit, &usLength);

    
    EXPECT_EQ(VOS_FALSE, ulRet);

    // 执行检查
    GlobalMockObject::verify();

}


class TEST_TAF_STD_UnPack7Bit: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();

    }

    void TearDown()
    {
    }
};


TEST_F(TEST_TAF_STD_UnPack7Bit, TEST_TAF_STD_UnPack7Bit_001)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucOrgChar[2];

    ulRet = TAF_STD_UnPack7Bit(VOS_NULL_PTR, 0, 0, VOS_NULL_PTR);

    EXPECT_EQ(VOS_ERR, ulRet);

    PS_MEM_SET(aucOrgChar, 0, sizeof(aucOrgChar));
    ulRet = TAF_STD_UnPack7Bit(aucOrgChar, 0, 0, VOS_NULL_PTR);

    EXPECT_EQ(VOS_ERR, ulRet);

    // 执行检查
    GlobalMockObject::verify();

}


class TEST_TAF_STD_Pack7Bit: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();

    }

    void TearDown()
    {
    }
};


TEST_F(TEST_TAF_STD_Pack7Bit, TEST_TAF_STD_Pack7Bit_001)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucOrgChar[] = {0x80, 0x31};
    VOS_UINT8                           aucPackedChar[2];
    VOS_UINT32                          ulLen;

    ulRet = TAF_STD_Pack7Bit(aucOrgChar, sizeof(aucOrgChar), 0, aucPackedChar, &ulLen);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(TEST_TAF_STD_Pack7Bit, TEST_TAF_STD_Pack7Bit_002)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucOrgChar[] = {0x80, 0x31};
    VOS_UINT8                           aucPackedChar[2];
    VOS_UINT32                          ulLen;

    ulRet = TAF_STD_Pack7Bit(aucOrgChar, sizeof(aucOrgChar), 0, aucPackedChar, VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}



