/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r30nkS2SsvIFwRmXhHfeUjmTtq/07bn/XrwhnjAzNXer3X/rkTN8G+HC8LNOlT+FWIGCc
oUyIvcGmaVaSxFTfiJCSbmtILorZ4JMdQeueZGrznQYufBMfUiKz2cJZgbsyow==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************
*
* Copyright (c) 2007 HUAWEI - All Rights Reserved
*
* File: $vfmw_ctrl.c$
* Date: $2009/04/22$
* Revision: $v1.0$
* Purpose: VFMW的解码控制，核心是解码线程的管理，包括
*          1. SCD,VDM等中断驱动IP的唤醒
*          2. 多通道调度
*          3. 解码的／启动／停止／关闭
*
* Change History:
*
* Date                       Author                          Change
* ====                       ======                          ======
* 2009/04/22                 z56361                          Original
*
*
* Dependencies:
* Linux OS
*
************************************************************************/

#include "basedef.h"
#include "mem_manage.h"
#include "public.h"
#include "vfmw_ctrl.h"
#include "vdm_drv.h"
#ifdef VFMW_VC1_SUPPORT
#include "bitplane.h"
#endif
#ifdef HIVDEC_SMMU_SUPPORT
#include "smmu.h"
#endif

/*======================================================================*/
/*   外部全局变量                                                              */
/*======================================================================*/
extern SM_IIS_S    s_SmIIS;
extern FSP_INST_S* s_pFspInst[MAX_CHAN_NUM];
DSP_STATE_E   g_DSPState[MAX_CHAN_NUM] = {0};
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
extern SINT32 g_TunnelLineNumber;
#endif

/*======================================================================*/
/*   常数                                                               */
/*======================================================================*/
#ifndef IRQ_HANDLED
#define IRQ_HANDLED                 (1)
#endif

#ifndef IRQF_DISABLED
#define IRQF_DISABLED               (0x00000020)
#endif

#define CHAN_CTX_MEM_SIZE  (sizeof(VFMW_CHAN_S)+2048+sizeof(VDEC_USRDAT_POOL_S))
#define CHAN_CTX_MEM_BEFORE_USRDAT  (sizeof(VFMW_CHAN_S)+2048)

#define BPD_SIZE                    (2048 * 7 + 512)  // 因为TV这边要求首地址是256/512对齐，所以这里增大512byte  l00232354
#define VP8_SEGID_SIZE              (32 * 1024)
#define MAX_VID_PROTOCOL_NAME       (20)

#define MAX_STOP_WAIT_COUNT         (100)
#define MAX_FPGA_STOP_WAIT_COUNT    (1000)

/*======================================================================*/
/*  宏                                                                  */
/*======================================================================*/
#define  DO_OPEN_DRV_ERR()                                  \
do {                                                        \
    memset( pstMem, 0, sizeof(MEM_RECORD_S) );              \
    VCTRL_CloseDrivers(pstDrvMem);                                \
    return VCTRL_ERR;                                       \
} while(0)

#define  VCTRL_ASSERT_RET( cond, else_print )               \
do {                                                            \
    if( !(cond) )                                               \
    {                                                           \
        dprint(PRN_FATAL,"vfmw_ctrl.c,L%d: %s\n", __LINE__, else_print ); \
        return VCTRL_ERR;                                       \
    }                                                           \
}while(0)

#define  VCTRL_ASSERT( cond, else_print )                   \
do {                                                            \
    if( !(cond) )                                               \
    {                                                           \
        dprint(PRN_FATAL,"vfmw_ctrl.c,L%d: %s\n", __LINE__, else_print ); \
        return;                                                 \
    }                                                           \
}while(0)

#define CHECK_FUNC(func,name)\
do {\
    if (func == NULL)\
    {\
        dprint(PRN_FATAL, "register soft decoder fail: '%s' can not be NULL\n", name);\
        return VDEC_ERR;\
    }\
}while(0)

#define IS_SOFT_DEC(eVidStd) (((eVidStd==VFMW_VP6 || eVidStd==VFMW_VP6F || eVidStd==VFMW_VP6A) && (0 == (g_VdmCharacter & VDM_SUPPORT_VP6)))\
                            || eVidStd==VFMW_H263 || eVidStd==VFMW_SORENSON)

#define TIME_PERIOD(begin, end) ((end >= begin)? (end-begin):(0xffffffff - begin + end))

/*======================================================================*/
/*  模块内共享数据                                                      */
/*======================================================================*/
/* 解码器控制数据 */
static VFMW_CTRL_DATA_S s_VfmwCTrl;

EXT_FN_EVENT_CALLBACK g_event_report;

/* 通道描述信息集 */
VFMW_CHAN_S       *s_pstVfmwChan[MAX_CHAN_NUM];

VFMW_CHAN_STAT_S   g_VfmwChanStat[MAX_CHAN_NUM];
VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
static VFMW_CHANNEL_CONTROL_STATE_E s_ChanControlState[MAX_CHAN_NUM];

/* 在某些特殊应用场景下需要扩展参考帧个数和显示帧个数, 通过insmod的参数实现 */
SINT32        extra_ref = 0;
SINT32        extra_disp = 0;
UINT32        extra_cmd = 0;                    /* 外部控制比特位，bit0: 是否解I 帧后B 帧
                                                             bit1: 高清是否支持16MV
                                                             bit2: H264整帧修补控制
                                                             bit3: 是否支持苹果电脑Airplay-Mirroring发过来的码流*/
                                                                 
SINT32        g_SleepTime = 0;
SINT32        g_StopDec = 0;
SINT8         g_RepairDisable = 0;

UINT8         g_allow_B_before_P = 0;
UINT8         g_not_direct_8x8_inference_flag = 1;
UINT8         g_not_allow_H264FullPictureRepair_flag = 0;
UINT8         g_allow_ClearDPB_after_RepairListErr_flag = 0;
UINT8         g_apple_airplay_mirrorinig_flag = 0; /* 仅在DPT产品上支持苹果电脑Airplay-Mirroring发过来的视频码流 */

SINT32        g_CurProcChan = FIRST_CHAN_NUM;
SINT32        g_VdmCharacter = 0;
UINT32        g_u32DFSMaxAllocTime = 0;
UINT32        g_ResetCreateNewSave = 0;
VDM_VERSION_E g_eVdmVersion;

UINT32        save_str_chan_num = 0;
UINT32        save_seg_chan_num = 0;
SINT32        save_yuv_chan_num = -1;
SINT32        save_yuv_with_crop = 0;
UINT8        *pY,*pUl,*pVl;
OSAL_FILE    *vfmw_save_str_file = NULL;
OSAL_FILE    *vfmw_save_seg_file = NULL;
OSAL_FILE    *vfmw_save_yuv_file = NULL;
MEM_RECORD_S  MemRecord_YUV;
SINT8         s_VfmwSavePath[64] = {'/','m','n','t',0};

/*======================================================================*/
/*  函数声明                                                            */
/*======================================================================*/
SINT32 VCTRL_Vfmw_Thread(VOID *p_temp);
SINT32 VCTRL_CalcActualCrc(VID_STD_E eVidStd, IMAGE *pImage);


/*======================================================================*/
/*  函数实现                                                            */
/*======================================================================*/

/* 休眠 */
VOID VCTRL_Suspend(VOID)
{
    UINT8  isScdSleep=0, isVdmSleep=0;
    UINT32 j;
    UINT32 SleepCount=0;
    UINT32 BeginTime, EntrTime, CurTime;

    EntrTime = VFMW_OSAL_GetTimeInMs();

    // 清除扣脉冲设置
    VDMDRV_ResetClock();

    // 设置SCD休眠
    SCDDRV_PrepareSleep();

    // 设置VDM休眠
    for (j=0; j<MAX_VDH_NUM; j++)
    {
        VDMDRV_PrepareSleep(j);
    }

    // 检测休眠状态
    BeginTime = VFMW_OSAL_GetTimeInMs();
    do
    {
        if (SCDDRV_SLEEP_STAGE_SLEEP == SCDDRV_GetSleepStage())
        {
            isScdSleep = 1;
        }

        for (j=0; j<MAX_VDH_NUM; j++)
        {
            if (VDMDRV_GetSleepStage(j) != VDMDRV_SLEEP_STAGE_SLEEP)
            {
                break;
            }
            if (j == MAX_VDH_NUM-1)
            {
                isVdmSleep = 1;
            }
        }

        if (1==isScdSleep && 1==isVdmSleep)
        {
            break;
        }
        else
        {
            if (SleepCount > 30)
            {
                CurTime = VFMW_OSAL_GetTimeInMs();
                dprint(PRN_FATAL,"Wait sleep time out %d ms (isScdSleep=%d, isVdmSleep=%d)!\n", TIME_PERIOD(BeginTime, CurTime), isScdSleep, isVdmSleep);
                if (isScdSleep != 1)
                {
                    dprint(PRN_FATAL,"Force scd sleep.\n");
                    SCDDRV_ForceSleep();
                }
                if(isVdmSleep != 1)
                {
                    for (j=0; j<MAX_VDH_NUM; j++)
                    {
                        dprint(PRN_FATAL,"Force vdm %d sleep.\n", j);
                        VDMDRV_ForceSleep(j);
                    }
                }
                break;
            }

            VFMW_OSAL_mSleep(10);
            SleepCount++;
        }
    }while(isScdSleep!=1 || isVdmSleep!=1);

    // 休眠完成后处理
    SCDDRV_CloseHardware();
    for (j=0; j<MAX_VDH_NUM; j++)
    {
        VDMDRV_CloseHardware(j);
    }

    // 设置线程休眠
    VCTRL_StopTask();

    CurTime = VFMW_OSAL_GetTimeInMs();
    dprint(PRN_FATAL,"Vfmw suspend totally take %d ms\n", TIME_PERIOD(EntrTime, CurTime));

    return;
}

/* 唤醒 */
VOID VCTRL_Resume(VOID)
{
    SINT32 j;
    UINT32 EntrTime, CurTime;

    EntrTime = VFMW_OSAL_GetTimeInMs();
#ifdef HIVDEC_SMMU_SUPPORT
    //SMMU reinit global regs
    SMMU_InitGlobalReg();
#endif

    // 唤醒SCD
    SCDDRV_ExitSleep();

    // 唤醒VDM
    for (j=0; j<MAX_VDH_NUM; j++)
    {
        VDMDRV_ExitSleep(j);
    }

    // 唤醒Task
    VCTRL_StartTask();

    CurTime = VFMW_OSAL_GetTimeInMs();
    dprint(PRN_FATAL,"Vfmw resume totally take %d ms\n", TIME_PERIOD(EntrTime, CurTime));

    return;
}

VOID VCTRL_ChanCtx_Init(VOID)
{
    SINT32 i;
    SINT32 *pPriorTab = g_ChanCtx.ChanIdTabByPrior;

    memset(&g_ChanCtx, 0, sizeof(CHAN_CTX));
    for (i=0; i<MAX_CHAN_NUM; i++)
    {
        pPriorTab[i] = -1;
    }
    return;
}

SINT32 VCTRL_Mfde_Isr_0(SINT32 irq, VOID *dev_id)
{
    VDMDRV_VdmIntServProc(0);

    return IRQ_HANDLED;
}

SINT32 VCTRL_Scd_Isr(SINT32 irq, VOID *dev_id)
{
    SM_SCDIntServeProc();

    return IRQ_HANDLED;
}

SINT32 VCTRL_Smmu_Isr(SINT32 irq, VOID *dev_id)
{
    SMMU_IntServProc();

    return IRQ_HANDLED;
}

/***********************************************************************
   VCTRL_InformVdmFree(): 知会VCTRL VDM已经空闲，等待VCTRL解码新的DecParam
 ***********************************************************************/
VOID VCTRL_InformVdmFree(SINT32 ChanID)
{
    static UINT32 LastEventTime = 0;
    UINT32 CurTime = VFMW_OSAL_GetTimeInMs();
    UINT32  Period;

    if (CurTime > LastEventTime)
    {
        Period = CurTime - LastEventTime;
    }
    else
    {
        Period = 10;
        LastEventTime = CurTime;
    }
    if (Period >= 10)
    {
        VFMW_OSAL_GiveEvent(G_INTEVENT);
        LastEventTime = CurTime;
    }

    return;
}


/*********************************************************************************************
   VCTRL_SetMoreGapEnable(): 设置当前通道是否支持多GAP应用
 *********************************************************************************************/
SINT32 VCTRL_SetMoreGapEnable(SINT32 ChanID, SINT32 MoreGapEnable)
{
    VCTRL_ASSERT_RET( ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "Chan inactive");
    VCTRL_ASSERT_RET( 1==s_pstVfmwChan[ChanID]->s32IsOpen, "can NOT config a not-opened Chan");

    if ((MoreGapEnable==0) || (MoreGapEnable==1))
    {
        s_pstVfmwChan[ChanID]->stSynExtraData.s32MoreGapEnable = MoreGapEnable;
    }
    else
    {
        s_pstVfmwChan[ChanID]->stSynExtraData.s32MoreGapEnable = 0;
        return VCTRL_ERR;
    }

    return VCTRL_OK;
}

SINT32 VCTRL_EventReport(SINT32 ChanID, SINT32 type, VOID *p_args, UINT32 len)
{
    SINT32 ret = VCTRL_ERR;
    VDEC_ADAPTER_TYPE_E eType;

    VCTRL_ASSERT_RET(ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET(NULL != s_pstVfmwChan[ChanID], "Chan inactive");

    eType = s_pstVfmwChan[ChanID]->eAdapterType;
    switch(eType)
    {
        case ADAPTER_TYPE_VDEC:
            if (NULL == s_VfmwCTrl.pfnEventReport_Vdec)
            {
                dprint(PRN_FATAL, "s_VfmwCTrl.event_report_vdec = NULL\n");
            }
            else
            {
                ret = (s_VfmwCTrl.pfnEventReport_Vdec)(ChanID, type, p_args, len);
            }
            break;
        case ADAPTER_TYPE_OMXVDEC:
            if (NULL == s_VfmwCTrl.pfnEventReport_OmxVdec)
            {
                dprint(PRN_FATAL, "s_VfmwCTrl.event_report_omxvdec = NULL\n");
            }
            else
            {
                ret = (s_VfmwCTrl.pfnEventReport_OmxVdec)(ChanID, type, p_args, len);
            }
            break;
        default:
            dprint(PRN_FATAL, "%s Unkown Adapter Type: %d, Len: %d\n", __func__, eType, len);
            break;
    }

    return ret;
}

inline VOID VCTRL_PowerOn(VOID)
{
    if (s_VfmwCTrl.pfnPowerON != NULL)
    {
        (s_VfmwCTrl.pfnPowerON)();
    }
    else
    {
        dprint(PRN_FATAL, "s_VfmwCTrl.pfnPowerON = NULL\n");
    }
}

inline VOID VCTRL_PowerOff(VOID)
{
    if (s_VfmwCTrl.pfnPowerOFF != NULL)
    {
        (s_VfmwCTrl.pfnPowerOFF)();
    }
    else
    {
        dprint(PRN_FATAL, "s_VfmwCTrl.pfnPowerOFF = NULL\n");
    }
}

SINT32 VCTRL_SetCallBack(VDEC_ADAPTER_TYPE_E type, INIT_INTF_S *pIntf)
{        
    FSP_OMX_INTF_S FspIntf;
    
    VCTRL_ASSERT_RET(pIntf != NULL, "pIntf null!");
    VCTRL_ASSERT_RET(type < ADAPTER_TYPE_BUTT, "type invalid!");

    if (ADAPTER_TYPE_VDEC == type)
    {
        s_VfmwCTrl.pfnEventReport_Vdec    = pIntf->event_handler;
    }
    else
    {
        s_VfmwCTrl.pfnEventReport_OmxVdec = pIntf->event_handler;
    }
    
    s_VfmwCTrl.pfnPowerON  = pIntf->power_on;
    s_VfmwCTrl.pfnPowerOFF = pIntf->power_off;

    memset(&FspIntf, 0, sizeof(FSP_OMX_INTF_S));
    FspIntf.pfnBufferHandler = pIntf->buffer_handler;
    FSP_SetOMXInterface(&FspIntf);

    return VCTRL_OK;
}

#ifdef COMMAND_LINE_EXTRA
#define COMMAND_LINE_BYTE_SIZE 1024
static SINT8 cmdline[COMMAND_LINE_BYTE_SIZE];
static SINT32 VCTRL_GetExtraRefFrmNum(VOID)
{
    SINT8 *s;
    SINT8 *p = NULL;
    strlcpy(cmdline, saved_command_line, COMMAND_LINE_SIZE);
    p = strstr(cmdline, "extra_ref=");
    if (p)
    {
        s = strsep((char **)&p, "=");
        if (s)
        {
            s = strsep((char **)&p, " ");
            if (NULL == s)
            {
                dprint(PRN_DBG, "fuction return value is null,%s %d unknow error!!\n",__FUNCTION__,__LINE__);
                return 0 ;
            }
            extra_ref = simple_strtol(s, NULL, 0);
        }
        else
        {
            extra_ref = 0;
        }
    }
    if (extra_ref < -5000 || extra_ref > 5000)
    {
        dprint(PRN_ALWS, "ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\n",extra_ref);
    }
    extra_ref = CLIP3(-5000, 5000, extra_ref);
    
    return 0;
}

static SINT32 VCTRL_GetExtraDispFrmNum(VOID)
{
    SINT8 *s;
    SINT8 *p = NULL;

    strlcpy(cmdline, saved_command_line, COMMAND_LINE_SIZE);
    p = strstr(cmdline, "extra_disp=");
    if (p)
    {
        s = strsep((char **)&p, "=");
        if (s)
        {
            s = strsep((char **)&p, " ");
            if (NULL == s)
            {
                dprint(PRN_DBG, "fuction return value is null,%s %d unknow error!!\n",__FUNCTION__,__LINE__);
                return 0 ;
            }
            extra_disp = simple_strtol(s, NULL, 0);
        }
        else
        {
            extra_disp = 0;
        }
    }
    if (extra_disp < -5000 || extra_disp > 5000)
    {
        dprint(PRN_ALWS, "ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\n",extra_disp);
    }
    extra_disp = CLIP3(-5000, 5000, extra_disp);
    
    return 0;
}

static SINT32 VCTRL_GetExtraCtrlCmd(VOID)
{
    SINT8 *s;
    SINT8 *p = NULL;

    if (extra_cmd != 0)
    {
        g_allow_B_before_P = (extra_cmd&1);
        g_not_direct_8x8_inference_flag = (extra_cmd>>1)&1;
		g_not_allow_H264FullPictureRepair_flag = (extra_cmd>>2)&1;
        g_apple_airplay_mirrorinig_flag = (extra_cmd>>3)&1;
        g_allow_ClearDPB_after_RepairListErr_flag = (extra_cmd >> 4) & 1;
    }
    else
    {
        strlcpy(cmdline, saved_command_line, COMMAND_LINE_SIZE);

        p = strstr(cmdline, "extra_cmd=");
        if (p)
        {
            s = strsep((char **)&p, "=");
            if (s)
            {
                s = strsep((char **)&p, " ");
                if (NULL == s)
                {
                    dprint(PRN_DBG, "fuction return value is null,%s %d unknow error!!\n",__FUNCTION__,__LINE__);
                    return 0 ;
                }
                extra_cmd = simple_strtol(s, NULL, 0);
            }

            g_allow_B_before_P = (extra_cmd&1);
            g_not_direct_8x8_inference_flag = (extra_cmd>>1)&1;
			g_not_allow_H264FullPictureRepair_flag = (extra_cmd>>2)&1;
            g_apple_airplay_mirrorinig_flag = (extra_cmd>>3)&1;
            g_allow_ClearDPB_after_RepairListErr_flag = (extra_cmd >> 4) & 1;
        }
    }
    return 0;
}
#endif


/***********************************************************************
   VCTRL_StartVfmw: VCTRL全局启动，解码线程进入运行状态
 ***********************************************************************/
SINT32 VCTRL_StartTask(VOID)
{
    SINT32 i;
    SINT32 ret = VCTRL_ERR;

    if( 1 != s_VfmwCTrl.s32IsVCTRLOpen )
    {
        return VCTRL_ERR;
    }

    /* 发出“启动指令” */
    s_VfmwCTrl.eTaskCommand = TASK_CMD_START;

    /* 等待VCTRL进入运行状态 */
    for( i=0; i<50; i++ )
    {
        if( TASK_STATE_RUNNING == s_VfmwCTrl.eTaskState )
        {
            ret = VCTRL_OK;
            break;
        }
        else
        {
            VFMW_OSAL_mSleep(10);
        }
    }

    /* 取消指令 */
    s_VfmwCTrl.eTaskCommand = TASK_CMD_NONE;

    return ret;
}

/***********************************************************************
   VCTRL_StopVfmw: VCTRL全局停止，解码线程进入空转状态
 ***********************************************************************/
SINT32 VCTRL_StopTask(VOID)
{
    SINT32 i;
    SINT32 ret = VCTRL_ERR;

    if( 1 != s_VfmwCTrl.s32IsVCTRLOpen )
    {
        return VCTRL_ERR;
    }

    /* 发出停止指令 */
    s_VfmwCTrl.eTaskCommand = TASK_CMD_STOP;

    /* 等待VCTRL进入停止状态 */
    for( i=0; i<50; i++ )
    {
        if( TASK_STATE_STOP == s_VfmwCTrl.eTaskState )
        {
            ret = VCTRL_OK;
            break;
        }
        else
        {
            VFMW_OSAL_mSleep(10);
        }
    }

    /* 取消指令 */
    s_VfmwCTrl.eTaskCommand = TASK_CMD_NONE;

    return ret;
}

/***********************************************************************
   打开硬件驱动程序: 为各硬件IP驱动程序分配资源，打开各驱动程序
 ***********************************************************************/
SINT32 VCTRL_OpenDrivers(DRV_MEM_S *pstDrvMem)
{
    MEM_RECORD_S *pstMem;
    SINT32  i = 0;
    SINT32  Size = 0;
    SINT32  ExtUsedLen = 0;
    SINT8   string[20];
    VDMHAL_OPENPARAM_S VDMOpenParam;
    SCD_OPEN_PARAM_S SCDOpenParam;
    
    /* 映射解码器寄存器 */
    pstMem = &pstDrvMem->stVdhReg;
    if( MEM_MAN_OK == MEM_MapRegisterAddr( gVdhRegBaseAddr, 64*1024, pstMem ) )
    {
        MEM_AddMemRecord(pstMem->PhyAddr, pstMem->VirAddr, pstMem->Length);
    }
    else
    {
        dprint(PRN_FATAL, "Map vdh register failed! gVdhRegBaseAddr = 0x%x, gVdhRegRange = %d\n", gVdhRegBaseAddr, gVdhRegRange);
        DO_OPEN_DRV_ERR();
    }
    
    /* VDM公共内存 */
    Size = VDMHAL_GetHalMemSize();
    if (Size <= 0)
    {
        dprint(PRN_FATAL, "VDMHAL_GetHalMemSize failed!\n");
        DO_OPEN_DRV_ERR();
    }
    for (i=0; i<MAX_VDH_NUM; i++)
    {
        pstMem = &pstDrvMem->stVdmHalMem[i];
        if (0 == pstDrvMem->stExtHalMem.Length)
        {
            /* 为VDM申请内存 */
            snprintf(string, sizeof(string), "HAL_%d", i);
            if( MEM_AllocMemBlock(string, Size, pstMem, 0) != MEM_MAN_OK )
            {
                dprint(PRN_FATAL, "MEM_AllocMemBlock vdh %d hal failed!\n", i);
                DO_OPEN_DRV_ERR();
            }
        }
        else
        {
            /* 为VDM分配外部内存 */
            pstMem->IsSecMem = pstDrvMem->stExtHalMem.IsSecMem;
            pstMem->PhyAddr  = pstDrvMem->stExtHalMem.PhyAddr + ExtUsedLen;
            pstMem->VirAddr  = pstDrvMem->stExtHalMem.VirAddr + ExtUsedLen;
            pstMem->Length   = Size;
            ExtUsedLen      += Size;
            if (ExtUsedLen > pstDrvMem->stExtHalMem.Length)
            {
                dprint(PRN_FATAL, "Vdm use ext hal mem failed! NeedLen %d > ExtLen %d\n", ExtUsedLen, pstDrvMem->stExtHalMem.Length);
                DO_OPEN_DRV_ERR();
            }
        }
        MEM_AddMemRecord(pstMem->PhyAddr, pstMem->VirAddr, pstMem->Length);
        
        memset(&VDMOpenParam, 0, sizeof(VDMHAL_OPENPARAM_S));
        VDMOpenParam.MemBaseAddr = pstMem->PhyAddr;
        VDMOpenParam.Size        = pstMem->Length;
        VDMOpenParam.VdhId       = i;
        if (VDMHAL_OK != VDMHAL_OpenHAL(&VDMOpenParam))
        {
            dprint(PRN_FATAL, "Vdm %d open hal failed!\n", i);
            DO_OPEN_DRV_ERR();
        }
        VDMDRV_Init(i);
    }

    /* SCD公共内存 */
    Size = SCD_MSG_BUFFER;
    pstMem = &pstDrvMem->stScdCmnMem;
    if (0 == pstDrvMem->stExtHalMem.Length)
    {
        /* 为SCD申请公共内存 */
        if( MEM_AllocMemBlock("SCD_MSG", Size, pstMem, 0) != MEM_MAN_OK )
        {
            dprint(PRN_FATAL, "MEM_AllocMemBlock scd msg failed!\n");
            DO_OPEN_DRV_ERR();
        }
    }
    else
    {
        /* 为SCD分配外部内存 */
        pstMem->IsSecMem = pstDrvMem->stExtHalMem.IsSecMem;
        pstMem->PhyAddr  = pstDrvMem->stExtHalMem.PhyAddr + ExtUsedLen;
        pstMem->VirAddr  = pstDrvMem->stExtHalMem.VirAddr + ExtUsedLen;
        pstMem->Length   = Size;
        ExtUsedLen      += Size;
        if (ExtUsedLen > pstDrvMem->stExtHalMem.Length)
        {
            dprint(PRN_FATAL, "Scd use ext hal mem failed! NeedLen %d > ExtLen %d\n", ExtUsedLen, pstDrvMem->stExtHalMem.Length);
            DO_OPEN_DRV_ERR();
        }
    }
    MEM_AddMemRecord(pstMem->PhyAddr, pstMem->VirAddr, pstMem->Length);
    
    memset(&SCDOpenParam, 0, sizeof(SCD_OPEN_PARAM_S));
    SCDOpenParam.MemAddr = pstMem->PhyAddr;
    SCDOpenParam.MemSize = pstMem->Length;
    if(FMW_OK != SM_OpenSCDDrv(&SCDOpenParam))
    {
        dprint(PRN_FATAL, "SM_OpenSCDDrv failed!\n");
        DO_OPEN_DRV_ERR();
    }

#ifdef HIVDEC_SMMU_SUPPORT
    //初始化smmu master和common寄存器
    if ( SMMU_OK != SMMU_Init() )
    {
        dprint(PRN_FATAL, "SMMU_Init failed!\n");
        DO_OPEN_DRV_ERR();
    }
#endif

    /* 注册VDM中断服务程序 */
#if !defined(VDM_BUSY_WAITTING)
    if (VFMW_OSAL_RequestIrq(gMfdeIrqNum, VCTRL_Mfde_Isr_0, IRQF_DISABLED, "vfmw_vdh_irq", NULL) != 0)//for 2.6.24以后
    {
        dprint(PRN_FATAL, "Request mfde irq failed!\n");
        DO_OPEN_DRV_ERR();
    }
#endif
#if !defined(SCD_BUSY_WAITTING)
    if (VFMW_OSAL_RequestIrq(gScdIrqNum, VCTRL_Scd_Isr, IRQF_DISABLED, "vfmw_scd_irq", NULL) != 0)//for 2.6.24以后
    {
        dprint(PRN_FATAL, "Request scd irq failed!\n");
        DO_OPEN_DRV_ERR();
    }
#endif
#ifdef HIVDEC_SMMU_SUPPORT
#if !defined(SMMU_BUSY_WAITTING)
        if (VFMW_OSAL_RequestIrq(gSmmuIrqNum, VCTRL_Smmu_Isr, IRQF_DISABLED, "vfmw_smmu_irq", NULL) != 0)//for 2.6.24以后
        {
            dprint(PRN_FATAL, "Request smmu irq failed!\n");
            DO_OPEN_DRV_ERR();
        }
#endif
#endif

    /* 全局复位 */
    VDMHAL_GlbReset();

    /* EMAR_ID 设置默认值 */
    VDMHAL_WriteScdEMARID();

    return VCTRL_OK;
}

/***********************************************************************
   关闭硬件驱动程序
 ***********************************************************************/
SINT32 VCTRL_CloseDrivers(DRV_MEM_S *pstDrvMem)
{
    SINT32 i;
    MEM_RECORD_S *pstMem;

    /* 关闭各个IP的驱动程序并且释放存储资源 */
    for (i=0; i<MAX_VDH_NUM; i++)
    {
        VDMHAL_CloseHAL(i);
        pstMem = &pstDrvMem->stVdmHalMem[i];
        if (0 == pstDrvMem->stExtHalMem.Length)
        {
            if( 0 != pstMem->Length )
            {
                MEM_ReleaseMemBlock(pstMem->PhyAddr, pstMem->VirAddr);
                memset(pstMem, 0, sizeof(MEM_RECORD_S));
            }
        }
        MEM_DelMemRecord(pstMem->PhyAddr, pstMem->VirAddr, pstMem->Length);
    }
    
    SM_CloseSCDDrv();
    pstMem = &pstDrvMem->stScdCmnMem;
    if (0 == pstDrvMem->stExtHalMem.Length)
    {
        if( 0 != pstMem->Length )
        {
            MEM_ReleaseMemBlock(pstMem->PhyAddr, pstMem->VirAddr);
            memset(pstMem, 0, sizeof(MEM_RECORD_S));
        }
    }
    MEM_DelMemRecord(pstMem->PhyAddr, pstMem->VirAddr, pstMem->Length);

    /* 去映射解码器寄存器 */
    pstMem = &pstDrvMem->stVdhReg;
    if( 0 != pstMem->Length )
    {
        MEM_UnmapRegisterAddr(pstMem->PhyAddr, pstMem->VirAddr);
        memset(pstMem, 0, sizeof(MEM_RECORD_S));
    }
    MEM_DelMemRecord(pstMem->PhyAddr, pstMem->VirAddr, pstMem->Length);

    /* 销毁VDM中断服务程序 */
#if !defined(VDM_BUSY_WAITTING)
    VFMW_OSAL_FreeIrq(gMfdeIrqNum, NULL);
#endif
#if !defined(SCD_BUSY_WAITTING)
    VFMW_OSAL_FreeIrq(gScdIrqNum, NULL);
#endif

#ifdef HIVDEC_SMMU_SUPPORT
#if !defined(SMMU_BUSY_WAITTING)
    VFMW_OSAL_FreeIrq(gSmmuIrqNum, NULL);
#endif
    SMMU_DeInit();
#endif

    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_OpenVfmw: VCTRL全局打开，主要是清除静态信息，以及创建解码线程
 ***********************************************************************/
SINT32 VCTRL_OpenVfmw(VDEC_OPERATION_S *pArgs)
{
    MEM_INIT_S MemInit;
    memset(&MemInit, 0, sizeof(MEM_INIT_S));

    if( 0 != s_VfmwCTrl.s32IsVCTRLOpen )
    {
        return VCTRL_ERR;
    }
    
#ifdef COMMAND_LINE_EXTRA
    VCTRL_GetExtraRefFrmNum();
    VCTRL_GetExtraDispFrmNum();
    VCTRL_GetExtraCtrlCmd();
#endif

    /* 清除静态信息 */
    memset(&s_VfmwCTrl, 0, sizeof(VFMW_CTRL_DATA_S));
    memset(s_pstVfmwChan, 0, sizeof(VFMW_CHAN_S *)*MAX_CHAN_NUM);

    /* 保存状态报告回调函数 */
    g_event_report = VCTRL_EventReport;

    /* 初始化内存管理模块 */
    MemInit.MemBaseAddr     = BOARD_MEM_BASE_ADDR;
    MemInit.MemSize         = BOARD_MEM_TOTAL_SIZE;

    MEM_InitMemManager(&MemInit);

    /* 初始化帧存管理模块 */
    FSP_Init();

    /* 初始化通道状态 */
    VCTRL_ChanCtx_Init();

    /* 初始化DSP的状态 */
    memset(g_DSPState, 0, sizeof(DSP_STATE_E)*MAX_CHAN_NUM);

    /* 打开各硬件IP的驱动程序 */
    s_VfmwCTrl.stDrvMem.stExtHalMem.IsSecMem = pArgs->ext_halmem.IsSecure;
    s_VfmwCTrl.stDrvMem.stExtHalMem.PhyAddr  = pArgs->ext_halmem.PhyAddr;
    s_VfmwCTrl.stDrvMem.stExtHalMem.VirAddr  = pArgs->ext_halmem.VirAddr;
    s_VfmwCTrl.stDrvMem.stExtHalMem.Length   = pArgs->ext_halmem.Length;

    if( VCTRL_OK != VCTRL_OpenDrivers(&s_VfmwCTrl.stDrvMem) )
    {
        dprint(PRN_FATAL, "OpenDrivers fail\n");
        return VCTRL_ERR;
    }

    /* 创建跟踪器 */
#ifdef VFMW_RECPOS_SUPPORT
    DBG_CreateTracer();
#endif

    /* 初始化解码互斥锁 */
    VFMW_OSAL_InitEvent(G_INTEVENT, 1);
    
#ifdef ENV_ARMLINUX_KERNEL
    /* 仅在非安侧创建解码线程 */
    if( OSAL_OK == OSAL_CreateTask(&s_VfmwCTrl.hThread, "HI_VFMW_VideoDecode", VCTRL_Vfmw_Thread) )
    {
        s_VfmwCTrl.eTaskState = TASK_STATE_BUTT;
        OSAL_WakeupTask(&s_VfmwCTrl.hThread);
    }
    else
    {
        VCTRL_CloseDrivers(&s_VfmwCTrl.stDrvMem);
        return VCTRL_ERR;
    }
#endif

    /* 宣告VCTRL打开成功 */
    s_VfmwCTrl.s32IsVCTRLOpen = 1;

    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_CloseVfmw: VCTRL全局退出，令解码线程自动结束
 ***********************************************************************/
SINT32 VCTRL_CloseVfmw(VOID)
{
    SINT32 i;
    SINT32 ret = VCTRL_ERR;    
    UINT32 MaxWaitCount = (0 == gIsFPGA)? MAX_STOP_WAIT_COUNT: MAX_FPGA_STOP_WAIT_COUNT;  //FPGA wait longer

    if( 1 != s_VfmwCTrl.s32IsVCTRLOpen )
    {
        return VCTRL_ERR;
    }

    /* 检查是否还有未销毁的通道，如有，则强行销毁 */
    for( i= 0; i < MAX_CHAN_NUM; i++ )
    {
        if( NULL != s_pstVfmwChan[i] )
        {
            VCTRL_DestroyChan(i);
        }
    }

    /* 关闭帧存管理模块 */
    FSP_Exit();

    /* 发出“退出指令” */
    s_VfmwCTrl.eTaskCommand = TASK_CMD_KILL;

    /* 等待VCTRL进入退出状态 */
    for( i=0; i<MaxWaitCount; i++ )
    {
        if( TASK_STATE_EXIT == s_VfmwCTrl.eTaskState )
        {
            ret = VCTRL_OK;
            break;
        }
        else
        {
            VFMW_OSAL_mSleep(10);
        }
    }

    if (i >= MaxWaitCount)
    {
        dprint(PRN_ERROR, "Error in close vfmw thread!\n");
    }

    /* 取消指令 */
    s_VfmwCTrl.eTaskCommand = TASK_CMD_NONE;

    /* 复位DSP的状态 */
    memset(g_DSPState, 0, sizeof(DSP_STATE_E)*MAX_CHAN_NUM);

    /* 关闭硬件IP的驱动程序 */
    VCTRL_CloseDrivers(&s_VfmwCTrl.stDrvMem);

    /* 销毁跟踪器 */
#ifdef VFMW_RECPOS_SUPPORT
    DBG_DestroyTracer();
#endif

    /* 宣告vfmw已关闭 */
    s_VfmwCTrl.eTaskState = TASK_STATE_EXIT;
    s_VfmwCTrl.s32IsVCTRLOpen = 0;

    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_SetStreamInterface: 设置码流访问接口(一般外部模块调用)
 ***********************************************************************/
SINT32 VCTRL_SetStreamInterface(SINT32 ChanID, VOID *pIntf)
{
    VCTRL_ASSERT_RET(NULL != pIntf, "pIntf is NULL");
    VCTRL_ASSERT_RET(NULL != s_pstVfmwChan[ChanID], "Chan inactive");
    
    memcpy(&s_pstVfmwChan[ChanID]->stStreamIntf, (STREAM_INTF_S *)pIntf, sizeof(STREAM_INTF_S)) ;
    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_GetStreamInterface: 获取码流访问接口(一般被VFMW内部子模块调用)
 ***********************************************************************/
STREAM_INTF_S *VCTRL_GetStreamInterface(SINT32 ChanID)
{
    if( NULL ==s_pstVfmwChan[ChanID])
    {
        return NULL;
    }

    return &s_pstVfmwChan[ChanID]->stStreamIntf;
}

/***********************************************************************
   VCTRL_GetStreamSize:  获取通道的VDH持有码流量(byte)
 ***********************************************************************/
SINT32 VCTRL_GetStreamSize(SINT32 ChanID, SINT32 *pArgs)
{
    SM_INSTANCE_S *pInst;
    SINT32 ret;

    VCTRL_ASSERT_RET( ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "This Chan has not been created!!!");
    VCTRL_ASSERT_RET( 1 ==s_pstVfmwChan[ChanID]->s32IsOpen, "can NOT get a not-opened Chan's information of bitstream");

    pInst = &s_pstVfmwChan[ChanID]->SmInstArray;
    ret = GetSegStreamSize(&pInst->StreamSegArray, pArgs);
    return ret;
}


/***********************************************************************
   VCTRL_GetChanState: 获取通道状态
 ***********************************************************************/
VOID VCTRL_GetChanState(SINT32 ChanID, VDEC_CHAN_STATE_S *pstChanState)
{
    SINT32 s32DecodedFrameNum = 0;
    SINT32 i=0;
    SM_INST_INFO_S    ScdInstInfo;
    SINT32 RefNum, ReadNum, NewNum;

    VCTRL_ASSERT( (0 <= ChanID && ChanID < MAX_CHAN_NUM), "ChanID out of range!");

    RefNum = ReadNum = NewNum =0;

    if (NULL != pstChanState)
    {
        memset(pstChanState, 0, sizeof(VDEC_CHAN_STATE_S));
        if( NULL != s_pstVfmwChan[ChanID])
        {
            memcpy(pstChanState, &s_pstVfmwChan[ChanID]->stSynExtraData.stChanState, sizeof(VDEC_CHAN_STATE_S));

            for(i=0; i<s_pstVfmwChan[ChanID]->FspInst.s32DecFsNum; i++)
            {
                if(FS_DISP_STATE_WAIT_DISP ==s_pstVfmwChan[ChanID]->FspInst.stDecFs[i].DispState)
                {
                    s32DecodedFrameNum++;
                }
            }
            pstChanState->wait_disp_frame_num = s32DecodedFrameNum;
            pstChanState->total_disp_frame_num = s_pstVfmwChan[ChanID]->FspInst.s32DecFsNum;

            /* 待转换的1D帧数(同步过程需要探测解码器还有多少帧储备) */
            {
                VCTRL_GetChanImgNum(ChanID, &RefNum, &ReadNum, &NewNum);
                pstChanState->decoded_1d_frame_num = ReadNum + NewNum;
            }

            pstChanState->is_field_flg = g_VfmwChanStat[ChanID].u32IsFieldFlag;
            pstChanState->frame_rate = g_VfmwChanStat[ChanID].u32FrFrameRate;

            /* SCD已切割但尚未解码的码流 */
            {
                SM_INST_INFO_S SmInstInfo;
                SM_GetInfo(ChanID, &SmInstInfo);
                pstChanState->buffered_stream_size = SmInstInfo.TotalSegSize;
                pstChanState->buffered_stream_num = SmInstInfo.SegNum;
            }

            /* 是否码流不足 */
            SM_GetInfo(ChanID, &ScdInstInfo);
            pstChanState->stream_not_enough = (ScdInstInfo.numReadSegFail > 10)? 1: 0;

            #ifdef VFMW_MPEG4_SUPPORT
            pstChanState->mpeg4_shorthead = ((MP4_CTX_S*)(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax))->ScdUpMsg.IsShStreamFlag;
            #endif
        }
    }

    return;
}

SINT32 VCTRL_UnInstallChan(SINT32 ChanID)
{
    /* 关闭FSP实例 */
    FSP_DisableInstance(ChanID);
    /* 关闭user data pool实例 */
    CloseUsdPool_WithMem(ChanID);

    return VCTRL_OK;
}

SINT32 VCTRL_RlsAllFrameNode(SINT32 ChanID)
{
    SINT32 s32Ret = VDEC_OK;
    SINT32 i = 0;
    MEM_RECORD_S* MEM_RECORD = HI_NULL;

    for(i = 0; i < MAX_FRAME_NUM; i++)
    {   // release pmv men and delete node
        if(FRAME_NODE_STATE_FREE != (s_pstVfmwChan[ChanID]->stPmvBuf[i].eBufferNodeState))
        {
            MEM_RECORD = &(s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer);
            if(FRAME_NODE_STATE_MMZ == s_pstVfmwChan[ChanID]->stPmvBuf[i].eBufferNodeState)//若是动态分配的节点
            {
                MEM_ReleaseMemBlock(MEM_RECORD->PhyAddr, MEM_RECORD->VirAddr);
            }
            s32Ret = MEM_DelMemRecord(MEM_RECORD->PhyAddr, (VOID* )MEM_RECORD->VirAddr, MEM_RECORD->Length);
            s_pstVfmwChan[ChanID]->stPmvBuf[i].eBufferNodeState = 0xFF;
        }

		// delete usr mem node
		if(FRAME_NODE_STATE_FREE != (s_pstVfmwChan[ChanID]->stFrmBuf[i].eBufferNodeState))
        {
            MEM_RECORD = &(s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer);
            if(FRAME_NODE_STATE_MMZ == s_pstVfmwChan[ChanID]->stFrmBuf[i].eBufferNodeState)//若是动态分配的节点
            {
                MEM_ReleaseMemBlock(MEM_RECORD->PhyAddr, MEM_RECORD->VirAddr);
            }
            s32Ret = MEM_DelMemRecord(MEM_RECORD->PhyAddr, (VOID* )MEM_RECORD->VirAddr, MEM_RECORD->Length);
            s_pstVfmwChan[ChanID]->stFrmBuf[i].eBufferNodeState = FRAME_NODE_STATE_FREE;
        }
    }

    return s32Ret;
}

SINT32 VCTRL_InfoChanCtrlDestroy(SINT32 ChanID)
{
    UINT32 Loop = 500;
    SINT32 ret;
    
    do
    {
        ret = VCTRT_SetChanCtrlState(ChanID, CHAN_DESTORY);
        if (VDEC_OK == ret)
        {
            break;
        }
        
        VFMW_OSAL_mSleep(1);
        Loop--;
    }while(Loop != 0);
    
    if( Loop <= 0 )
    {
        dprint(PRN_ERROR, "%s %d VCTRT_SetChanCtrlState failed!\n", __func__, __LINE__);
        return VCTRL_ERR;
    }

    return VCTRL_OK;
}

SINT32 VCTRL_ReleaseDynamicNode(VFMW_CHAN_MEM_S *pstChan)
{
    SINT32 i = 0;
    SINT32 s32Ret = HI_SUCCESS;
    MEM_RECORD_S* MEM_RECORD = HI_NULL;
    
    /*释放frame node*/
    for(i = 0; i < MAX_FRAME_NUM; i++)
    {
        if (FRAME_NODE_STATE_FREE != (pstChan->pstChanFrmBuf[i].eBufferNodeState))
        {
            MEM_RECORD = &(pstChan->pstChanFrmBuf[i].stFrameBuffer);
            if (FRAME_NODE_STATE_MMZ == (pstChan->pstChanFrmBuf[i].eBufferNodeState)) //若是动态分配的节点
            {
                dprint(PRN_FS, "DFS, rls MMZ Node, %#x\n", MEM_RECORD->PhyAddr);
                MEM_ReleaseMemBlock(MEM_RECORD->PhyAddr, MEM_RECORD->VirAddr);
                
                s32Ret = MEM_DelMemRecord(MEM_RECORD->PhyAddr, (VOID * )MEM_RECORD->VirAddr, MEM_RECORD->Length);
                if (HI_SUCCESS != s32Ret)
                {
                    dprint(PRN_FS, "Del MMZMemRecord 0x%x failed!\n", MEM_RECORD->PhyAddr);
                }

                pstChan->pstChanFrmBuf[i].eBufferNodeState = FRAME_NODE_STATE_FREE;
            }
            else if (FRAME_NODE_STATE_PRE == (pstChan->pstChanFrmBuf[i].eBufferNodeState))
            {
                s32Ret = MEM_DelMemRecord(MEM_RECORD->PhyAddr, (VOID * )MEM_RECORD->VirAddr, MEM_RECORD->Length);
                if (HI_SUCCESS != s32Ret)
                {
                    dprint(PRN_FS, "Del PREMemRecord 0x%x failed!\n", MEM_RECORD->PhyAddr);
                }

                pstChan->pstChanFrmBuf[i].eBufferNodeState = FRAME_NODE_STATE_FREE;
            }
        }
    }
    
    /*释放pmv node*/
    for(i = 0; i < MAX_FRAME_NUM; i++)
    {
        if(FRAME_NODE_STATE_FREE != (pstChan->pstChanPmvBuf[i].eBufferNodeState))
        {
            MEM_RECORD = &(pstChan->pstChanPmvBuf[i].stFrameBuffer);
            if(FRAME_NODE_STATE_MMZ == pstChan->pstChanPmvBuf[i].eBufferNodeState)//若是动态分配的节点
            {
                dprint(PRN_FS, "DFS, rls Pmv MMZ Node\n");
                MEM_ReleaseMemBlock(MEM_RECORD->PhyAddr, MEM_RECORD->VirAddr);
                
                s32Ret = MEM_DelMemRecord(MEM_RECORD->PhyAddr, (VOID * )MEM_RECORD->VirAddr, MEM_RECORD->Length);
                if (HI_SUCCESS != s32Ret)
                {
                    dprint(PRN_FS, "Del MMZMemRecord 0x%x failed!\n", MEM_RECORD->PhyAddr);
                }

                pstChan->pstChanPmvBuf[i].eBufferNodeState = FRAME_NODE_STATE_FREE;
            }
            else if (FRAME_NODE_STATE_PRE == (pstChan->pstChanPmvBuf[i].eBufferNodeState))
            {
                s32Ret = MEM_DelMemRecord(MEM_RECORD->PhyAddr, (VOID * )MEM_RECORD->VirAddr, MEM_RECORD->Length);
                if (HI_SUCCESS != s32Ret)
                {
                    dprint(PRN_FS, "Del PREMemRecord Pmv 0x%x failed!\n", MEM_RECORD->PhyAddr);
                }

                pstChan->pstChanPmvBuf[i].eBufferNodeState = FRAME_NODE_STATE_FREE;
            }
        }
    }

    return VCTRL_OK;
}

SINT32 VCTRL_FreeChanResource(SINT32 ChanID, VFMW_CHAN_MEM_S *pstChan)
{
    if(1 == (pstChan->u32DynamicAllocEn))
    {
        /* 释放动态帧存节点 */
        VCTRL_ReleaseDynamicNode(pstChan);
    }
    else
    {
        /* 释放资源 vdh */
        if( 1 == pstChan->s32SelfAllocChanMem_vdh && pstChan->stChanMem_vdh.PhyAddr != 0 )
        {
            MEM_ReleaseMemBlock(pstChan->stChanMem_vdh.PhyAddr, pstChan->stChanMem_vdh.VirAddr);
        }
        MEM_DelMemRecord(pstChan->stChanMem_vdh.PhyAddr, pstChan->stChanMem_vdh.VirAddr, pstChan->stChanMem_vdh.Length);
    }

    /* 释放资源 scd */
    if( 1 == pstChan->s32SelfAllocChanMem_scd && pstChan->stChanMem_scd.PhyAddr != 0 )
    {
        MEM_ReleaseMemBlock(pstChan->stChanMem_scd.PhyAddr, pstChan->stChanMem_scd.VirAddr);
    }
    MEM_DelMemRecord(pstChan->stChanMem_scd.PhyAddr, pstChan->stChanMem_scd.VirAddr, pstChan->stChanMem_scd.Length);

    /* 释放资源 ctx */
    if( 1 == pstChan->s32SelfAllocChanMem_ctx && pstChan->stChanMem_ctx.PhyAddr != 0 )
    {
        MEM_ReleaseMemBlock(pstChan->stChanMem_ctx.PhyAddr, pstChan->stChanMem_ctx.VirAddr);
    }
    MEM_DelMemRecord(pstChan->stChanMem_ctx.PhyAddr, pstChan->stChanMem_ctx.VirAddr, pstChan->stChanMem_ctx.Length);

    /* 释放资源 SCD DSP CTX */
#ifdef VFMW_SCD_LOWDLY_SUPPORT
    SM_DeletDSPCtxMem(&(pstChan->stChanMem_dsp));
#endif

    return VCTRL_OK;
}

VOID VCTRL_GetChanCtxSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, SINT32* s32ChanCtxSize)
{
#ifndef VFMW_MVC_SUPPORT
    (*s32ChanCtxSize) = CHAN_CTX_MEM_SIZE;
#else
    SINT32 s32MaxSyntaxSize = sizeof(MP2_CTX_S);

    if(CAP_LEVEL_MVC_FHD == eCapLevel)
    {
        (*s32ChanCtxSize) = CHAN_CTX_MEM_SIZE;
        return;
    }
    else
    {
#ifdef VFMW_MPEG4_SUPPORT
        if(sizeof(MP4_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(MP4_CTX_S);
        }
#endif
#ifdef VFMW_AVS_SUPPORT
        if(sizeof(AVS_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(AVS_CTX_S);
        }
#endif
#ifdef VFMW_H264_SUPPORT
        if(sizeof(H264_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(H264_CTX_S);
        }
#endif
#ifdef VFMW_VC1_SUPPORT
        if(sizeof(VC1_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(VC1_CTX_S);
        }
#endif
#ifdef VFMW_REAL8_SUPPORT
        if(sizeof(RV8_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(RV8_CTX_S);
        }
#endif
#ifdef VFMW_REAL9_SUPPORT
        if(sizeof(RV9_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(RV9_CTX_S);
        }
#endif
#ifdef VFMW_DIVX3_SUPPORT
        if(sizeof(DIVX3_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(DIVX3_CTX_S);
        }
#endif
#ifdef VFMW_VP6_SUPPORT
        if(sizeof(VP6_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(VP6_CTX_S);
        }
#endif
#ifdef VFMW_VP8_SUPPORT
        if(sizeof(VP8_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(VP6_CTX_S);
        }
#endif
#ifdef VFMW_HEVC_SUPPORT
        if(sizeof(HEVC_CTX_S) > s32MaxSyntaxSize)
        {
            s32MaxSyntaxSize = sizeof(HEVC_CTX_S);
        }
#endif

        (*s32ChanCtxSize) = CHAN_CTX_MEM_SIZE - sizeof(MVC_CTX_S) + s32MaxSyntaxSize;
    }
#endif
}
/***********************************************************************
   VCTRL_CreateChan: 创建通道
   eCapLevel: 能力级别，此级别决定了创建通道时占用的内存空间大小
   如果成功返回通道号(>= 0)，否则返回错误码(小于0)
 ***********************************************************************/
SINT32 VCTRL_CreateChan(VDEC_CHAN_CAP_LEVEL_E eCapLevel, MEM_DESC_S *pChanMem)
{
    SINT32  ChanID;
    SINT32  VdmChanMemSize[3], ScdChanMemSize[3];
    extern SINT32 CapItem[][7];
    VDEC_CHAN_OPTION_S stChanOption;
    MEM_DESC_S vdh_MemRecord,scd_MemRecord;
    SINT32 OneChanMemFlag;
    SINT32 MinPostFspNum; 

    if (eCapLevel >= CAP_LEVEL_BUTT)
    {
        dprint(PRN_ERROR, "VCTRL_CreateChan eCapLevel = %d error! Try to use VCTRL_CreateChanWithOption(CAP_LEVEL_USER_DEFINE_WITH_OPTION, ...)\n", eCapLevel);
        return VCTRL_ERR;
    }

    memset(&stChanOption,0,sizeof(VDEC_CHAN_OPTION_S));
    memset(&vdh_MemRecord,0,sizeof(MEM_DESC_S));
    memset(&scd_MemRecord,0,sizeof(MEM_DESC_S));

    /* 标准配置Option 参数 */
    stChanOption.Purpose = PURPOSE_DECODE;
    stChanOption.MemAllocMode = MODE_ALL_BY_MYSELF;
    stChanOption.s32MaxWidth = CapItem[eCapLevel][0];
    stChanOption.s32MaxHeight = CapItem[eCapLevel][1];
    stChanOption.s32MaxSliceNum = MAX_SLICE_SLOT_NUM;
    stChanOption.s32MaxSpsNum = 32;
    stChanOption.s32MaxPpsNum = 256;

    /* 根据选定能力集决定最小 显示帧存*/
    switch (eCapLevel)
    {
        case CAP_LEVEL_4096x2160:
        case CAP_LEVEL_2160x4096:
        case CAP_LEVEL_4096x4096:
        case CAP_LEVEL_8192x4096:
        case CAP_LEVEL_4096x8192:
            MinPostFspNum = 3;
            break;
        case CAP_LEVEL_8192x8192:
        case CAP_LEVEL_SINGLE_IFRAME_FHD:
        case CAP_LEVEL_USER_DEFINE_WITH_OPTION:
            MinPostFspNum = 1;
            break;
        default:
            MinPostFspNum = 6;
            break;
    }

    if (CapItem[eCapLevel][3] <= (MinPostFspNum + PLUS_FS_NUM)) 
    {
        stChanOption.s32MaxRefFrameNum = 1;
    }
    else
    {
        /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/
        stChanOption.s32MaxRefFrameNum = CapItem[eCapLevel][3] - MinPostFspNum - PLUS_FS_NUM;
    }

    stChanOption.s32SupportBFrame = 1;
    stChanOption.u32SupportStd = 1;
    stChanOption.s32ReRangeEn = 1;  /* 支持变分辨率时重新分配帧存 */
    stChanOption.s32SCDBufSize = CapItem[eCapLevel][6];
    stChanOption.s32DisplayFrameNum = MinPostFspNum; 
    stChanOption.s32SlotWidth = 0;
    stChanOption.s32SlotHeight = 0;

    if (eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)
    {
        stChanOption.s32MaxRefFrameNum = 0;
        stChanOption.s32DisplayFrameNum = 1;
    }
	if(eCapLevel== CAP_LEVEL_MVC_FHD)
	{
        stChanOption.s32MaxRefFrameNum = 16;
        stChanOption.s32DisplayFrameNum = 6;
	}
	if(eCapLevel== CAP_LEVEL_4096x2160)
	{
		stChanOption.s32MaxRefFrameNum = 4;
		stChanOption.s32DisplayFrameNum = 2;
    }
    /* 获得通道应有的内存预算 */
    if ( VCTRL_OK != VCTRL_GetChanMemSize(eCapLevel, VdmChanMemSize, ScdChanMemSize) )
    {
        dprint(PRN_ERROR, "VCTRL_GetChanMemSize ERROR\n");
        return VCTRL_ERR;
    }
    OneChanMemFlag = 0;
     /* 如果外部已分配通道buf则使用外部buf，否则自行分配 */
    if ( (NULL != pChanMem) && (pChanMem->Length != 0))
    {
        if( 0 != pChanMem->PhyAddr && NULL != pChanMem->VirAddr
            && (VdmChanMemSize[0]+ScdChanMemSize[0]) <= pChanMem->Length )
        {
            stChanOption.MemAllocMode = MODE_PART_BY_SDK;

            scd_MemRecord.PhyAddr = pChanMem->PhyAddr;
            scd_MemRecord.VirAddr = pChanMem->VirAddr;
            scd_MemRecord.Length  = ScdChanMemSize[1];

            vdh_MemRecord.PhyAddr = pChanMem->PhyAddr + ScdChanMemSize[1];
            vdh_MemRecord.VirAddr = pChanMem->VirAddr + ScdChanMemSize[1];
            vdh_MemRecord.Length  = pChanMem->Length - ScdChanMemSize[1];

            memcpy(&(stChanOption.MemDetail.ChanMemScd),&scd_MemRecord,sizeof(MEM_DESC_S));
            memcpy(&(stChanOption.MemDetail.ChanMemVdh),&vdh_MemRecord,sizeof(MEM_DESC_S));
            OneChanMemFlag = 1;
        }
        else
        {
            dprint(PRN_ERROR,"channel memory have been allocated outside, but the mem-info is not correct!\n");
            dprint(PRN_ERROR,"mem-info(phy, vir, size) = (%#x, %p, %d)\n", pChanMem->PhyAddr, pChanMem->VirAddr, pChanMem->Length);
            dprint(PRN_ERROR,"this channel totally need %d bytes memory\n", (VdmChanMemSize[0]+ScdChanMemSize[0]));
            return VCTRL_ERR;
        }
    }

    ChanID = VCTRL_CreateChanWithOption(eCapLevel, &stChanOption, VCTRL_ADD_EXTRA, OneChanMemFlag);

    return (ChanID >= 0)? ChanID : VCTRL_ERR;
}

/*if user creat channel with eCapLevel != CAP_LEVEL_USER_DEFINE_WITH_OPTION , flag should be 1 and option is classic to avoid error; if eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION, it means
user could creat channel with all kinds of option*/
SINT32 VCTRL_CreateChanWithOption(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, SINT32 flag, SINT32 OneChanMemFlag)
{
    SINT32  ChanID;
    SINT32  s32SelfAllocChanMem_vdh, s32SelfAllocChanMem_scd, s32SelfAllocChanMem_ctx;
    MEM_DESC_S ChanMemVDH, ChanMemScd, ChanMemCtx;
    MEM_RECORD_S MemRecord;
    VDEC_CHAN_MEM_DETAIL_S *pChanMem = NULL;
    DETAIL_MEM_SIZE DetailMemSize;
    VFMW_CHAN_MEM_S ChanMem;
    SINT32 s32ChanCtxSize = 0;
	UINT32 u32i = 0;

    s32SelfAllocChanMem_vdh = 0;
    s32SelfAllocChanMem_scd = 0;
    s32SelfAllocChanMem_ctx = 0;
    memset(&ChanMemVDH, 0, sizeof(MEM_DESC_S));
    memset(&ChanMemScd, 0, sizeof(MEM_DESC_S));
    memset(&ChanMemCtx, 0, sizeof(MEM_DESC_S));
    memset(&ChanMem,    0, sizeof(VFMW_CHAN_MEM_S));

    pChanMem = &(pChanOption->MemDetail);
    
    MemRecord.IsSecMem = pChanOption->u32IsSecMode; 
    
    if (eCapLevel >= CAP_LEVEL_BUTT)
    {
        dprint(PRN_FATAL, "%s eCapLevel invalid!\n", __func__, eCapLevel);
        return VCTRL_ERR;
    }
    
    VCTRL_GetChanCtxSize(eCapLevel, &s32ChanCtxSize);

    if (eCapLevel != CAP_LEVEL_USER_DEFINE_WITH_OPTION && flag == VCTRL_USER_OPTION)
    {
        dprint(PRN_FATAL, "VDEC_CID_CREATE_CHAN_WITH_OPTION is designed for CAP_LEVEL_USER_DEFINE_WITH_OPTION, please change channel's capability.\n");
        return VCTRL_ERR;
    }
    if (pChanOption->Purpose >= PURPOSE_BUTT)
    {
        dprint(PRN_FATAL, "VDEC_CID_CREATE_CHAN_WITH_OPTION the purpose of creating the channel is not clear.\n");
        return VCTRL_ERR;
    }
    if (pChanOption->Purpose == PURPOSE_FRAME_PATH_ONLY)
    {
        if ((pChanOption->s32SlotWidth == 0) || (pChanOption->s32SlotHeight == 0))
        {
            dprint(PRN_FATAL, "s32SlotWidth or s32SlotHeight is 0.\n");
            return VCTRL_ERR;
        }
    }
    if (pChanOption->Purpose == PURPOSE_DECODE)
    {
        if ((pChanOption->s32MaxRefFrameNum < 0)
         || (pChanOption->s32MaxWidth < 32)
         || (pChanOption->s32MaxHeight < 32)
         || (pChanOption->s32SCDBufSize < SM_MIN_SEG_BUF_SIZE))
        {
            dprint(PRN_FATAL, "CAP_LEVEL_USER_DEFINE_WITH_OPTION option is illegal.\n");
            return VCTRL_ERR;
        }
    }

    if((pChanOption->u32DynamicFrameStoreAllocEn) > 1)
    {
        pChanOption->u32DynamicFrameStoreAllocEn = 0;//防止该flag为随机值.l00273086//
    }
    /* 获得通道应有的内存预算 */
    if ( VCTRL_OK != VCTRL_GetChanMemSizeWithOption(eCapLevel, pChanOption, &DetailMemSize,flag) )
    {
        dprint(PRN_FATAL, "line %d VCTRL_GetChanMemSizeWithOption failed!\n",__LINE__);
        return VCTRL_ERR;
    }

    if (pChanOption->MemAllocMode == MODE_ALL_BY_SDK)
    {
        memcpy(&ChanMemVDH,&(pChanMem->ChanMemVdh),sizeof(MEM_DESC_S));
        memcpy(&ChanMemScd,&(pChanMem->ChanMemScd),sizeof(MEM_DESC_S));
        memcpy(&ChanMemCtx,&(pChanMem->ChanMemCtx),sizeof(MEM_DESC_S));

        if ((ChanMemCtx.VirAddr == NULL)||(ChanMemCtx.Length < DetailMemSize.CtxDetailMem ))
        {
            dprint(PRN_ERROR,"L: %d : sdk can NOT alloc buffer for channel context\n", __LINE__);
            return VCTRL_ERR;
        }
        
        if ((ChanMemVDH.VirAddr == NULL)||(ChanMemVDH.Length < DetailMemSize.VdhDetailMem))
        {
            dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for VDH\n", __LINE__);
            return VCTRL_ERR;
        }
           
        if (((ChanMemScd.VirAddr == NULL)||(ChanMemScd.Length < DetailMemSize.ScdDetailMem ))&&(pChanOption->Purpose == PURPOSE_DECODE))
        {
            dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for SCD\n", __LINE__);
            return VCTRL_ERR;
        }
   
        MEM_AddMemRecord(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr, ChanMemCtx.Length);
        MEM_AddMemRecord(ChanMemVDH.PhyAddr, ChanMemVDH.VirAddr, ChanMemVDH.Length);  
        if (pChanOption->Purpose != PURPOSE_FRAME_PATH_ONLY)
        {
            MEM_AddMemRecord(ChanMemScd.PhyAddr, ChanMemScd.VirAddr, ChanMemScd.Length);
        }
    }
    else if (pChanOption->MemAllocMode == MODE_ALL_BY_MYSELF)
    {
        if( MEM_MAN_OK != MEM_AllocMemBlock("SELF_CTX", DetailMemSize.CtxDetailMem, &MemRecord, 1) )
        {
            dprint(PRN_ERROR,"L: %d : we can NOT alloc buffer for channel context, size = %d\n", __LINE__, DetailMemSize.CtxDetailMem);
            return VCTRL_ERR;
        }
        MEM_AddMemRecord(MemRecord.PhyAddr, MemRecord.VirAddr, MemRecord.Length);
        ChanMemCtx.PhyAddr = MemRecord.PhyAddr;
        ChanMemCtx.VirAddr = MemRecord.VirAddr;
        ChanMemCtx.Length  = MemRecord.Length;
        s32SelfAllocChanMem_ctx = 1;

        if(1 != pChanOption->u32DynamicFrameStoreAllocEn)
        {
	        if( MEM_MAN_OK != MEM_AllocMemBlock("SELF_VDH", DetailMemSize.VdhDetailMem, &MemRecord, 0) )
	        {
	            /* 分配失败，需释放之前已经分配的内存空间，以免内存泄漏 */
	            MEM_ReleaseMemBlock(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr);
	            MEM_DelMemRecord(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr, ChanMemCtx.Length);
	            s32SelfAllocChanMem_ctx = 0;

	            dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for channel vdh, size = %d\n", __LINE__, DetailMemSize.VdhDetailMem);
	            return VCTRL_ERR;
	        }
	        MEM_AddMemRecord(MemRecord.PhyAddr, MemRecord.VirAddr, MemRecord.Length);
	        ChanMemVDH.PhyAddr = MemRecord.PhyAddr;
	        ChanMemVDH.VirAddr = MemRecord.VirAddr;
	        ChanMemVDH.Length = MemRecord.Length;
	        s32SelfAllocChanMem_vdh = 1;
        }
        else
        {
            ChanMemVDH.PhyAddr = HI_NULL;
            ChanMemVDH.VirAddr = HI_NULL;
            ChanMemVDH.Length = 0;
            s32SelfAllocChanMem_vdh = 0;
        }

        if (pChanOption->Purpose != PURPOSE_FRAME_PATH_ONLY)
        {
            if( MEM_MAN_OK != MEM_AllocMemBlock("SELF_SCD", DetailMemSize.ScdDetailMem, &MemRecord, 0) )
            {
                /* 分配失败，需释放之前已经分配的内存空间，以免内存泄漏 */
                MEM_ReleaseMemBlock(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr);
                MEM_DelMemRecord(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr, ChanMemCtx.Length);
                if(1 == s32SelfAllocChanMem_vdh)
                {
                    MEM_ReleaseMemBlock(ChanMemVDH.PhyAddr, ChanMemVDH.VirAddr);
                    MEM_DelMemRecord(ChanMemVDH.PhyAddr, ChanMemVDH.VirAddr, ChanMemVDH.Length);
                    s32SelfAllocChanMem_vdh = 0;
                }
                s32SelfAllocChanMem_ctx = 0;
                s32SelfAllocChanMem_vdh = 0;

                dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for channel scd, size = %d\n", __LINE__, DetailMemSize.ScdDetailMem);
                return VCTRL_ERR;
            }
            MEM_AddMemRecord(MemRecord.PhyAddr, MemRecord.VirAddr, MemRecord.Length);
            ChanMemScd.PhyAddr = MemRecord.PhyAddr;
            ChanMemScd.VirAddr = MemRecord.VirAddr;
            ChanMemScd.Length = MemRecord.Length;

            s32SelfAllocChanMem_scd = 1;
        }
        else
        {
            ChanMemScd.PhyAddr = ChanMemVDH.PhyAddr;
            ChanMemScd.VirAddr = ChanMemVDH.VirAddr;
            ChanMemScd.Length = 0;
        }
    }
    else if(pChanOption->MemAllocMode == MODE_PART_BY_SDK)
    {
        if(pChanMem->ChanMemCtx.VirAddr == NULL || pChanMem->ChanMemCtx.Length == 0)
        {
            if( MEM_MAN_OK != MEM_AllocMemBlock("SELF_CTX", DetailMemSize.CtxDetailMem, &MemRecord, 1) )
            {
                dprint(PRN_ERROR,"L: %d : part we can NOT alloc buffer for channel context\n", __LINE__);
                return VCTRL_ERR;
            }
            MEM_AddMemRecord(MemRecord.PhyAddr, MemRecord.VirAddr, MemRecord.Length);
            ChanMemCtx.PhyAddr = MemRecord.PhyAddr;
            ChanMemCtx.VirAddr = MemRecord.VirAddr;
            ChanMemCtx.Length = MemRecord.Length;
            s32SelfAllocChanMem_ctx = 1;
        }
        else
        {
            memcpy(&ChanMemCtx,&(pChanMem->ChanMemCtx),sizeof(MEM_DESC_S));
            if (ChanMemCtx.Length < DetailMemSize.CtxDetailMem )
            {
                dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for channel context\n", __LINE__);
                return VCTRL_ERR;
            }
            MEM_AddMemRecord(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr, ChanMemCtx.Length);
        }

        if(pChanMem->ChanMemVdh.VirAddr == NULL || pChanMem->ChanMemVdh.Length == 0)
        {
            if(1 != pChanOption->u32DynamicFrameStoreAllocEn)
            {
	            if( MEM_MAN_OK != MEM_AllocMemBlock("SELF_VDH", DetailMemSize.VdhDetailMem, &MemRecord, 0) )
	            {
	                /* 分配失败，需释放之前自己已经分配的内存空间，以免内存泄漏 */
	                if(s32SelfAllocChanMem_ctx == 1)
	                {
	                    MEM_ReleaseMemBlock(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr);
	                    MEM_DelMemRecord(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr, ChanMemCtx.Length);
	                    s32SelfAllocChanMem_ctx = 0;
	                }
	                dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for channel vdh\n", __LINE__);
	                return VCTRL_ERR;
	            }
	            MEM_AddMemRecord(MemRecord.PhyAddr, MemRecord.VirAddr, MemRecord.Length);
	            ChanMemVDH.PhyAddr = MemRecord.PhyAddr;
	            ChanMemVDH.VirAddr = MemRecord.VirAddr;
	            ChanMemVDH.Length = MemRecord.Length;
	            s32SelfAllocChanMem_vdh = 1;
	        }
	        else
	        {
                ChanMemVDH.PhyAddr = HI_NULL;
                ChanMemVDH.VirAddr = HI_NULL;
                ChanMemVDH.Length = 0;
                s32SelfAllocChanMem_vdh = 0;
            }
        }
        else
        {
            memcpy(&ChanMemVDH,&(pChanMem->ChanMemVdh),sizeof(MEM_DESC_S));
            if ((1 != pChanOption->u32DynamicFrameStoreAllocEn) && \
                (ChanMemVDH.Length < DetailMemSize.VdhDetailMem))
            {
                /* 分配失败，需释放之前自己已经分配的内存空间，以免内存泄漏 */
                if(s32SelfAllocChanMem_ctx == 1)
                {
                    MEM_ReleaseMemBlock(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr);
                    MEM_DelMemRecord(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr, ChanMemCtx.Length);
                    s32SelfAllocChanMem_ctx = 0;
                }
                dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for channel vdh, %#x < %#x\n", __LINE__, ChanMemVDH.Length, DetailMemSize.VdhDetailMem);
                return VCTRL_ERR;
            }
            MEM_AddMemRecord(ChanMemVDH.PhyAddr, ChanMemVDH.VirAddr, ChanMemVDH.Length);
        }

        if(pChanMem->ChanMemScd.VirAddr == NULL || pChanMem->ChanMemScd.Length == 0)
        {
            if (pChanOption->Purpose != PURPOSE_FRAME_PATH_ONLY)
            {
                if( MEM_MAN_OK != MEM_AllocMemBlock("SELF_SCD", DetailMemSize.ScdDetailMem, &MemRecord, 0) )
                {
                    /* 分配失败，需释放之前自己已经分配的内存空间，以免内存泄漏 */
                    if(s32SelfAllocChanMem_ctx == 1)
                    {
                        MEM_ReleaseMemBlock(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr);
                        MEM_DelMemRecord(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr, ChanMemCtx.Length);
                        s32SelfAllocChanMem_ctx = 0;
                    }

                    if(s32SelfAllocChanMem_vdh == 1)
                    {
                        MEM_ReleaseMemBlock(ChanMemVDH.PhyAddr, ChanMemVDH.VirAddr);
                        MEM_DelMemRecord(ChanMemVDH.PhyAddr, ChanMemVDH.VirAddr, ChanMemVDH.Length);
                        s32SelfAllocChanMem_vdh = 0;
                    }
                    dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for channel scd\n", __LINE__);
                    return VCTRL_ERR;
                }
                MEM_AddMemRecord(MemRecord.PhyAddr, MemRecord.VirAddr, MemRecord.Length);
                ChanMemScd.PhyAddr = MemRecord.PhyAddr;
                ChanMemScd.VirAddr = MemRecord.VirAddr;
                ChanMemScd.Length = MemRecord.Length;
                s32SelfAllocChanMem_scd = 1;
            }
            else
            {
                ChanMemScd.PhyAddr = ChanMemVDH.PhyAddr;
                ChanMemScd.VirAddr = ChanMemVDH.VirAddr;
                ChanMemScd.Length = 0;
            }
        }
        else
        {
            memcpy(&ChanMemScd,&(pChanMem->ChanMemScd),sizeof(MEM_DESC_S));
            if (pChanOption->Purpose != PURPOSE_FRAME_PATH_ONLY)
            {
                if (((ChanMemScd.VirAddr == NULL)||(ChanMemScd.Length < DetailMemSize.ScdDetailMem ))&&
                    (pChanOption->Purpose == PURPOSE_DECODE))
                {
                    /* 分配失败，需释放之前自己已经分配的内存空间，以免内存泄漏 */
                    if(s32SelfAllocChanMem_ctx == 1)
                    {
                        MEM_ReleaseMemBlock(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr);
                        MEM_DelMemRecord(ChanMemCtx.PhyAddr, ChanMemCtx.VirAddr, ChanMemCtx.Length);
                        s32SelfAllocChanMem_ctx = 0;
                    }

                    if(s32SelfAllocChanMem_vdh == 1)
                    {
                        MEM_ReleaseMemBlock(ChanMemVDH.PhyAddr, ChanMemVDH.VirAddr);
                        MEM_DelMemRecord(ChanMemVDH.PhyAddr, ChanMemVDH.VirAddr, ChanMemVDH.Length);
                        s32SelfAllocChanMem_vdh = 0;
                    }
                    dprint(PRN_ERROR,"L: %d : can NOT alloc buffer for SCD\n", __LINE__);
                    return VCTRL_ERR;
                }
                MEM_AddMemRecord(ChanMemScd.PhyAddr, ChanMemScd.VirAddr, ChanMemScd.Length);
            }
        }
    }
    else
    {
        dprint(PRN_ERROR,"mem alloc mode is not supportted\n");
        return VCTRL_ERR;
    }

    VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);

    VCTRL_MaskAllInt();
    
    /* 寻找一个空闲的通道 */
    for ( ChanID = FIRST_CHAN_NUM; ChanID < LAST_CHAN_NUM; ChanID++ )
    {
        if ( NULL == s_pstVfmwChan[ChanID] )
        {
            break;
        }
    }

    if ( ChanID >= LAST_CHAN_NUM )
    {
        dprint(PRN_ERROR, "vfmw have max(%d) channels opened, can NOT create more channels\n", LAST_CHAN_NUM);
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
        return VCTRL_ERR;
    }

    s_pstVfmwChan[ChanID] = (VFMW_CHAN_S*)ChanMemCtx.VirAddr;
    memset( s_pstVfmwChan[ChanID], 0, s32ChanCtxSize - (2048+sizeof(VDEC_USRDAT_POOL_S)) );
    {
        memcpy(&s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption, pChanOption, sizeof(VDEC_CHAN_OPTION_S));
        s_pstVfmwChan[ChanID]->stSynExtraData.s32BasicCtxSize = s32ChanCtxSize;
        s_pstVfmwChan[ChanID]->eChanCapLevel = eCapLevel;
        s_pstVfmwChan[ChanID]->stSynExtraData.eCapLevel = eCapLevel;
        s_pstVfmwChan[ChanID]->stSynExtraData.s32MoreGapEnable = 0;
    }
    s_pstVfmwChan[ChanID]->s32ChanID        = ChanID;
    s_pstVfmwChan[ChanID]->eAdapterType     = pChanOption->eAdapterType;
    s_pstVfmwChan[ChanID]->eVidStd          = VFMW_END_RESERVED;
    s_pstVfmwChan[ChanID]->stSynCtx.eVidStd = VFMW_END_RESERVED;
    s_SmIIS.pSmInstArray[ChanID]            = &s_pstVfmwChan[ChanID]->SmInstArray;
    s_pFspInst[ChanID]                      = &s_pstVfmwChan[ChanID]->FspInst;

    VCTRL_ResetChan(ChanID);

    s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_vdh = s32SelfAllocChanMem_vdh;
    s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_scd = s32SelfAllocChanMem_scd;
    s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_ctx = s32SelfAllocChanMem_ctx;

    s_pstVfmwChan[ChanID]->s32RefFrameNum    = 0;
    s_pstVfmwChan[ChanID]->s32RefFrameSize   = 0;
    s_pstVfmwChan[ChanID]->s32RefPmvSize     = 0;
    s_pstVfmwChan[ChanID]->s32ActualFrameNum = 0;
    for(u32i = 0; u32i < MAX_FRAME_NUM; u32i++)
    {
        s_pstVfmwChan[ChanID]->stFrmBuf[u32i].eBufferNodeState = FRAME_NODE_STATE_FREE;
		s_pstVfmwChan[ChanID]->stPmvBuf[u32i].eBufferNodeState = FRAME_NODE_STATE_FREE;
        memset(&(s_pstVfmwChan[ChanID]->stFrmBuf[u32i].stFrameBuffer), 0, sizeof(MEM_RECORD_S));
		memset(&(s_pstVfmwChan[ChanID]->stPmvBuf[u32i].stFrameBuffer), 0, sizeof(MEM_RECORD_S));
    }
    memset(&(s_pstVfmwChan[ChanID]->stMemArrangeInfo), 0, sizeof(VFMW_MEM_ARRANGE_INFO_S));
    memset(&(s_pstVfmwChan[ChanID]->stDynamicFSTimestamp), 0, sizeof(VFMW_DYNAMIC_FS_TIMESTAMP_S));
    s_ChanControlState[ChanID] = CHAN_NORMAL;

    /*为了保留分配一部分内存的创建通道方式，此处进行内存信息的存储*/
    if ((pChanOption->MemAllocMode == MODE_PART_BY_SDK)&&(s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_ctx == 1)
        &&(s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_vdh == 0)&&(s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_scd == 0)
        &&((ChanMemScd.PhyAddr + ChanMemScd.Length) == ChanMemVDH.PhyAddr)&&(OneChanMemFlag == 1))
    {
        s_pstVfmwChan[ChanID]->stChanMem.PhyAddr = ChanMemScd.PhyAddr;
        s_pstVfmwChan[ChanID]->stChanMem.VirAddr = ChanMemScd.VirAddr;
        s_pstVfmwChan[ChanID]->stChanMem.Length = ChanMemScd.Length + ChanMemVDH.Length;
        s_pstVfmwChan[ChanID]->s32OneChanMem = 1;
    }
    else
    {
        s_pstVfmwChan[ChanID]->s32OneChanMem = 0;
    }

    s_pstVfmwChan[ChanID]->stChanMem_vdh.PhyAddr = ChanMemVDH.PhyAddr;
    s_pstVfmwChan[ChanID]->stChanMem_vdh.VirAddr = ChanMemVDH.VirAddr;
    s_pstVfmwChan[ChanID]->stChanMem_vdh.Length  = ChanMemVDH.Length;

    s_pstVfmwChan[ChanID]->stChanMem_scd.PhyAddr = ChanMemScd.PhyAddr;
    s_pstVfmwChan[ChanID]->stChanMem_scd.VirAddr = ChanMemScd.VirAddr;
    s_pstVfmwChan[ChanID]->stChanMem_scd.Length  = ChanMemScd.Length;

    s_pstVfmwChan[ChanID]->stChanMem_ctx.PhyAddr = ChanMemCtx.PhyAddr;
    s_pstVfmwChan[ChanID]->stChanMem_ctx.VirAddr = ChanMemCtx.VirAddr;
    s_pstVfmwChan[ChanID]->stChanMem_ctx.Length  = ChanMemCtx.Length;

    s_pstVfmwChan[ChanID]->FspInst.eFspPartitionState = FSP_PARTITION_STATE_FIRST;//初始化通道帧存划分状态为第一次划分,等待接收数据获取宽高等.l00273086//

    //--- VDM
    if(1 != s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) //l00273086 使用动态分配的时候，BPD与SEGID的大小分在SCD中
    {
        s_pstVfmwChan[ChanID]->s32VdmChanMemAddr = ChanMemVDH.PhyAddr;
        s_pstVfmwChan[ChanID]->s32VdmChanMemSize = ChanMemVDH.Length - 16;
    #ifdef VFMW_VC1_SUPPORT
        s_pstVfmwChan[ChanID]->s32VdmChanMemSize -= BPD_SIZE;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        s_pstVfmwChan[ChanID]->s32VdmChanMemSize -= VP8_SEGID_SIZE;
    #endif

        //--- BPD
    #ifdef VFMW_VC1_SUPPORT
        s_pstVfmwChan[ChanID]->s32BpdChanMemAddr = (s_pstVfmwChan[ChanID]->s32VdmChanMemAddr + s_pstVfmwChan[ChanID]->s32VdmChanMemSize + 15)&(~0xf);
        s_pstVfmwChan[ChanID]->s32BpdChanMemSize = BPD_SIZE;
    #else
        s_pstVfmwChan[ChanID]->s32BpdChanMemAddr = 0;
        s_pstVfmwChan[ChanID]->s32BpdChanMemSize = 0;
    #endif

    #ifdef VFMW_VP8_SUPPORT
        s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemAddr = (s_pstVfmwChan[ChanID]->s32VdmChanMemAddr + s_pstVfmwChan[ChanID]->s32VdmChanMemSize +
                                                         s_pstVfmwChan[ChanID]->s32BpdChanMemSize + 15)&(~0xf);
        s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemSize = VP8_SEGID_SIZE;
    #else
        s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemAddr = 0;
        s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemSize = 0;
    #endif

        //--- (4) SCD
        s_pstVfmwChan[ChanID]->s32ScdChanMemAddr = ChanMemScd.PhyAddr;
        s_pstVfmwChan[ChanID]->s32ScdChanMemSize = ChanMemScd.Length;
    }
    else
    {
        s_pstVfmwChan[ChanID]->s32VdmChanMemAddr = 0;
        s_pstVfmwChan[ChanID]->s32VdmChanMemSize = 0;
        s_pstVfmwChan[ChanID]->s32ScdChanMemAddr = ChanMemScd.PhyAddr;
        s_pstVfmwChan[ChanID]->s32ScdChanMemSize = ChanMemScd.Length - 16;
    #ifdef VFMW_VC1_SUPPORT
        s_pstVfmwChan[ChanID]->s32ScdChanMemSize -= BPD_SIZE;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        s_pstVfmwChan[ChanID]->s32ScdChanMemSize -= VP8_SEGID_SIZE;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        s_pstVfmwChan[ChanID]->s32BpdChanMemAddr = (s_pstVfmwChan[ChanID]->s32ScdChanMemAddr + s_pstVfmwChan[ChanID]->s32ScdChanMemSize + 15)&(~0xf);
        s_pstVfmwChan[ChanID]->s32BpdChanMemSize = BPD_SIZE;
    #else
        s_pstVfmwChan[ChanID]->s32BpdChanMemAddr = 0;
        s_pstVfmwChan[ChanID]->s32BpdChanMemSize = 0;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemAddr = (s_pstVfmwChan[ChanID]->s32ScdChanMemAddr + s_pstVfmwChan[ChanID]->s32ScdChanMemSize +
                                                         s_pstVfmwChan[ChanID]->s32BpdChanMemSize + 15)&(~0xf);
        s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemSize = VP8_SEGID_SIZE;
    #else
        s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemAddr = 0;
        s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemSize = 0;
    #endif
    }

    /* 创建SCD/VDM通道 */
    s_pstVfmwChan[ChanID]->s32ChanID    = ChanID;
    s_pstVfmwChan[ChanID]->s32SCDInstID = ChanID;
    s_pstVfmwChan[ChanID]->s32VDMInstID = ChanID;
    s_pstVfmwChan[ChanID]->FspInst.s32InstID = ChanID;
    s_pstVfmwChan[ChanID]->SmInstArray.InstID = ChanID;

    /* 使能帧存管理实例 */
    if (FSP_OK != FSP_EnableInstance(ChanID))
    {
        dprint(PRN_ERROR, "can NOT enable FSP instance\n");
        goto INSTALL_ERROR_EXIT;
    }

    SM_ClearInst(ChanID);

    /* 打开user data pool实例 */
    OpenUsdPool_WithMem(ChanID, s_pstVfmwChan[ChanID]->stChanMem_ctx.VirAddr + s32ChanCtxSize-sizeof(VDEC_USRDAT_POOL_S));

    /* 标志该通道成功打开 */
    s_pstVfmwChan[ChanID]->s32IsOpen = 1;
    VDMDRV_ClearChanIsDec(ChanID);//标记此通道未被解码

    VCTRL_EnableAllInt();
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);

#ifdef VFMW_SCD_LOWDLY_SUPPORT
    pChanOption->s32ScdLowdlyEnable = 1;
    if(pChanOption->s32ScdLowdlyEnable)
    {
        SM_AllocDSPCtxMem(ChanID);
    }
#endif

    return ChanID;

INSTALL_ERROR_EXIT:
    VCTRL_UnInstallChan(ChanID);

    ChanMem.s32SelfAllocChanMem_ctx = s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_ctx;
    ChanMem.s32SelfAllocChanMem_vdh = s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_vdh;
    ChanMem.s32SelfAllocChanMem_scd = s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_scd;
    ChanMem.pstChanFrmBuf = s_pstVfmwChan[ChanID]->stFrmBuf;
    ChanMem.pstChanPmvBuf = s_pstVfmwChan[ChanID]->stPmvBuf;
    memcpy(&ChanMem.stChanMem, &s_pstVfmwChan[ChanID]->stChanMem, sizeof(MEM_RECORD_S));
    memcpy(&ChanMem.stChanMem_ctx, &s_pstVfmwChan[ChanID]->stChanMem_ctx, sizeof(MEM_RECORD_S));
    memcpy(&ChanMem.stChanMem_vdh, &s_pstVfmwChan[ChanID]->stChanMem_vdh, sizeof(MEM_RECORD_S));
    memcpy(&ChanMem.stChanMem_scd, &s_pstVfmwChan[ChanID]->stChanMem_scd, sizeof(MEM_RECORD_S));

    s_pstVfmwChan[ChanID] = NULL;
    VDMDRV_ClearChanIsDec(ChanID);//标记此通道未被解码

    VCTRL_EnableAllInt();
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    VCTRL_FreeChanResource(ChanID, &ChanMem);

    return VCTRL_ERR;
}

/***********************************************************************
   VCTRL_DestroyChan: 销毁通道
 ***********************************************************************/
SINT32 VCTRL_DestroyChan(SINT32 ChanID)
{
    SINT32 ret = VCTRL_ERR;

    ret = VCTRL_DestroyChanWithOption(ChanID);

    g_DSPState[ChanID] = DSP_STATE_NORMAL;

    return ret;
}

SINT32 VCTRL_DestroyChanWithOption(SINT32 ChanID)
{
    VFMW_CHAN_MEM_S ChanMem;
    VFMW_CHAN_S *pstChan;
    SINT32 ret = VCTRL_ERR;
    
    ret = VCTRL_InfoChanCtrlDestroy(ChanID);
    if (ret != VCTRL_OK)
    {
        dprint(PRN_FATAL,"%s InfoChanCtrlDestroy failed!\n", __func__);
        VCTRL_EnableAllInt();
        return VCTRL_ERR;
    }

    VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);

    if( ChanID < 0 || ChanID >= MAX_CHAN_NUM )
    {
        dprint(PRN_FATAL,"%s ChanID %d invalid!\n", __func__, ChanID);
        VCTRL_EnableAllInt();
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
        return VCTRL_ERR;
    }
    if( NULL == s_pstVfmwChan[ChanID] )
    {
        dprint(PRN_FATAL,"%s s_pstVfmwChan[%d] = NULL!\n", __func__, ChanID);
        VCTRL_EnableAllInt();
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
        return VCTRL_ERR;
    }
    /* 如果此处判断s32IsOpen会导致如果创建过程中出现失败并destroy时不清空s_pstVfmwChan[ChanID]，
       进而使得外部使用s_pstVfmwChan[ChanID]会出错，误认为该通道依然存在 */
    /*此处重新增加s32IsOpen判断条件是为了保证通道创建不成功就无法进行销毁，而在创建通道失败时，直接调用VCTRL_UnInstallChan
       和VCTRL_FreeChanResouce即可实现对各个实例状态的禁用和通道相关资源的释放*/
    if( 1 != s_pstVfmwChan[ChanID]->s32IsOpen )
    {
        dprint(PRN_FATAL,"%s s_pstVfmwChan[%d]->s32IsOpen = %d, invalid\n", __func__, ChanID, s_pstVfmwChan[ChanID]->s32IsOpen);
        VCTRL_EnableAllInt();
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
        return VCTRL_ERR;
    }

    pstChan = s_pstVfmwChan[ChanID];

    VFMW_OSAL_SpinLock(G_SPINLOCK_DESTROY);

    ret = VCTRL_StopChan(ChanID);
	if(VCTRL_OK != ret)
	{
        dprint(PRN_FATAL,"%s VCTRL_StopChan failed!\n", __func__);
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
		return VCTRL_ERR;
	}
    
    /*重置该通道*/
    VCTRL_ResetChan(ChanID);

    /*关闭相关资源*/
    VCTRL_UnInstallChan(ChanID);

    /*20150107: l232354 此处新加注释，下面进行赋值和COPY的原因是: 释放内存资源有休眠动作，
      不能够放到锁里面，但又要保证通道上下文相关互斥，故内存资源释放的信息需要进行备份，然
      后在锁外面进行资源的释放。
    */
    ChanMem.s32SelfAllocChanMem_ctx = s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_ctx;
    ChanMem.s32SelfAllocChanMem_vdh = s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_vdh;
    ChanMem.s32SelfAllocChanMem_scd = s_pstVfmwChan[ChanID]->s32SelfAllocChanMem_scd;
    ChanMem.u32DynamicAllocEn       = s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn;
    ChanMem.pstChanFrmBuf           = s_pstVfmwChan[ChanID]->stFrmBuf;
    ChanMem.pstChanPmvBuf           = s_pstVfmwChan[ChanID]->stPmvBuf;
    memcpy(&ChanMem.stChanMem,     &s_pstVfmwChan[ChanID]->stChanMem, sizeof(MEM_RECORD_S));
    memcpy(&ChanMem.stChanMem_ctx, &s_pstVfmwChan[ChanID]->stChanMem_ctx, sizeof(MEM_RECORD_S));
    memcpy(&ChanMem.stChanMem_vdh, &s_pstVfmwChan[ChanID]->stChanMem_vdh, sizeof(MEM_RECORD_S));
    memcpy(&ChanMem.stChanMem_scd, &s_pstVfmwChan[ChanID]->stChanMem_scd, sizeof(MEM_RECORD_S));
    memcpy(&ChanMem.stChanMem_dsp, &s_SmIIS.DspCtxMem[ChanID].stBaseMemInfo, sizeof(MEM_RECORD_S));
    s_SmIIS.pSmInstArray[ChanID] = NULL;
    s_pFspInst[ChanID] = NULL;
    s_pstVfmwChan[ChanID] = NULL;
    VDMDRV_ClearChanIsDec(ChanID);//标记此通道未被解码
    
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);
    VCTRL_EnableAllInt();
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);

    VCTRL_FreeChanResource(ChanID, &ChanMem);

    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_StartChan: 启动通道
 ***********************************************************************/
SINT32 VCTRL_StartChan(SINT32 ChanID)
{
    SINT32 i;
    static SINT32 PrioArray[MAX_CHAN_NUM];  /* 防止过多占用stack， 下同 */

    VCTRL_ASSERT_RET( ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "This Chan has not been created!!!");
    VCTRL_ASSERT_RET( 1 ==s_pstVfmwChan[ChanID]->s32IsOpen, "can NOT start a not-opened Chan");
    VCTRL_ASSERT_RET( s_pstVfmwChan[ChanID]->eVidStd != VFMW_END_RESERVED, "WARNING: vidio std not setted!");

    /* 启动SCD实例 */
    SM_Start(ChanID);

    /* 启动syntax */
    s_pstVfmwChan[ChanID]->s32IsRun = 1;
    s_pstVfmwChan[ChanID]->s32StopSyntax = 0;

    /* 设置默认优先级为1 */
    if (0 == s_pstVfmwChan[ChanID]->s32Priority)
    {
        s_pstVfmwChan[ChanID]->s32Priority = 1;
        // 刷新VDMDRV的优先级排序表
        for(i=0; i<MAX_CHAN_NUM; i++)
        {
            if( NULL != s_pstVfmwChan[i] )
            {
                PrioArray[i] = s_pstVfmwChan[i]->s32Priority;
                g_ChanCtx.PriorByChanId[i] = s_pstVfmwChan[i]->s32Priority;
            }
            else
            {
                PrioArray[i] = 0;
                g_ChanCtx.PriorByChanId[i] = 0;
            }
        }
        VDMDRV_SetPriority(PrioArray);
        VDMDRV_ClearChanIsDec(ChanID);//标记此通道未被解码

    }

    VDMDRV_ClearChanIsDec(ChanID);//标记此通道未被解码

    VCTRL_OpenHardware(ChanID);

    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_StopChanWithCheck: 循环检查确保通道确实已经停止
 ***********************************************************************/
SINT32 VCTRL_StopChanWithCheck(SINT32 ChanID)
{
    UINT32 i;
    SINT32 ret;
    UINT32 MaxWaitCount = (0 == gIsFPGA)? MAX_STOP_WAIT_COUNT: MAX_FPGA_STOP_WAIT_COUNT;  //FPGA wait longer

    for (i=0; i<MaxWaitCount; i++)
    {
        VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
        ret = VCTRL_StopChan(ChanID);
        VCTRL_EnableAllInt();
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
        if (VCTRL_OK == ret)
        {
            break;
        }
        else
        {
            VFMW_OSAL_mSleep(10);
        }
    }

    return ret;
}

/***********************************************************************
   VCTRL_StopChan: 停止通道
 ***********************************************************************/
SINT32 VCTRL_StopChan(SINT32 ChanID)
{
    VCTRL_ASSERT_RET( ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( NULL != s_pstVfmwChan[ChanID], "This Chan has not been created or has been destroyed !");

    if (s_pstVfmwChan[ChanID]->s32IsOpen != 1)
    {
        return VCTRL_ERR;
    }

    /* 先停止syntax，然后等待后级流干净，以保证安全的通道stop和 */
    s_pstVfmwChan[ChanID]->s32StopSyntax = 1;

    s_pstVfmwChan[ChanID]->s32IsRun = 0;
    
    /* 停止SCD实例 */
    if(FMW_OK != SM_Stop(ChanID))
    {
        return VCTRL_ERR;
    }
    DeleteRawPacketInBuffer(ChanID, 0);

    /*等待MFDE解码完成*/
    if (VFMW_TRUE == VDMDRV_IsChanInDec(ChanID))
    {
        //dprint(PRN_ERROR, "Chan still in dec, wait for a while.\n");
        return VCTRL_ERR;
    }

    VDMDRV_ClearChanIsDec(ChanID);//标记此通道未被解码

    s_pstVfmwChan[ChanID]->s32StopSyntax = 0;

    VCTRL_CloseHardware();

    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_GetChanCfg: 获取通道配置信息
 ***********************************************************************/
SINT32 VCTRL_GetChanCfg(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg)
{
    VCTRL_ASSERT_RET( ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( pstCfg != NULL, "pstCfg is null");
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "Chan inactive");

    memcpy( pstCfg, &s_pstVfmwChan[ChanID]->stChanCfg, sizeof(VDEC_CHAN_CFG_S) );

    return VCTRL_OK;
}


SINT32 VCTRL_CmpConfigParameter(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg)
{
    if (s_pstVfmwChan[ChanID]->eVidStd != VFMW_END_RESERVED)
    {
        if ((s_pstVfmwChan[ChanID]->stChanCfg.eVidStd == pstCfg->eVidStd)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s32ChanErrThr == pstCfg->s32ChanErrThr)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s32ChanPriority == pstCfg->s32ChanPriority)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s32ChanStrmOFThr == pstCfg->s32ChanStrmOFThr)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s32DecMode == pstCfg->s32DecMode)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s8DecOrderOutput == pstCfg->s8DecOrderOutput)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s8VcmpEn == pstCfg->s8VcmpEn)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s32VcmpWmEndLine == pstCfg->s32VcmpWmEndLine)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s32VcmpWmStartLine == pstCfg->s32VcmpWmStartLine)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s8WmEn == pstCfg->s8WmEn)
            &&(s_pstVfmwChan[ChanID]->stChanCfg.s8SupportAllP == pstCfg->s8SupportAllP))
        {
            if (s_pstVfmwChan[ChanID]->stChanCfg.eVidStd == VFMW_VC1)
            {
                if ((s_pstVfmwChan[ChanID]->stChanCfg.StdExt.Vc1Ext.IsAdvProfile == pstCfg->StdExt.Vc1Ext.IsAdvProfile)
                    &&(s_pstVfmwChan[ChanID]->stChanCfg.StdExt.Vc1Ext.CodecVersion == pstCfg->StdExt.Vc1Ext.CodecVersion))
                {
                    return VCTRL_OK;
                }
                else
                {
                    return VCTRL_ERR;
                }
            }
            else if ((s_pstVfmwChan[ChanID]->stChanCfg.eVidStd == VFMW_VP6)
                      ||(s_pstVfmwChan[ChanID]->stChanCfg.eVidStd == VFMW_VP6F)
                      ||(s_pstVfmwChan[ChanID]->stChanCfg.eVidStd == VFMW_VP6A))
            {
                if (s_pstVfmwChan[ChanID]->stChanCfg.StdExt.Vp6Ext.bReversed == pstCfg->StdExt.Vp6Ext.bReversed)
                {
                    return VCTRL_OK;
                }
                else
                {
                    return VCTRL_ERR;
                }
            }
            else
            {
                return VCTRL_OK;
            }
        }
        else
        {
            return VCTRL_ERR;
        }
    }
    else
    {
        return VCTRL_ERR;
    }
}

/************************************************************************
    VCTRL_GetVdecCapability 获取当前产品能力集
 ************************************************************************/
VOID VCTRL_GetVdecCapability(VDEC_CAP_S *pCap)
{
    SINT32  StdCnt = 0; 

    memset( pCap, 0, sizeof(VDEC_CAP_S) );
	
    pCap->s32MaxChanNum = MAX_CHAN_NUM;
    pCap->s32MaxBitRate = 150;
    pCap->s32MaxFrameWidth  = 4096;
    pCap->s32MaxFrameHeight = 4096;
    pCap->s32MaxPixelPerSec = pCap->s32MaxFrameWidth*pCap->s32MaxFrameHeight*30*3/2;
	
#ifdef    VFMW_H264_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_H264;
#endif	
#ifdef    VFMW_MPEG2_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_MPEG2;
#endif	
#ifdef    VFMW_MPEG4_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_MPEG4;
#endif	
#ifdef    VFMW_AVS_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_AVS;
#endif
#ifdef    VFMW_REAL8_SUPPORT
	pCap->SupportedStd[StdCnt++] = VFMW_REAL8;
#endif
#ifdef    VFMW_REAL9_SUPPORT
	pCap->SupportedStd[StdCnt++] = VFMW_REAL9;
#endif
#ifdef    VFMW_VC1_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_VC1;
#endif	
#ifdef    VFMW_DIVX3_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_DIVX3;
#endif	
#ifdef    VFMW_VP6_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_VP6;
    pCap->SupportedStd[StdCnt++] = VFMW_VP6F;
    pCap->SupportedStd[StdCnt++] = VFMW_VP6A;
#endif	
#ifdef    VFMW_VP8_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_VP8;
#endif	
#ifdef    VFMW_MVC_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_MVC;
#endif	
#ifdef    VFMW_HEVC_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_HEVC;
#endif		  
    pCap->SupportedStd[StdCnt++] = VFMW_END_RESERVED;

    return;
}


/***********************************************************************
   VCTRL_ResetChan: 配置通道
 ***********************************************************************/
SINT32 VCTRL_ConfigChan(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg)
{
    SM_CFG_S   ScdInstCfg;
    FSP_ATTR_S FspInstCfg;
    SINT32 i;
    static SINT32 PrioArray[MAX_CHAN_NUM];  /* 防止过多占用stack， 下同 */
    static VDEC_CAP_S  Capability;
    SINT32 s32supportFlag = 0;

    VCTRL_ASSERT_RET( ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "Chan inactive");
    VCTRL_ASSERT_RET( 1==s_pstVfmwChan[ChanID]->s32IsOpen, "can NOT config a not-opened Chan");

    /* 检查是否超出能力范围 */
    VCTRL_GetVdecCapability(&Capability);
    for (i = 0; i < 32; i++)
    {
        if (Capability.SupportedStd[i] >= VFMW_END_RESERVED)
        {
            dprint(PRN_FATAL,"VFMW didn't support std %d.\n", pstCfg->eVidStd);
            return VCTRL_ERR;
        }
        if (pstCfg->eVidStd == Capability.SupportedStd[i])
        {
            break;
        }
    }

    if (pstCfg->eVidStd == VFMW_REAL8)
    {
        REAL8DEC_Support(&s32supportFlag);

        if (0 == s32supportFlag)
        {
            return VCTRL_ERR;
        }
    }

    if (pstCfg->eVidStd == VFMW_REAL9)
    {
        REAL9DEC_Support(&s32supportFlag);

        if (0 == s32supportFlag)
        {
            return VCTRL_ERR;
        }
    }

    if (VCTRL_OK == VCTRL_CmpConfigParameter(ChanID, pstCfg))
    {
        dprint(PRN_FATAL,"VCTRL_ConfigChan with same config paramater.\n");
        return VCTRL_OK;
    }

    /* 对配置信息进行必要的过滤，主要处理各项配置之间的关联约束 */
    if (pstCfg->s32DecMode == 2)
    {
        //pstCfg->s32ChanErrThr = 0;   //z56361, 20110825: quyaxin建议把这个配置交给客户，下面不要做死了
    }

    /* 保存通道配置 */
    memcpy( &s_pstVfmwChan[ChanID]->stChanCfg, pstCfg, sizeof(VDEC_CHAN_CFG_S) );
    s_pstVfmwChan[ChanID]->s32Priority = pstCfg->s32ChanPriority;
    s_pstVfmwChan[ChanID]->eVidStd = pstCfg->eVidStd;

    // 配置SCD通道
    memset(&ScdInstCfg, 0, sizeof(SM_CFG_S));
    ScdInstCfg.BufPhyAddr  = s_pstVfmwChan[ChanID]->s32ScdChanMemAddr;
    ScdInstCfg.pBufVirAddr = (UINT8*)MEM_Phy2Vir(s_pstVfmwChan[ChanID]->s32ScdChanMemAddr);
    ScdInstCfg.BufSize     = s_pstVfmwChan[ChanID]->s32ScdChanMemSize;
    ScdInstCfg.Priority    = pstCfg->s32ChanPriority;
    ScdInstCfg.VidStd      = pstCfg->eVidStd;

    if (1 == pstCfg->s8IsOmxPath)
    {
        ScdInstCfg.IsOmxPath        = pstCfg->s8IsOmxPath;
        ScdInstCfg.SpecMode         = pstCfg->s8SpecMode;
        ScdInstCfg.MaxRawPacketNum  = pstCfg->s32MaxRawPacketNum;
        ScdInstCfg.MaxRawPacketSize = pstCfg->s32MaxRawPacketSize;
    }
#ifdef VFMW_SCD_LOWDLY_SUPPORT
    /* 对低延迟标志进行检测，如果非H264协议配置成了低延迟模式，需强制配成非低延迟模式 */
    ScdInstCfg.ScdLowdlyEnable = (VFMW_H264 != pstCfg->eVidStd)? 0 : pstCfg->s8LowdlyEnable;
#else
    ScdInstCfg.ScdLowdlyEnable = 0;
#endif

    memcpy(&ScdInstCfg.StdExt, &pstCfg->StdExt, sizeof(STD_EXTENSION_U));
    SM_Config(ChanID, &ScdInstCfg);

    // 配置帧存实例
    memset(&FspInstCfg, 0, sizeof(FSP_ATTR_S));
    if (1 == pstCfg->s8IsOmxPath)
    {
        FspInstCfg.IsOmxPath = 1;
        FSP_ConfigAttribute(ChanID, &FspInstCfg);
    }

    // 配置syntax
    s_pstVfmwChan[ChanID]->stSynExtraData.s32ContextMemAddr = s_pstVfmwChan[ChanID]->stChanMem_ctx.PhyAddr;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32ContextMemSize = s_pstVfmwChan[ChanID]->stChanMem_ctx.Length;

    s_pstVfmwChan[ChanID]->stSynExtraData.s32SyntaxMemAddr = s_pstVfmwChan[ChanID]->s32VdmChanMemAddr;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32SyntaxMemSize = s_pstVfmwChan[ChanID]->s32VdmChanMemSize;

    s_pstVfmwChan[ChanID]->stSynExtraData.s32BpdMemAddr = s_pstVfmwChan[ChanID]->s32BpdChanMemAddr;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32BpdMemSize = s_pstVfmwChan[ChanID]->s32BpdChanMemSize;

    s_pstVfmwChan[ChanID]->stSynExtraData.s32Vp8SegIdMemAddr = s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemAddr;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32Vp8SegIdMemSize= s_pstVfmwChan[ChanID]->s32Vp8SegIdChanMemSize;

    s_pstVfmwChan[ChanID]->stSynExtraData.s32OutErrThr = pstCfg->s32ChanErrThr;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32RefErrThr = pstCfg->s32ChanErrThr;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32DecMode = pstCfg->s32DecMode;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32DecOrderOutput = pstCfg->s8DecOrderOutput;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32Compress_en = pstCfg->s8VcmpEn;

    s_pstVfmwChan[ChanID]->stSynExtraData.s32SupportAllP = (1 == pstCfg->s8SupportAllP)? 1: 0;
    s_pstVfmwChan[ChanID]->stSynExtraData.s8SpecMode = pstCfg->s8SpecMode;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32ModuleLowlyEnable  = pstCfg->s8ModuleLowlyEnable;
    s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag = 0;
    memcpy(&s_pstVfmwChan[ChanID]->stSynExtraData.StdExt, &pstCfg->StdExt, sizeof(STD_EXTENSION_U));

    if( s_pstVfmwChan[ChanID]->stSynCtx.eVidStd != s_pstVfmwChan[ChanID]->eVidStd )
    {
        VCTRL_ResetChan(ChanID);
    }
    s_pstVfmwChan[ChanID]->stSynCtx.eVidStd = s_pstVfmwChan[ChanID]->eVidStd;

    // 刷新VDMDRV的优先级排序表
    for(i=0; i<MAX_CHAN_NUM; i++)
    {
        if( NULL != s_pstVfmwChan[i] )
        {
            PrioArray[i] = s_pstVfmwChan[i]->s32Priority;
            g_ChanCtx.PriorByChanId[i] = s_pstVfmwChan[i]->s32Priority;
        }
        else
        {
            PrioArray[i] = 0;
            g_ChanCtx.PriorByChanId[i] = 0;
        }
    }
    VDMDRV_SetPriority(PrioArray);
    VDMDRV_ClearChanIsDec(ChanID);//标记此通道未被解码

    return VCTRL_OK;
}


/***********************************************************************
   VCTRL_LoadDspCode: 有两种情况需要加载DSP代码，
   1. H264 低延迟；
   2. AVS
   3. AVS 与 低延迟不能共存
 ***********************************************************************/
#if defined(VFMW_SCD_LOWDLY_SUPPORT) || defined(VFMW_AVSPLUS_SUPPORT)
SINT32 VCTRL_LoadDspCode(SINT32 ChanID)
{
    SINT32 i = 0;
    SINT32 ret = VCTRL_OK;
    DSP_STATE_E eDSPState = DSP_STATE_NORMAL;
    VDEC_CHAN_CFG_S stCfgInfo;
    SINT32 ScdLowdlyEnable = 0;

    memset(&stCfgInfo, 0, sizeof(VDEC_CHAN_CFG_S));

    ret = VCTRL_GetChanCfg(ChanID, &stCfgInfo);
    if(VCTRL_OK !=ret)
    {
        dprint(PRN_FATAL,"vfmw_ctrl.c,L%d: VCTRL_GetChanCfg error\n", __LINE__);
        return VCTRL_ERR;
    }

    /* 对低延迟标志进行检测，如果非H264协议配置成了低延迟模式，需强制配成非低延迟模式 */
    ScdLowdlyEnable = (VFMW_H264 != stCfgInfo.eVidStd)? 0 : stCfgInfo.s8LowdlyEnable;

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (DSP_STATE_NORMAL != g_DSPState[i])
        {
            eDSPState = g_DSPState[i];
            break;
        }
    }

    // 如果之前有一通道为AVS, 当前通道又是低延迟，这种情况直接返回错误，反之亦然
    if (((1 == ScdLowdlyEnable) && (DSP_STATE_AVS == eDSPState)) ||
        ((VFMW_AVS == stCfgInfo.eVidStd) && (DSP_STATE_SCDLOWDLY == eDSPState)))
    {
        dprint(PRN_ALWS, "WARNNING: ScdLowdlyEnable = %d, VidStd = %d, eDSPState = %d AVS(+) and LOWDLY  cannot supported in the same time!!!\n",
            ScdLowdlyEnable, stCfgInfo.eVidStd, eDSPState);
        return VCTRL_ERR;
    }

    // l00232354: S5V100 低功耗处理，解码通道工作时，VDH时钟打开，销毁时，VDH时钟关掉: 此时是配置通道，VDH时钟还
    // 没有打开，但加载VFMW BIN 文件时，需要有时钟才能工作，故在这里打开和关闭。
    VCTRL_OpenHardware(ChanID);

    //1. 如果是SCD低延迟，且之前没有加载DSP代码时，这时候得加载 SCD DSP代码
    //2. 如果是AVS，且之前没有加载DSP代码时，这时候得加载 AVS DSP代码
    if ((1 == ScdLowdlyEnable) && (DSP_STATE_NORMAL == eDSPState))
    {
        WriteHexFile(stCfgInfo.eVidStd);
        g_DSPState[ChanID] = DSP_STATE_SCDLOWDLY;
    }
    else if ((VFMW_AVS == stCfgInfo.eVidStd) && (DSP_STATE_NORMAL == eDSPState))
    {
        dprint(PRN_ALWS, "WriteHexFile Avs Hex\n");
        WriteHexFile(stCfgInfo.eVidStd);
        g_DSPState[ChanID] = DSP_STATE_AVS;
    }
    else
    {
        ;
    }

    VCTRL_CloseHardware();

    return ret;
}
#endif

/***********************************************************************
   VCTRL_ReleaseStream: 释放raw buffer
 ***********************************************************************/
SINT32 VCTRL_ReleaseStream(SINT32 ChanID)
{
    SINT32 ret;
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "Chan inactive");
    /* 复位SCD实例 */
    ret = SM_Reset(ChanID);

    return (ret == FMW_OK)?  VCTRL_OK: VCTRL_ERR;
}

/***********************************************************************
   VCTRL_InitSyntaxCtx: 初始化各协议语法上下文
 ***********************************************************************/
VOID VCTRL_InitSyntaxCtx(SINT32 ChanID)
{
    VCTRL_ASSERT( NULL != s_pstVfmwChan[ChanID], "Chan inactive");

    switch( s_pstVfmwChan[ChanID]->eVidStd )
    {
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            MPEG2DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stMpeg2Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            MPEG4DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stMpeg4Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            H264DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stH264Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
	#ifdef VFMW_HEVC_SUPPORT
        case VFMW_HEVC:
            HEVCDEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stHevcCtx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
	#endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            AVSDEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stAvsCtx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            REAL8DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stReal8Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            REAL9DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stReal9Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            DIVX3DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stDivx3Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            VC1DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stVc1Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
        case VFMW_VP6:
        case VFMW_VP6F:
        case VFMW_VP6A:
            VP6DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stVp6Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            VP8DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stVp8Ctx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            MVC_DEC_Init(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stMvcCtx, &s_pstVfmwChan[ChanID]->stSynExtraData);
            break;
    #endif
        default:
            break;
    }

    return;
}

/***********************************************************************
   VCTRL_ResetChanWithOption: 复位通道有选择地保留某些特性
 ***********************************************************************/
SINT32 VCTRL_ResetChanWithOption(SINT32 ChanID, VDEC_CHAN_RESET_OPTION_S *pOption)
{
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "Chan inactive");

    /* 初始化VDMDRV */
    memset( &g_VfmwChanStat[ChanID], 0, sizeof(VFMW_CHAN_STAT_S) );

    /* 复位syntax上下文 */
    s_pstVfmwChan[ChanID]->stSynExtraData.s32KeepSPSPPS = pOption->s32KeepSPSPPS;
    VCTRL_InitSyntaxCtx(ChanID);

    /* 清除当前SEG */
    memset(&s_pstVfmwChan[ChanID]->stSynExtraData.stSegPacket, 0, sizeof(STREAM_SEG_PACKET_S));
    s_pstVfmwChan[ChanID]->stSynExtraData.pts = (UINT64)(-1);
    s_pstVfmwChan[ChanID]->stSynExtraData.NextPts = (UINT64)(-1);
    s_pstVfmwChan[ChanID]->stSynExtraData.s32NewPicSegDetector = 0;

    /* 当复位通道后就不能再次重送之前数据 l00273086 */
    if(1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn)
    {
        s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag = 0;
    }

    /* 复位FSP实例 */
    if (1 == pOption->s32KeepFSP)
    {
        FSP_EmptyInstance(ChanID);
    }
    else
    {
        FSP_ResetInstance(ChanID);
    }

    /* 初始化user data pool实例 */
    InitUsdPool(ChanID);

    if (pOption->s32KeepBS == 0)
    {
        /* 复位SCD实例 */
        SM_Reset(ChanID);
        
        /* 重置正在为该通道工作的SCD */
        SCDDRV_ResetSCD(ChanID);
    }

    /* 重置正在为该通道工作的VDH */
    VDMDRV_ResetVDH(ChanID);

    /* 标记此通道未被解码 */
    VDMDRV_ClearChanIsDec(ChanID);

    /* 调试: 单独保存复位后码流 */
    if(g_ResetCreateNewSave)
    {
        if (vfmw_save_str_file != NULL)
        {
            VCTRL_SetDbgOption(0x200, (UINT8*)&ChanID);
        }

        if (vfmw_save_str_file == NULL)
        {
            VCTRL_SetDbgOption(0x200, (UINT8*)&ChanID);
        }
    }

    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_ResetChan: 复位通道
 ***********************************************************************/
SINT32 VCTRL_ResetChan(SINT32 ChanID)
{
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "Chan inactive");

    /* 初始化VDMDRV */
    memset( &g_VfmwChanStat[ChanID], 0, sizeof(VFMW_CHAN_STAT_S) );

    /* 复位低延相关信息 */
#ifdef VFMW_SCD_LOWDLY_SUPPORT
    memset(g_stLowdlyInfo, 0, sizeof(LOWDLY_INFO_S)*MAX_CHAN_NUM);
#endif
    /* 复位syntax上下文 */
    s_pstVfmwChan[ChanID]->stSynExtraData.s32KeepSPSPPS = 0;
    VCTRL_InitSyntaxCtx(ChanID);

    /* 清除当前SEG */
    memset(&s_pstVfmwChan[ChanID]->stSynExtraData.stSegPacket, 0, sizeof(STREAM_SEG_PACKET_S));
    s_pstVfmwChan[ChanID]->stSynExtraData.pts = (UINT64)(-1);
    s_pstVfmwChan[ChanID]->stSynExtraData.NextPts = (UINT64)(-1);
    s_pstVfmwChan[ChanID]->stSynExtraData.s32NewPicSegDetector = 0;

    /* 当复位通道后就不能再次重送之前数据 l00273086 */
    if(1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn)
    {
        s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag = 0;
    }

    /* 复位FSP实例 */
    FSP_ResetInstance(ChanID);

    /* 初始化user data pool实例 */
    InitUsdPool(ChanID);

    /* 复位SCD实例 */
    SM_Reset(ChanID);

    /* 重置正在为该通道工作的SCD */
    SCDDRV_ResetSCD(ChanID);
    
    /* 重置正在为该通道工作的VDH */
    VDMDRV_ResetVDH(ChanID);
    
    /* 标记此通道未被解码 */
    VDMDRV_ClearChanIsDec(ChanID);

    /* 调试: 单独保存复位后码流 */
    if(g_ResetCreateNewSave)
    {
        if (vfmw_save_str_file != NULL)
        {
            VCTRL_SetDbgOption(0x200, (UINT8*)&ChanID);
        }

        if (vfmw_save_str_file == NULL)
        {
            VCTRL_SetDbgOption(0x200, (UINT8*)&ChanID);
        }
    }

    return VCTRL_OK;
}

