


#include <asm/uaccess.h>
#include <linux/delay.h>
#include "hi_unf_common.h"
#include "drv_venc_ext.h"
#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "drv_venc_ioctl.h"
#include "drv_venc.h"
#include "drv_omxvenc.h"
#include <linux/device.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/version.h>

#include "hi_drv_mem.h"
#include <linux/platform_device.h>
#include "venc_regulator.h"
#include <linux/hisi/hisi-iommu.h>

#define HI_VENC_LOCK() (void)pthread_mutex_lock(&g_VencMutex);
#define HI_VENC_UNLOCK() (void)pthread_mutex_unlock(&g_VencMutex);
#define PCTRL_PERI 0xE8A090A4

extern OPTM_VENC_CHN_S g_stVencChn[VENC_MAX_CHN_NUM];
extern HI_U32 gVencIsFPGA;

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

HI_BOOL gb_IsVencChanAlive[VENC_MAX_CHN_NUM] = {HI_FALSE};

/*============Deviece===============*/

//VENC device open times
atomic_t g_VencCount = ATOMIC_INIT(0);

HI_CHAR g_szYUVType[][8] = {"YUV_420", "YUV_422", "YUV_444", "UNKNOW"};
HI_CHAR g_szStoreType[][12] = {"SEMIPLANNAR", "PLANNAR", "PACKAGE", "UNKNOW"};

HI_VOID VENC_TimerFunc(HI_LENGTH_T value);

HI_S32 VENC_DRV_Resume(HI_VOID);
HI_S32 VENC_DRV_Suspend(HI_VOID);

typedef struct {
	dev_t dev;
	struct device* venc_device;
	struct device* venc_device_2;
	struct cdev cdev;
	struct class* venc_class;
}VENC_ENTRY;

static  HI_S32 VENC_DRV_SetupCdev(VENC_ENTRY *venc, const struct file_operations *fops);
static HI_S32 VENC_DRV_CleanupCdev(VENC_ENTRY *venc);
static HI_S32 VENC_DRV_Probe(struct platform_device * pltdev);
static HI_S32 VENC_DRV_Remove(struct platform_device *pltdev);
static HI_S32 VENC_DRV_Suspend1(struct platform_device *pltdev, pm_message_t state);
static HI_S32 VENC_DRV_Resume1(struct platform_device *pltdev);
static HI_VOID VENC_DRV_DeviceRelease1(struct device* dev);

VENC_EXPORT_FUNC_S s_VencExportFuncs =
{
	.pfnVencWakeUpThread = VENC_DRV_EflWakeUpThread,
    .pfnVencResume       = VENC_DRV_Resume,
    .pfnVencSuspend      = VENC_DRV_Suspend,
};

struct timer_list vencTimer;

DEFINE_SEMAPHORE(g_VencMutex);

HI_U32  g_u32VencOpenFlag = 0;
HI_BOOL g_vencDevDetected = HI_FALSE;


static HI_S32 VENC_DRV_Open(struct inode *finode, struct file  *ffile)
{
    HI_S32 Ret = 0;
    HI_S32 i   = 0;
    HI_INFO_VENC("enter %s()\n", __func__);

    Ret = down_interruptible(&g_VencMutex);

    if (Ret == 0)
    {
        HI_INFO_VENC("down_interruptible success!\n");
    }
    else
    {
        HI_FATAL_VENC("down_interruptible failed!\n");
    }

    if (1 == atomic_inc_return(&g_VencCount))
    {
        VENC_DRV_BoardInit();
        Ret = VENC_DRV_EflOpenVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("%s, VeduEfl_OpenVedu failed, ret=%d\n", __func__, Ret);
            atomic_dec(&g_VencCount);
            up(&g_VencMutex);
            return HI_FAILURE;
        }

        for (i = 0; i < VENC_MAX_CHN_NUM; i++)
        {
            memset((HI_VOID *)&(g_stVencChn[i]), 0, sizeof(OPTM_VENC_CHN_S));
            g_stVencChn[i].hVEncHandle = HI_INVALID_HANDLE;
        }

        init_timer(&vencTimer);
        vencTimer.expires  = jiffies + (HZ);
        vencTimer.function = VENC_TimerFunc;
        add_timer(&vencTimer);
    }

    g_u32VencOpenFlag = 1;
    up(&g_VencMutex);

    HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

