#include "gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsFilter.h"

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
类名     : Test_ADS_FILTER_InitCtx
功能描述 : ADS_FILTER_InitCtx UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_InitCtx: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_InitCtx_001
测试用例标题      : NV项读取失败
预期结果          : 老化周期使用默认值
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_InitCtx, Test_ADS_FILTER_InitCtx_001)
{
    // 变量声明
    VOS_UINT32                          ulTimeLen;
    VOS_UINT16                          usNvID;

    // 参数初始化
    usNvID      = en_NV_Item_SHARE_PDP_INFO;
    ulTimeLen   = ADS_FILTER_SECOND_TRANSFER_JIFFIES * ADS_FILTER_DEFAULT_AGING_TIMELEN;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(usNvID), any(), any())
        .will(returnValue(NV_ID_NOT_EXIST));

    MOCKER(ADS_FILTER_InitListsHead)
        .expects(exactly(1));

    MOCKER(ADS_FILTER_ResetIPv6Addr)
        .expects(exactly(1));

    // 调用被测函数
    ADS_FILTER_InitCtx();

    // 执行检查
    EXPECT_EQ(ulTimeLen, ADS_FILTER_GET_AGING_TIME_LEN());

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_InitCtx_002
测试用例标题      : NV项读取成功
预期结果          : 老化周期为10s
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_InitCtx, Test_ADS_FILTER_InitCtx_002)
{
    // 变量声明
    VOS_UINT32                          ulTimeLen;
    VOS_UINT16                          usNvID;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdp = {0};

    // 参数初始化
    usNvID      = en_NV_Item_SHARE_PDP_INFO;
    ulTimeLen   = ADS_FILTER_SECOND_TRANSFER_JIFFIES * 10;
    stSharePdp.ucEnableFlag     = VOS_TRUE;
    stSharePdp.usAgingTimeLen   = 10;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(usNvID), outBoundP((void *)&stSharePdp, sizeof(stSharePdp)), any())
        .will(returnValue(NV_OK));

    MOCKER(ADS_FILTER_InitListsHead)
        .expects(exactly(1));

    MOCKER(ADS_FILTER_ResetIPv6Addr)
        .expects(exactly(1));

    // 调用被测函数
    ADS_FILTER_InitCtx();

    // 执行检查
    EXPECT_EQ(ulTimeLen, ADS_FILTER_GET_AGING_TIME_LEN());

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_HeapAlloc
功能描述 : ADS_FILTER_HeapAlloc UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_HeapAlloc: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_HeapAlloc_001
测试用例标题      : 申请的内存大小为0
预期结果          : 申请失败，返回空指针
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_HeapAlloc, Test_ADS_FILTER_HeapAlloc_001)
{
    // 变量声明
    VOS_VOID                           *pPointer = VOS_NULL_PTR;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    pPointer = ADS_FILTER_HeapAlloc(-1);

    // 执行检查
    EXPECT_EQ(VOS_NULL_PTR, pPointer);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_HeapAlloc_002
测试用例标题      : 申请的内存大小太大，为1025字节
预期结果          : 申请失败，返回空指针
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_HeapAlloc, Test_ADS_FILTER_HeapAlloc_002)
{
    // 变量声明
    VOS_VOID                           *pPointer = VOS_NULL_PTR;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    pPointer = ADS_FILTER_HeapAlloc(1025);

    // 执行检查
    EXPECT_EQ(VOS_NULL_PTR, pPointer);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_HeapFree
功能描述 : ADS_FILTER_HeapFree UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_HeapFree: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_HeapFree_001
测试用例标题      : 释放空指针
预期结果          : 不处理，直接返回
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_HeapFree, Test_ADS_FILTER_HeapFree_001)
{
    // 变量声明

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ADS_FILTER_HeapFree(VOS_NULL_PTR);

    // 执行检查

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_AddFilter
功能描述 : ADS_FILTER_AddFilter UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_AddFilter: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 初始化过滤表头节点 */
        ADS_FILTER_InitListsHead();

    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 重置过滤表 */
        ADS_FILTER_ResetLists();

         GlobalMockObject::verify();

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_AddFilter_001
测试用例标题      : 内存申请失败
预期结果          : 错误打印
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_AddFilter, Test_ADS_FILTER_AddFilter_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    stFilter.enPktType              = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.stIPHeader.ulSrcAddr   = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr   = 0x3B31520A;   //10.82.49.59
    stFilter.stIPHeader.ucProtocol  = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x5000;   //80

    ucIndex = stFilter.unFilter.stTcpFilter.usSrcPort & 0xFF;

    // 初始化全局变量
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    // MOCKER操作
    MOCKER(ADS_FILTER_HeapAlloc)
        .expects(exactly(1))
        .will(returnValue((void *)VOS_NULL_PTR));

    // 调用被测函数
    ADS_FILTER_AddFilter(&stFilter);

    // 执行检查
    EXPECT_EQ(pstListHead, pstListHead->next);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_AddFilter_002
测试用例标题      : 内存申请成功
预期结果          : 过滤器增加到链表中
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_AddFilter, Test_ADS_FILTER_AddFilter_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    ADS_FILTER_NODE_STRU                stNode          = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter       = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    pstFilter   = &stNode.stFilter;
    pstFilter->enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    pstFilter->ulTmrCnt                 = 1000;
    pstFilter->stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    pstFilter->stIPHeader.ulDstAddr     = 0x3B31520A;   //10.82.49.59
    pstFilter->stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    pstFilter->unFilter.stTcpFilter.usSrcPort = 0x5000; //80
    pstFilter->unFilter.stTcpFilter.usDstPort = 0x5000; //80

    ucIndex = (pstFilter->unFilter.stTcpFilter.usSrcPort & 0xFF00) >> 8;

    // 初始化全局变量
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    // MOCKER操作

    // 调用被测函数
    ADS_FILTER_AddFilter(pstFilter);

    // 执行检查
    pstNode = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRet = PS_MEM_CMP(&pstNode->stFilter, pstFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_IsInfoMatch
功能描述 : ADS_FILTER_IsInfoMatch UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_IsInfoMatch: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 初始化过滤表头节点 */
        ADS_FILTER_InitListsHead();

    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /* 重置过滤表 */
        ADS_FILTER_ResetLists();

         GlobalMockObject::verify();

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_IsInfoMatch_001
测试用例标题      : 过滤器IP首部不匹配
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // 参数初始化
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_UDP;

    stFilter2.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter2.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter2.stIPHeader.ucProtocol     = ADS_IPPROTO_TCP;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_IsInfoMatch_002
测试用例标题      : 过滤器TCP首部匹配
预期结果          : 返回VOS_TRUE
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // 参数初始化
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_TCP;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_TCP;
    stFilter1.unFilter.stTcpFilter.usSrcPort = 0x5000;  //80
    stFilter1.unFilter.stTcpFilter.usDstPort = 0x5000;  //80

    stFilter2   = stFilter1;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_IsInfoMatch_003
测试用例标题      : 过滤器UDP首部匹配
预期结果          : 返回VOS_TRUE
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // 参数初始化
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_UDP;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_UDP;
    stFilter1.unFilter.stUdpFilter.usSrcPort = 0x5000;  //80
    stFilter1.unFilter.stUdpFilter.usDstPort = 0x901F;  //8080

    stFilter2   = stFilter1;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_IsInfoMatch_004
测试用例标题      : 过滤器ICMP首部匹配
预期结果          : 返回VOS_TRUE
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // 参数初始化
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_ICMP;
    stFilter1.unFilter.stIcmpFilter.usIdentifier    = 0x1806;   //1560
    stFilter1.unFilter.stIcmpFilter.usSeqNum        = 0x0F00;   //15

    stFilter2   = stFilter1;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_IsInfoMatch_005
测试用例标题      : 过滤器FRAGMENT首部匹配
预期结果          : 返回VOS_TRUE
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // 参数初始化
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_FRAGMENT;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_UDP;
    stFilter1.unFilter.stFragmentFilter.usIdentification = 0xFB00; //251

    stFilter2   = stFilter1;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_IsInfoMatch_006
测试用例标题      : 不支持的数据包类型
预期结果          : 返回VOS_FALSE
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // 参数初始化
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_BUTT;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_IGMP;

    stFilter2   = stFilter1;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // 执行检查
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_Match
功能描述 : ADS_FILTER_Match UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_Match: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 初始化过滤表头节点 */
        ADS_FILTER_InitListsHead();

    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 重置过滤表 */
        ADS_FILTER_ResetLists();

        GlobalMockObject::verify();
    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_Match_001
测试用例标题      : 节点老化，过滤信息匹配，老化周期匹配
预期结果          : 节点被老化，匹配节点老化时间刷新，返回VOS_TRUE
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_Match, Test_ADS_FILTER_Match_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilterTmp     = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    jiffies     = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;   //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x5000;   //80

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME() - 1000;
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;   //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;   //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stUdpFilter.usDstPort = 0x1500;   //21

    stFilterTmp = stFilter;

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3D31520A;    //10.82.49.61
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // 初始化全局变量
    ADS_FILTER_SET_AGING_TIME_LEN(2000);
    jiffies     = 9000;

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_Match(&stFilterTmp);

    // 执行检查
    EXPECT_EQ(VOS_TRUE, ulRet);
    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next->next, ADS_FILTER_NODE_STRU, stList);
    EXPECT_EQ(9000, pstNode->stFilter.ulTmrCnt);
    EXPECT_EQ(0x1500, pstNode->stFilter.unFilter.stUdpFilter.usDstPort);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_SaveIPAddrInfo
功能描述 : ADS_FILTER_SaveIPAddrInfo UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_SaveIPAddrInfo: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        ADS_FILTER_ResetIPv6Addr();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_SaveIPAddrInfo_001
测试用例标题      : 保存过滤用IPv6地址
预期结果          : 保存的地址相同
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_SaveIPAddrInfo, Test_ADS_FILTER_SaveIPAddrInfo_001)
{
    // 变量声明
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr  = {0};
    ADS_IPV6_ADDR_UN                    unIPv6Addr      = {0};
    VOS_UINT8                           ucRslt;

    // 参数初始化
    stFilterIpAddr.bitOpIpv6Addr    = VOS_TRUE;
    stFilterIpAddr.aucIpv6Addr[0]   = 200;
    stFilterIpAddr.aucIpv6Addr[1]   = 10;
    stFilterIpAddr.aucIpv6Addr[2]   = 20;
    stFilterIpAddr.aucIpv6Addr[3]   = 30;
    stFilterIpAddr.aucIpv6Addr[10]  = 11;
    stFilterIpAddr.aucIpv6Addr[11]  = 120;
    stFilterIpAddr.aucIpv6Addr[12]  = 130;
    stFilterIpAddr.aucIpv6Addr[13]  = 140;
    stFilterIpAddr.aucIpv6Addr[14]  = 1;
    stFilterIpAddr.aucIpv6Addr[15]  = 2;
    memcpy(unIPv6Addr.aucIpAddr, stFilterIpAddr.aucIpv6Addr, ADS_IPV6_ADDR_LEN);

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ADS_FILTER_SaveIPAddrInfo(&stFilterIpAddr);

    // 执行检查
    ucRslt = ADS_FILTER_IS_IPV6_ADDR_IDENTICAL(&unIPv6Addr, ADS_FILTER_GET_IPV6_ADDR()) ? 0 : 1;
    EXPECT_EQ(0, ucRslt);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_ProcUlPacket
功能描述 : ADS_FILTER_ProcUlPacket UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_ProcUlPacket: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /* 重置可维可测信息 */
        ADS_FILTER_ResetStatisticInfo();

        /* 初始化过滤表头节点 */
        ADS_FILTER_InitListsHead();
    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 重置过滤表 */
        ADS_FILTER_ResetLists();
        GlobalMockObject::verify();
    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcUlPacket_001
测试用例标题      : 上行发送IPV6数据包
预期结果          : 可维可测信息IPV6数据包个数增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_001)
{
    // 变量声明
    IMM_ZC_STRU                         stZcData = {0};

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV6);

    // 执行检查
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV6_PKT));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcUlPacket_002
测试用例标题      : 上行发送IPV4数据包，数据包类型不支持
预期结果          : 可维可测信息IPV4不支持数据包类型个数增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_002)
{
    // 变量声明
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02,
        0xBA, 0x2D, 0xC0, 0xA8, 0x01, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x11, 0x00, 0x0D, 0xFD, 0xE0, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // 参数初始化
    stZcData.data = aucData;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(ADS_FILTER_Match)
        .expects(never());

    // 调用被测函数
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcUlPacket_003
测试用例标题      : 上行发送IPV4数据包2个，数据包类型TCP类型，且过滤表中已经存在
预期结果          : 可维可测信息IPV4数据包TCP类型个数增加2
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
        0xBB, 0x29, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x50, 0x1F, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    stZcData.data   = aucData;
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    // 初始化全局变量
    ADS_FILTER_SET_AGING_TIME_LEN(2000);

    // MOCKER操作

    // 调用被测函数第一次
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRet       = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP));
    EXPECT_EQ(0, ulRet);

    // 调用被测函数第二次
    jiffies     = 9000;
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    stFilter.ulTmrCnt   = ADS_GET_CURR_KERNEL_TIME();
    ulRet               = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(2, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcUlPacket_004
测试用例标题      : 上行发送IPV4数据包2个，数据包类型ICMP类型，
                    ECHO REQ及ECHO REPLY类型
预期结果          : 可维可测信息IPV4数据包ICMP类型个数增加1
                    不支持的数据包个数增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData1[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x00, 0x4D, 0xC1, 0x00, 0x9C, 0x00, 0x0F, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           aucData2[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x08, 0x00, 0x45, 0xC1, 0x00, 0x9C, 0x00, 0x0F, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    stZcData.data   = aucData1;
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    // 初始化全局变量
    ADS_FILTER_SET_AGING_TIME_LEN(2000);

    // MOCKER操作

    // 调用被测函数第一次
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT));
    EXPECT_EQ((VOS_UINT_PTR)pstListHead, (VOS_UINT_PTR)pstListHead->next);

    // 调用被测函数第二次
    stZcData.data   = aucData2;
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRet       = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcUlPacket_005
测试用例标题      : 上行发送IPV4数据包，数据包类型UDP类型，
预期结果          : 可维可测信息IPV4数据包UDP类型个数增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x44, 0x00, 0x44, 0x00, 0x1E, 0x50, 0xFD, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    stZcData.data   = aucData;
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4400;   //68

    // 初始化全局变量
    ADS_FILTER_SET_AGING_TIME_LEN(2000);

    // MOCKER操作

    // 调用被测函数
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRet       = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_UDP));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcUlPacket_006
测试用例标题      : 上行发送IPV4数据包，数据包类型TCP类型，且为分配包非首片，
预期结果          : 可维可测信息非首片数据包类型个数增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x01, 0x03, 0x11,
        0xBB, 0x1E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x44, 0x00, 0x44, 0x00, 0x1E, 0x50, 0xFD, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    stZcData.data   = aucData;
    jiffies         = 8000;

        // 初始化全局变量
    ADS_FILTER_SET_AGING_TIME_LEN(2000);

    // MOCKER操作

    // 调用被测函数
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查

    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT));

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_ProcDlPacket
功能描述 : ADS_FILTER_ProcDlPacket UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_ProcDlPacket: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 重置可维可测信息 */
        ADS_FILTER_ResetStatisticInfo();

        /* 初始化过滤表头节点 */
        ADS_FILTER_InitListsHead();
    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /* 重置过滤表 */
        ADS_FILTER_ResetLists();
        GlobalMockObject::verify();
    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_001
