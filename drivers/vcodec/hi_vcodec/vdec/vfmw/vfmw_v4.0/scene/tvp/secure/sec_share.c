
#include "sec_share.h"
#include "public.h"
#include "vfmw_ctrl.h"
#include "tvp_adapter.h"


/*======================================================================*/
/*   Local value                                                        */
/*======================================================================*/
/* SECURE MARK */
SHARE_EVENT_ARRAY_S  *g_pEventList   = NULL; //share callback buffer
SHARE_RAW_ARRAY_S    *g_pStreamList  = NULL; //share stream   buffer
SHARE_EXTBUF_ARRAY_S *g_pExtBufArray = NULL; //share ext buffer description array


/*======================================================================*/
/*   Extern value                                                       */
/*======================================================================*/
extern FSP_INST_S   *s_pFspInst[MAX_CHAN_NUM];
extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];
extern SM_IIS_S      s_SmIIS;
extern SINT32        g_CurProcChan;
extern SINT32        g_StopDec;


/************************************************************************
    Share Zone Init
*************************************************************************/
SINT32 SEC_ShareZone_Init(UINT32 Share)
{    
    SINT32 ret = VDEC_ERR;
    SHARE_DATA_S *pShare = NULL;
       
    pShare = (SHARE_DATA_S *)SOS_MapShare(Share, sizeof(SHARE_DATA_S), 1, 1);
    if (pShare == NULL)
    {
        dprint(PRN_ALWS, "%s %d, map_section_entry failed!\n", __func__,__LINE__);
        return VDEC_ERR;
    }
    
    dprint(PRN_ALWS, "%s sec_print_word=%x, event_report_list=%x, stream_data_list=%x\n", __func__, pShare->sec_print_word, pShare->event_report_list, pShare->stream_data_list);
    
    // sync g_PrintEnable
    SEC_WriteProc(0, pShare->sec_print_word);

    // set dts info
    ret = VFMW_SetDtsConfig(&pShare->dts_data);
    if (ret != VDEC_OK)
    {
        dprint(PRN_ERROR, "%s VFMW_SetDtsConfig failed!\n", __func__);
        ret = VDEC_ERR;
        goto EXIT;
    }

    // map callback list 
    g_pEventList = (SHARE_EVENT_ARRAY_S *)SOS_MapShare(pShare->event_report_list, sizeof(SHARE_EVENT_ARRAY_S), 1, 1);
    if (NULL == g_pEventList)
    {
        dprint(PRN_ERROR, "%s map g_pEventList failed!\n", __func__);
        ret = VDEC_ERR;
        goto EXIT;
    }

    // map stream data list 
    g_pStreamList = (SHARE_RAW_ARRAY_S *)SOS_MapShare(pShare->stream_data_list, sizeof(SHARE_RAW_ARRAY_S)*MAX_CHAN_NUM, 1, 1);
    if (NULL == g_pStreamList)
    {
        dprint(PRN_ERROR, "%s map g_pStreamList failed!\n", __func__);
        ret = VDEC_ERR;
        SOS_UnMapShare((VOID *)g_pEventList, sizeof(SHARE_EVENT_ARRAY_S));
        goto EXIT;
    }
    
    // map ext buffer table 
    g_pExtBufArray = (SHARE_EXTBUF_ARRAY_S *)SOS_MapShare(pShare->ext_buffer_array, sizeof(SHARE_EXTBUF_ARRAY_S)*MAX_CHAN_NUM, 1, 1);
    if (NULL == g_pExtBufArray)
    {
        dprint(PRN_ERROR, "%s map g_pExtBuffer failed!\n", __func__);
        ret = VDEC_ERR;
        SOS_UnMapShare((VOID *)g_pEventList,  sizeof(SHARE_EVENT_ARRAY_S));
        SOS_UnMapShare((VOID *)g_pStreamList, sizeof(SHARE_RAW_ARRAY_S)*MAX_CHAN_NUM);
        goto EXIT;
    }

    ret = VDEC_OK;
    
EXIT:
    SOS_UnMapShare((VOID *)pShare, sizeof(SHARE_DATA_S));
    
    return ret;
}