static HI_S32 VENC_DRV_Close(struct inode *finode, struct file  *ffile)
{
    HI_U32 i   = 0;
    HI_S32 Ret = 0;

    HI_INFO_VENC("enter %s()\n", __func__);
    Ret = down_interruptible(&g_VencMutex);
    del_timer(&vencTimer);

    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        if ((g_stVencChn[i].pWhichFile == ffile)
            && (g_stVencChn[i].hVEncHandle != HI_INVALID_HANDLE))
        {
            HI_INFO_VENC("%s, Try VENC_DestroyChn %d/%#x.\n", __func__, i, g_stVencChn[i].hVEncHandle);

            Ret |= VENC_DRV_DestroyChn(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_WARN_VENC("%s, force DestroyChn %d failed, Ret=%#x.\n", __func__, i, Ret);
            }

            g_stVencChn[i].pWhichFile = HI_NULL;
        }
    }

    if (atomic_dec_and_test(&g_VencCount))
    {
        Ret = VENC_DRV_EflCloseVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("%s, VeduEfl_CloseVedu failed, ret=%d\n", __func__, Ret);
            up(&g_VencMutex);
            return HI_FAILURE;
        }

        VENC_DRV_BoardDeinit();
    }

    g_u32VencOpenFlag = 0;
    up(&g_VencMutex);

    HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_Suspend(HI_VOID)
{
    HI_U32 i   = 0;
    HI_S32 Ret = 0;
    HI_INFO_VENC("enter %s()\n", __func__);
    if (!g_u32VencOpenFlag)
    {
        HI_INFO_VENC("%s, VENC suspend OK\n", __func__);
        return 0;
    }

    Ret = down_interruptible(&g_VencMutex);
    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        HI_INFO_VENC("%s, suspend venc channel %d handle %x, invalid = %x\n", __func__, i, g_stVencChn[i].hVEncHandle,(HI_U32)HI_INVALID_HANDLE );
        if (g_stVencChn[i].hVEncHandle != HI_INVALID_HANDLE && g_stVencChn[i].bEnable == 1)
        {

            Ret = VENC_DRV_StopReceivePic(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_WARN_VENC("%s, VENC_StopReceivePic %d failed, Ret=%#x.\n", __func__, i, Ret);
            }

            gb_IsVencChanAlive[i] = HI_TRUE;
        }
        else
        {
            gb_IsVencChanAlive[i] = HI_FALSE;
        }
    }

    if (atomic_dec_and_test(&g_VencCount))
    {
        Ret = VENC_DRV_EflSuspendVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("%s, VeduEfl_CloseVedu failed, ret=%d\n", __func__, Ret);
            up(&g_VencMutex);
            return HI_FAILURE;
        }

        VENC_DRV_BoardDeinit();
    }

    up(&g_VencMutex);
	HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_Resume(HI_VOID)
{
    HI_S32 Ret = 0;
    HI_S32 i   = 0;
    HI_INFO_VENC("enter %s()\n", __func__);

    if (!g_u32VencOpenFlag)
    {
        HI_INFO_VENC("VENC resume OK\n");
        return 0;
    }

    Ret = down_interruptible(&g_VencMutex);
    if (1 == atomic_inc_return(&g_VencCount))
    {
        VENC_DRV_BoardInit();
        Ret = VENC_DRV_EflResumeVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("%s, VeduEfl_OpenVedu failed, ret=%d\n", __func__, Ret);
            atomic_dec(&g_VencCount);
            up(&g_VencMutex);
            return HI_FAILURE;
        }
    }

    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        if (gb_IsVencChanAlive[i])
        {
            HI_INFO_VENC(" h %d, fr %d. gop %d\n ",
                          g_stVencChn[i].stChnUserCfg.u32Height,
                          g_stVencChn[i].stChnUserCfg.u32TargetFrmRate,
                          g_stVencChn[i].stChnUserCfg.u32Gop);
            Ret = VENC_DRV_StartReceivePic(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_FATAL_VENC(KERN_ERR "Resume VENC_StartReceivePic %d failed.\n", i);
                continue;
            }
        }
    }

    up(&g_VencMutex);
	HI_INFO_VENC("exit %s\n", __func__);
    return HI_SUCCESS;
}

