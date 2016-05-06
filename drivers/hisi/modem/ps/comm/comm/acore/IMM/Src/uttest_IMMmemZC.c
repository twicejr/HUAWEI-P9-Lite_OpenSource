/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_immzc.c
  版 本 号   : 初稿
  作    者   : g00178567
  生成日期   : 2014年5月15日
  最近修改   :
  功能描述   : IMMmemZc.c 测试接口
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月15日
    作    者   : g00178567
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "linux/skbuff.h"
#include "IMMmemZC.h"
#include "linux/string.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#define TEST_IMM_STRUCT_ALLOC(s, pStruct) \
{ \
    pStruct = (struct s *)malloc(sizeof(struct s));    \
}

#define TEST_IMM_STRUCT_FREE(pStruct) free(pStruct)


/*****************************************************************************
  3 函数实现
*****************************************************************************/
unsigned char *test_IMM_ZcStaticAlloc_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else
    int iRet = 0;
    struct sk_buff *pSk_buff = 0;
    unsigned short usFileID = 10;
    unsigned short usLineNum = 10;
    unsigned int ulLen = 100;

    pSk_buff = (struct sk_buff *)IMM_ZcStaticAlloc_Debug(usFileID, usLineNum, ulLen);
    if (0 == pSk_buff)
    {
        return 0;
    }

    return (unsigned char *)pSk_buff;
#endif
}

int test_IMM_ZcAddMacHead(int iTestStep)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else
    int iRet = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    if (0 == iTestStep)
    {
        if (VOS_ERR == IMM_ZcAddMacHead(0, "test_IMM_ZcAddMacHead01"))
        {
            iRet = -1;
            goto test_fail;
        }
    }
    else if (1 == iTestStep)
    {
        if (VOS_ERR == IMM_ZcAddMacHead(pSk_buff, 0))
        {
            iRet = -1;
            goto test_fail;
        }
    }
    else if (2 == iTestStep)
    {
        pSk_buff->head = 0x0000000000000001;
        pSk_buff->data = 0x0000000000000002;

        if (VOS_ERR == IMM_ZcAddMacHead(pSk_buff, "test_IMM_ZcAddMacHead03"))
        {
            iRet = -1;
            goto test_fail;
        }
    }
    else
    {
        pSk_buff->head = 0x0000000000000001;
        pSk_buff->data = 0x00000000000000FF;

        IMM_ZcAddMacHead(pSk_buff, "test_IMM_ZcAddMacHead04");
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

int test_IMM_ZcAddMacHeadCmp(unsigned char *ucCmpbuff)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else

    int iRet = -1;

    iRet = memcmp(ucCmpbuff, "test_IMM_ZcAdd", IMM_MAC_HEADER_RES_LEN);

    return iRet;
#endif
}

int test_IMM_ZcRemoveMacHead(int iTestStep)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else
    int iRet = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    if (0 == iTestStep)
    {
        if (VOS_ERR == IMM_ZcRemoveMacHead(0))
        {
            iRet = -1;
            goto test_fail;
        }
    }
    else if (1 == iTestStep)
    {
        pSk_buff->len = 10;
        pSk_buff->data_len = 8;
        if (VOS_ERR == IMM_ZcRemoveMacHead(pSk_buff))
        {
            iRet = -1;
            goto test_fail;
        }
    }
    else
    {
        pSk_buff->len = 80;
        pSk_buff->data_len = 10;

        IMM_ZcRemoveMacHead(pSk_buff);
        if ((80 - IMM_MAC_HEADER_RES_LEN) != pSk_buff->len)
        {
            iRet = -1;
            goto test_fail;
        }
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

unsigned char * test_IMM_ZcPush_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else

    unsigned char * pucImmZc = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return 0;
    }

    pucImmZc = IMM_ZcPush_Debug(10, 10, pSk_buff, 10);

    TEST_IMM_STRUCT_FREE(pSk_buff);

    return pucImmZc;
