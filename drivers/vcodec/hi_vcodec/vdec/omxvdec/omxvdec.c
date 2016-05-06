

#include "omxvdec.h"
#include "channel.h"
#include "task.h"
#include <linux/clk.h>
#include <linux/of.h>


/*=================== MACRO ====================*/
#define DBG_CMD_LEN             (256)
#define DBG_CMD_START           "start"
#define DBG_CMD_STOP            "stop"
#define DBG_CMD_ON              "on"
#define DBG_CMD_OFF             "off"
#define DBG_CMD_FRAME_RATE      "limit_framerate"
#define DBG_CMD_RAW             "save_raw"
#define DBG_CMD_YUV             "save_yuv"
#define DBG_CMD_PATH            "save_path"
#define DBG_CMD_NAME            "save_name"
#define DBG_CMD_TRACE           "set_print"
#define DBG_CMD_RAWMOVE         "set_RawMove"
#define DBG_CMD_DEI             "set_Dei"
#define DBG_CMD_DISPNUM         "set_DispNum"
#define DBG_CMD_CANCELBUFNUM    "set_CancelNum"
#define DBG_CMD_SEGSIZE         "set_SegSize"
#define DBG_CMD_DFS             "set_Dfs"
#define DBG_CMD_HELP            "help"

#define PCTRL_PERI 0xE8A090A4
/*================ GLOBAL VALUE ================*/
HI_U32   g_DispNum               = 2;
HI_U32   g_NativeCancelNum       = 2;
HI_U32   g_SegSize               = 2;         // (M)
HI_BOOL  g_DynamicFsEnable       = HI_TRUE;
HI_BOOL  g_RawMoveEnable         = HI_TRUE;
HI_BOOL  g_FrameRateLimit        = HI_TRUE;
HI_BOOL  g_DeInterlaceEnable     = HI_FALSE;
HI_U32   g_TraceOption           = (1<<OMX_FATAL)+(1<<OMX_ERR);
HI_BOOL  g_SaveRawEnable         = HI_FALSE;
HI_BOOL  g_SaveYuvEnable         = HI_FALSE;
HI_CHAR  g_SavePath[PATH_LEN]    = {'/','m','n','t','\0'};
HI_CHAR  g_SaveName[NAME_LEN]    = {'o','m','x','\0'};

OMXVDEC_ENTRY  *g_pOmxVdec       = HI_NULL;
OMXVDEC_FUNC    g_OmxFunc        = {HI_NULL, HI_NULL};

extern HI_U32 gIsFPGA;
/*================ STATIC VALUE ================*/
static HI_BOOL       gIsDeviceDetected  = HI_FALSE;
static struct class *g_OmxVdecClass     = HI_NULL;
static const HI_CHAR g_OmxVdecDrvName[] = OMXVDEC_NAME;
static dev_t         g_OmxVdecDevNum;
static OMXVDEC_ENTRY g_OmxVdecEntry;

/*================ STATIC TYPE =================*/
#ifdef CONFIG_COMPAT //Modified for 64-bit platform

typedef enum {
    T_IOCTL_ARG,
    T_USER_BUFFER,
    T_BUF_MSG,
    T_BUTT,
}COMPAT_TYPE_E;

#endif


/*============================================*/
MODULE_DESCRIPTION("omxvdec driver");
MODULE_AUTHOR("y00226912, 2013-03-14");
MODULE_LICENSE("GPL");


/* ==========================================================================
 * FUNTION release memory and memset
 * =========================================================================*/
HI_VOID omxvdec_release_mem(MEM_BUFFER_S *pBuffer)
{
    if (HI_NULL != pBuffer)
    {
        if (pBuffer->u32Size != 0)
        {
			VDEC_MEM_UnmapAndRelease(pBuffer);
        }
		memset(pBuffer, 0, sizeof(MEM_BUFFER_S));
    }
    else
    {
        OmxPrint(OMX_FATAL, "%s invalid param pOMX_Buf = NULL\n", __func__);
    }

    return;
}

/* ==========================================================================
 * omxvdec device mode
 * =========================================================================*/
static HI_S32 omxvdec_setup_cdev(OMXVDEC_ENTRY *omxvdec, const struct file_operations *fops)
{
	HI_S32 rc = -ENODEV;
	struct device *dev;

	g_OmxVdecClass = class_create(THIS_MODULE, "omxvdec_class");
	if (IS_ERR(g_OmxVdecClass))
    {
        rc = PTR_ERR(g_OmxVdecClass);
		g_OmxVdecClass = HI_NULL;
        OmxPrint(OMX_FATAL, "%s call class_create failed, rc = %d\n", __func__, rc);
		return rc;
	}

	rc = alloc_chrdev_region(&g_OmxVdecDevNum, 0, 1, "hisi video decoder");
	if (rc)
    {
        OmxPrint(OMX_FATAL, "%s call alloc_chrdev_region failed, rc = %d\n", __func__, rc);
		goto cls_destroy;
	}

	dev = device_create(g_OmxVdecClass, NULL, g_OmxVdecDevNum, NULL, OMXVDEC_NAME);
	if (IS_ERR(dev))
    {
        rc = PTR_ERR(dev);
        OmxPrint(OMX_FATAL, "%s call device_create failed, rc = %d\n", __func__, rc);
		goto unregister_region;
	}

	cdev_init(&omxvdec->cdev, fops);
	omxvdec->cdev.owner = THIS_MODULE;
	omxvdec->cdev.ops = fops;
	rc = cdev_add(&omxvdec->cdev, g_OmxVdecDevNum , 1);
	if (rc < 0)
    {
        OmxPrint(OMX_FATAL, "%s call cdev_add failed, rc = %d\n", __func__, rc);
		goto dev_destroy;
	}

	return HI_SUCCESS;

dev_destroy:
	device_destroy(g_OmxVdecClass, g_OmxVdecDevNum);
unregister_region:
	unregister_chrdev_region(g_OmxVdecDevNum, 1);
cls_destroy:
	class_destroy(g_OmxVdecClass);
    g_OmxVdecClass = HI_NULL;

	return rc;
}

