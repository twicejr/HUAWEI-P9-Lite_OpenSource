/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsafe_fc_api.h
*
*  Project Code: V1.1.0
*   Module Name: ipsafe flow control api header file
*  Date Created: 2010-03-05
*        Author: v71873
*   Description: ipsafe flow control api header file. Contains the declararion 
*                of all functions and structures for flow control module exposed
*                to the user.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2010-03-05   v71873                   Create the first version.
*  2010-03-08   v71873                   Moved the declarations of 
*                                        IPSAFE_FC_Attach, IPSAFE_FC_Detach 
*                                        and IPSAFE_FC_Search to ipsafe_fc_api.h
*
*******************************************************************************/

#ifndef _IPSAFE_FC_API_H_
#define _IPSAFE_FC_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/*STRUCT<Structure for flow context. Every area must be 4-byte aligned>*/
typedef struct tagFlowContext
{
    /* begin of topo area */
    struct tagFlowContext *pstNext;
    struct tagFlowContext *pstPrev;
    
    /* end of topo area */

    /* begin of public area */
    UINT32 u32SrcIP;       /* source ip, network order */
    UINT32 u32DstIP;       /* destination ip,network order */
    UINT16 u16SrcPort;     /* source port,network order */
    UINT16 u16DstPort;     /* destination port,network order */
    UINT8  u8Protocol;     /* protocal number */
    UINT8  u8ConeMode;     /* cone mode, full cone or symmetric */
    UINT8  au8Reserved[2]; /* reserve for align */
    UINT32 u32VpnIndex;    /* vpn index */

    UINT32 u32HashValue;   /* hash value based on 5-elements */
    /* computed by hashValue % (number of flow queue)
       packets which match the 5-elements will enqueue the flow queue and then be scheduled */
    UINT32 u32FlowQueueID;
    
    /* end of public area */

    /* begin of NAT private area */
    VOID *pstNatSession;

    /* end of NAT private area */

    /* begin of ASPF private area */
    VOID *pstAspfSession;

    UINT32 u32CreatorVCPU;
    
    /* end of ASPF private area */

}IPSAFE_FLOW_CONTEXT_S;

/*******************************************************************************
*    Func Name: FC_ShowOneInfo
* Date Created: 2010-1-12
*       Author: z62474/b71224
*      Purpose: This function is used to display one session.
*  Description: This function displays the information of one session. It displays the 
*               source and destination IPs and ports, the protocol, the VPN index, the 
*               hash value, the flow queue ID, and the NAT and ASPF addresses.
*        Input: UINT32 u32SrcIP: Source IP, Host order<All int>
*               UINT32 u32DstIP: Destination IP, Host order<All int>
*               UINT16 u16SrcPort: Source port, Host order<All short>
*               UINT16 u16DstPort: Destination port, Host order<All short>
*               UINT8 u8Protocol: Protocol<All char>
*               UINT32 u32VpnIndex: Vpn index<All int>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-06  z62474/b71224      Create the first version.
*
*******************************************************************************/
extern VOID FC_ShowOneInfo(UINT32 u32SrcIP, UINT32 u32DstIP, 
                      UINT16 u16SrcPort, UINT16 u16DstPort,
                      UINT8 u8Protocol, UINT32 u32VpnIndex);

/*******************************************************************************
*    Func Name: FC_ShowAllInfo
* Date Created: 2010-1-12
*       Author: z62474/b71224
*      Purpose: This function displays the information of all flow context.
*  Description: This function displays the information of all flow context. 
*               It displays the source and destination IPs and ports, the protocol, 
*               the VPN index, the hash value, the flow queue ID, and 
*               the NAT and ASPF addresses.
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-06  z62474/b71224      Create the first version.
*
*******************************************************************************/
extern VOID FC_ShowAllInfo(VOID);

/*ERRORCODE< Flow context error codes >*/
enum enumFCRetCode
{
    IPSAFE_FC_SUCCESS,                                     /*<0> On success*/
    IPSAFE_FC_ERR_BEGIN_CODE = IPSAFE_FC_BEGIN_RET_CODE,   /*<6000> Beginning of FC error codes*/
    IPSAFE_FC_FCINIT_ERR_ALLOC_HASH,                       /*<6001> Memory allocation for hash is not successful*/
    IPSAFE_FC_FCINIT_ERR_ALLOC_BLK,                        /*<6002> BlkInit fails*/
    IPSAFE_FC_FCINIT_ERR_CREATE_SPINLOCK,                  /*<6003> Spin lock creation error */
    IPSAFE_FC_FCINIT_ERR_ADDNAME_SPINLOCK,                 /*<6004> Add name spin lock error*/
    IPSAFE_FC_FCATCH_ERR_GET_NODE_FROM_BLK,                /*<6005> Blk alloc fail*/
    IPSAFE_FC_FCSRCH_ERR_FC_NOT_FIND,                      /*<6006> FC not found*/
    IPSAFE_FC_FCINIT_ERR_ALLOCK_NUM_MEM,                   /*<6007> MCMemAlloc fails*/ 
    IPSAFE_FC_FCINIT_ERR_ADD_NUM_DB,                       /*<6008> MCMemNameDBAdd fails*/
    IPSAFE_FC_FCINIT_CONE__ERR_ALLOC_HASH,                 /*<6009> Memory allocation for Cone hash is not successful*/
    IPSAFE_FC_FCATCH_CONE_ERR_GET_NODE_FROM_BLK,           /*<6010> Blk alloc fail for Cone NAT*/
    IPSAFE_FC_FCINIT_CONE_ERR_ADDNAME_SPINLOCK,            /*<6011> Add name spin lock error for Cone Nat*/
    IPSAFE_FC_FCINIT_CONE_ERR_CREATE_SPINLOCK              /*<6012> Spin lock creation error for Cone Nat */
};
#ifdef  __cplusplus
}
#endif

#endif

