#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCmdCallProc.h"



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



#if (FEATURE_ON == FEATURE_ECALL)


class Test_AT_SetCecallPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();
		
		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_001)
{
    char *pucCmdString                                      = "AT+CECALL=0";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CECALL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_002)
{
    char *pucCmdString                                      = "AT+CECALL=1";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CECALL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_003)
{
    char *pucCmdString                                      = "AT+CECALL=2";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CECALL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_004)
{
    char *pucCmdString                                      = "AT+CECALL=3";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CECALL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_005)
{
    char *pucCmdString                                      = "AT+CECALL=";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    At_PidInit(VOS_IP_INITIAL);

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/

    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_006)
{
    char *pucCmdString                                      = "AT+CECALL=,";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/

    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_007)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    gucAtParaIndex                      = 1;
    gastAtParaList[0].ulParaValue       = 4;

    /* 调用被测函数 */
    ulRst = AT_SetCecallPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_008)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    gucAtParaIndex                      = 1;
    gastAtParaList[0].ulParaValue       = 1;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = AT_SetCecallPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


class Test_AT_SetEclstartPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_001)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=0,0,\"13911110008\"";
//
//    /* 初始化变量 */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* 调用消息入口函数 */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* 结果验证*/
//    EXPECT_EQ(AT_CMD_ECLSTART_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* 检查调用时, 需要在用例结束位置加上这句 */
//   GlobalMockObject::verify();
//}


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_002)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=0,1,\"112\"";
//
//    /* 初始化变量 */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* 调用消息入口函数 */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* 结果验证*/
//    EXPECT_EQ(AT_CMD_ECLSTART_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* 检查调用时, 需要在用例结束位置加上这句 */
//   GlobalMockObject::verify();
//}


TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_003)
{
    char *pucCmdString                                      = "AT^ECLSTART=1,0";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_ECLSTART_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_004)
{
    char *pucCmdString                                      = "AT^ECLSTART=1,1";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_ECLSTART_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_005)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=,1,\"112\"";
//
//    /* 初始化变量 */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* 函数打桩 */
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .times(0);
//
//    /* 调用消息入口函数 */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* 结果验证*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* 检查调用时, 需要在用例结束位置加上这句 */
//   GlobalMockObject::verify();
//}


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_006)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=1,,\"112\"";
//
//    /* 初始化变量 */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* 函数打桩 */
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .times(0);
//
//    /* 调用消息入口函数 */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* 结果验证*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* 检查调用时, 需要在用例结束位置加上这句 */
//   GlobalMockObject::verify();
//}


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_007)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=1,1,\"112\",1";
//
//    /* 初始化变量 */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* 函数打桩 */
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .times(0);
//
//    /* 调用消息入口函数 */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* 结果验证*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* 检查调用时, 需要在用例结束位置加上这句 */
//   GlobalMockObject::verify();
//}


TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_008)
{
    char *pucCmdString                                      = "AT^ECLSTART=1,1,";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 函数打桩 */

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_009)
//{
//    char *pucCmdString = "AT^ECLSTART=1,0,\"1502683289923456789\"";
//
//    /* 初始化变量 */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* 函数打桩 */
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .times(0);
//
//    /* 调用消息入口函数 */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* 结果验证*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* 检查调用时, 需要在用例结束位置加上这句 */
//   GlobalMockObject::verify();
//}


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_010)
//{
//    char *pucCmdString = "AT^ECLSTART=1,0,\"&15026832899\"";
//
//    /* 初始化变量 */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* 函数打桩 */
//    MOCKER(AT_SetCsCallErrCause)
//        .times(1);
//
//    /* 调用消息入口函数 */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* 结果验证*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* 检查调用时, 需要在用例结束位置加上这句 */
//   GlobalMockObject::verify();
//}


TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_011)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    PS_MEM_SET(gastAtParaList, 0, sizeof(gastAtParaList));

    gucAtParaIndex                      = 2;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = AT_SetEclstartPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


