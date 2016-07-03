#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtOutputProc.h"

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


class Test_At_SendData: public ::testing::Test
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


TEST_F(Test_At_SendData,Test_At_SendData_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = AT_MAX_CLIENT_NUM;

    ulRlst = At_SendData(ucIndex, 0, VOS_NULL_PTR, 0);
    EXPECT_EQ(ulRlst, AT_FAILURE);
}


TEST_F(Test_At_SendData,Test_At_SendData_002)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].DataMode = AT_DATA_BUTT_MODE;

    ulRlst = At_SendData(ucIndex, 0, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);
}



TEST_F(Test_At_SendData,Test_At_SendData_003)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    /* 当前索引未使用 */
    gastAtClientTab[ucIndex].ucUsed = AT_CLIENT_NULL;

    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_PPP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);
}


TEST_F(Test_At_SendData,Test_At_SendData_004)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    /* 当前索正使用 */
    gastAtClientTab[ucIndex].ucUsed = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;

    /* AT_COM_USER */
    gastAtClientTab[ucIndex].UserType  = AT_USBCOM_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* 期望调用1次 */
    //MOCKER(AT_MsgBufferPut)
    //    .expects(exactly(1));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SendData,Test_At_SendData_005)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    /* AT_CTR_USER */
    gastAtClientTab[ucIndex].UserType  = AT_CTR_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    /* 期望调用1次 */
    //MOCKER(AT_CtrMsgBufferPut)
    //    .expects(exactly(1));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    GlobalMockObject::verify();
}



TEST_F(Test_At_SendData,Test_At_SendData_006)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_MODEM_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    /* 期望调用1次 */
    MOCKER(AT_SendDataToModem)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SendData,Test_At_SendData_007)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_NDIS_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);

}


TEST_F(Test_At_SendData,Test_At_SendData_008)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_BUTT_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);

}


TEST_F(Test_At_SendData,Test_At_SendData_009)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = 0;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_HSIC1_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_FAILURE);

}

TEST_F(Test_At_SendData,Test_At_SendData_010)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_APP_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, VOS_NULL_PTR, 0);

    EXPECT_EQ(ulRlst, AT_SUCCESS);

}

#if (FEATURE_ON == FEATURE_AT_HSIC)

TEST_F(Test_At_SendData,Test_At_SendData_011)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[3] = {'O', 'K', 0};

    ucIndex = 0;
    usDataLen = 2;

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_HSIC4_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    MOCKER(AT_SendDataToHsic)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror(aucData), eq(usDataLen));

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, aucData, usDataLen);

    EXPECT_EQ(ulRlst, AT_SUCCESS);
}

TEST_F(Test_At_SendData,Test_At_SendData_012)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRlst;
    VOS_UINT8                           ucNvId;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           aucData[3] = {'O', 'K', 0};

    ucMuxSupportFlg = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_MUX1_INDEX;
    ucNvId  = en_NV_Item_Mux_Support_Flg;
    usDataLen = 2;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(ucNvId), outBoundP(&ucMuxSupportFlg))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(any(), mirror(aucData), eq(usDataLen));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue(VOS_FALSE));

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_GetLength)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;

    gastAtClientTab[ucIndex].DataMode  = AT_IP_DATA_MODE;

    gastAtClientTab[ucIndex].UserType  = AT_MUX1_USER;

    /* DATA_START_STATE */
    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    gastAtClientTab[ucIndex].Mode      = AT_DATA_MODE;

    ulRlst = At_SendData(ucIndex, AT_IP_DATA_MODE, aucData, usDataLen);

    EXPECT_EQ(ulRlst, AT_SUCCESS);

    GlobalMockObject::verify();
}
#endif


class Test_AT_DisplayResultData: public ::testing::Test
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


TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_001)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    gastAtClientTab[ucIndex].UserType = AT_COM_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

    AT_DisplayResultData(ucIndex, 0);
}


TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_002)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    gastAtClientTab[ucIndex].UserType = AT_USBCOM_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* 期望调用1次 */
    MOCKER(Sock_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)0));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_003)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    gastAtClientTab[ucIndex].UserType = AT_CTR_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* 期望调用1次 */
    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_004)
{
    VOS_UINT8                           ucIndex;
    TTF_MEM_ST                stDataMem;

    stDataMem.pData = (VOS_UINT8 *)malloc(1);

    ucIndex = 0;

    gastAtClientTab[ucIndex].UserType = AT_MODEM_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* 期望调用1次 */
    MOCKER(AT_SendDataToModem)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_005)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;

    /* 期望调用1次 */
    MOCKER(AT_HSUART_SendDlData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_006)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_NDIS_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* 期望调用1次 */

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_007)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_APP1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_APP_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* 期望调用1次 */
    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)

TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_008)

{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_HSIC1_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    /* 期望调用1次 */
   // MOCKER(APP_VCOM_Send)
     //   .expects(never());

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_009)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT16                          usNvId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           aucData[3] = {'O', 'K', 0};

    ucMuxSupportFlg = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_MUX1_INDEX;
    usNvId  = en_NV_Item_Mux_Support_Flg;
    usLen   = 2;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(usNvId), outBoundP(&ucMuxSupportFlg, sizeof(ucMuxSupportFlg)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(any(), mirror(aucData), eq(usLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_GetLength)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));


    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    gastAtClientTab[ucIndex].UserType = AT_MUX1_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    gstAtSendDataBuffer[0] = 'O';
    gstAtSendDataBuffer[1] = 'K';

    AT_DisplayResultData(ucIndex, 2);

    GlobalMockObject::verify();
}
#endif


TEST_F(Test_AT_DisplayResultData,Test_AT_DisplayResultData_010)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    gastAtClientTab[ucIndex].UserType = AT_UART_USER;

    gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;

    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;

    g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;

    /* 期望调用1次 */
    MOCKER(AT_UART_SendDlData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplayResultData(ucIndex, 0);

    GlobalMockObject::verify();
}


class Test_AT_DisplaySelResultData: public ::testing::Test
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

TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_01)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_USBCOM_USER;

    gucAtPortSel = 0;

    /* 期望调用一次 */
    MOCKER(Sock_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_02)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_CTR_USER;

    gucAtPortSel = 0;

    /* 期望调用一次 */
    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_INT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_03)
{
    TTF_MEM_ST                          stDataMem;

    stDataMem.pData = (VOS_UINT8 *)malloc(1);

    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_MODEM_USER;

    gucAtPortSel = 1;

    /* 期望调用一次 */
    MOCKER(AT_SendDataToModem)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_04)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_APP_USER;

    /* 期望调用一次 */
    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_NDIS)


TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_05)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_NDIS_USER;

    /* 期望调用一次 */
    MOCKER(DMS_WriteData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}
#endif

#if((FEATURE_ON == FEATURE_GNA)||(FEATURE_ON == FEATURE_RNIC))


TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_06)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_APP_USER;

    /* 期望调用一次 */
    MOCKER(APP_VCOM_Send)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    AT_DisplaySelResultData(0, 0);

    GlobalMockObject::verify();
}
#endif


TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_07)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_HSIC3_USER;


    AT_DisplaySelResultData(1, 0);

    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)

TEST_F(Test_AT_DisplaySelResultData, Test_AT_DisplaySelResultData_08)
{
    gastAtClientTab[0].Mode     = AT_CMD_MODE;
    gastAtClientTab[0].UserType = AT_HSIC4_USER;

    /* 期望调用1次 */
    MOCKER(AT_SendDataToHsic)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    AT_DisplaySelResultData(1, 0);

    GlobalMockObject::verify();
}

TEST_F(Test_AT_DisplaySelResultData,Test_AT_DisplaySelResultData_09)
{
    VOS_UINT32                          ulNvId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           aucData[3] = {'O', 'K', 0};

    ucMuxSupportFlg = VOS_TRUE;

    ucIndex = AT_CLIENT_TAB_MUX1_INDEX;
    ulNvId  = en_NV_Item_Mux_Support_Flg;
    usLen   = 2;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(ulNvId), outBoundP(&ucMuxSupportFlg))
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(MUX_DlciDlDataSend)
        .stubs()
        .with(any(), mirror(aucData), eq(usLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_CheckHsicUser)
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_GetLength)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /* AT PID INIT*/
    At_PidInit(VOS_IP_INITIAL);

    gastAtClientTab[ucIndex].Mode     = AT_CMD_MODE;
    gastAtClientTab[ucIndex].UserType = AT_MUX1_USER;

    gstAtSendDataBuffer[0] = 'O';
    gstAtSendDataBuffer[1] = 'K';

    AT_DisplaySelResultData(2, ucIndex);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_DisplaySelResultData, Test_AT_DisplaySelResultData_010)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    // 参数初始化

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode = AT_CMD_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    // MOCKER操作
    MOCKER(AT_HSUART_SendDlData)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // 调用被测函数
    AT_DisplaySelResultData(4, ucIndex);

    // 执行检查
    GlobalMockObject::verify();
}
#endif


