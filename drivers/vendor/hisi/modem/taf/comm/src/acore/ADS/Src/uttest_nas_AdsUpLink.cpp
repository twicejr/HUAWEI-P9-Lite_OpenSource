#include "gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsUpLink.h"

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
类名     : Test_ADS_UL_RcvCdsIpPacketMsg
功能描述 : ADS_UL_RcvCdsIpPacketMsg UT工程类
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_RcvCdsIpPacketMsg: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
        GlobalMockObject::verify();
    }
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvCdsIpPacketMsg_001
测试用例标题      : 处理ID_CDS_ADS_IP_PACKET_IND消息
预期结果          : 给NDIS发送ID_ADS_NIDS_DATA_IND消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvCdsIpPacketMsg,Test_ADS_UL_RcvCdsIpPacketMsg_001)
{
    CDS_ADS_DATA_IND_STRU               stCdsAdsDataInd;
    ADS_NDIS_DATA_IND_STRU              stAdsNdisDataInd;

    PS_MEM_SET(&stAdsNdisDataInd, 0x00, sizeof(ADS_NDIS_DATA_IND_STRU));

    /* 构造ID_CDS_ADS_IP_PACKET_IND消息 */
    stCdsAdsDataInd.ulSenderPid    = UEPS_PID_CDS;
    stCdsAdsDataInd.ulReceiverPid  = ACPU_PID_ADS_UL;
    stCdsAdsDataInd.enMsgId        = ID_CDS_ADS_IP_PACKET_IND;
    stCdsAdsDataInd.ucRabId        = 5;
    stCdsAdsDataInd.enIpPacketType = CDS_ADS_IP_PACKET_TYPE_DHCP_SERVERV4;
    //stCdsAdsDataInd.pstZcData      = PS_MEM_ALLOC(ACPU_PID_ADS_UL,4);
    stCdsAdsDataInd.usLen          = 4;

    /* VOS_SendMsg 发送ID_ADS_NIDS_DATA_IND消息*/
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ADS_UL_ProcMsg((struct MsgCB *)(&stCdsAdsDataInd));

    //PS_MEM_FREE(ACPU_PID_ADS_UL, stCdsAdsDataInd.pstZcData);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvCdsIpPacketMsg_002
测试用例标题      : 处理ID_CDS_ADS_IP_PACKET_IND消息
预期结果          : 申请ID_ADS_NIDS_DATA_IND消息失败，不给NDIS发送消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvCdsIpPacketMsg,Test_ADS_UL_RcvCdsIpPacketMsg_002)
{
    CDS_ADS_DATA_IND_STRU               stCdsAdsDataInd;
    ADS_NDIS_DATA_IND_STRU              stAdsNdisDataInd;

    PS_MEM_SET(&stAdsNdisDataInd, 0x00, sizeof(ADS_NDIS_DATA_IND_STRU));

    /* 构造ID_CDS_ADS_IP_PACKET_IND消息 */
    stCdsAdsDataInd.ulSenderPid    = UEPS_PID_CDS;
    stCdsAdsDataInd.ulReceiverPid  = ACPU_PID_ADS_UL;
    stCdsAdsDataInd.enMsgId        = ID_CDS_ADS_IP_PACKET_IND;
    stCdsAdsDataInd.ucRabId        = 5;
    stCdsAdsDataInd.enIpPacketType = CDS_ADS_IP_PACKET_TYPE_DHCP_SERVERV4;

    /* 内存申请失败 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgCB *)VOS_NULL_PTR));

    /* VOS_SendMsg 发送ID_ADS_NIDS_DATA_IND消息 */
    MOCKER(Ps_SendMsg)
        .expects(never());

    ADS_UL_ProcMsg((struct MsgCB *)(&stCdsAdsDataInd));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvCdsIpPacketMsg_003
测试用例标题      : 处理ID_CDS_ADS_IP_PACKET_IND消息
预期结果          : 申请SK_BUFF失败，不给NDIS发送消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvCdsIpPacketMsg,Test_ADS_UL_RcvCdsIpPacketMsg_003)
{
    CDS_ADS_DATA_IND_STRU               stCdsAdsDataInd;
    ADS_NDIS_DATA_IND_STRU              stAdsNdisDataInd;

    PS_MEM_SET(&stAdsNdisDataInd, 0x00, sizeof(ADS_NDIS_DATA_IND_STRU));

    /* 构造ID_CDS_ADS_IP_PACKET_IND消息 */
    stCdsAdsDataInd.ulSenderPid    = UEPS_PID_CDS;
    stCdsAdsDataInd.ulReceiverPid  = ACPU_PID_ADS_UL;
    stCdsAdsDataInd.enMsgId        = ID_CDS_ADS_IP_PACKET_IND;
    stCdsAdsDataInd.ucRabId        = 5;
    stCdsAdsDataInd.enIpPacketType = CDS_ADS_IP_PACKET_TYPE_DHCP_SERVERV4;

    /* 内存sk_buff申请失败 */
    MOCKER(IMM_ZcStaticAlloc_Debug)
        .stubs()
        .will(returnValue((IMM_ZC_STRU *)VOS_NULL_PTR));

    /* VOS_SendMsg 发送ID_ADS_NIDS_DATA_IND消息 */
    MOCKER(Ps_SendMsg)
        .expects(never());

    MOCKER(V_MemFree)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)0));

    ADS_UL_ProcMsg((struct MsgCB *)(&stCdsAdsDataInd));

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if 0
/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvCdsIpPacketMsg_004
测试用例标题      : 处理ID_CDS_ADS_IP_PACKET_IND消息
预期结果          : 发送消息失败
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvCdsIpPacketMsg,Test_ADS_UL_RcvCdsIpPacketMsg_004)
{
    CDS_ADS_DATA_IND_STRU               stCdsAdsDataInd;
    ADS_NDIS_DATA_IND_STRU              stAdsNdisDataInd;

    PS_MEM_SET(&stAdsNdisDataInd, 0x00, sizeof(ADS_NDIS_DATA_IND_STRU));

    /* 构造ID_CDS_ADS_IP_PACKET_IND消息 */
    stCdsAdsDataInd.ulSenderPid    = UEPS_PID_CDS;
    stCdsAdsDataInd.ulReceiverPid  = ACPU_PID_ADS_UL;
    stCdsAdsDataInd.enMsgId        = ID_CDS_ADS_IP_PACKET_IND;
    stCdsAdsDataInd.ucRabId        = 5;
    stCdsAdsDataInd.enIpPacketType = CDS_ADS_IP_PACKET_TYPE_DHCP_SERVERV4;
    stCdsAdsDataInd.pstZcData      = PS_MEM_ALLOC(ACPU_PID_ADS_UL,4);
    stCdsAdsDataInd.usLen          = 4;

    /* VOS_SendMsg 发送ID_ADS_NIDS_DATA_IND消息 */
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* 释放C核内存 */
    MOCKER(IMM_MemFree_Debug)
        .expects(exactly(1));

    MOCKER(kfree_skb)
        .expects(exactly(1));

    ADS_UL_ProcMsg((struct MsgCB *)(&stCdsAdsDataInd));

    PS_MEM_FREE(ACPU_PID_ADS_UL, stCdsAdsDataInd.pstZcData);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_ADS_UL_RcvTafPdpStatusInd
功能描述 : ADS_UL_RcvTafPdpStatusInd UT工程类
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_RcvTafPdpStatusInd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();
        GlobalMockObject::verify();
    }
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvTafPdpStatusInd_001
测试用例标题      : 创建上行缓存队列失败，RabId为1（预置条件：上行上下文被初始化）
预期结果          : ADS_UL_CreateQueue不被调用
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvTafPdpStatusInd,Test_ADS_UL_RcvTafPdpStatusInd_001)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x01;

    MOCKER(ADS_UL_CreateQueue)
        .expects(never());

    MOCKER(ADS_UL_UpdateQueueInPdpModified)
        .expects(never());

    MOCKER(ADS_UL_DestroyQueue)
        .expects(never());

    /* 创建RabId为1的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        EXPECT_EQ(pAdsUlCtx->aucPrioIndex[i] , 0);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvTafPdpStatusInd_002
测试用例标题      : 创建上行缓存队列失败，RabId为16（预置条件：上行上下文被初始化）
预期结果          : ADS_UL_CreateQueue不被调用
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvTafPdpStatusInd,Test_ADS_UL_RcvTafPdpStatusInd_002)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 16;

    MOCKER(ADS_UL_CreateQueue)
        .expects(never());

    MOCKER(ADS_UL_UpdateQueueInPdpModified)
        .expects(never());

    MOCKER(ADS_UL_DestroyQueue)
        .expects(never());

    /* 创建RabId为16的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        EXPECT_EQ(pAdsUlCtx->aucPrioIndex[i] , 0);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvTafPdpStatusInd_003
测试用例标题      : 创建上行缓存队列失败，RabId为5，PDP状态为ADS_PDP_STATUS_BUTT（预置条件：上行上下文被初始化）
预期结果          : ADS_UL_CreateQueue不被调用
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvTafPdpStatusInd,Test_ADS_UL_RcvTafPdpStatusInd_003)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_BUTT;
    stPdpStatusInd.ucRabId       = 5;

    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_FALSE;

    MOCKER(ADS_UL_CreateQueue)
        .expects(never());

    MOCKER(ADS_UL_UpdateQueueInPdpModified)
        .expects(never());

    MOCKER(ADS_UL_DestroyQueue)
        .expects(never());

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        EXPECT_EQ(pAdsUlCtx->aucPrioIndex[i] , 0);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvTafPdpStatusInd_004
测试用例标题      : 修改上行缓存队列失败，RabId为5，PDP状态为ADS_PDP_STATUS_MODIFY（预置条件：上行上下文被初始化）
预期结果          : 没有找到要处理的队列，不做任何处理
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvTafPdpStatusInd,Test_ADS_UL_RcvTafPdpStatusInd_004)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_MODIFY;
    stPdpStatusInd.ucRabId       = 5;

    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_FALSE;

    MOCKER(ADS_UL_CreateQueue)
        .expects(never());

    MOCKER(ADS_UL_DestroyQueue)
        .expects(never());

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        EXPECT_EQ(pAdsUlCtx->aucPrioIndex[i] , 0);
    }

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvTafPdpStatusInd_005
测试用例标题      : 收到Modem2的消息
预期结果          : 没有找到要处理的队列，不做任何处理
修改历史     :
  3.日    期   : 2015年05月30日
    作    者   : w00281933
    修改内容   : 新建CASEModified for The TSTS Project
*******************************************************************/
TEST_F(Test_ADS_UL_RcvTafPdpStatusInd,Test_ADS_UL_RcvTafPdpStatusInd_005)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I2_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_MODIFY;
    stPdpStatusInd.ucRabId       = 5;

    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_FALSE;

        /* 匹配执行结果 */
    MOCKER(ADS_UL_RcvTafPdpStatusInd)
        .times(1);

    MOCKER(vos_printf)
        .times(any());

    ADS_ShowEntityStats();
            
        
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_ADS_UL_ProcLinkData
功能描述 : ADS_UL_ProcLinkData UT工程类
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_ProcLinkData: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

        /*上行上下文初始化*/
        ADS_InitCtx();

        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_0);
        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_1);
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(31);
    }
    void TearDown()
    {
    }
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_001
测试用例标题      : Modem0，IPF可以配置的BD数为45，第一个队列中有50个数据包
预期结果          : 从第一个队列中取45个数据包，队列剩余5个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_001)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    IMM_ZC_HEAD_STRU                   *pstFreeQueue;
#endif

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    pstFreeQueue = ADS_UL_IPF_SRCMEM_FREE_QUE();
#endif

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的50个数据包 */
    for (i = 0; i < 50; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 50);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    EXPECT_EQ(45, pstFreeQueue->qlen);
