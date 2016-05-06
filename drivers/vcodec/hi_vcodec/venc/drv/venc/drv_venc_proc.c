/***********************************************************************************
*              Copyright 2004 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  vi_proc.c
* Description:
*
***********************************************************************************/

#include "hi_drv_mem.h"
#include "hi_drv_venc.h"
#include "drv_venc.h"
#include "drv_venc_osal.h"
#include <linux/seq_file.h>//ljh add
#include <asm/uaccess.h>

#include <linux/module.h>
#include <linux/version.h>
#include <linux/proc_fs.h>

extern OPTM_VENC_CHN_S g_stVencChn[VENC_MAX_CHN_NUM];
extern HI_S32 gVencNodeNum;
extern ION_MEM_DESC_S  gVencMemNode[MAX_ION_MEM_NODE];
extern struct ion_client *g_ion_client;

static HI_S32 VENC_DRV_ProcRead(struct seq_file *p, HI_VOID *v);
static ssize_t VENC_DRV_ProcWrite(struct file *file, const char __user *buffer, size_t count, loff_t *ppos);

static HI_S32 VENC_DRV_MEM_ProcRead(struct seq_file *p, HI_VOID *v);

static HI_S32 VENC_DRV_ProcOpen(struct inode *inode, struct file *file)
{
    void* data = NULL;
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
    data = PDE(inode)->data;
#else
    data = PDE_DATA(inode);
#endif
    if (data == NULL)
    {
   		return single_open(file, VENC_DRV_MEM_ProcRead, data);
	}
	else
	{
   		return single_open(file, VENC_DRV_ProcRead, data);
	}
}

struct file_operations  VENC_PROC_FOPS = {
        .owner      = THIS_MODULE,
        .open       = VENC_DRV_ProcOpen,
        .read       = seq_read,
        .write      = VENC_DRV_ProcWrite,
        .llseek     = seq_lseek,
        .release    = single_release,
};


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

static HI_VOID VENC_DRV_ProcHelp(HI_VOID)
{
    HI_DRV_PROC_EchoHelper("------ VENC Proc Help ------\n");
    HI_DRV_PROC_EchoHelper("USAGE:echo [cmd] [para1] [para2] > /proc/msp/vencXX\n");
	HI_DRV_PROC_EchoHelper("cmd = set_print,   para1           set print level for Encode,(0x1:FATAL 0x3:Err 0x7: WARNING 0xf:INFO 0x1f:DEBUG)\n");
    HI_DRV_PROC_EchoHelper("cmd = save_yuv,    para1 = start   start to save the yuv data before Encode\n");
	HI_DRV_PROC_EchoHelper("cmd = save_yuv,    para1 = stop    stop to save the yuv data before Encode\n");
    HI_DRV_PROC_EchoHelper("cmd = save_stream, para1 = second  save the streams after Encode for [para2] seconds\n");
	HI_DRV_PROC_EchoHelper("cmd = save_stream, para1 = frame  save the streams after Encode for [para2] frames\n");
	HI_DRV_PROC_EchoHelper("cmd = LowPowEn,    para1          if [para1]=0,means unable the low power control of algorithm\n");
	HI_DRV_PROC_EchoHelper("                                  if [para1]=0,means enable the low power control of algorithm\n");
}

