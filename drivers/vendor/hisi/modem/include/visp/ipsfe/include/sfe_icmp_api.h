/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_icmp_api.h
*
*  Project Code: VISPV1R8C02
*   Module Name: ICMP
*  Date Created: 2009-9-11
*        Author: zengshaoyang(62531)/zhangchunyu(62474) 
*   Description: 数据面ICMP对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-9-11    zengshaoyang(62531)/zhangchunyu(62474)            Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_ICMP_API_H_
#define _SFE_ICMP_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面BFD模块错误码 */
enum enumSfeIcmpErrCode
{ 
    SFE_ICMP_OK = SFE_OK,                         /* 操作成功 */
    SFE_ICMP_ERR_BEGIN = SFE_ICMP_BEGIN_RET_CODE, /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_ICMP_MALLOC_SWITCH_ERR,                   /* 1 分配ICMP调试开关内存失败 */
    SFE_ICMP_SETSWITCH_ERR,                       /* 2 设置发送ICMP调试开关非法 */
    SFE_ICMP_SETSWITCH_NULL_POINT,                /* 3 设置ICMP开关指针为空 */
    SFE_ICMP_GETSWITCH_NULL_POINT,                /* 4 获取ICMP开关指针为空 */
};

#ifdef  __cplusplus
}
#endif

#endif



