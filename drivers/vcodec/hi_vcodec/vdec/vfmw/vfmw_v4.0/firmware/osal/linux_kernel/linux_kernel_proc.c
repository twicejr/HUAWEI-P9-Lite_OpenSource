
#include <linux/file.h>
#include "linux_kernel_proc.h"
#include "linux_kernel_osal.h"
#include "scd_drv.h"
#include "fsp.h"
#include "vfmw_ctrl.h"

extern SINT32             extra_ref;
extern SINT32             extra_disp;
extern UINT32             extra_cmd;
extern SINT32             g_CurProcChan;
extern FSP_INST_S        *s_pFspInst[MAX_CHAN_NUM];
extern SM_IIS_S          *g_pSmIIS;
extern VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
extern DSP_STATE_E        g_DspDrvState[2];
extern UINT32             g_ResetCreateNewSave;
extern SINT8              s_VfmwSavePath[64];
extern VFMW_CHAN_S       *s_pstVfmwChan[MAX_CHAN_NUM];
extern UINT32             g_u32DFSMaxAllocTime;

#define MAX_VID_PROTOCOL_NAME  (20)
#define DEFAULT_ECHO_DEVICE_HANDLE (0)

#ifdef ENV_ARMLINUX_KERNEL
module_param(extra_ref,  int, 0000);
module_param(extra_disp, int, 0000);
module_param(extra_cmd,  int, 0000);

#ifdef HI_ADVCA_FUNCTION_RELEASE
#undef  HI_VFMW_PROC_SUPPORT
#else
#define HI_VFMW_PROC_SUPPORT
#endif

#ifdef HI_VFMW_PROC_SUPPORT

#define VFMW_PROC_NAME          "vfmw"
#define VFMW_PROC_NAME_DBG      "vfmw_dbg"
#define VFMW_PROC_NAME_DPRN     "vfmw_prn"
#define VFMW_PROC_NAME_SCD      "vfmw_scd"
#define VFMW_PROC_NAME_DEC      "vfmw_dec"
#define VFMW_PROC_NAME_LWD      "vfmw_lwd"
#define VFMW_PROC_NAME_CHN      "vfmw_chn"

void VID_STD_Enum2Str(VID_STD_E eVidStd, char *strVidStd)
{
    char *strVidstdTemp = NULL;

    switch (eVidStd)
    {
        case VFMW_H264:
            strVidstdTemp = "H264";
            break;

        case VFMW_VC1:
            strVidstdTemp = "VC1";
            break;

        case VFMW_MPEG4:
            strVidstdTemp = "MPEG4";
            break;

        case VFMW_MPEG2:
            strVidstdTemp = "MPEG2";
            break;

        case VFMW_H263:
            strVidstdTemp = "H263";
            break;

        case VFMW_DIVX3:
            strVidstdTemp = "DIVX3";
            break;

        case VFMW_AVS:
            strVidstdTemp = "AVS";
            break;

        case VFMW_JPEG:
            strVidstdTemp = "JPEG";
            break;

        case VFMW_REAL8:
            strVidstdTemp = "REAL8";
            break;

        case VFMW_REAL9:
            strVidstdTemp = "REAL9";
            break;

        case VFMW_VP6:
            strVidstdTemp = "VP6";
            break;

        case VFMW_VP6F:
            strVidstdTemp = "VP6F";
            break;

        case VFMW_VP6A:
            strVidstdTemp = "VP6A";
            break;

        case VFMW_VP8:
            strVidstdTemp = "VP8";
            break;

        case VFMW_SORENSON:
            strVidstdTemp = "SORENSON";
            break;

        case VFMW_MVC:
            strVidstdTemp = "MVC";
            break;

        case VFMW_HEVC:
            strVidstdTemp = "HEVC";
            break;

        case VFMW_RAW:
            strVidstdTemp = "RAW";
            break;

        case VFMW_USER:
            strVidstdTemp = "USER";
            break;

        case VFMW_END_RESERVED:
            strVidstdTemp = "RESERVED";
            break;

        default:
            *strVidStd = '\0';
            break;
    }

    strncpy(strVidStd, strVidstdTemp, strlen(strVidstdTemp));
    strVidStd[strlen(strVidstdTemp)] = '\0';

    return;
}

void VID_EofState_Enum2Str(LAST_FRAME_STATE_E eState, char *strState)
{
    char *strStateTemp = NULL;

    switch (eState)
    {
        case LAST_FRAME_INIT:
            strStateTemp = "BLANK";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_RECEIVE:
            strStateTemp = "RECEIVED";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_SUCCESS:
            strStateTemp = "SUCCESS";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_FAILURE:
            strStateTemp = "FAILURE";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_FRAMEID:
            strStateTemp = "FRAMEID";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        default:
            *strState = '\0';
            break;
    }

    return;
}

