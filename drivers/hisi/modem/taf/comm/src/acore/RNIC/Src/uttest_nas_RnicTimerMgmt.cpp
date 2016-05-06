#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicTimerMgmt.h"


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

//说明: 经过改造后的gtest+，测试套和测试用例名字不允许为空
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
/*****************************************************************************
类名       : Test_RNIC_InitAllTimers
功能描述   : RNIC_InitAllTimers UT工程类
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_InitAllTimers: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_InitAllTimers_001
测试用例标题      : 初始化RNIC定时器的CTX
预期结果          : RNIC的所有定时器资源都初始化成功
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_InitAllTimers, Test_RNIC_InitAllTimers_001)
{
    RNIC_TIMER_CTX_STRU                 astTimerCtx[RNIC_MAX_TIMER_NUM];   /* RNIC当前正在运行的定时器资源 */
    VOS_UINT32                          i;

    RNIC_InitAllTimers(astTimerCtx);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(VOS_NULL_PTR, astTimerCtx[i].hTimer);
        EXPECT_EQ(TI_RNIC_TIMER_BUTT, astTimerCtx[i].enTimerId);
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, astTimerCtx[i].enTimerStatus);

    }
}

/*****************************************************************************
类名       : Test_RNIC_StartTimer
功能描述   : RNIC_StartTimer UT工程类
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_StartTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }

};

/*******************************************************************
测试用例编号      : Test_RNIC_StartTimer_001
测试用例标题      : 当前无可用的定时器资源时直接返回
预期结果          : 直接返回,记录出错日志
修改历史          :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_StartTimer, Test_RNIC_StartTimer_001)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    }

    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DSFLOW_STATS_LEN);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_NE(TI_RNIC_DSFLOW_STATS_0, pstRnicTimerCtx[i].enTimerId);
    }
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartTimer_002
测试用例标题      : 定时器长度VOS_TIMER_MAX_LENGTH时，启动VOS_TIMER_MAX_LENGTH的定时器时长
预期结果          : 启动VOS_TIMER_MAX_LENGTH的定时器时长,启动定时器失败,不更新定时器状态
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_StartTimer, Test_RNIC_StartTimer_002)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .stubs()
        .will(returnValue(VOS_ERR));


    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DSFLOW_STATS_LEN + VOS_TIMER_MAX_LENGTH);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, pstRnicTimerCtx[i].enTimerStatus);
    }

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_RNIC_StartTimer_003
测试用例标题      : 有空闲资源时,启动TI_RNIC_DEMAND_DIAL_DISCONNECT定时器正常
预期结果          : TI_RNIC_DEMAND_DIAL_DISCONNECT定时器正常启动
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartTimer, Test_RNIC_StartTimer_003)
{

    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .stubs()
        .with(any(),eq(ACPU_PID_RNIC),eq(TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN),any(),any(),any())
        .will(returnValue(VOS_OK));

    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, pstRnicTimerCtx[0].enTimerStatus);
    EXPECT_EQ(TI_RNIC_DEMAND_DIAL_DISCONNECT, pstRnicTimerCtx[0].enTimerId);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_RNIC_StartTimer_004
测试用例标题      : TI_RNIC_DEMAND_DIAL_DISCONNECT定时器已经启动时,再次启动该定时器直接返回
预期结果          : 再次启动该定时器直接返回
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartTimer, Test_RNIC_StartTimer_004)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    pstRnicTimerCtx[1].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    pstRnicTimerCtx[1].enTimerId     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    MOCKER(V_StartRelTimer)
        .expects(never());

    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, pstRnicTimerCtx[1].enTimerStatus);
    EXPECT_EQ(TI_RNIC_DEMAND_DIAL_DISCONNECT, pstRnicTimerCtx[1].enTimerId);


    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_StopTimer
功能描述   : Test_RNIC_StopTimer UT工程类
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_StopTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }

};

/*******************************************************************
测试用例编号      : Test_RNIC_StopTimer_001
测试用例标题      : TI_RNIC_DEMAND_DIAL_DISCONNECT该定时器未启动直接返回
预期结果          : 直接返回
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StopTimer, Test_RNIC_StopTimer_001)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, pstRnicTimerCtx[i].enTimerStatus);
    }

}

/*******************************************************************
测试用例编号      : Test_RNIC_StopTimer_002
测试用例标题      : TI_RNIC_DEMAND_DIAL_DISCONNECT定时器运行过程中停止TI_RNIC_DEMAND_DIAL_DISCONNECT定时器
预期结果          : 停止TI_RNIC_DEMAND_DIAL_DISCONNECT定时器
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StopTimer, Test_RNIC_StopTimer_002)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;

    enTimerId = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    pstRnicTimerCtx[2].hTimer        = (HTIMER)(&enTimerId);
    pstRnicTimerCtx[2].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    pstRnicTimerCtx[2].enTimerId     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, pstRnicTimerCtx[i].enTimerStatus);
    }
}

/*****************************************************************************
类名       : Test_RNIC_StopAllTimer
功能描述   : RNIC_StopAllTimer UT工程类
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_StopAllTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }

};


/*******************************************************************
测试用例编号      : Test_RNIC_StopAllTimer_001
测试用例标题      : 停止所有定时器
预期结果          : 直接返回
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StopAllTimer, Test_RNIC_StopAllTimer_001)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    }

    RNIC_StopAllTimer();

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, pstRnicTimerCtx[i].enTimerStatus);
    }

}

/*****************************************************************************
类名       : Test_RNIC_GetTimerStatus
功能描述   : RNIC_GetTimerStatus UT工程类
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_GetTimerStatus: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }

};

/*******************************************************************
测试用例编号      : Test_RNIC_GetTimerStatus_001
测试用例标题      : 当前TI_RNIC_DEMAND_DIAL_DISCONNECT定时器停止时查询定时器状态返回停止
预期结果          : 定时器状态返回停止
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_GetTimerStatus, Test_RNIC_GetTimerStatus_001)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));
}


/*******************************************************************
测试用例编号      : Test_RNIC_GetTimerStatus_002
测试用例标题      : 当前TI_RNIC_DEMAND_DIAL_DISCONNECT定时器运行时但获取剩余时间失败查询定时器状态返回停止
预期结果          : 定时器状态返回停止
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_GetTimerStatus, Test_RNIC_GetTimerStatus_002)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    pstRnicTimerCtx[0].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    pstRnicTimerCtx[0].enTimerId     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    MOCKER(V_GetRelTmRemainTime)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(RNIC_StopTimer)
        .expects(exactly(1));

    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));
}


/*******************************************************************
测试用例编号      : Test_RNIC_GetTimerStatus_003
测试用例标题      : 当前TI_RNIC_DEMAND_DIAL_DISCONNECT定时器运行时同时获取剩余时间成功查询定时器状态返回运行
预期结果          : 定时器状态返回运行
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_RNIC_GetTimerStatus, Test_RNIC_GetTimerStatus_003)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    pstRnicTimerCtx[0].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    pstRnicTimerCtx[0].enTimerId     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    MOCKER(V_GetRelTmRemainTime)
        .stubs()
        .will(returnValue(VOS_OK));

    MOCKER(RNIC_StopTimer)
        .expects(never());

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));


}

#endif
