/*****************************************************************************
1 头文件包含
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicProcMsg.h"


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#if 0

/*****************************************************************************
2 函数声明
*****************************************************************************/


/*****************************************************************************
2 用例实现
*****************************************************************************/


/*****************************************************************************
类名       : Test_RNIC_RcvAtIpv4PdpActInd
功能描述   : RNIC_RcvAtIpv4PdpActInd UT工程类
修改历史   :
1.日   期  : 2012-12-11
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtIpv4PdpActInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4PdpActInd_001
测试用例标题      : modem0,当前为手动拨号模式，RNIC收到AT消息ID_AT_RNIC_IPV4_PDP_ACT_IND的处理
预期结果          : 拨号保护定时器停止，拨号断开定时器未启动,PDP上下文中IPV4为已激活状态
修改历史   :
1.日   期  : 2012-12-11
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_001)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 8;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);
    /* 停止拨号断开定时器 */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* 启动拨号保护定时器 */


	MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv4PdpActInd.ucRabId), any());

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);

    /* 获取流量统计定时器的状态 */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* 获取拨号断开定时器的状态 */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* 获取拨号保护定时器的状态 */

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4PdpActInd_002
测试用例标题      : modem1,当前为手动拨号模式，RNIC收到AT消息ID_AT_RNIC_IPV4_PDP_ACT_IND的处理
预期结果          : 拨号保护定时器停止，拨号断开定时器未启动,PDP上下文中IPV4为已激活状态
修改历史   :
1.日   期  : 2012-12-11
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_002)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
	VOS_UINT8                           ucNewBabId;

	ucNewBabId = 72;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 8;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_1;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);
    /* 停止拨号断开定时器 */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* 启动拨号保护定时器 */


	MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(ucNewBabId), any());

    MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);

     /* 获取流量统计定时器的状态 */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* 获取拨号断开定时器的状态 */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* 获取拨号保护定时器的状态 */

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4PdpActInd_003
测试用例标题      : 当前为按需拨号模式,且PDP激活成功。RNIC收到AT消息ID_AT_RNIC_IPV4_PDP_ACT_IND的处理
预期结果          : 拨号断开定时器启动，拨号保护定时器停止,PDP上下文中IPV4为已激活状态
修改历史   :
1.日   期  : 2012-12-11
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_003)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为按需拨号模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 8;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);
    /* 停止拨号断开定时器 */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* 启动拨号保护定时器 */

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv4PdpActInd.ucRabId), any());

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);

     /* 获取流量统计定时器的状态 */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* 获取拨号断开定时器的状态 */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* 获取拨号保护定时器的状态 */

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4PdpActInd_004
测试用例标题      : 填充RabID失败
预期结果          : 返回错误
修改历史   :
1.日   期  : 2012-12-11
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_004)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为按需拨号模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 8;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_BUTT;

	MOCKER(ADS_DL_RegDlDataCallback).expects(never());
    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4PdpActInd_005
测试用例标题      : 存储rabid对应网卡失败
预期结果          : 返回错误
修改历史   :
1.日   期  : 2012-12-11
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_005)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为按需拨号模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 4;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

	MOCKER(ADS_DL_RegDlDataCallback).expects(never());
    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_RcvAtIpv6PdpActInd
功能描述   : RNIC_RcvAtIpv6PdpActInd UT工程类
修改历史   :
1.日   期  : 2012-12-11
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtIpv6PdpActInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv6PdpActInd_001
测试用例标题      : modem0,当前为手动拨号模式，RNIC收到AT消息ID_AT_RNIC_IPV6_PDP_ACT_IND的处理
预期结果          : 启动流量统计定时器, PDP上下文中IPV6为已激活状态
修改历史   :
1.日   期  : 2012-12-11
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_001)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV6_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
    pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
	    .with(eq(stAtRnicIpv6PdpActInd.ucRabId), any());

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));


    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv6PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);


     /* 获取流量统计定时器的状态 */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv6PdpActInd_002
测试用例标题      : modem1,当前为手动拨号模式，RNIC收到AT消息ID_AT_RNIC_IPV6_PDP_ACT_IND的处理
预期结果          : 启动流量统计定时器, PDP上下文中IPV6为已激活状态
修改历史   :
1.日   期  : 2012-12-11
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_002)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
	VOS_UINT8                           ucNewBabId;

	ucNewBabId = 76;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV6_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_1;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
		.with(eq(ucNewBabId), any());

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv6PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);

     /* 获取流量统计定时器的状态 */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv6PdpActInd_003
测试用例标题      : 当前为按需拨号模式,RNIC收到AT消息ID_AT_RNIC_IPV6_PDP_ACT_IND的处理
预期结果          : 启动流量统计定时器, PDP上下文中IPV6为已激活状态
修改历史   :
1.日   期  : 2012-12-12
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_003)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
	AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV6_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv6PdpActInd.ucRabId), any());
	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv6PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);

     /* 获取流量统计定时器的状态 */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv6PdpActInd_004
测试用例标题      : 当前为按需拨号模式,且IPV4 PDP激活成功。RNIC收到AT消息ID_AT_RNIC_IPV6_PDP_ACT_IND的处理
预期结果          : 启动流量统计定时器, PDP上下文中IPV6为已激活状态
修改历史   :
1.日   期  : 2012-12-12
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_004)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
	AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV6_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* IPV4 已激活 */
	VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv6PdpActInd.ucRabId), any());
	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv6PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);

     /* 获取流量统计定时器的状态 */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv6PdpActInd_005
测试用例标题      : 填充RabID失败
预期结果          : 返回错误
修改历史   :
1.日   期  : 2012-12-11
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_005)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
	AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV6_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_BUTT;

    /* IPV4 已激活 */
	VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
	MOCKER(ADS_DL_RegDlDataCallback).expects(never());
    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv6PdpActInd_006
测试用例标题      : 存储rabid对应网卡失败
预期结果          : 返回错误
修改历史   :
1.日   期  : 2012-12-11
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_006)
{
   RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
	AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV6_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 4;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

	MOCKER(ADS_DL_RegDlDataCallback).expects(never());
    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_RcvAtIpv4v6PdpActInd
功能描述   : RNIC_RcvAtIpv4v6PdpActInd UT工程类
修改历史   :
1.日   期  : 2012-12-12
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtIpv4v6PdpActInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4v6PdpActInd_001
测试用例标题      : modem0,当前为手动拨号模式，RNIC收到AT消息ID_AT_RNIC_IPV6_PDP_ACT_IND的处理
预期结果          : 启动流量统计定时器, PDP上下文中IPV4V6为已激活状态
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4v6PdpActInd, Test_RNIC_RcvAtIpv4v6PdpActInd_001)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU     stAtRnicIpv4v6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4v6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv4v6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4v6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4v6PdpActInd.enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;
    stAtRnicIpv4v6PdpActInd.ucRabId         = 10;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv4v6PdpActInd.ucRabId), any());
	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4v6PdpActInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);

     /* 获取流量统计定时器的状态 */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4v6PdpActInd_002
测试用例标题      : modem1,当前为手动拨号模式，RNIC收到AT消息ID_AT_RNIC_IPV6_PDP_ACT_IND的处理
预期结果          : 启动流量统计定时器, PDP上下文中IPV4V6为已激活状态
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4v6PdpActInd, Test_RNIC_RcvAtIpv4v6PdpActInd_002)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU     stAtRnicIpv4v6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
	VOS_UINT8                           ucNewBabId;

	ucNewBabId = 74;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4v6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv4v6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4v6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4v6PdpActInd.enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;
    stAtRnicIpv4v6PdpActInd.ucRabId         = 10;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_1;

    /* 停止流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(ucNewBabId), any());
	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4v6PdpActInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);

     /* 获取流量统计定时器的状态 */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4v6PdpActInd_003
