/*****************************************************************************
1 头文件包含
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicEntity.h"


//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;


#if 0
/*****************************************************************************
2 用例实现
*****************************************************************************/

/*****************************************************************************
类名       : Test_RNIC_StopNetCard
功能描述   : RNIC_StopNetCard UT工程类
修改历史   :
1.日   期  : 2011-12-09
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_StopNetCard: public ::testing::Test
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
测试用例编号      : Test_RNIC_StopNetCard_001
测试用例标题      : 网卡指针为空
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-09
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StopNetCard, Test_RNIC_StopNetCard_001)
{
    VOS_INT                             lRst;
    struct net_device                   *pstNetDev = VOS_NULL_PTR;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    lRst = RNIC_StopNetCard(pstNetDev);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(RNIC_ERROR, lRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_StopNetCard_002
测试用例标题      : 网卡私有数据指针为空
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-09
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StopNetCard, Test_RNIC_StopNetCard_002)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(netif_stop_queue)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    lRst = RNIC_StopNetCard(&stNetDev);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(RNIC_ERROR, lRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_RNIC_StopNetCard_003
测试用例标题      : 网卡停止成功
预期结果          : 网卡状态标志置为关闭,返回RNIC_OK
修改历史   :
1.日   期  : 2011-12-09
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StopNetCard, Test_RNIC_StopNetCard_003)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    MOCKER(netif_stop_queue)
        .expects(exactly(1));

    /* 函数调用 */

    /* 调用入口函数 */
    lRst = RNIC_StopNetCard(&stNetDev);

    /* 获取结果 */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(&stNetDev);

    /* 参数匹配 */
    EXPECT_EQ(RNIC_OK, lRst);
    EXPECT_EQ(RNIC_NETCARD_STATUS_CLOSED, pstPriv->enStatus);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_OpenNetCard
功能描述   : RNIC_OpenNetCard UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_OpenNetCard: public ::testing::Test
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
测试用例编号      : Test_RNIC_OpenNetCard_001
测试用例标题      : 网卡指针为空
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_OpenNetCard, Test_RNIC_OpenNetCard_001)
{
    VOS_INT                             lRst;
    struct net_device                   *pstNetDev = VOS_NULL_PTR;

    /* 参数初始化 */

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(never());

    /* 函数调用 */

    /* 调用入口函数 */
    lRst = RNIC_OpenNetCard(pstNetDev);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(RNIC_ERROR, lRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_OpenNetCard_002
测试用例标题      : 网卡私有结构指针为空
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_OpenNetCard, Test_RNIC_OpenNetCard_002)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_OpenNetCard(&stNetDev);

    /* 获取结果 */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, lRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_OpenNetCard_003
测试用例标题      : 该设备如果已经打开
预期结果          : 返回RNIC_BUSY
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_OpenNetCard, Test_RNIC_OpenNetCard_003)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    ucIndex = 0;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_OpenNetCard(&stNetDev);

    /* 获取结果 */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_BUSY, lRst);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_OpenNetCard_004
测试用例标题      : 网卡停止成功
预期结果          : 网卡状态标志置为打开,返回RNIC_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_OpenNetCard, Test_RNIC_OpenNetCard_004)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    stPriv.enStatus = RNIC_NETCARD_STATUS_CLOSED;
    ucIndex = 0;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_OpenNetCard(&stNetDev);

    /* 获取结果 */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_StartXmit
功能描述   : RNIC_StartXmit UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_StartXmit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));

        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_001
测试用例标题      : 网卡指针为空
预期结果          : 返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_001)
{
    netdev_tx_t                         enRst;
    struct sk_buff                     *pstSkb;
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    pstSkb = IMM_ZcStaticAlloc(4);
    ucIndex = 0;

    /* 桩函数 */

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,pstNetDev);

    /* 获取结果 */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_002
测试用例标题      : 收到的数据无效
预期结果          : 返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_002)
{
    netdev_tx_t                         enRst;
    struct sk_buff                     *pstSkb    = VOS_NULL_PTR;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    /* 桩函数 */

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_003
测试用例标题      : 根据网卡设备获取不到网卡ID
预期结果          : 返回NETDEV_TX_OK，网卡错误丢包个数加1
修改历史   :
1.日   期  : 2012-12-5
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_003)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    VOS_sprintf(stNetDev.name, "RNIC");

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xFFFFFFFF;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));

    pstPriv->enRmNetId  = RNIC_NET_ID_MAX_NUM;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlNetIdDiscardNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_004
测试用例标题      : 流控启动时, 直接丢弃数据包
预期结果          : 返回NETDEV_TX_OK，流控启动丢包个数加1
修改历史   :
1.日   期  : 2012-12-5
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_004)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;
    RNIC_CTX_STRU                      *pstRnicCtx;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstRnicCtx = RNIC_GetRnicCtxAddr();
    pstRnicCtx->astSpecCtx[ucIndex].enFlowCtrlStatus = RNIC_FLOW_CTRL_STATUS_START;

    aulIpHeader[0] = 0x00;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;


    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
#if (0)
    MOCKER(ADS_UL_IsSendPermit)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));
