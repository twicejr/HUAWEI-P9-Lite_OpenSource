/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              acl6_var.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created: 
 *        Author: 
 *   Description: 全局变量的声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 ************************************************************************/
#ifndef _ACL6_VAR_H_
#define _ACL6_VAR_H_

#ifdef  __cplusplus
extern "C" 
{
#endif


extern ULONG g_ulAcl6ModID;
extern ULONG g_ulSemForACL6;
extern ULONG g_ulAcl6GroupNumSum;
extern ACL6_ACCESSLIST_S g_stACL6;

extern ACL6_PPI_GROUP_Update_NODES g_pstAcl6PpiGroupUpdate;
extern ACL6_PPI_RULE_Update_NODES  g_pstAcl6PpiRuleUpdate;
extern ACL6_GROUP_OR_RULE_CHANGE_HOOK  g_pstAcl6ChangeFunc;

extern const CHAR g_szACL6Version[LEN_32];
extern CHAR *g_pcACL6CompileTime;

extern ACL6_UPDATE_CALLBACK_NODE_S* g_pstACL6UpdateCallBacks;

#ifdef  __cplusplus
}
#endif
   
#endif
