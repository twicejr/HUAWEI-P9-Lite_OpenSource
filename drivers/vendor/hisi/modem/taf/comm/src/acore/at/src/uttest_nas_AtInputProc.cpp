#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtInputProc.h"

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


VOID Test_AT_InitMuxClientTab(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_AT_HSIC)
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucIndex;

    /* 初始化MUX上下文 */
    AT_InitMuxCtx();

    for (ucLoop = 0; ucLoop < AT_MUX_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[ucLoop].enAtClientTabIdx;

        /* 清空对应表项 */
        PS_MEM_SET(&gastAtClientTab[ucIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));

        /* 填写用户表项 */
        gastAtClientTab[ucIndex].usClientId      = AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[ucLoop].enAtClientId;
        gastAtClientTab[ucIndex].ucPortNo        = AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[ucLoop].ucMuxPort;
        gastAtClientTab[ucIndex].UserType        = AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[ucLoop].ucMuxUser;
        gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

        gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
        gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
        gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
        gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
        gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
    }
#endif
    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#if (FEATURE_ON == FEATURE_AT_HSIC)

class Test_AT_MuxInit: public ::testing::Test
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


TEST_F(Test_AT_MuxInit, Test_AT_MuxInit_001)
{
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq(en_NV_Item_Mux_Support_Flg))
        .will(returnValue(NV_ID_NOT_EXIST));

    MOCKER(MUX_AtRgstUlPortCallBack)
        .expects(never());

    AT_MuxInit();

    EXPECT_EQ(AT_GetCommCtxAddr()->stMuxCtx.ucMuxSupportFlg, VOS_FALSE);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MuxInit, Test_AT_MuxInit_002)
{
    VOS_UINT8                           ucMuxSupportFlg;

    ucMuxSupportFlg = VOS_FALSE;

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(MUX_AtRgstUlPortCallBack)
        .expects(never());

    AT_MuxInit();

    EXPECT_EQ(AT_GetCommCtxAddr()->stMuxCtx.ucMuxSupportFlg, VOS_FALSE);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MuxInit, Test_AT_MuxInit_003)
{
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           ucLoop;
    VOS_UINT32                          ulMuxReportCfg;
    AT_COMM_CTX_STRU                   *pCommCtx = VOS_NULL_PTR;

    ucMuxSupportFlg = VOS_TRUE;
    ulMuxReportCfg = 0xffffffff;

    pCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_MUX_REPORT_CFG), outBoundP(&ulMuxReportCfg))
        .will(returnValue(NV_OK));

    MOCKER(MUX_AtRgstUlPortCallBack)
        .expects(never())8);

    AT_MuxInit();

    EXPECT_EQ(AT_GetCommCtxAddr()->stMuxCtx.ucMuxSupportFlg, VOS_TRUE);

    for (ucLoop = 0; ucLoop < AT_MUX_AT_CHANNEL_MAX; ucLoop++)
    {
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].pReadDataCB, AT_MuxReadDataCB);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enAtClientId, AT_CLIENT_ID_MUX1 + ucLoop);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enAtClientTabIdx, AT_CLIENT_TAB_MUX1_INDEX + ucLoop);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].ucMuxUser,AT_MUX1_USER + ucLoop);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].ucMuxPort, AT_MUX1_PORT_NO + ucLoop);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enDlci, AT_MUX_DLCI1_ID + ucLoop);
        EXPECT_EQ(AT_HSIC_REPORT_OFF, pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enRptType);
    }

    GlobalMockObject::verify();
}



TEST_F(Test_AT_MuxInit, Test_AT_MuxInit_004)
{
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           ucLoop;
    VOS_UINT32                          ulMuxReportCfg;
    AT_COMM_CTX_STRU                   *pCommCtx = VOS_NULL_PTR;

    ucMuxSupportFlg = VOS_TRUE;
    ulMuxReportCfg = 0x0;

    pCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_MUX_REPORT_CFG), outBoundP(&ulMuxReportCfg))
        .will(returnValue(NV_OK));

    MOCKER(MUX_AtRgstUlPortCallBack)
        .expects(never())8);

    AT_MuxInit();

    EXPECT_EQ(AT_GetCommCtxAddr()->stMuxCtx.ucMuxSupportFlg, VOS_TRUE);

    for (ucLoop = 0; ucLoop < AT_MUX_AT_CHANNEL_MAX; ucLoop++)
    {
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].pReadDataCB, AT_MuxReadDataCB);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enRptType, AT_HSIC_REPORT_ON);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enAtClientId, AT_CLIENT_ID_MUX1 + ucLoop);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enAtClientTabIdx, AT_CLIENT_TAB_MUX1_INDEX + ucLoop);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].ucMuxUser,AT_MUX1_USER + ucLoop);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].ucMuxPort, AT_MUX1_PORT_NO + ucLoop);
        EXPECT_EQ(pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enDlci, AT_MUX_DLCI1_ID + ucLoop);
    }

    GlobalMockObject::verify();
}


class Test_AT_MuxReadDataCB: public ::testing::Test
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


TEST_F(Test_AT_MuxReadDataCB, Test_AT_MuxReadDataCB_001)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};

    MOCKER(At_RcvFromUsbCom).expects(never());

    ulRslt = AT_MuxReadDataCB(AT_MUX_DLCI1_ID, (VOS_UINT8 *)aucData, 0);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MuxReadDataCB, Test_AT_MuxReadDataCB_002)
{
    VOS_UINT32                          ulRslt;

    MOCKER(At_RcvFromUsbCom).expects(never());

    ulRslt = AT_MuxReadDataCB(AT_MUX_DLCI1_ID, VOS_NULL_PTR, 1);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MuxReadDataCB, Test_AT_MuxReadDataCB_003)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg;

    ucMuxSupportFlg = VOS_TRUE;

    MOCKER(At_RcvFromUsbCom).expects(never());

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    ulRslt = AT_MuxReadDataCB(0, (VOS_UINT8 *)aucData, 3);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MuxReadDataCB, Test_AT_MuxReadDataCB_004)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg;

    ucMuxSupportFlg = VOS_TRUE;

    MOCKER(At_RcvFromUsbCom).expects(never());

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[0].enDlci = 0;

    ulRslt = AT_MuxReadDataCB(AT_MUX_DLCI1_ID, (VOS_UINT8 *)aucData, 3);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MuxReadDataCB, Test_AT_MuxReadDataCB_005)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[4] = {'A', 'T', 0xd, 0xa};
    VOS_UINT8                           ucMuxSupportFlg = VOS_TRUE;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(eq(AT_MUX_DLCI1_ID), mirror(aucData), eq(3));

    MOCKER(At_SendCmdMsg)
        .stubs()
        .with(eq(AT_CLIENT_TAB_MUX1_INDEX), mirror(aucData), eq(3));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue(VOS_FALSE));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    /* 回显打开 */
    gucAtEType = AT_E_ECHO_CMD;

    gastAtClientTab[AT_CLIENT_TAB_MUX1_INDEX].Mode = AT_CMD_MODE;

    ulRslt = AT_MuxReadDataCB(AT_MUX_DLCI1_ID, (VOS_UINT8 *)aucData, 4);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MuxReadDataCB, Test_AT_MuxReadDataCB_006)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulNvId = en_NV_Item_Mux_Support_Flg;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg = VOS_TRUE;

    VOS_UINT8                           ucMuxDlciId = AT_MUX_DLCI1_ID;
    VOS_UINT8                           ucClientId = AT_CLIENT_TAB_MUX1_INDEX;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(ulNvId), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(eq(ucMuxDlciId), mirror(aucData), eq(3));

    MOCKER(At_SendCmdMsg)
        .stubs()
        .with(eq(ucClientId), mirror(aucData), eq(3), any());

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue(VOS_FALSE));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    /* 回显打开 */
    gucAtEType = AT_E_ECHO_CMD;

    gastAtClientTab[AT_CLIENT_TAB_MUX1_INDEX].Mode = AT_CMD_MODE;

    g_aucAtDataBuff[AT_CLIENT_TAB_MUX1_INDEX].ulBuffLen = 0;

    ulRslt = AT_MuxReadDataCB(AT_MUX_DLCI1_ID, (VOS_UINT8 *)aucData, 3);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_MuxCmdStreamEcho: public ::testing::Test
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


TEST_F(Test_AT_MuxCmdStreamEcho, Test_AT_RcvMuxCmdStream_PreProc_001)
{
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg = VOS_TRUE;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    MOCKER(MUX_DlciDlDataSend).expects(never());

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    AT_SetMuxSupportFlg(VOS_TRUE);

    AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[0].enDlci = 0;

    AT_MuxCmdStreamEcho(AT_MUX_DLCI1_ID, (VOS_UINT8 *)aucData, 3);

    GlobalMockObject::verify();
}


class Test_AT_SendMuxSelResultData: public ::testing::Test
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


TEST_F(Test_AT_SendMuxSelResultData, Test_AT_SendMuxSelResultData_001)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg;

    ucMuxSupportFlg = VOS_TRUE;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    MOCKER(MUX_DlciDlDataSend).expects(never());

    ulRslt = AT_SendMuxSelResultData(AT_CLIENT_TAB_PCUI_INDEX, aucData ,3);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendMuxSelResultData, Test_AT_SendMuxSelResultData_002)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    AT_SetMuxSupportFlg(VOS_TRUE);

    AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[0].enRptType = AT_HSIC_REPORT_OFF;

    MOCKER(MUX_DlciDlDataSend).expects(never());

    ulRslt = AT_SendMuxSelResultData(AT_CLIENT_TAB_MUX1_INDEX, aucData ,3);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendMuxSelResultData, Test_AT_SendMuxSelResultData_003)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulNvId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg;

    ucMuxSupportFlg = VOS_TRUE;
    ulNvId          = en_NV_Item_Mux_Support_Flg;
    usLen           = 3;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(ulNvId), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    AT_SetMuxSupportFlg(VOS_TRUE);

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(any(), mirror(aucData), eq(usLen));

    ulRslt = AT_SendMuxSelResultData(AT_CLIENT_TAB_MUX1_INDEX, aucData ,usLen);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_SendMuxResultData: public ::testing::Test
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


TEST_F(Test_AT_SendMuxResultData, Test_AT_SendMuxResultData_001)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg;

    ucMuxSupportFlg = VOS_TRUE;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    MOCKER(MUX_DlciDlDataSend).expects(never());

    ulRslt = AT_SendMuxResultData(AT_CLIENT_TAB_PCUI_INDEX, aucData ,3);

    EXPECT_EQ(AT_FAILURE, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendMuxResultData, Test_AT_SendMuxResultData_002)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg;

    ucMuxSupportFlg = VOS_FALSE;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    MOCKER(MUX_DlciDlDataSend).expects(never());

    ulRslt = AT_SendMuxResultData(AT_CLIENT_TAB_MUX1_INDEX, aucData ,3);

    EXPECT_EQ(AT_FAILURE, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_GetMuxDlciFromClientIdx: public ::testing::Test
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


TEST_F(Test_AT_GetMuxDlciFromClientIdx, Test_AT_GetMuxDlciFromClientIdx_001)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[3] = {'A', 'T', 0xd};
    VOS_UINT8                           ucMuxSupportFlg;
    AT_MUX_DLCI_TYPE_ENUM_UINT8         enDlci;

    ucMuxSupportFlg = VOS_TRUE;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_Mux_Support_Flg), outBoundP(&ucMuxSupportFlg))
        .will(returnValue(NV_OK));

    MOCKER(NV_ReadEx).stubs().will(returnValue(NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    AT_SetMuxSupportFlg(VOS_TRUE);

    MOCKER(MUX_DlciDlDataSend).expects(never());

    ulRslt = AT_GetMuxDlciFromClientIdx(AT_CLIENT_TAB_PCUI_INDEX, &enDlci);

    EXPECT_EQ(VOS_FALSE, ulRslt);

    GlobalMockObject::verify();
}
#endif /* FEATURE_ON == FEATURE_AT_HSIC */


class Test_AT_IsConcurrentPorts: public ::testing::Test
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


TEST_F(Test_AT_IsConcurrentPorts, Test_AT_IsConcurrentPorts_001)
{
    VOS_UINT32                          ulRslt;

    MOCKER(AT_CheckMuxUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(AT_CheckAppUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    ulRslt = AT_IsConcurrentPorts(AT_CLIENT_TAB_PCUI_INDEX, AT_CLIENT_TAB_APP_INDEX);

    EXPECT_EQ(VOS_TRUE, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsConcurrentPorts, Test_AT_IsConcurrentPorts_002)
{
    VOS_UINT32                          ulRslt;

    MOCKER(AT_CheckMuxUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_CheckAppUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    ulRslt = AT_IsConcurrentPorts(AT_CLIENT_TAB_APP_INDEX, AT_CLIENT_TAB_APP1_INDEX);

    EXPECT_EQ(VOS_TRUE, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsConcurrentPorts, Test_AT_IsConcurrentPorts_003)
{
    VOS_UINT32                          ulRslt;

    AT_SetPcuiCtrlConcurrentFlag(VOS_TRUE);
    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;
    gastAtClientTab[AT_CLIENT_TAB_CTRL_INDEX].UserType = AT_CTR_USER;

    MOCKER(AT_CheckMuxUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_CheckAppUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ulRslt = AT_IsConcurrentPorts(AT_CLIENT_TAB_PCUI_INDEX, AT_CLIENT_TAB_CTRL_INDEX);

    EXPECT_EQ(VOS_TRUE, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsConcurrentPorts, Test_AT_IsConcurrentPorts_004)
{
    VOS_UINT32                          ulRslt;

    AT_SetPcuiCtrlConcurrentFlag(VOS_FALSE);

    MOCKER(AT_CheckMuxUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_APP_INDEX))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_PCUI_INDEX))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(AT_CheckAppUser)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_APP_INDEX))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(AT_CheckAppUser)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_PCUI_INDEX))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ulRslt = AT_IsConcurrentPorts(AT_CLIENT_TAB_PCUI_INDEX, AT_CLIENT_TAB_APP_INDEX);

    EXPECT_EQ(VOS_FALSE, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_UsbModemInit: public ::testing::Test
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


TEST_F(Test_AT_UsbModemInit, Test_AT_UsbModemInit_001)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(UDI_INVALID_HANDLE));

    // 调用被测函数
    AT_UsbModemInit();

    EXPECT_EQ(UDI_INVALID_HANDLE, g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbModemInit, Test_AT_UsbModemInit_002)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_UsbModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbModemInit, Test_AT_UsbModemInit_003)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq((BSP_U32)ACM_IOCTL_SET_READ_CB), eq((VOS_VOID*)AT_UsbModemReadDataCB))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_UsbModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbModemInit, Test_AT_UsbModemInit_004)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq((BSP_U32)ACM_IOCTL_SET_READ_CB), eq((VOS_VOID*)AT_UsbModemReadDataCB))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq((BSP_U32)ACM_IOCTL_SET_FREE_CB), eq((VOS_VOID*)AT_ModemFreeDlDataBuf))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_UsbModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbModemInit, Test_AT_UsbModemInit_005)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq((BSP_U32)ACM_IOCTL_SET_READ_CB), eq((VOS_VOID*)AT_UsbModemReadDataCB))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq((BSP_U32)ACM_IOCTL_SET_FREE_CB), eq((VOS_VOID*)AT_ModemFreeDlDataBuf))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq((BSP_U32)ACM_MODEM_IOCTL_SET_MSC_READ_CB), eq((VOS_VOID*)AT_UsbModemReadMscCB))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_UsbModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbModemInit, Test_AT_UsbModemInit_006)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_OK));

    // 调用被测函数
    AT_UsbModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX]);
    EXPECT_EQ(AT_CLIENT_ID_MODEM, gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].usClientId);
    EXPECT_EQ(AT_USB_MODEM_PORT_NO, gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].ucPortType);
    EXPECT_EQ(AT_MODEM_USER_DLCI, gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].ucDlci);
    EXPECT_EQ(AT_USB_MODEM_PORT_NO, gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].ucPortNo);
    EXPECT_EQ(AT_MODEM_USER, gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].UserType);
    EXPECT_EQ(AT_CLIENT_USED, gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].ucUsed);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_UsbModemClose: public ::testing::Test
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


TEST_F(Test_AT_UsbModemClose, Test_AT_UsbModemClose_001)
{
    VOS_UINT8                           ucPsRabId;

    ucPsRabId = 1;

    gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].ucPsRabId = ucPsRabId;
    g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX] = 1;

    MOCKER(AT_DeRegModemPsDataFCPoint)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_MODEM_INDEX), eq(ucPsRabId))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_close)
        .expects(exactly(1))
        .with(eq(1))
        .will(returnValue(VOS_OK));

    // 调用被测函数
    AT_UsbModemClose();

    EXPECT_EQ(UDI_INVALID_HANDLE, g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SetUsbDebugFlag: public ::testing::Test
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


TEST_F(Test_AT_SetUsbDebugFlag, Test_AT_SetUsbDebugFlag_001)
{
    VOS_UINT32                          ulFlag;

    ulFlag = VOS_TRUE;

    // 调用被测函数
    AT_SetUsbDebugFlag(ulFlag);

    EXPECT_EQ(ulFlag, g_ulAtUsbDebugFlag);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_ModemMscInd: public ::testing::Test
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


TEST_F(Test_At_ModemMscInd, Test_At_ModemMscInd_001)
{
    AT_DCE_MSC_STRU                     MscStru;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;

    // 初始化局部变量
    memset(&MscStru, 0, sizeof(MscStru));
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;

    // MOCKER操作;
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)NULL));

    // 调用被测函数
    result = At_ModemMscInd(ucIndex, ucDlci, &MscStru);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ModemMscInd, Test_At_ModemMscInd_002)
{
    AT_DCE_MSC_STRU                     MscStru;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;

    // 初始化局部变量
    memset(&MscStru, 0, sizeof(MscStru));
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;

    // MOCKER操作;
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(invoke(UT_Ps_SendMsgFail));

    // 调用被测函数
    result = At_ModemMscInd(ucIndex, ucDlci, &MscStru);

    // 执行检查
    EXPECT_EQ(AT_FAILURE ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ModemMscInd, Test_At_ModemMscInd_003)
{
    AT_DCE_MSC_STRU                     MscStru;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;

    // 初始化局部变量
    memset(&MscStru, 0, sizeof(MscStru));
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;

    // 调用被测函数
    result = At_ModemMscInd(ucIndex, ucDlci, &MscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_ModemDataInd: public ::testing::Test
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



TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;
    IMM_ZC_STRU                         stData;
    VOS_CHAR                            acData[]   ="+++";

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_PCUI_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;
    memset(&stData, 0, sizeof(stData));

    stData.data   = (VOS_UINT8*)acData;
    stData.len    = strlen(acData);

    // MOCKER操作;
    MOCKER(AT_ModemFreeUlDataBuf)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(&stData))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, &stData);

    // 执行检查
    EXPECT_EQ(AT_FAILURE ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_002)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;
    IMM_ZC_STRU                         stData;
    VOS_CHAR                            acData[]   ="~~~";

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;
    memset(&stData, 0, sizeof(stData));

    stData.data   = (VOS_UINT8*)acData;
    stData.len    = strlen(acData);

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortType = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci     = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].Mode       = AT_CMD_MODE;

    // MOCKER操作;
    MOCKER(AT_ModemFreeUlDataBuf)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(&stData))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, &stData);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_003)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;
    IMM_ZC_STRU                         stData;
    VOS_CHAR                            acData[]   ="AT\r";

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;
    memset(&stData, 0, sizeof(stData));

    stData.data   = (VOS_UINT8*)acData;
    stData.len    = strlen(acData);

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortType = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci     = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].Mode       = AT_CMD_MODE;

    // MOCKER操作;
    MOCKER(AT_ModemFreeUlDataBuf)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(&stData))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // MOCKER操作;
    MOCKER(At_CmdStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, &stData);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_004)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;
    IMM_ZC_STRU                         stData;
    VOS_CHAR                            acData[]    = "+++";

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;
    memset(&stData, 0, sizeof(stData));

    stData.data   = (VOS_UINT8*)acData;
    stData.len    = strlen(acData);

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortType = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci     = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作;
    MOCKER(At_ModemMscInd)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ucDlci), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_ModemFreeUlDataBuf)
        .expects(exactly(1))
        .with(eq(ucIndex), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(PPP_PullPacketEvent)
        .expects(exactly(0))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, &stData);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_005)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;
    IMM_ZC_STRU                         stData;
    VOS_CHAR                            acData[]    = "~+++";

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;
    memset(&stData, 0, sizeof(stData));

    stData.data   = (VOS_UINT8*)acData;
    stData.len    = strlen(acData);

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortType = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci     = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作;
    MOCKER(At_ModemMscInd)
        .expects(exactly(0))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(PPP_PullPacketEvent)
        .expects(exactly(1))
        .with(eq(gastAtClientTab[ucIndex].usPppId), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, &stData);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_006)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;
    IMM_ZC_STRU                         stData;
    VOS_CHAR                            acData[]    = "+++";

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;
    memset(&stData, 0, sizeof(stData));

    stData.data   = (VOS_UINT8*)acData;
    stData.len    = strlen(acData);

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortType = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci     = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作;
    MOCKER(At_ModemMscInd)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ucDlci), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_ModemFreeUlDataBuf)
        .expects(exactly(1))
        .with(eq(ucIndex), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(PPP_PullRawDataEvent)
        .expects(exactly(0))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, &stData);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_007)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;
    IMM_ZC_STRU                         stData;
    VOS_CHAR                            acData[]    = "~+++";

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;
    memset(&stData, 0, sizeof(stData));

    stData.data   = (VOS_UINT8*)acData;
    stData.len    = strlen(acData);

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortType = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci     = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作;
    MOCKER(At_ModemMscInd)
        .expects(exactly(0))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(PPP_PullRawDataEvent)
        .expects(exactly(1))
        .with(eq(gastAtClientTab[ucIndex].usPppId), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, &stData);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_CSD)

TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_008)
{
    // 参数初始化
    VOS_UINT8 Data[4]="+++";
    VOS_UINT8 ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT8 ucDlci = AT_MODEM_USER_DLCI;
    VOS_UINT32 result;
    IMM_ZC_STRU                        *pstData;

    pstData = (IMM_ZC_STRU *)malloc(sizeof(IMM_ZC_STRU));

    pstData->data = Data;
    pstData->len = 3;

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortType = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci     = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_CSD_DATA_MODE;

    MOCKER(CSD_UL_SendData)
        .expects(exactly(1));

    MOCKER(AT_ModemFreeUlDataBuf)
        .expects(exactly(1))
        .with(eq(ucIndex), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, (IMM_ZC_STRU *)pstData);

    free(pstData);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_At_ModemDataInd, Test_At_ModemDataInd_009)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT32                          result;
    IMM_ZC_STRU                         stData;
    VOS_CHAR                            acData[]    = "+++";

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;
    ucDlci      = AT_MODEM_USER_DLCI;
    memset(&stData, 0, sizeof(stData));

    stData.data   = (VOS_UINT8*)acData;
    stData.len    = strlen(acData);

    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortType = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci     = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作;
    MOCKER(AT_ModemFreeUlDataBuf)
        .expects(exactly(1))
        .with(eq(ucIndex), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    result = At_ModemDataInd(ucIndex, ucDlci, &stData);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,result);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_ModemFreeUlDataBuf: public ::testing::Test
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


TEST_F(Test_AT_ModemFreeUlDataBuf, Test_AT_ModemFreeUlDataBuf_001)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stBuf = {0};

    g_stAtStatsInfo.stModemStats.ulUlReturnBuffSuccNum = 0;

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ACM_IOCTL_RETURN_BUFF), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_ModemFreeUlDataBuf(AT_CLIENT_TAB_MODEM_INDEX, &stBuf);

    EXPECT_EQ(AT_SUCCESS, ulRslt);
    EXPECT_EQ(1, g_stAtStatsInfo.stModemStats.ulUlReturnBuffSuccNum);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemFreeUlDataBuf, Test_AT_ModemFreeUlDataBuf_002)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stBuf = {0};

    g_stAtStatsInfo.stModemStats.ulUlReturnBuffSuccNum = 0;

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ACM_IOCTL_RETURN_BUFF), any())
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_ModemFreeUlDataBuf(AT_CLIENT_TAB_MODEM_INDEX, &stBuf);

    EXPECT_EQ(AT_FAILURE, ulRslt);
    EXPECT_EQ(1, g_stAtStatsInfo.stModemStats.ulUlReturnBuffFailNum);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_UsbModemReadDataCB: public ::testing::Test
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


TEST_F(Test_AT_UsbModemReadDataCB, Test_AT_UsbModemReadDataCB_001)
{
    /*获取BSP内存*/
    MOCKER(AT_ModemGetUlDataBuf)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    /*使用内存*/
    MOCKER(At_ModemDataInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_UsbModemReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_UsbModemReadMscCB: public ::testing::Test
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


TEST_F(Test_AT_UsbModemReadMscCB, Test_AT_UsbModemReadMscCB_001)
{
    AT_DCE_MSC_STRU                     stDceMsc;

    stDceMsc.OP_Cts = 1;
    stDceMsc.ucCts = 1;

    MOCKER(At_ModemMscInd)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_MODEM_INDEX), eq((VOS_UINT8)AT_MODEM_USER_DLCI), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_UsbModemReadMscCB(&stDceMsc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbModemReadMscCB, Test_AT_UsbModemReadMscCB_002)
{
    MOCKER(At_ModemMscInd)
        .expects(never());

    // 调用被测函数
    AT_UsbModemReadMscCB(VOS_NULL_PTR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_ModemWriteData: public ::testing::Test
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


TEST_F(Test_AT_ModemWriteData, Test_AT_ModemWriteData_001)
{
    IMM_ZC_STRU                         stData = {0};
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex = 0;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    g_alAtUdiHandle[ucIndex] = 0;
    g_stAtStatsInfo.stModemStats.ulDlWriteAsyncSuccNum = 0;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .with(any(), eq((VOS_UINT32)ACM_IOCTL_WRITE_ASYNC), any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_ModemWriteData(ucIndex, &stData);

    EXPECT_EQ(AT_SUCCESS, ulRslt);
    EXPECT_EQ(1, g_stAtStatsInfo.stModemStats.ulDlWriteAsyncSuccNum);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemWriteData, Test_AT_ModemWriteData_002)
{
    IMM_ZC_STRU                         stData = {0};
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    g_alAtUdiHandle[ucIndex] = 0;
    g_stAtStatsInfo.stModemStats.ulDlWriteAsyncFailNum = 0;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .with(any(), eq((VOS_UINT32)ACM_IOCTL_WRITE_ASYNC), any())
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_ModemFreeDlDataBuf)
        .expects(exactly(1));

    // 调用被测函数
    ulRslt = AT_ModemWriteData(ucIndex, &stData);

    EXPECT_EQ(AT_FAILURE, ulRslt);
    EXPECT_EQ(1, g_stAtStatsInfo.stModemStats.ulDlWriteAsyncFailNum);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_ModemWriteData, Test_AT_ModemWriteData_003)
{
    IMM_ZC_STRU                         stData = {0};
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;
    g_stAtStatsInfo.stModemStats.ulDlWriteAsyncSuccNum = 0;

    MOCKER(AT_ModemFreeDlDataBuf)
        .expects(exactly(1));

    // 调用被测函数
    ulRslt = AT_ModemWriteData(ucIndex, &stData);

    EXPECT_EQ(AT_FAILURE, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SendDataToModem: public ::testing::Test
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


TEST_F(Test_AT_SendDataToModem,Test_AT_SendDataToModem_001)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;

    usLen = 5;

    memcpy(aucData, "abcd", usLen);

    MOCKER(IMM_ZcStaticAlloc_Debug)
        .expects(exactly(1))
        .will(returnValue((IMM_ZC_STRU*)VOS_NULL_PTR));

    MOCKER(AT_ModemWriteData)
        .expects(never());

    ulRslt = AT_SendDataToModem(AT_CLIENT_TAB_MODEM_INDEX, aucData, usLen);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendDataToModem,Test_AT_SendDataToModem_002)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    IMM_ZC_STRU                         stImmZc;
    VOS_UINT8                          *pucTmp;

    usLen = 5;

    memcpy(aucData, "abcd", usLen);

    MOCKER(IMM_ZcStaticAlloc_Debug)
        .expects(exactly(1))
        .will(returnValue(&stImmZc));

    MOCKER(IMM_ZcPut_Debug)
        .expects(exactly(1))
        .will(returnValue(pucTmp));

    MOCKER(V_MemCpy)
        .expects(exactly(1))
        .will(returnValue((VOS_VOID*)pucTmp));

    MOCKER(AT_ModemWriteData)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRslt = AT_SendDataToModem(AT_CLIENT_TAB_MODEM_INDEX, aucData, usLen);

    EXPECT_EQ(AT_FAILURE, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendDataToModem,Test_AT_SendDataToModem_003)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    IMM_ZC_STRU                         stImmZc;
    VOS_UINT8                          *pucTmp;

    usLen = 5;

    memcpy(aucData, "abcd", usLen);

    MOCKER(IMM_ZcStaticAlloc_Debug)
        .expects(exactly(1))
        .will(returnValue(&stImmZc));

    MOCKER(IMM_ZcPut_Debug)
        .expects(exactly(1))
        .will(returnValue(pucTmp));

    MOCKER(V_MemCpy)
        .expects(exactly(1))
        .will(returnValue((VOS_VOID*)pucTmp));

    MOCKER(AT_ModemWriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRslt = AT_SendDataToModem(AT_CLIENT_TAB_MODEM_INDEX, aucData, usLen);

    EXPECT_EQ(AT_SUCCESS, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_SendZcDataToModem: public ::testing::Test
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


TEST_F(Test_AT_SendZcDataToModem,Test_AT_SendZcDataToModem_001)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stImmZc;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usPppId;

    ucIndex = AT_CLIENT_ID_MODEM;
    usPppId = 0;

    gastAtPppIndexTab[usPppId] = ucIndex;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    MOCKER(AT_ModemWriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRslt = AT_SendZcDataToModem(usPppId, &stImmZc);

    EXPECT_EQ(AT_FAILURE, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendZcDataToModem,Test_AT_SendZcDataToModem_002)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stImmZc;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usPppId;

    ucIndex = AT_CLIENT_ID_MODEM;
    usPppId = 0;

    gastAtPppIndexTab[usPppId] = ucIndex;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    MOCKER(AT_ModemWriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRslt = AT_SendZcDataToModem(usPppId, &stImmZc);

    EXPECT_EQ(AT_SUCCESS, ulRslt);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

TEST_F(Test_AT_SendZcDataToModem,Test_AT_SendZcDataToModem_003)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stImmZc;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usPppId;

    ucIndex = AT_CLIENT_ID_HSUART;
    usPppId = 0;

    gastAtPppIndexTab[usPppId] = ucIndex;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    MOCKER(AT_HSUART_WriteDataAsync)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRslt = AT_SendZcDataToModem(usPppId, &stImmZc);

    EXPECT_EQ(AT_FAILURE, ulRslt);

    GlobalMockObject::verify();
}
#endif


TEST_F(Test_AT_SendZcDataToModem,Test_AT_SendZcDataToModem_004)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stImmZc;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usPppId;

    ucIndex = AT_CLIENT_ID_PCUI;
    usPppId = 0;

    gastAtPppIndexTab[usPppId] = AT_CLIENT_ID_PCUI;
    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;

    MOCKER(AT_ModemWriteData)
        .expects(never());

    ulRslt = AT_SendZcDataToModem(usPppId, &stImmZc);

    EXPECT_EQ(AT_SUCCESS, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_SendCsdZcDataToModem: public ::testing::Test
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

TEST_F(Test_AT_SendCsdZcDataToModem,Test_AT_SendCsdZcDataToModem_001)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stImmZc;

    MOCKER(AT_ModemWriteData)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRslt = AT_SendCsdZcDataToModem(AT_CLIENT_TAB_MODEM_INDEX, &stImmZc);

    EXPECT_EQ(AT_FAILURE, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendCsdZcDataToModem,Test_AT_SendCsdZcDataToModem_002)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stImmZc;

    MOCKER(AT_ModemWriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRslt = AT_SendCsdZcDataToModem(AT_CLIENT_TAB_MODEM_INDEX, &stImmZc);

    EXPECT_EQ(AT_SUCCESS, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_UsbModemEnableCB: public ::testing::Test
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

TEST_F(Test_AT_UsbModemEnableCB,Test_AT_UsbModemEnableCB_001)
{
    VOS_UINT8                           ucEnable;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    ucEnable = VOS_FALSE;

    MOCKER(AT_ModemeEnableCB)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(ucEnable));

    AT_UsbModemEnableCB(ucEnable);

    GlobalMockObject::verify();
}


class Test_AT_ModemGetUlDataBuf: public ::testing::Test
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


TEST_F(Test_AT_ModemGetUlDataBuf, Test_AT_ModemGetUlDataBuf_001)
{
    IMM_ZC_STRU                        *pucBuf;
    VOS_UINT32                          ulRslt;

    g_stAtStatsInfo.stModemStats.ulUlGetRDFailNum = 0;

    MOCKER(mdrv_udi_ioctl)
       .stubs()
       .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_ModemGetUlDataBuf(AT_CLIENT_TAB_MODEM_INDEX, &pucBuf);

    EXPECT_EQ(AT_FAILURE, ulRslt);
    EXPECT_EQ(1, g_stAtStatsInfo.stModemStats.ulUlGetRDFailNum);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemGetUlDataBuf, Test_AT_ModemGetUlDataBuf_002)
{
    IMM_ZC_STRU                        *pucBuf;
    VOS_UINT32                          ulRslt;
    ACM_WR_ASYNC_INFO                   stCtlParam;

    stCtlParam.pVirAddr = VOS_NULL_PTR;
    stCtlParam.u32Size = 10;

    g_stAtStatsInfo.stModemStats.ulUlInvalidRDNum = 0;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .with(any(), any(), outBoundP((VOS_VOID*)&stCtlParam, (VOS_UINT32)sizeof(stCtlParam)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_ModemGetUlDataBuf(AT_CLIENT_TAB_MODEM_INDEX, &pucBuf);

    EXPECT_EQ(AT_FAILURE, ulRslt);
    EXPECT_EQ(1, g_stAtStatsInfo.stModemStats.ulUlInvalidRDNum);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_ModemGetUlDataBuf, Test_AT_ModemGetUlDataBuf_003)
{
    IMM_ZC_STRU                        *pucBuf;
    VOS_UINT32                          ulRslt;
    ACM_WR_ASYNC_INFO                   stCtlParam;

    stCtlParam.pVirAddr = (char *)malloc(10);
    stCtlParam.u32Size = 10;

    g_stAtStatsInfo.stModemStats.ulUlGetRDSuccNum = 0;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .with(any(), any(), outBoundP((VOS_VOID*)&stCtlParam, (VOS_UINT32)sizeof(stCtlParam)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRslt = AT_ModemGetUlDataBuf(AT_CLIENT_TAB_MODEM_INDEX, &pucBuf);

    EXPECT_EQ(AT_SUCCESS, ulRslt);
    EXPECT_EQ(1, g_stAtStatsInfo.stModemStats.ulUlGetRDSuccNum);

    free(stCtlParam.pVirAddr);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_ModemSetCtlStatus: public ::testing::Test
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


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_001)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Dsr = 1;
    stDceMsc.ucDsr = 1;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(IO_CTRL_DSR, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_DSR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_002)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Dsr = 1;
    stDceMsc.ucDsr = 0;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(0, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_DSR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_003)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Cts = 1;
    stDceMsc.ucCts = 1;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(IO_CTRL_CTS, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_CTS);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_004)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Cts = 1;
    stDceMsc.ucCts = 0;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(0, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_CTS);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_005)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Ri = 1;
    stDceMsc.ucRi = 1;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(IO_CTRL_RI, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_RI);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_006)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Ri = 1;
    stDceMsc.ucRi = 0;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(0, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_RI);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_007)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Dcd = 1;
    stDceMsc.ucDcd = 1;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(IO_CTRL_DCD, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_DCD);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_008)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Dcd = 1;
    stDceMsc.ucDcd = 0;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(0, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_DCD);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_009)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Fc = 1;
    stDceMsc.ucFc = 1;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(IO_CTRL_FC, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_FC);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_010)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    stDceMsc.OP_Fc = 1;
    stDceMsc.ucFc = 0;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(0, gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_FC);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemSetCtlStatus, Test_AT_ModemSetCtlStatus_011)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    gastAtClientTab[ucIndex].ModemStatus = IO_CTRL_FC;

    // 调用被测函数
    AT_ModemSetCtlStatus(ucIndex, VOS_NULL_PTR);

    EXPECT_EQ(IO_CTRL_FC, gastAtClientTab[ucIndex].ModemStatus);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SetModemStatus: public ::testing::Test
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


TEST_F(Test_AT_SetModemStatus, Test_AT_SetModemStatus_001)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT32                          ulRslt;

    stDceMsc.OP_Dsr = 1;
    stDceMsc.ucDsr = 1;

    gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].UserType = AT_MODEM_USER;

    MOCKER(AT_ModemSetCtlStatus)
        .expects(never());

    // 调用被测函数
    ulRslt = AT_SetModemStatus(AT_CLIENT_TAB_MODEM_INDEX, VOS_NULL_PTR);

    EXPECT_EQ(AT_FAILURE,ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetModemStatus, Test_AT_SetModemStatus_002)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT32                          ulRslt;

    memset(&stDceMsc, 0x0, sizeof(stDceMsc));
    stDceMsc.OP_Dsr = 1;
    stDceMsc.ucDsr = 1;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_ModemSetCtlStatus)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_PCUI_INDEX), any());

    // 调用被测函数
    ulRslt = AT_SetModemStatus(AT_CLIENT_TAB_PCUI_INDEX, &stDceMsc);

    EXPECT_EQ(AT_SUCCESS,ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetModemStatus, Test_AT_SetModemStatus_003)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT32                          ulRslt;

    memset(&stDceMsc, 0x0, sizeof(stDceMsc));
    stDceMsc.OP_Dsr = 1;
    stDceMsc.ucDsr  = 1;

    g_alAtUdiHandle[AT_CLIENT_TAB_MODEM_INDEX] = 0;

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERR));

    MOCKER(AT_ModemSetCtlStatus)
        .expects(exactly(1));

    gastAtClientTab[AT_CLIENT_TAB_MODEM_INDEX].UserType = AT_MODEM_USER;

    // 调用被测函数
    ulRslt = AT_SetModemStatus(AT_CLIENT_TAB_MODEM_INDEX, &stDceMsc);

    EXPECT_EQ(AT_FAILURE,ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetModemStatus, Test_AT_SetModemStatus_004)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    memset(&stDceMsc, 0x0, sizeof(stDceMsc));
    stDceMsc.OP_Dsr = 1;
    stDceMsc.ucDsr  = 1;
    ucIndex         = AT_CLIENT_TAB_MODEM_INDEX;

    g_alAtUdiHandle[ucIndex] = 0;

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    MOCKER(AT_ModemSetCtlStatus)
        .expects(exactly(1));

    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    // 调用被测函数
    ulRslt = AT_SetModemStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(AT_SUCCESS,ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

TEST_F(Test_AT_SetModemStatus, Test_AT_SetModemStatus_005)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    stDceMsc.OP_Dsr = 1;
    stDceMsc.ucDsr  = 1;
    ucIndex         = AT_CLIENT_TAB_HSUART_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;
    g_alAtUdiHandle[ucIndex] = 0;

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    MOCKER(AT_ModemSetCtlStatus)
        .expects(exactly(1));

    // 调用被测函数
    ulRslt = AT_SetModemStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(AT_SUCCESS,ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetModemStatus, Test_AT_SetModemStatus_006)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    stDceMsc.OP_Dsr = 1;
    stDceMsc.ucDsr  = 1;
    ucIndex         = AT_CLIENT_TAB_HSUART_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;
    g_alAtUdiHandle[ucIndex] = 0;

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    MOCKER(AT_ModemSetCtlStatus)
        .expects(exactly(1));

    // 调用被测函数
    ulRslt = AT_SetModemStatus(ucIndex, &stDceMsc);

    EXPECT_EQ(AT_FAILURE,ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_CmdStreamPreProc: public ::testing::Test
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


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_001)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_PCUI;
    usLen   = 4;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0A;

    /*全局变量初始化：回显*/
    gucAtEType = AT_E_ECHO_CMD;
    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .with(eq((DMS_PHY_BEAR_ENUM)AT_USB_COM_PORT_NO), any(), eq((TAF_UINT16)(usLen - 1)))
        .will(returnValue((VOS_INT32)VOS_OK));

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));
    //检查调用时，需要在用例结束位置加上这句
     GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_002)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_PCUI;
    usLen   = 3;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0F;

    /*全局变量初始化：回显*/
    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;
    gucAtEType = AT_E_ECHO_CMD;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .with(eq((DMS_PHY_BEAR_ENUM)AT_USB_COM_PORT_NO), any(), eq(usLen))
        .will(returnValue((VOS_INT32)VOS_OK));

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_003)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_CTRL;
    usLen   = 4;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0A;

    /*全局变量初始化：回显*/
    gucAtEType = AT_E_ECHO_CMD;
    gastAtClientTab[ucIndex].UserType = AT_CTR_USER;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .with(eq((DMS_PHY_BEAR_ENUM)AT_CTR_PORT_NO), any(), eq((TAF_UINT16)(usLen - 1)))
        .will(returnValue((VOS_INT32)VOS_OK));

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));
    //检查调用时，需要在用例结束位置加上这句
     GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_004)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_CTRL;
    usLen   = 3;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0F;

    /*全局变量初始化：回显*/
    gastAtClientTab[ucIndex].UserType = AT_CTR_USER;
    gucAtEType = AT_E_ECHO_CMD;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .with(eq((DMS_PHY_BEAR_ENUM)AT_CTR_PORT_NO), any(), eq(usLen))
        .will(returnValue((VOS_INT32)VOS_OK));

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_005)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_MODEM;
    usLen   = 4;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0A;

    /*全局变量初始化：回显*/
    gucAtEType = AT_E_ECHO_CMD;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(AT_SendDataToModem)
        .expects(exactly(1))
        .with(eq(ucIndex), any(), eq((TAF_UINT16)(usLen - 1)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));
    //检查调用时，需要在用例结束位置加上这句
     GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_006)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];
    VOS_UINT32                          ulRst;

    ucIndex = AT_CLIENT_ID_MODEM;
    usLen   = 3;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0F;

    /*全局变量初始化：回显*/
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;
    gucAtEType = AT_E_ECHO_CMD;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(AT_SendDataToModem)
        .expects(exactly(1))
        .with(eq(ucIndex), any(), eq(usLen))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRst = At_CmdStreamPreProc(ucIndex,pData,usLen);

    ASSERT_EQ(AT_SUCCESS, ulRst);
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_007)
{
    VOS_UINT8       ucIndex;
    VOS_UINT8       *pData;
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;

    pData = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);

    gucAtEType = AT_E_ECHO_CMD;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(AT_VcomCmdStreamEcho)
        .expects(exactly(1));

    ulResult = At_CmdStreamPreProc(ucIndex, pData, usLen);

    EXPECT_EQ(AT_SUCCESS,ulResult);

    PS_MEM_FREE(WUEPS_PID_AT, pData);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_008)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_APP;
    usLen   = 4;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0A;

    /*全局变量初始化：回显*/
    gucAtEType = AT_E_ECHO_CMD;
    gastAtClientTab[ucIndex].UserType = AT_APP_USER;
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(APP_VCOM_Send)
        .expects(never());

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));
    //检查调用时，需要在用例结束位置加上这句
     GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_009)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_NDIS;
    usLen   = 4;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0A;

    /*全局变量初始化：回显*/
    gucAtEType = AT_E_ECHO_CMD;
    gastAtClientTab[ucIndex].UserType = AT_NDIS_USER;
    g_ulAtUsbDebugFlag = VOS_TRUE;

    MOCKER(APP_VCOM_Send)
        .expects(never());

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));
    //检查调用时，需要在用例结束位置加上这句
     GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)

TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_010)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           aucData[3];
    VOS_UINT16                          usLen = 3;
    VOS_UINT32                          ulResult;

    gastAtClientTab[ucIndex].UserType = AT_HSIC1_USER;

    aucData[0] = 'A';
    aucData[1] = 'T';
    aucData[2] = ucAtS3;

    gucAtEType = AT_E_ECHO_CMD;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(AT_SendDataToHsic)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror(aucData, usLen), eq(usLen))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulResult = At_CmdStreamPreProc(ucIndex, aucData, usLen);

    EXPECT_EQ(AT_SUCCESS,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_011)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_HSIC4;
    usLen   = 4;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0A;

    /*全局变量初始化：回显*/
    gucAtEType = AT_E_ECHO_CMD;
    gastAtClientTab[ucIndex].UserType = AT_HSIC4_USER;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(APP_VCOM_Send)
        .expects(never());

    MOCKER(AT_SendDataToHsic)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(pData), eq((VOS_UINT16)(usLen - 1)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CmdStreamPreProc, Test_At_CmdStreamPreProc_012)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];

    ucIndex = AT_CLIENT_ID_HSIC4;
    usLen   = 4;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0D;

    /*全局变量初始化：回显*/
    gucAtEType = AT_E_ECHO_CMD;
    gastAtClientTab[ucIndex].UserType = AT_HSIC4_USER;
    g_ulAtUsbDebugFlag = VOS_FALSE;

    MOCKER(APP_VCOM_Send)
        .expects(never());

    MOCKER(AT_SendDataToHsic)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(pData), eq(usLen));

    ASSERT_EQ(AT_SUCCESS,At_CmdStreamPreProc(ucIndex,pData,usLen));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_VcomCmdStreamEcho: public ::testing::Test
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


TEST_F(Test_AT_VcomCmdStreamEcho, Test_AT_DisplayVcomInputData_001)
{
    TAF_UINT8                           ucIndex;
    TAF_UINT8                          *pData;
    TAF_UINT16                          usLen;
    TAF_UINT8                           audata[4];
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();
    *pucSystemAppConfig = SYSTEM_APP_WEBUI;

    ucIndex = AT_CLIENT_ID_APP;
    usLen   = 4;

    pData = audata;
    audata[0] = 0x4F;
    audata[1] = 0x4B;
    audata[2] = 0x0D;
    audata[3] = 0x0A;

    /*全局变量初始化：回显*/
    gucAtEType = AT_E_ECHO_CMD;
    gastAtClientTab[ucIndex].UserType = AT_APP_USER;

    MOCKER(APP_VCOM_Send)
        .expects(never());

    AT_VcomCmdStreamEcho(ucIndex,pData,usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_VcomCmdStreamEcho, Test_AT_DisplayVcomInputData_002)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[4];
    VOS_UINT8                          *pData;
    VOS_UINT16                          usLen = 4;
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();
    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;

    pData = aucData;
    aucData[0] = 'A';
    aucData[1] = 'T';
    aucData[2] = ucAtS3;
    aucData[3] = ucAtS4;

    gucAtEType = AT_E_ECHO_CMD;

    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .with(eq(gastAtClientTab[ucIndex].ucPortNo), any(), eq((VOS_UINT32)(usLen - 1)))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_VcomCmdStreamEcho(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_VcomCmdStreamEcho, Test_AT_DisplayVcomInputData_003)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           aucData[3];
    VOS_UINT8                          *pData;
    VOS_UINT16                          usLen = 3;
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();
    *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;

    pData = aucData;
    aucData[0] = 'A';
    aucData[1] = 'T';
    aucData[2] = ucAtS3;

    gucAtEType = AT_E_ECHO_CMD;

    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .with(eq(gastAtClientTab[ucIndex].ucPortNo), any(), eq((VOS_UINT32)usLen))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_VcomCmdStreamEcho(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_UsbPcuiEst: public ::testing::Test
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


TEST_F(Test_At_UsbPcuiEst,Test_At_UsbPcuiEst_001)
{
    VOS_UINT32                          ulRslt;

    MOCKER(Sock_RecvCallbackRegister)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    /* 调用测试函数 */
    ulRslt = At_UsbPcuiEst(AT_USB_COM_PORT_NO);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CLIENT_ID_PCUI, gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].usClientId);
    EXPECT_EQ(AT_USB_COM_PORT_NO, gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].ucPortNo);
    EXPECT_EQ(AT_USBCOM_USER, gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType);
    EXPECT_EQ(AT_CLIENT_USED, gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].ucUsed);

    GlobalMockObject::verify();
}


TEST_F(Test_At_UsbPcuiEst,Test_At_UsbPcuiEst_002)
{
    VOS_UINT32                          ulRslt;

    /* 调用测试函数 */
    ulRslt = At_UsbPcuiEst(AT_CTR_PORT_NO);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


class Test_At_UsbCtrEst: public ::testing::Test
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


TEST_F(Test_At_UsbCtrEst,Test_At_UsbCtrEst_001)
{
    VOS_UINT32                          ulRslt;

    /*注册函数被调用*/
    MOCKER(DMS_ACMRecvFuncReg)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    /* 调用测试函数 */
    ulRslt = At_UsbCtrEst(AT_CTR_PORT_NO);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CLIENT_ID_CTRL, gastAtClientTab[AT_CLIENT_TAB_CTRL_INDEX].usClientId);
    EXPECT_EQ(AT_CTR_PORT_NO, gastAtClientTab[AT_CLIENT_TAB_CTRL_INDEX].ucPortNo);
    EXPECT_EQ(AT_CTR_USER, gastAtClientTab[AT_CLIENT_TAB_CTRL_INDEX].UserType);
    EXPECT_EQ(AT_CLIENT_USED, gastAtClientTab[AT_CLIENT_TAB_CTRL_INDEX].ucUsed);

    GlobalMockObject::verify();
}


TEST_F(Test_At_UsbCtrEst,Test_At_UsbCtrEst_002)
{
    VOS_UINT32                          ulRslt;

    /*注册函数被调用*/
    MOCKER(DMS_ACMRecvFuncReg)
        .expects(never());

    /* 调用测试函数 */
    ulRslt = At_UsbCtrEst(AT_USB_COM_PORT_NO);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_AppComEst: public ::testing::Test
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


TEST_F(Test_AT_AppComEst,Test_AT_AppComEst_001)
{
    VOS_UINT32                          ulRslt;

    /*注册函数被调用*/
    MOCKER(APP_VCOM_RegDataCallback)
        .expects(exactly(AT_VCOM_AT_CHANNEL_MAX))
        .will(returnValue((VOS_INT32)VOS_OK));

    /* 调用测试函数 */
    ulRslt = AT_AppComEst();

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CLIENT_ID_APP, gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].usClientId);
    EXPECT_EQ(APP_VCOM_DEV_INDEX_0, gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].ucPortNo);
    EXPECT_EQ(AT_APP_USER, gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].UserType);
    EXPECT_EQ(AT_CLIENT_USED, gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].ucUsed);

    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_WIFI)

class Test_AT_SockComEst: public ::testing::Test
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


TEST_F(Test_AT_SockComEst,Test_AT_SockComEst_001)
{
    VOS_UINT32                          ulRslt;

    /*注册函数被调用*/
    MOCKER(CPM_LogicRcvReg)
        .expects(exactly(1));

    /* 调用测试函数 */
    ulRslt = AT_SockComEst(AT_SOCK_PORT_NO);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CLIENT_ID_SOCK, gastAtClientTab[AT_CLIENT_TAB_SOCK_INDEX].usClientId);
    EXPECT_EQ(AT_SOCK_PORT_NO, gastAtClientTab[AT_CLIENT_TAB_SOCK_INDEX].ucPortNo);
    EXPECT_EQ(AT_SOCK_USER, gastAtClientTab[AT_CLIENT_TAB_SOCK_INDEX].UserType);
    EXPECT_EQ(AT_CLIENT_USED, gastAtClientTab[AT_CLIENT_TAB_SOCK_INDEX].ucUsed);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SockComEst,Test_AT_SockComEst_002)
{
    VOS_UINT32                          ulRslt;

    /*注册函数被调用*/
    MOCKER(App_VcomRecvCallbackRegister)
        .expects(never());

    /* 调用测试函数 */
    ulRslt = AT_SockComEst(AT_CTR_PORT_NO);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_AppSockComEst: public ::testing::Test
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


TEST_F(Test_AT_AppSockComEst,Test_AT_AppSockComEst_001)
{
    VOS_UINT32                          ulRslt;

    /*注册函数被调用*/
    MOCKER(App_VcomRecvCallbackRegister)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    /* 调用测试函数 */
    ulRslt = AT_AppSockComEst(AT_APP_SOCK_PORT_NO);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CLIENT_ID_APPSOCK, gastAtClientTab[AT_CLIENT_TAB_APPSOCK_INDEX].usClientId);
    EXPECT_EQ(AT_APP_SOCK_PORT_NO, gastAtClientTab[AT_CLIENT_TAB_APPSOCK_INDEX].ucPortNo);
    EXPECT_EQ(AT_APP_SOCK_USER, gastAtClientTab[AT_CLIENT_TAB_APPSOCK_INDEX].UserType);
    EXPECT_EQ(AT_CLIENT_USED, gastAtClientTab[AT_CLIENT_TAB_APPSOCK_INDEX].ucUsed);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_AppSockComEst,Test_AT_AppSockComEst_002)
{
    VOS_UINT32                          ulRslt;

    /*注册函数被调用*/
    MOCKER(App_VcomRecvCallbackRegister)
        .expects(never());

    /* 调用测试函数 */
    ulRslt = AT_AppSockComEst(AT_CTR_PORT_NO);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}
#endif


class Test_AT_UsbCtrlBrkReqCB: public ::testing::Test
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


TEST_F(Test_AT_UsbCtrlBrkReqCB,Test_AT_UsbCtrlBrkReqCB_001)
{
    VOS_INT                             lRet;

    MOCKER(AT_NdisCheckPdpIdleState)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(TAF_PS_CallEnd)
        .expects(never());

    /* 调用测试函数 */
    lRet = AT_UsbCtrlBrkReqCB();

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, lRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbCtrlBrkReqCB,Test_AT_UsbCtrlBrkReqCB_002)
{
    VOS_INT                             lRet;

    g_stAtNdisDhcpPara.enIpv4v6State = AT_PDP_STATE_BUTT;
    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_ACTED;

    MOCKER(AT_NdisCheckPdpIdleState)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_NdisSetState)
        .expects(exactly(2));

    /* 调用测试函数 */
    lRet = AT_UsbCtrlBrkReqCB();

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, lRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbCtrlBrkReqCB,Test_AT_UsbCtrlBrkReqCB_003)
{
    VOS_INT                             lRet;

    g_stAtNdisDhcpPara.enIpv4v6State = AT_PDP_STATE_ACTED;
    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_BUTT;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_ACTED;

    MOCKER(AT_NdisCheckPdpIdleState)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_NdisSetState)
        .expects(exactly(1));

    /* 调用测试函数 */
    lRet = AT_UsbCtrlBrkReqCB();

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, lRet);

    GlobalMockObject::verify();
}


class Test_AT_NdisEst: public ::testing::Test
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


TEST_F(Test_AT_NdisEst,Test_AT_NdisEst_001)
{
    VOS_UINT32                          ulRslt;

    /* 调用测试函数 */
    ulRslt = AT_UsbNdisEst();

    /* 检查预期结果 */
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CLIENT_ID_NDIS, gastAtClientTab[AT_CLIENT_TAB_NDIS_INDEX].usClientId);
    EXPECT_EQ(AT_NDIS_PORT_NO, gastAtClientTab[AT_CLIENT_TAB_NDIS_INDEX].ucPortNo);
    EXPECT_EQ(AT_NDIS_USER, gastAtClientTab[AT_CLIENT_TAB_NDIS_INDEX].UserType);
    EXPECT_EQ(AT_CLIENT_USED, gastAtClientTab[AT_CLIENT_TAB_NDIS_INDEX].ucUsed);

    GlobalMockObject::verify();
}


class Test_At_DataStreamPreProc: public ::testing::Test
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


TEST_F(Test_At_DataStreamPreProc,Test_At_DataStreamPreProc_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDataMode;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRet;

    ucIndex    = AT_CLIENT_ID_CTRL;
    ucDataMode = AT_DIAG_DATA_MODE;
    usLen      = 5;

    memcpy(aucData, "abcd", usLen);

    MOCKER(At_OmDataProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = At_DataStreamPreProc(ucIndex, ucDataMode, aucData, usLen);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_DataStreamPreProc,Test_At_DataStreamPreProc_002)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDataMode;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRet;

    ucIndex    = AT_CLIENT_ID_CTRL;
    ucDataMode = AT_OM_DATA_MODE;
    usLen      = 5;

    memcpy(aucData, "abcd", usLen);

    MOCKER(At_OmDataProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = At_DataStreamPreProc(ucIndex, ucDataMode, aucData, usLen);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_DataStreamPreProc,Test_At_DataStreamPreProc_003)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDataMode;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRet;

    ucIndex    = AT_CLIENT_ID_CTRL;
    ucDataMode = AT_CSD_DATA_MODE;
    usLen      = 5;

    memcpy(aucData, "abcd", usLen);

    MOCKER(At_OmDataProc)
        .expects(never());

    ulRet = At_DataStreamPreProc(ucIndex, ucDataMode, aucData, usLen);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_DataStreamPreProc,Test_At_DataStreamPreProc_004)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDataMode;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRet;

    ucIndex    = AT_CLIENT_ID_CTRL;
    ucDataMode = AT_DATA_BUTT_MODE;
    usLen      = 5;

    memcpy(aucData, "abcd", usLen);

    MOCKER(At_OmDataProc)
        .expects(never());

    ulRet = At_DataStreamPreProc(ucIndex, ucDataMode, aucData, usLen);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


class Test_At_OmDataProc: public ::testing::Test
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

VOS_UINT32 AT_UART_RcvFunc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    return VOS_OK;
}

VOS_UINT32 AT_PCUI_RcvFunc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    return VOS_OK;
}

VOS_UINT32 AT_CTR_RcvFunc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    return VOS_OK;
}


TEST_F(Test_At_OmDataProc,Test_At_OmDataProc_001)
{
    VOS_UINT8                           ucPortNo;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRslt;

    ucPortNo = AT_UART_PORT_NO;
    usLen = 5;
    memcpy(aucData, "abcd", usLen);

    g_apAtPortDataRcvFuncTab[AT_UART_PORT] = VOS_NULL_PTR;

    ulRslt = At_OmDataProc(ucPortNo, aucData, usLen);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}



TEST_F(Test_At_OmDataProc,Test_At_OmDataProc_002)
{
    VOS_UINT8                           ucPortNo;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRslt;

    ucPortNo = AT_UART_PORT_NO;
    usLen = 5;
    memcpy(aucData, "abcd", usLen);

    g_apAtPortDataRcvFuncTab[AT_UART_PORT] = AT_UART_RcvFunc;

    ulRslt = At_OmDataProc(ucPortNo, aucData, usLen);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_At_OmDataProc,Test_At_OmDataProc_003)
{
    VOS_UINT8                           ucPortNo;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRslt;

    ucPortNo = AT_USB_COM_PORT_NO;
    usLen = 5;
    memcpy(aucData, "abcd", usLen);

    g_apAtPortDataRcvFuncTab[AT_PCUI_PORT] = VOS_NULL_PTR;

    ulRslt = At_OmDataProc(ucPortNo, aucData, usLen);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}



TEST_F(Test_At_OmDataProc,Test_At_OmDataProc_004)
{
    VOS_UINT8                           ucPortNo;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRslt;

    ucPortNo = AT_USB_COM_PORT_NO;
    usLen = 5;
    memcpy(aucData, "abcd", usLen);

    g_apAtPortDataRcvFuncTab[AT_PCUI_PORT] = AT_PCUI_RcvFunc;

    ulRslt = At_OmDataProc(ucPortNo, aucData, usLen);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_At_OmDataProc,Test_At_OmDataProc_005)
{
    VOS_UINT8                           ucPortNo;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRslt;

    ucPortNo = AT_CTR_PORT_NO;
    usLen = 5;
    memcpy(aucData, "abcd", usLen);

    g_apAtPortDataRcvFuncTab[AT_CTRL_PORT] = VOS_NULL_PTR;

    ulRslt = At_OmDataProc(ucPortNo, aucData, usLen);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}



TEST_F(Test_At_OmDataProc,Test_At_OmDataProc_006)
{
    VOS_UINT8                           ucPortNo;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRslt;

    ucPortNo = AT_CTR_PORT_NO;
    usLen = 5;
    memcpy(aucData, "abcd", usLen);

    g_apAtPortDataRcvFuncTab[AT_CTRL_PORT] = AT_CTR_RcvFunc;

    ulRslt = At_OmDataProc(ucPortNo, aucData, usLen);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_At_OmDataProc,Test_At_OmDataProc_007)
{
    VOS_UINT8                           ucPortNo;
    VOS_UINT8                           aucData[5];
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulRslt;

    ucPortNo = AT_APP_PORT_NO;
    usLen = 5;
    memcpy(aucData, "abcd", usLen);

    g_apAtPortDataRcvFuncTab[AT_CTRL_PORT] = AT_CTR_RcvFunc;

    ulRslt = At_OmDataProc(ucPortNo, aucData, usLen);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_QuerySndFunc: public ::testing::Test
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


TEST_F(Test_AT_QuerySndFunc,Test_AT_QuerySndFunc_001)
{
    CPM_SEND_FUNC                       pCpmFunc;

    pCpmFunc = AT_QuerySndFunc(AT_UART_PORT);

    EXPECT_EQ(AT_UART_SendRawDataFromOm, pCpmFunc);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QuerySndFunc,Test_AT_QuerySndFunc_002)
{
    CPM_SEND_FUNC                       pCpmFunc;

    pCpmFunc = AT_QuerySndFunc(AT_PCUI_PORT);

    EXPECT_EQ(AT_SendPcuiDataFromOm, pCpmFunc);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QuerySndFunc,Test_AT_QuerySndFunc_003)
{
    CPM_SEND_FUNC                       pCpmFunc;

    pCpmFunc = AT_QuerySndFunc(AT_CTRL_PORT);

    EXPECT_EQ(AT_SendCtrlDataFromOm, pCpmFunc);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QuerySndFunc,Test_AT_QuerySndFunc_004)
{
    CPM_SEND_FUNC                       pCpmFunc;

    pCpmFunc = AT_QuerySndFunc(AT_PORT_BUTT);

    EXPECT_EQ(VOS_NULL_PTR, pCpmFunc);

    GlobalMockObject::verify();
}


class Test_AT_SendPcuiDataFromOm: public ::testing::Test
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


TEST_F(Test_AT_SendPcuiDataFromOm,Test_AT_SendPcuiDataFromOm_001)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT32                          ulLen;

    ulLen = 5;

    memcpy(aucData, "abcd", ulLen);

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].DataMode = AT_OM_DATA_MODE;

    MOCKER(At_SendData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_PCUI_INDEX), eq((VOS_UINT8)AT_OM_DATA_MODE), any(), any())
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRslt = AT_SendPcuiDataFromOm(aucData, VOS_NULL_PTR, ulLen);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendPcuiDataFromOm,Test_AT_SendPcuiDataFromOm_002)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT32                          ulLen;

    ulLen = 5;

    memcpy(aucData, "abcd", ulLen);

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].DataMode = AT_OM_DATA_MODE;

    MOCKER(At_SendData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_PCUI_INDEX), eq((VOS_UINT8)AT_OM_DATA_MODE), any(), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRslt = AT_SendPcuiDataFromOm(aucData, VOS_NULL_PTR, ulLen);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_SendCtrlDataFromOm: public ::testing::Test
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