static HI_S32 omxvdec_cleanup_cdev(OMXVDEC_ENTRY *omxvdec)
{
    if (HI_NULL == g_OmxVdecClass)
    {
        OmxPrint(OMX_FATAL, "%s FATAL: g_OmxVdecClass = NULL", __func__);
		return HI_FAILURE;
    }
	else
	{
		cdev_del(&omxvdec->cdev);
		device_destroy(g_OmxVdecClass, g_OmxVdecDevNum);
		unregister_chrdev_region(g_OmxVdecDevNum, 1);
		class_destroy(g_OmxVdecClass);
		return HI_SUCCESS;
	}
}

/* ==========================================================================
 * HI_CHAR device ops functions
 * =========================================================================*/
static HI_S32 omxvdec_open(struct inode *inode, struct file *fd)
{
	HI_S32  ret = -EBUSY;
	OMXVDEC_ENTRY *omxvdec = HI_NULL;

	OmxPrint(OMX_TRACE, "omxvdec prepare to open.\n");

	omxvdec = container_of(inode->i_cdev, OMXVDEC_ENTRY, cdev);

    VDEC_DOWN_INTERRUPTIBLE(&omxvdec->omxvdec_mutex);

	if (omxvdec->open_count < MAX_OPEN_COUNT)
    {
        omxvdec->open_count++;

        if (1 == omxvdec->open_count)
        {
           memset(&g_OmxFunc, 0, sizeof(OMXVDEC_FUNC));

           ret = channel_init();
           if(ret != HI_SUCCESS)
           {
               OmxPrint(OMX_FATAL, "%s init channel failed!\n", __func__);
               goto error0;
           }

           if (HI_TRUE == g_DynamicFsEnable && HI_NULL == omxvdec->task.task_thread)
           {
               ret = task_create_thread(omxvdec);
               if (ret != HI_SUCCESS)
               {
                   OmxPrint(OMX_FATAL, "%s call channel_create_task failed!\n", __func__);
                   goto error1;
               }
           }
        }

        fd->private_data = omxvdec;

        OmxPrint(OMX_TRACE, "omxvdec open ok.\n");
        ret = HI_SUCCESS;
	}
    else
    {
        OmxPrint(OMX_FATAL, "%s open omxvdec instance too much! \n", __func__);
		ret = -EBUSY;
	}

    VDEC_UP_INTERRUPTIBLE(&omxvdec->omxvdec_mutex);

	return ret;

error1:
    channel_exit();
error0:
    omxvdec->open_count--;
    VDEC_UP_INTERRUPTIBLE(&omxvdec->omxvdec_mutex);

    return ret;
}

static HI_S32 omxvdec_release(struct inode *inode, struct file *fd)
{
	unsigned long     flags;
	OMXVDEC_ENTRY	 *omxvdec = HI_NULL;
	OMXVDEC_CHAN_CTX *pchan   = HI_NULL;
	OMXVDEC_CHAN_CTX *n       = HI_NULL;

	OmxPrint(OMX_TRACE, "omxvdec prepare to release.\n");

    omxvdec = fd->private_data;
    if (HI_NULL == omxvdec)
    {
	    OmxPrint(OMX_FATAL, "%s: omxvdec = null, error!\n", __func__);
	    return -EFAULT;
    }

    VDEC_DOWN_INTERRUPTIBLE(&omxvdec->omxvdec_mutex);

	spin_lock_irqsave(&omxvdec->channel_lock, flags);
	if (!list_empty(&omxvdec->chan_list))
    {
		list_for_each_entry_safe(pchan, n, &omxvdec->chan_list, chan_list)
        {
             if((pchan->file_dec == (HI_U64)fd) && (CHAN_STATE_INVALID != pchan->channel_state))
             {
                 spin_unlock_irqrestore(&omxvdec->channel_lock, flags);
                 channel_release_inst(pchan);
                 spin_lock_irqsave(&omxvdec->channel_lock, flags);
             }
        }
	}
	spin_unlock_irqrestore(&omxvdec->channel_lock, flags);

	if(omxvdec->open_count > 0)
    {
        omxvdec->open_count--;
    }

    if(0 == omxvdec->open_count)
    {
        channel_exit();
        task_destroy_thread(omxvdec);
    }

	fd->private_data = HI_NULL;
    memset(&g_OmxFunc, 0, sizeof(OMXVDEC_FUNC));

	OmxPrint(OMX_TRACE, "omxvdec release ok.\n");

    VDEC_UP_INTERRUPTIBLE(&omxvdec->omxvdec_mutex);

	return 0;
}

