#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCtx.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CTX_C

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
类名     : Test_AT_InitPlatformRatList
功能描述 : AT_InitPlatformRatList UT工程类
修改历史 :
1.日   期  : 2013-01-04
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitPlatformRatList: public ::testing::Test
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
测试用例编号      : Test_AT_InitPlatformRatList_001
测试用例标题      : 初始化全局变量
预期结果          : 初始化成功
修改历史          :
1.日   期  : 2013-01-04
  作   者  : z00220246
  修改内容 : 新建CASE
2.日    期   : 2014年03月04日
  作    者   : f62575
  修改内容   : DTS2014030801193, +CSMP初始值不生效
*******************************************************************/
TEST_F(Test_AT_InitPlatformRatList,Test_AT_InitPlatformRatList_001)
{
    //参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx;
    VOS_UINT8                           ucPlatformSptGsm;
    VOS_UINT8                           ucPlatformSptWcdma;
    VOS_UINT8                           ucPlatformSptLte;

    // 参数初始化
    ucPlatformSptGsm    = VOS_TRUE;
    ucPlatformSptWcdma  = VOS_FALSE;
    ucPlatformSptLte    = VOS_FALSE;

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstAtModemCtx = AT_GetModemCtxAddr(enModemId);

        //执行检查
        EXPECT_EQ(ucPlatformSptGsm, pstAtModemCtx->stPlatformRatList.ucPlatformSptGsm);
        EXPECT_EQ(ucPlatformSptWcdma, pstAtModemCtx->stPlatformRatList.ucPlatformSptWcdma);
        EXPECT_EQ(ucPlatformSptLte, pstAtModemCtx->stPlatformRatList.ucPlatformSptLte);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_InitUsimStatus
功能描述 : AT_InitUsimStatus UT工程类
修改历史 :
1.日   期  : 2013-01-04
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitUsimStatus: public ::testing::Test
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
测试用例编号      : Test_AT_InitUsimStatus_001
测试用例标题      : 初始化全局变量
预期结果          : 初始化成功
修改历史          :
1.日   期  : 2013-01-04
  作   者  : z00220246
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitUsimStatus,Test_AT_InitUsimStatus_001)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx;

    // 参数初始化

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstAtModemCtx = AT_GetModemCtxAddr(enModemId);

        //执行检查
        EXPECT_EQ(USIMM_CARD_SERVIC_BUTT, pstAtModemCtx->stAtUsimInfoCtx.enCardStatus);
        EXPECT_EQ(USIMM_CARD_TYPE_BUTT, pstAtModemCtx->stAtUsimInfoCtx.enCardType);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_InitModemSmsCtx
功能描述 : AT_InitModemSmsCtx UT工程类
修改历史 :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitModemSmsCtx: public ::testing::Test
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
测试用例编号      : Test_AT_InitModemSmsCtx_001
测试用例标题      : 初始化短信相关的上下文
预期结果          : 上下文初始化成功
修改历史          :
1.日   期  : 2013-03-07
  作   者  : l00227485
  修改内容 : 新建CASE
2.日    期   : 2014年03月04日
  作    者   : f62575
  修改内容   : DTS2014030801193, +CSMP初始值不生效
