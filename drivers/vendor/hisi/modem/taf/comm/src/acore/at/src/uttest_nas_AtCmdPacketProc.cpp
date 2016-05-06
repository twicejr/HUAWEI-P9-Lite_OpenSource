#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCmdPacketProc.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_AT_CMD_PACKET_PROC_C


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

AT_PAR_CMD_ELEMENT_STRU             gstDhcpCmdInfo = {AT_CMD_DHCP,
    At_SetDhcpPara, AT_SET_PARA_TIME, At_QryDhcpPara, AT_QRY_PARA_TIME, AT_TestDhcpPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^DHCP", (VOS_UINT8*)"(1-11)"};

AT_PAR_CMD_ELEMENT_STRU             gstDhcpV6CmdInfo = {AT_CMD_DHCPV6,
    AT_SetDhcpv6Para,       AT_NOT_SET_TIME,  AT_QryDhcpv6Para,          AT_NOT_SET_TIME,    AT_TestDhcpv6Para, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"^DHCPV6",      (VOS_UINT8*)"(1-11)"};


#if (FEATURE_ON == FEATURE_AT_HSIC)
/*****************************************************************************
类名     : Test_AT_SetChdataPara
功能描述 : AT_SetChdataPara UT工程类
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SetChdataPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
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

        AT_PS_DATA_CHANL_CFG_STRU  stTmpCfg;
        At_PidInit(VOS_IP_INITIAL);
        ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        stTmpCfg.ulUsed        = VOS_FALSE;
        stTmpCfg.ulRmNetId     = UDI_INVAL_DEV_ID;
        stTmpCfg.ulRmNetActFlg = VOS_FALSE;

        pstModemPsCtx->astChannelCfg[1] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[2] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[3] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[4] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[5] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[6] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[7] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[8] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[9] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[10] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[11] = stTmpCfg;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_SetChdataPara_001
测试用例标题      : 命令类型不为AT_CME_INCORRECT_PARAMETERS
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 0;
    gastAtParaList[0].ulParaValue       = 0;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_AT_SetChdataPara_002
测试用例标题      : 参数个数大于2
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 3;
    gastAtParaList[0].usParaLen         = 0;
    gastAtParaList[0].ulParaValue       = 0;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetChdataPara_003
测试用例标题      : 非HSIC 1/2/3通道收到CHDATA命令
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_USBCOM_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*函数打桩*/
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_004
测试用例标题      : 第一个参数为空
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_004)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 0;
    gastAtParaList[0].ulParaValue       = 0;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_005
测试用例标题      : 第二个参数为空
预期结果          : 返回OK，删除指定CID的映射关系
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_005)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 2;
    gastAtParaList[1].usParaLen         = 0;
    gastAtParaList[1].ulParaValue       = 0;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_FALSE,     pstModemPsCtx->astChannelCfg[2].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[2].ulRmNetId);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_006
测试用例标题      : 设定CID 1对应通道为2，但CID 2之前也被映射为2
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_006)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 2;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;

    /*函数打桩*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_UNSUPPORT));

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_FALSE,     pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}


/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_007
测试用例标题      : 设定CID 1对应通道为1，且没有其他CID被配为通道1
预期结果          : 返回AT_OK，并设置CID 1与通道1的映射关系
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_007)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*函数打桩*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_UNSUPPORT));
    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_ACM_HSIC_ACM1_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_008
测试用例标题      : 设定CID 1对应通道为3，且没有其他CID被配为通道3
预期结果          : 返回AT_OK，并设置CID 1与通道1的映射关系
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_008)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 3;

    /*函数打桩*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_UNSUPPORT));
    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_ACM_HSIC_ACM5_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_009
测试用例标题      : 删除cid为2的绑定，当该cid已激活
预期结果          : 返回AT_ERROR，删除指定CID的映射关系失败
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_009)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 2;
    gastAtParaList[1].usParaLen         = 0;
    gastAtParaList[1].ulParaValue       = 0;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;
    pstModemPsCtx->astChannelCfg[2].ulRmNetActFlg   = VOS_TRUE;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_TRUE,             pstModemPsCtx->astChannelCfg[2].ulUsed);
    EXPECT_EQ(UDI_ACM_HSIC_ACM3_ID, pstModemPsCtx->astChannelCfg[2].ulRmNetId);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_010
测试用例标题      : 设定CID 1对应通道为1，且没有其他CID被配为通道1
预期结果          : 返回AT_OK，并设置CID 1与通道1的映射关系
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_010)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*函数打桩*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_SUPPORT));
    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_NCM_HSIC_NCM0_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_011
测试用例标题      : 设定CID 1对应通道为2，且没有其他CID被配为通道2
预期结果          : 返回AT_OK，并设置CID 1与通道1的映射关系
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_011)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 2;

    /*函数打桩*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_SUPPORT));
    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_NCM_HSIC_NCM1_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_012
测试用例标题      : 设定CID 1对应通道为3，且没有其他CID被配为通道3
预期结果          : 返回AT_OK，并设置CID 1与通道1的映射关系
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_012)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 3;

    /*函数打桩*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_SUPPORT));
    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_NCM_HSIC_NCM2_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_QryChdataPara
功能描述 : AT_QryChdataPara UT工程类
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryChdataPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    void SetUp()
    {
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

        At_PidInit(VOS_IP_INITIAL);
        ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        stCmdInfo.ulCmdIndex        = AT_CMD_CHDATA;
        stCmdInfo.pfnSetProc        = AT_SetChdataPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryChdataPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CHDATA";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(1-11),(1-3)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].UserType       = AT_HSIC3_USER;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryChdataPara_001
测试用例标题      : 命令类型不为AT_CMD_OPT_READ_CMD
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_QryChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryChdataPara_002
测试用例标题      : 有效映射个数为0
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_FALSE;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_QryChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryChdataPara_003
测试用例标题      : 分别输出三个通道的映射关系
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;
    pcExpactedStr   = "^CHDATA: 1,2\r\n^CHDATA: 2,3\r\n^CHDATA: 11,1";

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM5_ID;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[11].ulRmNetId      = UDI_ACM_HSIC_ACM1_ID;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_QryChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryChdataPara_004
测试用例标题      : 命令从非HSIC通道下发
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_004)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_COM_USER;

    /*函数打桩*/
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /*调用被测函数 */
    ulRet = AT_QryChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryChdataPara_005
