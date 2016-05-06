#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsCtx.h"

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

VOS_VOID TEST_ADS_Set_QueuePriNv(VOS_UINT8 ucIndex)
{
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ucIndex);

    pstAdsUlCtx->stQueuePriNv.ulStatus = VOS_TRUE;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[0] = 9;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[1] = 8;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[2] = 7;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[3] = 6;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[4] = 5;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[5] = 4;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[6] = 3;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[7] = 2;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[8] = 1;

}


/*****************************************************************************
类名     : Test_ADS_UL_CreateQueue
功能描述 : ADS_UL_CreateQueue UT工程类
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_CreateQueue: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

        /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
        stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
        stPdpStatusInd.enModemId     = MODEM_ID_0;
        stPdpStatusInd.ucRabId       = 0x05;
        stPdpStatusInd.enPdpType     = ADS_PDP_PPP;

        PS_MEM_SET(&stPdpStatusInd2, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

        /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
        stPdpStatusInd2.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd2.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd2.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd2.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd2.enQciType     = ADS_QCI_TYPE_QCI1_GBR;
        stPdpStatusInd2.enModemId      = MODEM_ID_0;
        stPdpStatusInd2.ucRabId       = 0x08;
        stPdpStatusInd2.enPdpType     = ADS_PDP_PPP;

        /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
        stPdpStatusInd3.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd3.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd3.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd3.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd3.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
        stPdpStatusInd3.enModemId     = MODEM_ID_0;
        stPdpStatusInd3.ucRabId       = 0x07;
        stPdpStatusInd3.enPdpType     = ADS_PDP_PPP;

        /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
        stPdpStatusInd4.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd4.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd4.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd4.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd4.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
        stPdpStatusInd4.enModemId     = MODEM_ID_0;
        stPdpStatusInd4.ucRabId       = 0x05;
        stPdpStatusInd4.enPdpType     = ADS_PDP_PPP;

        /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
        stPdpStatusInd5.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd5.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd5.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd5.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd5.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
        stPdpStatusInd5.enModemId     = MODEM_ID_0;
        stPdpStatusInd5.ucRabId       = 0x05;
        stPdpStatusInd5.enPdpType     = ADS_PDP_PPP;

        ADS_InitCtx();

        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_0);
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_1);
#endif

    }
    void TearDown()
    {
    }

protected:

    IMM_ZC_HEAD_STRU                    stULQueue;
    IMM_ZC_HEAD_STRU                    stULQueue2;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd2;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd3;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd4;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd5;
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_001
测试用例标题      : Modem0，创建RabId为5的上行缓存队列（预置条件：上行上下文被初始化）
预期结果          : 队列创建成功，RabId和队列指针保存到g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.astAdsUlQueue[0]中
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_001)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* 场景配置 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)&stULQueue));

    /* 测试函数调用 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_002
测试用例标题      : Modem0，创建RabId为5的上行缓存队列（预置条件：RabId为5的队列已创建, 但优先级比之前创建的要低）
预期结果          : 不能重复创建，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.astAdsUlQueue[5].enPrio的值不变
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_002)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* 场景配置 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* 测试函数调用 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd4));

    /* 匹配执行结果 */
    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_003
测试用例标题      : Modem0，创建RabId为5的上行缓存队列（预置条件：RabId为5的队列已创建, 但优先级比之前创建的要高）
预期结果          : 不能重复创建，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.astAdsUlQueue[5].enPrio的值修改为优先级高的
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_003)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* 场景配置 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* 测试函数调用 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd5));

    /* 匹配执行结果 */
    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#if 0
/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_004
测试用例标题      : Modem0，创建RabId为8的上行缓存队列（预置条件：RabId为5的队列已创建,RABID8队列的优先级比较高）
预期结果          : g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.aucPrioIndex[0]存的是后注册的RABID为8的值，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.aucPrioIndex[1]值为5
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_004)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd2));

    /* 匹配执行结果 */
    //EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x05);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    //EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x08);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].ucIsQueueValid, VOS_TRUE);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].pstAdsUlLink->qlen, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_005
