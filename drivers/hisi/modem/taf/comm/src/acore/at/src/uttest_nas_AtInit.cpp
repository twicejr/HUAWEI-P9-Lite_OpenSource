#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtInit.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define    THIS_FILE_ID        PS_FILE_ID_AT_INIT_C
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
类名     : Test_AT_ReadClientConfigNV
功能描述 : Test_AT_ReadClientConfigNV UT工程类
修改历史 :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadClientConfigNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        
        AT_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_ReadClientConfigNV_001
测试用例标题      : NV不存在
预期结果          : 返回
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadClientConfigNV, Test_AT_ReadClientConfigNV_001)
{
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue(VOS_ERR));

    AT_ReadClientConfigNV();

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadClientConfigNV_002
测试用例标题      : NV存在，所有通道都属于modem0，都允许广播
预期结果          : 返回
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadClientConfigNV, Test_AT_ReadClientConfigNV_002)
{
    VOS_UINT8                           aucAtClientConfig[AT_CLIENT_ID_BUTT];

    PS_MEM_SET(aucAtClientConfig, 0 ,sizeof(aucAtClientConfig));

    aucAtClientConfig[TAF_NV_CLIENT_CFG_PCUI] = 0x04;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_CTRL] = 0x04;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_APP1] = 0x04;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_AT_CLIENT_CONFIG), outBoundP((void *)aucAtClientConfig, AT_CLIENT_ID_BUTT), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadClientConfigNV();

    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.enModemId);

    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.ucReportFlg);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadClientConfigNV_003
测试用例标题      : NV存在，PCUI，CTRL，APP5-APP8都属于modem1，APP5-APP8不允许广播
预期结果          : 返回
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadClientConfigNV, Test_AT_ReadClientConfigNV_003)
{
    VOS_UINT8                           aucAtClientConfig[AT_CLIENT_ID_BUTT];

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    aucAtClientConfig[TAF_NV_CLIENT_CFG_PCUI] = 0x05;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_CTRL] = 0x05;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_APP5] = 0x01;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_APP1] = 0x04;
#endif

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_AT_CLIENT_CONFIG), outBoundP((void *)aucAtClientConfig, AT_CLIENT_ID_BUTT), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadClientConfigNV();

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    EXPECT_EQ(MODEM_ID_1, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_1, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_1, g_astAtClientCtx[AT_CLIENT_TAB_APP5_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(VOS_FALSE, g_astAtClientCtx[AT_CLIENT_TAB_APP5_INDEX].stClientConfiguration.ucReportFlg);

#endif
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.ucReportFlg);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ReadPlatformNV
功能描述 : AT_ReadPlatformNV UT工程类
修改历史     :
#  1.日    期: 2013年01月05日
#    作    者: z00220246
#    修改内容: 新建CASE
*****************************************************************************/
class Test_AT_ReadPlatformNV: public ::testing::Test
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

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_AT_ReadPlatformNV_001
测试用例标题      : 读取平台接入技术支持NV
预期结果          : 全局变量结果赋值
修改历史          :
#  1.日    期: 2013年01月05日
#    作    者: z00220246
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadPlatformNV, Test_AT_ReadPlatformNV_001)
{
    PLATAFORM_RAT_CAPABILITY_STRU       stPlatFormRat;
    AT_MODEM_SPT_RAT_STRU                 *pstAtSptRatList = VOS_NULL_PTR;

    stPlatFormRat.usRatNum = 4;
    stPlatFormRat.aenRatList[0] = PLATFORM_RAT_LTE;
    stPlatFormRat.aenRatList[1] = PLATFORM_RAT_WCDMA;
    stPlatFormRat.aenRatList[2] = PLATFORM_RAT_TDS;
    stPlatFormRat.aenRatList[3] = PLATFORM_RAT_GSM;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0), eq((VOS_UINT16)en_NV_Item_Platform_RAT_CAP), outBoundP((void *)&stPlatFormRat, (VOS_UINT32)sizeof(stPlatFormRat)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    AT_ReadPlatformNV();

    pstAtSptRatList = AT_GetSptRatFromModemId(MODEM_ID_0);

#if(FEATURE_ON == FEATURE_LTE)
    EXPECT_EQ(VOS_TRUE, pstAtSptRatList->ucPlatformSptLte);
#endif

    EXPECT_EQ(VOS_TRUE, pstAtSptRatList->ucPlatformSptWcdma);
    EXPECT_EQ(VOS_TRUE, pstAtSptRatList->ucPlatformSptGsm);

    GlobalMockObject::verify();
}
#endif




/*****************************************************************************
类名    : Test_AT_SendDomainNvimToProto
功能描述: AT_SendDomainNvimToProto  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_SendDomainNvimToProto: public ::testing::Test
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
测试用例编号     : Test_AT_SendDomainNvimToProto_001
测试用例标题     : NVIM发送域为AT_NV_SMS_DOMAIN_PS_PREFERRED
预期结果         : 转换为协议发送域MN_MSG_SEND_DOMAIN_PS_PREFERRED
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SendDomainNvimToProto, Test_AT_SendDomainNvimToProto_001)
{
    // 参数定义
    VOS_UINT32                          ulNvimSendDomain;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        ulRslt;

    // 参数初始化
    ulNvimSendDomain = AT_NV_SMS_DOMAIN_PS_PREFERRED;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SendDomainNvimToProto(ulNvimSendDomain);

    // 执行检查
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS_PREFERRED, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_SendDomainNvimToProto_002
测试用例标题     : NVIM发送域为AT_NV_SMS_DOMAIN_PS_ONLY
预期结果         : 转换为协议发送域MN_MSG_SEND_DOMAIN_PS
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SendDomainNvimToProto, Test_AT_SendDomainNvimToProto_002)
{
    // 参数定义
    VOS_UINT32                          ulNvimSendDomain;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        ulRslt;

    // 参数初始化
    ulNvimSendDomain = AT_NV_SMS_DOMAIN_PS_ONLY;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SendDomainNvimToProto(ulNvimSendDomain);

    // 执行检查
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_SendDomainNvimToProto_003
测试用例标题     : NVIM发送域为AT_NV_SMS_DOMAIN_CS_ONLY
预期结果         : 转换为协议发送域MN_MSG_SEND_DOMAIN_CS
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SendDomainNvimToProto, Test_AT_SendDomainNvimToProto_003)
{
    // 参数定义
    VOS_UINT32                          ulNvimSendDomain;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        ulRslt;

    // 参数初始化
    ulNvimSendDomain = AT_NV_SMS_DOMAIN_CS_ONLY;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SendDomainNvimToProto(ulNvimSendDomain);

    // 执行检查
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_SendDomainNvimToProto_004
测试用例标题     : NVIM发送域为AT_NV_SMS_DOMAIN_CS_PREFERRED
预期结果         : 转换为协议发送域MN_MSG_SEND_DOMAIN_CS_PREFERRED
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SendDomainNvimToProto, Test_AT_SendDomainNvimToProto_004)
{
    // 参数定义
    VOS_UINT32                          ulNvimSendDomain;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        ulRslt;

    // 参数初始化
    ulNvimSendDomain = AT_NV_SMS_DOMAIN_CS_PREFERRED;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SendDomainNvimToProto(ulNvimSendDomain);

    // 执行检查
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS_PREFERRED, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_ReadSmsSendDomainNV
功能描述: AT_ReadSmsSendDomainNV  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ReadSmsSendDomainNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号     : Test_AT_ReadSmsSendDomainNV_001
测试用例标题     : Modem0NVIM发送域为AT_NV_SMS_DOMAIN_PS_PREFERRED
预期结果         : 转换为协议发送域MN_MSG_SEND_DOMAIN_PS_PREFERRED
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadSmsSendDomainNV, Test_AT_ReadSmsSendDomainNV_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;

    // 参数初始化
    enModemId = MODEM_ID_0;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_CS_PREFERRED;

    // 相关全局变量初始化

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadSmsSendDomainNV();

    // 执行检查
    EXPECT_EQ(VOS_TRUE, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCgsmsSendDomain.ucActFlg);
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS_PREFERRED, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCgsmsSendDomain.enSendDomain);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号     : Test_AT_ReadSmsSendDomainNV_002
测试用例标题     : Modem1NVIM发送域为AT_NV_SMS_DOMAIN_PS_PREFERRED
预期结果         : 转换为协议发送域MN_MSG_SEND_DOMAIN_PS_PREFERRED
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadSmsSendDomainNV, Test_AT_ReadSmsSendDomainNV_002)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;

    // 参数初始化
    enModemId = MODEM_ID_1;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_PS_ONLY;

    // 相关全局变量初始化

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadSmsSendDomainNV();

    // 执行检查
    EXPECT_EQ(VOS_TRUE, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCgsmsSendDomain.ucActFlg);
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCgsmsSendDomain.enSendDomain);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_AT_ReadSmsNV
功能描述 : AT_ReadSmsNV UT工程类
修改历史     :
#  1.日    期: 2013年03月08日
#    作    者: l60609
#    修改内容: 新建CASE
*****************************************************************************/
class Test_AT_ReadSmsNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