static long VENC_Ioctl(struct file *file, unsigned int ucmd, unsigned long uarg)
{
    HI_VOID *arg = (HI_VOID *)uarg;
    HI_S32 Ret = HI_FAILURE;
    HI_U32 u32Index = 0;
    int cmd = (int)ucmd;

    VENC_INFO_CREATE_S *pstCreateInfo;
    HI_HANDLE hKernVencChn;
    HI_HANDLE *pHandle = NULL;
    VENC_INFO_QUEUE_FRAME_S *pQueueFrameInfo = NULL;
    VENC_INFO_GET_MSG_S *pMessageInfo        = NULL;
    HI_HANDLE tempHandle;
    VENC_INFO_MMZ_MAP_S *pMMBInfo        = NULL;
    VENC_INFO_QUEUE_FRAME_S *pstQueStrm  = NULL;
    VENC_INFO_FLUSH_PORT_S *pstFlushPort = NULL;
    venc_user_buf * pstFrameBuf          = NULL;

    //HI_DBG_VENC("enter\n");
    switch (cmd)
    {
        case CMD_VENC_CREATE_CHN:
        {
            pstCreateInfo = (VENC_INFO_CREATE_S *)arg;
            HI_INFO_VENC("CMD_VENC_CREATE_CHN\n");
            Ret = down_interruptible(&g_VencMutex);
            Ret = VENC_DRV_CreateChn(&hKernVencChn, &(pstCreateInfo->stAttr),
            &(pstCreateInfo->stVeInfo), file);
            GET_INDEX_BYKERNHANDLE(u32Index, hKernVencChn);

            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel creat failed,pstCreateInfo:0x%x\n", __func__, pstCreateInfo);
               return HI_ERR_VENC_CREATE_ERR;
            }

            g_stVencChn[u32Index].hUsrHandle = GET_VENC_CHHANDLE(u32Index);

            pstCreateInfo->hVencChn = g_stVencChn[u32Index].hUsrHandle;
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_CREATE_CHN Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_DESTROY_CHN:
        {
            pHandle = (HI_HANDLE *)arg;
            HI_INFO_VENC("%s, CMD_VENC_DESTROY_CHN\n", __func__);
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, *pHandle);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,pHandle:0x%lx\n", __func__, pHandle);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }
            Ret  |= VENC_DRV_DestroyChn(g_stVencChn[u32Index].hVEncHandle);

            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_DESTROY_CHN Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_START_RECV_PIC:
        {
            pHandle = (HI_HANDLE*)arg;
            HI_INFO_VENC("%s, CMD_VENC_START_RECV_PIC\n", __func__);

            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, *pHandle);

            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,pHandle:0x%x\n", __func__, pHandle);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }

            Ret = VENC_DRV_StartReceivePic(g_stVencChn[u32Index].hVEncHandle);
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_START_RECV_PIC Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_STOP_RECV_PIC:
        {
            pHandle = (HI_HANDLE*)arg;
            HI_INFO_VENC("%s, CMD_VENC_STOP_RECV_PIC\n", __func__);
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, *pHandle);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,pHandle:0x%x\n", __func__, pHandle);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }
            Ret = VENC_DRV_StopReceivePic(g_stVencChn[u32Index].hVEncHandle);
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_STOP_RECV_PIC Ret:%d\n", __func__, Ret)	;
            break;
        }
        case CMD_VENC_SET_CHN_ATTR:
        {
            pstCreateInfo = (VENC_INFO_CREATE_S *)arg;
            HI_INFO_VENC("%s, CMD_VENC_SET_CHN_ATTR\n", __func__);
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, pstCreateInfo->hVencChn);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,Handle:0x%x\n", __func__, pstCreateInfo->hVencChn);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }
            Ret = VENC_DRV_SetAttr(g_stVencChn[u32Index].hVEncHandle, &(pstCreateInfo->stAttr),&(pstCreateInfo->stVeInfo));
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_SET_CHN_ATTR Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_GET_CHN_ATTR:
        {
            pstCreateInfo = (VENC_INFO_CREATE_S *)arg;
            HI_INFO_VENC("%s, CMD_VENC_GET_CHN_ATTR\n", __func__);
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, pstCreateInfo->hVencChn);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,Handle:0x%x\n", __func__, pstCreateInfo->hVencChn);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }
            Ret = VENC_DRV_GetAttr(g_stVencChn[u32Index].hVEncHandle, &(pstCreateInfo->stAttr));
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_GET_CHN_ATTR Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_REQUEST_I_FRAME:
        {
            pHandle = (HI_HANDLE*)arg;
            HI_INFO_VENC("%s, CMD_VENC_REQUEST_I_FRAME\n", __func__);
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, *pHandle);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,pHandle:0x%x\n", __func__, pHandle);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }
            Ret = VENC_DRV_RequestIFrame(g_stVencChn[u32Index].hVEncHandle);
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_REQUEST_I_FRAME Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_QUEUE_FRAME: //both omxvenc & venc use!!
        {
            pQueueFrameInfo = (VENC_INFO_QUEUE_FRAME_S*)arg;
            HI_INFO_VENC("%s, CMD_VENC_QUEUE_FRAME\n", __func__);
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, pQueueFrameInfo->hVencChn);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,Handle:0x%x\n", __func__, pQueueFrameInfo->hVencChn);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }
            Ret = VENC_DRV_QueueFrame_OMX(g_stVencChn[u32Index].hVEncHandle, &(pQueueFrameInfo->stVencFrame_OMX));
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_QUEUE_FRAME Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_GET_MSG:
        {
            pMessageInfo   = (VENC_INFO_GET_MSG_S *)arg;
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index,pMessageInfo->hVencChn);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,Handle:0x%x\n", __func__, pMessageInfo->hVencChn);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }

            tempHandle = g_stVencChn[u32Index].hVEncHandle;
            up(&g_VencMutex);

            Ret = VENC_DRV_GetMessage_OMX(tempHandle,&(pMessageInfo->msg_info_omx));
            //HI_DBG_VENC("CMD_VENC_GET_MSG Ret:%d\n",Ret);
            break;
        }
        case CMD_VENC_QUEUE_STREAM:                    //juse omxvenc use this api
        {
            pstQueStrm = (VENC_INFO_QUEUE_FRAME_S*)arg;
            HI_INFO_VENC("%s, CMD_VENC_QUEUE_STREAM\n", __func__);
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, pstQueStrm->hVencChn);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,Handle:0x%x\n", __func__, pstQueStrm->hVencChn);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }
            Ret = VENC_DRV_QueueStream_OMX(g_stVencChn[u32Index].hVEncHandle, &(pstQueStrm->stVencFrame_OMX));
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_QUEUE_STREAM Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_FLUSH_PORT:
        {
            pstFlushPort = (VENC_INFO_FLUSH_PORT_S*)arg;
            HI_INFO_VENC("%s, CMD_VENC_FLUSH_PORT\n", __func__);
            Ret = down_interruptible(&g_VencMutex);
            GET_INDEX_BYUSRHANDLE(u32Index, pstFlushPort->hVencChn);
            if (u32Index >= VENC_MAX_CHN_NUM)
            {
               up(&g_VencMutex);
               HI_ERR_VENC("%s, channel not exist,Handle:0x%x\n", __func__, pstFlushPort->hVencChn);
               return HI_ERR_VENC_CHN_NOT_EXIST;
            }
            Ret = VENC_DRV_FlushPort_OMX(g_stVencChn[u32Index].hVEncHandle, pstFlushPort->u32PortIndex);
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_FLUSH_PORT Ret:%d\n", __func__, Ret);
            break;
        }
