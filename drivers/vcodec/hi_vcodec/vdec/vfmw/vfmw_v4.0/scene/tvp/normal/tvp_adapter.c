
#include "public.h"
#include "vfmw.h"
#include "vfmw_dts.h"
#include "linux_kernel_osal.h"
#include "linux_kernel_proc.h"
#include "tvp_adapter.h"

#include <teek_client_api.h>

// Control Macro
#define DEBUG_SAVE_SUPPORT    (0)
#define PRINT_TEE_TIME        (0)

#if (1 == DEBUG_SAVE_SUPPORT)
#include "sec_mmz.h"          // for HI_SEC_MMZ_TA2CA
#define MAX_SAVE_SIZE         (3*1024*1024)
#endif

#define PATH_LEN              (64)
#define PROC_CMD_LEN          (16)

#define PROC_NAME             "vfmw_tvp"
#define PROC_CMD_HELP         "help"
#define PROC_CMD_SUSPEND      "suspend"
#define PROC_CMD_RESUME       "resume"
#define PROC_CMD_SAVERAW      "saveraw"
#define PROC_CMD_SAVEYUV      "saveyuv"
#define PROC_CMD_START        "start"
#define PROC_CMD_STOP         "stop"
#define PROC_CMD_SETPRINT     (0x000)

#ifdef HI_ADVCA_FUNCTION_RELEASE
// 高安不能检测到字符串和printk
#define SecPrint(type, fmt, arg...)                   \
    do{                                               \
    }while(0)
#else
#define SecPrint(type, fmt, arg...)                   \
    do{                                               \
        if (PRN_ALWS == type                          \
         || 0 != (g_SecPrintEnable & (1 << type)))    \
        {                                             \
            dprint(PRN_ALWS, fmt, ##arg);             \
        }                                             \
    }while(0)
#endif

typedef enum hiCHAN_STATE_E
{
    CHAN_INVALID = 0,
    CHAN_CREATE,
    CHAN_START,
    CHAN_STOP,
}CHAN_STATE_E;

typedef enum hiTHREAD_STATE_E
{
    THREAD_INVALID = 0,
    THREAD_SLEEP,
    THREAD_RUN,
    THREAD_EXIT,
}THREAD_STATE_E;

typedef enum
{
    HIVCODEC_CMD_ID_INVALID = 0x0,
    HIVCODEC_CMD_ID_INIT,
    HIVCODEC_CMD_ID_EXIT,
    HIVCODEC_CMD_ID_SUSPEND,
    HIVCODEC_CMD_ID_RESUME,
    HIVCODEC_CMD_ID_CONTROL,
    HIVCODEC_CMD_ID_RUN_PROCESS,
    HIVCODEC_CMD_ID_GET_IMAGE,
    HIVCODEC_CMD_ID_RELEASE_IMAGE,
    HIVCODEC_CMD_ID_READ_PROC,
    HIVCODEC_CMD_ID_WRITE_PROC,
}TEE_HIVCODEC_CMD_ID;

typedef struct
{
    HI_S32               ChanID;
    OSAL_SEMA            ChanSema;
    STREAM_INTF_S        StreamIntf;
#if (1 == DEBUG_SAVE_SUPPORT)
    OSAL_FILE           *pRawFile;
#endif
}SEC_CHAN_CTX_S;

typedef struct
{
    HI_S32               ChanID;
    HI_BOOL              bIsSecMode;
    CHAN_STATE_E         ChanState;
}CHAN_RECORD_S;

/* Share memory contain */
typedef struct
{
    SHARE_EVENT_ARRAY_S  EventList;
    VDEC_CHAN_OPTION_S   ChanOption;
    SHARE_RAW_ARRAY_S    StreamList[TVP_CHAN_NUM];
    SHARE_EXTBUF_ARRAY_S ExtBuffer[TVP_CHAN_NUM];
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    HI_U8                ProcBuf[MAX_PROC_SIZE];
#endif
#if (1 == DEBUG_SAVE_SUPPORT)
    HI_U8                SaveBuf[MAX_SAVE_SIZE];    // dump stream tmp buffer
#endif
}SHARE_CONTAIN_S;

/* Share memory information */
typedef struct
{
    MEM_DESC_S           MemDesc;
    UADDR                EventList_PhyAddr;
    HI_VOID             *EventList_VirAddr;
    UADDR                ChanOption_PhyAddr;
    HI_VOID             *ChanOption_VirAddr;
    UADDR                StreamList_PhyAddr;
    HI_VOID             *StreamList_VirAddr;
    UADDR                ExtBuffer_PhyAddr;
    HI_VOID             *ExtBuffer_VirAddr;
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    UADDR                ProcBuf_PhyAddr;
    HI_VOID             *ProcBuf_VirAddr;
#endif
#if (1 == DEBUG_SAVE_SUPPORT)
    UADDR                SaveBuffer_PhyAddr;
    HI_VOID             *SaveBuffer_VirAddr;
#endif
}SHARE_MEM_INFO_S;

/* TEE communication value */
static TEEC_Context      g_TeeContext;
static TEEC_Session      g_TeeSession;

/* Static global value */
static SHARE_MEM_INFO_S  g_ShareMem;
static OSAL_SEMA         g_TvpSem;
static HI_U32            g_SecPrintEnable       = 0x0;
static HI_S32            g_SecureInstNum        = 0;
static HI_BOOL           g_bSecEnvSetUp         = HI_FALSE;
static THREAD_STATE_E    g_ThreadState          = THREAD_INVALID;
#if (1 == DEBUG_SAVE_SUPPORT)
static HI_BOOL           g_RawSaveEnable        = HI_FALSE;
static HI_CHAR           g_SavePath[PATH_LEN]   = {'/','m','n','t','\0'};
#endif
static SEC_CHAN_CTX_S    g_SecureChan[TVP_CHAN_NUM];
static CHAN_RECORD_S     g_ChanRecord[MAX_CHAN_NUM];

/* Ext callback function */
EXT_FN_EVENT_CALLBACK    g_pEventHandler        = HI_NULL;
EXT_FN_BUFFER_CALLBACK   g_pBufferHandler       = HI_NULL;


#if (1 == DEBUG_SAVE_SUPPORT)
HI_VOID TVP_VDEC_SaveStream(HI_S32 ChanID, HI_BOOL bSaveEnable, UADDR PhyAddr, HI_S32 Length)
{
    mm_segment_t oldfs;
    HI_CHAR FilePath[PATH_LEN];
    struct file **ppFile = &g_SecureChan[ChanID].pRawFile;

    if (HI_TRUE == bSaveEnable && *ppFile == HI_NULL)
    {
        snprintf(FilePath, sizeof(FilePath), "%s/secure_chan%d.raw", g_SavePath, ChanID);
        *ppFile = filp_open(FilePath, O_RDWR | O_CREAT | O_TRUNC, S_IRWXO);

        if (IS_ERR(*ppFile))
        {
            SecPrint(PRN_ERROR, "%s open raw file failed, ret=%ld\n", __func__, PTR_ERR(*ppFile));
            *ppFile = HI_NULL;
        }
        else
        {
            SecPrint(PRN_ALWS, "Start to save stream of inst_%d in %s\n", ChanID, FilePath);
        }
    }
    else if (HI_FALSE == bSaveEnable && *ppFile != HI_NULL)
    {
        filp_close(*ppFile, HI_NULL);
        *ppFile = HI_NULL;
        SecPrint(PRN_ALWS, "Stop saving stream of inst_%d.\n", ChanID);
    }

    if (*ppFile != HI_NULL)
    {
        HI_SEC_MMZ_TA2CA(PhyAddr, g_ShareMem.SaveBuffer_PhyAddr, Length);
        oldfs = get_fs();
        set_fs(KERNEL_DS);
        (*ppFile)->f_op->write(*ppFile, g_ShareMem.SaveBuffer_VirAddr, Length, &(*ppFile)->f_pos);
        set_fs(oldfs);
        SecPrint(PRN_ALWS, "Saving stream of inst_%d\n", ChanID);
    }

    return;
}
#endif

static const HI_PCHAR TVP_VDEC_Show_ChanState(CHAN_STATE_E state)
{
	switch (state)
    {
       case CHAN_INVALID:
            return "INVALID";
            break;

       case CHAN_START:
            return "START";
            break;

       case CHAN_STOP:
            return "STOP";
            break;

       default:
            return "UNKOWN";
            break;
	}
}

HI_S32 TVP_VDEC_GetChanImage( HI_S32 ChanID, IMAGE *pImage )
{
    TEEC_Result result;
    TEEC_Operation operation;
    UADDR phy_addr;

#if (1 == PRINT_TEE_TIME)
    static HI_U32 BeginTime = 0;
    static HI_U32 StartTime = 0;
    static HI_U32 EndTime = 0;
    static HI_U32 TotalTime = 0;
    static HI_U32 Count = 0;
#endif

    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    if (!g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "%s: SecureDecoder not init yet!\n", __func__);
        OSAL_UP(&g_TvpSem);
        return VDEC_ERR;
    }

    phy_addr = __pa((HI_SIZE_T)pImage);

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    operation.started = 1;
    operation.params[0].value.a = ChanID;
    operation.params[0].value.b = phy_addr;

#if (1 == PRINT_TEE_TIME)
    StartTime = OSAL_GetTimeInUs();

    if (Count == 0)
    {
        BeginTime = StartTime;
    }
#endif

    result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_GET_IMAGE, &operation, HI_NULL);
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VFMW_GETCHANIMAGE Failed!\n");
        OSAL_UP(&g_TvpSem);
        return VDEC_ERR;
    }

#if (1 == PRINT_TEE_TIME)
    EndTime = OSAL_GetTimeInUs();
    TotalTime += EndTime - StartTime;
    Count++;

    if (EndTime - BeginTime >= 1000000)
    {
        SecPrint(PRN_ALWS, "GetChanImage Total: %d, Count: %d, Avg: %d us\n", TotalTime, Count, TotalTime / Count);
        TotalTime = BeginTime = StartTime = EndTime = 0;
        Count = 0;
    }
#endif

    OSAL_UP(&g_TvpSem);
    return (operation.params[0].value.a);
}


HI_S32 TVP_VDEC_ReleaseChanImage(HI_S32 ChanID, IMAGE *pImage )
{
    TEEC_Result result;
    TEEC_Operation operation;
    HI_U32 phy_addr;

#if (1 == PRINT_TEE_TIME)
    static HI_U32 BeginTime = 0;
    static HI_U32 StartTime = 0;
    static HI_U32 EndTime = 0;
    static HI_U32 TotalTime = 0;
    static HI_U32 Count = 0;
#endif

    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    if (!g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "%s: SecureDecoder not init yet!\n", __func__);
        OSAL_UP(&g_TvpSem);
        return VDEC_ERR;
    }

    phy_addr = __pa((HI_SIZE_T)pImage);

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    operation.started = 1;
    operation.params[0].value.a = ChanID;
    operation.params[0].value.b = phy_addr;

#if (1 == PRINT_TEE_TIME)
    StartTime = OSAL_GetTimeInUs();

    if (Count == 0)
    {
        BeginTime = StartTime;
    }

#endif

    result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_RELEASE_IMAGE, &operation, HI_NULL);
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VFMW_RELEASECHANIMAGE Failed!\n");
        OSAL_UP(&g_TvpSem);
        return VDEC_ERR;
    }

#if (1 == PRINT_TEE_TIME)
    EndTime = OSAL_GetTimeInUs();
    TotalTime += EndTime - StartTime;
    Count++;

    if (EndTime - BeginTime >= 1000000)
    {
        SecPrint(PRN_ALWS, "ReleaseChanImage Total: %d, Count: %d, Avg: %d us\n", TotalTime, Count, TotalTime / Count);
        TotalTime = BeginTime = StartTime = EndTime = 0;
        Count = 0;
    }

#endif

    OSAL_UP(&g_TvpSem);
    return (operation.params[0].value.a);
}


/************************************************************************
   安全共享码流链表: 读取码流
 ************************************************************************/