static HI_S32 str2val(char *str, unsigned int *data)
{
    unsigned int i, d, dat, weight;

    dat = 0;
    if(str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
		weight = 16;
	}
	else
	{
        i = 0;
		weight = 10;
	}

    for(; i < 10; i++)
    {
        if(str[i] < 0x20)break;
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

static HI_VOID val2str(unsigned int data,int radix,char *str)
{
   char tmp[32]={'\0'};
   unsigned int tmpval = data;
   int i,j;
   for(i=0;i<32;i++)
   {
		tmp[i]=((int)tmpval%radix)+'0';
		tmpval=tmpval/(unsigned int)radix;
		if(tmpval==0)
		break;
   }

   for(j=0;(i>=0)&&(i<32);i--)str[j++]=tmp[i];
   str[j]='\0';
   return ;
}

HI_S32 VENC_DRV_MEM_ProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_S32 i = 0;
    HI_U32 total_size = 0;

    PROC_PRINT(p, "================ MEM INFO ================\n\n");

    if (gVencNodeNum > 0)
    {
	    PROC_PRINT(p, " %-15s%-10s%-10s%-10s\n\n", "NAME", "OWNER", "PHYADDR", "SIZE");
    	for (i=0; i<MAX_ION_MEM_NODE; i++)
    	{
    	    if (gVencMemNode[i].phys_addr != 0)
    	    {
                PROC_PRINT(p, " %-15s%-10s%-10x%-10d\n",
                          gVencMemNode[i].node_name,
                          gVencMemNode[i].zone_name,
                          gVencMemNode[i].phys_addr,
                          gVencMemNode[i].size);
				total_size += gVencMemNode[i].size;
    	    }
    	}
        PROC_PRINT(p, "\n");
        PROC_PRINT(p, "------------------------------------------\n\n");
    }

    PROC_PRINT(p, "%-15s:%d\n", " TotalNum",   gVencNodeNum);
    PROC_PRINT(p, "%-15s:%d\n", " TotalSize",  total_size);
    PROC_PRINT(p, "\n");
    PROC_PRINT(p, "==========================================\n\n");

    return 0;
}


static HI_S32 VENC_DRV_ProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_S32 s32Ret = HI_FAILURE;
	HI_HANDLE hVenc;
	HI_U32 u32ChnID = 0;
	HI_U32 u32SkipFrmNum = 0;
    VeduEfl_StatInfo_S StatInfo;
    VeduEfl_StatInfo_S *pStatInfo = &StatInfo;

    HI_CHAR szProtocol[][16] = {"MPEG2", "MPEG4", "AVS",  "H.263",    "H.264", "REAL8", "REAL9",
                             "VC1","VP6","VP6F", "VP6A","MJPEG","SORENSON","DIVX3", "RAW",   "JPEG",  "VP8",
                             "MSMPEG4V1","MSMPEG4V2","MSVIDEO1","WMV1","WMV2","RV10","RV20","SVQ1","SVQ3","H261","VP3","VP5",
                             "CHINEPAK","INDEO2","INDEO3","INDEO4","INDEO5","MJPEGB","MVC","HEVC","DV","BUTT","UNKNOWN"};

	HI_CHAR szBoolTab[][8] = {"FALSE", "TRUE"};
	HI_CHAR szStateTab[][8] = {"Stop", "Start"};
	HI_CHAR szPixFormat[][16] = {"SP420_VU", "SP420_UV", "Planer420",  "Planer422", "Package422_YUYV", "Package422_UYVY","Package422_YVYU","UNKNOWN"};
    HI_CHAR szBufStateTab[][8] = {"NA","NA","NA","NA","NA","NA"};
	HI_CHAR szMaxMinQP[][8]= {"NA","NA"};
//	pProcItem = p->private;
    hVenc = (HI_HANDLE)p->private;

    seq_printf(p, "=============== vfmw info =============\n");
    D_VENC_GET_CHN(u32ChnID, hVenc);
    seq_printf(p, "u32ChnID:%d\n",u32ChnID);

	D_VENC_CHECK_CHN(u32ChnID);

    s32Ret = VENC_DRV_EflQueryStatInfo(g_stVencChn[u32ChnID].hVEncHandle, pStatInfo);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("VENC_DRV_EflQueryStatInfo failed!\n");
		return HI_FAILURE;
    }


    memcpy((HI_VOID *)szBufStateTab[0],"NA",3);
	memcpy((HI_VOID *)szBufStateTab[1],"NA",3);
	memcpy((HI_VOID *)szBufStateTab[2],"6",2);
    memcpy((HI_VOID *)szBufStateTab[3],"NA",3);
	memcpy((HI_VOID *)szBufStateTab[4],"NA",3);
    val2str(pStatInfo->QueueNum, 10, szBufStateTab[5]);

    /* VBR */
	val2str( g_stVencChn[u32ChnID].stChnUserCfg.u32MaxQp, 10, szMaxMinQP[0]);
	val2str( g_stVencChn[u32ChnID].stChnUserCfg.u32MinQp, 10, szMaxMinQP[1]);

	u32SkipFrmNum = pStatInfo->QuickEncodeSkip + pStatInfo->ErrCfgSkip + pStatInfo->FrmRcCtrlSkip
		            + pStatInfo->TooFewBufferSkip + pStatInfo->SamePTSSkip;

    pStatInfo->RecvTotalFrameNum = pStatInfo->GetFrameNumOK + pStatInfo->FlushUndoFrameNum;
    pStatInfo->RecvTotalStreamNum = pStatInfo->GetStreamNumOK + pStatInfo->FlushUndoStreamNum;


    PROC_PRINT(p, "--------------------- VENC[%02d] -----------------------\n", u32ChnID);
	PROC_PRINT(p, "-------------------- User  Config ----------------------\n");
    PROC_PRINT(p,
                    "CodecID                       :%s(0x%x)\n"
                    "Resolution                    :%uX%u\n"
                    "TargetBitRate                 :%u(kbps)\n"
                    "Gop                           :%u\n"
                    "FrmRate(Input/OutPut)         :%u/%u(fps)\n"
                    "priority                      :%u\n"
                    "QuickEncode                   :%s\n"
                    "Split                         :Enable(%s)	Size(%u)\n"
                    "StreamBufSize                 :%u(KB)\n"
                    "MaxQP/MinQP                   :%s/%s\n"
                    "QLevel                        :%u\n"
                    "Rotation                      :%u\n"
                    ,

                    szProtocol[g_stVencChn[u32ChnID].stChnUserCfg.enVencType],g_stVencChn[u32ChnID].stChnUserCfg.enVencType,
                    g_stVencChn[u32ChnID].stChnUserCfg.u32Width,
                    g_stVencChn[u32ChnID].stChnUserCfg.u32Height,
                    g_stVencChn[u32ChnID].stChnUserCfg.u32TargetBitRate / 1000U,
                    g_stVencChn[u32ChnID].stChnUserCfg.u32Gop,
                    g_stVencChn[u32ChnID].stChnUserCfg.u32InputFrmRate,g_stVencChn[u32ChnID].stChnUserCfg.u32TargetFrmRate,
                    g_stVencChn[u32ChnID].stChnUserCfg.u8Priority,
                    szBoolTab[g_stVencChn[u32ChnID].stChnUserCfg.bQuickEncode],

	                szBoolTab[g_stVencChn[u32ChnID].stChnUserCfg.bSlcSplitEn],g_stVencChn[u32ChnID].u32SliceSize*16,
	                g_stVencChn[u32ChnID].stChnUserCfg.u32StrmBufSize / 1000U,
	                szMaxMinQP[0],szMaxMinQP[1],
                    g_stVencChn[u32ChnID].stChnUserCfg.u32Qlevel,
                    g_stVencChn[u32ChnID].stChnUserCfg.u32RotationAngle);
	PROC_PRINT(p, "------------------ Real-time  Statistics ----------------------\n");
    PROC_PRINT(p,
                    "WorkStatus                    :%s\n"
                    "FrameInfo                     :%s\n"
                    "InputFrmRate(Use/Real)        :%u/%u(fps)\n"
                    "TargetFrmRate(Use/Real)       :%u/%u(fps)\n"
                    "BitRate                       :%u(kbps)\n"
                    "EncodeNum                     :%u\n"
                    "SkipNum                       :Total(%u) FrmRateCtrl(%u) SamePTS(%u) QuickEncode(%u) TooFewBuf(%u) ErrCfg(%u)\n"
                    "FrameBuffer:\n"
//                    "    VpssQueueBuf(Total/Used)  :%s/%s\n"
//                    "    VpssImgBuf  (Total/Used)  :%s/%s\n"
                    "    VencQueueBuf(Total/Used)  :%s/%s\n"
                    "StreamBuffer:\n"
                    "    Total/Used/Percent(Bytes) :%u/%u/%u%%\n"
                    "Statistics(Total):\n"
                    "    AcquireFrame(Try/OK)      :%d/%d\n"
                    "    ReleaseFrame(Try/OK)      :%d/%d\n"
                    "    AcquireStream(Try/OK)     :%d/%d\n"
                    "    ReleaseStream(Try/OK)     :%d/%d\n"
                    "    AcquireStreamInIsr(Try/OK)     :%d/%d\n"
                    "    AcquireStreamInTask(Try/OK)     :%d/%d\n"
                    "    FlushUndoFrame(Try/OK)     :%d/%d\n"
                    "    FlushUndoStream(Try/OK)     :%d/%d\n"
                    "    RecvTotalFrame(Try/OK)     :%d/%d\n"
                    "    RecvTotalStream(Try/OK)     :%d/%d\n"
                    "    QueueFrame(Try/OK)     :%d/%d\n"
                    "    QueueStream(Try/OK)     :%d/%d\n"
                    "Statistics(PerSecond):\n"
                    "    AcquireFrame(Try/OK)      :%d/%d\n"
                    "    ReleaseFrame(Try/OK)      :%d/%d\n"
                    "    StartVencInTask      			:%d\n"
                    "    StartVencInIsr      			:%d\n"
                    "    FrameIrqNum					:%d\n"
					"    SliceIrqNum					:%d\n"
					"	 IrqNum							:%d\n"
                    ,
                    szStateTab[g_stVencChn[u32ChnID].bEnable],
                    szPixFormat[pStatInfo->u32FrameType],
                    pStatInfo->u32RealSendInputRrmRate,g_stVencChn[u32ChnID].u32LastSecInputFps,
                    pStatInfo->u32RealSendOutputFrmRate,g_stVencChn[u32ChnID].u32LastSecEncodedFps,
                    g_stVencChn[u32ChnID].u32LastSecKbps * 8 / 1000U,
                    (pStatInfo->GetFrameNumOK - u32SkipFrmNum),
                    u32SkipFrmNum,
                    pStatInfo->FrmRcCtrlSkip,pStatInfo->SamePTSSkip,pStatInfo->QuickEncodeSkip,pStatInfo->TooFewBufferSkip,pStatInfo->ErrCfgSkip,
//                    szBufStateTab[0],szBufStateTab[1],
//                    szBufStateTab[2],szBufStateTab[3],
	                szBufStateTab[4],szBufStateTab[5],
                    g_stVencChn[u32ChnID].stChnUserCfg.u32StrmBufSize,pStatInfo->UsedStreamBuf,pStatInfo->UsedStreamBuf * 100/g_stVencChn[u32ChnID].stChnUserCfg.u32StrmBufSize,
                    pStatInfo->GetFrameNumTry, pStatInfo->GetFrameNumOK,
                    pStatInfo->PutFrameNumTry, pStatInfo->PutFrameNumOK,
                    pStatInfo->GetStreamNumTry, pStatInfo->GetStreamNumOK,
                    pStatInfo->PutStreamNumTry, pStatInfo->PutStreamNumOK,
                    pStatInfo->GetStreamNumInIsrTry, pStatInfo->GetStreamNumInIsrOK,
                    pStatInfo->GetStreamNumInTaskTry, pStatInfo->GetStreamNumInTaskOK,
                    pStatInfo->FlushUndoFrameNum,pStatInfo->FlushUndoFrameNum,
                    pStatInfo->FlushUndoStreamNum,pStatInfo->FlushUndoStreamNum,
                    pStatInfo->RecvTotalFrameNum, pStatInfo->RecvTotalFrameNum,
                    pStatInfo->RecvTotalStreamNum, pStatInfo->RecvTotalStreamNum,
                    pStatInfo->QueueFrameNumTry, pStatInfo->QueueFrameNumOK,
                    pStatInfo->QueueStreamNumTry, pStatInfo->QueueStreamNumOK,
	                g_stVencChn[u32ChnID].u32LastSecTryNum,g_stVencChn[u32ChnID].u32LastSecOKNum,
                    g_stVencChn[u32ChnID].u32LastSecPutNum,g_stVencChn[u32ChnID].u32LastSecPutNum,
					pStatInfo->StartVencNumInTask,
					pStatInfo->StartVencNumInISR,
					pStatInfo->u32FrameIrqNum,
					pStatInfo->u32SliceIrqNum,
					pStatInfo->u32IrqNum
					);