测试用例标题      : 收到IPv6类型下行数据包，目的地址与过滤IPv6地址不匹配
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr  = {0};
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x60, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x06, 0xFF, 0x20, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5E, 0xFE,
        0xC0, 0xA8, 0x01, 0x01, 0x20, 0x02, 0xD3, 0x01, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x00, 0x50, 0x1F, 0x90, 0x00, 0x00, 0xCF, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x3C, 0xCF, 0x00, 0x00
    };

    // 参数初始化
    stZcData.data   = aucData;
    stFilterIpAddr.bitOpIpv6Addr    = VOS_TRUE;

    /* IPv6: 2002:D301:0101:0001:02E0:DDFF:FEE0:E0E2 */
    stFilterIpAddr.aucIpv6Addr[0]   = 0x20;
    stFilterIpAddr.aucIpv6Addr[1]   = 0x02;
    stFilterIpAddr.aucIpv6Addr[2]   = 0xD3;
    stFilterIpAddr.aucIpv6Addr[3]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[4]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[5]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[6]   = 0x00;
    stFilterIpAddr.aucIpv6Addr[7]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[8]   = 0x02;
    stFilterIpAddr.aucIpv6Addr[9]   = 0xE0;
    stFilterIpAddr.aucIpv6Addr[10]  = 0xDD;
    stFilterIpAddr.aucIpv6Addr[11]  = 0xFF;
    stFilterIpAddr.aucIpv6Addr[12]  = 0xFE;
    stFilterIpAddr.aucIpv6Addr[13]  = 0xE0;
    stFilterIpAddr.aucIpv6Addr[14]  = 0xE0;
    stFilterIpAddr.aucIpv6Addr[15]  = 0xE2;

    // 初始化全局变量
    ADS_FILTER_SaveIPAddrInfo(&stFilterIpAddr);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV6);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_002
