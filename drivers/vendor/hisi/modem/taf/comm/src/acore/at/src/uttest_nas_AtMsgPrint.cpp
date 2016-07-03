#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtMsgPrint.h"


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

#if 0

TEST_F(Test_At_PrintCsmsInfo, 短信相关业务支持选项包括短信发送功能_短信接收功能_广播短信功能)
{
    // 参数定义
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = 0;

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (TAF_UINT8 *)"+CSMS";

    // MOCKER操作;

    // 调用被测函数
    At_PrintCsmsInfo(ucIndex);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_StubSendAutoReplyMsg: public ::testing::Test
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

TEST_F(Test_AT_StubSendAutoReplyMsg, Test_AT_StubSendAutoReplyMsg_01)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    EXPECT_EQ(AT_ERROR, AT_StubSendAutoReplyMsg(0, &stEvent, &stTsDataInfo));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubSendAutoReplyMsg, Test_AT_StubSendAutoReplyMsg_02)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/

    MOCKER(MN_MSG_Encode)
        .stubs()
        .will(returnValue(1));

    EXPECT_EQ(AT_ERROR, AT_StubSendAutoReplyMsg(0, &stEvent, &stTsDataInfo));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubSendAutoReplyMsg, Test_AT_StubSendAutoReplyMsg_03)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/

    MOCKER(MN_MSG_Encode)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    MOCKER(MN_MSG_Send)
        .stubs()
        .will(returnValue((VOS_UINT32)1));

    EXPECT_EQ(AT_ERROR, AT_StubSendAutoReplyMsg(0, &stEvent, &stTsDataInfo));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubSendAutoReplyMsg, Test_AT_StubSendAutoReplyMsg_04)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/

    MOCKER(MN_MSG_Encode)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    MOCKER(MN_MSG_Send)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    EXPECT_EQ(AT_OK, AT_StubSendAutoReplyMsg(0, &stEvent, &stTsDataInfo));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_StubTriggerAutoReply: public ::testing::Test
{
public:
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        ucIndex = 0;

        pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);

        pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;
    }

    void TearDown()
    {
    }

};

TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_01)
{
    TAF_UINT8                           ucCfgValue = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = &stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = &stTsDataInfo;

    MOCKER(V_MemFree)
        .expects(exactly(4))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_02)
{
    TAF_UINT8                           ucCfgValue = 1;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_03)
{
    TAF_UINT8                           ucCfgValue = 1;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)&stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)&stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    MOCKER(V_MemFree)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_04)
{
    TAF_UINT8                           ucCfgValue = 1;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = &stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = &stTsDataInfo;

    MOCKER(V_MemFree)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_05)
{
    TAF_UINT8                           ucCfgValue = 1;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_StubSaveAutoReplyData: public ::testing::Test
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

TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_01)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_02)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    stTsDataInfo.enTpduType = MN_MSG_TPDU_STARPT;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_FALSE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_03)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_TRUE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_04)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;
    MN_MSG_EVENT_INFO_STRU             *pstMsgEventInfo;


    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    pstMsgEventInfo = (MN_MSG_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_MSG_EVENT_INFO_STRU));

    MOCKER(V_MemAlloc)
        .expects(exactly(2))
        .will(returnObjectList((void *)pstMsgEventInfo, (void *)VOS_NULL_PTR));


    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_TRUE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_05)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = &stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_TRUE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_TRUE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_TRUE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_06)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*预置环境：*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = &stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_TRUE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_TRUE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_TRUE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SetAbsoluteValidPeriod: public ::testing::Test
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

TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_01)
{
    TAF_UINT8                           aucPara[] = "\"94/05/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_ABSOLUTE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_02)
{
    TAF_UINT8                           aucPara[] = "\"94/05/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_ERROR, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_03)
{
    TAF_UINT8                           aucPara[] = "\"94/05/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_04)
{
    TAF_UINT8                           aucPara[] = "\"94//05/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_05)
{
    TAF_UINT8                           aucPara[] = "\"14/20/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SetRelativeValidPeriod: public ::testing::Test
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

TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_01)
{
    TAF_UINT8                           aucPara[] = "1235";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_02)
{
    TAF_UINT8                           aucPara[] = "A4//05/06,22:10:00+08";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_NONE;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(167, stValidPeriod.u.ucOtherTime);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_03)
{
    TAF_UINT8                           aucPara[] = "A4//05/06,22:10:00+08";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_ABSOLUTE;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_ERROR, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_04)
{
    TAF_UINT8                           aucPara[] = "abc";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_05)
{
    TAF_UINT8                           aucPara[] = "1234567890123";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_06)
{
    TAF_UINT8                           aucPara[] = "1234";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_07)
{
    TAF_UINT8                           aucPara[] = "123";
    TAF_UINT16                          usParaLen = sizeof(aucPara)-1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(123, stValidPeriod.u.ucOtherTime);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

class Test_At_ParseCsmpVp: public ::testing::Test
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


TEST_F(Test_At_ParseCsmpVp, Test_At_ParseCsmpVp_001)
{
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    gastAtParaList[0].usParaLen = 0;
    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    gastAtParaList[1].usParaLen = sizeof("123") - 1;
    PS_MEM_CPY(gastAtParaList[1].aucPara, "123", gastAtParaList[1].usParaLen);
    ulRet = At_ParseCsmpVp(0,&stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(123, stValidPeriod.u.ucOtherTime);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp, Test_At_ParseCsmpVp_002)
{
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    gastAtParaList[0].usParaLen = 0;
    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_ABSOLUTE;
    gastAtParaList[1].usParaLen = sizeof("\"94/05/06,22:10:00+08\"") - 1;
    PS_MEM_CPY(gastAtParaList[1].aucPara, "\"94/05/06,22:10:00+08\"", gastAtParaList[1].usParaLen);
    ulRet = At_ParseCsmpVp(0, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_003)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // 参数初始化
    stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_NONE;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 0;

    //MOCKER操作

    //调用被测函数
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_004)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = sizeof("\"94/05/06,22:10:00+08\"") - 1;
    PS_MEM_CPY(gastAtParaList[1].aucPara, "\"94/05/06,22:10:00+08\"", gastAtParaList[1].usParaLen);

    //MOCKER操作

    //调用被测函数
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //执行检查
    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_005)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = 0;

    //MOCKER操作

    //调用被测函数
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_006)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // 参数初始化
    stVp.enValidPeriod = MN_MSG_VALID_PERIOD_NONE;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 0;

    //MOCKER操作

    //调用被测函数
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_007)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = sizeof("\"94/05/06,22:10:00+08\"") - 1;
    PS_MEM_CPY(gastAtParaList[1].aucPara, "\"94/05/06,22:10:00+08\"", gastAtParaList[1].usParaLen);

    //MOCKER操作
    MOCKER(At_CheckNumString)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    //调用被测函数
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //执行检查
    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_008)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = 0;

    //MOCKER操作

    //调用被测函数
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

class Test_AT_PrintTimeZone: public ::testing::Test
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

TEST_F(Test_AT_PrintTimeZone, Test_AT_PrintTimeZone_01)
{
    TAF_INT8                            cTimezone = -12;
    TAF_UINT16                          usLength;

    PS_MEM_SET(pgucAtSndCodeAddr, 0x00, 10);

/*  MOCKER(At_sprintf)
        .with(any(), any(), any(), eq("-"))
        .expects(exactly(1));

    MOCKER(At_sprintf)
        .with(any(), any(), any(), any(), eq(1), eq(2))
        .expects(exactly(1));*/

    AT_PrintTimeZone(cTimezone, pgucAtSndCodeAddr, &usLength);

/*  EXPECT_EQ('-', pgucAtSndCodeAddr[0]);
    EXPECT_EQ('1', pgucAtSndCodeAddr[1]);
    EXPECT_EQ('2', pgucAtSndCodeAddr[2]);*/
    EXPECT_EQ(4, usLength);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PrintTimeZone, Test_AT_PrintTimeZone_02)
{
    TAF_INT8                            cTimezone = 49;
    TAF_UINT16                          usLength;

    PS_MEM_SET(pgucAtSndCodeAddr, 0x00, 10);

    AT_PrintTimeZone(cTimezone, pgucAtSndCodeAddr, &usLength);

    EXPECT_EQ(4, usLength);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_SmsPrintScts: public ::testing::Test
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

TEST_F(Test_At_SmsPrintScts, Test_At_SmsPrintScts_01)
{
    MN_MSG_TIMESTAMP_STRU         stTimeStamp;

    stTimeStamp.ucYear = 0xa0;
    stTimeStamp.ucMonth = 0x31;
    stTimeStamp.ucDay = 0x40;
    stTimeStamp.ucHour = 0x24;
    stTimeStamp.ucMinute = 0x60;
    stTimeStamp.ucSecond = 0x60;

    PS_MEM_SET(pgucAtSndCodeAddr, 0x00, 50);

    At_SmsPrintScts(&stTimeStamp, pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsPrintScts, Test_At_SmsPrintScts_02)
{
    MN_MSG_TIMESTAMP_STRU         stTimeStamp;

    stTimeStamp.ucYear = 0x10;
    stTimeStamp.ucMonth = 0x04;
    stTimeStamp.ucDay = 0x11;
    stTimeStamp.ucHour = 0x17;
    stTimeStamp.ucMinute = 0x00;
    stTimeStamp.ucSecond = 0x00;

    PS_MEM_SET(pgucAtSndCodeAddr, 0x00, 50);

    At_SmsPrintScts(&stTimeStamp, pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_PrintAddrType: public ::testing::Test
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
#if 0

TEST_F(Test_At_PrintAddrType, Test_At_PrintAddrType_001)
{
    /*变量定义*/
    MN_MSG_ASCII_ADDR_STRU              stAddr;
    TAF_UINT8                           aucDst[1];
    TAF_UINT16                          usLength;
    TAF_UINT8                           ucCmpAddrType;

    /* 初始化变量 */
    memset(&stAddr, 0, sizeof(stAddr));
    stAddr.enNumPlan = MN_MSG_NPI_ISDN;
    stAddr.enNumType = MN_MSG_TON_UNKNOWN;
    aucDst[0] = 0;
    ucCmpAddrType    = 0x81;

    /* 全局变量赋值 */

    /* 调用消息入口函数 */
    usLength = At_PrintAddrType(&stAddr, aucDst);

    /* 结果验证*/

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif


class Test_AT_StubClearSpecificAutoRelyMsg: public ::testing::Test
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


TEST_F(Test_AT_StubClearSpecificAutoRelyMsg,Test_AT_StubClearSpecificAutoRelyMsg_001)
{
    // 参数定义
    VOS_UINT8                           ucClientIndex = 0;
    TAF_UINT32                          ulBufferIndex = 0;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;

    // 参数初始化
    pstEvent = (MN_MSG_EVENT_INFO_STRU *)malloc(sizeof(MN_MSG_EVENT_INFO_STRU));
    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)malloc(sizeof(MN_MSG_TS_DATA_INFO_STRU));

    // 相关全局变量初始化
    g_astAtClientCtx[ucClientIndex].stClientConfiguration.enModemId = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.astSmsMtBuffer[ulBufferIndex].pstEvent = pstEvent;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.astSmsMtBuffer[ulBufferIndex].pstTsDataInfo = pstTsDataInfo;
    // MOCKER操作

    // 调用被测函数
    AT_StubClearSpecificAutoRelyMsg(ucClientIndex, ulBufferIndex);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_StubClearSpecificAutoRelyMsg,Test_AT_StubClearSpecificAutoRelyMsg_002)
{
    // 参数定义
    VOS_UINT8                           ucClientIndex = 0;
    TAF_UINT32                          ulBufferIndex = 0;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;

    // 参数初始化
    pstEvent = (MN_MSG_EVENT_INFO_STRU *)malloc(sizeof(MN_MSG_EVENT_INFO_STRU));
    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)malloc(sizeof(MN_MSG_TS_DATA_INFO_STRU));

    // 相关全局变量初始化
    g_astAtClientCtx[ucClientIndex].stClientConfiguration.enModemId = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.astSmsMtBuffer[ulBufferIndex].pstEvent = pstEvent;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.astSmsMtBuffer[ulBufferIndex].pstTsDataInfo = pstTsDataInfo;

    // MOCKER操作

    // 调用被测函数
    AT_StubClearSpecificAutoRelyMsg(ucClientIndex, ulBufferIndex);


    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_PrintGetCpmsRsp: public ::testing::Test
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


TEST_F(Test_At_PrintGetCpmsRsp,Test_At_PrintGetCpmsRsp_001)
{
    // 参数定义
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: \"SM\",0,16,\"SM\",0,16,\"SM\",0,16";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};

    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->stCpmsInfo.enMemReadorDelete = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite  = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec = 16;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulUsedRec  = 0;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_PrintGetCpmsRsp(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)

TEST_F(Test_At_PrintGetCpmsRsp,Test_At_PrintGetCpmsRsp_002)
{
    // 参数定义
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: \"ME\",0,16,\"ME\",0,16,\"ME\",0,16";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\",\"c\"),(\"SM\",\"ME\"),(\"SM\",\"ME\")"};

    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->stCpmsInfo.enMemReadorDelete = MN_MSG_MEM_STORE_NV;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite  = MN_MSG_MEM_STORE_NV;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore = MN_MSG_MEM_STORE_NV;
    pstSmsCtx->stCpmsInfo.stNvimStorage.ulTotalRec = 16;
    pstSmsCtx->stCpmsInfo.stNvimStorage.ulUsedRec  = 0;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_PrintGetCpmsRsp(ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#endif
#endif


class Test_At_PrintSetCpmsRsp: public ::testing::Test
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


TEST_F(Test_At_PrintSetCpmsRsp,Test_At_PrintSetCpmsRsp_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: 0,16,0,16,0,16";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->stCpmsInfo.enMemReadorDelete = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite  = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec = 16;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulUsedRec  = 0;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_PrintSetCpmsRsp(ucIndex);

    // 执行检查
    EXPECT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_PrintSetCpmsRsp,Test_At_PrintSetCpmsRsp_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: 0,16,0,16,0,16";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->stCpmsInfo.enMemReadorDelete = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite  = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec = 16;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulUsedRec  = 0;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_PrintSetCpmsRsp(ucIndex);

    // 执行检查
    EXPECT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_SendMsgFoAttr: public ::testing::Test
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


TEST_F(Test_At_SendMsgFoAttr,Test_At_SendMsgFoAttr_001)
{
    // 参数定义
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    // 参数初始化
    stTsDataInfo.enTpduType = MN_MSG_TPDU_COMMAND;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    gastAtClientTab[ucIndex].CmdCurrentOpt                      = AT_CMD_CMGC_PDU_SET;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.bFoUsed = TAF_TRUE;

    // MOCKER操作

    // 调用被测函数
    At_SendMsgFoAttr(ucIndex, &stTsDataInfo);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SendMsgFoAttr,Test_At_SendMsgFoAttr_002)
{
    // 参数定义
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    // 参数初始化
    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    gastAtClientTab[ucIndex].CmdCurrentOpt                      = AT_CMD_CMGC_PDU_SET;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.bFoUsed = TAF_TRUE;

    // MOCKER操作

    // 调用被测函数
    At_SendMsgFoAttr(ucIndex, &stTsDataInfo);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