#ifdef TEST_TIME
	                PROC_PRINT(p, "------------------ Time  Statistics ----------------------\n");
                    PROC_PRINT(p,
                                    "TotalFrame:                    :%d\n"
                                    "TotalEncTime:                  :%d\n"
                                    "TotalOneCycletime:             :%d\n"
                                    "TotalEncSHRCTime:              :%d\n"
                                    "TotalEncSHTime:                :%d\n"
                                    "TotalEncRcTime:                :%d\n"
                                    "TotalCfgRegTime:              :%d\n"
                                    "TotalCfgRegTime1:              :%d\n"
                                    "TotalCfgRegTime2:              :%d\n"
                                    "TotalISRTime:                  :%d\n"
                                    "AvgEncTime:                    :%d\n"
                                    "OneCycletime:                  :%d\n"
                                    "AvgEncSHRCTime:                :%d\n"
                                    "AvgEncSHTime:                  :%d\n"
                                    "AvgEncRCTime:                  :%d\n"
                                    "AvgCfgRegTime1:                :%d\n"
                                    "AvgCfgRegTime2:                :%d\n"
                                    "AvgISRTime:                    :%d\n"
                                    "Total_VEDU_TIMER(cycle)        :%d\n"
                                    "Avg_VEDU_TIMER(cycle)          :%d\n"
                                    "Total_VEDU_IDLE_TIMER(cycle)   :%d\n"
                                    "Avg_VEDU_IDLE_TIMER(cycle)      :%d\n"
                                    "TotalISRTime1:                    :%d\n"
                                    "TotalISRTime2:                    :%d\n"
                                    "TotalISRTime3:                    :%d\n"
                                    "TotalISRTime4:                    :%d\n"
                                    "TotalISRTime5:                    :%d\n"
                                    "TotalISRTime6:                    :%d\n" ,
                                    pStatInfo->TotalFrame,
                                    pStatInfo->TotalEncTime,
                                    pStatInfo->TotalOneCycletime,
                                    pStatInfo->TotalEncSHRCTime,
                                    pStatInfo->TotalEncSHTime,
                                    pStatInfo->TotalEncRCTime,
                                    pStatInfo->TotalCfgRegTime,
                                    pStatInfo->TotalCfgRegTime1,
                                    pStatInfo->TotalCfgRegTime2,
                                    pStatInfo->TotalISRTime,
                                    pStatInfo->AvgEncTime,
                                    pStatInfo->OneCycletime,
                                    pStatInfo->AvgEncSHRCTime,
                                    pStatInfo->AvgEncSHTime,
                                    pStatInfo->AvgEncRCTime,
                                    pStatInfo->AvgCfgRegTime1,
                                    pStatInfo->AvgCfgRegTime2,
                                    pStatInfo->AvgISRTime,
                                    pStatInfo->Total_VEDU_TIMER,
                                    pStatInfo->Avg_VEDU_TIMER,
                                    pStatInfo->Total_VEDU_IDLE_TIMER,
                                    pStatInfo->Avg_VEDU_IDLE_TIMER,
                                    pStatInfo->TotalISRTime1,
                                    pStatInfo->TotalISRTime2,
                                    pStatInfo->TotalISRTime3,
                                    pStatInfo->TotalISRTime4,
                                    pStatInfo->TotalISRTime5,
                                    pStatInfo->TotalISRTime6
                                    );