/*******************************************************************
测试用例编号  : Test_AT_ReadSmsNV_001
测试用例标题  : 读短信发送域(CS)NV成功，读ME存储是否使能(使能)NV成功，读短信服务参数NV(SM存储使能)成功，读gclass0 NV成功
预期结果      : 短信发送域为CS，ME存储使能，短信和状态报告接收存储为NVIM，CLASS0类型为TIM
修改历史      :
1.日    期    : 2013年03月08日
  作    者    : l60609
  修改内容    : DSDA PHASE III
*******************************************************************/
TEST_F(Test_AT_ReadSmsNV, Test_AT_ReadSmsNV_001)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    VOS_UINT8                           aucSmsSrvParam[MN_MSG_SRV_PARAM_LEN];
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;
    MODEM_ID_ENUM_UINT16                enModemIdMoker;

    enModemIdMoker = MODEM_ID_0;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_CS_ONLY;

    MOCKER(AT_ReadSmsClosePathNV)
        .expects(exactly(1));

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMoker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));

    enModemIdMoker = MODEM_ID_1;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMoker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_ENABLE;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
   MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    aucSmsSrvParam[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET] = VOS_TRUE;
    aucSmsSrvParam[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = MN_MSG_MEM_STORE_NV;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_ACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_TIM;

    enModemIdMoker = MODEM_ID_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMoker), eq((VOS_UINT16)en_NV_Item_SMS_CLASS0_TAILOR), outBoundP((void *)&stClass0Tailor, (VOS_UINT32)sizeof(stClass0Tailor)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadSmsNV();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_TRUE, pstSmsCtx->stCgsmsSendDomain.ucActFlg);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS, pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(VOS_TRUE, pstSmsCtx->enMsgMeStorageStatus);
        EXPECT_EQ(MN_MSG_MEM_STORE_NV, pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore);
        EXPECT_EQ(MN_MSG_MEM_STORE_NV, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    }

    EXPECT_EQ(MN_MSG_CLASS0_TIM, g_enClass0Tailor);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadSmsNV_002
测试用例标题  : 读短信发送域(PS)NV成功，读ME存储是否使能(使能)NV成功，读短信服务参数NV(SM存储使能)失败，读gclass0 NV成功
预期结果      : 短信发送域为PS，ME存储使能，短信和状态报告接收存储为SIM，CLASS0类型为TIM
修改历史      :
1.日    期    : 2013年03月08日
  作    者    : l60609
  修改内容    : DSDA PHASE III
*******************************************************************/
TEST_F(Test_AT_ReadSmsNV, Test_AT_ReadSmsNV_002)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    VOS_UINT8                           aucSmsSrvParam[MN_MSG_SRV_PARAM_LEN];
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;
    MODEM_ID_ENUM_UINT16                enModemIdMocker;

    enModemIdMocker = MODEM_ID_0;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_PS_ONLY;

    MOCKER(AT_ReadSmsClosePathNV)
        .expects(exactly(1));

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));

    enModemIdMocker = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_ENABLE;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stMeStorageParm)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stMeStorageParm)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    aucSmsSrvParam[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET] = VOS_TRUE;
    aucSmsSrvParam[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = MN_MSG_MEM_STORE_NV;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_ACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_TIM;

    enModemIdMocker = MODEM_ID_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_CLASS0_TAILOR), outBoundP((void *)&stClass0Tailor, (VOS_UINT32)sizeof(stClass0Tailor)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadSmsNV();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_TRUE, pstSmsCtx->stCgsmsSendDomain.ucActFlg);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS, pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(VOS_TRUE, pstSmsCtx->enMsgMeStorageStatus);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM, pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    }

    EXPECT_EQ(MN_MSG_CLASS0_TIM, g_enClass0Tailor);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadSmsNV_003
测试用例标题  : 读短信发送域(PS PREFERRED)NV成功，读ME存储是否使能(使能)NV成功，读短信服务参数NV(SM存储使能)成功，读gclass0 NV失败
预期结果      : 短信发送域为PS PREFERRED，ME存储使能，短信和状态报告接收存储为NVIM，CLASS0类型为DEF
修改历史      :
1.日    期    : 2013年03月08日
  作    者    : l60609
  修改内容    : DSDA PHASE III
*******************************************************************/
TEST_F(Test_AT_ReadSmsNV, Test_AT_ReadSmsNV_003)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    VOS_UINT8                           aucSmsSrvParam[MN_MSG_SRV_PARAM_LEN];
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;
    MODEM_ID_ENUM_UINT16                enModemIdMocker;

    enModemIdMocker = MODEM_ID_0;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_PS_PREFERRED;

    MOCKER(AT_ReadSmsClosePathNV)
        .expects(exactly(1));

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));

    enModemIdMocker = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_ENABLE;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stMeStorageParm)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stMeStorageParm)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    aucSmsSrvParam[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET] = VOS_TRUE;
    aucSmsSrvParam[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = MN_MSG_MEM_STORE_NV;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_ACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_DEF;

    enModemIdMocker = MODEM_ID_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_CLASS0_TAILOR), outBoundP((void *)&stClass0Tailor, (VOS_UINT32)sizeof(stClass0Tailor)))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    AT_ReadSmsNV();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_TRUE, pstSmsCtx->stCgsmsSendDomain.ucActFlg);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS_PREFERRED, pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(VOS_TRUE, pstSmsCtx->enMsgMeStorageStatus);
        EXPECT_EQ(MN_MSG_MEM_STORE_NV, pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore);
        EXPECT_EQ(MN_MSG_MEM_STORE_NV, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    }

    EXPECT_EQ(MN_MSG_CLASS0_DEF, g_enClass0Tailor);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadSmsNV_004
测试用例标题  : 读短信发送域(CS PREFERRED)NV成功，读ME存储是否使能(使能)NV成功，读短信服务参数NV(SM存储使能)成功，读gclass0 NV成功但未使能
预期结果      : 短信发送域为CS PREFERRED，ME存储使能，短信和状态报告接收存储为NVIM，CLASS0类型为DEF
修改历史      :
1.日    期    : 2013年03月08日
  作    者    : l60609
  修改内容    : DSDA PHASE III
*******************************************************************/
TEST_F(Test_AT_ReadSmsNV, Test_AT_ReadSmsNV_004)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    VOS_UINT8                           aucSmsSrvParam[MN_MSG_SRV_PARAM_LEN];
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;

    MODEM_ID_ENUM_UINT16                enModemIdMocker;

    enModemIdMocker = MODEM_ID_0;

    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_CS_PREFERRED;
    MOCKER(AT_ReadSmsClosePathNV)
        .expects(exactly(1));

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain))
        .will(returnValue((VOS_UINT32)NV_OK));

    enModemIdMocker = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_ENABLE;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    aucSmsSrvParam[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET] = VOS_TRUE;
    aucSmsSrvParam[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = MN_MSG_MEM_STORE_NV;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_INACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_DEF;
    enModemIdMocker = MODEM_ID_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_CLASS0_TAILOR), outBoundP((void *)&stClass0Tailor))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadSmsNV();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_TRUE, pstSmsCtx->stCgsmsSendDomain.ucActFlg);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS_PREFERRED, pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(VOS_TRUE, pstSmsCtx->enMsgMeStorageStatus);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM, pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    }

    EXPECT_EQ(MN_MSG_CLASS0_DEF, g_enClass0Tailor);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_ReadRptNV
功能描述 : AT_ReadRptNV UT工程类
修改历史 :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadRptNV: public ::testing::Test
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

