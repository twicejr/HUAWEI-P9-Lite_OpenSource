#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtBasicCmd.h"


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_AT_BASICCMD_C

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


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

/*****************************************************************************
类名 : Test_CheckIfDCmdValidChar
功能描述 : CheckIfDCmdValidChar UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_CheckIfDCmdValidChar: public ::testing::Test
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

/*******************************************************************
测试用例编号      : Test_CheckIfDCmdValidChar_001
被测函数功能描述  : 检测指定字符是否为D命令中可出现的合法字符
预期结果          : AT_SUCCESS
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_CheckIfDCmdValidChar, Test_CheckIfDCmdValidChar_001)
{
    VOS_UINT8 ucChar = 'A';
    VOS_UINT32 ulRet = 0;
    ulRet = At_CheckIfDCmdValidChar(ucChar);
    EXPECT_EQ(ulRet,AT_SUCCESS);

    ucChar = 'a';
    ulRet = 0;
    ulRet = At_CheckIfDCmdValidChar(ucChar);
    EXPECT_EQ(ulRet,AT_FAILURE);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_GetFirstBasicCmdAddr
功能描述 : GetFirstBasicCmdAddr UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_GetFirstBasicCmdAddr: public ::testing::Test
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

/*******************************************************************
测试用例编号      : Test_GetFirstBasicCmdAddr_001
被测函数功能描述  : 找到第一个匹配的命令并返回字符串首地址，将命令长度存入参数2中。***
预期结果          : 返回处理结果
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_GetFirstBasicCmdAddr, Test_GetFirstBasicCmdAddr_001)
{

    VOS_UINT8 *pData=NULL;
    VOS_UINT32 pulLen=0;
    VOS_UINT8 *pcRet=NULL;

    pData=(VOS_UINT8 *)&"c64416";
    pcRet=At_GetFirstBasicCmdAddr(pData, &pulLen);
    EXPECT_EQ((VOS_UINT_PTR)pcRet,NULL);
    EXPECT_EQ(pulLen,0);

    pData=(VOS_UINT8 *)&"wwD123E45";
    pcRet=At_GetFirstBasicCmdAddr(pData, &pulLen);
    EXPECT_EQ((VOS_UINT_PTR)pcRet,(VOS_UINT_PTR)(pData+2));
    EXPECT_EQ(pulLen,4);

    pData=(VOS_UINT8 *)&"wwE123E45";
    pcRet=At_GetFirstBasicCmdAddr(pData, &pulLen);
    EXPECT_EQ((VOS_UINT_PTR)pcRet,(VOS_UINT_PTR)(pData+2));
    EXPECT_EQ(pulLen,1);

    GlobalMockObject::verify();
}