测试用例标题      : 收到IPv6类型下行数据包，目的地址与过滤IPv6地址匹配
预期结果          : 返回VOS_OK
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr  = {0};
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x60, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x06, 0xFF, 0x20, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5E, 0xFE,
        0xC0, 0xA8, 0x01, 0x01, 0x20, 0x02, 0xD3, 0x01, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x00, 0x50, 0x1F, 0x90, 0x00, 0x00, 0xCF, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x3C, 0xCF, 0x00, 0x00
    };

    // 参数初始化
    stZcData.data   = aucData;
    stFilterIpAddr.bitOpIpv6Addr    = VOS_TRUE;

    /* IPv6: 2002:D301:0101:0001:02E0:DDFF:FEE0:E0E2 */
    stFilterIpAddr.aucIpv6Addr[0]   = 0x20;
    stFilterIpAddr.aucIpv6Addr[1]   = 0x02;
    stFilterIpAddr.aucIpv6Addr[2]   = 0xD3;
    stFilterIpAddr.aucIpv6Addr[3]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[4]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[5]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[6]   = 0x00;
    stFilterIpAddr.aucIpv6Addr[7]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[8]   = 0x02;
    stFilterIpAddr.aucIpv6Addr[9]   = 0xE0;
    stFilterIpAddr.aucIpv6Addr[10]  = 0xDD;
    stFilterIpAddr.aucIpv6Addr[11]  = 0xFF;
    stFilterIpAddr.aucIpv6Addr[12]  = 0xFE;
    stFilterIpAddr.aucIpv6Addr[13]  = 0xE0;
    stFilterIpAddr.aucIpv6Addr[14]  = 0xE0;
    stFilterIpAddr.aucIpv6Addr[15]  = 0xE1;

    // 初始化全局变量
    ADS_FILTER_SaveIPAddrInfo(&stFilterIpAddr);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV6);
    ADS_FILTER_ShowIPv6Addr();

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV6_PKT));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_003
测试用例标题      : 收到未知IP类型下行数据包
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_BUTT);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_004
测试用例标题      : 收到IPv4类型下行数据包，不支持的报文类型
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_004)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02,
        0xBB, 0x2D, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x11, 0x00, 0x0D, 0xFD, 0xE0, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_005
