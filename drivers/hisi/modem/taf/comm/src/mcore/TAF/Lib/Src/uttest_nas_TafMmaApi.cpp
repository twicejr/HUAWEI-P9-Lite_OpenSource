#include "gtest/gtest.h"
#include "llt_mockcpp.h"


#include "uttest_nas_TafMmaApi.h"


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


class Test_TAF_MMA_PlmnPlmnUserSelSetReq: public ::testing::Test
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

TEST_F(Test_TAF_MMA_PlmnPlmnUserSelSetReq,Test_TAF_MMA_PlmnPlmnUserSelSetReq_001)
{
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    TAF_PLMN_USER_SEL_STRU              stPlmnUserSel;
    VOS_UINT32                          ulReslut;

    stPlmnUserSel.enAccessMode = TAF_PH_RA_GSM;
    stPlmnUserSel.ucFormatType = AT_COPS_NUMERIC_TYPE;
    stPlmnUserSel.usOperNameLen = 0;
    ClientId             = 0;
    OpId                 = 0;

    ulReslut = TAF_MMA_PlmnSpecialSelReq(ClientId, OpId, &stPlmnUserSel);
    EXPECT_EQ(VOS_TRUE, ulReslut);


    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_PlmnPlmnUserSelSetReq,Test_TAF_MMA_PlmnPlmnUserSelSetReq_002)
{
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    TAF_PLMN_USER_SEL_STRU              stPlmnUserSel;

    stPlmnUserSel.enAccessMode = TAF_PH_RA_GSM;
    stPlmnUserSel.ucFormatType = AT_COPS_NUMERIC_TYPE;
    stPlmnUserSel.usOperNameLen = 0;
    ClientId             = 0;
    OpId                 = 0;

    /* MOCKER操作 */
    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_APS_FAIL));

    EXPECT_EQ(VOS_FALSE, TAF_MMA_PlmnSpecialSelReq(ClientId, OpId, &stPlmnUserSel));


    GlobalMockObject::verify();
}


class Test_TAF_MMA_PhoneModeSetReq: public ::testing::Test
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


TEST_F(Test_TAF_MMA_PhoneModeSetReq,Test_TAF_MMA_PhoneModeSetReq_001)
{

    /* MOCKER操作 */

    /* 调用被测函数  */
    TAF_MMA_PhoneModeSetReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);

    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_PhoneModeSetReq,Test_TAF_MMA_PhoneModeSetReq_002)
{

    // 变量声明
    TAF_MMA_PHONE_MODE_PARA_STRU            stPhoneModePara;

    // 参数初始化
    PS_MEM_SET(&stPhoneModePara, 0, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));

    stPhoneModePara.PhMode  = TAF_PH_MODE_FULL;
    stPhoneModePara.PhReset = TAF_PH_OP_MODE_UNRESET;

    /* MOCKER操作 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* 调用被测函数  */
    TAF_MMA_PhoneModeSetReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stPhoneModePara);


    GlobalMockObject::verify();
}



class Test_TAF_MMA_SetSysCfgReq: public ::testing::Test
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


TEST_F(Test_TAF_MMA_SetSysCfgReq,Test_TAF_MMA_SetSysCfgReq_001)
{

    /* MOCKER操作 */

    /* 调用被测函数  */
    TAF_MMA_SetSysCfgReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);

    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_SetSysCfgReq,Test_TAF_MMA_SetSysCfgReq_002)
{
    // 变量声明
    TAF_MMA_SYS_CFG_PARA_STRU            stSysCfgPara;

    // 参数初始化
    // 参数初始化
    PS_MEM_SET(&stSysCfgPara, 0, sizeof(TAF_MMA_SYS_CFG_PARA_STRU));

    stSysCfgPara.enRoam                    = TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON;
    stSysCfgPara.enSrvDomain               = TAF_MMA_SERVICE_DOMAIN_PS;
    stSysCfgPara.enUserPrio                = TAF_MMA_USER_SET_PRIO_NOCHANGE;
    stSysCfgPara.stRatOrder.ucRatOrderNum  = 1;
    stSysCfgPara.stRatOrder.aenRatOrder[0] = TAF_MMA_RAT_LTE;

    /* MOCKER操作 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* 调用被测函数  */
    TAF_MMA_SetSysCfgReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stSysCfgPara);


    GlobalMockObject::verify();
}



