#include "gtest/gtest.h"
#include "llt_mockcpp.h"


#include "uttest_AtCombinecmd.h"


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
类名 : Test_GetSecondAddr
功能描述 : GetSecondAddr UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_GetSecondAddr: public ::testing::Test
{
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
测试用例编号      : Test_GetSecondAddr_001
被测函数功能描述  : 从pData 的usLen范围内 找到第二个匹配的命令，将字符串首地址存储在参数3中，返回查找结果
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_GetSecondAddr, Test_GetSecondAddr_001)
{
    VOS_UINT32 ulRet=0;
    VOS_UINT8 *pData=NULL;
    VOS_UINT16 usLen=0;
    VOS_UINT8 ctmp='a';
    VOS_UINT8 * pctmp=&ctmp;
    VOS_UINT8** ppDataOut=&pctmp;

    ulRet=0;
    pData = (VOS_UINT8*)"c64416";
    usLen = 5;
    ulRet = At_GetSecondAddr(pData,usLen, ppDataOut);
    EXPECT_EQ(ulRet,ERR_MSP_FAILURE);

    ulRet = 1;
    pData = (VOS_UINT8*)&"wwD123j456";
    usLen = 10;
    ulRet = At_GetSecondAddr(pData, usLen, ppDataOut);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ((VOS_UINT_PTR)(*ppDataOut),(VOS_UINT_PTR)(pData+10));

    ulRet = 1;
    pData = (VOS_UINT8*)&"wwD123*E456";
    usLen = 10;
    ulRet = At_GetSecondAddr(pData, usLen, ppDataOut);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ((VOS_UINT_PTR)*ppDataOut,(VOS_UINT_PTR)(pData+7));

}

/*****************************************************************************
类名 : Test_GetFirstCmdLen
功能描述 : GetFirstCmdLen UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_GetFirstCmdLen: public ::testing::Test
{
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
测试用例编号      : Test_GetFirstCmdLen_001
被测函数功能描述  : 获取第一个命令的长度
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_GetFirstCmdLen, Test_GetFirstCmdLen_001)
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT8 *pData = NULL;
    VOS_UINT16 usLen = 0;

    ulRet = 0;
    pData = (VOS_UINT8*)"c64416";
    usLen = 5;
    ulRet = At_GetFirstCmdLen(pData, usLen);
    EXPECT_EQ(ulRet,5);

    ulRet = 0;
    pData = (VOS_UINT8*)"c64416";
    usLen = 3;
    ulRet = At_GetFirstCmdLen(pData, usLen);
    EXPECT_EQ(ulRet,3);

    ulRet = 0;
    pData = (VOS_UINT8*)"wwE123**V456";
    usLen = 12;
    ulRet = At_GetFirstCmdLen(pData, usLen);
    EXPECT_EQ(ulRet,8);

    ulRet = 0;
    pData = (VOS_UINT8*)"wwE123***456";
    usLen = 12;
    ulRet = At_GetFirstCmdLen(pData, usLen);
    EXPECT_EQ(ulRet,12);

    ulRet = 0;
    pData = (VOS_UINT8*)"ww1123***456";
    usLen = 12;
    ulRet = At_GetFirstCmdLen(pData, usLen);
    EXPECT_EQ(ulRet,12);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_AT_ResetCombinCmdInfo
功能描述 : AT_ResetCombinCmdInfo UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_ResetCombinCmdInfo: public ::testing::Test
{
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
测试用例编号      : Test_AT_ResetCombinCmdInfo_001
被测函数功能描述  : 重置AT组合命令解析的信息
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_AT_ResetCombinCmdInfo, Test_AT_ResetCombinCmdInfo_001)
{
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo={0};
    AT_FW_COMBINE_CMD_NODE_STRU *pstCombineCmdNode = NULL;
    AT_FW_COMBINE_CMD_STRU * pstCombCmd=NULL;
    pstCombCmd = (AT_FW_COMBINE_CMD_STRU*)malloc(sizeof(AT_FW_COMBINE_CMD_STRU));
    pstCombineCmdNode = (AT_FW_COMBINE_CMD_NODE_STRU *)malloc(sizeof(AT_FW_COMBINE_CMD_NODE_STRU));
    if(pstCombCmd != NULL && pstCombineCmdNode != NULL)
    {
        pstCombineCmdNode->pstCombCmd=pstCombCmd;
        //pstCombineCmdNode->stCombCmdList.
        pstCombineCmdNode->stCombCmdList.next=&stCombineCmdInfo.stCombineCmdList;
        pstCombineCmdNode->stCombCmdList.prev=&stCombineCmdInfo.stCombineCmdList;


        stCombineCmdInfo.usTotalNum=3;
        stCombineCmdInfo.usProcNum=4;
        stCombineCmdInfo.stCombineCmdList.next=&pstCombineCmdNode->stCombCmdList;
        stCombineCmdInfo.stCombineCmdList.prev=&pstCombineCmdNode->stCombCmdList;


        At_ResetCombinCmdInfo(&stCombineCmdInfo.stCombineCmdList);

        EXPECT_EQ(stCombineCmdInfo.usTotalNum,0);
        EXPECT_EQ(stCombineCmdInfo.usProcNum,0);
        // 函数把 pstCombList 里的非NULL的项全部删除并free了
    }
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_AT_ResetCombinCmdInfo_002
被测函数功能描述  : 重置AT组合命令解析的信息
预期结果          : 返回处理结果
修改历史      :
1.日    期   : 2011年12月25日
  作    者   : 黎客来/00130025
  修改内容   : 问题单DTS2011120703681，组合命令解析使用空指针导致单板复位
*******************************************************************/
TEST_F(Test_AT_ResetCombinCmdInfo, Test_AT_ResetCombinCmdInfo_002)
{
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo={0};


    // 执行检查
    At_ResetCombinCmdInfo(&stCombineCmdInfo.stCombineCmdList);


    GlobalMockObject::verify();

}