int vfmw_read_proc(struct seq_file *p, void *v)
{
    seq_printf(p, "=============== vfmw info =============\n");
    seq_printf(p, "%-35s :%d\n", "version num", VFMW_VERSION_NUM);

    seq_printf(p, "%-35s :%d\n", "extra_ref", extra_ref);
    seq_printf(p, "%-35s :%d\n", "extra_disp", extra_disp);
    seq_printf(p, "%-35s :%d\n", "extra_cmd", extra_cmd);

    seq_printf(p, "%-35s :%d\n", "USE_FF_APT_EN", USE_FF_APT_EN);
    seq_printf(p, "%-35s :%d\n", "ResetCreateNewSave", g_ResetCreateNewSave);

    return 0;
}

int vfmw_read_proc_dbg(struct seq_file *p, void *v)
{
    extern UADDR  TracerPhyAddr;

    seq_printf(p, "------------------------debug options--------------------------\n");

    seq_printf(p, "%-27s :%#x\n", "tracer address",             TracerPhyAddr);
    seq_printf(p, "%-27s :%s\n",  "path to save debug data",    (char *)s_VfmwSavePath);
    seq_printf(p, "%-27s :%#x\n", "print enable word",          g_PrintEnable);
    seq_printf(p, "%-27s :%#x\n", "vfmw_state enable word",     g_TraceCtrl);
    seq_printf(p, "%-27s :%d\n",  "bitstream control period",   g_TraceBsPeriod);
    seq_printf(p, "%-27s :%d\n",  "frame control period",       g_TraceFramePeriod);
    seq_printf(p, "%-27s :%d\n",  "rcv/rls img control period", g_TraceImgPeriod);

    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "you can perform vfmw debug with such commond:\n");
    seq_printf(p, "echo [arg1] [arg2] > /proc/vfmw\n\n");
    seq_printf(p, "debug action                    arg1       arg2\n");
    seq_printf(p, "------------------------------  --------  ---------------------\n");
    seq_printf(p, "set print enable                0x0       print_enable_word\n");
    seq_printf(p, "set err_thr                     0x2       (chan_id<<24)|err_thr\n");
    seq_printf(p, "set dec order output            0x4       (chan_id<<24)|dec_order_output_enable\n");
    seq_printf(p, "set dec_mode(0/1/2=IPB/IP/I)    0x5       (chan_id<<24)|dec_mode\n");
    seq_printf(p, "set discard_before_dec_thr      0x7       (chan_id<<24)|stream_size_thr\n");
    seq_printf(p, "set postprocess options         0xa       (dc<<8)|(db<<4)|dr, 0000=auto,0001=on,0010=off\n");
    seq_printf(p, "set frame/adaptive storage      0xb       0:frame only, 1:adaptive\n");
    seq_printf(p, "pay attention to the channel    0xd       channel number\n");
    seq_printf(p, "channel vcmp config             0xe       chanId: arg2>>27,\n%42smirror_en: (arg2>>26)&1,\n%42svcmp_en: (arg2>>25)&1,\n%42swm_en: (arg2>>24)&1,\n%42swm_start: (arg2>>12)&0xfff,\n%42swm_end: (arg2)&0xfff\n", " ", " ", " ", " ", " ");
    seq_printf(p, "set regulator enable or disable 0xf       disable:0, enable:1 \n");
    seq_printf(p, "print tracer                    0x100     tracer address. do not care if vfmw still running\n");
    seq_printf(p, "start/stop raw stream saving    0x200     chan_id\n");
    seq_printf(p, "start/stop stream seg saving    0x201     chan_id\n");
    seq_printf(p, "start/stop 2D yuv saving        0x202     (chan_id<<24)|crop_enable\n");
    seq_printf(p, "save a single 2D frame          0x203     frame phy addr\n");
    seq_printf(p, "save a single 1D frame          0x204     frame phy addr width height=(height+PicStructure)\n");
    seq_printf(p, "set dec_task_schedule_delay     0x400     schedual_delay_time(ms)\n");
    seq_printf(p, "stop/start syntax dec           0x402     do not care\n");
    seq_printf(p, "set trace controller            0x500     vfmw_state_word in /proc/vfmw_prn\n");
    seq_printf(p, "set bitstream control period    0x501     period (ms)\n");
    seq_printf(p, "set frame control period        0x502     period (ms)\n");
    seq_printf(p, "set rcv/rls img control period  0x503     period (ms)\n");
    seq_printf(p, "set no stream report period     0x504     period (ms)\n");
    seq_printf(p, "set module lowdelay start       0x600     channel number\n");
    seq_printf(p, "set module lowdelay stop        0x601     channel number\n");
    seq_printf(p, "set tunnel line number          0x602     channel number\n");
    seq_printf(p, "set scd lowdelay start          0x603     channel number\n");
    seq_printf(p, "set scd lowdelay stop           0x604     channel number\n");
    seq_printf(p, "set VDH clock frequency         0x605     clock_sel\n");
    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

