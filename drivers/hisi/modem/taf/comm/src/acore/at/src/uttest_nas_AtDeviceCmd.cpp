#include "gtest/gtest.h"
#include "llt_mockcpp.h"


#include "uttest_AtDeviceCmd.h"
//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#define    THIS_FILE_ID                 PS_FILE_ID_AT_DEVICECMD_C

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


AT_PAR_CMD_ELEMENT_STRU             gstHssptCmdInfo = {AT_CMD_HSSPT,
    AT_SetHsspt  ,       AT_NOT_SET_TIME,    AT_QryHsspt,         AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^HSSPT",    (VOS_UINT8*)"(0,1,2,6)"};



/*****************************************************************************
类名     : Test_AT_SetHsspt
功能描述 : Test_AT_SetHsspt UT工程类
修改历史 :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*****************************************************************************/
class Test_AT_SetHsspt: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstHssptCmdInfo;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_SetHsspt_001
测试用例标题      : 非设置命令
预期结果          : 返回AT_DPAUPA_ERROR
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_BUTT;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_DPAUPA_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetHsspt_002
测试用例标题      : 参数个数不为1
预期结果          : 返回AT_DPAUPA_ERROR
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 2;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_DPAUPA_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetHsspt_003
测试用例标题      : DATALOCK未解锁
预期结果          : 返回AT_DATA_UNLOCK_ERROR
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_TRUE;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_SetHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_DATA_UNLOCK_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetHsspt_004
测试用例标题      : 设置W
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_004)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_FALSE;

    gastAtParaList[0].ulParaValue = 0;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_SetHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetHsspt_005
测试用例标题      : 设置DPA
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_005)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_FALSE;

    gastAtParaList[0].ulParaValue = 1;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_SetHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetHsspt_006
测试用例标题      : 设置DPA/UPA
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_006)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_FALSE;

    gastAtParaList[0].ulParaValue = 2;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_SetHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetHsspt_007
测试用例标题      : 设置HSPA+
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_007)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_FALSE;

    gastAtParaList[0].ulParaValue = 2;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_SetHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}


/*****************************************************************************
类名     : Test_AT_QryHsspt
功能描述 : Test_AT_QryHsspt UT工程类
修改历史 :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*****************************************************************************/
class Test_AT_QryHsspt: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstHssptCmdInfo;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryHsspt_001
测试用例标题      : W
预期结果          : 返回0
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_QryHsspt, Test_AT_QryHsspt_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_CHAR                           *pcExpactedStr = "^HSSPT:0";

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    stUECapa.ulHspaStatus = VOS_TRUE;
    stUECapa.enEDCHSupport    = VOS_FALSE;
    stUECapa.enHSDSCHSupport  = VOS_FALSE;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WAS_RadioAccess_Capa_New), outBoundP((void *)&stUECapa, sizeof(stUECapa)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_QryHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryHsspt_002
测试用例标题      : DPA
预期结果          : 返回1
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_QryHsspt, Test_AT_QryHsspt_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_CHAR                           *pcExpactedStr = "^HSSPT:1";

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    stUECapa.ulHspaStatus = VOS_TRUE;
    stUECapa.enEDCHSupport    = VOS_FALSE;
    stUECapa.enHSDSCHSupport  = VOS_TRUE;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WAS_RadioAccess_Capa_New), outBoundP((void *)&stUECapa, sizeof(stUECapa)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_QryHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryHsspt_003
测试用例标题      : DPA/UPA
预期结果          : 返回2
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_QryHsspt, Test_AT_QryHsspt_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_CHAR                           *pcExpactedStr = "^HSSPT:2";

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    stUECapa.ulHspaStatus = VOS_TRUE;
    stUECapa.enAsRelIndicator = AT_PTL_VER_ENUM_R6;
    stUECapa.enEDCHSupport    = VOS_TRUE;
    stUECapa.enHSDSCHSupport  = VOS_TRUE;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WAS_RadioAccess_Capa_New), outBoundP((void *)&stUECapa, sizeof(stUECapa)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_QryHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryHsspt_004
测试用例标题      : DPA/UPA
预期结果          : 返回6
修改历史          :
1.日   期  : 2012-04-21
作   者  : l60609
修改内容 :
*******************************************************************/
TEST_F(Test_AT_QryHsspt, Test_AT_QryHsspt_004)
{
    /*变量定义*/
    VOS_UINT32                          ulRet;
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_CHAR                           *pcExpactedStr = "^HSSPT:6";

    /*本地变量初始化*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    stUECapa.ulHspaStatus = VOS_TRUE;
    stUECapa.enAsRelIndicator = AT_PTL_VER_ENUM_R7;
    stUECapa.enEDCHSupport    = VOS_TRUE;
    stUECapa.enHSDSCHSupport  = VOS_TRUE;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WAS_RadioAccess_Capa_New), outBoundP((void *)&stUECapa, sizeof(stUECapa)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_QryHsspt(0);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_ExistSpecificPort
功能描述 : Test_AT_ExistSpecificPort UT工程类
修改历史 :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*****************************************************************************/
class Test_AT_ExistSpecificPort: public ::testing::Test
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
测试用例编号      : Test_AT_ExistSpecificPort_001
测试用例标题      : 存在指定类型的DIAG端口
预期结果          : 返回VOS_TRUE
修改历史          :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*******************************************************************/
TEST_F(Test_AT_ExistSpecificPort, Test_AT_ExistSpecificPort_001)
{
    /*变量定义*/
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8                           ucPortType = AT_DEV_DIAG;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* 设备切换前端口形态 */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x03,0x14,0x15, 0xA1,0xA2, 0x00};  /* 设备切换后端口形态 */
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/

    /*函数打桩*/
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_ExistSpecificPort(ucPortType);

    /* 结果验证*/
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ExistSpecificPort_002
测试用例标题      : 不存在指定类型的DIAG端口
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*******************************************************************/
TEST_F(Test_AT_ExistSpecificPort, Test_AT_ExistSpecificPort_002)
{
    /*变量定义*/
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8                           ucPortType = AT_DEV_DIAG;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* 设备切换前端口形态 */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x14,0x15, 0xA1,0xA2, 0x00};  /* 设备切换后端口形态 */
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/

    /*函数打桩*/
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_ExistSpecificPort(ucPortType);

    /* 结果验证*/
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_ExistSpecificPort_003
测试用例标题      : NV项读取失败
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*******************************************************************/
TEST_F(Test_AT_ExistSpecificPort, Test_AT_ExistSpecificPort_003)
{
    /*变量定义*/
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8                           ucPortType = AT_DEV_DIAG;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* 设备切换前端口形态 */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x14,0x15, 0xA1,0xA2, 0x00};  /* 设备切换后端口形态 */
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/

    /*函数打桩*/
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /*调用被测函数 */
    ulRet = AT_ExistSpecificPort(ucPortType);

    /* 结果验证*/
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_ExistSpecificPortChange
功能描述 : Test_AT_ExistSpecificPortChange UT工程类
修改历史 :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*****************************************************************************/
class Test_AT_ExistSpecificPortChange: public ::testing::Test
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
测试用例编号      : AT_ExistSpecificPortChange_001
测试用例标题      : 切换后的第一个端口形态为AT_DEV_CDROM
预期结果          : 返回VOS_OK但端口关闭操作不执行
修改历史          :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*******************************************************************/
TEST_F(Test_AT_ExistSpecificPortChange, AT_ExistSpecificPortChange_001)
{
    /*变量定义*/
    VOS_UINT8                           ucPortType = AT_DEV_DIAG;
    VOS_UINT8                           aucOldRewindPortStyle[AT_SETPORT_PARA_MAX_LEN] = {0};
    VOS_UINT8                           aucNewRewindPortStyle[AT_SETPORT_PARA_MAX_LEN] = {0};
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_YES;

    aucOldRewindPortStyle[0] = AT_DEV_DIAG;
    aucOldRewindPortStyle[1] = AT_DEV_PCUI;
    aucNewRewindPortStyle[0] = AT_DEV_PCUI;

    /*函数打桩*/

    /*调用被测函数 */
    ulRet = AT_ExistSpecificPortChange(ucPortType, aucOldRewindPortStyle, aucNewRewindPortStyle);

    /* 结果验证*/
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_CloseDiagPort
功能描述 : Test_AT_CloseDiagPort UT工程类
修改历史 :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*****************************************************************************/
class Test_AT_CloseDiagPort: public ::testing::Test
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
测试用例编号      : Test_AT_CloseDiagPort_001
测试用例标题      : 切换后的第一个端口形态为AT_DEV_CDROM
预期结果          : 返回VOS_OK但端口关闭操作不执行
修改历史          :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*******************************************************************/
TEST_F(Test_AT_CloseDiagPort, Test_AT_CloseDiagPort_001)
{
    /*变量定义*/
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_YES;

    stDynamicPidType.ulNvStatus = VOS_TRUE;
    stDynamicPidType.aucRewindPortStyle[0] = AT_DEV_DIAG;
    stDynamicPidType.aucRewindPortStyle[1] = AT_DEV_CDROM;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stDynamicPidType, sizeof(stDynamicPidType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .expects(never());

    /*调用被测函数 */
    ulRet = AT_CloseDiagPort();

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_OpenDiagPort
功能描述 : Test_AT_OpenDiagPort UT工程类
修改历史 :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*****************************************************************************/
class Test_AT_OpenDiagPort: public ::testing::Test
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
测试用例编号      : Test_AT_OpenDiagPort_001
测试用例标题      : 切换后的第一个端口形态为AT_DEV_CDROM
预期结果          : 返回VOS_OK但端口关闭操作不执行
修改历史          :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*******************************************************************/
TEST_F(Test_AT_OpenDiagPort, Test_AT_OpenDiagPort_001)
{
    /*变量定义*/
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_NO;

    stDynamicPidType.ulNvStatus = VOS_TRUE;
    stDynamicPidType.aucRewindPortStyle[0] = AT_DEV_PCUI;
    stDynamicPidType.aucRewindPortStyle[1] = AT_DEV_CDROM;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stDynamicPidType, sizeof(stDynamicPidType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .expects(never());

    /*调用被测函数 */
    ulRet = AT_OpenDiagPort();

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_CloseDiagPort_002
测试用例标题      : 切换后的第一个端口形态为AT_DEV_SD
预期结果          : 返回VOS_OK但端口关闭操作不执行
修改历史          :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*******************************************************************/
TEST_F(Test_AT_CloseDiagPort, Test_AT_CloseDiagPort_002)
{
    /*变量定义*/
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulRet;

    /*本地变量初始化*/
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_YES;

    stDynamicPidType.ulNvStatus = VOS_TRUE;
    stDynamicPidType.aucRewindPortStyle[0] = AT_DEV_DIAG;
    stDynamicPidType.aucRewindPortStyle[1] = AT_DEV_SD;

    /*函数打桩*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stDynamicPidType, sizeof(stDynamicPidType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .expects(never());

    /*调用被测函数 */
    ulRet = AT_CloseDiagPort();

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_GetSimLockStatus
功能描述 : Test_AT_GetSimLockStatus UT工程类
修改历史 :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*****************************************************************************/
class Test_AT_GetSimLockStatus: public ::testing::Test
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
测试用例编号      : Test_AT_GetSimLockStatus_001
测试用例标题      : 发送消息到C核获取锁卡状态OK
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2012-02-08
作   者  : f62575
修改内容 : B050 Project
*******************************************************************/
TEST_F(Test_AT_GetSimLockStatus, Test_AT_GetSimLockStatus_001)
{
    /*变量定义*/
    VOS_UINT32                                  ulRet;
    VOS_UINT8                                   ucIndex;

    /*本地变量初始化*/
    ucIndex = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = 0;

    /*函数打桩*/
    MOCKER(Taf_ParaQuery)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    MOCKER(At_StartTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    /*调用被测函数 */
    ulRet = AT_GetSimLockStatus(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_CMD_SIMLOCKSTATUS_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_PEND, g_stParseContext[ucIndex].ucClientStatus);
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_WIFI)
/*****************************************************************************
类名     : Test_AT_TestWifiPaRangePara
功能描述 : Test_AT_TestWifiPaRangePara UT工程类
修改历史     :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestWifiPaRangePara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
        stCmdInfo.ulCmdIndex        = AT_CMD_WIINFO;
        stCmdInfo.pfnSetProc        = AT_SetWifiPaRangePara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryWifiPaRangePara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestWifiPaRangePara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^WIPARANGE";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(@gainmode)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};
#if 0
/*******************************************************************
测试用例编号      : Test_AT_TestWifiPaRangePara_001
测试用例标题      : 查询当前单板支持的模式为PA模式
预期结果          : 返回AT_OK
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_TestWifiPaRangePara, Test_AT_TestWifiPaRangePara_001)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;

    /* 初始化变量 */
    pcExpactedStr = "^WIPARANGE:h";

    /* 全局变量赋值 */

    /* 桩函数 */
    MOCKER(wifi_get_pa_mode)
        .stubs()
        .will(returnValue(AT_WIFI_MODE_ONLY_PA));

    /* 调用消息入口函数 */
    ulRst = AT_TestWifiPaRangePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_TestWifiPaRangePara_002
测试用例标题      : 查询当前单板的模式为NOPA模式
预期结果          : 返回AT_OK
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_TestWifiPaRangePara, Test_AT_TestWifiPaRangePara_002)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;

    /* 初始化变量 */
    pcExpactedStr = "^WIPARANGE:l";

    /* 全局变量赋值 */

    /* 桩函数 */
    MOCKER(wifi_get_pa_mode)
        .stubs()
        .will(returnValue(AT_WIFI_MODE_ONLY_NOPA));

    /* 调用消息入口函数 */
    ulRst = AT_TestWifiPaRangePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_TestWifiPaRangePara_003
测试用例标题      : 查询当前单板支持两种模式
预期结果          : 返回AT_OK
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_TestWifiPaRangePara, Test_AT_TestWifiPaRangePara_003)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;

    /* 初始化变量 */
    pcExpactedStr = "^WIPARANGE:h,l";

    /* 全局变量赋值 */

    /* 桩函数 */
    MOCKER(wifi_get_pa_mode)
        .stubs()
        .will(returnValue(AT_WIFI_MODE_PA_NOPA));

    /* 调用消息入口函数 */
    ulRst = AT_TestWifiPaRangePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#endif
/*******************************************************************
测试用例编号      : Test_AT_TestWifiPaRangePara_004
测试用例标题      : 获取当前单板支持模式失败
预期结果          : 返回AT_ERROR
修改历史   :

1.日   期  : 2012-02-08
  作   者  : l00198894
  修改内容 : 新生成类
*******************************************************************/
TEST_F(Test_AT_TestWifiPaRangePara, Test_AT_TestWifiPaRangePara_004)
{
    /*变量定义*/
    VOS_UINT32                          ulRst = 0;

    /* 全局变量赋值 */

    /* 桩函数 */
    MOCKER(wifi_get_pa_mode)
        .stubs()
        .will(returnValue(-1));

    /* 调用消息入口函数 */
    ulRst = AT_TestWifiPaRangePara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

#endif

AT_PAR_CMD_ELEMENT_STRU     gstWiwepCmdInfo = {AT_CMD_WIWEP,
    AT_SetWiwepPara,        AT_SET_PARA_TIME,   AT_QryWiwepPara,  AT_QRY_PARA_TIME,  AT_TestWiwepPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"^WIWEP",    (VOS_UINT8 *)"(0-3),(@wifikey)"};

AT_PAR_CMD_ELEMENT_STRU     gstTbatCmdInfo = {AT_CMD_TBAT,
    AT_SetTbatPara,     AT_SET_PARA_TIME,   AT_QryTbatPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^TBAT",    (VOS_UINT8 *)"(1),(0,1),(0-65535),(0-65535)"};

AT_PAR_CMD_ELEMENT_STRU     gstCmdLenCmdInfo = {AT_CMD_CMDLEN,
    AT_SetCmdlenPara,        AT_SET_PARA_TIME,   AT_QryCmdlenPara,  AT_QRY_PARA_TIME,  At_CmdTestProcOK, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^CMDLEN",    (VOS_UINT8 *)"(0-65535),(0-65535)"};

AT_PAR_CMD_ELEMENT_STRU     gstTseLrfCmdInfo = {AT_CMD_TSELRF,
    AT_SetTseLrfPara,        AT_SET_PARA_TIME,   AT_QryTseLrfPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^TSELRF",    (VOS_UINT8 *)"(1,2,3,7)"};

AT_PAR_CMD_ELEMENT_STRU     gstPstandbyCmdInfo = {AT_CMD_PSTANDBY,
    AT_SetPstandbyPara,     AT_SET_PARA_TIME,   VOS_NULL_PTR,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^PSTANDBY",    (VOS_UINT8 *)"(0-65535),(0-65535)"};

/*AT_PAR_CMD_ELEMENT_STRU     gstCmdLenCmdInfo = {AT_CMD_CMDLEN,
    AT_SetCmdlenPara,        AT_SET_PARA_TIME,   AT_QryCmdlenPara,  AT_QRY_PARA_TIME,  At_CmdTestProcOK, AT_SET_PARA_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^CMDLEN",    (VOS_UINT8 *)"(0-65535),(0-65535)"};*/

#if 0
/*****************************************************************************
类名     : Test_AT_QryTbatPara
功能描述 : Test_AT_QryTbatPara UT工程类
修改历史 :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryTbatPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstTbatCmdInfo;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryTbatPara_001
测试用例标题      : ^TBAT命令获取电池安装方式
预期结果          : 根据AT手册格式返回
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryTbatPara, Test_AT_QryTbatPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    char                                  *paucExpectedStr = "^TBAT:1";
    VOS_UINT32                             usExpectedStrLen;

    /*本地变量初始化*/
    ucIndex = 0;

    /*调用被测函数 */
    ulRet = AT_QryTbatPara(ucIndex);

    /* 结果验证*/
    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);
}
#endif
/*****************************************************************************
类名     : Test_AT_QryWiwepPara
功能描述 : Test_AT_QryWiwepPara UT工程类
修改历史 :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryWiwepPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        g_stParseContext[0].pstCmdElement = &gstWiwepCmdInfo;
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryWiwepPara_001
测试用例标题      : WIFI KEY信息查询成功
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryWiwepPara, Test_AT_QryWiwepPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    TAF_AT_MULTI_WIFI_SEC_STRU             stWifiSecInfo;
    VOS_UINT8                              aucwlKeys1[] = "1234";
    VOS_UINT8                              aucwlKeys2[] = "12345";
    VOS_UINT8                              aucwlKeys3[] = "12346";
    VOS_UINT8                              aucwlKeys4[] = "12347";
    char                                  *paucExpectedStr = "^WIWEP:4\r\n^WIWEP:0,1234,0\r\n^WIWEP:1,12345,0\r\n^WIWEP:2,12346,0\r\n^WIWEP:3,12347,0\r\n";
    VOS_UINT32                             usExpectedStrLen;

    /*本地变量初始化*/
    ucIndex = 0;
    g_bAtDataLocked = VOS_FALSE;

    PS_MEM_SET(&stWifiSecInfo, 0x00, sizeof(stWifiSecInfo));
    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey1, aucwlKeys1, sizeof(aucwlKeys1));
    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey2, aucwlKeys2, sizeof(aucwlKeys2));
    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey3, aucwlKeys3, sizeof(aucwlKeys3));
    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey4, aucwlKeys4, sizeof(aucwlKeys4));
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiSecInfo, sizeof(stWifiSecInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*调用被测函数 */
    ulRet = AT_QryWiwepPara(ucIndex);

    // 执行检查
    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr) - strlen("\r\n");
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryWiwepPara_002
测试用例标题      : 内存申请失败，WIFI KEY信息查询失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryWiwepPara, Test_AT_QryWiwepPara_002)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*申请内存失败*/
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /*调用被测函数 */
    ulRet = AT_QryWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_QryWiwepPara_003
测试用例标题      : NV项en_NV_Item_MULTI_WIFI_KEY读取失败，WIFI KEY信息查询失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryWiwepPara, Test_AT_QryWiwepPara_003)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_bAtDataLocked = VOS_FALSE;

    /*NV项读取操作失败*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));


    /*调用被测函数 */
    ulRet = AT_QryWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


#if (FEATURE_ON != FEATURE_LTE)
/*****************************************************************************
类名     : Test_AT_SetTbatPara
功能描述 : Test_AT_SetTbatPara UT工程类
修改历史 :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SetTbatPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstTbatCmdInfo;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_001
测试用例标题      : ^TBAT命令获取电池电压数字值
预期结果          : 函数返回AT_WAIT_ASYNC_RETURN
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 2;

    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;

    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 0;

    /*本地变量初始化*/
    ucIndex = 0;

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq(DRV_AGENT_HKADC_GET_REQ), any(), any(), any())
        .will(returnValue(TAF_SUCCESS));

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_002
测试用例标题      : ^TBAT命令获取电池电压数字值失败
预期结果          : 函数返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_002)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 2;

    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;

    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 0;

    /*本地变量初始化*/
    ucIndex = 0;

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq(DRV_AGENT_HKADC_GET_REQ), any(), any(), any())
        .will(returnValue(TAF_FAILURE));

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_003
测试用例标题      : 设置电池电压数字值，用于电池校准
预期结果          : 函数返回AT_OK
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_003)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_INT                                TbatHkadc;
    VOS_UINT16                             usExpectedStrLen;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 4;

    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;

    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;

    gastAtParaList[2].usParaLen = 4;
    gastAtParaList[2].ulParaValue = 3700;

    gastAtParaList[3].usParaLen = 4;
    gastAtParaList[3].ulParaValue = 4200;

    /*本地变量初始化*/
    ucIndex = 0;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_004
