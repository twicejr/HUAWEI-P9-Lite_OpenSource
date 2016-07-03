#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_CsdUpLink.h"


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

#if 0

#if( FEATURE_ON == FEATURE_CSD )

class Test_CSD_UL_ProcMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        CSD_InitCtx();

        PS_MEM_SET(&stCallStateInd, 0x00, sizeof(AT_CSD_CALL_STATE_TYPE_IND_STRU));

        /* 填写消息头 */
        stCallStateInd.ulSenderPid     = WUEPS_PID_AT;
        stCallStateInd.ulReceiverCpuId = VOS_LOCAL_CPUID;
        stCallStateInd.ulReceiverPid   = ACPU_PID_CSD;
        stCallStateInd.enMsgId         = ID_AT_CSD_CALL_STATE_IND;
    }
    void TearDown()
    {
    }

protected:

    AT_CSD_CALL_STATE_TYPE_IND_STRU stCallStateInd;

};


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtMsg_001 )
{
    /* 输入码流配置 */
    stCallStateInd.enMsgId      = ID_AT_CSD_MSG_ID_ENUM_BUTT;

    /* 场景配置 */
    MOCKER(CSD_UL_RcvAtCallStateInd)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg((struct MsgCB *)(&stCallStateInd));

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcMsg_001 )
{
    /* 输入码流配置 */
    MsgBlock* pMsg;

    pMsg            = VOS_NULL_PTR;

    /* 场景配置 */
    MOCKER(CSD_UL_RcvAtMsg)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg(pMsg);

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcMsg_002 )
{
    /* 输入码流配置 */
    stCallStateInd.ulSenderPid      = ACPU_PID_CSD;

    /* 场景配置 */
    MOCKER(CSD_UL_RcvAtMsg)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateInd_001 )
{
    /* 输入码流配置 */
    stCallStateInd.enCallState      = AT_CSD_CALL_STATE_BUTT;

    /* 场景配置 */
    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    MOCKER(CSD_UL_RcvAtCallStateOff)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateOn_001 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;


    /* 输入码流配置 */
    stCallStateInd.enCallState           = AT_CSD_CALL_STATE_ON;

    /* 场景配置 */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                        sizeof(IMM_ZC_HEAD_STRU));

    MOCKER(V_MemAlloc)
          .will(returnValue(pstULQueue));

    MOCKER(CSD_UL_RcvAtCallStateOff)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pstULQueue, CSD_UL_GetQueue());
    EXPECT_EQ(AT_CSD_CALL_STATE_ON, CSD_GetCallState());

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateOff_001 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;

    pstULQueue                           =(IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                        sizeof(IMM_ZC_HEAD_STRU));
    /* 输入码流配置 */
    stCallStateInd.enCallState           = AT_CSD_CALL_STATE_OFF;

    /* 场景配置 */
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    CSD_UL_SetQueue(pstULQueue);

    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateOff_002 )
{
    /* 输入码流配置 */
    stCallStateInd.enCallState      = AT_CSD_CALL_STATE_OFF;

    /* 场景配置 */
    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());


    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));


    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());


    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateOff_003 )
{
    IMM_ZC_HEAD_STRU                   *pstULQueue;

    /* 输入码流配置 */
    stCallStateInd.enCallState          = AT_CSD_CALL_STATE_OFF;

    /* 场景配置 */
    pstULQueue                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    pstULQueue->qlen                   = 1;


    CSD_UL_SetQueue(pstULQueue);

    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_FreeQueue_001 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;
    IMM_ZC_STRU                         *pstCmpZcData;

    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    pstCmpZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* 输入码流配置 */
    stCallStateInd.enCallState           = AT_CSD_CALL_STATE_OFF;

    /* 场景配置 */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstCmpZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(),pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    MOCKER(kfree_skb)
        .with(mirror(pstCmpZcData, sizeof(IMM_ZC_STRU)));

    MOCKER(V_MemFree)
        .expects(exactly(1));

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_FreeQueue_002 )
{
    IMM_ZC_HEAD_STRU                         *pstULQueue;

    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    /* 输入码流配置 */
    stCallStateInd.enCallState           = AT_CSD_CALL_STATE_OFF;

    /* 场景配置 */
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    pstULQueue->qlen                   = 0x01;

    CSD_UL_SetQueue(pstULQueue);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    MOCKER(kfree_skb)
          .expects(never());

    MOCKER(V_MemFree)
          .expects(exactly(1));

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_FreeQueue_003 )
{
    IMM_ZC_HEAD_STRU                   *pstULQueue;
    IMM_ZC_STRU                        *pstZcData;
    IMM_ZC_STRU                         *pstCmpZcData;


    pstULQueue                          = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                         sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                         sizeof(IMM_ZC_STRU));
    pstCmpZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* 输入码流配置 */
    stCallStateInd.enCallState          = AT_CSD_CALL_STATE_OFF;

    /* 场景配置 */
    PS_MEM_SET(pstCmpZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(),pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_RcvAtCallStateOn)
        .expects(never());

    MOCKER(kfree_skb)
        .with(mirror(pstCmpZcData, sizeof(IMM_ZC_STRU)));