class Test_At_FormatResultData: public ::testing::Test
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
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_FormatResultData, Test_At_FormatResultData_001)
{
    // 变量声明
    VOS_CHAR                           *pcExpectStr = (VOS_CHAR *)"\r\nNO CARRIER\r\n";
    VOS_UINT32                          ulReturnCode;
    VOS_UINT8                           unIndex;

    // 参数初始化
    ulReturnCode = AT_NO_CARRIER;
    unIndex      = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    gstAtCombineSendData[unIndex].usBufLen = 0;
    gstAtSendData.usBufLen  = 0;
    gucAtVType              = AT_V_ENTIRE_TYPE;
    gucAtXType              = 1;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(unIndex), any(), eq((VOS_UINT16)VOS_StrLen(pcExpectStr)));

    MOCKER(AT_ProcFormatResultMsc)
        .expects(exactly(1))
        .with(eq(unIndex), eq(ulReturnCode));

    // 调用被测函数
    At_FormatResultData(unIndex, ulReturnCode);

    // 执行检查

    GlobalMockObject::verify();
}

#if 1

TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_002)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_RRETURN_CODE_BUTT + 1;

    //相关全局变量初始化

    // MOCKER操作
    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_003)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CMD_NOT_SUPPORT;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;

    // MOCKER操作
    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_004)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_TOO_MANY_PARA;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;

    // MOCKER操作
    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_005)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_WAIT_SMS_INPUT;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_006)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_007)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ERROR_CODE;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_008)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ERROR_CONTENT;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_010)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CONNECT;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtVType = AT_V_ENTIRE_TYPE;
    gastAtClientTab[1].Mode = AT_DATA_MODE;
    gastAtClientTab[1].DataMode = AT_PPP_DATA_MODE;
    gucAtXType = 1;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_ProcFormatResultMsc)
        .expects(exactly(1));

    MOCKER(AT_EventReport)
        .stubs()
        .with(eq(WUEPS_PID_AT), eq(NAS_OM_EVENT_DCE_UP_DCD),eq(VOS_NULL_PTR), eq(NAS_OM_EVENT_NO_PARA));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_011)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_NO_CARRIER;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtVType = AT_V_ENTIRE_TYPE;
    gastAtClientTab[1].Mode = AT_DATA_MODE;
    gastAtClientTab[1].DataMode = AT_PPP_DATA_MODE;
    gastAtClientTab[1].UserType = AT_MODEM_USER;
    gucAtXType = 1;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_ProcFormatResultMsc)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_012)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CONNECT;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtVType = AT_V_ENTIRE_TYPE;
    gastAtClientTab[1].Mode = AT_DATA_MODE;
    gastAtClientTab[1].DataMode = AT_CSD_DATA_MODE;
    gastAtClientTab[1].UserType = AT_MODEM_USER;
    gucAtXType = 1;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(AT_ProcFormatResultMsc)
        .expects(exactly(1));

    MOCKER(AT_EventReport)
        .stubs()
        .with(eq(WUEPS_PID_AT), eq(NAS_OM_EVENT_DCE_UP_DCD),eq(VOS_NULL_PTR), eq(NAS_OM_EVENT_NO_PARA));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_013)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CME_SIM_BUSY;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_ABORT));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));
    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_014)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CME_SIM_BUSY;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ERROR_CODE;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_ABORT));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_015)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CME_SIM_BUSY;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ERROR_CONTENT;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_ABORT));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_016)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    MOCKER(AT_ParseCmdOver)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_017)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_018)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_OK;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_FINISH));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_019)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_CME_SIM_FAILURE;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_ABORT));

    MOCKER(At_SendResultData)
        .expects(exactly(1));

    MOCKER(At_ResetCombinParseInfo)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_020)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_OK;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_BREVITE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_021)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_OK;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_022)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_OK;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;
    gstAtSendData.usBufLen = 10;
    gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    gucAtVType = AT_V_ENTIRE_TYPE;

    // MOCKER操作
    MOCKER(At_JudgeCombineCmdSubSequentProcess)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_COM_CMD_SUB_PROC_CONTINUE));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_023)
{
    //参数定义
    TAF_UINT8   ucIndex;
    TAF_UINT32  ReturnCode;

    //参数初始化
    ucIndex = 1;
    ReturnCode = AT_WAIT_XML_INPUT;

    //相关全局变量初始化
    gstAtCombineSendData[1].usBufLen = 10;

    // MOCKER操作
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //执行检查
    At_FormatResultData(ucIndex, ReturnCode);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_024)
{
    VOS_UINT8                           aucDataAt[50];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;
    VOS_UINT8                           ucAtCmdNotSupportStr2[]   = "COMMAND NOT SUPPORT";

    usLength  = 0;
    ulTmp     = 0;


    /* 初始化全局变量 */
    MOCKER(V_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    AT_STOP_TIMER_CMD_READY(0);
    At_ResetCombinParseInfo(0);

    PS_MEM_CPY((VOS_CHAR*)gaucAtCmdNotSupportStr,
               (VOS_CHAR*)ucAtCmdNotSupportStr2,
               sizeof(ucAtCmdNotSupportStr2));

    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    pgucAtSndCodeAddr = &gstAtSendData.aucBuffer[3];

    /* 构造输出结果 */
    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)ucAtCmdNotSupportStr2);
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)ucAtCmdNotSupportStr2, ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    PS_MEM_SET(&gstAtSendData,    0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

    PS_MEM_SET(&g_stParseContext, 0x00, sizeof(g_stParseContext));

    At_FormatResultData(0, AT_CMD_NOT_SUPPORT);

    EXPECT_STREQ((char*)pgucAtSndCodeAddr, (char*)aucDataAt);
}


TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_025)
{
    VOS_UINT8                           aucDataAt[50];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    usLength  = 0;
    ulTmp     = 0;


    /* 初始化全局变量 */
    AT_STOP_TIMER_CMD_READY(0);
    At_ResetCombinParseInfo(0);
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    pgucAtSndCodeAddr = &gstAtSendData.aucBuffer[3];


    /* 构造输出结果 */
    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)gaucAtTooManyParaStr);
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)gaucAtTooManyParaStr, ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    PS_MEM_SET(&gstAtSendData,    0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

    PS_MEM_SET(&g_stParseContext, 0x00, sizeof(g_stParseContext));

    At_FormatResultData(0, AT_TOO_MANY_PARA);

    EXPECT_STREQ((char*)pgucAtSndCodeAddr, (char*)aucDataAt);
}



TEST_F(Test_At_FormatResultData,Test_At_FormatResultData_026)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    TAF_AGENT_SYS_MODE_STRU             stSysMode;

    usLength  = 0;
    ucIndex   = 0;

    /* 初始化全局变量 */
    AT_STOP_TIMER_CMD_READY(0);
    At_ResetCombinParseInfo(0);
    PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));
    PS_MEM_SET(&g_stParseContext, 0x00, sizeof(g_stParseContext));
    gucAtVType        = AT_V_ENTIRE_TYPE;
    gucAtXType        = 1;
    g_stParseContext[ucIndex].stCombineCmdInfo.usTotalNum = 0;
    gastAtClientTab[ucIndex].Mode                         = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode                     = AT_PPP_DATA_MODE;
    g_stDialConnectDisplayRate.ucDpaConnectRate           = 7;

    PS_MEM_SET(&stSysMode, 0x00, sizeof(stSysMode));
    stSysMode.enRatType     = TAF_PH_INFO_GSM_RAT;
    stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_EDGE;

    /* MOCKER操作 */
    MOCKER(TAF_AGENT_GetSysMode)
        .expects(exactly(1))
        /*.with(eq((VOS_UINT16)ucIndex), outBoundP((void *)&stSysMode, (VOS_UINT32)sizeof(stSysMode)))*/
        .will(returnValue((VOS_UINT32)VOS_OK));

    At_FormatResultData(ucIndex, AT_CONNECT);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}


class Test_At_BufferorSendResultData: public ::testing::Test
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