测试用例标题      : 设置电池电压数字值，用于电池校准，写NV项失败
预期结果          : 函数返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_004)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_INT                                TbatHkadc;
    VOS_UINT16                             usExpectedStrLen;
    const char                             cWarning[] = "AT_SetTbatPara: Fail to write NV en_NV_Item_BATTERY_ADC.";

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 4;

    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;

    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;

    gastAtParaList[2].usParaLen = 4;
    gastAtParaList[2].ulParaValue = 3700;

    gastAtParaList[3].usParaLen = 4;
    gastAtParaList[3].ulParaValue = 4200;

    /*本地变量初始化*/
    ucIndex = 0;

    /*NV项读取操作失败*/
    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /* 写NV项失败的告警信息 */
    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
#if 0
/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_004
测试用例标题      : ^TBAT命令设置命令参数检查,操作类型为模拟电池电压
预期结果          : 返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_004)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    gastAtParaList[0].ulParaValue = AT_TBAT_BATTERY_ANALOG_VOLTAGE;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);
    GlobalMockObject::verify();
}
#endif
/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_006
测试用例标题      : ^TBAT设置命令操作类型错误
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_006)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_007
测试用例标题      : ^TBAT设置命令第一个参数为空
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_007)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_008
测试用例标题      : ^TBAT设置命令第二个参数为空
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_008)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[1].ulParaValue = 1;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_009
测试用例标题      : ^TBAT设置命令电池电压数字值查询参数个数不是2
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_009)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 0;

    gucAtParaIndex = 3;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_010
