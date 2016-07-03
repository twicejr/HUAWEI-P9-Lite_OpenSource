#include "gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsDownLink.h"

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




class Test_ADS_DL_RegDlDataCallback: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
    }
    void TearDown()
    {

    }

protected:

};


TEST_F(Test_ADS_DL_RegDlDataCallback,Test_ADS_DL_RegDlDataCallback_001)
{
    ADS_DL_CTX_STRU                    *pstDlCtx;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;

    pstDlCtx = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 发送ID_APS_ADS_PDP_STATUS_IND消息 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ADS_DL_RegDlDataCallback(1,VOS_NULL_PTR);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(VOS_NULL_PTR, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_RegDlDataCallback,Test_ADS_DL_RegDlDataCallback_002)
{
    VOS_UINT8                           ucRabId;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;

    pstDlCtx = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);
    ucRabId  = 5;

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = ucRabId;

    /* 发送ID_APS_ADS_PDP_STATUS_IND消息 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 注册下行接收函数 */
    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(ucRabId, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_RegDlDataCallback,Test_ADS_DL_RegDlDataCallback_003)
{
	ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_DL_CTX_STRU                    *pstDlCtx;

    pstDlCtx     = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);
    pAdsUlCtx    = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);
	ucRabId                             = 5;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

	stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
	ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(5, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    /* 构造数据 */
    ucRabId = 5;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 销毁RabId为5的队列 */
	stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

	stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
	ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pstDlCtx->astAdsDlRabInfo[0].ucRabId , ADS_RAB_ID_INVALID);

	ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_RegDlDataCallback,Test_ADS_DL_RegDlDataCallback_004)
{
    VOS_UINT8                           ucRabId;
    ADS_DL_CTX_STRU                    *pstDlCtx;

    pstDlCtx = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(5, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)


TEST_F(Test_ADS_DL_RegDlDataCallback,Test_ADS_DL_RegDlDataCallback_011)
{
    ADS_DL_CTX_STRU                    *pstDlCtx;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;

    pstDlCtx = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 发送ID_APS_ADS_PDP_STATUS_IND消息 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ADS_DL_RegDlDataCallback(0x11,VOS_NULL_PTR);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(VOS_NULL_PTR, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_RegDlDataCallback,Test_ADS_DL_RegDlDataCallback_012)
{
    VOS_UINT8                           ucRabId;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;

    pstDlCtx = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);
    ucRabId  = 5;

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = ucRabId;

    /* 发送ID_APS_ADS_PDP_STATUS_IND消息 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 注册下行接收函数 */
    ADS_DL_RegDlDataCallback(0x45, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x5, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_RegDlDataCallback,Test_ADS_DL_RegDlDataCallback_013)
{
	ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_DL_CTX_STRU                    *pstDlCtx;

    pstDlCtx     = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);
    pAdsUlCtx    = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);
	ucRabId                             = 5;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ADS_DL_RegDlDataCallback(0x45, (RCV_DL_DATA_FUNC)TestCallBack);

	stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
	ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(5, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    /* 构造数据 */
    ucRabId = 5;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 销毁RabId为5的队列 */
	stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

	stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
	ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pstDlCtx->astAdsDlRabInfo[0].ucRabId , ADS_RAB_ID_INVALID);

	ADS_DL_RegDlDataCallback(0x45, (RCV_DL_DATA_FUNC)TestCallBack);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_RegDlDataCallback,Test_ADS_DL_RegDlDataCallback_014)
{
    VOS_UINT8                           ucRabId;
    ADS_DL_CTX_STRU                    *pstDlCtx;

    pstDlCtx = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);

    ucRabId                             = 0x45;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(5, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif

class Test_ADS_DL_RcvTafPdpStatusInd: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上下行上下文初始化*/
        ADS_InitCtx();

        PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

        /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
        stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
        stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;
        stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd.ucRabId       = 0x05;

    }
    void TearDown()
    {

    }