*******************************************************************/
TEST_F(Test_AT_InitModemSmsCtx, Test_AT_InitModemSmsCtx_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx;
    MN_MSG_VALID_PERIOD_ENUM_U8         enValidPeriod;                          /*TP Validity Period Format*/
    VOS_UINT8                           ucOtherTime;

    // 参数初始化
    enValidPeriod   = MN_MSG_VALID_PERIOD_RELATIVE;
    ucOtherTime     = AT_CSMP_SUBMIT_VP_DEFAULT_VALUE;

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstAtModemCtx = AT_GetModemCtxAddr(enModemId);

        EXPECT_EQ(AT_CMGF_MSG_FORMAT_PDU, pstAtModemCtx->stSmsCtx.enCmgfMsgFormat);
        EXPECT_EQ(AT_CSDH_NOT_SHOW_TYPE, pstAtModemCtx->stSmsCtx.ucCsdhType);
        EXPECT_EQ(VOS_FALSE ,pstAtModemCtx->stSmsCtx.ucParaCmsr);
        EXPECT_EQ(VOS_FALSE ,pstAtModemCtx->stSmsCtx.ucSmsAutoReply);
        EXPECT_EQ(MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS ,pstAtModemCtx->stSmsCtx.enCsmsMsgVersion);
        EXPECT_EQ(MN_MSG_ME_STORAGE_DISABLE ,pstAtModemCtx->stSmsCtx.enMsgMeStorageStatus);
        EXPECT_EQ(AT_CNMI_MODE_BUFFER_TYPE ,pstAtModemCtx->stSmsCtx.stCnmiType.CnmiModeType);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS_PREFERRED ,pstAtModemCtx->stSmsCtx.stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM ,pstAtModemCtx->stSmsCtx.stCpmsInfo.enMemSendorWrite);
        EXPECT_EQ(MN_MSG_RCVMSG_ACT_STORE ,pstAtModemCtx->stSmsCtx.stCpmsInfo.stRcvPath.enRcvSmAct);
        EXPECT_EQ(enValidPeriod, pstAtModemCtx->stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod);
        EXPECT_EQ(ucOtherTime, pstAtModemCtx->stSmsCtx.stCscaCsmpInfo.stVp.u.ucOtherTime);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_InitModemCcCtx
功能描述 : AT_InitModemCcCtx UT工程类
修改历史 :
1.日   期  : 2013-03-11
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitModemCcCtx: public ::testing::Test
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
测试用例编号      : Test_AT_InitModemCcCtx_001
测试用例标题      : 初始化CC相关的上下文
预期结果          : 上下文初始化成功
修改历史          :
1.日   期  : 2013-03-07
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitModemCcCtx, Test_AT_InitModemCcCtx_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    // 参数初始化

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_FALSE, pstCcCtx->ulCurIsExistCallFlag);
        EXPECT_EQ(TAF_CS_CAUSE_SUCCESS, pstCcCtx->enCsErrCause);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_InitModemSsCtx
功能描述 : AT_InitModemSsCtx UT工程类
修改历史 :
1.日   期  : 2013-03-11
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitModemSsCtx: public ::testing::Test
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
测试用例编号      : Test_AT_InitModemSsCtx_001
测试用例标题      : 初始化SS相关的上下文
预期结果          : 上下文初始化成功
修改历史          :
1.日   期  : 2013-03-07
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitModemSsCtx, Test_AT_InitModemSsCtx_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    // 参数初始化

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_USSD_TRAN_MODE ,pstSsCtx->usUssdTransMode);
        EXPECT_EQ(MN_CALL_MODE_SINGLE , pstSsCtx->enCModType);
        EXPECT_EQ(AT_SALS_DISABLE_TYPE , pstSsCtx->ucSalsType);
        EXPECT_EQ(AT_CLIP_DISABLE_TYPE , pstSsCtx->ucClipType);
        EXPECT_EQ(AT_CLIR_AS_SUBSCRIPT , pstSsCtx->ucClirType);
        EXPECT_EQ(AT_COLP_DISABLE_TYPE , pstSsCtx->ucColpType);
        EXPECT_EQ(AT_CRC_DISABLE_TYPE , pstSsCtx->ucCrcType);
        EXPECT_EQ(AT_CCWA_DISABLE_TYPE , pstSsCtx->ucCcwaType);

        EXPECT_EQ(MN_CALL_CSD_SPD_64K_MULTI , pstSsCtx->stCbstDataCfg.enSpeed);
        EXPECT_EQ(MN_CALL_CSD_NAME_SYNC_UDI , pstSsCtx->stCbstDataCfg.enName);
        EXPECT_EQ(MN_CALL_CSD_CE_T , pstSsCtx->stCbstDataCfg.enConnElem);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_InitModemNetCtx