测试用例标题      : modem错误
预期结果          : 失败
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4v6PdpActInd, Test_RNIC_RcvAtIpv4v6PdpActInd_003)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU     stAtRnicIpv4v6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4v6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv4v6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4v6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4v6PdpActInd.enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;
    stAtRnicIpv4v6PdpActInd.ucRabId         = 10;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_BUTT;

    MOCKER(ADS_DL_RegDlDataCallback).expects(never());

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4v6PdpActInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtIpv4v6PdpActInd_004
测试用例标题      : rabid不在范围内
预期结果          : 失败
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4v6PdpActInd, Test_RNIC_RcvAtIpv4v6PdpActInd_004)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU     stAtRnicIpv4v6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 设置当前拨号模式为手动模式 */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicIpv4v6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv4v6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4v6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4v6PdpActInd.enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;
    stAtRnicIpv4v6PdpActInd.ucRabId         = 17;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    MOCKER(ADS_DL_RegDlDataCallback).expects(never());

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4v6PdpActInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
/*****************************************************************************
类名       : Test_RNIC_RcvAtPdpDeactInd
功能描述   : RNIC_RcvAtPdpDeactInd UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtPdpDeactInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};


/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdpDeactInd_001
测试用例标题      : IPV4激活状态, IPV6激活状态，收到AT下发的IPV4去激活消息
预期结果          : 拨号断开定时器停止， 流量统计定时器未停止,PDP上下文中IPV4为去激活状态
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_001)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 11;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv4PdpInfo.ucRabId    = 11;
     /* IPV4已激活 */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6已激活 */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* 启动流量统计定时器 */
    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
    /* 启动拨号断开定时器 */
    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* 获取流量统计定时器的状态 */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* 获取拨号断开定时器的状态 */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdpDeactInd_002
测试用例标题      : IPV4激活状态，IPV6激活状态，收到AT下发的IPV6去激活消息
预期结果          : 断开拨号定时器未停止，流量统计定时器未停止, PDP上下文中IPV6为去激活状态
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_002)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 11;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv6PdpInfo.ucRabId    = 11;
     /* IPV4已激活 */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6已激活 */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* 启动流量统计定时器 */
    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
    /* 启动拨号断开定时器 */
    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(2))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* 获取流量统计定时器的状态 */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* 获取拨号断开定时器的状态 */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdpDeactInd_003
测试用例标题      : IPV4未激活状态，IPV6未激活状态，IPV4V6激活状态，收到AT下发的IPV4V6去激活消息
预期结果          : 流量统计定时器停止, PDP上下文中IPV4V6为去激活状态
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_003)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 11;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv4v6PdpInfo.ucRabId    = 11;
     /* IPV4未激活 */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV6未激活 */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6已激活 */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* 启动流量统计定时器 */
    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
    /* 停止拨号断开定时器 */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* 获取流量统计定时器的状态 */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* 获取拨号断开定时器的状态 */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdpDeactInd_004
测试用例标题      : IPV4未激活状态，IPV6未激活状态，IPV4V6未激活状态，收到AT下发的去激活消息
预期结果          : 拨号断开定时器停止, 流量统计定时器停止，都为去激活状态
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_004)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 11;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv4v6PdpInfo.ucRabId    = 11;
     /* IPV4未激活 */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV6未激活 */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6已激活 */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* 启动流量统计定时器 */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);
    /* 停止拨号断开定时器 */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* 获取流量统计定时器的状态 */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* 获取拨号断开定时器的状态 */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdpDeactInd_005
测试用例标题      : IPV4激活状态, IPV6激活状态，收到AT下发的IPV4去激活消息,清除rabid对应网卡失败
预期结果          : 返回VOS_ERR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_005)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 4;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv4PdpInfo.ucRabId    = 4;
     /* IPV4已激活 */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6已激活 */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* 启动流量统计定时器 */
    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
    /* 启动拨号断开定时器 */
    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* 获取流量统计定时器的状态 */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* 获取拨号断开定时器的状态 */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_RcvAtMtuChangeInd
功能描述   : RNIC_RcvAtMtuChangeInd UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtMtuChangeInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};


