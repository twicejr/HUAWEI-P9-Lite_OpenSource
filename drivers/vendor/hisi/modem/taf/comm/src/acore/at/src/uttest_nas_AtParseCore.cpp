#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtParseCore.h"


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


class Test_AT_RegisterCmdTable: public ::testing::Test
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


TEST_F(Test_AT_RegisterCmdTable, Test_AT_RegisterCmdTable_001)
{
    VOS_UINT32                   ulRet = 0;
    AT_PAR_CMD_ELEMENT_STRU stCmdTblEntry = {0};
    VOS_UINT16                   usCmdNum      = 1;
    g_stCmdTblList.next = &g_stCmdTblList;
    g_stCmdTblList.prev = &g_stCmdTblList;

    ulRet = 1;
    ulRet = AT_RegisterCmdTable(&stCmdTblEntry,usCmdNum);

    EXPECT_EQ(ulRet, ERR_MSP_SUCCESS);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_RegisterCmdTable, Test_AT_RegisterCmdTable_002)
{
    VOS_UINT32                   ulRet = 0;
    AT_PAR_CMD_ELEMENT_STRU stCmdTblEntry = {0};
    VOS_UINT16                   usCmdNum      = 1;
    g_stCmdTblList.next = &g_stCmdTblList;
    g_stCmdTblList.prev = &g_stCmdTblList;

    MOCKER(At_HeapAllocD)
        .expects(exactly(1))
        .will(returnValue((void *)NULL));

    ulRet = 0;
    ulRet = AT_RegisterCmdTable(&stCmdTblEntry,usCmdNum);

    EXPECT_EQ(ulRet, ERR_MSP_MALLOC_FAILUE);

    GlobalMockObject::verify();
}


class Test_AT_ClacCmdProc: public ::testing::Test
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


TEST_F(Test_AT_ClacCmdProc, Test_AT_ClacCmdProc_001)
{
    //打印函数 无法测试

    g_stCmdTblList.next=&g_stCmdTblList;
    g_stCmdTblList.prev=&g_stCmdTblList;
    AT_ClacCmdProc();
}


class Test_BlockCmdCheck: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        PS_MEM_SET(&g_stParseContext,0x00,sizeof(g_stParseContext));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_BlockCmdCheck, Test_BlockCmdCheck_001)
{
    VOS_UINT8 ucBlockid;
    VOS_UINT8 stBlockCmd[5] = {0,};

    g_stParseContext[0].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
    g_stParseContext[0].pBlockCmd      = stBlockCmd;
    g_stParseContext[0].usBlockCmdLen  = sizeof(stBlockCmd);

    ucBlockid = AT_BlockCmdCheck();

    EXPECT_EQ(ucBlockid,0);

    //需要重置全局变量么，怎么重置
    GlobalMockObject::verify();
}


TEST_F(Test_BlockCmdCheck, Test_BlockCmdCheck_002)
{
    VOS_UINT8 ucBlockid;
    VOS_UINT8 i;

    for(i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        g_stParseContext[i].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
        g_stParseContext[i].pBlockCmd      = NULL;
        g_stParseContext[i].usBlockCmdLen  = 0;
    }

    ucBlockid = AT_BlockCmdCheck();

    EXPECT_EQ(ucBlockid,AT_MAX_CLIENT_NUM);

    GlobalMockObject::verify();
}


class Test_ClearBlockCmdInfo: public ::testing::Test
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


TEST_F(Test_ClearBlockCmdInfo, Test_ClearBlockCmdInfo_001)
{
    VOS_UINT8 ucIndex = 0;

    g_stParseContext[0].pBlockCmd     = (VOS_UINT8*)AT_MALLOC(10);
    g_stParseContext[0].usBlockCmdLen = 10;

    AT_ClearBlockCmdInfo(ucIndex);

    EXPECT_EQ(g_stParseContext[0].usBlockCmdLen,0);

    GlobalMockObject::verify();
}


class Test_CheckProcBlockCmd: public ::testing::Test
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


TEST_F(Test_CheckProcBlockCmd, Test_CheckProcBlockCmd_001)
{
    g_stParseContext[0].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
    g_stParseContext[0].pBlockCmd      = (VOS_UINT8*)AT_MALLOC(10);
    g_stParseContext[0].usBlockCmdLen  = 10;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.next = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.prev = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;

    AT_CheckProcBlockCmd();

    EXPECT_EQ(g_stParseContext[0].usBlockCmdLen,10);

    GlobalMockObject::verify();

}


class Test_AT_ParseCmdOver: public ::testing::Test
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


TEST_F(Test_AT_ParseCmdOver, Test_AT_ParseCmdOver_001)
{
    AT_ParseCmdOver(0);

}


class Test_AT_BlockCmdTimeOutProc: public ::testing::Test
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


TEST_F(Test_AT_BlockCmdTimeOutProc, Test_AT_BlockCmdTimeOutProc_001)
{
    VOS_UINT8 ucIndex = 0;
    g_stParseContext[0].pBlockCmd      = (VOS_UINT8*)AT_MALLOC(10);
    g_stParseContext[0].usBlockCmdLen  = 10;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.next = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.prev = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;

    AT_BlockCmdTimeOutProc(ucIndex);

//    EXPECT_STREQ(g_stParseContext[0].pBlockCmd,NULL);
    EXPECT_EQ(g_stParseContext[0].usBlockCmdLen,0);

    GlobalMockObject::verify();
}


class Test_PendClientProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        
        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_PendClientProc, Test_PendClientProc_001)
{
    VOS_UINT8 ucIndex  = 0;
    VOS_UINT8 pData[4] = {'S','T','O','P'};
    VOS_UINT16 usLen   = 4;

    g_stParseContext[0].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    AT_PendClientProc(ucIndex, pData, usLen);

    EXPECT_EQ(g_stParseContext[0].ucClientStatus,AT_FW_CLIENT_STATUS_READY);

    pData[0] = 'A';
    pData[1] = 'T';
    pData[2] = 'H';

    g_stParseContext[0].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    gastAtClientTab[0].CmdCurrentOpt   = AT_CMD_A_SET;

    AT_PendClientProc(ucIndex, pData, usLen);

    EXPECT_EQ(g_stParseContext[0].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[0].CmdCurrentOpt,AT_CMD_CURRENT_OPT_BUTT);

    GlobalMockObject::verify();
}


class Test_HoldBlockCmd: public ::testing::Test
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

    }
    void TearDown()
    {

    }
};


TEST_F(Test_HoldBlockCmd, Test_HoldBlockCmd_001)
{
    VOS_UINT8 ucIndex  = 0;
    VOS_UINT8 pData[5] = {0,};
    VOS_UINT16 usLen   = 5;
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    pstClientContext = &(g_stParseContext[ucIndex]);

    AT_HoldBlockCmd(ucIndex, pData, usLen);

    EXPECT_EQ(g_stParseContext[0].usBlockCmdLen,5);

    if(NULL != pstClientContext->pBlockCmd)
    {
        AT_FREE(pstClientContext->pBlockCmd);
    }

    GlobalMockObject::verify();
}


class Test_ParseCmdIsComb: public ::testing::Test
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


TEST_F(Test_ParseCmdIsComb, Test_ParseCmdIsComb_001)
{
    VOS_UINT8 i;
    VOS_UINT32 ulRet   = ERR_MSP_FAILURE;
    VOS_UINT8 pData[2] = {'A','T'};
    VOS_UINT16 usLen   = 2;

    //无客户端处理组合命令
    for(i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        g_stParseContext[i].stCombineCmdInfo.usProcNum  = 0;
        g_stParseContext[i].stCombineCmdInfo.usTotalNum = 0;
    }

    ulRet = AT_ParseCmdIsComb(0, pData, usLen);

    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    GlobalMockObject::verify();
}


TEST_F(Test_ParseCmdIsComb, Test_ParseCmdIsComb_002)
{
    //VOS_UINT8 i;
    VOS_UINT32 ulRet   = ERR_MSP_FAILURE;
    VOS_UINT8 pData[2] = {'A','T'};
    VOS_UINT16 usLen   = 2;

    g_stParseContext[0].stCombineCmdInfo.usProcNum  = 0;
    g_stParseContext[0].stCombineCmdInfo.usTotalNum = 2;

    g_stParseContext[1].pBlockCmd     = NULL;
    g_stParseContext[1].usBlockCmdLen = 0;

    ulRet = AT_ParseCmdIsComb(0, pData, usLen);

    EXPECT_EQ(ulRet,ERR_MSP_FAILURE);
    EXPECT_EQ(g_stParseContext[1].usBlockCmdLen,0);

    GlobalMockObject::verify();
}


class Test_atParseCmdIsPend: public ::testing::Test
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

    }
    void TearDown()
    {

    }
};


