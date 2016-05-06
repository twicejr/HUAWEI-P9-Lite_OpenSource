#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtParseExtendCmd.h"


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

#if(FEATURE_ON == FEATURE_E5)
/******************************************************************************
类名     : Test_AT_ParseSetApMacCmd
功能描述 : AT_ParseSetApMacCmd UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_AT_ParseSetApMacCmd: public ::testing::Test
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
*测试项:          解析是否是APMAC设置命令，如果是提取名称和长度
*被测函数功能描述:解析是否是APMAC设置命令，输入字符串长度为0
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseSetApMacCmd,Test_AT_ParseSetApMacCmd_01 )
{
    // 参数定义
	VOS_UINT8                          *pucData;
	VOS_UINT16                          usLen;
	VOS_UINT8                           auData[30]="";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucData = auData;
	usLen = 0;

    // 相关全局变量初始化

    // MOCKER操作;


	// 调用被测函数
    ulRst = AT_ParseSetApMacCmd(pucData,usLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          解析是否是APMAC设置命令，如果是提取名称和长度
*被测函数功能描述:解析是否是APMAC设置命令，分配内存失败
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseSetApMacCmd,Test_AT_ParseSetApMacCmd_02)
{
    // 参数定义
	VOS_UINT8                          *pucData;
	VOS_UINT16                          usLen;
	VOS_UINT8                           auData[30]="AT^APMAC=00:1E:10:12:F6:16";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucData = auData;
	usLen = 26;

    // 相关全局变量初始化

    // MOCKER操作;
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    MOCKER(V_MemAlloc)
		.will(returnValue(VOS_NULL_PTR));
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

	// 调用被测函数
    ulRst = AT_ParseSetApMacCmd(pucData,usLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          解析是否是APMAC设置命令，如果是提取名称和长度
*被测函数功能描述:解析是否是APMAC设置命令，去掉字符串中的退格符出错
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseSetApMacCmd,Test_AT_ParseSetApMacCmd_03)
{
    // 参数定义
	VOS_UINT8                          *pucData;
	VOS_UINT16                          usLen;
	VOS_UINT8                           auData[30]="AT^APMAC=00:1E:10:12:F6:16";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucData = auData;
	usLen = 26;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(At_ScanDelChar)
		.will(returnValue(AT_FAILURE));

	// 调用被测函数
    ulRst = AT_ParseSetApMacCmd(pucData,usLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          解析是否是APMAC设置命令，如果是提取名称和长度
*被测函数功能描述:解析是否是APMAC设置命令，去掉字符串中的控制符出错
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseSetApMacCmd,Test_AT_ParseSetApMacCmd_04)
{
    // 参数定义
	VOS_UINT8                          *pucData;
	VOS_UINT16                          usLen;
	VOS_UINT8                           auData[30]="AT^APMAC=00:1E:10:12:F6:16";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucData = auData;
	usLen = 26;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(At_ScanDelChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanCtlChar)
		.will(returnValue(AT_FAILURE));

	// 调用被测函数
    ulRst = AT_ParseSetApMacCmd(pucData,usLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
*测试项:          解析是否是APMAC设置命令，如果是提取名称和长度
*被测函数功能描述:解析是否是APMAC设置命令，去掉字符串中的空格出错
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseSetApMacCmd,Test_AT_ParseSetApMacCmd_05)
{
    // 参数定义
	VOS_UINT8                          *pucData;
	VOS_UINT16                          usLen;
	VOS_UINT8                           auData[30]="AT^APMAC=00:1E:10:12:F6:16";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucData = auData;
	usLen = 26;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(At_ScanDelChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanCtlChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanBlankChar)
		.will(returnValue(AT_FAILURE));

	// 调用被测函数
    ulRst = AT_ParseSetApMacCmd(pucData,usLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          解析是否是APMAC设置命令，如果是提取名称和长度
*被测函数功能描述:解析是否是APMAC设置命令，字符串长度小于9
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseSetApMacCmd,Test_AT_ParseSetApMacCmd_06)
{
    // 参数定义
	VOS_UINT8                          *pucData;
	VOS_UINT16                          usLen;
	VOS_UINT8                           auData[30]="AT^APMA=";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucData = auData;
	usLen = 8;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(At_ScanDelChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanCtlChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanBlankChar)
		.will(returnValue(AT_SUCCESS));

	// 调用被测函数
    ulRst = AT_ParseSetApMacCmd(pucData,usLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          解析是否是APMAC设置命令，如果是提取名称和长度
*被测函数功能描述:解析是否是APMAC设置命令，字符串头不为AT^APMAC=
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseSetApMacCmd,Test_AT_ParseSetApMacCmd_07)
{
    // 参数定义
	VOS_UINT8                          *pucData;
	VOS_UINT16                          usLen;
	VOS_UINT8                           auData[30]="AT^APMCC=00:1E:10:12:F6:16";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucData = auData;
	usLen = 26;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(At_ScanDelChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanCtlChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanBlankChar)
		.will(returnValue(AT_SUCCESS));

	// 调用被测函数
    ulRst = AT_ParseSetApMacCmd(pucData,usLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          解析是否是APMAC设置命令，如果是提取名称和长度
*被测函数功能描述:解析是否是APMAC设置命令，解析成功
*预期结果：       返回AT_SUCCESS
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseSetApMacCmd,Test_AT_ParseSetApMacCmd_08)
{
    // 参数定义
	VOS_UINT8                          *pucData;
	VOS_UINT16                          usLen;
	VOS_UINT8                           auData[40]="AT^WIFIGLOBALMAC=00:1E:10:12:F6:16";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucData = auData;
	usLen = 34;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(At_ScanDelChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanCtlChar)
		.will(returnValue(AT_SUCCESS));

	MOCKER(At_ScanBlankChar)
		.will(returnValue(AT_SUCCESS));

	// 调用被测函数
    ulRst = AT_ParseSetApMacCmd(pucData,usLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_SUCCESS);
	EXPECT_EQ(gstATCmdName.usCmdNameLen,strlen("^WIFIGLOBALMAC"));
	EXPECT_EQ(strcmp((const char*)gstATCmdName.aucCmdName,"^WIFIGLOBALMAC"),0);
	EXPECT_EQ(gastAtParaList[0].usParaLen,17);
	EXPECT_EQ(strcmp((const char*)gastAtParaList[0].aucPara,"00:1E:10:12:F6:16"),0);
	EXPECT_EQ(gucAtParaIndex,1);
	EXPECT_EQ(gucAtCmdOptType ,AT_CMD_OPT_SET_PARA_CMD);
	EXPECT_EQ(gucAtCmdFmtType ,AT_EXTEND_CMD_TYPE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#endif
