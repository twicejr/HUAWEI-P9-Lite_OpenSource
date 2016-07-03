#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "ATCmdProc.h"
#include "AtCmdImsProc.h"

using namespace testing;


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_IMS_PROC_C

extern TAF_VOID At_MsgProc(MsgBlock* pMsg);

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)

class Test_AT_ProcImsaMsg: public ::testing::Test
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

TEST_F(Test_AT_ProcImsaMsg, AT_ProcImsaMsg_001)
{
    // 变量声明
    AT_IMSA_MSG_STRU                    stImsaMsg;

    // 参数初始化
    PS_MEM_SET(&stImsaMsg, 0, sizeof(AT_IMSA_MSG_STRU));
    stImsaMsg.ulSenderPid   = PS_PID_IMSA;
    stImsaMsg.ulMsgId       = ID_AT_IMSA_MSG_BUTT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    At_MsgProc((MsgBlock *)&stImsaMsg);

    // 执行检查
    GlobalMockObject::verify();
}


class Test_AT_RcvImsaCiregSetCnf: public ::testing::Test
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

TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = 0;
    stCiregCnf.ulResult                 = VOS_OK;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulRslt = AT_RcvImsaCiregSetCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_003)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CURRENT_OPT_BUTT;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulRslt = AT_RcvImsaCiregSetCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_004)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    ulRslt                              = AT_OK;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREG_SET;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ulRslt));

    // 调用被测函数
    ulRslt = AT_RcvImsaCiregSetCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_005)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_ERR;
    ulRslt                              = AT_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREG_SET;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ulRslt));

    // 调用被测函数
    ulRslt = AT_RcvImsaCiregSetCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}


class Test_AT_RcvImsaCirepSetCnf: public ::testing::Test
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

TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = 0;
    stCirepCnf.ulResult                 = VOS_OK;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulRslt = AT_RcvImsaCirepSetCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_003)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CURRENT_OPT_BUTT;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulRslt = AT_RcvImsaCirepSetCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_004)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    ulRslt                              = AT_OK;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREP_SET;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ulRslt));

    // 调用被测函数
    ulRslt = AT_RcvImsaCirepSetCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_005)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_ERR;
    ulRslt                              = AT_ERROR;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREP_SET;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ulRslt));

    // 调用被测函数
    ulRslt = AT_RcvImsaCirepSetCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}


class Test_AT_RcvImsaCiregQryCnf: public ::testing::Test
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

TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));


    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulRslt =  AT_RcvImsaCiregQryCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_003)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CURRENT_OPT_BUTT;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulRslt =  AT_RcvImsaCiregQryCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_004)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;
    VOS_CHAR                            acExpectedStr[] = "+CIREG: 2,1,5";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CIREG,
        AT_SetCiregPara,     AT_SET_PARA_TIME,   AT_QryCiregPara,       AT_QRY_PARA_TIME,   AT_TestCiregPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
        (VOS_UINT8 *)"+CIREG",   (VOS_UINT8 *)"(0-2)"};

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREG_QRY;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRslt =  AT_RcvImsaCiregQryCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_005)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;

    // 参数初始化
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_ERR;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREG_QRY;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRslt =  AT_RcvImsaCiregQryCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}


class Test_AT_RcvImsaCirepQryCnf: public ::testing::Test
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

TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (TAF_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));


    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulRslt =  AT_RcvImsaCirepQryCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_003)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CURRENT_OPT_BUTT;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulRslt =  AT_RcvImsaCirepQryCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_004)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;
    VOS_CHAR                            acExpectedStr[] = "+CIREP: 1,1";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CIREP,
        AT_SetCirepPara,     AT_SET_PARA_TIME,   AT_QryCirepPara,       AT_QRY_PARA_TIME,   AT_TestCirepPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
        (VOS_UINT8 *)"+CIREP",   (VOS_UINT8 *)"(0,1)"};

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREP_QRY;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRslt =  AT_RcvImsaCirepQryCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_005)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;

    // 参数初始化
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_ERR;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // 初始化全局变量
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREP_QRY;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRslt =  AT_RcvImsaCirepQryCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}


class Test_AT_RcvImsaCirephInd: public ::testing::Test
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