/***********************************************************************
   VCTRL_GetChanImage: 获取通道图像
 ***********************************************************************/
SINT32 VCTRL_GetChanImage( SINT32 ChanID, IMAGE *pImage )
{
    SINT32 ret;
    SINT8  SpecMode;
    VID_STD_E eVidStd; 
#ifdef VFMW_MVC_SUPPORT
    IMAGE  Image_1;
    IMAGE *pimage_1 = NULL;
    UINT32 last_frame_flag = 0;
    pimage_1 = &Image_1;
#endif

    VCTRL_ASSERT_RET(ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( NULL !=s_pstVfmwChan[ChanID], "Chan inactive");

    /*虽然已经停止了该通道解码，但是由于通道信息都是齐全的，所以可以进行获取、释放帧存的操作l00165842*/
    VCTRL_ASSERT_RET(1 == s_pstVfmwChan[ChanID]->s32IsOpen, "This channel is not opened");

    VFMW_OSAL_SpinLock(G_SPINLOCK_DESTROY);

    if (NULL ==s_pstVfmwChan[ChanID])
    {
        dprint(PRN_FATAL,"vdm_ctrl.c,L%d: Chan inactive\n", __LINE__);
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);
        return VCTRL_ERR;
    }
    if (1 != s_pstVfmwChan[ChanID]->s32IsOpen)
    {
        dprint(PRN_FATAL,"vdm_ctrl.c,L%d: This channel is not opened\n", __LINE__);
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);
        return VCTRL_ERR;
    }

    ret = SYNTAX_ReceiveImage(&s_pstVfmwChan[ChanID]->stSynCtx, pImage);

