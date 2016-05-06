/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r3+wdNBVAaWSiemyLf8l47mSbvsHIny7YPxN17cSVi5cBtC4TaJu2EsMB5CsZ8x/mxAHh
7y7DbUs6C91ZJZRdEHbBQTNJfyLx0iCj7UCH6At3hVND8qFdRMBNJxkvmM21/A==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
   
#include "fsp.h"
#include "mem_manage.h"
#include "syntax.h"
#include "vfmw_ctrl.h"

FSP_INST_S* s_pFspInst[MAX_CHAN_NUM];

extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];
extern UINT32 g_u32DFSMaxAllocTime;


/***********************************************************************
   OMX 帧存回调接口
 ***********************************************************************/
static FSP_OMX_INTF_S g_FspOMXIntf;


/***********************************************************************
    OMX bypass模式时，设置帧存回调接口
 ***********************************************************************/
SINT32 FSP_SetOMXInterface(FSP_OMX_INTF_S *pIntf)
{
	if (NULL == pIntf->pfnBufferHandler)
	{
		dprint(PRN_FATAL, "%s FrameIntf invalid\n", __func__);
		return FSP_ERR;
	}

	memcpy(&g_FspOMXIntf, pIntf, sizeof(FSP_OMX_INTF_S));

	return FSP_OK;
}
   
/***********************************************************************
    查询是否是OMX bypass mode
 ***********************************************************************/
inline SINT32 FSP_IsOmxBypassMode(SINT32 InstID)
{         
    if(1 == s_pFspInst[InstID]->IsOmxPath
    && 1 == s_pstVfmwChan[InstID]->stSynExtraData.stChanOption.u32OmxBypassMode)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/***********************************************************************
    OMX bypass模式时，外部帧存回调
 ***********************************************************************/
inline SINT32 FSP_ExtBufHandler(SINT32 InstID, VDEC_BC_TYPE_E type, VOID *pParam)
{     
	if (NULL == g_FspOMXIntf.pfnBufferHandler)
	{
		dprint(PRN_FATAL, "%s: BufferHandler func null\n");
		return 0;
	}

	return g_FspOMXIntf.pfnBufferHandler(InstID, type, pParam);
}


/***********************************************************************
    全局初始化
 ***********************************************************************/
VOID FSP_Init(VOID)
{ 
    memset(s_pFspInst, 0, MAX_CHAN_NUM*sizeof(FSP_INST_S *));
    
    return;
}

/***********************************************************************
    全局退出
 ***********************************************************************/
VOID  FSP_Exit(VOID)
{
    SINT32 i;
        
    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (NULL != s_pFspInst[i] && FSP_INST_STATE_NULL != s_pFspInst[i]->eFspInstState)
        {
            FSP_DisableInstance(i);
        }
    }
       
    return;
}

/***********************************************************************
	配置通道时对于帧存实例的全局配置
 ***********************************************************************/
SINT32 FSP_ConfigAttribute(SINT32 InstID, FSP_ATTR_S *pstAttr)  
{
    FSP_INST_S *pstInst;

    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(s_pFspInst[InstID]->eFspInstState == FSP_INST_STATE_INUSE, "fsp instance not in used");

    pstInst = s_pFspInst[InstID];

    /* 设置低缓存模式，即划分帧存个数时按实际需要划分而不是最大值 */
    pstInst->IsOmxPath = pstAttr->IsOmxPath;

    return FSP_OK;
}

/***********************************************************************
	实例信息部分清除，以分界线开始往下都会被清零
 ***********************************************************************/
SINT32 FSP_ClearContext(FSP_INST_S *pFspInst)  // ONE TEST
{
	SINT8             s8TmpInstID;
    SINT8             s8TmpIsOmxPath;
	FSP_INST_STATE_E  eTmpFspInstState;
	FSP_PRE_INF_S     stTmpPreInfo;
	
    FSP_ASSERT_RET(pFspInst != NULL, "pFspInst = NULL");

    s8TmpInstID = pFspInst->s32InstID;
    s8TmpIsOmxPath  = pFspInst->IsOmxPath;
	eTmpFspInstState = pFspInst->eFspInstState;
    memcpy(&stTmpPreInfo, &(pFspInst->stPreInfo), sizeof(FSP_PRE_INF_S));
	
    memset(pFspInst, 0, sizeof(FSP_INST_S));
	
	pFspInst->s32InstID = s8TmpInstID;
    pFspInst->IsOmxPath =  s8TmpIsOmxPath;
	pFspInst->eFspInstState =  eTmpFspInstState;
    memcpy(&(pFspInst->stPreInfo), &stTmpPreInfo, sizeof(FSP_PRE_INF_S));

    return FSP_OK;
}

/***********************************************************************
    使能实例(树状帧存实例使能函数不用这个)
    成功返回实例FSP_OK，失败返回FSP_ERR
 ***********************************************************************/
SINT32  FSP_EnableInstance(SINT32  InstID)
{    
    FSP_INST_S *pstInst;
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");

    pstInst = s_pFspInst[InstID];
    if (FSP_INST_STATE_NULL == pstInst->eFspInstState)
    {
        memset( pstInst, 0, sizeof(FSP_INST_S) );
	    pstInst->eFspInstState = FSP_INST_STATE_INUSE;
        pstInst->eFspPartitionState = FSP_PARTITION_STATE_FIRST;
	    return FSP_OK;
    }
    
    return FSP_ERR;
}

/***********************************************************************
    销毁实例
 ***********************************************************************/