static long omxvdec_ioctl(struct file *fd, unsigned int code, unsigned long arg)
{
    HI_S32 ret        = HI_FAILURE;
    HI_S32 chan_id = -1;
    ePORT_DIR flush_dir;
    OMXVDEC_MSG_INFO  msg;
    OMXVDEC_CHAN_CFG  chan_cfg;
    OMXVDEC_IOCTL_MSG vdec_msg;
    OMXVDEC_BUF_DESC  user_buf;

    OMXVDEC_CHAN_CTX *pchan   = HI_NULL;
    HI_VOID          *u_arg   = (HI_VOID *)arg;
    OMXVDEC_ENTRY	 *omxvdec = fd->private_data;

    if (copy_from_user(&vdec_msg, u_arg, sizeof(OMXVDEC_IOCTL_MSG)))
    {
        OmxPrint(OMX_FATAL, "%s call copy_from_user failed! \n", __func__);
        return -EFAULT;
    }

    if (code != VDEC_IOCTL_CHAN_CREATE)
    {
        chan_id = vdec_msg.chan_num;
        if (chan_id < 0)
        {
            OmxPrint(OMX_FATAL, "%s Invalid Chan Num: %d.\n", __func__, chan_id);
            return -EINVAL;
        }

        pchan = channel_find_inst_by_channel_id(omxvdec, chan_id);
        if (HI_NULL == pchan)
        {
            OmxPrint(OMX_ERR, "%s can't find Chan(%d).\n", __func__, chan_id);
            return -EFAULT;
        }
    }

    /* handle ioctls */
    switch (code)
    {
        /* when alloc buffer in omx ,we need to sync it with omxvdec, because the buffer is share with omx
        & player & driver, here we use a input/output buf table to record its info */

        case VDEC_IOCTL_CHAN_ALLOC_BUFFER:
            if (copy_from_user(&user_buf, vdec_msg.in, sizeof(OMXVDEC_BUF_DESC)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_alloc_user_buffer(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call aloc_buffer failed!\n", __func__, __LINE__);
                return -EFAULT;
            }

            if (copy_to_user(vdec_msg.out, &user_buf, sizeof(OMXVDEC_BUF_DESC)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }
            break;

        case VDEC_IOCTL_CHAN_FREE_BUFFER:
            if (copy_from_user(&user_buf, vdec_msg.in, sizeof(OMXVDEC_BUF_DESC)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_free_user_buffer(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call free_buffer failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_BIND_BUFFER:
            if (copy_from_user(&user_buf, vdec_msg.in, sizeof(OMXVDEC_BUF_DESC)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_bind_user_buffer(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call bind_buffer failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_UNBIND_BUFFER:
            if (copy_from_user(&user_buf, vdec_msg.in, sizeof(OMXVDEC_BUF_DESC)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_unbind_user_buffer(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call unbind_buffer failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_EMPTY_INPUT_STREAM:
            if (copy_from_user(&user_buf, vdec_msg.in, sizeof(OMXVDEC_BUF_DESC)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_empty_this_stream(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call empty_stream failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_FILL_OUTPUT_FRAME:
            if (copy_from_user(&user_buf, vdec_msg.in, sizeof(OMXVDEC_BUF_DESC)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_fill_this_frame(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call fill_frame failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_FLUSH_PORT:
            if (copy_from_user(&flush_dir, vdec_msg.in, sizeof(ePORT_DIR)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EFAULT;
            }

            ret = channel_flush_inst(pchan, flush_dir);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call flush_port failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_GET_MSG:
            ret = channel_get_message(pchan, &msg);
            if (ret != HI_SUCCESS)
            {
                if (ret == -EAGAIN)
                {
                    OmxPrint(OMX_WARN, "%s %d: no msg found, try again.\n", __func__, __LINE__);
                    return -EAGAIN;
                }
                else
                {
                    OmxPrint(OMX_WARN, "%s %d: get msg error!\n", __func__, __LINE__);
                    return -EFAULT;
                }
            }

            if (copy_to_user(vdec_msg.out, &msg, sizeof(OMXVDEC_MSG_INFO)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }
            break;

        case VDEC_IOCTL_CHAN_PAUSE:
            ret = channel_pause_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call pause failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_RESUME:
            ret = channel_resume_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call resume failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_START:
            ret = channel_start_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call start failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_STOP:
            ret = channel_stop_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call stop failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_CREATE:
            if (copy_from_user(&chan_cfg, vdec_msg.in, sizeof(OMXVDEC_CHAN_CFG)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EFAULT;
            }

            chan_id = channel_create_inst(fd, &chan_cfg);
            if (chan_id < 0)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call channel_create_inst failed!\n", __func__, __LINE__);
                return -EFAULT;
            }

            if (copy_to_user(vdec_msg.out, &chan_id, sizeof(HI_S32)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }
            break;

        case VDEC_IOCTL_CHAN_RELEASE:
            ret = channel_release_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call release failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        default:
            /* could not handle ioctl */
            OmxPrint(OMX_FATAL, "%s %d: ERROR cmd=%d is not supported!\n", __func__, __LINE__, _IOC_NR(code));
            return -ENOTTY;
    }

    return 0;
}

#ifdef CONFIG_COMPAT //Modified for 64-bit platform
static HI_S32 omxvdec_compat_get_data(COMPAT_TYPE_E eType, HI_VOID __user *pUser, HI_VOID *pData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_S32 s32Data = 0;
    compat_ulong_t CompatData = 0;

    if (HI_NULL == pUser || HI_NULL == pData)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

    switch(eType)
    {
        case T_IOCTL_ARG:
            {
                COMPAT_IOCTL_MSG __user *pCompatMsg = pUser;
                OMXVDEC_IOCTL_MSG         *pIoctlMsg = pData;

                ret |= get_user(s32Data, &(pCompatMsg->chan_num));
                pIoctlMsg->chan_num = s32Data;

                ret |= get_user(CompatData, &(pCompatMsg->in));
                pIoctlMsg->in   = (HI_VOID *) ((HI_VIRT_ADDR_T)CompatData);

                ret |= get_user(CompatData, &(pCompatMsg->out));
                pIoctlMsg->out = (HI_VOID *) ((HI_VIRT_ADDR_T)CompatData);
            }
            break;

        case T_USER_BUFFER:
            {
                COMPAT_BUF_DESC __user *pCompatBuf  = pUser;
                OMXVDEC_BUF_DESC         *pIoctlBuf       = pData;

                ret |= copy_from_user(pIoctlBuf, pCompatBuf, sizeof(COMPAT_BUF_DESC));

                ret |= get_user(CompatData, &(pCompatBuf->bufferaddr));
                pIoctlBuf->bufferaddr    = (HI_VOID *) ((HI_VIRT_ADDR_T)CompatData);

                ret |= get_user(CompatData, &(pCompatBuf->client_data));
                pIoctlBuf->client_data   = (HI_VOID *) ((HI_VIRT_ADDR_T)CompatData);
            }
            break;

        default:
            OmxPrint(OMX_FATAL, "%s unkown type %d!\n", __func__, eType);
            break;
    }

    return ret;
}

static HI_S32 omxvdec_compat_set_data(COMPAT_TYPE_E eType, HI_VOID __user *pUser, HI_VOID *pData)
{
    HI_S32 ret = HI_SUCCESS;
    compat_ulong_t CompatData = 0;

    if (HI_NULL == pUser || HI_NULL == pData)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

    switch(eType)
    {
        case T_BUF_MSG:
            {
                COMPAT_MSG_INFO __user *pCompatMsgInfo  = pUser;
                OMXVDEC_MSG_INFO         *pIoctlMsgInfo       = pData;

                ret |= copy_to_user(pCompatMsgInfo, pIoctlMsgInfo, sizeof(COMPAT_MSG_INFO));

                CompatData = (compat_ulong_t)((HI_VIRT_ADDR_T)pIoctlMsgInfo->msgdata.buf.bufferaddr);
                ret |= put_user(CompatData, &(pCompatMsgInfo->msgdata.buf.bufferaddr));

                CompatData = (compat_ulong_t)((HI_VIRT_ADDR_T)pIoctlMsgInfo->msgdata.buf.client_data);
                ret |= put_user(CompatData, &(pCompatMsgInfo->msgdata.buf.client_data));
            }
            break;

        case T_USER_BUFFER:
            {
                COMPAT_BUF_DESC __user *pCompatBuf  = pUser;
                OMXVDEC_BUF_DESC         *pIoctlBuf       = pData;

                ret |= copy_to_user(pCompatBuf, pIoctlBuf, sizeof(COMPAT_BUF_DESC));

                CompatData = (compat_ulong_t)((HI_VIRT_ADDR_T)pIoctlBuf->bufferaddr);
                ret |= put_user(CompatData, &(pCompatBuf->bufferaddr));

                CompatData = (compat_ulong_t)((HI_VIRT_ADDR_T)pIoctlBuf->client_data);
                ret |= put_user(CompatData, &(pCompatBuf->client_data));
            }
            break;

        default:
            OmxPrint(OMX_FATAL, "%s unkown type %d!\n", __func__, eType);
            break;
    }

    return ret;
}

static long omxvdec_compat_ioctl(struct file *fd, unsigned int code, unsigned long arg)
{
    HI_S32 ret         = HI_FAILURE;
    HI_S32 chan_id  = -1;
    ePORT_DIR flush_dir;
    OMXVDEC_MSG_INFO   msg;
    OMXVDEC_CHAN_CFG   chan_cfg;
    OMXVDEC_BUF_DESC   user_buf;
    OMXVDEC_IOCTL_MSG vdec_msg;
    OMXVDEC_CHAN_CTX  *pchan   = HI_NULL;
    OMXVDEC_ENTRY	   *omxvdec = fd->private_data;

    ret = omxvdec_compat_get_data(T_IOCTL_ARG, compat_ptr(arg), &vdec_msg);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s T_IOCTL_MSG get data failed!\n", __func__);
        return -EIO;
    }

    if (code != VDEC_IOCTL_CHAN_CREATE)
    {
        chan_id = vdec_msg.chan_num;
        if (chan_id < 0)
        {
            OmxPrint(OMX_FATAL, "%s Invalid Chan Num: %d.\n", __func__, chan_id);
            return -EINVAL;
        }

        pchan = channel_find_inst_by_channel_id(omxvdec, chan_id);
        if (HI_NULL == pchan)
        {
            OmxPrint(OMX_ERR, "%s can't find Chan(%d).\n", __func__, chan_id);
            return -EFAULT;
        }
    }

    switch (code)
    {
        case VDEC_IOCTL_CHAN_ALLOC_BUFFER:
            ret = omxvdec_compat_get_data(T_USER_BUFFER, vdec_msg.in, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d T_USER_BUFFER get data failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_alloc_user_buffer(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call aloc_buffer failed!\n", __func__, __LINE__);
                return -EFAULT;
            }

            ret = omxvdec_compat_set_data(T_USER_BUFFER, vdec_msg.out, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d T_USER_BUFFER set data failed!\n", __func__, __LINE__);
                return -EIO;
            }
            break;

        case VDEC_IOCTL_CHAN_FREE_BUFFER:
            ret = omxvdec_compat_get_data(T_USER_BUFFER, vdec_msg.in, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d T_USER_BUFFER get data failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_free_user_buffer(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call free_buffer failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_BIND_BUFFER:
            ret = omxvdec_compat_get_data(T_USER_BUFFER, vdec_msg.in, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d T_USER_BUFFER get data failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_bind_user_buffer(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call bind_buffer failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_UNBIND_BUFFER:
            ret = omxvdec_compat_get_data(T_USER_BUFFER, vdec_msg.in, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d T_USER_BUFFER get data failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_unbind_user_buffer(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call unbind_buffer failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_EMPTY_INPUT_STREAM:
            ret = omxvdec_compat_get_data(T_USER_BUFFER, vdec_msg.in, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d T_USER_BUFFER get data failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_empty_this_stream(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call empty_stream failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

         case VDEC_IOCTL_FILL_OUTPUT_FRAME:
            ret = omxvdec_compat_get_data(T_USER_BUFFER, vdec_msg.in, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d T_USER_BUFFER get data failed!\n", __func__, __LINE__);
                return -EIO;
            }

            ret = channel_fill_this_frame(pchan, &user_buf);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call fill_frame failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_FLUSH_PORT:
            if (copy_from_user(&flush_dir, vdec_msg.in, sizeof(ePORT_DIR)))
            {
                OmxPrint(OMX_FATAL, "%s, %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EFAULT;
            }

            ret = channel_flush_inst(pchan, flush_dir);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call flush_port failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_GET_MSG:
            ret = channel_get_message(pchan, &msg);
            if (ret != HI_SUCCESS)
            {
                if (ret == -EAGAIN)
                {
                    OmxPrint(OMX_WARN, "%s %d: no msg found, try again.\n", __func__, __LINE__);
                    return -EAGAIN;
                }
                else
                {
                    OmxPrint(OMX_WARN, "%s %d: get msg error!\n", __func__, __LINE__);
                    return -EFAULT;
                }
            }

            if (VDEC_MSG_RESP_INPUT_DONE == msg.msgcode || VDEC_MSG_RESP_OUTPUT_DONE == msg.msgcode)
            {
                ret = omxvdec_compat_set_data(T_BUF_MSG, vdec_msg.out, &msg);
                if (ret != HI_SUCCESS)
                {
                    OmxPrint(OMX_FATAL, "%s %d T_BUF_MSG set data failed! msgcode = %d\n", __func__, __LINE__, msg.msgcode);
                    return -EIO;
                }
            }
            else
            {
                if (copy_to_user(vdec_msg.out, &msg, sizeof(COMPAT_MSG_INFO)))
                {
                    OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                    return -EIO;
                }
            }
            break;

        case VDEC_IOCTL_CHAN_PAUSE:
            ret = channel_pause_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call pause failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_RESUME:
            ret = channel_resume_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call resume failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_START:
            ret = channel_start_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call start failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_STOP:
            ret = channel_stop_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s, %d: case call stop failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        case VDEC_IOCTL_CHAN_CREATE:
            if (copy_from_user(&chan_cfg, vdec_msg.in, sizeof(OMXVDEC_CHAN_CFG)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EFAULT;
            }

            chan_id = channel_create_inst(fd, &chan_cfg);
            if (chan_id < 0)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call channel_create_inst failed!\n", __func__, __LINE__);
                return -EFAULT;
            }

            if (copy_to_user(vdec_msg.out, &chan_id, sizeof(HI_S32)))
            {
                OmxPrint(OMX_FATAL, "%s %d: case call copy_from_user failed!\n", __func__, __LINE__);
                return -EIO;
            }
            break;

        case VDEC_IOCTL_CHAN_RELEASE:
            ret = channel_release_inst(pchan);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_FATAL, "%s %d: case call release failed!\n", __func__, __LINE__);
                return -EFAULT;
            }
            break;

        default:
            /* could not handle ioctl */
            OmxPrint(OMX_FATAL, "%s %d: ERROR cmd=%d is not supported!\n", __func__, __LINE__, _IOC_NR(code));
            return -ENOTTY;
    }

    return 0;
}
#endif //CONFIG_COMPAT

static const struct file_operations omxvdec_fops = {

	.owner          = THIS_MODULE,
	.open           = omxvdec_open,
	.unlocked_ioctl = omxvdec_ioctl,
#ifdef CONFIG_COMPAT //Modified for 64-bit platform
    .compat_ioctl   = omxvdec_compat_ioctl,
#endif //CONFIG_COMPAT
	.release        = omxvdec_release,
};

static HI_S32 omxvdec_probe(struct platform_device *pltdev)
{
	HI_S32 ret = HI_FAILURE;

    if (gIsFPGA)
    {
        HI_S32 dev_exi = 0;
        HI_U64* viraddr_pctrl = NULL;
        viraddr_pctrl = (HI_U64 *)ioremap(PCTRL_PERI, 4);
        if (viraddr_pctrl)
        {
            dev_exi = readl(viraddr_pctrl) & 0x4;
            iounmap(viraddr_pctrl);
            viraddr_pctrl = NULL;
            if (dev_exi == 0)
            {
                OmxPrint(OMX_ERR, "vdec is not exist!\n");
                return HI_FAILURE;
            }
        }
        else
        {
            OmxPrint(OMX_ERR, "ioremap failed!\n");
            return HI_FAILURE;
        }
    }

    if(HI_TRUE == gIsDeviceDetected)
    {
        OmxPrint(OMX_INFO, "Already probe omxvdec!\n");
		return 0;
    }

	platform_set_drvdata(pltdev, HI_NULL);

    memset(&g_OmxVdecEntry, 0, sizeof(OMXVDEC_ENTRY));

	INIT_LIST_HEAD(&g_OmxVdecEntry.chan_list);
    VDEC_INIT_MUTEX(&g_OmxVdecEntry.omxvdec_mutex);
	spin_lock_init(&g_OmxVdecEntry.channel_lock);

	ret = omxvdec_setup_cdev(&g_OmxVdecEntry, &omxvdec_fops);
	if(ret < 0)
    {
        OmxPrint(OMX_FATAL, "%s call omxvdec_setup_cdev failed!\n", __func__);
		goto cleanup0;
	}

    ret = VDEC_Regulator_Initialize((HI_VOID *)pltdev);
	if(ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call Regulator_Initialize failed!\n", __func__);
		goto cleanup1;
	}

	g_OmxVdecEntry.device = &pltdev->dev;
	platform_set_drvdata(pltdev, &g_OmxVdecEntry);
	g_pOmxVdec = &g_OmxVdecEntry;
    gIsDeviceDetected = HI_TRUE;

	return 0;

cleanup1:
    omxvdec_cleanup_cdev(&g_OmxVdecEntry);

cleanup0:
	return ret;
}

static HI_S32 omxvdec_remove(struct platform_device *pltdev)
{
	OMXVDEC_ENTRY *omxvdec = HI_NULL;

	omxvdec = platform_get_drvdata(pltdev);
    if (omxvdec != HI_NULL)
    {
        if (IS_ERR(omxvdec))
        {
    		OmxPrint(OMX_ERR, "call platform_get_drvdata err, errno = %ld!\n", PTR_ERR(omxvdec));
        }
        else
        {
    		omxvdec_cleanup_cdev(omxvdec);
    		VDEC_Regulator_DeInitialize((HI_VOID *)pltdev);
        	g_pOmxVdec = HI_NULL;
    	    platform_set_drvdata(pltdev, HI_NULL);
            gIsDeviceDetected = HI_FALSE;
        }
    }

	return 0;
}

/* ==========================================================================
 * omxvdec proc entrance
 * =========================================================================*/
static inline HI_S32 omxvdec_string_to_value(HI_PCHAR str, HI_U32 *data)
{
    HI_U32 i, d, dat, weight;

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
        if(str[i] < 0x20)
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

    return HI_SUCCESS;
}

HI_VOID omxvdec_help_proc(HI_VOID)
{
    VDEC_PROC_EchoHelper(
    "\n"
    "================== OMXVDEC HELP ===========\n"
    "USAGE:echo [cmd] [para] > /proc/msp/omxvdec\n"
    "cmd = save_raw,         para = start/stop   :start/stop to save raw data\n"
    "cmd = save_yuv,         para = start/stop   :start/stop to save yuv data\n"
    "cmd = save_path,        para = path         :config path to save data\n"
    "cmd = set_RawMove,      para = on/off       :enable/disable raw move\n");
    VDEC_PROC_EchoHelper(
    "cmd = set_Dfs,          para = on/off       :enable/disable dynamic frame store\n"
    "cmd = set_print,        para = value        :set print                 = value\n"
    "cmd = set_DispNum,      para = value        :set DispNum               = value\n"
    "cmd = set_CancelNum,    para = value        :set NativeCancelNum       = value\n"
    "cmd = set_SegSize,      para = value        :set SegSize               = value\n"
    "cmd = set_InBufThred,   para = value        :set InBufThred            = value\n"
    "\n");
    VDEC_PROC_EchoHelper(
    "TraceOption(32bits):\n"
    "0(FATAL)   1(ERR)     2(WARN)     3(INFO)\n"
    "4(TRACE)   5(INBUF)   6(OUTBUF)   7(PP)\n"
    "8(VERBOSE) 9(PTS)                        \n"
    "-------------------------------------------\n"
    "\n");
}

static HI_S32 omxvdec_read_proc(struct seq_file *p, HI_VOID *v)
{
    unsigned long flags;
    OMXVDEC_CHAN_CTX *pchan = NULL;

    if (HI_NULL == g_pOmxVdec)
    {
        PROC_PRINT(p, "Warnning: g_OmxVdec = NULL\n");
        return 0;
    }

    PROC_PRINT(p, "\n");
    PROC_PRINT(p, "============ OMXVDEC INFO ============\n");
    PROC_PRINT(p, "%-20s :%d\n", "Version",           OMXVDEC_VERSION);
    PROC_PRINT(p, "%-20s :%d\n", "ActiveChanNum",     g_pOmxVdec->total_chan_num);

    PROC_PRINT(p, "%-20s :%d\n", "Print",             g_TraceOption);
    PROC_PRINT(p, "%-20s :%d\n", "SaveRawEnable",     g_SaveRawEnable);
    PROC_PRINT(p, "%-20s :%d\n", "SaveYuvEnable",     g_SaveYuvEnable);
    PROC_PRINT(p, "%-20s :%s\n", "SaveName",          g_SaveName);
    PROC_PRINT(p, "%-20s :%s\n", "SavePath",          g_SavePath);
    PROC_PRINT(p, "%-20s :%d\n", "DispNum",           g_DispNum);
    PROC_PRINT(p, "%-20s :%d\n", "NativeCancelNum",   g_NativeCancelNum);
    PROC_PRINT(p, "%-20s :%d\n", "SegSize(M)",        g_SegSize);
    PROC_PRINT(p, "%-20s :%d\n", "RawMoveEnable",     g_RawMoveEnable);
    PROC_PRINT(p, "%-20s :%d\n", "DynamicFsEnable",   g_DynamicFsEnable);
    if (HI_TRUE == g_DynamicFsEnable && HI_NULL != g_pOmxVdec->task.task_thread)
    {
        task_proc_entry(p, &g_pOmxVdec->task);
    }
    PROC_PRINT(p, "\n");

    spin_lock_irqsave(&g_pOmxVdec->channel_lock, flags);
    if (0 != g_pOmxVdec->total_chan_num)
    {
       list_for_each_entry(pchan, &g_pOmxVdec->chan_list, chan_list)
       {
           channel_proc_entry(p, pchan);
       }
    }
    spin_unlock_irqrestore(&g_pOmxVdec->channel_lock, flags);

    return 0;
}

HI_S32 omxvdec_write_proc(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
    HI_S32  i,j;
    HI_U32  dat2;
    HI_CHAR buf[DBG_CMD_LEN];
    HI_CHAR str1[DBG_CMD_LEN];
    HI_CHAR str2[DBG_CMD_LEN];

    if(count >= sizeof(buf))
    {
        OmxPrint(OMX_ALWS, "parameter string is too long!\n");
        return HI_FAILURE;
    }

    memset(buf, 0, sizeof(buf));
    if (copy_from_user(buf, buffer, count))
    {
        OmxPrint(OMX_ALWS, "copy_from_user failed!\n");
        return HI_FAILURE;
    }
    buf[count] = 0;

    if (count < 1)
    {
        goto error;
    }
    else
    {
        /* dat1 */
        i = 0;
        j = 0;
        for(; i < count; i++)
        {
            if(j==0 && buf[i]==' ')
            {
                continue;
            }
            if(buf[i] > ' ')
            {
                str1[j++] = buf[i];
            }
            if(j>0 && buf[i]==' ')
            {
                break;
            }
        }
        str1[j] = 0;

        /* dat2 */
        j = 0;
        for(; i < count; i++)
        {
            if(j==0 && buf[i]==' ')
            {
                continue;
            }
            if(buf[i] > ' ')
            {
                str2[j++] = buf[i];
            }
            if(j>0 && buf[i]==' ')
            {
                break;
            }
        }
        str2[j] = 0;

        if (!strncmp(str1, DBG_CMD_TRACE, DBG_CMD_LEN))
        {
            if(omxvdec_string_to_value(str2, &dat2) != 0)
            {
                goto error;
            }

            OmxPrint(OMX_ALWS, "print: %u\n", dat2);
            g_TraceOption = dat2;
        }
        else if (!strncmp(str1, DBG_CMD_RAW, DBG_CMD_LEN))
        {
            if (!strncmp(str2, DBG_CMD_START, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Enable raw save.\n");
                g_SaveRawEnable = HI_TRUE;
            }
            else if (!strncmp(str2, DBG_CMD_STOP, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Disable raw save.\n");
                g_SaveRawEnable = HI_FALSE;
            }
            else
            {
                goto error;
            }
        }
        else if (!strncmp(str1, DBG_CMD_YUV, DBG_CMD_LEN))
        {
            if (!strncmp(str2, DBG_CMD_START, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Enable yuv save.\n");
                g_SaveYuvEnable = HI_TRUE;
            }
            else if (!strncmp(str2, DBG_CMD_STOP, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Disable yuv save.\n");
                g_SaveYuvEnable = HI_FALSE;
            }
            else
            {
                goto error;
            }
        }
        else if (!strncmp(str1, DBG_CMD_PATH, DBG_CMD_LEN))
        {
            if (j > 0 && j < sizeof(g_SavePath) && str2[0] == '/')
            {
                if(str2[j-1] == '/')
                {
                   str2[j-1] = 0;
                }
                strncpy(g_SavePath, str2, PATH_LEN);
                g_SavePath[PATH_LEN-1] = '\0';
                OmxPrint(OMX_ALWS, "SavePath: %s\n", g_SavePath);
            }
            else
            {
                goto error;
            }
        }
        else if (!strncmp(str1, DBG_CMD_NAME, DBG_CMD_LEN))
        {
            if (j > 0 && j < sizeof(g_SaveName))
            {
                strncpy(g_SaveName, str2, NAME_LEN);
                g_SaveName[NAME_LEN-1] = '\0';
                OmxPrint(OMX_ALWS, "SaveName: %s\n", g_SaveName);
            }
            else
            {
                goto error;
            }
        }
        else if (!strncmp(str1, DBG_CMD_FRAME_RATE, DBG_CMD_LEN))
        {
            if (!strncmp(str2, DBG_CMD_ON, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Enable frame rate limit.\n");
                g_FrameRateLimit = HI_TRUE;
            }
            else if (!strncmp(str2, DBG_CMD_OFF, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Disable frame rate limit.\n");
                g_FrameRateLimit = HI_FALSE;
            }
            else
            {
                goto error;
            }
        }
        else if (!strncmp(str1, DBG_CMD_RAWMOVE, DBG_CMD_LEN))
        {
            if (!strncmp(str2, DBG_CMD_ON, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Enable Raw Move.\n");
                g_RawMoveEnable = HI_TRUE;
            }
            else if (!strncmp(str2, DBG_CMD_OFF, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Disable Raw Move.\n");
                g_RawMoveEnable = HI_FALSE;
            }
            else
            {
                goto error;
            }
        }
        else if (!strncmp(str1, DBG_CMD_DEI, DBG_CMD_LEN))
        {
            if (!strncmp(str2, DBG_CMD_ON, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Enable DeInterlace.\n");
                g_DeInterlaceEnable = HI_TRUE;
            }
            else if (!strncmp(str2, DBG_CMD_OFF, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Disable DeInterlace.\n");
                g_DeInterlaceEnable = HI_FALSE;
            }
            else
            {
                goto error;
            }
        }
        else if (!strncmp(str1, DBG_CMD_DISPNUM, DBG_CMD_LEN))
        {
            if(omxvdec_string_to_value(str2, &dat2) != 0)
            {
                goto error;
            }

            OmxPrint(OMX_ALWS, "DispNum: %u\n", dat2);
            g_DispNum = dat2;
        }
        else if (!strncmp(str1, DBG_CMD_CANCELBUFNUM, DBG_CMD_LEN))
        {
            if(omxvdec_string_to_value(str2, &dat2) != 0)
            {
                goto error;
            }

            OmxPrint(OMX_ALWS, "NativeCancelNum: %u\n", dat2);
            g_NativeCancelNum = dat2;
        }
        else if (!strncmp(str1, DBG_CMD_SEGSIZE, DBG_CMD_LEN))
        {
            if(omxvdec_string_to_value(str2, &dat2) != 0)
            {
                goto error;
            }

            OmxPrint(OMX_ALWS, "SegSize: %u\n", dat2);
            g_SegSize = dat2;
        }
        else if (!strncmp(str1, DBG_CMD_DFS, DBG_CMD_LEN))
        {
            if (!strncmp(str2, DBG_CMD_ON, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Enable DynamicFs.\n");
                g_DynamicFsEnable = HI_TRUE;
            }
            else if (!strncmp(str2, DBG_CMD_OFF, DBG_CMD_LEN))
            {
                OmxPrint(OMX_ALWS, "Disable DynamicFs.\n");
                g_DynamicFsEnable = HI_FALSE;
            }
            else
            {
                goto error;
            }
        }
        else if (!strncmp(str1, DBG_CMD_HELP, DBG_CMD_LEN))
        {
            omxvdec_help_proc();
        }
        else
        {
            goto error;
        }
    }

    return count;

error:
    OmxPrint(OMX_ALWS, "Invalid echo command!\n");
    omxvdec_help_proc();

    return count;
}

HI_S32 omxvdec_init_proc (HI_VOID)
{
    HI_CHAR aszBuf[16];
    HI_S32   ret = HI_FAILURE;

    /* Create proc */
    snprintf(aszBuf, sizeof(aszBuf), "omxvdec");
    ret = VDEC_PROC_Create(aszBuf, omxvdec_read_proc, omxvdec_write_proc);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "Create omxvdec proc entry failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID omxvdec_exit_proc(HI_VOID)
{
    HI_CHAR aszBuf[16];

    snprintf(aszBuf, sizeof(aszBuf), "omxvdec");
    VDEC_PROC_Destroy(aszBuf);

    return;
}

static HI_S32 omxvdec_suspend(struct platform_device *pltdev, pm_message_t state)
{
    HI_S32 ret;

    OmxPrint(OMX_ALWS, "%s enter.\n", __func__);

    ret = channel_suspend();
    if (ret != HI_SUCCESS)
    {
	    OmxPrint(OMX_FATAL, "%s failed!\n", __func__);
    }

    OmxPrint(OMX_ALWS, "%s success!\n", __func__);

    return HI_SUCCESS;
}

static HI_S32 omxvdec_resume(struct platform_device *pltdev)
{
    HI_S32 ret;

    OmxPrint(OMX_ALWS, "%s enter.\n", __func__);

    ret = channel_resume();
    if (ret != HI_SUCCESS)
    {
	    OmxPrint(OMX_FATAL, "%s failed!\n", __func__);
    }

    OmxPrint(OMX_ALWS, "%s success!\n", __func__);

    return HI_SUCCESS;
}

static HI_VOID omxvdec_device_release(struct device* dev)
{
	return;
}

static struct platform_driver omxvdec_driver = {

	.probe              = omxvdec_probe,
	.remove             = omxvdec_remove,
	.suspend            = omxvdec_suspend,
	.resume             = omxvdec_resume,
	.driver = {
	    .name           = (HI_PCHAR)g_OmxVdecDrvName,
	    .owner          = THIS_MODULE,
	    .of_match_table = Hisi_Vdec_Match_Table
	},
};

static struct platform_device omxvdec_device = {

	.name              = g_OmxVdecDrvName,
	.id                = -1,
    .dev = {
        .platform_data = NULL,
        .release       = omxvdec_device_release,
    },
};

HI_S32 __init OMXVDEC_DRV_ModInit(HI_VOID)
{
    HI_S32 ret;

    ret = platform_device_register(&omxvdec_device);
    if(ret < 0)
    {
        OmxPrint(OMX_FATAL, "%s call platform_device_register failed!\n", __func__);
        return ret;
    }

    ret = platform_driver_register(&omxvdec_driver);
    if(ret < 0)
    {
        OmxPrint(OMX_FATAL, "%s call platform_driver_register failed!\n", __func__);
        goto exit;
    }

#ifndef HI_ADVCA_FUNCTION_RELEASE
    ret = omxvdec_init_proc();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "omxvdec_init_proc failed!\n");
        goto exit1;
    }

#ifdef MODULE
	OmxPrint(OMX_ALWS, "Load hi_omxvdec.ko (%d) success.\n", OMXVDEC_VERSION);
#endif
#endif

	return HI_SUCCESS;

exit1:
	platform_driver_unregister(&omxvdec_driver);
exit:
	platform_device_unregister(&omxvdec_device);

	return ret;
}

HI_VOID __exit OMXVDEC_DRV_ModExit(HI_VOID)
{
	platform_driver_unregister(&omxvdec_driver);
	platform_device_unregister(&omxvdec_device);

#ifndef HI_ADVCA_FUNCTION_RELEASE
    omxvdec_exit_proc();

#ifdef MODULE
    OmxPrint(OMX_ALWS, "Unload hi_omxvdec.ko (%d) success.\n", OMXVDEC_VERSION);
#endif
#endif

}


//#ifdef MODULE
module_init(OMXVDEC_DRV_ModInit);
module_exit(OMXVDEC_DRV_ModExit);
//#endif



