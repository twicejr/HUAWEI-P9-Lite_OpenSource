/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r3wGH0F8avvLS64Dy+cLaj2fG07bHbpbbDbasAwFLmd4jkl1uh4N56VyqptiapirVDfNp
Fn66P/F9VvZCR/OObAVasUWnkC7HZ7KWXSOCGKgR2pqgwhsYRuST8NJQhxhS7A==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************** 
*
* Copyright (c) 2009 Hisilicon - All Rights Reserved
*
* File: $vdm_drv.c$
* Date: $2009/05/08$
* Revision: $v1.0$
* Purpose: VDEC driver interface.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20090508   q45134            Original
*
************************************************************************/

#include "public.h"
#include "vdm_hal.h"
#include "vdm_drv.h"
#include "postprocess.h"
#include "vfmw_ctrl.h"
#ifdef HIVDEC_SMMU_SUPPORT
#include "smmu.h"
#endif

SINT32 CapItem[][7] = 
{
    /* width, height, pmv, fs(min), fs(mid), fs(max),  scdbuf */
    {176,   144,    4,    10,      11,       12,         512*1024},      // CAP_LEVEL_MPEG_QCIF
    {352,   288,    4,    10,      11,       12,         768*1024},      // CAP_LEVEL_MPEG_CIF
    {720,   576,    4,    10,      11,       12,         1024*1024},     // CAP_LEVEL_MPEG_D1
    {1280,  768,    4,    10,      11,       12,         2*1024*1024},   // CAP_LEVEL_MPEG_720
    {1920,  1088,   4,    10,      11,       12,         3*1024*1024},   // CAP_LEVEL_MPEG_FHD
    {176,   144,    15,   19,      22,       24,         512*1024},      // CAP_LEVEL_H264_QCIF
    {352,   288,    15,   19,      22,       24,         768*1024},      // CAP_LEVEL_H264_CIF
    {720,   576,    9,    15,      16,       17,         1024*1024},     // CAP_LEVEL_H264_D1
    {1280,  768,    6,    13,      13,       14,         2*1024*1024},   // CAP_LEVEL_H264_720
    {1920,  1088,   6,    13,      13,       13,         2*1024*1024},   // CAP_LEVEL_H264_FHD
    {5632,  4224,   1,    3,       3,        3,          16*1024*1024},  // CAP_LEVEL_H264_BYDHD
   		
    {1280,   800,      6,    13,      13,       14,     2*1024*1024},    // CAP_LEVEL_1280x800
    {800,    1280,     6,    13,      13,       14,     2*1024*1024},    // CAP_LEVEL_800x1280
    {1488,   1280,     6,    13,      13,       14,     3*1024*1024},    // CAP_LEVEL_1488x1280
    {1280,   1488,     6,    13,      13,       14,     3*1024*1024},    // CAP_LEVEL_1280x1488 
    {2160,   1280,     6,    13,      13,       13,     3*1024*1024},    // CAP_LEVEL_2160x1280
    {1280,   2176,     6,    13,      13,       13,     3*1024*1024},    // CAP_LEVEL_1280x2160
    {2160,   2176,     4,    11,      11,       11,     4*1024*1024},    // CAP_LEVEL_2160x2160 
    {4096,   2304,     2,     9,       9,        9,     5*1024*1024},    // CAP_LEVEL_4096x2160 
    {2304,   4096,     2,     9,       9,        9,     5*1024*1024},    // CAP_LEVEL_2160x4096 
    {4096,   4096,     2,     9,       9,        9,     8*1024*1024},    // CAP_LEVEL_4096x4096 
    {8192,   4096,     2,     9,       9,        9,    10*1024*1024},    // CAP_LEVEL_8192x4096 
    {4096,   8192,     2,     9,       9,        9,    10*1024*1024},    // CAP_LEVEL_4096x8192 
    {8192,   8192,     1,     3,       3,        3,    20*1024*1024},    // CAP_LEVEL_8192x8192

    {1920,  1088,   1,    3,       3,        3,          2*1024*1024},   // CAP_LEVEL_SINGLE_IFRAME_FHD
    {1920,  1088,   1,    3,       3,        3,          2*1024*1024},   // CAP_LEVEL_USER_DEFINE_WITH_OPTION
    
    {1920,  1088,   17,    26,      26,       26,         2*1024*1024},  // CAP_LEVEL_MVC_FHD
    
    {192,   192,    15,   19,      22,       24,         512 * 1024},    // CAP_LEVEL_HEVC_QCIF
    {384,   320,    15,   19,      22,       24,         768 * 1024},    // CAP_LEVEL_HEVC_CIF
    {768,   576,    9,    15,      16,       17,         1024 * 1024},   // CAP_LEVEL_HEVC_D1
    {1280,  768,    6,    13,      13,       14,         2 * 1024 * 1024}, // CAP_LEVEL_HEVC_720
    {1920,  1088,   6,    13,      13,       13,         2*1024*1024},   // CAP_LEVEL_HEVC_FHD
    {4096,	2304,	4,     4,       4,        4,		 16*1024*1024},	 // CAP_LEVEL_HEVC_UHD
};

/************************************************************************/
/*  模块内共享数据                                                      */
/************************************************************************/
UINT32 g_UpMsg[MAX_VDH_NUM][UP_MSG_SIZE];//上行消息镜像
VDMHAL_HWMEM_S    g_HwMem[MAX_VDH_NUM];
VDMHAL_REPAIR_PARAM_S g_RepairParam[MAX_VDH_NUM][2];
VDMHAL_DEC_REPORT_S   g_DecReport[MAX_VDH_NUM];
VDMHAL_BACKUP_S       g_BackUp[MAX_VDH_NUM];
CHAN_CTX g_ChanCtx;

/* 是否打开帧场自适应 */
UINT32 USE_FF_APT_EN = 1;

VDMDRV_PARAM_S g_VdmDrvParam[MAX_VDH_NUM];
static SINT32  s_VdmIsInISR[MAX_VDH_NUM] = {0};

static VDMDRV_SLEEP_STAGE_E  s_eVdmDrvSleepState[MAX_VDH_NUM] = {VDMDRV_SLEEP_STAGE_NONE};

extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];
VOID VDMDRV_Init( SINT32 VdhId )
{
    memset(&g_VdmDrvParam[VdhId], 0, sizeof(VDMDRV_PARAM_S));
    s_eVdmDrvSleepState[VdhId] = VDMDRV_SLEEP_STAGE_NONE;
}

