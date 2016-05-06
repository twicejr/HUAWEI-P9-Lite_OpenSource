/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_ext_static.h
*
*  Project Code: VISPV100R007
*   Module Name: BFD EXTERN
*  Date Created: 2008-07-24
*        Author: qinyun
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME              DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-07-24      qinyun            Create
*
*******************************************************************************/
#ifndef _BFD_EXT_STATIC_H_
#define _BFD_EXT_STATIC_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagBfdForStaticFilter
{ 
    ULONG ulFltFlag;
    ULONG ulDestIp;
    ULONG ulPrefixLen;
    ULONG ulVrfIndex;
}BFD_FOR_STATIC_FILTER_S;
typedef struct tagBfd6ForStaticFilter
{ 
    ULONG ulFltFlag;
    ULONG ulDestIp[4];
    ULONG ulPrefixLen;
    ULONG ulVrfIndex;
}BFD6_FOR_STATIC_FILTER_S;
/* BFD会话关联表项标识*/
typedef struct tagBFD_FOR_STATIC_KEY_S
{
    ULONG ulVrfIndex    ;     /* vrf 索引 */
    ULONG ulSessionId   ;     /* 会话标识 */
    ULONG ulIsAllVrf    ;     /* 是否查询所有VRF下的关联表项:1-是,0-不是 */
}BFD_FOR_STATIC_KEY_S;

extern VOID *Extern_BFD_GetNextStaticRelationByFilter(VOID *pFilter,VOID *pCurEntry);
extern ULONG Extern_BFD_SetRtStaticDetecTime(ULONG ulSecTime);
extern ULONG Extern_BFD_AddRtStatic(ULONG *ulDestIp,ULONG ulPrefixLen,ULONG *ulNextHop,ULONG ulIfIndex,
                                ULONG ulVrfIndex,ULONG ulSessionId, ULONG ulIpVersion,ULONG ulRouteVrfIndex);
extern ULONG Extern_BFD_DelRtStatic(ULONG *ulDestIp,ULONG ulPrefixLen,ULONG *ulNextHop,ULONG ulIfIndex,
                                           ULONG ulSessionId,ULONG ulVrfIndex,ULONG ulRouteVrfIndex,ULONG ulIpVersion);
extern BOOL_T Extern_BFD_CheckStaticRelationByFilter(BFD_FOR_STATIC_FILTER_S *pstFilter, BFD_STATIC_NODE_S * pstEntry);
/* Add for DTS2011021002203, by chenyaoKF34558, at 2011-02-28. 修改原因: 重新设计license功能 */
extern ULONG Extern_BFD_ActRtStatic(ULONG ulDestIp,ULONG ulPrefixLen,ULONG ulNextHop,ULONG ulIfIndex,
                                           ULONG ulSessionId,ULONG ulVrfIndex, ULONG ulRelVrfIndex, ULONG ulIpVersion);
extern ULONG Extern_BFD_RmNotifyUpStatic(ULONG ulProcIndex,BFD_STATIC_NODE_S *pstNode,ULONG ulIpVersion);
extern VOID *Extern_BFD6_GetNextStaticRelationByFilter(VOID *pFilter,VOID *pCurEntry);
extern BOOL_T Extern_BFD6_CheckStaticRelationByFilter(BFD6_FOR_STATIC_FILTER_S *pstFilter, BFD_STATIC_NODE_S * pstEntry);
extern ULONG Extern_BFD_FindStaticRelation(ULONG *ulDestIp,ULONG ulPrefixLen,
                                    ULONG *ulNextHop,ULONG ulIfIndex,BFD_STATIC_NODE_S **pstNode,
                                    ULONG ulVrfIndex,ULONG ulIpVersion);
extern VOID Extern_BFD_GcProcess(BFD_STATIC_NODE_S *pstStaticNode);

#ifdef __cplusplus
}
#endif

#endif


