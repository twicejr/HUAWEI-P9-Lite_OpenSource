#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "AppVcApi.h"
#include "vos.h"
#include "PsCommonDef.h"
#include "ATCmdProc.h"

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

#define    THIS_FILE_ID        PS_FILE_ID_VC_API_C

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

/*****************************************************************************
类名     : Test_APP_VC_SetVoiceVolume
功能描述 : APP_VC_SetVoiceVolume UT工程类
修改历史     :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_SetVoiceVolume: public ::testing::Test
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
测试用例编号      : Test_APP_VC_SetVoiceVolume_001
测试用例标题      : 将消息发送到modem0的PID
预期结果          : 函数返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoiceVolume,Test_APP_VC_SetVoiceVolume_001)
{
    MN_CLIENT_ID_T                      enClientId;
    MN_OPERATION_ID_T                   enOpId;
    VOS_UINT8                           ucVoiceVolume;

    enClientId = AT_CLIENT_TAB_APP_INDEX;
    enOpId = 1;
    ucVoiceVolume = 1;

    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(enClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    APP_VC_SetVoiceVolume(enClientId, enOpId,ucVoiceVolume);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_APP_VC_GetVoiceVolume
功能描述 : APP_VC_GetVoiceVolume UT工程类
修改历史     :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_GetVoiceVolume: public ::testing::Test
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
测试用例编号      : Test_APP_VC_GetVoiceVolume_001
测试用例标题      : 将消息发送到modem0的PID
预期结果          : 函数返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoiceVolume,Test_APP_VC_GetVoiceVolume_001)
{
    MN_CLIENT_ID_T                      enClientId;
    MN_OPERATION_ID_T                   enOpId;

    enClientId = AT_CLIENT_TAB_APP_INDEX;
    enOpId = 1;

    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(enClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    APP_VC_GetVoiceVolume(enClientId, enOpId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_APP_VC_SetVoiceMode
功能描述 : APP_VC_SetVoiceMode UT工程类
修改历史     :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_SetVoiceMode: public ::testing::Test
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
测试用例编号      : Test_APP_VC_SetVoiceMode_001
测试用例标题      : 将消息发送到modem0的PID
预期结果          : 函数返回VOS_OK
修改历史          :
1.日   期  : 2012-12-26
  作   者  : l00227485
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoiceMode,Test_APP_VC_SetVoiceMode_001)
{
    MN_CLIENT_ID_T                      enClientId;
    MN_OPERATION_ID_T                   enOpId;
    VOS_UINT8                           ucVoiceMode;

    enClientId = AT_CLIENT_ID_APP;
    enOpId = 1;
    ucVoiceMode = 1;

    APP_VC_SetVoiceMode(enClientId, enOpId, ucVoiceMode, I0_WUEPS_PID_VC);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_APP_VC_SetVoicePort
功能描述 : APP_VC_SetVoicePort函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : f00179208
修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_SetVoicePort: public ::testing::Test
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
测试用例编号      : Test_APP_VC_SetVoicePort_001
测试用例标题      : 内存分配失败
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoicePort,Test_APP_VC_SetVoicePort_001)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort;

    // 参数初始化
    ClientId                            = 0;
    OpId                                = 0;
    ucVoicePort                         = 1;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)0));

    // 调用被测函数
    ulRst = APP_VC_SetVoicePort(ClientId, OpId, ucVoicePort);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_APP_VC_SetVoicePort_002
测试用例标题      : 发送消息到modem0的PID失败
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoicePort,Test_APP_VC_SetVoicePort_002)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort;

    // 参数初始化
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    ucVoicePort                         = 1;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRst = APP_VC_SetVoicePort(ClientId, OpId, ucVoicePort);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_APP_VC_SetVoicePort_003
测试用例标题      : 发送消息到modem0的PID成功
预期结果          : 返回VOS_OK
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoicePort,Test_APP_VC_SetVoicePort_003)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort;

    // 参数初始化
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    ucVoicePort                         = 1;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRst = APP_VC_SetVoicePort(ClientId, OpId, ucVoicePort);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_APP_VC_GetVoiceMode
功能描述 : APP_VC_GetVoiceMode函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : f00179208
修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_GetVoiceMode: public ::testing::Test
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
测试用例编号      : Test_APP_VC_GetVoiceMode_001
测试用例标题      : 内存分配失败
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoiceMode,Test_APP_VC_GetVoiceMode_001)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // 参数初始化
    ClientId                            = 0;
    OpId                                = 0;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)0));

    // 调用被测函数
    ulRst = APP_VC_GetVoiceMode(ClientId, OpId);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_APP_VC_GetVoiceMode_002
测试用例标题      : 发送消息到modem0的PID失败
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoiceMode,Test_APP_VC_GetVoiceMode_002)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // 参数初始化
    ClientId                            =AT_CLIENT_ID_APP;
    OpId                                = 0;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRst = APP_VC_GetVoiceMode(ClientId, OpId);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_APP_VC_GetVoiceMode_003
测试用例标题      : 发送消息到modem0的PID成功
预期结果          : 返回VOS_OK
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoiceMode,Test_APP_VC_GetVoiceMode_003)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // 参数初始化
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRst = APP_VC_GetVoiceMode(ClientId, OpId);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_APP_VC_GetVoicePort
功能描述 : APP_VC_GetVoicePort函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : f00179208
修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_GetVoicePort: public ::testing::Test
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
测试用例编号      : Test_APP_VC_GetVoicePort_001
测试用例标题      : 内存分配失败
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoicePort,Test_APP_VC_GetVoicePort_001)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // 参数初始化
    ClientId                            = 0;
    OpId                                = 0;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)0));

    // 调用被测函数
    ulRst = APP_VC_GetVoicePort(ClientId, OpId);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_APP_VC_GetVoicePort_002
测试用例标题      : 发送消息到modem0的PID失败
预期结果          : 返回VOS_ERR
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoicePort,Test_APP_VC_GetVoicePort_002)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // 参数初始化
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRst = APP_VC_GetVoicePort(ClientId, OpId);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_APP_VC_GetVoicePort_003
测试用例标题      : 发送消息到modem0的PID成功
预期结果          : 返回VOS_OK
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoicePort,Test_APP_VC_GetVoicePort_003)
{
    // 参数定义
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // 参数初始化
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRst = APP_VC_GetVoicePort(ClientId, OpId);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRst);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*****************************************************************************
类名     : Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode
功能描述 : APP_VC_AppVcVoiceMode2VcPhyVoiceMode函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : f00179208
修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode: public ::testing::Test
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
测试用例编号      : Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode_001
测试用例标题      : 枚举各种语音模式，转换正确
预期结果          : 返回对应的枚举
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode,Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode_001)
{
    // 参数定义

    // 输入参数：
    ASSERT_EQ(VC_PHY_DEVICE_MODE_PCVOICE,       APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_PCVOICE));
    ASSERT_EQ(VC_PHY_DEVICE_MODE_EARPHONE,      APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_EARPHONE));
    ASSERT_EQ(VC_PHY_DEVICE_MODE_HANDSET,       APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_HANDSET));
    ASSERT_EQ(VC_PHY_DEVICE_MODE_HANDS_FREE,    APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_HANDS_FREE));
    ASSERT_EQ(VC_PHY_DEVICE_MODE_BUTT,          APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_BUTT));

}

/*****************************************************************************
类名     : Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode
功能描述 : APP_VC_VcPhyVoiceMode2AppVcVoiceMode函数的UT测试类
修改历史 :
1.日   期  : 2011-10-13
作   者  : f00179208
修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode: public ::testing::Test
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
测试用例编号      : Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode_001
测试用例标题      : 枚举各种语音模式，转换正确
预期结果          : 返回对应的枚举
修改历史     :
1.日   期  : 2011-10-13
  作   者  : f00179208
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode,Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode_001)
{
    // 参数定义

    // 输入参数：
    ASSERT_EQ(APP_VC_VOICE_MODE_PCVOICE,       APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_PCVOICE));
    ASSERT_EQ(APP_VC_VOICE_MODE_EARPHONE,      APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_EARPHONE));
    ASSERT_EQ(APP_VC_VOICE_MODE_HANDSET,       APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_HANDSET));
    ASSERT_EQ(APP_VC_VOICE_MODE_HANDS_FREE,    APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_HANDS_FREE));
    ASSERT_EQ(APP_VC_VOICE_MODE_BUTT,          APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_BLUETOOTH));

}

/*****************************************************************************
类名     : Test_APP_VC_GetMuteStatus
功能描述 : Test_APP_VC_GetMuteStatus UT工程类
修改历史 :
1.日   期  : 2013-01-07
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_GetMuteStatus: public ::testing::Test
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
测试用例编号      : Test_APP_VC_GetMuteStatus_001
测试用例标题      : 将消息头发送到modem0的PID
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-01-07
  作   者  : z00220246
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetMuteStatus, Test_APP_VC_GetMuteStatus_001)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    usClientId = AT_CLIENT_TAB_APP_INDEX;
    ucOpId = 1;
    pstAtClientCtx = AT_GetClientCtxAddr(usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;


    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(usClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    EXPECT_EQ(VOS_OK, APP_VC_GetMuteStatus(usClientId, ucOpId));
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_APP_VC_SetMuteStatus
功能描述 : Test_APP_VC_SetMuteStatus UT工程类
修改历史 :
1.日   期  : 2013-01-07
  作   者  : z00220246
  修改内容 : 新生成类
*****************************************************************************/
class Test_APP_VC_SetMuteStatus: public ::testing::Test
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
测试用例编号      : Test_APP_VC_SetMuteStatus_001
测试用例标题      : 将消息头发送到modem0的PID
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-01-07
  作   者  : z00220246
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetMuteStatus, Test_APP_VC_SetMuteStatus_001)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    APP_VC_MUTE_STATUS_ENUM_UINT8       enMuteStatus;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    usClientId = AT_CLIENT_TAB_APP_INDEX;
    ucOpId = 1;
    enMuteStatus = 1;
    pstAtClientCtx = AT_GetClientCtxAddr(usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(usClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    EXPECT_EQ(VOS_OK, APP_VC_SetMuteStatus(usClientId, ucOpId,enMuteStatus));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

