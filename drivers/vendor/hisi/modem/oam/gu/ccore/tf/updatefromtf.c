/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: UpdateFromTF.c                                                  */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-06                                                             */
/*                                                                           */
/* Description: It's a flow that be used to control the update from TF card  */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-02                                                          */
/*    Author: Xu cheng                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/
#if 0

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "updatefromtf.h"
#include "NVIM_Interface.h"
#include "mdrv.h"
#include "errorlog.h"
#include "OamSpecTaskDef.h"

/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_UPDATE_FROM_TF_C
/*lint +e767 modify:x51137; review:h59254; */

/* the result of sdmmcMatchVersion which is a routine */
enum
{
    TFVersionMatch,
    TFVersionNotMatch,
    TFVersionMatchExecFail
};

/* the definition of getCdromFlag */
enum
{
    DRV_ISO_NOT_LOAD = 0,
    DRV_ISO_LOAD = 1,
    DRV_ISO_LOAD_BUTT
};


/* the control info of UpdateFromTF module */
struct
{
    VOS_UINT32       ulSem;/* trigger TF's task to run */
    /* record the address of a authentication function
        which is registered by user */
    VOS_ULFUNCPTR    pulFunctionAddress;
}g_stTFControl;

/* the task ID of TF's task */
VOS_UINT32               g_ulTFTaskId;


#define TF_CONFIG_LED_DATA_LEN                       (16*10*2)

#define PS_TURN_ON_UPDATE_VERSION_LED()         DRV_LED_FLUSH(LED_LIGHT_NORMAL_UPDATING)

#define PS_TURN_ON_UPDATE_VERSION_FAIL_LED()    DRV_LED_FLUSH(LED_LIGHT_UPDATE_FAIL)

#define PS_TURN_ON_UPDATE_VERSION_SUCCESS_LED() DRV_LED_FLUSH(LED_LIGHT_UPDATE_SUCCESS)

#define PS_TURN_ON_UPDATE_VERSION_NVFAIL_LED()  DRV_LED_FLUSH(LED_LIGHT_UPDATE_NVFAIL)


/*****************************************************************************
 Function   : TF_RegisterAuthFunc
 Description: register a authentication function
 Input      : the address of function
 Return     : ok or error
 Other      :
 *****************************************************************************/