/*

					PROC_PRINT(p,"ISRAvgtaketime:%d OneCycletime:%d  CfgRegTime:%d RCSHTime:%d AvgEncTime:%d "
					"CfgRegTime1:%d CfgRegTime2:%d TotalFrame:%d TotalEncSHRCTime:%d TotalCfgRegTime2:%d "
					"TotalEncSHTime:%d TotalEncRcTime:%d Total_VEDU_TIMER:%ld Avg_VEDU_TIMER:%ld\n",
						pStatInfo->ISRAvgtaketime ,pStatInfo->OneCycletime,pStatInfo->AvgCfgRegTime,pStatInfo->AvgEncSHRCTime,pStatInfo->AvgEncTime,
						pStatInfo->AvgCfgRegTime1,pStatInfo->AvgCfgRegTime2,pStatInfo->TotalFrame,pStatInfo->TotalEncSHRCTime,
						pStatInfo->TotalCfgRegTime2,pStatInfo->TotalEncSHTime,pStatInfo->TotalEncRCTime,
						pStatInfo->Total_VEDU_TIMER,pStatInfo->Avg_VEDU_TIMER);
*/
#endif


        return HI_SUCCESS;
}

static ssize_t VENC_DRV_ProcWrite(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
    static HI_CHAR buf[256], str1[256],str2[256],str3[256];
    HI_U32 u32ChnID;
    HI_S32 i,j;
    HI_U32 parm;

	struct seq_file *q = file->private_data;

    HI_HANDLE hVenc = (HI_HANDLE)q->private;
	if (hVenc == 0)
	{
        return 0;
	}



    D_VENC_GET_CHN(u32ChnID, hVenc);
	if (u32ChnID >= VENC_MAX_CHN_NUM)
	{
        HI_ERR_VENC("D_VENC_GET_CHN failed!\n");
	    return HI_FAILURE;
	}

    if(count >= sizeof(buf))
    {
		HI_INFO_VENC("MMZ: your echo parameter string is too long!\n");
		return -EIO;
	}

    if (count >= 1)
    {
	    memset(buf, 0, sizeof(buf));
		if (copy_from_user(buf, buffer, count))
		{
		    HI_INFO_VENC("MMZ: copy_from_user failed!\n");
		    return -EIO;
		}
		buf[count] = 0;

	    /* dat1 */
		i = 0;
		j = 0;
	    for(; i < count; i++)
	    {
	        if(j==0 && buf[i]==' ')continue;
	        if(buf[i] > ' ')str1[j++] = buf[i];
			if(j>0 && buf[i]==' ')break;
		}
		str1[j] = 0;

	    /*if(str2val(str, &dat1) != 0)
	    {
	        dprint(PRN_ALWS, "error echo cmd '%s'!\n", buf);
	        return -1;
		}*/

	    /* dat2 */
		j = 0;
	    for(; i < count; i++)
	    {
	        if(j==0 && buf[i]==' ')continue;
	        if(buf[i] > ' ')str2[j++] = buf[i];
			if(j>0 && buf[i]==' ')break;
		}
		str2[j] = 0;
	    /*if(str2val(str, &dat2) != 0)
	    {
	        dprint(PRN_ALWS, "error echo cmd '%s'!\n", buf);
	        return -1;
		}*/


        if (!strncmp(str1,"save_yuv",256))//modify by ljh (!HI_OSAL_Strncmp(str1,"save_yuv",256))
        {
           if (!strncmp(str2,"start",256))
           {
#if 1
               g_stVencChn[u32ChnID].stProcWrite.bSaveYUVFileRun = HI_TRUE;
#else
               HI_DBG_VENC("now start save yuv (to do)\n");//lzl
#endif

           }
		   else if (!strncmp(str2,"stop",256))
		   {
#if 1
               g_stVencChn[u32ChnID].stProcWrite.bSaveYUVFileRun = HI_FALSE;
#else
               HI_DBG_VENC("now stop save yuv (to do)\n");//lzl
#endif
		   }
		   else
		   {
		       VENC_DRV_ProcHelp();
		   }
        }
		else if (!strncmp(str1,"save_stream",256))
		{
		   if (!strncmp(str2,"second",256))   /*time mode*/
		   {
                /*dat 3*/
				j = 0;
			    for(; i < count; i++)
			    {
			        if(j==0 && buf[i]==' ')continue;
			        if(buf[i] > ' ')str3[j++] = buf[i];
					if(j>0 && buf[i]==' ')break;
				}
				str3[j] = 0;
			    if(str2val(str3, &parm) != 0)
			    {
			        HI_ERR_VENC("error: echo cmd '%s' is worng!\n", buf);
			        return HI_FAILURE;
				}

                if ( parm > 3600 )
                {
                    HI_ERR_VENC("error: not support save too large stream file!\n");
			        return HI_FAILURE;
                }

#if 0
		        HI_DRV_LOG_GetStorePath(s_VencSavePath, 64);
				HI_OSAL_Snprintf(FileName, 64, "%s/%s", s_VencSavePath,g_stVencChn[u32ChnID].stProcWrite.StreamFileName);
	            g_stVencChn[u32ChnID].stProcWrite.bTimeModeRun = HI_TRUE;
	            g_stVencChn[u32ChnID].stProcWrite.fpSaveFile = VENC_DRV_OsalFopen(FileName,  O_RDWR | O_CREAT|O_APPEND, 0);
	            if (HI_NULL == g_stVencChn[u32ChnID].stProcWrite.fpSaveFile)
	            {
	                HI_ERR_VENC("Can not create %s file.\n", FileName);
	                g_stVencChn[u32ChnID].stProcWrite.bTimeModeRun = HI_FALSE;
	                return HI_FAILURE;
	            }

	            msleep(1000 * parm);
	            g_stVencChn[u32ChnID].stProcWrite.bTimeModeRun = HI_FALSE;
	            VENC_DRV_OsalFclose(g_stVencChn[u32ChnID].stProcWrite.fpSaveFile);
#else
                HI_DBG_VENC("now save stream %d second(to do)\n",parm);
#endif
		   }
		   else if (!strncmp(str2,"frame",256))
		   {
                /*dat 3*/
				j = 0;
			    for(; i < count; i++)
			    {
			        if(j==0 && buf[i]==' ')continue;
			        if(buf[i] > ' ')str3[j++] = buf[i];
					if(j>0 && buf[i]==' ')break;
				}
				str3[j] = 0;
                if(str2val(str3, &parm) != 0)
			    {
			        HI_ERR_VENC("error: echo cmd '%s' is worng!\n", buf);
			        return HI_FAILURE;
				}

                if ( parm > 100000 )
                {
                    HI_ERR_VENC("error: not support save too large YUV file!\n");
			        return HI_FAILURE;
                }

#if 0
                HI_DRV_LOG_GetStorePath(s_VencSavePath, 64);
				HI_OSAL_Snprintf(FileName, 64, "%s/%s", s_VencSavePath,g_stVencChn[u32ChnID].stProcWrite.StreamFileName);
	            g_stVencChn[u32ChnID].stProcWrite.bFrameModeRun = HI_TRUE;
	            g_stVencChn[u32ChnID].stProcWrite.fpSaveFile = VENC_DRV_OsalFopen(FileName,  O_RDWR | O_CREAT|O_APPEND, 0);

	            if (HI_NULL == g_stVencChn[u32ChnID].stProcWrite.fpSaveFile)
	            {
	                HI_ERR_VENC("Can not create %s file.\n", FileName);
	                g_stVencChn[u32ChnID].stProcWrite.bFrameModeRun = HI_FALSE;
	                return HI_FAILURE;
	            }

	            g_stVencChn[u32ChnID].stProcWrite.u32FrameModeCount = parm;
	            while (1)
	            {
	                /* if the frame count reaches to aim, break */
	                if (HI_FALSE == g_stVencChn[u32ChnID].stProcWrite.bFrameModeRun)
	                {
	                    break;
	                }
	                else
	                {
	                    msleep(100);
	                }
	            }
	            VENC_DRV_OsalFclose(g_stVencChn[u32ChnID].stProcWrite.fpSaveFile);
#else
                HI_DBG_VENC("now save frame %d second(to do)\n",parm);//lzl
#endif


		   }
		   else
		   {
		       VENC_DRV_ProcHelp();
		   }
		}
		else if (!strncmp(str1,"LowPowEn",256))
		{
		   //VeduEfl_EncPara_S  *pEncPara  = (VeduEfl_EncPara_S *)hVenc;
           HI_DBG_VENC("LowPowEn\n");
		   if (!strncmp(str2,"0",256))
           {
			    //pEncPara->intpLowpowEn     = 0;
			    //pEncPara->fracLowpowEn     = 0;
           }
		   else if (!strncmp(str2,"1",256))
		   {
			    //pEncPara->intpLowpowEn     = 1;
			    //pEncPara->fracLowpowEn     = 1;
		   }
		   else
		   {
		       VENC_DRV_ProcHelp();
		   }
		}
		else if (!strncmp(str1,"set_print",256))
		{
           if(str2val(str2, &parm) != 0)
           {
               HI_ERR_VENC("error: echo cmd '%s' is worng!\n", buf);
               VENC_DRV_ProcHelp();
           }
		   else
		   {
		       g_VencPrintEnable = parm;
               HI_DBG_VENC("set_print level:%d\n",parm);
		   }
		}
		else
		{
		   VENC_DRV_ProcHelp();
		}
    }
	else
	{
	   VENC_DRV_ProcHelp();
	}

    return count;

}