#ifdef VFMW_MVC_SUPPORT
    if (VF_OK == ret)
    {
        pImage->image_id_1 = -1;
        if (pImage->is_3D == 1)
        {
            /* 正常情况下base view不应该是最后一帧，所以这里设置特殊标志，下面处理 */
            if (pImage->last_frame)
            {
                last_frame_flag = 1;
            }
            else
            {
                ret = SYNTAX_ReceiveImage(&s_pstVfmwChan[ChanID]->stSynCtx, pimage_1);
                if (ret != VF_OK )
                {
                    SYNTAX_ReturnImage(&s_pstVfmwChan[ChanID]->stSynCtx);
                    VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);
                    return ret;
                }
                else
                {
                    if (pImage->view_id < pimage_1->view_id)
                    {
                        pImage->top_chrom_phy_addr_1 = pimage_1->top_chrom_phy_addr;
                        pImage->top_luma_phy_addr_1  = pimage_1->top_luma_phy_addr;
                        pImage->btm_luma_phy_addr_1  = pimage_1->btm_luma_phy_addr;
                        pImage->btm_chrom_phy_addr_1 = pimage_1->btm_chrom_phy_addr;
                        pImage->image_id_1 = pimage_1->image_id;
                        pImage->eFramePackingType = FRAME_PACKING_TYPE_TIME_INTERLACED;

                        if (pimage_1->last_frame)
                        {
                            pImage->last_frame = 1;
                        }
                        ret = VF_OK;
                        //dprint(PRN_ALWS,"success out: view_0 id(%d), view_1 id(%d)\n", p_image->view_id, p_image_1->view_id);
                    }
                    else if (pImage->view_id > pimage_1->view_id)
                    {
                        SYNTAX_ReturnImage(&s_pstVfmwChan[ChanID]->stSynCtx);
                        SYNTAX_ReleaseImage(&s_pstVfmwChan[ChanID]->stSynCtx, pImage);
                        dprint(PRN_ERROR,"%s: view_0 id(%d) > view_1 id(%d), error!\n", __func__, pImage->view_id, pimage_1->view_id);
                        ret = VF_ERR_PARAM;
                    }
                    else // p_image->view_id == p_image_1->view_id
                    {
                        if (pImage->view_id == 0)  // view 0
                        {
                            SYNTAX_ReturnImage(&s_pstVfmwChan[ChanID]->stSynCtx);
                            SYNTAX_ReleaseImage(&s_pstVfmwChan[ChanID]->stSynCtx, pImage);
                            dprint(PRN_ERROR,"%s: continuous view0 id(%d)!\n", __func__, pImage->view_id);
                        }
                        else  // view 1
                        {
                            SYNTAX_ReleaseImage(&s_pstVfmwChan[ChanID]->stSynCtx, pImage);
                            if (pimage_1->last_frame)
                            {
                                last_frame_flag = 2;
                            }
                            else
                            {
                                SYNTAX_ReleaseImage(&s_pstVfmwChan[ChanID]->stSynCtx, pimage_1);
                            }
                            dprint(PRN_ERROR,"%s: continuous view1 id(%d)!\n", __func__, pImage->view_id);
                        }
                        ret = VF_ERR_PARAM;
                    }
                }
            }

            /* 判断是否捕捉到不匹配的最后一帧，单帧变两帧后输出 */
            switch (last_frame_flag)
            {
                case 1:  // base view 是最后一帧
                    pImage->top_chrom_phy_addr_1 = pImage->top_chrom_phy_addr;
                    pImage->top_luma_phy_addr_1 = pImage->top_luma_phy_addr;
                    pImage->image_id_1 = -1;
                    pImage->eFramePackingType = FRAME_PACKING_TYPE_TIME_INTERLACED;
                    pImage->last_frame = 1;
                    ret = VF_OK;
                    break;

                case 2: // dependent view 是最后一帧
                    memcpy(pImage, pimage_1, sizeof(IMAGE));
                    pImage->top_chrom_phy_addr_1 = pimage_1->top_chrom_phy_addr;
                    pImage->top_luma_phy_addr_1 = pimage_1->top_luma_phy_addr;
                    pImage->image_id_1 = -1;
                    pImage->eFramePackingType = FRAME_PACKING_TYPE_TIME_INTERLACED;
                    pImage->last_frame = 1;
                    ret = VF_OK;
                    break;

                default:
                    break;
           }
       }
    }