/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtMtuChangeInd_001
测试用例标题      : MTU值发生改变后，AT发来的指示消息
预期结果          : 改变对应网卡信息的MTU值
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtMtuChangeInd, Test_RNIC_RcvAtMtuChangeInd_001)
{
	AT_RNIC_MTU_CHANGE_IND_STRU         stAtRnicMtuChangeInd;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
	RNIC_NETCARD_DEV_INFO_STRU         *pstNetDevInfo;
	RNIC_NETCARD_DEV_INFO_STRU          stPrv;
	struct net_device                   stNetDev;

	/* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
	VOS_MemSet(&stAtRnicMtuChangeInd, 0, sizeof(AT_RNIC_MTU_CHANGE_IND_STRU));
	stAtRnicMtuChangeInd.ulSenderPid     = WUEPS_PID_AT;
	stAtRnicMtuChangeInd.ulReceiverPid   = ACPU_PID_RNIC;
	stAtRnicMtuChangeInd.enMsgId         = ID_AT_RNIC_MTU_CHANGE_IND;
	stAtRnicMtuChangeInd.ulMtuValue		 = 100;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicMtuChangeInd.ucRmNetId);

	pstSpecNetCardCtx->pstNetDevInfo = &stPrv;

    pstNetDevInfo = pstSpecNetCardCtx->pstNetDevInfo;
	pstNetDevInfo->pstNetDev = &stNetDev;

	RNIC_ProcMsg((MsgBlock *)&stAtRnicMtuChangeInd);

    EXPECT_EQ(100, pstSpecNetCardCtx->pstNetDevInfo->pstNetDev->mtu);
}


/*****************************************************************************
类名       : Test_RNIC_RcvAtDsflowInd
功能描述   : RNIC_RcvAtDsflowInd UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtDsflowInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtDsflowInd_001
测试用例标题      : 内存分配失败
预期结果          : 返回VOS_ERR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDsflowInd, Test_RNIC_RcvAtDsflowInd_001)
{
    AT_RNIC_DSFLOW_IND_STRU             stAtRnicDsflowInd;

    /* 构造ID_AT_RNIC_DIAL_MODE_IND消息 */
    stAtRnicDsflowInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicDsflowInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicDsflowInd.enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    stAtRnicDsflowInd.enRnicRmNetId   = RNIC_RM_NET_ID_0;
    stAtRnicDsflowInd.clientId        = 1;
    stAtRnicDsflowInd.aucRsv[0]       = 0;

    /* 消息内存分配失败 */
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicDsflowInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtDsflowInd_002
测试用例标题      : PDP未激活的情况下，消息发送成功
预期结果          : 上报的速率为0
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDsflowInd, Test_RNIC_RcvAtDsflowInd_002)
{
    AT_RNIC_DSFLOW_IND_STRU             stAtRnicDsflowInd;
    RNIC_AT_DSFLOW_RSP_STRU             stSndMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造ID_AT_RNIC_DSFLOW_IND消息 */
    stAtRnicDsflowInd.ulSenderPid        = WUEPS_PID_AT;
    stAtRnicDsflowInd.ulReceiverPid      = ACPU_PID_RNIC;
    stAtRnicDsflowInd.enMsgId            = ID_AT_RNIC_DSFLOW_IND;
    stAtRnicDsflowInd.enRnicRmNetId      = RNIC_RM_NET_ID_0;
    stAtRnicDsflowInd.clientId           = 1;
    stAtRnicDsflowInd.aucRsv[0]          = 0;

    /* 需要匹配的ID_RNIC_AT_DSFLOW_RSP */
    stSndMsg.ulSenderPid                 = ACPU_PID_RNIC;
    stSndMsg.ulReceiverPid               = WUEPS_PID_AT;
    stSndMsg.enMsgId                     = ID_RNIC_AT_DSFLOW_RSP;
    stSndMsg.clientId                    = 1;
    stSndMsg.stRnicDataRate.ulDLDataRate = 0;
    stSndMsg.stRnicDataRate.ulDLDataRate = 0;

    RNIC_SetCurrentDlRate(100, ucIndex);
    RNIC_SetCurrentUlRate(50, ucIndex);

     pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
     /* IPV4未激活 */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV6未激活 */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6已激活 */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* VOS_SendMsg 发送ID_RNIC_AT_DSFLOW_RSP消息*/
     MOCKER(Ps_SendMsg)
         .expects(exactly(1))
         .with(any(), any(), eq(ACPU_PID_RNIC), any());

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicDsflowInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtDsflowInd_003
测试用例标题      : PDP激活的情况下，消息发送成功
预期结果          : 上报的速率为当前的速率
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDsflowInd, Test_RNIC_RcvAtDsflowInd_003)
{
    AT_RNIC_DSFLOW_IND_STRU             stAtRnicDsflowInd;
    RNIC_AT_DSFLOW_RSP_STRU             stSndMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    stAtRnicDsflowInd.aucRsv[0]       = 0;

    /* 构造ID_AT_RNIC_DSFLOW_IND消息 */
    stAtRnicDsflowInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicDsflowInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicDsflowInd.enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    stAtRnicDsflowInd.clientId        = 1;
    stAtRnicDsflowInd.enRnicRmNetId   = RNIC_RM_NET_ID_0;

    /* 需要匹配的ID_RNIC_AT_DSFLOW_RSP */
    stSndMsg.ulSenderPid                = ACPU_PID_RNIC;
    stSndMsg.ulReceiverPid              = WUEPS_PID_AT;
    stSndMsg.enMsgId                    = ID_RNIC_AT_DSFLOW_RSP;
    stSndMsg.clientId                   = 1;
    stSndMsg.stRnicDataRate.ulDLDataRate = 100;
    stSndMsg.stRnicDataRate.ulDLDataRate = 50;

    RNIC_SetCurrentDlRate(100, ucIndex);
    RNIC_SetCurrentUlRate(50, ucIndex);

     pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
     /* IPV4激活 */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6未激活 */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6已激活 */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* VOS_SendMsg 发送ID_RNIC_AT_DSFLOW_RSP消息*/
     MOCKER(Ps_SendMsg)
         .expects(exactly(1))
         .with(any(), any(), eq(ACPU_PID_RNIC), any());

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicDsflowInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtDsflowInd_004
测试用例标题      : PDP激活的情况下，消息发送失败
预期结果          : 返回VOS_ERR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDsflowInd, Test_RNIC_RcvAtDsflowInd_004)
{
    AT_RNIC_DSFLOW_IND_STRU             stAtRnicDsflowInd;
    RNIC_AT_DSFLOW_RSP_STRU             stSndMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造ID_AT_RNIC_DSFLOW_IND消息 */
    stAtRnicDsflowInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicDsflowInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicDsflowInd.enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    stAtRnicDsflowInd.clientId        = 1;
    stAtRnicDsflowInd.aucRsv[0]       = 0;
    stAtRnicDsflowInd.enRnicRmNetId   = RNIC_RM_NET_ID_0;

    /* 需要匹配的ID_RNIC_AT_DSFLOW_RSP */
    stSndMsg.ulSenderPid                = ACPU_PID_RNIC;
    stSndMsg.ulReceiverPid              = WUEPS_PID_AT;
    stSndMsg.enMsgId                    = ID_RNIC_AT_DSFLOW_RSP;
    stSndMsg.clientId                   = 1;
    stSndMsg.stRnicDataRate.ulDLDataRate = 100;
    stSndMsg.stRnicDataRate.ulDLDataRate = 50;

    RNIC_SetCurrentDlRate(100, ucIndex);
    RNIC_SetCurrentUlRate(50, ucIndex);

     pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
     /* IPV4激活 */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6未激活 */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6已激活 */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* VOS_SendMsg 发送ID_RNIC_AT_DSFLOW_RSP消息*/
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue(VOS_ERR));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicDsflowInd);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_RcvAtDialModeReq
功能描述   : RNIC_RcvAtDialModeReq UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtDialModeReq: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtDialModeReq_001
测试用例标题      :
预期结果          :
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDialModeReq, Test_RNIC_RcvAtDialModeReq_001)
{
	AT_RNIC_DIAL_MODE_REQ_STRU          stAtRnicDialModeReq;
	RNIC_AT_DIAL_MODE_CNF_STRU          stSndMsg;
	RNIC_DIAL_MODE_STRU                *pstDialMode;

	/* 构造AT_RNIC_DIAL_MODE_REQ消息 */
	VOS_MemSet(&stAtRnicDialModeReq, 0, sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
	stAtRnicDialModeReq.ulSenderPid     = WUEPS_PID_AT;
	stAtRnicDialModeReq.ulReceiverPid   = ACPU_PID_RNIC;
	stAtRnicDialModeReq.enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
	stAtRnicDialModeReq.clientId        = 1;

	/* 消息内存分配失败 */
	MOCKER(V_AllocMsg)
        .stubs()
		.will(returnValue(VOS_NULL_PTR));

	MOCKER(Ps_SendMsg)
		.expects(never());

	/* 调用消息入口函数 */
	RNIC_ProcMsg((MsgBlock *)&stAtRnicDialModeReq);

	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtDialModeReq_002
测试用例标题      :
预期结果          :
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDialModeReq, Test_RNIC_RcvAtDialModeReq_002)
{
	AT_RNIC_DIAL_MODE_REQ_STRU          stAtRnicDialModeReq;
	RNIC_AT_DIAL_MODE_CNF_STRU          stSndMsg;
	RNIC_DIAL_MODE_STRU                *pstDialMode;

	/* 构造AT_RNIC_DIAL_MODE_REQ消息 */
	VOS_MemSet(&stAtRnicDialModeReq, 0, sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
	stAtRnicDialModeReq.ulSenderPid     = WUEPS_PID_AT;
	stAtRnicDialModeReq.ulReceiverPid   = ACPU_PID_RNIC;
	stAtRnicDialModeReq.enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
	stAtRnicDialModeReq.clientId        = 1;

	pstDialMode                         = RNIC_GetDialModeAddr();

	/* VOS_SendMsg 发送ID_RNIC_AT_DSFLOW_RSP消息*/
	MOCKER(Ps_SendMsg)
		.expects(exactly(1))
		.with(any(), any(), eq(ACPU_PID_RNIC), any());

	RNIC_ProcMsg((MsgBlock *)&stAtRnicDialModeReq);

	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtDialModeReq_003
测试用例标题      :
预期结果          :
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDialModeReq, Test_RNIC_RcvAtDialModeReq_003)
{
	AT_RNIC_DIAL_MODE_REQ_STRU          stAtRnicDialModeReq;
	RNIC_AT_DIAL_MODE_CNF_STRU          stSndMsg;
	RNIC_DIAL_MODE_STRU                *pstDialMode;

	/* 构造AT_RNIC_DIAL_MODE_REQ消息 */
	VOS_MemSet(&stAtRnicDialModeReq, 0, sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
	stAtRnicDialModeReq.ulSenderPid     = WUEPS_PID_AT;
	stAtRnicDialModeReq.ulReceiverPid   = ACPU_PID_RNIC;
	stAtRnicDialModeReq.enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
	stAtRnicDialModeReq.clientId        = 1;

	pstDialMode                         = RNIC_GetDialModeAddr();

	/* VOS_SendMsg 发送ID_AT_RNIC_DIAL_MODE_REQ消息*/
	MOCKER(Ps_SendMsg)
        .stubs()
		.will(returnValue(VOS_ERR));

	/* 调用消息入口函数 */
	RNIC_ProcMsg((MsgBlock *)&stAtRnicDialModeReq);

	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_RcvTiDsflowStatsExpired
功能描述   : RNIC_RcvTiDsflowStatsExpired UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvTiDsflowStatsExpired: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTiDsflowStatsExpired_001
测试用例标题      : PDP未激活。RNIC收到定时器超时消息消息TI_RNIC_APP_DSFLOW的处理
预期结果          : 保存速率的全局变量中没有值，周期统计Byte数清除
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDsflowStatsExpired, Test_RNIC_RcvTiDsflowStatsExpired_001)
{
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DSFLOW_STATS_0;

    /* 获取上下行上下文地址 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndBytes = 0;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes = 0;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4激活 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6未激活 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6已激活 */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULCurDataRate);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLCurDataRate);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalSndBytes);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLTotalRcvBytes);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalSndBytes);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLTotalRcvBytes);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTiDsflowStatsExpired_002