/************************************************************************
    Share Zone Deinit
*************************************************************************/
VOID SEC_ShareZone_Exit(VOID)
{    
    SINT32 ret = VDEC_ERR;
    
    if (g_pEventList != NULL)
    {
        SOS_UnMapShare((VOID *)g_pEventList,  sizeof(SHARE_EVENT_ARRAY_S));
        g_pEventList = NULL;
    }
    
    if (g_pStreamList != NULL)
    {
        SOS_UnMapShare((VOID *)g_pStreamList, sizeof(SHARE_RAW_ARRAY_S)*MAX_CHAN_NUM);
        g_pStreamList = NULL;
    }
    
    if (g_pExtBufArray != NULL)
    {
        SOS_UnMapShare((VOID *)g_pExtBufArray,  sizeof(SHARE_EXTBUF_ARRAY_S)*MAX_CHAN_NUM);
        g_pExtBufArray = NULL;
    }

    return;
}

/************************************************************************
    Share Zone Event Report
*************************************************************************/
SINT32 SEC_EventReport(SINT32 ChanID, SINT32 Type, VOID* pArgs, UINT32 Len)
{
    VDEC_ADAPTER_TYPE_E eType;
    
    if (ChanID < 0 || ChanID >= MAX_CHAN_NUM)
    {
        dprint(PRN_FATAL, "%s Chanid %d invalid!\n", __func__, ChanID);
        return VDEC_ERR;
    }

    if (NULL == s_pstVfmwChan[ChanID])
    {
        dprint(PRN_FATAL, "%s s_pstVfmwChan[%d] = NULL!\n", __func__, ChanID);
        return VDEC_ERR;
    }

    eType = s_pstVfmwChan[ChanID]->eAdapterType;

    // 安全侧上报消息过滤，只上报会处理的消息，防止队列溢出
    // 注意，如新增消息处理，这里需要同步放开  y00226912
    if (ADAPTER_TYPE_OMXVDEC == eType)
    {
        if (eType != EVNT_NEED_ARRANGE && eType != EVNT_NEED_ARRANGE_L
         && eType != EVNT_NEW_IMAGE    && eType != EVNT_LAST_FRAME)
        {
            return VDEC_OK;
        }
    }

    if (NULL != g_pEventList)
    {
        if (((g_pEventList->Head+1) % MAX_EVENT_NUM) != g_pEventList->Tail)
        {
            g_pEventList->Message[g_pEventList->Head].IsValid = 1;
            g_pEventList->Message[g_pEventList->Head].ChanID  = ChanID;
            g_pEventList->Message[g_pEventList->Head].Type    = Type;

            memset(g_pEventList->Message[g_pEventList->Head].para, 0, MAX_PARA_SIZE);
            if (NULL != pArgs)
            {
                if (Len > MAX_PARA_SIZE)
                {
                    dprint(PRN_FATAL, "Type(%d): Length(%d) > MAX_PARA_SIZE(%d)\n", Type, Len, MAX_PARA_SIZE);
                    return VDEC_ERR;
                }
                else
                {
                    memcpy(g_pEventList->Message[g_pEventList->Head].para, pArgs, Len*sizeof(UINT8));               
                }
            }
            g_pEventList->Head = (g_pEventList->Head+1) % MAX_EVENT_NUM; 
            return VDEC_OK;
        }
        else
        {
            dprint(PRN_FATAL, "Type(%d): The ARRAY OVERFLOW!\n", Type);
            return VDEC_ERR;
        }
    }
    
    return VDEC_OK;
}


