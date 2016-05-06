/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_sem.c                                                         */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement semaphore                                          */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (VOS_VXWORKS == VOS_OS_VER) 
#include "semLib.h"
#endif

#include "vos_config.h"
#include "v_sem.h"
#include "stdlib.h"
#include "stdio.h"
#include "v_IO.h"
#include "v_task.h"
#include "v_int.h"


#if (VOS_VXWORKS == VOS_OS_VER) 


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_SEM_C
/*lint +e767 modify:x51137; review:h59254; */

typedef struct SEM_CONTROL_STRU
{
    int                       Flag;/* control block's state */
    struct SEM_CONTROL_STRU   *SemId;/* the ID return to User */
    int                       SemType;/* type of SEM */
    int                       SemFlags;
    int                       SemInitCount;
    char                      Name[VOS_MAX_SEM_NAME_LENGTH];
    SEM_ID                    VxWorksSemId;/* maped VxWorks ID */
} SEM_CONTROL_BLOCK;

/* the number of queue's control block */
VOS_UINT32              vos_SemCtrlBlkNumber;

/* the start address of queue's control block */
SEM_CONTROL_BLOCK       *vos_SemCtrlBlk;

/* the Max usage of queue */
VOS_UINT32              vos_SemMaxSemId;

#define VOS_SEM_CTRL_BUF_SIZE (sizeof(SEM_CONTROL_BLOCK)*VOS_MAX_SEM_NUMBER)

VOS_CHAR g_acVosSemCtrlBuf[VOS_SEM_CTRL_BUF_SIZE];

/*****************************************************************************
 Function   : VOS_SemCtrlBlkInit
 Description: Init semaphore's control block
 Input      : ulSemCtrlBlkNumber -- number
 Return     : None
 Other      :
 *****************************************************************************/
VOS_VOID VOS_SemCtrlBlkInit(VOS_VOID)
{
    int i;

    vos_SemCtrlBlkNumber = VOS_MAX_SEM_NUMBER;

    vos_SemCtrlBlk = (SEM_CONTROL_BLOCK*)g_acVosSemCtrlBuf;

    for(i=0; i<(int)vos_SemCtrlBlkNumber; i++)
    {
        vos_SemCtrlBlk[i].Flag  = VOS_SEM_CTRL_BLK_IDLE;
        vos_SemCtrlBlk[i].SemId = vos_SemCtrlBlk+i;
    }

    vos_SemMaxSemId = 0;

    return;
}

/*****************************************************************************
 Function   : VOS_SemCtrlBlkGet
 Description: allocate a control block
 Input      : void
 Return     : address
 Other      :
 *****************************************************************************/
SEM_CONTROL_BLOCK *VOS_SemCtrlBlkGet(VOS_VOID)
{
    VOS_UINT32      i;
    int             intLockLevel;

    intLockLevel = VOS_SplIMP();

    for(i=0; i<vos_SemCtrlBlkNumber; i++)
    {
        if(vos_SemCtrlBlk[i].Flag == VOS_SEM_CTRL_BLK_IDLE)
        {
            vos_SemCtrlBlk[i].Flag = VOS_SEM_CTRL_BLK_BUSY;
            break;
        }
    }

    VOS_Splx(intLockLevel);

    if( i < vos_SemCtrlBlkNumber)
    {
        /* record the max usage of SEM */
        if ( i > vos_SemMaxSemId )
        {
            vos_SemMaxSemId = i;
        }

        return vos_SemCtrlBlk+i;
    }
    else
    {
        /*lint -e534*/
        LogPrint("# VOS_GetSemCtrlBlk no Idle.\r\n");
        /*lint +e534*/

        VOS_SetErrorNo(VOS_ERRNO_SEMA4_FULL);

        return(VOS_MAX_SEM_ID_NULL);
    }
}

