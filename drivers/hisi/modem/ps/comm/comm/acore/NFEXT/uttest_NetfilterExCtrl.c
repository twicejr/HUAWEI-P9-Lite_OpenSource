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
#include "IpsMntn.h"
#include "LinuxInterface.h"

#if (FEATURE_ON == FEATURE_NFEXT)
#include "NetfilterEx.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern NF_EXT_ENTITY_STRU                  g_stExEntity;
extern NF_EXT_FLOW_CTRL_ENTITY             g_stExFlowCtrlEntity;
#if(NF_EXT_DBG == DBG_ON)
extern NF_EXT_STATS_STRU                   g_stNfExtStats;
#endif
extern NF_EXT_NV_STRU                      g_stNfExtNv;
extern NF_EXT_HOOK_MASK_NV_STRU            g_stExHookMask;

#define TEST_IMM_STRUCT_ALLOC(s, pStruct) \
{ \
    pStruct = (struct s *)malloc(sizeof(struct s));    \
}

#define TEST_IMM_STRUCT_FREE(pStruct) free(pStruct)

unsigned int uDataRingSize   = sizeof(NF_EXT_DATA_RING_BUF_STRU);

/*****************************************************************************
  3 函数实现
*****************************************************************************/
int test_NFExt_RegHooks(void)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int iRet = 0;

    g_stExEntity.ulCurHookOnMask = 0;

    NFExt_RegHooks(NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK);

    if (NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK != (g_stExEntity.ulCurHookOnMask & NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK))
    {
        iRet = -1;
        goto test_fail;
    }

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_ReRegHooks(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int iRet = 0;

    if (0 == iTest)
    {
        g_stExEntity.ulCurHookOnMask = 0;
    }
    else
    {
        g_stExEntity.ulCurHookOnMask = NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK;
    }

    NFExt_ReRegHooks(NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK);
    if (NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK != (g_stExEntity.ulCurHookOnMask & NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK))
    {
        iRet = -1;
        goto test_fail;
    }

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_ConfigEffective(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int iRet = 0;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU stRcvMsg;
    PS_BOOL_ENUM_UINT8 enTestFunRet;

    stRcvMsg.stBridgeArpTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;

    g_stExEntity.ulCurHookOnMask = 0;
    NF_EXT_DEF_FLOW_CTRL_HOOK_ON_MASK = NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK;

    enTestFunRet = NFExt_ConfigEffective(&stRcvMsg);
    if (PS_TRUE != enTestFunRet)
    {
        iRet = -1;
        goto test_fail;
    }

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_Get1stInetIpv4Addr(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int iRet = 0;
    unsigned int uTestFunRet;
    struct net_device stDev;
    struct in_device *in_dev;
    struct in_ifaddr *inet_ifa;

    in_dev = malloc(sizeof(struct in_device));
    if (!in_dev)
    {
        iRet = -1;
        return iRet;
    }

    inet_ifa = malloc(sizeof(struct in_ifaddr));
    if (!inet_ifa)
    {
        iRet = -1;
        free(in_dev);
        return iRet;
    }

    if (0 == iTest)
    {
        uTestFunRet = NFExt_Get1stInetIpv4Addr(0);
        if (0 == uTestFunRet)
        {
            iRet = -1;
            goto test_fail;
        }
    }
    else if (1 == iTest)
    {
        stDev.ip_ptr = 0;
        uTestFunRet = NFExt_Get1stInetIpv4Addr(&stDev);
        if (0 == uTestFunRet)
        {
            iRet = -1;
            goto test_fail;
        }
    }
    else if (2 == iTest)
    {
        stDev.ip_ptr = in_dev;
        stDev.ip_ptr->ifa_list = 0;
        uTestFunRet = NFExt_Get1stInetIpv4Addr(&stDev);
        if (0 == uTestFunRet)
        {
            iRet = -1;
            goto test_fail;
        }
    }
    else
    {
        stDev.ip_ptr = in_dev;
        stDev.ip_ptr->ifa_list = inet_ifa;

        INIT_HLIST_NODE(&stDev.ip_ptr->ifa_list->hash);

        stDev.ip_ptr->ifa_list->ifa_address = 0x7f000001;
        uTestFunRet = NFExt_Get1stInetIpv4Addr(&stDev);
        #ifdef CONFIG_64BIT
        if (0x0100007f != uTestFunRet)
        {
            iRet = -1;
            goto test_fail;
        }
        #else
        #endif
    }

    /* 检查是否 */
test_fail:
    free(in_dev);
    free(inet_ifa);
    return iRet;
#endif
}

int test_NFExt_RcvNfExtInfoCfgReq(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    OM_PS_PARAM_REQ_STRU                    stOmMsg;

    NFExt_RcvNfExtInfoCfgReq((void *)&stOmMsg);


    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_SelfTaskInit(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;

    NFExt_SelfTaskInit();


    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_RingBufferPut(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    OM_RING                                 stOmRing;
    char buf[80];

    NFExt_RingBufferPut(&stOmRing, buf, 80);


    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_RingBufferGet(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    OM_RING                                 stOmRing;
    char buf[80];

    stOmRing.pToBuf = 2;
    stOmRing.pFromBuf = 1;

    NFExt_RingBufferGet(&stOmRing, buf, 80);


    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_FlushRingBuffer(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    OM_RING                                 stOmRing;

    NFExt_FlushRingBuffer(&stOmRing);


    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_AddDataToRingBuf(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    OM_RING                                 stOmRing;
    NF_EXT_DATA_RING_BUF_STRU               stData;
    unsigned int                            uTestFunRet;

    if (0 == iTest)
    {
        g_stExEntity.pRingBufferId = 0;
        goto testfun;
    }
    else
    {
        g_stExEntity.pRingBufferId = &stOmRing;
        goto testfun;
    }

testfun:
    uTestFunRet = NFExt_AddDataToRingBuf(&stData);
    if (VOS_ERR == uTestFunRet)
    {
        iRet = -1;
    }

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_CtrlTxMsgTask(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    OM_RING                                 stOmRing;
    NF_EXT_DATA_RING_BUF_STRU               stData;
    unsigned int                            uTestFunRet;

    if (0 == iTest)
    {
        g_stExEntity.pRingBufferId = 0;
        goto testfun;
    }
    else
    {
        g_stExEntity.pRingBufferId      = &stOmRing;
        goto testfun;
    }

testfun:
    NFExt_CtrlTxMsgTask();


    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_ReadNvCfg(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    unsigned int                            uTestFunRet;

    uTestFunRet = NFExt_ReadNvCfg();
    if (VOS_ERR == uTestFunRet)
    {
        iRet = -1;
        goto test_fail;
    }

    /* Set the default value */
    NFExt_SetDefaultNvCfg();

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_Init(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    unsigned int                            uTestFunRet;

    uTestFunRet = NFExt_Init();

    /* UnInit */
    NFExt_Uninit();

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_BrFlowCtrl(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    unsigned int                            uTestFunRet;

    NFExt_FlowCtrlInit();

    NFExt_BrSetFlowCtrl();

    NFExt_BrStopFlowCtrl();

    NFExt_GetBrBytesCnt();

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_SaveBrDev(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    unsigned int                            uTestFunRet;

    uTestFunRet = NFExt_SaveBrDev();
    if (VOS_ERR == uTestFunRet)
    {
        iRet = -1;
        goto test_fail;
    }

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_ResetPri(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    unsigned int                            uTestFunRet;

#if(NF_EXT_DBG == DBG_ON)
    if (0 == iTest)
    {
        NFExt_ResetPri(1000, 100);
    }
    else
    {
        NFExt_ResetPri(0, 100);
    }
#endif

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_RcvOmMsg(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    unsigned int                            uTestFunRet;
    char                                    buf[80];
    unsigned short *                        usMsgType;

    usMsgType   = (unsigned short *)&buf[VOS_MSG_HEAD_LENGTH];

    *usMsgType  = ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ;
    NFExt_RcvOmMsg((void *)&buf);

    *usMsgType  = ID_OM_IPS_MNTN_INFO_CONFIG_REQ;
    NFExt_RcvOmMsg((void *)&buf);

    *usMsgType  = ID_OM_IPS_MNTN_IP_INFO_CONFIG_REQ;
    NFExt_RcvOmMsg((void *)&buf);

    *usMsgType  = ID_IPS_MNTN_TRACE_CONFIG_TYPE_BUTT;
    NFExt_RcvOmMsg((void *)&buf);

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_MsgProc(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    unsigned int                            uTestFunRet;
    char                                    buf[80];
    unsigned short *                        usMsgType;
    struct MsgCB *                          pMsg = (struct MsgCB *)&buf;

    if (0 == iTest)
    {
        NFExt_MsgProc((struct MsgCB *)0);
    }
    else if (1 == iTest)
    {
        usMsgType   = (unsigned short *)&buf[VOS_MSG_HEAD_LENGTH];
        *usMsgType  = ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ;
        pMsg->ulSenderPid = 0;
        NFExt_MsgProc(pMsg);
    }
    else
    {
        usMsgType   = (unsigned short *)&buf[VOS_MSG_HEAD_LENGTH];
        *usMsgType  = ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ;
        pMsg->ulSenderPid = WUEPS_PID_OM;
        NFExt_MsgProc(pMsg);
    }

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

int test_NFExt_FidInit(int iTest)
{
#if (FEATURE_OFF == FEATURE_NFEXT)
    return 0;
#else
    int                                     iRet    = 0;
    unsigned int                            uTestFunRet;

    if (0 == iTest)
    {
        NFExt_FidInit(100);
    }
    else if (1 == iTest)
    {
        NFExt_FidInit(VOS_IP_FARMALLOC);
    }
    else
    {
        uTestFunRet = NFExt_FidInit(VOS_IP_LOAD_CONFIG);
        if (PS_FAIL == uTestFunRet)
        {
            iRet = -1;
            goto test_fail;
        }
    }

    /* 检查是否 */
test_fail:
    return iRet;
#endif
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