HI_S32 TVP_VDEC_ReadStream(HI_VOID)
{
    HI_S32 ret;
    HI_S32 ChanID;
    HI_S32 InstID;
    EXT_FN_READ_STREAM pfnReadStream = HI_NULL;
    STREAM_DATA_S *pStrRawPacket = HI_NULL;
    SHARE_RAW_ARRAY_S *pStreamBuf = (SHARE_RAW_ARRAY_S *)g_ShareMem.StreamList_VirAddr;

    if (HI_NULL == pStreamBuf)
    {
        SecPrint(PRN_FATAL, "%s FATAL: pStreamBuf = NULL\n", __func__);
        return HI_FAILURE;
    }
    
    for (ChanID = 0; ChanID < TVP_CHAN_NUM; ChanID++)
    {
        OSAL_DOWN_INTERRUPTIBLE(&g_SecureChan[ChanID].ChanSema);
         
        if (CHAN_START == g_ChanRecord[ChanID].ChanState)
        {
            InstID        = g_SecureChan[ChanID].StreamIntf.stream_provider_inst_id;
            pfnReadStream = g_SecureChan[ChanID].StreamIntf.read_stream;
            if (HI_NULL == pfnReadStream)
            {
                SecPrint(PRN_FATAL, "%s FATAL: Chan %d read_stream = NULL\n", __func__, ChanID);
                OSAL_UP(&g_SecureChan[ChanID].ChanSema);
                return HI_FAILURE;
            }
           
            while (1)
            {
                if (((pStreamBuf[ChanID].Head_NS + 1) % MAX_RAW_NUM) != pStreamBuf[ChanID].Tail_NS)
                {
                    pStrRawPacket = &(pStreamBuf[ChanID].RawPacket[pStreamBuf[ChanID].Head_NS]);

                    ret = pfnReadStream(InstID, pStrRawPacket);
                    if (HI_SUCCESS == ret)
                    {
                        pStreamBuf[ChanID].Head_NS = (pStreamBuf[ChanID].Head_NS + 1) % MAX_RAW_NUM;

                    #if (1 == DEBUG_SAVE_SUPPORT)
                        TVP_VDEC_SaveStream(ChanID, g_RawSaveEnable, pStrRawPacket->PhyAddr, pStrRawPacket->Length);
                    #endif
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            OSAL_UP(&g_SecureChan[ChanID].ChanSema);
        }
    }
    
    return HI_SUCCESS;
}


/************************************************************************
   安全共享码流链表: 释放码流
 ************************************************************************/
HI_S32 TVP_VDEC_ReleaseStream(HI_VOID)
{
    HI_S32 ret;
    HI_S32 ChanID;
    HI_S32 InstID;
    EXT_FN_RELEASE_STREAM pfnReleaseStream = HI_NULL;
    STREAM_DATA_S *pStrRawPacket = HI_NULL;
    SHARE_RAW_ARRAY_S *pStreamBuf = (SHARE_RAW_ARRAY_S *)g_ShareMem.StreamList_VirAddr;
    
    if (HI_NULL == pStreamBuf)
    {
        SecPrint(PRN_FATAL, "%s FATAL: pStreamBuf = NULL\n", __func__);
        return HI_FAILURE;
    }
    
    for (ChanID = 0; ChanID < TVP_CHAN_NUM; ChanID++)
    {
        OSAL_DOWN_INTERRUPTIBLE(&g_SecureChan[ChanID].ChanSema);
        
        if (CHAN_INVALID != g_ChanRecord[ChanID].ChanState)
        {
            InstID           = g_SecureChan[ChanID].StreamIntf.stream_provider_inst_id;
            pfnReleaseStream = g_SecureChan[ChanID].StreamIntf.release_stream;
            if (HI_NULL == pfnReleaseStream)
            {
                SecPrint(PRN_FATAL, "%s FATAL: Chan %d release_stream = NULL\n", __func__, ChanID);
                OSAL_UP(&g_SecureChan[ChanID].ChanSema);
                return HI_FAILURE;
            }
        
            while (1)
            {
                if (pStreamBuf[ChanID].Tail_NS != pStreamBuf[ChanID].Tail_S)
                {
                    pStrRawPacket = &(pStreamBuf[ChanID].RawPacket[pStreamBuf[ChanID].Tail_NS]);

                    ret = pfnReleaseStream(InstID, pStrRawPacket);
                    if (HI_SUCCESS == ret)
                    {
                        //SecPrint(PRN_FATAL, "pStreamBuf[%d].Tail_S = %d Tail_NS = %d \n", ChanID, pStreamBuf[ChanID].Tail_S, pStreamBuf[ChanID].Tail_NS);
                        pStreamBuf[ChanID].Tail_NS = (pStreamBuf[ChanID].Tail_NS + 1) % MAX_RAW_NUM;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            OSAL_UP(&g_SecureChan[ChanID].ChanSema);
        }
    }
    
    return HI_SUCCESS;
}

/************************************************************************
   安全共享消息链表: 处理消息
 ************************************************************************/
HI_S32 TVP_VDEC_ReportEvent(HI_VOID)
{
    SHARE_EVENT_ARRAY_S *pEventBuf = (SHARE_EVENT_ARRAY_S *)g_ShareMem.EventList_VirAddr;
        
    if (HI_NULL == pEventBuf || HI_NULL == g_pEventHandler)
    {
        SecPrint(PRN_FATAL, "%s FATAL: pEventBuf(%p)/g_pEventHandler(%p) = NULL\n", __func__, pEventBuf, g_pEventHandler);
        return HI_FAILURE;
    }
    
    while (pEventBuf->Tail != pEventBuf->Head)
    {
        if (pEventBuf->Message[pEventBuf->Tail].IsValid)
        {
            //HI_FATAL_VFMW("Event Pointer:%p\n", (HI_U8 *)pEventBuf->Message[pEventBuf->Head].para);

            g_pEventHandler(pEventBuf->Message[pEventBuf->Tail].ChanID,
                            pEventBuf->Message[pEventBuf->Tail].Type,
                            (HI_U8 *)pEventBuf->Message[pEventBuf->Tail].para, MAX_PARA_SIZE);
        }

        pEventBuf->Tail = (pEventBuf->Tail + 1) % MAX_EVENT_NUM;
    }
    
    return HI_SUCCESS;
}


/************************************************************************
   非安全侧线程，管理码流和callback信息
 ************************************************************************/
HI_S32 TVP_VDEC_MiddleWare(HI_VOID *pArgs)
{
    HI_S32 ret;
    TEEC_Result    result;
    TEEC_Operation operation;

#if (1 == PRINT_TEE_TIME)
    static HI_U32 BeginTime = 0;
    static HI_U32 StartTime = 0;
    static HI_U32 EndTime   = 0;
    static HI_U32 TotalTime = 0;
    static HI_U32 Count     = 0;
#endif

    while (1)
    {
        switch (g_ThreadState)
        {
            case THREAD_RUN:
                break;

            case THREAD_SLEEP:
                goto sleep;

            case THREAD_EXIT:
                goto exit;

            default:
                break;
        }

        /*读码流*/
        ret = TVP_VDEC_ReadStream();
        if (ret != HI_SUCCESS)
        {
            SecPrint(PRN_FATAL, "%s ReadStream FATAL occur!\n", __func__);
            goto exit;
        }

#if (1 == PRINT_TEE_TIME)
        StartTime = OSAL_GetTimeInUs();
        if (0 == Count)
        {
            BeginTime = StartTime;
        }
#endif

        /*调用安全侧的主线程函数*/
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
        operation.started = 1;
        operation.params[0].value.a = 0;
        operation.params[0].value.b = 0;
        result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_RUN_PROCESS, &operation, HI_NULL);
        if (TEEC_SUCCESS != result)
        {
            SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VFMW_THREADPROC Failed!\n");
            goto exit;
        }

#if (1 == PRINT_TEE_TIME)
        EndTime = OSAL_GetTimeInUs();
        TotalTime += EndTime - StartTime;
        Count++;

        if (EndTime - BeginTime >= 1000000)
        {
            SecPrint(PRN_ALWS, "THREADPROC Total: %d, Count: %d, Avg: %d us\n", TotalTime, Count, TotalTime / Count);
            TotalTime = BeginTime = StartTime = EndTime = 0;
            Count = 0;
        }
#endif

        /* 处理上报信息*/
        ret = TVP_VDEC_ReportEvent();
        if (ret != HI_SUCCESS)
        {
            SecPrint(PRN_FATAL, "%s ReportEvent FATAL occur!\n", __func__);
            goto exit;
        }

        /*释放码流*/
        ret = TVP_VDEC_ReleaseStream(); 
        if (ret != HI_SUCCESS)
        {
            SecPrint(PRN_FATAL, "%s ReleaseStream FATAL occur!\n", __func__);
            goto exit;
        }       

    sleep:
        OSAL_MSLEEP(10);
    }

exit:
    g_ThreadState = THREAD_INVALID;
    return VDEC_OK;
}

/************ synchronize ext buffer *******************/
HI_S32 TVP_VDEC_FindExtBuffer(SHARE_EXTBUF_ARRAY_S *pArray, UADDR PhyAddr)
{
    UINT32 i;
    HI_S32 pos = -1;

    for (i=0; i<MAX_FRAME_NUM; i++)
    {
        if (PhyAddr == pArray->PhyAddr[i])
        {
            pos = i;
            break;
        }
    }

    return pos;
}

/************ synchronize ext buffer *******************/
HI_S32 TVP_VDEC_SyncExtBuffer(HI_S32 ChanID, EXTBUF_PARAM_S *pParam)
{
    UADDR TargetPhyAddr = 0;
    HI_S32 pos = -1;
    SHARE_EXTBUF_ARRAY_S *pArray = (SHARE_EXTBUF_ARRAY_S *)g_ShareMem.ExtBuffer_VirAddr;

    if (NULL == pParam || NULL == pArray)
    {
        SecPrint(PRN_FATAL, "%s pParam(%p)/pArray(%p) = null!\n", __func__, pParam, pArray);
        return VDEC_ERR;
    }

    if (ChanID < 0 || ChanID >= TVP_CHAN_NUM)
    {
        dprint(PRN_ERROR, "%s ChanID %d invalid!\n", __func__, ChanID);
        return VDEC_ERR;
    }

    pArray = &(pArray[ChanID]);
    
    // find an empty position if state = EXTBUF_INSERT
    TargetPhyAddr = (EXTBUF_INSERT == pParam->State)? 0: pParam->PhyAddr;
    
    // find target position in array
    pos = TVP_VDEC_FindExtBuffer(pArray, 0);
    if (pos < 0 || pos >= MAX_FRAME_NUM)
    {
        dprint(PRN_ERROR, "%s ChanID %d can not find the position for target %x\n", __func__, ChanID, TargetPhyAddr);
        return VDEC_ERR;
    }
    
    if (EXTBUF_INSERT == pParam->State)
    {
        pArray->State[pos]   = pParam->State;
        pArray->PhyAddr[pos] = pParam->PhyAddr;
        pArray->TotalNum++;
    }
    else if (EXTBUF_NULL == pParam->State)
    {
        pArray->State[pos]   = pParam->State;
        pArray->PhyAddr[pos] = 0;
        pArray->TotalNum--;
    }
    else
    {
        pArray->State[pos]   = pParam->State;
    }

    return HI_SUCCESS;
}

/************create thread*******************/
HI_S32 TVP_VDEC_Thread_Init(HI_VOID)
{
    OSAL_TASK pTask = HI_NULL;

    OSAL_CreateTask(&pTask, "SecVideoDec", TVP_VDEC_MiddleWare);

    if ( HI_NULL == pTask)
    {
        SecPrint(PRN_FATAL, "Create thread SecVideoDec Failed!\n");
        return VDEC_ERR;
    }

    g_ThreadState = THREAD_SLEEP;

    return VDEC_OK;
}

/************reset chan clear stream*******************/
HI_S32 TVP_VDEC_ClearStream(HI_S32 ChanID)
{
    HI_S32 ret;
    HI_S32 InstID;
    EXT_FN_RELEASE_STREAM pfnReleaseStream = HI_NULL;
    STREAM_DATA_S *pStrRawPacket = HI_NULL;
    SHARE_RAW_ARRAY_S *pStreamBuf = (SHARE_RAW_ARRAY_S *)g_ShareMem.StreamList_VirAddr;

    pfnReleaseStream = g_SecureChan[ChanID].StreamIntf.release_stream;
    if (HI_NULL == pStreamBuf || HI_NULL == pfnReleaseStream)
    {
        SecPrint(PRN_FATAL, "%s FATAL: Chan %d pStreamBuf(%p)/pfnReleaseStream(%p) = NULL\n", __func__, ChanID, pStreamBuf, pfnReleaseStream);
        return HI_FAILURE;
    }
    
    /*清还未被安全侧读取的码流*/
    InstID = g_SecureChan[ChanID].StreamIntf.stream_provider_inst_id;
    while (1)
    {
        if (pStreamBuf[ChanID].Tail_NS != pStreamBuf[ChanID].Head_NS)
        {
            pStrRawPacket = &(pStreamBuf[ChanID].RawPacket[pStreamBuf[ChanID].Tail_NS]);

            ret = pfnReleaseStream(InstID, pStrRawPacket);
            if (HI_SUCCESS == ret)
            {
                pStreamBuf[ChanID].Tail_NS = (pStreamBuf[ChanID].Tail_NS + 1) % MAX_RAW_NUM;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    memset(&pStreamBuf[ChanID], 0, sizeof(SHARE_RAW_ARRAY_S));

    return HI_SUCCESS;
}

/********清相应通道的event消息******/
HI_S32 TVP_VDEC_ClearEvent(HI_S32 ChanID)
{
    HI_S32 Tail;
    SHARE_EVENT_ARRAY_S *pEventBuf = (SHARE_EVENT_ARRAY_S *)g_ShareMem.EventList_VirAddr;
        
    Tail = pEventBuf->Tail;
  
    if (HI_NULL != pEventBuf)
    {
        while (Tail != pEventBuf->Head)
        {
            if (ChanID == pEventBuf->Message[Tail].ChanID)
            {
                pEventBuf->Message[Tail].IsValid = 0;
            }

            Tail = (Tail + 1) % MAX_EVENT_NUM;
        }
    }
    else
    {
        SecPrint(PRN_FATAL, "%s FATAL: pEventBuf = NULL\n", __func__);
    }

    return VDEC_OK;
}

HI_S32 TVP_VDEC_Suspend(HI_VOID)
{
    TEEC_Result result;
    TEEC_Operation operation;
    HI_S32 ret;

    ret = VDEC_Suspend();
    if (ret != VDEC_OK)
    {
        SecPrint(PRN_ERROR, "%s Call VDEC_Suspend Failed!\n", __func__);
    }

    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    if (HI_TRUE == g_bSecEnvSetUp)
    {
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

        operation.started = 1;
        operation.params[0].value.a = 0;
        operation.params[0].value.b = TEEC_VALUE_UNDEF;

        result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_SUSPEND, &operation, HI_NULL);
        if (result != TEEC_SUCCESS)
        {
            SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VDEC_SUSPEND Failed!\n");
            OSAL_UP(&g_TvpSem);
        }

        g_ThreadState = THREAD_SLEEP;
        ret = operation.params[0].value.a;
    }

    OSAL_UP(&g_TvpSem);
    
    return ret;
}

HI_S32 TVP_VDEC_Resume(HI_VOID)
{
    HI_S32 ret;
    TEEC_Result result;
    TEEC_Operation operation;
    
    ret = VDEC_Resume();
    if (ret != VDEC_OK)
    {
        SecPrint(PRN_ERROR, "%s Call VDEC_Resume Failed!\n", __func__);
    }

    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    if (HI_TRUE == g_bSecEnvSetUp)
    {
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

        operation.started = 1;
        operation.params[0].value.a = 0;
        operation.params[0].value.b = TEEC_VALUE_UNDEF;

        result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_RESUME, &operation, HI_NULL);
        if (result != TEEC_SUCCESS)
        {
            SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VDEC_RESUME Failed!\n");
            OSAL_UP(&g_TvpSem);
        }

        g_ThreadState = THREAD_RUN;
        ret = operation.params[0].value.a;
    }

    OSAL_UP(&g_TvpSem);

    return ret;
}

HI_S32 TVP_VDEC_NormalControl(HI_S32 ChanID, VDEC_CID_E eCmdID, HI_VOID *pArgs, HI_U32 ArgLen)
{
    HI_S32     ret     = VDEC_ERR;
    HI_SIZE_T *p32     = NULL;
    HI_S32     chan_id = 0;
    
    ret = VDEC_Control(ChanID, eCmdID, pArgs, ArgLen);

    if (VDEC_OK == ret)
    {
        switch (eCmdID)
        {
            case VDEC_CID_CREATE_CHAN:
            case VDEC_CID_CREATE_CHAN_WITH_OPTION:
                p32 = (HI_SIZE_T *)pArgs;
                chan_id = p32[0];
                
                if (chan_id < TVP_CHAN_NUM || chan_id >= MAX_CHAN_NUM)
                {
                    SecPrint(PRN_FATAL, "%s FATAL: return chan_id(%d) invalid\n", __func__, chan_id);
                    return VDEC_ERR;
                }
                
                memset(&g_ChanRecord[chan_id], 0, sizeof(CHAN_RECORD_S));
                g_ChanRecord[chan_id].ChanID     = chan_id;
                g_ChanRecord[chan_id].bIsSecMode = HI_FALSE;
                g_ChanRecord[chan_id].ChanState  = CHAN_CREATE;
                break;

            case VDEC_CID_START_CHAN:
                g_ChanRecord[ChanID].ChanState = CHAN_START;
                break;

            case VDEC_CID_STOP_CHAN:
                g_ChanRecord[ChanID].ChanState = CHAN_STOP;
                break;

            case VDEC_CID_DESTROY_CHAN:
            case VDEC_CID_DESTROY_CHAN_WITH_OPTION:
                g_ChanRecord[ChanID].ChanState = CHAN_INVALID;
                break;

            default:
                break;
        }
    }
    
    return ret;
}


HI_S32 TVP_VDEC_SecureControl(HI_S32 ChanID, VDEC_CID_E eCmdID, HI_VOID *pArgs, HI_U32 ArgLen)
{
    TEEC_Result    result;
    TEEC_Operation operation;
    IMAGE_INTF_S  *pImgIntf;
	STREAM_INTF_S  StreamIntf;
    VDEC_CHAN_RESET_OPTION_S *opt;
    HI_S32     ret       = VDEC_ERR;
    UADDR      phy_addr  = 0;
    HI_VOID   *vir_addr  = NULL;
    HI_SIZE_T *p32       = NULL;
    HI_S32     chan_id   = 0;
    
#if (1 == PRINT_TEE_TIME)
    static HI_U32 BeginTime = 0;
    static HI_U32 StartTime = 0;
    static HI_U32 EndTime   = 0;
    static HI_U32 TotalTime = 0;
    static HI_U32 Count     = 0;
#endif
    
    SecPrint(PRN_ERROR, "Secure Command: ChanId = %d, CmdID = %d\n", ChanID, eCmdID);

    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    if (HI_FALSE == g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "%s: SecureDecoder not init yet!\n", __func__);
        OSAL_UP(&g_TvpSem);
        return VDEC_ERR;
    }

    switch (eCmdID)
    {
        case VDEC_CID_SYNC_EXT_BUFFER:
            return TVP_VDEC_SyncExtBuffer(ChanID, (EXTBUF_PARAM_S *)pArgs);
            
        case VDEC_CID_CREATE_CHAN_WITH_OPTION:
        case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
            p32      = (HI_SIZE_T *)pArgs;
            vir_addr = (HI_VOID *)p32[1];
            p32[1]   = g_ShareMem.ChanOption_PhyAddr;
            memcpy(g_ShareMem.ChanOption_VirAddr, vir_addr, sizeof(VDEC_CHAN_OPTION_S));
            SecPrint(PRN_ALWS, "%s cmd %d, p32[0] = %x, p32[1] = %x\n", __func__, eCmdID, p32[0], p32[1]);
            break;

        case VDEC_CID_SET_STREAM_INTF:  /* 设置通道的码流接口 */
            if (HI_NULL != pArgs)
            {
                memcpy(&g_SecureChan[ChanID].StreamIntf, (STREAM_INTF_S *)pArgs, sizeof(STREAM_INTF_S));
                memset(&StreamIntf, 0, sizeof(STREAM_INTF_S));
                StreamIntf.stream_provider_inst_id = ChanID;
                phy_addr = __pa((HI_SIZE_T)&StreamIntf);
            }
            else
            {
                SecPrint(PRN_FATAL, "VDEC_CID_SET_STREAM_INTF Invalid Param\n");
                goto Exit_Entry;
            }

            break;

        case VDEC_CID_GET_IMAGE_INTF:  /* 获取通道的图象接口 */
            if (HI_NULL != pArgs)
            {
                pImgIntf = (IMAGE_INTF_S *)pArgs;
                pImgIntf->image_provider_inst_id = ChanID;
                pImgIntf->read_image    = TVP_VDEC_GetChanImage;
                pImgIntf->release_image = TVP_VDEC_ReleaseChanImage;
                ret = VDEC_OK;
            }
            else
            {
                SecPrint(PRN_FATAL, "VDEC_CID_GET_IMAGE_INTF Invalid Param\n");
            }

            goto Exit_Entry;
            break;
            
        default:
            break;
    }

    if (0 == phy_addr && NULL != pArgs)
    {
        phy_addr = __pa((HI_SIZE_T)pArgs);
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE);
    operation.params[0].value.a = ChanID;
    operation.params[0].value.b = eCmdID;
    operation.params[1].value.a = phy_addr;
    operation.params[1].value.b = ArgLen;

#if (1 == PRINT_TEE_TIME)
    StartTime = OSAL_GetTimeInUs();

    if (Count == 0)
    {
        BeginTime = StartTime;
    }
#endif

    result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_CONTROL, &operation, HI_NULL);
    if (TEEC_SUCCESS != result)
    {
        SecPrint(PRN_FATAL, "TEEC_InvokeCommand VFMW_CMD_ID_VDEC_CONTROL Failed!\n");
        goto Exit_Entry;
    }

#if (1 == PRINT_TEE_TIME)
    EndTime = OSAL_GetTimeInUs();
    TotalTime += EndTime - StartTime;
    Count++;

    if (EndTime - BeginTime >= 1000000)
    {
        SecPrint(PRN_ALWS, "Control Total: %d, Count: %d, Avg: %d us\n", TotalTime, Count, TotalTime / Count);
        TotalTime = BeginTime = StartTime = EndTime = 0;
        Count = 0;
    }
#endif

    ret = operation.params[0].value.a;

    switch (eCmdID)
    {
        case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
            if (HI_NULL != vir_addr)
            {
                memcpy(vir_addr, g_ShareMem.ChanOption_VirAddr, sizeof(VDEC_CHAN_OPTION_S));
                p32[1] = (HI_SIZE_T)vir_addr;
            }
            break;
            
        case VDEC_CID_CREATE_CHAN_WITH_OPTION:
            if (VDEC_OK == ret)
            {
                chan_id = p32[0];
                SecPrint(PRN_ALWS, "%s cmd %d, return chan_id = %d\n", __func__, eCmdID, chan_id);
                
                if (chan_id < 0 || chan_id >= TVP_CHAN_NUM)
                {
                    SecPrint(PRN_FATAL, "%s FATAL: return chan_id(%d) invalid!\n", __func__, chan_id);
                    ret = VDEC_ERR;
                    goto Exit_Entry;
                }
                
                memset(&g_ChanRecord[chan_id], 0, sizeof(CHAN_RECORD_S));
                g_ChanRecord[chan_id].ChanID     = chan_id;
                g_ChanRecord[chan_id].bIsSecMode = HI_TRUE;
                g_ChanRecord[chan_id].ChanState  = CHAN_CREATE;
                
                memset(&g_SecureChan[chan_id], 0, sizeof(SEC_CHAN_CTX_S));
                g_SecureChan[chan_id].ChanID     = chan_id;
                OSAL_SEMA_INTIT(&g_SecureChan[chan_id].ChanSema);
                g_SecureInstNum++;
            }

            if (HI_NULL != vir_addr)
            {
                memcpy(vir_addr, g_ShareMem.ChanOption_VirAddr, sizeof(VDEC_CHAN_OPTION_S));
                p32[1] = (HI_SIZE_T)vir_addr;
            }
            break;

        case VDEC_CID_START_CHAN:
            g_ChanRecord[ChanID].ChanState = CHAN_START;
            g_ThreadState = THREAD_RUN;
            break;

        case VDEC_CID_STOP_CHAN:
            g_ChanRecord[ChanID].ChanState = CHAN_STOP;
            for (chan_id = 0; chan_id < TVP_CHAN_NUM; chan_id++)
            {
                if (CHAN_START == g_ChanRecord[chan_id].ChanState)
                {
                    break;
                }
            }
            // All secure chan stop, thread turn to sleep
            if (chan_id >= MAX_CHAN_NUM)
            {
                g_ThreadState = THREAD_SLEEP;
            }
            break;

        case VDEC_CID_RESET_CHAN:
            OSAL_DOWN_INTERRUPTIBLE(&g_SecureChan[ChanID].ChanSema);
            TVP_VDEC_ClearEvent(ChanID);
            TVP_VDEC_ClearStream(ChanID);
            OSAL_UP(&g_SecureChan[ChanID].ChanSema);
            break;

        case VDEC_CID_RESET_CHAN_WITH_OPTION:
            opt = (VDEC_CHAN_RESET_OPTION_S *)pArgs;
            
            OSAL_DOWN_INTERRUPTIBLE(&g_SecureChan[ChanID].ChanSema);
            TVP_VDEC_ClearEvent(ChanID);
            if (opt->s32KeepBS == 0)
            {
                TVP_VDEC_ClearStream(ChanID);//释放还未被安全侧读取的码流
            }
            OSAL_UP(&g_SecureChan[ChanID].ChanSema);
            break;
            
        case VDEC_CID_DESTROY_CHAN:
        case VDEC_CID_DESTROY_CHAN_WITH_OPTION:
            OSAL_DOWN_INTERRUPTIBLE(&g_SecureChan[ChanID].ChanSema);
            TVP_VDEC_ClearEvent(ChanID);
            TVP_VDEC_ClearStream(ChanID);
    
            g_SecureInstNum--;
    
            if (g_SecureInstNum <= 0)
            {
                g_SecureInstNum = 0;
                g_ThreadState = THREAD_SLEEP;
            }
            
#if (1 == DEBUG_SAVE_SUPPORT)
            if (g_SecureChan[ChanID].pRawFile != HI_NULL)
            {
                filp_close(g_SecureChan[ChanID].pRawFile, HI_NULL);
                g_SecureChan[ChanID].pRawFile = HI_NULL;
            }
#endif
    
            g_ChanRecord[ChanID].ChanState = CHAN_INVALID;
            OSAL_UP(&g_SecureChan[ChanID].ChanSema);
            break;

        default:
            break;
    }

Exit_Entry:
    OSAL_UP(&g_TvpSem);
    
    SecPrint(PRN_ERROR, "Secure Command: ChanId = %d, CmdID = %d, Ret = %d\n", ChanID, eCmdID, ret);
    return ret;
}


/************************************************************************
    VDEC控制引擎
    ChanID:  需要操作的通道号(对于通道无关操作，此参数可为任意值)
    eCmdID:  命令编码，指定需要VDEC执行何种动作
    pArgs:   命令参数，其格式与eCmdID相关
    ArgLen:  参数长度
 ************************************************************************/
HI_S32 TVP_VDEC_Control(HI_S32 ChanID, VDEC_CID_E eCmdID, HI_VOID *pArgs, HI_U32 ArgLen)
{
    HI_U8  IsSecFlag = 0;
    HI_S32 ret = VDEC_ERR;

    if(-1 != ChanID)
    {
        IsSecFlag = g_ChanRecord[ChanID].bIsSecMode;
    }
    else
    {
        if (VDEC_CID_CREATE_CHAN == eCmdID      || VDEC_CID_CREATE_CHAN_WITH_OPTION == eCmdID 
         || VDEC_CID_GET_CHAN_MEMSIZE == eCmdID || VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION == eCmdID)
        {
            IsSecFlag = ((VDEC_CHAN_OPTION_S *)((HI_SIZE_T *)pArgs)[1])->u32IsSecMode;
        }
    }

    if (IsSecFlag)
    {
        ret = TVP_VDEC_SecureControl(ChanID, eCmdID, pArgs, ArgLen);
    }
    else
    {
        ret = TVP_VDEC_NormalControl(ChanID, eCmdID, pArgs, ArgLen);
    }

    return ret;
}

#ifndef  HI_ADVCA_FUNCTION_RELEASE
static inline HI_S32 TVP_VDEC_String2Value(HI_PCHAR str, HI_U32 *data)
{
    HI_U32 i, d, dat, weight;

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
        if (str[i] < 0x20)
        {
            break;
        }
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

HI_VOID TVP_VDEC_HelpProc(HI_VOID)
{
    SecPrint(PRN_ALWS, "\n");
    SecPrint(PRN_ALWS, "================= SEC_VFMW HELP =================\n");
    SecPrint(PRN_ALWS, "USAGE:echo [cmd] [para] >/proc/sec_vfmw\n");
    SecPrint(PRN_ALWS, "  help,     [not_care]    :read help infomation\n");
    SecPrint(PRN_ALWS, "  saveraw,  [start/stop]  :enable/disable raw save,debug only\n");
    SecPrint(PRN_ALWS, "  saveyuv,  [start/stop]  :enable/disable yuv save,debug only\n");
    SecPrint(PRN_ALWS, "\n");
    SecPrint(PRN_ALWS, "Further command avalible in trusted decoder:\n");
    SecPrint(PRN_ALWS, "  0x0,      [print_word]  :set print enable word\n");
    SecPrint(PRN_ALWS, "  0x2,      [0~100]       :set err thr\n");
    SecPrint(PRN_ALWS, "  0x4,      [0/1]         :set output order(0/1=DISP/DEC)\n");
    SecPrint(PRN_ALWS, "  0x5,      [0/1/2]       :set dec mode(0/1/2=IPB/IP/I)\n");
    SecPrint(PRN_ALWS, "  0x7,      [0~100]       :set discard before dec thr\n");
    SecPrint(PRN_ALWS, "  0xb,      [0/1]         :set frame/adaptive(0/1) storage\n");
    SecPrint(PRN_ALWS, "  0xd,      [8~15]        :set to abserve specify channel\n");
    SecPrint(PRN_ALWS, "  0x400,    [ms]          :set dec task schedule delay\n");
    SecPrint(PRN_ALWS, "  0x402,    [0/1]         :start/stop syntax proccess\n");
    SecPrint(PRN_ALWS, "  0x501,    [ms]          :set scd state period\n");
    SecPrint(PRN_ALWS, "  0x502,    [ms]          :set vdh state period\n");
    SecPrint(PRN_ALWS, "  0x503,    [ms]          :set rcv/rls frame period\n");
    SecPrint(PRN_ALWS, "=================================================\n");
    SecPrint(PRN_ALWS, "\n");

    return;
}

HI_S32 TVP_VDEC_ParamProccess(const HI_S8 __user *buffer, size_t count, HI_U32 *p_option, HI_U32 *p_value)
{
    HI_S32  i, j;
    HI_S32  ret = HI_FAILURE;
    HI_CHAR buf[PROC_CMD_LEN * 2];
    HI_CHAR str1[PROC_CMD_LEN];
    HI_CHAR str2[PROC_CMD_LEN];

    if (count < 1 || count >= sizeof(buf))
    {
        SecPrint(PRN_ALWS, "Parameter count(%ld) Invalid!\n", count);
        return HI_FAILURE;
    }

    memset(buf, 0, sizeof(buf));

    if (copy_from_user(buf, buffer, count))
    {
        SecPrint(PRN_ALWS, "Copy from user Failed!\n");
        return HI_FAILURE;
    }

    buf[count] = 0;

    /* 1.读取参数1 */
    i = 0;
    j = 0;

    for (; i < count; i++)
    {
        if (j == 0 && buf[i] == ' ')
        {
            continue;
        }

        if (buf[i] > ' ')
        {
            str1[j++] = buf[i];
        }

        if (j > 0 && buf[i] == ' ')
        {
            break;
        }
    }

    str1[j] = 0;

    /* 2.读取参数2 */
    j = 0;

    for (; i < count; i++)
    {
        if (j == 0 && buf[i] == ' ')
        {
            continue;
        }

        if (buf[i] > ' ')
        {
            str2[j++] = buf[i];
        }

        if (j > 0 && buf[i] == ' ')
        {
            break;
        }
    }

    str2[j] = 0;

    /* 3.参数判断 */
    if (!strncmp(str1, PROC_CMD_HELP, PROC_CMD_LEN))
    {
        TVP_VDEC_HelpProc();
    }

#if (1 == DEBUG_SAVE_SUPPORT)
    else if (!strncmp(str1, PROC_CMD_SAVERAW, PROC_CMD_LEN))
    {
        if (!strncmp(str2, PROC_CMD_START, PROC_CMD_LEN))
        {
            SecPrint(PRN_ALWS, "Enable Raw Stream Save.\n");
            g_RawSaveEnable = HI_TRUE;
        }
        else if (!strncmp(str2, PROC_CMD_STOP, PROC_CMD_LEN))
        {
            SecPrint(PRN_ALWS, "Disable Raw Stream Save.\n");
            g_RawSaveEnable = HI_FALSE;
        }
    }

#endif
    else if (!strncmp(str1, PROC_CMD_SUSPEND, PROC_CMD_LEN))
    {
        TVP_VDEC_Suspend();
    }
    else if (!strncmp(str1, PROC_CMD_RESUME, PROC_CMD_LEN))
    {
        TVP_VDEC_Resume();
    }
    else
    {
        /*转化参数1*/
        if (TVP_VDEC_String2Value(str1, p_option) != 0)
        {
            SecPrint(PRN_ALWS, "Unknown param %s\n", str1);
        }
        /*转化参数2*/
        else if (TVP_VDEC_String2Value(str2, p_value) != 0)
        {
            SecPrint(PRN_ALWS, "Unknown param %s\n", str2);
        }
        /*两个参数都有效*/
        else
        {
            switch (*p_option)
            {
                case PROC_CMD_SETPRINT:
                    g_SecPrintEnable = *p_value;
                    SecPrint(PRN_ALWS, "Set SecPrintEnable = 0x%x\n", g_SecPrintEnable);
                    break;
                    
                default: /*默认参数必需通过TEE传递*/
                    if (HI_FALSE == g_bSecEnvSetUp)
                    {
                        SecPrint(PRN_ALWS, "%s: SecureDecoder not init yet!\n", __func__);
                    }

                    break;
            }

            /*安全解码器有效时才返回HI_SUCCESS*/
            if (HI_TRUE == g_bSecEnvSetUp)
            {
                ret = HI_SUCCESS;
            }
        }
    }

    return ret;
}

HI_S32 TVP_VDEC_SendProcCommand(HI_U32 option, HI_U32 value)
{
    TEEC_Result result;
    TEEC_Operation operation;

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;
    operation.params[0].value.a = option;
    operation.params[0].value.b = value;

    result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_WRITE_PROC, &operation, HI_NULL);
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_ALWS, "InvokeCommand VFMW_CMD_ID_VFMW_WRITEPROC Failed!\n");
        return VDEC_ERR;
    }

    return operation.params[0].value.a;
}

static HI_S32 TVP_VDEC_ReadProc(struct seq_file *p, HI_VOID *v)
{
    HI_U32 i;
    TEEC_Result result;  
    TEEC_Operation operation; 
    SHARE_RAW_ARRAY_S *pStreamBuf = HI_NULL;
    
    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    //在没启动解码器之前应该允许查询部分信息
    PROC_PRINT(p, "\n");
    PROC_PRINT(p, "======================= Global Info ========================\n");
    PROC_PRINT(p, "SecEnvSetUp      :%-7d  | SecPrintEnable      :0x%-5x\n", g_bSecEnvSetUp,  g_SecPrintEnable);
    PROC_PRINT(p, "ThreadState      :%-7d  | ShareMemPhyAddr     :0x%-5x\n", g_ThreadState,   g_ShareMem.MemDesc.PhyAddr);
    PROC_PRINT(p, "SecureInstNum    :%-7d  | ShareMemLength      :%d\n",     g_SecureInstNum, g_ShareMem.MemDesc.Length);

#if (1 == DEBUG_SAVE_SUPPORT)
    PROC_PRINT(p, "RawSaveEnable    :%-7d  | SavePath            :%s\n",     g_RawSaveEnable, g_SavePath);
#endif
    PROC_PRINT(p, "\n");
    
    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (g_ChanRecord[i].ChanState != CHAN_INVALID)
        {
    		PROC_PRINT(p, "Chan %d\n", i);
    		PROC_PRINT(p, "State            :%-7s  | SecMode             :%d\n", TVP_VDEC_Show_ChanState(g_ChanRecord[i].ChanState), g_ChanRecord[i].bIsSecMode);

            if (HI_TRUE == g_ChanRecord[i].bIsSecMode)
            {
                pStreamBuf = (SHARE_RAW_ARRAY_S *)g_ShareMem.StreamList_VirAddr;
                if (pStreamBuf != NULL)
                {
    		    PROC_PRINT(p, "StreamList       : %d/%d (%d,%d,%d,%d)\n", 
                           (pStreamBuf[i].Head_S  - pStreamBuf[i].Tail_S  + MAX_RAW_NUM) % MAX_RAW_NUM,
                           (pStreamBuf[i].Head_NS - pStreamBuf[i].Tail_NS + MAX_RAW_NUM) % MAX_RAW_NUM,
                            pStreamBuf[i].Head_S,   pStreamBuf[i].Tail_S, 
                            pStreamBuf[i].Head_NS,  pStreamBuf[i].Tail_NS);
                }
            }
        }
    }

    PROC_PRINT(p, "\n");
    if (g_bSecEnvSetUp && g_SecureInstNum > 0)
    {
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
        operation.started = 1;
        operation.params[0].value.a = g_ShareMem.ProcBuf_PhyAddr;
        operation.params[0].value.b = MAX_PROC_SIZE;

        result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_READ_PROC, &operation, HI_NULL);
        if (result != TEEC_SUCCESS)
        {
            SecPrint(PRN_ALWS, "InvokeCommand VFMW_CMD_ID_VFMW_READPROC Failed!\n");
            OSAL_UP(&g_TvpSem);
            return VDEC_ERR;
        }

        PROC_PRINT(p, g_ShareMem.ProcBuf_VirAddr);
    }
    else
    {
        PROC_PRINT(p, " No secure channel.\n");
    }

    PROC_PRINT(p, "============================================================\n");
    PROC_PRINT(p, "\n");
        
    OSAL_UP(&g_TvpSem);

    return 0;
}