#endif
    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_002
测试用例标题      : Modem0，IPF可以配置的BD数为45，第一个队列中有20个数据包，第二个队列中有30个数据包
预期结果          : 从第一个队列中取20个数据包，从第二个队列中取25个数据包，第一个队列变空，第二个队列剩余5个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_002)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 6;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 5);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if 0
/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_003
测试用例标题      : Modem0，IPF可以配置的BD数为45，第一个队列中有26个数据包，第二个队列中有30个数据包
预期结果          : 从第一个队列中取24个数据包，从第二个队列中取21个数据包，第一个队列剩余2个包，第二个队列剩余9个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_003)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 26; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 26);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 6;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num).
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 2);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 9);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_004
测试用例标题      : Modem0，IPF可以配置的BD数为45，第一个队列中有35个数据包，第二个队列不存在，第三个队列存在但无数据，第四个队列中有30个数据包,优先级已初始化
预期结果          : 从第一个队列中取30个数据包，从第四个队列中取15个数据包，第一个队列剩余5个，第四个队列剩余15个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_004)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 35; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 35);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 创建RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    /* 创建RabId为8的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 6;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 销毁RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 15);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_005
测试用例标题      : Modem0，IPF可以配置的BD数为45，第一个队列中有26个数据包，第二个队列不存在，第三个队列存在但无数据，第四个队列中有30个数据包，但是IPF配置失败
预期结果          : 从第一个队列中取26个数据包，从第四个队列中取19个数据包，数据不恢复，第一个队列剩余0个，第四个队列剩余11个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_005)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 26; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 26);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 创建RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    /* 创建RabId为8的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 6;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 销毁RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.ucRabId       = 0x08;

    /* 销毁RabId为8的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_ERROR));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 11);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].usRecordNum, 4);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_006
测试用例标题      : Modem0，IPF可以配置的BD数为45，队列中有90个数据包
预期结果          : 所有数据全部写入IPF，队列清空，不启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_006)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的90个数据包 */
    for (i = 0; i < 90; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    EXPECT_EQ(64, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);
#endif

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_007
测试用例标题      : Modem0，TI_ADS_UL_SEND定时器超时，队列中有10个数据包
预期结果          : 所有数据全部写入IPF，队列清空
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_007)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    REL_TIMER_MSG                       stTimerMsg;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;

    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();
    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的10个数据包 */
    for (i = 0; i < 10; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 10);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    stTimerMsg.ulSenderPid   = VOS_PID_TIMER;
    stTimerMsg.ulReceiverPid = ACPU_PID_ADS_UL;
    stTimerMsg.ulName        = TI_ADS_UL_SEND;

    ADS_UL_ProcMsg((struct MsgCB *)(&stTimerMsg));

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    EXPECT_EQ(10, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);
#endif

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_008
测试用例标题      : Modem0，队列中有90个数据包，前三次获取BD数为0，第四次及以后每次获取BD数为45
预期结果          : 所有数据全部写入IPF，队列清空
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_008)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的90个数据包 */
    for (i = 0; i < 90; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(exactly(1))
        .will(returnValue(0));

    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(never());
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(exactly(1))
        .will(returnValue(0));

    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(never());
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .expects(never())
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));


    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_009