VOID VDMDRV_Reset( SINT32 VdhId )
{
    memset(&g_VdmDrvParam[VdhId], 0, sizeof(VDMDRV_PARAM_S));
    return;
}


VOID VDMDRV_SetPriority(SINT32 *pPrioArray)
{
    SINT32 i, j, total;
    SINT32 MaxPrio, MaxPrioChanID = 0;
    SINT32 *pPriorTab = g_ChanCtx.ChanIdTabByPrior; 

    total = 0;
    for (i=0; i<MAX_CHAN_NUM; i++)
    {
        /* 寻找优先级最高的通道 */
        MaxPrio = 0;
        for (j=0; j<MAX_CHAN_NUM; j++)
        {
            if (pPrioArray[j] > MaxPrio)
            {
                MaxPrio = pPrioArray[j];
                MaxPrioChanID = j;
            }
        }

        /* 如果剩下通道都无需调度，把pPriorTab剩余节点都填成-1; 否则记录此节点 */
        if ( 0 >= MaxPrio )  
        {
            for ( j=total; j<MAX_CHAN_NUM; j++ )
            {
                pPriorTab[j] = -1;
            }
            break;
        }
        else
        {
            pPriorTab[total++] = MaxPrioChanID;
            pPrioArray[MaxPrioChanID] = 0;  /* 避免下次再选到这个通道 */
        }
    }
    
    return;
}

VOID VDMDRV_AdjustPriorityAfterDec(SINT32 CurChanId)
{
    SINT32 i = 0;
    SINT32 TabPos = 0, TmpChanId = 0;
    SINT32 *pPriorTab = g_ChanCtx.ChanIdTabByPrior; 
    SINT32 *pPrioArray = g_ChanCtx.PriorByChanId;

    for (i=0; i<MAX_CHAN_NUM; i++)
    {
        if (pPriorTab[i] == CurChanId)
        {
            TabPos = i;
			break;
        }
    }

    for (i=TabPos; i<(MAX_CHAN_NUM-1); i++)
    {
        if (pPriorTab[i+1] < 0)
        {
            break;
        }
        
        if (pPrioArray[pPriorTab[i+1]] >= pPrioArray[pPriorTab[i]])
        {
            TmpChanId = pPriorTab[i];
            pPriorTab[i] = pPriorTab[i+1];
			pPriorTab[i+1] = TmpChanId;
        }
    }	
    
    return;
}

/* 准备休眠: 收到此命令后把当前工作完成，但不会寻找下一个解码通道 */
SINT32 VDMDRV_PrepareSleep(SINT32 VdhId)
{
    SINT32 ret = VDMDRV_OK;

    if (s_eVdmDrvSleepState[VdhId] == VDMDRV_SLEEP_STAGE_NONE)
	{
        if (g_VdmDrvParam[VdhId].VdmStateMachine == VDM_NULL_STATE)
        {
            s_eVdmDrvSleepState[VdhId] = VDMDRV_SLEEP_STAGE_SLEEP;
        }
        else
        {
            s_eVdmDrvSleepState[VdhId] = VDMDRV_SLEEP_STAGE_PREPARE;
        }
        
		ret = VDMDRV_OK;
	}
	else
	{
        ret = VDMDRV_ERR;
	}
	
    return ret;
}

/* 查询休眠: 返回休眠进行到何种阶段 */
VDMDRV_SLEEP_STAGE_E VDMDRV_GetSleepStage(SINT32 VdhId)
{
    return s_eVdmDrvSleepState[VdhId];
}

/* 强制休眠: 无法自然休眠，强制复位VdmDrv并且令其进入sleep */
VOID VDMDRV_ForceSleep(SINT32 VdhId)
{
	if (s_eVdmDrvSleepState[VdhId] != VDMDRV_SLEEP_STAGE_SLEEP)
	{
        VDMDRV_Reset(VdhId);
		s_eVdmDrvSleepState[VdhId] = VDMDRV_SLEEP_STAGE_SLEEP;
	}

	dprint(PRN_FATAL,"====== forece VDM sleep! ======\n");
	
    return;
}

/* 退出休眠: 恢复正常运行 */
VOID VDMDRV_ExitSleep(SINT32 VdhId)
{
    VDMDRV_OpenHardware(VdhId);
    s_eVdmDrvSleepState[VdhId] = VDMDRV_SLEEP_STAGE_NONE;
}


/* 启动修补，StateAfterRepair是启动后的VDMDRV新状态 */
VOID VDMDRV_StartRepair( VDMDRV_STATEMACHINE_E StateAfterRepair, SINT32 VdhId)
{
    VDMHAL_StartHwRepair(VdhId);
	g_VdmDrvParam[VdhId].VdmStateMachine = StateAfterRepair;
	return;
}

/* 启动解码 */
VOID VDMDRV_StartDec(SINT32 VdhId)
{
    VDMHAL_StartHwDecode(VdhId);
	g_VdmDrvParam[VdhId].VdmStateMachine = VDM_DECODE_STATE;
	return;
}

SINT32 VDMDRV_IsChanDec( SINT32 ChanID )
{
    if (g_ChanCtx.ChanDecByVdhPlusOne[ChanID] != 0)
    {
        return 1;//the channel is  being decoded.
    }
    else
    {
        return 0;
    }
}

VOID VDMDRV_SetChanIsDec( SINT32 ChanID, SINT32 VdhID )
{
    g_ChanCtx.ChanDecByVdhPlusOne[ChanID] = VdhID + 1;
	VDMDRV_AdjustPriorityAfterDec(ChanID);
	
    return;
}

VOID VDMDRV_ClearChanIsDec( SINT32 ChanID )
{
    g_ChanCtx.ChanDecByVdhPlusOne[ChanID] = 0;
    return;
}

