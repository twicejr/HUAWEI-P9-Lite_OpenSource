#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCmdSimProc.h"


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_SIM_PROC_C

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
类名     : Test_At_QrySIMSlotPara
功能描述 : At_QrySIMSlotPara UT工程类
修改历史 :
1.日    期    : 2013年07月05日
  作    者    : L47619
  修改内容    : add for SIM Insert
*****************************************************************************/
class Test_At_QrySIMSlotPara: public ::testing::Test
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
测试用例编号: Test_At_QrySIMSlotPara_001
测试用例标题: 读取NV失败
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_QrySIMSlotPara, Test_At_QrySIMSlotPara_001)
{
    // 变量声明
    VOS_UINT32  ulresult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulresult = At_QrySIMSlotPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulresult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_QrySIMSlotPara_002
测试用例标题: 读取NV成功
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_QrySIMSlotPara, Test_At_QrySIMSlotPara_002)
{
    // 变量声明
    VOS_UINT32  ulresult;
    VOS_UINT8   ucIndex = 0;

    // 参数初始化

    // 初始化全局变量
    g_stParseContext[ucIndex].pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_PAR_CMD_ELEMENT_STRU));
    memset(g_stParseContext[ucIndex].pstCmdElement, 0 ,sizeof(AT_PAR_CMD_ELEMENT_STRU));
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (VOS_UINT8*)"^SIMSLOT";

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));
    // 调用被测函数
    ulresult = At_QrySIMSlotPara(0);

    // 执行检查
    EXPECT_EQ(AT_OK, ulresult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_SetSIMSlotPara
功能描述 : At_SetSIMSlotPara UT工程类
修改历史 :
1.日    期    : 2013年07月05日
  作    者    : L47619
  修改内容    : add for SIM Insert
*****************************************************************************/
class Test_At_SetSIMSlotPara: public ::testing::Test
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
测试用例编号: Test_At_SetSIMSlotPara_001
测试用例标题: SIMSLOT命令，ucCmdOptType不正确
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_SetSIMSlotPara, Test_At_SetSIMSlotPara_001)
{
    // 变量声明
    VOS_UINT32  ulResult;

    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetSIMSlotPara(0);
    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetSIMSlotPara_002
测试用例标题: SIMSLOT命令，gucAtParaIndex不正确
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_SetSIMSlotPara, Test_At_SetSIMSlotPara_002)
{
    // 变量声明
    VOS_UINT32  ulResult;

    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetSIMSlotPara(0);
    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetSIMSlotPara_003
测试用例标题: SIMSLOT命令，参数SIM1STATE为空
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_SetSIMSlotPara, Test_At_SetSIMSlotPara_003)
{
    // 变量声明
    VOS_UINT32  ulResult;

    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 0;
    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetSIMSlotPara(0);
    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetSIMSlotPara_004
测试用例标题: SIMSLOT命令，参数SIM2STATE为空
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_SetSIMSlotPara, Test_At_SetSIMSlotPara_004)
{
    // 变量声明
    VOS_UINT32  ulResult;

    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[1].ulParaValue = 1;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetSIMSlotPara(0);
    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetSIMSlotPara_005
测试用例标题: SIMSLOT命令，读取NV项失败
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_SetSIMSlotPara, Test_At_SetSIMSlotPara_005)
{
    // 变量声明
    VOS_UINT32  ulResult;

    // 参数初始化

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 2;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulResult = At_SetSIMSlotPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetSIMSlotPara_006
测试用例标题: 设置的参数都为0，导致相等
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_SetSIMSlotPara, Test_At_SetSIMSlotPara_006)
{
    // 变量声明
    VOS_UINT32                          ulResult;
    TAF_NV_SCI_CFG_STRU                 stSCICfg;

    // 参数初始化
    stSCICfg.ulValue = 0;

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 0;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)ev_NV_Item_SCI_DSDA_CFG), outBoundP((void *)&stSCICfg, (VOS_UINT32)sizeof(stSCICfg)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulResult = At_SetSIMSlotPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetSIMSlotPara_007
测试用例标题: 写NV失败
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_SetSIMSlotPara, Test_At_SetSIMSlotPara_007)
{
    // 变量声明
    VOS_UINT32                          ulResult;
    TAF_NV_SCI_CFG_STRU                 stSCICfg;

    // 参数初始化
    stSCICfg.ulValue = 0;

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 2;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stSCICfg, (VOS_UINT32)sizeof(stSCICfg)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // 调用被测函数
    ulResult = At_SetSIMSlotPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetSIMSlotPara_008
测试用例标题: 写NV成功
预期结果    :
修改历史    :
 1.日   期  : 2013-07-05
   作   者  : L47619
   修改内容 : add for SIM Insert
******************************************************************************/
TEST_F(Test_At_SetSIMSlotPara, Test_At_SetSIMSlotPara_008)
{
    // 变量声明
    VOS_UINT32                          ulResult;
    TAF_NV_SCI_CFG_STRU                 stSCICfg;

    // 参数初始化
    stSCICfg.ulValue = 0;

    // 初始化全局变量
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 2;

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stSCICfg, (VOS_UINT32)sizeof(stSCICfg)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulResult = At_SetSIMSlotPara(0);

    // 执行检查
    EXPECT_EQ(AT_OK, ulResult);

    GlobalMockObject::verify();
}


#if (FEATURE_ON == FEATURE_VSIM)
/******************************************************************************
类名     : Test_At_SetHvpDHPara
功能描述 : At_SetHvpDHPara UT工程类
修改历史 :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
class Test_At_SetHvpDHPara: public ::testing::Test
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
测试用例编号: Test_At_SetHvpDHPara_001
测试用例标题: 参数过多
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_001)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvpDHPara_002
测试用例标题: 第一个参数为空
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_002)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 0;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvpDHPara_003
测试用例标题: 第二个参数为空
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_003)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 0;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvpDHPara_004
测试用例标题: 第二个参数长度为奇数
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_004)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 255;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvpDHPara_005
测试用例标题: 申请动态内存失败
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_005)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 256;

    // MOCKER操作
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvpDHPara_006
测试用例标题: 服务器公钥BASE16解码后长度错误
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_006)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = DRV_AGENT_DH_KEY_SERVER_PUBLIC_KEY;
    gastAtParaList[1].usParaLen = 256;

    // MOCKER操作
    MOCKER(At_Base16Decode)
        .stubs()
        .will(returnValue(200));

    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvpDHPara_007
测试用例标题: Modem侧私钥BASE16解码后长度错误
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_007)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = DRV_AGENT_DH_KEY_MODEM_PRIVATE_KEY;
    gastAtParaList[1].usParaLen = 96;

    // MOCKER操作
    MOCKER(At_Base16Decode)
        .stubs()
        .will(returnValue(200));

    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvpDHPara_008
测试用例标题: 设置服务器公钥，但发送消息失败
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_008)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = DRV_AGENT_DH_KEY_SERVER_PUBLIC_KEY;
    gastAtParaList[1].usParaLen = 256;

    // MOCKER操作
    MOCKER(At_Base16Decode)
        .stubs()
        .will(returnValue(128));

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_FAILURE));


    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvpDHPara_009
测试用例标题: 设置Modem侧私钥，发送消息成功
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_SetHvpDHPara, Test_At_SetHvpDHPara_009)
{
    // 变量声明
    VOS_UINT8       ucIndex = 0;
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = DRV_AGENT_DH_KEY_MODEM_PRIVATE_KEY;
    gastAtParaList[1].usParaLen = 96;

    // MOCKER操作
    MOCKER(At_Base16Decode)
        .stubs()
        .will(returnValue(48));

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_SUCCESS));


    // 调用被测函数
    ulResult = At_SetHvpDHPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulResult);
    EXPECT_EQ(AT_CMD_HVPDH_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_At_TestHvpDHPara
功能描述 : At_TestHvpDHPara UT工程类
修改历史 :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
class Test_At_TestHvpDHPara: public ::testing::Test
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
测试用例编号: Test_At_TestHvpDHPara_001
测试用例标题: HVPDH测试命令
预期结果    :
修改历史    :
 1.日   期  : 2013-9-3
   作   者  : L47619
   修改内容 : V9R1 vSIM项目修改
******************************************************************************/
TEST_F(Test_At_TestHvpDHPara, Test_At_TestHvpDHPara_001)
{
    // 变量声明
    VOS_UINT32      ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = At_TestHvpDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_OK, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_SetHvsDHPara
功能描述 : At_SetHvsDHPara UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_SetHvsDHPara: public ::testing::Test
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
测试用例编号: Test_At_SetHvsDHPara_001
测试用例标题: 参数过多
预期结果    : 操作失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsDHPara, Test_At_SetHvsDHPara_001)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 2;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsDHPara_002
测试用例标题: 输入字符串为空
预期结果    : 操作失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsDHPara, Test_At_SetHvsDHPara_002)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 0;

    // 调用被测函数
    ulResult = At_SetHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    // 执行检查

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsDHPara_003
测试用例标题: 输入字符串长度为奇数
预期结果    : 操作失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsDHPara, Test_At_SetHvsDHPara_003)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 31;

    // 调用被测函数
    ulResult = At_SetHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    // 执行检查

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsDHPara_004
测试用例标题: 申请空间失败
预期结果    : 操作失败，返回AT_ERROR
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsDHPara, Test_At_SetHvsDHPara_004)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 30;

    // MOCKER操作，申请内存失败
    MOCKER(V_MemAlloc)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    // 调用被测函数
    ulResult = At_SetHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsDHPara_005
