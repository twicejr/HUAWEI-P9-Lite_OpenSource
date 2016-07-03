#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtEventReport.h"
#include "uttest_AtSetParaCmd.h"
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

    AT_PAR_CMD_ELEMENT_STRU             gstCpbrCmdInfo = {AT_CMD_CPBR2,
        At_SetCpbr2Para,     AT_SET_PARA_TIME,   TAF_NULL_PTR,    AT_NOT_SET_TIME,   AT_TestCpbrPara, AT_SET_PARA_TIME,
        VOS_NULL_PTR ,       AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (TAF_UINT8*)"+CPBR",    (TAF_UINT8*)"(1-65535),(1-65535)"};

    AT_PAR_CMD_ELEMENT_STRU             gstCpmsCmdInfo = {AT_CMD_CPMS,
        At_SetCpmsPara,     AT_SET_PARA_TIME, At_QryCpmsPara,   AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,       AT_NOT_SET_TIME,
        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};

    AT_PAR_CMD_ELEMENT_STRU             gstAppDmVerCmdInfo = {AT_CMD_APPDMVER,
        VOS_NULL_PTR,           AT_NOT_SET_TIME,  AT_QryAppdmverPara,       AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,       AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"^APPDMVER",    VOS_NULL_PTR};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


class Test_At_SendSmRspProc: public ::testing::Test
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


TEST_F(Test_At_SendSmRspProc, Test_At_SendSmRspProc_001)
{
    // 变量声明
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrorCode;

    /*参数初始化*/
    PS_MEM_SET(&stEvent, 0, sizeof(stEvent));
    stEvent.u.stSubmitRptInfo.enErrorCode = (TAF_MSG_ERROR_ENUM_UINT32)TAF_MSG_ERROR_RP_CAUSE_NETWORK_OUT_OF_ORDER;
    ucIndex = 0;

    /* 初始化全局变量;*/
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGS_PDU_SET;

    // MOCKER操作;
    ulErrorCode = AT_CMS_NETWORK_OUT_OF_ORDER;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulErrorCode));

    /* 调用被测函数 */
    At_SendSmRspProc(ucIndex, &stEvent);

    // 执行检查

    GlobalMockObject::verify();

}


TEST_F(Test_At_SendSmRspProc, Test_At_SendSmRspProc_002)
{
    // 变量声明
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrorCode;

    /*参数初始化*/
    PS_MEM_SET(&stEvent, 0, sizeof(stEvent));
    stEvent.u.stSubmitRptInfo.enErrorCode = TAF_MSG_ERROR_ERROR_BUTT;
    ucIndex = 0;

    /* 初始化全局变量;*/
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGS_PDU_SET;

    // MOCKER操作;
    ulErrorCode = AT_CMS_UNKNOWN_ERROR;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulErrorCode));

    /* 调用被测函数 */
    At_SendSmRspProc(ucIndex, &stEvent);

    // 执行检查

    GlobalMockObject::verify();

}





class Test_AT_RcvDrvAgentAppdmverQryRsp: public ::testing::Test
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


TEST_F(Test_AT_RcvDrvAgentAppdmverQryRsp, Test_AT_RcvDrvAgentAppdmverQryRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_VOID                           *pMsg;               /* 作为被测函数的入参 */
    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;
    DRV_AGENT_APPDMVER_QRY_CNF_STRU    *pstEvent;
    VOS_UINT16                          usLen;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                        + sizeof(DRV_AGENT_APPDMVER_QRY_CNF_STRU)
                                        - sizeof(pstDrvAgentMsg->aucContent);
    pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)malloc(usLen);
    PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

    pMsg                                = (VOS_VOID *)pstDrvAgentMsg;
    pstEvent                            = (DRV_AGENT_APPDMVER_QRY_CNF_STRU *)pstDrvAgentMsg->aucContent;
    pcLogStr                             = "AT_RcvDrvAgentAppdmverQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), any())
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .stubs();

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAppdmverQryRsp(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();

    // 释放申请的内存
    free(pstDrvAgentMsg);
}


TEST_F(Test_AT_RcvDrvAgentAppdmverQryRsp, Test_AT_RcvDrvAgentAppdmverQryRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_VOID                           *pMsg;               /* 作为被测函数的入参 */
    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;
    DRV_AGENT_APPDMVER_QRY_CNF_STRU    *pstEvent;
    VOS_UINT16                          usLen;
    VOS_CHAR                           *pLogStr;

    //参数初始化
    ucIndex                             = 0;

    usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                        + sizeof(DRV_AGENT_APPDMVER_QRY_CNF_STRU)
                                        - sizeof(pstDrvAgentMsg->aucContent);
    pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)malloc(usLen);
    PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

    pMsg                                = (VOS_VOID *)pstDrvAgentMsg;
    pstEvent                            = (DRV_AGENT_APPDMVER_QRY_CNF_STRU *)pstDrvAgentMsg->aucContent;
    pLogStr                             = "AT_RcvDrvAgentAppdmverQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSINFO_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAppdmverQryRsp(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();

    // 释放申请的内存
    free(pstDrvAgentMsg);
}


TEST_F(Test_AT_RcvDrvAgentAppdmverQryRsp, Test_AT_RcvDrvAgentAppdmverQryRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_VOID                           *pMsg;               /* 作为被测函数的入参 */
    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;
    DRV_AGENT_APPDMVER_QRY_CNF_STRU    *pstEvent;
    VOS_UINT16                          usLen;

    //参数初始化
    ucIndex                             = 0;

    usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                        + sizeof(DRV_AGENT_APPDMVER_QRY_CNF_STRU)
                                        - sizeof(pstDrvAgentMsg->aucContent);
    pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)malloc(usLen);
    PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

    pMsg                                = (VOS_VOID *)pstDrvAgentMsg;
    pstEvent                            = (DRV_AGENT_APPDMVER_QRY_CNF_STRU *)pstDrvAgentMsg->aucContent;
    pstEvent->enResult                  = DRV_AGENT_APPDMVER_QRY_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APPDMVER_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAppdmverQryRsp(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ((VOS_UINT8)AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ((MN_OPERATION_ID_T)0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0,gstAtSendData.usBufLen);

    GlobalMockObject::verify();

    // 释放申请的内存
    free(pstDrvAgentMsg);
}


TEST_F(Test_AT_RcvDrvAgentAppdmverQryRsp, Test_AT_RcvDrvAgentAppdmverQryRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_VOID                           *pMsg;               /* 作为被测函数的入参 */
    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;
    DRV_AGENT_APPDMVER_QRY_CNF_STRU    *pstEvent;
    VOS_UINT16                          usLen;
    VOS_CHAR                           *pcPdmver;
    VOS_CHAR                           *pcExpactedStr;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_APPDMVER,         VOS_NULL_PTR,
                                                     AT_NOT_SET_TIME,         AT_QryAppdmverPara,
                                                     AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                     AT_RRETURN_CODE_BUTT,    CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^APPDMVER", VOS_NULL_PTR};

    //参数初始化
    ucIndex                             = 0;

    usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                        + sizeof(DRV_AGENT_APPDMVER_QRY_CNF_STRU)
                                        - sizeof(pstDrvAgentMsg->aucContent);
    pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)malloc(usLen);
    PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

    pcPdmver                            = "001";
    pcExpactedStr                       = "^APPDMVER:001";

    pMsg                                = (VOS_VOID *)pstDrvAgentMsg;
    pstEvent                            = (DRV_AGENT_APPDMVER_QRY_CNF_STRU *)pstDrvAgentMsg->aucContent;
    pstEvent->enResult                  = DRV_AGENT_APPDMVER_QRY_NO_ERROR;
    PS_MEM_CPY(pstEvent->acPdmver, pcPdmver, VOS_StrLen(pcPdmver));

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APPDMVER_READ;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAppdmverQryRsp(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(13, gstAtSendData.usBufLen);
    // EXPECT_EQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();

    // 释放申请的内存
    free(pstDrvAgentMsg);
}



class Test_AT_RcvDrvAgentDloadInfoQryRsp: public ::testing::Test
{
public:

    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;     /* 接受消息结构 */
    DRV_AGENT_DLOADINFO_QRY_CNF_STRU   *pstEvent;           /* 发送消息结构 */
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLen;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        /* 生成输入消息 */
        usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                            + sizeof(DRV_AGENT_DLOADINFO_QRY_CNF_STRU)
                                            - sizeof(pstDrvAgentMsg->aucContent);
        pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
        PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

        if (VOS_NULL_PTR == pstDrvAgentMsg)
        {
            return;
        }

        pstEvent                            = (DRV_AGENT_DLOADINFO_QRY_CNF_STRU *)(pstDrvAgentMsg->aucContent);
    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstDrvAgentMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDrvAgentMsg);
        }
    }
};


TEST_F(Test_AT_RcvDrvAgentDloadInfoQryRsp, Test_AT_RcvDrvAgentDloadInfoQryRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr                            = "AT_RcvDrvAgentDloadInfoQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentDloadInfoQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentDloadInfoQryRsp, Test_AT_RcvDrvAgentDloadInfoQryRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq((VOS_UINT16)pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentDloadInfoQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentDloadInfoQryRsp, Test_AT_RcvDrvAgentDloadInfoQryRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_DLOADINFO_QRY_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_DLOADINFO_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq((VOS_UINT16)pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentDloadInfoQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ((VOS_UINT8)AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentDloadInfoQryRsp, Test_AT_RcvDrvAgentDloadInfoQryRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_DLOADINFO_QRY_NO_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_DLOADINFO_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentDloadInfoQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);

    GlobalMockObject::verify();
}



class Test_AT_RcvDrvAgentAuthorityVerQryRsp: public ::testing::Test
{
public:

    DRV_AGENT_MSG_STRU                  *pstDrvAgentMsg;     /* 接受消息结构 */
    DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU *pstEvent;           /* 发送消息结构 */
    VOS_UINT8                            ucIndex;
    VOS_UINT16                           usLen;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        /* 生成输入消息 */
        usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                            + sizeof(DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU)
                                            - sizeof(pstDrvAgentMsg->aucContent);
        pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
        PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

        if (VOS_NULL_PTR == pstDrvAgentMsg)
        {
            return;
        }

        pstEvent                            = (DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU *)(pstDrvAgentMsg->aucContent);
    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstDrvAgentMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDrvAgentMsg);
        }
    }
};


TEST_F(Test_AT_RcvDrvAgentAuthorityVerQryRsp, Test_AT_RcvDrvAgentAuthorityVerQryRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr                            = "AT_RcvDrvAgentAuthorityVerQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthorityVerQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthorityVerQryRsp, Test_AT_RcvDrvAgentAuthorityVerQryRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthorityVerQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthorityVerQryRsp, Test_AT_RcvDrvAgentAuthorityVerQryRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_AUTHORITYVER_QRY_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_AUTHORITYVER_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthorityVerQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthorityVerQryRsp, Test_AT_RcvDrvAgentAuthorityVerQryRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_AUTHORITYVER_QRY_NO_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_AUTHORITYVER_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthorityVerQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);

    GlobalMockObject::verify();
}


class Test_AT_RcvDrvAgentAuthorityIdQryRsp: public ::testing::Test
{
public:

    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;     /* 接受消息结构 */
    DRV_AGENT_AUTHORITYID_QRY_CNF_STRU *pstEvent;           /* 发送消息结构 */
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLen;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        /* 生成输入消息 */
        usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                            + sizeof(DRV_AGENT_AUTHORITYID_QRY_CNF_STRU)
                                            - sizeof(pstDrvAgentMsg->aucContent);
        pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
        PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

        if (VOS_NULL_PTR == pstDrvAgentMsg)
        {
            return;
        }

        pstEvent                            = (DRV_AGENT_AUTHORITYID_QRY_CNF_STRU *)(pstDrvAgentMsg->aucContent);
    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstDrvAgentMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDrvAgentMsg);
        }
    }
};


TEST_F(Test_AT_RcvDrvAgentAuthorityIdQryRsp, Test_AT_RcvDrvAgentAuthorityIdQryRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr                            = "AT_RcvDrvAgentAuthorityIdQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthorityIdQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthorityIdQryRsp, Test_AT_RcvDrvAgentAuthorityIdQryRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthorityIdQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthorityIdQryRsp, Test_AT_RcvDrvAgentAuthorityIdQryRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_AUTHORITYID_QRY_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_AUTHORITYID_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthorityIdQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthorityIdQryRsp, Test_AT_RcvDrvAgentAuthorityIdQryRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_AUTHORITYID_QRY_NO_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_AUTHORITYID_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthorityIdQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);

    GlobalMockObject::verify();
}


class Test_AT_RcvDrvAgentGodloadSetRsp: public ::testing::Test
{
public:

    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;     /* 接受消息结构 */
    DRV_AGENT_GODLOAD_SET_CNF_STRU     *pstEvent;           /* 发送消息结构 */
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLen;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        /* 生成输入消息 */
        usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                            + sizeof(DRV_AGENT_GODLOAD_SET_CNF_STRU)
                                            - sizeof(pstDrvAgentMsg->aucContent);
        pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
        PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

        if (VOS_NULL_PTR == pstDrvAgentMsg)
        {
            return;
        }

        pstEvent                            = (DRV_AGENT_GODLOAD_SET_CNF_STRU *)(pstDrvAgentMsg->aucContent);
    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstDrvAgentMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDrvAgentMsg);
        }
    }
};


TEST_F(Test_AT_RcvDrvAgentGodloadSetRsp, Test_AT_RcvDrvAgentGodloadSetRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr                            = "AT_RcvDrvAgentGodloadSetRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentGodloadSetRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentGodloadSetRsp, Test_AT_RcvDrvAgentGodloadSetRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentGodloadSetRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentGodloadSetRsp, Test_AT_RcvDrvAgentGodloadSetRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_GODLOAD_SET_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_GODLOAD_SET;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue(VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentGodloadSetRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentGodloadSetRsp, Test_AT_RcvDrvAgentGodloadSetRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_GODLOAD_SET_NO_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_GODLOAD_SET;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentGodloadSetRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);

    GlobalMockObject::verify();
}


class Test_AT_RcvDrvAgentHwnatQryRsp: public ::testing::Test
{
public:

    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;     /* 接受消息结构 */
    DRV_AGENT_HWNATQRY_QRY_CNF_STRU    *pstEvent;           /* 发送消息结构 */
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLen;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        /* 生成输入消息 */
        usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                            + sizeof(DRV_AGENT_HWNATQRY_QRY_CNF_STRU)
                                            - sizeof(pstDrvAgentMsg->aucContent);
        pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
        PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

        if (VOS_NULL_PTR == pstDrvAgentMsg)
        {
            return;
        }

        pstEvent                            = (DRV_AGENT_HWNATQRY_QRY_CNF_STRU *)(pstDrvAgentMsg->aucContent);
    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstDrvAgentMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDrvAgentMsg);
        }
    }
};


TEST_F(Test_AT_RcvDrvAgentHwnatQryRsp, Test_AT_RcvDrvAgentHwnatQryRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr                            = "AT_RcvDrvAgentHwnatQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentHwnatQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentHwnatQryRsp, Test_AT_RcvDrvAgentHwnatQryRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentHwnatQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentHwnatQryRsp, Test_AT_RcvDrvAgentHwnatQryRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_HWNATQRY_QRY_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_HWNATQRY_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentHwnatQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}

#if 0

TEST_F(Test_AT_RcvDrvAgentHwnatQryRsp, Test_AT_RcvDrvAgentHwnatQryRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_HWNATQRY,       VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                     AT_QryHwnatQryPara,    AT_QRY_PARA_TIME,
                                                     VOS_NULL_PTR,          AT_NOT_SET_TIME,
                                                     AT_RRETURN_CODE_BUTT,  CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^HWNATQRY",    VOS_NULL_PTR};

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_HWNATQRY_QRY_NO_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_HWNATQRY_READ;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP(&ucIndex))
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq(ucIndex), any());

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(AT_OK));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentHwnatQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);

    GlobalMockObject::verify();
}
#endif

class Test_AT_RcvDrvAgentFlashInfoQryRsp: public ::testing::Test
{
public:

    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;     /* 接受消息结构 */
    DRV_AGENT_FLASHINFO_QRY_CNF_STRU   *pstEvent;           /* 发送消息结构 */
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLen;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        /* 生成输入消息 */
        usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                            + sizeof(DRV_AGENT_FLASHINFO_QRY_CNF_STRU)
                                            - sizeof(pstDrvAgentMsg->aucContent);
        pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
        PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

        if (VOS_NULL_PTR == pstDrvAgentMsg)
        {
            return;
        }

        pstEvent                            = (DRV_AGENT_FLASHINFO_QRY_CNF_STRU *)(pstDrvAgentMsg->aucContent);
    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstDrvAgentMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDrvAgentMsg);
        }
    }
};


TEST_F(Test_AT_RcvDrvAgentFlashInfoQryRsp, Test_AT_RcvDrvAgentFlashInfoQryRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr                            = "AT_RcvDrvAgentFlashInfoQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentFlashInfoQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentFlashInfoQryRsp, Test_AT_RcvDrvAgentFlashInfoQryRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentFlashInfoQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentFlashInfoQryRsp, Test_AT_RcvDrvAgentFlashInfoQryRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_FLASHINFO_QRY_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_FLASHINFO_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentFlashInfoQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentFlashInfoQryRsp, Test_AT_RcvDrvAgentFlashInfoQryRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_FLASHINFO_QRY_NO_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_FLASHINFO_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentFlashInfoQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);

    GlobalMockObject::verify();
}


class Test_AT_RcvDrvAgentAuthVerQryRsp: public ::testing::Test
{
public:

    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;     /* 接受消息结构 */
    DRV_AGENT_AUTHVER_QRY_CNF_STRU     *pstEvent;           /* 发送消息结构 */
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLen;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        /* 生成输入消息 */
        usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                            + sizeof(DRV_AGENT_AUTHVER_QRY_CNF_STRU)
                                            - sizeof(pstDrvAgentMsg->aucContent);
        pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
        PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

        if (VOS_NULL_PTR == pstDrvAgentMsg)
        {
            return;
        }

        pstEvent                            = (DRV_AGENT_AUTHVER_QRY_CNF_STRU *)(pstDrvAgentMsg->aucContent);
    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstDrvAgentMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDrvAgentMsg);
        }
    }
};


TEST_F(Test_AT_RcvDrvAgentAuthVerQryRsp, Test_AT_RcvDrvAgentAuthVerQryRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr                            = "AT_RcvDrvAgentAuthVerQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthVerQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthVerQryRsp, Test_AT_RcvDrvAgentAuthVerQryRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthVerQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthVerQryRsp, Test_AT_RcvDrvAgentAuthVerQryRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_AUTHVER_QRY_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_AUTHVER_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthVerQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentAuthVerQryRsp, Test_AT_RcvDrvAgentAuthVerQryRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_AUTHVER,            TAF_NULL_PTR, AT_NOT_SET_TIME,
                                                     AT_QryAuthverPara,         AT_QRY_PARA_TIME,
                                                     VOS_NULL_PTR,              AT_NOT_SET_TIME,
                                                     VOS_NULL_PTR,              AT_NOT_SET_TIME,
                                                     AT_RRETURN_CODE_BUTT,      CMD_TBL_PIN_IS_LOCKED,
                                                     (VOS_UINT8*)"^AUTHVER",    TAF_NULL_PTR};

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_AUTHVER_QRY_NO_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_AUTHVER_READ;
    g_stParseContext[0].pstCmdElement   = &stCmdInfo;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(pstEvent->stAtAppCtrl.usClientId), outBoundP((VOS_UINT8*)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));


    // 调用被测函数
    ulRet = AT_RcvDrvAgentAuthVerQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);

    GlobalMockObject::verify();
}


class Test_AT_RcvCdurQryRsp: public ::testing::Test
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


TEST_F(Test_AT_RcvCdurQryRsp, Test_AT_RcvCdurQryRsp_001)
{
    // 变量声明
    VOS_UINT8                            ucIndex;
    MN_CALL_INFO_STRU                    stCallMgmt;

    //参数初始化
    ucIndex = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PFVER_READ;

    // MOCKER操作;
    MOCKER(AT_StopRelTimer)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_RcvCdurQryRsp(ucIndex, MN_CALL_EVT_GET_CDUR_CNF, &stCallMgmt);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvCdurQryRsp, Test_AT_RcvCdurQryRsp_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                    stCallMgmt;
    VOS_UINT16                            usExpectdLen;
    VOS_CHAR                           *pcExpectedStr;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CDUR,
                                AT_SetCdurPara,         AT_NOT_SET_TIME,  VOS_NULL_PTR,              AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
                                VOS_NULL_PTR ,          AT_NOT_SET_TIME,
                                AT_RRETURN_CODE_BUTT,       CMD_TBL_LIMITED_NULL,
                                (VOS_UINT8*)"^CDUR",    (VOS_UINT8*)"(0-7)"};

    //参数初始化
    ucIndex                                    = 0;
    enEvent                                    = MN_CALL_EVT_GET_CDUR_CNF;
    pcExpectedStr                            = "^CDUR:1,10";
    usExpectdLen                            = VOS_StrLen(pcExpectedStr);
    stCallMgmt.ulCurCallTime                = 10;
    stCallMgmt.callId                       = 1;
    stCallMgmt.enCause                      = TAF_CS_CAUSE_SUCCESS;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt    = AT_CMD_CDUR_READ;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    // MOCKER操作;
    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_CsRspProc(ucIndex, enEvent, &stCallMgmt);

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(usExpectdLen, gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpectedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();

}


class Test_AT_RcvDrvAgentPfverQryRsp: public ::testing::Test
{
public:

    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsg;     /* 接受消息结构 */
    DRV_AGENT_PFVER_QRY_CNF_STRU       *pstEvent;           /* 发送消息结构 */
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLen;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        stCmdElement.ulCmdIndex     = AT_CMD_PFVER;
        stCmdElement.pfnSetProc     = At_SetPfverPara;
        stCmdElement.ulSetTimeOut   = AT_SET_PARA_TIME;
        stCmdElement.pfnQryProc     = TAF_NULL_PTR;
        stCmdElement.ulQryTimeOut   = AT_NOT_SET_TIME;
        stCmdElement.pfnTestProc    = VOS_NULL_PTR;
        stCmdElement.ulTestTimeOut  = AT_NOT_SET_TIME;
        stCmdElement.pfnAbortProc   = VOS_NULL_PTR;
        stCmdElement.ulAbortTimeOut = AT_NOT_SET_TIME;
        stCmdElement.ulParamErrCode = AT_CME_INCORRECT_PARAMETERS;
        stCmdElement.ulChkFlag      = CMD_TBL_PIN_IS_LOCKED;
        stCmdElement.pszCmdName     = (VOS_UINT8*)"^PFVER";
        stCmdElement.pszParam       = VOS_NULL_PTR;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

        /* 生成输入消息 */
        usLen                               = sizeof(DRV_AGENT_MSG_STRU)
                                            + sizeof(DRV_AGENT_PFVER_QRY_CNF_STRU)
                                            - sizeof(pstDrvAgentMsg->aucContent);
        pstDrvAgentMsg                      = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
        PS_MEM_SET(pstDrvAgentMsg, 0x00, usLen);

        if (VOS_NULL_PTR == pstDrvAgentMsg)
        {
            return;
        }

        pstEvent                            = (DRV_AGENT_PFVER_QRY_CNF_STRU *)(pstDrvAgentMsg->aucContent);
    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstDrvAgentMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDrvAgentMsg);
        }
    }
};


TEST_F(Test_AT_RcvDrvAgentPfverQryRsp, Test_AT_RcvDrvAgentPfverQryRsp_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcLogStr;

    //参数初始化
    pcLogStr                            = "AT_RcvDrvAgentPfverQryRsp: AT INDEX NOT FOUND!";

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentPfverQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentPfverQryRsp, Test_AT_RcvDrvAgentPfverQryRsp_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
		.with(eq((TAF_UINT16)pstEvent->stAtAppCtrl.usClientId), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentPfverQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentPfverQryRsp, Test_AT_RcvDrvAgentPfverQryRsp_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_PFVER_QRY_ERROR_GET_VERSION_TIME;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_PFVER_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
		.with(eq((TAF_UINT16)pstEvent->stAtAppCtrl.usClientId), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
		.will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentPfverQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentPfverQryRsp, Test_AT_RcvDrvAgentPfverQryRsp_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    pstEvent->enResult                  = DRV_AGENT_PFVER_QRY_NO_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_PFVER_READ;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq((TAF_UINT16)pstEvent->stAtAppCtrl.usClientId), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
		.will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRet = AT_RcvDrvAgentPfverQryRsp(pstDrvAgentMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);

    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsCallEvtPdpActivateCnf: public ::testing::Test
{
public:
    void SetUp()
	{
		MOCKER(VOS_SmP)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		MOCKER(VOS_SmV)
			.defaults()
			.will(returnValue((VOS_UINT32)VOS_OK));

		UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType       = TAF_PDP_IPV4V6;
    stCallEvt.stCtrl.usClientId         = AT_CLIENT_ID_NDIS;

    //相关全局变量初始化
    ucIndex                             = 0;
    gastAtClientTab[ucIndex].UserType   = AT_NDIS_USER;

#if (FEATURE_ON == FEATURE_NDIS)
    //MOCKER操作
    MOCKER(AT_FwSendClientMsg)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)PS_PID_APP_NDIS), eq((VOS_UINT32)ID_AT_NDIS_PDNINFO_CFG_REQ), any(), any())
		.will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));
    MOCKER(AT_NdisConfigIpv6Dns)
        .expects(exactly(1));
#endif

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    VOS_CHAR                           *pcPdpAddr = "192.168.1.100";

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.bitOpPdpAddr  = VOS_TRUE;
    memcpy(stCallEvt.stPdpAddr.aucIpv4Addr, pcPdpAddr, strlen(pcPdpAddr));

    //相关全局变量初始化
    ucIndex                             = 0;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_ORG_SET;

    //MOCKER操作
    MOCKER(AT_HsicPsRspEvtPdpActCnfProc)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_MODEM;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_HSIC1_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作

    MOCKER(At_SendResultData)
        .expects(exactly(1));


    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstModemPsCtx->astCallEntity[0].enIpv4State);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_MODEM;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_HSIC1_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = UDI_NCM_HSIC_NCM0_ID;

    //MOCKER操作

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    /* 给DIPC发消息 */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
		.will(returnValue((VOS_UINT32)0));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstModemPsCtx->astCallEntity[0].enIpv4State);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_005)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_WEBUI;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType       = TAF_PDP_IPV4V6;

    //相关全局变量初始化
    ucIndex                             = 0;
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_ORG_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_006)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;

    //相关全局变量初始化
    ucIndex                             = 0;
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_ORG_SET;

    //MOCKER操作
    MOCKER(AT_ProcAppPsRspEvtPdpActCnf)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_007)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_APP;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstModemPsCtx->astCallEntity[0].enIpv4State);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_008)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_APP;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;

    //MOCKER操作

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    /* 给RNIC发消息 */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
		.will(returnValue((VOS_UINT32)0));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg);
    EXPECT_EQ(AT_PDP_STATE_ACTED, pstModemPsCtx->astCallEntity[0].enIpv4State);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_009)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_PCUI;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作

    MOCKER(At_SendResultData)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_010)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_PPP;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_MODEM;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGANS_ANS_EXT_SET;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_CONNECT));

    MOCKER(Ppp_CreateRawDataPppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_011)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_PPP;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_MODEM;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGANS_ANS_EXT_SET;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_ERROR));

    MOCKER(Ppp_CreateRawDataPppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //MOCKER(OM_AppGreenChannel).stubs().will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_012)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_MODEM;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGANS_ANS_EXT_SET;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_CONNECT));

    MOCKER(Ppp_CreateRawDataPppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateCnf, Test_AT_RcvTafPsCallEvtPdpActivateCnf_013)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));
    stCallEvt.ucCid       = 1;
    stCallEvt.ucRabId     = 5;
    stCallEvt.stPdpAddr.enPdpType     = TAF_PDP_PPP;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_MODEM;

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_IP_CALL_SET;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_CONNECT));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateCnf(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtPdpActivateRej: public ::testing::Test
{
public:
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    void SetUp()
	{
		UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateRej, Test_AT_RcvTafPsCallEvtPdpActivateRej_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_ID_MODEM;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_MODEM;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].enCurrPdpType = TAF_PDP_IPV4;
    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = AT_CLIENT_TAB_MODEM_INDEX;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = AT_CLIENT_TAB_MODEM_INDEX;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType   = AT_HSIC4_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid    = 1;

    //MOCKER操作
    MOCKER(AT_CleanAtChdataCfg)
        .expects(exactly(1));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateRej, Test_AT_RcvTafPsCallEvtPdpActivateRej_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_ID_MODEM;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_MODEM;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_ORG_SET;

    //MOCKER操作
    MOCKER(AT_CleanAtChdataCfg)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateRej, Test_AT_RcvTafPsCallEvtPdpActivateRej_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU              stCallEvt;

    //参数初始化
    ucIndex                             = AT_CLIENT_ID_APP;
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    //相关全局变量初始化
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;

    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].enCurrPdpType = TAF_PDP_IPV4;
    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType   = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid    = 1;

    //MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateRej, Test_AT_RcvTafPsCallEvtPdpActivateRej_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    //相关全局变量初始化
    ucIndex                             = AT_CLIENT_ID_APP;
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_ORG_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateRej, Test_AT_RcvTafPsCallEvtPdpActivateRej_005)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU              stCallEvt;

    //参数初始化
    ucIndex                             = AT_CLIENT_ID_APP;
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    //相关全局变量初始化
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;

    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].enCurrPdpType = TAF_PDP_IPV6;
    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = 1;
    pstModemPsCtx->astCallEntity[0].enIpv6State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType   = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid    = 1;

    //MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, pstModemPsCtx->aucCidToIndexTbl[1]);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstModemPsCtx->astCallEntity[0].enIpv6State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstModemPsCtx->astCallEntity[0].ucIpv6Cid);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateRej, Test_AT_RcvTafPsCallEvtPdpActivateRej_006)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU              stCallEvt;

    //参数初始化
    ucIndex                             = AT_CLIENT_ID_APP;
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    //相关全局变量初始化
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;

    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].enCurrPdpType = TAF_PDP_IPV4V6;
    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = 1;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;
    pstModemPsCtx->astCallEntity[0].enIpv6State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType   = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid    = 1;

    //MOCKER操作
    /* 上报IPV4 IPV6 DEND*/
    MOCKER(At_SendResultData)
        .expects(exactly(2));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);
    EXPECT_EQ(AT_PS_CALL_INVALID_CALLID, pstModemPsCtx->aucCidToIndexTbl[1]);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstModemPsCtx->astCallEntity[0].enIpv4State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstModemPsCtx->astCallEntity[0].ucIpv4Cid);
    EXPECT_EQ(AT_PDP_STATE_IDLE, pstModemPsCtx->astCallEntity[0].enIpv6State);
    EXPECT_EQ(AT_PS_CALL_INVALID_CID, pstModemPsCtx->astCallEntity[0].ucIpv6Cid);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateRej, Test_AT_RcvTafPsCallEvtPdpActivateRej_007)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvt;

    // 参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    stCallEvt.ucCid       = 1;
    stCallEvt.stCtrl.usClientId    = AT_CLIENT_ID_HSUART;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSUART_USER;

    // MOCKER操作
    MOCKER(AT_ModemPsRspPdpActEvtRejProc)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex, &stCallEvt);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpActivateRej, Test_AT_RcvTafPsCallEvtPdpActivateRej_008)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stCallEvt;

    //参数初始化
    ucIndex                             = AT_CLIENT_ID_NDIS;
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

    //相关全局变量初始化
    gastAtClientTab[ucIndex].UserType   = AT_NDIS_USER;

    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_NDIS;

    //MOCKER操作
    MOCKER(AT_NdisPsRspPdpActEvtRejProc)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpActivateRej(ucIndex,
                                                &stCallEvt);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtPdpManageInd: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsCallEvtPdpManageInd, Test_AT_RcvTafPsCallEvtPdpManageInd_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MANAGE_IND_STRU     stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));

    //相关全局变量初始化
    ucIndex         = 0;
    AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucCrcType    = AT_CRC_DISABLE_TYPE;

    //MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpManageInd(ucIndex,
                                                &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_RcvTafPsCallEvtPdpManageInd, Test_AT_RcvTafPsCallEvtPdpManageInd_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MANAGE_IND_STRU     stCallEvt;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CRING: GPRS \"IPV6\",\"49.50.51.52\",,\"huawei.com\"\r\n";

    //参数初始化
    ucIndex         = 0;
    PS_MEM_SET(&stCallEvt, 0, sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));
    stCallEvt.stPdpAddr.enPdpType       = TAF_PDP_IPV6;
    memcpy(stCallEvt.stPdpAddr.aucIpv4Addr, "1234", TAF_IPV4_ADDR_LEN);
    memcpy(stCallEvt.stApn.aucValue, "huawei.com", strlen("huawei.com"));
    stCallEvt.stApn.ucLength            = strlen("huawei.com");


    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSsCtx.ucCrcType             = AT_CRC_ENABLE_TYPE;

    //MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpManageInd(ucIndex,
                                                &stCallEvt);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_RcvTafPsCallEvtPdpManageInd, Test_AT_RcvTafPsCallEvtPdpManageInd_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MANAGE_IND_STRU     stCallEvt;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CRING: GPRS \"IPV4V6\",\"49.50.51.52\",,\"huawei.com\"\r\n";

    //参数初始化
    ucIndex         = 0;
    PS_MEM_SET(&stCallEvt, 0, sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));

    stCallEvt.stPdpAddr.enPdpType       = TAF_PDP_IPV4V6;
    memcpy(stCallEvt.stPdpAddr.aucIpv4Addr, "1234", TAF_IPV4_ADDR_LEN);
    memcpy(stCallEvt.stApn.aucValue, "huawei.com", strlen("huawei.com"));
    stCallEvt.stApn.ucLength            = strlen("huawei.com");

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSsCtx.ucCrcType             = AT_CRC_ENABLE_TYPE;

    //MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpManageInd(ucIndex,
                                                &stCallEvt);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
#endif

TEST_F(Test_AT_RcvTafPsCallEvtPdpManageInd, Test_AT_RcvTafPsCallEvtPdpManageInd_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MANAGE_IND_STRU     stCallEvt;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CRING: GPRS \"PPP\",\"49.50.51.52\",,\"huawei.com\"\r\n";

    //参数初始化
    ucIndex         = 0;
    PS_MEM_SET(&stCallEvt, 0, sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));

    stCallEvt.stPdpAddr.enPdpType       = TAF_PDP_PPP;
    memcpy(stCallEvt.stPdpAddr.aucIpv4Addr, "1234", TAF_IPV4_ADDR_LEN);
    memcpy(stCallEvt.stApn.aucValue, "huawei.com", strlen("huawei.com"));
    stCallEvt.stApn.ucLength            = strlen("huawei.com");
    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSsCtx.ucCrcType             = AT_CRC_ENABLE_TYPE;

    //MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpManageInd(ucIndex,
                                                &stCallEvt);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpManageInd, Test_AT_RcvTafPsCallEvtPdpManageInd_005)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_MANAGE_IND_STRU     stEvent;
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                           *pcExpect;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_CHAR                           *pcIpAddr = "10.161.90.51";
    VOS_CHAR                           *pcApn = "abc.com";

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->ucCrcType = AT_CRC_ENABLE_TYPE;

    memset(&stEvent,0,sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));
    stEvent.stPdpAddr.enPdpType = TAF_PDP_IPV4;
    stEvent.stPdpAddr.aucIpv4Addr[0] = 10;
    stEvent.stPdpAddr.aucIpv4Addr[1] = 161;
    stEvent.stPdpAddr.aucIpv4Addr[2] = 90;
    stEvent.stPdpAddr.aucIpv4Addr[3] = 51;
    PS_MEM_CPY(stEvent.stApn.aucValue , pcApn, 8);
    stEvent.stApn.ucLength           = 8;

    /* 打桩函数 */
    pcExpect    = "\r\n+CRING: GPRS \"IP\",\"10.161.90.51\",,\"abc.com\"\r\n";
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    /* 调用函数 */
    AT_RcvTafPsCallEvtPdpManageInd(ucIndex, &stEvent);

    /* 检查结果 */
    ASSERT_STREQ(pcExpect, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtPdpModifyCnf: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyCnf, Test_AT_RcvTafPsCallEvtPdpModifyCnf_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyCnf(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyCnf, Test_AT_RcvTafPsCallEvtPdpModifyCnf_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyCnf(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyCnf, Test_AT_RcvTafPsCallEvtPdpModifyCnf_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));
    stCallEvt.ucCid = 0;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;
    gastAtClientTab[ucIndex].UserType      = AT_HSIC4_USER;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->astChannelCfg[stCallEvt.ucCid].ulRmNetId = UDI_ACM_HSIC_ACM1_ID;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(AT_NotifyFcWhenPdpModify)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT8)FC_ID_DIPC_1));


    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyCnf(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyCnf, Test_AT_RcvTafPsCallEvtPdpModifyCnf_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));
    stCallEvt.ucCid = 0;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;


    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyCnf(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyCnf, Test_AT_RcvTafPsCallEvtPdpModifyCnf_005)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTED;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    //MOCKER操作


    MOCKER(AT_NotifyFcWhenPdpModify)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyCnf(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyCnf, Test_AT_RcvTafPsCallEvtPdpModifyCnf_006)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTED;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作

    MOCKER(AT_NotifyFcWhenPdpModify)
        .expects(never());

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyCnf(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyCnf, Test_AT_RcvTafPsCallEvtPdpModifyCnf_007)
{
    // 变量声明
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     stCallEvt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    stCallEvt.ucCid       				= 1;
    stCallEvt.stCtrl.usClientId    		= AT_CLIENT_ID_HSUART;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSUART_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;

    // MOCKER操作
    MOCKER(AT_NotifyFcWhenPdpModify)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyCnf(ucIndex, &stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtPdpModifyRej: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyRej, Test_AT_RcvTafPsCallEvtPdpModifyRej_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_REJ_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_REJ_STRU));

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyRej(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifyRej, Test_AT_RcvTafPsCallEvtPdpModifyRej_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_REJ_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_REJ_STRU));

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifyRej(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtPdpModifiedInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifiedInd, Test_AT_RcvTafPsCallEvtPdpModifiedInd_001)
{
    /* 该事件不处理 */
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifiedInd, Test_AT_RcvTafPsCallEvtPdpModifiedInd_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_IND_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));
    stCallEvt.ucCid = 0;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].UserType      = AT_HSIC4_USER;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->astChannelCfg[0].ulRmNetId         = UDI_ACM_HSIC_ACM1_ID;

    //MOCKER操作
    MOCKER(AT_NotifyFcWhenPdpModify)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT8)FC_ID_DIPC_1));


    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifiedInd(ucIndex,
                                                   &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifiedInd, Test_AT_RcvTafPsCallEvtPdpModifiedInd_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_IND_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));
    stCallEvt.ucCid = 0;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifiedInd(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifiedInd, Test_AT_RcvTafPsCallEvtPdpModifiedInd_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_IND_STRU     stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stCallEvt.bitOpUmtsQos      = VOS_TRUE;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTED;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifiedInd(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifiedInd, Test_AT_RcvTafPsCallEvtPdpModifiedInd_005)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_MODIFY_IND_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTED;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //MOCKER操作
    MOCKER(AT_NotifyFcWhenPdpModify)
        .expects(never());

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifiedInd(ucIndex,
                                              &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpModifiedInd, Test_AT_RcvTafPsCallEvtPdpModifiedInd_006)
{
    // 变量声明
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     stCallEvt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    stCallEvt.ucCid       			    = 1;
    stCallEvt.stCtrl.usClientId    	    = AT_CLIENT_ID_HSUART;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSUART_USER;

    // MOCKER操作
    MOCKER(AT_NotifyFcWhenPdpModify)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpModifiedInd(ucIndex, &stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtPdpDeactivateCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_NDIS_USER;

#if (FEATURE_ON == FEATURE_NDIS)
    //MOCKER操作
    MOCKER(AT_NdisPsRspPdpDeactEvtCnfProc)
        .expects(exactly(1));
#endif

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_HSIC4_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_END_SET;

    //MOCKER操作
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(AT_HsicPsRspEvtPdpDeactCnfProc)
        .expects(exactly(1));

    MOCKER(At_SetMode)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

   //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_HSIC4_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stCallEvt.enPdpType = TAF_PDP_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_HSIC4_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

   //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_HSIC4_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_MODEM;
    stCallEvt.enPdpType         = TAF_PDP_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_HSIC4_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = UDI_NCM_HSIC_NCM0_ID;

    /* 给DIPC发消息 */
	MOCKER(Ps_SendMsg)
		.expects(exactly(1))
		.will(returnValue((VOS_UINT32)0));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

   //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_005)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU              stCallEvt;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_END_SET;

    //MOCKER操作
    MOCKER(AT_ProcAppPsRspEvtPdpDeActCnf)
        .expects(exactly(1));

    MOCKER(At_SetMode)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

   //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_006)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stCallEvt.enPdpType         = TAF_PDP_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

   //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_007)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU              stCallEvt;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    stCallEvt.ucCid = 1;
    stCallEvt.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stCallEvt.enPdpType         = TAF_PDP_IPV4;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    pstModemPsCtx->astChannelCfg[1].ulUsed = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId = RNIC_RM_NET_ID_0;

    /* 给RNIC发消息 */
	MOCKER(Ps_SendMsg)
		.expects(exactly(1))
		.will(returnValue((VOS_UINT32)0));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

   //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_008)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU              stCallEvt;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_WEBUI;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_END_SET;

    //MOCKER操作
    MOCKER(AT_AppPsRspEvtPdpDeactCnfProc)
        .expects(exactly(1));

   //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_009)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_END_SET;

    //MOCKER操作
    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(At_SetMode)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

   //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex,
                                                  &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivateCnf, Test_AT_RcvTafPsCallEvtPdpDeactivateCnf_010)
{
    // 变量声明
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     stCallEvt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    stCallEvt.ucCid                     = 1;
    stCallEvt.stCtrl.usClientId         = AT_CLIENT_ID_HSUART;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSUART_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_PS_SET;

    // MOCKER操作
    MOCKER(AT_ModemPsRspPdpDeactEvtCnfProc)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivateCnf(ucIndex, &stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtPdpDeactivatedInd: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivatedInd, Test_AT_RcvTafPsCallEvtPdpDeactivatedInd_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU));

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].UserType      = AT_NDIS_USER;

#if (FEATURE_ON == FEATURE_NDIS)
    //MOCKER操作
    MOCKER(AT_NdisPsRspPdpDeactivatedEvtProc)
        .expects(exactly(1));
#endif

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex,
                                                   &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivatedInd, Test_AT_RcvTafPsCallEvtPdpDeactivatedInd_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU));

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_HSIC4_USER;

    //MOCKER操作
    MOCKER(AT_HsicPsRspEvtPdpDeactivatedProc)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex,
                                                   &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivatedInd, Test_AT_RcvTafPsCallEvtPdpDeactivatedInd_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU));
    ucIndex                                = AT_CLIENT_TAB_APP1_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr             = SYSTEM_APP_ANDROID;

    //MOCKER操作
    MOCKER(AT_ProcAppPsRspEvtPdpDeactivated)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex,
                                                   &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivatedInd, Test_AT_RcvTafPsCallEvtPdpDeactivatedInd_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU              stCallEvt;

    //参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU));
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr             = SYSTEM_APP_WEBUI;

    //MOCKER操作
    MOCKER(AT_AppPsRspEvtPdpDeactivatedProc)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex,
                                                   &stCallEvt);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtPdpDeactivatedInd, Test_AT_RcvTafPsCallEvtPdpDeactivatedInd_005)
{
    // 变量声明
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     stCallEvt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    stCallEvt.ucCid                     = 1;
    stCallEvt.stCtrl.usClientId         = AT_CLIENT_ID_HSUART;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSUART_USER;

    // MOCKER操作
    MOCKER(AT_ModemPsRspPdpDeactivatedEvtProc)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvTafPsCallEvtPdpDeactivatedInd(ucIndex, &stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtCallOrigCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsCallEvtCallOrigCnf, Test_AT_RcvTafPsCallEvtCallOrigCnf_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;

    //参数初始化
    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SUCCESS;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_NDIS_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;
    g_stAtNdisDhcpPara.stUsrInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex,
                                             &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsCallEvtCallOrigCnf, Test_AT_RcvTafPsCallEvtCallOrigCnf_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;

    //参数初始化
    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_NDIS_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;
    g_stAtNdisDhcpPara.stUsrInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex,
                                             &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallOrigCnf, Test_AT_RcvTafPsCallEvtCallOrigCnf_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_WEBUI;

    //参数初始化
    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SUCCESS;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;
    g_stAtAppPdpEntity.stUsrInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex,
                                             &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsCallEvtCallOrigCnf, Test_AT_RcvTafPsCallEvtCallOrigCnf_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_WEBUI;
    //参数初始化
    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;
    g_stAtAppPdpEntity.stUsrInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex,
                                             &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallOrigCnf, Test_AT_RcvTafPsCallEvtCallOrigCnf_005)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;
    VOS_UINT8                          *pucSystemAppConfig;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;
    stCallOrigCnf.ucCid = 1;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = 1;
    pstModemPsCtx->astCallEntity[0].enIpv6State = AT_PDP_STATE_DEACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex,
                                             &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)

TEST_F(Test_AT_RcvTafPsCallEvtCallOrigCnf, Test_AT_RcvTafPsCallEvtCallOrigCnf_006)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;
    VOS_UINT8                          *pucSystemAppConfig;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;
    stCallOrigCnf.ucCid = 1;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_HSIC1_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_HSIC1_USER;
    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = 1;
    pstModemPsCtx->astCallEntity[0].enIpv6State = AT_PDP_STATE_DEACTING;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex,
                                             &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_AT_RcvTafPsCallEvtCallOrigCnf, Test_AT_RcvTafPsCallEvtCallOrigCnf_007)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;
    VOS_UINT8                          *pucSystemAppConfig;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallOrigCnf.enCause = TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN;
    stCallOrigCnf.ucCid = 1;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_USBCOM_USER;


    MOCKER(At_SendResultData)
        .expects(never());

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallOrigCnf(ucIndex,
                                             &stCallOrigCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

class Test_AT_RcvTafPsCallEvtCallEndCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsCallEvtCallEndCnf, Test_AT_RcvTafPsCallEvtCallEndCnf_001)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;

    //参数初始化
    PS_MEM_SET(&stCallEndCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallEndCnf.enCause               = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_NDIS_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;
    g_stAtNdisDhcpPara.stUsrInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallEndCnf(ucIndex,
                                            &stCallEndCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsCallEvtCallEndCnf, Test_AT_RcvTafPsCallEvtCallEndCnf_002)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;

    //参数初始化
    PS_MEM_SET(&stCallEndCnf, 0x00, sizeof(TAF_PS_CALL_END_CNF_STRU));
    stCallEndCnf.enCause               = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_NDIS_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;
    g_stAtNdisDhcpPara.stUsrInfo.enPortIndex = AT_CLIENT_TAB_NDIS_INDEX;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallEndCnf(ucIndex,
                                            &stCallEndCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallEndCnf, Test_AT_RcvTafPsCallEvtCallEndCnf_003)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_WEBUI;

    //参数初始化
    PS_MEM_SET(&stCallEndCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallEndCnf.enCause               = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;
    g_stAtAppPdpEntity.stUsrInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_APP_GET_USR_PORT_INDEX()), eq((VOS_UINT32)AT_OK));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallEndCnf(ucIndex,
                                            &stCallEndCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallEndCnf, Test_AT_RcvTafPsCallEvtCallEndCnf_004)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_WEBUI;

    //参数初始化
    PS_MEM_SET(&stCallEndCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    stCallEndCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;
    g_stAtAppPdpEntity.stUsrInfo.enPortIndex = AT_CLIENT_TAB_APP_INDEX;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_ERROR));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallEndCnf(ucIndex,
                                            &stCallEndCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallEndCnf, Test_AT_RcvTafPsCallEvtCallEndCnf_005)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;
    VOS_UINT8                          *pucSystemAppConfig;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEndCnf, 0x00, sizeof(TAF_PS_CALL_END_CNF_STRU));
    stCallEndCnf.enCause                = TAF_ERR_NO_ERROR;
    stCallEndCnf.stCtrl.usClientId      = AT_CLIENT_ID_APP;
    stCallEndCnf.ucCid                     = 1;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_APP_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_APP_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallEndCnf(ucIndex,
                                            &stCallEndCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallEndCnf, Test_AT_RcvTafPsCallEvtCallEndCnf_006)
{
    //参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;
    VOS_UINT8                          *pucSystemAppConfig;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    //参数初始化
    PS_MEM_SET(&stCallEndCnf, 0x00, sizeof(TAF_PS_CALL_END_CNF_STRU));
    stCallEndCnf.enCause                = TAF_ERR_NO_ERROR;
    stCallEndCnf.stCtrl.usClientId      = AT_CLIENT_ID_MODEM;
    stCallEndCnf.ucCid                     = 1;

    //相关全局变量初始化
    ucIndex                                = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].UserType      = AT_HSIC1_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    pstModemPsCtx->aucCidToIndexTbl[1] = 0;

    pstModemPsCtx->astCallEntity[0].ucIpv4Cid = 1;
    pstModemPsCtx->astCallEntity[0].ucIpv6Cid = AT_PS_CALL_INVALID_CID;
    pstModemPsCtx->astCallEntity[0].enIpv4State = AT_PDP_STATE_ACTING;

    pstModemPsCtx->astCallEntity[0].stUserInfo.enPortIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.enUserIndex = ucIndex;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrType = AT_HSIC1_USER;
    pstModemPsCtx->astCallEntity[0].stUserInfo.ucUsrCid = 1;

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallEndCnf(ucIndex,
                                            &stCallEndCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallEndCnf, Test_AT_RcvTafPsCallEvtCallEndCnf_007)
{
    // 变量声明
    TAF_PS_CALL_END_CNF_STRU            stCallEvt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_CALL_END_CNF_STRU));
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    stCallEvt.stCtrl.usClientId      = AT_CLIENT_ID_HSUART;
    stCallEvt.ucCid                     = 1;
    stCallEvt.enCause               = TAF_ERR_NO_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSUART_USER;

    // MOCKER操作
    MOCKER(AT_MODEM_ProcCallEndCnfEvent)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallEndCnf(ucIndex, &stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtCallModifyCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsCallEvtCallModifyCnf, Test_AT_RcvTafPsCallEvtCallModifyCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_MODIFY_CNF_STRU         stCallModifyCnf;

    //参数初始化
    PS_MEM_SET(&stCallModifyCnf, 0x00, sizeof(TAF_PS_CALL_MODIFY_CNF_STRU));
    stCallModifyCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallModifyCnf(ucIndex,
                                               &stCallModifyCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallModifyCnf, Test_AT_RcvTafPsCallEvtCallModifyCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_MODIFY_CNF_STRU         stCallModifyCnf;

    //参数初始化
    PS_MEM_SET(&stCallModifyCnf, 0x00, sizeof(TAF_PS_CALL_MODIFY_CNF_STRU));
    stCallModifyCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallModifyCnf(ucIndex,
                                               &stCallModifyCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsCallEvtCallAnswerCnf: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        //MOCKER(OM_AppGreenChannel)
        //    .stubs()
        //    .will(returnValue((VOS_UINT32)VOS_OK));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTafPsCallEvtCallAnswerCnf, Test_AT_RcvTafPsCallEvtCallAnswerCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_ANSWER_CNF_STRU         stCallAnswerCnf;

    //参数初始化
    PS_MEM_SET(&stCallAnswerCnf, 0x00, sizeof(TAF_PS_CALL_ANSWER_CNF_STRU));
    stCallAnswerCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallAnswerCnf(ucIndex,
                                               &stCallAnswerCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallAnswerCnf, Test_AT_RcvTafPsCallEvtCallAnswerCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_ANSWER_CNF_STRU         stCallAnswerCnf;

    //参数初始化
    PS_MEM_SET(&stCallAnswerCnf, 0x00, sizeof(TAF_PS_CALL_ANSWER_CNF_STRU));
    stCallAnswerCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGANS_ANS_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallAnswerCnf(ucIndex,
                                               &stCallAnswerCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsCallEvtCallAnswerCnf, Test_AT_RcvTafPsCallEvtCallAnswerCnf_003)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CALL_ANSWER_CNF_STRU         stCallAnswerCnf;

    //参数初始化
    PS_MEM_SET(&stCallAnswerCnf, 0x00, sizeof(TAF_PS_CALL_ANSWER_CNF_STRU));
    stCallAnswerCnf.enCause = TAF_ERR_AT_CONNECT;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGANS_ANS_EXT_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(Ppp_CreatePppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //调用被测函数
    ulResult = AT_RcvTafPsCallEvtCallAnswerCnf(ucIndex,
                                               &stCallAnswerCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus, AT_FW_CLIENT_STATUS_READY);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetPrimPdpContextInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtSetPrimPdpContextInfoCnf_001)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stSetPdpCtxInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU));
    stSetPdpCtxInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetPrimPdpContextInfoCnf(ucIndex,
                                                      &stSetPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtSetPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtSetPrimPdpContextInfoCnf_002)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stSetPdpCtxInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU));
    stSetPdpCtxInfoCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDCONT_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetPrimPdpContextInfoCnf(ucIndex,
                                                      &stSetPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsEvtGetPrimPdpContextInfoCnf: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};


TEST_F(Test_AT_RcvTafPsEvtGetPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetPrimPdpContextInfoCnf_001)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stGetPrimPdpCtxInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetPrimPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU));
    stGetPrimPdpCtxInfoCnf.enCause      = TAF_ERR_NO_ERROR;
    stGetPrimPdpCtxInfoCnf.ulCidNum     = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDCONT_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPrimPdpContextInfoCnf(ucIndex,
                                                      &stGetPrimPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetPrimPdpContextInfoCnf_002)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stGetPrimPdpCtxInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetPrimPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU));
    stGetPrimPdpCtxInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetPrimPdpCtxInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDCONT_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPrimPdpContextInfoCnf(ucIndex,
                                                      &stGetPrimPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetPrimPdpContextInfoCnf_003)
{
    // 变量声明
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulRslt;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   *pstGetPrimPdpCtxInfoCnf;
    VOS_CHAR                                    acExpectedStr[] = "+CGDCONT: 1,\"IP\",\"huawei.com\",\"192.168.1.2\",1,1,0,0,1,1\
\r\n+CGDCONT: 2,\"IPV6\",\"huawei1.com\",\"\",1,1,0,0,1,1\r\n+CGDCONT: 3,\"IPV4V6\",\"huawei2.com\",\"192.168.1.2\",1,1,0,1,1,1";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGDCONT,
        AT_SetCgdcontPara, AT_SET_PARA_TIME, AT_QryCgdcontPara, AT_QRY_PARA_TIME, At_TestCgdcont, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"+CGDCONT",     (VOS_UINT8*)CGDCONT_CMD_PARA_STRING};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstGetPrimPdpCtxInfoCnf = (TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
        sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU) + (3 * sizeof(TAF_PRI_PDP_QUERY_INFO_STRU)));
    PS_MEM_SET(pstGetPrimPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU) + (3 * sizeof(TAF_PRI_PDP_QUERY_INFO_STRU)));

    pstGetPrimPdpCtxInfoCnf->enCause      = TAF_PS_CAUSE_SUCCESS;
    pstGetPrimPdpCtxInfoCnf->ulCidNum     = 3;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].ucCid      = 1;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.stPdpAddr.enPdpType = TAF_PDP_IPV4;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.stPdpAddr.aucIpv4Addr[0] = 192;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.stPdpAddr.aucIpv4Addr[1] = 168;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.stPdpAddr.aucIpv4Addr[2] = 1;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.stPdpAddr.aucIpv4Addr[3] = 2;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.stApn.ucLength           = VOS_StrLen("huawei.com");
    PS_MEM_CPY(pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.stApn.aucValue,
               "huawei.com",
               VOS_StrLen("huawei.com"));
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.enPdpHcomp        = TAF_PDP_H_COMP_ON;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.enPdpDcomp        = TAF_PDP_D_COMP_ON;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.enEmergencyInd    = TAF_PDP_NOT_FOR_EMC;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.enPcscfDiscovery  = TAF_PDP_PCSCF_DISCOVERY_THROUGH_NAS_SIG;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.enIpv4AddrAlloc   = TAF_PDP_IPV4_ADDR_ALLOC_TYPE_NAS;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[0].stPriPdpInfo.enImCnSignalFlg   = TAF_PDP_FOR_IM_CN_SIG_ONLY;

    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].ucCid      = 2;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.stPdpAddr.enPdpType = TAF_PDP_IPV6;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.stApn.ucLength      = VOS_StrLen("huawei1.com");
    PS_MEM_CPY(pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.stApn.aucValue,
               "huawei1.com",
               VOS_StrLen("huawei1.com"));
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.enPdpHcomp        = TAF_PDP_H_COMP_ON;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.enPdpDcomp        = TAF_PDP_D_COMP_ON;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.enEmergencyInd    = TAF_PDP_NOT_FOR_EMC;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.enPcscfDiscovery  = TAF_PDP_PCSCF_DISCOVERY_THROUGH_NAS_SIG;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.enIpv4AddrAlloc   = 0;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[1].stPriPdpInfo.enImCnSignalFlg   = TAF_PDP_FOR_IM_CN_SIG_ONLY;

    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].ucCid      = 3;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.stPdpAddr.enPdpType = TAF_PDP_IPV4V6;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.stPdpAddr.aucIpv4Addr[0] = 192;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.stPdpAddr.aucIpv4Addr[1] = 168;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.stPdpAddr.aucIpv4Addr[2] = 1;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.stPdpAddr.aucIpv4Addr[3] = 2;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.stApn.ucLength           = VOS_StrLen("huawei2.com");
    PS_MEM_CPY(pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.stApn.aucValue,
               "huawei2.com",
               VOS_StrLen("huawei2.com"));
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.enPdpHcomp        = TAF_PDP_H_COMP_ON;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.enPdpDcomp        = TAF_PDP_D_COMP_ON;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.enEmergencyInd    = TAF_PDP_FOR_EMC;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.enPcscfDiscovery  = TAF_PDP_PCSCF_DISCOVERY_THROUGH_NAS_SIG;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.enIpv4AddrAlloc   = TAF_PDP_IPV4_ADDR_ALLOC_TYPE_NAS;
    pstGetPrimPdpCtxInfoCnf->astPdpContextQueryInfo[2].stPriPdpInfo.enImCnSignalFlg   = TAF_PDP_FOR_IM_CN_SIG_ONLY;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGDCONT_READ;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulRslt = AT_RcvTafPsEvtGetPrimPdpContextInfoCnf(ucIndex,
                                                    pstGetPrimPdpCtxInfoCnf);

    if (VOS_NULL_PTR != pstGetPrimPdpCtxInfoCnf)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetPrimPdpCtxInfoCnf);
        pstGetPrimPdpCtxInfoCnf = VOS_NULL_PTR;
    }

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsEvtSetSecPdpContextInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetSecPdpContextInfoCnf, Test_AT_RcvTafPsEvtSetSecPdpContextInfoCnf_001)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU    stSetPdpCtxInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU));
    stSetPdpCtxInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetSecPdpContextInfoCnf(ucIndex,
                                                     &stSetPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtSetSecPdpContextInfoCnf, Test_AT_RcvTafPsEvtSetSecPdpContextInfoCnf_002)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU    stSetPdpCtxInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU));
    stSetPdpCtxInfoCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDSCONT_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetSecPdpContextInfoCnf(ucIndex,
                                                     &stSetPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




class Test_AT_RcvTafPsEvtGetSecPdpContextInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetSecPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetSecPdpContextInfoCnf_001)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU    stGetSecPdpCtxInfoCnf;

    //参数初始化
    PS_MEM_SET(&stGetSecPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU));
    stGetSecPdpCtxInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetSecPdpCtxInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDSCONT_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetSecPdpContextInfoCnf(ucIndex,
                                                     &stGetSecPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetSecPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetSecPdpContextInfoCnf_002)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU    stGetSecPdpCtxInfoCnf;

    //参数初始化
    PS_MEM_SET(&stGetSecPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU));
    stGetSecPdpCtxInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetSecPdpCtxInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDSCONT_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetSecPdpContextInfoCnf(ucIndex,
                                                     &stGetSecPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtGetSecPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetSecPdpContextInfoCnf_003)
{
    // 变量声明
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulRslt;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU   *pstGetSecPdpCtxInfoCnf;
    VOS_CHAR                                    acExpectedStr[] = "+CGDSCONT: 1,4,1,1\r\n+CGDSCONT: 2,4,1,1\r\n+CGDSCONT: 3,4,1,1";


    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =  {AT_CMD_CGDSCONT,
        AT_SetCgdscontPara, AT_SET_PARA_TIME, AT_QryCgdscontPara, AT_QRY_PARA_TIME, At_TestCgdscont, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"+CGDSCONT",    (VOS_UINT8*)CGDSCONT_CMD_PARA_STRING};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstGetSecPdpCtxInfoCnf = (TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
        sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU) + (3 * sizeof(TAF_PDP_SEC_CONTEXT_STRU)));
    PS_MEM_SET(pstGetSecPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU) + (3 * sizeof(TAF_PDP_SEC_CONTEXT_STRU)));

    pstGetSecPdpCtxInfoCnf->enCause      = TAF_PS_CAUSE_SUCCESS;
    pstGetSecPdpCtxInfoCnf->ulCidNum     = 3;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[0].ucCid        = 1;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[0].ucLinkdCid   = 4;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[0].enPdpHcomp   = TAF_PDP_H_COMP_ON;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[0].enPdpDcomp   = TAF_PDP_D_COMP_ON;

    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[1].ucCid        = 2;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[1].ucLinkdCid   = 4;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[1].enPdpHcomp   = TAF_PDP_H_COMP_ON;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[1].enPdpDcomp   = TAF_PDP_D_COMP_ON;

    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[2].ucCid        = 3;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[2].ucLinkdCid   = 4;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[2].enPdpHcomp   = TAF_PDP_H_COMP_ON;
    pstGetSecPdpCtxInfoCnf->astPdpContextQueryInfo[2].enPdpDcomp   = TAF_PDP_D_COMP_ON;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGDSCONT_READ;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulRslt = AT_RcvTafPsEvtGetSecPdpContextInfoCnf(ucIndex,
                                                    pstGetSecPdpCtxInfoCnf);

    if (VOS_NULL_PTR != pstGetSecPdpCtxInfoCnf)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetSecPdpCtxInfoCnf);
        pstGetSecPdpCtxInfoCnf = VOS_NULL_PTR;
    }

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsEvtSetTftInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetTftInfoCnf, Test_AT_RcvTafPsEvtSetTftInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_TFT_INFO_CNF_STRU        stSetTftInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetTftInfoCnf, 0x00, sizeof(TAF_PS_SET_TFT_INFO_CNF_STRU));
    stSetTftInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetTftInfoCnf(ucIndex,
                                           &stSetTftInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtSetTftInfoCnf, Test_AT_RcvTafPsEvtSetTftInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_TFT_INFO_CNF_STRU        stSetTftInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetTftInfoCnf, 0x00, sizeof(TAF_PS_SET_TFT_INFO_CNF_STRU));
    stSetTftInfoCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFT_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetTftInfoCnf(ucIndex,
                                           &stSetTftInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetTftInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetTftInfoCnf, Test_AT_RcvTafPsEvtGetTftInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_TFT_INFO_CNF_STRU        stGetTftInfoCnf;

    //参数初始化
    PS_MEM_SET(&stGetTftInfoCnf, 0x00, sizeof(TAF_PS_GET_TFT_INFO_CNF_STRU));
    stGetTftInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetTftInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFT_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetTftInfoCnf(ucIndex,
                                           &stGetTftInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetTftInfoCnf, Test_AT_RcvTafPsEvtGetTftInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_TFT_INFO_CNF_STRU        stGetTftInfoCnf;

    //参数初始化
    PS_MEM_SET(&stGetTftInfoCnf, 0x00, sizeof(TAF_PS_GET_TFT_INFO_CNF_STRU));
    stGetTftInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetTftInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFT_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetTftInfoCnf(ucIndex,
                                           &stGetTftInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetUmtsQosInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetUmtsQosInfoCnf, Test_AT_RcvTafPsEvtSetUmtsQosInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU   stSetUmtsQosInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetUmtsQosInfoCnf, 0x00, sizeof(TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU));
    stSetUmtsQosInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetUmtsQosInfoCnf(ucIndex,
                                               &stSetUmtsQosInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtSetUmtsQosInfoCnf, Test_AT_RcvTafPsEvtSetUmtsQosInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU   stSetUmtsQosInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetUmtsQosInfoCnf, 0x00, sizeof(TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU));
    stSetUmtsQosInfoCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQREQ_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetUmtsQosInfoCnf(ucIndex,
                                               &stSetUmtsQosInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetUmtsQosInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetUmtsQosInfoCnf, Test_AT_RcvTafPsEvtGetUmtsQosInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU   stGetUmtsQosInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetUmtsQosInfoCnf, 0x00, sizeof(TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU));
    stGetUmtsQosInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetUmtsQosInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQREQ_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetUmtsQosInfoCnf(ucIndex,
                                               &stGetUmtsQosInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetUmtsQosInfoCnf, Test_AT_RcvTafPsEvtGetUmtsQosInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU   stGetUmtsQosInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetUmtsQosInfoCnf, 0x00, sizeof(TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU));
    stGetUmtsQosInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetUmtsQosInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQREQ_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetUmtsQosInfoCnf(ucIndex,
                                               &stGetUmtsQosInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetUmtsQosMinInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetUmtsQosMinInfoCnf, Test_AT_RcvTafPsEvtSetUmtsQosMinInfoCnf_001)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU   stSetUmtsQosMinInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetUmtsQosMinInfoCnf, 0x00, sizeof(TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU));
    stSetUmtsQosMinInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetUmtsQosMinInfoCnf(ucIndex,
                                                  &stSetUmtsQosMinInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtSetUmtsQosMinInfoCnf, Test_AT_RcvTafPsEvtSetUmtsQosMinInfoCnf_002)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU   stSetUmtsQosMinInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetUmtsQosMinInfoCnf, 0x00, sizeof(TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU));
    stSetUmtsQosMinInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetUmtsQosMinInfoCnf(ucIndex,
                                                  &stSetUmtsQosMinInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetUmtsQosMinInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetUmtsQosMinInfoCnf, Test_AT_RcvTafPsEvtGetUmtsQosMinInfoCnf_001)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU   stGetUmtsQosMinInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetUmtsQosMinInfoCnf, 0x00, sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU));
    stGetUmtsQosMinInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetUmtsQosMinInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetUmtsQosMinInfoCnf(ucIndex,
                                                  &stGetUmtsQosMinInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




TEST_F(Test_AT_RcvTafPsEvtGetUmtsQosMinInfoCnf, Test_AT_RcvTafPsEvtGetUmtsQosMinInfoCnf_002)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU   stGetUmtsQosMinInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetUmtsQosMinInfoCnf, 0x00, sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU));
    stGetUmtsQosMinInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetUmtsQosMinInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetUmtsQosMinInfoCnf(ucIndex,
                                                  &stGetUmtsQosMinInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf, Test_AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf_001)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU   stDynUmtsQosMinInfo;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stDynUmtsQosMinInfo, 0x00, sizeof(TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU));
    stDynUmtsQosMinInfo.enCause = TAF_ERR_NO_ERROR;
    stDynUmtsQosMinInfo.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_READ;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf(ucIndex,
                                                      &stDynUmtsQosMinInfo);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf, Test_AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf_002)
{
    //参数定义
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU   stDynUmtsQosMinInfo;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stDynUmtsQosMinInfo, 0x00, sizeof(TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU));
    stDynUmtsQosMinInfo.enCause = TAF_ERR_NO_ERROR;
    stDynUmtsQosMinInfo.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQNEG_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf(ucIndex,
                                                      &stDynUmtsQosMinInfo);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetPdpContextCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetPdpContextCnf, Test_AT_RcvTafPsEvtSetPdpContextCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_PDP_STATE_CNF_STRU       stSetPdpStateCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpStateCnf, 0x00, sizeof(TAF_PS_SET_PDP_STATE_CNF_STRU));
    stSetPdpStateCnf.enCause = TAF_PS_CAUSE_SUCCESS;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetPdpStateCnf(ucIndex,
                                            &stSetPdpStateCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtSetPdpContextCnf, Test_AT_RcvTafPsEvtSetPdpContextCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_PDP_STATE_CNF_STRU       stSetPdpStateCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpStateCnf, 0x00, sizeof(TAF_PS_SET_PDP_STATE_CNF_STRU));
    stSetPdpStateCnf.enCause = TAF_PS_CAUSE_CID_INVALID;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_END_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetPdpStateCnf(ucIndex,
                                            &stSetPdpStateCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsEvtGetPdpStateCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetPdpStateCnf, Test_AT_RcvTafPsEvtGetPdpStateCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_PDP_STATE_CNF_STRU       stPdpCtxState;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stPdpCtxState, 0x00, sizeof(TAF_PS_GET_PDP_STATE_CNF_STRU));
    stPdpCtxState.enCause = TAF_ERR_NO_ERROR;
    stPdpCtxState.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_READ;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpStateCnf(ucIndex,
                                            &stPdpCtxState);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetPdpStateCnf, Test_AT_RcvTafPsEvtGetPdpStateCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_PDP_STATE_CNF_STRU       stPdpCtxState;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stPdpCtxState, 0x00, sizeof(TAF_PS_GET_PDP_STATE_CNF_STRU));
    stPdpCtxState.enCause = TAF_ERR_NO_ERROR;
    stPdpCtxState.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpStateCnf(ucIndex,
                                            &stPdpCtxState);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetPdpStateCnf, Test_AT_RcvTafPsEvtGetPdpStateCnf_003)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_PDP_STATE_CNF_STRU       stPdpCtxState;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stPdpCtxState, 0x00, sizeof(TAF_PS_GET_PDP_STATE_CNF_STRU));
    stPdpCtxState.enCause = TAF_ERR_NO_ERROR;
    stPdpCtxState.ulCidNum    = 1;
    ucIndex                   = 0;
    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_READ;


    /*MOCKER(At_sprintf)
          .stubs()
          .will(returnValue(0));*/

    //MOCKER操作
    MOCKER(AT_RcvTafPsEvtCgactQryCnf)
        .expects(exactly(1))
		.will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpStateCnf(ucIndex,
                                            &stPdpCtxState);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtGetPdpStateCnf, Test_AT_RcvTafPsEvtGetPdpStateCnf_004)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_PDP_STATE_CNF_STRU       stPdpCtxState;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stPdpCtxState, 0x00, sizeof(TAF_PS_GET_PDP_STATE_CNF_STRU));
    stPdpCtxState.enCause = TAF_ERR_NO_ERROR;
    stPdpCtxState.ulCidNum    = 1;
    ucIndex                   = 0;
    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQNEG_TEST;


    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(0));*/

    //MOCKER操作
    MOCKER(AT_RcvTafPsEvtCgeqnegTestCnf)
		.expects(exactly(1))
		.will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpStateCnf(ucIndex,
                                            &stPdpCtxState);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetPdpIpAddrInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetPdpIpAddrInfoCnf, Test_AT_RcvTafPsEvtGetPdpIpAddrInfoCnf_001)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU    stGetPdpIpAddrInfoCnf;

    //参数初始化
    PS_MEM_SET(&stGetPdpIpAddrInfoCnf, 0x00, sizeof(TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU));
    stGetPdpIpAddrInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetPdpIpAddrInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpIpAddrInfoCnf(ucIndex,
                                                 &stGetPdpIpAddrInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetPdpIpAddrInfoCnf, Test_AT_RcvTafPsEvtGetPdpIpAddrInfoCnf_002)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU    stGetPdpIpAddrInfoCnf;

    //参数初始化
    PS_MEM_SET(&stGetPdpIpAddrInfoCnf, 0x00, sizeof(TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU));
    stGetPdpIpAddrInfoCnf.enCause = TAF_ERR_NO_ERROR;
    stGetPdpIpAddrInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGPADDR_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpIpAddrInfoCnf(ucIndex,
                                                 &stGetPdpIpAddrInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetAnsModeInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetAnsModeInfoCnf, Test_AT_RcvTafPsEvtSetAnsModeInfoCnf_001)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU    stSetAnsModeInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetAnsModeInfoCnf, 0x00, sizeof(TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU));
    stSetAnsModeInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetAnsModeInfoCnf(ucIndex,
                                               &stSetAnsModeInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtSetAnsModeInfoCnf, Test_AT_RcvTafPsEvtSetAnsModeInfoCnf_002)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU    stSetAnsModeInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetAnsModeInfoCnf, 0x00, sizeof(TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU));
    stSetAnsModeInfoCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetAnsModeInfoCnf(ucIndex,
                                               &stSetAnsModeInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetAnsModeInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetAnsModeInfoCnf, Test_AT_RcvTafPsEvtGetAnsModeInfoCnf_001)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU    stAnsModeInfo;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stAnsModeInfo, 0x00, sizeof(TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU));
    stAnsModeInfo.enCause = TAF_ERR_NO_ERROR;
    stAnsModeInfo.ulAnsMode   = 1;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetAnsModeInfoCnf(ucIndex,
                                               &stAnsModeInfo);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetAnsModeInfoCnf, Test_AT_RcvTafPsEvtGetAnsModeInfoCnf_002)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    AT_PAR_CMD_ELEMENT_STRU                 stCmdElement;
    TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU    stAnsModeInfo;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stCmdElement, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    stCmdElement.pszCmdName = (VOS_UINT8*)"^CGAUTH";

    PS_MEM_SET(&stAnsModeInfo, 0x00, sizeof(TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU));
    stAnsModeInfo.enCause = TAF_ERR_NO_ERROR;
    stAnsModeInfo.ulAnsMode   = 1;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_READ;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetAnsModeInfoCnf(ucIndex,
                                               &stAnsModeInfo);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




class Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf_001)
{
    //参数定义
    VOS_UINT32                                          ulResult;
    VOS_UINT8                                           ucIndex;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stGetDynamicPdpCtxInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetDynamicPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU));
    stGetDynamicPdpCtxInfoCnf.enCause = TAF_PARA_OK;
    stGetDynamicPdpCtxInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf(ucIndex,
                                               &stGetDynamicPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf_002)
{
    //参数定义
    VOS_UINT32                                          ulResult;
    VOS_UINT8                                           ucIndex;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stGetDynamicPdpCtxInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetDynamicPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU));
    stGetDynamicPdpCtxInfoCnf.enCause = TAF_PARA_OK;
    stGetDynamicPdpCtxInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCONTRDP_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf(ucIndex,
                                               &stGetDynamicPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf_003)
{
    // 变量声明
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulRslt;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU   *pstGetDynamicPdpCtxInfoCnf;
    VOS_CHAR                                    acExpectedStr[] = "+CGCONTRDP: 1,2,\"huawei.com\",\
\"192.168.1.2.255.255.255.0\",\"192.168.1.2\",\"192.168.1.2\",\"192.168.1.2\",\"192.168.1.2\",\"192.168.1.2\",1";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGCONTRDP,
    atSetCgcontrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgcontrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGCONTRDP",    (VOS_UINT8*)"(1-31)"};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstGetDynamicPdpCtxInfoCnf = (TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
        sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU) + (1 * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU)));
    PS_MEM_SET(pstGetDynamicPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU) + (1 * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU)));

    pstGetDynamicPdpCtxInfoCnf->enCause      = TAF_PS_CAUSE_SUCCESS;
    pstGetDynamicPdpCtxInfoCnf->ulCidNum     = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].ucPrimayCid                 = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].ucBearerId                  = 2;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpApn                    = VOS_TRUE;
    PS_MEM_CPY(pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].aucApn,
               "huawei.com",
               VOS_StrLen("huawei.com"));
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpIpAddr                 = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPdpAddr.enPdpType         = TAF_PDP_IPV4;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPdpAddr.aucIpv4Addr[0]    = 192;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPdpAddr.aucIpv4Addr[1]    = 168;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPdpAddr.aucIpv4Addr[2]    = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPdpAddr.aucIpv4Addr[3]    = 2;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpSubMask                = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stSubnetMask.enPdpType      = TAF_PDP_IPV4;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stSubnetMask.aucIpv4Addr[0] = 255;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stSubnetMask.aucIpv4Addr[1] = 255;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stSubnetMask.aucIpv4Addr[2] = 255;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stSubnetMask.aucIpv4Addr[3] = 0;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpGwAddr                 = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stGWAddr.enPdpType          = TAF_PDP_IPV4;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stGWAddr.aucIpv4Addr[0]     = 192;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stGWAddr.aucIpv4Addr[1]     = 168;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stGWAddr.aucIpv4Addr[2]     = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stGWAddr.aucIpv4Addr[3]     = 2;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpDNSPrimAddr            = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSPrimAddr.enPdpType     = TAF_PDP_IPV4;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSPrimAddr.aucIpv4Addr[0]= 192;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSPrimAddr.aucIpv4Addr[1]= 168;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSPrimAddr.aucIpv4Addr[2]= 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSPrimAddr.aucIpv4Addr[3]= 2;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpDNSSecAddr             = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSSecAddr.enPdpType      = TAF_PDP_IPV4;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSSecAddr.aucIpv4Addr[0] = 192;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSSecAddr.aucIpv4Addr[1] = 168;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSSecAddr.aucIpv4Addr[2] = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSSecAddr.aucIpv4Addr[3] = 2;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpPCSCFPrimAddr              = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFPrimAddr.enPdpType       = TAF_PDP_IPV4;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFPrimAddr.aucIpv4Addr[0]  = 192;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFPrimAddr.aucIpv4Addr[1]  = 168;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFPrimAddr.aucIpv4Addr[2]  = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFPrimAddr.aucIpv4Addr[3]  = 2;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpPCSCFSecAddr               = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFSecAddr.enPdpType        = TAF_PDP_IPV4;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFSecAddr.aucIpv4Addr[0]   = 192;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFSecAddr.aucIpv4Addr[1]   = 168;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFSecAddr.aucIpv4Addr[2]   = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFSecAddr.aucIpv4Addr[3]   = 2;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpImCnSignalFlg          = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].enImCnSignalFlg             = TAF_PDP_FOR_IM_CN_SIG_ONLY;



    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGCONTRDP_SET;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulRslt = AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf(ucIndex,
                                                           pstGetDynamicPdpCtxInfoCnf);

    if (VOS_NULL_PTR != pstGetDynamicPdpCtxInfoCnf)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);
        pstGetDynamicPdpCtxInfoCnf = VOS_NULL_PTR;
    }

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf_004)
{
    // 变量声明
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulRslt;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU   *pstGetDynamicPdpCtxInfoCnf;
    VOS_CHAR                                    acExpectedStr[] = "+CGCONTRDP: 1,2,\
\"huawei.com\",\"0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0\",\
\"0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0\",\"0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0\",\
\"0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0\",\"0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0\",\"0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0\",";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGCONTRDP,
    atSetCgcontrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgcontrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGCONTRDP",    (VOS_UINT8*)"(1-31)"};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstGetDynamicPdpCtxInfoCnf = (TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
        sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU) + (1 * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU)));
    PS_MEM_SET(pstGetDynamicPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU) + (1 * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU)));

    pstGetDynamicPdpCtxInfoCnf->enCause      = TAF_PS_CAUSE_SUCCESS;
    pstGetDynamicPdpCtxInfoCnf->ulCidNum     = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].ucPrimayCid                 = 1;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].ucBearerId                  = 2;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpApn                    = VOS_TRUE;
    PS_MEM_CPY(pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].aucApn,
               "huawei.com",
               VOS_StrLen("huawei.com"));
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpIpAddr                 = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPdpAddr.enPdpType         = TAF_PDP_IPV6;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpSubMask                = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stSubnetMask.enPdpType      = TAF_PDP_IPV6;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpGwAddr                 = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stGWAddr.enPdpType          = TAF_PDP_IPV6;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpDNSPrimAddr            = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSPrimAddr.enPdpType     = TAF_PDP_IPV6;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpDNSSecAddr             = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stDNSSecAddr.enPdpType      = TAF_PDP_IPV6;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpPCSCFPrimAddr          = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFPrimAddr.enPdpType   = TAF_PDP_IPV6;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpPCSCFSecAddr           = VOS_TRUE;
    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].stPCSCFSecAddr.enPdpType    = TAF_PDP_IPV6;

    pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo[0].bitOpImCnSignalFlg          = VOS_FALSE;


    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGCONTRDP_SET;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulRslt = AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf(ucIndex,
                                                           pstGetDynamicPdpCtxInfoCnf);

    if (VOS_NULL_PTR != pstGetDynamicPdpCtxInfoCnf)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);
        pstGetDynamicPdpCtxInfoCnf = VOS_NULL_PTR;
    }

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf_001)
{
    //参数定义
    VOS_UINT32                                          ulResult;
    VOS_UINT8                                           ucIndex;
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU    stGetDynamicPdpCtxInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetDynamicPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU));
    stGetDynamicPdpCtxInfoCnf.enCause = TAF_PARA_OK;
    stGetDynamicPdpCtxInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf(ucIndex,
                                                            &stGetDynamicPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf, Test_AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf_002)
{
    //参数定义
    VOS_UINT32                                          ulResult;
    VOS_UINT8                                           ucIndex;
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU    stGetDynamicPdpCtxInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetDynamicPdpCtxInfoCnf, 0x00, sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU));
    stGetDynamicPdpCtxInfoCnf.enCause = TAF_PARA_OK;
    stGetDynamicPdpCtxInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGSCONTRDP_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf(ucIndex,
                                                            &stGetDynamicPdpCtxInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetDynamicTftInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetDynamicTftInfoCnf, Test_AT_RcvTafPsEvtGetDynamicTftInfoCnf_001)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU    stGetDynamicTftInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetDynamicTftInfoCnf, 0x00, sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU));
    stGetDynamicTftInfoCnf.enCause = TAF_PARA_OK;
    stGetDynamicTftInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDynamicTftInfoCnf(ucIndex,
                                                  &stGetDynamicTftInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetDynamicTftInfoCnf, Test_AT_RcvTafPsEvtGetDynamicTftInfoCnf_002)
{
    //参数定义
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU    stGetDynamicTftInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetDynamicTftInfoCnf, 0x00, sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU));
    stGetDynamicTftInfoCnf.enCause = TAF_PARA_OK;
    stGetDynamicTftInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFTRDP_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDynamicTftInfoCnf(ucIndex,
                                                  &stGetDynamicTftInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetDsFlowInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetDsFlowInfoCnf, Test_AT_RcvTafPsEvtGetDsFlowInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_DSFLOW_INFO_CNF_STRU     stGetDsFlowInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetDsFlowInfoCnf, 0x00, sizeof(TAF_PS_GET_DSFLOW_INFO_CNF_STRU));
    stGetDsFlowInfoCnf.enCause             = TAF_PARA_OK;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetDsFlowInfoCnf(ucIndex,
                                              &stGetDsFlowInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




class Test_AT_RcvTafPsEvtClearDsFlowInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtClearDsFlowInfoCnf, Test_AT_RcvTafPsEvtClearDsFlowInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CLEAR_DSFLOW_CNF_STRU        stClearDsFlowCnf;

    //参数初始化
    PS_MEM_SET(&stClearDsFlowCnf, 0x00, sizeof(TAF_PS_CLEAR_DSFLOW_CNF_STRU));
    stClearDsFlowCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtClearDsFlowInfoCnf(ucIndex,
                                                &stClearDsFlowCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtClearDsFlowInfoCnf, Test_AT_RcvTafPsEvtClearDsFlowInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CLEAR_DSFLOW_CNF_STRU        stClearDsFlowCnf;

    //参数初始化
    PS_MEM_SET(&stClearDsFlowCnf, 0x00, sizeof(TAF_PS_CLEAR_DSFLOW_CNF_STRU));
    stClearDsFlowCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DSFLOWCLR_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtClearDsFlowInfoCnf(ucIndex,
                                                &stClearDsFlowCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtConfigDsFlowRptCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtConfigDsFlowRptCnf, Test_AT_RcvTafPsEvtConfigDsFlowRptCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU   stConfigDsFlowRptCnf;

    //参数初始化
    PS_MEM_SET(&stConfigDsFlowRptCnf, 0x00, sizeof(TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU));
    stConfigDsFlowRptCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtConfigDsFlowRptCnf(ucIndex,
                                                &stConfigDsFlowRptCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtConfigDsFlowRptCnf, Test_AT_RcvTafPsEvtConfigDsFlowRptCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU   stConfigDsFlowRptCnf;

    //参数初始化
    PS_MEM_SET(&stConfigDsFlowRptCnf, 0x00, sizeof(TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU));
    stConfigDsFlowRptCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DSFLOWRPT_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtConfigDsFlowRptCnf(ucIndex,
                                                &stConfigDsFlowRptCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetPdpAuthInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetPdpAuthInfoCnf, Test_AT_RcvTafPsEvtSetPdpAuthInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU   stSetPdpAuthInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpAuthInfoCnf, 0x00, sizeof(TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU));
    stSetPdpAuthInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetPdpAuthInfoCnf(ucIndex,
                                               &stSetPdpAuthInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtSetPdpAuthInfoCnf, Test_AT_RcvTafPsEvtSetPdpAuthInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU   stSetPdpAuthInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpAuthInfoCnf, 0x00, sizeof(TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU));
    stSetPdpAuthInfoCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTH_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetPdpAuthInfoCnf(ucIndex,
                                               &stSetPdpAuthInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetPdpAuthInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetPdpAuthInfoCnf, Test_AT_RcvTafPsEvtGetPdpAuthInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU   stGetPdpAuthInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetPdpAuthInfoCnf, 0x00, sizeof(TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU));
    stGetPdpAuthInfoCnf.enCause = TAF_PARA_OK;
    stGetPdpAuthInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTH_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpAuthInfoCnf(ucIndex,
                                               &stGetPdpAuthInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetPdpAuthInfoCnf, Test_AT_RcvTafPsEvtGetPdpAuthInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU   stGetPdpAuthInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetPdpAuthInfoCnf, 0x00, sizeof(TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU));
    stGetPdpAuthInfoCnf.enCause = TAF_PARA_OK;
    stGetPdpAuthInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTH_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpAuthInfoCnf(ucIndex,
                                               &stGetPdpAuthInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetPdpDnsInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetPdpDnsInfoCnf, Test_AT_RcvTafPsEvtSetPdpDnsInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_PDP_DNS_INFO_CNF_STRU    stSetPdpDnsInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpDnsInfoCnf, 0x00, sizeof(TAF_PS_SET_PDP_DNS_INFO_CNF_STRU));
    stSetPdpDnsInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetPdpDnsInfoCnf(ucIndex,
                                              &stSetPdpDnsInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtSetPdpDnsInfoCnf, Test_AT_RcvTafPsEvtSetPdpDnsInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_PDP_DNS_INFO_CNF_STRU    stSetPdpDnsInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetPdpDnsInfoCnf, 0x00, sizeof(TAF_PS_SET_PDP_DNS_INFO_CNF_STRU));
    stSetPdpDnsInfoCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetPdpDnsInfoCnf(ucIndex,
                                              &stSetPdpDnsInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetPdpDnsInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetPdpDnsInfoCnf, Test_AT_RcvTafPsEvtGetPdpDnsInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_PDP_DNS_INFO_CNF_STRU    stGetPdpDnsInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetPdpDnsInfoCnf, 0x00, sizeof(TAF_PS_GET_PDP_DNS_INFO_CNF_STRU));
    stGetPdpDnsInfoCnf.enCause = TAF_PARA_OK;
    stGetPdpDnsInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpDnsInfoCnf(ucIndex,
                                              &stGetPdpDnsInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




TEST_F(Test_AT_RcvTafPsEvtGetPdpDnsInfoCnf, Test_AT_RcvTafPsEvtGetPdpDnsInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_PDP_DNS_INFO_CNF_STRU    stGetPdpDnsInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetPdpDnsInfoCnf, 0x00, sizeof(TAF_PS_GET_PDP_DNS_INFO_CNF_STRU));
    stGetPdpDnsInfoCnf.enCause = TAF_PARA_OK;
    stGetPdpDnsInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetPdpDnsInfoCnf(ucIndex,
                                               &stGetPdpDnsInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtGetPdpDnsInfoCnf, Test_AT_RcvTafPsEvtGetPdpDnsInfoCnf_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    TAF_PS_GET_PDP_DNS_INFO_CNF_STRU   *pstGetDnsInfoCnf;
    VOS_CHAR                            acExpectedStr[] = "^CGDNS: 1,\"192.168.1.2\",\"192.168.1.2\"";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGDNS,
    AT_SetCgdnsPara,        AT_SET_PARA_TIME,   AT_QryCgdnsPara,        AT_QRY_PARA_TIME,
    At_TestCgdnsPara,   AT_TEST_PARA_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"^CGDNS",    (VOS_UINT8*)"(1-11),(PriDns),(SecDns)"};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstGetDnsInfoCnf = (TAF_PS_GET_PDP_DNS_INFO_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
        sizeof(TAF_PS_GET_PDP_DNS_INFO_CNF_STRU) + (1 * sizeof(TAF_DNS_QUERY_INFO_STRU)));
    PS_MEM_SET(pstGetDnsInfoCnf, 0x00, sizeof(TAF_PS_GET_PDP_DNS_INFO_CNF_STRU) + (1 * sizeof(TAF_DNS_QUERY_INFO_STRU)));

    pstGetDnsInfoCnf->ulCidNum  = 1;
    pstGetDnsInfoCnf->enCause   = TAF_PS_CAUSE_SUCCESS;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].ucCid                       = 1;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.bitOpPrimDnsAddr  = VOS_TRUE;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.aucPrimDnsAddr[0] = 192;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.aucPrimDnsAddr[1] = 168;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.aucPrimDnsAddr[2] = 1;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.aucPrimDnsAddr[3] = 2;

    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.bitOpSecDnsAddr   = VOS_TRUE;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.aucSecDnsAddr[0]  = 192;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.aucSecDnsAddr[1]  = 168;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.aucSecDnsAddr[2]  = 1;
    pstGetDnsInfoCnf->astPdpDnsQueryInfo[0].stDnsInfo.aucSecDnsAddr[3]  = 2;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGDNS_READ;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulRslt = AT_RcvTafPsEvtGetPdpDnsInfoCnf(ucIndex, pstGetDnsInfoCnf);

    if (VOS_NULL_PTR != pstGetDnsInfoCnf)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDnsInfoCnf);
        pstGetDnsInfoCnf = VOS_NULL_PTR;
    }

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetAuthDataInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtSetAuthDataInfoCnf, Test_AT_RcvTafPsEvtSetAuthDataInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_AUTHDATA_INFO_CNF_STRU   stSetAuthDataInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetAuthDataInfoCnf, 0x00, sizeof(TAF_PS_SET_AUTHDATA_INFO_CNF_STRU));
    stSetAuthDataInfoCnf.enCause = TAF_ERR_NO_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetAuthDataInfoCnf(ucIndex,
                                                &stSetAuthDataInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtSetAuthDataInfoCnf, Test_AT_RcvTafPsEvtSetAuthDataInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_SET_AUTHDATA_INFO_CNF_STRU   stSetAuthDataInfoCnf;

    //参数初始化
    PS_MEM_SET(&stSetAuthDataInfoCnf, 0x00, sizeof(TAF_PS_SET_AUTHDATA_INFO_CNF_STRU));
    stSetAuthDataInfoCnf.enCause = TAF_ERR_ERROR;

    //相关全局变量初始化
    ucIndex                                = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtSetAuthDataInfoCnf(ucIndex,
                                                &stSetAuthDataInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtGetAuthDataInfoCnf: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtGetAuthDataInfoCnf, Test_AT_RcvTafPsEvtGetAuthDataInfoCnf_001)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_AUTHDATA_INFO_CNF_STRU   stGetAuthDataInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetAuthDataInfoCnf, 0x00, sizeof(TAF_PS_GET_AUTHDATA_INFO_CNF_STRU));
    stGetAuthDataInfoCnf.enCause = TAF_PARA_OK;
    stGetAuthDataInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    //MOCKER操作

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetAuthDataInfoCnf(ucIndex,
                                                &stGetAuthDataInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvTafPsEvtGetAuthDataInfoCnf, Test_AT_RcvTafPsEvtGetAuthDataInfoCnf_002)
{
    //参数定义
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_PS_GET_AUTHDATA_INFO_CNF_STRU   stGetAuthDataInfoCnf;

    //参数初始化
    ucIndex = 0;

    PS_MEM_SET(&stGetAuthDataInfoCnf, 0x00, sizeof(TAF_PS_GET_AUTHDATA_INFO_CNF_STRU));
    stGetAuthDataInfoCnf.enCause = TAF_PARA_OK;
    stGetAuthDataInfoCnf.ulCidNum    = 0;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_AUTHDATA_READ;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //调用被测函数
    ulResult = AT_RcvTafPsEvtGetAuthDataInfoCnf(ucIndex,
                                                &stGetAuthDataInfoCnf);

    //执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




class Test_AT_RcvTafPsEvtGetPdpContextInfoCnf: public ::testing::Test
{
public:
    TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU    m_stPdpCxt;
    VOS_UINT8                               ucIndex;
    AT_PAR_CMD_ELEMENT_STRU                 stElement;
    VOS_UINT8                               szCmdName[32];

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"+cgpaddr");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;
    }

    void TearDown()
    {
    }
};

TEST_F(Test_AT_RcvTafPsEvtGetPdpContextInfoCnf,Test_AT_RcvTafPsEvtGetPdpContextInfoCnf_001)
{
    /* 变量定义 */
    VOS_UINT32                  ulRet;

    gastAtClientTab[0].CmdCurrentOpt    = AT_CMD_CSDFLT_READ;

    /* 调用被测函数 */
    ulRet = AT_RcvTafPsEvtGetPdpContextInfoCnf(ucIndex,&m_stPdpCxt);

    EXPECT_EQ((VOS_UINT16)VOS_ERR, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsEvtGetPdpContextInfoCnf,Test_AT_RcvTafPsEvtGetPdpContextInfoCnf_002)
{
    /* 变量定义 */
    VOS_UINT32                  ulRet;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGPADDR_TEST;

    m_stPdpCxt.ulCidNum                 = 2;
    m_stPdpCxt.ulCid[0]                 = 1;
    m_stPdpCxt.ulCid[1]                 = 2;

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    ulRet = AT_RcvTafPsEvtGetPdpContextInfoCnf(ucIndex,&m_stPdpCxt);

    EXPECT_EQ((VOS_UINT16)VOS_OK, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




class Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex     = 0;

        stCmdInfo.ulCmdIndex        = AT_CMD_DNSQUERY;
        stCmdInfo.pfnSetProc        = AT_SetDnsQueryPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_LIMITED_NULL;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^DNSQUERY";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf, Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf_001)
{
    VOS_UINT32                          ulRet;
    TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU stNegoDnsCnf;
    VOS_CHAR                           *pcExpactedStr;

    /* 初始化变量 */
    ulRet           = VOS_ERROR;
    PS_MEM_SET(&stNegoDnsCnf, 0x00, sizeof(TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU));

    pcExpactedStr   = "^DNSQUERY: \"192.168.1.1\",\"192.168.1.2\"";
    stNegoDnsCnf.stCtrl.usClientId   = 0;
    stNegoDnsCnf.stCtrl.ucOpId       = 0;
    stNegoDnsCnf.stNegotiationDns.ucCid = 1;
    stNegoDnsCnf.enCause                = TAF_PARA_OK;

    stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpPrimDnsAddr   = VOS_TRUE;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpSecDnsAddr   = VOS_TRUE;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr[0] = 192;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr[1] = 168;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr[2] = 1;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr[3] = 1;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr[0]  = 192;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr[1]  = 168;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr[2]  = 1;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr[3]  = 2;

    /* 初始化全局变量 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DNSQUERY_SET;

    /* 桩函数 */
	MOCKER(AT_StopRelTimer)
		.expects(exactly(1))
		.with(eq((VOS_UINT32)ucIndex), any())
		.will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    /* 调用消息入口函数 */
    ulRet = AT_RcvTafPsEvtGetDynamicDnsInfoCnf(ucIndex, &stNegoDnsCnf);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}


TEST_F(Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf, Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf_003)
{
    VOS_UINT32                          ulRet;
    TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU     stNegoDnsCnf;

    /* 初始化变量 */
    ulRet           = VOS_ERROR;
    PS_MEM_SET(&stNegoDnsCnf, 0x00, sizeof(TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU));
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 初始化全局变量 */

    /* 桩函数 */
    MOCKER(AT_StopRelTimer)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用消息入口函数 */
    ulRet = AT_RcvTafPsEvtGetDynamicDnsInfoCnf(ucIndex, &stNegoDnsCnf);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRet);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}


TEST_F(Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf, Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf_004)
{
    VOS_UINT32                          ulRet;
    TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU     stNegoDnsCnf;

    /* 初始化变量 */
    ulRet           = VOS_ERROR;
    PS_MEM_SET(&stNegoDnsCnf, 0x00, sizeof(TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU));

    /* 初始化全局变量 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    /* 桩函数 */
    MOCKER(AT_StopRelTimer)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用消息入口函数 */
    ulRet = AT_RcvTafPsEvtGetDynamicDnsInfoCnf(ucIndex, &stNegoDnsCnf);

    /* 结果验证*/
    EXPECT_EQ(VOS_ERR, ulRet);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}


TEST_F(Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf, Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf_005)
{
    VOS_UINT32                          ulRet;
    TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU     stNegoDnsCnf;

    /* 初始化变量 */
    ulRet           = VOS_ERROR;
    PS_MEM_SET(&stNegoDnsCnf, 0x00, sizeof(TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU));
    stNegoDnsCnf.enCause    = TAF_PARA_UNSPECIFIED_ERROR;

    /* 初始化全局变量 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DNSQUERY_SET;

    /* 桩函数 */
	MOCKER(AT_StopRelTimer)
		.expects(exactly(1))
		.with(eq((VOS_UINT32)ucIndex), any())
		.will(returnValue((VOS_UINT32)VOS_OK));

	MOCKER(At_FormatResultData)
		.stubs()
		.with(any(), eq((VOS_UINT32)AT_ERROR));

    /* 调用消息入口函数 */
    ulRet = AT_RcvTafPsEvtGetDynamicDnsInfoCnf(ucIndex, &stNegoDnsCnf);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRet);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}


TEST_F(Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf, Test_AT_RcvTafPsEvtGetDynamicDnsInfoCnf_006)
{
    VOS_UINT32                          ulRet;
    TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU stNegoDnsCnf;
    VOS_CHAR                           *pcExpactedStr;

    /* 初始化变量 */
    ulRet           = VOS_ERROR;
    PS_MEM_SET(&stNegoDnsCnf, 0x00, sizeof(TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU));

    pcExpactedStr   = "^DNSQUERY: \"192.168.1.1\",";
    stNegoDnsCnf.stCtrl.usClientId   = 0;
    stNegoDnsCnf.stCtrl.ucOpId       = 0;
    stNegoDnsCnf.stNegotiationDns.ucCid = 1;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpPrimDnsAddr  = VOS_TRUE;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpSecDnsAddr   = VOS_FALSE;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr[0] = 192;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr[1] = 168;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr[2] = 1;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr[3] = 1;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr[0]  = 192;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr[1]  = 168;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr[2]  = 1;
    stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr[3]  = 2;

    stNegoDnsCnf.enCause            = TAF_PARA_OK;

    /* 初始化全局变量 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DNSQUERY_SET;

    /* 桩函数 */
    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ucIndex), any())
		.will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    /* 调用消息入口函数 */
    ulRet = AT_RcvTafPsEvtGetDynamicDnsInfoCnf(ucIndex, &stNegoDnsCnf);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}





class Test_AT_RcvTafPsEvtPppDialOrigCnf: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        //MOCKER(OM_AppGreenChannel)
        //    .stubs()
        //    .will(returnValue((VOS_UINT32)VOS_OK));

        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_PS_SetPsCallErrCause(0,TAF_PS_CAUSE_SUCCESS);
    }

};


TEST_F(Test_AT_RcvTafPsEvtPppDialOrigCnf, Test_AT_RcvTafPsEvtPppDialOrigCnf_001)
{
    //参数定义
    TAF_PS_PPP_DIAL_ORIG_CNF_STRU       stPppDialOrigCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ucIndex = 0;
    stPppDialOrigCnf.enCause = TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_IP_CALL_SET;

    //MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_CME_PDP_ACT_LIMIT));

    //调用被测函数
    ulRslt = AT_RcvTafPsEvtPppDialOrigCnf(ucIndex, (VOS_VOID *)&stPppDialOrigCnf);

    //执行检查
    ASSERT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtPppDialOrigCnf, Test_AT_RcvTafPsEvtPppDialOrigCnf_002)
{
    // 变量声明
    TAF_PS_PPP_DIAL_ORIG_CNF_STRU       stCallEvt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    PS_MEM_SET(&stCallEvt, 0x00, sizeof(TAF_PS_PPP_DIAL_ORIG_CNF_STRU));
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    stCallEvt.stCtrl.usClientId      = AT_CLIENT_ID_HSUART;
    stCallEvt.enCause                   = TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSUART_USER;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_IP_CALL_SET;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq((VOS_UINT8)ucIndex), eq((VOS_UINT32)AT_CME_PDP_ACT_LIMIT));

    // 调用被测函数
    ulResult = AT_RcvTafPsEvtPppDialOrigCnf(ucIndex, &stCallEvt);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}


class Test_AT_CheckRptCmdStatus: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_CheckRptCmdStatus, Test_AT_CheckRptCmdStatus_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_RPT_CMD_INDEX_ENUM_UINT8         enRptCmdIndex;
    VOS_UINT8                           aucRptCfg[AT_CURC_RPT_CFG_MAX_SIZE];
    AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8     enRptCtrlType;

    //参数初始化
    enRptCmdIndex   = AT_RPT_CMD_BUTT;

    // 初始化全局变量
    PS_MEM_SET(aucRptCfg, 0xFF, TAF_MMA_RPT_CFG_MAX_SIZE);
    enRptCtrlType   = AT_CMD_RPT_CTRL_BY_CURC;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_CheckRptCmdStatus(aucRptCfg, enRptCtrlType, enRptCmdIndex);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CheckRptCmdStatus, Test_AT_CheckRptCmdStatus_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_RPT_CMD_INDEX_ENUM_UINT8         enRptCmdIndex;
    VOS_UINT8                           aucRptCfg[AT_CURC_RPT_CFG_MAX_SIZE];
    AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8     enRptCtrlType;

    //参数初始化
    enRptCmdIndex   = AT_RPT_CMD_CEND;

    // 初始化全局变量
    PS_MEM_SET(aucRptCfg, 0x00, TAF_MMA_RPT_CFG_MAX_SIZE);
    enRptCtrlType   = AT_CMD_RPT_CTRL_BY_CURC;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_CheckRptCmdStatus(aucRptCfg, enRptCtrlType, enRptCmdIndex);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CheckRptCmdStatus, Test_AT_CheckRptCmdStatus_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_RPT_CMD_INDEX_ENUM_UINT8         enRptCmdIndex;
    VOS_UINT8                           aucRptCfg[AT_CURC_RPT_CFG_MAX_SIZE];
    AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8     enRptCtrlType;

    //参数初始化
    enRptCmdIndex   = AT_RPT_CMD_CEND;

    // 初始化全局变量
    PS_MEM_SET(aucRptCfg, 0, AT_CURC_RPT_CFG_MAX_SIZE);
    aucRptCfg[4] = 0x08;
    enRptCtrlType = AT_CMD_RPT_CTRL_BY_CURC;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_CheckRptCmdStatus(aucRptCfg, enRptCtrlType, enRptCmdIndex);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);
    enRptCmdIndex   = AT_RPT_CMD_CONN;
    ulRet = AT_CheckRptCmdStatus(aucRptCfg, enRptCtrlType, enRptCmdIndex);
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CheckRptCmdStatus, Test_AT_CheckRptCmdStatus_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_RPT_CMD_INDEX_ENUM_UINT8         enRptCmdIndex;
    VOS_UINT8                           aucRptCfg[AT_CURC_RPT_CFG_MAX_SIZE];
    AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8     enRptCtrlType;

    //参数初始化
    enRptCmdIndex   = AT_RPT_CMD_CEND;

    // 初始化全局变量
    PS_MEM_SET(aucRptCfg, 0, AT_CURC_RPT_CFG_MAX_SIZE);
    aucRptCfg[4] = 0x08;
    enRptCtrlType = AT_CMD_RPT_CTRL_BUTT;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_CheckRptCmdStatus(aucRptCfg, enRptCtrlType, enRptCmdIndex);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_RcvTafPsEvtReportDsFlowInd: public ::testing::Test
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


TEST_F(Test_AT_RcvTafPsEvtReportDsFlowInd, Test_AT_RcvTafPsEvtReportDsFlowInd_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    TAF_PS_REPORT_DSFLOW_IND_STRU       stDSFlowReport;
    VOS_UINT8                           aucData[] = {0x00, 0x00, 0x00, 0x00,
                                                     0x00, 0x40, 0x00, 0x00};
    VOS_CHAR                           *pcExpect;

    //参数初始化
    ucIndex     = 0;
    pcExpect    = "\r\n^DSFLOWRPT:00000000,00000000,00000000,0000000000000000,0000000000000000,00000000,00000000\r\n";
    PS_MEM_SET(&stDSFlowReport, 0, sizeof(TAF_PS_REPORT_DSFLOW_IND_STRU));

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), mirror((VOS_UINT8 *)pcExpect, (VOS_UINT32)VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    ulRet = AT_RcvTafPsEvtReportDsFlowInd(ucIndex, &stDSFlowReport);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_ForwardDeliverMsgToTe: public ::testing::Test
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


TEST_F(Test_AT_ForwardDeliverMsgToTe, Test_AT_ForwardDeliverMsgToTe_001)
{
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;

    stEvent.clientId = AT_CLIENT_BUTT;

    AT_ForwardDeliverMsgToTe(&stEvent, &stTsDataInfo);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardDeliverMsgToTe, Test_AT_ForwardDeliverMsgToTe_002)
{
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    AT_GetModemSmsCtxAddrFromClientId(ucIndex)->stCnmiType.CnmiMtType = AT_CNMI_MT_CMTI_TYPE;

    MOCKER(At_SendResultData).expects(exactly(1));

    AT_ForwardDeliverMsgToTe(&stEvent, &stTsDataInfo);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardDeliverMsgToTe, Test_AT_ForwardDeliverMsgToTe_003)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                                                     = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId                                            = AT_BROADCAST_CLIENT_ID_MODEM_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCnmiType.CnmiMtType  = AT_CNMI_MT_NO_SEND_TYPE;

    //MOCKER操作

    //调用被测函数
    AT_ForwardDeliverMsgToTe(&stEvent, &stTsDataInfo);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardDeliverMsgToTe, Test_AT_ForwardDeliverMsgToTe_004)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                            = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId                   = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stEvent.u.stDeliverInfo.enRcvSmAct = MN_MSG_RCVMSG_ACT_STORE;
    stEvent.u.stDeliverInfo.enMemStore = MN_MSG_MEM_STORE_SIM;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCnmiType.CnmiMtType  = AT_CNMI_MT_CMTI_TYPE;

    //MOCKER操作
    MOCKER(At_SendResultData).expects(exactly(1));

    //调用被测函数
    AT_ForwardDeliverMsgToTe(&stEvent, &stTsDataInfo);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_ForwardDeliverMsgToTe, Test_AT_ForwardDeliverMsgToTe_005)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                 = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    stEvent.clientId        = AT_BROADCAST_CLIENT_ID_MODEM_1;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiMtType = AT_CNMI_MT_NO_SEND_TYPE;

    //MOCKER操作

    //调用被测函数
    AT_ForwardDeliverMsgToTe(&stEvent, &stTsDataInfo);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardDeliverMsgToTe, Test_AT_ForwardDeliverMsgToTe_006)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                            = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    stEvent.clientId                   = AT_BROADCAST_CLIENT_ID_MODEM_1;
    stEvent.u.stDeliverInfo.enRcvSmAct = MN_MSG_RCVMSG_ACT_STORE;
    stEvent.u.stDeliverInfo.enMemStore = MN_MSG_MEM_STORE_SIM;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiMtType  = AT_CNMI_MT_CMTI_TYPE;

    //MOCKER操作
    MOCKER(At_SendResultData).expects(exactly(1));

    //调用被测函数
    AT_ForwardDeliverMsgToTe(&stEvent, &stTsDataInfo);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_ForwardStatusReportMsgToTe: public ::testing::Test
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


TEST_F(Test_AT_ForwardStatusReportMsgToTe, Test_AT_ForwardStatusReportMsgToTe_001)
{
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;

    stEvent.clientId = AT_CLIENT_BUTT;

    AT_ForwardStatusReportMsgToTe(&stEvent, &stTsDataInfo);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardStatusReportMsgToTe, Test_AT_ForwardStatusReportMsgToTe_002)
{
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    AT_GetModemSmsCtxAddrFromClientId(ucIndex)->stCnmiType.CnmiDsType = AT_CNMI_DS_CDS_TYPE;

    MOCKER(At_SendResultData).expects(exactly(1));

    AT_ForwardStatusReportMsgToTe(&stEvent, &stTsDataInfo);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardStatusReportMsgToTe, Test_AT_ForwardStatusReportMsgToTe_003)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                            = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId                   = AT_BROADCAST_CLIENT_ID_MODEM_0;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCnmiType.CnmiDsType  = AT_CNMI_DS_NO_SEND_TYPE;

    //MOCKER操作

    //调用被测函数
    AT_ForwardStatusReportMsgToTe(&stEvent, &stTsDataInfo);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardStatusReportMsgToTe, Test_AT_ForwardStatusReportMsgToTe_004)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                            = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId                   = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stEvent.u.stDeliverInfo.enMemStore = MN_MSG_MEM_STORE_NONE;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCnmiType.CnmiDsType  = AT_CNMI_DS_CDS_TYPE;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;

    //MOCKER操作
    MOCKER(At_SendResultData).expects(exactly(1));

    //调用被测函数
    AT_ForwardStatusReportMsgToTe(&stEvent, &stTsDataInfo);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_ForwardStatusReportMsgToTe, Test_AT_ForwardStatusReportMsgToTe_005)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                            = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    stEvent.clientId                   = AT_BROADCAST_CLIENT_ID_MODEM_1;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiDsType  = AT_CNMI_DS_NO_SEND_TYPE;

    //MOCKER操作

    //调用被测函数
    AT_ForwardStatusReportMsgToTe(&stEvent, &stTsDataInfo);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardStatusReportMsgToTe, Test_AT_ForwardStatusReportMsgToTe_006)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                            = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    stEvent.clientId                   = AT_BROADCAST_CLIENT_ID_MODEM_1;
    stEvent.u.stDeliverInfo.enMemStore = MN_MSG_MEM_STORE_NONE;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiDsType  = AT_CNMI_DS_CDS_TYPE;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;

    //MOCKER操作
    MOCKER(At_SendResultData).expects(exactly(1));

    //调用被测函数
    AT_ForwardStatusReportMsgToTe(&stEvent, &stTsDataInfo);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

class Test_AT_ForwardCbMsgToTe: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		MOCKER(At_PrintReportData)
			.stubs()
			.will(returnValue((TAF_UINT16)0));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ForwardCbMsgToTe, Test_AT_ForwardCbMsgToTe_001)
{
    MN_MSG_EVENT_INFO_STRU               stEvent;

    stEvent.clientId = AT_CLIENT_BUTT;

    AT_ForwardCbMsgToTe(&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardCbMsgToTe, Test_AT_ForwardCbMsgToTe_002)
{
    MN_MSG_EVENT_INFO_STRU                 stEvent;
    VOS_UINT8                              ucIndex;

	memset(&stEvent, 0, sizeof(stEvent));

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;


    MOCKER(MN_MSG_DecodeCbmPage).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_SendResultData).expects(exactly(1));

    AT_ForwardCbMsgToTe(&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ForwardCbMsgToTe, Test_AT_ForwardCbMsgToTe_003)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                            = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId                   = AT_BROADCAST_CLIENT_ID_MODEM_0;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;

    //MOCKER操作
    MOCKER(MN_MSG_DecodeCbmPage).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_SendResultData).expects(exactly(1));

    //调用被测函数
    AT_ForwardCbMsgToTe(&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_ForwardCbMsgToTe, Test_AT_ForwardCbMsgToTe_004)
{
    //参数定义
    MN_MSG_EVENT_INFO_STRU               stEvent;
    VOS_UINT8                            ucIndex;

    //参数初始化
    ucIndex                            = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    stEvent.clientId                   = AT_BROADCAST_CLIENT_ID_MODEM_1;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;

    //MOCKER操作
    MOCKER(MN_MSG_DecodeCbmPage).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_SendResultData).expects(exactly(1));

    //调用被测函数
    AT_ForwardCbMsgToTe(&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
#endif


class Test_At_TAFPbMsgProc: public ::testing::Test
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


TEST_F(Test_At_TAFPbMsgProc, Test_At_TAFPbMsgProc_001)
{
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen = sizeof(SI_PB_EVENT_INFO_STRU);
    SI_PB_EVENT_INFO_STRU               stEvent;

    pData = (TAF_UINT8 *)malloc(usLen);
    stEvent.ClientId = AT_CLIENT_BUTT;

    At_TAFPbMsgProc(pData, usLen);

	free(pData);
    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_PhEventProc: public ::testing::Test
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



class Test_At_ChgMnErrCodeToAt: public ::testing::Test
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


TEST_F(Test_At_ChgMnErrCodeToAt,Test_At_ChgMnErrCodeToAt_001)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulMnErrorCode;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ulMnErrorCode = MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;

    //MOCKER操作

    //调用被测函数
    ulRslt = At_ChgMnErrCodeToAt(ucIndex, ulMnErrorCode);

    //执行检查
    EXPECT_EQ(AT_CMS_INVALID_TEXT_MODE_PARAMETER, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ChgMnErrCodeToAt,Test_At_ChgMnErrCodeToAt_002)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulMnErrorCode;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ulMnErrorCode = MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;

    //MOCKER操作

    //调用被测函数
    ulRslt = At_ChgMnErrCodeToAt(ucIndex, ulMnErrorCode);

    //执行检查
    EXPECT_EQ(AT_CMS_INVALID_PDU_MODE_PARAMETER, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_ChgMnErrCodeToAt,Test_At_ChgMnErrCodeToAt_003)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulMnErrorCode;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ulMnErrorCode = MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;

    //MOCKER操作

    //调用被测函数
    ulRslt = At_ChgMnErrCodeToAt(ucIndex, ulMnErrorCode);

    //执行检查
    EXPECT_EQ(AT_CMS_INVALID_TEXT_MODE_PARAMETER, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_ChgMnErrCodeToAt,Test_At_ChgMnErrCodeToAt_004)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulMnErrorCode;
    VOS_UINT32                          ulRslt;

    //参数初始化
    ulMnErrorCode = MN_ERR_CLASS_SMS_MSGLEN_OVERFLOW;

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;

    //MOCKER操作

    //调用被测函数
    ulRslt = At_ChgMnErrCodeToAt(ucIndex, ulMnErrorCode);

    //执行检查
    EXPECT_EQ(AT_CMS_INVALID_PDU_MODE_PARAMETER, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif





class Test_AT_RcvTafPsEvtGetCidSdfInfoCnf: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};


TEST_F(Test_AT_RcvTafPsEvtGetCidSdfInfoCnf, Test_AT_RcvTafPsEvtGetCidSdfInfoCnf_001)
{
    // 变量声明
    TAF_PS_EVT_STRU                    *pstEvent;
	VOS_UINT16                          usLength;

    // 参数初始化
    usLength = sizeof(TAF_PS_EVT_STRU) + sizeof(TAF_CTRL_STRU) - 4;

	pstEvent = (TAF_PS_EVT_STRU*)malloc(usLength);

    pstEvent->stHeader.ulMsgName          = MN_CALLBACK_PS_CALL;
    pstEvent->ulEvtId                     = ID_EVT_TAF_PS_GET_CID_SDF_CNF;

    // 初始化全局变量

    // MOCKER操作
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    AT_RcvTafPsEvt(pstEvent);

	free(pstEvent);

    // 执行检查
    GlobalMockObject::verify();
}



class Test_AT_RcvTafPsEvtSetEpsQosInfoCnf: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_AT_RcvTafPsEvtSetEpsQosInfoCnf, Test_AT_RcvTafPsEvtSetEpsQosInfoCnf_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    TAF_PS_SET_EPS_QOS_INFO_CNF_STRU    stSetEpsqosInfoCnf;

    // 参数初始化
    PS_MEM_SET(&stSetEpsqosInfoCnf, 0, sizeof(TAF_PS_SET_EPS_QOS_INFO_CNF_STRU));
    stSetEpsqosInfoCnf.enCause          = TAF_PS_CAUSE_SUCCESS;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGEQOS_SET;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    ulRslt = AT_RcvTafPsEvtSetEpsQosInfoCnf(ucIndex, &stSetEpsqosInfoCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_VSIM)

class Test_AT_RcvDrvAgentHvpdhSetCnf: public ::testing::Test
{
public:
    DRV_AGENT_MSG_STRU                 *pMsg ;
    VOS_UINT16                          usLength;
    DRV_AGENT_HVPDH_CNF_STRU           *pstEvent;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 申请消息，并初始化 */
        usLength        = sizeof(DRV_AGENT_MSG_STRU) + sizeof(DRV_AGENT_HVPDH_CNF_STRU) - 4;
        pMsg            = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLength);
        PS_MEM_SET(pMsg, 0, usLength);

        pstEvent        = (DRV_AGENT_HVPDH_CNF_STRU  *)pMsg->aucContent;

    }
    void TearDown()
    {
        if (VOS_NULL_PTR != pMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pMsg);
        }
    }};

TEST_F(Test_AT_RcvDrvAgentHvpdhSetCnf, Test_AT_RcvDrvAgentHvpdhSetCnf_001)
{
    // 变量声明
    VOS_UINT32      ulResult;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    ulResult = AT_RcvDrvAgentHvpdhSetCnf(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentHvpdhSetCnf, Test_AT_RcvDrvAgentHvpdhSetCnf_002)
{
    // 变量声明
    VOS_UINT32      ulResult;

    // 参数初始化
    pstEvent->stAtAppCtrl.usClientId   = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstEvent->stAtAppCtrl.ucOpId       = 0;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = AT_RcvDrvAgentHvpdhSetCnf(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentHvpdhSetCnf, Test_AT_RcvDrvAgentHvpdhSetCnf_003)
{
    // 变量声明
    VOS_UINT32      ulResult;
    VOS_UINT8       ucIndex;

    // 参数初始化
    pstEvent->stAtAppCtrl.usClientId   = 1;
    pstEvent->stAtAppCtrl.ucOpId       = 0;

    ucIndex = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
		.with(any(), outBoundP((TAF_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulResult = AT_RcvDrvAgentHvpdhSetCnf(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentHvpdhSetCnf, Test_AT_RcvDrvAgentHvpdhSetCnf_004)
{
    // 变量声明
    VOS_UINT32      ulResult;
    VOS_UINT8       ucIndex;

    // 参数初始化
    pstEvent->stAtAppCtrl.usClientId   = 1;
    pstEvent->stAtAppCtrl.ucOpId       = 0;
    pstEvent->enResult                 = DRV_AGENT_HVPDH_AUTH_UNDO;

    ucIndex = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVPDH_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
		.with(any(), outBoundP((TAF_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvDrvAgentHvpdhSetCnf(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvDrvAgentHvpdhSetCnf, Test_AT_RcvDrvAgentHvpdhSetCnf_005)
{
    // 变量声明
    VOS_UINT32      ulResult;
    VOS_UINT8       ucIndex;

    // 参数初始化
    pstEvent->stAtAppCtrl.usClientId   = 1;
    pstEvent->stAtAppCtrl.ucOpId       = 0;
    pstEvent->enResult                 = DRV_AGENT_HVPDH_NO_ERROR;

    ucIndex = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVPDH_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
		.with(any(), outBoundP((TAF_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvDrvAgentHvpdhSetCnf(pMsg);


    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}

#endif





class Test_AT_RcvNvManufactureExtSetCnf: public ::testing::Test
{
public:
    DRV_AGENT_MSG_STRU                 *pMsg ;
    VOS_UINT16                          usLength;
    DRV_AGENT_NVMANUFACTUREEXT_SET_CNF_STRU           *pstEvent;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 申请消息，并初始化 */
        usLength        = sizeof(DRV_AGENT_MSG_STRU) + sizeof(DRV_AGENT_NVMANUFACTUREEXT_SET_CNF_STRU) - 4;
        pMsg            = (DRV_AGENT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLength);
        PS_MEM_SET(pMsg, 0, usLength);

        pstEvent        = (DRV_AGENT_NVMANUFACTUREEXT_SET_CNF_STRU  *)pMsg->aucContent;

    }
    void TearDown()
    {
        if (VOS_NULL_PTR != pMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pMsg);
        }
    }};

TEST_F(Test_AT_RcvNvManufactureExtSetCnf, Test_AT_RcvNvManufactureExtSetCnf_001)
{
    // 变量声明
    VOS_UINT32      ulResult;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    ulResult = AT_RcvNvManufactureExtSetCnf(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvNvManufactureExtSetCnf, Test_AT_RcvNvManufactureExtSetCnf_002)
{
    // 变量声明
    VOS_UINT32      ulResult;

    // 参数初始化
    pstEvent->stAtAppCtrl.usClientId   = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstEvent->stAtAppCtrl.ucOpId       = 0;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = AT_RcvNvManufactureExtSetCnf(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvNvManufactureExtSetCnf, Test_AT_RcvNvManufactureExtSetCnf_003)
{
    // 变量声明
    VOS_UINT32      ulResult;
    VOS_UINT8       ucIndex;

    // 参数初始化
    pstEvent->stAtAppCtrl.usClientId   = 1;
    pstEvent->stAtAppCtrl.ucOpId       = 0;

    ucIndex = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
		.with(any(), outBoundP((TAF_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulResult = AT_RcvNvManufactureExtSetCnf(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvNvManufactureExtSetCnf, Test_AT_RcvNvManufactureExtSetCnf_004)
{
    // 变量声明
    VOS_UINT32      ulResult;
    VOS_UINT8       ucIndex;

    // 参数初始化
    pstEvent->stAtAppCtrl.usClientId   = 1;
    pstEvent->stAtAppCtrl.ucOpId       = 0;
    pstEvent->ulRslt                 = NV_OK;

    ucIndex = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVMANUFACTUREEXT_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
		.with(any(), outBoundP((TAF_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvNvManufactureExtSetCnf(pMsg);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvNvManufactureExtSetCnf, Test_AT_RcvNvManufactureExtSetCnf_005)
{
    // 变量声明
    VOS_UINT32      ulResult;
    VOS_UINT8       ucIndex;

    // 参数初始化
    pstEvent->stAtAppCtrl.usClientId   = 1;
    pstEvent->stAtAppCtrl.ucOpId       = 0;
    pstEvent->ulRslt                 = NV_OK;

    ucIndex = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVMANUFACTUREEXT_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = AT_RcvNvManufactureExtSetCnf(pMsg);


    // 执行检查
    EXPECT_EQ(VOS_OK, ulResult);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_ECALL)

class Test_At_ProcVcReportEcallStateEvent: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                         = 0;
    }
    void TearDown()
    {
    }

protected:
    APP_VC_EVENT_INFO_STRU              stVcEvtInfo;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_At_ProcVcReportEcallStateEvent, Test_At_ProcVcReportEcallStateEvent_001)
{
    /* 初始化变量 */
    stVcEvtInfo.enEcallState = APP_VC_ECALL_MSD_TRANSMITTING_FAIL;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_ProcVcReportEcallStateEvent(ucIndex, &stVcEvtInfo);

    /* 结果验证 */
    ASSERT_NE(strlen("\r\n^ECLSTAT: 1\r\n"), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ProcVcReportEcallStateEvent, Test_At_ProcVcReportEcallStateEvent_002)
{
    /* 初始化变量 */
    stVcEvtInfo.enEcallState = APP_VC_ECALL_PSAP_MSD_REQUIRETRANSMITTING;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_ProcVcReportEcallStateEvent(ucIndex, &stVcEvtInfo);

    /* 结果验证 */
    ASSERT_NE(strlen("\r\n^ECLSTAT: 1\r\n"), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ProcVcReportEcallStateEvent, Test_At_ProcVcReportEcallStateEvent_003)
{
    stVcEvtInfo.enEcallState = APP_VC_ECALL_MSD_TRANSMITTING_START;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_ProcVcReportEcallStateEvent(ucIndex, &stVcEvtInfo);

    /* 结果验证 */
    ASSERT_EQ(strlen("\r\n^ECLSTAT: 1\r\n"), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_At_VcEventProc: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                         = 0;

    }
    void TearDown()
    {
    }

protected:
    VOS_UINT8                           ucIndex;
    APP_VC_EVENT_INFO_STRU              stVcEvt;
    APP_VC_EVENT_ENUM_U32               enEvent;
};


TEST_F(Test_At_VcEventProc, Test_At_VcEventProc_001)
{
    /* 变量定义 */


    /* 初始化变量 */
    enEvent                             = APP_VC_EVT_ECALL_TRANS_STATUS;

    MOCKER(At_ProcVcReportEcallStateEvent)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_VcEventProc(ucIndex, &stVcEvt, enEvent);

    /* 结果验证 */

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_VcEventProc, Test_At_VcEventProc_002)
{
    /* 变量定义 */


    /* 初始化变量 */
    enEvent                             = APP_VC_EVT_SET_ECALL_CFG;

    MOCKER(At_ProcVcSetEcallCfgEvent)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_VcEventProc(ucIndex, &stVcEvt, enEvent);

    /* 结果验证 */

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}



class Test_At_ProcVcSetEcallCfgEvent: public ::testing::Test
{
public:
    void SetUp()
    {
    }
    void TearDown()
    {
    }

protected:
    APP_VC_EVENT_INFO_STRU              stVcEvtInfo;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_At_ProcVcSetEcallCfgEvent, Test_At_ProcVcSetEcallCfgEvent_001)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 调用被测函数 */
    ulRst = At_ProcVcSetEcallCfgEvent(ucIndex, &stVcEvtInfo);

    /* 结果验证 */
    ASSERT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ProcVcSetEcallCfgEvent, Test_At_ProcVcSetEcallCfgEvent_002)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_1;

    /* 调用被测函数 */
    ulRst = At_ProcVcSetEcallCfgEvent(ucIndex, &stVcEvtInfo);

    /* 结果验证 */
    ASSERT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ProcVcSetEcallCfgEvent, Test_At_ProcVcSetEcallCfgEvent_003)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    ucIndex = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;

    /* 调用被测函数 */
    ulRst = At_ProcVcSetEcallCfgEvent(ucIndex, &stVcEvtInfo);

    /* 结果验证 */
    ASSERT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ProcVcSetEcallCfgEvent, Test_At_ProcVcSetEcallCfgEvent_004)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    ucIndex = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLCFG_SET;
    stVcEvtInfo.bSuccess = VOS_TRUE;

    /* 调用被测函数 */
    ulRst = At_ProcVcSetEcallCfgEvent(ucIndex, &stVcEvtInfo);

    /* 结果验证 */
    ASSERT_EQ(VOS_OK, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ProcVcSetEcallCfgEvent, Test_At_ProcVcSetEcallCfgEvent_005)
{
    /* 变量定义 */
    VOS_UINT32                          ulRst;

    /* 初始化变量 */
    ucIndex = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLCFG_SET;
    stVcEvtInfo.bSuccess = VOS_FALSE;

    /* 调用被测函数 */
    ulRst = At_ProcVcSetEcallCfgEvent(ucIndex, &stVcEvtInfo);

    /* 结果验证 */
    ASSERT_EQ(VOS_OK, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_At_RcvTafCallQryEcallInfoCnf: public ::testing::Test
{
public:
    void SetUp()
    {
        At_PidInit(VOS_IP_INITIAL);

        ulEventLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU);
        pstEvent = (MN_AT_IND_EVT_STRU *)malloc(ulEventLen);
        PS_MEM_SET(pstEvent, 0, ulEventLen);
        pstEcallInfo = (MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU *)&pstEvent->aucContent[sizeof(MN_CALL_EVENT_ENUM_U32)];
    }
    void TearDown()
    {
        free(pstEvent);
    }

protected:
    MN_AT_IND_EVT_STRU                                     *pstEvent;
    MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU                    *pstEcallInfo;
    VOS_UINT32                                              ulEventLen;
    AT_PAR_CMD_ELEMENT_STRU                                 stCmdElememt;
    VOS_UINT32                                              ulRst;
};



TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_001)
{
    /* 变量定义 */

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .will(returnValue(AT_FAILURE));

    /* 调用被测函数 */
    ulRst = At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_002)
{
    /* 变量定义 */

    /* 初始化变量 */
    pstEcallInfo->usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;

    /* 调用被测函数 */
    ulRst = At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_003)
{
    /* 变量定义 */

    /* 初始化变量 */
    pstEcallInfo->usClientId = AT_BROADCAST_CLIENT_ID_MODEM_1;

    /* 调用被测函数 */
    ulRst = At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_004)
{
    /* 变量定义 */

    /* 初始化变量 */
    pstEcallInfo->usClientId = 0;
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;

    /* 调用被测函数 */
    ulRst = At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(VOS_ERR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_005)
{

    pstEcallInfo->usClientId = 0;
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_CECALL_QRY;
    pstEcallInfo->stEcallInfo.ucNumOfEcall = 1;
    pstEcallInfo->stEcallInfo.astEcallInfos[0].enEcallType = MN_CALL_TYPE_TEST;

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(strlen("+CECALL: 0"), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_006)
{
    pstEcallInfo->usClientId = 0;
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_CECALL_QRY;
    pstEcallInfo->stEcallInfo.ucNumOfEcall = 1;
    pstEcallInfo->stEcallInfo.astEcallInfos[0].enEcallType = MN_CALL_TYPE_RECFGURATION;

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(strlen("+CECALL: 1"), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_007)
{
    pstEcallInfo->usClientId = 0;
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_CECALL_QRY;
    pstEcallInfo->stEcallInfo.ucNumOfEcall = 1;
    pstEcallInfo->stEcallInfo.astEcallInfos[0].enEcallType = MN_CALL_TYPE_MIEC;

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(strlen("+CECALL: 2"), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_008)
{
    pstEcallInfo->usClientId = 0;
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_CECALL_QRY;
    pstEcallInfo->stEcallInfo.ucNumOfEcall = 1;
    pstEcallInfo->stEcallInfo.astEcallInfos[0].enEcallType = MN_CALL_TYPE_AIEC;

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(strlen("+CECALL: 3"), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvTafCallQryEcallInfoCnf, Test_At_RcvTafCallQryEcallInfoCnf_009)
{
    pstEcallInfo->usClientId = 0;
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_CECALL_QRY;
    pstEcallInfo->stEcallInfo.ucNumOfEcall = 1;
    pstEcallInfo->stEcallInfo.astEcallInfos[0].enEcallType = MN_CALL_TYPE_BUTT;

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_RcvTafCallQryEcallInfoCnf(pstEvent);

    /* 结果验证 */
    ASSERT_EQ(strlen("+CECALL: "), gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif


class Test_At_VcMsgProc: public ::testing::Test
{
    void SetUp()
    {

    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_VcMsgProc, Test_At_VcMsgProc_001)
{
    /* 变量定义 */
    MN_AT_IND_EVT_STRU                  stData;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
		.stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    At_VcMsgProc(&stData, 0);

    /* 结果验证 */

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_At_CheckOrigCnfCallType: public ::testing::Test
{
    void SetUp()
    {

    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_CheckOrigCnfCallType, Test_At_CheckOrigCnfCallType_001)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_VOICE;

    enRst = At_CheckOrigCnfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckOrigCnfCallType, Test_At_CheckOrigCnfCallType_002)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_EMERGENCY;

    enRst = At_CheckOrigCnfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckOrigCnfCallType, Test_At_CheckOrigCnfCallType_003)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_MIEC;

    enRst = At_CheckOrigCnfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckOrigCnfCallType, Test_At_CheckOrigCnfCallType_004)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_AIEC;

    enRst = At_CheckOrigCnfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckOrigCnfCallType, Test_At_CheckOrigCnfCallType_005)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_TEST;

    enRst = At_CheckOrigCnfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckOrigCnfCallType, Test_At_CheckOrigCnfCallType_006)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_RECFGURATION;

    enRst = At_CheckOrigCnfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckOrigCnfCallType, Test_At_CheckOrigCnfCallType_007)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_BUTT;

    enRst = At_CheckOrigCnfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_FALSE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_At_CheckReportCendCallType: public ::testing::Test
{
    void SetUp()
    {

    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_CheckReportCendCallType, Test_At_CheckReportCendCallType_001)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_VOICE;

    enRst = At_CheckReportCendCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportCendCallType, Test_At_CheckReportCendCallType_002)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_EMERGENCY;

    enRst = At_CheckReportCendCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportCendCallType, Test_At_CheckReportCendCallType_003)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_MIEC;

    enRst = At_CheckReportCendCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportCendCallType, Test_At_CheckReportCendCallType_004)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_AIEC;

    enRst = At_CheckReportCendCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportCendCallType, Test_At_CheckReportCendCallType_005)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_TEST;

    enRst = At_CheckReportCendCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportCendCallType, Test_At_CheckReportCendCallType_006)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_RECFGURATION;

    enRst = At_CheckReportCendCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportCendCallType, Test_At_CheckReportCendCallType_007)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_PSAP_ECALL;

    enRst = At_CheckReportCendCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}



TEST_F(Test_At_CheckReportCendCallType, Test_At_CheckReportCendCallType_008)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_BUTT;

    enRst = At_CheckReportCendCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_FALSE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_At_CheckReportOrigCallType: public ::testing::Test
{
    void SetUp()
    {

    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_CheckReportOrigCallType, Test_At_CheckReportOrigCallType_001)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_VOICE;

    enRst = At_CheckReportOrigCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportOrigCallType, Test_At_CheckReportOrigCallType_002)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_EMERGENCY;

    enRst = At_CheckReportOrigCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportOrigCallType, Test_At_CheckReportOrigCallType_003)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_BUTT;

    enRst = At_CheckReportOrigCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_FALSE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_At_CheckReportConfCallType: public ::testing::Test
{
    void SetUp()
    {

    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_CheckReportConfCallType, Test_At_CheckReportConfCallType_001)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_VOICE;

    enRst = At_CheckReportConfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportConfCallType, Test_At_CheckReportConfCallType_002)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_EMERGENCY;

    enRst = At_CheckReportConfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportConfCallType, Test_At_CheckReportConfCallType_003)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_MIEC;

    enRst = At_CheckReportConfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportConfCallType, Test_At_CheckReportConfCallType_004)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_AIEC;

    enRst = At_CheckReportConfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportConfCallType, Test_At_CheckReportConfCallType_005)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_TEST;

    enRst = At_CheckReportConfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportConfCallType, Test_At_CheckReportConfCallType_006)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_RECFGURATION;

    enRst = At_CheckReportConfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckReportConfCallType, Test_At_CheckReportConfCallType_007)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_PSAP_ECALL;

    enRst = At_CheckReportConfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}



TEST_F(Test_At_CheckReportConfCallType, Test_At_CheckReportConfCallType_008)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_BUTT;

    enRst = At_CheckReportConfCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_FALSE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_At_CheckUartRingTeCallType: public ::testing::Test
{
    void SetUp()
    {

    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_CheckUartRingTeCallType, Test_At_CheckUartRingTeCallType_001)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_VOICE;

    enRst = At_CheckUartRingTeCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckUartRingTeCallType, Test_At_CheckUartRingTeCallType_002)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_EMERGENCY;

    enRst = At_CheckUartRingTeCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckUartRingTeCallType, Test_At_CheckUartRingTeCallType_003)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_MIEC;

    enRst = At_CheckUartRingTeCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckUartRingTeCallType, Test_At_CheckUartRingTeCallType_004)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_AIEC;

    enRst = At_CheckUartRingTeCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckUartRingTeCallType, Test_At_CheckUartRingTeCallType_005)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_TEST;

    enRst = At_CheckUartRingTeCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckUartRingTeCallType, Test_At_CheckUartRingTeCallType_006)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_RECFGURATION;

    enRst = At_CheckUartRingTeCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckUartRingTeCallType, Test_At_CheckUartRingTeCallType_007)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_PSAP_ECALL;

    enRst = At_CheckUartRingTeCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_TRUE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}



TEST_F(Test_At_CheckUartRingTeCallType, Test_At_CheckUartRingTeCallType_008)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    PS_BOOL_ENUM_UINT8                  enRst;

    enCallType = MN_CALL_TYPE_BUTT;

    enRst = At_CheckUartRingTeCallType(enCallType);

    /* 结果验证 */
    ASSERT_EQ(PS_FALSE, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_At_ChangeEcallTypeToCallType: public ::testing::Test
{
public:
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};


TEST_F(Test_At_ChangeEcallTypeToCallType, Test_At_ChangeEcallTypeToCallType_001)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_TYPE_ENUM_U8                enNewCallType;

    enCallType = MN_CALL_TYPE_TEST;

    At_ChangeEcallTypeToCallType(enCallType, &enNewCallType);

    /* 结果验证 */
    ASSERT_EQ(MN_CALL_TYPE_VOICE, enNewCallType);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ChangeEcallTypeToCallType, Test_At_ChangeEcallTypeToCallType_002)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_TYPE_ENUM_U8                enNewCallType;

    enCallType = MN_CALL_TYPE_RECFGURATION;

    At_ChangeEcallTypeToCallType(enCallType, &enNewCallType);

    /* 结果验证 */
    ASSERT_EQ(MN_CALL_TYPE_VOICE, enNewCallType);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ChangeEcallTypeToCallType, Test_At_ChangeEcallTypeToCallType_003)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_TYPE_ENUM_U8                enNewCallType;

    enCallType = MN_CALL_TYPE_PSAP_ECALL;

    At_ChangeEcallTypeToCallType(enCallType, &enNewCallType);

    /* 结果验证 */
    ASSERT_EQ(MN_CALL_TYPE_VOICE, enNewCallType);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ChangeEcallTypeToCallType, Test_At_ChangeEcallTypeToCallType_004)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_TYPE_ENUM_U8                enNewCallType;

    enCallType = MN_CALL_TYPE_MIEC;

    At_ChangeEcallTypeToCallType(enCallType, &enNewCallType);

    /* 结果验证 */
    ASSERT_EQ(MN_CALL_TYPE_EMERGENCY, enNewCallType);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ChangeEcallTypeToCallType, Test_At_ChangeEcallTypeToCallType_005)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_TYPE_ENUM_U8                enNewCallType;

    enCallType = MN_CALL_TYPE_AIEC;

    At_ChangeEcallTypeToCallType(enCallType, &enNewCallType);

    /* 结果验证 */
    ASSERT_EQ(MN_CALL_TYPE_EMERGENCY, enNewCallType);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_ChangeEcallTypeToCallType, Test_At_ChangeEcallTypeToCallType_006)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_TYPE_ENUM_U8                enNewCallType;

    enCallType = MN_CALL_TYPE_VOICE;

    At_ChangeEcallTypeToCallType(enCallType, &enNewCallType);

    /* 结果验证 */
    ASSERT_EQ(MN_CALL_TYPE_VOICE, enNewCallType);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


/*****************************以下NAS2负责******************************/



class Test_At_PbMsgProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_PbMsgProc, Test_At_PbMsgProc_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           aucMsg[] = {0x00,0x00,0x00,0x00,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x01,0x00,0x00,0x08,0x02,0x00,0x00,0x03,0x00,0x00,0x00,0xff,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfa,0x00,0x0e,0x00,0x28,0x00,0x14,0x00,0x0e,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x0e,0x00,0x28,0x00,0x28,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x10,0x60,0x46,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x60,0x46,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0xb8,0x2a,0x71,0x30,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0xb8,0x2a,0x71,0x30,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0xa0,0x36,0x71,0x30,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0xa0,0x36,0x71,0x30,0x6f,0x00,0x00,0x00,0x40,0x6f,0x00,0x00,0xc1,0x01,0x00,0x00,0x08,0x3a,0x2d,0x31,0x34,0x56,0x2e,0x30,0xc1,0x01,0x00,0x00,0xf8,0x6e,0x58,0x31,0xd8,0x29,0xf6,0x30,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xa0,0x4a,0x2e,0x30,0x10,0x6f,0x58,0x31,0xd8,0x29,0xf6,0x30,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xa0,0x4a,0x2e,0x30,0xd8,0x29,0xf6,0x30,0xdc,0x29,0xf6,0x30,0x74,0xf6,0x2c,0x30,0x01,0x00,0x00,0x00,0xb8,0x2a,0x2e,0x30,0x65,0x00,0x00,0x00,0x98,0xb9,0x70,0x30,0x00,0x00,0x00,0x00,0x8a,0x00,0x00,0x00,0x10,0xf0,0xbf,0x31,0xa4,0xb7,0x71,0x30,0x65,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x48,0x2f,0xee,0x30,0x98,0x66,0x11,0x31,0xa0,0x00,0x00,0x00,0xb8,0x40,0x4b,0x31,0xa0,0x36,0x71,0x30,0x01,0x00,0x00,0x00,0x3c,0xbf,0xbf,0x31,0xa0,0x36,0x71,0x30,0x74,0xf6,0x2c,0x30,0xf8,0x6e,0x58,0x31,0x90,0x2e,0x2e,0x30,0xa0,0xc9,0x95,0x30,0x40,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x48,0x2a,0xf6,0x30,0x9c,0x72,0x48,0x31,0xa0,0x36,0x71,0x30,0xc8,0x3e,0x2d,0x31,0x34,0x56,0x2e,0x30,0x00,0x00,0x00,0x00,0xa0,0x00,0x00,0x00,0x78,0xb1,0x77,0x31,0x24,0x16,0x2d,0x30,0x01,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x3f,0x2d,0x31,0x34,0x56,0x2e,0x30,0x3e,0x00,0x00,0x00,0xa0,0xc9,0x95,0x30,0x40,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x48,0x2a,0xf6,0x30,0x3e,0x00,0x00,0x00,0x88,0x18,0x2d,0x30,0x84,0xf3,0x2e,0x30,0x00,0x00,0x00,0x00,0xe0,0x07,0x00,0x00,0x04,0xa2,0x2c,0x31,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x34,0x09,0xca,0x01,0x34,0x09,0xca,0x01,0x68,0x8b,0x2a,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x00,0x00,0x28,0x19,0x2d,0x30,0x28,0xf7,0x2c,0x30,0x48,0x37,0x71,0x30,0x04,0x00,0x00,0x00,0x5c,0xc8,0x2a,0x30,0x00,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x3e,0x00,0x00,0x00,0x70,0x03,0x2d,0x30,0x48,0x2a,0xf6,0x30,0x00,0x00,0x95,0x30};
    MsgBlock                            *pstMsg;

    /*参数初始化*/
    pstMsg = (MsgBlock *)aucMsg;

    /* 初始化全局变量;*/
    memset(&gstPBATInfo, 0, sizeof(gstPBATInfo));

    // MOCKER操作;

    /* 调用被测函数 */
    At_PbMsgProc(pstMsg);

    // 执行检查
    EXPECT_EQ(0x000e, gstPBATInfo.usNameMaxLen);
    EXPECT_EQ(0x0028, gstPBATInfo.usNumMaxLen);
    EXPECT_EQ(0x00fa, gstPBATInfo.usTotal);
    EXPECT_EQ(0x0028, gstPBATInfo.usAnrNumLen);
    EXPECT_EQ(0x0028, gstPBATInfo.usEmailLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_PbMsgProc, Test_At_PbMsgProc_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           aucMsg[] = {0x00,0x00,0x00,0x00,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x01,0x00,0x00,0x08,0x02,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfa,0x00,0xfa,0x00,0x0e,0x00,0x28,0x00,0x28,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    MsgBlock                            *pstMsg;
    VOS_CHAR                            *pcExpactedStr;

    /* 初始化变量 */
    pcExpactedStr = "+CPBR: (1-250),40,14";

    ////参数初始化
    pstMsg = (MsgBlock *)aucMsg;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBR2_SET;
    g_stParseContext[ucIndex].pstCmdElement = &gstCpbrCmdInfo;
    gstPBATInfo.usNameMaxLen = 0x000e;
    gstPBATInfo.usNumMaxLen  = 0x0028;
    gstPBATInfo.usTotal      = 0x00fa;
    gstPBATInfo.usAnrNumLen  = 0x0028;
    gstPBATInfo.usEmailLen   = 0x0028;

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
           .stubs()
           .with(any(), outBoundP((VOS_UINT8 *)&ucIndex,VOS_UINT32(sizeof(ucIndex))))
           .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    //// 调用被测函数
    At_PbMsgProc((MsgBlock*)pstMsg);

    // 执行检查
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();

}


TEST_F(Test_At_PbMsgProc, Test_At_PbMsgProc_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucMsg[] = {0x00,0x00,0x00,0x00,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x01,0x00,0x00,0x08,0x02,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfa,0x00,0x0e,0x00,0x28,0x00,0x14,0x00,0x0e,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x0e,0x00,0x28,0x00,0x28,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x10,0x60,0x46,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x60,0x46,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0xb8,0x2a,0x71,0x30,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0xb8,0x2a,0x71,0x30,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0xa0,0x36,0x71,0x30,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0xa0,0x36,0x71,0x30,0x6f,0x00,0x00,0x00,0x40,0x6f,0x00,0x00,0xc1,0x01,0x00,0x00,0x08,0x3a,0x2d,0x31,0x34,0x56,0x2e,0x30,0xc1,0x01,0x00,0x00,0xf8,0x6e,0x58,0x31,0xd8,0x29,0xf6,0x30,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xa0,0x4a,0x2e,0x30,0x10,0x6f,0x58,0x31,0xd8,0x29,0xf6,0x30,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xa0,0x4a,0x2e,0x30,0xd8,0x29,0xf6,0x30,0xdc,0x29,0xf6,0x30,0x74,0xf6,0x2c,0x30,0x01,0x00,0x00,0x00,0xb8,0x2a,0x2e,0x30,0x65,0x00,0x00,0x00,0x98,0xb9,0x70,0x30,0x00,0x00,0x00,0x00,0x8a,0x00,0x00,0x00,0x10,0xf0,0xbf,0x31,0xa4,0xb7,0x71,0x30,0x65,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x48,0x2f,0xee,0x30,0x98,0x66,0x11,0x31,0xa0,0x00,0x00,0x00,0xb8,0x40,0x4b,0x31,0xa0,0x36,0x71,0x30,0x01,0x00,0x00,0x00,0x3c,0xbf,0xbf,0x31,0xa0,0x36,0x71,0x30,0x74,0xf6,0x2c,0x30,0xf8,0x6e,0x58,0x31,0x90,0x2e,0x2e,0x30,0xa0,0xc9,0x95,0x30,0x40,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x48,0x2a,0xf6,0x30,0x9c,0x72,0x48,0x31,0xa0,0x36,0x71,0x30,0xc8,0x3e,0x2d,0x31,0x34,0x56,0x2e,0x30,0x00,0x00,0x00,0x00,0xa0,0x00,0x00,0x00,0x78,0xb1,0x77,0x31,0x24,0x16,0x2d,0x30,0x01,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x3f,0x2d,0x31,0x34,0x56,0x2e,0x30,0x3e,0x00,0x00,0x00,0xa0,0xc9,0x95,0x30,0x40,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x48,0x2a,0xf6,0x30,0x3e,0x00,0x00,0x00,0x88,0x18,0x2d,0x30,0x84,0xf3,0x2e,0x30,0x00,0x00,0x00,0x00,0xe0,0x07,0x00,0x00,0x04,0xa2,0x2c,0x31,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x34,0x09,0xca,0x01,0x34,0x09,0xca,0x01,0x68,0x8b,0x2a,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x00,0x00,0x28,0x19,0x2d,0x30,0x28,0xf7,0x2c,0x30,0x48,0x37,0x71,0x30,0x04,0x00,0x00,0x00,0x5c,0xc8,0x2a,0x30,0x00,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x3e,0x00,0x00,0x00,0x70,0x03,0x2d,0x30,0x48,0x2a,0xf6,0x30,0x00,0x00,0x95,0x30};
    MsgBlock                            *pstMsg;
    VOS_CHAR                            *pcLogStr1;
    VOS_CHAR                            *pcLogStr2;
    VOS_CHAR                            *pcLogStr3;
    VOS_CHAR                            *pcLogStr4;
    MN_APP_PB_AT_CNF_STRU               *pstAppPbMsg;

    ////参数初始化
    pcLogStr1                            = "At_PbMsgProc pEvent->ClientId";
    pcLogStr2                            = "At_PbMsgProc PBEventType";
    pcLogStr3                            = "At_PbMsgProc Event Error";
    pcLogStr4                            = "At_PbMsgProc At_ClientIdToUserId FAILURE";
    pstMsg                              = (MsgBlock *)aucMsg;
    pstAppPbMsg                         = (MN_APP_PB_AT_CNF_STRU *)aucMsg;

    //// 初始化全局变量;
    memset(&gstPBATInfo, 0, sizeof(gstPBATInfo));

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
           .stubs()
           .will(returnValue((TAF_UINT32)AT_FAILURE));

    //// 调用被测函数
    At_PbMsgProc((MsgBlock *)pstMsg);

    // 执行检查

    GlobalMockObject::verify();

}


TEST_F(Test_At_PbMsgProc, Test_At_PbMsgProc_004)
{
    // 变量声明
    VOS_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT8                           aucMsg[] = {0x00,0x00,0x00,0x00,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x01,0x00,0x00,0x08,0x02,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfa,0x00,0x0e,0x00,0x28,0x00,0x14,0x00,0x0e,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x0e,0x00,0x28,0x00,0x28,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x10,0x60,0x46,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x60,0x46,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0xb8,0x2a,0x71,0x30,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0xb8,0x2a,0x71,0x30,0x13,0x00,0x09,0x80,0x94,0xca,0x45,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0xa0,0x36,0x71,0x30,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x94,0xca,0x45,0x31,0xa0,0x36,0x71,0x30,0x6f,0x00,0x00,0x00,0x40,0x6f,0x00,0x00,0xc1,0x01,0x00,0x00,0x08,0x3a,0x2d,0x31,0x34,0x56,0x2e,0x30,0xc1,0x01,0x00,0x00,0xf8,0x6e,0x58,0x31,0xd8,0x29,0xf6,0x30,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xa0,0x4a,0x2e,0x30,0x10,0x6f,0x58,0x31,0xd8,0x29,0xf6,0x30,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xa0,0x4a,0x2e,0x30,0xd8,0x29,0xf6,0x30,0xdc,0x29,0xf6,0x30,0x74,0xf6,0x2c,0x30,0x01,0x00,0x00,0x00,0xb8,0x2a,0x2e,0x30,0x65,0x00,0x00,0x00,0x98,0xb9,0x70,0x30,0x00,0x00,0x00,0x00,0x8a,0x00,0x00,0x00,0x10,0xf0,0xbf,0x31,0xa4,0xb7,0x71,0x30,0x65,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x48,0x2f,0xee,0x30,0x98,0x66,0x11,0x31,0xa0,0x00,0x00,0x00,0xb8,0x40,0x4b,0x31,0xa0,0x36,0x71,0x30,0x01,0x00,0x00,0x00,0x3c,0xbf,0xbf,0x31,0xa0,0x36,0x71,0x30,0x74,0xf6,0x2c,0x30,0xf8,0x6e,0x58,0x31,0x90,0x2e,0x2e,0x30,0xa0,0xc9,0x95,0x30,0x40,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x48,0x2a,0xf6,0x30,0x9c,0x72,0x48,0x31,0xa0,0x36,0x71,0x30,0xc8,0x3e,0x2d,0x31,0x34,0x56,0x2e,0x30,0x00,0x00,0x00,0x00,0xa0,0x00,0x00,0x00,0x78,0xb1,0x77,0x31,0x24,0x16,0x2d,0x30,0x01,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x3f,0x2d,0x31,0x34,0x56,0x2e,0x30,0x3e,0x00,0x00,0x00,0xa0,0xc9,0x95,0x30,0x40,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x48,0x2a,0xf6,0x30,0x3e,0x00,0x00,0x00,0x88,0x18,0x2d,0x30,0x84,0xf3,0x2e,0x30,0x00,0x00,0x00,0x00,0xe0,0x07,0x00,0x00,0x04,0xa2,0x2c,0x31,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x34,0x09,0xca,0x01,0x34,0x09,0xca,0x01,0x68,0x8b,0x2a,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x00,0x00,0x28,0x19,0x2d,0x30,0x28,0xf7,0x2c,0x30,0x48,0x37,0x71,0x30,0x04,0x00,0x00,0x00,0x5c,0xc8,0x2a,0x30,0x00,0x00,0x00,0x00,0x48,0x2a,0xf6,0x30,0x3e,0x00,0x00,0x00,0x70,0x03,0x2d,0x30,0x48,0x2a,0xf6,0x30,0x00,0x00,0x95,0x30};
    MsgBlock                            *pstMsg;
    VOS_CHAR                            *pcLogStr;

    ////参数初始化
    pcLogStr                            = "At_PbMsgProc: AT_BROADCAST_INDEX.";
    pstMsg = (MsgBlock *)aucMsg;

    //// 初始化全局变量;
    memset(&gstPBATInfo, 0, sizeof(gstPBATInfo));

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
           .stubs()
           .with(any(), outBoundP((VOS_UINT8 *)&ucIndex,VOS_UINT32(sizeof(ucIndex))))
           .will(returnValue((TAF_UINT32)AT_SUCCESS));

    //// 调用被测函数
    At_PbMsgProc((MsgBlock*)pstMsg);

    // 执行检查

    GlobalMockObject::verify();

}



class Test_At_QryParaRspProc: public ::testing::Test
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




class Test_At_SmsStubRspProc: public ::testing::Test
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


TEST_F(Test_At_SmsStubRspProc,Test_At_SmsStubRspProc_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           OpId;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    ////参数初始化
    ucIndex                                    = 0;
    OpId                                       = 0;
    ucIndex                                    = 0;
    stEvent.u.stResult.ulErrorCode            = MN_ERR_NO_ERROR;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CMSTUB_SET;

    //// MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //// 调用被测函数
    At_SmsStubRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_SmsStubRspProc,Test_At_SmsStubRspProc_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           OpId;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    ////参数初始化
    ucIndex                                    = 0;
    OpId                                       = 0;
    ucIndex                                    = 0;
    stEvent.u.stResult.ulErrorCode            = MN_ERR_NO_ERROR;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CURRENT_OPT_BUTT;

    //// MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(never());

    MOCKER(AT_StopRelTimer)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    //// 调用被测函数
    At_SmsStubRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    GlobalMockObject::verify();

}


TEST_F(Test_At_SmsStubRspProc,Test_At_SmsStubRspProc_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           OpId;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    ////参数初始化
    ucIndex                                    = 0;
    OpId                                       = 0;
    ucIndex                                    = 0;
    stEvent.u.stResult.ulErrorCode            = MN_ERR_UNSPECIFIED;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CMSTUB_SET;

    //// MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_UNKNOWN_ERROR));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //// 调用被测函数
    At_SmsStubRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}





class Test_At_CsAllCallInfoEvtCnfProc: public ::testing::Test
{
public:
    VOS_UINT8                            ucIndex;
    MN_AT_IND_EVT_STRU                  *pstData;
    MN_CALL_INFO_QRY_CNF_STRU           *pstCallInfos;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;

        pstData = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_QRY_CNF_STRU));

        if (VOS_NULL_PTR == pstData)
        {
            return;
        }
        pstCallInfos = (MN_CALL_INFO_QRY_CNF_STRU *)(pstData->aucContent);

        PS_MEM_SET(pstData, 0, sizeof(MN_AT_IND_EVT_STRU));
        PS_MEM_SET(pstCallInfos, 0, sizeof(MN_CALL_INFO_QRY_CNF_STRU));
    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pstData)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstData);
        }
    }
};


TEST_F(Test_At_CsAllCallInfoEvtCnfProc,Test_At_CsAllCallInfoEvtCnfProc_001)
{
    // 参数定义
    VOS_UINT16                                  usLen;

    // 参数初始化
    usLen                                       = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_QRY_CNF_STRU);
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // 调用被测函数
    At_CsAllCallInfoEvtCnfProc((MN_AT_IND_EVT_STRU *)pstData, usLen);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CsAllCallInfoEvtCnfProc,Test_At_CsAllCallInfoEvtCnfProc_002)
{
   // 参数定义
    VOS_UINT16                                  usLen;
    // 参数初始化
    usLen                                       = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_QRY_CNF_STRU);
    pstCallInfos->ucNumOfCalls                  = 1;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt      = AT_CMD_CLCC_SET;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(),outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_ProcSetClccResult)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_CsAllCallInfoEvtCnfProc((MN_AT_IND_EVT_STRU *)pstData, usLen);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CsAllCallInfoEvtCnfProc,Test_At_CsAllCallInfoEvtCnfProc_003)
{
   // 参数定义
    VOS_UINT16                                  usLen;
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CPAS,
                                                             At_SetCpasPara, AT_SET_PARA_TIME,
                                                             VOS_NULL_PTR,AT_QRY_PARA_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                             (VOS_UINT8*)"+CPAS",VOS_NULL_PTR};

     // 参数初始化
    usLen                                       = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_QRY_CNF_STRU);
    pstCallInfos->ucNumOfCalls                  = 8;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt      = AT_CMD_CPAS_SET;
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));


    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CME_UNKNOWN));

    // 调用被测函数
    At_CsAllCallInfoEvtCnfProc((MN_AT_IND_EVT_STRU *)pstData, usLen);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CsAllCallInfoEvtCnfProc,Test_At_CsAllCallInfoEvtCnfProc_004)
{
   // 参数定义
    VOS_UINT16                                  usLen;
    char                                        acExpectedResult[] = "+CPAS: 0";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CPAS,
                                                             At_SetCpasPara, AT_SET_PARA_TIME,
                                                             VOS_NULL_PTR,AT_QRY_PARA_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                             (VOS_UINT8*)"+CPAS",VOS_NULL_PTR};

    // 参数初始化
    usLen                                       = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_QRY_CNF_STRU);
    pstCallInfos->ucNumOfCalls                  = 0;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt      = AT_CMD_CPAS_SET;
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(),any());

    // 调用被测函数
    At_CsAllCallInfoEvtCnfProc((MN_AT_IND_EVT_STRU *)pstData, usLen);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



TEST_F(Test_At_CsAllCallInfoEvtCnfProc,Test_At_CsAllCallInfoEvtCnfProc_005)
{
   // 参数定义
    char                                        acExpectedResult[] = "+CPAS: 3";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CPAS,
                                                             At_SetCpasPara, AT_SET_PARA_TIME,
                                                             VOS_NULL_PTR,AT_QRY_PARA_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                             (VOS_UINT8*)"+CPAS",VOS_NULL_PTR};


    VOS_UINT16                                  usLen;
    // 参数初始化
    usLen                                       = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_QRY_CNF_STRU);
    pstCallInfos->ucNumOfCalls                  = 1;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt      = AT_CMD_CPAS_SET;
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;
    pstCallInfos->astCallInfos[0].enCallState = MN_CALL_S_INCOMING;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(),any());

    // 调用被测函数
    At_CsAllCallInfoEvtCnfProc((MN_AT_IND_EVT_STRU *)pstData, usLen);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CsAllCallInfoEvtCnfProc,Test_At_CsAllCallInfoEvtCnfProc_006)
{
    // 参数定义
    VOS_UINT16                                  usLen;

    // 参数初始化
    usLen                                       = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_QRY_CNF_STRU);
    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt      = AT_CMD_INVALID;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // 调用被测函数
    At_CsAllCallInfoEvtCnfProc((MN_AT_IND_EVT_STRU *)pstData, usLen);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


class Test_At_ProcSetClccResult: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                         = 0;
        gstAtSendData.usBufLen          = 0;
    }

    void TearDown()
    {
        gstAtSendData.usBufLen          = 0;
    }
};


TEST_F(Test_At_ProcSetClccResult,Test_At_ProcSetClccResult_001)
{
   // 参数定义
    VOS_UINT8                                   ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU                   stCallInfos = {0};
    VOS_CHAR                                    aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1] = "15002107919";
    AT_CLCC_MODE_ENUM_U8                        enClccMode;
    VOS_UINT32                                  ulLen;
    char                                        acExpectedResult[] = "+CLCC: 0,0,0,0,0,\"15002107919\",128,\"\",\r\n+CLCC: 0,0,0,0,0,\"15002107919\",128,\"\",";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CPAS,
                                                             At_SetCpasPara, AT_SET_PARA_TIME,
                                                             VOS_NULL_PTR,AT_QRY_PARA_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                             (VOS_UINT8*)"+CLCC",VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 2;

    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MO;
    stCallInfos.astCallInfos[0].stConnectNumber.ucNumLen = 1;
    stCallInfos.astCallInfos[1].enCallDir       = MN_CALL_DIR_MO;
    stCallInfos.astCallInfos[1].stConnectNumber.ucNumLen = 1;

    stCallInfos.astCallInfos[0].stCallNumber.ucNumLen    = 0;

    enClccMode                                  = 0;

    ulLen                                       = 12;
    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(2))
        .with(any(),outBoundP((AT_CLCC_MODE_ENUM_U8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    MOCKER(AT_BcdNumberToAscii)
    .expects(exactly(2))
    .with(any(),any(), outBoundP((VOS_CHAR *)aucAsciiNum, (VOS_UINT32)sizeof(aucAsciiNum)))
    .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    At_ProcSetClccResult(ucNumOfCalls, (MN_CALL_INFO_QRY_CNF_STRU *)&stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_ProcSetClccResult,Test_At_ProcSetClccResult_002)
{
   // 参数定义
    VOS_UINT8                                   ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU                   stCallInfos = {0};
    VOS_CHAR                                   aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1] = "15002107919";
    AT_CLCC_MODE_ENUM_U8                        enClccMode;
    VOS_UINT32                                  ulLen;
    char                                        acExpectedResult[] = "+CLCC: 0,0,0,0,0,\"15002107919\",128,\"\",";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CPAS,
                                                             At_SetCpasPara, AT_SET_PARA_TIME,
                                                             VOS_NULL_PTR,AT_QRY_PARA_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                             (VOS_UINT8*)"+CLCC",VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 1;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MO;
    stCallInfos.astCallInfos[0].stConnectNumber.ucNumLen = 0;
    stCallInfos.astCallInfos[0].stCalledNumber.ucNumLen    = 1;

    enClccMode                                  = 0;

    ulLen                                       = 12;

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(1))
        .with(any(),outBoundP((AT_CLCC_MODE_ENUM_U8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    MOCKER(AT_BcdNumberToAscii)
    .expects(exactly(1))
    .with(any(),any(), outBoundP((VOS_CHAR *)aucAsciiNum, (VOS_UINT32)sizeof(aucAsciiNum)))
    .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    At_ProcSetClccResult(ucNumOfCalls, (MN_CALL_INFO_QRY_CNF_STRU *)&stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_ProcSetClccResult,Test_At_ProcSetClccResult_003)
{
   // 参数定义
    VOS_UINT8                           ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU                   stCallInfos = {0};
    AT_CLCC_MODE_ENUM_U8                        enClccMode;
    VOS_UINT32                                  ulLen;
    char                                        acExpectedResult[] = "+CLCC: 0,0,0,0,0,\"\",128";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CPAS,
                                                             At_SetCpasPara, AT_SET_PARA_TIME,
                                                             VOS_NULL_PTR,AT_QRY_PARA_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                             (VOS_UINT8*)"+CLCC",VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 1;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MO;
    stCallInfos.astCallInfos[0].stConnectNumber.ucNumLen = 0;
    stCallInfos.astCallInfos[0].stCallNumber.ucNumLen    = 0;

    enClccMode                                  = 0;

    ulLen                                       = 12;

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(1))
        .with(any(),outBoundP((AT_CLCC_MODE_ENUM_U8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    // 调用被测函数
    At_ProcSetClccResult(ucNumOfCalls, (MN_CALL_INFO_QRY_CNF_STRU *)&stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_ProcSetClccResult,Test_At_ProcSetClccResult_004)
{
   // 参数定义
    VOS_UINT8                           ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU                   stCallInfos = {0};
    VOS_CHAR                                   aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1] = "15002107919";
    AT_CLCC_MODE_ENUM_U8                        enClccMode;
    VOS_UINT32                                  ulLen;
    char                                        acExpectedResult[] = "+CLCC: 0,1,0,0,0,\"15002107919\",128,\"\",";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CPAS,
                                                             At_SetCpasPara, AT_SET_PARA_TIME,
                                                             VOS_NULL_PTR,AT_QRY_PARA_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                             (VOS_UINT8*)"+CLCC",VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 1;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MT;
    stCallInfos.astCallInfos[0].stCallNumber.ucNumLen    = 1;

    enClccMode                                  = 0;

    ulLen                                       = 12;
    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(1))
        .with(any(),outBoundP((AT_CLCC_MODE_ENUM_U8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    MOCKER(AT_BcdNumberToAscii)
    .expects(exactly(1))
    .with(any(),any(), outBoundP((VOS_CHAR *)aucAsciiNum, (VOS_UINT32)sizeof(aucAsciiNum)))
    .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    At_ProcSetClccResult(ucNumOfCalls, (MN_CALL_INFO_QRY_CNF_STRU *)&stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_ProcSetClccResult,Test_At_ProcSetClccResult_005)
{
   // 参数定义
    VOS_UINT8                           ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU                   stCallInfos = {0};
    AT_CLCC_MODE_ENUM_U8                        enClccMode;
    VOS_UINT32                                  ulLen;
    char                                        acExpectedResult[] = "+CLCC: 0,1,0,0,0,\"\",128";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CPAS,
                                                             At_SetCpasPara, AT_SET_PARA_TIME,
                                                             VOS_NULL_PTR,AT_QRY_PARA_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                             AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                             (VOS_UINT8*)"+CLCC",VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 1;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MT;
    stCallInfos.astCallInfos[0].stCallNumber.ucNumLen    = 0;

    enClccMode                                  = 0;

    ulLen                                       = 12;
    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(1))
        .with(any(),outBoundP((AT_CLCC_MODE_ENUM_U8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));


    // 调用被测函数
    At_ProcSetClccResult(ucNumOfCalls,(MN_CALL_INFO_QRY_CNF_STRU *) &stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}




class Test_At_CmdCnfMsgProc: public ::testing::Test
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


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_001)
{
    // 变量声明
    VOS_UINT32                            ulRst;
    VOS_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    AT_CMD_CNF_EVENT                    stCmdCnf;
    VOS_CHAR                           *pcLogStr1;
    VOS_CHAR                           *pcLogStr2;

    ////参数初始化
    ucIndex                                    = 0;

    stCmdCnf.clientId                        = 0;
    stCmdCnf.opId                            = 0;
    stCmdCnf.ulErrorCode                    = TAF_CS_CAUSE_STATE_ERROR;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CDUR_READ;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CME_INCORRECT_PARAMETERS));


    //// 调用被测函数
    At_CmdCnfMsgProc((TAF_UINT8 *)&stCmdCnf, sizeof(stCmdCnf));

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_002)
{
    // 变量声明
    VOS_UINT32                            ulRst;
    VOS_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    AT_CMD_CNF_EVENT                    stCmdCnf;
    VOS_CHAR                           *pcLogStr1;
    VOS_CHAR                           *pcLogStr2;

    ////参数初始化
    ucIndex                                    = 0;

    stCmdCnf.clientId                        = 0;
    stCmdCnf.opId                            = 0;
    stCmdCnf.ulErrorCode                    = TAF_CS_CAUSE_UNKNOWN;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CDUR_READ;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CME_UNKNOWN));

    //// 调用被测函数
    At_CmdCnfMsgProc((TAF_UINT8 *)&stCmdCnf, sizeof(stCmdCnf));

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_003)
{
    // 变量声明
    VOS_UINT32                            ulRst;
    VOS_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    AT_CMD_CNF_EVENT                    stCmdCnf;
    VOS_CHAR                           *pcLogStr1;
    VOS_CHAR                           *pcLogStr2;

    //参数初始化
    ucIndex                                    = 0;

    stCmdCnf.clientId                        = 0;
    stCmdCnf.opId                            = 0;
    stCmdCnf.ulErrorCode                    = TAF_CS_CAUSE_STATE_ERROR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CDUR_READ;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    // MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CME_INCORRECT_PARAMETERS));


    // 调用被测函数
    At_CmdCnfMsgProc((TAF_UINT8 *)&stCmdCnf, sizeof(stCmdCnf));

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_004)
{
    // 变量声明
    VOS_UINT32                            ulRst;
    VOS_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    AT_CMD_CNF_EVENT                    stCmdCnf;
    VOS_CHAR                           *pcLogStr1;
    VOS_CHAR                           *pcLogStr2;

    ////参数初始化
    ucIndex                                    = 0;

    stCmdCnf.clientId                        = 0;
    stCmdCnf.opId                            = 0;
    stCmdCnf.ulErrorCode                    = MN_ERR_CLASS_SMS_UPDATE_USIM;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CSCA_READ;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CMS_U_SIM_BUSY));

    //// 调用被测函数
    At_CmdCnfMsgProc((TAF_UINT8 *)&stCmdCnf, sizeof(stCmdCnf));

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_005)
{
    // 变量声明
    VOS_UINT32                            ulRst;
    VOS_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    AT_CMD_CNF_EVENT                    stCmdCnf;
    VOS_CHAR                           *pcLogStr1;
    VOS_CHAR                           *pcLogStr2;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CSCA,
        At_SetCscaPara,     AT_SET_PARA_TIME, At_QryCscaPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,      AT_NOT_SET_TIME,
        AT_RRETURN_CODE_BUTT, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CSCA",    (VOS_UINT8*)"(sca),(0-255)"};

    ////参数初始化
    ucIndex                                    = 0;

    stCmdCnf.clientId                        = 0;
    stCmdCnf.opId                            = 0;
    stCmdCnf.ulErrorCode                    = MN_ERR_CLASS_SMS_FILE_NOEXIST;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CSCA_READ;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    g_stParseContext[ucIndex].pstCmdElement  = &stCmdInfo;

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CMS_UNKNOWN_ERROR));

    //// 调用被测函数
    At_CmdCnfMsgProc((TAF_UINT8 *)&stCmdCnf, sizeof(stCmdCnf));

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_006)
{
    // 变量声明
    VOS_UINT32                            ulRst;
    VOS_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    AT_CMD_CNF_EVENT                    stCmdCnf;
    VOS_CHAR                           *pcLogStr1;
    VOS_CHAR                           *pcLogStr2;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CSCA,
        At_SetCscaPara,     AT_SET_PARA_TIME, At_QryCscaPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,      AT_NOT_SET_TIME,
        AT_RRETURN_CODE_BUTT, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CSCA",    (VOS_UINT8*)"(sca),(0-255)"};

    ////参数初始化
    ucIndex                                    = 0;


    stCmdCnf.clientId                        = 0;
    stCmdCnf.opId                            = 0;
    stCmdCnf.ulErrorCode                    = MN_ERR_CLASS_SMS_INVALID_REC;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CSCA_READ;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    g_stParseContext[ucIndex].pstCmdElement  = &stCmdInfo;

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CMS_UNKNOWN_ERROR));


    //// 调用被测函数
    At_CmdCnfMsgProc((TAF_UINT8 *)&stCmdCnf, sizeof(stCmdCnf));

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_007)
{
    // 变量声明
    VOS_UINT32                            ulRst;
    VOS_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    AT_CMD_CNF_EVENT                    stCmdCnf;
    VOS_CHAR                           *pcLogStr1;
    VOS_CHAR                           *pcLogStr2;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CSCA,
        At_SetCscaPara,     AT_SET_PARA_TIME, At_QryCscaPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,      AT_NOT_SET_TIME,
        AT_RRETURN_CODE_BUTT, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CSCA",    (VOS_UINT8*)"(sca),(0-255)"};

    ////参数初始化
    ucIndex                                    = 0;

    stCmdCnf.clientId                        = 0;
    stCmdCnf.opId                            = 0;
    stCmdCnf.ulErrorCode                    = MN_ERR_CLASS_SMS_EMPTY_REC;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CSCA_READ;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    g_stParseContext[ucIndex].pstCmdElement  = &stCmdInfo;

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CMS_UNKNOWN_ERROR));



    //// 调用被测函数
    At_CmdCnfMsgProc((TAF_UINT8 *)&stCmdCnf, sizeof(stCmdCnf));

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_008)
{
    // 变量声明
    VOS_UINT32                            ulRst;
    VOS_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    AT_CMD_CNF_EVENT                    stCmdCnf;
    VOS_CHAR                           *pcLogStr1;
    VOS_CHAR                           *pcLogStr2;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CSCA,
        At_SetCscaPara,     AT_SET_PARA_TIME, At_QryCscaPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,      AT_NOT_SET_TIME,
        AT_RRETURN_CODE_BUTT, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CSCA",    (VOS_UINT8*)"(sca),(0-255)"};

    ////参数初始化
    ucIndex                                    = 0;

    stCmdCnf.clientId                        = 0;
    stCmdCnf.opId                            = 0;
    stCmdCnf.ulErrorCode                    = MN_ERR_CLASS_SMS_FILE_NOEXIST;

    //// 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt     = AT_CMD_CSCA_READ;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    g_stParseContext[ucIndex].pstCmdElement  = &stCmdInfo;

    //// MOCKER操作;
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CMS_UNKNOWN_ERROR));

    //// 调用被测函数
    At_CmdCnfMsgProc((TAF_UINT8 *)&stCmdCnf, sizeof(stCmdCnf));

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ((VOS_UINT16)0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();

}



TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_011)
{
    //参数定义
    AT_CMD_CNF_EVENT                    stCmdCnfEvt;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                 = 0;
    stCmdCnfEvt.clientId    = AT_CLIENT_TAB_PCUI_INDEX;
    stCmdCnfEvt.ulErrorCode = TAF_CS_CAUSE_NO_CALL_ID;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_D_CS_VOICE_CALL_SET;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    //MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_ERROR));

    //调用被测函数
    At_CmdCnfMsgProc((VOS_UINT8 *)&stCmdCnfEvt, sizeof(AT_CMD_CNF_EVENT));

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CmdCnfMsgProc, At_CmdCnfMsgProc_012)
{
    //参数定义
    AT_CMD_CNF_EVENT                    stCmdCnfEvt;
    VOS_UINT8                           ucIndex;

    //参数初始化
    ucIndex                 = 0;
    stCmdCnfEvt.clientId    = AT_CLIENT_TAB_PCUI_INDEX;
    stCmdCnfEvt.ulErrorCode = TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING;

    //相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_H_SET;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    //MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((VOS_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CME_UNKNOWN));

    //调用被测函数
    At_CmdCnfMsgProc((VOS_UINT8 *)&stCmdCnfEvt, sizeof(AT_CMD_CNF_EVENT));

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




class Test_At_SetRcvPathRspProc: public ::testing::Test
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


TEST_F(Test_At_SetRcvPathRspProc,Test_At_SetRcvPathRspProc_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化
    ucIndex  = 1;
    pstEvent = &stEvent;
    pstEvent->u.stDeleteInfo.bSuccess = TAF_FALSE;
    // 相关全局变量初始化

    // MOCKER操作;
    MOCKER(At_ChgMnErrCodeToAt)
    .expects(exactly(1))
    .will(returnValue((VOS_UINT32)AT_CMS_INVALID_TEXT_MODE_PARAMETER));

    MOCKER(At_FormatResultData)
    .expects(exactly(1));

    // 调用被测函数
    At_SetRcvPathRspProc(ucIndex,(MN_MSG_EVENT_INFO_STRU *)pstEvent);

    // 执行检查
    //ASSERT_EQ(AT_MSG_DELETE_ALL, gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_SetRcvPathRspProc,Test_At_SetRcvPathRspProc_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化
    ucIndex  = 1;
    pstEvent = &stEvent;
    pstEvent->u.stDeleteInfo.bSuccess = TAF_TRUE;
    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMS_SET;
    gastAtClientTab[ucIndex].AtSmsData.bWaitForNvStorageStatus = TAF_FALSE;

    // MOCKER操作;
    MOCKER(At_PrintSetCpmsRsp)
    .expects(exactly(1));

    // 调用被测函数
    At_SetRcvPathRspProc(ucIndex,(MN_MSG_EVENT_INFO_STRU *)pstEvent);

    // 执行检查
    //ASSERT_EQ(AT_MSG_DELETE_ALL, gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_SetRcvPathRspProc,Test_At_SetRcvPathRspProc_003)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化
    ucIndex  = 1;
    pstEvent = &stEvent;
    pstEvent->u.stDeleteInfo.bSuccess = TAF_TRUE;
    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSMS_SET;
    g_stParseContext[ucIndex].pstCmdElement = &gstCpmsCmdInfo;
    // MOCKER操作;
    /*MOCKER(At_sprintf)
    .expects(exactly(1));*/
    MOCKER(At_PrintCsmsInfo)
    .expects(exactly(1));
    MOCKER(At_FormatResultData)
    .expects(exactly(1));

    // 调用被测函数
    At_SetRcvPathRspProc(ucIndex,(MN_MSG_EVENT_INFO_STRU *)pstEvent);

    // 执行检查
    //ASSERT_EQ(AT_MSG_DELETE_ALL, gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_SetRcvPathRspProc,Test_At_SetRcvPathRspProc_004)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化
    ucIndex  = 1;
    pstEvent = &stEvent;
    pstEvent->u.stDeleteInfo.bSuccess = TAF_TRUE;
    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGF_SET;
    AT_GetModemSmsCtxAddrFromClientId(ucIndex)->stCnmiType.CnmiTmpModeType = 1;
    // MOCKER操作;
    MOCKER(At_HandleSmtBuffer)
    .expects(exactly(1));
    MOCKER(At_FormatResultData)
    .expects(exactly(1));

    // 调用被测函数
    At_SetRcvPathRspProc(ucIndex,(MN_MSG_EVENT_INFO_STRU *)pstEvent);

    // 执行检查
    //ASSERT_EQ(AT_MSG_DELETE_ALL, gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SetRcvPathRspProc,Test_At_SetRcvPathRspProc_005)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_APP5_INDEX;
    pstEvent                            = &stEvent;
    pstEvent->u.stDeleteInfo.bSuccess   = TAF_FALSE;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId = MODEM_ID_1;

    // MOCKER操作;
    MOCKER(At_ChgMnErrCodeToAt)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_CMS_INVALID_TEXT_MODE_PARAMETER));
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_SetRcvPathRspProc(ucIndex,(MN_MSG_EVENT_INFO_STRU *)pstEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F(Test_At_SetRcvPathRspProc,Test_At_SetRcvPathRspProc_006)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_APP5_INDEX;
    pstEvent                            = &stEvent;
    pstEvent->u.stDeleteInfo.bSuccess   = TAF_TRUE;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt                      = AT_CMD_CPMS_SET;
    gastAtClientTab[ucIndex].AtSmsData.bWaitForNvStorageStatus  = TAF_FALSE;
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    // MOCKER操作;
    MOCKER(At_PrintSetCpmsRsp)
        .expects(exactly(1));

    // 调用被测函数
    At_SetRcvPathRspProc(ucIndex,(MN_MSG_EVENT_INFO_STRU *)pstEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_SetRcvPathRspProc,Test_At_SetRcvPathRspProc_007)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_APP5_INDEX;
    pstEvent                            = &stEvent;
    pstEvent->u.stDeleteInfo.bSuccess   = TAF_TRUE;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt                      = AT_CMD_CSMS_SET;
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_stParseContext[ucIndex].pstCmdElement                     = &gstCpmsCmdInfo;

    // MOCKER操作;
    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/
    MOCKER(At_PrintCsmsInfo)
        .expects(exactly(1));
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_SetRcvPathRspProc(ucIndex,(MN_MSG_EVENT_INFO_STRU *)pstEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_SetRcvPathRspProc,Test_At_SetRcvPathRspProc_008)
{
    // 参数定义
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化
    ucIndex                             = AT_CLIENT_ID_APP5;
    pstEvent                            = &stEvent;
    pstEvent->u.stDeleteInfo.bSuccess   = TAF_TRUE;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt                          = AT_CMD_CMGF_SET;
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId       = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiTmpModeType = 1;

    // MOCKER操作;
    MOCKER(At_HandleSmtBuffer)
        .expects(exactly(1));
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_SetRcvPathRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)pstEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_SmsInitResultProc: public ::testing::Test
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


TEST_F(Test_At_SmsInitResultProc,Test_At_SmsInitResultProc_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stInitResultInfo.ulTotalSmRec = 30;
    stEvent.u.stInitResultInfo.ulUsedSmRec  = 20;

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数
    At_SmsInitResultProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_EQ(30, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.stUsimStorage.ulTotalRec);
    ASSERT_EQ(20, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.stUsimStorage.ulUsedRec);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SmsInitResultProc,Test_At_SmsInitResultProc_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stInitResultInfo.ulTotalSmRec                     = 30;
    stEvent.u.stInitResultInfo.ulUsedSmRec                      = 20;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    // MOCKER操作;

    // 调用被测函数
    At_SmsInitResultProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_EQ(30, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.stUsimStorage.ulTotalRec);
    ASSERT_EQ(20, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.stUsimStorage.ulUsedRec);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_SmsRcvMsgPathChangeProc: public ::testing::Test
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


TEST_F(Test_At_SmsRcvMsgPathChangeProc,Test_At_SmsRcvMsgPathChangeProc_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stRcvMsgPathInfo.enRcvSmAct                       = 1;
    stEvent.u.stRcvMsgPathInfo.enSmMemStore                     = 2;
    stEvent.u.stRcvMsgPathInfo.enRcvStaRptAct                   = 3;
    stEvent.u.stRcvMsgPathInfo.enStaRptMemStore                 = 4;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    // MOCKER操作;

    // 调用被测函数
    At_SmsRcvMsgPathChangeProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_EQ(1, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.stRcvPath.enRcvSmAct);
    ASSERT_EQ(2, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.stRcvPath.enSmMemStore);
    ASSERT_EQ(3, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.stRcvPath.enRcvStaRptAct);
    ASSERT_EQ(4, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.stRcvPath.enStaRptMemStore);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SmsRcvMsgPathChangeProc,Test_At_SmsRcvMsgPathChangeProc_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stRcvMsgPathInfo.enRcvSmAct                       = 10;
    stEvent.u.stRcvMsgPathInfo.enSmMemStore                     = 20;
    stEvent.u.stRcvMsgPathInfo.enRcvStaRptAct                   = 30;
    stEvent.u.stRcvMsgPathInfo.enStaRptMemStore                 = 40;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    // MOCKER操作;

    // 调用被测函数
    At_SmsRcvMsgPathChangeProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_EQ(10, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.stRcvPath.enRcvSmAct);
    ASSERT_EQ(20, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.stRcvPath.enSmMemStore);
    ASSERT_EQ(30, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.stRcvPath.enRcvStaRptAct);
    ASSERT_EQ(40, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.stRcvPath.enStaRptMemStore);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_SmsStorageListProc: public ::testing::Test
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


TEST_F(Test_At_SmsStorageListProc,Test_At_SmsStorageListProc_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stStorageListInfo.enMemStroe                      = MN_MSG_MEM_STORE_SIM;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    // MOCKER操作;

    // 调用被测函数
    At_SmsStorageListProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(TAF_FALSE, gastAtClientTab[ucIndex].AtSmsData.bWaitForUsimStorageStatus);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_SmsStorageListProc,Test_At_SmsStorageListProc_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stStorageListInfo.enMemStroe                      = MN_MSG_MEM_STORE_NV;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    // MOCKER操作;

    // 调用被测函数
    At_SmsStorageListProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(TAF_FALSE, gastAtClientTab[ucIndex].AtSmsData.bWaitForNvStorageStatus);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SmsStorageListProc,Test_At_SmsStorageListProc_003)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stStorageListInfo.enMemStroe                      = MN_MSG_MEM_STORE_SIM;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    // MOCKER操作;

    // 调用被测函数
    At_SmsStorageListProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(TAF_FALSE, gastAtClientTab[ucIndex].AtSmsData.bWaitForUsimStorageStatus);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_SmsStorageListProc,Test_At_SmsStorageListProc_004)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stStorageListInfo.enMemStroe                      = MN_MSG_MEM_STORE_NV;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    // MOCKER操作;

    // 调用被测函数
    At_SmsStorageListProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(TAF_FALSE, gastAtClientTab[ucIndex].AtSmsData.bWaitForNvStorageStatus);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif



TEST(Test_At_StaRptPduInd,Test_At_StaRptPduInd_001)
{
    // 参数定义
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stPdu;
    VOS_UINT32                          ulLength;
    VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};
    VOS_UINT8                           aucPdu[] = {0x02,0x81,0x0D,0x91,0x68,0x31,0x09,0x04,0x00,0x00,0xF3,0x11,0x50,0x07,0x22,0x52,0x84,0x00,0x11,0x50,0x70,0x22,0x13,0x11,0x00,0x00};
    VOS_UINT8                           aucOutput[] = {0x32,0x36,0x0d,0x0a,0x30,0x36,0x39,0x31,0x36,0x38,0x33,0x31,0x30,0x39,0x30,0x32,0x31,0x30,0x30,0x32,0x38,0x31,0x30,0x44,0x39,0x31,0x36,0x38,0x33,0x31,0x30,0x39,0x30,0x34,0x30,0x30,0x30,0x30,0x46,0x33,0x31,0x31,0x35,0x30,0x30,0x37,0x32,0x32,0x35,0x32,0x38,0x34,0x30,0x30,0x31,
                                                       0x31,0x35,0x30,0x37,0x30,0x32,0x32,0x31,0x33,0x31,0x31,0x30,0x30,0x30,0x30};
                                                        /*53..0691683109021002810D91683109040000F3115070225284001150702213110000*/
    VOS_UINT32                          i;
    VOS_UINT8                           *pucPdu;

    // 参数初始化

    stScAddr.addrType=0x91;
    stScAddr.ucBcdLen = sizeof(aucBcd);
    PS_MEM_CPY(stScAddr.aucBcdNum, aucBcd, stScAddr.ucBcdLen);

    stPdu.enTpduType = MN_MSG_TPDU_STARPT;
    stPdu.ulLen = sizeof(aucPdu);
    PS_MEM_CPY(stPdu.aucData, aucPdu, stPdu.ulLen);

    pucPdu = pgucAtSndCodeAddr;

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数
    ulLength = At_StaRptPduInd(&stScAddr, &stPdu, pucPdu);

    EXPECT_EQ(sizeof(aucOutput), ulLength);

    for (i = 0; i < ulLength; i++)
    {
        EXPECT_EQ(pgucAtSndCodeAddr[i], aucOutput[i]);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST(Test_At_StaRptPduInd,Test_At_StaRptPduInd_002)
{
    // 参数定义
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stPdu;
    VOS_UINT32                          ulLength;
    VOS_UINT8                           aucPdu[] = {0x02,0x81,0x0D,0x91,0x68,0x31,0x09,0x04,0x00,0x00,0xF3,0x11,0x50,0x07,0x22,0x52,0x84,0x00,0x11,0x50,0x70,0x22,0x13,0x11,0x00,0x00};
    VOS_UINT8                           aucOutput[] = {0x32,0x36,0x0d,0x0a,0x30,0x30,0x30,0x32,0x38,0x31,0x30,0x44,0x39,0x31,0x36,0x38,0x33,0x31,0x30,0x39,0x30,0x34,0x30,0x30,0x30,0x30,0x46,0x33,0x31,0x31,0x35,0x30,0x30,0x37,0x32,0x32,0x35,0x32,0x38,0x34,0x30,0x30,0x31,
                                                       0x31,0x35,0x30,0x37,0x30,0x32,0x32,0x31,0x33,0x31,0x31,0x30,0x30,0x30,0x30};
                                                        /*53..0691683109021002810D91683109040000F3115070225284001150702213110000*/
    VOS_UINT32                          i;
    VOS_UINT8                           *pucPdu;

    // 参数初始化

    stScAddr.addrType=0;
    stScAddr.ucBcdLen = 0;

    stPdu.enTpduType = MN_MSG_TPDU_STARPT;
    stPdu.ulLen = sizeof(aucPdu);
    PS_MEM_CPY(stPdu.aucData, aucPdu, stPdu.ulLen);

    pucPdu = pgucAtSndCodeAddr;

    // 相关全局变量初始化

    // MOCKER操作;

    // 调用被测函数
    ulLength = At_StaRptPduInd(&stScAddr, &stPdu, pucPdu);

    EXPECT_EQ(sizeof(aucOutput), ulLength);

    for (i = 0; i < ulLength; i++)
    {
        EXPECT_EQ(pgucAtSndCodeAddr[i], aucOutput[i]);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}









class Test_AT_QryParaAnQueryProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        /* 初始化用户输出缓存 */
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

    }
    void TearDown()
    {
        /* 初始化用户输出缓存 */
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

    }
};


TEST_F(Test_AT_QryParaAnQueryProc, Test_AT_QryParaAnQueryProc_001)
{
    /* 变量定义 */
    MN_MMA_ANQUERY_PARA_STRU            stAnqueryPara;
    VOS_UINT8                           aucExpectedStr[]     = "^ANQUERY:0,0,99,0,0xFFFFFFFF";
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =         {AT_CMD_ANQUERY,
                                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                                        AT_QryAnQuery,          AT_QRY_PARA_TIME,
                                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                                        (VOS_UINT8*)"^ANQUERY", VOS_NULL_PTR};


    /* 变量初始化 */
    stAnqueryPara.sCpichRscp            = 0;
    stAnqueryPara.sCpichEcNo            = 0;
    stAnqueryPara.ucRssi                = 99;
    stAnqueryPara.ulCellId              = 0xFFFFFFFF;

    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->enCalculateAntennaLevel = AT_CMD_ANTENNA_LEVEL_2;

    /* 函数打桩 */
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    /* 调用被测函数 */
    AT_QryParaAnQueryProc(ucIndex, 1, (VOS_VOID *)&stAnqueryPara);

    /* 结果验证 */
    ASSERT_STREQ((char *)aucExpectedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#if (FEATURE_ON == FEATURE_LTE)

TEST_F(Test_AT_QryParaAnQueryProc, Test_AT_QryParaAnQueryProc_002)
{
    /* 变量定义 */
    MN_MMA_ANQUERY_PARA_STRU            stAnqueryPara;
    VOS_UINT8                           aucExpectedStr[]     = "^ANQUERY:96,10,20,1,0,0";
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =         {AT_CMD_ANQUERY,
                                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                                        AT_QryAnQuery,          AT_QRY_PARA_TIME,
                                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                                        (VOS_UINT8*)"^ANQUERY", VOS_NULL_PTR};


    /* 变量初始化 */
    stAnqueryPara.sCpichRscp = -96;
    stAnqueryPara.sCpichEcNo = -10;
    stAnqueryPara.ucRssi     = 20;
    stAnqueryPara.ulCellId   = 46746;

    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->enCalculateAntennaLevel = AT_CMD_ANTENNA_LEVEL_2;


    /* 函数打桩 */
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq((VOS_UINT32)AT_OK));

    /* 调用被测函数 */
    AT_QryParaAnQueryProc(ucIndex, 1, (VOS_VOID *)&stAnqueryPara);

    /* 结果验证 */
    ASSERT_STREQ((char *)aucExpectedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#endif


class Test_AT_QryParaHomePlmnProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        /* 初始化用户输出缓存 */
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

    }
    void TearDown()
    {
        /* 初始化用户输出缓存 */
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

    }
};



TEST_F(Test_AT_QryParaHomePlmnProc, Test_AT_QryParaHomePlmnProc_001)
{
    /* 变量定义 */
    TAF_MMA_HPLMN_WITH_MNC_LEN_STRU                    stPlmnId;
    VOS_UINT8                           aucExpectedStr[]     = "^APHPLMN:46006";
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         = {AT_CMD_APHPLMN,
                                                                VOS_NULL_PTR,               AT_NOT_SET_TIME,
                                                                At_QryApHplmn,              AT_QRY_PARA_TIME,
                                                                VOS_NULL_PTR,               AT_NOT_SET_TIME,
                                                                VOS_NULL_PTR,               AT_NOT_SET_TIME,
                                                                AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                                (VOS_UINT8*)"^APHPLMN",     VOS_NULL_PTR};


    /* 变量初始化 */
    stPlmnId.stHplmn.Mcc = 0x000604;
    stPlmnId.stHplmn.Mnc = 0x000600;
    stPlmnId.ucHplmnMncLen=2;

    ucIndex                                 = 0;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;


    /* 函数打桩 */
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq((VOS_UINT32)AT_OK));

    /* 调用被测函数 */
    AT_QryParaHomePlmnProc(0, 0, (VOS_VOID *)&stPlmnId);

    /* 结果验证 */
    ASSERT_STREQ((char *)aucExpectedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_AT_QryParaHomePlmnProc, Test_AT_QryParaHomePlmnProc_002)
{
    /* 变量定义 */
    TAF_MMA_HPLMN_WITH_MNC_LEN_STRU                    stPlmnId;
    VOS_UINT8                           aucExpectedStr[]     = "^APHPLMN:460060";
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         = {AT_CMD_APHPLMN,
                                                                VOS_NULL_PTR,               AT_NOT_SET_TIME,
                                                                At_QryApHplmn,              AT_QRY_PARA_TIME,
                                                                VOS_NULL_PTR,               AT_NOT_SET_TIME,
                                                                VOS_NULL_PTR,               AT_NOT_SET_TIME,
                                                                AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
                                                                (VOS_UINT8*)"^APHPLMN",     VOS_NULL_PTR};


    /* 变量初始化 */
    stPlmnId.stHplmn.Mcc = 0x000604;
    stPlmnId.stHplmn.Mnc = 0x000600;
    stPlmnId.ucHplmnMncLen=3;

    ucIndex                                 = 0;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;


    /* 函数打桩 */
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq((VOS_UINT32)AT_OK));

    /* 调用被测函数 */
    AT_QryParaHomePlmnProc(0, 0, (VOS_UINT32 *)&stPlmnId);

    /* 结果验证 */
    ASSERT_STREQ((char *)aucExpectedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



class Test_At_CsRspProc: public ::testing::Test
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


TEST_F(Test_At_CsRspProc, Test_At_CsRspProc_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    // 参数初始化
    ucIndex                             = 0;
    enEvent                             = MN_CALL_EVT_ORIG;
    stCallInfo.enCallType               = MN_CALL_TYPE_VIDEO;
    PS_MEM_SET(&stCallInfo, 0x00, sizeof(MN_CALL_INFO_STRU));

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    At_CsRspProc(ucIndex, enEvent, (MN_CALL_INFO_STRU *)&stCallInfo);

    // 执行检查
    EXPECT_EQ(AT_GetModemCcCtxAddrFromClientId(ucIndex)->ulCurIsExistCallFlag, VOS_TRUE);

    GlobalMockObject::verify();
}


TEST_F(Test_At_CsRspProc, Test_At_CsRspProc_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    // 参数初始化
    ucIndex                             = 0;
    enEvent                             = MN_CALL_EVT_GET_CDUR_CNF;
    PS_MEM_SET(&stCallInfo, 0x00, sizeof(MN_CALL_INFO_STRU));

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_RcvCdurQryRsp)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), eq((MN_CALL_EVENT_ENUM_U32)enEvent),
                mirror((MN_CALL_INFO_STRU *)&stCallInfo, (VOS_UINT32)sizeof(MN_CALL_INFO_STRU)));

    // 调用被测函数
    At_CsRspProc(ucIndex, enEvent, (MN_CALL_INFO_STRU *)&stCallInfo);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_At_CsRspProc, Test_At_CsRspProc_003)
{
    // 变量声明
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    // 参数初始化
    ucIndex                             = 0;
    enEvent                             = MN_CALL_EVT_ALL_RELEASED;
    PS_MEM_SET(&stCallInfo, 0x00, sizeof(MN_CALL_INFO_STRU));

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_CsRspProc(ucIndex, enEvent, (MN_CALL_INFO_STRU *)&stCallInfo);

    // 执行检查
    EXPECT_EQ(AT_GetModemCcCtxAddrFromClientId(ucIndex)->ulCurIsExistCallFlag, VOS_FALSE);

    GlobalMockObject::verify();
}


TEST_F(Test_At_CsRspProc, Test_At_CsRspProc_004)
{
    // 变量声明
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;
    VOS_CHAR                           *pcExpect;

    // 参数初始化
    ucIndex                             = 0;
    enEvent                             = MN_CALL_EVT_CALL_PROC;
    PS_MEM_SET(&stCallInfo, 0x00, sizeof(MN_CALL_INFO_STRU));
    stCallInfo.enCallType = MN_CALL_TYPE_EMERGENCY;
    stCallInfo.callId     = 1;
    PS_MEM_SET(stCallInfo.aucCurcRptCfg, 0xFF, sizeof(stCallInfo.aucCurcRptCfg));
    pcExpect    = "\r\n^CONF:1\r\n";

    // 初始化全局变量

    // MOCKER操作;
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, (VOS_UINT32)VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    At_CsRspProc(ucIndex, enEvent, (MN_CALL_INFO_STRU *)&stCallInfo);

    // 执行检查

    GlobalMockObject::verify();
}


class Test_AT_QryCscaRspProc: public ::testing::Test
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


TEST_F(Test_AT_QryCscaRspProc, Test_AT_QryCscaRspProc_002)
{
    // 变量声明
    VOS_UINT8                            ucIndex;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    //参数初始化
    ucIndex = 0;
    PS_MEM_SET(&stEvent, 0x00, sizeof(stEvent));

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PFVER_READ;

    // MOCKER操作;
    MOCKER(AT_StopRelTimer)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_QryCscaRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryCscaRspProc, Test_AT_QryCscaRspProc_003)
{
    // 变量声明
    VOS_UINT8                            ucIndex;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CSCA,
        At_SetCscaPara,     AT_SET_PARA_TIME, At_QryCscaPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,      AT_NOT_SET_TIME,
        AT_RRETURN_CODE_BUTT, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CSCA",    (VOS_UINT8*)"(sca),(0-255)"};

    //参数初始化
    ucIndex = 0;
    PS_MEM_SET(&stEvent, 0x00, sizeof(stEvent));
    stEvent.u.stSrvParmInfo.bSuccess = VOS_FALSE;
    stEvent.u.stSrvParmInfo.ulFailCause = MN_ERR_CLASS_SMS_INVALID_SCADDR;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CDUR_READ;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    // MOCKER操作;
    MOCKER(AT_StopRelTimer)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_QryCscaRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryCscaRspProc, Test_AT_QryCscaRspProc_004)
{
    // 变量声明
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_UINT8                            aucBcdSc[] = {0x68, 0x31, 0x09, 0x02, 0x10};
    VOS_UINT16                            usExpectdLen;
    VOS_CHAR                           *pcExpectedStr;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CSCA,
        At_SetCscaPara,     AT_SET_PARA_TIME, At_QryCscaPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,      AT_NOT_SET_TIME,
        AT_RRETURN_CODE_BUTT, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CSCA",    (VOS_UINT8*)"(sca),(0-255)"};

    //参数初始化
    ucIndex                                    = 0;
    pcExpectedStr                            = "+CSCA: \"+8613902001\",145";
    usExpectdLen                            = VOS_StrLen(pcExpectedStr);

    PS_MEM_SET(&stEvent, 0x00, sizeof(stEvent));
    stEvent.u.stSrvParmInfo.bSuccess = VOS_TRUE;
    stEvent.u.stSrvParmInfo.stSrvParm.stScAddr.ucBcdLen = sizeof(aucBcdSc);
    stEvent.u.stSrvParmInfo.stSrvParm.stScAddr.addrType = 145;
    PS_MEM_CPY(&stEvent.u.stSrvParmInfo.stSrvParm.stScAddr.aucBcdNum, aucBcdSc, stEvent.u.stSrvParmInfo.stSrvParm.stScAddr.ucBcdLen);

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CSCA_READ;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gucAtCscsType                           = AT_CSCS_IRA_CODE;

    // MOCKER操作;
    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    AT_QryCscaRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(usExpectdLen, gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpectedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_QryCscaRspProc, Test_AT_QryCscaRspProc_005)
{
    // 变量声明
    TAF_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_UINT16                            usExpectdLen;
    VOS_CHAR                           *pcExpectedStr;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CSCA,
        At_SetCscaPara,     AT_SET_PARA_TIME, At_QryCscaPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR ,      AT_NOT_SET_TIME,
        AT_RRETURN_CODE_BUTT, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CSCA",    (VOS_UINT8*)"(sca),(0-255)"};

    //参数初始化
    ucIndex                                    = 0;
    pcExpectedStr                            = "+CSCA: \"\",128";
    usExpectdLen                            = VOS_StrLen(pcExpectedStr);

    PS_MEM_SET(&stEvent, 0x00, sizeof(stEvent));
    stEvent.u.stSrvParmInfo.bSuccess = VOS_TRUE;
    stEvent.u.stSrvParmInfo.stSrvParm.stScAddr.ucBcdLen = 0;

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt    = AT_CMD_CSCA_READ;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    // MOCKER操作;
    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    AT_QryCscaRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(0, gastAtClientTab[ucIndex].opId);
    EXPECT_EQ(usExpectdLen, gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpectedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();

}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_QryCscaRspProc, Test_AT_QryCscaRspProc_006)
{

}


TEST_F(Test_AT_QryCscaRspProc, Test_AT_QryCscaRspProc_007)
{

}


//VOS_INT32 ut_VOS_sprintf(VOS_CHAR *str, const VOS_CHAR *fmt)
//{
//
//    return VOS_OK;
//}

class Test_AT_PhnEvtTestCpol: public ::testing::Test
{
public:
    VOS_UINT8                                ucIndex;
    AT_PAR_CMD_ELEMENT_STRU                  stElement;
    VOS_UINT8                                szCmdName[32];

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"+cpol");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;
    }

    void TearDown()
    {
        ucIndex                                = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
    }
};

TEST_F(Test_AT_PhnEvtTestCpol,Test_AT_PhnEvtTestCpol_001)
{
    TAF_PHONE_EVENT_INFO_STRU   stEvent;

    stEvent.OP_PrefPlmnList = 1;

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*MOCKER(VOS_sprintf)
        .expects(exactly(1));*/

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    AT_PhnEvtTestCpol(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


class Test_AT_PhnEvtGetDomainAttachState: public ::testing::Test
{
public:
    VOS_UINT8                                ucIndex;
    AT_PAR_CMD_ELEMENT_STRU                  stElement;
    VOS_UINT8                                szCmdName[32];

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"^cgcatt");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;
    }

    void TearDown()
    {
        ucIndex                                = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
    }
};

TEST_F(Test_AT_PhnEvtGetDomainAttachState,Test_AT_PhnEvtGetDomainAttachState_001)
{
    TAF_PHONE_EVENT_INFO_STRU   stEvent;

    AT_PhnEvtGetDomainAttachState(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_INVALID, gastAtClientTab[ucIndex].CmdCurrentOpt);

}

TEST_F(Test_AT_PhnEvtGetDomainAttachState,Test_AT_PhnEvtGetDomainAttachState_002)
{
    TAF_PHONE_EVENT_INFO_STRU   stEvent;

    stEvent.OP_DomainAttachState            = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_PhnEvtGetDomainAttachState(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS, gastAtClientTab[ucIndex].CmdCurrentOpt);
}

TEST_F(Test_AT_PhnEvtGetDomainAttachState,Test_AT_PhnEvtGetDomainAttachState_003)
{
    TAF_PHONE_EVENT_INFO_STRU   stEvent;

    stEvent.stDomainAttachState.ucDomain    = TAF_PH_PS_CS_OPERATE;
    stEvent.OP_DomainAttachState            = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;

    MOCKER(AT_StopRelTimer)
        .expects(exactly(0));

    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    AT_PhnEvtGetDomainAttachState(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}

TEST_F(Test_AT_PhnEvtGetDomainAttachState,Test_AT_PhnEvtGetDomainAttachState_004)
{
    TAF_PHONE_EVENT_INFO_STRU   stEvent;

    stEvent.stDomainAttachState.ucDomain    = TAF_PH_PS_OPERATE;
    stEvent.OP_DomainAttachState            = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    AT_PhnEvtGetDomainAttachState(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}

TEST_F(Test_AT_PhnEvtGetDomainAttachState,Test_AT_PhnEvtGetDomainAttachState_005)
{
    TAF_PHONE_EVENT_INFO_STRU   stEvent;

    stEvent.stDomainAttachState.ucDomain    = TAF_PH_CS_OPERATE;
    stEvent.OP_DomainAttachState            = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    AT_PhnEvtGetDomainAttachState(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}



class Test_At_SetAlsCnf: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    MN_CALL_SET_ALS_CNF_STRU           *pstEvent;
    VOS_UINT8                           szCmdName[32];


    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        /* 生成输入消息 */
        pRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_SET_ALS_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }

        pstEvent = (MN_CALL_SET_ALS_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(MN_AT_IND_EVT_STRU));
        PS_MEM_SET(pstEvent, 0, sizeof(MN_CALL_SET_ALS_CNF_STRU));

    }

    void TearDown()
    {
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

TEST_F(Test_At_SetAlsCnf,Test_At_SetAlsCnf_001)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_SetAlsCnf(pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_SetAlsCnf,Test_At_SetAlsCnf_002)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->ulRet           = TAF_ERR_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_SetAlsCnf(pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_SetAlsCnf,Test_At_SetAlsCnf_003)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->ulRet           = TAF_ERR_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    At_SetAlsCnf(pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

class Test_At_CsMsgProc: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    MN_CALL_QRY_ALS_CNF_STRU           *pstEvent;
    VOS_UINT8                           szCmdName[32];
    VOS_UINT32                          ulMsgLen;


    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        /* 生成输入消息 */
        ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_QRY_ALS_CNF_STRU) - 4;
        pRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }

        pstEvent = (MN_CALL_QRY_ALS_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(MN_AT_IND_EVT_STRU));
        PS_MEM_SET(pstEvent, 0, sizeof(MN_CALL_QRY_ALS_CNF_STRU));

    }

    void TearDown()
    {
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_001)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_QRY_ALS_CNF;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_002)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_QRY_UUS1_INFO_CNF;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_003)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_SET_UUS1_INFO_CNF;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_004)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_SET_ALS_CNF;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_005)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_CLCC_INFO;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_006)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_CALL_PROC;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_CSCallStateReportProc)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#endif


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_007)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult = AT_OK;

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_SET_CSSN_CNF;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSSN_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_008)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_CALL_ORIG_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_009)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_CALL_ORIG_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_010)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_CALL_ORIG_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VIDEO;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_DATA_CALL_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_011)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_CALL_ORIG_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_NO_CALL_ID;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_012)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_CALL_ORIG_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_NO_CARRIER));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_013)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_014)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHUP_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_016)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHLD_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_018)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHLD_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(AT_ConvertCallError)
        .expects(exactly(1))
        .will(returnValue(VOS_UINT32(AT_SUCCESS)));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_019)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHUP_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(AT_ConvertCallError)
        .expects(exactly(1))
        .will(returnValue(VOS_UINT32(AT_SUCCESS)));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_020)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_A_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(AT_ConvertCallError)
        .expects(exactly(1))
        .will(returnValue(VOS_UINT32(AT_SUCCESS)));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_021)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(AT_ConvertCallError)
        .expects(exactly(1))
        .will(returnValue(VOS_UINT32(AT_SUCCESS)));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_022)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(AT_ConvertCallError)
        .expects(never())
        .will(returnValue(VOS_UINT32(AT_SUCCESS)));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_CME_UNKNOWN));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_023)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(AT_ConvertCallError)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_024)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    MOCKER(AT_ConvertCallError)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_025)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    ucIndex = 0;

    MOCKER(AT_ConvertCallError)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


#if (FEATURE_ON == FEATURE_ECALL)

TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_028)
{
    /* 变量定义 */
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);
    *pulEvent = MN_CALL_EVT_QRY_ECALL_INFO_CNF;

    /* 函数打桩 */
    MOCKER(At_RcvTafCallQryEcallInfoCnf)
        .expects(exactly(1))
        .will(returnValue(VOS_UINT32(VOS_OK)));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_029)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult      = AT_OK;
    MN_CALL_INFO_STRU              *pstMnCallInfo = VOS_NULL_PTR;
    MN_AT_IND_EVT_STRU             *pstRcvMsg     = VOS_NULL_PTR;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                     *pulEvent;

    /* 生成输入消息 */
    ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU);
    pstRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulMsgLen);

    /* 变量初始化 */
    pulEvent = (VOS_UINT32 *)&(pstRcvMsg->aucContent[0]);

    *pulEvent = MN_CALL_EVT_SUPS_CMD_CNF;

    pstMnCallInfo = (MN_CALL_INFO_STRU *)&(pstRcvMsg->aucContent[4]);
    pstMnCallInfo->enCallType = MN_CALL_TYPE_VOICE;
    pstMnCallInfo->enCause    = TAF_CS_CAUSE_SUCCESS;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLSTOP_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    MOCKER(At_FormatResultData)
        .times(1)
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    /* 调用被测函数 */
    At_CsMsgProc(pstRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    LLT_GLOBALOBJMOCKER::verify();
}

#endif



class Test_At_RcvMnCallSetCssnCnf: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    MN_CALL_SET_CSSN_CNF_STRU          *pstEvent;
    VOS_UINT8                           szCmdName[32];
    VOS_UINT8                           ulMsgLen;


    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"+cssn");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;

        /* 生成输入消息 */
        ulMsgLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_QRY_ALS_CNF_STRU) - 4;
        pRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_SET_CSSN_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }

        pstEvent = (MN_CALL_SET_CSSN_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(MN_AT_IND_EVT_STRU));
        PS_MEM_SET(pstEvent, 0, sizeof(MN_CALL_SET_CSSN_CNF_STRU));

    }

    void TearDown()
    {
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

TEST_F(Test_At_RcvMnCallSetCssnCnf,Test_At_RcvMnCallSetCssnCnf_001)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult = AT_OK;

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_SET_CSSN_CNF;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSSN_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never())
        .with(eq(ucIndex), eq(ulResult));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_RcvMnCallSetCssnCnf,Test_At_RcvMnCallSetCssnCnf_002)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult = AT_OK;

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_SET_CSSN_CNF;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSSN_SET;
    ucIndex                   = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(never())
        .with(eq(ucIndex), eq(ulResult));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_RcvMnCallSetCssnCnf,Test_At_RcvMnCallSetCssnCnf_003)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult = AT_OK;

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_SET_CSSN_CNF;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSSM_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(never())
        .with(eq(ucIndex), eq(ulResult));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_RcvMnCallSetCssnCnf,Test_At_RcvMnCallSetCssnCnf_004)
{
    /* 变量定义 */
    VOS_UINT32                      ulResult = AT_CME_INCORRECT_PARAMETERS;

    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_SET_CSSN_CNF;
    pstEvent->ulRet           = TAF_ERR_NOT_READY;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSSN_SET;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



class Test_At_QryAlsCnf: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    MN_CALL_QRY_ALS_CNF_STRU           *pstEvent;
    VOS_UINT8                           szCmdName[32];


    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"^als");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;

        /* 生成输入消息 */
        pRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_QRY_ALS_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }

        pstEvent = (MN_CALL_QRY_ALS_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(MN_AT_IND_EVT_STRU));
        PS_MEM_SET(pstEvent, 0, sizeof(MN_CALL_QRY_ALS_CNF_STRU));

    }

    void TearDown()
    {
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

TEST_F(Test_At_QryAlsCnf,Test_At_QryAlsCnf_001)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*MOCKER(At_sprintf)
        .expects(exactly(2));*/

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_QryAlsCnf(pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

class Test_At_SetUus1Cnf: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    TAF_PH_SET_UUS1_INFO_CNF_STRU      *pstEvent;
    VOS_UINT8                           szCmdName[32];


    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"+cuus1");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;

        /* 生成输入消息 */
        pRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_AT_IND_EVT_STRU) + sizeof(TAF_PH_SET_UUS1_INFO_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }

        pstEvent = (TAF_PH_SET_UUS1_INFO_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(MN_AT_IND_EVT_STRU));
        PS_MEM_SET(pstEvent, 0, sizeof(TAF_PH_SET_UUS1_INFO_CNF_STRU));

    }

    void TearDown()
    {
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

TEST_F(Test_At_SetUus1Cnf,Test_At_SetUus1Cnf_001)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_SetUus1Cnf(pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F(Test_At_SetUus1Cnf,Test_At_SetUus1Cnf_002)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->ulRet           = TAF_ERR_ERROR;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_SetUus1Cnf(pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

class Test_At_QryUus1Cnf: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    TAF_PH_QRY_UUS1_INFO_CNF_STRU      *pstEvent;
    VOS_UINT8                           szCmdName[32];


    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"+cuus1");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;

        /* 生成输入消息 */
        pRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_AT_IND_EVT_STRU) + sizeof(TAF_PH_QRY_UUS1_INFO_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }

        pstEvent = (TAF_PH_QRY_UUS1_INFO_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(MN_AT_IND_EVT_STRU));
        PS_MEM_SET(pstEvent, 0, sizeof(TAF_PH_QRY_UUS1_INFO_CNF_STRU));

    }

    void TearDown()
    {
        ucIndex                                 = 0 ;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        /* 释放消息内存 */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};

TEST_F(Test_At_QryUus1Cnf,Test_At_QryUus1Cnf_001)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;
    pstEvent->ulActNum        = 1;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*MOCKER(At_sprintf)
        .expects(exactly(4));*/

    MOCKER(At_HexAlpha2AsciiString)
        .expects(exactly(1))
        .will(returnValue(0));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_QryUus1Cnf(pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_QryUus1Cnf,Test_At_QryUus1Cnf_002)
{
    /* 变量定义 */

    /* 变量初始化 */
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;
    pstEvent->ulActNum        = 1;
    pstEvent->aenSetType[0]     = MN_CALL_CUUS1_DISABLE;
    pstEvent->aenSetType[1]     = MN_CALL_CUUS1_DISABLE;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*MOCKER(At_sprintf)
        .expects(exactly(4));*/

    MOCKER(At_HexAlpha2AsciiString)
        .expects(exactly(1))
        .will(returnValue(0));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_QryUus1Cnf(pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


class Test_At_PhMsgProc: public ::testing::Test
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

TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_001)
{
    /* 变量定义 */
    TAF_PHONE_EVENT_PLMN_LIST_STRU         stPhoneEvent;

    /* 变量初始化 */
    stPhoneEvent.PhoneEvent = TAF_PH_EVT_PLMN_LIST_CNF;
    stPhoneEvent.ClientId   = 0xFF;

    /* 函数打桩 */

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stPhoneEvent,sizeof(TAF_PHONE_EVENT_PLMN_LIST_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_002)
{
    /* 变量定义 */
    TAF_PHONE_EVENT_PLMN_LIST_STRU         stPhoneEvent;

    /* 变量初始化 */
    stPhoneEvent.PhoneEvent = TAF_PH_EVT_ATTACH_CNF;
    stPhoneEvent.ClientId   = 0xFF;

    /* 函数打桩 */
    MOCKER(At_PhEventProc)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stPhoneEvent,sizeof(TAF_PHONE_EVENT_PLMN_LIST_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_003)
{
    /* 变量定义 */
    TAF_PHONE_EVENT_PLMN_LIST_STRU         stPhoneEvent;

    /* 变量初始化 */
    stPhoneEvent.PhoneEvent = ID_TAF_MMA_REG_REJ_INFO_IND;
    stPhoneEvent.ClientId   = 0xFF;

    /* 函数打桩 */

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stPhoneEvent,sizeof(TAF_PHONE_EVENT_PLMN_LIST_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_004)
{
    /* 变量定义 */
    TAF_PHONE_EVENT_PLMN_LIST_STRU         stPhoneEvent;

    /* 变量初始化 */
    stPhoneEvent.PhoneEvent = ID_TAF_MMA_PLMN_SELECTION_INFO_IND;
    stPhoneEvent.ClientId   = 0xFF;

    /* 函数打桩 */

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stPhoneEvent,sizeof(TAF_PHONE_EVENT_PLMN_LIST_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_005)
{
    /* 变量定义 */
    TAF_PHONE_EVENT_PLMN_LIST_STRU         stPhoneEvent;

    /* 变量初始化 */
    stPhoneEvent.PhoneEvent = ID_TAF_MMA_EOPLMN_QRY_CNF;
    stPhoneEvent.ClientId   = 0xFF;

    /* 函数打桩 */
    MOCKER(AT_PhEOPlmnQueryCnfProc)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stPhoneEvent,sizeof(TAF_PHONE_EVENT_PLMN_LIST_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_006)
{
    /* 变量定义 */
    TAF_PHONE_EVENT_PLMN_LIST_STRU         stPhoneEvent;

    /* 变量初始化 */
    stPhoneEvent.PhoneEvent = ID_TAF_MMA_EOPLMN_SET_CNF;
    stPhoneEvent.ClientId   = 0xFF;

    /* 函数打桩 */

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stPhoneEvent,sizeof(TAF_PHONE_EVENT_PLMN_LIST_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_004_1)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;

    /* 变量初始化 */
    ulRet                   = AT_FAILURE;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)ulRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_005_1)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_SUCCESS;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_BUTT;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_006_1)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_SUCCESS;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_BUTT;
    stNetScanCnf.ucFreqNum  = 1;


    stNetScanCnf.astNetScanInfo[0].usArfcn  = 278;
    stNetScanCnf.astNetScanInfo[0].usC1     = 0;
    stNetScanCnf.astNetScanInfo[0].usC2     = 0;
    stNetScanCnf.astNetScanInfo[0].usLac    = 0x01;
    stNetScanCnf.astNetScanInfo[0].ulMcc    = 0x00402;
    stNetScanCnf.astNetScanInfo[0].ulMnc    = 0xf0500;
    stNetScanCnf.astNetScanInfo[0].usBsic   = 0;
    stNetScanCnf.astNetScanInfo[0].sRxlev   = 0;
    stNetScanCnf.astNetScanInfo[0].sRssi    = 0;
    stNetScanCnf.astNetScanInfo[0].ulCellId = 1;
    stNetScanCnf.astNetScanInfo[0].stBand.ulBandHigh = 0x00040000;
    stNetScanCnf.astNetScanInfo[0].stBand.ulBandLow  = 0x00000000;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */
    pcExpect = "^NETSCAN: 278,,,1,240,05,0,0,1,4000000000000";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_007)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

     stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_SUCCESS;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_BUTT;
    stNetScanCnf.ucFreqNum  = 1;


    stNetScanCnf.astNetScanInfo[0].usArfcn  = 278;
    stNetScanCnf.astNetScanInfo[0].usC1     = 0;
    stNetScanCnf.astNetScanInfo[0].usC2     = 0;
    stNetScanCnf.astNetScanInfo[0].usLac    = 0x01;
    stNetScanCnf.astNetScanInfo[0].ulMcc    = 0x00402;
    stNetScanCnf.astNetScanInfo[0].ulMnc    = 0x00500;
    stNetScanCnf.astNetScanInfo[0].usBsic   = 0;
    stNetScanCnf.astNetScanInfo[0].sRxlev   = 0;
    stNetScanCnf.astNetScanInfo[0].sRssi    = 0;
    stNetScanCnf.astNetScanInfo[0].ulCellId = 1;
    stNetScanCnf.astNetScanInfo[0].stBand.ulBandLow  = 0x40000000;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */
    pcExpect = "^NETSCAN: 278,,,1,240,050,0,0,1,40000000";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_008)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_SUCCESS;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_BUTT;
    stNetScanCnf.ucFreqNum  = 2;


    stNetScanCnf.astNetScanInfo[0].usArfcn  = 278;
    stNetScanCnf.astNetScanInfo[0].usC1     = 0;
    stNetScanCnf.astNetScanInfo[0].usC2     = 0;
    stNetScanCnf.astNetScanInfo[0].usLac    = 0x01;
    stNetScanCnf.astNetScanInfo[0].ulMcc    = 0x00402;
    stNetScanCnf.astNetScanInfo[0].ulMnc    = 0x00500;
    stNetScanCnf.astNetScanInfo[0].usBsic   = 0;
    stNetScanCnf.astNetScanInfo[0].sRxlev   = 0;
    stNetScanCnf.astNetScanInfo[0].sRssi    = 0;
    stNetScanCnf.astNetScanInfo[0].ulCellId = 1;
    stNetScanCnf.astNetScanInfo[0].stBand.ulBandLow  = 0x40000000;

    stNetScanCnf.astNetScanInfo[1].usArfcn  = 278;
    stNetScanCnf.astNetScanInfo[1].usC1     = 0;
    stNetScanCnf.astNetScanInfo[1].usC2     = 0;
    stNetScanCnf.astNetScanInfo[1].usLac    = 0x01;
    stNetScanCnf.astNetScanInfo[1].ulMcc    = 0x00402;
    stNetScanCnf.astNetScanInfo[1].ulMnc    = 0x00500;
    stNetScanCnf.astNetScanInfo[1].usBsic   = 0;
    stNetScanCnf.astNetScanInfo[1].sRxlev   = 0;
    stNetScanCnf.astNetScanInfo[1].sRssi    = 0;
    stNetScanCnf.astNetScanInfo[1].ulCellId = 1;
    stNetScanCnf.astNetScanInfo[1].stBand.ulBandLow  = 0x40000000;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */
    pcExpect = "^NETSCAN: 278,,,1,240,050,0,0,1,40000000\r\n^NETSCAN: 278,,,1,240,050,0,0,1,40000000";
    ASSERT_STREQ(pcExpect, (TAF_CHAR*)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_009)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_ERROR;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_SIGNAL_EXIST;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_010)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_CME_OPERATION_NOT_ALLOWED;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_STATE_NOT_ALLOWED;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_011)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_CME_OPERATION_NOT_ALLOWED;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_FREQ_LOCK;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_012)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_CME_INCORRECT_PARAMETERS;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_PARA_ERROR;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_013)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_CME_OPERATION_NOT_ALLOWED;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_CONFLICT;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_014)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_CME_OPERATION_NOT_ALLOWED;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));
    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_SERVICE_EXIST;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_015)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_ERROR;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_TIMER_EXPIRED;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_016)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_CME_OPERATION_NOT_ALLOWED;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_RAT_TYPE_ERROR;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_017)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_ERROR;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_MMA_STATE_DISABLE;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_018)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_ERROR;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));
    ucIndex                 = 0;

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_MMA_STATE_DISABLE + 1;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_019)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_CME_OPERATION_NOT_ALLOWED;
    ucIndex                 = 0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_NOT_CAMPED;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(ulFormatRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhMsgProc,Test_At_PhMsgProc_020)
{
    /* 变量定义 */
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;
    VOS_UINT32                          ulFormatRet;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    ulRet                   = AT_SUCCESS;
    ulFormatRet             = AT_CME_OPERATION_NOT_ALLOWED;
    ucIndex                 = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    stNetScanCnf.ulMsgName= ID_TAF_MMA_NET_SCAN_CNF;
    stNetScanCnf.enResult   = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    stNetScanCnf.enCause    = TAF_MMA_NET_SCAN_CAUSE_NOT_CAMPED;
    stNetScanCnf.ucFreqNum  = 0;

    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue(ulRet));

    /* 调用被测函数 */
    At_PhMsgProc((TAF_UINT8*)&stNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_At_PhPlmnListProc: public ::testing::Test
{
public:
    VOS_UINT8                                ucIndex;
    AT_PAR_CMD_ELEMENT_STRU                  stElement;
    VOS_UINT8                                szCmdName[32];

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"+cops");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;
    }
    void TearDown()
    {
        ucIndex = 0;
    }
};

TEST_F(Test_At_PhPlmnListProc,Test_At_PhPlmnListProc_001)
{
    /* 变量定义 */
    TAF_PHONE_EVENT_PLMN_LIST_STRU         stPhoneEvent;

    /* 变量初始化 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_TEST;
    stPhoneEvent.PhoneEvent = TAF_PH_EVT_PLMN_LIST_CNF;
    stPhoneEvent.ClientId   = 0;

    stPhoneEvent.ulPlmnNum = 3;

    stPhoneEvent.astPlmnName[0].PlmnId.Mcc = 0x406;
    stPhoneEvent.astPlmnName[0].PlmnId.Mnc = 0x302;
    stPhoneEvent.astPlmnName[0].aucOperatorNameLong[0] = '\0';
    stPhoneEvent.astPlmnName[0].aucOperatorNameShort[0] = '\0';
    stPhoneEvent.astPlmnInfo[0].RaMode = TAF_PH_RA_GSM;

    stPhoneEvent.astPlmnName[1].PlmnId.Mcc = 0x406;
    stPhoneEvent.astPlmnName[1].PlmnId.Mnc = 0x303;
    VOS_StrCpy((VOS_CHAR*)stPhoneEvent.astPlmnName[1].aucOperatorNameLong,"^CMCC.CN");
    VOS_StrCpy((VOS_CHAR*)stPhoneEvent.astPlmnName[1].aucOperatorNameShort,"^CMCC");
    stPhoneEvent.astPlmnInfo[1].RaMode = TAF_PH_RA_WCDMA;

    stPhoneEvent.astPlmnName[2].PlmnId.Mcc = 0x406;
    stPhoneEvent.astPlmnName[2].PlmnId.Mnc = 0x304;
    stPhoneEvent.astPlmnName[2].aucOperatorNameLong[0] = '\0';
    stPhoneEvent.astPlmnName[2].aucOperatorNameShort[0] = '\0';
    stPhoneEvent.astPlmnInfo[2].RaMode = TAF_PH_RA_LTE;


    /* 函数打桩 */
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_PhPlmnListProc((TAF_UINT8*)&stPhoneEvent,sizeof(TAF_PHONE_EVENT_PLMN_LIST_STRU));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

class Test_AT_RcvTafPsEvtReportRaInfo: public ::testing::Test
{
public:
    TAF_PS_EVT_STRU                         *m_pstPsEvt;
    MN_AT_IND_EVT_STRU                      *m_pRcvMsg;
    TAF_PS_IPV6_INFO_IND_STRU     *m_pstEvent;

    void SetUp()
    {
        UT_STUB_INIT();
        /* 生成输入消息 */
        m_pRcvMsg = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_AT_IND_EVT_STRU) + sizeof(TAF_PS_IPV6_INFO_IND_STRU) - 4);

        if (VOS_NULL_PTR == m_pRcvMsg)
        {
            return;
        }

        m_pstEvent = (TAF_PS_IPV6_INFO_IND_STRU *)(m_pRcvMsg->aucContent);
        m_pstPsEvt = (TAF_PS_EVT_STRU*)m_pRcvMsg;

        PS_MEM_SET(m_pRcvMsg, 0, sizeof(MN_AT_IND_EVT_STRU));
        PS_MEM_SET(m_pstEvent, 0, sizeof(TAF_PS_IPV6_INFO_IND_STRU));

        m_pRcvMsg->ulSenderPid      = WUEPS_PID_TAF;
        m_pRcvMsg->usMsgName        = MN_CALLBACK_PS_CALL;
        m_pstPsEvt->ulEvtId         = ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND;

    }
    void TearDown()
    {
        /* 释放消息内存 */
        if (VOS_NULL_PTR != m_pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, m_pRcvMsg);
        }
        m_pstPsEvt = NULL;
    }
};

#if (FEATURE_ON == FEATURE_IPV6)

TEST_F(Test_AT_RcvTafPsEvtReportRaInfo, Test_AT_RcvTafPsEvtReportRaInfo_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PS_IPV6_INFO_IND_STRU   stEvtInfo;

    ucIndex = AT_CLIENT_BUTT;

    AT_RcvTafPsEvtReportRaInfo(ucIndex, (VOS_VOID *)&stEvtInfo);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtReportRaInfo, Test_AT_RcvTafPsEvtReportRaInfo_002)
{
    VOS_UINT8                           ucIndex;
    TAF_PS_IPV6_INFO_IND_STRU   stEvtInfo;
    AT_PDP_ENTITY_STRU                 *pstPdpEntity;

    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].UserType = AT_NDIS_USER;

    pstPdpEntity = AT_NDIS_GetPdpEntInfoAddr();

    pstPdpEntity->enIpv6State = AT_PDP_STATE_ACTED;

    MOCKER(AT_FwSendClientMsg)
        .expects(exactly(0));

    MOCKER(AT_SendNdisIPv6PdnInfoCfgReq)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_PS_ProcSharePdpIpv6RaInfo)
        .expects(exactly(1));

    AT_RcvTafPsEvtReportRaInfo(ucIndex, (VOS_VOID *)&stEvtInfo);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#if(FEATURE_ON == FEATURE_NDIS)

TEST_F(Test_AT_RcvTafPsEvtReportRaInfo,Test_AT_RcvTafPsEvtReportRaInfo_003)
{
    AT_PDP_ENTITY_STRU                 *pstPdpEntity;
    VOS_UINT8                           ucIndex;

    g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns   = VOS_TRUE;
    g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns   = VOS_TRUE;

    ucIndex                             = 0;
    gastAtClientTab[ucIndex].UserType   = AT_NDIS_USER;

    pstPdpEntity = AT_APP_GetPdpEntInfoAddr();
    pstPdpEntity->enIpv6State = AT_PDP_STATE_ACTED;

    // 构建消息
    m_pstEvent->stIpv6RaInfo.ulPrefixNum                      = 1;
    m_pstEvent->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen  = AT_APS_IP6_ADDR_PREFIX_BYTE_LEN;
    m_pstEvent->stIpv6RaInfo.bitOpMtu                         = VOS_TRUE;

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_FwSendClientMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)ERR_MSP_NOT_FOUND));


    At_MsgProc((MsgBlock*)m_pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

TEST_F(Test_AT_RcvTafPsEvtReportRaInfo,Test_AT_RcvTafPsEvtReportRaInfo_004)
{
    AT_PDP_ENTITY_STRU                 *pstPdpEntity;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_WEBUI;

    g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns   = VOS_TRUE;
    g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns   = VOS_TRUE;

    ucIndex                             = 0;
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;

    pstPdpEntity = AT_APP_GetPdpEntInfoAddr();
    pstPdpEntity->enIpv6State = AT_PDP_STATE_ACTED;

    // 构建消息
    m_pstEvent->stIpv6RaInfo.ulPrefixNum                      = 1;
    m_pstEvent->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen  = AT_APS_IP6_ADDR_PREFIX_BYTE_LEN+1;
    m_pstEvent->stIpv6RaInfo.bitOpMtu                         = VOS_TRUE;

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_AppRcvIpv6LanAddr)
        .expects(exactly(1));

    MOCKER(AT_AppRcvIpv6Prefix)
        .expects(exactly(1));

    MOCKER(AT_AppRcvPrefixIpv6PreferredLifetime)
        .expects(exactly(1));

    MOCKER(AT_AppRcvPrefixIpv6ValidLifetime)
        .expects(exactly(1));

    MOCKER(AT_AppRcvEnableIpv6Prefix)
        .expects(exactly(1));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    At_MsgProc((MsgBlock*)m_pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvTafPsEvtReportRaInfo,Test_AT_RcvTafPsEvtReportRaInfo_005)
{
    AT_PDP_ENTITY_STRU                 *pstPdpEntity;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns   = VOS_TRUE;
    g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns   = VOS_TRUE;

    ucIndex                             = 0;
    gastAtClientTab[ucIndex].UserType   = AT_APP_USER;

    pstPdpEntity = AT_APP_GetPdpEntInfoAddr();
    pstPdpEntity->enIpv6State = AT_PDP_STATE_ACTED;

    // 构建消息
    m_pstEvent->stIpv6RaInfo.ulPrefixNum                      = 1;
    m_pstEvent->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen  = AT_APS_IP6_ADDR_PREFIX_BYTE_LEN+1;
    m_pstEvent->stIpv6RaInfo.bitOpMtu                         = VOS_TRUE;

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    At_MsgProc((MsgBlock*)m_pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafPsEvtReportRaInfo,Test_AT_RcvTafPsEvtReportRaInfo_006)
{
    AT_PDP_ENTITY_STRU                 *pstPdpEntity;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           *pucSystemAppConfig;

    /* 初始化 */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns   = VOS_TRUE;
    g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns   = VOS_TRUE;

    ucIndex                             = 0;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;

    pstPdpEntity = AT_APP_GetPdpEntInfoAddr();
    pstPdpEntity->enIpv6State = AT_PDP_STATE_ACTED;

    // 构建消息
    m_pstEvent->stIpv6RaInfo.ulPrefixNum                      = 1;
    m_pstEvent->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen  = AT_APS_IP6_ADDR_PREFIX_BYTE_LEN+1;
    m_pstEvent->stIpv6RaInfo.bitOpMtu                         = VOS_TRUE;

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(),outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    At_MsgProc((MsgBlock*)m_pRcvMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif


class Test_AT_SetMemStatusRspProc: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex     = 0;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SetMemStatusRspProc, Test_AT_SetMemStatusRspProc_001)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;

    /* 初始化变量 */
    PS_MEM_SET(&stEvent, 0x00, sizeof(MN_MSG_EVENT_INFO_STRU));
    stEvent.u.stMemStatusInfo.bSuccess  = VOS_TRUE;
    stEvent.u.stMemStatusInfo.enMemFlag = MN_MSG_MEM_FULL_SET;
    stEvent.u.stMemStatusInfo.enMemFlag = MN_ERR_NO_ERROR;

    /* 初始化全局变量 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSASM_SET;

    /* 桩函数 */
    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    /* 调用消息入口函数 */
    AT_SetMemStatusRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    /* 结果验证*/
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetMemStatusRspProc, Test_AT_SetMemStatusRspProc_002)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;

    /* 初始化变量 */
    PS_MEM_SET(&stEvent, 0x00, sizeof(MN_MSG_EVENT_INFO_STRU));
    stEvent.u.stMemStatusInfo.bSuccess  = VOS_TRUE;
    stEvent.u.stMemStatusInfo.enMemFlag = MN_MSG_MEM_FULL_SET;
    stEvent.u.stMemStatusInfo.enMemFlag = MN_ERR_NO_ERROR;

    ucIndex                             = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 初始化全局变量 */

    /* 桩函数 */
    MOCKER(AT_StopRelTimer)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用消息入口函数 */
    AT_SetMemStatusRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    /* 结果验证*/

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetMemStatusRspProc, Test_AT_SetMemStatusRspProc_003)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;

    /* 初始化变量 */
    PS_MEM_SET(&stEvent, 0x00, sizeof(MN_MSG_EVENT_INFO_STRU));
    stEvent.u.stMemStatusInfo.bSuccess  = VOS_TRUE;
    stEvent.u.stMemStatusInfo.enMemFlag = MN_MSG_MEM_FULL_SET;
    stEvent.u.stMemStatusInfo.enMemFlag = MN_ERR_NO_ERROR;

    ucIndex                             = 0;

    /* 初始化全局变量 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    /* 桩函数 */
    MOCKER(AT_StopRelTimer)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(never());

    /* 调用消息入口函数 */
    AT_SetMemStatusRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    /* 结果验证*/

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetMemStatusRspProc, Test_AT_SetMemStatusRspProc_004)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;

    /* 初始化变量 */
    PS_MEM_SET(&stEvent, 0x00, sizeof(MN_MSG_EVENT_INFO_STRU));
    stEvent.u.stMemStatusInfo.bSuccess  = VOS_FALSE;
    stEvent.u.stMemStatusInfo.enMemFlag = MN_MSG_MEM_FULL_SET;
    stEvent.u.stMemStatusInfo.enMemFlag = MN_ERR_NO_ERROR;

    /* 初始化全局变量 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSASM_SET;

    /* 桩函数 */
    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));;

    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_ERROR));

    /* 调用消息入口函数 */
    AT_SetMemStatusRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    /* 结果验证*/
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}



#if 0

TEST(Test_AT_ClearDtmfInfo,Test_AT_ClearDtmfInfo_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;

    ////参数初始化
    ucIndex                                    = 0;

    //// 初始化全局变量;

    //// MOCKER操作;
    //MOCKER(At_FormatResultData)
    //    .expects(never());


    //// 调用被测函数
    AT_ClearDtmfInfo(ucIndex);

    // 执行检查

    GlobalMockObject::verify();

}

TEST(Test_AT_ClearDtmfInfo,Test_AT_ClearDtmfInfo_002)
{
     // 变量声明
    VOS_UINT8                           ucIndex;

    ////参数初始化
    ucIndex                                    = 0;

    //// 初始化全局变量;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

    //// MOCKER操作;
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(259),any())
        .will(returnValue(VOS_ERR));


    //// 调用被测函数
    AT_ClearDtmfInfo(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_DTMF_STOP, pstCcCtx->stDtmfPara.ulOnLength);
    GlobalMockObject::verify();
}
#endif

class Test_At_SsRspCusdProc: public ::testing::Test
{
public:
    TAF_UINT8  ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU   stEvent;

    void SetUp()
	{
		UT_STUB_INIT();
        ucIndex = 0;
    }

    void TearDown()
    {
    }
};


TEST_F(Test_At_SsRspCusdProc, Test_At_SsRspCusdProc_001)
{
    TAF_UINT32                          ulResult;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CUSD_REQ;
    stEvent.SsEvent = TAF_SS_EVT_ERROR;
    stEvent.ErrorCode = TAF_ERR_PARA_ERROR;//

    ulResult = AT_CME_INCORRECT_PARAMETERS;
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(ulResult));

    At_SsRspCusdProc(0, &stEvent);

    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


class Test_At_SsRspProc: public ::testing::Test
{
public:
    TAF_UINT8  ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU   stEvent;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
    }

    void TearDown()
    {
    }
};


TEST_F(Test_At_SsRspProc, Test_At_SsRspProc_001)
{
    TAF_UINT32                          ulResult;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CUSD_REQ;
    stEvent.SsEvent = TAF_SS_EVT_ERROR;
    stEvent.ErrorCode = TAF_ERR_PARA_ERROR;//

    ulResult = AT_CME_INCORRECT_PARAMETERS;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    At_SsRspCusdProc(0, (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&stEvent);

    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_SsRspProc, Test_At_SsRspProc_002)
{
    TAF_UINT32                          ulResult;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CUSD_REQ;
    stEvent.SsEvent = TAF_SS_EVT_USSD_DATA_SND;

    ulResult = AT_OK;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    At_SsRspCusdProc(0, (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&stEvent);

    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_SsRspProc, Test_At_SsRspProc_003)
{
    TAF_UINT32                          ulResult;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SS_ERASE;
    stEvent.SsEvent = TAF_SS_EVT_ERROR;
    stEvent.ErrorCode = TAF_ERR_TIME_OUT;

    ulResult = AT_CME_NETWORK_TIMEOUT;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    At_SsRspCusdProc(0, (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&stEvent);

    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_SsRspProc, Test_At_SsRspProc_004)
{
    TAF_UINT32                          ulResult;

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SS_ERASE;
    stEvent.SsEvent = TAF_SS_EVT_ERASESS_CNF;
    stEvent.OP_Error = 0;

    ulResult = AT_OK;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    At_SsRspCusdProc(0, (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&stEvent);

    EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



TEST_F(Test_At_SsRspProc,Test_At_SsRspProc_123)
{
    TAF_UINT8                                       ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU              enEvent;

    ucIndex = 0;

    gastAtClientTab[ucIndex].CmdIndex = AT_CMD_CUSD;

    MOCKER(At_SsRspCusdProc)
        .expects(exactly(0));

    At_SsRspProc(ucIndex,&enEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspProc,Test_At_SsRspProc_124)
{
    TAF_UINT8                                       ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU              enEvent;

    ucIndex = 0;
    enEvent.SsEvent = TAF_SS_EVT_ERROR;


    MOCKER(At_ChgTafErrorCode)
        .expects(exactly(0));

    MOCKER(At_FormatResultData)
        .expects(exactly(0));

    At_SsRspProc(ucIndex,(TAF_SS_CALL_INDEPENDENT_EVENT_STRU* )&enEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspProc,Test_At_SsRspProc_125)
{
    TAF_UINT8                                       ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU              enEvent;

    ucIndex = 0;
    enEvent.SsEvent = TAF_SS_EVT_INTERROGATESS_CNF;

    MOCKER(At_SsRspInterrogateCnfProc)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    At_SsRspProc(ucIndex,(TAF_SS_CALL_INDEPENDENT_EVENT_STRU* )&enEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspProc,Test_At_SsRspProc_126)
{
    VOS_UINT8                                       ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU              enEvent;

    ucIndex = 0;
    enEvent.SsEvent = TAF_SS_EVT_ERASESS_CNF;
    enEvent.OP_Error = 0;


    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_OK));

    At_SsRspProc(ucIndex,(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&enEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspProc,Test_At_SsRspProc_127)
{
    TAF_UINT8                                       ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU              enEvent;

    ucIndex = 0;
    enEvent.SsEvent = TAF_SS_EVT_ERASESS_CNF;
    enEvent.OP_Error = 1;

    MOCKER(At_ChgTafErrorCode)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_CME_UNKNOWN));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    At_SsRspProc(ucIndex,(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&enEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspProc,Test_At_SsRspProc_128)
{
    TAF_UINT8                                       ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU              enEvent;

    ucIndex = 0;
    enEvent.SsEvent = TAF_SS_EVT_USS_NOTIFY_IND;

    MOCKER(At_SsRspUssdProc)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    At_SsRspProc(ucIndex,(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&enEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspProc,Test_At_SsRspProc_129)
{
    TAF_UINT8                                       ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU              enEvent;

    ucIndex = 0;
    enEvent.SsEvent = TAF_SS_EVT_GET_PASSWORD_IND;

   // MOCKER(TAF_GetPasswordRsp)
    //    .expects(exactly(1))
     //   .will(returnValue(0));

    At_SsRspProc(ucIndex,(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&enEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspProc,Test_At_SsRspProc_130)
{
    TAF_UINT8                                       ucIndex;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU              enEvent;

    ucIndex = 0;
    enEvent.SsEvent = 20;

    At_SsRspProc(ucIndex,(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&enEvent);

    GlobalMockObject::verify();
}





class Test_At_QryCpinRspProc: public ::testing::Test
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



TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_001)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_SIM_PIN;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(14, usLength);

    GlobalMockObject::verify();
}


TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_002)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_SIM_PUK;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(14, usLength);

    GlobalMockObject::verify();
}


TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_003)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_PHNET_PIN;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(17, usLength);

    //GlobalMockObject::verify();
}


TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_004)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_PHNET_PUK;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(17, usLength);

    //GlobalMockObject::verify();
}


TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_005)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_PHNETSUB_PIN;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(20, usLength);

    //GlobalMockObject::verify();
}


TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_006)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_PHNETSUB_PUK;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(20, usLength);

    //GlobalMockObject::verify();
}




TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_007)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_PHSP_PIN;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(16, usLength);

    //GlobalMockObject::verify();
}


TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_008)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_PHSP_PUK;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(16, usLength);

    //GlobalMockObject::verify();
}


TEST_F(Test_At_QryCpinRspProc, Test_At_QryCpinRspProc_009)
{
    // 变量声明
    VOS_UINT8                       ucIndex = 0;
    TAF_PH_PIN_TYPE     ucPinType = TAF_SIM_PIN2;
    VOS_UINT16                  usLength = 0;
    VOS_CHAR                    *pcCmdName = "+CPIN";
    // 参数初始化

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8 *)pcCmdName;
    // MOCKER操作;


    // 调用被测函数
    At_QryCpinRspProc(ucIndex, ucPinType, &usLength);

    // 执行检查
    EXPECT_EQ(12, usLength);

    //GlobalMockObject::verify();
}


class Test_At_PhRspProc: public ::testing::Test
{
public:
    TAF_PHONE_EVENT_INFO_STRU   stEvent;
    VOS_UINT8                   ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;

        ucIndex                         = 0;

        PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PHONE_EVENT_INFO_STRU));

        pstAbortCmdPara = AT_GetAbortCmdPara();

        pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, "AT");

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtRspStr, "ABORT");
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_001)
{
    // 变量声明
    VOS_UINT16                          usLength;

    // 参数初始化
    usLength    = 100;
    stEvent.PhoneEvent              = TAF_PH_EVT_OP_PIN_CNF;
    stEvent.PinCnf.OpPinResult      = TAF_PH_OP_PIN_OK;
    stEvent.PinCnf.CmdType          = TAF_PIN_QUERY;

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex = AT_CMD_CPIN;
    gstAtSendData.usBufLen = 0;

    // MOCKER操作;
    MOCKER(At_QryCpinRspProc)
        .stubs()
        .with(eq(ucIndex), eq((TAF_PH_PIN_TYPE)stEvent.PinCnf.PinType), outBoundP((VOS_UINT16 *)&usLength, (VOS_UINT32)sizeof(usLength)));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_PhRspProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(gstAtSendData.usBufLen, usLength);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_002)
{
    // 变量声明

    // 参数初始化
    stEvent.PhoneEvent              = TAF_PH_EVT_OP_PIN_CNF;
    stEvent.PinCnf.OpPinResult      = TAF_PH_OP_PIN_OK;
    stEvent.PinCnf.CmdType          = TAF_PIN2_QUERY;

    // 初始化全局变量;
    g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex = AT_CMD_CPIN;
    gstAtSendData.usBufLen = 0;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    At_PhRspProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(gstAtSendData.usBufLen, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_003)
{
    TAF_PHONE_EVENT_INFO_STRU           stEvent;

    /* 初始化全局变量 */
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));


    /* 参数初始化 */
    stEvent.PhoneEvent              = TAF_PH_EVT_PLMN_LIST_ABORT_CNF;

    MOCKER(DIAG_LogReport)
        .expects(exactly(0));

    At_PhRspProc(0, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_004)
{
    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    TAF_PHONE_EVENT_INFO_STRU           stEvent;

    /* 初始化全局变量 */
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_COPS_ABORT_PLMN_LIST;

    /* 构造ABORT返回结果 */
    usLength  = 0;
    ulTmp     = 0;

    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 参数初始化 */
    stEvent.PhoneEvent              = TAF_PH_EVT_PLMN_LIST_ABORT_CNF;

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    At_PhRspProc(0, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    EXPECT_STREQ((VOS_CHAR*)aucDataAt, (VOS_CHAR*)(pgucAtSndCodeAddr));

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_005)
{
    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    TAF_PHONE_EVENT_INFO_STRU           stEvent;
    AT_PAR_CMD_ELEMENT_STRU             stCopsCmd =
    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    VOS_NULL_PTR,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2,7)"};

    /* 初始化全局变量 */
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_COPS_ABORT_PLMN_LIST;

    g_stParseContext[0].pstCmdElement = &stCopsCmd;

    /* 构造ABORT返回结果 */
    usLength  = 0;
    ulTmp     = 0;

    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 参数初始化 */
    stEvent.PhoneEvent              = TAF_PH_EVT_PLMN_LIST_CNF;

    At_PhRspProc(0, &stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_006)
{
    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    TAF_PHONE_EVENT_INFO_STRU           stEvent;
    AT_PAR_CMD_ELEMENT_STRU             stCopsCmd =
    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    VOS_NULL_PTR,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2,7)"};

    /* 初始化全局变量 */
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_COPS_TEST;
    stEvent.OP_PhoneError = VOS_TRUE;

    g_stParseContext[0].pstCmdElement = &stCopsCmd;

    /* 构造ABORT返回结果 */
    usLength  = 0;
    ulTmp     = 0;

    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 参数初始化 */
    stEvent.PhoneEvent              = TAF_PH_EVT_PLMN_LIST_CNF;

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    At_PhRspProc(0, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_007)
{
    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    TAF_PHONE_EVENT_INFO_STRU           stEvent;
    AT_PAR_CMD_ELEMENT_STRU             stCopsCmd =
    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    VOS_NULL_PTR,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2,7)"};

    /* 初始化全局变量 */
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_COPS_ABORT_PLMN_LIST;

    g_stParseContext[0].pstCmdElement = &stCopsCmd;

    /* 构造ABORT返回结果 */
    usLength  = 0;
    ulTmp     = 0;

    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 参数初始化 */
    stEvent.PhoneEvent              = TAF_PH_EVT_PLMN_LIST_ABORT_CNF;

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    At_PhRspProc(0, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_LTE)

TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_008)
{
    VOS_UINT8       ucIndex;
    TAF_PHONE_EVENT_INFO_STRU  stEvent;

    // 参数初始化
    ucIndex = AT_CLIENT_BUTT;
    stEvent.PhoneEvent = TAF_PH_EVT_OP_PIN_CNF;
    stEvent.OP_PhoneError = 1;
    stEvent.PinCnf.CmdType = TAF_PIN_VERIFY;


    /* 相关全局变量初始化 */

    // MOCKER操作
    MOCKER(At_ChgTafErrorCode)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_CME_SIM_PUK_REQUIRED));

    MOCKER(At_FormatResultData)
        .expects(never());

    MOCKER(AT_PhSendNeedPuk)
        .expects(never());

    // 调用被测函数
    At_PhRspProc(ucIndex, &stEvent);
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_009)
{
    VOS_UINT8       ucIndex;
    TAF_PHONE_EVENT_INFO_STRU  stEvent;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    stEvent.PhoneEvent = TAF_PH_EVT_OPER_MODE_CNF;
    stEvent.OP_PhoneError = 1;
    stEvent.PinCnf.CmdType = TAF_PIN_VERIFY;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TMODE_SET;

    /* 相关全局变量初始化 */

    // MOCKER操作
    MOCKER(AT_IsModemSupportRat)
        .expects(never())
        .will(returnValue((VOS_UINT8)VOS_TRUE));

    MOCKER(atSendFtmDataMsg)
        .expects(never())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData).expects(exactly(1));
    // 调用被测函数
    At_PhRspProc(ucIndex, &stEvent);
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_010)
{
    VOS_UINT8       ucIndex;
    TAF_PHONE_EVENT_INFO_STRU  stEvent;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    stEvent.PhoneEvent = TAF_PH_EVT_OPER_MODE_CNF;
    stEvent.OP_PhoneError = 1;
    stEvent.PinCnf.CmdType = TAF_PIN_VERIFY;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_TMODE;
    /* 相关全局变量初始化 */

    // MOCKER操作
    MOCKER(AT_IsModemSupportRat)
        .expects(never())
        .will(returnValue((VOS_UINT8)VOS_TRUE));

    MOCKER(AT_ProcOperModeWhenLteOn)
        .expects(never())
        .will(returnValue((TAF_UINT32)VOS_OK));

    MOCKER(At_FormatResultData).expects(exactly(1));
    // 调用被测函数
    At_PhRspProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);
    GlobalMockObject::verify();
}


TEST_F(Test_At_PhRspProc, Test_At_PhRspProc_016)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU           stEvent;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    // 参数初始化
    memset(&stEvent, 0, sizeof(stEvent));
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    stEvent.ulMsgName = ID_TAF_MMA_PREF_PLMN_TYPE_SET_CNF;
    stEvent.enPrefPlmnType = MN_PH_PREF_PLMN_HPLMN;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_SET_PREF_PLMN_TYPE;

    /* 相关全局变量初始化 */

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .times(1)
        .with(eq(ucIndex),eq(AT_OK));

    // 调用被测函数
    AT_RcvMmaPrefPlmnTypeSetCnf((VOS_VOID *)&stEvent);

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    ASSERT_EQ(MN_PH_PREF_PLMN_HPLMN, pstNetCtx->enPrefPlmnType);

    GlobalMockObject::verify();
}



class Test_AT_ProcOperModeWhenLteOn: public ::testing::Test
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


TEST_F(Test_AT_ProcOperModeWhenLteOn, Test_AT_ProcOperModeWhenLteOn_001)
{
    VOS_UINT8       ucIndex;
    TAF_UINT32      ulRst;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_TMODE;
    g_ulLteIsSend2Dsp = 1;
    g_ulGuOnly = 1;

    MOCKER(atSetTmodePara).expects(exactly(1)).will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRst = AT_ProcOperModeWhenLteOn(ucIndex);

    EXPECT_EQ((TAF_UINT32)VOS_OK, ulRst);

    GlobalMockObject::verify();
}

#endif

class Test_AT_PhnEvtPlmnList: public ::testing::Test
{
public:
    TAF_PHONE_EVENT_INFO_STRU   stEvent;
    VOS_UINT8                   ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                         = 0;
        PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_PhnEvtPlmnList, Test_AT_PhnEvtPlmnList_001)
{
    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    TAF_UINT32                          ulRtn = 0;

    /* 初始化全局变量 */
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    g_stParseContext[0].pstCmdElement = VOS_NULL_PTR;

    /* 构造ABORT返回结果 */
    usLength  = 0;
    ulTmp     = 0;

    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 参数初始化 */
    stEvent.PhoneEvent              = TAF_PH_EVT_PLMN_LIST_CNF;
    stEvent.OP_PhoneError           = VOS_TRUE;
    ulRtn                           = AT_PhnEvtPlmnList(0, &stEvent);

    EXPECT_EQ((TAF_UINT32)AT_CME_UNKNOWN, ulRtn);
}


TEST_F(Test_AT_PhnEvtPlmnList, Test_AT_PhnEvtPlmnList_002)
{
    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    TAF_UINT32                          ulRtn = 0;

    AT_PAR_CMD_ELEMENT_STRU             stElement;
    VOS_UINT8                           szCmdName[32];

    /* 初始化全局变量 */
    VOS_StrCpy((VOS_CHAR*)szCmdName,"+cops");
    g_stParseContext[0].pstCmdElement = &stElement;
    stElement.pszCmdName                    = szCmdName;
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    g_stParseContext[0].pstCmdElement->pszCmdName = (VOS_UINT8*)"+COPS";

    /* 构造ABORT返回结果 */
    usLength  = 0;
    ulTmp     = 0;

    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 参数初始化 */
    stEvent.PhoneEvent                  = TAF_PH_EVT_PLMN_LIST_CNF;
    stEvent.OP_PhoneError               = VOS_FALSE;
    stEvent.PlmnList.ucPlmnNum          = 2;
    stEvent.PlmnList.PlmnInfo[0].RaMode = TAF_PH_RA_WCDMA;
    stEvent.PlmnList.Plmn[0].Mnc        = 0x604;
    stEvent.PlmnList.Plmn[0].Mcc        = 0xF02000;
    stEvent.PlmnList.PlmnInfo[1].RaMode = TAF_PH_RA_LTE;
    stEvent.PlmnList.Plmn[1].Mnc        = 0x604;
    stEvent.PlmnList.Plmn[1].Mcc        = 0xF02000;
    ulRtn                               = AT_PhnEvtPlmnList(0, &stEvent);

    EXPECT_EQ((TAF_UINT32)AT_OK, ulRtn);
}


TEST_F(Test_AT_PhnEvtPlmnList, Test_AT_PhnEvtPlmnList_003)
{
    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    TAF_UINT32                          ulRtn = 0;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    VOS_UINT8                           szCmdName[32];

    /* 初始化全局变量 */
    VOS_StrCpy((VOS_CHAR*)szCmdName,"+cops");
    g_stParseContext[0].pstCmdElement = &stElement;
    stElement.pszCmdName                    = szCmdName;
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    g_stParseContext[0].pstCmdElement->pszCmdName = (VOS_UINT8*)"+COPS";

    /* 构造ABORT返回结果 */
    usLength  = 0;
    ulTmp     = 0;

    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 参数初始化 */
    stEvent.PhoneEvent                  = TAF_PH_EVT_PLMN_LIST_CNF;
    stEvent.OP_PhoneError               = VOS_FALSE;
    stEvent.PlmnList.ucPlmnNum          = 1;
    stEvent.PlmnList.PlmnInfo[0].RaMode = TAF_PH_RA_GSM;
    stEvent.PlmnList.Plmn[0].Mnc        = 0x604;
    stEvent.PlmnList.Plmn[0].Mcc        = 0xF02000;
    ulRtn                               = AT_PhnEvtPlmnList(0, &stEvent);

    EXPECT_EQ((TAF_UINT32)AT_OK, ulRtn);
}







class Test_At_StkCsinIndPrint: public ::testing::Test
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


TEST_F(Test_At_StkCsinIndPrint, Test_At_StkCsinIndPrint_001)
{
    SI_STK_EVENT_INFO_STRU              stEvent;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucIndex                                 =   0;
    stEvent.STKCmdStru.SatCmd.SatDataLen    =   2;
    stEvent.STKCmdStru.SatType              =   SI_STK_TIMERMANAGEMENT;
    stEvent.STKCmdStru.SatCmd.SatCmdData[0] =   0xD0;
    stEvent.STKCmdStru.SatCmd.SatCmdData[1] =   0x09;

    /* 调用被测函数 */
    At_StkCsinIndPrint(ucIndex, (SI_STK_EVENT_INFO_STRU *)&stEvent);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_STKCnfMsgProc: public ::testing::Test
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


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_001)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType   =   SYSTEM_APP_ANDROID;
    ucIndex     =   AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_002)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_ANDROID;
    ucIndex                         =   AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_TERMINAL_RSP_EVENT;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_003)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_ANDROID;
    ucIndex                         =   0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_TERMINAL_RSP_EVENT;
    stCnfMsg.stSTKAtCnf.STKErrorNo  =   TAF_ERR_SIM_FAIL;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_ChgTafErrorCode)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_CME_SIM_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_004)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_ANDROID;
    ucIndex                         =   AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_CMD_IND_EVENT;
    stCnfMsg.stSTKAtCnf.STKErrorNo  =   TAF_ERR_NO_ERROR;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_StkCsinIndPrint)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_005)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_MP;
    ucIndex                         =   AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_CMD_IND_EVENT;
    stCnfMsg.stSTKAtCnf.STKErrorNo  =   TAF_ERR_NO_ERROR;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_STKCMDTypePrint)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_006)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_ANDROID;
    ucIndex                         =   0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_GET_CMD_RSP_EVENT;
    stCnfMsg.stSTKAtCnf.STKErrorNo  =   TAF_ERR_NO_ERROR;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_StkCsinIndPrint)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_FormatResultData)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_007)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_MP;
    ucIndex                         =   0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_GET_CMD_RSP_EVENT;
    stCnfMsg.stSTKAtCnf.STKErrorNo  =   TAF_ERR_NO_ERROR;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_STKCMDDataPrintSimple)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_FormatResultData)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_008)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_MP;
    ucIndex                         =   0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_CC_RESULT_IND_EVENT;
    stCnfMsg.stSTKAtCnf.STKErrorNo  =   TAF_ERR_NO_ERROR;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_StkCcinIndPrint)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_FormatResultData)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_009)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_MP;
    ucIndex                         =   0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_SMSCTRL_RESULT_IND_EVENT;
    stCnfMsg.stSTKAtCnf.STKErrorNo  =   TAF_ERR_NO_ERROR;

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_StkCcinIndPrint)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_FormatResultData)
        .stubs()
        .will(returnValue(0));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc(&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_VSIM == FEATURE_ON)


TEST_F(Test_AT_STKCnfMsgProc, Test_AT_STKCnfMsgProc_010)
{
    MN_APP_STK_AT_CNF_STRU              stCnfMsg;
    TAF_UINT8                           ucSysType;
    TAF_UINT8                           ucIndex;
    VOS_UINT8                           aucData[5]={0x12, 0x34, 0x56, 0x78, 0x9A};

    /* 初始化局部变量 */
    ucSysType                       =   SYSTEM_APP_MP;
    ucIndex                         =   0;
    stCnfMsg.stSTKAtCnf.STKCBEvent  =   SI_STK_SMS_PP_DL_DATA_IND_EVENT;
    stCnfMsg.stSTKAtCnf.STKErrorNo  =   TAF_ERR_NO_ERROR;
    stCnfMsg.stSTKAtCnf.STKCmdStru.CmdStru.SmsPpDlDataInfo.ucLen = 5;
    VOS_MemCpy(stCnfMsg.stSTKAtCnf.STKCmdStru.CmdStru.SmsPpDlDataInfo.aucData, aucData, sizeof(aucData));

    /* 对函数打桩 */
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSysType));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    /* 调用被测函数 */
    AT_STKCnfMsgProc((MN_APP_STK_AT_CNF_STRU *)&stCnfMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

class Test_AT_CsRspEvtConnectProc: public ::testing::Test
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


TEST(Test_AT_CsRspEvtConnectProc,Test_AT_CsRspEvtConnectProc_001)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_CONNECT;
    ucIndex = 0;
    stCallInfo.enCallDir = MN_CALL_DIR_MO;
    AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucColpType = AT_COLP_ENABLE_TYPE;


    /*MOCKER(At_sprintf)
        .expects(exactly(7));*/

    MOCKER(AT_BcdNumberToAscii)
        .expects(exactly(0));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    AT_CsRspEvtConnectProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    ASSERT_EQ((TAF_CS_CAUSE_ENUM_UINT32)TAF_CS_CAUSE_SUCCESS, AT_GetCsCallErrCause(0));

    GlobalMockObject::verify();
}


TEST(Test_AT_CsRspEvtConnectProc,Test_AT_CsRspEvtConnectProc_002)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_CONNECT;
    ucIndex = 0;
    stCallInfo.enCallDir = MN_CALL_DIR_MO;
    AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucColpType = AT_COLP_ENABLE_TYPE;
    stCallInfo.stConnectNumber.ucNumLen = 0;


    /*MOCKER(At_sprintf)
        .expects(exactly(7));*/

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    AT_CsRspEvtConnectProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


TEST(Test_AT_CsRspEvtConnectProc,Test_AT_CsRspEvtConnectProc_003)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_CONNECT;
    ucIndex = 0;
    stCallInfo.enCallDir = MN_CALL_DIR_MO;
    AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucColpType = AT_COLP_DISABLE_TYPE;


    /*MOCKER(At_sprintf)
        .expects(exactly(4));*/

    MOCKER(At_SendResultData)
        .expects(exactly(0));

    AT_CsRspEvtConnectProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


TEST(Test_AT_CsRspEvtConnectProc,Test_AT_CsRspEvtConnectProc_004)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_CONNECT;
    ucIndex = 0;
    stCallInfo.enCallType = MN_CALL_TYPE_VIDEO;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;


    MOCKER(At_SetMode)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_CONNECT));

    AT_CsRspEvtConnectProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


TEST(Test_AT_CsRspEvtConnectProc,Test_AT_CsRspEvtConnectProc_005)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_CONNECT;
    ucIndex = 0;
    stCallInfo.enCallDir = MN_CALL_DIR_MO;
    AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucColpType = AT_COLP_ENABLE_TYPE;


    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue(VOS_ERR));

    AT_CsRspEvtConnectProc(ucIndex,enEvent,&stCallInfo);

    ASSERT_EQ(0, AT_GetCsCallErrCause(0));

    GlobalMockObject::verify();
}



class Test_AT_IsFindVedioModemStatus: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        gastAtClientTab[2].UserType         = AT_BUTT_USER;
        gastAtClientTab[2].Mode        = 0;
        gastAtClientTab[2].DataMode    = 0;

    }
    void TearDown()
    {
        gastAtClientTab[2].UserType         = AT_BUTT_USER;
        gastAtClientTab[2].Mode        = 0;
        gastAtClientTab[2].DataMode    = 0;

    }
};


TEST(Test_AT_IsFindVedioModemStatus,Test_AT_IsFindVedioModemStatus_001)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_TYPE_ENUM_U8                enCallType;

    ucIndex     = 2;
    enCallType  = MN_CALL_TYPE_VIDEO;

    PS_MEM_SET(gastAtClientTab,0x00,sizeof(gastAtClientTab));
    gastAtClientTab[2].UserType         = AT_MODEM_USER;
    gastAtClientTab[2].Mode        = AT_DATA_MODE;
    gastAtClientTab[2].DataMode    = AT_CSD_DATA_MODE;

    MOCKER(At_SetMode)
        .expects(exactly(1));

    MOCKER(AT_SetModemStatus)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_EventReport)
        .expects(exactly(1));

    EXPECT_EQ((VOS_BOOL)VOS_TRUE,AT_IsFindVedioModemStatus(ucIndex,enCallType));

    GlobalMockObject::verify();

}


TEST(Test_AT_IsFindVedioModemStatus,Test_AT_IsFindVedioModemStatus_002)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_TYPE_ENUM_U8                enCallType;

    ucIndex     = 0;
    enCallType  = MN_CALL_TYPE_VIDEO;

    PS_MEM_SET(gastAtClientTab,0x00,sizeof(gastAtClientTab));
    gastAtClientTab[1].UserType         = AT_MODEM_USER;
    gastAtClientTab[1].Mode        = AT_DATA_MODE;
    gastAtClientTab[1].DataMode    = AT_CSD_DATA_MODE;

    MOCKER(At_SetMode)
        .expects(never());

    MOCKER(AT_SetModemStatus)
        .expects(never());

    EXPECT_EQ((VOS_BOOL)VOS_FALSE,AT_IsFindVedioModemStatus(ucIndex,enCallType));

    GlobalMockObject::verify();

}

TEST(Test_AT_IsFindVedioModemStatus,Test_AT_IsFindVedioModemStatus_003)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_TYPE_ENUM_U8                enCallType;

    ucIndex     = 2;
    enCallType  = MN_CALL_TYPE_VOICE;

    PS_MEM_SET(gastAtClientTab,0x00,sizeof(gastAtClientTab));

    EXPECT_EQ(VOS_FALSE,AT_IsFindVedioModemStatus(ucIndex,enCallType));

     GlobalMockObject::verify();

}


class Test_AT_ConvertSysCfgRatOrderToStr: public ::testing::Test
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

#if (FEATURE_ON == FEATURE_LTE)

TEST(Test_AT_ConvertSysCfgRatOrderToStr,Test_AT_ConvertSysCfgRatOrderToStr_001)
{
    TAF_MMA_RAT_ORDER_STRU               stRatOrder;
    VOS_UINT8                           aucAcqorder[7];
    VOS_CHAR                           *pcExpactedStr;

    pcExpactedStr = "00";

    stRatOrder.ucRatOrderNum = TAF_PH_MAX_GUL_RAT_NUM;
    stRatOrder.aenRatOrder[0] = TAF_MMA_RAT_LTE;
    stRatOrder.aenRatOrder[1] = TAF_MMA_RAT_WCDMA;
    stRatOrder.aenRatOrder[2] = TAF_MMA_RAT_GSM;
    AT_ConvertSysCfgRatOrderToStr((TAF_MMA_RAT_ORDER_STRU *)&stRatOrder, aucAcqorder);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)aucAcqorder);

    GlobalMockObject::verify();

}


TEST(Test_AT_ConvertSysCfgRatOrderToStr,Test_AT_ConvertSysCfgRatOrderToStr_002)
{
    TAF_MMA_RAT_ORDER_STRU               stRatOrder;
    VOS_UINT8                           aucAcqorder[7];
    VOS_CHAR                           *pcExpactedStr;

    pcExpactedStr = "0302";

    stRatOrder.ucRatOrderNum = TAF_PH_MAX_GUL_RAT_NUM;
    stRatOrder.aenRatOrder[0] = TAF_MMA_RAT_LTE;
    stRatOrder.aenRatOrder[1] = TAF_MMA_RAT_WCDMA;
    stRatOrder.aenRatOrder[2] = TAF_MMA_RAT_BUTT;
    AT_ConvertSysCfgRatOrderToStr((TAF_MMA_RAT_ORDER_STRU *)&stRatOrder, aucAcqorder);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)aucAcqorder);

    GlobalMockObject::verify();

}
#else

TEST(Test_AT_ConvertSysCfgRatOrderToStr,Test_AT_ConvertSysCfgRatOrderToStr_003)
{
    TAF_MMA_RAT_ORDER_STRU               stRatOrder;
    VOS_UINT8                           aucAcqorder[7];
    VOS_CHAR                           *pcExpactedStr;

    pcExpactedStr = "00";

    stRatOrder.ucRatOrderNum = TAF_PH_MAX_GU_RAT_NUM;
    stRatOrder.aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
    stRatOrder.aenRatOrder[1] = TAF_MMA_RAT_GSM;
    AT_ConvertSysCfgRatOrderToStr((TAF_MMA_RAT_ORDER_STRU *)&stRatOrder, aucAcqorder);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)aucAcqorder);

    GlobalMockObject::verify();

}


TEST(Test_AT_ConvertSysCfgRatOrderToStr,Test_AT_ConvertSysCfgRatOrderToStr_004)
{
    TAF_MMA_RAT_ORDER_STRU               stRatOrder;
    VOS_UINT8                           aucAcqorder[7];
    VOS_CHAR                           *pcExpactedStr;

    pcExpactedStr = "02";

    stRatOrder.ucRatOrderNum  = 1;
    stRatOrder.aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
    stRatOrder.aenRatOrder[1] = TAF_MMA_RAT_BUTT;
    AT_ConvertSysCfgRatOrderToStr((TAF_MMA_RAT_ORDER_STRU *)&stRatOrder, aucAcqorder);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)aucAcqorder);

    GlobalMockObject::verify();

}
#endif



class Test_At_CsIndProc: public ::testing::Test
{
    VOS_UINT16             usLoop;
public:
    void SetUp()
    {
        UT_STUB_INIT();
        for(usLoop = 0; usLoop < AT_MAX_CLIENT_NUM; usLoop++)
        {
            gastAtClientTab[usLoop].UserType = 0;
        }

        AT_GetModemCcCtxAddrFromClientId(0)->ulCurIsExistCallFlag = VOS_FALSE;
        AT_GetModemCcCtxAddrFromClientId(0)->stS0TimeInfo.ucS0TimerLen = 0;
        AT_GetModemCcCtxAddrFromClientId(0)->stS0TimeInfo.bTimerStart  = VOS_FALSE;
    }
    void TearDown()
    {
        for(usLoop = 0; usLoop < AT_MAX_CLIENT_NUM; usLoop++)
        {
            gastAtClientTab[usLoop].UserType = 0;
        }

        AT_GetModemCcCtxAddrFromClientId(0)->ulCurIsExistCallFlag = VOS_FALSE;
        AT_GetModemCcCtxAddrFromClientId(0)->stS0TimeInfo.ucS0TimerLen = 0;
        AT_GetModemCcCtxAddrFromClientId(0)->stS0TimeInfo.bTimerStart  = VOS_FALSE;
    }
};


TEST(Test_At_CsIndProc, Test_At_CsIndProc_001)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    ucIndex = 0;

    AT_GetModemCcCtxAddrFromClientId(ucIndex)->ulCurIsExistCallFlag = VOS_FALSE;

    enEvent = MN_CALL_EVT_INCOMING;

    MOCKER(At_CsIncomingEvtIndProc)
        .expects(exactly(1));

    At_CsIndProc(ucIndex,enEvent,&stCallInfo);

    EXPECT_EQ((VOS_UINT32)VOS_TRUE, AT_GetModemCcCtxAddrFromClientId(ucIndex)->ulCurIsExistCallFlag);
    GlobalMockObject::verify();
}


TEST(Test_At_CsIndProc,Test_At_CsIndProc_002)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_RELEASED;
    ucIndex = 0;

    stCallInfo.enCallType = MN_CALL_TYPE_VIDEO;
    gastAtClientTab[0].UserType = AT_MODEM_USER;

    MOCKER(AT_EventReport)
        .expects(exactly(1));

    At_CsIndProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


TEST(Test_At_CsIndProc,Test_At_CsIndProc_003)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_RELEASED;
    ucIndex = 0;
    stCallInfo.enCallType = MN_CALL_TYPE_VIDEO;
    gastAtClientTab[0].UserType = 0;

    MOCKER(AT_EventReport)
        .expects(exactly(0));

    At_CsIndProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


TEST(Test_At_CsIndProc,Test_At_CsIndProc_004)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_RELEASED;
    ucIndex = 0;

    AT_GetModemCcCtxAddrFromClientId(ucIndex)->stS0TimeInfo.ucS0TimerLen = 10;
    AT_GetModemCcCtxAddrFromClientId(ucIndex)->stS0TimeInfo.bTimerStart  = VOS_TRUE;

    stCallInfo.enCallType = MN_CALL_TYPE_VOICE;

    MOCKER(AT_EventReport)
        .expects(exactly(0));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_VoiceStopRingTe)
        .expects(exactly(1));

    At_CsIndProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


TEST(Test_At_CsIndProc,Test_At_CsIndProc_005)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_CONNECT;
    ucIndex = 0;

    /*MOCKER(At_sprintf)
        .expects(exactly(4));*/

    MOCKER(At_SendResultData)
        .expects(exactly(0));

    MOCKER(AT_VoiceStopRingTe)
        .expects(exactly(1));

    At_CsIndProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    ASSERT_EQ((TAF_CS_CAUSE_ENUM_UINT32)TAF_CS_CAUSE_SUCCESS, AT_GetCsCallErrCause(0));

    GlobalMockObject::verify();
}


TEST(Test_At_CsIndProc,Test_At_CsIndProc_006)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_SS_NOTIFY;
    ucIndex = 0;

    MOCKER(AT_CsSsNotifyEvtIndProc)
        .expects(exactly(1));

    At_CsIndProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


TEST(Test_At_CsIndProc,Test_At_CsIndProc_007)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    enEvent = MN_CALL_EVT_UUS1_INFO;
    ucIndex = 0;

    MOCKER(AT_CsUus1InfoEvtIndProc)
        .expects(exactly(1));

    At_CsIndProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


TEST(Test_At_CsIndProc, Test_At_CsIndProc_008)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    ucIndex = 0;

    enEvent = MN_CALL_EVT_ALL_RELEASED;

    At_CsIndProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    EXPECT_EQ((VOS_UINT32)VOS_FALSE, AT_GetModemCcCtxAddrFromClientId(ucIndex)->ulCurIsExistCallFlag);
    GlobalMockObject::verify();
}


TEST(Test_At_CsIndProc, Test_At_CsIndProc_009)
{
    TAF_UINT8                           ucIndex;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    ucIndex = 0;
    stCallInfo.enCallState = MN_CALL_S_ACTIVE;

    AT_GetModemCcCtxAddrFromClientId(ucIndex)->ulCurIsExistCallFlag = VOS_FALSE;

    enEvent = MN_CALL_EVT_INCOMING;

    At_CsIndProc(ucIndex,enEvent,(MN_CALL_INFO_STRU *)&stCallInfo);

    GlobalMockObject::verify();
}


class Test_At_RcvMnCallEccNumIndProc: public ::testing::Test
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


TEST_F(Test_At_RcvMnCallEccNumIndProc, Test_At_RcvMnCallEccNumIndProc_001)
{
    MN_CALL_ECC_NUM_INFO_STRU           stEccNum;
    MN_AT_IND_EVT_STRU                 *pstEvent = VOS_NULL_PTR;

    /* 填充上报事件 */
    PS_MEM_SET(&stEccNum, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    stEccNum.enEvent    = MN_CALL_EVT_ECC_NUM_IND;
    stEccNum.usClientId = 19;
    stEccNum.ulEccNumCount = 1;
    stEccNum.astCustomEccNumList[0].ucCategory = 1;
    stEccNum.astCustomEccNumList[0].ucValidSimPresent = 1;
    stEccNum.astCustomEccNumList[0].ucEccNumLen = 0x2;
    stEccNum.astCustomEccNumList[0].aucEccNum[0] = 0x11;
    stEccNum.astCustomEccNumList[0].aucEccNum[1] = 0xF8;
    stEccNum.astCustomEccNumList[0].ulMcc = 0x104;

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(MN_CALL_ECC_NUM_INFO_STRU) + MN_AT_INTERFACE_MSG_HEADER_LEN));

    pstEvent->ulReceiverPid = WUEPS_PID_AT;
    pstEvent->ulSenderPid   = WUEPS_PID_TAF;
    pstEvent->usLen         = sizeof(MN_CALL_ECC_NUM_INFO_STRU);
    pstEvent->usMsgName     = MN_CALLBACK_CS_CALL;
    pstEvent->clientId      = AT_BUTT_CLIENT_ID;
    PS_MEM_CPY(pstEvent->aucContent, &stEccNum, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    MOCKER(At_SendResultData).expects(never());

    At_MsgProc((MsgBlock *)pstEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvMnCallEccNumIndProc, Test_At_RcvMnCallEccNumIndProc_002)
{
    MN_CALL_ECC_NUM_INFO_STRU           stEccNum;
    MN_AT_IND_EVT_STRU                 *pstEvent = VOS_NULL_PTR;

    /* 填充上报事件 */
    PS_MEM_SET(&stEccNum, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    stEccNum.enEvent    = MN_CALL_EVT_ECC_NUM_IND;
    stEccNum.usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stEccNum.ulEccNumCount = 2;
    stEccNum.astCustomEccNumList[0].ucCategory = 1;
    stEccNum.astCustomEccNumList[0].ucValidSimPresent = 1;
    stEccNum.astCustomEccNumList[0].ucEccNumLen = 0x2;
    stEccNum.astCustomEccNumList[0].aucEccNum[0] = 0x11;
    stEccNum.astCustomEccNumList[0].aucEccNum[1] = 0xF8;
    stEccNum.astCustomEccNumList[0].ulMcc = 0x104;

    stEccNum.astCustomEccNumList[1].ucCategory = 1;
    stEccNum.astCustomEccNumList[1].ucValidSimPresent = 1;
    stEccNum.astCustomEccNumList[1].ucEccNumLen = 0x2;
    stEccNum.astCustomEccNumList[1].aucEccNum[0] = 0x11;
    stEccNum.astCustomEccNumList[1].aucEccNum[1] = 0xF9;
    stEccNum.astCustomEccNumList[1].ulMcc = 0x104;

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(MN_CALL_ECC_NUM_INFO_STRU) + MN_AT_INTERFACE_MSG_HEADER_LEN));

    pstEvent->ulReceiverPid = WUEPS_PID_AT;
    pstEvent->ulSenderPid   = WUEPS_PID_TAF;
    pstEvent->usLen         = sizeof(MN_CALL_ECC_NUM_INFO_STRU);
    pstEvent->usMsgName     = MN_CALLBACK_CS_CALL;
    pstEvent->clientId      = AT_BROADCAST_CLIENT_ID_MODEM_0;
    PS_MEM_CPY(pstEvent->aucContent, &stEccNum, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    /* 允许主动上报 */
    MOCKER(At_SendResultData)
        .expects(exactly(2));

    At_MsgProc((MsgBlock *)pstEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvMnCallEccNumIndProc, Test_At_RcvMnCallEccNumIndProc_003)
{
    MN_CALL_ECC_NUM_INFO_STRU           stEccNum;
    MN_AT_IND_EVT_STRU                 *pstEvent = VOS_NULL_PTR;

    /* 填充上报事件 */
    PS_MEM_SET(&stEccNum, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    stEccNum.enEvent    = MN_CALL_EVT_ECC_NUM_IND;
    stEccNum.usClientId = MN_CLIENT_ALL;
    stEccNum.ulEccNumCount = 1;
    stEccNum.astCustomEccNumList[0].ucCategory = 1;
    stEccNum.astCustomEccNumList[0].ucValidSimPresent = 1;
    stEccNum.astCustomEccNumList[0].ucEccNumLen = 0x2;
    stEccNum.astCustomEccNumList[0].aucEccNum[0] = 0x11;
    stEccNum.astCustomEccNumList[0].aucEccNum[1] = 0xF8;
    stEccNum.astCustomEccNumList[0].ulMcc = 0x104;

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(MN_CALL_ECC_NUM_INFO_STRU) + MN_AT_INTERFACE_MSG_HEADER_LEN));

    pstEvent->ulReceiverPid = WUEPS_PID_AT;
    pstEvent->ulSenderPid   = WUEPS_PID_TAF;
    pstEvent->usLen         = sizeof(MN_CALL_ECC_NUM_INFO_STRU);
    pstEvent->usMsgName     = MN_CALLBACK_CS_CALL;
    pstEvent->clientId      = AT_BUTT_CLIENT_ID;
    PS_MEM_CPY(pstEvent->aucContent, &stEccNum, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    MOCKER(At_SendResultData)
        .stubs()
        .with(eq(0xFF), any());

    At_MsgProc((MsgBlock *)pstEvent);

    GlobalMockObject::verify();
}





class Test_AT_RcvMmaNsmStatusInd: public ::testing::Test
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


TEST_F(Test_AT_RcvMmaNsmStatusInd,Test_AT_RcvMmaNsmStatusInd_001)
{
    TAF_PHONE_EVENT_INFO_STRU           stPhoneEvent;
    MN_AT_IND_EVT_STRU                 *pstEvent = VOS_NULL_PTR;

    /* 填充上报事件 */
    stPhoneEvent.PhoneEvent    = TAF_PH_EVT_NSM_STATUS_IND;
    stPhoneEvent.OP_PlmnMode   = VOS_TRUE;
    stPhoneEvent.ucPlmnMode    = 1;
    stPhoneEvent.ClientId      = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(TAF_PHONE_EVENT_INFO_STRU) + MN_AT_INTERFACE_MSG_HEADER_LEN));

    pstEvent->ulReceiverPid = WUEPS_PID_AT;
    pstEvent->ulSenderPid   = WUEPS_PID_TAF;
    pstEvent->usLen         = sizeof(TAF_PHONE_EVENT_INFO_STRU);
    pstEvent->usMsgName     = MN_CALLBACK_PHONE;
    pstEvent->clientId      = AT_BUTT_CLIENT_ID;
    PS_MEM_CPY(pstEvent->aucContent, &stPhoneEvent, (VOS_UINT32)sizeof(TAF_PHONE_EVENT_INFO_STRU));

    MOCKER(At_SendResultData)
        .stubs()
        .with(eq((VOS_UINT8)AT_BUTT_CLIENT_ID), any(), any());
    At_MsgProc((MsgBlock *)pstEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvMmaNsmStatusInd,Test_AT_RcvMmaNsmStatusInd_002)
{
    TAF_PHONE_EVENT_INFO_STRU           stPhoneEvent;
    MN_AT_IND_EVT_STRU                 *pstEvent = VOS_NULL_PTR;

    /* 填充上报事件 */
    stPhoneEvent.PhoneEvent    = TAF_PH_EVT_NSM_STATUS_IND;
    stPhoneEvent.OP_PlmnMode   = VOS_TRUE;
    stPhoneEvent.ucPlmnMode    = 0;
    stPhoneEvent.ClientId      = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(TAF_PHONE_EVENT_INFO_STRU) + MN_AT_INTERFACE_MSG_HEADER_LEN));

    pstEvent->ulReceiverPid = WUEPS_PID_AT;
    pstEvent->ulSenderPid   = WUEPS_PID_TAF;
    pstEvent->usLen         = sizeof(TAF_PHONE_EVENT_INFO_STRU);
    pstEvent->usMsgName     = MN_CALLBACK_PHONE;
    pstEvent->clientId      = AT_BUTT_CLIENT_ID;
    PS_MEM_CPY(pstEvent->aucContent, &stPhoneEvent, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    MOCKER(At_SendResultData)
        .stubs()
        .with(eq((VOS_UINT8)AT_BUTT_CLIENT_ID), any(), any());
    At_MsgProc((MsgBlock *)pstEvent);

    GlobalMockObject::verify();
}



class Test_At_PIHRspProc: public ::testing::Test
{
public:
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_CISA;
        stCmdInfo.pfnSetProc        = VOS_NULL_PTR;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CISA";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-520),(cmd)";
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CISA_SET;
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_001)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT8                           aucCommand[] = {0x87, 0x65};
    VOS_CHAR                           *pcResult;

    //参数初始化
    pcResult            = "^CISA: 8,\"87654321\"";
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.ClientId    = AT_CLIENT_TAB_APP_INDEX;
    stEvent.OpId        = 0;
    stEvent.EventType   = SI_PIH_EVENT_ISDB_ACCESS_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;
    stEvent.PIHEvent.GAccessCnf.Len = 2;
    stEvent.PIHEvent.GAccessCnf.SW1 = 0x43;
    stEvent.PIHEvent.GAccessCnf.SW2 = 0x21;
    memcpy(stEvent.PIHEvent.GAccessCnf.Command, aucCommand, sizeof(aucCommand));

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_PIHRspProc(ucIndex, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(pcResult, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_002)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT8                           aucCommand[] = {0x87, 0x65};
    VOS_CHAR                           *pcResult;

    //参数初始化
    pcResult            = "^CISA: 8,\"87654321\"";
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.ClientId    = AT_CLIENT_TAB_APP_INDEX;
    stEvent.OpId        = 0;
    stEvent.EventType   = SI_PIH_EVENT_ISDB_ACCESS_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;
    stEvent.PIHEvent.GAccessCnf.Len = 2;
    stEvent.PIHEvent.GAccessCnf.SW1 = 0x43;
    stEvent.PIHEvent.GAccessCnf.SW2 = 0x21;
    memcpy(stEvent.PIHEvent.GAccessCnf.Command, aucCommand, sizeof(aucCommand));

    // 初始化全局变量
    gstAtSendData.usBufLen = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    At_PIHRspProc(ucIndex, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}

#if (FEATURE_VSIM == FEATURE_ON)

TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_003)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_HVSST_QUERY_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_HvsstQueryCnf)
        .stubs()
        .will(returnValue(10));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_PIHRspProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(10, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_004)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_HVSST_SET_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_PIHRspProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);


    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_005)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_HVSDH_SET_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_PIHRspProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_006)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_HVSDH_QRY_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_HvsDHQueryCnf)
        .stubs()
        .will(returnValue(10));
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_PIHRspProc(0, &stEvent);

    // 执行检查
    EXPECT_EQ(10, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_007)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_HVSCONT_QUERY_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_HvsContQueryCnf)
        .stubs()
        .will(returnValue(10));
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_PIHRspProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(10, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_008)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_FILE_WRITE_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_PIHRspProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IMS)

TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_009)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_UICCAUTH_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(AT_UiccAuthCnf)
        .expects(exactly(1))
        .will(returnValue(0));

    // 调用被测函数
    At_PIHRspProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHRspProc, Test_At_PIHRspProc_010)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_URSM_CNF;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(AT_UiccAccessFileCnf)
        .expects(exactly(1))
        .will(returnValue(0));

    // 调用被测函数
    At_PIHRspProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


#endif


class Test_At_PIHIndProc: public ::testing::Test
{
public:
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {
    }
};



TEST_F(Test_At_PIHIndProc, Test_At_PIHIndProc_001)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_HVRDH_IND;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_PIHIndProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHIndProc, Test_At_PIHIndProc_002)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_HVRDH_IND;
    stEvent.PIHError    = TAF_ERR_NO_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));
    /*MOCKER(At_sprintf)
        .expects(never());*/
    MOCKER(At_SendResultData)
        .expects(never());

    // 调用被测函数
    At_PIHIndProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    //EXPECT_EQ(0, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PIHIndProc, Test_At_PIHIndProc_003)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU              stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    stEvent.EventType   = SI_PIH_EVENT_HVSDH_QRY_CNF;
    stEvent.PIHError    = TAF_ERR_ERROR;

    // 初始化全局变量

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .expects(never());*/
    MOCKER(At_SendResultData)
        .expects(never());

    // 调用被测函数
    At_PIHIndProc(0, (SI_PIH_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    //EXPECT_EQ(10, gstAtSendData.usBufLen);

    GlobalMockObject::verify();
}
#endif


class Test_At_PrintMmTimeInfo: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }
    void TearDown()
    {
    }

};


TEST_F(Test_At_PrintMmTimeInfo, Test_At_PrintMmTimeInfo_001)
{
    //参数定义
    TAF_MMA_TIME_CHANGE_IND_STRU           stEvent;
    VOS_UINT32                          usLength;

    // 参数定义
    usLength = 0;

    // 参数初始化
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    // 相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    usLength = At_PrintMmTimeInfo(AT_CLIENT_BUTT, &stEvent, pgucAtSndCodeAddr);

    //执行检查
    EXPECT_EQ(0, usLength);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_PrintMmTimeInfo, Test_At_PrintMmTimeInfo_002)
{
    //参数定义
    TAF_MMA_TIME_CHANGE_IND_STRU        stEvent;
    VOS_CHAR                            acExpectedStr[] = "\r\n^TIME: \"12/09/14,06:51:55+32,01\"\r\n";
    VOS_UINT32                          usLength;
    VOS_UINT8                           ucIndex;

    // 参数定义
    usLength = 0;
    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // 参数初始化
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_MMA_TIME_CHANGE_IND_STRU));

    stEvent.ucIeFlg |= NAS_MM_INFO_IE_LTZ;
    stEvent.ucIeFlg |= NAS_MM_INFO_IE_UTLTZ;
    stEvent.ucIeFlg |= NAS_MM_INFO_IE_DST;
    stEvent.stUniversalTimeandLocalTimeZone.ucYear    = 12;
    stEvent.stUniversalTimeandLocalTimeZone.ucMonth   = 9;
    stEvent.stUniversalTimeandLocalTimeZone.ucDay     = 14;
    stEvent.stUniversalTimeandLocalTimeZone.ucHour    = 6;
    stEvent.stUniversalTimeandLocalTimeZone.ucMinute  = 51;
    stEvent.stUniversalTimeandLocalTimeZone.ucSecond  = 55;
    stEvent.stUniversalTimeandLocalTimeZone.cTimeZone = 32;
    stEvent.ucDST = 1;
    stEvent.cLocalTimeZone = 32;
    stEvent.aucCurcRptCfg[7] = 0x40;
    stEvent.aucUnsolicitedRptCfg[7] = 0x40;


    // 相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    usLength = At_PrintMmTimeInfo(ucIndex, (TAF_MMA_TIME_CHANGE_IND_STRU *)&stEvent, pgucAtSndCodeAddr);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_PrintMmTimeInfo, Test_At_PrintMmTimeInfo_003)
{
    //参数定义

    TAF_MMA_TIME_CHANGE_IND_STRU        stEvent;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CTZV: \"GMT+7, Summer Time\"\r\n";
    VOS_UINT32                          usLength;
    VOS_UINT8                           ucIndex;

    // 参数定义
    usLength = 0;
    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_1;

    // 参数初始化
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_MMA_TIME_CHANGE_IND_STRU));

    stEvent.ucIeFlg |= NAS_MM_INFO_IE_LTZ;
    stEvent.ucIeFlg |= NAS_MM_INFO_IE_UTLTZ;
    stEvent.ucIeFlg |= NAS_MM_INFO_IE_DST;
    stEvent.stUniversalTimeandLocalTimeZone.ucYear    = 12;
    stEvent.stUniversalTimeandLocalTimeZone.ucMonth   = 9;
    stEvent.stUniversalTimeandLocalTimeZone.ucDay     = 14;
    stEvent.stUniversalTimeandLocalTimeZone.ucHour    = 6;
    stEvent.stUniversalTimeandLocalTimeZone.ucMinute  = 51;
    stEvent.stUniversalTimeandLocalTimeZone.ucSecond  = 55;
    stEvent.stUniversalTimeandLocalTimeZone.cTimeZone = 32;
    stEvent.ucDST = 1;
    stEvent.cLocalTimeZone = 32;
    stEvent.aucCurcRptCfg[5] = 0x08;
    stEvent.aucUnsolicitedRptCfg[5] = 0x08;

    // 相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    usLength = At_PrintMmTimeInfo(ucIndex, (TAF_MMA_TIME_CHANGE_IND_STRU *)&stEvent, pgucAtSndCodeAddr);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_At_PrintMmTimeInfo, Test_At_PrintMmTimeInfo_004)
{
    //参数定义
    TAF_MMA_TIME_CHANGE_IND_STRU        stEvent;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CTZV: \"GMT+8, Winter Time\"\r\n";
    VOS_UINT32                          usLength;
    VOS_UINT8                           ucIndex;

    // 参数定义
    usLength = 0;
    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;


    // 参数初始化
    PS_MEM_SET(&stEvent, 0x00, sizeof(TAF_MMA_TIME_CHANGE_IND_STRU));

    stEvent.ucIeFlg |= NAS_MM_INFO_IE_LTZ;
    stEvent.stUniversalTimeandLocalTimeZone.ucYear    = 12;
    stEvent.stUniversalTimeandLocalTimeZone.ucMonth   = 9;
    stEvent.stUniversalTimeandLocalTimeZone.ucDay     = 14;
    stEvent.stUniversalTimeandLocalTimeZone.ucHour    = 6;
    stEvent.stUniversalTimeandLocalTimeZone.ucMinute  = 51;
    stEvent.stUniversalTimeandLocalTimeZone.ucSecond  = 55;
    stEvent.stUniversalTimeandLocalTimeZone.cTimeZone = 32;
    stEvent.ucDST = 1;
    stEvent.cLocalTimeZone = 32;
    stEvent.aucCurcRptCfg[5] = 0x08;
    stEvent.aucUnsolicitedRptCfg[5] = 0x08;

    // 相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    usLength = At_PrintMmTimeInfo(ucIndex, (TAF_MMA_TIME_CHANGE_IND_STRU *)&stEvent, pgucAtSndCodeAddr);

    //执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




class Test_AT_CsRspEvtReleasedProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_CsRspEvtReleasedProc, Test_AT_CsRspEvtReleasedProc_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CALL_INFO_STRU                   stCallInfo = {0};

    //参数初始化
    ucIndex         = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;

    // MOCKER操作
    MOCKER(AT_ReportCendResult)
        .expects(exactly(1))
        .with(eq(ucIndex), any());

    // 调用被测函数
    AT_CsRspEvtReleasedProc(ucIndex, MN_CALL_EVT_RELEASED, (MN_CALL_INFO_STRU *)&stCallInfo);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CsRspEvtReleasedProc, Test_AT_CsRspEvtReleasedProc_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CALL_INFO_STRU                   stCallInfo = {0};

    //参数初始化
    ucIndex                 = AT_CLIENT_TAB_PCUI_INDEX;
    stCallInfo.enCallType   = MN_CALL_TYPE_EMERGENCY;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(AT_ReportCendResult)
        .expects(exactly(1))
        .with(eq(ucIndex), any());

    // 调用被测函数
    AT_CsRspEvtReleasedProc(ucIndex, MN_CALL_EVT_RELEASED, (MN_CALL_INFO_STRU *)&stCallInfo);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CsRspEvtReleasedProc, Test_AT_CsRspEvtReleasedProc_003)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;

     pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucClientIndex);
     pstCcCtx->stS0TimeInfo.bTimerStart = VOS_TRUE;

     gastAtClientTab[ucClientIndex].CmdCurrentOpt = AT_CMD_CHUP_SET;

     enEventType = MN_CALL_EVT_RELEASED;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = ucClientIndex;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->ulPreCallTime = 1;
     pstEvent->enNoCliCause = 1;
     pstEvent->enCause = 1;
     pstEvent->aucCurcRptCfg[4] = 0x08;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n^CEND:1,1,1,1\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 执行检查 */
     EXPECT_EQ((VOS_BOOL)VOS_FALSE, pstCcCtx->stS0TimeInfo.bTimerStart);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_AT_CsRspEvtReleasedProc, Test_AT_CsRspEvtReleasedProc_004)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;

     pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucClientIndex);

     pstCcCtx->stS0TimeInfo.bTimerStart = VOS_TRUE;

     gastAtClientTab[ucClientIndex].CmdCurrentOpt = AT_CMD_CGEQREQ_SET;

     enEventType = MN_CALL_EVT_RELEASED;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = ucClientIndex;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->ulPreCallTime = 1;
     pstEvent->enNoCliCause = 1;
     pstEvent->enCause = 1;
     pstEvent->aucCurcRptCfg[4] = 0x08;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n^CEND:1,1,1,1\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 执行检查 */
     EXPECT_EQ((VOS_BOOL)VOS_FALSE, pstCcCtx->stS0TimeInfo.bTimerStart);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}



class Test_AT_CSCallStateReportProc: public ::testing::Test
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


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_001)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_INFO_STRU                  *pstCallInfo;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    VOS_UINT32                          ulEventLen;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    enEvent     = MN_CALL_EVT_ORIG;
    ulEventLen  = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU) + ulEventLen - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    PS_MEM_CPY(pstData->aucContent, &enEvent, ulEventLen);
    pstCallInfo = (MN_CALL_INFO_STRU *)&pstData->aucContent[ulEventLen];
    pstCallInfo->callId = 1;
    pstCallInfo->enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;
    PS_MEM_SET(pstCallInfo->aucCurcRptCfg, 0xFF, sizeof(pstCallInfo->aucCurcRptCfg));
    pcExpect    = "\r\n^CCALLSTATE: 1,0,0\r\n";

    // 初始化全局变量
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstCallInfo->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_002)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_INFO_STRU                  *pstCallInfo;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    VOS_UINT32                          ulEventLen;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    enEvent     = MN_CALL_EVT_CALL_PROC;
    ulEventLen  = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU) + ulEventLen - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    PS_MEM_CPY(pstData->aucContent, &enEvent, ulEventLen);
    pstCallInfo = (MN_CALL_INFO_STRU *)&pstData->aucContent[ulEventLen];
    pstCallInfo->callId = 1;
    pcExpect    = "\r\n^CCALLSTATE: 1,1,0\r\n";
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstCallInfo->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    // 初始化全局变量
    PS_MEM_SET(pstCallInfo->aucCurcRptCfg, 0xFF, sizeof(pstCallInfo->aucCurcRptCfg));

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_003)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_INFO_STRU                  *pstCallInfo;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    VOS_UINT32                          ulEventLen;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    enEvent     = MN_CALL_EVT_ALERTING;
    ulEventLen  = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU) + ulEventLen - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    PS_MEM_CPY(pstData->aucContent, &enEvent, ulEventLen);
    pstCallInfo = (MN_CALL_INFO_STRU *)&pstData->aucContent[ulEventLen];
    pstCallInfo->callId = 1;
    pcExpect    = "\r\n^CCALLSTATE: 1,2,0\r\n";
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstCallInfo->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    // 初始化全局变量
    PS_MEM_SET(pstCallInfo->aucCurcRptCfg, 0xFF, sizeof(pstCallInfo->aucCurcRptCfg));

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_004)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_INFO_STRU                  *pstCallInfo;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    VOS_UINT32                          ulEventLen;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    enEvent     = MN_CALL_EVT_CONNECT;
    ulEventLen  = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU) + ulEventLen - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    PS_MEM_CPY(pstData->aucContent, &enEvent, ulEventLen);
    pstCallInfo = (MN_CALL_INFO_STRU *)&pstData->aucContent[ulEventLen];
    pstCallInfo->callId = 1;
    pcExpect    = "\r\n^CCALLSTATE: 1,3,0\r\n";
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstCallInfo->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;

    // 初始化全局变量
    PS_MEM_SET(pstCallInfo->aucCurcRptCfg, 0xFF, sizeof(pstCallInfo->aucCurcRptCfg));

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_005)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_INFO_STRU                  *pstCallInfo;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    VOS_UINT32                          ulEventLen;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    enEvent     = MN_CALL_EVT_RELEASED;
    ulEventLen  = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU) + ulEventLen - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    PS_MEM_CPY(pstData->aucContent, &enEvent, ulEventLen);
    pstCallInfo = (MN_CALL_INFO_STRU *)&pstData->aucContent[ulEventLen];
    pstCallInfo->callId = 1;
    pcExpect    = "\r\n^CCALLSTATE: 1,4,0\r\n";
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstCallInfo->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    // 初始化全局变量
    PS_MEM_SET(pstCallInfo->aucCurcRptCfg, 0xFF, sizeof(pstCallInfo->aucCurcRptCfg));

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_006)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_INFO_STRU                  *pstCallInfo;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    VOS_UINT32                          ulEventLen;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    enEvent     = MN_CALL_EVT_INCOMING;
    ulEventLen  = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU) + ulEventLen - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    PS_MEM_CPY(pstData->aucContent, &enEvent, ulEventLen);
    pstCallInfo = (MN_CALL_INFO_STRU *)&pstData->aucContent[ulEventLen];
    pstCallInfo->callId = 1;
    pstCallInfo->enCallState = MN_CALL_S_INCOMING;
    pcExpect    = "\r\n^CCALLSTATE: 1,5,0\r\n";
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstCallInfo->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    // 初始化全局变量
    PS_MEM_SET(pstCallInfo->aucCurcRptCfg, 0xFF, sizeof(pstCallInfo->aucCurcRptCfg));

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_007)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_INFO_STRU                  *pstCallInfo;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    VOS_UINT32                          ulEventLen;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    enEvent     = MN_CALL_EVT_INCOMING;
    ulEventLen  = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_STRU) + ulEventLen - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    PS_MEM_CPY(pstData->aucContent, &enEvent, ulEventLen);
    pstCallInfo = (MN_CALL_INFO_STRU *)&pstData->aucContent[ulEventLen];
    pstCallInfo->callId = 1;
    pstCallInfo->enCallState = MN_CALL_S_WAITING;
    pcExpect    = "\r\n^CCALLSTATE: 1,6,0\r\n";
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstCallInfo->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    // 初始化全局变量
    PS_MEM_SET(pstCallInfo->aucCurcRptCfg, 0xFF, sizeof(pstCallInfo->aucCurcRptCfg));

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_008)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_EVT_HOLD_STRU              *pstHoldEvt;
    VOS_CHAR                           *pcExpect1;
    VOS_CHAR                           *pcExpect2;

    //参数初始化
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_EVT_HOLD_STRU) - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    pstHoldEvt  = (MN_CALL_EVT_HOLD_STRU *)pstData->aucContent;
    pstHoldEvt->enEvent         = MN_CALL_EVT_HOLD;
    pstHoldEvt->ucCallNum       = 2;
    pstHoldEvt->aucCallId[0]    = 1;
    pstHoldEvt->aucCallId[1]    = 2;
    pcExpect1   = "\r\n^CCALLSTATE: 1,7,0\r\n";
    pcExpect2   = "\r\n^CCALLSTATE: 2,7,0\r\n";
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstHoldEvt->usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;

    // 初始化全局变量
    PS_MEM_SET(pstHoldEvt->aucCurcRptCfg, 0xFF, sizeof(pstHoldEvt->aucCurcRptCfg));

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect1, VOS_StrLen(pcExpect1)), any());

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect2, VOS_StrLen(pcExpect2)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_009)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_EVT_RETRIEVE_STRU          *pstRetrieveEvt;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    ulLength    = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_EVT_RETRIEVE_STRU) - 4;
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    pstRetrieveEvt                  = (MN_CALL_EVT_RETRIEVE_STRU *)pstData->aucContent;
    pstRetrieveEvt->enEvent         = MN_CALL_EVT_RETRIEVE;
    pstRetrieveEvt->ucCallNum       = 1;
    pstRetrieveEvt->aucCallId[0]    = 1;
    pcExpect    = "\r\n^CCALLSTATE: 1,8,0\r\n";
    pstData->clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstRetrieveEvt->usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    // 初始化全局变量
    PS_MEM_SET(pstRetrieveEvt->aucCurcRptCfg, 0xFF, sizeof(pstRetrieveEvt->aucCurcRptCfg));

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    AT_CSCallStateReportProc((MN_AT_IND_EVT_STRU *)pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CSCallStateReportProc, Test_AT_CSCallStateReportProc_010)
{
    // 变量声明
    MN_AT_IND_EVT_STRU                 *pstData;
    VOS_UINT32                          ulLength;
    MN_CALL_EVENT_ENUM_U32              enEvent;
    VOS_UINT32                          ulEventLen;

    //参数初始化
    enEvent     = MN_CALL_EVT_BUTT;
    ulEventLen  = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulLength    = sizeof(MN_AT_IND_EVT_STRU);
    pstData     = (MN_AT_IND_EVT_STRU *)malloc(ulLength);
    PS_MEM_SET(pstData, 0, ulLength);
    PS_MEM_CPY(pstData->aucContent, &enEvent, ulEventLen);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(never());

    // 调用被测函数
    AT_CSCallStateReportProc(pstData);

    // 执行检查

    // 释放内存
    free(pstData);

    GlobalMockObject::verify();
}


class Test_At_SmsStorageExceedProc: public ::testing::Test
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


TEST_F(Test_At_SmsStorageExceedProc, Test_At_SmsStorageExceedProc_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              stEvent = {0};
    VOS_UINT8                           aucData[] = {0x00, 0x00, 0x00, 0x00,
                                                     0x00, 0x00, 0x08, 0x00};
    VOS_CHAR                           *pcExpect;

    //参数初始化
    ucIndex     = 0;
    stEvent.u.stStorageStateInfo.enMemStroe = MN_MSG_MEM_STORE_SIM;
    pcExpect    = "\r\n^SMMEMFULL: \"SM\"\r\n";

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    At_SmsStorageExceedProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}


class Test_AT_RcvMmInfoInd: public ::testing::Test
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




class Test_At_STKCMDTypePrint: public ::testing::Test
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


TEST_F(Test_At_STKCMDTypePrint, Test_At_STKCMDTypePrint_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSatType;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucSystemAppConfig;

    //参数初始化
    ucIndex     = 0;
    ulSatType   = SI_STK_NOCMDDATA;
    ulEventType = SI_STK_CMD_QUERY_RSP_EVENT;
    ucSystemAppConfig           = SYSTEM_APP_WEBUI;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSystemAppConfig));

    MOCKER(At_ChangeSTKCmdNo)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ulSatType), any())
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRet = At_STKCMDTypePrint(ucIndex, ulSatType, ulEventType);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_STKCMDTypePrint, Test_At_STKCMDTypePrint_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSatType;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucSystemAppConfig;

    //参数初始化
    ucIndex     = 0;
    ulSatType   = SI_STK_NOCMDDATA;
    ulEventType = SI_STK_CMD_QUERY_RSP_EVENT;
    ucSystemAppConfig           = SYSTEM_APP_WEBUI;

    // 初始化全局变量
    g_ulSTKFunctionFlag = TAF_FALSE;

    // MOCKER操作
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSystemAppConfig));

    MOCKER(At_ChangeSTKCmdNo)
        .expects(exactly(1))
        .with(eq(ulSatType), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = At_STKCMDTypePrint(ucIndex, ulSatType, ulEventType);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_STKCMDTypePrint, Test_At_STKCMDTypePrint_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSystemAppConfig;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSatType;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucCmdType;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    ucSystemAppConfig   = SYSTEM_APP_MP;
    ucIndex             = 0;
    ulSatType           = SI_STK_NOCMDDATA;
    ulEventType         = SI_STK_CMD_QUERY_RSP_EVENT;
    ucCmdType           = 1;
    pcExpect            = "\r\n^STGI: 1, 0\r\n";

    // 初始化全局变量
    g_ulSTKFunctionFlag = TAF_TRUE;
    gucAtVType          = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue(&ucSystemAppConfig));

    MOCKER(At_ChangeSTKCmdNo)
        .stubs()
        .with(eq(ulSatType), outBoundP((VOS_UINT8 *)&ucCmdType,(VOS_UINT32)sizeof(ucCmdType)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    ulRet = At_STKCMDTypePrint(ucIndex, ulSatType, ulEventType);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_STKCMDTypePrint, Test_At_STKCMDTypePrint_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSystemAppConfig;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSatType;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucCmdType;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           aucData[] = {0x00, 0x00, 0x00, 0x00,
                                                     0x20, 0x00, 0x00, 0x00};

    //参数初始化
    ucSystemAppConfig   = SYSTEM_APP_MP;
    ucIndex             = 0;
    ulSatType           = SI_STK_NOCMDDATA;
    ulEventType         = SI_STK_CMD_IND_EVENT;
    ucCmdType           = 1;
    pcExpect            = "\r\n^STIN: 1, 0, 0\r\n";

    // 初始化全局变量
    g_ulSTKFunctionFlag = TAF_TRUE;
    gucAtVType          = AT_V_ENTIRE_TYPE;


    // MOCKER操作
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue(&ucSystemAppConfig));

    MOCKER(At_ChangeSTKCmdNo)
        .stubs()
        .with(eq(ulSatType), outBoundP((VOS_UINT8 *)&ucCmdType, (VOS_UINT32)sizeof(ucCmdType)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    ulRet = At_STKCMDTypePrint(ucIndex, ulSatType, ulEventType);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_STKCMDTypePrint, Test_At_STKCMDTypePrint_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSystemAppConfig;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSatType;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucCmdType;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           aucData[] = {0x00, 0x00, 0x00, 0x00,
                                                     0x20, 0x00, 0x00, 0x00};

    //参数初始化
    ucSystemAppConfig   = SYSTEM_APP_MP;
    ucIndex             = 0;
    ulSatType           = SI_STK_NOCMDDATA;
    ulEventType         = SI_STK_CMD_END_EVENT;
    ucCmdType           = 1;
    pcExpect            = "\r\n^STIN: 99, 0, 0\r\n";

    // 初始化全局变量
    g_ulSTKFunctionFlag = TAF_TRUE;
    gucAtVType          = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue(&ucSystemAppConfig));

    MOCKER(At_ChangeSTKCmdNo)
        .stubs()
        .with(eq(ulSatType), outBoundP((VOS_UINT8 *)&ucCmdType, (VOS_UINT32)sizeof(ucCmdType)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    ulRet = At_STKCMDTypePrint(ucIndex, ulSatType, ulEventType);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_STKCMDTypePrint, Test_At_STKCMDTypePrint_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSystemAppConfig;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSatType;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucCmdType;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           aucData[] = {0x00, 0x00, 0x00, 0x00,
                                                     0x20, 0x00, 0x00, 0x00};

    //参数初始化
    ucSystemAppConfig   = SYSTEM_APP_ANDROID;
    ucIndex             = 0;
    ulSatType           = SI_STK_NOCMDDATA;
    ulEventType         = SI_STK_CMD_END_EVENT;
    ucCmdType           = 1;
    pcExpect            = "\r\n^CSIN: 0, 0\r\n";

    // 初始化全局变量
    g_ulSTKFunctionFlag = TAF_TRUE;
    gucAtVType          = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue((VOS_UINT8 *)&ucSystemAppConfig));

    MOCKER(At_ChangeSTKCmdNo)
        .expects(never());

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    ulRet = At_STKCMDTypePrint(ucIndex, ulSatType, ulEventType);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_STKCMDTypePrint, Test_At_STKCMDTypePrint_007)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSystemAppConfig;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSatType;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucCmdType;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           aucData[] = {0x00, 0x00, 0x00, 0x00,
                                                     0x20, 0x00, 0x00, 0x00};

    //参数初始化
    ucSystemAppConfig   = SYSTEM_APP_MP;
    ucIndex             = 0;
    ulSatType           = SI_STK_NOCMDDATA;
    ulEventType         = SI_STK_CALLBACK_BUTT;
    ucCmdType           = 1;
    pcExpect            = "\r\n^STIN: 1, 0, 1\r\n";

    // 初始化全局变量
    g_ulSTKFunctionFlag = TAF_TRUE;
    gucAtVType          = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(AT_GetSystemAppConfigAddr)
        .stubs()
        .will(returnValue(&ucSystemAppConfig));

    MOCKER(At_ChangeSTKCmdNo)
        .stubs()
        .with(eq(ulSatType), outBoundP(&ucCmdType))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    ulRet = At_STKCMDTypePrint(ucIndex, ulSatType, ulEventType);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


class Test_At_PhIndProc: public ::testing::Test
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



TEST_F(Test_At_PhIndProc, Test_At_PhIndProc_004)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU           stEvent = {0};
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    ucIndex = AT_CLIENT_BUTT;
    enModemId = MODEM_ID_0;
    stEvent.PhoneEvent      = TAF_PH_EVT_USIM_INFO_IND;
    stEvent.SimStatus       = TAF_PH_USIM_STATUS_AVAIL;
    stEvent.MeLockStatus    = TAF_PH_ME_SIM_UNLOCK;

    MOCKER(AT_CheckRptCmdStatus)
        .expects(never());

    // 调用被测函数
    At_PhIndProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhIndProc, Test_At_PhIndProc_005)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU           stEvent = {0};
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           aucData[] = {0x00, 0x00, 0x00, 0x00,
                                                     0x00, 0x00, 0x00, 0x20};
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    ucIndex                 = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    enModemId               = MODEM_ID_0;
    stEvent.PhoneEvent      = TAF_PH_EVT_USIM_INFO_IND;
    stEvent.SimStatus       = TAF_PH_USIM_STATUS_AVAIL;
    stEvent.MeLockStatus    = TAF_PH_ME_SIM_UNLOCK;
    pcExpect                = "\r\n^SIMST:1,0\r\n";

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    At_PhIndProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhIndProc, Test_At_PhIndProc_006)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU           stEvent = {0};
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    ucIndex = AT_CLIENT_BUTT;
    enModemId = MODEM_ID_0;
    stEvent.PhoneEvent      = TAF_PH_EVT_SERVICE_STATUS_IND;
    stEvent.OP_Srvst        = 1;
    stEvent.ServiceStatus   = TAF_REPORT_SRVSTA_NORMAL_SERVICE;

    MOCKER(AT_CheckRptCmdStatus)
        .expects(never());

    // 调用被测函数
    At_PhIndProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_PhIndProc, Test_At_PhIndProc_007)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU           stEvent = {0};
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           aucData[] = {0x00, 0x00, 0x00, 0x00,
                                                     0x00, 0x00, 0x00, 0x08};
    MODEM_ID_ENUM_UINT16                enModemId;

    //参数初始化
    ucIndex                 = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    enModemId               = MODEM_ID_0;
    stEvent.PhoneEvent      = TAF_PH_EVT_SERVICE_STATUS_IND;
    stEvent.OP_Srvst        = 1;
    stEvent.ServiceStatus   = TAF_REPORT_SRVSTA_NORMAL_SERVICE;
    pcExpect                = "\r\n^SRVST: 2\r\n";

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    // 调用被测函数
    At_PhIndProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}



class Test_At_StkCcinIndPrint: public ::testing::Test
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


TEST_F(Test_At_StkCcinIndPrint, Test_At_StkCcinIndPrint_001)
{
    //参数定义
    TAF_UINT8 ucIndex = 0;
    SI_STK_EVENT_INFO_STRU stEvent;

    // 参数初始化
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucType = SI_STK_MO_CALL_CTRL;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucResult = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.ulAlphaLen = 2;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.aucAlphaId[0] = 0x61;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.aucAlphaId[1] = 0x62;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.usDataLen = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData[0] = 0x21;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData[1] = 0xC1;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData[2] = 0xdb;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData[3] = 0xfa;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.ucDataType = 129;

    // 相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    At_StkCcinIndPrint(ucIndex, (SI_STK_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_StkCcinIndPrint, Test_At_StkCcinIndPrint_002)
{
    //参数定义
    TAF_UINT8 ucIndex = 0;
    SI_STK_EVENT_INFO_STRU stEvent;

    // 参数初始化
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucType = SI_STK_SS_CALL_CTRL;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucResult = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.ulAlphaLen = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.ucAddrLen = 0;


    // 相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    At_StkCcinIndPrint(ucIndex, (SI_STK_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_StkCcinIndPrint, Test_At_StkCcinIndPrint_003)
{
    //参数定义
    TAF_UINT8 ucIndex = 0;
    SI_STK_EVENT_INFO_STRU stEvent;

    // 参数初始化
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucType = SI_STK_USSD_CALL_CTRL;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucResult = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.ulAlphaLen = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.usDataLen = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData[0] = 0x21;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData[1] = 0xFF;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData[2] = 0xdb;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData[3] = 0xfa;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.ucDataType = 129;

    // 相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    At_StkCcinIndPrint(ucIndex, (SI_STK_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_StkCcinIndPrint, Test_At_StkCcinIndPrint_004)
{
    //参数定义
    TAF_UINT8 ucIndex = 0;
    SI_STK_EVENT_INFO_STRU stEvent;

    // 参数初始化
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucType = SI_STK_SMS_CTRL;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucResult = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.ulAlphaLen = 0;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.ucAddrLen = 4;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.aucAddr[0] = 0x21;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.aucAddr[1] = 0xce;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.aucAddr[2] = 0xdb;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.aucAddr[3] = 0xfa;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.ucNumType = 129;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.ucAddrLen = 4;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.aucAddr[0] = 0x21;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.aucAddr[1] = 0xc1;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.aucAddr[2] = 0xff;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.aucAddr[3] = 0xfa;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.ucNumType = 129;

    // 相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    At_StkCcinIndPrint(ucIndex, (SI_STK_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_RcvMnCallErrInd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
        AT_SetCsCallErrCause(0,TAF_CS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_SetCsCallErrCause(0,TAF_CS_CAUSE_SUCCESS);
    }

};


TEST_F(Test_AT_RcvMnCallErrInd, Test_AT_RcvMnCallErrInd_001)
{
    //参数定义
    MN_AT_IND_EVT_STRU                 *pstCsEvt;
    MN_CALL_EVT_ERR_IND_STRU           *pstErrInd;
    VOS_UINT32                          ulEvtLen;

    //参数初始化
    ulEvtLen = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_EVT_ERR_IND_STRU) - 4;
    pstCsEvt = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulEvtLen);

    PS_MEM_SET(pstCsEvt, 0x00, ulEvtLen);

    AT_SetCsCallErrCause(0, TAF_CS_CAUSE_SUCCESS);

    pstCsEvt->usLen      = sizeof(MN_CALL_EVT_ERR_IND_STRU);

    pstErrInd            = (MN_CALL_EVT_ERR_IND_STRU *)pstCsEvt->aucContent;
    pstErrInd->enEventId = MN_CALL_EVT_ERR_IND;
    pstErrInd->enCause   = TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    At_CsMsgProc(pstCsEvt, pstCsEvt->usLen);

    //释放内存
    PS_MEM_FREE(WUEPS_PID_AT, pstCsEvt);

    //执行检查
    ASSERT_EQ((TAF_CS_CAUSE_ENUM_UINT32)TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED, AT_GetCsCallErrCause(0));

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_ConvertCallError: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
        AT_SetCsCallErrCause(0,TAF_CS_CAUSE_SUCCESS);
    }
    void TearDown()
    {
        AT_SetCsCallErrCause(0,TAF_CS_CAUSE_SUCCESS);
    }

};


TEST_F(Test_AT_ConvertCallError, Test_AT_ConvertCallError_001)
{
    //参数定义
    VOS_UINT32                          ulCallError;
    VOS_UINT32                          ulRsltCode;

    //参数初始化
    ulCallError = TAF_CS_CAUSE_STATE_ERROR;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRsltCode = AT_ConvertCallError(ulCallError);

    //执行检查
    ASSERT_EQ((VOS_UINT32)AT_CME_INCORRECT_PARAMETERS, ulRsltCode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ConvertCallError, Test_AT_ConvertCallError_002)
{
    //参数定义
    VOS_UINT32                          ulCallError;
    VOS_UINT32                          ulRsltCode;

    //参数初始化
    ulCallError = TAF_CS_CAUSE_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRsltCode = AT_ConvertCallError(ulCallError);

    //执行检查
    ASSERT_EQ((VOS_UINT32)AT_CME_UNKNOWN, ulRsltCode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_SetClprCnf: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 1;
        usLen   = 0;

        ulEventLen  = sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_CLPR_GET_CNF_STRU) - 4;
        pstData     = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, ulEventLen);
        stClprGetCnf.enEvent                        = MN_CALL_EVT_CLPR_SET_CNF;
        stClprGetCnf.ulRet                          = TAF_ERR_NO_ERROR;
        stClprGetCnf.stAppCtrl.usClientId           = ucIndex;
        stClprGetCnf.stAppCtrl.ucOpId               = AT_CMD_CLPR_SET;
        stClprGetCnf.stRedirectInfo.bitOpPI         = VOS_TRUE;
        stClprGetCnf.stRedirectInfo.enPI            = MN_CALL_PRESENTATION_RESTRICTED;

        stClprGetCnf.stRedirectInfo.bitOpNoCLICause = VOS_TRUE;
        stClprGetCnf.stRedirectInfo.enNoCLICause    = MN_CALL_NO_CLI_USR_REJ;

        stClprGetCnf.stRedirectInfo.bitOpRedirectNum        = VOS_TRUE;
        stClprGetCnf.stRedirectInfo.stRedirectNum.ucNumLen  = 20;
        stClprGetCnf.stRedirectInfo.stRedirectNum.enNumType = MN_CALL_TON_UNKNOWN;
        memcpy(stClprGetCnf.stRedirectInfo.stRedirectNum.aucBcdNum,
               "1654853164813",
               14);


        stClprGetCnf.stRedirectInfo.bitOpRedirectSubaddr            = VOS_TRUE;
        stClprGetCnf.stRedirectInfo.stRedirectSubaddr.IsExist       = VOS_TRUE;
        stClprGetCnf.stRedirectInfo.stRedirectSubaddr.LastOctOffset = 12;
        memcpy(stClprGetCnf.stRedirectInfo.stRedirectSubaddr.SubAddrInfo,
               "15444365448",
               12);
        stClprGetCnf.stRedirectInfo.stRedirectSubaddr.Octet3  = (MN_CALL_IS_EXIT | (MN_CALL_SUBADDR_NSAP << 4));

        for ( ulLoop = 0; ulLoop < AT_MAX_CLIENT_NUM; ulLoop++ )
        {
            gastAtClientTab[ulLoop].CmdCurrentOpt  = AT_CMD_INVALID;
            gastAtClientTab[ulLoop].usClientId     = AT_CLIENT_BUTT;
            gastAtClientTab[ulLoop].ucUsed         = AT_CLIENT_USED;
        }

        stCmdInfo.pszCmdName                    = (VOS_UINT8 *)"^CLPR";
        stCmdInfo.ulCmdIndex                    = AT_CMD_CLPR;
        stCmdInfo.pfnSetProc                    = AT_SetClprPara;
        stCmdInfo.ulSetTimeOut                  = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc                    = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut                 = AT_NOT_SET_TIME;
        stCmdInfo.ulTestTimeOut                 = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode                = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag                     = CMD_TBL_PIN_IS_LOCKED;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CLPR_SET;
        gastAtClientTab[ucIndex].usClientId     = ucIndex;
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
        if (VOS_NULL_PTR != pstData)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstData);
            pstData   = VOS_NULL_PTR;
        }
    }

    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulEventLen;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    MN_AT_IND_EVT_STRU                 *pstData;
    MN_CALL_CLPR_GET_CNF_STRU           stClprGetCnf;
};

TEST_F(Test_At_SetClprCnf, Test_At_SetClprCnf_001)
{
    // 变量声明

    // 参数初始化
    stClprGetCnf.ulRet = TAF_ERR_NO_ERROR + 1;

    /* 构造消息结构 */
    PS_MEM_CPY(pstData->aucContent, &stClprGetCnf, sizeof(MN_CALL_CLPR_GET_CNF_STRU));


    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    At_CsMsgProc(pstData, usLen);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetClprCnf, Test_At_SetClprCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           i;

    // 参数初始化
    /* 构造消息结构 */
    PS_MEM_CPY(pstData->aucContent, &stClprGetCnf, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    // 初始化全局变量;
    for ( i = 0; i < AT_MAX_CLIENT_NUM; i++ )
    {
        gastAtClientTab[i].usClientId   = AT_CLIENT_BUTT;
        gastAtClientTab[i].ucUsed       = AT_CLIENT_NULL;
    }

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(never())
        .with(any(), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    At_CsMsgProc(pstData, usLen);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_At_SetClprCnf, Test_At_SetClprCnf_003)
{
    // 变量声明


    // 参数初始化
    stClprGetCnf.stAppCtrl.usClientId           = MN_CLIENT_ALL;

    /* 构造消息结构 */
    PS_MEM_CPY(pstData->aucContent, &stClprGetCnf, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(never())
        .with(any(), eq((VOS_UINT32)AT_ERROR));

    MOCKER(AT_StopRelTimer)
        .expects(never());

    // 调用被测函数
    At_CsMsgProc(pstData, usLen);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetClprCnf, Test_At_SetClprCnf_004)
{
    // 变量声明

    // 参数初始化
    /* 构造消息结构 */
    PS_MEM_CPY(pstData->aucContent, &stClprGetCnf, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    // 初始化全局变量;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(never())
        .with(any(), eq((VOS_UINT32)AT_ERROR));

    MOCKER(AT_StopRelTimer)
        .expects(never());

    // 调用被测函数
    At_CsMsgProc(pstData, usLen);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetClprCnf, Test_At_SetClprCnf_005)
{
    // 变量声明

    // 参数初始化

    /* 构造消息结构 */
    PS_MEM_CPY(pstData->aucContent, &stClprGetCnf, sizeof(MN_CALL_CLPR_GET_CNF_STRU));


    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_CsMsgProc(pstData, usLen);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetClprCnf, Test_At_SetClprCnf_006)
{
    // 变量声明

    // 参数初始化
    stClprGetCnf.stRedirectInfo.bitOpPI              = VOS_FALSE;
    stClprGetCnf.stRedirectInfo.bitOpNoCLICause      = VOS_FALSE;
    stClprGetCnf.stRedirectInfo.bitOpRedirectNum     = VOS_FALSE;
    stClprGetCnf.stRedirectInfo.bitOpRedirectSubaddr = VOS_FALSE;

    /* 构造消息结构 */
    PS_MEM_CPY(pstData->aucContent, &stClprGetCnf, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_CsMsgProc(pstData, usLen);

    // 执行检查
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_LTE)

class Test_AT_ReportCeregResult: public ::testing::Test
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


TEST_F(Test_AT_ReportCeregResult, Test_AT_ReportCeregResult_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent;
    VOS_UINT16                         *pusLength;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    ucIndex = AT_CLIENT_BUTT;
    pstEvent = (TAF_PHONE_EVENT_INFO_STRU*)malloc(sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pusLength = (VOS_UINT16*)malloc(sizeof(VOS_UINT16));

    MOCKER(AT_IsModemSupportRat).expects(never());

    AT_ReportCeregResult(ucIndex, pstEvent, pusLength);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReportCeregResult, Test_AT_ReportCeregResult_002)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent;
    VOS_UINT16                         *pusLength;

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    pstEvent = (TAF_PHONE_EVENT_INFO_STRU*)malloc(sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pusLength = (VOS_UINT16*)malloc(sizeof(VOS_UINT16));

    MOCKER(AT_IsModemSupportRat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT8)VOS_FALSE));

    AT_ReportCeregResult(ucIndex, pstEvent, pusLength);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReportCeregResult, Test_AT_ReportCeregResult_003)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent;
    VOS_UINT16                         *pusLength;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    g_astAtModemCtx[enModemId].stPlatformRatList.ucPlatformSptLte = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    pstEvent = (TAF_PHONE_EVENT_INFO_STRU*)malloc(sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pusLength = (VOS_UINT16*)malloc(sizeof(VOS_UINT16));
    pstEvent->CurRegSta.OP_PsRegState = VOS_TRUE;
    pstEvent->CurRegSta.ucPsRegState = TAF_PH_REG_REGISTERED_ROAM;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);
    pstNetCtx->ucCeregType = AT_CEREG_RESULT_CODE_BREVITE_TYPE;

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/
        //.with(any(), any(), any(), any(), any(), any(), eq(TAF_PH_REG_REGISTERED_ROAM), any());

    AT_ReportCeregResult(ucIndex, pstEvent, pusLength);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReportCeregResult, Test_AT_ReportCeregResult_004)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent;
    VOS_UINT16                         *pusLength;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    g_astAtModemCtx[enModemId].stPlatformRatList.ucPlatformSptLte = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    pstEvent = (TAF_PHONE_EVENT_INFO_STRU*)malloc(sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pusLength = (VOS_UINT16*)malloc(sizeof(VOS_UINT16));
    pstEvent->CurRegSta.OP_CellId = VOS_TRUE;
    pstEvent->CurRegSta.OP_PsRegState = VOS_TRUE;
    pstEvent->RatType = TAF_PH_INFO_LTE_RAT;
    pstEvent->CurRegSta.ucPsRegState = TAF_PH_REG_REGISTERED_HOME_NETWORK;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);
    pstNetCtx->ucCeregType = AT_CEREG_RESULT_CODE_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(AT_IsModemSupportRat)
        .stubs()
        .will(returnValue((VOS_UINT8)VOS_TRUE));

    MOCKER(At_PhReadCreg)
        .expects(exactly(1))
        .will(returnValue(0));

    AT_ReportCeregResult(ucIndex, pstEvent, (VOS_UINT16 *)pusLength);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReportCeregResult, Test_AT_ReportCeregResult_005)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent;
    VOS_UINT16                         *pusLength;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    g_astAtModemCtx[enModemId].stPlatformRatList.ucPlatformSptLte = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    pstEvent = (TAF_PHONE_EVENT_INFO_STRU*)malloc(sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pusLength = (VOS_UINT16*)malloc(sizeof(VOS_UINT16));
    pstEvent->CurRegSta.OP_PsRegState = VOS_TRUE;
    pstEvent->CurRegSta.OP_CellId = VOS_FALSE;
    pstEvent->CurRegSta.ucPsRegState = TAF_PH_REG_REGISTERED_HOME_NETWORK;
    pstEvent->RatType = TAF_PH_INFO_LTE_RAT;


    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);
    pstNetCtx->ucCeregType = AT_CEREG_RESULT_CODE_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_PhReadCreg)
        .expects(exactly(1))
        .will(returnValue(0));

    AT_ReportCeregResult(ucIndex, pstEvent, (VOS_UINT16 *)pusLength);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReportCeregResult, Test_AT_ReportCeregResult_006)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent;
    VOS_UINT16                         *pusLength;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    g_astAtModemCtx[enModemId].stPlatformRatList.ucPlatformSptLte = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    pstEvent = (TAF_PHONE_EVENT_INFO_STRU*)malloc(sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pusLength = (VOS_UINT16*)malloc(sizeof(VOS_UINT16));
    pstEvent->CurRegSta.OP_PsRegState = VOS_TRUE;
    pstEvent->CurRegSta.OP_CellId = VOS_FALSE;
    pstEvent->CurRegSta.ucPsRegState = TAF_PH_REG_NOT_REGISTERED_SEARCHING;
    pstEvent->RatType = TAF_PH_INFO_LTE_RAT;


    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);
    pstNetCtx->ucCeregType = AT_CEREG_RESULT_CODE_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_PhReadCreg)
        .expects(never())
        .will(returnValue(0));

    AT_ReportCeregResult(ucIndex, pstEvent, (VOS_UINT16 *)pusLength);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReportCeregResult, Test_AT_ReportCeregResult_007)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent;
    VOS_UINT16                         *pusLength;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    g_astAtModemCtx[enModemId].stPlatformRatList.ucPlatformSptLte = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    pstEvent = (TAF_PHONE_EVENT_INFO_STRU*)malloc(sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pusLength = (VOS_UINT16*)malloc(sizeof(VOS_UINT16));
    pstEvent->CurRegSta.OP_PsRegState = VOS_FALSE;
    pstEvent->CurRegSta.OP_CellId = VOS_FALSE;
    pstEvent->CurRegSta.ucPsRegState = TAF_PH_REG_NOT_REGISTERED_SEARCHING;
    pstEvent->RatType = TAF_PH_INFO_LTE_RAT;


    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);
    pstNetCtx->ucCeregType = AT_CEREG_RESULT_CODE_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_PhReadCreg)
        .expects(never());

    /*MOCKER(At_sprintf)
        .expects(never());*/

    AT_ReportCeregResult(ucIndex, pstEvent, (VOS_UINT16 *)pusLength);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReportCeregResult, Test_AT_ReportCeregResult_008)
{
    VOS_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent;
    VOS_UINT16                         *pusLength;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    g_astAtModemCtx[enModemId].stPlatformRatList.ucPlatformSptLte = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    pstEvent = (TAF_PHONE_EVENT_INFO_STRU*)malloc(sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pusLength = (VOS_UINT16*)malloc(sizeof(VOS_UINT16));
    pstEvent->CurRegSta.OP_PsRegState = VOS_FALSE;
    pstEvent->CurRegSta.OP_CellId = VOS_FALSE;
    pstEvent->CurRegSta.ucPsRegState = TAF_PH_REG_NOT_REGISTERED_SEARCHING;
    pstEvent->RatType = TAF_PH_INFO_LTE_RAT;


    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);
    pstNetCtx->ucCeregType = AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE;

    // MOCKER操作
    MOCKER(At_PhReadCreg)
        .expects(never());

    /*MOCKER(At_sprintf)
        .expects(never());*/

    AT_ReportCeregResult(ucIndex, pstEvent, (VOS_UINT16 *)pusLength);
    GlobalMockObject::verify();
}
#endif


class Test_At_SmsDeliverProc: public ::testing::Test
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


TEST_F(Test_At_SmsDeliverProc, Test_At_SmsDeliverProc_001)
{
    TAF_UINT8                              ucIndex;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    ucIndex = 0;
    stEvent.clientId = AT_CLIENT_BUTT;

    At_SmsDeliverProc(ucIndex, &stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsDeliverProc, Test_At_SmsDeliverProc_002)
{
    TAF_UINT8                              ucIndex;
    MN_MSG_EVENT_INFO_STRU                 stEvent;
    VOS_UINT8                              ucUserId;
    MN_MSG_TS_DATA_INFO_STRU              *pstTsDataInfo;

    ucIndex = 1;
    ucUserId = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    pstTsDataInfo = At_GetMsgMem();
    pstTsDataInfo->enTpduType = MN_MSG_TPDU_DELIVER;
    pstTsDataInfo->u.stDeliver.stDcs.enMsgClass = MN_MSG_MSG_CLASS_0;
    g_enClass0Tailor = MN_MSG_CLASS0_VODAFONE;


    MOCKER(MN_MSG_Decode)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    At_SmsDeliverProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsDeliverProc, Test_At_SmsDeliverProc_003)
{
    //参数定义
    TAF_UINT8                              ucIndex;
    MN_MSG_EVENT_INFO_STRU                 stEvent;
    VOS_UINT8                              ucUserId;

    //参数初始化
    ucIndex = 1;
    ucUserId = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;

    //相关全局变量初始化
    g_enClass0Tailor                                             = MN_MSG_CLASS0_DEF;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCnmiType.CnmiModeType = AT_CNMI_MODE_SEND_OR_DISCARD_TYPE;

    //MOCKER操作
    MOCKER(MN_MSG_Decode)
    .stubs()
    .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    //调用被测函数
    At_SmsDeliverProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsDeliverProc, Test_At_SmsDeliverProc_004)
{
    //参数定义
    TAF_UINT8                              ucIndex;
    MN_MSG_EVENT_INFO_STRU                 stEvent;
    VOS_UINT8                              ucUserId;

    //参数初始化
    ucIndex = 1;
    ucUserId = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    stEvent.clientId = AT_BROADCAST_CLIENT_ID_MODEM_0;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCnmiType.CnmiModeType = AT_CNMI_MODE_BUFFER_TYPE;

    //MOCKER操作
    MOCKER(MN_MSG_Decode)
    .stubs()
    .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MOCKER(At_BufferMsgInTa)
        .expects(exactly(1));

    //调用被测函数
    At_SmsDeliverProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SmsDeliverProc, Test_At_SmsDeliverProc_005)
{
    //参数定义
    TAF_UINT8                              ucIndex;
    MN_MSG_EVENT_INFO_STRU                 stEvent;
    VOS_UINT8                              ucUserId;

    //参数初始化
    ucIndex = 1;
    ucUserId = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    stEvent.clientId = AT_BROADCAST_CLIENT_ID_MODEM_1;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiModeType = AT_CNMI_MODE_SEND_OR_BUFFER_TYPE;

    //MOCKER操作
    MOCKER(MN_MSG_Decode)
    .stubs()
    .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_ForwardMsgToTe).expects(exactly(1));

    //调用被测函数
    At_SmsDeliverProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsDeliverProc, Test_At_SmsDeliverProc_006)
{
    //参数定义
    TAF_UINT8                              ucIndex;
    MN_MSG_EVENT_INFO_STRU                 stEvent;
    VOS_UINT8                              ucUserId;

    //参数初始化
    ucIndex = 1;
    ucUserId = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    stEvent.clientId = AT_BROADCAST_CLIENT_ID_MODEM_1;

    //相关全局变量初始化
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiModeType = AT_CNMI_MODE_SEND_OR_BUFFER_TYPE;

    //MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(AT_IsClientBlock).stubs().will(returnValue((VOS_UINT32)VOS_TRUE));
    MOCKER(At_BufferMsgInTa).expects(exactly(1));

    //调用被测函数
    At_SmsDeliverProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif



#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

class Test_At_SmsDeliverCbmProc: public ::testing::Test
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


TEST_F(Test_At_SmsDeliverCbmProc, Test_AAt_SmsDeliverCbmProc_001)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId       = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCnmiType.CnmiModeType    = AT_CNMI_MODE_SEND_OR_DISCARD_TYPE;

    //MOCKER操作

    //调用被测函数
    At_SmsDeliverCbmProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsDeliverCbmProc, Test_AAt_SmsDeliverCbmProc_002)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId       = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCnmiType.CnmiModeType    = AT_CNMI_MODE_EMBED_AND_SEND_TYPE;

    //MOCKER操作

    //调用被测函数
    At_SmsDeliverCbmProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SmsDeliverCbmProc, Test_AAt_SmsDeliverCbmProc_003)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId       = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiModeType    = AT_CNMI_MODE_SEND_OR_BUFFER_TYPE;

    //MOCKER操作
    MOCKER(At_ForwardMsgToTe).expects(exactly(1));

    //调用被测函数
    At_SmsDeliverCbmProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsDeliverCbmProc, Test_AAt_SmsDeliverCbmProc_004)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId       = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCnmiType.CnmiModeType    = AT_CNMI_MODE_EMBED_AND_SEND_TYPE;

    //MOCKER操作

    //调用被测函数
    At_SmsDeliverCbmProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
#endif


class Test_At_SmsInitSmspResultProc: public ::testing::Test
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


TEST_F(Test_At_SmsInitSmspResultProc, Test_At_SmsInitSmspResultProc_001)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化
    stEvent.u.stInitSmspResultInfo.enClass0Tailor               = 2;

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    //MOCKER操作

    //调用被测函数
    At_SmsInitSmspResultProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查
    EXPECT_EQ(2, g_enClass0Tailor);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SmsInitSmspResultProc, Test_At_SmsInitSmspResultProc_002)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化
    stEvent.u.stInitSmspResultInfo.enClass0Tailor               = 3;

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    //MOCKER操作

    //调用被测函数
    At_SmsInitSmspResultProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查
    EXPECT_EQ(3, g_enClass0Tailor);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_SmsSrvParmChangeProc: public ::testing::Test
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


TEST_F(Test_At_SmsSrvParmChangeProc, Test_At_SmsSrvParmChangeProc_001)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    //MOCKER操作

    //调用被测函数
    At_SmsSrvParmChangeProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SmsSrvParmChangeProc, Test_At_SmsSrvParmChangeProc_002)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    //MOCKER操作

    //调用被测函数
    At_SmsSrvParmChangeProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_ReportCCallstateResult: public ::testing::Test
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


TEST_F(Test_AT_ReportCCallstateResult, Test_AT_ReportCCallstateResult_001)
{
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucCallId = 0;
    VOS_UINT8                           aucRptCfg[AT_CURC_RPT_CFG_MAX_SIZE];

    PS_MEM_SET(aucRptCfg, 0xFF, sizeof(aucRptCfg));
    usClientId = AT_CLIENT_BUTT;
    enCallState = AT_CS_CALL_STATE_HOLD;

    AT_ReportCCallstateResult(usClientId, ucCallId, aucRptCfg, enCallState, (TAF_CALL_VOICE_DOMAIN_ENUM_UINT8)TAF_CALL_VOICE_DOMAIN_IMS);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReportCCallstateResult, Test_AT_ReportCCallstateResult_002)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucCallId = 0;
    VOS_UINT8                           aucRptCfg[AT_CURC_RPT_CFG_MAX_SIZE];
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState;
    VOS_UINT8                           ucIndex;

    PS_MEM_SET(aucRptCfg, 0, sizeof(aucRptCfg));
    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    enCallState = AT_CS_CALL_STATE_HOLD;

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    AT_ReportCCallstateResult(usClientId, ucCallId, aucRptCfg, enCallState, (TAF_CALL_VOICE_DOMAIN_ENUM_UINT8)TAF_CALL_VOICE_DOMAIN_IMS);

    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_ReportCCallstateResult, Test_AT_ReportCCallstateResult_003)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucCallId = 0;
    VOS_UINT8                           aucRptCfg[AT_CURC_RPT_CFG_MAX_SIZE];
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState;
    VOS_UINT8                           ucIndex;

    PS_MEM_SET(aucRptCfg, 0, sizeof(aucRptCfg));
    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    usClientId = AT_BROADCAST_CLIENT_ID_MODEM_1;
    enCallState = AT_CS_CALL_STATE_HOLD;

    MOCKER(At_SendResultData).expects(exactly(1));

    AT_ReportCCallstateResult(usClientId, ucCallId, aucRptCfg, enCallState, (TAF_CALL_VOICE_DOMAIN_ENUM_UINT8)TAF_CALL_VOICE_DOMAIN_3GPP);

    GlobalMockObject::verify();
}
#endif


class Test_AT_ReportCCallstateHoldList: public ::testing::Test
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


TEST_F(Test_AT_ReportCCallstateHoldList, Test_AT_ReportCCallstateHoldList_001)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           aucCallId[MN_CALL_MAX_NUM] = {0};
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState;
    MN_CALL_EVT_HOLD_STRU               stHoldEvt;


    ucCallNum = 7;
    usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    enCallState = AT_CS_CALL_STATE_HOLD;
    PS_MEM_SET(&stHoldEvt, 0, sizeof(stHoldEvt));
    stHoldEvt.usClientId = usClientId;
    stHoldEvt.ucCallNum  = ucCallNum;
    PS_MEM_SET(stHoldEvt.aucCurcRptCfg, 0xFF, sizeof(stHoldEvt.aucCurcRptCfg));
    PS_MEM_CPY(stHoldEvt.aucCallId, aucCallId, sizeof(stHoldEvt.aucCallId));

    MOCKER(AT_ReportCCallstateResult).expects(exactly(7));

    AT_ReportCCallstateHoldList(&stHoldEvt, enCallState);

    GlobalMockObject::verify();
}


class Test_AT_RcvMmaRssiChangeInd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }
    void TearDown()
    {
    }

};


TEST_F(Test_AT_RcvMmaRssiChangeInd, Test_AT_RcvMmaRssiChangeInd_001)
{
    //参数定义
    TAF_UINT8                          ucIndex;
    TAF_MMA_RSSI_INFO_IND_STRU          stEvent;

    //参数初始化
    ucIndex = 0;
    stEvent.stRssiInfo.enRatType = TAF_MMA_RAT_GSM;

    //相关全局变量初始化
    AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucCerssiReportType = AT_CERSSI_REPORT_TYPE_2DB_CHANGE_REPORT;

    //MOCKER操作
    MOCKER(AT_CheckRptCmdStatus)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));
    MOCKER(At_SendResultData)
        .expects(exactly(2));

    //调用被测函数
    AT_RcvMmaRssiChangeInd(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvMmaRssiChangeInd, Test_AT_RcvMmaRssiChangeInd_002)
{
    //参数定义
    TAF_UINT8                          ucIndex;
    TAF_MMA_RSSI_INFO_IND_STRU          stEvent;

    //参数初始化
    ucIndex = 0;
    stEvent.stRssiInfo.enRatType = TAF_MMA_RAT_WCDMA;
    stEvent.stRssiInfo.ucCurrentUtranMode = TAF_UTRANCTRL_UTRAN_MODE_FDD;

    //相关全局变量初始化
    AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucCerssiReportType = AT_CERSSI_REPORT_TYPE_3DB_CHANGE_REPORT;

    //MOCKER操作
    MOCKER(AT_CheckRptCmdStatus)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));
    MOCKER(At_SendResultData)
        .expects(exactly(2));

    //调用被测函数
    AT_RcvMmaRssiChangeInd(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvMmaRssiChangeInd, Test_AT_RcvMmaRssiChangeInd_003)
{
    //参数定义
    TAF_UINT8                          ucIndex;
    TAF_MMA_RSSI_INFO_IND_STRU          stEvent;

    //参数初始化
    ucIndex = 0;
    stEvent.stRssiInfo.enRatType = TAF_MMA_RAT_WCDMA;
    stEvent.stRssiInfo.ucCurrentUtranMode = TAF_UTRANCTRL_UTRAN_MODE_TDD;

    //相关全局变量初始化
    AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucCerssiReportType = AT_CERSSI_REPORT_TYPE_3DB_CHANGE_REPORT;

    //MOCKER操作
    MOCKER(AT_CheckRptCmdStatus)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));
    MOCKER(At_SendResultData)
        .expects(exactly(2));

    //调用被测函数
    AT_RcvMmaRssiChangeInd(ucIndex,(TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_RcvMmaRssiChangeInd, Test_AT_RcvMmaRssiChangeInd_004)
{
}


#if 0

TEST_F(Test_AT_RcvMmaAcInfoChangeInd, Test_AT_RcvMmaAcInfoChangeInd_002)
{
    //参数定义
    TAF_UINT8                          ucIndex;
    TAF_PHONE_EVENT_INFO_STRU          stEvent;

    //参数初始化
    ucIndex = 0;
    stEvent.Op_CellAcInfo   = 1;
    stEvent.stCellAcInfo.enCellAcType = 0;
    stEvent.stCellAcInfo.ucSrvDomain  = 0;
    stEvent.stCellAcInfo.ucRestrictPagingRsp = VOS_TRUE;
    stEvent.stCellAcInfo.ucRestrictRegister  = VOS_TRUE;

    gstAtSendData.usBufLen = 32;

    //相关全局变量初始化
    AT_GetModemCtrlCtxAddrFromClientId(ucIndex)->ucStatusReportGeneralControl = AT_STATUS_REPORT_GENERAL_CONTROL_CUSTOM;

    MOCKER(AT_CheckRptCmdStatus).will(returnValue(VOS_FALSE));

    MOCKER(At_SendResultData).expects(never());

    //调用被测函数
    AT_RcvMmaAcInfoChangeInd(ucIndex,&stEvent);

    //执行检查
    EXPECT_EQ(32,gstAtSendData.usBufLen);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif




class Test_AT_ProcCsRspEvtCallProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ProcCsRspEvtCallProc, Test_AT_ProcCsRspEvtCallProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     pstAtClientCtx = AT_GetClientCtxAddr(ucClientIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     enEventType = MN_CALL_EVT_CALL_PROC;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = ucClientIndex;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen), pstEvent, sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     MOCKER(AT_GetModemIdFromClient).stubs().will(returnValue(VOS_ERR));
     MOCKER(At_SendResultData)
        .expects(never());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();

}


TEST_F(Test_AT_ProcCsRspEvtCallProc, Test_AT_ProcCsRspEvtCallProc_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;

     enEventType = MN_CALL_EVT_CALL_PROC;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = ucClientIndex;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->aucCurcRptCfg[4] = 0x0F;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen), pstEvent, sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n^CONF:1\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_0), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}



class Test_AT_ProcCsCallConnectInd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ProcCsCallConnectInd, Test_AT_ProcCsCallConnectInd_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;

     /* 初始化变量 */
     enEventType = MN_CALL_EVT_CONNECT;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x3fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = 0;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     MOCKER(AT_GetModemIdFromClient).stubs().will(returnValue((VOS_UINT32)VOS_ERR));

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);
     EXPECT_EQ((TAF_CS_CAUSE_ENUM_UINT32)TAF_CS_CAUSE_SUCCESS, pstCcCtx->enCsErrCause);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_ProcCsCallConnectInd, Test_AT_ProcCsCallConnectInd_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucClientIndex = 0x7f;

     enEventType = MN_CALL_EVT_CONNECT;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x7fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x7fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = 0;
     pstEvent->aucCurcRptCfg[4] = 0x0F;

     ulEventTypeLen  = sizeof(enEventType);
     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n^CONN:1,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(2))
        .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());


     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);
     EXPECT_EQ((TAF_CS_CAUSE_ENUM_UINT32)TAF_CS_CAUSE_SUCCESS, pstCcCtx->enCsErrCause);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#endif

class Test_AT_ProcCsRspEvtOrig: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {
       // At_PidInit(VOS_IP_INITIAL);
    }
};



TEST_F(Test_AT_ProcCsRspEvtOrig, Test_AT_ProcCsRspEvtOrig_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;

     enEventType = MN_CALL_EVT_ORIG;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     MOCKER(AT_GetModemIdFromClient)
         .stubs()
         .will(returnValue((VOS_UINT32)VOS_ERR));

     MOCKER(AT_ReportCCallstateResult)
        .expects(exactly(1));

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);
     EXPECT_EQ((VOS_UINT32)VOS_FALSE,  pstCcCtx->ulCurIsExistCallFlag);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


#if(FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_ProcCsRspEvtOrig, Test_AT_ProcCsRspEvtOrig_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;

     pstAtClientCtx = AT_GetClientCtxAddr(ucClientIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     enEventType = MN_CALL_EVT_ORIG;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x7fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->aucCurcRptCfg[4] = 0x0F;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n^ORIG:1,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());
      MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_BROADCAST_CLIENT_INDEX_MODEM_1), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);
     EXPECT_EQ((VOS_UINT32)VOS_TRUE,  pstCcCtx->ulCurIsExistCallFlag);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#endif


class Test_AT_CsUus1InfoEvtIndProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
         At_PidInit(VOS_IP_INITIAL);
         memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_CsUus1InfoEvtIndProc, Test_AT_CsUus1InfoEvtIndProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucClientIndex = 0x3f;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucClientIndex);

     enEventType = MN_CALL_EVT_UUS1_INFO;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x3fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = 0;
     pstEvent->enCallDir = MN_CALL_DIR_MO;

     ulEventTypeLen  = sizeof(enEventType);
     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     pcExpect = "";
     ASSERT_STREQ(pcExpect, (TAF_CHAR *)pgucAtSndCodeAddr);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_AT_CsUus1InfoEvtIndProc, Test_AT_CsUus1InfoEvtIndProc_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucClientIndex = 0x3f;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucClientIndex);

     enEventType = MN_CALL_EVT_UUS1_INFO;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x3fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = 0;
     pstEvent->enCallDir = MN_CALL_DIR_MT;

     ulEventTypeLen  = sizeof(enEventType);
     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     pcExpect = "";
     ASSERT_STREQ(pcExpect, (TAF_CHAR *)pgucAtSndCodeAddr);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


class Test_At_CsIncomingEvtOfIncomeStateIndProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
         At_PidInit(VOS_IP_INITIAL);
         memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_CsIncomingEvtOfIncomeStateIndProc, Test_At_CsIncomingEvtOfIncomeStateIndProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x3F;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);
     pstCcCtx->stS0TimeInfo.ucS0TimerLen = 2;
     pstCcCtx->stS0TimeInfo.bTimerStart = VOS_FALSE;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucCrcType = AT_CRC_ENABLE_TYPE;
     pstSsCtx->ucClipType = AT_CLIP_ENABLE_TYPE;
     pstSsCtx->ucSalsType = AT_SALS_ENABLE_TYPE;

     enEventType = MN_CALL_EVT_INCOMING;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x3fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->enCallState = MN_CALL_S_INCOMING;
     pstEvent->enAlsLineNo = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CRING: VOICE\r\n\r\n+CLIP: \"\",,\"\",,\"\",0\r\n\r\n^ALS: 1\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(2))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());


     MOCKER(AT_StartRelTimer)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->ulCurIsExistCallFlag);
     EXPECT_EQ((VOS_BOOL)VOS_TRUE, pstCcCtx->stS0TimeInfo.bTimerStart);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_CsIncomingEvtOfIncomeStateIndProc, Test_At_CsIncomingEvtOfIncomeStateIndProc_002)
{
    MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x7F;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucCrcType = AT_CRC_ENABLE_TYPE;
     pstSsCtx->ucClipType = AT_CLIP_ENABLE_TYPE;
     pstSsCtx->ucSalsType = AT_SALS_ENABLE_TYPE;

     enEventType = MN_CALL_EVT_INCOMING;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x7fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x7fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VIDEO;
     pstEvent->enCallState = MN_CALL_S_INCOMING;
     pstEvent->enAlsLineNo = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CRING: SYNC\r\n\r\n+CLIP: \"\",,\"\",,\"\",0\r\n\r\n^ALS: 1\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(2))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->ulCurIsExistCallFlag);
     EXPECT_EQ(0, pstCcCtx->stS0TimeInfo.ucS0TimerLen);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#endif

#if (FEATURE_ON == FEATURE_IMS)

TEST_F(Test_At_CsIncomingEvtOfIncomeStateIndProc, Test_At_CsIncomingEvtOfIncomeStateIndProc_003)
{
    MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
    MN_CALL_INFO_STRU                  *pstEvent;
    MN_CALL_EVENT_ENUM_U32              enEventType;
    TAF_UINT32                          ulEventTypeLen;
    TAF_UINT32                          ulTmpAddr;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    TAF_UINT16                          usLength;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           ucIndex = 0x3F;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    /* 初始化变量 */
    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pstCcCtx->stS0TimeInfo.ucS0TimerLen = 2;
    pstCcCtx->stS0TimeInfo.bTimerStart = VOS_FALSE;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->ucCrcType = AT_CRC_ENABLE_TYPE;
    pstSsCtx->ucClipType = AT_CLIP_ENABLE_TYPE;
    pstSsCtx->ucSalsType = AT_SALS_ENABLE_TYPE;

    enEventType = MN_CALL_EVT_INCOMING;
    ulEventTypeLen  = sizeof(enEventType);
    usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

    pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
    memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
    pMsg->clientId  = AT_BROADCAST_CLIENT_ID_MODEM_0;

    /* 填写新消息内容 */
    pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
    memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
    pstEvent->clientId = 0x3fff;
    pstEvent->callId = 1;
    pstEvent->enCallType = MN_CALL_TYPE_VOICE;
    pstEvent->enCallState = MN_CALL_S_INCOMING;
    pstEvent->enAlsLineNo = 1;
    pstEvent->enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;
    PS_MEM_SET(pstEvent->aucCurcRptCfg, 0xFF, sizeof(pstEvent->aucCurcRptCfg));

    ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
    PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
    PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

    /* 桩函数 */
    pcExpect    = "\r\nIRING\r\n\r\n+CLIP: \"\",,\"\",,\"\",0\r\n\r\n^ALS: 1\r\n";
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    pcExpect    = "\r\n^CCALLSTATE: 1,5,1\r\n";
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    MOCKER(AT_StartRelTimer)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 处理函数 */
    At_MsgProc((MsgBlock*)pMsg);

    /* 检查结果 */
    EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->ulCurIsExistCallFlag);
    EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->stS0TimeInfo.bTimerStart);

    free(pstEvent);
    free(pMsg);
    /* 检查调用时，需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_At_CsIncomingEvtOfIncomeStateIndProc, Test_At_CsIncomingEvtOfIncomeStateIndProc_004)
{
    MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
    MN_CALL_INFO_STRU                  *pstEvent;
    MN_CALL_EVENT_ENUM_U32              enEventType;
    TAF_UINT32                          ulEventTypeLen;
    TAF_UINT32                          ulTmpAddr;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    TAF_UINT16                          usLength;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           ucIndex = 0x3F;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    /* 初始化变量 */
    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pstCcCtx->stS0TimeInfo.ucS0TimerLen = 2;
    pstCcCtx->stS0TimeInfo.bTimerStart = VOS_FALSE;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->ucCrcType  = AT_CRC_DISABLE_TYPE;
    pstSsCtx->ucClipType = AT_CLIP_ENABLE_TYPE;
    pstSsCtx->ucSalsType = AT_SALS_ENABLE_TYPE;

    enEventType = MN_CALL_EVT_INCOMING;
    ulEventTypeLen  = sizeof(enEventType);
    usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

    pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
    memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
    pMsg->clientId  = AT_BROADCAST_CLIENT_ID_MODEM_0;

    /* 填写新消息内容 */
    pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
    memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
    pstEvent->clientId = 0x3fff;
    pstEvent->callId = 1;
    pstEvent->enCallType = MN_CALL_TYPE_VOICE;
    pstEvent->enCallState = MN_CALL_S_INCOMING;
    pstEvent->enAlsLineNo = 1;
    pstEvent->enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;
    PS_MEM_SET(pstEvent->aucCurcRptCfg, 0xFF, sizeof(pstEvent->aucCurcRptCfg));

    ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
    PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
    PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

    /* 桩函数 */
    pcExpect    = "\r\nIRING\r\n\r\n+CLIP: \"\",,\"\",,\"\",0\r\n\r\n^ALS: 1\r\n";
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    pcExpect    = "\r\n^CCALLSTATE: 1,5,1\r\n";
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    MOCKER(AT_StartRelTimer)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 处理函数 */
    At_MsgProc((MsgBlock*)pMsg);

    /* 检查结果 */
    EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->ulCurIsExistCallFlag);
    EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->stS0TimeInfo.bTimerStart);

    free(pstEvent);
    free(pMsg);
    /* 检查调用时，需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#endif

class Test_At_SsIndProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x3F;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x3FFF;
     pstEvent->SsEvent = TAF_SS_EVT_USS_REQ_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 1,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x3F;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x3FFF;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 0,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_009)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x3F;
     AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

     pstCommCtx = AT_GetCommCtxAddr();

     pstCommCtx->ucSystemAppConfigAddr = 0;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x3FFF;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 0;
     pstEvent->OP_UssdString =0;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_010)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x3F;
     AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

     pstCommCtx = AT_GetCommCtxAddr();

     pstCommCtx->ucSystemAppConfigAddr = 2;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x3FFF;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 0;
     pstEvent->OP_UssdString =0;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 2\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_003)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x3F;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x3FFF;
     pstEvent->SsEvent = TAF_SS_EVT_USS_REQ_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);


     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_004)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x3F;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x3FFF;
     pstEvent->SsEvent = TAF_SS_EVT_ERROR;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 0,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(never())
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_005)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x7F;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x7FFF;
     pstEvent->SsEvent = TAF_SS_EVT_USS_REQ_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 1,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_006)
{
    MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x7F;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x7FFF;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 0,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_007)
{
      MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x7F;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x7FFF;
     pstEvent->SsEvent = TAF_SS_EVT_USS_REQ_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);


     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsIndProc, Test_At_SsIndProc_008)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x7F;

     /* 初始化变量 */
     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 0x7FFF;
     pstEvent->SsEvent = TAF_SS_EVT_ERROR;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 0,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(never())
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#endif


class Test_At_SsRspUssdProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SsRspUssdProc, Test_At_SsRspUssdProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,(usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_USS_REQ_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 1,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspUssdProc, Test_At_SsRspUssdProc_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,(usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 0,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspUssdProc, Test_At_SsRspUssdProc_003)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,(usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SsRspUssdProc, Test_At_SsRspUssdProc_004)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,(usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_USS_REQ_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 1,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspUssdProc, Test_At_SsRspUssdProc_005)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,(usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 0,\"\",0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspUssdProc, Test_At_SsRspUssdProc_006)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,(usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 1;
     pstEvent->OP_UssdString = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#endif


TEST_F(Test_At_SsRspUssdProc, Test_At_SsRspUssdProc_008)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
     AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

     pstCommCtx = AT_GetCommCtxAddr();

     pstCommCtx->ucSystemAppConfigAddr = 2;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,(usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 0;
     pstEvent->OP_UssdString = 0;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 2\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspUssdProc, Test_At_SsRspUssdProc_009)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
     AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

     pstCommCtx = AT_GetCommCtxAddr();

     pstCommCtx->ucSystemAppConfigAddr = 0;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->usUssdTransMode = AT_USSD_TRAN_MODE;

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,(usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
     pstEvent->OP_DataCodingScheme = 0;
     pstEvent->OP_UssdString = 0;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CUSD: 2\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}



class Test_At_CsIncomingEvtOfWaitStateIndProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
         At_PidInit(VOS_IP_INITIAL);
         memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_CsIncomingEvtOfWaitStateIndProc, Test_At_CsIncomingEvtOfWaitStateIndProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x3F;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucCcwaType = AT_CCWA_ENABLE_TYPE;
     pstSsCtx->ucSalsType = AT_SALS_ENABLE_TYPE;

     enEventType = MN_CALL_EVT_INCOMING;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x3fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->enCallState = MN_CALL_S_WAITING;
     pstEvent->enAlsLineNo = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CCWA: ,,1\r\n\r\n^ALS: 1\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(2))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());


     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->ulCurIsExistCallFlag );
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_CsIncomingEvtOfWaitStateIndProc, Test_At_CsIncomingEvtOfWaitStateIndProc_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     TAF_UINT16                          usLength;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 0x7F;
     AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucCcwaType = AT_CCWA_ENABLE_TYPE;
     pstSsCtx->ucSalsType = AT_SALS_ENABLE_TYPE;

     enEventType = MN_CALL_EVT_INCOMING;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x7fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x7fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->enCallState = MN_CALL_S_WAITING;
     pstEvent->enAlsLineNo = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CCWA: ,,1\r\n\r\n^ALS: 1\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(2))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());


     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->ulCurIsExistCallFlag );
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#endif

#if (FEATURE_ON == FEATURE_IMS)

TEST_F(Test_At_CsIncomingEvtOfWaitStateIndProc, Test_At_CsIncomingEvtOfWaitStateIndProc_003)
{
    MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
    MN_CALL_INFO_STRU                  *pstEvent;
    MN_CALL_EVENT_ENUM_U32              enEventType;
    TAF_UINT32                          ulEventTypeLen;
    TAF_UINT32                          ulTmpAddr;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    TAF_UINT16                          usLength;
    VOS_CHAR                           *pcExpect;
    VOS_UINT8                           ucIndex = 0x3F;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    /* 初始化变量 */
    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->ucCcwaType = AT_CCWA_ENABLE_TYPE;
    pstSsCtx->ucSalsType = AT_SALS_ENABLE_TYPE;

    enEventType = MN_CALL_EVT_INCOMING;
    ulEventTypeLen  = sizeof(enEventType);
    usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

    pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
    PS_MEM_SET(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
    pMsg->clientId  = 0x3fff;

    /* 填写新消息内容 */
    pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
    PS_MEM_SET(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
    pstEvent->clientId                  = 0x3fff;
    pstEvent->callId                    = 1;
    pstEvent->enCallType                = MN_CALL_TYPE_VOICE;
    pstEvent->enCallState               = MN_CALL_S_WAITING;
    pstEvent->enAlsLineNo               = 1;
    pstEvent->enVoiceDomain             = TAF_CALL_VOICE_DOMAIN_IMS;
    PS_MEM_SET(pstEvent->aucCurcRptCfg, 0xFF ,sizeof(pstEvent->aucCurcRptCfg));

    ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
    PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
    PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

    /* 桩函数 */
    pcExpect    = "\r\n^CCWA: ,,1\r\n\r\n^ALS: 1\r\n";
    MOCKER(At_SendResultData)
       .expects(exactly(1))
       .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    pcExpect    = "\r\n^CCALLSTATE: 1,6,1\r\n";
     MOCKER(At_SendResultData)
       .expects(exactly(1))
       .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    /* 处理函数 */
    At_MsgProc((MsgBlock*)pMsg);

    /* 检查结果 */
    EXPECT_EQ((VOS_UINT32)VOS_TRUE, pstCcCtx->ulCurIsExistCallFlag );
    free(pstEvent);
    free(pMsg);
    /* 检查调用时，需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#endif




class Test_At_SsRspInterrogateCnfClipProc: public ::testing::Test
{
public:
    void SetUp()
    {
         UT_STUB_INIT();
         At_PidInit(VOS_IP_INITIAL);
         memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SsRspInterrogateCnfClipProc, Test_At_SsRspInterrogateCnfClipProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucClipType = AT_CLIP_DISABLE_TYPE;

     g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
     memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
     g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex = AT_CMD_CLIP;
     g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CLIP";

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_INTERROGATESS_CNF;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CLIP: 0,2\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT8)AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
     EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
     EXPECT_EQ(0, gastAtClientTab[ucIndex].hTimer);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SsRspInterrogateCnfClipProc, Test_At_SsRspInterrogateCnfClipProc_002)
{
    MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucClipType = AT_CLIP_ENABLE_TYPE;

     g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
     memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
     g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex = AT_CMD_CLIP;
     g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CLIP";

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_INTERROGATESS_CNF;
     pstEvent->OP_SsStatus = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CLIP: 1,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT8)AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
     EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
     EXPECT_EQ(0, gastAtClientTab[ucIndex].hTimer);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#endif


class Test_At_SsRspInterrogateCnfClirProc: public ::testing::Test
{
public:
    void SetUp()
    {
         UT_STUB_INIT();
         At_PidInit(VOS_IP_INITIAL);
         memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SsRspInterrogateCnfClirProc, Test_At_SsRspInterrogateCnfClirProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucClirType = AT_CLIR_INVOKE;

     g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
     memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
     g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex = AT_CMD_CLIR;
     g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CLIR";

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_INTERROGATESS_CNF;
     pstEvent->OP_SsStatus = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CLIR: 1,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT8)AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
     EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
     EXPECT_EQ(0, gastAtClientTab[ucIndex].hTimer);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SsRspInterrogateCnfClirProc, Test_At_SsRspInterrogateCnfClirProc_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucClirType = AT_CLIR_SUPPRESS;

     g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
     memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
     g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex = AT_CMD_CLIR;
     g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+CLIR";

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_INTERROGATESS_CNF;
     pstEvent->OP_SsStatus = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+CLIR: 2,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT8)AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
     EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
     EXPECT_EQ(0, gastAtClientTab[ucIndex].hTimer);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#endif

class Test_At_QryParaRspCopsProc: public ::testing::Test
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


TEST_F(Test_At_QryParaRspCopsProc,Test_At_QryParaRspCopsProc_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_NETWORKNAME_STRU             stCops;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_CHAR                            acExpectedStr[] = "+COPS: 1,0,\"China Mobile\",0";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_COPS,
        At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
        At_AbortCopsPara,   AT_COPS_LIST_ABORT_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2)"};


    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->ucCopsFormatType = AT_COPS_LONG_ALPH_TYPE;

    memset(&stCops, 0, sizeof(stCops));
    stCops.PlmnSelMode = TAF_PH_PLMN_SEL_MODE_MANUAL;
    stCops.Name.PlmnId.Mcc = 0x460;
    stCops.Name.PlmnId.Mnc = 0x1;
    stCops.RaMode = TAF_PH_RA_GSM;
    memcpy(stCops.Name.aucOperatorNameLong, "China Mobile", sizeof("China Mobile"));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_OK));

    At_QryParaRspCopsProc(ucIndex, 1, (VOS_VOID *)&stCops);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

TEST_F(Test_At_QryParaRspCopsProc,Test_At_QryParaRspCopsProc_002)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_NETWORKNAME_STRU             stCops;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_CHAR                            acExpectedStr[] = "+COPS: 1,1,\"China Union\",2";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_COPS,
        At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
        At_AbortCopsPara,   AT_COPS_LIST_ABORT_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2)"};


    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->ucCopsFormatType = AT_COPS_SHORT_ALPH_TYPE;

    memset(&stCops, 0, sizeof(stCops));
    stCops.PlmnSelMode = TAF_PH_PLMN_SEL_MODE_MANUAL;
    stCops.Name.PlmnId.Mcc = 0x460;
    stCops.Name.PlmnId.Mnc = 0x02;
    stCops.RaMode = TAF_PH_RA_WCDMA;
    memcpy(stCops.Name.aucOperatorNameShort, "China Union", sizeof("China Union"));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_OK));

    At_QryParaRspCopsProc(ucIndex, 1, (VOS_VOID *)&stCops);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_At_QryParaRspCopsProc,Test_At_QryParaRspCopsProc_003)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_NETWORKNAME_STRU             stCops;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_CHAR                            acExpectedStr[] = "+COPS: 1,2,\"460001\",7";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_COPS,
        At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
        At_AbortCopsPara,   AT_COPS_LIST_ABORT_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2)"};


    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->ucCopsFormatType = AT_COPS_NUMERIC_TYPE;

    memset(&stCops, 0, sizeof(stCops));
    stCops.PlmnSelMode = TAF_PH_PLMN_SEL_MODE_MANUAL;
    stCops.Name.PlmnId.Mcc = 0x460;
    stCops.Name.PlmnId.Mnc = 0x01;
    stCops.RaMode = TAF_PH_RA_LTE;

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_OK));

    At_QryParaRspCopsProc(ucIndex, 1, (VOS_VOID *)&stCops);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_At_QryParaRspCopsProc,Test_At_QryParaRspCopsProc_004)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_NETWORKNAME_STRU             stCops;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_CHAR                            acExpectedStr[] = "+COPS: 1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_COPS,
        At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
        At_AbortCopsPara,   AT_COPS_LIST_ABORT_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2)"};


    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->ucCopsFormatType = AT_COPS_NUMERIC_TYPE;

    memset(&stCops, 0, sizeof(stCops));
    stCops.PlmnSelMode = TAF_PH_PLMN_SEL_MODE_MANUAL;
    stCops.Name.PlmnId.Mcc = 0;
    stCops.Name.PlmnId.Mnc = 0;
    stCops.RaMode = TAF_PH_RA_LTE;

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_OK));

    At_QryParaRspCopsProc(ucIndex, 1, (VOS_VOID *)&stCops);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


class Test_At_QryParaRspCregProc: public ::testing::Test
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


TEST_F(Test_At_QryParaRspCregProc,Test_At_QryParaRspCregProc_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_REG_STATE_STRU               stCreg;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_CHAR                            acExpectedStr[] = "+CREG: 2,1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =        {AT_CMD_CREG,
        At_SetCregPara,     AT_NOT_SET_TIME,  At_QryCregPara,   AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CREG",    (VOS_UINT8*)"(0-2)"};



    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->ucCregType = AT_CREG_RESULT_CODE_ENTIRE_TYPE;

    memset(&stCreg, 0, sizeof(stCreg));
    stCreg.RegState = TAF_PH_REG_REGISTERED_HOME_NETWORK;
    stCreg.CellId.ucCellNum = 0;

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_OK));

    At_QryParaRspCregProc(ucIndex, 1, (VOS_VOID *)&stCreg);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


class Test_At_QryParaRspCgregProc: public ::testing::Test
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


TEST_F(Test_At_QryParaRspCgregProc,Test_At_QryParaRspCgregProc_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_REG_STATE_STRU               stCgreg;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_CHAR                            acExpectedStr[] = "+CGREG: 2,1";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =     {AT_CMD_CGREG,
        At_SetCgregPara,    AT_NOT_SET_TIME,  At_QryCgregPara,  AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CGREG",   (VOS_UINT8*)"(0-2)"};

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->ucCgregType = AT_CGREG_RESULT_CODE_ENTIRE_TYPE;

    memset(&stCgreg, 0, sizeof(stCgreg));
    stCgreg.ucPsRegState = TAF_PH_REG_REGISTERED_HOME_NETWORK;
    stCgreg.CellId.ucCellNum = 0;

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_OK));

    At_QryParaRspCgregProc(ucIndex, 1, (VOS_VOID *)&stCgreg);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_LTE)

class Test_AT_QryParaRspCeregProc: public ::testing::Test
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


TEST_F(Test_AT_QryParaRspCeregProc,Test_AT_QryParaRspCeregProc_001)
{
    VOS_UINT8                           ucIndex;
    TAF_PH_REG_STATE_STRU               stCereg;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_CHAR                            acExpectedStr[] = "+CEREG: 2,5";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement         =    {AT_CMD_CEREG,
        AT_SetCeregPara,    AT_NOT_SET_TIME,  At_QryCeregPara,  AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CEREG",   (VOS_UINT8*)"(0-2)"};

    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->ucCeregType = AT_CEREG_RESULT_CODE_ENTIRE_TYPE;

    memset(&stCereg, 0, sizeof(stCereg));
    stCereg.ucPsRegState = TAF_PH_REG_REGISTERED_ROAM;
    stCereg.ucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
    stCereg.CellId.ucCellNum = 0;

    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex),eq((VOS_UINT32)AT_OK));

    AT_QryParaRspCeregProc(ucIndex, 1,(VOS_VOID *) &stCereg);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
#endif



class Test_At_SetCscaCsmpRspProc: public ::testing::Test
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


TEST_F(Test_At_SetCscaCsmpRspProc, Test_At_SetCscaCsmpRspProc_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    gastAtClientTab[ucIndex].CmdCurrentOpt                      = AT_CMD_CSMP_SET;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_SetCscaCsmpRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_SetCscaCsmpRspProc, Test_At_SetCscaCsmpRspProc_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_FALSE;
    stEvent.u.stSrvParmInfo.ulFailCause                         = MN_ERR_NOMEM;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CMS_MEMORY_FAILURE));

    // 调用被测函数
    At_SetCscaCsmpRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SetCscaCsmpRspProc, Test_At_SetCscaCsmpRspProc_003)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    gastAtClientTab[ucIndex].CmdCurrentOpt                      = AT_CMD_CSMP_SET;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_SetCscaCsmpRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetCscaCsmpRspProc, Test_At_SetCscaCsmpRspProc_004)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_FALSE;
    stEvent.u.stSrvParmInfo.ulFailCause                         = MN_ERR_CLASS_SMS_UPDATE_USIM;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_CMS_U_SIM_BUSY));

    // 调用被测函数
    At_SetCscaCsmpRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_ReadRspProc: public ::testing::Test
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


TEST_F(Test_At_ReadRspProc, Test_At_ReadRspProc_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGR: ,,10\r\n0000000000000000000000";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGR,
                                                        At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)", (TAF_UINT8*)"(0-65535)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stReadInfo.stMsgInfo.stScAddr.ucBcdLen            = 0;
    stEvent.u.stReadInfo.stMsgInfo.stTsRawData.ulLen            = 10;
    PS_MEM_SET(stEvent.u.stReadInfo.stMsgInfo.stTsRawData.aucData, 0x00, MN_MSG_MAX_LEN);

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    PS_MEM_SET(&gstAtSendData.aucBuffer[3], 0, (AT_CMD_MAX_LEN + 17));

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ReadRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ReadRspProc, Test_At_ReadRspProc_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGR: ,\"\",,\"00/00/00,00:00:00+00\",128,4,0,0,,2,0\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGR,
                                                        At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)", (TAF_UINT8*)"(0-65535)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stReadInfo.stMsgInfo.stTsRawData.enTpduType       = MN_MSG_TPDU_DELIVER;
    stEvent.u.stReadInfo.stMsgInfo.stScAddr.addrType            = 2;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    g_stAtMsgTsDataInfo.u.stDeliver.enPid                       = 0;
    g_stAtMsgTsDataInfo.u.stDeliver.stDcs.ucRawDcsData          = 1;
    g_stAtMsgTsDataInfo.u.stDeliver.stUserData.ulLen            = 3;

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ReadRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ReadRspProc, Test_At_ReadRspProc_003)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGR: ,\"\",,128,4,0,0,,,2,0\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGR,
                                                        At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)", (TAF_UINT8*)"(0-65535)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stReadInfo.stMsgInfo.stTsRawData.enTpduType       = MN_MSG_TPDU_SUBMIT;
    stEvent.u.stReadInfo.stMsgInfo.stScAddr.addrType            = 2;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    g_stAtMsgTsDataInfo.u.stSubmit.enPid                        = 0;
    g_stAtMsgTsDataInfo.u.stSubmit.stDcs.ucRawDcsData           = 1;
    g_stAtMsgTsDataInfo.u.stSubmit.stUserData.ulLen             = 3;
    PS_MEM_SET(g_stAtMsgTsDataInfo.u.stSubmit.stUserData.aucOrgData, 0x00, g_stAtMsgTsDataInfo.u.stSubmit.stUserData.ulLen);

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ReadRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_ReadRspProc, Test_At_ReadRspProc_004)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGR: ,4,0,0,0,\"\",128,0\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGR,
                                                        At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)", (TAF_UINT8*)"(0-65535)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stReadInfo.stMsgInfo.stTsRawData.enTpduType       = MN_MSG_TPDU_COMMAND;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    g_stAtMsgTsDataInfo.u.stCommand.enCmdType                   = MN_MSG_COMMAND_TYPE_ENQUIRY;
    g_stAtMsgTsDataInfo.u.stCommand.enPid                       = 0;
    g_stAtMsgTsDataInfo.u.stCommand.ucMsgNumber                 = 1;
    g_stAtMsgTsDataInfo.u.stCommand.ucCommandDataLen            = 3;
    PS_MEM_SET(g_stAtMsgTsDataInfo.u.stCommand.aucCmdData, 0x00, g_stAtMsgTsDataInfo.u.stCommand.ucCommandDataLen);

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ReadRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_ReadRspProc, Test_At_ReadRspProc_005)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGR: ,,5\r\n000000000000\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGR,
                                                        At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)", (TAF_UINT8*)"(0-65535)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stReadInfo.stMsgInfo.stScAddr.ucBcdLen            = 0;
    stEvent.u.stReadInfo.stMsgInfo.stTsRawData.ulLen            = 5;
    PS_MEM_SET(stEvent.u.stReadInfo.stMsgInfo.stTsRawData.aucData, 0x00, stEvent.u.stReadInfo.stMsgInfo.stTsRawData.ulLen);

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;;

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ReadRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ReadRspProc, Test_At_ReadRspProc_006)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGR: ,\"\",,\"00/00/00,00:00:00+00\",128,4,0,0,,2,0\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGR,
                                                        At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)", (TAF_UINT8*)"(0-65535)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stReadInfo.stMsgInfo.stTsRawData.enTpduType       = MN_MSG_TPDU_DELIVER;
    stEvent.u.stReadInfo.stMsgInfo.stScAddr.addrType            = 2;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    g_stAtMsgTsDataInfo.u.stDeliver.enPid                       = 1;
    g_stAtMsgTsDataInfo.u.stDeliver.stDcs.ucRawDcsData          = 2;
    g_stAtMsgTsDataInfo.u.stDeliver.stUserData.ulLen            = 3;

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ReadRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ReadRspProc, Test_At_ReadRspProc_007)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGR: ,\"\",,128,4,0,0,,,2,0\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGR,
                                                        At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)", (TAF_UINT8*)"(0-65535)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stReadInfo.stMsgInfo.stTsRawData.enTpduType       = MN_MSG_TPDU_SUBMIT;
    stEvent.u.stReadInfo.stMsgInfo.stScAddr.addrType            = 2;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    g_stAtMsgTsDataInfo.u.stSubmit.enPid                        = 1;
    g_stAtMsgTsDataInfo.u.stSubmit.stDcs.ucRawDcsData           = 2;
    g_stAtMsgTsDataInfo.u.stSubmit.stUserData.ulLen             = 3;
    PS_MEM_SET(g_stAtMsgTsDataInfo.u.stSubmit.stUserData.aucOrgData, 0x00, g_stAtMsgTsDataInfo.u.stSubmit.stUserData.ulLen);

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ReadRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_ReadRspProc, Test_At_ReadRspProc_008)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGR: ,4,0,0,0,\"\",128,0\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGR,
        At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)", (TAF_UINT8*)"(0-65535)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stReadInfo.stMsgInfo.stTsRawData.enTpduType       = MN_MSG_TPDU_COMMAND;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    g_stAtMsgTsDataInfo.u.stCommand.enCmdType                   = MN_MSG_COMMAND_TYPE_ENQUIRY;
    g_stAtMsgTsDataInfo.u.stCommand.enPid                       = 1;
    g_stAtMsgTsDataInfo.u.stCommand.ucMsgNumber                 = 2;
    g_stAtMsgTsDataInfo.u.stCommand.ucCommandDataLen            = 3;
    PS_MEM_SET(g_stAtMsgTsDataInfo.u.stCommand.aucCmdData, 0x00, g_stAtMsgTsDataInfo.u.stCommand.ucCommandDataLen);

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ReadRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif



class Test_At_ListRspProc: public ::testing::Test
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


TEST_F(Test_At_ListRspProc,Test_At_ListRspProc_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGL: 1,,,5\r\n000000000000\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGL,
                                                        At_SetCmglPara,  AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGL", (VOS_UINT8*)"(\"REC UNREAD\",\"REC READ\",\"STO UNSENT\",\"STO SENT\",\"ALL\")", (TAF_UINT8*)"(0-4)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stListInfo.bLastListEvt                           = TAF_TRUE;
    stEvent.u.stListInfo.ulReportNum                            = 1;
    stEvent.u.stListInfo.astSmInfo[0].ulIndex                   = 1;
    stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stScAddr.ucBcdLen = 0;
    stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stTsRawData.ulLen = 5;
    PS_MEM_SET(stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stTsRawData.aucData, 0x00, MN_MSG_MAX_LEN);

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    PS_MEM_SET(&gstAtSendData.aucBuffer[3], 0, (AT_CMD_MAX_LEN + 17));

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ListRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ListRspProc,Test_At_ListRspProc_001_1)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_LIST_PARM_STRU               stEvtList;
    MN_MSG_LIST_PARM_STRU               stList;



    VOS_CHAR                            acExpectedStr[] = "+CMGL: 1,1,,5\r\n000000000000\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGL,
                                                        At_SetCmglPara,  AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGL", (VOS_UINT8*)"(\"REC UNREAD\",\"REC READ\",\"STO UNSENT\",\"STO SENT\",\"ALL\")", (TAF_UINT8*)"(0-4)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stListInfo.bLastListEvt                           = TAF_FALSE;
    stEvent.u.stListInfo.ulReportNum                            = 1;
    stEvent.u.stListInfo.astSmInfo[0].ulIndex                   = 1;
    stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stScAddr.ucBcdLen = 0;
    stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stTsRawData.ulLen = 5;

    stList.bChangeFlag      = VOS_TRUE;
    stList.enMemStore       = MN_MSG_MEM_STORE_SIM;
    stList.enStatus         = (TAF_UINT8)MN_MSG_STATUS_MT_NOT_READ;
    stList.ucIsFirstTimeReq =  VOS_FALSE;

    stEvtList.bChangeFlag      = VOS_TRUE;
    stEvtList.enMemStore       = MN_MSG_MEM_STORE_SIM;
    stEvtList.enStatus         = (TAF_UINT8)MN_MSG_STATUS_MT_NOT_READ;
    stEvtList.ucIsFirstTimeReq =  VOS_TRUE;

    PS_MEM_CPY( &(stEvent.u.stListInfo.stReceivedListPara), &stEvtList, sizeof(stEvtList));

    PS_MEM_SET(stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stTsRawData.aucData, 0x00, MN_MSG_MAX_LEN);


    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    PS_MEM_SET(&gstAtSendData.aucBuffer[3], 0, (AT_CMD_MAX_LEN + 17));

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    At_ListRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}




TEST_F(Test_At_ListRspProc,Test_At_ListRspProc_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;
    VOS_CHAR                            acExpectedStr[] = "+CMGL: 1,,\"\",,\"00/00/00,00:00:00+00\",128,0\r\n\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGL,
                                                        At_SetCmglPara,  AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGL", (VOS_UINT8*)"(\"REC UNREAD\",\"REC READ\",\"STO UNSENT\",\"STO SENT\",\"ALL\")", (TAF_UINT8*)"(0-4)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stListInfo.bLastListEvt                           = TAF_TRUE;
    stEvent.u.stListInfo.ulReportNum                            = 1;
    stEvent.u.stListInfo.astSmInfo[0].ulIndex                   = 1;
    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.stUserData.ulLen = 5;
    PS_MEM_SET(stTsDataInfo.u.stDeliver.stUserData.aucOrgData, 0x00, MN_MSG_MAX_LEN);

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    PS_MEM_SET(&gstAtSendData.aucBuffer[3], 0, (AT_CMD_MAX_LEN + 17));

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ListRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_ListRspProc,Test_At_ListRspProc_003)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_CHAR                            acExpectedStr[] = "+CMGL: 1,,,5\r\n000000000000\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGL,
                                                        At_SetCmglPara,  AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGL", (VOS_UINT8*)"(\"REC UNREAD\",\"REC READ\",\"STO UNSENT\",\"STO SENT\",\"ALL\")", (TAF_UINT8*)"(0-4)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stListInfo.bLastListEvt                           = TAF_TRUE;
    stEvent.u.stListInfo.ulReportNum                            = 1;
    stEvent.u.stListInfo.astSmInfo[0].ulIndex                   = 1;
    stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stScAddr.ucBcdLen = 0;
    stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stTsRawData.ulLen = 5;
    PS_MEM_SET(stEvent.u.stListInfo.astSmInfo[0].stMsgInfo.stTsRawData.aucData, 0x00, MN_MSG_MAX_LEN);

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ListRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

TEST_F(Test_At_ListRspProc,Test_At_ListRspProc_004)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;
    VOS_CHAR                            acExpectedStr[] = "+CMGL: 1,,\"\",,\"00/00/00,00:00:00+00\",128,0\r\n\r\n";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;
    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CMGL,
                                                        At_SetCmglPara,  AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,    AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CMGL", (VOS_UINT8*)"(\"REC UNREAD\",\"REC READ\",\"STO UNSENT\",\"STO SENT\",\"ALL\")", (TAF_UINT8*)"(0-4)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stListInfo.bLastListEvt                           = TAF_TRUE;
    stEvent.u.stListInfo.ulReportNum                            = 1;
    stEvent.u.stListInfo.astSmInfo[0].ulIndex                   = 1;
    stTsDataInfo.enTpduType = MN_MSG_TPDU_SUBMIT;
    stTsDataInfo.u.stSubmit.stUserData.ulLen = 5;
    PS_MEM_SET(stTsDataInfo.u.stSubmit.stUserData.aucOrgData, 0x00, MN_MSG_MAX_LEN);

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    PS_MEM_SET(&gstAtSendData.aucBuffer[3], 0, (AT_CMD_MAX_LEN + 17));

    // MOCKER操作
    MOCKER(MN_MSG_Decode).stubs().will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_ListRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif


class Test_At_GetCbActiveMidsRspProc: public ::testing::Test
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
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

TEST_F(Test_At_GetCbActiveMidsRspProc,Test_At_GetCbActiveMidsRspProc_001)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSCB,
                                                        At_SetCscbPara,     AT_SET_PARA_TIME,
                                                        At_QryCscbPara,     AT_QRY_PARA_TIME,
                                                        AT_TestCscbPara,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (TAF_UINT8*)"+CSCB",    (VOS_UINT8*)"(0,1),(MIDS),(DCSS)"};
    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stCbsCbMids.stCbMidr.usCbmirNum                   = 10;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_GetCbActiveMidsRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_GetCbActiveMidsRspProc,Test_At_GetCbActiveMidsRspProc_002)
{
    // 参数定义
    TAF_UINT8                           ucIndex = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSCB,
                                                        At_SetCscbPara,     AT_SET_PARA_TIME,
                                                        At_QryCscbPara,     AT_QRY_PARA_TIME,
                                                        AT_TestCscbPara,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (TAF_UINT8*)"+CSCB",    (VOS_UINT8*)"(0,1),(MIDS),(DCSS)"};

    // 参数初始化
    stEvent.u.stSrvParmInfo.bSuccess                            = TAF_TRUE;
    stEvent.u.stCbsCbMids.stCbMidr.usCbmirNum                   = 10;

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_GetCbActiveMidsRspProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
#endif



class Test_At_ForwardMsgToTeInCmt: public ::testing::Test
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


TEST_F(Test_At_ForwardMsgToTeInCmt,Test_At_ForwardMsgToTeInCmt_001)
{
    // 参数定义
    VOS_UINT8                            ucIndex = 0;
    TAF_UINT16                           usSendLength = 10;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;

    // MOCKER操作

    // 调用被测函数
    At_ForwardMsgToTeInCmt(ucIndex, &usSendLength, &stTsDataInfo, &stEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_ForwardMsgToTeInCmt,Test_At_ForwardMsgToTeInCmt_002)
{
    // 参数定义
    VOS_UINT8                            ucIndex = 0;
    TAF_UINT16                           usSendLength = 10;
    MN_MSG_TS_DATA_INFO_STRU             stTsDataInfo;
    MN_MSG_EVENT_INFO_STRU               stEvent;

    // 参数初始化

    // 相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_TEXT;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.ucCsdhType             = AT_CSDH_SHOW_TYPE;

    // MOCKER操作

    // 调用被测函数
    At_ForwardMsgToTeInCmt(ucIndex, &usSendLength, &stTsDataInfo, &stEvent);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_SsRspInterrogateCnfColpProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SsRspInterrogateCnfColpProc, Test_At_SsRspInterrogateCnfColpProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucColpType = AT_CLIP_ENABLE_TYPE;

     gucAtVType = AT_V_ENTIRE_TYPE;
     memset(&gstAtCombineSendData[ucIndex], 0, sizeof(gstAtCombineSendData[ucIndex]));

     g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
     memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
     g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex = AT_CMD_COLP;
     g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+COLP";

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_INTERROGATESS_CNF;
     pstEvent->OP_SsStatus = 1;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+COLP: 1,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT8)AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
     EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
     EXPECT_EQ(0, gastAtClientTab[ucIndex].hTimer);

     free(pstEvent);
     free(pMsg);
     memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
     free(g_stParseContext[ucIndex].pstCmdElement);

     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SsRspInterrogateCnfColpProc, Test_At_SsRspInterrogateCnfColpProc_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = TAF_NULL_PTR;
     TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
     TAF_UINT16                          usLen;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_CHAR                           *pcExpect;
     VOS_UINT8                           ucIndex = 1;
     AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

     /* 初始化变量 */
     pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
     pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

     pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);
     pstSsCtx->ucColpType = AT_CLIP_DISABLE_TYPE;

     gucAtVType = AT_V_ENTIRE_TYPE;
     memset(&gstAtCombineSendData[ucIndex], 0, sizeof(gstAtCombineSendData[ucIndex]));

     g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)malloc(sizeof(AT_PAR_CMD_ELEMENT_STRU));
     memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
     g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex = AT_CMD_COLP;
     g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"+COLP";

     usLen = sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);
     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I1_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;
     pMsg->usMsgName = MN_CALLBACK_SS;
     pMsg->usLen = usLen;

     /* 填写新消息内容 */
     pstEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)malloc(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     memset(pstEvent, 0 ,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
     pstEvent->ClientId = 1;
     pstEvent->SsEvent = TAF_SS_EVT_INTERROGATESS_CNF;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY((TAF_VOID *)pMsg->aucContent, pstEvent, usLen);

    /* 桩函数 */
     pcExpect    = "\r\n+COLP: 0,2\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     /* 检查结果 */
     EXPECT_EQ((VOS_UINT8)AT_FW_CLIENT_STATUS_READY, g_stParseContext[ucIndex].ucClientStatus);
     EXPECT_EQ((AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
     EXPECT_EQ(0, gastAtClientTab[ucIndex].hTimer);

     free(pstEvent);
     free(pMsg);
     memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
     free(g_stParseContext[ucIndex].pstCmdElement);

     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#endif



class Test_At_ProcCsRspEvtCssiNotifiy: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_ProcCsRspEvtCssiNotifiy, Test_At_ProcCsRspEvtCssiNotifiy_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_MO_CUG_INFO;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->aucUnsolicitedRptCfg[2] = 0x08;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSI: 4,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IMS)

TEST_F(Test_At_ProcCsRspEvtCssiNotifiy, Test_At_ProcCsRspEvtCssiNotifiy_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId                 = ucClientIndex;
     pstEvent->callId                   = 1;
     pstEvent->enCallType               = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode        = MN_CALL_SS_NTFY_MO_CUG_INFO;
     pstEvent->stSsNotify.ulCugIndex    = 0;
     pstEvent->aucUnsolicitedRptCfg[2]  = 0x08;
     pstEvent->enVoiceDomain            = TAF_CALL_VOICE_DOMAIN_IMS;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n^CSSI: 4,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#endif


class Test_At_ProcCsRspEvtCssuNotifiy: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_ProcCsRspEvtCssuNotifiy, Test_At_ProcCsRspEvtCssuNotifiy_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_FORWORDED_CALL;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0x10;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSU: 0,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_ProcCsRspEvtCssuNotifiy, Test_At_ProcCsRspEvtCssuNotifiy_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_MT_CUG_INFO;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0x10;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSU: 1,0,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_ProcCsRspEvtCssuNotifiy, Test_At_ProcCsRspEvtCssuNotifiy_003)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_ON_HOLD;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0x10;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSU: 2,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_ProcCsRspEvtCssuNotifiy, Test_At_ProcCsRspEvtCssuNotifiy_004)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_RETRIEVED;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0x10;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSU: 3,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_ProcCsRspEvtCssuNotifiy, Test_At_ProcCsRspEvtCssuNotifiy_005)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_ENTER_MPTY;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0x10;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSU: 4,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_ProcCsRspEvtCssuNotifiy, Test_At_ProcCsRspEvtCssuNotifiy_006)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_DEFLECTED_CALL;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0x10;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSU: 9,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);
     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_At_ProcCsRspEvtCssuNotifiy, Test_At_ProcCsRspEvtCssuNotifiy_007)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_EXPLICIT_CALL_TRANSFER;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0x10;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSU: ,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_IMS)

TEST_F(Test_At_ProcCsRspEvtCssuNotifiy, Test_At_ProcCsRspEvtCssuNotifiy_008)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = ucClientIndex;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_EXPLICIT_CALL_TRANSFER;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0x10;
     pstEvent->enVoiceDomain           = TAF_CALL_VOICE_DOMAIN_IMS;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n^CSSU: ,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#endif


class Test_AT_CsSsNotifyEvtIndProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        At_PidInit(VOS_IP_INITIAL);
        memset(&gstAtSendData, 0, sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_CsSsNotifyEvtIndProc, Test_AT_CsSsNotifyEvtIndProc_001)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0x3f;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x3fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_MO_CUG_INFO;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->aucUnsolicitedRptCfg[2] = 0xFF;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSI: 4,0\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}


TEST_F(Test_AT_CsSsNotifyEvtIndProc, Test_AT_CsSsNotifyEvtIndProc_002)
{
     MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
     MN_CALL_INFO_STRU                  *pstEvent;
     MN_CALL_EVENT_ENUM_U32              enEventType;
     TAF_UINT32                          ulEventTypeLen;
     TAF_UINT32                          ulTmpAddr;
     MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
     TAF_UINT16                          usLength;
     VOS_UINT8                           ucClientIndex = 0x3f;
     VOS_CHAR                           *pcExpect;
     AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
     VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

     pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

     enEventType = MN_CALL_EVT_SS_NOTIFY;
     ulEventTypeLen  = sizeof(enEventType);
     usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

     pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
     memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

     /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
     pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
     pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
     pMsg->ulReceiverPid   = WUEPS_PID_AT;

     pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
     pMsg->clientId  = 0x3fff;

     /* 填写新消息内容 */
     pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
     memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
     pstEvent->clientId = 0x3fff;
     pstEvent->callId = 1;
     pstEvent->enCallType = MN_CALL_TYPE_VOICE;
     pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_MT_CUG_INFO;
     pstEvent->stSsNotify.ulCugIndex = 0;
     pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
     PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
     pstEvent->stCcbsFeature.OP_CcbsIndex = MN_CALL_OPTION_EXIST;
     pstEvent->aucUnsolicitedRptCfg[2] = 0xFF;

     ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
     PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
     PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

     /* 桩函数 */
     pcExpect    = "\r\n+CSSU: 1,0,\"8613902001\",128\r\n";
     MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

     /* 处理函数 */
     At_MsgProc((MsgBlock*)pMsg);

     free(pstEvent);
     free(pMsg);
     /* 检查调用时，需要在用例结束位置加上这句 */
     GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IMS)

TEST_F(Test_AT_CsSsNotifyEvtIndProc, Test_AT_CsSsNotifyEvtIndProc_003)
{
    MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                  *pstEvent;
    MN_CALL_EVENT_ENUM_U32              enEventType;
    TAF_UINT32                          ulEventTypeLen;
    TAF_UINT32                          ulTmpAddr;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    TAF_UINT16                          usLength;
    VOS_UINT8                           ucClientIndex = 0x3f;
    VOS_CHAR                           *pcExpect;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

    pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

    enEventType = MN_CALL_EVT_SS_NOTIFY;
    ulEventTypeLen  = sizeof(enEventType);
    usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

    pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
    memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
    pMsg->clientId  = 0x3fff;

    /* 填写新消息内容 */
    pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
    memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
    pstEvent->clientId = 0x3fff;
    pstEvent->callId = 1;
    pstEvent->enCallType = MN_CALL_TYPE_VOICE;
    pstEvent->stSsNotify.enCode = MN_CALL_SS_NTFY_MO_CUG_INFO;
    pstEvent->stSsNotify.ulCugIndex = 0;
    pstEvent->stCallNumber.ucNumLen = sizeof(aucBcd);
    PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
    pstEvent->aucUnsolicitedRptCfg[2] = 0xFF;
    pstEvent->enVoiceDomain            = TAF_CALL_VOICE_DOMAIN_IMS;

    ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
    PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
    PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

    /* 桩函数 */
    pcExpect    = "\r\n^CSSI: 4,0\r\n";
    MOCKER(At_SendResultData)
       .expects(exactly(1))
       .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    /* 处理函数 */
    At_MsgProc((MsgBlock*)pMsg);

    free(pstEvent);
    free(pMsg);
    /* 检查调用时，需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_AT_CsSsNotifyEvtIndProc, Test_AT_CsSsNotifyEvtIndProc_004)
{
    MN_AT_IND_EVT_STRU                 *pMsg = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                  *pstEvent;
    MN_CALL_EVENT_ENUM_U32              enEventType;
    TAF_UINT32                          ulEventTypeLen;
    TAF_UINT32                          ulTmpAddr;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    TAF_UINT16                          usLength;
    VOS_UINT8                           ucClientIndex = 0x3f;
    VOS_CHAR                           *pcExpect;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucBcd[] = {0x68,0x31,0x09,0x02,0x10};

    pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

    enEventType = MN_CALL_EVT_SS_NOTIFY;
    ulEventTypeLen  = sizeof(enEventType);
    usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

    pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
    memset(pMsg, 0 ,sizeof(MN_AT_IND_EVT_STRU));

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = I0_WUEPS_PID_TAF;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
    pMsg->clientId  = 0x3fff;

    /* 填写新消息内容 */
    pstEvent = (MN_CALL_INFO_STRU*)malloc(sizeof(MN_CALL_INFO_STRU));
    memset(pstEvent, 0 ,sizeof(MN_CALL_INFO_STRU));
    pstEvent->clientId                  = 0x3fff;
    pstEvent->callId                    = 1;
    pstEvent->enCallType = MN_CALL_TYPE_VOICE;
    pstEvent->stSsNotify.enCode         = MN_CALL_SS_NTFY_MT_CUG_INFO;
    pstEvent->stSsNotify.ulCugIndex     = 0;
    pstEvent->stCallNumber.ucNumLen     = sizeof(aucBcd);
    PS_MEM_CPY(pstEvent->stCallNumber.aucBcdNum, aucBcd, pstEvent->stCallNumber.ucNumLen );
    pstEvent->stCcbsFeature.OP_CcbsIndex = MN_CALL_OPTION_EXIST;
    pstEvent->aucUnsolicitedRptCfg[2]   = 0xFF;
    pstEvent->enVoiceDomain             = TAF_CALL_VOICE_DOMAIN_IMS;

    ulTmpAddr = (VOS_UINT_PTR)pMsg->aucContent;
    PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
    PS_MEM_CPY((VOS_VOID*)(pMsg->aucContent + ulEventTypeLen),pstEvent,sizeof(MN_CALL_INFO_STRU));

    /* 桩函数 */
    pcExpect    = "\r\n^CSSU: 1,0,\"8613902001\",128\r\n";
    MOCKER(At_SendResultData)
       .expects(exactly(1))
       .with(eq(ucClientIndex), mirror((VOS_UINT8 *)pcExpect, VOS_StrLen(pcExpect)), any());

    /* 处理函数 */
    At_MsgProc((MsgBlock*)pMsg);

    free(pstEvent);
    free(pMsg);
    /* 检查调用时，需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#endif



class Test_At_BufferMsgInTa: public ::testing::Test
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


TEST_F(Test_At_BufferMsgInTa,Test_At_BufferMsgInTa_001)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_ENUM_U32                  enEvent = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;

    //MOCKER操作

    //调用被测函数
    At_BufferMsgInTa(ucIndex, enEvent, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_BufferMsgInTa,Test_At_BufferMsgInTa_002)
{
    //参数定义
    VOS_UINT8                              ucIndex = 0;
    MN_MSG_EVENT_ENUM_U32                  enEvent = 0;
    MN_MSG_EVENT_INFO_STRU                 stEvent;

    //参数初始化

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;

    //MOCKER操作

    //调用被测函数
    At_BufferMsgInTa(ucIndex, enEvent, &stEvent);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif



class Test_At_HandleSmtBuffer: public ::testing::Test
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


TEST_F(Test_At_HandleSmtBuffer,Test_At_HandleSmtBuffer_001)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    AT_CNMI_BFR_TYPE                    ucBfrType;
    TAF_UINT8                           ucLoop = 0;

    //参数初始化
    ucBfrType = AT_CNMI_BFR_SEND_TYPE;

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId           = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stSmtBuffer.aucUsed[ucLoop]    = AT_MSG_BUFFER_USED;

    //MOCKER操作
    MOCKER(At_ForwardMsgToTe).expects(exactly(1));

    //调用被测函数
    At_HandleSmtBuffer(ucIndex, ucBfrType);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_HandleSmtBuffer,Test_At_HandleSmtBuffer_002)
{
    //参数定义
    VOS_UINT8                           ucIndex = 0;
    AT_CNMI_BFR_TYPE                    ucBfrType;
    TAF_UINT8                           ucLoop = 0;

    //参数初始化
    ucBfrType = AT_CNMI_BFR_SEND_TYPE;

    //相关全局变量初始化
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId           = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stSmtBuffer.aucUsed[ucLoop]    = AT_MSG_BUFFER_USED;

    //MOCKER操作
    MOCKER(At_ForwardMsgToTe).expects(exactly(1));

    //调用被测函数
    At_HandleSmtBuffer(ucIndex, ucBfrType);

    //执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_RcvMnCallChannelInfoInd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }
    void TearDown()
    {
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }

};


TEST_F(Test_AT_RcvMnCallChannelInfoInd, Test_AT_RcvMnCallChannelInfoInd_001)
{
    MN_AT_IND_EVT_STRU                 *pstEvent;
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;

    /* 增加自定义的ITEM，共4个字节 */
    pstEvent = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_AT_IND_EVT_STRU)+sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));
    if (TAF_NULL_PTR == pstEvent)
    {
        return;
    }

    pstEvent->ulSenderPid       = WUEPS_PID_TAF;
    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->usMsgName         = MN_CALLBACK_CS_CALL;
    pstEvent->usLen             = sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU);

    stChannelEvt.enEvent                                  = MN_CALL_EVT_CHANNEL_INFO_IND;
    stChannelEvt.usClientId                               = MN_CLIENT_ALL;
    stChannelEvt.enCodecType                              = MN_CALL_CODEC_TYPE_BUTT;
    stChannelEvt.ucIsLocalAlertingFlag                    = VOS_FALSE;

    PS_MEM_CPY(pstEvent->aucContent, &stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    MOCKER(At_ClientIdToUserId)
        .expects(never());

    At_MsgProc((MsgBlock*)pstEvent);

    PS_MEM_FREE(WUEPS_PID_TAF, pstEvent);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_RcvMnCallChannelInfoInd, Test_AT_RcvMnCallChannelInfoInd_002)
{
    MN_AT_IND_EVT_STRU                 *pstEvent;
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_AT_IND_EVT_STRU)+sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));
    if (TAF_NULL_PTR == pstEvent)
    {
        return;
    }

    pstEvent->ulSenderPid       = WUEPS_PID_TAF;
    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->usMsgName         = MN_CALLBACK_CS_CALL;
    pstEvent->usLen             = sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU);

    stChannelEvt.enEvent                                  = MN_CALL_EVT_CHANNEL_INFO_IND;
    stChannelEvt.usClientId                               = MN_CLIENT_ALL;
    stChannelEvt.enCodecType                              = MN_CALL_CODEC_TYPE_AMRWB;

    PS_MEM_CPY(pstEvent->aucContent, &stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    /*MOCKER(At_sprintf)
        .expects(never());*/

    At_MsgProc((MsgBlock*)pstEvent);

    PS_MEM_FREE(WUEPS_PID_TAF, pstEvent);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_RcvMnCallChannelInfoInd, Test_AT_RcvMnCallChannelInfoInd_003)
{
    MN_AT_IND_EVT_STRU                 *pstEvent;
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;
    VOS_CHAR                            aucDataAt[30] = "\r\n^CSCHANNELINFO: 2,0\r\n";

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_AT_IND_EVT_STRU)+sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));
    if (TAF_NULL_PTR == pstEvent)
    {
        return;
    }

    pstEvent->ulSenderPid       = I0_WUEPS_PID_TAF;
    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->usMsgName         = MN_CALLBACK_CS_CALL;
    pstEvent->usLen             = sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU);

    stChannelEvt.enEvent                                  = MN_CALL_EVT_CHANNEL_INFO_IND;
    stChannelEvt.usClientId                               = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stChannelEvt.enCodecType                              = MN_CALL_CODEC_TYPE_AMRWB;
    stChannelEvt.ucIsLocalAlertingFlag                    = VOS_FALSE;
    stChannelEvt.enVoiceDomain                            = TAF_CALL_VOICE_DOMAIN_3GPP;

    PS_MEM_CPY(pstEvent->aucContent, &stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    At_MsgProc((MsgBlock*)pstEvent);

    PS_MEM_FREE(WUEPS_PID_TAF, pstEvent);

    EXPECT_STREQ((VOS_CHAR*)aucDataAt, (VOS_CHAR*)(pgucAtSndCodeAddr));
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvMnCallChannelInfoInd, Test_AT_RcvMnCallChannelInfoInd_004)
{
    MN_AT_IND_EVT_STRU                 *pstEvent;
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;
    VOS_CHAR                            aucDataAt[30] = "\r\n^CSCHANNELINFO: 1,1\r\n";

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_AT_IND_EVT_STRU)+sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));
    if (TAF_NULL_PTR == pstEvent)
    {
        return;
    }

    pstEvent->ulSenderPid       = I0_WUEPS_PID_TAF;
    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->usMsgName         = MN_CALLBACK_CS_CALL;
    pstEvent->usLen             = sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU);

    stChannelEvt.enEvent                                  = MN_CALL_EVT_CHANNEL_INFO_IND;
    stChannelEvt.usClientId                               = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stChannelEvt.enCodecType                              = MN_CALL_CODEC_TYPE_AMR;
    stChannelEvt.ucIsLocalAlertingFlag                    = VOS_FALSE;
    stChannelEvt.enVoiceDomain                            = TAF_CALL_VOICE_DOMAIN_IMS;

    PS_MEM_CPY(pstEvent->aucContent, &stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    At_MsgProc((MsgBlock*)pstEvent);

    PS_MEM_FREE(WUEPS_PID_TAF, pstEvent);

    EXPECT_STREQ((VOS_CHAR*)aucDataAt, (VOS_CHAR*)(pgucAtSndCodeAddr));
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvMnCallChannelInfoInd, Test_AT_RcvMnCallChannelInfoInd_005)
{
    MN_AT_IND_EVT_STRU                 *pstEvent;
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;
    VOS_CHAR                            aucDataAt[30] = "\r\n^CSCHANNELINFO: 1,1\r\n";

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_AT_IND_EVT_STRU)+sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));
    if (TAF_NULL_PTR == pstEvent)
    {
        return;
    }

    pstEvent->ulSenderPid       = I0_WUEPS_PID_TAF;
    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->usMsgName         = MN_CALLBACK_CS_CALL;
    pstEvent->usLen             = sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU);

    stChannelEvt.enEvent                                  = MN_CALL_EVT_CHANNEL_INFO_IND;
    stChannelEvt.usClientId                               = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stChannelEvt.enCodecType                              = MN_CALL_CODEC_TYPE_AMR2;
    stChannelEvt.ucIsLocalAlertingFlag                    = VOS_FALSE;
    stChannelEvt.enVoiceDomain                            = TAF_CALL_VOICE_DOMAIN_IMS;

    PS_MEM_CPY(pstEvent->aucContent, &stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    At_MsgProc((MsgBlock*)pstEvent);

    PS_MEM_FREE(WUEPS_PID_TAF, pstEvent);

    EXPECT_STREQ((VOS_CHAR*)aucDataAt, (VOS_CHAR*)(pgucAtSndCodeAddr));
    GlobalMockObject::verify();
}



class Test_At_QryMmPlmnInfoRspProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }
    void TearDown()
    {
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }

};

TEST_F(Test_At_QryMmPlmnInfoRspProc, Test_At_QryMmPlmnInfoRspProc_001)
{
    TAF_MMA_MM_INFO_PLMN_NAME_STRU      stEvent;
    AT_PAR_CMD_ELEMENT_STRU             stCmdElenent;

    g_stParseContext[0].pstCmdElement = &stCmdElenent;

    g_stParseContext[0].pstCmdElement->pszCmdName = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, 20);
    if (TAF_NULL_PTR == g_stParseContext[0].pstCmdElement->pszCmdName)
    {
        return;
    }

    stEvent.ucLongNameLen       = 1;
    stEvent.ucShortNameLen      = 0;

    //g_stParseContext[0].pstCmdElement->pszCmdName = "MM";

   // PS_MEM_CPY(g_stParseContext[0].pstCmdElement->pszCmdName , 'M', 1);



    At_QryMmPlmnInfoRspProc(0, 0, (TAF_VOID *)&stEvent);


    //EXPECT_STREQ(11, gstAtSendData.usBufLen);
    GlobalMockObject::verify();
}




class Test_AT_GetSsEventErrorCode: public ::testing::Test
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


TEST_F(Test_AT_GetSsEventErrorCode, Test_AT_GetSsEventErrorCode_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU  stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(stEvent));
    stEvent.OP_Error    = VOS_TRUE;
    stEvent.ErrorCode   = TAF_ERR_ERROR;
    stEvent.OP_SsStatus = VOS_TRUE;
    stEvent.SsStatus    = 0;

    // 初始化全局变量

    // 调用被测函数
    ulRet = AT_GetSsEventErrorCode(0, &stEvent);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_CME_SERVICE_NOT_PROVISIONED, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetSsEventErrorCode, Test_AT_GetSsEventErrorCode_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU  stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(stEvent));
    stEvent.OP_Error    = VOS_TRUE;
    stEvent.ErrorCode   = TAF_ERR_ERROR;
    stEvent.OP_SsStatus = VOS_TRUE;
    stEvent.SsStatus    = TAF_SS_PROVISIONED_STATUS_MASK;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ChgTafErrorCode)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_CME_UNKNOWN));

    // 调用被测函数
    ulRet = AT_GetSsEventErrorCode(0, (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_CME_UNKNOWN, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetSsEventErrorCode, Test_AT_GetSsEventErrorCode_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU  stEvent;

    //参数初始化
    memset(&stEvent, 0, sizeof(stEvent));
    stEvent.OP_Error    = VOS_TRUE;
    stEvent.ErrorCode   = TAF_ERR_ERROR;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ChgTafErrorCode)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_CME_UNKNOWN));

    // 调用被测函数
    ulRet = AT_GetSsEventErrorCode(0, (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_CME_UNKNOWN, ulRet);

    GlobalMockObject::verify();
}


class Test_At_RcvXlemaQryCnf: public ::testing::Test
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


TEST_F(Test_At_RcvXlemaQryCnf, Test_At_RcvXlemaQryCnf_001)
{
    // 变量声明
    MN_CALL_ECC_NUM_INFO_STRU           stEccNum;
    MN_AT_IND_EVT_STRU                 *pstEvent;
    VOS_UINT8                           ucIndex;

    /* 填充上报事件 */
    PS_MEM_SET(&stEccNum, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    stEccNum.enEvent    = MN_CALL_EVT_XLEMA_CNF;
    stEccNum.usClientId = 1;
    stEccNum.ulEccNumCount = 2;
    stEccNum.astCustomEccNumList[0].ucCategory = 1;
    stEccNum.astCustomEccNumList[0].ucValidSimPresent = 1;
    stEccNum.astCustomEccNumList[0].ucEccNumLen = 0x2;
    stEccNum.astCustomEccNumList[0].aucEccNum[0] = 0x11;
    stEccNum.astCustomEccNumList[0].aucEccNum[1] = 0xF8;
    stEccNum.astCustomEccNumList[0].ulMcc = 0x104;

    stEccNum.astCustomEccNumList[1].ucCategory = 1;
    stEccNum.astCustomEccNumList[1].ucValidSimPresent = 1;
    stEccNum.astCustomEccNumList[1].ucEccNumLen = 0x2;
    stEccNum.astCustomEccNumList[1].aucEccNum[0] = 0x11;
    stEccNum.astCustomEccNumList[1].aucEccNum[1] = 0xF9;
    stEccNum.astCustomEccNumList[1].ulMcc = 0x104;

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(MN_CALL_ECC_NUM_INFO_STRU) + MN_AT_INTERFACE_MSG_HEADER_LEN));

    pstEvent->ulReceiverPid = WUEPS_PID_AT;
    pstEvent->ulSenderPid   = WUEPS_PID_TAF;
    pstEvent->usLen         = sizeof(MN_CALL_ECC_NUM_INFO_STRU);
    pstEvent->usMsgName     = MN_CALLBACK_CS_CALL;
    pstEvent->clientId      = 1;
    PS_MEM_CPY(pstEvent->aucContent, &stEccNum, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    ucIndex = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XLEMA_QRY;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    //MOCKER(At_SendResultData)
    //    .expects(exactly(1))
    //    .with(eq(0x01), mirror("\r\n^XLEMA: 1,1,118,1,1,410\r\n"));

    //MOCKER(At_SendResultData)
    //    .expects(exactly(1))
    //    .with(eq(0x01), mirror("\r\n^XLEMA: 1,1,119,1,1,410\r\n"));

    At_CsMsgProc(pstEvent, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvXlemaQryCnf, Test_At_RcvXlemaQryCnf_002)
{
    // 变量声明
    MN_CALL_ECC_NUM_INFO_STRU           stEccNum;
    MN_AT_IND_EVT_STRU                 *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr1[] = "\r\n^XLEMA: 1,2,901010,1,1,410\r\n";
    VOS_CHAR                            acExpectedStr2[] = "\r\n^XLEMA: 2,2,00,1,1,410\r\n";

    /* 填充上报事件 */
    PS_MEM_SET(&stEccNum, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    stEccNum.enEvent    = MN_CALL_EVT_XLEMA_CNF;
    stEccNum.usClientId = 1;
    stEccNum.ulEccNumCount = 2;
    stEccNum.astCustomEccNumList[0].ucCategory = 1;
    stEccNum.astCustomEccNumList[0].ucValidSimPresent = 1;
    stEccNum.astCustomEccNumList[0].ucEccNumLen = 0x3;
    stEccNum.astCustomEccNumList[0].aucEccNum[0] = 0x09;
    stEccNum.astCustomEccNumList[0].aucEccNum[1] = 0x01;
    stEccNum.astCustomEccNumList[0].aucEccNum[2] = 0x01;
    stEccNum.astCustomEccNumList[0].ulMcc = 0x104;

    stEccNum.astCustomEccNumList[1].ucCategory = 1;
    stEccNum.astCustomEccNumList[1].ucValidSimPresent = 1;
    stEccNum.astCustomEccNumList[1].ucEccNumLen = 0x3;
    stEccNum.astCustomEccNumList[1].aucEccNum[0] = 0x00;
    stEccNum.astCustomEccNumList[1].aucEccNum[1] = 0x0F;
    stEccNum.astCustomEccNumList[1].aucEccNum[2] = 0xFF;
    stEccNum.astCustomEccNumList[1].ulMcc = 0x104;

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(MN_CALL_ECC_NUM_INFO_STRU) + MN_AT_INTERFACE_MSG_HEADER_LEN));

    pstEvent->ulReceiverPid = WUEPS_PID_AT;
    pstEvent->ulSenderPid   = WUEPS_PID_TAF;
    pstEvent->usLen         = sizeof(MN_CALL_ECC_NUM_INFO_STRU);
    pstEvent->usMsgName     = MN_CALLBACK_CS_CALL;
    pstEvent->clientId      = 1;
    PS_MEM_CPY(pstEvent->aucContent, &stEccNum, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    ucIndex = 1;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XLEMA_QRY;
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)acExpectedStr1, 0x1e),any());

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(any(), mirror((VOS_UINT8 *)acExpectedStr2, 0x1a),any());

    MOCKER(At_FormatResultData).expects(exactly(1));

    At_CsMsgProc(pstEvent, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    // 执行检查
    GlobalMockObject::verify();
}



class Test_At_PrintReportData: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        gucAtCscsType                = AT_CSCS_IRA_CODE;
        pgucAtSndCodeAddr            = &gstAtSendData.aucBuffer[3];
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_PrintReportData, Test_At_PrintReportData_001)
{
    // 变量声明
    TAF_UINT8                           aucOutput[] = "42304B30";
    VOS_UINT16                          usOutputLength;
    VOS_UINT8                           aucSrc[] = {0x42,0x30,0x4b,0x30};
    VOS_UINT16                          usSrcLen;
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPass;

    ////参数初始化
    usSrcLen = sizeof(aucSrc);
    usOutputLength = strlen((char *)aucOutput);

    //// 初始化全局变量;

    //// MOCKER操作;

    //// 调用被测函数
    usLength = At_PrintReportData(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, MN_MSG_MSG_CODING_UCS2, pgucAtSndCodeAddr, aucSrc, usSrcLen);

    if (!strncmp((char *)aucOutput, (char *)pgucAtSndCodeAddr, usOutputLength))
    {
        bPass = VOS_TRUE;
    }
    else
    {
        bPass = VOS_FALSE;
    }

    // 执行检查
    EXPECT_EQ(usOutputLength, usLength);
    EXPECT_EQ((VOS_BOOL)VOS_TRUE, bPass);

    GlobalMockObject::verify();

}


TEST_F(Test_At_PrintReportData, Test_At_PrintReportData_002)
{
    // 变量声明
    TAF_UINT8                           aucOutput[] = "DDD";
    VOS_UINT16                          usOutputLength;
    VOS_UINT8                           aucSrc[] = {0x44,0x44,0x44};
    VOS_UINT16                          usSrcLen;
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPass;

    ////参数初始化
    usSrcLen = sizeof(aucSrc);
    usOutputLength = strlen((char *)aucOutput);

    //// 初始化全局变量;

    //// MOCKER操作;

    //// 调用被测函数
    usLength = At_PrintReportData(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, MN_MSG_MSG_CODING_7_BIT, pgucAtSndCodeAddr, aucSrc, usSrcLen);

    if (!strncmp((char *)aucOutput, (char *)pgucAtSndCodeAddr, usOutputLength))
    {
        bPass = VOS_TRUE;
    }
    else
    {
        bPass = VOS_FALSE;
    }

    // 执行检查
    EXPECT_EQ(usOutputLength, usLength);
    EXPECT_EQ((VOS_BOOL)VOS_TRUE, bPass);

    GlobalMockObject::verify();

}


TEST_F(Test_At_PrintReportData, Test_At_PrintReportData_003)
{
    // 变量声明
    TAF_UINT8                           aucOutput[] = "442211";
    VOS_UINT16                          usOutputLength;
    VOS_UINT8                           aucSrc[] = {0x44,0x22,0x11};
    VOS_UINT16                          usSrcLen;
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPass;

    ////参数初始化
    usSrcLen = sizeof(aucSrc);
    usOutputLength = strlen((char *)aucOutput);

    //// 初始化全局变量;
    gucAtCscsType                = AT_CSCS_UCS2_CODE;

    //// MOCKER操作;

    //// 调用被测函数
    usLength = At_PrintReportData((TAF_UINT32)AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (MN_MSG_MSG_CODING_ENUM_U8)MN_MSG_MSG_CODING_7_BIT, pgucAtSndCodeAddr, aucSrc, usSrcLen);

    if (!strncmp((char *)aucOutput, (char *)pgucAtSndCodeAddr, usOutputLength))
    {
        bPass = VOS_FALSE;
    }
    else
    {
        bPass = VOS_TRUE;
    }

    // 执行检查
    EXPECT_EQ(12, usLength);
    EXPECT_EQ((VOS_BOOL)VOS_TRUE, bPass);

    GlobalMockObject::verify();

}


class Test_AT_PrintSmsLength: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        gucAtCscsType                = AT_CSCS_IRA_CODE;
        pgucAtSndCodeAddr            = &gstAtSendData.aucBuffer[3];
    }
    void TearDown()
    {

    }
};
#if 1

TEST_F(Test_AT_PrintSmsLength, Test_AT_PrintSmsLength_001)
{
    // 变量声明
    TAF_UINT8                           aucOutput[] = ",2";
    VOS_UINT16                          usOutputLength;
    VOS_UINT8                           aucSrc[] = {0x42,0x30,0x4b,0x30};
    VOS_UINT16                          usSrcLen;
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPass;

    ////参数初始化
    usSrcLen = sizeof(aucSrc);
    usOutputLength = strlen((char *)aucOutput);

    //// 初始化全局变量;

    //// MOCKER操作;

    //// 调用被测函数
    usLength = AT_PrintSmsLength(MN_MSG_MSG_CODING_UCS2, usSrcLen, pgucAtSndCodeAddr);

    if (!strncmp((char *)aucOutput, (char *)pgucAtSndCodeAddr, usOutputLength))
    {
        bPass = VOS_TRUE;
    }
    else
    {
        bPass = VOS_FALSE;
    }

    // 执行检查
    EXPECT_EQ(usOutputLength, usLength);
    EXPECT_EQ((VOS_BOOL)VOS_TRUE, bPass);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_PrintSmsLength, Test_AT_PrintSmsLength_002)
{
    // 变量声明
    TAF_UINT8                           aucOutput[] = ",3";
    VOS_UINT16                          usOutputLength;
    VOS_UINT8                           aucSrc[] = {0x44,0x44,0x44};
    VOS_UINT16                          usSrcLen;
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPass;

    ////参数初始化
    usSrcLen = sizeof(aucSrc);
    usOutputLength = strlen((char *)aucOutput);

    //// 初始化全局变量;

    //// MOCKER操作;

    //// 调用被测函数
    usLength = AT_PrintSmsLength(MN_MSG_MSG_CODING_7_BIT, usSrcLen, pgucAtSndCodeAddr);

    if (!strncmp((char *)aucOutput, (char *)pgucAtSndCodeAddr, usOutputLength))
    {
        bPass = VOS_TRUE;
    }
    else
    {
        bPass = VOS_FALSE;
    }

    // 执行检查
    EXPECT_EQ(usOutputLength, usLength);
    EXPECT_EQ((VOS_BOOL)VOS_TRUE, bPass);

    GlobalMockObject::verify();

}
#endif


class Test_At_GetClckClassFromBsCode: public ::testing::Test
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


TEST_F(Test_At_GetClckClassFromBsCode, Test_At_GetClckClassFromBsCode_001)
{
    // 变量声明
    AT_CLCK_PARA_CLASS_ENUM_UINT8       ucClass;
    TAF_SS_BASIC_SERVICE_STRU           stBs    = {0};

    // 参数初始化
    stBs.BsType         = TAF_SS_TELE_SERVICE;
    stBs.BsServiceCode  = TAF_ALL_TELESERVICES_TSCODE;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ucClass = At_GetClckClassFromBsCode(&stBs);

    // 执行检查
    EXPECT_EQ((TAF_UINT8)AT_CLCK_PARA_CLASS_VOICE_DATA_FAX_SMS, ucClass);

    GlobalMockObject::verify();
}


TEST_F(Test_At_GetClckClassFromBsCode, Test_At_GetClckClassFromBsCode_002)
{
    // 变量声明
    AT_CLCK_PARA_CLASS_ENUM_UINT8       ucClass;
    TAF_SS_BASIC_SERVICE_STRU           stBs    = {0};

    // 参数初始化
    stBs.BsType         = TAF_SS_TELE_SERVICE;
    stBs.BsServiceCode  = TAF_ALL_SYNCHRONOUS_SERVICES_BSCODE;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ucClass = At_GetClckClassFromBsCode(&stBs);

    // 执行检查
    EXPECT_EQ((TAF_UINT8)AT_UNKNOWN_CLCK_CLASS, ucClass);

    GlobalMockObject::verify();
}


class Test_At_SsRspInterrogateCnfClckProc: public ::testing::Test
{
public:
    VOS_UINT8                               ucIndex;
    AT_PAR_CMD_ELEMENT_STRU                 stCmdInfo;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU      stEvent;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_CLCK;
        stCmdInfo.pfnSetProc        = At_SetClckPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = At_TestClckPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnAbortProc      = VOS_NULL_PTR;
        stCmdInfo.ulAbortTimeOut    = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_LIMITED_NULL;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"+CLCK";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(\"P2\",\"SC\",\"AO\",\"OI\",\"OX\",\"AI\",\"IR\",\"AB\",\"AG\",\"AC\",\"PS\",\"FD\"),(0-2),(psw),(1-255)";

        PS_MEM_SET(&stEvent, 0, sizeof(stEvent));

        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCK_LOCK;
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_SsRspInterrogateCnfClckProc, Test_At_SsRspInterrogateCnfClckProc_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr = "+CLCK: 0,255,2";
    usLength = 0;
    stEvent.OP_SsStatus = VOS_TRUE;
    stEvent.SsStatus    = TAF_SS_REGISTERED_STATUS_MASK;

    // 初始化全局变量
    g_stAtSsCustomizePara.ucStatus          = VOS_TRUE;
    g_stAtSsCustomizePara.ucSsCmdCustomize  = 0x02;

    // MOCKER操作

    // 调用被测函数
    At_SsRspInterrogateCnfClckProc(ucIndex, &stEvent, &ulRet, &usLength);

    // 执行检查
    EXPECT_EQ((TAF_UINT32)AT_OK, ulRet);
    EXPECT_EQ(strlen(pcExpectStr), usLength);
    ASSERT_STREQ(pcExpectStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspInterrogateCnfClckProc, Test_At_SsRspInterrogateCnfClckProc_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr = "+CLCK: 0";
    usLength = 0;
    stEvent.OP_SsStatus = VOS_FALSE;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    At_SsRspInterrogateCnfClckProc(ucIndex, &stEvent, &ulRet, &usLength);

    // 执行检查
    EXPECT_EQ((TAF_UINT32)AT_OK, ulRet);
    EXPECT_EQ(strlen(pcExpectStr), usLength);
    ASSERT_STREQ(pcExpectStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


class Test_At_SsRspInterrogateCnfCcwaProc: public ::testing::Test
{
public:
    VOS_UINT8                               ucIndex;
    AT_PAR_CMD_ELEMENT_STRU                 stCmdInfo;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU      stEvent;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_CCWA;
        stCmdInfo.pfnSetProc        = At_SetCcwaPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = At_QryCcwaPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = At_TestCcwaPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnAbortProc      = VOS_NULL_PTR;
        stCmdInfo.ulAbortTimeOut    = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_LIMITED_NULL;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"+CCWA";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1),(0-2),(1-255)";

        PS_MEM_SET(&stEvent, 0, sizeof(stEvent));

        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCWA_QUERY;
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_SsRspInterrogateCnfCcwaProc, Test_At_SsRspInterrogateCnfCcwaProc_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr = "+CCWA: 0,255,2";
    usLength = 0;
    stEvent.OP_SsStatus = VOS_TRUE;
    stEvent.SsStatus    = TAF_SS_REGISTERED_STATUS_MASK;

    // 初始化全局变量
    g_stAtSsCustomizePara.ucStatus          = VOS_TRUE;
    g_stAtSsCustomizePara.ucSsCmdCustomize  = 0x01;

    // MOCKER操作

    // 调用被测函数
    At_SsRspInterrogateCnfCcwaProc(ucIndex, &stEvent, &ulRet, &usLength);

    // 执行检查
    EXPECT_EQ((TAF_UINT32)AT_OK, ulRet);
    EXPECT_EQ(strlen(pcExpectStr), usLength);
    ASSERT_STREQ(pcExpectStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SsRspInterrogateCnfCcwaProc, Test_At_SsRspInterrogateCnfCcwaProc_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    VOS_CHAR                           *pcExpectStr;

    // 参数初始化
    pcExpectStr = "+CCWA: 0";
    usLength = 0;
    stEvent.OP_SsStatus = VOS_FALSE;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    At_SsRspInterrogateCnfCcwaProc(ucIndex, &stEvent, &ulRet, &usLength);

    // 执行检查
    EXPECT_EQ((VOS_UINT32)AT_OK, ulRet);
    EXPECT_EQ(strlen(pcExpectStr), usLength);
    ASSERT_STREQ(pcExpectStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvMnCallChannelInfoInd, Test_AT_RcvMnCallChannelInfoInd_006)
{
    MN_AT_IND_EVT_STRU                 *pstEvent;
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;
    VOS_CHAR                            aucDataAt[30] = "\r\n^CSCHANNELINFO: 0,1\r\n";

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_AT_IND_EVT_STRU)+sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));
    if (TAF_NULL_PTR == pstEvent)
    {
        return;
    }

    pstEvent->ulSenderPid       = I0_WUEPS_PID_TAF;
    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->usMsgName         = MN_CALLBACK_CS_CALL;
    pstEvent->usLen             = sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU);

    stChannelEvt.enEvent                                  = MN_CALL_EVT_CHANNEL_INFO_IND;
    stChannelEvt.usClientId                               = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stChannelEvt.enCodecType                              = MN_CALL_CODEC_TYPE_AMR;
    stChannelEvt.ucIsLocalAlertingFlag                    = VOS_TRUE;
    stChannelEvt.enVoiceDomain                            = TAF_CALL_VOICE_DOMAIN_IMS;

    PS_MEM_CPY(pstEvent->aucContent, &stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    At_MsgProc((MsgBlock*)pstEvent);

    PS_MEM_FREE(WUEPS_PID_TAF, pstEvent);

    EXPECT_STREQ((VOS_CHAR*)aucDataAt, (VOS_CHAR*)(pgucAtSndCodeAddr));
    GlobalMockObject::verify();
}



class Test_AT_RcvTafCallStartDtmfCnf: public ::testing::Test
{
public:
    MN_AT_IND_EVT_STRU                 *pstData;
    MN_CALL_EVENT_ENUM_U32             *penEventType;
    TAF_CALL_EVT_DTMF_CNF_STRU         *pstDtmfCnf;
    VOS_UINT16                          usLength;

    void SetUp()
    {
        UT_STUB_INIT();
        /* 申请消息，并初始化 */
        usLength        = sizeof(MN_AT_IND_EVT_STRU) + sizeof(TAF_CALL_EVT_DTMF_CNF_STRU);
        pstData         = (MN_AT_IND_EVT_STRU *)malloc(usLength);
        memset(pstData, 0, usLength);

        penEventType    = (MN_CALL_EVENT_ENUM_U32 *)pstData->aucContent;
        pstDtmfCnf      = (TAF_CALL_EVT_DTMF_CNF_STRU *)(pstData->aucContent
                                                       + sizeof(MN_CALL_EVENT_ENUM_U32));

        pstData->clientId   = 1;
        pstData->usLen      = sizeof(TAF_CALL_EVT_DTMF_CNF_STRU) + sizeof(MN_CALL_EVENT_ENUM_U32);
        pstData->usMsgName  = MN_CALLBACK_CS_CALL;

        *penEventType       = MN_CALL_EVT_START_DTMF_CNF;

        pstDtmfCnf->callId  = 1;
        pstDtmfCnf->enCause = TAF_CS_CAUSE_SUCCESS;
        pstDtmfCnf->usClientId  = 1;
        pstDtmfCnf->enDtmfState = TAF_CALL_DTMF_WAIT_START_CNF;
        pstDtmfCnf->ucDtmfCnt   = 1;

    }
    void TearDown()
    {
        free(pstData);
    }
};


TEST_F(Test_AT_RcvTafCallStartDtmfCnf, Test_AT_RcvTafCallStartDtmfCnf_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CLIENT_ID_T                      usClient;

    // 参数初始化
    ucIndex     = 0;
    usClient    = 1;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(usClient), any())
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(0));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    At_CsMsgProc(pstData, usLength);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafCallStartDtmfCnf, Test_AT_RcvTafCallStartDtmfCnf_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CLIENT_ID_T                      usClient;

    // 参数初始化
    ucIndex     = 1;
    usClient    = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHUP_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(usClient), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(DIAG_LogReport)
        .expects(exactly(0));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    At_CsMsgProc(pstData, usLength);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafCallStartDtmfCnf, Test_AT_RcvTafCallStartDtmfCnf_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CLIENT_ID_T                      usClient;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = 1;
    usClient    = 1;
    ulResult    = AT_OK;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VTS_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(usClient), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(DIAG_LogReport)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    // 调用被测函数
    At_CsMsgProc(pstData, usLength);

    // 执行检查
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus, (VOS_UINT8)AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafCallStartDtmfCnf, Test_AT_RcvTafCallStartDtmfCnf_004)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CLIENT_ID_T                      usClient;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = 1;
    usClient    = 1;
    ulResult    = AT_ERROR;
    pstDtmfCnf->enCause = TAF_CS_CAUSE_UNKNOWN;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DTMF_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(usClient), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(DIAG_LogReport)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    // 调用被测函数
    At_CsMsgProc(pstData, usLength);

    // 执行检查
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus, (VOS_UINT8)AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT);

    GlobalMockObject::verify();
}


class Test_At_RcvMmaPsInitResultIndProc: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        //初始化用户输出缓存
        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));
    }

    void TearDown()
    {

    }
};



TEST_F(Test_At_RcvMmaPsInitResultIndProc, Test_At_RcvMmaPsInitResultIndProc_001)
{
    VOS_CHAR                           *pcPrintStr = "\r\n^PSINIT: 1\r\n";
    TAF_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU           stEvent;

    //参数初始化
    ucIndex                 = 0;
    stEvent.OP_PsInitRslt   = VOS_TRUE;
    stEvent.ulPsInitRslt    = VOS_TRUE;
    stEvent.PhoneEvent      = TAF_MMA_EVT_PS_INIT_RESULT_IND;

    /* 打桩函数 */
    MOCKER(BSP_Modem_OS_Status_Switch)
        .expects(exactly(1))
        .will(returnValue(1));

    /* 调用测试函数 */
    At_PhIndProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    /* 检查 */
    ASSERT_STREQ(pcPrintStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    // 执行检查
    GlobalMockObject::verify();
}


TEST_F(Test_At_RcvMmaPsInitResultIndProc, Test_At_RcvMmaPsInitResultIndProc_002)
{
    VOS_CHAR                           *pcPrintStr = "\r\n^PSINIT: 0\r\n";
    TAF_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU           stEvent;

    //参数初始化
    ucIndex                 = 0;
    stEvent.OP_PsInitRslt   = VOS_TRUE;
    stEvent.ulPsInitRslt    = VOS_FALSE;
    stEvent.PhoneEvent      = TAF_MMA_EVT_PS_INIT_RESULT_IND;

    /* 打桩函数 */
    MOCKER(BSP_Modem_OS_Status_Switch)
        .expects(never());

    /* 调用测试函数 */
    At_RcvMmaPsInitResultIndProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    /* 检查 */
    ASSERT_STREQ(pcPrintStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    // 执行检查
    GlobalMockObject::verify();
}



TEST_F(Test_At_RcvMmaPsInitResultIndProc, Test_At_RcvMmaPsInitResultIndProc_003)
{
    VOS_CHAR                           *pcPrintStr = "^PSINIT: 1\r\n\r\nOK\r\n";
    TAF_UINT8                           ucIndex;
    TAF_PHONE_EVENT_INFO_STRU           stEvent;

    //参数初始化
    ucIndex                 = 0;
    stEvent.OP_PsInitRslt   = VOS_FALSE;
    stEvent.ulPsInitRslt    = VOS_TRUE;
    stEvent.PhoneEvent      = TAF_MMA_EVT_PS_INIT_RESULT_IND;

    /* 打桩函数 */
    MOCKER(BSP_Modem_OS_Status_Switch)
        .expects(never());

    /* 调用测试函数 */
    At_RcvMmaPsInitResultIndProc(ucIndex, (TAF_PHONE_EVENT_INFO_STRU *)&stEvent);

    /* 检查 */

    // 执行检查
    GlobalMockObject::verify();
}




class Test_AT_RcvTafCallStopDtmfCnf: public ::testing::Test
{
public:
    MN_AT_IND_EVT_STRU                 *pstData;
    MN_CALL_EVENT_ENUM_U32             *penEventType;
    TAF_CALL_EVT_DTMF_CNF_STRU         *pstDtmfCnf;
    VOS_UINT16                          usLength;

    void SetUp()
    {
        UT_STUB_INIT();
        /* 申请消息，并初始化 */
        usLength        = sizeof(MN_AT_IND_EVT_STRU) + sizeof(TAF_CALL_EVT_DTMF_CNF_STRU);
        pstData         = (MN_AT_IND_EVT_STRU *)malloc(usLength);
        memset(pstData, 0, usLength);

        penEventType    = (MN_CALL_EVENT_ENUM_U32 *)pstData->aucContent;
        pstDtmfCnf      = (TAF_CALL_EVT_DTMF_CNF_STRU *)(pstData->aucContent
                                                       + sizeof(MN_CALL_EVENT_ENUM_U32));

        pstData->clientId   = 1;
        pstData->usLen      = sizeof(TAF_CALL_EVT_DTMF_CNF_STRU) + sizeof(MN_CALL_EVENT_ENUM_U32);
        pstData->usMsgName  = MN_CALLBACK_CS_CALL;

        *penEventType       = MN_CALL_EVT_STOP_DTMF_CNF;

        pstDtmfCnf->callId  = 1;
        pstDtmfCnf->enCause = TAF_CS_CAUSE_SUCCESS;
        pstDtmfCnf->usClientId  = 1;
        pstDtmfCnf->enDtmfState = TAF_CALL_DTMF_WAIT_STOP_CNF;
        pstDtmfCnf->ucDtmfCnt   = 1;

    }
    void TearDown()
    {
        free(pstData);
    }
};


TEST_F(Test_AT_RcvTafCallStopDtmfCnf, Test_AT_RcvTafCallStopDtmfCnf_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CLIENT_ID_T                      usClient;

    // 参数初始化
    ucIndex     = 0;
    usClient    = 1;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(usClient), any())
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(DIAG_LogReport)
        .expects(exactly(0));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    At_CsMsgProc(pstData, usLength);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafCallStopDtmfCnf, Test_AT_RcvTafCallStopDtmfCnf_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CLIENT_ID_T                      usClient;

    // 参数初始化
    ucIndex     = 1;
    usClient    = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHUP_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(usClient), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(DIAG_LogReport)
        .expects(exactly(0));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    At_CsMsgProc(pstData, usLength);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafCallStopDtmfCnf, Test_AT_RcvTafCallStopDtmfCnf_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CLIENT_ID_T                      usClient;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = 1;
    usClient    = 1;
    ulResult    = AT_OK;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DTMF_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(usClient), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(DIAG_LogReport)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    // 调用被测函数
    At_CsMsgProc(pstData, usLength);

    // 执行检查
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus, (VOS_UINT8)AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTafCallStopDtmfCnf, Test_AT_RcvTafCallStopDtmfCnf_004)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    MN_CLIENT_ID_T                      usClient;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = 1;
    usClient    = 1;
    ulResult    = AT_ERROR;
    pstDtmfCnf->enCause = TAF_CS_CAUSE_UNKNOWN;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DTMF_SET;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(eq(usClient), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(DIAG_LogReport)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ulResult));

    // 调用被测函数
    At_CsMsgProc(pstData, usLength);

    // 执行检查
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus, (VOS_UINT8)AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_CURRENT_OPT_BUTT);

    GlobalMockObject::verify();
}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_026)
{
    /* 变量定义 */


    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_START_DTMF_RSLT;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CsMsgProc,Test_At_CsMsgProc_027)
{
    /* 变量定义 */


    /* 变量初始化 */
    pstEvent->enEvent         = MN_CALL_EVT_STOP_DTMF_RSLT;
    pstEvent->ulRet           = TAF_ERR_NO_ERROR;

    /* 函数打桩 */

    /* 调用被测函数 */
    At_CsMsgProc(pRcvMsg,ulMsgLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}




class Test_At_SmsDeliverErrProc: public ::testing::Test
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


TEST_F(Test_At_SmsDeliverErrProc, Test_At_SmsDeliverErrProc_001)
{
    // 变量声明
    AT_MODEM_SMS_CTX_STRU               stSmsCtx;
    VOS_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_UINT8                           ucModemIndex;

    //参数初始化
    ucIndex      = 0;
    ucModemIndex = 0;

    stEvent.u.stDeliverErrInfo.enErrorCode = TAF_MSG_ERROR_TR2M_TIMEOUT;

    // 初始化全局变量
    memset(&g_astAtModemCtx, 0, sizeof(g_astAtModemCtx));
    g_astAtModemCtx[ucModemIndex].stSmsCtx.ucLocalStoreFlg = VOS_FALSE;

    g_astAtModemCtx[ucModemIndex].stSmsCtx.stCnmiType.CnmiMtType = AT_CNMI_MT_CMT_TYPE;
    g_astAtModemCtx[ucModemIndex].stSmsCtx.stCnmiType.CnmiDsType = AT_CNMI_DS_CDS_TYPE;

    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId    = ucModemIndex;

    // MOCKER操作;

    // 调用被测函数
    At_SmsDeliverErrProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(g_astAtModemCtx[ucIndex].stSmsCtx.stCnmiType.CnmiMtType, AT_CNMI_MT_CMT_TYPE);
    EXPECT_EQ(g_astAtModemCtx[ucIndex].stSmsCtx.stCnmiType.CnmiDsType, AT_CNMI_DS_CDS_TYPE);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsDeliverErrProc, Test_At_SmsDeliverErrProc_002)
{
    // 变量声明
    AT_MODEM_SMS_CTX_STRU               stSmsCtx;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucModemIndex;
    MN_MSG_EVENT_INFO_STRU              stEvent;

    //参数初始化
    ucIndex      = 0;
    ucModemIndex = 0;

    stEvent.u.stDeliverErrInfo.enErrorCode = TAF_MSG_ERROR_TR2M_TIMEOUT;

    // 初始化全局变量
    memset(&g_astAtModemCtx, 0, sizeof(g_astAtModemCtx));
    g_astAtModemCtx[ucModemIndex].stSmsCtx.ucLocalStoreFlg = VOS_TRUE;

    g_astAtModemCtx[ucModemIndex].stSmsCtx.stCnmiType.CnmiMtType = AT_CNMI_MT_CMT_TYPE;
    g_astAtModemCtx[ucModemIndex].stSmsCtx.stCnmiType.CnmiDsType = AT_CNMI_DS_CDS_TYPE;

    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId    = ucModemIndex;

    // MOCKER操作;

    // 调用被测函数
    At_SmsDeliverErrProc(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(g_astAtModemCtx[ucIndex].stSmsCtx.stCnmiType.CnmiMtType, AT_CNMI_MT_NO_SEND_TYPE);
    EXPECT_EQ(g_astAtModemCtx[ucIndex].stSmsCtx.stCnmiType.CnmiDsType, AT_CNMI_DS_NO_SEND_TYPE);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsDeliverErrProc, Test_At_SmsDeliverErrProc_003)
{
    // 变量声明
    AT_MODEM_SMS_CTX_STRU               stSmsCtx;
    VOS_UINT8                           ucIndex;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    VOS_UINT8                           ucModemIndex;

    //参数初始化
    ucIndex      = 0;
    ucModemIndex = 0;

    stEvent.u.stDeliverErrInfo.enErrorCode = TAF_MSG_ERROR_NO_SERVICE;

    // 初始化全局变量
    memset(&g_astAtModemCtx, 0, sizeof(g_astAtModemCtx));
    g_astAtModemCtx[ucModemIndex].stSmsCtx.ucLocalStoreFlg = VOS_TRUE;

    g_astAtModemCtx[ucModemIndex].stSmsCtx.stCnmiType.CnmiMtType = AT_CNMI_MT_CMT_TYPE;
    g_astAtModemCtx[ucModemIndex].stSmsCtx.stCnmiType.CnmiDsType = AT_CNMI_DS_CDS_TYPE;

    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId    = ucModemIndex;

    // MOCKER操作;

    // 调用被测函数
    At_SmsDeliverErrProc(ucIndex, (MN_MSG_EVENT_INFO_STRU *)&stEvent);

    // 执行检查
    EXPECT_EQ(g_astAtModemCtx[ucIndex].stSmsCtx.stCnmiType.CnmiMtType, (AT_CNMI_MT_TYPE)AT_CNMI_MT_CMT_TYPE);
    EXPECT_EQ(g_astAtModemCtx[ucIndex].stSmsCtx.stCnmiType.CnmiDsType, (AT_CNMI_DS_TYPE)AT_CNMI_DS_CDS_TYPE);

    GlobalMockObject::verify();
}


class Test_At_QryParaRspPnnProc: public ::testing::Test
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


TEST_F(Test_At_QryParaRspPnnProc, Test_At_QryParaRspPnnProc_001)
{
    // 变量声明
    TAF_PH_USIM_PNN_CNF_STRU   *pstPNN = VOS_NULL_PTR;
    VOS_UINT32  ulTotalNum;
    VOS_UINT16  usEfLen;
    TAF_PH_ICC_TYPE                     Icctype;

    TAF_UINT8                           ucIndex;
    TAF_UINT8                           OpId;

    //参数初始化
    ulTotalNum = 50;
    usEfLen = 80;

    Icctype = TAF_PH_ICC_SIM;

    ucIndex = 1;

    OpId = 1;

    pstPNN = (TAF_PH_USIM_PNN_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT,
                  sizeof(TAF_PH_USIM_PNN_CNF_STRU)+(sizeof(TAF_PH_USIM_PNN_RECORD)*ulTotalNum));

    memset(pstPNN, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU)+(sizeof(TAF_PH_USIM_PNN_RECORD)*ulTotalNum));

    pstPNN->RecordLen = usEfLen;
    pstPNN->TotalRecordNum = ulTotalNum;
    pstPNN->usPnnCurrIndex = 0;
    pstPNN->Icctype = TAF_PH_ICC_SIM;

    for(int i=0;i<ulTotalNum;i++)
    {
        for(int j=0;j<usEfLen;j++)
        {
            pstPNN->PNNRecord[i].PNN[j] = i+1;
        }
    }

    // 初始化全局变量

    // MOCKER操作;
    MOCKER(MN_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_QryParaRspPnnProc(ucIndex, OpId, pstPNN);

    // 执行检查
    PS_MEM_FREE(WUEPS_PID_AT,pstPNN);
    GlobalMockObject::verify();
}


TEST_F(Test_At_QryParaRspPnnProc, Test_At_QryParaRspPnnProc_002)
{
    // 变量声明
    TAF_PH_USIM_PNN_CNF_STRU   *pstPNN = VOS_NULL_PTR;
    VOS_UINT32  ulTotalNum;
    VOS_UINT16  usEfLen;
    TAF_PH_ICC_TYPE                     Icctype;

     AT_PAR_CMD_ELEMENT_STRU  stCmdElement;

    TAF_UINT8                           ucIndex;
    TAF_UINT8                           OpId;

    //参数初始化
    ulTotalNum = 0;
    usEfLen = 80;

    VOS_UINT8 name = 44;

    stCmdElement.pszCmdName = &name;
    g_stParseContext[0].pstCmdElement = &stCmdElement;

    Icctype = TAF_PH_ICC_SIM;

    ucIndex = 0;

    OpId = 1;

    pstPNN = (TAF_PH_USIM_PNN_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT,
                  sizeof(TAF_PH_USIM_PNN_CNF_STRU)+(sizeof(TAF_PH_USIM_PNN_RECORD)*ulTotalNum));

    memset(pstPNN, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU)+(sizeof(TAF_PH_USIM_PNN_RECORD)*ulTotalNum));

    pstPNN->RecordLen = usEfLen;
    pstPNN->TotalRecordNum = ulTotalNum;
    pstPNN->usPnnCurrIndex = 0;
    pstPNN->Icctype = TAF_PH_ICC_SIM;

    for(int i=0;i<ulTotalNum;i++)
    {
        for(int j=0;j<usEfLen;j++)
        {
            pstPNN->PNNRecord[i].PNN[j] = i+1;
        }
    }
    pstPNN->PNNRecord[0].PNN[0] = FULL_NAME_IEI;
    // 初始化全局变量

    // MOCKER操作;
    MOCKER(At_BufferorSendResultData)
        .expects(exactly(0));

    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));


    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_QryParaRspPnnProc(ucIndex, OpId, pstPNN);

    // 执行检查
    PS_MEM_FREE(WUEPS_PID_AT,pstPNN);
    GlobalMockObject::verify();
}



class Test_AT_PhEOPlmnQueryCnfProc: public ::testing::Test
{
public:
    VOS_UINT16                                              usLength;
    TAF_PHONE_EVENT_EOPLMN_QRY_CNF_STRU                    *pstEOPlmnQryCnf;

    void SetUp()
    {
        UT_STUB_INIT();
        /* 申请消息，并初始化 */
        usLength        = sizeof(TAF_PHONE_EVENT_EOPLMN_QRY_CNF_STRU);
        pstEOPlmnQryCnf = (TAF_PHONE_EVENT_EOPLMN_QRY_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, usLength);
        PS_MEM_SET(pstEOPlmnQryCnf, 0, usLength);
    }
    void TearDown()
    {
        if (VOS_NULL_PTR != pstEOPlmnQryCnf)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstEOPlmnQryCnf);
        }
    }
};


TEST_F(Test_AT_PhEOPlmnQueryCnfProc, Test_AT_PhEOPlmnQueryCnfProc_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_PhEOPlmnQueryCnfProc((TAF_UINT8 *)pstEOPlmnQryCnf);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PhEOPlmnQueryCnfProc, Test_AT_PhEOPlmnQueryCnfProc_002)
{
    // 变量声明
    VOS_UINT8       ucIndex;

    // 参数初始化
    ucIndex                   = 1;
    pstEOPlmnQryCnf->ClientId = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_PhEOPlmnQueryCnfProc((TAF_UINT8 *)pstEOPlmnQryCnf);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PhEOPlmnQueryCnfProc, Test_AT_PhEOPlmnQueryCnfProc_003)
{
    // 变量声明
    VOS_UINT8       ucIndex;

    // 参数初始化
    ucIndex                                = 1;
    pstEOPlmnQryCnf->ClientId              = 1;
    pstEOPlmnQryCnf->ulResult              = TAF_ERR_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EOPLMN_QRY;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    AT_PhEOPlmnQueryCnfProc((TAF_UINT8 *)pstEOPlmnQryCnf);

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PhEOPlmnQueryCnfProc, Test_AT_PhEOPlmnQueryCnfProc_004)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    VOS_UINT8                           szCmdName[32];

    // 参数初始化
    ucIndex                                = 1;
    pstEOPlmnQryCnf->ClientId              = 1;
    pstEOPlmnQryCnf->ulResult              = TAF_ERR_NO_ERROR;
    pstEOPlmnQryCnf->usOPlmnNum            = 1;
    pstEOPlmnQryCnf->aucOPlmnList[0]       = 0X64;
    pstEOPlmnQryCnf->aucOPlmnList[1]       = 0XF0;
    pstEOPlmnQryCnf->aucOPlmnList[2]       = 0X30;
    pstEOPlmnQryCnf->aucOPlmnList[3]       = 0X08;
    pstEOPlmnQryCnf->aucOPlmnList[4]       = 0X08;

    VOS_StrCpy((VOS_CHAR*)pstEOPlmnQryCnf->aucVersion, "1.20");

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt                = AT_CMD_EOPLMN_QRY;

    VOS_StrCpy((VOS_CHAR*)szCmdName,"^EOPLMN");
    g_stParseContext[ucIndex].pstCmdElement               = &stElement;
    stElement.pszCmdName                                  = szCmdName;
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName   = (VOS_UINT8*)"^EOPLMN";
    g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex   = AT_CMD_EOPLMN;
    g_stParseContext[ucIndex].stCombineCmdInfo.usTotalNum = 0 ;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    AT_PhEOPlmnQueryCnfProc((TAF_UINT8 *)pstEOPlmnQryCnf);

    // 执行检查

    GlobalMockObject::verify();
}



#if (FEATURE_ON == FEATURE_IMS)

class Test_At_ProcQryClccResult: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                         = 0;
        gstAtSendData.usBufLen          = 0;
    }

    void TearDown()
    {
        gstAtSendData.usBufLen          = 0;
    }
};


TEST_F(Test_At_ProcQryClccResult,Test_At_ProcQryClccResult_001)
{
   // 参数定义
    VOS_UINT8                                   ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU                   stCallInfos = {0};
    VOS_UINT8                                   aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1] = "15002107919";
    AT_CLCC_MODE_ENUM_U8                        enClccMode;
    VOS_UINT32                                  ulLen;
    char                                        acExpectedResult[] = "^CLCC: 0,0,0,0,0,0,\"15002107919\",128,\"\",\r\n^CLCC: 0,0,0,0,0,1,\"15002107919\",128,\"\",";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CLCC_IMS,
        VOS_NULL_PTR,      AT_NOT_SET_TIME, AT_QryClccPara,     AT_QRY_PARA_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"^CLCC", VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 2;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MO;
    stCallInfos.astCallInfos[0].stConnectNumber.ucNumLen = 1;
    stCallInfos.astCallInfos[0].enVoiceDomain   = TAF_CALL_VOICE_DOMAIN_3GPP;
    stCallInfos.astCallInfos[1].enCallDir       = MN_CALL_DIR_MO;
    stCallInfos.astCallInfos[1].stConnectNumber.ucNumLen = 1;
    stCallInfos.astCallInfos[1].enVoiceDomain   = TAF_CALL_VOICE_DOMAIN_IMS;

    stCallInfos.astCallInfos[0].stCallNumber.ucNumLen    = 0;

    enClccMode                                  = 0;

    ulLen                                       = 12;
    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(2))
        .with(any(),outBoundP((VOS_UINT8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    MOCKER(AT_BcdNumberToAscii)
    .expects(exactly(2))
    .with(any(),any(), outBoundP((VOS_CHAR *)aucAsciiNum, ulLen))
    .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    At_ProcQryClccResult(ucNumOfCalls, (MN_CALL_INFO_QRY_CNF_STRU *)&stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_ProcQryClccResult,Test_At_ProcQryClccResult_002)
{
   // 参数定义
    VOS_UINT8                                   ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU                   stCallInfos = {0};
    VOS_UINT8                                   aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1] = "15002107919";
    AT_CLCC_MODE_ENUM_U8                        enClccMode;
    VOS_UINT32                                  ulLen;
    char                                        acExpectedResult[] = "^CLCC: 0,0,0,0,0,0,\"15002107919\",128,\"\",";
    AT_PAR_CMD_ELEMENT_STRU                     stCmdInfo = {AT_CMD_CLCC_IMS,
        VOS_NULL_PTR,      AT_NOT_SET_TIME, AT_QryClccPara,     AT_QRY_PARA_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"^CLCC", VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 1;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MO;
    stCallInfos.astCallInfos[0].stConnectNumber.ucNumLen = 0;
    stCallInfos.astCallInfos[0].stCalledNumber.ucNumLen  = 1;

    enClccMode                                  = 0;

    ulLen                                       = 12;

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(1))
        .with(any(),outBoundP((VOS_UINT8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    MOCKER(AT_BcdNumberToAscii)
    .expects(exactly(1))
    .with(any(),any(), outBoundP((VOS_CHAR *)aucAsciiNum, ulLen))
    .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));


    // 调用被测函数
    At_ProcQryClccResult(ucNumOfCalls, (MN_CALL_INFO_QRY_CNF_STRU *)&stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_ProcQryClccResult,Test_At_ProcQryClccResult_003)
{
   // 参数定义
    VOS_UINT8                           ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU           stCallInfos = {0};
    AT_CLCC_MODE_ENUM_U8                enClccMode;
    VOS_UINT32                          ulLen;
    char                                acExpectedResult[] = "^CLCC: 0,0,0,0,0,0,\"\",128";
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CLCC_IMS,
        VOS_NULL_PTR,      AT_NOT_SET_TIME, AT_QryClccPara,     AT_QRY_PARA_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"^CLCC", VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 1;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MO;
    stCallInfos.astCallInfos[0].stConnectNumber.ucNumLen = 0;
    stCallInfos.astCallInfos[0].stCallNumber.ucNumLen    = 0;

    enClccMode                                  = 0;

    ulLen                                       = 12;

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(1))
        .with(any(),outBoundP((VOS_UINT8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    // 调用被测函数
    At_ProcQryClccResult(ucNumOfCalls, (MN_CALL_INFO_QRY_CNF_STRU *)&stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_ProcQryClccResult,Test_At_ProcQryClccResult_004)
{
   // 参数定义
    VOS_UINT8                           ucNumOfCalls;
    MN_CALL_INFO_QRY_CNF_STRU           stCallInfos = {0};
    VOS_UINT8                           aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1] = "15002107919";
    AT_CLCC_MODE_ENUM_U8                enClccMode;
    VOS_UINT32                          ulLen;
    char                                acExpectedResult[] = "^CLCC: 0,1,0,0,0,0,\"15002107919\",128,\"\",";
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CLCC_IMS,
        VOS_NULL_PTR,      AT_NOT_SET_TIME, AT_QryClccPara,     AT_QRY_PARA_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"^CLCC", VOS_NULL_PTR};

    // 参数初始化
    ucNumOfCalls                                = 1;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MT;
    stCallInfos.astCallInfos[0].stCallNumber.ucNumLen    = 1;

    enClccMode                                  = 0;

    ulLen                                       = 12;
    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(1))
        .with(any(),outBoundP((VOS_UINT8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    MOCKER(AT_BcdNumberToAscii)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((VOS_CHAR *)aucAsciiNum, ulLen))
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    At_ProcQryClccResult(ucNumOfCalls, (MN_CALL_INFO_QRY_CNF_STRU *)&stCallInfos, ucIndex);

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_ProcQryClccResult,Test_At_ProcQryClccResult_005)
{
   // 参数定义
    MN_CALL_INFO_QRY_CNF_STRU           stCallInfos = {0};
    AT_CLCC_MODE_ENUM_U8                enClccMode;
    char                                acExpectedResult[] = "^CLCC: 0,1,0,0,0,1,\"\",128";
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo = {AT_CMD_CLCC_IMS,
        VOS_NULL_PTR,      AT_NOT_SET_TIME, AT_QryClccPara,     AT_QRY_PARA_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"^CLCC", VOS_NULL_PTR};

    MN_AT_IND_EVT_STRU                 *pstData;

    // 参数初始化
    stCallInfos.clientId                        = ucIndex;
    stCallInfos.ucNumOfCalls                    = 1;
    stCallInfos.astCallInfos[0].enCallDir       = MN_CALL_DIR_MT;
    stCallInfos.astCallInfos[0].stCallNumber.ucNumLen    = 0;
    stCallInfos.astCallInfos[0].enVoiceDomain   = 1;

    enClccMode                                  = 0;

    pstData = (MN_AT_IND_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_AT_IND_EVT_STRU) + sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstData)
    {
        return;
    }
    PS_MEM_SET(pstData, 0, sizeof(MN_AT_IND_EVT_STRU));
    PS_MEM_CPY(pstData->aucContent, &stCallInfos, sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    // 相关全局变量初始化
    g_stParseContext[ucIndex].pstCmdElement     = &stCmdInfo;
    gastAtClientTab[ucIndex].CmdCurrentOpt      = AT_CMD_CLCC_QRY;
    gastAtClientTab[ucIndex].ucUsed             = AT_CLIENT_USED;

    // MOCKER操作;

    MOCKER(AT_MapCallTypeModeToClccMode)
        .expects(exactly(1))
        .with(any(),outBoundP((VOS_UINT8 *)&enClccMode, (VOS_UINT32)sizeof(enClccMode)));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    At_CsAllCallInfoEvtCnfProc(pstData, sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    // 执行检查
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#endif



class Test_AT_IsClientBlock: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPortBuffCfg();
    }
    void TearDown()
    {
        AT_InitPortBuffCfg();
    }
};


TEST_F(Test_AT_IsClientBlock, Test_AT_IsClientBlock_001)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->enSmsBuffCfg = AT_PORT_BUFF_DISABLE;

    EXPECT_EQ((VOS_UINT32)VOS_FALSE, AT_IsClientBlock());

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsClientBlock, Test_AT_IsClientBlock_002)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->enSmsBuffCfg = AT_PORT_BUFF_ENABLE;

    MOCKER(AT_IsAnyParseClientPend)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    EXPECT_EQ((VOS_UINT32)VOS_TRUE, AT_IsClientBlock());

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsClientBlock, Test_AT_IsClientBlock_003)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->enSmsBuffCfg = AT_PORT_BUFF_ENABLE;

    MOCKER(AT_IsAnyParseClientPend)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_IsAllClientDataMode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    EXPECT_EQ((VOS_UINT32)VOS_TRUE, AT_IsClientBlock());

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsClientBlock, Test_AT_IsClientBlock_004)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->enSmsBuffCfg = AT_PORT_BUFF_ENABLE;

    MOCKER(AT_IsAnyParseClientPend)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_IsAllClientDataMode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    EXPECT_EQ((VOS_UINT32)VOS_FALSE, AT_IsClientBlock());

    GlobalMockObject::verify();
}


class Test_AT_FlushSmsIndication: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPortBuffCfg();

    }
    void TearDown()
    {
        AT_InitPortBuffCfg();
    }
};


TEST_F(Test_AT_FlushSmsIndication, Test_AT_FlushSmsIndication_001)
{
    VOS_UINT16                          usClientId;
    VOS_UINT32                          i;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(MODEM_ID_0);

    pstSmsCtx->stCnmiType.CnmiBfrType = AT_CNMI_BFR_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiModeType = AT_CNMI_MODE_SEND_OR_BUFFER_TYPE;

    for (i = 0; i < AT_BUFFER_SMT_EVENT_MAX; i++)
    {
        pstSmsCtx->stSmtBuffer.aucUsed[i] = AT_MSG_BUFFER_USED;
    }

    MOCKER(At_ForwardMsgToTe)
        .expects(exactly(5));

    for (usClientId = 0; usClientId < AT_MAX_CLIENT_NUM; usClientId++)
    {
        AT_AddUsedClientId2Tab(usClientId);
    }

    AT_FlushSmsIndication();

    GlobalMockObject::verify();

}


TEST_F(Test_AT_FlushSmsIndication, Test_AT_FlushSmsIndication_002)
{
    VOS_UINT16                          usClientId;
    VOS_UINT32                          i;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(MODEM_ID_0);
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstSmsCtx->stCnmiType.CnmiBfrType = AT_CNMI_BFR_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiModeType = AT_CNMI_MODE_SEND_OR_BUFFER_TYPE;

    for (i = 0; i < AT_BUFFER_SMT_EVENT_MAX; i++)
    {
        pstSmsCtx->stSmtBuffer.aucUsed[i] = AT_MSG_BUFFER_USED;
    }

    MOCKER(At_ForwardMsgToTe)
        .expects(exactly(5));

    for (usClientId = 0; usClientId < AT_MAX_CLIENT_NUM; usClientId++)
    {
        AT_AddUsedClientId2Tab(usClientId);
    }

    pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM + 1;

    AT_FlushSmsIndication();

    GlobalMockObject::verify();

}

