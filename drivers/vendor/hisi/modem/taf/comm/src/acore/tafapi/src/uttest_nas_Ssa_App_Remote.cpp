#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "v_typdef.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "TafAppSsa.h"
#include "MnCommApi.h"
#include "Taf_Tafm_Remote.h"

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

#define    THIS_FILE_ID        PS_FILE_ID_SSA_APP_REMOTE_C

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



/*****************************************************************************
类名     : Test_TAF_EraseSSReq
功能描述 : TAF_EraseSSReq UT工程类
修改历史 :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新生成类
*****************************************************************************/
class Test_TAF_EraseSSReq: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_TAF_EraseSSReq_001
测试用例标题      : 业务删除操作
预期结果          : 调用MN_FillAndSndAppReqMsg发送业务请求到TAF
修改历史          :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新增函数
*******************************************************************/
TEST_F(Test_TAF_EraseSSReq, Test_TAF_EraseSSReq_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    TAF_SS_ERASESS_REQ_STRU             stPara;
    VOS_UINT32                          ulParaLen;

    PS_MEM_SET(&stPara, 0, sizeof(stPara));

    ulParaLen = sizeof(stPara);
    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_ERASESS_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_EraseSSReq(ClientId, OpId, &stPara);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // 执行检查
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_TAF_ActivateSSReq
功能描述 : TAF_InterrogateSSReq UT工程类
修改历史 :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新生成类
*****************************************************************************/
class Test_TAF_ActivateSSReq: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_TAF_ActivateSSReq_001
测试用例标题      : 业务激活操作
预期结果          : 调用MN_FillAndSndAppReqMsg发送业务请求到TAF
修改历史          :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新增函数
*******************************************************************/
TEST_F(Test_TAF_ActivateSSReq, Test_TAF_ActivateSSReq_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    TAF_SS_ACTIVATESS_REQ_STRU          stPara;
    VOS_UINT32                          ulParaLen;

    ulParaLen = sizeof(stPara);

    PS_MEM_SET(&stPara, 0, sizeof(stPara));

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_ACTIVATESS_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_ActivateSSReq(ClientId, OpId, &stPara);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // 执行检查
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_TAF_RegisterPasswordReq
功能描述 : TAF_RegisterPasswordReq UT工程类
修改历史 :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新生成类
*****************************************************************************/
class Test_TAF_RegisterPasswordReq: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_TAF_RegisterPasswordReq_001
测试用例标题      : 注册密码操作
预期结果          : 调用MN_FillAndSndAppReqMsg发送业务请求到TAF
修改历史          :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新增函数
*******************************************************************/
TEST_F(Test_TAF_RegisterPasswordReq, Test_TAF_RegisterPasswordReq_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    TAF_SS_REGPWD_REQ_STRU              stPara;
    VOS_UINT32                          ulParaLen;

    ulParaLen = sizeof(stPara);

    PS_MEM_SET(&stPara, 0, sizeof(stPara));

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_REGPWD_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_RegisterPasswordReq(ClientId, OpId, &stPara);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // 执行检查
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_TAF_EraseCCEntryReq
功能描述 : TAF_EraseCCEntryReq UT工程类
修改历史 :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新生成类
*****************************************************************************/
class Test_TAF_EraseCCEntryReq: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_TAF_EraseCCEntryReq_001
测试用例标题      : 去激活CCBS操作
预期结果          : 调用MN_FillAndSndAppReqMsg发送业务请求到TAF
修改历史          :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新增函数
*******************************************************************/
TEST_F(Test_TAF_EraseCCEntryReq, Test_TAF_EraseCCEntryReq_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    TAF_SS_ERASECC_ENTRY_REQ_STRU       stPara;
    VOS_UINT32                          ulParaLen;

    ulParaLen = sizeof(stPara);

    PS_MEM_SET(&stPara, 0, sizeof(stPara));

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_ERASECCENTRY_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_EraseCCEntryReq(ClientId, OpId, &stPara);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // 执行检查
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_TAF_SsReleaseComplete
功能描述 : TAF_SsReleaseComplete UT工程类
修改历史 :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新生成类
*****************************************************************************/
class Test_TAF_SsReleaseComplete: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_TAF_SsReleaseComplete_001
测试用例标题      : 释放链路操作
预期结果          : 调用MN_FillAndSndAppReqMsg发送业务请求到TAF
修改历史          :
1.日    期   : 2013年05月29日
  作    者   : f62575
  修改内容   : 新增函数
*******************************************************************/
TEST_F(Test_TAF_SsReleaseComplete, Test_TAF_SsReleaseComplete_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    VOS_UINT32                          ulParaLen;

    ulParaLen = 0;

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_RLEASE_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_SsReleaseComplete(ClientId, OpId);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // 执行检查
    GlobalMockObject::verify();

}