HI_S32 TVP_VDEC_WriteProc(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
    HI_U32 option, value;
    HI_S32 ret;
    SecPrint(PRN_ALWS, "enter write proc!\n");

    ret = TVP_VDEC_ParamProccess(buffer, count, &option, &value);

    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    if (HI_SUCCESS != ret)
    {
        OSAL_UP(&g_TvpSem);
        return count;
    }

    if (HI_TRUE == g_bSecEnvSetUp)
    {
        ret = TVP_VDEC_SendProcCommand(option, value);
        if (HI_SUCCESS != ret)
        {
            SecPrint(PRN_ALWS, "Invalid CMD(%d %d), refer to help.\n", option, value);
            TVP_VDEC_HelpProc();
        }
    }

    OSAL_UP(&g_TvpSem);
    SecPrint(PRN_ALWS, "enter write proc SUCCESS!\n");
    return count;
}
#endif

HI_VOID TVP_VDEC_ContextInit(HI_VOID)
{
    /*全局指针初始化*/
    g_pEventHandler       = HI_NULL;

    /*静态全局变量初始化*/
    g_SecureInstNum       = 0;
    g_bSecEnvSetUp        = HI_FALSE;
    g_ThreadState         = THREAD_INVALID;

    /*全局结构体初始化*/
    memset(&g_ShareMem,   0, sizeof(g_ShareMem));
    memset(g_SecureChan,  0, sizeof(g_SecureChan));

    return;
}

