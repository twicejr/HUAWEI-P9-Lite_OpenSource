#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtExtendCmd.h"

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
/*****************************************************************************
类名     : Test_At_TestCpolPara
功能描述 : CPOL测试命令的UT测试类
修改历史 :
1.日   期  : 2011-10-27
作   者  : c00173809
修改内容 : 新生成类
*****************************************************************************/
class Test_At_TestCpolPara: public ::testing::Test
{
public:
    VOS_UINT8       ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    VOS_UINT8                           szCmdName[32];

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                       = 0;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"+cpol");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;

        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[0].ulParaValue = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucSalsType                 = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
        AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucRoamFeature              = AT_ROAM_FEATURE_OFF;
    }

    void TearDown()
    {
        ucIndex                       = 0;
        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[0].ulParaValue = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucSalsType                 = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
        AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucRoamFeature              = AT_ROAM_FEATURE_OFF;
    }
};
/*******************************************************************
测试用例编号      : Test_At_TestCpolPara_001
测试用例标题      : 发送消息失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_TestCpolPara,Test_At_TestCpolPara_001)
{
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_FAILURE));

    EXPECT_EQ(AT_ERROR, At_TestCpolPara(ucIndex));

    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_At_TestCpolPara_002
测试用例标题      : 发送消息成功
预期结果          : 返回等待异步消息
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_TestCpolPara,Test_At_TestCpolPara_002)
{
    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_SUCCESS));

    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, At_TestCpolPara(ucIndex));

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_TestCgeqnegPara
功能描述 : At_TestCgeqnegPara UT工程类
修改历史     :
1.日   期  : 2011-12-17
作   者  :   l00130025
修改内容 : 新生成类
*****************************************************************************/
class Test_At_TestCgeqnegPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        gastAtClientTab[0].CmdCurrentOpt = AT_CMD_INVALID;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_TestCgeqnegPara_001
测试用例标题      : 发送获取PDP状态成功和启动定时器成功，返回
预期结果          : AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期         : 2011-12-17
  作   者         : l00130025
  修改内容        : DTS2011120604361,CGEQNEG错误
*******************************************************************/
TEST_F(Test_At_TestCgeqnegPara,Test_At_TestCgeqnegPara_001)
{
    // 变量声明

    //参数初始化

    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_INVALID;


    // MOCKER操作;
    MOCKER(TAF_PS_GetPdpContextState)
           .stubs()
           .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_StartTimer)
           .stubs()
           .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    At_TestCgeqnegPara(0);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGEQNEG_TEST, gastAtClientTab[0].CmdCurrentOpt);

    GlobalMockObject::verify();
}

