#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtDataProc.h"


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

TAF_PS_EVT_STRU* TEST_Build_ApsAtMsg(
    VOS_UINT32                          ulEvtId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult = VOS_OK;
    TAF_PS_EVT_STRU                    *pstMsg   = VOS_NULL_PTR;

    /* 构造事件消息: PS域事件消息结构见TAF_PS_EVT_STRU */
    pstMsg = (TAF_PS_EVT_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PS_EVT_STRU) - 4 + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_NULL_PTR;
    }

    /* 填写事件消息头 */
    pstMsg->stHeader.ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->stHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stHeader.ulMsgName       = MN_CALLBACK_PS_CALL;

    /* 填写事件ID */
    pstMsg->ulEvtId                     = ulEvtId;

    /* 填写事件内容 */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    return pstMsg;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


class Test_AT_AppSndCallConnectedResult: public ::testing::Test
{
public:
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
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


TEST_F(Test_AT_AppSndCallConnectedResult, Test_AT_AppSndCallConnectedResult_001)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.ucRabId             = 5;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV4;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstPsModemCtx->aucCidToIndexTbl[1] = 0;
    pstPsModemCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstPsModemCtx->astCallEntity[0].stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
    pstPsModemCtx->astCallEntity[0].stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    pstPsModemCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstPsModemCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    At_MsgProc(pMsg);

    ASSERT_STREQ("\r\n^DCONN:1,\"IPV4\"\r\n", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppSndCallConnectedResult, Test_AT_AppSndCallConnectedResult_002)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.ucRabId             = 5;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV4;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    At_MsgProc(pMsg);

    ASSERT_STREQ("\r\n^DCONN:1,\"IPV4\"\r\n", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_AppSndCallConnectedResult, Test_AT_AppSndCallConnectedResult_003)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PS_IPV6_INFO_IND_STRU           stIpv6RaInfoNotifyInd;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.ucRabId             = 5;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV6;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstPsModemCtx->aucCidToIndexTbl[1] = 0;
    pstPsModemCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstPsModemCtx->astCallEntity[0].stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
    pstPsModemCtx->astCallEntity[0].stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    pstPsModemCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstPsModemCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    /* pdp act msg */
    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    At_MsgProc(pMsg);

    /* ra info */
    stIpv6RaInfoNotifyInd.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stIpv6RaInfoNotifyInd.stCtrl.ucOpId     = 0;
    stIpv6RaInfoNotifyInd.ucCid = 1;
    stIpv6RaInfoNotifyInd.ucRabId = 5;
    stIpv6RaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum = 1;

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND, &stIpv6RaInfoNotifyInd, sizeof(TAF_PS_IPV6_INFO_IND_STRU));

    At_MsgProc(pMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppSndCallConnectedResult, Test_AT_AppSndCallConnectedResult_004)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PS_IPV6_INFO_IND_STRU           stIpv6RaInfoNotifyInd;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.ucRabId             = 5;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV6;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    At_MsgProc(pMsg);

    /* ra info */
    stIpv6RaInfoNotifyInd.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stIpv6RaInfoNotifyInd.stCtrl.ucOpId     = 0;
    stIpv6RaInfoNotifyInd.ucCid = 1;
    stIpv6RaInfoNotifyInd.ucRabId = 5;

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND, &stIpv6RaInfoNotifyInd, sizeof(TAF_PS_IPV6_INFO_IND_STRU));

    At_MsgProc(pMsg);

    //ASSERT_STREQ("\r\n^DCONN:1,\"IPV6\"\r\n", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_AppSndCallEndedResult: public ::testing::Test
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
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_AppSndCallEndedResult, Test_AT_AppSndCallEndedResult_001)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  stEvent;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.enPdpType           = TAF_PDP_IPV4;
    stEvent.enCause             = 33;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    g_enAtAppActPdpType = TAF_PDP_IPV4;

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    At_MsgProc(pMsg);

    ASSERT_STREQ("\r\n^DEND:1,33,\"IPV4\"\r\n", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppSndCallEndedResult, Test_AT_AppSndCallEndedResult_002)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  stEvent;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.enPdpType = TAF_PDP_IPV4;
    stEvent.enCause             = 33;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    g_enAtAppActPdpType = TAF_PDP_IPV4;

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    At_MsgProc(pMsg);

    ASSERT_STREQ("\r\n^DEND:1,33,\"IPV4\"\r\n", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_AppSndCallEndedResult, Test_AT_AppSndCallEndedResult_003)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEvent;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.enPdpType           = TAF_PDP_IPV6;
    stEvent.enCause             = 33;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    g_enAtAppActPdpType = TAF_PDP_IPV6;

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    At_MsgProc(pMsg);

    ASSERT_STREQ("\r\n^DEND:1,33,\"IPV6\"\r\n", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppSndCallEndedResult, Test_AT_AppSndCallEndedResult_004)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEvent;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.enPdpType = TAF_PDP_IPV6;
    stEvent.enCause             = 33;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    g_enAtAppActPdpType = TAF_PDP_IPV6;

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    At_MsgProc(pMsg);

    ASSERT_STREQ("\r\n^DEND:1,33,\"IPV6\"\r\n", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppSndCallEndedResult, Test_AT_AppSndCallEndedResult_005)
{
    //参数定义
    VOS_UINT8                           ucCid;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_CHAR                            acExpectedStr[] = "\r\n^DEND:1,289,\"IPV4\"\r\n";

    //参数初始化
    ucCid = 1;
    enCause = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;
    enPdpType = TAF_PDP_IPV4;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppSndCallEndedResult(ucCid, enCause, enPdpType);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppSndCallEndedResult, Test_AT_AppSndCallEndedResult_006)
{
    //参数定义
    VOS_UINT8                           ucCid;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_CHAR                            acExpectedStr[] = "\r\n^DEND:1,289,\"IPV6\"\r\n";

    //参数初始化
    ucCid = 1;
    enCause = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;
    enPdpType = TAF_PDP_IPV6;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppSndCallEndedResult(ucCid, enCause, enPdpType);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif



class Test_AT_ProcAppPdpStateChange: public ::testing::Test
{
public:
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx;

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


TEST_F(Test_AT_ProcAppPdpStateChange, Test_AT_ProcAppPdpStateChange_001)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stDcActEvent;
    MsgBlock                           *pMsg;

    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stEvent.stCtrl.ucOpId       = 0;
    stEvent.ucCid               = 1;
    stEvent.ucRabId             = 5;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV4;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstPsModemCtx->aucCidToIndexTbl[1] = 0;
    pstPsModemCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstPsModemCtx->astCallEntity[0].stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
    pstPsModemCtx->astCallEntity[0].stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    pstPsModemCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstPsModemCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    MOCKER(At_SendResultData)
        .expects(exactly(2));

    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF, &stEvent, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /* PDP ACT */
    At_MsgProc(pMsg);

    ASSERT_STREQ("\r\n^DCONN:1,\"IPV4\"\r\n", (char *)pgucAtSndCodeAddr);

    stDcActEvent.stCtrl.usClientId   = AT_CLIENT_ID_APP;
    stDcActEvent.stCtrl.ucOpId       = 0;
    stDcActEvent.ucCid               = 1;
    stDcActEvent.enPdpType           = TAF_PDP_IPV4;
    stDcActEvent.enCause             = 33;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    g_enAtAppActPdpType = TAF_PDP_IPV4;

    /* PDP DEACT */
    pMsg = (MsgBlock *)TEST_Build_ApsAtMsg(ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND, &stDcActEvent, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    At_MsgProc(pMsg);

    ASSERT_STREQ("\r\n^DEND:1,33,\"IPV4\"\r\n", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_GetFcPriFromMap: public ::testing::Test
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

TEST(Test_AT_GetFcPriFromMap, Test_AT_GetFcPriFromMap_001)
{
    //参数定义
    FC_ID_ENUM_UINT8                   enFcId;
    AT_FCID_MAP_STRU                   stFcIdMap;
    VOS_UINT32                         ulRst;

    //参数初始化
    enFcId = FC_ID_BUTT;

    //相关全局变量初始化

    //MOCKER


    //调用被测函数.
    ulRst =AT_GetFcPriFromMap(enFcId, &stFcIdMap);

    //执行检查

    EXPECT_EQ(ulRst, VOS_ERR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST(Test_AT_GetFcPriFromMap, Test_AT_GetFcPriFromMap_002)
{
    //参数定义
    FC_ID_ENUM_UINT8                   enFcId;
    AT_FCID_MAP_STRU                   stFcIdMap;
    VOS_UINT32                         ulRst;

    //参数初始化
    enFcId = FC_ID_MODEM;

    //相关全局变量初始化

    //MOCKER


    //调用被测函数.
    ulRst =AT_GetFcPriFromMap(enFcId, &stFcIdMap);

    //执行检查

    EXPECT_EQ(ulRst, VOS_OK);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST(Test_AT_GetFcPriFromMap, Test_AT_GetFcPriFromMap_003)
{
    //参数定义
    FC_ID_ENUM_UINT8                   enFcId;
    AT_FCID_MAP_STRU                   stFcIdMap;
    VOS_UINT32                         ulRst;

    //参数初始化
    enFcId = FC_ID_USB_ETH;

    //相关全局变量初始化

    //MOCKER


    //调用被测函数.
    ulRst =AT_GetFcPriFromMap(enFcId, &stFcIdMap);

    //执行检查

    EXPECT_EQ(ulRst, VOS_ERR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_NotifyFcWhenPdpModify: public ::testing::Test
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

TEST(Test_AT_NotifyFcWhenPdpModify, Test_AT_NotifyFcWhenPdpModify_001)
{
    //参数定义
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     stEvent;
    FC_ID_ENUM_UINT8                    enFcId;

    //参数初始化
    enFcId = FC_ID_MODEM;

    //相关全局变量初始化
    g_stFcIdMaptoFcPri[enFcId].enFcPri   = 0;
    g_stFcIdMaptoFcPri[enFcId].ulUsed    = VOS_TRUE;

    //MOCKER
    MOCKER(AT_GetFCPriFromQos)
        .stubs()
        .will(returnValue((FC_PRI_ENUM_UINT8)1));

    MOCKER(AT_ChangeFCPoint)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));


    //调用被测函数.
    AT_NotifyFcWhenPdpModify(&stEvent, enFcId);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_ProcNdisRegFCPoint: public ::testing::Test
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


TEST_F(Test_AT_ProcNdisRegFCPoint,Test_AT_ProcNdisRegFCPoint_001)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_NDIS;
    stEvent.ucRabId                     = 15;
    enPdpType                           = TAF_PDP_IPV4;

    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri = 0;

    AT_ProcNdisRegFCPoint(&stEvent, enPdpType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcNdisRegFCPoint,Test_AT_ProcNdisRegFCPoint_002)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_NDIS;
    stEvent.ucRabId                     = 14;
    stEvent.bitOpUmtsQos                = VOS_TRUE;
    stEvent.stUmtsQos.ucTrafficClass    = AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL;

    enPdpType                           = TAF_PDP_IPV4;

    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri = 0;


    MOCKER(AT_GetFCPriFromQos)
        .stubs()
        .will(returnValue((FC_PRI_ENUM_UINT8)1));

    AT_ProcNdisRegFCPoint(&stEvent, enPdpType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcNdisRegFCPoint,Test_AT_ProcNdisRegFCPoint_003)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_NDIS;
    stEvent.ucRabId                     = 14;
    stEvent.bitOpUmtsQos                = VOS_TRUE;
    stEvent.stUmtsQos.ucTrafficClass    = AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL;
    enPdpType                           = TAF_PDP_IPV4;

    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri = 0;


    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_ProcNdisRegFCPoint(&stEvent, enPdpType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcNdisRegFCPoint,Test_AT_ProcNdisRegFCPoint_004)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_NDIS;
    stEvent.ucRabId                     = 14;
    stEvent.bitOpUmtsQos                = 0;
    enPdpType                           = TAF_PDP_IPV4;

    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri = 0;


    MOCKER(AT_GetFCPriFromQos)
        .stubs()
        .will(returnValue((FC_PRI_ENUM_UINT8)1));

    AT_ProcNdisRegFCPoint(&stEvent, enPdpType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_ProcNdisDeRegFCPoint: public ::testing::Test
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


TEST_F(Test_AT_ProcNdisDeRegFCPoint,Test_AT_ProcNdisDeRegFCPointe_001)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_NDIS;
    stEvent.ucRabId                     = 14;
    enPdpType                           = TAF_PDP_IPV4;

    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri = 0;

    AT_ProcNdisDeRegFCPoint(&stEvent, enPdpType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcNdisDeRegFCPoint,Test_AT_ProcNdisDeRegFCPoint_002)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU       stEvent;
    TAF_PDP_TYPE_ENUM_UINT8                   enPdpType;

    stEvent.stCtrl.usClientId = AT_CLIENT_ID_BUTT;
    enPdpType = TAF_PDP_IPV4;

    MOCKER(AT_DeRegNdisFCPoint)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_ProcNdisDeRegFCPoint(&stEvent, enPdpType);

    GlobalMockObject::verify();
}



class Test_AT_ModemPsRspPdpDeactivatedEvtProc: public ::testing::Test
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

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        At_PidInit(VOS_IP_INITIAL);
        AT_InitUartCtx();
        AT_UsbModemInit();
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicModemInit();
#endif
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ModemPsRspPdpDeactivatedEvtProc,Test_AT_ModemPsRspPdpDeactivatedEvtProc_001)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;

    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_MODEM;
    stEvent.ucRabId                     = 15;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;

    AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex, (VOS_VOID *)&stEvent);

    EXPECT_EQ(AT_CMD_WAIT_PPP_PROTOCOL_REL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_ModemPsRspPdpDeactivatedEvtProc,Test_AT_ModemPsRspPdpDeactivatedEvtProc_002)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU   stEvent;
    VOS_UINT8                           ucIndex;

    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_MODEM;
    stEvent.ucRabId                     = 15;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_IP_DATA_MODE;

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_NO_CARRIER));


    AT_ModemPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactivatedEvtProc, Test_AT_ModemPsRspPdpDeactivatedEvtProc_003)
{
    // 变量声明
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstLineCtrl                         = AT_GetUartLineCtrlInfo();
    pstLineCtrl->enDcdMode              = AT_UART_DCD_MODE_CONNECT_ON;

    gastAtClientTab[ucIndex].Mode       = AT_ONLINE_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_PS_SET;

    AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    AT_ModemPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactivatedEvtProc, Test_AT_ModemPsRspPdpDeactivatedEvtProc_004)
{
    // 变量声明
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstLineCtrl                         = AT_GetUartLineCtrlInfo();
    pstLineCtrl->enDcdMode              = AT_UART_DCD_MODE_CONNECT_ON;

    gastAtClientTab[ucIndex].Mode       = AT_ONLINE_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_NO_CARRIER));

    // 调用被测函数
    AT_ModemPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactivatedEvtProc, Test_AT_ModemPsRspPdpDeactivatedEvtProc_005)
{
    // 变量声明
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstLineCtrl                         = AT_GetUartLineCtrlInfo();
    pstLineCtrl->enDcdMode              = AT_UART_DCD_MODE_CONNECT_ON;

    gastAtClientTab[ucIndex].Mode       = AT_ONLINE_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_PS_SET;

    AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_RAW_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_OK));

    // 调用被测函数
    AT_ModemPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactivatedEvtProc, Test_AT_ModemPsRspPdpDeactivatedEvtProc_006)
{
    // 变量声明
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_ONLINE_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_RAW_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_NO_CARRIER));

    // 调用被测函数
    AT_ModemPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactivatedEvtProc, Test_AT_ModemPsRspPdpDeactivatedEvtProc_007)
{
    // 变量声明
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_NO_CARRIER));

    // 调用被测函数
    AT_ModemPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


class Test_AT_ModemPsRspPdpDeactEvtCnfProc: public ::testing::Test
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
        AT_InitUartCtx();
        AT_UsbModemInit();
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicModemInit();
#endif
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc, Test_AT_ModemPsRspPdpDeactEvtCnfProc_001)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    ucIndex                             = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(never());

    MOCKER(AT_SetModemStatus)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_CtrlDCD)
        .expects(never());

    // 调用被测函数
    AT_ModemPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc,Test_AT_ModemPsRspPdpDeactEvtCnfProc_002)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_MODEM;
    stEvent.ucRabId                     = 15;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(never());

    AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex, (VOS_VOID *)&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc, Test_AT_ModemPsRspPdpDeactEvtCnfProc_003)
{
    // 变量声明
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_ERROR));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_NO_CARRIER));

    // 调用被测函数
    AT_ModemPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc, Test_AT_ModemPsRspPdpDeactEvtCnfProc_004)
{
    // 变量声明
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstLineCtrl                         = AT_GetUartLineCtrlInfo();
    pstLineCtrl->enDcdMode              = AT_UART_DCD_MODE_CONNECT_ON;

    gastAtClientTab[ucIndex].Mode       = AT_ONLINE_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_PS_SET;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_ERROR));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    AT_ModemPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_MODE, gastAtClientTab[ucIndex].Mode);
    EXPECT_EQ(AT_DATA_BUTT_MODE, gastAtClientTab[ucIndex].DataMode);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc,Test_AT_ModemPsRspPdpDeactEvtCnfProc_005)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_MODEM;
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_RAW_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_ERROR));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_NO_CARRIER));

    AT_ModemPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);

    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_MODE, gastAtClientTab[ucIndex].Mode);
    EXPECT_EQ(AT_DATA_BUTT_MODE, gastAtClientTab[ucIndex].DataMode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc, Test_AT_ModemPsRspPdpDeactEvtCnfProc_006)
{
    // 变量声明
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_NO_CARRIER));

    // 调用被测函数
    AT_ModemPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc, Test_AT_ModemPsRspPdpDeactEvtCnfProc_007)
{
    // 变量声明
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucRabId                     = 5;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_ERROR));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_NO_CARRIER));

    MOCKER(AT_SetModemStatus)
        .expects(never())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_ModemPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

#if 0

TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc,Test_AT_ModemPsRspPdpDeactEvtCnfProc_008)
{
    /*变量定义*/
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;

    /*本地变量初始化*/
    ucIndex   = AT_CLIENT_TAB_MODEM_INDEX;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    /*调用被测函数 */
    AT_ModemPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);

    /* 结果验证*/

    GlobalMockObject::verify();
}
#endif


class Test_AT_MODEM_ProcCallEndCnfEvent: public ::testing::Test
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
        AT_InitUartCtx();
        AT_UsbModemInit();
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicModemInit();
#endif
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_MODEM_ProcCallEndCnfEvent, Test_AT_MODEM_ProcCallEndCnfEvent_001)
{
    // 变量声明
    TAF_PS_CALL_END_CNF_STRU            stEvent;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucCid                       = 1;
    stEvent.enCause                     = TAF_PS_CAUSE_SUCCESS;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_MODEM_ProcCallEndCnfEvent(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MODEM_ProcCallEndCnfEvent, Test_AT_MODEM_ProcCallEndCnfEvent_002)
{
    // 变量声明
    TAF_PS_CALL_END_CNF_STRU            stEvent;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucCid                       = 1;
    stEvent.enCause                     = TAF_PS_CAUSE_SUCCESS;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_MODEM_ProcCallEndCnfEvent(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_PS_DATA_CALL_END_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MODEM_ProcCallEndCnfEvent, Test_AT_MODEM_ProcCallEndCnfEvent_003)
{
    // 变量声明
    TAF_PS_CALL_END_CNF_STRU            stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucCid                       = 1;
    stEvent.enCause                     = TAF_PS_CAUSE_CID_INVALID;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;

    AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .stubs()
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .stubs()
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_MODEM_ProcCallEndCnfEvent(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MODEM_ProcCallEndCnfEvent, Test_AT_MODEM_ProcCallEndCnfEvent_004)
{
    // 变量声明
    TAF_PS_CALL_END_CNF_STRU            stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucCid                       = 1;
    stEvent.enCause                     = TAF_PS_CAUSE_CID_INVALID;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_ONLINE_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_PS_SET;

    AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .stubs()
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_RAW_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .stubs()
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_ERROR));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    AT_MODEM_ProcCallEndCnfEvent(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MODEM_ProcCallEndCnfEvent, Test_AT_MODEM_ProcCallEndCnfEvent_005)
{
    // 变量声明
    TAF_PS_CALL_END_CNF_STRU            stEvent;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    stEvent.ucCid                       = 1;
    stEvent.enCause                     = TAF_PS_CAUSE_CID_INVALID;
    usPppId                             = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;

    // MOCKER操作
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .stubs()
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_REL_PPP_REQ))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(PPP_RcvAtCtrlOperEvent)
         .stubs()
        .with(eq(usPppId), eq((PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32)PPP_AT_CTRL_HDLC_DISABLE))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_StartTimer)
        .stubs()
        .with(eq((VOS_UINT32)AT_PPP_PROTOCOL_REL_TIME), eq(ucIndex))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(BSP_USB_GetLinuxSysType)
        .stubs()
        .will(returnValue((int)VOS_ERROR));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_NO_CARRIER));

    // 调用被测函数
    AT_MODEM_ProcCallEndCnfEvent(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


class Test_At_PppReleaseIndProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_PppReleaseIndProc,Test_At_PppReleaseIndProc_001)
{
    VOS_UINT8                           ucIndex;

    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;