测试用例标题      : 分别输出三个通道的映射关系
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_005)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;
    pcExpactedStr   = "^CHDATA: 1,2\r\n^CHDATA: 2,3\r\n^CHDATA: 11,1";

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = UDI_NCM_HSIC_NCM1_ID;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_NCM_HSIC_NCM2_ID;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[11].ulRmNetId      = UDI_NCM_HSIC_NCM0_ID;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_QryChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_AT_QryChdataPara_006
测试用例标题      : 分别输出三个通道的映射关系
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_006)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;
    pcExpactedStr   = "^CHDATA: 1,2\r\n^CHDATA: 2,3\r\n^CHDATA: 11,1";

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = UDI_NCM_NDIS_ID;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_QryChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_TestChdataPara
功能描述 : AT_TestChdataPara UT工程类
修改历史     :
1.日   期  : 2012-09-11
  作   者  : L60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestChdataPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        pucSystemAppConfig          = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig         = SYSTEM_APP_ANDROID;

        stCmdInfo.ulCmdIndex        = AT_CMD_CHDATA;
        stCmdInfo.pfnSetProc        = AT_SetChdataPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryChdataPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CHDATA";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(1-31),(1-5)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].UserType       = AT_APP_USER;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestChdataPara_001
测试用例标题      : 非APP通道
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestChdataPara,Test_AT_TestChdataPara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    /*函数打桩*/
    MOCKER(AT_CheckHsicUser).stubs().will(returnValue(VOS_FALSE));

    /*调用被测函数 */
    ulRet = AT_TestChdataPara(AT_CLIENT_TAB_PCUI_INDEX);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestChdataPara_002
测试用例标题      : APP通道
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2012-02-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestChdataPara,Test_AT_TestChdataPara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
#if (FEATURE_ON == FEATURE_LTE)
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    pcExpactedStr   = "^CHDATA: (1-31),(1-5)";
#else
    pcExpactedStr   = "^CHDATA: (1-31),(1-3)";
#endif
#else
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    pcExpactedStr   = "^CHDATA: (1-11),(1-5)";
#else
    pcExpactedStr   = "^CHDATA: (1-11),(1-3)";
#endif
#endif

    /*本地变量初始化*/

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_TestChdataPara(AT_CLIENT_TAB_APP_INDEX);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
#endif