/*****************************************************************************
类名 : Test_At_ResetCombinParseInfo
功能描述 : At_ResetCombinParseInfo UT工程类
修改历史     :
  1.日    期   : 2011年12月25日
    作    者   : 黎客来/00130025
    修改内容   : 问题单DTS2011120703681，组合命令解析使用空指针导致单板复位
*****************************************************************************/
class Test_At_ResetCombinParseInfo: public ::testing::Test
{
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
测试用例编号      : Test_At_ResetCombinParseInfo_001
被测函数功能描述  : 重置AT组合命令解析的信息
预期结果          : 返回处理结果
修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : 黎客来/00130025
    修改内容   : 问题单DTS2011120703681，组合命令解析使用空指针导致单板复位
*******************************************************************/
TEST_F(Test_At_ResetCombinParseInfo, Test_At_ResetCombinParseInfo_001)
{
    MOCKER(At_ResetCombinCmdInfo)
             .expects(never());
    // 执行检查
    At_ResetCombinParseInfo(AT_MAX_CLIENT_NUM);

    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_At_ResetCombinParseInfo_002
被测函数功能描述  : 重置AT组合命令解析的信息
预期结果          : 返回处理结果
修改历史      :
1.日    期   : 2011年12月25日
  作    者   : 黎客来/00130025
  修改内容   : 问题单DTS2011120703681，组合命令解析使用空指针导致单板复位
*******************************************************************/
TEST_F(Test_At_ResetCombinParseInfo, Test_At_ResetCombinParseInfo_002)
{
   PS_MEM_SET(&g_stParseContext, 0x00, sizeof(g_stParseContext)),

    MOCKER(At_ResetCombinCmdInfo)
             .expects(exactly(1));
    // 执行检查
    At_ResetCombinParseInfo(0);


    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_At_ResetCombinParseInfo_003
被测函数功能描述  : 重置AT组合命令解析的信息
预期结果          : 返回处理结果
修改历史      :
1.日    期   : 2011年12月25日
  作    者   : 黎客来/00130025
  修改内容   : 问题单DTS2011120703681，组合命令解析使用空指针导致单板复位
*******************************************************************/
TEST_F(Test_At_ResetCombinParseInfo, Test_At_ResetCombinParseInfo_003)
{
   PS_MEM_SET(&g_stParseContext, 0xFF, sizeof(g_stParseContext)),

    MOCKER(At_ResetCombinCmdInfo)
             .expects(exactly(1));
    // 执行检查
    At_ResetCombinParseInfo(0);


    GlobalMockObject::verify();

}
#if 0
/*****************************************************************************
类名 : Test_atfwPrintCombinCmd
功能描述 : atfwPrintCombinCmd UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_atfwPrintCombinCmd: public ::testing::Test
{
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
测试用例编号      : Test_atfwPrintCombinCmd_001
被测函数功能描述  : 打印解析出的组合命令信息，调试用
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_atfwPrintCombinCmd, Test_atfwPrintCombinCmd_001)
{

}

/*****************************************************************************
类名 : Test_StoreSubCombCmd
功能描述 : StoreSubCombCmd UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_StoreSubCombCmd: public ::testing::Test
{
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
测试用例编号      : Test_StoreSubCombCmd_001
被测函数功能描述  : 存储命令于链表中
预期结果          : ERR_MSP_MALLOC_FAILUE
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_StoreSubCombCmd, Test_StoreSubCombCmd_001)
{
    AT_FW_COMBINE_CMD_NODE_STRU* pstCombCmdNode = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo={0};
    stCombineCmdInfo.usTotalNum=3;
    stCombineCmdInfo.usProcNum=2;
    stCombineCmdInfo.stCombineCmdList.next=&stCombineCmdInfo.stCombineCmdList;
    stCombineCmdInfo.stCombineCmdList.prev=&stCombineCmdInfo.stCombineCmdList;

    VOS_UINT8 *pDataIn = (VOS_UINT8*)"12345";
    VOS_UINT16 usLenIn = 6;
    VOS_UINT32 ulRet = 1;

    //MOCKER(OSA_HeapAllocD).will(returnValue(NULL));
    EXPECT_EQ((int)stCombineCmdInfo.stCombineCmdList.prev,(int)(&stCombineCmdInfo.stCombineCmdList));
    EXPECT_EQ((int)stCombineCmdInfo.stCombineCmdList.prev,(int)stCombineCmdInfo.stCombineCmdList.next);

    ulRet = At_StoreSubCombCmd( &stCombineCmdInfo.stCombineCmdList, pDataIn, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ(stCombineCmdInfo.usTotalNum,4);
    EXPECT_NE((int)stCombineCmdInfo.stCombineCmdList.prev,(int)(&stCombineCmdInfo.stCombineCmdList));
    EXPECT_EQ((int)stCombineCmdInfo.stCombineCmdList.prev,(int)stCombineCmdInfo.stCombineCmdList.next);
    pstCombCmdNode=msp_list_entry(stCombineCmdInfo.stCombineCmdList.prev, AT_FW_COMBINE_CMD_NODE_STRU, stCombineCmdInfo.stCombineCmdList.next);
    EXPECT_EQ(pstCombCmdNode->pstCombCmd->ulLen,8);

    pDataIn = (VOS_UINT8*)"maxwell";
    usLenIn = 8;
    ulRet = 1;
    ulRet = At_StoreSubCombCmd( &stCombineCmdInfo.stCombineCmdList, pDataIn, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ(stCombineCmdInfo.usTotalNum,5);
    pstCombCmdNode=msp_list_entry(stCombineCmdInfo.stCombineCmdList.prev, AT_FW_COMBINE_CMD_NODE_STRU, stCombineCmdInfo.stCombineCmdList.next);
    EXPECT_EQ(pstCombCmdNode->pstCombCmd->ulLen,10);



}

/*****************************************************************************
类名 : Test_BasicCombineCmdParse
功能描述 : BasicCombineCmdParse UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_BasicCombineCmdParse: public ::testing::Test
{
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
测试用例编号      : Test_BasicCombineCmdParse_001
被测函数功能描述  : 基础组合命令解析
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_BasicCombineCmdParse, Test_BasicCombineCmdParse_001)
{
    //该函数在 pDataIn 的 usLenIn 长度的内容 中检索命令名存入pstCombList 中。
    AT_FW_COMBINE_CMD_NODE_STRU* pstCombCmdNode = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo={0};
    stCombineCmdInfo.usTotalNum=3;
    stCombineCmdInfo.usProcNum=2;
    stCombineCmdInfo.stCombineCmdList.next=&stCombineCmdInfo.stCombineCmdList;
    stCombineCmdInfo.stCombineCmdList.prev=&stCombineCmdInfo.stCombineCmdList;

    VOS_UINT8 *pDataIn = (VOS_UINT8*)"E123V45&F78";
    VOS_UINT16 usLenIn = 12;
    VOS_UINT32 ulRet = 1;

    ulRet = At_BasicCombineCmdParse(&stCombineCmdInfo.stCombineCmdList,pDataIn, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ(stCombineCmdInfo.usTotalNum,6);
    pstCombCmdNode=msp_list_entry(stCombineCmdInfo.stCombineCmdList.prev, AT_FW_COMBINE_CMD_NODE_STRU, stCombineCmdInfo.stCombineCmdList.next);
    EXPECT_EQ(pstCombCmdNode->pstCombCmd->ulLen,7);
    ulRet = 1;
    ulRet = strcmp("AT&F78",(char*)pstCombCmdNode->pstCombCmd->ucData);
    EXPECT_EQ(ulRet,0);


}
#endif
/*****************************************************************************
类名 : Test_BasicExCombineCmdParse
功能描述 : BasicExCombineCmdParse UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_BasicExCombineCmdParse: public ::testing::Test
{
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
测试用例编号      : Test_BasicExCombineCmdParse_001
被测函数功能描述  : 基础命令和扩展命令组合解析
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_BasicExCombineCmdParse, Test_BasicExCombineCmdParse_001)
{
    AT_FW_COMBINE_CMD_NODE_STRU* pstCombCmdNode = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo={0};
    stCombineCmdInfo.usTotalNum=3;
    stCombineCmdInfo.usProcNum=2;
    stCombineCmdInfo.stCombineCmdList.next=&stCombineCmdInfo.stCombineCmdList;
    stCombineCmdInfo.stCombineCmdList.prev=&stCombineCmdInfo.stCombineCmdList;

    VOS_UINT8 *pDataIn = (VOS_UINT8*)"E1234";
    VOS_UINT16 usLenIn = 5;
    VOS_UINT32 ulRet = 1;
    VOS_UINT16 usFirIndex=0;

    ulRet = At_BasicExCombineCmdParse(&stCombineCmdInfo.stCombineCmdList, pDataIn, usLenIn, usFirIndex);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ(stCombineCmdInfo.usTotalNum,4);

    pDataIn = (VOS_UINT8*)"E123^tmode";
    usLenIn = 11;
    ulRet = 1;
    usFirIndex=4;

    ulRet = At_BasicExCombineCmdParse(&stCombineCmdInfo.stCombineCmdList, pDataIn, usLenIn, usFirIndex);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);
    EXPECT_EQ(stCombineCmdInfo.usTotalNum,6);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_SemicolonCmdParse
功能描述 : SemicolonCmdParse UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_SemicolonCmdParse: public ::testing::Test
{
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
测试用例编号      : Test_SemicolonCmdParse_001
被测函数功能描述  : 每个;前的命令的解析
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_SemicolonCmdParse, Test_SemicolonCmdParse_001)
{
    AT_FW_COMBINE_CMD_NODE_STRU* pstCombCmdNode = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo={0};
    stCombineCmdInfo.usTotalNum=3;
    stCombineCmdInfo.usProcNum=2;
    stCombineCmdInfo.stCombineCmdList.next=&stCombineCmdInfo.stCombineCmdList;
    stCombineCmdInfo.stCombineCmdList.prev=&stCombineCmdInfo.stCombineCmdList;

    VOS_UINT8 *pDataIn = NULL;
    VOS_UINT16 usLenIn = 5;
    VOS_UINT32 ulRet = 0;
    ulRet = At_SemicolonCmdParse(&stCombineCmdInfo.stCombineCmdList, pDataIn, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_FAILURE);

    VOS_UINT8 pDataIn2[]="E12V34^tmode";
    usLenIn = 12;
    ulRet = 0;
    //MOCKER(At_BasicExCombineCmdParse).will(returnValue(ERR_MSP_SUCCESS));
    ulRet = At_SemicolonCmdParse(&stCombineCmdInfo.stCombineCmdList, pDataIn2, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    VOS_UINT8 pDataIn3[] = "E12V34^^tmode";
    usLenIn = 12;
    ulRet = 0;
    //MOCKER(At_BasicExCombineCmdParse).will(returnValue(ERR_MSP_SUCCESS));
    ulRet = At_SemicolonCmdParse(&stCombineCmdInfo.stCombineCmdList, pDataIn3, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_FAILURE);

    VOS_UINT8 pDataIn4[]="D;";
    usLenIn = 2;
    ulRet = 0;
    //MOCKER(At_BasicExCombineCmdParse).will(returnValue(ERR_MSP_SUCCESS));
    ulRet = At_SemicolonCmdParse(&stCombineCmdInfo.stCombineCmdList, pDataIn4, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    VOS_UINT8 pDataIn5[]="ATD+117;";
    usLenIn = 2;
    ulRet = 0;
    //MOCKER(At_BasicExCombineCmdParse).will(returnValue(ERR_MSP_SUCCESS));
    ulRet = At_SemicolonCmdParse(&stCombineCmdInfo.stCombineCmdList, pDataIn5, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_CombineCmdPreProc
功能描述 : CombineCmdPreProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_CombineCmdPreProc: public ::testing::Test
{
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
测试用例编号      : Test_CombineCmdPreProc_001
被测函数功能描述  : 组合命令的预处理,把命令拆分放入缓存中
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_CombineCmdPreProc, Test_CombineCmdPreProc_001)
{
    AT_FW_COMBINE_CMD_NODE_STRU* pstCombCmdNode = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo={0};
    stCombineCmdInfo.usTotalNum=3;
    stCombineCmdInfo.usProcNum=2;
    stCombineCmdInfo.stCombineCmdList.next=&stCombineCmdInfo.stCombineCmdList;
    stCombineCmdInfo.stCombineCmdList.prev=&stCombineCmdInfo.stCombineCmdList;

    VOS_UINT8 pDataIn[] = "^tmode;ftxon=3";
    VOS_UINT16 usLenIn = 14;
    VOS_UINT32 ulRet = 0;

    //MOCKER(At_SemicolonCmdParse).will(returnValue(ERR_MSP_SUCCESS));
    ulRet = At_CombineCmdPreProc(&stCombineCmdInfo.stCombineCmdList, pDataIn, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_CombineCmdProc
功能描述 : CombineCmdProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_CombineCmdProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};
#if 0
/*******************************************************************
测试用例编号      : Test_CombineCmdProc_001
被测函数功能描述  : 组合命令的预处理,把命令拆分放入缓存中
预期结果          : 返回处理结果
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_CombineCmdProc, Test_CombineCmdProc_001)
{
    VOS_UINT8 ucClientId = 0;
    VOS_UINT32 ulRet = 0;
    AT_FW_COMBINE_CMD_STRU stCombCmd = {0};
    AT_FW_COMBINE_CMD_NODE_STRU stCombCmdNode = {0};
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo = {0};

    g_stParseContext[0].stCombineCmdInfo.usTotalNum = 3;
    g_stParseContext[0].stCombineCmdInfo.usProcNum = 0;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.next = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.prev = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;

    MOCKER(CmdParseProc).will(returnValue(AT_OK));
    ulRet = At_CombineCmdProc(ucClientId);
    EXPECT_EQ(ulRet,AT_ERROR);

    stCombCmdNode.pstCombCmd = &stCombCmd;
    stCombCmdNode.stCombCmdList.next = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    stCombCmdNode.stCombCmdList.prev = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    g_stParseContext[0].stCombineCmdInfo.usTotalNum = 3;
    g_stParseContext[0].stCombineCmdInfo.usProcNum = 0;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.next = &stCombCmdNode.stCombCmdList;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.prev = &stCombCmdNode.stCombCmdList;

    ulRet = 0;
    MOCKER(CmdParseProc).will(returnValue(AT_OK));
    ulRet = At_CombineCmdProc(ucClientId);
    EXPECT_EQ(ulRet,AT_OK);
}

/*******************************************************************
测试用例编号      : Test_CombineCmdProc_002
被测函数功能描述  : 组合命令的预处理,把命令拆分放入缓存中
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_CombineCmdProc, Test_CombineCmdProc_002)
{
    VOS_UINT8 ucClientId = 0;
    VOS_UINT32 ulRet = 0;
    AT_FW_COMBINE_CMD_STRU stCombCmd = {0};
    AT_FW_COMBINE_CMD_NODE_STRU stCombCmdNode = {0};
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo = {0};

    stCombCmdNode.pstCombCmd = &stCombCmd;
    stCombCmdNode.stCombCmdList.next = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    stCombCmdNode.stCombCmdList.prev = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    g_stParseContext[0].stCombineCmdInfo.usTotalNum = 3;
    g_stParseContext[0].stCombineCmdInfo.usProcNum = 0;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.next = &stCombCmdNode.stCombCmdList;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.prev = &stCombCmdNode.stCombCmdList;

    ulRet = 0;
    MOCKER(CmdParseProc).will(returnValue(AT_WAIT_ASYNC_RETURN));
    ulRet = At_CombineCmdProc(ucClientId);
    EXPECT_EQ(ulRet,AT_WAIT_ASYNC_RETURN);

}
#endif

#if 0


/*****************************************************************************
类名 : Test_atfwCombineCmdChkProc
功能描述 : atfwCombineCmdChkProc UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_atfwCombineCmdChkProc: public ::testing::Test
{
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
测试用例编号      : Test_atfwCombineCmdChkProc_001
被测函数功能描述  : 组合命令检查、处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_atfwCombineCmdChkProc, Test_atfwCombineCmdChkProc_001)
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT8 ucClientId = 0;

    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.next=&g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.prev=&g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    for(int j=0;j<AT_MAX_CLIENT_NUM;j++){
        g_stParseContext[j].stCombineCmdInfo.stCombineCmdList.next=&g_stParseContext[j].stCombineCmdInfo.stCombineCmdList;
        g_stParseContext[j].stCombineCmdInfo.stCombineCmdList.prev=&g_stParseContext[j].stCombineCmdInfo.stCombineCmdList;
    }


    VOS_UINT8 * pDataIn= NULL;
    VOS_UINT16 usLenIn = 0;
    MOCKER(At_CombineCmdProc).will(returnValue(ERR_MSP_SUCCESS));

    pDataIn = (VOS_UINT8*)"at1234";
    usLenIn = 6;
    ulRet = At_CombineCmdChkProc(ucClientId, pDataIn, usLenIn);
    EXPECT_EQ(ulRet,ERR_MSP_SUCCESS);

    pDataIn = (VOS_UINT8*)"at123";
    usLenIn = 2;
    ulRet = At_CombineCmdChkProc(ucClientId, pDataIn, usLenIn);
    EXPECT_EQ(ulRet,AT_OK);

    pDataIn = (VOS_UINT8*)"bt123";
    usLenIn = 2;
    ulRet = At_CombineCmdChkProc(ucClientId, pDataIn, usLenIn);
    EXPECT_EQ(ulRet,AT_ERROR);

    pDataIn = (VOS_UINT8*)"at;123";
    usLenIn = 3;
    ulRet = At_CombineCmdChkProc(ucClientId, pDataIn, usLenIn);
    EXPECT_EQ(ulRet,AT_OK);



}

/*****************************************************************************
类名 : Test_atfwCombCmdProcAfterCmd
功能描述 : atfwCombCmdProcAfterCmd UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_atfwCombCmdProcAfterCmd: public ::testing::Test
{
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
测试用例编号      : Test_atfwCombCmdProcAfterCmd_001
被测函数功能描述  : 组合命令检查、处理
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_atfwCombCmdProcAfterCmd, Test_atfwCombCmdProcAfterCmd_001)
{
    VOS_UINT8 ucClientId = 0;
    VOS_UINT32 ulRet = 0;
    AT_FW_COMBINE_CMD_STRU stCombCmd = {0};
    AT_FW_COMBINE_CMD_NODE_STRU stCombCmdNode = {0};
    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo = {0};

    stCombCmdNode.pstCombCmd = &stCombCmd;
    stCombCmdNode.stCombCmdList.next = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    stCombCmdNode.stCombCmdList.prev = &g_stParseContext[0].stCombineCmdInfo.stCombineCmdList;
    g_stParseContext[0].stCombineCmdInfo.usTotalNum = 3;
    g_stParseContext[0].stCombineCmdInfo.usProcNum = 0;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.next = &stCombCmdNode.stCombCmdList;
    g_stParseContext[0].stCombineCmdInfo.stCombineCmdList.prev = &stCombCmdNode.stCombCmdList;

    MOCKER(CmdParseProc).will(returnValue(AT_OK));
    At_CombCmdProcAfterCmd(0);
    EXPECT_EQ(g_stParseContext[0].stCombineCmdInfo.usProcNum,1);

}
#endif
/*****************************************************************************
类名 : Test_AT_CombCmdisFinal
功能描述 : AT_CombCmdisFinal UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_AT_CombCmdisFinal: public ::testing::Test
{
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
测试用例编号      : Test_AT_CombCmdisFinal_001
被测函数功能描述  : 判断是否是组合命令的最后一个子命令，用来AT上报AT_OK输出用
预期结果          : 返回处理结果
修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : c64416
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_AT_CombCmdisFinal, Test_AT_CombCmdisFinal_001)
{
    VOS_BOOL ret = 0;
    VOS_UINT8 ucIndex = 0;

    g_stParseContext[0].stCombineCmdInfo.usTotalNum=4;
    g_stParseContext[0].stCombineCmdInfo.usProcNum=2;
    ret = At_CombCmdisFinal(ucIndex);
    EXPECT_EQ(ret,VOS_FALSE);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_AT_CombCmdisFinal_002
被测函数功能描述  : 判断是否是组合命令的最后一个子命令，用来AT上报AT_OK输出用
预期结果          : 返回处理结果
修改历史      :
1.日    期   : 2011年10月13日
作    者   : c64416
修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_AT_CombCmdisFinal, Test_AT_CombCmdisFinal_002)
{
    VOS_BOOL ret = 0;
    VOS_UINT8 ucIndex = 0;

    g_stParseContext[0].stCombineCmdInfo.usTotalNum=1;
    g_stParseContext[0].stCombineCmdInfo.usProcNum=2;
    ret = At_CombCmdisFinal(ucIndex);
    EXPECT_EQ(ret,VOS_TRUE);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名 : Test_At_FilterDCmdSpecCharacter
功能描述 : At_FilterDCmdSpecCharacter UT工程类
修改历史     :
1.日   期  : 2011年10月13日
作   者  : c64416
修改内容 : 新生成类
*****************************************************************************/
class Test_At_FilterDCmdSpecCharacter: public ::testing::Test
{
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
测试用例编号      : Test_At_FilterDCmdSpecCharacter_001
被测函数功能描述  : 数据长度小于3
预期结果          : 不处理
修改历史      :
 1.日    期   : 2013年05月13日
   作    者   : L65478
   修改内容   : 新建CASE
 2.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : DTS2013121606723
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_001)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("AT") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "AT", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ(ulExpectDataLen,ulDataLen);
    free(aucAtData);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_002
被测函数功能描述  : 第一个数字不是A
预期结果          : 不处理
修改历史      :
 1.日    期   : 2013年05月13日
   作    者   : L65478
   修改内容   : 新建CASE
 2.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : DTS2013121606723
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_002)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("BTD+&1^*#$17*#)-;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "BTD+&1^*#$17*#)-;", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ('B',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('+',aucAtData[3]);
    EXPECT_EQ('&',aucAtData[4]);
    EXPECT_EQ('1',aucAtData[5]);
    EXPECT_EQ('^',aucAtData[6]);
    EXPECT_EQ('*',aucAtData[7]);
    EXPECT_EQ('#',aucAtData[8]);
    EXPECT_EQ('$',aucAtData[9]);
    EXPECT_EQ('1',aucAtData[10]);
    EXPECT_EQ('7',aucAtData[11]);
    EXPECT_EQ('*',aucAtData[12]);
    EXPECT_EQ('#',aucAtData[13]);
    EXPECT_EQ(')',aucAtData[14]);
    EXPECT_EQ('-',aucAtData[15]);
    EXPECT_EQ(';',aucAtData[16]);
    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_003
被测函数功能描述  : 第二个数字不是T
预期结果          : 不处理
修改历史      :
 1.日    期   : 2013年05月13日
   作    者   : L65478
   修改内容   : 新建CASE
 2.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : DTS2013121606723
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_003)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ABD+&1^*#$17*#)-;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ABD+&1^*#$17*#)-;", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('B',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('+',aucAtData[3]);
    EXPECT_EQ('&',aucAtData[4]);
    EXPECT_EQ('1',aucAtData[5]);
    EXPECT_EQ('^',aucAtData[6]);
    EXPECT_EQ('*',aucAtData[7]);
    EXPECT_EQ('#',aucAtData[8]);
    EXPECT_EQ('$',aucAtData[9]);
    EXPECT_EQ('1',aucAtData[10]);
    EXPECT_EQ('7',aucAtData[11]);
    EXPECT_EQ('*',aucAtData[12]);
    EXPECT_EQ('#',aucAtData[13]);
    EXPECT_EQ(')',aucAtData[14]);
    EXPECT_EQ('-',aucAtData[15]);
    EXPECT_EQ(';',aucAtData[16]);
    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_004
被测函数功能描述  : 第三个数字不是D
预期结果          : 不处理
修改历史      :
 1.日    期   : 2013年05月13日
   作    者   : L65478
   修改内容   : 新建CASE
 2.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : DTS2013121606723
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_004)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATB+&1^*#$17*#)-;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATB+&1^*#$17*#)-;", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('B',aucAtData[2]);
    EXPECT_EQ('+',aucAtData[3]);
    EXPECT_EQ('&',aucAtData[4]);
    EXPECT_EQ('1',aucAtData[5]);
    EXPECT_EQ('^',aucAtData[6]);
    EXPECT_EQ('*',aucAtData[7]);
    EXPECT_EQ('#',aucAtData[8]);
    EXPECT_EQ('$',aucAtData[9]);
    EXPECT_EQ('1',aucAtData[10]);
    EXPECT_EQ('7',aucAtData[11]);
    EXPECT_EQ('*',aucAtData[12]);
    EXPECT_EQ('#',aucAtData[13]);
    EXPECT_EQ(')',aucAtData[14]);
    EXPECT_EQ('-',aucAtData[15]);
    EXPECT_EQ(';',aucAtData[16]);
    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_005
被测函数功能描述  : 包含有特殊字符串ATD+1234567890*#ABCDabcd,TP!W@>IiGg$&;
预期结果          : 删除0-9，a-c，A-C和i,I,g,G,>外的字符
修改历史      :
 1.日    期   : 2013年05月13日
   作    者   : L65478
   修改内容   : 新建CASE
 2.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : DTS2013121606723
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_005)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD+1234567890*#ABCDabcd,TP!W@>IiGg$&;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD+1234567890*#ABCDabcd,TP!W@>IiGg$&;", ulDataLen);

    ulExpectDataLen = 26;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('+',aucAtData[3]);
    EXPECT_EQ('1',aucAtData[4]);
    EXPECT_EQ('2',aucAtData[5]);
    EXPECT_EQ('3',aucAtData[6]);
    EXPECT_EQ('4',aucAtData[7]);
    EXPECT_EQ('5',aucAtData[8]);
    EXPECT_EQ('6',aucAtData[9]);
    EXPECT_EQ('7',aucAtData[10]);
    EXPECT_EQ('8',aucAtData[11]);
    EXPECT_EQ('9',aucAtData[12]);
    EXPECT_EQ('0',aucAtData[13]);
    EXPECT_EQ('*',aucAtData[14]);
    EXPECT_EQ('#',aucAtData[15]);
    EXPECT_EQ('A',aucAtData[16]);
    EXPECT_EQ('B',aucAtData[17]);
    EXPECT_EQ('C',aucAtData[18]);
    EXPECT_EQ('a',aucAtData[19]);
    EXPECT_EQ('b',aucAtData[20]);
    EXPECT_EQ('c',aucAtData[21]);
    EXPECT_EQ('>',aucAtData[22]);
    EXPECT_EQ('i',aucAtData[23]);
    EXPECT_EQ('G',aucAtData[24]);
    EXPECT_EQ(';',aucAtData[25]);
    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_006
