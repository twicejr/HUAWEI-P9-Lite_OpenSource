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
    extern unsigned char g_aucVhwMemDDR[];
    extern unsigned int uttest_NV_Init_case1(void);
    extern unsigned int uttest_NV_Init_case2(void);
    extern unsigned int uttest_NV_Init_case3(void);
    extern unsigned int uttest_NV_GetLength_case1(void);
    extern unsigned int uttest_NV_GetLength_case2(void);
    extern unsigned int uttest_NV_GetLength_case3(void);
    extern unsigned int uttest_NVIM_MemCpy_case1(void);
    extern void uttest_NV_MemDump_case1(void);
    extern void uttest_NV_MemDump_case2(void);
    extern void uttest_NV_MemCpy_case1(void);
    extern void uttest_NV_MemCpy_case2(void);
    extern void uttest_NV_MemCpy_case3(void);
    extern void uttest_NV_MemCpy_case4(void);
    extern unsigned int uttest_NV_ReadPartEx_case1(void);
    extern unsigned int uttest_NV_ReadPartEx_case2(void);
    extern unsigned int uttest_NV_ReadPartEx_case3(void);
    extern unsigned int uttest_NV_ReadPartEx_case4(void);
    extern unsigned int uttest_NV_ReadPartEx_case5(void);
    extern unsigned int uttest_NV_ReadPartEx_case6(void);
    extern unsigned int uttest_NV_ReadPartEx_case7(void);
    extern unsigned int uttest_NV_Printf_case1(void);
    extern unsigned int uttest_NV_ReadPartEx_case8(void);
    extern unsigned int uttest_NV_ReadEx_case1(void);
    extern unsigned int uttest_NV_ReadEx_case2(void);
    extern unsigned int uttest_NV_ReadEx_case3(void);
    extern unsigned int uttest_NV_ReadEx_case4(void);
    extern unsigned int uttest_NV_ReadEx_case5(void);
    extern unsigned int uttest_NV_ReadEx_case6(void);
    extern unsigned int uttest_NV_ReadEx_case7(void);

    extern unsigned int omTimerGet(void);
    extern int BSP_DDR_GetSectInfo(void *pstSectQuery, void *pstSectInfo);
    extern void BSP_MNTN_SystemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);
    extern void * mdrv_phy_to_virt(void * pPhyAddr);
    extern int BSP_IPC_SemCreate(unsigned int u32SignalNum);
    extern unsigned int _VOS_SmMCreate(unsigned char acSmName[], unsigned int ulSmInit, unsigned int ulFlags, void *pulSmID);
    extern unsigned int NV_Ctrl_File_Search_InMemory(unsigned short usID, void *pstNVCtrlInfo, void *pstFileListInfo, void *pstNvIdInfo);
    extern unsigned int uttest_NV_Ctrl_File_Search_InMemory_stub1(unsigned short usID, void *pstNVCtrlInfo, void *pstFileListInfo, void *pstNvIdInfo);
    extern unsigned int uttest_NV_Ctrl_File_Search_InMemory_stub2(unsigned short usID, void *pstNVCtrlInfo, void *pstFileListInfo, void *pstNvIdInfo);
    extern unsigned int uttest_NV_Ctrl_File_Search_InMemory_stub3(unsigned short usID, void *pstNVCtrlInfo, void *pstFileListInfo, void *pstNvIdInfo);
    extern unsigned int uttest_NV_Ctrl_File_Search_InMemory_stub4(unsigned short usID, void *pstNVCtrlInfo, void *pstFileListInfo, void *pstNvIdInfo);
    extern void NV_MemDump(unsigned int ulErrorNO, unsigned int ulFileID,int ulLineNo,void *pData, unsigned int ulDataLen);
    extern void* BSP_MNTN_ExchMemMalloc(unsigned int ulSize);
    extern void NVIM_MemCpy( void * Dest, const void * Src,  unsigned int ulnbytes );
    extern void NV_MemCpy(void * Dest, const void * Src,  unsigned int ulnbytes, unsigned int ulFileID, int usLineNo);
    extern void add_preempt_count(int val);
    extern int vsnprintf(char *str, size_t size, const char *format, va_list ap);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif


/*******************************************************************
*测试项:             获得地址信息失败
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_Init1, UT)
{
    MOCKER(omTimerGet)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(BSP_DDR_GetSectInfo)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(BSP_MNTN_SystemError)
        .expects(once());

    EXPECT_EQ(VOS_OK, uttest_NV_Init_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             创建信号量失败
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_Init2, UT)
{
    MOCKER(omTimerGet)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

	MOCKER(mdrv_phy_to_virt)
	    .stubs()
        .will(returnValue((void*)&g_aucVhwMemDDR[0]));

	MOCKER(_VOS_SmMCreate)
	    .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_NV_Init_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             创建硬件锁失败
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_Init3, UT)
{
    MOCKER(omTimerGet)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

	MOCKER(mdrv_phy_to_virt)
	    .stubs()
        .will(returnValue((void*)&g_aucVhwMemDDR[0]));

	MOCKER(_VOS_SmMCreate)
	    .stubs()
        .will(returnValue((unsigned int)VOS_OK));

	MOCKER(BSP_IPC_SemCreate)
	    .stubs()
		.will(returnValue(VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_NV_Init_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             输入参数为空
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_GetLength1, UT)
{
	EXPECT_EQ(VOS_OK, uttest_NV_GetLength_case1());
}

/*******************************************************************
*测试项:             ID不存在
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_GetLength2, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_NV_GetLength_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             获取长度成功
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_GetLength3, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(invoke(uttest_NV_Ctrl_File_Search_InMemory_stub1));

    EXPECT_EQ(VOS_OK, uttest_NV_GetLength_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             复制内存
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NVIM_MemCpy1, UT)
{
	EXPECT_EQ(0, uttest_NVIM_MemCpy_case1());
}

/*******************************************************************
*测试项:             申请内存失败
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_MemDump1, UT)
{
    MOCKER(add_preempt_count)
        .expects(once());

	MOCKER(BSP_MNTN_ExchMemMalloc)
	    .stubs()
		.will(returnValue((void*)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(once());

	uttest_NV_MemDump_case1();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             申请内存OK
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_MemDump2, UT)
{
	unsigned char aucData[32*1024];

    MOCKER(add_preempt_count)
            .expects(once());

	MOCKER(BSP_MNTN_ExchMemMalloc)
	    .stubs()
		.will(returnValue((void*)&aucData[0]));

    MOCKER(omTimerGet)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(BSP_MNTN_SystemError)
        .expects(once());

    MOCKER(NVIM_MemCpy)
        .expects(once());

	uttest_NV_MemDump_case2();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             源地址非法
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_MemCpy1, UT)
{
	MOCKER(NV_MemDump)
		.expects(once());

	MOCKER(NVIM_MemCpy)
		.expects(never());

	uttest_NV_MemCpy_case1();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             偏移量非法
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_MemCpy2, UT)
{
	MOCKER(NV_MemDump)
		.expects(once());

	MOCKER(NVIM_MemCpy)
		.expects(never());

	uttest_NV_MemCpy_case2();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             拷贝数据长度非法
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_MemCpy3, UT)
{
	MOCKER(NV_MemDump)
		.expects(once());

	MOCKER(NVIM_MemCpy)
		.expects(never());

	uttest_NV_MemCpy_case3();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:             拷贝数据OK
*被测函数功能描述:
*预期结果：           返回
************************* 修改记录 *************************
#  1.日    期: 2010年11月11日
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_MemCpy4, UT)
{
	MOCKER(NV_MemDump)
		.expects(once());

	MOCKER(NVIM_MemCpy)
		.expects(once());

	uttest_NV_MemCpy_case4();

	GlobalMockObject::reset();
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:  参数检查MocemID错误
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadPartEx1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_NV_ReadPartEx_case1());
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:  参数检查pItem为空
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadPartEx2, UT)
{
    EXPECT_EQ(VOS_OK, uttest_NV_ReadPartEx_case2());
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadPartEx3, UT)
{
	EXPECT_EQ(VOS_OK, uttest_NV_ReadPartEx_case3());
}

#if 0
/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadPartEx4, UT)
{
	MOCKER(NV_Ctrl_File_Search_InMemory)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_NV_ReadPartEx_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:  ulOffset大于NV长度
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadPartEx5, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(invoke(uttest_NV_Ctrl_File_Search_InMemory_stub2));

    EXPECT_EQ(VOS_OK, uttest_NV_ReadPartEx_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:  需读取的NV长度超标
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadPartEx6, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(invoke(uttest_NV_Ctrl_File_Search_InMemory_stub2));

    EXPECT_EQ(VOS_OK, uttest_NV_ReadPartEx_case6());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:  NV_ReadPart成功
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadPartEx7, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(invoke(uttest_NV_Ctrl_File_Search_InMemory_stub3));

	MOCKER(NV_MemCpy)
		.expects(exactly(2));

    EXPECT_EQ(VOS_OK, uttest_NV_ReadPartEx_case7());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:  NV_ReadPart成功2
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadPartEx8, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(invoke(uttest_NV_Ctrl_File_Search_InMemory_stub4));

	MOCKER(NV_MemCpy)
		.expects(exactly(1));

    EXPECT_EQ(VOS_OK, uttest_NV_ReadPartEx_case8());

    GlobalMockObject::reset();
}

#endif
/*******************************************************************
*测试项:			NV_ReadPart()
*被测函数功能描述:  打印字符串过长
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_Printf1, UT)
{
/*  64位UT不支持可变参数打桩
    MOCKER(vsnprintf)
        .stubs()
        .will(returnValue((512) + 1));

    EXPECT_EQ(VOS_OK, uttest_NV_Printf_case1());

    GlobalMockObject::reset();
*/
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:  参数检查MocemID错误
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadEx1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_NV_ReadEx_case1());
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:  参数检查pItem为空
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadEx2, UT)
{
    EXPECT_EQ(VOS_OK, uttest_NV_ReadEx_case2());
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadEx3, UT)
{
    EXPECT_EQ(VOS_OK, uttest_NV_ReadEx_case3());
}

