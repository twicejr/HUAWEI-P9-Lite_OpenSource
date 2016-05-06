#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCmdFtmProc.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_AT_CMD_FTM_PROC_C


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

AT_PAR_CMD_ELEMENT_STRU             gstLogPortCmdInfo = {AT_CMD_LOGPORT,
                                                        At_SetLogPortPara,       AT_NOT_SET_TIME,  At_QryLogPortPara,   AT_NOT_SET_TIME,    At_CmdTestProcOK,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^LOGPORT",  VOS_NULL_PTR};

/*****************************************************************************
类名     : Test_At_SetLogPortPara
功能描述 : At_SetLogPortPara UT工程类
修改历史     :
1.日   期  : 2013-06-20
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_SetLogPortPara: public ::testing::Test
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
测试用例编号      : Test_At_SetLogPortPara_001
测试用例标题      : 命令类型不为设置命令
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2013-06-20
  作   者  : L60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*本地变量初始化*/
    ucIndex = AT_CLIENT_ID_APP1;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = At_SetLogPortPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetLogPortPara_002
测试用例标题      : 参数个数不为1
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2013-06-20
  作   者  : L60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*本地变量初始化*/
    ucIndex = AT_CLIENT_ID_APP1;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 0;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = At_SetLogPortPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetLogPortPara_003
测试用例标题      : 切换USB口成功
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2013-06-20
  作   者  : L60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*本地变量初始化*/
    ucIndex = AT_CLIENT_ID_APP1;
    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].ulParaValue = 0;

    /*函数打桩*/
    MOCKER(PPM_LogPortSwitch)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*调用被测函数 */
    ulRet = At_SetLogPortPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_At_SetLogPortPara_004
测试用例标题      : 切换USB口成功
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2013-06-20
  作   者  : L60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_004)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*本地变量初始化*/
    ucIndex = AT_CLIENT_ID_APP1;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].ulParaValue = 1;

    /*函数打桩*/
    MOCKER(PPM_LogPortSwitch)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*调用被测函数 */
    ulRet = At_SetLogPortPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetLogPortPara_005
测试用例标题      : 切换USB口失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2013-06-20
  作   者  : L60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_005)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*本地变量初始化*/
    ucIndex = AT_CLIENT_ID_APP1;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].ulParaValue = 0;

    /*函数打桩*/
    MOCKER(PPM_LogPortSwitch)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /*调用被测函数 */
    ulRet = At_SetLogPortPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryLogPortPara
功能描述 : At_QryLogPortPara UT工程类
修改历史     :
1.日   期  : 2013-06-20
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryLogPortPara: public ::testing::Test
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
测试用例编号      : Test_At_QryLogPortPara_001
测试用例标题      : 查询端口成功VCOM
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2013-06-20
  作   者  : L60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryLogPortPara,Test_At_QryLogPortPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulOmLogPort;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    pcExpactedStr   = "^LOGPORT: 0";
    ucIndex = AT_CLIENT_ID_APP1;
    g_stParseContext[ucIndex].pstCmdElement = &gstLogPortCmdInfo;
    ulOmLogPort = COMM_LOG_PORT_USB;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;

    /*函数打桩*/
    MOCKER(PPM_QueryLogPort)
        .expects(exactly(1))
        .with(outBoundP((VOS_UINT32 *)&ulOmLogPort, sizeof(ulOmLogPort)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*调用被测函数 */
    ulRet = At_QryLogPortPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryLogPortPara_002
测试用例标题      : 查询端口成功USB
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2013-06-20
  作   者  : L60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryLogPortPara,Test_At_QryLogPortPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulOmLogPort;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    pcExpactedStr   = "^LOGPORT: 1";
    ucIndex = AT_CLIENT_ID_APP1;
    g_stParseContext[ucIndex].pstCmdElement = &gstLogPortCmdInfo;
    ulOmLogPort = COMM_LOG_PORT_VCOM;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;

    /*函数打桩*/
    MOCKER(PPM_QueryLogPort)
        .stubs()
        .with(outBoundP((VOS_UINT32 *)&ulOmLogPort, sizeof(ulOmLogPort)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*调用被测函数 */
    ulRet = At_QryLogPortPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryLogPortPara_003
测试用例标题      : 查询端口失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2013-06-20
  作   者  : L60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryLogPortPara,Test_At_QryLogPortPara_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    pcExpactedStr   = "^LOGPORT: 0";
    ucIndex = AT_CLIENT_ID_APP1;
    g_stParseContext[ucIndex].pstCmdElement = &gstLogPortCmdInfo;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;

    /*函数打桩*/
    MOCKER(PPM_QueryLogPort)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /*调用被测函数 */
    ulRet = At_QryLogPortPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_SetDpdtTestFlagPara
功能描述 : Test_At_SetDpdtTestFlagPara UT工程类
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_SetDpdtTestFlagPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_At_SetDpdtTestFlagPara_001
测试用例标题      : 参数非法
预期结果          : 函数给用户回复AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetDpdtTestFlagPara, Test_At_SetDpdtTestFlagPara_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    gucAtParaIndex                = 3;

    /* 函数打桩 */

    /* 调用被测函数 */
    ulRst = At_SetDpdtTestFlagPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetDpdtTestFlagPara_002
测试用例标题      : 发送消息失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetDpdtTestFlagPara, Test_At_SetDpdtTestFlagPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU   stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 2;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].ulParaValue = 1;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucFlag    = gastAtParaList[1].ulParaValue;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_DPDTTEST_FLAG_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_SetDpdtTestFlagPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetDpdtTestFlagPara_003
测试用例标题      : 发送消息成功
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetDpdtTestFlagPara, Test_At_SetDpdtTestFlagPara_003)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU   stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 2;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].ulParaValue = 1;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucFlag    = gastAtParaList[1].ulParaValue;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_DPDTTEST_FLAG_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_SetDpdtTestFlagPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_SetDpdtPara
功能描述 : Test_At_SetDpdtPara UT工程类
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_SetDpdtPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_At_SetDpdtPara_001
测试用例标题      : 参数非法
预期结果          : 函数给用户回复AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetDpdtPara, Test_At_SetDpdtPara_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    gucAtParaIndex                = 3;

    /* 函数打桩 */

    /* 调用被测函数 */
    ulRst = At_SetDpdtPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetDpdtPara_002
测试用例标题      : 发送消息失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetDpdtPara, Test_At_SetDpdtPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_DPDT_VALUE_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 2;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 1;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode   = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ulDpdtValue = gastAtParaList[1].ulParaValue;


    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_DPDT_VALUE_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_SetDpdtPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetDpdtPara_003
测试用例标题      : 发送消息成功
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetDpdtPara, Test_At_SetDpdtPara_003)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_DPDT_VALUE_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 2;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 1;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode   = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ulDpdtValue = gastAtParaList[1].ulParaValue;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_DPDT_VALUE_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_SetDpdtPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_SetQryDpdtPara
功能描述 : Test_At_SetQryDpdtPara UT工程类
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_SetQryDpdtPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_At_SetQryDpdtPara_001
测试用例标题      : 参数非法
预期结果          : 函数给用户回复AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetQryDpdtPara, Test_At_SetQryDpdtPara_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    gucAtParaIndex                = 2;

    /* 函数打桩 */

    /* 调用被测函数 */
    ulRst = At_SetQryDpdtPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetQryDpdtPara_002
测试用例标题      : 发送消息失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetQryDpdtPara, Test_At_SetQryDpdtPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 1;
    gastAtParaList[0].ulParaValue = 0;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_QRY_DPDT_VALUE_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_SetQryDpdtPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetQryDpdtPara_003
测试用例标题      : 发送消息成功
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetQryDpdtPara, Test_At_SetQryDpdtPara_003)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 1;
    gastAtParaList[0].ulParaValue = 2;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_QRY_DPDT_VALUE_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_SetQryDpdtPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_RcvMtaSetDpdtTestFlagCnf
功能描述 : Test_AT_RcvMtaSetDpdtTestFlagCnf UT工程类
修改历史 :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*****************************************************************************/
class Test_AT_RcvMtaSetDpdtTestFlagCnf: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU   *pstSetCnf;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));
        
        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 生成输入消息 */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstSetCnf = (MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstSetCnf, 0, sizeof(MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtTestFlagCnf_001
测试用例标题  : 通过clientid获取index失败
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtTestFlagCnf_002
测试用例标题  : ucIndex为AT_BROADCAST_CLIENT_INDEX_MODEM_0
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucIndexTemp;

    /* 变量初始化 */
    usClientId  = 0;
    ucIndexTemp = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndexTemp, sizeof(ucIndexTemp)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtTestFlagCnf_003
测试用例标题  : AT不处于等待命令返回
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_003)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtTestFlagCnf_004
测试用例标题  : AT命令执行失败
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_004)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTTEST_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();
    
    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(0,gstAtSendData.usBufLen);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtTestFlagCnf_005
