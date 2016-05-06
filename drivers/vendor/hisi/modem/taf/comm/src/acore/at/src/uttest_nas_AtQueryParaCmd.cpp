#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtQueryParaCmd.h"

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

AT_PAR_CMD_ELEMENT_STRU             gstU2diagCmdInfo = {AT_CMD_U2DIAG,
    At_SetU2DiagPara,       AT_SET_PARA_TIME,   At_QryU2DiagPara,       AT_QRY_PARA_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_CLAC_IS_INVISIBLE_STICK | CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^U2DIAG",    (VOS_UINT8*)"(0-4294967295)"};

AT_PAR_CMD_ELEMENT_STRU             gstDislogCmdInfo = {AT_CMD_DISLOG,
    AT_SetDislogPara,       AT_NOT_SET_TIME,  AT_QryDislogPara,         AT_NOT_SET_TIME,   At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED | CMD_TBL_E5_IS_LOCKED,
    (VOS_UINT8*)"^DISLOG",      (VOS_UINT8*)"(0,1,255)"};

AT_PAR_CMD_ELEMENT_STRU             gstPcscCmdInfo = {AT_CMD_PCSCINFO,
    At_SetPcscInfo,         AT_NOT_SET_TIME,    At_QryPcscInfo,         AT_NOT_SET_TIME,    At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"^PCSCINFO",    (VOS_UINT8*)"(0,1)"};

AT_PAR_CMD_ELEMENT_STRU             gstRsimCmdInfo = {AT_CMD_RSIM,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryRsimPara,        AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^RSIM",     VOS_NULL_PTR};

/* Added by b00269685 for L-C互操作项目, 2014-2-25, begin */
/*****************************************************************************
类名 : Test_AT_QrySysCfgExPara
功能描述 : AT_QrySysCfgExPara　UT工程类
修改历史     :
1.日   期  : 2014-02-25
作   者  : b00269685
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QrySysCfgExPara: public ::testing::Test
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

/*******************************************************************
测试用例编号      : Test_At_QrySysCfgExPara_001
测试用例标题      : 查询syscfgex设置成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2014-02-25
作   者  : b00269685
修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_AT_QrySysCfgExPara,Test_AT_QrySysCfgExPara_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    //参数初始化
    ucIndex = 1;

    // 初始化全局变量

    // MOCKER操作;
    MOCKER(TAF_MMA_QrySyscfgReq)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulResult = AT_QrySysCfgExPara(ucIndex);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_SYSCFGEX_READ);
    EXPECT_EQ(ulResult, AT_WAIT_ASYNC_RETURN);

    // 执行检查
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QrySysCfgExPara_002
测试用例标题      : 查询syscfgex设置失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2014-02-25
作   者  : b00269685
修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_AT_QrySysCfgExPara,Test_AT_QrySysCfgExPara_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    //参数初始化
    ucIndex = 1;

    // 初始化全局变量

    // MOCKER操作;
    MOCKER(TAF_MMA_QrySyscfgReq)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulResult = AT_QrySysCfgExPara(ucIndex);
    EXPECT_EQ(ulResult, AT_ERROR);

    // 执行检查
    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_At_QrySysCfgPara
功能描述 : At_QrySysCfgPara　UT工程类
修改历史     :
1.日   期  : 2014-02-25
作   者  : b00269685
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QrySysCfgPara: public ::testing::Test
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

/*******************************************************************
测试用例编号      : Test_At_QrySysCfgPara_001
测试用例标题      : 查询syscfgex设置成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2014-02-25
作   者  : b00269685
修改内容 : 新建CASE
2.日    期   : 2015年4月7日
作    者   : y00322978
修改内容   : 修改消息发送接口后更改测试用例

*******************************************************************/
TEST_F(Test_At_QrySysCfgPara,Test_At_QrySysCfgPara_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_MMA_SYSCFG_QRY_REQ_STRU         pstMsg;

    //参数初始化
    ucIndex = 1;

    PS_MEM_SET(&pstMsg, 0, sizeof(pstMsg));

    /* 发送PID统一填写为WUEPS_PID_TAF */
    pstMsg.ulSenderCpuId                = VOS_LOCAL_CPUID;
    pstMsg.ulReceiverCpuId              = VOS_LOCAL_CPUID;
    pstMsg.ulSenderPid                  = WUEPS_PID_TAF;
    pstMsg.ulReceiverPid                = WUEPS_PID_MMA;
    pstMsg.ulMsgName                    = ID_TAF_MMA_SYSCFG_QRY_REQ;
    pstMsg.ulLength                     = sizeof(TAF_MMA_SYSCFG_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg.stCtrl.ulModuleId            = WUEPS_PID_AT;
    pstMsg.stCtrl.usClientId            = gastAtClientTab[ucIndex].usClientId;
    pstMsg.stCtrl.ucOpId                = 0;

    //MOCKER操作
    MOCKER(Ps_SendMsg)
        .with(any(), any(),eq(WUEPS_PID_TAF), mirror(&pstMsg, sizeof(pstMsg)))
        .will(invoke(Ps_SendMsgSucc));;

    // 调用被测函数
    ulResult = At_QrySysCfgPara(ucIndex);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_SYSCFG_READ);
    EXPECT_EQ(ulResult, AT_WAIT_ASYNC_RETURN);

    // 执行检查
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QrySysCfgPara_002
测试用例标题      : 查询syscfgex设置失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2014-02-25
作   者  : b00269685
修改内容 : 新建CASE
2.日    期   : 2015年4月7日
作    者   : y00322978
修改内容   : 修改消息发送接口后更改测试用例
*******************************************************************/
TEST_F(Test_At_QrySysCfgPara,Test_At_QrySysCfgPara_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    //参数初始化
    ucIndex = 1;

    // 初始化全局变量

    //MOCKER操作
    MOCKER(V_AllocMsg)
    .times(1)
    .will(returnValue(VOS_NULL_PTR));

    // 调用被测函数
    ulResult = At_QrySysCfgPara(ucIndex);
    EXPECT_EQ(ulResult, AT_ERROR);

    // 执行检查
    GlobalMockObject::verify();
}
/* Added by b00269685 for L-C互操作项目, 2014-2-25, end */

/*****************************************************************************
类名     : Test_AT_GetWifiNvValue
功能描述 : Test_AT_GetWifiNvValue UT工程类
修改历史     :

1.日   期  : 2012-07-30
  作   者  : f62575
  修改内容 : 新生成类
2.日   期  : 2012-09-18
  作   者  : z60575
  修改内容 : 支持多组SSID修改
*****************************************************************************/
class Test_AT_GetWifiNvValue: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
protected:
};

/*******************************************************************
测试用例编号      : Test_AT_GetWifiNvValue_001
测试用例标题      : 获取WIFI相关的NV项是否为默认值：所有数据均为0
预期结果          : 返回VOS_OK，输出判断结果WIFI相关的NV项是默认值

1.日   期  : 2012-07-30
  作   者  : f62575
  修改内容 : 新生成类
2.日   期  : 2012-09-18
  作   者  : z60575
  修改内容 : 支持多组SSID修改
*******************************************************************/
TEST_F(Test_AT_GetWifiNvValue, Test_AT_GetWifiNvValue_001)
{
    /*变量定义*/
    TAF_AT_MULTI_WIFI_SEC_STRU          stWifiKeyStub;
    TAF_AT_MULTI_WIFI_SSID_STRU         stWifiSsidStub;
    VOS_UINT16                          usCsdValue;
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    memset(&stWifiKeyStub, 0, sizeof(stWifiKeyStub));
    memset(&stWifiSsidStub, 0, sizeof(stWifiSsidStub));
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiKeyStub, sizeof(stWifiKeyStub)), any())
        .will(returnValue((VOS_UINT32)NV_OK))
        .id("first");

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_STATUS_SSID), outBoundP((void *)&stWifiSsidStub, sizeof(stWifiSsidStub)), any())
        .after("first")
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    ulRst = AT_GetWifiNvValue(&usCsdValue);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE, usCsdValue);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetWifiNvValue_002
测试用例标题      : 获取WIFI相关的NV项是否为默认值：NV项en_NV_Item_MULTI_WIFI_KEY读取失败
预期结果          : 返回VOS_ERR

1.日   期  : 2012-07-30
  作   者  : f62575
  修改内容 : 新生成类
 2.日   期  : 2012-09-18
  作   者  : z60575
  修改内容 : 支持多组SSID修改
*******************************************************************/
TEST_F(Test_AT_GetWifiNvValue, Test_AT_GetWifiNvValue_002)
{
    /*变量定义*/
    TAF_AT_MULTI_WIFI_SEC_STRU                    stWifiKeyStub;
    TAF_AT_MULTI_WIFI_SSID_STRU                   stWifiSsidStub;
    VOS_UINT16                          usCsdValue;
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    memset(&stWifiKeyStub, 0, sizeof(stWifiKeyStub));
    memset(&stWifiSsidStub, 0, sizeof(stWifiSsidStub));
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiKeyStub, sizeof(stWifiKeyStub)), any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    ulRst = AT_GetWifiNvValue(&usCsdValue);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetWifiNvValue_003
测试用例标题      : 获取WIFI相关的NV项是否为默认值：NV项en_NV_Item_MULTI_WIFI_STATUS_SSID读取失败
预期结果          : 返回VOS_ERR

1.日   期  : 2012-07-30
  作   者  : f62575
  修改内容 : 新生成类
2.日   期  : 2012-09-18
  作   者  : z60575
  修改内容 : 支持多组SSID修改
*******************************************************************/
TEST_F(Test_AT_GetWifiNvValue, Test_AT_GetWifiNvValue_003)
{
    /*变量定义*/
    TAF_AT_MULTI_WIFI_SEC_STRU                    stWifiKeyStub;
    TAF_AT_MULTI_WIFI_SSID_STRU                   stWifiSsidStub;
    VOS_UINT16                          usCsdValue;
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    memset(&stWifiKeyStub, 0, sizeof(stWifiKeyStub));
    memset(&stWifiSsidStub, 0, sizeof(stWifiSsidStub));
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiKeyStub, sizeof(stWifiKeyStub)), any())
        .will(returnValue((VOS_UINT32)NV_OK))
        .id("first");

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_STATUS_SSID), outBoundP((void *)&stWifiSsidStub, sizeof(stWifiSsidStub)), any())
        .after("first")
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    ulRst = AT_GetWifiNvValue(&usCsdValue);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetWifiNvValue_004
测试用例标题      : 获取WIFI相关的NV项是否为默认值：NV项en_NV_Item_MULTI_WIFI_STATUS_SSID的输出aucWifiSsid[0]字段非0
预期结果          : 返回VOS_OK，输出判断结果WIFI相关的NV项不是默认值

1.日   期  : 2012-07-30
  作   者  : f62575
  修改内容 : 新生成类
2.日   期  : 2012-09-18
  作   者  : z60575
  修改内容 : 支持多组SSID修改
*******************************************************************/
TEST_F(Test_AT_GetWifiNvValue, Test_AT_GetWifiNvValue_004)
{
    /*变量定义*/
    TAF_AT_MULTI_WIFI_SEC_STRU                    stWifiKeyStub;
    TAF_AT_MULTI_WIFI_SSID_STRU                   stWifiSsidStub;
    VOS_UINT16                          usCsdValue;
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    memset(&stWifiKeyStub, 0, sizeof(stWifiKeyStub));
    memset(&stWifiSsidStub, 0, sizeof(stWifiSsidStub));
    stWifiSsidStub.aucWifiSsid[0][0] = 1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiKeyStub, sizeof(stWifiKeyStub)), any())
        .will(returnValue((VOS_UINT32)NV_OK))
        .id("first");

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_STATUS_SSID), outBoundP((void *)&stWifiSsidStub, sizeof(stWifiSsidStub)), any())
        .after("first")
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    ulRst = AT_GetWifiNvValue(&usCsdValue);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED, usCsdValue);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetWifiNvValue_005
测试用例标题      : 获取WIFI相关的NV项是否为默认值：NV项en_NV_Item_MULTI_WIFI_KEY的输出aucWifiWpapsk[1]字段非0
预期结果          : 返回VOS_OK，输出判断结果WIFI相关的NV项不是默认值

1.日   期  : 2012-07-30
  作   者  : f62575
  修改内容 : 新生成类
2.日   期  : 2012-09-18
  作   者  : z60575
  修改内容 : 支持多组SSID修改
*******************************************************************/
TEST_F(Test_AT_GetWifiNvValue, Test_AT_GetWifiNvValue_005)
{
    /*变量定义*/
    TAF_AT_MULTI_WIFI_SEC_STRU                    stWifiKeyStub;
    TAF_AT_MULTI_WIFI_SSID_STRU                   stWifiSsidStub;
    VOS_UINT16                          usCsdValue;
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    memset(&stWifiKeyStub, 0, sizeof(stWifiKeyStub));
    stWifiKeyStub.aucWifiWpapsk[0][1] = 1;
    memset(&stWifiSsidStub, 0, sizeof(stWifiSsidStub));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiKeyStub, sizeof(stWifiKeyStub)), any())
        .will(returnValue((VOS_UINT32)NV_OK))
        .id("first");

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_STATUS_SSID), outBoundP((void *)&stWifiSsidStub, sizeof(stWifiSsidStub)), any())
        .after("first")
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    ulRst = AT_GetWifiNvValue(&usCsdValue);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED, usCsdValue);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_GetCsdValue
功能描述 : AT_GetCsdValue UT工程类
修改历史     :

1.日   期  : 2012-07-30
  作   者  : f62575
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_GetCsdValue: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
protected:
};

/*******************************************************************
测试用例编号      : Test_AT_GetCsdValue_001
测试用例标题      : 获取定制值
预期结果          : 返回VOS_OK，输出NV项为默认值

1.日   期  : 2012-07-30
  作   者  : f62575
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_GetCsdValue, Test_AT_GetCsdValue_001)
{
    /*变量定义*/
    VOS_BOOL                            bSimlockEnableFlg;
    VOS_UINT16                          usCsdValue;
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    bSimlockEnableFlg = VOS_FALSE;
    usCsdValue        = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;

    MOCKER(At_ReadCustomizeServiceNV)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_ReadGprsActiveTimerLenNV)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_UNSUPPORT));

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    ulRst = AT_GetCsdValue(bSimlockEnableFlg, &usCsdValue);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE, usCsdValue);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryDislogPara
功能描述 : Test_AT_QryDislogPara UT工程类
修改历史     :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryDislogPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
        g_stParseContext[ucIndex].pstCmdElement = &gstDislogCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};

#if (FEATURE_ON!=FEATURE_LTE)
/*******************************************************************
测试用例编号      : Test_AT_QryDislogPara_001
测试用例标题      : DIAG端口已经打开
预期结果          : 输出字符串
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryDislogPara, Test_AT_QryDislogPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* 设备切换前端口形态 */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x03,0x14,0x15, 0xA1,0xA2, 0x00};  /* 设备切换后端口形态 */

    /* 初始化变量 */
    pcExpactedStr = "^DISLOG:0";

    /* 初始化变量 */

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gastAtClientTab[ucIndex].opId       = 0;

    /* 桩函数 */
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 调用消息入口函数 */
    ulRst = AT_QryDislogPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_QryDislogPara_002
测试用例标题      : DIAG端口未打开
预期结果          : 输出字符串
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryDislogPara, Test_AT_QryDislogPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* 设备切换前端口形态 */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x14,0x15, 0xA1,0xA2, 0x00};  /* 设备切换后端口形态 */

    /* 初始化变量 */
    pcExpactedStr = "^DISLOG:1";

    /* 初始化变量 */

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gastAtClientTab[ucIndex].opId       = 0;

    /* 桩函数 */
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 调用消息入口函数 */
    ulRst = AT_QryDislogPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#endif

/*****************************************************************************
类名     : Test_At_QryPcscInfo
功能描述 : Test_At_QryPcscInfo UT工程类
修改历史     :

1.日   期  : 2012-03-20
  作   者  : L60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryPcscInfo: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
        g_stParseContext[ucIndex].pstCmdElement = &gstPcscCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};

/*******************************************************************
测试用例编号      : Test_At_QryPcscInfo_001
测试用例标题      : PCSC端口已经打开
预期结果          : 输出字符串
修改历史   :

1.日   期  : 2012-03-20
  作   者  : L60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryPcscInfo, Test_At_QryPcscInfo_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* 设备切换前端口形态 */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x03,0x14,0x15, 0xA1,0xA2, 0x04};  /* 设备切换后端口形态 */

    /* 初始化变量 */
    pcExpactedStr = "^PCSCINFO:1";

    /* 初始化变量 */

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gastAtClientTab[ucIndex].opId       = 0;

    /* 桩函数 */
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 调用消息入口函数 */
    ulRst = At_QryPcscInfo(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_At_QryPcscInfo_002
测试用例标题      : PCSC端口未打开
预期结果          : 输出字符串
修改历史   :

1.日   期  : 2012-03-20
  作   者  : L60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryPcscInfo, Test_At_QryPcscInfo_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* 设备切换前端口形态 */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x14,0x15, 0xA1,0xA2, 0x00};  /* 设备切换后端口形态 */

    /* 初始化变量 */
    pcExpactedStr = "^PCSCINFO:0";

    /* 初始化变量 */

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gastAtClientTab[ucIndex].opId       = 0;

    /* 桩函数 */
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 调用消息入口函数 */
    ulRst = At_QryPcscInfo(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}


/*****************************************************************************
类名     : Test_At_QryCsdfltPara
功能描述 : Test_At_QryCsdfltPara UT工程类
修改历史     :
1.日   期  : 2011-10-13
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCsdfltPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCsdfltPara_001
测试用例标题      : 查询查询定制项的默认值：消息发送失败
预期结果          : 函数返回为AT_ERROR
修改历史          :
1.日   期         : 2012-02-29
  作   者         : f62575
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdfltPara,Test_At_QryCsdfltPara_001)
{
    // 变量声明
    VOS_UINT32                            ulRet;
    VOS_UINT8                             ucIndex;

    //参数初始化
    ucIndex  = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(Taf_ParaQuery)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = At_QryCsdfltPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCsdfltPara_002
测试用例标题      : 查询查询定制项的默认值：消息发送成功
预期结果          : 函数返回为AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期         : 2012-02-29
  作   者         : f62575
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdfltPara,Test_At_QryCsdfltPara_002)
{
    // 变量声明
    VOS_UINT32                            ulRet;
    VOS_UINT8                             ucIndex;

    //参数初始化
    ucIndex  = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(Taf_ParaQuery)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = At_QryCsdfltPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_CSDFLT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryAppdmverPara
功能描述 : AT_QryAppdmverPara UT工程类
修改历史     :
1.日   期  : 2011-10-13
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryAppdmverPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        gucAtParaIndex                    = 1;
        gastAtParaList[0].usParaLen        = 1;
        gastAtParaList[0].ulParaValue    = 0;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_SetCdurPara_001
测试用例标题      : 查询当前PDM版本号：消息发送失败
预期结果          : 函数返回均为AT_ERROR
修改历史          :
1.日   期         : 2011-10-14
  作   者         : f62575
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAppdmverPara,Test_AT_QryAppdmverPara_001)
{
    // 变量声明
    VOS_UINT32                            ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr = "AT_QryAppdmverPara: AT_FillAndSndAppReqMsg fail.";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryAppdmverPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetCdurPara_002
测试用例标题      : 查询当前PDM版本号：消息发送成功
预期结果          : 函数返回均为AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期         : 2011-10-14
  作   者         : f62575
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAppdmverPara,Test_AT_QryAppdmverPara_002)
{
    // 变量声明
    VOS_UINT32                            ulRet;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex     = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryAppdmverPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_APPDMVER_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryCscaPara
功能描述 : At_QryCscaPara UT工程类
修改历史     :
1.日   期  : 2011-10-13
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCscaPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        gucAtParaIndex                    = 1;
        gastAtParaList[0].usParaLen        = 1;
        gastAtParaList[0].ulParaValue    = 0;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCscaPara_001
测试用例标题      : CSCA查询命令调用MN_MSG_ReadSrvParam发送查询消息失败
预期结果          : 函数返回均为AT_ERROR
修改历史          :
1.日   期         : 2011-10-14
  作   者         : f62575
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCscaPara,Test_At_QryCscaPara_001)
{
    // 变量声明
    VOS_UINT32                            ulRet;

    //参数初始化

    // 初始化全局变量;
    gucAtParaIndex = 0;

    // MOCKER操作;
    MOCKER(MN_MSG_ReadSrvParam)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_INVALIDPARM));

    // 调用被测函数
    ulRet = At_QryCscaPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCscaPara_002
测试用例标题      : CSCA查询命令调用MN_MSG_ReadSrvParam发送查询消息成功
预期结果          : 函数返回均为AT_WAIT_ASYNC_RETURN同时操作标志AT_CMD_CSCA_READ
修改历史          :
1.日   期         : 2011-10-14
  作   者         : f62575
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCscaPara,Test_At_QryCscaPara_002)
{
    // 变量声明
    VOS_UINT32                            ulRet;

    //参数初始化

    // 初始化全局变量;
    gucAtParaIndex = 0;

    // MOCKER操作;
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = At_QryCscaPara(0);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_CSCA_READ, gastAtClientTab[0].CmdCurrentOpt);

    GlobalMockObject::verify();
}

#if (NAS_FEATURE_CS_VC == FEATURE_ON)
/*****************************************************************************
类名     : Test_At_QryVMSETPara
功能描述 : At_QryVMSETPara函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : f00179208
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryVMSETPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VMSET_READ;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VMSET_READ;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_At_QryVMSETPara_001
测试用例标题      : AT命令参数检查错误
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryVMSETPara,Test_At_QryVMSETPara_001)
{
    // 参数定义
    VOS_UINT32   ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    // MOCKER操作;

    // 调用被测函数
    ulRst = At_QryVMSETPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryVMSETPara_002
测试用例标题      : 获取语音模式成功
预期结果          : 当前操作类型为AT_CMD_VMSET_READ，返回AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryVMSETPara,Test_At_QryVMSETPara_002)
{
    // 参数定义
    VOS_UINT32      ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(APP_VC_GetVoiceMode)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRst = At_QryVMSETPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    EXPECT_EQ(AT_CMD_VMSET_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryVMSETPara_003
测试用例标题      : 获取语音模式失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryVMSETPara,Test_At_QryVMSETPara_003)
{
    // 参数定义
    VOS_UINT32      ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(APP_VC_GetVoiceMode)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRst = At_QryVMSETPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryCvoicePara
功能描述 : At_QryCvoicePara函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : f00179208
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCvoicePara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVOICE_READ;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVOICE_READ;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCvoicePara_001
测试用例标题      : AT命令参数检查错误
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCvoicePara,Test_At_QryCvoicePara_001)
{
    // 参数定义
    VOS_UINT32   ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    // MOCKER操作;

    // 调用被测函数
    ulRst = At_QryCvoicePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCvoicePara_002
测试用例标题      : 获取语音模式成功
预期结果          : 当前操作类型为AT_CMD_CVOICE_READ，返回AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCvoicePara,Test_At_QryCvoicePara_002)
{
    // 参数定义
    VOS_UINT32      ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(APP_VC_GetVoiceMode)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRst = At_QryCvoicePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    EXPECT_EQ(AT_CMD_CVOICE_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCvoicePara_003
测试用例标题      : 获取语音模式失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCvoicePara,Test_At_QryCvoicePara_003)
{
    // 参数定义
    VOS_UINT32      ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(APP_VC_GetVoiceMode)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRst = At_QryCvoicePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryDdsetexPara
功能描述 : At_QryDdsetexPara函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : f00179208
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryDdsetexPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DDSETEX_READ;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DDSETEX_READ;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_At_QryDdsetexPara_001
测试用例标题      : AT命令参数检查错误
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryDdsetexPara,Test_At_QryDdsetexPara_001)
{
    // 参数定义
    VOS_UINT32   ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    // MOCKER操作;

    // 调用被测函数
    ulRst = At_QryDdsetexPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryDdsetexPara_002
测试用例标题      : 获取语音模式成功
预期结果          : 当前操作类型为AT_CMD_DDSETEX_READ，返回AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryDdsetexPara,Test_At_QryDdsetexPara_002)
{
    // 参数定义
    VOS_UINT32      ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(APP_VC_GetVoicePort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRst = At_QryDdsetexPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    EXPECT_EQ(AT_CMD_DDSETEX_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryDdsetexPara_003
测试用例标题      : 获取语音模式失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryDdsetexPara,Test_At_QryDdsetexPara_003)
{
    // 参数定义
    VOS_UINT32      ulRst;

    // 参数初始化

    // 相关全局变量初始化
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(APP_VC_GetVoicePort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRst = At_QryDdsetexPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


/******************************************************************************
类名     : Test_At_QryDialModePara
功能描述 : At_QryDialModePara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_At_QryDialModePara: public ::testing::Test
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
*测试项:              DIALMODE返回成功
*被测函数功能描述:    AT命令，查询拨号方式
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年6月29日
#    作    者: o00132663
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryDialModePara,Test_At_QryDialModePara_01)
{
    // 参数定义
    VOS_UINT8    ucDialmode = 0;
    VOS_UINT8    ucCdcSpec  = 1;
    TAF_UINT32   ulRst;
    TAF_UINT8    ucIndex;
    char *paucExpectedStr = "^DIALMODE:0,1";
    char         *pCmdName = "^DIALMODE";
   AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_DIALMODE,
    At_SetDialModePara,     AT_NOT_SET_TIME,  At_QryDialModePara,       AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_STICK,
    (VOS_UINT8*)"^DIALMODE", (VOS_UINT8*)"(0-2),(0-255)"};


    // 参数初始化
    ucIndex = 0;

    // 相关全局变量初始化
    PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
     g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (TAF_UINT8 *)pCmdName;

    // MOCKER操作;
    MOCKER(BSP_USB_GetDiagModeValue)
        .stubs()
        .with(outBoundP((VOS_UINT8 *)&ucDialmode, sizeof(ucDialmode)),outBoundP((VOS_UINT8 *)&ucCdcSpec, sizeof(ucCdcSpec)))
        .will(returnValue((BSP_S32)VOS_OK));

    // 调用被测函数
    ulRst = At_QryDialModePara(ucIndex);

    // 执行检查
    ASSERT_EQ(AT_OK, ulRst);
    ASSERT_STREQ(paucExpectedStr , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



/*******************************************************************
*测试项:              DIALMODE调用失败
*被测函数功能描述:    AT命令，查询拨号方式
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年6月29日
#    作    者: o00132663
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryDialModePara,Test_At_QryDialModePara_02)
{
    // 参数定义
    VOS_UINT8    ucDialmode = 0;
    VOS_UINT8    ucCdcSpec  = 1;
    TAF_UINT32   ulRst;
    TAF_UINT8    ucIndex;

    // 参数初始化
    ucIndex = 0;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(BSP_USB_GetDiagModeValue)
        .stubs()
        .with(outBoundP((VOS_UINT8 *)&ucDialmode, sizeof(ucDialmode)),outBoundP((VOS_UINT8 *)&ucCdcSpec, sizeof(ucCdcSpec)))
        .will(returnValue((BSP_S32)VOS_ERR));

    // 调用被测函数
    ulRst = At_QryDialModePara(ucIndex);

    // 执行检查
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

/******************************************************************************
类名     : Test_At_QryCscbPara
功能描述 : At_QryCscbPara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_At_QryCscbPara: public ::testing::Test
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
*测试项:           调用CBS提供的API接口返回失败后直接返回查询失败
*被测函数功能描述: 查询CSCB当前设置的值
*预期结果：        返回查询失败
************************* 修改记录 ********************************
#  1.日    期: 2010年05月17日
#    作    者: z40661
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCscbPara,Test_At_QryCscbPara_01)
{
    MOCKER(MN_MSG_GetAllCbMids)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_UNSPECIFIED));

    ASSERT_EQ(AT_ERROR, At_QryCscbPara(0));
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
*测试项:           调用CBS提供的API接口返回成功后直接返回AT_WAIT_ASYNC_RETURN等待MSG模块上报查询结果
*被测函数功能描述: 查询CSCB当前设置的值
*预期结果：        返回返回AT_WAIT_ASYNC_RETURN等待MSG模块上报查询结果
************************* 修改记录 ********************************
#  1.日    期: 2010年05月17日
#    作    者: z40661
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCscbPara,Test_At_QryCscbPara_02)
{
    MOCKER(MN_MSG_GetAllCbMids)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, At_QryCscbPara(0));
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#endif


/******************************************************************************
类名     : Test_At_QryPort
功能描述 : Test_At_QryPort UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_At_QryPort: public ::testing::Test
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
*测试项:           PID使能NV读取失败
*被测函数功能描述: 查询当前端口形态
*预期结果：
************************* 修改记录 ********************************
#  1.日    期: 2010年05月07日
#    作    者: a00165503
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryPort,Test_At_QryPort_01)
{
    // 参数定义
    VOS_UINT32      ulRst;
    VOS_UINT8       ucIndex;

    DRV_DYNAMIC_PID_TYPE_STRU   stDynamicPidType;
    AT_PID_ENABLE_TYPE_STRU     stPidEnableType;

    //参数赋值
    ucIndex = 0;
    stPidEnableType.ulPidEnabled = VOS_FALSE;

    // 相关全局变量初始化

    //打桩
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    //执行测试函数
    ulRst = At_QryPort(ucIndex);
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:           PID未使能
*被测函数功能描述: 查询当前端口形态
*预期结果：
************************* 修改记录 ********************************
#  1.日    期: 2010年05月07日
#    作    者: a00165503
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryPort,Test_At_QryPort_02)
{
    // 参数定义
    VOS_UINT32      ulRst;
    VOS_UINT8       ucIndex;

    DRV_DYNAMIC_PID_TYPE_STRU   stDynamicPidType;
    AT_PID_ENABLE_TYPE_STRU     stPidEnableType;

    //参数赋值
    ucIndex = 0;
    stPidEnableType.ulPidEnabled = VOS_FALSE;

    // 相关全局变量初始化

    //打桩
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_PID_Enable_Type), outBoundP((void *)&stPidEnableType, sizeof(stPidEnableType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    //执行测试函数
    ulRst = At_QryPort(ucIndex);
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:           获取当前的端口形态失败
*被测函数功能描述: 查询当前端口形态
*预期结果：
************************* 修改记录 ********************************
#  1.日    期: 2010年05月07日
#    作    者: a00165503
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryPort,Test_At_QryPort_03)
{
    // 参数定义
    VOS_UINT32   ulRst;
    VOS_UINT8    ucIndex;
    AT_PID_ENABLE_TYPE_STRU     stPidEnableType;

    //参数初始化
    stPidEnableType.ulPidEnabled = VOS_TRUE;
    ucIndex = 0;

    //打桩
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_PID_Enable_Type), outBoundP((void *)&stPidEnableType, sizeof(stPidEnableType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(set_port_quiry)
        .stubs()
        .will(returnValue((unsigned int)1));

    //执行测试函数
    ulRst = At_QryPort(ucIndex);
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:           获取当前的端口形态成功
*被测函数功能描述: 查询当前端口形态
*预期结果：
************************* 修改记录 ********************************
#  1.日    期: 2010年05月07日
#    作    者: a00165503
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryPort,Test_At_QryPort_04)
{
    // 参数定义
    VOS_UINT32      ulRst;
    VOS_UINT8       ucIndex;
    VOS_UINT8       aucFirstPortStyle[]  = {0xA1, 0xA2};
    VOS_UINT8       aucRewindPortStyle[] = {0x01, 0x02, 0x03};
    VOS_UINT8       aucCmdName[]         = "^SETPORT";
    VOS_UINT8       aucExpectedStr[]     = "^SETPORT:A1,A2;1,2,3";
    AT_PAR_CMD_ELEMENT_STRU             stElement;

    DRV_DYNAMIC_PID_TYPE_STRU   stDynamicPidType;
    AT_PID_ENABLE_TYPE_STRU     stPidEnableType;

    //参数赋值
    ucIndex = 0;
    stPidEnableType.ulPidEnabled = VOS_TRUE;

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement = &stElement;
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName =(VOS_UINT8 *)aucCmdName;

    memset(&stDynamicPidType, 0, sizeof(DRV_DYNAMIC_PID_TYPE_STRU));
    memset(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    memcpy(stDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    memcpy(stDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));

    //打桩
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_PID_Enable_Type), outBoundP((void *)&stPidEnableType, sizeof(stPidEnableType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(set_port_quiry)
        .expects(exactly(1))
        .with(outBoundP((DRV_DYNAMIC_PID_TYPE_STRU *)&stDynamicPidType, (VOS_UINT32)sizeof(stDynamicPidType)))
        .will(returnValue((unsigned int)0));

    //执行测试函数
    ulRst = At_QryPort(ucIndex);
    ASSERT_EQ(AT_OK, ulRst);
    ASSERT_STREQ((char *)aucExpectedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



#if(FEATURE_ON == FEATURE_E5)
/******************************************************************************
类名     : Test_AT_QryWifiBlobalMacPara
功能描述 : AT_QryWifiBlobalMacPara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_AT_QryWifiBlobalMacPara: public ::testing::Test
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
*测试项:          查询网关MAC地址
*被测函数功能描述:读NV成功，NV项激活
*预期结果：       返回AT_OK
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: s62952
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryWifiBlobalMacPara,Test_AT_QryWifiBlobalMacPara_01)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRst;
    char                                *paucExpectedStr = "^APMAC:01:AB:EF:89:34:02";
    VOS_UINT8                           aucE5GwMacAddr[AT_GNA_E5_MAC_ADDR_LEN+1];

    // 参数初始化
    ucIndex = 0;
    PS_MEM_SET(aucE5GwMacAddr, 0x00, sizeof(aucE5GwMacAddr));

    strcpy((char *)aucE5GwMacAddr,"01:AB:EF:89:34:02");

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].pucCmdName = (TAF_UINT8 *)"^APMAC";

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_WIFI_MAC_ADDR),outBoundP((char *)aucE5GwMacAddr),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRst = AT_QryWifiBlobalMacPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK,ulRst);
    //ASSERT_STREQ(paucExpectedStr , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
*测试项:          查询网关MAC地址
*被测函数功能描述:读NV失败
*预期结果：       返回AT_ERROR
************************* 修改记录 *************************
#  1.日    期: 2010年9月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryWifiBlobalMacPara,Test_AT_QryWifiBlobalMacPara_02)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRst;


    // 参数初始化
    ucIndex = 0;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulRst = AT_QryWifiBlobalMacPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR,ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#endif


#if(FEATURE_ON == FEATURE_E5)

/******************************************************************************
类名     : Test_At_QryApThroughputPara
功能描述 : At_QryApThroughputPara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_At_QryApThroughputPara: public ::testing::Test
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
*测试项:          1。未拨上号速率为0
*被测函数功能描述:E5查询当前流量
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年9月15日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryApThroughputPara,Test_At_QryApThroughputPara_01)
{
    MOCKER(AT_E5GetState)
        .stubs()
        .will(returnValue(AT_PDP_STATE_IDLE));

    /*MOCKER(At_sprintf)
        .expects(exactly(3));*/

    At_QryApThroughputPara(0);

    EXPECT_EQ(g_stAtE5CurrentRate.ulULCurrentRate, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:          2。已拨上号
*被测函数功能描述:E5查询当前流量
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年9月15日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryApThroughputPara,Test_At_QryApThroughputPara_02)
{
    g_stAtE5CurrentRate.ulDLCurrentRate = 5;

    MOCKER(AT_E5GetState)
        .stubs()
        .will(returnValue(AT_PDP_STATE_ACTED));

    /*MOCKER(At_sprintf)
        .expects(exactly(3));*/

    At_QryApThroughputPara(0);

    EXPECT_EQ(g_stAtE5CurrentRate.ulDLCurrentRate, 5);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_At_QryApDialModePara
功能描述 : Test_At_QryApDialModePara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_At_QryApDialModePara: public ::testing::Test
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
*测试项:          查询拨号模式
*被测函数功能描述:查询拨号模式
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年9月15日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryApDialModePara,Test_At_QryApDialModePara_01)
{
    g_stAtE5DialMode.ulDialMode = AT_E5_DEMAND_DIAL_MODE;

    /*MOCKER(At_sprintf)
        .expects(exactly(3));*/

    EXPECT_EQ(At_QryApDialModePara(0), AT_OK);

    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_At_QryApConnStPara
功能描述 : At_QryApConnStPara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_At_QryApConnStPara: public ::testing::Test
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
*测试项:          1.DIALING状态
*被测函数功能描述:查询E5拨号状态
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年9月15日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryApConnStPara,Test_At_QryApConnStPara_01)
{
    MOCKER(AT_E5GetState)
        .stubs()
        .will(returnValue(AT_PDP_STATE_ACTING));

    /*MOCKER(At_sprintf)
        .expects(exactly(2));*/

    EXPECT_EQ(At_QryApConnStPara(0), AT_OK);
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:          2DIALED状态
*被测函数功能描述:查询E5拨号状态
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年9月15日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryApConnStPara,Test_At_QryApConnStPara_02)
{
    MOCKER(AT_E5GetState)
        .stubs()
        .will(returnValue(AT_PDP_STATE_ACTED));

    /*MOCKER(At_sprintf)
        .expects(exactly(2));*/

    EXPECT_EQ(At_QryApConnStPara(0), AT_OK);
    GlobalMockObject::verify();
}


