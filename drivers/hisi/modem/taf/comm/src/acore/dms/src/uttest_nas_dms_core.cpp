#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "dms.h"
#include "dms_core.h"
#include "ImmInterface.h"

#define    THIS_FILE_ID        PS_FILE_ID_DMS_CORE_C
//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

VOS_VOID STUB_DMS_ChanEvtCB(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_CHAN_EVT_ENUM_UINT32 enEvt)
{
	return;
}

VOS_UINT32 STUB_DMS_ChanDataReadCB(DMS_OM_CHAN_ENUM_UINT32 enChan, VOS_UINT8 *pucData, VOS_UINT32 ulLength)
{
	return VOS_OK;
}

unsigned char *UT_skb_put(struct sk_buff *skb, unsigned int len)
{
	unsigned char *tmp = skb->tail;

	return tmp;
}

extern "C" int nlmsg_msg_size(int payload)
{
	return NLMSG_HDRLEN + payload;
}

extern "C" struct nlmsghdr * UT_nlmsg_put(struct sk_buff *skb, u32 portid, u32 seq, int type, int len, int flags)
{
	struct nlmsghdr *nlh;
	int size = nlmsg_msg_size(len);

	nlh = (struct nlmsghdr*)UT_skb_put(skb, NLMSG_ALIGN(size));
	nlh->nlmsg_type = type;
	nlh->nlmsg_len = size;
	nlh->nlmsg_flags = flags;
	nlh->nlmsg_pid = portid;
	nlh->nlmsg_seq = seq;

	return nlh;
}

void UT_kfree_skb(struct sk_buff *skb)
{
	if (NULL == skb)
	{
		return;
	}

	if (MEM_TYPE_SYS_DEFINED == skb->private_mem.enType)
	{
		free(skb->head);
	}
	else if(MEM_TYPE_USER_DEFINED == skb->private_mem.enType)
	{
		;
	}

	free(skb);
	skb = NULL;
}

extern "C" void *nlmsg_data(const struct nlmsghdr *nlh)
{
	return (unsigned char *) nlh + NLMSG_HDRLEN;
}

extern "C" int nlmsg_total_size(int payload)
{
	return NLMSG_ALIGN(nlmsg_msg_size(payload));
}

extern "C" struct sk_buff *nlmsg_new(size_t payload, gfp_t flags)
{
	//return IMM_ZcStaticAlloc(nlmsg_total_size(payload));
	IMM_ZC_STRU    *pstImmZc;
	unsigned char  *pucData;
	unsigned int    ulAllignlen;

	ulAllignlen = nlmsg_total_size(payload);

	pstImmZc = (IMM_ZC_STRU*)malloc(sizeof(IMM_ZC_STRU));
	if(VOS_NULL_PTR == pstImmZc)
	{
		return VOS_NULL_PTR;
	}
	pucData = (unsigned char*)malloc(((ulAllignlen +31)&(~31)) + 64  +288 );
	if(VOS_NULL_PTR == pucData)
	{
		free(pstImmZc);
		return VOS_NULL_PTR;
	}

	memset(pstImmZc, 0x0, sizeof(IMM_ZC_STRU));

	pstImmZc->head               = pucData;
	pstImmZc->len                = ulAllignlen;
	pstImmZc->data               = pucData + 64;
	pstImmZc->tail               = pstImmZc->data;
	ulAllignlen                  = (ulAllignlen +31)&(~31);
	pstImmZc->end                = pstImmZc->data + ulAllignlen;
	pstImmZc->private_mem.enType = MEM_TYPE_SYS_DEFINED;
	pstImmZc->private_mem.pMem   = (void*)pstImmZc;
	return (struct sk_buff *)pstImmZc;
}