#ifdef SPLIT_SPS_PPS
        case CMD_VENC_KEN_MAP:
        {
            pstFrameBuf   = (venc_user_buf *)arg;
            Ret = down_interruptible(&g_VencMutex);
            Ret = VENC_DRV_KEN_Map_OMX(pstFrameBuf );
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_MMZ_MAP Ret:%d\n", __func__, Ret);
            break;
        }
        case CMD_VENC_KEN_UMMAP:
        {
            pMMBInfo   = (venc_user_buf *)arg;
            Ret = down_interruptible(&g_VencMutex);
            Ret = VENC_DRV_KEN_UMMap_OMX(pstFrameBuf );
            up(&g_VencMutex);
            HI_INFO_VENC("%s, CMD_VENC_MMZ_UMMAP Ret:%d\n", __func__, Ret);
            break;
        }
#endif

        default:
        {
            HI_ERR_VENC("venc cmd unknown:%x\n", ucmd);
            break;
        }
    }

    return Ret;
}

static long VENC_DRV_Ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    long Ret;

    Ret = (long)HI_DRV_UserCopy(file, cmd, arg, VENC_Ioctl);
    return Ret;
}

static struct file_operations VENC_FOPS =
{
    .owner          = THIS_MODULE,
    .open           = VENC_DRV_Open,
    .unlocked_ioctl = VENC_DRV_Ioctl,
    .compat_ioctl   = VENC_DRV_Ioctl,  //用户态 ，内核态平台位宽不一致的时候，会调用
    .release        = VENC_DRV_Close,
};

