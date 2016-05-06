/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  dynamic_load_stub.c
*
*   作    者 :  y00171698
*
*   描    述 :  C核动态加载stub
*
*   修改记录 :  2015年8月18日
*
*************************************************************************/
/*lint -save -e534 -e586 -e801*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <time.h>

/* stub for drv separate */
extern void rand();
extern void srand(unsigned int);
void mtp_test_stub()
{
    rand();
    srand((unsigned int)time((time_t*)0));
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

/*lint -restore*/