IMM_ZC_STRU *IMM_ZcStaticAlloc_Debug(unsigned short usFileID, unsigned short usLineNum, unsigned int ulLen)
{
	IMM_ZC_STRU    *pstImmZc;
	unsigned char  *pucData;
	unsigned int    ulAllignlen;

	ulAllignlen = ulLen;

	pstImmZc = (IMM_ZC_STRU*)malloc(sizeof(IMM_ZC_STRU));
	if(VOS_NULL_PTR == pstImmZc)
	{
		return VOS_NULL_PTR;
	}
	pucData = (unsigned char*)malloc(((ulLen +31)&(~31)) + 64  +288 );
	if(VOS_NULL_PTR == pucData)
	{
		free(pstImmZc);
		return VOS_NULL_PTR;
	}

	memset(pstImmZc, 0x0, sizeof(IMM_ZC_STRU));

	pstImmZc->head               = pucData;
	pstImmZc->len                = ulLen;
	pstImmZc->data               = pucData + 64;
	pstImmZc->tail               = pstImmZc->data;
	ulLen                       = (ulAllignlen +31)&(~31);
	pstImmZc->end                = pstImmZc->data + ulLen;
	pstImmZc->private_mem.enType = MEM_TYPE_SYS_DEFINED;
	pstImmZc->private_mem.pMem   = (void*)pstImmZc;
	return pstImmZc;
}

extern "C" struct nlmsghdr *nlmsg_hdr(const struct sk_buff *skb)
{
	return (struct nlmsghdr *)skb->data;
}