TEST_F(Test_AT_SendCtrlDataFromOm,Test_AT_SendCtrlDataFromOm_001)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT32                          ulLen;

    ulLen = 5;

    memcpy(aucData, "abcd", ulLen);

    gastAtClientTab[AT_CLIENT_TAB_CTRL_INDEX].DataMode = AT_OM_DATA_MODE;

    MOCKER(At_SendData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_CTRL_INDEX), eq((VOS_UINT8)AT_OM_DATA_MODE), any(), any())
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRslt = AT_SendCtrlDataFromOm(aucData, VOS_NULL_PTR, ulLen);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendCtrlDataFromOm,Test_AT_SendCtrlDataFromOm_002)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT32                          ulLen;

    ulLen = 5;

    memcpy(aucData, "abcd", ulLen);

    gastAtClientTab[AT_CLIENT_TAB_CTRL_INDEX].DataMode = AT_OM_DATA_MODE;

    MOCKER(At_SendData)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_CTRL_INDEX), eq((VOS_UINT8)AT_OM_DATA_MODE), any(), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRslt = AT_SendCtrlDataFromOm(aucData, VOS_NULL_PTR, ulLen);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_DiscardInvalidCharForSms: public ::testing::Test
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

TEST_F(Test_AT_DiscardInvalidCharForSms,Test_AT_DiscardInvalidCharForSms_01)
{
    TAF_UINT8       aucData[50];
    TAF_UINT16      usLen = 3;

    //相关全局变量初始化

    //MOCKER
    MOCKER(VOS_StrCmp)
        .expects(never());

    MOCKER(V_MemCpy)
        .expects(never());

    //调用被测函数
    AT_DiscardInvalidCharForSms(aucData, &usLen);

    //执行检查
    EXPECT_EQ(3, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DiscardInvalidCharForSms,Test_AT_DiscardInvalidCharForSms_02)
{
    TAF_UINT8       aucData[] = "AT+CMGF=1";
    TAF_UINT16      usLen;

    //相关全局变量初始化
    usLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucData);;

    //MOCKER

    //调用被测函数
    AT_DiscardInvalidCharForSms(aucData, &usLen);

    //执行检查
    EXPECT_EQ(9, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DiscardInvalidCharForSms,Test_AT_DiscardInvalidCharForSms_03)
{
    TAF_UINT8       aucData[] = "AT+CMGS=15\x0d\x1aZ";
    TAF_UINT16      usLen;

    //相关全局变量初始化
    ucAtS3 = 13;
    ucAtS4 = 10;
    usLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucData);;

    //MOCKER

    //调用被测函数
    AT_DiscardInvalidCharForSms(aucData, &usLen);

    //执行检查
    EXPECT_EQ(11, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DiscardInvalidCharForSms,Test_AT_DiscardInvalidCharForSms_04)
{
    TAF_UINT8       aucData[] = "AT+CMGS=15\x0d\x1az";
    TAF_UINT16      usLen;

    //相关全局变量初始化
    ucAtS3 = 13;
    ucAtS4 = 10;
    usLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucData);;

    //MOCKER

    //调用被测函数
    AT_DiscardInvalidCharForSms(aucData, &usLen);

    //执行检查
    EXPECT_EQ(11, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DiscardInvalidCharForSms,Test_AT_DiscardInvalidCharForSms_05)
{
    TAF_UINT8       aucData[] = "AT+CMGS=15\x0d\x0a\x0d";
    TAF_UINT16      usLen;

    //相关全局变量初始化
    ucAtS3 = 13;
    ucAtS4 = 10;
    usLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucData);;

    //MOCKER

    //调用被测函数
    AT_DiscardInvalidCharForSms(aucData, &usLen);

    //执行检查
    EXPECT_EQ(11, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DiscardInvalidCharForSms,Test_AT_DiscardInvalidCharForSms_06)
{
    TAF_UINT8       aucData[] = "AT+CMGS=15\x0d";
    TAF_UINT16      usLen;

    //相关全局变量初始化
    ucAtS3 = 13;
    ucAtS4 = 10;
    usLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucData);;

    //MOCKER

    //调用被测函数
    AT_DiscardInvalidCharForSms(aucData, &usLen);

    //执行检查
    EXPECT_EQ(11, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_DiscardInvalidCharForSms,Test_AT_DiscardInvalidCharForSms_07)
{
    TAF_UINT8       aucData[] = "AT+CMGS=15\x0d\x0a";
    TAF_UINT16      usLen;

    //相关全局变量初始化
    ucAtS3 = 13;
    ucAtS4 = 10;
    usLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucData);;

    //MOCKER

    //调用被测函数
    AT_DiscardInvalidCharForSms(aucData, &usLen);

    //执行检查
    EXPECT_EQ(11, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_CsdDataModeRcvModemMsc: public ::testing::Test
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


TEST_F(Test_AT_CsdDataModeRcvModemMsc,Test_AT_CsdDataModeRcvModemMsc_001)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucCallNum;
    TAFAGERNT_MN_CALL_INFO_STRU         astCallInfos[MN_CALL_MAX_NUM] = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    ucCallNum = 1;

    astCallInfos[0].callId              = 1;
    astCallInfos[0].enCallType          = MN_CALL_TYPE_VIDEO;
    astCallInfos[0].enCallState         = MN_CALL_S_ACTIVE;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;

    // MOCKER操作
    MOCKER(TAF_AGENT_GetCallInfoReq)
        .stubs()
        .with(any(),
              outBoundP(&ucCallNum),
              outBoundP(astCallInfos, sizeof(TAFAGERNT_MN_CALL_INFO_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(MN_CALL_End)
        .expects(exactly(1))
        .with(any(), any(), eq(astCallInfos[0].callId), any())
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRslt = AT_CsdDataModeRcvModemMsc(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);
    EXPECT_EQ(AT_CMD_END_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_CsdDataModeRcvModemMsc,Test_AT_CsdDataModeRcvModemMsc_002)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucCallNum;
    TAFAGERNT_MN_CALL_INFO_STRU         astCallInfos[MN_CALL_MAX_NUM] = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    ucCallNum = 1;

    astCallInfos[0].callId              = 1;
    astCallInfos[0].enCallType          = MN_CALL_TYPE_VIDEO;
    astCallInfos[0].enCallState         = MN_CALL_S_ACTIVE;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;

    // MOCKER操作
    MOCKER(TAF_AGENT_GetCallInfoReq)
        .stubs()
        .with(any(),
              outBoundP(&ucCallNum),
              outBoundP(astCallInfos, sizeof(TAFAGERNT_MN_CALL_INFO_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(MN_CALL_End)
        .expects(exactly(1))
        .with(any(), any(), eq(astCallInfos[0].callId), any())
        .will(returnValue((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRslt = AT_CsdDataModeRcvModemMsc(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    EXPECT_EQ(AT_CMD_H_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_CsdDataModeRcvModemMsc,Test_AT_CsdDataModeRcvModemMsc_003)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucCallNum;
    TAFAGERNT_MN_CALL_INFO_STRU         astCallInfos[MN_CALL_MAX_NUM] = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    ucCallNum = 1;

    astCallInfos[0].callId              = 1;
    astCallInfos[0].enCallType          = MN_CALL_TYPE_VIDEO;
    astCallInfos[0].enCallState         = MN_CALL_S_ACTIVE;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_END_SET;

    // MOCKER操作
    MOCKER(TAF_AGENT_GetCallInfoReq)
        .stubs()
        .with(any(),
              outBoundP(&ucCallNum),
              outBoundP(astCallInfos, sizeof(TAFAGERNT_MN_CALL_INFO_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(MN_CALL_End)
        .expects(never());

    // 调用被测函数
    ulRslt = AT_CsdDataModeRcvModemMsc(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRslt);
    EXPECT_EQ(AT_CMD_END_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_CsdDataModeRcvModemMsc,Test_AT_CsdDataModeRcvModemMsc_004)
{
    // 参数定义
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucCallNum;
    TAFAGERNT_MN_CALL_INFO_STRU         astCallInfos[MN_CALL_MAX_NUM] = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_APP_INDEX;
    ucCallNum = 1;

    astCallInfos[0].callId              = 1;
    astCallInfos[0].enCallType          = MN_CALL_TYPE_VOICE;
    astCallInfos[0].enCallState         = MN_CALL_S_ACTIVE;

    // 相关全局变量初始化
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;

    // MOCKER操作
    MOCKER(TAF_AGENT_GetCallInfoReq)
        .stubs()
        .with(any(),
              outBoundP(&ucCallNum),
              outBoundP(astCallInfos, sizeof(TAFAGERNT_MN_CALL_INFO_STRU)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(MN_CALL_End)
        .expects(never());

    // 调用被测函数
    ulRslt = AT_CsdDataModeRcvModemMsc(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_UNKNOWN, ulRslt);
    EXPECT_EQ(AT_CMD_H_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RcvFromSock: public ::testing::Test
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

TEST_F(Test_AT_RcvFromSock, Test_AT_RcvFromSock_01)
{
    /* 输入pData为VOS_NULL_PTR */
    ASSERT_EQ(VOS_ERR, AT_RcvFromSock(VOS_NULL_PTR, 0));
}


TEST_F(Test_AT_RcvFromSock,Test_AT_RcvFromSock_02)
{
    VOS_UINT8                           aucData[1];

    /* 输入uslength为0 */
    ASSERT_EQ(VOS_ERR, AT_RcvFromSock(aucData, 0));
}


TEST_F(Test_AT_RcvFromSock,Test_AT_RcvFromSock_03)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[1];

    ucIndex = AT_CLIENT_TAB_SOCK_INDEX;

    gastAtClientTab[ucIndex].UserType   = AT_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_NULL;

    ASSERT_EQ(VOS_ERR, AT_RcvFromSock(aucData, 1));
}


TEST_F(Test_AT_RcvFromSock, Test_AT_RcvFromSock_04)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[1];

    ucIndex                             = AT_CLIENT_TAB_SOCK_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortNo   = AT_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].Mode       = AT_CMD_MODE;

    MOCKER(At_CmdStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    /* uslength 不为SCSI_CMD_LEN */
    ASSERT_EQ(VOS_ERR, AT_RcvFromSock(aucData, 1));
}


TEST_F(Test_AT_RcvFromSock, Test_AT_RcvFromSock_05)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[1];

    ucIndex                             = AT_CLIENT_TAB_SOCK_INDEX;
    gastAtClientTab[ucIndex].UserType   = AT_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].ucPortNo   = AT_SOCK_PORT_NO;
    /* 非AT_CMD_MODE模式 */
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;

    MOCKER(At_DataStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    /* uslength 不为SCSI_CMD_LEN */
    ASSERT_EQ(VOS_OK, AT_RcvFromSock(aucData, 1));
}


class Test_AT_GetAtMsgStruMsgLength: public ::testing::Test
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


TEST_F(Test_AT_GetAtMsgStruMsgLength, Test_AT_GetAtMsgStruMsgLength_01)
{
    VOS_UINT32                         ulMsgLength;

    AT_GetAtMsgStruMsgLength(3, &ulMsgLength);

    EXPECT_EQ(16, ulMsgLength);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetAtMsgStruMsgLength, Test_AT_GetAtMsgStruMsgLength_02)
{
    VOS_UINT32                         ulMsgLength;

    AT_GetAtMsgStruMsgLength(6, &ulMsgLength);

    EXPECT_EQ(18, ulMsgLength);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_GetUserTypeFromIndex: public ::testing::Test
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


TEST_F(Test_AT_GetUserTypeFromIndex, Test_AT_GetUserTypeFromIndex_01)
{
    VOS_UINT8                          ucUserType;

    AT_GetUserTypeFromIndex(AT_MAX_CLIENT_NUM, &ucUserType);

    EXPECT_EQ(AT_BUTT_USER, ucUserType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetUserTypeFromIndex, Test_AT_GetUserTypeFromIndex_02)
{
    VOS_UINT8                          ucUserType;

    gastAtClientTab[AT_CLIENT_ID_PCUI].UserType = AT_USBCOM_USER;

    AT_GetUserTypeFromIndex(AT_CLIENT_ID_PCUI, &ucUserType);

    EXPECT_EQ(AT_USBCOM_USER, ucUserType);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_SendCmdMsg: public ::testing::Test
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


TEST_F(Test_At_SendCmdMsg, Test_At_SendCmdMsg_01)
{
    TAF_UINT8           ucIndex     = 0;
    TAF_UINT8          *pData       = VOS_NULL_PTR;
    TAF_UINT16          usLen       = 0;
    TAF_UINT8           ucType      = 0;
    VOS_UINT32          ulRet;

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    ulRet = At_SendCmdMsg(ucIndex, pData, usLen, ucType);

    EXPECT_EQ(AT_FAILURE, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendCmdMsg, Test_At_SendCmdMsg_02)
{
    TAF_UINT8           ucIndex         = 0;
    TAF_UINT8           aucCmdString[]  = "at+cimi";
    TAF_UINT8          *pData           = VOS_NULL_PTR;
    TAF_UINT16          usLen           = 0;
    TAF_UINT8           ucType          = 0;
    VOS_UINT32          ulRet;

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    pData = aucCmdString;

    ulRet = At_SendCmdMsg(ucIndex, pData, usLen, ucType);

    EXPECT_EQ(AT_FAILURE, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendCmdMsg, Test_At_SendCmdMsg_03)
{
    TAF_UINT8           ucIndex         = 0;
    TAF_UINT8           aucCmdString[]  = "at+cimi";
    TAF_UINT8          *pData           = VOS_NULL_PTR;
    TAF_UINT16          usLen           = AT_COM_BUFF_LEN + 1;
    TAF_UINT8           ucType = 0;
    VOS_UINT32          ulRet;

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    pData = aucCmdString;

    ulRet = At_SendCmdMsg(ucIndex, pData, usLen, ucType);

    EXPECT_EQ(AT_FAILURE, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendCmdMsg, Test_At_SendCmdMsg_04)
{
    TAF_UINT8           ucIndex         = 0;
    TAF_UINT8           aucCmdString[]  = "at+cimi";
    TAF_UINT8          *pData           = VOS_NULL_PTR;
    TAF_UINT16          usLen;
    TAF_UINT8           ucType          = 0;
    VOS_UINT32          ulRet;

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    ulRet = At_SendCmdMsg(ucIndex, pData, usLen, ucType);

    EXPECT_EQ(AT_FAILURE, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendCmdMsg, Test_At_SendCmdMsg_05)
{
    TAF_UINT8           ucIndex         = 0;
    TAF_UINT8           aucCmdString[]  = "at+cimi";
    TAF_UINT8          *pData           = VOS_NULL_PTR;
    TAF_UINT16          usLen;
    TAF_UINT8           ucType          = 0;
    VOS_UINT32          ulRet;

    MOCKER(DIAG_LogReport)
        .expects(exactly(1));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(invoke(UT_Ps_SendMsgFail));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    ulRet = At_SendCmdMsg(ucIndex, pData, usLen, ucType);

    EXPECT_EQ(AT_FAILURE, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendCmdMsg, Test_At_SendCmdMsg_06)
{
    TAF_UINT8                           ucIndex         = 0;
    TAF_UINT8                           aucCmdString[]  = "at+cimi";
    TAF_UINT8                          *pData           = VOS_NULL_PTR;
    TAF_UINT16                          usLen;
    TAF_UINT8                           ucType          = 0;
    VOS_UINT32                          ulRet;

    MOCKER(DIAG_LogReport)
        .expects(never());

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    ulRet = At_SendCmdMsg(ucIndex, pData, usLen, ucType);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_At_RcvFromUsbCom: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_ulAtUsbDebugFlag                  = VOS_FALSE;

    }
    void TearDown()
    {

    }
};

#if (FEATURE_ON == FEATURE_AT_HSIC)

TEST_F(Test_At_RcvFromUsbCom, Test_At_RcvFromUsbCom_001)
{
    VOS_UINT8       ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;
    VOS_UINT8       *pData;
    VOS_UINT16      usLen = 4;
    VOS_INT32       lResult;
    VOS_UINT8       ucPortNo = AT_HSIC1_PORT_NO;

    pData = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);

    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].Mode       = AT_CMD_MODE;
    gastAtClientTab[ucIndex].ucPortNo   = AT_HSIC1_PORT_NO;

    MOCKER(At_CmdStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    lResult = At_RcvFromUsbCom(ucPortNo, pData, usLen);

    EXPECT_EQ(AT_DRV_SUCCESS, lResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_At_RcvFromUsbCom, Test_At_RcvFromUsbCom_002)
{
    VOS_UINT8       ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT8       *pData;
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucPortNo = AT_USB_COM_PORT_NO;

    pData = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);

    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].ucUsed   = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].Mode  = AT_CMD_MODE;

    gastAtClientTab[ucIndex].ucPortNo = AT_USB_COM_PORT_NO;

    MOCKER(At_CmdStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));


    ulResult = At_RcvFromUsbCom(ucPortNo, pData, usLen);

    EXPECT_EQ(AT_DRV_SUCCESS,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_RcvFromAppCom: public ::testing::Test
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


TEST_F(Test_AT_RcvFromAppCom, Test_AT_RcvFromAppCom_001)
{
    VOS_UINT8       aucData[4];
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucVcomId;

    ucVcomId = AT_VCOM_AT_CHANNEL_MAX;

    ulResult = AT_RcvFromAppCom(ucVcomId, aucData, usLen);

    EXPECT_EQ(VOS_ERR,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvFromAppCom, Test_AT_RcvFromAppCom_002)
{
    VOS_UINT8       *pData;
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucVcomId;

    ucVcomId = APP_VCOM_DEV_INDEX_1;
    pData = VOS_NULL_PTR;

    ulResult = AT_RcvFromAppCom(ucVcomId, pData, usLen);

    EXPECT_EQ(VOS_ERR,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvFromAppCom, Test_AT_RcvFromAppCom_003)
{
    VOS_UINT8       aucData[4];
    VOS_UINT16      usLen = 0;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucVcomId;

    ucVcomId = APP_VCOM_DEV_INDEX_1;

    ulResult = AT_RcvFromAppCom(ucVcomId, aucData, usLen);

    EXPECT_EQ(VOS_ERR,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvFromAppCom, Test_AT_RcvFromAppCom_004)
{
    VOS_UINT8       ucIndex;
    VOS_UINT8       aucData[4];
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucVcomId = APP_VCOM_DEV_INDEX_1;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_NDIS_USER;
    gastAtClientTab[ucIndex].ucUsed   = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].Mode  = AT_CMD_MODE;

    ulResult = AT_RcvFromAppCom(ucVcomId, aucData, usLen);

    EXPECT_EQ(VOS_ERR,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvFromAppCom, Test_AT_RcvFromAppCom_005)
{
    VOS_UINT8       ucIndex;
    VOS_UINT8       aucData[4];
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucVcomId = APP_VCOM_DEV_INDEX_1;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;
    gastAtClientTab[ucIndex].ucUsed   = AT_CLIENT_NULL;

    gastAtClientTab[ucIndex].Mode  = AT_CMD_MODE;

    ulResult = AT_RcvFromAppCom(ucVcomId, aucData, usLen);

    EXPECT_EQ(VOS_ERR,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvFromAppCom, Test_AT_RcvFromAppCom_006)
{
    VOS_UINT8       ucIndex;
    VOS_UINT8       aucData[4];
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucVcomId = APP_VCOM_DEV_INDEX_1;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;
    gastAtClientTab[ucIndex].ucUsed   = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].Mode     = AT_CMD_MODE;

    MOCKER(At_CmdStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulResult = AT_RcvFromAppCom(ucVcomId, aucData, usLen);

    EXPECT_EQ(VOS_OK,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvFromAppCom, Test_AT_RcvFromAppCom_007)
{
    VOS_UINT8       ucIndex;
    VOS_UINT8       aucData[4];
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucVcomId = APP_VCOM_DEV_INDEX_1;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;
    gastAtClientTab[ucIndex].ucUsed   = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].Mode     = AT_DATA_MODE;

    MOCKER(At_DataStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulResult = AT_RcvFromAppCom(ucVcomId, aucData, usLen);

    EXPECT_EQ(VOS_ERR,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvFromAppCom, Test_AT_RcvFromAppCom_008)
{
    VOS_UINT8       ucIndex;
    VOS_UINT8       aucData[4];
    VOS_UINT16      usLen = 4;
    VOS_UINT32      ulResult;
    VOS_UINT8       ucVcomId = APP_VCOM_DEV_INDEX_1;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;
    gastAtClientTab[ucIndex].ucUsed   = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].Mode  = AT_DATA_MODE;

    MOCKER(At_DataStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulResult = AT_RcvFromAppCom(ucVcomId, aucData, usLen);

    EXPECT_EQ(VOS_OK,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)

class Test_AT_HsicInit: public ::testing::Test
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


TEST_F(Test_AT_HsicInit, 打开UDI设备失败)
{
    VOS_UINT32  ulResult;

    // 参数初始化

    // MOCKER操作;
    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(UDI_INVALID_HANDLE));


    // 调用被测函数
    ulResult = AT_HsicInit();

    // 执行检查
    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicInit: public ::testing::Test
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

TEST_F(Test_AT_HsicInit, Test_AT_HsicInit_01)
{
    VOS_UINT32  ulResult;

    // 参数初始化

    // MOCKER操作;
    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    ulResult = AT_HsicInit();

    // 执行检查
    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicInit, Test_AT_HsicInit_02)
{
    VOS_UINT32  ulResult;

    // 参数初始化

    // MOCKER操作;
    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnObjectList(VOS_OK,VOS_ERR));

    // 调用被测函数
    ulResult = AT_HsicInit();

    // 执行检查
    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicInit, Test_AT_HsicInit_03)
{
    VOS_UINT32  ulResult;

    // 参数初始化

    // MOCKER操作;
    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnObjectList(VOS_OK,VOS_OK));

    MOCKER(AT_HsicInitUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));


    // 调用被测函数
    ulResult = AT_HsicInit();

    // 执行检查
    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicInit, Test_AT_HsicInit_04)
{

    // 参数初始化
    VOS_UINT32  ulResult;

    // MOCKER操作;
    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnObjectList(VOS_OK,VOS_OK));

    MOCKER(AT_HsicInitUlDataBuf)
        .expects(never())AT_HSIC_AT_CHANNEL_MAX);

    MOCKER(AT_HsicEst)
        .expects(never())AT_HSIC_AT_CHANNEL_MAX);

    // 调用被测函数
    ulResult = AT_HsicInit();

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicInit, Test_AT_HsicInit_06)
{

    // 参数初始化
    VOS_UINT32  ulResult;

    // MOCKER操作;
    MOCKER(mdrv_misc_support_check)
        .will(returnValue(BSP_MODULE_UNSUPPORT));

    MOCKER(AT_HsicInitUlDataBuf)
        .expects(never());

    MOCKER(AT_HsicEst)
        .expects(never());

    // 调用被测函数
    ulResult = AT_HsicInit();

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicEst: public ::testing::Test
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


TEST_F(Test_AT_HsicEst, Test_AT_HsicEst_01)
{
    VOS_UINT32  ulResult;

    // 调用被测函数
    ulResult = AT_HsicEst(AT_HSIC_AT_CHANNEL_INDEX_ONE);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicOneReadDataCB: public ::testing::Test
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


TEST_F(Test_AT_HsicOneReadDataCB, Test_AT_HsicOneReadDataCB_01)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));

    MOCKER(At_RcvFromUsbCom)
        .expects(never());

    // 调用被测函数
    AT_HsicOneReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicOneReadDataCB, Test_AT_HsicOneReadDataCB_02)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_HsicFreeUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));

    MOCKER(At_RcvFromUsbCom)
        .expects(exactly(1));


    // 调用被测函数
    AT_HsicOneReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicOneReadDataCB, Test_AT_HsicOneReadDataCB_03)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_HsicFreeUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(At_RcvFromUsbCom)
        .expects(exactly(1));


    // 调用被测函数
    AT_HsicOneReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicTwoReadDataCB: public ::testing::Test
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


TEST_F(Test_AT_HsicTwoReadDataCB, Test_AT_HsicTwoReadDataCB_01)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));

    MOCKER(At_RcvFromUsbCom)
        .expects(never());

    // 调用被测函数
    AT_HsicTwoReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicTwoReadDataCB, Test_AT_HsicTwoReadDataCB_02)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_HsicFreeUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));

    MOCKER(At_RcvFromUsbCom)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicTwoReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicTwoReadDataCB, Test_AT_HsicTwoReadDataCB_03)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_HsicFreeUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(At_RcvFromUsbCom)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicTwoReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicThreeReadDataCB: public ::testing::Test
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


TEST_F(Test_AT_HsicThreeReadDataCB, Test_AT_HsicThreeReadDataCB_01)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));

    MOCKER(At_RcvFromUsbCom)
        .expects(never());

    // 调用被测函数
    AT_HsicThreeReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicThreeReadDataCB, Test_AT_HsicThreeReadDataCB_02)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_HsicFreeUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));

    MOCKER(At_RcvFromUsbCom)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicThreeReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicThreeReadDataCB, Test_AT_HsicThreeReadDataCB_03)
{

    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_HsicFreeUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(At_RcvFromUsbCom)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicThreeReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicOneFreeDlDataBuf: public ::testing::Test
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


TEST_F(Test_AT_HsicOneFreeDlDataBuf, Test_AT_HsicOneFreeDlDataBuf_01)
{
    VOS_UINT8   ucData[10];

    MOCKER(BSP_Free)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicOneFreeDlDataBuf(ucData);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicTwoFreeDlDataBuf, Test_AT_HsicOneFreeDlDataBuf_02)
{
    VOS_UINT8   ucData[10];

    MOCKER(BSP_Free)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicTwoFreeDlDataBuf(ucData);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_AT_HsicThreeFreeDlDataBuf, Test_AT_HsicOneFreeDlDataBuf_03)
{
    VOS_UINT8   ucData[10];

    MOCKER(BSP_Free)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicThreeFreeDlDataBuf(ucData);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicGetUlDataBuf: public ::testing::Test
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


TEST_F(Test_AT_HsicGetUlDataBuf, Test_AT_HsicGetUlDataBuf_01)
{
    VOS_UINT8 *pucdata;
    VOS_UINT32 ulLen;
    VOS_UINT32  ulResult;
    UDI_HANDLE  ulUdiHdl = 1;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    ulResult = AT_HsicGetUlDataBuf(ulUdiHdl , &pucdata, &ulLen);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

VOS_INT32 stub_udi_ioctl_1(VOS_INT32 handle, VOS_UINT32 u32Cmd, VOS_VOID* pParam)
{
    ACM_WR_ASYNC_INFO                   *pstCtlParam;

    pstCtlParam = (ACM_WR_ASYNC_INFO *)pParam;
    pstCtlParam->pVirAddr = VOS_NULL_PTR;

    return VOS_OK;
}



TEST_F(Test_AT_HsicGetUlDataBuf, Test_AT_HsicGetUlDataBuf_02)
{
    VOS_UINT8 *pucdata;
    VOS_UINT32 ulLen;
    VOS_UINT32  ulResult;
    UDI_HANDLE  ulUdiHdl = 1;

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(invoke(stub_udi_ioctl_1));


    // 调用被测函数
    ulResult = AT_HsicGetUlDataBuf(ulUdiHdl, &pucdata, &ulLen);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


VOS_INT32 stub_udi_ioctl_2(VOS_INT32 handle, VOS_UINT32 u32Cmd, VOS_VOID* pParam)
{
    ACM_WR_ASYNC_INFO                   *pstCtlParam;

    pstCtlParam = (ACM_WR_ASYNC_INFO *)pParam;

    pstCtlParam->pVirAddr = (VOS_CHAR *)0xFFFFFF00;
    pstCtlParam->u32Size = 1;

    return VOS_OK;
}


TEST_F(Test_AT_HsicGetUlDataBuf, Test_AT_HsicGetUlDataBuf_03)
{
    VOS_UINT8 *pucdata;
    VOS_UINT32 ulLen;
    VOS_UINT32  ulResult;
    UDI_HANDLE  ulUdiHdl = 1;


    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(invoke(stub_udi_ioctl_2));


    // 调用被测函数
    ulResult = AT_HsicGetUlDataBuf(ulUdiHdl, &pucdata, &ulLen);

    EXPECT_EQ(AT_SUCCESS ,ulResult);
    EXPECT_EQ((VOS_UINT32)pucdata ,0xFFFFFF00);
    EXPECT_EQ(ulLen,1);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_HsicFreeUlDataBuf: public ::testing::Test
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


TEST_F(Test_AT_HsicFreeUlDataBuf, Test_AT_HsicFreeUlDataBuf_01)
{
    VOS_UINT32                          ulResult;
    UDI_HANDLE                          ulUdiHdl = 1;
    VOS_UINT8                          *pucBuf;
    VOS_UINT32                          ulLen = 1;

    pucBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, ulLen);


    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_ERR));


    ulResult = AT_HsicFreeUlDataBuf(ulUdiHdl, pucBuf, ulLen);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicFreeUlDataBuf, Test_AT_HsicFreeUlDataBuf_02)
{
    VOS_UINT32                          ulResult;
    UDI_HANDLE                          ulUdiHdl = 1;
    VOS_UINT8                          *pucBuf;
    VOS_UINT32                          ulLen = 1;

    pucBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, ulLen);


    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_OK));


    ulResult = AT_HsicFreeUlDataBuf(ulUdiHdl, pucBuf, ulLen);

    EXPECT_EQ(AT_SUCCESS ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicInitUlDataBuf: public ::testing::Test
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


TEST_F(Test_AT_HsicInitUlDataBuf, Test_AT_HsicInitUlDataBuf_01)
{
    VOS_UINT32                          ulResult;
    UDI_HANDLE                          ulUdiHdl = 1;
    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    ulResult = AT_HsicInitUlDataBuf(ulUdiHdl,
                                    AT_HSIC_UL_DATA_BUFF_SIZE,
                                    AT_HSIC_UL_DATA_BUFF_NUM);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicInitUlDataBuf,Test_AT_HsicInitUlDataBuf_02)
{
    VOS_UINT32 ulResult;

    UDI_HANDLE                          ulUdiHdl = 1;
    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_OK));

    // 调用被测函数
    ulResult = AT_HsicInitUlDataBuf(ulUdiHdl,
                                    AT_HSIC_UL_DATA_BUFF_SIZE,
                                    AT_HSIC_UL_DATA_BUFF_NUM);

    EXPECT_EQ(AT_SUCCESS ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicWriteData: public ::testing::Test
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


TEST_F(Test_AT_HsicWriteData, Test_AT_HsicWriteData_01)
{
    VOS_UINT8   ucIndex = AT_CLIENT_TAB_NDIS_INDEX;
    VOS_UINT32  ulResult;
    VOS_UINT8   ucData[10];

    MOCKER(mdrv_udi_ioctl)
        .expects(never())
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    ulResult = AT_HsicWriteData(ucIndex, ucData, 10);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicWriteData, Test_AT_HsicWriteData_02)
{
    VOS_UINT8   ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;
    VOS_UINT32  ulResult;
    VOS_UINT8  ucData[10];

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    ulResult = AT_HsicWriteData(ucIndex, ucData, 10);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicWriteData, Test_AT_HsicWriteData_03)
{
    VOS_UINT8   ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;
    VOS_UINT32  ulResult;
    VOS_UINT8  ucData[10];

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    // 调用被测函数
    ulResult = AT_HsicWriteData(ucIndex ,ucData, 10);

    EXPECT_EQ(AT_SUCCESS ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicWriteData, Test_AT_HsicWriteData_04)
{
    VOS_UINT8   ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;
    VOS_UINT32  ulResult;
    VOS_UINT8  ucData[10];

    g_astAtHsicCtx[0].lHdlId = UDI_INVALID_HANDLE;

    // 调用被测函数
    ulResult = AT_HsicWriteData(ucIndex ,ucData, 10);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SendDataToHsic: public ::testing::Test
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


TEST_F(Test_AT_SendDataToHsic, Test_AT_SendDataToHsic_01)
{
    VOS_UINT8  ucIndex = 1;
    VOS_UINT32  ulResult;
    VOS_UINT8  ucData[10];

    MOCKER(BSP_Malloc)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    // 调用被测函数
    ulResult = AT_SendDataToHsic(ucIndex, ucData, 10);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

VOS_VOID AT_MemSingleCopy_stub(
    VOS_UINT8                          *pucDest,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulLen
)
{
    return;
}

VOS_UINT32 AT_HsicWriteData_stub1(
    VOS_UINT8                          *pucBuf,
    VOS_UINT32                          ulLen
)
{
    return AT_FAILURE;
}


TEST_F(Test_AT_SendDataToHsic, Test_AT_SendDataToHsic_02)
{
    VOS_UINT8  ucIndex = 1;
    VOS_UINT32  ulResult;
    VOS_UINT8  ucData[10];

    //MOCKER(BSP_Malloc)
    //    .will(returnValue((VOS_UINT32)0xffffff00));

    MOCKER(AT_MemSingleCopy)
        .stubs()
        .will(invoke(AT_MemSingleCopy_stub));

    MOCKER(AT_HsicWriteData)
        .stubs()
        .will(invoke(AT_HsicWriteData_stub1));

    // 调用被测函数
    ulResult = AT_SendDataToHsic(ucIndex, ucData, 10);

    EXPECT_EQ(AT_FAILURE ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

VOS_UINT32 AT_HsicWriteData_stub2(
    VOS_UINT8                          *pucBuf,
    VOS_UINT32                          ulLen
)
{
    return AT_SUCCESS;
}


TEST_F(Test_AT_SendDataToHsic, Test_AT_SendDataToHsic_03)
{
    VOS_UINT8  ucIndex = 1;
    VOS_UINT32  ulResult;
    VOS_UINT8  ucData[10];

    //MOCKER(BSP_Malloc)
    //    .will(returnValue((VOS_UINT32)0xffffff00));

    MOCKER(AT_MemSingleCopy)
        .stubs()
        .will(invoke(AT_MemSingleCopy_stub));


    MOCKER(AT_HsicWriteData)
        .stubs()
        .will(invoke(AT_HsicWriteData_stub2));


    // 调用被测函数
    ulResult = AT_SendDataToHsic(ucIndex ,ucData, 10);

    EXPECT_EQ(AT_SUCCESS ,ulResult);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicFourReadDataCB: public ::testing::Test
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


TEST_F(Test_AT_HsicFourReadDataCB, Test_AT_HsicFourReadDataCB_001)
{
    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));

    MOCKER(At_RcvFromUsbCom)
        .expects(never());


    // 调用被测函数
    AT_HsicFourReadDataCB();
}


TEST_F(Test_AT_HsicFourReadDataCB, Test_AT_HsicFourReadDataCB_002)
{
    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_HsicFreeUlDataBuf)
        .stubs()
        .will(returnValue(AT_FAILURE));

    MOCKER(At_RcvFromUsbCom)
        .expects(exactly(1));


    // 调用被测函数
    AT_HsicFourReadDataCB();
}


TEST_F(Test_AT_HsicFourReadDataCB, Test_AT_HsicFourReadDataCB_003)
{
    MOCKER(AT_HsicGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(AT_HsicFreeUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    MOCKER(At_RcvFromUsbCom)
        .expects(exactly(1));


    // 调用被测函数
    AT_HsicFourReadDataCB();
}


class Test_AT_HsicFourFreeDlDataBuf: public ::testing::Test
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


TEST_F(Test_AT_HsicFourFreeDlDataBuf, Test_AT_HsicFourFreeDlDataBuf_001)
{
    VOS_UINT8   ucData[10];

    MOCKER(BSP_Free)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicFourFreeDlDataBuf(ucData);
}


class Test_AT_CheckHsicUser: public ::testing::Test
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


TEST_F(Test_AT_CheckHsicUser, Test_AT_CheckHsicUser_001)
{
    VOS_UINT32  ulRslt;
    VOS_UINT8   ucIndex;

    ucIndex = AT_CLIENT_ID_HSIC1;

    gastAtClientTab[ucIndex].UserType = AT_HSIC1_USER;

    ulRslt = AT_CheckHsicUser(0);

    /* 检查预期结果 */
    EXPECT_EQ(VOS_FALSE, ulRslt);
}



class Test_AT_HsicModemEnableCB: public ::testing::Test
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


TEST_F(Test_AT_HsicModemEnableCB, Test_AT_HsicModemEnableCB_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucEnable;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;
    ucEnable = PS_FALSE;

    gastAtClientTab[ucIndex].DataMode = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].ModemStatus = 0;

    /* 桩函数 */
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(any(), eq(PPP_AT_CTRL_REL_PPP_REQ));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(any(), eq(PPP_AT_CTRL_HDLC_DISABLE));

    /* 函数调用 */

    /* 调用入口函数 */
    AT_HsicModemEnableCB(ucEnable);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(AT_DATA_BUTT_MODE, gastAtClientTab[ucIndex].DataMode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_HsicModemEnableCB, Test_AT_HsicModemEnableCB_002)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucEnable;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;
    ucEnable = PS_FALSE;

    gastAtClientTab[ucIndex].DataMode = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].ModemStatus = 0;

    /* 桩函数 */
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(any(), eq(PPP_AT_CTRL_REL_PPP_REQ));

    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .with(any(), eq(PPP_AT_CTRL_HDLC_DISABLE));

    /* 函数调用 */

    /* 调用入口函数 */
    AT_HsicModemEnableCB(ucEnable);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(AT_PPP_DATA_MODE, gastAtClientTab[ucIndex].DataMode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_HsicModemEnableCB, Test_AT_HsicModemEnableCB_003)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucEnable;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;
    ucEnable = PS_FALSE;

    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].ModemStatus = 0;

    /* 桩函数 */
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(any(), eq(PPP_AT_CTRL_REL_PPP_RAW_REQ));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(any(), eq(PPP_AT_CTRL_HDLC_DISABLE));

    /* 函数调用 */

    /* 调用入口函数 */
    AT_HsicModemEnableCB(ucEnable);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(AT_DATA_BUTT_MODE, gastAtClientTab[ucIndex].DataMode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



TEST_F(Test_AT_HsicModemEnableCB, Test_AT_HsicModemEnableCB_004)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucEnable;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;
    ucEnable = PS_FALSE;

    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].ModemStatus = 0;

    /* 桩函数 */
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(any(), eq(PPP_AT_CTRL_REL_PPP_RAW_REQ));

    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .with(any(), eq(PPP_AT_CTRL_HDLC_DISABLE));

    /* 函数调用 */

    /* 调用入口函数 */
    AT_HsicModemEnableCB(ucEnable);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(AT_IP_DATA_MODE, gastAtClientTab[ucIndex].DataMode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



TEST_F(Test_AT_HsicModemEnableCB, Test_AT_HsicModemEnableCB_005)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucEnable;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;
    ucEnable = PS_FALSE;

    gastAtClientTab[ucIndex].DataMode = AT_CSD_DATA_MODE;
    gastAtClientTab[ucIndex].ModemStatus = 0;

    /* 桩函数 */
    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(never())
        .with(any(), eq(PPP_AT_CTRL_REL_PPP_RAW_REQ));

    MOCKER(PPP_RcvAtCtrlOperEvent)
        .expects(exactly(1))
        .with(any(), eq(PPP_AT_CTRL_HDLC_DISABLE));

    /* 函数调用 */

    /* 调用入口函数 */
    AT_HsicModemEnableCB(ucEnable);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(AT_DATA_BUTT_MODE, gastAtClientTab[ucIndex].DataMode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



class Test_AT_HsicModemReadDataCB: public ::testing::Test
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


TEST_F(Test_AT_HsicModemReadDataCB, Test_AT_HsicModemReadDataCB_001)
{
    /*获取BSP内存*/
    MOCKER(AT_ModemGetUlDataBuf)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    /*使用内存*/
    MOCKER(At_ModemDataInd)
        .expects(exactly(1));

    // 调用被测函数
    AT_HsicModemReadDataCB();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicModemReadMscCB: public ::testing::Test
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


TEST_F(Test_AT_HsicModemReadMscCB, Test_AT_HsicModemReadMscCB_001)
{
    AT_DCE_MSC_STRU                     stDceMsc;

    stDceMsc.OP_Cts = 1;
    stDceMsc.ucCts = 1;

    // 调用被测函数
    AT_HsicModemReadMscCB(&stDceMsc);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicModemReadMscCB, Test_AT_HsicModemReadMscCB_002)
{
    MOCKER(At_ModemMscInd)
        .expects(never());

    // 调用被测函数
    AT_HsicModemReadMscCB(VOS_NULL_PTR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HsicModemInit: public ::testing::Test
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


TEST_F(Test_AT_HsicModemInit, Test_AT_HsicModemInit_001)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(UDI_INVALID_HANDLE));

    // 调用被测函数
    AT_HsicModemInit();

    EXPECT_EQ(UDI_INVALID_HANDLE, g_alAtUdiHandle[AT_CLIENT_TAB_HSIC_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicModemInit, Test_AT_HsicModemInit_002)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .stubs()
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_HsicModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_HSIC_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicModemInit, Test_AT_HsicModemInit_003)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_HsicModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_HSIC_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicModemInit, Test_AT_HsicModemInit_004)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(2))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_HsicModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_HSIC_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicModemInit, Test_AT_HsicModemInit_005)
{
    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(3))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_HsicModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[AT_CLIENT_TAB_HSIC_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HsicModemInit, Test_AT_HsicModemInit_006)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;

    MOCKER(mdrv_udi_open)
        .stubs()
        .will(returnValue(1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(4))
        .will(returnValue(VOS_OK));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    AT_HsicModemInit();

    EXPECT_EQ(1, g_alAtUdiHandle[ucIndex]);
    EXPECT_EQ(AT_CLIENT_ID_HSIC_MODEM, gastAtClientTab[ucIndex].usClientId);
    EXPECT_EQ(AT_HSIC_MODEM_PORT_NO, gastAtClientTab[ucIndex].ucPortType);
    EXPECT_EQ(AT_MODEM_USER_DLCI, gastAtClientTab[ucIndex].ucDlci);
    EXPECT_EQ(AT_HSIC_MODEM_PORT_NO, gastAtClientTab[ucIndex].ucPortNo);
    EXPECT_EQ(AT_MODEM_USER, gastAtClientTab[ucIndex].UserType);
    EXPECT_EQ(AT_CLIENT_USED, gastAtClientTab[ucIndex].ucUsed);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



class Test_AT_HsicModemClose: public ::testing::Test
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


TEST_F(Test_AT_HsicModemClose, Test_AT_HsicModemClose_001)
{
    g_alAtUdiHandle[AT_CLIENT_TAB_HSIC_MODEM_INDEX] = 1;

    // 调用被测函数
    AT_HsicModemClose();

    EXPECT_EQ(UDI_INVALID_HANDLE, g_alAtUdiHandle[AT_CLIENT_TAB_HSIC_MODEM_INDEX]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif


class Test_AT_SndDipcPdpActInd: public ::testing::Test
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


TEST_F(Test_AT_SndDipcPdpActInd, Test_AT_SndDipcPdpActInd_01)
{
    VOS_UINT8                           ucCid = 1;
    VOS_UINT8                           ucRabId = 5;

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(V_SendMsg)
        .expects(never());

    // 调用被测函数
    AT_SndDipcPdpActInd(0, ucCid, ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SndDipcPdpActInd, Test_AT_SndDipcPdpActInd_02)
{
    VOS_UINT8                           ucCid = 1;
    VOS_UINT8                           ucRabId = 5;
    AT_DIPC_PDP_ACT_STRU                stAtDipcPdpAct;
    VOS_UINT16                          usClientId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)&stAtDipcPdpAct));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    AT_SndDipcPdpActInd(usClientId, ucCid, ucRabId);

    EXPECT_EQ(ID_AT_DIPC_PDP_ACT_IND,stAtDipcPdpAct.enMsgType);
    EXPECT_EQ(ucRabId,stAtDipcPdpAct.ucRabId);
    EXPECT_EQ(pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId,stAtDipcPdpAct.enUdiDevId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SndDipcPdpActInd, Test_AT_SndDipcPdpActInd_03)
{
    VOS_UINT8                           ucCid = 1;
    VOS_UINT8                           ucRabId = 5;
    AT_DIPC_PDP_ACT_STRU                stAtDipcPdpAct;
    VOS_UINT16                          usClientId;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)&stAtDipcPdpAct));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_SndDipcPdpActInd(usClientId, ucCid, ucRabId);

    EXPECT_EQ(ID_AT_DIPC_PDP_ACT_IND,stAtDipcPdpAct.enMsgType);
    EXPECT_EQ(ucRabId,stAtDipcPdpAct.ucRabId);
    EXPECT_EQ(pstModemPsCtx->astChannelCfg[ucCid].ulRmNetId,stAtDipcPdpAct.enUdiDevId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SndDipcPdpDeactInd: public ::testing::Test
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

TEST_F(Test_AT_SndDipcPdpDeactInd, Test_AT_SndDipcPdpDeactInd_01)
{
    VOS_UINT8                           ucRabId = 5;

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(V_SendMsg)
        .expects(never());

    // 调用被测函数
    AT_SndDipcPdpDeactInd(ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SndDipcPdpDeactInd, Test_AT_SndDipcPdpDeactInd_02)
{
    VOS_UINT8                           ucRabId = 5;
    AT_DIPC_PDP_DEACT_STRU              stAtDipcPdpDeact;
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)&stAtDipcPdpDeact));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));


    // 调用被测函数
    AT_SndDipcPdpDeactInd(ucRabId);

    EXPECT_EQ(ID_AT_DIPC_PDP_REL_IND, stAtDipcPdpDeact.enMsgType);
    EXPECT_EQ(ucRabId, stAtDipcPdpDeact.ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SndDipcPdpDeactInd, Test_AT_SndDipcPdpDeactInd_03)
{
    VOS_UINT8                           ucRabId = 5;
    AT_DIPC_PDP_DEACT_STRU              stAtDipcPdpDeact;

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)&stAtDipcPdpDeact));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_SndDipcPdpDeactInd(ucRabId);
    EXPECT_EQ(ID_AT_DIPC_PDP_REL_IND, stAtDipcPdpDeact.enMsgType);
    EXPECT_EQ(ucRabId, stAtDipcPdpDeact.ucRabId);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_SetAtChdataCidActStatus: public ::testing::Test
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


TEST_F(Test_AT_SetAtChdataCidActStatus, Test_AT_SetAtChdataCidActStatus_01)
{
    VOS_UINT8                           ucCid = 12;
    VOS_UINT32                          ulIsCidAct = VOS_TRUE;
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT16                          usClientId;

    usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    for (ucIndex = 0; ucIndex < TAF_MAX_CID_NV; ucIndex++)
    {
        pstModemPsCtx->astChannelCfg[ucIndex].ulRmNetActFlg = VOS_FALSE;
    }

    // 调用被测函数
    AT_SetAtChdataCidActStatus(usClientId, ucCid, ulIsCidAct);

    for (ucIndex = 0; ucIndex < TAF_MAX_CID_NV; ucIndex++)
    {
        EXPECT_EQ(VOS_FALSE, pstModemPsCtx->astChannelCfg[ucIndex].ulRmNetActFlg);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAtChdataCidActStatus, Test_AT_SetAtChdataCidActStatus_02)
{
    VOS_UINT8                           ucCid = 1;
    VOS_UINT32                          ulIsCidAct = VOS_TRUE;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT16                          usClientId;

    usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    // 调用被测函数
    AT_SetAtChdataCidActStatus(usClientId, ucCid, ulIsCidAct);

    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[ucCid].ulRmNetActFlg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_CleanAtChdataCfg: public ::testing::Test
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

TEST_F(Test_AT_CleanAtChdataCfg, Test_AT_CleanAtChdataCfg_01)
{
    VOS_UINT8                           ucCid = 12;
    VOS_UINT32                          ulIsCidAct = VOS_FALSE;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT16                          usClientId;

    usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed        = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId     = UDI_ACM_HSIC_ACM0_ID;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    // 调用被测函数
    AT_CleanAtChdataCfg(usClientId, ucCid);

    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_ACM_HSIC_ACM0_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_CleanAtChdataCfg, Test_AT_CleanAtChdataCfg_02)
{
    VOS_UINT8                           ucCid = 1;
    VOS_UINT32                          ulIsCidAct = VOS_FALSE;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT16                          usClientId;

    usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstModemPsCtx->astChannelCfg[1].ulUsed        = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId     = UDI_ACM_HSIC_ACM0_ID;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    // 调用被测函数
    AT_CleanAtChdataCfg(usClientId, ucCid);

    EXPECT_EQ(VOS_FALSE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);
    EXPECT_EQ(VOS_FALSE, pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_InitFcMap: public ::testing::Test
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


TEST_F(Test_AT_InitFcMap, Test_AT_InitFcMap_01)
{
    VOS_UINT8                           ucCid = 1;
    VOS_UINT32                          ulIsCidAct = VOS_FALSE;
    VOS_UINT8                           ucLoop;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    VOS_UINT16                          usClientId;

    usClientId = AT_CLIENT_ID_APP;

    pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
    pstModemPsCtx->astChannelCfg[1].ulUsed        = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId     = UDI_ACM_HSIC_ACM0_ID;
    pstModemPsCtx->astChannelCfg[1].ulRmNetActFlg = VOS_TRUE;

    // 调用被测函数
    AT_InitFcMap();

    for(ucLoop = 0; ucLoop < FC_ID_BUTT; ucLoop++)
    {
        EXPECT_EQ(VOS_FALSE,   g_stFcIdMaptoFcPri[0].ulUsed);
        EXPECT_EQ(FC_PRI_BUTT, g_stFcIdMaptoFcPri[0].enFcPri);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_CCpuResetCallback: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);
    }
    void TearDown()
    {
        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);
    }
};


TEST_F(Test_AT_CCpuResetCallback, Test_AT_CCpuResetCallback_001)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(TAF_AGENT_ClearAllSem)
        .expects(exactly(1));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_CCpuResetCallback, Test_AT_CCpuResetCallback_002)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(TAF_AGENT_ClearAllSem)
        .expects(exactly(1));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(invoke(UT_Ps_SendMsgFail));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_CCpuResetCallback, Test_AT_CCpuResetCallback_003)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(TAF_AGENT_ClearAllSem)
        .expects(exactly(1));

    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}



TEST_F(Test_AT_CCpuResetCallback, Test_AT_CCpuResetCallback_004)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(TAF_AGENT_ClearAllSem)
        .expects(exactly(1));

    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_CCpuResetCallback, Test_AT_CCpuResetCallback_005)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_CCpuResetCallback, Test_AT_CCpuResetCallback_006)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(invoke(UT_Ps_SendMsgFail));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_CCpuResetCallback, Test_AT_CCpuResetCallback_007)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_CCpuResetCallback, Test_AT_CCpuResetCallback_008)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_CCpuResetCallback(MDRV_RESET_CB_INVALID, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


class Test_AT_HifiResetCallback: public ::testing::Test
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


TEST_F(Test_AT_HifiResetCallback, Test_AT_HifiResetCallback_001)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_HifiResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_HifiResetCallback, Test_AT_HifiResetCallback_002)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(invoke(UT_Ps_SendMsgFail));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_HifiResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_HifiResetCallback, Test_AT_HifiResetCallback_003)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_HifiResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_HifiResetCallback, Test_AT_HifiResetCallback_004)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_HifiResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_HifiResetCallback, Test_AT_HifiResetCallback_005)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_HifiResetCallback(MDRV_RESET_CB_INVALID, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_HifiResetCallback, Test_AT_HifiResetCallback_006)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_HifiResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_AT_HifiResetCallback, Test_AT_HifiResetCallback_007)
{
    VOS_INT                             iRst;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(invoke(UT_Ps_SendMsgFail));

    /* 函数调用 */

    /* 调用入口函数 */
    iRst = AT_HifiResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERROR, iRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


class Test_AT_ModemStatusPreProc: public ::testing::Test
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


TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr  = 0;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_CSD_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    // MOCKER操作
    MOCKER(AT_CtrlDCD)
        .expects(exactly(1));

    MOCKER(AT_CsdDataModeRcvModemMsc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr  = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    // MOCKER操作
    MOCKER(AT_MODEM_ProcDtrChange)
        .expects(exactly(1));

    MOCKER(AT_PppDataModeRcvModemMsc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr  = 0;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    // MOCKER操作
    MOCKER(AT_MODEM_ProcDtrChange)
        .expects(exactly(1));

    MOCKER(AT_IpDataModeRcvModemMsc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr  = 0;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    // MOCKER操作
    MOCKER(AT_MODEM_ProcDtrChange)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr  = 1;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    MOCKER(AT_MODEM_ProcDtrChange)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_007)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr = 0;
    pstUartCtx = AT_GetUartCtxAddr();

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;
    pstUartCtx->stLineCtrl.enDsrMode = AT_UART_DSR_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDcdMode = AT_UART_DCD_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDtrMode = AT_UART_DTR_MODE_SWITCH_CMD_MODE;

    // MOCKER操作
    MOCKER(At_SetMode)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(AT_StopFlowCtrl)
        .expects(never());

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(AT_DATA_MODE, gastAtClientTab[ucIndex].Mode);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_008)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr = 0;
    pstUartCtx = AT_GetUartCtxAddr();

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;
    pstUartCtx->stLineCtrl.enDsrMode = AT_UART_DSR_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDcdMode = AT_UART_DCD_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDtrMode = AT_UART_DTR_MODE_HANGUP_CALL;

    // MOCKER操作
    MOCKER(AT_IpDataModeRcvModemMsc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_009)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr = 0;
    pstUartCtx = AT_GetUartCtxAddr();

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;
    pstUartCtx->stLineCtrl.enDsrMode = AT_UART_DSR_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDcdMode = AT_UART_DCD_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDtrMode = AT_UART_DTR_MODE_IGNORE;

    // MOCKER操作
    MOCKER(AT_IpDataModeRcvModemMsc)
        .expects(never());

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ModemStatusPreProc, Test_AT_ModemStatusPreProc_010)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr = 0;
    pstUartCtx = AT_GetUartCtxAddr();

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_ONLINE_CMD_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;
    pstUartCtx->stLineCtrl.enDsrMode = AT_UART_DSR_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDcdMode = AT_UART_DCD_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDtrMode = AT_UART_DTR_MODE_HANGUP_CALL;

    // MOCKER操作
    MOCKER(AT_PppDataModeRcvModemMsc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_ModemStatusPreProc(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}
#endif


class Test_AT_MODEM_ProcDtrChange: public ::testing::Test
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


TEST_F(Test_AT_MODEM_ProcDtrChange, Test_AT_MODEM_ProcDtrChange_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    memset(&stMscStru, 0x0,sizeof(stMscStru));
    stMscStru.ucDtr = 1;

    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    // MOCKER操作
    MOCKER(AT_CtrlDSR)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_HIGH));

    MOCKER(AT_CtrlCTS)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_HIGH));

    MOCKER(AT_MNTN_TraceStopFlowCtrl)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_FC_DEVICE_TYPE_ENUM_UINT32)AT_FC_DEVICE_TYPE_MODEM));

    AT_MODEM_ProcDtrChange(ucIndex, &stMscStru);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_MODEM_ProcDtrChange, Test_AT_MODEM_ProcDtrChange_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_MODEM;
    memset(&stMscStru, 0x0,sizeof(stMscStru));
    stMscStru.ucDtr = 0;

    g_ucDtrDownFlag = VOS_FALSE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE ;
    gastAtClientTab[ucIndex].DataMode = AT_CSD_DATA_MODE;

    MOCKER(AT_CtrlDCD)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_LOW));

    AT_MODEM_ProcDtrChange(ucIndex,&stMscStru);

    EXPECT_EQ(VOS_TRUE,g_ucDtrDownFlag);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