int vfmw_read_proc_prn(struct seq_file *p, void *v)
{
    seq_printf(p, "'print_enable_word' definition, from bit31 to bit0:\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "<not used>  DEC_MODE    PTS         POST\n");
    seq_printf(p, "INT_TIME    SCD_INFO    SCD_STREAM  SCD_REGMSG\n");
    seq_printf(p, "BLOCK       DBG         SE          SEI\n");
    seq_printf(p, "SLICE       PIC         SEQ         MARK_MMCO\n");
    seq_printf(p, "POC         DPB         REF         QUEUE\n");
    seq_printf(p, "IMAGE       STR_BODY    STR_TAIL    STR_HEAD\n");
    seq_printf(p, "STREAM      UPMSG       RPMSG       DNMSG\n");
    seq_printf(p, "VDMREG      CTRL        ERROR       FATAL\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "'vfmw_state' definition, from bit31 to bit0:\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<VO_REL_IMG>     <VO_RCV_IMG>     <2D_TO_QUEUE> <1D_TO_QUEUE>\n");
    seq_printf(p, "<VDH_REPAIR>     <VDH_INTERRUPT>  <VDH_START>   <GENERATE_DECPARAM>\n");
    seq_printf(p, "<DECSYNTAX_SEG>  <SCD_INTERRUPT>  <SCD_START>   <RCV_RAW>\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "'extra_cmd' definition, from bit31 to bit0:\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>      <direct 8x8>   <B before P>\n");
    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

int vfmw_read_proc_scd(struct seq_file *p, void *v)
{
    SINT32 i;
    SINT32 ret;
    SINT32 RawNum, RawSize, SegNum, SegSize;
    char strVidStd[MAX_VID_PROTOCOL_NAME];
    SM_INSTANCE_S *pInst = NULL;

    seq_printf(p, "=============== scd info ==============================\n");
    seq_printf(p, "%-25s :%d\n", "IsScdDrvOpen", g_pSmIIS->IsScdDrvOpen);
    seq_printf(p, "%-25s :%d\n", "SCDState", g_pSmIIS->SCDState);
    seq_printf(p, "%-25s :%d\n", "ThisInstID", g_pSmIIS->ThisInstID);
    seq_printf(p, "%-25s :%d\n", "LastProcessTime", g_pSmIIS->LastProcessTime);
    seq_printf(p, "%-25s :%#x\n", "HwMemAddr", g_pSmIIS->ScdDrvMem.HwMemAddr);
    seq_printf(p, "%-25s :%d\n", "HwMemSize", g_pSmIIS->ScdDrvMem.HwMemSize);
    seq_printf(p, "%-25s :%#x\n", "DownMsgMemAddr", g_pSmIIS->ScdDrvMem.DownMsgMemAddr);
    seq_printf(p, "%-25s :%#x\n", "UpMsgMemAddr", g_pSmIIS->ScdDrvMem.UpMsgMemAddr);

    i = g_CurProcChan;

    pInst = g_pSmIIS->pSmInstArray[i];
    if(NULL == pInst || pInst->Mode == SM_INST_MODE_IDLE)
    {
        return 0;
    }

    //continue;
    ret = GetRawStreamSize(&pInst->RawPacketArray, &RawSize);

    if (FMW_OK != ret)
    {
        dprint(PRN_DBG, "fuction return value is null,%s %d unknow error!!\n", __FUNCTION__, __LINE__);
    }

    ret = GetRawStreamNum(&pInst->RawPacketArray, &RawNum);

    if (FMW_OK != ret)
    {
        dprint(PRN_DBG, "fuction return value is null,%s %d unknow error!!\n", __FUNCTION__, __LINE__);
    }

    ret = GetSegStreamSize(&pInst->StreamSegArray, &SegSize);

    if (FMW_OK != ret)
    {
        dprint(PRN_DBG, "fuction return value is null,%s %d unknow error!!\n", __FUNCTION__, __LINE__);
    }

    ret = GetSegStreamNum(&pInst->StreamSegArray, &SegNum);

    if (FMW_OK != ret)
    {
        dprint(PRN_DBG, "fuction return value is null,%s %d unknow error!!\n", __FUNCTION__, __LINE__);
    }

    VID_STD_Enum2Str(pInst->Config.VidStd, strVidStd);
    seq_printf(p, "--------------- inst[%d] -------------\n", i);
    seq_printf(p, "%-25s :%d\n", "Mode", pInst->Mode);
    seq_printf(p, "%-25s :%s\n", "cfg VidStd", strVidStd);
    seq_printf(p, "%-25s :%d\n", "is wait seg ext", pInst->IsCounting);
    seq_printf(p, "%-25s :%d\n", "is_omx_path", pInst->Config.IsOmxPath);
    seq_printf(p, "%-25s :%#x\n", "cfg BufPhyAddr", pInst->Config.BufPhyAddr);
    seq_printf(p, "%-25s :%d\n", "cfg BufSize", pInst->Config.BufSize);
    seq_printf(p, "%-25s :%d\n", "raw size count", pInst->u32RawSizeCount);
    seq_printf(p, "%-25s :%d\n", "raw num count", pInst->u32RawNumCount);
    seq_printf(p, "%-25s :%d\n", "raw Total size", RawSize);
    seq_printf(p, "%-25s :%d\n", "raw Total num", RawNum);
    seq_printf(p, "%-25s :%d\n", "seg Total size", SegSize);
    seq_printf(p, "%-25s :%d\n", "seg Total num", SegNum);
    seq_printf(p, "%-25s :%#x\n", "seg read_addr", pInst->StreamSegArray.SegBufReadAddr);
    seq_printf(p, "%-25s :%#x\n", "seg write_addr", pInst->StreamSegArray.SegBufWriteAddr);
    seq_printf(p, "%-25s :%d Kbps\n", "actual bitrate", pInst->BitRate);
    seq_printf(p, "\n");

    return 0;
}

int vfmw_read_proc_chn(struct seq_file *p, void *v)
{
    SINT32 i;

    seq_printf(p, "=============== chn info ==============================\n");

    seq_printf(p, "=============== chn by vdh ============================\n");

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        seq_printf(p, "%d ", g_ChanCtx.ChanDecByVdhPlusOne[i] - 1);
    }

    seq_printf(p, "\n");

    seq_printf(p, "=============== chanid by prior =======================\n");

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        seq_printf(p, "%d ", g_ChanCtx.ChanIdTabByPrior[i]);
    }

    seq_printf(p, "\n");

    seq_printf(p, "=============== chan prior ============================\n");

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        seq_printf(p, "%d ", g_ChanCtx.PriorByChanId[i]);
    }

    seq_printf(p, "\n");

    seq_printf(p, "=============== chan isopen isrun =====================\n");

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (s_pstVfmwChan[i] != NULL)
        {
            seq_printf(p, "%d %d %d\n", s_pstVfmwChan[i]->s32IsOpen, s_pstVfmwChan[i]->s32IsRun, s_pstVfmwChan[i]->s32Priority);
        }
    }

    seq_printf(p, "\n");

    return 0;
}