#if 0
/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:  检查NV_ID不存在
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadEx4, UT)
{
	MOCKER(NV_Ctrl_File_Search_InMemory)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_OK, uttest_NV_ReadEx_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:  需读取的NV长度超标
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadEx5, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(invoke(uttest_NV_Ctrl_File_Search_InMemory_stub4));

    EXPECT_EQ(VOS_OK, uttest_NV_ReadEx_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadEx6, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(invoke(uttest_NV_Ctrl_File_Search_InMemory_stub4));

	MOCKER(NV_MemCpy)
		.expects(exactly(2));

    EXPECT_EQ(VOS_OK, uttest_NV_ReadEx_case6());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:			NV_ReadEx()
*被测函数功能描述:  NV_ReadEx成功2
*预期结果：			返回
************************* 修改记录 *********************************
#  1.日    期: 2011.12.30
#    作    者: n00203913
#    修改内容: 新建CASE
*******************************************************************/
TEST(NV_ReadEx7, UT)
{
    MOCKER(NV_Ctrl_File_Search_InMemory)
        .stubs()
		.will(invoke(uttest_NV_Ctrl_File_Search_InMemory_stub4));

	MOCKER(NV_MemCpy)
	    .expects(once());

    EXPECT_EQ(VOS_OK, uttest_NV_ReadEx_case7());

    GlobalMockObject::reset();
}
#endif

