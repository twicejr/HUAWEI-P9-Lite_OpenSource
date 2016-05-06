

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: vos_main.c                                                      */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement root function                                      */
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
/* 3. Date: 2007-03-10                                                       */
/*    Author: Xu Cheng                                                       */
/*    Modification: A32D07254                                                */
/*                                                                           */
/*****************************************************************************/

#include "v_typdef.h"
#include "v_root.h"
#include "vos_config.h"
#include "v_IO.h"
#include "v_blkMem.h"
#include "v_queue.h"
#include "v_sem.h"
#include "v_timer.h"
#include "vos_Id.h"
#include "v_int.h"
#include "NVIM_Interface.h"
#include "mdrv.h"

/* LINUX 不支持 */
#if (VOS_VXWORKS== VOS_OS_VER)
#include "stdio.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_VOS_MAIN_C
/*lint +e767 modify:x51137; review:h59254; */

typedef struct
{
    VOS_UINT32 ulStartUpStage;
    VOS_UINT32 ulStep;
    VOS_UINT32 ulOutSideStep;
    VOS_UINT16 usFidInitStep;
    VOS_UINT16 usFidInitId;
    VOS_UINT16 usPidInitStep;
    VOS_UINT16 usPidInitId;
}VOS_START_ERR_STEP_STRU;

extern VOS_UINT32       g_ulOmFidInit ;
extern VOS_UINT32       g_ulOmPidInit ;
extern VOS_UINT32       g_ulVosOutsideStep;
extern VOS_UINT16       g_usFidInitStep;
extern VOS_UINT16       g_usFidInitId;
extern VOS_UINT16       g_usPidInitStep;
extern VOS_UINT16       g_usPidInitId;

extern VOS_UINT32 VOS_OutsideInit(VOS_VOID);

extern VOS_VOID OM_RecordMemInit(VOS_VOID);

VOS_UINT32 vos_StartUpStage = 0x00010000;
VOS_UINT32 g_ulVosStartStep = 0;

HTIMER  g_VosProtectInitTimer = VOS_NULL_PTR;

VOS_UINT32 *g_pulOsaLogTmp;

VOS_VOID V_LogInit(VOS_VOID)
{
#if (VOS_RTOSCK == VOS_OS_VER)
    VOS_UINT32                          ulRecordAddr;

    /* 初始化定位信息 */
    ulRecordAddr = (VOS_UINT32)VOS_EXCH_MEM_MALLOC(VOS_DUMP_MEM_ALL_SIZE);

    if (VOS_NULL_PTR == ulRecordAddr)
    {
        return;
    }

    /* COMM在PID初始化流程会用到部分内容，使用最后的16个UINT32作为记录 */
    g_pulOsaLogTmp  = (VOS_UINT32 *)(ulRecordAddr+(VOS_DUMP_MEM_TOTAL_SIZE-16*sizeof(VOS_UINT32)));

    VOS_MemSet((VOS_VOID *)g_pulOsaLogTmp, 0x5A, 16*sizeof(VOS_UINT32));
#endif
    return;
}

VOS_VOID V_LogRecord(VOS_UINT32 ulIndex, VOS_UINT32 ulValue)
{
#if (VOS_RTOSCK == VOS_OS_VER)
    if (VOS_NULL_PTR == g_pulOsaLogTmp)
    {
        return;
    }

    if (ulIndex >= 16)
    {
        return;
    }

    g_pulOsaLogTmp[ulIndex] = ulValue;
#endif
    return;
}

/*****************************************************************************
 Function   : root
 Description: main function
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID root( VOS_VOID)
{
    /*lint -e534*/
    Print("\n!!!!! VOS_Startup Begin !!!!!\n");
    /*lint +e534*/

#if (VOS_WIN32 == VOS_OS_VER)
    VOS_SplInit();
#endif

    V_LogInit();