HI_S32 TVP_VDEC_SecureInit(VDEC_OPERATION_S *pArgs)
{
    HI_S32 ret;
    TEEC_Result result;
    TEEC_Operation operation;
    TEEC_UUID svc_id = {0x0D0D0D0D, 0x0D0D, 0x0D0D,
                        {0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D}
                       };
    UADDR phy_addr_0 = 0;
    UADDR phy_addr_1 = 0;
    VDEC_OPERATION_S  stInitArgs;
    SHARE_DATA_S  stShareData;
    SHARE_CONTAIN_S  *pSecVfmwMem  = HI_NULL;

    SecPrint(PRN_ERROR, "%s Enter\n", __func__);

    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    if (HI_NULL == pArgs
     || HI_NULL == pArgs->ext_intf.event_handler
     || HI_NULL == pArgs->ext_intf.buffer_handler)
    {
        SecPrint(PRN_FATAL, "%s: Param Invalid!\n", __func__);
        OSAL_UP(&g_TvpSem);
        return VDEC_ERR;
    }

    if (HI_TRUE == g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "SecureDecoder already init, return OK.\n");
        OSAL_UP(&g_TvpSem);
        return VDEC_OK;
    }

    /* 建立通信环境 */
    result = TEEK_InitializeContext(HI_NULL, &g_TeeContext);
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_FATAL, "TEEC_InitializeContext Failed!\n");
        OSAL_UP(&g_TvpSem);
        return VDEC_ERR;
    }

    /* 建立会话 */
    result = TEEK_OpenSession(&g_TeeContext, &g_TeeSession, &svc_id, TEEC_LOGIN_PUBLIC, HI_NULL, HI_NULL, HI_NULL);
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_FATAL, "TEEC_OpenSession Failed!\n");
        goto InitWithfree_0;
    }

    /* 初始化全局信息 */
    TVP_VDEC_ContextInit();

    /* 申请共享内存 */
    SecPrint(PRN_ALWS, ">>>>>>>>>>>>>>>>Fix me here, alloc share memory!\n");
    g_ShareMem.MemDesc.MemType = MEM_CMA_ZERO;
    ret = VFMW_OSAL_MemAlloc("SEC_Share", sizeof(SHARE_CONTAIN_S), 4, 1, &g_ShareMem.MemDesc);
    if (OSAL_OK != ret)
    {
        SecPrint(PRN_FATAL, "Alloc share memory failed! size = %d\n", sizeof(SHARE_CONTAIN_S));
        goto InitWithfree_1;
    }
    pSecVfmwMem = (SHARE_CONTAIN_S *)g_ShareMem.MemDesc.VirAddr;

    /* 共享内存非安侧指针赋值 */
    g_ShareMem.EventList_VirAddr  = (HI_VOID *)(&pSecVfmwMem->EventList);;
    g_ShareMem.ChanOption_VirAddr = (HI_VOID *)(&pSecVfmwMem->ChanOption);
    g_ShareMem.StreamList_VirAddr = (HI_VOID *)(&pSecVfmwMem->StreamList);
    g_ShareMem.ExtBuffer_VirAddr  = (HI_VOID *)(&pSecVfmwMem->ExtBuffer);
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    g_ShareMem.ProcBuf_VirAddr    = (HI_VOID *)(&pSecVfmwMem->ProcBuf);
#endif
#if (1 == DEBUG_SAVE_SUPPORT)
    g_ShareMem.SaveBuffer_VirAddr = (HI_VOID *)(&pSecVfmwMem->SaveBuf);