测试用例标题      : Modem0，IPF可以配置的BD数为45，队列中有90个数据包
预期结果          : 当前不允许发送，队列中数据包还是90个
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_009)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* 设置不允许发送 */
    ADS_UL_SET_MODEM_SND_PERMIT_FLAG(ADS_INSTANCE_INDEX_0, VOS_FALSE);
    ADS_UL_SET_MODEM_SND_PERMIT_FLAG(ADS_INSTANCE_INDEX_1, VOS_FALSE);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的90个数据包 */
    for (i = 0; i < 90; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(never());
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(never());
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .expects(never());

    ADS_UL_ProcEvent(ADS_UL_EVENT_DATA_PROC);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if(FEATURE_OFF == FEATURE_SKB_EXP)
/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_011
测试用例标题      : Modem0，IPF可以配置的BD数为45，队列中有90个数据包，
预期结果          : 队列中的数据全部发送完，PDP去激活后源内存全部释放
修改历史     :
1.日   期  : 2012-09-05
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_011)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;
    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();
    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的90个数据包 */
    for (i = 0; i < 90; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(exactly(4))
        .will(returnObjectList(45,64,64,64));
#else
    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(exactly(4))
        .will(returnObjectList(45,64,64,64));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* PDP去激活后，源内存队列为空 */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);
    EXPECT_EQ(0, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_012
测试用例标题      : Modem0，IPF可以配置的BD数为45，第一个队列中有35个数据包，第二个队列不存在，第三个队列存在但无数据，第四个队列中有30个数据包,优先级已初始化
预期结果          : 从第一个队列中取30个数据包，从第四个队列中取15个数据包，第一个队列剩余5个，第四个队列剩余15个包，启动定时器TI_ADS_UL_SEND。第一个PDP去激活后，不会清空源内存队列
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_012)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;
    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();
    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 35; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 35);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 创建RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    /* 创建RabId为8的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 6;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 销毁RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    /* PDP去激活后，源内存队列为空 */
    stPdpStatusInd.ucRabId         = 0x05;
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 15);

    EXPECT_EQ(45, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_013
测试用例标题      : Modem0，IPF可以配置的BD数为45，第一个队列中有35个数据包，第二个队列中有10个数据包,优先级已初始化
预期结果          : 从第一个队列中取30个数据包，从第二个队列中取15个数据包，PDP全部去激活后，数据未搬完，不会清空源内存队列
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_013)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;
    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();
    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 35; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 35);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 6;

    /* 构造RabId5的10个数据包 */
    for (i = 0; i < 10; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 10);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(exactly(1))
        .will(returnValue(63));

    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(exactly(1))
        .will(returnValue(19));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(exactly(1))
        .will(returnValue(63));

    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(exactly(1))
        .will(returnValue(19));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 销毁RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 销毁RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink);

    EXPECT_EQ(45, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_014
测试用例标题      : 两个Modem并发，IPF可以配置的BD数为45，Modem0第一个队列中有20个数据包，Modem1第一个队列中有30个数据包
预期结果          : 从Modem0中取20个数据包，从Modem中取25个数据包，Modem0变空，Modem1剩余5个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_014)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_UL_CTX_STRU                    *pAdsUlCtx1;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    IMM_ZC_HEAD_STRU                   *pstFreeQueue;
#endif

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    pstFreeQueue = ADS_UL_IPF_SRCMEM_FREE_QUE();
#endif

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);
    pAdsUlCtx1 = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 构造数据 */
    ucRabId = 6;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 10; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, 0x45);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 10);
    /*rab6不允许发送*/
    pAdsUlCtx->astAdsUlQueue[6].ucRabSndPermitFlg = VOS_FALSE;

    EXPECT_EQ(pAdsUlCtx1->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx1->astAdsUlQueue[5].pstAdsUlLink->qlen, 30);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 10);
    EXPECT_EQ(pAdsUlCtx1->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    EXPECT_EQ(45, pstFreeQueue->qlen);
#endif

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_021
测试用例标题      : Modem1，IPF可以配置的BD数为45，第一个队列中有50个数据包
预期结果          : 从第一个队列中取45个数据包，队列剩余5个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_021)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    IMM_ZC_HEAD_STRU                   *pstFreeQueue;
#endif

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    pstFreeQueue = ADS_UL_IPF_SRCMEM_FREE_QUE();
#endif

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的50个数据包 */
    for (i = 0; i < 50; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 50);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    EXPECT_EQ(45, pstFreeQueue->qlen);
#endif

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_022
测试用例标题      : Modem1，IPF可以配置的BD数为45，第一个队列中有20个数据包，第二个队列中有30个数据包
预期结果          : 从第一个队列中取20个数据包，从第二个队列中取25个数据包，第一个队列变空，第二个队列剩余5个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_022)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x46;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 5);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_023
测试用例标题      : Modem1，IPF可以配置的BD数为45，第一个队列中有26个数据包，第二个队列中有30个数据包
预期结果          : 从第一个队列中取24个数据包，从第二个队列中取21个数据包，第一个队列剩余2个包，第二个队列剩余9个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_023)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 26; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 26);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x46;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 2);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 9);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_024
测试用例标题      : Modem1，IPF可以配置的BD数为45，第一个队列中有35个数据包，第二个队列不存在，第三个队列存在但无数据，第四个队列中有30个数据包,优先级已初始化
预期结果          : 从第一个队列中取30个数据包，从第四个队列中取15个数据包，第一个队列剩余5个，第四个队列剩余15个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_024)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 35; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 35);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 创建RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    /* 创建RabId为8的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x46;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 销毁RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 15);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_025
测试用例标题      : Modem1，IPF可以配置的BD数为45，第一个队列中有26个数据包，第二个队列不存在，第三个队列存在但无数据，第四个队列中有30个数据包，但是IPF配置失败
预期结果          : 从第一个队列中取26个数据包，从第四个队列中取19个数据包，数据不恢复，第一个队列剩余0个，第四个队列剩余11个包，启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_025)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 26; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 26);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 创建RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    /* 创建RabId为8的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x46;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 销毁RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.ucRabId       = 0x08;

    /* 销毁RabId为8的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_ERROR));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 11);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].usRecordNum, 4);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_026
测试用例标题      : Modem1，IPF可以配置的BD数为45，队列中有90个数据包
预期结果          : 所有数据全部写入IPF，队列清空，不启动定时器TI_ADS_UL_SEND
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_026)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的90个数据包 */
    for (i = 0; i < 90; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    EXPECT_EQ(64, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);
#endif

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_027
测试用例标题      : Modem1，TI_ADS_UL_SEND定时器超时，队列中有10个数据包
预期结果          : 所有数据全部写入IPF，队列清空
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_027)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    REL_TIMER_MSG                       stTimerMsg;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;

    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();
    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的10个数据包 */
    for (i = 0; i < 10; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 10);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    stTimerMsg.ulSenderPid   = VOS_PID_TIMER;
    stTimerMsg.ulReceiverPid = ACPU_PID_ADS_UL;
    stTimerMsg.ulName        = TI_ADS_UL_SEND;

    ADS_UL_ProcMsg((struct MsgCB *)(&stTimerMsg));

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    EXPECT_EQ(10, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);
#endif

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_028
测试用例标题      : Modem1，队列中有90个数据包，前三次获取BD数为0，第四次及以后每次获取BD数为45
预期结果          : 所有数据全部写入IPF，队列清空
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_028)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的90个数据包 */
    for (i = 0; i < 90; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(exactly(1))
        .will(returnValue(0));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(exactly(1))
        .will(returnValue(0));
#endif

    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(never());

    MOCKER(mdrv_ipf_config_ulbd)
        .expects(never())
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));


    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_029