protected:

    ADS_DL_CTX_STRU     *pstDlCtx;

    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
};


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_001)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    /* 输入码流配置*/
    stPdpStatusInd.enModemId            = MODEM_ID_0;
    stPdpStatusInd.enPdpStatus          = ADS_PDP_STATUS_BUTT;
    /* 场景配置 */

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_RAB_ID_INVALID, pstDlCtx->astAdsDlRabInfo[0].ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_002)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    /* 输入码流配置*/
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x04;
    /* 场景配置 */

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_RAB_ID_INVALID, pstDlCtx->astAdsDlRabInfo[0].ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_003)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    stPdpStatusInd.enModemId            = MODEM_ID_0;
    stPdpStatusInd.enPdpType            = ADS_PDP_IPV4;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(ADS_CDS_IPF_PKT_TYPE_IP, pstDlCtx->astAdsDlRabInfo[0].enPktType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_004)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    /* 输入码流配置*/
    stPdpStatusInd.enModemId            = MODEM_ID_0;
    stPdpStatusInd.enPdpStatus          = ADS_PDP_STATUS_DEACT;
    /* 场景配置 */
    pstDlCtx->astAdsDlRabInfo[0].ucRabId = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_RAB_ID_INVALID, pstDlCtx->astAdsDlRabInfo[0].ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_005)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    stPdpStatusInd.enModemId            = MODEM_ID_0;
    stPdpStatusInd.enPdpType            = ADS_PDP_PPP;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(ADS_CDS_IPF_PKT_TYPE_PPP, pstDlCtx->astAdsDlRabInfo[0].enPktType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_011)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);

    /* 输入码流配置*/
    stPdpStatusInd.ulSenderPid          = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId            = MODEM_ID_1;
    stPdpStatusInd.enPdpStatus          = ADS_PDP_STATUS_BUTT;
    /* 场景配置 */

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_RAB_ID_INVALID, pstDlCtx->astAdsDlRabInfo[0].ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_012)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);

    /* 输入码流配置*/
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x04;
    /* 场景配置 */

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_RAB_ID_INVALID, pstDlCtx->astAdsDlRabInfo[0].ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_013)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);

    stPdpStatusInd.ulSenderPid          = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId            = MODEM_ID_1;
    stPdpStatusInd.enPdpType            = ADS_PDP_IPV4;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(ADS_CDS_IPF_PKT_TYPE_IP, pstDlCtx->astAdsDlRabInfo[0].enPktType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_014)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);

    /* 输入码流配置*/
    stPdpStatusInd.ulSenderPid          = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId            = MODEM_ID_1;
    stPdpStatusInd.enPdpStatus          = ADS_PDP_STATUS_DEACT;
    /* 场景配置 */
    pstDlCtx->astAdsDlRabInfo[0].ucRabId = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_RAB_ID_INVALID, pstDlCtx->astAdsDlRabInfo[0].ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RcvTafPdpStatusInd,Test_ADS_DL_RcvTafPdpStatusInd_015)
{
    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);

    stPdpStatusInd.ulSenderPid          = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId            = MODEM_ID_1;
    stPdpStatusInd.enPdpType            = ADS_PDP_PPP;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(ADS_CDS_IPF_PKT_TYPE_PPP, pstDlCtx->astAdsDlRabInfo[0].enPktType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

class Test_ADS_DL_RcvIpfData: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        /*上下行上下文初始化*/
        pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);
    }
    void TearDown()
    {

    }

protected:

    ADS_DL_CTX_STRU                    *pstDlCtx;
};
#if 0

class Test_ADS_DL_ProcIpfResult: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上下行上下文初始化*/
        ADS_InitCtx();
        pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

		ADS_InitStatsInfoCtx(ADS_INSTANCE_INDEX_0);
    }
    void TearDown()
    {

    }

protected :
    ADS_DL_CTX_STRU                    *pstDlCtx;

    IPF_RD_DESC_S                      stRd;
};
#if(FEATURE_OFF == FEATURE_SKB_EXP)

TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_001)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
   	ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

	pAdsStatsInfoCtx     = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;
    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0213;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .with(any(), any(),any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));


    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

	EXPECT_EQ(10, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_002)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
   	ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_CHAR                           *pstZcPutData = VOS_NULL_PTR;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

	pAdsStatsInfoCtx     = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

	pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes = 10;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0205;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = ADS_MTU_LEN_MAX + 1;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

	EXPECT_EQ(ADS_MTU_LEN_MAX + 11, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_003)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x023F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_004)
{
    VOS_UINT8                              ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_CHAR                           *pstZcPutData = VOS_NULL_PTR;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(VOS_NULL_PTR, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x023F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_006)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0214;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(TestCallBack)
        .expects(never());

    /* 释放C核内存 */
    //MOCKER(kfree_skb)
   //     .expects(exactly(1));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_007)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0200;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_008)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0210;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_009)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0205;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));


    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_010)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x423F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_011)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x223F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_013)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0a3F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_014)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x043F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_015)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;
    stPdpStatusInd.enPdpType     = ADS_PDP_PPP;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x043F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_016)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_CHAR                           *pstZcPutData = VOS_NULL_PTR;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(VOS_NULL_PTR, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
        ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x023F;
    pstRd->u16UsrField1 = 0x15;
    pstRd->u16PktLen    = 10;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#else

TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_021)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
   	ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    VOS_UINT8                          *pData;

	pAdsStatsInfoCtx     = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;
    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pData = (VOS_UINT8 *)malloc(pstRd->u16PktLen);

    pstRd->u16Result    = 0x0213;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;
    pstRd->u32OutPtr = (VOS_UINT_PTR)pData;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .with(any(), any(),eq(ACPU_PID_ADS_DL));

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(IMM_RbRemoteFreeMem).expects(exactly(1));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

	EXPECT_EQ(100, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    free(pData);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_022)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
   	ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    TTF_MEM_ST                         *pstTtfMem;

    pstTtfMem = (TTF_MEM_ST*)malloc(sizeof(TTF_MEM_ST));

    pstTtfMem->usUsed = 10;

    pstTtfMem->pData = (unsigned char *)malloc(pstTtfMem->usUsed);

	pAdsStatsInfoCtx     = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

	pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes = 10;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0205;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = ADS_MTU_LEN_MAX + 1;
    pstRd->u32UsrField2 = (VOS_UINT_PTR)pstTtfMem;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

	EXPECT_EQ(ADS_MTU_LEN_MAX + 11, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    free(pstTtfMem->pData);

    free(pstTtfMem);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_023)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x023F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;
    pstRd->u32OutPtr    = (VOS_UINT32)malloc(pstRd->u16PktLen);

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

	free((VOS_VOID *)(pstRd->u32OutPtr));
    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_024)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ(VOS_NULL_PTR, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x023F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;
    pstRd->u32OutPtr    = (VOS_UINT32)malloc(pstRd->u16PktLen);

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(kfree_skb)
        .expects(exactly(1));

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_026)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0214;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;

    MOCKER(mdrv_ipf_get_dlrd)
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    /* 释放C核内存 */
    MOCKER(IMM_RbRemoteFreeMem)
        .expects(exactly(1));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_027)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0200;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;

    MOCKER(mdrv_ipf_get_dlrd)
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    /* 释放C核内存 */
    MOCKER(IMM_RbRemoteFreeMem)
        .expects(exactly(1));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_028)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0210;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    /* 释放C核内存 */
    MOCKER(IMM_RbRemoteFreeMem)
        .expects(exactly(1));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_029)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0205;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    /* VOS_SendMsg 发送ID_ADS_NDCLIENT_ERR_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    /* 释放C核内存 */
    MOCKER(IMM_RbRemoteFreeMem)
        .expects(exactly(1));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_030)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x423F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_031)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x223F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_033)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0a3F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_034)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x043F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_035)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
	ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));
    PS_MEM_SET(&stFilterIpAddr, 0x00, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);
    ADS_DL_RegFilterDataCallback(ucRabId, &stFilterIpAddr, VOS_NULL_PTR);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);
    EXPECT_EQ(VOS_NULL_PTR, pstDlCtx->astAdsDlRabInfo[0].pRcvDlFilterDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x023F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;
    pstRd->u32OutPtr    = (VOS_UINT32)malloc(pstRd->u16PktLen);

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_FILTER_ProcDlPacket)
        .expects(never());

    MOCKER(TestFilterCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_036)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
	ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));
    PS_MEM_SET(&stFilterIpAddr, 0x00, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);
    ADS_DL_RegFilterDataCallback(ucRabId, &stFilterIpAddr, (RCV_DL_DATA_FUNC)TestFilterCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestFilterCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlFilterDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x023F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;
    pstRd->u32OutPtr    = (VOS_UINT32)malloc(pstRd->u16PktLen);

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(exactly(1));

    MOCKER(ADS_FILTER_ProcDlPacket)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(TestFilterCallBack)
        .expects(never());

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfResult,Test_ADS_DL_ProcIpfResult_037)
{
    VOS_UINT8                           ucRabId;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_DL_CTX_STRU                    *pstDlCtx;
    BSP_U32                             ulRdNum;
    IPF_RD_DESC_S                      *pstRd;
	ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;

    pstDlCtx             = ADS_GetDlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));
    PS_MEM_SET(&stFilterIpAddr, 0x00, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_DL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 测试函数调用 */
    ADS_DL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* RabId5注册下行数据处理函数 */
    ucRabId                             = 5;

    ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)TestCallBack);
    ADS_DL_RegFilterDataCallback(ucRabId, &stFilterIpAddr, (RCV_DL_DATA_FUNC)TestFilterCallBack);

    EXPECT_EQ(0x05, pstDlCtx->astAdsDlRabInfo[0].ucRabId);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlDataFunc);
    EXPECT_EQ((RCV_DL_DATA_FUNC)TestFilterCallBack, pstDlCtx->astAdsDlRabInfo[0].pRcvDlFilterDataFunc);

    ulRdNum = 1;

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
                                          ulRdNum * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x023F;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 100;
    pstRd->u32OutPtr    = (VOS_UINT32)malloc(pstRd->u16PktLen);

    MOCKER(mdrv_ipf_get_dlrd)
        .stubs()
        .with(outBoundP((BSP_U32 *)&ulRdNum), outBoundP(pstRd,sizeof(IPF_RD_DESC_S)));

    MOCKER(TestCallBack)
        .expects(never());

    MOCKER(ADS_FILTER_ProcDlPacket)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TestFilterCallBack)
        .expects(exactly(1));

    MOCKER(ADS_DL_IsFcAssemTuneNeeded)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ADS_DL_ProcIpfResult();

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif
#endif