#endif

    /* 记录共享内存物理地址 */
    g_ShareMem.EventList_PhyAddr  = g_ShareMem.MemDesc.PhyAddr + (HI_U8 *)(g_ShareMem.EventList_VirAddr)  - (HI_U8 *)(pSecVfmwMem);
    g_ShareMem.ChanOption_PhyAddr = g_ShareMem.MemDesc.PhyAddr + (HI_U8 *)(g_ShareMem.ChanOption_VirAddr) - (HI_U8 *)(pSecVfmwMem); 
    g_ShareMem.StreamList_PhyAddr = g_ShareMem.MemDesc.PhyAddr + (HI_U8 *)(g_ShareMem.StreamList_VirAddr) - (HI_U8 *)(pSecVfmwMem);
    g_ShareMem.ExtBuffer_PhyAddr  = g_ShareMem.MemDesc.PhyAddr + (HI_U8 *)(g_ShareMem.ExtBuffer_VirAddr)  - (HI_U8 *)(pSecVfmwMem);
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    g_ShareMem.ProcBuf_PhyAddr    = g_ShareMem.MemDesc.PhyAddr + (HI_U8 *)(g_ShareMem.ProcBuf_VirAddr)    - (HI_U8 *)(pSecVfmwMem);
#endif
#if (1 == DEBUG_SAVE_SUPPORT)
    g_ShareMem.SaveBuffer_PhyAddr = g_ShareMem.MemDesc.PhyAddr + (HI_U8 *)(g_ShareMem.SaveBuffer_VirAddr) - (HI_U8 *)(pSecVfmwMem);