测试用例标题  : AT命令执行成功
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_005)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_NO_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTTEST_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_RcvMtaSetDpdtValueCnf
功能描述 : Test_AT_RcvMtaSetDpdtValueCnf UT工程类
修改历史 :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*****************************************************************************/
class Test_AT_RcvMtaSetDpdtValueCnf: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_SET_DPDT_VALUE_CNF_STRU      *pstSetCnf;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 生成输入消息 */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_SET_DPDT_VALUE_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstSetCnf = (MTA_AT_SET_DPDT_VALUE_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstSetCnf, 0, sizeof(MTA_AT_SET_DPDT_VALUE_CNF_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtValueCnf_001
测试用例标题  : 通过clientid获取index失败
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtValueCnf_002
测试用例标题  : ucIndex为AT_BROADCAST_CLIENT_INDEX_MODEM_0
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucIndexTemp;

    /* 变量初始化 */
    usClientId  = 0;
    ucIndexTemp = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndexTemp))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtValueCnf_003
测试用例标题  : AT不处于等待命令返回
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_003)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtValueCnf_004
测试用例标题  : AT命令执行失败
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_004)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDT_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(0,gstAtSendData.usBufLen);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetDpdtValueCnf_005
测试用例标题  : AT命令执行成功
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_005)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_NO_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDT_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // 调用被测函数
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_RcvMtaQryDpdtValueCnf
功能描述 : Test_AT_RcvMtaQryDpdtValueCnf UT工程类
修改历史 :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*****************************************************************************/
class Test_AT_RcvMtaQryDpdtValueCnf: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      *pstQryCnf;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));
    
        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 生成输入消息 */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstQryCnf = (MTA_AT_QRY_DPDT_VALUE_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstQryCnf, 0, sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaQryDpdtValueCnf_001
测试用例标题  : 通过clientid获取index失败
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaQryDpdtValueCnf_002
测试用例标题  : ucIndex为AT_BROADCAST_CLIENT_INDEX_MODEM_0
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucIndexTemp;

    /* 变量初始化 */
    usClientId  = 0;
    ucIndexTemp = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndexTemp))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaQryDpdtValueCnf_003
测试用例标题  : AT不处于等待命令返回
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_003)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaQryDpdtValueCnf_004
测试用例标题  : AT命令执行失败
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_004)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;
    pstQryCnf->enResult = MTA_AT_RESULT_ERROR;
    pstQryCnf->ulDpdtValue = 0x100;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTQRY_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // 调用被测函数
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(0,gstAtSendData.usBufLen);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaQryDpdtValueCnf_005
测试用例标题  : AT命令执行成功
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_005)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    char                                acExpectedResult[] = "^DPDTQRY: 256";

    /* 变量初始化 */
    usClientId = 0;
    pstQryCnf->enResult = MTA_AT_RESULT_NO_ERROR;
    pstQryCnf->ulDpdtValue = 0x100;


    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTQRY_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // 调用被测函数
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_At_SetJamDetectPara
 功能描述   : At_SetJamDetectPara UT工程类
 修改历史   :
 1.日   期  : 2014-5-14
   作   者  : g00261581
   修改内容 : 新生成类
*****************************************************************************/
class Test_At_SetJamDetectPara: public ::testing::Test
{
public:
    TAF_UINT8                           ucIndex;