#endif

    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlFlowCtrlDiscardNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_005
测试用例标题      : IPV4 PDP未激活的情况下，收到广播包的情况
预期结果          : 返回NETDEV_TX_OK，上行收到的广播包加1
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_005)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;

    VOS_sprintf(stNetDev.name, g_astRnicManageTbl[ucIndex].pucRnicNetCardName);
    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    pstDialMode = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xFFFFFFFF;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlIpv4BrdcstPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    //EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_006
测试用例标题      : IPV4 PDP未激活的情况下，收到有效数据包的情况，通知APP拨号成功
预期结果          : 返回NETDEV_TX_OK,按需拨号成功全局变量加1
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_006)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTiStatus;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    pstDialMode = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode       = AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT;
    pstDialMode->enEventReportFlag = RNIC_ALLOW_EVENT_REPORT;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(device_event_report)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(V_GetRelTmRemainTime)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);
    enTiStatus                          = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_PROTECT);


    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendAppDialUpSucc);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTiStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_007
测试用例标题      : IPV4 PDP未激活的情况下，收到有效数据包的情况，通知APP拨号失败
预期结果          : 返回NETDEV_TX_OK,按需拨号失败全局变量加1
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_007)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTiStatus;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    pstDialMode = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode       = AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT;
    pstDialMode->enEventReportFlag = RNIC_ALLOW_EVENT_REPORT;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(device_event_report)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);
    enTiStatus                          = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_PROTECT);


    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendAppDialUpFail);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTiStatus);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_008
测试用例标题      : 无效的IP报文
预期结果          : 返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_008)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x00;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlRecvErrPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/* Added by m00217266 for L-C互操作项目, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_009
测试用例标题      : 外部modem ipv4数据包发送成功
预期结果          : 返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_009)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    MOCKER(SDIO_UL_SendPacket)
        .expects(exactly(1))
        .will(returnValue(SDIO_OK));


    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_010
测试用例标题      : 外部modem ipv6数据包发送成功
预期结果          : 返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_010)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    MOCKER(SDIO_UL_SendPacket)
        .expects(exactly(1))
        .will(returnValue(SDIO_OK));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_011
测试用例标题      : 外部modem ipv6数据包，但IPV6未激活
预期结果          : 释放数据包内存，返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_011)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlPdnIdErr);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_012
测试用例标题      : 外部modem ipv6数据包发送失败
预期结果          : 释放数据包内存，返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_012)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    MOCKER(SDIO_UL_SendPacket)
        .expects(exactly(1))
        .will(returnValue(SDIO_ERR));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_013
测试用例标题      : 外部modem 发送非ipv4、ipv6数据包
预期结果          : 释放数据包内存，返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_013)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x00;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    MOCKER(SDIO_UL_SendPacket)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlRecvErrPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_RNIC_StartXmit_014
测试用例标题      : modem type 异常
预期结果          : 释放数据包内存，返回NETDEV_TX_OK
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_014)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* 参数初始化 */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_BUTT;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(RNIC_RcvInsideModemUlData)
        .expects(never());

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    MOCKER(RNIC_RcvOutsideModemUlData)
        .expects(never());
#endif

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 参数匹配 */
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/* Added by m00217266 for L-C互操作项目, 2014-2-7, end */

/*****************************************************************************
类名       : Test_RNIC_SendULIpv6Data
功能描述   : RNIC_SendULIpv6Data UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_SendULIpv6Data: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;
    IMM_ZC_STRU                        *pstImmZc;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    struct sk_buff                     *pstSkb;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 分配A核共享内存 */
        pstImmZc = IMM_ZcStaticAlloc(20);

        /* 分配私有数据空间 */
        pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

        /* 分配SKBUF内存 */
        pstSkb = (struct sk_buff *)IMM_ZcStaticAlloc(20);
        /* 分配IP头内存 */


        /* 初始化RNIC上下文 */
        pstRnicCtx  = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));

        if (VOS_NULL_PTR != pstPriv)
        {
            free(pstPriv);
        }
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv6Data_001
测试用例标题      : 收到IPV6的数据，但是RABID无效时
预期结果          : 上行rab err丢包数加1
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv6Data, Test_RNIC_SendULIpv6Data_001)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 0xff;

    /* 填充IP协议类型 */
    aulIpHeader[0] = 0x60;
    /* 填充目的地址 */
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(never());

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb, &stNetDev);

    /* 获取结果 */
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlRabIdErr);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

#if(0)
/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv6Data_002
测试用例标题      : IPV6激活的情况下,收到由Linux系统提供IPV6的数据包,跨核内存拷贝失败
预期结果          : 上行丢包加1
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv6Data, Test_RNIC_SendULIpv6Data_002)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 12;

    /* 填充IP协议类型 */
    aulIpHeader[0] = 0x60;
    /* 填充目的地址 */
    aulIpHeader[4] = 0x0;

    pstSkb->len = sizeof(VOS_UINT32)*5;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(never());

    MOCKER(IMM_ZcStaticCopy_Debug)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never())
        .will(returnValue(VOS_OK));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(0, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlImmzcFailPktNum);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv6Data_003