int vfmw_read_proc_dec(struct seq_file *p, void *v)
{
    char strVidStd[MAX_VID_PROTOCOL_NAME];
    char strEofState[MAX_VID_PROTOCOL_NAME];
    SINT32 i, j;
    SINT32 VdhLoad  = 0;
    SINT32 VdhFps   = 0;
    SINT32 VdhCycle = 0;
    SINT32 RefNum =0, ReadNum =0, NewNum =0, VdhId;
    SINT32 QueHist=0, QueHead=0, QueTail=0;
    IMAGE_VO_QUEUE *pstDecQue;
    VFMW_CHAN_S *pChan;
    extern FSP_INST_S *s_pFspInst[MAX_CHAN_NUM];
    FSP_INST_S *pFsp = NULL;

    seq_printf(p, "\n============== DEC INFO Chan [%d] ==============\n", g_CurProcChan);

    i = g_CurProcChan;

    pFsp = s_pFspInst[i];
    if (pFsp == NULL)
    {
        return 0;
    }

    pChan = s_pstVfmwChan[i];
    if (pChan == NULL)
    {
        return 0;
    }

    //continue;
    VdhId = g_ChanCtx.ChanDecByVdhPlusOne[i] - 1;

    VCTRL_GetChanImgNum(i, &RefNum, &ReadNum, &NewNum);
    if (NULL != (pstDecQue = VCTRL_GetChanVoQue(i)))
    {
        QueHist = pstDecQue->history;
        QueHead = pstDecQue->head;
        QueTail = pstDecQue->tail;
    }

    VID_STD_Enum2Str(pChan->eVidStd, strVidStd);
    VID_EofState_Enum2Str(pChan->eLastFrameState, strEofState);
    seq_printf(p, "%-25s :%d\n", "Dec by VDH",           VdhId);
    seq_printf(p, "%-25s :%d\n", "IsOpen",               pChan->s32IsOpen);
    seq_printf(p, "%-25s :%d\n", "IsRun",                pChan->s32IsRun);
    seq_printf(p, "%-25s :%d\n", "Priority",             pChan->s32Priority);
    seq_printf(p, "%-25s :%s\n", "eVidStd",              strVidStd);
    seq_printf(p, "%-25s :%d\n", "ChanCapLevel",         pChan->eChanCapLevel);
    seq_printf(p, "%-25s :%s\n", "LastFrameState",       strEofState);
    seq_printf(p, "%-25s :%d\n", "IsOmxPath",            pChan->stChanCfg.s8IsOmxPath);
    seq_printf(p, "%-25s :%d\n", "SpecMode",             pChan->stChanCfg.s8SpecMode);
    seq_printf(p, "%-25s :%d\n", "DecMode",              pChan->stChanCfg.s32DecMode);
    seq_printf(p, "%-25s :%d\n", "DecOrderOutput",       pChan->stChanCfg.s8DecOrderOutput);
    seq_printf(p, "%-25s :%d\n", "ErrorThred",           pChan->stChanCfg.s32ChanErrThr);
    seq_printf(p, "%-25s :%d\n", "StreamThred",          pChan->stChanCfg.s32ChanStrmOFThr);

    if (VFMW_VC1 == pChan->eVidStd)
    {
        seq_printf(p, "%-25s :%d\n", "USE_FF_APT_EN",   USE_FF_APT_EN);
        seq_printf(p, "%-25s :%d\n", "StdExt AP",       pChan->stChanCfg.StdExt.Vc1Ext.IsAdvProfile);
        seq_printf(p, "%-25s :%d\n", "StdExt CodecVer", pChan->stChanCfg.StdExt.Vc1Ext.CodecVersion);
    }
#ifdef VFMW_VP6_SUPPORT
    else if (VFMW_VP6 == pChan->eVidStd || VFMW_VP6F == pChan->eVidStd || VFMW_VP6A == pChan->eVidStd)
    {
        seq_printf(p, "%-25s :%d\n", "StdExt Reversed",      pChan->stChanCfg.StdExt.Vp6Ext.bReversed);
    }
#endif
#ifdef VFMW_MPEG4_SUPPORT
    else if (VFMW_MPEG4 == pChan->eVidStd)
    {
        seq_printf(p, "%-25s :%d\n",          "Skip Frame Found",      g_VfmwChanStat[i].u32SkipFind);
        seq_printf(p, "%-25s :%d\n",          "Skip Frame Discarded",  g_VfmwChanStat[i].u32SkipDiscard);
        seq_printf(p, "%-25s :%d\n",          "Is Short Headed",      ((MP4_CTX_S*)(&pChan->stSynCtx.unSyntax))->ScdUpMsg.IsShStreamFlag);
    }
#endif

    seq_printf(p, "\n");
    seq_printf(p, "%-25s :%#x\n", "ChanMem VDH Mem Phy",  pChan->stChanMem_vdh.PhyAddr);
    seq_printf(p, "%-25s :%d\n",  "ChanMem VDH Mem Size", pChan->stChanMem_vdh.Length);
    seq_printf(p, "%-25s :%#x\n", "ChanMem SCD Mem Phy",  pChan->stChanMem_scd.PhyAddr);
    seq_printf(p, "%-25s :%d\n",  "ChanMem SCD Mem Size", pChan->stChanMem_scd.Length);
    seq_printf(p, "%-25s :%#x\n", "ChanMem CTX Mem Phy",  pChan->stChanMem_ctx.PhyAddr);
    seq_printf(p, "%-25s :%d\n",  "ChanMem CTX Mem Size", pChan->stChanMem_ctx.Length);

    seq_printf(p, "\n");
    seq_printf(p, "%-25s :%d,%d,%d\n",    "Ref,Read,New",          RefNum, ReadNum, NewNum);
    seq_printf(p, "%-25s :(%d,%d,%d)\n",  "VoQue Detail",          QueHist, QueHead, QueTail);
    seq_printf(p, "%-25s :%d\n",          "Actual DecMode",        pChan->stSynExtraData.s32DecMode);
    seq_printf(p, "%-25s :%d\n",          "Actual DecOrderOutput", pChan->stSynExtraData.s32DecOrderOutput);
    seq_printf(p, "%-25s :%#x\n",         "Image Format",          pChan->stRecentImgformat);
    seq_printf(p, "%-25s :%d\n",          "Frame Packing Type",    pChan->stRecentImgPackingType);
    seq_printf(p, "\n");

    /* FSP */
    seq_printf(p, "------------------- FSP INFO ------------------\n");
    seq_printf(p, "%-25s :%d\n", "FSP DecFsWidth",       pFsp->stInstCfg.s32DecFsWidth);
    seq_printf(p, "%-25s :%d\n", "FSP DecFsHeight",      pFsp->stInstCfg.s32DecFsHeight);
    seq_printf(p, "%-25s :%d\n", "FSP DispFsWidth",      pFsp->stInstCfg.s32DispFsWidth);
    seq_printf(p, "%-25s :%d\n", "FSP DispFsHeight",     pFsp->stInstCfg.s32DispFsHeight);
    seq_printf(p, "%-25s :%d\n", "FSP ExpectedDecFsNum", pFsp->stInstCfg.s32ExpectedDecFsNum);
    seq_printf(p, "%-25s :%d\n", "FSP TotalValidFSNum",  pFsp->s8TotalValidFsNum);
    seq_printf(p, "%-25s :%d\n", "FSP ActualPmvNum",     pFsp->s32PmvNum);
    seq_printf(p, "%-25s :%d\n", "FSP ActualDecFsNum",   pFsp->s32DecFsNum);

    for (j = 0; j < pFsp->s32DecFsNum; j++)
    {
        if ((j != 0) && ((j & 15) == 0) ) { seq_printf(p, "\n"); }

        seq_printf(p, "%d%d ",pFsp->stDecFs[j].IsDecRef,pFsp->stDecFs[j].DispState);
    }
    seq_printf(p, "\n");

    seq_printf(p, "%-25s :%d\n",   "FSP LogicFsNum",     MAX_FRAME_NUM);
    for (j = 0; j < MAX_FRAME_NUM; j++)
    {
        if ((j != 0) && ((j & 15) == 0) ) { seq_printf(p, "\n"); }

        seq_printf(p, "%d%d ", pFsp->stLogicFs[j].s32IsRef, pFsp->stLogicFs[j].s32DispState);
    }
    seq_printf(p, "\n");

    /* Dynamic Frame Store */
    if (1 == pChan->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn)
    {
            seq_printf(p, "--------------Dynamic Frame Store--------------\n");
    	if (1 == pChan->stSynExtraData.stChanOption.u32OmxBypassMode)
    	{
            seq_printf(p, "%-25s : %d\n",    "Ref Frame Num",          pChan->s32RefFrameNum);
            seq_printf(p, "%-25s : %d\n",    "Frm Size(byte)",         pChan->s32RefFrameSize);
            seq_printf(p, "%-25s : %d\n",    "Pmv Size(byte)",         pChan->s32RefPmvSize);
            seq_printf(p, "%-25s : %d\n",    "Max Time(ms)",           g_u32DFSMaxAllocTime);
            seq_printf(p, "%-25s : %d/%d\n", "Act Frame Num/Time(ms)", pChan->s32ActualFrameNum, pChan->stDynamicFSTimestamp.u32AllTime);
    	}
    	else
    	{
            seq_printf(p, "%-25s : %d\n",    "Ref Frame Num",          pChan->s32RefFrameNum);
            seq_printf(p, "%-25s : %d\n",    "Frm Size(byte)",         pChan->s32RefFrameSize);
            seq_printf(p, "%-25s : %d\n",    "Max Time(ms)",           g_u32DFSMaxAllocTime);
            seq_printf(p, "%-25s : %d/%d\n", "Act Frame Num/Time(ms)", pChan->s32ActualFrameNum, pChan->stDynamicFSTimestamp.u32AllTime);
        }
    }
    seq_printf(p, "\n");

    seq_printf(p, "------------------- VDH INFO ------------------\n");
    for (i = 0; i < MAX_VDH_NUM; i++)
    {
        VdhCycle = 0;
        VdhLoad  = g_VfmwGlobalStat[i].u32VaVdmLoad / 10;
        VdhFps   = g_VfmwChanStat[i].u32FrFrameRate / 10;

        if ((VdhFps != 0) && (pFsp->stInstCfg.s32DecFsWidth / 16 != 0) && (pFsp->stInstCfg.s32DecFsHeight / 16 != 0))
        {
            VdhCycle = g_VfmwGlobalStat[i].u32VaVdmKiloCycle * 1000 / VdhFps / (pFsp->stInstCfg.s32DecFsWidth / 16) / (pFsp->stInstCfg.s32DecFsHeight / 16);
        }

        seq_printf(p, "%s%-21d :%d.%d%%\n", "VDH ",    i,     VdhLoad, g_VfmwGlobalStat[i].u32VaVdmLoad % 10);
        seq_printf(p, "%-25s :%d.%d fps\n", "Frame Rate",     VdhFps,  g_VfmwChanStat[i].u32FrFrameRate % 10);
        seq_printf(p, "%-25s :%d/mb\n",     "Cycle State",    VdhCycle);
    }
    seq_printf(p, "\n");

    return 0;
}

#ifdef VFMW_SCD_LOWDLY_SUPPORT
int vfmw_read_proc_lwd(struct seq_file *p, void *v)
{
    SINT32 i;
    LOWDLY_INFO_S *pLwd = NULL;

    i = g_CurProcChan;
    pLwd = &g_stLowdlyInfo[i];

    //continue;
    seq_printf(p, "=============== lowdly info ================\n");
    seq_printf(p, "%-25s :%d\n", "LowdlyEnable", pLwd->lowdly_enable);
    seq_printf(p, "%-25s :%d\n", "ChanID",   pLwd->chan_id);
    seq_printf(p, "%-25s :%d\n", "ScdCount", pLwd->scd_count);
    seq_printf(p, "%-25s :%d\n", "VdhCount", pLwd->vdh_count);
    seq_printf(p, "\n");

    return 0;
}
#endif

int str2val(char *str, unsigned int *data)
{
    unsigned int i, d, dat, weight;

    dat = 0;

    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
        weight = 16;
    }
    else
    {
        i = 0;
        weight = 10;
    }

    for (; i < 10; i++)
    {
        if (str[i] < 0x20) { break; }
        else if (weight == 16 && str[i] >= 'a' && str[i] <= 'f')
        {
            d = str[i] - 'a' + 10;
        }
        else if (weight == 16 && str[i] >= 'A' && str[i] <= 'F')
        {
            d = str[i] - 'A' + 10;
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            d = str[i] - '0';
        }
        else
        {
            return -1;
        }

        dat = dat * weight + d;
    }

    *data = dat;

    return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
