#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_CsdDownLink.h"

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
/*****************************************************************************
类名 : Test_CSD_DL_ProcData
功能描述 : Test_CSD_DL_ProcData UT工程类
修改历史     :
1.日   期  : 2011-12-10
  作   者  : w00199382
  修改内容 : 新生成类
*****************************************************************************/
class Test_CSD_DL_ProcDataTask: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        CSD_InitCtx();
    }
    void TearDown()
    {
    }
private:

};

/*******************************************************************
测试用例编号      : Test_CSD_DL_ProcDataTask_001
测试用例标题      : CSD_DL_ProcDataTask下行任务没有收到数据,信号量未释放
预期结果          : 打印信号量未释放log
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_ProcDataTask_001 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_ERR));

    MOCKER(CSD_DL_ClearData)
          .expects(never());
#if 0
    MOCKER(DICC_EnableIsr)
          .expects(never());
#endif
    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_CSD_DL_ProcDataTask_002
测试用例标题      : CSD_DL_ProcDataTask中CSD_GetCallState不为 AT_CSD_CALL_STATE_ON下行任务没有接通电话
预期结果          : 清空DICC发送来的数据，使能中断，打印异常 。下行数据被释放
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_ProcDataTask_002 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(3));

    MOCKER(DICC_RemoveChannelData)
          .will(returnValue(DICC_OK));

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(exactly(3));
#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}
/*******************************************************************
测试用例编号      : Test_CSD_DL_ClearData_001
测试用例标题      : CSD_DL_ProcDataTask中CSD_GetCallState不为 AT_CSD_CALL_STATE_ON下行任务没有接通电话
                    从DICC中移出数据失败
预期结果          : 打印异常，下行数据未释放
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_ClearData_001 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(3));

    MOCKER(DICC_RemoveChannelData)
          .will(returnValue(DICC_ERR_TRIG_ISR_FAIL));

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(never());
#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}
/*******************************************************************
测试用例编号      : Test_CSD_DL_ClearData_002
测试用例标题      : CSD_DL_ProcDataTask中CSD_GetCallState不为 AT_CSD_CALL_STATE_ON下行任务没有接通电话
                    清除DICC中发送来的数据,获取节点数目非法
预期结果          : 不清除数据直接返回
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_ClearData_002 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(DICC_INVALID_VALUE));

    MOCKER(DICC_RemoveChannelData)
          .expects(never());

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(never());
#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif
    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      :  Test_CSD_DL_SendData_001
测试用例标题      :  CSD_DL_ProcDataTask中CSD_DL_SendData ulDICCNodeCnt为零
预期结果          :  打印缓存发完结果，下行数据被清空
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_SendData_001 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(0));

    MOCKER(DICC_RemoveChannelData)
          .expects(never());

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(never());
#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();



}
/*******************************************************************
测试用例编号      :  Test_CSD_DL_SendData_002
测试用例标题      :  CSD_DL_ProcDataTask中CSD_DL_SendData,
                     获取DICC通道节点数目非法
预期结果          :  打印节点数目异常信息，终止流程，下行数据未改变
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_SendData_002 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(DICC_INVALID_VALUE));

    MOCKER(DICC_RemoveChannelData)
          .expects(never());

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(never());
#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      :  Test_CSD_DL_SendData_003
测试用例标题      :  CSD_DL_ProcDataTask中CSD_DL_SendData,
                     ulRslt为VOS_ERR下行任务从DICC中移除数据失败
预期结果          :  打印数据移出异常信息，终止流程，
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_SendData_003 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(3));

    MOCKER(DICC_RemoveChannelData)
          .will(returnValue(DICC_ERR_TRIG_ISR_FAIL));

    MOCKER(IMM_ZcStaticAlloc_Debug)
          .expects(never());

    MOCKER(AT_SendCsdZcDataToModem)
          .expects(never());

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(never());

#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      :  Test_CSD_DL_SendData_004
测试用例标题      :  CSD_DL_ProcDataTask中CSD_DL_SendData,
                     C核传送过来的数据指针为空
预期结果          :  打印数据指针为空异常信息，终止流程
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_SendData_004 )
{
    CST_CSD_DATA_IND_STRU               stDLData;

    /* 输入码流配置 */
    PS_MEM_SET(&stDLData, 0x00, sizeof(CST_CSD_DATA_IND_STRU));

    stDLData.pGarbage                   = VOS_NULL_PTR;
    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(3));

    MOCKER(DICC_RemoveChannelData)
          .with(eq(ACPU_PID_CSD),
                eq(DICC_CHAN_ID_2),
                outBoundP((VOS_VOID *)&stDLData, sizeof(CST_CSD_DATA_IND_STRU)))
           .will(returnValue(DICC_OK));

    MOCKER(IMM_ZcStaticAlloc_Debug)
          .expects(never());

    MOCKER(AT_SendCsdZcDataToModem)
          .expects(never());

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(never());