测试用例标题      : IPV6激活的情况下,收到由Linux系统提供的IPV6非modem0或1的数据包,跨核内存拷贝成功
预期结果          : 发包数加1
修改历史   :
1.日   期  : 2011-12-29
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv6Data, Test_RNIC_SendULIpv6Data_003)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(0, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(1, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(0, g_astRnicStats[ucIndex].ulUlModemIdDiscardNum);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#else
/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv6Data_004
测试用例标题      : IPV6激活的情况下,收到由Linux系统提供的IPV6非modem0或1的数据包,跨核内存拷贝成功
预期结果          : 发包数加1
修改历史   :
1.日   期  : 2011-12-29
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv6Data, Test_RNIC_SendULIpv6Data_004)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;
    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0x0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(0, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(1, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(0, g_astRnicStats[ucIndex].ulUlModemIdDiscardNum);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#endif

/*****************************************************************************
类名       : Test_RNIC_SendULIpv4Data
功能描述   : RNIC_SendULIpv4Data UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_SendULIpv4Data: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;
    IMM_ZC_STRU                        *pstImmZc;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    struct sk_buff                     *pstSkb;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 分配A核共享内存 */
        pstImmZc = IMM_ZcStaticAlloc(sizeof(struct sk_buff));

        /* 分配私有数据空间 */
        pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));

        /* 分配SKBUF内存 */
        pstSkb = (struct sk_buff *)IMM_ZcStaticAlloc(sizeof(struct sk_buff));
        /* 分配IP头内存 */



        /* 初始化RNIC上下文 */
        pstRnicCtx  = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));

        if (VOS_NULL_PTR != pstPriv)
        {
            free(pstPriv);
        }

    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv4Data_001
测试用例标题      : 收到IPV4的数据，但是RABID无效时
预期结果          : 上行丢包数加1
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_001)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 0xff;

    /* 填充IP协议类型 */
    aulIpHeader[0] = 0x40;
    /* 填充目的地址 */
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(never());

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlRabIdErr);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#if(0)
/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv4Data_002
测试用例标题      : IPV4激活的情况下,收到由用户管理系统提供IPV4的数据包,A核共享内存池以外的内存,跨核内存拷贝失败
预期结果          : 上行丢包加1
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_002)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 12;

    stImmMem.enPoolId = IMM_MEM_POOL_ID_EXT;

    /* 填充IP协议类型 */
    aulIpHeader[0] = 0x40;
    /* 填充目的地址 */
    aulIpHeader[4] = 0x0;

    pstSkb->len = sizeof(VOS_UINT32)*5;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.pMem = &stImmMem;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(never());

    MOCKER(IMM_ZcStaticCopy_Debug)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never())
        .will(returnValue(VOS_OK));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(0, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlImmzcFailPktNum);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv4Data_003
测试用例标题      : IPV4激活的情况下,收到由用户管理系统提供IPV4的modem0的数据包,A核共享内存池以外的内存,跨核内存拷贝成功
预期结果          : 丢包数加1
修改历史   :
1.日   期  : 2011-12-29
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_003)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 12;

    stImmMem.enPoolId = IMM_MEM_POOL_ID_EXT;

    /* 填充IP协议类型 */
    aulIpHeader[0] = 0x40;
    /* 填充目的地址 */
    aulIpHeader[4] = 0x0;

    pstSkb->len = sizeof(VOS_UINT32)*5;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.pMem = &stImmMem;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(exactly(1));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never())
        .will(returnValue(VOS_OK));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(0, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(0, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(0, g_astRnicStats[ucIndex].ulUlImmzcFailPktNum);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv4Data_004
测试用例标题      : IPV4激活的情况下,收到由用户管理系统提供A核共享内存池的modem0的IPV4数据包,A核共享内存池的内存,发送给ADS失败
预期结果          : 丢包数加1
修改历史   :
1.日   期  : 2011-12-29
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_004)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    stImmMem.enPoolId = IMM_MEM_POOL_ID_SHARE;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    pstSkb->private_mem.pMem = &stImmMem;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendPktFailNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#else

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv4Data_005
测试用例标题      : IPV4激活的情况下,收到由系统管理系统提供modem1的IPV4数据包,数据成功发给ADS
预期结果          : 发包数加1
修改历史   :
1.日   期  : 2012-09-03
  作   者  : L60609
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_005)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 3;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    stImmMem.enPoolId = IMM_MEM_POOL_ID_SHARE;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    pstSkb->private_mem.pMem = &stImmMem;

	pstPriv->enRmNetId = ucIndex;


    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
测试用例编号      : Test_RNIC_SendULIpv4Data_006
测试用例标题      : IPV4激活的情况下,收到由系统管理系统提供modem1的IPV4数据包,数据成功发给ADS
预期结果          : 发包数加1
修改历史   :
1.日   期  : 2012-09-03
  作   者  : L60609
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_006)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    stImmMem.enPoolId = IMM_MEM_POOL_ID_SHARE;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    pstSkb->private_mem.pMem = &stImmMem;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* 调用入口函数 */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* 获取结果 */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif

/*****************************************************************************
类名       : Test_RNIC_RcvAdsDlData
功能描述   : RNIC_RcvAdsDlData UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvAdsDlData: public ::testing::Test
{
public:
    IMM_ZC_STRU                        *pstImmZc;
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 分配A核共享内存 */
        pstImmZc = IMM_ZcStaticAlloc(20);

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
};
/*******************************************************************
测试用例编号      : Test_RNIC_RcvAdsDlData_001
测试用例标题      : 根据RABID获取不到网卡ID
预期结果          : 返回RNIC_INVAL
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_001)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    ucRabid = 6;
    enPktType = ADS_PKT_TYPE_IPV4;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    /* 桩函数 */

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, ucIndex);

    /* 调用入口函数 */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* 获取结果 */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(VOS_NULL_PTR, pstPriv);
    EXPECT_EQ(RNIC_INVAL, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAdsDlData_002
测试用例标题      : RNIC网卡的私有数据为空
预期结果          : 返回RNIC_INVAL
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_002)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 3;
    ucRabid = 0x45;
    enPktType = ADS_PKT_TYPE_IPV4;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    /* 桩函数 */

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, ucIndex);

    /* 调用入口函数 */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* 获取结果 */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(VOS_NULL_PTR, pstPriv);
    EXPECT_EQ(RNIC_INVAL, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAdsDlData_003
测试用例标题      : 网卡设备未打开
预期结果          : 丢包数加1，返回RNIC_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_003)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV4;
    stPriv.enStatus = RNIC_NETCARD_STATUS_CLOSED;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv4PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* 桩函数 */

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* 获取结果 */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, ulRst);
    EXPECT_EQ(1, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAdsDlData_004
测试用例标题      : skb数据长度超出有效值(不包含MAC头)
预期结果          : 错包数加1，返回RNIC_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_004)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV4;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET * 2;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv4PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* 桩函数 */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
     MOCKER(netif_rx_ni)
        .expects(never())
        .will(returnValue(NET_RX_DROP));
#else
    MOCKER(netif_rx_ni_balong)
        .expects(never())
        .will(returnValue(NET_RX_DROP));
#endif

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* 获取结果 */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, ulRst);
    EXPECT_EQ(1, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulDlRecvBigPktNum);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAdsDlData_005
测试用例标题      : ADS发来的IPV4数据包有效的情况下，发送给IPstack失败
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_005)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV4;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv4PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* 桩函数 */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(netif_rx_ni)
        .expects(exactly(1))
        .will(returnValue(NET_RX_DROP));
#else
    MOCKER(netif_rx_ni_balong)
        .expects(exactly(1))
        .will(returnValue(NET_RX_DROP));
#endif

    MOCKER(RNIC_AddMacHead)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* 函数调用 */
     RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* 获取结果 */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, ulRst);
    EXPECT_EQ(1, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAdsDlData_006
测试用例标题      : ADS发来的IPV6数据包有效的情况下，发送给IPstack成功
预期结果          : 流量统计信息增加，返回RNIC_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_006)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV6;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv6PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* 桩函数 */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
     MOCKER(netif_rx_ni)
         .expects(exactly(1))
         .will(returnValue(NET_RX_SUCCESS));
#else
     MOCKER(netif_rx_ni_balong)
         .expects(exactly(1))
         .will(returnValue(NET_RX_SUCCESS));
#endif

     MOCKER(RNIC_AddMacHead)
         .expects(exactly(1))
         .will(returnValue(VOS_OK));

     /* 函数调用 */
     RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* 获取结果 */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, ulRst);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);
    EXPECT_EQ(pstImmZc->len, pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes);
    EXPECT_NE(0, pstDlCtx->stDLDataStats.ulDLTotalRcvBytes);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAdsDlData_007
测试用例标题      : ADS发来的IPV6数据包类型与承载支持类型不一致
预期结果          : 下行err数据包加1，返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_007)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_BUTT;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv6PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* 桩函数 */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(netif_rx_ni)
        .expects(never())
        .will(returnValue(NET_RX_SUCCESS));
#else
    MOCKER(netif_rx_ni_balong)
        .expects(never())
        .will(returnValue(NET_RX_SUCCESS));
#endif

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* 获取结果 */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, ulRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvAdsDlData_008
测试用例标题      : ADS发来的IPV4数据包有效的情况下，发送给IPstack失败
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_008)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV4;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv4PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* 桩函数 */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(netif_rx_ni)
        .expects(never())
        .will(returnValue(NET_RX_DROP));
#else
    MOCKER(netif_rx_ni_balong)
        .expects(never())
        .will(returnValue(NET_RX_DROP));
#endif

    MOCKER(RNIC_AddMacHead)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* 函数调用 */
     RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* 获取结果 */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, ulRst);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_SetMacAddress