/******************************************************************************
类名     : Test_At_SetDhcpPara
功能描述 : At_SetDhcpPara UT工程类
修改历史 :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增类
******************************************************************************/
class Test_At_SetDhcpPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        ucCid                           = 1;
        ucIndex                         = AT_CLIENT_TAB_APP_INDEX;
        g_stATParseCmd.ucCmdOptType     = AT_CMD_OPT_SET_PARA_CMD;
        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName            = (VOS_UINT8*)"^DHCP";
        stCmdInfo.pszParam              = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

        gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;
        gastAtParaList[0].usParaLen         = 1;
        gastAtParaList[0].aucPara[0]        = ucCid;
        gastAtParaList[0].ulParaValue       = ucCid;
        gucAtParaIndex                      = 1;

        AT_InitCtx();
        pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, 0);
        pstPsCallEntity->enIpv4State    = AT_PDP_STATE_ACTED;
        pstPsCallEntity->ucIpv4Cid      = 1;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0;

    }

    void TearDown()
    {

    }
};
/******************************************************************************
测试用例编号: Test_At_SetDhcpPara_001
测试用例标题: 通过HSIC4通道下发,查询CID为1的DHCP信息
预期结果    : 返回AT_OK
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC1_USER;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_SetDhcpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpPara_002
测试用例标题: 通过NDIS通道下发查询命令
预期结果    : 返回AT_OK
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量
    ucIndex                             = AT_CLIENT_TAB_NDIS_INDEX;

    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_SetDhcpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpPara_003
测试用例标题: 通过HSIC4通道下发,参数类型错误
预期结果    : 返回AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC3_USER;

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_SetDhcpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpPara_004
测试用例标题: 当前CID未激活
预期结果    : 返回AT_TOO_MANY_PARA
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_004)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC2_USER;

    // 初始化全局变量
    gucAtParaIndex                      = 2;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_SetDhcpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpPara_005
测试用例标题: 正在去激活
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_005)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    pstPsCallEntity->enIpv4State    = AT_PDP_STATE_DEACTING;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_SetDhcpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpPara_006
测试用例标题: 获取带宽失败
预期结果    : 返回AT_OK
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_006)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    ulRslt = At_SetDhcpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpPara_007
测试用例标题: 当前PDP未激活
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_007)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue        = ucCid + 1;

    // MOCKER操作

    // 调用被测函数
    ulRslt = At_SetDhcpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_At_QryDhcpPara_AppUser
功能描述 : At_QryDhcpPara_AppUser UT工程类
修改历史     :

1.日   期  : 2012-09-03
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryDhcpPara_AppUser: public ::testing::Test
{
public:
    void SetUp()
    {
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

        At_PidInit(VOS_IP_INITIAL);

        g_stParseContext[AT_CLIENT_TAB_PCUI_INDEX].pstCmdElement = &gstDhcpCmdInfo;
    }
    void TearDown()
    {

    }
//protected:
    //VOS_UINT8                   ucIndex;
};

/*******************************************************************
测试用例编号      : Test_At_QryDhcpPara_AppUser_001
测试用例标题      : PCUI模拟APP发起的AT^DHCP?请求，当前PDP未激活
预期结果          : 返回AT_ERROR
修改历史   :

1.日   期  : 2012-09-03
  作   者  : l60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpPara_AppUser, Test_At_QryDhcpPara_AppUser_001)
{
    //参数定义

    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_IDLE;

    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_IDLE;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    /* 查询AT^DHCP? */
    EXPECT_EQ(AT_ERROR, At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX));

    /* 上报结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryDhcpPara_AppUser_002
测试用例标题      : PCUI模拟APP发起的AT^DHCP?请求，获取带宽错误
预期结果          : 上报^DHCP:413DA8C0,00FFFFFF,413DA8C0,413DA8C0,00000000,00000000,81920000,81920000
修改历史   :

1.日   期  : 2012-09-03
  作   者  : l60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpPara_AppUser, Test_At_QryDhcpPara_AppUser_002)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                            acAtSndCode[100];

    /*本地变量初始化*/
    PS_MEM_SET(acAtSndCode, 0 ,100);

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr = 0xC0A83D41;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue(VOS_ERR));

    //MOCKER(At_sprintf).expects(exactly(9));

    /* 查询AT^DHCP? */
    ulResult = At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX);

    PS_MEM_CPY(acAtSndCode, (char *)pgucAtSndCodeAddr, VOS_StrLen((VOS_CHAR *)pgucAtSndCodeAddr));

    EXPECT_EQ(AT_OK, ulResult);

    //EXPECT_STREQ("^DHCP: 413DA8C0,00FFFFFF,423DA8C0,423DA8C0,00000000,00000000,81920000,81920000", acAtSndCode);
    /* 上报结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryDhcpPara_AppUser_003
测试用例标题      : PCUI模拟APP发起的AT^DHCP?请求，获取带宽正确
预期结果          : 上报^DHCP:413DA8C0,00FFFFFF,413DA8C0,413DA8C0,00000000,00000000,14400000,14400000
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpPara_AppUser, Test_At_QryDhcpPara_AppUser_003)
{
    VOS_UINT32                          ulResult;

    VOS_UINT32                          ulSpeed = 14400000;

    TAF_AGENT_SYS_MODE_STRU             stSysMode = {0};
    stSysMode.enRatType     = TAF_PH_INFO_WCDMA_RAT;
    stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_WCDMA;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr = 0xC0A83D41;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    MOCKER(TAF_AGENT_GetSysMode)
        .stubs()
        .with(any(), outBoundP(&stSysMode))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .with(any(), outBoundP((VOS_UINT32 *)&ulSpeed, (VOS_UINT32)sizeof(ulSpeed)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //MOCKER(At_sprintf).expects(exactly(9));

    /* 查询AT^DHCP? */
    ulResult = At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    //EXPECT_STREQ("^DHCP: 413DA8C0,00FFFFFF,423DA8C0,423DA8C0,00000000,00000000,14400000,14400000", (char *)pgucAtSndCodeAddr);
    /* 上报结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
//#endif

/*****************************************************************************
类名     : Test_At_QryDhcpPara_NdisUser
功能描述 : At_QryDhcpPara_NdisUser UT工程类
修改历史     :

1.日   期  : 2012-09-03
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_At_QryDhcpPara_NdisUser: public ::testing::Test
{
public:
    void SetUp()
    {
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

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        At_PidInit(VOS_IP_INITIAL);
        ucIndex = 0;
        g_stParseContext[ucIndex].pstCmdElement = &gstDhcpCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};

/*******************************************************************
测试用例编号      : Test_At_QryDhcpPara_NdisUser_001
测试用例标题      : PCUI模拟NDIS发起的AT^DHCP?请求，当前PDP未激活
预期结果          : 返回AT_ERROR
修改历史   :

1.日   期  : 2012-09-03
  作   者  : l60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpPara_NdisUser, Test_At_QryDhcpPara_NdisUser_001)
{
    //参数定义

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;

    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_DEACTING;

    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_IDLE;

    /* 查询AT^DHCP? */
    EXPECT_EQ(AT_ERROR, At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX));

    /* 上报结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryDhcpPara_NdisUser_002
测试用例标题      : PCUI模拟NDIS发起的AT^DHCP?请求，获取带宽错误
预期结果          : 上报^DHCP:413DA8C0,FFFFFF00,413DA8C0,413DA8C0,0,0,81920000,81920000
修改历史   :

1.日   期  : 2012-09-03
  作   者  : l60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpPara_NdisUser, Test_At_QryDhcpPara_NdisUser_002)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    pcExpactedStr   = "^DHCP: 413DA8C0,FFFFFF,423DA8C0,423DA8C0,0,0,81920000,81920000";

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr = 0xC0A83D41;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue(VOS_ERR));

    //MOCKER(At_sprintf).expects(exactly(9));

    /* 查询AT^DHCP? */
    ulResult = At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* 上报结果 */
    //ASSERT_STREQ(pcExpactedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_QryDhcpPara_NdisUser_003
测试用例标题      : PCUI模拟NDIS发起的AT^DHCP?请求，获取带宽正确
预期结果          : 上报^DHCP:413DA8C0,FFFFFF,413DA8C0,413DA8C0,0,0,14400000,14400000
修改历史   :

1.日   期  : 2012-09-03
  作   者  : l60609
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpPara_NdisUser, Test_At_QryDhcpPara_NdisUser_003)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    pcExpactedStr   = "^DHCP: 413DA8C0,FFFFFF,423DA8C0,423DA8C0,0,0,14400000,14400000";

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr = 0xC0A83D41;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    //MOCKER(At_sprintf).expects(exactly(9));

    /* 查询AT^DHCP? */
    ulResult = At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* 上报结果 */
    //EXPECT_STREQ(pcExpactedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_AT_TestDhcpPara
功能描述 : AT_TestDhcpPara UT工程类
修改历史 :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增类
******************************************************************************/
class Test_AT_TestDhcpPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        memset(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^DHCP";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }

    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};
