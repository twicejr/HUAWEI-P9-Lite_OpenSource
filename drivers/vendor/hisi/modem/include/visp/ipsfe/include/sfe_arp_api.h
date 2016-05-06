/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_arp_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面ARP对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_ARP_API_H_
#define _SFE_ARP_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面ARP模块错误码 */
typedef enum enumSfeArpErrCode
{
    SFE_ARP_OK = SFE_OK,                /* 操作成功 */
    SFE_ARP_ERR_BEGIN = SFE_ARP_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    SFE_ARP_GET_ARP_PRECONFIG_FAIL,     /* 1  获取ARP预配置失败 */
    SFE_ARP_GET_FAKEARP_PRECONFIG_FAIL, /* 2  获取ARP哑元预配置失败 */
    SFE_ARP_GET_CACHE_PACKET_PRECONFIG_FAIL,/* 3  获取ARP哑元允许缓存的总的最大报文个数预配置失败 */
    SFE_ARP_MALLOC_FAIL_VRF,            /* 4  分配ARP的VRF数组失败 */
    SFE_ARP_MALLOC_FAIL_GLOBAL_NODE_NUM,/* 5  分配ARP的全局计数失败 */
    SFE_ARP_MALLOC_FAIL_ARP_HASH_TABLE, /* 6  分配ARP哈希表失败 */
    SFE_ARP_ADD_NAMEDB_VRF,             /* 7  将ARP的VRF数组加入名字空间失败 */
    SFE_ARP_MALLOC_ARP_RESOLVED_POOL,   /* 8  分配已解析ARP缓冲池失败 */
    SFE_ARP_MALLOC_ARP_RESOLVING_POOL,  /* 9  分配待解析ARP缓冲池失败 */
    SFE_ARP_INPUT_NULL_POINTER_ADD,     /* 10 ARP添加时传入空指针 */
    SFE_ARP_INPUT_NULL_POINTER_DEL,     /* 11 ARP删除时传入空指针 */
    SFE_ARP_VRF_NULL_POINTER_ADD,       /* 12 当添加ARP节点时VRF数组是空指针 */
    SFE_ARP_VRF_NULL_POINTER_DEL,       /* 13 当删除ARP节点时VRF数组是空指针 */
    SFE_ARP_HASHTABLE_NULL_POINTER_ADD, /* 14 当添加ARP节点时ARP hash table 是空指针 */
    SFE_ARP_HASHTABLE_NULL_POINTER_DEL, /* 15 当删除ARP节点时ARP hash table 是空指针 */
    SFE_ARP_VRF_WRONG_ADD,              /* 16 当添加ARP节点时VRF索引错误 */
    SFE_ARP_VRF_WRONG_DEL,              /* 17 当删除ARP节点时VRF索引错误 */
    SFE_ARP_CREATE_RWLOCK_FAIL,         /* 18 创建读写锁失败 */
    SFE_ARP_NOT_ALLOW_ADD_FAKE_NODE,    /* 19 不允许产品添加哑元节点 */
    SFE_ARP_NOT_ALLOW_DEL_FAKE_NODE,    /* 20 不允许产品删除哑元节点 */
    SFE_ARP_RWLOCK_FAIL_ADD_FAKE,       /* 21 当增加哑元时获取ARP Hash哑元读写锁失败 */
    SFE_ARP_RWLOCK_FAIL_DEL_FAKE,       /* 22 当删除哑元时获取ARP Hash哑元读写锁失败  */
    SFE_ARP_GET_ARPNODEADDR_FAIL_ADDFAKE,/* 23 添加哑元时根据ARP节点索引获取对应的ARP节点地址失败 */
    SFE_ARP_GET_ARPNODEADDR_FAIL_UPDATENORMAL,/* 24 更新正常ARP时根据ARP节点索引获取对应的ARP节点地址失败 */
    SFE_ARP_GET_ARPNODEADDR_FAIL_ADDNORMAL,/* 25 添加正常ARP时根据ARP节点索引获取对应的ARP节点地址失败 */
    SFE_ARP_GET_ARPNODEADDR_FAIL_ARPMISS,/* 26 ARP MISS处理时根据ARP节点索引获取对应的ARP节点地址失败 */
    SFE_ARP_SOURCE_CONFLICT_ADD,        /* 27 添加ARP表项时,存在来源不同的相同ARP表项,产生冲突 */
    SFE_ARP_SOURCE_NOTSAME_DEL,         /* 28 删除ARP表项时来源不相同删除失败 */
    SFE_ARP_NOT_EXSIT_SAME_ARP_DEL,     /* 29 删除ARP表项时不存在对应的ARP表项删除失败 */
    SFE_ARP_NOT_EXSIT_SAME_FAKE_DEL,    /* 30 删除哑元ARP表项时不存在对应的ARP表项删除失败 */
    SFE_ARP_VRF_WRONG_SEARCH,           /* 31 查找ARP时,VRF值不合法 */
    SFE_ARP_RWLOCK_FAIL_SEARCH,         /* 32 查找ARP时获取哑元读写锁失败 */
    SFE_ARP_NO_NORMAL_ARP_SEARCH,       /* 33 查找ARP时,无正常ARP节点，并进行了ARP MISS处理 */
    SFE_ARP_CACHE_PACKET_SEARCH,        /* 34 查找ARP时,无有效ARP节点,有ARP哑元节点,将报文缓存在哑元节点下 */
    SFE_ARP_MISS_CACHE_PACKET_SEARCH,   /* 35 查找ARP时,无有效ARP节点,无ARP哑元节点,生成新哑元节点将报文缓存在哑元节点下 */
    SFE_ARP_MISS_NOTIFY_FAIL_ARPMISS,   /* 36 ARP MISS处理时上报控制面失败 */
    SFE_ARP_MISS_RENOTIFY_FAIL_SEARCH,  /* 37 ARP查找到哑元处理时重复上报ARP MISS给控制面失败 */
    SFE_ARP_MAX_FAKE_NODE_NUM_ADD,      /* 38 超过哑元最大个数限制 */
    SFE_ARP_MAX_ARP_NODE_NUM_ADD,       /* 39 超过已解析ARP最大个数限制 */
    SFE_ARP_POOL_ALLOC_UNIT_FAIL_ADD,      /* 40 添加ARP节点时分配ARP资源池空闲节点失败 */
    SFE_ARP_POOL_ALLOC_UNIT_FAIL_UPDATA,   /* 41 更新ARP节点时分配ARP资源池空闲节点失败 */
    SFE_ARP_FAKE_POOL_ALLOC_UNIT_FAIL_ADD, /* 42 添加ARP哑元节点时分配ARP哑元资源池空闲节点失败 */
    SFE_ARP_FAKE_POOL_ALLOC_UNIT_FAIL_MISS,/* 43 ARP MISS处理时分配ARP哑元资源池空闲节点失败 */
    SFE_ARP_MISS_RENOTIFY_SUCCESS_SEARCH,  /* 44 ARP查找到哑元处理时重复上报ARP MISS给控制面成功 */
    SFE_ARP_CREATE_LOOP_TIMER_FAIL,        /* 45 创建ARP哑元循环定时器失败 */
    SFE_ARP_SNED_PKT_FAIL_ETHHEADER_NULL,      /* 46 发送缓存报文时,取报文MBUF以太头为NULL */
    SFE_ARP_SNED_PKT_FAIL_ETHPHYSENDFUNC_NULL, /* 47 发送缓存报文时,用户没有注册以太底层发送函数,发送函数为NULL */
    SFE_ARP_SNED_PKT_FAIL_ETHPHYSEND_FAIL,     /* 48 发送缓存报文时, 底层发送函数返回发送失败 */
    SFE_ARP_VCPU_ALREADY_INIT_REGPHYSENDFUNC,  /* 49 注册以太类型报文底层发送函数失败因为VCPU已经初始化 */
    SFE_ARP_NULL_POINTER_REGPHYSENDFUNC,       /* 50 注册以太类型报文底层发送函数失败因为传入NULL指针 */
    SFE_ARP_MAX_FAKE_NODE_NUM_MISS,            /* 51 超过哑元最大个数限制 */
    SFE_ARP_PPI_CMD_INVALID,                   /* 52 ARP PPI命令字不合法 */
    SFE_ARP_GET_VRF_NULL_POINTER,              /* 53 当获取ARP信息时VRF数组是空指针 */
    SFE_ARP_GET_VRF_WRONG,                     /* 54 当获取ARP信息时VRF参数不合法 */
    SFE_ARP_GET_HASHTABLE_NULL_POINTER,        /* 55 当获取ARP信息时ARP hash table 是空指针 */
    SFE_ARP_GET_RWLOCK_FAIL,                   /* 56 当获取ARP信息时获取哑元锁失败 */
    SFE_ARP_GET_NOT_FOUND_ARP,                 /* 57 当获取ARP信息时不存在对应的ARP表项 */
    SFE_ARP_HAVE_ARP_ETHHDR_NULL,              /* 58 报文发送时找到了ARP但是向MBUF中填写信息时获取以太头指针为NULL */
    SFE_ARP_NO_ARP_AND_ARPMISS_SEARCH,         /* 59 查找ARP时,无正常ARP节点，并且配置为不进行ARP MISS处理 */
    SFE_ARP_MALLOC_FAIL_ARPFAKE_TIMER,         /* 60 分配存放ARP哑元定时器ID的共享内存失败 */
    SFE_ARP_ADD_NAMEDB_ARPFAKE_TIMER,          /* 61 将存放ARP哑元定时器ID的共享内存加入名字空间失败 */
    SFE_ARP_VCPU_NOT_INIT_ADD,                 /* 62 添加ARP时该VCPU没有初始化 */
    SFE_ARP_VCPU_NOT_INIT_DEL,                 /* 63 删除ARP时该VCPU没有初始化 */
    SFE_ARP_LOOP_DEL_FAKE,                     /* 64 删除ARP时while循环超出最大次数限制*/
    SFE_ARP_LOOP_ADD_FAKE,                     /* 65 添加哑元时while循环超出最大次数限制*/
    SFE_ARP_LOOP_ADD_NORMAL_ARP,               /* 66 添加ARP时while循环超出最大次数限制*/
    SFE_ARP_LOOP_DELETE_NORMAL_ARP,            /* 67 删除ARP时while循环超出最大次数限制*/
    SFE_ARP_LOOP_GET_ARPINFO,                  /* 68 获取ARP信息时while循环超出最大次数限制*/
    SFE_ARP_LOOP_GET_FAKEARPINFO,              /* 69 获取FAKE ARP信息时while循环超出最大次数限制*/
    SFE_ARP_LOOP_SEARCH_ARP,                   /* 70 搜索ARP时while循环超出最大次数限制*/
    SFE_ARP_LOOP_PROCESS_FAKE_ARP,             /* 71 处理哑元ARP时while循环超出最大次数限制*/
    SFE_ARP_LOOP_DELETE_MBUF,                  /* 72 删除哑元的MBUF时while循环超出最大次数限制*/
}SFE_ARP_ERR_CODE_E;

/*******************************************************************************
*    Func Name: SFE_ShowAllArpInfo
* Date Created: 2009-8-6
*       Author: w60786
*      Purpose: 显示数据面所有ARP表项信息
*  Description: 显示数据面所有ARP表项信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-6     w60786/luowentong         Creat the first version.
*
*******************************************************************************/
VOID SFE_ShowAllArpInfo(VOID);


#ifdef  __cplusplus
}
#endif

#endif


