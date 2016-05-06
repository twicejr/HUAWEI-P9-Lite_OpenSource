#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtSndMsg.h"

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

/*****************************************************************************
类名     : Test_AT_FillAppReqMsgHeader
功能描述 : Test_AT_FillAppReqMsgHeader UT工程类
修改历史 :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_FillAppReqMsgHeader: public ::testing::Test
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
测试用例编号      : Test_AT_FillAppReqMsgHeader_001
测试用例标题      : 填充AT消息头
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_FillAppReqMsgHeader, Test_AT_FillAppReqMsgHeader_001)
{
	MN_APP_REQ_MSG_STRU                *pMsg;
	MN_CLIENT_ID_T                      usClientId;
	MN_OPERATION_ID_T                   ucOpId = 0;
	VOS_UINT16                          usMsgType = 0;
	VOS_UINT32                          ulRcvPid;
	VOS_UINT32								ulRslt;

	pMsg = (MN_APP_REQ_MSG_STRU *)malloc(sizeof(MN_APP_REQ_MSG_STRU));
	usClientId = AT_CLIENT_ID_APP;
	ulRcvPid   = I0_WUEPS_PID_TAF;

	MOCKER(AT_GetDestPid)
		.expects(exactly(1))
		.with(eq(usClientId), eq(ulRcvPid))
		.will(returnValue((VOS_UINT32)I0_WUEPS_PID_TAF));

	ulRslt = AT_FillAppReqMsgHeader(pMsg, usClientId, ucOpId, usMsgType, ulRcvPid);

	EXPECT_EQ(I0_WUEPS_PID_TAF, pMsg->ulReceiverPid);
	EXPECT_EQ(VOS_OK, ulRslt);

	GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_AT_SndSetFastDorm
功能描述 : Test_AT_SndSetFastDorm UT工程类
修改历史 :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SndSetFastDorm: public ::testing::Test
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
测试用例编号      : Test_AT_SndSetFastDorm_001
测试用例标题      : 将消息发送到modem0的PID
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SndSetFastDorm, Test_AT_SndSetFastDorm_001)
{
	VOS_UINT16                          usClientId;
	VOS_UINT8                           ucOpId = 0;
	AT_RABM_FASTDORM_PARA_STRU         *pstFastDormPara;
	VOS_UINT32                          ulRslt;

	usClientId = AT_CLIENT_ID_APP;
	pstFastDormPara = (AT_RABM_FASTDORM_PARA_STRU *)malloc(sizeof(AT_RABM_FASTDORM_PARA_STRU));

	MOCKER(AT_GetDestPid)
		.expects(exactly(1))
		.with(eq(usClientId), eq(I0_WUEPS_PID_RABM))
		.will(returnValue((VOS_UINT32)I0_WUEPS_PID_RABM));

	ulRslt = AT_SndSetFastDorm(usClientId, ucOpId, pstFastDormPara);
;
	EXPECT_EQ(VOS_OK, ulRslt);

    free(pstFastDormPara);

	GlobalMockObject::verify();
}



/*****************************************************************************
类名     : Test_AT_SndQryFastDorm
功能描述 : Test_AT_SndQryFastDorm UT工程类
修改历史 :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SndQryFastDorm: public ::testing::Test
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
测试用例编号      : Test_AT_SndQryFastDorm_001
测试用例标题      : 将消息发送到modem0的PID
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SndQryFastDorm, Test_AT_SndQryFastDorm_001)
{
	VOS_UINT16                          usClientId;
	VOS_UINT8                           ucOpId = 0;
	VOS_UINT32                          ulRslt;

	usClientId = AT_CLIENT_ID_APP;

	MOCKER(AT_GetDestPid)
		.expects(exactly(1))
		.with(eq(usClientId), eq(I0_WUEPS_PID_RABM))
		.will(returnValue((VOS_UINT32)I0_WUEPS_PID_RABM));

	ulRslt = AT_SndQryFastDorm (usClientId, ucOpId);

	EXPECT_EQ(VOS_OK, ulRslt);

	GlobalMockObject::verify();

}