#if 0
/*****************************************************************************
类名    : Test_AT_ReadPrivateCmdStatusRptNV
功能描述: AT_ReadPrivateCmdStatusRptNV  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ReadPrivateCmdStatusRptNV: public ::testing::Test
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
测试用例编号     : Test_AT_ReadPrivateCmdStatusRptNV_001
测试用例标题     : 从NV中读取CREG/CGREG的CI参数
预期结果         : 读取成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadPrivateCmdStatusRptNV, Test_AT_ReadPrivateCmdStatusRptNV_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl;

    // 参数初始化
    enModemId                                     = MODEM_ID_0;
    stAtCmdRptCtrl.ucStatus                       = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl = 1;

    // 相关全局变量初始化

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .with(any(), any(), outBoundP((void *)&stAtCmdRptCtrl), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadPrivateCmdStatusRptNV();

    // 执行检查
    EXPECT_EQ(AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT, g_astAtModemCtx[MODEM_ID_0].stCtrlCtx.ucStatusReportGeneralControl);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadRptNV_001
测试用例标题      : NV项读取失败
预期结果          : 全局变量被赋予默认值
修改历史          :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadRptNV, Test_AT_ReadRptNV_001)
{
    // 变量声明
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CONTROL_CTX_STRU          *pstCtrlCtx = VOS_NULL_PTR;

    //参数初始化

    // 初始化全局变量
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);
        pstCtrlCtx->ucStatusReportGeneralControl     = AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT;
    }
    g_enAtCCallStateRptStatus           = AT_CMD_RPT_STATUS_DISABLE;

    // MOCKER操作;
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(3))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif
    // 调用被测函数
    AT_ReadRptNV();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);
        EXPECT_EQ(AT_STATUS_REPORT_GENERAL_CONTROL_REPORT, pstCtrlCtx->ucStatusReportGeneralControl);
    }
    EXPECT_EQ(AT_CMD_RPT_STATUS_ENABLE, g_enAtCCallStateRptStatus);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadRptNV_002
测试用例标题      : NV项读取成功, 私有命令及^CCALLSTATE命令均主动上报
预期结果          : 全局变量被赋予对应值
修改历史          :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadRptNV, Test_AT_ReadRptNV_002)
{
    // 变量声明
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl  = {0};
    AT_NV_CCALLSTATE_RPT_STATUS_STRU    stStatus        = {0};
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CONTROL_CTX_STRU          *pstCtrlCtx = VOS_NULL_PTR;

    //参数初始化
    stAtCmdRptCtrl.ucStatus                         = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl   = 0;
    PS_MEM_SET(&stStatus, 0, sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU));
    stStatus.enStatus                               = AT_CMD_RPT_STATUS_ENABLE;

    // 初始化全局变量
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);
        pstCtrlCtx->ucStatusReportGeneralControl     = AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT;
    }
    g_enAtCCallStateRptStatus           = AT_CMD_RPT_STATUS_DISABLE;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(MODEM_ID_0), eq(en_NV_Item_PRIVATE_CMD_STATUS_RPT),
              outBoundP((void *)&stAtCmdRptCtrl, sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)),
              eq(sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(MODEM_ID_1), eq(en_NV_Item_PRIVATE_CMD_STATUS_RPT),
        outBoundP((void *)&stAtCmdRptCtrl, sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)),
        eq(sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_CCallState_Rpt_Status),
              outBoundP((void *)&stStatus, sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU)),
              eq(sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadRptNV();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_STATUS_REPORT_GENERAL_CONTROL_REPORT, pstCtrlCtx->ucStatusReportGeneralControl);
    }
    EXPECT_EQ(AT_CMD_RPT_STATUS_ENABLE, g_enAtCCallStateRptStatus);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadRptNV_003
测试用例标题      : NV项读取成功, 私有命令及^CCALLSTATE命令均禁止主动上报
预期结果          : 全局变量被赋予对应值
修改历史          :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadRptNV, Test_AT_ReadRptNV_003)
{
    // 变量声明
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl  = {0};
    AT_NV_CCALLSTATE_RPT_STATUS_STRU    stStatus        = {0};
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CONTROL_CTX_STRU          *pstCtrlCtx = VOS_NULL_PTR;

     //参数初始化
    stAtCmdRptCtrl.ucStatus                         = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl   = 1;
    PS_MEM_SET(&stStatus, 0, sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU));
    stStatus.enStatus                               = AT_CMD_RPT_STATUS_DISABLE;

    // 初始化全局变量
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);

        pstCtrlCtx->ucStatusReportGeneralControl     = AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT;
    }
    g_enAtCCallStateRptStatus           = AT_CMD_RPT_STATUS_DISABLE;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(MODEM_ID_0), eq(en_NV_Item_PRIVATE_CMD_STATUS_RPT),
              outBoundP((void *)&stAtCmdRptCtrl, sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)),
              eq(sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(MODEM_ID_1), eq(en_NV_Item_PRIVATE_CMD_STATUS_RPT),
        outBoundP((void *)&stAtCmdRptCtrl, sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)),
        eq(sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_CCallState_Rpt_Status),
              outBoundP((void *)&stStatus, sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU)),
              eq(sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadRptNV();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);
        EXPECT_EQ(AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT, pstCtrlCtx->ucStatusReportGeneralControl);
    }
    EXPECT_EQ(AT_CMD_RPT_STATUS_DISABLE, g_enAtCCallStateRptStatus);

    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_AT_ReadSystemAppConfigNV
功能描述 : AT_ReadSystemAppConfigNV UT工程类
修改历史 :
1.日   期  : 2013-03-16
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadSystemAppConfigNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_ReadSystemAppConfigNV_001
测试用例标题      : NV项读取失败
预期结果          : 默认值为MP
修改历史          :
1.日   期  : 2013-03-16
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadSystemAppConfigNV, Test_AT_ReadSystemAppConfigNV_001)
{
    // 变量声明
    VOS_UINT8                            ucSystemAppConfig;
    VOS_UINT8                           *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    //参数初始化

    // 初始化全局变量

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    AT_ReadSystemAppConfigNV();

    // 执行检查
    EXPECT_EQ(SYSTEM_APP_MP, *pucSystemAppConfig);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadSystemAppConfigNV_002
测试用例标题      : NV项读取成功，ANDROID
预期结果          : ANDROID
修改历史          :
1.日   期  : 2013-03-16
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadSystemAppConfigNV, Test_AT_ReadSystemAppConfigNV_002)
{
    // 变量声明
    VOS_UINT8                            ucSystemAppConfig;
    VOS_UINT8                           *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    ucSystemAppConfig = SYSTEM_APP_ANDROID;
    //参数初始化

    // 初始化全局变量

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_System_APP_Config), outBoundP((void *)&ucSystemAppConfig))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadSystemAppConfigNV();

    // 执行检查
    EXPECT_EQ(SYSTEM_APP_ANDROID, *pucSystemAppConfig);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadSystemAppConfigNV_003
测试用例标题      : NV项读取成功，无效值
预期结果          : MP
修改历史          :
1.日   期  : 2013-03-16
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadSystemAppConfigNV, Test_AT_ReadSystemAppConfigNV_003)
{
    // 变量声明
    VOS_UINT8                            ucSystemAppConfig;
    VOS_UINT8                           *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    ucSystemAppConfig = SYSTEM_APP_BUTT;
    //参数初始化

    // 初始化全局变量

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_System_APP_Config), outBoundP((void *)&ucSystemAppConfig))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadSystemAppConfigNV();

    // 执行检查
    EXPECT_EQ(SYSTEM_APP_MP, *pucSystemAppConfig);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ReadRoamCapaNV
功能描述 : AT_ReadRoamCapaNV UT工程类
修改历史 :
1.日   期  : 2013-03-16
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadRoamCapaNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_ReadRoamCapaNV_001
测试用例标题      : NV项读取失败
预期结果          : 漫游特性未使能
修改历史          :
1.日   期  : 2013-03-16
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadRoamCapaNV, Test_AT_ReadRoamCapaNV_001)
{
    // 变量声明
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    //参数初始化

    // 初始化全局变量

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    // 调用被测函数
    AT_ReadRoamCapaNV();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_ROAM_FEATURE_OFF, pstNetCtx->ucRoamFeature);
    }

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadRoamCapaNV_002
测试用例标题      : NV项读取成功，漫游特性打开
预期结果          : 漫游特性打开
修改历史          :
1.日   期  : 2013-03-16
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadRoamCapaNV, Test_AT_ReadRoamCapaNV_002)
{
    // 变量声明
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucTmp[2];

    //参数初始化
    aucTmp[0] = AT_ROAM_FEATURE_ON;
    // 初始化全局变量

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Roam_Capa), outBoundP((void *)aucTmp))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Roam_Capa), outBoundP((void *)aucTmp))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    // 调用被测函数
    AT_ReadRoamCapaNV();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_ROAM_FEATURE_ON, pstNetCtx->ucRoamFeature);
    }

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadRoamCapaNV_003
测试用例标题      : NV项读取成功，无效值
预期结果          : 漫游特性未使能
修改历史          :
1.日   期  : 2013-03-16
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadRoamCapaNV, Test_AT_ReadRoamCapaNV_003)
{
    // 变量声明
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucTmp[2];

    //参数初始化
    aucTmp[0] = 2;
    // 初始化全局变量

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Roam_Capa), outBoundP((void *)aucTmp))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Roam_Capa), outBoundP((void *)aucTmp))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    // 调用被测函数
    AT_ReadRoamCapaNV();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_ROAM_FEATURE_OFF, pstNetCtx->ucRoamFeature);
    }

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_AT_ReadAbortCmdParaNV
功能描述 : Test_AT_ReadAbortCmdParaNV UT工程类
修改历史     :
1.日   期  : 2012-09-25
  作   者  : l00171473
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadAbortCmdParaNV: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_ABORT_CMD_PARA_STRU             *pstCmdPara;

        pstCmdPara = AT_GetAbortCmdPara();

        PS_MEM_SET(pstCmdPara->aucAbortAtCmdStr, 0x00, sizeof(pstCmdPara->aucAbortAtCmdStr));
        PS_MEM_SET(pstCmdPara->aucAbortAtRspStr, 0x00, sizeof(pstCmdPara->aucAbortAtRspStr));
    }

    void TearDown()
    {
        AT_ABORT_CMD_PARA_STRU             *pstCmdPara;

        pstCmdPara = AT_GetAbortCmdPara();

        PS_MEM_SET(pstCmdPara->aucAbortAtCmdStr, 0x00, sizeof(pstCmdPara->aucAbortAtCmdStr));
        PS_MEM_SET(pstCmdPara->aucAbortAtRspStr, 0x00, sizeof(pstCmdPara->aucAbortAtRspStr));
    }
};

/*******************************************************************
测试用例编号  : Test_AT_ReadAbortCmdParaNV_001
测试用例标题  : 读取NV成功, NV中ABORT数据无效
预期结果      : 全局变量中ABORT数据有效标志为FALSE
修改历史      :
1.日    期    : 2012年09月25日
  作    者    : L00171473
  修改内容    : 新增 for V7R1C50_At_Abort
*******************************************************************/
TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_001)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_FALSE;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_FALSE, pstCmdPara->ucAbortEnableFlg);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadAbortCmdParaNV_002
测试用例标题  : 读取NV失败
预期结果      : 打断命令的全局变量设为默认值
修改历史      :
1.日    期    : 2012年09月25日
  作    者    : L00171473
  修改内容    : 新增 for V7R1C50_At_Abort