/*****************************************************************************
 Function   : VOS_SemCtrlBlkFree
 Description: fress a block
 Input      : Sem_Address -- address
 Return     : VOS_OK on success or errno on failure.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_SemCtrlBlkFree( SEM_CONTROL_BLOCK *Sem_Address )
{
    int             intLockLevel;

    if( Sem_Address == Sem_Address->SemId )
    {
        if(Sem_Address->Flag == VOS_SEM_CTRL_BLK_IDLE)
        {
            return(VOS_ERR);
        }
        else
        {
            intLockLevel = VOS_SplIMP();

            Sem_Address->Flag = VOS_SEM_CTRL_BLK_IDLE;

            VOS_Splx(intLockLevel);
        }

        return(VOS_OK);
    }
    else
    {
        Print("# VOS_FreeSemCtrlBlk free NULL Sem.\r\n");

        return(VOS_ERR);
    }
}

/*****************************************************************************
 Function   : VOS_SmCCreate
 Description: To create a counting semaphore;
 Input      : acSmName -- the semaphore name, can be null
              ulSmInit -- The count number of the semaphore that create;
              ulFlags  -- FIFO or priority;
 Output     : pulSmID  -- the ID of the create semaphore;
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmCCreate( VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_SEM *pulSmID )
{
    int                    i;
    SEM_CONTROL_BLOCK      *iSemId;
    SEM_ID                 SemId;
    int                    iOptions = 0;

    if( (ulFlags & VOS_SEMA4_PRIOR) )
    {
        iOptions |= SEM_Q_PRIORITY;
    }
    else
    {
        iOptions |= SEM_Q_FIFO;
    }

    if ( (ulFlags & VOS_SEMA4_INVERSION_SAFE) && (0xFFFFFFFF == ulSmInit) )
    {
        iOptions |= SEM_INVERSION_SAFE;
    }

    iSemId = VOS_SemCtrlBlkGet();

    if( iSemId == VOS_MAX_SEM_ID_NULL)
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        return(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
    }

    if(ulSmInit == 0xFFFFFFFF)
    {
        SemId = semMCreate( iOptions);
    }
    else
    {
        SemId = semCCreate( iOptions , (int)ulSmInit );
    }

    if(SemId == NULL)
    {
        VOS_SemCtrlBlkFree(iSemId);
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        return(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
    }
    else
    {
        *pulSmID = (VOS_SEM)iSemId;

        if ( VOS_NULL_PTR != acSmName )
        {
            for(i=0; i<VOS_MAX_SEM_NAME_LENGTH/2; i++)
            {
                iSemId->Name[i]  = acSmName[i];
            }
            iSemId->Name[VOS_MAX_SEM_NAME_LENGTH/2]  = '\0';
        }
        else
        {
            iSemId->Name[0] = '\0';
        }

        if(ulSmInit == 0xFFFFFFFF)
        {
            iSemId->SemType  = VOS_SEM_TYPE_MUTEX;
        }
        else
        {
            iSemId->SemType  = VOS_SEM_TYPE_COUNT;
        }

        iSemId->SemFlags     = (int)ulFlags;
        iSemId->SemInitCount = (int)ulSmInit;
        iSemId->VxWorksSemId = SemId;

        return(VOS_OK);
    }
}

/*****************************************************************************
 Function   : VOS_SmMCreate
 Description: To create a Mutex semaphore, can be null
 Input      : acSmName[4] -- the semaphore name;
              ulFlags     -- FIFO or priority;
 Output     : pulSmID     -- the ID of the created semaphore;
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmMCreate( VOS_CHAR   Sm_Name[4],
                          VOS_UINT32 Flags,
                          VOS_SEM *Sm_ID )
{
    return( VOS_SmCCreate( Sm_Name, 0xFFFFFFFF, Flags, Sm_ID ));
}

/*****************************************************************************
 Function   : VOS_SmCCreate
 Description: To create a counting semaphore;
 Input      : acSmName -- the semaphore name, can be null
              ulSmInit -- The count number of the semaphore that create;
              ulFlags  -- FIFO or priority;
 Output     : pulSmID  -- the ID of the create semaphore;
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmCreate( VOS_CHAR Sm_Name[4],
                         VOS_UINT32 Sm_Init,
                         VOS_UINT32 Flags,
                         VOS_SEM * Sm_ID )
{
    return( VOS_SmCCreate( Sm_Name, Sm_Init, Flags, Sm_ID ));
}

/**************************************************************************
 Function   : VOS_SmBCreate
 Description: To create a Binary semaphore;
 Input      : acSmName -- the semaphore name, can be null
              Sm_Ini   -- The count number of the semaphore that create;
              ulFlags  -- FIFO or priority;
 Output     : pulSmID  -- the ID of the create semaphore;
 Return     : VOS_OK on success and errno on failure
 **************************************************************************/