功能描述   : RNIC_SetMacAddress UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_SetMacAddress: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_SetMacAddress_001
测试用例标题      : RNIC网卡网卡指针为空
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SetMacAddress, Test_RNIC_SetMacAddress_001)
{
    VOS_INT                             lRst;
    struct sockaddr                     stMacAddr;
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    /* 桩函数 */
    MOCKER(is_valid_ether_addr)
        .expects(never());

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_SetMacAddress(pstNetDev, (void *)&stMacAddr);

    /* 获取结果 */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_SetMacAddress_002
测试用例标题      : 设置的MAC地址无效
预期结果          : 返回RNIC_ADDR_INVALID
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SetMacAddress, Test_RNIC_SetMacAddress_002)
{
    VOS_INT                             lRst;
    struct sockaddr                     stMacAddr;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    /* 桩函数 */
    MOCKER(is_valid_ether_addr)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_SetMacAddress(&stNetDev, (void *)&stMacAddr);

    /* 获取结果 */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ADDR_INVALID, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_SetMacAddress_003
测试用例标题      : 网卡指针的dev_addr为空
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SetMacAddress, Test_RNIC_SetMacAddress_003)
{
    VOS_INT                             lRst;
    struct sockaddr                     stMacAddr;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    stNetDev.dev_addr = VOS_NULL_PTR;

    /* 桩函数 */
    MOCKER(is_valid_ether_addr)
        .expects(exactly(1))
        .will(returnValue(VOS_TRUE));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_SetMacAddress(&stNetDev, (void *)&stMacAddr);

    /* 获取结果 */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_SetMacAddress_004
测试用例标题      : 设置MAC地址成功
预期结果          : 返回RNIC_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_SetMacAddress, Test_RNIC_SetMacAddress_004)
{
    VOS_INT                             lRst;
    VOS_UINT8                           ucAddr;
    struct sockaddr                     stMacAddr;
    struct net_device                  *pstNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    pstNetDev = (struct net_device *)malloc(sizeof(struct net_device));
    VOS_MemSet(pstNetDev, 0, sizeof(struct net_device));
    pstNetDev->dev_addr = &ucAddr;

    /* 桩函数 */
    MOCKER(is_valid_ether_addr)
        .expects(exactly(1))
        .will(returnValue(VOS_TRUE));

    /* 函数调用 */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_SetMacAddress(pstNetDev, (void *)&stMacAddr);

    /* 获取结果 */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_ChangeMtu
功能描述   : RNIC_ChangeMtu UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_ChangeMtu: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_ChangeMtu_001
测试用例标题      : RNIC网卡网卡指针为空
预期结果          : 返回RNIC_ERROR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_ChangeMtu, Test_RNIC_ChangeMtu_001)
{
    VOS_INT                             lRst;
    VOS_INT                             lNewMtu;
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    lNewMtu = 1;

    /* 桩函数 */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_ChangeMtu(pstNetDev, lNewMtu);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_ChangeMtu_002
测试用例标题      : 设置的的MTU不在有效范围内
预期结果          : 返回RNIC_OUT_RANGE
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_ChangeMtu, Test_RNIC_ChangeMtu_002)
{
    VOS_INT                             lRst;
    VOS_INT                             lNewMtu;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    lNewMtu = RNIC_MAX_PACKET + 1;

    /* 桩函数 */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_ChangeMtu(&stNetDev, lNewMtu);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OUT_RANGE, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_ChangeMtu_003
测试用例标题      : 设置的MTU值成功
预期结果          : 返回RNIC_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_ChangeMtu, Test_RNIC_ChangeMtu_003)
{
    VOS_INT                             lRst;
    VOS_INT                             lNewMtu;
    struct net_device                   *pstNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;
    lNewMtu = RNIC_MAX_PACKET;
    pstNetDev = (struct net_device *)malloc(sizeof(struct net_device));
    VOS_MemSet(pstNetDev, 0, sizeof(struct net_device));
    pstNetDev->mtu = 1000;

    /* 桩函数 */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    lRst = RNIC_ChangeMtu(pstNetDev, lNewMtu);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, lRst);
    EXPECT_EQ(RNIC_MAX_PACKET, pstNetDev->mtu);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_ProcTxTimeout