测试用例标题      : ^TBAT设置命令电池电压数字值设置参数个数不是4
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_010)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;

    gucAtParaIndex = 3;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_011
测试用例标题      : ^TBAT设置命令电池电压数字值设置第三个参数为空
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_011)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;
    gastAtParaList[2].usParaLen = 0;
    gastAtParaList[3].usParaLen = 4;
    gastAtParaList[3].ulParaValue = 4200;

    gucAtParaIndex = 4;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_SetTbatPara_012
测试用例标题      : ^TBAT设置命令电池电压数字值设置第四个参数为空
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_012)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;
    gastAtParaList[2].usParaLen = 4;
    gastAtParaList[2].ulParaValue = 3700;
    gastAtParaList[3].usParaLen = 0;

    gucAtParaIndex = 4;

    /*调用被测函数 */
    ulRet = AT_SetTbatPara(ucIndex);

    /* 结果验证*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}
#endif
/*****************************************************************************
类名     : Test_AT_SetWiwepPara
功能描述 : Test_AT_SetWiwepPara UT工程类
修改历史 :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SetWiwepPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstWiwepCmdInfo;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_001
测试用例标题      : 设置指定INDEX的WiFi WEP（WIFI的KEY）内容成功
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    g_bAtDataLocked = VOS_FALSE;

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_002
测试用例标题      : 申请内存失败，设置指定INDEX的WiFi WEP（WIFI的KEY）内容失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_002)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*申请内存失败*/
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_003
测试用例标题      : 读取en_NV_Item_MULTI_WIFI_KEY失败，设置指定INDEX的WiFi WEP（WIFI的KEY）内容失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_003)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*NV项读取操作失败*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    g_bAtDataLocked = VOS_FALSE;

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_004
测试用例标题      : 写en_NV_Item_MULTI_WIFI_KEY失败，设置指定INDEX的WiFi WEP（WIFI的KEY）内容失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_004)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*NV项读取操作失败*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    g_bAtDataLocked = VOS_FALSE;


    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_005
