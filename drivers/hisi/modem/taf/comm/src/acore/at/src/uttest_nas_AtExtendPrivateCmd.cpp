#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtExtendPrivateCmd.h"


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

/*****************************************************************************
类名     : Test_AT_TestXcposrPara
功能描述 : AT_TestXcposrPara UT工程类
修改历史 :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*****************************************************************************/
class Test_AT_TestXcposrPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        pucSystemAppConfig          = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig         = SYSTEM_APP_ANDROID;

        stCmdInfo.ulCmdIndex        = AT_CMD_XCPOSR;
        stCmdInfo.pfnSetProc        = AT_SetXcposrPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryXcposrPara;
        stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestXcposrPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"+XCPOSR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }

    void TearDown()
    {
    }

    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
    VOS_UINT8                  *pucSystemAppConfig;
};

/*******************************************************************
测试用例编号      : Test_AT_TestXcposrPara_001
测试用例标题      : 通过HSIC通道下发正确的测试命令
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_TestXcposrPara, Test_AT_TestXcposrPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_TestXcposrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("+XCPOSR: (0,1)"));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestXcposrPara_002
测试用例标题      : 非HSIC通道下发
预期结果          : 返回AT_ERROR
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_TestXcposrPara, Test_AT_TestXcposrPara_002)
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
    ulRet = AT_TestXcposrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_TestCgpsClockPara
功能描述 : AT_TestCgpsClockPara UT工程类
修改历史 :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*****************************************************************************/
class Test_AT_TestCgpsClockPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        pucSystemAppConfig          = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig         = SYSTEM_APP_ANDROID;

        stCmdInfo.ulCmdIndex        = AT_CMD_CGPSCLOCK;
        stCmdInfo.pfnSetProc        = AT_SetCgpsClockPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestCgpsClockPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CGPSCLOCK";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(0,1)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
     }

    void TearDown()
    {

    }

    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    VOS_UINT8                          *pucSystemAppConfig;
};