static const struct of_device_id venc_of_match[] = {
    { .compatible = "hisi,kirin960-venc", },
    { }
};

static struct platform_driver Venc_driver = {

	.probe             = VENC_DRV_Probe,
	.remove            = VENC_DRV_Remove,

#ifdef CONFIG_PM
	.suspend           = VENC_DRV_Suspend1,
	.resume            = VENC_DRV_Resume1,
#endif

	.driver = {
	    .name           = "hi_venc",
	    .owner          = THIS_MODULE,
        .of_match_table = venc_of_match
	},
};

static struct platform_device Venc_device = {
	.name              = "hi_venc",
	.id                = -1,
    .dev = {
        .platform_data = NULL,
        .release       = VENC_DRV_DeviceRelease1,
    },
};

static HI_S32 VENC_DRV_SetupCdev(VENC_ENTRY *venc, const struct file_operations *fops)
{
    HI_U32 i   = 0;
    HI_S32 err = 0;
    HI_INFO_VENC("enter %s()\n", __func__);
    /*动态分配主设备和从设备号*/
    // 字符类型
    err = alloc_chrdev_region(&venc->dev, 0, 1, "hi_venc");

    memset((HI_VOID*)&(venc->cdev), 0, sizeof(struct cdev));

    cdev_init(&(venc->cdev), &VENC_FOPS);

    venc->cdev.owner = THIS_MODULE;
    venc->cdev.ops = &VENC_FOPS;
    err = cdev_add(&(venc->cdev), venc->dev, 1);

    /*在/sys/class/目录下创建设备类别目录hi_venc*/
    venc->venc_class = class_create(THIS_MODULE, "hi_venc");
    if (IS_ERR(venc->venc_class))
    {
        err = PTR_ERR(venc->venc_class);
        HI_ERR_VENC("Fail to create hi_venc class\n");
        return HI_FAILURE;
    }

    /*在/dev/目录和/sys/class/hi_venc目录下分别创建设备文件hi_venc*/
    venc->venc_device = device_create(venc->venc_class, NULL, venc->dev, "%s", "hi_venc");
    if (IS_ERR(venc->venc_device))
    {
        err = PTR_ERR(venc->venc_device);
        HI_ERR_VENC("%s, Fail to create hi_venc device\n", __func__);
        return HI_FAILURE;
    }

    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        g_stVencChn[i].pWhichFile = NULL;
    }

    HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