#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      :  Test_CSD_DL_SendData_005
测试用例标题      :  CSD_DL_SendData中IMM_ZcLargeMemAlloc申请数据内存失败VOS_NULL_PTR
预期结果          :  打印内存申请失败异常，释放C核数据
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_SendData_005 )
{
    CST_CSD_DATA_IND_STRU               stDLData;

    /* 输入码流配置 */
    PS_MEM_SET(&stDLData, 0x00, sizeof(CST_CSD_DATA_IND_STRU));

    stDLData.pGarbage                   = (VOS_VOID *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                   4);
    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(3));

    MOCKER(DICC_RemoveChannelData)
          .with(eq(ACPU_PID_CSD),
                eq(DICC_CHAN_ID_2),
                outBoundP((VOS_VOID *)&stDLData, sizeof(CST_CSD_DATA_IND_STRU)))
           .will(returnValue(DICC_OK));

    MOCKER(IMM_ZcStaticAlloc_Debug)
          .expects(exactly(1))
          .will(returnValue(VOS_NULL_PTR));

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(exactly(1))
          .with(mirror(stDLData.pGarbage, 4));

    MOCKER(AT_SendCsdZcDataToModem)
          .expects(never());
#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      :  Test_CSD_DL_SendData_006
测试用例标题      :  CSD_DL_SendData中AT_UsbModemWriteData写数据内存失败
预期结果          :  释放A核内存和C核数据内存
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_SendData_006 )
{
    CST_CSD_DATA_IND_STRU               stDLData;

    /* 输入码流配置 */
    PS_MEM_SET(&stDLData, 0x00, sizeof(CST_CSD_DATA_IND_STRU));

    stDLData.pGarbage                   = PS_MEM_ALLOC(ACPU_PID_CSD, 4);
    stDLData.pucData                    = (VOS_UINT8 *)PS_MEM_ALLOC(ACPU_PID_CSD, 4);
    stDLData.usLen                      = 4;

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(3));

    MOCKER(DICC_RemoveChannelData)
          .with(eq(ACPU_PID_CSD),
                eq(DICC_CHAN_ID_2),
                outBoundP((VOS_VOID *)&stDLData, sizeof(CST_CSD_DATA_IND_STRU)))
           .will(returnValue(DICC_OK));

    MOCKER(IMM_ZcStaticAlloc_Debug)
          .expects(exactly(1))
          .will(returnValue(&stDLData.pucData));

    MOCKER(V_MemCpy)
          .expects(exactly(1));

    MOCKER(AT_SendCsdZcDataToModem)
          .expects(exactly(1))
          .will(returnValue(VOS_ERR));

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(exactly(1))
          .with(mirror(stDLData.pGarbage, 4));

#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      :  Test_CSD_DL_ProcDataTask_007
测试用例标题      :  发送数据成功
预期结果          :  发送数据成功使能DICC中断
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_ProcDataTask_007 )
{
    CST_CSD_DATA_IND_STRU               stDLData;

    /* 输入码流配置 */
    PS_MEM_SET(&stDLData, 0x00, sizeof(CST_CSD_DATA_IND_STRU));

    stDLData.pGarbage                   = PS_MEM_ALLOC(ACPU_PID_CSD, 4);
    stDLData.pucData                    = (VOS_UINT8 *)PS_MEM_ALLOC(ACPU_PID_CSD, 4);
    stDLData.usLen                      = 4;

    /* 场景配置 */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(2))
          .will(returnObjectList(3,0));

    MOCKER(DICC_RemoveChannelData)
          .with(eq(ACPU_PID_CSD),
                eq(DICC_CHAN_ID_2),
                outBoundP((VOS_VOID *)&stDLData, sizeof(CST_CSD_DATA_IND_STRU)))
           .will(returnValue(DICC_OK));

    MOCKER(IMM_ZcStaticAlloc_Debug)
          .expects(exactly(1))
          .will(returnValue(&stDLData.pucData));

    MOCKER(V_MemCpy)
          .expects(exactly(1));

    MOCKER(AT_SendCsdZcDataToModem)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(IMM_RbRemoteFreeMem)
          .expects(exactly(1))
          .with(mirror(stDLData.pGarbage, 4));

#if 0
    MOCKER(DICC_EnableIsr)
          .expects(exactly(1));
#endif
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* 测试函数调用 */
    CSD_DL_ProcDataTask();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();


}

/*******************************************************************
测试用例编号      : Test_CSD_DL_ProcIsr_001
测试用例标题      : 调用中断响应函数
预期结果          : 释放信号量，关闭中断
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_CSD_DL_ProcDataTask, Test_CSD_DL_ProcIsr_001 )
{
    /* 输入码流配置 */

    /* 场景配置 */
    MOCKER(VOS_SmV)
          .with(eq(CSD_GetDownLinkDataSem()));
#if 0
    MOCKER(DICC_DisableIsr)
          .expects(exactly(1));
#endif
    /* 测试函数调用 */
    CSD_DL_ProcIsr();

    /* 匹配执行结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#endif

#endif
