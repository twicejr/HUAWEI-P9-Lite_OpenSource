/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                        IF_VLINK.H
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2000/03/07  
 *        Author: yuanjie
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000/03/07      yuanjie         yuanjie
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2006-05-10   luyao(60000758)    为支持ARM CPU字节对齐特性，修改结构。
 *
 ************************************************************************/

#ifndef _IF_VLINK_H_
#define _IF_VLINK_H_

#ifdef  __cplusplus
extern "C"{
#endif
#include"tcpip/ifnet/include/ifnet_api.h"

#define RTM_DELVLINK    0x80    /*删除VLINK*/

#define VLINK_ADJACENT_TOTALLEN 65535
#define VLINK_ADJACENT_EACHLEN  256
#define VLINK_TABLE_EACHLEN     256
#define VLINK6_TABLE_EACHLEN    256


#define VLINK_TABLELINE_EMPTY   0
#define VLINK_TABLELINE_USED    1


typedef struct tagVLINKTABLE
{
    ULONG  ulPrevFreeIndex;          /*previous free struct*/
    ULONG  ulNextFreeIndex;          /*next free struct*/
    ULONG  ulPrevUsedIndex;          /*previous used struct*/
    ULONG  ulNextUsedIndex;          /*next used struct*/
    ULONG  ulIfIndex;                /*the IFNET index map belong to*/
    ULONG  ulUsedFlag;               /*if the struct inused 0-empty 1-used*/
    ULONG  ulSynCount;               /*syn count */
    VLINKSTATUS_S tLastStatus ;      /* save last change status */
    VOID*  pCB;                      /*Control Block of VLINK */
}VLINKTABLE_S;

#define VLINK_TABLE_NOTEXIST    0
#define VLINK_TABLE_INUSED      1
#define VLINK_TABLE_FULL        2

typedef struct tagVLINKTABLEHEAD
{
    ULONG  ulTableStatus;        /*0--not exist 1--can use 2--full*/
    ULONG  ulTableNumber;      /*total number of the table*/
    ULONG  ulTableFirstIndex;  /*the first index of the table*/
    ULONG  ulTableEndIndex;    /*the end index of the table*/
    ULONG  ulTableFirstUsedIndex;  /*the first used index of the table*/
    ULONG  ulTableEndUsedIndex;    /*the end used index of the table*/
    ULONG  ulTableFirstFreeIndex;   /*the first free index of the table*/
    ULONG  ulTableEndFreeIndex;    /*the end free index of the table*/
    VLINKTABLE_S    *pTable;           /*begin of the table*/
}VLINKTABLEHEAD_S;


/************************************************************************
 * 请在这里填写该头文件的具体内容                                       *
 ************************************************************************/
VOID VLINK_Init();
ULONG VLINK_NotifyRouter(VLINKSTATUS_S * pVLinkStatus);
ULONG VLINK_If_NotifyRouter(IFNET_S *, ULONG, UINTPTR );

ULONG IF_VLINK_IoCtl(VOID *pVLinkStatus, VOID *pCB);
ULONG VLINK_Insert(VLINKSTATUS_S *pVLinkStatus, VOID *pCB);
ULONG VLINK_Delete(VLINKSTATUS_S *);
VLINKTABLE_S *VLINK_Create_Table(ULONG );
ULONG VLINK_Add_Table(VLINKSTATUS_S *pVLinkStatus, VOID *pCB);

ULONG VLINK_ChgLinkStatus(VLINKSTATUS_S *);
ULONG IF_RecvVLinkMsg(VOID* pMsg,ULONG ulLen);
VOID* VLINK_GetCB(ULONG ulVlinkIndex);
ULONG VLINK_SetCB(ULONG ulVlinkIndex, VOID *pCB);
ULONG VLINK_IoCtl(VLINKSTATUS_S *pVLinkStatus, VOID *pCB);
ULONG VLINK6_IoCtl(IFVLINKENTRY6_S *pVLinkStatus, VOID *pCB);

ULONG IF_VLINK6_IoCtl(VOID *pVLinkStatus, VOID *pCB);


ULONG VLINK6_If_NotifyRouter( IFNET_S * pstIf, ULONG     ulCmdIndex,  UINTPTR     pData );

#define VLINK6_TABLELINE_EMPTY  0
#define VLINK6_TABLELINE_USED   1


typedef struct tagVLINK6TABLE
{
    ULONG  ulPrevFreeIndex;     /*previous free struct*/
    ULONG  ulNextFreeIndex;     /*next free struct*/
    ULONG  ulPrevUsedIndex;     /*previous used struct*/
    ULONG  ulNextUsedIndex;     /*next used struct*/
    ULONG  ulIfIndex;           /* the IFNET index map belong to*/
    ULONG  ulUsedFlag;          /*if the struct inused 0-empty 1-used*/
    ULONG  ulSynCount;          /*syn count */
    IFVLINKENTRY6_S tLastStatus ;   /* save last change status */
    VOID*  pCB;                 /*Control Block of VLINK */
}VLINK6TABLE_S;


#define VLINK6_TABLE_NOTEXIST   0
#define VLINK6_TABLE_INUSED     1
#define VLINK6_TABLE_FULL       2

typedef struct tagVLINK6TABLEHEAD
{
    ULONG   ulTableStatus;      /*0--not exist 1--can use 2--full*/
    ULONG  ulTableNumber;      /*total number of the table*/
    ULONG  ulTableFirstIndex;  /*the first index of the table*/
    ULONG  ulTableEndIndex;    /*the end index of the table*/
    ULONG  ulTableFirstUsedIndex;  /*the first used index of the table*/
    ULONG  ulTableEndUsedIndex;    /*the end used index of the table*/
    ULONG  ulTableFirstFreeIndex;  /*the first free index of the table*/
    ULONG  ulTableEndFreeIndex;    /*the end free index of the table*/
    VLINK6TABLE_S   *pTable;        /*begin of the table*/
}VLINK6TABLEHEAD_S;

#define RTM_CREATE  0x01
#define RTM_DEL     0x02    

/*函数声明*/
VOID* VLINK6_GetCB(ULONG ulVlinkIndex);
VLINK6TABLE_S *VLINK6_Create_Table(ULONG ulLen);
ULONG VLINK6_Add_Table(IFVLINKENTRY6_S *pVLinkStatus, VOID *pCB);
ULONG VLINK6_Insert(IFVLINKENTRY6_S *pVLinkStatus, VOID *pCB);
ULONG VLINK6_Delete(IFVLINKENTRY6_S *pVLinkStatus);

#ifdef  __cplusplus
}
#endif

#endif  /* _IF_VLINK_H_ */