*******************************************************************/
TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_002)
{
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT";
    VOS_UINT8                           aucDfltAbortRsp[] = "OK";

    pstCmdPara = AT_GetAbortCmdPara();

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadAbortCmdParaNV_003
测试用例标题  : 读取NV成功, 命令名中有无效字符
预期结果      : 打断命令的全局变量设为默认值
修改历史      :
1.日    期    : 2012年09月25日
  作    者    : L00171473
  修改内容    : 新增 for V7R1C50_At_Abort
*******************************************************************/
TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_003)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT";
    VOS_UINT8                           aucDfltAbortRsp[] = "OK";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    stTmpNvAbortCmdPara.aucAbortAtCmdStr[0] = 'a';
    stTmpNvAbortCmdPara.aucAbortAtCmdStr[1] = '\n';

    stTmpNvAbortCmdPara.aucAbortAtRspStr[0] = 'O';
    stTmpNvAbortCmdPara.aucAbortAtRspStr[1] = 'K';
    stTmpNvAbortCmdPara.aucAbortAtRspStr[2] = '\n';

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadAbortCmdParaNV_004
测试用例标题  : 读取NV成功, 打断命令的返回结果中有无效字符
预期结果      : 打断命令的全局变量设为默认值
修改历史      :
1.日    期    : 2012年09月25日
  作    者    : L00171473
  修改内容    : 新增 for V7R1C50_At_Abort
*******************************************************************/
TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_004)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT";
    VOS_UINT8                           aucDfltAbortRsp[] = "OK";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    stTmpNvAbortCmdPara.aucAbortAtCmdStr[0] = 'A';
    stTmpNvAbortCmdPara.aucAbortAtCmdStr[1] = 'T';
    stTmpNvAbortCmdPara.aucAbortAtCmdStr[2] = '\n';

    stTmpNvAbortCmdPara.aucAbortAtRspStr[0] = 'B';
    stTmpNvAbortCmdPara.aucAbortAtRspStr[1] = '\n';

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);

    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号  : Test_AT_ReadAbortCmdParaNV_005
测试用例标题  : 读取NV成功, 命令字符无无效字符
预期结果      : 打断命令的全局变量为NV中设置值
修改历史      :
1.日    期    : 2012年09月25日
  作    者    : L00171473
  修改内容    : 新增 for V7R1C50_At_Abort
*******************************************************************/
TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_005)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT^BREAK";
    VOS_UINT8                           aucDfltAbortRsp[] = "ABORT";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtCmdStr,
                (VOS_CHAR *)aucDfltAbortCmd,
                AT_MAX_ABORT_CMD_STR_LEN);

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtRspStr,
                (VOS_CHAR *)aucDfltAbortRsp,
                AT_MAX_ABORT_RSP_STR_LEN);

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadAbortCmdParaNV_006
测试用例标题  : 读取NV成功, 命令字符为ANY1
预期结果      : 非任意字符打断
修改历史      :
1.日    期    : 2013年10月31日
  作    者    : w00242748
  修改内容    : 新增
*******************************************************************/
TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_006)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "ANY1";
    VOS_UINT8                           aucDfltAbortRsp[] = "ABORT";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtCmdStr,
                (VOS_CHAR *)aucDfltAbortCmd,
                AT_MAX_ABORT_CMD_STR_LEN);

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtRspStr,
                (VOS_CHAR *)aucDfltAbortRsp,
                AT_MAX_ABORT_RSP_STR_LEN);

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);
    EXPECT_EQ(VOS_FALSE, pstCmdPara->ucAnyAbortFlg);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadAbortCmdParaNV_007
测试用例标题  : 读取NV成功, 命令字符为ABC
预期结果      : 非任意字符打断
修改历史      :
1.日    期    : 2013年10月31日
  作    者    : w00242748
  修改内容    : 新增
*******************************************************************/
TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_007)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "ABC";
    VOS_UINT8                           aucDfltAbortRsp[] = "ABORT";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtCmdStr,
                (VOS_CHAR *)aucDfltAbortCmd,
                AT_MAX_ABORT_CMD_STR_LEN);

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtRspStr,
                (VOS_CHAR *)aucDfltAbortRsp,
                AT_MAX_ABORT_RSP_STR_LEN);

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);
    EXPECT_EQ(VOS_FALSE, pstCmdPara->ucAnyAbortFlg);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_ReadAbortCmdParaNV_008
测试用例标题  : 读取NV成功, 命令字符为ANY
预期结果      : 非任意字符打断
修改历史      :
1.日    期    : 2013年10月31日
  作    者    : w00242748
  修改内容    : 新增
*******************************************************************/
TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_008)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "ANY";
    VOS_UINT8                           aucDfltAbortRsp[] = "ABORT";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtCmdStr,
                (VOS_CHAR *)aucDfltAbortCmd,
                AT_MAX_ABORT_CMD_STR_LEN);

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtRspStr,
                (VOS_CHAR *)aucDfltAbortRsp,
                AT_MAX_ABORT_RSP_STR_LEN);

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);
    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAnyAbortFlg);

    GlobalMockObject::verify();
}




/*****************************************************************************
类名     : Test_AT_IsAbortCmdCharValid
功能描述 : Test_AT_IsAbortCmdCharValid UT工程类
修改历史     :
1.日   期  : 2012-09-25
  作   者  : l00171473
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_IsAbortCmdCharValid: public ::testing::Test
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
测试用例编号  : Test_AT_IsAbortCmdCharValid_001
测试用例标题  : 判断打断命令中的字符是否有效, 输入为空指针
预期结果      : 返回FALSE
修改历史      :
1.日    期    : 2012年09月25日
  作    者    : L00171473
  修改内容    : 新增 for V7R1C50_At_Abort
*******************************************************************/
TEST_F(Test_AT_IsAbortCmdCharValid, Test_AT_IsAbortCmdCharValid_001)
{
    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdCharValid(VOS_NULL_PTR, 0));

    GlobalMockObject::verify();
}



/*******************************************************************
测试用例编号  : Test_AT_IsAbortCmdCharValid_002
测试用例标题  : 打断命令中的字符长度为0
预期结果      : 返回FALSE
修改历史      :
1.日    期    : 2013年03月20日
  作    者    : l00227485
  修改内容    : 新建CASE
*******************************************************************/
TEST_F(Test_AT_IsAbortCmdCharValid, Test_AT_IsAbortCmdCharValid_002)
{
    VOS_UINT8                          *pucAbortCmdChar;
    VOS_UINT32                          ulLen;

    pucAbortCmdChar = (VOS_UINT8 *)malloc(sizeof(VOS_UINT8));
    ulLen           = 0;

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdCharValid(pucAbortCmdChar, ulLen));

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ReadSysNV
功能描述 : AT_ReadSysNV UT工程类
修改历史 :
1.日   期  : 2013-03-8
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadSysNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_ReadSysNV_001
测试用例标题      : 读取域NV成功, 漫游NV成功,漫游NV项有效
预期结果          : VOS_VOID
修改历史          :
1.日   期  : 2013-03-21
  作   者  : f00179208
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_ReadSysNV,Test_AT_ReadSysNV_001)
{
    VOS_UINT8                           aucTmp[2];
    VOS_UINT16                          usNVId;
    VOS_UINT16                          usModem0;
    VOS_UINT16                          usModem1;

    aucTmp[0] = 1;
    usNVId = en_NV_Item_Roam_Capa;
    usModem0 = MODEM_ID_0;
    usModem1 = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(usModem0), eq(usNVId), outBoundP((void *)aucTmp,sizeof(aucTmp)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(usModem1), eq(usNVId), outBoundP((void *)aucTmp, sizeof(aucTmp)), any())
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    MOCKER(AT_ReadSystemAppConfigNV)
        .expects(exactly(1));

    MOCKER(AT_ReadE5NV)
        .expects(exactly(1));


    MOCKER(AT_ReadAbortCmdParaNV)
        .expects(exactly(1));

    AT_ReadSysNV();

    EXPECT_EQ(aucTmp[0], AT_GetModemNetCtxAddrFromClientId(0)->ucRoamFeature);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadSysNV_002
测试用例标题      : 读取域NV失败, 漫游NV失败
预期结果          : VOS_VOID
修改历史          :
1.日   期  : 2013-03-21
  作   者  : f00179208
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_ReadSysNV,Test_AT_ReadSysNV_002)
{

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    MOCKER(AT_ReadSystemAppConfigNV)
        .expects(exactly(1));

    MOCKER(AT_ReadE5NV)
        .expects(exactly(1));


    MOCKER(AT_ReadAbortCmdParaNV)
        .expects(exactly(1));

    AT_ReadSysNV();

    EXPECT_EQ(AT_GetModemNetCtxAddrFromClientId(0)->ucRoamFeature, AT_ROAM_FEATURE_OFF);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadSysNV_003
测试用例标题      : 读取域NV成功, 漫游NV成功,但漫游NV项无效
预期结果          : VOS_VOID
修改历史          :
1.日   期  : 2013-03-21
  作   者  : f00179208
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_ReadSysNV,Test_AT_ReadSysNV_003)
{
    VOS_UINT8                           aucTmp[2];
    VOS_UINT16                          usNVId;
    VOS_UINT16                          usModem0;
    VOS_UINT16                          usModem1;

    aucTmp[0]   = 5;
    usNVId      = en_NV_Item_Roam_Capa;
    usModem0    = MODEM_ID_0;
    usModem1    = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(usModem0), eq(usNVId), outBoundP((void *)aucTmp, sizeof(aucTmp)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(usModem1), eq(usNVId), outBoundP((void *)aucTmp, sizeof(aucTmp)), any())
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    MOCKER(AT_ReadSystemAppConfigNV)
        .expects(exactly(1));

    MOCKER(AT_ReadE5NV)
        .expects(exactly(1));


    MOCKER(AT_ReadAbortCmdParaNV)
        .expects(exactly(1));

    AT_ReadSysNV();

    EXPECT_EQ(AT_ROAM_FEATURE_OFF, AT_GetModemNetCtxAddrFromClientId(0)->ucRoamFeature);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ReadCellSignReportCfgNV
功能描述 : AT_ReadCellSignReportCfgNV UT工程类
修改历史 :
1.日   期  : 2012-11-28
  作   者  : z00161729
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadCellSignReportCfgNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_ReadCellSignReportCfgNV_001
测试用例标题      : 读nv失败
预期结果          :
修改历史          :
1.日   期  : 2012-11-28
  作   者  : z00161729
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_ReadCellSignReportCfgNV, Test_AT_ReadCellSignReportCfgNV_001)
{
    // 变量声明

    // 参数初始化

    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        pstNetCtx->ucCerssiReportType = AT_CERSSI_REPORT_TYPE_NOT_REPORT;

    }

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    AT_ReadCellSignReportCfgNV();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_CERSSI_REPORT_TYPE_NOT_REPORT, pstNetCtx->ucCerssiReportType);
    }

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadCellSignReportCfgNV_002
测试用例标题      : 读成功，信号质量门限为6
预期结果          :
修改历史          :
1.日   期  : 2012-11-28
  作   者  : z00161729
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_ReadCellSignReportCfgNV, Test_AT_ReadCellSignReportCfgNV_002)
{
    // 变量声明
    NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU  stCellSignReportCfg;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    // 参数初始化
    stCellSignReportCfg.enSignThreshold = AT_CERSSI_REPORT_TYPE_BUTT;


    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_CELL_SIGN_REPORT_CFG), outBoundP((void *)&stCellSignReportCfg), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadCellSignReportCfgNV();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_CERSSI_REPORT_TYPE_NOT_REPORT, pstNetCtx->ucCerssiReportType);
    }

    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_AT_ReadCsNV
