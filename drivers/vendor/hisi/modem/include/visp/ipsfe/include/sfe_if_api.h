/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_if_api.h
*
*  Project Code: V1.1.0
*   Module Name: 
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面IF接口对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_IF_API_H_
#define _SFE_IF_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面IF模块错误码 */
typedef enum enumSFE_IF_ERRCODE
{
    SFE_IF_OK  = SFE_OK,                /* 操作成功 */
    SFE_IF_ERR_BEGIN = SFE_IF_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    SFE_IF_UPDATE_CMD_INVALID,          /* 1  更新接口信息时,命令字不识别 */
    SFE_IF_ERRPORTNO,                   /* 2  最大接口数目 */ 
    SFE_IF_ISNOTINIT,                   /* 3  IF模块未初始化 */
    SFE_IF_ISEXIST,                     /* 4  接口已经存在 */
    SFE_IF_ISNOTEXIST,                  /* 5  接口不存在 */
    SFE_IF_ISNOTSUSTAINTYPE,            /* 6  不支持该类型接口 */
    
    SFE_IF_ERRFRAMEORSLOTID,            /* 7  框号或槽号错误 */

    SFE_IF_NULL_POINTER_INPUTPARA,      /* 8  输入参数指针为空 */
    SFE_IF_NULL_POINTER_INTFINFO,       /* 9  输入接口信息指针为空 */
    SFE_IF_NULL_POINTER_TYPEINFO,       /* 10 接口类型信息指针为空 */
    SFE_IF_NULL_POINTER_FULLINFO,       /* 11 接口全部信息指针为空 */

    SFE_IF_MALLOC_FAIL_FRAMESLOT,       /* 12 分配框槽空间失败 */
    SFE_IF_MALLOC_FAIL_TYPEINFO,        /* 13 分配接口类型内存失败 */
    SFE_IF_MALLOC_FAIL_FULLINFO1,       /* 14 申请接口全部信息内存失败 */
    SFE_IF_MALLOC_FAIL_FULLINFO2,       /* 15 第一次申请接口全部信息内存失败 */    
    SFE_IF_MALLOC_FAIL_IFPOOL,          /* 16 申请接口基本信息失败 */
    SFE_IF_MALLOC_FAIL_IFUNIT,          /* 17 从资源池中申请接口单元信息失败 */
    
    SFE_IF_ERRPORTTYPE,                 /* 18 端口类型错误 */
    SFE_IF_GETBASEINFOFAIL,             /* 19 获取接口基本信息失败 */
    SFE_IF_GETBASEINFOFAILFORUPDATE,    /* 20 获取更新接口基本信息失败*/
    SFE_IF_GETLINKINFOFAIL,             /* 21 获取链路层信息失败 */

    SFE_IF_ERRORIGIN,                   /* 22 接口来源错误 */
    SFE_IF_ERRCREATELINK,               /* 23 创建链路层自有接口信息失败 */    
    SFE_IF_DELETELINKFAIL,              /* 24 删除链路层信息失败 */
    SFE_IF_UPDATELINKFAIL,              /* 25 更新链路层信息失败 */
    SFE_IF_OVER_MAX_VRF,                /* 26 VRF索引非法 */
    SFE_IF_ERRREDUCETTL,                /* 27 接口TTL是否减1值错误 */ 

    SFE_IF_ERR_PORTTYPE_CHECK_IFID,     /* 28 检查接口ID有效性时,接口类型非法 */
    SFE_IF_ERR_FRAMEID_CHECK_IFID,      /* 29 检查接口ID有效性时,接口框号非法 */
    SFE_IF_ERR_SLOTID_CHECK_IFID,       /* 30 检查接口ID有效性时,接口槽号非法 */
    SFE_IF_ERR_PORTNO_CHECK_IFID,       /* 31 检查接口ID有效性时,接口端口号非法 */

    SFE_IF_NULL_IFTYPE_GET_IFINFO_POOLADDR,         /* 32 获取接口信息时,接口类型控制块为空 */
    SFE_IF_NULL_IFFULLINFO_GET_IFINFO_POOLADDR,     /* 33 获取接口信息时,接口全部信息控制块为空 */
    SFE_IF_IS_NOT_EXIST_GET_IFINFO_POOLADDR,        /* 34 获取接口信息时,接口不存在 */
    SFE_IF_BASEINFO_NULL_GET_IFINFO_POOLADDR,       /* 35 获取接口信息时,接口基本信息控制块为空 */
    SFE_IF_LINKINFO_NULL_GET_IFINFO_POOLADDR,       /* 36 获取接口信息时,接口自有信息控制块为空 */

    SFE_IF_DISABLE_ARPMISS_SWITCH_INVALID,          /* 37 配置以太接口信息时, 指定的ARP MISS是否使能标志非法 */

    SFE_IF_ERR_PORTTYPE_GETIFINFO,                  /* 38 报文收发流程中,获取接口信息的地址时,接口类型非法 */
    SFE_IF_ERR_FRAMEID_GETIFINFO,                   /* 39 报文收发流程中,获取接口信息的地址时,接口框号非法 */
    SFE_IF_ERR_SLOTID_GETIFINFO,                    /* 40 报文收发流程中,获取接口信息的地址时,接口槽号非法 */
    SFE_IF_ERR_PORTNO_GETIFINFO,                    /* 41 报文收发流程中,获取接口信息的地址时,接口端口号非法 */

    SFE_IF_SWITCH_INVALID_SETTTLSWITCH,             /* 42 设置接口TTL减一开关时,开关值非法 */
    SFE_IF_VCPU_NOT_INIT_CREATE,                    /* 43 VCPU没有初始化时不能进行创建接口操作 */
    SFE_IF_VCPU_NOT_INIT_DELETE,                    /* 44 VCPU没有初始化时不能进行删除接口操作 */
    SFE_IF_VCPU_NOT_INIT_UPDATE,                    /* 45 VCPU没有初始化时不能进行更新接口操作 */

    SFE_IF_NULL_POINTER_IFID,                       /* 46 根据IFID获取IF索引时，接口ID为NULL*/
    SFE_IF_ERR_GETIFINDEX,                          /* 47 根据IFID获取IF索引时，接口不存在*/

    SFE_IF_ERRPORTNO_BYIFID,                        /* 48 接口编号超过配置最大值 */
    SFE_IF_ISNOTINIT_BYID,                          /* 49 IF模块未初始化 */
    SFE_IF_ISNOTEXIST_BYID,                         /* 50 接口不存在 */
    SFE_IF_NULL_POINTER_TYPEINFO_BYID,              /* 51 接口类型信息指针为空 */
    SFE_IF_NULL_POINTER_FULLINFO_BYID,              /* 52 接口全部信息指针为空 */
    SFE_IF_MALLOC_FAIL_IFUNIT_UPDATE,               /* 53 从资源池中申请接口单元信息失败 */
    SFE_IF_ERRPORTTYPE_BYID,                        /* 54 端口类型错误 */
    SFE_IF_GETBASEINFOFAIL_DELETE,                  /* 55 获取接口基本信息失败 */
    SFE_IF_GETBASEINFOFAIL_UPDATE,                  /* 56 获取接口基本信息失败 */
    SFE_IF_GETBASEINFOFAIL_IF,                      /* 57 获取接口基本信息失败 */
    SFE_IF_GETBASEINFOFAIL_ADDR,                    /* 58 获取接口基本信息失败 */
    SFE_IF_GETLINKINFOFAIL_ADDR,                    /* 59 获取链路层信息失败 */
    SFE_IF_ERRORIGIN_DELETE,                        /* 60 接口来源错误 */
    SFE_IF_ERRORIGIN_UPDATE,                        /* 61 接口来源错误 */
    
    SFE_IF_MAX
}SFE_IF_ERRCODE_E;

/* 数据面对应的接口类型枚举定义 */
typedef enum enumSFE_IF_TYPE
{
    SFE_IF_NULL = 0,
    SFE_IF_INLOOPBACK,
    SFE_IF_LOOPBACK,
    SFE_IF_ETH,
    SFE_IF_PPP,
    
    SFE_IF_TYPEMAX = 8
}SFE_IF_TYPE_E;

/*******************************************************************************
*    Func Name: SFE_ShowAllIfInfo
* Date Created: 2009-8-6
*       Author: w60786
*  Description: 显示数据面所有接口信息
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-6     w60786/luowentong         Creat the first version.
*
*******************************************************************************/
VOID SFE_ShowAllIfInfo(VOID);

#ifdef  __cplusplus
}
#endif

#endif