测试用例标题      : 设置操作类型为无参数设置操作，设置指定INDEX的WiFi WEP（WIFI的KEY）内容失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_005)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_006
测试用例标题      : 设置操作参数个数不为2，设置指定INDEX的WiFi WEP（WIFI的KEY）内容失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_006)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 4;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 0;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_007
测试用例标题      : 设置操作第一个参数为空，设置指定INDEX的WiFi WEP（WIFI的KEY）内容失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_007)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_008
测试用例标题      : 设置操作第二个参数为空，设置指定INDEX的WiFi WEP（WIFI的KEY）内容失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_008)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_009
测试用例标题      : 设置操作第二个参数长度超过允许值，设置指定INDEX的WiFi WEP（WIFI的KEY）内容失败
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_009)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = AT_NV_WLKEY_LEN + 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_010
测试用例标题      : 设置指定INDEX的WiFi WEP（WIFI的KEY）内容：无参数输入    
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_010)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = AT_NV_WLKEY_LEN + 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_011
测试用例标题      : 设置指定INDEX的WiFi WEP（WIFI的KEY）内容：第一个参数长度为0
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_011)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = AT_NV_WLKEY_LEN + 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_011
测试用例标题      : 设置指定INDEX的WiFi WEP（WIFI的KEY）内容：第一个参数长度为0
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_012)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = AT_NV_WLKEY_LEN + 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_013
测试用例标题      : 设置指定INDEX的WiFi WEP（WIFI的KEY）内容：第二个参数长度为0
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_013)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetWiwepPara_014
测试用例标题      : 设置指定INDEX的WiFi WEP（WIFI的KEY）内容：待写入的WIWEP数据与NV中的相同
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_014)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey1[] = "12345";
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;
    TAF_AT_MULTI_WIFI_SEC_STRU             stWifiSecInfo;

    /*本地变量初始化*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = 5 ;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey1, aucWifiKey1, sizeof(aucWifiKey1));
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiSecInfo,sizeof(stWifiSecInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*调用被测函数 */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* 结果验证*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_TestWiwepPara
功能描述 : Test_AT_TestWiwepPara UT工程类
修改历史 :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestWiwepPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstWiwepCmdInfo;

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestWiwepPara_001
测试用例标题      : WIWEP的测试命令
预期结果          : 输出工位支持的WIFI KEY总数
修改历史          :
1.日   期  : 2012-1-10
作   者  : f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestWiwepPara, Test_AT_TestWiwepPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    char                                  *paucExpectedStr = "^WIWEP:16";
    VOS_UINT32                             usExpectedStrLen;

    /*本地变量初始化*/
    ucIndex = 0;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    /*调用被测函数 */
    ulRet = AT_TestWiwepPara(ucIndex);

    /* 结果验证*/
    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_GetTseLrfLoadDspInfo
功能描述 : Test_AT_GetTseLrfLoadDspInfo UT工程类
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_GetTseLrfLoadDspInfo: public ::testing::Test
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
测试用例编号      : Test_AT_GetTseLrfLoadDspInfo_001
测试用例标题      : ^TSELRF命令是否触发LOAD DSP：^TSELRF命令设置的射频通路编号为GSM且当前已经LOAD了该通路，无需LOAD DSP
                    g_stAtDevCmdCtrl.ucDeviceRatMode为AT_RAT_MODE_GSM
                    g_stAtDevCmdCtrl.bDspLoadFlag为VOS_TRUE
预期结果          : 无需LOAD DSP
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_001)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_GSM;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_GSM;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_GSM;
    bLoadDsp                   = VOS_TRUE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_FALSE, bLoadDsp);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetTseLrfLoadDspInfo_002
测试用例标题      : ^TSELRF命令是否触发LOAD DSP：^TSELRF命令设置的射频通路编号为GSM 但没有LOAD通路，需要LOAD DSP
                    g_stAtDevCmdCtrl.ucDeviceRatMode为AT_RAT_MODE_GSM
                    g_stAtDevCmdCtrl.bDspLoadFlag为VOS_TRUE
预期结果          : 需要LOAD DSP
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_002)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_GSM;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_FALSE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_GSM;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_GSM;
    bLoadDsp                   = VOS_TRUE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_TRUE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_GSM, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_GSM, stTseLrf.ucDeviceRatMode);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetTseLrfLoadDspInfo_003
测试用例标题      : ^TSELRF命令是否触发LOAD DSP：^TSELRF命令设置的射频通路编号为WCDMA，需要LOAD DSP
                    g_stAtDevCmdCtrl.ucDeviceRatMode为AT_RAT_MODE_WCDMA
                    g_stAtDevCmdCtrl.bDspLoadFlag为VOS_TRUE
预期结果          : 需要LOAD DSP
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_003)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_GSM;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_FALSE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_GSM;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_GSM;
    bLoadDsp                   = VOS_TRUE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_TRUE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_GSM, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_GSM, stTseLrf.ucDeviceRatMode);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetTseLrfLoadDspInfo_004
测试用例标题      : ^TSELRF命令是否触发LOAD DSP：^TSELRF命令设置的射频通路编号为WCDMA已有LOAD通路，不需要LOAD DSP
                    g_stAtDevCmdCtrl.ucDeviceRatMode为AT_RAT_MODE_WCDMA
                    g_stAtDevCmdCtrl.bDspLoadFlag为VOS_TRUE
预期结果          : 不需要LOAD DSP
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_004)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_WCDMA_PRI;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_TRUE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_FALSE, bLoadDsp);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetTseLrfLoadDspInfo_005
测试用例标题      : ^TSELRF命令是否触发LOAD DSP：^TSELRF命令设置的射频通路编号为WCDMA没有LOAD通路，需要LOAD DSP
                    g_stAtDevCmdCtrl.ucDeviceRatMode为AT_RAT_MODE_AWS
                    g_stAtDevCmdCtrl.bDspLoadFlag为VOS_TRUE
预期结果          : 需要LOAD DSP
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_005)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_WCDMA_PRI;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_AWS;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_FALSE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_FALSE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_WCDMA, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_WCDMA, stTseLrf.ucDeviceRatMode);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetTseLrfLoadDspInfo_006
测试用例标题      : ^TSELRF命令是否触发LOAD DSP：^TSELRF命令设置的射频通路编号为WCDMA没有LOAD通路，需要LOAD DSP
                    g_stAtDevCmdCtrl.ucDeviceRatMode为AT_RAT_MODE_WCDMA
                    g_stAtDevCmdCtrl.bDspLoadFlag为VOS_FALSE
预期结果          : 需要LOAD DSP
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_006)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_WCDMA_PRI;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_FALSE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_FALSE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_TRUE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_WCDMA, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_WCDMA, stTseLrf.ucDeviceRatMode);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetTseLrfLoadDspInfo_007
测试用例标题      : ^TSELRF命令是否触发LOAD DSP：^TSELRF命令设置的射频通路编号为GSM，需要LOAD DSP
                    g_stAtDevCmdCtrl.ucDeviceRatMode为AT_RAT_MODE_WCDMA
                    g_stAtDevCmdCtrl.bDspLoadFlag为VOS_FALSE
预期结果          : 需要LOAD DSP
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_007)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_WCDMA_PRI;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_FALSE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_TRUE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_WCDMA, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_WCDMA, stTseLrf.ucDeviceRatMode);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_GetTseLrfLoadDspInfo_008
测试用例标题      : ^TSELRF命令是否触发LOAD DSP：^TSELRF命令设置的射频通路编号不存在，无需加载
                    该分支为异常分支，仅用于代码完整性，流程不会走到。
预期结果          : 不需要LOAD DSP
                    打印告警信息
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_008)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;
    const char                          cWarning[] = "AT_GetTseLrfLoadDspInfo: enPath only support GSM or WCDMA primary.";

    enPath = AT_TSELRF_PATH_BUTT;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_FALSE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_FALSE, bLoadDsp);

    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_AT_QryCmdlenPara