#ifndef VOS_SUPPORT_APP_MEM
    if ( VOS_OK != VOS_Startup( VOS_STARTUP_INIT_DOPRA_SOFEWARE_RESOURCE ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase 0: Error.\n");
        /*lint +e534*/
    }
#endif

    if ( VOS_OK != VOS_Startup( VOS_STARTUP_SET_TIME_INTERRUPT ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase 1: Error.\n");
        /*lint +e534*/
    }

    if ( VOS_OK != VOS_Startup( VOS_STARTUP_CREATE_TICK_TASK ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase2: Error.\n");
        /*lint +e534*/
    }

    if( VOS_OK != VOS_Startup( VOS_STARTUP_CREATE_ROOT_TASK ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase 3: Error\n");
        /*lint +e534*/
    }

    if ( VOS_OK != VOS_Startup( VOS_STARTUP_SUSPEND_MAIN_TASK ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase 4: Error\n");
        /*lint +e534*/
    }

    /*lint -e534*/
    Print("\n!!!!! VOS_Startup End !!!!!\n");
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Function   : VOS_ProtectInit
 Description: reboot if OSA can't init
 Calls      :
 Called By  : root
 Input      : None
 Return     : None
 Other      :
 *****************************************************************************/
VOS_VOID VOS_ProtectInit(VOS_UINT32 ulParam1, VOS_UINT32 ulParam2)
{
    VOS_START_ERR_STEP_STRU stStep;

    stStep.ulStartUpStage = vos_StartUpStage;
    stStep.ulStep         = g_ulVosStartStep;
    stStep.ulOutSideStep  = g_ulVosOutsideStep;
    stStep.usFidInitStep  = g_usFidInitStep;
    stStep.usFidInitId    = g_usFidInitId;
    stStep.usPidInitStep  = g_usPidInitStep;
    stStep.usPidInitId    = g_usPidInitId;


    VOS_ProtectionReboot(OSA_EXPIRE_ERROR, 0, 0, (VOS_CHAR *)&stStep, sizeof(VOS_START_ERR_STEP_STRU) );
}

/*****************************************************************************
 Function   : VOS_Startup
 Description: startup function
 Calls      :
 Called By  : root
 Input      : None
 Return     : VOS_OK or VOS_ERROR
 Other      :

日    期   : 2010年12月22日
作    者   : j00174725
修改内容   : 根据问题单号:DTS2010122401828
            由于虚拟USB出现黄色感叹号，将锁任务处理调整到
            创建VOS各FID任务之前，创建完成后解锁，
            在Resume操作前锁任务，在Resume后解锁。

 *****************************************************************************/
VOS_UINT32 VOS_Startup( enum VOS_STARTUP_PHASE ph )
{
    VOS_UINT32      ulReturnValue;
    VOS_UINT32      ulStartUpFailStage = 0;

    switch(ph)
    {
        case VOS_STARTUP_INIT_DOPRA_SOFEWARE_RESOURCE :
            vos_StartUpStage    = 0x00010000;
            V_LogRecord(0, 0x00010000);

            if ( VOS_OK != VOS_MemInit() )
            {
                ulStartUpFailStage |= 0x0001;

                break;
            }

            VOS_SemCtrlBlkInit();

            VOS_QueueCtrlBlkInit();

            VOS_TaskCtrlBlkInit();

            if ( VOS_OK != VOS_TimerCtrlBlkInit() )
            {
                ulStartUpFailStage |= 0x0010;
            }

            OM_RecordMemInit();

            if ( VOS_OK != RTC_TimerCtrlBlkInit() )
            {
                ulStartUpFailStage |= 0x0100;
            }

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
            if ( VOS_OK != VOS_DrxTimerCtrlBlkInit())
            {
                ulStartUpFailStage |= 0x0200;
            }
#endif

            if ( VOS_OK != VOS_PidCtrlBlkInit() )
            {
                ulStartUpFailStage |= 0x0400;
            }

            if ( VOS_OK != VOS_FidCtrlBlkInit() )
            {
                ulStartUpFailStage |= 0x0800;
            }

            if ( VOS_OK != CreateFidsQueque() )
            {
                ulStartUpFailStage |= 0x1000;
            }
            break;

        case VOS_STARTUP_SET_TIME_INTERRUPT:
            vos_StartUpStage = 0x00020000;
            V_LogRecord(0, 0x00020000);
            break;

        case VOS_STARTUP_CREATE_TICK_TASK:
            vos_StartUpStage = 0x00040000;
            V_LogRecord(0, 0x00040000);

            /* create soft timer task */
            if ( VOS_OK != VOS_TimerTaskCreat() )
            {
                ulStartUpFailStage |= 0x0001;
            }

            if ( VOS_OK != RTC_TimerTaskCreat() )
            {
                ulStartUpFailStage |= 0x0002;
            }

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
            if ( VOS_OK != VOS_DrxTimerTaskCreat() )
            {
                ulStartUpFailStage |= 0x0004;
            }
#endif

            break;

        case VOS_STARTUP_CREATE_ROOT_TASK:
            vos_StartUpStage = 0x00080000;
            V_LogRecord(0, 0x00080000);
            /*
            if ( VOS_OK !=
                    VOS_StartCallBackRelTimer(&g_VosProtectInitTimer,
                        DOPRA_PID_TIMER, 20000, 0, 0,
                        VOS_RELTIMER_NOLOOP, VOS_ProtectInit, VOS_TIMER_PRECISION_5) )
            {
                ulStartUpFailStage |= 0x0001;
            }
            */

            g_ulVosStartStep = 0x0000;
            V_LogRecord(1, 0x0000);

            ulReturnValue = VOS_OutsideInit();

            if(VOS_OK != ulReturnValue)
            {
                ulStartUpFailStage |= ulReturnValue;
            }

            g_ulVosStartStep = 0x0008;
            V_LogRecord(1, 0x0008);

            if ( VOS_OK != VOS_FidsInit() )
            {
                ulStartUpFailStage |= 0x0008;
            }

#if (VOS_LINUX != VOS_OS_VER)
            g_ulVosStartStep = 0x0010;
            V_LogRecord(1, 0x0010);

            /* 创建VOS各FID任务之前，锁任务 */
            if ( VOS_OK != VOS_TaskLock() )
            {
                ulStartUpFailStage |= 0x0010;
            }
#endif

            g_ulVosStartStep = 0x0020;
            V_LogRecord(1, 0x0020);

            /* create FID task & selftask task */
            if ( VOS_OK != CreateFidsTask() )
            {
                ulStartUpFailStage |= 0x0020;
            }

#if (VOS_LINUX != VOS_OS_VER)

#if (VOS_WIN32 != VOS_OS_VER)
            g_ulVosStartStep = 0x0040;
            V_LogRecord(1, 0x0040);

            /* suspend FID task & selftask task */
            if ( VOS_OK != VOS_SuspendFidsTask() )
            {
                ulStartUpFailStage |= 0x0040;
            }
#endif

            g_ulVosStartStep = 0x0080;
            V_LogRecord(1, 0x0080);

            /* 创建VOS各FID任务完成后解锁 */
            if ( VOS_OK != VOS_TaskUnlock() )
            {
                ulStartUpFailStage |= 0x0080;
            }
#endif
            g_ulVosStartStep = 0x0100;
            V_LogRecord(1, 0x0100);

            if ( VOS_OK != VOS_PidsInit() )
            {
                ulStartUpFailStage |= 0x0100;
            }
            break;

        case VOS_STARTUP_SUSPEND_MAIN_TASK:
            vos_StartUpStage = 0x00100000;
            V_LogRecord(0, 0x00100000);

#if (VOS_LINUX != VOS_OS_VER)
            g_ulVosStartStep = 0x0001;

            /* Resume任务之前，锁任务 */
            if ( VOS_OK != VOS_TaskLock() )
            {
                ulStartUpFailStage |= 0x0001;
            }

#if (VOS_WIN32 != VOS_OS_VER)

            g_ulVosStartStep = 0x0002;
            V_LogRecord(1, 0x0002);

            /* Resume FID task & selftask task */
            if ( VOS_OK != VOS_ResumeFidsTask() )
            {
                ulStartUpFailStage |= 0x0002;
            }
#endif

            g_ulVosStartStep = 0x0004;
            V_LogRecord(1, 0x0004);

            /* Resume任务之后解锁 */
            if ( VOS_OK != VOS_TaskUnlock() )
            {
                ulStartUpFailStage |= 0x0004;
            }
#endif
            g_ulVosStartStep = 0x0008;
            V_LogRecord(1, 0x0008);

            /* stop protect timer */
            /*VOS_StopRelTimer(&g_VosProtectInitTimer);*/

 #if (OSA_CPU_CCPU == VOS_OSA_CPU)
            /* OSA初始化完成，需要调用DRV函数通知DRV OSA启动完成 */
            if ( VOS_OK != mdrv_sysboot_ok() )
            {
                ulStartUpFailStage |= 0x0008;
            }
#endif

#if (VOS_LINUX == VOS_OS_VER)
            VOS_RunTask();
#endif


            break;

        default:
            break;
    }

    /* calculate return value */
    if( 0 != ulStartUpFailStage )
    {
        ulReturnValue = vos_StartUpStage;
        ulReturnValue |= ulStartUpFailStage;
        /*lint -e534*/
        Print1("startup retuen value is %x.\r\n",ulReturnValue);
        /*lint +e534*/

        /* reboot */
        VOS_ProtectionReboot(OSA_INIT_ERROR, (VOS_INT)ulReturnValue,
            (VOS_INT)g_ulOmPidInit, (VOS_CHAR *)&g_ulOmFidInit, sizeof(VOS_UINT32));

        return(ulReturnValue);
    }
    else
    {
        return(VOS_OK);
    }
}

#if (VOS_LINUX == VOS_OS_VER)

/*****************************************************************************
 Function   : VOS_ModuleInit
 Description:
 Input      :
 Output     :
 Return     :
 *****************************************************************************/
extern VOS_INT RNIC_InitNetCard(VOS_VOID);
extern VOS_INT APP_VCOM_Init(VOS_VOID);


VOS_INT VOS_ModuleInit(VOS_VOID)
{
#if (FEATURE_OFF == FEATURE_DELAY_MODEM_INIT)
    APP_VCOM_Init();
    RNIC_InitNetCard();
#endif

    root();

    return 0;
}

#if (FEATURE_OFF == FEATURE_DELAY_MODEM_INIT)
/*****************************************************************************
 Function   : VOS_ModuleExit
 Description:
 Input      :
 Output     :
 Return     :
 *****************************************************************************/
static VOS_VOID VOS_ModuleExit(VOS_VOID)
{
    return;
}
#endif

#ifndef BOOT_OPTI_BUILDIN
#ifdef FEATURE_FLASH_LESS
#else
/*when flash less on, VOS_ModuleInit should be called by bsp drv.*/
#if (FEATURE_OFF == FEATURE_DELAY_MODEM_INIT)
module_init(VOS_ModuleInit);

module_exit(VOS_ModuleExit);


MODULE_AUTHOR("x51137");

MODULE_DESCRIPTION("Hisilicon OSA");

MODULE_LICENSE("GPL");
#endif

#endif
#endif

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

