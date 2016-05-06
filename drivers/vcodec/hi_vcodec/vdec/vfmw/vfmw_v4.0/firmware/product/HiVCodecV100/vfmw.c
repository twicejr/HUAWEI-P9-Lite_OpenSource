/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vdec_firmware.c
    版 本 号   : 初稿
    作    者   :
    生成日期   :
    最近修改   :
    功能描述   : firmware的对外接口实现


 修改历史   :
    1.日    期 : 2009-01-08
    作    者   : z56361
    修改内容   :

******************************************************************************/
#include "vfmw.h"
#include "vdm_hal.h"
#include "mem_manage.h"
#include "public.h"
#include "vfmw_ctrl.h"
#include "syntax.h"
#include "vfmw_dts.h"
#ifdef VFMW_VDH_V400R004_SUPPORT
#include "vdm_hal_v400r004_api.h"
#endif
#ifdef VFMW_VC1_SUPPORT
#include "vc1.h"
#include "bitplane.h"
#endif
#ifdef HIVDEC_SMMU_SUPPORT
#include "smmu.h"
#endif


/*======================================================================*/
/*   宏                                                                 */
/*======================================================================*/
#define  VDEC_ASSERT_RET( cond, else_print )                    \
do {                                                            \
    if( !(cond) )                                               \
    {                                                           \
        dprint(PRN_FATAL,"vfmw.c,L%d: %s\n", __LINE__, else_print ); \
        return VDEC_ERR;                                        \
    }                                                           \
}while(0)

#define  VDEC_ASSERT( cond, else_print )                        \
do {                                                            \
    if( !(cond) )                                               \
    {                                                           \
        dprint(PRN_FATAL,"vfmw.c,L%d: %s\n", __LINE__, else_print ); \
        return;                                                 \
    }                                                           \
}while(0)


/*======================================================================*/
/*   全局共享数据                                                       */
/*======================================================================*/
SINT32 g_VfmwEnableFlag = 0;
SINT32 g_VfmwInitCount = 0;

/* vfmw hal  function pointer */
VDMHAL_FUN_PTR_S   g_vdm_hal_fun_ptr; 
/* vfmw osal function pointer */
Vfmw_Osal_Func_Ptr g_vfmw_osal_fun_ptr;


/*======================================================================*/
/*   函数实现                                                           */
/*======================================================================*/
VOID VDM_ResetClock(VOID)
{
	return;
}

VOID VDM_OpenHardware(SINT32 VdhId)
{
    //当前版本不做配置，保持默认值验自动门控
	//WR_VREG( VREG_V400R004_CRG_CLK_EN,  CRG_CLK_EN_DEFAULT_VALUE,  VdhId );
	//WR_VREG( VREG_V400R004_MFDE_CLK_EN, MFDE_CLK_EN_DEFAULT_VALUE, VdhId );

	return;
}

VOID VDM_CloseHardware(SINT32 VdhId)
{
    //FPGA版本不能配0，暂时只能配置成全F
	//WR_VREG( VREG_V400R004_CRG_CLK_EN,  0x0, VdhId );
	//WR_VREG( VREG_V400R004_MFDE_CLK_EN, 0x0, VdhId );

	return;  
}

VOID SCD_OpenHardware(VOID)
{
	return;
}

VOID SCD_CloseHardware(VOID)
{
	return;
}

VOID BPD_OpenHardware(VOID)
{
	return;
}

VOID BPD_CloseHardware(VOID)
{
	return;
}

/***********************************************************************
   获取解码器硬件工作所需要的HAL层公共内存大小
 ***********************************************************************/
SINT32 VDEC_GetHalMemSize(MEM_DESC_S *pHalMem)
{
    SINT32 Size = 0;

    Size = VDMHAL_V400R004_GetHalMemSize();
    if (Size <= 0)
    {
        dprint(PRN_ERROR, "%s GetHalMemSize failed!\n", __func__);
        return VCTRL_ERR;
    }

    pHalMem->Length  = MAX_VDH_NUM * Size;

    pHalMem->Length += MAX_SCD_NUM * SCD_MSG_BUFFER;

    return VCTRL_OK;
}