#endif

    // Performance Calculation
    {
        static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
        UINT32 currtime = 0;
        UINT32 dat = 0;

        if (CHECK_REC_POS_ENABLE(STATE_VO_RCV_IMG))
        {
            currtime = VFMW_OSAL_GetTimeInMs();
            if ((currtime - last_rec_pos_time[ChanID]) > g_TraceImgPeriod)
            {
                last_rec_pos_time[ChanID] = currtime;
                dat = ((ChanID)<<24) + (STATE_VO_RCV_IMG<<16) + (ret==VF_OK);
                REC_POS(dat);
            }
        }
    }

    ret = (ret==VF_OK)? VCTRL_OK: VCTRL_ERR;
#ifdef VFMW_SCD_LOWDLY_SUPPORT
    if(VCTRL_OK == ret)
    {
        DBG_CountTimeInfo(ChanID, STATE_VO_RCV_IMG, 0);
    }
#endif

    if(VCTRL_OK == ret)
    {
        s_pstVfmwChan[ChanID]->stRecentImgformat      = pImage->format;
        s_pstVfmwChan[ChanID]->stRecentImgPackingType = pImage->eFramePackingType;
    }
    eVidStd  = s_pstVfmwChan[ChanID]->eVidStd;
    SpecMode = s_pstVfmwChan[ChanID]->stChanCfg.s8SpecMode;

    VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);
    
    if (VCTRL_OK == ret)
    {
#ifdef ENV_ARMLINUX_KERNEL
        if (vfmw_save_yuv_file != NULL && save_yuv_chan_num == ChanID)
        {
            OSAL_WriteYuv(eVidStd, pImage, vfmw_save_yuv_file, save_yuv_with_crop);
        #ifdef VFMW_MVC_SUPPORT
            if (1 == pImage->is_3D)
            {
                OSAL_WriteYuv(eVidStd, pimage_1, vfmw_save_yuv_file, save_yuv_with_crop);
            }
        #endif
        }

        /* Calc frame CRC value in CRC check mode */
        if (1 == SpecMode)
        {
            VCTRL_CalcActualCrc(eVidStd, pImage);
        }
#endif
    }

    return ret;
}

/***********************************************************************
   VCTRL_ReleaseChanImage: 释放通道图像
 ***********************************************************************/
SINT32 VCTRL_ReleaseChanImage( SINT32 ChanID, IMAGE *pImage )
{
    SINT32 ret;
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
    UINT32 currtime = 0;
    UINT32 dat = 0;
#ifdef VFMW_MVC_SUPPORT
    IMAGE Image_1;
#endif

    VCTRL_ASSERT_RET(ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET(NULL != s_pstVfmwChan[ChanID], "Chan inactive");
    VCTRL_ASSERT_RET(1 == s_pstVfmwChan[ChanID]->s32IsOpen, "This channel is not opened");
    VCTRL_ASSERT_RET(pImage != NULL, "pImage is NULL");
    dprint(PRN_CTRL, "call VCTRL_ReleaseChanImage, ChanID, ImgID = %d,%d\n", ChanID, pImage->image_id);

    VFMW_OSAL_SpinLock(G_SPINLOCK_DESTROY);

    if (NULL ==s_pstVfmwChan[ChanID])
    {
        dprint(PRN_FATAL,"vdm_ctrl.c,L%d: Chan inactive\n", __LINE__);
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);
        return VCTRL_ERR;
    }
    if (1 != s_pstVfmwChan[ChanID]->s32IsOpen)
    {
        dprint(PRN_FATAL,"vdm_ctrl.c,L%d: This channel is not opened\n", __LINE__);
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);
        return VCTRL_ERR;
    }

    ret = SYNTAX_ReleaseImage(&s_pstVfmwChan[ChanID]->stSynCtx, pImage);

#ifdef VFMW_MVC_SUPPORT
    if (pImage->image_id_1 != -1)
    {
        Image_1.image_id = pImage->image_id_1;
        ret = SYNTAX_ReleaseImage(&s_pstVfmwChan[ChanID]->stSynCtx, &Image_1);
    }
#endif

    // Performance Calculation
    if (CHECK_REC_POS_ENABLE(STATE_VO_REL_IMG))
    {
        currtime = VFMW_OSAL_GetTimeInMs();
        if ((currtime - last_rec_pos_time[ChanID]) > g_TraceImgPeriod)
        {
            last_rec_pos_time[ChanID] = currtime;
            dat = ((ChanID)<<24) + (STATE_VO_REL_IMG<<16) + (ret==VF_OK);
            REC_POS(dat);
        }
    }

    ret = (ret==VF_OK)? VCTRL_OK: VCTRL_ERR;

    VFMW_OSAL_SpinUnLock(G_SPINLOCK_DESTROY);

    return ret;
}


/***********************************************************************
   VCTRL_GetVidStd: 查询指定通道的协议类型
 ***********************************************************************/
VID_STD_E VCTRL_GetVidStd(SINT32 ChanId)
{
    if( ChanId<0 || ChanId>=MAX_CHAN_NUM || NULL ==s_pstVfmwChan[ChanId])
    {
        dprint(PRN_FATAL, "vfmw_ctrl.c, line %d: ChanID out of range\n", __LINE__);
        return VFMW_END_RESERVED;
    }

    /* z56361, 20111101, 通道停止后，只要没关闭，协议类型还应当保持，否则软解码协议在通道停止后无法释放图象. */
    if( 1 != s_pstVfmwChan[ChanId]->s32IsOpen /*|| 1 != s_pstVfmwChan[ChanId]->s32IsRun*/ )
    {
        dprint(PRN_FATAL, "vfmw_ctrl.c, line %d: Chan %d is not open or not running\n",__LINE__, ChanId);
        return VFMW_END_RESERVED;
    }

    return s_pstVfmwChan[ChanId]->eVidStd;
}

/***********************************************************************
   VCTRL_GetDecParam: 获取指定通道的解码参数(VDM解码所需参数)
 ***********************************************************************/
VOID *VCTRL_GetDecParam(SINT32 ChanId)
{
    VID_STD_E VidStd;
    VOID *pDecParam = (VOID*)NULL;

    if( ChanId<0 || ChanId>=MAX_CHAN_NUM || NULL==s_pstVfmwChan[ChanId])
    {
        dprint(PRN_DBG, "vfmw_ctrl.c, line %d: ChanID out of range is %d\n", __LINE__,ChanId);
        return NULL;
    }

    if( 1 != s_pstVfmwChan[ChanId]->s32IsOpen || 1 != s_pstVfmwChan[ChanId]->s32IsRun )
    {
        //dprint(PRN_FATAL, "Chan %d is not open or not running\n", ChanId);
        return NULL;
    }

    VidStd = s_pstVfmwChan[ChanId]->eVidStd;

    switch (VidStd)
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stH264Ctx.pH264DecParam);
            break;
    #endif
	#ifdef VFMW_HEVC_SUPPORT
		case VFMW_HEVC:
		    pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stHevcCtx.pHevcDecParam);
		    break;
	#endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg2Ctx.pMp2DecParam);
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg4Ctx.pMp4DecParam);
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stAvsCtx.pAvsDecParam);
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal8Ctx.pRv8DecParam);
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal9Ctx.pRv9DecParam);
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stDivx3Ctx.pDivx3DecParam);
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVc1Ctx.pVc1DecParam);
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp8Ctx.pVp8DecParam);
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
        case VFMW_VP6:
        case VFMW_VP6F:
        case VFMW_VP6A:
            if(0 != (g_VdmCharacter & VDM_SUPPORT_VP6))
            {
                pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp6Ctx.pVp6DecParam);
            }
            else
            {
                pDecParam = (VOID *)NULL;
            }
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            pDecParam = (VOID *)(s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMvcCtx.pMvcDecParam);
            break;
    #endif
        default:
            //dprint(PRN_FATAL, "VidStd=%d Error!\n", VidStd);
            pDecParam = (VOID *)NULL;
            break;
    }

    if (pDecParam != (VOID*)NULL)
    {
        s_pstVfmwChan[ChanId]->u32timeLastDecParamReady = VFMW_OSAL_GetTimeInMs();
    }

    return pDecParam;
}

VOID VCTRL_PostProc( SINT32 ChanId, SINT32 ErrRatio, UINT32 Mb0QpInCurrPic, LUMA_INFO_S *pLumaInfo,SINT32 VdhId)
{
    VID_STD_E VidStd;
    SINT32 ModuleLowlyEnable = 0;
    VCTRL_ASSERT( NULL !=s_pstVfmwChan[ChanId], "Chan inactive");
    VidStd = s_pstVfmwChan[ChanId]->eVidStd;


#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (NULL != s_pstVfmwChan[ChanId])
    {
        ModuleLowlyEnable = s_pstVfmwChan[ChanId]->stSynExtraData.s32ModuleLowlyEnable;
    }
    else
    {
        ModuleLowlyEnable = 0;
    }
#endif

    switch (VidStd)
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
         H264DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stH264Ctx, ErrRatio, 1, pLumaInfo,ModuleLowlyEnable,VdhId);
         if(1 == s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag)
         {
          VCTRL_OutputLastFrame(ChanId);
          s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stH264Ctx.IsStreamEndFlag = 0;
         }
         //模块间低延时在解码完成中断中清除pH264DecParam，此位置的代码是在行号中断中执行到的
         if(1 != ModuleLowlyEnable)
         {
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stH264Ctx.pH264DecParam = NULL;  ///--- 同下
         }
         break;
    #endif
    #ifdef VFMW_HEVC_SUPPORT
        case VFMW_HEVC:
         HEVCDEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stHevcCtx, ErrRatio, 1,pLumaInfo,ModuleLowlyEnable,VdhId);
	     if(1 == s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag)//最后一帧,输出 l00214825
	     {
             VCTRL_OutputLastFrame(ChanId);
             s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stHevcCtx.IsStreamEndFlag = 0;
	     }
         //模块间低延时在解码完成中断中清除pH264DecParam，此位置的代码是在行号中断中执行到的
         s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stHevcCtx.pHevcDecParam = NULL;
         break;
    #endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
         MPEG2DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg2Ctx, ErrRatio );
         if(1 == s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg2Ctx.IsStreamEndFlag)
         {
          VCTRL_OutputLastFrame(ChanId);
          s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg2Ctx.IsStreamEndFlag = 0;
         }
         s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg2Ctx.pMp2DecParam = NULL;   ///--- 最好放在MPEG2DEC_VDMPostProc内部
         break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            MPEG4DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg4Ctx, ErrRatio, pLumaInfo);
         if(1 == s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag)
         {
          VCTRL_OutputLastFrame(ChanId);
          s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg4Ctx.IsStreamEndFlag = 0;
         }
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg4Ctx.pMp4DecParam = NULL;  ///--- 同上
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            AVSDEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stAvsCtx, ErrRatio );
         if(1 == s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stAvsCtx.IsStreamEndFlag)
         {
          VCTRL_OutputLastFrame(ChanId);
          s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stAvsCtx.IsStreamEndFlag = 0;
         }
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stAvsCtx.pAvsDecParam = NULL;  ///--- 同上
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            REAL8DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal8Ctx, ErrRatio, Mb0QpInCurrPic );
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal8Ctx.pRv8DecParam = NULL;  ///--- 同上
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            REAL9DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal9Ctx, ErrRatio, Mb0QpInCurrPic );
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal9Ctx.pRv9DecParam = NULL;  ///--- 同上
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            DIVX3DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stDivx3Ctx, ErrRatio, Mb0QpInCurrPic );
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stDivx3Ctx.pDivx3DecParam = NULL;  ///--- 同上
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            VC1DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVc1Ctx, ErrRatio);
            if(1 == s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVc1Ctx.CodecInfo.IsStreamEndFlag)
            {
                VCTRL_OutputLastFrame(ChanId);
                s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVc1Ctx.CodecInfo.IsStreamEndFlag = 0;
            }
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVc1Ctx.pVc1DecParam = NULL;  ///--- 同下
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
        case VFMW_VP6:
        case VFMW_VP6A:
        case VFMW_VP6F:
            VP6DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp6Ctx, ErrRatio);
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp6Ctx.pVp6DecParam = NULL;  ///--- 同下
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            VP8DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp8Ctx, ErrRatio);
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp8Ctx.pVp8DecParam = NULL;  ///--- 同下
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            MVC_DEC_VDMPostProc( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMvcCtx, ErrRatio, 1 );
         if(1 == s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag)
         {
          VCTRL_OutputLastFrame(ChanId);
          s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMvcCtx.IsStreamEndFlag = 0;
         }
            s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMvcCtx.pMvcDecParam = NULL;  ///--- 同下
            break;
    #endif
        default:
            //dprint(PRN_FATAL, "VidStd=%d Error!\n", VidStd);
            break;
    }

    return;
}

