#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtMntn.h"


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


/******************************************************************************
类名     : Test_AT_MNTN_TraceCmdResult
功能描述 : AT_MNTN_TraceCmdResult UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_AT_MNTN_TraceCmdResult: public ::testing::Test
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
*测试项:             申请内存失败函数直接返回
*被测函数功能描述:   将AT命令回复显示在SDT LOG中
*预期结果：          WARNING告警"At_HookResult:ERROR:Alloc Mem Fail."
************************* 修改记录 *************************
#  1.日    期: 2011年4月22日
#    作    者: f62575
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_MNTN_TraceCmdResult, Test_AT_MNTN_TraceCmdResult_01)
{
    const char          cWarning[] = "At_HookResult:ERROR:Alloc Mem Fail.";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;

    //MOCKER(DIAG_LogReport)
    //    .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    MOCKER(DIAG_TraceReport)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:             钩包成功
*被测函数功能描述:   将AT命令回复显示在SDT LOG中
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2011年4月22日
#    作    者: f62575
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_MNTN_TraceCmdResult, Test_AT_MNTN_TraceCmdResult_02)
{
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;

    MOCKER(DIAG_TraceReport)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_MNTN_TraceCmdBuffer
功能描述 : AT_MNTN_TraceCmdBuffer UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_AT_MNTN_TraceCmdBuffer: public ::testing::Test
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
*测试项:             申请内存失败函数直接返回
*被测函数功能描述:   将缓存命令处理以消息方式显示
*预期结果：          WARNING告警"AT_MNTN_TraceCmdBuffer:ERROR:Alloc Mem Fail."
************************* 修改记录 *************************
#  1.日    期: 2011年4月22日
#    作    者: f62575
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_MNTN_TraceCmdBuffer, Test_AT_MNTN_TraceCmdBuffer_01)
{
    const char          cWarning[] = "AT_MNTN_TraceCmdBuffer:ERROR:Alloc Mem Fail.";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    MOCKER(DIAG_TraceReport)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    AT_MNTN_TraceCmdBuffer(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:             钩包成功
*被测函数功能描述:   将缓存命令处理以消息方式显示
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2011年4月22日
#    作    者: f62575
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_MNTN_TraceCmdBuffer, Test_AT_MNTN_TraceCmdBuffer_02)
{
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;

    MOCKER(DIAG_TraceReport)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    AT_MNTN_TraceCmdBuffer(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_AT_ShowResetStatsInfo
 功能描述   : AT_ShowResetStatsInfo UT工程类
 修改历史   :
 1.日   期  : 2013-04-25
   作   者  : f00179208
   修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ShowResetStatsInfo: public ::testing::Test
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
 测试用例编号   : Test_AT_ShowResetStatsInfo_001
 测试用例标题   : 无
 预期结果       : 无
 修改历史       :
 1.日   期  : 2013-04-25
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ShowResetStatsInfo, Test_AT_ShowResetStatsInfo_001)
{
    //参数定义

    //参数初始化

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_ShowResetStatsInfo();

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_Help
功能描述 : Test_AT_Help UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : A00165503
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_Help: public ::testing::Test
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
测试用例编号    : Test_AT_Help_001
测试用例标题    : AT软调帮助
预期结果        : 直接返回
修改历史        :
1.日   期  : 2013-11-15
  作   者  : A00165503
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_Help, Test_AT_Help_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_Help();

    // 执行检查

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ShowPsEntityInfo
功能描述 : Test_AT_ShowPsEntityInfo UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : A00165503
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ShowPsEntityInfo: public ::testing::Test
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
测试用例编号    : Test_AT_ShowPsEntityInfo_001
测试用例标题    : PS域实体信息
预期结果        : 直接返回
修改历史        :
1.日   期  : 2013-11-15
  作   者  : A00165503
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_ShowPsEntityInfo, Test_AT_ShowPsEntityInfo_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_ShowPsEntityInfo(0);

    // 执行检查

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_InitHsUartStats
功能描述 : AT_InitHsUartStats UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitHsUartStats: public ::testing::Test
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
测试用例编号      : Test_AT_InitHsUartStats_001
测试用例标题      :
预期结果          :
修改历史          :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitHsUartStats, Test_AT_InitHsUartStats_001)
{
    g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum = 1;
    AT_InitHsUartStats();

    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ShowHsUartNvStats
功能描述 : AT_ShowHsUartNvStats UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ShowHsUartNvStats: public ::testing::Test
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
测试用例编号      : Test_AT_ShowHsUartNvStats_001
测试用例标题      : UART NV可维可测信息
预期结果          : NA
修改历史          :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ShowHsUartNvStats, Test_AT_ShowHsUartNvStats_001)
{
    AT_ShowHsUartNvStats();

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ShowHsUartIoctlStats
功能描述 : AT_ShowHsUartIoctlStats UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ShowHsUartIoctlStats: public ::testing::Test
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
测试用例编号      : Test_AT_ShowHsUartIoctlStats_001
测试用例标题      : UART IOCTL操作结果
预期结果          : NA
修改历史          :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ShowHsUartIoctlStats, Test_AT_ShowHsUartIoctlStats_001)
{
    AT_ShowHsUartIoctlStats();
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ShowHsUartDataStats
功能描述 : AT_ShowHsUartDataStats UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ShowHsUartDataStats: public ::testing::Test
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
测试用例编号      : Test_AT_ShowHsUartDataStats_001
测试用例标题      : UART Data 可维可测
预期结果          : NA
修改历史          :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ShowHsUartDataStats, Test_AT_ShowHsUartDataStats_001)
{
    AT_ShowHsUartDataStats();

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ShowUartConfigInfo
功能描述 : Test_AT_ShowUartConfigInfo UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : A00165503
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ShowHsUartConfigInfo: public ::testing::Test
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
测试用例编号    : Test_AT_ShowHsUartConfigInfo_001
测试用例标题    : UART配置可维可测信息
预期结果        : 直接返回
修改历史        :
1.日   期  : 2013-11-15
  作   者  : A00165503
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_ShowHsUartConfigInfo, Test_AT_ShowHsUartConfigInfo_001)
{
    // 变量声明
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    AT_UART_FLOW_CTRL_STRU             *pstFlowCtrl = VOS_NULL_PTR;
    AT_UART_RI_CFG_STRU                *pstUartRiCfgInfo = VOS_NULL_PTR;
    AT_UART_PHY_CFG_STRU               *pstUartPhyCfgInfo = VOS_NULL_PTR;
    AT_UART_FORMAT_PARAM_STRU          *pstFormatParam = VOS_NULL_PTR;

    // 参数初始化
    pstLineCtrl       = AT_GetUartLineCtrlInfo();
    memset(pstLineCtrl, 0, sizeof(AT_UART_LINE_CTRL_STRU));
    pstFlowCtrl       = AT_GetUartFlowCtrlInfo();
    memset(pstFlowCtrl, 0, sizeof(AT_UART_FLOW_CTRL_STRU));
    pstUartRiCfgInfo  = AT_GetUartRiCfgInfo();
    memset(pstUartRiCfgInfo, 0, sizeof(AT_UART_RI_CFG_STRU));
    pstUartPhyCfgInfo = AT_GetUartPhyCfgInfo();
    memset(pstUartPhyCfgInfo, 0, sizeof(AT_UART_PHY_CFG_STRU));
    pstFormatParam    = AT_HSUART_GetFormatParam(pstUartPhyCfgInfo->stFrame.enFormat);
    memset(pstFormatParam, 0, sizeof(AT_UART_FORMAT_PARAM_STRU));

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_ShowHsUartConfigInfo();

    // 执行检查

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_InitModemStats
功能描述 : Test_AT_InitModemStats UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : A00165503
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitModemStats: public ::testing::Test
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
测试用例编号    : Test_AT_InitModemStats_001
测试用例标题    : MODEM统计信息初始化
预期结果        : 直接返回
修改历史        :
1.日   期  : 2013-11-15
  作   者  : A00165503
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_InitModemStats, Test_AT_InitModemStats_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_InitModemStats();

    // 执行检查

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ShowModemDataStats
功能描述 : Test_AT_ShowModemDataStats UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : A00165503
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ShowModemDataStats: public ::testing::Test
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
测试用例编号    : Test_AT_ShowModemDataStats_001
测试用例标题    : MODEM软调帮助
预期结果        : 直接返回
修改历史        :
1.日   期  : 2013-11-15
  作   者  : A00165503
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_ShowModemDataStats, Test_AT_ShowModemDataStats_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_ShowModemDataStats();

    // 执行检查

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_MNTN_TraceEvent
功能描述 : Test_AT_MNTN_TraceEvent UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : A00165503
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_MNTN_TraceEvent: public ::testing::Test
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
测试用例编号    : Test_AT_MNTN_TraceEvent_001
测试用例标题    : 钩包失败
预期结果        : 直接返回
修改历史        :
1.日   期  : 2013-11-15
  作   者  : A00165503
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_MNTN_TraceEvent, Test_AT_MNTN_TraceEvent_001)
{
    // 变量声明
    AT_MNTN_MSC_STRU                    stMntnMsc;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(DIAG_TraceReport)
        .stubs()
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_MNTN_TraceEvent(&stMntnMsc);

    // 执行检查

    GlobalMockObject::verify();
}