class Test_AT_SetEclstopPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;


		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));
		
		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_SetEclstopPara, Test_AT_SetEclstopPara_001)
{
    char *pucCmdString                                 = "AT^ECLSTOP";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_ECLSTOP_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclstopPara, Test_AT_SetEclstopPara_002)
{
    char *pucCmdString                                 = "AT^ECLSTOP=";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclstopPara, Test_AT_SetEclstopPara_003)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_CMD_NO_PARA;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = AT_SetEclstopPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


class Test_AT_SetEclcfgPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_001)
{
    char *pucCmdString                                      = "AT^ECLCFG=0";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_ECLCFG_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_002)
{
    char *pucCmdString                                      = "AT^ECLCFG=0,1";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_ECLCFG_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_003)
{
    char *pucCmdString                                      = "AT^ECLCFG=";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_004)
{
    char *pucCmdString                                      = "AT^ECLCFG=0,0,";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_005)
{
    char *pucCmdString                                      = "AT^ECLCFG=0,";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_006)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */
    gucAtParaIndex                      = 2;
    gastAtParaList[0].ulParaValue       = 0;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = AT_SetEclcfgPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();

}
#if 0

class Test_AT_SetEclmsdPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_001)
{
    char *pucCmdString = "AT^ECLMSD=\"010108414141414141414141414131313131313188\
0000000100000001000000010100010001000100010600010db885a308d313198a2e037073340000\
00000000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000000000000000\"";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_ECLMSD_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_002)
{
    char *pucCmdString                                      = "AT^ECLMSD=";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_003)
{
    char *pucCmdString                                      = "AT^ECLMSD=\"00\"";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_004)
{
    char *pucCmdString = "AT^ECLMSD=\"&&0108414141414141414141414131313131313188\
0000000100000001000000010100010001000100010600010db885a308d313198a2e037073340000\
00000000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000000000000000\"";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_005)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;
    char *pucMsdString = "010108414141414141414141414131313131313188000000010000\
0001000000010100010001000100010600010db885a308d313198a2e037073340000000000000000\
00000000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000";

    /* 变量初始化 */
    gucAtParaIndex                      = 1;
    PS_MEM_CPY(gastAtParaList[0].aucPara, pucMsdString, strlen(pucMsdString)+1);
    gastAtParaList[0].usParaLen         = APP_VC_MSD_DATA_LEN * 2;

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .will(returnValue(TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = AT_SetEclmsdPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();

}
#endif


class Test_AT_QryCecallPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_QryCecallPara, Test_AT_QryCecallPara_001)
{
    char *pucCmdString = "AT+CECALL?";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_CECALL_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_QryCecallPara, Test_AT_QryCecallPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = AT_QryCecallPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();

}


class Test_AT_QryEclcfgPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_QryEclcfgPara, Test_AT_QryEclcfgPara_001)
{
    char *pucCmdString = "AT^ECLCFG?";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_ECLCFG_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_QryEclcfgPara, Test_AT_QryEclcfgPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
        .defaults()
		.will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = AT_QryEclcfgPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();

}


class Test_AT_QryEclmsdPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_QryEclmsdPara, Test_AT_QryEclmsdPara_001)
{
    char *pucCmdString = "AT^ECLMSD?";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 结果验证*/
    EXPECT_EQ(AT_CMD_ECLMSD_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_QryEclmsdPara, Test_AT_QryEclmsdPara_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 变量初始化 */

    /* 函数打桩 */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
		.will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* 调用被测函数 */
    ulRst = AT_QryEclmsdPara(ucIndex);

    /* 结果验证 */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();

}



class Test_AT_TestEclstartPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_TestEclstartPara, Test_AT_TestEclstartPara_001)
{
    char *pucCmdString = "AT^ECLSTART=?";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


class Test_AT_TestEclmsdPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

		UT_STUB_INIT();

		MOCKER(VOS_SmBCreate)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(NV_ReadEx)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(NV_GetLength)
			.defaults()
			.will(returnValue((VOS_UINT32)NV_OK));

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_TestEclmsdPara, Test_AT_TestEclmsdPara_001)
{
    char *pucCmdString = "AT^ECLMSD=?";

    /* 初始化变量 */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* 调用消息入口函数 */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* 检查调用时, 需要在用例结束位置加上这句 */
   GlobalMockObject::verify();
}


#endif








