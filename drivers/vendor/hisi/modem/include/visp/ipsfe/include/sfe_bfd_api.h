/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_bfd_api.h
*
*  Project Code: V1.1.0
*   Module Name: BFD
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面BFD对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_BFD_API_H_
#define _SFE_BFD_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面BFD模块错误码 */
typedef enum enumSfeBfdErrCode
{ 
    SFE_BFD_OK = SFE_OK,                        /* 操作成功 */
    SFE_BFD_ERR_BEGIN = SFE_BFD_BEGIN_RET_CODE, /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_BFD_GET_SINGLEHOP_PROCMODE_PRECFG_FAIL, /* 1  获取BFD单跳会话处理模式预配置值失败 */
    SFE_BFD_GET_SESS_PRECFG_FAIL,               /* 2  获取最大BFD会话预配置值失败 */
    SFE_BFD_MALLOC_FAIL_GLOBAL_NODE_NUM,        /* 3  分配全局BFD计数节点核间共享内存时失败 */
    SFE_BFD_MALLOC_FAIL_VRF,                    /* 4  分配BFD VRF信息数组共享内存时失败 */
    SFE_BFD_ADD_NAMEDB_VRF,                     /* 5  将BFD VRF信息数组地址添加到名字库失败 */
    SFE_BFD_MALLOC_FAIL_SESS_CTRL,              /* 6  分配每个VRF下的BFD信息控制块失败 */
    SFE_BFD_MALLOC_SESSION_POOL,                /* 7  分配BFD会话信息POOL资源池失败 */
    SFE_BFD_PPI_CMD_INVALID,                    /* 8  BFD PPI命令字不合法 */

    SFE_BFD_GLOBAL_VAR_NULL_POINTER_OPER,       /* 9  操作BFD会话时, 核间共享变量为NULL */
    SFE_BFD_INPUT_NULL_POINTER_OPER,            /* 10 操作BFD会话时, 输入参数为NULL */
    SFE_BFD_VRF_WRONG_OPER,                     /* 11 操作BFD会话时, VRF索引参数不合法 */
    SFE_BFD_SESSION_ID_WRONG_OPER,              /* 12 操作BFD会话时, BFD会话ID不合法 */
    
    SFE_BFD_NUM_EXCEED_PRECFG,                  /* 13 添加BFD会话时, 当前BFD会话个数已经达到了预配置规格 */
    SFE_BFD_POOL_ALLOC_UNIT_FAIL_ADD,           /* 14 添加BFD会话时, 分配BFD会话POOL资源池节点失败 */
    SFE_BFD_GET_POOLNODEADDR_FAIL_ADD,          /* 15 添加BFD会话时, 根据POOL节点索引获取节点地址失败 */
    SFE_BFD_CREATE_SEND_TIMER_FAIL_ADD,         /* 16 添加BFD会话时, 创建定时发送定时器失败 */    
    SFE_BFD_CREATE_DETECT_TIMER_FAIL_ADD,       /* 17 添加BFD会话时, 创建超时探测定时器失败 */    

    SFE_BFD_DETECT_MODE_INVALID_CHANGE,         /* 18 更改BFD会话信息时, BFD探测模式不合法 */
    SFE_BFD_SESSION_NOT_EXIST_CHANGE,           /* 19 更改BFD会话信息时, BFD会话不存在 */
    SFE_BFD_GET_OLD_POOLNODEADDR_FAIL_CHANGE,   /* 20 更改BFD会话信息时, 根据已经存在的POOL节点索引获取节点地址失败 */
    SFE_BFD_POOL_ALLOC_UNIT_FAIL_CHANGE,        /* 21 更改BFD会话信息时, 分配BFD会话POOL资源池节点失败 */
    SFE_BFD_GET_NEW_POOLNODEADDR_FAIL_CHANGE,   /* 22 更改BFD会话信息时, 根据新的POOL节点索引获取节点地址失败 */

    SFE_BFD_SESSION_NOT_EXIST_DOWN,             /* 23 BFD会话DOWN时，BFD会话不存在 */
    SFE_BFD_GET_POOLNODEADDR_FAIL_DOWN,         /* 24 BFD会话DOWN时，根据已经存在的POOL节点索引获取节点地址失败 */

    SFE_BFD_SESSION_NOT_EXIST_DEL,              /* 25 BFD会话DEL时，BFD会话不存在 */   
    SFE_BFD_GET_POOLNODEADDR_FAIL_FREE,         /* 26 释放BFD会话信息时，根据已经存在的POOL节点索引获取节点地址失败 */
    SFE_BFD_GLOBAL_VAR_NULL_POINTER_DELALL,     /* 27 删除所有BFD会话时, 核间共享变量为NULL */

    SFE_BFD_GLOBAL_VAR_NULL_POINTER_GETBYID,    /* 28 指定ID获取BFD会话时, 核间共享变量为NULL */
    SFE_BFD_VRF_WRONG_GETBYID,                  /* 29 指定ID获取BFD会话时, VRF索引参数不合法 */
    SFE_BFD_SESSION_ID_WRONG_GETBYID,           /* 30 指定ID获取BFD会话时, BFD会话ID不合法 */
    SFE_BFD_NOT_FOUND_GETBYID,                  /* 31 指定ID获取BFD会话时, BFD会话不存在*/
    SFE_BFD_GET_POOLNODEADDR_FAIL_GETBYID,      /* 32 指定ID获取BFD会话时, 根据新的POOL节点索引获取节点地址失败 */
    
    SFE_BFD_PKT_VRF_INVALID_INPUT,              /* 33 接收BFD报文时, 报文中的VRF索引与会话中的不相同 */
    SFE_BFD_PKT_DSTIP_INVALID_INPUT,            /* 34 接收BFD报文时, 报文中的目的地址IP与会话中的不相同 */
    SFE_BFD_PKT_SRCIP_INVALID_INPUT,            /* 35 接收BFD报文时, 报文中的源IP与会话中的不相同 */
    SFE_BFD_PKT_TTL_INVALID_INPUT,              /* 36 接收BFD报文时, 单跳BFD会话报文中的TTL不等于255 */
    SFE_BFD_PKT_IFTYPE_INVALID_INPUT,           /* 37 接收BFD报文时, 报文中的接口类型与会话中的不相同 */
    SFE_BFD_PKT_FRAMID_INVALID_INPUT,           /* 38 接收BFD报文时, 报文中的框号与会话中的不相同 */
    SFE_BFD_PKT_SLOTID_INVALID_INPUT,           /* 39 接收BFD报文时, 报文中的槽号与会话中的不相同 */
    SFE_BFD_PKT_PORTNO_INVALID_INPUT,           /* 40 接收BFD报文时, 报文中的端口号与会话中的不相同 */
    SFE_BFD_ENCAP_FAIL_UIDRESV_ENLINKHEADER,    /* 41 封装链路层头失败, 链路层处理函数内部释放报文,调用者不能释放报文 */
    SFE_BFD_ENCAP_FAIL_UIDERR_ENLINKHEADER,     /* 42 封装链路层头失败, 链路层处理函数不释放报文,调用者必须释放报文 */
    SFE_BFD_IF_TYPE_INVALID_ENLINKHEADER,       /* 43 封装链路层头失败, 接口类型错误 */
    SFE_BFD_VCPU_NOT_INIT_OPER,                 /* 44 操作BFD会话时, VCPU没有初始化 */
    SFE_BFD_SESS_CTRL_NULL_POINTER_OPER,        /* 45 操作BFD会话时, VRF下的BFD会话控制块数组核间共享内存变量为NULL */
    SFE_BFD_VCPU_NOT_INIT_DELALL,               /* 46 删除所有BFD会话时, VCPU没有初始化 */
    SFE_BFD_SESS_CTRL_NULL_POINTER_GETBYID,     /* 47 指定ID获取BFD会话时, VRF下的BFD会话控制块数组核间共享内存变量为NULL */

    SFE_BFD_SET_DEBUG_VRF_ERR,                  /* 48 设置BFD会话调试开关时,VRF索引错误 */
    SFE_BFD_SET_DEBUG_SID_ERR,                  /* 49 设置BFD会话调试开关时,session id错误 */
    SFE_BFD_SET_DEBUG_BFDVRF_SHARE_NULL,        /* 50 设置BFD会话调试开关时,共享空间为NULL */
    SFE_BFD_SET_DEBUG_SWITCH_ERR,               /* 51 设置BFD会话调试开关时,开关错误 */
    SFE_BFD_SET_DEBUG_SESSION_NOEXIST,          /* 52 设置BFD会话调试开关时,会话不存在 */

    SFE_BFD_GET_DEBUG_VRF_ERR,                  /* 53 获取BFD会话调试开关时,VRF索引错误 */
    SFE_BFD_GET_DEBUG_SID_ERR,                  /* 54 获取BFD会话调试开关时,session id错误 */
    SFE_BFD_GET_DEBUG_BFDVRF_SHARE_NULL,        /* 55 获取BFD会话调试开关时,共享空间为NULL */
    SFE_BFD_GET_DEBUG_POINT_NULL,               /* 56 获取BFD会话调试开关时,参数为空指针 */
    SFE_BFD_GET_DEBUG_SESSION_NOEXIST,          /* 57 获取BFD会话调试开关时,会话不存在 */
    SFE_BFD_MALLOC_FAIL_ALL_SESSION_DEBUG,      /* 58 分配打开全部会话的调试开关核间共享内存时失败 */

    SFE_BFD_GET_STAT_BFD_NOT_INIT,              /* 59 检查BFD KEY信息时, BFD模块没有初始化 */
    SFE_BFD_GET_STAT_VRF_ERR,                   /* 60 检查BFD KEY信息时, vrf不合法 */
    SFE_BFD_GET_STAT_SESS_CTRL_NULL,            /* 61 检查BFD KEY信息时, VRF下的BFD会话控制块数组核间共享内存变量为NULL */
    SFE_BFD_GET_STAT_SESSID_ERR,                /* 62 检查BFD KEY信息时, 会话ID不正确 */
    SFE_BFD_GET_STAT_SESSID_NOTEXIST,           /* 63 检查BFD KEY信息时, 会话不存在 */

}SFE_BFD_ERR_CODE_E;