测试用例标题      : PDP激活时。RNIC收到定时器超时消息消息TI_RNIC_APP_DSFLOW的处理
预期结果          : 保存速率的全局变量中有值,周期统计Byte数清除
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDsflowStatsExpired, Test_RNIC_RcvTiDsflowStatsExpired_002)
{
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName    = TI_RNIC_DSFLOW_STATS_0;

    /* 获取上下行上下文地址 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndBytes = 50;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes = 200;
    pstUlCtx->stULDataStats.ulULTotalSndBytes  = 12345;
    pstDlCtx->stDLDataStats.ulDLTotalRcvBytes  = 54321;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4激活 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    /* IPV6未激活 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6已激活 */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(25, pstUlCtx->stULDataStats.ulULCurDataRate);
    EXPECT_EQ(100, pstDlCtx->stDLDataStats.ulDLCurDataRate);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes);
    EXPECT_EQ(12345, pstUlCtx->stULDataStats.ulULTotalSndBytes);
    EXPECT_EQ(54321, pstDlCtx->stDLDataStats.ulDLTotalRcvBytes);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_RcvTiDemandDialDisconnectExpired
功能描述   : RNIC_RcvTiDemandDialDisconnectExpired UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvTiDemandDialDisconnectExpired: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTiDemandDialDisconnectExpired_001
测试用例标题      : 手动拨号模式下。RNIC收到定时器超时消息消息TI_RNIC_APP_DEMAND_DIAL_DOWN的处理
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_001)
{
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_MANUAL;

    /* 获取上下行上下文地址 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4激活 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6未激活 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6未激活 */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(1, pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTiDemandDialDisconnectExpired_002
测试用例标题      : 按需拨号模式下，当前有用户数据且有用户连接。
预期结果          : 断开拨号定时器计数器清零
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_002)
{
    VOS_UINT32                          ulCount;
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialMode->ulIdleTime             = AT_APP_IDLE_TIME;

    /* 获取上下行上下文地址 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4激活 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6未激活 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6未激活 */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;


    RNIC_IncTiDialDownExpCount();

    MOCKER(drv_get_local_usr_connect_status)
        .expects(exactly(1))
        .will(returnValue(VOS_TRUE));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    ulCount = RNIC_GetTiDialDownExpCount();
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(0, ulCount);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTiDemandDialDisconnectExpired_003
测试用例标题      : 按需拨号模式下，当前有用户数据且无用户连接。
预期结果          : 断开拨号定时器计数器增加
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_003)
{
    VOS_UINT32                          ulCount;
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialMode->ulIdleTime             = AT_APP_IDLE_TIME;

    /* 获取上下行上下文地址 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4激活 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6未激活 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6未激活 */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    RNIC_ClearTiDialDownExpCount();

    MOCKER(drv_get_local_usr_connect_status)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    ulCount = RNIC_GetTiDialDownExpCount();
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(1, ulCount);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTiDemandDialDisconnectExpired_004
测试用例标题      : 按需拨号模式下，当前有用户数据且无用户连接，定时器超时已达到了统计的次数
预期结果          : 断开拨号定时器计数器增加， 通知应用拨号
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_004)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCount;
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialMode->ulIdleTime             = AT_APP_IDLE_TIME;
	pstDialMode->enEventReportFlag      = RNIC_ALLOW_EVENT_REPORT;

    /* 获取上下行上下文地址 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4激活 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6未激活 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6已激活 */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    RNIC_ClearTiDialDownExpCount();
    for (i = 1; i < (AT_APP_IDLE_TIME * TI_RNIC_UNIT / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN); i++)
    {
        RNIC_IncTiDialDownExpCount();
    }

    MOCKER(drv_get_local_usr_connect_status)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    ulCount = RNIC_GetTiDialDownExpCount();
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ((AT_APP_IDLE_TIME * TI_RNIC_UNIT / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN), ulCount);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTiDemandDialDisconnectExpired_005
测试用例标题      : 通知应用断开拨号失败
预期结果          : 断开拨号失败计数器增加
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_005)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCount;
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialMode->ulIdleTime             = AT_APP_IDLE_TIME;
	pstDialMode->enEventReportFlag      = RNIC_ALLOW_EVENT_REPORT;

    /* 获取上下行上下文地址 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4激活 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6未激活 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6已激活 */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    RNIC_ClearTiDialDownExpCount();
    for (i = 1; i < (AT_APP_IDLE_TIME * TI_RNIC_UNIT / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN); i++)
    {
        RNIC_IncTiDialDownExpCount();
    }

    MOCKER(drv_get_local_usr_connect_status)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));
	MOCKER(RNIC_SendDialEvent)
        .stubs()
        .will(returnValue(VOS_ERR));

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    ulCount = RNIC_GetTiDialDownExpCount();
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ((AT_APP_IDLE_TIME * TI_RNIC_UNIT / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN), ulCount);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_RNIC_RcvTiDemandDialProtectExpired
功能描述 : Test_RNIC_RcvTiDemandDialProtectExpired UT工程类
修改历史     :
1.日   期  : 2012-06-06
  作   者  : A00165503
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvTiDemandDialProtectExpired: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTiDemandDialProtectExpired_001
测试用例标题      : 停止按需拨号保护定时器
预期结果          : 停止按需拨号保护定时器
修改历史     :
1.日   期  : 2012-06-06
  作   者  : A00165503
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialProtectExpired, Test_RNIC_RcvTiDemandDialProtectExpired_001)
{
    //参数定义
    REL_TIMER_MSG                       stTimeMsg;

    //参数初始化
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid   = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid = ACPU_PID_RNIC;
    stTimeMsg.ulName        = TI_RNIC_DEMAND_DIAL_PROTECT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    //执行检查
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_PROTECT));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_RcvAtMsg
功能描述   : RNIC_RcvAtMsg UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtMsg_001
测试用例标题      : 收到的消息没有需要处理的
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtMsg, Test_RNIC_ProcMsg_001)
{
    MSG_HEADER_STRU                     stMsgHeader;

    /* 构造ID_AT_RNIC_IPV4_PDP_ACT_IND消息 */
    VOS_MemSet(&stMsgHeader, 0, sizeof(MSG_HEADER_STRU));
    stMsgHeader.ulSenderPid     = WUEPS_PID_AT;
    stMsgHeader.ulReceiverPid   = ACPU_PID_RNIC;
    stMsgHeader.ulMsgName      = ID_RNIC_AT_MSG_ID_ENUM_BUTT;


    MOCKER(RNIC_RcvAtIpv4PdpActInd)
        .expects(never());

    MOCKER(RNIC_RcvAtIpv6PdpActInd)
        .expects(never());

    MOCKER(RNIC_RcvAtIpv4v6PdpActInd)
        .expects(never());

    MOCKER(RNIC_RcvAtPdpDeactInd)
        .expects(never());

    MOCKER(RNIC_RcvAtDsflowInd)
        .expects(never());

    MOCKER(RNIC_RcvAtMtuChangeInd)
        .expects(never());

    /* 调用消息入口函数 */
    RNIC_ProcMsg((MsgBlock *)&stMsgHeader);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtMsg_002
测试用例标题      : 收到AT PDN配置消息
预期结果          : 进入PDN配置分发处理函数
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtMsg,Test_RNIC_RcvAtMsg_002)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;


    /*本地变量初始化*/
    PS_MEM_SET(&stRnicPdnCfgInd,0x00,sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId = ID_AT_RNIC_PDN_INFO_CFG_IND;

    /*函数打桩*/
    MOCKER(RNIC_RcvAtPdnInfoCfgInd)
        .expects(exactly(1));

    /*调用被测函数 */
    RNIC_RcvAtMsg((MsgBlock *)&stRnicPdnCfgInd);

    /* 结果验证*/

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtMsg_003
测试用例标题      : 收到AT PDN释放消息
预期结果          : 进入PDN配置释放分发处理函数
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtMsg,Test_RNIC_RcvAtMsg_003)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_REL_IND_STRU     	stRnicPdnCfgRel;


    /*本地变量初始化*/
    PS_MEM_SET(&stRnicPdnCfgRel,0x00,sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnCfgRel.enMsgId = ID_AT_RNIC_PDN_INFO_REL_IND;

    /*函数打桩*/
    MOCKER(RNIC_RcvAtPdnInfoRelInd)
        .expects(exactly(1));

    /*调用被测函数 */
    RNIC_RcvAtMsg((MsgBlock *)&stRnicPdnCfgRel);

    /* 结果验证*/

    GlobalMockObject::verify();
}


