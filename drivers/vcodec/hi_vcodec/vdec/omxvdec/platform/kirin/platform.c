


#include <linux/math64.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/file.h>
#include <linux/major.h>

#include "omxvdec.h"
#include "platform.h"
#include "vfmw_ext.h"

/********************************** MACRO *************************************/
#define DIV_NS_TO_MS               (1000000)
#define DRV_MAX_PROC_NAME_SIZE     (16)
#define DEFAULT_ECHO_DEVICE_HANDLE (0)
#define PLATFORM_PROC_NAME         "omxvdec_info"


/********************************* FUNCTION ***********************************/
extern HI_S32  VFMW_GetFunction(VFMW_EXPORT_FUNC_S **ppVfmwExportFuncs);
static HI_S32  DRV_PROC_Open(struct inode *inode, struct file *file);
static ssize_t DRV_PROC_Write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);


/********************************* STRUCT *************************************/
typedef struct
{
    HI_CHAR            proc_name[DRV_MAX_PROC_NAME_SIZE];
    drv_proc_read_fn   pread;
    drv_proc_write_fn  pwrite;
} DRV_PROC_FUNC;

static const struct file_operations  gProcFopS =
{
    .owner   = THIS_MODULE,
    .open    = DRV_PROC_Open,
    .read    = seq_read,
    .write   = DRV_PROC_Write,
    .llseek  = seq_lseek,
    .release = single_release,
};


/*********************************** VARS *************************************/
static DRV_PROC_FUNC  gMemProc;
static DRV_PROC_FUNC  gOmxVdecProc;
VFMW_EXPORT_FUNC_S   *pVfmwExportFuncs = HI_NULL;


/******************************** LOCAL FUNC **********************************/

/*----------------------------------------
    proc fs relative functions
 ----------------------------------------*/
static HI_S32 DRV_PROC_Open(struct inode *inode, struct file *file)
{
    DRV_PROC_FUNC *proc;

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
    proc = PDE(inode)->data;
#else
    proc = PDE_DATA(inode);
#endif
    if(NULL == proc)
    {
        return HI_FAILURE;
    }
    if (proc->pread)
    {
        return single_open(file, proc->pread, proc);
    }

    return HI_FAILURE;
}

static ssize_t DRV_PROC_Write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    struct seq_file *s   = file->private_data;
    DRV_PROC_FUNC  *proc = s->private;

    if (proc->pwrite)
    {
        return proc->pwrite(file, buf, count, ppos);
    }

    return HI_FAILURE;
}

static inline HI_S32 DRV_PROC_Create_Node(DRV_PROC_FUNC *proc, HI_CHAR *proc_name, drv_proc_read_fn pfn_read, drv_proc_write_fn pfn_write)
{
    struct proc_dir_entry  *entry;

    strncpy(proc->proc_name, proc_name, DRV_MAX_PROC_NAME_SIZE);
    proc->proc_name[DRV_MAX_PROC_NAME_SIZE - 1] = 0;

    proc->pread  = pfn_read;
    proc->pwrite = pfn_write;

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
    entry = create_proc_entry(proc->proc_name, 0666, HI_NULL);
    if (!entry)
    {
        return HI_FAILURE;
    }

    entry->proc_fops  = &gProcFopS;
    entry->data       = proc;
#else
    entry = proc_create_data(proc->proc_name, 0666, HI_NULL, &gProcFopS, (void*)proc);
    if (!entry)
    {
        return HI_FAILURE;
    }
#endif

    return HI_SUCCESS;
}

static inline HI_S32 DRV_PROC_Destroy_Node(DRV_PROC_FUNC *proc)
{
    remove_proc_entry(proc->proc_name, HI_NULL);
    memset(proc, 0, sizeof(DRV_PROC_FUNC));

    return HI_SUCCESS;
}

static HI_VOID DRV_PROC_EchoHelperVargs(HI_CHAR *buf, HI_U32 size, const HI_CHAR * fmt, va_list args)
{
    struct kstat stat;
    HI_S32 ret;

    if (!buf || 0 == size)
    {
        return;
    }

    ret = vfs_fstat(DEFAULT_ECHO_DEVICE_HANDLE, &stat);
    if (ret)
    {
        return;
    }

    vsnprintf(buf, size, fmt, args);

    /* echo device must be chrdev and major number must be TTYAUX_MAJOR or UNIX98_PTY_SLAVE_MAJOR */
    if ( S_ISCHR(stat.mode) && (MAJOR(stat.rdev) == TTYAUX_MAJOR || MAJOR(stat.rdev) == UNIX98_PTY_SLAVE_MAJOR) )
    {
        struct file *file = fget(DEFAULT_ECHO_DEVICE_HANDLE);
        if (file)
        {
            mm_segment_t stOld_FS = {0};
            /* file pos is invalid for chrdev */
            loff_t pos = 0;

            set_fs(KERNEL_DS);
            vfs_write(file, buf, strlen(buf), &pos);
            set_fs(stOld_FS);

            fput(file);
        }
    }
    
    return;
}

