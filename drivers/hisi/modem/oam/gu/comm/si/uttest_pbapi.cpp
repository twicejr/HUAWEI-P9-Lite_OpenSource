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
    extern unsigned int uttest_SI_PB_Read_ReturnFail(void);
    extern unsigned int uttest_SI_PB_SRead_ReturnFail(void);
    extern unsigned int uttest_SI_PB_Query_ReturnFail(void);
    extern unsigned int uttest_SI_PB_Set_ReturnFail(void);
    extern unsigned int uttest_SI_PB_Add_ReturnFail(void);
    extern unsigned int uttest_SI_PB_SAdd_ReturnFail(void);
    extern unsigned int uttest_SI_PB_Modify_ReturnFail(void);
    extern unsigned int uttest_SI_PB_SModify_ReturnFail(void);
    extern unsigned int uttest_SI_PB_Delete_ReturnFail(void);
    extern unsigned int uttest_SI_PB_Search_ReturnFail(void);
    extern unsigned int uttest_SI_PB_GetStorateType_ReturnFail(void);
    extern unsigned int uttest_SI_PB_GetSPBFlag_ReturnFail(void);

    extern void * V_AllocMsg(unsigned int Pid, unsigned int ulLength, unsigned int ulFileID, signed int usLineNo);
    extern unsigned int V_SendMsg(unsigned int Pid, void **ppMsg, unsigned int ulFileID, signed int lLineNo);

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
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_Read, ReturnFail)
{
	EXPECT_EQ(VOS_OK, uttest_SI_PB_Read_ReturnFail());
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SRead,ReturnFail)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_SRead_ReturnFail());
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_Query,ReturnFail)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_Set_ReturnFail());
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_Set,ReturnFail)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_Set_ReturnFail());
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_Add,ReturnFail)
{
    char buf[1024];

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&buf[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_SI_PB_Add_ReturnFail());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SAdd,ReturnFail)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_SAdd_ReturnFail());
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_Modify,ReturnFail)
{
    char buf[1024];

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&buf[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)0));

    EXPECT_EQ(VOS_OK, uttest_SI_PB_Modify_ReturnFail());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_SModify,ReturnFail)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_SModify_ReturnFail());
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_Delete,ReturnFail)
{
    char buf[1024];

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((void*)&buf[0]));

    MOCKER(V_SendMsg)
        .stubs()
        .will(returnValue((unsigned int)0));

    EXPECT_EQ(VOS_OK, uttest_SI_PB_Delete_ReturnFail());

    GlobalMockObject::reset();
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_Search,ReturnFail)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_Search_ReturnFail());
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_GetStorateType,ReturnFail)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_GetStorateType_ReturnFail());
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者:
#    修改内容: 新建CASE
*******************************************************************/
TEST(SI_PB_GetSPBFlag,ReturnFail)
{
    EXPECT_EQ(VOS_OK, uttest_SI_PB_GetSPBFlag_ReturnFail());
}