测试用例标题      : Modem1，IPF可以配置的BD数为45，队列中有90个数据包
预期结果          : 当前不允许发送，队列中数据包还是90个
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_029)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* 设置不允许发送 */
    ADS_UL_SET_MODEM_SND_PERMIT_FLAG(ADS_INSTANCE_INDEX_0, VOS_FALSE);
    ADS_UL_SET_MODEM_SND_PERMIT_FLAG(ADS_INSTANCE_INDEX_1, VOS_FALSE);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的90个数据包 */
    for (i = 0; i < 90; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(never());
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(never());
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .expects(never());

    ADS_UL_ProcEvent(ADS_UL_EVENT_DATA_PROC);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if(FEATURE_OFF == FEATURE_SKB_EXP)

/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_031
测试用例标题      : Modem1，IPF可以配置的BD数为45，队列中有90个数据包，
预期结果          : 队列中的数据全部发送完，PDP去激活后源内存全部释放
修改历史     :
1.日   期  : 2012-09-05
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_031)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;
    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();
    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的90个数据包 */
    for (i = 0; i < 90; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

     ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 90);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .expects(exactly(1))
        .will(returnValue(45));

    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(64));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .expects(exactly(1))
        .will(returnValue(45));

    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(64));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* PDP去激活后，源内存队列为空 */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);
    EXPECT_EQ(0, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_032
测试用例标题      : Modem1，IPF可以配置的BD数为45，第一个队列中有35个数据包，第二个队列不存在，第三个队列存在但无数据，第四个队列中有30个数据包,优先级已初始化
预期结果          : 从第一个队列中取30个数据包，从第四个队列中取15个数据包，第一个队列剩余5个，第四个队列剩余15个包，启动定时器TI_ADS_UL_SEND。第一个PDP去激活后，不会清空源内存队列
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_032)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_IPF_CTX_STRU                   *pAdsIpfCtx;
    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();
    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的26个数据包 */
    for (i = 0; i < 35; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 35);

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 创建RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    /* 创建RabId为8的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x46;

    /* 构造RabId5的30个数据包 */
    for (i = 0; i < 30; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 30);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 销毁RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif


    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    /* PDP去激活后，源内存队列为空 */
    stPdpStatusInd.ucRabId         = 0x05;
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 15);

    EXPECT_EQ(45, pAdsIpfCtx->stUlSrcMemFreeQue.qlen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_ADS_UL_ProcLinkData_033
测试用例标题      : 两个Modem并发，IPF可以配置的BD数为45，Modem0第一个队列中有50个数据包，第二个队列中有10个数据包但不允许发送
预期结果          : 从Modem0的第一个队列中取45个数据包
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ProcLinkData,Test_ADS_UL_ProcLinkData_033)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的50个数据包 */
    for (i = 0; i < 50; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 构造数据 */
    ucRabId = 6;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 10; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 50);

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x06);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 10);
    /*rab6不允许发送*/
    pAdsUlCtx->astAdsUlQueue[6].ucRabSndPermitFlg = VOS_FALSE;

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(45));
#else
    MOCKER(mdrv_ipf_get_ulbd_num)
        .stubs()
        .will(returnValue(45));
#endif

    MOCKER(mdrv_ipf_config_ulbd)
        .stubs()
        .with(eq((VOS_UINT32)45))
        .will(returnValue(IPF_SUCCESS));

    ulEvent = ADS_UL_EVENT_DATA_PROC;
    ADS_UL_ProcEvent(ulEvent);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 10);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#endif
#endif
/*****************************************************************************
类名     : Test_ADS_UL_ConfigBD
功能描述 : ADS_UL_ConfigBD UT工程类
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_ConfigBD: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};
/*******************************************************************
测试用例编号      : Test_ADS_UL_ConfigBD_001
测试用例标题      : IPF可以配置的BD数为45，队列中有45个数据包，从队列中取数据异常
预期结果          : 数据未写入IPF，队列中剩余数据包为45
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_ConfigBD,Test_ADS_UL_ConfigBD_01)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的45个数据包 */
    for (i = 0; i < 45; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 45);

    MOCKER(ADS_UL_GetNextQueueNode)
        .stubs()
        .will(returnValue((sk_buff *)VOS_NULL_PTR));

    MOCKER(mdrv_ipf_config_ulbd)
        .expects(never());

    ADS_UL_ConfigBD(45);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 45);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_UL_SendPacket
功能描述 : ADS_UL_SendPacket UT工程类
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_SendPacket: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_001
测试用例标题      : Modem0，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列不存在）
预期结果          : 数据不处理，返回VOS_ERR
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_001)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    /* 构造数据 */
    ucRabId = 5;
    pstData = IMM_ZcStaticAlloc(5);

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);

    EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULCurDataRate);
    EXPECT_EQ(5, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLCurDataRate);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


#if(FEATURE_OFF == FEATURE_SKB_EXP)
/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_002
测试用例标题      : Modem0，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列存在）
预期结果          : 数据插入RabId为5的队列，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_002)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 5;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;
    pstData = IMM_ZcStaticAlloc(5);

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 1);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->next, pstData);
    EXPECT_EQ(VOS_OK, ulRslt);

    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_003
测试用例标题      : Modem0，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列有数据包20个，RabId为6的队列有数据包11个）
预期结果          : 数据插入RabId为5的队列，达到攒包门限，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_003)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);
    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_TRUE;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 5;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 创建RabId为6的队列 */
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 6;

    /* 构造RabId6的11个数据包 */
    for (i = 0; i < 11; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    pstData = IMM_ZcStaticAlloc(10);

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 12);

    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_004
测试用例标题      : Modem0，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列有数据包20个，RabId为6的队列有数据包12个）
预期结果          : 数据插入RabId为5的队列，已达到攒包门限，不重复发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_004)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 5;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 创建RabId为6的队列 */
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 6;

    /* 构造RabId6的20个数据包 */
    for (i = 0; i < 12; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    pstData = IMM_ZcStaticAlloc(10);

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 13);

    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#else