class Test_ADS_DL_IpfIntCB: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
    }
    void TearDown()
    {

    }

protected:

};


TEST_F(Test_ADS_DL_IpfIntCB,Test_ADS_DL_IpfIntCB_001)
{
    g_ulAdsDLTaskReadyFlag = 1;

    MOCKER(VOS_EventWrite).expects(exactly(1)).will(returnValue((VOS_UINT32)0));

    ADS_DL_IpfIntCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_ADS_DL_RcvTiProtectExpired: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
    }
    void TearDown()
    {

    }

protected:

};


TEST_F(Test_ADS_DL_RcvTiProtectExpired,Test_ADS_DL_RcvTiProtectExpired_001)
{
    g_ulAdsDLTaskReadyFlag = 1;

    MOCKER(mdrv_ipf_get_dlrd_num)
        .stubs()
        .will(returnValue(1));

    MOCKER(VOS_EventWrite)
        .expects(exactly(1))
        .with(any(), eq(ADS_DL_EVENT_IPF_RD_INT))
        .will(returnValue((VOS_UINT32)0));

    MOCKER(V_StartCallBackRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ADS_DL_RcvTiProtectExpired(0, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_OFF == FEATURE_SKB_EXP)


class Test_ADS_DL_ProcAdq: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
    }
    void TearDown()
    {

    }

protected:

};


TEST_F(Test_ADS_DL_ProcAdq,Test_ADS_DL_ProcAdq_001)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;
    VOS_UINT8                           i;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 63;
    ulIpfAd1Num = 63;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .will(returnValue(IPF_ERROR));

    MOCKER(mdrv_ipf_config_dlad)
        .expects(never());

    ADS_DL_ProcAdq();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_ADS_DL_IpfAdqEmptyCB: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
    }
    void TearDown()
    {

    }

protected:

};


TEST_F(Test_ADS_DL_IpfAdqEmptyCB,Test_ADS_DL_IpfAdqEmptyCB_001)
{
    g_ulAdsDLTaskReadyFlag = 1;

    MOCKER(VOS_EventWrite).expects(exactly(1)).will(returnValue((VOS_UINT32)0));

    ADS_DL_IpfAdqEmptyCB(IPF_EMPTY_ADQ0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_ADS_DL_ProcIpfAdqEmtpyEvent: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
	
	    MOCKER(V_StartCallBackRelTimer)
	        .defaults()
	        .will(returnValue((VOS_UINT32)VOS_OK));

        ADS_InitCtx();
    }
    void TearDown()
    {

    }

protected:

};


