/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

using namespace testing;

/* 使用到C中函数和全局变量请放这里 */
#ifdef __cplusplus
extern "C"
{
#endif

extern void *g_pstIpsToOmMsg;
extern unsigned char g_aucTraceData[];

extern unsigned int IPS_MNTN_TransMsg
(
    unsigned char               *pucTransMsg,
    unsigned int                 ulTransMsgContentLen,
    unsigned short               enMsgName
);
extern void OM_Log(char *, unsigned int,
                   int , int ,int, char *);
extern void OM_AcpuAddSNTime(unsigned int *, unsigned int *);
extern unsigned int NFExt_AddDataToRingBuf(void *);
extern int test_IPS_MNTN_TransMsg_002(void);
extern void* V_AllocMsg(unsigned int, unsigned int,
                        unsigned int, int);
extern void test_IPS_MNTN_SndCfgCnf2Om_001(void);
extern unsigned int OM_GetSlice(void);
extern unsigned int Ps_SendMsg(char *, unsigned int, unsigned int, void *);
extern void test_init_IPS_MNTN(void);
extern void test_recover_IPS_MNTN(void);
extern int test_IPS_MNTN_SndCfgCnf2Om_002(void);
extern int test_IPS_MNTN_SndCfgCnf2Om_003(void);
extern unsigned int test_IPS_MNTN_GetPktLenByTraceCfg_001(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_002(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_003(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_004(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_005(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_006(void);
extern void IPS_MNTN_CtrlPktInfoCB(unsigned char *,
    unsigned char *,
    unsigned short,
    unsigned short);
extern int test_IPS_MNTN_CtrlPktInfoCB_002(void);
extern void * V_MemAlloc(unsigned int, unsigned char, unsigned int ,
                        unsigned int, unsigned int, int);
extern void *kmalloc(size_t size, unsigned int flags);
extern int test_IPS_MNTN_CtrlPktInfoCB_003(void);
extern void test_IPS_MNTN_CtrlPktInfoCB_004(void);
extern void IPS_MNTN_PktInfoCB
(
    unsigned char                        *pucNetIfName,
    unsigned char                        *pucPktData,
    unsigned short                              usPktLen,
    unsigned short     usType
);
extern void OM_AddSNTime(unsigned int *, unsigned int *);
extern void test_IPS_MNTN_PktInfoCB_003(void);
extern void test_IPS_MNTN_PktInfoCB_005(void);
extern void test_IPS_MNTN_PktInfoCB_006(void);
extern void test_IPS_MNTN_PktInfoCB_007(void);
extern void IPS_MNTN_BridgePktInfoCB
(
    unsigned char                        *pucSrcPort,
    unsigned char                        *pucDestPort,
    unsigned char                              *pucPktData,
    unsigned short                              usPktLen,
    unsigned short     usType
);
extern void test_IPS_MNTN_BridgePktInfoCB_003(void);
extern void test_IPS_MNTN_BridgePktInfoCB_004(void);
extern void test_IPS_MNTN_BridgePktInfoCB_005(void);
extern unsigned char test_IPS_MNTN_BridgeTraceCfgChkParam_002(void);
extern unsigned char test_IPS_MNTN_BridgeTraceCfgChkParam_001(void);
extern unsigned char test_IPS_MNTN_TraceCfgChkParam_001(void);
extern unsigned char test_IPS_MNTN_TraceCfgChkParam_002(void);
extern unsigned char test_IPS_MNTN_TraceCfgChkParam_003(void);
extern unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_001(void);
extern unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_002(void);
extern unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_003(void);
extern unsigned char NFExt_ConfigEffective(void *pRcvMsg);
extern int test_IPS_MNTN_TraceAdvancedCfgReq_001(void);
extern int test_IPS_MNTN_TraceAdvancedCfgReq_002(void);
extern int test_IPS_MNTN_TraceAdvancedCfgReq_003(void);
extern unsigned int test_IPS_MNTN_IPInfoCfgChkParam_001(void);
extern unsigned int test_IPS_MNTN_IPInfoCfgChkParam_002(void);
extern unsigned int test_IPS_MNTN_IPInfoCfgChkParam_003(void);
//extern unsigned int test_sizeof_IPS_MNTN_TRACE_CONFIG_CNF_STRU();
extern void IPS_MNTN_SndCfgCnf2Om
(
    unsigned short      usPrimId,
    unsigned int        ulTransMsgContentLen,
    void               *pTransMsgContent
);
extern void test_IPS_MNTN_IPInfoCfgReq_001(void);
extern void test_IPS_MNTN_IPInfoCfgReq_002(void);
extern void test_IPS_MNTN_IPInfoCfgReq_003(void);
extern int test_IPS_MNTN_Ipv4DataParse_001(void);
extern int test_IPS_MNTN_Ipv4DataParse_002(void);
extern int test_IPS_MNTN_Ipv4DataParse_003(void);
extern int test_IPS_MNTN_Ipv4DataParse_004(void);
extern int test_IPS_MNTN_Ipv4DataParse_005(void);
extern int test_IPS_MNTN_Ipv4DataParse_006(void);
extern int test_IPS_MNTN_Ipv4DataParse_007(void);
extern int test_IPS_MNTN_Ipv4DataParse_008(void);
extern int test_IPS_MNTN_GetIPInfoCfg_001(void);
extern int test_IPS_MNTN_GetIPInfoCfg_002(void);
extern void IPS_MNTN_Ipv4DataParse(void *, void *);
extern void IPS_MNTN_Ipv6DataParse(void *, void *);
extern void test_IPS_MNTN_TraceIpInfo_001(void);
extern void test_IPS_MNTN_TraceIpInfo_002(void);
extern void test_IPS_MNTN_TraceIpInfo_003(void);
extern void test_IPS_MNTN_TraceIpInfo_004(void);
extern void test_IPS_MNTN_TraceIpInfo_005(void);
extern unsigned int OM_AcpuSendData(void *, unsigned short);
extern void test_IPS_MNTN_TraceIpInfo_006(void);
extern void test_IPS_MNTN_TraceIpInfo_007(void);
extern void test_IPS_MNTN_TraceIpInfo_008(void);
extern int BSP_MNTN_SystemError();
extern int BSP_USB_RegIpsTraceCB();

extern int _raw_spin_lock_irqsave();
extern int _raw_spin_unlock_irqrestore();
extern int add_preempt_count();
extern int BSP_MNTN_ExchMemMalloc();
extern int BSP_MNTN_SystemError();

//IPS_MNTN_TRACE_MAX_BYTE_LEN + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN == 1548
unsigned char    g_aucTempData[1548];


#ifdef __cplusplus
}
#endif

/* 以下是用例 */
void test_init_IPS_MNTN_CPP()
{
    test_init_IPS_MNTN();
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
}

void test_recover_IPS_MNTN_CPP()
{
    test_recover_IPS_MNTN();
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
}

/*****************************************************************************
测试项:  Test_IPS_MNTN_TransMsg
功能描述:消息指针为空
测试编号:Test_IPS_MNTN_TransMsg_001
测试标题:消息指针为空
预期结果:

1.日    期: 2011年8月11日
  作    者: f00166181
  修改内容: 新建CASE
2.日    期   : 2014年5月17日
  作    者   : liukai
  修改内容   : 改造为linux WinGDB UT用例
*****************************************************************************/
TEST(test_IPS_MNTN_TransMsg, IPS_MNTN_TransMsg_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned int                 ulDataLen;
    unsigned int                 result;
    const char                  *str = "IPS, IPS_MNTN_TransMsg, ERROR, pucTransMsg is NULL ";

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    ulDataLen   = 6;

    /* check异常输出 */
    MOCKER(OM_Log)
        .stubs()
        .with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    result = IPS_MNTN_TransMsg(0L, ulDataLen, 0xD021);//ID_IPS_TRACE_MNTN_INFO

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1, result);//VOS_ERR

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
 被测函数   : test_IPS_MNTN_TransMsg_002
 被测功能   : 对桩test_IPS_MNTN_TransMsg测试
 用例条件   : 消息指针为空

 修改历史       :
 1.日    期 : 2014年5月20日
   作    者 : liukai
   修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TransMsg, IPS_MNTN_TransMsg_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned int ulSn        = 10;
    unsigned int ulTimeStamp = 20;
    int          result;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(OM_AcpuAddSNTime).expects(once()).with(outBoundP(&ulSn), outBoundP(&ulTimeStamp));
    MOCKER(NFExt_AddDataToRingBuf).expects(once()).will(returnValue(0UL));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    result = test_IPS_MNTN_TransMsg_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, result);

    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  Test_IPS_MNTN_SndCfgCnf2Om
功能描述:向OM发送配置确认消息，申请内存失败
测试编号:Test_IPS_MNTN_SndCfgCnf2Om_001
测试标题:向OM发送配置确认消息，申请内存失败
预期结果:

1.日    期   : 2014年5月21日
  作    者   : liukai
  修改内容   : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_SndCfgCnf2Om_001, IPS_MNTN_SndCfgCnf2Om_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    const char *str = "IPS, IPS_MNTN_SndCfgCnf2Om, ERROR, Call PS_ALLOC_MSG_WITH_HEADER_LEN \
            fail!";

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_AllocMsg).stubs().will(returnValue((void *)NULL));//VOS_NULL_PTR
    /* check 异常输出 */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));

	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));
    //MOCKER(add_preempt_count).stubs().will(returnValue(0));
    //MOCKER(BSP_MNTN_ExchMemMalloc).stubs().will(returnValue(0));
    //MOCKER(BSP_MNTN_SystemError).stubs().will(returnValue(0));
    //MOCKER(sub_preempt_count).stubs().will(returnValue(0));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_SndCfgCnf2Om_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  Test_IPS_MNTN_SndCfgCnf2Om
功能描述:向OM发送配置确认消息，发送消息成功
测试编号:Test_IPS_MNTN_SndCfgCnf2Om_002
测试标题:向OM发送配置确认消息，发送消息成功
预期结果:

1.日    期 : 2014年5月21日
   作    者 : liukai
   修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_SndCfgCnf2Om_002, IPS_MNTN_SndCfgCnf2Om_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int rslt;
    test_init_IPS_MNTN();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_AllocMsg).expects(once()).will(returnValue((void *)(g_pstIpsToOmMsg)));
    MOCKER(OM_GetSlice).expects(once()).will(returnValue(100));
    MOCKER(Ps_SendMsg).stubs().will(returnValue(0));//VOS_OK
    MOCKER(BSP_MNTN_SystemError).stubs().will(returnValue(0));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_SndCfgCnf2Om_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_SndCfgCnf2Om_003
功能描述:向OM发送配置确认消息，发送消息失败
测试编号:IPS_MNTN_SndCfgCnf2Om_003
测试标题:向OM发送配置确认消息，发送消息失败
预期结果:

1.日    期 : 2014年5月21日
   作    者 : liukai
   修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_SndCfgCnf2Om_003, IPS_MNTN_SndCfgCnf2Om_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int rslt;
    const char *str = "IPS, IPS_MNTN_SndCfgCnf2Om, ERROR, Call PS_SEND_MSG fail!";
    test_init_IPS_MNTN();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_AllocMsg).expects(once()).will(returnValue((void *)(g_pstIpsToOmMsg)));
    MOCKER(OM_GetSlice).expects(once()).will(returnValue(100));
    MOCKER(Ps_SendMsg).stubs().will(returnValue(0));//VOS_OK
    /* check 异常输出 */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
    MOCKER(BSP_MNTN_SystemError).stubs().will(returnValue(0));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_SndCfgCnf2Om_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_GetPktLenByTraceCfg_001
功能描述:不捕获报文的情况
测试编号:test_IPS_MNTN_GetPktLenByTraceCfg_001
测试标题:不捕获报文的情况
预期结果:

1.日    期 : 2014年5月21日
   作    者 : liukai
   修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned int                       rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/


    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_GetPktLenByTraceCfg_002
功能描述:
测试编号:test_IPS_MNTN_GetPktLenByTraceCfg_002
测试标题:
预期结果:

1.日    期 : 2014年5月21日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_GetPktLenByTraceCfg_003
功能描述:
测试编号:test_IPS_MNTN_GetPktLenByTraceCfg_003
测试标题:
预期结果:

1.日    期 : 2014年5月22日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_GetPktLenByTraceCfg_004
功能描述:
测试编号:test_IPS_MNTN_GetPktLenByTraceCfg_004
测试标题:
预期结果:

1.日    期 : 2014年5月22日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_004)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_004();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_GetPktLenByTraceCfg_005
功能描述:
测试编号:test_IPS_MNTN_GetPktLenByTraceCfg_005
测试标题:
预期结果:

1.日    期 : 2014年5月22日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_005)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_005();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_GetPktLenByTraceCfg_006
功能描述:
测试编号:test_IPS_MNTN_GetPktLenByTraceCfg_006
测试标题:
预期结果:

1.日    期 : 2014年5月22日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_006)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_006();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_CtrlPktInfoCB
功能描述:报文指针为空
测试编号:test_IPS_MNTN_CtrlPktInfoCB_001
测试标题:报文指针为空
预期结果:

1.日    期: 2011年8月11日
  作    者: f00166181
  修改内容: 新建CASE
2.日    期   : 2014年5月17日
  作    者   : liukai
  修改内容   : 改造为linux WinGDB UT用例
*****************************************************************************/
TEST(test_IPS_MNTN_CtrlPktInfoCB, IPS_MNTN_CtrlPktInfoCB_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char                           aucNetIfName[16];//IPS_IFNAMSIZ
    const char *str = "IPS, IPS_MNTN_CtrlPktInfoCB, ERROR, pucPktData is NULL ";

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    /* check 异常输出正确 */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    IPS_MNTN_CtrlPktInfoCB(aucNetIfName, (unsigned char *)0L, 0, 0xD01A);//ID_IPS_TRACE_RECV_ARP_PKT

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_CtrlPktInfoCB_002
功能描述:
测试编号:test_IPS_MNTN_CtrlPktInfoCB_002
测试标题:
预期结果:

1.日    期 : 2014年5月22日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_CtrlPktInfoCB, IPS_MNTN_CtrlPktInfoCB_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int                       rslt;

    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	MOCKER(OM_AcpuAddSNTime).expects(never());
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
    MOCKER(NFExt_AddDataToRingBuf).stubs().will(returnValue(0U));//VOS_OK
    MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_CtrlPktInfoCB_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_CtrlPktInfoCB_003
功能描述:
测试编号:test_IPS_MNTN_CtrlPktInfoCB_003
测试标题:
预期结果:

1.日    期 : 2014年5月26日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_CtrlPktInfoCB, IPS_MNTN_CtrlPktInfoCB_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
#if 0
    /* kmalloc已经被UT工程打桩，测试脚本不要再打桩，否则造成工程不稳定 */
    /* MOCKER(kmalloc).expects(once()).will(returnValue((void *)0L)); */
    /* malloc打桩，在run时出现挂住不往下执行 */
    /* MOCKER(malloc).expects(once().will(returnValue((void *)0L)); */
    MOCKER(V_MemAlloc).expects(once()).will(returnValue((void *)0L));
#else
    /* 打桩函数不检查次数，否则打桩函数不生效 */
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)0L));
#endif
    MOCKER(OM_AddSNTime).expects(never());
    MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    rslt = test_IPS_MNTN_CtrlPktInfoCB_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_CtrlPktInfoCB_004
功能描述:
测试编号:test_IPS_MNTN_CtrlPktInfoCB_004
测试标题:
预期结果:

1.日    期 : 2014年5月26日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_CtrlPktInfoCB, IPS_MNTN_CtrlPktInfoCB_004)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    test_init_IPS_MNTN();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(OM_AcpuAddSNTime).expects(never());
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_CtrlPktInfoCB_004();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    test_recover_IPS_MNTN();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  Test_IPS_MNTN_PktInfoCB
功能描述:报文指针为空
测试编号:Test_IPS_MNTN_PktInfoCB_001
测试标题:报文指针为空
预期结果:

1.日    期: 2011年8月11日
  作    者: f00166181
  修改内容: 新建CASE
2.日    期   : 2014年5月26日
  作    者   : liukai
  修改内容   : 改造为linux WinGDB UT用例
*****************************************************************************/
TEST(test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char              aucNetIfName[16];//IPS_IFNAMSIZ
    const char *str = "IPS, IPS_MNTN_PktInfoCB, ERROR, paucPktData is NULL ";
    unsigned short             usMsgType = 0xD017;//ID_IPS_TRACE_INPUT_DATA_INFO

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    /* check 异常输出 */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    IPS_MNTN_PktInfoCB(aucNetIfName, (unsigned char *)0L, 0, usMsgType);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项: Test_IPS_MNTN_PktInfoCB
功能描述:捕获消息类型为桥
测试编号:Test_IPS_MNTN_PktInfoCB_002
测试标题:捕获消息类型为桥
预期结果:

1.日  期: 2011年8月11日
  作    者: f00166181
  修改内容: 新建CASE
2.日    期   : 2014年5月26日
  作    者   : liukai
  修改内容   : 改造为linux WinGDB UT用例
*****************************************************************************/
TEST(test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char                           aucNetIfName[16];//IPS_IFNAMSIZ
    unsigned char                           aucPktData[40];
    unsigned short                          usPktLen;
    unsigned char                          *paucPktData;
    unsigned short                      	usMsgType = 0xD019;//ID_IPS_TRACE_BRIDGE_DATA_INFO

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    usPktLen        = 40;
    paucPktData     = (unsigned char *)aucPktData;

	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    IPS_MNTN_PktInfoCB(aucNetIfName, paucPktData, usPktLen, usMsgType);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_PktInfoCB_003
功能描述:
测试编号:test_IPS_MNTN_PktInfoCB_003
测试标题:
预期结果:

1.日    期 : 2014年5月26日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例

*****************************************************************************/
TEST(test_test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)0L));
	MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_PktInfoCB_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项: Test_IPS_MNTN_PktInfoCB
功能描述:捕获消息类型错误
测试编号:Test_IPS_MNTN_PktInfoCB_002
测试标题:捕获消息类型错误
预期结果:

1.日  期: 2011年8月11日
  作    者: f00166181
  修改内容: 新建CASE
2.日    期   : 2014年5月26日
  作    者   : liukai
  修改内容   : 改造为linux WinGDB UT用例
*****************************************************************************/
TEST(test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_004)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char                           aucNetIfName[16];//IPS_IFNAMSIZ
    unsigned char                          *paucPktData;
    unsigned short                          usPktLen;
    const char *str = "IPS, IPS_MNTN_PktInfoCB : ERROR : usType is not Expectes!";
    unsigned char                           aucPktData[40];
    unsigned short                          usMsgType;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    usPktLen        = 40;
    paucPktData     = (unsigned char *)aucPktData;
    usMsgType       = 0xD02E;//ID_IPS_TRACE_MSG_TYPE_BUTT
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    IPS_MNTN_PktInfoCB(aucNetIfName, paucPktData, usPktLen, usMsgType);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项: Test_IPS_MNTN_PktInfoCB
功能描述:配置不捕获接收报文
测试编号:Test_IPS_MNTN_PktInfoCB_005
测试标题:配置不捕获接收报文
预期结果:

1.日    期 : 2014年5月26日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_005)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
    MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_PktInfoCB_005();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项: Test_IPS_MNTN_PktInfoCB
功能描述:
测试编号:Test_IPS_MNTN_PktInfoCB_006
测试标题:
预期结果:

1.日    期 : 2014年5月26日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_006)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(OM_AcpuAddSNTime).expects(never());
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_PktInfoCB_006();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项: Test_IPS_MNTN_PktInfoCB
功能描述:配置不捕获接收报文
测试编号:Test_IPS_MNTN_PktInfoCB_007
测试标题:配置不捕获接收报文
预期结果:

1.日    期 : 2014年5月26日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_007)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(OM_AcpuAddSNTime).expects(never());
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_PktInfoCB_007();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  Test_IPS_MNTN_BridgePktInfoCB
功能描述:报文指针为空
测试编号:Test_IPS_MNTN_BridgePktInfoCB_001
测试标题:报文指针为空
预期结果:

1.日    期: 2011年8月11日
  作    者: f00166181
  修改内容: 新建CASE
2.日    期   : 2014年5月27日
  作    者   : liukai
  修改内容   : 改造为linux WinGDB UT用例
*****************************************************************************/
TEST(test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char                           aucSrcPort[16];//IPS_END_NAME
    unsigned char                           aucDestPort[16];//IPS_END_NAME
    const char *str = "IPS, IPS_MNTN_BridgePktInfoCB, ERROR, paucPktData is NULL ";
    unsigned short                      usMsgType;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    usMsgType = 0xD019;//ID_IPS_TRACE_BRIDGE_DATA_INFO

    /* check 异常输出 */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    IPS_MNTN_BridgePktInfoCB(aucSrcPort, aucDestPort, (unsigned char *)0L, 0, usMsgType);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  Test_IPS_MNTN_BridgePktInfoCB
功能描述:捕获消息类型错误
测试编号:Test_IPS_MNTN_BridgePktInfoCB_002
测试标题:捕获消息类型错误
预期结果:

1.日    期: 2011年8月11日
  作    者: f00166181
  修改内容: 新建CASE
2.日    期   : 2014年5月27日
  作    者   : liukai
  修改内容   : 改造为linux WinGDB UT用例
*****************************************************************************/
TEST(test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char                           aucSrcPort[16];//IPS_END_NAME
    unsigned char                           aucDestPort[16];//IPS_END_NAME
    unsigned char                          *paucPktData;
    unsigned short                          usPktLen;
    const char *str = "IPS, IPS_MNTN_BridgePktInfoCB : ERROR : usType is not Expectes!";
    unsigned short                          usMsgType;
    unsigned char                           aucPktData[40];

    usPktLen        = 40;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    paucPktData = aucPktData;
    usMsgType = 0xD02E;//ID_IPS_TRACE_MSG_TYPE_BUTT

    /* check 异常输出 */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    IPS_MNTN_BridgePktInfoCB(aucSrcPort, aucDestPort, paucPktData, usPktLen, usMsgType);

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_BridgePktInfoCB_003
功能描述:配置不捕获接收报文
测试编号:test_IPS_MNTN_BridgePktInfoCB_003
测试标题:配置不捕获接收报文
预期结果:

1.日    期 : 2014年5月27日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    test_init_IPS_MNTN();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
    MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_BridgePktInfoCB_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_BridgePktInfoCB_004
功能描述:配置不捕获接收报文
测试编号:test_IPS_MNTN_BridgePktInfoCB_004
测试标题:配置不捕获接收报文
预期结果:

1.日    期 : 2014年5月27日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_004)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned int                          ulSn;
    unsigned int                          ulTimeStamp;

    ulSn        = 10;
    ulTimeStamp = 20;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
	MOCKER(OM_AcpuAddSNTime).expects(never());
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_BridgePktInfoCB_004();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_BridgePktInfoCB_005
功能描述:配置不捕获接收报文
测试编号:test_IPS_MNTN_BridgePktInfoCB_005
测试标题:配置不捕获接收报文
预期结果:

1.日    期 : 2014年5月27日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_005)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned int                          ulSn;
    unsigned int                          ulTimeStamp;

    ulSn        = 10;
    ulTimeStamp = 20;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(OM_AddSNTime).expects(never());
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)NULL));
    MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK


    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_BridgePktInfoCB_005();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_BridgeTraceCfgChkParam_001
功能描述:
测试编号:test_IPS_MNTN_BridgeTraceCfgChkParam_001
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgeTraceCfgChkParam, IPS_MNTN_BridgeTraceCfgChkParam_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    ucRslt = test_IPS_MNTN_BridgeTraceCfgChkParam_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_BridgeTraceCfgChkParam_002
功能描述:
测试编号:test_IPS_MNTN_BridgeTraceCfgChkParam_002
测试标题:
预期结果:

1.日    期 : 2014年5月27日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgeTraceCfgChkParam, IPS_MNTN_BridgeTraceCfgChkParam_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    ucRslt = test_IPS_MNTN_BridgeTraceCfgChkParam_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1, ucRslt);//PS_TRUE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceCfgChkParam_001
功能描述:
测试编号:test_IPS_MNTN_TraceCfgChkParam_001
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceCfgChkParam, IPS_MNTN_TraceCfgChkParam_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    ucRslt = test_IPS_MNTN_TraceCfgChkParam_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceCfgChkParam_002
功能描述:
测试编号:test_IPS_MNTN_TraceCfgChkParam_002
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceCfgChkParam, IPS_MNTN_TraceCfgChkParam_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    ucRslt = test_IPS_MNTN_TraceCfgChkParam_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceCfgChkParam_003
功能描述:
测试编号:test_IPS_MNTN_TraceCfgChkParam_003
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceCfgChkParam, IPS_MNTN_TraceCfgChkParam_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    ucRslt = test_IPS_MNTN_TraceCfgChkParam_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1, ucRslt);//PS_TRUE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceAdvancedCfgChkParam_001
功能描述:
测试编号:test_IPS_MNTN_TraceAdvancedCfgChkParam_001
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgChkParam, IPS_MNTN_TraceAdvancedCfgChkParam_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/

	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));

    ucRslt = test_IPS_MNTN_TraceAdvancedCfgChkParam_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceAdvancedCfgChkParam_002
功能描述:
测试编号:test_IPS_MNTN_TraceAdvancedCfgChkParam_002
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgChkParam, IPS_MNTN_TraceAdvancedCfgChkParam_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));

    ucRslt = test_IPS_MNTN_TraceAdvancedCfgChkParam_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceAdvancedCfgChkParam_003
功能描述:
测试编号:test_IPS_MNTN_TraceAdvancedCfgChkParam_003
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgChkParam, IPS_MNTN_TraceAdvancedCfgChkParam_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));

    ucRslt = test_IPS_MNTN_TraceAdvancedCfgChkParam_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1, ucRslt);//PS_TRUE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceAdvancedCfgReq_001
功能描述:
测试编号:test_IPS_MNTN_TraceAdvancedCfgReq_001
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgReq, IPS_MNTN_TraceAdvancedCfgReq_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int Rslt;
    const char *str = "Warning: IPS_MNTN_TraceAdvancedCfgReq check fail";

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(NFExt_ConfigEffective).expects(never());
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));//check log
	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));
    /* V_AllocMsg已被UT工程打桩，代码走不到IPS_MNTN_SndCfgCnf2Om, 通过其它检查
       判断代码执行分支 */
    //MOCKER(V_AllocMsg).will(returnValue(pstIpsToOmMsg));
    MOCKER(IPS_MNTN_SndCfgCnf2Om).stubs().will(ignoreReturnValue());//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    Rslt = test_IPS_MNTN_TraceAdvancedCfgReq_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, Rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceAdvancedCfgReq_002