class Test_AT_UART_ProcDtrChange: public ::testing::Test
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


TEST_F(Test_AT_UART_ProcDtrChange, Test_AT_UART_ProcDtrChange_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    memset(&stMscStru,0x0,sizeof(stMscStru));
    stMscStru.ucDtr = 1;
    pstUartCtx = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDsrMode = AT_UART_DSR_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDcdMode = AT_UART_DSR_MODE_ALWAYS_ON;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    // MOCKER操作
    MOCKER(AT_CtrlDSR)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_HIGH));

    MOCKER(AT_CtrlDCD)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_HIGH));

    MOCKER(AT_CtrlCTS)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_HIGH));

    MOCKER(AT_MNTN_TraceStopFlowCtrl)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_FC_DEVICE_TYPE_ENUM_UINT32)AT_FC_DEVICE_TYPE_HSUART));

    // 调用被测函数
    ulRet = AT_UART_ProcDtrChange(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_ProcDtrChange, Test_AT_UART_ProcDtrChange_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_DCE_MSC_STRU                     stMscStru;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    memset(&stMscStru,0x0,sizeof(stMscStru));
    stMscStru.ucDtr = 0;
    pstUartCtx = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDsrMode = AT_UART_DSR_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDcdMode = AT_UART_DSR_MODE_ALWAYS_ON;
    pstUartCtx->stLineCtrl.enDtrMode = AT_UART_DTR_MODE_IGNORE;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    // MOCKER操作
    MOCKER(AT_CtrlDSR)
        .expects(never());

    MOCKER(AT_CtrlDCD)
        .expects(never());

    // 调用被测函数
    ulRet = AT_UART_ProcDtrChange(ucIndex, &stMscStru);

    // 执行检查
    EXPECT_EQ(VOS_FALSE,ulRet);

    GlobalMockObject::verify();
}