/*****************************************************************************
类名       : Test_RNIC_RcvTimerMsg
功能描述   : RNIC_RcvTimerMsg UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvTimerMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTimerMsg_001
测试用例标题      : 收到的定时器消息没有需要处理的
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTimerMsg, Test_RNIC_RcvTimerMsg_001)
{
    REL_TIMER_MSG                       stTimeMsg;
    VOS_UINT32                          ulRst;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_TIMER_BUTT;

    MOCKER(RNIC_RcvTiDsflowStatsExpired)
        .expects(never());

    MOCKER(RNIC_RcvTiDemandDialProtectExpired)
        .expects(never());

    MOCKER(RNIC_RcvTiDemandDialDisconnectExpired)
        .expects(never());


    /* 调用消息入口函数 */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    EXPECT_EQ(VOS_OK, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvTimerMsg_002
测试用例标题      : 收到的定时器消息，处理函数返回值为ERR
预期结果          : 返回VOS_ERR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTimerMsg, Test_RNIC_RcvTimerMsg_002)
{
	 REL_TIMER_MSG                       stTimeMsg;
     VOS_UINT32                          ulRst;

    /* 构造REL_TIMER_MSG消息 */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DSFLOW_STATS_0;

	MOCKER(RNIC_RcvTiDsflowStatsExpired)
        .stubs()
        .will(returnValue(VOS_ERR));
    /* 调用消息入口函数 */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*****************************************************************************
类名       : Test_RNIC_ProcMsg
功能描述   : RNIC_ProcMsg UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_ProcMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_ProcMsg_001
测试用例标题      : 收到的消息为空时
预期结果          : 返回VOS_ERR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_ProcMsg, Test_RNIC_ProcMsg_001)
{
    MsgBlock                     *pstMsgBlock = VOS_NULL_PTR;

    MOCKER(RNIC_RcvAtMsg)
        .expects(never());

    MOCKER(RNIC_RcvTimerMsg)
        .expects(never());

    /* 调用消息入口函数 */
    RNIC_ProcMsg(pstMsgBlock);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_ProcMsg_002
测试用例标题      : 收到的消息没有对应的PID时
预期结果          : 返回VOS_ERR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_ProcMsg, Test_RNIC_ProcMsg_002)
{
    MsgBlock                            stMsgBlock;

    VOS_MemSet(&stMsgBlock, 0, sizeof(MsgBlock));
    stMsgBlock.ulSenderPid                = ACPU_PID_ADS_UL;
    stMsgBlock.ulReceiverPid              = ACPU_PID_RNIC;

    MOCKER(RNIC_RcvAtMsg)
        .expects(never());

    MOCKER(RNIC_RcvTimerMsg)
        .expects(never());

    /* 调用消息入口函数 */
    RNIC_ProcMsg(&stMsgBlock);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_GetDsflowTimerIdByNetId
功能描述   : RNIC_GetDsflowTimerIdByNetId UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_GetDsflowTimerIdByNetId: public ::testing::Test
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
测试用例编号      : Test_RNIC_GetDsflowTimerIdByNetId_001
测试用例标题      : 网卡ID分别为1,2,3,4
预期结果          : 流量统计定时器为1,2,3,4
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_GetDsflowTimerIdByNetId, Test_RNIC_GetDsflowTimerIdByNetId_001)
{
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID1;
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID2;
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID3;
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID4;
#endif
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID5;

    enTimerID1 = RNIC_GetDsflowTimerIdByNetId(RNIC_RM_NET_ID_1);
	enTimerID2 = RNIC_GetDsflowTimerIdByNetId(RNIC_RM_NET_ID_2);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	enTimerID3 = RNIC_GetDsflowTimerIdByNetId(RNIC_RM_NET_ID_3);
	enTimerID4 = RNIC_GetDsflowTimerIdByNetId(RNIC_RM_NET_ID_4);
#endif
	enTimerID5 = RNIC_GetDsflowTimerIdByNetId(RNIC_RMNET_ID_BUTT);

	EXPECT_EQ(TI_RNIC_DSFLOW_STATS_1,enTimerID1);
	EXPECT_EQ(TI_RNIC_DSFLOW_STATS_2,enTimerID2);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	EXPECT_EQ(TI_RNIC_DSFLOW_STATS_3,enTimerID3);
	EXPECT_EQ(TI_RNIC_DSFLOW_STATS_4,enTimerID4);
#endif
	EXPECT_EQ(TI_RNIC_TIMER_BUTT,enTimerID5);
    /* 检查调用时, 需要在用例结束位加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_GetNetIdByTimerId
功能描述   : RNIC_GetNetIdByTimerId UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_GetNetIdByTimerId: public ::testing::Test
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
测试用例编号      : Test_RNIC_GetNetIdByTimerId_001
测试用例标题      : 流量统计定时器为1,2,3,4
预期结果          : 网卡分别为1,2,3,4
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_GetNetIdByTimerId, Test_RNIC_GetNetIdByTimerId_001)
{
	VOS_UINT8 ucRmNedId1;
	VOS_UINT8 ucRmNedId2;
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	VOS_UINT8 ucRmNedId3;
	VOS_UINT8 ucRmNedId4;
#endif

    ucRmNedId1 = RNIC_GetNetIdByTimerId(TI_RNIC_DSFLOW_STATS_1);
	ucRmNedId2 = RNIC_GetNetIdByTimerId(TI_RNIC_DSFLOW_STATS_2);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	ucRmNedId3 = RNIC_GetNetIdByTimerId(TI_RNIC_DSFLOW_STATS_3);
	ucRmNedId4 = RNIC_GetNetIdByTimerId(TI_RNIC_DSFLOW_STATS_4);
#endif

	EXPECT_EQ(RNIC_RM_NET_ID_1,ucRmNedId1);
	EXPECT_EQ(RNIC_RM_NET_ID_2,ucRmNedId2);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	EXPECT_EQ(RNIC_RM_NET_ID_3,ucRmNedId3);
	EXPECT_EQ(RNIC_RM_NET_ID_4,ucRmNedId4);
#endif
    /* 检查调用时, 需要在用例结束位加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_BuildRabIdByModemId
功能描述   : RNIC_BuildRabIdByModemId UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_BuildRabIdByModemId: public ::testing::Test
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
测试用例编号      : Test_RNIC_BuildRabIdByModemId_001
测试用例标题      : modemID既不为0也不为1
预期结果          : 返回VOS_ERR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_BuildRabIdByModemId, Test_RNIC_BuildRabIdByModemId_001)
{
	VOS_UINT8 ucRabId = 6;
	VOS_UINT32 ulRst;

	ulRst = RNIC_BuildRabIdByModemId(MODEM_ID_BUTT,ucRabId,&ucRabId);

	EXPECT_EQ(VOS_ERR,ulRst);
    /* 检查调用时, 需要在用例结束位加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_SaveNetIdByRabId
功能描述   : RNIC_SaveNetIdByRabId UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_SaveNetIdByRabId: public ::testing::Test
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
测试用例编号      : Test_RNIC_SaveNetIdByRabId_001
测试用例标题      : RABID不符合5-15
预期结果          : 返回VOS_ERR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : z00220246
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SaveNetIdByRabId, Test_RNIC_SaveNetIdByRabId_001)
{
	VOS_UINT8  ucRabId = 4;
    VOS_UINT32 ulRst;
	ulRst = RNIC_SaveNetIdByRabId(MODEM_ID_0,ucRabId,RNIC_RM_NET_ID_1);

  //　EXPECT_EQ(VOS_ERR,ulRst);
    /* 检查调用时, 需要在用例结束位加上这句 */
    GlobalMockObject::verify();
}