int vfmw_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *data)
#else
int vfmw_write_proc(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
#endif
{
    static char cmd[256], str[256];
    int i, j;
    unsigned int dat1, dat2, dat3, dat4;
    unsigned int args[8];

    dat1 = dat2 = dat3 = dat4 = 0;

    if (count >= sizeof(cmd))
    {
        dprint(PRN_ALWS, "MMZ: your parameter string is too long!\n");
        return -EIO;
    }

    memset(cmd, 0, sizeof(cmd));

    if (copy_from_user(cmd, buffer, count))
    {
        dprint(PRN_ALWS, "MMZ: copy_from_user failed!\n");
        return -EIO;
    }

    cmd[count] = 0;

    /* dat1 */
    i = 0;
    j = 0;

    for (; i < count; i++)
    {
        if (j == 0 && cmd[i] == ' ') { continue; }

        if (cmd[i] > ' ') { str[j++] = cmd[i]; }

        if (j > 0 && cmd[i] == ' ') { break; }
    }

    str[j] = 0;

    if (str2val(str, &dat1) != 0)
    {
        dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
        return -1;
    }

    /* dat2 */
    j = 0;

    for (; i < count; i++)
    {
        if (j == 0 && cmd[i] == ' ') { continue; }

        if (cmd[i] > ' ') { str[j++] = cmd[i]; }

        if (j > 0 && cmd[i] == ' ') { break; }
    }

    str[j] = 0;

    if (str2val(str, &dat2) != 0)
    {
        dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
        return -1;
    }

    /* extra arguments */
    if (dat1 >= 0x200 && dat1 < 0x300)
    {
        if (dat1 == 0x204)
        {
            j = 0;

            for (; i < count; i++)
            {
                if (j == 0 && cmd[i] == ' ') { continue; }

                if (cmd[i] > ' ') { str[j++] = cmd[i]; }

                if (j > 0 && cmd[i] <= ' ') { break; }
            }

            str[j] = 0;

            if (str2val(str, &dat3) != 0)
            {
                dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
                return -1;
            }

            j = 0;

            for (; i < count; i++)
            {
                if (j == 0 && cmd[i] == ' ') { continue; }

                if (cmd[i] > ' ') { str[j++] = cmd[i]; }

                if (j > 0 && cmd[i] <= ' ') { break; }
            }

            str[j] = 0;

            if (str2val(str, &dat4) != 0)
            {
                dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
                return -1;
            }
        }

        j = 0;

        for (; i < count; i++)
        {
            if (j == 0 && cmd[i] == ' ') { continue; }

            if (cmd[i] > ' ') { str[j++] = cmd[i]; }

            if (j > 0 && cmd[i] <= ' ') { break; }
        }

        str[j] = 0;

        if (str[0] == '/')
        {
            if (j >= 1)
            {
                if (str[j - 1] == '/')
                {
                    str[j - 1] = 0;
                }

                dprint(PRN_ALWS, "******* vfmw save path: %s ********\n", str);
                strncpy(s_VfmwSavePath, str, sizeof(s_VfmwSavePath));
                s_VfmwSavePath[sizeof(s_VfmwSavePath) - 1] = '\0';
            }
            else
            {
                dprint(PRN_ALWS, "%s %d j < 1!!\n", __FUNCTION__, __LINE__);
                return -1;
            }
        }
    }

    dprint(PRN_ALWS, "\nvfmw debug: arg1=%#x, arg2=%#x\n", dat1, dat2);

    args[0] = dat2;
    args[1] = dat3;
    args[2] = dat4;
    VCTRL_SetDbgOption(dat1, (UINT8 *)args);

    return count;
}

int vfmw_proc_open(struct inode *inode, struct file *file)
{
    vfmw_proc_func *proc;

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
    proc = PDE(inode)->data;
#else
    proc = PDE_DATA(inode);
#endif

    if (NULL == proc)
    {
        return -ENOSYS;
    }

    if (proc->read)
    {
        return single_open(file, proc->read, proc);
    }

    return -ENOSYS;
}

ssize_t vfmw_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    struct seq_file *s      = file->private_data;
    vfmw_proc_func  *proc   = s->private;

    if (proc->write)
    {
        return proc->write(file, buf, count, ppos);
    }

    return -ENOSYS;
}