static HI_S32 VENC_DRV_CleanupCdev(VENC_ENTRY *venc)
{
    /*销毁设备类别和设备*/
    if (venc->venc_class)
    {
        device_destroy(venc->venc_class,venc->dev);
        class_destroy(venc->venc_class);
    }

    cdev_del(&(venc->cdev));

    unregister_chrdev_region(venc->dev,1);
	return 0;
}

static HI_S32 VENC_DRV_Probe(struct platform_device * pltdev)
{
	HI_S32 ret       = HI_FAILURE;
	VENC_ENTRY *venc = HI_NULL;
	HI_INFO_VENC("%s, omxvenc prepare to probe.\n", __func__);
    if (gVencIsFPGA)
    {
        HI_S32 dev_exi = 0;
        HI_U64   *viraddr_pctrl = NULL;
        viraddr_pctrl = (HI_U64 *)ioremap(PCTRL_PERI, 4);

        if (viraddr_pctrl)
        {
            dev_exi = readl(viraddr_pctrl) & 0x10;
            iounmap(viraddr_pctrl);
            viraddr_pctrl = NULL;
            if (dev_exi == 0)
            {
                HI_INFO_VENC("device enc is not exist!\n");
                return HI_FAILURE;
            }
        }
        else
        {
            HI_INFO_VENC("ioremap failed!\n");
            return HI_FAILURE;
        }
    }

    if(g_vencDevDetected)
    {
        HI_INFO_VENC("%s,  venc device detected already!\n", __func__);
        return HI_SUCCESS;
    }

	venc = kzalloc(sizeof(VENC_ENTRY), GFP_KERNEL);
	if (HI_NULL == venc)
    {
        HI_ERR_VENC("%s call kzalloc failed!\n", __func__);
		return -1;
	}

	ret = VENC_DRV_SetupCdev(venc, &VENC_FOPS);
	if(ret < 0)
    {
        HI_ERR_VENC("%s call hivdec_setup_cdev failed!\n", __func__);
		goto free;
	}

	venc->venc_device_2 = &pltdev->dev;
	platform_set_drvdata(pltdev, venc);
    g_vencDevDetected = HI_TRUE;

	ret = Venc_Regulator_Init(pltdev);
    if(ret < 0)
    {
        HI_ERR_VENC("%s, Venc_Regulator_Init failed!\n", __func__);
        goto cleanup;
    }

	HI_INFO_VENC("%s, omxvenc probe ok.\n", __func__);

	return HI_SUCCESS;

cleanup:
    VENC_DRV_CleanupCdev(venc);

free:
	kfree(venc);
	return HI_FAILURE;
}

static HI_S32 VENC_DRV_Remove(struct platform_device *pltdev)
{
	VENC_ENTRY *venc = NULL;
	HI_INFO_VENC("%s, omxvenc prepare to remove.\n", __func__);

	venc = platform_get_drvdata(pltdev);
	if (venc)
	{
		VENC_DRV_CleanupCdev(venc);
        Venc_Regulator_Deinit(pltdev);
	}
	else
	{
		HI_ERR_VENC("%s, call platform_get_drvdata err!\n", __func__);
	}

	platform_set_drvdata(pltdev,NULL);
	kfree(venc);
    g_vencDevDetected = HI_FALSE;

	HI_INFO_VENC("%s, remove omxvenc ok.\n", __func__);
	return 0;
}

static HI_S32 VENC_DRV_Suspend1(struct platform_device *pltdev, pm_message_t state)
{
	return HI_SUCCESS;
}

static HI_S32 VENC_DRV_Resume1(struct platform_device *pltdev)
{
	return HI_SUCCESS;
}

static HI_VOID VENC_DRV_DeviceRelease1(struct device* dev)
{
	return;
}