/*----------------------------------------
    func: memory read proc entry
 ----------------------------------------*/
HI_S32 VDEC_Platform_Read_Proc(struct seq_file *p, HI_VOID *v)
{
    PROC_PRINT(p, "\n");
    
    VDEC_MEM_Read_Proc((HI_VOID *)p, v);
    
    VDEC_Regulator_Read_Proc((HI_VOID *)p, v);
    
    PROC_PRINT(p, "\n");

    return 0;
}


/******************************** SHARE FUNC **********************************/

/*----------------------------------------
    func: get module export functions
 ----------------------------------------*/
HI_S32 VDEC_MODULE_GetFunction(OMX_MODULE_E u32ModuleID, HI_VOID** ppFunc)
{
    if (HI_NULL == ppFunc)
    {
        OmxPrint(OMX_FATAL, "%s null pointer error\n", __func__);
        return HI_FAILURE;
    }

    switch(u32ModuleID)
    {
        case MODULE_VFMW:
			pVfmwExportFuncs = HI_NULL;
			VFMW_GetFunction(&pVfmwExportFuncs);
			if (pVfmwExportFuncs == HI_NULL)
			{
                OmxPrint(OMX_ERR, "%s VFMW_GetFunction failed\n", __func__);
                return HI_FAILURE;
			}
			else
			{
                *ppFunc = (HI_VOID *)pVfmwExportFuncs;
			}
            break;

        case MODULE_VPSS:
            break;

        case MODULE_BPP:
            break;

        default:
           OmxPrint(OMX_ERR, "%s unkown module %d\n", __func__, u32ModuleID);
           return HI_FAILURE;
    }

    return HI_SUCCESS;
}


/*----------------------------------------
    func: get system time function
 ----------------------------------------*/
HI_S32 VDEC_SYS_GetTimeStampMs(HI_U32 *pu32TimeMs)
{
    HI_U64 u64TimeNow;

    if (HI_NULL == pu32TimeMs)
    {
        OmxPrint(OMX_ERR, "%s null pointer error\n", __func__);
        return HI_FAILURE;
    }

    u64TimeNow = sched_clock();

    do_div(u64TimeNow, DIV_NS_TO_MS);

    *pu32TimeMs = (HI_U32)u64TimeNow;

    return HI_SUCCESS;
}


/*----------------------------------------
    func: omxvdec proc create
 ----------------------------------------*/
HI_S32 VDEC_PROC_Create(HI_CHAR *proc_name, drv_proc_read_fn pfn_read, drv_proc_write_fn pfn_write)
{
    HI_S32 ret = HI_FAILURE;
    DRV_PROC_FUNC *proc;

    // create platform proc
    proc = &gMemProc;
    memset(proc, 0, sizeof(DRV_PROC_FUNC));

    ret = DRV_PROC_Create_Node(proc, PLATFORM_PROC_NAME, VDEC_Platform_Read_Proc, HI_NULL);
	if (ret != HI_SUCCESS)
	{
        OmxPrint(OMX_ERR, "Create proc %s failed!\n", PLATFORM_PROC_NAME);
        return HI_FAILURE;
	}

    // create omxvdec proc
    proc = &gOmxVdecProc;
    memset(proc, 0, sizeof(DRV_PROC_FUNC));

    ret = DRV_PROC_Create_Node(proc, proc_name, pfn_read, pfn_write);
	if (ret != HI_SUCCESS)
	{
	    DRV_PROC_Destroy_Node(&gMemProc);
        OmxPrint(OMX_ERR, "Create proc %s failed!\n", proc_name);
        return HI_FAILURE;
	}

    return HI_SUCCESS;
}


/*----------------------------------------
    func: omxvdec proc destroy
 ----------------------------------------*/
HI_VOID VDEC_PROC_Destroy(HI_CHAR *proc_name)
{
    DRV_PROC_FUNC *proc = &gOmxVdecProc;

    if (0 == strncmp(proc_name, proc->proc_name, sizeof(proc->proc_name)))
    {
        DRV_PROC_Destroy_Node(proc);
    }

	DRV_PROC_Destroy_Node(&gMemProc);

    return;
}


/*----------------------------------------
    func: omxvdec proc help message
 ----------------------------------------*/
HI_VOID VDEC_PROC_EchoHelper(const HI_CHAR *fmt, ...)
{
    char buf[512];
    va_list args;

    if (HI_NULL == fmt)
    {
        return;
    }

    va_start(args, fmt);
    DRV_PROC_EchoHelperVargs(buf, sizeof(buf), fmt, args);
    va_end(args);
}