/******************************************************************************
测试用例编号: Test_AT_TestDhcpPara_001
测试用例标题:
预期结果    :
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_AT_TestDhcpPara, Test_AT_TestDhcpPara_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;

    // MOCKER操作

    // 调用被测函数
    AT_TestDhcpPara(ucIndex);

    // 执行检查
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^DHCP: (1-11)"));
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)

/******************************************************************************
类名     : Test_At_SetDhcpv6Para
功能描述 : At_SetDhcpv6Para UT工程类
修改历史 :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增类
******************************************************************************/
class Test_At_SetDhcpv6Para: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        ucCid                           = 1;
        ucIndex                         = AT_CLIENT_TAB_APP_INDEX;
        g_stATParseCmd.ucCmdOptType     = AT_CMD_OPT_SET_PARA_CMD;
        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName            = (VOS_UINT8*)"^DHCP";
        stCmdInfo.pszParam              = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

        gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;
        gastAtParaList[0].usParaLen         = 1;
        gastAtParaList[0].aucPara[0]        = ucCid;
        gastAtParaList[0].ulParaValue       = ucCid;
        gucAtParaIndex                      = 1;

        AT_InitCtx();
        pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, 0);
        pstPsCallEntity->enIpv6State    = AT_PDP_STATE_ACTED;
        pstPsCallEntity->ucIpv6Cid      = 1;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0;

    }

    void TearDown()
    {

    }
};
/******************************************************************************
测试用例编号: Test_At_SetDhcpv6Para_001
测试用例标题: 通过HSIC4通道下发,查询CID为1的DHCP信息
预期结果    : 返回AT_OK
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC1_USER;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpv6Para_002
测试用例标题: 通过NDIS通道下发查询命令
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化

    // 初始化全局变量
    ucIndex                             = AT_CLIENT_TAB_NDIS_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpv6Para_003
测试用例标题: 通过HSIC4通道下发,参数类型错误
预期结果    : 返回AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_003)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC3_USER;

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpv6Para_004
测试用例标题: 当前CID未激活
预期结果    : 返回AT_TOO_MANY_PARA
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_004)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex                          = 2;
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC2_USER;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpv6Para_005
测试用例标题: 正在去激活
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_005)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    pstPsCallEntity->enIpv6State    = AT_PDP_STATE_DEACTING;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpv6Para_006
测试用例标题: 获取带宽失败
预期结果    : 返回AT_OK
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_006)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetDhcpv6Para_007
测试用例标题: 当前PDP未激活
预期结果    : 返回AT_ERROR
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_007)
{
    // 变量声明
    VOS_UINT32                          ulRslt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue        = ucCid + 1;

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_CheckIpv6Capability
功能描述 : AT_CheckIpv6Capability UT工程类
修改历史 :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增类
******************************************************************************/
class Test_AT_CheckIpv6Capability: public ::testing::Test
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
测试用例编号: Test_AT_CheckIpv6Capability_001
测试用例标题: AT_IPV6_CAPABILITY_IPV4_ONLY
预期结果    : 打印log
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_AT_CheckIpv6Capability, Test_AT_CheckIpv6Capability_001)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化
    AT_GetCommPsCtxAddr()->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_CheckIpv6Capability(AT_PDP_IPV6);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}
/******************************************************************************
测试用例编号: Test_AT_CheckIpv6Capability_002
测试用例标题: AT_IPV6_CAPABILITY_IPV4_ONLY
预期结果    : 打印log
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_AT_CheckIpv6Capability, Test_AT_CheckIpv6Capability_002)
{
    // 变量声明
    VOS_UINT32                          ulRslt;

    // 参数初始化
    AT_GetCommPsCtxAddr()->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV6_ONLY;
    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRslt = AT_CheckIpv6Capability(AT_PDP_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_At_QryDhcpV6Para_AppUser
功能描述: At_QryDhcpV6Para_AppUser UT工程类
修改历史    :

1.日  期 : 2012-09-03
  作  者 : l60609
  修改内容: 新生成类
*****************************************************************************/
class Test_At_QryDhcpV6Para_AppUser: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //PS_MEM_SET(&gstAtSendData, 0 , sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};