#endif

    /* 设置安全侧初始化参数，回调接口无需传递 */
    memset(&stInitArgs, 0, sizeof(VDEC_OPERATION_S));
    stInitArgs.is_secure    = 1;
    stInitArgs.adapter_type = pArgs->adapter_type;
    memcpy(&stInitArgs.ext_halmem, &pArgs->ext_halmem, sizeof(MEM_DESC_S));
    SecPrint(PRN_ALWS, "%s ext hal phy= %x, len=%x, vir=%p\n", __func__, stInitArgs.ext_halmem.PhyAddr, stInitArgs.ext_halmem.Length, stInitArgs.ext_halmem.VirAddr);
    
    /* 设置安全侧共享内存信息 */
    memset(&stShareData, 0, sizeof(SHARE_DATA_S));
    ret = VFMW_GetDtsConfig(&stShareData.dts_data);
    if (ret != HI_SUCCESS)
    {
        SecPrint(PRN_FATAL, "%s call VFMW_GetDtsConfig failed\n", __func__);
        goto InitWithfree_2;
    }
    stShareData.sec_print_word    = g_SecPrintEnable;
    stShareData.event_report_list = g_ShareMem.EventList_PhyAddr;
    stShareData.stream_data_list  = g_ShareMem.StreamList_PhyAddr;
    stShareData.ext_buffer_array  = g_ShareMem.ExtBuffer_PhyAddr;

    SecPrint(PRN_ALWS, "%s sec_print_word=%x, event_report_list=%x, stream_data_list=%x\n", __func__, stShareData.sec_print_word, stShareData.event_report_list, stShareData.stream_data_list);
    
    /* 调用安全侧初始化接口 */
    phy_addr_0 = __pa((HI_SIZE_T)(&stInitArgs));
    phy_addr_1 = __pa((HI_SIZE_T)(&stShareData));

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;
    operation.params[0].value.a = phy_addr_0;
    operation.params[0].value.b = phy_addr_1;

    result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_INIT, &operation, HI_NULL);
    if (result != TEEC_SUCCESS || operation.params[0].value.a != VDEC_OK)
    {
        SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VDEC_INITWITHOPERATION failed, result_val=%d\n", operation.params[0].value.a);
        goto InitWithfree_2;
    }

    /* 记录实际回调函数 */
    g_pEventHandler  = pArgs->ext_intf.event_handler;
    g_pBufferHandler = pArgs->ext_intf.buffer_handler;

    /* 建立安全解码线程 */
    ret = TVP_VDEC_Thread_Init();
    if (ret != VDEC_OK)
    {
        SecPrint(PRN_FATAL, "%s call TVP_VDEC_Thread_Init failed\n", __func__);
        goto InitWithfree_3;
    }

    /* 安全解码器初始化成功 */
    g_bSecEnvSetUp = HI_TRUE;

    SecPrint(PRN_ERROR, "SecureDecoder init Success.\n");

    OSAL_UP(&g_TvpSem);
    
    return VDEC_OK;