    void SetUp()
    {
		UT_STUB_INIT();

        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_At_SetJamDetectPara_001
测试用例标题      : 参数非法
预期结果          : 函数给用户回复AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    gucAtParaIndex                = 5;

    /* 函数打桩 */

    /* 调用被测函数 */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //检查调用时，需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetJamDetectPara_002
测试用例标题      : 发送消息失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 1;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 1;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucFreqNum   = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    /* 函数打桩 */
	MOCKER(NV_ReadEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(NV_WriteEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_JAM_DETECT_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetJamDetectPara_003
测试用例标题      : 发送消息成功
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_003)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 1;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 1;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucFreqNum   = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    /* 函数打桩 */
	MOCKER(NV_ReadEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(NV_WriteEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(AT_FillAndSndAppReqMsg)
		.expects(exactly(1))
		.with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_JAM_DETECT_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
		.will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //检查调用时，需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetJamDetectPara_004
测试用例标题      : AT命令下发的参数不全，不全的参数按照默认值补齐
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_004)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 0;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 0;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = AT_JAM_DETECT_DEFAULT_THRESHOLD;
    stAtCmd.ucFreqNum   = AT_JAM_DETECT_DEFAULT_FREQ_NUM;

    /* 函数打桩 */
	MOCKER(NV_ReadEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(NV_WriteEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(AT_FillAndSndAppReqMsg)
		.expects(exactly(1))
		.with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_JAM_DETECT_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
		.will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //检查调用时，需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetJamDetectPara_005
测试用例标题      : 本地写NV失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_005)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 1;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 1;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucFreqNum   = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    /* 函数打桩 */
	MOCKER(NV_ReadEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(0));

    /* 调用被测函数 */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_SetJamDetectPara_006
测试用例标题      : 本地读NV失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2014-04-11
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_006)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* 变量初始化 */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 1;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 1;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucFreqNum   = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    /* 函数打桩 */
    MOCKER(NV_ReadEx)
		.stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(0));

    /* 调用被测函数 */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_At_QryJamDetectPara
 功能描述   : At_QryJamDetectPara UT工程类
 修改历史   :
 1.日   期  : 2014-5-14
   作   者  : g00261581
   修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryJamDetectPara: public ::testing::Test
{
public:
    TAF_UINT8                           ucIndex;

    void SetUp()
    {
		UT_STUB_INIT();

        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_At_QryJamDetectPara_001
测试用例标题      : 读取NV失败
预期结果          : 函数给用户回复AT_ERROR
修改历史     :
1.日   期  : 2014-05-14
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryJamDetectPara, Test_At_QryJamDetectPara_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */

    /* 函数打桩 */

    /* 调用被测函数 */
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    ulRst = At_QryJamDetectPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryJamDetectPara_002
测试用例标题      : 查询Jam Detect设置参数成功,锁频模式设为G模
预期结果          : 上报查询结果
修改历史     :
1.日   期  : 2014-05-14
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryJamDetectPara, Test_At_QryJamDetectPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamDetect;
    char                                acExpectedResult[] = "^JDETEX: 1,2,20,100";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_JDETEX,
                                                        At_SetJamDetectPara,   AT_SET_PARA_TIME,
                                                        At_QryJamDetectPara,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
                                                        (VOS_UINT8*)"^JDETEX",  VOS_NULL_PTR};

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    /* 变量初始化 */
    PS_MEM_SET(&stNvJamDetect, 0x0, sizeof(stNvJamDetect));
    stNvJamDetect.ucMode       = 1;
    stNvJamDetect.ucMethod     = 2;
    stNvJamDetect.ucThreshold  = 20;
    stNvJamDetect.ucFreqNum    = 100;

    /* 函数打桩 */

    /* 调用被测函数 */
    MOCKER(NV_ReadEx)
		.expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_JAM_DETECT_CFG), outBoundP((void *)&stNvJamDetect, (VOS_UINT32)sizeof(NV_NAS_JAM_DETECT_CFG_STRU)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRst = At_QryJamDetectPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_OK, ulRst);
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_RcvMtaSetJamDetectCnf
功能描述 : AT_RcvMtaSetJamDetectCnf UT工程类
修改历史 :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*****************************************************************************/
class Test_AT_RcvMtaSetJamDetectCnf: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_SET_JAM_DETECT_CNF_STRU      *pstSetCnf;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
		UT_STUB_INIT();

		MOCKER(V_StopRelTimer)
			.stubs()
			.will(returnValue((VOS_UINT32)VOS_OK));

        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 生成输入消息 */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_SET_JAM_DETECT_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstSetCnf = (MTA_AT_SET_JAM_DETECT_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstSetCnf, 0, sizeof(MTA_AT_SET_JAM_DETECT_CNF_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetJamDetectCnf_001
测试用例标题  : 通过clientid获取index失败
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量

    // MOCKER操作
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
		.will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetJamDetectCnf_002
测试用例标题  : ucIndex为AT_BROADCAST_CLIENT_INDEX_MODEM_0
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucIndexTemp;

    /* 变量初始化 */
    usClientId  = 0;
    ucIndexTemp = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // 初始化全局变量

    // MOCKER操作
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndexTemp))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetJamDetectCnf_003
测试用例标题  : AT不处于等待命令返回
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_003)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetJamDetectCnf_004
测试用例标题  : AT命令执行失败
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_004)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_JDETEX_SET;

