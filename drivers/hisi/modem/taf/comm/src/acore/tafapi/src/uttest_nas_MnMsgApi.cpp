#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include  "product_config.h"
#include  "vos.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "ATCmdProc.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern VOS_UINT32 MSG_SendAppReq(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const VOS_VOID                      *pSendParm
);

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

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


/*****************************************************************************
类名	 : Test_MN_MSG_ReqStub
功能描述 : MN_MSG_ReqStub UT工程类
修改历史     :
1.日   期  : 2011-10-13
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_MN_MSG_ReqStub: public ::testing::Test
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
测试用例编号      : Test_MN_MSG_ReqStub_001
测试用例标题      : 输入参数指针为空
预期结果          : 函数返回MN_ERR_NULLPTR
修改历史          :
1.日   期         : 2011-10-14
  作   者         : f62575
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_MN_MSG_ReqStub,Test_MN_MSG_ReqStub_001)
{
}

/*******************************************************************
测试用例编号      : Test_MN_MSG_ReqStub_002
测试用例标题      : 消息发送成功
预期结果          : 函数返回MN_ERR_NO_ERROR
修改历史          :
1.日   期         : 2011-10-14
  作   者         : f62575
  修改内容        : 新建CASE
*******************************************************************/
TEST_F(Test_MN_MSG_ReqStub,Test_MN_MSG_ReqStub_002)
{
}

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

/******************************************************************************
类名     : Test_MN_MSG_GetAllCbMids
功能描述 : MN_MSG_GetAllCbMids UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_MN_MSG_GetAllCbMids: public ::testing::Test
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
*测试项:           申请消息并发送到MSG模块成功函数返回成功
*被测函数功能描述: 提供给应用层查询CBS列表功能的请求
*预期结果：        返回成功
************************* 修改记录 ********************************
#  1.日    期: 2010年05月17日
#    作    者: z40661
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_MN_MSG_GetAllCbMids,Test_MN_MSG_GetAllCbMids_01)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NO_ERROR,MN_MSG_GetAllCbMids(clientId,opId));
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           申请消息并发送到MSG模块成功函数返回成功
*被测函数功能描述: 提供给应用层增加CBS列表功能的请求
*预期结果：        返回成功
************************* 修改记录 ********************************
#  1.日    期: 2010年05月17日
#    作    者: z40661
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_MN_MSG_AddCbMids,Test_MN_MSG_GetAllCbMids_02)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;
    TAF_CBA_CBMI_RANGE_LIST_STRU              stCbmirList;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NO_ERROR,MN_MSG_AddCbMids(clientId,opId,&stCbmirList));
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           输入空指针函数返回失败
*被测函数功能描述: 提供给应用层增加CBS列表功能的请求
*预期结果：        返回失败
************************* 修改记录 ********************************
#  1.日    期: 2010年05月17日
#    作    者: z40661
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_MN_MSG_AddCbMids,Test_MN_MSG_GetAllCbMids_03)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NULLPTR,MN_MSG_AddCbMids(clientId,opId,VOS_NULL_PTR));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/******************************************************************************
类名     : Test_MN_MSG_DelCbMids
功能描述 : MN_MSG_DelCbMids UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_MN_MSG_DelCbMids: public ::testing::Test
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
*测试项:           申请消息并发送到MSG模块成功函数返回成功
*被测函数功能描述: 提供给应用层删除CBS列表功能的请求
*预期结果：        返回成功
************************* 修改记录 ********************************
#  1.日    期: 2010年05月17日
#    作    者: z40661
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_MN_MSG_DelCbMids,Test_MN_MSG_DelCbMids_01)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;
    TAF_CBA_CBMI_RANGE_LIST_STRU              stCbmirList;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NO_ERROR,MN_MSG_DelCbMids(clientId,opId,&stCbmirList));
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
*测试项:           输入空指针函数返回失败
*被测函数功能描述: 提供给应用层删除CBS列表功能的请求
*预期结果：        返回失败
************************* 修改记录 ********************************
#  1.日    期: 2010年05月17日
#    作    者: z40661
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_MN_MSG_DelCbMids,Test_MN_MSG_DelCbMids_02)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NULLPTR,MN_MSG_DelCbMids(clientId,opId,VOS_NULL_PTR));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/******************************************************************************
类名     : Test_MN_MSG_EmptyCbMids
功能描述 : MN_MSG_EmptyCbMids UT工程类
修改历史 :
 1.日   期  : 2014-05-28
   作   者  : Y00213812
   修改内容 : 64bit ut修改
******************************************************************************/
class Test_MN_MSG_EmptyCbMids: public ::testing::Test
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
*测试项:           申请消息并发送到MSG模块成功函数返回成功
*被测函数功能描述: 删除所有CBS ID
*预期结果：        返回成功
************************* 修改记录 ********************************
#  1.日    期: 2010年05月17日
#    作    者: z40661
#    修改内容: 新建CASE
*******************************************************************/
TEST(Test_MN_MSG_EmptyCbMids,Test_MN_MSG_EmptyCbMids_01)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NO_ERROR,MN_MSG_EmptyCbMids(clientId,opId));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



#endif