/***********************************************************************
   VCTRL_VdmPostProc: 对指定通道做解码后处理
 ***********************************************************************/
VOID VCTRL_VdmPostProc( SINT32 ChanId, SINT32 ErrRatio, UINT32 Mb0QpInCurrPic, LUMA_INFO_S *pLumaInfo,SINT32 VdhId )
{
    VCTRL_ASSERT(ChanId>=0 && ChanId<MAX_CHAN_NUM, "ChanId out of range");
    VCTRL_ASSERT(NULL != s_pstVfmwChan[ChanId], "This channel is not opened");
    VCTRL_ASSERT(1 == s_pstVfmwChan[ChanId]->s32IsRun, "This channel is not running");

    /* 防止syntax已经复位，但VDMDRV随后发生中断从而造成错误 */
    if( NULL == VCTRL_GetDecParam(ChanId) )
    {
        return;
    }

    VCTRL_PostProc (ChanId, ErrRatio, Mb0QpInCurrPic, pLumaInfo,VdhId);
	
    return;
}

SINT32 VCTRL_GetImageBuffer( SINT32 ChanId )
{
    VID_STD_E VidStd;
    SINT32 Ret = 0;  // 0: imgbuf not available, 1: imgbuf available

    VCTRL_ASSERT_RET(ChanId>=0 && ChanId<MAX_CHAN_NUM, "ChanId out of range");
    VCTRL_ASSERT_RET(NULL != s_pstVfmwChan[ChanId], "This channel is not opened");
    VCTRL_ASSERT_RET(1 == s_pstVfmwChan[ChanId]->s32IsRun, "This channel is not running");

    VidStd = s_pstVfmwChan[ChanId]->eVidStd;

    switch (VidStd)
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            Ret = H264DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stH264Ctx );
            break;
    #endif
    #ifdef VFMW_HEVC_SUPPORT
        case VFMW_HEVC:
            Ret = HEVCDEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stHevcCtx );
            break;
    #endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            Ret = MPEG2DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg2Ctx );
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            Ret = MPEG4DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg4Ctx );
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            Ret = AVSDEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stAvsCtx );
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            Ret = REAL8DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal8Ctx );
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            Ret = REAL9DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal9Ctx );
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            Ret = DIVX3DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stDivx3Ctx );
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            Ret = VC1DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVc1Ctx );
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
        case VFMW_VP6:
        case VFMW_VP6F:
        case VFMW_VP6A:
            if(0 != (g_VdmCharacter & VDM_SUPPORT_VP6))
            {
                Ret = VP6DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp6Ctx );
            }
            else
            {
                Ret = 1;
            }
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            Ret = VP8DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp8Ctx );
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            Ret = MVC_DEC_GetImageBuffer( &s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMvcCtx );
            break;
    #endif
        default:
            //dprint(PRN_FATAL, "VidStd=%d Error!\n", VidStd);
            break;
    }

    return Ret;
}

/* 判断指定通道能否解码
   如果通道码流seg充足，framestore有空闲，则这个通道就是可解码的 */
SINT32  VCTRL_IsChanDecable( SINT32 ChanID )
{
    SINT32 ret = VCTRL_ERR;
    SM_INST_INFO_S  SmInstInfo;

    if (s_pstVfmwChan[ChanID] == NULL)
    {
        return VCTRL_ERR;
    }

    if( FMW_OK == SM_GetInfo(ChanID, &SmInstInfo) )
    {
        /* 如果码流seg充足 */
        if( SmInstInfo.SegNum > 16 || SmInstInfo.TotalSegSize > 512*1024 )
        {
            if( 1 == VCTRL_GetImageBuffer(ChanID) )
            {
                ret = VCTRL_OK;
            }
        }
    }

    if (VCTRL_OK == ret)
    {
        UINT32 timeNow = (UINT32)VFMW_OSAL_GetTimeInMs();
        UINT32 timeLastReady = s_pstVfmwChan[ChanID]->u32timeLastDecParamReady;
        UINT32 timePeriod;

        /** 如果该通道距上一次产生有效的DecParam已经超过了50ms，说明该通道虽然"看起来"可解，但肯定有问题，
            实际上应该认为不可解，以免它耽误其它可解的通道
         */
        timePeriod = timeNow - timeLastReady;
        if(timePeriod > 50)
        {
            ret = VCTRL_ERR;
        }
    }

    return ret;
}

/* 判断指定通道码流seg是否充足 */
SINT32  VCTRL_IsChanSegEnough( SINT32 ChanID )
{
    SINT32 ret = 0;

    if (s_pstVfmwChan[ChanID]->s32NoStreamFlag == 1)
    {
        ret = 0;
    }
    else
    {
        ret = 1;
    }

    return ret;
}

/* 判定制定通道是否激活
   如果通道未激活，但中断服务程序发生时却指向这个通道，说明中断是误触发，
此时照常往下走会带来不可预测的问题，所以在ISR有必要先判断其指向的通道是否是激活的。
   中断误触发的一个例子是: 待机后唤起，此时硬件可能不稳定 */
SINT32  VCTRL_IsChanActive( SINT32 ChanID )
{

    if( ChanID < 0 || ChanID >= MAX_CHAN_NUM || NULL == s_pstVfmwChan[ChanID] )
    {
        return VCTRL_ERR;
    }
    else if ( (s_pstVfmwChan[ChanID]->s32IsOpen == 0) ||
               (s_pstVfmwChan[ChanID]->s32IsRun == 0)  ||
               (s_pstVfmwChan[ChanID]->s32Priority == 0) ||
               (s_pstVfmwChan[ChanID]->eVidStd == VFMW_END_RESERVED) )
    {
        return VCTRL_ERR;
    }

    return VCTRL_OK;
}

SINT32 VCTRL_GetChanMemSizeWithOption(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, DETAIL_MEM_SIZE *pDetailMemSize,SINT32 flag)
{
    SINT32 PmvNum, FrameNum;
    VDMHAL_MEM_ARRANGE_S MemArrange;
    SINT32 ret;
    SINT32 TempRefNum,TempDispNum;
    SINT32 s32ChanCtxSize = 0;
    UINT32 TempAddMem = 0;
	ARRANGE_FLAG_E eFlag = INVALID_CHAN_ID;

    VCTRL_GetChanCtxSize(eCapLevel,&s32ChanCtxSize);

    if (VCTRL_IGNOR_EXTRA != flag)
    {
        TempRefNum = pChanOption->s32MaxRefFrameNum + extra_ref;
        TempDispNum = pChanOption->s32DisplayFrameNum + extra_disp;

        if((TempRefNum < 0) || (TempDispNum < 0))
        {
            dprint(PRN_ALWS, "ERROR: s32MaxRefFrameNum(%d), extra_ref(%d), s32DisplayFrameNum(%d), extra_disp(%d)\n",pChanOption->s32MaxRefFrameNum, extra_ref,
            pChanOption->s32DisplayFrameNum, extra_disp);
            return VCTRL_ERR;

        }
        else if(TempRefNum > 16)
        {
            dprint(PRN_ALWS, "ERROR: (MaxRefFrameNum(%d) + extra_ref(%d)) > 16\n",pChanOption->s32MaxRefFrameNum, extra_ref);
            pChanOption->s32MaxRefFrameNum = 16;
            pChanOption->s32DisplayFrameNum = TempDispNum;
        }
        else
        {
            pChanOption->s32MaxRefFrameNum = TempRefNum;
            pChanOption->s32DisplayFrameNum = TempDispNum;
        }
    }

    if (eCapLevel != CAP_LEVEL_USER_DEFINE_WITH_OPTION && flag == VCTRL_USER_OPTION)
    {
        dprint(PRN_ALWS, "VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_BY_OPTION is designed for CAP_LEVEL_USER_DEFINE_WITH_OPTION, please change channel's capability or use VDEC_CID_GET_CHAN_MEMSIZE.\n");
        return VCTRL_ERR;
    }

    if (pChanOption->Purpose >= PURPOSE_BUTT)
    {
        dprint(PRN_ALWS, "VDEC_CID_CREATE_CHAN_WITH_OPTION the purpose of creating the channel is not clear.\n");
        return VCTRL_ERR;
    }

    if (pChanOption->Purpose == PURPOSE_FRAME_PATH_ONLY)
    {
        if ((pChanOption->s32SlotWidth == 0) || (pChanOption->s32SlotHeight == 0))
        {
            dprint(PRN_ALWS, "s32SlotWidth or s32SlotHeight is 0.\n");
            return VCTRL_ERR;
        }
        pDetailMemSize->VdhDetailMem = pChanOption->s32SlotWidth * pChanOption->s32SlotHeight * (pChanOption->s32DisplayFrameNum + 1)*2;
        pDetailMemSize->ScdDetailMem = 0;
        pDetailMemSize->CtxDetailMem = s32ChanCtxSize;

        return VCTRL_OK;
    }

    if (pChanOption->Purpose == PURPOSE_DECODE)
    {
        if ((pChanOption->s32MaxRefFrameNum < 0)
         || (pChanOption->s32MaxWidth < 32)
         || (pChanOption->s32MaxHeight < 32)
         || (pChanOption->s32SCDBufSize < SM_MIN_SEG_BUF_SIZE))
        {
            dprint(PRN_ALWS, "CAP_LEVEL_USER_DEFINE_WITH_OPTION option is illegal.\n");
            return VCTRL_ERR;
        }
        else
        {
            if (0 == pChanOption->s32SupportBFrame)
            {
                PmvNum = 1;
            }
            else
            {
                PmvNum = pChanOption->s32MaxRefFrameNum + 1;
                PmvNum = MIN(PmvNum,17);
            }
            /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/
            FrameNum = pChanOption->s32MaxRefFrameNum + pChanOption->s32DisplayFrameNum + PLUS_FS_NUM;
        }

	    if (eCapLevel >= CAP_LEVEL_HEVC_QCIF && eCapLevel <= CAP_LEVEL_HEVC_UHD)
		{
	        eFlag = CAP_HEVC_SPECIFIC;
		}
		else
	    {
	        eFlag = INVALID_CHAN_ID;
    	}

        ret = VDMHAL_ArrangeMem( 1, 0x7fffffff, pChanOption->s32MaxWidth, pChanOption->s32MaxHeight, PmvNum, FrameNum, eFlag, &MemArrange );
        if( VDMHAL_OK == ret )
        {
            pDetailMemSize->VdhDetailMem = MemArrange.TotalMemUsed + 16;
            if(1 != pChanOption->u32DynamicFrameStoreAllocEn)//l00273086 使用动态帧存时，由于在create chan时不分配内存，所以对BPD,SEG的分配挪到SCD中
            {
            #ifdef VFMW_VC1_SUPPORT
                pDetailMemSize->VdhDetailMem += BPD_SIZE;
            #endif
            #ifdef VFMW_VP8_SUPPORT
                pDetailMemSize->VdhDetailMem += VP8_SEGID_SIZE;/*32*1024为segid_buffer*/
            #endif
                pDetailMemSize->ScdDetailMem = pChanOption->s32SCDBufSize + 32768;
            }
            else
            {
                pDetailMemSize->ScdDetailMem = pChanOption->s32SCDBufSize + 32768 + 16;
            #ifdef VFMW_VC1_SUPPORT
                pDetailMemSize->ScdDetailMem += BPD_SIZE;
            #endif
            #ifdef VFMW_VP8_SUPPORT
                pDetailMemSize->ScdDetailMem += VP8_SEGID_SIZE;/*32*1024为segid_buffer*/
            #endif
            }

            pDetailMemSize->CtxDetailMem = s32ChanCtxSize;
            if (pChanOption->u32SupportStd != 0)
            {
            #ifdef VFMW_H264_SUPPORT
                if ((pChanOption->u32SupportStd&0x1) != 0)
                {
                    TempAddMem = MAX(TempAddMem, (sizeof(H264_DEC_SLICE_PARAM_S)*MAX_SLICE_SLOT_NUM + \
                                                  sizeof(H264_SPS_S)*MAX_SPS_NUM + \
                                                  sizeof(H264_PPS_S)*MAX_PPS_NUM));
                }
            #endif
              
            #ifdef VFMW_MVC_SUPPORT
                if (((pChanOption->u32SupportStd>>1)&0x1) != 0)
                {
                    TempAddMem = MAX(TempAddMem, (sizeof(MVC_DEC_SLICE_PARAM_S)*MAX_SLICE_SLOT_NUM + \
		                                          sizeof(MVC_SPS_S)*MVC_MAX_SPS_NUM + \
		                                          sizeof(MVC_PPS_S)*MVC_MAX_PPS_NUM));
				}
            #endif
            
            #ifdef VFMW_HEVC_SUPPORT
                if (((pChanOption->u32SupportStd>>2)&0x1) != 0)
    			{
                    TempAddMem = MAX(TempAddMem, (sizeof(HEVC_DEC_SLICE_PARAM_S)*HEVC_MAX_SLICE_NUM + \
                                                  sizeof(HEVC_VIDEO_PARAM_SET_S)*HEVC_MAX_VIDEO_PARAM_SET_ID + \
                                                  sizeof(HEVC_SEQ_PARAM_SET_S)*HEVC_MAX_SEQ_PARAM_SET_ID + \
                                                  sizeof(HEVC_PIC_PARAM_SET_S)*HEVC_MAX_PIC_PARAM_SET_ID + \
                                                  sizeof(HEVC_NALU_S)*(HEVC_MAX_SLOT_NUM+1) + \
                                                  sizeof(HEVC_MSGSLOT_S)*HEVC_MAX_SLOT_NUM));
    			}
			#endif
                pDetailMemSize->CtxDetailMem += TempAddMem;
            }
        }
        else
        {
            dprint(PRN_FATAL,"VCTRL_GetChanMemSizeByOption L%d: arrange return failure\n", __LINE__);
            return VCTRL_ERR;
        }

        return VCTRL_OK;
    }

    return VCTRL_ERR;
}

/***********************************************************************
   计算各种能力级别下创建通道所需要占用的内存大小, 每种能力级别给出三种
   配置分别占用的内存量:
   [0]: 最小预算
   [1]: 普通预算
   [2]: 流畅预算
 ***********************************************************************/
SINT32 VCTRL_GetChanMemSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, SINT32 *VdmMemSize, SINT32 *ScdMemSize)
{
    extern SINT32 CapItem[][7];
    SINT32  nMinFrame, nMiddleFrame, nFluentFrame, nPmv;
    SINT32  TempMinFrame, TempMiddleFrame, TempFluentFrame, TempPmv;
    SINT32  MinPostFspNum, s32MaxRefFrameNum, extra_ref_tmp;

    nMinFrame    = TempMinFrame    = CapItem[eCapLevel][3];
    nMiddleFrame = TempMiddleFrame = CapItem[eCapLevel][4];
    nFluentFrame = TempFluentFrame = CapItem[eCapLevel][5];
    nPmv         = TempPmv         = CapItem[eCapLevel][2];

    /* 根据选定能力集决定最小 显示帧存*/
    switch(eCapLevel)
    {
        case CAP_LEVEL_4096x2160:
        case CAP_LEVEL_2160x4096:
        case CAP_LEVEL_4096x4096:
        case CAP_LEVEL_8192x4096:
        case CAP_LEVEL_4096x8192:
            MinPostFspNum = 3;
            break;

        case CAP_LEVEL_8192x8192:
        case CAP_LEVEL_SINGLE_IFRAME_FHD:
        case CAP_LEVEL_USER_DEFINE_WITH_OPTION:
            MinPostFspNum = 1;
            break;

        default:
            MinPostFspNum = 6;
            break;
    }
    s32MaxRefFrameNum = CapItem[eCapLevel][3] - MinPostFspNum - PLUS_FS_NUM;

    if (extra_ref < 0)
    {
        extra_ref = 0;
    }

    if (s32MaxRefFrameNum >= 16)
    {
        extra_ref_tmp = 0;
    }
    else if (s32MaxRefFrameNum + extra_ref > 16)
    {
        extra_ref_tmp = extra_ref - ( (s32MaxRefFrameNum + extra_ref) - 16 );
    }
    else
    {
        extra_ref_tmp = extra_ref;
    }

    TempMinFrame    += (extra_ref_tmp + extra_disp);
    TempMiddleFrame += (extra_ref_tmp + extra_disp);
    TempFluentFrame += (extra_ref_tmp + extra_disp);
    TempPmv         += extra_ref_tmp;
    if(TempPmv <= 0)
    {
        dprint(PRN_ALWS, "ERROR: (nPmv(%d) + extra_ref(%d)) <= 0\n", nPmv, extra_ref_tmp);
        nPmv = MIN(nPmv, 17);
    }
    else
    {
        nPmv = MIN(TempPmv, 17);
    }

    if (eCapLevel < CAP_LEVEL_SINGLE_IFRAME_FHD)
    {
        if((TempMinFrame <= 0) || (TempMiddleFrame <= 0) || (TempFluentFrame <= 0))
        {
            /* 所给的extra_ref 和 extra_disp值不合法，将其无效处理，使用原来的有效值*/
                dprint(PRN_ALWS, "ERROR: TempMinFrame(%d + %d + %d), TempMiddleFrame(%d + %d + %d), TempFluentFrame(%d + %d + %d)\n",
                nMinFrame, extra_ref_tmp, extra_disp, nMiddleFrame, extra_ref_tmp, extra_disp, nFluentFrame, extra_ref_tmp, extra_disp);
        }
        else
        {
            nMinFrame    = TempMinFrame;
            nMiddleFrame = TempMiddleFrame;
            nFluentFrame = TempFluentFrame;
        }
    }

    if( eCapLevel < CAP_LEVEL_BUTT )
    {
        VDMHAL_MEM_ARRANGE_S MemArrange;
        SINT32 ret;
        /* 最小配置 */
        ret = VDMHAL_ArrangeMem(1, 0x7fffffff, CapItem[eCapLevel][0], CapItem[eCapLevel][1],
            nPmv, nMinFrame, -1,  &MemArrange );
        if( VDMHAL_OK == ret )
        {
            VdmMemSize[0] = MemArrange.TotalMemUsed + 16;
        #ifdef VFMW_VC1_SUPPORT
            VdmMemSize[0] += BPD_SIZE;
        #endif
        #ifdef VFMW_VP8_SUPPORT
            VdmMemSize[0] += VP8_SEGID_SIZE;/*32*1024为segid_buffer*/
        #endif
            ScdMemSize[0] = CapItem[eCapLevel][6] + 32768;
        }
        else
        {
            dprint(PRN_FATAL,"VCTRL_GetChanMemSize L%d: arrange return failure\n", __LINE__);
            return VCTRL_ERR;
        }
        /* 普通配置 */
        ret = VDMHAL_ArrangeMem( 1, 0x7fffffff, CapItem[eCapLevel][0], CapItem[eCapLevel][1],
            nPmv, nMiddleFrame, -1,  &MemArrange );
        if( VDMHAL_OK == ret )
        {
            VdmMemSize[1] = MemArrange.TotalMemUsed + 16;
        #ifdef VFMW_VC1_SUPPORT
            VdmMemSize[1] += BPD_SIZE;
        #endif
        #ifdef VFMW_VP8_SUPPORT
            VdmMemSize[1] += VP8_SEGID_SIZE;/*32*1024为segid_buffer*/
        #endif
            ScdMemSize[1] = CapItem[eCapLevel][6] + 32768;
        }
        else
        {
            dprint(PRN_FATAL,"VCTRL_GetChanMemSize L%d: arrange return failure\n", __LINE__);
            return VCTRL_ERR;
        }
        /* 流畅配置 */
        ret = VDMHAL_ArrangeMem( 1, 0x7fffffff, CapItem[eCapLevel][0], CapItem[eCapLevel][1],
            nPmv, nFluentFrame, -1,  &MemArrange );
        if( VDMHAL_OK == ret )
        {
            VdmMemSize[2] = MemArrange.TotalMemUsed + 16;
        #ifdef VFMW_VC1_SUPPORT
            VdmMemSize[2] += BPD_SIZE;
        #endif
        #ifdef VFMW_VP8_SUPPORT
            VdmMemSize[2] += VP8_SEGID_SIZE;/*32*1024为segid_buffer*/
        #endif
            ScdMemSize[2] = CapItem[eCapLevel][6] + 32768;
        }
        else
        {
            dprint(PRN_FATAL,"VCTRL_GetChanMemSize L%d: arrange return failure\n", __LINE__);
            return VCTRL_ERR;
        }

        return VCTRL_OK;
    }

    return VCTRL_ERR;
}


/***********************************************************************
   VCTRL_GetNextDecodeMode: 解码前丢帧时解码模式的计算
 ***********************************************************************/
SINT32 VCTRL_GetNextDecodeMode( SINT32 CurMode, SINT32 StreamAmount, SINT32 Threshould )
{
    SINT32  NextMode = CurMode;
    SINT32  SafeThr, DangerThr, WarningThr;

    SafeThr    = Threshould / 8;
    WarningThr = Threshould * 2 / 3;
    DangerThr  = Threshould;
    dprint(PRN_DEC_MODE, "(safe,warn,danger) :amount = %d,%d,%d,%d\n", SafeThr, WarningThr, DangerThr, StreamAmount);

    /* 用I模式做解码前丢帧 */
    if(CurMode == DISCARD_MODE)
    {   /* 正在激烈丢帧，是否切换到不丢帧? */
        if( StreamAmount < SafeThr )
        {
            dprint(PRN_DEC_MODE, "strm_ctrl: I->IPB\n");
            NextMode = IPB_MODE;
        }
    }
    else
    {
        /* 非丢帧状态，判断是否应该启动丢帧 */
        if( StreamAmount > DangerThr )
        {
            dprint(PRN_DEC_MODE, "strm_ctrl: IPB->I\n");
            NextMode = DISCARD_MODE;
        }
    }
    dprint(PRN_DEC_MODE, "(CurrMode,NextMode) = %d,%d\n",CurMode,NextMode);

    return NextMode;
}


/***********************************************************************
   VCTRL_DecChanSyntax: 一包seg数据语法解析单元
 ***********************************************************************/