VOS_UINT32 VOS_SmBCreate( VOS_CHAR Sm_Name[4],
                          VOS_UINT32 Sm_Init,
                          VOS_UINT32 Flags,
                          VOS_SEM * Sm_ID )
{
    int                    i;
    SEM_CONTROL_BLOCK      *iSemId;
    SEM_ID                 SemId;
    int                    iOptions;
    SEM_B_STATE            init_state;

    if( (Flags & VOS_SEMA4_PRIOR) )
    {
        iOptions = SEM_Q_PRIORITY;
    }
    else
    {
        iOptions = SEM_Q_FIFO;
    }

    if ( Sm_Init >= 1 )
    {
        init_state = SEM_FULL;
    }
    else
    {
        init_state = SEM_EMPTY;
    }

    iSemId = VOS_SemCtrlBlkGet();

    if( iSemId == VOS_MAX_SEM_ID_NULL)
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        return(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
    }

    SemId = semBCreate( iOptions , init_state );

    if(SemId == NULL)
    {
        VOS_SemCtrlBlkFree(iSemId);
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        return(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
    }
    else
    {
        *Sm_ID = (VOS_SEM)iSemId;

        if ( VOS_NULL_PTR != Sm_Name )
        {
            for(i=0; i<VOS_MAX_SEM_NAME_LENGTH/2; i++)
            {
                iSemId->Name[i]  = Sm_Name[i];
            }
            iSemId->Name[VOS_MAX_SEM_NAME_LENGTH/2]  = '\0';
        }
        else
        {
            iSemId->Name[0] = '\0';
        }
        
        iSemId->SemType  = VOS_SEM_TYPE_BINARY;
        iSemId->SemFlags     = (int)Flags;
        iSemId->SemInitCount = (int)Sm_Init;
        iSemId->VxWorksSemId = SemId;

        return(VOS_OK);
    }
}

/*****************************************************************************
 Function   : VOS_SmDelete
 Description: to delete the exiting semaphore according to the ulSmID
 Input      : ulSmID -- ID of semaphore
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmDelete( VOS_SEM Sm_ID )
{
    SEM_CONTROL_BLOCK *temp_Ptr;

    temp_Ptr = (SEM_CONTROL_BLOCK *)Sm_ID;

    if( temp_Ptr == temp_Ptr->SemId )
    {
        if(temp_Ptr->Flag == VOS_SEM_CTRL_BLK_IDLE)
        {
            VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
            return(VOS_ERRNO_SEMA4_CCREATE_INVALID_SMID);
        }

        if ( OK == semDelete(temp_Ptr->VxWorksSemId) )
        {
            return VOS_SemCtrlBlkFree(temp_Ptr);
        }
        else
        {
            VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OSALCREATEERR);
            return(VOS_ERRNO_SEMA4_CCREATE_OSALCREATEERR);
        }
    }
    else
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_INVALID_SMID);
        return(VOS_ERRNO_SEMA4_CCREATE_INVALID_SMID);
    }
}

/*****************************************************************************
 Function   : VOS_SmP
 Description: Lock the resource for synchronization, if the resource is none
              then block, otherwise the number of the resource --
 Input      : ulSmID             -- the ID of the resource to lock
              ulTimeOutInMillSec -- the time to wait(0 for ever)
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmP( VOS_SEM Sm_ID, VOS_UINT32 ulTimeOutInMillSec )
{
    SEM_CONTROL_BLOCK  *temp_Ptr;
    int                iTimeOut;

    temp_Ptr = (SEM_CONTROL_BLOCK *)Sm_ID;

#if (VOS_YES == VOS_CHECK_PARA)
    if( temp_Ptr != temp_Ptr->SemId )
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_P_IDERR);
        return (VOS_ERRNO_SEMA4_P_IDERR);
    }

    if (VOS_SEM_CTRL_BLK_IDLE == temp_Ptr->Flag)
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_P_NOTACTIVE);
        return(VOS_ERRNO_SEMA4_P_NOTACTIVE);
    }
#endif

    iTimeOut = (0 == ulTimeOutInMillSec) ?
        -1 : (int)ulTimeOutInMillSec/MILLISECONDS_PER_TICK;

    if ( OK == semTake( temp_Ptr->VxWorksSemId, iTimeOut ) )
    {
        return(VOS_OK);
    }

    /*lint -e534*/
    Print3("# semTake ID %x Name %s errno %x.\r\n", 
        Sm_ID, temp_Ptr->Name, errno );
    /*lint +e534*/

    if ( S_objLib_OBJ_TIMEOUT == errno )
    {
        VOS_SetErrorNo (VOS_ERRNO_SEMA4_P_TIMEOUT);
        return VOS_ERRNO_SEMA4_P_TIMEOUT;
    }

    VOS_SetErrorNo (VOS_ERRNO_SEMA4_P_CANOTP);
    return VOS_ERRNO_SEMA4_P_CANOTP;

}