/*****************************************************************************
 类名       : Test_DMS_RegOmChanDataReadCB
 功能描述   : Test_DMS_RegOmChanDataReadCB UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_RegOmChanDataReadCB: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_RegOmChanDataReadCB_001
 测试用例标题   : 通道号错误
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanDataReadCB, Test_DMS_RegOmChanDataReadCB_001)
{
    //参数定义
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //参数初始化
    pFunc = STUB_DMS_ChanDataReadCB;
    enChan = DMS_OM_CHAN_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = DMS_RegOmChanDataReadCB(enChan, pFunc);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_RegOmChanDataReadCB_002
 测试用例标题   : 回调函数指针为空
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanDataReadCB, Test_DMS_RegOmChanDataReadCB_002)
{
    //参数定义
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //参数初始化
    enChan = DMS_OM_CHAN_LTE_CTRL;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = DMS_RegOmChanDataReadCB(enChan, pFunc);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_RegOmChanDataReadCB_003
 测试用例标题   : 注册成功
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanDataReadCB, Test_DMS_RegOmChanDataReadCB_003)
{
    //参数定义
    DMS_NLK_OM_CHAN_PROPERTY_STRU      *pstOmChanProp = VOS_NULL_PTR;
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //参数初始化
    pFunc = STUB_DMS_ChanDataReadCB;
    enChan = DMS_OM_CHAN_LTE_CTRL;
    pstOmChanProp = DMS_GET_NLK_OM_CHAN_PROP(enChan);

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = DMS_RegOmChanDataReadCB(enChan, pFunc);

    //执行检查
    EXPECT_EQ(STUB_DMS_ChanDataReadCB, pstOmChanProp->pDataFunc);
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_RegOmChanEventCB
 功能描述   : Test_DMS_RegOmChanEventCB UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_RegOmChanEventCB: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_RegOmChanEventCB_001
 测试用例标题   : 通道号错误
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanEventCB, Test_DMS_RegOmChanEventCB_001)
{
    //参数定义
    DMS_OM_CHAN_EVENT_CB_FUNC           pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //参数初始化
    pFunc = STUB_DMS_ChanEvtCB;
    enChan = DMS_OM_CHAN_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = DMS_RegOmChanEventCB(enChan, pFunc);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_RegOmChanEventCB_002
 测试用例标题   : 回调函数指针为空
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanEventCB, Test_DMS_RegOmChanEventCB_002)
{
    //参数定义
    DMS_OM_CHAN_EVENT_CB_FUNC           pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //参数初始化
    enChan = DMS_OM_CHAN_LTE_CTRL;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = DMS_RegOmChanEventCB(enChan, pFunc);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_RegOmChanEventCB_003
 测试用例标题   : 注册成功
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanEventCB, Test_DMS_RegOmChanEventCB_003)
{
    //参数定义
    DMS_NLK_OM_CHAN_PROPERTY_STRU      *pstOmChanProp = VOS_NULL_PTR;
    DMS_OM_CHAN_EVENT_CB_FUNC           pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //参数初始化
    pFunc = STUB_DMS_ChanEvtCB;
    enChan = DMS_OM_CHAN_LTE_CTRL;
    pstOmChanProp = DMS_GET_NLK_OM_CHAN_PROP(enChan);

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = DMS_RegOmChanEventCB(enChan, pFunc);

    //执行检查
    EXPECT_EQ(pFunc, pstOmChanProp->pEvtFunc);
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_InitEntity
 功能描述   : Test_DMS_NLK_InitEntity UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_InitEntity: public ::testing::Test
{
public:

    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_InitEntity_001
 测试用例标题   : netlink 初始化
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_InitEntity, Test_DMS_NLK_InitEntity_001)
{
    //参数定义

    //参数初始化

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    DMS_NLK_InitEntity();

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_CfgOpen
 功能描述   : Test_DMS_NLK_CfgOpen UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_CfgOpen: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_CfgOpen_001
 测试用例标题   : 物理承载号错误
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_CfgOpen, Test_DMS_NLK_CfgOpen_001)
{
    //参数定义
    struct nlmsghdr                     stNlkHdr;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulRslt;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = DMS_NLK_CfgOpen(&stNlkHdr, enPhyBear);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_CfgOpen_002
 测试用例标题   : 调用与物理承载上注册的回调函数
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_CfgOpen, Test_DMS_NLK_CfgOpen_002)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    struct nlmsghdr                     stNlkHdr;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    DMS_CHAN_EVT_ENUM_UINT32            enEvt;
    VOS_UINT32                          ulRslt;

    //参数初始化
    stNlkHdr.nlmsg_pid = 1;
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enChan    = DMS_OM_CHAN_LTE_CTRL;
    enEvt     = DMS_CHAN_EVT_OPEN;

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pEvtFunc = STUB_DMS_ChanEvtCB;

    //MOCKER操作
    MOCKER(STUB_DMS_ChanEvtCB)
	    .expects(exactly(1))
        .with(eq(enChan), eq(enEvt));

    //调用被测函数
    ulRslt = DMS_NLK_CfgOpen(&stNlkHdr, enPhyBear);

    //执行检查
    EXPECT_EQ(stNlkHdr.nlmsg_pid, pstNlkEntity->astPhyBearProp[enPhyBear].lPid);
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_CfgClose
 功能描述   : Test_DMS_NLK_CfgClose UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_CfgClose: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_CfgClose_001
 测试用例标题   : 物理承载号错误
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_CfgClose, Test_DMS_NLK_CfgClose_001)
{
    //参数定义
    struct nlmsghdr                     stNlkHdr;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulRslt;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_BUTT;

    //相关全局变量初始化

    //MOCKER操作

    //调用被测函数
    ulRslt = DMS_NLK_CfgClose(&stNlkHdr, enPhyBear);

    //执行检查
    EXPECT_EQ(VOS_ERR, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_CfgOpen_002
 测试用例标题   : 调用与物理承载上注册的回调函数
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_CfgClose, Test_DMS_NLK_CfgClose_002)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    struct nlmsghdr                     stNlkHdr;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    DMS_CHAN_EVT_ENUM_UINT32            enEvt;
    VOS_UINT32                          ulRslt;

    //参数初始化
    stNlkHdr.nlmsg_pid = 1;
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enChan    = DMS_OM_CHAN_LTE_CTRL;
    enEvt     = DMS_CHAN_EVT_CLOSE;

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pEvtFunc = STUB_DMS_ChanEvtCB;

    //MOCKER操作
    MOCKER(STUB_DMS_ChanEvtCB)
	    .expects(exactly(1))
        .with(eq(enChan), eq(enEvt));

    //调用被测函数
    ulRslt = DMS_NLK_CfgClose(&stNlkHdr, enPhyBear);

    //执行检查
    EXPECT_EQ(DMS_NLK_INVALID_PID, pstNlkEntity->astPhyBearProp[enPhyBear].lPid);
    EXPECT_EQ(VOS_OK, ulRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_ProcLteCfgMsg
 功能描述   : Test_DMS_NLK_ProcLteCfgMsg UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_ProcLteCfgMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcLteCfgMsg_001
 测试用例标题   : 端口打开
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCfgMsg, Test_DMS_NLK_ProcLteCfgMsg_001)
{
    //参数定义
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_OPEN;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_CfgOpen)
	    .expects(exactly(1))
        .with(any(), eq(enPhyBear))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    DMS_NLK_ProcLteCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_CfgOpen_002
 测试用例标题   : 端口关闭
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCfgMsg, Test_DMS_NLK_ProcLteCfgMsg_002)
{
    //参数定义
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_CLOSE;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_CfgClose)
	    .expects(exactly(1))
        .with(any(), eq(enPhyBear))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    DMS_NLK_ProcLteCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_CfgOpen_002
 测试用例标题   : 无效命令
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCfgMsg, Test_DMS_NLK_ProcLteCfgMsg_003)
{
    //参数定义
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;

    //参数初始化
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_BUTT;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_CfgOpen)
        .expects(never());

    MOCKER(DMS_NLK_CfgClose)
        .expects(never());

    //调用被测函数
    DMS_NLK_ProcLteCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_ProcGuCfgMsg
 功能描述   : Test_DMS_NLK_ProcGuCfgMsg UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_ProcGuCfgMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcGuCfgMsg_001
 测试用例标题   : 端口打开
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuCfgMsg, Test_DMS_NLK_ProcGuCfgMsg_001)
{
    //参数定义
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_GU;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_OPEN;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_CfgOpen)
	    .expects(exactly(1))
        .with(any(), eq(enPhyBear))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    DMS_NLK_ProcGuCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcGuCfgMsg_002
 测试用例标题   : 端口关闭
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuCfgMsg, Test_DMS_NLK_ProcGuCfgMsg_002)
{
    //参数定义
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_GU;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_CLOSE;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_CfgClose)
	    .expects(exactly(1))
        .with(any(), eq(enPhyBear))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    DMS_NLK_ProcGuCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcGuCfgMsg_003
 测试用例标题   : 无效命令
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuCfgMsg, Test_DMS_NLK_ProcGuCfgMsg_003)
{
    //参数定义
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;

    //参数初始化
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_BUTT;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_CfgOpen)
    .expects(never());

    MOCKER(DMS_NLK_CfgClose)
    .expects(never());

    //调用被测函数
    DMS_NLK_ProcGuCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_ProcLteCtrlMsg
 功能描述   : Test_DMS_NLK_ProcLteCtrlMsg UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_ProcLteCtrlMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcLteCtrlMsg_001
 测试用例标题   : 透传数据
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCtrlMsg, Test_DMS_NLK_ProcLteCtrlMsg_001)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulDataLen;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enChan    = DMS_OM_CHAN_LTE_CTRL;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pDataFunc = STUB_DMS_ChanDataReadCB;

    //MOCKER操作
    MOCKER(STUB_DMS_ChanDataReadCB)
	    .expects(exactly(1))
        .with(eq(enChan), any(), eq(ulDataLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    DMS_NLK_ProcLteCtrlMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcLteCtrlMsg_002
 测试用例标题   : 丢弃数据
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCtrlMsg, Test_DMS_NLK_ProcLteCtrlMsg_002)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulDataLen;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(STUB_DMS_ChanDataReadCB)
    .expects(never());

    //调用被测函数
    DMS_NLK_ProcLteCtrlMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_ProcLteDataMsg
 功能描述   : Test_DMS_NLK_ProcLteDataMsg UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_ProcLteDataMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcLteDataMsg_001
 测试用例标题   : 透传数据
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteDataMsg, Test_DMS_NLK_ProcLteDataMsg_001)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulDataLen;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enChan    = DMS_OM_CHAN_LTE_DATA;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pDataFunc = STUB_DMS_ChanDataReadCB;

    //MOCKER操作
    MOCKER(STUB_DMS_ChanDataReadCB)
	    .expects(exactly(1))
        .with(eq(enChan), any(), eq(ulDataLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    DMS_NLK_ProcLteDataMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcLteDataMsg_002
 测试用例标题   : 丢弃数据
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteDataMsg, Test_DMS_NLK_ProcLteDataMsg_002)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulDataLen;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(STUB_DMS_ChanDataReadCB)
    .expects(never());

    //调用被测函数
    DMS_NLK_ProcLteDataMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_ProcGuDataMsg
 功能描述   : Test_DMS_NLK_ProcGuDataMsg UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_ProcGuDataMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcGuDataMsg_001
 测试用例标题   : 透传数据
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuDataMsg, Test_DMS_NLK_ProcGuDataMsg_001)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulDataLen;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_GU;
    enChan    = DMS_OM_CHAN_GU_DATA;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pDataFunc = STUB_DMS_ChanDataReadCB;

    //MOCKER操作
    MOCKER(STUB_DMS_ChanDataReadCB)
	    .expects(exactly(1))
        .with(eq(enChan), any(), eq(ulDataLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //调用被测函数
    DMS_NLK_ProcGuDataMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_ProcGuDataMsg_002
 测试用例标题   : 丢弃数据
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuDataMsg, Test_DMS_NLK_ProcGuDataMsg_002)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulDataLen;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_GU;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(STUB_DMS_ChanDataReadCB)
        .expects(never());

    //调用被测函数
    DMS_NLK_ProcGuDataMsg(pstNlkHdr);
    free(pstNlkHdr);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_Send
 功能描述   : Test_DMS_NLK_Send UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_Send: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();

		MOCKER(nlmsg_put)
			.defaults()
			.will(invoke(UT_nlmsg_put));
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Send_001
 测试用例标题   : socket 错误
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_001)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = VOS_NULL_PTR;

    //MOCKER操作

    //调用被测函数
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //执行检查
    EXPECT_EQ(-EIO, lRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Send_002
 测试用例标题   : pid 错误
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_002)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = DMS_NLK_INVALID_PID;

    //MOCKER操作

    //调用被测函数
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //执行检查
    EXPECT_EQ(-EINVAL, lRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Send_003
 测试用例标题   : 申请 netlink 消息失败
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_003)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = 1;

    //MOCKER操作
    MOCKER(nlmsg_new)
        .stubs()
        .will(returnValue((sk_buff *)VOS_NULL_PTR));

    //调用被测函数
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //执行检查
    EXPECT_EQ(-ENOBUFS, lRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Send_004
 测试用例标题   : 填充 netlink 消息失败
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_004)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

	MOCKER(kfree_skb)
		.defaults()
		.will(invoke(UT_kfree_skb));

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = 1;

    //MOCKER操作
    MOCKER(nlmsg_put)
        .stubs()
        .will(returnValue((struct nlmsghdr *)VOS_NULL_PTR));

    //调用被测函数
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //执行检查
    EXPECT_EQ(-EMSGSIZE, lRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Send_005
 测试用例标题   : 发送 netlink 消息失败
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_005)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = 1;

    //MOCKER操作
    MOCKER(netlink_unicast)
        .stubs()
        .will(returnValue((VOS_INT)-1));

	MOCKER(kfree_skb)
		.defaults()
		.will(invoke(UT_kfree_skb));

	MOCKER(nlmsg_put)
		.defaults()
		.will(invoke(UT_nlmsg_put));

    //调用被测函数
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //执行检查
    EXPECT_EQ(-1, lRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Send_006
 测试用例标题   : 发送 netlink 消息成功
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_006)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulSock;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //参数初始化
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //相关全局变量初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = 1;

    //MOCKER操作
	MOCKER(netlink_unicast)
		.stubs()
		.will(returnValue((VOS_INT)0));

    //调用被测函数
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //执行检查
    EXPECT_EQ(0, lRslt);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_Input
 功能描述   : Test_DMS_NLK_Input UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_Input: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();

		MOCKER(nlmsg_put)
			.defaults()
			.will(invoke(UT_nlmsg_put));

		MOCKER(kfree_skb)
			.defaults()
			.will(invoke(UT_kfree_skb));
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Input_001
 测试用例标题   : netlink 消息错误
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_001)
{
    //参数定义
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;

    //参数初始化
    pstSkb = nlmsg_new(sizeof(DMS_NLK_CFG_STRU), GFP_ATOMIC);
    pstNlkHdr = nlmsg_hdr(pstSkb);
    pstNlkHdr->nlmsg_len = 0;

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_ProcLteCfgMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcLteCtrlMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcLteDataMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcGuCfgMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcGuDataMsg)
        .expects(never());

	MOCKER(kfree_skb)
		.defaults()
		.will(invoke(UT_kfree_skb));

    //调用被测函数
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Input_002
 测试用例标题   : DMS_NLK_MSG_TYPE_LTE_CFG消息
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_002)
{
    //参数定义
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //参数初始化
    ulMsgType = DMS_NLK_MSG_TYPE_LTE_CFG;
    ulPayloadSize = sizeof(DMS_NLK_CFG_STRU);
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_ProcLteCfgMsg)
	    .expects(exactly(1));

    //调用被测函数
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Input_003
 测试用例标题   : DMS_NLK_MSG_TYPE_LTE_CTRL消息
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_003)
{
    //参数定义
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //参数初始化
    ulMsgType = DMS_NLK_MSG_TYPE_LTE_CTRL;
    ulDataLen = 10;
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_ProcLteCtrlMsg)
	    .expects(exactly(1));

    //调用被测函数
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Input_004
 测试用例标题   : DMS_NLK_MSG_TYPE_LTE_DATA消息
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_004)
{
    //参数定义
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //参数初始化
    ulMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_ProcLteDataMsg)
	    .expects(exactly(1));

    //调用被测函数
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Input_005
 测试用例标题   : DMS_NLK_MSG_TYPE_GU_CFG消息
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_005)
{
    //参数定义
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //参数初始化
    ulMsgType = DMS_NLK_MSG_TYPE_GU_CFG;
    ulPayloadSize = sizeof(DMS_NLK_CFG_STRU);
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_ProcGuCfgMsg)
	    .expects(exactly(1));

    //调用被测函数
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Input_006
 测试用例标题   : DMS_NLK_MSG_TYPE_GU_DATA消息
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_006)
{
    //参数定义
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //参数初始化
    ulMsgType = DMS_NLK_MSG_TYPE_GU_DATA;
    ulDataLen = 10;
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_ProcGuDataMsg)
	    .expects(exactly(1));

    //调用被测函数
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}
#if 0
/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Input_007
 测试用例标题   : 无效消息
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_007)
{
    //参数定义
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //参数初始化
    ulMsgType = DMS_NLK_MSG_TYPE_BUTT;
    ulDataLen = 10;
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(DMS_NLK_ProcLteCfgMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcLteCtrlMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcLteDataMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcGuCfgMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcGuDataMsg)
        .expects(never());

    //调用被测函数
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //执行检查

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}
#endif
/*****************************************************************************
 类名       : Test_DMS_NLK_Init
 功能描述   : Test_DMS_NLK_Init UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_Init: public ::testing::Test
{
public:

    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Input_001
 测试用例标题   : 创建 netlink 失败
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Init, Test_DMS_NLK_Init_001)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;

    //参数初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(netlink_kernel_create)
        .stubs()
        .will(returnValue((struct sock *)NULL));

    //调用被测函数
    DMS_NLK_Init();

    //执行检查
    EXPECT_EQ(VOS_NULL_PTR, pstNlkEntity->pstSock);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Init_002
 测试用例标题   : 创建 netlink 成功
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Init, Test_DMS_NLK_Init_002)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;

    //参数初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(netlink_kernel_create)
        .stubs()
        .will(returnValue((struct sock *)&ulSock));

    //调用被测函数
    DMS_NLK_Init();

    //执行检查
    EXPECT_EQ((struct sock *)&ulSock, pstNlkEntity->pstSock);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}

/*****************************************************************************
 类名       : Test_DMS_NLK_Exit
 功能描述   : Test_DMS_NLK_Exit UT工程类
 修改历史   :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新生成类
*****************************************************************************/
class Test_DMS_NLK_Exit: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 测试用例编号   : Test_DMS_NLK_Exit_001
 测试用例标题   : 释放 netlink
 预期结果       :
 修改历史       :
 1.日   期  : 2014-07-17
   作   者  : A00165503
   修改内容 : 新建CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Exit, Test_DMS_NLK_Exit_001)
{
    //参数定义
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;

    //参数初始化
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;

    //相关全局变量初始化

    //MOCKER操作
	MOCKER(netlink_kernel_release)
	    .expects(exactly(1));

    //调用被测函数
    DMS_NLK_Exit();

    //执行检查
    EXPECT_EQ(VOS_NULL_PTR, pstNlkEntity->pstSock);

    //检查调用时, 需要在用例结束位置加上这句
	GlobalMockObject::verify();
}