功能描述   : AT_ReadCsNV UT工程类
修改历史   :
1.日   期  : 2013-03-08
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadCsNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {
    }
protected:

};

/*******************************************************************
测试用例编号  : Test_AT_ReadCsNV_001
测试用例标题  : 读自动应答NV成功，自动应答时间为5s，读USSD透传模式NV成功
预期结果      : 自动应答时间为5s，USSD透传模式
修改历史      :
1.日    期    : 2013年03月08日
  作    者    : l60609
  修改内容    : DSDA PHASE III
*******************************************************************/
TEST_F(Test_AT_ReadCsNV, Test_AT_ReadCsNV_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_USSD_NVIM_TRANS_MODE_STRU       stUssdTranMode;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;

    // 参数初始化
    enModemId                       = MODEM_ID_0;
    stTimeInfo.ucS0TimerLen         = 5;
    stUssdTranMode.ucStatus         = 1;
    stUssdTranMode.ucUssdTransMode  = 1;

    // 相关全局变量初始化

    // MOCKER操作
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0), eq((VOS_UINT16)en_NV_Item_CCA_TelePara), outBoundP((void *)&stTimeInfo, (VOS_UINT32)sizeof(stTimeInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_1), eq((VOS_UINT16)en_NV_Item_CCA_TelePara), outBoundP((void *)&stTimeInfo, (VOS_UINT32)sizeof(stTimeInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0), eq((VOS_UINT16)en_NV_Item_CUST_USSD_MODE), outBoundP((void *)&stUssdTranMode, (VOS_UINT32)sizeof(stUssdTranMode)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SS_CUSTOMIZE_PARA), any(), any())
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stTimeInfo, (VOS_UINT32)sizeof(stTimeInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stUssdTranMode, (VOS_UINT32)sizeof(stUssdTranMode)), any())
        .will(returnValue((VOS_UINT32)NV_OK));
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), any(), any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    // 调用被测函数
    AT_ReadCsNV();

    // 执行检查
    EXPECT_EQ(5, g_astAtModemCtx[MODEM_ID_0].stCcCtx.stS0TimeInfo.ucS0TimerLen);
    EXPECT_EQ(1, g_astAtModemCtx[MODEM_ID_0].stSsCtx.usUssdTransMode);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_ValidateWasCategory