SINT32 VCTRL_DecChanSyntax(SINT32 ChanID)
{
    SINT32 ret;
    STREAM_SEG_PACKET_S *pSegMan;
    VOID *pDecParam;
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
    static UINT32 last_rec_pos_decparam_time[MAX_CHAN_NUM] = {0};
    UINT32 currtime = 0;
    SINT32 rec_pos_print_flag = 0;
    UINT32 dat = 0;
    SINT8  IsAdvProfile = 0;

    VCTRL_ASSERT_RET(ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET(NULL != s_pstVfmwChan[ChanID], "This channel is not opened");
    VCTRL_ASSERT_RET(1 == s_pstVfmwChan[ChanID]->s32IsRun, "This channel is not running");
    VCTRL_ASSERT_RET(0 == s_pstVfmwChan[ChanID]->s32StopSyntax, "Syntax is stopped from This channel");

    s_pstVfmwChan[ChanID]->s32NoStreamFlag = 0;

    currtime = VFMW_OSAL_GetTimeInMs();
    if ((currtime - last_rec_pos_time[ChanID]) > g_TraceBsPeriod)
    {
        rec_pos_print_flag = 1;
        last_rec_pos_time[ChanID] = currtime;
    }
    else
    {
        rec_pos_print_flag = 0;
    }

    /* 1. 检查此通道的VDM是否繁忙 */
    pDecParam = VCTRL_GetDecParam(ChanID);
    if ( NULL != pDecParam )
    {
        if (rec_pos_print_flag == 1)
        {
            dprint(PRN_BLOCK, "[%d] vdm busy\n", ChanID);
        }
        return VCTRL_ERR_VDM_BUSY;
    }
    
    /* 2. 检查帧存是否足够 */
    if ( 1 != VCTRL_GetImageBuffer(ChanID) )  // if (  ChanID 帧存不足  )
    {
        if (rec_pos_print_flag == 1)
        {
            dprint(PRN_BLOCK, "[%d] no frame\n", ChanID);
        }
        return VCTRL_ERR_NO_FSTORE;
    }

    /* 3. 尝试读码流 */
    ret = FMW_OK;  /* 赋初值，因为软解码时未必需要每次都读码流 */
    pSegMan = &s_pstVfmwChan[ChanID]->stSynExtraData.stSegPacket;
    
    if((0 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) || \
       ((1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) && \
       (FSP_PARTITION_STATE_FIRST   == s_pstVfmwChan[ChanID]->FspInst.eFspPartitionState || \
        FSP_PARTITION_STATE_SUCCESS == s_pstVfmwChan[ChanID]->FspInst.eFspPartitionState)))   //状态机 l00273086
    {
        if ((0 == pSegMan->IsCurrSegWaitDec) && (0 == s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag))
        {
            ret = SM_ReadStreamSeg(ChanID, &(pSegMan->CurrSeg));
        }

        /* 如果有码流可解则解码，否则返回 */
        if ( FMW_OK != ret)
        {
            //读不到码流或出错
            if (rec_pos_print_flag == 1)
            {
                dprint(PRN_BLOCK, "[%d] no stream\n", ChanID);
            }

            s_pstVfmwChan[ChanID]->s32NoStreamFlag = 1;
            return VCTRL_ERR_NO_STREAM;
        }
        else
        {
            dprint(PRN_PTS, "seg_pts: %lld, seg_usertag = %lld\n", pSegMan->CurrSeg.Pts, pSegMan->CurrSeg.Usertag);
        #ifdef VFMW_VC1_SUPPORT
            if(VFMW_VC1 == s_pstVfmwChan[ChanID]->stChanCfg.eVidStd)
            {
                IsAdvProfile = ((VC1_CTX_S *)(&s_pstVfmwChan[ChanID]->stSynCtx.unSyntax))->pstExtraData->StdExt.Vc1Ext.IsAdvProfile;
            }
        #endif
            /* mpeg2 PTS 处理机制修改，解决PTS提前一帧的问题  */
            /* lkf58351 20111227: mpeg2 码流处理机制修改，不需要等到下一帧码流才送当前帧码流去解码，
               即不存在PTS提前一帧的问题，故沿用之前的pts处理方式  */
            if(
            #ifdef SCD_MP4_SLICE_ENABLE
                VFMW_MPEG2 == s_pstVfmwChan[ChanID]->stChanCfg.eVidStd ||
            #endif
                VFMW_MPEG4 == s_pstVfmwChan[ChanID]->stChanCfg.eVidStd ||
                VFMW_AVS == s_pstVfmwChan[ChanID]->stChanCfg.eVidStd ||
                (VFMW_VC1 == s_pstVfmwChan[ChanID]->stChanCfg.eVidStd && (IsAdvProfile == 1)))
            {
                if ( SYN_OK == IsNewpicSeg( &s_pstVfmwChan[ChanID]->stSynExtraData.s32NewPicSegDetector,
                   s_pstVfmwChan[ChanID]->stChanCfg.eVidStd, &pSegMan->CurrSeg) )
                {
                    if(VFMW_MPEG2 == s_pstVfmwChan[ChanID]->stChanCfg.eVidStd)
                    {
                       // if (s_pstVfmwChan[ChanID]->stSynExtraData.pts == (UINT64)(-1))
                        {
                            s_pstVfmwChan[ChanID]->stSynExtraData.pts = s_pstVfmwChan[ChanID]->stSynExtraData.NextPts;
                        }
                    }
                    else
                    {
                        if (s_pstVfmwChan[ChanID]->stSynExtraData.NextPts != (UINT64)(-1))
                        {
                            s_pstVfmwChan[ChanID]->stSynExtraData.pts = s_pstVfmwChan[ChanID]->stSynExtraData.NextPts;
                        }
                    }
                    s_pstVfmwChan[ChanID]->stSynExtraData.NextPts = (UINT64)(-1);
                    s_pstVfmwChan[ChanID]->stSynExtraData.Usertag = s_pstVfmwChan[ChanID]->stSynExtraData.NextUsertag;
                    s_pstVfmwChan[ChanID]->stSynExtraData.DispTime = s_pstVfmwChan[ChanID]->stSynExtraData.NextDispTime;
                    s_pstVfmwChan[ChanID]->stSynExtraData.DispEnableFlag = s_pstVfmwChan[ChanID]->stSynExtraData.NextDispEnableFlag;
                    s_pstVfmwChan[ChanID]->stSynExtraData.DispFrameDistance = s_pstVfmwChan[ChanID]->stSynExtraData.NextDispFrameDistance;
                    s_pstVfmwChan[ChanID]->stSynExtraData.DistanceBeforeFirstFrame = s_pstVfmwChan[ChanID]->stSynExtraData.NextDistanceBeforeFirstFrame;
                    s_pstVfmwChan[ChanID]->stSynExtraData.GopNum = s_pstVfmwChan[ChanID]->stSynExtraData.NextGopNum;

                    dprint(PRN_PTS, "pic_pts: %lld\n", s_pstVfmwChan[ChanID]->stSynExtraData.pts);

                    if(VFMW_MPEG2 == s_pstVfmwChan[ChanID]->stChanCfg.eVidStd)
                    {
                        {
                            s_pstVfmwChan[ChanID]->stSynExtraData.NextPts = pSegMan->CurrSeg.Pts;
                        }
                        s_pstVfmwChan[ChanID]->stSynExtraData.NextUsertag = pSegMan->CurrSeg.Usertag;
                        s_pstVfmwChan[ChanID]->stSynExtraData.NextDispTime = pSegMan->CurrSeg.DispTime;
                        s_pstVfmwChan[ChanID]->stSynExtraData.NextDispEnableFlag = pSegMan->CurrSeg.DispEnableFlag;
                        s_pstVfmwChan[ChanID]->stSynExtraData.NextDispFrameDistance = pSegMan->CurrSeg.DispFrameDistance;
                        s_pstVfmwChan[ChanID]->stSynExtraData.NextDistanceBeforeFirstFrame = pSegMan->CurrSeg.DistanceBeforeFirstFrame;
                        s_pstVfmwChan[ChanID]->stSynExtraData.NextGopNum = pSegMan->CurrSeg.GopNum;
                    }
                }

                if(VFMW_MPEG2 != s_pstVfmwChan[ChanID]->stChanCfg.eVidStd)
                {
                    if( pSegMan->CurrSeg.Pts != (UINT64)(-1) )
                    {
                        s_pstVfmwChan[ChanID]->stSynExtraData.NextPts = pSegMan->CurrSeg.Pts;
                    }
                    s_pstVfmwChan[ChanID]->stSynExtraData.NextUsertag = pSegMan->CurrSeg.Usertag;
                    s_pstVfmwChan[ChanID]->stSynExtraData.NextDispTime = pSegMan->CurrSeg.DispTime;
                    s_pstVfmwChan[ChanID]->stSynExtraData.NextDispEnableFlag = pSegMan->CurrSeg.DispEnableFlag;
                    s_pstVfmwChan[ChanID]->stSynExtraData.NextDispFrameDistance = pSegMan->CurrSeg.DispFrameDistance;
                    s_pstVfmwChan[ChanID]->stSynExtraData.NextDistanceBeforeFirstFrame = pSegMan->CurrSeg.DistanceBeforeFirstFrame;
                    s_pstVfmwChan[ChanID]->stSynExtraData.NextGopNum = pSegMan->CurrSeg.GopNum;

                }
                dprint(PRN_PTS, "pic_usertag: %lld\n", s_pstVfmwChan[ChanID]->stSynExtraData.Usertag);
            }
            else
            {
                /*沿用之前的方式，避免不成熟的方法引起更大的网上问题 */
                if( pSegMan->CurrSeg.Pts != (UINT64)(-1) )
                {
                    s_pstVfmwChan[ChanID]->stSynExtraData.pts = pSegMan->CurrSeg.Pts;
                }
                s_pstVfmwChan[ChanID]->stSynExtraData.Usertag = pSegMan->CurrSeg.Usertag;
                s_pstVfmwChan[ChanID]->stSynExtraData.DispTime = pSegMan->CurrSeg.DispTime;
                s_pstVfmwChan[ChanID]->stSynExtraData.DispEnableFlag = pSegMan->CurrSeg.DispEnableFlag;
                s_pstVfmwChan[ChanID]->stSynExtraData.DispFrameDistance = pSegMan->CurrSeg.DispFrameDistance;
                s_pstVfmwChan[ChanID]->stSynExtraData.DistanceBeforeFirstFrame = pSegMan->CurrSeg.DistanceBeforeFirstFrame;
                s_pstVfmwChan[ChanID]->stSynExtraData.GopNum = pSegMan->CurrSeg.GopNum;

                dprint(PRN_PTS, "pic_pts: %lld pic_usertag = %lld\n", s_pstVfmwChan[ChanID]->stSynExtraData.pts, s_pstVfmwChan[ChanID]->stSynExtraData.Usertag);
            }
        }

        if (CHECK_REC_POS_ENABLE(STATE_DECSYNTAX_SEG))
        {
            if (rec_pos_print_flag == 1)
            {
                dat = (ChanID<<24) + (STATE_DECSYNTAX_SEG<<16);
                REC_POS(dat);
            }
        }

        /* 4. 解码 */
        DecodeStream(pSegMan, s_pstVfmwChan[ChanID]->eVidStd, &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax);

        if (CHECK_REC_POS_ENABLE(STATE_GENERATE_DECPARAM))
        {
            currtime = VFMW_OSAL_GetTimeInMs();
            if ((currtime - last_rec_pos_decparam_time[ChanID]) > g_TraceFramePeriod)
            {
                last_rec_pos_decparam_time[ChanID] = currtime;
                if (VCTRL_GetDecParam(ChanID) != NULL)
                {
                    dat = (ChanID<<24) + (STATE_GENERATE_DECPARAM<<16);
                    REC_POS(dat);
                }
            }
        }
        return VCTRL_OK;
    }
    else if((1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) && \
            (FSP_PARTITION_STATE_WAIT == s_pstVfmwChan[ChanID]->FspInst.eFspPartitionState))
    {
        dprint(PRN_FS, "DFS, Wait Partition\n");
        return VCTRL_ERR_NO_FSTORE;
    }
    else
    {
        dprint(PRN_FS,"DFS, Partition fail, u32DynamicFrameStoreAllocEn: %d, eFspPartitionState: %d\n", \
               s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn, \
               s_pstVfmwChan[ChanID]->FspInst.eFspPartitionState);
        return VCTRL_ERR;
    }
}

/***********************************************************************
   VCTRL_DecSyntax: 解码语法，按优先级次序解码各通道的语法
 ***********************************************************************/
SINT32 VCTRL_DecSyntax(VOID)
{
    static SINT32 ChanPriTab[MAX_CHAN_NUM];
    SINT32 i, MaxPri, MaxPriChan;
    SINT32 ret = VCTRL_ERR;
    SM_INST_INFO_S stScdInstInfo;

    for ( i = 0; i < MAX_CHAN_NUM; i++ )
    {
        if (NULL != s_pstVfmwChan[i])
        {
            ChanPriTab[i] = s_pstVfmwChan[i]->s32Priority;
        }
        else
        {
            ChanPriTab[i] = 0;
        }
    }

    while (1)
    {
        /* 寻找优先级最高的一路 */
        MaxPri = ChanPriTab[0];
        MaxPriChan = 0;
        for ( i = 0; i < MAX_CHAN_NUM; i++ )
        {
            if ( ChanPriTab[i] > MaxPri )
            {
                MaxPri = ChanPriTab[i];
                MaxPriChan = i;
            }
        }

        /* 为避免反复选中同一路,将选中者标记为不再调度 */
        ChanPriTab[MaxPriChan] = 0;

        /* 如果通道MaxPriChan可解则解此通道，否则退出调度 */
        s_VfmwCTrl.s32ThisChanIDPlus1 = MaxPriChan + 1;
        if ( MaxPri > 0 )
        {
            if ( NULL != s_pstVfmwChan[MaxPriChan] && 1 == s_pstVfmwChan[MaxPriChan]->s32IsRun )
            {
                /* 看看是否需要做解码前丢帧 */
                if ( s_pstVfmwChan[MaxPriChan]->stChanCfg.s32ChanStrmOFThr > 0 && IPB_MODE == s_pstVfmwChan[MaxPriChan]->stChanCfg.s32DecMode )
                {
                    if ( FMW_OK != SM_GetInfo(MaxPriChan, &stScdInstInfo) )
                    {
                        memset( &stScdInstInfo, 0, sizeof(SM_INST_INFO_S) );
                    }

                    s_pstVfmwChan[MaxPriChan]->stSynExtraData.s32DecMode \
                        = VCTRL_GetNextDecodeMode(s_pstVfmwChan[MaxPriChan]->stSynExtraData.s32DecMode,
                                                  stScdInstInfo.TotalRawSize,
                                                  s_pstVfmwChan[MaxPriChan]->stChanCfg.s32ChanStrmOFThr );

                    if ( s_pstVfmwChan[MaxPriChan]->stSynExtraData.s32DecMode != IPB_MODE )
                    {
                        s_pstVfmwChan[MaxPriChan]->stSynExtraData.s32OutErrThr = 0;
                        s_pstVfmwChan[MaxPriChan]->stSynExtraData.s32RefErrThr = 0;
                    }
                    else
                    {
                        s_pstVfmwChan[MaxPriChan]->stSynExtraData.s32OutErrThr = s_pstVfmwChan[MaxPriChan]->stChanCfg.s32ChanErrThr;
                        s_pstVfmwChan[MaxPriChan]->stSynExtraData.s32RefErrThr = s_pstVfmwChan[MaxPriChan]->stChanCfg.s32ChanErrThr;
                    }
                }

                /* 尝试为通道MaxPriChan解码 */
                for ( i = 0; i < 200; i++ )  /* 264可能要解多个nal才能生成decparam */
                {
                    ret = VCTRL_DecChanSyntax(MaxPriChan);
                    if(VCTRL_ERR == ret)
                    {
                        REPORT_UNSUPPORT(MaxPriChan);
                        return VCTRL_ERR;
                    }
                    else if ( VCTRL_OK != ret )
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            break;
        }
    }

    /* 标记syntax没有为任何通道服务 */
    s_VfmwCTrl.s32ThisChanIDPlus1 = 0;

    return ret; //VCTRL_OK;

}


/************************************************************************/
/* 控制线程                                                             */
/************************************************************************/
SINT32 VCTRL_Vfmw_Thread(VOID *p_temp)
{
    /*============================= 处理运行 ===========================*/
VfmwCtrlThreadRun:
    s_VfmwCTrl.s32ThreadPos = 0;
    dprint(PRN_CTRL,"Thread running...\n");
    s_VfmwCTrl.eTaskState = TASK_STATE_RUNNING;
    while(1)
    {
        s_VfmwCTrl.s32ThreadPos = 1;
        if( TASK_CMD_STOP == s_VfmwCTrl.eTaskCommand )       /* 运行 --> 停止 */
        {
            goto VfmwCtrlThreadStop;
        }
        else if( TASK_CMD_KILL == s_VfmwCTrl.eTaskCommand )  /* 运行 --> 退出 */
        {
            goto VfmwCtrlThreadExit;
        }
        if (TASK_STATE_EXIT == s_VfmwCTrl.eTaskState)
        {
            goto VfmwCtrlThreadExit;
        }

        s_VfmwCTrl.s32ThreadPos = 2;

        VCTRL_RunProcess();
        dprint(PRN_DBG,"thread running...\n");

        s_VfmwCTrl.s32ThreadPos = 3;
    }

    /*============================= 处理停止 ===========================*/
VfmwCtrlThreadStop:
    s_VfmwCTrl.s32ThreadPos = 4;

    dprint(PRN_CTRL,"Thread stopped!\n");
    s_VfmwCTrl.eTaskState = TASK_STATE_STOP;
    while(1)
    {
       s_VfmwCTrl.s32ThreadPos = 5;
        dprint(PRN_DBG,"thread stopped...\n");
        if( TASK_CMD_START == s_VfmwCTrl.eTaskCommand )      /* 停止 --> 运行 */
        {
            goto VfmwCtrlThreadRun;
        }
        else if( TASK_CMD_KILL == s_VfmwCTrl.eTaskCommand )  /* 停止 --> 退出 */
        {
            goto VfmwCtrlThreadExit;
        }
        else
        {
            VFMW_OSAL_mSleep(10);
        }

        if (TASK_STATE_EXIT == s_VfmwCTrl.eTaskState)
        {
            goto VfmwCtrlThreadExit;
        }
    }

    /*============================= 处理退出 ===========================*/
VfmwCtrlThreadExit:
    s_VfmwCTrl.s32ThreadPos = 6;

    dprint(PRN_CTRL,"Thread killed!\n");
    s_VfmwCTrl.eTaskState = TASK_STATE_EXIT;
    return VCTRL_OK;
}

/************************************************************************/
/* 解码线程主函数                                                       */
/************************************************************************/
SINT32 VCTRL_RunProcess(VOID)
{
    SINT32 ret = VCTRL_OK;
    SINT32 i;

    s_VfmwCTrl.s32ThreadPos = 100;

    if(g_SleepTime > 0)
    {
        VFMW_OSAL_mSleep(g_SleepTime);
    }

    /** 锁定，在一个解码循环内部不允许停止通道 **/
    VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);

    /* 1. 唤醒SCD */
    SM_Wakeup();

    /* 2. 语法解析，一次调用仅解一个通道，如果无通道可解返回失败 */
    s_VfmwCTrl.s32ThreadPos = 101;
    if(g_StopDec==0)
    {
        ret = VCTRL_DecSyntax();
    }

    /* 3. 唤醒VDM */
    s_VfmwCTrl.s32ThreadPos = 102;
    VDMDRV_WakeUpVdm();

    SCDDRV_EnableInt();

    /* VDH中断打开*/
    for(i=0;i<MAX_VDH_NUM;i++)
    {
        VDMHAL_EnableInt(i);
    }

    /* 释放各个通道RAW码流 */
    for(i=0;i<MAX_CHAN_NUM;i++)
    {
        DeleteRawPacketInBuffer(i, 0);
    }

    /** 解除锁定，允许停止通道 **/
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);

    s_VfmwCTrl.s32ThreadPos = 105;

    /* 阻塞一下 */
    VFMW_OSAL_WaitEvent(G_INTEVENT, 10);

    return ret;
}


SINT32 VCTRL_GetChanIDByCtx(VOID *pCtx)
{
    SINT32 i;
    for( i = 0; i < MAX_CHAN_NUM; i++ )
    {
        if( NULL == s_pstVfmwChan[i] )
        {
            continue;
        }

        if( pCtx == &s_pstVfmwChan[i]->stSynCtx.unSyntax )
        {
            return i;
        }
    }

    return -1;
}


IMAGE_VO_QUEUE *VCTRL_GetChanVoQue(SINT32 ChanID)
{
    IMAGE_VO_QUEUE *pstVoQue = NULL;

    if (NULL == s_pstVfmwChan[ChanID])
    {
        return NULL;
    }

    switch(s_pstVfmwChan[ChanID]->eVidStd)
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stH264Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_HEVC_SUPPORT
        case VFMW_HEVC:
			pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stHevcCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stMpeg2Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stMpeg4Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stAvsCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stReal8Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stReal9Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stDivx3Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stVc1Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
        case VFMW_VP6:
        case VFMW_VP6F:
        case VFMW_VP6A:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stVp6Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stVp8Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            pstVoQue = &s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stMvcCtx.ImageQue;
            break;
    #endif
        default:
            break;
    }

    return pstVoQue;
}


VOID VCTRL_GetChanImgNum( SINT32 ChanID, SINT32 *pRefImgNum, SINT32 *pReadImgNum, SINT32 *pNewImgNum )
{
    IMAGE_VO_QUEUE *pstVoQue = NULL;
    VCTRL_ASSERT( NULL !=s_pstVfmwChan[ChanID], "Chan inactive");

    pstVoQue = VCTRL_GetChanVoQue(ChanID);
    if(pstVoQue)
    {
        GetQueueImgNum(pstVoQue, pReadImgNum, pNewImgNum);
        if (s_pstVfmwChan[ChanID]->eVidStd == VFMW_H264)
        {
        #ifdef VFMW_H264_SUPPORT
            *pRefImgNum = s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stH264Ctx.DPB.size;
        #else
            dprint(PRN_ALWS,">>>>>line %d cannot support h264\n");
        #endif
        }
        else if (s_pstVfmwChan[ChanID]->eVidStd == VFMW_HEVC)
        {
        #ifdef VFMW_HEVC_SUPPORT
            *pRefImgNum = s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stHevcCtx.DPB.size;
        #else
            dprint(PRN_ALWS,">>>>>line %d cannot support hevc\n");
        #endif
        }
        else if (s_pstVfmwChan[ChanID]->eVidStd == VFMW_MVC)
        {
        #ifdef VFMW_MVC_SUPPORT
            *pRefImgNum = s_pstVfmwChan[ChanID]->stSynCtx.unSyntax.stMvcCtx.DPB.size;
        #else
            dprint(PRN_ALWS,">>>>>line %d cannot support mvc\n");
        #endif
        }
        else
        {
            *pRefImgNum = 2;
        }
    }
    else
    {
        *pRefImgNum = *pReadImgNum = *pNewImgNum = 0;
    }

    return;
}