功能描述:
测试编号:test_IPS_MNTN_TraceAdvancedCfgReq_002
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgReq, IPS_MNTN_TraceAdvancedCfgReq_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int Rslt;
    const char *str = "Warning: NFExt_ConfigEffective fail";

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(NFExt_ConfigEffective).stubs().will(returnValue(0));//PS_FALSE
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));//check log
	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));
    /* V_AllocMsg已被UT工程打桩，代码走不到IPS_MNTN_SndCfgCnf2Om, 通过其它检查
       判断代码执行分支 */
    //MOCKER(V_AllocMsg).will(returnValue(pstIpsToOmMsg));
    MOCKER(IPS_MNTN_SndCfgCnf2Om).stubs().will(ignoreReturnValue());//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    Rslt = test_IPS_MNTN_TraceAdvancedCfgReq_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, Rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceAdvancedCfgReq_003
功能描述:
测试编号:test_IPS_MNTN_TraceAdvancedCfgReq_003
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgReq, IPS_MNTN_TraceAdvancedCfgReq_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int Rslt;
    const char *str = "Warning: NFExt_ConfigEffective fail";

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(NFExt_ConfigEffective).stubs().will(returnValue(1));//PS_TRUE
    MOCKER(OM_Log).expects(never());
	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));
    /* V_AllocMsg已被UT工程打桩，代码走不到IPS_MNTN_SndCfgCnf2Om, 通过其它检查
       判断代码执行分支 */
    //MOCKER(V_AllocMsg).will(returnValue(pstIpsToOmMsg));
    MOCKER(IPS_MNTN_SndCfgCnf2Om).stubs().will(ignoreReturnValue());//VOS_OK

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    Rslt = test_IPS_MNTN_TraceAdvancedCfgReq_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, Rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_IPInfoCfgChkParam_001
功能描述:
测试编号:test_IPS_MNTN_IPInfoCfgChkParam_001
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgChkParam, IPS_MNTN_IPInfoCfgChkParam_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned int Rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(BSP_USB_RegIpsTraceCB).stubs().will(returnValue(0));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    Rslt = test_IPS_MNTN_IPInfoCfgChkParam_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(1, Rslt);//PS_TRUE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_IPInfoCfgChkParam_002
功能描述:
测试编号:test_IPS_MNTN_IPInfoCfgChkParam_002
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgChkParam, IPS_MNTN_IPInfoCfgChkParam_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned int Rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    Rslt = test_IPS_MNTN_IPInfoCfgChkParam_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, Rslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_IPInfoCfgChkParam_003
功能描述:
测试编号:test_IPS_MNTN_IPInfoCfgChkParam_003
测试标题:
预期结果:

1.日    期 : 2014年5月28日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgChkParam, IPS_MNTN_IPInfoCfgChkParam_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    unsigned int Rslt;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    Rslt = test_IPS_MNTN_IPInfoCfgChkParam_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, Rslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_IPInfoCfgReq_001
功能描述:
测试编号:test_IPS_MNTN_IPInfoCfgReq_001
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgReq, IPS_MNTN_IPInfoCfgReq_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(OM_Log).expects(never());
    MOCKER(IPS_MNTN_SndCfgCnf2Om).expects(once());
    MOCKER(BSP_USB_RegIpsTraceCB).stubs().will(returnValue(0));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_IPInfoCfgReq_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_IPInfoCfgReq_002
功能描述:
测试编号:test_IPS_MNTN_IPInfoCfgReq_002
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgReq, IPS_MNTN_IPInfoCfgReq_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(OM_Log).expects(never());
    MOCKER(IPS_MNTN_SndCfgCnf2Om).expects(once());
    MOCKER(BSP_USB_RegIpsTraceCB).stubs().will(returnValue(0));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_IPInfoCfgReq_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_IPInfoCfgReq_003
功能描述:
测试编号:test_IPS_MNTN_IPInfoCfgReq_003
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgReq, IPS_MNTN_IPInfoCfgReq_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    const char  *str = "Warning: IPS_MNTN_IPInfoCfgReq check fail";

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(IPS_MNTN_SndCfgCnf2Om).expects(once());
    /* check异常输出 */
    MOCKER(OM_Log)
        .stubs()
        .with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_IPInfoCfgReq_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_Ipv4DataParse_001