TEST_F(Test_atParseCmdIsPend, Test_atParseCmdIsPend_001)
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT8 ucIndex = 0;
    VOS_UINT8 pData[]="1234";
    VOS_UINT16 usLen=5;

    g_stParseContext[0].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    ulRet = AT_ParseCmdIsPend(ucIndex, pData, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_FAILURE);

    g_stParseContext[1].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    gastAtClientTab[0].UserType        = AT_HSIC1_USER;
    gastAtClientTab[1].UserType        = AT_HSIC2_USER;

    ulRet = AT_ParseCmdIsPend(1, pData, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_FAILURE);

    g_stParseContext[1].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    gastAtClientTab[0].UserType        = AT_APP_USER;
    gastAtClientTab[1].UserType        = AT_HSIC2_USER;

    ulRet = AT_ParseCmdIsPend(1, pData, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_FAILURE);

    g_stParseContext[0].ucClientStatus = 0;
    g_stParseContext[1].ucClientStatus = 0;

    ulRet = AT_ParseCmdIsPend(0, pData, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    GlobalMockObject::verify();
}


TEST_F(Test_atParseCmdIsPend, Test_atParseCmdIsPend_002)
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT8 ucIndex = 0;
    VOS_UINT8 pData[]="1234";
    VOS_UINT16 usLen=5;

    g_stParseContext[1].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    gastAtClientTab[0].UserType        = AT_APP_USER;
    gastAtClientTab[1].UserType        = AT_APP_USER;

    ulRet = AT_ParseCmdIsPend(0, pData, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    GlobalMockObject::verify();
}


class Test_atDiscardInvalidCharForSms:public ::testing::Test
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


TEST_F(Test_atDiscardInvalidCharForSms, Test_atDiscardInvalidCharForSms_001)
{
    VOS_UINT8*pData = (VOS_UINT8*)"AT+CMGS=\r\n";
    VOS_UINT16 usLen   = 10;

    AT_DiscardInvalidCharForSms(pData, &usLen);

    EXPECT_EQ(usLen,9);

    GlobalMockObject::verify();

}


TEST_F(Test_atDiscardInvalidCharForSms, Test_atDiscardInvalidCharForSms_002)
{
    VOS_UINT8*pData = (VOS_UINT8*)"AT+CMGS=\r\n\r\n";
    VOS_UINT16 usLen   = 11;

    AT_DiscardInvalidCharForSms(pData, &usLen);

    EXPECT_EQ(usLen,9);

    GlobalMockObject::verify();

}



class Test_atResetParseVariable: public ::testing::Test
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


TEST_F(Test_atResetParseVariable, Test_atResetParseVariable_001)
{
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;
    g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;

    AT_ResetParseVariable();

    EXPECT_EQ(g_stATParseCmd.ucCmdOptType,AT_CMD_OPT_BUTT);
    EXPECT_EQ(g_stATParseCmd.ucCmdFmtType,AT_CMD_TYPE_BUTT);

    GlobalMockObject::verify();

}


class Test_ParseCmdType: public ::testing::Test
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


TEST_F(Test_ParseCmdType, Test_ParseCmdType_001)
{
    VOS_UINT8* pData =(VOS_UINT8*) "AT";
    VOS_UINT16   usLen = 1;
    VOS_UINT32   ulRet = ERR_MSP_SUCCESS;

    ulRet = AT_ParseCmdType(pData, usLen);
    EXPECT_EQ(ulRet,AT_ERROR);

    pData =(VOS_UINT8*) "AT";
    usLen = 2;
    ulRet = ERR_MSP_SUCCESS;
    ulRet = AT_ParseCmdType(pData, usLen);
    EXPECT_EQ(ulRet,AT_OK);

    pData =(VOS_UINT8*) "AT;";
    usLen = 3;
    ulRet = ERR_MSP_SUCCESS;
    ulRet = AT_ParseCmdType(pData, usLen);
    EXPECT_EQ(ulRet,AT_OK);

    GlobalMockObject::verify();

}


TEST_F(Test_ParseCmdType, Test_ParseCmdType_002)
{
    VOS_UINT8* pData =(VOS_UINT8*) "BT";
    VOS_UINT16   usLen = 2;
    VOS_UINT32   ulRet = ERR_MSP_SUCCESS;

    ulRet = AT_ParseCmdType(pData, usLen);

    EXPECT_EQ(ulRet,AT_ERROR);

    GlobalMockObject::verify();

}



TEST_F(Test_ParseCmdType, Test_ParseCmdType_003)
{
    VOS_UINT8* pData = (VOS_UINT8*)"AT+CGDCONT?";
    VOS_UINT16   usLen = 11;
    VOS_UINT32   ulRet = ERR_MSP_SUCCESS;

    MOCKER(atParseExtendCmd)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_SUCCESS));
    ulRet = AT_ParseCmdType(pData, usLen);

    EXPECT_EQ(ulRet,AT_SUCCESS);
    //EXPECT_EQ(g_stATParseCmd.stCmdName.aucCmdName,"AT+CGDCONT");

    GlobalMockObject::verify();

}


class Test_atMatchCmdName: public ::testing::Test
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


TEST_F(Test_atMatchCmdName, Test_atMatchCmdName_001)
{
    VOS_UINT32 ulRet;
    VOS_UINT8 ucClientId = 0;
    VOS_UINT32 CmdType   = AT_EXTEND_CMD_TYPE;

    PS_MEM_CPY(g_stATParseCmd.stCmdName.aucCmdName,"AT+CCC",7);
    g_stATParseCmd.stCmdName.usCmdNameLen = 7;
    g_stCmdTblList.next = &g_stCmdTblList;
    g_stCmdTblList.prev = &g_stCmdTblList;

    ulRet = atMatchCmdName(ucClientId, CmdType);

    EXPECT_EQ(ulRet,AT_CMD_NOT_SUPPORT);

    GlobalMockObject::verify();

}


class Test_ParseParam: public ::testing::Test
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


TEST_F(Test_ParseParam, Test_ParseParam_001)
{
    VOS_UINT32   ulRet  = ERR_MSP_FAILURE;
    VOS_UINT8* pParam = (VOS_UINT8*)"5,0";
    AT_PAR_CMD_ELEMENT_STRU stCmdElement = {0};

    stCmdElement.pszParam = pParam;

    ulRet = ParseParam(&stCmdElement);

    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    // EXPECT_EQ(g_stATParseCmd.auStrRange[0],5);
    GlobalMockObject::verify();

}


TEST_F(Test_ParseParam, Test_ParseParam_002)
{
    VOS_UINT32   ulRet  = ERR_MSP_FAILURE;
    VOS_UINT8* pParam = (VOS_UINT8*)"33,0";
    AT_PAR_CMD_ELEMENT_STRU stCmdElement = {0};

    stCmdElement.pszParam = pParam;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    ulRet = ParseParam(&stCmdElement);

    EXPECT_EQ(ulRet,AT_CME_INCORRECT_PARAMETERS);
    GlobalMockObject::verify();

}


class Test_fwCmdTestProc: public ::testing::Test
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


TEST_F(Test_fwCmdTestProc, Test_fwCmdTestProc_001)
{
    VOS_UINT32   ulRet = ERR_MSP_FAILURE;
    AT_PAR_CMD_ELEMENT_STRU stCmdElement = {0};

    VOS_UINT8* pCmdName = (VOS_UINT8*)"+CGDSCONT";
    VOS_UINT8* pPara    = (VOS_UINT8*)"(1-11),(1-11),(0-2),(0-3)";

    stCmdElement.pszCmdName = (VOS_UINT8*)"+CGDSCONT";
    stCmdElement.pszParam   = (VOS_UINT8*)"(1-11),(1-11),(0-2),(0-3)";

    ulRet = fwCmdTestProc(0, &stCmdElement);

    EXPECT_EQ(ulRet,AT_OK);
    //   EXPECT_STREQ(pgucAtSndCodeAddr,"+CGDSCONT: (1-11),(1-11),(0-2),(0-3)");
    GlobalMockObject::verify();

}


class Test_atCmdDispatch: public ::testing::Test
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


TEST_F(Test_atCmdDispatch, Test_atCmdDispatch_001)
{
    VOS_UINT32 ulRet   = ERR_MSP_SUCCESS;
    VOS_UINT8  ulIndex = 0;
    AT_PAR_CMD_ELEMENT_STRU stCmdElement = {0};
    g_stParseContext[0].pstCmdElement = &stCmdElement;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    MOCKER(fwCmdTestProc)
        .stubs()
        .will(returnValue((AT_RRETURN_CODE_ENUM_UINT32)AT_OK));

    ulRet = atCmdDispatch(ulIndex);
    EXPECT_EQ(ulRet,AT_OK);

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    ulRet = atCmdDispatch(ulIndex);
    EXPECT_EQ(ulRet,AT_ERROR);

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    ulRet = atCmdDispatch(ulIndex);
    EXPECT_EQ(ulRet,AT_ERROR);

    GlobalMockObject::verify();

}


TEST_F(Test_atCmdDispatch, Test_atCmdDispatch_002)
{
    VOS_UINT32 ulRet       = ERR_MSP_SUCCESS;
    VOS_UINT8  ulIndex     = 0;
    VOS_UINT32 ulExpectRet = AT_WAIT_ASYNC_RETURN;
    VOS_UINT32 ulTimerRet  = AT_SUCCESS;
    VOS_UINT32 ulTickRet   = 5;
    AT_CMD_ABORT_TICK_INFO *pstAbortTick;

    pstAbortTick = At_GetAtCmdAbortTickInfo();

    AT_PAR_CMD_ELEMENT_STRU stCmdElement = {0};
    stCmdElement.pfnSetProc = AT_SetNetScan;
    g_stParseContext[0].pstCmdElement = &stCmdElement;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    MOCKER(AT_SetNetScan)
        .expects(exactly(1))
        .will(returnValue(ulExpectRet));

    MOCKER(At_StartTimer)
        .expects(exactly(1))
        .will(returnValue(ulTimerRet));

    MOCKER(VOS_GetTick)
        .expects(exactly(1))
        .will(returnValue(ulTickRet));

    ulRet = atCmdDispatch(ulIndex);

    EXPECT_EQ(ulExpectRet, ulRet);
    EXPECT_EQ(5,pstAbortTick->ulAtSetTick[ulIndex]);

    GlobalMockObject::verify();
}