    gastAtClientTab[ucIndex].usPppId    = 1;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAIT_PPP_PROTOCOL_REL_SET;

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_NO_CARRIER));

    At_PppReleaseIndProc(ucIndex);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_At_PppReleaseIndProc,Test_At_PppReleaseIndProc_002)
{
    VOS_UINT8                           ucIndex;

    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;

    gastAtClientTab[ucIndex].usPppId    = 1;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_IP_CALL_SET;

    At_PppReleaseIndProc(ucIndex);

    ASSERT_EQ(AT_CMD_PS_DATA_CALL_END_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_HsicPsRspEvtPdpDeactivatedProc: public ::testing::Test
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

TEST_F(Test_AT_HsicPsRspEvtPdpDeactivatedProc,Test_AT_HsicPsRspEvtPdpDeactivatedProc_001)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;
    stEvent.enPdpType                   = TAF_PDP_IPV4;
    ucIndex                             = 0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed     = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId  = UDI_ACM_HSIC_ACM1_ID;

    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    AT_HsicPsRspEvtPdpDeactivatedProc(ucIndex, &stEvent);

    EXPECT_EQ(VOS_FALSE, g_stFcIdMaptoFcPri[FC_ID_DIPC_1].ulUsed);
    EXPECT_EQ(FC_PRI_BUTT, g_stFcIdMaptoFcPri[FC_ID_DIPC_1].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicPsRspEvtPdpDeactivatedProc,Test_AT_HsicPsRspEvtPdpDeactivatedProc_002)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;
    stEvent.enPdpType                   = TAF_PDP_IPV4;
    ucIndex                             = 0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed     = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId  = UDI_ACM_HSIC_ACM3_ID;

    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    AT_HsicPsRspEvtPdpDeactivatedProc(ucIndex, &stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicPsRspEvtPdpDeactivatedProc,Test_AT_HsicPsRspEvtPdpDeactivatedProc_003)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;
    stEvent.enPdpType                   = TAF_PDP_IPV4;
    ucIndex                             = 0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM2_ID;


    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    AT_HsicPsRspEvtPdpDeactivatedProc(ucIndex, &stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicPsRspEvtPdpDeactivatedProc,Test_AT_HsicPsRspEvtPdpDeactivatedProc_004)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;
    stEvent.enPdpType                   = TAF_PDP_TYPE_BUTT;
    ucIndex                             = 0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_INVAL_DEV_ID;


    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(At_SendResultData)
        .expects(never());

    AT_HsicPsRspEvtPdpDeactivatedProc(ucIndex, &stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_HsicPsRspEvtPdpDeactivatedProc,Test_AT_HsicPsRspEvtPdpDeactivatedProc_005)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId = AT_CLIENT_ID_NDIS;
    stEvent.ucCid    = 1;
    stEvent.ucRabId  = 5;
    stEvent.enPdpType= TAF_PDP_IPV6;
    stEvent.enCause  = TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE;
    ucIndex          = 0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_INVAL_DEV_ID;


    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    AT_HsicPsRspEvtPdpDeactivatedProc(ucIndex, &stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicPsRspEvtPdpDeactivatedProc,Test_AT_HsicPsRspEvtPdpDeactivatedProc_006)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId = AT_CLIENT_ID_NDIS;
    stEvent.ucCid    = 1;
    stEvent.ucRabId  = 5;
    stEvent.enPdpType= TAF_PDP_IPV4V6;
    stEvent.enCause  = TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE;
    ucIndex          = 0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_INVAL_DEV_ID;


    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    AT_HsicPsRspEvtPdpDeactivatedProc(ucIndex, &stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif


class Test_AT_HsicPsRspEvtPdpDeactCnfProc: public ::testing::Test
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

TEST_F(Test_AT_HsicPsRspEvtPdpDeactCnfProc,Test_AT_HsicPsRspEvtPdpDeactCnfProc_001)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;


    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_HsicPsRspEvtPdpDeactCnfProc(&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicPsRspEvtPdpActCnfProc: public ::testing::Test
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

TEST_F(Test_AT_HsicPsRspEvtPdpActCnfProc,Test_AT_HsicPsRspEvtPdpActCnfProc_001)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;


    MOCKER(FC_RegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_HsicPsRspEvtPdpActCnfProc(&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicPsRspEvtPdpActCnfProc,Test_AT_HsicPsRspEvtPdpActCnfProc_002)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed     = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM3_ID;


    MOCKER(FC_RegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_HsicPsRspEvtPdpActCnfProc(&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicPsRspEvtPdpActCnfProc,Test_AT_HsicPsRspEvtPdpActCnfProc_003)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed     = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM5_ID;


    MOCKER(FC_RegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_HsicPsRspEvtPdpActCnfProc(&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicPsRspEvtPdpActCnfProc,Test_AT_HsicPsRspEvtPdpActCnfProc_004)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed     = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM5_ID;

    MOCKER(FC_RegPoint)
        .stubs()
        .will(returnValue(VOS_ERR));

    AT_HsicPsRspEvtPdpActCnfProc(&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicPsRspEvtPdpActCnfProc,Test_AT_HsicPsRspEvtPdpActCnfProc_005)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed     = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM5_ID;

    MOCKER(FC_RegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_HsicPsRspEvtPdpActCnfProc(&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicPsRspEvtPdpActCnfProc,Test_AT_HsicPsRspEvtPdpActCnfProc_006)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed     = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_INVAL_DEV_ID;


    MOCKER(FC_RegPoint)
        .expects(never())
        .will(returnValue(VOS_OK));

    AT_HsicPsRspEvtPdpActCnfProc(&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicPsRspEvtPdpActCnfProc,Test_AT_HsicPsRspEvtPdpActCnfProc_007)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    stEvent.stCtrl.usClientId                    = AT_CLIENT_ID_NDIS;
    stEvent.ucCid                       = 1;
    stEvent.ucRabId                     = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed     = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM2_ID;

    MOCKER(FC_RegPoint)
        .expects(never())
        .will(returnValue(VOS_OK));

    AT_HsicPsRspEvtPdpActCnfProc(&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_DisableHsicFlowCtl: public ::testing::Test
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

TEST_F(Test_AT_DisableHsicFlowCtl,Test_AT_DisableHsicFlowCtl_001)
{
    VOS_UINT32                          ulUdiHdl;
    VOS_UINT32                          ulParam2;
    VOS_UINT32                          ulRst;

    ulUdiHdl = 1;
    ulParam2 = 1;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue((BSP_S32)VOS_ERR));

    ulRst = AT_DisableHsicFlowCtl(ulUdiHdl, ulParam2);

    EXPECT_EQ(ulRst, VOS_ERR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DisableHsicFlowCtl,Test_AT_DisableHsicFlowCtl_002)
{
    VOS_UINT32                          ulUdiHdl;
    VOS_UINT32                          ulParam2;
    VOS_UINT32                          ulRst;

    ulUdiHdl = 1;
    ulParam2 = 1;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue((BSP_S32)VOS_OK));

    ulRst = AT_DisableHsicFlowCtl(ulUdiHdl, ulParam2);

    EXPECT_EQ(ulRst, VOS_OK);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_EnableHsicFlowCtl: public ::testing::Test
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

TEST_F(Test_AT_EnableHsicFlowCtl,Test_AT_EnableHsicFlowCtl_001)
{
    VOS_UINT32                          ulUdiHdl;
    VOS_UINT32                          ulParam2;
    VOS_UINT32                          ulRst;

    ulUdiHdl = 1;
    ulParam2 = 1;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue((BSP_S32)VOS_ERR));

    ulRst = AT_EnableHsicFlowCtl(ulUdiHdl, ulParam2);

    EXPECT_EQ(ulRst, VOS_ERR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_EnableHsicFlowCtl,Test_AT_EnableHsicFlowCtl_002)
{
    VOS_UINT32                          ulUdiHdl;
    VOS_UINT32                          ulParam2;
    VOS_UINT32                          ulRst;

    ulUdiHdl = 1;
    ulParam2 = 1;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue((BSP_S32)VOS_OK));

    ulRst = AT_EnableHsicFlowCtl(ulUdiHdl, ulParam2);

    EXPECT_EQ(ulRst, VOS_OK);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_AppRegFCPoint: public ::testing::Test
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


TEST_F(Test_AT_AppRegFCPoint, Test_AT_AppRegFCPoint_001)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;

    //参数初始化
    enFcId = FC_ID_NIC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = 0;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_AppRegFCPoint(enFcId, &stEvent, 0);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_FOR_PDN_LOWEST, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppRegFCPoint, Test_AT_AppRegFCPoint_002)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;

    //参数初始化
    enFcId = FC_ID_NIC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_BUTT;

    //调用被测函数
    ulRslt = AT_AppRegFCPoint(enFcId, &stEvent, 0);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppRegFCPoint, Test_AT_AppRegFCPoint_003)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           ucRmNetId;
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    enModemId = MODEM_ID_0;
    ucRmNetId = 1;
    enFcId    = FC_ID_NIC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_TAB_APP1_INDEX;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_AppRegFCPoint(enFcId, &stEvent, 0);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_FOR_PDN_LOWEST, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_AppDeRegFCPoint: public ::testing::Test
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


TEST_F(Test_AT_AppDeRegFCPoint, Test_AT_AppDeRegFCPoint_001)
{
    //参数定义
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           ucRabId;
    VOS_UINT32                          ulRslt;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;

    //参数初始化
    enFcId  = FC_ID_NIC_1;
    ucRabId = 5;
    stEvent.stCtrl.usClientId = 0;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_AppDeRegFCPoint(enFcId, &stEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_FALSE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_BUTT, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppDeRegFCPoint, Test_AT_AppDeRegFCPoint_002)
{
    //参数定义
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;

    //参数初始化
    enFcId  = FC_ID_NIC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_AppDeRegFCPoint(enFcId, &stEvent);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)

class Test_AT_RegHsicFCPoint: public ::testing::Test
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


TEST_F(Test_AT_RegHsicFCPoint, Test_AT_RegHsicFCPoint_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;

    //参数初始化
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RegHsicFCPoint(&stEvent);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RegHsicFCPoint, Test_AT_RegHsicFCPoint_002)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    FC_PRI_ENUM_UINT32                  enFCPri;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    //参数初始化
    enFcId = FC_ID_DIPC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_TAB_MODEM_INDEX;
    stEvent.ucCid = 1;
    enFCPri = FC_PRI_1;
    enModemId = MODEM_ID_0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapCreate)
        .expects(exactly(1));

    //调用被测函数
    ulRslt = AT_RegHsicFCPoint(&stEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_FOR_PDN_LOWEST, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RegHsicFCPoint, Test_AT_RegHsicFCPoint_003)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    FC_PRI_ENUM_UINT32                  enFCPri;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    //参数初始化
    enFcId = FC_ID_DIPC_1;

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_TAB_MODEM_INDEX;
    stEvent.ucCid = 1;
    enFCPri = FC_PRI_1;
    enModemId = MODEM_ID_0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapCreate)
        .expects(exactly(1));

    //调用被测函数
    ulRslt = AT_RegHsicFCPoint(&stEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_FOR_PDN_NONGBR, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_DeRegHsicFCPoint: public ::testing::Test
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


TEST_F(Test_AT_DeRegHsicFCPoint, Test_AT_DeRegHsicFCPoint_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;

    //参数初始化
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_DeRegHsicFCPoint(&stEvent);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DeRegHsicFCPoint, Test_AT_DeRegHsicFCPoint_002)
{
    //参数定义
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    enFcId  = FC_ID_DIPC_1;
    stEvent.ucRabId = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_TAB_MODEM_INDEX;
    stEvent.ucCid = AT_PS_USER_CID_1;
    enModemId = MODEM_ID_0;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulUsed    = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapDelete)
        .expects(exactly(1))
        .with(eq(stEvent.ucRabId), eq(enModemId));

    //调用被测函数
    ulRslt = AT_DeRegHsicFCPoint(&stEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_FALSE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_BUTT, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_RegNdisFCPoint: public ::testing::Test
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


TEST_F(Test_AT_RegNdisFCPoint, Test_AT_RegNdisFCPoint_001)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    FC_PRI_ENUM_UINT8                   enFCPri;
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    enFcId = FC_ID_NIC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = 0;
    stEvent.ucCid = 1;
    stEvent.stUmtsQos.ucTrafficClass = AT_QOS_TRAFFIC_CLASS_INTERACTIVE;
    enFCPri = FC_PRI_1;
    enModemId = MODEM_ID_0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapCreate)
        .expects(exactly(1))
        .with(eq(enFcId), eq(stEvent.ucRabId), eq(enModemId));

    //调用被测函数
    ulRslt = AT_RegNdisFCPoint(&stEvent, enFcId, enModemId);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_FOR_PDN_NONGBR, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RegNdisFCPoint, Test_AT_RegNdisFCPoint_002)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    FC_PRI_ENUM_UINT8                   enFCPri;
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    enFcId = FC_ID_NIC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = 0;
    stEvent.ucCid = 1;
    enFCPri = FC_PRI_1;
    enModemId = MODEM_ID_0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapCreate)
        .expects(exactly(1))
        .with(eq(enFcId), eq(stEvent.ucRabId), eq(enModemId));

    //调用被测函数
    ulRslt = AT_RegNdisFCPoint(&stEvent, enFcId, enModemId);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_FOR_PDN_NONGBR, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_DeRegNdisFCPoint: public ::testing::Test
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


TEST_F(Test_AT_DeRegNdisFCPoint, Test_AT_DeRegNdisFCPoint_001)
{
    //参数定义
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucRabId;
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    enFcId = FC_ID_NIC_1;
    ucRabId = 5;
    enModemId = MODEM_ID_0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapDelete)
        .expects(exactly(1))
        .with(eq(ucRabId), eq(enModemId));
    MOCKER(FC_DeRegPoint)
        .expects(exactly(1))
        .with(eq(enFcId), eq(enModemId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulRslt = AT_DeRegNdisFCPoint(ucRabId, enModemId);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_FALSE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_BUTT, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RegModemPsDataFCPoint: public ::testing::Test
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


TEST_F(Test_AT_RegModemPsDataFCPoint, Test_AT_RegModemPsDataFCPoint_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           ucIndex;

    //参数初始化
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_BUTT;
    enFcId = FC_ID_MODEM;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RegModemPsDataFCPoint(ucIndex, &stEvent, enFcId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RegModemPsDataFCPoint, Test_AT_RegModemPsDataFCPoint_002)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    FC_PRI_ENUM_UINT8                   enFCPri;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;

    //参数初始化
    enFcId = FC_ID_MODEM;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_TAB_APP1_INDEX;
    stEvent.ucCid = 1;
    stEvent.bitOpUmtsQos = TAF_FREE;
    enFCPri = FC_PRI_1;
    enModemId = MODEM_ID_0;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapCreate)
        .expects(exactly(1))
        .with(eq(enFcId), eq(stEvent.ucRabId), eq(enModemId));

    //调用被测函数
    ulRslt = AT_RegModemPsDataFCPoint(ucIndex, &stEvent, enFcId);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[enFcId].ulUsed);
    EXPECT_EQ(FC_PRI_FOR_PDN_NONGBR, g_stFcIdMaptoFcPri[enFcId].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_DeRegModemPsDataFCPoint: public ::testing::Test
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


TEST_F(Test_AT_DeRegModemPsDataFCPoint, Test_AT_DeRegModemPsDataFCPoint_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucRabId = 5;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = AT_DeRegModemPsDataFCPoint(ucIndex, ucRabId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DeRegModemPsDataFCPoint, Test_AT_DeRegModemPsDataFCPoint_002)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucRabId;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;

    //参数初始化
    ucRabId = 5;
    enModemId = MODEM_ID_0;
    enClientIndex = AT_CLIENT_TAB_MODEM_INDEX;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapDelete)
        .expects(exactly(1))
        .with(eq(ucRabId), eq(enModemId));
    MOCKER(FC_DeRegPoint)
        .expects(exactly(1))
        .with(eq((FC_ID_ENUM_UINT8)FC_ID_MODEM), eq(enModemId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulRslt = AT_DeRegModemPsDataFCPoint(enClientIndex, ucRabId);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(VOS_FALSE, g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed);
    EXPECT_EQ(FC_PRI_BUTT, g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DeRegModemPsDataFCPoint, Test_AT_DeRegModemPsDataFCPoint_003)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucRabId;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;

    //参数初始化
    ucRabId = 5;
    enModemId = MODEM_ID_0;
    enClientIndex = AT_CLIENT_TAB_MODEM_INDEX;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChannelMapDelete)
        .expects(exactly(1))
        .with(eq(ucRabId), eq(enModemId));
    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = AT_DeRegModemPsDataFCPoint(enClientIndex, ucRabId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if( FEATURE_ON == FEATURE_CSD )

class Test_AT_VpResetFlowCtl: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed       = VOS_TRUE;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri      = FC_PRI_4;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask  = 0x20;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId    = MODEM_ID_0;
    }
    void TearDown()
    {
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed       = VOS_FALSE;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri      = FC_PRI_BUTT;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask  = 0;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId    = MODEM_ID_BUTT;
    }
};


TEST_F(Test_AT_VpResetFlowCtl, Test_AT_VpResetFlowCtl_001)
{
    //参数定义
    VOS_UINT32                          ulParam1;
    VOS_UINT32                          ulParam2;

    //参数初始化
    ulParam1 = 0;
    ulParam2 = FC_ID_NIC_1;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    AT_VpResetFlowCtl(ulParam1, ulParam2);

    //执行检查
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed);
    EXPECT_EQ(FC_PRI_4, g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri);
    EXPECT_EQ(0x20, g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask);
    EXPECT_EQ(MODEM_ID_0, g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_VpResetFlowCtl, Test_AT_VpResetFlowCtl_002)
{
    //参数定义
    VOS_UINT32                          ulParam1;
    VOS_UINT32                          ulParam2;

    //参数初始化
    ulParam1 = 0;
    ulParam2 = FC_ID_NIC_1;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    AT_VpResetFlowCtl(ulParam1, ulParam2);

    //执行检查
    EXPECT_EQ(VOS_FALSE, g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed);
    EXPECT_EQ(FC_PRI_BUTT, g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri);
    EXPECT_EQ(0x20, g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask);
    EXPECT_EQ(MODEM_ID_BUTT, g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RegModemVideoPhoneFCPoint: public ::testing::Test
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


TEST_F(Test_AT_RegModemVideoPhoneFCPoint, Test_AT_RegModemVideoPhoneFCPoint_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;
    FC_ID_ENUM_UINT8                    ulFcId;

    //参数初始化
    ulFcId = FC_ID_MODEM;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = AT_RegModemVideoPhoneFCPoint(0, ulFcId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_DeRegModemVideoPhoneFCPoint: public ::testing::Test
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


TEST_F(Test_AT_DeRegModemVideoPhoneFCPoint, Test_AT_DeRegModemVideoPhoneFCPoint_001)
{
    //参数定义
    VOS_UINT32                          ulRslt;

    //参数初始化

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = AT_DeRegModemVideoPhoneFCPoint(0);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

class Test_AT_ChangeFCPoint: public ::testing::Test
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


TEST_F(Test_AT_ChangeFCPoint, Test_AT_ChangeFCPoint_001)
{
    //参数定义
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    FC_PRI_ENUM_UINT8                   enFCPri;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;

    //参数初始化
    enFCPri = 0;
    enFcId  = FC_ID_NIC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_ChangeFCPoint(&(stEvent.stCtrl), enFCPri, enFcId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ChangeFCPoint, Test_AT_ChangeFCPoint_002)
{
    //参数定义
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRslt;
    FC_PRI_ENUM_UINT8                   enFCPri;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    enFCPri = 0;
    enFcId  = FC_ID_NIC_1;
    stEvent.ucRabId  = 5;
    stEvent.stCtrl.usClientId = AT_CLIENT_TAB_APP1_INDEX;
    enModemId = MODEM_ID_0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_ChangePoint)
        .expects(exactly(4))
        .with(eq(enFcId), any(), eq(enFCPri), eq(enModemId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulRslt = AT_ChangeFCPoint(&(stEvent.stCtrl), enFCPri, enFcId);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_AppIpv4PdpActRejProc: public ::testing::Test
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


TEST_F(Test_AT_AppIpv4PdpActRejProc, Test_AT_AppIpv4PdpActRejProc_001)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEvent;

    //参数初始化
    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();

    stEvent.ucCid   = 2;
    stEvent.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;

    //相关全局变量初始化
#if (FEATURE_ON == FEATURE_IPV6)
    AT_APP_SetFirstActPdpType(TAF_PDP_IPV4V6);
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_ACTED);
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTING);
#else
    AT_APP_SetFirstActPdpType(TAF_PDP_IPV4);
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTING);
#endif

    //MOCKER操作

    //调用被测函数
    AT_AppIpv4PdpActRejProc(pstAppPdpEntity, &stEvent);

    //执行检查
#if (FEATURE_ON == FEATURE_IPV6)
    EXPECT_EQ(AT_PDP_STATE_ACTED, AT_AppGetPdpState(TAF_PDP_IPV6));
#endif
    EXPECT_EQ(AT_PDP_STATE_IDLE, AT_AppGetPdpState(TAF_PDP_IPV4));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppIpv4PdpActRejProc, Test_AT_AppIpv4PdpActRejProc_002)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEvent;

    //参数初始化
    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();

    stEvent.ucCid   = 2;
    stEvent.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;

    //相关全局变量初始化
    AT_APP_SetFirstActPdpType(TAF_PDP_IPV4);
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTING);

    //MOCKER操作

    //调用被测函数
    AT_AppIpv4PdpActRejProc(pstAppPdpEntity, &stEvent);

    //执行检查
    EXPECT_EQ(AT_PDP_STATE_IDLE, AT_AppGetPdpState(TAF_PDP_IPV4));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_NdisIpv4ActCnfProc: public ::testing::Test
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


TEST_F(Test_AT_NdisIpv4ActCnfProc, Test_AT_NdisIpv4ActCnfProc_001)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        stEvent;

    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;

    MOCKER(AT_CtrlConnIndProc)
        .expects(exactly(1))
        .with(any(), eq((AT_USER_TYPE)AT_NDIS_USER));
    MOCKER(AT_ProcNdisRegFCPoint)
        .expects(exactly(1))
        .with(any(), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV4));

#if (FEATURE_ON == FEATURE_IPV6)
    g_enAtFirstNdisActPdpType = TAF_PDP_IPV4V6;
    g_enAtNdisActPdpType = TAF_PDP_IPV4;

    MOCKER(AT_NdisGetState)
        .stubs()
        .with(eq((VOS_UINT8)TAF_PDP_IPV6))
        .will(returnValue((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_IDLE));
    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(eq(stEvent.stCtrl.usClientId), any())
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(AT_NdisPdpActOrig)
        .stubs()
        .with(eq(stEvent.stCtrl.usClientId), any(), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV6));
#endif

    AT_NdisIpv4ActCnfProc(&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisIpv4ActCnfProc, Test_AT_NdisIpv4ActCnfProc_002)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        stEvent;

    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;

    MOCKER(AT_CtrlConnIndProc)
        .expects(exactly(1))
        .with(any(), eq((AT_USER_TYPE)AT_NDIS_USER));
    MOCKER(AT_ProcNdisRegFCPoint)
        .expects(exactly(1))
        .with(any(), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV4));
    MOCKER(AT_GetModemIdFromClient)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_FwSendClientMsg)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

#if (FEATURE_ON == FEATURE_IPV6)
    g_enAtFirstNdisActPdpType = TAF_PDP_IPV4V6;
    g_enAtNdisActPdpType = TAF_PDP_IPV4;

    MOCKER(AT_NdisGetState)
        .stubs()
        .with(eq((VOS_UINT8)TAF_PDP_IPV6))
        .will(returnValue((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_IDLE));
    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(eq(stEvent.stCtrl.usClientId), any())
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(AT_NdisPdpActOrig)
        .stubs()
        .with(eq(stEvent.stCtrl.usClientId), any(), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV6));
#endif

    AT_NdisIpv4ActCnfProc(&stEvent);

    GlobalMockObject::verify();
}


class Test_AT_AppIpv4PdpActCnfProc: public ::testing::Test
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

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_AppIpv4PdpActCnfProc, Test_AT_AppIpv4PdpActCnfProc_001)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent;

    pstAppPdpEntity = (AT_PDP_ENTITY_STRU*)malloc(sizeof(AT_PDP_ENTITY_STRU));
    AT_APP_SetFirstActPdpType(TAF_PDP_IPV4V6);
    AT_APP_SetActPdpType(TAF_PDP_IPV4);
    pstEvent = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU*)malloc(sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    PS_MEM_SET(pstEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    pstEvent->stPcscf.bitOpPrimPcscfAddr = VOS_TRUE;
    pstEvent->stPcscf.bitOpSecPcscfAddr  = VOS_TRUE;
    pstEvent->stCtrl.usClientId = AT_CLIENT_TAB_APP_INDEX;

    MOCKER(AT_AppGetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV6))
        .will(returnValue((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_IDLE));
    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(eq(pstEvent->stCtrl.usClientId ),any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_AppIpv4PdpActCnfProc(pstAppPdpEntity, pstEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

class Test_AT_PS_GetRmNetIdFromCid: public ::testing::Test
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


TEST_F(Test_AT_PS_GetRmNetIdFromCid, Test_AT_PS_GetRmNetIdFromCid_001)
{
    //参数定义
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    VOS_UINT8                           ucCid;
    VOS_UINT8                          *pucRmNetId;
    VOS_UINT32                              ulRslt;

    //参数初始化
    enClientIndex = AT_CLIENT_TAB_APP1_INDEX;
    ucCid = AT_PS_USER_CID_1;
    pucRmNetId = VOS_NULL_PTR;

    //调用被测函数
    ulRslt =AT_PS_GetRmNetIdByCid(enClientIndex, ucCid, pucRmNetId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_GetRmNetIdFromCid, Test_AT_PS_GetRmNetIdFromCid_002)
{
    //参数定义
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    VOS_UINT8                           ucCid;
    VOS_UINT8                          *pucRmNetId;
    VOS_UINT32                              ulRslt;

    //参数初始化
    enClientIndex = AT_CLIENT_BUTT;
    ucCid = AT_PS_USER_CID_1;
    pucRmNetId = (VOS_UINT8 *)malloc(sizeof(VOS_UINT8));

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt =AT_PS_GetRmNetIdByCid(enClientIndex, ucCid, pucRmNetId);
    free(pucRmNetId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_GetRmNetIdFromCid, Test_AT_PS_GetRmNetIdFromCid_003)
{
    //参数定义
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    VOS_UINT8                           ucCid;
    VOS_UINT8                          *pucRmNetId;
    VOS_UINT32                              ulRslt;
    VOS_UINT8                           i;

    //参数初始化
    enClientIndex = AT_CLIENT_TAB_APP1_INDEX;
    ucCid = AT_PS_USER_CID_1;
    pucRmNetId = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    i = 0;
    g_astPsRmNetIdTab[i].enModemId = MODEM_ID_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt =AT_PS_GetRmNetIdByCid(enClientIndex, ucCid, pucRmNetId);
    free(pucRmNetId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_GetRmNetIdFromCid, Test_AT_PS_GetRmNetIdFromCid_004)
{
    //参数定义
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    VOS_UINT8                           ucCid;
    VOS_UINT8                          *pucRmNetId;
    VOS_UINT32                              ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           i;

    //参数初始化
    enClientIndex = AT_CLIENT_TAB_APP_INDEX;
    ucCid = AT_PS_USER_CID_1;
    pucRmNetId = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    enModemId = MODEM_ID_0;
    i = 0;
    g_astPsRmNetIdTab[0].enModemId = MODEM_ID_0;
    g_astPsRmNetIdTab[0].ucUsrCid  = AT_PS_USER_CID_1;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt =AT_PS_GetRmNetIdByCid(enClientIndex, ucCid, pucRmNetId);
    free(pucRmNetId);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_NotifyFcWhenAppPdpModify: public ::testing::Test
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


TEST_F(Test_AT_NotifyFcWhenAppPdpModify, Test_AT_NotifyFcWhenAppPdpModify_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     stEvent;
    VOS_UINT8                           ucRmNetId;

    //参数初始化
    ucIndex = AT_CLIENT_BUTT;
    stEvent.ucCid = AT_PS_USER_CID_1;
    ucRmNetId = 0;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_NotifyFcWhenAppPdpModify(ucIndex, &stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NotifyFcWhenAppPdpModify, Test_AT_NotifyFcWhenAppPdpModify_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     stEvent;
    VOS_UINT8                           ucRmNetId;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    stEvent.ucCid = AT_PS_USER_CID_1;
    ucRmNetId = 0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_NotifyFcWhenPdpModify).expects(exactly(1));

    //调用被测函数
    AT_NotifyFcWhenAppPdpModify(ucIndex, &stEvent);

    //执行检查
    EXPECT_EQ(FC_ID_NIC_1, g_astPsRmNetIdTab[ucRmNetId].enFcId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_ProcAppPsRspEvtPdpActCnf: public ::testing::Test
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


TEST_F(Test_AT_ProcAppPsRspEvtPdpActCnf, Test_AT_ProcAppPsRspEvtPdpActCnf_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;

    //参数初始化
    ucIndex = AT_CLIENT_BUTT;
    stEvent.ucCid = AT_PS_USER_CID_1;

    //MOCKER操作

    //调用被测函数
    AT_ProcAppPsRspEvtPdpActCnf(ucIndex,&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcAppPsRspEvtPdpActCnf, Test_AT_ProcAppPsRspEvtPdpActCnf_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    VOS_UINT8                           ucRmNetId;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_APP1_INDEX;
    stEvent.ucCid = AT_PS_USER_CID_1;
    stEvent.ucRabId = 5;
    stFCPriOrg.ulUsed = VOS_FALSE;
    ucRmNetId = 0;

    //MOCKER操作
    MOCKER(AT_GetFcPriFromMap)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(AT_AppRegFCPoint)
        .expects(exactly(1))
        .with(eq(g_astPsRmNetIdTab[ucRmNetId].enFcId), eq(&stEvent), eq(ucRmNetId))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(AT_SendRnicCgactIpv4ActInd)
        .expects(exactly(1))
        .with(eq(stEvent.ucRabId), eq(ucRmNetId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    AT_ProcAppPsRspEvtPdpActCnf(ucIndex,&stEvent);

    //执行检查
    EXPECT_EQ(0, ucRmNetId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_ProcAppPsRspEvtPdpDeActCnf: public ::testing::Test
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


TEST_F(Test_AT_ProcAppPsRspEvtPdpDeActCnf, Test_AT_ProcAppPsRspEvtPdpDeActCnf_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;

    //参数初始化
    ucIndex = AT_CLIENT_BUTT;
    stEvent.ucCid = AT_PS_USER_CID_1;

    //MOCKER操作

    //调用被测函数
    AT_ProcAppPsRspEvtPdpDeActCnf(ucIndex,&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_ProcAppPsRspEvtPdpDeActCnf, Test_AT_ProcAppPsRspEvtPdpDeActCnf_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucRmNetId;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_APP1_INDEX;
    stEvent.ucCid = AT_PS_USER_CID_1;
    stEvent.ucRabId = 5;
    ucRmNetId = 0;

    //MOCKER操作
    MOCKER(AT_SendRnicPdpDeactInd)
        .expects(exactly(1))
        .with(eq(stEvent.ucRabId), eq(ucRmNetId))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(AT_AppDeRegFCPoint)
        .expects(exactly(1))
        .with(eq(g_astPsRmNetIdTab[ucRmNetId].enFcId), eq(&stEvent))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    AT_ProcAppPsRspEvtPdpDeActCnf(ucIndex,&stEvent);

    //执行检查
    EXPECT_EQ(0, ucRmNetId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_ProcAppPsRspEvtPdpDeactivated: public ::testing::Test
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


TEST_F(Test_AT_ProcAppPsRspEvtPdpDeactivated, Test_AT_ProcAppPsRspEvtPdpDeactivated_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU   stEvent;
    VOS_UINT8                           ucRmNetId;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_APP1_INDEX;
    stEvent.enPdpType= TAF_PDP_IPV4;
    stEvent.ucCid = AT_PS_USER_CID_1;
    ucRmNetId = 0;

    //MOCKER操作
    MOCKER(AT_SendRnicPdpDeactInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_AppDeRegFCPoint)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    AT_ProcAppPsRspEvtPdpDeactivated(ucIndex,&stEvent);

    //执行检查
    EXPECT_EQ(0, ucRmNetId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_ProcAppPsRspEvtPdpDeactivated, Test_AT_ProcAppPsRspEvtPdpDeactivated_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU   stEvent;
    VOS_UINT8                           ucRmNetId;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_APP1_INDEX;
    stEvent.enPdpType = TAF_PDP_IPV6;
    stEvent.ucCid = AT_PS_USER_CID_1;
    ucRmNetId = 0;

    //MOCKER操作
    MOCKER(AT_SendRnicPdpDeactInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_AppDeRegFCPoint)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    AT_ProcAppPsRspEvtPdpDeactivated(ucIndex,&stEvent);

    //执行检查
    EXPECT_EQ(0, ucRmNetId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_ProcAppPsRspEvtPdpDeactivated, Test_AT_ProcAppPsRspEvtPdpDeactivated_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU   stEvent;
    VOS_UINT8                           ucRmNetId;

    //参数初始化
    ucIndex = ucIndex = AT_CLIENT_TAB_APP1_INDEX;
    stEvent.enPdpType = TAF_PDP_IPV4V6;
    stEvent.ucCid = AT_PS_USER_CID_1;
    ucRmNetId = 0;

    //MOCKER操作
    MOCKER(AT_SendRnicPdpDeactInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_AppDeRegFCPoint)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    AT_ProcAppPsRspEvtPdpDeactivated(ucIndex,&stEvent);
    //执行检查
    EXPECT_EQ(0, ucRmNetId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif


TEST_F(Test_AT_ProcAppPsRspEvtPdpDeactivated, Test_AT_ProcAppPsRspEvtPdpDeactivated_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT8                           ucRmNetId;

    //参数初始化
    ucIndex = ucIndex = AT_CLIENT_TAB_APP1_INDEX;
    stEvent.enPdpType = TAF_PDP_TYPE_BUTT;
    stEvent.ucCid = AT_PS_USER_CID_1;
    ucRmNetId = 0;

    //MOCKER操作
    MOCKER(AT_SendRnicPdpDeactInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_AppDeRegFCPoint)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    AT_ProcAppPsRspEvtPdpDeactivated(ucIndex,&stEvent);
    //执行检查
    EXPECT_EQ(0, ucRmNetId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SendRnicCgactIpv4ActInd: public ::testing::Test
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


TEST_F(Test_AT_SendRnicCgactIpv4ActInd, Test_AT_SendRnicCgactIpv4ActInd_001)
{
    //参数定义
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                              ulRslt;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    //参数初始化
    ucRabId = 0;
    ucRmNetId = 0;
    pstMsg = VOS_NULL_PTR;

    //MOCKER操作
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    //调用被测函数
    ulRslt = AT_SendRnicCgactIpv4ActInd(ucRabId, ucRmNetId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendRnicCgactIpv4ActInd, Test_AT_SendRnicCgactIpv4ActInd_002)
{
    //参数定义
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                              ulRslt;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    //参数初始化
    ucRabId = 5;
    ucRmNetId = 1;
    pstMsg = VOS_NULL_PTR;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_SendRnicCgactIpv4ActInd(ucRabId, ucRmNetId);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SendNdisRelReq: public ::testing::Test
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


TEST_F(Test_AT_SendNdisRelReq,Test_AT_SendNdisRelReq_001)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT32                              ulRslt;

    stEvent.stCtrl.usClientId = AT_CLIENT_ID_BUTT;

    MOCKER(AT_FwSendClientMsg)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRslt = AT_SendNdisRelReq(&stEvent);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendNdisRelReq,Test_AT_SendNdisRelReq_002)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_UINT32                              ulRslt;

    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;

    MOCKER(AT_FwSendClientMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));

    ulRslt = AT_SendNdisRelReq(&stEvent);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_SendNdisIPv6PdnInfoCfgReq: public ::testing::Test
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


TEST_F(Test_AT_SendNdisIPv6PdnInfoCfgReq,Test_AT_SendNdisIPv6PdnInfoCfgReq_001)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_PS_IPV6_INFO_IND_STRU           stIPv6RaNotify;
    VOS_UINT32                              ulRslt;

    enModemId = MODEM_ID_0;
    stIPv6RaNotify.stIpv6RaInfo.bitOpMtu = VOS_TRUE;

    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_FwSendClientMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));

    ulRslt = AT_SendNdisIPv6PdnInfoCfgReq(enModemId, &stIPv6RaNotify);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_SendRnicIpv4v6ActInd: public ::testing::Test
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


TEST_F(Test_AT_SendRnicIpv4v6ActInd,Test_AT_SendRnicIpv4v6ActInd_001)
{
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_PID)WUEPS_PID_AT), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_AppSndRnicPdpActInd(TAF_PDP_IPV4V6);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendRnicIpv4v6ActInd,Test_AT_SendRnicIpv4v6ActInd_002)
{
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    AT_AppSndRnicPdpActInd(TAF_PDP_IPV4V6);

    GlobalMockObject::verify();
}


class Test_AT_AppSetFlowCtrl: public ::testing::Test
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


TEST_F(Test_AT_AppSetFlowCtrl,Test_AT_AppSetFlowCtrl_001)
{
    VOS_UINT32                          ulParam1;
    VOS_UINT32                          ulParam2;
    VOS_UINT32                          ulRslt;

    ulParam1 = 0;
    ulParam2 = 0;

    MOCKER(RNIC_StartFlowCtrl)
        .stubs()
        .with(eq((VOS_UINT8)ulParam1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRslt = AT_AppSetFlowCtrl(ulParam1, ulParam2);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_AppClearFlowCtrl: public ::testing::Test
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


TEST_F(Test_AT_AppClearFlowCtrl,Test_AT_AppClearFlowCtrl_001)
{
    VOS_UINT32                          ulParam1;
    VOS_UINT32                          ulParam2;
    VOS_UINT32                          ulRslt;

    ulParam1 = 0;
    ulParam2 = 0;

    MOCKER(RNIC_StopFlowCtrl)
        .stubs()
        .with(eq((VOS_UINT8)ulParam1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRslt = AT_AppClearFlowCtrl(ulParam1, ulParam2);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}

class Test_AT_NdisPsRspPdpDeactEvtCnfProc: public ::testing::Test
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


TEST_F(Test_AT_NdisPsRspPdpDeactEvtCnfProc,Test_AT_NdisPsRspPdpDeactEvtCnfProc_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;

     ucIndex = 0;
    stEvent.enPdpType = TAF_PDP_IPV4;

    MOCKER(AT_NdisStateChangeProc)
        .expects(exactly(1));
    MOCKER(AT_SendNdisRelReq)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(AT_NdisSetState)
        .expects(exactly(1));
    MOCKER(AT_NdisIPv4DeactiveCnfProc)
        .expects(exactly(1));
    MOCKER(AT_DeActiveUsbNet)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_NdisPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);

    GlobalMockObject::verify();
}


class Test_AT_NdisPsRspPdpDeactivatedEvtProc: public ::testing::Test
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


TEST_F(Test_AT_NdisPsRspPdpDeactivatedEvtProc,Test_AT_NdisPsRspPdpDeactivatedEvtProc_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,38,,\"IPV4\"\r\n";

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    ucIndex             = AT_CLIENT_TAB_NDIS_INDEX;
    stEvent.enPdpType   = TAF_PDP_IPV4;
    stEvent.enCause     = TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE;
    stEvent.ucRabId     = 5;
    stEvent.ucCid       = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_NDIS;

    MOCKER(AT_DeActiveUsbNet)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_NdisPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisPsRspPdpDeactivatedEvtProc,Test_AT_NdisPsRspPdpDeactivatedEvtProc_002)
{
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,38,,\"IPV6\"\r\n";

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    ucIndex             = AT_CLIENT_TAB_NDIS_INDEX;
    stEvent.enPdpType   = TAF_PDP_IPV6;
    stEvent.enCause     = TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE;
    stEvent.ucRabId     = 5;
    stEvent.ucCid       = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_NDIS;

    MOCKER(AT_DeActiveUsbNet)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_NdisPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisPsRspPdpDeactivatedEvtProc,Test_AT_NdisPsRspPdpDeactivatedEvtProc_003)
{
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,38,,\"IPV6\"\r\n";

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    ucIndex             = AT_CLIENT_TAB_NDIS_INDEX;
    stEvent.enPdpType   = TAF_PDP_IPV4V6;
    stEvent.enCause     = TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE;
    stEvent.ucRabId     = 5;
    stEvent.ucCid       = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_NDIS;

    MOCKER(AT_DeActiveUsbNet)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_NdisPsRspPdpDeactivatedEvtProc(ucIndex, &stEvent);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

class Test_AT_AppIpv6PdpActRejProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_AppIpv6PdpActRejProc, Test_AT_AppIpv6PdpActRejProc_001)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEventInfo;

    //参数初始化
    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();

    stEventInfo.ucCid = 1;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppIpv6PdpActRejProc(pstAppPdpEntity, &stEventInfo);

    //执行检查
    ASSERT_EQ(AT_PDP_STATE_IDLE, AT_AppGetPdpState(TAF_PDP_IPV6));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_AppIpv4v6PdpActRejProc: public ::testing::Test
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

        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_AppIpv4v6PdpActRejProc, Test_AT_AppIpv4v6PdpActRejProc_001)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEventInfo;

    //参数初始化
    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();

    stEventInfo.ucCid = 1;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppIpv4v6PdpActRejProc(pstAppPdpEntity, &stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppIpv4v6PdpActRejProc, Test_AT_AppIpv4v6PdpActRejProc_002)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEventInfo;

    //参数初始化
    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();

    stEventInfo.ucCid = 1;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_AppSndCallEndedResult)
        .expects(exactly(2));

    //调用被测函数
    AT_AppIpv4v6PdpActRejProc(pstAppPdpEntity, &stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_AppActCnfBackProc: public ::testing::Test
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

        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_AppActCnfBackProc, Test_AT_AppActCnfBackProc_001)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  stEventInfo;

    //参数初始化
    stEventInfo.ucCid = 1;
    stEventInfo.bitOpCause = VOS_TRUE;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED;
    stEventInfo.stPdpAddr.enPdpType = TAF_PDP_IPV4;

    //相关全局变量初始化
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    //MOCKER操作
    MOCKER(TAF_AGENT_FindCidForDial)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));


    //调用被测函数
    AT_AppActCnfBackProc(&stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppActCnfBackProc, Test_AT_AppActCnfBackProc_002)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEventInfo;

    //参数初始化
    stEventInfo.ucCid = 1;
    stEventInfo.bitOpCause = VOS_TRUE;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED;
    stEventInfo.stPdpAddr.enPdpType = TAF_PDP_IPV4;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_AppSndCallEndedResult)
        .expects(exactly(1))
        .with(eq(stEventInfo.ucCid), eq(stEventInfo.enCause), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV6));

    //调用被测函数
    AT_AppActCnfBackProc(&stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppActCnfBackProc, Test_AT_AppActCnfBackProc_003)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEventInfo;

    //参数初始化
    stEventInfo.ucCid = 1;
    stEventInfo.bitOpCause = VOS_TRUE;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED;
    stEventInfo.stPdpAddr.enPdpType = TAF_PDP_IPV6;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_AppSndCallEndedResult)
        .expects(exactly(1))
        .with(eq(stEventInfo.ucCid), eq(stEventInfo.enCause), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV4));

    //调用被测函数
    AT_AppActCnfBackProc(&stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppActCnfBackProc, Test_AT_AppActCnfBackProc_004)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  stEventInfo;

    //参数初始化
    stEventInfo.ucCid = 1;
    stEventInfo.bitOpCause = VOS_TRUE;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED;
    stEventInfo.stPdpAddr.enPdpType = TAF_PDP_IPV6;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppActCnfBackProc(&stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppActCnfBackProc, Test_AT_AppActCnfBackProc_005)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU     *pstEvent;
    pstEvent = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU*)malloc(sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    pstEvent->bitOpCause = VOS_FALSE;
    pstEvent->stPdpAddr.enPdpType = TAF_PDP_IPV4;
    pstEvent->stCtrl.usClientId = AT_CLIENT_TAB_APP_INDEX;

    MOCKER(AT_AppGetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV6))
        .will(returnValue((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_IDLE));
    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(eq(pstEvent->stCtrl.usClientId),any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_AppActCnfBackProc(pstEvent);
    free(pstEvent);

        //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppActCnfBackProc, Test_AT_AppActCnfBackProc_006)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent;
    pstEvent = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU*)malloc(sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    pstEvent->bitOpCause = VOS_FALSE;
    pstEvent->stPdpAddr.enPdpType = TAF_PDP_IPV6;
    pstEvent->stCtrl.usClientId = AT_CLIENT_TAB_APP_INDEX;

    MOCKER(AT_AppGetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV4))
        .will(returnValue((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_IDLE));
    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(eq(pstEvent->stCtrl.usClientId),any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_AppActCnfBackProc(pstEvent);
    free(pstEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

class Test_AT_AppProcIpv6RaInfo: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_AppDhcpv6Reset();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_AppProcIpv6RaInfo, Test_AT_AppProcIpv6RaInfo_001)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstPdpEntity;
    TAF_PS_IPV6_INFO_IND_STRU stRaInfoNotifyInd;

    //参数初始化
    pstPdpEntity = AT_APP_GetPdpEntInfoAddr();
    pstPdpEntity->enIpv6State = AT_PDP_STATE_ACTED;

    stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum = 0;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppProcIpv6RaInfo(&stRaInfoNotifyInd);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppProcIpv6RaInfo, Test_AT_AppProcIpv6RaInfo_002)
{
    //参数定义
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    AT_PDP_ENTITY_STRU                 *pstPdpEntity;
    TAF_PS_IPV6_INFO_IND_STRU stRaInfoNotifyInd;
    VOS_UINT8                           aucPrefix[TAF_IPV6_ADDR_LEN] = {0x23, 0x07, 0x00, 0x02,
                                                                           0x00, 0x02, 0x00, 0x01,
                                                                           0x00, 0x00, 0x00, 0x00,
                                                                           0x00, 0x00, 0x00, 0x00};

    //参数初始化
    pstPdpEntity = AT_APP_GetPdpEntInfoAddr();
    pstPdpEntity->enIpv6State = AT_PDP_STATE_ACTED;

    pstAppRaInfoAddr = AT_APP_GetRaInfoAddr();

    stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum = 1;
    stRaInfoNotifyInd.stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen = 64;
    memcpy(stRaInfoNotifyInd.stIpv6RaInfo.astPrefixList[0].aucPrefix, aucPrefix, TAF_IPV6_ADDR_LEN);

    stRaInfoNotifyInd.stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime = 0xFFFFFFFF;
    stRaInfoNotifyInd.stIpv6RaInfo.astPrefixList[0].ulValidLifeTime     = 0xFFFFFFFF;

    stRaInfoNotifyInd.stIpv6RaInfo.bitOpMtu = VOS_TRUE;
    stRaInfoNotifyInd.stIpv6RaInfo.ulMtu  = 1428;

    //相关全局变量初始化
    pstAppRaInfoAddr->bitOpPrefixAddr = VOS_FALSE;

    //MOCKER操作

    //调用被测函数
    AT_AppProcIpv6RaInfo(&stRaInfoNotifyInd);

    //执行检查
    EXPECT_EQ(VOS_TRUE, pstAppRaInfoAddr->bitOpPrefixAddr);
    EXPECT_EQ(VOS_TRUE, pstAppRaInfoAddr->bitOpPreferredLifetime);
    EXPECT_EQ(VOS_TRUE, pstAppRaInfoAddr->bitOpValidLifetime);
    EXPECT_EQ(VOS_TRUE, pstAppRaInfoAddr->bitOpMtuSize);
    EXPECT_EQ(VOS_TRUE, pstAppRaInfoAddr->bitOpLanAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_Get3gppSmCauseByPsCause: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }

};


TEST_F(Test_AT_Get3gppSmCauseByPsCause, Test_AT_Get3gppSmCauseByPsCause_001)
{
    //参数定义
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT16                          us3gppSmCause;

    //参数初始化
    enCause = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    us3gppSmCause = AT_Get3gppSmCauseByPsCause(enCause);

    //执行检查
    ASSERT_EQ(33, us3gppSmCause);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_NdisStateChangeProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_NdisStateChangeProc, Test_AT_NdisStateChangeProc_001)
{
    //参数定义
    VOS_UINT8                           ucPdpType;
    AT_PDP_STATUS_ENUM_UINT32           enStat;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,33,,\"IPV4\"\r\n";

    //参数初始化
    ucPdpType = TAF_PDP_IPV4;
    enStat = AT_PDP_STATUS_DEACT;

    //相关全局变量初始化
    AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED);

    //MOCKER操作

    //调用被测函数
    AT_NdisStateChangeProc(ucPdpType, enStat, TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_NdisStateChangeProc, Test_AT_NdisStateChangeProc_002)
{
    //参数定义
    VOS_UINT8                           ucPdpType;
    AT_PDP_STATUS_ENUM_UINT32           enStat;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,33,,\"IPV6\"\r\n";

    //参数初始化
    ucPdpType = TAF_PDP_IPV6;
    enStat = AT_PDP_STATUS_DEACT;

    //相关全局变量初始化
    AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED);

    //MOCKER操作

    //调用被测函数
    AT_NdisStateChangeProc(ucPdpType, enStat, TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisStateChangeProc, Test_AT_NdisStateChangeProc_003)
{
    //参数定义
    VOS_UINT8                           ucPdpType;
    AT_PDP_STATUS_ENUM_UINT32           enStat;
    VOS_CHAR                            *pcExpectedStr1 = "\r\n^NDISSTAT:0,33,,\"IPV4\"\r\n";
    VOS_CHAR                            *pcExpectedStr2 = "\r\n^NDISSTAT:0,33,,\"IPV6\"\r\n";

    //参数初始化
    ucPdpType = TAF_PDP_IPV4V6;
    enStat = AT_PDP_STATUS_DEACT;

    //相关全局变量初始化
    AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED);

    //MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpectedStr1, (VOS_UINT32)strlen(pcExpectedStr1)), any());

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpectedStr2, (VOS_UINT32)strlen(pcExpectedStr2)), any());

    //调用被测函数
    AT_NdisStateChangeProc(ucPdpType, enStat, TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisStateChangeProc, Test_AT_NdisStateChangeProc_005)
{
    //参数定义
    VOS_UINT8                           ucPdpType;
    AT_PDP_STATUS_ENUM_UINT32           enStat;
    VOS_CHAR                            *pcExpectedStr1 = "\r\n^NDISSTAT:1,,,\"IPV4\"\r\n";
    VOS_CHAR                            *pcExpectedStr2 = "\r\n^NDISSTAT:1,,,\"IPV6\"\r\n";

    //参数初始化
    ucPdpType = TAF_PDP_IPV4V6;
    enStat = AT_PDP_STATUS_ACT;

    //相关全局变量初始化
    AT_PS_SetPsCallErrCause(0, TAF_PS_CAUSE_SUCCESS);

    //MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpectedStr1, (VOS_UINT32)strlen(pcExpectedStr1)), any());

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpectedStr2, (VOS_UINT32)strlen(pcExpectedStr2)), any());

    //调用被测函数
    AT_NdisStateChangeProc(ucPdpType, enStat, TAF_PS_CAUSE_SUCCESS);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif


TEST_F(Test_AT_NdisStateChangeProc, Test_AT_NdisStateChangeProc_004)
{
    //参数定义
    VOS_UINT8                           ucPdpType;
    AT_PDP_STATUS_ENUM_UINT32           enStat;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,36,,\"IPV4\"\r\n";

    //参数初始化
    ucPdpType = TAF_PDP_IPV4;
    enStat = AT_PDP_STATUS_DEACT;

    //相关全局变量初始化
    AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);

    //MOCKER操作

    //调用被测函数
    AT_NdisStateChangeProc(ucPdpType, enStat, TAF_PS_CAUSE_SUCCESS);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_NdisPsRspPdpActEvtRejProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_NdisPsRspPdpActEvtRejProc, Test_AT_NdisPsRspPdpActEvtRejProc_001)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEventInfo;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex = 0;

    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE;

    //相关全局变量初始化
    g_enAtFirstNdisActPdpType = TAF_PDP_IPV4V6;
    g_enAtNdisActPdpType = TAF_PDP_IPV4V6;

    //MOCKER操作
    MOCKER(AT_NdisPdpActOrig)
        .stubs()
        .with(any(), any(), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV4));


    //调用被测函数
    AT_NdisPsRspPdpActEvtRejProc(ucIndex, &stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisPsRspPdpActEvtRejProc, Test_AT_NdisPsRspPdpActEvtRejProc_002)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEventInfo;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex = 0;

    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE;

    //相关全局变量初始化
    g_enAtFirstNdisActPdpType = TAF_PDP_IPV4V6;
    g_enAtNdisActPdpType = TAF_PDP_IPV4;
    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_ACTING;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_IDLE;

    //MOCKER操作
    MOCKER(AT_NdisPdpActOrig)
        .expects(exactly(1));

    //调用被测函数
    AT_NdisPsRspPdpActEvtRejProc(ucIndex, &stEventInfo);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisPsRspPdpActEvtRejProc, Test_AT_NdisPsRspPdpActEvtRejProc_003)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEventInfo;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,27,,\"IPV6\"\r\n";

    //参数初始化
    ucIndex = 0;

    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;

    //相关全局变量初始化
    g_enAtFirstNdisActPdpType       = TAF_PDP_IPV4V6;
    g_enAtNdisActPdpType            = TAF_PDP_IPV4V6;
    g_stAtNdisDhcpPara.enIpv4State  = AT_PDP_STATE_ACTING;
    g_stAtNdisDhcpPara.enIpv6State  = AT_PDP_STATE_IDLE;

    //MOCKER操作
    MOCKER(AT_NdisPdpActOrig)
        .expects(never());

    //调用被测函数
    AT_NdisPsRspPdpActEvtRejProc(ucIndex, &stEventInfo);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisPsRspPdpActEvtRejProc, Test_AT_NdisPsRspPdpActEvtRejProc_004)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEventInfo;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,27,,\"IPV6\"\r\n";

    //参数初始化
    ucIndex = 0;

    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;

    //相关全局变量初始化
    g_enAtFirstNdisActPdpType       = TAF_PDP_IPV4V6;
    g_enAtNdisActPdpType            = TAF_PDP_IPV6;
    g_stAtNdisDhcpPara.enIpv4State  = AT_PDP_STATE_ACTING;
    g_stAtNdisDhcpPara.enIpv6State  = AT_PDP_STATE_IDLE;

    //MOCKER操作
    MOCKER(AT_NdisPdpActOrig)
        .expects(never());

    //调用被测函数
    AT_NdisPsRspPdpActEvtRejProc(ucIndex, &stEventInfo);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisPsRspPdpActEvtRejProc, Test_AT_NdisPsRspPdpActEvtRejProc_005)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stEventInfo;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "\r\n^NDISSTAT:0,27,,\"IPV4\"\r\n";

    //参数初始化
    ucIndex = 0;

    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;

    //相关全局变量初始化
    g_enAtFirstNdisActPdpType       = TAF_PDP_IPV4;
    g_enAtNdisActPdpType            = TAF_PDP_IPV4;
    g_stAtNdisDhcpPara.enIpv4State  = AT_PDP_STATE_ACTING;
    g_stAtNdisDhcpPara.enIpv6State  = AT_PDP_STATE_IDLE;

    //MOCKER操作
    MOCKER(AT_NdisPdpActOrig)
        .expects(never());

    //调用被测函数
    AT_NdisPsRspPdpActEvtRejProc(ucIndex, &stEventInfo);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_AppIpv4PdpDeactivatedProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_AppIpv4PdpDeactivatedProc, Test_AT_AppIpv4PdpDeactivatedProc_001)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEventInfo;

    //参数初始化
    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();

    stEventInfo.ucCid = 1;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppIpv4PdpDeactivatedProc(pstAppPdpEntity, &stEventInfo);

    //执行检查
    ASSERT_EQ(AT_PDP_STATE_IDLE, AT_AppGetPdpState(TAF_PDP_IPV4));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

class Test_AT_AppIpv6PdpDeactivatedProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_AppIpv6PdpDeactivatedProc, Test_AT_AppIpv6PdpDeactivatedProc_001)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEventInfo;

    //参数初始化
    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();

    stEventInfo.ucCid = 1;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppIpv6PdpDeactivatedProc(pstAppPdpEntity, &stEventInfo);

    //执行检查
    ASSERT_EQ(AT_PDP_STATE_IDLE, AT_AppGetPdpState(TAF_PDP_IPV6));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_AppIpv4v6PdpDeactivatedProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_AppIpv4v6PdpDeactivatedProc, Test_AT_AppIpv4v6PdpDeactivatedProc_001)
{
    //参数定义
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEventInfo;

    //参数初始化
    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();

    stEventInfo.ucCid = 1;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_AppIpv4v6PdpDeactivatedProc(pstAppPdpEntity, &stEventInfo);

    //执行检查
    ASSERT_EQ(AT_PDP_STATE_IDLE, AT_AppGetPdpState(TAF_PDP_IPV4V6));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_NdisActCnfBackProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_NdisActCnfBackProc, Test_AT_NdisActCnfBackProc_001)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEventInfo;

    //参数初始化
    stEventInfo.ucCid = 1;
    stEventInfo.bitOpCause = VOS_TRUE;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED;
    stEventInfo.stPdpAddr.enPdpType = TAF_PDP_IPV4;

    //相关全局变量初始化
    AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    //MOCKER操作
    MOCKER(TAF_AGENT_FindCidForDial)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_NdisPdpActOrig)
        .expects(exactly(1));

    //调用被测函数
    AT_NdisActCnfBackProc(&stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisActCnfBackProc, Test_AT_NdisActCnfBackProc_002)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         stEventInfo;

    //参数初始化
    stEventInfo.ucCid = 1;
    stEventInfo.bitOpCause = VOS_TRUE;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED;
    stEventInfo.stPdpAddr.enPdpType = TAF_PDP_IPV4;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_NdisActCnfBackProc(&stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisActCnfBackProc, Test_AT_NdisActCnfBackProc_003)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         stEvent;

    stEvent.bitOpCause = VOS_FALSE;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV4;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;

    MOCKER(AT_NdisGetState)
        .stubs()
        .with(eq((VOS_UINT8)TAF_PDP_IPV6))
        .will(returnValue((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_IDLE));
    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(eq(stEvent.stCtrl.usClientId), any())
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(AT_NdisPdpActOrig)
        .stubs()
        .with(any(), any(), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV6));

    AT_NdisActCnfBackProc(&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisActCnfBackProc, Test_AT_NdisActCnfBackProc_004)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         stEvent;

    stEvent.bitOpCause = VOS_FALSE;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV6;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;

    MOCKER(AT_NdisGetState)
        .stubs()
        .with(eq((VOS_UINT8)TAF_PDP_IPV4))
        .will(returnValue((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_IDLE));
    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(eq(stEvent.stCtrl.usClientId), any())
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(AT_NdisPdpActOrig)
        .stubs()
        .with(eq(stEvent.stCtrl.usClientId), any(), eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV4));

    AT_NdisActCnfBackProc(&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisActCnfBackProc, Test_AT_NdisActCnfBackProc_005)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         stEventInfo;

    //参数初始化
    stEventInfo.ucCid = 1;
    stEventInfo.bitOpCause = VOS_TRUE;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED;
    stEventInfo.stPdpAddr.enPdpType = TAF_PDP_IPV6;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_NdisActCnfBackProc(&stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisActCnfBackProc, Test_AT_NdisActCnfBackProc_006)
{
    //参数定义
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         stEventInfo;

    //参数初始化
    stEventInfo.ucCid = 1;
    stEventInfo.bitOpCause = VOS_TRUE;
    stEventInfo.enCause = TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE;
    stEventInfo.stPdpAddr.enPdpType = TAF_PDP_IPV6;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_NdisActCnfBackProc(&stEventInfo);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_ResetFlowCtl: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed       = VOS_TRUE;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri      = FC_PRI_4;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask  = 0x20;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId    = MODEM_ID_0;
    }
    void TearDown()
    {
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed       = VOS_FALSE;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri      = FC_PRI_BUTT;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask  = 0;
        g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId    = MODEM_ID_BUTT;
    }
};


TEST_F(Test_AT_ResetFlowCtl, Test_AT_ResetFlowCtl_001)
{
    //参数定义
    VOS_UINT32                          ulParam1;
    VOS_UINT32                          ulParam2;

    //参数初始化
    ulParam1 = 0;
    ulParam2 = FC_ID_NIC_1;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    AT_ResetFlowCtl(ulParam1, ulParam2);

    //执行检查
    EXPECT_EQ(VOS_TRUE, g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed);
    EXPECT_EQ(FC_PRI_4, g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri);
    EXPECT_EQ(0x20, g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask);
    EXPECT_EQ(MODEM_ID_0, g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ResetFlowCtl, Test_AT_ResetFlowCtl_002)
{
    //参数定义
    VOS_UINT32                          ulParam1;
    VOS_UINT32                          ulParam2;

    //参数初始化
    ulParam1 = 0;
    ulParam2 = FC_ID_NIC_1;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    AT_ResetFlowCtl(ulParam1, ulParam2);

    //执行检查
    EXPECT_EQ(VOS_FALSE, g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed);
    EXPECT_EQ(FC_PRI_BUTT, g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri);
    EXPECT_EQ(0, g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask);
    EXPECT_EQ(MODEM_ID_BUTT, g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ValidateDialParam: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PS_DATA_CHANL_CFG_STRU           *pstChanCfg;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_GetSlice)
            .defaults()
            .will(returnValue((VOS_UINT32)0));

        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));

        ucCid                           = 1;
        ucIndex                         = AT_CLIENT_ID_APP;
        g_stATParseCmd.ucCmdOptType     = AT_CMD_OPT_SET_PARA_CMD;
        memset(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName            = (VOS_UINT8*)"^NDISDUP";
        stCmdInfo.pszParam              = (VOS_UINT8 *)"(1,11)";

        AT_InitModemPsCtx(MODEM_ID_0);

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

        gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;
        gastAtParaList[0].usParaLen         = 1;
        gastAtParaList[0].aucPara[0]        = ucCid;
        gastAtParaList[0].ulParaValue       = ucCid;
        gastAtParaList[1].usParaLen         = 1;
        gastAtParaList[1].aucPara[0]        = 1;
        gastAtParaList[1].ulParaValue       = 1;
        gastAtParaList[2].usParaLen         = TAF_MAX_APN_LEN;
        gastAtParaList[2].aucPara[0]        = '1';
        gastAtParaList[2].ulParaValue       = 1;
        gastAtParaList[3].usParaLen         = TAF_MAX_GW_AUTH_USERNAME_LEN;
        gastAtParaList[3].aucPara[0]        = 1;
        gastAtParaList[3].ulParaValue       = 1;
        gastAtParaList[4].usParaLen         = TAF_MAX_GW_AUTH_USERNAME_LEN;
        gastAtParaList[4].aucPara[0]        = 1;
        gastAtParaList[4].ulParaValue       = 1;
        gastAtParaList[5].usParaLen         = 1;
        gastAtParaList[5].aucPara[0]        = 1;
        gastAtParaList[5].ulParaValue       = 1;

        gucAtParaIndex                      = 6;

        pstChanCfg = AT_PS_GetDataChanlCfg(ucIndex, gastAtParaList[0].ulParaValue);
        pstChanCfg->ulUsed              = VOS_TRUE;
        pstChanCfg->ulRmNetId           = UDI_NCM_HSIC_NCM0_ID;
        pstChanCfg->ulRmNetActFlg       = VOS_FALSE;

    }

    void TearDown()
    {

    }
};

TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_CheckApnFormat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucSystemAppConfig;

    // 参数初始化
    ucSystemAppConfig                   = SYSTEM_APP_ANDROID;

    // 初始化全局变量
    ucIndex                             = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_USBCOM_USER;

    AT_SetPcuiPsCallFlag(VOS_TRUE, AT_CLIENT_TAB_PCUI_INDEX);
    // MOCKER操作
    MOCKER(AT_CheckApnFormat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_GetSystemAppConfigAddr)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT8 *)&ucSystemAppConfig));

    MOCKER(TAF_AGENT_SetPdpCidPara)
        .expects(exactly(0))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_SetNdisdupPara(ucIndex);
    AT_SetPcuiPsCallFlag(VOS_FALSE, AT_CLIENT_BUTT);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_003)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER操作
    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRslt = AT_SetNdisdupPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_004)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex                      = 8;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_TOO_MANY_PARA, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_005)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].usParaLen         = 0;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_006)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[1].usParaLen         = 0;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_007)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[2].usParaLen         = TAF_MAX_APN_LEN + 1;

    // MOCKER操作
    MOCKER(AT_CheckApnFormat)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_011)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[2].usParaLen         = TAF_MAX_APN_LEN;

    // MOCKER操作
    MOCKER(AT_CheckApnFormat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_008)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[3].usParaLen         = TAF_MAX_GW_AUTH_USERNAME_LEN + 1;

    // MOCKER操作
    MOCKER(AT_CheckApnFormat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_009)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[4].usParaLen         = TAF_MAX_GW_AUTH_PASSWORD_LEN + 1;

    // MOCKER操作
    MOCKER(AT_CheckApnFormat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_010)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    pstChanCfg->ulRmNetId              = UDI_INVAL_DEV_ID;
    // MOCKER操作
    MOCKER(AT_CheckApnFormat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}