class Test_AT_UART_ProcDtrCtrlMode: public ::testing::Test
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


TEST_F(Test_AT_UART_ProcDtrCtrlMode, Test_AT_UART_ProcDtrCtrlMode_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstUartCtx                          = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDtrMode    = AT_UART_DTR_MODE_IGNORE;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_UART_ProcDtrCtrlMode();

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_ProcDtrCtrlMode, Test_AT_UART_ProcDtrCtrlMode_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    pstUartCtx = AT_GetUartCtxAddr();
    ucIndex    = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstUartCtx->stLineCtrl.enDtrMode = AT_UART_DTR_MODE_SWITCH_CMD_MODE;
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_PPP_DATA_MODE;

    // MOCKER操作
    MOCKER(At_SetMode)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_MODE_TYPE)AT_ONLINE_CMD_MODE), eq((VOS_UINT8)AT_NORMAL_MODE));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // 调用被测函数
    ulRet = AT_UART_ProcDtrCtrlMode();

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_ProcDtrCtrlMode, Test_AT_UART_ProcDtrCtrlMode_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstUartCtx                          = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDtrMode    = AT_UART_DTR_MODE_HANGUP_CALL;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_UART_ProcDtrCtrlMode();

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_ProcDtrCtrlMode, Test_AT_UART_ProcDtrCtrlMode_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstUartCtx                          = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDtrMode    = AT_UART_DTR_MODE_BUTT;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_UART_ProcDtrCtrlMode();

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_StartFlowCtrl: public ::testing::Test
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


TEST_F(Test_AT_HSUART_StartFlowCtrl, Test_AT_HSUART_StartFlowCtrl_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;

    // MOCKER操作
    MOCKER(AT_CtrlCTS)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_LOW));

    MOCKER(AT_MNTN_TraceStartFlowCtrl)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_FC_DEVICE_TYPE_ENUM_UINT32)AT_FC_DEVICE_TYPE_HSUART));

    // 调用被测函数
    ulRet = AT_HSUART_StartFlowCtrl(0, 0);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_StopFlowCtrl: public ::testing::Test
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


TEST_F(Test_AT_HSUART_StopFlowCtrl, Test_AT_HSUART_StopFlowCtrl_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;

    // MOCKER操作
    MOCKER(AT_CtrlCTS)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_HIGH));

    MOCKER(AT_MNTN_TraceStopFlowCtrl)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_FC_DEVICE_TYPE_ENUM_UINT32)AT_FC_DEVICE_TYPE_HSUART));

    // 调用被测函数
    ulRet = AT_HSUART_StopFlowCtrl(0, 0);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_FreeDlDataBuff: public ::testing::Test
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


TEST_F(Test_AT_HSUART_FreeDlDataBuff, Test_AT_HSUART_FreeDlDataBuff_001)
{
    // 变量声明
    IMM_ZC_STRU                         stBuf;

    // 参数初始化

    // 初始化全局变量
    g_stAtStatsInfo.stHsUartStats.ulDlFreeBuffNum = 0;

    // MOCKER操作
    MOCKER(kfree_skb)
        .expects(exactly(1));

    // 调用被测函数
    AT_HSUART_FreeDlDataBuff(&stBuf);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulDlFreeBuffNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_FreeDlDataBuff, Test_AT_HSUART_FreeDlDataBuff_002)
{
    // 变量声明
    IMM_ZC_STRU                        *pstImmZc;

    // 参数初始化
    g_stAtStatsInfo.stHsUartStats.ulDlFreeBuffNum = 0;

    // 初始化全局变量
    pstImmZc = VOS_NULL_PTR;

    // MOCKER操作

    // 调用被测函数
    AT_HSUART_FreeDlDataBuff(pstImmZc);

    // 执行检查
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlFreeBuffNum);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_SendDlData: public ::testing::Test
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