测试用例标题: 密钥长度超过最大值
预期结果    : 操作失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsDHPara, Test_At_SetHvsDHPara_005)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 30;

    // MOCKER操作
    MOCKER(At_Base16Decode)
        .expects(exactly(1))
        .will(returnValue(VSIM_KEYLEN_MAX+1));

    // 调用被测函数
    ulResult = At_SetHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsDHPara_006
测试用例标题: SI_PIH_HvsDHSet操作失败
预期结果    : 操作失败，返回AT_ERROR
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsDHPara, Test_At_SetHvsDHPara_006)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 30;

    // MOCKER操作
    MOCKER(At_Base16Decode)
        .stubs()
        .will(returnValue(VSIM_KEYLEN_MAX));
    MOCKER(SI_PIH_HvsDHSet)
        .stubs()
        .will(returnValue(TAF_FAILURE));

    MOCKER(V_MemCpy)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = At_SetHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsDHPara_007
测试用例标题: 参数等均正确
预期结果    : 操作成功，返回AT_WAIT_ASYNC_RETURN
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsDHPara, Test_At_SetHvsDHPara_007)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 30;

    // MOCKER操作
    MOCKER(At_Base16Decode)
        .expects(exactly(1))
        .will(returnValue(VSIM_KEYLEN_MAX));

    MOCKER(SI_PIH_HvsDHSet)
        .expects(exactly(1))
        .will(returnValue(TAF_SUCCESS));

    MOCKER(V_MemCpy)
        .expects(exactly(1));

    // 调用被测函数
    ulResult = At_SetHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryHvsDHPara
功能描述 : At_QryHvsDHPara UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_QryHvsDHPara: public ::testing::Test
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
测试用例编号: Test_At_QryHvsDHPara_001
测试用例标题: SI_PIH_HvsDHQuery失败
预期结果    : 操作失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_QryHvsDHPara, Test_At_QryHvsDHPara_001)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(SI_PIH_HvsDHQuery)
        .expects(exactly(1))
        .will(returnValue(TAF_FAILURE));

    // 调用被测函数
    ulResult = At_QryHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_QryHvsDHPara_002
测试用例标题: SI_PIH_HvsDHQuery成功
预期结果    : 操作成功，返回AT_WAIT_ASYNC_RETURN
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_QryHvsDHPara, Test_At_QryHvsDHPara_002)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(SI_PIH_HvsDHQuery)
        .expects(exactly(1))
        .will(returnValue(TAF_SUCCESS));

    // 调用被测函数
    ulResult = At_QryHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_TestHvsDHPara
功能描述 : At_TestHvsDHPara UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_TestHvsDHPara: public ::testing::Test
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
测试用例编号: Test_At_TestHvsDHPara_001
测试用例标题: At_TestHvsDHPara测试命令
预期结果    : 操作成功，返回AT_OK
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_TestHvsDHPara, Test_At_TestHvsDHPara_001)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
   /* MOCKER(At_sprintf)
        .expects(exactly(1));*/

    // 调用被测函数
    ulResult = At_TestHvsDHPara(0);

    // 执行检查
    EXPECT_EQ(AT_OK, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_SetHvsstPara
功能描述 : At_SetHvsstPara UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_SetHvsstPara: public ::testing::Test
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
测试用例编号: Test_At_SetHvsstPara_001
测试用例标题: 参数过多
预期结果    : 测试失败，返回AT_ERROR
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_001)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 4;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_002
测试用例标题: 参数缺失
预期结果    : 测试失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_002)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_003
测试用例标题: 参数缺失
预期结果    : 测试失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_003)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[2].usParaLen = 1;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_004
测试用例标题: 参数缺失
预期结果    : 测试失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_004)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 0;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_005
测试用例标题: 传入的Index 不正确
预期结果    : 测试失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_005)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[0].ulParaValue = SI_PIH_SIM_REAL_SIM1+1;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_006
测试用例标题: 传入的Index 不正确
预期结果    : 测试失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_006)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 2;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[0].ulParaValue = SI_PIH_SIM_INDEX_BUTT;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_007
测试用例标题: 传入的enable 参数不正确
预期结果    : 测试失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_007)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 2;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[0].ulParaValue = SI_PIH_SIM_VIRT_SIM1+1;
    gastAtParaList[1].ulParaValue = SI_PIH_SIM_STATE_BUTT;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_008
测试用例标题: 传入的slot 参数不正确
预期结果    : 测试失败，返回AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_008)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 2;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[0].ulParaValue = SI_PIH_SIM_VIRT_SIM1+1;
    gastAtParaList[1].ulParaValue = SI_PIH_SIM_DISABLE;
    gastAtParaList[2].ulParaValue = SI_PIH_SIM_SLOT_BUTT;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_009