VOID VDMDRV_ActivateVDH(SINT32 VdhId)
{
    /*随后由g_VdmDrvParam[VdhId]来指示各个VDH的驱动参数*/
    SINT32 i;
    UINT32 dat      = 0;
    UINT32 currtime = 0;
    VDMDRV_STATEMACHINE_E *pVdmStateMachine = &g_VdmDrvParam[VdhId].VdmStateMachine;
    SINT32 *pPriorTab       = g_ChanCtx.ChanIdTabByPrior;
    SINT32 *pErrRatio       = &g_VdmDrvParam[VdhId].ErrRatio;
    SINT32 *pChanId         = &g_VdmDrvParam[VdhId].ChanId;   
    UINT32 *pStartTime      = &g_VdmDrvParam[VdhId].StartTime;
    VOID  **ppDecParam      = &g_VdmDrvParam[VdhId].pDecParam; 
    VID_STD_E *pVidStd      = &g_VdmDrvParam[VdhId].VidStd;
    SINT32  Mb0QpInCurrPic  = 0x0F;
    UINT32 *pMb0QpInCurrPic = &Mb0QpInCurrPic;
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};

    /* 选择一个新的解码通道，开始下一个任务 */
    for (i=0; i<MAX_CHAN_NUM; i++)
    {
		if ( pPriorTab[i] < 0 )
        {
            break;
        }
		
        *pChanId = pPriorTab[i];
        
		if (VCTRL_OK != VCTRL_IsChanActive(*pChanId))
		{
            //dprint(PRN_ERROR, "%s The channel %d is not active\n", __func__, *pChanId); // 这个打印太多，且对定位问题没有太大帮助，注释掉。 y00226912
		    continue;
		}

        if (VDMDRV_IsChanDec(*pChanId) == 1)
		{
            dprint(PRN_DBG, "The channel %d is decoding\n", *pChanId);
            continue;
		}
		
        *ppDecParam = NULL;
        *ppDecParam = VCTRL_GetDecParam(*pChanId);
        
        if (NULL == *ppDecParam)
        {
            dprint(PRN_DBG, "The channel %d DEC PARAM is not ready(pDecParam == NULL)\n", *pChanId);
            continue;
        }

        *pVidStd = VCTRL_GetVidStd(*pChanId);
        
        if(0)
        {
            ;
        }
    #ifdef VFMW_MPEG4_SUPPORT    
        else if ( 1 == VDMDRV_IsMpeg4NvopCopy(*pVidStd, *ppDecParam) )
        {
            if (POSTPRO_TRUE == PostPro_CopyYuv(*ppDecParam, VdhId))
            {
                *pErrRatio = 0;
                VDMDRV_StartRepair(VDM_REPAIR_STATE_0, VdhId);
				VDMDRV_SetChanIsDec(*pChanId, VdhId); //标记此通道被解码
                if (CHECK_REC_POS_ENABLE(STATE_VDH_REPAIR))
                {
                    currtime = VFMW_OSAL_GetTimeInMs();	
                    if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
                    {
                        last_rec_pos_time[*pChanId] = currtime;
                        dat = ((*pChanId)<<24) + (STATE_VDH_REPAIR<<16) + VdhId;
                        REC_POS(dat);
                    }
                }
			}
        }
    #endif    
    #ifdef VFMW_VC1_SUPPORT    
        else if ( 1 == VDMDRV_IsVc1SkpicCopy(*pVidStd, *ppDecParam) )//vc1 copy
        {
            dprint(PRN_DBG,"---SKIP REPAIR!---\n");
            if (POSTPRO_TRUE == PostPro_CopyYuv_Vc1(*ppDecParam, VdhId))
            {
                *pErrRatio = 0;
                VDMDRV_StartRepair(VDM_REPAIR_STATE_0, VdhId);
				VDMDRV_SetChanIsDec(*pChanId, VdhId); //标记此通道被解码
                if (CHECK_REC_POS_ENABLE(STATE_VDH_REPAIR))
                {
                    currtime = VFMW_OSAL_GetTimeInMs();	
                    if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
                    {
                        last_rec_pos_time[*pChanId] = currtime;
                        dat = ((*pChanId)<<24) + (STATE_VDH_REPAIR<<16) + VdhId;
                        REC_POS(dat);
                    }
                }
            }
        }
    #endif   
    #ifdef VFMW_VP6_SUPPORT
        else if ( 1 == VDMDRV_IsVp6NvopCopy(*pVidStd, *ppDecParam))
        {
            dprint(PRN_DBG,"---SKIP REPAIR!---\n");
            if (POSTPRO_TRUE == PostPro_CopyYuv_Vp6(*ppDecParam, VdhId))
            {
                *pErrRatio = 0;
                VDMDRV_StartRepair(VDM_REPAIR_STATE_0, VdhId);
				VDMDRV_SetChanIsDec(*pChanId, VdhId); //标记此通道被解码
                if (CHECK_REC_POS_ENABLE(STATE_VDH_REPAIR))
                {
                    currtime = VFMW_OSAL_GetTimeInMs();	
                    if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
                    {
                        last_rec_pos_time[*pChanId] = currtime;
                        dat = ((*pChanId)<<24) + (STATE_VDH_REPAIR<<16) + VdhId;
                        REC_POS(dat);
                    }
                }
            }
        }
    #endif    
        else
        {
            if ( VDMHAL_OK != VDMHAL_PrepareDec(*pVidStd, *ppDecParam, VdhId) )
            {
                dprint(PRN_FATAL, "VDM Start Fail 2 !\n");
                *pVdmStateMachine = VDM_NULL_STATE;
                *pErrRatio = 100;
                VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic, NULL, VdhId);
                VDMDRV_Reset(VdhId);
				VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
            }
			else
			{
                *pStartTime = VFMW_OSAL_GetTimeInMs();
				g_VfmwGlobalStat[VdhId].u32VaLastStartTime = *pStartTime;
				VDMDRV_StartDec(VdhId);
				VDMDRV_SetChanIsDec(*pChanId, VdhId); //标记此通道被解码
            #ifdef VFMW_SCD_LOWDLY_SUPPORT
                DBG_CountTimeInfo(*pChanId, STATE_VDH_START, 0);
            #endif
                if (CHECK_REC_POS_ENABLE(STATE_VDH_START))
                {
                    currtime = VFMW_OSAL_GetTimeInMs();	
                    if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
                    {
                        last_rec_pos_time[*pChanId] = currtime;
                        dat = ((*pChanId)<<24) + (STATE_VDH_START<<16) + VdhId;
                        REC_POS(dat);
                    }
                }
			}
        }
        
        break;
    }

	return;    
}