功能描述   : RNIC_ProcTxTimeout UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_ProcTxTimeout: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_ProcTxTimeout_001
测试用例标题      : RNIC网卡网卡指针为空
预期结果          : 打印错误信息
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_ProcTxTimeout, Test_RNIC_ProcTxTimeout_001)
{
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    /* 桩函数 */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    RNIC_ProcTxTimeout(pstNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_ProcTxTimeout_002
测试用例标题      : 网卡指针不为空
预期结果          : 打印正常信息
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_ProcTxTimeout, Test_RNIC_ProcTxTimeout_002)
{
    struct net_device                   stNetDev ;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    /* 桩函数 */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    RNIC_ProcTxTimeout(&stNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_Ioctrl
功能描述   : RNIC_Ioctrl UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_Ioctrl: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_Ioctrl_001
测试用例标题      : 不做处理
预期结果          : 返回RNIC_NOTSUPP
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_Ioctrl, Test_RNIC_Ioctrl_001)
{
    struct net_device                   stNetDev;
    struct ifreq                        stIfr;
    VOS_INT                             lCmd;
    VOS_INT                             lRst;

    /* 参数初始化 */
    lCmd = 1;

    /* 桩函数 */

    /* 函数调用 */

    /* 调用入口函数 */
    lRst = RNIC_Ioctrl(&stNetDev, &stIfr, lCmd);

    /* 获取结果 */

    /* 参数匹配 */
    EXPECT_EQ(RNIC_NOTSUPP, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_DeinitNetCard
功能描述   : RNIC_DeinitNetCard UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_DeinitNetCard: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};
/*******************************************************************
测试用例编号      : Test_RNIC_DeinitNetCard_001
测试用例标题      : RNIC网卡指针为空
预期结果          : 不需要释放网卡设备指针
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_DeinitNetCard, Test_RNIC_DeinitNetCard_001)
{
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    /* 桩函数 */
    MOCKER(netif_carrier_off)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    MOCKER(unregister_netdev)
        .expects(never());

    MOCKER(free_netdev)
        .expects(never());

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    RNIC_DeinitNetCard(pstNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
/*******************************************************************
测试用例编号      : Test_RNIC_DeinitNetCard_002
测试用例标题      : 根据设备获取不到网卡ID
预期结果          : 不需要释放网卡设备指针
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_DeinitNetCard, Test_RNIC_DeinitNetCard_002)
{
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    stPriv.enRmNetId = RNIC_NET_ID_MAX_NUM;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    MOCKER(netif_carrier_off)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    MOCKER(unregister_netdev)
        .expects(never());

    MOCKER(free_netdev)
        .expects(never());

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    RNIC_DeinitNetCard(&stNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv, pstPriv);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_DeinitNetCard_003
测试用例标题      : RNIC网卡去初始化成功
预期结果          : 网卡设备指针为空
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_DeinitNetCard, Test_RNIC_DeinitNetCard_003)
{
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* 参数初始化 */
    ucIndex = 0;

    VOS_MemSet(&stNetDev, 0, sizeof(struct net_device));
    VOS_sprintf(stNetDev.name, "eth_x");

    stPriv.enRmNetId = RNIC_RM_NET_ID_0;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    MOCKER(netif_carrier_off)
        .expects(exactly(1));

    MOCKER(netif_stop_queue)
        .expects(exactly(1));

    MOCKER(unregister_netdev)
        .expects(exactly(1));

    MOCKER(free_netdev)
        .expects(exactly(1));

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* 调用入口函数 */
    RNIC_DeinitNetCard(&stNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* 参数匹配 */
    EXPECT_EQ(VOS_NULL_PTR, pstPriv);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_GetNetCardStats
功能描述   : RNIC_GetNetCardStats UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_GetNetCardStats: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_GetNetCardStats_001
测试用例标题      : RNIC网卡指针为空
预期结果          : 返回VOS_NULL_PTR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_GetNetCardStats, Test_RNIC_GetNetCardStats_001)
{
    struct net_device_stats            *pstStats;
    struct net_device                  *pstNetDev = VOS_NULL_PTR;

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(never());

    /* 调用入口函数 */
    pstStats = RNIC_GetNetCardStats(pstNetDev);

    /* 参数匹配 */
    EXPECT_EQ(VOS_NULL_PTR, pstStats);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_GetNetCardStats_002
测试用例标题      : RNIC网卡私有数据为空
预期结果          : 返回VOS_NULL_PTR
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_GetNetCardStats, Test_RNIC_GetNetCardStats_002)
{
    struct net_device_stats            *pstStats;
    struct net_device                   stNetDev;

    VOS_MemSet(&stNetDev, 0, sizeof(struct net_device));

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    /* 调用入口函数 */
    pstStats = RNIC_GetNetCardStats(&stNetDev);

    /* 参数匹配 */
    EXPECT_EQ(VOS_NULL_PTR, pstStats);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_GetNetCardStats_003
测试用例标题      : 获取网卡数据信息成功
预期结果          : 返回获取到得数据
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_GetNetCardStats, Test_RNIC_GetNetCardStats_003)
{
    struct net_device_stats            *pstStats;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    struct net_device_stats             stStats;

    VOS_MemSet(&stNetDev, 0, sizeof(struct net_device));
    VOS_MemSet(&stPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(&stStats, 0, sizeof(struct net_device_stats));

    VOS_MemCpy(&stPriv.stStats, &stStats, sizeof(stStats));

    /* 桩函数 */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(&stPriv));

    /* 调用入口函数 */
    pstStats = RNIC_GetNetCardStats(&stNetDev);

    /* 参数匹配 */
    EXPECT_EQ(&stPriv.stStats, pstStats);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*****************************************************************************
类名       : Test_RNIC_InitNetCard
功能描述   : RNIC_InitNetCard UT工程类
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_InitNetCard: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 初始化RNIC上下文 */
        pstRnicCtx  = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        /* 初始化RNIC上下文 */
        pstRnicCtx  = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_InitNetCard_001
测试用例标题      : RNIC网卡指针为空
预期结果          : 返回RNIC_NOMEM
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_InitNetCard, Test_RNIC_InitNetCard_001)
{
    VOS_INT                             lRst;

    /* 桩函数 */
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(netif_carrier_off)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    MOCKER(register_netdev)
        .expects(never());

    MOCKER(netif_carrier_on)
        .expects(never());

    MOCKER(netif_start_queue)
        .expects(never());

    /* 调用入口函数 */
    lRst = RNIC_InitNetCard();

    /* 参数匹配 */
    EXPECT_EQ(RNIC_NOMEM, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_InitNetCard_002
测试用例标题      : RNIC网卡MAC地址指针为空
预期结果          : 返回RNIC_NOMEM
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_InitNetCard, Test_RNIC_InitNetCard_002)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;

    stNetDev.dev_addr = VOS_NULL_PTR;

    /* 桩函数 */
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev));

    MOCKER(netif_carrier_off)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    MOCKER(register_netdev)
        .expects(never());

    MOCKER(free_netdev)
        .expects(exactly(1));

    MOCKER(netif_carrier_on)
        .expects(never());

    MOCKER(netif_start_queue)
        .expects(never());

    /* 调用入口函数 */
    lRst = RNIC_InitNetCard();

    /* 参数匹配 */
    EXPECT_EQ(RNIC_NOMEM, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


/*******************************************************************
测试用例编号      : Test_RNIC_InitNetCard_003
测试用例标题      : RNIC网卡注册失败
预期结果          : 返回RNIC_STATE
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_InitNetCard, Test_RNIC_InitNetCard_003)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    VOS_UINT8                           aucAddr[RNIC_MAC_ADDR_LEN] = {0x58,0x02,0x03,0x04,0x05,0x06};

    stNetDev.dev_addr = aucAddr;

    /* 桩函数 */
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev));

    MOCKER(netif_carrier_off)
        .expects(exactly(1));

    MOCKER(netif_stop_queue)
        .expects(exactly(1));

    MOCKER(register_netdev)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(&stPriv));

    MOCKER(free_netdev)
        .expects(exactly(1));

    MOCKER(netif_carrier_on)
        .expects(never());

    MOCKER(netif_start_queue)
        .expects(never());

    /* 调用入口函数 */
    lRst = RNIC_InitNetCard();

    /* 参数匹配 */
    EXPECT_EQ(RNIC_STATE, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_InitNetCard_004
测试用例标题      : RNIC虚拟网卡初始化成功
预期结果          : 返回RNIC_OK
修改历史   :
1.日   期  : 2011-12-10
  作   者  : f00179208
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_InitNetCard, Test_RNIC_InitNetCard_004)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev0;
    struct net_device                   stNetDev1;
    struct net_device                   stNetDev2;
    struct net_device                   stNetDev3;
    struct net_device                   stNetDev4;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    VOS_UINT8                           aucAddr[RNIC_NET_ID_MAX_NUM][RNIC_MAC_ADDR_LEN] = {
                                                {0x58,0x02,0x03,0x04,0x05,0x06},
                                                {0x58,0x02,0x03,0x04,0x05,0x07},
                                                {0x58,0x02,0x03,0x04,0x05,0x08},
                                                {0x58,0x02,0x03,0x04,0x05,0x09},
                                                {0x58,0x02,0x03,0x04,0x05,0x0a}
                                            };
#else
    VOS_UINT8                           aucAddr[RNIC_NET_ID_MAX_NUM][RNIC_MAC_ADDR_LEN] = {
                                                {0x58,0x02,0x03,0x04,0x05,0x06},
                                                {0x58,0x02,0x03,0x04,0x05,0x07},
                                                {0x58,0x02,0x03,0x04,0x05,0x08}
                                            };
#endif

    VOS_MemSet(&stNetDev0, 0, sizeof(struct net_device));
    VOS_MemSet(&stNetDev1, 0, sizeof(struct net_device));
    VOS_MemSet(&stNetDev2, 0, sizeof(struct net_device));
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    VOS_MemSet(&stNetDev3, 0, sizeof(struct net_device));
    VOS_MemSet(&stNetDev4, 0, sizeof(struct net_device));
    VOS_MemSet(&stPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
#endif
    stNetDev0.dev_addr = aucAddr[0];
    stNetDev1.dev_addr = aucAddr[1];
    stNetDev2.dev_addr = aucAddr[2];
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    stNetDev3.dev_addr = aucAddr[3];
    stNetDev4.dev_addr = aucAddr[4];
#endif
    /* 桩函数 */
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev0));
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev1));
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev2));
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev3));
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev4));
#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    MOCKER(netif_carrier_off)
        .expects(exactly(5));

    MOCKER(netif_stop_queue)
        .expects(exactly(5));

    MOCKER(register_netdev)
        .expects(exactly(5))
        .will(returnValue(VOS_OK));

    MOCKER(netdev_priv)
        .expects(exactly(5))
        .will(returnValue(&stPriv));

    MOCKER(netif_carrier_on)
        .expects(exactly(5));

    MOCKER(netif_start_queue)
        .expects(exactly(5));