测试用例标题: SI_PIH_HvSstSet失败
预期结果    : 测试失败，返回AT_CME_PHONE_FAILURE
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_009)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 2;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[0].ulParaValue = SI_PIH_SIM_VIRT_SIM1;
    gastAtParaList[1].ulParaValue = SI_PIH_SIM_DISABLE;
    gastAtParaList[2].ulParaValue = SI_PIH_SIM_SLOT1;

    // MOCKER操作
    MOCKER(SI_PIH_HvSstSet)
        .expects(exactly(1))
        .will(returnValue(TAF_FAILURE));

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_PHONE_FAILURE, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_010
测试用例标题: SI_PIH_HvSstSet成功
预期结果    : 测试成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_010)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 2;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[0].ulParaValue = SI_PIH_SIM_VIRT_SIM1;
    gastAtParaList[1].ulParaValue = SI_PIH_SIM_DISABLE;
    gastAtParaList[2].ulParaValue = SI_PIH_SIM_SLOT1;

    // MOCKER操作
    MOCKER(SI_PIH_HvSstSet)
        .expects(exactly(1))
        .will(returnValue(TAF_SUCCESS));

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_011
测试用例标题: SI_PIH_HvSstSet输入参数不正确
预期结果    : 测试成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_011)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 2;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[0].ulParaValue = SI_PIH_SIM_VIRT_SIM1;
    gastAtParaList[1].ulParaValue = SI_PIH_SIM_STATE_BUTT;
    gastAtParaList[2].ulParaValue = SI_PIH_SIM_SLOT1;

    // MOCKER操作
    MOCKER(SI_PIH_HvSstSet)
        .expects(never())
        .will(returnValue(TAF_SUCCESS));

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_SetHvsstPara_012
测试用例标题: SI_PIH_HvSstSet输入卡槽参数不正确
预期结果    : 测试成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_SetHvsstPara, Test_At_SetHvsstPara_012)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 2;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[0].ulParaValue = SI_PIH_SIM_VIRT_SIM1;
    gastAtParaList[1].ulParaValue = SI_PIH_SIM_DISABLE;
    gastAtParaList[2].ulParaValue = SI_PIH_SIM_SLOT_BUTT;

    // MOCKER操作
    MOCKER(SI_PIH_HvSstSet)
        .expects(never())
        .will(returnValue(TAF_SUCCESS));

    // 调用被测函数
    ulResult = At_SetHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryHvsstPara
功能描述 : At_QryHvsstPara UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_QryHvsstPara: public ::testing::Test
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
测试用例编号: Test_At_QryHvsstPara_001
测试用例标题: SI_PIH_HvSstQuery操作失败
预期结果    : 操作失败，返回AT_ERROR
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_QryHvsstPara, Test_At_QryHvsstPara_001)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(SI_PIH_HvSstQuery)
        .expects(exactly(1))
        .will(returnValue(TAF_FAILURE));

    // 调用被测函数
    ulResult = At_QryHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_TestHvsstPara_002
测试用例标题:
预期结果    : 操作成功，返回AT_OK
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_QryHvsstPara, Test_At_QryHvsstPara_002)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(SI_PIH_HvSstQuery)
        .expects(exactly(1))
        .will(returnValue(TAF_SUCCESS));

    // 调用被测函数
    ulResult = At_QryHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_TestHvsstPara