static vfmw_proc_func  vfmw_proc[32];

HI_S32 OSAL_ProcCreate(HI_CHAR *proc_name, vfmw_proc_read_fn read, vfmw_proc_write_fn write)
{
    struct proc_dir_entry  *entry;
    vfmw_proc_func         *proc = NULL;
    HI_U32                  i;
    HI_U32                  count = sizeof(vfmw_proc) / sizeof(vfmw_proc[0]);

    for (i = 0; i < count; i++)
    {
        if ((HI_NULL == vfmw_proc[i].read) && (HI_NULL == vfmw_proc[i].write))
        {
            proc = &vfmw_proc[i];

            strncpy(proc->proc_name, proc_name, sizeof(proc->proc_name));
            proc->proc_name[sizeof(proc->proc_name) - 1] = 0;

            proc->read  = read;
            proc->write = write;

            break;
        }
    }

    if (i >= count)
    {
        return -1;
    }

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
    entry = create_proc_entry(proc_name, 0666, HI_NULL);
    if (!entry)
    {
        return -1;
    }

    entry->proc_fops    = &vfmw_proc_fops;
    entry->data         = proc;
#else
    entry = proc_create_data(proc_name, 0666, HI_NULL, &vfmw_proc_fops, (void*)proc);
    if (!entry)
    {
        return -1;
    }
#endif

    return 0;
}