/*******************************************************************
*测试项:          3UNDIALED状态
*被测函数功能描述:查询E5拨号状态
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年9月15日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryApConnStPara,Test_At_QryApConnStPara_03)
{
    MOCKER(AT_E5GetState)
        .stubs()
        .will(returnValue(AT_PDP_STATE_IDLE));

    /*MOCKER(At_sprintf)
        .expects(exactly(2));*/

    EXPECT_EQ(At_QryApConnStPara(0), AT_OK);
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_QryDislogPara
功能描述 : AT_QryDislogPara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_AT_QryDislogPara: public ::testing::Test
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
*测试项:           Dislog值异常返回ERROR
*被测函数功能描述: DISLOG的查询函数
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年10月27日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryDislogPara, Test_AT_QryDislogPara_01)
{
    g_stATDislogPwd.lValue = AT_DIAG_OPEN_FLAG_BUTT;

    EXPECT_EQ(AT_QryDislogPara(0), AT_ERROR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:           Dislog值正常返回OK
*被测函数功能描述: DISLOG的查询函数
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年10月26日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryDislogPara, Test_AT_QryDislogPara_02)
{
    g_stATDislogPwd.lValue = AT_DIAG_OPEN_FLAG_OPEN;

    AT_DISLOG_PWD_STRU                  stTmpPwd;

    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/

    EXPECT_EQ(AT_QryDislogPara(0), AT_OK);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif  /* (FEATURE_ON == FEATURE_E5) */



/******************************************************************************
类名     : Test_At_QryClvlPara
功能描述 : At_QryClvlPara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_At_QryClvlPara: public ::testing::Test
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
*测试项:          查询音量等级
*被测函数功能描述:查询音量等级
*预期结果：       返回AT_OK
************************* 修改记录 *************************
#  1.日    期: 2010年10月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryClvlPara,Test_At_QryClvlPara_01)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRst;

    // 参数初始化
    ucIndex = 0;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(APP_VC_GetVoiceVolume)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRst = At_QryClvlPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN,ulRst);
    EXPECT_EQ(AT_CMD_CLVL_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:          查询音量等级
*被测函数功能描述:查询音量等级
*预期结果：       返回AT_ERROR
************************* 修改记录 *************************
#  1.日    期: 2010年10月13日
#    作    者: z00161729
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryClvlPara,Test_At_QryClvlPara_02)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRst;

    // 参数初始化
    ucIndex = 0;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(APP_VC_GetVoiceVolume)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRst = At_QryClvlPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR,ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



#ifdef FEATURE_SECURITY_SHELL

/******************************************************************************
类名     : Test_AT_QryShellPara
功能描述 : AT_QryShellPara UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_AT_QryShellPara: public ::testing::Test
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
*测试项:           SHELL值异常返回ERROR
*被测函数功能描述: AT^SHELL?的查询函数
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年10月26日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryShellPara, Test_AT_QryShellPara_01)
{
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_WRITE_SECURE_FAIL));

    EXPECT_EQ(AT_QryShellPara(0), AT_ERROR);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           SHELL值正常返回OK
*被测函数功能描述: AT^SHELL?的查询函数
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年10月26日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryShellPara, Test_AT_QryShellPara_02)
{

    VOS_UINT32                          ulShellStatus;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_SHELL,
    AT_SetShellPara,        AT_NOT_SET_TIME,  AT_QryShellPara,          AT_NOT_SET_TIME,   At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SHELL",       (VOS_UINT8*)"(0-2)"};

    g_stParseContext[0].pstCmdElement = &stCmdInfo;

    ulShellStatus                       = 2;

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_AT_SHELL_OPEN_FLAG),outBoundP((void *)&ulShellStatus, sizeof(ulShellStatus)),eq((VOS_UINT32)4))
        .will(returnValue((VOS_UINT32)NV_OK));

    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/


    EXPECT_EQ(AT_QryShellPara(0), AT_OK);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#endif

/*****************************************************************************
类名     : Test_At_QryCgattPara
功能描述 : CGATT命令查询处理函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : c00173809
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCgattPara: public ::testing::Test
{
public:
    VOS_UINT8       ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                 = 0;
        gastAtClientTab[ucIndex].usClientId     = 0;
        gastAtClientTab[ucIndex].opId           = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;
    }

    void TearDown()
    {
        ucIndex                                 = 0;
        gastAtClientTab[ucIndex].usClientId     = 0;
        gastAtClientTab[ucIndex].opId           = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;
    }
};
/*******************************************************************
测试用例编号      : Test_At_QryCgattPara_001
测试用例标题      : 发送查询CSPS状态消息成功
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCgattPara,Test_At_QryCgattPara_001)
{

    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 本地变量初始化 */

    /* 初始化全局变量 */

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_QryCgattPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_At_QryCgattPara_002
测试用例标题      : 发送查询CSPS状态消息失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCgattPara,Test_At_QryCgattPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 本地变量初始化 */

    /* 初始化全局变量 */

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_QryCgattPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_At_QryCgcattPara
功能描述 : CGCATT命令查询处理函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : c00173809
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCgcattPara: public ::testing::Test
{
public:
    VOS_UINT8       ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                 = 0;
        gastAtClientTab[ucIndex].usClientId     = 0;
        gastAtClientTab[ucIndex].opId           = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;
    }

    void TearDown()
    {
        ucIndex                                 = 0;
        gastAtClientTab[ucIndex].usClientId     = 0;
        gastAtClientTab[ucIndex].opId           = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;
    }
};
/*******************************************************************
测试用例编号      : Test_At_QryCgcattPara_001
测试用例标题      : 发送查询CSPS状态消息成功
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCgcattPara,Test_At_QryCgcattPara_001)
{

    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 本地变量初始化 */

    /* 初始化全局变量 */

    /* 函数打桩 */
    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_QryCgcattPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_At_QryCgcattPara_002
测试用例标题      : 发送查询CSPS状态消息失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCgcattPara,Test_At_QryCgcattPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 本地变量初始化 */

    /* 初始化全局变量 */

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_QryCgcattPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryRxDiv
功能描述 : 查询接收分集的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : c00173809
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryRxDiv: public ::testing::Test
{
public:
    VOS_UINT8       ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                       = 0;
        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        gastAtParaList[2].usParaLen   = 0;
        gastAtParaList[3].usParaLen   = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
    }

    void TearDown()
    {
        ucIndex                       = 0;
        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        gastAtParaList[2].usParaLen   = 0;
        gastAtParaList[3].usParaLen   = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
    }
};
/*******************************************************************
测试用例编号      : Test_At_QryRxDiv_001
测试用例标题      : 发送设置RXDIV消息失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryRxDiv,Test_At_QryRxDiv_001)
{
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    EXPECT_EQ(AT_ERROR, At_QryRxDiv(ucIndex));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_At_QryRxDiv002
测试用例标题      : 发送设置RXDIV消息成功
预期结果          : 返回等待异步消息
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryRxDiv,Test_At_QryRxDiv_002)
{
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, At_QryRxDiv(ucIndex));

    ASSERT_EQ(AT_CMD_DRV_AGENT_RXDIV_QRY_REQ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_At_QryCellSearch
功能描述 : 查询cell search的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : c00173809
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCellSearch: public ::testing::Test
{
public:
    VOS_UINT8       ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                       = 0;
        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        gastAtParaList[2].usParaLen   = 0;
        gastAtParaList[3].usParaLen   = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
    }

    void TearDown()
    {
        ucIndex                       = 0;
        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        gastAtParaList[2].usParaLen   = 0;
        gastAtParaList[3].usParaLen   = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
    }
};
/*******************************************************************
测试用例编号      : Test_At_QryCellSearch_001
测试用例标题      : 发送设置消息失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCellSearch,Test_At_QryCellSearch_001)
{
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    EXPECT_EQ(AT_ERROR, At_QryCellSearch(ucIndex));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_At_QryCellSearch_002
测试用例标题      : 发送设置消息成功
预期结果          : 返回等待异步消息
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCellSearch,Test_At_QryCellSearch_002)
{
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));


    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, At_QryCellSearch(ucIndex));

    ASSERT_EQ(AT_CMD_WAS_MNTN_QRY_CELLSRH, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_At_QryCuus1Para
功能描述 : 查询CUUS1函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : c00173809
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCuus1Para: public ::testing::Test
{
public:
    VOS_UINT8       ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                       = 0;
        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        gastAtParaList[2].usParaLen   = 0;
        gastAtParaList[3].usParaLen   = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
    }

    void TearDown()
    {
        ucIndex                       = 0;
        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        gastAtParaList[2].usParaLen   = 0;
        gastAtParaList[3].usParaLen   = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
    }
};
/*******************************************************************
测试用例编号      : Test_At_QryCuus1Para_001
测试用例标题      : 发送查询CUUS1消息成功
预期结果          : 返回等待异步结果
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCuus1Para,Test_At_QryCuus1Para_001)
{
    MOCKER(MN_CALL_SendAppRequest)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));


    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, At_QryCuus1Para(ucIndex));
    ASSERT_EQ(AT_CMD_APP_SET_UUSINFO_REQ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_At_QryCuus1Para_002
测试用例标题      : 发送查询CUUS1消息失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2011-10-13
作   者  :   c00173809
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCuus1Para,Test_At_QryCuus1Para_002)
{
    MOCKER(MN_CALL_SendAppRequest)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    EXPECT_EQ(AT_ERROR, At_QryCuus1Para(ucIndex));

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryAppWronReg
功能描述 : Test_At_QryAppWronReg UT工程类
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryAppWronReg: public ::testing::Test
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
测试用例编号      : Test_At_QryAppWronReg_001
测试用例标题      : 发送消息失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryAppWronReg, Test_At_QryAppWronReg_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ucIndex                       = 0;

    /* 函数打桩 */
    MOCKER(Taf_ParaQuery)
        .stubs()
        .with(any(),any(),eq((TAF_PARA_TYPE)ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ),any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_QryAppWronReg(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_At_QryAppWronReg_002
测试用例标题      : 发送消息成功
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryAppWronReg, Test_At_QryAppWronReg_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ucIndex                       = 0;

    /* 函数打桩 */
    MOCKER(Taf_ParaQuery)
        .stubs()
        .with(any(),any(),eq((TAF_PARA_TYPE)ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ),any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_QryAppWronReg(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    ASSERT_EQ(AT_CMD_REGISTER_TIME_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



/******************************************************************************
类名     : Test_AT_CalculateAntennaLevel
功能描述 : AT_CalculateAntennaLevel UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_AT_CalculateAntennaLevel: public ::testing::Test
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
*测试项:           level3
*被测函数功能描述: 根据rscp, Ecio, rssi来计算信号格数:g_ucMNPHAntennaLevel
*预期结果：   返回AT_ERROR
************************* 修改记录 ********************************
#  1.日    期: 2010年09月13日
#    作    者: w00167002
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_CalculateAntennaLevel,Test_AT_CalculateAntennaLevel_01)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_INT16                           sRscp;
    VOS_INT16                           sEcio;

    //参数赋值
    ucIndex = 0;
    sRscp = -96;
    sEcio = -10;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    //执行测试函数
    ASSERT_EQ(4, AT_CalculateAntennaLevel(sRscp, sEcio));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:           level2
*被测函数功能描述: 根据rscp, Ecio, rssi来计算信号格数:g_ucMNPHAntennaLevel
*预期结果：   返回AT_ERROR
************************* 修改记录 ********************************
#  1.日    期: 2010年09月13日
#    作    者: w00167002
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_CalculateAntennaLevel,Test_AT_CalculateAntennaLevel_02)
{
    // 参数定义
    VOS_UINT8       ucIndex;
    VOS_INT16                           sRscp;
    VOS_INT16                           sEcio;

    //参数赋值
    ucIndex = 0;
    sRscp = -102;
    sEcio = -13;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    //执行测试函数
    ASSERT_EQ(3, AT_CalculateAntennaLevel(sRscp, sEcio));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           level1
*被测函数功能描述: 根据rscp, Ecio, rssi来计算信号格数:g_ucMNPHAntennaLevel
*预期结果：   返回AT_ERROR
************************* 修改记录 ********************************
#  1.日    期: 2010年09月13日
#    作    者: w00167002
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_CalculateAntennaLevel,Test_AT_CalculateAntennaLevel_03)
{
// 参数定义
    VOS_UINT8       ucIndex;
    VOS_INT16                           sRscp;
    VOS_INT16                           sEcio;

    //参数赋值
    ucIndex = 0;
    sRscp = -108;
    sEcio = -16;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    //执行测试函数

    ASSERT_EQ(2, AT_CalculateAntennaLevel(sRscp, sEcio));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
*测试项:           level0
*被测函数功能描述: 根据rscp, Ecio, rssi来计算信号格数:g_ucMNPHAntennaLevel
*预期结果：   返回AT_ERROR
************************* 修改记录 ********************************
#  1.日    期: 2010年09月13日
#    作    者: w00167002
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_CalculateAntennaLevel,Test_AT_CalculateAntennaLevel_04)
{
// 参数定义
    VOS_UINT8       ucIndex;
    VOS_INT16                           sRscp;
    VOS_INT16                           sEcio;

    //参数赋值
    ucIndex = 0;
    sRscp = -109;
    sEcio = -17;

    //执行测试函数

    ASSERT_EQ(1, AT_CalculateAntennaLevel(sRscp, sEcio));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*****************************************************************************
 类名       : Test_AT_GetSmoothAntennaLevel
 功能描述   : AT_GetSmoothAntennaLevel UT工程类
 修改历史   :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新生成类
*****************************************************************************/
class Test_AT_GetSmoothAntennaLevel: public ::testing::Test
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
 测试用例编号   : Test_AT_GetSmoothAntennaLevel_001
 测试用例标题   : 丢网时立即更新
 预期结果       : 返回
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSmoothAntennaLevel,Test_AT_GetSmoothAntennaLevel_001)
{
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel;

    AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel = AT_CMD_ANTENNA_LEVEL_BUTT;

    /* 当前为无服务状态 */
    enLevel = AT_CMD_ANTENNA_LEVEL_0;

    AT_GetSmoothAntennaLevel(0,enLevel);

    EXPECT_EQ(AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel, AT_CMD_ANTENNA_LEVEL_0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_AT_GetSmoothAntennaLevel_002
 测试用例标题   : 丢网到有服务状态立即更新
 预期结果       : 返回
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSmoothAntennaLevel,Test_AT_GetSmoothAntennaLevel_002)
{
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel;

    /* 前状态是丢网 */
    AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel = AT_CMD_ANTENNA_LEVEL_0;

    /* 当前有服务信号1格 */
    enLevel = AT_CMD_ANTENNA_LEVEL_1;

    AT_GetSmoothAntennaLevel(0,enLevel);

    EXPECT_EQ(AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel, AT_CMD_ANTENNA_LEVEL_1);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_AT_GetSmoothAntennaLevel_003
 测试用例标题   : 与上次的信号格数比变化大于1格
 预期结果       : 返回
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSmoothAntennaLevel,Test_AT_GetSmoothAntennaLevel_003)
{
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel;

    AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel = AT_CMD_ANTENNA_LEVEL_BUTT;

    /* 上次信号1格 */
    AT_GetModemNetCtxAddrFromClientId(0)->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = 1;

    /* 本次信号3格 */
    enLevel = AT_CMD_ANTENNA_LEVEL_3;

    AT_GetSmoothAntennaLevel(0,enLevel);

    EXPECT_EQ(AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel, AT_CMD_ANTENNA_LEVEL_3);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_AT_GetSmoothAntennaLevel_004
 测试用例标题   : 与上次的信号格数比变化小过1格
 预期结果       : 返回
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSmoothAntennaLevel,Test_AT_GetSmoothAntennaLevel_004)
{
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel;

    AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel = AT_CMD_ANTENNA_LEVEL_BUTT;

    /* 上次信号1格 */
    AT_GetModemNetCtxAddrFromClientId(0)->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = 4;

    /* 本次信号3格 */
    enLevel = AT_CMD_ANTENNA_LEVEL_1;

    AT_GetSmoothAntennaLevel(0,enLevel);

    EXPECT_EQ(AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel, AT_CMD_ANTENNA_LEVEL_1);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_AT_GetSmoothAntennaLevel_005
 测试用例标题   : 格数波动则不更新
 预期结果       : 返回
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSmoothAntennaLevel,Test_AT_GetSmoothAntennaLevel_005)
{
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel;

    AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel = AT_CMD_ANTENNA_LEVEL_1;

    AT_GetModemNetCtxAddrFromClientId(0)->aenAntennaLevel[0] = AT_CMD_ANTENNA_LEVEL_0;
    AT_GetModemNetCtxAddrFromClientId(0)->aenAntennaLevel[1] = AT_CMD_ANTENNA_LEVEL_0;
    AT_GetModemNetCtxAddrFromClientId(0)->aenAntennaLevel[2] = AT_CMD_ANTENNA_LEVEL_1;

    /* 本次信号2格 */
    enLevel = AT_CMD_ANTENNA_LEVEL_2;

    AT_GetSmoothAntennaLevel(0,enLevel);

    EXPECT_EQ(AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel, AT_CMD_ANTENNA_LEVEL_1);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_AT_GetSmoothAntennaLevel_006
 测试用例标题   : 格数波动稳定了才更新
 预期结果       : 返回
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSmoothAntennaLevel,Test_AT_GetSmoothAntennaLevel_006)
{
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel;

    AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel = AT_CMD_ANTENNA_LEVEL_1;

    AT_GetModemNetCtxAddrFromClientId(0)->aenAntennaLevel[0] = AT_CMD_ANTENNA_LEVEL_1;
    AT_GetModemNetCtxAddrFromClientId(0)->aenAntennaLevel[1] = AT_CMD_ANTENNA_LEVEL_2;
    AT_GetModemNetCtxAddrFromClientId(0)->aenAntennaLevel[2] = AT_CMD_ANTENNA_LEVEL_2;

    /* 本次信号2格 */
    enLevel = AT_CMD_ANTENNA_LEVEL_2;

    AT_GetSmoothAntennaLevel(0,enLevel);

    EXPECT_EQ(AT_GetModemNetCtxAddrFromClientId(0)->enCalculateAntennaLevel, AT_CMD_ANTENNA_LEVEL_2);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryFreqLock
功能描述 : Test_At_QryFreqLock UT工程类
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryFreqLock: public ::testing::Test
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
测试用例编号      : Test_At_QryFreqLock_001
测试用例标题      : 发送消息失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFreqLock, Test_At_QryFreqLock_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ucIndex                       = 0;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),any(),eq((VOS_UINT16)ID_AT_MTA_WRR_FREQLOCK_QRY_REQ),any(), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_QryFreqLock(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryFreqLock_002
测试用例标题      : 发送消息成功
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFreqLock, Test_At_QryFreqLock_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ucIndex                       = 0;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),any(),eq((VOS_UINT16)ID_AT_MTA_WRR_FREQLOCK_QRY_REQ),any(), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_QryFreqLock(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    ASSERT_EQ(AT_CMD_FREQLOCK_QUERY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryRRCVersion
功能描述 : Test_At_QryRRCVersion UT工程类
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryRRCVersion: public ::testing::Test
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
测试用例编号      : Test_At_QryRRCVersion_001
测试用例标题      : 发送消息失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryRRCVersion, Test_At_QryRRCVersion_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ucIndex                       = 0;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),any(),eq((VOS_UINT16)ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ),any(), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_QryRRCVersion(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryRRCVersion_002
测试用例标题      : 发送消息成功
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryRRCVersion, Test_At_QryRRCVersion_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ucIndex                       = 0;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),any(),eq((VOS_UINT16)ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ),any(), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* 调用被测函数 */
    ulRst = At_QryRRCVersion(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    ASSERT_EQ(AT_CMD_RRC_VERSION_QUERY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryYjcxPara
功能描述 : Test_At_QryYjcxPara UT工程类
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryYjcxPara: public ::testing::Test
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
测试用例编号      : Test_At_QryYjcxPara_001
测试用例标题      : 发送消息失败
预期结果          : 函数给用户回复ERROR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryYjcxPara, Test_At_QryYjcxPara_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ucIndex                       = 0;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),any(),eq((VOS_UINT16)DRV_AGENT_YJCX_QRY_REQ),any(), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = At_QryYjcxPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryYjcxPara_002
测试用例标题      : 发送消息成功
预期结果          : 函数给用户回复AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2011-10-13
  作   者  : o00132663
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryYjcxPara, Test_At_QryYjcxPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ucIndex                       = 0;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),any(),eq((VOS_UINT16)DRV_AGENT_YJCX_QRY_REQ),any(), any(), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 调用被测函数 */
    ulRst = At_QryYjcxPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    ASSERT_EQ(AT_CMD_YJCX_QUERY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}





/*****************************************************************************
类名     : Test_AT_QryDloadInfoPara
功能描述 : Test_AT_QryDloadInfoPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryDloadInfoPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryDloadInfoPara_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryDloadInfoPara, Test_AT_QryDloadInfoPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    ucIndex                             = 0;
    pcLogStr                            = "AT_QryDloadInfoPara: AT_FillAndSndAppReqMsg fail.";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_DLOADINFO_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));


    // 调用被测函数
    ulRet = AT_QryDloadInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryDloadInfoPara_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryDloadInfoPara, Test_AT_QryDloadInfoPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_DLOADINFO_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryDloadInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_DLOADINFO_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryAuthorityVerPara
功能描述 : Test_AT_QryAuthorityVerPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryAuthorityVerPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryAuthorityVerPara_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAuthorityVerPara, Test_AT_QryAuthorityVerPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    ucIndex                             = 0;
    pcLogStr                            = "AT_QryAuthorityVerPara: AT_FillAndSndAppReqMsg fail.";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_AUTHORITYVER_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryAuthorityVerPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryAuthorityVerPara_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAuthorityVerPara, Test_AT_QryAuthorityVerPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_AUTHORITYVER_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryAuthorityVerPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_AUTHORITYVER_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryAuthorityIdPara
功能描述 : Test_AT_QryAuthorityIdPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryAuthorityIdPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryAuthorityIdPara_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAuthorityIdPara, Test_AT_QryAuthorityIdPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    ucIndex                             = 0;
    pcLogStr                            = "AT_QryAuthorityIdPara: AT_FillAndSndAppReqMsg fail.";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_AUTHORITYID_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryAuthorityIdPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryAuthorityIdPara_002
测试用例标题      : 发送消息到C核成功
预期结果          : 操作类型为AT_CMD_AUTHORITYID_READ，返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAuthorityIdPara, Test_AT_QryAuthorityIdPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_AUTHORITYID_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryAuthorityIdPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_AUTHORITYID_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

///*****************************************************************************
//类名     : Test_AT_QryHwnatQryPara
//功能描述 : Test_AT_QryHwnatQryPara UT工程类
//修改历史 :
//1.日   期  : 2011-10-13
//  修改内容 : 新生成类
// *****************************************************************************/
//class Test_AT_QryHwnatQryPara: public ::testing::Test
//{
//public:
//    void SetUp()
//    {
//        UT_STUB_INIT();
//
//    }
//    void TearDown()
//    {
//
//    }
//};
//
///*******************************************************************
//测试用例编号      : Test_AT_QryHwnatQryPara_001
//测试用例标题      : 发消息到C核失败
//预期结果          : 返回AT_ERROR
//修改历史          :
//1.日   期  : 2011-10-13
//  修改内容 : 新建CASE
// *******************************************************************/
//TEST_F(Test_AT_QryHwnatQryPara, Test_AT_QryHwnatQryPara_001)
//{
//    // 变量声明
//    VOS_UINT32                          ulRet;
//    VOS_UINT8                           ucIndex;
//    VOS_CHAR                           *pcLogStr;
//
//    //参数初始化
//    ucIndex                             = 0;
//    pcLogStr                            = "AT_QryHwnatQryPara: AT_FillAndSndAppReqMsg fail.";
//
//    // 初始化全局变量;
//
//    // MOCKER操作;
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .expects(exactly(1))
//        .with(any(), any(), eq(DRV_AGENT_HWNATQRY_QRY_REQ),
//              eq(VOS_NULL_PTR), eq(0), eq(WUEPS_PID_DRV_AGENT))
//        .will(returnValue(TAF_FAILURE));
//
//    MOCKER(DIAG_LogReport)
//        .expects(exactly(1))
//        .with(any(), any(), any(), any(), any(),
//              mirror(pcLogStr, (VOS_StrLen(pcLogStr) + 1)));
//
//    // 调用被测函数
//    ulRet = AT_QryHwnatQryPara(ucIndex);
//
//    // 执行检查
//    EXPECT_EQ(AT_ERROR, ulRet);
//
//    GlobalMockObject::verify();
//}
//
///*******************************************************************
//测试用例编号      : Test_AT_QryHwnatQryPara_002
//测试用例标题      : 发送消息到C核成功
//预期结果          : 返回AT_WAIT_ASYNC_RETURN
//修改历史          :
//1.日   期  : 2011-10-13
//  修改内容 : 新建CASE
// *******************************************************************/
//TEST_F(Test_AT_QryHwnatQryPara, Test_AT_QryHwnatQryPara_002)
//{
//    // 变量声明
//    VOS_UINT32                          ulRet;
//    VOS_UINT8                           ucIndex;
//
//    //参数初始化
//    ucIndex                             = 0;
//
//    // 初始化全局变量;
//
//    // MOCKER操作;
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .expects(exactly(1))
//        .with(any(), any(), eq(DRV_AGENT_HWNATQRY_QRY_REQ),
//              eq(VOS_NULL_PTR), eq(0), eq(WUEPS_PID_DRV_AGENT))
//        .will(returnValue(TAF_SUCCESS));
//
//    // 调用被测函数
//    ulRet = AT_QryHwnatQryPara(ucIndex);
//
//    // 执行检查
//    EXPECT_EQ(AT_CMD_HWNATQRY_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
//    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
//
//    GlobalMockObject::verify();
//}

/*****************************************************************************
类名     : Test_AT_QryFlashInfoPara
功能描述 : Test_AT_QryFlashInfoPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryFlashInfoPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryFlashInfoPara_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryFlashInfoPara, Test_AT_QryFlashInfoPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    ucIndex                             = 0;
    pcLogStr                            = "AT_QryFlashInfoPara: AT_FillAndSndAppReqMsg fail.";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_FLASHINFO_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryFlashInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryFlashInfoPara_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryFlashInfoPara, Test_AT_QryFlashInfoPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_FLASHINFO_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryFlashInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_FLASHINFO_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_AT_QryFeaturePara
功能描述 : Test_AT_QryFeaturePara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryFeaturePara: public ::testing::Test
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
测试用例编号      : Test_AT_QryFeaturePara_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryFeaturePara, Test_AT_QryFeaturePara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_SFEATURE_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryFeaturePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryFeaturePara_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryFeaturePara, Test_AT_QryFeaturePara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_SFEATURE_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryFeaturePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_SFEATURE_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryProdTypePara
功能描述 : Test_AT_QryProdTypePara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryProdTypePara: public ::testing::Test
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
测试用例编号      : Test_AT_QryProdTypePara_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryProdTypePara, Test_AT_QryProdTypePara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_PRODTYPE_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryProdTypePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryProdTypePara_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryProdTypePara, Test_AT_QryProdTypePara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_PRODTYPE_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryProdTypePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_PRODTYPE_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}


#if(FEATURE_ON == FEATURE_WIFI)

/*******************************************************************
测试用例编号      : Test_At_QrySecuBootFeaturePara_001
测试用例标题      : 发消息到C核失败
/*****************************************************************************
类名     : Test_AT_QryWifiPaRangePara
功能描述 : Test_AT_QryWifiPaRangePara UT工程类
修改历史     :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryWifiPaRangePara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
        stCmdInfo.ulCmdIndex        = AT_CMD_WIINFO;
        stCmdInfo.pfnSetProc        = AT_SetWifiPaRangePara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryWifiPaRangePara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^WIPARANGE";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(@gainmode)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};
#if 0
/*******************************************************************
测试用例编号      : Test_AT_QryWifiPaRangePara_001
测试用例标题      : 查询成功，当前模式为PA模式
预期结果          : 返回AT_OK
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryWifiPaRangePara, Test_AT_QryWifiPaRangePara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;

    /* 初始化变量 */
    pcExpactedStr = "^WIPARANGE:h";

    /* 全局变量赋值 */

    /* 桩函数 */
    MOCKER(wifi_get_pa_curMode)
        .will(returnValue(AT_WIFI_MODE_ONLY_PA));

    /* 调用消息入口函数 */
    ulRst = AT_QryWifiPaRangePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_QryWifiPaRangePara_002
测试用例标题      : 查询成功，当前模式为NOPA模式
预期结果          : 返回AT_OK
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryWifiPaRangePara, Test_AT_QryWifiPaRangePara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;

    /* 初始化变量 */
    pcExpactedStr = "^WIPARANGE:l";

    /* 全局变量赋值 */

    /* 桩函数 */
    MOCKER(wifi_get_pa_curMode)
        .will(returnValue(AT_WIFI_MODE_ONLY_NOPA));

    /* 调用消息入口函数 */
    ulRst = AT_QryWifiPaRangePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_QryWifiPaRangePara_003
测试用例标题      : 获取当前模式失败
预期结果          : 返回AT_ERROR
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryWifiPaRangePara, Test_AT_QryWifiPaRangePara_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;

    /* 全局变量赋值 */

    /* 桩函数 */
    MOCKER(wifi_get_pa_curMode)
        .will(returnValue(-1));

    /* 调用消息入口函数 */
    ulRst = AT_QryWifiPaRangePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#endif

#endif


/*****************************************************************************
类名     : Test_AT_QryNvResumePara
功能描述 : Test_AT_QryNvResumePara UT工程类
修改历史     :

1.日   期  : 2012-03-09
  作   者  : L60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryNvResumePara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
        stCmdInfo.ulCmdIndex        = AT_CMD_QRYNVRESUME;
        stCmdInfo.pfnSetProc        = VOS_NULL_PTR;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryLocinfoPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^QRYNVRESUME";
        stCmdInfo.pszParam          = VOS_NULL_PTR;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};

/*******************************************************************
测试用例编号      : Test_AT_QryNvResumePara_001
测试用例标题      : 读NV失败
预期结果          : 返回AT_ERROR
修改历史   :

1.日   期  : 2012-03-09
  作   者  : L60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNvResumePara, Test_AT_QryNvResumePara_001)
{
     /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_UINT16                          usNvResumeFlag;

    /* 初始化变量 */

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gastAtClientTab[ucIndex].opId       = 0;

    /* 桩函数 */
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),eq((VOS_UINT16)en_NV_Resume_Flag),any(),any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /* 调用消息入口函数 */
    ulRst = AT_QryNvResumePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_AT_QryNvResumePara_002
测试用例标题      : 读NV成功，返回值为2
预期结果          : 返回AT_ERROR
修改历史   :

1.日   期  : 2012-03-09
  作   者  : L60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNvResumePara, Test_AT_QryNvResumePara_002)
{
     /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_UINT16                          usNvResumeFlag;

    /* 初始化变量 */

    usNvResumeFlag = 2;

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gastAtClientTab[ucIndex].opId       = 0;

    /* 桩函数 */
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),eq((VOS_UINT16)en_NV_Resume_Flag),outBoundP((void *)&usNvResumeFlag),eq((VOS_UINT32)2))
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 调用消息入口函数 */
    ulRst = AT_QryNvResumePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_AT_QryNvResumePara_003
测试用例标题      : 读NV成功，返回值为AT_NV_RESUME_SUCC
预期结果          : 返回AT_ERROR
修改历史   :

1.日   期  : 2012-03-09
  作   者  : L60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNvResumePara, Test_AT_QryNvResumePara_003)
{
     /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_UINT16                          usNvResumeFlag;

    /* 初始化变量 */

    usNvResumeFlag = AT_NV_RESUME_SUCC;

    /* 全局变量赋值 */
    gastAtClientTab[ucIndex].usClientId = 0;
    gastAtClientTab[ucIndex].opId       = 0;

    /* 桩函数 */
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),eq((VOS_UINT16)en_NV_Resume_Flag),outBoundP((void *)&usNvResumeFlag),eq((VOS_UINT32)2))
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 调用消息入口函数 */
    ulRst = AT_QryNvResumePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);

    EXPECT_EQ(VOS_StrLen("^QRYNVRESUME:0"), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QrySecuBootFeaturePara
功能描述 : At_QrySecuBootFeaturePara UT工程类
修改历史 :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QrySecuBootFeaturePara: public ::testing::Test
{
public:
    AT_PAR_CMD_ELEMENT_STRU                 stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));

        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^SECUBOOTFEATURE";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }
    void TearDown()
    {

    }

    VOS_UINT8       ucIndex;
};

/*******************************************************************
测试用例编号      : Test_At_QrySecuBootFeaturePara_001
测试用例标题      : 读取NV项失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
2.日    期 : 2012年08月08日
  作    者 : y00213812
  修改内容 : 根据V7R1C50_AR_DRV_FLASHLESS_22修改，直接读取NV项
*******************************************************************/
TEST_F(Test_At_QrySecuBootFeaturePara, Test_At_QrySecuBootFeaturePara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SEC_BOOT_FLAG), any(), any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulRet = At_QrySecuBootFeaturePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QrySecuBootFeaturePara_002
测试用例标题      : 读取NV项成功，打印输出
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
2.日    期 : 2012年08月08日
  作    者 : y00213812
  修改内容 : 根据V7R1C50_AR_DRV_FLASHLESS_22修改，直接读取NV项

*******************************************************************/
TEST_F(Test_At_QrySecuBootFeaturePara, Test_At_QrySecuBootFeaturePara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usNVSecBootEnableFlag;
    VOS_CHAR                           *pcInput;

    //参数初始化
    usNVSecBootEnableFlag               = 1;
    pcInput                             = "^SECUBOOTFEATURE: 1";
    // 初始化全局变量;
    gstAtSendData.usBufLen              = 0;
    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SEC_BOOT_FLAG), outBoundP((void *)&usNVSecBootEnableFlag), eq((VOS_UINT32)2))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = At_QrySecuBootFeaturePara(ucIndex);

    // 执行检查
    EXPECT_EQ(strlen(pcInput), gstAtSendData.usBufLen);
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QrySecuBootPara
功能描述 : Test_At_QrySecuBootPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QrySecuBootPara: public ::testing::Test
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
测试用例编号      : Test_At_QrySecuBootPara_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QrySecuBootPara, Test_At_QrySecuBootPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_SECUBOOT_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = At_QrySecuBootPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QrySecuBootPara_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QrySecuBootPara, Test_At_QrySecuBootPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_SECUBOOT_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = At_QrySecuBootPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_SECUBOOT_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryVersion
功能描述 : Test_At_QryVersion UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryVersion: public ::testing::Test
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
测试用例编号      : Test_At_QryVersion_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryVersion, Test_At_QryVersion_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_VERSION_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = At_QryVersion(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryVersion_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryVersion, Test_At_QryVersion_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_VERSION_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = At_QryVersion(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_VERSION_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryTModePara
功能描述 : Test_At_QryTModePara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryTModePara: public ::testing::Test
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
测试用例编号      : Test_At_QryTModePara_002
测试用例标题      : 当前设备制式是GU模，查询当前TMODE的执行状态
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryTModePara, Test_At_QryTModePara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcPrintStr;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_TMODE,          At_SetTModePara,
                                                     AT_SET_PARA_TIME,      At_QryTModePara,
                                                     AT_QRY_PARA_TIME ,     At_TestTmodePara ,
                                                     AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                     AT_CME_INCORRECT_PARAMETERS,
                                                     CMD_TBL_PIN_IS_LOCKED, (VOS_UINT8*)"^TMODE",
                                                     (VOS_UINT8*)"(0-7)"};

    //参数初始化
    ucIndex                             = 0;
    pcPrintStr                          = "^TMODE:1";
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    // 初始化全局变量;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;

    // MOCKER操作;

    // 调用被测函数
    ulRet = At_QryTModePara(ucIndex);

    // 执行检查
    EXPECT_EQ(VOS_StrLen(pcPrintStr), gstAtSendData.usBufLen);
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_E5)
/*****************************************************************************
类名     : Test_AT_QryBatVolPara
功能描述 : Test_AT_QryBatVolPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryBatVolPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryBatVolPara_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBatVolPara, Test_AT_QryBatVolPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_TBATVOLT_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryBatVolPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_AT_QryBatVolPara_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBatVolPara, Test_AT_QryBatVolPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_TBATVOLT_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryBatVolPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_TBATVOLT_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}
#endif
/*****************************************************************************
类名     : Test_At_QryGPIOPL
功能描述 : Test_At_QryGPIOPL UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryGPIOPL: public ::testing::Test
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
测试用例编号      : Test_At_QryGPIOPL_001
测试用例标题      : 发消息到C核失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryGPIOPL, Test_At_QryGPIOPL_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_GPIOPL_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = At_QryGPIOPL(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryGPIOPL_002
测试用例标题      : 发送消息到C核成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryGPIOPL, Test_At_QryGPIOPL_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)DRV_AGENT_GPIOPL_QRY_REQ),
              eq((void *)VOS_NULL_PTR), eq((VOS_UINT32)0), eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = At_QryGPIOPL(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_GPIOPL_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryFrssiPara
功能描述 : Test_At_QryFrssiPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryFrssiPara: public ::testing::Test
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
测试用例编号      : Test_At_QryFrssiPara_001
测试用例标题      : 当前设备制式为L模
预期结果          : 调用L模对应的接口，返回接口的返回值
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFrssiPara, Test_At_QryFrssiPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    g_stAtDevCmdCtrl.ucCurrentTMode     = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.bDspLoadFlag       = VOS_TRUE;
    g_stAtDevCmdCtrl.ucRxOnOff          = AT_DSP_RF_SWITCH_ON;
    g_stAtDevCmdCtrl.ucDeviceRatMode    = AT_RAT_MODE_FDD_LTE;

    // MOCKER操作
    MOCKER(atQryFRSSIPara)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_WAIT_ASYNC_RETURN));

    // 调用被测函数
    ulRet = At_QryFrssiPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryFrssiPara_002
测试用例标题      : lTE宏关闭，GSM模式下，发送到modem0的PID
预期结果          : 返回接口的返回值
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFrssiPara, Test_At_QryFrssiPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stAtDevCmdCtrl.ucCurrentTMode     = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.bDspLoadFlag       = VOS_TRUE;
    g_stAtDevCmdCtrl.ucRxOnOff          = AT_DSP_RF_SWITCH_ON;
    g_stAtDevCmdCtrl.ucDeviceRatMode    = AT_RAT_MODE_GSM;

    // MOCKER操作
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq((MN_CLIENT_ID_T)ucIndex), eq((VOS_UINT32)I0_DSP_PID_GPHY))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = At_QryFrssiPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_At_QryFlnaPara
功能描述 : Test_At_QryFlnaPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryFlnaPara: public ::testing::Test
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
#if(FEATURE_LTE == FEATURE_ON)
/*******************************************************************
测试用例编号      : Test_At_QryFlnaPara_001
测试用例标题      : 当前设备制式为L模
预期结果          : 调用L模对应的接口，返回接口的返回值
修改历史          :
1.日   期  : 2011-10-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFlnaPara, Test_At_QryFlnaPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    g_stAtDevCmdCtrl.ucCurrentTMode     = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucDeviceRatMode    = AT_RAT_MODE_FDD_LTE;

    // MOCKER操作
    MOCKER(atQryFLNAPara)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_WAIT_ASYNC_RETURN));

    // 调用被测函数
    ulRet = At_QryFlnaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}
#endif
/*****************************************************************************
类名     : Test_AT_QryCgdcontPara
功能描述 : Test_AT_QryCgdcontPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCgdcontPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryCgdcontPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCgdcontPara, Test_AT_QryCgdcontPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryCgdcontPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGDCONT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryCgactPara
功能描述 : Test_AT_QryCgactPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCgactPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryCgactPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCgactPara, Test_AT_QryCgactPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_PDP_CONTEXT_STATE_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_PDP_STATE_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryCgactPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGACT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryCgeqreqPara
功能描述 : Test_AT_QryCgeqreqPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCgeqreqPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryCgeqreqPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCgeqreqPara, Test_AT_QryCgeqreqPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryCgeqreqPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGEQREQ_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryCgeqminPara
功能描述 : Test_At_QryCgeqminPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCgeqminPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCgeqminPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCgeqminPara, Test_At_QryCgeqminPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = At_QryCgeqminPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGEQMIN_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryCgdscontPara
功能描述 : Test_AT_QryCgdscontPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCgdscontPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryCgdscontPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCgdscontPara, Test_AT_QryCgdscontPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryCgdscontPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGDSCONT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryCgdnsPara
功能描述 : Test_AT_QryCgdnsPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCgdnsPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryCgdnsPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCgdnsPara, Test_AT_QryCgdnsPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_PDP_DNS_INFO_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryCgdnsPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGDNS_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryCgautoPara
功能描述 : Test_AT_QryCgautoPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCgautoPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryCgautoPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCgautoPara, Test_AT_QryCgautoPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_ANSWER_MODE_INFO_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryCgautoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGAUTO_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryCgauthPara
功能描述 : Test_AT_QryCgauthPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCgauthPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryCgauthPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCgauthPara, Test_AT_QryCgauthPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_PDP_AUTH_INFO_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryCgauthPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGAUTH_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryCgtftPara
功能描述 : Test_AT_QryCgtftPara UT工程类
修改历史 :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCgtftPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryCgtftPara_001
测试用例标题      : 成功执行命令操作
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2011-10-28
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCgtftPara, Test_AT_QryCgtftPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)WUEPS_PID_TAF), eq((VOS_UINT32)ID_MSG_TAF_PS_GET_TFT_INFO_REQ),
              any(), eq((VOS_UINT32)sizeof(TAF_PS_GET_TFT_INFO_REQ_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryCgtftPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CGTFT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}




/*****************************************************************************
类名     : Test_AT_QryRsimPara
功能描述 : Test_AT_QryRsimPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
作   者  : w00181244
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryRsimPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
        g_stParseContext[ucIndex].pstCmdElement = &gstRsimCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};

/*******************************************************************
 测试用例编号      : Test_AT_QryRsimPara_001
 测试用例标题      : 通过ModemId失败，默认Modem0
 预期结果          : 继续执行函数
 修改历史     :
 1.日   期  : 2013-01-10
   作   者  : l00227485
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRsimPara, Test_AT_QryRsimPara_001)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_QryRsimPara(ucIndex);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryRsimPara_002
测试用例标题      : 卡类型为USIMM_CARD_USIM，卡状态为USIMM_CARD_SERVIC_AVAILABLE
预期结果          : 返回1,AT_OK,符合格式
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRsimPara, Test_AT_QryRsimPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_RSIM, VOS_NULL_PTR,
                                                     AT_NOT_SET_TIME,    AT_QryRsimPara,
                                                     AT_NOT_SET_TIME,    VOS_NULL_PTR ,
                                                     AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                     AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^RSIM", VOS_NULL_PTR};
    VOS_CHAR                           *pcExpactedStr;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx = VOS_NULL_PTR;

    pstAtModemCtx = AT_GetModemCtxAddr(MODEM_ID_0);

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    pstAtModemCtx->stAtUsimInfoCtx.enCardType = USIMM_CARD_USIM;
    pstAtModemCtx->stAtUsimInfoCtx.enCardStatus = USIMM_CARD_SERVIC_AVAILABLE;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    pcExpactedStr = "^RSIM:1";

    /*调用被测函数 */
    ulRet = AT_QryRsimPara(ucIndex);

    /*执行检查*/
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryRsimPara_003
测试用例标题      : 卡类型为USIMM_CARD_ROM_SIM，卡状态为USIMM_CARD_SERVIC_ABSENT
预期结果          : 返回0,AT_OK,符合格式
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRsimPara, Test_AT_QryRsimPara_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_RSIM, VOS_NULL_PTR,
                                                     AT_NOT_SET_TIME,    AT_QryRsimPara,
                                                     AT_NOT_SET_TIME,    VOS_NULL_PTR ,
                                                     AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                     AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^RSIM", VOS_NULL_PTR};
    VOS_CHAR                           *pcExpactedStr;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx = VOS_NULL_PTR;

    pstAtModemCtx = AT_GetModemCtxAddr(MODEM_ID_0);

    pcExpactedStr = "^RSIM:0";

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    pstAtModemCtx->stAtUsimInfoCtx.enCardType = USIMM_CARD_ROM_SIM;
    pstAtModemCtx->stAtUsimInfoCtx.enCardStatus = USIMM_CARD_SERVIC_ABSENT;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    /*调用被测函数 */
    ulRet = AT_QryRsimPara(ucIndex);

    /*执行检查*/
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_QryRsimPara_004
测试用例标题      : 卡类型为USIMM_CARD_TYPE_BUTT，卡状态为USIMM_CARD_SERVIC_BUTT
预期结果          : 返回2,AT_OK,符合格式
修改历史          :
1.日   期  : 2012-05-05
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRsimPara, Test_AT_QryRsimPara_004)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_RSIM, VOS_NULL_PTR,
                                                     AT_NOT_SET_TIME,    AT_QryRsimPara,
                                                     AT_NOT_SET_TIME,    VOS_NULL_PTR ,
                                                     AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                     AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^RSIM", VOS_NULL_PTR};
    VOS_CHAR                           *pcExpactedStr;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx = VOS_NULL_PTR;

    pstAtModemCtx = AT_GetModemCtxAddr(MODEM_ID_0);

    pcExpactedStr = "^RSIM:2";

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    pstAtModemCtx->stAtUsimInfoCtx.enCardStatus = USIMM_CARD_SERVIC_BUTT;
    pstAtModemCtx->stAtUsimInfoCtx.enCardType = USIMM_CARD_TYPE_BUTT;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    /*调用被测函数 */
    ulRet = AT_QryRsimPara(ucIndex);

    /*执行检查*/
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_AT_QryPhyNumPara
功能描述 : Test_AT_QryPhyNumPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
作   者  : w00181244
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryPhyNumPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryPhyNumPara_001
测试用例标题      : 获取IMSI失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhyNumPara, Test_AT_QryPhyNumPara_001)
{
    /*变量定义*/
    VOS_UINT8                           aucAsciiImei[TAF_PH_IMEI_LEN + 1];
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*本地变量初始化*/
    ucIndex = 0;

    /*函数打桩*/
    PS_MEM_CPY(aucAsciiImei, "12345678901234", (strlen("12345678901234") + 1));
    MOCKER(AT_GetImeiValue)
        .stubs()
        .with(any(), outBoundP(aucAsciiImei, sizeof(aucAsciiImei)))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /*调用被测函数 */
    ulRet = AT_QryPhyNumPara(ucIndex);

    /*执行检查*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_GetImeiValue_002
测试用例标题      : 获取SVN值失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhyNumPara, Test_AT_QryPhyNumPara_002)
{
    /*变量定义*/
    VOS_UINT8                           aucAsciiImei[TAF_PH_IMEI_LEN + 1];
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*本地变量初始化*/
    ucIndex = 0;

    /*函数打桩*/
    PS_MEM_CPY(aucAsciiImei, "12345678901234", (strlen("12345678901234") + 1));
    MOCKER(AT_GetImeiValue)
        .stubs()
        .with(any(), outBoundP(aucAsciiImei, sizeof(aucAsciiImei)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /*调用被测函数 */
    ulRet = AT_QryPhyNumPara(ucIndex);

    /*执行检查*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetImeiValue_003
测试用例标题      : 获取IMSI和SVN都成功
预期结果          : 按格式返回输出
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhyNumPara, Test_AT_QryPhyNumPara_003)
{
    /*变量定义*/
    VOS_UINT8                           aucAsciiImei[TAF_PH_IMEI_LEN + 1];
    VOS_UINT32                          ulRet;
    TAF_SVN_DATA_STRU                   stSvn;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucMac[] = "7AFEE22111E4";
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_PHYNUM, AT_SetPhyNumPara,
                                                     AT_NOT_SET_TIME,    AT_QryPhyNumPara,
                                                     AT_NOT_SET_TIME,   VOS_NULL_PTR ,
                                                     AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR,      AT_NOT_SET_TIME,
                                                     AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^PHYNUM",   VOS_NULL_PTR};

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    /*函数打桩*/
    PS_MEM_CPY(aucAsciiImei, "12345678901234", (strlen("12345678901234") + 1));
    MOCKER(AT_GetImeiValue)
        .stubs()
        .with(any(), outBoundP(aucAsciiImei, sizeof(aucAsciiImei)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_QryPhyNumPara(ucIndex);

    /*执行检查*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryFTxonPara
功能描述 : Test_At_QryFTxonPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
作   者  : w00181244
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryFTxonPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    }
    void TearDown()
    {

    }
};

#if(FEATURE_LTE == FEATURE_ON)
/*******************************************************************
测试用例编号      : Test_At_QryFTxonPara_001
测试用例标题      : 当前接入模式为AT_RAT_MODE_FDD_LTE
预期结果          : 返回LTE模的接口atQryFTXONPara的返回结果
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFTxonPara, Test_At_QryFTxonPara_001)
{
    /*变量定义*/
    VOS_UINT8                        ucIndex;
    VOS_UINT32                       ulRet;

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_FDD_LTE;

    /*调用被测函数 */
    ulRet = At_QryFTxonPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_SUCCESS, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryFTxonPara_002
测试用例标题      : 当前接入模式为AT_RAT_MODE_TDD_LTE
预期结果          : 返回LTE模的接口atQryFTXONPara的返回结果
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFTxonPara, Test_At_QryFTxonPara_002)
{
    /*变量定义*/
    VOS_UINT8                        ucIndex;
    VOS_UINT32                       ulRet;

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_TDD_LTE;


    /*调用被测函数 */
    ulRet = At_QryFTxonPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_SUCCESS, ulRet);
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_At_QryFTxonPara_003
测试用例标题      : 当前接入模式为AT_RAT_MODE_WCDMA
预期结果          : 返回g_stAtDevCmdCtrl.ucTxOnOff的值
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFTxonPara, Test_At_QryFTxonPara_003)
{
    /*变量定义*/
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_FTXON,
                                                     At_SetFTxonPara,     AT_SET_PARA_TIME,
                                                     At_QryFTxonPara,       AT_QRY_PARA_TIME,
                                                     VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                     AT_FTXON_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^FTXON",    (VOS_UINT8*)"(0,1,2)"};
    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    /*调用被测函数 */
    ulRet = At_QryFTxonPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}



/*****************************************************************************
类名     : Test_At_QryFRxonPara
功能描述 : Test_At_QryFRxonPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
作   者  : w00181244
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryFRxonPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    }
    void TearDown()
    {

    }
};

#if(FEATURE_LTE == FEATURE_ON)
/*******************************************************************
测试用例编号      : Test_At_QryFRxonPara_001
测试用例标题      : 当前接入模式为AT_RAT_MODE_FDD_LTE
预期结果          : 返回LTE模的接口atQryFRXONPara的返回结果
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFRxonPara, Test_At_QryFRxonPara_001)
{
    /*变量定义*/
    VOS_UINT8                        ucIndex;
    VOS_UINT32                       ulRet;

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_FDD_LTE;


    /*调用被测函数 */
    ulRet = At_QryFRxonPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_SUCCESS, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryFRxonPara_002
测试用例标题      : 当前接入模式为AT_RAT_MODE_TDD_LTE
预期结果          : 返回LTE模的接口atQryFRXONPara的返回结果
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFRxonPara, Test_At_QryFRxonPara_002)
{
    /*变量定义*/
    VOS_UINT8                        ucIndex;
    VOS_UINT32                       ulRet;

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_TDD_LTE;

    /*调用被测函数 */
    ulRet = At_QryFRxonPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_SUCCESS, ulRet);
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_At_QryFRxonPara_003
测试用例标题      : 当前接入模式为AT_RAT_MODE_WCDMA
预期结果          : 返回g_stAtDevCmdCtrl.ucRxOnOff的值
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFRxonPara, Test_At_QryFRxonPara_003)
{
    /*变量定义*/
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_FRXON,
                                                     At_SetFRxonPara,     AT_SET_PARA_TIME,
                                                     At_QryFRxonPara,       AT_QRY_PARA_TIME,
                                                     VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                     AT_FRXON_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^FRXON",    (VOS_UINT8*)"(0-1)"};
    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    /*调用被测函数 */
    ulRet = At_QryFRxonPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}



/*****************************************************************************
类名     : Test_At_QryFChanPara
功能描述 : Test_At_QryFChanPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
作   者  : w00181244
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryFChanPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    }
    void TearDown()
    {

    }
};

#if (FEATURE_LTE == FEATURE_ON)
/*******************************************************************
测试用例编号      : Test_At_QryFChanPara_001
测试用例标题      : 当前接入模式为AT_RAT_MODE_FDD_LTE
预期结果          : 返回LTE模的接口atQryFFCHANSPara的返回结果
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFChanPara, Test_At_QryFChanPara_001)
{
    /*变量定义*/
    VOS_UINT8                        ucIndex;
    VOS_UINT32                       ulRet;

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_FDD_LTE;


    /*调用被测函数 */
    ulRet = At_QryFChanPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_SUCCESS, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryFChanPara_002
测试用例标题      : 当前接入模式为AT_RAT_MODE_TDD_LTE
预期结果          : 返回LTE模的接口atQryFFCHANSPara的返回结果
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFChanPara, Test_At_QryFChanPara_002)
{
    /*变量定义*/
    VOS_UINT8                        ucIndex;
    VOS_UINT32                       ulRet;

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_TDD_LTE;

    /*调用被测函数 */
    ulRet = At_QryFChanPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_SUCCESS, ulRet);
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_At_QryFChanPara_003
测试用例标题      : 当前接入模式为AT_RAT_MODE_WCDMA
预期结果          : 按格式返回
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryFChanPara, Test_At_QryFChanPara_003)
{
    /*变量定义*/
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_FCHAN,
                                                     At_SetFChanPara,     AT_SET_PARA_TIME,
                                                     At_QryFChanPara,       AT_QRY_PARA_TIME,
                                                     VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                     AT_FCHAN_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^FCHAN",    (VOS_UINT8*)"(0-7),(0-10),(0-65535)"};

    /*本地变量初始化*/
    ucIndex = 0;

    /*全局变量初始化*/
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;
    g_stAtDevCmdCtrl.ucDeviceAtBand = AT_BAND_2100M;
    g_stAtDevCmdCtrl.stDspBandArfcn.usUlArfcn = 46009;
    g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn = 20056;

    /*调用被测函数 */
    ulRet = At_QryFChanPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}