TEST_F(Test_AT_HSUART_SendDlData, Test_AT_HSUART_SendDlData_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLen;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucDataBuf[4] = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    usLen = 4;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(IMM_ZcStaticAlloc_Debug)
        .expects(exactly(1))
        .will(returnValue((IMM_ZC_STRU*)VOS_NULL_PTR));

    // 调用被测函数
    ulRet = AT_HSUART_SendDlData(ucIndex, aucDataBuf, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_SendDlData, Test_AT_HSUART_SendDlData_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLen;
    VOS_UINT8                           ucIndex;
    IMM_ZC_STRU                         stImmZc = {0};
    VOS_UINT8                           aucDataBuf[16] = {0};
    VOS_UINT8                           aucTmpBuf[16] = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    usLen = 16;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(IMM_ZcStaticAlloc_Debug)
        .expects(exactly(1))
        .will(returnValue(&stImmZc));

    MOCKER(IMM_ZcPut_Debug)
        .expects(exactly(1))
        .will(returnValue((unsigned char*)aucTmpBuf));

    MOCKER(AT_HSUART_WriteDataAsync)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRet = AT_HSUART_SendDlData(ucIndex, aucDataBuf, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_SendDlData, Test_AT_HSUART_SendDlData_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLen;
    VOS_UINT8                           ucIndex;
    IMM_ZC_STRU                         stImmZc = {0};
    VOS_UINT8                           aucDataBuf[16] = {0};
    VOS_UINT8                           aucTmpBuf[16] = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    usLen = 16;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(IMM_ZcStaticAlloc_Debug)
        .expects(exactly(1))
        .will(returnValue(&stImmZc));

    MOCKER(IMM_ZcPut_Debug)
        .expects(exactly(1))
        .will(returnValue((unsigned char*)aucTmpBuf));

    MOCKER(AT_HSUART_WriteDataAsync)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    ulRet = AT_HSUART_SendDlData(ucIndex, aucDataBuf, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_ProcUlData: public ::testing::Test
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


TEST_F(Test_AT_HSUART_ProcUlData, Test_AT_HSUART_ProcUlData_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTemp[] = "~~~";
    IMM_ZC_STRU                         stZcData;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stZcData.data = aucTemp;
    stZcData.len  = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_CMD_MODE;
    g_stAtStatsInfo.stHsUartStats.ulUlRcvInvalidCmdNum = 0;

    // MOCKER操作
    MOCKER(AT_HSUART_FreeUlDataBuff)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_HSUART_ProcUlData(ucIndex, &stZcData);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlRcvInvalidCmdNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ProcUlData, Test_AT_HSUART_ProcUlData_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTemp[] = "AT\r";
    IMM_ZC_STRU                         stZcData;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stZcData.data = aucTemp;
    stZcData.len  = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_CMD_MODE;
    g_stAtStatsInfo.stHsUartStats.ulUlRcvInvalidCmdNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulUlValidCmdNum = 0;

    // MOCKER操作
    MOCKER(AT_HSUART_FreeUlDataBuff)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(At_CmdStreamPreProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    // 调用被测函数
    AT_HSUART_ProcUlData(ucIndex, &stZcData);

    // 执行检查
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulUlRcvInvalidCmdNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlValidCmdNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ProcUlData, Test_AT_HSUART_ProcUlData_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTemp[] = "~~~";
    IMM_ZC_STRU                         stZcData = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stZcData.data = aucTemp;
    stZcData.len  = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_PPP_DATA_MODE;
    g_stAtStatsInfo.stHsUartStats.ulUlIpDataNum = 0;

    // MOCKER操作
    MOCKER(PPP_PullPacketEvent)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_HSUART_FreeUlDataBuff)
        .expects(never());

    // 调用被测函数
    AT_HSUART_ProcUlData(ucIndex, &stZcData);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlIpDataNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ProcUlData, Test_AT_HSUART_ProcUlData_004)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTemp[] = "~~~";
    IMM_ZC_STRU                         stZcData = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stZcData.data = aucTemp;
    stZcData.len  = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    g_stAtStatsInfo.stHsUartStats.ulUlPppDataNum = 0;

    // MOCKER操作
    MOCKER(PPP_PullRawDataEvent)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_HSUART_FreeUlDataBuff)
        .expects(never());

    // 调用被测函数
    AT_HSUART_ProcUlData(ucIndex, &stZcData);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlPppDataNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ProcUlData, Test_AT_HSUART_ProcUlData_005)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTemp[] = "~~~";
    IMM_ZC_STRU                         stZcData = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stZcData.data = aucTemp;
    stZcData.len  = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_OM_DATA_MODE;
    g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum = 0;

    // MOCKER操作
    MOCKER(At_OmDataProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_HSUART_FreeUlDataBuff)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_HSUART_ProcUlData(ucIndex, &stZcData);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ProcUlData, Test_AT_HSUART_ProcUlData_006)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTemp[] = "~~~";
    IMM_ZC_STRU                         stZcData = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stZcData.data = aucTemp;
    stZcData.len  = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_DATA_BUTT_MODE;
    g_stAtStatsInfo.stHsUartStats.ulUlInvalidModeDataNum = 0;

    // MOCKER操作
    MOCKER(AT_HSUART_FreeUlDataBuff)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_HSUART_ProcUlData(ucIndex, &stZcData);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlInvalidModeDataNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ProcUlData, Test_AT_HSUART_ProcUlData_007)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTemp[] = "~~~";
    IMM_ZC_STRU                         stZcData = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stZcData.data = aucTemp;
    stZcData.len  = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_DIAG_DATA_MODE;
    g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum = 0;

    // MOCKER操作
    MOCKER(At_OmDataProc)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_HSUART_FreeUlDataBuff)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_HSUART_ProcUlData(ucIndex, &stZcData);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ProcUlData, Test_AT_HSUART_ProcUlData_008)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTemp[] = "~~~";
    IMM_ZC_STRU                         stZcData = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    stZcData.data = aucTemp;
    stZcData.len  = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_CSD_DATA_MODE;
    g_stAtStatsInfo.stHsUartStats.ulUlInvalidModeDataNum = 0;

    // MOCKER操作
    MOCKER(AT_HSUART_FreeUlDataBuff)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_HSUART_ProcUlData(ucIndex, &stZcData);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlInvalidModeDataNum);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_MscReadCB: public ::testing::Test
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


TEST_F(Test_AT_HSUART_MscReadCB, Test_AT_HSUART_MscReadCB_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量
    g_stAtStatsInfo.stHsUartStats.ulMscReadCBNum = 0;

    // MOCKER操作

    // 调用被测函数
    AT_HSUART_MscReadCB(VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulMscReadCBNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_MscReadCB, Test_AT_HSUART_MscReadCB_002)
{
    // 变量声明
    AT_DCE_MSC_STRU                     stRcvedMsc;

    // 参数初始化
    stRcvedMsc.OP_Dtr   = 1;
    stRcvedMsc.ucDtr    = 1;

    // 初始化全局变量
    g_stAtStatsInfo.stHsUartStats.ulMscReadCBNum = 0;

    // MOCKER操作
    MOCKER(At_ModemMscInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_HSUART_MscReadCB(&stRcvedMsc);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulMscReadCBNum);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_SwitchCmdDetectCB: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_HSUART_SwitchCmdDetectCB, Test_AT_HSUART_SwitchCmdDetectCB_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    // 调用被测函数
    AT_HSUART_SwitchCmdDetectCB();

    // 执行检查

    GlobalMockObject::verify();
}

TEST_F(Test_AT_HSUART_SwitchCmdDetectCB, Test_AT_HSUART_SwitchCmdDetectCB_002)
{
    // 变量声明
    AT_MSG_STRU                         stMsg = {0};

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)&stMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    AT_HSUART_SwitchCmdDetectCB();

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_SwitchCmdDetectCB, Test_AT_HSUART_SwitchCmdDetectCB_003)
{
    // 变量声明
    AT_MSG_STRU                         stMsg = {0};

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)&stMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_HSUART_SwitchCmdDetectCB();

    // 执行检查

    GlobalMockObject::verify();
}


class Test_AT_HSUART_UlDataReadCB: public ::testing::Test
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


TEST_F(Test_AT_HSUART_UlDataReadCB, Test_AT_HSUART_UlDataReadCB_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量
    g_stAtStatsInfo.stHsUartStats.ulUlDataReadCBNum = 0;

    // MOCKER操作
    MOCKER(AT_HSUART_GetUlDataBuff)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    MOCKER(AT_HSUART_ProcUlData)
        .expects(never());

    // 调用被测函数
    AT_HSUART_UlDataReadCB();

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlDataReadCBNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_UlDataReadCB, Test_AT_HSUART_UlDataReadCB_002)
{
    // 变量声明
    VOS_UINT8                       ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    g_stAtStatsInfo.stHsUartStats.ulUlDataReadCBNum = 0;

    // MOCKER操作
    MOCKER(AT_HSUART_GetUlDataBuff)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(AT_HSUART_ProcUlData)
        .expects(exactly(1))
        .with(eq(ucIndex), any());

    // 调用被测函数
    AT_HSUART_UlDataReadCB();

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlDataReadCBNum);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_FreeUlDataBuff: public ::testing::Test
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


TEST_F(Test_AT_HSUART_FreeUlDataBuff, Test_AT_HSUART_FreeUlDataBuff_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    IMM_ZC_STRU                         stZcBuff = {0};

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex]            = UDI_INVALID_HANDLE;
    g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(never());

    // 调用被测函数
    ulRet = AT_HSUART_FreeUlDataBuff(ucIndex, &stZcBuff);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_FreeUlDataBuff, Test_AT_HSUART_FreeUlDataBuff_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    IMM_ZC_STRU                         stZcBuff = {0};

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex]            = 0;
    g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffFailNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    MOCKER(kfree_skb)
        .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_HSUART_FreeUlDataBuff(ucIndex, &stZcBuff);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffFailNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_FreeUlDataBuff, Test_AT_HSUART_FreeUlDataBuff_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    IMM_ZC_STRU                         stZcBuff = {0};

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex]            = 0;
    g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffFailNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    MOCKER(kfree_skb)
        .expects(never());

    // 调用被测函数
    ulRet = AT_HSUART_FreeUlDataBuff(ucIndex, &stZcBuff);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffFailNum);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_WriteDlDataAsync: public ::testing::Test
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


TEST_F(Test_AT_HSUART_WriteDlDataAsync, Test_AT_HSUART_WriteDlDataAsync_001)
{
    // 变量声明
    IMM_ZC_STRU                         stBuf = {0};
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum = 0;

    // MOCKER操作
    MOCKER(AT_HSUART_FreeDlDataBuff)
        .expects(exactly(1));

    MOCKER(mdrv_udi_ioctl)
        .expects(never());

    // 调用被测函数
    ulRet = AT_HSUART_WriteDataAsync(ucIndex, &stBuf);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_WriteDlDataAsync, Test_AT_HSUART_WriteDlDataAsync_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    IMM_ZC_STRU                         stBuf;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncFailNum = 0;

    // MOCKER操作
     MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERROR));

     MOCKER(AT_HSUART_FreeDlDataBuff)
         .expects(exactly(1));

    // 调用被测函数
    ulRet = AT_HSUART_WriteDataAsync(ucIndex,&stBuf);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncFailNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_WriteDlDataAsync, Test_AT_HSUART_WriteDlDataAsync_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    IMM_ZC_STRU                         stBuf;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncFailNum = 0;

    // MOCKER操作
     MOCKER(mdrv_udi_ioctl)
           .expects(exactly(1))
           .will(returnValue((VOS_INT32)VOS_OK));

    MOCKER(AT_HSUART_FreeDlDataBuff)
        .expects(never());

    // 调用被测函数
    ulRet = AT_HSUART_WriteDataAsync(ucIndex,&stBuf);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncFailNum);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_GetUlDataBuff: public ::testing::Test
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


TEST_F(Test_AT_HSUART_GetUlDataBuff, Test_AT_HSUART_GetUlDataBuff_001)
{
    // 变量声明
    IMM_ZC_STRU                        *pstBuf;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLen;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    pstBuf  = VOS_NULL_PTR;
    ulLen   = 0;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulUlGetRDFailNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    // 调用被测函数
    ulRet = AT_HSUART_GetUlDataBuff(ucIndex, &pstBuf, &ulLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlGetRDFailNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUlDataBuff, Test_AT_HSUART_GetUlDataBuff_002)
{
    // 变量声明
    IMM_ZC_STRU                        *pstBuf;
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    pstBuf = VOS_NULL_PTR;
    stCtlParam.pVirAddr = VOS_NULL_PTR;
    stCtlParam.u32Size = 100;
    ulLen   = 0;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulUlInvalidRDNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(eq((UDI_HANDLE)1), eq((VOS_UINT32)UART_IOCTL_GET_RD_BUFF), outBoundP((VOS_VOID*)&stCtlParam, sizeof(stCtlParam)))
        .will(returnValue((VOS_INT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_HSUART_GetUlDataBuff(ucIndex, &pstBuf, &ulLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, ulLen);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlInvalidRDNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUlDataBuff, Test_AT_HSUART_GetUlDataBuff_003)
{
    // 变量声明
    IMM_ZC_STRU                        *pstBuf;
    IMM_ZC_STRU                         stZcBuff = {0};
    ACM_WR_ASYNC_INFO                   stCtlParam = {0};
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLen;
    VOS_UINT8                           ucIndex;
    IMM_ZC_STRU                         stZcBuf;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    pstBuf = VOS_NULL_PTR;
    stCtlParam.pVirAddr = (VOS_CHAR*)&stZcBuff;
    stCtlParam.u32Size = sizeof(stZcBuff);
    ulLen   = 0;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(eq((UDI_HANDLE)1), eq((VOS_UINT32)UART_IOCTL_GET_RD_BUFF), outBoundP((VOS_VOID*)&stCtlParam, sizeof(stCtlParam)))
        .will(returnValue((VOS_INT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_HSUART_GetUlDataBuff(ucIndex, &pstBuf, &ulLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(stCtlParam.u32Size, ulLen);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUlDataBuff, Test_AT_HSUART_GetUlDataBuff_004)
{
    // 变量声明
    IMM_ZC_STRU                        *pstBuf;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLen;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    pstBuf  = VOS_NULL_PTR;
    ulLen   = 0;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(never());

    // 调用被测函数
    ulRet = AT_HSUART_GetUlDataBuff(ucIndex, &pstBuf, &ulLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_InitPort: public ::testing::Test
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


TEST_F(Test_AT_HSUART_InitPort, Test_AT_HSUART_InitPort_001)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    MOCKER(mdrv_udi_open)
        .expects(exactly(1))
        .will(returnValue((UDI_HANDLE)UDI_INVALID_HANDLE));

    // 调用被测函数
    AT_HSUART_InitPort();

    EXPECT_EQ(UDI_INVALID_HANDLE, g_alAtUdiHandle[ucIndex]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_InitPort, Test_AT_HSUART_InitPort_002)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    g_stAtStatsInfo.stHsUartStats.ucSetReadCbERR = 0;
    g_stAtStatsInfo.stHsUartStats.ucRellocReadBuffERR = 0;
    g_stAtStatsInfo.stHsUartStats.ucSetFreeBuffCbERR = 0;
    g_stAtStatsInfo.stHsUartStats.ucSetMscReadCbERR = 0;
    g_stAtStatsInfo.stHsUartStats.ucSetSwitchCmdCbERR = 0;

    MOCKER(AT_HSUART_ConfigPort)
        .expects(exactly(1));

    MOCKER(mdrv_udi_open)
        .expects(exactly(1))
        .will(returnValue((UDI_HANDLE)1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(5))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    // 调用被测函数
    AT_HSUART_InitPort();

    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ucSetReadCbERR);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ucRellocReadBuffERR);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ucSetFreeBuffCbERR);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ucSetMscReadCbERR);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ucSetSwitchCmdCbERR);

    EXPECT_EQ(1, g_alAtUdiHandle[ucIndex]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_InitPort, Test_AT_HSUART_InitPort_003)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    g_stAtStatsInfo.stHsUartStats.ucSetReadCbERR = 0;
    g_stAtStatsInfo.stHsUartStats.ucRellocReadBuffERR = 0;
    g_stAtStatsInfo.stHsUartStats.ucSetFreeBuffCbERR = 0;
    g_stAtStatsInfo.stHsUartStats.ucSetMscReadCbERR = 0;
    g_stAtStatsInfo.stHsUartStats.ucSetSwitchCmdCbERR = 0;

    MOCKER(AT_HSUART_ConfigPort)
        .expects(exactly(1));

    MOCKER(mdrv_udi_open)
        .expects(exactly(1))
        .will(returnValue((UDI_HANDLE)1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(5))
        .will(returnValue((VOS_INT32)VOS_OK));

    // 调用被测函数
    AT_HSUART_InitPort();

    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ucSetReadCbERR);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ucRellocReadBuffERR);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ucSetFreeBuffCbERR);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ucSetMscReadCbERR);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ucSetSwitchCmdCbERR);

    EXPECT_EQ(1, g_alAtUdiHandle[ucIndex]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_HSUART_ConfigPort: public ::testing::Test
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


TEST_F(Test_AT_HSUART_ConfigPort, Test_AT_HSUART_ConfigPort_001)
{
    // 变量声明
    UDI_HANDLE                          lUartHdl = 1;
    AT_UART_CTX_STRU                   *pstUartCtx;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    pstUartCtx      = AT_GetUartCtxAddr();
    pstUartCtx->stPhyConfig.stFrame.enFormat = AT_UART_FORMAT_BUTT;

    // 参数初始化

    // 初始化全局变量
    g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(4))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    // 调用被测函数
    AT_HSUART_ConfigPort(lUartHdl);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ConfigPort, Test_AT_HSUART_ConfigPort_002)
{
    // 变量声明
    UDI_HANDLE                          lUartHdl = 1;
    AT_UART_CTX_STRU                   *pstUartCtx;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    pstUartCtx      = AT_GetUartCtxAddr();
    pstUartCtx->stPhyConfig.stFrame.enFormat = AT_UART_FORMAT_8DATA_1PARITY_1STOP;

    // 参数初始化

    // 初始化全局变量
    g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(4))
        .will(returnValue((VOS_INT32)VOS_OK));

    MOCKER(AT_HSUART_GetUdiValueByDataLen)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_HSUART_GetUdiValueByStopLen)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_HSUART_GetUdiValueByParity)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    AT_HSUART_ConfigPort(lUartHdl);

    // 执行检查
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ConfigPort, Test_AT_HSUART_ConfigPort_003)
{
    // 变量声明
    UDI_HANDLE                          lUartHdl = 1;
    AT_UART_CTX_STRU                   *pstUartCtx;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    pstUartCtx      = AT_GetUartCtxAddr();
    pstUartCtx->stPhyConfig.stFrame.enFormat = AT_UART_FORMAT_8DATA_1PARITY_1STOP;

    // 参数初始化

    // 初始化全局变量
    g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(4))
        .will(returnValue((VOS_INT32)VOS_OK));

    MOCKER(AT_HSUART_GetUdiValueByDataLen)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_HSUART_GetUdiValueByStopLen)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_HSUART_GetUdiValueByParity)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_HSUART_ConfigPort(lUartHdl);

    // 执行检查
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_IsBaudRateValid: public ::testing::Test
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


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_0;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_300;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_600;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_1200;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_2400;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_4800;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_007)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_9600;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_008)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_19200;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_009)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_38400;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_010)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_57600;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_011)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_115200;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_012)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_230400;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_013)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_1152000;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_014)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_1500000;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_015)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_2000000;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_016)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_3000000;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_017)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = 4000000000;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_018)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_460800;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsBaudRateValid, Test_AT_HSUART_IsBaudRateValid_019)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;

    // 参数初始化
    enBaudRate = AT_UART_BAUDRATE_921600;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsBaudRateValid(enBaudRate);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_IsFormatValid: public ::testing::Test
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


TEST_F(Test_AT_HSUART_IsFormatValid, Test_AT_HSUART_IsFormatValid_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;

    // 参数初始化
    enFormat = AT_UART_FORMAT_AUTO_DETECT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsFormatValid(enFormat);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsFormatValid, Test_AT_HSUART_IsFormatValid_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;

    // 参数初始化
    enFormat = AT_UART_FORMAT_8DATA_2STOP;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsFormatValid(enFormat);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsFormatValid, Test_AT_HSUART_IsFormatValid_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;

    // 参数初始化
    enFormat = AT_UART_FORMAT_8DATA_1PARITY_1STOP;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsFormatValid(enFormat);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsFormatValid, Test_AT_HSUART_IsFormatValid_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;

    // 参数初始化
    enFormat = AT_UART_FORMAT_8DATA_1STOP;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsFormatValid(enFormat);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsFormatValid, Test_AT_HSUART_IsFormatValid_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;

    // 参数初始化
    enFormat = AT_UART_FORMAT_7DATA_2STOP;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsFormatValid(enFormat);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}

TEST_F(Test_AT_HSUART_IsFormatValid, Test_AT_HSUART_IsFormatValid_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;

    // 参数初始化
    enFormat = AT_UART_FORMAT_7DATA_1PARITY_1STOP;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsFormatValid(enFormat);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsFormatValid, Test_AT_HSUART_IsFormatValid_007)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;

    // 参数初始化
    enFormat = AT_UART_FORMAT_7DATA_1STOP;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsFormatValid(enFormat);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsFormatValid, Test_AT_HSUART_IsFormatValid_008)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;


    // 参数初始化
    enFormat = AT_UART_FORMAT_BUTT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsFormatValid(enFormat);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_IsParityValid: public ::testing::Test
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