TEST_F(Test_atCmdDispatch, Test_atCmdDispatch_003)
{
    VOS_UINT32 ulRet       = ERR_MSP_SUCCESS;
    VOS_UINT8  ulIndex     = 0;
    VOS_UINT32 ulExpectRet = AT_WAIT_ASYNC_RETURN;
    VOS_UINT32 ulTimerRet  = AT_SUCCESS;
    VOS_UINT32 ulTickRet   = 5;
    AT_CMD_ABORT_TICK_INFO *pstAbortTick;

    pstAbortTick = At_GetAtCmdAbortTickInfo();

    AT_PAR_CMD_ELEMENT_STRU stCmdElement = {0};
    stCmdElement.pfnTestProc = AT_TestNetScan;
    g_stParseContext[0].pstCmdElement = &stCmdElement;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    MOCKER(AT_TestNetScan)
        .expects(exactly(1))
        .will(returnValue(ulExpectRet));

    MOCKER(At_StartTimer)
        .expects(exactly(1))
        .will(returnValue(ulTimerRet));

    MOCKER(VOS_GetTick)
        .expects(exactly(1))
        .will(returnValue(ulTickRet));

    ulRet = atCmdDispatch(ulIndex);

    EXPECT_EQ(ulExpectRet, ulRet);
    EXPECT_EQ(5,pstAbortTick->ulAtSetTick[ulIndex]);

    GlobalMockObject::verify();
}


class Test_LimitedCmdProc: public ::testing::Test
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


TEST_F(Test_LimitedCmdProc, Test_LimitedCmdProc_001)
{

    VOS_UINT32 ulRet;
    VOS_UINT8 ucClientId = 0;
    VOS_UINT8 pData[] = "1234";
    VOS_UINT16 usLen = 0;
    AT_PAR_CMD_ELEMENT_STRU stCmdElement={0};
    stCmdElement.ulChkFlag=0;
    gastAtClientTab[0].UserType = 7;

    stCmdElement.ulChkFlag = CMD_TBL_PIN_IS_LOCKED;
    ulRet = LimitedCmdProc(ucClientId, pData, usLen, &stCmdElement);
    EXPECT_EQ(ulRet,AT_OK);

    gastAtClientTab[0].UserType = AT_USBCOM_USER;
    MOCKER(AT_E5CheckRight)
        .expects(exactly(1))
        .will(returnValue((VOS_BOOL)VOS_FALSE));
    ulRet = LimitedCmdProc(ucClientId, pData, usLen, &stCmdElement);
    EXPECT_EQ(ulRet,AT_SUCCESS);

    stCmdElement.ulChkFlag = CMD_TBL_IS_E5_DOCK | CMD_TBL_E5_IS_LOCKED;
    gastAtClientTab[0].UserType = AT_USBCOM_USER;
    MOCKER(AT_DockHandleCmd)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_SUCCESS));
    ulRet = LimitedCmdProc(ucClientId, pData, usLen, &stCmdElement);
    EXPECT_EQ(ulRet,AT_SUCCESS);

    stCmdElement.ulChkFlag = CMD_TBL_E5_IS_LOCKED;
    MOCKER(At_CheckUsimStatus)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));
    ulRet = LimitedCmdProc(ucClientId, pData, usLen, &stCmdElement);
    EXPECT_EQ(ulRet,AT_OK);

    GlobalMockObject::verify();

}

TEST_F(Test_LimitedCmdProc, Test_LimitedCmdProc_002)
{

    VOS_UINT32 ulRet;
    VOS_UINT8 ucClientId = 0;
    VOS_UINT8 pData[] = "1234";
    VOS_UINT16 usLen = 0;
    AT_PAR_CMD_ELEMENT_STRU stCmdElement={0};
    stCmdElement.ulChkFlag=0;
    gastAtClientTab[0].UserType = 7;

    stCmdElement.ulChkFlag = CMD_TBL_PIN_IS_LOCKED;
    ulRet = LimitedCmdProc(ucClientId, pData, usLen, &stCmdElement);
    EXPECT_EQ(ulRet,AT_OK);

    gastAtClientTab[0].UserType = AT_USBCOM_USER;
    MOCKER(AT_E5CheckRight)
        .expects(exactly(1))
        .will(returnValue((VOS_BOOL)VOS_FALSE));
    ulRet = LimitedCmdProc(ucClientId, pData, usLen, &stCmdElement);
    EXPECT_EQ(ulRet,AT_SUCCESS);

    stCmdElement.ulChkFlag = CMD_TBL_IS_E5_DOCK | CMD_TBL_E5_IS_LOCKED;
    gastAtClientTab[0].UserType = AT_USBCOM_USER;

    MOCKER(AT_DockHandleCmd)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_FAILURE));
    ulRet = LimitedCmdProc(ucClientId, pData, usLen, &stCmdElement);
    EXPECT_EQ(ulRet,AT_ERROR);

    stCmdElement.ulChkFlag = CMD_TBL_E5_IS_LOCKED;
    MOCKER(At_CheckUsimStatus)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));
    ulRet = LimitedCmdProc(ucClientId, pData, usLen, &stCmdElement);
    EXPECT_EQ(ulRet,AT_FAILURE);

    GlobalMockObject::verify();

}


class Test_DockCmdProc: public ::testing::Test
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


TEST_F(Test_DockCmdProc, Test_DockCmdProc_001)
{

}


class Test_CmdParseProc: public ::testing::Test
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


TEST_F(Test_CmdParseProc, Test_CmdParseProc_001)
{
#if(FEATURE_ON == FEATURE_E5)
    VOS_UINT32 ulRet = 0;
    VOS_UINT8 ucClientId = 0;
    VOS_UINT8 pData[] = "12345";
    VOS_UINT16 usLen = 5;
    AT_PAR_CMD_ELEMENT_STRU stCmdElement={0};
    g_stParseContext[0].pstCmdElement = &stCmdElement;

    MOCKER(AT_ParseCmdType)
        .stubs()
        .will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));
    MOCKER(atMatchCmdName)
        .stubs()
        .will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));
    MOCKER(atCmdDispatch)
        .stubs()
        .will(returnValue((AT_RRETURN_CODE_ENUM_UINT32)ERR_MSP_SUCCESS));
    ulRet = CmdParseProc(ucClientId, pData, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
#else
    VOS_UINT32 ulRet = 0;
    VOS_UINT8 ucClientId = 0;
    VOS_UINT8 pData[] = "12345";
    VOS_UINT16 usLen = 5;
    AT_PAR_CMD_ELEMENT_STRU stCmdElement={0};
    g_stParseContext[0].pstCmdElement = &stCmdElement;

    MOCKER(AT_ParseCmdType).stubs().will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));
    MOCKER(atMatchCmdName).stubs().will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));
    MOCKER(LimitedCmdProc).stubs().will(returnValue((VOS_UINT32)AT_OK));
    MOCKER(atCmdDispatch).stubs().will(returnValue((AT_RRETURN_CODE_ENUM_UINT32)ERR_MSP_SUCCESS));
    ulRet = CmdParseProc(ucClientId, pData, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

#endif

    GlobalMockObject::verify();
}


class Test_RepeatCmdProc: public ::testing::Test
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


TEST_F(Test_RepeatCmdProc, Test_RepeatCmdProc_001)
{
    VOS_UINT8* pCmd =(VOS_UINT8*) "AT+CGDCONT";
    VOS_UINT8* pData = (VOS_UINT8*)"A/";

    PS_MEM_CPY(g_stParseContext[0].aucDataBuff, pData, 3);
    g_stParseContext[0].usDataLen    = 3;

    g_stParseContext[0].pucCmdLine   = pCmd;
    g_stParseContext[0].usCmdLineLen = 11;

    RepeatCmdProc(&g_stParseContext[0]);

    EXPECT_EQ(g_stParseContext[0].usDataLen,11);
    //    EXPECT_STREQ(g_stParseContext[0].aucDataBuff,"AT+CGDCONT");

    GlobalMockObject::verify();
}


TEST_F(Test_RepeatCmdProc, Test_RepeatCmdProc_002)
{
    //g_stParseContext[0].aucDataBuff  = "A/";
    g_stParseContext[0].usDataLen    = 3;
    g_stParseContext[0].usCmdLineLen = 0;

    RepeatCmdProc(&g_stParseContext[0]);

    //    EXPECT_STREQ(g_stParseContext[0].aucDataBuff,"AT\n");

    GlobalMockObject::verify();
}


class Test_SaveRepeatCmd: public ::testing::Test
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


