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

/*****************************************************************************
类名 : Test_AT_RegisterCmdTable
功能描述 : AT_RegisterCmdTable UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_RegisterCmdTable_001
测试用例标题      : 注册命令表成功
预期结果          : 返回ERR_MSP_SUCCESS
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_RegisterCmdTable_002
测试用例标题      : 分配命令表内存失败
预期结果          : 返回ERR_MSP_MALLOC_FAILUE
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_AT_RegisterCmdTable, Test_AT_RegisterCmdTable_002)
{
    VOS_UINT32                   ulRet = 0;
    AT_PAR_CMD_ELEMENT_STRU stCmdTblEntry = {0};
    VOS_UINT16                   usCmdNum      = 1;
    g_stCmdTblList.next = &g_stCmdTblList;
    g_stCmdTblList.prev = &g_stCmdTblList;

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    MOCKER(At_HeapAllocD)
        .expects(exactly(1))
        .will(returnValue((void *)NULL));
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    ulRet = 0;
    ulRet = AT_RegisterCmdTable(&stCmdTblEntry,usCmdNum);

    EXPECT_EQ(ulRet, ERR_MSP_MALLOC_FAILUE);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_AT_ClacCmdProc
功能描述 : AT_ClacCmdProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_ClacCmdProc_001
测试用例标题      : 输出所有命令
预期结果          : 输出所有命令成功
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ClacCmdProc, Test_AT_ClacCmdProc_001)
{
    //打印函数 无法测试

    g_stCmdTblList.next=&g_stCmdTblList;
    g_stCmdTblList.prev=&g_stCmdTblList;
    AT_ClacCmdProc();
}

/*****************************************************************************
类名 : Test_BlockCmdCheck
功能描述 : BlockCmdCheck UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_BlockCmdCheck_001
测试用例标题      : 检查有命令处于阻塞状态
预期结果          : 返回阻塞命令所在g_stParseContext[]索引
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_BlockCmdCheck_002
测试用例标题      : 没有命令处于阻塞状态
预期结果          : 返回AT_MAX_CLIENT_NUM
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_ClearBlockCmdInfo
功能描述 : ClearBlockCmdInfo UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ClearBlockCmdInfo_001
测试用例标题      : 清空被阻塞命令信息
预期结果          : 清空g_stParseContext[i]成功
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_ClearBlockCmdInfo, Test_ClearBlockCmdInfo_001)
{
    VOS_UINT8 ucIndex = 0;

    g_stParseContext[0].pBlockCmd     = (VOS_UINT8*)AT_MALLOC(10);
    g_stParseContext[0].usBlockCmdLen = 10;

    AT_ClearBlockCmdInfo(ucIndex);

    EXPECT_EQ(g_stParseContext[0].usBlockCmdLen,0);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_CheckProcBlockCmd
功能描述 : CheckProcBlockCmd UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_CheckProcBlockCmd_001
测试用例标题      : 检查阻塞命令并处理,第一个解析上下文存在阻塞命令
预期结果          : 第一个解析上下文中的阻塞命令被处理
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_AT_ParseCmdOver
功能描述 : AT_ParseCmdOver UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_ParseCmdOver_001
测试用例标题      : 检查阻塞命令并处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ParseCmdOver, Test_AT_ParseCmdOver_001)
{
    AT_ParseCmdOver(0);

}

/*****************************************************************************
类名 : Test_AT_BlockCmdTimeOutProc
功能描述 : AT_BlockCmdTimeOutProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_BlockCmdTimeOutProc_001
测试用例标题      : 缓存命令超时处理函数，0号客户端缓存命令超时，
预期结果          : 清除0号解析上下文中的阻塞命令
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_PendClientProc
功能描述 : PendClientProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_PendClientProc_001
测试用例标题      : PEND客户端处理，0号客户端处于PEND状态，执行STOP或ATH命令
预期结果          : 客户端被置为READY状态
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_HoldBlockCmd
功能描述 : HoldBlockCmd UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_HoldBlockCmd_001
测试用例标题      : 保存阻塞命令字符串，0号客户端保存阻塞命令
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_ParseCmdIsComb
功能描述 : ParseCmdIsComb UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ParseCmdIsComb_001
测试用例标题      : 0号客户端发送AT命令，当前没有其他客户端处理组合命令
预期结果          : 返回ERR_MSP_SUCCESS
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ParseCmdIsComb_002
测试用例标题      : 1号客户端发送AT命令，0客户端正在处理组合命令
预期结果          : 返回ERR_MSP_FAILURE,并且1号客户端缓存命令
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_atParseCmdIsPend
功能描述 : atParseCmdIsPend UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atParseCmdIsPend_001
测试用例标题      : 判断是否有正在处理的通道，有的话丢弃或缓存
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atParseCmdIsPend_002
测试用例标题      : 本通道和遍历到的通道均为APP通道
预期结果          : 返回ERR_MSP_SUCCESS
修改历史      :
 1.日    期   : 2012年12月6日
   作    者   : l00227485
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_AT_DiscardInvalidCharForSms
功能描述 : AT_DiscardInvalidCharForSms UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_DiscardInvalidCharForSms_001
测试用例标题      : +CMGS,+CMGW,+CMGC命令的检查和特殊处理，输入参数字符串为"AT+CMGS=<CR><LF>"
预期结果          : 字符串长度减1
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_atDiscardInvalidCharForSms, Test_atDiscardInvalidCharForSms_001)
{
    VOS_UINT8*pData = (VOS_UINT8*)"AT+CMGS=\r\n";
    VOS_UINT16 usLen   = 10;

    AT_DiscardInvalidCharForSms(pData, &usLen);

    EXPECT_EQ(usLen,9);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_AT_DiscardInvalidCharForSms_002
测试用例标题      : +CMGS,+CMGW,+CMGC命令的检查和特殊处理，输入参数字符串为"AT+CMGS=<CR><LF><CR>"
预期结果          : 字符串长度减2
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_atDiscardInvalidCharForSms, Test_atDiscardInvalidCharForSms_002)
{
    VOS_UINT8*pData = (VOS_UINT8*)"AT+CMGS=\r\n\r\n";
    VOS_UINT16 usLen   = 11;

    AT_DiscardInvalidCharForSms(pData, &usLen);

    EXPECT_EQ(usLen,9);

    GlobalMockObject::verify();

}


/*****************************************************************************
类名 : Test_atResetParseVariable
功能描述 : atResetParseVariable UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atResetParseVariable_001
测试用例标题      : 重新初始化解析用全局变量
预期结果          : 解析全局变量被重置
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_atResetParseVariable, Test_atResetParseVariable_001)
{
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;
    g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;

    AT_ResetParseVariable();

    EXPECT_EQ(g_stATParseCmd.ucCmdOptType,AT_CMD_OPT_BUTT);
    EXPECT_EQ(g_stATParseCmd.ucCmdFmtType,AT_CMD_TYPE_BUTT);

    GlobalMockObject::verify();

}

/*****************************************************************************
类名 : Test_ParseCmdType
功能描述 : ParseCmdType UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ParseCmdType_001
测试用例标题      : 根据命令类型解析命令字符串，输入命令AT
预期结果          : 返回AT_OK
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ParseCmdType_002
测试用例标题      : 根据命令类型解析命令字符串，输入错误命令BT
预期结果          : 返回AT_ERROR
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_ParseCmdType, Test_ParseCmdType_002)
{
    VOS_UINT8* pData =(VOS_UINT8*) "BT";
    VOS_UINT16   usLen = 2;
    VOS_UINT32   ulRet = ERR_MSP_SUCCESS;

    ulRet = AT_ParseCmdType(pData, usLen);

    EXPECT_EQ(ulRet,AT_ERROR);

    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ParseCmdType_003
测试用例标题      : 根据命令类型解析命令字符串，输入扩展命令AT+CGDCONT?
预期结果          : 返回AT_SUCCESS，解析全局变量中保存了AT+CGDCONT?命令
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_atMatchCmdName
功能描述 : ParseCmdType UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atMatchCmdName_001
测试用例标题      : 匹配命令名称，为客户端0匹配命令at+ccc
预期结果          : 返回失败，不支持该命令
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_ParseParam
功能描述 : ParseParam UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ParseParam_001
测试用例标题      : 解析参数，解析的AT命令为AT+CGDSCONT=5,0
预期结果          : 返回解析成功，并在全局变量g_stATParseCmd中保存解析结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ParseParam_002
测试用例标题      : 解析参数，解析的AT命令为AT+CGDSCONT=33,0
预期结果          : 返回参数错误
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_fwCmdTestProc
功能描述 : fwCmdTestProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_fwCmdTestProc_001
测试用例标题      : AT命令测试函数执行，执行AT+CGDSCONT命令的测试函数
预期结果          : 返回AT_OK，保存"+CGDSCONT: (1-11),(1-11),(0-2),(0-3)"在pgucAtSndCodeAddr中
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_atCmdDispatch
功能描述 : atCmdDispatch UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atCmdDispatch_001
测试用例标题      : 分发AT命令，客户端0发送了AT+CGDSCONT=?
预期结果          : 返回AT_OK
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atCmdDispatch_002
测试用例标题      : 分发AT命令，客户端0发送设置、查询或者测试命令
                    记录该条记录成功后的时间。
预期结果          : 记录AT命令的TICK值
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atCmdDispatch_003
测试用例标题      : 分发AT命令，客户端0发送设置、查询或者测试命令
                    记录该条记录成功后的时间。
预期结果          : 记录AT命令的TICK值
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_LimitedCmdProc
功能描述 : LimitedCmdProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_LimitedCmdProc_001
测试用例标题      : 命令受限查询和处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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
/*******************************************************************
测试用例编号      : Test_LimitedCmdProc_002
测试用例标题      : 命令受限查询和处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_DockCmdProc
功能描述 : DockCmdProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_DockCmdProc_001
测试用例标题      : DOCK命令解析的特殊处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_DockCmdProc, Test_DockCmdProc_001)
{

}

/*****************************************************************************
类名 : Test_CmdParseProc
功能描述 : CmdParseProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_CmdParseProc_001
测试用例标题      : 命令解析处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_RepeatCmdProc
功能描述 : RepeatCmdProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_RepeatCmdProc_001
测试用例标题      : A/命令的处理,pucCmdLine中命令为"AT+CGDCONT"
预期结果          : 在aucDataBuff中保存"AT+CGDCONT"
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_RepeatCmdProc_002
测试用例标题      : A/命令的处理,pucCmdLine中没有命令
预期结果          : 在aucDataBuff中保存"AT\n"
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_RepeatCmdProc, Test_RepeatCmdProc_002)
{
    //g_stParseContext[0].aucDataBuff  = "A/";
    g_stParseContext[0].usDataLen    = 3;
    g_stParseContext[0].usCmdLineLen = 0;

    RepeatCmdProc(&g_stParseContext[0]);

    //    EXPECT_STREQ(g_stParseContext[0].aucDataBuff,"AT\n");

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_SaveRepeatCmd
功能描述 : SaveRepeatCmd UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_SaveRepeatCmd_001
测试用例标题      : 保存当前命令字符串
预期结果          : 保存字符串到解析上下文中
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_ScanDelChar
功能描述 : ScanDelChar UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ScanDelChar_001
测试用例标题      : 扫描退格符
预期结果          : 返回AT_SUCCESS,去掉字符串里面的退格符连同前面的一个字符
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_ScanCtlChar
功能描述 : ScanCtlChar UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ScanCtlChar_001
测试用例标题      : 扫描控制符(去除字符串中小于0x20的字符)，扫描字符串"at+cgdcont12",12代表ASCII为12的字符
预期结果          : 返回AT+SUCCESS，字符串变为"at+cgdcont"
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_ScanBlankChar
功能描述 : ScanBlankChar UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_ScanBlankChar_001
测试用例标题      : 扫描引号外空格符，扫描字符串"at+cgdcon t"
预期结果          : 返回AT_SUCCESS，字符串变为"at+cgdcont"
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_FormatCmdStr
功能描述 : FormatCmdStr UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_FormatCmdStr_001
测试用例标题      : 格式化命令字符串,"at+cgdcont13cgd"
预期结果          : 返回AT_SUCCESS,保留"at+cgdcont"
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_CmdStringFormat
功能描述 : CmdStringFormat UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_CmdStringFormat_001
测试用例标题      : 格式化命令字符串"at+cg12dc oo8nt13cgd"
预期结果          : 返回ERR_MSP_SUCCESS,"at+cgdcont"
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_atCmdMsgProc
功能描述 : atCmdMsgProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atCmdMsgProc_001
测试用例标题      : 命令处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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
/*******************************************************************
测试用例编号      : Test_atCmdMsgProc_002
测试用例标题      : 当前子模式为AT_XML_MODE,XML码流总长度超出AT_XML_MAX_LEN
预期结果          : 返回处理结果 AT_WAIT_XML_INPUT
修改历史     :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atCmdMsgProc_003
测试用例标题      : 当前子模式为AT_XML_MODE,以输入结束字符"ctrl-Z"
预期结果          : 返回处理结果 当前AT通道状态置为AT_FW_CLIENT_STATUS_PEND
修改历史     :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atCmdMsgProc_004
测试用例标题      : 当前子模式为AT_XML_MODE,收到"ESC"字符
预期结果          : 返回错误码 AT_CMS_INVALID_TEXT_MODE_PARAMETER
修改历史     :
1.日    期   : 2012年07月03日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*******************************************************************/
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
/*****************************************************************************
类名 : Test_At_CmdMsgDistr
功能描述 : At_CmdMsgDistr UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_001
测试用例标题      : AT命令字符串的预处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_002
测试用例标题      : 收到ID_HIFI_AT_RESET_END_IND
预期结果          : 上报^RESET:2
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_003
测试用例标题      : 处于C核复位过程中收到正常的AT命令消息
预期结果          : 不处理AT命令消息
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
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
/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_004
测试用例标题      : 接收到来自ＡＴ的回放数据
预期结果          : 处理AT的回放命令消息
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_005
测试用例标题      : 收到HIFI复位结束消息
预期结果          : 不处理AT命令消息
修改历史   :
1.日   期  : 2013-07-05
  作   者  : L47619
  修改内容 : add for HIFI Reset End Report
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_006
测试用例标题      : clientID错误
预期结果          : 直接返回
修改历史   :
1.日   期  : 2013-10-16
  作   者  : z00189113
  修改内容 : 新增 case
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_007
测试用例标题      : 非UART口收到 AT_SWITCH_CMD_MODE_MSG
预期结果          : 直接返回
修改历史   :
1.日   期  : 2013-10-16
  作   者  : z00189113
  修改内容 : 新增 case

*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_008
测试用例标题      : HSUART口收到 AT_SWITCH_CMD_MODE_MSG
预期结果          : 可维可测收到+++次数加1
修改历史   :
1.日   期  : 2013-10-16
  作   者  : z00189113
  修改内容 : 新增CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_009
测试用例标题      : 命令模式HSUART口收到 AT_SWITCH_CMD_MODE_MSG
预期结果          : 端口依然为命令模式
修改历史   :
1.日   期  : 2013-10-16
  作   者  : z00189113
  修改内容 : 新增 case

*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_010
测试用例标题      : 数据模式为PPP模式
预期结果          : 切换到online_command模式
修改历史   :
1.日   期  : 2013-10-16
  作   者  : z00189113
  修改内容 : 新增 case

*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_011
测试用例标题      : 数据模式为IP模式
预期结果          : 切换到online_command模式
修改历史   :
1.日   期  : 2013-10-16
  作   者  : z00189113
  修改内容 : 新增 case

*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdMsgDistr_012
测试用例标题      :
预期结果          : 切换到online_command模式
修改历史   :
1.日   期  : 2013-10-16
  作   者  : z00189113
  修改内容 : 新增 case

*******************************************************************/
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