功能描述 : At_TestHvsstPara UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_TestHvsstPara: public ::testing::Test
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
测试用例编号: Test_At_SetHvsstPara_001
测试用例标题:
预期结果    : 操作成功，返回AT_OK
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_TestHvsstPara, Test_At_TestHvsstPara_001)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .expects(exactly(1));*/

    // 调用被测函数
    ulResult = At_TestHvsstPara(0);

    // 执行检查
    EXPECT_EQ(AT_OK, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_QryHvsContPara
功能描述 : At_QryHvsContPara UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_QryHvsContPara: public ::testing::Test
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
测试用例编号: Test_At_QryHvsContPara_001
测试用例标题: SI_PIH_HvsContQuery操作失败
预期结果    : 操作失败，返回AT_ERROR
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_QryHvsContPara, Test_At_QryHvsContPara_001)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(SI_PIH_HvsContQuery)
        .expects(exactly(1))
        .will(returnValue(TAF_FAILURE));

    // 调用被测函数
    ulResult = At_QryHvsContPara(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_TestHvsstPara_002
测试用例标题: SI_PIH_HvsContQuery操作成功s
预期结果    : 操作成功，返回AT_OK
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_QryHvsContPara, Test_At_QryHvsContPara_002)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    MOCKER(SI_PIH_HvsContQuery)
        .expects(exactly(1))
        .will(returnValue(TAF_SUCCESS));

    // 调用被测函数
    ulResult = At_QryHvsContPara(0);

    // 执行检查
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_DealRSFWVsim
功能描述 : At_DealRSFWVsim UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_DealRSFWVsim: public ::testing::Test
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
测试用例编号: Test_At_DealRSFWVsim_001
测试用例标题: 当前Index超过最大个数
预期结果    : 操作失败，返回AT_CME_INVALID_INDEX
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_DealRSFWVsim, Test_At_DealRSFWVsim_001)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gastAtParaList[4].ulParaValue = 2;
    gastAtParaList[3].ulParaValue = 1;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_DealRSFWVsim(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INVALID_INDEX, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_DealRSFWVsim_002
测试用例标题: 传入的数据长度超过最大限制
预期结果    : 操作失败，AT_CME_TEXT_STRING_TOO_LONG
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_DealRSFWVsim, Test_At_DealRSFWVsim_002)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gastAtParaList[4].ulParaValue = 2;
    gastAtParaList[3].ulParaValue = 2;
    gastAtParaList[5].usParaLen = AT_PARA_MAX_LEN + 1;

    // MOCKER操作

    // 调用被测函数
    ulResult = At_DealRSFWVsim(0);

    // 执行检查
    EXPECT_EQ(AT_CME_TEXT_STRING_TOO_LONG, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_DealRSFWVsim_003
测试用例标题: 申请空间失败
预期结果    : 操作失败，AT_CME_MEMORY_FAILURE
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_DealRSFWVsim, Test_At_DealRSFWVsim_003)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gastAtParaList[4].ulParaValue = 2;
    gastAtParaList[3].ulParaValue = 2;
    gastAtParaList[5].usParaLen = AT_PARA_MAX_LEN;

    // MOCKER操作
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    // 调用被测函数
    ulResult = At_DealRSFWVsim(0);

    // 执行检查
    EXPECT_EQ(AT_CME_MEMORY_FAILURE, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_DealRSFWVsim_004
测试用例标题: AtBase64Decode失败
预期结果    : 操作失败，AT_CME_INCORRECT_PARAMETERS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_DealRSFWVsim, Test_At_DealRSFWVsim_004)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gastAtParaList[4].ulParaValue = 2;
    gastAtParaList[3].ulParaValue = 2;
    gastAtParaList[5].usParaLen = AT_PARA_MAX_LEN;

    // MOCKER操作
    MOCKER(AtBase64Decode)
        .stubs()
        .will(returnValue(b64Result_CODE_SIZE_ERROR));

    // 调用被测函数
    ulResult = At_DealRSFWVsim(0);

    // 执行检查
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_DealRSFWVsim_005
测试用例标题: SI_PIH_AtFileWrite失败
预期结果    : 操作失败，AT_ERROR
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_DealRSFWVsim, Test_At_DealRSFWVsim_005)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gastAtParaList[4].ulParaValue = 2;
    gastAtParaList[3].ulParaValue = 2;
    gastAtParaList[5].usParaLen = AT_PARA_MAX_LEN;

    // MOCKER操作
    MOCKER(AtBase64Decode)
        .stubs()
        .will(returnValue(b64Result_OK));
    MOCKER(SI_PIH_AtFileWrite)
        .stubs()
        .will(returnValue(TAF_FAILURE));

    // 调用被测函数
    ulResult = At_DealRSFWVsim(0);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_DealRSFWVsim_006