/*****************************************************************************
类名       : Test_RNIC_RcvCcpuResetStartInd
功能描述   : RNIC_RcvCcpuResetStartInd UT工程类
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvCcpuResetStartInd: public ::testing::Test
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
测试用例编号      : Test_RNIC_RcvCcpuResetStartInd_001
测试用例标题      : 收到ID_CCPU_RNIC_RESET_START_IND
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvCcpuResetStartInd, Test_RNIC_RcvCcpuResetStartInd_001)
{
    VOS_UINT32                          ulRst;
    RNIC_CCPU_RESET_IND_STRU            stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(RNIC_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_RNIC;
    stResetInd.ulReceiverPid   = ACPU_PID_RNIC;
    stResetInd.enMsgId         = ID_RNIC_CCPU_RESET_START_IND;

    /* 桩函数 */
    MOCKER(RNIC_StopAllTimer)
        .expects(exactly(1));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*****************************************************************************
类名       : Test_RNIC_RcvRnicMsg
功能描述   : RNIC_RcvRnicMsg UT工程类
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvRnicMsg: public ::testing::Test
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
测试用例编号      : Test_RNIC_RcvRnicMsg_001
测试用例标题      : 收到ID_CCPU_RNIC_RESET_END_IND
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicMsg, Test_RNIC_RcvRnicMsg_001)
{
    VOS_UINT32                          ulRst;
    RNIC_CCPU_RESET_IND_STRU            stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(RNIC_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_RNIC;
    stResetInd.ulReceiverPid   = ACPU_PID_RNIC;
    stResetInd.enMsgId         = ID_RNIC_CCPU_RESET_END_IND;

    /* 桩函数 */
    MOCKER(RNIC_StopAllTimer)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicMsg_002
测试用例标题      : 收到ID_RNIC_RESET_MSG_ID_ENUM_BUTT
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicMsg, Test_RNIC_RcvRnicMsg_002)
{
    VOS_UINT32                          ulRst;
    RNIC_CCPU_RESET_IND_STRU            stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(RNIC_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_RNIC;
    stResetInd.ulReceiverPid   = ACPU_PID_RNIC;
    stResetInd.enMsgId         = ID_RNIC_RNIC_MSG_ID_BUTT;

    /* 桩函数 */
    MOCKER(RNIC_StopAllTimer)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_RNIC_RcvAtPdnInfoCfgInd
功能描述 : RNIC_RcvAtPdnInfoCfgInd UT工程类
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtPdnInfoCfgInd: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdnInfoCfgInd_001
测试用例标题      : 根据ModemId生成RABID失败
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoCfgInd,Test_RNIC_RcvAtPdnInfoCfgInd_001)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU      	stRnicPdnCfgInd;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    PS_MEM_SET(&stRnicPdnCfgInd, 0x00, sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId = ID_AT_RNIC_PDN_INFO_CFG_IND;

    /*函数打桩*/
    MOCKER(RNIC_BuildRabIdByModemId)
        .stubs()
        .will(returnValue(VOS_ERR));

    /*调用被测函数 */
    ulRslt = RNIC_RcvAtPdnInfoCfgInd((MsgBlock *)&stRnicPdnCfgInd);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdnInfoCfgInd_002
测试用例标题      : 存储RABID对应的网卡ID
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoCfgInd,Test_RNIC_RcvAtPdnInfoCfgInd_002)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU      	stRnicPdnCfgInd;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    PS_MEM_SET(&stRnicPdnCfgInd, 0x00, sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId = 16;

    /*函数打桩*/

    /*调用被测函数 */
    ulRslt = RNIC_RcvAtPdnInfoCfgInd((MsgBlock *)&stRnicPdnCfgInd);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdnInfoCfgInd_003
测试用例标题      : 收到IPV4类型的PDN配置消息
预期结果          : 更新IPV4 PDN信息，返回VOS_OK
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoCfgInd,Test_RNIC_RcvAtPdnInfoCfgInd_003)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    PS_MEM_SET(&stFilterIpAddr, 0x00, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));
    stFilterIpAddr.bitOpIpv4Addr        = VOS_TRUE;

    PS_MEM_SET(&stRnicPdnCfgInd, 0x00, sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId             = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId             = 5;
    stRnicPdnCfgInd.bitOpIpv4PdnInfo    = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnCfgInd.ucRmNetId);

    /*函数打桩*/
    MOCKER(ADS_DL_RegFilterDataCallback)
        .stubs()
        .with(any(),mirror(&stFilterIpAddr, sizeof(stFilterIpAddr)),any());

    /*调用被测函数 */
    ulRslt = RNIC_RcvAtPdnInfoCfgInd((MsgBlock *)&stRnicPdnCfgInd);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdnInfoCfgInd_004
测试用例标题      : 收到IPV6类型的PDN配置消息
预期结果          : 更新IPV6 PDN信息，返回VOS_OK
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoCfgInd,Test_RNIC_RcvAtPdnInfoCfgInd_004)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    PS_MEM_SET(&stFilterIpAddr, 0x00, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));
    stFilterIpAddr.bitOpIpv6Addr        = VOS_TRUE;

    PS_MEM_SET(&stRnicPdnCfgInd, 0x00, sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId             = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId             = 5;
    stRnicPdnCfgInd.bitOpIpv6PdnInfo    = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnCfgInd.ucRmNetId);

    /*函数打桩*/
    MOCKER(ADS_DL_RegFilterDataCallback)
        .stubs()
        .with(any(),mirror(&stFilterIpAddr, sizeof(stFilterIpAddr)),any());

    /*调用被测函数 */
    ulRslt = RNIC_RcvAtPdnInfoCfgInd((MsgBlock *)&stRnicPdnCfgInd);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(5, pstPdpAddr->stIpv6PdpInfo.ucRabId);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_RNIC_RcvAtPdnInfoRelInd