VOID VDMDRV_AfterDec(SINT32 VdhId, UINT8 FromInt)
{
    /*随后由g_VdmDrvParam[VdhId]来指示各个VDH的驱动参数*/
    VDMDRV_STATEMACHINE_E *pVdmStateMachine = &g_VdmDrvParam[VdhId].VdmStateMachine;
    SINT32 *pErrRatio = &g_VdmDrvParam[VdhId].ErrRatio;
    SINT32 *pChanId = &g_VdmDrvParam[VdhId].ChanId;
    VID_STD_E *pVidStd = &g_VdmDrvParam[VdhId].VidStd;
    VOID  **ppDecParam = &g_VdmDrvParam[VdhId].pDecParam;    
    UINT32 *pStartTime = &g_VdmDrvParam[VdhId].StartTime;
    SINT32 *pVdmTimeOut = &g_VdmDrvParam[VdhId].VdmTimeOut;
    UINT32  Mb0QpInCurrPic = 0x0F;
    UINT32 *pMb0QpInCurrPic = &Mb0QpInCurrPic;
    SINT32 *pDecErrFrameNum = &s_pstVfmwChan[*pChanId]->stSynExtraData.stChanState.dec_error_frame_num;
    RP_STRATAGE_E eRpStratage;
    LUMA_INFO_S lumaInfo;
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
    UINT32 currtime = 0;
    UINT32 dat = 0;
    GetErrRatio_S Param;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    SINT32 ModuleLowlyEnable = 0;
#endif

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (NULL != s_pstVfmwChan[*pChanId])
    {
        ModuleLowlyEnable = s_pstVfmwChan[*pChanId]->stSynExtraData.s32ModuleLowlyEnable;
    }
    else
    {
        ModuleLowlyEnable = 0;
    }
#endif

    memset(&lumaInfo, 0, sizeof(LUMA_INFO_S));    
    if ( VFMW_DIVX3 == (g_BackUp[VdhId].BasicCfg1 & 0x0F) )
    {
        *pMb0QpInCurrPic = g_BackUp[VdhId].SwitchRounding & 0x01;  //use 'Mb0QpInCurrPic' to store 'SwitchRounding'
	}
    else
    {
        *pMb0QpInCurrPic = g_BackUp[VdhId].Mb0QpInCurrPic & 0x1F;
    }
    
    /* 根据状态机的值分别处理 */
    if (VDM_DECODE_STATE == *pVdmStateMachine)
    {
        if (1 == *pVdmTimeOut)
        {
            PostPro_SetFullRepair(*pVidStd, *ppDecParam, VdhId);
            *pErrRatio = 100;
            *pVdmTimeOut = 0;
            dprint(PRN_FATAL, "ISR process vdm timeout! FromInt = %d\n", FromInt);
        }
        else
        {
            memset(&Param, 0, sizeof(GetErrRatio_S));
            Param.VidStd       = *pVidStd;
            Param.pDecParam    = *ppDecParam;
            Param.VdhId        = VdhId;

            *pErrRatio = PostPro_GetErrRatio(&Param);

            dprint(PRN_ERROR,"Chan %d ErrRatio = %d\n", *pChanId, *pErrRatio);
            
            if ( (VFMW_REAL8 == *pVidStd) || (VFMW_REAL9 == *pVidStd) || (VFMW_DIVX3 == *pVidStd) )
			{
                *pErrRatio = 0;
			}
            if ( 0 != (*pErrRatio) )
            {
                (*pDecErrFrameNum)++;
                REPORT_RATIO_NOTZERO(*pChanId, *pErrRatio);
            }
        }

	#ifdef VFMW_MODULE_LOWDLY_SUPPORT
        if(1 == ModuleLowlyEnable)
        {
            *pErrRatio = 0;  // 低延时模式下不启动修补
        }
	#endif
        eRpStratage = PostPro_GetRepairStratage(*pVidStd, *ppDecParam);

		if (0 == *pErrRatio || RP_STRATAGE_DISABLE_REPAIR == eRpStratage)
        {
        #ifdef VFMW_MODULE_LOWDLY_SUPPORT
		    if(1 == ModuleLowlyEnable)
            {
                *pErrRatio = CLIP1(100, (SINT32)(*pErrRatio));
                if(1== g_VdmDrvParam[VdhId].ChanIntState)
                {
                    VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic,&lumaInfo, VdhId);
					s_pstVfmwChan[*pChanId]->stSynCtx.unSyntax.stH264Ctx.pH264DecParam = NULL;
	                VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
                    VDMDRV_Reset(VdhId);
                    VDMDRV_ActivateVDH(VdhId);
                }
                else
                {
                    //如果是行号中断则把数据插入到队列中
                    if( 2== g_VdmDrvParam[VdhId].ChanIntState)
                    {
                        VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic,&lumaInfo, VdhId);
                    }
			        //如果是解码完成中断则启动下一次解码
		            else if(3== g_VdmDrvParam[VdhId].ChanIntState)
                    {
                        VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic,&lumaInfo, VdhId);
                        *pVdmStateMachine = VDM_NULL_STATE;
                        //VCTRL_ClearDecparam(*pChanId);
                        s_pstVfmwChan[*pChanId]->stSynCtx.unSyntax.stH264Ctx.pH264DecParam = NULL;
			            VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
                        VDMDRV_Reset(VdhId);
                        VDMDRV_ActivateVDH(VdhId);
			        }
				    else
				    {
				    }
                 }
		    }
			else
			{
			    *pVdmStateMachine = VDM_NULL_STATE;
                *pErrRatio = CLIP1(100, (SINT32)(*pErrRatio));
                VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic, &lumaInfo, VdhId);
			    VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
                VDMDRV_Reset(VdhId);
                VDMDRV_ActivateVDH(VdhId);
			}
		#else
            *pVdmStateMachine = VDM_NULL_STATE;
            *pErrRatio = CLIP1(100, (SINT32)(*pErrRatio));
            VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic, &lumaInfo, VdhId);
			VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
            VDMDRV_Reset(VdhId);
            VDMDRV_ActivateVDH(VdhId);
        #endif
        }
        else
        {
            if ( 1 == VDMDRV_AvsFirstFldNeedRepair(*pVidStd, *ppDecParam, VdhId) )
            {
            #ifdef VFMW_AVS_SUPPORT    
                *pStartTime = VFMW_OSAL_GetTimeInMs();
                if (VDMHAL_OK == VDMHAL_PrepareRepair(*pVidStd, *ppDecParam, FIRST_REPAIR, VdhId))
                {
// *pVdmStateMachine = VDM_REPAIR_STATE_0;
					g_VfmwGlobalStat[VdhId].u32VaLastStartTime = *pStartTime;
					VDMDRV_StartRepair(VDM_REPAIR_STATE_0, VdhId);
                    if (CHECK_REC_POS_ENABLE(STATE_VDH_REPAIR))
                    {
                        currtime = VFMW_OSAL_GetTimeInMs();	
                        if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
                        {
                            last_rec_pos_time[*pChanId] = currtime;
                            dat = ((*pChanId)<<24) + (STATE_VDH_REPAIR<<16) + VdhId;
                            REC_POS(dat);
                        }
                    }
                }
                else
                {
                    VCTRL_VdmPostProc(*pChanId, 100, *pMb0QpInCurrPic, &lumaInfo, VdhId);	
					VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
                    *pVdmStateMachine = VDM_NULL_STATE;                    
                }
            #endif    
            }
            else if ( 1 == VDMDRV_AvsSecondFldNeedRepair(*pVidStd, *ppDecParam, VdhId) )
            {
            #ifdef VFMW_AVS_SUPPORT    
                *pStartTime = VFMW_OSAL_GetTimeInMs();
                if (VDMHAL_OK == VDMHAL_PrepareRepair(*pVidStd, *ppDecParam, SECOND_REPAIR, VdhId))
                {
					g_VfmwGlobalStat[VdhId].u32VaLastStartTime = *pStartTime;
					VDMDRV_StartRepair(VDM_REPAIR_STATE_1, VdhId);
                    if (CHECK_REC_POS_ENABLE(STATE_VDH_REPAIR))
                    {
                        currtime = VFMW_OSAL_GetTimeInMs();	
                        if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
                        {
                            last_rec_pos_time[*pChanId] = currtime;
                            dat = ((*pChanId)<<24) + (STATE_VDH_REPAIR<<16) + VdhId;
                            REC_POS(dat);
                        }
                    }
				}
                else
                {
                    VCTRL_VdmPostProc(*pChanId, 100, *pMb0QpInCurrPic, &lumaInfo, VdhId);	
					VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
                    *pVdmStateMachine = VDM_NULL_STATE;                    
                }
            #endif    
            }
            else
            {
                *pStartTime = VFMW_OSAL_GetTimeInMs();
                if (VDMHAL_OK == VDMHAL_PrepareRepair(*pVidStd, *ppDecParam, FIRST_REPAIR, VdhId))
                {
					g_VfmwGlobalStat[VdhId].u32VaLastStartTime = *pStartTime;
                    VDMDRV_StartRepair(VDM_REPAIR_STATE_0, VdhId);
                    if (CHECK_REC_POS_ENABLE(STATE_VDH_REPAIR))
                    {
                        currtime = VFMW_OSAL_GetTimeInMs();	
                        if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
                        {
                            last_rec_pos_time[*pChanId] = currtime;
                            dat = ((*pChanId)<<24) + (STATE_VDH_REPAIR<<16) + VdhId;
                            REC_POS(dat);
                        }
                    }
				}
                else
                {
                    VCTRL_VdmPostProc(*pChanId, 100, *pMb0QpInCurrPic, &lumaInfo, VdhId);	
					VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
                    *pVdmStateMachine = VDM_NULL_STATE;                    
                }
            }
        }
    }
    else if (VDM_REPAIR_STATE_0 == *pVdmStateMachine)
    {
        if (1 == *pVdmTimeOut)
        {
            *pVdmTimeOut = 0;
        }

        if ( 1 == VDMDRV_AvsSecondFldNeedRepair(*pVidStd, *ppDecParam, VdhId) )
        {
        #ifdef VFMW_AVS_SUPPORT    
            *pStartTime = VFMW_OSAL_GetTimeInMs();
            if (VDMHAL_OK == VDMHAL_PrepareRepair(*pVidStd, *ppDecParam, SECOND_REPAIR, VdhId))
            {
// *pVdmStateMachine = VDM_REPAIR_STATE_1;
				g_VfmwGlobalStat[VdhId].u32VaLastStartTime = *pStartTime;
                VDMDRV_StartRepair(VDM_REPAIR_STATE_1, VdhId);
                if (CHECK_REC_POS_ENABLE(STATE_VDH_REPAIR))
                {
                    currtime = VFMW_OSAL_GetTimeInMs();	
                    if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
                    {
                        last_rec_pos_time[*pChanId] = currtime;
                        dat = ((*pChanId)<<24) + (STATE_VDH_REPAIR<<16) + VdhId;
                        REC_POS(dat);
                    }
                }
			}
            else
            {
                VCTRL_VdmPostProc(*pChanId, 100, *pMb0QpInCurrPic, &lumaInfo, VdhId);	
				VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
                *pVdmStateMachine = VDM_NULL_STATE;                    
            }
        #endif    
        }
        else if ( 1 == VDMDRV_IsMpeg4NvopCopy(*pVidStd, *ppDecParam) )
        {
        #ifdef VFMW_MPEG4_SUPPORT    
            *pVdmStateMachine = VDM_NULL_STATE;
            *pErrRatio = 0;
            VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic, &lumaInfo, VdhId);
			VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
            VDMDRV_Reset(VdhId);
            VDMDRV_ActivateVDH(VdhId);
        #endif    
        }
        else if ( 1 == VDMDRV_IsVc1SkpicCopy(*pVidStd, *ppDecParam) )//vc1 copy
        {
        #ifdef VFMW_VC1_SUPPORT    
            *pVdmStateMachine = VDM_NULL_STATE;
            *pErrRatio = 0;
            VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic, &lumaInfo, VdhId);
			VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
            VDMDRV_Reset(VdhId);
            VDMDRV_ActivateVDH(VdhId);
        #endif    
        }
        else if ( 1 == VDMDRV_IsVp6NvopCopy(*pVidStd, *ppDecParam) )
        {
        #ifdef VFMW_VP6_SUPPORT    
            *pVdmStateMachine = VDM_NULL_STATE;
            *pErrRatio = 0;
            VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic, &lumaInfo, VdhId);
            VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
            VDMDRV_Reset(VdhId);
            VDMDRV_ActivateVDH(VdhId);
        #endif    
        }
        else
        {
            *pVdmStateMachine = VDM_NULL_STATE;
            *pErrRatio = CLIP1(100, (SINT32)(*pErrRatio));
            VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic, &lumaInfo, VdhId);
			VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
            VDMDRV_Reset(VdhId);
            VDMDRV_ActivateVDH(VdhId);
        }
    }
    else if (VDM_REPAIR_STATE_1 == *pVdmStateMachine)
    {
        if (1 == *pVdmTimeOut)
        {
            *pVdmTimeOut = 0;
        }

        *pVdmStateMachine = VDM_NULL_STATE;
        *pErrRatio = CLIP1(100, (SINT32)(*pErrRatio));
        VCTRL_VdmPostProc(*pChanId, *pErrRatio, *pMb0QpInCurrPic, &lumaInfo, VdhId);
        VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
        VDMDRV_Reset(VdhId);
        VDMDRV_ActivateVDH(VdhId);
    }
    else
    {
        //VDMDRV_Reset();
        /*
            z56361,20101127: 此处reset会带来额外风险，应该去除。因为:
            在线程已获得decparam准备配置硬件却发生了意外的中断(的确发生过，原因不祥)，或者在启动硬件但还没来得及置state machine
            时硬件中断，都会在ISR中进入此分支。如果这个分支中做了reset，会清除本来有效的decparam，给后续操作带来致命的隐患。
		*/
        dprint(PRN_FATAL, "Chan %d VdmStateMachine=%d Error! FromInt = %d.\n", *pChanId, *pVdmStateMachine, FromInt);
        VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
    }

    return;
}