测试用例标题      : 收到IPv4类型下行TCP数据包非分片，且匹配
预期结果          : 返回VOS_OK，可维可测信息TCP下行数据包增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_005)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
        0xBB, 0x29, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x1F, 0x90, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_TCP));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_006
测试用例标题      : 收到IPv4类型下行TCP数据包非分片，不匹配
预期结果          : 返回VOS_ERR，可维可测信息TCP下行数据包不变
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_006)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
        0xBB, 0x29, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x1F, 0x90, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;     //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_TCP));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_007
测试用例标题      : 收到IPv4类型下行UDP数据包非分片，且匹配
预期结果          : 返回VOS_OK，可维可测信息UDP下行数据包增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_007)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x43, 0x00, 0x44, 0x00, 0x1E, 0x1F, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_UDP));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_008
测试用例标题      : 收到IPv4类型下行UDP数据包非分片，不匹配
预期结果          : 返回VOS_ERR，可维可测信息UDP下行数据包不变
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_008)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x43, 0x00, 0x44, 0x00, 0x1E, 0x1F, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;     //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_UDP));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_009
测试用例标题      : 收到IPv4类型下行ICMP数据包ping回复(ECHO REPLY)，且匹配
预期结果          : 返回VOS_OK，可维可测信息ICMP下行ECHOREPLY数据包增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_009)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x81, 0x00, 0x89, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_010
测试用例标题      : 收到IPv4类型下行ICMP数据包，不支持的类型
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_010)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x10, 0x00, 0x23, 0x46, 0x00, 0x9C, 0x00, 0x0F, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x81, 0x00, 0x89, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_011
测试用例标题      : 收到IPv4类型下行ICMP数据包，
                    Time Exceeded类型差错报文，源报文为TCP报文，且匹配