    // MOCKER操作
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

	MOCKER(At_FormatResultData)
		.stubs();

    // 调用被测函数
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(0,gstAtSendData.usBufLen);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaSetJamDetectCnf_005
测试用例标题  : AT命令执行成功
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_005)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_NO_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_JDETEX_SET;

    // MOCKER操作
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

	MOCKER(At_FormatResultData)
		.stubs();

    // 调用被测函数
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
	GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_RcvMtaJamDetectInd
功能描述 : AT_RcvMtaJamDetectInd UT工程类
修改历史 :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*****************************************************************************/
class Test_AT_RcvMtaJamDetectInd: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_JAM_DETECT_IND_STRU          *pstJamInd;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
		UT_STUB_INIT();

		MOCKER(V_StopRelTimer)
			.stubs()
			.will(returnValue((VOS_UINT32)VOS_OK));

        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 生成输入消息 */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_JAM_DETECT_IND_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstJamInd = (MTA_AT_JAM_DETECT_IND_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstJamInd, 0, sizeof(MTA_AT_JAM_DETECT_IND_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaJamDetectInd_001
测试用例标题  : 通过clientid获取index失败
预期结果      : 返回VOS_ERR
修改历史      :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaJamDetectInd, Test_AT_RcvMtaJamDetectInd_001)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* 变量初始化 */
    usClientId = 0;

    // 初始化全局变量

    // MOCKER操作
	MOCKER(At_ClientIdToUserId)
		.stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRst = AT_RcvMtaJamDetectInd((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);
	GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号  : Test_AT_RcvMtaJamDetectInd_002
测试用例标题  : 上报干扰检测存在
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaJamDetectInd, Test_AT_RcvMtaJamDetectInd_002)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_CHAR                           *pcExpectStr;

    /* 变量初始化 */
    pcExpectStr = "\r\n^JDET: JAMMED\r\n";

    // 初始化全局变量

    // MOCKER操作
    pstJamInd->enJamResult = MTA_AT_JAM_RESULT_JAM_DISCOVERED;
/*
	MOCKER(At_ClientIdToUserId)
		.stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));*/


	MOCKER(At_ClientIdToUserId)
		.stubs()
		.will(returnValue((VOS_UINT32)AT_SUCCESS));

	MOCKER(At_FormatResultData)
		.stubs();
    // 调用被测函数
    ulRst = AT_RcvMtaJamDetectInd((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    ASSERT_STREQ((VOS_CHAR *)pgucAtSndCodeAddr, pcExpectStr);
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_RcvMtaJamDetectInd_003
测试用例标题  : 上报干扰检测不存在
预期结果      : 返回VOS_OK
修改历史      :
1.日   期  : 2014-05-15
  作   者  : g00261581
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RcvMtaJamDetectInd, Test_AT_RcvMtaJamDetectInd_003)
{
    // 变量声明
    VOS_UINT32                          ulRst;
    VOS_CHAR                           *pcExpectStr;

    /* 变量初始化 */
    pcExpectStr = "\r\n^JDET: DETECTING\r\n";

    // 初始化全局变量

    // MOCKER操作
    pstJamInd->enJamResult = MTA_AT_JAM_RESULT_JAM_DISAPPEARED;

	MOCKER(At_ClientIdToUserId)
		.stubs()
		.will(returnValue((VOS_UINT32)AT_SUCCESS));


    // 调用被测函数
    ulRst = AT_RcvMtaJamDetectInd((VOS_VOID*)pRcvMsg);
    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);
    ASSERT_STREQ((VOS_CHAR *)pgucAtSndCodeAddr, pcExpectStr);
	GlobalMockObject::verify();
}