SINT32 VDMDRV_CheckDevice(SINT32 VdhId)
{
    /*随后由g_VdmDrvParam[VdhId]来指示各个VDH的驱动参数,s_eVdmDrvSleepState[]*/
    VDMDRV_STATEMACHINE_E *pVdmStateMachine = &g_VdmDrvParam[VdhId].VdmStateMachine;
    SINT32 *pChanId     = &g_VdmDrvParam[VdhId].ChanId; 
    UINT32 *pStartTime  = &g_VdmDrvParam[VdhId].StartTime;
    UINT32 *pCurrTime   = &g_VdmDrvParam[VdhId].CurrTime;
    SINT32 *pVdmTimeOut = &g_VdmDrvParam[VdhId].VdmTimeOut;
    UINT32  TimeElapse  = 0;
    UINT32  MaxTimeOut  = (0 == gIsFPGA)? VDM_TIME_OUT: VDM_FPGA_TIME_OUT; //FPGA wait longer

    if( NULL == VCTRL_GetDecParam(*pChanId) && VDM_NULL_STATE != *pVdmStateMachine )
    {
        dprint(PRN_FATAL, "Chan %d VCTRL_GetDecParam = NULL && VdmStateMachine (%d) != VDM_NULL_STATE\n", *pChanId, *pVdmStateMachine);
        if (VDMHAL_IsVdmRun(VdhId))
        {
            dprint(PRN_FATAL, "Vdm busy, set ChanResetFlag\n");
            g_VdmDrvParam[VdhId].ChanResetFlag = 1;
        }
        else
        {
            dprint(PRN_FATAL, "Vdm free, VDMDRV_Reset\n");
            g_VdmDrvParam[VdhId].ChanResetFlag = 0;
            VDMDRV_Reset(VdhId);
    		VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
        }
    }

    if (VDM_NULL_STATE != *pVdmStateMachine)
    {
#ifdef VDM_BUSY_WAITTING
        if (VFMW_TRUE == VDMDRV_WaitVdmReadyIfNoIsr(VdhId) )
        {
            VDMDRV_VdmIntServProc(VdhId);
            return VDH_BUSY;
        }
#endif

        *pCurrTime = VFMW_OSAL_GetTimeInMs();
        if (*pCurrTime >= *pStartTime)
        {
            TimeElapse =  (*pCurrTime - *pStartTime);
            /* 防止由于控制疏忽导致异常的时间差 */
            if( TimeElapse > 0x7fffffff || *pStartTime == 0 )
            {
                /* 无效，重新计时 */
                *pStartTime = *pCurrTime;
                TimeElapse = 0;
            }
        }
        else
        {
            *pStartTime = *pCurrTime;
            TimeElapse = 0;
        }

        if (TimeElapse > MaxTimeOut)
        {
            dprint(PRN_ERROR, "VDM Time Out(%d/%d ms), Reset VDM!\n", TimeElapse, MaxTimeOut);
            REPORT_VDMERR(*pChanId);
            VDMHAL_ResetVdm(VdhId);// 2VDH
            *pVdmTimeOut = 1;

            if (g_VdmDrvParam[VdhId].ChanResetFlag == 1)
            {
                g_VdmDrvParam[VdhId].ChanResetFlag = 0;
                *pVdmStateMachine = VDM_NULL_STATE;
                *pVdmTimeOut = 0;
                VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
                return VDH_IDLE;
            }
            else
            {
                VDMDRV_AfterDec(VdhId, 0);
            }
        }

        return VDH_BUSY;
    }
	else if (VDMDRV_SLEEP_STAGE_NONE != s_eVdmDrvSleepState[VdhId])
	{
        if (VDMDRV_SLEEP_STAGE_PREPARE == s_eVdmDrvSleepState[VdhId])
        {
            s_eVdmDrvSleepState[VdhId] = VDMDRV_SLEEP_STAGE_SLEEP;
        }
        return VDH_BUSY;
    }
	else
	{
        return VDH_IDLE;
	}
}