TEST_F(Test_AT_RcvImsaCirephInd, Test_AT_RcvImsaCirephInd_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    IMSA_AT_CIREPH_IND_STRU             stCirephInd;

    // 参数初始化
    PS_MEM_SET(&stCirephInd, 0, sizeof(IMSA_AT_CIREPH_IND_STRU));
    stCirephInd.ulMsgId                  = ID_IMSA_AT_CIREPH_IND;
    stCirephInd.usClientId               = ucIndex;
    stCirephInd.enHandover               = AT_IMSA_SRVCC_HANDOVER_SUCCESS;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_SendResultData)
        .expects(never());

    // 调用被测函数
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCirephInd);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirephInd, Test_AT_RcvImsaCirephInd_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREPH_IND_STRU             stCirephInd;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CIREPH: 1\r\n";

    // 参数初始化
    PS_MEM_SET(&stCirephInd, 0, sizeof(IMSA_AT_CIREPH_IND_STRU));
    stCirephInd.ulMsgId                  = ID_IMSA_AT_CIREPH_IND;
    stCirephInd.usClientId               = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stCirephInd.enHandover               = AT_IMSA_SRVCC_HANDOVER_SUCCESS;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)acExpectedStr, sizeof(acExpectedStr) -1), eq(VOS_UINT16(sizeof(acExpectedStr) - 1)));

    // 调用被测函数
    ulRslt = AT_RcvImsaCirephInd((AT_IMSA_MSG_STRU *)&stCirephInd);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


class Test_AT_RcvImsaCirepiInd: public ::testing::Test
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

TEST_F(Test_AT_RcvImsaCirepiInd, Test_AT_RcvImsaCirepiInd_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    IMSA_AT_CIREPI_IND_STRU             stCirepiInd;

    // 参数初始化
    PS_MEM_SET(&stCirepiInd, 0, sizeof(IMSA_AT_CIREPI_IND_STRU));
    stCirepiInd.ulMsgId                 = ID_IMSA_AT_CIREPI_IND;
    stCirepiInd.usClientId              = ucIndex;
    stCirepiInd.enImsvops               = AT_IMSA_NW_SUPORT_IMSVOPS;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_SendResultData)
        .expects(never());

    // 调用被测函数
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCirepiInd);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCirepiInd, Test_AT_RcvImsaCirepiInd_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREPI_IND_STRU             stCirepiInd;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CIREPI: 1\r\n";

    // 参数初始化
    PS_MEM_SET(&stCirepiInd, 0, sizeof(IMSA_AT_CIREPI_IND_STRU));
    stCirepiInd.ulMsgId                 = ID_IMSA_AT_CIREPI_IND;
    stCirepiInd.usClientId              = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stCirepiInd.enImsvops               = AT_IMSA_NW_SUPORT_IMSVOPS;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)acExpectedStr, sizeof(acExpectedStr) -1), eq(VOS_UINT16(sizeof(acExpectedStr) - 1)));

    // 调用被测函数
    ulRslt = AT_RcvImsaCirepiInd((AT_IMSA_MSG_STRU *)&stCirepiInd);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


class Test_AT_RcvImsaCireguInd: public ::testing::Test
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

TEST_F(Test_AT_RcvImsaCireguInd, Test_AT_RcvImsaCireguInd_001)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    IMSA_AT_CIREGU_IND_STRU             stCireguInd;

    // 参数初始化
    PS_MEM_SET(&stCireguInd, 0, sizeof(IMSA_AT_CIREGU_IND_STRU));
    stCireguInd.ulMsgId                 = ID_IMSA_AT_CIREGU_IND;
    stCireguInd.usClientId              = ucIndex;
    stCireguInd.bitOpExtInfo            = VOS_TRUE;
    stCireguInd.ulRegInfo               = VOS_TRUE;
    stCireguInd.ulExtInfo               = 5;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_SendResultData)
        .expects(never());

    // 调用被测函数
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCireguInd);

    // 执行检查
    GlobalMockObject::verify();
}

TEST_F(Test_AT_RcvImsaCireguInd, Test_AT_RcvImsaCireguInd_002)
{
    // 变量声明
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREGU_IND_STRU             stCireguInd;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CIREGU: 1,5\r\n";

    // 参数初始化
    PS_MEM_SET(&stCireguInd, 0, sizeof(IMSA_AT_CIREGU_IND_STRU));
    stCireguInd.ulMsgId                 = ID_IMSA_AT_CIREGU_IND;
    stCireguInd.usClientId              = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stCireguInd.bitOpExtInfo            = VOS_TRUE;
    stCireguInd.ulRegInfo               = VOS_TRUE;
    stCireguInd.ulExtInfo               = 5;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)acExpectedStr, sizeof(acExpectedStr) -1), eq(VOS_UINT16(sizeof(acExpectedStr) - 1)));

    // 调用被测函数
    ulRslt = AT_RcvImsaCireguInd((AT_IMSA_MSG_STRU *)&stCireguInd);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


#endif