/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_005
测试用例标题      : Modem0，上层模块发送上行数据(TCP/IP协议栈过来的数据)，RabId为5（预置条件：RabId为5的队列存在）
预期结果          : 数据插入RabId为5的队列，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_005)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 5;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;
    pstData = IMM_ZcStaticAlloc(5);
    pstData->private_mem.ucTailPktInd = 0;  /* TCP/IP的数据 */

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 1);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->next, pstData);
    EXPECT_EQ(VOS_OK, ulRslt);

    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_006
测试用例标题      : Modem0，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列有数据包20个，RabId为6的队列有数据包11个）
预期结果          : 数据插入RabId为5的队列，达到攒包门限，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_006)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);
    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_TRUE;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 5;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 创建RabId为6的队列 */
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 6;

    /* 构造RabId6的11个数据包 */
    for (i = 0; i < 11; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    pstData = IMM_ZcStaticAlloc(10);
    pstData->private_mem.ucTailPktInd = 0;  /* TCP/IP的数据 */

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 12);

    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_007
测试用例标题      : Modem0，上层模块发送上行数据(USB过来的数据且为最后一个IP包)，RabId为5（预置条件：RabId为5的队列存在）
预期结果          : 数据插入RabId为5的队列，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_007)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 5;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;
    pstData = IMM_ZcStaticAlloc(5);
    pstData->private_mem.ucTailPktInd = 1;  /* USB过来的最后一个数据 */

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 1);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->next, pstData);
    EXPECT_EQ(VOS_OK, ulRslt);

    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_008
测试用例标题      : Modem0，上层模块发送上行数据(USB过来的数据不是最后一个IP包)，
                    RabId为5（预置条件：RabId为5的队列有数据包20个，RabId为6的队列有数据包11个）
预期结果          : 数据插入RabId为5的队列，达到攒包门限，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_008)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);
    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_TRUE;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 5;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 创建RabId为6的队列 */
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 6;

    /* 构造RabId6的11个数据包 */
    for (i = 0; i < 11; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    pstData = IMM_ZcStaticAlloc(10);
    pstData->private_mem.ucTailPktInd = 2;  /* USB过来的非最后一个数据 */

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 12);

    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_009
测试用例标题      : Modem0，上层模块发送上行数据，RabId为5，数据为空
预期结果          : 数据不处理，返回VOS_ERR
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_009)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    pstData = VOS_NULL_PTR;

    ulRslt = ADS_UL_SendPacket(pstData, 5);

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_010
测试用例标题      : Modem0，上层模块发送上行数据，RabId为1
预期结果          : 数据不处理，返回VOS_ERR
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_010)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;

    pstData = IMM_ZcStaticAlloc(10);

    /* 不会有队列操作 */

    ulRslt = ADS_UL_SendPacket(pstData, 1);

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if(FEATURE_OFF == FEATURE_SKB_EXP)
/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_011
测试用例标题      : Modem0，上层模块发送上行数据，RabId为1，队列长度超过1000
预期结果          : 数据不处理，返回VOS_ERR
修改历史     :
1.日   期  : 2012-09-03
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_011)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 1004; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 512);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_011
测试用例标题      : Modem1，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列不存在）
预期结果          : 数据不处理，返回VOS_ERR
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_101)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    /* 构造数据 */
    ucRabId = 0x45;
    pstData = IMM_ZcStaticAlloc(5);

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);

    EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULCurDataRate);
    EXPECT_EQ(5, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLCurDataRate);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if(FEATURE_OFF == FEATURE_SKB_EXP)
/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_102
测试用例标题      : Modem1，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列存在）
预期结果          : 数据插入RabId为5的队列，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_102)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 5;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;
    pstData = IMM_ZcStaticAlloc(5);

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 1);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->next, pstData);
    EXPECT_EQ(VOS_OK, ulRslt);

    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_103
测试用例标题      : Modem1，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列有数据包20个，RabId为6的队列有数据包11个）
预期结果          : 数据插入RabId为5的队列，达到攒包门限，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_103)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);
    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_TRUE;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 0x45;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 创建RabId为6的队列 */
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 0x46;

    /* 构造RabId6的11个数据包 */
    for (i = 0; i < 11; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    pstData = IMM_ZcStaticAlloc(10);

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 12);

    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_104
测试用例标题      : Modem1，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列有数据包20个，RabId为6的队列有数据包12个）
预期结果          : 数据插入RabId为5的队列，已达到攒包门限，不重复发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_104)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 0x45;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 创建RabId为6的队列 */
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 0x46;

    /* 构造RabId6的20个数据包 */
    for (i = 0; i < 12; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    pstData = IMM_ZcStaticAlloc(10);

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 13);

    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#else
/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_105
测试用例标题      : Modem0，上层模块发送上行数据(TCP/IP协议栈过来的数据)，RabId为5（预置条件：RabId为5的队列存在）
预期结果          : 数据插入RabId为5的队列，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_105)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 5;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;
    pstData = IMM_ZcStaticAlloc(5);
    pstData->private_mem.ucTailPktInd = 0;  /* TCP/IP的数据 */

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 1);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->next, pstData);
    EXPECT_EQ(VOS_OK, ulRslt);

    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_106
测试用例标题      : Modem0，上层模块发送上行数据，RabId为5（预置条件：RabId为5的队列有数据包20个，RabId为6的队列有数据包11个）
预期结果          : 数据插入RabId为5的队列，达到攒包门限，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_106)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);
    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_TRUE;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 0x45;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 创建RabId为6的队列 */
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 0x46;

    /* 构造RabId6的11个数据包 */
    for (i = 0; i < 11; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    pstData = IMM_ZcStaticAlloc(10);
    pstData->private_mem.ucTailPktInd = 0;  /* TCP/IP的数据 */

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 12);

    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_107
测试用例标题      : Modem0，上层模块发送上行数据(USB过来的数据且为最后一个IP包)，RabId为5（预置条件：RabId为5的队列存在）
预期结果          : 数据插入RabId为5的队列，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_107)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 5;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;
    pstData = IMM_ZcStaticAlloc(5);
    pstData->private_mem.ucTailPktInd = 1;  /* USB过来的最后一个数据 */

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 1);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->next, pstData);
    EXPECT_EQ(VOS_OK, ulRslt);

    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_108
测试用例标题      : Modem0，上层模块发送上行数据(USB过来的数据不是最后一个IP包)，
                    RabId为5（预置条件：RabId为5的队列有数据包20个，RabId为6的队列有数据包11个）
预期结果          : 数据插入RabId为5的队列，达到攒包门限，发ID_ADS_UL_DATA_READY消息
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_108)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);
    pAdsUlCtx->stQueuePriNv.ulStatus = VOS_TRUE;

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 0x45;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 20; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 创建RabId为6的队列 */
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ucRabId = 0x46;

    /* 构造RabId6的11个数据包 */
    for (i = 0; i < 11; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ulRslt = ADS_UL_SendPacket(pstData, ucRabId);
    }

    pstData = IMM_ZcStaticAlloc(10);
    pstData->private_mem.ucTailPktInd = 2;  /* USB过来的非最后一个数据 */

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(ADS_UL_SndEvent)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ADS_UL_EVENT_DATA_PROC));

    ulRslt = ADS_UL_SendPacket(pstData, ucRabId);

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 20);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink->qlen, 12);

    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif

/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_109
测试用例标题      : Modem1，上层模块发送上行数据，RabId为5，数据为空
预期结果          : 数据不处理，返回VOS_ERR
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_109)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* VOS_SendMsg 发送ID_ADS_UL_DATA_READY消息*/
    MOCKER(Ps_SendMsg)
        .expects(never());

    pstData = VOS_NULL_PTR;

    ulRslt = ADS_UL_SendPacket(pstData, 0x45);

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_110
测试用例标题      : Modem1，上层模块发送上行数据，RabId为1
预期结果          : 数据不处理，返回VOS_ERR
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_110)
{
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                        *pstData;

    pstData = IMM_ZcStaticAlloc(10);

    /* 不会有队列操作 */

    ulRslt = ADS_UL_SendPacket(pstData, 0x11);

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if(FEATURE_OFF == FEATURE_SKB_EXP)
/*******************************************************************
测试用例编号      : Test_ADS_UL_SendPacket_111
测试用例标题      : Modem1，上层模块发送上行数据，RabId为1，队列长度超过1000
预期结果          : 数据不处理，返回VOS_ERR
修改历史     :
1.日   期  : 2012-09-03
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SendPacket,Test_ADS_UL_SendPacket_111)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的20个数据包 */
    for (i = 0; i < 1004; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 512);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif
#endif
/*****************************************************************************
类名     : Test_ADS_UL_RcvTiDsFlowStatsExpired
功能描述 : ADS_UL_RcvTiDsFlowStatsExpired UT工程类
修改历史     :
1.日   期  : 2012-1-10
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_RcvTiDsFlowStatsExpired: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvTiDsFlowStatsExpired_001
测试用例标题      : 流量统计定时器超时处理，计算ADS数传中当前的速率
预期结果          : 定时器重新启动，流量统计数据清零
修改历史     :
1.日   期  : 2012-1-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvTiDsFlowStatsExpired,Test_ADS_UL_RcvTiDsFlowStatsExpired_001)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    REL_TIMER_MSG                       stTimerMsg;
    VOS_UINT32                          ulUlBpsRate;
    VOS_UINT32                          ulDlBpsRate;
    VOS_UINT32                          i;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_0;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的10个数据包 */
    for (i = 0; i < 10; i++)
    {
        pstData = IMM_ZcStaticAlloc(5);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    stTimerMsg.ulSenderPid   = VOS_PID_TIMER;
    stTimerMsg.ulReceiverPid = ACPU_PID_ADS_UL;
    stTimerMsg.ulName        = TI_ADS_DSFLOW_STATS;

    ADS_UL_ProcMsg((struct MsgCB *)(&stTimerMsg));
    ADS_GetCurrentRate(&ulUlBpsRate,&ulDlBpsRate);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(200, ulUlBpsRate);
    EXPECT_EQ(0, ulDlBpsRate);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvTiDsFlowStatsExpired_002
测试用例标题      : 两个Modem并发，流量统计定时器超时处理，计算ADS数传中当前的速率
预期结果          : 定时器重新启动，流量统计数据清零
修改历史     :
1.日   期  : 2012-1-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_RcvTiDsFlowStatsExpired,Test_ADS_UL_RcvTiDsFlowStatsExpired_002)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    REL_TIMER_MSG                       stTimerMsg;
    VOS_UINT32                          ulUlBpsRate;
    VOS_UINT32                          ulDlBpsRate;
    VOS_UINT32                          i;
    ADS_STATS_INFO_CTX_STRU            *pstAdsStatsInfo;

    pstAdsStatsInfo = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enModemId     = MODEM_ID_1;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的10个数据包 */
    for (i = 0; i < 10; i++)
    {
        pstData = IMM_ZcStaticAlloc(5);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    stTimerMsg.ulSenderPid   = VOS_PID_TIMER;
    stTimerMsg.ulReceiverPid = ACPU_PID_ADS_UL;
    stTimerMsg.ulName        = TI_ADS_DSFLOW_STATS_1;

    ADS_UL_ProcMsg((struct MsgCB *)(&stTimerMsg));

    ulUlBpsRate = pstAdsStatsInfo->stULDataStats.ulULCurDataRate << 3;
    ulDlBpsRate = pstAdsStatsInfo->stDLDataStats.ulDLCurDataRate << 3;

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS_1);

    /* 匹配执行结果 */
    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(200, ulUlBpsRate);
    EXPECT_EQ(0, ulDlBpsRate);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

#if(FEATURE_OFF == FEATURE_SKB_EXP)
/*****************************************************************************
类名     : Test_ADS_UL_FreeIpfUlConfigSuccSrcMem
功能描述 : ADS_UL_FreeIpfUlConfigSuccSrcMem UT工程类
修改历史     :
1.日   期  : 2012-09-05
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_FreeIpfUlConfigSuccSrcMem: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_FreeIpfUlConfigSuccSrcMem_001
测试用例标题      : IPF的busy BD数大于源内存队列的个数
预期结果          : 不释放源内存
修改历史     :
1.日   期  : 2012-05-31
  作   者  : A00165503
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_FreeIpfUlConfigSuccSrcMem, Test_ADS_UL_FreeIpfUlConfigSuccSrcMem_001)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    pstUlFreeQue->qlen = 30;

    MOCKER(mdrv_ipf_get_uldesc_num)
        .stubs()
        .will(returnValue(15));

    MOCKER(IMM_ZcDequeueHead_Debug)
        .expects(never());

    MOCKER(kfree_skb)
        .expects(never());

    ADS_UL_FreeIpfUlConfigSuccSrcMem();

    GlobalMockObject::verify();
}

/*****************************************************************************
类名     : Test_ADS_UL_FreeIpfUlConfigFailSrcMem
功能描述 : ADS_UL_FreeIpfUlConfigFailSrcMem UT工程类
修改历史     :
1.日   期  : 2012-09-05
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_FreeIpfUlConfigFailSrcMem: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_FreeIpfUlConfigFailSrcMem_001
测试用例标题      : 需要释放的内存大于源内存队列的个数
预期结果          : 不释放源内存
修改历史     :
1.日   期  : 2012-05-31
  作   者  : A00165503
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_FreeIpfUlConfigFailSrcMem, Test_ADS_UL_FreeIpfUlConfigFailSrcMem_001)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    pstUlFreeQue->qlen = 30;

    MOCKER(IMM_ZcDequeueHead_Debug)
        .expects(never());

    MOCKER(kfree_skb)
        .expects(never());

    ADS_UL_FreeIpfUlConfigFailSrcMem(35);

    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_FreeIpfUlConfigFailSrcMem_002
测试用例标题      : 源内存队列的个数为0
预期结果          : 不释放源内存
修改历史     :
1.日   期  : 2012-05-31
  作   者  : A00165503
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_FreeIpfUlConfigFailSrcMem, Test_ADS_UL_FreeIpfUlConfigFailSrcMem_002)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    pstUlFreeQue->qlen = 0;

    MOCKER(IMM_ZcDequeueHead_Debug)
        .expects(never());

    MOCKER(kfree_skb)
        .expects(never());

    ADS_UL_FreeIpfUlConfigFailSrcMem(35);

    GlobalMockObject::verify();
}
/*****************************************************************************
类名     : Test_ADS_UL_SetMaxQueueLength
功能描述 : ADS_UL_SetMaxQueueLength UT工程类
修改历史     :
1.日   期  : 2012-09-05
  作   者  : l60609
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_SetMaxQueueLength: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_SetMaxQueueLength_001
测试用例标题      : 需要释放的内存大于源内存队列的个数
预期结果          : 不释放源内存
修改历史     :
1.日   期  : 2012-05-31
  作   者  : A00165503
  修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SetMaxQueueLength, Test_ADS_UL_SetMaxQueueLength_001)
{
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    ADS_UL_SetMaxQueueLength(1000, ADS_INSTANCE_INDEX_0);

    EXPECT_EQ(pstAdsUlCtx->ulUlMaxQueueLength, 1000);

    GlobalMockObject::verify();
}
#endif


/*****************************************************************************
类名       : Test_ADS_UL_RcvCcpuResetStartInd
功能描述   : ADS_UL_RcvCcpuResetStartInd UT工程类
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_RcvCcpuResetStartInd: public ::testing::Test
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
测试用例编号      : Test_ADS_UL_RcvCcpuResetStartInd_001
测试用例标题      : 收到ID_ADS_CCPU_RESET_START_IND
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_ADS_UL_RcvCcpuResetStartInd, Test_ADS_UL_RcvCcpuResetStartInd_001)
{
    ADS_CCPU_RESET_IND_STRU                  stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(ADS_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_ADS_UL;
    stResetInd.ulReceiverPid   = ACPU_PID_ADS_UL;
    stResetInd.enMsgId         = ID_ADS_CCPU_RESET_START_IND;

    /* 桩函数 */
    MOCKER(ADS_ResetUlCtx)
        .expects(exactly(1));

    MOCKER(ADS_FILTER_Reset)
        .expects(exactly(1));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 函数调用 */

    /* 调用入口函数 */
    ADS_UL_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*****************************************************************************
类名       : Test_ADS_UL_RcvAdsUlMsg
功能描述   : ADS_UL_RcvAdsUlMsg UT工程类
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_RcvAdsUlMsg: public ::testing::Test
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
测试用例编号      : Test_ADS_UL_RcvAdsUlMsg_001
测试用例标题      : 收到ID_CCPU_ADS_UL_RESET_END_IND
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_ADS_UL_RcvAdsUlMsg, Test_ADS_UL_RcvAdsUlMsg_001)
{
    ADS_CCPU_RESET_IND_STRU                  stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(ADS_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_ADS_UL;
    stResetInd.ulReceiverPid   = ACPU_PID_ADS_UL;
    stResetInd.enMsgId         = ID_ADS_CCPU_RESET_END_IND;

    /* 桩函数 */
    MOCKER(ADS_InitSpecCtx)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    ADS_UL_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_ADS_UL_RcvAdsUlMsg_002
测试用例标题      : 收到ID_ADS_RESET_MSG_ID_ENUM_BUTT
预期结果          : 返回VOS_ERROR
修改历史   :
1.日   期  : 2013-04-19
  作   者  : f00179208
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_ADS_UL_RcvAdsUlMsg, Test_ADS_UL_RcvAdsUlMsg_002)
{
    ADS_CCPU_RESET_IND_STRU                  stResetInd;

    /* 参数初始化 */

    /* 构造ID_CCPU_RNIC_RESET_START_IND消息 */
    VOS_MemSet(&stResetInd, 0, sizeof(ADS_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_ADS_UL;
    stResetInd.ulReceiverPid   = ACPU_PID_ADS_UL;
    stResetInd.enMsgId         = ID_ADS_MSG_ID_ENUM_BUTT;

    /* 桩函数 */
    MOCKER(ADS_InitSpecCtx)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    ADS_UL_ProcMsg((MsgBlock *)&stResetInd);

    /* 获取结果 */

    /* 参数匹配 */

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/******************************************************************************
类名     : Test_ADS_UL_SendPacketEx
功能描述 : ADS_UL_SendPacketEx UT工程类
修改历史 :
1.日    期 : 2013-6-19
  作    者 : L47619
  修改内容 : V3R3 Share-PDP项目新增类
******************************************************************************/
class Test_ADS_UL_SendPacketEx: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};

/******************************************************************************
测试用例编号: Test_ADS_UL_SendPacketEx_001
测试用例标题: 数据包为空指针
预期结果    : 函数返回VOS_ERR
修改历史    :
 1.日   期  : 2013-6-19
   作   者  : L47619
   修改内容 : V3R3 Share-PDP项目新增用例
******************************************************************************/
TEST_F(Test_ADS_UL_SendPacketEx, Test_ADS_UL_SendPacketEx_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                        *pstData;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;
    VOS_UINT8                           ucRabId;

    // 参数初始化
    pstData  = VOS_NULL_PTR;
    enIpType = ADS_PKT_TYPE_IPV4;
    ucRabId  = 5;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(ADS_FILTER_ProcUlPacket)
        .expects(never());

    MOCKER(ADS_UL_InsertQueue)
        .expects(never());

    // 调用被测函数
    ulRet = ADS_UL_SendPacketEx(pstData, enIpType, ucRabId);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_ADS_UL_SendPacketEx_002
测试用例标题: 未注册下行过滤回调指针
预期结果    : 函数返回VOS_OK
修改历史    :
 1.日   期  : 2013-6-19
   作   者  : L47619
   修改内容 : V3R3 Share-PDP项目新增用例
******************************************************************************/
TEST_F(Test_ADS_UL_SendPacketEx, Test_ADS_UL_SendPacketEx_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                        *pstData;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;

    // 参数初始化
    pstData  = IMM_ZcStaticAlloc(5);
    enIpType = ADS_PKT_TYPE_IPV4;
    ucRabId  = 5;

    // 初始化全局变量
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);
    pstDlRabInfo    = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);
    pstDlRabInfo->ucRabId               = ucRealRabId;
    pstDlRabInfo->pRcvDlFilterDataFunc  = VOS_NULL_PTR;

    // MOCKER操作
    MOCKER(ADS_FILTER_ProcUlPacket)
        .expects(never());

    MOCKER(ADS_UL_InsertQueue)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = ADS_UL_SendPacketEx(pstData, enIpType, ucRabId);

    // 执行检查
    EXPECT_EQ(VOS_OK, ulRet);

    GlobalMockObject::verify();
}

/******************************************************************************
测试用例编号: Test_ADS_UL_SendPacketEx_003
测试用例标题: 已注册下行过滤回调指针
预期结果    : 函数返回VOS_ERR
修改历史    :
 1.日   期  : 2013-6-19
   作   者  : L47619
   修改内容 : V3R3 Share-PDP项目新增用例
******************************************************************************/
TEST_F(Test_ADS_UL_SendPacketEx, Test_ADS_UL_SendPacketEx_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                        *pstData;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;

    // 参数初始化
    pstData  = IMM_ZcStaticAlloc(5);
    enIpType = ADS_PKT_TYPE_IPV4;
    ucRabId  = 5;

    // 初始化全局变量
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);
    pstDlRabInfo    = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);
    pstDlRabInfo->ucRabId               = ucRealRabId;
    pstDlRabInfo->pRcvDlFilterDataFunc  = (RCV_DL_DATA_FUNC)RNIC_SendDlData;

    // MOCKER操作
    MOCKER(ADS_FILTER_ProcUlPacket)
        .expects(exactly(1));

    MOCKER(ADS_UL_InsertQueue)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // 调用被测函数
    ulRet = ADS_UL_SendPacketEx(pstData, enIpType, ucRabId);

    // 执行检查
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}

