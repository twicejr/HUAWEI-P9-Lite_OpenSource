/*****************************************************************************
1 头文件包含
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicInit.h"


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#if 0
/*****************************************************************************
2 用例实现
*****************************************************************************/

/*****************************************************************************
类名       : Test_RNIC_PidInit
功能描述   : RNIC_PidInit UT工程类
修改历史   :
1.日   期  : 2012-12-05
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_PidInit: public ::testing::Test
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
测试用例编号      : Test_RNIC_PidInit_001
测试用例标题      : VOS_IP_LOAD_CONFIG分支处理
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2012-12-05
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_PidInit, Test_RNIC_PidInit_001)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;
    RNIC_CTX_STRU                      *pstRnicCtx;

    /* 参数初始化 */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_PidInit(enPhase);

    /* 获取结果 */
    pstRnicCtx = RNIC_GetRnicCtxAddr();

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(AT_RNIC_DIAL_MODE_MANUAL, pstRnicCtx->stDialMode.enDialMode);
    EXPECT_EQ(RNIC_DIAL_DEMA_IDLE_TIME, pstRnicCtx->stDialMode.ulIdleTime);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_0, pstRnicCtx->astSpecCtx[0].enTiDsFlowStats);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_1, pstRnicCtx->astSpecCtx[1].enTiDsFlowStats);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_2, pstRnicCtx->astSpecCtx[2].enTiDsFlowStats);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    EXPECT_EQ(MODEM_ID_1, pstRnicCtx->astSpecCtx[3].enModemId);
#endif
    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
    
}

/*******************************************************************
测试用例编号      : Test_RNIC_PidInit_002
测试用例标题      : default分支处理
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2012-12-05
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_PidInit, Test_RNIC_PidInit_002)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* 参数初始化 */
    enPhase = VOS_IP_FARMALLOC;

    /* 桩函数 */
    MOCKER(RNIC_GetRnicCtxAddr)
        .expects(never());
    
    MOCKER(RNIC_InitCtx)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_PidInit(enPhase);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);

    enPhase = VOS_IP_BUTT;
    ulRst = RNIC_PidInit(enPhase);
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_PidInit_003
测试用例标题      : 创建信号量失败
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_PidInit, Test_RNIC_PidInit_003)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;
    RNIC_CTX_STRU                      *pstRnicCtx;

    /* 参数初始化 */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* 桩函数 */
    MOCKER(VOS_SmBCreate)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_PidInit(enPhase);

    /* 获取结果 */
    pstRnicCtx = RNIC_GetRnicCtxAddr();

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(AT_RNIC_DIAL_MODE_MANUAL, pstRnicCtx->stDialMode.enDialMode);
    EXPECT_EQ(RNIC_DIAL_DEMA_IDLE_TIME, pstRnicCtx->stDialMode.ulIdleTime);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_0, pstRnicCtx->astSpecCtx[0].enTiDsFlowStats);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_1, pstRnicCtx->astSpecCtx[1].enTiDsFlowStats);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_2, pstRnicCtx->astSpecCtx[2].enTiDsFlowStats);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    EXPECT_EQ(MODEM_ID_1, pstRnicCtx->astSpecCtx[3].enModemId);
#endif
    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_FidInit
功能描述   : RNIC_FidInit UT工程类
修改历史   :
1.日   期  : 2012-12-05
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_FidInit: public ::testing::Test
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
测试用例编号      : Test_RNIC_FidInit_001
测试用例标题      : 网卡模块注册PID成功，且任务优先级设置成功
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2012-12-05
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_FidInit, Test_RNIC_FidInit_001)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* 参数初始化 */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* 桩函数 */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_RNIC), eq((VOS_UINT_PTR)RNIC_PidInit), eq((VOS_UINT_PTR)RNIC_ProcMsg))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterMsgTaskPrio)
        .expects(exactly(1))
        .with(eq(ACPU_FID_RNIC), eq(VOS_PRIORITY_P6))
        .will(returnValue(VOS_OK));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_FidInit(enPhase);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_FidInit_002
测试用例标题      : 网卡模块注册PID失败
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2012-12-05
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_FidInit, Test_RNIC_FidInit_002)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* 参数初始化 */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* 桩函数 */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_RNIC), eq((VOS_UINT_PTR)RNIC_PidInit), eq((VOS_UINT_PTR)RNIC_ProcMsg))
        .will(returnValue(VOS_ERR));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_FidInit(enPhase);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_FidInit_003
测试用例标题      : 网卡模块注册PID成功，但任务优先级设置失败
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2012-12-05
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_FidInit, Test_RNIC_FidInit_003)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* 参数初始化 */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* 桩函数 */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_RNIC), eq((VOS_UINT_PTR)RNIC_PidInit), eq((VOS_UINT_PTR)RNIC_ProcMsg))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterMsgTaskPrio)
        .expects(exactly(1))
        .with(eq(ACPU_FID_RNIC), eq(VOS_PRIORITY_P6))
        .will(returnValue(VOS_ERR));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_FidInit(enPhase);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_FidInit_004
测试用例标题      : default分支处理
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2012-12-05
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_FidInit, Test_RNIC_FidInit_004)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* 参数初始化 */
    enPhase = VOS_IP_FARMALLOC;

    /* 桩函数 */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(never());
    
    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_FidInit(enPhase);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);

    enPhase = VOS_IP_BUTT;
    ulRst = RNIC_FidInit(enPhase);
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*****************************************************************************
类名       : Test_RNIC_CCpuResetCallback
功能描述   : RNIC_CCpuResetCallback UT工程类
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_CCpuResetCallback: public ::testing::Test
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
测试用例编号      : Test_RNIC_CCpuResetCallback_001
测试用例标题      : C核复位前，分配内存失败
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_001)
{
    VOS_UINT32                          ulRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
    
}

/*******************************************************************
测试用例编号      : Test_RNIC_CCpuResetCallback_002
测试用例标题      : C核复位前，消息发送失败
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_002)
{
    VOS_UINT32                          ulRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
    
}

/*******************************************************************
测试用例编号      : Test_RNIC_CCpuResetCallback_003
测试用例标题      : C核复位前，消息发送成功，锁信号量失败
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_003)
{
    VOS_UINT32                          ulRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
    
}


/*******************************************************************
测试用例编号      : Test_RNIC_CCpuResetCallback_004
测试用例标题      : C核复位前，消息发送成功，锁信号量成功
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_004)
{
    VOS_UINT32                          ulRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
    
}

/*******************************************************************
测试用例编号      : Test_RNIC_CCpuResetCallback_005
测试用例标题      : C核复位后
预期结果          : 返回VOS_OK
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_005)
{
    VOS_UINT32                          ulRst;

    /* 参数初始化 */

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
    
}

/*******************************************************************
测试用例编号      : Test_RNIC_CCpuResetCallback_006
测试用例标题      : 非C核复位前后
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_006)
{
    VOS_UINT32                          ulRst;

    /* 参数初始化 */

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_INVALID, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
    
}

#endif
