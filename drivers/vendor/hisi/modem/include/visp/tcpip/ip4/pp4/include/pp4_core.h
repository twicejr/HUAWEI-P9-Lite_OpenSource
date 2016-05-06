/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_core.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-6-18
*        Author: chenshuanglong(28510)
*   Description: PP4内核相关宏、数据结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-6-18    chenshuanglong(28510)   Create
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_CORE_H_
#define _PP4_CORE_H_


/* ACL ip packet debug opt */
#define IP_DEBUG_IFIN             1    /*  debug ip packet 加入接口过滤  */
#define IP_DEBUG_IFOUT            2    /*  debug ip packet 加出接口过滤 */
#define IP_DEBUG_IFANY            3    /*  debug ip packet 加入或出接口过滤 */


/* PP4返回的错误码定义已经挪到pp4_api.h里 2008-4-24,z00104207*/

#define PP4_DIRECTLOOKUPIP   1
#define PP4_NO_DIRECTLOOKUPIP 0

#define PP4_INPUT_NORMAL        0  
#define PP4_INPUT_DISTRIBUTE    1

/* PP4模块使用的SID统一在此定义,一个函数对应一个SID */
#define    SID_COMP_PP4_IP_INPUT                1
#define    SID_COMP_PP4_IP_FORWARD              2
#define    SID_COMP_PP4_IP_OUTPUTFORINTERNAL    3
#define    SID_COMP_PP4_IP_IF_OUTPUT            4
#define    SID_COMP_PP4_IP_REASS                5    
#define    SID_COMP_PP4_IP_SRCROUTE             6
#define    SID_COMP_PP4_IP_INSERTOPTION         7
#define    SID_COMP_PP4_IP_FRAG                 8 
#define    SID_COMP_PP4_IP_GETMOPTIONS          9
#define    SID_COMP_PP4_IP_GETVIPPKT            10
#define    SID_COMP_PP4_IP_SLOWTIMO             11
#define    SID_COMP_PP4_IP_PROCBYBOARD          12


struct tagIP;
struct  tagUDPHDR;
/* callback function set of pp4 */
typedef struct tagPp4ICCallbackSet
{
    ULONG (*pfIP_PP4_SH_SendDebugInfoToIC)(CHAR* strInfo1, CHAR* strInfo2, CHAR * strInfo3,
           struct tagMBuf* pMbuf,ULONG ulDisplay);
    ULONG (*pfIP_PP4_SH_SanForwardDebugToIC)(CHAR* strInfo1, CHAR* strInfo2,struct tagUDPHDR *pUdpHdr,
           struct  tagIP* pstIp);
    ULONG (*pfIP_PP4_SH_HaInfoToIC)(ULONG ulMId, ULONG ulInfoId, char *pBuf);
}IP_PP4_IC_CALLBACK_SET_S;

/* module info of pp4 */
typedef struct tagPp4ModuleInfo
{
    ULONG ulModID;        /* Module id;*/
    ULONG ulSubModID;     /* Sub module id;*/
    ULONG ulIfOutputMbuftrId;
    ULONG ulIpOptionMbuftrId;
    ULONG ulDeliverUpMbuftrId;
    ULONG ulDirectLookUpIp;/*接收报文时是否先与本机地址比较的开关*/
    ULONG ulDistriSockFlag;
} IP_PP4_MOD_INFO_S;

#endif  /* _PP4_CORE_H_  */


#ifdef  __cplusplus
}
#endif