/************************************************************************
    Share Zone Read Raw Stream
*************************************************************************/
SINT32 SEC_ReadRawStream(SINT32 InstID, STREAM_DATA_S *pRawPacket)
{	
    UINT32 cnt = 0;
    static UINT8 test = 0;
    SINT32 ret = VDEC_ERR;
    
    if (NULL == g_pStreamList)
    {
        dprint(PRN_FATAL, "%s FATAL: g_pStreamList = NULL\n", __func__);
        return VDEC_ERR;    
    }
    if (0 == test)
    {
        dprint(PRN_FATAL, "First Check Read g_pStreamList[%d]...\n",InstID);
        dprint(PRN_FATAL, "InstID = %d Head_S = %d, Head_NS = %d\n",InstID, g_pStreamList[InstID].Head_S,g_pStreamList[InstID].Head_NS);
        dprint(PRN_FATAL, "Check Read g_pStreamList[%d] Success!\n",InstID);
        test = 1;
    }
    
    if(g_pStreamList[InstID].Head_S != g_pStreamList[InstID].Head_NS)
    {
        memcpy(pRawPacket, &(g_pStreamList[InstID].RawPacket[g_pStreamList[InstID].Head_S]), sizeof(STREAM_DATA_S));
        pRawPacket->VirAddr = SOS_MapShare(pRawPacket->PhyAddr, pRawPacket->Length, 0, 0);
        if (NULL == pRawPacket->VirAddr)
        {
            dprint(PRN_FATAL, "%s SOS_MapShare(phy = %x) Failed!\n", __func__, pRawPacket->PhyAddr);
            ret = VDEC_ERR;
        }
        else
        {
            g_pStreamList[InstID].Head_S = (g_pStreamList[InstID].Head_S+1) % MAX_RAW_NUM;
            ret = VDEC_OK;
            if (1 == test)
            {
                dprint(PRN_FATAL, "\nCheck first 10 bytes:\n");
                for (cnt=0; cnt<10; cnt++)
                {
                    dprint(PRN_FATAL, "%x ", *(pRawPacket->VirAddr+cnt));
                }
                dprint(PRN_FATAL, "\n\n");
                test = 2;
            }
        }
    }
    else
    {
        ret = VDEC_ERR;
    }
    
    return ret;
}


/************************************************************************
    Share Zone Release Raw Stream
*************************************************************************/
SINT32 SEC_ReleaseRawStream(SINT32 InstID, STREAM_DATA_S *pRawPacket)
{
    SINT32 ret = FMW_ERR_SCD;
    
    if(g_pStreamList[InstID].Tail_S != g_pStreamList[InstID].Head_S)
    {
        SOS_UnMapShare((VOID *)pRawPacket->VirAddr, pRawPacket->Length);
        g_pStreamList[InstID].Tail_S = (g_pStreamList[InstID].Tail_S+1) % MAX_RAW_NUM;
        ret = FMW_OK;
    }
    else
    {
        ret = FMW_ERR_SCD;
    }
    
    return ret;
}

/************************************************************************
    Share Zone Control Adjust
*************************************************************************/
SINT32 SEC_ControlAdjust(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    SINT32  ret    = VDEC_OK;
	SINT32 *p32    = NULL;
	UINT64 *pulong = NULL;
    VDEC_CHAN_OPTION_S   *pData = NULL;
    STREAM_INTF_S        *pIntf = NULL;
    
    switch (eCmdID)
    {
        case VDEC_CID_CREATE_CHAN_WITH_OPTION:
        case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
    		pulong = (UINT64 *)pArgs;
            dprint(PRN_ALWS, "%s %d eCmdID %d: pulong[0] = %x, pulong[1] = %x\n", __func__, __LINE__, eCmdID, pulong[0], pulong[1]);
            pData  = (VDEC_CHAN_OPTION_S *)SOS_MapShare((ULONG)(pulong[1]), sizeof(VDEC_CHAN_OPTION_S), 1, 1);
            if (NULL == pData)
            {
                dprint(PRN_FATAL, "%s eCmdID %d SOS_MapShare Failed!\n", __func__, eCmdID);
                ret = VDEC_ERR;
            }
            else
            {
                *(VDEC_CHAN_OPTION_S **)(pulong + 1) = pData;
            }
            dprint(PRN_ALWS, "%s %d eCmdID %d: pulong[0] = %x, pulong[1] = %x\n", __func__, __LINE__, eCmdID, pulong[0], pulong[1]);
            break;
            
        case VDEC_CID_SET_STREAM_INTF:
            pIntf = (STREAM_INTF_S *)pArgs;
            pIntf->read_stream    = SEC_ReadRawStream;
            pIntf->release_stream = SEC_ReleaseRawStream;
            break;

        default:
            break;
    }

    return ret;
}