TEST_F(Test_ADS_DL_ProcIpfAdqEmtpyEvent,Test_ADS_DL_ProcIpfAdqEmtpyEvent_001)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 61;
    ulIpfAd1Num = 5;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(IMM_ZcStaticAlloc_Debug)
        .stubs()
        .will(returnValue((IMM_ZC_STRU *)VOS_NULL_PTR));

    ADS_DL_ProcIpfAdqEmtpyEvent();

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, ADS_GetTimerStatus(ACPU_PID_ADS_UL,TI_ADS_DL_ADQ_EMPTY));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfAdqEmtpyEvent,Test_ADS_DL_ProcIpfAdqEmtpyEvent_002)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 5;
    ulIpfAd1Num = 61;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(IMM_ZcStaticAlloc_Debug)
        .stubs()
        .will(returnValue((IMM_ZC_STRU *)VOS_NULL_PTR));

    ADS_DL_ProcIpfAdqEmtpyEvent();

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, ADS_GetTimerStatus(ACPU_PID_ADS_UL,TI_ADS_DL_ADQ_EMPTY));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfAdqEmtpyEvent,Test_ADS_DL_ProcIpfAdqEmtpyEvent_003)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 61;
    ulIpfAd1Num = 61;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(IMM_ZcStaticAlloc_Debug)
        .stubs()
        .will(returnValue((IMM_ZC_STRU *)VOS_NULL_PTR));

    ADS_DL_ProcIpfAdqEmtpyEvent();

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, ADS_GetTimerStatus(ACPU_PID_ADS_UL,TI_ADS_DL_ADQ_EMPTY));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_ProcIpfAdqEmtpyEvent,Test_ADS_DL_ProcIpfAdqEmtpyEvent_004)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 63;
    ulIpfAd1Num = 63;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .will(returnValue(IPF_ERROR));

    MOCKER(IMM_ZcStaticAlloc_Debug).expects(never());

    ADS_DL_ProcIpfAdqEmtpyEvent();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if 0

TEST_F(Test_ADS_DL_ProcIpfAdqEmtpyEvent,Test_ADS_DL_ProcIpfAdqEmtpyEvent_005)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
     ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 61;
    ulIpfAd1Num = 5;

    MOCKER(mdrv_ipf_get_dlad_num)
        .expects(exactly(1))
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(IMM_ZcStaticAlloc_Debug)
        .stubs()
        .will(returnValue((IMM_ZC_STRU *)VOS_NULL_PTR));

    ADS_DL_ProcIpfAdqEmtpyEvent();

    /* 需要清除之前的mocker桩 */
    GlobalMockObject::verify();
    UT_STUB_INIT();
    UT_IMM_STUB_INIT();

    ulIpfAd0Num = 61;
    ulIpfAd1Num = 61;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    ADS_DL_ProcIpfAdqEmtpyEvent();

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, ADS_GetTimerStatus(ACPU_PID_ADS_UL,TI_ADS_DL_ADQ_EMPTY));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

TEST_F(Test_ADS_DL_ProcIpfAdqEmtpyEvent,Test_ADS_DL_ProcIpfAdqEmtpyEvent_006)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;
    VOS_UINT8                           i;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 63;
    ulIpfAd1Num = 63;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(mdrv_ipf_config_dlad)
        .expects(exactly(1))
        .with(eq(IPF_AD_0), eq(ulIpfAd0Num))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(mdrv_ipf_config_dlad)
        .expects(exactly(1))
        .with(eq(IPF_AD_1), eq(ulIpfAd1Num))
        .will(returnValue(IPF_SUCCESS));

    ADS_DL_ProcIpfAdqEmtpyEvent();

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, ADS_GetTimerStatus(ACPU_PID_ADS_UL,TI_ADS_DL_ADQ_EMPTY));
#if 0
    /* 配置失败，释放内存 */
    for (i = 0; i < ulIpfAd0Num; i++)
    {
        IMM_ZcFree((IMM_ZC_STRU *)ADS_DL_GET_IPF_AD_BUFFER_PTR(IPF_AD_0, i)->u32OutPtr1);
        IMM_ZcFree((IMM_ZC_STRU *)ADS_DL_GET_IPF_AD_BUFFER_PTR(IPF_AD_1, i)->u32OutPtr1);
    }