HI_S32 __init VENC_DRV_ModInit(HI_VOID)
{
    HI_S32 ret = 0;
	HI_INFO_VENC("enter %s()\n", __func__);

    ret = platform_device_register(&Venc_device);
    if(ret < 0)
    {
        HI_ERR_VENC("%s call platform_device_register failed!\n", __func__);
        return ret;
    }

    ret = platform_driver_register(&Venc_driver);
    if(ret < 0)
    {
        HI_ERR_VENC("%s call platform_driver_register failed!\n", __func__);
        goto exit;
    }

	VENC_DRV_MemProcAdd();

	HI_INFO_VENC("%s, success!!!\n", __func__);

#ifdef MODULE
    HI_INFO_VENC("Load hi_venc.ko success.\t(%s)\n", VERSION_STRING);
#endif

    HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;

exit:
	platform_device_unregister(&Venc_device);
#ifdef MODULE
    HI_ERR_VENC("Load hi_venc.ko failed!!.\t(%s)\n", VERSION_STRING);
#endif
	return ret;
}

HI_VOID VENC_DRV_ModExit(HI_VOID)
{
    HI_INFO_VENC("enter %s()\n", __func__);

	VENC_DRV_MemProcDel();

	platform_driver_unregister(&Venc_driver);
	platform_device_unregister(&Venc_device);

    HI_INFO_VENC("exit %s()\n", __func__);
    return;
}

HI_VOID VENC_TimerFunc(HI_LENGTH_T value)
{
    HI_U32 i      = 0;
    HI_S32 s32Ret = HI_FAILURE;
    VeduEfl_StatInfo_S StatInfo;
    memset(&StatInfo, 0, sizeof(StatInfo));

    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        if (g_stVencChn[i].hVEncHandle != HI_INVALID_HANDLE)
        {
            s32Ret = VENC_DRV_EflQueryStatInfo(g_stVencChn[i].hVEncHandle, &StatInfo);
            if (HI_SUCCESS == s32Ret)
            {
                /* video encoder does frame rate control by this value */
                g_stVencChn[i].u32LastSecEncodedFps = StatInfo.GetFrameNumOK - StatInfo.QuickEncodeSkip
                                                     -StatInfo.ErrCfgSkip - StatInfo.FrmRcCtrlSkip - StatInfo.SamePTSSkip
                                                     -StatInfo.TooFewBufferSkip - g_stVencChn[i].u32FrameNumLastEncoded;
                g_stVencChn[i].u32LastSecInputFps   = StatInfo.GetFrameNumOK - g_stVencChn[i].u32FrameNumLastInput;
                g_stVencChn[i].u32LastSecKbps       = StatInfo.StreamTotalByte - g_stVencChn[i].u32TotalByteLastEncoded;
                g_stVencChn[i].u32LastSecTryNum     = StatInfo.GetFrameNumTry - g_stVencChn[i].u32LastTryNumTotal;
				g_stVencChn[i].u32LastSecOKNum      = StatInfo.GetFrameNumOK - g_stVencChn[i].u32LastOKNumTotal;
                g_stVencChn[i].u32LastSecPutNum     = StatInfo.PutFrameNumOK - g_stVencChn[i].u32LastPutNumTotal;
                /* save value for next calculation */
                g_stVencChn[i].u32FrameNumLastInput    = StatInfo.GetFrameNumOK;
                g_stVencChn[i].u32FrameNumLastEncoded  = StatInfo.GetFrameNumOK - StatInfo.QuickEncodeSkip - StatInfo.ErrCfgSkip
					                                   - StatInfo.FrmRcCtrlSkip - StatInfo.SamePTSSkip - StatInfo.TooFewBufferSkip;
                g_stVencChn[i].u32TotalByteLastEncoded = StatInfo.StreamTotalByte;
                g_stVencChn[i].u32LastTryNumTotal      = StatInfo.GetFrameNumTry;
				g_stVencChn[i].u32LastOKNumTotal       = StatInfo.GetFrameNumOK;
                g_stVencChn[i].u32LastPutNumTotal      = StatInfo.PutFrameNumOK;
            }
        }
    }

    vencTimer.expires  = jiffies + (HZ);
    vencTimer.function = VENC_TimerFunc;
    add_timer(&vencTimer);

    return;
}

module_init(VENC_DRV_ModInit);
module_exit(VENC_DRV_ModExit);

MODULE_LICENSE("Dual BSD/GPL");