#if 0
/*****************************************************************************
类名     : Test_At_QryCsdfltPara
功能描述 : Test_At_QryCsdfltPara UT工程类
修改历史 :
1.日   期  : 2011-10-13
作   者  : w00181244
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCsdfltPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCsdfltPara_001
测试用例标题      : 读NV失败
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdfltPara, Test_At_QryCsdfltPara_001)
{
    /*变量定义*/
    VOS_UINT32                                  ulRet;
    VOS_BOOL                                    pbActiveFlg = VOS_NULL;

    /*本地变量初始化*/

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /*调用被测函数 */
    ulRet = AT_GetSimLockStatus(&pbActiveFlg);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCsdfltPara_002
测试用例标题      : 读NV成功，但PLMN校验失败
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdfltPara, Test_At_QryCsdfltPara_002)
{
    /*变量定义*/
    VOS_UINT32                                  ulRet;
    VOS_BOOL                                    pbActiveFlg = VOS_NULL;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(AT_IsSimLockPlmnInfoValid)
        .stubs()
        .will(returnValue(VOS_FALSE));

    /*调用被测函数 */
    ulRet = AT_GetSimLockStatus(&pbActiveFlg);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCsdfltPara_003
测试用例标题      : 获取simlock status失败
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdfltPara, Test_At_QryCsdfltPara_003)
{
    /*变量定义*/
    VOS_UINT32                           ulRet;
    VOS_BOOL                             pbSimLockStatus = VOS_NULL;
    VOS_UINT16                           pusValueInfo = VOS_NULL;

    /*函数打桩*/
    MOCKER(AT_GetSimLockStatus)
        .stubs()
        .with(outBoundP((void *)&pbSimLockStatus))
        .will(returnValue(VOS_ERR));

    /*调用被测函数 */
    ulRet = At_ReadCustomizeSimLockNV(&pbSimLockStatus, &pusValueInfo);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCsdfltPara_004
测试用例标题      : 获取simlock status成功，pusValueInfo = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdfltPara, Test_At_QryCsdfltPara_004)
{
    /*变量定义*/
    VOS_UINT32                           ulRet;
    VOS_BOOL                             pbSimLockStatus = VOS_NULL;
    VOS_UINT16                           pusValueInfo = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;

    /*函数打桩*/
    MOCKER(AT_GetSimLockStatus)
        .stubs()
        .with(outBoundP((void *)&pbSimLockStatus))
        .will(returnValue(VOS_OK));

    /*调用被测函数 */
    ulRet = At_ReadCustomizeSimLockNV(&pbSimLockStatus, &pusValueInfo);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCsdfltPara_005
测试用例标题      : 获取SIM Lock Status定制项的值并检查是否为默认值失败
预期结果          : 返回AT_DEVICE_OTHER_ERROR
修改历史          :
1.日   期  : 2011-10-14
作   者  : w00181244
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdfltPara, Test_At_QryCsdfltPara_005)
{
    /*变量定义*/
    VOS_UINT32                           ulRet;
    VOS_UINT8                            ucIndex;
    VOS_BOOL                             bSimLockStatus;
    VOS_UINT16                           usValueInfo;

    /*本地变量初始化*/
    ucIndex = 0;
    bSimLockStatus = VOS_NULL;
    usValueInfo    = VOS_NULL;

    /*函数打桩*/
    MOCKER(At_ReadCustomizeSimLockNV)
        .stubs()
        .with(outBoundP((void *)&bSimLockStatus), outBoundP((void *)&usValueInfo))
        .will(returnValue(VOS_ERR));

    /*调用被测函数 */
    ulRet = At_QryCsdfltPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_DEVICE_OTHER_ERROR, ulRet);
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_AT_QryNvBackupStatusPara
功能描述 : AT_QryNvBackupStatusPara UT工程类
修改历史 :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryNvBackupStatusPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex     = 0;
        gastAtClientTab[ucIndex].usClientId = 0;
        gastAtClientTab[ucIndex].opId       = 0;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryNvBackupStatusPara_001
测试用例标题      : 查询NV备份状态命令下发成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNvBackupStatusPara, Test_AT_QryNvBackupStatusPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_NVBACKUPSTAT_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /*调用被测函数 */
    ulRet = AT_QryNvBackupStatusPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_NVBACKUPSTAT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryNvBackupStatusPara_002
测试用例标题      : 给DRV AGENT模块发消息失败
预期结果          : 返回AT_ERROR
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNvBackupStatusPara, Test_AT_QryNvBackupStatusPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_NVBACKUPSTAT_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /*调用被测函数 */
    ulRet = AT_QryNvBackupStatusPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryNandBadBlockPara
功能描述 : AT_QryNandBadBlockPara UT工程类
修改历史 :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryNandBadBlockPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex     = 0;
        gastAtClientTab[ucIndex].usClientId = 0;
        gastAtClientTab[ucIndex].opId       = 0;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryNandBadBlockPara_001
测试用例标题      : 查询NAND FLASH的所有坏块索引列表命令下发成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNandBadBlockPara, Test_AT_QryNandBadBlockPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_NANDBBC_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /*调用被测函数 */
    ulRet = AT_QryNandBadBlockPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_NANDBBC_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryNandBadBlockPara_002
测试用例标题      : 给DRV AGENT模块发消息失败
预期结果          : 返回AT_ERROR
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNandBadBlockPara, Test_AT_QryNandBadBlockPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_NANDBBC_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /*调用被测函数 */
    ulRet = AT_QryNandBadBlockPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryNandDevInfoPara
功能描述 : AT_QryNandDevInfoPara UT工程类
修改历史 :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryNandDevInfoPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex     = 0;
        gastAtClientTab[ucIndex].usClientId = 0;
        gastAtClientTab[ucIndex].opId       = 0;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryNandDevInfoPara_001
测试用例标题      : 查询NAND FLASH的型号信息命令下发成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNandDevInfoPara, Test_AT_QryNandDevInfoPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_NANDVER_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /*调用被测函数 */
    ulRet = AT_QryNandDevInfoPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_NANDVER_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryNandDevInfoPara_002
测试用例标题      : 给DRV AGENT模块发消息失败
预期结果          : 返回AT_ERROR
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryNandDevInfoPara, Test_AT_QryNandDevInfoPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_NANDVER_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /*调用被测函数 */
    ulRet = AT_QryNandDevInfoPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryChipTempPara
功能描述 : AT_QryChipTempPara UT工程类
修改历史 :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryChipTempPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex     = 0;
        gastAtClientTab[ucIndex].usClientId = 0;
        gastAtClientTab[ucIndex].opId       = 0;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryChipTempPara_001
测试用例标题      : 查询PA、SIM卡和电池的温度信息命令下发成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryChipTempPara, Test_AT_QryChipTempPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_CHIPTEMP_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /*调用被测函数 */
    ulRet = AT_QryChipTempPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_CHIPTEMP_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryChipTempPara_002
测试用例标题      : 给DRV AGENT模块发消息失败
预期结果          : 返回AT_ERROR
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryChipTempPara, Test_AT_QryChipTempPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_CHIPTEMP_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /*调用被测函数 */
    ulRet = AT_QryChipTempPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryCpuLoadPara
功能描述 : At_QryCpuLoadPara UT工程类
修改历史 :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCpuLoadPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex     = 0;
        gastAtClientTab[ucIndex].usClientId = 0;
        gastAtClientTab[ucIndex].opId       = 0;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCpuLoadPara_001
测试用例标题      : 获取当前CPU占用率命令下发成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryCpuLoadPara, Test_At_QryCpuLoadPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_CPULOAD_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /*调用被测函数 */
    ulRet = At_QryCpuLoadPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_CPULOAD_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCpuLoadPara_002
测试用例标题      : 给DRV AGENT模块发消息失败
预期结果          : 返回AT_ERROR
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryCpuLoadPara, Test_At_QryCpuLoadPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet = TAF_FAILURE;

    /*函数打桩*/
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_CPULOAD_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /*调用被测函数 */
    ulRet = At_QryCpuLoadPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_AT_QryApRptPortSelectPara
功能描述 : AT_QryApRptPortSelectPara UT工程类
修改历史 :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryApRptPortSelectPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);

        ucIndex     = 0;

        stCmdInfo.ulCmdIndex        = AT_CMD_APRPTPORTSEL;
        stCmdInfo.pfnSetProc        = AT_SetApRptPortSelectPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryApRptPortSelectPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_LIMITED_NULL;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APRPTPORTSEL";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(0-3)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryApRptPortSelectPara_001
测试用例标题      : 查询已配置的主动上报的HSIC AT端口成功，并输出结果
预期结果          : 返回AT_OK
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryApRptPortSelectPara, Test_AT_QryApRptPortSelectPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    pcExpactedStr   = "^APRPTPORTSEL: 00000001, 00000001";
#else
    pcExpactedStr   = "^APRPTPORTSEL: 00000001, 00000000";
#endif

    /*全局变量初始化*/
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;

    /*函数打桩*/

    pstAtClientCtx = AT_GetClientCtxAddr(AT_CLIENT_ID_PCUI);

    pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_TRUE;

#if (FEATURE_ON == FEATURE_VCOM_EXT)
    pstAtClientCtx = AT_GetClientCtxAddr(AT_CLIENT_ID_APP13);

    pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_TRUE;
#endif

    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    /*调用被测函数 */
    ulRet = AT_QryApRptPortSelectPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryApRptPortSelectPara_002
测试用例标题      : 命令从非HSIC通道下发，直接回复失败
预期结果          : 返回AT_ERROR
修改历史   :
1.日   期  : 2012-02-13
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryApRptPortSelectPara, Test_AT_QryApRptPortSelectPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;

    /*全局变量初始化*/
    gastAtClientTab[ucIndex].UserType   = AT_COM_USER;
#if (FEATURE_ON == FEATURE_AT_HSIC)
    g_astAtHsicCtx[0].enRptType         = AT_HSIC_REPORT_OFF;
    g_astAtHsicCtx[0].enAcmChannelId    = UDI_ACM_HSIC_ACM0_ID;
    g_astAtHsicCtx[1].enRptType         = AT_HSIC_REPORT_ON;
    g_astAtHsicCtx[1].enAcmChannelId    = UDI_ACM_HSIC_ACM2_ID;
    g_astAtHsicCtx[2].enRptType         = AT_HSIC_REPORT_ON;
    g_astAtHsicCtx[2].enAcmChannelId    = UDI_ACM_HSIC_ACM4_ID;
#endif

    /*函数打桩*/
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    /*调用被测函数 */
    ulRet = AT_QryApRptPortSelectPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryUsbSwitchPara
功能描述 : At_QryUsbSwitchPara UT工程类
修改历史     :
1.日   期  : 2012-01-04
  作   者  : h59254
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryUsbSwitchPara: public ::testing::Test
{
public:
    TAF_UINT8       ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 1;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryUsbSwitchPara_001
测试用例标题      : 调用低软接口失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-01-04
  作   者  : h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryUsbSwitchPara, Test_At_QryUsbSwitchPara_001)
{
    /* 变量初始化 */

    /* 函数打桩 */
    MOCKER(USB_otg_switch_get)
        .stubs()
        .will(returnValue((int)VOS_ERR));

    /* 调用被测函数并结果验证 */
    EXPECT_EQ(AT_ERROR, At_QryUsbSwitchPara(ucIndex));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if 0
/*******************************************************************
测试用例编号      : Test_At_QryUsbSwitchPara_002
测试用例标题      : 调用底软接口返回激活
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-01-04
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryUsbSwitchPara, Test_At_QryUsbSwitchPara_002)
{
    /* 变量初始化 */
    TAF_UINT8       ucUsbStatus = 1;

    /* 函数打桩 */
    MOCKER(USB_otg_switch_get)
        .stubs()
        .with(outBoundP((void *)&ucUsbStatus))
        .will(returnValue(VOS_OK));

    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(100));*/

    /* 调用被测函数并结果验证 */
    EXPECT_EQ(AT_OK, At_QryUsbSwitchPara(ucIndex));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryUsbSwitchPara_003
测试用例标题      : 调用底软接口返回未激活
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-01-04
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryUsbSwitchPara, Test_At_QryUsbSwitchPara_003)
{
    /* 变量初始化 */
    TAF_UINT8       ucUsbStatus     = 2;

    /* 函数打桩 */
    MOCKER(USB_otg_switch_get)
        .stubs()
        .with(outBoundP((void *)&ucUsbStatus))
        .will(returnValue(VOS_OK));

    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(100));*/

    /* 调用被测函数并结果验证 */
    EXPECT_EQ(AT_OK, At_QryUsbSwitchPara(ucIndex));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif


/*****************************************************************************
类名     : Test_AT_QryAntState
功能描述 : AT_QryAntState UT工程类
修改历史     :
1.日   期  : 2012-04-26
  作   者  : h59254
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryAntState: public ::testing::Test
{
public:
    TAF_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = 0;
        gstAtSendData.usBufLen      = 0;
        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

        stCmdInfo.ulCmdIndex        = AT_CMD_ANTSTATE;
        stCmdInfo.pfnSetProc        = AT_QryAntState;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^ANTSTATE";
        stCmdInfo.pszParam          = VOS_NULL_PTR;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {
        ucIndex                 = 1;
        gstAtSendData.usBufLen  = 0;
        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryAntState_001
测试用例标题      : 降SRS功能查询当前天线状态，TAF_AGENT_GetAntState失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-04-26
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAntState, Test_AT_QryAntState_001)
{
    /* 变量初始化 */
    VOS_UINT32                          ulRslt;


    /* 函数打桩 */
    MOCKER(TAF_AGENT_GetAntState)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* 调用被测函数并结果验证 */
    ulRslt = AT_QryAntState(ucIndex);

    EXPECT_EQ(AT_ERROR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryAntState_002
测试用例标题      : 降SRS功能查询当前天线状态函数执行成功
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-04-26
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAntState, Test_AT_QryAntState_002)
{
    /* 变量初始化 */
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usAntState;

    /* 函数打桩 */
    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(0));*/

    usAntState = 0;

    MOCKER(TAF_AGENT_GetAntState)
        .stubs()
        .with(any(), outBoundP((VOS_UINT16 *)&usAntState, sizeof(usAntState)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 调用被测函数并结果验证 */
    ulRslt = AT_QryAntState(ucIndex);

    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryAntState_003
测试用例标题      : 输入的AT命令带有参数
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2012-04-26
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryAntState, Test_AT_QryAntState_003)
{
    /* 变量初始化 */
    VOS_UINT32                          ulRslt;

    /* 设置全局变量 */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    /* 函数打桩 */

    /* 调用被测函数并结果验证 */
    ulRslt = AT_QryAntState(ucIndex);

    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QrySARReduction
功能描述 : AT_QrySARReduction UT工程类
修改历史     :
1.日   期  : 2012-04-26
  作   者  : h59254
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QrySARReduction: public ::testing::Test
{
public:
    TAF_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = 0;
        gstAtSendData.usBufLen      = 0;

        stCmdInfo.ulCmdIndex        = AT_CMD_SARREDUCTION;
        stCmdInfo.pfnSetProc        = AT_SetSARReduction;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = AT_QrySARReduction;
        stCmdInfo.ulTestTimeOut     = AT_QRY_PARA_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^SARREDUCTION";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(0-8)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {
        ucIndex                 = 1;
        gstAtSendData.usBufLen  = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_AT_QrySARReduction_001
测试用例标题      : 降SRS查询功率回退等级读取NV项失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-04-26
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QrySARReduction, Test_AT_QrySARReduction_001)
{
    /* 变量初始化 */
    VOS_UINT32                          ulRslt;


    /* 函数打桩 */
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /* 调用被测函数并结果验证 */
    ulRslt = AT_QrySARReduction(ucIndex);

    EXPECT_EQ(AT_ERROR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QrySARReduction_002
测试用例标题      : AT_GetModemIdFromClient失败
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-04-26
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QrySARReduction, Test_AT_QrySARReduction_002)
{
    /* 变量初始化 */
    VOS_UINT32                          ulRslt;


    /* 函数打桩 */
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* 调用被测函数并结果验证 */
    ulRslt = AT_QrySARReduction(ucIndex);

    EXPECT_EQ(AT_ERROR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QrySARReduction_003
测试用例标题      : 降SRS查询功率回退等级传导模式且非测试模式
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-04-26
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QrySARReduction, Test_AT_QrySARReduction_003)
{
    /* 变量初始化 */
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usUETestMode = VOS_FALSE;
    VOS_UINT16                          usAntState = AT_ANT_CONDUCTION_MODE;

    /* 函数打桩 */
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        //.with(any(),eq((VOS_UINT16)en_NV_Item_RF_SAR_BACKOFF_TESTMODE),outBoundP((VOS_UINT16 *)&usUETestMode, (VOS_UINT32)sizeof(usUETestMode)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    usAntState = 1;
    MOCKER(TAF_AGENT_GetAntState)
        .expects(exactly(1))
        .with(eq((VOS_UINT16)ucIndex),outBoundP((VOS_UINT16 *)&usAntState, (VOS_UINT32)sizeof(usAntState)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 调用被测函数并结果验证 */
    ulRslt = AT_QrySARReduction(ucIndex);

    EXPECT_EQ(AT_ERROR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QrySARReduction_004
测试用例标题      : 降SRS查询功率回退等级函数正常输出
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-04-26
  作   者  :   h59254
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QrySARReduction, Test_AT_QrySARReduction_004)
{
    /* 变量初始化 */
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usUETestMode = VOS_TRUE;
    VOS_UINT16                          usAntState = AT_ANT_AIRWIRE_MODE;

    /* 函数打桩 */
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        //.with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0),
        //      eq((VOS_UINT16)en_NV_Item_RF_SAR_BACKOFF_TESTMODE),
        //      outBoundP((VOS_UINT16 *)&usUETestMode, (VOS_UINT32)sizeof(usUETestMode)),
        //      eq((VOS_UINT32)sizeof(usUETestMode)))
        .will(returnValue((VOS_UINT32)NV_OK));

    usAntState = 0;
    MOCKER(TAF_AGENT_GetAntState)
        .expects(exactly(1))
        .with(eq((VOS_UINT16)ucIndex), outBoundP((VOS_UINT16 *)&usAntState, (VOS_UINT32)sizeof(usAntState)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(100));*/

    /* 调用被测函数并结果验证 */
    ulRslt = AT_QrySARReduction(ucIndex);

    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
 函 数 名  : AT_InitQryCtx
 功能描述  : AT命令处理函数UT测试套初始化AT上下文函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_VOID AT_InitQryCtx(VOS_VOID)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucLoop;

    PS_MEM_SET(gastAtClientTab, 0x00, (AT_MAX_CLIENT_NUM * sizeof(AT_CLIENT_MANAGE_STRU)));

    /* 初始化PCUI通道 */
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    /* 填写用户表项 */
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_COM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
    gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
    gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* 初始化HSIC通道 */
    for (ucLoop = 0; ucLoop < AT_HSIC_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = g_astAtHsicCtx[ucLoop].ucAtClientTabIdx;

        /* 填写用户表项 */
        gastAtClientTab[ucIndex].usClientId      = g_astAtHsicCtx[ucLoop].enAtClientId;
        gastAtClientTab[ucIndex].ucPortNo        = g_astAtHsicCtx[ucLoop].ucHsicPort;
        gastAtClientTab[ucIndex].UserType        = g_astAtHsicCtx[ucLoop].ucHsicUser;
        gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

        gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
        gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
        gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
        gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
        gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    }
#endif

    /* 初始化参数列表 */
    gucAtParaIndex                  = 0;
    g_stATParseCmd.ucCmdOptType     = AT_CMD_OPT_READ_CMD;
    PS_MEM_SET(gastAtParaList, 0x00, (AT_MAX_PARA_NUMBER * sizeof(AT_PARSE_PARA_TYPE_STRU)));

    return;

}

/*****************************************************************************
类名     : Test_AT_QryPhoneSimlockInfoPara
功能描述 : AT_QryPhoneSimlockInfoPara UT工程类
修改历史 :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryPhoneSimlockInfoPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitQryCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryPhoneSimlockInfoPara_001
测试用例标题      : 命令从非HSIC通道下发
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhoneSimlockInfoPara, Test_AT_QryPhoneSimlockInfoPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_PCUI;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_QryPhoneSimlockInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryPhoneSimlockInfoPara_002
测试用例标题      : 命令从HSIC通道下发
预期结果          : 返回AT_WAIT_ASYNC_RETURN, AT发送消息给DrvAgent, AT等待异步返回
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhoneSimlockInfoPara, Test_AT_QryPhoneSimlockInfoPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QryPhoneSimlockInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN,         ulRet);
    EXPECT_EQ(AT_CMD_PHONESIMLOCKINFO_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryPhoneSimlockInfoPara_003
测试用例标题      : 命令从HSIC通道下发, 消息发送失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhoneSimlockInfoPara, Test_AT_QryPhoneSimlockInfoPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryPhoneSimlockInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QrySimlockDataReadPara
功能描述 : AT_QrySimlockDataReadPara UT工程类
修改历史 :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QrySimlockDataReadPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitQryCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QrySimlockDataReadPara_001
测试用例标题      : 命令从非HSIC通道下发
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QrySimlockDataReadPara, Test_AT_QrySimlockDataReadPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_PCUI;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_QrySimlockDataReadPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QrySimlockDataReadPara_002
测试用例标题      : 命令从HSIC通道下发
预期结果          : 返回AT_WAIT_ASYNC_RETURN, AT发送消息给DrvAgent, AT等待异步返回
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QrySimlockDataReadPara, Test_AT_QrySimlockDataReadPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QrySimlockDataReadPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN,         ulRet);
    EXPECT_EQ(AT_CMD_SIMLOCKDATAREAD_READ,  gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QrySimlockDataReadPara_003
测试用例标题      : 命令从HSIC通道下发, 消息发送失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QrySimlockDataReadPara, Test_AT_QrySimlockDataReadPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QrySimlockDataReadPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR,         ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryPhonePhynumPara
功能描述 : AT_QryPhonePhynumPara UT工程类
修改历史 :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryPhonePhynumPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitQryCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryPhonePhynumPara_001
测试用例标题      : 命令从非HSIC通道下发
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhonePhynumPara, Test_AT_QryPhonePhynumPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_PCUI;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_QryPhonePhynumPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryPhonePhynumPara_002
测试用例标题      : 命令从HSIC通道下发
预期结果          : 返回AT_WAIT_ASYNC_RETURN, AT发送消息给DrvAgent, AT等待异步返回
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhonePhynumPara, Test_AT_QryPhonePhynumPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_PHONEPHYNUM_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QryPhonePhynumPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN,     ulRet);
    EXPECT_EQ(AT_CMD_PHONEPHYNUM_READ,  gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryPhonePhynumPara_003
测试用例标题      : 命令从HSIC通道下发, 消息发送失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPhonePhynumPara, Test_AT_QryPhonePhynumPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_PHONEPHYNUM_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryPhonePhynumPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_QryPortCtrlTmpPara
功能描述 : AT_QryPortCtrlTmpPara UT工程类
修改历史 :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryPortCtrlTmpPara: public ::testing::Test
{
public:
    AT_PAR_CMD_ELEMENT_STRU                 stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_PORTCTRLTMP;
        stCmdInfo.pfnSetProc        = AT_SetPortCtrlTmpPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = AT_QryPortCtrlTmpPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestHsicCmdPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^PORTCTRLTMP";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(@password)";

        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_PORTCTRLTMP_READ;
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }
    void TearDown()
    {

    }

    VOS_UINT8       ucIndex;
};

/*******************************************************************
测试用例编号      : Test_AT_QryPortCtrlTmpPara_001
测试用例标题      : 命令从非HSIC通道下发
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPortCtrlTmpPara, Test_AT_QryPortCtrlTmpPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_IsApPort)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_QryPortCtrlTmpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryPortCtrlTmpPara_002
测试用例标题      : 命令从HSIC通道下发,访问失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPortCtrlTmpPara, Test_AT_QryPortCtrlTmpPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(PPM_GetHsicPortStatus)
        .expects(exactly(1))
        .will(returnValue((OM_HSIC_PORT_STATUS_ENUM_UINT32)OM_HSIC_PORT_STATUS_BUTT));

    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QryPortCtrlTmpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryPortCtrlTmpPara_003
测试用例标题      : 命令从HSIC通道下发
预期结果          : 返回AT_OK,打印输出结果
修改历史          :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPortCtrlTmpPara, Test_AT_QryPortCtrlTmpPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    // 参数初始化
    pcExpactedStr           = "^PORTCTRLTMP: 1";

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(PPM_GetHsicPortStatus)
        .expects(exactly(1))
        .will(returnValue((OM_HSIC_PORT_STATUS_ENUM_UINT32)OM_HSIC_PORT_STATUS_ON));
#if (FEATURE_ON==FEATURE_LTE)
    MOCKER(DMS_GetHsicPortStatus)
        .stubs()
        .will(returnValue((VOS_UINT32)OM_HSIC_PORT_STATUS_ON));
#endif

    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QryPortCtrlTmpPara(ucIndex);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);


    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryPortAttribSetPara
功能描述 : AT_QryPortAttribSetPara UT工程类
修改历史 :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryPortAttribSetPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitQryCtx();
    }
    void TearDown()
    {

    }

    VOS_UINT8       ucIndex;
};

/*******************************************************************
测试用例编号      : Test_AT_QryPortAttribSetPara_001
测试用例标题      : 命令从非HSIC通道下发
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPortAttribSetPara, Test_AT_QryPortAttribSetPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_PCUI;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_QryPortAttribSetPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryPortAttribSetPara_002
测试用例标题      : 命令从HSIC通道下发
预期结果          : 返回AT_WAIT_ASYNC_RETURN, AT发送消息给DrvAgent, AT等待异步返回
修改历史          :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPortAttribSetPara, Test_AT_QryPortAttribSetPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_PORTATTRIBSET_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QryPortAttribSetPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_PORTATTRIBSET_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryPortAttribSetPara_003
测试用例标题      : 命令从HSIC通道下发, 消息发送失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryPortAttribSetPara, Test_AT_QryPortAttribSetPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)DRV_AGENT_PORTATTRIBSET_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)WUEPS_PID_DRV_AGENT))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QryPortAttribSetPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryU2DiagPara
功能描述 : Test_At_QryU2DiagPara UT工程类
修改历史     :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*****************************************************************************/
class Test_At_QryU2DiagPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
        PS_MEM_SET(&gstAtSendData, 0, sizeof(gstAtSendData));
        g_stParseContext[0].pstCmdElement = &gstU2diagCmdInfo;
    }
    void TearDown()
    {
    }

protected:
    VOS_UINT8 ucIndex;
};

/*******************************************************************
测试用例编号      : Test_At_QryU2DiagPara_001
测试用例标题      : 读取NV项en_NV_Item_PID_Enable_Type失败
预期结果          : 函数返回AT_ERROR
修改历史          :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_At_QryU2DiagPara, Test_At_QryU2DiagPara_001)
{
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;
    VOS_UINT32                          ulResult;

    ucIndex             = 0;

    stPidEnableType.ulPidEnabled = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_PID_Enable_Type), outBoundP((void *)&stPidEnableType, sizeof(stPidEnableType)), any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    ulResult = At_QryU2DiagPara(ucIndex);

    EXPECT_EQ(ulResult, AT_ERROR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryU2DiagPara_002
测试用例标题      : 读取NV项en_NV_Item_PID_Enable_Type得到状态为已使能
预期结果          : 函数返回AT_ERROR
修改历史          :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_At_QryU2DiagPara, Test_At_QryU2DiagPara_002)
{
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;
    VOS_UINT32                          ulResult;

    ucIndex             = 0;

    stPidEnableType.ulPidEnabled = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_PID_Enable_Type), outBoundP((void *)&stPidEnableType, sizeof(stPidEnableType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulResult = At_QryU2DiagPara(ucIndex);

    EXPECT_EQ(ulResult, AT_ERROR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryU2DiagPara_003
测试用例标题      : 读取NV项en_NV_Item_PID_Enable_Type得到状态为未使能
预期结果          : 函数返回AT_OK
修改历史          :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_At_QryU2DiagPara, Test_At_QryU2DiagPara_003)
{
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;
    AT_USB_ENUM_STATUS_STRU             stUsbEnumStatus;
    VOS_CHAR                           *pcExpactedStr;
    VOS_UINT32                          ulResult;

    ucIndex             = 0;

    stPidEnableType.ulPidEnabled = VOS_FALSE;
    stUsbEnumStatus.ulStatus = VOS_TRUE;
    stUsbEnumStatus.ulValue = 118;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_PID_Enable_Type), outBoundP((void *)&stPidEnableType, sizeof(stPidEnableType)), any())
        .will(returnValue((VOS_UINT32)NV_OK))
        .id("first");

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_USB_Enum_Status), outBoundP((void *)&stUsbEnumStatus, sizeof(stUsbEnumStatus)), any())
        .after("first")
        .will(returnValue((VOS_UINT32)NV_OK));

    pcExpactedStr = "^U2DIAG: 118";

    ulResult = At_QryU2DiagPara(ucIndex);

    EXPECT_EQ(AT_OK, ulResult);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_GetWcdmaBandStr
功能描述 : Test_AT_GetWcdmaBandStr UT工程类
修改历史     :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*****************************************************************************/
class Test_AT_GetWcdmaBandStr: public ::testing::Test
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
测试用例编号      : Test_AT_GetWcdmaBandStr_001
测试用例标题      : W全频带都支持
预期结果          : 输出字符串为"BC1,BC2,BC3,BC4,BC5,BC6,BC7,BC8,BC9,BC11"
修改历史          :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_AT_GetWcdmaBandStr, Test_AT_GetWcdmaBandStr_001)
{
    AT_UE_BAND_CAPA_ST                 stBandCapa;
    VOS_UINT32                         ulResult;
    VOS_UINT8                          aucGsmBandstr[500];
    VOS_CHAR                           *pcExpactedStr;
    pcExpactedStr = "BC1,BC2,BC3,BC4,BC5,BC6,BC7,BC8,BC9,BC11,BC19";

    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_I_2100 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_II_1900 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_III_1800 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_IV_1700 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_V_850 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_VI_800 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_VII_2600 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_VIII_900 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_IX_J1700 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_XI_1500 = 1;
    stBandCapa.unWRFSptBand.BitBand.BandWCDMA_XIX_850 = 1;

    PS_MEM_SET(aucGsmBandstr, 0, sizeof(aucGsmBandstr));
    ulResult = AT_GetWcdmaBandStr(aucGsmBandstr, &stBandCapa);

    EXPECT_EQ((ulResult - 1), VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)aucGsmBandstr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetWcdmaBandStr_002
测试用例标题      : W全频带都不支持
预期结果          : 输出字符串为空
修改历史          :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_AT_GetWcdmaBandStr, Test_AT_GetWcdmaBandStr_002)
{
    AT_UE_BAND_CAPA_ST                 stBandCapa;
    VOS_UINT32                         ulResult;
    VOS_UINT8                          aucGsmBandstr[500];
    VOS_CHAR                           *pcExpactedStr;
    pcExpactedStr = "";

    PS_MEM_SET(&stBandCapa, 0, sizeof(stBandCapa));

    PS_MEM_SET(aucGsmBandstr, 0, sizeof(aucGsmBandstr));
    ulResult = AT_GetWcdmaBandStr(aucGsmBandstr, &stBandCapa);

    EXPECT_EQ(ulResult, VOS_StrLen(pcExpactedStr));
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)aucGsmBandstr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
//#if 0

/*****************************************************************************
类名     : Test_AT_QryCposrPara
功能描述 : AT_QryCposrPara UT工程类
修改历史 :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*****************************************************************************/
class Test_AT_QryCposrPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;

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

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }

    void TearDown()
    {
    }

    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};

/*******************************************************************
测试用例编号      : Test_AT_QryCposrPara_001
测试用例标题      : 命令从HSIC4通道下发，
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_QryCposrPara, Test_AT_QryCposrPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucPrint;

    // 参数初始化
    pucPrint                            = (VOS_UINT8 *)"+CPOSR: 1";

    // 初始化全局变量;
    AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enCposrReport                   = AT_CPOSR_ENABLE;

    // MOCKER操作;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QryCposrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    ulRet = PS_MEM_CMP(pgucAtSndCodeAddr, pucPrint, VOS_StrLen("+CPOSR: 1"));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryCposrPara_002
测试用例标题      : 命令从非HSIC通道下发，
预期结果          : 返回AT_ERROR
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_QryCposrPara, Test_AT_QryCposrPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量;
    AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enCposrReport                   = AT_CPOSR_ENABLE;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_QryCposrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryXcposrPara
功能描述 : AT_QryXcposrPara UT工程类
修改历史 :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*****************************************************************************/
class Test_AT_QryXcposrPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;

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

};

/*******************************************************************
测试用例编号      : Test_AT_QryXcposrPara_001
测试用例标题      : 命令从HSIC4通道下发，
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_QryXcposrPara, Test_AT_QryXcposrPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucPrint;

    // 参数初始化
    pucPrint                            = (VOS_UINT8 *)"+XCPOSR: 1";

    // 初始化全局变量;
    AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enXcposrReport                   = AT_XCPOSR_ENABLE;

    // MOCKER操作;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_QryXcposrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    ulRet = PS_MEM_CMP(pgucAtSndCodeAddr, pucPrint, VOS_StrLen("+XCPOSR: 1"));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryXcposrPara_002
测试用例标题      : 命令从非HSIC通道下发，
预期结果          : 返回AT_ERROR
修改历史          :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
TEST_F(Test_AT_QryXcposrPara, Test_AT_QryXcposrPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量;
    AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enXcposrReport                   = AT_XCPOSR_ENABLE;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_QryXcposrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


/*****************************************************************************
 类名       : Test_AT_QryCPsErrPara
 功能描述   : Test_AT_QryCPsErrPara UT工程类
 修改历史   :
 1.日   期  : 2012-08-22
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCPsErrPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }
    void TearDown()
    {
    }

};

/*******************************************************************
 测试用例编号   : Test_AT_QryCPsErrPara_001
 测试用例标题   : 查询PS域呼叫错误码
 预期结果       : 输出符合^CPSERR命令格式要求
 修改历史       :
 1.日   期  : 2012-08-22
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCPsErrPara, Test_AT_QryCPsErrPara_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "^CPSERR: 289";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement    = {AT_CMD_CPSERR_SET,
                                                           VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                           AT_QryCPsErrPara, AT_NOT_SET_TIME,
                                                           At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                           VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                           AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                           (VOS_UINT8 *)"^CPSERR", VOS_NULL_PTR};


    //参数初始化
    ucIndex = 0;

    //相关全局变量初始化
    AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED);
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_QryCPsErrPara(ucIndex);

    //执行检查
    ASSERT_EQ(AT_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_AT_QryCmutPara
 功能描述   : Test_AT_QryCmutPara UT工程类
 修改历史   :
 1.日   期  : 2012-09-14
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCmutPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }
    void TearDown()
    {
    }

};

/*******************************************************************
 测试用例编号   : Test_AT_QryCmutPara_001
 测试用例标题   : 查询静音状态, 发送消息失败
 预期结果       : AT_ERROR
 修改历史       :
 1.日   期  : 2012-09-14
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCmutPara, Test_AT_QryCmutPara_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement    = {AT_CMD_CMUT,
                                                           AT_SetCmutPara, AT_SET_PARA_TIME,
                                                           AT_QryCmutPara, AT_QRY_PARA_TIME,
                                                           AT_TestCmutPara, AT_NOT_SET_TIME,
                                                           VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                           AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                           (VOS_UINT8 *)"+CMUT", (VOS_UINT8 *)"(0,1)"};

    //参数初始化
    ucIndex = 0;

    //相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    //MOCKER操作
    MOCKER(APP_VC_GetMuteStatus)
        .stubs()
        .will(returnValue(VOS_ERR));

    //调用被测函数
    ulRslt = AT_QryCmutPara(ucIndex);

    //执行检查
    ASSERT_EQ(AT_ERROR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_AT_QryCmutPara_002
 测试用例标题   : 查询静音状态, 发送消息成功
 预期结果       : AT_ERROR
 修改历史       :
 1.日   期  : 2012-09-14
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCmutPara, Test_AT_QryCmutPara_002)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement    = {AT_CMD_CMUT,
                                                           AT_SetCmutPara, AT_SET_PARA_TIME,
                                                           AT_QryCmutPara, AT_QRY_PARA_TIME,
                                                           AT_TestCmutPara, AT_NOT_SET_TIME,
                                                           VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                           AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                           (VOS_UINT8 *)"+CMUT", (VOS_UINT8 *)"(0,1)"};

    //参数初始化
    ucIndex = 0;

    //相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_QryCmutPara(ucIndex);

    //执行检查
    ASSERT_EQ(AT_CMD_CMUT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

AT_PAR_CMD_ELEMENT_STRU     gstSsidCmdInfo = {AT_CMD_SSID,
    AT_SetWiFiSsidPara,   AT_NOT_SET_TIME, AT_QryWiFiSsidPara,   AT_NOT_SET_TIME, AT_TestSsidPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SSID",  (VOS_UINT8*)"(0-3),(@SSID)"};

AT_PAR_CMD_ELEMENT_STRU     gstWiKeyCmdInfo = {AT_CMD_WIKEY,
    AT_SetWiFiKeyPara,    AT_NOT_SET_TIME, AT_QryWiFiKeyPara,    AT_NOT_SET_TIME, AT_TestWikeyPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIKEY",  (VOS_UINT8*)"(0-3),(@WIKEY)"};

AT_PAR_CMD_ELEMENT_STRU     gstWiLogCmdInfo = {AT_CMD_WILOG,
    AT_SetWiFiLogPara,    AT_NOT_SET_TIME, AT_QryWiFiLogPara,    AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WILOG",  (VOS_UINT8*)"(0,1),(@content)"};

/*****************************************************************************
类名     : Test_AT_QryWiFiSsidPara
功能描述 : Test_AT_QryWiFiSsidPara UT工程类
修改历史     :
1.日   期  : 2012-09-18
  作   者  :   z60575
  修改内容 :   新生成类
*****************************************************************************/
class Test_AT_QryWiFiSsidPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstSsidCmdInfo;
    }
    void TearDown()
    {
        g_stParseContext[0].pstCmdElement = VOS_NULL_PTR;
    }

};

/*******************************************************************
测试用例编号      : Test_AT_QryWiFiSsidPara_001
测试用例标题      : 不支持WIFI
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_AT_QryWiFiSsidPara, Test_AT_QryWiFiSsidPara_001)
{
    VOS_UINT32                  ulResult;

    /* 初始化变量 */
    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_UNSUPPORT));

    ulResult = AT_QryWiFiSsidPara(0);

    EXPECT_EQ(AT_ERROR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryWiFiSsidPara_002
测试用例标题      : 查询成功
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-05-10
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_AT_QryWiFiSsidPara, Test_AT_QryWiFiSsidPara_002)
{
    TAF_AT_MULTI_WIFI_SSID_STRU             stWifiSsid;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSsid1[] = "1234";
    VOS_UINT8                           aucSsid2[] = "1234";
    VOS_UINT8                           aucSsid3[] = "1234";
    VOS_UINT8                           aucSsid4[] = "1234";
    VOS_UINT16                          usExpectedStrLen;
    char                               *paucExpectedStr = "^SSID:4\r\n^SSID:0,1234\r\n^SSID:1,1234\r\n^SSID:2,1234\r\n^SSID:3,1234\r\n";

    /* 初始化变量 */
    PS_MEM_SET(&stWifiSsid, 0x00, sizeof(stWifiSsid));

    PS_MEM_CPY(stWifiSsid.aucWifiSsid[0], aucSsid1, sizeof(aucSsid1));
    PS_MEM_CPY(stWifiSsid.aucWifiSsid[1], aucSsid2, sizeof(aucSsid2));
    PS_MEM_CPY(stWifiSsid.aucWifiSsid[2], aucSsid3, sizeof(aucSsid3));
    PS_MEM_CPY(stWifiSsid.aucWifiSsid[3], aucSsid4, sizeof(aucSsid4));

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_STATUS_SSID), outBoundP((void *)&stWifiSsid, sizeof(stWifiSsid)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRet = AT_QryWiFiSsidPara(0);

    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryWiFiLogPara
功能描述 : Test_AT_QryWiFiLogPara UT工程类
修改历史     :
1.日   期  : 2012-09-18
  作   者  :   z60575
  修改内容 :   新生成类
*****************************************************************************/
class Test_AT_QryWiFiLogPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstWiLogCmdInfo;
    }
    void TearDown()
    {
        g_stParseContext[0].pstCmdElement = VOS_NULL_PTR;
    }

};

/*******************************************************************
测试用例编号      : Test_AT_QryWiFiLogPara_001
测试用例标题      : 不支持WIFI
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-09-19
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_AT_QryWiFiLogPara, Test_AT_QryWiFiLogPara_001)
{
    VOS_UINT32                  ulResult;

    /* 初始化变量 */
    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_UNSUPPORT));

    ulResult = AT_QryWiFiLogPara(0);

    EXPECT_EQ(AT_ERROR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryWiFiLogPara_002
测试用例标题      : 查询成功
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-09-19
  作   者  :   z60575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_AT_QryWiFiLogPara, Test_AT_QryWiFiLogPara_002)
{
    TAF_AT_MULTI_WIFI_SSID_STRU             stWifiSsid;
    TAF_AT_MULTI_WIFI_SEC_STRU              stWifiSec;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSsid1[] = "1234";
    VOS_UINT8                           aucSsid2[] = "1234";
    VOS_UINT8                           aucSsid3[] = "1234";
    VOS_UINT8                           aucSsid4[] = "1234";
    VOS_UINT8                           aucWiWep1[] =  "1234";
    VOS_UINT8                           aucWiWep2[] =  "1234";
    VOS_UINT8                           aucWiWep3[] =  "1234";
    VOS_UINT8                           aucWiWep4[] =  "1234";
    VOS_UINT8                           aucWiWpa[] =  "1234";
    VOS_UINT16                          usExpectedStrLen;
    char                               *paucExpectedStr = "^WILOG:0,1234\r\n^WILOG:1,1234\r\n^WILOG:2,1234\r\n^WILOG:3,1234\r\n^WILOG:4,1234\r\n";

    /* 初始化变量 */
    PS_MEM_SET(&stWifiSsid, 0x00, sizeof(stWifiSsid));
    PS_MEM_SET(&stWifiSec, 0x00, sizeof(stWifiSec));

    PS_MEM_CPY(stWifiSsid.aucWifiSsid[0], aucSsid1, sizeof(aucSsid1));
    PS_MEM_CPY(stWifiSsid.aucWifiSsid[1], aucSsid2, sizeof(aucSsid2));
    PS_MEM_CPY(stWifiSsid.aucWifiSsid[2], aucSsid3, sizeof(aucSsid3));
    PS_MEM_CPY(stWifiSsid.aucWifiSsid[3], aucSsid4, sizeof(aucSsid4));

    PS_MEM_CPY(stWifiSec.aucWifiWepKey1[0], aucWiWep1, sizeof(aucWiWep1));
    PS_MEM_CPY(stWifiSec.aucWifiWepKey2[0], aucWiWep2, sizeof(aucWiWep2));
    PS_MEM_CPY(stWifiSec.aucWifiWepKey3[0], aucWiWep3, sizeof(aucWiWep3));
    PS_MEM_CPY(stWifiSec.aucWifiWepKey4[0], aucWiWep4, sizeof(aucWiWep4));

    PS_MEM_CPY(stWifiSec.aucWifiWpapsk[0], aucWiWpa, sizeof(aucWiWpa));

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_STATUS_SSID), outBoundP((void *)&stWifiSsid, sizeof(stWifiSsid)), any())
        .will(returnValue((VOS_UINT32)NV_OK))
        .id("first");

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiSec, sizeof(stWifiSec)), any())
        .after("first")
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRet = AT_QryWiFiLogPara(0);

    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryWiFiKeyPara
功能描述 : Test_AT_QryWiFiKeyPara UT工程类
修改历史     :
1.日   期  : 2012-09-18
  作   者  :   z60575
  修改内容 :   新生成类
*****************************************************************************/
class Test_AT_QryWiFiKeyPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstWiKeyCmdInfo;
    }
    void TearDown()
    {
        g_stParseContext[0].pstCmdElement = VOS_NULL_PTR;
    }

};