#else
    MOCKER(netif_carrier_off)
        .expects(exactly(3));

    MOCKER(netif_stop_queue)
        .expects(exactly(3));

    MOCKER(register_netdev)
        .expects(exactly(3))
        .will(returnValue(VOS_OK));

    MOCKER(netdev_priv)
        .expects(exactly(3))
        .will(returnValue(&stPriv));

    MOCKER(netif_carrier_on)
        .expects(exactly(3));

    MOCKER(netif_start_queue)
        .expects(exactly(3));
#endif
    MOCKER(free_netdev)
        .expects(never());

    /* 调用入口函数 */
    lRst = RNIC_InitNetCard();

    /* 参数匹配 */
    EXPECT_EQ(RNIC_OK, lRst);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/* Added by m00217266 for L-C互操作项目, 2014-2-7, begin */
/*****************************************************************************
类名       : Test_RNIC_ConfigRmnetStatus
功能描述   : RNIC_ConfigRmnetStatus UT工程类
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_ConfigRmnetStatus: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_001
测试用例标题      : 网卡接入技术能力无效
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_001)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_BUTT;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_002
测试用例标题      : RAB ID无效
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_002)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 1;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_003
测试用例标题      : PDN ID类型无效
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_003)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 0;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_004
测试用例标题      : 网卡操作类型错误异常
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_004)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_BUTT;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_005
测试用例标题      : IP类型错误异常
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_005)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_BUTT;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_006
测试用例标题      : modem id 错误
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_006)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_1;

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_007
测试用例标题      : 网卡id错误
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_007)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RMNET_ID_BUTT;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_008
测试用例标题      : 发送内部消息失败，内存申请失败
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_008)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;
    RNIC_RMNET_CONFIG_REQ_STRU          stSndMsg;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 打桩 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_009
测试用例标题      : 发送内部消息失败，消息发送失败
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_009)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;
    RNIC_RMNET_CONFIG_REQ_STRU          stSndMsg;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 打桩 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_010
测试用例标题      : 发送内部消息失败，内存申请失败
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_010)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    RNIC_RMNET_CONFIG_REQ_STRU          stSndMsg;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 打桩 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_011
测试用例标题      : 发送内部消息失败，消息发送失败
预期结果          : 直接返回error
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_011)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;
    RNIC_RMNET_CONFIG_REQ_STRU          stSndMsg;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 打桩 */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));


    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_ERR, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}