VOID VDMDRV_VdmIntServProc( SINT32 VdhId )
{
	UINT32 dat = 0;
    VDMDRV_STATEMACHINE_E *pVdmStateMachine = NULL;
    SINT32 *pChanId = NULL;
    VOID **ppDecParam = NULL;
    UINT32 Mb0QpInCurrPic = 0x0F;
    UINT32 *pMb0QpInCurrPic = NULL;
    static UINT32 cycle[2] = {0};
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
    UINT32 currtime = 0;
    BACKUP_INFO_S BackUpInfo;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    SINT32 ModuleLowlyEnable = 0;
#endif

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n",__func__, VdhId, (MAX_VDH_NUM - 1));
        return;
    }

    pVdmStateMachine = &g_VdmDrvParam[VdhId].VdmStateMachine;
    pChanId = &g_VdmDrvParam[VdhId].ChanId;
    ppDecParam = &g_VdmDrvParam[VdhId].pDecParam;

    pMb0QpInCurrPic = &Mb0QpInCurrPic;

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (NULL != s_pstVfmwChan[*pChanId])
    {
        ModuleLowlyEnable = s_pstVfmwChan[*pChanId]->stSynExtraData.s32ModuleLowlyEnable;
    }
    else
    {
        ModuleLowlyEnable = 0;
    }
#endif

#ifndef VDM_BUSY_WAITTING    
    VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
	dat = VDMHAL_CheckReg(INT_STATE_REG, VdhId);
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if(1 == ModuleLowlyEnable)
    {
        if( (dat & 1) == 0 && (dat>>2 & 1) == 0)
        {
            VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
			*pVdmStateMachine = VDM_NULL_STATE;
            return;
	    }
    }
	else
	{
	    if( (dat & 1) == 0 )
        {
            VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
			*pVdmStateMachine = VDM_NULL_STATE;
            return;
	    } 
	}