/*******************************************************************
测试用例编号      : Test_AT_QryWiFiKeyPara_001
测试用例标题      : 不支持WIFI
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-09-19
  作   者  :   f62575
  修改内容 :   新生成类
*******************************************************************/
TEST_F(Test_AT_QryWiFiKeyPara, Test_AT_QryWiFiKeyPara_001)
{
    VOS_UINT32                  ulResult;

    /* 初始化变量 */
    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_UNSUPPORT));

    ulResult = AT_QryWiFiKeyPara(0);

    EXPECT_EQ(AT_ERROR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryWiFiKeyPara_002
测试用例标题      : 查询成功
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-09-19
  作   者  :   z60575
  修改内容 :   新生成类
*********************** ********************************************/
TEST_F(Test_AT_QryWiFiKeyPara, Test_AT_QryWiFiKeyPara_002)
{
    TAF_AT_MULTI_WIFI_SEC_STRU              stWifiSec;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucWiWpa1[] =  "1234";
    VOS_UINT8                           aucWiWpa2[] =  "1234";
    VOS_UINT8                           aucWiWpa3[] =  "1234";
    VOS_UINT8                           aucWiWpa4[] =  "1234";
    VOS_UINT16                          usExpectedStrLen;
    char                               *paucExpectedStr = "^WIKEY:4\r\n^WIKEY:0,1234\r\n^WIKEY:1,1234\r\n^WIKEY:2,1234\r\n^WIKEY:3,1234\r\n";

    /* 初始化变量 */
    PS_MEM_SET(&stWifiSec, 0x00, sizeof(stWifiSec));

    PS_MEM_CPY(stWifiSec.aucWifiWpapsk[0] , aucWiWpa1, sizeof(aucWiWpa1));
    PS_MEM_CPY(stWifiSec.aucWifiWpapsk[1] , aucWiWpa2, sizeof(aucWiWpa2));
    PS_MEM_CPY(stWifiSec.aucWifiWpapsk[2] , aucWiWpa3, sizeof(aucWiWpa3));
    PS_MEM_CPY(stWifiSec.aucWifiWpapsk[3] , aucWiWpa4, sizeof(aucWiWpa4));

    g_bAtDataLocked = PS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiSec, sizeof(stWifiSec)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRet = AT_QryWiFiKeyPara(0);

    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryCurcPara
功能描述 : At_QryCurcPara UT工程类
修改历史 :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCurcPara: public ::testing::Test
{
public:
    VOS_UINT8                       ucIndex;
    AT_PAR_CMD_ELEMENT_STRU         stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_CURC;
        stCmdInfo.pfnSetProc        = At_SetCurcPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = At_QryCurcPara;
        stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CURC";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0-2)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }

};

/*******************************************************************
测试用例编号      : Test_At_QryCurcPara_001
测试用例标题      : 当前私有命令上报模式为自定义
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCurcPara, Test_At_QryCurcPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT16                          usMsgType;
    VOS_UINT8                          *pucPara = VOS_NULL_PTR;
    VOS_UINT32                          ulParaLen;
    VOS_UINT32                          ulRcvPid;

    //参数初始化
    usClientId  = gastAtClientTab[ucIndex].usClientId;
    ucOpId      = gastAtClientTab[ucIndex].opId;
    usMsgType   = ID_AT_MTA_CURC_QRY_REQ;
    ulParaLen   = 0;
    ulRcvPid    = I0_UEPS_PID_MTA;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(usClientId),
                eq(ucOpId),
                eq(usMsgType),
                any(),
                eq(ulParaLen),
                eq(ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = At_QryCurcPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_CURC_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryCurcPara_002
测试用例标题      : 当前私有命令上报模式为自定义
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2013-04-16
  作   者  : s00217060
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCurcPara, Test_At_QryCurcPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT16                          usMsgType;
    VOS_UINT8                          *pucPara = VOS_NULL_PTR;
    VOS_UINT32                          ulParaLen;
    VOS_UINT32                          ulRcvPid;

    //参数初始化
    usClientId  = gastAtClientTab[ucIndex].usClientId;
    ucOpId      = gastAtClientTab[ucIndex].opId;
    usMsgType   = ID_AT_MTA_CURC_QRY_REQ;
    ulParaLen   = 0;
    ulRcvPid    = I0_UEPS_PID_MTA;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(usClientId),
                eq(ucOpId),
                eq(usMsgType),
                any(),
                eq(ulParaLen),
                eq(ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = At_QryCurcPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


/*****************************************************************************
 类名       : Test_AT_QryCCsErrPara
 功能描述   : Test_AT_QryCCsErrPara UT工程类
 修改历史   :
 1.日   期  : 2012-09-26
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCCsErrPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
        AT_SetCsCallErrCause(0,TAF_CS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_SetCsCallErrCause(0,TAF_CS_CAUSE_SUCCESS);
    }

};

/*******************************************************************
 测试用例编号   : Test_AT_QryCCsErrPara_001
 测试用例标题   : 查询CS域呼叫错误码
 预期结果       : 输出符合^CCSERR命令格式要求
 修改历史       :
 1.日   期  : 2012-09-26
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCCsErrPara, Test_AT_QryCCsErrPara_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "^CCSERR: 1035";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement    = {AT_CMD_CPSERR_SET,
                                                           VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                           AT_QryCCsErrPara, AT_NOT_SET_TIME,
                                                           At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                           VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                           AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                           (VOS_UINT8 *)"^CCSERR", VOS_NULL_PTR};


    //参数初始化
    ucIndex = 0;

    //相关全局变量初始化
    AT_SetCsCallErrCause(0,TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED);
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_QryCCsErrPara(ucIndex);

    //执行检查
    ASSERT_EQ(AT_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_GetDspLoadMode
功能描述 : Test_At_GetDspLoadMode函数的UT测试类
修改历史 :
1.日   期  : 2012-08-30
  作   者  : f62575
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_GetDspLoadMode: public ::testing::Test
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
测试用例编号      : Test_At_GetDspLoadMode_001
测试用例标题      : 根据FCHAN的<MODE>参数获取到GU模的DSP加载模式
预期结果          : 输入                            输出
                    AT_RAT_MODE_WCDMA,              CPHY_DSP_LOAD_WCDMA
                    AT_RAT_MODE_CDMA,               CPHY_DSP_LOAD_BUTT
                    AT_RAT_MODE_TDSCDMA,            CPHY_DSP_LOAD_BUTT
                    AT_RAT_MODE_GSM,                CPHY_DSP_LOAD_GSM
                    AT_RAT_MODE_EDGE,               CPHY_DSP_LOAD_GSM
                    AT_RAT_MODE_AWS,                CPHY_DSP_LOAD_WCDMA
                    AT_RAT_MODE_FDD_LTE,            CPHY_DSP_LOAD_BUTT
                    AT_RAT_MODE_TDD_LTE,            CPHY_DSP_LOAD_BUTT
                    AT_RAT_MODE_WIFI,               CPHY_DSP_LOAD_BUTT
                    AT_RAT_MODE_BUTT                CPHY_DSP_LOAD_BUTT

修改历史          :
1.日   期  : 2012-08-30
  作   者  : f62575
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_GetDspLoadMode, Test_At_GetDspLoadMode_001)
{
    VOS_UINT32                      ulRatMode;
    TAF_UINT8                       ucDspLoadMode;

    ulRatMode     = AT_RAT_MODE_WCDMA;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_WCDMA, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_CDMA;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_BUTT, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_TDSCDMA;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_BUTT, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_GSM;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_GSM, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_EDGE;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_GSM, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_AWS;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_WCDMA, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_FDD_LTE;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_BUTT, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_TDD_LTE;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_BUTT, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_WIFI;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_BUTT, ucDspLoadMode);

    ulRatMode     = AT_RAT_MODE_BUTT;
    ucDspLoadMode = At_GetDspLoadMode(ulRatMode);
    EXPECT_EQ(VOS_RATMODE_BUTT, ucDspLoadMode);

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryCerssiPara
功能描述 : At_QryCerssiPara UT工程类
修改历史 :
1.日   期  : 2012-11-28
  作   者  : z00161729
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCerssiPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCerssiPara_001
测试用例标题      : 参数个数大于1
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-11-28
  作   者  : z00161729
  修改内容 : 新生成类
2.日   期  : 2013-1-9
  作   者  : t00212959
  修改内容 : DTS2013010809978,增加时间间隔
*******************************************************************/
TEST_F(Test_At_QryCerssiPara, Test_At_QryCerssiPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucPrint;
    VOS_UINT8                           ucIndex;

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement    = {AT_CMD_CERSSI,
                                                           At_SetCerssiPara,   AT_SET_PARA_TIME,  At_QryCerssiPara,
                                                           AT_QRY_PARA_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                           VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                           AT_CME_INCORRECT_PARAMETERS, CMD_TBL_CLAC_IS_INVISIBLE,
                                                          (VOS_UINT8*)"^CERSSI",       (VOS_UINT8*)"(0,1,2,3,4,5),(1-20)"};
    // 参数初始化
    ucIndex                             = 0;
    pucPrint                            = (VOS_UINT8 *)"^CERSSI: 2,3";


    // 初始化全局变量;
    AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucCerssiReportType          = AT_CERSSI_REPORT_TYPE_2DB_CHANGE_REPORT;
    AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucCerssiMinTimerInterval    = 3;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作;

    // 调用被测函数
    ulRet = At_QryCerssiPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);


    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_At_QryCerssiPara_002
测试用例标题      : 参数个数大于2
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2013-2-5
  作   者  : t00212959
  修改内容 : AT^CERSSI?增加参数
*******************************************************************/
TEST_F(Test_At_QryCerssiPara, Test_At_QryCerssiPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucPrint;
    VOS_UINT8                           ucIndex;

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement    = {AT_CMD_CERSSI,
                                                           At_SetCerssiPara,   AT_NOT_SET_TIME,  At_QryCerssiPara,
                                                           AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                           VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                           AT_CME_INCORRECT_PARAMETERS, CMD_TBL_CLAC_IS_INVISIBLE,
                                                          (VOS_UINT8*)"^CERSSI",       (VOS_UINT8*)"(0,1,2,3,4,5),(1-20)"};
    // 参数初始化
    ucIndex                             = 0;

    // 初始化全局变量;

    AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucCerssiReportType          = AT_CERSSI_REPORT_TYPE_2DB_CHANGE_REPORT;
    AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucCerssiMinTimerInterval    = 3;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作;

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = At_QryCerssiPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);


    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryCLteRoamAllowPara
功能描述 : AT_QryCLteRoamAllowPara UT工程类
修改历史 :
1.日   期  : 2012-12-19
  作   者  : l00171473
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCLteRoamAllowPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        PS_MEM_SET(&gstAtSendData.aucBuffer[0], 0x00, sizeof(gstAtSendData.aucBuffer));
        pgucAtSndCodeAddr            = &gstAtSendData.aucBuffer[3];
    }
    void TearDown()
    {
        PS_MEM_SET(&gstAtSendData.aucBuffer[0], 0x00, sizeof(gstAtSendData.aucBuffer));
    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryCLteRoamAllowPara_001
测试用例标题      : 读取NV失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-12-19
  作   者  : l00171473
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryCLteRoamAllowPara, Test_AT_QryCLteRoamAllowPara_001)
{
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    EXPECT_EQ(AT_QryCLteRoamAllowPara(0), AT_ERROR);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryCLteRoamAllowPara_002
测试用例标题      : 读出的NV漫游禁止标志位为255
预期结果          : 返回AT_OK,AT返回漫游允许
修改历史          :
1.日   期  : 2012-12-19
  作   者  : l00171473
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryCLteRoamAllowPara, Test_AT_QryCLteRoamAllowPara_002)
{
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU  stLteRoamAllowedFlg;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement    =
            {AT_CMD_CLTEROAMALLOW,
            AT_SetCLteRoamAllowPara,    AT_SET_PARA_TIME,   AT_QryCLteRoamAllowPara,   AT_NOT_SET_TIME,    At_CmdTestProcOK,       AT_NOT_SET_TIME,
            VOS_NULL_PTR, AT_NOT_SET_TIME,
            AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
            (VOS_UINT8*)"^CLTEROAMALLOW",    (VOS_UINT8 *)"(0,1)"};

    ucIndex = 0;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    stLteRoamAllowedFlg.ucLteRoamAllowedFlg = 255;
    PS_MEM_SET(stLteRoamAllowedFlg.aucReserve,0x00,sizeof(stLteRoamAllowedFlg.aucReserve));
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_Lte_Internation_Roam_Config), outBoundP((void *)&stLteRoamAllowedFlg), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    EXPECT_EQ(AT_QryCLteRoamAllowPara(ucIndex), AT_OK);
    EXPECT_STREQ("^CLTEROAMALLOW:1", (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryCLteRoamAllowPara_004
测试用例标题      : 读出的NV漫游禁止标志位为0
预期结果          : 返回AT_OK, AT返回漫游不允许
修改历史          :
1.日   期  : 2012-12-19
  作   者  : l00171473
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryCLteRoamAllowPara, Test_AT_QryCLteRoamAllowPara_004)
{
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU  stNvimLteRoamAllowedFlg;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement    =
            {AT_CMD_CLTEROAMALLOW,
            AT_SetCLteRoamAllowPara,    AT_SET_PARA_TIME,   AT_QryCLteRoamAllowPara,   AT_NOT_SET_TIME,    At_CmdTestProcOK,       AT_NOT_SET_TIME,
            VOS_NULL_PTR, AT_NOT_SET_TIME,
            AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
            (VOS_UINT8*)"^CLTEROAMALLOW",    (VOS_UINT8 *)"(0,1)"};

    ucIndex = 0;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg = VOS_FALSE;
    PS_MEM_SET(stNvimLteRoamAllowedFlg.aucReserve,0x00,sizeof(stNvimLteRoamAllowedFlg.aucReserve));
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_Lte_Internation_Roam_Config), outBoundP((void *)&stNvimLteRoamAllowedFlg), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    EXPECT_EQ(AT_QryCLteRoamAllowPara(ucIndex), AT_OK);
    EXPECT_STREQ("^CLTEROAMALLOW:0", (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


/******************************************************************************
类名       : Test_AT_QryCbgPara
功能描述  : AT_QryCbgPara UT工程类
修改历史  :
 1.日   期   : 2012-01-05
   作   者   : z00214637
   修改内容 : DSDA GUNAS C CORE Project 项目新增类
******************************************************************************/
class Test_AT_QryCbgPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

    }

    void TearDown()
    {

    }

    VOS_UINT8                           ucIndex;
};

/******************************************************************************
测试用例编号: Test_AT_QryCbgPara_001
测试用例标题: 申请内存失败
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2012-01-05
   作   者  : z00214637
   修改内容 : DSDA GUNAS C CORE Project 项目新增
******************************************************************************/
TEST_F(Test_AT_QryCbgPara, Test_At_QryCbgPara_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    // 调用被测函数
    ulRslt = AT_QryCbgPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_QryCbgPara_002
测试用例标题: 申请内存成功，发送消息失败
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2012-01-05
   作   者  : z00214637
   修改内容 : DSDA GUNAS C CORE Project 项目新增
******************************************************************************/
TEST_F(Test_AT_QryCbgPara, Test_AT_QryCbgPara_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(Ps_SendMsg).stubs().will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_QryCbgPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_QryCbgPara_003
测试用例标题: 发送消息成功
预期结果    : AT下发VC消息头为APP_VC_MSG_QRY_FOREGROUND_REQ的消息包
        返回AT_WAIT_ASYNC_RETURN
修改历史    :
 1.日   期  : 2012-01-05
   作   者  : z00214637
   修改内容 : DSDA GUNAS C CORE Project 项目新增
******************************************************************************/
TEST_F(Test_AT_QryCbgPara, Test_AT_QryCbgPara_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(), any(),
              eq((VOS_UINT16)APP_VC_MSG_FOREGROUND_QRY),
              any(), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRslt = AT_QryCbgPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CBG_READ, gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRslt);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryBodySarOnPara
功能描述 : AT_QryBodySarOnPara UT工程类
修改历史 :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryBodySarOnPara: public ::testing::Test
{
public:
    public:
        VOS_UINT8                       ucIndex;
        AT_PAR_CMD_ELEMENT_STRU         stCmdInfo;

        void SetUp()
    {
        UT_STUB_INIT();
            ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;

            stCmdInfo.ulCmdIndex        = AT_CMD_BODYSARON;
            stCmdInfo.pfnSetProc        = AT_SetBodySarOnPara;
            stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
            stCmdInfo.pfnQryProc        = AT_QryBodySarOnPara;
            stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
            stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
            stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
            stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
            stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
            stCmdInfo.pszCmdName        = (VOS_UINT8*)"^BODYSARON";
            stCmdInfo.pszParam          = (VOS_UINT8*)"(0,1)";

            g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : AT_QryBodySarOnPara_001
测试用例标题      :  查询BODYSAR状态成功
预期结果          : 返回 AT_OK
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarOnPara, Test_AT_QryBodySarOnPara_001)
{
    // 变量声明
    VOS_UINT8                           ulRet;
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARON: 1";

    g_enAtBodySarState = AT_MTA_BODY_SAR_ON;

    // 调用被测函数
    ulRet = AT_QryBodySarOnPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryBodySarWcdmaPara
功能描述 : AT_QryBodySarWcdmaPara UT工程类
修改历史 :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryBodySarWcdmaPara: public ::testing::Test
{
public:
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
测试用例编号      : AT_QryBodySarWcdmaPara_001
测试用例标题      :  查询WCDMA功率门限，读取NV失败
预期结果          : 返回 AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarWcdmaPara, Test_AT_QryBodySarWcdmaPara_001)
{
    // 变量声明
    VOS_UINT8                           ulRet;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulRet = AT_QryBodySarWcdmaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : AT_QryBodySarWcdmaPara_002
测试用例标题      : 查询WCDMA功率门限，填充^BODYSARWCDMA命令参数结构体失败
预期结果          : 返回 AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarWcdmaPara, Test_AT_QryBodySarWcdmaPara_002)
{
    // 变量声明
    VOS_UINT8                           ulRet;
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;

    // 参数初始化
    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    stBodySarPara.usWBandNum = 1;
    stBodySarPara.astWBandPara[0].sPower = 17;
    stBodySarPara.astWBandPara[0].enBand = MTA_WCDMA_II_1900;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), outBoundP((void *)&stBodySarPara, (VOS_UINT32)sizeof(stBodySarPara)), eq((VOS_UINT32)sizeof(stBodySarPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_READ_UNABLE));

    // 调用被测函数
    ulRet = AT_QryBodySarWcdmaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : AT_QryBodySarWcdmaPara_003
测试用例标题      : 查询WCDMA功率门限成功
预期结果          : 返回 AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarWcdmaPara, Test_AT_QryBodySarWcdmaPara_003)
{
    // 变量声明
    VOS_UINT8                           ulRet;
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARWCDMA: (17,0000000A),(18,00000001)";

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    stBodySarPara.usWBandNum = 3;
    stBodySarPara.astWBandPara[0].sPower = 17;
    stBodySarPara.astWBandPara[1].sPower = 18;
    stBodySarPara.astWBandPara[2].sPower = 17;

    stBodySarPara.astWBandPara[0].enBand = MTA_WCDMA_II_1900;
    stBodySarPara.astWBandPara[1].enBand = MTA_WCDMA_I_2100;
    stBodySarPara.astWBandPara[2].enBand = MTA_WCDMA_IV_1700;

    PS_MEM_SET(&stWGBand, 0, sizeof(stWGBand));
    stWGBand.unWcdmaBand.ulBand                     = 0x00000003;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_I_2100   = 1;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_II_1900  = 1;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), outBoundP((void *)&stBodySarPara, (VOS_UINT32)sizeof(stBodySarPara)), eq((VOS_UINT32)sizeof(stBodySarPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND),outBoundP((void *)&stWGBand, (VOS_UINT32)sizeof(stWGBand)),eq((VOS_UINT32)sizeof(stWGBand)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_QryBodySarWcdmaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : AT_QryBodySarWcdmaPara_004
测试用例标题      : 查询WCDMA功率门限成功，所有功率门限相同
预期结果          : 返回 AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarWcdmaPara, Test_AT_QryBodySarWcdmaPara_004)
{
    // 变量声明
    VOS_UINT8                           ulRet;
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARWCDMA: (18,3FFFFFFF)";

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    stBodySarPara.usWBandNum = 2;
    stBodySarPara.astWBandPara[0].sPower = 18;
    stBodySarPara.astWBandPara[1].sPower = 18;

    stBodySarPara.astWBandPara[0].enBand = MTA_WCDMA_II_1900;
    stBodySarPara.astWBandPara[1].enBand = MTA_WCDMA_I_2100;

    PS_MEM_SET(&stWGBand, 0, sizeof(stWGBand));
    stWGBand.unWcdmaBand.ulBand                     = 0x00000003;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_I_2100   = 1;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_II_1900  = 1;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), outBoundP((void *)&stBodySarPara, (VOS_UINT32)sizeof(stBodySarPara)), eq((VOS_UINT32)sizeof(stBodySarPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND),outBoundP((void *)&stWGBand, (VOS_UINT32)sizeof(stWGBand)),eq((VOS_UINT32)sizeof(stWGBand)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_QryBodySarWcdmaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_FillBodySarWcdmaQryPara
功能描述 : AT_FillBodySarWcdmaQryPara UT工程类
修改历史 :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_FillBodySarWcdmaQryPara: public ::testing::Test
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
测试用例编号      : AT_FillBodySarWcdmaQryPara_001
测试用例标题      : 填充Body SAR参数到查询命令参数结构体，获取WCDMA Band能力NV值失败
预期结果          : 返回 VOS_ERR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_FillBodySarWcdmaQryPara, Test_AT_FillBodySarWcdmaQryPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARWCDMA_SET_PARA_STRU       stBodySarWcdmaPara;

    // 参数初始化
    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    PS_MEM_SET(&stBodySarWcdmaPara, 0, sizeof(stBodySarWcdmaPara));

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulRet = AT_FillBodySarWcdmaQryPara(&stBodySarPara,&stBodySarWcdmaPara);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : AT_FillBodySarWcdmaQryPara_002
测试用例标题      : 填充Body SAR参数到查询命令参数结构体成功
预期结果          : 返回 VOS_OK
修改历史          :
1.日   期  : 2013-03-13
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_FillBodySarWcdmaQryPara, Test_AT_FillBodySarWcdmaQryPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARWCDMA_SET_PARA_STRU       stBodySarWcdmaPara;

    // 参数初始化
    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    stBodySarPara.usWBandNum = 3;
    stBodySarPara.astWBandPara[0].sPower = 17;
    stBodySarPara.astWBandPara[1].sPower = 18;
    stBodySarPara.astWBandPara[2].sPower = 18;

    stBodySarPara.astWBandPara[0].enBand = MTA_WCDMA_II_1900;
    stBodySarPara.astWBandPara[1].enBand = MTA_WCDMA_I_2100;
    stBodySarPara.astWBandPara[2].enBand = MTA_WCDMA_IV_1700;

    PS_MEM_SET(&stWGBand, 0, sizeof(stWGBand));
    stWGBand.unWcdmaBand.ulBand                     = 0x0F;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_I_2100   = 1;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_II_1900  = 1;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_III_1800 = 1;
    stWGBand.unWcdmaBand.BitBand.BandWCDMA_IV_1700  = 1;

    PS_MEM_SET(&stBodySarWcdmaPara, 0, sizeof(stBodySarWcdmaPara));

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND),outBoundP((void *)&stWGBand, (VOS_UINT32)sizeof(stWGBand)),eq((VOS_UINT32)sizeof(stWGBand)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_FillBodySarWcdmaQryPara(&stBodySarPara,&stBodySarWcdmaPara);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);

    EXPECT_EQ(3, stBodySarWcdmaPara.ucParaNum);
    EXPECT_EQ(17, stBodySarWcdmaPara.asPower[0]);
    EXPECT_EQ(0x00000002, stBodySarWcdmaPara.aulBand[0]);
    EXPECT_EQ(18, stBodySarWcdmaPara.asPower[1]);
    EXPECT_EQ(0x00000009, stBodySarWcdmaPara.aulBand[1]);
    EXPECT_EQ(24, stBodySarWcdmaPara.asPower[2]);
    EXPECT_EQ(0x00000004, stBodySarWcdmaPara.aulBand[2]);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryBodySarGsmPara
功能描述 : AT_QryBodySarGsmPara UT工程类
修改历史 :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryBodySarGsmPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryBodySarGsmPara_001
测试用例标题      : NV项读取失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarGsmPara, Test_AT_QryBodySarGsmPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), any(), any())
        .will(returnValue((VOS_UINT32)NV_INIT_FAIL));

    // 调用被测函数
    ulRet = AT_QryBodySarGsmPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryBodySarGsmPara_002
测试用例标题      : NV项读取成功，填充默认值失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarGsmPara, Test_AT_QryBodySarGsmPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), any(), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(AT_GetGsmBandCapa)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    ulRet = AT_QryBodySarGsmPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryBodySarGsmPara_003
测试用例标题      : NV项读取成功，填充默认值成功，所有频段功率门限不同
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarGsmPara, Test_AT_QryBodySarGsmPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand        = {0};
    MTA_BODY_SAR_PARA_STRU              stBodySarPara   = {0};
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARGSM: (15,00000001),(17,00000002),(19,00000004),(21,00000008),(16,00010000),(18,00020000),(20,00040000),(22,00080000)";
    stWGBand.unGsmBand.ulBand   = 0xDC;
    stBodySarPara.ulGBandMask   = 0x000F000F;
    stBodySarPara.astGBandPara[AT_GSM_850].sGPRSPower  = 15;
    stBodySarPara.astGBandPara[AT_GSM_850].sEDGEPower  = 16;
    stBodySarPara.astGBandPara[AT_GSM_900].sGPRSPower  = 17;
    stBodySarPara.astGBandPara[AT_GSM_900].sEDGEPower  = 18;
    stBodySarPara.astGBandPara[AT_GSM_1800].sGPRSPower = 19;
    stBodySarPara.astGBandPara[AT_GSM_1800].sEDGEPower = 20;
    stBodySarPara.astGBandPara[AT_GSM_1900].sGPRSPower = 21;
    stBodySarPara.astGBandPara[AT_GSM_1900].sEDGEPower = 22;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), outBoundP((void *)&stBodySarPara, sizeof(stBodySarPara)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND), outBoundP((void *)&stWGBand, sizeof(stWGBand)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_QryBodySarGsmPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryBodySarGsmPara_004
测试用例标题      : NV项读取成功，填充默认值成功，部分频段功率门限相同
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarGsmPara, Test_AT_QryBodySarGsmPara_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand        = {0};
    MTA_BODY_SAR_PARA_STRU              stBodySarPara   = {0};
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARGSM: (15,00010001),(17,00000002),(19,00000004),(22,000C0008),(18,00020000)";
    stWGBand.unGsmBand.ulBand   = 0xDC;
    stBodySarPara.ulGBandMask   = 0x000F000F;
    stBodySarPara.astGBandPara[AT_GSM_850].sGPRSPower  = 15;
    stBodySarPara.astGBandPara[AT_GSM_850].sEDGEPower  = 15;
    stBodySarPara.astGBandPara[AT_GSM_900].sGPRSPower  = 17;
    stBodySarPara.astGBandPara[AT_GSM_900].sEDGEPower  = 18;
    stBodySarPara.astGBandPara[AT_GSM_1800].sGPRSPower = 19;
    stBodySarPara.astGBandPara[AT_GSM_1800].sEDGEPower = 22;
    stBodySarPara.astGBandPara[AT_GSM_1900].sGPRSPower = 22;
    stBodySarPara.astGBandPara[AT_GSM_1900].sEDGEPower = 22;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), outBoundP((void *)&stBodySarPara, sizeof(stBodySarPara)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND), outBoundP((void *)&stWGBand, sizeof(stWGBand)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_QryBodySarGsmPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_QryBodySarGsmPara_005
测试用例标题      : NV项读取成功，填充默认值成功，所有频段功率门限相同
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarGsmPara, Test_AT_QryBodySarGsmPara_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand        = {0};
    MTA_BODY_SAR_PARA_STRU              stBodySarPara   = {0};
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARGSM: (20,3FFFFFFF)";
    stWGBand.unGsmBand.ulBand   = 0xDC;
    stBodySarPara.ulGBandMask   = 0x000F000F;
    stBodySarPara.astGBandPara[AT_GSM_850].sGPRSPower  = 20;
    stBodySarPara.astGBandPara[AT_GSM_850].sEDGEPower  = 20;
    stBodySarPara.astGBandPara[AT_GSM_900].sGPRSPower  = 20;
    stBodySarPara.astGBandPara[AT_GSM_900].sEDGEPower  = 20;
    stBodySarPara.astGBandPara[AT_GSM_1800].sGPRSPower = 20;
    stBodySarPara.astGBandPara[AT_GSM_1800].sEDGEPower = 20;
    stBodySarPara.astGBandPara[AT_GSM_1900].sGPRSPower = 20;
    stBodySarPara.astGBandPara[AT_GSM_1900].sEDGEPower = 20;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), outBoundP((void *)&stBodySarPara, sizeof(stBodySarPara)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND), outBoundP((void *)&stWGBand, sizeof(stWGBand)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_QryBodySarGsmPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryBodySarGsmPara_006
测试用例标题      : 用户未设置过Body SAR功能GSM的功率门限值
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2013-03-13
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryBodySarGsmPara, Test_AT_QryBodySarGsmPara_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand        = {0};
    MTA_BODY_SAR_PARA_STRU              stBodySarPara   = {0};
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr    = "^BODYSARGSM: (33,00000003),(30,0000000C),(27,00030000),(26,000C0000)";
    stWGBand.unGsmBand.ulBand   = 0xDC;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_BODY_SAR_PARA), outBoundP((void *)&stBodySarPara, sizeof(stBodySarPara)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WG_RF_MAIN_BAND), outBoundP((void *)&stWGBand, sizeof(stWGBand)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRet = AT_QryBodySarGsmPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_EQ(VOS_StrLen(pcExpectStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpectStr, (VOS_CHAR*)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryS0Para
功能描述 : At_QryS0Para UT工程类
修改历史     :
1.日   期  : 2013-03-07
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryS0Para: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryS0Para_001
测试用例标题      : modem0的S0自动应答时间为5
预期结果          : pgucAtSndCodeAddr=5
修改历史          :
1.日   期         : 2013-03-07
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryS0Para, Test_At_QryS0Para_001)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pstCcCtx->stS0TimeInfo.ucS0TimerLen = 5;

    /* 调用函数 */
    ulRst = At_QryS0Para(ucIndex);

    /* 检查结果 */
    pcExpect = "5";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(1, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_OK, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryS0Para_002
测试用例标题      : modem1的S0自动应答时间为6
预期结果          : pgucAtSndCodeAddr=6
修改历史          :
1.日   期         : 2013-03-07
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryS0Para, Test_At_QryS0Para_002)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pstCcCtx->stS0TimeInfo.ucS0TimerLen = 6;

    /* 调用函数 */
    ulRst = At_QryS0Para(ucIndex);

    /* 检查结果 */
    pcExpect = "6";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(1, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_OK, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryUssdModePara
功能描述 : At_QryUssdModePara UT工程类
修改历史     :
1.日   期  : 2013-03-07
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryUssdModePara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryUssdModePara_001
测试用例标题      : Modem0的USSDMODE为0，查询命令AT^USSDMODE?
预期结果          : ^USSDMODE：0
修改历史          :
1.日   期         : 2013-03-07
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryUssdModePara, Test_At_QryUssdModePara_001)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->usUssdTransMode = 0;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"^USSDMODE";

    ulRst = At_QryUssdModePara(ucIndex);

    /* 检查结果 */
    pcExpect = "^USSDMODE: 0";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);
    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryUssdModePara_002
测试用例标题      : Modem1的USSDMODE为1，查询命令AT^USSDMODE?
预期结果          : ^USSDMODE：1
修改历史          :
1.日   期         : 2013-03-07
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryUssdModePara, Test_At_QryUssdModePara_002)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->usUssdTransMode = 1;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"^USSDMODE";

    ulRst = At_QryUssdModePara(ucIndex);

    /* 检查结果 */
    pcExpect = "^USSDMODE: 1";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCusdPara
功能描述 : At_QryCusdPara UT工程类
修改历史     :
1.日   期  : 2013-03-07
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCusdPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCusdPara_001
测试用例标题      : 查询CUSD，给MTA发送查询消息成功
预期结果          : 等待异步回复
修改历史          :
1.日   期         : 2013-03-07
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCusdPara, Test_At_QryCusdPara_001)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CUSD";

    ulRst = At_QryCusdPara(ucIndex);

    /* 检查结果 */
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    EXPECT_EQ(AT_CMD_UNSOLICITED_RPT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCusdPara_002
测试用例标题      : Modem1的ucCusdType为1，查询命令AT+CUSD?
预期结果          : +CUSD：1
修改历史          :
1.日   期         : 2013-03-07
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCusdPara, Test_At_QryCusdPara_002)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    MN_OPERATION_ID_T                       ucOpId;
    VOS_UINT16                              usMsgType;
    VOS_UINT32                              ulRcvPid;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CUSD";

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CUSD_RPT_TYPE;
    ucOpId                  = 0;
    usMsgType               = ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ;
    ulRcvPid                = I0_UEPS_PID_MTA;

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
                eq(ucOpId),
                eq(usMsgType),
                mirror((void *)&stAtCmd, sizeof(stAtCmd)),
                eq((VOS_UINT32)sizeof(stAtCmd)),
                eq((VOS_UINT32)ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    ulRst = At_QryCusdPara(ucIndex);

    /* 检查结果 */
    EXPECT_EQ(AT_ERROR, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCmodPara
功能描述 : At_QryCmodPara UT工程类
修改历史     :
1.日   期  : 2013-03-07
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCmodPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCmodPara_001
测试用例标题      : Modem0的呼叫模式为0
预期结果          : 查询结果+CMOD:0
修改历史          :
1.日   期         : 2013-03-07
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCmodPara, Test_At_QryCmodPara_001)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->enCModType = 0;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CMOD";

    ulRst = At_QryCmodPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CMOD: 0";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCmodPara_002
测试用例标题      : Modem1的呼叫模式为1
预期结果          : 查询结果+CMOD:1
修改历史          :
1.日   期         : 2013-03-07
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCmodPara, Test_At_QryCmodPara_002)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->enCModType = 1;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CMOD";

    ulRst = At_QryCmodPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CMOD: 1";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );
    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif
/*****************************************************************************
 类名       : Test_At_QryTimePara
 功能描述   : At_QryTimePara UT工程类
 修改历史   :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryTimePara: public ::testing::Test
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
 测试用例编号   : Test_At_QryTimePara_001
 测试用例标题   : 查询是否主动上报网络下发的时间信息,给MTA发送消息成功
 预期结果       : 异步等待查询回复
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryTimePara,Test_At_QryTimePara_001)
{
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_TIME,
        At_SetTimePara,         AT_SET_PARA_TIME,   At_QryTimePara,         AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR,   AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"^TIME",    (VOS_UINT8*)"(0,1)"};

    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    MN_OPERATION_ID_T                       ucOpId;
    VOS_UINT16                              usMsgType;
    VOS_UINT32                              ulRcvPid;
    VOS_UINT32                              ulRst;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_TIME_RPT_TYPE;
    ucOpId                  = 0;
    usMsgType               = ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ;
    ulRcvPid                = I0_UEPS_PID_MTA;

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
                eq(ucOpId),
                eq(usMsgType),
                mirror((void *)&stAtCmd, sizeof(stAtCmd)),
                eq((VOS_UINT32)sizeof(stAtCmd)),
                eq((VOS_UINT32)ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRst = At_QryTimePara(ucIndex);

    /* 执行检查 */
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    EXPECT_EQ(AT_CMD_UNSOLICITED_RPT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();

}

/*******************************************************************
 测试用例编号   : Test_At_QryTimePara_002
 测试用例标题   : 查询是否主动上报网络下发的时间信息,给MTA发送消息失败
 预期结果       : 返回AT_ERROR
 修改历史       :
 1.日   期  : 2013-04-15
   作   者  : s00217060
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryTimePara,Test_At_QryTimePara_002)
{
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_TIME,
        At_SetTimePara,         AT_SET_PARA_TIME,   At_QryTimePara,         AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR,   AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"^TIME",    (VOS_UINT8*)"(0,1)"};

    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    MN_OPERATION_ID_T                       ucOpId;
    VOS_UINT16                              usMsgType;
    VOS_UINT32                              ulRcvPid;
    VOS_UINT32                              ulRst;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_TIME_RPT_TYPE;
    ucOpId                  = 0;
    usMsgType               = ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ;
    ulRcvPid                = I0_UEPS_PID_MTA;

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
                eq(ucOpId),
                eq(usMsgType),
                mirror((void *)&stAtCmd, sizeof(stAtCmd)),
                eq((VOS_UINT32)sizeof(stAtCmd)),
                eq((VOS_UINT32)ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRst = At_QryTimePara(ucIndex);

    /* 执行检查 */
    EXPECT_EQ(AT_ERROR, ulRst);

    GlobalMockObject::verify();

}

/*****************************************************************************
 类名       : Test_At_QryCtzrPara
 功能描述   : At_QryCtzrPara UT工程类
 修改历史   :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCtzrPara: public ::testing::Test
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
 测试用例编号   : Test_At_QryCtzrPara_001
 测试用例标题   : 查询是否主动上报网络下发的时区更新,给MTA发送消息成功
 预期结果       : 异步等待查询回复
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCtzrPara,Test_At_QryCtzrPara_001)
{
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "+CTZR: 1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_CTZR,
        At_SetCtzrPara,     AT_SET_PARA_TIME, At_QryCtzrPara,    AT_QRY_PARA_TIME,  VOS_NULL_PTR,       AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CTZR",    (VOS_UINT8*)"(0,1)"};

    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    MN_OPERATION_ID_T                       ucOpId;
    VOS_UINT16                              usMsgType;
    VOS_UINT32                              ulRcvPid;
    VOS_UINT32                              ulRst;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CTZR_RPT_TYPE;
    ucOpId                  = 0;
    usMsgType               = ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ;
    ulRcvPid                = I0_UEPS_PID_MTA;

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
                eq(ucOpId),
                eq(usMsgType),
                mirror((void *)&stAtCmd, sizeof(stAtCmd)),
                eq((VOS_UINT32)sizeof(stAtCmd)),
                eq((VOS_UINT32)ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRst = At_QryCtzrPara(ucIndex);

    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    EXPECT_EQ(AT_CMD_UNSOLICITED_RPT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();

}

/*******************************************************************
 测试用例编号   : Test_At_QryCtzrPara_002
 测试用例标题   : 查询是否主动上报网络下发的时区更新,给MTA发送消息失败
 预期结果       : 返回AT_ERROR
 修改历史       :
 1.日   期  : 2013-04-18
   作   者  : s00217060
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCtzrPara,Test_At_QryCtzrPara_002)
{
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "+CTZR: 1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_CTZR,
        At_SetCtzrPara,     AT_SET_PARA_TIME, At_QryCtzrPara,    AT_QRY_PARA_TIME,  VOS_NULL_PTR,       AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CTZR",    (VOS_UINT8*)"(0,1)"};

    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    MN_OPERATION_ID_T                       ucOpId;
    VOS_UINT16                              usMsgType;
    VOS_UINT32                              ulRcvPid;
    VOS_UINT32                              ulRst;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CTZR_RPT_TYPE;
    ucOpId                  = 0;
    usMsgType               = ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ;
    ulRcvPid                = I0_UEPS_PID_MTA;

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
                eq(ucOpId),
                eq(usMsgType),
                mirror((void *)&stAtCmd, sizeof(stAtCmd)),
                eq((VOS_UINT32)sizeof(stAtCmd)),
                eq((VOS_UINT32)ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRst = At_QryCtzrPara(ucIndex);

    EXPECT_EQ(AT_ERROR, ulRst);

    GlobalMockObject::verify();

}

/*****************************************************************************
 类名       : Test_At_QryCplsPara
 功能描述   : At_QryCplsPara UT工程类
 修改历史   :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCplsPara: public ::testing::Test
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
 测试用例编号   : Test_At_QryCplsPara_001
 测试用例标题   : 查询CPLS的设置情况
 预期结果       : 输出查询结果
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCplsPara,Test_At_QryCplsPara_001)
{
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "+CPLS: 2";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_CPLS,
        At_SetCplsPara,     AT_SET_PARA_TIME, At_QryCplsPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CPLS",       (VOS_UINT8*)"(0,1,2)"};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    AT_GetModemNetCtxAddrFromClientId(ucIndex)->enPrefPlmnType = MN_PH_PREF_PLMN_HPLMN;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // 调用被测函数
    At_QryCplsPara(ucIndex);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_At_QryCpolPara
 功能描述   : At_QryCpolPara UT工程类
 修改历史   :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCpolPara: public ::testing::Test
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
 测试用例编号   : Test_At_QryCpolPara_001
 测试用例标题   : 查询CPOL的设置情况成功
 预期结果       : 输出查询结果
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
 2.日    期   : 2014年01月15日
   作    者   : f62575
   修改内容   : DTS2014011301359，+CPOL命令支持超过37个UPLMN
*******************************************************************/
TEST_F(Test_At_QryCpolPara,Test_At_QryCpolPara_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_PREF_PLMN_OPERATE_STRU       stPrefPlmn;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    memset(&stPrefPlmn, 0, sizeof(stPrefPlmn));
    stPrefPlmn.enPrefPlmnOperType = MN_PH_PrefPLMN_QUREY;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);
    pstNetCtx->enPrefPlmnType = MN_PH_PREF_PLMN_HPLMN;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = At_QryCpolPara(ucIndex);

    EXPECT_EQ(AT_CMD_CPOL_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
 测试用例编号   : Test_At_QryCpolPara_002
 测试用例标题   : 查询CPOL的设置情况失败
 预期结果       : 返回AT_ERROR
 修改历史       :
 1.日   期  : 2013-03-08
   作   者  : f00179208
   修改内容 : 新建CASE
 2.日    期   : 2014年01月15日
   作    者   : f62575
   修改内容   : DTS2014011301359，查询函数调用失败返回值修改AT_CME_INCORRECT_PARAMETERS=》AT_ERROR
*******************************************************************/
TEST_F(Test_At_QryCpolPara,Test_At_QryCpolPara_002)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_PREF_PLMN_OPERATE_STRU       stPrefPlmn;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    memset(&stPrefPlmn, 0, sizeof(stPrefPlmn));
    stPrefPlmn.enPrefPlmnOperType = MN_PH_PrefPLMN_QUREY;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);
    pstNetCtx->enPrefPlmnType = MN_PH_PREF_PLMN_HPLMN;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = At_QryCpolPara(ucIndex);

    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_At_QryCpolPara_003
 测试用例标题   : 查询CPOL的操作类型不是查询
 预期结果       : 返回AT_ERROR
 修改历史       :
1.日    期   : 2014年01月15日
  作    者   : f62575
  修改内容   : DTS2014011301359
*******************************************************************/
TEST_F(Test_At_QryCpolPara,Test_At_QryCpolPara_003)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_PREF_PLMN_OPERATE_STRU       stPrefPlmn;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_BUTT;

    memset(&stPrefPlmn, 0, sizeof(stPrefPlmn));
    stPrefPlmn.enPrefPlmnOperType = MN_PH_PrefPLMN_QUREY;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);
    pstNetCtx->enPrefPlmnType = MN_PH_PREF_PLMN_HPLMN;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(never())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = At_QryCpolPara(ucIndex);

    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryCrcPara
功能描述 : At_QryCrcPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCrcPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCrcPara_001
测试用例标题      : 当前Modem0的CRC为1，查询CRC参数
预期结果          : 结果为+CRC：1
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCrcPara, Test_At_QryCrcPara_001)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->ucCrcType = 1;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CRC";

    ulRst = At_QryCrcPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CRC: 1";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCrcPara_002
测试用例标题      : 当前Modem1的CRC为0，查询CRC参数
预期结果          : 结果为+CRC：0
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCrcPara, Test_At_QryCrcPara_002)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->ucCrcType = 0;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CRC";

    ulRst = At_QryCrcPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CRC: 0";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCcwaPara
功能描述 : At_QryCcwaPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCcwaPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);

        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCcwaPara_001
测试用例标题      : 当前Modem0的ucCcwaType为1
预期结果          : 结果为+CCWA：1
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCcwaPara, Test_At_QryCcwaPara_001)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->ucCcwaType = 1;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CCWA";

    ulRst = At_QryCcwaPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CCWA: 1";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCcwaPara_002
测试用例标题      : 当前Modem1的ucCcwaType为0
预期结果          : 结果为+CCWA：0
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCcwaPara, Test_At_QryCcwaPara_002)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->ucCcwaType = 0;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CCWA";

    ulRst = At_QryCcwaPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CCWA: 0";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCssnPara
功能描述 : At_QryCssnPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCssnPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCssnPara_001
测试用例标题      : Modem0查询命令+CSSN
预期结果          : 结果为+CSSN：0,1
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCssnPara, Test_At_QryCssnPara_001)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    MN_OPERATION_ID_T                       ucOpId;
    VOS_UINT16                              usMsgType;
    VOS_UINT32                              ulRcvPid;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CSSN";

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CSSN_RPT_TYPE;
    ucOpId                  = 0;
    usMsgType               = ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ;
    ulRcvPid                = I0_UEPS_PID_MTA;

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
                eq(ucOpId),
                eq(usMsgType),
                mirror((void *)&stAtCmd, sizeof(stAtCmd)),
                eq((VOS_UINT32)sizeof(stAtCmd)),
                eq((VOS_UINT32)ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRst = At_QryCssnPara(ucIndex);

    /* 检查结果 */
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);
    EXPECT_EQ(AT_CMD_UNSOLICITED_RPT_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCssnPara_002
测试用例标题      : Modem1查询命令+CSSN
预期结果          : 结果为+CSSN：1,1
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCssnPara, Test_At_QryCssnPara_002)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    MN_OPERATION_ID_T                       ucOpId;
    VOS_UINT16                              usMsgType;
    VOS_UINT32                              ulRcvPid;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CSSN";

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CSSN_RPT_TYPE;
    ucOpId                  = 0;
    usMsgType               = ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ;
    ulRcvPid                = I0_UEPS_PID_MTA;

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
                eq(ucOpId),
                eq(usMsgType),
                mirror((void *)&stAtCmd, sizeof(stAtCmd)),
                eq((VOS_UINT32)sizeof(stAtCmd)),
                eq((VOS_UINT32)ulRcvPid))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    ulRst = At_QryCssnPara(ucIndex);

    /* 检查结果 */
    EXPECT_EQ(AT_ERROR, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCbstPara
功能描述 : At_QryCbstPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCbstPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCbstPara_001
测试用例标题      : 查询Modem0的CBST参数
预期结果          : 返回+CBST
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCbstPara,Test_At_QryCbstPara_001)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->stCbstDataCfg.enSpeed = 134;
    pstSsCtx->stCbstDataCfg.enName = 1;
    pstSsCtx->stCbstDataCfg.enConnElem = 0;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CBST";

    ulRst = At_QryCbstPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CBST: 134,1,0";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCbstPara_002
测试用例标题      : 查询Modem1的CBST参数
预期结果          : 返回+CBST
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCbstPara,Test_At_QryCbstPara_002)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->stCbstDataCfg.enSpeed = 134;
    pstSsCtx->stCbstDataCfg.enName = 1;
    pstSsCtx->stCbstDataCfg.enConnElem = 0;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CBST";

    ulRst = At_QryCbstPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CBST: 134,1,0";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCcugPara
功能描述 : At_QryCcugPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
作   者  :   z00220246
修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCcugPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_At_QryCcugPara_001
测试用例标题      : 查询Modem0的CCcug参数，当前bIndexPresent为0
预期结果          : 返回+ccug
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCcugPara, Test_At_QryCcugPara_001)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->stCcugCfg.bEnable = 1;
    pstSsCtx->stCcugCfg.bIndexPresent = 0;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CCUG";

    ulRst = At_QryCcugPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CCUG: 1,10,0";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCcugPara_002
测试用例标题      : 查询Modem1的CCcug参数，当前bIndexPresent不为0
预期结果          : 返回+ccug
修改历史          :
1.日   期  : 2013-03-11
  作   者         : z00220246
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCcugPara, Test_At_QryCcugPara_002)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->stCcugCfg.bEnable = 0;
    pstSsCtx->stCcugCfg.bIndexPresent = 1;
    pstSsCtx->stCcugCfg.ulIndex = 1;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CCUG";

    ulRst = At_QryCcugPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CCUG: 0,1,0";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCmgfPara
功能描述 : At_QryCmgfPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  :   l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCmgfPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCmgfPara_001
测试用例标题      : 查询Modem0 CMGF参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCmgfPara,Test_At_QryCmgfPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CMGF: 0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CMGF,
                                                        At_SetCmgfPara,     AT_NOT_SET_TIME,
                                                        At_QryCmgfPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"+CMGF",    (VOS_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCmgfPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCmgfPara_002
测试用例标题      : 查询Modem1 CMGF参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCmgfPara,Test_At_QryCmgfPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CMGF: 1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CMGF,
                                                        At_SetCmgfPara,     AT_NOT_SET_TIME,
                                                        At_QryCmgfPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"+CMGF",    (VOS_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCmgfPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCsdhPara
功能描述 : At_QryCsdhPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  :   l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCsdhPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCsdhPara_001
测试用例标题      : 查询Modem0 CNMI参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdhPara,Test_At_QryCsdhPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CSDH: 0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSDH,
                                                        At_SetCsdhPara,     AT_NOT_SET_TIME,
                                                        At_QryCsdhPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED,       CMD_TBL_PIN_IS_LOCKED,
                                                        (TAF_UINT8*)"+CSDH",    (TAF_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.ucCsdhType             = AT_CSDH_NOT_SHOW_TYPE;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCsdhPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCsdhPara_002
测试用例标题      : 查询Modem1 CNMI参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsdhPara,Test_At_QryCsdhPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CSDH: 1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSDH,
                                                        At_SetCsdhPara,     AT_NOT_SET_TIME,
                                                        At_QryCsdhPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED,       CMD_TBL_PIN_IS_LOCKED,
                                                        (TAF_UINT8*)"+CSDH",    (TAF_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCsdhPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCmsrPara
功能描述 : At_QryCmsrPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  :   l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCmsrPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCmsrPara_001
测试用例标题      : 查询Modem0 CMSR参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCmsrPara,Test_At_QryCmsrPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^CMSR: 0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CMSR,
                                                        At_SetCmsrPara,     AT_NOT_SET_TIME,
                                                        At_QryCmsrPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED,       CMD_TBL_PIN_IS_LOCKED,
                                                        (TAF_UINT8*)"^CMSR", (VOS_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.ucParaCmsr             = 0;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCmsrPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCmsrPara_002
测试用例标题      : 查询Modem1 CMSR参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCmsrPara,Test_At_QryCmsrPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^CMSR: 1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CMSR,
                                        At_SetCmsrPara,     AT_NOT_SET_TIME,
                                        At_QryCmsrPara,     AT_NOT_SET_TIME,
                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                        AT_CMS_OPERATION_NOT_ALLOWED,       CMD_TBL_PIN_IS_LOCKED,
                                        (TAF_UINT8*)"^CMSR", (VOS_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.ucParaCmsr             = 1;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCmsrPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCsmsPara
功能描述 : At_QryCsmsPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  :   l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCsmsPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCsmsPara_001
测试用例标题      : 查询Modem0 CSMS参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsmsPara,Test_At_QryCsmsPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CSMS: 0,1,1,1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSMS,
                                                        At_SetCsmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCsmsPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CSMS",    (VOS_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCsmsMsgVersion       = MN_MSG_CSMS_MSG_VERSION_PHASE2;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCsmsPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCsmsPara_002
测试用例标题      : 查询Modem1 CSMS参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsmsPara,Test_At_QryCsmsPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CSMS: 1,1,1,1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSMS,
                                                        At_SetCsmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCsmsPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CSMS",    (VOS_UINT8*)"(0,1)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCsmsMsgVersion       = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCsmsPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCgsmsPara
功能描述 : At_QryCgsmsPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  :   l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCgsmsPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCgsmsPara_001
测试用例标题      : 查询Modem0 CGSMS参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCgsmsPara,Test_At_QryCgsmsPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGSMS: 0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CGSMS,
                                                        At_SetCgsmsPara,    AT_NOT_SET_TIME,
                                                        At_QryCgsmsPara,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CGSMS",   (VOS_UINT8*)"(0-3)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId           = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCgsmsSendDomain.enSendDomain = MN_MSG_SEND_DOMAIN_PS;
    g_stParseContext[ucIndex].pstCmdElement                             = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCgsmsPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCgsmsPara_002
测试用例标题      : 查询Modem1 CGSMS参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCgsmsPara,Test_At_QryCgsmsPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGSMS: 1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CGSMS,
                                                        At_SetCgsmsPara,    AT_NOT_SET_TIME,
                                                        At_QryCgsmsPara,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CGSMS",   (VOS_UINT8*)"(0-3)"};

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId           = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCgsmsSendDomain.enSendDomain = MN_MSG_SEND_DOMAIN_CS;
    g_stParseContext[ucIndex].pstCmdElement                             = &stCmdElement;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCgsmsPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCsmpPara
功能描述 : At_QryCsmpPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCsmpPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCsmpPara_001
测试用例标题      : 查询Modem0 CSMP参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsmpPara,Test_At_QryCsmpPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CSMP: 17,167,0,0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSMP,
                                                        At_SetCsmpPara,     AT_SET_PARA_TIME,
                                                        At_QryCsmpPara,     AT_NOT_SET_TIME,
                                                        At_CmdTestProcOK,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CSMP",    TAF_NULL_PTR};
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);
    pstSmsCtx->stCscaCsmpInfo.bFoUsed = TAF_TRUE;
    pstSmsCtx->stCscaCsmpInfo.ucFo    = 17;
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid = 0;
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs = 0;
    pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    pstSmsCtx->stCscaCsmpInfo.stVp.u.ucOtherTime = AT_CSMP_SUBMIT_VP_DEFAULT_VALUE;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCsmpPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCsmpPara_002
测试用例标题      : 查询Modem1 CSMP参数成功
预期结果          : 返回AT_OK
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCsmpPara,Test_At_QryCsmpPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CSMP: ,,0,0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSMP,
                                                        At_SetCsmpPara,     AT_SET_PARA_TIME,
                                                        At_QryCsmpPara,     AT_NOT_SET_TIME,
                                                        At_CmdTestProcOK,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CSMP",    TAF_NULL_PTR};
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP5_INDEX;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);
    pstSmsCtx->stCscaCsmpInfo.bFoUsed = TAF_FALSE;
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid = 0;
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs = 0;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCsmpPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_At_QryCsmpPara_003
测试用例标题      : 查询Modem0 CSMP参数成功
预期结果          : 默认配置为+CSMP: ,,0,0
修改历史
  1.日    期   : 2014年03月04日
    作    者   : f62575
    修改内容   : DTS2014030801193, +CSMP初始值不生效
*******************************************************************/
TEST_F(Test_At_QryCsmpPara,Test_At_QryCsmpPara_003)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CSMP: ,,0,0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSMP,
                                                        At_SetCsmpPara,     AT_SET_PARA_TIME,
                                                        At_QryCsmpPara,     AT_NOT_SET_TIME,
                                                        At_CmdTestProcOK,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CSMP",    TAF_NULL_PTR};
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);
    pstSmsCtx->stCscaCsmpInfo.bFoUsed = TAF_FALSE;
    pstSmsCtx->stCscaCsmpInfo.ucFo    = 0;
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid = 0;
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs = 0;
    pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod     = MN_MSG_VALID_PERIOD_RELATIVE;
    pstSmsCtx->stCscaCsmpInfo.stVp.u.ucOtherTime     = AT_CSMP_SUBMIT_VP_DEFAULT_VALUE;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_QryCsmpPara(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryCpmsPara
功能描述 : At_QryCpmsPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCpmsPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCpmsPara_001
测试用例标题      : 查询Modem0 CPMS参数
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCpmsPara,Test_At_QryCpmsPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    // MOCKER操作
    MOCKER(At_GetSmsStorage).stubs().will(returnValue((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRslt = At_QryCpmsPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CPMS_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCpmsPara_002
测试用例标题      : 查询Modem1 CPMS参数失败
预期结果          : 返回AT_ERROR
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCpmsPara,Test_At_QryCpmsPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    // MOCKER操作
    MOCKER(At_GetSmsStorage).stubs().will(returnValue((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRslt = At_QryCpmsPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_At_QryCmgdPara
功能描述 : At_QryCmgdPara UT工程类
修改历史     :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryCmgdPara: public ::testing::Test
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
测试用例编号      : Test_At_QryCmgdPara_001
测试用例标题      : 查询Modem0 CMGD参数
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCmgdPara,Test_At_QryCmgdPara_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    // MOCKER操作
    MOCKER(MN_MSG_Delete_Test).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    ulRslt = At_QryCmgdPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_CMGD_TEST, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_At_QryCmgdPara_002
测试用例标题      : 查询Modem1 CMGD参数
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史
  1.日    期: 2013年3月11日
    作    者: l00227485
    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCmgdPara,Test_At_QryCmgdPara_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    // MOCKER操作
    MOCKER(MN_MSG_Delete_Test).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    ulRslt = At_QryCmgdPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_PEND, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名    : Test_At_QryQosPara
功能描述: At_QryQosPara  UT工程类
修改历史    :
1.日  期 : 2013-03-18
  作  者 :   l60609
  修改内容: 新生成类
*****************************************************************************/
class Test_At_QryQosPara: public ::testing::Test
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
测试用例编号     : Test_At_QryQosPara_001
测试用例标题     : MODEM 0 查询QOS命令
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l60609
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryQosPara, Test_At_QryQosPara_001)
{
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU     stATTrafficClass;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    AT_CLIENT_CTX_STRU                 *pstClientCtx;
    char                                acExpectedResult[] = "^QOS:0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_QOS,
                                                        At_SetQosPara,       AT_NOT_SET_TIME,    At_QryQosPara,         AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^QOS",      VOS_NULL_PTR};

    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);

    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    /* 命令参数 */
    stATTrafficClass.ucStatus       = NV_ITEM_ACTIVE;
    stATTrafficClass.ucTrafficClass = AT_QOS_TRAFFIC_CLASS_SUBSCRIBE;


    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_TRAFFIC_CLASS_Type), outBoundP((void *)&stATTrafficClass), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRslt = At_QryQosPara(ucIndex);

    EXPECT_EQ(AT_OK, ulRslt);
    EXPECT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号     : Test_At_QryQosPara_002
测试用例标题     : MODEM 1 查询QOS命令
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l60609
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryQosPara, Test_At_QryQosPara_002)
{
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU     stATTrafficClass;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    AT_CLIENT_CTX_STRU                 *pstClientCtx;
    char                                acExpectedResult[] = "^QOS:1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_QOS,
                                                        At_SetQosPara,       AT_NOT_SET_TIME,    At_QryQosPara,         AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^QOS",      VOS_NULL_PTR};

    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);

    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    /* 命令参数 */
    stATTrafficClass.ucStatus       = NV_ITEM_ACTIVE;
    stATTrafficClass.ucTrafficClass = AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL;


    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_TRAFFIC_CLASS_Type), outBoundP((void *)&stATTrafficClass, (VOS_UINT32)sizeof(stATTrafficClass)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRslt = At_QryQosPara(ucIndex);

    EXPECT_EQ(AT_OK, ulRslt);
    EXPECT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名    : Test_At_QrySDomainPara
功能描述: At_QrySDomainPara  UT工程类
修改历史    :
1.日  期 : 2013-03-18
  作  者 :   l60609
  修改内容: 新生成类
*****************************************************************************/
class Test_At_QrySDomainPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));
    }
    void TearDown()
    {

    }
};
/*******************************************************************
测试用例编号     : Test_At_QrySDomainPara_001
测试用例标题     : MODEM 0 查询SDOMAIN命令
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l60609
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QrySDomainPara, Test_At_QrySDomainPara_001)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    AT_CLIENT_CTX_STRU                 *pstClientCtx;
    char                                acExpectedResult[] = "^SDOMAIN:0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_SDOMAIN,
                                                        At_SetSDomainPara,   AT_NOT_SET_TIME,    At_QrySDomainPara,     AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^SDOMAIN",  VOS_NULL_PTR};

    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);

    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    /* 命令参数 */
    stMsClass.ucMsClass = 0;
    stMsClass.ucReserved = 0;

    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq(enModemId), any(), outBoundP((void *)&stMsClass, sizeof(stMsClass)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRslt = At_QrySDomainPara(ucIndex);

    EXPECT_EQ(AT_OK, ulRslt);
    EXPECT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号     : Test_At_QrySDomainPara_002
测试用例标题     : MODEM 1 查询SDOMAIN命令
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l60609
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QrySDomainPara, Test_At_QrySDomainPara_002)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    AT_CLIENT_CTX_STRU                 *pstClientCtx;
    char                                acExpectedResult[] = "^SDOMAIN:1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_SDOMAIN,
                                                        At_SetSDomainPara,   AT_NOT_SET_TIME,    At_QrySDomainPara,     AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^SDOMAIN",  VOS_NULL_PTR};

    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_1;

    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);

    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    /* 命令参数 */
    /* 命令参数 */
    stMsClass.ucMsClass = 1;
    stMsClass.ucReserved = 0;
    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq(enModemId), any(), outBoundP((void *)&stMsClass), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRslt = At_QrySDomainPara(ucIndex);

    EXPECT_EQ(AT_OK, ulRslt);
    EXPECT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


/*****************************************************************************
类名    : Test_AT_QryRstriggerPara
功能描述: AT_QryRstriggerPara  UT工程类
修改历史    :
1.日  期 : 2013-03-18
  作  者 :   l60609
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_QryRstriggerPara: public ::testing::Test
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
测试用例编号     : Test_AT_QryRstriggerPara_001
测试用例标题     : MODEM 0 查询RSTRIGGER命令
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l60609
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRstriggerPara, Test_AT_QryRstriggerPara_001)
{
    VOS_UINT8                           aucActiveMessageInfo[MN_MSG_ACTIVE_MESSAGE_PARA_LEN];
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    AT_CLIENT_CTX_STRU                 *pstClientCtx;
    char                                acExpectedResult[] = "^RSTRIGGER: 0,\"\"";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_RSTRIGGER,
                                                        AT_SetRstriggerPara,    AT_NOT_SET_TIME,  AT_QryRstriggerPara,       AT_NOT_SET_TIME,    AT_TestRstriggerPara, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED,       CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"^RSTRIGGER",   (VOS_UINT8*)"(0,1,255),(URL)"};

    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);

    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    PS_MEM_SET(aucActiveMessageInfo, 0, MN_MSG_ACTIVE_MESSAGE_PARA_LEN);

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    /* 命令参数 */

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), outBoundP((void *)aucActiveMessageInfo, MN_MSG_ACTIVE_MESSAGE_PARA_LEN), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRslt = AT_QryRstriggerPara(ucIndex);

    EXPECT_EQ(AT_OK, ulRslt);
    EXPECT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号     : Test_AT_QryRstriggerPara_002
测试用例标题     : MODEM 1 查询SDOMAIN命令
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l60609
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRstriggerPara, Test_AT_QryRstriggerPara_002)
{
    VOS_UINT8                           aucActiveMessageInfo[MN_MSG_ACTIVE_MESSAGE_PARA_LEN];
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    AT_CLIENT_CTX_STRU                 *pstClientCtx;
    char                                acExpectedResult[] = "^RSTRIGGER: 0,\"\"";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_RSTRIGGER,
                                                        AT_SetRstriggerPara,    AT_NOT_SET_TIME,  AT_QryRstriggerPara,       AT_NOT_SET_TIME,    AT_TestRstriggerPara, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED,       CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"^RSTRIGGER",   (VOS_UINT8*)"(0,1,255),(URL)"};

    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);

    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    PS_MEM_SET(aucActiveMessageInfo, 0, MN_MSG_ACTIVE_MESSAGE_PARA_LEN);

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    /* 命令参数 */

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), outBoundP((void *)aucActiveMessageInfo, MN_MSG_ACTIVE_MESSAGE_PARA_LEN), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRslt = AT_QryRstriggerPara(ucIndex);

    EXPECT_EQ(AT_OK, ulRslt);
    EXPECT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