#if (FEATURE_IMM_MEM_DEBUG)
    MOCKER(skb_queue_tail_debug)
        .will(returnValue(VOS_NULL_PTR));
#else
    MOCKER(skb_queue_tail)
        .will(returnValue(VOS_NULL_PTR));
#endif

    MOCKER(V_MemFree)
        .expects(exactly(1));

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_InitQueue_001 )
{
    /* 输入码流配置 */
    stCallStateInd.enCallState          = AT_CSD_CALL_STATE_ON;

    /* 场景配置 */
    MOCKER(CSD_UL_RcvAtCallStateOff)
          .expects(never());

    MOCKER(V_MemAlloc)
           .will(returnValue(VOS_NULL_PTR));

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_InitQueue_002 )
{
    IMM_ZC_HEAD_STRU                         *pstULQueue;

    /* 输入码流配置 */
    stCallStateInd.enCallState          = AT_CSD_CALL_STATE_ON;

    /* 场景配置 */

    pstULQueue                          = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    MOCKER(CSD_UL_RcvAtCallStateOff)
      .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* 匹配执行结果 */
    EXPECT_EQ(pstULQueue, CSD_UL_GetQueue());
    EXPECT_EQ(AT_CSD_CALL_STATE_ON, CSD_GetCallState());

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_InsertQueue_001 )
{
    IMM_ZC_STRU                        *pstZcData;

    /* 输入码流配置 */
    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));

    pstZcData->data                     = (VOS_UINT8 *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                    4);
    pstZcData->len                      = 4;

    /* 场景配置 */
    MOCKER(kfree_skb)
        .with(mirror(pstZcData, sizeof(IMM_ZC_STRU)));

    /* 测试函数调用 */
    CSD_UL_SendData(pstZcData);

    /* 匹配执行结果 */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_InsertQueue_003 )
{
    IMM_ZC_STRU                        *pstZcData;
    IMM_ZC_HEAD_STRU                   *pstULQueue;

    /* 输入码流配置 */
    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                sizeof(IMM_ZC_STRU));

    pstULQueue                          = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                        sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));

    pstZcData->data                     = (VOS_UINT8 *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                    4);
    pstZcData->len                      = 4;

    /* 场景配置 */
    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    MOCKER(VOS_SmV)
        .with(eq(CSD_GetUpLinkDataSem()))
        .expects(exactly(1));

    /* 测试函数调用 */
    CSD_UL_SendData(pstZcData);

    /* 匹配执行结果 */
    EXPECT_EQ(pstULQueue, CSD_UL_GetQueue());
    EXPECT_EQ(1, CSD_UL_GetQueue()->qlen);
    EXPECT_EQ(AT_CSD_CALL_STATE_ON, CSD_GetCallState());

}



TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcDataTask_001 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_ERR));


    MOCKER(CSD_UL_CalcIsrSlice)
          .expects(never());

    MOCKER(CSD_UL_SendDataToDICC)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcDataTask_002 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));


    MOCKER(CSD_UL_CalcIsrSlice)
          .expects(never());

    MOCKER(CSD_UL_SendDataToDICC)
          .expects(never());

    CSD_SetCallState(AT_CSD_CALL_STATE_OFF);

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcDataTask_003 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnObjectList(CSD_MAX_SLICE_CNT - 100, CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .with(eq(CSD_UL_TASK_DELAY_TIME));

    MOCKER(CSD_UL_SendDataToDICC)
          .expects(exactly(1));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendData_001 )
{
    IMM_ZC_HEAD_STRU                   *pstULQueue;

    /* 输入码流配置 */
    pstULQueue                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    /* 场景配置 */
    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_InsertQueue)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_SendData(VOS_NULL_PTR);


    /* 匹配执行结果 */
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendData_002 )
{
    IMM_ZC_STRU                        *pstZcData;
    IMM_ZC_HEAD_STRU                   *pstULQueue;

    /* 输入码流配置 */
    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_STRU));

    pstULQueue                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));

    pstZcData->data                     = VOS_NULL_PTR;
    pstZcData->len                      = 4;

    /* 场景配置 */
    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_InsertQueue)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_SendData(pstZcData);

    /* 匹配执行结果 */
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendData_003 )
{
    IMM_ZC_STRU                        *pstZcData;
    IMM_ZC_HEAD_STRU                        *pstULQueue;

    /* 输入码流配置 */
    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_STRU));

    pstULQueue                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));

    pstZcData->data                     = (VOS_UINT8 *)PS_MEM_ALLOC(ACPU_PID_CSD, 4);;
    pstZcData->len                      = 0;

    /* 场景配置 */
    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_InsertQueue)
          .expects(never());

    /* 测试函数调用 */
    CSD_UL_SendData(pstZcData);


    /* 匹配执行结果 */
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_001 )
{

    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;

    /* 输入码流配置 */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* 场景配置 */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(), pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .will(returnObjectList(0,1));

    MOCKER(DICC_TriggerChanDataTx)
           .expects(exactly(2));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_002 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;

    /* 输入码流配置 */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* 场景配置 */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(), pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(1));

    MOCKER(DICC_InsertChannelDataAction)
          .expects(exactly(1))
          .will(returnValue(DICC_ERR_BUTT));

    MOCKER(IMM_MemFree_Debug)
          .expects(exactly(1));

    MOCKER(DICC_TriggerChanDataTx)
           .expects(exactly(1));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_003 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;

    /* 输入码流配置 */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* 场景配置 */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(), pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .will(returnValue(1));

    MOCKER(DICC_InsertChannelDataAction)
          .will(returnValue(DICC_OK));

    MOCKER(DICC_TriggerChanDataTx)
           .expects(exactly(1));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_004 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;

    /* 输入码流配置 */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* 场景配置 */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(), pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(1));

    MOCKER(DICC_InsertChannelDataAction)
          .expects(exactly(1))
          .will(returnValue(DICC_OK));

    MOCKER(DICC_TriggerChanDataTx)
           .expects(exactly(1))
           .will(returnValue(DICC_ERR_BUTT));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_005 )
{
    IMM_ZC_HEAD_STRU                         *pstULQueue;

    /* 输入码流配置 */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    /* 场景配置 */
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);


    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .will(returnValue(1));


    MOCKER(DICC_InsertChannelDataAction)
          .expects(never());

    MOCKER(DICC_TriggerChanDataTx)
           .expects(never());

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();

}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_006 )
{
    IMM_ZC_HEAD_STRU                         *pstULQueue;

    /* 输入码流配置 */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    /* 场景配置 */
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);


    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .will(returnValue(DICC_INVALID_VALUE));


    MOCKER(DICC_InsertChannelDataAction)
          .expects(never());

    MOCKER(DICC_TriggerChanDataTx)
           .expects(never());

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_UL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_CalcIsrSlice_001 )
{

    VOS_UINT32  ulRslt;

    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 600));

    MOCKER(CSD_GetLastTxSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));


    /* 测试函数调用 */


    ulRslt = CSD_UL_CalcIsrSlice();

    /* 匹配执行结果 */
    EXPECT_EQ(CSD_MAX_SLICE_CNT - 200 , ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_CalcIsrSlice_002 )
{
    VOS_UINT32  ulRslt;

    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 200));

    MOCKER(CSD_GetLastTxSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));


    /* 测试函数调用 */


    ulRslt = CSD_UL_CalcIsrSlice();

    /* 匹配执行结果 */
    EXPECT_EQ(200 , ulRslt);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#endif

#endif