/************************************************************************
    VDEC 对proc文件系统初始化
 ************************************************************************/
VOID VDEC_OpenModule(VOID)
{
#ifdef ENV_ARMLINUX_KERNEL
    OSAL_InitInterface();
    VFMW_OSAL_ProcInit();
#endif

    VFMW_OSAL_SemaInit(G_VfmwSem);
}


/************************************************************************
    VDEC 对proc文件系统去初始化
 ************************************************************************/
VOID VDEC_ExitModule(VOID)
{
#ifdef ENV_ARMLINUX_KERNEL
    VFMW_OSAL_ProcExit();
#endif
}

/************************************************************************
    VDEC 对VFMW所有的锁进行初始化
 ************************************************************************/
VOID VDEC_SpinLockInit(VOID)
{
    VFMW_OSAL_SpinLockInit(G_SPINLOCK_THREAD);
    VFMW_OSAL_SpinLockInit(G_SPINLOCK_RECORD);
    VFMW_OSAL_SpinLockInit(G_SPINLOCK_VOQUEUE);
    VFMW_OSAL_SpinLockInit(G_SPINLOCK_FSP);
    VFMW_OSAL_SpinLockInit(G_SPINLOCK_DESTROY);
    
    return;
}


/************************************************************************
    VDEC全局初始化
 ************************************************************************/
SINT32 VDEC_Init(VDEC_OPERATION_S *pArgs)
{
    SINT32 ret;
	
    VFMW_OSAL_SemaDown(G_VfmwSem);

    if (NULL == pArgs)
    {
        dprint(PRN_ERROR, "VDEC_InitWithOperation has NULL parameter, error!\n");
        VFMW_OSAL_SemaUp(G_VfmwSem);
        return VDEC_ERR;
    }

    /* 因为OMX和VDEC可能同时并存，所以一方初始化后，
       另一方只需设置回调函数即可，否则重复初始化。 y00226912 */
    if (1 == g_VfmwEnableFlag)
    {
        g_VfmwInitCount++;
        VCTRL_SetCallBack(pArgs->adapter_type, &pArgs->ext_intf);
        VFMW_OSAL_SemaUp(G_VfmwSem);
        return VDEC_OK;
    }
    
    ret = VFMW_IsDtsDataValid();
    if (ret != VDEC_OK)
    {
        dprint(PRN_FATAL, "%s: Dts data invalid!\n", __func__);
        return VDEC_ERR;
    }
    
    // Initialize function pointer
    g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware           = VDM_OpenHardware;
    g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware          = VDM_CloseHardware;
    g_vdm_hal_fun_ptr.pfun_VDMDRV_ResetClock             = VDM_ResetClock;
    g_vdm_hal_fun_ptr.pfun_SCDDRV_OpenHardware           = SCD_OpenHardware;
    g_vdm_hal_fun_ptr.pfun_SCDDRV_CloseHardware          = SCD_CloseHardware;
    g_vdm_hal_fun_ptr.pfun_BPDDRV_OpenHardware           = BPD_OpenHardware;
    g_vdm_hal_fun_ptr.pfun_BPDDRV_CloseHardware          = BPD_CloseHardware;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_GetHalMemSize          = VDMHAL_V400R004_GetHalMemSize;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_OpenHAL                = VDMHAL_V400R004_OpenHAL;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_CloseHAL               = VDMHAL_V400R004_CloseHAL;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem             = VDMHAL_V400R004_ArrangeMem;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm               = VDMHAL_V400R004_ResetVdm;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_GlbReset               = VDMHAL_V400R004_GlbReset;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_ClearIntState          = VDMHAL_V400R004_ClearIntState;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_MaskInt                = VDMHAL_V400R004_MaskInt;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_EnableInt              = VDMHAL_V400R004_EnableInt;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_CheckReg               = VDMHAL_V400R004_CheckReg;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwRepair          = VDMHAL_V400R004_StartHwRepair;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwDecode          = VDMHAL_V400R004_StartHwDecode;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareDec             = VDMHAL_V400R004_PrepareDec;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmReady             = VDMHAL_V400R004_IsVdmReady;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmRun               = VDMHAL_V400R004_IsVdmRun;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareRepair          = VDMHAL_V400R004_PrepareRepair;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_MakeDecReport          = VDMHAL_V400R004_MakeDecReport;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_BackupInfo             = VDMHAL_V400R004_BackupInfo;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_GetCharacter           = VDMHAL_V400R004_GetCharacter;
    g_vdm_hal_fun_ptr.pfun_VDMHAL_WriteScdEMARID         = VDMHAL_V400R004_WriteScdEMARID;

    // Initialize lock
    VDEC_SpinLockInit();

    VDMHAL_GetCharacter();
    MEM_ManagerWithOperation(&pArgs->ext_intf);

    // Initialize hardware and thread
    ret = VCTRL_OpenVfmw(pArgs);
    if (ret == VCTRL_OK)
    {
        g_VfmwEnableFlag = 1;
        g_VfmwInitCount  = 1;
    }
    else
    {
        g_VfmwEnableFlag = 0;
        g_VfmwInitCount = 0;
    }

    // Set callback function
    VCTRL_SetCallBack(pArgs->adapter_type, &pArgs->ext_intf);

    VFMW_OSAL_SemaUp(G_VfmwSem);
    return (ret == VCTRL_OK)? VDEC_OK : VDEC_ERR;
}

