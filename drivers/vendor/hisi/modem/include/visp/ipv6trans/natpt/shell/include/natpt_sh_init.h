/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             Natpt_Sh_Init.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-18
 *  Author:             Desh   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  2003-12=15  Archana P V      For Defect BYAD05088
 *  2004-03-18  Archana P V      For Defect BYAD09118
 ************************************************************************/



#ifndef _NATPT_SH_INIT_H
#define _NATPT_SH_INIT_H

#ifdef  __cplusplus
extern  "C"{
#endif


/*----------------------------------------------*
 * Header Files                
 *----------------------------------------------*/

#define NATPT_RPC_TIMEOUT (1000 * 10) /*Changed for defect BYAD09118.Modified B y : Archana P V */
#define NATPT_MAX_SLOT_NUMBER 20 
#define NATPT_MAX_OUTPKT 1 
#define NATPT_MAX_QUE_SIZE 1800 

#define NATPT_NOT_IN_MULTICAST_GROUP 2*NATPT_MAX_SLOT_NUMBER

/*----------------------------------------------*
 * External Variables            
 *----------------------------------------------*/
/* Hided by Leonru 
  extern ComponentInfo * g_pCompNATPTInfo ; */
/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/

/*Added for license change */

#define NATPT_PAT_DISABLE_CLI  0
#define NATPT_PAT_ENABLE_CLI   1
#define NATPT_DPAT_DISABLE_CLI 0
#define NATPT_DPAT_ENABLE_CLI  1

typedef struct tag_SlotInMultiCase
{
    USHORT usCmdSgn;
    USHORT usCount;
    ULONG  ulSlot[NATPT_MAX_SLOT_NUMBER];
}NATPT_SLOTINMULTICAST;

/*----------------------------------------------*
 * External Functions
 *----------------------------------------------*/

/*----------------------------------------------*
 * Functions
 *----------------------------------------------*/

ULONG NATPT_Shell_Init() ;
ULONG NATPT_SH_GlobalInit( );
ULONG NATPT_CFG_Init () ;
ULONG NATPT_MBUF_TR_Init ();
ULONG NATPT_IPC_Init();
ULONG NATPT_MBUF_TR_Send(MBUF_S* pstMbuf,ULONG ulNode, ULONG ulAttachMessage) ;
ULONG NATPT_SetModuleInfo( NATPT_MOD_INFO_S *pstModInfo) ;
ULONG NATPT_MBUF_TR_Send(MBUF_S* pstMbuf,ULONG ulNode, ULONG ulAttachMessage);
ULONG NATPT_SendToIPC(UCHAR* pucData,ULONG ulLength,ULONG ulNode, ULONG ulMode,UCHAR* pucRecv,ULONG ulRecvlength);
ULONG NATPT_Multicast(UCHAR* pucData,ULONG ulLength, ULONG ulMode,UCHAR* pucRecv,ULONG ulRecvlength);
ULONG NATPT_Join_Multicast(ULONG ulNode);
ULONG NATPT_Leave_Multicast(ULONG ulNode) ;
VOID NATPT_IPC_CALLBACK(ULONG ulSrcNode,    ULONG ulSrcModuleID,    VOID *pReceiveData, ULONG ulReceiveDataLen,VOID **ppSendData,   ULONG *pulSendDataLen);
ULONG NATPT_IC_Init();
ULONG NATPT_Register_NonComIntALL() ;
extern ULONG CFG_ModuleRegister(ULONG,ULONG,ULONG,ULONG,ULONG (*)(VOID*,VOID**) );
extern VOID  IPC_RPC_Register(ULONG,VOID (*)(ULONG,ULONG,VOID *,ULONG,VOID **,ULONG*));
extern VOID *IPC_RPC_AllocMsg(ULONG, ULONG);

extern VOID *IPC_RPC_AllocMsg(ULONG,ULONG);
extern VOID  IPC_RPC_FreeMsg(VOID *);
extern ULONG IPC_RPC_SyncCall(ULONG,ULONG,ULONG,ULONG,VOID *,ULONG,VOID **,ULONG*,ULONG);
extern ULONG IPC_Send(ULONG ulIpcChId, ULONG ulDstNode, ULONG ulDstIpcChId,
               ULONG ulMode, VOID *pMsg, ULONG ulLen, 
               ULONG ulUserInfo);
ULONG NATPT_Mbuf_Recv(MBUF_S *pstMBuf);
VOID NATPT_Mbuf_Write_Queue(MBUF_S *pstMBuf,ULONG ulAttachMessage);
VOID NATPT_RegToIC(VOID);
/**  Added by Keshava Check with Desh and remove it Later */
VOID NATPT_Analyse_Result_Multicast(VOID* pSendData , ULONG ulslot );
/* added by keshava */
ULONG NATPT_Create_Timer ( VOID (*pfTimerFunc)(VOID * ), ULONG* timerid );
ULONG NATPT_Delete_Timer ( ULONG  timerid );
VOID NATPT_IPC_ASYN_CALLBACK(ULONG ulFlag,ULONG ulSrcChID,ULONG ulDstNode,ULONG ulDstChID,VOID *pReceiveData,ULONG ulLen);
ULONG NATPT_SH_MGMT_Init (COM_ID_INFO_S *pstComInfo);
/*Added for Defect BYAD05088*/
ULONG NATPT_Sh_SetLcsAvailValue(CHAR* szLcsKey, ULONG ulAvailValue);


#ifdef  __cplusplus
}
#endif

#endif