测试用例标题      : Modem0，创建RabId为9的上行缓存队列（预置条件：无空闲队列, 该次的优先级比之前的要高）
预期结果          : 优先级修改成功
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_005)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 构造队列满 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        stPdpStatusInd.ucRabId       = 5 + i;
        stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI1_GBR + (i % ADS_QCI_TYPE_BUTT);

        ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    }

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 14);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 6);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 15);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[4] , 7);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[5] , 8);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[6] , 9);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[7] , 10);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[8] , 11);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[9] , 12);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[10], 13);

    stPdpStatusInd.ucRabId       = 0x09;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[5] , 9);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[6] , 8);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio, ADS_QCI_TYPE_QCI1_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[7].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].enPrio, ADS_QCI_TYPE_QCI4_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[9].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[10].enPrio, ADS_QCI_TYPE_QCI6_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[11].enPrio, ADS_QCI_TYPE_QCI7_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[12].enPrio, ADS_QCI_TYPE_QCI8_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[13].enPrio, ADS_QCI_TYPE_QCI9_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[14].enPrio, ADS_QCI_TYPE_QCI1_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[15].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[9].pstAdsUlLink->qlen, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_006
测试用例标题      : Modem0，创建RabId为6的上行缓存队列（预置条件：内存申请失败）
预期结果          : 创建队列失败
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_006)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* 构造队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 内存申请失败 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd2));

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[8].pstAdsUlLink);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)

/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_011
测试用例标题      : Modem1，创建RabId为5的上行缓存队列（预置条件：上行上下文被初始化）
预期结果          : 队列创建成功，RabId和队列指针保存到g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.astAdsUlQueue[0]中
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_011)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* 场景配置 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* 测试函数调用 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS_1);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_012
测试用例标题      : Modem1，创建RabId为5的上行缓存队列（预置条件：RabId为5的队列已创建, 但优先级比之前创建的要低）
预期结果          : 不能重复创建，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.astAdsUlQueue[5].enPrio的值不变
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_012)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* 场景配置 */
    MOCKER(V_MemAlloc).stubs()
          .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* 测试函数调用 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId = MODEM_ID_1;

    stPdpStatusInd4.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd4.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd4));

    /* 匹配执行结果 */
    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_013
测试用例标题      : Modem1，创建RabId为5的上行缓存队列（预置条件：RabId为5的队列已创建, 但优先级比之前创建的要高）
预期结果          : 不能重复创建，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.astAdsUlQueue[5].enPrio的值修改为优先级高的
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_013)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* 场景配置 */
    MOCKER(V_MemAlloc).stubs()
          .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* 测试函数调用 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId = MODEM_ID_1;

    stPdpStatusInd5.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd5.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd5));

    /* 匹配执行结果 */
    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}
#if 0
/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_014
测试用例标题      : Modem1，创建RabId为8的上行缓存队列（预置条件：RabId为5的队列已创建,RABID8队列的优先级比较高）
预期结果          : g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.aucPrioIndex[0]存的是后注册的RABID为8的值，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.aucPrioIndex[1]值为5
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_014)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId = MODEM_ID_1;

    stPdpStatusInd2.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd2.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd2));

    /* 匹配执行结果 */
    //EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x05);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    //EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x08);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].ucIsQueueValid, VOS_TRUE);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].pstAdsUlLink->qlen, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_015
测试用例标题      : Modem1，创建RabId为9的上行缓存队列（预置条件：无空闲队列, 该次的优先级比之前的要高）
预期结果          : 优先级修改成功
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_015)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 构造队列满 */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        stPdpStatusInd.ucRabId       = 5 + i;
        stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI1_GBR + (i % ADS_QCI_TYPE_BUTT);


        stPdpStatusInd.enModemId = MODEM_ID_1;

        ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    }

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 14);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 6);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 15);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[4] , 7);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[5] , 8);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[6] , 9);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[7] , 10);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[8] , 11);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[9] , 12);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[10], 13);

    stPdpStatusInd.ucRabId       = 0x09;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;

    /* 创建RabId为6的队列 */
    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[5] , 9);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[6] , 8);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio, ADS_QCI_TYPE_QCI1_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[7].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].enPrio, ADS_QCI_TYPE_QCI4_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[9].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[10].enPrio, ADS_QCI_TYPE_QCI6_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[11].enPrio, ADS_QCI_TYPE_QCI7_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[12].enPrio, ADS_QCI_TYPE_QCI8_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[13].enPrio, ADS_QCI_TYPE_QCI9_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[14].enPrio, ADS_QCI_TYPE_QCI1_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[15].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[9].pstAdsUlLink->qlen, 0);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_ADS_UL_CreateQueue_016