功能描述: AT_ValidateWasCategory  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ValidateWasCategory: public ::testing::Test
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
测试用例编号     : Test_AT_ValidateWasCategory_001
测试用例标题     : 支持HS-DSCH物理层的类型标志为0
预期结果         : 返回VOS_ERR
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ValidateWasCategory, Test_AT_ValidateWasCategory_001)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport      = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategory  = 0;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_ValidateWasCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_ValidateWasCategory_002
测试用例标题     : 支持HS-DSCH物理层的类型标志为2
预期结果         : 返回VOS_OK
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ValidateWasCategory, Test_AT_ValidateWasCategory_002)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport      = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategory  = 2;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_ValidateWasCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_ValidateWasCategoryExt
功能描述: AT_ValidateWasCategoryExt  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ValidateWasCategoryExt: public ::testing::Test
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
测试用例编号     : Test_AT_ValidateWasCategoryExt_001
测试用例标题     : ucHSDSCHPhyCategoryExt为10
预期结果         : 返回VOS_ERR
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ValidateWasCategoryExt, Test_AT_ValidateWasCategoryExt_001)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt   = 10;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_ValidateWasCategoryExt(&stUeCapability);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_ValidateWasCategoryExt_002
测试用例标题     : ucHSDSCHPhyCategoryExt为15
预期结果         : 返回VOS_OK
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ValidateWasCategoryExt, Test_AT_ValidateWasCategoryExt_002)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt   = 15;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_ValidateWasCategoryExt(&stUeCapability);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_ValidateWasCategoryExt2
功能描述: AT_ValidateWasCategoryExt2  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ValidateWasCategoryExt2: public ::testing::Test
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
测试用例编号     : Test_AT_ValidateWasCategoryExt2_001
测试用例标题     : ucHSDSCHPhyCategoryExt2为20
预期结果         : 返回VOS_ERR
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ValidateWasCategoryExt2, Test_AT_ValidateWasCategoryExt2_001)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt2  = 20;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_ValidateWasCategoryExt2(&stUeCapability);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_ValidateWasCategoryExt2_002
测试用例标题     : ucHSDSCHPhyCategoryExt2为22
预期结果         : 返回VOS_OK
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ValidateWasCategoryExt2, Test_AT_ValidateWasCategoryExt2_002)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt2  = 22;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_ValidateWasCategoryExt2(&stUeCapability);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_ValidateWasCategoryExt3
功能描述: AT_ValidateWasCategoryExt3  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ValidateWasCategoryExt3: public ::testing::Test
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
测试用例编号     : Test_AT_ValidateWasCategoryExt3_001
测试用例标题     : ucHSDSCHPhyCategoryExt3为20
预期结果         : 返回VOS_ERR
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ValidateWasCategoryExt3, Test_AT_ValidateWasCategoryExt3_001)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucDcMimoSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt3  = 20;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_ValidateWasCategoryExt3(&stUeCapability);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_ValidateWasCategoryExt3_002
测试用例标题     : ucHSDSCHPhyCategoryExt3为26
预期结果         : 返回VOS_OK
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ValidateWasCategoryExt3, Test_AT_ValidateWasCategoryExt3_002)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucDcMimoSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt3  = 26;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_ValidateWasCategoryExt3(&stUeCapability);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_GetWasDefaultCategory
功能描述: AT_GetWasDefaultCategory  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_GetWasDefaultCategory: public ::testing::Test
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
测试用例编号     : Test_AT_GetWasDefaultCategory_001
测试用例标题     : ucAsRelIndicator为PS_PTL_VER_R5
预期结果         : 返回AT_RATE_WCDMA_CATEGORY_10
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetWasDefaultCategory, Test_AT_GetWasDefaultCategory_001)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // 参数初始化
    stUeCapability.ucAsRelIndicator = PS_PTL_VER_R5;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_GetWasDefaultCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(AT_RATE_WCDMA_CATEGORY_10, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_GetWasDefaultCategory_002
测试用例标题     : ucAsRelIndicator为PS_PTL_VER_R6
预期结果         : 返回AT_RATE_WCDMA_CATEGORY_10
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetWasDefaultCategory, Test_AT_GetWasDefaultCategory_002)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // 参数初始化
    stUeCapability.ucAsRelIndicator = PS_PTL_VER_R6;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_GetWasDefaultCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(AT_RATE_WCDMA_CATEGORY_10, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_GetWasDefaultCategory_003
测试用例标题     : ucAsRelIndicator为PS_PTL_VER_R7
预期结果         : 返回AT_RATE_WCDMA_CATEGORY_18
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetWasDefaultCategory, Test_AT_GetWasDefaultCategory_003)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // 参数初始化
    stUeCapability.ucAsRelIndicator = PS_PTL_VER_R7;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_GetWasDefaultCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(AT_RATE_WCDMA_CATEGORY_18, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_GetWasDefaultCategory_004
测试用例标题     : ucAsRelIndicator为PS_PTL_VER_R8
预期结果         : 返回AT_RATE_WCDMA_CATEGORY_28
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetWasDefaultCategory, Test_AT_GetWasDefaultCategory_004)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // 参数初始化
    stUeCapability.ucAsRelIndicator = PS_PTL_VER_R8;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_GetWasDefaultCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(AT_RATE_WCDMA_CATEGORY_28, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_CalcWasCategory
功能描述: AT_CalcWasCategory  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_CalcWasCategory: public ::testing::Test
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
测试用例编号     : Test_AT_CalcWasCategory_001
测试用例标题     : 检查UE能力中CategoryExt3有效性正确
预期结果         : 返回CategoryExt3值
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_CalcWasCategory, Test_AT_CalcWasCategory_001)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // 参数初始化
    PS_MEM_SET(&stUeCapability, 0, sizeof(stUeCapability));

    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucDcMimoSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt3  = 26;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_CalcWasCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(26, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_CalcWasCategory_002
测试用例标题     : 检查UE能力中CategoryExt2有效性正确
预期结果         : 返回CategoryExt2值
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_CalcWasCategory, Test_AT_CalcWasCategory_002)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // 参数初始化
    PS_MEM_SET(&stUeCapability, 0, sizeof(stUeCapability));

    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt2  = 22;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_CalcWasCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(22, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号     : Test_AT_CalcWasCategory_003
测试用例标题     : 检查UE能力中CategoryExt有效性正确
预期结果         : 返回CategoryExt值
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_CalcWasCategory, Test_AT_CalcWasCategory_003)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // 参数初始化
    PS_MEM_SET(&stUeCapability, 0, sizeof(stUeCapability));

    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt   = 15;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_CalcWasCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(15, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_CalcWasCategory_004
测试用例标题     : 检查UE能力中Category有效性正确
预期结果         : 返回HSDSCHPhyCategory值
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_CalcWasCategory, Test_AT_CalcWasCategory_004)
{
    // 参数定义
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // 参数初始化
    stUeCapability.ucHSDSCHSupport      = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategory  = 2;

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_CalcWasCategory(&stUeCapability);

    // 执行检查
    EXPECT_EQ(2, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_AT_ReadGasCapabilityNV
功能描述   : AT_ReadGasCapabilityNV UT工程类
修改历史   :
1.日   期  : 2012-02-08
  作   者  : z60575
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadGasCapabilityNV: public ::testing::Test
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
测试用例编号      : Test_AT_ReadGasCapabilityNV_001
测试用例标题      : NV读取失败
预期结果          : 匹配输出字符串
修改历史   :
1.日   期  : 2012-02-08
  作   者  : z60575
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_AT_ReadGasCapabilityNV, Test_AT_ReadGasCapabilityNV_001)
{
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /* 调用消息入口函数 */
    AT_ReadGasCapabilityNV();

    /* 结果验证*/
    EXPECT_EQ(VOS_FALSE,g_stAtDlRateCategory.ucGasMultislotClass33Flg);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadGasCapabilityNV_002
测试用例标题      : NV读取成功并支持CLASS33
预期结果          : 匹配输出字符串
修改历史   :
1.日   期  : 2012-02-08
  作   者  : z60575
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_AT_ReadGasCapabilityNV, Test_AT_ReadGasCapabilityNV_002)
{
    NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU          stHighMultislotclass;
    VOS_UINT16                                  usGprsMultiSlotClass;
    VOS_UINT16                                  usEgprsMultiSlotClass;
    VOS_UINT16                                  usEgprsFlag;

    usEgprsFlag                                     = VOS_TRUE;
    usGprsMultiSlotClass                            = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    usEgprsMultiSlotClass                           = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    stHighMultislotclass.usHighMultislotClassFlg    = VOS_TRUE;
    stHighMultislotclass.usHighMultislotClass       = AT_GAS_HIGH_MULTISLOT_CLASS_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_Egprs_Flag),outBoundP((void *)&usEgprsFlag, (VOS_UINT32)sizeof(usEgprsFlag)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_Nv_Item_Gprs_Multi_Slot_Class),outBoundP((void *)&usGprsMultiSlotClass, (VOS_UINT32)sizeof(usGprsMultiSlotClass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_Egprs_Multi_Slot_Class),outBoundP((void *)&usEgprsMultiSlotClass, (VOS_UINT32)sizeof(usEgprsMultiSlotClass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_GAS_High_Multislot_Class),outBoundP((void *)&stHighMultislotclass, (VOS_UINT32)sizeof(stHighMultislotclass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 调用消息入口函数 */
    AT_ReadGasCapabilityNV();

    /* 结果验证*/
    EXPECT_EQ(VOS_TRUE,g_stAtDlRateCategory.ucGasMultislotClass33Flg);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadGasCapabilityNV_003
测试用例标题      : NV读取成功gprs
预期结果          : 匹配输出字符串
修改历史   :
1.日   期  : 2012-02-08
  作   者  : z60575
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_AT_ReadGasCapabilityNV, Test_AT_ReadGasCapabilityNV_003)
{
    NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU          stHighMultislotclass;
    VOS_UINT16                                  usGprsMultiSlotClass;
    VOS_UINT16                                  usEgprsMultiSlotClass;
    VOS_UINT16                                  usEgprsFlag;

    usEgprsFlag                                     = VOS_FALSE;
    usGprsMultiSlotClass                            = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    usEgprsMultiSlotClass                           = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    stHighMultislotclass.usHighMultislotClassFlg    = VOS_TRUE;
    stHighMultislotclass.usHighMultislotClass       = AT_GAS_HIGH_MULTISLOT_CLASS_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_Egprs_Flag),outBoundP((void *)&usEgprsFlag, (VOS_UINT32)sizeof(usEgprsFlag)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_Nv_Item_Gprs_Multi_Slot_Class),outBoundP((void *)&usGprsMultiSlotClass, (VOS_UINT32)sizeof(usGprsMultiSlotClass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_Egprs_Multi_Slot_Class),outBoundP((void *)&usEgprsMultiSlotClass, (VOS_UINT32)sizeof(usEgprsMultiSlotClass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_GAS_High_Multislot_Class),outBoundP((void *)&stHighMultislotclass, (VOS_UINT32)sizeof(stHighMultislotclass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /* 调用消息入口函数 */
    AT_ReadGasCapabilityNV();

    /* 结果验证*/
    EXPECT_EQ(VOS_TRUE,g_stAtDlRateCategory.ucGasMultislotClass33Flg);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
类名    : Test_AT_ReadIpv6CapabilityNV
功能描述: AT_ReadIpv6CapabilityNV  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ReadIpv6CapabilityNV: public ::testing::Test
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
测试用例编号     : Test_AT_ReadIpv6CapabilityNV_001
测试用例标题     : 从NV中读取IPV6能力相关信息
预期结果         : 读取成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadIpv6CapabilityNV, Test_AT_ReadIpv6CapabilityNV_001)
{
    // 参数定义
    AT_NV_IPV6_CAPABILITY_STRU          stNvIpv6Capability;

    // 参数初始化
    stNvIpv6Capability.ucStatus = VOS_TRUE;
    stNvIpv6Capability.ucIpv6Capablity = AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;

    // 相关全局变量初始化

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), outBoundP((void *)&stNvIpv6Capability, (VOS_UINT32)sizeof(stNvIpv6Capability)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadIpv6CapabilityNV();

    // 执行检查
    EXPECT_EQ(AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP, AT_GetCommPsCtxAddr()->ucIpv6Capability);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_ReadIpv6BackProcExtCauseNV
功能描述: AT_ReadIpv6BackProcExtCauseNV  UT工程类
修改历史    :
1.日   期 : 2013-05-8
  作   者 : l60609
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ReadIpv6BackProcExtCauseNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号     : Test_AT_ReadIpv6BackProcExtCauseNV_001
测试用例标题     : 从NV中读取IPV6能力相关信息
预期结果         : 读取成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadIpv6BackProcExtCauseNV, Test_AT_ReadIpv6BackProcExtCauseNV_001)
{
    TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU  stNvBackProcExtCause;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    memset(&stNvBackProcExtCause, 0x00, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU));

    stNvBackProcExtCause.ulActiveFlag = VOS_TRUE;
    stNvBackProcExtCause.aucSmCause[0] = 8;
    stNvBackProcExtCause.aucSmCause[1] = 112    ;
    stNvBackProcExtCause.aucSmCause[2] = 7;
    stNvBackProcExtCause.aucSmCause[3] = 113;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),
              eq((VOS_UINT16)en_NV_Item_IPV6_BACKPROC_EXT_CAUSE),
              outBoundP((void *)&stNvBackProcExtCause, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU)) ,
              eq((VOS_UINT32)sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadIpv6BackProcExtCauseNV();

    EXPECT_EQ(2, pstCommPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum);
    EXPECT_EQ(TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 8, pstCommPsCtx->stIpv6BackProcExtCauseTbl.aenPsCause[0]);
    EXPECT_EQ(TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 112, pstCommPsCtx->stIpv6BackProcExtCauseTbl.aenPsCause[1]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_ReadIpv6BackProcExtCauseNV_002
测试用例标题: NV读取成功
预期结果    : 返回AT_OK
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_AT_ReadIpv6BackProcExtCauseNV, Test_AT_ReadIpv6BackProcExtCauseNV_002)
{
    // 变量声明
    TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU  stNvIpv6BackProcExtCause;
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU *pstPsIpv6BackProcExtCause;

    // 参数初始化
    memset(&stNvIpv6BackProcExtCause, 0x00, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU));
    stNvIpv6BackProcExtCause.ulActiveFlag   = VOS_TRUE;
    stNvIpv6BackProcExtCause.aucSmCause[2]  = 33;

    // 初始化全局变量
    pstPsIpv6BackProcExtCause               = &(AT_GetCommPsCtxAddr()->stIpv6BackProcExtCauseTbl);

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),
              eq((VOS_UINT16)en_NV_Item_IPV6_BACKPROC_EXT_CAUSE),
              outBoundP((void *)&stNvIpv6BackProcExtCause, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU)) ,
              eq((VOS_UINT32)sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadIpv6BackProcExtCauseNV();

    // 执行检查
    EXPECT_EQ(pstPsIpv6BackProcExtCause->aenPsCause[0], TAF_PS_CONVERT_SM_CAUSE_TO_PS_CAUSE(stNvIpv6BackProcExtCause.aucSmCause[2]));
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名    : Test_AT_ReadPppDialErrCodeNV
功能描述: AT_ReadPppDialErrCodeNV  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ReadPppDialErrCodeNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号     : Test_AT_ReadPppDialErrCodeNV_001
测试用例标题     : 从NV中读取PPP拨号错误码上报相关信息
预期结果         : 读取成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadPppDialErrCodeNV, Test_AT_ReadPppDialErrCodeNV_001)
{
    // 参数定义
    NAS_NV_PPP_DIAL_ERR_CODE_STRU       stPppErrRpt;

    // 参数初始化
    stPppErrRpt.ucStatus         = VOS_TRUE;
    stPppErrRpt.ucErrCodeRpt     = PPP_DIAL_ERR_CODE_ENABLE;

    // 相关全局变量初始化

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stPppErrRpt, (VOS_UINT32)sizeof(stPppErrRpt)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadPppDialErrCodeNV();

    // 执行检查
    EXPECT_EQ(PPP_DIAL_ERR_CODE_ENABLE, gucPppDialErrCodeRpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_ReadCregAndCgregCiFourByteRptNV
功能描述: AT_ReadCregAndCgregCiFourByteRptNV  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_ReadCregAndCgregCiFourByteRptNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        
        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号     : Test_AT_ReadCregAndCgregCiFourByteRptNV_001
测试用例标题     : 从NV中读取CREG/CGREG的CI参数
预期结果         : 读取成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadCregAndCgregCiFourByteRptNV, Test_AT_ReadCregAndCgregCiFourByteRptNV_001)
{
    // 参数定义
    NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU     stCiFourByteRpt;

    // 参数初始化
    stCiFourByteRpt.ucStatus     = VOS_TRUE;
    stCiFourByteRpt.ucCiBytesRpt = CREG_CGREG_CI_RPT_FOUR_BYTE;

    // 相关全局变量初始化

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stCiFourByteRpt, (VOS_UINT32)sizeof(stCiFourByteRpt)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadCregAndCgregCiFourByteRptNV();

    // 执行检查
    EXPECT_EQ(CREG_CGREG_CI_RPT_FOUR_BYTE, gucCiRptByte);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_AT_InitDeviceCmd
功能描述   : AT_InitDeviceCmd UT工程类
修改历史   :
1.日   期  : 2013-03-08
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitDeviceCmd: public ::testing::Test
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
测试用例编号  : Test_AT_InitDeviceCmd_001
测试用例标题  : 读取物理号相关的NV
预期结果      : 读取NV成功
修改历史      :
1.日    期    : 2013年03月08日
  作    者    : l60609
  修改内容    : DSDA PHASE III
*******************************************************************/
TEST_F(Test_AT_InitDeviceCmd, Test_AT_InitDeviceCmd_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucImei[TAF_PH_IMEI_LEN]     = {0x01, 0x02, 0x03, 0x04, 0x06};

    // 参数初始化
    enModemId = MODEM_ID_0;

    // 相关全局变量初始化
    g_bAtDataLocked         = VOS_TRUE;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_IMEI), outBoundP((void *)&aucImei, TAF_PH_IMEI_LEN))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_InitDeviceCmd();

    // 执行检查
    EXPECT_EQ(VOS_TRUE, g_bAtDataLocked);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号  : Test_AT_InitDeviceCmd_002
测试用例标题  : 读取物理号相关的NV
预期结果      : 读取NV成功，但IMEI为空
修改历史      :
1.日    期    : 2013年03月08日
  作    者    : l60609
  修改内容    : DSDA PHASE III
*******************************************************************/
TEST_F(Test_AT_InitDeviceCmd, Test_AT_InitDeviceCmd_002)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucImei[TAF_PH_IMEI_LEN]     = {0};

    // 参数初始化
    enModemId = MODEM_ID_0;

    // 相关全局变量初始化
    g_bAtDataLocked         = VOS_TRUE;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_IMEI), outBoundP((void *)&aucImei, TAF_PH_IMEI_LEN))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_InitDeviceCmd();

    // 执行检查
    EXPECT_EQ(VOS_FALSE, g_bAtDataLocked);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_UsbSwitchGwMode
功能描述: AT_UsbSwitchGwMode  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_UsbSwitchGwMode: public ::testing::Test
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
测试用例编号     : Test_AT_UsbSwitchGwMode_001
测试用例标题     : 有一个PDP处于DEACTING
预期结果         : 返回
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_UsbSwitchGwMode, Test_AT_UsbSwitchGwMode_001)
{
    // 参数定义

    // 参数初始化

    // 相关全局变量初始化
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_DEACTING;

    // MOCKER操作
    MOCKER(TAF_PS_CallEnd).expects(never());

    // 调用被测函数
    AT_UsbSwitchGwMode();

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_UsbSwitchGwMode_002
测试用例标题     : 有IPV4 PDP不处于IDLE，结束PS CALL
预期结果         : 返回
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_UsbSwitchGwMode, Test_AT_UsbSwitchGwMode_002)
{
    // 参数定义

    // 参数初始化

    // 相关全局变量初始化
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_ACTING;
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;

    // MOCKER操作
    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_AppSetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV4), eq((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_DEACTING));

    // 调用被测函数
    AT_UsbSwitchGwMode();

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_UsbSwitchGwMode_003
测试用例标题     : 有IPV6 PDP不处于IDLE，结束PS CALL
预期结果         : 返回
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_UsbSwitchGwMode, Test_AT_UsbSwitchGwMode_003)
{
    // 参数定义

    // 参数初始化

    // 相关全局变量初始化
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_ACTING;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;

    // MOCKER操作
    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_AppSetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV6), eq((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_DEACTING));

    // 调用被测函数
    AT_UsbSwitchGwMode();

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_UsbSwitchGwMode_004
测试用例标题     : 有IPV4V6 PDP不处于IDLE，结束PS CALL
预期结果         : 返回
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_UsbSwitchGwMode, Test_AT_UsbSwitchGwMode_004)
{
    // 参数定义

    // 参数初始化

    // 相关全局变量初始化
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_ACTING;

    // MOCKER操作
    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_AppSetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV4V6), eq((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_DEACTING));

    // 调用被测函数
    AT_UsbSwitchGwMode();

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_InitPort
功能描述: AT_InitPort  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_InitPort: public ::testing::Test
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
测试用例编号     : Test_AT_InitPort_001
测试用例标题     : 端口口建立失败
预期结果         : 打印log
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitPort, Test_AT_InitPort_001)
{
    // 参数定义

    // 参数初始化

    // 相关全局变量初始化

    // MOCKER操作
    MOCKER(BSP_USB_NASSwitchGatewayRegFunc)
        .stubs()
        .will(returnValue(VOS_ERROR));
    MOCKER(BSP_GetHsicEnumStatus)
        .stubs()
        .will(returnValue(VOS_FALSE));

    // 调用被测函数
    AT_InitPort();

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_InitPort_002
测试用例标题     : 端口断开
预期结果         : 调用注册的断开函数
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitPort, Test_AT_InitPort_002)
{
    // 参数定义

    // 参数初始化

    // 相关全局变量初始化

    // MOCKER操作

    // 调用被测函数
    AT_UsbEnableCB();
    AT_UsbDisableCB();
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_HsicEnableCB();
    AT_HsicDisableCB();
#endif

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_AT_InitPara
功能描述: AT_InitPara  UT工程类
修改历史    :
1.日   期 : 2013-03-11
  作   者 : l00227485
  修改内容: 新生成类
*****************************************************************************/
class Test_AT_InitPara: public ::testing::Test
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
测试用例编号     : Test_AT_InitPara_001
测试用例标题     : 当前特性为SYSTEM_APP_WEBUI
预期结果         : 初始化成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitPara, Test_AT_InitPara_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;

    // 参数初始化
    enModemId = MODEM_ID_0;

    // 相关全局变量初始化
    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    // MOCKER操作

    // 调用被测函数
    AT_InitPara();

    // 执行检查
    EXPECT_EQ(AT_COPS_NUMERIC_TYPE, g_astAtModemCtx[MODEM_ID_0].stNetCtx.ucCopsFormatType);
    EXPECT_EQ(AT_CMEE_ERROR_CODE, gucAtCmeeType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_InitPara_002
测试用例标题     : 当前特性为SYSTEM_APP_ANDROID
预期结果         : 初始化成功
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitPara, Test_AT_InitPara_002)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;

    // 参数初始化
    enModemId = MODEM_ID_0;

    // 相关全局变量初始化
    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    // MOCKER操作

    // 调用被测函数
    AT_InitPara();

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        EXPECT_EQ(AT_COPS_LONG_ALPH_TYPE, g_astAtModemCtx[enModemId].stNetCtx.ucCopsFormatType);
    }
    EXPECT_EQ(AT_CMEE_ERROR_CONTENT, gucAtCmeeType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_AT_InitPara_003
测试用例标题     : 当前特性为SYSTEM_APP_BUTT
预期结果         : 直接返回
修改历史         :
1.日  期         : 2013-03-11
  作  者         : l00227485
  修改内容       : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitPara, Test_AT_InitPara_003)
{
    // 参数定义

    // 参数初始化

    // 相关全局变量初始化
    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_BUTT;

    // MOCKER操作

    // 调用被测函数
    AT_InitPara();

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_At_PidInit
功能描述   : At_PidInit UT工程类
修改历史   :
1.日   期  : 2013-03-08
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_PidInit: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmCCreate)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));
        
        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));
    }
    void TearDown()
    {
    }