VOS_UINT32 TF_RegisterAuthFunc( VOS_ULFUNCPTR pulFun )
{
    if ( VOS_NULL_PTR != pulFun )
    {
        g_stTFControl.pulFunctionAddress = pulFun;

        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 Function   : TF_InsertNotify
 Description: register this to lowersoftware.
                This should be called when user insert a TF card.
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID TF_InsertNotify(VOS_VOID)
{
    if ( VOS_OK != VOS_SmV(g_stTFControl.ulSem) )
    {
        /*lint -e534*/
        LogPrint("TF_InsertNotify send sem error.\r\n");
        /*lint +e534*/
    }
}

/*****************************************************************************
 Function   : TF_SDUpdateNotify
 Description: SD卡升级时，NAS通过调用此接口通知OM进行NV备份等操作
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 TF_SDUpdateNotify(VOS_VOID)
{
    if ( VOS_OK != VOS_SmV(g_stTFControl.ulSem) )
    {
        /*lint -e534*/
        LogPrint("TF_InsertNotify send sem error.\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : TF_NVAutoResume
 Description: resume NV
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID TF_NVAutoResume(VOS_VOID)
{
    VOS_INT                             lNVResumeFlag;
    VOS_UINT16                          usNVResumeFlag = VOS_FALSE;
    OAM_MNTN_NV_ERRLOG_EVENT_STRU       stErrLog;

    /* get the flag from DRV */
    lNVResumeFlag = DRV_GET_CDROM_FLAG();

    if ( DRV_ISO_NOT_LOAD == lNVResumeFlag )/* need to do */
    {
        /* clear DRV's flag */
        DRV_SET_CDROM_FLAG(DRV_ISO_LOAD);
    }

    /* Get Flag */
    if ( VOS_OK != NV_Read(en_NV_Resume_Flag,
                    (VOS_VOID *)(&usNVResumeFlag), sizeof(VOS_UINT16)) )
    {
        Print("TF can't read NV resume flag.\r\n");
    }

    if ( VOS_TRUE != usNVResumeFlag )
    {
        return;
    }

    /* light LED updating */
    PS_TURN_ON_UPDATE_VERSION_LED();

    /*lint -e534*/
    VOS_TaskLock();
    /*lint +e534*/

    if ( VOS_FALSE == DRV_BOOT_FORCELOAD_MODE_CHECK() )/* noraml update */
    {
        if ( VOS_OK != NV_RestoreAll() )
        {
            /* light LED.fail. */
            PS_TURN_ON_UPDATE_VERSION_NVFAIL_LED();

            Print("TF can't resume All NV.\r\n");

            DRV_SDMMC_CLEAR_WHOLE_SCREEN();
            DRV_SDMMC_UPDATE_DISPLAY(VOS_FALSE);

            /*lint -e534*/
            VOS_TaskUnlock();
            /*lint +e534*/

            return;
        }
        else
        {
            /* clear flag */
            usNVResumeFlag = VOS_FALSE;

            if ( VOS_OK != NV_Write(en_NV_Resume_Flag,
                            (VOS_VOID *)(&usNVResumeFlag), sizeof(VOS_UINT16)))
            {
                Print("TF can't write NV resume flag.\r\n");
            }

            /* light LED sucess. */
            PS_TURN_ON_UPDATE_VERSION_SUCCESS_LED();

            DRV_SDMMC_CLEAR_WHOLE_SCREEN();
            DRV_SDMMC_UPDATE_DISPLAY(VOS_TRUE);
        }
    }
    else    /* force update */
    {
        if ( VOS_OK != NV_RestoreManufacture() )
        {
            /* light LED.fail. */
            PS_TURN_ON_UPDATE_VERSION_NVFAIL_LED();

            Print("TF can't resume Manufacture NV.\r\n");

            DRV_SDMMC_CLEAR_WHOLE_SCREEN();
            DRV_SDMMC_UPDATE_DISPLAY(VOS_FALSE);

            /*lint -e534*/
            VOS_TaskUnlock();
            /*lint +e534*/

            return;
        }
        else
        {
            /* clear flag */
            usNVResumeFlag = VOS_FALSE;

            if ( VOS_OK != NV_Write(en_NV_Resume_Flag,
                            (VOS_VOID *)(&usNVResumeFlag), sizeof(VOS_UINT16)))
            {
                Print("TF can't write NV resume flag.\r\n");
            }

            /* light LED sucess. */
            PS_TURN_ON_UPDATE_VERSION_SUCCESS_LED();

            DRV_SDMMC_CLEAR_WHOLE_SCREEN();
            DRV_SDMMC_UPDATE_DISPLAY(VOS_TRUE);
        }
    }

    /* NV Backup*/
    if ( VOS_OK != NV_Backup() )
    {
        MNTN_RecordErrorLog(MNTN_OAM_MNTN_NV_ERRLOG_EVENT, (void *)&stErrLog,
                    sizeof(OAM_MNTN_NV_ERRLOG_EVENT_STRU));
    }

    /*lint -e534*/
    VOS_TaskUnlock();
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Function   : TF_ConfigLed
 Description: config LED
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID TF_ConfigLed(VOS_VOID)
{
    VOS_UINT32 ulTempAdress;

    /* get the adress from DRV */
    ulTempAdress= DRV_LED_GET_ADDRESS();

    if ( VOS_OK != NV_Read(en_NV_Item_LED_CONFIG_Data,
                (VOS_VOID *)(ulTempAdress), TF_CONFIG_LED_DATA_LEN) )
    {
        Print("TF can't read NV config LED data.\r\n");
    }

    return;
}

/*****************************************************************************
 Function   : TF_TaskEntry
 Description: entry of the task
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID TF_TaskEntry(VOS_UINT32 ulPara0, VOS_UINT32 ulPara1,
                      VOS_UINT32 ulPara2, VOS_UINT32 ulPara3)
{
    if ( VOS_OK != VOS_SmCCreate( "TF", 0, VOS_SEMA4_FIFO, &(g_stTFControl.ulSem)))
    {
        Print("TF: creat sem error.\r\n");

        return;
    }

    if(VOS_OK != DRV_SDMMC_ADD_HOOK( 0, (VOS_VOID *)TF_InsertNotify))
    {
        Print("TF: register hook to lowersoftware error.\r\n");

        return;
    }

    TF_ConfigLed();

    TF_NVAutoResume();

    DRV_ONLINE_UPDATE_RESULT();

    /* main loop */
    for ( ; ;  )
    {
        if ( VOS_OK != VOS_SmP(g_stTFControl.ulSem, 0) )
        {
            continue;
        }

        /* light LED updating */
        PS_TURN_ON_UPDATE_VERSION_LED();

        /*lint -e746 修改人:徐铖 51137 ;检视人:蒋开波 00105005;
            原因:该告警是因为OSA的VOS_ULFUNCPTR原型定义时没有在形参中加入void */
        /* AUTH */
        if ( VOS_NULL_PTR != g_stTFControl.pulFunctionAddress )
        {
            if ( VOS_OK != g_stTFControl.pulFunctionAddress() )
            {
                /* light LED fail to update */
                PS_TURN_ON_UPDATE_VERSION_FAIL_LED();

                Print("TF AUTH fail.\r\n");

                continue;
            }
        }

        /*lint +e746 修改人:徐铖 51137; 检视人:蒋开波 00105005;*/
        if(VOS_TRUE == DRV_TF_NVBACKUP_FLAG())
        {
            /* NV Backup*/
            if ( VOS_OK != NV_Backup() )
            {
                /* light LED fail to update */
                PS_TURN_ON_UPDATE_VERSION_FAIL_LED();

                Print("TF backup fail.\r\n");

                continue;
            }
        }

        /*set the flag of update */
        DRV_SET_UPDATA_FLAG(0);

        /* reboot */
        VOS_FlowReboot();
    }
}

/*****************************************************************************
 Function   : TF_TaskCreat
 Description: create TF's task
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID TF_TaskCreat(VOS_VOID)
{
    VOS_UINT32 Arguments[4] = {0,0,0,0};

    if ( VOS_OK != VOS_CreateTask( "TF_TASK", &g_ulTFTaskId, TF_TaskEntry,
                            TF_TASK_PRI, TF_TASK_STACK_SIZE, Arguments) )
    {
        Print("TF create task error.\r\n");
    }
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif


