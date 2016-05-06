#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtTestParaCmd.h"


#define    THIS_FILE_ID                 PS_FILE_ID_AT_TESTPARACMD_C

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


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
类名     : Test_AT_SetWifiPaRangePara
功能描述 : Test_AT_SetWifiPaRangePara UT工程类
修改历史     :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_TestCgpaddr: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;

    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};


/*******************************************************************
测试用例编号      : Test_At_TestCgpaddr_002
测试用例标题      : 发送消息成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_TestCgpaddr, Test_At_TestCgpaddr_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gucAtParaIndex                  = 1;
    gastAtParaList[0].usParaLen     = 2;

    /* 桩函数 */
    MOCKER(TAF_PS_SndMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));


    /* 调用消息入口函数 */
    ulRst = At_TestCgpaddr(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
/*******************************************************************
测试用例编号      : Test_At_TestCgpaddr_003
测试用例标题      : 发送消息成功
预期结果          : 返回AT_ERROR
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_TestCgpaddr, Test_At_TestCgpaddr_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gucAtParaIndex                  = 1;
    gastAtParaList[0].usParaLen     = 2;

    /* 桩函数 */
    MOCKER(TAF_PS_SndMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));


    /* 调用消息入口函数 */
    ulRst = At_TestCgpaddr(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_AT_TestCposrPara
功能描述 : AT_TestCposrPara UT工程类
修改历史 :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*****************************************************************************/
class Test_AT_TestCposrPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_MODEM_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_CPOSR;
        stCmdInfo.pfnSetProc        = AT_SetCposrPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryCposrPara;
        stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestCposrPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"+CPOSR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1)";

        PS_MEM_SET(g_stParseContext, 0, sizeof(AT_PARSE_CONTEXT_STRU)*AT_MAX_CLIENT_NUM);

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }

    void TearDown()
    {
    }

    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};

/*******************************************************************
测试用例编号      : Test_AT_TestCposrPara_001
测试用例标题      : 命令从HSIC4通道下发，
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_TestCposrPara, Test_AT_TestCposrPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_TestCposrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("+CPOSR: (0,1)"));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestCposrPara_002
测试用例标题      : 命令从非HSIC通道下发，
预期结果          : 返回AT_ERROR
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_TestCposrPara, Test_AT_TestCposrPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_TestCposrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/******************************************************************************
类名       : Test_AT_TestCbgPara
功能描述  : AT_TestCbgPara UT工程类
修改历史  :
 1.日   期   : 2012-01-05
   作   者   : z00214637
   修改内容 : DSDA GUNAS C CORE Project 项目新增类
******************************************************************************/
class Test_AT_TestCbgPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_CBG;
        stCmdInfo.pfnSetProc        = AT_SetCbgPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = AT_QryCbgPara;
        stCmdInfo.ulQryTimeOut      = AT_QRY_PARA_TIME;
        stCmdInfo.pfnTestProc       = AT_TestCbgPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CBG";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(0,1)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {

    }

    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
};