TEST_F(Test_AT_HSUART_IsParityValid, Test_AT_HSUART_IsParityValid_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;

    // 参数初始化
    enParity = AT_UART_PARITY_ODD;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsParityValid(enParity);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsParityValid, Test_AT_HSUART_IsParityValid_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;

    // 参数初始化
    enParity = AT_UART_PARITY_EVEN;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsParityValid(enParity);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsParityValid, Test_AT_HSUART_IsParityValid_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;

    // 参数初始化
    enParity = AT_UART_PARITY_MARK;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsParityValid(enParity);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsParityValid, Test_AT_HSUART_IsParityValid_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;

    // 参数初始化
    enParity = AT_UART_PARITY_SPACE;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsParityValid(enParity);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsParityValid, Test_AT_HSUART_IsParityValid_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;

    // 参数初始化
    enParity = AT_UART_PARITY_NONE;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsParityValid(enParity);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_IsParityValid, Test_AT_HSUART_IsParityValid_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;

    // 参数初始化
    enParity = AT_UART_PARITY_BUTT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_IsParityValid(enParity);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_GetUdiValueByDataLen: public ::testing::Test
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


TEST_F(Test_AT_HSUART_GetUdiValueByDataLen, Test_AT_HSUART_GetUdiValueByDataLen_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_DATA_LEN_ENUM_UINT8         enDataLen;

    // 参数初始化
    enDataLen = AT_UART_DATA_LEN_5_BIT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByDataLen(enDataLen, VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByDataLen, Test_AT_HSUART_GetUdiValueByDataLen_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_DATA_LEN_ENUM_UINT8         enDataLen;
    VOS_UINT32                          ulUdiValue;

    // 参数初始化
    enDataLen = AT_UART_DATA_LEN_6_BIT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByDataLen(enDataLen, &ulUdiValue);

    // 执行检查
    EXPECT_EQ(WLEN_6_BITS, ulUdiValue);
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByDataLen, Test_AT_HSUART_GetUdiValueByDataLen_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_DATA_LEN_ENUM_UINT8         enDataLen;
    VOS_UINT32                          ulUdiValue;

    // 参数初始化
    enDataLen = AT_UART_DATA_LEN_7_BIT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByDataLen(enDataLen, &ulUdiValue);

    // 执行检查
    EXPECT_EQ(WLEN_7_BITS, ulUdiValue);
     EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByDataLen, Test_AT_HSUART_GetUdiValueByDataLen_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_DATA_LEN_ENUM_UINT8         enDataLen;
    VOS_UINT32                          ulUdiValue;

    // 参数初始化
    enDataLen = AT_UART_DATA_LEN_8_BIT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByDataLen(enDataLen, &ulUdiValue);

    // 执行检查
    EXPECT_EQ(WLEN_8_BITS, ulUdiValue);
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByDataLen, Test_AT_HSUART_GetUdiValueByDataLen_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_DATA_LEN_ENUM_UINT8         enDataLen;
    VOS_UINT32                          ulUdiValue;

    // 参数初始化
    enDataLen = AT_UART_DATA_LEN_BUTT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByDataLen(enDataLen, &ulUdiValue);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByDataLen, Test_AT_HSUART_GetUdiValueByDataLen_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_DATA_LEN_ENUM_UINT8         enDataLen;
    VOS_UINT32                          ulUdiValue;

    // 参数初始化
    enDataLen = AT_UART_DATA_LEN_5_BIT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByDataLen(enDataLen, &ulUdiValue);

    // 执行检查
    EXPECT_EQ(WLEN_5_BITS, ulUdiValue);
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_GetUdiValueByStopLen: public ::testing::Test
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


TEST_F(Test_AT_HSUART_GetUdiValueByStopLen, Test_AT_HSUART_GetUdiValueByStopLen_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_STOP_LEN_ENUM_UINT8         enStopLen;

    // 参数初始化

    enStopLen = AT_UART_STOP_LEN_1_BIT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByStopLen(enStopLen, VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByStopLen, Test_AT_HSUART_GetUdiValueByStopLen_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_STOP_LEN_ENUM_UINT8         enStopLen;
    VOS_UINT32                          ulUdiValue;

    // 参数初始化

    enStopLen = AT_UART_STOP_LEN_1_BIT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByStopLen(enStopLen, &ulUdiValue);

    // 执行检查
    EXPECT_EQ(STP2_OFF, ulUdiValue);
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByStopLen, Test_AT_HSUART_GetUdiValueByStopLen_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_STOP_LEN_ENUM_UINT8         enStopLen;
    VOS_UINT32                          ulUdiValue;

    // 参数初始化

    enStopLen = AT_UART_STOP_LEN_2_BIT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByStopLen(enStopLen, &ulUdiValue);

    // 执行检查
    EXPECT_EQ(STP2_ON, ulUdiValue);
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByStopLen, Test_AT_HSUART_GetUdiValueByStopLen_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_STOP_LEN_ENUM_UINT8         enStopLen;
    VOS_UINT32                          ulUdiValue;

    // 参数初始化

    enStopLen = AT_UART_STOP_LEN_BUTT;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByStopLen(enStopLen, &ulUdiValue);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_GetUdiValueByParity: public ::testing::Test
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


TEST_F(Test_AT_HSUART_GetUdiValueByParity, Test_AT_HSUART_GetUdiValueByParity_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;

    // 参数初始化
    enParity = AT_UART_PARITY_ODD;
    // 初始化全局变量

    // MOCKER操作

   // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByParity(enParity,VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByParity, Test_AT_HSUART_GetUdiValueByParity_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;
   VOS_UINT32                           ulUdiValue;

    // 参数初始化
    enParity = AT_UART_PARITY_ODD;
    // 初始化全局变量

    // MOCKER操作

   // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByParity(enParity,&ulUdiValue);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(PARITY_CHECK_ODD, ulUdiValue);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByParity, Test_AT_HSUART_GetUdiValueByParity_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;
   VOS_UINT32                           ulUdiValue;

    // 参数初始化
    enParity = AT_UART_PARITY_EVEN;
    // 初始化全局变量

    // MOCKER操作

   // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByParity(enParity,&ulUdiValue);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(PARITY_CHECK_EVEN, ulUdiValue);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByParity, Test_AT_HSUART_GetUdiValueByParity_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;
   VOS_UINT32                           ulUdiValue;

    // 参数初始化
    enParity = AT_UART_PARITY_MARK;
    // 初始化全局变量

    // MOCKER操作

   // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByParity(enParity,&ulUdiValue);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(PARITY_CHECK_MARK, ulUdiValue);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByParity, Test_AT_HSUART_GetUdiValueByParity_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;
   VOS_UINT32                           ulUdiValue;

    // 参数初始化
    enParity = AT_UART_PARITY_SPACE;
    // 初始化全局变量

    // MOCKER操作

   // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByParity(enParity,&ulUdiValue);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(PARITY_CHECK_SPACE, ulUdiValue);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByParity, Test_AT_HSUART_GetUdiValueByParity_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;
   VOS_UINT32                           ulUdiValue;

    // 参数初始化
    enParity = AT_UART_PARITY_NONE;
    // 初始化全局变量

    // MOCKER操作

   // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByParity(enParity,&ulUdiValue);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(PARITY_NO_CHECK, ulUdiValue);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_GetUdiValueByParity, Test_AT_HSUART_GetUdiValueByParity_007)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    AT_UART_PARITY_ENUM_UINT8           enParity;
   VOS_UINT32                           ulUdiValue;

    // 参数初始化
    enParity = AT_UART_PARITY_BUTT;
    // 初始化全局变量

    // MOCKER操作

   // 调用被测函数
    ulRet = AT_HSUART_GetUdiValueByParity(enParity,&ulUdiValue);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

#endif


class Test_AT_UART_SendDlData: public ::testing::Test
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


TEST_F(Test_AT_UART_SendDlData, Test_AT_UART_SendDlData_001)
{
    // 变量声明
    VOS_CHAR                           *pcData = "AT\r\n";
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;

    // MOCKER操作

    // 调用被测函数
    ulResult = AT_UART_SendDlData(ucIndex, (VOS_UINT8 *)pcData, VOS_StrLen(pcData));

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_SendDlData, Test_AT_UART_SendDlData_002)
{
    // 变量声明
    VOS_CHAR                           *pcData = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;;

    // MOCKER操作

    // 调用被测函数
    ulResult = AT_UART_SendDlData(ucIndex, (VOS_UINT8 *)pcData, 0);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_SendDlData, Test_AT_UART_SendDlData_003)
{
    // 变量声明
    VOS_CHAR                           *pcData = "AT\r\n";
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_write)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    // 调用被测函数
    ulResult = AT_UART_SendDlData(ucIndex, (VOS_UINT8 *)pcData, VOS_StrLen(pcData));

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);
    EXPECT_EQ(VOS_StrLen(pcData), g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_SendDlData, Test_AT_UART_SendDlData_004)
{
    // 变量声明
    VOS_CHAR                           *pcData = "AT\r\n";
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_write)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    // 调用被测函数
    ulResult = AT_UART_SendDlData(ucIndex, (VOS_UINT8 *)pcData, VOS_StrLen(pcData));

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen);

    GlobalMockObject::verify();
}


class Test_AT_UART_SendDlDataFromOm: public ::testing::Test
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


TEST_F(Test_AT_UART_SendDlDataFromOm,Test_AT_UART_SendDlDataFromOm_001)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT32                          ulLen;

    ulLen = 5;

    memcpy(aucData, "abcd", ulLen);

    MOCKER(AT_UART_WriteDataSync)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_UART_INDEX), any(), eq(ulLen))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRslt = AT_UART_SendRawDataFromOm(aucData, VOS_NULL_PTR, ulLen);

    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_SendDlDataFromOm,Test_AT_UART_SendDlDataFromOm_002)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           aucData[5];
    VOS_UINT32                          ulLen;

    ulLen = 5;

    memcpy(aucData, "abcd", ulLen);

    MOCKER(AT_UART_WriteDataSync)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)AT_CLIENT_TAB_UART_INDEX), any(), eq(ulLen))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRslt = AT_UART_SendRawDataFromOm(aucData, VOS_NULL_PTR, ulLen);

    EXPECT_EQ(VOS_OK, ulRslt);

    GlobalMockObject::verify();
}


class Test_AT_UART_UlDataReadCB: public ::testing::Test
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


TEST_F(Test_AT_UART_UlDataReadCB, Test_AT_UART_UlDataReadCB_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;

    // MOCKER操作
    MOCKER(mdrv_udi_write)
        .expects(never());

    MOCKER(At_RcvFromUsbCom)
        .expects(never());

    // 调用被测函数
    AT_UART_UlDataReadCB();

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_UlDataReadCB, Test_AT_UART_UlDataReadCB_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    // 调用被测函数
    AT_UART_UlDataReadCB();

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_UlDataReadCB, Test_AT_UART_UlDataReadCB_003)
{
    // 变量声明
    VOS_CHAR                           *pcData = VOS_NULL_PTR;
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_UINT32                          ulIoGetCmd;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ulIoGetCmd                          = UART_IOCTL_GET_RD_BUFF;
    ucIndex                             = AT_CLIENT_TAB_UART_INDEX;
    stCtlParam.pVirAddr                 = pcData;
    stCtlParam.u32Size                  = 0;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq(ulIoGetCmd), outBoundP((VOS_VOID*)&stCtlParam, sizeof(ACM_WR_ASYNC_INFO)))
        .will(returnValue((VOS_INT32)VOS_OK));

    // 调用被测函数
    AT_UART_UlDataReadCB();

    // 执行检查

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_UlDataReadCB, Test_AT_UART_UlDataReadCB_004)
{
    // 变量声明
    VOS_CHAR                           *pcData = "AT\r\n";
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_UINT32                          ulIoGetCmd;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ulIoGetCmd                          = UART_IOCTL_GET_RD_BUFF;
    ucIndex                             = AT_CLIENT_TAB_UART_INDEX;
    stCtlParam.pVirAddr                 = pcData;
    stCtlParam.u32Size                  = VOS_StrLen(pcData);

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(any(), eq(ulIoGetCmd), outBoundP((VOS_VOID*)&stCtlParam, sizeof(ACM_WR_ASYNC_INFO)))
        .will(returnValue((VOS_INT32)VOS_OK));

    // 调用被测函数
    AT_UART_UlDataReadCB();

    // 执行检查

    GlobalMockObject::verify();
}


class Test_AT_UART_InitLink: public ::testing::Test
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


TEST_F(Test_AT_UART_InitLink, Test_AT_UART_InitLink_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    TAF_AT_NVIM_DEFAULT_LINK_OF_UART_STRU    stDefaultLinkType;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    stDefaultLinkType.enUartLinkType = AT_UART_LINK_TYPE_AT;

    // 初始化全局变量
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_MODEM;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((VOS_VOID*)&stDefaultLinkType, sizeof(stDefaultLinkType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    AT_UART_InitLink(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_MODE, gastAtClientTab[ucIndex].Mode);
    EXPECT_EQ(AT_CLIENT_ID_UART, gastAtClientTab[ucIndex].usClientId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_InitLink, Test_AT_UART_InitLink_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    TAF_AT_NVIM_DEFAULT_LINK_OF_UART_STRU    stDefaultLinkType;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    stDefaultLinkType.enUartLinkType = AT_UART_LINK_TYPE_OM;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((VOS_VOID*)&stDefaultLinkType, sizeof(stDefaultLinkType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(CBTCPM_NotifyChangePort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_AddUsedClientId2Tab)
        .expects(exactly(1))
        .with(eq((VOS_UINT16)AT_CLIENT_ID_UART));

    // 调用被测函数
    AT_UART_InitLink(ucIndex);

    // 执行检查
    EXPECT_EQ(ucIndex, gucAtOmIndex);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_InitLink, Test_AT_UART_InitLink_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    MOCKER(CBTCPM_NotifyChangePort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_AddUsedClientId2Tab)
        .expects(exactly(1))
        .with(eq((VOS_UINT16)AT_CLIENT_ID_UART));

    // 调用被测函数
    AT_UART_InitLink(ucIndex);

    // 执行检查
    EXPECT_EQ(ucIndex, gucAtOmIndex);

    GlobalMockObject::verify();
}


class Test_AT_UART_InitPort: public ::testing::Test
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


TEST_F(Test_AT_UART_InitPort, Test_AT_UART_InitPort_001)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    MOCKER(mdrv_udi_open)
        .expects(exactly(1))
        .will(returnValue((UDI_HANDLE)UDI_INVALID_HANDLE));

    // 调用被测函数
    AT_UART_InitPort();

    EXPECT_EQ(UDI_INVALID_HANDLE, g_alAtUdiHandle[ucIndex]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_InitPort, Test_AT_UART_InitPort_002)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    MOCKER(mdrv_udi_open)
        .expects(exactly(1))
        .will(returnValue((UDI_HANDLE)1));

    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    MOCKER(AT_UART_InitLink)
        .expects(exactly(1))
        .with(eq(ucIndex));

    // 调用被测函数
    AT_UART_InitPort();

    EXPECT_EQ(1, g_alAtUdiHandle[ucIndex]);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_AT_CheckHsUartUser: public ::testing::Test
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

#if (FEATURE_ON == FEATURE_AT_HSUART)

TEST_F(Test_AT_CheckHsUartUser, Test_AT_CheckHsUartUser_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_CheckHsUartUser(ucIndex);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}
#endif


TEST_F(Test_AT_CheckHsUartUser, Test_AT_CheckHsUartUser_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_CheckHsUartUser(ucIndex);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_CheckModemUser: public ::testing::Test
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


TEST_F(Test_AT_CheckModemUser, Test_AT_CheckModemUser_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_CheckModemUser(ucIndex);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_CheckModemUser, Test_AT_CheckModemUser_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType = AT_UART_USER;

    // MOCKER操作

    // 调用被测函数
    ulRet = AT_CheckModemUser(ucIndex);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_MODEM_StartFlowCtrl: public ::testing::Test
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


TEST_F(Test_AT_MODEM_StartFlowCtrl, Test_AT_MODEM_StartFlowCtrl_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量
    memset(gastAtClientTab, 0, sizeof(gastAtClientTab));
    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_CSD_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作
    MOCKER(AT_MNTN_TraceStartFlowCtrl)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_FC_DEVICE_TYPE_ENUM_UINT32)AT_FC_DEVICE_TYPE_MODEM));

    MOCKER(AT_CtrlCTS)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_LOW));

    // 调用被测函数
    ulRet = AT_MODEM_StartFlowCtrl(0, 0);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_MODEM_StopFlowCtrl: public ::testing::Test
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


TEST_F(Test_AT_MODEM_StopFlowCtrl, Test_AT_MODEM_StopFlowCtrl_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量
    memset(gastAtClientTab, 0, sizeof(gastAtClientTab));
    gastAtClientTab[ucIndex].UserType   = AT_MODEM_USER;
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_CSD_DATA_MODE;
    gastAtClientTab[ucIndex].usPppId    = 1;

    // MOCKER操作
    MOCKER(AT_MNTN_TraceStopFlowCtrl)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_FC_DEVICE_TYPE_ENUM_UINT32)AT_FC_DEVICE_TYPE_MODEM));

    MOCKER(AT_CtrlCTS)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((AT_IO_LEVEL_ENUM_UINT8)AT_IO_LEVEL_HIGH));

    // 调用被测函数
    ulRet = AT_MODEM_StopFlowCtrl(0, 0);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_UART_WriteDataSync: public ::testing::Test
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


TEST_F(Test_AT_UART_WriteDataSync, Test_AT_UART_WriteDataSync_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[2];
    VOS_UINT32                          ulLen;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    ulLen = 0;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_write)
        .expects(never());

    // 调用被测函数
    ulRet = AT_UART_WriteDataSync(ucIndex, aucData, ulLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_WriteDataSync, Test_AT_UART_WriteDataSync_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[2];
    VOS_UINT32                          ulLen;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    ulLen = 0;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_write)
        .expects(never());

    // 调用被测函数
    ulRet = AT_UART_WriteDataSync(ucIndex, aucData, ulLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_WriteDataSync, Test_AT_UART_WriteDataSync_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[2];
    VOS_UINT32                          ulLen;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    ulLen = 2;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen = 0;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailLen = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_write)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    // 调用被测函数
    ulRet = AT_UART_WriteDataSync(ucIndex, aucData, ulLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen);
    EXPECT_EQ(ulLen, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailLen);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_UART_WriteDataSync, Test_AT_UART_WriteDataSync_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[2];
    VOS_UINT32                          ulLen;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    ulLen = 2;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen = 0;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailLen = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_write)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    // 调用被测函数
    ulRet = AT_UART_WriteDataSync(ucIndex, aucData, ulLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(ulLen, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailLen);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_ConfigFlowCtrl: public ::testing::Test
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


TEST_F(Test_AT_HSUART_ConfigFlowCtrl, Test_AT_HSUART_ConfigFlowCtrl_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    uart_flow_ctrl_union                unFlowCtrlValue = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    unFlowCtrlValue.reg.rtsen = VOS_TRUE;
    unFlowCtrlValue.reg.ctsen = VOS_TRUE;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulConFlowCtrlErr = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(eq((UDI_HANDLE)1), eq((VOS_UINT32)UART_IOCTL_SET_FLOW_CONTROL), mirror((VOS_VOID*)&unFlowCtrlValue, (VOS_UINT32)sizeof(unFlowCtrlValue)))
        .will(returnValue((VOS_INT32)VOS_ERROR));

    // 调用被测函数
    AT_HSUART_ConfigFlowCtrl(ucIndex, VOS_TRUE, VOS_TRUE);

    // 执行检查
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulConFlowCtrlErr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_ConfigFlowCtrl, Test_AT_HSUART_ConfigFlowCtrl_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    uart_flow_ctrl_union                unFlowCtrlValue = {0};

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    unFlowCtrlValue.reg.rtsen = VOS_TRUE;
    unFlowCtrlValue.reg.ctsen = VOS_TRUE;

    // 初始化全局变量
    g_alAtUdiHandle[ucIndex] = 1;
    g_stAtStatsInfo.stHsUartStats.ulConFlowCtrlErr = 0;

    // MOCKER操作
    MOCKER(mdrv_udi_ioctl)
        .expects(exactly(1))
        .with(eq((UDI_HANDLE)1), eq((VOS_UINT32)UART_IOCTL_SET_FLOW_CONTROL), mirror((VOS_VOID*)&unFlowCtrlValue, (VOS_UINT32)sizeof(unFlowCtrlValue)))
        .will(returnValue((VOS_INT32)VOS_OK));

    // 调用被测函数
    AT_HSUART_ConfigFlowCtrl(ucIndex, VOS_TRUE, VOS_TRUE);

    // 执行检查
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulConFlowCtrlErr);

    GlobalMockObject::verify();
}


class Test_AT_HSUART_SendRawDataFromOm: public ::testing::Test
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


TEST_F(Test_AT_HSUART_SendRawDataFromOm, Test_AT_HSUART_SendRawDataFromOm_001)
{
    VOS_UINT8                           aucData[2];
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;

    ulLen = 2;

    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccNum = 0;

    MOCKER(AT_UART_WriteDataSync)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRet = AT_HSUART_SendRawDataFromOm(aucData, VOS_NULL_PTR, ulLen);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailNum);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HSUART_SendRawDataFromOm, Test_AT_HSUART_SendRawDataFromOm_002)
{
    VOS_UINT8                           aucData[2];
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;

    ulLen = 2;

    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailNum = 0;
    g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccNum = 0;

    MOCKER(AT_UART_WriteDataSync)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRet = AT_HSUART_SendRawDataFromOm(aucData, VOS_NULL_PTR, ulLen);

    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailNum);
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccNum);

    GlobalMockObject::verify();
}


