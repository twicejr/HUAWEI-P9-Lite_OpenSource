#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "AtCheckFunc.h"

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
 
/*******************************************************************
*测试项:atCheckBasicCmdName_001          
*被测函数功能描述:检查指定字符是否属于basic 字符
*预期结果：是:返回 AT_SUCCESS    
           否:返回 AT_FAILURE
           
#  1.日    期: 2013年10月26日
#    作    者: z00189113
#    修改内容: 新建CASE
*******************************************************************/
TEST(atCheckBasicCmdName,atCheckBasicCmdName_001)
{
    // 参数定义
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // 参数初始化
    uchar = 's';

    // 相关全局变量初始化


    // MOCKER操作;


    // 调用被测函数
    ulRst = atCheckBasicCmdName(uchar);

    // 执行检查
    EXPECT_EQ(ulRst,AT_SUCCESS);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:atCheckBasicCmdName_002          
*被测函数功能描述:检查指定字符是否属于basic 字符
*预期结果：是:返回 AT_SUCCESS    
           否:返回 AT_FAILURE
           
#  1.日    期: 2013年10月26日
#    作    者: z00189113
#    修改内容: 新建CASE
*******************************************************************/
TEST(atCheckBasicCmdName,atCheckBasicCmdName_002)
{
    // 参数定义
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // 参数初始化
    uchar = 'S';

    // 相关全局变量初始化


    // MOCKER操作;


    // 调用被测函数
    ulRst = atCheckBasicCmdName(uchar);

    // 执行检查
    EXPECT_EQ(ulRst,AT_SUCCESS);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:atCheckBasicCmdName_003          
*被测函数功能描述:检查指定字符是否属于basic 字符
*预期结果：是:返回 AT_SUCCESS    
           否:返回 AT_FAILURE
           
#  1.日    期: 2013年10月26日
#    作    者: z00189113
#    修改内容: 新建CASE
*******************************************************************/
TEST(atCheckBasicCmdName,atCheckBasicCmdName_003)
{
    // 参数定义
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // 参数初始化
    uchar = 'o';

    // 相关全局变量初始化


    // MOCKER操作;


    // 调用被测函数
    ulRst = atCheckBasicCmdName(uchar);

    // 执行检查
    EXPECT_EQ(ulRst,AT_SUCCESS);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:atCheckBasicCmdName_004          
*被测函数功能描述:检查指定字符是否属于basic 字符
*预期结果：是:返回 AT_SUCCESS    
           否:返回 AT_FAILURE
           
#  1.日    期: 2013年10月26日
#    作    者: z00189113
#    修改内容: 新建CASE
*******************************************************************/
TEST(atCheckBasicCmdName,atCheckBasicCmdName_004)
{
    // 参数定义
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // 参数初始化
    uchar = 'S';

    // 相关全局变量初始化


    // MOCKER操作;


    // 调用被测函数
    ulRst = atCheckBasicCmdName(uchar);

    // 执行检查
    EXPECT_EQ(ulRst,AT_SUCCESS);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:atCheckBasicCmdName_005          
*被测函数功能描述:检查指定字符是否属于basic 字符
*预期结果：是:返回 AT_SUCCESS    
           否:返回 AT_FAILURE
           
#  1.日    期: 2013年10月26日
#    作    者: z00189113
#    修改内容: 新建CASE
*******************************************************************/
TEST(atCheckBasicCmdName,atCheckBasicCmdName_005)
{
    // 参数定义
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // 参数初始化
    uchar = 'm';

    // 相关全局变量初始化


    // MOCKER操作;


    // 调用被测函数
    ulRst = atCheckBasicCmdName(uchar);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


#if 0

/*******************************************************************
*测试项:          检查MAC地址格式是否合法，正确格式XX:XX:XX:XX:XX:XX
*被测函数功能描述:检查MAC地址格式是否合法,存在不在'0'-'9'或'A'-'F'的字符
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_AT_CheckMacAddrFormat,检查MAC地址格式是否合法存在非法字符)
{
    // 参数定义
	VOS_UINT8                          *pucDateStr;
    VOS_UINT32                          ulDateStrLen;
	VOS_UINT8                           auData[30]="00:1E:10:12:FG:16";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucDateStr = auData;
	ulDateStrLen = AT_GNA_E5_MAC_ADDR_LEN;

    // 相关全局变量初始化


    // MOCKER操作;


	// 调用被测函数
    ulRst = AT_CheckMacAddrFormat(pucDateStr,ulDateStrLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          检查MAC地址格式是否合法，正确格式XX:XX:XX:XX:XX:XX
*被测函数功能描述:检查MAC地址格式是否合法,冒号个数不为5
*预期结果：       返回AT_FAILURE
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_AT_CheckMacAddrFormat,检查MAC地址格式是否合法冒号个数不为5)
{
    // 参数定义
	VOS_UINT8                          *pucDateStr;
    VOS_UINT32                          ulDateStrLen;
	VOS_UINT8                           auData[30]="01";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucDateStr = auData;
	ulDateStrLen = strlen((const char*)auData);

    // 相关全局变量初始化


    // MOCKER操作;


	// 调用被测函数
    ulRst = AT_CheckMacAddrFormat(pucDateStr,ulDateStrLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_FAILURE);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
*测试项:          检查MAC地址格式是否合法，正确格式XX:XX:XX:XX:XX:XX
*被测函数功能描述:检查MAC地址格式是否合法,冒号间字符不为2个，左补0，冒号为5个
*预期结果：       返回AT_SUCCESS
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_AT_CheckMacAddrFormat,检查MAC地址格式是否合法冒号间字符不为2个)
{
    // 参数定义
	VOS_UINT8                          *pucDateStr;
    VOS_UINT32                          ulDateStrLen;
	VOS_UINT8                           auData[30]="0:E:0:2:F:6";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucDateStr = auData;
	ulDateStrLen = strlen((const char*)auData);

    // 相关全局变量初始化


    // MOCKER操作;


	// 调用被测函数
    ulRst = AT_CheckMacAddrFormat(pucDateStr,ulDateStrLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_SUCCESS);
	EXPECT_EQ(strcmp((const char *)pucDateStr,"00:0E:00:02:0F:06"),0);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          检查MAC地址格式是否合法，正确格式XX:XX:XX:XX:XX:XX
*被测函数功能描述:检查MAC地址格式是否合法,格式合法
*预期结果：       返回AT_SUCCESS
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_AT_CheckMacAddrFormat,检查MAC地址格式是否合法格式合法)
{
    // 参数定义
	VOS_UINT8                          *pucDateStr;
    VOS_UINT32                          ulDateStrLen;
	VOS_UINT8                           auData[30]="01:EF:ac:52:Bb:96";
	VOS_UINT32                          ulRst;

    // 参数初始化
    pucDateStr = auData;
	ulDateStrLen = strlen((const char*)auData);

    // 相关全局变量初始化


    // MOCKER操作;


	// 调用被测函数
    ulRst = AT_CheckMacAddrFormat(pucDateStr,ulDateStrLen);

    // 执行检查
    EXPECT_EQ(ulRst,AT_SUCCESS);
	EXPECT_EQ(strcmp((const char *)pucDateStr,"01:EF:ac:52:Bb:96"),0);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



#endif