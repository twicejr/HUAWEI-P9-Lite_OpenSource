/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: win32_sem.c                                                     */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement win32 semaphore                                    */
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

#include "vos_config.h"
#include "v_sem.h"
#include "stdlib.h"
#include "stdio.h"
#include "v_IO.h"
#include "v_task.h"
#include "v_int.h"


#if (VOS_WIN32 == VOS_OS_VER)


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_V_WIN32_SEM_C

typedef struct SEM_CONTROL_STRU
{
    int                       Flag;/* control block's state */
    struct SEM_CONTROL_STRU   *SemId;/* the ID return to User */
    int                       SemType;/* type of SEM */
    int                       SemFlags;
    int                       SemInitCount;
    char                      Name[VOS_MAX_SEM_NAME_LENGTH];
    HANDLE                    Win32Handle;/* maped Win32 Handle */
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

        VOS_SetErrorNo(VOS_ERRNO_SEMA4_FULL);
        /*lint +e534*/

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
    HANDLE                 pulSemId;

    iSemId = VOS_SemCtrlBlkGet();

    if( iSemId == VOS_MAX_SEM_ID_NULL)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        /*lint +e534*/
        return(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
    }

    if(ulSmInit == 0xFFFFFFFF)
    {
        pulSemId = CreateSemaphore( NULL, (VOS_INT32)1, 1, NULL );
    }
    else
    {
        pulSemId = CreateSemaphore( NULL, (VOS_INT32)ulSmInit, 0x400000, NULL );
    }

    if(pulSemId == NULL)
    {
        VOS_SemCtrlBlkFree(iSemId);
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        /*lint +e534*/
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
        iSemId->Win32Handle  = pulSemId;

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
    HANDLE                 pulSemId;
    VOS_INT32              init_state;

    if ( Sm_Init >= 1 )
    {
        init_state = 1;
    }
    else
    {
        init_state = 0;
    }

    iSemId = VOS_SemCtrlBlkGet();

    if( iSemId == VOS_MAX_SEM_ID_NULL)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        /*lint +e534*/
        return(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
    }

    pulSemId = CreateSemaphore( NULL, init_state,(VOS_INT32) 1, NULL );

    if(pulSemId == NULL)
    {
        VOS_SemCtrlBlkFree(iSemId);
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        /*lint +e534*/
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
        iSemId->Win32Handle = pulSemId;

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
            /*lint -e534*/
            VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
            /*lint +e534*/
            return(VOS_ERRNO_SEMA4_CCREATE_INVALID_SMID);
        }

        if ( 0 != CloseHandle(temp_Ptr->Win32Handle) )
        {
            return VOS_SemCtrlBlkFree(temp_Ptr);
        }
        else
        {
            /*lint -e534*/
            VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OSALCREATEERR);
            /*lint +e534*/
            return(VOS_ERRNO_SEMA4_CCREATE_OSALCREATEERR);
        }
    }
    else
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_INVALID_SMID);
        /*lint +e534*/
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
    VOS_UINT32         TimeOut;
    VOS_UINT32         ulerror;


    temp_Ptr = (SEM_CONTROL_BLOCK *)Sm_ID;

    if( temp_Ptr != temp_Ptr->SemId )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_P_IDERR);
        /*lint +e534*/
        return (VOS_ERRNO_SEMA4_P_IDERR);
    }

    if (VOS_SEM_CTRL_BLK_IDLE == temp_Ptr->Flag)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_P_NOTACTIVE);
        /*lint +e534*/
        return(VOS_ERRNO_SEMA4_P_NOTACTIVE);
    }

    if ( ulTimeOutInMillSec == 0 )
    {
        TimeOut = INFINITE;
    }
    else
    {
        TimeOut = ulTimeOutInMillSec;
    }

    ulerror = WaitForSingleObject( temp_Ptr->Win32Handle, TimeOut );

    if ( WAIT_OBJECT_0 == ulerror )
    {
        return VOS_OK;
    }

    if ( WAIT_TIMEOUT == ulerror )
    {
        /*lint -e534*/
        VOS_SetErrorNo (VOS_ERRNO_SEMA4_P_TIMEOUT);
        /*lint +e534*/
        return VOS_ERRNO_SEMA4_P_TIMEOUT;
    }

    /*lint -e534*/
    VOS_SetErrorNo (VOS_ERRNO_SEMA4_P_CANOTP);
    /*lint +e534*/
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
    VOS_UINT32         ulerror;

    temp_Ptr = (SEM_CONTROL_BLOCK *)Sm_ID;

    if( temp_Ptr == temp_Ptr->SemId )
    {
        if( temp_Ptr->Flag == VOS_SEM_CTRL_BLK_IDLE)
        {
            /*lint -e534*/
            VOS_SetErrorNo(VOS_ERRNO_SEMA4_V_NOTACTIVE);
            /*lint +e534*/
            return(VOS_ERRNO_SEMA4_V_NOTACTIVE);
        }
       
        ulerror = (VOS_UINT32)ReleaseSemaphore( temp_Ptr->Win32Handle, 1, NULL );

        if( 0 == ulerror )
        {
            /*lint -e534*/
            VOS_SetErrorNo(VOS_ERRNO_SEMA4_V_NOTACTIVE);
            /*lint +e534*/
            return(VOS_ERRNO_SEMA4_V_NOTACTIVE);
        }
        else
        {
            return VOS_OK;
        }
    }
    else
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_V_IDERR);
        /*lint +e534*/
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