功能描述 : Test_AT_QryCmdlenPara UT工程类
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryCmdlenPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstCmdLenCmdInfo;
    }
    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryCmdlenPara_001
测试用例标题      : 查询单板最大可以直接接收AT命令字符个数，以及单板通过AT一次最大
                    可以响应的字符个数，该字符个数均不包含AT这两个字符。
预期结果          : 输出字符串^CMDLEN:1598,5000
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryCmdlenPara, Test_AT_QryCmdlenPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    char                                  *paucExpectedStr = "^CMDLEN:1598,5000";
    VOS_UINT32                             usExpectedStrLen;

    ucIndex = 0;

    ulRet = AT_QryCmdlenPara(ucIndex);

    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);

    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_SetTseLrfPara
功能描述 : Test_AT_SetTseLrfPara UT工程类
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SetTseLrfPara: public ::testing::Test
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
测试用例编号      : Test_AT_SetTseLrfPara_001
测试用例标题      : ^TSELRF的设置操作: 无参数的设置操作
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

#if (FEATURE_ON != FEATURE_LTE)
/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_002
测试用例标题      : ^TSELRF的设置操作: 第一个参数不存在
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_002)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 0;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_003
测试用例标题      : ^TSELRF的设置操作: 不支持WIFI情况下收到设置WIFI通路请求
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_003)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WIFI;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .with(eq((BSP_MODULE_TYPE_E)BSP_MODULE_TYPE_WIFI))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    MOCKER(wifi_get_status)
        .stubs()
        .will(returnValue((int)VOS_FALSE));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_004
测试用例标题      : ^TSELRF的设置操作: 参数个数不为1
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_004)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_PRI;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_005
测试用例标题      : ^TSELRF的设置操作: 支持WIFI情况下收到设置WIFI通路请求
预期结果          : 函数返回AT_OK
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_005)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WIFI;

    MOCKER(wifi_get_status)
        .expects(exactly(1))
        .will(returnValue((int)VOS_TRUE));

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .with(eq((BSP_MODULE_TYPE_E)BSP_MODULE_TYPE_WIFI))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    MOCKER(wifi_get_status)
        .expects(exactly(1))
        .will(returnValue((int)VOS_TRUE));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_EQ(AT_RAT_MODE_WIFI, g_stAtDevCmdCtrl.ucDeviceRatMode);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_006
测试用例标题      : ^TSELRF的设置操作: 非WIFI版本收到设置WIFI通路请求
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_006)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WIFI;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .with(eq((BSP_MODULE_TYPE_E)BSP_MODULE_TYPE_WIFI))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_UNSUPPORT));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_007
测试用例标题      : ^TSELRF的设置操作: 信令模式下收到设置非WIFI通路请求
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_007)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_DIV;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_NORMAL;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_008
测试用例标题      : ^TSELRF的设置操作: 接收机未打开情况下收到设置分集请求
预期结果          : 函数返回AT_OK同时记录打开分集标志到本地
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_008)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_UINT8                              ucPriOrDiv;

    ucIndex = 0;
    ucPriOrDiv = AT_RX_DIV_ON;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_DIV;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = 0;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_EQ(ucPriOrDiv, g_stAtDevCmdCtrl.ucPriOrDiv);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_009
测试用例标题      : ^TSELRF的设置操作: 发送设置分集请求失败
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_009)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_DIV;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    MOCKER(At_SendRfCfgAntSelToHPA)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_010
测试用例标题      : ^TSELRF的设置操作: 发送设置分集请求成功
预期结果          : 函数返回AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_010)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_DIV;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    MOCKER(At_SendRfCfgAntSelToHPA)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(ucIndex, g_stAtDevCmdCtrl.ucIndex);
    ASSERT_EQ(AT_CMD_TSELRF_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_011
测试用例标题      : ^TSELRF的设置操作: 接收到设置WCDMA主集通道配置且要求LOAD DSP，但LOAD 指令发送失败
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_011)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_BOOL                               bLoadDsp;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_PRI;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    bLoadDsp = VOS_TRUE;

    MOCKER(AT_GetTseLrfLoadDspInfo)
        .expects(exactly(1))
        .with(eq((AT_TSELRF_PATH_ENUM_UINT32)AT_TSELRF_PATH_WCDMA_PRI), outBoundP((VOS_BOOL *)&bLoadDsp, (VOS_UINT32)sizeof(bLoadDsp)), any());

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_CMD_TSELRF_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_012
测试用例标题      : ^TSELRF的设置操作: 接收到设置WCDMA主集通道配置且要求LOAD DSP
预期结果          : 函数返回AT_WAIT_ASYNC_RETURN
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_012)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_BOOL                               bLoadDsp;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_PRI;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    bLoadDsp = VOS_TRUE;

    MOCKER(AT_GetTseLrfLoadDspInfo)
        .stubs()
        .with(any(), outBoundP((VOS_BOOL *)&bLoadDsp, (VOS_UINT32)sizeof(bLoadDsp)), any());

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_CMD_TSELRF_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTseLrfPara_013
测试用例标题      : ^TSELRF的设置操作: 接收到设置WCDMA主集通道配置且不要求LOAD DSP
预期结果          : 函数返回AT_OK
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_013)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_BOOL                               bLoadDsp;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_PRI;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    bLoadDsp = VOS_FALSE;

    MOCKER(AT_GetTseLrfLoadDspInfo)
        .stubs()
        .with(any(), outBoundP((VOS_BOOL *)&bLoadDsp, (VOS_UINT32)sizeof(bLoadDsp)), any());
    
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