/******************************************************************************
测试用例编号: Test_AT_TestCbgPara_001
测试用例标题: 从VCOM0下发AT^CBG测试命令
预期结果    : 返回AT_OK
修改历史    :
 1.日   期  : 2012-01-05
   作   者  : z00214637
   修改内容 : DSDA GUNAS C CORE Project 项目新增
******************************************************************************/
TEST_F(Test_AT_TestCbgPara, Test_AT_TestCbgPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pStr = "^CBG: (0,1)";

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestCbgPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    ASSERT_STREQ(pStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^CBG: (0,1)"));

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_TestCnmaPara
功能描述 : AT_TestCnmaPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestCnmaPara: public ::testing::Test
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
测试用例编号      : Test_AT_TestCnmaPara_001
测试用例标题      : Modem0 CNMA命令的测试命令，消息格式为PDU
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestCnmaPara,Test_AT_TestCnmaPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CNMA: (0-2)";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;

    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CNMA,
                                                        At_SetCnmaPara, AT_SMS_SET_PARA_TIME,
                                                        AT_TestCnmaPara, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CNMA",  TAF_NULL_PTR, (TAF_UINT8*)"(0-2),(0-65535)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestCnmaPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_AT_TestCnmaPara_002
测试用例标题      : Modem1 CNMA命令的测试命令，消息格式为PDU
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestCnmaPara,Test_AT_TestCnmaPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CNMA: (0-2)";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;

    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CNMA,
                                                        At_SetCnmaPara, AT_SMS_SET_PARA_TIME,
                                                        AT_TestCnmaPara, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CNMA",  TAF_NULL_PTR, (TAF_UINT8*)"(0-2),(0-65535)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestCnmaPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_AT_TestCpmsPara
功能描述 : AT_TestCpmsPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestCpmsPara: public ::testing::Test
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
测试用例编号      : Test_AT_TestCpmsPara_001
测试用例标题      : Modem0 CPMS命令的测试命令，ME存储状态标志为MN_MSG_ME_STORAGE_ENABLE
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestCpmsPara,Test_AT_TestCpmsPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: (\"SM\"),(\"SM\"),(\"SM\")";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        AT_TestCpmsPara,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enMsgMeStorageStatus   = MN_MSG_ME_STORAGE_DISABLE;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestCpmsPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_AT_TestCpmsPara_002
测试用例标题      : Modem1 CPMS命令的测试命令，ME存储状态标志为MN_MSG_ME_STORAGE_ENABLE
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestCpmsPara,Test_AT_TestCpmsPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: (\"SM\"),(\"SM\"),(\"SM\")";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
        At_SetCpmsPara,     AT_SET_PARA_TIME,
        At_QryCpmsPara,     AT_QRY_PARA_TIME,
        AT_TestCpmsPara,    AT_NOT_SET_TIME,
        VOS_NULL_PTR,       AT_NOT_SET_TIME,
        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enMsgMeStorageStatus   = MN_MSG_ME_STORAGE_DISABLE;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestCpmsPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
#if 0
/*****************************************************************************
类名     : Test_AT_TestMemStatusPara
功能描述 : AT_TestMemStatusPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestMemStatusPara: public ::testing::Test
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
测试用例编号      : Test_AT_TestMemStatusPara_001
测试用例标题      : ^CSASM测试参数
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestMemStatusPara,Test_AT_TestMemStatusPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^CSASM: (0,1)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSASM,
                                                        AT_SetMemStatusPara,    AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                        AT_TestMemStatusPara,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                        (TAF_UINT8*)"^CSASM",  (TAF_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].UserType                           = AT_APP_USER;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestMemStatusPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
/*****************************************************************************
类名     : Test_AT_TestApRptPortSelectPara
功能描述 : AT_TestApRptPortSelectPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestApRptPortSelectPara: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        pucSystemAppConfig          = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig         = SYSTEM_APP_ANDROID;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestApRptPortSelectPara_001
测试用例标题      : ^APRPTPORTSEL测试参数
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestApRptPortSelectPara,Test_AT_TestApRptPortSelectPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_APP_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^APRPTPORTSEL: (0-FFFFFFFF), (0-FFFFFFFF)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_APRPTPORTSEL,
                                                        AT_SetApRptPortSelectPara,  AT_NOT_SET_TIME,
                                                        AT_QryApRptPortSelectPara,  AT_NOT_SET_TIME,
                                                        AT_TestApRptPortSelectPara, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^APRPTPORTSEL",    (VOS_UINT8*)"(0-FFFFFFFF), (0-FFFFFFFF)"};

    // 参数初始化

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].UserType                           = AT_APP_USER;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestApRptPortSelectPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_TestUsbSwitchPara
功能描述 : AT_TestUsbSwitchPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestUsbSwitchPara: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        pucSystemAppConfig  = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig = SYSTEM_APP_ANDROID;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestUsbSwitchPara_001
测试用例标题      : +USBSWITCH测试参数
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestUsbSwitchPara,Test_AT_TestUsbSwitchPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+USBSWITCH: (1,2)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_USBSWITCH,
                                                        At_SetUsbSwitchPara,    AT_NOT_SET_TIME,
                                                        At_QryUsbSwitchPara,    AT_NOT_SET_TIME,
                                                        AT_TestUsbSwitchPara,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"+USBSWITCH",    (VOS_UINT8*)"(1,2)"};

    // 参数初始化

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].UserType                           = AT_APP_USER;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestUsbSwitchPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_TestApSimStPara
功能描述 : AT_TestApSimStPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestApSimStPara: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        pucSystemAppConfig = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestApSimStPara_001
测试用例标题      : ^APSIMST测试参数
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestApSimStPara,Test_AT_TestApSimStPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^APSIMST: (0,1)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_APSIMST,
                                                        AT_SetApSimStPara,      AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                        AT_TestApSimStPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^APSIMST",    (VOS_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].UserType                           = AT_APP_USER;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestApSimStPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_TestCgdcont
功能描述 : At_TestCgdcont UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_TestCgdcont: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        pucSystemAppConfig = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_TestCgdcont_001
测试用例标题      : ^APSIMST测试参数
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年05月30日
    作    者: f00179208
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_TestCgdcont,Test_At_TestCgdcont_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT32                          ulRslt;

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGDCONT,
        AT_SetCgdcontPara, AT_SET_PARA_TIME, AT_QryCgdcontPara, AT_QRY_PARA_TIME, At_TestCgdcont, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"+CGDCONT",     (VOS_UINT8*)CGDCONT_CMD_PARA_STRING};

    // 参数初始化

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_TestCgdcont(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_TestCgdcont_002
测试用例标题      : +CGDCONT测试参数
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年07月30日
    作    者: Y00213812
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_TestCgdcont,Test_At_TestCgdcont_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT32                          ulRslt;

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGDCONT,
        AT_SetCgdcontPara, AT_SET_PARA_TIME, AT_QryCgdcontPara, AT_QRY_PARA_TIME, At_TestCgdcont, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"+CGDCONT",     (VOS_UINT8*)CGDCONT_CMD_PARA_STRING};

    // 参数初始化

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    AT_GetCommPsCtxAddr()->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_TestCgdcont(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_TestCgansExtPara
功能描述 : At_TestCgansExtPara UT工程类
修改历史     :
1.日   期  : 2013-06-08
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_TestCgansExtPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_TestCgansExtPara_001
测试用例标题      : ^CGANS测试参数
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年06月08日
    作    者: l60609
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_TestCgansExtPara,Test_At_TestCgansExtPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^CGANS: (0,1)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGANS_EXT,
        AT_SetCgansPara,    AT_SET_PARA_TIME, VOS_NULL_PTR,      AT_NOT_SET_TIME,   At_TestCgansExtPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"^CGANS",       (VOS_UINT8*)CGANS_EXT_CMD_PARA_STRING};

    // 参数初始化

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_TestCgansExtPara(ucIndex);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_TestRefclkfreqPara
功能描述 : AT_TestRefclkfreqPara UT工程类
修改历史 :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestRefclkfreqPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        stCmdInfo.ulCmdIndex        = AT_CMD_REFCLKFREQ;
        stCmdInfo.pfnSetProc        = AT_SetRefclkfreqPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = AT_QryRefclkfreqPara;
        stCmdInfo.ulTestTimeOut     = AT_QRY_PARA_TIME;
        stCmdInfo.pfnTestProc       = AT_TestRefclkfreqPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnAbortProc      = VOS_NULL_PTR;
        stCmdInfo.ulAbortTimeOut    = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_ERROR;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^REFCLKFREQ";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1)";

        AT_ResetClientTab();

        ucIndex         = AT_CLIENT_TAB_APP_INDEX;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        g_stAtCommCtx.ucSystemAppConfigAddr     = SYSTEM_APP_ANDROID;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestRefclkfreqPara_001
测试用例标题      : 通道错误
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestRefclkfreqPara, Test_AT_TestRefclkfreqPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex         = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_TestRefclkfreqPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestRefclkfreqPara_002
测试用例标题      : 通道正确
预期结果          : 返回AT_OK，打印测试命令结果
修改历史          :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestRefclkfreqPara, Test_AT_TestRefclkfreqPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpectStr = VOS_NULL_PTR;

    // 参数初始化
    pcExpectStr     = "^REFCLKFREQ: (0,1)";

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_TestRefclkfreqPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_STREQ((VOS_CHAR*)pgucAtSndCodeAddr, pcExpectStr);

    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_At_TestCgeqos
功能描述 : At_TestCgeqos UT工程类
修改历史 :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_At_TestCgeqos: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
测试用例编号: Test_At_TestCgeqos_001
测试用例标题: +CGEQOS测试命令
预期结果    :
修改历史    :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_At_TestCgeqos, Test_At_TestCgeqos_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGEQOS: (1-31),(0-9),(0-262144),(0-262144),(0-262144),(0-262144)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGEQOS,
    atSetCgeqosPara, AT_SET_PARA_TIME, atQryCgeqosPara,   AT_QRY_PARA_TIME,  At_TestCgeqos,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGEQOS",    (VOS_UINT8*)"(1-31),(0-9),(0-262144),(0-262144),(0-262144),(0-262144)"};

    // 参数初始化

    // 初始化全局变量
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_TestCgeqos(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_At_TestCgeqosrdp
功能描述 : At_TestCgeqosrdp UT工程类
修改历史 :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_At_TestCgeqosrdp: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
测试用例编号: Test_At_TestCgeqosrdp_001
测试用例标题: +CGEQOSRDP测试命令
预期结果    :
修改历史    :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_At_TestCgeqosrdp, Test_At_TestCgeqosrdp_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGEQOSRDP: (1-31)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGEQOSRDP,
    atSetCgeqosrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgeqosrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGEQOSRDP",    (VOS_UINT8*)"(1-31)"};

    // 参数初始化

    // 初始化全局变量
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_TestCgeqosrdp(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_At_TestCgcontrdp
功能描述 : At_TestCgcontrdp UT工程类
修改历史 :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_At_TestCgcontrdp: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
测试用例编号: Test_At_TestCgcontrdp_001
测试用例标题: +CGCONTRDP测试命令
预期结果    :
修改历史    :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_At_TestCgcontrdp, Test_At_TestCgcontrdp_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGCONTRDP: (1-31)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGCONTRDP,
    atSetCgcontrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgcontrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGCONTRDP",    (VOS_UINT8*)"(1-31)"};

    // 参数初始化

    // 初始化全局变量
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_TestCgcontrdp(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_At_TestCgscontrdp
功能描述 : At_TestCgscontrdp UT工程类
修改历史 :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_At_TestCgscontrdp: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
测试用例编号: Test_At_TestCgscontrdp_001
测试用例标题: +CGSCONTRDP测试命令
预期结果    :
修改历史    :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_At_TestCgscontrdp, Test_At_TestCgscontrdp_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGSCONTRDP: (1-31)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGSCONTRDP,
    atSetCgscontrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgscontrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGSCONTRDP",    (VOS_UINT8*)"(1-31)"};

    // 参数初始化

    // 初始化全局变量
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_TestCgscontrdp(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_At_TestCgtftrdp
功能描述 : At_TestCgtftrdp UT工程类
修改历史 :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_At_TestCgtftrdp: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
测试用例编号: Test_At_TestCgtftrdp_001
测试用例标题: +CGTFTRDP测试命令
预期结果    :
修改历史    :
 1.日   期  : 2013-08-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_At_TestCgtftrdp, Test_At_TestCgtftrdp_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGTFTRDP: (1-31)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGTFTRDP,
    atSetCgtftrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,    AT_NOT_SET_TIME,  At_TestCgtftrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGTFTRDP",    (VOS_UINT8*)"(1-31)"};

    // 参数初始化

    // 初始化全局变量
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_TestCgtftrdp(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IMS)
/******************************************************************************
类名     : Test_AT_TestCiregPara
功能描述 : AT_TestCiregPara UT工程类
修改历史 :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_AT_TestCiregPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
测试用例编号: Test_AT_TestCiregPara_001
测试用例标题: +CIREG测试命令
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_AT_TestCiregPara, Test_AT_TestCiregPara_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CIREG: (0-2)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CIREG,
        AT_SetCiregPara,     AT_SET_PARA_TIME,   AT_QryCiregPara,       AT_QRY_PARA_TIME,   AT_TestCiregPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
        (VOS_UINT8 *)"+CIREG",   (VOS_UINT8 *)"(0-2)"};

    // 参数初始化

    // 初始化全局变量
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestCiregPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_TestCirepPara
功能描述 : AT_TestCirepPara UT工程类
修改历史 :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_AT_TestCirepPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
测试用例编号: Test_AT_TestCirepPara_001
测试用例标题: +CIREP测试命令
预期结果    :返回AT_OK
修改历史    :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_AT_TestCirepPara, Test_AT_TestCirepPara_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CIREP: (0,1)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CIREP,
        AT_SetCirepPara,     AT_SET_PARA_TIME,   AT_QryCirepPara,       AT_QRY_PARA_TIME,   AT_TestCirepPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
        (VOS_UINT8 *)"+CIREP",   (VOS_UINT8 *)"(0,1)"};

    // 参数初始化

    // 初始化全局变量
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_TestCirepPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

#endif
