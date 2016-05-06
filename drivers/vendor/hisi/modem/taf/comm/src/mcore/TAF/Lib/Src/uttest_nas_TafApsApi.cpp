#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "vos.h"
#include "PsCommonDef.h"
#include "TafApsApi.h"
#include "MnClient.h"
//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
extern VOS_UINT32 AT_GetDestPid(
                                MN_CLIENT_ID_T                      usClientId,
                                VOS_UINT32                          ulRcvPid
                                );
extern VOS_UINT32 TAF_PS_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

extern VOS_UINT8 TAF_APS_FindCidForDial(VOS_UINT32  ulAppPid);
extern VOS_UINT32 TAF_APS_GetSdfParaInfo(
    VOS_UINT8                           ucCid,
    TAF_SDF_PARA_STRU                  *pstSdfParaInfo
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
类名     : Test_TAF_PS_SndMsg
功能描述 : TAF_PS_SndMsg UT工程类
修改历史     :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_TAF_PS_SndMsg: public ::testing::Test
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
测试用例编号      : Test_TAF_PS_SndMsg_001
测试用例标题      : 将消息发送到modem0的PID
预期结果          : 函数返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_TAF_PS_SndMsg,Test_TAF_PS_SndMsg_001)
{
    VOS_UINT32                          ulTaskId;
    VOS_UINT32                          ulMsgId;
    TAF_CTRL_STRU                      *pstCtrl;
    VOS_UINT32                          ulLength;

    ulTaskId = I0_WUEPS_PID_TAF;
    ulMsgId = 1;
    pstCtrl = (TAF_CTRL_STRU*)malloc(sizeof(TAF_CTRL_STRU));
    pstCtrl->usClientId = AT_CLIENT_TAB_APP_INDEX;
    ulLength = 1;

    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(pstCtrl->usClientId),eq(ulTaskId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    TAF_PS_SndMsg(ulTaskId, ulMsgId,(VOS_VOID*)pstCtrl, ulLength);

    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_TAF_PS_GetCidSdfParaInfo
功能描述 : TAF_PS_GetCidSdfParaInfo UT工程类
修改历史 :
 1.日   期  : 2013-08-08
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_TAF_PS_GetCidSdfParaInfo: public ::testing::Test
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
/******************************************************************************
测试用例编号: Test_TAF_PS_GetCidSdfParaInfo_001
测试用例标题: 异步方式调用接口
预期结果    : 发送消息给APS，返回OK
修改历史    :
 1.日   期  : 2013-08-08
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_TAF_PS_GetCidSdfParaInfo, Test_TAF_PS_GetCidSdfParaInfo_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    TAF_SDF_PARA_QUERY_INFO_STRU        stSdfInfo;
    TAF_PS_SDF_INFO_REQ_STRU            stSdfInfoReq;

    // 参数初始化
    memset(&stSdfInfo, 0, sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));
    memset(&stSdfInfoReq, 0, sizeof(TAF_PS_SDF_INFO_REQ_STRU));
#if (FEATURE_IMS == FEATURE_ON)
    stSdfInfoReq.stCtrl.ulModuleId = PS_PID_IMSA;
#endif

    stSdfInfoReq.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stSdfInfoReq.stCtrl.ucOpId     = 0;
    // 初始化全局变量

    // MOCKER操作
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(any(),
              eq(ID_MSG_TAF_PS_GET_CID_SDF_REQ),
              mirror((void *)&stSdfInfoReq,(unsigned int)sizeof(TAF_PS_SDF_INFO_REQ_STRU)),
              eq((unsigned int)sizeof(TAF_PS_SDF_INFO_REQ_STRU)))
              .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRelt = TAF_PS_GetCidSdfParaInfo(stSdfInfoReq.stCtrl.ulModuleId,
                                      stSdfInfoReq.stCtrl.usClientId,
                                      stSdfInfoReq.stCtrl.ucOpId,
                                      VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRelt);
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_TAF_PS_GetUnusedCid
功能描述 : TAF_PS_GetUnusedCid UT工程类
修改历史 :
 1.日   期  : 2013-08-08
   作   者  : Y00213812
   修改内容 : 新增类
******************************************************************************/
class Test_TAF_PS_GetUnusedCid: public ::testing::Test
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
/******************************************************************************
测试用例编号: Test_TAF_PS_GetUnusedCid_001
测试用例标题: 异步方式调用接口
预期结果    : 不支持，返回VOS_ERR
修改历史    :
 1.日   期  : 2013-08-08
   作   者  : Y00213812
   修改内容 : 新增用例
******************************************************************************/
TEST_F(Test_TAF_PS_GetUnusedCid, Test_TAF_PS_GetUnusedCid_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    TAF_CTRL_STRU                       stCtrl;

    // 参数初始化
    memset(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

#if (FEATURE_IMS == FEATURE_ON)
    stCtrl.ulModuleId = PS_PID_IMSA;
#endif
    stCtrl.usClientId = AT_CLIENT_ID_APP;
    stCtrl.ucOpId     = 0;
    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRelt = TAF_PS_GetUnusedCid(stCtrl.ulModuleId,
                                 stCtrl.usClientId,
                                 stCtrl.ucOpId,
                                 VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRelt);
    GlobalMockObject::verify();
}