TEST_F(Test_AT_PS_ValidateDialParam, Test_AT_PS_ValidateDialParam_012)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucSystemAppConfig;

    // 参数初始化
    ucSystemAppConfig                   = SYSTEM_APP_ANDROID;

    // 初始化全局变量
    ucIndex                             = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;

    // MOCKER操作
    MOCKER(AT_CheckApnFormat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_GetSystemAppConfigAddr)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT8 *)&ucSystemAppConfig));

#if 0
    MOCKER(AT_PS_ProcDialUp)
        .expects(exactly(1))
        .will(returnValue(AT_OK));
#endif

    MOCKER(TAF_AGENT_SetPdpCidPara)
        .expects(exactly(0))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_SetNdisdupPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcDialUp: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        AT_InitCtx();

        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));

        ucCid                           = 1;
        ucIndex                         = AT_CLIENT_ID_APP;
        g_stATParseCmd.ucCmdOptType     = AT_CMD_OPT_SET_PARA_CMD;
        memset(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName            = (VOS_UINT8*)"^NDISDUP";
        stCmdInfo.pszParam              = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

        gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;
        gastAtParaList[0].usParaLen         = 1;
        gastAtParaList[0].aucPara[0]        = ucCid;
        gastAtParaList[0].ulParaValue       = ucCid;
        gastAtParaList[1].usParaLen         = 1;
        gastAtParaList[1].aucPara[0]        = 1;
        gastAtParaList[1].ulParaValue       = 1;
        gucAtParaIndex                      = 2;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        pstChanCfg = AT_PS_GetDataChanlCfg(ucIndex, gastAtParaList[0].ulParaValue);
        pstChanCfg->ulUsed              = VOS_TRUE;
        pstChanCfg->ulRmNetId           = UDI_NCM_HSIC_NCM0_ID;
        pstChanCfg->ulRmNetActFlg       = VOS_FALSE;

        pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, 0);
        pstPsCallEntity->enIpv4State    = AT_PDP_STATE_ACTED;
        pstPsCallEntity->ucIpv4Cid      = 1;
        pstPsCallEntity->stIpv6RaInfo.bitOpPrefixAddr = VOS_TRUE;

        pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0xFF;
    }

    void TearDown()
    {
        AT_CleanAtChdataCfg(ucIndex, 1);
    }
};


TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_PS_ProcDialCmd(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量
    gastAtParaList[3].usParaLen         = 1;
    gastAtParaList[4].usParaLen         = 1;

    // MOCKER操作
    MOCKER(AT_CheckIpv6Capability)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_PS_ProcDialUp(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_003)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    TAF_PDP_PRIM_CONTEXT_STRU                    stPdpCtxInfo;

    // 参数初始化
    memset(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));
    stPdpCtxInfo.stPdpAddr.enPdpType                = TAF_PDP_IPV4V6;

    // 初始化全局变量
    gastAtParaList[5].usParaLen         = 1;
    pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0x00;
    pstPsCallEntity->enIpv4State        = AT_PDP_STATE_ACTED;
    pstPsCallEntity->enIpv6State        = AT_PDP_STATE_ACTING;

    // MOCKER操作
    MOCKER(TAF_AGENT_GetPdpCidPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_PS_ProcDialUp(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_004)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    TAF_PDP_PRIM_CONTEXT_STRU                    stPdpCtxInfo;

    // 参数初始化
    memset(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));
    stPdpCtxInfo.stPdpAddr.enPdpType                = TAF_PDP_IPV4V6;

    pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0x00;
    pstPsCallEntity->enIpv4State        = AT_PDP_STATE_DEACTING;
    pstPsCallEntity->enIpv6State        = AT_PDP_STATE_DEACTING;

    // 初始化全局变量
    gastAtParaList[5].usParaLen         = 1;

    // MOCKER操作
    MOCKER(TAF_AGENT_GetPdpCidPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_SetPdpCidPara)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    ulRslt = AT_PS_ProcDialUp(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_010)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    TAF_PDP_PRIM_CONTEXT_STRU                    stPdpCtxInfo;

    // 参数初始化
    memset(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));
    stPdpCtxInfo.stPdpAddr.enPdpType                = TAF_PDP_IPV4V6;

    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0x00;
    pstPsCallEntity->enIpv4State        = AT_PDP_STATE_ACTED;
    pstPsCallEntity->enIpv6State        = AT_PDP_STATE_ACTED;
    pstPsCallEntity->stUserInfo.enPortIndex = ucIndex;
    pstPsCallEntity->stUserInfo.enUserIndex = ucIndex;
    pstPsCallEntity->stUserInfo.ucUsrType = AT_APP_USER;
    pstPsCallEntity->stUserInfo.ucUsrCid = 1;

    // 初始化全局变量
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(At_SendResultData)
        .expects(exactly(2));

    // 调用被测函数
    ulRslt = AT_PS_ProcDialUp(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);
    GlobalMockObject::verify();
}
#endif

TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_005)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化
    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, 0);
    pstPsCallEntity->ulUsedFlg          = VOS_TRUE;
    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, 1);
    pstPsCallEntity->ulUsedFlg          = VOS_TRUE;
    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, 2);
    pstPsCallEntity->ulUsedFlg          = VOS_TRUE;

    // 初始化全局变量
    gastAtParaList[5].usParaLen         = 1;

    // MOCKER操作
    MOCKER(TAF_AGENT_GetPdpCidPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_SetPdpCidPara)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_PS_ProcDialUp(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_006)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU                    stPdpCtxInfo;

    // 参数初始化
    memset(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));
    stPdpCtxInfo.stPdpAddr.enPdpType                = TAF_PDP_IPV4V6;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(TAF_AGENT_GetPdpCidPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_PS_ProcDialUp(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_007)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU                    stPdpCtxInfo;

    // 参数初始化
    memset(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));
    stPdpCtxInfo.stPdpAddr.enPdpType                = TAF_PDP_IPV4V6;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(TAF_AGENT_GetPdpCidPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_PS_CallOrig)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));
    // 调用被测函数
    ulRslt = AT_PS_ProcDialUp(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_008)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU                    stPdpCtxInfo;

    // 参数初始化
    PS_MEM_SET(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));
    stPdpCtxInfo.stPdpAddr.enPdpType = TAF_PDP_IPV4;
    gastAtParaList[2].usParaLen   = 10;
    PS_MEM_CPY(gastAtParaList[2].aucPara, (VOS_UINT8 *)"huawei.com", 10);
    gastAtParaList[3].usParaLen   = 4;
    PS_MEM_CPY(gastAtParaList[3].aucPara, (VOS_UINT8 *)"name", 4);
    gastAtParaList[4].usParaLen   = 10;
    PS_MEM_CPY(gastAtParaList[4].aucPara, (VOS_UINT8 *)"password", 8);

    // 初始化全局变量

    // MOCKER操作

    MOCKER(TAF_AGENT_GetPdpCidPara)
        .expects(exactly(1))
        //.with(outBoundP((void *)&stPdpCtxInfo, (VOS_UINT32)sizeof(stPdpCtxInfo)), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_PS_ProcDialCmd(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialUp, Test_AT_PS_ProcDialUp_009)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU                    stPdpCtxInfo;

    // 参数初始化
    PS_MEM_SET(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));
    stPdpCtxInfo.stPdpAddr.enPdpType                = TAF_PDP_IPV4;
    pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0x00;

    // 初始化全局变量

    // MOCKER操作

    MOCKER(TAF_AGENT_GetPdpCidPara)
        .expects(exactly(1))
        //.with(outBoundP((void *)&stPdpCtxInfo, (VOS_UINT32)sizeof(stPdpCtxInfo)), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_PS_ProcConflictDialUpWithCurrCall)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_PS_ProcDialCmd(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}

class Test_AT_PS_SetCid2CurrCall: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        usClientId                      = AT_CLIENT_ID_MODEM;
        ucCid                           = 1;
        AT_InitCtx();
        pstPsCallEntity = AT_PS_GetCallEntity(usClientId, 0);
        pstPsCallEntity->enIpv4State    = AT_PDP_STATE_ACTED;
        pstPsCallEntity->ucIpv4Cid      = 1;

    }

    void TearDown()
    {

    }
};


TEST_F(Test_AT_PS_SetCid2CurrCall, Test_AT_PS_SetCid2CurrCall_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_SetCid2CurrCall(usClientId, 0, TAF_PDP_IPV4, 1);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SetCid2CurrCall, Test_AT_PS_SetCid2CurrCall_002)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_SetCid2CurrCall(usClientId, 0, TAF_PDP_IPV6, 1);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SetCid2CurrCall, Test_AT_PS_SetCid2CurrCall_003)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_SetCid2CurrCall(usClientId, 0, TAF_PDP_IPV4V6, 1);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SetCid2CurrCall, Test_AT_PS_SetCid2CurrCall_004)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_SetCid2CurrCall(usClientId, 0, TAF_PDP_TYPE_BUTT, 1);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_PdpAddrProc: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCid       = 1;
        ucCallId    = 0;
        memset(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
        stCallEvt.ucCid   = ucCid;
        stCallEvt.ucRabId = 1;
        stCallEvt.stDns.bitOpPrimDnsAddr = VOS_TRUE;
        stCallEvt.stDns.bitOpSecDnsAddr = VOS_TRUE;
        stCallEvt.stPcscf.bitOpPrimPcscfAddr   = VOS_TRUE;
        stCallEvt.stPcscf.bitOpSecPcscfAddr    = VOS_TRUE;
        stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_MODEM;

        AT_InitCtx();

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stCallEvt.stCtrl.usClientId);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]     = 0;

        pstCallEntity = AT_PS_GetCallEntity(stCallEvt.stCtrl.usClientId, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEntity->stUserInfo.ucUsrType   = AT_MODEM_USER;
        pstCallEntity->stUserInfo.ucUsrCid    = ucCid;

        pstCallEntity->enCurrPdpType          = AT_PDP_IPV4;
        pstCallEntity->ucIpv4Cid              = ucCid;
#if (FEATURE_ON == FEATURE_IPV6)
        pstCallEntity->enIpv6State            = AT_PDP_STATE_IDLE;
        pstCallEntity->ucIpv6Cid              = ucCid;
#endif
        pstCallEntity->stUsrDialParam.enPdpType               = TAF_PDP_IPV4;
        pstCallEntity->stUsrDialParam.ulPrimIPv4DNSValidFlag  = VOS_FALSE;
        pstCallEntity->stUsrDialParam.ulSndIPv4DNSValidFlag   = VOS_FALSE;

    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(stCallEvt.stCtrl.usClientId, 1);
        AT_PS_FreeCallEntity(stCallEvt.stCtrl.usClientId, 0);
    }
};


TEST_F(Test_AT_PS_PdpAddrProc, Test_AT_PS_PdpAddrProc_001)
{
    // 变量声明
    AT_DHCP_CONFIG_STRU                 stDhcpConfig;

    // 参数初始化
    memset(&stDhcpConfig, 0x00,sizeof(AT_DHCP_CONFIG_STRU));
    stDhcpConfig.ulPrimDNS  = 1;
    stDhcpConfig.ulSndDNS   = 1;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_PdpAddrProc(ucCallId, &stDhcpConfig, &stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_IPV6)

class Test_AT_PS_ProcIpv4CallConnected: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU              stCallEntity;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCid       = 1;
        ucCallId    = 0;
        memset(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
        stCallEvt.stCtrl.usClientId = AT_CLIENT_TAB_MODEM_INDEX;
        stCallEvt.ucCid   = ucCid;
        stCallEvt.ucRabId = 1;
        stCallEvt.stPdpAddr.enPdpType = AT_PDP_IPV4;
        stCallEvt.stDns.bitOpPrimDnsAddr = VOS_TRUE;
        stCallEvt.stDns.bitOpSecDnsAddr = VOS_TRUE;
        stCallEvt.stPcscf.bitOpPrimPcscfAddr   = VOS_TRUE;
        stCallEvt.stPcscf.bitOpSecPcscfAddr    = VOS_TRUE;

        gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].UserType     = AT_HSIC1_USER;
        gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].CmdCurrentOpt= AT_CMD_INVALID;

        AT_InitCtx();

        pstCommPsCtx = AT_GetCommPsCtxAddr();
        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(AT_CLIENT_TAB_MODEM_INDEX);

        pstModemPsCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
        pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId  = UDI_ACM_HSIC_ACM1_ID;
        AT_PS_SetPsCallErrCause(AT_CLIENT_TAB_MODEM_INDEX, TAF_PS_CAUSE_SUCCESS);

        pstModemPsCtx->aucCidToIndexTbl[ucCid]                   = 0;
        pstCommPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum      = 1;
        pstCommPsCtx->stIpv6BackProcExtCauseTbl.aenPsCause[0]   = 289;

        memset(&stCallEntity, 0x00, sizeof(AT_PS_CALL_ENTITY_STRU));
        stCallEntity.enIpv4State      = AT_PDP_STATE_ACTED;
        stCallEntity.enCurrPdpType    = AT_PDP_IPV4;

        pstCallEntity = AT_PS_GetCallEntity(AT_CLIENT_TAB_MODEM_INDEX, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEntity->stUserInfo.ucUsrType   = AT_HSIC1_USER;
        pstCallEntity->stUserInfo.ucUsrCid    = ucCid;

        pstCallEntity->enCurrPdpType          = AT_PDP_IPV4;
        pstCallEntity->enIpv6State            = AT_PDP_STATE_IDLE;
        pstCallEntity->ucIpv4Cid              = ucCid;
        pstCallEntity->ucIpv6Cid              = ucCid;

        pstCallEntity->stUsrDialParam.enPdpType               = TAF_PDP_IPV4;
        pstCallEntity->stUsrDialParam.ulPrimIPv4DNSValidFlag  = VOS_TRUE;
        pstCallEntity->stUsrDialParam.ulSndIPv4DNSValidFlag   = VOS_TRUE;

    }

    void TearDown()
    {
        AT_CleanAtChdataCfg(AT_CLIENT_TAB_MODEM_INDEX, 1);
        AT_PS_FreeCallIdToCid(AT_CLIENT_TAB_MODEM_INDEX, 1);
        AT_PS_FreeCallEntity(AT_CLIENT_TAB_MODEM_INDEX, 0);
    }
};


TEST_F(Test_AT_PS_ProcIpv4CallConnected, Test_AT_PS_ProcIpv4ConnectedCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcPrint = (VOS_CHAR *)"\r\n^DCONN:1,\"IPV4\"\r\n";

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_DHCPServerSetUp)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_MODEM_INDEX), mirror((VOS_UINT8 *)pcPrint, (VOS_UINT32)VOS_StrLen(pcPrint)), any());

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv4State);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4CallConnected, Test_AT_PS_ProcIpv4ConnectedCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_LenStr2IpAddr)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(AT_DHCPServerSetUp)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4CallConnected, Test_AT_PS_ProcIpv4ConnectedCnf_003)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化
    pstCallEntity->stUsrDialParam.ulPrimIPv4DNSValidFlag  = VOS_FALSE;
    pstCallEntity->stUsrDialParam.ulSndIPv4DNSValidFlag   = VOS_FALSE;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_DHCPServerSetUp)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4CallConnected, Test_AT_PS_ProcIpv4ConnectedCnf_004)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           *pcDconn = (VOS_UINT8 *)"\r\n^DCONN:1,\"IPV4\"\r\n";
    VOS_UINT8                           *pcDend  = (VOS_UINT8 *)"\r\n^DEND:1,127,\"IPV6\"\r\n";
    VOS_UINT8                           ucDconnLen = VOS_StrLen((VOS_CHAR *)pcDconn);
    VOS_UINT8                           ucDendLen  = VOS_StrLen((VOS_CHAR *)pcDend);
    VOS_UINT8                           ucActCid;
    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosQueryPara;

    PS_MEM_SET(&stQosQueryPara, 0 , sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));

    stQosQueryPara.ucQosFlag = VOS_TRUE;
    stQosQueryPara.ucMinQosFlag = VOS_TRUE;

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType               = TAF_PDP_IPV4V6;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_DHCPServerSetUp)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ucActCid = 12;

    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(any(), outBoundP((VOS_UINT8 *)&ucActCid, (VOS_UINT32)sizeof(ucActCid)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_SetPdpCidQosPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_GetPdpCidQosPara)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((TAF_PS_PDP_QOS_QUERY_PARA_STRU *)&stQosQueryPara, (VOS_UINT32)sizeof(stQosQueryPara)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_PS_CallOrig)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDconn, (VOS_UINT32)ucDconnLen), any());

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDend, (VOS_UINT32)ucDendLen), any());

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4CallConnected, Test_AT_PS_ProcIpv4ConnectedCnf_005)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcDconnIpv4 = (VOS_CHAR *)"\r\n^DCONN:1,\"IPV4\"\r\n";
    VOS_UINT8                           ucActCid;
    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosQueryPara;

    PS_MEM_SET(&stQosQueryPara, 0 , sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));

    stQosQueryPara.ucQosFlag = VOS_TRUE;
    stQosQueryPara.ucMinQosFlag = VOS_TRUE;

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType               = TAF_PDP_IPV4V6;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_DHCPServerSetUp)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ucActCid = 12;

    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(any(), outBoundP((VOS_UINT8 *)&ucActCid, (VOS_UINT32)sizeof(ucActCid)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_SetPdpCidQosPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_GetPdpCidQosPara)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((TAF_PS_PDP_QOS_QUERY_PARA_STRU *)&stQosQueryPara, (VOS_UINT32)sizeof(stQosQueryPara)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_PS_CallOrig)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDconnIpv4, VOS_StrLen(pcDconnIpv4)), any());

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4CallConnected, Test_AT_PS_ProcIpv4ConnectedCnf_006)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcDconn = (VOS_CHAR *)"\r\n^DCONN:1,\"IPV4\"\r\n";
    VOS_CHAR                           *pcDend  = (VOS_CHAR *)"\r\n^DEND:1,127,\"IPV6\"\r\n";

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
    pstCallEntity->enCurrPdpType         = TAF_PDP_IPV4V6;
    stCallEvt.bitOpCause      = VOS_TRUE;
    stCallEvt.enCause         = TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_DHCPServerSetUp)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));
#if (FEATURE_ON == FEATURE_IPV6)
    MOCKER(AT_PS_SetupSingleStackConn)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));
#endif
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDconn, VOS_StrLen(pcDconn)), any());

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDend, VOS_StrLen(pcDend)), any());

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4CallConnected, Test_AT_PS_ProcIpv4ConnectedCnf_007)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcDconn = (VOS_CHAR *)"\r\n^DCONN:1,\"IPV4\"\r\n";
    VOS_CHAR                           *pcDend  = (VOS_CHAR *)"\r\n^DEND:1,306,\"IPV6\"\r\n";

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
    pstCallEntity->enCurrPdpType         = TAF_PDP_IPV4V6;
    stCallEvt.bitOpCause      = VOS_TRUE;
    stCallEvt.enCause         = TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_DHCPServerSetUp)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_PS_SetupSingleStackConn)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDconn, VOS_StrLen(pcDconn)), any());

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDend, VOS_StrLen(pcDend)), any());

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcIpv6CallConnected: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU              stCallEntity;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx;
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucCid       = 1;
        ucCallId    = 0;
        ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
        memset(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
        stCallEvt.stCtrl.usClientId = AT_CLIENT_TAB_MODEM_INDEX;
        stCallEvt.ucCid   = ucCid;
        stCallEvt.ucRabId = 1;
        stCallEvt.stPdpAddr.enPdpType = AT_PDP_IPV6;

        stCallEvt.stIpv6Dns.bitOpPrimDnsAddr       = VOS_TRUE;
        stCallEvt.stIpv6Dns.bitOpSecDnsAddr        = VOS_TRUE;
        stCallEvt.stIpv6Pcscf.bitOpPrimPcscfAddr   = VOS_TRUE;
        stCallEvt.stIpv6Pcscf.bitOpSecPcscfAddr    = VOS_TRUE;

        gastAtClientTab[ucIndex].UserType       = AT_HSIC2_USER;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        AT_InitCtx();

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);
        pstCommPsCtx = AT_GetCommPsCtxAddr();

        pstModemPsCtx->astChannelCfg[ucCid].ulUsed          = VOS_TRUE;
        pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId       = UDI_ACM_HSIC_ACM2_ID;
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_SUCCESS);

        pstModemPsCtx->aucCidToIndexTbl[ucCid]                   = 0;

        pstCommPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum      = 1;
        pstCommPsCtx->stIpv6BackProcExtCauseTbl.aenPsCause[0]   = 289;

        memset(&stCallEntity, 0x00, sizeof(AT_PS_CALL_ENTITY_STRU));
        stCallEntity.enIpv4State      = AT_PDP_STATE_ACTED;
        stCallEntity.enCurrPdpType    = AT_PDP_IPV6;

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex = ucIndex;
        pstCallEntity->stUserInfo.enUserIndex = ucIndex;
        pstCallEntity->stUserInfo.ucUsrType   = AT_HSIC2_USER;
        pstCallEntity->stUserInfo.ucUsrCid    = ucCid;

        pstCallEntity->enCurrPdpType          = AT_PDP_IPV6;
        pstCallEntity->enIpv4State            = AT_PDP_STATE_IDLE;
        pstCallEntity->enIpv6State            = AT_PDP_STATE_IDLE;
        pstCallEntity->ucIpv4Cid              = ucCid;
        pstCallEntity->ucIpv6Cid              = ucCid;

        pstCallEntity->stUsrDialParam.enPdpType               = AT_PDP_IPV6;
        pstCallEntity->stUsrDialParam.ulPrimIPv4DNSValidFlag  = VOS_TRUE;
        pstCallEntity->stUsrDialParam.ulSndIPv4DNSValidFlag   = VOS_TRUE;

    }

    void TearDown()
    {
        AT_CleanAtChdataCfg(ucIndex, 1);
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, 0);
    }
};


TEST_F(Test_AT_PS_ProcIpv6CallConnected, Test_AT_PS_ProcIpv6ConnectedCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv6State);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6CallConnected, Test_AT_PS_ProcIpv6ConnectedCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcDend  = (VOS_CHAR *)"\r\n^DEND:1,127,\"IPV4\"\r\n";
    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosQueryPara;
    VOS_UINT8                           ucActCid;

    PS_MEM_SET(&stQosQueryPara, 0 , sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));

    stQosQueryPara.ucQosFlag = VOS_TRUE;
    stQosQueryPara.ucMinQosFlag = VOS_TRUE;

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType = AT_PDP_IPV4V6;
    pstCallEntity->enCurrPdpType         = AT_PDP_IPV4V6;

    // 初始化全局变量

    // MOCKER操作
#if(FEATURE_ON == FEATURE_LTE)
    ucActCid = 12;
#else
    ucActCid = 11;
#endif

    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(any(), outBoundP((VOS_UINT8 *)&ucActCid, (VOS_UINT32)sizeof(ucActCid)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_SetPdpCidQosPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_GetPdpCidQosPara)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((TAF_PS_PDP_QOS_QUERY_PARA_STRU *)&stQosQueryPara, (VOS_UINT32)sizeof(stQosQueryPara)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_PS_CallOrig)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDend, VOS_StrLen(pcDend)), any());

  // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv6State);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6CallConnected, Test_AT_PS_ProcIpv6ConnectedCnf_003)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosQueryPara;
    VOS_UINT8                           ucActCid;

    PS_MEM_SET(&stQosQueryPara, 0 , sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));

    stQosQueryPara.ucQosFlag = VOS_TRUE;
    stQosQueryPara.ucMinQosFlag = VOS_TRUE;

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType = AT_PDP_IPV4V6;
    pstCallEntity->enCurrPdpType         = AT_PDP_IPV4V6;

    // 初始化全局变量

    // MOCKER操作
#if(FEATURE_ON == FEATURE_LTE)
    ucActCid = 12;
#else
    ucActCid = 11;