SINT32 VCTRL_GetChanWidth(SINT32 ChanID)
{
    VCTRL_ASSERT_RET(ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( NULL != s_pstVfmwChan[ChanID], "Chan inactive");

    return s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.s32MaxWidth;
}

SINT32 VCTRL_GetChanHeight(SINT32 ChanID)
{
    VCTRL_ASSERT_RET(ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");
    VCTRL_ASSERT_RET( NULL != s_pstVfmwChan[ChanID], "Chan inactive");

    return s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.s32MaxHeight;
}

VDEC_CHAN_CAP_LEVEL_E  VCTRL_GetChanCapLevel(SINT32 ChanID)
{
    VCTRL_ASSERT_RET(ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");

    if (s_pstVfmwChan[ChanID] != NULL)
    {
        return s_pstVfmwChan[ChanID]->eChanCapLevel;
    }

    return CAP_LEVEL_BUTT;
}

VOID VCTRL_MaskAllInt(VOID)
{
    SINT32 i;

    /* VDH中断屏蔽*/
    for(i=0;i<MAX_VDH_NUM;i++)
    {
        VDMHAL_MaskInt(i);
    }
    SCDDRV_MaskInt();

    return;
}

VOID VCTRL_EnableAllInt(VOID)
{
    SINT32 i;
    /* VDH中断打开*/
    for(i=0;i<MAX_VDH_NUM;i++)
    {
        VDMHAL_EnableInt(i);
    }
    SCDDRV_EnableInt();

    return;
}

/*********************************************************************************
    设置VDM的调试选项
*********************************************************************************/
SINT32 VCTRL_SetDbgOption ( UINT32 opt, UINT8* p_args )
{
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    UINT32 dat, *p32Args;
    SINT32 ret;

    if ( NULL== p_args )
    {
        return VF_ERR_PARAM;
    }

    p32Args = (UINT32*)p_args;
    dat = p32Args[0];
    switch ( opt )
    {

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%% 配置测试(0x000) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    case 0x000: /* 设置打印使能 */
        g_PrintEnable = dat;
        break;
        
    case 0x001: /* 设置打印设备 */
        break;
        
   case 0x002: /* 设置error_thr */
        {
            SINT32 ChanID, Thr;
            VDEC_CHAN_CFG_S ChanCfg;
            ChanID = dat >> 24;
            Thr = dat & 0x00ffffff;
            dprint(PRN_ALWS,"chan %d: new ChanErrThr = %d\n", ChanID, Thr);
            if( VCTRL_OK == VCTRL_GetChanCfg(ChanID, &ChanCfg) )
            {
                ChanCfg.s32ChanErrThr = Thr;
                VCTRL_ConfigChan(ChanID, &ChanCfg);
            }
        }
        break;
        
    case 0x004: /* 设置是否解码序输出 */
        {
            SINT32 ChanID, DecOrderOutput;
            VDEC_CHAN_CFG_S ChanCfg;
            ChanID = dat >> 24;
            DecOrderOutput = dat & 3;
            dprint(PRN_ALWS,"chan %d: new DecOrderOutput = %d\n", ChanID, DecOrderOutput);
            if( VCTRL_OK == VCTRL_GetChanCfg(ChanID, &ChanCfg) )
            {
                ChanCfg.s8DecOrderOutput = DecOrderOutput;
                VCTRL_ConfigChan(ChanID, &ChanCfg);
            }
        }
        break;
        
    case 0x005: /* 设置 I/IP/IPB模式 */
        {
            SINT32 ChanID, Mode;
            VDEC_CHAN_CFG_S ChanCfg;
            ChanID = dat >> 24;
            Mode = dat & 7;
            dprint(PRN_ALWS,"chan %d: new DecMode = %d\n", ChanID, Mode);
            if( VCTRL_OK == VCTRL_GetChanCfg(ChanID, &ChanCfg) )
            {
                ChanCfg.s32DecMode = Mode;
                VCTRL_ConfigChan(ChanID, &ChanCfg);
            }
            else
            {
                dprint(PRN_ALWS,"chan %d: GetChanCfg failed!\n", ChanID);
            }
        }
        break;
        
    case 0x006: /* 设置修补是否使能 */
        {
            if(dat == 0 || dat == 1)
            {
                g_RepairDisable = dat;
                dprint(PRN_ALWS,"RepairDisable = %d\n", g_RepairDisable);
            }
            else
            {
                dprint(PRN_ALWS,"RepairDisable can NOT be set to %d, must be 0 or 1\n", dat);
            }
        }
        break;
        
    case 0x007: /* 修改码流丢帧阈值 */
        {
            SINT32 ChanID, Thr;
            VDEC_CHAN_CFG_S ChanCfg;
            ChanID = dat >> 24;
            Thr = dat & 0x00ffffff;
            dprint(PRN_ALWS,"chan %d: new StrmOFThr = %d\n", ChanID, Thr);
            if( VCTRL_OK == VCTRL_GetChanCfg(ChanID, &ChanCfg) )
            {
                ChanCfg.s32ChanStrmOFThr = Thr;
                VCTRL_ConfigChan(ChanID, &ChanCfg);
            }
        }
        break;
        
    case 0x00b: /* 设置是否打开帧场自适应存储 */
        if(dat == 0 || dat == 1)
        {
            USE_FF_APT_EN = dat;
            dprint(PRN_ALWS,"USE_FF_APT_EN = %d\n", USE_FF_APT_EN);
        }
        else
        {
            dprint(PRN_ALWS,"USE_FF_APT_EN can NOT be set to %d, must be 0 or 1\n", dat);
        }
        break;

    case 0x00c: /* 设置是否在通道复位的时候创建新的调试文件 */
        if(dat == 0 || dat == 1)
        {
            g_ResetCreateNewSave = dat;
            dprint(PRN_ALWS,"ResetCreateNewSave = %d\n", g_ResetCreateNewSave);
        }
        else
        {
            dprint(PRN_ALWS,"ResetCreateNewSave can NOT be set to %d, must be 0 or 1\n", dat);
        }
        break;
        
    case 0x00d:/*设置需要查看的通道号*/
        if (dat > MAX_CHAN_NUM)
        {
            dprint(PRN_ALWS, "NO SUCH CHANNEL : %d\n", dat);
        }
        else
        {
            g_CurProcChan = dat;
            dprint(PRN_ALWS, "Pay attention to  CHANNEL : %d\n", dat);
        }
        break;

    case 0x00f: /* 设置上下电 */
        if (dat == 0)
        {
            VDMDRV_PowerOff();
        }
        else if(dat == 1)
        {
            VDMDRV_PowerOn();
        }
        else
        {
            dprint(PRN_ALWS,"Invalid parameter!\n");
        }
        break;

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%% 打印(0x1xx) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    case 0x100:      /* 内存跟踪 */
        dprint(PRN_ALWS,"print memory tracer...\n");
#ifdef VFMW_RECPOS_SUPPORT
        DBG_PrintTracer(dat);
#endif
        break;

    case 0x101:      /* SCD */
        {
            UINT32 TmpPrintEnable = g_PrintEnable;
            g_PrintEnable = (1<<PRN_SCD_INFO);
            PrintScdRawState(dat, 1);
            g_PrintEnable = TmpPrintEnable;
        }
        break;

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%% 数据存盘(0x200) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
#ifdef ENV_ARMLINUX_KERNEL
    case 0x200:          /* stream存盘 */
        if ( dat >= MAX_CHAN_NUM)
        {
            break;
        }
        if(NULL == vfmw_save_str_file)
        {
            SINT8 str[50];
            static UINT32 save_file_cnt = 0;

            snprintf(str,50,"%s/vfmw_raw_save_%d.dat",(char*)s_VfmwSavePath, save_file_cnt++);
            vfmw_save_str_file = OSAL_FileOpen(str, O_RDWR | O_CREAT, 0);
            save_str_chan_num = dat;
            if (NULL != vfmw_save_str_file)
            {
                dprint(PRN_ALWS,"OK create file '%s' for channel %d raw stream save\n",str, save_str_chan_num);
            }
            else
            {
                dprint(PRN_ALWS,"failed create file '%s' for raw stream save!\n",str);
            }
        }
        else
        {
            dprint(PRN_ALWS,">>>> close raw stream saving >>>>\n");
            OSAL_FileClose(vfmw_save_str_file);
            vfmw_save_str_file = NULL;
        }
        break;

    case 0x201:          /* seg存盘 */
        if (dat >= MAX_CHAN_NUM)
        {
            break;
        }
        if(NULL == vfmw_save_seg_file)
        {
            SINT8 str[50];
            static UINT32 save_file_cnt = 0;

            snprintf(str,50,"%s/vfmw_seg_save_%d.dat",(char*)s_VfmwSavePath, save_file_cnt++);
            vfmw_save_seg_file = OSAL_FileOpen(str, O_RDWR | O_CREAT, 0);
            save_seg_chan_num = dat;
            if (NULL != vfmw_save_seg_file)
            {
                dprint(PRN_ALWS,"OK create file '%s' for channel %d seg stream save\n",str, save_seg_chan_num);
            }
            else
            {
                dprint(PRN_ALWS,"failed create file '%s' for seg stream save!\n",str);
            }
        }
        else
        {
            dprint(PRN_ALWS,">>>> close seg stream saving >>>>\n");
            OSAL_FileClose(vfmw_save_seg_file);
            vfmw_save_seg_file = NULL;
        }
        break;

    case 0x202:        /* YUV存盘 */
        if (dat >= MAX_CHAN_NUM)
        {
            break;
        }
        if(NULL == vfmw_save_yuv_file)
        {
            SINT8 str[100];
            UINT32 max_save_width  = 4096;
            UINT32 max_save_height = 2304;
            static UINT32 save_file_cnt = 0;

            snprintf(str,sizeof(str),"%s/vfmw_yuv_save_%d.yuv",(char*)s_VfmwSavePath, save_file_cnt++);
            vfmw_save_yuv_file = OSAL_FileOpen(str, O_RDWR|O_CREAT|O_TRUNC, 0);
            if (NULL != vfmw_save_yuv_file)
            {
                memset(&MemRecord_YUV,0,sizeof(MEM_RECORD_S));
                if( MEM_MAN_OK != MEM_AllocMemBlock("YUV_TMP", max_save_width*max_save_height*3/2, &MemRecord_YUV, 0) )
                {
                    dprint(PRN_ERROR,"Failed Alloc VFMW_BigTile1d_YUV for yuv save!\n");
                    OSAL_FileClose(vfmw_save_yuv_file);
                    vfmw_save_yuv_file = NULL;
                    pY = pUl = pVl = NULL;
                    save_yuv_chan_num = -1;
                    save_yuv_with_crop = 0;
                }
                else
                {
                    MEM_AddMemRecord(MemRecord_YUV.PhyAddr, MemRecord_YUV.VirAddr, MemRecord_YUV.Length);
                    pY  = MemRecord_YUV.VirAddr;
                    pUl = pY + (max_save_width*max_save_height);
                    pVl = pUl + (max_save_width*max_save_height/4);
                    save_yuv_chan_num = (dat>>24);
                    save_yuv_with_crop = dat&0x03;
                    dprint(PRN_ALWS,"OK create file '%s' for chan %d yuv save.(crop %d)\n",str, save_yuv_chan_num, save_yuv_with_crop);
                }
            }
            else
            {
                dprint(PRN_ALWS,"failed create file '%s' for yuv save!\n",str);
			}
		}
		else
		{
            dprint(PRN_ALWS,"OK close yuv save.\n");
            OSAL_FileClose(vfmw_save_yuv_file);
            vfmw_save_yuv_file = NULL;
            pY = pUl = pVl = NULL;
            save_yuv_chan_num = -1;
            save_yuv_with_crop = 0;

            if (MemRecord_YUV.PhyAddr != 0)
            {
    			MEM_ReleaseMemBlock(MemRecord_YUV.PhyAddr, MemRecord_YUV.VirAddr);
    			MEM_DelMemRecord(MemRecord_YUV.PhyAddr, MemRecord_YUV.VirAddr, MemRecord_YUV.Length);
    			memset(&MemRecord_YUV,0,sizeof(MEM_RECORD_S));
            }
        }
        break;
#endif

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%% 功能测试(0x300) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    case 0x300:   /* 测试待机 */
        VCTRL_Suspend();
        break;
    case 0x301:   /* 测试唤醒 */
        VCTRL_Resume();
        break;
    case 0x380:   /* 测试停止通道 */
        ret = VCTRL_StopChan(dat);
        dprint(PRN_ALWS, "stop chan %d: VCTRL_StopChan return %d\n",dat, ret);
        break;
    case 0x381:   /* 测试复位通道 */
        ret = VCTRL_ResetChan(dat);
        dprint(PRN_ALWS, "reset chan %d: VCTRL_ResetChan return %d\n",dat, ret);
        break;
    case 0x382:   /* 测试启动通道 */
        ret = VCTRL_StartChan(dat);
        dprint(PRN_ALWS, "start chan %d: VCTRL_StartChan return %d\n",dat, ret);
        break;
    case 0x383:   /* 测试启动通道 */
        ret = VCTRL_StopChan(dat);
        dprint(PRN_ALWS, "stop chan %d: VCTRL_StopChan return %d\n",dat, ret);
        ret = VCTRL_ResetChan(dat);
        dprint(PRN_ALWS, "reset chan %d: VCTRL_ResetChan return %d\n",dat, ret);
        ret = VCTRL_StartChan(dat);
        dprint(PRN_ALWS, "start chan %d: VCTRL_StartChan return %d\n",dat, ret);
        break;

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%% 时序测试(0x400) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    case 0x400:
        g_SleepTime = dat;
        dprint(PRN_ALWS,"------ dec task delay %d ms ------\n", g_SleepTime);
        break;
        
    case 0x402:
        g_StopDec = dat;
        dprint(PRN_ALWS,"------ dec stop = %d ------\n", g_StopDec);
        break;
    /* %%%%%%%%%%%%%%%%%%%%%% 调试信息控制参数(0x500) %%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    case 0x500:
        g_TraceCtrl = dat;
        dprint(PRN_ALWS,"------ g_TraceCtrl = %x ------\n", g_TraceCtrl);
        break;
    case 0x501:
        g_TraceBsPeriod = dat;
        dprint(PRN_ALWS,"------ g_TraceBsPeriod = %x ------\n", g_TraceBsPeriod);
        break;
    case 0x502:
        g_TraceFramePeriod = dat;
        dprint(PRN_ALWS,"------ g_TraceFramePeriod = %x ------\n", g_TraceFramePeriod);
        break;
    case 0x503:
        g_TraceImgPeriod = dat;
        dprint(PRN_ALWS,"------ g_TraceImgPeriod = %x ------\n", g_TraceImgPeriod);
        break;
    /* %%%%%%%%%%%%%%%%%%%%%% 低延时控制(0x600) %%%%%%%%%%%%%%%%%%%%%%%%%%%% */
	//打开指定通道的模块间低延时功能
	case 0x600:
		if (dat >= MAX_CHAN_NUM)
        {
            dprint(PRN_FATAL,"The channel number is to Large.\n");
            break;
        }
        s_pstVfmwChan[dat]->stSynExtraData.s32ModuleLowlyEnable = 1;
        dprint(PRN_ALWS,"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleLowlyEnable = 1 ------\n", dat);
		break;
	//关闭指定通道的模块间低延时功能
	case 0x601:
		if (dat >= MAX_CHAN_NUM)
        {
            dprint(PRN_FATAL,"The channel number is to Large.\n");
            break;
        }
        s_pstVfmwChan[dat]->stSynExtraData.s32ModuleLowlyEnable = 0;
        dprint(PRN_ALWS,"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleLowlyEnable = 1 ------\n", dat);
		break;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
	//模块间低延时行号设置
	case 0x602:
        g_TunnelLineNumber = dat;
        dprint(PRN_ALWS,"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleLowlyEnable = 1 ------\n", dat);
		break;
#endif
#ifdef VFMW_SCD_LOWDLY_SUPPORT
	//指定通道scd低延时打开
	case 0x603:
		s_SmIIS.pSmInstArray[dat]->Config.ScdLowdlyEnable = 1;
		break;
	//指定通道scd低延时关闭
	case 0x604:
		s_SmIIS.pSmInstArray[dat]->Config.ScdLowdlyEnable = 0;
		break;
#endif

    default:
        return VF_ERR_PARAM;
    }

    return VF_OK;
#else
    return VF_ERR_SYS;
#endif
}

VOID VCTRL_SetLastFrameState(SINT32 ChanID, LAST_FRAME_STATE_E eState)
{
    VCTRL_ASSERT(ChanID>=0 && ChanID<MAX_CHAN_NUM, "ChanID out of range");

    if (s_pstVfmwChan[ChanID] != NULL)
    {
        s_pstVfmwChan[ChanID]->eLastFrameState = eState;
    }

    return;
}

VOID VCTRL_ReportLastFrame(SINT32 ChanID, SINT32 Value)
{
    LAST_FRAME_STATE_E eState;

    switch (Value)
    {
        case 0:
            eState = LAST_FRAME_REPORT_SUCCESS;
            break;
        case 1:
            eState = LAST_FRAME_REPORT_FAILURE;
            break;
        default:
            eState = LAST_FRAME_REPORT_FRAMEID;
            break;
    }
    VCTRL_SetLastFrameState(ChanID, eState);
    REPORT_LAST_FRAME(ChanID, Value);

    dprint(PRN_ERROR, "Report Last Frame, Value=%d, LastFrameState=%d\n", Value, s_pstVfmwChan[ChanID]->eLastFrameState);
    return;
}

SINT32 VCTRL_OutputLastFrame(SINT32 ChanId)
{
    SINT32 ret = VCTRL_ERR;

    switch (s_pstVfmwChan[ChanId]->stSynCtx.eVidStd)
    {
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2 :
            ret = MPEG2DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg2Ctx);
            break;
    #endif

    #ifdef VFMW_MPEG4_SUPPORT
        case  VFMW_MPEG4 :
            ret = MPEG4DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMpeg4Ctx);
            break;
    #endif

    #ifdef VFMW_H264_SUPPORT
        case  VFMW_H264 :
            ret = H264DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stH264Ctx);
            break;
    #endif

    #ifdef VFMW_HEVC_SUPPORT
        case  VFMW_HEVC :
            ret = HEVCDEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stHevcCtx);
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS :
            ret = AVSDEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stAvsCtx);
            break;
    #endif

    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8 :
            ret = REAL8DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal8Ctx);
            break;
    #endif

    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9 :
            ret = REAL9DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stReal9Ctx);
            break;
    #endif

    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3 :
            ret = DIVX3DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stDivx3Ctx);
            break;
    #endif

    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1 :
            ret = VC1DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVc1Ctx);
            break;
    #endif

    #ifdef VFMW_VP6_SUPPORT
        case VFMW_VP6 :
        case VFMW_VP6A :
        case VFMW_VP6F :
            ret = VP6DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp6Ctx);
            break;
    #endif

    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8 :
            ret = VP8DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stVp8Ctx);
            break;
    #endif

    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC :
            ret = MVC_DEC_GetRemainImg(&s_pstVfmwChan[ChanId]->stSynCtx.unSyntax.stMvcCtx);
            break;
    #endif

        default :
            break;
    }

    switch (ret)
    {
        case -1:
            VCTRL_ReportLastFrame(ChanId, 1);
            dprint(PRN_CTRL, "Last frame output failed!\n");
            break;

        case 0:
            VCTRL_ReportLastFrame(ChanId, 0);
            dprint(PRN_CTRL, "Last frame output successed!\n");
            break;

        default:
            VCTRL_ReportLastFrame(ChanId, ret);
            dprint(PRN_CTRL, "Last frame already output, image id: %d!\n", ret - 2);
    }


    return ret;
}


/***********************************************************************
   VCTRL_OpenHardware: 打开时钟使能
 ***********************************************************************/
VOID VCTRL_OpenHardware(SINT32 ChanID)
{
    SINT32 vdm_need_flag = 1;
    SINT32 bpd_need_flag  = 1;
    VID_STD_E  vid_std = VFMW_H264;
    SINT32 i = 0;

    if ((ChanID < 0) || (ChanID >= MAX_CHAN_NUM))
    {
        dprint(PRN_FATAL,"L:%d ChanID out of range\n", __LINE__);
        return;
    }

    if (NULL == s_pstVfmwChan[ChanID])
    {
        dprint(PRN_FATAL,"L:%d This Chan has not been created!!!\n", __LINE__);
        return;
    }

    if ((1 != s_pstVfmwChan[ChanID]->s32IsOpen) || (VFMW_END_RESERVED == s_pstVfmwChan[ChanID]->eVidStd))
    {
        dprint(PRN_FATAL,"L:%d WARNING: vidio std not setted!\n", __LINE__);
        return;
    }

    // 如果该通道是用户态软解或内核态软解时，请时钟打开
    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (i != ChanID && VCTRL_IsChanActive(i) == VCTRL_OK)
        {
            vid_std = s_pstVfmwChan[i]->eVidStd;
            if (1 == vdm_need_flag)
            {
                //已经存在一路硬解，则不需要再打开VDH时钟
                vdm_need_flag = 0;
            }

                //已经存在一路VC1 硬解，则不需要再打开BPD时钟
            if ((1 == bpd_need_flag)
              && (VFMW_VC1 == vid_std))
            {
                bpd_need_flag = 0;
            }
        }
    }

    if (1 == vdm_need_flag)
    {
        for (i=0; i<MAX_VDH_NUM; i++)
        {
            VDMDRV_OpenHardware(i);
        }
        SCDDRV_OpenHardware();
    }

    if (1 == bpd_need_flag)
    {
        BPDDRV_OpenHardware();
    }

    return;
}


/***********************************************************************
   VCTRL_CloseHardware: 关闭时钟使能
 ***********************************************************************/
VOID VCTRL_CloseHardware(VOID)
{
    SINT32 chan_id = 0, i = 0;
    VID_STD_E  vid_std = VFMW_H264;
    SINT32 vdm_need_flag = 0;
    SINT32 bpd_need_flag  = 0;

    for (chan_id=0; chan_id<MAX_CHAN_NUM; chan_id++)
    {
        if (NULL == s_pstVfmwChan[chan_id])
        {
            continue;
        }

        vid_std = s_pstVfmwChan[chan_id]->eVidStd;

        if ((0 == vdm_need_flag)
            && (1 == s_pstVfmwChan[chan_id]->s32IsOpen)
            && (1 == s_pstVfmwChan[chan_id]->s32IsRun))
        {
            //只要存在一路硬解码，则不能关闭VDH时钟
            vdm_need_flag = 1;
        }

            //只要存在一路VC1 硬解码，则不能关闭BPD时钟
        if ((0 == bpd_need_flag)
            && (VFMW_VC1 == vid_std)
            && (1 == s_pstVfmwChan[chan_id]->s32IsOpen)
            && (1 == s_pstVfmwChan[chan_id]->s32IsRun))
        {
            bpd_need_flag = 1;
        }
    }

    if (0 == vdm_need_flag)
    {
        for (i = 0; i < MAX_VDH_NUM; i++)
        {
            VDMDRV_CloseHardware(i);
            g_VdmDrvParam[i].VdmStateMachine = VDM_NULL_STATE;
        }
        SCDDRV_CloseHardware();
        s_SmIIS.SCDState = 0;
    }

    if (0 == bpd_need_flag)
    {
        BPDDRV_CloseHardware();
    }

    return;
}

VOID VCTRL_SetChanFsPartitionState(SINT32 ChanId, FSP_PARTITION_STATE_E state)
{
	s_pstVfmwChan[ChanId]->FspInst.eFspPartitionState = state;
}

SINT32 VCTRT_SetChanCtrlState(SINT32 ChanID, VFMW_CHANNEL_CONTROL_STATE_E ChanCtrlState)
{
    SINT32 ret = HI_SUCCESS;

    VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    switch(ChanCtrlState)
    {
        case CHAN_NORMAL:
            s_ChanControlState[ChanID] = ChanCtrlState;
            ret = HI_SUCCESS;
            break;

        case CHAN_FRAME_STORE_ALLOC:
            if(CHAN_NORMAL != s_ChanControlState[ChanID])
            {
                ret = HI_FAILURE;
            }
            else
            {
                s_ChanControlState[ChanID] = ChanCtrlState;
                ret = HI_SUCCESS;
            }
            break;
        case CHAN_DESTORY:
            if (CHAN_FRAME_STORE_ALLOC == s_ChanControlState[ChanID]) 
            {
                ret = HI_FAILURE;
            }
            else
            {
                s_ChanControlState[ChanID] = ChanCtrlState;
                ret = HI_SUCCESS;
            }
            break;

        default:
            break;
    }
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    return ret;
}

VOID VCTRL_SetFsParamToChan(SINT32 ChanID, VDEC_CHAN_FRAME_STORES* stParams)
{
	SINT32 i = 0;
	SINT32 s32AllocedFrameNum;

	if(HI_NULL == stParams)
	{
		dprint(PRN_FATAL,"%s, %d, stParams = NULL!\n", __FUNCTION__, __LINE__);
	}

	//配置解码帧存
	s32AllocedFrameNum = 0;
	for(i = 0; i < MAX_FRAME_NUM; i++)
	{
	    if(FRAME_NODE_STATE_FREE == (s_pstVfmwChan[ChanID]->stFrmBuf[i].eBufferNodeState) && (s32AllocedFrameNum < stParams->TotalFrameNum))
	    {
	        s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.PhyAddr = stParams->stFrameBuf[i].PhyAddr;
	        s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.VirAddr = (UINT8 *)stParams->stFrameBuf[i].VirAddr;
	        s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.Length  = stParams->stFrameBuf[i].Length;
	        s_pstVfmwChan[ChanID]->stFrmBuf[i].eBufferNodeState = FRAME_NODE_STATE_PRE;
	        MEM_AddMemRecord(s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.PhyAddr,\
	                         (VOID* )s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.VirAddr,\
	                         s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.Length);
			s32AllocedFrameNum++;
	    }
	    else if(s32AllocedFrameNum >= stParams->TotalFrameNum)
	    {
	        break;
	    }
	}

	//配置PMV帧存
	s32AllocedFrameNum = 0;
	for(i = 0; i < MAX_FRAME_NUM; i++)
	{
	    if(FRAME_NODE_STATE_FREE == (s_pstVfmwChan[ChanID]->stPmvBuf[i].eBufferNodeState) && (s32AllocedFrameNum < stParams->TotalFrameNum))
	    {
	        s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer.PhyAddr = stParams->stPmvBuf[i].PhyAddr;
	        s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer.VirAddr = (UINT8 *)stParams->stPmvBuf[i].VirAddr;
	        s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer.Length  = stParams->stPmvBuf[i].Length;
	        s_pstVfmwChan[ChanID]->stPmvBuf[i].eBufferNodeState = FRAME_NODE_STATE_PRE;
	        MEM_AddMemRecord(s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer.PhyAddr,\
	                         (VOID* )s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer.VirAddr,\
	                         s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer.Length);
			s32AllocedFrameNum++;
	    }
	    else if(s32AllocedFrameNum >= stParams->TotalFrameNum)
	    {
	        break;
	    }
	}
    
	//配置帧存数
    s_pstVfmwChan[ChanID]->s32ActualFrameNum = stParams->TotalFrameNum;
    
    return;
}


/***********************************************************/
/*                       CRC 计算算法                      */
/***********************************************************/
UINT8* VCTRL_GetLinePointer(UINT32 i, UINT8 *Yaddress, UINT32 Stride, UINT8 BtmField)
{
    UINT8 *ptr = NULL;

    if (BtmField == 0) // 顶场
    {
        ptr = Yaddress + (2 * i) * Stride;
    }
    else if (BtmField == 1) // 底场
    {
        ptr = (Yaddress + Stride) + (2 * i) * Stride;
    }
    else
    {
        dprint(PRN_ERROR, "%s BtmField = %d err!!\n", __func__, BtmField);
    }

    return ptr;
}

SINT32 VCTRL_GetU32Crc(UINT32 j, UINT8 *LPointer)
{
    UINT32 u32Crc = 0;
    
    u32Crc = *((UINT32 *)(LPointer + j));

    return u32Crc;
}

/***********************************************************/
/*                       计算场校验码                      */
/***********************************************************/
SINT32 VCTRL_CalcFieldCrc(UINT8 *Yaddress, UINT8 *Caddress, UINT32 Width, UINT32 FieldHeight, UINT32 Stride, UINT8 BtmField)
{
    UINT32 i, j;
    UINT32 FrameCrc             = 0;
    UINT32 chrom_width          = Width / 2;
    UINT32 chrom_height         = FieldHeight / 2;
    UINT32 Y_WidthDistance      = Width / 8;
    UINT32 Y_HeightDistance     = FieldHeight / 4;
    UINT32 chrom_WidthDistance  = Y_WidthDistance / 2;
    UINT32 chrom_HeightDistance = Y_HeightDistance / 2;
    UINT8 *LPointer = NULL;

    while ((Y_WidthDistance % 8) != 0)
    {
        Y_WidthDistance--;
    }

    chrom_WidthDistance = Y_WidthDistance / 2;
    chrom_HeightDistance = Y_HeightDistance / 2;

    Y_WidthDistance = (Y_WidthDistance < 4) ? 4 : Y_WidthDistance;
    chrom_WidthDistance = (chrom_WidthDistance < 4) ? 4 : chrom_WidthDistance;

    for (i = 0; i < FieldHeight ; i += Y_HeightDistance)
    {
        LPointer = VCTRL_GetLinePointer(i, Yaddress, Stride, BtmField);

        for (j = 0; j < Width - 4; j += Y_WidthDistance)
        {
            FrameCrc += VCTRL_GetU32Crc(j, LPointer);
        }
    }

    for (i = 0; i < chrom_height; i += chrom_HeightDistance)
    {
        LPointer = VCTRL_GetLinePointer(i, Caddress, Stride, BtmField);

        for (j = 0; j < 2 * chrom_width - 4; j += chrom_WidthDistance)
        {
            FrameCrc += VCTRL_GetU32Crc(j, LPointer);
        }
    }

    return FrameCrc;
}

/***********************************************************/
/*                       计算场对校验码                    */
/***********************************************************/
SINT32 VCTRL_CalcActualCrc(VID_STD_E eVidStd, IMAGE *pImage)
{
    UINT32  CrcWidth, CrcHeight, CrcStride;
    UINT32  OffsetY,  OffsetC;
    UINT8  *Yaddress = NULL;
    UINT8  *Caddress = NULL;
    UINT8  *pYAddr   = NULL;
    UINT8  *pCAddr   = NULL;

    if (NULL == pImage)
    {
        dprint(PRN_ERROR, "%s pImage = null\n", __func__);
        return VCTRL_ERR;
    }
    
    Yaddress = (UINT8 *)MEM_Phy2Vir(pImage->top_luma_phy_addr);
    if (NULL == Yaddress)
    {
        dprint(PRN_ERROR, "%s FATAL: YPhyAddr = %x, Yaddress = NULL\n", __func__, pImage->top_luma_phy_addr);
        return VCTRL_ERR;
    }

    Caddress = (UINT8 *)MEM_Phy2Vir(pImage->top_chrom_phy_addr);
    if (NULL == Caddress)
    {
        dprint(PRN_ERROR, "%s FATAL: CPhyAddr = %x, Caddress = NULL\n", __func__, pImage->top_chrom_phy_addr);
        return VCTRL_ERR;
    }
    dprint(PRN_CRC, "%s: YPhyAddr = %x, Yaddress = %p, CPhyAddr = %x, Caddress = %p\n", __func__, pImage->top_luma_phy_addr, Yaddress, pImage->top_chrom_phy_addr, Caddress);

    /*注意，HEVC按照显示宽高对齐做的CRC，而其他协议是按照解码宽高做的CRC*/
    CrcStride = pImage->image_stride/16;
    if (STD_HEVC == eVidStd)
    {
        CrcWidth  = ((pImage->disp_width  + 15) / 16) * 16;
        CrcHeight = ((pImage->disp_height + 15) / 16) * 16;
        OffsetY   = pImage->top_offset* CrcStride + pImage->left_offset;
        OffsetC   = (pImage->top_offset >> 1) * CrcStride + pImage->left_offset;
        pYAddr    = Yaddress + OffsetY;
        pCAddr    = Caddress + OffsetC;
    }
    else
    {
        CrcWidth  = ((pImage->image_width  + 15) / 16) * 16;
        CrcHeight = ((pImage->image_height + 15) / 16) * 16;
        pYAddr    = Yaddress;
        pCAddr    = Caddress;
    }
    
    pImage->ActualCRC[0] = VCTRL_CalcFieldCrc(pYAddr, pCAddr, CrcWidth, CrcHeight/2, CrcStride, 0);  // 顶场
    pImage->ActualCRC[1] = VCTRL_CalcFieldCrc(pYAddr, pCAddr, CrcWidth, CrcHeight/2, CrcStride, 1);  // 底场

    dprint(PRN_CRC, "ActualCRC = %x, %x, CrcWidth = %d, CrcHeight = %d, CrcStride = %d\n", pImage->ActualCRC[0], pImage->ActualCRC[1], CrcWidth, CrcHeight, CrcStride);

    return VCTRL_OK;
}