功能描述 : RNIC_RcvAtPdnInfoRelInd UT工程类
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAtPdnInfoRelInd: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdnInfoRelInd_001
测试用例标题      : 一个承载时，收到IPV4\IPV6类型的PDN重置消息
预期结果          : 更新注册状态，清除IPV4\IPv6 PDN信息
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoRelInd,Test_RNIC_RcvAtPdnInfoRelInd_001)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /*本地变量初始化*/
    PS_MEM_SET(&stRnicPdnRelInd, 0x00, sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = 5;

    /*全局变量初始化*/
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;

    /*函数打桩*/
    MOCKER(RNIC_StopTimer)
        .expects(exactly(1));

    MOCKER(ADS_DL_DeregFilterDataCallback)
        .expects(exactly(1));

    /*调用被测函数 */
    RNIC_RcvAtPdnInfoRelInd((MsgBlock *)&stRnicPdnRelInd);

    /* 结果验证*/
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdnInfoRelInd_002
测试用例标题      : 一个承载时，收到IPV4V6类型的PDN重置消息
预期结果          : 更新注册状态，清除IPV4V6 PDN信息
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoRelInd,Test_RNIC_RcvAtPdnInfoRelInd_002)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /*本地变量初始化*/
    PS_MEM_SET(&stRnicPdnRelInd, 0x00, sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = 5;

    /*全局变量初始化*/
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;

    /*函数打桩*/
    MOCKER(RNIC_StopTimer)
        .expects(exactly(1));

    MOCKER(ADS_DL_DeregFilterDataCallback)
        .expects(exactly(1));

    /*调用被测函数 */
    RNIC_RcvAtPdnInfoRelInd((MsgBlock *)&stRnicPdnRelInd);

    /* 结果验证*/
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdnInfoRelInd_003
测试用例标题      : 多个承载时，收到IPV4类型的PDN重置消息
预期结果          : 更新注册状态，清除IPV4 PDN信息
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoRelInd,Test_RNIC_RcvAtPdnInfoRelInd_003)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /*本地变量初始化*/
    PS_MEM_SET(&stRnicPdnRelInd, 0x00, sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = 5;

    /*全局变量初始化*/
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 6;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;

    /*函数打桩*/
    MOCKER(RNIC_StopTimer)
        .expects(never());

    MOCKER(ADS_DL_DeregFilterDataCallback)
        .expects(exactly(1));

    /*调用被测函数 */
    RNIC_RcvAtPdnInfoRelInd((MsgBlock *)&stRnicPdnRelInd);

    /* 结果验证*/
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAtPdnInfoRelInd_004
测试用例标题      : 收到PDN重置消息，清除RABID对应的网卡ID失败
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2013-06-19
  作   者  : z00214637
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoRelInd,Test_RNIC_RcvAtPdnInfoRelInd_004)
{
    /*变量定义*/
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT32                          ulRslt;

    /*本地变量初始化*/
    PS_MEM_SET(&stRnicPdnRelInd, 0x00, sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = 5;

    /*全局变量初始化*/
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;

    /*函数打桩*/
    MOCKER(RNIC_StopTimer)
        .expects(exactly(1));

    MOCKER(RNIC_SaveNetIdByRabId)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(ADS_DL_DeregFilterDataCallback)
        .expects(never());

    /*调用被测函数 */
    ulRslt = RNIC_RcvAtPdnInfoRelInd((MsgBlock *)&stRnicPdnRelInd);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}

/* Added by m00217266 for L-C互操作项目, 2014-2-7, begin */
/*****************************************************************************
类名       : Test_RNIC_RcvRnicRmnetConfigReq
功能描述   : RNIC_RcvRnicRmnetConfigReq UT工程类
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvRnicRmnetConfigReq: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_001
测试用例标题      : 配置内部modem，ipv4类型网卡up
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_001)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    for (i = 0; i < 10; i++)
    {
        /* ipv4激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_0, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

        /* ipv6激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_0, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        /* ipv6去激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        /* ipv4去激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    }
    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_002
测试用例标题      : 配置内部modem，ipv6类型网卡up
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_002)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_0, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    /* ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_0, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    /* ipv4v6去激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4V6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_003
测试用例标题      : 配置外部modem，ipv4类型网卡up
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_003)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    for (i = 0; i < 10; i++)
    {
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ipv6激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 2;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(2, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(2));
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ipv4去激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(2, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(2));
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ipv6去激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 2;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(2));
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));
    }

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_004
测试用例标题      : 配置外部modem，ipv6类型网卡up
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_004)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#endif

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_005
测试用例标题      : 配置内部modem，ipv4类型网卡down
预期结果          : 清除ipv4网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_005)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ipv4去激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_006
测试用例标题      : 配置内部modem，ipv6类型网卡down
预期结果          : 清除ipv6网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_006)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ipv6激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 6;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    /* ipv6去激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 6;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_007
测试用例标题      : 配置外部modem，ipv4类型网卡down
预期结果          : 清除ipv4网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_007)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_008
测试用例标题      : 配置外部modem，ipv6类型网卡down
预期结果          : 清除ipv6网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_008)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_009
测试用例标题      : 配置内部modem切换到外modem，ipv4类型PDP激活(首次modem切换)
预期结果          : 网卡上下文只保存外modem的激活信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_009)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_PDP_CTX_STRU                  *pstRmnet2PdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstRmnet2SpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);
    pstRmnet2PdpAddr                    = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_2);
    pstRmnet2SpecNetCardCtx             = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_2);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    /* 网卡1ipv6激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 6;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    /* 网卡2ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 7;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_2;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstRmnet2SpecNetCardCtx->enModemType);
    EXPECT_EQ(7, pstRmnet2PdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstRmnet2PdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_2, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 7));

    /* handover */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* 网卡2的内容匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstRmnet2SpecNetCardCtx->enModemType);
    EXPECT_EQ(7, pstRmnet2PdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstRmnet2PdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_2, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 7));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_010
测试用例标题      : 配置内部modem切换到外modem，ipv6类型PDP激活(第二次modem切换)
预期结果          : 网卡上下文只保存外modem的激活信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_010)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_PDP_CTX_STRU                  *pstRmnet2PdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstRmnet2SpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);
    pstRmnet2PdpAddr                    = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_2);
    pstRmnet2SpecNetCardCtx             = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_2);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    for (i = 0; i < 10; i++)
    {
        /* 网卡1ipv4激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

        /* 网卡1ipv6激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        /* 第一次handover */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 第二次handover */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ipv4v6去激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4V6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(2));
    }

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_011
测试用例标题      : 配置外部modem切换到内modem，ipv4类型PDP激活(首次modem切换)
预期结果          : 网卡上下文只保存内modem的激活信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_011)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_PDP_CTX_STRU                  *pstRmnet2PdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstRmnet2SpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);
    pstRmnet2PdpAddr                    = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_2);
    pstRmnet2SpecNetCardCtx             = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_2);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* 网卡1ipv6激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* 网卡2ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 7;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_2;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstRmnet2SpecNetCardCtx->enModemType);
    EXPECT_EQ(7, pstRmnet2PdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstRmnet2PdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_2, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 7));

    /* 第一次handover */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* 网卡2的内容匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstRmnet2SpecNetCardCtx->enModemType);
    EXPECT_EQ(7, pstRmnet2PdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstRmnet2PdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_2, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 7));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_012