protected:

};

#if (FEATURE_ON == FEATURE_E5)

/*******************************************************************
*测试项:              AT_E5ComEst返回ERROR
*被测函数功能描述:    AT PID初始化函数,该函数注册给DOPRA使用
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年10月09日
#    作    者: lijun 00171473
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_PidInit,AT_E5ComEst返回ERROR)
{
    //参数定义
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //参数初始化
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stAtCmdRptCtrl.ucStatus = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl = 2;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 0;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;

    MOCKER(AT_E5ComEst)
        .stubs()
        .will(returnValue(VOS_ERR));

    //调用被测函数
    ulResult = At_PidInit(enPhase);

    //执行检查
    EXPECT_EQ(NV_OK, ulResult);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


#if (FEATURE_ON == FEATURE_NDIS)
/*******************************************************************
*测试项:              AT_UsbNdisEst返回ERROR
*被测函数功能描述:    AT PID初始化函数,该函数注册给DOPRA使用
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2012年1月4日
#    作    者: L47619
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_PidInit,AT_UsbNdisEst返回ERROR)
{
    //参数定义
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //参数初始化
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stAtCmdRptCtrl.ucStatus = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl = 2;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 0;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;

    MOCKER(AT_UsbNdisEst)
        .stubs()
        .will(returnValue(VOS_ERR));

    //调用被测函数
    ulResult = At_PidInit(enPhase);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
/*******************************************************************
*测试项:              AT初始化成功，读NV项成功，且取值范围正确
*被测函数功能描述:    AT PID初始化函数,该函数注册给DOPRA使用
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年7月30日
#    作    者: o00132663
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_PidInit,Test_At_PidInit_001)
{
    //参数定义
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //参数初始化
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 1;
    stUssdTranMode.ucUssdTransMode = AT_USSD_NON_TRAN_MODE;

    aucTmp[0] = 1;

    usReportCregActParaFlg = VOS_TRUE;


    //相关全局变量初始化

    //调用被测函数
    ulResult = At_PidInit(enPhase);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
*测试项:              AT初始化失败，读NV项均失败
*被测函数功能描述:    AT PID初始化函数,该函数注册给DOPRA使用
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年7月30日
#    作    者: o00132663
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_PidInit,Test_At_PidInit_002)
{
    //参数定义
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //参数初始化
    enPhase = VOS_IP_INITIAL;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 1;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    //调用被测函数
    ulResult = At_PidInit(enPhase);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);
    EXPECT_EQ(VOS_FALSE, AT_GetModemSmsCtxAddrFromClientId(0)->stCgsmsSendDomain.ucActFlg);
    EXPECT_EQ(AT_USSD_TRAN_MODE, AT_GetModemSsCtxAddrFromClientId(0)->usUssdTransMode);
    EXPECT_EQ(AT_ROAM_FEATURE_OFF, AT_GetModemNetCtxAddrFromClientId(0)->ucRoamFeature);
    EXPECT_EQ(VOS_FALSE, g_usReportCregActParaFlg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
*测试项:              AT初始化成功，读NV项成功，但超出取值范围
*被测函数功能描述:    AT PID初始化函数,该函数注册给DOPRA使用
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年7月30日
#    作    者: o00132663
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_PidInit,Test_At_PidInit_003)
{
    //参数定义
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //参数初始化
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 0;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;


    //调用被测函数
    ulResult = At_PidInit(enPhase);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);


    //检查调用时，需要在用例结束位置加上这句
        GlobalMockObject::verify();
}

/*******************************************************************
*测试项:              AT未进行初始化
*被测函数功能描述:    AT PID初始化函数,该函数注册给DOPRA使用
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2010年7月30日
#    作    者: o00132663
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_PidInit,Test_At_PidInit_004)
{
    //参数定义
    enum VOS_INIT_PHASE_DEFINE          enPhase;
    TAF_UINT32                          ulResult;

    //参数初始化
    enPhase = VOS_IP_BUTT;

    //MOCKER操作
    MOCKER(AT_InitCtx).expects(never());

    //调用被测函数
    ulResult = At_PidInit(enPhase);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)
/*******************************************************************
*测试项:              AT_HsicInit返回ERROR
*被测函数功能描述:    AT PID初始化函数,该函数注册给DOPRA使用
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2012年2月25日
#    作    者: L47619
#    修改内容: 新建CASE
*******************************************************************/
TEST_F(Test_At_PidInit, AT_HsicInit返回ERROR)
{
    //参数定义
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //参数初始化
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 0;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;

    MOCKER(AT_HsicInit)
        .stubs()
        .will(returnValue(AT_FAILURE));

    //调用被测函数
    ulResult = At_PidInit(enPhase);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_AT_ReadUartCfgNV
功能描述 : AT_ReadUartCfgNV UT工程类
修改历史 :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ReadUartCfgNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitHsUartStats();
    }
    void TearDown()
    {
        AT_InitHsUartStats();
    }
};