功能描述 : AT_InitModemNetCtx UT工程类
修改历史 :
1.日   期  : 2013-03-07
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitModemNetCtx: public ::testing::Test
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
测试用例编号      : Test_AT_InitModemNetCtx_001
测试用例标题      : 初始化网卡相关的上下文
预期结果          : 上下文初始化成功
修改历史          :
1.日   期  : 2013-03-07
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitModemNetCtx, Test_AT_InitModemNetCtx_001)
{
    // 参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    // 参数初始化

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_CERSSI_REPORT_TYPE_5DB_CHANGE_REPORT, pstNetCtx->ucCerssiReportType);
        EXPECT_EQ(AT_CREG_RESULT_CODE_NOT_REPORT_TYPE, pstNetCtx->ucCregType);
        EXPECT_EQ(AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE, pstNetCtx->ucCgregType);

        EXPECT_EQ(AT_COPS_LONG_ALPH_TYPE, pstNetCtx->ucCopsFormatType);
        EXPECT_EQ(MN_PH_PREF_PLMN_UPLMN, pstNetCtx->enPrefPlmnType);
        EXPECT_EQ(AT_COPS_NUMERIC_TYPE, pstNetCtx->ucCpolFormatType);
        EXPECT_EQ(AT_ROAM_FEATURE_OFF, pstNetCtx->ucRoamFeature);
        EXPECT_EQ(0, pstNetCtx->ucSpnType);
        EXPECT_EQ(AT_CMD_ANTENNA_LEVEL_0, pstNetCtx->enCalculateAntennaLevel);

#if(FEATURE_ON == FEATURE_LTE)
        EXPECT_EQ(AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE, pstNetCtx->ucCeregType);
#endif

    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_InitModemAgpsCtx
功能描述 : AT_InitModemAgpsCtx UT工程类
修改历史 :
1.日   期  : 2013-03-07
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitModemAgpsCtx: public ::testing::Test
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
测试用例编号      : Test_AT_InitModemAgpsCtx_001
测试用例标题      : 初始化AGPS相关的上下文
预期结果          : 上下文初始化成功
修改历史          :
1.日   期  : 2013-03-07
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitModemAgpsCtx, Test_AT_InitModemAgpsCtx_001)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx;

    // 参数初始化

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数

    // 执行检查
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstAgpsCtx = AT_GetModemAgpsCtxAddrFromModemId(enModemId);

        //执行检查
        EXPECT_EQ(AT_CPOSR_DISABLE, pstAgpsCtx->enCposrReport);
        EXPECT_EQ(AT_XCPOSR_DISABLE, pstAgpsCtx->enXcposrReport);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_InitClientConfiguration
功能描述 : Test_AT_InitClientConfiguration UT工程类
修改历史 :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitClientConfiguration: public ::testing::Test
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
测试用例编号      : Test_AT_InitClientConfiguration_001
测试用例标题      : 初始化client的配置信息
预期结果          : 返回
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitClientConfiguration, Test_AT_InitClientConfiguration_001)
{
    //参数定义

    //参数初始化

    //MOCKER操作

    //调用被测函数
    AT_InitClientConfiguration();

    //执行检查
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.enModemId);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_APP5_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_APP5_INDEX].stClientConfiguration.enModemId);
#endif
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.enModemId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_IsModemSupportRat
功能描述 : AT_IsModemSupportRat UT工程类
修改历史 :
1.日   期  : 2012-12-26
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_IsModemSupportRat: public ::testing::Test
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
        At_PidInit(VOS_IP_INITIAL);
    }
};