VOID  FSP_DisableInstance(SINT32 InstID)
{    
    FSP_INST_S *pstInst;
    FSP_ASSERT(InstID >= 0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");

    pstInst = s_pFspInst[InstID];
    if (FSP_INST_STATE_INUSE == pstInst->eFspInstState)
    {
        pstInst->eFspInstState = FSP_INST_STATE_NULL;
    }
	
    return;
}


/***********************************************************************
    复位实例
    成功返回实例FSP_OK，失败返回FSP_ERR
 ***********************************************************************/
SINT32  FSP_ResetInstance(SINT32  InstID)
{  
    FSP_INST_S *pFspInst = s_pFspInst[InstID];
    
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");

    FSP_ClearContext(pFspInst);

    return FSP_OK;
}

/***********************************************************************
    清空实例
    在极端情况下，如果解码出现严重错误，协议层可能会要求清除所有解码上下
    文，其中包括清空FSP实例，将所有帧存都标记为不参考，不显示，等待新一轮
    解码使用。
    与FSP_ResetInstance()不同的是，本函数不清除配置信息，也不清除帧存的分配
    信息，仅仅清除所有帧的占用信息。
    成功返回实例FSP_OK，失败返回FSP_ERR
 ***********************************************************************/
SINT32  FSP_EmptyInstance(SINT32  InstID)
{
    FSP_INST_S *pstInst;
    SINT32 i;

    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");

    pstInst = s_pFspInst[InstID];

    /* 清除逻辑帧存占用 */
    memset( &pstInst->stLogicFs[0], 0, sizeof(FSP_LOGIC_FS_S)*MAX_FRAME_NUM);

    /* 清除解码帧存占用 */
    for (i = 0; i < pstInst->s32DecFsNum; i++)
    {
        pstInst->stDecFs[i].IsDecRef = 0;
        pstInst->stDecFs[i].DispState = FS_DISP_STATE_NOT_USED;
        pstInst->stDecFs[i].u32Tick = 0;
    }
    /* 清除显示占用 */
    for (i = 0; i < pstInst->s32DispFsNum; i++)
    {
        pstInst->stDispFs[i].IsDecRef = 0;
        pstInst->stDispFs[i].DispState = FS_DISP_STATE_NOT_USED;
        pstInst->stDispFs[i].u32Tick = 0;
    }
    /* 清除PMV占用 */
    for (i = 0; i < pstInst->s32PmvNum; i++)
    {
        pstInst->IsPmvInUse[i] = 0;
    }

    /* 实例tick清零 */
    pstInst->u32InstTick = 0;

    return FSP_OK;
}


/***********************************************************************
    清空没有被放到VO QUEUE 的逻辑帧
 ***********************************************************************/
SINT32 FSP_ClearNotInVoQueue(SINT32 InstID,IMAGE_VO_QUEUE *pstVoQue)
{
    FSP_INST_S *pstInst;
    IMAGE *p_image;
    SINT32 i;

    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(pstVoQue != NULL, "pstVoQue is NULL");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");
    
    pstInst = s_pFspInst[InstID];

    for(i= 0; i < MAX_FRAME_NUM; i++)
    {
        p_image = &(pstInst->stLogicFs[i].stDispImg);   
        FSP_SetRef(InstID, p_image->image_id, 0);

        if( SYN_OK != IsImageInVoQueue(pstVoQue, p_image))
        {
            FSP_SetDisplay(InstID,p_image->image_id, 0);   
        }
    }

    return FSP_OK;

}


/***********************************************************************
    配置实例
 ***********************************************************************/
SINT32  FSP_ConfigInstance( SINT32 InstID,  FSP_INST_CFG_S *pstFspInstCfg )
{
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(pstFspInstCfg != NULL, "pstFspInstCfg = NULL");
    FSP_ASSERT_RET((NULL != s_pFspInst[InstID] && s_pFspInst[InstID]->eFspInstState == FSP_INST_STATE_INUSE), "This inst is not active");
        
    /* 配置信息过滤 */
    pstFspInstCfg->s32DispLoopEnable = 0;    /* 不需要后处理帧存  */
    
    /* 既然FSP不能动态修改配置，则配置时清除实例上下文也是合理的 */
    FSP_ClearContext(pstInst);
    
    /* 保存配置信息 */
    memcpy( &pstInst->stInstCfg, pstFspInstCfg, sizeof(FSP_INST_CFG_S) );

    return FSP_OK;
}


/***********************************************************************
    帧存分割
 ***********************************************************************/
SINT32  FSP_PartitionFsMemory ( SINT32 InstID, UADDR MemPhyAddr, SINT32 MemSize, SINT32 *UsedMemSize )
{
    SINT32  i, Ret;
    SINT32  MinFsNum;
    UADDR   PhyAddr;
    SINT32  Size;
    SINT32  ExpectedRefNum = 0;
    FSP_INST_S *pstInst;
    FSP_INST_CFG_S *pstCfg;
    VDMHAL_MEM_ARRANGE_S MemArrange;
    VDEC_CHAN_CAP_LEVEL_E  eChanCapLevel;
    extern SINT32 CapItem[][7];
    memset(&MemArrange, 0, sizeof(VDMHAL_MEM_ARRANGE_S));
        
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");

	pstInst = s_pFspInst[InstID];

	pstCfg  = &pstInst->stInstCfg;
	PhyAddr = MemPhyAddr;
	Size    = MemSize;

    if(0 == s_pstVfmwChan[InstID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn)// check only when dfs disable	
    {
        /* 判断图象大小是否符合通道的能力级别，若不符合则放弃分配，返回失败 */
        eChanCapLevel = VCTRL_GetChanCapLevel(InstID);
        if  (eChanCapLevel >= CAP_LEVEL_BUTT || 
            (((pstCfg->s32DecFsWidth * pstCfg->s32DecFsHeight) > (CapItem[eChanCapLevel][0] * CapItem[eChanCapLevel][1]))&&(eChanCapLevel != CAP_LEVEL_USER_DEFINE_WITH_OPTION)) )
        {
            if (eChanCapLevel >= CAP_LEVEL_BUTT)
            {
                dprint(PRN_FATAL, "eChanCapLevel = %d is not expected!\n", eChanCapLevel);
            }
            else
            {
                dprint(PRN_FATAL, "decode channel CapLevel is %d(w=%d,h=%d), this stream (w=%d,h=%d) can NOT be decoded!\n",
                eChanCapLevel, CapItem[eChanCapLevel][0], CapItem[eChanCapLevel][1],
                pstCfg->s32DecFsWidth, pstCfg->s32DecFsHeight);
            }
            pstInst->s8TotalValidFsNum = 0;
            return FSP_ERR;
        }
    }

    /* 判断是否有2D scaler，如果没有则统一划分物理帧存(dec,disp,tf三种物理帧存大小都是一样的). */ 
	if ((pstCfg->s32DispFsHeight == 0 || pstCfg->s32DispFsWidth == 0) || (0 == pstCfg->s32DispLoopEnable) ||
		((pstCfg->s32DecFsHeight == pstCfg->s32DispFsHeight) && (pstCfg->s32DecFsWidth  == pstCfg->s32DispFsWidth)))
	{
        MinFsNum = pstCfg->s32ExpectedDecFsNum + pstCfg->s32DispLoopEnable*4;
        if ((1 != (s_pstVfmwChan[InstID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn)) || \
           ((1 == (s_pstVfmwChan[InstID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn)) && \
           ((FSP_PARTITION_STATE_FIRST == s_pstVfmwChan[InstID]->FspInst.eFspPartitionState) || \
           (FSP_PARTITION_STATE_SUCCESS == s_pstVfmwChan[InstID]->FspInst.eFspPartitionState))))
		{
            if (1 == (s_pstVfmwChan[InstID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn))
            {
                // 使能动态帧存，只要求实际帧存个数
                ExpectedRefNum = pstCfg->s32ExpectedDecFsNum;
            }
            else
            {
                // 不使能动态帧存，有多少用多少
                ExpectedRefNum = 40;
            }
		    Ret = VDMHAL_ArrangeMem(PhyAddr, Size, pstCfg->s32DecFsWidth, pstCfg->s32DecFsHeight, pstCfg->s32ExpectedPmvNum, ExpectedRefNum, InstID, &MemArrange);  /* PmvNum = 0 */
        }
        else if(FSP_PARTITION_STATE_WAIT == s_pstVfmwChan[InstID]->FspInst.eFspPartitionState)
        {
            return FSP_OK;
        }
        else
        {
            pstInst->s8TotalValidFsNum = 0;
            dprint(PRN_ERROR,"DFS, Wrong Partition State. State: 0x%x\n", s_pstVfmwChan[InstID]->FspInst.eFspPartitionState); 
            return FSP_ERR;
        }
        
        if (VDMHAL_NOT_ARRANGE == Ret)
        {
            pstInst->s8TotalValidFsNum = MemArrange.ValidFrameNum;
            s_pstVfmwChan[InstID]->stSynExtraData.s32WaitFsFlag = 1;
            dprint(PRN_FS,"DFS, Chan %d change to FSP_WAIT_ARRANGE state.\n", InstID); 
            return FSP_WAIT_ARRANGE;
        }
        else if(VDMHAL_OK == Ret)
        {
            pstInst->s8TotalValidFsNum = MemArrange.ValidFrameNum;
            s_pstVfmwChan[InstID]->stSynExtraData.s32WaitFsFlag = 0;
            if(1 == (s_pstVfmwChan[InstID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn))
            {
                s_pstVfmwChan[InstID]->stDynamicFSTimestamp.u32AllTime = VFMW_OSAL_GetTimeInMs() - s_pstVfmwChan[InstID]->stDynamicFSTimestamp.u32StartTime;
                if((s_pstVfmwChan[InstID]->stDynamicFSTimestamp.u32AllTime) > g_u32DFSMaxAllocTime)
                {
                    g_u32DFSMaxAllocTime = s_pstVfmwChan[InstID]->stDynamicFSTimestamp.u32AllTime;
                }
            }
            dprint(PRN_FS, "DFS, Mem Element Fill Successed! Ready to Decode!\n");
        }
        else
        {
            pstInst->s8TotalValidFsNum = 0;
            s_pstVfmwChan[InstID]->stSynExtraData.s32WaitFsFlag = 0;
            dprint(PRN_FATAL, "Fsp arrange failed, return %d\n", Ret);
            return FSP_ERR;
        }
        
		if (MemArrange.ValidFrameNum >= MinFsNum)
		{
			pstInst->s32DispFsNum = 0;
			pstInst->s32TfFsNum = 0;

			/* 解码物理帧存: 如果输出环路不使能所有帧存都归解码用，否则要分开管理 */
			if (0 == pstCfg->s32DispLoopEnable)
			{
                if (pstInst->IsOmxPath && 1 != s_pstVfmwChan[InstID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn)
                {
                    //+1为了兼容单独双场，+3给VPSS做DEI缓存
                    pstInst->s32DecFsNum = MIN(MemArrange.ValidFrameNum, pstCfg->s32ExpectedDecFsNum+1+3);
                }
                else
                {
                    pstInst->s32DecFsNum = MIN(MemArrange.ValidFrameNum, 40); 
                }
			}
			else
			{
            #ifdef VFMW_CFG_CAP_HD_SIMPLE
                pstInst->s32DecFsNum = MIN(MemArrange.ValidFrameNum, 40);
            #else
                pstInst->s32DecFsNum = pstCfg->s32ExpectedDecFsNum;
            #endif
			}

			/* 地址数组需初始化为有效值，无效的逻辑帧存地址初始化为第零个的值 */
			for (i = 0; i < MAX_FRAME_NUM; i++)
			{
			    if (i < pstInst->s32DecFsNum)
			    {
				    pstInst->stDecFs[i].PhyFsID     = i;
		            pstInst->stDecFs[i].PhyAddr     = MemArrange.FrameAddr[i];
			    #ifdef VFMW_MODULE_LOWDLY_SUPPORT
					pstInst->stDecFs[i].LineNumAddr = MemArrange.LineNumAddr[i];
				#endif
					pstInst->stDecFs[i].Stride      = MemArrange.VahbStride;
					pstInst->stDecFs[i].FsWidth     = pstCfg->s32DecFsWidth;
					pstInst->stDecFs[i].FsHeight    = pstCfg->s32DecFsHeight;
		            pstInst->stDecFs[i].ChromOffset = MemArrange.ChromOffset;
					pstInst->stDecFs[i].IsDecRef    = 0;
					pstInst->stDecFs[i].DispState   = FS_DISP_STATE_NOT_USED;
			    }
				else
				{
				    pstInst->stDecFs[i].PhyFsID     = 0;
		            pstInst->stDecFs[i].PhyAddr     = MemArrange.FrameAddr[0];
					pstInst->stDecFs[i].Stride      = MemArrange.VahbStride;
					pstInst->stDecFs[i].FsWidth     = pstCfg->s32DecFsWidth;
					pstInst->stDecFs[i].FsHeight    = pstCfg->s32DecFsHeight;
		            pstInst->stDecFs[i].ChromOffset = MemArrange.ChromOffset;
					pstInst->stDecFs[i].IsDecRef    = 0;
					pstInst->stDecFs[i].DispState   = FS_DISP_STATE_NOT_USED;

				}
			}
			
            /* TF物理帧存(TF虽已确定不启用，但TF物理内存与DB公用，硬件还得用) */
			pstInst->s32TfFsNum = 1;
		    pstInst->stTfFs[0].PhyFsID     = 0;
            pstInst->stTfFs[0].PhyAddr     = MemArrange.FrameAddr[pstInst->s32DecFsNum];
			pstInst->stTfFs[0].Stride      = MemArrange.VahbStride;
			pstInst->stTfFs[0].FsWidth     = pstCfg->s32DecFsWidth;
			pstInst->stTfFs[0].FsHeight    = pstCfg->s32DecFsHeight;
            pstInst->stTfFs[0].ChromOffset = MemArrange.ChromOffset;
			pstInst->stTfFs[0].IsDecRef    = 0;
			pstInst->stTfFs[0].DispState   = FS_DISP_STATE_NOT_USED;

            /* 显示物理帧存 */
			if (0 == pstCfg->s32DispLoopEnable)
			{
                pstInst->s32DispFsNum = 0;
			}
            else
            {
                pstInst->s32DispFsNum = MIN((MemArrange.ValidFrameNum - pstInst->s32DecFsNum - pstInst->s32TfFsNum), 25);
				//if (pstInst->s32DispFsNum < pstCfg->s32ExpectedDispFsNum + pstCfg->s32ExpectedDecFsNum)
				if (pstInst->s32DispFsNum < pstCfg->s32ExpectedDispFsNum)
				{
                    pstInst->s8TotalValidFsNum = 0;
                    dprint(PRN_FATAL, "disp fs(=%d) less than expected(=%d+%d)!\n", pstInst->s32DispFsNum, pstCfg->s32ExpectedDecFsNum, pstCfg->s32ExpectedDispFsNum);
					return FSP_ERR;
				}
			}
			for (i = 0; i < MAX_FRAME_NUM; i++)
			{
				if (i < pstInst->s32DispFsNum)
				{
				    pstInst->stDispFs[i].PhyFsID     = i;
		            pstInst->stDispFs[i].PhyAddr     = MemArrange.FrameAddr[pstInst->s32DecFsNum + pstInst->s32TfFsNum + i];
					pstInst->stDispFs[i].Stride      = MemArrange.VahbStride;
					pstInst->stDispFs[i].FsWidth     = pstCfg->s32DispFsWidth;
					pstInst->stDispFs[i].FsHeight    = pstCfg->s32DispFsHeight;
		            pstInst->stDispFs[i].ChromOffset = MemArrange.ChromOffset;
					pstInst->stDispFs[i].IsDecRef    = 0;
					pstInst->stDispFs[i].DispState   = FS_DISP_STATE_NOT_USED;
				}
				else
				{
				    pstInst->stDispFs[i].PhyFsID     = 0;
		            pstInst->stDispFs[i].PhyAddr     = MemArrange.FrameAddr[pstInst->s32DecFsNum + pstInst->s32TfFsNum + 0];
					pstInst->stDispFs[i].Stride      = MemArrange.VahbStride;
					pstInst->stDispFs[i].FsWidth     = pstCfg->s32DispFsWidth;
					pstInst->stDispFs[i].FsHeight    = pstCfg->s32DispFsHeight;
		            pstInst->stDispFs[i].ChromOffset = MemArrange.ChromOffset;
					pstInst->stDispFs[i].IsDecRef    = 0;
					pstInst->stDispFs[i].DispState   = FS_DISP_STATE_NOT_USED;
				}
			}

			/* PMV 存储块 */
			pstInst->s32PmvNum  = MIN(MemArrange.ValidPMVNum, MAX_PMV_NUM);
			for (i = 0; i < MAX_PMV_NUM; i++ )
			{
				if (i < pstInst->s32PmvNum)
				{
	                pstInst->PmvAddr[i] = MemArrange.PMVAddr[i];
					pstInst->IsPmvInUse[i] = 0;
				}
				else
				{
	                pstInst->PmvAddr[i] = MemArrange.PMVAddr[0];
					pstInst->IsPmvInUse[i] = 0;
				}
			}
            pstInst->s32HalfPmvOffset = MemArrange.HafPmvOffset;

            /* 伪物理帧初始化 (H264解gap将会用到伪物理帧) */
			pstInst->stDummyPhyFs.PhyFsID     = 0;
			pstInst->stDummyPhyFs.PhyAddr     = pstInst->stDecFs[0].PhyAddr; /* 地址不会使用，为保安全随便赋个值而已 */
			pstInst->stDummyPhyFs.Stride      = MemArrange.VahbStride;
			pstInst->stDummyPhyFs.FsWidth     = pstCfg->s32DecFsWidth;
			pstInst->stDummyPhyFs.FsHeight    = pstCfg->s32DecFsHeight;
			pstInst->stDummyPhyFs.ChromOffset = MemArrange.ChromOffset;
			pstInst->stDummyPhyFs.IsDecRef    = 0;
			pstInst->stDummyPhyFs.DispState   = 0;

             /* 查询分辨率是否变化，如是，事件上报 */
             if (pstCfg->s32DecFsWidth != pstInst->stPreInfo.s32PreWidth || pstCfg->s32DecFsHeight != pstInst->stPreInfo.s32PreHeight || pstInst->s32DecFsNum != pstInst->stPreInfo.s32PreDecNum)
             {
                 if (pstInst->stPreInfo.s32PreWidth != 0 && pstInst->stPreInfo.s32PreHeight != 0 && pstInst->stPreInfo.s32PreDecNum != 0)  //排除第一次分隔的错误判断
                 {
                 #ifdef VFMW_CFG_CAP_HD_SIMPLE
                     pstInst->s8SizeChangeFlag = 1;
                     REPORT_RESOLUTION_CHANGE(InstID);
                 #endif
                 }
                                 
                 pstInst->stPreInfo.s32PreWidth = pstCfg->s32DecFsWidth;
                 pstInst->stPreInfo.s32PreHeight = pstCfg->s32DecFsHeight;
                 pstInst->stPreInfo.s32PreDecNum = pstInst->s32DecFsNum;
                 pstInst->stPreInfo.s32PreDecSlotLen = pstInst->stDecFs[1].PhyAddr - pstInst->stDecFs[0].PhyAddr;
             }
                     
			/* 反馈真正占用的内存量 */
			*UsedMemSize = MemArrange.TotalMemUsed;
			return FSP_OK;
		}
		else
		{
            dprint(PRN_FATAL, "arrange ret %d, min = %d, actual = %d\n", Ret, MinFsNum, MemArrange.ValidFrameNum);
		}
	}
	else
	{
        /* 若有2D scaler，则先划分dec和tf帧存，再分disp帧存. 加入2d scaler后再实现 */
        dprint(PRN_ERROR, "%s %d err return!\n", __func__, __LINE__); 
	}
	
    return FSP_ERR;
}


/***********************************************************************
    获取解码帧地址表
    VDH配置解码帧地址时，要求按"解码帧地址表 + 帧ID"的方式配
 ***********************************************************************/
VOID  FSP_GetDecodeFrameTable(SINT32 InstID, UADDR PhyAddr[], SINT32 *pFsNum)
{
    SINT32 i;
    FSP_INST_S *pstInst;
    
    FSP_ASSERT(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");	
    FSP_ASSERT(PhyAddr != NULL, "PhyAddr is NULL\n");
    FSP_ASSERT(pFsNum != NULL, "pFsNum is NULL\n");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");

    pstInst = s_pFspInst[InstID];
    *pFsNum = pstInst->s32DecFsNum;
    for (i = 0; i < pstInst->s32DecFsNum; i++)
    {
        PhyAddr[i] = pstInst->stDecFs[i].PhyAddr;
    }
	
    return;
}


/***********************************************************************
    获取解码PMV地址表
    VDH配置PMV地址时，要求按"PMV地址表 + PMV ID"的方式配
 ***********************************************************************/
VOID  FSP_GetDecodePmvTable(SINT32 InstID, UADDR PhyAddr[], SINT32 *pPmvNum)
{
    SINT32 i;
    FSP_INST_S *pstInst;
    
    FSP_ASSERT(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");	
    FSP_ASSERT(PhyAddr != NULL, "PhyAddr is NULL\n");
    FSP_ASSERT(pPmvNum != NULL, "pFsNum is NULL\n");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");

    pstInst = s_pFspInst[InstID];
    *pPmvNum = pstInst->s32PmvNum;
    for (i = 0; i < pstInst->s32PmvNum; i++)
    {
        PhyAddr[i] = pstInst->PmvAddr[i];
    }
	
    return;
}

/***********************************************************************
    判断是否还能申请到新帧
    如果能申请到，返回1，否则返回0
 ***********************************************************************/
SINT32  FSP_IsNewFsAvalible(SINT32 InstID)
{
    SINT8  flag = 0;
    SINT32 i;
    FSP_INST_S *pstInst;

    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");	
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");	

    pstInst = s_pFspInst[InstID];

    /* 0. 如果PartitionFsMemory操作尚未执行，固定返回1，否则码流得不到解析，也就没有机会解到SEQ */
    if (0 == pstInst->s32DecFsNum)
    {
        return 1;
    }

    /* 1. 有解码帧存? */
    for (i = 0; i < pstInst->s32DecFsNum; i++)
    {
        if ((pstInst->stDecFs[i].IsDecRef == 0) && (pstInst->stDecFs[i].DispState == FS_DISP_STATE_NOT_USED))
        {
            if (FSP_IsOmxBypassMode(InstID) && (FSP_ExtBufHandler(InstID, BC_CHK_BUF, &pstInst->stDecFs[i].PhyAddr) != 1))
            {
                flag = 1;
                continue;
            }
            else
            {
                break;
            }
        }
    }
	
    if (i >= pstInst->s32DecFsNum)
    {
        goto fs_leak_detect;
    }

    return 1;


fs_leak_detect:

    if (FSP_IsFsLeak(InstID))
    {
        return -1;
    }

    if (flag)
    {
        return 2;
    }

    return 0;
}

/* 检测是否发生了帧存(主要是显示帧存)泄漏 */
SINT32 FSP_IsFsLeak(SINT32 InstID)
{
    SINT32 i;
    SINT32  RefNum, NewNum, ReadNum;    
    SINT32  TotalFsNum;
    FSP_INST_S *pstInst;

    pstInst = s_pFspInst[InstID];
    if (NULL == pstInst)
    {
       dprint(PRN_ERROR, "FSP_IsFsLeak: fsp is not inited \n");
			return FSP_ERR;
    }            
    
    TotalFsNum = pstInst->s32DecFsNum;
    for (i = 0; i < pstInst->s32DecFsNum; i++)
    {
        if ((pstInst->stDecFs[i].IsDecRef == 0) && (pstInst->stDecFs[i].DispState == FS_DISP_STATE_NOT_USED))
        {
            break;
	  }
    }

    /* 如果没有空闲帧存，要判断是否都在队列中 */
    if (i >= TotalFsNum)
    {
        RefNum = ReadNum = NewNum = 0;
        VCTRL_GetChanImgNum(InstID, &RefNum, &ReadNum, &NewNum);
        if (RefNum + ReadNum + NewNum + 2 < TotalFsNum)
        {
            dprint(PRN_FATAL,"No free fs: ref=%d,read=%d,new=%d,total=%d\n",RefNum, ReadNum, NewNum, TotalFsNum);
            FSP_PrintContext(InstID);
            return 1;
        }
    }

    return 0;
}


/* 找一个tick最小的物理帧存，返回帧存号 */
SINT32 FindLeastTickPhyFs(FSP_PHY_FS_S *pstPhyFs, SINT32 PhyNum)
{
    SINT32 i, LeastFsID = 0;
    UINT32 LeastTick;

    LeastTick = 0xffffffff;
    for (i = 0; i < PhyNum; i++)
    {
        if (pstPhyFs->u32Tick < LeastTick)
        {
              LeastTick = pstPhyFs->u32Tick;
          	LeastFsID = i;
        }
        pstPhyFs++;   //yyc change
    }

    return LeastFsID;
}

/***********************************************************************
    获取新的逻辑帧
    InstID: 实例ID
    NeedPhyFs: 标志是否需要分配物理帧存。H.264在解码gap时也要分配帧存，
               但这种帧存不需要给真实的物理帧，以此区分.
               
    成功返回逻辑帧的ID，失败返回-1
 ***********************************************************************/
#define  PHYFS_USED(pFs) \
 ((pFs != NULL) && (((pFs)->DispState != FS_DISP_STATE_NOT_USED) || ((pFs)->IsDecRef != 0) || ((pFs)->IsTfRef != 0)))
 
SINT32 FSP_NewLogicFs ( SINT32 InstID, SINT32 NeedPhyFs )
{
    SINT32 i;
    FSP_INST_S *pstInst;
    FSP_LOGIC_FS_S *pstLogicFs = NULL;
    FSP_PHY_FS_S *pstDecFs, *pstDispFs, *pstTfFs;
    IMAGE *pstImg;
 
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");
     
    VFMW_OSAL_SpinLock(G_SPINLOCK_FSP);
    
    pstInst = s_pFspInst[InstID];

	/* 寻找一个空闲的逻辑帧存 */
	pstLogicFs = NULL;

    for (i = 0; i < MAX_FRAME_NUM; i++)
    {
        /* 为防止逻辑帧存泄漏，把pstDecodeFs，pstDispOutFs，pstTfOutFs全部无效的逻辑帧视为空闲逻辑帧 */
        if (pstInst->stLogicFs[i].s32IsRef == 0 && pstInst->stLogicFs[i].s32DispState == FS_DISP_STATE_NOT_USED)
        {
              pstLogicFs = &pstInst->stLogicFs[i];
              pstLogicFs->s32LogicFsID = i;
              pstLogicFs->IsDummyFs = 0;
              break;
        }
	}
    
    if (NULL == pstLogicFs)
    {
        dprint(PRN_FATAL, "no logic frame store!!!\n");
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_FSP);
        /* 清洗帧存池操作在外面做 */
        return -1;
	}
	
    pstLogicFs->pstDecodeFs  = NULL;
	pstLogicFs->pstDispOutFs = NULL;
	pstLogicFs->pstTfOutFs   = NULL;
	pstLogicFs->PmvAddr      = 0;

    if (0 == NeedPhyFs)
    {
        /* 只分逻辑帧，无需分配物理帧. 只有H.264解GAP的时候才会进入此分支 */
		pstLogicFs->pstDecodeFs  = &pstInst->stDummyPhyFs;
		pstLogicFs->pstDispOutFs = &pstInst->stDummyPhyFs;
		pstLogicFs->pstTfOutFs   = &pstInst->stDummyPhyFs;
		pstLogicFs->PmvAddr      = pstInst->PmvAddr[0];   /* pmv地址和ID不会用到，为安全赋个值而已 */
		pstLogicFs->PmvIdc       = pstInst->s32PmvNum - 1;
		pstLogicFs->IsDummyFs    = 1;
    }
	else
	{
        /*** 申请解码帧存 ***/	
		for (i=0; i < pstInst->s32DecFsNum; i++)
		{
            if (pstInst->stDecFs[i].IsDecRef == 0 && pstInst->stDecFs[i].DispState == FS_DISP_STATE_NOT_USED)
            {
                if (FSP_IsOmxBypassMode(InstID) && (FSP_ExtBufHandler(InstID, BC_CHK_BUF, &pstInst->stDecFs[i].PhyAddr) != 1))
                {
                    continue;
                }
                else
                {
                    pstLogicFs->pstDecodeFs = &pstInst->stDecFs[i];
                    break;
                }
            }
		}
		if (NULL == pstLogicFs->pstDecodeFs)
	    {
		    dprint(PRN_FATAL, "%s no decode phy fs\n", __func__);
    		for (i = 0; i < pstInst->s32DecFsNum; i++)
    		{
    		    dprint(PRN_FATAL,"%d%d ",pstInst->stDecFs[i].IsDecRef,pstInst->stDecFs[i].DispState);
    		}
    		dprint(PRN_FATAL,"\n");

            if (pstInst->s8TotalValidFsNum > 0)
            {
    			/* 容错: 找一个最"老"的解码帧 */
    			i = FindLeastTickPhyFs(&pstInst->stDecFs[0], pstInst->s32DecFsNum);
    			pstLogicFs->pstDecodeFs = &pstInst->stDecFs[i];
            }
            else
            {
                dprint(PRN_FATAL, "%s Not partition yet!\n", __func__);
                VFMW_OSAL_SpinUnLock(G_SPINLOCK_FSP);
                return -1;
            }
		}

		/*** 申请TF帧存 ***/
		pstLogicFs->pstTfOutFs = &pstInst->stTfFs[0];

        /* 申请PMV存储区 */
		if (pstInst->s32PmvNum > 0)
  		{
            for (i = 0; i < pstInst->s32PmvNum; i++)
            {
                if (0 == pstInst->IsPmvInUse[i])
                {
                    pstLogicFs->PmvIdc  = i;
                    pstLogicFs->PmvAddr = pstInst->PmvAddr[i];
                    pstLogicFs->HalfPmvOffset = pstInst->s32HalfPmvOffset;
                    break;
                }
            }

            if (i >= pstInst->s32PmvNum)
            {
                for (i = 0; i < pstInst->s32PmvNum; i++)
                {
                    pstInst->IsPmvInUse[i] = 0;
                }

                pstLogicFs->PmvIdc  = 0;
                pstLogicFs->PmvAddr = pstInst->PmvAddr[0];
                pstLogicFs->HalfPmvOffset = pstInst->s32HalfPmvOffset;
                dprint(PRN_FATAL, "no pmv memory\n");
            }
	    }

		/*** 申请显示帧存 ***/
		if (0 == pstInst->stInstCfg.s32DispLoopEnable)
		{
            pstLogicFs->pstDispOutFs = pstLogicFs->pstDecodeFs;
		}
	}
	
    /* 显示帧存置为"预占用"防止重复使用 */
	pstLogicFs->s32DispState = FS_DISP_STATE_ALLOCED;
	pstLogicFs->pstDispOutFs->DispState = FS_DISP_STATE_ALLOCED;
	pstLogicFs->eLfsPmvState            = LFS_PMV_STATE_ALLOCATED;	

    /* 给各种帧存打上"时间戳"，防止以后由于不可意料的原因错误访问 */
	pstLogicFs->u32Tick               = pstInst->u32InstTick;
	pstLogicFs->pstDecodeFs->u32Tick  = pstLogicFs->u32Tick;
	pstLogicFs->pstDispOutFs->u32Tick = pstLogicFs->u32Tick;
	pstInst->u32InstTick++;

    /* 填写IMAGE结构的相应信息 */
	pstDecFs = pstLogicFs->pstDecodeFs;
	pstDispFs = pstLogicFs->pstDispOutFs;
	pstTfFs = pstLogicFs->pstTfOutFs;
	pstImg = &pstLogicFs->stDispImg;

	memset(pstImg, 0, sizeof(IMAGE));
	pstImg->image_id           = pstLogicFs->s32LogicFsID;
    pstImg->image_width        = pstDecFs->FsWidth;
	pstImg->image_height       = pstDecFs->FsHeight;
	pstImg->image_stride       = pstDispFs->Stride;

	pstImg->luma_phy_addr      = pstDecFs->PhyAddr;
    pstImg->chrom_phy_addr     = pstImg->luma_phy_addr + pstDecFs->ChromOffset;
	pstImg->top_luma_phy_addr  = pstDispFs->PhyAddr;
	pstImg->top_chrom_phy_addr = pstImg->top_luma_phy_addr + pstDispFs->ChromOffset;
	pstImg->btm_luma_phy_addr  = pstImg->top_luma_phy_addr + pstDispFs->Stride;
	pstImg->btm_chrom_phy_addr = pstImg->top_chrom_phy_addr + pstDispFs->Stride;

	// 填写图像输出和TF用的几个地址
	pstImg->luma_2d_phy_addr   = pstDispFs->PhyAddr;
    pstImg->chrom_2d_phy_addr  = pstImg->luma_2d_phy_addr + pstDispFs->ChromOffset;

    VFMW_OSAL_SpinUnLock(G_SPINLOCK_FSP);

    return pstLogicFs->s32LogicFsID;
}


/***********************************************************************
    删除指定逻辑帧的PMV块
    PMV块与每一个解码帧绑定，在将一帧标记为参考时，它的PMV块也被锁定。但
    不是每一个参考帧都需要PMV块(前向参考帧的PMV无需保存)，所以在一个参考
    帧的PMV块不需要保存时将它删掉，可保证最大程度地节省内存。
    如果PMV块足够(例如MPEG2协议下3个PMV块)，本函数不使用也可以正常运行.
 ***********************************************************************/
VOID  FSP_RemovePmv ( SINT32 InstID, SINT32 LogicFrameID )
{
    FSP_LOGIC_FS_S *pstLogicFs;
    FSP_INST_S *pstInst = s_pFspInst[InstID];

    FSP_ASSERT(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT(LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM, "LogicFrameID out of range");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");

    pstLogicFs = &pstInst->stLogicFs[LogicFrameID];

    if (LFS_PMV_STATE_VALID == pstLogicFs->eLfsPmvState)
    {
        if (pstLogicFs->PmvIdc >= 0 && pstLogicFs->PmvIdc < MAX_PMV_NUM)
        {
            pstInst->IsPmvInUse[pstLogicFs->PmvIdc] = 0;
        }
        pstLogicFs->eLfsPmvState = LFS_PMV_STATE_NOT_USE;
    }

    return;
}


/***********************************************************************
    设置逻辑帧的参考属性, 包括解码帧和TF参考帧
    IsRef = 1标记为作参考，反之该逻辑帧标记为不参考
 ***********************************************************************/
VOID  FSP_SetRef ( SINT32 InstID, SINT32 LogicFrameID, SINT32 IsRef )
{
    FSP_LOGIC_FS_S *pstLogicFs = NULL;
    FSP_INST_S *pstInst = NULL;
    
    FSP_ASSERT(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT(LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM, "LogicFrameID out of range");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");
    
    pstInst = s_pFspInst[InstID];

    if(NULL == pstInst)
    {
    	dprint(PRN_DBG, "%s %d NULL == pstInst!!\n",__FUNCTION__,__LINE__);
    	return;
    }
    
    pstLogicFs = &pstInst->stLogicFs[LogicFrameID];
    pstLogicFs->s32IsRef = IsRef;

    if (pstLogicFs->IsDummyFs)   /* 如果是gap帧，其所指的物理帧均无意义，不作处理 */
    {
        return;
    }

    /*** 1. 解码参考处理(包括解码帧，PMV) ***/
    /* tick若不等，说明解码帧存应该被剥夺，给其它逻辑帧存了，此情况下会造成vdec外部帧存泄漏 */
    if ((NULL != pstLogicFs->pstDecodeFs) && (pstLogicFs->pstDecodeFs->u32Tick == pstLogicFs->u32Tick))
    {
        pstLogicFs->pstDecodeFs->IsDecRef = IsRef;
    }
    // PMV块
    if ((pstLogicFs->PmvIdc >= 0) && (pstLogicFs->PmvIdc < MAX_PMV_NUM))
    {
        if ((1 == IsRef) && (LFS_PMV_STATE_ALLOCATED == pstLogicFs->eLfsPmvState))
        {
            if( NULL == pstInst)
            {
                dprint(PRN_DBG, "%s %d pstInst is null!!\n",__FUNCTION__,__LINE__);
                return;
            }
            pstInst->IsPmvInUse[pstLogicFs->PmvIdc] = 1;

            pstLogicFs->eLfsPmvState = LFS_PMV_STATE_VALID;
        }
        else if ((0 == IsRef) && (LFS_PMV_STATE_VALID == pstLogicFs->eLfsPmvState))
        {
            if( NULL == pstInst)
            {
                dprint(PRN_DBG, "%s %d pstInst is null!!\n",__FUNCTION__,__LINE__);
                return;
            }
            pstInst->IsPmvInUse[pstLogicFs->PmvIdc] = 0;
            pstLogicFs->PmvAddr = 0;
            pstLogicFs->eLfsPmvState = LFS_PMV_STATE_NOT_USE;
        }
    }
    else
    {
        dprint(PRN_FATAL, "fsp.c, line %d: pstLogicFs->PmvIdc out of range(=%d)\n", __LINE__,pstLogicFs->PmvIdc);
    }
    
    /* 如果标记为"不参考"，还要清除一些信息 */
    if (0 == IsRef)
    {
    	if (NULL != pstLogicFs->pstDispOutFs && pstLogicFs->pstDispOutFs->DispState == FS_DISP_STATE_ALLOCED)
    	{
          pstLogicFs->pstDispOutFs->DispState = FS_DISP_STATE_NOT_USED;
    	}
    	//pstLogicFs->pstDecodeFs = NULL;
    }

    /* 如果标记为"参考"，说明这一帧解码完毕，对应的显示物理帧要标记为"解码完成" */
    if ((NULL != pstLogicFs->pstDispOutFs) && (pstLogicFs->pstDispOutFs->u32Tick == pstLogicFs->u32Tick))
    {
        if ((1 == IsRef) && FS_DISP_STATE_ALLOCED == pstLogicFs->pstDispOutFs->DispState)
        {
           pstLogicFs->pstDispOutFs->DispState = FS_DISP_STATE_DEC_COMPLETE;
           pstLogicFs->s32DispState = FS_DISP_STATE_DEC_COMPLETE;
    	}
    }

    if (0 == IsRef)
    {
    	pstLogicFs->pstDecodeFs = NULL;
    }

    return;
}

/***********************************************************************
    获取逻辑帧的解码参考属性
 ***********************************************************************/
SINT32  FSP_GetRef ( SINT32 InstID, SINT32 LogicFrameID )
{
    FSP_LOGIC_FS_S *pstLogicFs;
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "FSP_GetRef: InstID out of range");
    FSP_ASSERT_RET(LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM, "FSP_GetRef: LogicFrameID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "FSP_GetRef: Fsp is not inited");
    
    pstLogicFs = &pstInst->stLogicFs[LogicFrameID];

    return pstLogicFs->s32IsRef;
}


/***********************************************************************
    设置逻辑帧是否等待显示
 ***********************************************************************/
VOID  FSP_SetDisplay ( SINT32 InstID, SINT32 LogicFrameID, SINT32 IsWaitDisp )
{
    FSP_LOGIC_FS_S *pstLogicFs;
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    FSP_ASSERT(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT(LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM, "LogicFrameID out of range");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");
    
    VFMW_OSAL_SpinLock(G_SPINLOCK_FSP);
   
    pstLogicFs = &pstInst->stLogicFs[LogicFrameID];

    pstLogicFs->s32DispState = (0 == IsWaitDisp)? FS_DISP_STATE_NOT_USED : FS_DISP_STATE_WAIT_DISP;

    if (pstLogicFs->IsDummyFs || NULL == pstLogicFs->pstDispOutFs)
    {
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_FSP);
        return;
    }
	
    if (pstLogicFs->pstDispOutFs->u32Tick != pstLogicFs->u32Tick)
    {
        dprint(PRN_FATAL,"FSP_SetDisplay: LogicTick=%d, DispTick=%d!\n",pstLogicFs->u32Tick,pstLogicFs->pstDispOutFs->u32Tick);       
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_FSP);
        return;
    }
 
    if (0 == IsWaitDisp)
    {
        pstLogicFs->s32DispState = FS_DISP_STATE_NOT_USED;
        pstLogicFs->pstDispOutFs->DispState = FS_DISP_STATE_NOT_USED;
    }
    else
    {
        pstLogicFs->s32DispState = FS_DISP_STATE_WAIT_DISP;
        pstLogicFs->pstDispOutFs->DispState = FS_DISP_STATE_WAIT_DISP;
    }

    if (0 == IsWaitDisp)
    {
        pstLogicFs->pstDispOutFs = NULL;
    }
    
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_FSP);

    return;
}

/***********************************************************************
    获取逻辑帧是否等待显示
 ***********************************************************************/
SINT32  FSP_GetDisplay ( SINT32 InstID, SINT32 LogicFrameID )
{   
    FSP_LOGIC_FS_S *pstLogicFs;
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");
   
    pstLogicFs = &pstInst->stLogicFs[LogicFrameID];
    
    return pstLogicFs->s32DispState;
}

/***********************************************************************
    设置物理帧存的存储方式(按帧存储/按场存储)
 ***********************************************************************/
SINT32  FSP_SetStoreType( SINT32 InstID, FSP_PHY_FS_TYPE_E ePhyFsType, SINT32 PhyFsID, FSP_PHY_FS_STORE_TYPE_E eStoreType)
{
    SINT32 Ret = FSP_ERR;
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");

    if (FSP_PHY_FS_TYPE_DECODE == ePhyFsType)
    {
        if (PhyFsID < pstInst->s32DecFsNum)
        {
            pstInst->stDecFs[PhyFsID].eStoreType = eStoreType;
            Ret = FSP_OK;
        }
    }
    else if (FSP_PHY_FS_TYPE_DISPLAY == ePhyFsType)
    {
        if (PhyFsID < pstInst->s32DispFsNum)
        {
            pstInst->stDispFs[PhyFsID].eStoreType = eStoreType;
            Ret = FSP_OK;
        }
    }
    
    return Ret;
}

/***********************************************************************
    获取物理帧存的存储方式(按帧存储/按场存储)
 ***********************************************************************/
FSP_PHY_FS_STORE_TYPE_E  FSP_GetStoreType( SINT32 InstID, FSP_PHY_FS_TYPE_E ePhyFsType, SINT32 PhyFsID)
{
    FSP_PHY_FS_STORE_TYPE_E eStoreType = FSP_PHY_FS_STORE_TYPE_BUTT;   
    FSP_INST_S *pstInst = s_pFspInst[InstID]; 

    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");

    if (FSP_PHY_FS_TYPE_DECODE == ePhyFsType)
    {
        if (PhyFsID < pstInst->s32DecFsNum)
        {
            eStoreType = pstInst->stDecFs[PhyFsID].eStoreType;
        }
    }
    else if (FSP_PHY_FS_TYPE_DISPLAY == ePhyFsType)
    {
        if (PhyFsID < pstInst->s32DispFsNum)
        {
            eStoreType = pstInst->stDispFs[PhyFsID].eStoreType;
        }
    }

    return eStoreType;
}



/***********************************************************************
    清除逻辑帧
    如果要刻意丢弃一个已经申请到的逻辑帧，可以分别把它设置为不解码参考，
    不待显示，不作TF参考等，但最好调用此函数，使用简单且能保证把这个逻辑
    帧上关联的资源完全释放掉
    HoldDispFs: 指示是否需要保留待显示的显示帧存，1表示如果逻辑帧内的显示
                帧存已插入显示队列则保留，否则把整个逻辑帧都清除掉。
                无论HoldDispFs为何值，当前逻辑帧的参考特性一定会被清除.
 ***********************************************************************/
VOID FSP_ClearLogicFs( SINT32 InstID, SINT32 LogicFrameID, SINT32 HoldDispFs)
{
    FSP_LOGIC_FS_S *pstLogic;
    FSP_INST_S *pstInst = s_pFspInst[InstID];

    if ((InstID>=0 && InstID < MAX_CHAN_NUM) && (LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM) && NULL != s_pFspInst[InstID])
    {
        FSP_SetRef(InstID, LogicFrameID, 0);
        pstLogic = &pstInst->stLogicFs[LogicFrameID];
        
        if (FS_DISP_STATE_WAIT_DISP != pstLogic->s32DispState)
        {
            FSP_SetDisplay(InstID, LogicFrameID, 0);
        }
    }

    return ;
}


/***********************************************************************
    获取逻辑帧
 ***********************************************************************/
FSP_LOGIC_FS_S*  FSP_GetLogicFs( SINT32 InstID, SINT32 LogicFrameID)
{
    FSP_LOGIC_FS_S *pstLogicFs;
    
    if ((InstID>=0 && InstID < MAX_CHAN_NUM) && (LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM) && NULL != s_pFspInst[InstID])
    {        
        pstLogicFs = &s_pFspInst[InstID]->stLogicFs[LogicFrameID];
        
        return (pstLogicFs);
    }

    return NULL;
}

/***********************************************************************
    获取逻辑帧的输出图像(指向IMAGE结构体的指针)
 ***********************************************************************/
IMAGE*  FSP_GetFsImagePtr( SINT32 InstID, SINT32 LogicFrameID)
{
    FSP_LOGIC_FS_S *pstLogicFs;
    
    if ((InstID>=0 && InstID < MAX_CHAN_NUM) && (LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM) && NULL != s_pFspInst[InstID])
    {      
        pstLogicFs = &s_pFspInst[InstID]->stLogicFs[LogicFrameID];
           
        return (&pstLogicFs->stDispImg);
    }

    return NULL;
}


/***********************************************************************
    获取解码物理帧存
 ***********************************************************************/
FSP_PHY_FS_S*  FSP_GetDecPhyFs( SINT32 InstID, SINT32 LogicFrameID)
{
    FSP_LOGIC_FS_S *pstLogicFs;
    
    if ((InstID>=0 && InstID < MAX_CHAN_NUM) && (LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM) && NULL != s_pFspInst[InstID])
    {  
        pstLogicFs = &s_pFspInst[InstID]->stLogicFs[LogicFrameID];
           
        return (pstLogicFs->pstDecodeFs);
    }

    return NULL;
}


/***********************************************************************
    获取输出物理帧存
 ***********************************************************************/
FSP_PHY_FS_S*  FSP_GetDispPhyFs( SINT32 InstID, SINT32 LogicFrameID)
{
    FSP_LOGIC_FS_S *pstLogicFs;
    
    if ((InstID>=0 && InstID < MAX_CHAN_NUM) && (LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM) && NULL != s_pFspInst[InstID])
    {  
        pstLogicFs = &s_pFspInst[InstID]->stLogicFs[LogicFrameID];
        return (pstLogicFs->pstDispOutFs);
    }
	
    return NULL;
}


/***********************************************************************
    获取PMV地址
 ***********************************************************************/
UADDR FSP_GetPmvAddr( SINT32 InstID, SINT32 LogicFrameID )
{
    FSP_LOGIC_FS_S *pstLogicFs;
    
    if ((InstID>=0 && InstID < MAX_CHAN_NUM) && (LogicFrameID>=0 && LogicFrameID < MAX_FRAME_NUM) && NULL != s_pFspInst[InstID])
    {  
        pstLogicFs = &s_pFspInst[InstID]->stLogicFs[LogicFrameID];
        return (pstLogicFs->PmvAddr);
    }

    return 0;
}

/***********************************************************************
    获取DecFs地址表
    264协议用地址表+ID的方式给逻辑配置地址信息，所以需要获取解码帧存地址表
 ***********************************************************************/
VOID  FSP_GetDecFsAddrTab( SINT32 InstID, SINT32 *DecFsNum, SINT32 *DecFsAddrTab ,SINT32 *LineNumAddrTab)
{
    FSP_PHY_FS_S *pstDecFs;
    SINT32 i;
    
    FSP_ASSERT(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");	
    FSP_ASSERT(DecFsAddrTab != NULL, "DecFsAddrTab is NULL\n");
    FSP_ASSERT(DecFsNum != NULL, "DecFsNum is NULL\n");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");
    
    *DecFsNum = s_pFspInst[InstID]->s32DecFsNum;
    pstDecFs = &s_pFspInst[InstID]->stDecFs[0];
    for (i = 0; i < *DecFsNum; i++)
    {
        DecFsAddrTab[i] = pstDecFs[i].PhyAddr;
    #ifdef VFMW_MODULE_LOWDLY_SUPPORT
        LineNumAddrTab[i] = pstDecFs[i].LineNumAddr;
    #endif
    }

    return;
}


/***********************************************************************
    获取PMV地址表
    264协议用地址表+ID的方式给逻辑配置PMV地址信息，所以需要获取PMV地址表
 ***********************************************************************/
VOID  FSP_GetPmvAddrTab( SINT32 InstID, SINT32 *PmvNum, SINT32 *PmvAddrTab )
{
    SINT32 i;
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    FSP_ASSERT(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");	
    FSP_ASSERT(PmvAddrTab != NULL, "PmvAddrTab is NULL\n");
    FSP_ASSERT(PmvNum != NULL, "PmvNum is NULL\n");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");
    
    *PmvNum = pstInst->s32PmvNum;
    for (i = 0; i < pstInst->s32PmvNum; i++)
    {
        PmvAddrTab[i] = pstInst->PmvAddr[i];
    }

    return;
}

VOID  FSP_GetInstInfo( SINT32 InstID, FSP_INST_INFO_S *pFspInstInfo )
{
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");
   
    pFspInstInfo->s32DecFsNum  = pstInst->s32DecFsNum;
    pFspInstInfo->s32DecFsSize = pstInst->stDecFs[1].PhyAddr - pstInst->stDecFs[0].PhyAddr;
    pFspInstInfo->s32DispFsNum = pstInst->s32DispFsNum;
    pFspInstInfo->s32TfFsNum   = pstInst->s32TfFsNum;
    pFspInstInfo->s32InstID    = pstInst->s32InstID;	
    pFspInstInfo->s32PmvNum    = pstInst->s32PmvNum;	
    memcpy(&pFspInstInfo->stDecFs[0], &pstInst->stDecFs[0], sizeof(FSP_PHY_FS_S)*MAX_FRAME_NUM);
 
    return;
}

SINT32  FSP_GetLogicIdByPhyAddr( SINT32 InstID, UADDR PhyAddr)
{
    SINT32 i;
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");

    for (i=0; i<MAX_FRAME_NUM; i++)
    {
        if (pstInst->stLogicFs[i].pstDecodeFs == NULL)
        {
            continue;
        }
        if (PhyAddr == pstInst->stLogicFs[i].pstDecodeFs->PhyAddr)
        {
            return i;
        }
    }
        
    return -1;
}

/***********************************************************************
    打印FSP内部状态
    用于实时运行时，利用特定命令探测FSP内部状态
 ***********************************************************************/
VOID FSP_PrintContext(SINT32 InstID)
{
    SINT32 i;
    FSP_INST_S *pstInst;
    FSP_PHY_FS_S *pstPhy;
    FSP_LOGIC_FS_S *pstLogic;
    
    FSP_ASSERT(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT(NULL != s_pFspInst[InstID], "fsp is not inited");

    pstInst = s_pFspInst[InstID];    
    if (NULL == pstInst)
    {
        dprint(PRN_FATAL,"%s s_pFspInst[%d]=NULL\n", __func__, InstID);
        return;
    }

    dprint(PRN_FATAL,"FSP CONTEXT:\n");
    dprint(PRN_FATAL,"%-35s :%d\n", "FspInstState",      pstInst->eFspInstState);
    dprint(PRN_FATAL,"%-35s :%d\n", "DecFsWidth",        pstInst->stInstCfg.s32DecFsWidth);
    dprint(PRN_FATAL,"%-35s :%d\n", "DecFsHeight",       pstInst->stInstCfg.s32DecFsHeight);
    dprint(PRN_FATAL,"%-35s :%d\n", "DispFsWidth",       pstInst->stInstCfg.s32DispFsWidth);
    dprint(PRN_FATAL,"%-35s :%d\n", "DispFsHeight",      pstInst->stInstCfg.s32DispFsHeight);
    dprint(PRN_FATAL,"%-35s :%d\n", "ExpectedDecFsNum",  pstInst->stInstCfg.s32ExpectedDecFsNum);
    dprint(PRN_FATAL,"%-35s :%d\n", "ExpectedDispFsNum", pstInst->stInstCfg.s32ExpectedDispFsNum);
    dprint(PRN_FATAL,"%-35s :%d\n", "ExpectedPmvNum",    pstInst->stInstCfg.s32ExpectedPmvNum);
    dprint(PRN_FATAL,"%-35s :%d\n", "DecFsNum",          pstInst->s32DecFsNum);
    dprint(PRN_FATAL,"%-35s :%d\n", "DispFsNum",         pstInst->s32DispFsNum);
    dprint(PRN_FATAL,"%-35s :%d\n", "PmvNum",            pstInst->s32PmvNum);

    dprint(PRN_FATAL,"logic fs: %d\n", MAX_FRAME_NUM);
    for (i = 0; i < MAX_FRAME_NUM; i++)
    {
        pstLogic = &pstInst->stLogicFs[i];
        if ((i != 0) && ((i&7) == 0) )
        {
            dprint(PRN_FATAL,"\n");
        }
        dprint(PRN_FATAL,"%d%d ", pstLogic->s32IsRef, pstLogic->s32DispState);
    }
    dprint(PRN_FATAL,"\ndec fs: %d\n", pstInst->s32DecFsNum);
    for (i = 0; i < pstInst->s32DecFsNum; i++)
    {
        pstPhy = &pstInst->stDecFs[i];
        if ((i != 0) && ((i&7) == 0) )
        {
            dprint(PRN_FATAL,"\n");
        }
        dprint(PRN_FATAL,"%d%d ", pstPhy->IsDecRef, pstPhy->DispState);
    }
    dprint(PRN_FATAL,"\ndisp fs: %d\n", pstInst->s32DispFsNum);
    for (i = 0; i < pstInst->s32DispFsNum; i++)
    {
        pstPhy = &pstInst->stDispFs[i];
        if ((i != 0) && ((i&7) == 0) )
        {
            dprint(PRN_FATAL,"\n");
        }
        dprint(PRN_FATAL,"%d%d ", pstPhy->IsDecRef, pstPhy->DispState);
    }
    dprint(PRN_FATAL,"\npmv: %d\n", pstInst->s32PmvNum);
    for (i = 0; i < pstInst->s32PmvNum; i++)
    {
        if ((i != 0) && ((i&15) == 0) )
        {
            dprint(PRN_FATAL,"\n");
        }
        dprint(PRN_FATAL,"%d ", pstInst->IsPmvInUse[i]);
    }
    dprint(PRN_FATAL,"\n\n");

    return;
}


/***********************************************************************
    获取空闲逻辑帧存ID
    参考帧复位时用
 ***********************************************************************/
SINT32 FSP_GetNullLogicFs(SINT32 InstID)
{
    SINT32 i;
    SINT32 ret_id = 0;
    
    FSP_INST_S *pstInst = s_pFspInst[InstID];
    
    for (i=MAX_FRAME_NUM-1; i>=0; i--)
    {
        if (FS_DISP_STATE_NOT_USED == pstInst->stLogicFs[i].s32DispState)
        {
            ret_id = i;
            break;
        }
    }
    
    pstInst->stLogicFs[ret_id].pstDecodeFs = NULL;
    pstInst->stLogicFs[ret_id].pstDispOutFs = NULL;
    
    return ret_id;
}

/***********************************************************************
    查询是否有帧存上限递增空间
 ***********************************************************************/
SINT32 FSP_GetTotalValidFsNum(SINT32 InstID)
{     
    FSP_ASSERT_RET(InstID>=0 && InstID < MAX_CHAN_NUM, "InstID out of range");
    FSP_ASSERT_RET(NULL != s_pFspInst[InstID], "fsp is not inited");
 
    return s_pFspInst[InstID]->s8TotalValidFsNum;
}