/************************************************************************
    Share Zone Control Converse
*************************************************************************/
SINT32 SEC_ControlConverse(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    SINT32  ret     = VDEC_OK;
	SINT32 *p32     = NULL;
	UINT64 *pulong  = NULL;
    VDEC_CHAN_OPTION_S *pOption = NULL;
    
    switch (eCmdID)
    {
        case VDEC_CID_CREATE_CHAN_WITH_OPTION:
        case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
    		pulong = (UINT64 *)pArgs;
            pOption = *(VDEC_CHAN_OPTION_S **)(pulong + 1);
            SOS_UnMapShare(pOption, sizeof(VDEC_CHAN_OPTION_S));
            dprint(PRN_ALWS, "%s %d eCmdID %d pOption = %x\n", __func__, __LINE__, eCmdID, pOption);
            break;
            
        default:
            break;
    }

    return ret;
}

/************************************************************************
    Share Zone Check if Specofic Buffer Usable
*************************************************************************/
SINT32 SEC_Is_Buffer_Usable(SINT32 ChanID, UADDR PhyAddr)
{
    UINT32 i;
    SINT32 usable = 0; // init not found
    SHARE_EXTBUF_ARRAY_S *pArray = NULL;

    if (ChanID < 0 || ChanID >= MAX_CHAN_NUM)
    {
        dprint(PRN_ERROR, "%s ChanID %d invalid!\n", __func__, ChanID);
        return VDEC_ERR;
    }

    if (NULL == g_pExtBufArray)
    {
        dprint(PRN_ERROR, "%s g_pExtBuffer = NULL!\n", __func__, ChanID);
        return VDEC_ERR;
    }

    pArray = &(g_pExtBufArray[ChanID]);

    for (i=0; i<MAX_FRAME_NUM; i++)
    {
        if (PhyAddr == pArray->PhyAddr[i])
        {
            if (EXTBUF_READY == pArray->State[i])
            {
                usable = 1;  // specific buffer usable
            }
            break;
        }
    }

    return usable;
}

/************************************************************************
    Share Zone Set Specofic Buffer Taken
*************************************************************************/
SINT32 SEC_Set_Buffer_Taken(SINT32 ChanID, UADDR PhyAddr)
{
    UINT32 i;
    SHARE_EXTBUF_ARRAY_S *pArray = NULL;

    if (ChanID < 0 || ChanID >= MAX_CHAN_NUM)
    {
        dprint(PRN_ERROR, "%s ChanID %d invalid!\n", __func__, ChanID);
        return VDEC_ERR;
    }

    if (NULL == g_pExtBufArray)
    {
        dprint(PRN_ERROR, "%s g_pExtBuffer = NULL!\n", __func__, ChanID);
        return VDEC_ERR;
    }
        
    pArray = &(g_pExtBufArray[ChanID]);
    
    for (i=0; i<MAX_FRAME_NUM; i++)
    {
        if (PhyAddr == pArray->PhyAddr[i])
        {
            if (EXTBUF_READY != pArray->State[i])
            {
                dprint(PRN_ERROR, "%s Chan %d ExtBuf %x state %d confused!\n", __func__, ChanID, pArray->PhyAddr[i], pArray->State[i]);
            }
            pArray->State[i] = EXTBUF_TAKEN;  // set buffer taken to avoid reuse.
            return VDEC_OK;
        }
    }

    return VDEC_ERR;
}

/************************************************************************
    Share Zone Inquire Buffer State
*************************************************************************/
SINT32 SEC_Buffer_Handler(SINT32 ChanID, SINT32 Type, VOID *pArgs)
{
    SINT32 ret = VDEC_ERR;
    UADDR  phy_addr = 0;
    
    switch (Type)
    {
        case BC_CHK_BUF:
        {
            if (NULL == pArgs)
            {
                dprint(PRN_ERROR, "%s type %d, pArgs = NULL\n", __func__, Type);
                return VDEC_ERR;
            }
            phy_addr = *(UADDR *)pArgs;
            ret = SEC_Is_Buffer_Usable(ChanID, phy_addr);
            break;
        }
        
        case BC_REPORT_BUF:
        {
            if (NULL == pArgs)
            {
                dprint(PRN_ERROR, "%s type %d, pArgs = NULL\n", __func__, Type);
                return VDEC_ERR;
            }
            phy_addr = *(UADDR *)pArgs;
            ret = SEC_Set_Buffer_Taken(ChanID, phy_addr);
            break;
        }
        
        default:
        {
            dprint(PRN_ERROR, "%s unsupport type %d\n", __func__, Type);
            break;
        }
    }

    return ret;
}

