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

    extern void uttest_Om_HdlcEncap_case1(void);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif


TEST(Test_Om_HdlcEncap, UT)
{
	uttest_Om_HdlcEncap_case1();
}