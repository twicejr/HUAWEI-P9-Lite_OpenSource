
/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                tcpip_pub_hdr.h
*
*  Project Code: VR7C03
*   Module Name: PUBLIC 
*  Date Created: 2009-02-26
*        Author: wuhailan/zhangchi(00103194/00142640)
*   Description: public体检报告
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-26   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/

#ifndef _TCPIP_PUB_HDR_H_
#define _TCPIP_PUB_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

typedef struct tagPUBLIC_HEALTH_MEMINFO
{
    ULONG   ulModId;
    ULONG   ulMemInfo;       
}PUBLIC_HEALTH_MEMINFO_S;

typedef struct tagPUBLIC_HEALTH_MBUFMIDSTAT
{
    ULONG   ulModId;
    ULONG   ulMemInfo;    
}PUBLIC_HEALTH_MBUFMIDSTAT_S;

typedef struct tagPUBLIC_HEALTH_MBUFCACHE
{
    ULONG   ulUsedHeadNum;
    ULONG   ulUsedDBDNum;
    ULONG   ulUsedDBNum;
    ULONG   ulUsedOSNum;    
}PUBLIC_HEALTH_MBUFCACHE_S;

typedef struct tagPUBLIC_LASTWORD_MEMINFO
{
    ULONG   ulModId;
    ULONG   ulMemInfo;       
}PUBLIC_LASTWORD_MEMINFO_S;

typedef struct tagPUBLIC_LASTWORD_MBUFMIDSTAT
{
    ULONG   ulModId;
    ULONG   ulMemInfo;    
}PUBLIC_LASTWORDMBUFMIDSTAT_S;

typedef struct tagPUBLIC_LASTWORD_MBUFCACHE
{
    ULONG   ulUsedHeadNum;
    ULONG   ulUsedDBDNum;
    ULONG   ulUsedDBNum;
    ULONG   ulUsedOSNum;    
}PUBLIC_LASTWORD_MBUFCACHE_S;

/*每次报告的接口个数 */
#define  PULIC_HEALTH_MAXMEMINFO_ITEM     40  

extern VOID TCPIP_Public_Health_Batchup(VOID);
extern ULONG TCPIP_Health_MemInfo(VOID);
extern ULONG TCPIP_Health_MbufMidStatInfo(VOID);
extern ULONG TCPIP_Health_MbufCacheStatInfo(VOID);
extern ULONG TCPIP_Health_NpStatInfo(VOID);
extern ULONG TCPIP_Health_CtlMsgStatInfo(VOID);

extern ULONG TCPIP_LastWord_MemInfo(CHAR *pstBuf, ULONG *pulLastWordLen);
extern ULONG TCPIP_LastWord_MbufMidStatInfo(CHAR *pstBuf, ULONG *pulLastWordLen);
extern ULONG TCPIP_LastWord_MbufCacheStatInfo(CHAR *pstBuf, ULONG *pulLastWordLen);
extern ULONG TCPIP_LastWord_NPStatInfo(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif


