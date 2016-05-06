

#include "hal_venc.h"
#include "drv_venc_ext.h"
#include "drv_venc_efl.h"
#include "drv_venc_osal.h"
#include "drv_venc_buf_mng.h"
#include "drv_venc.h"
#include "hi_drv_venc.h"
#include "hi_drv_video.h"
#include "hi_drv_mem.h"


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

//Check null pointer
OPTM_VENC_CHN_S g_stVencChn[VENC_MAX_CHN_NUM];

struct iommu_domain* g_hisi_mmu_domain = NULL;

extern atomic_t g_VencCount;
extern struct timer_list vencTimer;
extern HI_U32 g_u32VencOpenFlag;
extern HI_VOID VENC_TimerFunc(HI_LENGTH_T value);

#define GET_INDEX_BYKERNHANDLE(s32ChIndx, hKernChn) \
    do {\
        s32ChIndx = 0; \
        while (s32ChIndx < VENC_MAX_CHN_NUM)\
        {   \
            if (g_stVencChn[s32ChIndx].hVEncHandle == hKernChn)\
            { \
                break; \
            } \
            s32ChIndx++; \
        } \
    } while (0)

#define GET_INDEX_BYUSRHANDLE(s32ChIndx, hUsrChn) \
    do {\
        s32ChIndx = 0; \
        while (s32ChIndx < VENC_MAX_CHN_NUM)\
        {   \
            if (g_stVencChn[s32ChIndx].hUsrHandle == hUsrChn)\
            { \
                break; \
            } \
            s32ChIndx++; \
        } \
    } while (0)

spinlock_t g_SendFrame_Lock[VENC_MAX_CHN_NUM];     /*lock the destroy and send frame*/

#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        u32VeChn = 0; \
        while (u32VeChn < VENC_MAX_CHN_NUM)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_PRIORITY_ID(s32VeChn, sPriorityID) \
    do {\
        sPriorityID = 0; \
        while (sPriorityID < VENC_MAX_CHN_NUM)\
        {   \
            if (PriorityTab[0][sPriorityID] == s32VeChn)\
            { \
                break; \
            } \
            sPriorityID++; \
        } \
    } while (0)

//PriorityTab[0][x]表示通道，PriorityTab[1][x]表示优先级 l00214825
HI_S8 PriorityTab[2][VENC_MAX_CHN_NUM]={{-1,-1,-1,-1,-1,-1,-1,-1},{}};
///////////////////////////////////////////////////////////////
extern VENC_EXPORT_FUNC_S s_VencExportFuncs;

//HI_U32* pResetReg;
HI_U32  pre_enc_protocol; //用于判断协议切换的标志
HI_HANDLE   h_pre_enc_handle;//用于判断通道切换的标志
HI_U32 cur_handle_num;//目前通道计数，用于判断帧间上下电
HI_U32 b_Regular_down_flag;

/* 外边复位vedu, 并设置时钟，撤销复位l00214825  */
HI_VOID VENC_DRV_BoardInit(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 ret = 0;
    HI_INFO_VENC("enter %s()\n", __func__);

//	VENC_HAL_ResetReg(); //暂时不复位  l00214825
	pre_enc_protocol = VEDU_H265;
	h_pre_enc_handle =HI_INVALID_HANDLE ;
#ifdef SHUTDOWN_REGULATOR_EN
 //  b_Regular_down_flag = HI_FALSE;
    b_Regular_down_flag = HI_TRUE;
    cur_handle_num = 0;
#else
    ret = Venc_Regulator_Enable();
    if (ret != 0)
    {
        HI_INFO_VENC("%s, enable regulator failed!\n", __func__);
        return HI_FAILURE;
    }
#endif
    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        //init_waitqueue_head(&g_astVencWait[i]);
		 spin_lock_init(&g_SendFrame_Lock[i]);
    }

    HI_INFO_VENC("exit %s ()\n", __func__);
}

HI_VOID VENC_DRV_BoardDeinit(HI_VOID)
{
    HI_INFO_VENC("enter %s ()\n", __func__);
//	iounmap(pResetReg);
#ifndef SHUTDOWN_REGULATOR_EN
    Venc_Regulator_Disable();
#endif
    HI_INFO_VENC("exit %s ()\n", __func__);
}


HI_S32 VENC_DRV_CreateChn(HI_HANDLE *phVencChn, HI_UNF_VENC_CHN_ATTR_S *pstAttr,
                      VENC_CHN_INFO_S *pstVeInfo,struct file  *pfile)
{
    HI_S32 s32Ret = 0;
    HI_S32 i      = 0;
	HI_CHAR YUVFileName[64]    = {0};
	HI_CHAR StreamFileName[64] = {0};
    VeduEfl_EncCfg_S stEncCfg;
    VeduEfl_RcAttr_S stRcAttrCfg;

    memset(&stEncCfg, 0, sizeof(stEncCfg));
    memset(&stRcAttrCfg, 0, sizeof(stRcAttrCfg));
    D_VENC_CHECK_PTR(phVencChn);
    D_VENC_CHECK_PTR(pstAttr);
	D_VENC_CHECK_PTR(pstVeInfo);

    HI_INFO_VENC("enter,phVencChn:0x%x, pstAttr->enVencType:%d\n",phVencChn,pstAttr->enVencType);

    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        if (g_stVencChn[i].hVEncHandle == HI_INVALID_HANDLE)
        {
            break;
        }
    }

    if (i == VENC_MAX_CHN_NUM)
    {
        HI_ERR_VENC("%s, Not have free handle! \n", __func__);
        return HI_ERR_VENC_CREATE_ERR;
    }

    switch (pstAttr->enVencType)
    {
        case HI_UNF_VCODEC_TYPE_HEVC:
            stEncCfg.Protocol = VEDU_H265;
            stEncCfg.Profile  = (HI_U32)pstAttr->enVencProfile;
            stEncCfg.Gop      = pstAttr->u32Gop;
            stEncCfg.QLevel   = 0;
            break;
        case HI_UNF_VCODEC_TYPE_H264:
            stEncCfg.Protocol = VEDU_H264;
            stEncCfg.Profile  = (HI_U32)pstAttr->enVencProfile;
            stEncCfg.Gop      = pstAttr->u32Gop;
            stEncCfg.QLevel   = 0;
            break;
        default:
            stEncCfg.Protocol = VEDU_H264;
            break;
    }

    stEncCfg.FrameWidth    = pstAttr->u32Width;
    stEncCfg.FrameHeight   = pstAttr->u32Height;
    stEncCfg.RotationAngle = pstAttr->u32RotationAngle;
    stEncCfg.Priority      = pstAttr->u8Priority;
    stEncCfg.streamBufSize = pstAttr->u32StrmBufSize;
    stEncCfg.QuickEncode   = pstAttr->bQuickEncode;
    stEncCfg.bSlcSplitEn   = pstAttr->bSlcSplitEn;

    s32Ret = VENC_DRV_EflCreateVenc(phVencChn, &stEncCfg, i, pstAttr);


    if (HI_SUCCESS != s32Ret)
    {
		HI_ERR_VENC("%s, channel:0x%x create  failed,i:%d\n",__func__, phVencChn, i);
        return s32Ret;
    }

    stRcAttrCfg.BitRate     = pstAttr->u32TargetBitRate;
    stRcAttrCfg.InFrmRate   = pstAttr->u32InputFrmRate;
    stRcAttrCfg.OutFrmRate  = pstAttr->u32TargetFrmRate;
    stRcAttrCfg.MaxQp       = pstAttr->u32MaxQp;
    stRcAttrCfg.MinQp       = pstAttr->u32MinQp;
	stRcAttrCfg.ImgWidth    = pstAttr->u32Width;
	stRcAttrCfg.ImgHeight   = pstAttr->u32Height;
	stRcAttrCfg.Gop         = pstAttr->u32Gop;
	stRcAttrCfg.SkipFrameEn = pstAttr->bSkipFrame;

	HI_INFO_VENC("stRcAttrCfg.InFrmRate:%d\n",stRcAttrCfg.InFrmRate);
	HI_INFO_VENC("stRcAttrCfg.Gop:%d\n",stRcAttrCfg.Gop);
	HI_INFO_VENC("stRcAttrCfg.BitRate:%d\n",stRcAttrCfg.BitRate);
	HI_INFO_VENC("stRcAttrCfg.MinQp:%d\n",stRcAttrCfg.MinQp);
	HI_INFO_VENC("stRcAttrCfg.MaxQp:%d\n",stRcAttrCfg.MaxQp);
	HI_INFO_VENC("stRcAttrCfg.SkipFrameEn:%d\n",stRcAttrCfg.SkipFrameEn);

	s32Ret = VENC_DRV_EflRcAttrInit(*phVencChn, &stRcAttrCfg);
	if (HI_SUCCESS != s32Ret)
	{
		HI_ERR_VENC("%s, set rc err:%#x.\n", __func__, s32Ret);
		s32Ret = HI_ERR_VENC_INVALID_PARA;
		goto create_error_1;
	}

    /*creat one proc file*/
    s32Ret = VENC_DRV_ProcAdd(*phVencChn,i);

    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("%s, venc_ProcAdd failed, ret = 0x%08x\n", __func__, s32Ret);
		s32Ret = HI_ERR_VENC_CREATE_ERR;
        goto create_error_1;
    }

    pstVeInfo->handle                            = *phVencChn;
	//用于信息统计
    g_stVencChn[i].hVEncHandle                   = *phVencChn;
    g_stVencChn[i].hSource                       = HI_INVALID_HANDLE;
    g_stVencChn[i].pWhichFile                    = pfile;
//	g_stVencChn[i].u32SliceSize                  = stEncCfg.SplitSize;
    g_stVencChn[i].u32FrameNumLastInput          = 0;
    g_stVencChn[i].u32FrameNumLastEncoded        = 0;
    g_stVencChn[i].u32TotalByteLastEncoded       = 0;
    g_stVencChn[i].u32LastSecInputFps            = 0;
    g_stVencChn[i].u32LastSecEncodedFps          = 0;
    g_stVencChn[i].u32LastSecKbps                = 0;
    g_stVencChn[i].u32LastSecTryNum              = 0;
    g_stVencChn[i].u32LastTryNumTotal            = 0;
	g_stVencChn[i].u32LastSecOKNum               = 0;
    g_stVencChn[i].u32LastOKNumTotal             = 0;
    g_stVencChn[i].u32LastSecPutNum              = 0;
    g_stVencChn[i].u32LastPutNumTotal            = 0;
	g_stVencChn[i].bFrameBufMng                  = HI_TRUE;
	g_stVencChn[i].bEnable                       = HI_FALSE;
	g_stVencChn[i].stProcWrite.bFrameModeRun     = HI_FALSE;
	g_stVencChn[i].stProcWrite.bTimeModeRun      = HI_FALSE;
	g_stVencChn[i].stProcWrite.bSaveYUVFileRun   = HI_FALSE;
	g_stVencChn[i].stProcWrite.u32FrameModeCount = 0;
	g_stVencChn[i].stProcWrite.fpSaveFile        = HI_NULL;

	g_stVencChn[i].stChnUserCfg                  = *pstAttr;
	g_stVencChn[i].stChnUserCfg.u32Qlevel        = 0;

    s32Ret = snprintf(YUVFileName, sizeof(YUVFileName), "venc_proc_chn%02d.yuv", i);
	if(sizeof(YUVFileName) != s32Ret)
    {
        HI_DBG_VENC("%s, Snprintf failed!\n", __func__);
    }
	memcpy((HI_VOID *)g_stVencChn[i].stProcWrite.YUVFileName,(HI_VOID *)YUVFileName,64);
    s32Ret = snprintf(StreamFileName, sizeof(StreamFileName), "venc_proc_chn%02d.h264", i);
	if (sizeof(StreamFileName) != s32Ret)
    {
        HI_DBG_VENC("%s, Snprintf failed!\n", __func__);
    }
	memcpy((HI_VOID *)g_stVencChn[i].stProcWrite.StreamFileName,(HI_VOID *)StreamFileName,64);
    HI_INFO_VENC("create OK, Chn:%d/%#x.\n", i, g_stVencChn[i].hVEncHandle);