#endif
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if 0

TEST_F(Test_ADS_DL_ProcIpfAdqEmtpyEvent,Test_ADS_DL_ProcIpfAdqEmtpyEvent_007)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;
    VOS_UINT8                           i;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 61;
    ulIpfAd1Num = 61;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(mdrv_ipf_config_dlad)
        .expects(exactly(1))
        .with(eq(IPF_AD_0), eq(ulIpfAd0Num))
        .will(returnValue(IPF_ERROR));

    MOCKER(mdrv_ipf_config_dlad)
        .expects(exactly(1))
        .with(eq(IPF_AD_1), eq(ulIpfAd1Num))
        .will(returnValue(IPF_ERROR));

    ADS_DL_ProcIpfAdqEmtpyEvent();

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, ADS_GetTimerStatus(ACPU_PID_ADS_UL,TI_ADS_DL_ADQ_EMPTY));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

TEST_F(Test_ADS_DL_ProcIpfAdqEmtpyEvent,Test_ADS_DL_ProcIpfAdqEmtpyEvent_008)
{
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;
    VOS_UINT8                           i;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    ulIpfAd0Num = 63;
    ulIpfAd1Num = 63;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .will(returnValue(IPF_ERROR));

    MOCKER(mdrv_ipf_config_dlad)
        .expects(never());

    ADS_DL_ProcIpfAdqEmtpyEvent();


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

class Test_ADS_DL_RcvTiAdqEmptyExpired: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
    }
    void TearDown()
    {

    }

protected:

};


TEST_F(Test_ADS_DL_RcvTiAdqEmptyExpired,Test_ADS_DL_RcvTiAdqEmptyExpired_001)
{
    g_ulAdsDLTaskReadyFlag = 1;

    MOCKER(VOS_EventWrite)
        .expects(exactly(1))
        .with(any(), eq(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT))
        .will(returnValue((VOS_UINT32)0));

    ADS_DL_RcvTiAdqEmptyExpired(0, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#if 0

class Test_ADS_DL_SendNdClientDataInd: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
    }
    void TearDown()
    {

    }

protected:

};

#if (FEATURE_OFF == FEATURE_SKB_EXP)

TEST_F(Test_ADS_DL_SendNdClientDataInd,Test_ADS_DL_SendNdClientDataInd_001)
{
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
        1 * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0213;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 5;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    ADS_DL_SendNdClientDataInd(pstRd);

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    IMM_ZcFree(pstImmZc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_SendNdClientDataInd,Test_ADS_DL_SendNdClientDataInd_002)
{
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
        1 * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0213;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 5;
    pstRd->u32OutPtr    = (VOS_UINT_PTR)pstImmZc;

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ADS_DL_SendNdClientDataInd(pstRd);

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    IMM_ZcFree(pstImmZc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#else

TEST_F(Test_ADS_DL_SendNdClientDataInd,Test_ADS_DL_SendNdClientDataInd_003)
{
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
        1 * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0213;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 5;
    pstRd->u32OutPtr    = (VOS_UINT32)malloc(5);

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)VOS_NULL_PTR));

    MOCKER(Ps_SendMsg).expects(never());

    ADS_DL_SendNdClientDataInd(pstRd);

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    IMM_ZcFree(pstImmZc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_SendNdClientDataInd,Test_ADS_DL_SendNdClientDataInd_004)
{
    IPF_RD_DESC_S                      *pstRd;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_CHAR                           *pstZcPutData;

    pstImmZc = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(5);

    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstImmZc, 5);

    pstRd = (IPF_RD_DESC_S *)PS_MEM_ALLOC(ACPU_PID_ADS_DL,
        1 * sizeof(IPF_RD_DESC_S));

    pstRd->u16Result    = 0x0213;
    pstRd->u16UsrField1 = 5;
    pstRd->u16PktLen    = 5;
    pstRd->u32OutPtr    = (VOS_UINT32)malloc(5);

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ADS_DL_SendNdClientDataInd(pstRd);

    PS_MEM_FREE(ACPU_PID_ADS_DL,pstRd);

    IMM_ZcFree(pstImmZc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
#endif


#if (FEATURE_OFF == FEATURE_SKB_EXP)

class Test_ADS_DL_RcvCcpuResetStartInd: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
    }
    void TearDown()
    {
    }
};