被测函数功能描述  : 被叫号码字符串中间的+ ATD*7+41796915248;
预期结果          : +会被丢弃
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_006)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD*7+41796915248;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD*7+41796915248;", ulDataLen);

    ulExpectDataLen = ulDataLen - 1;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('*',aucAtData[3]);
    EXPECT_EQ('7',aucAtData[4]);
    EXPECT_EQ('4',aucAtData[5]);
    EXPECT_EQ('1',aucAtData[6]);
    EXPECT_EQ('7',aucAtData[7]);
    EXPECT_EQ('9',aucAtData[8]);
    EXPECT_EQ('6',aucAtData[9]);
    EXPECT_EQ('9',aucAtData[10]);
    EXPECT_EQ('1',aucAtData[11]);
    EXPECT_EQ('5',aucAtData[12]);
    EXPECT_EQ('2',aucAtData[13]);
    EXPECT_EQ('4',aucAtData[14]);
    EXPECT_EQ('8',aucAtData[15]);
    EXPECT_EQ(';',aucAtData[16]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_007
被测函数功能描述  : 被叫号码字符串后的呼叫属性字符I：ATD13901100335I;
预期结果          : 字符I会保留
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_007)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD13901100335I;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD13901100335I;", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('3',aucAtData[4]);
    EXPECT_EQ('9',aucAtData[5]);
    EXPECT_EQ('0',aucAtData[6]);
    EXPECT_EQ('1',aucAtData[7]);
    EXPECT_EQ('1',aucAtData[8]);
    EXPECT_EQ('0',aucAtData[9]);
    EXPECT_EQ('0',aucAtData[10]);
    EXPECT_EQ('3',aucAtData[11]);
    EXPECT_EQ('3',aucAtData[12]);
    EXPECT_EQ('5',aucAtData[13]);
    EXPECT_EQ('I',aucAtData[14]);
    EXPECT_EQ(';',aucAtData[15]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_008
被测函数功能描述  : 被叫号码字符串后的呼叫属性字符G：ATD13901100335G;
预期结果          : 字符G会保留
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_008)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD13901100335G;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD13901100335G;", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('3',aucAtData[4]);
    EXPECT_EQ('9',aucAtData[5]);
    EXPECT_EQ('0',aucAtData[6]);
    EXPECT_EQ('1',aucAtData[7]);
    EXPECT_EQ('1',aucAtData[8]);
    EXPECT_EQ('0',aucAtData[9]);
    EXPECT_EQ('0',aucAtData[10]);
    EXPECT_EQ('3',aucAtData[11]);
    EXPECT_EQ('3',aucAtData[12]);
    EXPECT_EQ('5',aucAtData[13]);
    EXPECT_EQ('G',aucAtData[14]);
    EXPECT_EQ(';',aucAtData[15]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_009
被测函数功能描述  : 被叫号码字符串后的呼叫属性字符i：ATD13901100335i;
预期结果          : 字符i会保留
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_009)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD13901100335i;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD13901100335i;", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('3',aucAtData[4]);
    EXPECT_EQ('9',aucAtData[5]);
    EXPECT_EQ('0',aucAtData[6]);
    EXPECT_EQ('1',aucAtData[7]);
    EXPECT_EQ('1',aucAtData[8]);
    EXPECT_EQ('0',aucAtData[9]);
    EXPECT_EQ('0',aucAtData[10]);
    EXPECT_EQ('3',aucAtData[11]);
    EXPECT_EQ('3',aucAtData[12]);
    EXPECT_EQ('5',aucAtData[13]);
    EXPECT_EQ('i',aucAtData[14]);
    EXPECT_EQ(';',aucAtData[15]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_010
被测函数功能描述  : 被叫号码字符串后的呼叫属性字符g：ATD13901100335g;
预期结果          : 字符g会保留
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_010)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD13901100335g;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD13901100335g;", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('3',aucAtData[4]);
    EXPECT_EQ('9',aucAtData[5]);
    EXPECT_EQ('0',aucAtData[6]);
    EXPECT_EQ('1',aucAtData[7]);
    EXPECT_EQ('1',aucAtData[8]);
    EXPECT_EQ('0',aucAtData[9]);
    EXPECT_EQ('0',aucAtData[10]);
    EXPECT_EQ('3',aucAtData[11]);
    EXPECT_EQ('3',aucAtData[12]);
    EXPECT_EQ('5',aucAtData[13]);
    EXPECT_EQ('G',aucAtData[14]);
    EXPECT_EQ(';',aucAtData[15]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_011
被测函数功能描述  : 呼叫电话本中的索引：ATD>1;
预期结果          : >符号不会被丢弃
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_011)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD>1;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD>1;", ulDataLen);

    ulExpectDataLen = ulDataLen;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('>',aucAtData[3]);
    EXPECT_EQ('1',aucAtData[4]);
    EXPECT_EQ(';',aucAtData[5]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_012
被测函数功能描述  : 被叫号码字符串第4个字符为I：ATDI1234;
预期结果          : 删除第4个字符I输出字符串为ATD1234;
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_012)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATDI1234;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATDI1234;", ulDataLen);

    ulExpectDataLen = ulDataLen - 1;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('2',aucAtData[4]);
    EXPECT_EQ('3',aucAtData[5]);
    EXPECT_EQ('4',aucAtData[6]);
    EXPECT_EQ(';',aucAtData[7]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_013
被测函数功能描述  : 被叫号码中包含字符I：ATD12I3G4;
预期结果          : 属性字符保留一份移动到电话号码结尾处，输出字符串为ATD1234IG;
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_013)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD1i2I3G4g;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD1i2I3G4g;", ulDataLen);

    ulExpectDataLen = ulDataLen - 2;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('2',aucAtData[4]);
    EXPECT_EQ('3',aucAtData[5]);
    EXPECT_EQ('4',aucAtData[6]);
    EXPECT_EQ('I',aucAtData[7]);
    EXPECT_EQ('G',aucAtData[8]);
    EXPECT_EQ(';',aucAtData[9]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_014
被测函数功能描述  : 被叫号码包含属性字符串GG：ATD12I3GG4;
预期结果          : 属性字符保留一份移动到电话号码结尾处，输出字符串为ATD1234IG;
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_014)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD12I3GG4;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD12I3GG4;", ulDataLen);

    ulExpectDataLen = ulDataLen - 1;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('2',aucAtData[4]);
    EXPECT_EQ('3',aucAtData[5]);
    EXPECT_EQ('4',aucAtData[6]);
    EXPECT_EQ('I',aucAtData[7]);
    EXPECT_EQ('G',aucAtData[8]);
    EXPECT_EQ(';',aucAtData[9]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_015
被测函数功能描述  : 被叫号码包含冲突的属性字符串Ii：ATD12I3IigG4;
预期结果          : 冲突属性字符保留最后一份移动到电话号码结尾处，输出字符串为ATD1234iG;
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_015)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD12I3IigG4;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD12I3IigG4;", ulDataLen);

    ulExpectDataLen = ulDataLen - 3;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('2',aucAtData[4]);
    EXPECT_EQ('3',aucAtData[5]);
    EXPECT_EQ('4',aucAtData[6]);
    EXPECT_EQ('i',aucAtData[7]);
    EXPECT_EQ('G',aucAtData[8]);
    EXPECT_EQ(';',aucAtData[9]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_016
被测函数功能描述  : 被叫号码包含冲突的属性字符串Ii：ATD1i2I3gG4;
预期结果          : 冲突属性字符保留最后一份移动到电话号码结尾处，输出字符串为ATD1234iG;
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_016)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATD1i2I3gG4;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATD1i2I3gG4;", ulDataLen);

    ulExpectDataLen = ulDataLen - 2;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('2',aucAtData[4]);
    EXPECT_EQ('3',aucAtData[5]);
    EXPECT_EQ('4',aucAtData[6]);
    EXPECT_EQ('I',aucAtData[7]);
    EXPECT_EQ('G',aucAtData[8]);
    EXPECT_EQ(';',aucAtData[9]);

    free(aucAtData);
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_At_FilterDCmdSpecCharacter_017
被测函数功能描述  : 被叫号码前包含属性字符串i：ATDi123gG4;
预期结果          : 属性字符串i保留移动到电话号码结尾处，输出字符串为ATD1234iG;
修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : f62575
   修改内容   : 新建CASE