/*****************************************************************************
类名 : Test_atfwParseSaveParam
功能描述 : atfwParseSaveParam UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atfwParseSaveParam_001
测试用例标题      : 解析字符串并保存参数到全局变量，参数字符串"15"，长度为2，全局变量gucAtParaIndex为0
预期结果          : 返回ERR_MSP_SUCCESS，gastAtParaList中保存了参数以及长度
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atfwParseSaveParam_002
测试用例标题      : 解析字符串并保存参数到全局变量，参数字符串为空，长度为0，全局变量gucAtParaIndex为0
预期结果          : 返回ERR_MSP_SUCCESS，gastAtParaList中长度为0
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_atfwParseSaveParam_003
测试用例标题      : 解析字符串并保存参数到全局变量，参数字符串为空，长度为4，全局变量gucAtParaIndex为0
预期结果          : 返回ERR_MSP_FAILURE
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_AT_FwSendClientMsg
功能描述 : AT_FwSendClientMsg UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_FwSendClientMsg_001
测试用例标题      : 二进制消息回复处理接口
预期结果          : 返回ERR_MSP_SUCCESS，gastAtParaList中保存了参数以及长度
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_At_CmdTestProcERROR
功能描述 : At_CmdTestProcERROR UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdTestProcERROR_001
测试用例标题      : 命令的测试模式下返回ERROR的处理函数
预期结果          : 返回AT_ERROR
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_CmdTestProcERROR, Test_At_CmdTestProcERROR_001)
{
    VOS_UINT32 ulRet=1;
    ulRet = At_CmdTestProcERROR(0);
    EXPECT_EQ(ulRet,AT_ERROR);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_At_At_CmdTestProcOK
功能描述 : At_At_CmdTestProcOK UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdTestProcOK_001
测试用例标题      : 命令的测试模式下返回AT_OK的处理函数
预期结果          : 返回AT_OK
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_CmdTestProcOK, Test_At_CmdTestProcOK_001)
{
    VOS_UINT32 ulRet=1;
    ulRet = At_CmdTestProcOK(0);
    EXPECT_EQ(ulRet,AT_OK);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_At_CmdStreamRcv
功能描述 : At_CmdStreamRcv UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_CmdStreamRcv_001
测试用例标题      : 二进制消息回复处理接口
预期结果          : 返回ERR_MSP_SUCCESS，gastAtParaList中保存了参数以及长度
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_At_ReadyClientCmdProc
功能描述 : At_ReadyClientCmdProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_ReadyClientCmdProc_001
测试用例标题      : 二进制消息回复处理接口
预期结果          : 返回ERR_MSP_SUCCESS，gastAtParaList中保存了参数以及长度
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_At_ReadyClientCmdProc_002
测试用例标题      : AT^FACAUTHPUBKEY命令特殊处理
预期结果          : 函数不调用通用AT命令处理流程
修改历史          :
1.日   期  : 2012-04-21
  作   者  : L47619
  修改内容 : 新建CASE
*******************************************************************/
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

/*****************************************************************************
类名 : Test_AT_IsAbortCmdStr
功能描述 : AT_IsAbortCmdStr UT工程类
修改历史     :
1.日   期  : 2012年09月25日
  作   者  : l00171473
  修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_001
测试用例标题      : 获取打断命令的参数为空
预期结果          : 返回FALSE
修改历史      :
1.日    期   : 2012年09月25日
  作    者   : l00171473
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_002
测试用例标题      : 未使能打断命令功能
预期结果          : 返回FALSE
修改历史      :
1.日    期   : 2012年09月25日
  作    者   : l00171473
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_003
测试用例标题      : 长度判断失败
预期结果          : 返回FALSE
修改历史      :
1.日    期   : 2012年09月25日
  作    者   : l00171473
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_004
测试用例标题      : 长度判断失败
预期结果          : 返回FALSE
修改历史      :
1.日    期   : 2012年09月25日
  作    者   : l00171473
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_005
测试用例标题      : 内容比较通过
预期结果          : 返回TRUE
修改历史      :
1.日    期   : 2012年09月25日
  作    者   : l00171473
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_006
测试用例标题      : 内容比较失败
预期结果          : 返回FALE
修改历史      :
1.日    期   : 2012年09月25日
  作    者   : l00171473
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_007
测试用例标题      : 设置时间与打断字符时间间隔差125ms以内
预期结果          : 返回FALSE
修改历史      :
1.日    期   : 2013年10月29日
  作    者   : w00242748
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_008
测试用例标题      : 设置时间与打断字符时间间隔差超过125ms,但未设置
                    任意字符打断
预期结果          : 返回FALSE
修改历史      :
1.日    期   : 2013年10月29日
  作    者   : w00242748
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_009
测试用例标题      : 设置时间与打断字符时间间隔差超过125ms,且设置
                    任意字符打断
预期结果          : 返回FALSE
修改历史      :
1.日    期   : 2013年10月29日
  作    者   : w00242748
  修改内容   : 新建CASE,
*******************************************************************/
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