TEST_F(Test_ADS_DL_RcvCcpuResetStartInd, Test_ADS_DL_RcvCcpuResetStartInd_001)
{
    ADS_CCPU_RESET_IND_STRU                  stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(ADS_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_ADS_DL;
    stResetInd.ulReceiverPid   = ACPU_PID_ADS_DL;
    stResetInd.enMsgId         = ID_ADS_CCPU_RESET_START_IND;

    /* 桩函数 */
    MOCKER(ADS_GetDLResetSem)
        .expects(exactly(1))
        .will(returnValue(VOS_SEM(0)));

    MOCKER(ADS_DL_ProcIpfResult)
        .times(1);

    MOCKER(mdrv_ipf_get_used_dlad)
        .expects(exactly(1))
        .with(eq(IPF_AD_1), any(), any())
        .will(returnValue(IPF_SUCCESS));

    MOCKER(mdrv_ipf_get_used_dlad)
        .expects(exactly(1))
        .with(eq(IPF_AD_0), any(), any())
        .will(returnValue(IPF_SUCCESS));

    MOCKER(VOS_SmV)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 函数调用 */

    /* 调用入口函数 */
    ADS_DL_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#if 0

class Test_ADS_DL_RcvAdsDlMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();
    }
    void TearDown()
    {
    }
};


TEST_F(Test_ADS_DL_RcvAdsDlMsg, Test_ADS_DL_RcvAdsDlMsg_001)
{
    ADS_CCPU_RESET_IND_STRU                  stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(ADS_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_ADS_DL;
    stResetInd.ulReceiverPid   = ACPU_PID_ADS_DL;
    stResetInd.enMsgId         = ID_ADS_CCPU_RESET_END_IND;

    /* 桩函数 */
    MOCKER(ADS_GetDLResetSem)
        .expects(never());

    MOCKER(mdrv_ipf_reinit_dlreg)
        .expects(exactly(1));

    /* 函数调用 */

    /* 调用入口函数 */
    ADS_DL_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_DL_RcvAdsDlMsg, Test_ADS_DL_RcvAdsDlMsg_002)
{
    ADS_CCPU_RESET_IND_STRU                  stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(ADS_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_ADS_DL;
    stResetInd.ulReceiverPid   = ACPU_PID_ADS_DL;
    stResetInd.enMsgId         = ID_ADS_MSG_ID_ENUM_BUTT;

    /* 桩函数 */
    MOCKER(ADS_GetDLResetSem)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    ADS_DL_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#endif
#endif


class Test_ADS_DL_RegFilterDataCallback: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

		ADS_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_DL_RegFilterDataCallback, Test_ADS_DL_RegFilterDataCallback_001)
{
    // 变量声明
    VOS_UINT8                           ucRabId;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;
	VOS_UINT32							ulRet;

    // 参数初始化
	ucRabId = 16;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
	ulRet = ADS_DL_RegFilterDataCallback(ucRabId, &stFilterIpAddr, (RCV_DL_DATA_FUNC)TestFilterCallBack);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_RegFilterDataCallback, Test_ADS_DL_RegFilterDataCallback_002)
{
    // 变量声明
    VOS_UINT8                           ucRabId;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;
	VOS_UINT32							ulRet;

    // 参数初始化
	ucRabId = 5;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
	ulRet = ADS_DL_RegFilterDataCallback(ucRabId, &stFilterIpAddr, (RCV_DL_DATA_FUNC)TestFilterCallBack);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


class Test_ADS_DL_DeregFilterDataCallback: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

		ADS_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_DL_DeregFilterDataCallback, Test_ADS_DL_DeregFilterDataCallback_001)
{
    // 变量声明
    VOS_UINT8                           ucRabId;
	VOS_UINT32							ulRet;

    // 参数初始化
	ucRabId = 16;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
	ulRet = ADS_DL_DeregFilterDataCallback(ucRabId);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_DeregFilterDataCallback, Test_ADS_DL_DeregFilterDataCallback_002)
{
    // 变量声明
    VOS_UINT8                           ucRabId;
	VOS_UINT32							ulRet;

	// 参数初始化
	ucRabId = 5;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
	ulRet = ADS_DL_DeregFilterDataCallback(ucRabId);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}

