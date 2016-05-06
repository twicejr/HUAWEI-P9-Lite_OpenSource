
#ifndef __VFMW_LINUX_KERNEL_PROC_HEADER__
#define  __VFMW_LINUX_KERNEL_PROC_HEADER__

#include "linux_kernel_osal.h"

#define VFMW_MAX_PROC_NAME_SIZE 16

#define PROC_PRINT(arg...)  seq_printf(arg)

typedef SINT32 (*vfmw_proc_read_fn)(struct seq_file *, VOID *);
typedef SINT32 (*vfmw_proc_write_fn)(struct file *file, const char __user *buf, size_t count, loff_t *ppos);

typedef struct
{
    HI_CHAR proc_name[VFMW_MAX_PROC_NAME_SIZE];

    vfmw_proc_read_fn  read;
    vfmw_proc_write_fn write;
} vfmw_proc_func;

VOID VID_STD_Enum2Str(VID_STD_E eVidStd, char *strVidStd);

SINT32 vfmw_read_proc(struct seq_file *p, void *v);
SINT32 vfmw_read_proc_dbg(struct seq_file *p, void *v);
SINT32 vfmw_read_proc_prn(struct seq_file *p, void *v);
SINT32 vfmw_read_proc_scd(struct seq_file *p, void *v);
SINT32 vfmw_read_proc_chn(struct seq_file *p, void *v);
SINT32 vfmw_read_proc_dec(struct seq_file *p, void *v);

ssize_t vfmw_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);

#ifdef VFMW_SCD_LOWDLY_SUPPORT
int vfmw_read_proc_lwd(struct seq_file *p, void *v);
#endif

SINT32 str2val(char *str, unsigned int *data);

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
SINT32 vfmw_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *data);
#else
SINT32 vfmw_write_proc(struct file *file, const char __user *buffer, size_t count, loff_t *pos);
#endif

SINT32 vfmw_proc_open(struct inode *inode, struct file *file);

static const struct file_operations vfmw_proc_fops =
{
    .owner   = THIS_MODULE,
    .open    = vfmw_proc_open,
    .read    = seq_read,
    .write   = vfmw_proc_write,
    .llseek  = seq_lseek,
    .release = single_release,
};

SINT32 OSAL_ProcCreate(HI_CHAR *proc_name, vfmw_proc_read_fn read, vfmw_proc_write_fn write);
VOID   OSAL_ProcDestroy(HI_CHAR *proc_name);
SINT32 OSAL_ProcInit(VOID);
VOID   OSAL_ProcExit(VOID);

#endif

