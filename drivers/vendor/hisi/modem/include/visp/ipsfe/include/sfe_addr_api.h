/*******************************************************************************
*
*
*                Copyright 2010, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_addr_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2010-6-9
*        Author: w60786
*   Description: 数据面地址管理模块用户API头文件，定义用户需要使用的数据结构、宏和API原型
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-6-9     w60786           Creat the first version.
*
*******************************************************************************/
#ifndef _SFE_ADDR_API_H_
#define _SFE_ADDR_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面ADDR模块错误码 */
typedef enum enumSfeAddrErrCode
{
    SFE_ADDR_OK = SFE_OK,                               /* 操作成功 */
    SFE_ADDR_ERR_BEGIN = SFE_ADDR_BEGIN_RET_CODE,       /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_ADDR_IFID_INVALID_ADD,                          /* 1  要添加地址的接口指针为空 */
    SFE_ADDR_IP_INVALID_ADD,                            /* 2  要添加地址的不合法 */
    SFE_ADDR_GETBASEINFOFAIL_ADD,                       /* 3  添加地址,获取接口base节点失败 */
    SFE_ADDR_IP_NUM_MAX_ADD,                            /* 4  添加地址,接口的地址数目已经达到最大值 */
    SFE_ADDR_MALLOC_FAIL_ADDIPADDR_ADD,                 /* 5  添加地址,获取地址管理数据结构索引失败 */
    SFE_ADDR_GETBASEINFOFAILFORUPDATE_ADD,              /* 6  添加地址,获取地址管理数据结构节点失败 */
    SFE_ADDR_IP_HAS_SETTED_ADD,                         /* 7  添加地址,IP已在统一接口配置过 */
    SFE_ADDR_IFID_INVALID_DEL,                          /* 8  要删除地址的接口指针为空 */
    SFE_ADDR_IP_INVALID_DEL,                            /* 9  要删除地址的接口指针为空 */
    SFE_ADDR_GETBASEINFOFAIL_DEL,                       /* 10 删除地址,获取接口base节点失败 */
    SFE_ADDR_IP_NOT_EXIST_DEL,                          /* 11 删除地址,要删除的地址不存在 */
    SFE_ADDR_FREE_IPADDR_FAIL_DEL,                      /* 12 删除地址,资源池释放地址节点失败 */
    SFE_ADDR_GET_SFE_IPADDR_MAX_NUM_PRECFG_FAIL,        /* 13 地址管理初始化,获取地址资源初始化数量失败 */
    SFE_ADDR_GET_SFE_IPADDR_MAX_NUM_PER_IF_PRECFG_FAIL, /* 14 地址管理初始化,获取每个接口最大可配置IP ADDR数目失败 */
    SFE_ADDR_ALLOC_IP_ADDR_POOL_FAIL,                   /* 15 地址管理初始化,初始化IP ADDR资源池失败 */

}SFE_ADDR_ERR_CODE_E;

/*******************************************************************************
*    Func Name: SFE_ADDR_AddIpAddr
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 添加地址
*  Description: 添加地址
*        Input: UINT32 u32IpAddr: 要添加的地址(主机序)
*               UINT32 u32SubnetMask: 要添加的地址子网掩码
*               SFE_MBUF_IFID_S *pstIfId: 要添加地址的接口
*       Output: 
*       Return: 成功返回 SFE_ADDR_OK
*               失败返回 错误码
*      Caution: 1.由调用者保证一个地址只能配置在一个接口上.内部不做检查判断.
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
UINT32 SFE_ADDR_AddIpAddr(UINT32 u32IpAddr, UINT32 u32SubnetMask, SFE_MBUF_IFID_S *pstIfId);

/*******************************************************************************
*    Func Name: SFE_ADDR_DelIpAddr
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 删除地址
*  Description: 删除地址
*        Input: UINT32 u32IpAddr: 要删除的地址(主机序)
*               UINT32 u32SubnetMask: 要删除的地址的子网掩码
*               SFE_MBUF_IFID_S *pstIfId: 要删除地址的接口
*       Output: 
*       Return: 成功返回 SFE_ADDR_OK
*               失败返回 错误码
*      Caution: 
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
UINT32 SFE_ADDR_DelIpAddr(UINT32 u32IpAddr, UINT32 u32SubnetMask, SFE_MBUF_IFID_S *pstIfId);

/*******************************************************************************
*    Func Name: SFE_ADDR_ShowIpAddr
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 显示数据面所有地址信息
*  Description: 显示数据面所有地址信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
VOID SFE_ADDR_ShowIpAddr(VOID);


#ifdef  __cplusplus
}
#endif

#endif

