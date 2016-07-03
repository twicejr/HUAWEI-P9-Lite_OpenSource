#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "vos.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "MnCallApi.h"
#include  "product_config.h"
#include "MnErrorCode.h"
#include "AtParse.h"
#include "ATCmdProc.h"
#include "MnCommApi.h"

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

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




class Test_MN_CALL_QryCdur: public ::testing::Test
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


TEST_F(Test_MN_CALL_QryCdur,Test_MN_CALL_QryCdur_001)
{
}


class Test_MN_CALL_Orig: public ::testing::Test
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


TEST_F(Test_MN_CALL_Orig,Test_MN_CALL_Orig_001)
{
        // 参数定义
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        CallId;
    MN_CALL_ORIG_PARAM_STRU       stOrigParam;
    VOS_UINT32                          ulRst;

    // 参数初始化
    clientId                            = 0;
    opId                                = 0;

    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    // 调用被测函数
    ulRst = MN_CALL_Orig(clientId, opId, &CallId, &stOrigParam);

    // 执行检查
    EXPECT_EQ(VOS_OK,ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}




class Test_MN_CALL_GetCallInfos: public ::testing::Test
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


TEST_F(Test_MN_CALL_GetCallInfos,Test_MN_CALL_GetCallInfos_001)
{
        // 参数定义
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        CallId;
    VOS_UINT32                          ulRst;

    // 参数初始化
    clientId                            = 0;
    opId                                = 0;
    CallId                             = 1;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(MN_CALL_SendAppRequest)
        .stubs()
        .with(eq((VOS_UINT32)MN_CALL_APP_GET_INFO_REQ), eq(clientId), eq(opId), eq(CallId), eq((MN_CALL_APP_REQ_PARM_UNION const*)VOS_NULL_PTR))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRst = MN_CALL_GetCallInfos(clientId, opId, CallId);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_MN_CALL_GetCallInfos,Test_MN_CALL_GetCallInfos_002)
{
        // 参数定义
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        pCallId;
    VOS_UINT32                          ulRst;

    // 参数初始化
    clientId                            = 0;
    opId                                = 0;
    pCallId                             = 1;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(MN_CALL_SendAppRequest)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRst = MN_CALL_GetCallInfos(clientId, opId, pCallId);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


class Test_MN_FillAppReqMsgHeader: public ::testing::Test
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


TEST_F(Test_MN_FillAppReqMsgHeader, Test_MN_FillAppReqMsgHeader_001)
{
	MN_APP_REQ_MSG_STRU                 *pMsg;
    MN_CLIENT_ID_T                      enClientId;
    MN_OPERATION_ID_T                   OpId;
    VOS_UINT16                          usMsgType;
    VOS_UINT32                          ulReceiverPid;
	AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
  
	enClientId = AT_CLIENT_TAB_APP_INDEX;
    pstAtClientCtx = AT_GetClientCtxAddr(enClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

	pMsg = (MN_APP_REQ_MSG_STRU*)malloc(sizeof(MN_APP_REQ_MSG_STRU));
	OpId = 1;
    usMsgType = 1;
    ulReceiverPid = I0_WUEPS_PID_MMA;

	MN_FillAppReqMsgHeader(pMsg, enClientId, OpId, usMsgType, ulReceiverPid);

	EXPECT_EQ(pMsg->clientId, enClientId);
	EXPECT_EQ(pMsg->opId, OpId);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
	EXPECT_EQ(pMsg->ulReceiverPid, I1_WUEPS_PID_MMA);
#endif
#else
    EXPECT_EQ(pMsg->ulReceiverPid, I0_WUEPS_PID_MMA);
#endif
	EXPECT_EQ(pMsg->usMsgName, usMsgType);

	//检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if 0
#if (NAS_FEATURE_ALS == FEATURE_ON)

TEST(Test_MN_CALL_QryAlsLineNo,获取当前使用的线路号使用的是线路号1的处理)
{

    MOCKER(MN_CALL_GetAlsLineInfo)
        .will(returnValue(MN_CALL_ALS_LINE_NO_1));

    EXPECT_EQ(MN_CALL_QryAlsLineNo(),MN_CALL_ALS_LINE_NO_1);

}


TEST(Test_MN_CALL_SetAlsLineNo,根据设置的线路号更新NV和当前使用的线路号设置的线路号不在取值范围之内的处理)
{
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;

    enAlsLine = MN_CALL_ALS_LINE_NO_MAX;

    EXPECT_EQ(MN_CALL_SetAlsLineNo(enAlsLine),MN_ERR_INVALIDPARM);

}


TEST(Test_MN_CALL_SetAlsLineNo,根据设置的线路号更新NV和当前使用的线路号设置的线路号为2更新成功的处理)
{
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;

    enAlsLine = MN_CALL_ALS_LINE_NO_2;

    MOCKER(MN_CALL_UpdateAlsLineInfo)
        .will(returnValue((VOS_UINT32)VOS_OK));

    EXPECT_EQ(MN_CALL_SetAlsLineNo(enAlsLine),MN_ERR_NO_ERROR);

}


TEST(Test_MN_CALL_SetAlsLineNo,根据设置的线路号更新NV和当前使用的线路号设置的线路号为2更新失败的处理)
{
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;

    enAlsLine = MN_CALL_ALS_LINE_NO_2;

    MOCKER(MN_CALL_UpdateAlsLineInfo)
        .will(returnValue((VOS_UINT32)VOS_ERR));

    EXPECT_EQ(MN_CALL_SetAlsLineNo(enAlsLine),MN_ERR_UNSPECIFIED);

}
#endif


TEST(Test_MN_CALL_CheckUus1ParmValid,输入指针为空时直接返回出错)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;

    enSetType = MN_CALL_SET_UUS1_ACT;
    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_CheckUus1ParmValid(enSetType,VOS_NULL_PTR));
}


TEST(Test_MN_CALL_CheckUus1ParmValid,消息类型为PROGRESS返回出错)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_ACT;
    stUus1Info.enMsgType = MN_CALL_UUS1_MSG_PROGRESS;

    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_CheckUus1ParmValid(enSetType,&stUus1Info));

}



