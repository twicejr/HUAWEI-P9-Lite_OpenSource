#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicDemandDialFileIO.h"


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;


//说明: 经过改造后的gtest+，测试套和测试用例名字不允许为空
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

/*****************************************************************************
类名       : Test_RNIC_DemandDialFileIO
功能描述   : Test_RNIC_DemandDialFileIO UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : w00199382
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_DemandDialFileIO: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();

        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

    }
};

/*******************************************************************
测试用例编号      : RNIC_TransferStringToInt_001
测试用例标题      : RNIC_ReadOnDemandFile文件超长
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, RNIC_TransferStringToInt_001)
{
    VOS_CHAR *pcSting = "5";


    EXPECT_EQ(5, RNIC_TransferStringToInt(pcSting));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : RNIC_TransferStringToInt_002
测试用例标题      : RNIC_ReadOnDemandFile文件超长
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, RNIC_TransferStringToInt_002)
{
    VOS_CHAR *pcSting = "50";


    EXPECT_EQ(50, RNIC_TransferStringToInt(pcSting));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : RNIC_TransferStringToInt_002
测试用例标题      : RNIC_ReadOnDemandFile文件超长
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, RNIC_TransferStringToInt_003)
{
    VOS_CHAR *pcSting = "0";


    EXPECT_EQ(0, RNIC_TransferStringToInt(pcSting));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if 0
/*******************************************************************
测试用例编号      : TEST_RNIC_ReadOnDemandFile_001
测试用例标题      : RNIC_ReadOnDemandFile文件超长
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadOnDemandFile_001)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_to_user)
        .expects(never());

    RNIC_ReadOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : TEST_RNIC_ReadOnDemandFile_002
测试用例标题      : RNIC_ReadOnDemandFile文件长度为4
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadOnDemandFile_002)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;
    RNIC_DIAL_MODE_STRU *pstDialMode;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 4;

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode     = RNIC_GetDialModeAddr();

    pstDialMode->enDialMode = RNIC_ALLOW_EVENT_REPORT;

    MOCKER(copy_to_user)
        .with(any(),eq(1),any())
        .expects(exactly(1));

    RNIC_ReadOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif
/*******************************************************************
测试用例编号      : TEST_RNIC_WriteOnDemandFile_001
测试用例标题      : RNIC_ReadOnDemandFile文件长度为5
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteOnDemandFile_001)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_from_user)
        .expects(never());

    RNIC_WriteOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#if 0
/*******************************************************************
测试用例编号      : TEST_RNIC_WriteOnDemandFile_002
测试用例标题      : RNIC_ReadOnDemandFile文件长度为4,模式为手动拨号
预期结果          : 全局变量更新为手动拨号
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteOnDemandFile_002)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 4;

    PS_MEM_SET(pstFile, 0x00, 4);


    RNIC_WriteOnDemandFile(pstFile, pcSrc, 4, VOS_NULL_PTR);

    /* 参数匹配 */
    EXPECT_EQ(1, RNIC_GetDialModeAddr()->enDialMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : TEST_RNIC_WriteOnDemandFile_003
测试用例标题      : RNIC_ReadOnDemandFile文件长度为4,模式为自动拨号
预期结果          : 全局变量更新为自动拨号
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteOnDemandFile_003)
{
    struct file                        *pstFile;
    char                               *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 2;
    pcSrc           = (char *)&ulCnt;
    len             = 4;
    pstPdpAddr      = RNIC_GetPdpCtxAddr();

    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    PS_MEM_SET(pstFile, 0x00, 4);

    RNIC_WriteOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 参数匹配 */
    EXPECT_EQ(2, RNIC_GetDialModeAddr()->enDialMode);
    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : TEST_RNIC_WriteOnDemandFile_003
测试用例标题      : RNIC_ReadOnDemandFile文件长度为4,模式为0
预期结果          : 全局变量不更新
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteOnDemandFile_004)
{
    struct file                        *pstFile;
    char                               *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 0;
    pcSrc           = (char *)&ulCnt;
    len             = 4;
    pstPdpAddr      = RNIC_GetPdpCtxAddr(0);

    PS_MEM_SET(pstFile, 0x00, 4);


    RNIC_WriteOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 参数匹配 */
    EXPECT_EQ(0, RNIC_GetDialModeAddr()->enDialMode);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#if 0
/*******************************************************************
测试用例编号      : TEST_RNIC_ReadIdleTimerOutFile_001
测试用例标题      : RNIC_ReadIdleTimerOutFile文件超长
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadIdleTimerOutFile_001)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_to_user)
        .expects(never());

    RNIC_ReadIdleTimerOutFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : TEST_RNIC_ReadIdleTimerOutFile_002
测试用例标题      : RNIC_ReadIdleTimerOutFiles文件长度为4
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadIdleTimerOutFile_002)
{
    struct file                         *pstFile;
    char                                *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_DIAL_MODE_STRU                 *pstDialMode;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 4;

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode     = RNIC_GetDialModeAddr();

    pstDialMode->ulIdleTime = 65550;

    MOCKER(copy_to_user)
        .with(any(),eq(65550),any())
        .expects(exactly(1));


    RNIC_ReadIdleTimerOutFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif
#if 0
/*******************************************************************
测试用例编号      : TEST_RNIC_WriteIdleTimerOutFile_001
测试用例标题      : RNIC_IdleTimerOutFile文件长度为5
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteIdleTimerOutFile_001)
{
    struct file                         *pstFile;
    char                                *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_from_user)
        .expects(never());

    RNIC_WriteIdleTimerOutFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif
#if 0
/*******************************************************************
测试用例编号      : TEST_RNIC_WriteIdleTimerOutFile_002
测试用例标题      : RNIC_ReadOnDemandFile文件长度为4,模式为自动拨号
预期结果          : 全局变量更新为自动拨号
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteIdleTimerOutFile_002)
{
    struct file                        *pstFile;
    char                               *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_DIAL_MODE_STRU                *pstDialMode;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 2;
    pcSrc           = (char *)&ulCnt;
    len             = 4;
    pstPdpAddr      = RNIC_GetPdpCtxAddr();

     /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode     = RNIC_GetDialModeAddr();

    pstDialMode->enDialMode               = AT_RNIC_DIAL_MODE_DEMAND;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    PS_MEM_SET(pstFile, 0x00, 4);

    RNIC_WriteIdleTimerOutFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 参数匹配 */
    EXPECT_EQ(2, RNIC_GetDialModeAddr()->enDialMode);
    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif
#if 0
/*******************************************************************
测试用例编号      : TEST_RNIC_ReadDialEventReportFile_001
测试用例标题      : RNIC_ReadDialEventReportFile文件超长
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadDialEventReportFile_001)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_to_user)
        .expects(never());

    RNIC_ReadDialEventReportFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : TEST_RNIC_ReadDialEventReportFile_002
测试用例标题      : RNIC_ReadDialEventReportFile文件长度为4
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadDialEventReportFile_002)
{
    struct file                         *pstFile;
    char                                *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 4;



    MOCKER(copy_to_user)
        .expects(exactly(1));

    RNIC_ReadDialEventReportFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif
/*******************************************************************
测试用例编号      : TEST_RNIC_WriteDialEventReportFile_001
测试用例标题      : RNIC_WriteDialEventReportFile文件长度为5
预期结果          : 打印错误信息拷贝函数未调用
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteDialEventReportFile_001)
{
    struct file                         *pstFile;
    char                                *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_from_user)
        .expects(never());

    RNIC_WriteDialEventReportFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

#if 0
/*******************************************************************
测试用例编号      : TEST_RNIC_WriteDialEventReportFile_002
测试用例标题      : RNIC_WriteDialEventReportFile文件长度为4,模式为自动拨号
预期结果          : 全局变量更新为自动拨号
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteDialEventReportFile_002)
{
    struct file                        *pstFile;
    char                               *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_DIAL_MODE_STRU                *pstDialMode;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 2;
    pcSrc           = (char *)&ulCnt;
    len             = 4;
    pstPdpAddr      = RNIC_GetPdpCtxAddr();

     /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode     = RNIC_GetDialModeAddr();

    pstDialMode->enDialMode               = AT_RNIC_DIAL_MODE_DEMAND;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    PS_MEM_SET(pstFile, 0x00, 4);

    RNIC_WriteDialEventReportFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* 参数匹配 */
    EXPECT_EQ(2, RNIC_GetDialModeAddr()->enEventReportFlag);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名       : Test_RNIC_InitDemandDialFile
功能描述   : Test_RNIC_InitDemandDialFile UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : w00199382
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_InitDemandDialFile: public ::testing::Test
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
测试用例编号      : Test_RNIC_InitDemandDialFile_001
测试用例标题      : Test_RNIC_InitDemandDialFile创建路径失败
预期结果          : 返回vos_err
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_001)
{
    MOCKER(kern_path)
        .stubs()
        .will(returnValue(1));

    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(proc_create)
        .expects(never());

    EXPECT_EQ(VOS_ERR, RNIC_InitDemandDialFile());

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
/*******************************************************************
测试用例编号      : Test_RNIC_InitDemandDialFile_002
测试用例标题      : Test_RNIC_InitDemandDialFile创建模式文件失败
预期结果          : 返回vos_err
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_002)
{
    struct proc_dir_entry              stProcEntry;



    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(&stProcEntry));

    MOCKER(proc_create)
        .expects(never())
        .will(returnValue(VOS_NULL_PTR));

    EXPECT_EQ(VOS_ERR, RNIC_InitDemandDialFile());

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#if 0
/*******************************************************************
测试用例编号      : Test_RNIC_InitDemandDialFile_003
测试用例标题      : Test_RNIC_InitDemandDialFile创建idletimerout文件失败
预期结果          : 返回vos_err
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_003)
{
    struct proc_dir_entry              stProcEntry;



    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(&stProcEntry));

    MOCKER(proc_create)
        .expects(exactly(1))
        .will(returnValue(&stProcEntry));

    MOCKER(proc_create)
        .expects(never())
        .will(returnValue(VOS_NULL_PTR));


    EXPECT_EQ(VOS_ERR, RNIC_InitDemandDialFile());

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_InitDemandDialFile_004
测试用例标题      : Test_RNIC_InitDemandDialFile创建eventreport文件失败
预期结果          : 返回vos_err
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_004)
{
    struct proc_dir_entry              stProcEntry;



    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(&stProcEntry));

    MOCKER(proc_create)
        .expects(exactly(2))
        .will(returnValue(&stProcEntry));



    MOCKER(proc_create)
        .will(returnValue(VOS_NULL_PTR))
        .expects(never());


    EXPECT_EQ(VOS_ERR, RNIC_InitDemandDialFile());

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_InitDemandDialFile_005
测试用例标题      : Test_RNIC_InitDemandDialFile创建成功
预期结果          : 返回vos_OK
修改历史     :
1.日   期  : 2011-12-09
  作   者  : w00199382
  修改内容 : 新建CASE

*******************************************************************/
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_005)
{
    struct proc_dir_entry              stProcEntry;



    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(&stProcEntry));



    MOCKER(proc_create)
        .stubs()
        .will(returnValue(&stProcEntry));


    EXPECT_EQ(VOS_OK, RNIC_InitDemandDialFile());

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#endif

#endif