测试用例标题      : Modem1，创建RabId为6的上行缓存队列（预置条件：内存申请失败）
预期结果          : 创建队列失败
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_016)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* 构造队列 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 内存申请失败 */
    MOCKER(V_MemAlloc)
        .expects(exactly(1))
        .will(returnValue((void *)VOS_NULL_PTR));

    /* 创建RabId为6的队列 */
    stPdpStatusInd2.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd2.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd2));

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[8].pstAdsUlLink);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#endif

/*****************************************************************************
类名     : Test_ADS_UL_DestroyQueue
功能描述 : ADS_UL_DestroyQueue UT工程类
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_DestroyQueue: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(VOS_GetSlice)
            .defaults()
            .will(returnValue((VOS_INT64)0xffffffff));

        PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

        /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
        stPdpStatusInd.ulSenderPid                          = WUEPS_PID_TAF;
        stPdpStatusInd.ulReceiverPid                        = ACPU_PID_ADS_UL;
        stPdpStatusInd.enMsgId                              = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd.enPdpStatus                          = ADS_PDP_STATUS_DEACT;
        stPdpStatusInd.ucRabId                              = 0x05;

        pstULQueue                                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_ADS_UL,
                                                                         sizeof(IMM_ZC_HEAD_STRU));

        ADS_InitCtx();
        IMM_ZcQueueHeadInit(pstULQueue);

        /*已激活0x05*/

        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_0);
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_1);
#endif

    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();

        GlobalMockObject::verify();
    }

protected:

    IMM_ZC_HEAD_STRU                    *pstULQueue;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
};

/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_001
测试用例标题      : Modem0，销毁RabId为6的队列（预置条件：只有RabId为5的队列已创建）
预期结果          : RabId为6的队列不存在，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.astAdsUlQueue的值不变
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_001)
{
    /* 输入码流配置 */
    stPdpStatusInd.ucRabId                              = 0x06;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    pstAdsUlCtx->aucPrioIndex[0] = 5;
    pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = pstULQueue;
    pstAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;
    pstAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid = VOS_TRUE;

    /* 场景配置 */
    MOCKER(V_MemAlloc).stubs()
          .will(returnValue((VOS_VOID *)(pstULQueue)));

    /* 测试函数调用 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pstAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink, pstULQueue);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_002
测试用例标题      : Modem0，销毁RabId为5的队列（预置条件：RabId为5的队列已创建，在上下文中的index为5，队列中没有数据）
预期结果          : RabId为5的队列被销毁，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.astAdsUlQueue[0]置为无效值
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_002)
{
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pstAdsUlCtx->aucPrioIndex[0] = 5;
    pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = pstULQueue;
    pstAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;

    /* 输入码流配置 */

    /* 场景配置 */

    /* 测试函数调用 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pstAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_003
测试用例标题      : Modem0，销毁RabId为5的队列（预置条件：RabId为5的队列已创建，在上下文中的index为5，队列中有5个数据）
预期结果          : RabId为5的队列中数据被释放，队列被销毁，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.astAdsUlQueue[5]置为无效值
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_003)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx    = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

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

    /* 构造RabId5的5个数据包 */
    for (i = 0; i < 5; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 销毁RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_FALSE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_004
测试用例标题      : Modem0，销毁RabId为6的队列（预置条件：RabId为5，6，7的队列已创建，销毁6，再创建8）
预期结果          : RabId8存入g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.astAdsUlQueue[1]
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_004)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    MOCKER(V_StartRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI1_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 创建RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 5;

    /* 构造RabId5的5个数据包 */
    for (i = 0; i < 5; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 10;

    /* 销毁RabId为6的队列 */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 7);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].ucIsQueueValid, VOS_FALSE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);

    /* 创建RabId为8的队列 */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 7);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 8);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 5);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_005