#endif

    MOCKER(TAF_AGENT_FindCidForDial)
        .expects(exactly(1))
        .with(any(), outBoundP((VOS_UINT8 *)&ucActCid, (VOS_UINT32)sizeof(ucActCid)))
        .will(returnValue((VOS_UINT32)VOS_OK));

   MOCKER(TAF_AGENT_SetPdpCidQosPara)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_GetPdpCidQosPara)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((TAF_PS_PDP_QOS_QUERY_PARA_STRU *)&stQosQueryPara, (VOS_UINT32)sizeof(stQosQueryPara)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_PS_CallOrig)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv6State);
    EXPECT_EQ(AT_PDP_STATE_ACTING, pstCallEntity->enIpv4State);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6CallConnected, Test_AT_PS_ProcIpv6ConnectedCnf_004)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcDend  = (VOS_CHAR *)"\r\n^DEND:1,307,\"IPV4\"\r\n";

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
    pstCallEntity->enCurrPdpType         = TAF_PDP_IPV4V6;
    stCallEvt.bitOpCause      = VOS_TRUE;
    stCallEvt.enCause         = TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDend, VOS_StrLen(pcDend)), any());

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6CallConnected, Test_AT_PS_ProcIpv6ConnectedCnf_005)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
    pstCallEntity->enCurrPdpType         = TAF_PDP_IPV4V6;
    stCallEvt.bitOpCause      = VOS_TRUE;
    stCallEvt.enCause         = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_PS_SetupSingleStackConn)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(AT_CLIENT_TAB_MODEM_INDEX, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}

class Test_AT_PS_ProcIpv4v6CallConnected: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx;
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();

        ucCid       = 1;
        ucCallId    = 0;
        ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
        gastAtClientTab[ucIndex].UserType         = AT_HSIC3_USER;
        gastAtClientTab[ucIndex].CmdCurrentOpt    = AT_CMD_INVALID;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);
        pstCommPsCtx = AT_GetCommPsCtxAddr();

        pstModemPsCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
        pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId = UDI_ACM_HSIC_ACM3_ID;
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_SUCCESS);

        memset(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
        stCallEvt.ucCid   = ucCid;
        stCallEvt.ucRabId = 1;
        stCallEvt.stPdpAddr.enPdpType = AT_PDP_IPV4V6;

        stCallEvt.stIpv6Dns.bitOpPrimDnsAddr       = VOS_TRUE;
        stCallEvt.stIpv6Dns.bitOpSecDnsAddr        = VOS_TRUE;
        stCallEvt.stIpv6Pcscf.bitOpPrimPcscfAddr   = VOS_TRUE;
        stCallEvt.stIpv6Pcscf.bitOpSecPcscfAddr    = VOS_TRUE;

        pstModemPsCtx->aucCidToIndexTbl[ucCid]                   = 0;

        pstCommPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum      = 1;
        pstCommPsCtx->stIpv6BackProcExtCauseTbl.aenPsCause[0]   = 289;

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex = ucIndex;
        pstCallEntity->stUserInfo.enUserIndex = ucIndex;
        pstCallEntity->stUserInfo.ucUsrType   = AT_HSIC3_USER;
        pstCallEntity->stUserInfo.ucUsrCid    = ucCid;

        pstCallEntity->enCurrPdpType          = AT_PDP_IPV4V6;
        pstCallEntity->enIpv4State            = AT_PDP_STATE_IDLE;
        pstCallEntity->enIpv6State            = AT_PDP_STATE_IDLE;
        pstCallEntity->ucIpv4Cid              = ucCid;
        pstCallEntity->ucIpv6Cid              = ucCid;

        pstCallEntity->stUsrDialParam.enPdpType               = AT_PDP_IPV4V6;
        pstCallEntity->stUsrDialParam.ulPrimIPv4DNSValidFlag  = VOS_TRUE;
        pstCallEntity->stUsrDialParam.ulSndIPv4DNSValidFlag   = VOS_TRUE;

    }

    void TearDown()
    {
        AT_CleanAtChdataCfg(ucIndex, 1);
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, 0);
    }
};


TEST_F(Test_AT_PS_ProcIpv4v6CallConnected, Test_AT_PS_ProcIpv4v6ConnectedCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcPrint = (VOS_CHAR *)"\r\n^DCONN:1,\"IPV4\"\r\n";

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcPrint, VOS_StrLen(pcPrint)), any());

    // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv6State);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4v6CallConnected, Test_AT_PS_ProcIpv4v6ConnectedCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcDconn = (VOS_CHAR *)"\r\n^DCONN:1,\"IPV4\"\r\n";

    // 参数初始化
    pstCallEntity->stUsrDialParam.enPdpType = AT_PDP_IPV4V6;
    pstCallEntity->enCurrPdpType         = AT_PDP_IPV4V6;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDconn, VOS_StrLen(pcDconn)), any());

  // 调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex, (VOS_VOID *)&stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


class Test_AT_PS_GenIpv6LanAddrWithRadomIID: public ::testing::Test
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


TEST_F(Test_AT_PS_GenIpv6LanAddrWithRadomIID, Test_AT_PS_GenIpv6LanAddrWithRadomIID_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucProFrix[AT_IPV6_ADDR_PREFIX_BYTE_LEN];
    VOS_UINT32                          ulLen = AT_IPV6_ADDR_PREFIX_BYTE_LEN + 1;
    VOS_UINT8                           aucIpv6Len[AT_IPV6_ADDR_PREFIX_BYTE_LEN];
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_PS_GenIpv6LanAddrWithRadomIID(aucProFrix, ulLen, aucIpv6Len);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcIpv6RaInfo: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    TAF_PS_IPV6_INFO_IND_STRU stRaInfoNotifyInd;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx;
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();

        ucCid       = 1;
        ucCallId    = 0;
        ucIndex     = AT_CLIENT_TAB_APP_INDEX;
        memset(&stRaInfoNotifyInd, 0x00, sizeof(TAF_PS_IPV6_INFO_IND_STRU));
        stRaInfoNotifyInd.ucCid                 = ucCid;
        stRaInfoNotifyInd.ucRabId               = 1;
        stRaInfoNotifyInd.stIpv6RaInfo.bitOpMtu = VOS_TRUE;
        stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum = 1;

        gastAtClientTab[ucIndex].UserType       = AT_APP_USER;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_SUCCESS);

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]                   = 0;

        pstCommPsCtx = AT_GetCommPsCtxAddr();

        pstCommPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum      = 1;
        pstCommPsCtx->stIpv6BackProcExtCauseTbl.aenPsCause[0]   = 289;

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex = ucIndex;
        pstCallEntity->stUserInfo.enUserIndex  = ucIndex;
        pstCallEntity->stUserInfo.ucUsrType   = AT_APP_USER;
        pstCallEntity->stUserInfo.ucUsrCid    = ucCid;

        pstCallEntity->enCurrPdpType          = AT_PDP_IPV6;
        pstCallEntity->enIpv6State            = AT_PDP_STATE_ACTED;
        pstCallEntity->ucIpv4Cid              = ucCid;
        pstCallEntity->ucIpv6Cid              = ucCid;

    }

    void TearDown()
    {
        AT_CleanAtChdataCfg(ucIndex,1);
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, 0);
    }
};


TEST_F(Test_AT_PS_ProcIpv6RaInfo, Test_AT_PS_ProcIpv6RaInfo_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pcDconn  = (VOS_CHAR *)"\r\n^DCONN:1,\"IPV6\"\r\n";

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDconn, VOS_StrLen(pcDconn)), any());

    // 调用被测函数
    ulRslt = AT_RcvTafPsEvtReportRaInfo(ucIndex, (VOS_VOID *)&stRaInfoNotifyInd);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6RaInfo, Test_AT_PS_ProcIpv6RaInfo_002)
{
    // 变量声明

    // 参数初始化
    pstCallEntity->ucIpv4Cid              = AT_PS_CALL_INVALID_CID;
    pstCallEntity->ucIpv6Cid              = AT_PS_CALL_INVALID_CID;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcIpv6RaInfo(&stRaInfoNotifyInd);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6RaInfo, Test_AT_PS_ProcIpv6RaInfo_003)
{
    // 变量声明

    // 参数初始化
    stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum  = 0;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcIpv6RaInfo(&stRaInfoNotifyInd);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6RaInfo, Test_AT_PS_ProcIpv6RaInfo_004)
{
    // 变量声明
    VOS_CHAR                           *pcDconn  = (VOS_CHAR *)"\r\n^DCONN:1,\"IPV6\"\r\n";

    // 参数初始化
    pstCallEntity->stUserInfo.ucUsrType = AT_APP_USER;
    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcDconn, VOS_StrLen(pcDconn)), any());

    // 调用被测函数
    AT_PS_ProcIpv6RaInfo(&stRaInfoNotifyInd);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_SetupSingleStackConn: public ::testing::Test
{
public:
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        ucCallId    = 0;
        usClientId = AT_CLIENT_ID_MODEM;

        AT_InitCtx();
        pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
        pstCallEntity->enIpv4State      = AT_PDP_STATE_ACTED;

    }

    void TearDown()
    {
        AT_CleanAtChdataCfg(usClientId, 1);
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, 0);
    }
};


TEST_F(Test_AT_PS_SetupSingleStackConn, Test_AT_PS_SetupSingleStackConn_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_PS_SetupSingleStackConn(usClientId, ucCallId, AT_PDP_IPV4V6);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SetupSingleStackConn, Test_AT_PS_SetupSingleStackConn_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_PS_SetupSingleStackConn(usClientId, ucCallId, AT_PDP_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_PS_ProcDualStackCallConn: public ::testing::Test
{
public:
    VOS_UINT8                           ucCallId;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCallId    = 0;
        memset(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
        stEvent.bitOpCause              = VOS_FALSE;
        stEvent.stPdpAddr.enPdpType                 = TAF_PDP_IPV4V6;
    }

    void TearDown()
    {
    }
};


TEST_F(Test_AT_PS_ProcDualStackCallConn, Test_AT_PS_ProcDualStackCallConn_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcDualStackCallConn(ucCallId, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcIpv4ConnSuccFallback: public ::testing::Test
{
public:
    VOS_UINT8                           ucCallId;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCallId    = 0;
        memset(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
        AT_InitCtx();
        pstCallEntity = AT_PS_GetCallEntity(0, ucCallId);
        pstCallEntity->enCurrPdpType = TAF_PDP_IPV6;
    }

    void TearDown()
    {
        AT_PS_FreeCallEntity(0, 0);
    }
};


TEST_F(Test_AT_PS_ProcIpv4ConnSuccFallback, Test_AT_PS_ProcIpv4ConnSuccFallback_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcIpv4ConnSuccFallback(ucCallId, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcIpv6ConnSuccFallback: public ::testing::Test
{
public:
    VOS_UINT8                           ucCallId;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCallId    = 0;
        memset(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
        AT_InitCtx();
        pstCallEntity = AT_PS_GetCallEntity(0, ucCallId);
    }

    void TearDown()
    {
        AT_PS_FreeCallEntity(0, 0);
    }
};


TEST_F(Test_AT_PS_ProcIpv6ConnSuccFallback, Test_AT_PS_ProcIpv6ConnSuccFallback_001)
{
    // 变量声明

    // 参数初始化
    pstCallEntity->enCurrPdpType = TAF_PDP_IPV6;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcIpv6ConnSuccFallback(ucCallId, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6ConnSuccFallback, Test_AT_PS_ProcIpv6ConnSuccFallback_002)
{
    // 变量声明

    // 参数初始化
    pstCallEntity->enCurrPdpType = TAF_PDP_IPV4;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcIpv6ConnSuccFallback(ucCallId, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcCallConnectedEvent: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();

        ucCid       = 1;
        ucCallId    = 0;
        memset(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
        stCallEvt.ucCid   = ucCid;
        stCallEvt.ucRabId = 1;
        stCallEvt.stPdpAddr.enPdpType = AT_PDP_IPV4;
        stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_MODEM;

        AT_PS_SetPsCallErrCause(stCallEvt.stCtrl.usClientId, TAF_PS_CAUSE_SUCCESS);

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stCallEvt.stCtrl.usClientId);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]                   = 0;

        pstCallEntity = AT_PS_GetCallEntity(stCallEvt.stCtrl.usClientId, ucCallId);
        pstCallEntity->enCurrPdpType          = AT_PDP_IPV4;
        pstCallEntity->enIpv6State            = AT_PDP_STATE_IDLE;
        pstCallEntity->ucIpv4Cid              = AT_PS_CALL_INVALID_CID;
        pstCallEntity->ucIpv6Cid              = AT_PS_CALL_INVALID_CID;

    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(stCallEvt.stCtrl.usClientId, 1);
        AT_PS_FreeCallEntity(stCallEvt.stCtrl.usClientId, 0);
    }
};


TEST_F(Test_AT_PS_ProcCallConnectedEvent, Test_AT_PS_ProcCallConnectedEvent_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallConnectedEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallConnectedEvent, Test_AT_PS_ProcCallConnectedEvent_002)
{
    // 变量声明

    // 参数初始化
    stCallEvt.stPdpAddr.enPdpType     = AT_PDP_TYPE_BUTT;
    pstCallEntity->ucIpv4Cid          = ucCid;
    pstCallEntity->ucIpv6Cid          = ucCid;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallConnectedEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallConnectedEvent, Test_AT_PS_ProcCallConnectedEvent_003)
{
    // 变量声明

    // 参数初始化
    stCallEvt.stCtrl.usClientId      = AT_CLIENT_ID_PCUI;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
    stCallEvt.ucCid       = ucCid;

    pstCallEntity->ucIpv4Cid          = ucCid;
    pstCallEntity->enIpv4State        = AT_PDP_STATE_ACTING;
    pstCallEntity->ucIpv6Cid          = AT_PS_CALL_INVALID_CID;

    pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_PCUI_INDEX;
    pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_PCUI_INDEX;
    pstCallEntity->stUserInfo.ucUsrType = AT_USBCOM_USER;
    pstCallEntity->stUserInfo.ucUsrCid = 1;
    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallConnectedEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}

class Test_AT_PS_ProcCallRejectEvent: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCid       = 1;
        ucCallId    = 0;
        memset(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
        stCallEvt.ucCid   = ucCid;
        stCallEvt.enPdpType = AT_PDP_IPV4;
        stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_MODEM;

        AT_InitCtx();

        AT_PS_SetPsCallErrCause(stCallEvt.stCtrl.usClientId, TAF_PS_CAUSE_SUCCESS);

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stCallEvt.stCtrl.usClientId);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]                   = 0;

        pstCallEntity = AT_PS_GetCallEntity(stCallEvt.stCtrl.usClientId, ucCallId);
        pstCallEntity->enCurrPdpType          = AT_PDP_IPV4;
        pstCallEntity->enIpv6State            = AT_PDP_STATE_IDLE;
        pstCallEntity->ucIpv4Cid              = AT_PS_CALL_INVALID_CID;
        pstCallEntity->ucIpv6Cid              = AT_PS_CALL_INVALID_CID;

    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(stCallEvt.stCtrl.usClientId, 1);
        AT_PS_FreeCallEntity(stCallEvt.stCtrl.usClientId, 0);
    }
};


TEST_F(Test_AT_PS_ProcCallRejectEvent, Test_AT_PS_ProcCallRejectEvent_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallRejectEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallRejectEvent, Test_AT_PS_ProcCallRejectEvent_002)
{
    // 变量声明

    // 参数初始化
    stCallEvt.enPdpType               = AT_PDP_TYPE_BUTT;
    pstCallEntity->ucIpv4Cid          = ucCid;
    pstCallEntity->ucIpv6Cid          = ucCid;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallRejectEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallRejectEvent, Test_AT_PS_ProcCallRejectEvent_003)
{
    // 变量声明

    // 参数初始化
    stCallEvt.enPdpType               = AT_PDP_IPV4;
    pstCallEntity->ucIpv4Cid          = ucCid;
    pstCallEntity->ucIpv6Cid          = ucCid;
    pstCallEntity->enCurrPdpType      = TAF_PDP_TYPE_BUTT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallRejectEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcCallEndedEvent: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCid       = 1;
        ucCallId    = 0;

        memset(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
        stCallEvt.ucCid   = ucCid;
        stCallEvt.ucRabId = 1;
        stCallEvt.enPdpType = AT_PDP_IPV4;
        stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_MODEM;

        AT_InitCtx();

        AT_PS_SetPsCallErrCause(stCallEvt.stCtrl.usClientId, TAF_PS_CAUSE_SUCCESS);

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stCallEvt.stCtrl.usClientId);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]                   = 0;

        pstCallEntity = AT_PS_GetCallEntity(stCallEvt.stCtrl.usClientId, ucCallId);
        pstCallEntity->enCurrPdpType          = AT_PDP_IPV4;
        pstCallEntity->enIpv6State            = AT_PDP_STATE_IDLE;
        pstCallEntity->ucIpv4Cid              = AT_PS_CALL_INVALID_CID;
        pstCallEntity->ucIpv6Cid              = AT_PS_CALL_INVALID_CID;

    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(stCallEvt.stCtrl.usClientId, 1);
        AT_PS_FreeCallEntity(stCallEvt.stCtrl.usClientId, 0);
    }
};


TEST_F(Test_AT_PS_ProcCallEndedEvent, Test_AT_PS_ProcCallEndedEvent_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallEndedEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallEndedEvent, Test_AT_PS_ProcCallEndedEvent_002)
{
    // 变量声明

    // 参数初始化
    stCallEvt.enPdpType                 = AT_PDP_TYPE_BUTT;
    pstCallEntity->ucIpv4Cid            = ucCid;
    pstCallEntity->ucIpv6Cid            = ucCid;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallEndedEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallEndedEvent, Test_AT_PS_ProcCallEndedEvent_003)
{
    // 变量声明

    // 参数初始化
    stCallEvt.stCtrl.usClientId     = AT_CLIENT_ID_PCUI;
    stCallEvt.enPdpType             = TAF_PDP_IPV4;
    stCallEvt.ucCid                 = ucCid;

    pstCallEntity->ucIpv4Cid          = ucCid;
    pstCallEntity->enIpv4State        = AT_PDP_STATE_DEACTING;
    pstCallEntity->ucIpv6Cid          = AT_PS_CALL_INVALID_CID;

    pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_PCUI_INDEX;
    pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_PCUI_INDEX;
    pstCallEntity->stUserInfo.ucUsrType = AT_USBCOM_USER;
    pstCallEntity->stUserInfo.ucUsrCid = 1;
    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_ProcCallEndedEvent(&stCallEvt);

    // 执行检查
    GlobalMockObject::verify();
}

class Test_AT_PS_ProcDialDown: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));

#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicEst(0);
#endif
        AT_InitCtx();

        ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

        pstModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        AT_PS_AssignCallIdToCid(ucIndex, 1, 0);
        AT_PS_AllocCallEntity(ucIndex, &ucCallId);

        pstChanCfg = AT_PS_GetDataChanlCfg(ucIndex, 1);
        pstChanCfg->ulUsed     = VOS_TRUE;
        pstChanCfg->ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        pstCallEnt = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_MODEM_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_ACTED;
#if (FEATURE_ON == FEATURE_IPV6)
        pstCallEnt->ucIpv6Cid   = 2;
        pstCallEnt->enIpv6State = AT_PDP_STATE_ACTED;
#endif
        AT_GetCommPsCtxAddr()->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;
    }
    void TearDown()
    {
        AT_CleanAtChdataCfg(ucIndex, 1);
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};


TEST_F(Test_AT_PS_ProcDialDown, Test_AT_PS_ProcDialDown_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucCid = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);
    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    //相关全局变量初始化
    gucAtParaIndex = 2;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gastAtParaList[0].usParaLen   = 1;
    gastAtParaList[0].ulParaValue = ucCid;
    gastAtParaList[1].usParaLen   = 1;
    gastAtParaList[1].ulParaValue = 0;

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_PS_ProcDialCmd(ucIndex);

    //执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    EXPECT_EQ(AT_PDP_STATE_DEACTING, pstCallEntity->enIpv4State);
#if (FEATURE_ON == FEATURE_IPV6)
    EXPECT_EQ(AT_PDP_STATE_DEACTING, pstCallEntity->enIpv6State);
#endif

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialDown, Test_AT_PS_ProcDialDown_002)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucCid = 1;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);
    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    //相关全局变量初始化
    gucAtParaIndex = 2;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gastAtParaList[0].usParaLen   = 1;
    gastAtParaList[0].ulParaValue = ucCid;
    gastAtParaList[1].usParaLen   = 1;
    gastAtParaList[1].ulParaValue = 0;

    //MOCKER操作
    MOCKER(TAF_PS_CallEnd)
        .stubs()
        .will(returnValue(VOS_ERR));

    //调用被测函数
    ulRslt = AT_PS_ProcDialCmd(ucIndex);

    //执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv4State);
#if (FEATURE_ON == FEATURE_IPV6)
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv6State);
#endif

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialDown, Test_AT_PS_ProcDialDown_003)
{
    //参数定义
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucCid = 5;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstChanCfg = AT_PS_GetDataChanlCfg(ucIndex, ucCid);
    pstChanCfg->ulUsed     = VOS_TRUE;
    pstChanCfg->ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

    //相关全局变量初始化
    gucAtParaIndex = 2;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gastAtParaList[0].usParaLen   = 1;
    gastAtParaList[0].ulParaValue = ucCid;
    gastAtParaList[1].usParaLen   = 1;
    gastAtParaList[1].ulParaValue = 0;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_OK));

//    MOCKER(AT_PS_ReportDEND)
//        .with(eq(ucCid),
//              eq(ucIndex),
//              eq(TAF_PDP_IPV4),
//              eq(TAF_PS_CAUSE_SUCCESS));
//
//#if (FEATURE_ON == FEATURE_IPV6)
//    MOCKER(AT_PS_ReportDEND)
//        .with(eq(ucCid),
//              eq(ucIndex),
//              eq(TAF_PDP_IPV6),
//              eq(TAF_PS_CAUSE_SUCCESS));
//#endif

    //调用被测函数
    ulRslt = AT_PS_ProcDialCmd(ucIndex);

    //执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialDown, Test_AT_PS_ProcDialDown_004)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucCid = 1;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);
    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    pstCallEntity->enIpv4State = AT_PDP_STATE_DEACTING;
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv6State = AT_PDP_STATE_IDLE;
#endif

    //相关全局变量初始化
    gucAtParaIndex = 2;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gastAtParaList[0].usParaLen   = 1;
    gastAtParaList[0].ulParaValue = ucCid;
    gastAtParaList[1].usParaLen   = 1;
    gastAtParaList[1].ulParaValue = 0;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_OK));

//#if (FEATURE_ON == FEATURE_IPV6)
//    MOCKER(AT_PS_ReportDEND)
//        .with(eq(ucCid),
//              eq(ucIndex),
//              eq(TAF_PDP_IPV6),
//              eq(TAF_PS_CAUSE_SUCCESS))
//#endif

    //调用被测函数
    ulRslt = AT_PS_ProcDialCmd(ucIndex);

    //执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcDialDown, Test_AT_PS_ProcDialDown_005)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucCid = 1;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);
    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    pstCallEntity->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv4State = AT_PDP_STATE_IDLE;
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->enIpv6State = AT_PDP_STATE_DEACTING;
#endif

    //相关全局变量初始化
    gucAtParaIndex = 2;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gastAtParaList[0].usParaLen   = 1;
    gastAtParaList[0].ulParaValue = ucCid;
    gastAtParaList[1].usParaLen   = 1;
    gastAtParaList[1].ulParaValue = 0;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(AT_OK));

//#if (FEATURE_ON == FEATURE_IPV6)
//    MOCKER(AT_PS_ReportDEND)
//        .with(eq(ucCid),
//              eq(ucIndex),
//              eq(TAF_PDP_IPV6),
//              eq(TAF_PS_CAUSE_SUCCESS))
//#endif

    //调用被测函数
    ulRslt = AT_PS_ProcDialCmd(ucIndex);

    //执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ReportAllCallEndState: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_UsbPcuiEst(AT_USB_COM_PORT_NO);
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};


TEST_F(Test_AT_PS_ReportAllCallEndState, Test_AT_PS_ReportAllCallEndState_001)
{
    //参数定义
    AT_PS_USER_INFO_STRU                stUsrInfo;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    stUsrInfo.enPortIndex = AT_CLIENT_TAB_PCUI_INDEX;
    stUsrInfo.enUserIndex = AT_CLIENT_TAB_PCUI_INDEX;
    stUsrInfo.ucUsrType   = AT_USBCOM_USER;
    stUsrInfo.ucUsrCid    = 1;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_PS_ParseUsrInfo)
        .stubs()
        .with(eq(ucIndex), outBoundP((AT_PS_USER_INFO_STRU *)&stUsrInfo, (VOS_UINT32)sizeof(stUsrInfo)));

    //调用被测函数
    AT_PS_ReportAllCallEndState(ucIndex);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ReportCurrCallEndState: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        usClientId = AT_CLIENT_TAB_NDIS_INDEX;

        AT_InitCtx();
        AT_PS_AssignCallIdToCid(usClientId, 1, 0);
        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);
        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_NDIS_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_NDIS_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_ACTED;
#if (FEATURE_ON == FEATURE_IPV6)
        pstCallEnt->ucIpv6Cid   = 2;
        pstCallEnt->enIpv6State = AT_PDP_STATE_ACTED;
#endif
    }
    void TearDown()
    {
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_ReportCurrCallEndState, Test_AT_PS_ReportCurrCallEndState_001)
{
    //参数定义
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;

    //参数初始化
    ucCid = 1;
    ucCallId = AT_PS_TransCidToCallId(usClientId, ucCid);

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_ReportCurrCallEndState(usClientId, ucCallId);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ReportCurrCallConnState: public ::testing::Test
{
public:
    VOS_UINT16                          usClientId;

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


TEST_F(Test_AT_PS_ReportCurrCallConnState, Test_AT_PS_ReportCurrCallConnState_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    //参数初始化
    ucCallId  = 0;
    enPdpType = TAF_PDP_TYPE_BUTT;

    usClientId = AT_CLIENT_TAB_NDIS_INDEX;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;
    pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_NDIS_INDEX;
    pstCallEntity->stUserInfo.ucUsrType   = AT_NDIS_USER;
    pstCallEntity->stUserInfo.ucUsrCid    = 1;

    pstCallEntity->ucIpv4Cid   = 1;
    pstCallEntity->enIpv4State = AT_PDP_STATE_ACTED;
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = 2;
    pstCallEntity->enIpv6State = AT_PDP_STATE_ACTED;
#endif

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_ReportCurrCallConnState(usClientId, ucCallId);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ReportCurrCallConnState, Test_AT_PS_ReportCurrCallConnState_002)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    //参数初始化
    ucCallId  = 0;
    enPdpType = TAF_PDP_TYPE_BUTT;

    usClientId = AT_CLIENT_TAB_NDIS_INDEX;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;
    pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_NDIS_INDEX;
    pstCallEntity->stUserInfo.ucUsrType   = AT_MODEM_USER;
    pstCallEntity->stUserInfo.ucUsrCid    = 1;

    pstCallEntity->ucIpv4Cid   = 1;
    pstCallEntity->enIpv4State = AT_PDP_STATE_ACTED;
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = 2;
    pstCallEntity->enIpv6State = AT_PDP_STATE_ACTED;
#endif

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_ReportCurrCallConnState(usClientId, ucCallId);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcConflictDialUpWithCurrCall: public ::testing::Test
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


TEST_F(Test_AT_PS_ProcConflictDialUpWithCurrCall, Test_AT_PS_ProcConflictDialUpWithCurrCall_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_PS_IsLinkGoingUp)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));
    MOCKER(AT_PS_IsLinkGoingDown)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRslt = AT_PS_ProcConflictDialUpWithCurrCall(1, 1);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}

class Test_AT_PS_HangupCall: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    VOS_UINT8                           ucCallId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        usClientId  = AT_CLIENT_ID_MODEM;

        AT_InitCtx();
        AT_PS_AssignCallIdToCid(usClientId, 1, 0);
        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);
        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_MODEM_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;
    }
    void TearDown()
    {
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_HangupCall, Test_AT_PS_HangupCall_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucCid = 1;
    ucCallId = AT_PS_TransCidToCallId(usClientId, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    pstCallEntity->ucIpv4Cid   = ucCid;
    pstCallEntity->enIpv4State = AT_PDP_STATE_ACTED;
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv6State = AT_PDP_STATE_IDLE;
#endif

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(TAF_PS_CallEnd)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = AT_PS_HangupCall(usClientId,ucCallId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_PS_HangupCall, Test_AT_PS_HangupCall_002)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucCid = 1;
    ucCallId = AT_PS_TransCidToCallId(usClientId, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    pstCallEntity->ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv4State = AT_PDP_STATE_IDLE;
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = ucCid;
    pstCallEntity->enIpv6State = AT_PDP_STATE_ACTED;
#endif

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(TAF_PS_CallEnd)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = AT_PS_HangupCall(usClientId, ucCallId);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#if (FEATURE_ON == FEATURE_AT_HSIC)

class Test_AT_PS_ProcCallOrigCnfEvent: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_HsicEst(0);
        AT_InitCtx();

        usClientId = AT_CLIENT_ID_MODEM;

        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        AT_PS_AssignCallIdToCid(usClientId, 1, 0);

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);
        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_HSIC1_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_ACTING;

#if (FEATURE_ON == FEATURE_IPV6)
        pstCallEnt->ucIpv6Cid   = 1;
        pstCallEnt->enIpv6State = AT_PDP_STATE_ACTING;
#endif
    }
    void TearDown()
    {
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_ProcCallOrigCnfEvent, Test_AT_PS_ProcCallOrigCnfEvent_001)
{
    //参数定义
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    stCallOrigCnf.ucCid   = 5;
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SUCCESS;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex, &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallOrigCnfEvent, Test_AT_PS_ProcCallOrigCnfEvent_002)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    stCallOrigCnf.ucCid   = 1;
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SIM_INVALID;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, stCallOrigCnf.ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
    pstCallEntity->enCurrPdpType = TAF_PDP_IPV4V6;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex, &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallOrigCnf.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
#if (FEATURE_ON == FEATURE_IPV6)
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);
#endif

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallOrigCnfEvent, Test_AT_PS_ProcCallOrigCnfEvent_003)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    stCallOrigCnf.ucCid   = 1;
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SIM_INVALID;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, stCallOrigCnf.ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
    pstCallEntity->enCurrPdpType = TAF_PDP_IPV4;
    pstCallEntity->ucIpv4Cid   = 1;
    pstCallEntity->enIpv4State = AT_PDP_STATE_ACTED;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex, &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(0, AT_PS_TransCidToCallId(ucIndex, stCallOrigCnf.ucCid));
    EXPECT_EQ(1, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstCallEntity->enIpv4State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_PS_ProcCallEndCnfEvent: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        usClientId = AT_CLIENT_ID_MODEM;
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicEst(0);
#endif
        AT_InitCtx();
        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        AT_PS_AssignCallIdToCid(usClientId, 1, 0);

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);
        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_MODEM_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_MODEM_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_DEACTING;

#if (FEATURE_ON == FEATURE_IPV6)
        pstCallEnt->ucIpv6Cid   = 1;
        pstCallEnt->enIpv6State = AT_PDP_STATE_DEACTING;
#endif
    }
    void TearDown()
    {
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_ProcCallEndCnfEvent, Test_AT_PS_ProcCallEndCnfEvent_001)
{
    //参数定义
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    stCallEndCnf.ucCid = 5;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtCallEndCnf(ucIndex, &stCallEndCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcCallEndCnfEvent, Test_AT_PS_ProcCallEndCnfEvent_002)
{
    //参数定义
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stCallEndCnf.ucCid       = 1;
    stCallEndCnf.enCause     = TAF_PS_CAUSE_INVALID_PARAMETER;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtCallEndCnf(ucIndex, &stCallEndCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcIpv4CallEnded: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicEst(0);
#endif
        AT_InitCtx();

        usClientId = AT_CLIENT_ID_APP;

        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

        pstChanCfg =AT_PS_GetDataChanlCfg(usClientId, 1);
        pstChanCfg->ulUsed     = VOS_TRUE;
        pstChanCfg->ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);

        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_HSIC1_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].UserType     = AT_APP_USER;
        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].CmdCurrentOpt= AT_CMD_INVALID;

        AT_PS_AssignCallIdToCid(usClientId, 1, 0);
        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_ACTED;
#if (FEATURE_ON == FEATURE_IPV6)
        AT_PS_AssignCallIdToCid(usClientId, 2, 0);
        pstCallEnt->ucIpv6Cid   = 2;
        pstCallEnt->enIpv6State = AT_PDP_STATE_ACTED;
#endif
    }
    void TearDown()
    {
        AT_CleanAtChdataCfg(usClientId, 1);
        AT_PS_FreeCallIdToCid(usClientId, 1);
#if (FEATURE_ON == FEATURE_IPV6)
        AT_PS_FreeCallIdToCid(usClientId, 2);
#endif
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_ProcIpv4CallEnded, Test_AT_PS_ProcIpv4CallEnded_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv6State = AT_PDP_STATE_ACTED;
    pstCallEntity->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
#endif
    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType  = TAF_PDP_IPV4;
    stCallEvent.ucRabId    = 5;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION;

    //相关全局变量初始化

    //MOCKER操作
    //MOCKER(AT_PS_ReportDEND)
    //    .with(eq(pstCallEntity->stUserInfo.ucUsrCid),
    //          eq(pstCallEntity->stUserInfo.enPortIndex),
    //          eq(TAF_PDP_IPV4),
    //          eq(stEvent.enCause));

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
#if (FEATURE_ON == FEATURE_IPV6)
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_DEACTING, pstCallEntity->enIpv6State);
#endif

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_PS_ProcIpv4CallEnded, Test_AT_PS_ProcIpv4CallEnded_002)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.ucRabId    = 5;
    stCallEvent.enPdpType  = TAF_PDP_IPV4;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION;

    pstCallEnt->enIpv6State                 = AT_PDP_STATE_ACTING;
    pstCallEntity->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
    //相关全局变量初始化

    //MOCKER操作
    //MOCKER(AT_PS_ReportDEND)
    //    .with(eq(pstCallEntity->stUserInfo.ucUsrCid),
    //          eq(pstCallEntity->stUserInfo.enPortIndex),
    //          eq(TAF_PDP_IPV4),
    //          eq(stEvent.enCause));

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PDP_STATE_DEACTING, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4CallEnded, Test_AT_PS_ProcIpv4CallEnded_003)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.ucRabId    = 5;
    stCallEvent.enPdpType  = TAF_PDP_IPV4;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION;

    pstCallEnt->enIpv6State                 = AT_PDP_STATE_ACTING;
    pstCallEntity->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
    pstCallEntity->enCurrPdpType = TAF_PDP_IPV4;
    //相关全局变量初始化

    //MOCKER操作
    MOCKER(AT_PS_HangupSingleStackConn)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_PS_SndCallEndedResult)
        .expects(exactly(2));


    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif

TEST_F(Test_AT_PS_ProcIpv4CallEnded, Test_AT_PS_ProcIpv4CallEnded_004)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv6State = AT_PDP_STATE_IDLE;
#endif
    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType  = TAF_PDP_IPV4;
    stCallEvent.ucRabId    = 5;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
#if (FEATURE_ON == FEATURE_IPV6)
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);
#endif

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_IPV6)

class Test_AT_PS_ProcIpv6CallEnded: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicEst(0);
#endif
        AT_InitCtx();

        usClientId = AT_CLIENT_ID_APP;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        pstChanCfg = AT_PS_GetDataChanlCfg(usClientId, 1);
        pstChanCfg->ulUsed     = VOS_TRUE;
        pstChanCfg->ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);

        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_HSIC1_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].UserType     = AT_APP_USER;
        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].CmdCurrentOpt= AT_CMD_INVALID;

        AT_PS_AssignCallIdToCid(usClientId, 1, 0);
        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_ACTED;
        AT_PS_AssignCallIdToCid(usClientId, 2, 0);
        pstCallEnt->ucIpv6Cid   = 2;
        pstCallEnt->enIpv6State = AT_PDP_STATE_ACTED;
    }
    void TearDown()
    {
        AT_CleanAtChdataCfg(usClientId, 1);
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallIdToCid(usClientId, 2);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_ProcIpv6CallEnded, Test_AT_PS_ProcIpv6CallEnded_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
    pstCallEntity->ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv4State = AT_PDP_STATE_IDLE;

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stCallEvent.ucCid      = 2;
    stCallEvent.enPdpType  = TAF_PDP_IPV6;
    stCallEvent.ucRabId    = 6;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION;

    //相关全局变量初始化

    //MOCKER操作
    //MOCKER(AT_PS_ReportDEND)
    //    .with(eq(pstCallEntity->stUserInfo.ucUsrCid),
    //          eq(pstCallEntity->stUserInfo.enPortIndex),
    //          eq(TAF_PDP_IPV4),
    //          eq(stEvent.enCause));

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv6CallEnded, Test_AT_PS_ProcIpv6CallEnded_002)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stCallEvent.ucCid      = 2;
    stCallEvent.enPdpType  = TAF_PDP_IPV6;
    stCallEvent.ucRabId    = 6;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION;

    pstCallEnt->enIpv4State              = AT_PDP_STATE_DEACTING;

    //相关全局变量初始化

    //MOCKER操作
    //MOCKER(AT_PS_ReportDEND)
    //    .with(eq(pstCallEntity->stUserInfo.ucUsrCid),
    //          eq(pstCallEntity->stUserInfo.enPortIndex),
    //          eq(TAF_PDP_IPV4),
    //          eq(stEvent.enCause));

    ulRslt = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);
    EXPECT_EQ(AT_PDP_STATE_DEACTING, pstCallEntity->enIpv4State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcIpv4v6CallEnded: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicEst(0);
#endif
        AT_InitCtx();

        usClientId = AT_CLIENT_ID_APP;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        pstChanCfg = AT_PS_GetDataChanlCfg(usClientId, 1);
        pstChanCfg->ulUsed     = VOS_TRUE;
        pstChanCfg->ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);

        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_HSIC1_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].UserType     = AT_APP_USER;
        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].CmdCurrentOpt= AT_CMD_INVALID;

        AT_PS_AssignCallIdToCid(usClientId, 1, 0);
        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_ACTED;
        pstCallEnt->ucIpv6Cid   = 1;
        pstCallEnt->enIpv6State = AT_PDP_STATE_ACTED;
    }
    void TearDown()
    {
        AT_CleanAtChdataCfg(usClientId, 1);
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_ProcIpv4v6CallEnded, Test_AT_PS_ProcIpv4v6CallEnded_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;

    //参数初始化
    ucCid = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
    pstCallEntity->ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv4State = AT_PDP_STATE_IDLE;

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType  = TAF_PDP_IPV4V6;
    stCallEvent.ucRabId    = 5;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION;

    //相关全局变量初始化

    //MOCKER操作
    //MOCKER(AT_PS_ReportDEND)
    //    .with(eq(pstCallEntity->stUserInfo.ucUsrCid),
    //          eq(pstCallEntity->stUserInfo.enPortIndex),
    //          eq(TAF_PDP_IPV4),
    //          eq(stEvent.enCause));

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_PS_ProcIpv4CallReject: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg;
    VOS_UINT8                           ucCallId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicEst(0);
#endif
        AT_InitCtx();

        usClientId = AT_CLIENT_ID_APP;

        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

        pstChanCfg = AT_PS_GetDataChanlCfg(usClientId, 1);
        pstChanCfg->ulUsed     = VOS_TRUE;
        pstChanCfg->ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);

        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_HSIC1_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].UserType     = AT_HSIC1_USER;
        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].CmdCurrentOpt= AT_CMD_INVALID;

        pstCallEnt->enCurrPdpType       = TAF_PDP_IPV4;

        AT_PS_AssignCallIdToCid(usClientId, 1, 0);
        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_ACTING;
#if (FEATURE_ON == FEATURE_IPV6)
        pstCallEnt->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
        pstCallEnt->enIpv6State = AT_PDP_STATE_IDLE;
#endif
    }
    void TearDown()
    {
        AT_CleanAtChdataCfg(usClientId, 1);
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_ProcIpv4CallReject, Test_AT_PS_ProcIpv4CallReject_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    pstUsrDialParam = &(pstCallEntity->stUsrDialParam);
    pstUsrDialParam->enPdpType = TAF_PDP_IPV4;

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType  = TAF_PDP_IPV4;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
#if (FEATURE_ON == FEATURE_IPV6)
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);
#endif

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_PS_ProcIpv4CallReject, Test_AT_PS_ProcIpv4CallReject_002)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucNewCid;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucNewCid = 1;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    pstUsrDialParam = &(pstCallEntity->stUsrDialParam);
    pstUsrDialParam->enPdpType = TAF_PDP_IPV4V6;

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType  = TAF_PDP_IPV4;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(TAF_AGENT_FindCidForDial)
        .stubs()
        .with(outBoundP((VOS_UINT8 *)&ucNewCid))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_SetPdpCidPara)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(ucCallId, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(ucCallId, AT_PS_TransCidToCallId(ucIndex, ucNewCid));
    EXPECT_EQ(ucNewCid, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_ACTING, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4CallReject, Test_AT_PS_ProcIpv4CallReject_003)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucNewCid;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucNewCid = 12;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    pstUsrDialParam = &(pstCallEntity->stUsrDialParam);
    pstUsrDialParam->enPdpType = TAF_PDP_IPV4V6;

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
    stCallEvent.ucCid      = 1;
    pstCallEnt->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(TAF_AGENT_FindCidForDial)
        .stubs()
        .with(outBoundP((void *)&ucNewCid))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_PS_CallOrig)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, ucNewCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#if (FEATURE_ON == FEATURE_IPV6)

class Test_AT_PS_ProcIpv6CallReject: public ::testing::Test
{
public:
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicEst(0);
#endif
        AT_InitCtx();

        usClientId = AT_CLIENT_ID_APP;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

        AT_PS_AllocCallEntity(usClientId, &ucCallId);

        pstChanCfg = AT_PS_GetDataChanlCfg(usClientId, 1);
        pstChanCfg->ulUsed     = VOS_TRUE;
        pstChanCfg->ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);

        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_HSIC1_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].UserType     = AT_HSIC1_USER;
        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].CmdCurrentOpt= AT_CMD_INVALID;


        AT_PS_AssignCallIdToCid(usClientId, 1, 0);
        pstCallEnt->ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
        pstCallEnt->enIpv4State = AT_PDP_STATE_IDLE;
        pstCallEnt->ucIpv6Cid   = 1;
        pstCallEnt->enIpv6State = AT_PDP_STATE_ACTING;

        pstCallEnt->stUsrDialParam.enPdpType = TAF_PDP_IPV6;
        pstCallEnt->enCurrPdpType         = TAF_PDP_IPV6;

    }
    void TearDown()
    {
        AT_CleanAtChdataCfg(usClientId, 1);
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_ProcIpv6CallReject, Test_AT_PS_ProcIpv6CallReject_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType    = TAF_PDP_IPV6;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ProcIpv4v6CallReject: public ::testing::Test
{
public:
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU *pstBackProcExtCause;
    AT_PS_CALL_ENTITY_STRU             *pstCallEnt;
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg;
    VOS_UINT8                           ucCallId;
    VOS_UINT16                          usClientId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_HsicEst(0);
#endif
        AT_InitCtx();

        usClientId = AT_CLIENT_ID_APP;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

        AT_PS_AllocCallEntity(usClientId, &ucCallId);
        AT_PS_SetPsCallErrCause(usClientId, TAF_PS_CAUSE_SUCCESS);

        pstChanCfg = AT_PS_GetDataChanlCfg(usClientId, 1);
        pstChanCfg->ulUsed     = VOS_TRUE;
        pstChanCfg->ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        pstCallEnt = AT_PS_GetCallEntity(usClientId, ucCallId);

        pstCallEnt->stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.enUserIndex  = AT_CLIENT_TAB_APP_INDEX;
        pstCallEnt->stUserInfo.ucUsrType   = AT_HSIC1_USER;
        pstCallEnt->stUserInfo.ucUsrCid    = 1;

        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].UserType     = AT_HSIC1_USER;
        gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].CmdCurrentOpt= AT_CMD_INVALID;

        AT_PS_AssignCallIdToCid(usClientId, 1, 0);
        pstCallEnt->ucIpv4Cid   = 1;
        pstCallEnt->enIpv4State = AT_PDP_STATE_ACTING;
        pstCallEnt->ucIpv6Cid   = 1;
        pstCallEnt->enIpv6State = AT_PDP_STATE_ACTING;

        pstCallEnt->stUsrDialParam.enPdpType = TAF_PDP_IPV4V6;
        pstCallEnt->enCurrPdpType         = TAF_PDP_IPV4V6;

    }
    void TearDown()
    {
        pstBackProcExtCause = &(AT_GetCommCtxAddr()->stPsCtx.stIpv6BackProcExtCauseTbl);
        pstBackProcExtCause->ulCauseNum = 0;

        AT_CleanAtChdataCfg(usClientId, 1);
        AT_PS_FreeCallIdToCid(usClientId, 1);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
        AT_PS_SetPsCallErrCause(usClientId, TAF_PS_CAUSE_SUCCESS);
    }
};


TEST_F(Test_AT_PS_ProcIpv4v6CallReject, Test_AT_PS_ProcIpv4v6CallReject_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType  = TAF_PDP_IPV4V6;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4v6CallReject, Test_AT_PS_ProcIpv4v6CallReject_002)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType    = TAF_PDP_IPV4V6;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(TAF_AGENT_SetPdpCidPara)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(ucCallId, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(ucCid, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_ACTING, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcIpv4v6CallReject, Test_AT_PS_ProcIpv4v6CallReject_003)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU *pstBackProcExtCause = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex  = AT_CLIENT_TAB_APP_INDEX;
    ucCid    = 1;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, ucCid);

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    pstBackProcExtCause = &(AT_GetCommCtxAddr()->stPsCtx.stIpv6BackProcExtCauseTbl);
    pstBackProcExtCause->ulCauseNum = 2;
    pstBackProcExtCause->aenPsCause[0] = TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED;
    pstBackProcExtCause->aenPsCause[1] = TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED;

    PS_MEM_SET(&stCallEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
    stCallEvent.ucCid      = 1;
    stCallEvent.enPdpType  = TAF_PDP_IPV4V6;
    stCallEvent.enCause    = TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(TAF_AGENT_SetPdpCidPara)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_PS_CallOrig)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex, &stCallEvent);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(ucIndex, stCallEvent.ucCid));
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv4State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstCallEntity->ucIpv6Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstCallEntity->enIpv6State);
    EXPECT_EQ(TAF_PS_CAUSE_UNKNOWN, AT_PS_GetPsCallErrCause(ucIndex));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_PS_ReportDCONN: public ::testing::Test
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


TEST_F(Test_AT_PS_ReportDCONN, Test_AT_PS_ReportDCONN_001)
{
    //参数定义
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucPortIndex;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    //参数初始化
    ucCid       = 1;
    ucPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
    enPdpType   = TAF_PDP_TYPE_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_ReportDCONN(ucCid, ucPortIndex, enPdpType);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ReportDCONN, Test_AT_PS_ReportDCONN_002)
{
    //参数定义
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucPortIndex;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_CHAR                            acExpectedStr[] = "\r\n^DCONN:1,\"IPV4\"\r\n\r\n^DCONN:1,\"IPV6\"\r\n";

    //参数初始化
    ucCid       = 1;
    ucPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
    enPdpType   = TAF_PDP_IPV4V6;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_ReportDCONN(ucCid, ucPortIndex, enPdpType);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_ReportDEND: public ::testing::Test
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


TEST_F(Test_AT_PS_ReportDEND, Test_AT_PS_ReportDEND_001)
{
    //参数定义
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucPortIndex;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

    //参数初始化
    ucCid       = 1;
    ucPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
    enPdpType   = TAF_PDP_TYPE_BUTT;
    enCause     = TAF_PS_CAUSE_SUCCESS;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_ReportDEND(ucCid, ucPortIndex, enPdpType, enCause);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_SndCallConnectedResult: public ::testing::Test
{
public:
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        usClientId = AT_CLIENT_ID_MODEM;
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};


TEST_F(Test_AT_PS_SndCallConnectedResult, Test_AT_PS_SndCallConnectedResult_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    //参数初始化
    ucCallId  = 0;
    enPdpType = TAF_PDP_TYPE_BUTT;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;
    pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_NDIS_INDEX;
    pstCallEntity->stUserInfo.ucUsrType   = AT_NDIS_USER;
    pstCallEntity->stUserInfo.ucUsrCid    = 1;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_SndCallConnectedResult(usClientId, ucCallId, enPdpType);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_SndCallEndedResult: public ::testing::Test
{
public:
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        usClientId = AT_CLIENT_ID_MODEM;

        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};


TEST_F(Test_AT_PS_SndCallEndedResult, Test_AT_PS_SndCallEndedResult_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;

    //参数初始化
    ucCallId  = 0;
    enPdpType = TAF_PDP_TYPE_BUTT;
    enCause   = TAF_PS_CAUSE_SUCCESS;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;
    pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_NDIS_INDEX;
    pstCallEntity->stUserInfo.ucUsrType   = AT_NDIS_USER;
    pstCallEntity->stUserInfo.ucUsrCid    = 1;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_SndCallEndedResult(usClientId, ucCallId, enPdpType, enCause);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_GetCidByCallType: public ::testing::Test
{
public:
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        usClientId = AT_CLIENT_ID_MODEM;
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};


TEST_F(Test_AT_PS_GetCidByCallType, Test_AT_PS_GetCidByCallType_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           ucCid;

    //参数初始化
    ucCallId  = 0;
    enPdpType = TAF_PDP_TYPE_BUTT;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
    pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_MODEM_INDEX;
    pstCallEntity->stUserInfo.ucUsrType   = AT_MODEM_USER;
    pstCallEntity->stUserInfo.ucUsrCid    = 1;

    pstCallEntity->ucIpv4Cid   = 1;
    pstCallEntity->enIpv4State = AT_PDP_STATE_ACTED;
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = 2;
    pstCallEntity->enIpv6State = AT_PDP_STATE_ACTED;
#endif

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ucCid = AT_PS_GetCidByCallType(usClientId, ucCallId, enPdpType);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_SetCallState: public ::testing::Test
{
public:
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        usClientId = AT_CLIENT_ID_MODEM;
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};


TEST_F(Test_AT_PS_SetCallState, Test_AT_PS_SetCallState_001)
{
    //参数定义
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    //参数初始化
    ucCallId  = 0;
    enPdpType = TAF_PDP_TYPE_BUTT;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    pstCallEntity->stUserInfo.enPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
    pstCallEntity->stUserInfo.enUserIndex = AT_CLIENT_TAB_MODEM_INDEX;
    pstCallEntity->stUserInfo.ucUsrType   = AT_MODEM_USER;
    pstCallEntity->stUserInfo.ucUsrCid    = 1;

    pstCallEntity->ucIpv4Cid   = 1;
    pstCallEntity->enIpv4State = AT_PDP_STATE_ACTED;
#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = 2;
    pstCallEntity->enIpv6State = AT_PDP_STATE_ACTING;
#endif

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    AT_PS_SetCallStateByType(0, ucCallId, enPdpType, AT_PDP_STATE_ACTED);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_PS_RegFCPoint: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCid       = 1;
        ucCallId    = 0;
        usClientId  = AT_CLIENT_ID_MODEM;

        AT_InitCtx();
        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]   = ucCallId;
        pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
        pstCallEntity->stUserInfo.ucUsrType = AT_USBCOM_USER;

    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(usClientId, ucCid);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_RegFCPoint, Test_AT_PS_RegFCPoint_001)
{
    // 变量声明
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        stEvent;

    // 参数初始化
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_PS_RegFCPoint(ucCallId, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_RegHsicFCPoint: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCid       = 1;
        ucCallId    = 0;
        usClientId  = AT_CLIENT_ID_MODEM;

        AT_InitCtx();
        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]   = ucCallId;
        pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
        pstCallEntity->stUserInfo.ucUsrType = AT_USBCOM_USER;

        pstModemPsCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
        pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    }

    void TearDown()
    {
        AT_CleanAtChdataCfg(usClientId, ucCid);
        AT_PS_FreeCallIdToCid(usClientId, ucCid);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_RegHsicFCPoint, Test_AT_PS_RegHsicFCPoint_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量
    pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId = UDI_INVAL_DEV_ID;
    // MOCKER操作

    // 调用被测函数
    AT_PS_RegHsicFCPoint(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_RegHsicFCPoint, Test_AT_PS_RegHsicFCPoint_002)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(FC_RegPoint)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    AT_PS_RegHsicFCPoint(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_RegHsicFCPoint, Test_AT_PS_RegHsicFCPoint_003)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(FC_RegPoint)
        .expects(exactly(2))
        .will(returnObjectList((VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_ERR));

    // 调用被测函数
    AT_PS_RegHsicFCPoint(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_RegHsicFCPoint, Test_AT_PS_RegHsicFCPoint_004)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(FC_RegPoint)
        .expects(exactly(3))
        .will(returnObjectList((VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_ERR));

    // 调用被测函数
    AT_PS_RegHsicFCPoint(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_RegHsicFCPoint, Test_AT_PS_RegHsicFCPoint_005)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(FC_RegPoint)
        .expects(exactly(4))
        .will(returnObjectList((VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_ERR));

    // 调用被测函数
    AT_PS_RegHsicFCPoint(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_RegHsicFCPoint, Test_AT_PS_RegHsicFCPoint_006)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(FC_RegPoint)
        .expects(never());

    stEvent.stCtrl.usClientId = AT_CLIENT_ID_BUTT;

    // 调用被测函数
    AT_PS_RegHsicFCPoint(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_RegHsicFCPoint, Test_AT_PS_RegHsicFCPoint_007)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量
    pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

    g_stFcIdMaptoFcPri[FC_ID_DIPC_1].ulUsed = VOS_TRUE;

    g_stFcIdMaptoFcPri[FC_ID_DIPC_1].enFcPri = FC_PRI_FOR_PDN_LOWEST;

    stEvent.bitOpUmtsQos             = VOS_TRUE;
    stEvent.stUmtsQos.ucTrafficClass = AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL;

    // MOCKER操作
    MOCKER(FC_RegPoint)
        .expects(never());

    // 调用被测函数
    AT_PS_RegHsicFCPoint(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}
#endif


class Test_AT_PS_DeRegHsicFCPoint: public ::testing::Test
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


TEST_F(Test_AT_PS_DeRegHsicFCPoint, Test_AT_PS_DeRegHsicFCPoint_001)
{
    // 变量声明
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  stEvent;

    // 参数初始化
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_BUTT;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(FC_DeRegPoint)
        .expects(never());

    // 调用被测函数
    AT_PS_DeRegHsicFCPoint(1, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_DeRegHsicFCPoint, Test_AT_PS_DeRegHsicFCPoint_002)
{
    // 变量声明
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    // 参数初始化
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stEvent.ucCid = 1;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(AT_CLIENT_ID_MODEM);

    pstPsModemCtx->astChannelCfg[stEvent.ucCid].ulUsed = VOS_TRUE;
    pstPsModemCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_CTRL_ID;
    pstPsModemCtx->astChannelCfg[stEvent.ucCid].ulRmNetActFlg = VOS_TRUE;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(FC_DeRegPoint)
        .expects(never());

    // 调用被测函数
    AT_PS_DeRegHsicFCPoint(1, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_DeRegHsicFCPoint, Test_AT_PS_DeRegHsicFCPoint_003)
{
    // 变量声明
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    // 参数初始化
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stEvent.ucCid = 1;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(AT_CLIENT_ID_MODEM);

    pstPsModemCtx->astChannelCfg[stEvent.ucCid].ulUsed = VOS_TRUE;
    pstPsModemCtx->astChannelCfg[stEvent.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;
    pstPsModemCtx->astChannelCfg[stEvent.ucCid].ulRmNetActFlg = VOS_TRUE;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(FC_DeRegPoint)
        .stubs()
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_PS_DeRegHsicFCPoint(1, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}

class Test_AT_PS_RegAppFCPoint: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    VOS_UINT16                          usClientId;

    void SetUp()
    {
        UT_STUB_INIT();
        ucCid       = 1;
        ucCallId    = 0;
        usClientId  = AT_CLIENT_ID_MODEM;

        AT_InitCtx();
        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]   = ucCallId;
        pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
        pstCallEntity->stUserInfo.ucUsrType = AT_USBCOM_USER;

        pstModemPsCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
        pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

        PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    }

    void TearDown()
    {
        AT_CleanAtChdataCfg(usClientId, ucCid);
        AT_PS_FreeCallIdToCid(usClientId, ucCid);
        AT_PS_FreeCallEntity(usClientId, ucCallId);
    }
};


TEST_F(Test_AT_PS_RegAppFCPoint, Test_AT_PS_RegAppFCPoint_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量
    pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId = RNIC_RM_NET_ID_0;

    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed = VOS_TRUE;

    // MOCKER操作
    MOCKER(FC_RegPoint)
       .expects(never());

    // 调用被测函数
    AT_PS_RegAppFCPoint(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}

class Test_AT_PS_GetFcIdByUdiDeviceId: public ::testing::Test
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


TEST_F(Test_AT_PS_GetFcIdByUdiDeviceId, Test_AT_PS_GetFcIdByUdiDeviceId_001)
{
    EXPECT_EQ(FC_ID_DIPC_1, AT_PS_GetFcIdByUdiDeviceId(UDI_ACM_HSIC_ACM1_ID));
    EXPECT_EQ(FC_ID_DIPC_1, AT_PS_GetFcIdByUdiDeviceId(UDI_NCM_HSIC_NCM0_ID));
    EXPECT_EQ(FC_ID_DIPC_2, AT_PS_GetFcIdByUdiDeviceId(UDI_ACM_HSIC_ACM3_ID));
    EXPECT_EQ(FC_ID_DIPC_2, AT_PS_GetFcIdByUdiDeviceId(UDI_NCM_HSIC_NCM1_ID));
    EXPECT_EQ(FC_ID_DIPC_3, AT_PS_GetFcIdByUdiDeviceId(UDI_ACM_HSIC_ACM5_ID));
    EXPECT_EQ(FC_ID_DIPC_3, AT_PS_GetFcIdByUdiDeviceId(UDI_NCM_HSIC_NCM2_ID));

    EXPECT_EQ(FC_ID_BUTT, AT_PS_GetFcIdByUdiDeviceId(UDI_ACM_HSIC_ACM0_ID));

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_GetFcIdFromRnicByRmNetId: public ::testing::Test
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


TEST_F(Test_AT_PS_GetFcIdFromRnicByRmNetId, Test_AT_PS_GetFcIdFromRnicByRmNetId_001)
{
    EXPECT_EQ(FC_ID_NIC_1, AT_PS_GetFcIdFromRnicByRmNetId(RNIC_RM_NET_ID_0));
    EXPECT_EQ(FC_ID_NIC_2, AT_PS_GetFcIdFromRnicByRmNetId(RNIC_RM_NET_ID_1));
    EXPECT_EQ(FC_ID_NIC_3, AT_PS_GetFcIdFromRnicByRmNetId(RNIC_RM_NET_ID_2));
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    EXPECT_EQ(FC_ID_NIC_4, AT_PS_GetFcIdFromRnicByRmNetId(RNIC_RM_NET_ID_3));
    EXPECT_EQ(FC_ID_NIC_5, AT_PS_GetFcIdFromRnicByRmNetId(RNIC_RM_NET_ID_4));
    #if (MULTI_MODEM_NUMBER == 3)
    EXPECT_EQ(FC_ID_NIC_6, AT_PS_GetFcIdFromRnicByRmNetId(RNIC_RMNET_ID_5));
    EXPECT_EQ(FC_ID_NIC_7, AT_PS_GetFcIdFromRnicByRmNetId(RNIC_RMNET_ID_6));
    #endif
#endif
    EXPECT_EQ(FC_ID_BUTT, AT_PS_GetFcIdFromRnicByRmNetId(RNIC_RMNET_ID_BUTT));

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_GetRnicRmNetIdFromChDataValue: public ::testing::Test
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


TEST_F(Test_AT_PS_GetRnicRmNetIdFromChDataValue, Test_AT_PS_GetRnicRmNetIdFromChDataValue_001)
{
    VOS_UINT8                           ucIndex;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    RNIC_RM_NET_ID_ENUM_UINT8           enRnicRmNetId;
    VOS_UINT32                          ulRslt;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    /* 非法值 */
    ucIndex = AT_CLIENT_BUTT;

    enDataChannelId = AT_CH_DATA_CHANNEL_ID_1;

    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    EXPECT_EQ(VOS_ERR, ulRslt);

    /* chdata 1 */
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    enDataChannelId = AT_CH_DATA_CHANNEL_ID_1;

    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_RM_NET_ID_0, enRnicRmNetId);

    /* chdata 2 */
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    enDataChannelId = AT_CH_DATA_CHANNEL_ID_2;

    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_RM_NET_ID_1, enRnicRmNetId);

    /* chdata 3 */
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    enDataChannelId = AT_CH_DATA_CHANNEL_ID_3;

    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_RM_NET_ID_2, enRnicRmNetId);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    /* chdata 4 */
    ucIndex = AT_CLIENT_TAB_APP5_INDEX;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    enDataChannelId = AT_CH_DATA_CHANNEL_ID_4;

    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_RM_NET_ID_3, enRnicRmNetId);

    /* chdata 5 */
    ucIndex = AT_CLIENT_TAB_APP5_INDEX;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    enDataChannelId = AT_CH_DATA_CHANNEL_ID_5;

    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_RM_NET_ID_4, enRnicRmNetId);
#endif

    /* MODEM0 chdata 4 */
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    enDataChannelId = AT_CH_DATA_CHANNEL_ID_4;

    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    EXPECT_EQ(VOS_ERR, ulRslt);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    /* MODEM1 chdata 1 */
    ucIndex = AT_CLIENT_TAB_APP5_INDEX;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    enDataChannelId = AT_CH_DATA_CHANNEL_ID_1;

    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    EXPECT_EQ(VOS_ERR, ulRslt);
#endif

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_GetChDataValueFromRnicRmNetId: public ::testing::Test
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


TEST_F(Test_AT_PS_GetChDataValueFromRnicRmNetId, AT_PS_GetChDataValueFromRnicRmNetId_001)
{
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    RNIC_RM_NET_ID_ENUM_UINT8           enRnicRmNetId;
    VOS_UINT32                          ulRslt;

    enRnicRmNetId = RNIC_RM_NET_ID_0;

    ulRslt = AT_PS_GetChDataValueFromRnicRmNetId(enRnicRmNetId, &enDataChannelId);

    EXPECT_EQ(AT_CH_DATA_CHANNEL_ID_1, enDataChannelId);
    EXPECT_EQ(VOS_OK, ulRslt);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    enRnicRmNetId = RNIC_RM_NET_ID_3;

    ulRslt = AT_PS_GetChDataValueFromRnicRmNetId(enRnicRmNetId, &enDataChannelId);

    EXPECT_EQ(AT_CH_DATA_CHANNEL_ID_4, enDataChannelId);
    EXPECT_EQ(VOS_OK, ulRslt);
#endif
    enRnicRmNetId = RNIC_RMNET_ID_BUTT;

    ulRslt = AT_PS_GetChDataValueFromRnicRmNetId(enRnicRmNetId, &enDataChannelId);

    EXPECT_EQ(VOS_ERR, ulRslt);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_NDIS_ParseUsrInfo: public ::testing::Test
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


TEST_F(Test_AT_NDIS_ParseUsrInfo, Test_AT_NDIS_ParseUsrInfo_001)
{
    VOS_UINT8                           ucIndex;
    AT_PS_USER_INFO_STRU                stUsrInfo;

    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    gastAtParaList[0].ulParaValue = 1;

    AT_NDIS_ParseUsrInfo(ucIndex, &stUsrInfo);

    EXPECT_EQ(ucIndex, stUsrInfo.enPortIndex);
    EXPECT_EQ(AT_CLIENT_TAB_NDIS_INDEX, stUsrInfo.enUserIndex);
    EXPECT_EQ(AT_NDIS_USER, stUsrInfo.ucUsrType);
    EXPECT_EQ(1, stUsrInfo.ucUsrCid);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_APP_ParseUsrInfo: public ::testing::Test
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


TEST_F(Test_AT_APP_ParseUsrInfo, Test_AT_APP_ParseUsrInfo_001)
{
    VOS_UINT8                           ucIndex;
    AT_PS_USER_INFO_STRU                stUsrInfo;

    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    gastAtParaList[0].ulParaValue = 1;

    AT_APP_ParseUsrInfo(ucIndex, &stUsrInfo);

    EXPECT_EQ(ucIndex, stUsrInfo.enPortIndex);
    EXPECT_EQ(AT_CLIENT_TAB_APP_INDEX, stUsrInfo.enUserIndex);
    EXPECT_EQ(AT_APP_USER, stUsrInfo.ucUsrType);
    EXPECT_EQ(1, stUsrInfo.ucUsrCid);

    // 执行检查
    GlobalMockObject::verify();
}

class Test_AT_PS_ParseUsrInfo: public ::testing::Test
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


TEST_F(Test_AT_PS_ParseUsrInfo, Test_AT_PS_ParseUsrInfo_001)
{
    VOS_UINT8                           ucIndex;
    AT_PS_USER_INFO_STRU                stUsrInfo;

    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    AT_SetPcuiPsCallFlag(VOS_TRUE, AT_CLIENT_TAB_APP_INDEX);

    gastAtParaList[0].ulParaValue = 1;

    AT_PS_ParseUsrInfo(ucIndex, &stUsrInfo);

    EXPECT_EQ(ucIndex, stUsrInfo.enPortIndex);
    EXPECT_EQ(AT_CLIENT_TAB_APP_INDEX, stUsrInfo.enUserIndex);
    EXPECT_EQ(AT_APP_USER, stUsrInfo.ucUsrType);
    EXPECT_EQ(1, stUsrInfo.ucUsrCid);

    // 执行检查
    GlobalMockObject::verify();
}

class Test_AT_PS_SndDipcPdpActBearerTypeInd: public ::testing::Test
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


TEST_F(Test_AT_PS_SndDipcPdpActBearerTypeInd, Test_AT_PS_SndDipcPdpActBearerTypeInd_001)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;
    enBearerType = DIPC_BEARER_TYPE_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)NULL));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_PS_SndDipcPdpActBearerTypeInd(ucCid, &stEvent, enBearerType);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SndDipcPdpActBearerTypeInd, Test_AT_PS_SndDipcPdpActBearerTypeInd_002)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;
    enBearerType = DIPC_BEARER_TYPE_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_PS_SndDipcPdpActBearerTypeInd(ucCid, &stEvent, enBearerType);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_SndDipcPdpDeactBearerTypeInd: public ::testing::Test
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


TEST_F(Test_AT_PS_SndDipcPdpDeactBearerTypeInd, Test_AT_PS_SndDipcPdpDeactBearerTypeInd_001)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;
    enBearerType = DIPC_BEARER_TYPE_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)NULL));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_PS_SndDipcPdpDeactBearerTypeInd(&stEvent, enBearerType);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SndDipcPdpDeactBearerTypeInd, Test_AT_PS_SndDipcPdpDeactBearerTypeInd_002)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;
    enBearerType = DIPC_BEARER_TYPE_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_PS_SndDipcPdpDeactBearerTypeInd(&stEvent, enBearerType);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_SndRnicIpv4PdpActInd: public ::testing::Test
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


TEST_F(Test_AT_PS_SndRnicIpv4PdpActInd, Test_AT_PS_SndRnicIpv4PdpActInd_001)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)NULL));

    MOCKER(Ps_SendMsg)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_PS_SndRnicIpv4PdpActInd(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SndRnicIpv4PdpActInd, Test_AT_PS_SndRnicIpv4PdpActInd_002)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_PS_SndRnicIpv4PdpActInd(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SndRnicIpv4PdpActInd, Test_AT_PS_SndRnicIpv4PdpActInd_003)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_PS_SndRnicIpv4PdpActInd(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_SndRnicIpv6PdpActInd: public ::testing::Test
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


TEST_F(Test_AT_PS_SndRnicIpv6PdpActInd, Test_AT_PS_SndRnicIpv6PdpActInd_001)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)NULL));

    MOCKER(Ps_SendMsg)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_PS_SndRnicIpv6PdpActInd(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SndRnicIpv6PdpActInd, Test_AT_PS_SndRnicIpv6PdpActInd_002)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_PS_SndRnicIpv6PdpActInd(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SndRnicIpv6PdpActInd, Test_AT_PS_SndRnicIpv6PdpActInd_003)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_PS_SndRnicIpv6PdpActInd(ucCid, &stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_SndRnicPdpDeactInd: public ::testing::Test
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


TEST_F(Test_AT_PS_SndRnicPdpDeactInd, Test_AT_PS_SndRnicPdpDeactInd_001)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;
    enPdpType = TAF_PDP_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)NULL));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_PS_SndRnicPdpDeactInd(ucCid, &stEvent, enPdpType);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SndRnicPdpDeactInd, Test_AT_PS_SndRnicPdpDeactInd_002)
{
    VOS_UINT8                           ucCid;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;

    ucCid = 1;
    stEvent.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stEvent.ucCid = 1;
    stEvent.ucRabId = 5;
    enPdpType = TAF_PDP_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(stEvent.stCtrl.usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    AT_PS_SndRnicPdpDeactInd(ucCid, &stEvent, enPdpType);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_GetCallStateByCid: public ::testing::Test
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


TEST_F(Test_AT_PS_GetCallStateByCid, Test_AT_PS_GetCallStateByCid_001)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCid;
    AT_PDP_STATE_ENUM_U8                enPdpState;

    usClientId = AT_CLIENT_ID_APP;

    ucCallId = 0;

    ucCid = 1;

    enPdpState = AT_PS_GetCallStateByCid(usClientId, ucCallId, ucCid);

    EXPECT_EQ(enPdpState, enPdpState);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_HangupSingleStackConn: public ::testing::Test
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


TEST_F(Test_AT_PS_HangupSingleStackConn, Test_AT_PS_HangupSingleStackConn_001)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT32                          ulRslt;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_APP;

    ucCallId = 0;

    enPdpType = TAF_PDP_IPV4;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    pstCallEntity->ucIpv4Cid = 1;
    pstCallEntity->enIpv4State = AT_PDP_STATE_IDLE;

    ulRslt = AT_PS_HangupSingleStackConn(usClientId, ucCallId, enPdpType);

    EXPECT_EQ(VOS_ERR, ulRslt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_HangupSingleStackConn, Test_AT_PS_HangupSingleStackConn_002)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT32                          ulRslt;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_APP;

    ucCallId = 0;

    enPdpType = TAF_PDP_IPV4;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    pstCallEntity->ucIpv4Cid = 1;
    pstCallEntity->enIpv4State = AT_PDP_STATE_ACTED;

    MOCKER(TAF_PS_CallEnd)
    .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRslt = AT_PS_HangupSingleStackConn(usClientId, ucCallId, enPdpType);

    EXPECT_EQ(VOS_ERR, ulRslt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_HangupSingleStackConn, Test_AT_PS_HangupSingleStackConn_004)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucCallId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT32                          ulRslt;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_APP;

    ucCallId = 0;

    enPdpType = TAF_PDP_IPV4;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    pstCallEntity->ucIpv4Cid = 1;
    pstCallEntity->enIpv4State = AT_PDP_STATE_BUTT;

    ulRslt = AT_PS_HangupSingleStackConn(usClientId, ucCallId, enPdpType);

    EXPECT_EQ(VOS_ERR, ulRslt);

    // 执行检查
    GlobalMockObject::verify();
}

class Test_AT_PS_TransCidToCallId: public ::testing::Test
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


TEST_F(Test_AT_PS_TransCidToCallId, Test_AT_PS_TransCidToCallId_001)
{
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, AT_PS_TransCidToCallId(0, TAF_MAX_CID + 1));

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_PS_IsIpv6Support: public ::testing::Test
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

        MOCKER(mdrv_sysboot_register_reset_notify)
            .defaults()
            .will(returnValue((int)0));

        MOCKER(hifireset_regcbfunc)
            .defaults()
            .will(returnValue((int)0));

        At_PidInit(VOS_IP_INITIAL);

    }

    void TearDown()
    {
    }
};


TEST_F(Test_AT_PS_IsIpv6Support, Test_AT_PS_IsIpv6Support_001)
{
    AT_GetCommPsCtxAddr()->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;

    EXPECT_EQ(VOS_FALSE, AT_PS_IsIpv6Support());

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_AppRcvIpv6LinkMtu: public ::testing::Test
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


TEST_F(Test_AT_AppRcvIpv6LinkMtu,Test_AT_AppRcvIpv6LinkMtu_001)
{
    /*变量定义*/
    VOS_UINT32                          ulMtu;

    /*本地变量初始化*/
    ulMtu = 1500;

    /*全局变量初始化*/
    g_stAtAppPdpEntity.stUsrInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)g_stAtAppPdpEntity.stUsrInfo.enPortIndex), any(), any());

    /*调用被测函数 */
    AT_AppRcvIpv6LinkMtu(ulMtu);

    /* 结果验证*/

    GlobalMockObject::verify();
}


class Test_AT_ModemPsRspPdpActEvtCnfProc: public ::testing::Test
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


TEST_F(Test_AT_ModemPsRspPdpActEvtCnfProc,Test_AT_ModemPsRspPdpActEvtCnfProc_001)
{
    /*变量定义*/
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;

    /*本地变量初始化*/
    ucIndex   = AT_CLIENT_TAB_MODEM_INDEX;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.stPdpAddr.enPdpType         = TAF_PDP_IPV4;
    stEvent.bitOpPdpAddr                = VOS_TRUE;
    stEvent.stDns.bitOpPrimDnsAddr      = VOS_TRUE;
    stEvent.stDns.bitOpSecDnsAddr       = VOS_TRUE;
    stEvent.stNbns.bitOpPrimNbnsAddr    = VOS_TRUE;
    stEvent.stNbns.bitOpSecNbnsAddr     = VOS_TRUE;
    stEvent.stGateWay.bitOpGateWayAddr  = VOS_TRUE;

    /*调用被测函数 */
    AT_ModemPsRspPdpActEvtCnfProc(ucIndex, &stEvent);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemPsRspPdpActEvtCnfProc,Test_AT_ModemPsRspPdpActEvtCnfProc_002)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    VOS_UINT8                           ucIndex;

    stEvent.stCtrl.usClientId           = AT_CLIENT_ID_MODEM;
    stEvent.ucRabId                     = 15;
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;

    gastAtClientTab[ucIndex].usPppId    = 1;

    MOCKER(Ppp_RcvConfigInfoInd)
        .stubs()
        .with(eq(1), any());

    AT_ModemPsRspPdpActEvtCnfProc(ucIndex, &stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
//
///*******************************************************************
//测试用例编号      : Test_AT_ModemPsRspPdpDeactEvtCnfProc_003
//测试用例标题      : PPP拨号,收到网络侧PDP去激活消息处理
//预期结果          : 调用Share PDP特性相关的处理
//修改历史     :
//1.日   期  : 2013-06-19
//  修改内容 : 新建CASE
// *******************************************************************/
//TEST_F(Test_AT_ModemPsRspPdpDeactEvtCnfProc,Test_AT_ModemPsRspPdpDeactEvtCnfProc_003)
//{
//    /*变量定义*/
//    VOS_UINT8                           ucIndex;
//    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
//
//    /*本地变量初始化*/
//    ucIndex   = AT_CLIENT_TAB_MODEM_INDEX;
//
//    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
//
//    /*调用被测函数 */
//    AT_ModemPsRspPdpDeactEvtCnfProc(ucIndex, &stEvent);
//
//    /* 结果验证*/
//
//    GlobalMockObject::verify();
//}


class Test_AT_PS_ProcSharePdpStateChange: public ::testing::Test
{
public:
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;

    void SetUp()
    {
        UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_PS_ProcSharePdpStateChange,Test_AT_PS_ProcSharePdpStateChange_001)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;

    /*本地变量初始化*/
    enPdpType   = TAF_PDP_IPV4;

    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_FALSE;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    pstCommPsCtx->ucSharePdpFlag = VOS_TRUE;

    /*函数打桩*/
    MOCKER(AT_PS_GetRptEndResultFunc)
        .expects(never())
        .will(returnValue((AT_PS_RPT_END_RSLT_FUNC)VOS_NULL_PTR));

    /*调用被测函数 */
    AT_PS_ProcActSharePdpState(&stEvent, enPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpStateChange,Test_AT_PS_ProcSharePdpStateChange_002)
{
    /*变量定义*/
    VOS_UINT8                           ucModemId;
    VOS_UINT8                           ucClientId;
    VOS_UINT32                          ulNvId;

    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;
    VOS_CHAR                            acExpectedStr[]  = "\r\n^DCONN:1,\"IPV4\"\r\n";

    /*本地变量初始化*/
    enPdpType   = TAF_PDP_IPV4;
    ucModemId   = MODEM_ID_0;
    ulNvId      = en_NV_Item_SHARE_PDP_INFO;
    ucClientId  = AT_CLIENT_TAB_APP_INDEX;

    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.ucCid       = 1;
    stEvent.ucRabId     = 5;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    pstCommPsCtx->ucSharePdpFlag = VOS_TRUE;

    /*函数打桩*/

    MOCKER(AT_PS_SaveRnicPdpDhcpPara)
        .stubs()
        .with(eq(enPdpType),mirror((TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *)&stEvent, (VOS_UINT32)sizeof(stEvent)));

    MOCKER(AT_PS_SendRnicPdnInfoCfgInd)
        .stubs()
        .with(eq(enPdpType),any(),any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .stubs()
        .with(eq(ucClientId), mirror((VOS_UINT8 *)acExpectedStr, VOS_StrLen(acExpectedStr)), any());

    /*调用被测函数 */
    AT_PS_ProcActSharePdpState(&stEvent, enPdpType);

    /* 结果验证*/
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpStateChange,Test_AT_PS_ProcSharePdpStateChange_003)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;
    VOS_CHAR                            acExpectedStr[]  = "\r\n^DCONN:1,\"IPV4\"\r\n";

    /*本地变量初始化*/
    enPdpType   = TAF_PDP_IPV4;

    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.ucCid    = 1;
    stEvent.ucRabId  = 5;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    pstCommPsCtx->ucSharePdpFlag = VOS_TRUE;

    /*函数打桩*/

    MOCKER(AT_PS_GetRptConnResultFunc)
        .stubs()
        .will(returnValue((AT_PS_RPT_CONN_RSLT_FUNC)VOS_NULL_PTR));

    MOCKER(At_SendResultData)
        .expects(never());

    /*调用被测函数 */
    AT_PS_ProcActSharePdpState(&stEvent, enPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_PS_ProcSharePdpStateChange,Test_AT_PS_ProcSharePdpStateChange_004)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;

    /*本地变量初始化*/
    enPdpType   = TAF_PDP_IPV6;

    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.ucCid    = 1;
    stEvent.ucRabId  = 5;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    pstCommPsCtx->ucSharePdpFlag = VOS_TRUE;

    /*函数打桩*/

    MOCKER(AT_PS_SaveRnicPdpDhcpPara)
        .stubs()
        .with(eq((TAF_PDP_TYPE_ENUM_UINT8)TAF_PDP_IPV6),mirror((TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *)&stEvent,sizeof(stEvent)));

    /*调用被测函数 */
    AT_PS_ProcActSharePdpState(&stEvent, enPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpStateChange,Test_AT_PS_ProcSharePdpStateChange_005)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType2;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;
    VOS_CHAR                            acExpectedStr[]  = "\r\n^DCONN:1,\"IPV4\"\r\n";

    VOS_UINT8                           ucModemId;
    VOS_UINT8                           ucClientId;
    VOS_UINT32                          ulNvId;

    /*本地变量初始化*/
    enPdpType   = TAF_PDP_IPV4V6;

    enPdpType2   = TAF_PDP_IPV4;
    ucModemId   = MODEM_ID_0;
    ulNvId      = en_NV_Item_SHARE_PDP_INFO;
    ucClientId  = AT_CLIENT_TAB_APP_INDEX;

    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.ucCid    = 1;
    stEvent.ucRabId  = 5;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    pstCommPsCtx->ucSharePdpFlag = VOS_TRUE;

    /*函数打桩*/

    MOCKER(AT_PS_SaveRnicPdpDhcpPara)
        .stubs()
        .with(eq(enPdpType),mirror((TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *)&stEvent,sizeof(stEvent)));

    MOCKER(AT_PS_SendRnicPdnInfoCfgInd)
        .stubs()
        .with(eq(enPdpType2),any(),any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .stubs()
        .with(eq(ucClientId), mirror((VOS_UINT8 *)acExpectedStr, VOS_StrLen(acExpectedStr)), any());

    /*调用被测函数 */
    AT_PS_ProcActSharePdpState(&stEvent, enPdpType);

    /* 结果验证*/
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpStateChange,Test_AT_PS_ProcSharePdpStateChange_006)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;

    /*本地变量初始化*/
    enPdpType   = TAF_PDP_IPV4V6;

    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stEvent.ucCid    = 1;
    stEvent.ucRabId  = 5;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    pstCommPsCtx->ucSharePdpFlag = VOS_TRUE;

    /*函数打桩*/
    MOCKER(AT_PS_GetRptConnResultFunc)
        .stubs()
        .will(returnValue((AT_PS_RPT_CONN_RSLT_FUNC)VOS_NULL_PTR));

    MOCKER(At_SendResultData)
        .expects(never());

    /*调用被测函数 */
    AT_PS_ProcActSharePdpState(&stEvent, enPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpStateChange,Test_AT_PS_ProcSharePdpStateChange_007)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;

    /*本地变量初始化*/
    enPdpType   = TAF_PDP_IPV4V6;

    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stEvent.ucCid    = 1;
    stEvent.ucRabId  = 5;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    pstCommPsCtx->ucSharePdpFlag = VOS_TRUE;

    /*函数打桩*/
    MOCKER(AT_PS_GetRptEndResultFunc)
        .stubs()
        .will(returnValue((AT_PS_RPT_END_RSLT_FUNC)VOS_NULL_PTR));

    MOCKER(At_SendResultData)
        .expects(never());

    /*调用被测函数 */
    AT_PS_ProcDeactSharePdpState(&stEvent, enPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpStateChange,Test_AT_PS_ProcSharePdpStateChange_008)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;
    VOS_CHAR                            acExpectedStr[]  = "\r\n^DEND:1,127,\"IPV4\"\r\n\r\n^DEND:1,127,\"IPV6\"\r\n";

    VOS_UINT8                           ucModemId;;
    VOS_UINT8                           ucClientId;
    VOS_UINT32                          ulNvId;

    /*本地变量初始化*/
    enPdpType   = TAF_PDP_IPV4V6;
    ucModemId   = MODEM_ID_0;
    ulNvId      = en_NV_Item_SHARE_PDP_INFO;
    ucClientId  = AT_CLIENT_TAB_APP_INDEX;

    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));
    stEvent.ucCid       = 1;
    stEvent.enCause     = 127;
    stEvent.ucRabId     = 5;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    pstCommPsCtx->ucSharePdpFlag = VOS_TRUE;

    /*函数打桩*/
    MOCKER(AT_PS_SendRnicPdnInfoRelInd)
        .stubs()
        .with(eq(stEvent.ucRabId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_SendResultData)
        .stubs()
        .with(eq(ucClientId), mirror((VOS_UINT8 *)acExpectedStr, VOS_StrLen(acExpectedStr)), any());

    /*调用被测函数 */
    AT_PS_ProcDeactSharePdpState(&stEvent, enPdpType);

    /* 结果验证*/
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
#endif


class Test_AT_PS_ProcSharePdpIpv6RaInfo: public ::testing::Test
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


TEST_F(Test_AT_PS_ProcSharePdpIpv6RaInfo,Test_AT_PS_ProcSharePdpIpv6RaInfo_001)
{
    /*变量定义*/
    TAF_PS_IPV6_INFO_IND_STRU                     stRaInfoNotifyInd;
    TAF_NVIM_SHARE_PDP_INFO_STRU                            stSharePdpInfo;

    /*本地变量初始化*/
    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_FALSE;

    PS_MEM_SET(&stRaInfoNotifyInd, 0x00, sizeof(TAF_PS_IPV6_INFO_IND_STRU));

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0),eq((VOS_UINT16)en_NV_Item_SHARE_PDP_INFO),outBoundP((void *)&stSharePdpInfo),eq((VOS_UINT32)sizeof(stSharePdpInfo)))
        .will(returnValue((VOS_UINT32)NV_OK));

    /*全局变量初始化*/
    AT_ReadSharePdpInfoNV();

    /*调用被测函数 */
    AT_PS_ProcSharePdpIpv6RaInfo(&stRaInfoNotifyInd);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpIpv6RaInfo,Test_AT_PS_ProcSharePdpIpv6RaInfo_002)
{
    /*变量定义*/
    TAF_PS_IPV6_INFO_IND_STRU                     stRaInfoNotifyInd;
    TAF_NVIM_SHARE_PDP_INFO_STRU                            stSharePdpInfo;

    /*本地变量初始化*/
    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stRaInfoNotifyInd, 0x00, sizeof(TAF_PS_IPV6_INFO_IND_STRU));
    stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum = 0;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0),eq((VOS_UINT16)en_NV_Item_SHARE_PDP_INFO),outBoundP((void *)&stSharePdpInfo),eq((VOS_UINT32)sizeof(stSharePdpInfo)))
        .will(returnValue((VOS_UINT32)NV_OK));

    /*全局变量初始化*/
    AT_ReadSharePdpInfoNV();

    /*调用被测函数 */
    AT_PS_ProcSharePdpIpv6RaInfo(&stRaInfoNotifyInd);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpIpv6RaInfo,Test_AT_PS_ProcSharePdpIpv6RaInfo_003)
{
    /*变量定义*/
    TAF_PS_IPV6_INFO_IND_STRU                     stRaInfoNotifyInd;
    TAF_NVIM_SHARE_PDP_INFO_STRU                            stSharePdpInfo;

    /*本地变量初始化*/
    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stRaInfoNotifyInd, 0x00, sizeof(TAF_PS_IPV6_INFO_IND_STRU));
    stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum = 1;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0),eq((VOS_UINT16)en_NV_Item_SHARE_PDP_INFO),outBoundP((void *)&stSharePdpInfo),eq((VOS_UINT32)sizeof(stSharePdpInfo)))
        .will(returnValue((VOS_UINT32)NV_OK));

    /*全局变量初始化*/
    g_stAtAppRaInfo.bitOpPrefixAddr = VOS_TRUE;
    AT_ReadSharePdpInfoNV();

    /*调用被测函数 */
    AT_PS_ProcSharePdpIpv6RaInfo(&stRaInfoNotifyInd);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpIpv6RaInfo,Test_AT_PS_ProcSharePdpIpv6RaInfo_004)
{
    /*变量定义*/
    TAF_PS_IPV6_INFO_IND_STRU                     stRaInfoNotifyInd;
    TAF_NVIM_SHARE_PDP_INFO_STRU                            stSharePdpInfo;

    /*本地变量初始化*/
    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stRaInfoNotifyInd, 0x00, sizeof(TAF_PS_IPV6_INFO_IND_STRU));
    stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum = 1;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0),eq((VOS_UINT16)en_NV_Item_SHARE_PDP_INFO),outBoundP((void *)&stSharePdpInfo),eq((VOS_UINT32)sizeof(stSharePdpInfo)))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(AT_PS_GetRptConnResultFunc)
        .stubs()
        .will(returnValue((AT_PS_RPT_CONN_RSLT_FUNC)VOS_NULL_PTR));

    /*全局变量初始化*/
    g_stAtAppRaInfo.bitOpPrefixAddr = VOS_FALSE;
    AT_ReadSharePdpInfoNV();

    /*调用被测函数 */
    AT_PS_ProcSharePdpIpv6RaInfo(&stRaInfoNotifyInd);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpIpv6RaInfo,Test_AT_PS_ProcSharePdpIpv6RaInfo_005)
{
    /*变量定义*/
    TAF_PS_IPV6_INFO_IND_STRU                     stRaInfoNotifyInd;
    TAF_NVIM_SHARE_PDP_INFO_STRU                            stSharePdpInfo;
    VOS_CHAR                                                acExpectedStr[]  = "\r\n^DCONN:1,\"IPV6\"\r\n";

    /*本地变量初始化*/
    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stRaInfoNotifyInd, 0x00, sizeof(TAF_PS_IPV6_INFO_IND_STRU));
    stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum = 1;
    stRaInfoNotifyInd.ucCid                    = 1;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0),eq((VOS_UINT16)en_NV_Item_SHARE_PDP_INFO),outBoundP((void *)&stSharePdpInfo),eq((VOS_UINT32)sizeof(stSharePdpInfo)))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(At_SendResultData)
        .stubs()
        .with(any(), mirror((VOS_UINT8 *)acExpectedStr, VOS_StrLen(acExpectedStr)), any());

    MOCKER(AT_PS_SendRnicPdnInfoCfgInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*全局变量初始化*/
    g_stAtAppRaInfo.bitOpPrefixAddr          = VOS_FALSE;
    g_stAtAppPdpEntity.stUsrInfo.ucUsrType   = AT_APP_USER;
    g_stAtAppPdpEntity.stUsrInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
    AT_ReadSharePdpInfoNV();

    /*调用被测函数 */
    AT_PS_ProcSharePdpIpv6RaInfo(&stRaInfoNotifyInd);

    /* 结果验证*/
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ProcSharePdpIpv6RaInfo,Test_AT_PS_ProcSharePdpIpv6RaInfo_006)
{
    /*变量定义*/
    TAF_PS_IPV6_INFO_IND_STRU                     stRaInfoNotifyInd;
    TAF_NVIM_SHARE_PDP_INFO_STRU                            stSharePdpInfo;
    VOS_CHAR                                                acExpectedStr[]  = "\r\n^DCONN:1,\"IPV6\"\r\n";

    /*本地变量初始化*/
    PS_MEM_SET(&stSharePdpInfo, 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));
    stSharePdpInfo.ucEnableFlag = VOS_TRUE;

    PS_MEM_SET(&stRaInfoNotifyInd, 0x00, sizeof(TAF_PS_IPV6_INFO_IND_STRU));
    stRaInfoNotifyInd.ucCid                     = 1;
    stRaInfoNotifyInd.stIpv6RaInfo.ulPrefixNum  = 1;
    stRaInfoNotifyInd.stIpv6RaInfo.bitOpMtu     = VOS_TRUE;
    stRaInfoNotifyInd.stIpv6RaInfo.ulMtu        = 1500;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0),eq((VOS_UINT16)en_NV_Item_SHARE_PDP_INFO),outBoundP((void *)&stSharePdpInfo),eq((VOS_UINT32)sizeof(stSharePdpInfo)))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(At_SendResultData)
        .stubs()
        .with(any(),mirror((VOS_UINT8 *)acExpectedStr, VOS_StrLen(acExpectedStr)), any());

    MOCKER(AT_PS_SendRnicPdnInfoCfgInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*全局变量初始化*/
    g_stAtAppRaInfo.bitOpPrefixAddr = VOS_FALSE;
    g_stAtAppPdpEntity.stUsrInfo.ucUsrType  = AT_APP_USER;
    g_stAtAppPdpEntity.stUsrInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
    AT_ReadSharePdpInfoNV();

    /*调用被测函数 */
    AT_PS_ProcSharePdpIpv6RaInfo(&stRaInfoNotifyInd);

    /* 结果验证*/
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(VOS_TRUE, g_stAtAppRaInfo.bitOpMtuSize);
    EXPECT_EQ(1500, g_stAtAppRaInfo.ulMtuSize);

    GlobalMockObject::verify();
}