#else	
    if( (dat & 1) == 0 )
    {
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
		*pVdmStateMachine = VDM_NULL_STATE;
        return;
	}
#endif
#endif

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if(1 == ModuleLowlyEnable)
    {
        dat = VDMHAL_CheckReg(VDH_STATE_REG, VdhId);
       
        if(1==((dat>>19)&1) && 1==((dat>>17)&1))
        {
           g_VdmDrvParam[VdhId].ChanIntState = 1;
        }
        else if(1==((dat>>19)&1) && 0==((dat>>17)&1))
        {
            g_VdmDrvParam[VdhId].ChanIntState = 2;
        }
        else if(0==((dat>>19)&1) && 1==((dat>>17)&1))
        {
            if(g_VdmDrvParam[VdhId].ChanIntState == 2)
            {
                g_VdmDrvParam[VdhId].ChanIntState = 3;
            }
            else
            {
                g_VdmDrvParam[VdhId].ChanIntState = 1;
            }
        }
    }
#endif

    s_VdmIsInISR[VdhId] = 1;

    memset(&BackUpInfo, 0, sizeof(BACKUP_INFO_S));
    BackUpInfo.pMb0QpInCurrPic = pMb0QpInCurrPic;
    BackUpInfo.VdhId           = VdhId;
    VDMHAL_BackupInfo(&BackUpInfo);
    
    VDMHAL_ClearIntState(VdhId);
#ifdef VFMW_SCD_LOWDLY_SUPPORT
    DBG_CountTimeInfo(*pChanId, STATE_VDH_INTERRUPT, 0);
#endif
    if (CHECK_REC_POS_ENABLE(STATE_VDH_INTERRUPT))
    {
        currtime = VFMW_OSAL_GetTimeInMs();	
        if ((currtime - last_rec_pos_time[*pChanId]) > g_TraceFramePeriod)
        {
            last_rec_pos_time[*pChanId] = currtime;
            dat = ((*pChanId)<<24) + (STATE_VDH_INTERRUPT<<16) + VdhId;
            REC_POS(dat);
        }
    }
	
    if (g_VdmDrvParam[VdhId].ChanResetFlag == 1)
    {
        g_VdmDrvParam[VdhId].ChanResetFlag = 0;
		VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
		*pVdmStateMachine = VDM_NULL_STATE;
        goto VDM_ISR_RETURN_0;
    }
	
    cycle[VdhId] +=g_BackUp[VdhId].DecCyclePerPic;
	
    /* 统计CPU占用率 */
    if (g_VfmwGlobalStat[VdhId].u32VaLastStartTime != 0 )
    {
        UINT32 CurTime = VFMW_OSAL_GetTimeInMs();
		UINT32 Period;

		/* 检查起始计时值，若不正常重置它 */
        if (g_VfmwGlobalStat[VdhId].u32VaBeginTime + 50000 < g_VfmwGlobalStat[VdhId].u32VaLastStartTime )
        {
            g_VfmwGlobalStat[VdhId].u32VaBeginTime = g_VfmwGlobalStat[VdhId].u32VaLastStartTime;
			g_VfmwGlobalStat[VdhId].u32VaVdmWorkTime = 0;
		}

		g_VfmwGlobalStat[VdhId].u32VaVdmWorkTime += CurTime - g_VfmwGlobalStat[VdhId].u32VaLastStartTime;
		g_VfmwGlobalStat[VdhId].u32VaLastStartTime = 0;

        g_VfmwGlobalStat[VdhId].u32AccVdmKiloCycle       += (g_BackUp[VdhId].DecCyclePerPic >> 10);
        g_VfmwGlobalStat[VdhId].u32PicNum++;

        /* 如果计算时间间隔已到，则算一次VDM占用率 */
		Period = CurTime - g_VfmwGlobalStat[VdhId].u32VaBeginTime;
        if ( Period >=  1000 )
        {
            g_VfmwGlobalStat[VdhId].u32VaVdmLoad = g_VfmwGlobalStat[VdhId].u32VaVdmWorkTime*1000 / Period;

			g_VfmwGlobalStat[VdhId].u32VaBeginTime = 0;
            g_VfmwGlobalStat[VdhId].u32VaVdmKiloCycle = g_VfmwGlobalStat[VdhId].u32AccVdmKiloCycle;
            g_VfmwGlobalStat[VdhId].u32StatTime = Period;
            g_VfmwGlobalStat[VdhId].u32AccVdmKiloCycle = 0;
            g_VfmwGlobalStat[VdhId].u32PicNum = 0;
		}
	}

    /* 对上下文进行检查，避免意外错误导致更严重的问题 */
	if (VDM_NULL_STATE != *pVdmStateMachine)
	{
        if (NULL == *ppDecParam)
        {
            dprint(PRN_FATAL, "Chan %d vdm state machine = %d, but DecParam is null!\n", *pChanId, *pVdmStateMachine);
			if (NULL != VCTRL_GetDecParam(*pChanId))
			{
                dprint(PRN_FATAL, "But Chan %d VCTRL_GetDecParam != NULL\n", *pChanId);
                VCTRL_VdmPostProc(*pChanId, 100, *pMb0QpInCurrPic, NULL, VdhId);
			}
			VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
			*pVdmStateMachine = VDM_NULL_STATE;	
            goto VDM_ISR_RETURN_0;
		}
	}
    if( VCTRL_OK != VCTRL_IsChanActive(*pChanId) )
    {
        dprint(PRN_FATAL,"ISR called but chan %d is not active!\n", *pChanId);
		VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
		*pVdmStateMachine = VDM_NULL_STATE;		
        goto VDM_ISR_RETURN;
	}
	else
	{
	    /*为了防止复位通道造成实际解码参数已经清0，出现空指针，在通道复位完成并且是Start后判断下解码参数指针情况*/
	    if (NULL == VCTRL_GetDecParam(*pChanId))
	    {
            dprint(PRN_FATAL,"ISR called but chan %d is not active!\n", *pChanId);
			VDMDRV_ClearChanIsDec(*pChanId);//标记此通道未被解码
			*pVdmStateMachine = VDM_NULL_STATE;			
            goto VDM_ISR_RETURN;
	    }
	}
	
    VDMDRV_AfterDec(VdhId, 1);