测试用例标题      : 配置外部modem切换到内modem，ipv6类型PDP激活(第二次modem切换)
预期结果          : 网卡上下文只保存内modem的激活信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_012)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    for (i = 0; i < 10; i++)
    {
        /* 网卡1ipv4激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 网卡1ipv6激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 第一次handover */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 第二次handover */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 网卡1 ipv4去激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 网卡1 ipv6去激活 */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));
    }

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_013
测试用例标题      : handover流程压力测试
预期结果          : 网卡上下文工作正常
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_013)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* 网卡1ipv6激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    for (i = 0; i < 10; i++)
    {
        /* 第一次外modem handover 内modem */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 第二次外modem handover 内modem */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 第一次内modem handover 外modem */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* 第二次内modem handover 外modem */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 2;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* 函数调用 */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* 参数匹配 */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(2, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));
    }

    /* 网卡1 ipv4去激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 2;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* 网卡1 ipv6去激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_014
测试用例标题      : handover过程中清除ipv4上下文中异常rabid对应网卡id失败
预期结果          : 网卡上下文工作正常
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_014)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_INSIDE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = RNIC_PDN_ID_INVALID;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 4;                /* 无效rabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_015
测试用例标题      : handover过程中清除ipv6上下文中异常rabid对应网卡id失败
预期结果          : 网卡上下文工作正常
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_015)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_INSIDE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId       = RNIC_PDN_ID_INVALID;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 4;                /* 无效rabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_016
测试用例标题      : handover过程中清除ipv4v6上下文中异常rabid对应网卡id失败
预期结果          : 网卡上下文工作正常
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_016)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_INSIDE;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucPdnId       = RNIC_PDN_ID_INVALID;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = 4;                /* 无效rabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_017
测试用例标题      : handover过程中清除ipv4v6上下文中异常pdnid对应网卡id失败
预期结果          : 网卡上下文工作正常
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_017)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucPdnId       = 21;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = RNIC_PDN_ID_INVALID;                /* 无效rabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_018
测试用例标题      : handover过程中清除ipv6上下文中异常pdnid对应网卡id失败
预期结果          : 网卡上下文工作正常
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_018)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId       = 21;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = RNIC_PDN_ID_INVALID;                /* 无效rabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_019
测试用例标题      : handover过程中清除ipv4上下文中异常pdnid对应网卡id失败
预期结果          : 网卡上下文工作正常
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_019)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 21;       /* 无效pdnid */
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = RNIC_PDN_ID_INVALID;

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_020
测试用例标题      : handover过程中清除ipv4上下文中异常pdnid对应网卡id失败
预期结果          : 网卡上下文工作正常
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_020)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 21;       /* 无效pdnid */
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = RNIC_PDN_ID_INVALID;

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_021
测试用例标题      : 外部modem激活时，收到IPV4V6类型去激活，去激活成功
预期结果          : 去激活成功
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_021)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucPdnId       = 1;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4v6去激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4V6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    MOCKER(RNIC_SaveNetIdByPdnId)
        .will(returnValue(VOS_ERR));

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#endif
/*******************************************************************
测试用例编号      : Test_RNIC_RcvRnicRmnetConfigReq_022
测试用例标题      : 内部modem激活时，收到IPV4V6类型去激活，去激活成功
预期结果          : 去激活成功
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_022)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* 全局变量初始化 */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_INSIDE;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucPdnId       = RNIC_PDN_ID_INVALID;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = 5;

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 网卡1ipv4v6去激活 */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4V6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    MOCKER(RNIC_SaveNetIdByRabId)
        .stubs()
        .will(returnValue(VOS_ERR));

    /* 函数调用 */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



/* 补充覆盖率 */
/*****************************************************************************
类名       : Test_RNIC_ProcInsideModemIpv4ActInd
功能描述   : RNIC_ProcInsideModemIpv4ActInd UT工程类
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_ProcInsideModemIpv4ActInd: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_ProcInsideModemIpv4ActInd_001
测试用例标题      : 配置内部modem，构造rabid失败
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ProcInsideModemIpv4ActInd, Test_RNIC_ProcInsideModemIpv4ActInd_001)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId  = RNIC_RM_NET_ID_0;
    stPdpStatusInd.usModemId  = RNIC_MODEM_TYPE_INSIDE;

    MOCKER(RNIC_BuildRabIdByModemId)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(RNIC_SaveNetIdByRabId)
        .expects(never());

    RNIC_ProcInsideModemIpv4ActInd(&stPdpStatusInd);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_ProcInsideModemIpv4ActInd_002
测试用例标题      : 配置内部modem，保存网卡id失败
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ProcInsideModemIpv4ActInd, Test_RNIC_ProcInsideModemIpv4ActInd_002)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId = RNIC_RM_NET_ID_1;
    stPdpStatusInd.ucRabId   = 4;

    MOCKER(RNIC_GetDsflowTimerIdByNetId)
        .expects(never());

    RNIC_ProcInsideModemIpv4ActInd(&stPdpStatusInd);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_ProcInsideModemIpv6ActInd
功能描述   : RNIC_ProcInsideModemIpv6ActInd UT工程类
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_ProcInsideModemIpv6ActInd: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_ProcInsideModemIpv6ActInd_001
测试用例标题      : 配置内部modem，构造rabid失败
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ProcInsideModemIpv6ActInd, Test_RNIC_ProcInsideModemIpv6ActInd_001)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId  = RNIC_RM_NET_ID_0;
    stPdpStatusInd.usModemId  = RNIC_MODEM_TYPE_INSIDE;

    MOCKER(RNIC_BuildRabIdByModemId)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(RNIC_SaveNetIdByRabId)
        .expects(never());

    RNIC_ProcInsideModemIpv6ActInd(&stPdpStatusInd);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_ProcInsideModemIpv6ActInd_002
测试用例标题      : 配置内部modem，保存网卡id失败
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ProcInsideModemIpv6ActInd, Test_RNIC_ProcInsideModemIpv6ActInd_002)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId = RNIC_RM_NET_ID_1;
    stPdpStatusInd.ucRabId   = 4;

    MOCKER(RNIC_GetDsflowTimerIdByNetId)
        .expects(never());

    RNIC_ProcInsideModemIpv6ActInd(&stPdpStatusInd);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
类名       : Test_RNIC_ProcOutsideModemIpv6ActInd
功能描述   : RNIC_ProcOutsideModemIpv6ActInd UT工程类
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_ProcOutsideModemIpv6ActInd: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_ProcOutsideModemIpv6ActInd_001
测试用例标题      : 配置内部modem，构造rabid失败
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ProcOutsideModemIpv6ActInd, Test_RNIC_ProcOutsideModemIpv6ActInd_001)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId = RNIC_RM_NET_ID_1;
    stPdpStatusInd.ucPdnId   = 21;

    MOCKER(RNIC_GetDsflowTimerIdByNetId)
        .expects(never());

    RNIC_ProcOutsideModemIpv6ActInd(&stPdpStatusInd);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_ProcOutsideModemIpv4ActInd
功能描述   : RNIC_ProcOutsideModemIpv4ActInd UT工程类
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_ProcOutsideModemIpv4ActInd: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* 初始化RNIC上下文信息 */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_ProcOutsideModemIpv4ActInd_001
测试用例标题      : 配置内部modem，构造rabid失败
预期结果          : 保持网卡的配置信息
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ProcOutsideModemIpv4ActInd, Test_RNIC_ProcOutsideModemIpv4ActInd_001)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId = RNIC_RM_NET_ID_1;
    stPdpStatusInd.ucPdnId   = 21;

    MOCKER(RNIC_GetDsflowTimerIdByNetId)
        .expects(never());

    RNIC_ProcOutsideModemIpv4ActInd(&stPdpStatusInd);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/* 补充覆盖率 */
#endif
/* Added by m00217266 for L-C互操作项目, 2014-2-7, end */
#endif