class Test_AT_PS_SaveRnicPdpDhcpPara: public ::testing::Test
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


TEST_F(Test_AT_PS_SaveRnicPdpDhcpPara,Test_AT_PS_SaveRnicPdpDhcpPara_001)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV4;
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /*函数打桩*/
    MOCKER(AT_CtrlConnIndProc)
        .stubs()
        .with(mirror((TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *)&stEvent, (VOS_UINT32)sizeof(stEvent)),eq((AT_USER_TYPE)AT_APP_USER));

    /*调用被测函数 */
    AT_PS_SaveRnicPdpDhcpPara(ucPdpType,&stEvent);

    /* 结果验证*/

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_PS_SaveRnicPdpDhcpPara,Test_AT_PS_SaveRnicPdpDhcpPara_002)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV6;
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /*函数打桩*/
    MOCKER(AT_AppCtrlConnIpv6IndProc)
        .stubs();

    /*调用被测函数 */
    AT_PS_SaveRnicPdpDhcpPara(ucPdpType,&stEvent);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SaveRnicPdpDhcpPara,Test_AT_PS_SaveRnicPdpDhcpPara_003)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV4V6;
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /*函数打桩*/
    MOCKER(AT_CtrlConnIndProc)
        .stubs()
        .with(mirror((TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *)&stEvent, (VOS_UINT32)sizeof(stEvent)),eq((AT_USER_TYPE)AT_APP_USER));

    MOCKER(AT_AppCtrlConnIpv6IndProc)
        .stubs();

    /*调用被测函数 */
    AT_PS_SaveRnicPdpDhcpPara(ucPdpType,&stEvent);

    /* 结果验证*/

    GlobalMockObject::verify();
}
#endif


TEST_F(Test_AT_PS_SaveRnicPdpDhcpPara,Test_AT_PS_SaveRnicPdpDhcpPara_004)
{
    /*变量定义*/
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_TYPE_BUTT;
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /*函数打桩*/
    MOCKER(AT_AppSetPdpState)
        .expects(never());

    /*调用被测函数 */
    AT_PS_SaveRnicPdpDhcpPara(ucPdpType,&stEvent);

    /* 结果验证*/

    GlobalMockObject::verify();
}


class Test_AT_PS_ResetRnicPdpDhcpPara: public ::testing::Test
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


TEST_F(Test_AT_PS_ResetRnicPdpDhcpPara,Test_AT_PS_ResetRnicPdpDhcpPara_001)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV4;

    /*函数打桩*/
    MOCKER(AT_AppDhcpReset)
        .expects(exactly(1));

    /*调用被测函数 */
    AT_PS_ResetRnicPdpDhcpPara(ucPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_PS_ResetRnicPdpDhcpPara,Test_AT_PS_ResetRnicPdpDhcpPara_002)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV6;

    /*函数打桩*/
    MOCKER(AT_AppDhcpv6Reset)
        .expects(exactly(1));

    /*调用被测函数 */
    AT_PS_ResetRnicPdpDhcpPara(ucPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_ResetRnicPdpDhcpPara,Test_AT_PS_ResetRnicPdpDhcpPara_003)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV4V6;

    /*函数打桩*/
    MOCKER(AT_AppDhcpReset)
        .expects(exactly(1));

    MOCKER(AT_AppDhcpv6Reset)
        .expects(exactly(1));

    /*调用被测函数 */
    AT_PS_ResetRnicPdpDhcpPara(ucPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}
#endif


TEST_F(Test_AT_PS_ResetRnicPdpDhcpPara,Test_AT_PS_ResetRnicPdpDhcpPara_004)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_TYPE_BUTT;

    /*函数打桩*/
    MOCKER(AT_AppSetPdpState)
        .expects(never());

    /*调用被测函数 */
    AT_PS_ResetRnicPdpDhcpPara(ucPdpType);

    /* 结果验证*/

    GlobalMockObject::verify();
}


class Test_AT_PS_SendRnicPdnInfoCfgInd: public ::testing::Test
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


TEST_F(Test_AT_PS_SendRnicPdnInfoCfgInd,Test_AT_PS_SendRnicPdnInfoCfgInd_001)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;
    VOS_UINT8                           ucRabId;
    AT_PDP_ENTITY_STRU                  stAppPdpEntity;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV4;
    ucRabId   = 5;
    PS_MEM_SET(&stAppPdpEntity,0x00,sizeof(AT_PDP_ENTITY_STRU));

    /*函数打桩*/
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    /*调用被测函数 */
    ulRslt = AT_PS_SendRnicPdnInfoCfgInd(ucPdpType,ucRabId,&stAppPdpEntity);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SendRnicPdnInfoCfgInd,Test_AT_PS_SendRnicPdnInfoCfgInd_002)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;
    VOS_UINT8                           ucRabId;
    AT_PDP_ENTITY_STRU                  stAppPdpEntity;
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV4;
    ucRabId   = 5;
    PS_MEM_SET(&stAppPdpEntity,0x00,sizeof(AT_PDP_ENTITY_STRU));
    PS_MEM_SET(&stRnicPdnCfgInd,0x00,sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));

    stRnicPdnCfgInd.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stRnicPdnCfgInd.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stRnicPdnCfgInd.ulSenderPid         = WUEPS_PID_AT;
    stRnicPdnCfgInd.ulReceiverPid       = ACPU_PID_RNIC;
    stRnicPdnCfgInd.ulLength            = sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stRnicPdnCfgInd.bitOpIpv4PdnInfo    = VOS_TRUE;
    stRnicPdnCfgInd.enMsgId             = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId             = ucRabId;
    stRnicPdnCfgInd.ucRmNetId           = RNIC_RM_NET_ID_0;

    /*函数打桩*/
    MOCKER(Ps_SendMsg)
        .stubs()
        .with(any(),any(),eq(WUEPS_PID_AT),mirror((void *)&stRnicPdnCfgInd, (VOS_UINT32)sizeof(stRnicPdnCfgInd)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*调用被测函数 */
    AT_PS_SendRnicPdnInfoCfgInd(ucPdpType,ucRabId,&stAppPdpEntity);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SendRnicPdnInfoCfgInd,Test_AT_PS_SendRnicPdnInfoCfgInd_003)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;
    VOS_UINT8                           ucRabId;
    AT_PDP_ENTITY_STRU                  stAppPdpEntity;
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV6;
    ucRabId   = 5;
    PS_MEM_SET(&stAppPdpEntity,0x00,sizeof(AT_PDP_ENTITY_STRU));
    PS_MEM_SET(&stRnicPdnCfgInd,0x00,sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));

    stRnicPdnCfgInd.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stRnicPdnCfgInd.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stRnicPdnCfgInd.ulSenderPid         = WUEPS_PID_AT;
    stRnicPdnCfgInd.ulReceiverPid       = ACPU_PID_RNIC;
    stRnicPdnCfgInd.ulLength            = sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stRnicPdnCfgInd.bitOpIpv6PdnInfo    = VOS_TRUE;
    stRnicPdnCfgInd.enMsgId             = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId             = ucRabId;
    stRnicPdnCfgInd.ucRmNetId           = RNIC_RM_NET_ID_0;

    /*函数打桩*/
    MOCKER(Ps_SendMsg)
        .stubs()
        .with(any(),any(),eq(WUEPS_PID_AT),mirror((void *)&stRnicPdnCfgInd, (VOS_UINT32)sizeof(stRnicPdnCfgInd)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*调用被测函数 */
    AT_PS_SendRnicPdnInfoCfgInd(ucPdpType,ucRabId,&stAppPdpEntity);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SendRnicPdnInfoCfgInd,Test_AT_PS_SendRnicPdnInfoCfgInd_004)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;
    VOS_UINT8                           ucRabId;
    AT_PDP_ENTITY_STRU                  stAppPdpEntity;
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_TYPE_BUTT;
    ucRabId   = 5;
    PS_MEM_SET(&stAppPdpEntity,0x00,sizeof(AT_PDP_ENTITY_STRU));
    PS_MEM_SET(&stRnicPdnCfgInd,0x00,sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));

    stRnicPdnCfgInd.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stRnicPdnCfgInd.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stRnicPdnCfgInd.ulSenderPid         = WUEPS_PID_AT;
    stRnicPdnCfgInd.ulReceiverPid       = ACPU_PID_RNIC;
    stRnicPdnCfgInd.ulLength            = sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stRnicPdnCfgInd.enMsgId             = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId             = ucRabId;
    stRnicPdnCfgInd.ucRmNetId           = RNIC_RM_NET_ID_0;

    /*函数打桩*/
    MOCKER(V_FreeMsg)
        .stubs()
        .with(eq((VOS_PID)WUEPS_PID_AT),any(),any(),any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*调用被测函数 */
    AT_PS_SendRnicPdnInfoCfgInd(ucPdpType,ucRabId,&stAppPdpEntity);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SendRnicPdnInfoCfgInd,Test_AT_PS_SendRnicPdnInfoCfgInd_005)
{
    /*变量定义*/
    TAF_PDP_TYPE_ENUM_UINT8                        ucPdpType;
    VOS_UINT8                           ucRabId;
    AT_PDP_ENTITY_STRU                  stAppPdpEntity;
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    ucPdpType = TAF_PDP_IPV4;
    ucRabId   = 5;
    PS_MEM_SET(&stAppPdpEntity,0x00,sizeof(AT_PDP_ENTITY_STRU));
    PS_MEM_SET(&stRnicPdnCfgInd,0x00,sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));

    stRnicPdnCfgInd.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stRnicPdnCfgInd.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stRnicPdnCfgInd.ulSenderPid         = WUEPS_PID_AT;
    stRnicPdnCfgInd.ulReceiverPid       = ACPU_PID_RNIC;
    stRnicPdnCfgInd.ulLength            = sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stRnicPdnCfgInd.bitOpIpv4PdnInfo    = VOS_TRUE;
    stRnicPdnCfgInd.enMsgId             = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId             = ucRabId;
    stRnicPdnCfgInd.ucRmNetId           = RNIC_RM_NET_ID_0;

    /*函数打桩*/
    MOCKER(Ps_SendMsg)
        .stubs()
        .with(any(),any(),eq((VOS_PID)WUEPS_PID_AT),mirror((void *)&stRnicPdnCfgInd, (VOS_UINT32)sizeof(stRnicPdnCfgInd)))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /*调用被测函数 */
    ulRslt = AT_PS_SendRnicPdnInfoCfgInd(ucPdpType,ucRabId,&stAppPdpEntity);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_PS_SendRnicPdnInfoRelInd: public ::testing::Test
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


TEST_F(Test_AT_PS_SendRnicPdnInfoRelInd,Test_AT_PS_SendRnicPdnInfoRelInd_001)
{
    /*变量定义*/
    VOS_UINT8                           ucRabId;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    ucRabId = 0;

    /*函数打桩*/
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    /*调用被测函数 */
    ulRslt = AT_PS_SendRnicPdnInfoRelInd(ucRabId);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SendRnicPdnInfoRelInd,Test_AT_PS_SendRnicPdnInfoRelInd_002)
{
    /*变量定义*/
    VOS_UINT8                           ucRabId;
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;

    /*本地变量初始化*/
    ucRabId                     = 5;

    PS_MEM_SET(&stRnicPdnRelInd,0x00,sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stRnicPdnRelInd.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stRnicPdnRelInd.ulSenderPid         = WUEPS_PID_AT;
    stRnicPdnRelInd.ulReceiverPid       = ACPU_PID_RNIC;
    stRnicPdnRelInd.ulLength            = sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = ucRabId;
    stRnicPdnRelInd.ucRmNetId           = RNIC_RM_NET_ID_0;

    /*函数打桩*/
    MOCKER(Ps_SendMsg)
        .stubs()
        .with(any(),any(),eq((VOS_PID)WUEPS_PID_AT),mirror((void *)&stRnicPdnRelInd,sizeof(stRnicPdnRelInd)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*调用被测函数 */
    AT_PS_SendRnicPdnInfoRelInd(ucRabId);

    /* 结果验证*/

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PS_SendRnicPdnInfoRelInd,Test_AT_PS_SendRnicPdnInfoRelInd_003)
{
    /*变量定义*/
    VOS_UINT8                           ucRabId;
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    ucRabId                     = 5;

    PS_MEM_SET(&stRnicPdnRelInd,0x00,sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stRnicPdnRelInd.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stRnicPdnRelInd.ulSenderPid         = WUEPS_PID_AT;
    stRnicPdnRelInd.ulReceiverPid       = ACPU_PID_RNIC;
    stRnicPdnRelInd.ulLength            = sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = ucRabId;
    stRnicPdnRelInd.ucRmNetId           = RNIC_RM_NET_ID_0;

    /*函数打桩*/
    MOCKER(Ps_SendMsg)
        .stubs()
        .with(any(),any(),eq((VOS_PID)WUEPS_PID_AT),mirror((void *)&stRnicPdnRelInd,sizeof(stRnicPdnRelInd)))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /*调用被测函数 */
    ulRslt = AT_PS_SendRnicPdnInfoRelInd(ucRabId);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_NdisIpv6ActCnfProc: public ::testing::Test
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

        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_AT_NdisIpv6ActCnfProc, Test_AT_NdisIpv6ActCnfProc_001)
{
    // 变量声明
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;
    VOS_CHAR                            acExpectedStr[] = "\r\n^DCONN:1,\"IPV6\"\r\n";

    // 参数初始化
    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    stEvent.ucCid               = 1;
    stEvent.ucRabId             = 5;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV6;
    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_NDIS;
    stEvent.enCause             = TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED;

    // 初始化全局变量
    g_enAtFirstNdisActPdpType   = TAF_PDP_IPV4V6;
    g_enAtNdisActPdpType        = TAF_PDP_IPV4V6;

    // MOCKER操作

    // 调用被测函数
    AT_NdisIpv6ActCnfProc(&stEvent);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_NdisIpv6ActCnfProc, Test_AT_NdisIpv6ActCnfProc_002)
{
    // 变量声明
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stEvent;

    // 参数初始化
    PS_MEM_SET(&stEvent, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    stEvent.ucCid               = 1;
    stEvent.ucRabId             = 5;
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV6;
    stEvent.stCtrl.usClientId   = AT_CLIENT_ID_NDIS;
    stEvent.enCause             = TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED;

    // 初始化全局变量
    g_enAtFirstNdisActPdpType   = TAF_PDP_IPV4V6;
    g_enAtNdisActPdpType        = 0;

    // MOCKER操作

    // 调用被测函数
    AT_NdisIpv6ActCnfProc(&stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_Ipv4AddrAtoi: public ::testing::Test
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


TEST_F(Test_AT_Ipv4AddrAtoi, Test_AT_Ipv4AddrAtoi_001)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString     = VOS_NULL_PTR;
    VOS_UINT8    pucNumber[4] = {0};

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv4AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv4AddrAtoi, Test_AT_Ipv4AddrAtoi_002)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.1.1";
    VOS_UINT8   *pucNumber      = VOS_NULL_PTR;

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv4AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_Ipv4AddrAtoi, Test_AT_Ipv4AddrAtoi_003)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.1.1    ";
    VOS_UINT8    pucNumber[4]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv4AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv4AddrAtoi, Test_AT_Ipv4AddrAtoi_004)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.1111.1";
    VOS_UINT8    pucNumber[4]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv4AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv4AddrAtoi, Test_AT_Ipv4AddrAtoi_005)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.256.1";
    VOS_UINT8    pucNumber[4]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv4AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv4AddrAtoi, Test_AT_Ipv4AddrAtoi_006)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.2a.1";
    VOS_UINT8    pucNumber[4]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv4AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv4AddrAtoi, Test_AT_Ipv4AddrAtoi_007)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.2.256";
    VOS_UINT8    pucNumber[4]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv4AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv4AddrAtoi, Test_AT_Ipv4AddrAtoi_008)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.2.2";
    VOS_UINT8    pucNumber[4]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv4AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(192, pucNumber[0]);
    EXPECT_EQ(168, pucNumber[1]);
    EXPECT_EQ(2, pucNumber[2]);
    EXPECT_EQ(2, pucNumber[3]);

    GlobalMockObject::verify();
}


class Test_AT_Ipv6AddrAtoi: public ::testing::Test
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


TEST_F(Test_AT_Ipv6AddrAtoi, Test_AT_Ipv6AddrAtoi_001)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString     = VOS_NULL_PTR;
    VOS_UINT8    pucNumber[16] = {0};

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv6AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv6AddrAtoi, Test_AT_Ipv6AddrAtoi_002)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.0.1.13.23.56.24.192.168.0.1.13.23.56.24";
    VOS_UINT8   *pucNumber      = VOS_NULL_PTR;

    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv6AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_Ipv6AddrAtoi, Test_AT_Ipv6AddrAtoi_003)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.0.1.13.23.56.24.192.168.0.1.13.23.56.24 ";
    VOS_UINT8    pucNumber[16]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv6AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv6AddrAtoi, Test_AT_Ipv4AddrAtoi_004)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "1921.168.0.1.13.23.56.24.192.168.0.1.13.23.56.24";
    VOS_UINT8    pucNumber[16]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv6AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv6AddrAtoi, Test_AT_Ipv6AddrAtoi_005)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "256.168.0.1.13.23.56.24.192.168.0.1.13.23.56.24";
    VOS_UINT8    pucNumber[16]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv6AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv6AddrAtoi, Test_AT_Ipv6AddrAtoi_006)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "19a.168.0.1.13.23.56.24.192.168.0.1.13.23.56.24";
    VOS_UINT8    pucNumber[16]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv6AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv6AddrAtoi, Test_AT_Ipv6AddrAtoi_007)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.0.1.13.23.56.24.192.168.0.1.13.23.56.256";
    VOS_UINT8    pucNumber[16]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv6AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_Ipv6AddrAtoi, Test_AT_Ipv6AddrAtoi_008)
{
    // 变量声明
    VOS_UINT32   ulRet;
    VOS_CHAR    *pcString       = "192.168.0.1.13.23.56.24.192.168.0.1.13.23.56.200";
    VOS_UINT8    pucNumber[16]   = {0};


    // 参数初始化

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = AT_Ipv6AddrAtoi(pcString, pucNumber);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(192, pucNumber[0]);
    EXPECT_EQ(168, pucNumber[1]);
    EXPECT_EQ(0, pucNumber[2]);
    EXPECT_EQ(1, pucNumber[3]);
    EXPECT_EQ(13, pucNumber[4]);
    EXPECT_EQ(23, pucNumber[5]);
    EXPECT_EQ(56, pucNumber[6]);
    EXPECT_EQ(24, pucNumber[7]);
    EXPECT_EQ(192, pucNumber[8]);
    EXPECT_EQ(168, pucNumber[9]);
    EXPECT_EQ(0, pucNumber[10]);
    EXPECT_EQ(1, pucNumber[11]);
    EXPECT_EQ(13, pucNumber[12]);
    EXPECT_EQ(23, pucNumber[13]);
    EXPECT_EQ(56, pucNumber[14]);
    EXPECT_EQ(200, pucNumber[15]);

    GlobalMockObject::verify();
}


class Test_AT_EnableNdisFlowCtl: public ::testing::Test
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


TEST_F(Test_AT_EnableNdisFlowCtl, Test_AT_EnableNdisFlowCtl_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_EnableNdisFlowCtl(0, 0);

    // 执行检查

    GlobalMockObject::verify();
}


class Test_AT_DisableNdisFlowCtl: public ::testing::Test
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


TEST_F(Test_AT_DisableNdisFlowCtl, Test_AT_DisableNdisFlowCtl_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_DisableNdisFlowCtl(0, 0);

    // 执行检查

    GlobalMockObject::verify();
}