HI_S32 VENC_DRV_MemProcAdd()   /**/
{

    struct proc_dir_entry* entry;

    entry = proc_create_data("venc_mem_info", 0, HI_NULL, &VENC_PROC_FOPS, NULL);
    if (!entry)
    {
        HI_ERR_VENC("proc create error\n");
        return -1;
    }

    HI_INFO_VENC("proc create success\n");
    return HI_SUCCESS;
}


HI_VOID VENC_DRV_MemProcDel()
{
    remove_proc_entry("venc_mem_info", NULL);
}



HI_S32 VENC_DRV_ProcAdd(HI_HANDLE hVenc,HI_U32 u32ChnID)   /**/
{
    HI_S32 Ret;
//    DRV_PROC_ITEM_S *pProcItem;
    HI_CHAR ProcName[12];
    struct proc_dir_entry* entry;

    if (HI_INVALID_HANDLE == hVenc)
    {
        HI_ERR_VENC("Invaild handle!\n");
		return HI_FAILURE;
    }

    Ret = snprintf(ProcName, sizeof(ProcName), "venc%02x", u32ChnID);

 //   Ret = HI_OSAL_Snprintf(ProcName, sizeof(ProcName), "venc%02x", u32ChnID);
    if (0 == Ret)
    {
        HI_ERR_VENC("HI_OSAL_Snprintf failed!\n");
        return HI_FAILURE;
    }

    entry = proc_create_data(ProcName, 0, HI_NULL, &VENC_PROC_FOPS, (void*)hVenc);
    if (!entry)
    {
        HI_ERR_VENC("proc create error\n");
        return -1;
    }

    HI_INFO_VENC("proc create success\n");
    return HI_SUCCESS;
}


HI_VOID VENC_DRV_ProcDel(HI_HANDLE hVenc,HI_U32 u32ChnID)
{
    HI_S32 Ret;
    HI_CHAR ProcName[12];

    if (HI_INVALID_HANDLE == hVenc)
    {
        return;
    }
    Ret = snprintf(ProcName, sizeof(ProcName), "venc%02x", u32ChnID);
    if (0 == Ret)
    {
        return;
    }
    remove_proc_entry(ProcName, NULL);
}



