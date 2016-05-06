/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ethvln_ha.h
*
*  Project Code: VISPV100R008C02
*   Module Name: Ethvlan备份模块头文件 
*  Date Created: 2008-11-7
*        Author: z62474
*   Description: ethvln_ha.h
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME               DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-11-7   z62474      Create the first version.
*******************************************************************************/
#ifndef _ETHVLN_HA_H_
#define _ETHVLN_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* 以太VLAN备份消息头结构 */
typedef struct tagEthVlanHaHead
{
    USHORT  usBakType;          /* ETH VLAN备份消息类型  */
    USHORT  usBakLen;           /* ETH VLAN备份消息长度  */
}ETHVLAN_HA_HEAD_S;


/* 以太VLAN备份数据 */
typedef struct tagEthVlanHaData
{
    ULONG   ulIfIndex;         /* 子接口索引 */
    USHORT  usMinVid;          /* VLAN ID最小值 */
    USHORT  usMaxVid;          /* VLAN ID最大值 */
    USHORT  usEncapType ;      /* 封装格式 */
    UCHAR   ucpadd[2];
}ETHVLAN_HA_DATA_S;


#define ETHVLAN_HA_BATCH         0x1
#define ETHVLAN_HA_REALTIME      0x2

#define SET_ETHVLAN_HA_HEAD(pstEthVlanBakHdr, ulBakType, ulBakLen)\
{\
    (pstEthVlanBakHdr)->usBakType = (USHORT)(ulBakType);\
    (pstEthVlanBakHdr)->usBakLen  = (USHORT)(ulBakLen);\
}


#define ETHVLAN_VID_CONVERT_HADATA(pstVidNode, pstEthVlanData) \
{ \
    (pstEthVlanData)->ulIfIndex   = (pstVidNode)->ulSubIfIndex; \
    (pstEthVlanData)->usMinVid    = (pstVidNode)->usVID; \
    (pstEthVlanData)->usMaxVid    = (pstVidNode)->usVID; \
    (pstEthVlanData)->usEncapType = (pstVidNode)->encapType; \
}


#define ETHVLAN_HA_ADD  1
#define ETHVLAN_HA_DEL  2


extern ULONG ETHVLAN_HA_BatchBackup(VOID);
extern ULONG ETHVLAN_HA_RealTimeBackup(ULONG ulBakType, VOID* pData);
extern ULONG ETHVLAN_HA_BuildOnePkt(UCHAR* pucData, ULONG ulOffset, ULONG ulBufTotalLen,
                                     VOID *pstVoid, ULONG *pulMsgAddLen, USHORT usType);
extern ULONG ETHVLAN_HA_CntBakLen(ULONG ulBakType, ULONG *pulBakLen);
extern ULONG EHTVLAN_HA_OpenWaitList(UINTPTR *pulWaitListHandle);
extern ULONG EHTVLAN_HA_CloseWtLstObject(UINTPTR ulWaitListHandle);
extern ULONG EHTVLAN_HA_GetWtLstEntry(UINTPTR ulWaitListHandle, ETHVLAN_VID_NODE_S *pstVidNode);
extern VOID *EHTVLAN_HA_GetWtLstNext(VOID *pCur,VOID **ppNext);
extern ULONG ETHVLAN_HA_Input(UCHAR *pucBuf, ULONG ulMsgLen);
extern ULONG ETHVLAN_HA_OutputMsg(UCHAR *pucData, ULONG ulMsgLen);
extern VOID  ETHVLAN_HA_VerboseOutput(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
extern ULONG ETHVLAN_HA_Smooth(VOID);
extern ULONG ETHVLAN_HA_Clean(VOID);



#ifdef __cplusplus
}
#endif

#endif