TEST(Test_MN_CALL_CheckUus1ParmValid,激活UUS1时_UUIE首字节非法返回出错)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_ACT;
    stUus1Info.enMsgType = MN_CALL_UUS1_MSG_RELEASE_COMPLETE;
    stUus1Info.aucUuie[MN_CALL_IEI_POS] = 0x00;

    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_CheckUus1ParmValid(enSetType,&stUus1Info));
}


TEST(Test_MN_CALL_CheckUus1ParmValid,去激活ANY消息的UUS1返回成功)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_DEACT;
    stUus1Info.enMsgType = MN_CALL_UUS1_MSG_ANY;

    ASSERT_EQ(MN_ERR_NO_ERROR,MN_CALL_CheckUus1ParmValid(enSetType,&stUus1Info));
}


TEST(Test_MN_CALL_SetUus1Info,输入参数非法时直接返回出错)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_ACT;

    MOCKER(MN_CALL_CheckUus1ParmValid)
        .will(returnValue(MN_ERR_INVALIDPARM));

    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_SetUus1Info(enSetType,&stUus1Info));
}



TEST(Test_MN_CALL_SetUus1Info,更新CC内存的UUS1信息成功返回成功)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_ACT;

    MOCKER(MN_CALL_CheckUus1ParmValid)
        .will(returnValue(MN_ERR_NO_ERROR));

    MOCKER(MN_CALL_UpdateCcUus1Info)
        .will(returnValue(MN_ERR_NO_ERROR));

    ASSERT_EQ(MN_ERR_NO_ERROR,MN_CALL_SetUus1Info(enSetType,&stUus1Info));

}


TEST(Test_MN_CALL_QryUus1nfo,查询CC内存的UUS1信息失败返回查询失败)
{
    VOS_UINT32                          ulActNum;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    ulActNum = 0;

    MOCKER(MN_CALL_GetCcUus1Info)
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_QryUus1nfo(&ulActNum,&stUus1Info));
}


TEST(Test_MN_CALL_QryUus1nfo,查询CC内存的UUS1信息成功返回查询成功)
{
    VOS_UINT32                          ulActNum;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    ulActNum = 0;

    MOCKER(MN_CALL_GetCcUus1Info)
        .will(returnValue((VOS_UINT32)VOS_OK));

    ASSERT_EQ(MN_ERR_NO_ERROR,MN_CALL_QryUus1nfo(&ulActNum,&stUus1Info));
}
#endif


class Test_MN_CALL_Sups: public ::testing::Test
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


TEST_F(Test_MN_CALL_Sups, Test_MN_CALL_Sups_001)
{
    //参数定义
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_SUPS_PARAM_STRU             stCallSupsParam;
    VOS_UINT32                          ulRslt;

    //参数初始化
    clientId = 0;
    opId     = 0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    //调用被测函数
    ulRslt = MN_CALL_Sups(clientId, opId, &stCallSupsParam);

    //执行检查
    ASSERT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_MN_CALL_SetAlsLineNo: public ::testing::Test
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


TEST_F(Test_MN_CALL_SetAlsLineNo, Test_MN_CALL_SetAlsLineNo_001)
{
    //参数定义
    TAF_UINT8                           ucIndex;
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex   = 0;
    enAlsLine = MN_CALL_ALS_LINE_NO_1;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    //调用被测函数
    ulRslt = MN_CALL_SetAlsLineNo(ucIndex, enAlsLine);

    //执行检查
    ASSERT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_MN_CALL_SendAppRequest: public ::testing::Test
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


TEST_F(Test_MN_CALL_SendAppRequest, Test_MN_CALL_SendAppRequest_001)
{
    //参数定义
    MN_CALL_APP_REQ_ENUM_UINT32         enReq;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        callId;
    VOS_UINT32                          ulRslt;

    //参数初始化
    enReq    = MN_CALL_APP_ORIG_REQ;
    callId   = 1;
    opId     = 0;
    clientId = 0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)VOS_NULL_PTR));

    //调用被测函数
    ulRslt = MN_CALL_SendAppRequest(enReq, clientId, opId, callId, VOS_NULL_PTR);

    //执行检查
    ASSERT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_MN_CALL_SendAppRequest, Test_MN_CALL_SendAppRequest_002)
{
    //参数定义
    MN_CALL_APP_REQ_ENUM_UINT32         enReq;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        callId;
    VOS_UINT32                          ulRslt;

    //参数初始化
    enReq    = MN_CALL_APP_ORIG_REQ;
    callId   = 1;
    opId     = 0;
    clientId = 0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulRslt = MN_CALL_SendAppRequest(enReq, clientId, opId, callId, VOS_NULL_PTR);

    //执行检查
    ASSERT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_MN_CALL_SendAppRequest, Test_MN_CALL_SendAppRequest_003)
{
	const MN_CALL_APP_REQ_PARM_UNION    *punParam;
    MN_CLIENT_ID_T                      enClientId;

    punParam = (MN_CALL_APP_REQ_PARM_UNION*)malloc(sizeof(MN_CALL_APP_REQ_PARM_UNION));
	enClientId = AT_CLIENT_TAB_APP_INDEX;

    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

	MOCKER(AT_GetDestPid)
		.expects(exactly(1))
        .with(eq(enClientId),eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)VOS_OK));

	MN_CALL_SendAppRequest(0,enClientId,0,0,punParam);

	//检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


class Test_MN_CALL_End: public ::testing::Test
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


TEST_F(Test_MN_CALL_End, Test_MN_CALL_End_001)
{
    //参数定义
    VOS_UINT32                          ulRelt;
    MN_CALL_END_PARAM_STRU             *pstEndParam = VOS_NULL_PTR;

    //参数初始化

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    //调用被测函数
    ulRelt = MN_CALL_End(TAF_AT_CLIENT, 0, 1, pstEndParam);

    //执行检查
    EXPECT_EQ(VOS_OK, ulRelt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