#if(FEATURE_LTE != FEATURE_ON)
/*****************************************************************************
类名     : Test_AT_QryTseLrfPara
功能描述 : Test_AT_QryTseLrfPara UT工程类
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_QryTseLrfPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstTseLrfCmdInfo;
    }
    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_AT_QryTseLrfPara_001
测试用例标题      : 查询命令用来返回单板支持的所有情况，每种情况分行显示
预期结果          : 输出字符串^TSELRF:4\r\n^TSELRF:1\r\n^TSELRF:2\r\n^TSELRF:3\r\n^TSELRF:7
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_QryTseLrfPara, Test_AT_QryTseLrfPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    char                                  *paucExpectedStr = "^TSELRF:4\r\n^TSELRF:1\r\n^TSELRF:2\r\n^TSELRF:3\r\n^TSELRF:7";
    VOS_UINT32                             usExpectedStrLen;

    ucIndex = 0;
    ulRet = AT_QryTseLrfPara(ucIndex);

    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);

    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

#endif
#if 0
/*****************************************************************************
类名     : Test_AT_SetCmdlenPara
功能描述 : Test_AT_SetCmdlenPara UT工程类
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SetCmdlenPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstCmdLenCmdInfo;
    }
    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_AT_SetCmdlenPara_001
测试用例标题      : 告知单板PC一次期望发送的字符个数和PC期望单板一次发送的字符个数
                    该命令用于支撑SIMLOCK数据的分段发送，BALONG无此需求，仅返回OK保证工
                    位归一化流程正常执行
预期结果          : 函数返回OK
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 3;
    gastAtParaList[0].ulParaValue = 1000;
    gastAtParaList[1].usParaLen = 3;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;

    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetCmdlenPara_002
测试用例标题      : 告知单板PC一次期望发送的字符个数和PC期望单板一次发送的字符个数
                    该命令用于支撑SIMLOCK数据的分段发送，BALONG无此需求，仅返回OK保证工
                    位归一化流程正常执行，无参数输入
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_002)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    gastAtParaList[0].usParaLen = 3;
    gastAtParaList[0].ulParaValue = 1000;
    gastAtParaList[1].usParaLen = 3;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;

    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetCmdlenPara_003
测试用例标题      : 告知单板PC一次期望发送的字符个数和PC期望单板一次发送的字符个数
                    该命令用于支撑SIMLOCK数据的分段发送，BALONG无此需求，仅返回OK保证工
                    位归一化流程正常执行参数一为空
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_003)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 1000;
    gastAtParaList[1].usParaLen = 3;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;
    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetCmdlenPara_004
测试用例标题      : 告知单板PC一次期望发送的字符个数和PC期望单板一次发送的字符个数
                    该命令用于支撑SIMLOCK数据的分段发送，BALONG无此需求，仅返回OK保证工
                    位归一化流程正常执行参数二为空
预期结果          : 函数返回AT_CME_INCORRECT_PARAMETERS
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_004)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 3;
    gastAtParaList[0].ulParaValue = 1000;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;
    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetCmdlenPara_005
测试用例标题      : 告知单板PC一次期望发送的字符个数和PC期望单板一次发送的字符个数
                    该命令用于支撑SIMLOCK数据的分段发送，BALONG无此需求，仅返回OK保证工
                    位归一化流程正常执行参数二大于1598
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_005)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 3;
    gastAtParaList[0].ulParaValue = 1600;
    gastAtParaList[1].usParaLen = 3;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;
    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_SetTmodeAutoPowerOff
功能描述 : Test_AT_SetTmodeAutoPowerOff UT工程类
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_SetTmodeAutoPowerOff: public ::testing::Test
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

#if (FEATURE_ON == FEATURE_E5)
/*******************************************************************
测试用例编号      : Test_AT_SetTmodeAutoPowerOff_001
测试用例标题      : 自动关机的装备命令消息发送操作执行成功
                    产线要求先通知用户AT命令已执行，满足产线的时效需求
                    用户通过检测端口是否消失来确认任务是否正确执行
预期结果          : 函数返回OK
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTmodeAutoPowerOff, Test_AT_SetTmodeAutoPowerOff_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    TAF_PH_OP_MODE_STRU    stPhModeSet;

    ucIndex = 0;

    stPhModeSet.CmdType = TAF_PH_CMD_SET;
    stPhModeSet.PhMode  = TAF_PH_MODE_POWEROFF;
    MOCKER(Taf_DefPhMode)
        .stubs()
        .with(any(), any(), mirror(&stPhModeSet, sizeof(stPhModeSet)))
        .will(returnValue(AT_SUCCESS));

    ulRet = AT_SetTmodeAutoPowerOff(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_SetTmodeAutoPowerOff_002
测试用例标题      : 自动关机的装备命令消息发送操作执行失败
                    产线要求先通知用户AT命令已执行，满足产线的时效需求
                    用户通过检测端口是否消失来确认任务是否正确执行
预期结果          : 函数返回AT_ERROR
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTmodeAutoPowerOff, Test_AT_SetTmodeAutoPowerOff_002)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    TAF_PH_OP_MODE_STRU    stPhModeSet;

    ucIndex = 0;

    stPhModeSet.CmdType = TAF_PH_CMD_SET;
    stPhModeSet.PhMode  = TAF_PH_MODE_POWEROFF;
    MOCKER(Taf_DefPhMode)
        .stubs()
        .with(any(), any(), mirror(&stPhModeSet, sizeof(stPhModeSet)))
        .will(returnValue(AT_FAILURE));

    ulRet = AT_SetTmodeAutoPowerOff(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
#else

/*******************************************************************
测试用例编号      : Test_AT_SetTmodeAutoPowerOff_001
测试用例标题      : 自动关机的装备命令消息发送操作执行成功
                    产线要求先通知用户AT命令已执行，满足产线的时效需求
                    用户通过检测端口是否消失来确认任务是否正确执行
预期结果          : 函数返回OK
修改历史     :
1.日   期  : 2012-1-17
作   者  :   f62575
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_SetTmodeAutoPowerOff, Test_AT_SetTmodeAutoPowerOff_001)
{
    /*变量定义*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;
    ulRet = AT_SetTmodeAutoPowerOff(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

#endif

#endif

/*****************************************************************************
类名     : Test_AT_TestHsicCmdPara
功能描述 : AT_TestHsicCmdPara UT工程类
修改历史 :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestHsicCmdPara: public ::testing::Test
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
测试用例编号      : Test_AT_TestHsicCmdPara_001
测试用例标题      : 测试命令从HSIC通道下发
预期结果          : 返回AT_OK
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestHsicCmdPara, Test_AT_TestHsicCmdPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_APP;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq(ucIndex))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_TestHsicCmdPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestHsicCmdPara_002
测试用例标题      : 获取的用户索引非法
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2012-04-12
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestHsicCmdPara, Test_AT_TestHsicCmdPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex = AT_CLIENT_ID_PCUI;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq(ucIndex))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_TestHsicCmdPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_AT_TestSimlockUnlockPara
功能描述 : AT_TestSimlockUnlockPara UT工程类
修改历史 :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_AT_TestSimlockUnlockPara: public ::testing::Test
{
public:
    AT_PAR_CMD_ELEMENT_STRU                 stCmdInfo;
    VOS_UINT8                               ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        stCmdInfo.ulCmdIndex        = AT_CMD_SIMLOCKUNLOCK;
        stCmdInfo.pfnSetProc        = AT_SetSimlockUnlockPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestSimlockUnlockPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^SIMLOCKUNLOCK";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(\"NET\",\"NETSUB\",\"SP\"),(pwd)";
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_AT_TestSimlockUnlockPara_001
测试用例标题      : 命令下发通道非HSIC通道
预期结果          : 返回AT_ERROR
修改历史          :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestSimlockUnlockPara, Test_AT_TestSimlockUnlockPara_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    //参数初始化
    ucIndex         = AT_CLIENT_TAB_PCUI_INDEX;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .with(eq(ucIndex))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulRet = AT_TestSimlockUnlockPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_TestSimlockUnlockPara_002
测试用例标题      : 命令下发通道为HSIC1通道
预期结果          : 返回AT_OK, 打印结果
修改历史          :
1.日   期  : 2012-09-24
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_AT_TestSimlockUnlockPara, Test_AT_TestSimlockUnlockPara_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;

    //参数初始化
    pcExpect        = "^SIMLOCKUNLOCK: (\"NET\",\"NETSUB\",\"SP\")";

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .with(eq(ucIndex))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 调用被测函数
    ulRet = AT_TestSimlockUnlockPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpect), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpect, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}



/******************************************************************************
类名     : Test_AT_QryFPllStatusPara
功能描述 : AT_QryFPllStatusPara UT工程类
修改历史 :
 1.日   期  : 2013-11-30
   作   者  : L00256032
   修改内容 : Added for PLL status query
******************************************************************************/
class Test_AT_QryFPllStatusPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        VOS_MemSet(&g_stAtDevCmdCtrl, 0, sizeof(g_stAtDevCmdCtrl));
    }
    void TearDown()
    {

    }
};
/******************************************************************************
测试用例编号: Test_AT_QryFPllStatusPara_001
测试用例标题: 当前模式不合法
预期结果    : 
修改历史    :
 1.日   期  : 2013-11-30
   作   者  : L00256032
   修改内容 : Added for PLL status query
******************************************************************************/
TEST_F(Test_AT_QryFPllStatusPara, Test_AT_QryFPllStatusPara_001)
{
    // 变量声明
    VOS_UINT8  ucIndex = 0;
    VOS_UINT32 ulResult; 


    // 参数初始化

    // 初始化全局变量
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_BUTT;

    // MOCKER操作

    // 调用被测函数
    ulResult = AT_QryFPllStatusPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_DEVICE_MODE_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryFPllStatusPara_002
测试用例标题: 申请消息失败
预期结果    : 
修改历史    :
 1.日   期  : 2013-11-30
   作   者  : L00256032
   修改内容 : Added for PLL status query
******************************************************************************/
TEST_F(Test_AT_QryFPllStatusPara, Test_AT_QryFPllStatusPara_002)
{
    // 变量声明
    VOS_UINT8  ucIndex = 0;
    VOS_UINT32 ulResult; 


    // 参数初始化

    // 初始化全局变量
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;

    // MOCKER操作
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    // 调用被测函数
    ulResult = AT_QryFPllStatusPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryFPllStatusPara_003
测试用例标题: 发送消息失败
预期结果    : 
修改历史    :
 1.日   期  : 2013-11-30
   作   者  : L00256032
   修改内容 : Added for PLL status query
******************************************************************************/
TEST_F(Test_AT_QryFPllStatusPara, Test_AT_QryFPllStatusPara_003)
{
    // 变量声明
    VOS_UINT8  ucIndex = 0;
    VOS_UINT32 ulResult; 


    // 参数初始化

    // 初始化全局变量
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;

    // MOCKER操作
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulResult = AT_QryFPllStatusPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_AT_QryFPllStatusPara_004
测试用例标题: 发送消息成功
预期结果    : 
修改历史    :
 1.日   期  : 2013-11-30
   作   者  : L00256032
   修改内容 : Added for PLL status query
******************************************************************************/
TEST_F(Test_AT_QryFPllStatusPara, Test_AT_QryFPllStatusPara_004)
{
    // 变量声明
    VOS_UINT8  ucIndex = 0;
    VOS_UINT32 ulResult; 


    // 参数初始化

    // 初始化全局变量
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;

    // MOCKER操作


    // 调用被测函数
    ulResult = AT_QryFPllStatusPara(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_FPLLSTATUS_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(ucIndex, g_stAtDevCmdCtrl.ucIndex);

    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_At_RfPllStatusCnfProc
功能描述 : At_RfPllStatusCnfProc UT工程类
修改历史 :
 1.日   期  : 2013-11-30
   作   者  : L00256032
   修改内容 : Added for PLL status query
******************************************************************************/
class Test_At_RfPllStatusCnfProc: public ::testing::Test
{
public:
    AT_PAR_CMD_ELEMENT_STRU                 stCmdInfo;
    VOS_UINT8                               ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));
        
        ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;
        stCmdInfo.ulCmdIndex        = AT_CMD_FPLLSTATUS;
        stCmdInfo.pfnSetProc        = VOS_NULL_PTR;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryFPllStatusPara;
        stCmdInfo.ulTestTimeOut     = AT_QRY_PARA_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^FPLLSTATUS";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1),(0,1)";
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }
};
/******************************************************************************
测试用例编号: Test_At_RfPllStatusCnfProc_001
测试用例标题: 当前AT命令未处于等待AT_CMD_FPLLSTATUS_QRY响应的状态
预期结果    : 
修改历史    :
 1.日   期  : 2013-11-30
   作   者  : L00256032
   修改内容 : Added for PLL status query
******************************************************************************/
TEST_F(Test_At_RfPllStatusCnfProc, Test_At_RfPllStatusCnfProc_001)
{
    // 变量声明
    PHY_AT_RF_PLL_STATUS_CNF_STRU   stMsg;

    // 参数初始化

    // 初始化全局变量
    g_stAtDevCmdCtrl.ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    At_RfPllStatusCnfProc(&stMsg);

    // 执行检查
    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_At_RfPllStatusCnfProc_002
测试用例标题: 正常执行查询命令的返回
预期结果    : 
修改历史    :
 1.日   期  : 2013-11-30
   作   者  : L00256032
   修改内容 : Added for PLL status query
******************************************************************************/
TEST_F(Test_At_RfPllStatusCnfProc, Test_At_RfPllStatusCnfProc_002)
{
    // 变量声明
    PHY_AT_RF_PLL_STATUS_CNF_STRU   stMsg;
    VOS_CHAR                        *pcExpect = "^FPLLSTATUS: 0,1";


    // 参数初始化
    stMsg.usTxStatus = 0;
    stMsg.usRxStatus = 1;

    // 初始化全局变量
    g_stAtDevCmdCtrl.ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FPLLSTATUS_QRY;

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    At_RfPllStatusCnfProc(&stMsg);
    EXPECT_EQ(VOS_StrLen(pcExpect), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpect, (VOS_CHAR *)pgucAtSndCodeAddr);


    // 执行检查
    GlobalMockObject::verify();
}