VDM_ISR_RETURN:
    s_VdmIsInISR[VdhId] = 0;
    /* 由于VDMDRV_AfterDec的操作可能选择新的通道解码，因此此处的*pChanId与本次中断的*pChanId已经有可能不一致了，
    只是该函数中未用到，所以可以这样使用，若今后对于该函数功能有扩展，则应该记录本次中断时的通道号，再传入使用 */
	VCTRL_InformVdmFree(*pChanId);

VDM_ISR_RETURN_0:
#ifndef VDM_BUSY_WAITTING  
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
#endif

    return;
}


SINT32 VDMDRV_IsVdmInISR(SINT32 VdhId)
{
    return s_VdmIsInISR[VdhId];
}


VOID VDMDRV_WakeUpVdm( VOID )
{
    SINT32 i;

    for (i=0; i<MAX_VDH_NUM; i++)
    {
        if (VDH_IDLE == VDMDRV_CheckDevice(i))
        {
            VDMDRV_ActivateVDH(i);
        }
    }
	
	return;
}


SINT32 VDMDRV_IsVdmIdle(SINT32 VdhId )
{
    VDMDRV_STATEMACHINE_E *pVdmStateMachine = &g_VdmDrvParam[VdhId].VdmStateMachine;

    if (VDM_NULL_STATE == *pVdmStateMachine)
    {
        return VFMW_TRUE;
    }
    else
    {
        return VFMW_FALSE;
    }
}

SINT32 VDMDRV_IsChanInDec( SINT32 ChanID )
{
    UINT8 i = 0;

    for(i = 0; i < MAX_VDH_NUM; i++)
    {
        if(VDM_NULL_STATE != g_VdmDrvParam[i].VdmStateMachine && ChanID == g_VdmDrvParam[i].ChanId)
        {
            return VFMW_TRUE;
        }
    }

    return VFMW_FALSE;
}

SINT32 VDMDRV_GetCurrChanID(SINT32 VdhId)
{
    return g_VdmDrvParam[VdhId].ChanId;
}


SINT32 VDMDRV_WaitVdmReadyIfNoIsr( SINT32 VdhId )
{
    UINT32 cnt_wait = 0;

    for ( cnt_wait = 0; cnt_wait < COUNT_WAIT_NO_ISR; cnt_wait++ )   /* 循环：等待VDM解码完成 */
    {
        if ( VDMHAL_IsVdmReady(VdhId) )
        {
            break;
        }
        else
        {
            //OSAL_MSLEEP(10);
        }
    }

    if (cnt_wait < COUNT_WAIT_NO_ISR)
    {
        return VFMW_TRUE;
    }
    else
    {
        return VFMW_FALSE;
    }
}


SINT32 VDMDRV_AvsFirstFldNeedRepair(VID_STD_E VidStd, VOID *pDecParam, SINT32 VdhId)
{
#ifdef VFMW_AVS_SUPPORT
    VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][0]);

    if ( (VFMW_AVS == VidStd) && (1==((AVS_DEC_PARAM_S *)pDecParam)->PicStruct) && (pRepairParam[0].ValidGroupNum>0) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
#else
        return 0;    
#endif
}


SINT32 VDMDRV_AvsSecondFldNeedRepair(VID_STD_E VidStd, VOID *pDecParam,SINT32 VdhId)
{
#ifdef VFMW_AVS_SUPPORT
    VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][0]);

    if ( (VFMW_AVS == VidStd) && (1==((AVS_DEC_PARAM_S *)pDecParam)->PicStruct) && (pRepairParam[1].ValidGroupNum>0) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
#else
    return 0;    
#endif
}


SINT32 VDMDRV_IsMpeg4NvopCopy(VID_STD_E VidStd, VOID *pDecParam)
{
#ifdef VFMW_MPEG4_SUPPORT
    MP4_DEC_PARAM_S *pMp4DecParam = (MP4_DEC_PARAM_S *)pDecParam;
    
    if (pDecParam == NULL)
    {
        dprint(PRN_FATAL, "VDMHAL_V200_IsMpeg4NvopCopy point of picture para null, wait forever!!!\n");
        return 0;
    }

    if ( (VFMW_MPEG4 == VidStd) && (1==pMp4DecParam->IsNvopCopy) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
#else
        return 0;    
#endif
}

SINT32 VDMDRV_IsVc1SkpicCopy(VID_STD_E VidStd, VOID *pDecParam)
{
#ifdef VFMW_VC1_SUPPORT   
    VC1_DEC_PARAM_S *pVc1DecParam = (VC1_DEC_PARAM_S *)pDecParam;
    
    if (pDecParam == NULL)
    {
        dprint(PRN_FATAL, "VDMDRV_IsVc1SkpicCopy point of picture para null, wait forever!!!\n");
        return 0;
    }

    if ( (VFMW_VC1 == VidStd) && (1==pVc1DecParam->IsSkpicCopy) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
#else
        return 0;    
#endif
}

SINT32 VDMDRV_IsVp6NvopCopy(VID_STD_E VidStd, VOID *pDecParam)
{
#ifdef VFMW_VP6_SUPPORT
    VP6_DEC_PARAM_S *pVp6DecParam = (VP6_DEC_PARAM_S *)pDecParam;
    
    if (pDecParam == NULL)
    {
        dprint(PRN_FATAL, "VDMDRV_IsVp6NvopCopy point of picture para null, wait forever!!!\n");
        return 0;
    }

    if ( ((VFMW_VP6 == VidStd) || (VFMW_VP6A == VidStd) || (VFMW_VP6F == VidStd)) && (1==pVp6DecParam->IsNvopCopy) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
#else
        return 0;    
#endif
}

VOID VDMDRV_ResetVDH(SINT32 ChanID)
{
    UINT8 i = 0;

    for(i = 0; i < MAX_VDH_NUM; i++)
    {
        if(VDM_NULL_STATE != g_VdmDrvParam[i].VdmStateMachine && ChanID == g_VdmDrvParam[i].ChanId)
        {
            VDMHAL_ResetVdm(i);
            g_VdmDrvParam[i].VdmStateMachine = VDM_NULL_STATE;
            break;
        }
    }
    
}

VOID VDMDRV_PowerOn(VOID)
{
    VCTRL_PowerOn();
    SMMU_InitGlobalReg();
    return;
}

VOID VDMDRV_PowerOff(VOID)
{
    VCTRL_PowerOff();
    return;
}

#ifdef ENV_ARMLINUX_KERNEL
EXPORT_SYMBOL(CapItem);
#endif