预期结果          : 返回VOS_OK，可维可测信息，ICMP差错报文数增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_011)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x0B, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F,

        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
        0xBB, 0x29, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x50, 0x1F, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_012
测试用例标题      : 收到IPv4类型下行ICMP数据包，
                    Time Exceeded类型差错报文，源报文为UDP报文，且匹配
预期结果          : 返回VOS_OK，可维可测信息，ICMP差错报文数增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_012)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x0B, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F,

        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x44, 0x00, 0x43, 0x00, 0x1E, 0x50, 0xFD, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_013
测试用例标题      : 收到IPv4类型下行ICMP数据包，
                    Time Exceeded类型差错报文，源报文类型不支持
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_013)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x0B, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F,

        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x81, 0x00, 0x89, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_014
测试用例标题      : 收到IPv4类型下行TCP数据包首分片，且匹配，
                    并收到后续非首片
预期结果          : 返回VOS_OK，
                    可维可测信息下行分片首片数据包增加1
                    下行分片包非首片数据包增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_014)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData1[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0xC0, 0x20, 0x00, 0x03, 0x06,
        0xBA, 0x29, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x1F, 0x90, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           aucData2[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0xC0, 0x20, 0x3F, 0x03, 0x06,
        0xB9, 0xEA, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    stZcData.data   = aucData1;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_FRAGMENT;
    stFilter.unFilter.stFragmentFilter.usIdentification = 0xC000;   //192
    stFilter.unFilter.stFragmentFilter.aucReserved[0]   = 0;
    stFilter.unFilter.stFragmentFilter.aucReserved[1]   = 0;

    // MOCKER操作

    // 调用被测函数 首片
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRslt      = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT));
    EXPECT_EQ(0, ulRslt);

    // 调用被测函数 非首片
    stZcData.data   = aucData2;
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT));

    ADS_FILTER_ShowStatisticInfo();

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_015
测试用例标题      : 收到IPv4类型下行UDP数据包首分片，且匹配，
                    并收到后续非首片