/*******************************************************************
测试用例编号      : Test_AT_IsAbortCmdStr_010
测试用例标题      : 设置时间与打断字符时间发生翻转
预期结果          : 返回FALSE
修改历史      :
1.日    期   : 2013年10月29日
  作    者   : w00242748
  修改内容   : 新建CASE,
*******************************************************************/
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

/*****************************************************************************
类名     : Test_AT_AbortCmdProc
功能描述 : AT_AbortCmdProc UT工程类
修改历史 :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*****************************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_AbortCmdProc_001
测试用例标题  : 进入列表搜的打断处理, 返回异步
预期结果      : 当前操作类型更新为列表搜打断处理
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目

2.日    期   : 2013年11月1日
  作    者   : w00167002
  修改内容   : NETSCAN:增加了125ms打断限制，调整原有用例；
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_AbortCmdProc_002
测试用例标题  : 进入列表搜的打断处理, 返回异步, 打断保护时长为0
预期结果      : 当前操作类型更新为列表搜打断处理
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
2.日    期   : 2013年11月1日
  作    者   : w00167002
  修改内容   : NETSCAN:增加了125ms打断限制，调整原有用例；
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_AbortCmdProc_003
测试用例标题  : 进入列表搜的打断处理, 返回异步, 启动打断保护定时器失败
预期结果      : 当前操作类型更新为列表搜打断处理
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
2.日    期   : 2013年11月1日
  作    者   : w00167002
  修改内容   : NETSCAN:增加了125ms打断限制，调整原有用例；
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_AbortCmdProc_004
测试用例标题  : 进入列表搜的打断处理, 返回AT_ABORT
预期结果      : 返回打断结果"ABORT"
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
2.日    期   : 2013年11月1日
  作    者   : w00167002
  修改内容   : NETSCAN:增加了125ms打断限制，调整原有用例；
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_AbortCmdProc_005
测试用例标题  : 进入列表搜的打断处理, 返回AT_FAILURE
预期结果      : 当前操作类型不更新, 仍为列表搜
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_AbortCmdProc_006
测试用例标题  : pstCmdElement空指针
预期结果      : 直接返回
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
TEST_F(Test_AT_AbortCmdProc, Test_AT_AbortCmdProc_006)
{
    g_stParseContext[0].pstCmdElement = VOS_NULL_PTR;

    AT_AbortCmdProc(0);
}

/*******************************************************************
测试用例编号  : Test_AT_AbortCmdProc_007
测试用例标题  : pstCmdElement->pfnAbortProc空指针
预期结果      : 直接返回
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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

/*****************************************************************************
类名     : Test_AT_SaveCmdElementInfo
功能描述 : AT_SaveCmdElementInfo UT工程类
修改历史 :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*****************************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_SaveCmdElementInfo_001
测试用例标题  : 输入参数为空
预期结果      : 不更新全局变量
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_SaveCmdElementInfo_002
测试用例标题  : 从命令表中查找指定命令失败
预期结果      : 不更新全局变量
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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
/*******************************************************************
测试用例编号  : Test_AT_SaveCmdElementInfo_003
测试用例标题  : 输入命令表类型不支持
预期结果      : 不更新全局变量
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_SaveCmdElementInfo_004
测试用例标题  : 特殊命令^SIMLOCK的处理
预期结果      : 更新全局变量
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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
/*******************************************************************
测试用例编号  : Test_AT_SaveCmdElementInfo_005
测试用例标题  : 特殊命令^SIMLOCK的处理, 命令表中存在元素异常的命令
预期结果      : 更新全局变量, 比较时跳过异常命令
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_SaveCmdElementInfo_006
测试用例标题  : 特殊命令^FACAUTHPUBKEY的处理,
预期结果      : 更新全局变量,
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_SaveCmdElementInfo_007
测试用例标题  : 特殊命令^DOCK的处理,
预期结果      : 更新全局变量,
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_SaveCmdElementInfo_009
测试用例标题  : 特殊命令^SIMLOCKDATAWRITE的处理,
预期结果      : 更新全局变量,
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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


/*****************************************************************************
类名     : Test_At_MatchSmsCmdName
功能描述 : At_MatchSmsCmdName UT工程类
修改历史 :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*****************************************************************************/
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

/*******************************************************************
测试用例编号  : Test_At_MatchSmsCmdName_001
测试用例标题  : 特殊命令^SIMLOCKDATAWRITE的处理,
预期结果      : 更新全局变量,
修改历史      :
1.日    期    : 2012年09月26日
  作    者    : l00171473
  修改内容    : V7R1C50_At_Abort, AT打断项目
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_At_MatchSmsCmdName_002
测试用例标题  : g_enAtCmgfMsgFormat设置为文本方式
预期结果      : 参数有效值范围从gastAtSmsCmdTab[i].ParaText中获取
修改历史      :
1.日    期    : 2012年11月20日
  作    者    : f62575
  修改内容    : DTS2012110604700, 解决短信命令支持多通道并发命令名被覆盖问题；
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_At_MatchSmsCmdName_003
测试用例标题  : g_enAtCmgfMsgFormat设置为PDU
预期结果      : 参数有效值范围从gastAtSmsCmdTab[i].ParaPDU中获取
修改历史      :
1.日    期    : 2012年11月20日
  作    者    : f62575
  修改内容    : DTS2012110604700, 解决短信命令支持多通道并发命令名被覆盖问题；
*******************************************************************/
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

/*****************************************************************************
类名 : Test_AT_IsAnyParseClientPend
功能描述 : AT_IsAnyParseClientPend UT工程类
修改历史     :
1.日   期  : 2014年01月07日
作   者  : j00174725
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_IsAnyParseClientPend_001
测试用例标题  : 端口状态判断
预期结果      :当前有商品处于pend状态，函数返回TRUE
修改历史      :
1.日   期  : 2014年01月07日
作   者  : j00174725
修改内容 : 新生成类
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_IsAnyParseClientPend_002
测试用例标题  : 端口状态判断
预期结果      :当前没有商品处于pend状态，函数返回FALSE
修改历史      :
1.日   期  : 2014年01月07日
作   者  : j00174725
修改内容 : 新生成类
*******************************************************************/
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

/*****************************************************************************
类名 : Test_AT_IsAllClientDataMode
功能描述 : AT_IsAllClientDataMode UT工程类
修改历史     :
1.日   期  : 2014年01月07日
作   者  : j00174725
修改内容 : 新生成类
*****************************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_IsAllClientDataMode_001
测试用例标题  : 所有端口处于CMD状态
预期结果      : 函数返回 VOS_FALSE
修改历史      :
1.日   期  : 2014年01月07日
作   者  : j00174725
修改内容 : 新生成类
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_IsAllClientDataMode_002
测试用例标题  : 所有端口处于data模式
预期结果      : 函数返回 TRUE
修改历史      :
1.日   期  : 2014年01月07日
作   者  : j00174725
修改内容 : 新生成类
*******************************************************************/
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

/*******************************************************************
测试用例编号  : Test_AT_IsAllClientDataMode_003
测试用例标题  : 部分端口处于data状态
预期结果      : 函数返回 False
修改历史      :
1.日   期  : 2014年01月07日
作   者  : j00174725
修改内容 : 新生成类
*******************************************************************/
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