/*****************************************************************************
 Function   : VOS_SmV
 Description: Release/Unlock the sema4 that has locked a resource
 Input      : ulSmID -- id of semaphore
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmV( VOS_SEM Sm_ID )
{
    SEM_CONTROL_BLOCK  *temp_Ptr;

    temp_Ptr = (SEM_CONTROL_BLOCK *)Sm_ID;

    if( temp_Ptr == temp_Ptr->SemId )
    {
#if (VOS_YES == VOS_CHECK_PARA)
        if( temp_Ptr->Flag == VOS_SEM_CTRL_BLK_IDLE)
        {
            VOS_SetErrorNo(VOS_ERRNO_SEMA4_V_NOTACTIVE);
            return(VOS_ERRNO_SEMA4_V_NOTACTIVE);
        }
#endif

        if ( OK == semGive( temp_Ptr->VxWorksSemId ) )
        {
            return(VOS_OK);
        }
        else
        {
            /*lint -e534*/
            Print3("# semGive ID %x Name %s errno %x.\r\n", 
                Sm_ID, temp_Ptr->Name, errno );
            /*lint +e534*/

            VOS_SetErrorNo(VOS_ERRNO_SEMA4_V_CANOTV);
            return(VOS_ERRNO_SEMA4_V_CANOTV);
        }
    }
    else
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_V_IDERR);
        return(VOS_ERRNO_SEMA4_V_IDERR);
    }
}

/*****************************************************************************
 Function   : VOS_Sm_AsyP
 Description: to lock the resource asynchronous
 Input      : ulSmID -- ID of semaphore
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_Sm_AsyP( VOS_SEM Sm_ID )
{
    return(VOS_SmP( Sm_ID, 1 ));
}

/*****************************************************************************
 Function   : VOS_show_sem_info
 Description: print the usage info of Sem
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID VOS_show_sem_info( VOS_VOID )
{
    /*lint -e534*/
    vos_printf("Max be used sem is %x.\r\n",vos_SemMaxSemId);
    /*lint +e534*/
}


#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