/***********************************************************************
   Share Zone Read Proc
 ***********************************************************************/
SINT32 SEC_ReadProc(SINT8 *Page, SINT32 Count)
{
	SINT32 len = 0;
    SINT32 i = 0;
    SINT32 ChanID = 0;
    SINT32 VdhId = 0;
    FSP_INST_S     *pFsp         = NULL;
    VFMW_CHAN_S    *pChan        = NULL;
	SM_INSTANCE_S  *pScdInst     = NULL;
    IMAGE_VO_QUEUE *pstDecQue    = NULL;
    SHARE_EXTBUF_ARRAY_S *pArray = NULL;
    SINT32 RefNum=0, ReadNum=0, NewNum=0;
    SINT32 QueHist=0, QueHead=0, QueTail=0;
    SINT32 RawNum=0, RawSize=0, SegNum=0, SegSize=0;
    
    extern FSP_INST_S* s_pFspInst[MAX_CHAN_NUM];
    
    ChanID = g_CurProcChan;
    if (ChanID < 0 || ChanID >= MAX_CHAN_NUM)
    {
        len += snprintf(Page+len, Count-len, "ChanID out of range(0, %d)\n", ChanID, MAX_CHAN_NUM);
        return len;;
    }

    /* 1. global info */
    len += snprintf(Page+len, Count-len, "===================== Secure Vfmw Info =====================\n"); 
    len += snprintf(Page+len, Count-len, "CurChan            :%d      \n", ChanID);
    len += snprintf(Page+len, Count-len, "Stream Period      :%d\n",   g_TraceBsPeriod);
    len += snprintf(Page+len, Count-len, "Frame  Period      :%d\n",   g_TraceFramePeriod);
    len += snprintf(Page+len, Count-len, "Image  Period      :%d\n",   g_TraceImgPeriod);
    len += snprintf(Page+len, Count-len, "Print Enable Word  :0x%x\n", g_PrintEnable);
    len += snprintf(Page+len, Count-len, "\n");

    /* 2. SCD info */
    len += snprintf(Page+len, Count-len, "------------------------- Scd Info -------------------------\n");
    len += snprintf(Page+len, Count-len, "IsScdOpen          :%d      | SecHwMemAddr          :0x%x\n", s_SmIIS.IsScdDrvOpen, s_SmIIS.ScdDrvMem.HwMemAddr);
    len += snprintf(Page+len, Count-len, "Scd State          :%d      | SecHwMemSize          :%d\n",   s_SmIIS.SCDState, s_SmIIS.ScdDrvMem.HwMemSize);
    len += snprintf(Page+len, Count-len, "\n");
        
	pScdInst = s_SmIIS.pSmInstArray[ChanID];
    if(pScdInst != NULL)
    {
       	GetRawStreamSize(&pScdInst->RawPacketArray, &RawSize);
      	GetRawStreamNum(&pScdInst->RawPacketArray, &RawNum);
       	GetSegStreamSize(&pScdInst->StreamSegArray, &SegSize);
        GetSegStreamNum(&pScdInst->StreamSegArray, &SegNum);

        len += snprintf(Page+len, Count-len, "Mode               :%d      | Config BufPhyAddr     :0x%x\n", pScdInst->Mode, pScdInst->Config.BufPhyAddr);
        len += snprintf(Page+len, Count-len, "Last Pts           :%d      | Config BufSize        :%d\n", pScdInst->LastPts, pScdInst->Config.BufSize);
        len += snprintf(Page+len, Count-len, "Raw Total Size     :%d      | Seg Read  Addr        :0x%x\n", RawSize, pScdInst->StreamSegArray.SegBufReadAddr);
        len += snprintf(Page+len, Count-len, "Raw Total Num      :%d      | Seg Write Addr        :0x%x\n", RawNum, pScdInst->StreamSegArray.SegBufWriteAddr);
        len += snprintf(Page+len, Count-len, "Seg Total Size     :%d      | IsCounting            :%d\n", SegSize, pScdInst->IsCounting);
        len += snprintf(Page+len, Count-len, "Seg Total Num      :%d      | Actual Bitrate        :%d\n", SegNum, pScdInst->BitRate);
        len += snprintf(Page+len, Count-len, "\n");
    }

    /* 3. VDH info */
    pChan = s_pstVfmwChan[ChanID];
    if(pChan != NULL)
    {
        VdhId = g_ChanCtx.ChanDecByVdhPlusOne[ChanID] - 1;
        VCTRL_GetChanImgNum(ChanID, &RefNum, &ReadNum, &NewNum);
        if(NULL != (pstDecQue = VCTRL_GetChanVoQue(ChanID)))
        {
            QueHist = pstDecQue->history;
            QueHead = pstDecQue->head;
            QueTail = pstDecQue->tail;
        }
        len += snprintf(Page+len, Count-len, "------------------------- Vdh Info -------------------------\n");       
        len += snprintf(Page+len, Count-len, "VdhId              :%d      | ChanMemVDH PhyAddr    :0x%x\n", VdhId, pChan->stChanMem_vdh.PhyAddr);
        len += snprintf(Page+len, Count-len, "IsOpen             :%d      | ChanMemVDH Size       :%d\n", pChan->s32IsOpen, pChan->stChanMem_vdh.Length);
        len += snprintf(Page+len, Count-len, "IsRun              :%d      | Vdm MemAddr           :0x%x\n", pChan->s32IsRun, pChan->s32VdmChanMemAddr);
        len += snprintf(Page+len, Count-len, "Priority           :%d      | Vdm MemSize           :%d\n", pChan->s32Priority, pChan->s32VdmChanMemSize);
        len += snprintf(Page+len, Count-len, "CapLevel           :%d      | Last Frame State      :%d\n", pChan->eChanCapLevel, pChan->eLastFrameState);
        len += snprintf(Page+len, Count-len, "Standard           :%d      | DecQue Detail         :(%d,%d,%d)\n", pChan->eVidStd, QueHist, QueHead, QueTail);
        len += snprintf(Page+len, Count-len, "ChanErrThr         :%d      | Mp4 Skip Num          :%d\n", pChan->stChanCfg.s32ChanErrThr, g_VfmwChanStat[ChanID].u32SkipFind);
        len += snprintf(Page+len, Count-len, "ChanStrmOFThr      :%d      | Mp4 Skip Discarded    :%d\n", pChan->stChanCfg.s32ChanStrmOFThr, g_VfmwChanStat[ChanID].u32SkipDiscard);
        len += snprintf(Page+len, Count-len, "DecMode            :%d      | Actual DecMode        :%d\n", pChan->stChanCfg.s32DecMode, pChan->stSynExtraData.s32DecMode);
        len += snprintf(Page+len, Count-len, "DecOrderOutput     :%d      | Actual DecOrderOutput :%d\n", pChan->stChanCfg.s8DecOrderOutput, pChan->stSynExtraData.s32DecOrderOutput);
        len += snprintf(Page+len, Count-len, "SupportAllP        :%d      | Image Format          :0x%x\n", pChan->stChanCfg.s8SupportAllP, pChan->stRecentImgformat);
        len += snprintf(Page+len, Count-len, "StdExt AP          :%d      | Frame Packing Type    :0x%x\n", pChan->stChanCfg.StdExt.Vc1Ext.IsAdvProfile, pChan->stRecentImgPackingType);
        len += snprintf(Page+len, Count-len, "StdExt CodecVer    :%d      | Frame Packing Type    :0x%x\n", pChan->stChanCfg.StdExt.Vc1Ext.CodecVersion, pChan->stRecentImgPackingType);
        len += snprintf(Page+len, Count-len, "StdExt Reversed    :%d      | Actual Frame Rate     :%d.%dfps\n", pChan->stChanCfg.StdExt.Vp6Ext.bReversed, g_VfmwChanStat[ChanID].u32FrFrameRate/10,g_VfmwChanStat[ChanID].u32FrFrameRate%10);
        len += snprintf(Page+len, Count-len, "\n");
        for (i=0; i<MAX_VDH_NUM; i++)
        {
            len += snprintf(Page+len, Count-len, "VDH %d              :%d/%d/%d.%d%  KiloCycle/Period/Load\n", i, g_VfmwGlobalStat[i].u32VaVdmKiloCycle, g_VfmwGlobalStat[i].u32StatTime, 
                                                                                                            g_VfmwGlobalStat[i].u32VaVdmLoad/10,   g_VfmwGlobalStat[i].u32VaVdmLoad%10);
        }
        len += snprintf(Page+len, Count-len, "\n");
    }

    /* 4. FSP info */
    pFsp = s_pFspInst[ChanID];
    if (pFsp != NULL)
    {
        len += snprintf(Page+len, Count-len, "------------------------- Fsp Info -------------------------\n");     
        len += snprintf(Page+len, Count-len, "Fsp State          :%d     | DecFs Width           :%d\n", pFsp->eFspInstState, pFsp->stInstCfg.s32DecFsWidth);
        len += snprintf(Page+len, Count-len, "Inst Tick          :%d     | DecFs Height          :%d\n", pFsp->u32InstTick, pFsp->stInstCfg.s32DecFsHeight);
        len += snprintf(Page+len, Count-len, "Logic FsNum        :%d     | Logic PmvNum          :%d\n", MAX_FRAME_NUM, MAX_PMV_NUM);
        len += snprintf(Page+len, Count-len, "Expected DecFsNum  :%d     | Expected PmvNum       :%d\n", pFsp->stInstCfg.s32ExpectedDecFsNum, pFsp->stInstCfg.s32ExpectedPmvNum);
        len += snprintf(Page+len, Count-len, "Actual DecFsNum    :%d     | Actual PmvNum         :%d\n", pFsp->s32DecFsNum, pFsp->s32PmvNum);
        len += snprintf(Page+len, Count-len, "DecFs State:\n");
        for(i = 0; i < pFsp->s32DecFsNum; i++)
        {
            if ((i != 0) && ((i&15) == 0) )len += snprintf(Page+len, Count-len,"\n");
            len += snprintf(Page+len, Count-len, "%d%d ",pFsp->stDecFs[i].IsDecRef,pFsp->stDecFs[i].DispState);
        }
        len += snprintf(Page+len, Count-len, "\n");        
        len += snprintf(Page+len, Count-len, "Pmv State:\n");
        for(i = 0; i < pFsp->s32PmvNum; i++)
        {
            if ((i != 0) && ((i&15) == 0) )len += snprintf(Page+len, Count-len,"\n");
            len += snprintf(Page+len, Count-len, "%d  ", pFsp->IsPmvInUse[i]);
        }
        len += snprintf(Page+len, Count-len, "\n");
    }

    /* 5. EXT BUF info */
    if (g_pExtBufArray != NULL)
    {
        pArray = &(g_pExtBufArray[ChanID]);
        
        len += snprintf(Page+len, Count-len, "Total Ext Buf:\n", pArray->TotalNum);        
        for (i=0; i<MAX_FRAME_NUM; i++)
        {
            if (pArray->PhyAddr[i] != 0)
            {
                len += snprintf(Page+len, Count-len, " %d: %x %d\n", i, pArray->PhyAddr[i], pArray->State[i]);
            }
        }
    }

    len += snprintf(Page+len, Count-len, "\n");
    
	return len;
}