功能描述:
测试编号:test_IPS_MNTN_Ipv4DataParse_001
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_Ipv4DataParse_002
功能描述:
测试编号:test_IPS_MNTN_Ipv4DataParse_002
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_Ipv4DataParse_003
功能描述:
测试编号:test_IPS_MNTN_Ipv4DataParse_003
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_Ipv4DataParse_004
功能描述:
测试编号:test_IPS_MNTN_Ipv4DataParse_004
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_004)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_004();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_Ipv4DataParse_005
功能描述:
测试编号:test_IPS_MNTN_Ipv4DataParse_005
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_005)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_005();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_Ipv4DataParse_006
功能描述:
测试编号:test_IPS_MNTN_Ipv4DataParse_006
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_006)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_006();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_Ipv4DataParse_007
功能描述:
测试编号:test_IPS_MNTN_Ipv4DataParse_007
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_007)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_007();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_Ipv4DataParse_008
功能描述:
测试编号:test_IPS_MNTN_Ipv4DataParse_008
测试标题:
预期结果:

1.日    期 : 2014年5月29日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_008)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_008();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_GetIPInfoCfg_001
功能描述:
测试编号:test_IPS_MNTN_GetIPInfoCfg_001
测试标题:
预期结果:

1.日    期 : 2014年5月30日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_GetIPInfoCfg, IPS_MNTN_GetIPInfoCfg_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int result;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    result = test_IPS_MNTN_GetIPInfoCfg_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, result);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_GetIPInfoCfg_002
功能描述:
测试编号:test_IPS_MNTN_GetIPInfoCfg_002
测试标题:
预期结果:

1.日    期 : 2014年5月30日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_GetIPInfoCfg, IPS_MNTN_GetIPInfoCfg_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/
    int result;

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    result = test_IPS_MNTN_GetIPInfoCfg_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    EXPECT_EQ(0, result);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceIpInfo_001
功能描述:
测试编号:test_IPS_MNTN_TraceIpInfo_001
测试标题:
预期结果:

1.日    期 : 2014年5月30日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_001)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_001();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceIpInfo_002
功能描述:
测试编号:test_IPS_MNTN_TraceIpInfo_002
测试标题:
预期结果:

1.日    期 : 2014年5月30日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_002)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_002();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceIpInfo_003
功能描述:
测试编号:test_IPS_MNTN_TraceIpInfo_003
测试标题:
预期结果:

1.日    期 : 2014年5月30日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_003)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_003();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceIpInfo_004
功能描述:
测试编号:test_IPS_MNTN_TraceIpInfo_004
测试标题:
预期结果:

1.日    期 : 2014年5月30日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_004)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_004();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceIpInfo_005
功能描述:
测试编号:test_IPS_MNTN_TraceIpInfo_005
测试标题:
预期结果:

1.日    期 : 2014年5月30日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_005)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTraceData));
    MOCKER(OM_AcpuSendData).expects(once()).will(returnValue(0U));//VOS_OK
    MOCKER(OM_AcpuAddSNTime).expects(once());
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(once());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_005();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceIpInfo_006
功能描述:
测试编号:test_IPS_MNTN_TraceIpInfo_006
测试标题:
预期结果:

1.日    期 : 2014年5月30日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_006)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTraceData));
    MOCKER(OM_AcpuSendData).expects(once()).will(returnValue(0U));//VOS_OK
    MOCKER(OM_AcpuAddSNTime).expects(once());
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(once());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_006();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceIpInfo_007
功能描述:
测试编号:test_IPS_MNTN_TraceIpInfo_007
测试标题:
预期结果:

1.日    期 : 2014年5月31日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_007)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTraceData));
    MOCKER(OM_AcpuSendData).expects(once()).will(returnValue(0U));//VOS_OK
    MOCKER(OM_AcpuAddSNTime).expects(once());
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(once());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_007();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
测试项:  test_IPS_MNTN_TraceIpInfo_008
功能描述:
测试编号:test_IPS_MNTN_TraceIpInfo_008
测试标题:
预期结果:

1.日    期 : 2014年5月31日
  作    者 : liukai
  修改内容 : 新生成linux WinGDB UT用例
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_008)
{
    /*************************************************************************
      (1)初始化测试环境
    *************************************************************************/

    /*************************************************************************
      (2)设置被测函数形参
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTraceData));
    MOCKER(OM_AcpuSendData).expects(once()).will(returnValue(0U));//VOS_OK
    MOCKER(OM_AcpuAddSNTime).expects(once());
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(once());

    /*************************************************************************
      (3)执行被测函数
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_008();

    /*************************************************************************
      (4)检测测试结果
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)清理测试环境
    *************************************************************************/
    GlobalMockObject::reset();
}