#endif
}

unsigned char * test_IMM_ZcPull_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else
    unsigned char * pucImmZc = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return 0;
    }

    pucImmZc = IMM_ZcPull_Debug(10, 10, pSk_buff, 10);

    TEST_IMM_STRUCT_FREE(pSk_buff);

    return pucImmZc;
#endif
}

unsigned char * test_IMM_ZcPut_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else

    unsigned char * pucImmZc = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return 0;
    }

    pucImmZc = IMM_ZcPut_Debug(10, 10, pSk_buff, 10);

    TEST_IMM_STRUCT_FREE(pSk_buff);

    return pucImmZc;
#endif
}

int test_IMM_ZcReserve_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else
    int iRet = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    pSk_buff->data = 0x0000000000000010;
    pSk_buff->tail = 0x0000000000000020;

    IMM_ZcReserve_Debug(10, 10, pSk_buff, 10);

    if (0x0000000000000020 != pSk_buff->data)
    {
        iRet = -1;
        goto test_fail;
    }

    if (0x0000000000000030 != pSk_buff->tail)
    {
        iRet = -1;
        goto test_fail;
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

int test_IMM_ZcGetUsedLen(int iTestStep)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
     return 0;
#else

    int iRet = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    pSk_buff->len = 10;

    if (0 == iTestStep)
    {
        if (IMM_INVALID_VALUE == IMM_ZcGetUsedLen(0))
        {
            iRet = -1;
            goto test_fail;
        }
    }

    IMM_ZcGetUsedLen(pSk_buff);
    if (10 != pSk_buff->len)
    {
        iRet = -1;
        goto test_fail;
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

int test_IMM_ZcGetUserApp(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
    return 0;
#else
    int iRet = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    IMM_PRIV_CB(pSk_buff)->usApp = 0xFE;

    if (0xFE != IMM_ZcGetUserApp(pSk_buff))
        iRet = -1;

    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

int test_IMM_ZcSetUserApp(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
     return 0;
#else

    int iRet = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    IMM_PRIV_CB(pSk_buff)->usApp = 0xFE;

    IMM_ZcSetUserApp(0, 0xEF);
    if (0xFE != IMM_PRIV_CB(pSk_buff)->usApp)
    {
        iRet = -1;
        goto test_fail;
    }

    IMM_ZcSetUserApp(pSk_buff, 0xEF);
    if (0xEF != IMM_PRIV_CB(pSk_buff)->usApp)
    {
        iRet = -1;
        goto test_fail;
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

int test_IMM_ZcQueueHeadInit_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
     return 0;
#else
    int iRet = 0;
    struct sk_buff_head *pSk_buff_head = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff_head, pSk_buff_head);
    if (0 == pSk_buff_head)
    {
        return -1;
    }

    IMM_ZcQueueHeadInit_Debug(10, 10, pSk_buff_head);

    if ((struct sk_buff *)pSk_buff_head != pSk_buff_head->prev)
    {
        iRet = -1;
        goto test_fail;
    }

    if ((struct sk_buff *)pSk_buff_head != pSk_buff_head->next)
    {
        iRet = -1;
        goto test_fail;
    }

    if (0 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff_head);

    return iRet;
#endif
}

int test_IMM_ZcQueueHead_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
     return 0;
#else

    int iRet = 0;
    struct sk_buff_head *pSk_buff_head = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff_head, pSk_buff_head);
    if (0 == pSk_buff_head)
    {
        return -1;
    }

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    IMM_ZcQueueHeadInit_Debug(10, 10, pSk_buff_head);
    if (0 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

    IMM_ZcQueueHead_Debug(10, 10, pSk_buff_head, pSk_buff);
    if ((struct sk_buff *)pSk_buff_head != (struct sk_buff_head *)pSk_buff->prev)
    {
        iRet = -1;
        goto test_fail;
    }

    if ((struct sk_buff *)pSk_buff_head != (struct sk_buff_head *)pSk_buff->next)
    {
        iRet = -1;
        goto test_fail;
    }

    if (1 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff);
    TEST_IMM_STRUCT_FREE(pSk_buff_head);

    return iRet;
#endif
}


int test_IMM_ZcQueueTail_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
     return 0;
#else
    int iRet = 0;
    struct sk_buff_head *pSk_buff_head = 0;
    struct sk_buff *pSk_buff = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff_head, pSk_buff_head);
    if (0 == pSk_buff_head)
    {
        return -1;
    }

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    IMM_ZcQueueHeadInit_Debug(10, 10, pSk_buff_head);
    if (0 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

    IMM_ZcQueueTail_Debug(10, 10, pSk_buff_head, pSk_buff);
    if (pSk_buff != pSk_buff_head->prev)
    {
        iRet = -1;
        goto test_fail;
    }

    if (pSk_buff != pSk_buff_head->next)
    {
        iRet = -1;
        goto test_fail;
    }

    if (1 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff_head);
    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

int test_IMM_ZcDequeueHead_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
     return 0;
#else

    int iRet = 0;
    struct sk_buff_head *pSk_buff_head = 0;
    struct sk_buff *pSk_buff = 0;
    struct sk_buff *pSk_buff_test = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff_head, pSk_buff_head);
    if (0 == pSk_buff_head)
    {
        return -1;
    }

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    IMM_ZcQueueHeadInit_Debug(10, 10, pSk_buff_head);
    if (0 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

    IMM_ZcQueueHead_Debug(10, 10, pSk_buff_head, pSk_buff);
    if (1 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

    pSk_buff_test = IMM_ZcDequeueHead_Debug(10, 10, pSk_buff_head);
    if (pSk_buff != pSk_buff_test)
    {
        iRet = -1;
        goto test_fail;
    }

    if (0 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff_head);
    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

int test_IMM_ZcDequeueTail_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
     return 0;
#else

    int iRet = 0;
    struct sk_buff_head *pSk_buff_head = 0;
    struct sk_buff *pSk_buff = 0;
    struct sk_buff *pSk_buff_test = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff_head, pSk_buff_head);
    if (0 == pSk_buff_head)
    {
        return -1;
    }

    TEST_IMM_STRUCT_ALLOC(sk_buff, pSk_buff);
    if (0 == pSk_buff)
    {
        return -1;
    }

    IMM_ZcQueueHeadInit_Debug(10, 10, pSk_buff_head);
    if (0 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

    IMM_ZcQueueTail_Debug(10, 10, pSk_buff_head, pSk_buff);
    if (1 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }

    pSk_buff_test = IMM_ZcDequeueTail_Debug(10, 10, pSk_buff_head);
    if (pSk_buff != pSk_buff_test)
    {
        iRet = -1;
        goto test_fail;
    }

    if (0 != pSk_buff_head->qlen)
    {
        iRet = -1;
        goto test_fail;
    }
test_fail:
    TEST_IMM_STRUCT_FREE(pSk_buff_head);
    TEST_IMM_STRUCT_FREE(pSk_buff);

    return iRet;
#endif
}

int test_IMM_ZcQueueLen_Debug(void)
{
#if (FEATURE_ON == FEATURE_SKB_EXP)
     return 0;
#else

    int iRet = 0;
    struct sk_buff_head *pSk_buff_head = 0;

    TEST_IMM_STRUCT_ALLOC(sk_buff_head, pSk_buff_head);
    if (0 == pSk_buff_head)
    {
        return -1;
    }

    pSk_buff_head->qlen = 100;
    if (100 != IMM_ZcQueueLen_Debug(10, 10, pSk_buff_head))
        iRet = -1;

    TEST_IMM_STRUCT_FREE(pSk_buff_head);

    return iRet;
#endif
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