/*******************************************************************
测试用例编号      : Test_AT_TestCgpsClockPara_001
测试用例标题      : 通过HSIC通道下发正确的测试命令
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_TestCgpsClockPara, Test_AT_TestCgpsClockPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量;
    ucIndex = AT_CLIENT_ID_APP;

    // MOCKER操作;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_TestCgpsClockPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^CGPSCLOCK: (0,1)"));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestCgpsClockPara_002
测试用例标题      : 非HSIC通道下发
预期结果          : 返回AT_ERROR
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_TestCgpsClockPara, Test_AT_TestCgpsClockPara_002)
{
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量;
    ucIndex = AT_CLIENT_ID_PCUI;


    // MOCKER操作;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_TestCgpsClockPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();

}


#if (FEATURE_ON == FEATURE_AT_HSIC)
/*****************************************************************************
类名     : Test_AT_TestApSecPara
功能描述 : AT_TestApSecPara UT工程类
修改历史 :
1.日    期 : 2012年09月03日
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestApSecPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        Test_AT_InitMuxClientTab();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestApSecPara_001
测试用例标题      : 命令下发通道错误
预期结果          : 返回AT_ERROR
修改历史          :
1.日    期 : 2012年09月03日
  作   者  : 工号
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestApSecPara, Test_AT_TestApSecPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex         = AT_CLIENT_TAB_MUX1_INDEX;

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_TestApSecPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestApSecPara_002
测试用例标题      : 命令下发通道正确
预期结果          : 返回AT_OK
修改历史          :
1.日    期 : 2012年09月03日
  作   者  : 工号
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestApSecPara, Test_AT_TestApSecPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex         = AT_CLIENT_TAB_MUX4_INDEX;

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_TestApSecPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}
#endif

/******************************************************************************
类名     : Test_AT_TestClprPara
功能描述 :  AT_TestClprPara UT工程类
修改历史 :
 1.日   期  : 2012-09-28
   作   者  : Y00213812
   修改内容 : STK&DCM Project 项目新增类
******************************************************************************/
class Test_AT_TestClprPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = 1;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CLPR";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(1,7)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
     }

    void TearDown()
    {

    }

    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
};
/******************************************************************************
测试用例编号: Test_AT_TestClprPara_001
测试用例标题:
预期结果    :
修改历史    :
 1.日   期  : 2012-09-28
   作   者  : Y00213812
   修改内容 : STK&DCM Project 项目新增
******************************************************************************/
TEST_F(Test_AT_TestClprPara, Test_AT_TestClprPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    VOS_UINT8                          *pucOutput = (VOS_UINT8 *)"^CLPR: (1-7)";
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_TestClprPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(0, PS_MEM_CMP(pucOutput, pgucAtSndCodeAddr,sizeof(pgucAtSndCodeAddr)));
    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_AT_TestBodySarGsmPara
功能描述 : AT_TestBodySarGsmPara UT工程类
修改历史 :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestBodySarGsmPara: public ::testing::Test
{
public:
    VOS_UINT8                       ucIndex;
    AT_PAR_CMD_ELEMENT_STRU         stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_BODYSARGSM;
        stCmdInfo.pfnSetProc        = AT_SetBodySarGsmPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryBodySarGsmPara;
        stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestBodySarGsmPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^BODYSARGSM";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(15-33),(@band),(15-33),(@band),(15-33),(@band),(15-33),(@band),(15-33),(@band),(15-33),(@band),(15-33),(@band),(15-33),(@band)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestBodySarGsmPara_001
测试用例标题      : GSM Band能力值获取失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestBodySarGsmPara, Test_AT_TestBodySarGsmPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_GetGsmBandCapa)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRet = AT_TestBodySarGsmPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestBodySarGsmPara_002
测试用例标题      : GSM Band能力值获取成功
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestBodySarGsmPara, Test_AT_TestBodySarGsmPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand        = {0};
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARGSM: (15,33),000F000F";
    stWGBand.unGsmBand.ulBand   = 0xDC;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND), outBoundP((void *)&stWGBand, sizeof(stWGBand)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_TestBodySarGsmPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_TestNetScan
功能描述 : AT_TestNetScan UT工程类
修改历史 :
1.日   期  : 2013-10-31
  作   者  : w00242748
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestNetScan: public ::testing::Test
{
public:
    VOS_UINT8                       ucIndex;
    AT_PAR_CMD_ELEMENT_STRU         stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_NETSCAN;
        stCmdInfo.pfnSetProc        = AT_SetNetScan;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestNetScan;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^NETSCAN";
        stCmdInfo.pszParam          = (VOS_UINT8*)"";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestNetScan_001
测试用例标题      : GSM Band能力值获取失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestNetScan, Test_AT_TestNetScan_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           ulRet;

    // 参数初始化
    ucIndex    = 0;

    // 初始化全局变量


    // MOCKER操作


    // 调用被测函数
    ulRet = AT_TestNetScan(ucIndex);

    // 执行检查
    pcExpect = "^NETSCAN: (1-20),(-110--47),(0,1)";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_TestBodySarWcdmaPara
功能描述 : AT_TestBodySarWcdmaPara UT工程类
修改历史 :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestBodySarWcdmaPara: public ::testing::Test
{
public:
    VOS_UINT8                       ucIndex;
    AT_PAR_CMD_ELEMENT_STRU         stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_BODYSARWCDMA;
        stCmdInfo.pfnSetProc        = AT_SetBodySarWcdmaPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryBodySarWcdmaPara;
        stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestBodySarWcdmaPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^BODYSARWCDMA";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(17-24),(@band),(17-24),(@band),(17-24),(@band),(17-24),(@band),(17-24),(@band),(17-24),(@band),(17-24),(@band),(17-24),(@band)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestBodySarWcdmaPara_001
测试用例标题      : WCDMA Band能力值获取失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestBodySarWcdmaPara, Test_AT_TestBodySarWcdmaPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulRet = AT_TestBodySarWcdmaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestBodySarWcdmaPara_002
测试用例标题      : WCDMA Band能力值获取成功
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestBodySarWcdmaPara, Test_AT_TestBodySarWcdmaPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand = {0};
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARWCDMA: (17,24),0000000F";

    stWGBand.unWcdmaBand.ulBand                     = 0x0000000F;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_I_2100   = 1;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_II_1900  = 1;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_III_1800 = 1;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_IV_1700  = 1;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND), outBoundP((void *)&stWGBand, sizeof(stWGBand)), eq((VOS_UINT32)sizeof(stWGBand)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_TestBodySarWcdmaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

#if (FEATURE_VSIM == FEATURE_ON)
/*****************************************************************************
 类名       : Test_AT_TestSyscfgEx
 功能描述   : AT_TestRsfwPara UT工程类
 修改历史   :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_AT_TestRsfwPara: public ::testing::Test
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
 测试用例编号 : Test_AT_TestRsfwPara_001
 测试用例标题 : AT_TestRsfwPara  测试函数
 预期结果     : 返回AT_OK
 修改历史     :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestRsfwPara,Test_AT_TestRsfwPara_001)
{
    /* 变量初始化 */

    /* 函数打桩 */
    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/

    /* 调用被测函数并结果验证 */
    EXPECT_EQ(AT_OK, AT_TestRsfwPara(0));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