HI_VOID OSAL_ProcDestroy(HI_CHAR *proc_name)
{
    HI_U32  i;
    HI_U32  count = sizeof(vfmw_proc) / sizeof(vfmw_proc[0]);

    for (i = 0; i < count; i++)
    {
        vfmw_proc_func *proc = &vfmw_proc[i];

        if (0 == strncmp(proc_name, proc->proc_name, sizeof(proc->proc_name)))
        {
            remove_proc_entry(proc_name, HI_NULL);

            memset(proc->proc_name, 0, sizeof(proc->proc_name));

            proc->read  = HI_NULL;
            proc->write = HI_NULL;

            break;
        }
    }
}

#endif

SINT32 OSAL_ProcInit(VOID)
{
#ifdef HI_VFMW_PROC_SUPPORT
    HI_S32  ret;

    ret = OSAL_ProcCreate(VFMW_PROC_NAME, vfmw_read_proc, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = OSAL_ProcCreate(VFMW_PROC_NAME_DBG, vfmw_read_proc_dbg, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = OSAL_ProcCreate(VFMW_PROC_NAME_DPRN, vfmw_read_proc_prn, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = OSAL_ProcCreate(VFMW_PROC_NAME_SCD, vfmw_read_proc_scd, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = OSAL_ProcCreate(VFMW_PROC_NAME_DEC, vfmw_read_proc_dec, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

#ifdef VFMW_SCD_LOWDLY_SUPPORT
    ret = OSAL_ProcCreate(VFMW_PROC_NAME_LWD, vfmw_read_proc_lwd, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }
#endif

    ret = OSAL_ProcCreate(VFMW_PROC_NAME_CHN, vfmw_read_proc_chn, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }
#endif

    return 0;
}


VOID OSAL_ProcExit(VOID)
{
#ifdef HI_VFMW_PROC_SUPPORT
    HI_U32  i;
    HI_CHAR name[16];
    HI_U32  end = sizeof(name) - 1;

    for (i = 0; i < 16; i++)
    {
        snprintf(name, sizeof(name), "vfmw%02d", i);
        name[end] = 0;

        OSAL_ProcDestroy(name);
    }

    OSAL_ProcDestroy(VFMW_PROC_NAME);
    OSAL_ProcDestroy(VFMW_PROC_NAME_DBG);
    OSAL_ProcDestroy(VFMW_PROC_NAME_DPRN);
    OSAL_ProcDestroy(VFMW_PROC_NAME_SCD);
    OSAL_ProcDestroy(VFMW_PROC_NAME_DEC);

#ifdef VFMW_SCD_LOWDLY_SUPPORT
    OSAL_ProcDestroy(VFMW_PROC_NAME_LWD);
#endif

    OSAL_ProcDestroy(VFMW_PROC_NAME_CHN);
#endif
}

#endif
