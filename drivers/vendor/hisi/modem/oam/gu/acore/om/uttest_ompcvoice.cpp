#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include <stdio.h>
#include <stdlib.h>

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

#ifdef __cplusplus
extern "C"
{
#endif
    extern unsigned int OM_PcvInitRBuf(void *pstRingId, void *pstAddrInfo);
    extern void CBTCPM_PortRcvReg(void * pRcvFunc);
    extern void * V_MemSet( void * ToSet, unsigned char Char, unsigned int Count,
        unsigned int ulFileID, int usLineNo );
    extern unsigned int VOS_SmP( unsigned long Sm_ID, unsigned int ulTimeOutInMillSec );
    extern unsigned int OM_GetSlice(void);
    extern int udi_ioctl(int handle, unsigned int u32Cmd, void* pParam);
    extern void BSP_MNTN_SystemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);
    extern unsigned int VOS_SmBCreate( unsigned char Sm_Name[4],
        unsigned int Sm_Init,
        unsigned int Flags,
        unsigned long * Sm_ID );
    extern void *VOS_UnCacheMemAlloc(unsigned int ulSize, unsigned long *pulRealAddr);

    extern unsigned int uttest_OM_PcvOpen_case1(void);
    extern unsigned int uttest_OM_PcvOpen_case2(void);
    extern void uttest_OM_PcvReleaseAll_case1(void);
    extern void uttest_OM_PcvReleaseAll_case2(void);
    extern unsigned int uttest_OM_PcvSendData_case1(void);
    extern unsigned int uttest_OM_PcvSendData_case2(void);
    extern unsigned int uttest_OM_PcvSendData_case3(void);
    extern unsigned int uttest_OM_PcvSendData_case4(void);
    extern unsigned int uttest_OM_PcvSendData_case5(void);
    extern unsigned int uttest_OM_PcvSendData_case6(void);
    extern void uttest_OM_PcvTransmitTaskEntry_case1(void);
    extern void uttest_OM_PcvTransmitTaskEntry_case2(void);
    extern unsigned int uttest_OM_PcvPidInit_case1(void);
    extern unsigned int uttest_OM_PcvPidInit_case2(void);
    extern unsigned int uttest_OM_PcvPidInit_case3(void);
    extern unsigned int uttest_OM_PcvPidInit_case4(void);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif

#ifndef MDRV_OK
#define MDRV_OK                          (0)
#endif

#ifndef MDRV_ERROR
#define MDRV_ERROR                       (-1)
#endif

/*******************************************************************
*测试项: OM_PcvOpen1
*被测函数功能描述:g_ulPcvStatus状态不为关闭
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvOpen1, UT)
{
    EXPECT_EQ(VOS_ERR, uttest_OM_PcvOpen_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvOpen2
*被测函数功能描述:g_ulPcvStatus状态为关闭
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvOpen2, UT)
{
    MOCKER(OM_PcvInitRBuf)
        .expects(exactly(2))
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(CBTCPM_PortRcvReg)
        .expects(exactly(1));

    EXPECT_EQ(VOS_OK, uttest_OM_PcvOpen_case2());

    GlobalMockObject::reset();
}


/*******************************************************************
*测试项: OM_PcvReleaseAll1
*被测函数功能描述:g_ucPcvComPort不为VOS_NULL_BYTE
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvReleaseAll1, UT)
{
    MOCKER(CBTCPM_PortRcvReg)
        .expects(exactly(1))
        .with(eq((void *)0));

    MOCKER(V_MemSet)
        .expects(exactly(1))
        .will(returnValue((void *)0));

    uttest_OM_PcvReleaseAll_case1();

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvReleaseAll2
*被测函数功能描述:g_ucPcvComPort为VOS_NULL_BYTE
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvReleaseAll2, UT)
{
    MOCKER(CBTCPM_PortRcvReg)
        .expects(exactly(0))
        .with(eq((void *)0));

    MOCKER(V_MemSet)
        .expects(exactly(1))
        .will(returnValue((void *)0));

    uttest_OM_PcvReleaseAll_case2();

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvSendData1
*被测函数功能描述:pucVirAddr为空指针
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvSendData1, UT)
{
    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvSendData2
*被测函数功能描述:pucPhyAddr为空指针
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvSendData2, UT)
{
    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvSendData3
*被测函数功能描述:发送成功，但获取信号量失败
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvSendData3, UT)
{
    MOCKER(udi_ioctl)
        .stubs()
        .will(returnValue((int)MDRV_OK));

    MOCKER(OM_GetSlice)
        .stubs()
        .will(returnObjectList((unsigned int)20, (unsigned int)10));

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvSendData4
*被测函数功能描述:发送成功，获取信号量成功
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvSendData4, UT)
{
    MOCKER(udi_ioctl)
        .stubs()
        .will(returnValue((int)MDRV_OK));

    MOCKER(OM_GetSlice)
        .stubs()
        .will(returnObjectList((unsigned int)10, (unsigned int)20));

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_OM_PcvSendData_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvSendData5
*被测函数功能描述:发送失败，错误码为BSP_ERROR
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvSendData5, UT)
{
    MOCKER(udi_ioctl)
        .stubs()
        .will(returnValue((int)MDRV_ERROR));

    MOCKER(OM_GetSlice)
        .stubs()
        .will(returnObjectList((unsigned int)10, (unsigned int)20, (unsigned int)30));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvSendData6
*被测函数功能描述:发送失败，错误码为其他错误
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvSendData6, UT)
{
    MOCKER(udi_ioctl)
        .stubs()
        .will(returnValue((int)2));

    MOCKER(OM_GetSlice)
        .stubs()
        .will(returnObjectList((unsigned int)10, (unsigned int)20));

    MOCKER(BSP_MNTN_SystemError)
        .expects(exactly(1));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case6());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvTransmitTaskEntry1
*被测函数功能描述:g_ulPcvTransmitSem信号量创建失败
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvTransmitTaskEntry1, UT)
{
    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    uttest_OM_PcvTransmitTaskEntry_case1();

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvTransmitTaskEntry2
*被测函数功能描述:申请uncache内存失败
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvTransmitTaskEntry2, UT)
{
    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(VOS_UnCacheMemAlloc)
        .stubs()
        .will(returnValue((void *)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(exactly(1));

    uttest_OM_PcvTransmitTaskEntry_case2();

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvPidInit1
*被测函数功能描述:phase不为VOS_IP_LOAD_CONFIG
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvPidInit1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_OM_PcvPidInit_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvPidInit2
*被测函数功能描述:申请g_stPcvOmToDspAddr uncache内存失败
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvPidInit2, UT)
{
    MOCKER(VOS_UnCacheMemAlloc)
        .stubs()
        .will(returnObjectList((void *)0, (void *)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(exactly(1));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvPidInit_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvPidInit3
*被测函数功能描述:申请g_stPcvDspToOmAddr uncache内存失败
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvPidInit3, UT)
{
    MOCKER(VOS_UnCacheMemAlloc)
        .stubs()
        .will(returnObjectList((void *)1, (void *)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(exactly(1));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvPidInit_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项: OM_PcvPidInit4
*被测函数功能描述:PID初始化成功
*预期结果：
************************* 修改记录 *************************
#  1.日    期: 2014年6月16日
#    作    者: L00256032
#    修改内容: 新建CASE
*******************************************************************/
TEST(OM_PcvPidInit4, UT)
{
    MOCKER(VOS_UnCacheMemAlloc)
        .stubs()
        .will(returnObjectList((void *)1, (void *)1));

    EXPECT_EQ(VOS_OK, uttest_OM_PcvPidInit_case4());

    GlobalMockObject::reset();
}