/*******************************************************************
测试用例编号      : Test_RNIC_ConfigRmnetStatus_012
测试用例标题      : 发送内部消息成功
预期结果          : 直接返回ok
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类

*******************************************************************/
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_012)
{
    /* 参数初始化 */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* 函数调用 */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* 参数匹配 */
    EXPECT_EQ(VOS_OK, ulRet);

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();

}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
类名       : Test_RNIC_RcvSdioDlData
功能描述   : RNIC_RcvSdioDlData UT工程类
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新生成类
*****************************************************************************/
class Test_RNIC_RcvSdioDlData: public ::testing::Test
{
public:
    IMM_ZC_STRU                        *pstImmZc;
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* 分配A核共享内存 */
        pstImmZc = IMM_ZcStaticAlloc(20);

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
};

/*******************************************************************
测试用例编号      : Test_RNIC_RcvSdioDlData_001
测试用例标题      : 根据PDNid获取不到网卡ID
预期结果          : 返回RNIC_INVAL
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvSdioDlData, Test_RNIC_RcvSdioDlData_001)
{
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucPdnId;

    aulIpHeader[0] = 0x00;
    aulIpHeader[4] = 0xF0F0F0F0;
    ucPdnId        = 1;

    RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RM_NET_ID_0);

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    EXPECT_EQ(RNIC_ERROR, RNIC_RcvSdioDlData(ucPdnId, pstSkb));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvSdioDlData_002
测试用例标题      : RNIC的私有数据为空
预期结果          : 返回RNIC_INVAL
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvSdioDlData, Test_RNIC_RcvSdioDlData_002)
{
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucPdnId;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;
    ucPdnId        = 1;

    RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RM_NET_ID_0);

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    MOCKER(RNIC_SendDlData)
        .will(returnValue(RNIC_OK))
        .with(eq(RNIC_RM_NET_ID_0), any(), eq(ADS_PKT_TYPE_IPV4));


    EXPECT_EQ(RNIC_OK, RNIC_RcvSdioDlData(ucPdnId, pstSkb));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

/*******************************************************************
测试用例编号      : Test_RNIC_RcvSdioDlData_003
测试用例标题      : 网卡未打开
预期结果          : 下行丢包统计加1，释放内存，返回RNIC_OK
修改历史   :
1.日   期  : 2014-02-07
  作   者  : m00217266
  修改内容 : 新建CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvSdioDlData, Test_RNIC_RcvSdioDlData_003)
{
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucPdnId;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0xF0F0F0F0;
    ucPdnId        = 1;

    RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RM_NET_ID_0);

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    MOCKER(RNIC_SendDlData)
        .with(eq(RNIC_RM_NET_ID_0), any(), eq(ADS_PKT_TYPE_IPV6))
        .will(returnValue(RNIC_OK));

    EXPECT_EQ(RNIC_OK, RNIC_RcvSdioDlData(ucPdnId, pstSkb));

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();

}
#endif
/* Added by m00217266 for L-C互操作项目, 2014-2-7, end */

#endif