/***********************************************************************
   Share Zone Write Proc
 ***********************************************************************/
SINT32 SEC_WriteProc(UINT32 Option, SINT32 Value)
{
    SINT32 ChanID;
    VDEC_CHAN_CFG_S ChanCfg;
    SINT32 ret = VCTRL_OK;
    
    switch (Option)
    {
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%% 配置测试(0x000) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    case 0x000: /* 设置打印使能 */
        g_PrintEnable = Value;
        break;
 
    case 0x002: /* 设置error_thr */
        ChanID = g_CurProcChan;
        if( VCTRL_OK == VCTRL_GetChanCfg(ChanID, &ChanCfg))
        {
            ChanCfg.s32ChanErrThr = Value;
            VCTRL_ConfigChan(ChanID, &ChanCfg);
		    dprint(PRN_ALWS, "Chan %d: new ChanErrThr = %d\n", ChanID, ChanCfg.s32ChanErrThr);
        }
        else
        {
            ret = VCTRL_ERR;
		    dprint(PRN_ALWS, "Chan %d: VCTRL_GetChanCfg Failed!\n", ChanID);
        }
        break;
        
    case 0x004: /* 设置是否解码序输出 */
        ChanID = g_CurProcChan;
        if( VCTRL_OK == VCTRL_GetChanCfg(ChanID, &ChanCfg))
        {
            ChanCfg.s8DecOrderOutput = Value;
            VCTRL_ConfigChan(ChanID, &ChanCfg);
		    dprint(PRN_ALWS,"Chan %d: new DecOrderOutput = %d\n", ChanID, ChanCfg.s8DecOrderOutput);
        }
        else
        {
            ret = VCTRL_ERR;
		    dprint(PRN_ALWS, "Chan %d: VCTRL_GetChanCfg Failed!\n", ChanID);
        }
        break;
        
    case 0x005: /* 设置 I/IP/IPB模式 */
        ChanID = g_CurProcChan;
        if( VCTRL_OK == VCTRL_GetChanCfg(ChanID, &ChanCfg))
        {
            ChanCfg.s32DecMode = Value;
            VCTRL_ConfigChan(ChanID, &ChanCfg);
		    dprint(PRN_ALWS,"Chan %d: new DecMode = %d\n", ChanID, ChanCfg.s32DecMode);
        }
        else
        {
            ret = VCTRL_ERR;
		    dprint(PRN_ALWS, "Chan %d: VCTRL_GetChanCfg Failed!\n", ChanID);
        }
        break;
        
    case 0x007: /* 修改码流丢帧阈值 */
        ChanID = g_CurProcChan;
        if( VCTRL_OK == VCTRL_GetChanCfg(ChanID, &ChanCfg))
        {
            ChanCfg.s32ChanStrmOFThr = Value;
            VCTRL_ConfigChan(ChanID, &ChanCfg);
		    dprint(PRN_ALWS,"Chan %d: new StrmOFThr = %d\n", ChanID, ChanCfg.s32ChanStrmOFThr);
        }
        else
        {
            ret = VCTRL_ERR;
		    dprint(PRN_ALWS, "Chan %d: VCTRL_GetChanCfg Failed!\n", ChanID);
        }
        break;
             
    case 0x00b: /* 设置是否打开帧场自适应存储 */
		if(Value == 0 || Value == 1)
		{
		    USE_FF_APT_EN = Value;
			dprint(PRN_ALWS,"USE_FF_APT_EN = %d\n", USE_FF_APT_EN);
		}
		else
		{
            ret = VCTRL_ERR;
            dprint(PRN_ALWS,"USE_FF_APT_EN can NOT be set to %d, must be 0 or 1\n", Value);
		}
        break;
        
    case 0x00d:/*设置需要查看的通道号*/
        if (Value>=MAX_CHAN_NUM/2 && Value < MAX_CHAN_NUM)
		{
		    g_CurProcChan = Value;
            dprint(PRN_ALWS, "Pay attention to  CHANNEL : %d\n", Value);
		} 
		else 
        {
            ret = VCTRL_ERR;
            dprint(PRN_ALWS, "NO SUCH CHANNEL : %d\n", Value);
        }     
        break;
        
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%% 时序测试 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
	case 0x402:
		g_StopDec = Value;
		dprint(PRN_ALWS,"------ Trusted Decoder stop = %d ------\n", g_StopDec);
		break;
        
    /* %%%%%%%%%%%%%%%%%%%%%% 调试信息控制参数 %%%%%%%%%%%%%%%%%%%%%%%%%%%% */
	case 0x501:
		g_TraceBsPeriod = Value;
		dprint(PRN_ALWS,"------ TraceBsPeriod = %x ------\n", g_TraceBsPeriod);
		break;
        
	case 0x502:
		g_TraceFramePeriod = Value;
		dprint(PRN_ALWS,"------ TraceFramePeriod = %x ------\n", g_TraceFramePeriod);
		break;
        
	case 0x503:
		g_TraceImgPeriod = Value;
		dprint(PRN_ALWS,"------ TraceImgPeriod = %x ------\n", g_TraceImgPeriod);
		break;
        
    default:
        ret = VCTRL_ERR;
		dprint(PRN_ALWS,"Unsupport option(%d) now!\n", Option);
    }

    return ret;
}