#ifdef SHUTDOWN_REGULATOR_EN
	cur_handle_num++;
#endif

#ifdef __VENC_RC_DBG__

    g_stVencChn[i].stProcWrite.fpSaveFile = VENC_DRV_OsalFopen("/mnt/yuv_stream/venc_rc_dbg.h264",  O_RDWR | O_CREAT|O_APPEND, 0);
    if (HI_NULL == g_stVencChn[i].stProcWrite.fpSaveFile)
    {
        HI_ERR_VENC("%s, Can not create file.\n", __func__);
        g_stVencChn[i].stProcWrite.bTimeModeRun = HI_FALSE;
        return HI_FAILURE;
    }
	g_stVencChn[i].stProcWrite.bTimeModeRun = HI_TRUE;
#endif

	HI_INFO_VENC("exit %s, ,phVencChn:0x%x\n", __func__, phVencChn);
    return HI_SUCCESS;

create_error_1:
    VENC_DRV_EflDestroyVenc(*phVencChn);

    HI_INFO_VENC("exit %s, phVencChn:0x%x\n", __func__, phVencChn);
    return s32Ret;
}

HI_S32 VENC_DRV_DestroyChn( HI_HANDLE hVencChn)
{
    HI_S32 s32Ret   = 0;
    HI_U32 u32VeChn = 0;
    OPTM_VENC_CHN_S *pstVenc = NULL;
    VEDU_LOCK_FLAG flags = 0;

    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);
	HI_INFO_VENC("enter,hVencChn:0x%x \n",hVencChn);

    spin_lock_irqsave(&g_SendFrame_Lock[u32VeChn],flags);
    pstVenc = &g_stVencChn[u32VeChn];
    spin_unlock_irqrestore(&g_SendFrame_Lock[u32VeChn],flags);

    //VENC must be stop working
    if (pstVenc->bEnable)
    {
        HI_WARN_VENC("Destroy channel when VENC is run.\n");
        VENC_DRV_EflStopVenc(hVencChn);
    }

#ifdef __VENC_RC_DBG__
    g_stVencChn[u32VeChn].stProcWrite.bTimeModeRun = HI_FALSE;
    VENC_DRV_OsalFclose(g_stVencChn[u32VeChn].stProcWrite.fpSaveFile);

#endif

    VENC_DRV_ProcDel(hVencChn,u32VeChn);
    s32Ret = VENC_DRV_EflDestroyVenc(hVencChn);

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("%s, destroy channel failed,hVencChn:0x%x\n", __func__, hVencChn);
        return s32Ret;
    }

    spin_lock_irqsave(&g_SendFrame_Lock[u32VeChn],flags);
	g_stVencChn[u32VeChn].hSource      = HI_INVALID_HANDLE;
    g_stVencChn[u32VeChn].hVEncHandle  = HI_INVALID_HANDLE;
	g_stVencChn[u32VeChn].bFrameBufMng = HI_TRUE;
	g_stVencChn[u32VeChn].bEnable      = HI_FALSE;
#ifdef SHUTDOWN_REGULATOR_EN
	cur_handle_num--;
#endif
	spin_unlock_irqrestore(&g_SendFrame_Lock[u32VeChn],flags);

	HI_INFO_VENC("exit %s, hVencChn:0x%x\n", __func__, hVencChn);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_StartReceivePic(HI_HANDLE EncHandle)
{
    HI_S32 s32Ret   = HI_FAILURE;
    HI_U32 u32VeChn = 0;
    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);

	HI_INFO_VENC("enter %s,EncHandle:0x%x\n", __func__, EncHandle);

    if (HI_TRUE == g_stVencChn[u32VeChn].bEnable)
    {
        return HI_SUCCESS;
    }

    s32Ret = VENC_DRV_EflStartVenc(EncHandle);
    if (HI_SUCCESS == s32Ret)
    {
        g_stVencChn[u32VeChn].bEnable = HI_TRUE;
        do_gettimeofday(&(g_stVencChn[u32VeChn].stTimeStart));
        HI_INFO_VENC("%s, start Chn %d/%#x. OK\n", __func__, u32VeChn, EncHandle);
        VENC_DRV_EflRequestIframe(EncHandle);
    }
    else
    {
        s32Ret = HI_ERR_VENC_INVALID_CHNID;
    }

	HI_INFO_VENC("exit %s, EncHandle:0x%x\n", __func__, EncHandle);
    return s32Ret;
}

HI_S32 VENC_DRV_StopReceivePic(HI_HANDLE EncHandle)
{
    HI_S32 s32Ret   = HI_FAILURE;
    HI_U32 u32VeChn = 0;
	HI_INFO_VENC("enter %s, EncHandle:0x%x\n", __func__, EncHandle);

    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);

    if (HI_FALSE == g_stVencChn[u32VeChn].bEnable)
    {
        return HI_SUCCESS;
    }

    s32Ret = VENC_DRV_EflStopVenc(EncHandle);
    if (HI_SUCCESS == s32Ret)
    {
        g_stVencChn[u32VeChn].bEnable = HI_FALSE;
        HI_INFO_VENC("%s, stop Chn %d/%#x. OK\n", __func__, u32VeChn, EncHandle);
    }

    HI_INFO_VENC("exit %s, EncHandle:0x%x\n", __func__, EncHandle);
    return s32Ret;
}