TEST_F(Test_At_BufferorSendResultData,Test_At_BufferorSendResultData_01)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           aucData[5000];
    VOS_UINT16                          usLength = 4001;

    //相关全局变量初始化
    gstAtCombineSendData[ucIndex].usBufLen = 1000;

    //MOCKER
    MOCKER(At_SendResultData)
        .expects(exactly(1));

    //调用被测函数
    At_BufferorSendResultData(ucIndex, aucData, usLength);

    //执行检查
    EXPECT_EQ(4001, gstAtCombineSendData[ucIndex].usBufLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_BufferorSendResultData,Test_At_BufferorSendResultData_02)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           aucData[5000];
    VOS_UINT16                          usLength = 200;

    //相关全局变量初始化
    gstAtCombineSendData[ucIndex].usBufLen = 1000;

    //MOCKER
    MOCKER(At_SendResultData)
        .expects(never());

    //调用被测函数
    At_BufferorSendResultData(ucIndex, aucData, usLength);

    //执行检查
    EXPECT_EQ(1200, gstAtCombineSendData[ucIndex].usBufLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



#ifdef NAS_STUB

class Test_At_SndResult_Stub: public ::testing::Test
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

TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_01)
{
    const char          cWarning[] = "At_SndResult_Stub :pData is null ptr!";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

/*  pData = aucCmdString;
    usLen = sizeof(aucCmdString);*/

    At_SndResult_Stub(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_02)
{
    const char          cWarning[] = "At_SndResult_Stub ulLength = 0";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(Ps_SendMsg)
        .expects(never());

/*  pData = aucCmdString;
    usLen = sizeof(aucCmdString);*/

    At_SndResult_Stub(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_03)
{
    const char          cWarning[] = "At_SndResult_Stub ulLength > AT_COM_BUFF_LEN";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen = AT_COM_BUFF_LEN + 1;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(Ps_SendMsg)
        .expects(never());

/*  pData = aucCmdString;
    usLen = sizeof(aucCmdString);*/

    At_SndResult_Stub(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_04)
{
    const char          cWarning[] = "At_SndResult_Stub:ERROR:Alloc Msg";
    TAF_UINT8           ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    At_SndResult_Stub(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_05)
{
    const char          cWarning[] = "At_SndResult_Stub:ERROR:VOS_SendMsg";
    TAF_UINT8           ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    At_SndResult_Stub(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SndResult_Stub, Test_At_SndResult_Stub_06)
{
    TAF_UINT8           ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;
    VOS_UINT32  ulRet;

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    At_SndResult_Stub(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_At_SendResultData,Test_At_SendResultData_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                          *pData;
    VOS_UINT16                          usLen;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    usLen = 9;

    MOCKER(AT_SendBroadCastResultData).expects(exactly(1)).with(eq(ucIndex),any(),any());

    At_SendResultData(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

class Test_AT_SendBroadCastResultData: public ::testing::Test
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

TEST_F(Test_AT_SendBroadCastResultData,Test_AT_SendBroadCastResultData_001)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                          *pData;
    VOS_UINT16                          usLen;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
    pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    usLen = 9;

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_GetLength)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    At_PidInit(VOS_IP_INITIAL);
    pstAtClientCtx = AT_GetClientCtxAddr(AT_CLIENT_TAB_PCUI_INDEX);
    pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_FALSE;

    pstAtClientCtx = AT_GetClientCtxAddr(AT_CLIENT_TAB_CTRL_INDEX);
    pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_FALSE;

    pstAtClientCtx = AT_GetClientCtxAddr(AT_CLIENT_TAB_APP5_INDEX);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    AT_SendBroadCastResultData(ucIndex, pData, usLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_AT_SmsStartRingTe: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SmsStartRingTe, Test_AT_SmsStartRingTe_001)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;

    // 参数初始化
    pstRiStateInfo                      = AT_GetUartRiStateInfo();

    // 初始化全局变量
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->ulSmsRiOutputCount  = 0;

    // MOCKER操作

    // 调用被测函数
    AT_SmsStartRingTe(VOS_TRUE);

    // 执行检查
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SmsStartRingTe, Test_AT_SmsStartRingTe_002)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    // 初始化全局变量
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_FALSE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_BUTT;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;

    // MOCKER操作
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_SmsStartRingTe(VOS_FALSE);

    // 执行检查
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_SmsStopRingTe: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SmsStopRingTe, Test_AT_SmsStopRingTe_001)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .expects(exactly(1))
        .with(eq(ulTmrName), eq(&(pstRiStateInfo->hSmsRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_SmsStopRingTe();

    // 执行检查
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SmsStopRingTe, Test_AT_SmsStopRingTe_002)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_STOP;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .expects(never());

    // 调用被测函数
    AT_SmsStopRingTe();

    // 执行检查
    EXPECT_EQ(0, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_RcvTiSmsRiExpired: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_001)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ulTmrParam;

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_FALSE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_BUTT;;
    pstRiStateInfo->ulSmsRiOutputCount  = 0;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_STOP;;

    // MOCKER操作
    MOCKER(AT_SmsRingOff)
        .expects(never());
    MOCKER(AT_SmsStopRingTe)
        .expects(never());

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(0, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enSmsRiTmrStatus);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_002)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ulTmrParam;

    // 初始化全局变量
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOffInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_003)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = 0;

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulTmrName), eq(&(pstRiStateInfo->hSmsRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(0, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_004)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ulTmrParam;

    // 初始化全局变量
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 2;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulTmrName), eq(&(pstRiStateInfo->hSmsRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiSmsRiExpired, Test_AT_RcvTiSmsRiExpired_005)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ulTmrParam;

    // 初始化全局变量
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiCfgInfo->ulSmsRiOffInterval    = 0;
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 2;
    pstRiStateInfo->enSmsRiTmrStatus      = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulTmrName), eq(&(pstRiStateInfo->hSmsRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_GetRiStatusByCallId: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_GetRiStatusByCallId, Test_AT_GetRiStatusByCallId_001)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    AT_UART_RI_STATUS_ENUM_UINT8        enRiStatus;
    VOS_UINT8                           ucCallId;

    // 参数初始化
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    ucCallId                            = 1;

    // 初始化全局变量
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;

    // MOCKER操作

    // 调用被测函数
    enRiStatus = AT_GetRiStatusByCallId(ucCallId);

    // 执行检查
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, enRiStatus);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetRiStatusByCallId, Test_AT_GetRiStatusByCallId_002)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    AT_UART_RI_STATUS_ENUM_UINT8        enRiStatus;
    VOS_UINT8                           ucCallId;

    // 参数初始化
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    ucCallId                            = 8;

    // 初始化全局变量
    pstRiStateInfo->aenVoiceRiStatus[1] = AT_UART_RI_STATUS_RINGING;

    // MOCKER操作

    // 调用被测函数
    enRiStatus = AT_GetRiStatusByCallId(ucCallId);

    // 执行检查
    EXPECT_EQ(AT_UART_RI_STATUS_STOP, enRiStatus);

    GlobalMockObject::verify();
}


class Test_AT_VoiceStartRingTe: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_VoiceStartRingTe, Test_AT_VoiceStartRingTe_001)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    // 参数初始化
    ucCallId                            = 8;

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();

    // MOCKER操作
    MOCKER(AT_SmsStopRingTe)
        .expects(never());
    MOCKER(AT_VoiceRingOn)
        .expects(never());

    // 调用被测函数
    AT_VoiceStartRingTe(ucCallId);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStartRingTe, Test_AT_VoiceStartRingTe_002)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    // 参数初始化
    ucCallId                            = 1;

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->ulSmsRiOutputCount  = 0;

    // MOCKER操作
    MOCKER(AT_VoiceRingOn)
        .expects(never());

    // 调用被测函数
    AT_VoiceStartRingTe(ucCallId);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, pstRiStateInfo->aenVoiceRiStatus[ucCallId]);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStartRingTe, Test_AT_VoiceStartRingTe_003)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;
    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_SmsStopRingTe)
        .expects(never());
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hVoiceRiTmrHdl)),
              eq(pstRiCfgInfo->ulVoiceRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_VoiceStartRingTe(ucCallId);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStartRingTe, Test_AT_VoiceStartRingTe_004)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;
    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hVoiceRiTmrHdl)),
              eq(pstRiCfgInfo->ulVoiceRiOnInterval),
              eq(ulTmrName),
              eq(ulTmrParam),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_VoiceStartRingTe(ucCallId);

    // 执行检查
    EXPECT_EQ(1, pstRiStateInfo->ulSmsRiOutputCount);
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_VoiceStopRingTe: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_VoiceStopRingTe, Test_AT_VoiceStopRingTe_001)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucCallId                            = 8;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .expects(never());
    MOCKER(AT_SmsStartRingTe)
        .expects(never());

    // 调用被测函数
    AT_VoiceStopRingTe(ucCallId);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStopRingTe, Test_AT_VoiceStopRingTe_002)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucCallId                            = 8;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_SMS;;
    pstRiStateInfo->enSmsRiTmrStatus    = AT_TIMER_STATUS_RUNNING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .expects(never());
    MOCKER(AT_SmsStartRingTe)
        .expects(never());

    // 调用被测函数
    AT_VoiceStopRingTe(ucCallId);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStopRingTe, Test_AT_VoiceStopRingTe_003)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucCallId                            = 1;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->aenVoiceRiStatus[2] = AT_UART_RI_STATUS_RINGING;;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .expects(never());
    MOCKER(AT_SmsStartRingTe)
        .expects(never());

    // 调用被测函数
    AT_VoiceStopRingTe(ucCallId);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_VoiceStopRingTe, Test_AT_VoiceStopRingTe_004)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulVoiceTmrName;
    VOS_UINT32                          ulVoiceTmrPara;
    VOS_UINT32                          ulSmsTmrName;
    VOS_UINT32                          ulSmsTmrPara;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulVoiceTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulVoiceTmrPara, ucIndex, ucCallId);
    AT_SET_SMS_RI_TMR_NAME(ulSmsTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulSmsTmrPara, ucIndex);

    // 初始化全局变量
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;;
    pstRiStateInfo->ulSmsRiOutputCount  = 1;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulVoiceTmrName),
              eq(&(pstRiStateInfo->hVoiceRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hSmsRiTmrHdl)),
              eq(pstRiCfgInfo->ulSmsRiOnInterval),
              eq(ulSmsTmrName),
              eq(ulSmsTmrPara),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    AT_VoiceStopRingTe(ucCallId);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_SMS, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enSmsRiTmrStatus);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_RcvTiVoiceRiExpired: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_001)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ucCallId;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_FALSE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_BUTT;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_STOP;;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_STOP;
    pstRiStateInfo->ulVoiceRiCycleCount = 0;

    // MOCKER操作
    MOCKER(AT_VoiceRingOff)
        .expects(never());
    MOCKER(AT_VoiceStopRingTe)
        .expects(never());
    MOCKER(AT_VoiceRingOn)
        .expects(never());

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enVoiceRiTmrStatus);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_002)
{
    // 变量声明
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    stMsg.ulName                        = ulTmrName;
    stMsg.ulPara                        = ucCallId;

    // 初始化全局变量
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->aenVoiceRiStatus[2] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->ulVoiceRiCycleCount = 0;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_VoiceRingOff)
        .expects(never());
    MOCKER(AT_VoiceStopRingTe)
        .expects(never());
    MOCKER(AT_VoiceRingOn)
        .expects(never());

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, pstRiStateInfo->aenVoiceRiStatus[2]);
    EXPECT_EQ(0, pstRiStateInfo->ulVoiceRiCycleCount);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_003)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulVoiceTmrName;
    VOS_UINT32                          ulVoiceTmrPara;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulVoiceTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulVoiceTmrPara, ucIndex, ucCallId);

    stMsg.ulName                        = ulVoiceTmrName;
    stMsg.ulPara                        = ulVoiceTmrPara;

    // 初始化全局变量
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiCfgInfo->ucVoiceRiCycleTimes   = 10;
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->ulVoiceRiCycleCount = 0;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    // MOCKER操作
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hVoiceRiTmrHdl)),
              eq(pstRiCfgInfo->ulVoiceRiOffInterval),
              eq(ulVoiceTmrName),
              eq(ulVoiceTmrPara),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, pstRiStateInfo->aenVoiceRiStatus[ucCallId]);
    EXPECT_EQ(0, pstRiStateInfo->ulVoiceRiCycleCount);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_004)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulVoiceTmrName;
    VOS_UINT32                          ulVoiceTmrPara;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;
    AT_SET_VOICE_RI_TMR_NAME(ulVoiceTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulVoiceTmrPara, ucIndex, ucCallId);

    stMsg.ulName                        = ulVoiceTmrName;
    stMsg.ulPara                        = ulVoiceTmrPara;

    // 初始化全局变量
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiCfgInfo->ucVoiceRiCycleTimes   = 10;
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->ulVoiceRiCycleCount = 0;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER操作
    MOCKER(AT_StartRelTimer)
        .stubs()
        .with(eq(&(pstRiStateInfo->hVoiceRiTmrHdl)),
              eq(pstRiCfgInfo->ulVoiceRiOnInterval),
              eq(ulVoiceTmrName),
              eq(ulVoiceTmrPara),
              eq((VOS_UINT8)VOS_RELTIMER_NOLOOP))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_VOICE, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_RUNNING, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_UART_RI_STATUS_RINGING, pstRiStateInfo->aenVoiceRiStatus[ucCallId]);
    EXPECT_EQ(1, pstRiStateInfo->ulVoiceRiCycleCount);
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvTiVoiceRiExpired, Test_AT_RcvTiVoiceRiExpired_005)
{
    // 变量声明
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    REL_TIMER_MSG                       stMsg;
    VOS_UINT32                          ulVoiceTmrName;
    VOS_UINT32                          ulVoiceTmrPara;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;
    ucCallId                            = 1;

    AT_SET_VOICE_RI_TMR_NAME(ulVoiceTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulVoiceTmrPara, ucIndex, ucCallId);

    stMsg.ulName                        = ulVoiceTmrName;
    stMsg.ulPara                        = ulVoiceTmrPara;

    // 初始化全局变量
    pstRiCfgInfo                        = AT_GetUartRiCfgInfo();
    pstRiCfgInfo->ucVoiceRiCycleTimes   = 10;
    pstRiStateInfo                      = AT_GetUartRiStateInfo();
    pstRiStateInfo->ulRunFlg            = VOS_TRUE;
    pstRiStateInfo->enType              = AT_UART_RI_TYPE_VOICE;
    pstRiStateInfo->enVoiceRiTmrStatus  = AT_TIMER_STATUS_RUNNING;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;
    pstRiStateInfo->ulVoiceRiCycleCount = 9;

    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    // MOCKER操作
    MOCKER(AT_StopRelTimer)
        .stubs()
        .with(eq(ulVoiceTmrName),
              eq(&(pstRiStateInfo->hVoiceRiTmrHdl)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_TimeOutProc(&stMsg);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, pstRiStateInfo->ulRunFlg);
    EXPECT_EQ(AT_UART_RI_TYPE_BUTT, pstRiStateInfo->enType);
    EXPECT_EQ(AT_TIMER_STATUS_STOP, pstRiStateInfo->enVoiceRiTmrStatus);
    EXPECT_EQ(AT_UART_RI_STATUS_STOP, pstRiStateInfo->aenVoiceRiStatus[ucCallId]);
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_RI));

    GlobalMockObject::verify();
}


