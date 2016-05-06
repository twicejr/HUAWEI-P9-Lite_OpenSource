#include "gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsTimerMgmt.h"

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



#if (FEATURE_OFF == FEATURE_SKB_EXP)            
/*****************************************************************************
类名       : Test_ADS_DL_StartAdqEmptyTimer
功能描述   : ADS_DL_StartAdqEmptyTimer UT工程类
修改历史   :
1.日   期  : 2013-1-4
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_DL_StartAdqEmptyTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        ADS_InitTiCtx();       
    }
    void TearDown()
    {
    }

};

/*******************************************************************
测试用例编号      : Test_ADS_DL_StartAdqEmptyTimer_001
测试用例标题      : 当前无可用的定时器资源时直接返回
预期结果          : 直接返回,记录出错日志
修改历史          :
1.日   期  : 2013-1-4
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_DL_StartAdqEmptyTimer, Test_ADS_DL_StartAdqEmptyTimer_001)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_RUNNING;
    }

    MOCKER(V_StartCallBackRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));
	
    ADS_DL_StartAdqEmptyTimer();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_DL_StartAdqEmptyTimer_002
测试用例标题      : 启动定时器失败
预期结果          : 直接返回,记录出错日志
修改历史          :
1.日   期  : 2013-1-4
  作   者  : l60609
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_DL_StartAdqEmptyTimer, Test_ADS_DL_StartAdqEmptyTimer_002)
{
    MOCKER(V_StartCallBackRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ADS_DL_StartAdqEmptyTimer();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名       : Test_ADS_StartTimer
功能描述   : ADS_StartTimer UT工程类
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_StartTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        ADS_InitTiCtx();       
    }
    void TearDown()
    {
    }

};

/*******************************************************************
测试用例编号      : Test_ADS_StartTimer_001
测试用例标题      : 当前无可用的定时器资源时直接返回
预期结果          : 直接返回,记录出错日志
修改历史          :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_001)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_RUNNING;
    }

    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, TI_ADS_UL_SEND_LEN);

}

/*******************************************************************
测试用例编号      : Test_ADS_StartTimer_002
测试用例标题      : 定时器长度VOS_TIMER_MAX_LENGTH时，启动VOS_TIMER_MAX_LENGTH的定时器时长
预期结果          : 启动VOS_TIMER_MAX_LENGTH的定时器时长,启动定时器失败,不更新定时器状态
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_002)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));


    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, TI_ADS_UL_SEND_LEN + VOS_TIMER_MAX_LENGTH);

    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(ADS_TIMER_STATUS_STOP, pstAdsTimerCtx[i].enTimerStatus);
    }

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ADS_StartTimer_003
测试用例标题      : 有空闲资源时,启动TI_ADS_UL_SEND定时器正常
预期结果          : TI_ADS_UL_SEND定时器正常启动
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_003)
{

    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .stubs()
        .with(any(),eq(ACPU_PID_ADS_UL),eq((VOS_UINT32)TI_ADS_UL_SEND_LEN))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, TI_ADS_UL_SEND_LEN);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, pstAdsTimerCtx[0].enTimerStatus);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ADS_StartTimer_004
测试用例标题      : TI_ADS_UL_SEND定时器已经启动时,再次启动该定时器直接返回
预期结果          : 再次启动该定时器直接返回
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_004)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    pstAdsTimerCtx[TI_ADS_UL_SEND].enTimerStatus = ADS_TIMER_STATUS_RUNNING;

    MOCKER(V_StartRelTimer)
        .expects(never());

    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, TI_ADS_UL_SEND_LEN);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, pstAdsTimerCtx[TI_ADS_UL_SEND].enTimerStatus);


    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



/*******************************************************************
测试用例编号      : Test_ADS_StartTimer_005
测试用例标题      : TI_ADS_UL_SEND定时器启动时长为0
预期结果          : 启动失败
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_005)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .expects(never());

    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, 0);

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, pstAdsTimerCtx[1].enTimerStatus);


    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*****************************************************************************
类名       : Test_ADS_StopTimer
功能描述   : Test_ADS_StopTimer UT工程类
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_StopTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        ADS_InitTiCtx();           
    }
    void TearDown()
    {
    }

};

/*******************************************************************
测试用例编号      : Test_ADS_StopTimer_001
测试用例标题      : TI_ADS_UL_SEND该定时器未启动直接返回
预期结果          : 直接返回
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_ADS_StopTimer, Test_ADS_StopTimer_001)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(ADS_TIMER_STATUS_STOP, pstAdsTimerCtx[i].enTimerStatus);
    }

}

/*******************************************************************
测试用例编号      : Test_ADS_StopTimer_002
测试用例标题      : TI_ADS_UL_SEND定时器运行过程中停止TI_ADS_UL_SEND定时器
预期结果          : 停止TI_ADS_UL_SEND定时器
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_ADS_StopTimer, Test_ADS_StopTimer_002)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;
    HTIMER                              hTimer;
    ADS_TIMER_ID_ENUM_UINT32            enTimerId;

    enTimerId = TI_ADS_UL_SEND;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    pstAdsTimerCtx[TI_ADS_UL_SEND].hTimer        = (HTIMER)(&enTimerId);
    pstAdsTimerCtx[TI_ADS_UL_SEND].enTimerStatus = ADS_TIMER_STATUS_RUNNING;

    MOCKER(V_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(ADS_TIMER_STATUS_STOP, pstAdsTimerCtx[i].enTimerStatus);
    }
}

/*****************************************************************************
类名       : Test_ADS_GetTimerStatus
功能描述   : ADS_GetTimerStatus UT工程类
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_GetTimerStatus: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        ADS_InitTiCtx();      
    }
    void TearDown()
    {
    }

};

/*******************************************************************
测试用例编号      : Test_ADS_GetTimerStatus_001
测试用例标题      : 当前TI_ADS_UL_SEND定时器停止时查询定时器状态返回停止
预期结果          : 定时器状态返回停止
修改历史   :
1.日   期  : 2011-12-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_GetTimerStatus, Test_ADS_GetTimerStatus_001)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    pstAdsTiCtx[0].enTimerStatus = ADS_TIMER_STATUS_STOP;

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, ADS_GetTimerStatus(ACPU_PID_ADS_UL,TI_ADS_UL_SEND));
}