测试用例标题      : Modem0，销毁RabId为5的队列（预置条件：RabId为5的结点存在，但是队列为空）
预期结果          : RabId为5的队列被销毁，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_0].stAdsUlCtx.astAdsUlQueue[0]置为无效值
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_005)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    pAdsUlCtx->aucPrioIndex[0] = 5;
    /* 构造结点存在，但是队列为空 */
    pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = VOS_NULL_PTR;
    pAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;
    pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid = VOS_TRUE;

    /* 测试函数调用 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if(FEATURE_ON == FEATURE_MULTI_MODEM)

/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_011
测试用例标题      : Modem1，销毁RabId为6的队列（预置条件：只有RabId为5的队列已创建）
预期结果          : RabId为6的队列不存在，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.astAdsUlQueue的值不变
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_011)
{
    /* 输入码流配置 */
    stPdpStatusInd.ucRabId                              = 0x06;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    pstAdsUlCtx->aucPrioIndex[0] = 5;
    pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = pstULQueue;
    pstAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;
    pstAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid = VOS_TRUE;

    /* 场景配置 */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)(pstULQueue)));

    /* 测试函数调用 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pstAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink, pstULQueue);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_012
测试用例标题      : Modem1，销毁RabId为5的队列（预置条件：RabId为5的队列已创建，在上下文中的index为5，队列中没有数据）
预期结果          : RabId为5的队列被销毁，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.astAdsUlQueue[0]置为无效值
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_012)
{
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pstAdsUlCtx->aucPrioIndex[0] = 5;
    pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = pstULQueue;
    pstAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;

    /* 输入码流配置 */

    /* 场景配置 */

    /* 测试函数调用 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pstAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_013
测试用例标题      : Modem1，销毁RabId为5的队列（预置条件：RabId为5的队列已创建，在上下文中的index为5，队列中有5个数据）
预期结果          : RabId为5的队列中数据被释放，队列被销毁，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.astAdsUlQueue[5]置为无效值
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_013)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx    = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的5个数据包 */
    for (i = 0; i < 5; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 销毁RabId为5的队列 */
    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_FALSE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_014
测试用例标题      : Modem1，销毁RabId为6的队列（预置条件：RabId为5，6，7的队列已创建，销毁6，再创建8）
预期结果          : RabId8存入g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.astAdsUlQueue[1]
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_014)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* 构造ID_APS_ADS_PDP_STATUS_IND消息 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x05;

    /* 创建RabId为5的队列 */
    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI1_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* 创建RabId为6的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* 创建RabId为7的队列 */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* 构造数据 */
    ucRabId = 0x45;

    /* 构造RabId5的5个数据包 */
    for (i = 0; i < 5; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 10;

    /* 销毁RabId为6的队列 */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 7);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].ucIsQueueValid, VOS_FALSE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS_1);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);

    /* 创建RabId为8的队列 */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 7);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 8);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 5);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_ADS_UL_DestroyQueue_015
测试用例标题      : Modem1，销毁RabId为5的队列（预置条件：RabId为5的结点存在，但是队列为空）
预期结果          : RabId为5的队列被销毁，g_stAdsCtx.astAdsSpecCtx[ADS_INSTANCE_INDEX_1].stAdsUlCtx.astAdsUlQueue[0]置为无效值
修改历史     :
1.日   期  : 2011-12-10
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_015)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    pAdsUlCtx->aucPrioIndex[0] = 5;
    /* 构造结点存在，但是队列为空 */
    pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = VOS_NULL_PTR;
    pAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;
    pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid = VOS_TRUE;

    /* 测试函数调用 */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


    /* 匹配执行结果 */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名     : Test_ADS_UL_SetProtectTmrLen
功能描述 : ADS_UL_SetProtectTmrLen UT工程类
修改历史     :
1.日   期  : 2013-1-4
作   者  :   l60609
修改内容 : 新生成类
*****************************************************************************/
class Test_ADS_UL_SetProtectTmrLen: public ::testing::Test
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
测试用例编号      : Test_ADS_UL_SetProtectTmrLen_001
测试用例标题      : ADS任务初始化
预期结果          : ADS上下行PID、下行自处理任务注册成功，返回VOS_OK
修改历史     :
1.日   期  : 2013-1-4
作   者  :   l60609
修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_ADS_UL_SetProtectTmrLen,Test_ADS_UL_SetProtectTmrLen_001)
{
    ADS_IPF_CTX_STRU                    *pAdsIpfCtx;

    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();

    ADS_UL_SetProtectTmrLen(10);

    EXPECT_EQ(10, pAdsIpfCtx->ulProtectTmrLen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