/*******************************************************************
测试用例编号      : Test_AT_ReadUartCfgNV_001
测试用例标题      : 读NV失败
预期结果          : 可维可测中，读NV失败计数为1
修改历史          :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadUartCfgNV, Test_AT_ReadUartCfgNV_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    AT_ReadUartCfgNV();

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadUartCfgNV_002
测试用例标题      : 读NV成功
预期结果          : UART上下文中值与NV中设置一样
修改历史          :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadUartCfgNV, Test_AT_ReadUartCfgNV_002)
{
    // 变量声明
    TAF_NV_UART_CFG_STRU                stUartNVCfg;
    AT_UART_CTX_STRU                   *pstUartCtx          = VOS_NULL_PTR;

    // 参数初始化
    memset(&stUartNVCfg, 0x0,sizeof(stUartNVCfg));
    stUartNVCfg.ulBaudRate          = AT_UART_BAUDRATE_115200;
    stUartNVCfg.stFrame.ucFormat    = AT_UART_FORMAT_8DATA_1STOP;
    stUartNVCfg.stFrame.ucParity    = AT_UART_PARITY_SPACE;

    pstUartCtx = AT_GetUartCtxAddr();

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stUartNVCfg, sizeof(stUartNVCfg)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadUartCfgNV();

    // 执行检查
    EXPECT_EQ(AT_UART_BAUDRATE_115200, pstUartCtx->stPhyConfig.enBaudRate);
    EXPECT_EQ(AT_UART_FORMAT_8DATA_1STOP, pstUartCtx->stPhyConfig.stFrame.enFormat);
    EXPECT_EQ(AT_UART_PARITY_SPACE, pstUartCtx->stPhyConfig.stFrame.enParity);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadUartCfgNV_003
测试用例标题      : NV中的值不合法
预期结果          : UART上下文中值与默认值一样
修改历史          :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadUartCfgNV, Test_AT_ReadUartCfgNV_003)
{
    // 变量声明
    TAF_NV_UART_CFG_STRU                stUartNVCfg;
    AT_UART_CTX_STRU                   *pstUartCtx          = VOS_NULL_PTR;

    // 参数初始化
    memset(&stUartNVCfg, 0x0,sizeof(stUartNVCfg));
    stUartNVCfg.ulBaudRate          = AT_UART_BAUDRATE_BUTT;
    stUartNVCfg.stFrame.ucFormat    = AT_UART_FORMAT_BUTT;
    stUartNVCfg.stFrame.ucParity    = AT_UART_PARITY_SPACE;

    pstUartCtx = AT_GetUartCtxAddr();

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stUartNVCfg, sizeof(stUartNVCfg)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadUartCfgNV();

    // 执行检查
    EXPECT_EQ(AT_UART_BAUDRATE_115200, pstUartCtx->stPhyConfig.enBaudRate);
    EXPECT_EQ(AT_UART_FORMAT_8DATA_1STOP, pstUartCtx->stPhyConfig.stFrame.enFormat);
    EXPECT_EQ(AT_UART_PARITY_SPACE, pstUartCtx->stPhyConfig.stFrame.enParity);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ReadUartCfgNV_004
测试用例标题      : 获取帧格式参数失败
预期结果          : 打印失败
修改历史          :
1.日   期  : 2013-10-15
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ReadUartCfgNV, Test_AT_ReadUartCfgNV_004)
{
    // 变量声明
    TAF_NV_UART_CFG_STRU                stUartNVCfg;
    AT_UART_CTX_STRU                   *pstUartCtx          = VOS_NULL_PTR;

    // 参数初始化
    memset(&stUartNVCfg, 0x0,sizeof(stUartNVCfg));
    stUartNVCfg.ulBaudRate          = AT_UART_BAUDRATE_115200;
    stUartNVCfg.stFrame.ucFormat    = AT_UART_FORMAT_8DATA_1STOP;
    stUartNVCfg.stFrame.ucParity    = AT_UART_PARITY_BUTT;

    pstUartCtx = AT_GetUartCtxAddr();

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stUartNVCfg, sizeof(stUartNVCfg)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_ReadUartCfgNV();

    // 执行检查
    EXPECT_EQ(AT_UART_BAUDRATE_115200, pstUartCtx->stPhyConfig.enBaudRate);
    EXPECT_EQ(AT_UART_FORMAT_8DATA_1STOP, pstUartCtx->stPhyConfig.stFrame.enFormat);
    EXPECT_EQ(AT_UART_PARITY_SPACE, pstUartCtx->stPhyConfig.stFrame.enParity);

    GlobalMockObject::verify();
}