class Test_AT_ProcFormatResultMsc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitUartCtx();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ulRet   = AT_CONNECT;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // 执行检查
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ulRet   = AT_NO_CARRIER;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // 执行检查
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_003)
{
    // 变量声明
    AT_UART_CTX_STRU                   *pstUartCtx;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ulRet                               = AT_CONNECT;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstUartCtx                          = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDsrMode    = AT_UART_DSR_MODE_CONNECT_ON;
    pstUartCtx->stLineCtrl.enDcdMode    = AT_UART_DCD_MODE_CONNECT_ON;

    // MOCKER操作

    // 调用被测函数
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // 执行检查
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));
    EXPECT_EQ(AT_IO_LEVEL_HIGH, AT_GetIoLevel(ucIndex, IO_CTRL_DSR));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    AT_UART_CTX_STRU                   *pstUartCtx;

    // 参数初始化
    ulRet                               = AT_NO_CARRIER;
    ucIndex                             = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量
    pstUartCtx                          = AT_GetUartCtxAddr();
    pstUartCtx->stLineCtrl.enDsrMode    = AT_UART_DSR_MODE_CONNECT_ON;
    pstUartCtx->stLineCtrl.enDcdMode    = AT_UART_DCD_MODE_CONNECT_ON;

    // MOCKER操作

    // 调用被测函数
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // 执行检查
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DSR));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ProcFormatResultMsc, Test_AT_ProcFormatResultMsc_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // 参数初始化
    ulRet   = AT_NO_CARRIER;
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    AT_ProcFormatResultMsc(ucIndex, ulRet);

    // 执行检查
    EXPECT_EQ(AT_IO_LEVEL_LOW, AT_GetIoLevel(ucIndex, IO_CTRL_DCD));

    GlobalMockObject::verify();
}