TEST_F(Test_SaveRepeatCmd, Test_SaveRepeatCmd_001)
{
    VOS_UINT8* pData = (VOS_UINT8*)"AT+CGDCONT";
    VOS_UINT16 usLen = 11;

    g_stParseContext[0].pucCmdLine   = NULL;
    g_stParseContext[0].usCmdLineLen = 0;

    SaveRepeatCmd(&g_stParseContext[0], pData, usLen);

//    EXPECT_STREQ(g_stParseContext[0].pucCmdLine,"AT+CGDCONT");
    EXPECT_EQ(g_stParseContext[0].usCmdLineLen,11);

    GlobalMockObject::verify();
}


class Test_ScanDelChar: public ::testing::Test
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


TEST_F(Test_ScanDelChar, Test_ScanDelChar_001)
{
    VOS_UINT8  pData[] = {'a','t','+','c','g','d','c','o','n','t','s',8,'\0'};
    VOS_UINT16 usLen   = sizeof(pData);
    VOS_UINT32 ulRet   = ERR_MSP_FAILURE;
    VOS_UINT16 usLen2  = usLen;

    ulRet = ScanDelChar(pData,&usLen,8);

    EXPECT_EQ(ulRet,AT_SUCCESS);
    EXPECT_EQ(usLen,usLen2 - 2);
    //    EXPECT_STREQ(pData,"at+cgdcont");

    GlobalMockObject::verify();
}


class Test_ScanCtlChar: public ::testing::Test
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


TEST_F(Test_ScanCtlChar, Test_ScanCtlChar_001)
{
    VOS_UINT8 * pData = (VOS_UINT8*)"at+cgdcont\r";

    VOS_UINT8 pData1[100] = {0};
    VOS_UINT16 usLen   = 12;
    VOS_UINT32 ulRet   = ERR_MSP_FAILURE;

    memcpy(pData1, pData, 12);

    ulRet = ScanCtlChar(pData1,&usLen);

    EXPECT_EQ(ulRet,AT_SUCCESS);
    EXPECT_EQ(usLen,10);
    //    EXPECT_STREQ(pData,"at+cgdcont");

    GlobalMockObject::verify();

}


class Test_ScanBlankChar: public ::testing::Test
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


TEST_F(Test_ScanBlankChar, Test_ScanBlankChar_001)
{
    VOS_UINT8  pData[]   = "at+cgdcon t";
    VOS_UINT16 usLen   = 12;
    VOS_UINT32 ulRet   = ERR_MSP_FAILURE;

    ulRet = ScanBlankChar(pData,&usLen);

    EXPECT_EQ(ulRet,AT_SUCCESS);
    EXPECT_EQ(usLen,11);
    //    EXPECT_STREQ(pData,"at+cgdcont");

    GlobalMockObject::verify();

}


class Test_FormatCmdStr: public ::testing::Test
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


TEST_F(Test_FormatCmdStr, Test_FormatCmdStr_001)
{
    VOS_UINT32 ulRet   = ERR_MSP_SUCCESS;
    VOS_UINT8  pData[] = {'a','t','+','c','g','d','c','o','n','t',13,'c','g','d'};
    VOS_UINT16 usLen   = 14;

    ulRet = FormatCmdStr(pData,&usLen,13);

    EXPECT_EQ(usLen,10);
    EXPECT_EQ(ulRet,AT_SUCCESS);

    GlobalMockObject::verify();
}


class Test_CmdStringFormat: public ::testing::Test
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


TEST_F(Test_CmdStringFormat, Test_CmdStringFormat_001)
{
    VOS_UINT32 ulRet   = ERR_MSP_FAILURE;
    VOS_UINT8  pData[] = {'a','t','+','c','g',12,'d','c',' ','o','o',8,'n','t',13,'c','g','d'};
    VOS_UINT16 usLen   = sizeof(pData);

    ulRet = CmdStringFormat(0, pData,&usLen);

    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ(usLen,10);

    GlobalMockObject::verify();
}


class Test_atCmdMsgProc: public ::testing::Test
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

        AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_AT, AT_XML_MAX_LEN);
        if (VOS_NULL_PTR == AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead)
        {
            AT_ERR_LOG("Memory malloc failed!");
        }
        AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextCur = AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead;

        ucIndex                          = AT_CLIENT_TAB_APP_INDEX;
        g_stParseContext[ucIndex].ucMode = AT_XML_MODE;
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_INVALID;

        usLen = AT_XML_MAX_LEN + 2;
        PS_MEM_SET(aucData, 0x31, usLen);

    }
    void TearDown()
    {
        if (VOS_NULL_PTR != AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead)
        {
            AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead     = VOS_NULL_PTR;
            AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextCur      = VOS_NULL_PTR;
        }
    }

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucData[AT_XML_MAX_LEN + 2];
    VOS_UINT16                          usLen;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

};


TEST_F(Test_atCmdMsgProc, Test_atCmdMsgProc_001)
{
    VOS_UINT8 ucIndex = 0;
    VOS_UINT8 pData[] = "12345";
    VOS_UINT16 usLen = 5;
    AT_PAR_CMD_ELEMENT_STRU stCmdElement={0};
    stCmdElement.ulSetTimeOut=5;
    g_stParseContext[0].ucMode = AT_SMS_MODE;
    g_stParseContext[0].pstCmdElement = &stCmdElement;

    MOCKER(At_SmsProc)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_WAIT_ASYNC_RETURN));
    atCmdMsgProc(ucIndex, pData, usLen);
    EXPECT_EQ(g_stParseContext[0].ucClientStatus,AT_FW_CLIENT_STATUS_PEND);

    GlobalMockObject::verify();
}

TEST_F(Test_atCmdMsgProc, Test_atCmdMsgProc_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    usLen                               = AT_XML_MAX_LEN + 1;
    aucData[usLen - 1]                  = ucAtS3;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // 调用被测函数
    atCmdMsgProc(ucIndex, aucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_CMD_INVALID, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


TEST_F(Test_atCmdMsgProc, Test_atCmdMsgProc_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    usLen                               = AT_XML_MAX_LEN - 101;
    aucData[usLen - 1]                  = ucAtS3;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    MOCKER(AT_IsApPort)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // 输入CPOS命令
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    
    AT_SetCposPara(AT_CLIENT_ID_APP);

    // 调用被测函数，输入第一段XML码流
    atCmdMsgProc(ucIndex, aucData, usLen);

    //再次调用被测函数，输入第二段XML码流，结束
    usLen                               = 100;
    aucData[usLen]                      = AT_CTRL_Z;
    atCmdMsgProc(ucIndex, aucData, usLen + 1);

    // 执行检查
    ulRet = PS_MEM_CMP(AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead, aucData, usLen);
    EXPECT_EQ(AT_CMD_CPOS_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    GlobalMockObject::verify();
}


TEST_F(Test_atCmdMsgProc, Test_atCmdMsgProc_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    usLen                               = 1;
    aucData[0]                          = AT_ESC;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    atCmdMsgProc(ucIndex, aucData, usLen);

    // 执行检查
    ulRet = PS_MEM_CMP(AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead, aucData, usLen);

    GlobalMockObject::verify();
}

class Test_At_CmdMsgDistr: public ::testing::Test
{
public:
    VOS_UINT8 ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_001)
{
    AT_MSG_STRU stMsg={0};
    stMsg.ucType = AT_PC_REPLAY_MSG;
    At_CmdMsgDistr(&stMsg);
    stMsg.ucType = AT_PC_REPLAY_MSG_CLIENT_TAB;
    At_CmdMsgDistr(&stMsg);
    stMsg.ucType = AT_COMBIN_BLOCK_MSG;
    At_CmdMsgDistr(&stMsg);

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_002)
{
    VOS_UINT32                          ulResetingFlag;
    AT_MSG_STRU                         stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(AT_MSG_STRU));
    stResetInd.ulSenderPid     = WUEPS_PID_AT;
    stResetInd.ulReceiverPid   = WUEPS_PID_AT;
    stResetInd.ucType          = ID_HIFI_AT_RESET_END_IND;

    /* 桩函数 */
    MOCKER(AT_GetResetFlag)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    At_MsgProc((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_003)
{
    VOS_UINT32                          ulResetingFlag;
    AT_MSG_STRU                         stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(AT_MSG_STRU));
    stResetInd.ulSenderPid     = WUEPS_PID_AT;
    stResetInd.ulReceiverPid   = WUEPS_PID_AT;
    stResetInd.ucType          = 0;

    /* 桩函数 */
    AT_SetResetFlag(VOS_TRUE);

    /* 函数调用 */

    /* 调用入口函数 */
    At_MsgProc((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#ifdef __PS_WIN32_RECUR__

TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_004)
{
    TEST_AT_MSG_STRU stMsg;

    stMsg.ucType = 0xff;//AT_PC_REPLAY_MSG

    MOCKER(AT_RestoreContextData)
        .expects(exactly(1));

    At_CmdMsgDistr((AT_MSG_STRU *)&stMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_005)
{
    VOS_UINT32                          ulResetingFlag;
    AT_MSG_STRU                         stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(AT_MSG_STRU));
    stResetInd.ulSenderPid     = WUEPS_PID_AT;
    stResetInd.ulReceiverPid   = WUEPS_PID_AT;
    stResetInd.ucType          = ID_HIFI_AT_RESET_END_IND;

    /* MOCKER */
    MOCKER(AT_RcvHifiResetEndInd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 调用入口函数 */
    At_MsgProc((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_006)
{
    AT_MSG_STRU                         stMsg;

    /* 参数初始化 */

    /* 全局变量初始化 */
    g_stAtResetCtx.ulResetingFlag = VOS_FALSE;

    /* 构造消息 */
    VOS_MemSet(&stMsg, 0, sizeof(AT_MSG_STRU));
    stMsg.ulSenderPid     = WUEPS_PID_AT;
    stMsg.ulReceiverPid   = WUEPS_PID_AT;
    stMsg.ucType          = AT_SWITCH_CMD_MODE_MSG;
    stMsg.ucIndex         = AT_CLIENT_BUTT;

    /* MOCKER操作 */
    MOCKER(AT_CheckHsUartUser)
        .expects(never());

    /* 调用被测函数 */
    At_MsgProc((MsgBlock *)&stMsg);

    /* 执行检查 */


    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_007)
{
    AT_MSG_STRU                         stMsg;

    /* 参数初始化 */

    /* 全局变量初始化 */
    g_stAtResetCtx.ulResetingFlag = VOS_FALSE;

    /* 构造消息 */
    VOS_MemSet(&stMsg, 0, sizeof(AT_MSG_STRU));
    stMsg.ulSenderPid     = WUEPS_PID_AT;
    stMsg.ulReceiverPid   = WUEPS_PID_AT;
    stMsg.ucType          = AT_SWITCH_CMD_MODE_MSG;
    stMsg.ucIndex         = AT_CLIENT_TAB_PCUI_INDEX;

    /* MOCKER操作 */

    /* 调用被测函数 */
    At_MsgProc((MsgBlock *)&stMsg);

    /* 执行检查 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_008)
{
    AT_MSG_STRU                         stMsg;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    /* 全局变量初始化 */
    g_stAtResetCtx.ulResetingFlag = VOS_FALSE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    /* 构造消息 */
    VOS_MemSet(&stMsg, 0, sizeof(AT_MSG_STRU));
    stMsg.ulSenderPid     = WUEPS_PID_AT;
    stMsg.ulReceiverPid   = WUEPS_PID_AT;
    stMsg.ucType          = AT_SWITCH_CMD_MODE_MSG;
    stMsg.ucIndex         = ucIndex;

    /* MOCKER操作 */

    /* 调用被测函数 */
    At_MsgProc((MsgBlock *)&stMsg);

    /* 执行检查 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_009)
{
    AT_MSG_STRU                         stMsg;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    /* 全局变量初始化 */
    g_stAtResetCtx.ulResetingFlag = VOS_FALSE;
    gastAtClientTab[ucIndex].Mode = AT_CMD_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    /* 构造消息 */
    VOS_MemSet(&stMsg, 0, sizeof(AT_MSG_STRU));
    stMsg.ulSenderPid     = WUEPS_PID_AT;
    stMsg.ulReceiverPid   = WUEPS_PID_AT;
    stMsg.ucType          = AT_SWITCH_CMD_MODE_MSG;
    stMsg.ucIndex         = AT_CLIENT_TAB_HSUART_INDEX;

    /* MOCKER操作 */
    MOCKER(At_FormatResultData)
    .expects(never());

    /* 调用被测函数 */
    At_MsgProc((MsgBlock *)&stMsg);

    /* 执行检查 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_010)
{
    AT_MSG_STRU                         stMsg;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    /* 全局变量初始化 */
    g_stAtResetCtx.ulResetingFlag = VOS_FALSE;
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    /* 构造消息 */
    VOS_MemSet(&stMsg, 0, sizeof(AT_MSG_STRU));
    stMsg.ulSenderPid     = WUEPS_PID_AT;
    stMsg.ulReceiverPid   = WUEPS_PID_AT;
    stMsg.ucType          = AT_SWITCH_CMD_MODE_MSG;
    stMsg.ucIndex         = AT_CLIENT_TAB_HSUART_INDEX;

    /* MOCKER操作 */
    MOCKER(At_FormatResultData)
    .expects(exactly(1));

    /* 调用被测函数 */
    At_MsgProc((MsgBlock *)&stMsg);

    /* 执行检查 */
    EXPECT_EQ(AT_DATA_STOP_STATE,gastAtClientTab[ucIndex].DataState);
    EXPECT_EQ(AT_ONLINE_CMD_MODE,gastAtClientTab[ucIndex].Mode);
    EXPECT_EQ(AT_NORMAL_MODE,g_stParseContext[ucIndex].ucMode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_011)
{
    AT_MSG_STRU                         stMsg;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    /* 全局变量初始化 */
    g_stAtResetCtx.ulResetingFlag = VOS_FALSE;
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;

    /* 构造消息 */
    VOS_MemSet(&stMsg, 0, sizeof(AT_MSG_STRU));
    stMsg.ulSenderPid     = WUEPS_PID_AT;
    stMsg.ulReceiverPid   = WUEPS_PID_AT;
    stMsg.ucType          = AT_SWITCH_CMD_MODE_MSG;
    stMsg.ucIndex         = AT_CLIENT_TAB_HSUART_INDEX;

    /* MOCKER操作 */
    MOCKER(At_FormatResultData)
    .expects(exactly(1));

    /* 调用被测函数 */
    At_MsgProc((MsgBlock *)&stMsg);

    /* 执行检查 */
    EXPECT_EQ(AT_DATA_STOP_STATE,gastAtClientTab[ucIndex].DataState);
    EXPECT_EQ(AT_ONLINE_CMD_MODE,gastAtClientTab[ucIndex].Mode);
    EXPECT_EQ(AT_NORMAL_MODE,g_stParseContext[ucIndex].ucMode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F(Test_At_CmdMsgDistr, Test_At_CmdMsgDistr_012)
{
    AT_MSG_STRU                         stMsg;

    /* 参数初始化 */
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;

    /* 全局变量初始化 */
    g_stAtResetCtx.ulResetingFlag = VOS_FALSE;
    gastAtClientTab[ucIndex].Mode = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode = AT_IP_DATA_MODE;
    gastAtClientTab[ucIndex].UserType = AT_HSUART_USER;
    g_stAtCommCtx.stUartCtx.stLineCtrl.enDsrMode = AT_UART_DSR_MODE_CONNECT_ON;

    /* 构造消息 */
    VOS_MemSet(&stMsg, 0, sizeof(AT_MSG_STRU));
    stMsg.ulSenderPid     = WUEPS_PID_AT;
    stMsg.ulReceiverPid   = WUEPS_PID_AT;
    stMsg.ucType          = AT_SWITCH_CMD_MODE_MSG;
    stMsg.ucIndex         = AT_CLIENT_TAB_HSUART_INDEX;

    /* MOCKER操作 */
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    /* 调用被测函数 */
    At_MsgProc((MsgBlock *)&stMsg);

    /* 执行检查 */
    EXPECT_EQ(AT_DATA_STOP_STATE,gastAtClientTab[ucIndex].DataState);
    EXPECT_EQ(AT_ONLINE_CMD_MODE,gastAtClientTab[ucIndex].Mode);
    EXPECT_EQ(AT_NORMAL_MODE,g_stParseContext[ucIndex].ucMode);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}




class Test_atfwParseSaveParam: public ::testing::Test
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


TEST_F(Test_atfwParseSaveParam, Test_atfwParseSaveParam_001)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT8* pStringBuf = (VOS_UINT8*)"5,0";
    VOS_UINT16 usLen      = 2;

    gucAtParaIndex = 0;
    PS_MEM_SET(gastAtParaList[0].aucPara, 0, AT_PARA_MAX_LEN + 1);

    ulRet = atfwParseSaveParam(pStringBuf, usLen);

    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ(gastAtParaList[0].usParaLen,usLen);
    //   EXPECT_STREQ(gastAtParaList[0].aucPara,"15");

    GlobalMockObject::verify();

}


TEST_F(Test_atfwParseSaveParam, Test_atfwParseSaveParam_002)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT8* pStringBuf = NULL;
    VOS_UINT16 usLen      = 0;

    gucAtParaIndex = 0;

    ulRet = atfwParseSaveParam(pStringBuf, usLen);

    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ(gastAtParaList[0].usParaLen,0);

    GlobalMockObject::verify();
}


TEST_F(Test_atfwParseSaveParam, Test_atfwParseSaveParam_003)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT8* pStringBuf = NULL;
    VOS_UINT16 usLen      = 4;

    gucAtParaIndex = 0;

    ulRet = atfwParseSaveParam(pStringBuf, usLen);

    EXPECT_EQ(ulRet,ERR_MSP_FAILURE);

    GlobalMockObject::verify();
}


class Test_AT_FwSendClientMsg: public ::testing::Test
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


TEST_F(Test_AT_FwSendClientMsg, Test_AT_FwSendClientMsg_001)
{
    VOS_UINT32 ulRcvPid = 0;
    VOS_UINT32 ulMsgId = ID_MSG_AT_FW_CMD_BINARY_MSG;
    VOS_UINT16 usMsgParamSize=10;
    VOS_VOID *pMsgParam = (VOS_VOID *)AT_FwSendClientMsg;
    VOS_UINT32 ulRet=0;

    //MOCKER(atFWSendMsg).will(returnValue(ERR_MSP_SUCCESS));
    ulRet = AT_FwSendClientMsg(ulRcvPid, ulMsgId, usMsgParamSize, pMsgParam);

    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    GlobalMockObject::verify();
}


class Test_At_CmdTestProcERROR: public ::testing::Test
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


TEST_F(Test_At_CmdTestProcERROR, Test_At_CmdTestProcERROR_001)
{
    VOS_UINT32 ulRet=1;
    ulRet = At_CmdTestProcERROR(0);
    EXPECT_EQ(ulRet,AT_ERROR);

    GlobalMockObject::verify();
}


class Test_At_CmdTestProcOK: public ::testing::Test
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


TEST_F(Test_At_CmdTestProcOK, Test_At_CmdTestProcOK_001)
{
    VOS_UINT32 ulRet=1;
    ulRet = At_CmdTestProcOK(0);
    EXPECT_EQ(ulRet,AT_OK);

    GlobalMockObject::verify();
}


class Test_At_CmdStreamRcv: public ::testing::Test
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


TEST_F(Test_At_CmdStreamRcv, Test_At_CmdStreamRcv_001)
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT8 ucIndex = 0;
    VOS_UINT8 pData[]="12345";
    VOS_UINT16 usLen=5;

    ulRet = At_CmdStreamRcv(ucIndex, pData, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    VOS_UINT8 *pData2=NULL;
    usLen=5;

    ulRet = At_CmdStreamRcv(ucIndex, pData2, usLen);
    EXPECT_EQ(ulRet,ERR_MSP_INVALID_PARAMETER);

    GlobalMockObject::verify();


}


class Test_At_ReadyClientCmdProc: public ::testing::Test
{
public:
    VOS_UINT8            ucIndex;
    VOS_UINT8           *pData;
    VOS_UINT16           usLen;
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_ReadyClientCmdProc, Test_At_ReadyClientCmdProc_001)
{
    ucIndex = 0;
    pData   = (VOS_UINT8 *)"12345";
    usLen   = VOS_StrLen((VOS_CHAR *)pData);

    MOCKER(At_CombineCmdChkProc)
        .expects(never());

    At_ReadyClientCmdProc(ucIndex, pData, usLen);


    GlobalMockObject::verify();
}


TEST_F(Test_At_ReadyClientCmdProc, Test_At_ReadyClientCmdProc_002)
{
    // 变量声明

    // 参数初始化
    ucIndex = 0;
    pData   = (VOS_UINT8 *)"AT^FACAUTHPUBKEY=123";
    usLen   = VOS_StrLen((VOS_CHAR *)pData);

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(CmdStringFormat)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));

    MOCKER(At_HandleApModemSpecialCmd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    MOCKER(At_CombineCmdChkProc)
        .expects(never());

    // 调用被测函数
    At_ReadyClientCmdProc(ucIndex, pData, usLen);

    // 执行检查

    GlobalMockObject::verify();
}


class Test_AT_IsAbortCmdStr: public ::testing::Test
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


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_001)
{
    VOS_UINT8                           aucData[10];
    VOS_UINT16                          usLen;

    usLen = 10;

    MOCKER(AT_GetAbortCmdPara)
        .expects(exactly(1))
        .will(returnValue((AT_ABORT_CMD_PARA_STRU *)VOS_NULL_PTR));

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdStr(0, aucData, usLen));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_002)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10];
    VOS_UINT16                          usLen;

    usLen = 10;

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_FALSE;

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdStr(0, aucData, usLen));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_003)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10];
    VOS_UINT16                          usLen;

    usLen = 0;

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdStr(0, aucData, usLen));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_004)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10];
    VOS_UINT16                          usLen;

    usLen = 2;

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

    VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, "at^break");

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdStr(0, aucData, usLen));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_005)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10]="At^Break";

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

    VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, "at^break");

    EXPECT_EQ(VOS_TRUE, AT_IsAbortCmdStr(0, aucData, VOS_StrLen((VOS_CHAR *)aucData)));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_006)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10]="At+Break";

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

    VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, "at^break");

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdStr(0, aucData, VOS_StrLen((VOS_CHAR *)aucData)));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_007)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10]="At+Break";
    VOS_UINT32                          ulTickRet = 16;

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;
    At_SetAtCmdAbortTickInfo(0, 5);

    MOCKER(VOS_GetTick)
        .expects(exactly(1))
        .will(returnValue(ulTickRet));

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdStr(0, aucData, VOS_StrLen((VOS_CHAR *)aucData)));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_008)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10]="At+Break";
    VOS_UINT32                          ulTickRet = 21;

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;
    At_SetAtCmdAbortTickInfo(0, 5);
    At_SetAtCmdAnyAbortFlg(VOS_FALSE);

    MOCKER(VOS_GetTick)
        .expects(exactly(1))
        .will(returnValue(ulTickRet));

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdStr(0, aucData, 0));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_009)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10]="At+Break";
    VOS_UINT32                          ulTickRet = 21;

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;
    At_SetAtCmdAbortTickInfo(0, 5);
    At_SetAtCmdAnyAbortFlg(VOS_TRUE);

    MOCKER(VOS_GetTick)
        .expects(exactly(1))
        .will(returnValue(ulTickRet));

    EXPECT_EQ(VOS_TRUE, AT_IsAbortCmdStr(0, aucData, VOS_StrLen((VOS_CHAR *)aucData)));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAbortCmdStr, Test_AT_IsAbortCmdStr_010)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;
    VOS_UINT8                           aucData[10]="At+Break";
    VOS_UINT32                          ulTickRet = 0xFFFFFFF0;

    pstAbortCmdPara = AT_GetAbortCmdPara();

    pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;
    At_SetAtCmdAbortTickInfo(0, 150);
    At_SetAtCmdAnyAbortFlg(VOS_TRUE);

    MOCKER(VOS_GetTick)
        .expects(exactly(1))
        .will(returnValue(ulTickRet));

    EXPECT_EQ(VOS_TRUE, AT_IsAbortCmdStr(0, aucData, VOS_StrLen((VOS_CHAR *)aucData)));

    GlobalMockObject::verify();
}


class Test_AT_AbortCmdProc: public ::testing::Test
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

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;

        At_PidInit(VOS_IP_INITIAL);

        pstAbortCmdPara = AT_GetAbortCmdPara();

        pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, "AT");

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtRspStr, "ABORT");

        PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

        AT_STOP_TIMER_CMD_READY(0);

        PS_MEM_SET(&(g_stParseContext[0]), 0x00, sizeof(g_stParseContext[0]));

        At_ResetCombinParseInfo(0);

        for(int i = AT_CLIENT_ID_PCUI;i < AT_CLIENT_ID_BUTT;i++)
        {
            g_stParseContext[i].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
        }
    }

    void TearDown()
    {

    }
};


TEST_F(Test_AT_AbortCmdProc, Test_AT_AbortCmdProc_001)
{
    VOS_UINT32                          ulTick;

    ulTick = VOS_GetTick();

    VOS_UINT8                           aucMsgCops[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x12,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0A,0x00,0x41,0x54,0x2B,0x43,0x4F,0x50,0x53,0x3D,
        0x3F,0x0D
    };

    VOS_UINT8                           aucMsgAt[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x0B,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x03,0x00,0x41,0x54,0x0D
    };

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    At_MsgProc((MsgBlock *)aucMsgCops);


    /* 确保不受125ms丢弃影响 */
    ulTick += 100000;
    MOCKER(VOS_GetTick)
        .stubs()
        .will(returnValue(ulTick));

    At_MsgProc((MsgBlock *)aucMsgAt);

    EXPECT_EQ(AT_CMD_COPS_ABORT_PLMN_LIST, gastAtClientTab[0].CmdCurrentOpt);


    GlobalMockObject::verify();

}


TEST_F(Test_AT_AbortCmdProc, Test_AT_AbortCmdProc_002)
{
    VOS_UINT32                          ulTick;

    ulTick = VOS_GetTick();

    VOS_UINT8                           aucMsgCops[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x12,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0A,0x00,0x41,0x54,0x2B,0x43,0x4F,0x50,0x53,0x3D,
        0x3F,0x0D
    };

    VOS_UINT8                           aucMsgAt[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x0B,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x03,0x00,0x41,0x54,0x0D
    };
    VOS_UINT32                          ulTmpLen;

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    At_MsgProc((MsgBlock *)aucMsgCops);

    ulTmpLen = g_stParseContext[0].pstCmdElement->ulAbortTimeOut;
    g_stParseContext[0].pstCmdElement->ulAbortTimeOut = 0;


    /* 确保不受125ms丢弃影响 */
    ulTick += 100000;
    MOCKER(VOS_GetTick)
        .stubs()
        .will(returnValue(ulTick));

    At_MsgProc((MsgBlock *)aucMsgAt);

    EXPECT_EQ(AT_CMD_COPS_ABORT_PLMN_LIST, gastAtClientTab[0].CmdCurrentOpt);

    g_stParseContext[0].pstCmdElement->ulAbortTimeOut = ulTmpLen;

    GlobalMockObject::verify();

}