/************************************************************************
    VDEC全局去初始化，上层调用此函数使VDEC关闭所有硬件加速，释放所有资源
 ************************************************************************/
SINT32 VDEC_Exit(UINT8 IsSecure)
{
    SINT32 ret;
    ret = VFMW_OSAL_SemaDown(G_VfmwSem);

    /* 因为OMX 和VDEC 可能同时并存，所以任一方不能随便全局去初始化 y00226912 */
    g_VfmwInitCount = (g_VfmwInitCount-1 < 0)? 0: g_VfmwInitCount-1;        
    if (g_VfmwInitCount > 0)
    {
        VFMW_OSAL_SemaUp(G_VfmwSem);
        return VCTRL_OK;
    }
    
    ret = VCTRL_CloseVfmw();
    MEM_ManagerClearOperation();
    
    g_VfmwEnableFlag = 0;
	
    VFMW_OSAL_SemaUp(G_VfmwSem);
    return (ret == VCTRL_OK)? VDEC_OK : VDEC_ERR;
}

static SINT32 VDEC_CheckParam(VDEC_CID_E eCmdID, VOID *pArgs, UINT32 ArgLen)
{
    SINT32 ParamErrFlag = 0;
	
    switch(eCmdID)
    {
        case VDEC_CID_DESTROY_CHAN:                         /* 销毁通道 */
        case VDEC_CID_DESTROY_CHAN_WITH_OPTION:             /* 销毁通道，资源外部释放 */
        case VDEC_CID_GET_CHAN_STATE:                       /* 获取通道状态信息 */
        case VDEC_CID_START_CHAN:                           /* 启动通道 */
        case VDEC_CID_STOP_CHAN:                            /* 停止通道 */
        case VDEC_CID_RESET_CHAN:                           /* 复位通道 */
        case VDEC_CID_RELEASE_STREAM:                       /* 释放raw buffer */
        case VDEC_CID_RESET_CHAN_WITH_OPTION:               /* 复位通道有选择地保留某些通道属性 */
		case VDEC_CID_ACTIVATE_CHANNEL:                     /* 动态帧存buffer可用触发解码 */
			ParamErrFlag = 0;
            break;
    	    
        case VDEC_CID_GET_CAPABILITY:                       /* 获取解码器能力 */
        case VDEC_CID_GET_CHAN_CFG:                         /* 获取通道配置 */
        case VDEC_CID_CFG_CHAN:                             /* 配置通道 */			
        case VDEC_CID_SET_STREAM_INTF:                      /* 设置通道的码流接口 */
        case VDEC_CID_GET_IMAGE_INTF:                       /* 获取通道的图象接口 */
        case VDEC_CID_GET_HAL_MEMSIZE:                      /* 获取解码器所需要的HAL层内存总量 */
        case VDEC_CID_GET_CHAN_MEMSIZE:                     /* 获取通道在特定能力级别下需要占用的内存总量 */
        case VDEC_CID_CREATE_CHAN:                          /* 创建通道 */
        case VDEC_CID_CREATE_CHAN_WITH_OPTION:              /* 创建特定大小的解码通道 */    
        case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:  /* 获取通道所需内存细节 */  
		case VDEC_CID_BIND_MEM_TO_CHANNEL:                  /* 绑定动态帧存申请的内存 */  
            if ( NULL == pArgs || 0 == ArgLen )
            {
               dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
               ParamErrFlag = 1;
            }
            break;
            
       default:
            dprint(PRN_FATAL,"vfmw.c,L%d: unsupport cmd id %d\n", __LINE__, eCmdID); 
            ParamErrFlag = 1;
            break;
    }

	if (ParamErrFlag)
	{
	    return VDEC_ERR;
	}
	else
	{
	    return VDEC_OK;
	}
}