/*******************************************************************
测试用例编号     : Test_At_QryDhcpV6Para_AppUser_001
测试用例标题     : PCUI模拟APP发起的AT^DHCPV6?请求，当前PDP未激活
预期结果         : 返回AT_ERROR
修改历史  :

1.日  期 : 2012-09-03
  作  者 : l60609
  修改内容: 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpV6Para_AppUser, Test_At_QryDhcpV6Para_AppUser_001)
{
    //参数定义

    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_IDLE;

    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_IDLE;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    /* 查询AT^DHCP? */
    EXPECT_EQ(AT_ERROR, AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX));

    /* 上报结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_At_QryDhcpV6Para_AppUser_002
测试用例标题     : PCUI模拟APP发起的AT^DHCPV6?请求，获取带宽错误
预期结果         : 上报^DHCPV6:
修改历史  :

1.日  期 : 2012-09-03
  作  者 : l60609
  修改内容: 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpV6Para_AppUser, Test_At_QryDhcpV6Para_AppUser_002)
{
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    PS_MEM_SET(&g_stAtAppPdpEntity, 0 ,sizeof(g_stAtAppPdpEntity));
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_ACTED;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    g_stParseContext[AT_CLIENT_TAB_PCUI_INDEX].pstCmdElement = &gstDhcpV6CmdInfo;

    AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX);

    /* 上报结果 */
    EXPECT_STREQ("^DHCPV6: ::,::,::,::,::,::,81920000,81920000", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_At_QryDhcpV6Para_AppUser_003
测试用例标题     : PCUI模拟APP发起的AT^DHCPV6?请求，获取带宽正确
预期结果         : 上报^DHCPV6:
修改历史  :

1.日  期 : 2012-09-03
  作  者 : l60609
  修改内容: 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpV6Para_AppUser, Test_At_QryDhcpV6Para_AppUser_003)
{
    VOS_UINT32                          ulSpeed = 14400000;
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    PS_MEM_SET(&g_stAtAppPdpEntity, 0 ,sizeof(g_stAtAppPdpEntity));
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_ACTED;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .with(any(), outBoundP(&ulSpeed))
        .will(returnValue((VOS_UINT32)VOS_OK));

    g_stParseContext[AT_CLIENT_TAB_PCUI_INDEX].pstCmdElement = &gstDhcpV6CmdInfo;

    AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX);

    /* 上报结果 */
    EXPECT_STREQ("^DHCPV6: ::,::,::,::,::,::,14400000,14400000", (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名    : Test_At_QryDhcpV6Para_NdisUser
功能描述: At_QryDhcpV6Para_NdisUser UT工程类
修改历史    :

1.日  期 : 2012-09-03
  作  者 : l60609
  修改内容: 新生成类
*****************************************************************************/
class Test_At_QryDhcpV6Para_NdisUser: public ::testing::Test
{
public:
    void SetUp()
    {
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

        At_PidInit(VOS_IP_INITIAL);
       // ucIndex = AT_CLIENT_TAB_APP_INDEX;
        ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
        g_stParseContext[ucIndex].pstCmdElement = &gstDhcpV6CmdInfo;

    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};

/*******************************************************************
测试用例编号     : Test_At_QryDhcpV6Para_NdisUser_001
测试用例标题     : PCUI模拟NDIS发起的AT^DHCPV6?请求，当前PDP未激活
预期结果         : 返回AT_ERROR
修改历史  :

1.日  期 : 2012-09-03
  作  者 : l60609
  修改内容: 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpV6Para_NdisUser, Test_At_QryDhcpV6Para_NdisUser_001)
{
    //参数定义

    memset(&g_stAtNdisDhcpPara,0,sizeof(g_stAtNdisDhcpPara));

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_DEACTING;
    //g_stAtNdisDhcpPara.stIpv6Dhcp.ulIpvAddr = 0xC0A83D41;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    /* 查询AT^DHCPV6? */
    EXPECT_EQ(AT_ERROR, AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX));

    /* 上报结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_At_QryDhcpV6Para_NdisUser_002
测试用例标题     : PCUI模拟NDIS发起的AT^DHCPV6?请求，获取带宽错误
预期结果         : 上报^DHCPV6:
修改历史  :

1.日  期 : 2012-09-03
  作  者 : l60609
  修改内容: 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpV6Para_NdisUser, Test_At_QryDhcpV6Para_NdisUser_002)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    pcExpactedStr   = "^DHCPV6: ::,::,::,::,::,::,81920000,81920000";

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_ACTED;
    //g_stAtNdisDhcpPara.stIpv6Dhcp.ulIpvAddr = 0xC0A83D41;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue(VOS_ERR));

    /* 查询AT^DHCP? */
    ulResult = AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* 上报结果 */
    ASSERT_STREQ(pcExpactedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号     : Test_At_QryDhcpV6Para_NdisUser_003
测试用例标题     : PCUI模拟NDIS发起的AT^DHCPV6?请求，获取带宽正确
预期结果         : 上报^DHCPV6:
修改历史  :

1.日  期 : 2012-09-03
  作  者 : l60609
  修改内容: 新生成类
*******************************************************************/
TEST_F(Test_At_QryDhcpV6Para_NdisUser, Test_At_QryDhcpV6Para_NdisUser_003)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                           *pcExpactedStr;
    TAF_AGENT_SYS_MODE_STRU             stSysMode;

    memset(&g_stAtNdisDhcpPara,0,sizeof(g_stAtNdisDhcpPara));

    /*本地变量初始化*/
    pcExpactedStr   = "^DHCPV6: ::,::,::,::,::,::,384000,384000";

    PS_MEM_SET(&stSysMode, 0, sizeof(TAF_AGENT_SYS_MODE_STRU));

    stSysMode.enRatType     = TAF_PH_INFO_WCDMA_RAT;
    stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_WCDMA;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_ACTED;
    g_stDialConnectDisplayRate.ucWcdmaConnectRate = 3;
    //g_stAtNdisDhcpPara.stIpv6Dhcp.ulIpvAddr = 0xC0A83D41;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(TAF_AGENT_GetSysMode)
        .stubs()
        .with(eq((VOS_UINT16)AT_CLIENT_TAB_PCUI_INDEX), outBoundP((TAF_AGENT_SYS_MODE_STRU *)&stSysMode, sizeof(stSysMode)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 查询AT^DHCP? */
    ulResult = AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* 上报结果 */
    ASSERT_STREQ(pcExpactedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_At_TestDhcpv6Para
功能描述 : AT_TestDhcpv6Para UT工程类
修改历史 :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增类
******************************************************************************/
class Test_AT_TestDhcpv6Para: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        memset(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^DHCPV6";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }

    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};
/******************************************************************************
测试用例编号: Test_AT_TestDhcpv6Para_001
测试用例标题:
预期结果    :
修改历史    :
 1.日   期  : 2012-12-21
   作   者  : Y00213812
   修改内容 : C50 IPv6 项目新增
******************************************************************************/
TEST_F(Test_AT_TestDhcpv6Para, Test_AT_TestDhcpv6Para_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;

    // MOCKER操作

    // 调用被测函数
    AT_TestDhcpv6Para(ucIndex);

    // 执行检查
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^DHCPV6: (1-11)"));
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_SetApRaInfoPara
功能描述 : AT_SetApRaInfoPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_AT_SetApRaInfoPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        AT_PS_AllocCallEntity(ucIndex, &ucCallId);
        AT_PS_AssignCallIdToCid(ucIndex, cid, ucCallId);

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.enUserIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.ucUsrType     = AT_APP_USER;
        pstCallEntity->stUserInfo.ucUsrCid      = cid;
        pstCallEntity->enIpv6State              = AT_PDP_STATE_ACTED;
        pstCallEntity->ucIpv6Cid                = cid;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APRAINFO";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};
/******************************************************************************
测试用例编号: Test_AT_SetApRaInfoPara_001
测试用例标题: 命令类型错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_SetApRaInfoPara_002
测试用例标题: 命令参数个数错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_SetApRaInfoPara_003
测试用例标题: 命令参数个数错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue   = cid;
    AT_PS_FreeCallIdToCid(ucIndex, 1);
    AT_PS_FreeCallEntity(ucIndex, ucCallId);

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_SetApRaInfoPara_004
测试用例标题: 当前CID PDP未激活
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_004)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue   = cid;
    pstCallEntity->enIpv6State      = AT_PDP_STATE_ACTING;


    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_AT_SetApRaInfoPara_005
测试用例标题: 当前所有OP项为FALSE
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_005)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue   = cid;
    pstCallEntity->stIpv6RaInfo.bitOpMtuSize            = VOS_FALSE;
    pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr         = VOS_FALSE;
    pstCallEntity->stIpv6RaInfo.bitOpPreferredLifetime  = VOS_FALSE;
    pstCallEntity->stIpv6RaInfo.bitOpValidLifetime      = VOS_FALSE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_SetApRaInfoPara_006
测试用例标题: 当前所有OP项为TRUE
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_006)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue   = cid;
    pstCallEntity->stIpv6RaInfo.bitOpMtuSize            = VOS_TRUE;
    pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr         = VOS_TRUE;
    pstCallEntity->stIpv6RaInfo.bitOpPreferredLifetime  = VOS_TRUE;
    pstCallEntity->stIpv6RaInfo.bitOpValidLifetime      = VOS_TRUE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_AT_QryApRaInfoPara
功能描述 : AT_QryApRaInfoPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_AT_QryApRaInfoPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();
        pstAppRaInfoAddr               = AT_APP_GetRaInfoAddr();
        pstAppPdpEntity                = AT_APP_GetPdpEntInfoAddr();

        pstAppPdpEntity->enIpv6State   = AT_PDP_STATE_ACTED;
        pstAppPdpEntity->enIpv4v6State = AT_PDP_STATE_ACTED;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APRAINFO";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};
/******************************************************************************
测试用例编号: Test_AT_QryApRaInfoPara_001
测试用例标题: 当前不为IPV6类型
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_QryApRaInfoPara, Test_AT_QryApRaInfoPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppPdpEntity->enIpv6State    = AT_PDP_STATE_IDLE;
    pstAppPdpEntity->enIpv4v6State  = AT_PDP_STATE_IDLE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_QryApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryApRaInfoPara_002
测试用例标题: 当前所有OP项为FALSE
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_QryApRaInfoPara, Test_AT_QryApRaInfoPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppRaInfoAddr->bitOpMtuSize            = VOS_FALSE;
    pstAppRaInfoAddr->bitOpPrefixAddr         = VOS_FALSE;
    pstAppRaInfoAddr->bitOpPreferredLifetime  = VOS_FALSE;
    pstAppRaInfoAddr->bitOpValidLifetime      = VOS_FALSE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_QryApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryApRaInfoPara_003
测试用例标题: 当前所有OP项为TRUE
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_QryApRaInfoPara, Test_AT_QryApRaInfoPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppRaInfoAddr->bitOpMtuSize            = VOS_TRUE;
    pstAppRaInfoAddr->bitOpPrefixAddr         = VOS_TRUE;
    pstAppRaInfoAddr->bitOpPreferredLifetime  = VOS_TRUE;
    pstAppRaInfoAddr->bitOpValidLifetime      = VOS_TRUE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_QryApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_TestApRaInfoPara
功能描述 : AT_TestApRaInfoPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_AT_TestApRaInfoPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APRAINFO";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};
/******************************************************************************
测试用例编号: Test_AT_TestApRaInfoPara_001
测试用例标题: AT^APRAINFO=?
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_TestApRaInfoPara, Test_AT_TestApRaInfoPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_TestApRaInfoPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APRAINFO: (1-11)"));
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_SetApLanAddrPara
功能描述 : AT_SetApLanAddrPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_AT_SetApLanAddrPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        AT_PS_AllocCallEntity(ucIndex, &ucCallId);
        AT_PS_AssignCallIdToCid(ucIndex, cid, ucCallId);

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.enUserIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.ucUsrType     = AT_APP_USER;
        pstCallEntity->stUserInfo.ucUsrCid      = cid;
        pstCallEntity->enIpv6State              = AT_PDP_STATE_ACTED;
        pstCallEntity->ucIpv6Cid                = cid;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APLANADDR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};
/******************************************************************************
测试用例编号: Test_AT_SetApLanAddrPara_001
测试用例标题: 命令类型错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_SetApLanAddrPara_002
测试用例标题: 命令参数个数错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_AT_SetApLanAddrPara_003
测试用例标题: 命令参数个数错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue   = cid;
    AT_PS_FreeCallIdToCid(ucIndex, 1);
    AT_PS_FreeCallEntity(ucIndex, ucCallId);

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_SetApLanAddrPara_004
测试用例标题: 当前CID PDP未激活
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_004)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue   = cid;
    pstCallEntity->enIpv6State      = AT_PDP_STATE_ACTING;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_SetApLanAddrPara_005
测试用例标题: 当前所有OP项为FALSE
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_005)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue            = cid;
    pstCallEntity->stIpv6RaInfo.bitOpLanAddr = VOS_FALSE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_SetApLanAddrPara_006
测试用例标题: 当前所有OP项为TRUE
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_006)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue            = cid;
    pstCallEntity->stIpv6RaInfo.bitOpLanAddr = VOS_TRUE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_AT_QryApLanAddrPara
功能描述 : AT_QryApLanAddrPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_AT_QryApLanAddrPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();
        pstAppRaInfoAddr               = AT_APP_GetRaInfoAddr();
        pstAppPdpEntity                = AT_APP_GetPdpEntInfoAddr();

        pstAppPdpEntity->enIpv6State   = AT_PDP_STATE_ACTED;
        pstAppPdpEntity->enIpv4v6State = AT_PDP_STATE_ACTED;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APLANADDR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].UserType       = AT_APP_USER;
    }

    void TearDown()
    {
    }
};
/******************************************************************************
测试用例编号: Test_AT_QryApLanAddrPara_001
测试用例标题: 当前不为IPV6类型
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_QryApLanAddrPara, Test_AT_QryApLanAddrPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppPdpEntity->enIpv6State    = AT_PDP_STATE_IDLE;
    pstAppPdpEntity->enIpv4v6State  = AT_PDP_STATE_IDLE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_QryApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryApLanAddrPara_002
测试用例标题: 当前所有OP项为FALSE
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_QryApLanAddrPara, Test_AT_QryApLanAddrPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppRaInfoAddr->bitOpLanAddr = VOS_FALSE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_QryApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryApLanAddrPara_003
测试用例标题: 当前所有OP项为TRUE
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_QryApLanAddrPara, Test_AT_QryApLanAddrPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppRaInfoAddr->bitOpLanAddr = VOS_TRUE;
    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_QryApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_AT_TestApLanAddrPara
功能描述 : AT_TestApLanAddrPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_AT_TestApLanAddrPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APLANADDR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};
/******************************************************************************
测试用例编号: Test_AT_TestApLanAddrPara_001
测试用例标题: AT^APLANADDR=?
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_TestApLanAddrPara, Test_AT_TestApLanAddrPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_TestApLanAddrPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APLANADDR: (1-11)"));
    GlobalMockObject::verify();
}
/******************************************************************************
类名     : Test_At_SetApConnStPara
功能描述 : At_SetApConnStPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_At_SetApConnStPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx;
    VOS_UINT8                           ucIpv6Capability;
    VOS_CHAR                           *pcExpactedStr;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        pstCommPsCtx = AT_GetCommPsCtxAddr();
        ucIpv6Capability = pstCommPsCtx->ucIpv6Capability;

        AT_PS_AllocCallEntity(ucIndex, &ucCallId);
        AT_PS_AssignCallIdToCid(ucIndex, cid, ucCallId);

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.enUserIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.ucUsrType     = AT_APP_USER;
        pstCallEntity->stUserInfo.ucUsrCid      = cid;
        pstCallEntity->enIpv6State              = AT_PDP_STATE_ACTED;
        pstCallEntity->ucIpv6Cid                = cid;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APCONNST";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
        pstCommPsCtx->ucIpv6Capability = ucIpv6Capability;
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};
/******************************************************************************
测试用例编号: Test_At_SetApConnStPara_001
测试用例标题: 命令类型错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApConnStPara_002
测试用例标题: 命令参数个数错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApConnStPara_003
测试用例标题: 命令参数个数错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue   = cid;
    AT_PS_FreeCallIdToCid(ucIndex, 1);
    AT_PS_FreeCallEntity(ucIndex, ucCallId);

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApConnStPara_004
测试用例标题: 当前只支持IPV4
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_004)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化
    pcExpactedStr   = "^APCONNST: 0,\"IPV4\"";

    // 初始化全局变量
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
    pstCallEntity->enIpv4State     = AT_PDP_STATE_ACTING;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 0,\"IPV4\""));
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApConnStPara_005
测试用例标题: 当前只支持IPV6
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_005)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化
    pcExpactedStr   = "^APCONNST: 2,\"IPV6\"";

    // 初始化全局变量
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV6_ONLY;
    pstCallEntity->enIpv6State     = AT_PDP_STATE_IDLE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 2,\"IPV6\""));
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApConnStPara_006
测试用例标题: 当前支持AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_006)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化
    pcExpactedStr   = "^APCONNST: 1,\"IPV4\",1,\"IPV6\"";

    // 初始化全局变量
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP;
    pstCallEntity->enIpv4State     = AT_PDP_STATE_ACTED;
    pstCallEntity->enIpv6State     = AT_PDP_STATE_ACTED;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 1,\"IPV4\",1,\"IPV6\""));
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_At_SetApConnStPara_007
测试用例标题: 当前支持AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_007)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化
    pcExpactedStr   = "^APCONNST: 2,\"IPV4\",1,\"IPV6\"";

    // 初始化全局变量
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;
    pstCallEntity->enIpv4State     = AT_PDP_STATE_BUTT;
    pstCallEntity->enIpv6State     = AT_PDP_STATE_DEACTING;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 2,\"IPV4\",1,\"IPV6\""));
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_At_SetApConnStPara_008
测试用例标题: NV项填写错误
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_008)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = 0;
    pstCallEntity->enIpv4State     = AT_PDP_STATE_ACTING;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, 0);
    GlobalMockObject::verify();
}
/******************************************************************************
类名     : Test_At_QryApConnStPara
功能描述 : At_QryApConnStPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_At_QryApConnStPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();
        pstAppPdpEntity                = AT_APP_GetPdpEntInfoAddr();

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APCONNST";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};

/******************************************************************************
测试用例编号: Test_At_QryApConnStPara_001
测试用例标题: 当前只支持IPV4
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_QryApConnStPara, Test_At_QryApConnStPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppPdpEntity->enIpv4State     = AT_PDP_STATE_ACTING;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_QryApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 0"));
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_QryApConnStPara_002
测试用例标题: 当前只支持IPV6
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_QryApConnStPara, Test_At_QryApConnStPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppPdpEntity->enIpv4State = AT_PDP_STATE_IDLE;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_QryApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 2"));
    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_At_QryApConnStPara_003
测试用例标题: 当前只支持IPV4v6
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_QryApConnStPara, Test_At_QryApConnStPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstAppPdpEntity->enIpv4State     = AT_PDP_STATE_ACTED;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_QryApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 1"));
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_AT_TestApConnStPara
功能描述 : AT_TestApConnStPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_AT_TestApConnStPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APCONNST";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};
/******************************************************************************
测试用例编号: Test_AT_TestApConnStPara_001
测试用例标题: AT^APCONNST=?
预期结果    : AT_OK
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_TestApConnStPara, Test_AT_TestApConnStPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_TestApConnStPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: (1-11)"));
    GlobalMockObject::verify();
}
#endif
/*****************************************************************************
类名     : Test_AT_SetChdataPara_App
功能描述 : AT_SetChdataPara_App UT工程类
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SetChdataPara_App: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_DATA_CHANL_CFG_STRU  stTmpCfg;
        ucIndex                = AT_CLIENT_TAB_APP_INDEX;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        stTmpCfg.ulUsed        = VOS_FALSE;
        stTmpCfg.ulRmNetId     = UDI_INVAL_DEV_ID;
        stTmpCfg.ulRmNetActFlg = VOS_FALSE;

        pstModemPsCtx->astChannelCfg[1] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[2] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[3] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[4] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[5] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[6] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[7] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[8] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[9] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[10] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[11] = stTmpCfg;
    }
    void TearDown()
    {
        AT_CleanAtChdataCfg(ucIndex, 1);
    }
};

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_App_001
测试用例标题      : 第二个参数为空
预期结果          : 返回OK，删除指定CID的映射关系
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 2;
    gastAtParaList[1].usParaLen         = 0;
    gastAtParaList[1].ulParaValue       = 0;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_0;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_FALSE,     pstModemPsCtx->astChannelCfg[2].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[2].ulRmNetId);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_App_002
测试用例标题      : 设定CID 1对应通道为2，但CID 2之前也被映射为2
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 2;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_1;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_FALSE,     pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}


/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_App_003
测试用例标题      : 设定CID 1对应通道为1，且没有其他CID被配为通道1
预期结果          : 返回AT_OK，并设置CID 1与通道1的映射关系
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(RNIC_RM_NET_ID_0, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}


/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_App_004
测试用例标题      : 设定CID 1对应通道为5
预期结果          : 返回AT_ERROR
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_004)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 5;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_FALSE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}

/******************************************************************
测试用例编号      : Test_AT_SetChdataPara_App_005
测试用例标题      : 删除cid为1的绑定，当该cid已激活
预期结果          : 返回AT_ERROR，删除指定CID的映射关系失败
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_005)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet                               = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 2;
    gastAtParaList[1].usParaLen         = 0;
    gastAtParaList[1].ulParaValue       = 0;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_1;
    pstModemPsCtx->astChannelCfg[2].ulRmNetActFlg   = VOS_TRUE;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_TRUE,         pstModemPsCtx->astChannelCfg[2].ulUsed);
    EXPECT_EQ(RNIC_RM_NET_ID_1, pstModemPsCtx->astChannelCfg[2].ulRmNetId);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_QryChdataPara_App
功能描述 : AT_QryChdataPara UT工程类
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryChdataPara_App: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    void SetUp()
    {
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

        At_PidInit(VOS_IP_INITIAL);
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        stCmdInfo.ulCmdIndex        = AT_CMD_CHDATA;
        stCmdInfo.pfnSetProc        = AT_SetChdataPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryChdataPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CHDATA";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(1-11),(1-5)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].UserType       = AT_APP_USER;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryChdataPara_App_001
测试用例标题      : 分别输出三个通道的映射关系
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryChdataPara_App,Test_AT_QryChdataPara_App_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;
    pcExpactedStr   = "^CHDATA: 1,2\r\n^CHDATA: 2,3\r\n^CHDATA: 11,1";

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = RNIC_RM_NET_ID_1;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_2;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[11].ulRmNetId      = RNIC_RM_NET_ID_0;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_QryChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_AT_QryChdataPara_App_002
测试用例标题      : 分别输出三个通道的映射关系
预期结果          : 返回AT_OK
修改历史     :
1.日   期  : 2013-05-08
  作   者  : Y00213812
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryChdataPara_App,Test_AT_QryChdataPara_App_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    ulRet           = TAF_FAILURE;

    /*全局变量初始化*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = RNIC_RMNET_ID_BUTT;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_2;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[11].ulRmNetId      = RNIC_RM_NET_ID_0;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_QryChdataPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_At_SetApThroughputPara
功能描述 : At_SetApThroughputPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_At_SetApThroughputPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        pstPsModemCtx->astChannelCfg[cid].ulRmNetId = RNIC_RM_NET_ID_2;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APTHROUGHPUT";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtParaList[0].ulParaValue           = 1;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};
/******************************************************************************
测试用例编号: Test_At_SetApThroughputPara_001
测试用例标题: 命令类型错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApThroughputPara_002
测试用例标题: 命令参数个数错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApThroughputPara_003
测试用例标题: 网卡错误
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量
    pstPsModemCtx->astChannelCfg[cid].ulRmNetId = RNIC_RMNET_ID_BUTT;

    // MOCKER操作

    // 调用被测函数
    ulRelt = At_SetApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApThroughputPara_004
测试用例标题: 申请内存失败
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_004)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    // 调用被测函数
    ulRelt = At_SetApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApThroughputPara_005
测试用例标题: 发送消息失败
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_005)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    AT_RNIC_DSFLOW_IND_STRU             stMsg;
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
    ulRelt = At_SetApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetApThroughputPara_006
测试用例标题: 发送消息成功
预期结果    : AT_WAIT_ASYNC_RETURN
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_006)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    AT_RNIC_DSFLOW_IND_STRU             stMsg;
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
    ulRelt = At_SetApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRelt);
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_At_QryApThroughputPara
功能描述 : At_QryApThroughputPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_At_QryApThroughputPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        pstPsModemCtx->astChannelCfg[cid].ulRmNetId = RNIC_RM_NET_ID_2;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APTHROUGHPUT";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtParaList[0].ulParaValue           = 1;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};

/******************************************************************************
测试用例编号: Test_At_QryApThroughputPara_001
测试用例标题: 申请内存失败
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_QryApThroughputPara, Test_At_QryApThroughputPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    // 调用被测函数
    ulRelt = At_QryApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_QryApThroughputPara_002
测试用例标题: 发送消息失败
预期结果    : AT_ERROR
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_QryApThroughputPara, Test_At_QryApThroughputPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    AT_RNIC_DSFLOW_IND_STRU             stMsg;
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
    ulRelt = At_QryApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_QryApThroughputPara_003
测试用例标题: 发送消息成功
预期结果    : AT_WAIT_ASYNC_RETURN
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_At_QryApThroughputPara, Test_At_QryApThroughputPara_003)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    AT_RNIC_DSFLOW_IND_STRU             stMsg;
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
    ulRelt = At_QryApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRelt);
    GlobalMockObject::verify();
}


/******************************************************************************
类名     : Test_AT_TestApThroughputPara
功能描述 : AT_TestApThroughputPara UT工程类
修改历史 :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 项目新增类
******************************************************************************/
class Test_AT_TestApThroughputPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        pstPsModemCtx->astChannelCfg[cid].ulRmNetId = RNIC_RM_NET_ID_2;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APTHROUGHPUT";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtParaList[0].ulParaValue           = 1;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};
/******************************************************************************
测试用例编号: Test_AT_TestApThroughputPara_001
测试用例标题: 命令类型错误
预期结果    : AT_CME_INCORRECT_PARAMETERS
修改历史    :
 1.日   期  : 2013-05-07
   作   者  : Y00213812
   修改内容 : 新增函数
******************************************************************************/
TEST_F(Test_AT_TestApThroughputPara, Test_AT_TestApThroughputPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRelt;
    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRelt = AT_TestApThroughputPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APTHROUGHPUT: (1-11)"));
    GlobalMockObject::verify();
}
