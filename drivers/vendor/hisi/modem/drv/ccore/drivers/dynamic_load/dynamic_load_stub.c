
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