TEST_F(Test_AT_AbortCmdProc, Test_AT_AbortCmdProc_003)
{
    VOS_UINT32                          ulTick;

    ulTick = VOS_GetTick();

    VOS_UINT8                           aucMsgCops[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x12,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0A,0x00,0x41,0x54,0x2B,0x43,0x4F,0x50,0x53,0x3D,
        0x3F,0x0D
    };

    VOS_UINT8                           aucMsgAt[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x0B,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x03,0x00,0x41,0x54,0x0D
    };

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    At_MsgProc((MsgBlock *)aucMsgCops);

    MOCKER(At_StartTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    /* 确保不受125ms丢弃影响 */
    ulTick += 100000;
    MOCKER(VOS_GetTick)
        .stubs()
        .will(returnValue(ulTick));


    At_MsgProc((MsgBlock *)aucMsgAt);

    EXPECT_EQ(AT_CMD_COPS_ABORT_PLMN_LIST, gastAtClientTab[0].CmdCurrentOpt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_AbortCmdProc, Test_AT_AbortCmdProc_004)
{
    VOS_UINT32                          ulTick;

    ulTick = VOS_GetTick();

    VOS_UINT8                           aucMsgCops[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x12,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0A,0x00,0x41,0x54,0x2B,0x43,0x4F,0x50,0x53,0x3D,
        0x3F,0x0D
    };

    VOS_UINT8                           aucMsgAt[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x0B,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x03,0x00,0x41,0x54,0x0D
    };

    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

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

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    MOCKER(At_AbortCopsPara)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_ABORT));

    At_MsgProc((MsgBlock *)aucMsgCops);

    MOCKER(AT_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 确保不受125ms丢弃影响 */
    ulTick += 100000;
    MOCKER(VOS_GetTick)
        .stubs()
        .will(returnValue(ulTick));

    At_MsgProc((MsgBlock *)aucMsgAt);

    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[0].CmdCurrentOpt);

    EXPECT_EQ(AT_FW_CLIENT_STATUS_READY, g_stParseContext[0].ucClientStatus);

    EXPECT_STREQ((char*)pgucAtSndCodeAddr, (char*)aucDataAt);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_AbortCmdProc, Test_AT_AbortCmdProc_005)
{
    VOS_UINT8                           aucMsgCops[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x12,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0A,0x00,0x41,0x54,0x2B,0x43,0x4F,0x50,0x53,0x3D,
        0x3F,0x0D
    };

    VOS_UINT8                           aucMsgAt[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x0B,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x03,0x00,0x41,0x54,0x0D
    };/* AT */

    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

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

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    MOCKER(At_AbortCopsPara)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    At_MsgProc((MsgBlock *)aucMsgCops);

    At_MsgProc((MsgBlock *)aucMsgAt);

    EXPECT_EQ(AT_CMD_COPS_TEST, gastAtClientTab[0].CmdCurrentOpt);

    EXPECT_STRNE((char*)pgucAtSndCodeAddr, (char*)aucDataAt);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_AbortCmdProc, Test_AT_AbortCmdProc_006)
{
    g_stParseContext[0].pstCmdElement = VOS_NULL_PTR;

    AT_AbortCmdProc(0);
}


TEST_F(Test_AT_AbortCmdProc, Test_AT_AbortCmdProc_007)
{
    AT_PAR_CMD_ELEMENT_STRU             stCopsCmd =
    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    VOS_NULL_PTR,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2,7)"};


    g_stParseContext[0].pstCmdElement = &stCopsCmd;

    g_stParseContext[0].pstCmdElement->pfnAbortProc = VOS_NULL_PTR;

    AT_AbortCmdProc(0);

    GlobalMockObject::verify();
}


class Test_AT_SaveCmdElementInfo: public ::testing::Test
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

        MOCKER(NV_WriteEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;

        At_PidInit(VOS_IP_INITIAL);

        pstAbortCmdPara = AT_GetAbortCmdPara();

        pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, "AT");

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtRspStr, "ABORT");

        PS_MEM_SET(&gstAtSendData,    0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

        PS_MEM_SET(&(g_stParseContext[0]), 0x00, sizeof(g_stParseContext[0]));

        AT_STOP_TIMER_CMD_READY(0);
        At_ResetCombinParseInfo(0);
        for(int i = AT_CLIENT_ID_PCUI;i < AT_CLIENT_ID_BUTT;i++)
        {
            g_stParseContext[i].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
        }
    }

    void TearDown()
    {

    }
};


TEST_F(Test_AT_SaveCmdElementInfo, Test_AT_SaveCmdElementInfo_001)
{
    AT_PAR_CMD_ELEMENT_STRU             stCopsCmd =
    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    VOS_NULL_PTR,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2,7)"};


    g_stParseContext[0].pstCmdElement = &stCopsCmd;

    MOCKER(AT_GetCmdElementInfo)
        .expects(never());

    AT_SaveCmdElementInfo(0, VOS_NULL_PTR, AT_EXTEND_CMD_TYPE);

    EXPECT_EQ(g_stParseContext[0].pstCmdElement, &stCopsCmd);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SaveCmdElementInfo, Test_AT_SaveCmdElementInfo_002)
{
    AT_PAR_CMD_ELEMENT_STRU             stCopsCmd =
    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    VOS_NULL_PTR,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2,7)"};


    g_stParseContext[0].pstCmdElement = &stCopsCmd;

    AT_SaveCmdElementInfo(0, (VOS_UINT8*)"^BREAK", AT_EXTEND_CMD_TYPE);

    EXPECT_EQ(g_stParseContext[0].pstCmdElement, &stCopsCmd);

    GlobalMockObject::verify();
}

TEST_F(Test_AT_SaveCmdElementInfo, Test_AT_SaveCmdElementInfo_003)
{
    AT_PAR_CMD_ELEMENT_STRU             stCopsCmd =
    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    VOS_NULL_PTR,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2,7)"};


    g_stParseContext[0].pstCmdElement = &stCopsCmd;

    AT_SaveCmdElementInfo(0, (VOS_UINT8*)"^BREAK", AT_CMD_TYPE_BUTT);

    EXPECT_EQ(g_stParseContext[0].pstCmdElement, &stCopsCmd);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SaveCmdElementInfo, Test_AT_SaveCmdElementInfo_004)
{
    VOS_UINT8                           aucMsgCops[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x1D,0x23,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x1B,0x00,0x41,0x54,0x5E,0x53,0x49,0x4D,0x4C,0x4F,
        0x43,0x4b,0x3D,0x31,0x2C,0x32,0x2C,0x34,0x36,0x30,
        0x30,0x31,0x2C,0x34,0x36,0x30,0x30,0x39,0x0D
    };  /* AT^SIMLOCK=1,2,46001,46009 */
    VOS_UINT8                           aucMsgAt[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x0B,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x03,0x00,0x41,0x54,0x0D
    };/* AT */

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue(AT_OK));

    At_MsgProc((MsgBlock *)aucMsgCops);

    At_MsgProc((MsgBlock *)aucMsgAt);

    EXPECT_STREQ("^SIMLOCK", (VOS_CHAR*)(g_stParseContext[0].pstCmdElement->pszCmdName));

    GlobalMockObject::verify();
}