InitWithfree_3:
    /* 调用安全侧去初始化函数 */
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;
    operation.params[0].value.a = 1;  // is secure flag
    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_EXIT, &operation, HI_NULL);

InitWithfree_2:
    OSAL_MemFree(&g_ShareMem.MemDesc);
    TVP_VDEC_ContextInit();

InitWithfree_1:
    TEEK_CloseSession(&g_TeeSession);
    
InitWithfree_0:
    TEEK_FinalizeContext(&g_TeeContext);

    OSAL_UP(&g_TvpSem);
    return VDEC_ERR;
}

HI_S32 TVP_VDEC_SecureExit(HI_VOID)
{
    HI_U32 i = 0;
    TEEC_Result result;
    TEEC_Operation operation;
    HI_S32 ret;

    SecPrint(PRN_ERROR, "%s Enter\n", __func__);

    OSAL_DOWN_INTERRUPTIBLE(&g_TvpSem);

    if (HI_FALSE == g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "SecureDecoder not init, return OK.\n");
        OSAL_UP(&g_TvpSem);
        return VDEC_OK;
    }
    
    if (g_SecureInstNum > 0)
    {
        SecPrint(PRN_ERROR, "SecureInstNum(%d) > 0, return OK.\n", g_SecureInstNum);
        OSAL_UP(&g_TvpSem);
        return VDEC_OK;
    }
    
    g_ThreadState = THREAD_EXIT;

    for (i = 0; i < 50; i++)
    {
        if (THREAD_INVALID == g_ThreadState)
        {
            break;
        }
        else
        {
            OSAL_MSLEEP(10);
        }
    }

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;
    operation.params[0].value.a = 1;  // is secure flag
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    result = TEEK_InvokeCommand(&g_TeeSession, HIVCODEC_CMD_ID_EXIT, &operation, HI_NULL);
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VDEC_EXIT Failed!\n");
    }

    ret = operation.params[0].value.a;
    
    /*关闭VFMW的TEEC通信*/
    TEEK_CloseSession(&g_TeeSession);
    TEEK_FinalizeContext(&g_TeeContext);
    
    OSAL_MemFree(&g_ShareMem.MemDesc);
    
    g_bSecEnvSetUp = HI_FALSE;

    SecPrint(PRN_ERROR, "SecureDecoder exit Success.\n");

    OSAL_UP(&g_TvpSem);
    return ret;
}

HI_S32 TVP_VDEC_Init(VDEC_OPERATION_S *pArgs)
{
    HI_S32 ret;

    if (HI_NULL == pArgs)
    {
        SecPrint(PRN_ERROR, "%s pArgs = NULL\n", __func__);
        return HI_FAILURE;
    }
    
    if (1 == pArgs->is_secure)
    {
        ret = TVP_VDEC_SecureInit(pArgs);
    }
    else
    {
        ret = VDEC_Init(pArgs);
    }
    
    return (VDEC_OK == ret)? HI_SUCCESS: HI_FAILURE;
}

HI_S32 TVP_VDEC_Exit(HI_U8 IsSecure)
{
    HI_S32 ret;

    if (1 == IsSecure)
    {
        ret = TVP_VDEC_SecureExit();
    }
    else
    {
        ret = VDEC_Exit(0);
    }
    
    return (VDEC_OK == ret)? HI_SUCCESS: HI_FAILURE;
}

/************************************************************************
  打开/退出VDEC组件: 在insmod/rmmod时调用如下函数，
  主要职责是创建/销毁proc文件系统
************************************************************************/
HI_VOID TVP_VDEC_OpenModule(HI_VOID)
{
    HI_S32 ret;

    OSAL_SEMA_INTIT(&g_TvpSem);
    memset(g_ChanRecord, 0, sizeof(g_ChanRecord));

#ifndef  HI_ADVCA_FUNCTION_RELEASE
    /* Create proc */
    ret = OSAL_ProcCreate(PROC_NAME, TVP_VDEC_ReadProc, TVP_VDEC_WriteProc);
    if(ret != 0)
    {
        SecPrint(PRN_ALWS, "Create TVP VDEC proc entry failed!\n");
    }
#endif

    return;
}

HI_VOID TVP_VDEC_ExitModule(HI_VOID)
{
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    OSAL_ProcDestroy(PROC_NAME);
#endif

    return;
}