class Test_TAF_MMA_AcqBestNetworkReq: public ::testing::Test
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


TEST_F(Test_TAF_MMA_AcqBestNetworkReq,Test_TAF_MMA_AcqBestNetworkReq_001)
{

    /* MOCKER操作 */

    /* 调用被测函数  */
    TAF_MMA_AcqBestNetworkReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);

    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_AcqBestNetworkReq,Test_TAF_MMA_AcqBestNetworkReq_002)
{

    // 变量声明
    TAF_MMA_ACQ_PARA_STRU               stAcqPara;

    // 参数初始化
    // 参数初始化
    PS_MEM_SET(&stAcqPara, 0, sizeof(TAF_MMA_ACQ_PARA_STRU));

    stAcqPara.enAcqReason      = TAF_MMA_ACQ_REASON_POWER_UP;

    /* MOCKER操作 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* 调用被测函数  */
    TAF_MMA_AcqBestNetworkReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stAcqPara);

    GlobalMockObject::verify();
}


class Test_TAF_MMA_RegReq: public ::testing::Test
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


TEST_F(Test_TAF_MMA_RegReq,Test_TAF_MMA_RegReq_001)
{

    /* MOCKER操作 */

    /* 调用被测函数  */
    TAF_MMA_RegReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);


    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_RegReq,Test_TAF_MMA_RegReq_002)
{

    // 变量声明
    TAF_MMA_REG_PARA_STRU               stRegPara;

    // 参数初始化
    PS_MEM_SET(&stRegPara, 0, sizeof(TAF_MMA_REG_PARA_STRU));

    stRegPara.bitOpPrioClass      = 1;

    /* MOCKER操作 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* 调用被测函数  */
    TAF_MMA_RegReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stRegPara);

    GlobalMockObject::verify();
}


class Test_TAF_MMA_PowerSaveReq: public ::testing::Test
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


TEST_F(Test_TAF_MMA_PowerSaveReq, Test_TAF_MMA_PowerSaveReq_001)
{

    /* MOCKER操作 */
    MOCKER(Ps_SendMsg)
        .expects(never());

    /* 调用函数，给NULL参数 */
    TAF_MMA_PowerSaveReq(0, 0, 0, NULL);

    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_PowerSaveReq, Test_TAF_MMA_PowerSaveReq_002)
{
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;

    /* MOCKER操作 */
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    /* 调用被测函数  */
    TAF_MMA_PowerSaveReq(0, 0, 0, &stPowerSavePara);

    GlobalMockObject::reset();
    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_PowerSaveReq, Test_TAF_MMA_PowerSaveReq_003)
{
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;

    PS_MEM_SET(&stPowerSavePara, 0, sizeof(TAF_MMA_POWER_SAVE_PARA_STRU));

    /* MOCKER操作 */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* 调用被测函数  */
    TAF_MMA_PowerSaveReq(0, 0, 0, &stPowerSavePara);

    GlobalMockObject::verify();
}



class Test_TAF_MMA_DetachReq: public ::testing::Test
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


TEST_F(Test_TAF_MMA_DetachReq,Test_TAF_MMA_DetachReq_001)
{

    /* MOCKER操作 */
    MOCKER(Ps_SendMsg)
        .expects(never());

    /* 调用函数，给NULL参数 */
    TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);


    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_DetachReq,Test_TAF_MMA_DetachReq_002)
{

    TAF_MMA_DETACH_PARA_STRU        stDetachPara;

    PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));

    /* MOCKER操作 */
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    /* 调用被测函数  */
    TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stDetachPara);

    GlobalMockObject::verify();
}


TEST_F(Test_TAF_MMA_DetachReq,Test_TAF_MMA_DetachReq_003)
{

    TAF_MMA_DETACH_PARA_STRU        stDetachPara;

    PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));

    /* MOCKER操作 */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* 调用被测函数  */
    TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stDetachPara);

    GlobalMockObject::verify();
}