测试用例标题: 操作成功
预期结果    : 操作成功，AT_SUCCESS
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_DealRSFWVsim, Test_At_DealRSFWVsim_006)
{
    // 变量声明
    VOS_UINT32 ulResult;

    // 参数初始化

    // 初始化全局变量
    gastAtParaList[4].ulParaValue = 2;
    gastAtParaList[3].ulParaValue = 2;
    gastAtParaList[5].usParaLen = AT_PARA_MAX_LEN;

    // MOCKER操作
    MOCKER(AtBase64Decode)
        .stubs()
        .will(returnValue(b64Result_OK));
    MOCKER(SI_PIH_AtFileWrite)
        .stubs()
        .will(returnValue(TAF_SUCCESS));

    // 调用被测函数
    ulResult = At_DealRSFWVsim(0);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_HvsstQueryCnf
功能描述 : At_HvsstQueryCnf UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_HvsstQueryCnf: public ::testing::Test
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
测试用例编号: Test_At_HvsstQueryCnf_001
测试用例标题: VSIM使能状态
预期结果    : 操作成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_HvsstQueryCnf, Test_At_HvsstQueryCnf_001)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU stEvent;

    // 参数初始化
    V_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU), 0, 0);
    stEvent.PIHEvent.HVSSTQueryCnf.enVSimState = SI_PIH_SIM_ENABLE;
    stEvent.PIHEvent.HVSSTQueryCnf.enSlot = 1;
    stEvent.PIHEvent.HVSSTQueryCnf.enCardUse = 1;

    // 初始化全局变量

    // 调用被测函数
    At_HvsstQueryCnf(&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_HvsstQueryCnf_002
测试用例标题: VSIM 非使能状态
预期结果    : 操作成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_HvsstQueryCnf, Test_At_HvsstQueryCnf_002)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU stEvent;

    // 参数初始化
    V_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU), 0, 0);
    stEvent.PIHEvent.HVSSTQueryCnf.enVSimState = SI_PIH_SIM_DISABLE;
    stEvent.PIHEvent.HVSSTQueryCnf.enSlot = 1;
    stEvent.PIHEvent.HVSSTQueryCnf.enCardUse = 1;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    At_HvsstQueryCnf(&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_HvsContQueryCnf
功能描述 : At_HvsContQueryCnf UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_HvsContQueryCnf: public ::testing::Test
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
测试用例编号: Test_At_HvsContQueryCnf_001
测试用例标题: 上报SIM卡内容，MNC长度为2
预期结果    : 操作成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_HvsContQueryCnf, Test_At_HvsContQueryCnf_001)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU  stEvent;
    VOS_UINT8               aucImsi[] = {4,5,4,0,3,0,0,0,1,3,0,0,8,4,9};

    // 参数初始化
    V_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU), 0, 0);
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].ucIndex = 1;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].ucCardCap = 3;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].ucCardType = 2;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].ucRsv = 0;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].usPlmnNum = 0;

    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].ucIndex = 11;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].ucCardCap = 3;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].ucCardType = 2;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].ucRsv = 0;
    V_MemCpy(stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].aucImsi, aucImsi, sizeof(aucImsi), 0, 0);
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].usPlmnNum = 1;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].astPlmn[0].ulMCC = 0x40504;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].astPlmn[0].ulMNC = 0xF0300;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    At_HvsContQueryCnf(&stEvent);

    // 执行检查


    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_HvsContQueryCnf_002
测试用例标题: 上报SIM卡内容，硬卡的类型为0，软卡的MNC长度为3
预期结果    : 操作成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_HvsContQueryCnf, Test_At_HvsContQueryCnf_002)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU  stEvent;
    VOS_UINT8               aucImsi[] = {4,5,4,0,3,0,0,0,1,3,0,0,8,4,9};

    // 参数初始化
    V_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU), 0, 0);
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].ucIndex = 1;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].ucCardCap = 3;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].ucCardType = 0;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].ucRsv = 0;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM].usPlmnNum = 0;

    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].ucIndex = 11;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].ucCardCap = 3;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].ucCardType = 2;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].ucRsv = 0;
    V_MemCpy(stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].aucImsi, aucImsi, sizeof(aucImsi), 0, 0);
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].usPlmnNum = 1;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].astPlmn[0].ulMCC = 0x40504;
    stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM].astPlmn[0].ulMNC = 0x30300;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    At_HvsContQueryCnf(&stEvent);

    // 执行检查


    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_HvsDHQueryCnf
