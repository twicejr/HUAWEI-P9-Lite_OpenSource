/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_comp.h
*
*  Project Code: VISPV100R007
*   Module Name: igmp  
*  Date Created: 2008-04-15
*        Author: zengshaoyang62531
*   Description: igmp组件相关定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-15   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_COMP_H_
#define _IGMPV3_COMP_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef struct tagIpIgmpModInfo
{
    ULONG ulModId;
}IpIgmpModInfo_S;

#define IGMP_DEF_GLOBALTIME 100
#define IGMP_DEF_INTERFACES 16
#define IGMP_DEF_GROUPS_ON_INTERFACE     16

extern APP_INIT_INFO_S  g_stIgmp4AppInfo;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