/******************************************************************************
类名     : Test_ADS_UL_RcvTiDataStatExpired
功能描述 : ADS_UL_RcvTiDataStatExpired UT工程类
修改历史 :
1.日    期 : 2014-6-03
  作    者 : f00179208
  修改内容 : 新增
******************************************************************************/
class Test_ADS_UL_RcvTiDataStatExpired: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();


        /*上行上下文初始化*/
        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};

/******************************************************************************
测试用例编号: Test_ADS_UL_RcvTiDataStatExpired_001
测试用例标题: 数据个数在水线1下
预期结果    : 设置赞包门限1,定时器重新启动
修改历史    :
1.日    期 : 2014-6-03
  作    者 : f00179208
  修改内容 : 新增
******************************************************************************/
TEST_F(Test_ADS_UL_RcvTiDataStatExpired, Test_ADS_UL_RcvTiDataStatExpired_001)
{
    // 变量声明
    VOS_UINT32                          ulTimerName;
    VOS_UINT32                          ulParam;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    // 参数初始化
    ulTimerName = TI_ADS_UL_DATA_STAT;
    ulParam = 0;

    // 初始化全局变量
    ADS_UL_ADD_STAT_PKT_NUM(1);

    // MOCKER操作

    // 调用被测函数
    ADS_UL_RcvTiDataStatExpired(ulTimerName, ulParam);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_DATA_STAT);

    // 执行检查
    EXPECT_EQ(ADS_UL_DATA_THRESHOLD_ONE, ADS_UL_SEND_DATA_NUM_THREDHOLD);

    EXPECT_EQ(enTimerStatus, ADS_TIMER_STATUS_RUNNING);

    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_ADS_UL_RcvTiDataStatExpired_002