/*******************************************************************************
*    Func Name: SFE_BFD_DelAllBfdSession
* Date Created: 2009-9-15
*       Author: w60786/h00121208
*  Description: 删除所有BFD会话
*        Input: VOID
*       Output: 
*       Return: 成功:SFE_BFD_OK
*               失败:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-15    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_BFD_DelAllBfdSession(VOID);

/*******************************************************************************
*    Func Name: SFE_BFD_SetBfdSwitch
* Date Created: 2009-9-15
*       Author: z62531
*  Description: 转发面设置调试开关
*        Input: UINT32 u32VrfIndex : VRF索引
*               UINT32 u32SessionId : 会话ID
*               UINT32 u32IsDebug : 调试开关,1打开,0关闭
*       Output: 
*       Return: 成功:SFE_BFD_OK
*               错误:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-15    z62531              Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_BFD_SetBfdSwitch(UINT32 u32VrfIndex, UINT32 u32SessionId, UINT32 u32IsDebug);

/*******************************************************************************
*    Func Name: SFE_BFD_GetBfdSwitch
* Date Created: 2009-9-15
*       Author: z62531
*  Description: 转发面获取调试开关
*        Input: UINT32 u32VrfIndex : VRF索引
*               UINT32 u32SessionId : 会话ID
*       Output: UINT32 *pu32IsDebug : 调试开关,1打开,0关闭
*       Return: 成功:SFE_BFD_OK
*               错误:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-15    z62531              Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_BFD_GetBfdSwitch(UINT32 u32VrfIndex, UINT32 u32SessionId, UINT32 *pu32IsDebug);


#ifdef  __cplusplus
}
#endif

#endif