预期结果          : 返回VOS_OK，
                    可维可测信息下行分片首片数据包增加1
                    下行分片包非首片数据包增加1
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_015)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData1[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0xC0, 0x20, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x43, 0x00, 0x44, 0x00, 0x1E, 0x1F, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           aucData2[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0xC0, 0x20, 0x3F, 0x03, 0x11,
        0xB9, 0x1E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // 参数初始化
    stZcData.data   = aucData1;

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_FRAGMENT;
    stFilter.unFilter.stFragmentFilter.usIdentification = 0xC000;   //192
    stFilter.unFilter.stFragmentFilter.aucReserved[0]   = 0;
    stFilter.unFilter.stFragmentFilter.aucReserved[1]   = 0;

    // MOCKER操作

    // 调用被测函数 首片
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRslt      = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT));
    EXPECT_EQ(0, ulRslt);

    // 调用被测函数 非首片
    stZcData.data   = aucData2;
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT));

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ProcDlPacket_016
测试用例标题      : 收到IPv4类型下行不支持类型的分片包首片
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_016)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x0C, 0x00, 0x20, 0x00, 0x03, 0x02,
        0xAD, 0x2D, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x11, 0x00, 0x0D, 0xFD, 0xE0, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // 参数初始化
    stZcData.data   = aucData;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数 首片
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_Ipv4AddrItoa
功能描述 : ADS_Ipv4AddrItoa UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_Ipv4AddrItoa: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_Ipv4AddrItoa_001
测试用例标题      : 入参为空指针
预期结果          : 返回VOS_ERR
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_Ipv4AddrItoa, Test_ADS_Ipv4AddrItoa_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulRet = ADS_Ipv4AddrItoa(VOS_NULL_PTR, VOS_NULL_PTR);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_FILTER_ShowFilterLists
功能描述 : ADS_FILTER_ShowFilterLists UT工程类
修改历史 :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_FILTER_ShowFilterLists: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 初始化过滤表头节点 */
        ADS_FILTER_InitListsHead();
    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* 重置过滤表 */
        ADS_FILTER_ResetLists();
        GlobalMockObject::verify();
    }
};

/*******************************************************************
测试用例编号      : Test_ADS_FILTER_ShowFilterLists_001
测试用例标题      :
预期结果          :
修改历史          :
1.日   期  : 2013-06-19
  作   者  : l00198894
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_FILTER_ShowFilterLists, Test_ADS_FILTER_ShowFilterLists_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // 参数初始化

    // 初始化全局变量
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;     //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;     //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_FRAGMENT;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_BUTT;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER操作

    // 调用被测函数
    ADS_FILTER_ShowFilterLists();

    // 执行检查

    GlobalMockObject::verify();
}