测试用例标题: 数据个数在水线1与水线2间
预期结果    : 设置赞包门限2,定时器重新启动
修改历史    :
1.日    期 : 2014-6-03
  作    者 : f00179208
  修改内容 : 新增
******************************************************************************/
TEST_F(Test_ADS_UL_RcvTiDataStatExpired, Test_ADS_UL_RcvTiDataStatExpired_002)
{
    // 变量声明
    VOS_UINT32                          ulTimerName;
    VOS_UINT32                          ulParam;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    // 参数初始化
    ulTimerName = TI_ADS_UL_DATA_STAT;
    ulParam = 0;

    // 初始化全局变量
    ADS_UL_ADD_STAT_PKT_NUM(100);


    // MOCKER操作

    // 调用被测函数
    ADS_UL_RcvTiDataStatExpired(ulTimerName, ulParam);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_DATA_STAT);

    // 执行检查
    EXPECT_EQ(ADS_UL_DATA_THRESHOLD_TWO, ADS_UL_SEND_DATA_NUM_THREDHOLD);

    EXPECT_EQ(enTimerStatus, ADS_TIMER_STATUS_RUNNING);

    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_ADS_UL_RcvTiDataStatExpired_003
测试用例标题: 数据个数在水线2与水线3
预期结果    : 设置赞包门限3,定时器重新启动
修改历史    :
1.日    期 : 2014-6-03
  作    者 : f00179208
  修改内容 : 新增
******************************************************************************/
TEST_F(Test_ADS_UL_RcvTiDataStatExpired, Test_ADS_UL_RcvTiDataStatExpired_003)
{
    // 变量声明
    VOS_UINT32                          ulTimerName;
    VOS_UINT32                          ulParam;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    // 参数初始化
    ulTimerName = TI_ADS_UL_DATA_STAT;
    ulParam = 0;

    // 初始化全局变量
    ADS_UL_ADD_STAT_PKT_NUM(200);


    // MOCKER操作

    // 调用被测函数
    ADS_UL_RcvTiDataStatExpired(ulTimerName, ulParam);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_DATA_STAT);

    // 执行检查
    EXPECT_EQ(ADS_UL_DATA_THRESHOLD_THREE, ADS_UL_SEND_DATA_NUM_THREDHOLD);

    EXPECT_EQ(enTimerStatus, ADS_TIMER_STATUS_RUNNING);

    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_ADS_UL_RcvTiDataStatExpired_004
测试用例标题: 数据个数在水线3以上
预期结果    : 设置赞包门限4,定时器重新启动
修改历史    :
1.日    期 : 2014-6-03
  作    者 : f00179208
  修改内容 : 新增
******************************************************************************/
TEST_F(Test_ADS_UL_RcvTiDataStatExpired, Test_ADS_UL_RcvTiDataStatExpired_004)
{
    // 变量声明
    VOS_UINT32                          ulTimerName;
    VOS_UINT32                          ulParam;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    // 参数初始化
    ulTimerName = TI_ADS_UL_DATA_STAT;
    ulParam = 0;

    // 初始化全局变量
    ADS_UL_ADD_STAT_PKT_NUM(600);

    // MOCKER操作

    // 调用被测函数
    ADS_UL_RcvTiDataStatExpired(ulTimerName, ulParam);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_DATA_STAT);

    // 执行检查
    EXPECT_EQ(ADS_UL_DATA_THRESHOLD_FOUR, ADS_UL_SEND_DATA_NUM_THREDHOLD);

    EXPECT_EQ(enTimerStatus, ADS_TIMER_STATUS_RUNNING);

    GlobalMockObject::verify();
}


/******************************************************************************
测试用例编号: Test_ADS_UL_RcvTiDataStatExpired_005
测试用例标题: 无数据包
预期结果    : 设置赞包门限1,定时器不再启动
修改历史    :
1.日    期 : 2014-6-03
  作    者 : f00179208
  修改内容 : 新增
******************************************************************************/
TEST_F(Test_ADS_UL_RcvTiDataStatExpired, Test_ADS_UL_RcvTiDataStatExpired_005)
{
    // 变量声明
    VOS_UINT32                          ulTimerName;
    VOS_UINT32                          ulParam;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    // 参数初始化
    ulTimerName = TI_ADS_UL_DATA_STAT;
    ulParam = 0;

    // 初始化全局变量
    ADS_UL_ADD_STAT_PKT_NUM(0);

    // MOCKER操作

    // 调用被测函数
    ADS_UL_RcvTiDataStatExpired(ulTimerName, ulParam);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_UL_DATA_STAT);

    // 执行检查
    EXPECT_EQ(ADS_UL_DATA_THRESHOLD_ONE, ADS_UL_SEND_DATA_NUM_THREDHOLD);

    EXPECT_EQ(enTimerStatus, ADS_TIMER_STATUS_STOP);

    GlobalMockObject::verify();
}