/*****************************************************************************
类名    : Test_At_QryCnmiPara
功能描述: At_QryCnmiPara  UT工程类
修改历史    :
1.日  期 : 2013-03-18
  作  者 :  z00220246
  修改内容: 新生成类
*****************************************************************************/
class Test_At_QryCnmiPara: public ::testing::Test
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
测试用例编号     : Test_At_QryCnmiPara_001
测试用例标题     : MODEM 0 查询CNMI命令
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : z00220246
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCnmiPara, Test_At_QryCnmiPara_001)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);
    pstSmsCtx->stCnmiType.CnmiModeType = 1;
    pstSmsCtx->stCnmiType.CnmiMtType = 1;
    pstSmsCtx->stCnmiType.CnmiBmType = 1;
    pstSmsCtx->stCnmiType.CnmiDsType = 1;
    pstSmsCtx->stCnmiType.CnmiBfrType = 1;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CNMI";

    ulRst = At_QryCnmiPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CNMI: 1,1,1,1,1";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
试用例编号     : Test_At_QryCnmiPara_002
测试用例标题     : MODEM 1 查询CNMI命令
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : z00220246
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryCnmiPara, Test_At_QryCnmiPara_002)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);
    pstSmsCtx->stCnmiType.CnmiModeType = 1;
    pstSmsCtx->stCnmiType.CnmiMtType = 0;
    pstSmsCtx->stCnmiType.CnmiBmType = 1;
    pstSmsCtx->stCnmiType.CnmiDsType = 1;
    pstSmsCtx->stCnmiType.CnmiBfrType = 1;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CNMI";

    ulRst = At_QryCnmiPara(ucIndex);

    /* 检查结果 */
    pcExpect = "+CNMI: 1,0,1,1,1";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名    : Test_At_QryBsn
功能描述: At_QryBsn  UT工程类
修改历史    :
1.日  期 : 2013-03-18
  作  者 :  z00220246
  修改内容: 新生成类
*****************************************************************************/
class Test_At_QryBsn: public ::testing::Test
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
测试用例编号     : Test_At_QryBsn_001
测试用例标题     : MODEM 0 查询BSN命令，获取ModemId失败
预期结果         : 查询失败
修改历史         :
1.日  期         : 2013-03-11
  作  者         : z00220246
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryBsn, Test_At_QryBsn_001)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRst = At_QryBsn(ucIndex);

    /* 检查结果 */
    EXPECT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号     : Test_At_QryBsn_002
测试用例标题     : MODEM 0 查询BSN命令，读取NV失败
预期结果         : 查询失败
修改历史         :
1.日  期         : 2013-03-11
  作  者         : z00220246
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryBsn, Test_At_QryBsn_002)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_1;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq(enModemId), eq((VOS_UINT16)en_NV_Item_ManufactureInfo), any(), any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    ulRst = At_QryBsn(ucIndex);

    /* 检查结果 */
    EXPECT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号     : Test_At_QryBsn_003
测试用例标题     : MODEM 0 查询BSN命令，读取NV成功
预期结果         : 查询成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : z00220246
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryBsn, Test_At_QryBsn_003)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucBsnSerialNum[17];
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+BSN";

    PS_MEM_SET(aucBsnSerialNum, 0x00, sizeof(aucBsnSerialNum));

    strcpy((char *)aucBsnSerialNum,"0203073425123468");

    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq(enModemId), eq((VOS_UINT16)en_NV_Item_ManufactureInfo), outBoundP((void *)aucBsnSerialNum, sizeof(aucBsnSerialNum)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRst = At_QryBsn(ucIndex);

    /* 检查结果 */
    pcExpect = "+BSN:0203073425123468";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRst);

    free(g_stParseContext[ucIndex].pstCmdElement );

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryMmPlmnInfoPara
功能描述 : At_QryMmPlmnInfoPara UT工程类
修改历史 :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryMmPlmnInfoPara: public ::testing::Test
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
测试用例编号      : Test_At_QryMmPlmnInfoPara_001
测试用例标题      : TAF参数查询成功
预期结果          : AT通道进入阻塞状态
修改历史          :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryMmPlmnInfoPara, Test_At_QryMmPlmnInfoPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = 0;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(Taf_ParaQuery)
        .expects(exactly(1))
        .with(eq((VOS_UINT16)ucIndex), any(), eq((TAF_PARA_TYPE)ID_TAF_MMA_MMPLMNINFO_QRY_REQ), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = At_QryMmPlmnInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_MMPLMNINFO_QRY);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryMmPlmnInfoPara_002
测试用例标题      : TAF参数查询失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryMmPlmnInfoPara, Test_At_QryMmPlmnInfoPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = 0;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(Taf_ParaQuery)
        .expects(exactly(1))
        .with(eq((VOS_UINT16)ucIndex), any(), eq((TAF_PARA_TYPE)ID_TAF_MMA_MMPLMNINFO_QRY_REQ), any())
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRet = At_QryMmPlmnInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryXlemaPara
功能描述 : At_QryXlemaPara UT工程类
修改历史 :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryXlemaPara: public ::testing::Test
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
测试用例编号      : Test_At_QryXlemaPara_001
测试用例标题      : 查询请求发送成功
预期结果          : AT通道进入阻塞状态
修改历史          :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryXlemaPara, Test_At_QryXlemaPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = 0;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(MN_CALL_SendAppRequest)
        .expects(exactly(1))
        .with(eq((MN_CALL_APP_REQ_ENUM_UINT32)MN_CALL_APP_XLEMA_REQ), eq((MN_CLIENT_ID_T)ucIndex), any(), any(), any())
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    ulRet = At_QryXlemaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_XLEMA_QRY);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryXlemaPara_002
测试用例标题      : 查询请求发送失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryXlemaPara, Test_At_QryXlemaPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = 0;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(MN_CALL_SendAppRequest)
        .expects(exactly(1))
        .with(eq((MN_CALL_APP_REQ_ENUM_UINT32)MN_CALL_APP_XLEMA_REQ), eq((MN_CLIENT_ID_T)ucIndex), any(), any(), any())
        .will(returnValue((VOS_UINT32)MN_ERR_UNSPECIFIED));

    // 调用被测函数
    ulRet = At_QryXlemaPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryIMEIVerifyPara
功能描述 : At_QryIMEIVerifyPara UT工程类
修改历史 :
1.日   期  : 2013-05-22
  作   者  : Y00213812
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryIMEIVerifyPara: public ::testing::Test
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
测试用例编号      : Test_At_QryIMEIVerifyPara_001
测试用例标题      : TAF参数查询成功
预期结果          : AT通道进入阻塞状态
修改历史          :
1.日   期  : 2013-05-22
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryIMEIVerifyPara, Test_At_QryIMEIVerifyPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = AT_CLIENT_ID_APP;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = At_QryIMEIVerifyPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_IMEI_VERIFY_READ);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryIMEIVerifyPara_002
测试用例标题      : TAF参数查询失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-05-22
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryIMEIVerifyPara, Test_At_QryIMEIVerifyPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = AT_CLIENT_ID_APP;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRet = At_QryIMEIVerifyPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryUserSrvStatePara
功能描述 : AT_QryUserSrvStatePara UT工程类
修改历史 :
1.日   期  : 2013-06-13
  作   者  : s00217060
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryUserSrvStatePara: public ::testing::Test
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
测试用例编号      : Test_AT_QryUserSrvStatePara_001
测试用例标题      : 查询请求发送成功
预期结果          : AT通道进入阻塞状态
修改历史          :
1.日   期  : 2013-06-13
  作   者  : s00217060
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryUserSrvStatePara, Test_AT_QryUserSrvStatePara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           ucOpId = 0;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(Taf_ParaQuery)
        .expects(exactly(1))
        .with(eq(gastAtClientTab[ucIndex].usClientId), eq(ucOpId), eq((TAF_PARA_TYPE)ID_TAF_MMA_USER_SRV_STATE_QRY_REQ), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryUserSrvStatePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_USER_SRV_STATE_READ);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryUserSrvStatePara_002
测试用例标题      : 查询请求发送失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-06-13
  作   者  : s00217060
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryUserSrvStatePara, Test_AT_QryUserSrvStatePara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           ucOpId = 0;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(Taf_ParaQuery)
        .expects(exactly(1))
        .with(eq(gastAtClientTab[ucIndex].usClientId), eq(ucOpId), eq((TAF_PARA_TYPE)ID_TAF_MMA_USER_SRV_STATE_QRY_REQ), any())
        .will(returnValue((VOS_UINT32)TAF_APS_FAIL));

    // 调用被测函数
    ulRet = AT_QryUserSrvStatePara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_AT_QryNCellMonitorPara
功能描述 : AT_QryNCellMonitorPara UT工程类
修改历史 :
1.日   期  : 2013-06-13
  作   者  : s00217060
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryNCellMonitorPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryNCellMonitorPara_001
测试用例标题      : 查询请求发送成功
预期结果          : AT通道进入阻塞状态
修改历史          :
1.日   期  : 2013-06-13
  作   者  : s00217060
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryNCellMonitorPara, Test_AT_QryNCellMonitorPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = 0;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(eq(gastAtClientTab[ucIndex].usClientId), eq((MN_OPERATION_ID_T)ucIndex), eq((VOS_UINT16)ID_AT_MTA_NCELL_MONITOR_QRY_REQ), any(), eq((VOS_UINT32)0), eq((VOS_UINT32)I0_UEPS_PID_MTA))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryNCellMonitorPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_NCELL_MONITOR_READ);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryNCellMonitorPara_002
测试用例标题      : 查询请求发送失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-06-13
  作   者  : s00217060
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryNCellMonitorPara, Test_AT_QryNCellMonitorPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex = 0;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId = ucIndex;

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(eq(gastAtClientTab[ucIndex].usClientId), eq((MN_OPERATION_ID_T)ucIndex), eq((VOS_UINT16)ID_AT_MTA_NCELL_MONITOR_QRY_REQ), any(), eq((VOS_UINT32)0), eq((VOS_UINT32)I0_UEPS_PID_MTA))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryNCellMonitorPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryRefclkfreqPara
功能描述 : AT_QryRefclkfreqPara UT工程类
修改历史 :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryRefclkfreqPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_ResetClientTab();
        g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryRefclkfreqPara_001
测试用例标题      : 命令从非AP对接通道下发
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRefclkfreqPara, Test_AT_QryRefclkfreqPara_001)
{

    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_QryRefclkfreqPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryRefclkfreqPara_002
测试用例标题      : 命令从AP对接通道下发
预期结果          : 返回AT_WAIT_ASYNC_RETURN, AT发送消息给MTA, AT等待异步返回
修改历史          :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRefclkfreqPara, Test_AT_QryRefclkfreqPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)ID_AT_MTA_REFCLKFREQ_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)I0_UEPS_PID_MTA))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryRefclkfreqPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN,  ulRet);
    EXPECT_EQ(AT_CMD_REFCLKFREQ_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryRefclkfreqPara_003
测试用例标题      : 命令从AP对接通道下发，消息发送失败
预期结果          : 返回AT_ERROR, 错误打印
修改历史          :
1.日   期  : 2013-07-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryRefclkfreqPara, Test_AT_QryRefclkfreqPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(gastAtClientTab[ucIndex].usClientId),
              eq(gastAtClientTab[ucIndex].opId),
              eq((VOS_UINT16)ID_AT_MTA_REFCLKFREQ_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)I0_UEPS_PID_MTA))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryRefclkfreqPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR,  ulRet);

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryHandleDect
功能描述 : Test_At_QryHandleDect UT工程类
修改历史 :
1.日   期  : 2013-08-08
  作   者  : m00217266
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryHandleDect: public ::testing::Test
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
测试用例编号      : Test_At_QryHandleDect_001
测试用例标题      : 系统平台为SYSTEM_APP_WEBUI
预期结果          : 直接返回AT_CMD_NOT_SUPPORT
修改历史          :
1.日   期  : 2013-08-08
  作   者  : m00217266
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_At_QryHandleDect, Test_At_QryHandleDect_001)
{
    VOS_UINT8                           ucIndex;

    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;
    ucIndex = 0;

    EXPECT_EQ(AT_CMD_NOT_SUPPORT, At_QryHandleDect(ucIndex));

    // 执行检查
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_At_QryHandleDect_002
测试用例标题      : 操作类型为AT_CMD_OPT_TEST_CMD
预期结果          : 直接返回AT_ERROR
修改历史          :
1.日   期  : 2013-08-08
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_At_QryHandleDect, Test_At_QryHandleDect_002)
{
    VOS_UINT8                           ucIndex;

    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;
    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;


    EXPECT_EQ(AT_ERROR, At_QryHandleDect(ucIndex));

    // 执行检查
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_At_QryHandleDect_003
测试用例标题      : 发送成功
预期结果          : 直接返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2013-08-08
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_At_QryHandleDect, Test_At_QryHandleDect_003)
{
    VOS_UINT8                           ucIndex;

    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;
    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;


    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, At_QryHandleDect(ucIndex));
    EXPECT_EQ(AT_CMD_HANDLEDECT_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    // 执行检查
    GlobalMockObject::verify();

}


/*****************************************************************************
类名     : Test_AT_QryUserCfgOPlmnPara
功能描述 : AT_QryUserCfgOPlmnPara UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : s00190137
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryUserCfgOPlmnPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryUserCfgOPlmnPara_001
测试用例标题      : 发送成功
预期结果          : 直接返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2013-10-15
  作   者  : s00190137
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryUserCfgOPlmnPara, Test_AT_QryUserCfgOPlmnPara_001)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, AT_QryUserCfgOPlmnPara(ucIndex));

    // 执行检查
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryUserCfgOPlmnPara_002
测试用例标题      : 发送失败
预期结果          : 直接返回AT_ERROR
修改历史          :
1.日   期  : 2013-10-15
  作   者  : s00190137
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_AT_QryUserCfgOPlmnPara, Test_AT_QryUserCfgOPlmnPara_002)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    EXPECT_EQ(AT_ERROR, AT_QryUserCfgOPlmnPara(ucIndex));

    // 执行检查
    GlobalMockObject::verify();

}

/*****************************************************************************
类名            : Test_AT_QryIprPara
功能描述        : AT_QryIprPara UT工程类
修改历史        :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*****************************************************************************/
class Test_AT_QryIprPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);

        ucIndex                     = 0;
        gstAtSendData.usBufLen      = 0;
        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

        stCmdInfo.ulCmdIndex        = AT_CMD_IPR;
        stCmdInfo.pfnSetProc        = AT_QryIprPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"+IPR";
        stCmdInfo.pszParam          = VOS_NULL_PTR;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }

};

/*******************************************************************
测试用例编号      : Test_AT_QryIprPara_001
测试用例标题      : 端口类型错误
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryIprPara, Test_AT_QryIprPara_001)
{
    // 变量声明
    VOS_UINT32  ulRet;

    // 参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;

    // MOCKER操作;


    // 调用被测函数
    ulRet = AT_QryIprPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_QryIprPara_002
测试用例标题      : 查询波特率成功
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryIprPara, Test_AT_QryIprPara_002)
{
    // 变量声明
    VOS_UINT32  ulRet;

    // 参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].UserType       = AT_HSUART_USER;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_QryIprPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();

}

/*****************************************************************************
类名            : Test_AT_QryIcfPara
功能描述        : AT_QryIcfPara UT工程类
修改历史        :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*****************************************************************************/
class Test_AT_QryIcfPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);

        ucIndex                     = 0;
        gstAtSendData.usBufLen      = 0;
        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

        stCmdInfo.ulCmdIndex        = AT_CMD_ICF;
        stCmdInfo.pfnSetProc        = AT_QryIcfPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"+ICF";
        stCmdInfo.pszParam          = VOS_NULL_PTR;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }

};

/*******************************************************************
测试用例编号      : Test_AT_QryIcfPara_001
测试用例标题      : 端口类型错误
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryIcfPara, Test_AT_QryIcfPara_001)
{
    // 变量声明
    VOS_UINT32  ulRet;

    // 参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;

    // MOCKER操作;


    // 调用被测函数
    ulRet = AT_QryIcfPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_QryIcfPara_002
测试用例标题      : 查询帧格式成功
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryIcfPara, Test_AT_QryIcfPara_002)
{
    // 变量声明
    VOS_UINT32  ulRet;

    // 参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].UserType       = AT_HSUART_USER;
    AT_SEND_DATA_BUFFER_STRU gstAtSendData  = {0};

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_QryIcfPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();

}

/*****************************************************************************
类名            : Test_AT_QryIfcPara
功能描述        : AT_QryIfcPara UT工程类
修改历史        :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*****************************************************************************/
class Test_AT_QryIfcPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);

        ucIndex                     = 0;
        gstAtSendData.usBufLen      = 0;
        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

        stCmdInfo.ulCmdIndex        = AT_CMD_IFC;
        stCmdInfo.pfnSetProc        = AT_QryIfcPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"+IFC";
        stCmdInfo.pszParam          = VOS_NULL_PTR;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }

};

/*******************************************************************
测试用例编号      : Test_AT_QryIfcPara_001
测试用例标题      : 端口类型错误
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryIfcPara, Test_AT_QryIfcPara_001)
{
    // 变量声明
    VOS_UINT32  ulRet;

    // 参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;

    // MOCKER操作;


    // 调用被测函数
    ulRet = AT_QryIfcPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_QryIfcPara_002
测试用例标题      : 查询流控方式成功
预期结果          : 返回AT_OK
修改历史          :
1.日    期   : 2013年10月14日
  作    者   : z00189113
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryIfcPara, Test_AT_QryIfcPara_002)
{
    // 变量声明
    VOS_UINT32  ulRet;

    // 参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].UserType       = AT_HSUART_USER;
    AT_SEND_DATA_BUFFER_STRU gstAtSendData  = {0};

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_QryIfcPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();

}



#if (FEATURE_ON == FEATURE_IMS)
/******************************************************************************
类名     : Test_AT_QryCiregPara
功能描述 : AT_QryCiregPara UT工程类
修改历史 :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_AT_QryCiregPara: public ::testing::Test
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
测试用例编号: Test_AT_QryCiregPara_001
测试用例标题: +CIREG发送消息失败
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_AT_QryCiregPara, Test_AT_QryCiregPara_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRslt = AT_QryCiregPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryCiregPara_002
测试用例标题: +CIREP发送消息成功
预期结果    : 返回AT_WAIT_ASYNC_RETURN
修改历史    :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_AT_QryCiregPara, Test_AT_QryCiregPara_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(),
              any(),
              eq((VOS_UINT16)ID_AT_IMSA_CIREG_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)PS_PID_IMSA))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRslt = AT_QryCiregPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_QryCirepPara
功能描述 : AT_QryCirepPara UT工程类
修改历史 :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_AT_QryCirepPara: public ::testing::Test
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
测试用例编号: Test_AT_QryCirepPara_001
测试用例标题: +CIREG发送消息失败
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_AT_QryCirepPara, Test_AT_QryCirepPara_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRslt = AT_QryCirepPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryCirepPara_002
测试用例标题: +CIREP发送消息成功
预期结果    : 返回AT_WAIT_ASYNC_RETURN
修改历史    :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_AT_QryCirepPara, Test_AT_QryCirepPara_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(),
              any(),
              eq((VOS_UINT16)ID_AT_IMSA_CIREP_QRY_REQ),
              any(),
              eq((VOS_UINT32)0),
              eq((VOS_UINT32)PS_PID_IMSA))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRslt = AT_QryCirepPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_QryClccPara
功能描述 : AT_QryClccPara UT工程类
修改历史 :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_AT_QryClccPara: public ::testing::Test
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
测试用例编号: Test_AT_QryClccPara_001
测试用例标题: ^CLCC发送消息失败
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_AT_QryClccPara, Test_AT_QryClccPara_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(MN_CALL_GetCallInfos)
        .expects(exactly(1))
        .will(returnValue(TAF_FAILURE));

    // 调用被测函数
    ulRslt = AT_QryClccPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryClccPara_002
测试用例标题: ^CLCC发送消息成功
预期结果    : 返回AT_WAIT_ASYNC_RETURN
修改历史    :
 1.日   期  : 2013-10-02
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_AT_QryClccPara, Test_AT_QryClccPara_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_QryClccPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRslt);
    EXPECT_EQ(AT_CMD_CLCC_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

#endif
/*****************************************************************************
类名     : Test_AT_QryAntSwitchPara
功能描述 : AT_QryAntSwitchPara UT工程类
修改历史 :
1.日    期   : 2014年1月2日
  作    者   : m00217266
  修改内容   : 新增测试用例
*****************************************************************************/
class Test_AT_QryAntSwitchPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryAntSwitchPara_001
测试用例标题      : 命令操作类型类型错误
预期结果          : 返回AT_ERROR
修改历史          :
1.日    期   : 2014年1月2日
  作    者   : m00217266
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryAntSwitchPara, Test_AT_QryAntSwitchPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_QryAntSwitchPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryAntSwitchPara_002
测试用例标题      : 消息发送失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日    期   : 2014年1月2日
  作    者   : m00217266
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryAntSwitchPara, Test_AT_QryAntSwitchPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = AT_QryAntSwitchPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryAntSwitchPara_003
测试用例标题      : 消息发送成功
预期结果          : 返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日    期   : 2014年1月2日
  作    者   : m00217266
  修改内容   : 新增测试用例
*******************************************************************/
TEST_F(Test_AT_QryAntSwitchPara, Test_AT_QryAntSwitchPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    // 调用被测函数
    ulRet = AT_QryAntSwitchPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);
    EXPECT_EQ(AT_CMD_ANTSWITCH_QRY,  gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryModemStatusPara
功能描述 : AT_QryModemStatusPara UT工程类
修改历史 :
1.日   期  : 2013-12-30
  作   者  : d00212987
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryModemStatusPara: public ::testing::Test
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
测试用例编号      : Test_AT_QryModemStatusPara_001
测试用例标题      : 查询命令返回成功
预期结果          : 返回OK
修改历史          :
1.日   期  : 2013-12-30
  作   者  : d00212987
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryModemStatusPara, Test_AT_QryModemStatusPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    // 初始化全局变量;

    // 调用被测函数
    ulRet = AT_QryModemStatusPara(0);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryRATCombinePara
功能描述 : AT_QryRATCombinePara UT工程类
修改历史 :
1.日   期  : 2014-01-23
作   者  : h59254
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryRATCombinePara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);

        ucIndex                     = 0;
        gstAtSendData.usBufLen      = 0;
        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

        stCmdInfo.ulCmdIndex        = AT_CMD_RATCOMBINEPRIO;
        stCmdInfo.pfnSetProc        = AT_QryRATCombinePara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^RATCOMBINEPRIO";
        stCmdInfo.pszParam          = VOS_NULL_PTR;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryRATCombinePara_001
测试用例标题      : NV项读取失败
预期结果          : 返回OK
修改历史          :
1.日   期  : 2014-01-23
作   者  : h59254
修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryRATCombinePara, Test_AT_QryRATCombinePara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_NV_LC_CTRL_PARA_STRU            stCtrlData;

    // 初始化全局变量;


    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulRet = AT_QryRATCombinePara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryRATCombinePara_002
测试用例标题      : NV项读取成功，但C+L未使能
预期结果          : 返回OK
修改历史          :
1.日   期  : 2014-01-23
作   者  : h59254
修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryRATCombinePara, Test_AT_QryRATCombinePara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_NV_LC_CTRL_PARA_STRU            stCtrlData;

    // 初始化全局变量;
    stCtrlData.ucLCEnableFlg = VOS_FALSE;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stCtrlData, sizeof(stCtrlData)), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryRATCombinePara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_OPERATION_NOT_ALLOWED, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryRATCombinePara_003
测试用例标题      : NV项读取成功，C+L使能，主控值错误
预期结果          : 返回OK
修改历史          :
1.日   期  : 2014-01-23
作   者  : h59254
修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryRATCombinePara, Test_AT_QryRATCombinePara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_NV_LC_CTRL_PARA_STRU            stCtrlData;

    // 初始化全局变量;
    stCtrlData.ucLCEnableFlg = VOS_TRUE;
    stCtrlData.enRatCombined    = TAF_NVIM_LC_RAT_COMBINED_BUTT;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stCtrlData, (VOS_UINT32)sizeof(stCtrlData)), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_QryRATCombinePara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryRATCombinePara_004
测试用例标题      : NV项读取成功，C+L使能，主控值CL
预期结果          : 返回OK
修改历史          :
1.日   期  : 2014-01-23
作   者  : h59254
修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryRATCombinePara, Test_AT_QryRATCombinePara_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_NV_LC_CTRL_PARA_STRU            stCtrlData;

    // 初始化全局变量;
    stCtrlData.ucLCEnableFlg = VOS_TRUE;
    stCtrlData.enRatCombined     = TAF_NVIM_LC_RAT_COMBINED_CL;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stCtrlData, (VOS_UINT32)sizeof(stCtrlData)), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*MOCKER(At_sprintf)
        .expects(exactly(1))
        .will(returnValue(100));*/

    // 调用被测函数
    ulRet = AT_QryRATCombinePara(0);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(0x12, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryRATCombinePara_005
测试用例标题      : NV项读取成功，C+L使能，主控值GUL
预期结果          : 返回OK
修改历史          :
1.日   期  : 2014-01-23
  作   者  : h59254
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryRATCombinePara, Test_AT_QryRATCombinePara_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_NV_LC_CTRL_PARA_STRU            stCtrlData;

    // 初始化全局变量;
    stCtrlData.ucLCEnableFlg = VOS_TRUE;
    stCtrlData.enRatCombined     = TAF_NVIM_LC_RAT_COMBINED_GUL;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stCtrlData, (VOS_UINT32)sizeof(stCtrlData)), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*MOCKER(At_sprintf)
        .expects(exactly(1))
        .will(returnValue(100));*/

    // 调用被测函数
    ulRet = AT_QryRATCombinePara(0);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(0x12, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryMipiClkValue
功能描述 : AT_QryMipiClkValue UT工程类
修改历史 :
1.日   期  : 2014-01-23
作   者  : h59254
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryMipiClkValue: public ::testing::Test
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
测试用例编号      : Test_AT_QryMipiClkValue_001
测试用例标题      : 填写消息结构失败
预期结果          : 消息没有发送
修改历史          :
1.日   期  : 2014-03-10
  作   者  : j00174725
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryMipiClkValue, Test_AT_QryMipiClkValue_001)
{
    // 变量声明

    // 初始化全局变量;


    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    // 调用被测函数
    EXPECT_EQ(AT_ERROR, AT_QryMipiClkValue(AT_CLIENT_ID_PCUI));

    // 执行检查

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryMipiClkValue_002
测试用例标题      : 消息发送成功
预期结果          : 消息发送成功
修改历史          :
1.日   期  : 2014-03-10
  作   者  : j00174725
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_QryMipiClkValue, Test_AT_QryMipiClkValue_002)
{
    // 变量声明

    // 初始化全局变量;


    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, AT_QryMipiClkValue(AT_CLIENT_ID_PCUI));
    EXPECT_EQ(AT_CMD_MIPI_CLK_QRY, gastAtClientTab[AT_CLIENT_ID_PCUI].CmdCurrentOpt);

    // 执行检查

    GlobalMockObject::verify();
}