HI_S32 VENC_DRV_SetAttr(HI_HANDLE EncHandle, HI_UNF_VENC_CHN_ATTR_S *pstAttr,VENC_CHN_INFO_S *pstVeInfo)
{
    HI_S32 s32Ret            = -1;
    HI_U32 u32VeChn          = 0;
    HI_BOOL bErrCfg          = HI_FALSE;

    OPTM_VENC_CHN_S *pstVenc         = NULL;
    VeduEfl_EncPara_S* pstEncChnPara = (VeduEfl_EncPara_S*)EncHandle;
    VeduEfl_RcAttr_S stRcAttrCfg;

    memset(&stRcAttrCfg, 0, sizeof(stRcAttrCfg));

	HI_INFO_VENC("enter %s, ,EncHandle:0x%x\n", __func__, EncHandle);

    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);
	D_VENC_CHECK_PTR(pstAttr);
    pstVenc = &g_stVencChn[u32VeChn];

    /* check the new attr whether legal */
	if((pstVenc->stChnUserCfg.bSlcSplitEn != pstAttr->bSlcSplitEn)
	|| (pstVenc->stChnUserCfg.u32RotationAngle!= pstAttr->u32RotationAngle)
	||(pstVenc->stChnUserCfg.u32StrmBufSize!= pstAttr->u32StrmBufSize))
	{
		bErrCfg = HI_TRUE;
	}
	if (pstVenc->bEnable)
	{
	    if(pstVenc->stChnUserCfg.enVencType != pstAttr->enVencType)
		{
			bErrCfg = HI_TRUE;
		}
		if (( pstVenc->stChnUserCfg.enVencType == HI_UNF_VCODEC_TYPE_H264 )&&(pstVenc->stChnUserCfg.enVencProfile!= pstAttr->enVencProfile))
		{
			bErrCfg = HI_TRUE;
		}
	}
    if (HI_TRUE == bErrCfg)
    {
        if (pstVenc->stChnUserCfg.bSlcSplitEn != pstAttr->bSlcSplitEn)
        {
            HI_ERR_VENC("VENC not support this active change bSlcSplitEn:(%d -> %d)!\n",
				pstVenc->stChnUserCfg.bSlcSplitEn,pstAttr->bSlcSplitEn);
        }

	    if (pstVenc->stChnUserCfg.u32RotationAngle!= pstAttr->u32RotationAngle)
	    {
	        HI_ERR_VENC("VENC not support this active change u32RotationAngle:(%d -> %d)!\n",
				pstVenc->stChnUserCfg.u32RotationAngle,pstAttr->u32RotationAngle);
	    }

		if (pstVenc->stChnUserCfg.u32StrmBufSize!= pstAttr->u32StrmBufSize)
		{
		     HI_ERR_VENC("VENC not support this active change u32StrmBufSize:(%d -> %d)!\n",
				pstVenc->stChnUserCfg.u32StrmBufSize,pstAttr->u32StrmBufSize);
		}

		if (pstVenc->bEnable)
		{
		    if (pstVenc->stChnUserCfg.enVencType != pstAttr->enVencType)
		    {
		        HI_ERR_VENC("VENC not support this active change enVencType:(%d -> %d)!\n",
				pstVenc->stChnUserCfg.enVencType,pstAttr->enVencType);
		    }

			if ((pstVenc->stChnUserCfg.enVencProfile!= pstAttr->enVencProfile)
				&& (pstVenc->stChnUserCfg.enVencType == HI_UNF_VCODEC_TYPE_H264))
			{
			    HI_ERR_VENC("VENC not support this active change enVencProfile:(%d -> %d)! enVencType(%d,%d)\n",
				pstVenc->stChnUserCfg.enVencProfile,pstAttr->enVencProfile,pstVenc->stChnUserCfg.enVencType,HI_UNF_VCODEC_TYPE_H264);
			}
		}
        return HI_ERR_VENC_NOT_SUPPORT;
    }

    if (HI_UNF_VCODEC_TYPE_HEVC != pstAttr->enVencType && HI_UNF_VCODEC_TYPE_H264 != pstAttr->enVencType)
    {
        HI_ERR_VENC("VENC not support creat this VencType:%d\n",pstAttr->enVencType);
        return HI_ERR_VENC_NOT_SUPPORT;
    }

    /* this case to change the resolution */
    if ((pstVenc->stChnUserCfg.u32Height  != pstAttr->u32Height)                //should be change
        || (pstVenc->stChnUserCfg.u32Width!= pstAttr->u32Width))
    {
        //add by ljh 宽高改变，码控需初始化 huangliang
		HI_INFO_VENC("stRcAttrCfg.InFrmRate:%d\n",stRcAttrCfg.InFrmRate);
		HI_INFO_VENC("stRcAttrCfg.Gop:%d\n",stRcAttrCfg.Gop);
		HI_INFO_VENC("stRcAttrCfg.BitRate:%d\n",stRcAttrCfg.BitRate);
		HI_INFO_VENC("stRcAttrCfg.MinQp:%d\n",stRcAttrCfg.MinQp);
		HI_INFO_VENC("stRcAttrCfg.MaxQp:%d\n",stRcAttrCfg.MaxQp);

	    s32Ret = VENC_DRV_EflRcAttrInit(pstVenc->hVEncHandle, &stRcAttrCfg);
	    if (HI_SUCCESS != s32Ret)
	    {
	        HI_ERR_VENC("%s, config venc err:%#x.\n", __func__, s32Ret);
        	return HI_ERR_VENC_INVALID_PARA;
	    }
	}

     /* this case to change the protocol of Encoder */
	if (pstVenc->stChnUserCfg.enVencType != pstAttr->enVencType)
	{
	    D_VENC_CHECK_PTR(pstVeInfo);
	    if (pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264)   /*h265 --> h264*/
	    {
			pstEncChnPara->vcpi_protocol = VEDU_H264;
	    }
		else                                                  /*h264 --> h265*/
		{
            pstEncChnPara->vcpi_protocol = VEDU_H265;
		}
		pstEncChnPara->RcStart = 1;
	}

	if (HI_UNF_H264_PROFILE_BASELINE == pstAttr->enVencProfile)
	{
		pstEncChnPara->pstCfg_EncPara->vcpi_trans_mode = 1; // 4*4
		pstEncChnPara->pstCfg_EncPara->vcpi_intra_cu_en = 0x5;
	}
	else if(HI_UNF_H264_PROFILE_MAIN == pstAttr->enVencProfile)
	{
		pstEncChnPara->pstCfg_EncPara->vcpi_trans_mode = 1;// 4*4
		pstEncChnPara->pstCfg_EncPara->vcpi_intra_cu_en = 0x5;
	}
	else if(HI_UNF_H264_PROFILE_HIGH == pstAttr->enVencProfile)
	{
		pstEncChnPara->pstCfg_EncPara->vcpi_trans_mode = 0;// 4*4 &8*8
		pstEncChnPara->pstCfg_EncPara->vcpi_intra_cu_en = 0xf;
	}

    /* this case to change the profile of H264 Encoder  */
    if ((pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264) && (pstVenc->stChnUserCfg.enVencProfile!= pstAttr->enVencProfile))
	{
		pstEncChnPara->H264Profile    = (HI_U32)pstAttr->enVencProfile;
		pstEncChnPara->pstCfg_EncPara->vcpi_entropy_mode = (pstEncChnPara->H264Profile == VEDU_H264_BASELINE_PROFILE)? 1 : 0;
		if(pstAttr->u32Width*pstAttr->u32Height > 1920*1080)
		{
			pstEncChnPara->pstCfg_EncPara->vcpi_entropy_mode = 1;//分辨率大，不使用cabac
		}

        /* make sps & pps & VOL stream */
		VENC_DRV_EflFlushStrmHeader(pstEncChnPara);
		pstEncChnPara->RcStart = 1;
    }

	/* this case to change the RC & FrmRate Control parameter */
	//if (pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264)
	{
	    if( (pstVenc->stChnUserCfg.u32TargetBitRate != pstAttr->u32TargetBitRate)
	    || (pstVenc->stChnUserCfg.u32InputFrmRate  != pstAttr->u32InputFrmRate)
	    || (pstVenc->stChnUserCfg.u32TargetFrmRate != pstAttr->u32TargetFrmRate)
	    || (pstVenc->stChnUserCfg.u32Gop           != pstAttr->u32Gop)
		|| (pstVenc->stChnUserCfg.u32MaxQp         != pstAttr->u32MaxQp)
		|| (pstVenc->stChnUserCfg.u32MinQp         != pstAttr->u32MinQp)
		|| (pstVenc->stChnUserCfg.bSkipFrame       != pstAttr->bSkipFrame))
	    {
	        stRcAttrCfg.BitRate     = pstAttr->u32TargetBitRate;
	        stRcAttrCfg.InFrmRate   = pstAttr->u32InputFrmRate;
	        stRcAttrCfg.OutFrmRate  = pstAttr->u32TargetFrmRate;
			stRcAttrCfg.Gop         = pstAttr->u32Gop;
			stRcAttrCfg.MaxQp 	    = pstAttr->u32MaxQp;
			stRcAttrCfg.MinQp 	    = pstAttr->u32MinQp;
			stRcAttrCfg.ImgWidth    = pstAttr->u32Width;
			stRcAttrCfg.ImgHeight   = pstAttr->u32Height;
			stRcAttrCfg.SkipFrameEn = pstAttr->bSkipFrame;

	        s32Ret = VENC_DRV_EflRcSetAttr(pstVenc->hVEncHandle, &stRcAttrCfg);
	        if (HI_SUCCESS != s32Ret)
	        {
	            HI_ERR_VENC("%s, config venc Rate Control Attribute err:%#x.\n", __func__, s32Ret);
	            return HI_FAILURE;
	        }
	    }
	}

    /* this case to change the Priority */
    if (pstVenc->stChnUserCfg.u8Priority != pstAttr->u8Priority)
    {
        HI_U32 PriorityID;
        D_VENC_GET_PRIORITY_ID(u32VeChn, PriorityID);
		D_VENC_CHECK_CHN(PriorityID);
        PriorityTab[1][PriorityID] = pstAttr->u8Priority;
        VENC_DRV_EflSortPriority();
    }

    if ((1 != pstAttr->ui32nSlices) && (pstAttr->bSlcSplitEn))
    {
		pstEncChnPara->pstCfg_EncPara->vcpi_multislc_en  = 1;
		pstEncChnPara->pstCfg_EncPara->vcpi_slcspilt_mod = 1;//按照寄存器表描述，当前必须为1，按Lcu行划分
		if(pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264)//MB 16*16
		{
			pstEncChnPara->pstCfg_EncPara->vcpi_slice_size = ((pstAttr->u32Height+15)>>4)/pstAttr->ui32nSlices;
			if(((pstAttr->u32Height+15)>>4)%pstAttr->ui32nSlices)//不能整除要多分一个slice
			{
				pstAttr->ui32nSlices++;
			}
		}
		else//LCU 64*64
		{
			pstEncChnPara->pstCfg_EncPara->vcpi_slice_size = ((pstAttr->u32Height+63)>>6)/pstAttr->ui32nSlices;
			if(((pstAttr->u32Height+63)>>6)%pstAttr->ui32nSlices)
			{
				pstAttr->ui32nSlices++;
			}
		}
	}
	else
	{
		pstEncChnPara->pstCfg_EncPara->vcpi_multislc_en = 0;
	}

	pstEncChnPara->pstCfg_EncPara->vcpi_crop_en = pstAttr->bEnableCrop;
	if(pstEncChnPara->pstCfg_EncPara->vcpi_crop_en)
	{
		pstEncChnPara->pstCfg_EncPara->vcpi_crop_ystart = pstAttr->CropInfo.u32CropTop;
		pstEncChnPara->pstCfg_EncPara->vcpi_crop_yend   = pstAttr->CropInfo.u32CropBottom;
		pstEncChnPara->pstCfg_EncPara->vcpi_crop_xstart = pstAttr->CropInfo.u32CropLeft;
		pstEncChnPara->pstCfg_EncPara->vcpi_crop_xend   = pstAttr->CropInfo.u32CropRight;
	}

	if(pstEncChnPara->pstCfg_EncPara->vcpi_scale_en)
	{
		pstEncChnPara->pstCfg_EncPara->vcpi_yscale = pstAttr->ScaleInfo.s32Height<<13;//配到寄存器要左移13位
		pstEncChnPara->pstCfg_EncPara->vcpi_xscale = pstAttr->ScaleInfo.s32Width<<13;
	}

	pstEncChnPara->pstCfg_EncPara->vcpi_roi_en = pstAttr->bEnableROI;
	if (pstEncChnPara->pstCfg_EncPara->vcpi_roi_en)
	{

		pstEncChnPara->pstCfg_EncPara->region0keep      = pstAttr->ROIInfo.bRegion0keep;
		pstEncChnPara->pstCfg_EncPara->absqp0           = pstAttr->ROIInfo.absqp0;
		pstEncChnPara->pstCfg_EncPara->region0en        = pstAttr->ROIInfo.bRegion0en;
		pstEncChnPara->pstCfg_EncPara->roiqp0           = pstAttr->ROIInfo.roiqp0;
		pstEncChnPara->pstCfg_EncPara->start0_roistartx = pstAttr->ROIInfo.start0_roistartx;
		pstEncChnPara->pstCfg_EncPara->start0_roistarty = pstAttr->ROIInfo.start0_roistarty;
		pstEncChnPara->pstCfg_EncPara->size0_roiwidth   = pstAttr->ROIInfo.size0_roiwidth;
		pstEncChnPara->pstCfg_EncPara->size0_roiheight  = pstAttr->ROIInfo.size0_roiheight;


		pstEncChnPara->pstCfg_EncPara->region1keep      = pstAttr->ROIInfo.bRegion1keep;
		pstEncChnPara->pstCfg_EncPara->absqp1           = pstAttr->ROIInfo.absqp1;
		pstEncChnPara->pstCfg_EncPara->region1en        = pstAttr->ROIInfo.bRegion1en;
		pstEncChnPara->pstCfg_EncPara->roiqp1           = pstAttr->ROIInfo.roiqp1;
		pstEncChnPara->pstCfg_EncPara->start1_roistartx = pstAttr->ROIInfo.start1_roistartx;
		pstEncChnPara->pstCfg_EncPara->start1_roistarty = pstAttr->ROIInfo.start1_roistarty;
		pstEncChnPara->pstCfg_EncPara->size1_roiwidth   = pstAttr->ROIInfo.size1_roiwidth;
		pstEncChnPara->pstCfg_EncPara->size1_roiheight  = pstAttr->ROIInfo.size1_roiheight;
		pstEncChnPara->pstCfg_EncPara->region2keep      = pstAttr->ROIInfo.bRegion2keep;
		pstEncChnPara->pstCfg_EncPara->absqp2           = pstAttr->ROIInfo.absqp2;
		pstEncChnPara->pstCfg_EncPara->region2en        = pstAttr->ROIInfo.bRegion2en;
		pstEncChnPara->pstCfg_EncPara->roiqp2           = pstAttr->ROIInfo.roiqp2;
		pstEncChnPara->pstCfg_EncPara->start2_roistartx = pstAttr->ROIInfo.start2_roistartx;
		pstEncChnPara->pstCfg_EncPara->start2_roistarty = pstAttr->ROIInfo.start2_roistarty;
		pstEncChnPara->pstCfg_EncPara->size2_roiwidth   = pstAttr->ROIInfo.size2_roiwidth;
		pstEncChnPara->pstCfg_EncPara->size2_roiheight  = pstAttr->ROIInfo.size2_roiheight;


		pstEncChnPara->pstCfg_EncPara->region3keep      = pstAttr->ROIInfo.bRegion3keep;
		pstEncChnPara->pstCfg_EncPara->absqp3           = pstAttr->ROIInfo.absqp3;
		pstEncChnPara->pstCfg_EncPara->region3en        = pstAttr->ROIInfo.bRegion3en;
		pstEncChnPara->pstCfg_EncPara->roiqp3           = pstAttr->ROIInfo.roiqp3;
		pstEncChnPara->pstCfg_EncPara->start3_roistartx = pstAttr->ROIInfo.start3_roistartx;
		pstEncChnPara->pstCfg_EncPara->start3_roistarty = pstAttr->ROIInfo.start3_roistarty;
		pstEncChnPara->pstCfg_EncPara->size3_roiwidth   = pstAttr->ROIInfo.size3_roiwidth;
		pstEncChnPara->pstCfg_EncPara->size3_roiheight  = pstAttr->ROIInfo.size3_roiheight;


		pstEncChnPara->pstCfg_EncPara->region4keep      = pstAttr->ROIInfo.bRegion4keep;
		pstEncChnPara->pstCfg_EncPara->absqp4           = pstAttr->ROIInfo.absqp4;
		pstEncChnPara->pstCfg_EncPara->region4en        = pstAttr->ROIInfo.bRegion4en;
		pstEncChnPara->pstCfg_EncPara->roiqp4           = pstAttr->ROIInfo.roiqp4;
		pstEncChnPara->pstCfg_EncPara->start4_roistartx = pstAttr->ROIInfo.start4_roistartx;
		pstEncChnPara->pstCfg_EncPara->start4_roistarty = pstAttr->ROIInfo.start4_roistarty;
		pstEncChnPara->pstCfg_EncPara->size4_roiwidth   = pstAttr->ROIInfo.size4_roiwidth;
		pstEncChnPara->pstCfg_EncPara->size4_roiheight  = pstAttr->ROIInfo.size4_roiheight;


		pstEncChnPara->pstCfg_EncPara->region5keep      = pstAttr->ROIInfo.bRegion5keep;
		pstEncChnPara->pstCfg_EncPara->absqp5           = pstAttr->ROIInfo.absqp5;
		pstEncChnPara->pstCfg_EncPara->region5en        = pstAttr->ROIInfo.bRegion5en;
		pstEncChnPara->pstCfg_EncPara->roiqp5           = pstAttr->ROIInfo.roiqp5;
		pstEncChnPara->pstCfg_EncPara->start5_roistartx = pstAttr->ROIInfo.start5_roistartx;
		pstEncChnPara->pstCfg_EncPara->start5_roistarty = pstAttr->ROIInfo.start5_roistarty;
		pstEncChnPara->pstCfg_EncPara->size5_roiwidth   = pstAttr->ROIInfo.size5_roiwidth;
		pstEncChnPara->pstCfg_EncPara->size5_roiheight  = pstAttr->ROIInfo.size5_roiheight;


		pstEncChnPara->pstCfg_EncPara->region6keep      = pstAttr->ROIInfo.bRegion6keep;
		pstEncChnPara->pstCfg_EncPara->absqp6           = pstAttr->ROIInfo.absqp6;
		pstEncChnPara->pstCfg_EncPara->region6en        = pstAttr->ROIInfo.bRegion6en;
		pstEncChnPara->pstCfg_EncPara->roiqp6           = pstAttr->ROIInfo.roiqp6;
		pstEncChnPara->pstCfg_EncPara->start6_roistartx = pstAttr->ROIInfo.start6_roistartx;
		pstEncChnPara->pstCfg_EncPara->start6_roistarty = pstAttr->ROIInfo.start6_roistarty;
		pstEncChnPara->pstCfg_EncPara->size6_roiwidth   = pstAttr->ROIInfo.size6_roiwidth;
		pstEncChnPara->pstCfg_EncPara->size6_roiheight  = pstAttr->ROIInfo.size6_roiheight;


		pstEncChnPara->pstCfg_EncPara->region7keep      = pstAttr->ROIInfo.bRegion7keep;
		pstEncChnPara->pstCfg_EncPara->absqp7           = pstAttr->ROIInfo.absqp7;
		pstEncChnPara->pstCfg_EncPara->region7en        = pstAttr->ROIInfo.bRegion7en;
		pstEncChnPara->pstCfg_EncPara->roiqp7           = pstAttr->ROIInfo.roiqp7;
		pstEncChnPara->pstCfg_EncPara->start7_roistartx = pstAttr->ROIInfo.start7_roistartx;
		pstEncChnPara->pstCfg_EncPara->start7_roistarty = pstAttr->ROIInfo.start7_roistarty;
		pstEncChnPara->pstCfg_EncPara->size7_roiwidth   = pstAttr->ROIInfo.size7_roiwidth;
		pstEncChnPara->pstCfg_EncPara->size7_roiheight  = pstAttr->ROIInfo.size7_roiheight;
	}

    /* update the new user attr */
    pstVenc->stChnUserCfg.u32Gop           = pstAttr->u32Gop;
    pstVenc->stChnUserCfg.u8Priority       = pstAttr->u8Priority;
    pstVenc->stChnUserCfg.u32TargetBitRate = pstAttr->u32TargetBitRate;
    pstVenc->stChnUserCfg.u32InputFrmRate  = pstAttr->u32InputFrmRate;
    pstVenc->stChnUserCfg.u32TargetFrmRate = pstAttr->u32TargetFrmRate;
    pstVenc->stChnUserCfg.u32MaxQp         = pstAttr->u32MaxQp;
    pstVenc->stChnUserCfg.u32MinQp         = pstAttr->u32MinQp;
    pstVenc->stChnUserCfg.bQuickEncode     = pstAttr->bQuickEncode;
    pstVenc->stChnUserCfg.enVencProfile    = pstAttr->enVencProfile;
    pstVenc->stChnUserCfg.enVencType       = pstAttr->enVencType;
	pstVenc->stChnUserCfg.u32RotationAngle = pstAttr->u32RotationAngle;
	pstVenc->stChnUserCfg.u32Height        = pstAttr->u32Height;
    pstVenc->stChnUserCfg.u32Width         = pstAttr->u32Width;

	HI_INFO_VENC("enVencHevcProfile:%d\n",pstAttr->enVencHevcProfile);
	HI_INFO_VENC("h264Level:%d\n",pstAttr->h264Level);
	HI_INFO_VENC("h265Level:%d\n",pstAttr->h265Level);
	HI_INFO_VENC("CropInfo.u32CropHeig:%d\n",pstAttr->CropInfo.u32CropHeight);
	HI_INFO_VENC("CropInfo.u32CropWidth:%d\n",pstAttr->CropInfo.u32CropWidth);
	HI_INFO_VENC("CropInfo.u32CropLeft:%d\n",pstAttr->CropInfo.u32CropLeft);
	HI_INFO_VENC("CropInfo.u32CropTop:%d\n",pstAttr->CropInfo.u32CropTop);
	HI_INFO_VENC("ScaleInfo.s32Height:%d\n",pstAttr->ScaleInfo.s32Height);
	HI_INFO_VENC("ScaleInfo.s32Widt:%d\n",pstAttr->ScaleInfo.s32Width);
	HI_INFO_VENC("ui32nSlices:%d\n",pstAttr->ui32nSlices);
	HI_INFO_VENC("bLowPowerMode:%d\n",pstAttr->bLowPowerMode);
	HI_INFO_VENC("bInputLowDelayMode:%d\n",pstAttr->bInputLowDelayMode);
	HI_INFO_VENC("bOutputLowDelayMode:%d\n",pstAttr->bOutputLowDelayMode);
	HI_INFO_VENC("bEnableROI:%d\n",pstAttr->bEnableROI);

	pstVenc->stChnUserCfg.enVencHevcProfile = pstAttr->enVencHevcProfile;

	pstVenc->stChnUserCfg.h264Level = pstAttr->h264Level;
	pstVenc->stChnUserCfg.h265Level = pstAttr->h265Level;

	pstVenc->stChnUserCfg.CropInfo.u32CropHeight = pstAttr->CropInfo.u32CropHeight;
	pstVenc->stChnUserCfg.CropInfo.u32CropWidth  = pstAttr->CropInfo.u32CropWidth;
	pstVenc->stChnUserCfg.CropInfo.u32CropLeft   = pstAttr->CropInfo.u32CropLeft;
	pstVenc->stChnUserCfg.CropInfo.u32CropTop    = pstAttr->CropInfo.u32CropTop;

	pstVenc->stChnUserCfg.ScaleInfo.s32Height    = pstAttr->ScaleInfo.s32Height;
	pstVenc->stChnUserCfg.ScaleInfo.s32Width     = pstAttr->ScaleInfo.s32Width;

	pstVenc->stChnUserCfg.ui32nSlices         = pstAttr->ui32nSlices;
	pstVenc->stChnUserCfg.bLowPowerMode       = pstAttr->bLowPowerMode;
	pstVenc->stChnUserCfg.bInputLowDelayMode  = pstAttr->bInputLowDelayMode;
	pstVenc->stChnUserCfg.bOutputLowDelayMode = pstAttr->bOutputLowDelayMode;
	pstVenc->stChnUserCfg.bEnableROI          = pstAttr->bEnableROI;
	pstVenc->stChnUserCfg.bEnableCrop         = pstAttr->bEnableCrop;
	memcpy(&(pstVenc->stChnUserCfg.ROIInfo),&(pstAttr->ROIInfo),sizeof(HI_UNF_VCODEC_ROI_INFO_S));
	pstVenc->stChnUserCfg.uiYUVStoreMode      = pstAttr->uiYUVStoreMode;
	pstVenc->stChnUserCfg.bMMUByPass	      = pstAttr->bMMUByPass;
	pstVenc->stChnUserCfg.WideToNarrowEn	  = pstAttr->WideToNarrowEn;

	pstEncChnPara->bMMUByPass             = pstAttr->bMMUByPass;
	pstEncChnPara->pstCfg_EncPara->vcpi_wide_narrow_en = pstAttr->WideToNarrowEn;
    pstEncChnPara->pstCfg_EncPara->min_qp = pstAttr->u32MinQp;
	pstEncChnPara->pstCfg_EncPara->max_qp = pstAttr->u32MaxQp;
    pstEncChnPara->QuickEncode            = pstAttr->bQuickEncode;

	if (pstAttr->enVencType == HI_UNF_VCODEC_TYPE_HEVC)
	{
		if ((pstAttr->u32InputFrmRate >= 240 &&pstVenc->stChnUserCfg.u32Width*pstVenc->stChnUserCfg.u32Height >= 1280*720)
			|| (pstAttr->u32InputFrmRate >= 360 && pstVenc->stChnUserCfg.u32Width*pstVenc->stChnUserCfg.u32Height >= 800*480)
			|| (pstAttr->u32InputFrmRate >= 120 && pstVenc->stChnUserCfg.u32Width*pstVenc->stChnUserCfg.u32Height >= 1920*1080))
		{
			HI_INFO_VENC("%s, High FrameRate Mode!\n", __func__);
			pstEncChnPara->pstCfg_EncPara->vcpi_intra_cu_en = pstEncChnPara->pstCfg_EncPara->vcpi_intra_cu_en & 0xe;
			pstEncChnPara->pstCfg_EncPara->vcpi_img_improve_en = 0;
			check_enc_para(pstEncChnPara->pstCfg_EncPara, HI_TRUE);

		}
	}

	HI_INFO_VENC("exit %s, EncHandle:0x%x\n", __func__, EncHandle);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_GetAttr(HI_HANDLE EncHandle, HI_UNF_VENC_CHN_ATTR_S *pstAttr)
{
    HI_U32 u32VeChn          = 0;
    OPTM_VENC_CHN_S *pstVenc = NULL;

	HI_INFO_VENC("enter %s, EncHandle:0x%x\n", __func__, EncHandle);
    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);
	D_VENC_CHECK_PTR(pstAttr);
    pstVenc = &g_stVencChn[u32VeChn];

    *pstAttr = pstVenc->stChnUserCfg;
	HI_INFO_VENC("exit %s, EncHandle:0x%x\n", __func__, EncHandle);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_RequestIFrame(HI_HANDLE EncHandle)
{
    HI_S32 s32Ret   = -1;
    HI_U32 u32VeChn = 0;
    OPTM_VENC_CHN_S *pstVenc = NULL;

	HI_INFO_VENC("enter %s, EncHandle:0x%x\n", __func__, EncHandle);
    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);
    pstVenc = &g_stVencChn[u32VeChn];

    s32Ret = VENC_DRV_EflRequestIframe(pstVenc->hVEncHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("%s, request IFrame err:%#x.\n", __func__, s32Ret);
        return HI_FAILURE;
    }

	HI_INFO_VENC("exit %s, EncHandle:0x%x\n", __func__, EncHandle);
    return HI_SUCCESS;
}
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