TEST_F(Test_AT_SaveCmdElementInfo, Test_AT_SaveCmdElementInfo_005)
{
    VOS_UINT8                           aucMsgCops[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x1D,0x15,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0D,0x00,0x41,0x54,0x5E,0x53,0x49,0x4D,0x4C,0x4F,
        0x43,0x4b,0x3D,0x32,0x0D
    };  /* AT^SIMLOCK=1,2,46001,46009 */
    VOS_UINT8                           aucMsgAt[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x0B,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x03,0x00,0x41,0x54,0x0D
    };/* AT */
    HI_LIST_S                          *pstCmdTblList = VOS_NULL_PTR;
    AT_PAR_CMDTBL_LIST_STRU            *pstCurCmdNode = VOS_NULL_PTR;

    const VOS_UINT8                    *pszCmdName = VOS_NULL_PTR;

    pstCmdTblList   = &(g_stCmdTblList);

    pstCurCmdNode = msp_list_entry(pstCmdTblList->next, AT_PAR_CMDTBL_LIST_STRU, stCmdTblList);

    /* 构造异常元素 */
    pszCmdName = pstCurCmdNode->pstCmdElement[0].pszCmdName;
    pstCurCmdNode->pstCmdElement[0].pszCmdName = VOS_NULL_PTR;

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue(AT_OK));

    At_MsgProc((MsgBlock *)aucMsgCops);

    EXPECT_STREQ("^SIMLOCK", (VOS_CHAR*)(g_stParseContext[0].pstCmdElement->pszCmdName));

    pstCurCmdNode->pstCmdElement[0].pszCmdName = pszCmdName; 

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SaveCmdElementInfo, Test_AT_SaveCmdElementInfo_006)
{
    AT_MSG_STRU                        *pstAtMsg;
    VOS_UINT8                           aucAtCmd[] = "AT^FACAUTHPUBKEY=\r";

    pstAtMsg = (AT_MSG_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MSG_STRU)+50);

    pstAtMsg->ulSenderPid   = WUEPS_PID_AT;
    pstAtMsg->ulReceiverPid = WUEPS_PID_AT;

    pstAtMsg->ucType     = 0;
    pstAtMsg->ucUserType = 0;
    pstAtMsg->ucIndex    = 0;
    pstAtMsg->usLen      = VOS_StrLen((VOS_CHAR *)aucAtCmd);

    VOS_MemCpy(pstAtMsg->aucValue, aucAtCmd, VOS_StrLen((VOS_CHAR *)aucAtCmd));

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    At_MsgProc((MsgBlock *)pstAtMsg);

    EXPECT_STREQ("^FACAUTHPUBKEY", (VOS_CHAR*)(g_stParseContext[0].pstCmdElement->pszCmdName));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SaveCmdElementInfo, Test_AT_SaveCmdElementInfo_007)
{
    AT_MSG_STRU                        *pstAtMsg;
    VOS_UINT8                           aucAtCmd[] = "AT^DOCK=\r";

    pstAtMsg = (AT_MSG_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MSG_STRU)+50);

    pstAtMsg->ulSenderPid   = WUEPS_PID_AT;
    pstAtMsg->ulReceiverPid = WUEPS_PID_AT;

    pstAtMsg->ucType     = 0;
    pstAtMsg->ucUserType = 0;
    pstAtMsg->ucIndex    = 0;
    pstAtMsg->usLen      = VOS_StrLen((VOS_CHAR *)aucAtCmd);

    VOS_MemCpy(pstAtMsg->aucValue, aucAtCmd, VOS_StrLen((VOS_CHAR *)aucAtCmd));

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    MOCKER(At_MatchCmdName)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    At_MsgProc((MsgBlock *)pstAtMsg);

    EXPECT_STREQ("^DOCK", (VOS_CHAR*)(g_stParseContext[0].pstCmdElement->pszCmdName));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SaveCmdElementInfo, Test_AT_SaveCmdElementInfo_009)
{
    AT_MSG_STRU                        *pstAtMsg;
    VOS_UINT8                           aucAtCmd[] = "AT^SIMLOCKDATAWRITE=\r";

    pstAtMsg = (AT_MSG_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MSG_STRU)+50);

    pstAtMsg->ulSenderPid   = WUEPS_PID_AT;
    pstAtMsg->ulReceiverPid = WUEPS_PID_AT;

    pstAtMsg->ucType     = 0;
    pstAtMsg->ucUserType = 0;
    pstAtMsg->ucIndex    = 0;
    pstAtMsg->usLen      = VOS_StrLen((VOS_CHAR *)aucAtCmd);

    VOS_MemCpy(pstAtMsg->aucValue, aucAtCmd, VOS_StrLen((VOS_CHAR *)aucAtCmd));

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    MOCKER(At_MatchCmdName)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    At_MsgProc((MsgBlock *)pstAtMsg);

    EXPECT_STREQ("^SIMLOCKDATAWRITE", (VOS_CHAR*)(g_stParseContext[0].pstCmdElement->pszCmdName));

    GlobalMockObject::verify();
}



class Test_At_MatchSmsCmdName: public ::testing::Test
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

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;

        At_PidInit(VOS_IP_INITIAL);

        pstAbortCmdPara = AT_GetAbortCmdPara();

        pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, "AT");

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtRspStr, "ABORT");

        PS_MEM_SET(&gstAtSendData,    0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

        PS_MEM_SET(&(g_stParseContext[0]), 0x00, sizeof(g_stParseContext[0]));

        AT_STOP_TIMER_CMD_READY(0);
        At_ResetCombinParseInfo(0);

        PS_MEM_SET(g_stParseContext, 0, sizeof(AT_PARSE_CONTEXT_STRU)*AT_MAX_CLIENT_NUM);
    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_MatchSmsCmdName, Test_At_MatchSmsCmdName_001)
{
    AT_MSG_STRU                        *pstAtMsg;
    VOS_UINT8                           aucAtCmd[] = "AT+CMGS=\"139\"\r";

    pstAtMsg = (AT_MSG_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MSG_STRU)+50);

    pstAtMsg->ulSenderPid   = WUEPS_PID_AT;
    pstAtMsg->ulReceiverPid = WUEPS_PID_AT;

    pstAtMsg->ucType     = 0;
    pstAtMsg->ucUserType = 0;
    pstAtMsg->ucIndex    = 0;
    pstAtMsg->usLen      = VOS_StrLen((VOS_CHAR *)aucAtCmd);

    VOS_MemCpy(pstAtMsg->aucValue, aucAtCmd, VOS_StrLen((VOS_CHAR *)aucAtCmd));

    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    At_MsgProc((MsgBlock *)pstAtMsg);

    EXPECT_STREQ("+CMGS", (VOS_CHAR*)(g_stParseContext[0].pstCmdElement->pszCmdName));

    GlobalMockObject::verify();
}


TEST_F(Test_At_MatchSmsCmdName, Test_At_MatchSmsCmdName_002)
{
    VOS_CHAR                         aucAtCmd[] = "+CMGS";
    VOS_UINT8                        ucIndex;

    ucIndex             = 0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_TEXT;

    At_MatchSmsCmdName(ucIndex, aucAtCmd);

    EXPECT_STREQ("(da),(0-255)", (VOS_CHAR*)(g_stCmdElement[ucIndex].pszParam));
    ASSERT_EQ(AT_CMD_CMGS, g_stCmdElement[ucIndex].ulCmdIndex);

    GlobalMockObject::verify();

}


TEST_F(Test_At_MatchSmsCmdName, Test_At_MatchSmsCmdName_003)
{
    VOS_CHAR                           aucAtCmd[] = "+CMGS";
    VOS_UINT8                        ucIndex;

    ucIndex             = 0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;

    At_MatchSmsCmdName(ucIndex, aucAtCmd);

    EXPECT_STREQ("(0-255)", (VOS_CHAR*)(g_stCmdElement[ucIndex].pszParam));
    ASSERT_EQ(AT_CMD_CMGS, g_stCmdElement[ucIndex].ulCmdIndex);

    GlobalMockObject::verify();

}


class Test_AT_IsAnyParseClientPend: public ::testing::Test
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


TEST_F(Test_AT_IsAnyParseClientPend, Test_AT_IsAnyParseClientPend_001)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucClientId;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM + 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    for (ucClientId = AT_CLIENT_ID_PCUI; ucClientId < AT_MAX_CLIENT_NUM; ucClientId++)
    {
        g_stParseContext[ucClientId].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
    }

    g_stParseContext[AT_CLIENT_ID_PCUI].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    EXPECT_EQ(VOS_TRUE, AT_IsAnyParseClientPend());

    g_stParseContext[AT_CLIENT_ID_PCUI].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAnyParseClientPend, Test_AT_IsAnyParseClientPend_002)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucClientId;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM + 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_BUTT;

    for (ucClientId = AT_CLIENT_ID_PCUI; ucClientId < AT_MAX_CLIENT_NUM; ucClientId++)
    {
        g_stParseContext[ucClientId].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
    }


    EXPECT_EQ(VOS_FALSE, AT_IsAnyParseClientPend());

    GlobalMockObject::verify();
}


class Test_AT_IsAllClientDataMode: public ::testing::Test
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


TEST_F(Test_AT_IsAllClientDataMode, Test_AT_IsAllClientDataMode_001)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucClientId;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM + 1;
    pstPortBuffCfg->ulUsedClientID[0]=AT_CLIENT_ID_PCUI;

    for (ucClientId = AT_CLIENT_ID_PCUI; ucClientId < AT_CLIENT_ID_BUTT; ucClientId++)
    {
        gastAtClientTab[ucClientId].Mode = AT_CMD_MODE;
    }

    EXPECT_EQ(VOS_FALSE, AT_IsAllClientDataMode());

    GlobalMockObject::verify();

}


TEST_F(Test_AT_IsAllClientDataMode, Test_AT_IsAllClientDataMode_002)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucClientId;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    for (ucClientId = AT_CLIENT_ID_PCUI; ucClientId < AT_CLIENT_ID_BUTT; ucClientId++)
    {
        AT_AddUsedClientId2Tab(ucClientId);
        gastAtClientTab[ucClientId].Mode = AT_DATA_MODE;
    }

    EXPECT_EQ(VOS_TRUE, AT_IsAllClientDataMode());

    for (ucClientId = AT_CLIENT_ID_PCUI; ucClientId < AT_CLIENT_ID_BUTT; ucClientId++)
    {
        gastAtClientTab[ucClientId].Mode = AT_CMD_MODE;
    }

    GlobalMockObject::verify();
}


TEST_F(Test_AT_IsAllClientDataMode, Test_AT_IsAllClientDataMode_003)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucClientId;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum =  2;
    pstPortBuffCfg->ulUsedClientID[0]=AT_CLIENT_ID_PCUI;
    pstPortBuffCfg->ulUsedClientID[1]=AT_CLIENT_ID_CTRL;
    gastAtClientTab[AT_CLIENT_ID_PCUI].Mode = AT_DATA_MODE;
    gastAtClientTab[AT_CLIENT_ID_CTRL].Mode = AT_CMD_MODE;

    EXPECT_EQ(VOS_FALSE, AT_IsAllClientDataMode());

    gastAtClientTab[AT_CLIENT_ID_PCUI].Mode = AT_CMD_MODE;

    GlobalMockObject::verify();
}
