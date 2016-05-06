#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_CsdInit.h"

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

#if( FEATURE_ON == FEATURE_CSD )
/*****************************************************************************
类名 : Test_CSD_FidInit
功能描述 : Test_ALink_Link UT工程类
修改历史     :
1.日   期  : 2011-11-04
  作   者  : w00199382
  修改内容 : 新生成类
*****************************************************************************/
class Test_CSD_FidInit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();

    }
    void TearDown()
    {
    }
private:

};

/*******************************************************************
测试用例编号      : TEST_CSD_FidInit_001
测试用例标题      : 任务初始化成功
预期结果          : VOS_OK
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_001 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(VOS_SmBCreate)
        .expects(exactly(2))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterPIDInfo)
        .with(eq(ACPU_PID_CSD))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterSelfTaskPrio)
        .with(eq(ACPU_FID_CSD),eq(CSD_UL_ProcDataTask))
        .will(returnValue(VOS_OK));

   MOCKER(VOS_RegisterSelfTaskPrio)
        .with(eq(ACPU_FID_CSD),eq(CSD_DL_ProcDataTask))
        .will(returnValue(VOS_OK));

   MOCKER(VOS_RegisterTaskPrio)
        .will(returnValue(VOS_OK));

    EXPECT_EQ(VOS_OK, CSD_FidInit(enInitPhase));


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
/*******************************************************************
测试用例编号      : TEST_CSD_FidInit_005
测试用例标题      : 任务初始化成功
预期结果          : VOS_OK
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_005 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(VOS_SmBCreate)
        .expects(exactly(2))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterPIDInfo)
        .with(eq(ACPU_PID_CSD))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterSelfTask)
        .with(eq(ACPU_FID_CSD),eq(CSD_UL_ProcDataTask))
        .will(returnValue(VOS_OK));

   MOCKER(VOS_RegisterSelfTask)
        .with(eq(ACPU_FID_CSD),eq(CSD_DL_ProcDataTask))
        .will(returnValue(VOS_OK));

   MOCKER(VOS_RegisterMsgTaskPrio)
        .will(returnValue(VOS_ERR));

    EXPECT_EQ(VOS_ERR, CSD_FidInit(enInitPhase));


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : TEST_CSD_FidInit_002
测试用例标题      : CSD_DL_ProcDataTask下行任务注册失败
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_002 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

     enInitPhase = VOS_IP_LOAD_CONFIG;

     MOCKER(VOS_SmBCreate)
         .expects(exactly(2))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterPIDInfo)
         .with(eq(ACPU_PID_CSD))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterSelfTask)
         .with(eq(ACPU_FID_CSD),eq(CSD_UL_ProcDataTask))
         .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterSelfTask)
         .with(eq(ACPU_FID_CSD),eq(CSD_DL_ProcDataTask))
         .will(returnValue(VOS_NULL_BYTE));

     EXPECT_EQ(VOS_ERR, CSD_FidInit(enInitPhase));


     //检查调用时，需要在用例结束位置加上这句
     GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      : TEST_CSD_FidInit_003
测试用例标题      : CSD_UL_ProcDataTask上行任务注册失败
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_003)
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

     enInitPhase = VOS_IP_LOAD_CONFIG;

     MOCKER(VOS_SmBCreate)
         .expects(exactly(2))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterPIDInfo)
         .with(eq(ACPU_PID_CSD))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterSelfTask)
         .with(eq(ACPU_FID_CSD),eq(CSD_UL_ProcDataTask))
         .will(returnValue(VOS_NULL_BYTE));

     EXPECT_EQ(VOS_ERR, CSD_FidInit(enInitPhase));


     //检查调用时，需要在用例结束位置加上这句
     GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      : TEST_CSD_FidInit_004
测试用例标题      : CSD_UL_PidInit任务注册失败
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_004 )
{
     VOS_INIT_PHASE_DEFINE          enInitPhase ;

     enInitPhase = VOS_IP_LOAD_CONFIG;

     MOCKER(VOS_SmBCreate)
         .expects(exactly(2))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterPIDInfo)
         .with(eq(ACPU_PID_CSD))
         .will(returnValue(VOS_ERR));


     EXPECT_EQ(VOS_ERR, CSD_FidInit(enInitPhase));


     //检查调用时，需要在用例结束位置加上这句
     GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      : TEST_CSD_InitDicc_001
测试用例标题      : CSD_InitDicc返回失败，DICC通道初始化失败
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_InitDicc_001 )
{

    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_ERR_BUTT));

    MOCKER(DICC_OpenChannel)
          .expects(never());

    EXPECT_EQ(VOS_ERR,CSD_UL_PidInit(enInitPhase));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      : TEST_CSD_InitDicc_002
测试用例标题      : CSD_InitDicc返回失败，DICC下行通道打开失败
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_InitDicc_002 )
{

    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_OK));

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_OK));

    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_0),eq(DICC_CHAN_ROLE_SENDER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_OK));

    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_2),eq(DICC_CHAN_ROLE_RECVER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_ERR_BUTT));

    MOCKER(CSD_InitCtx)
          .expects(never());


    EXPECT_EQ(VOS_ERR,CSD_UL_PidInit(enInitPhase));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}
/*******************************************************************
测试用例编号      : TEST_CSD_InitDicc_003
测试用例标题      : CSD_InitDicc返回失败，DICC上行通道打开失败
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_InitDicc_003 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_OK));



    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_0),eq(DICC_CHAN_ROLE_SENDER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_ERR_BUTT));

    MOCKER(CSD_InitCtx)
          .expects(never());


    EXPECT_EQ(VOS_ERR,CSD_UL_PidInit(enInitPhase));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      : TEST_CSD_InitSem_001
测试用例标题      : CSD_InitSem返回失败，上行数据队列信号量失败
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_InitSem_001 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(VOS_SmBCreate)
        .will(returnObjectList(VOS_OK, VOS_ERR));


    MOCKER(VOS_SmDelete)
        .with(eq(CSD_GetDownLinkDataSem()));


    EXPECT_EQ(VOS_ERR,CSD_FidInit(enInitPhase));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      : TEST_CSD_InitSem_002
测试用例标题      :  CSD_InitSem返回失败，下行数据队列信号量失败
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_InitSem_002 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(VOS_SmBCreate)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));


    MOCKER(VOS_SmDelete)
        .expects(exactly(1))
        .with(eq(CSD_GetDownLinkDataSem()));


    EXPECT_EQ(VOS_ERR,CSD_FidInit(enInitPhase));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      : TEST_CSD_UL_PidInit_001
测试用例标题      :  CSD_UL_PidInit成功
预期结果          : VOS_ERR
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_FidInit, TEST_CSD_UL_PidInit_001 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_OK));

    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_2),eq(DICC_CHAN_ROLE_RECVER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_OK));

    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_0),eq(DICC_CHAN_ROLE_SENDER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_OK));



    EXPECT_EQ(DICC_OK,CSD_UL_PidInit(enInitPhase));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}
#endif

#endif