功能描述 : AT_HvsDHQueryCnf UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_AT_HvsDHQueryCnf: public ::testing::Test
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
测试用例编号: Test_AT_HvsDHQueryCnf_001
测试用例标题: 服务器公钥长度为0
预期结果    : 操作成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_AT_HvsDHQueryCnf, Test_AT_HvsDHQueryCnf_001)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU  stEvent;

    // 参数初始化
    V_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU), 0, 0);
    stEvent.PIHEvent.HvsDHCnf.enAlgorithm = 1;
    stEvent.PIHEvent.HvsDHCnf.stSkey.ulKeyLen = 0;

    // 初始化全局变量

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .expects(exactly(6))
        .will(returnValue(128));*/
    MOCKER(At_Hex2Base16)
        .expects(exactly(1))
        .will(returnValue(128));

    // 调用被测函数
    AT_HvsDHQueryCnf(&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_HvsDHQueryCnf_002
测试用例标题: 服务器公钥长度不为0
预期结果    : 操作成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_AT_HvsDHQueryCnf, Test_AT_HvsDHQueryCnf_002)
{
    // 变量声明
    SI_PIH_EVENT_INFO_STRU  stEvent;

    // 参数初始化
    V_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU), 0, 0);
    stEvent.PIHEvent.HvsDHCnf.enAlgorithm = 1;
    stEvent.PIHEvent.HvsDHCnf.stSkey.ulKeyLen = 128;

    // 初始化全局变量

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .expects(exactly(6))
        .will(returnValue(128));*/
    MOCKER(At_Hex2Base16)
        .expects(exactly(2))
        .will(returnValue(128));

    // 调用被测函数
    AT_HvsDHQueryCnf(&stEvent);

    // 执行检查

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_Base16Decode
功能描述 : At_Base16Decode UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_Base16Decode: public ::testing::Test
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
测试用例编号: Test_At_Base16Decode_00１
测试用例标题: 解析Base16编码字符串
预期结果    : 操作成功
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_Base16Decode, Test_At_Base16Decode_001)
{
    // 变量声明
    VOS_CHAR    *cInput         = "12BA3F&(bd";
    VOS_UINT32   ulDataLen      = 10;
    VOS_UINT8    ucOutput[10]   = {0};
    VOS_UINT32   ulResult       = 0;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = At_Base16Decode(cInput, ulDataLen, ucOutput);

    // 执行检查
    EXPECT_EQ(5, ulResult);
    EXPECT_EQ(0x12, ucOutput[0]);
    EXPECT_EQ(0xBA, ucOutput[1]);
    EXPECT_EQ(0x3F, ucOutput[2]);
    EXPECT_EQ(0xBD, ucOutput[4]);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_At_Hex2Base16
功能描述 : At_Hex2Base16 UT工程类
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
*****************************************************************************/
class Test_At_Hex2Base16: public ::testing::Test
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
测试用例编号: Test_At_Hex2Base_001
测试用例标题: Hex转换为Base16编码数据
预期结果    :
修改历史 :
 1.日   期  : 2013-09-03
   作   者  : zhangxuechao 00185430
   修改内容 : 新建CASE
******************************************************************************/
TEST_F(Test_At_Hex2Base16, Test_At_Hex2Base16_001)
{
    // 变量声明
    VOS_UINT32   ulMaxLength    = AT_CMD_MAX_LEN;
    VOS_UINT8    ucInput[10]    = {0xFF, 0x1E, 0x3E, 0x4F, 0x5A, 0x99, 0x10, 0x58, 0xab, 0xdA};
    VOS_UINT8    ucOutput[21]   = {0};
    VOS_UINT32   ulDataLen      = 10;
    VOS_UINT32   ulResult       = 0;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .expects(exactly(20));*/

    // 调用被测函数
    ulResult = At_Hex2Base16(ulMaxLength, (TAF_CHAR*)ucOutput, (TAF_CHAR*)ucOutput, ucInput, ulDataLen);

    // 执行检查
    EXPECT_EQ(20, ulResult);

    GlobalMockObject::verify();
}

#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
类名     : Test_AT_UiccAccessFileCnf
功能描述 : AT_UiccAccessFileCnf UT工程类
修改历史 :
1.日    期    : 2014年03月25日
  作    者    : H59254
  修改内容    : GBA开发项目
*****************************************************************************/
class Test_AT_UiccAccessFileCnf: public ::testing::Test
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
测试用例编号: Test_AT_UiccAccessFileCnf_001
测试用例标题: 读取文件的返回
预期结果    :
修改历史    :
1.日    期    : 2014年03月25日
  作    者    : H59254
  修改内容    : GBA开发项目
******************************************************************************/
TEST_F(Test_AT_UiccAccessFileCnf, Test_AT_UiccAccessFileCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulresult;
    TAF_UINT8                           ucIndex;
    SI_PIH_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    ucIndex = 0;
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    stEvent.PIHEvent.UiccAcsFileCnf.ulDataLen = 100;
    stEvent.PIHEvent.UiccAcsFileCnf.enCmdType = SI_PIH_ACCESS_READ;

    // 初始化全局变量

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(100));*/

    MOCKER(At_HexAlpha2AsciiString)
        .stubs()
        .will(returnValue(100));

    // 调用被测函数
    ulresult = AT_UiccAccessFileCnf(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(109, ulresult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_UiccAccessFileCnf_002
测试用例标题: 写入文件的返回
预期结果    :
修改历史    :
1.日    期    : 2014年03月25日
  作    者    : H59254
  修改内容    : GBA开发项目
******************************************************************************/
TEST_F(Test_AT_UiccAccessFileCnf, Test_AT_UiccAccessFileCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulresult;
    TAF_UINT8                           ucIndex;
    SI_PIH_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    ucIndex = 0;
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    stEvent.PIHEvent.UiccAcsFileCnf.ulDataLen = 0;
    stEvent.PIHEvent.UiccAcsFileCnf.enCmdType = SI_PIH_ACCESS_WRITE;

    // 初始化全局变量

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .expects(never())
        .will(returnValue(100));*/

    MOCKER(At_HexAlpha2AsciiString)
        .expects(never())
        .will(returnValue(100));

    // 调用被测函数
    ulresult = AT_UiccAccessFileCnf(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(0, ulresult);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_UiccAuthCnf
功能描述 : AT_UiccAuthCnf UT工程类
修改历史 :
1.日    期    : 2014年03月25日
  作    者    : H59254
  修改内容    : GBA开发项目
*****************************************************************************/
class Test_AT_UiccAuthCnf: public ::testing::Test
{
    public:

    void SetUp()
    {
        UT_STUB_INIT();
        gastAtClientTab[0].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;
    }
    void TearDown()
    {
        gastAtClientTab[0].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;
    }
};

/******************************************************************************
测试用例编号: Test_AT_UiccAuthCnf_001
测试用例标题: ^UICCAUTH命令AKA鉴权
预期结果    :
修改历史    :
1.日    期    : 2014年03月25日
  作    者    : H59254
  修改内容    : GBA开发项目
******************************************************************************/
TEST_F(Test_AT_UiccAuthCnf, Test_AT_UiccAuthCnf_001)
{
    // 变量声明
    VOS_UINT32                          ulresult;
    TAF_UINT8                           ucIndex;
    SI_PIH_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    ucIndex = 0;
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    stEvent.PIHEvent.UiccAuthCnf.enStatus = SI_PIH_AUTH_SUCCESS;
    stEvent.PIHEvent.UiccAuthCnf.enAuthType = SI_PIH_UICCAUTH_AKA;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UICCAUTH_SET;

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(10));*/

    MOCKER(At_HexAlpha2AsciiString)
        .stubs()
        .will(returnValue((VOS_UINT32)10));

    // 调用被测函数
    ulresult = AT_UiccAuthCnf(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(50, ulresult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_UiccAuthCnf_002
测试用例标题: ^UICCAUTH命令GBA鉴权
预期结果    :
修改历史    :
1.日    期    : 2014年03月25日
  作    者    : H59254
  修改内容    : GBA开发项目
******************************************************************************/
TEST_F(Test_AT_UiccAuthCnf, Test_AT_UiccAuthCnf_002)
{
    // 变量声明
    VOS_UINT32                          ulresult;
    TAF_UINT8                           ucIndex;
    SI_PIH_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    ucIndex = 0;
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    stEvent.PIHEvent.UiccAuthCnf.enStatus = SI_PIH_AUTH_SUCCESS;
    stEvent.PIHEvent.UiccAuthCnf.enAuthType = SI_PIH_UICCAUTH_GBA;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UICCAUTH_SET;

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(10));*/

    MOCKER(At_HexAlpha2AsciiString)
        .stubs()
        .will(returnValue((VOS_UINT32)10));

    // 调用被测函数
    ulresult = AT_UiccAuthCnf(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(24, ulresult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_UiccAuthCnf_003
测试用例标题: ^UICCAUTH命令鉴权同步失败
预期结果    :
修改历史    :
1.日    期    : 2014年03月25日
  作    者    : H59254
  修改内容    : GBA开发项目
******************************************************************************/
TEST_F(Test_AT_UiccAuthCnf, Test_AT_UiccAuthCnf_003)
{
    // 变量声明
    VOS_UINT32                          ulresult;
    TAF_UINT8                           ucIndex;
    SI_PIH_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    ucIndex = 0;
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    stEvent.PIHEvent.UiccAuthCnf.enStatus = SI_PIH_AUTH_SYNC;
    stEvent.PIHEvent.UiccAuthCnf.enAuthType = SI_PIH_UICCAUTH_GBA;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UICCAUTH_SET;

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(10));*/

    MOCKER(At_HexAlpha2AsciiString)
        .stubs()
        .will(returnValue((VOS_UINT32)10));

    // 调用被测函数
    ulresult = AT_UiccAuthCnf(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(33, ulresult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_UiccAuthCnf_004
测试用例标题: ^KSNAFAUTH命令鉴权成功
预期结果    :
修改历史    :
1.日    期    : 2014年03月25日
  作    者    : H59254
  修改内容    : GBA开发项目
******************************************************************************/
TEST_F(Test_AT_UiccAuthCnf, Test_AT_UiccAuthCnf_004)
{
    // 变量声明
    VOS_UINT32                          ulresult;
    TAF_UINT8                           ucIndex;
    SI_PIH_EVENT_INFO_STRU              stEvent;

    // 参数初始化
    ucIndex = 0;
    memset(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    stEvent.PIHEvent.UiccAuthCnf.stNAFData.aucKs_ext_NAF[0] = 16;

    // 初始化全局变量
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_KSNAFAUTH_SET;

    // MOCKER操作
    /*MOCKER(At_sprintf)
        .stubs()
        .will(returnValue(10));*/

    MOCKER(At_HexAlpha2AsciiString)
        .stubs()
        .will(returnValue((VOS_UINT32)10));

    // 调用被测函数
    ulresult = AT_UiccAuthCnf(ucIndex, &stEvent);

    // 执行检查
    EXPECT_EQ(25, ulresult);

    GlobalMockObject::verify();
}

#endif