*******************************************************************/
TEST_F(Test_At_FilterDCmdSpecCharacter, Test_At_FilterDCmdSpecCharacter_017)
{
    VOS_UINT8                  *aucAtData = VOS_NULL_PTR;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulExpectDataLen;

    ulDataLen       = sizeof("ATDi123gG4;") - 1;
    aucAtData       = (VOS_UINT8 *)malloc(ulDataLen);
    memcpy(aucAtData, "ATDi123gG4;", ulDataLen);

    ulExpectDataLen = ulDataLen - 1;
    At_FilterDCmdSpecCharacter(&ulDataLen, aucAtData);

    EXPECT_EQ(ulExpectDataLen,ulDataLen);

    EXPECT_EQ('A',aucAtData[0]);
    EXPECT_EQ('T',aucAtData[1]);
    EXPECT_EQ('D',aucAtData[2]);
    EXPECT_EQ('1',aucAtData[3]);
    EXPECT_EQ('2',aucAtData[4]);
    EXPECT_EQ('3',aucAtData[5]);
    EXPECT_EQ('4',aucAtData[6]);
    EXPECT_EQ('i',aucAtData[7]);
    EXPECT_EQ('G',aucAtData[8]);
    EXPECT_EQ(';',aucAtData[9]);

    free(aucAtData);
    GlobalMockObject::verify();
}