/*******************************************************************
测试用例编号      : Test_AT_IsModemSupportRat_001
测试用例标题      : Modem是否支持LTE
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2012-12-26
  作   者  : z00220246
  修改内容 : 新建CASE
*******************************************************************/
TEST(Test_AT_IsModemSupportRat,Test_AT_IsModemSupportRat_001)
{
    //参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
    VOS_UINT8                           ucRst;

    //参数初始化
    enModemId = MODEM_ID_0;
    enRat = TAF_MMA_RAT_LTE;

    //MOCKER操作

    //调用被测函数
    ucRst = AT_IsModemSupportRat(enModemId, enRat);

    //执行检查
    EXPECT_EQ(VOS_FALSE, ucRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_IsModemSupportRat_002
测试用例标题      : Modem是否支持WCDMA
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2012-12-26
  作   者  : z00220246
  修改内容 : 新建CASE
*******************************************************************/
TEST(Test_AT_IsModemSupportRat,Test_AT_IsModemSupportRat_002)
{
    //参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
    VOS_UINT8                           ucRst;

    //参数初始化
    enModemId = MODEM_ID_0;
    enRat = TAF_MMA_RAT_WCDMA;

    //MOCKER操作

    //调用被测函数
    ucRst = AT_IsModemSupportRat(enModemId, enRat);

    //执行检查
    EXPECT_EQ(VOS_FALSE, ucRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_IsModemSupportRat_003
测试用例标题      : Modem是否支持GSM
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2012-12-26
  作   者  : z00220246
  修改内容 : 新建CASE
*******************************************************************/
TEST(Test_AT_IsModemSupportRat,Test_AT_IsModemSupportRat_003)
{
    //参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
    VOS_UINT8                           ucRst;

    //参数初始化
    enModemId = MODEM_ID_0;
    enRat = TAF_MMA_RAT_GSM;

    //MOCKER操作

    //调用被测函数
    ucRst = AT_IsModemSupportRat(enModemId, enRat);

    //执行检查
    EXPECT_EQ(VOS_TRUE, ucRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_IsModemSupportRat_004
测试用例标题      : 接入技术不正确
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2012-12-26
  作   者  : z00220246
  修改内容 : 新建CASE
*******************************************************************/
TEST(Test_AT_IsModemSupportRat,Test_AT_IsModemSupportRat_004)
{
    //参数定义
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
    VOS_UINT8                           ucRst;

    //参数初始化
    enModemId = MODEM_ID_0;
    enRat = TAF_MMA_RAT_BUTT;

    //MOCKER操作

    //调用被测函数
    ucRst = AT_IsModemSupportRat(enModemId, enRat);

    //执行检查
    EXPECT_EQ(VOS_FALSE, ucRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_GetModemIdFromClient
功能描述 : Test_AT_GetModemIdFromClient UT工程类
修改历史 :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_GetModemIdFromClient: public ::testing::Test
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
测试用例编号      : Test_AT_GetModemIdFromClient_001
测试用例标题      : Client Index无效
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetModemIdFromClient, Test_AT_GetModemIdFromClient_001)
{
    //参数定义
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    UINT8                               ucRslt;

    //参数初始化
    enClientIndex = AT_CLIENT_BUTT;
    enModemId = MODEM_ID_0;

    //MOCKER操作

    //调用被测函数
    ucRslt = AT_GetModemIdFromClient(enClientIndex, &enModemId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ucRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetModemIdFromClient_002
测试用例标题      : Client Index有效，获取归属的ModemId(Modem0)
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetModemIdFromClient, Test_AT_GetModemIdFromClient_002)
{
    //参数定义
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    UINT8                               ucRslt;

    //参数初始化
    enClientIndex = AT_CLIENT_TAB_APP1_INDEX;
    enModemId = MODEM_ID_0;

    pstAtClientCtx = AT_GetClientCtxAddr(enClientIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    //MOCKER操作

    //调用被测函数
    ucRslt = AT_GetModemIdFromClient(enClientIndex, &enModemId);

    //执行检查
    EXPECT_EQ(MODEM_ID_0, enModemId);
    EXPECT_EQ(VOS_OK, ucRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_AT_GetModemIdFromClient_003
测试用例标题      : Client Index有效，获取归属的ModemIdModem1)
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetModemIdFromClient, Test_AT_GetModemIdFromClient_003)
{
    //参数定义
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    UINT8                               ucRslt;

    //参数初始化
    enClientIndex = AT_CLIENT_TAB_APP5_INDEX;
    enModemId = MODEM_ID_0;

    pstAtClientCtx = AT_GetClientCtxAddr(enClientIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    //MOCKER操作

    //调用被测函数
    ucRslt = AT_GetModemIdFromClient(enClientIndex, &enModemId);

    //执行检查
    EXPECT_EQ(MODEM_ID_1, enModemId);
    EXPECT_EQ(VOS_OK, ucRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_AT_GetDestPid
功能描述 : Test_AT_GetDestPid UT工程类
修改历史 :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_GetDestPid: public ::testing::Test
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
测试用例编号      : Test_AT_GetDestPid_001
测试用例标题      : MULTI_MODEM宏关闭
预期结果          : 返回传入的PID
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetDestPid, Test_AT_GetDestPid_001)
{
    //参数定义
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT32                          ulRcvPid;
    UINT8                               ucRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    usClientId = AT_CLIENT_ID_APP;
    ulRcvPid = I0_WUEPS_PID_TAF;
    enModemId = MODEM_ID_0;

    //MOCKER操作
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .with(eq(usClientId), outBoundP(&enModemId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ucRslt = AT_GetDestPid(usClientId, ulRcvPid);

    //执行检查
    EXPECT_EQ(I0_WUEPS_PID_TAF, ucRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_AT_GetDestPid_002
测试用例标题      : MULTI_MODEM宏打开，获取modem1的PID
预期结果          : 返回实际获取的PID
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetDestPid, Test_AT_GetDestPid_002)
{
    //参数定义
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT32                          ulRcvPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    //参数初始化
    usClientId = AT_CLIENT_ID_APP;
    enModemId  = MODEM_ID_0;
    ulRcvPid   = I0_WUEPS_PID_TAF;

    pstAtClientCtx = AT_GetClientCtxAddr((AT_CLIENT_TAB_INDEX_UINT8)usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_GetDestPid(usClientId, ulRcvPid);

    //执行检查
    EXPECT_EQ(I0_WUEPS_PID_TAF, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetDestPid_003
测试用例标题      : MULTI_MODEM宏打开，获取modem1的PID
预期结果          : 返回实际获取的PID
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetDestPid, Test_AT_GetDestPid_003)
{
    //参数定义
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT32                          ulRcvPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    //参数初始化
    usClientId = AT_CLIENT_ID_APP5;
    enModemId  = MODEM_ID_0;
    ulRcvPid   = I0_WUEPS_PID_TAF;

    pstAtClientCtx = AT_GetClientCtxAddr((AT_CLIENT_TAB_INDEX_UINT8)usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_GetDestPid(usClientId, ulRcvPid);

    //执行检查
    EXPECT_EQ(I1_WUEPS_PID_TAF, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetDestPid_004
测试用例标题      : MULTI_MODEM宏打开，获取modem1的PID
预期结果          : 返回MODEM1的PID
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetDestPid, Test_AT_GetDestPid_004)
{
    //参数定义
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRcvPid;
    MN_CLIENT_ID_T                      usClientId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    //参数初始化
    i = 0;
    ulRcvPid   = I0_WUEPS_PID_SS;
    enModemId  = MODEM_ID_0;
    usClientId = AT_CLIENT_ID_APP6;

    pstAtClientCtx = AT_GetClientCtxAddr((AT_CLIENT_TAB_INDEX_UINT8)usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_GetDestPid(usClientId, ulRcvPid);

    //执行检查
    EXPECT_EQ(I1_WUEPS_PID_SS, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif

/*****************************************************************************
类名     : Test_AT_GetSsCustomizePara
功能描述 : AT_GetSsCustomizePara UT工程类
修改历史 :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_GetSsCustomizePara: public ::testing::Test
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
测试用例编号      : Test_AT_GetSsCustomizePara_001
测试用例标题      : SS参数未定定制
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSsCustomizePara, Test_AT_GetSsCustomizePara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量
    g_stAtSsCustomizePara.ucStatus  = VOS_FALSE;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_CCWA_QUERY);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetSsCustomizePara_002
测试用例标题      : SS参数定制使能，并定制了参数
预期结果          : 返回VOS_TRUE
修改历史          :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSsCustomizePara, Test_AT_GetSsCustomizePara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量
    g_stAtSsCustomizePara.ucStatus          = VOS_TRUE;
    g_stAtSsCustomizePara.ucSsCmdCustomize  = 0x01;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_CCWA_QUERY);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetSsCustomizePara_003
测试用例标题      : SS参数定制使能，没有定制参数
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2013-04-17
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetSsCustomizePara, Test_AT_GetSsCustomizePara_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量
    g_stAtSsCustomizePara.ucStatus          = VOS_TRUE;
    g_stAtSsCustomizePara.ucSsCmdCustomize  = 0x10;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_CCWA_QUERY);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_InitResetCtx
功能描述 : AT_InitResetCtx UT工程类
修改历史 :
1.日   期  : 2013-04-25
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_InitResetCtx: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum = 0;
    }
    void TearDown()
    {
        g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum = 0;
    }
};

/*******************************************************************
测试用例编号      : Test_AT_InitResetCtx_001
测试用例标题      : 初始化信号量失败
预期结果          : 信号量初始化标志为VOS_FALSE
修改历史          :
1.日   期  : 2013-04-25
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_InitResetCtx, Test_AT_InitResetCtx_001)
{
    //参数定义

    //参数初始化

    //MOCKER操作
    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue(VOS_ERR));

    //调用被测函数
    AT_InitResetCtx();

    //执行检查
    EXPECT_EQ(VOS_FALSE, g_stAtStatsInfo.stCCpuResetStatsInfo.ulSemInitFlg);
    EXPECT_EQ(1, g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_PORT_BUFF_CFG
功能描述 : 端口缓存 UT工程类
修改历史 :
1.日   期  : 2014-01-07
  作   者  : j00174725
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_PORT_BUFF_CFG: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPortBuffCfg();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_001
测试用例标题      : 读取缓存NV
预期结果          : NV中的使能位不正确
修改历史          :
1.日   期  : 2014-01-07
  作   者  : j00174725
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_001)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;
    TAF_NV_PORT_BUFF_CFG_STRU           stSmsBuffCfg;

    stSmsBuffCfg.ucEnableFlg = AT_PORT_BUFF_BUTT;
    pstCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stSmsBuffCfg),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadPortBuffCfgNV();

    EXPECT_EQ(AT_PORT_BUFF_DISABLE,pstCommCtx->stPortBuffCfg.enSmsBuffCfg);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_002
测试用例标题      : 读取缓存NV
预期结果          : NV中的使能位正确
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_002)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;
    TAF_NV_PORT_BUFF_CFG_STRU           stSmsBuffCfg;

    PS_MEM_SET(&stSmsBuffCfg, 0, sizeof(TAF_NV_PORT_BUFF_CFG_STRU));

    stSmsBuffCfg.ucEnableFlg = AT_PORT_BUFF_ENABLE;
    pstCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0), eq((VOS_UINT16)en_NV_Item_PORT_BUFF_CFG), outBoundP((void *)&stSmsBuffCfg), eq((VOS_UINT32)sizeof(stSmsBuffCfg)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadPortBuffCfgNV();

    EXPECT_EQ(AT_PORT_BUFF_ENABLE, pstCommCtx->stPortBuffCfg.enSmsBuffCfg);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_003
测试用例标题      : 读取缓存NV
预期结果          : 读取NV失败
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_003)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    AT_ReadPortBuffCfgNV();

    EXPECT_EQ(AT_PORT_BUFF_DISABLE,pstCommCtx->stPortBuffCfg.enSmsBuffCfg);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_004
测试用例标题      : 获取缓存标识
预期结果          : 获取NV成功
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_004)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;
    TAF_NV_PORT_BUFF_CFG_STRU           stSmsBuffCfg;

    stSmsBuffCfg.ucEnableFlg = AT_PORT_BUFF_ENABLE;
    pstCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stSmsBuffCfg),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadPortBuffCfgNV();
    EXPECT_EQ(AT_PORT_BUFF_ENABLE, AT_GetPortBuffCfg());

    EXPECT_EQ(AT_PORT_BUFF_ENABLE,pstCommCtx->stPortBuffCfg.enSmsBuffCfg);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_005
测试用例标题      : 添加端口号
预期结果          : 不正确的端口ID
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_005)
{
    VOS_UINT16                      usClientId;

    usClientId = AT_MAX_CLIENT_NUM;

    AT_AddUsedClientId2Tab(usClientId);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_006
测试用例标题      : 添加端口号_
预期结果          : 当前添加的是内端口，最小的APP端口号
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_006)
{
    VOS_UINT16                      usClientId;

    usClientId = AT_CLIENT_ID_APP;

    AT_AddUsedClientId2Tab(usClientId);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_007
测试用例标题      : 添加端口号_
预期结果          : 当前添加的是内端口,最大的APP端口号
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_007)
{
    VOS_UINT16                      usClientId;

    usClientId = AT_MAX_APP_CLIENT_ID;

    AT_AddUsedClientId2Tab(usClientId);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_008
测试用例标题      : 添加端口号_
预期结果          : 当前端口记录个数超过最大值
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_008)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_PCUI;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM + 1;

    AT_AddUsedClientId2Tab(usClientId);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_009
测试用例标题      : 添加端口号_
预期结果          : 添加PCUI口成功
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_009)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_PCUI;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_AddUsedClientId2Tab(usClientId);

    EXPECT_EQ(1, pstPortBuffCfg->ucNum);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_010
测试用例标题      : 添加端口号_
预期结果          : 再次添加端口成功
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_010)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_CTRL;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_AddUsedClientId2Tab(usClientId);

    EXPECT_EQ(2, pstPortBuffCfg->ucNum);
    EXPECT_EQ(AT_CLIENT_ID_CTRL, pstPortBuffCfg->ulUsedClientID[1]);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_011
测试用例标题      :  删除端口号_
预期结果          : 当前需要删除的端口号没有记录过
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_011)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_CTRL;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM + 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_RmUsedClientIdFromTab(usClientId);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_012
测试用例标题      :  删除端口号_
预期结果          : 删除端口号成功
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_012)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_PCUI;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_RmUsedClientIdFromTab(usClientId);

    EXPECT_EQ(0,pstPortBuffCfg->ucNum);
    EXPECT_EQ(0xFFFFFFFF,pstPortBuffCfg->ulUsedClientID[0]);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_013
测试用例标题      :  删除端口号_
预期结果          : 需要删除的端口号不存在
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_013)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_CTRL;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_RmUsedClientIdFromTab(usClientId);

    EXPECT_EQ(1,pstPortBuffCfg->ucNum);
    EXPECT_EQ(AT_CLIENT_ID_PCUI,pstPortBuffCfg->ulUsedClientID[0]);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_PORT_BUFF_CFG_014
测试用例标题      :  删除端口号_
预期结果          : 批量添加删除端口号成功
修改历史          :
1.日   期  : 2014-01-07
作   者  : j00174725
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_014)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_CTRL;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    for (usClientId = 0; usClientId < AT_MAX_CLIENT_NUM; usClientId++)
    {
        AT_AddUsedClientId2Tab(usClientId);
    }

    EXPECT_EQ(AT_CLIENT_ID_PCUI,pstPortBuffCfg->ulUsedClientID[0]);
    EXPECT_EQ(AT_CLIENT_ID_CTRL,pstPortBuffCfg->ulUsedClientID[1]);
    EXPECT_EQ(AT_CLIENT_ID_MODEM,pstPortBuffCfg->ulUsedClientID[2]);
    EXPECT_EQ(AT_CLIENT_ID_NDIS,pstPortBuffCfg->ulUsedClientID[3]);
    EXPECT_EQ(AT_CLIENT_ID_UART,pstPortBuffCfg->ulUsedClientID[4]);

    for (usClientId = 0; usClientId < AT_MAX_CLIENT_NUM; usClientId++)
    {
        AT_RmUsedClientIdFromTab(usClientId);
    }

    EXPECT_EQ(0,pstPortBuffCfg->ucNum);
    EXPECT_EQ(0xFFFFFFFF,pstPortBuffCfg->ulUsedClientID[0]);

    GlobalMockObject::verify();
}