static SINT32 VDEC_ProcessCommand(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    SINT32  ret     = VDEC_OK;
	SINT32 *p32     = NULL;
	UINT64 *pulong  = NULL;
    VDEC_CHAN_OPTION_S *pOption = NULL;
    SINT32  VdmMem[3], ScdMem[3];
    IMAGE_INTF_S *pImgIntf;
    DETAIL_MEM_SIZE DetailMemSize;
	
	switch(eCmdID)
	{
    	case VDEC_CID_GET_CAPABILITY:	/* 获取解码器能力 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		VCTRL_GetVdecCapability((VDEC_CAP_S*)pArgs);
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
    
    	case VDEC_CID_CREATE_CHAN:		/* 创建通道 */
    		p32 = (UINT32 *)pArgs;
    		ret = VCTRL_CreateChan(p32[0], (MEM_DESC_S*)(&p32[1]));
            if (ret >= 0)
            {
        		p32 = (SINT32 *)pArgs;
        		p32[0] = ret;  /* 注意，此命令中pArgs既传递输入参数(能力级),又传递输出参数(通道号) */
    			ret = VDEC_OK;
            }
            else
            {
    			ret = VDEC_ERR;
            }
    		break;
    		
    	case VDEC_CID_CREATE_CHAN_WITH_OPTION:	/* 创建特定大小的解码通道 */
    		pulong  = (UINT64 *)pArgs;
            pOption = *(VDEC_CHAN_OPTION_S **)(pulong + 1);
    		ret = VCTRL_CreateChanWithOption(pulong[0], pOption, VCTRL_IGNOR_EXTRA, 0);
            if (ret >= 0)
            {
        		p32 = (SINT32 *)pArgs;
        		p32[0] = ret;  /* 注意，此命令中pArgs既传递输入参数(能力级),又传递输出参数(通道号) */
    			ret = VDEC_OK;
            }
            else
            {
    			ret = VDEC_ERR;
            }
    		break;
            
    	case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
    		pulong  = (UINT64 *)pArgs;
            pOption = *(VDEC_CHAN_OPTION_S **)(pulong + 1);
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
            ret = VCTRL_GetChanMemSizeWithOption(pulong[0], pOption, &DetailMemSize, VCTRL_ADD_EXTRA);
            if (VCTRL_OK == ret)
    		{
    		    p32    = (SINT32*)pArgs;
    			p32[0] = DetailMemSize.VdhDetailMem;
    			p32[1] = DetailMemSize.ScdDetailMem;
    			p32[2] = DetailMemSize.CtxDetailMem;			
    			ret = VDEC_OK;
    		}
    		else
    		{
    			ret = VDEC_ERR;
    		}
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
			
    	case VDEC_CID_DESTROY_CHAN: 	/* 销毁通道 */
    		ret = VCTRL_DestroyChan(ChanID);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		break;
    
    	case VDEC_CID_DESTROY_CHAN_WITH_OPTION: 	/* 销毁通道，资源外部释放 */ 
    		ret = VCTRL_DestroyChanWithOption(ChanID);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		break;
			
    	case VDEC_CID_GET_CHAN_CFG: 	/* 获取通道配置 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		ret = VCTRL_GetChanCfg(ChanID, (VDEC_CHAN_CFG_S*)pArgs);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);		
    		break;
    
    	case VDEC_CID_CFG_CHAN: 		/* 配置通道 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		ret = VCTRL_ConfigChan(ChanID, (VDEC_CHAN_CFG_S*)pArgs);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
#if defined(VFMW_SCD_LOWDLY_SUPPORT) || defined(VFMW_AVSPLUS_SUPPORT)
    		VCTRL_LoadDspCode(ChanID);
#endif
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
    
    	case VDEC_CID_GET_CHAN_STATE:	/* 获取通道状态信息 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		VCTRL_GetChanState(ChanID, (VDEC_CHAN_STATE_S *)pArgs);
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
    
    	case VDEC_CID_START_CHAN:		/* 启动通道 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		ret = VCTRL_StartChan(ChanID);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);				
    		break;
						
    	case VDEC_CID_STOP_CHAN:		/* 停止通道 */
    		ret = VCTRL_StopChanWithCheck(ChanID);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		if (ret != VDEC_OK)
    		{
    			dprint(PRN_FATAL,"Stop chan %d failed!\n", ChanID);
    		}
    		break;
    
    	case VDEC_CID_RESET_CHAN:		/* 复位通道 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		ret = VCTRL_ResetChan(ChanID);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
    
    	case VDEC_CID_RELEASE_STREAM:	/* 释放raw buffer */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		ret = VCTRL_ReleaseStream(ChanID);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
    		
    	case VDEC_CID_SET_STREAM_INTF:	/* 设置通道的码流接口 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		ret = VCTRL_SetStreamInterface(ChanID, pArgs);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);		
    		break;
    
    	case VDEC_CID_GET_IMAGE_INTF:	/* 获取通道的图象接口 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		pImgIntf = (IMAGE_INTF_S *)pArgs;
    		pImgIntf->image_provider_inst_id = ChanID;
    		pImgIntf->read_image = VCTRL_GetChanImage;
    		pImgIntf->release_image = VCTRL_ReleaseChanImage;
    		ret = VDEC_OK;
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
            
		case VDEC_CID_GET_HAL_MEMSIZE:
    		if ( VCTRL_OK == VDEC_GetHalMemSize((MEM_DESC_S *)pArgs) )
    		{
    			ret = VDEC_OK;
    		}
    		else
    		{
    			ret = VDEC_ERR;
    		}
            break;
                    
    	case VDEC_CID_GET_CHAN_MEMSIZE:    /* 获取通道在特定能力级别下需要占用的内存总量 */
    		p32 = (UINT32 *)pArgs;
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		if ( VCTRL_OK == VCTRL_GetChanMemSize( p32[0], VdmMem, ScdMem) )
    		{
    			CHAN_MEM_BUDGET_S *pMem = (CHAN_MEM_BUDGET_S*)pArgs;
    			pMem->MinMemSize	= VdmMem[0] + ScdMem[0];
    			pMem->NormalMemSize = VdmMem[1] + ScdMem[1];
    			pMem->FluentMemSize = VdmMem[2] + ScdMem[2];
    			ret = VDEC_OK;
    		}
    		else
    		{
    			ret = VDEC_ERR;
    		}
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
			
    	case VDEC_CID_RESET_CHAN_WITH_OPTION:		/* 复位通道有选择地保留某些通道属性 */
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		ret = VCTRL_ResetChanWithOption(ChanID, (VDEC_CHAN_RESET_OPTION_S *)pArgs);
    		ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    		VCTRL_EnableAllInt();
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);		
    		break;
    		
       case VDEC_CID_BIND_MEM_TO_CHANNEL:
    		// 1 set chan ctrl state
    		ret = VCTRT_SetChanCtrlState(ChanID, CHAN_FRAME_STORE_ALLOC);
    		if(VDEC_OK != ret)
    		{
    			dprint(PRN_ERROR, "%s set chan ctrl state CHAN_FRAME_STORE_ALLOC failed!\n", __func__);
    			ret = VDEC_ERR;
    			break;
    		}	
    
    		// 2 release pmv men and delete dec men node
    		ret = VCTRL_RlsAllFrameNode(ChanID); //释放之前已经动态分配的帧存
    		if(VDEC_OK != ret)
    		{
    			dprint(PRN_ERROR,"DFS, rls chan %d frame store fail!\n", ChanID);
    			break;
    		}
    		dprint(PRN_FS,"DFS, rls chan %d frame store success!\n", ChanID);
    
    		// 3 bind dec mem to fwm
    		VCTRL_SetFsParamToChan(ChanID, (VDEC_CHAN_FRAME_STORES*)pArgs);
        		
    		// 4 set chan ctrl state
    		ret = VCTRT_SetChanCtrlState(ChanID, CHAN_NORMAL);
    		if(VDEC_OK != ret)
    		{
    			dprint(PRN_ERROR, "%s set chan ctrl state CHAN_NORMAL failed!\n", __func__);
    			ret = VDEC_ERR;
    		}	  
    		break;
    		
       case VDEC_CID_ACTIVATE_CHANNEL:
    		//set chan fs partition state success
    		VFMW_OSAL_SpinLock(G_SPINLOCK_THREAD);
    		VCTRL_SetChanFsPartitionState(ChanID, FSP_PARTITION_STATE_SUCCESS);
    		dprint(PRN_FS, "DFS, set decoding thread state to success!\n ");
    		VFMW_OSAL_SpinUnLock(G_SPINLOCK_THREAD);
    		break;
    		
    	default:
    		ret = VDEC_ERR;
	}

    return ret;
}

/************************************************************************
    VDEC控制引擎
    ChanID:  需要操作的通道号(对于通道无关操作，此参数可为任意值)
    eCmdID:  命令编码，指定需要VDEC执行何种动作
    pArgs:   命令参数，其格式与eCmdID相关
 ************************************************************************/
SINT32 VDEC_Control(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, UINT32 ArgLen)
{
    SINT32 ret=VDEC_OK;

    if (g_VfmwEnableFlag != 1 && eCmdID != VDEC_CID_GET_HAL_MEMSIZE)
    {
        dprint(PRN_FATAL, "VFMW has been destroyed, so any operation is unuseful!\n");
        return VDEC_ERR;
    }
	
    ret = VDEC_CheckParam(eCmdID, pArgs, ArgLen);
	if (ret != VDEC_OK)
    {
        dprint(PRN_FATAL, "VDEC_CheckParam failed! eCmdID = %d.\n", eCmdID);
        return ret; 
    }

	ret = VDEC_ProcessCommand(ChanID, eCmdID, pArgs);
	if (ret != VDEC_OK)
    {
        dprint(PRN_FATAL, "VDEC_ProcessCommand failed! eCmdID = %d.\n", eCmdID);
        return ret; 
    }
	
    return ret;
}


SINT32 VDEC_Suspend(VOID)
{
    VCTRL_Suspend();
    dprint(PRN_FATAL,"VDEC_Suspend OK !\n");
    return VDEC_OK;
}

SINT32 VDEC_Resume(VOID)
{
    VCTRL_Resume();
    dprint(PRN_FATAL,"VDEC_Resume OK !\n");
    return VDEC_OK;
}

